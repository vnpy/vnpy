"""Comprehensive tests for DisruptorEventEngine + standard EventEngine."""

from __future__ import annotations

import threading
import time
import signal
from unittest.mock import MagicMock, patch

import pytest

from vnpy.event import Event, EVENT_TIMER, create_engine
from vnpy.event.engine import EventEngine as StandardEventEngine
from vnpy.trader.setting import SETTINGS

def timeout(seconds):
    def decorator(func):
        def wrapper(*args, **kwargs):
            def handler(signum, frame):
                raise TimeoutError(f"Test timed out after {seconds} seconds")
            signal.signal(signal.SIGALRM, handler)
            signal.alarm(seconds)
            try:
                result = func(*args, **kwargs)
            finally:
                signal.alarm(0)
            return result
        return wrapper
    return decorator


# ─────────────────────────────────────────────────────────────────────────────
# Helpers
# ─────────────────────────────────────────────────────────────────────────────

def _has_rust() -> bool:
    try:
        from vnpy_disruptor import DisruptorProducer  # noqa: F401
        return True
    except ImportError:
        return False


RUST_AVAILABLE = _has_rust()
requires_rust = pytest.mark.skipif(not RUST_AVAILABLE, reason="Rust extension not available")


# ─────────────────────────────────────────────────────────────────────────────
# Factory
# ─────────────────────────────────────────────────────────────────────────────

class TestEventEngineFactory:
    """Factory creates correct engine type based on settings."""

    @timeout(5)
    def test_default_creates_standard_engine(self):
        """With feature flag disabled, should return standard EventEngine."""
        with patch.dict(SETTINGS, {"event.use_disruptor": False}):
            engine = create_engine(1)
            assert isinstance(engine, StandardEventEngine)

    @requires_rust
    @timeout(5)
    def test_enabled_creates_disruptor(self):
        """With feature flag enabled (and Rust available), should return DisruptorEventEngine."""
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        with patch.dict(SETTINGS, {"event.use_disruptor": True}):
            engine = create_engine(1)
            assert isinstance(engine, DisruptorEventEngine)


# ─────────────────────────────────────────────────────────────────────────────
# DisruptorEventEngine API surface
# ─────────────────────────────────────────────────────────────────────────────

@requires_rust
class TestDisruptorEventEngineAPI:
    """DisruptorEventEngine API must match standard EventEngine."""

    def setup_method(self):
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        with patch.dict(SETTINGS, {"event.buffer_size": 256}):
            self.engine = DisruptorEventEngine(interval=1)

    def teardown_method(self):
        if self.engine.is_active():
            self.engine.stop()

    def test_register_type_handler(self):
        handler = MagicMock()
        self.engine.register("test.event", handler)
        assert "test.event" in self.engine._handlers

    def test_unregister_type_handler(self):
        handler = MagicMock()
        self.engine.register("test.event", handler)
        self.engine.unregister("test.event", handler)
        assert "test.event" not in self.engine._handlers

    def test_register_general_handler(self):
        handler = MagicMock()
        self.engine.register_general(handler)
        assert handler in self.engine._general_handlers

    def test_unregister_general_handler(self):
        handler = MagicMock()
        self.engine.register_general(handler)
        self.engine.unregister_general(handler)
        assert handler not in self.engine._general_handlers

    @timeout(10)
    def test_put_event_via_process(self):
        """put() should eventually dispatch to registered handlers."""
        processed = []

        def handler(event: Event):
            processed.append(event.data)

        self.engine.register("test.event", handler)
        self.engine.start()

        event = Event("test.event", {"value": 42})
        self.engine.put(event)

        # Give the worker thread time to process
        timeout_at = time.time() + 2.0
        while not processed and time.time() < timeout_at:
            time.sleep(0.005)

        assert processed == [{"value": 42}]

    def test_start_stop(self):
        """start/stop should control is_active."""
        assert not self.engine.is_active()
        self.engine.start()
        assert self.engine.is_active()
        self.engine.stop()
        assert not self.engine.is_active()

    def test_processing_dispatches_to_handler(self):
        """_process dispatches to type-specific handlers."""
        processed = []

        def handler(event: Event):
            processed.append(event.data)

        self.engine.register("test.event", handler)
        self.engine._process(Event("test.event", {"value": 42}))

        assert processed == [{"value": 42}]

    def test_processing_dispatches_to_general_handler(self):
        """_process dispatches to general handlers regardless of type."""
        processed = []

        def handler(event: Event):
            processed.append(event.type)

        self.engine.register_general(handler)
        self.engine._process(Event("any.event"))

        assert processed == ["any.event"]

    def test_multiple_handlers_same_type(self):
        """All handlers for a type are called in registration order."""
        results = []
        self.engine.register("test.event", lambda e: results.append(1))
        self.engine.register("test.event", lambda e: results.append(2))
        self.engine._process(Event("test.event"))
        assert results == [1, 2]

    def test_handler_exception_propagates(self):
        """Handler exceptions must propagate (Production Hardening)."""
        def bad_handler(event: Event):
            raise ValueError("test error")

        self.engine.register("test.event", bad_handler)
        
        with pytest.raises(ValueError, match="test error"):
            self.engine._process(Event("test.event"))

    def test_timer_generation(self):
        """Timer events should be generated at the configured interval."""
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        with patch.dict(SETTINGS, {"event.buffer_size": 256}):
            engine = DisruptorEventEngine(interval=0)

        timer_events: list[Event] = []
        engine.register(EVENT_TIMER, lambda e: timer_events.append(e))
        engine.start()
        time.sleep(0.1)
        engine.stop()

        assert len(timer_events) >= 1

    def test_is_active_status(self):
        """is_active reflects real engine state."""
        assert not self.engine.is_active()
        self.engine.start()
        assert self.engine.is_active()
        self.engine.stop()
        assert not self.engine.is_active()

    def test_get_handler_count(self):
        self.engine.register("x", MagicMock())
        self.engine.register("x", MagicMock())
        assert self.engine.get_handler_count("x") == 2
        assert self.engine.get_handler_count("y") == 0

    def test_get_general_handler_count(self):
        self.engine.register_general(MagicMock())
        assert self.engine.get_general_handler_count() == 1


# ─────────────────────────────────────────────────────────────────────────────
# End-to-end throughput
# ─────────────────────────────────────────────────────────────────────────────

@requires_rust
class TestDisruptorPerformance:
    """End-to-end delivery correctness under load."""

    @timeout(10)
    def test_all_events_delivered(self):
        """Every published event should reach the handler (buffer large enough)."""
        from vnpy.event.disruptor_engine import DisruptorEventEngine

        n = 1000
        with patch.dict(SETTINGS, {"event.buffer_size": 4096}):
            engine = DisruptorEventEngine(interval=1)

        processed = []
        engine.register("test", lambda e: processed.append(e.data))
        engine.start()

        for i in range(n):
            engine.put(Event("test", i))

        deadline = time.time() + 5.0
        while len(processed) < n and time.time() < deadline:
            time.sleep(0.01)

        engine.stop()
        assert len(processed) == n, f"Expected {n}, got {len(processed)}"

    def test_payload_fidelity(self):
        """Payloads survive the Rust boundary faithfully via pickle."""
        from vnpy.event.disruptor_engine import DisruptorEventEngine

        payload = {"price": 100.5, "symbol": "BTCUSDT", "nested": [1, 2, 3]}
        received = []

        with patch.dict(SETTINGS, {"event.buffer_size": 64}):
            engine = DisruptorEventEngine(interval=1)

        engine.register("tick", lambda e: received.append(e.data))
        engine.start()
        engine.put(Event("tick", payload))

        timeout = time.time() + 2.0
        while not received and time.time() < timeout:
            time.sleep(0.005)

        engine.stop()
        assert received == [payload]

    def test_none_payload_handled(self):
        """Events with None data should work."""
        from vnpy.event.disruptor_engine import DisruptorEventEngine

        received = []
        with patch.dict(SETTINGS, {"event.buffer_size": 64}):
            engine = DisruptorEventEngine(interval=1)

        engine.register("empty", lambda e: received.append(e.data))
        engine.start()
        engine.put(Event("empty", None))

        timeout = time.time() + 2.0
        while not received and time.time() < timeout:
            time.sleep(0.005)

        engine.stop()
        assert received == [None]


# ─────────────────────────────────────────────────────────────────────────────
# Feature flag combinations
# ─────────────────────────────────────────────────────────────────────────────

class TestFeatureFlagCombinations:
    """All possible feature flag combinations."""

    def test_neither_enabled(self):
        with patch.dict(SETTINGS, {"event.use_arrow": False, "event.use_disruptor": False}):
            engine = create_engine()
            assert isinstance(engine, StandardEventEngine)

    @requires_rust
    def test_disruptor_only(self):
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        with patch.dict(SETTINGS, {"event.use_arrow": False, "event.use_disruptor": True}):
            engine = create_engine()
            assert isinstance(engine, DisruptorEventEngine)

    def test_arrow_only(self):
        from vnpy.trader.arrow_oms import create_arrow_oms
        with patch.dict(SETTINGS, {"event.use_arrow": True, "event.use_disruptor": False}):
            event_engine = create_engine(1)
            assert isinstance(event_engine, StandardEventEngine)
            oms = create_arrow_oms(MagicMock(), event_engine)
            assert oms is not None
            assert oms.is_enabled()

    @requires_rust
    def test_both_enabled(self):
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        from vnpy.trader.arrow_oms import create_arrow_oms
        with patch.dict(SETTINGS, {"event.use_arrow": True, "event.use_disruptor": True}):
            event_engine = create_engine(1)
            assert isinstance(event_engine, DisruptorEventEngine)
            oms = create_arrow_oms(MagicMock(), event_engine)
            assert oms is not None
            assert oms.is_enabled()


# ─────────────────────────────────────────────────────────────────────────────
# Backward compatibility
# ─────────────────────────────────────────────────────────────────────────────

class TestBackwardCompatibility:
    """Existing downstream code must continue working unchanged."""

    def test_existing_gateway_works(self):
        from vnpy.trader.gateway import BaseGateway
        assert hasattr(BaseGateway, "on_tick")
        assert hasattr(BaseGateway, "on_order")
        assert hasattr(BaseGateway, "on_trade")
        assert hasattr(BaseGateway, "on_position")
        assert hasattr(BaseGateway, "on_account")
        assert hasattr(BaseGateway, "on_quote")

    def test_existing_oms_works(self):
        from vnpy.trader.engine import OmsEngine
        assert hasattr(OmsEngine, "process_tick_event")
        assert hasattr(OmsEngine, "process_order_event")
        assert hasattr(OmsEngine, "get_tick")
        assert hasattr(OmsEngine, "get_all_ticks")

    def test_existing_data_objects_work(self):
        from vnpy.trader.object import TickData
        from vnpy.trader.constant import Exchange
        from datetime import datetime

        tick = TickData(
            symbol="BTCUSDT",
            exchange=Exchange.LOCAL,
            datetime=datetime.now(),
            last_price=50000.0,
            gateway_name="test",
        )
        assert tick.last_price == 50000.0
        assert tick.vt_symbol == "BTCUSDT.LOCAL"

    def test_event_imports_unchanged(self):
        from vnpy.event import Event, EventEngine, EVENT_TIMER
        assert Event is not None
        assert EventEngine is not None
        assert EVENT_TIMER == "eTimer"

    def test_data_to_arrow_method(self):
        from vnpy.trader.object import TickData
        from vnpy.trader.constant import Exchange
        from datetime import datetime

        tick = TickData(
            symbol="BTCUSDT",
            exchange=Exchange.LOCAL,
            datetime=datetime.now(),
            last_price=50000.0,
            gateway_name="test",
        )
        # Method exists even if pyarrow not installed
        assert hasattr(tick, "to_arrow")


# ─────────────────────────────────────────────────────────────────────────────
# Edge cases
# ─────────────────────────────────────────────────────────────────────────────

@requires_rust
class TestEdgeCases:
    """Edge cases and error handling."""

    def _make_engine(self, buffer_size: int = 256):
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        with patch.dict(SETTINGS, {"event.buffer_size": buffer_size}):
            return DisruptorEventEngine(interval=1)

    def test_double_start_no_effect(self):
        engine = self._make_engine()
        engine.start()
        engine.start()  # idempotent
        assert engine.is_active()
        engine.stop()

    def test_stop_twice_no_effect(self):
        engine = self._make_engine()
        engine.start()
        engine.stop()
        engine.stop()  # idempotent
        assert not engine.is_active()

    def test_buffer_size_must_be_power_of_two(self):
        """Non-power-of-2 buffer_size raises ValueError from Rust."""
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        with patch.dict(SETTINGS, {"event.buffer_size": 300}):
            with pytest.raises(ValueError, match="power of 2"):
                DisruptorEventEngine(interval=1)

    def test_valid_buffer_sizes(self):
        for size in [64, 256, 512, 1024, 65536]:
            engine = self._make_engine(buffer_size=size)
            assert engine is not None
            engine._producer.stop()

    def test_unknown_wait_strategy_raises(self):
        from vnpy.event.disruptor_engine import DisruptorEventEngine
        with patch.dict(SETTINGS, {
            "event.buffer_size": 256,
            "event.wait_strategy": "invalid_strategy",
        }):
            with pytest.raises(ValueError, match="wait_strategy"):
                DisruptorEventEngine(interval=1)


# ─────────────────────────────────────────────────────────────────────────────
# Rust extension smoke tests (direct)
# ─────────────────────────────────────────────────────────────────────────────

@requires_rust
class TestRustExtensionDirect:
    """Direct tests of the DisruptorProducer PyO3 bindings."""

    @timeout(5)
    def test_basic_publish_consume(self):
        from vnpy_disruptor import DisruptorProducer
        p = DisruptorProducer(1024, "busy_spin")
        
        processed = []
        def callback(batch):
            processed.extend(batch)
            
        p.start_worker(callback)
        p.publish({"event_type": "eTick", "data": {"price": 42.0}})
        
        deadline = time.time() + 2.0
        while not processed and time.time() < deadline:
            time.sleep(0.01)
            
        assert len(processed) == 1
        assert processed[0]["event_type"] == "eTick"
        assert processed[0]["data"] == {"price": 42.0}
        p.stop()

    @timeout(5)
    def test_batch_consume_flow(self):
        from vnpy_disruptor import DisruptorProducer
        p = DisruptorProducer(1024, "busy_spin")
        processed = []
        p.start_worker(lambda b: processed.extend(b))
        
        for i in range(50):
            p.publish({"t": i})
            
        deadline = time.time() + 2.0
        while len(processed) < 50 and time.time() < deadline:
            time.sleep(0.01)
            
        assert len(processed) == 50
        p.stop()

    @timeout(5)
    def test_none_data_round_trip(self):
        from vnpy_disruptor import DisruptorProducer
        p = DisruptorProducer(64, "busy_spin")
        processed = []
        p.start_worker(lambda b: processed.extend(b))
        
        p.publish({"data": None})
        
        deadline = time.time() + 2.0
        while not processed and time.time() < deadline:
            time.sleep(0.01)
            
        assert len(processed) == 1
        assert processed[0]["data"] is None
        p.stop()


if __name__ == "__main__":
    pytest.main([__file__, "-v", "--tb=short"])