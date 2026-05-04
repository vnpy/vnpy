import time
import unittest
from datetime import datetime
from vnpy.event import Event
from vnpy.trader.engine import MainEngine, BaseEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import TickData
from vnpy.trader.constant import Exchange
from vnpy.trader.app import BaseApp
from vnpy.trader.event import EVENT_TICK
from unittest.mock import patch
from vnpy.trader.setting import SETTINGS

# ─────────────────────────────────────────────────────────────────────────────
# Mock Components
# ─────────────────────────────────────────────────────────────────────────────


class MockGateway(BaseGateway):
    default_name = "MOCK"

    def connect(self, setting: dict):
        pass

    def subscribe(self, req):
        pass

    def send_order(self, req):
        return ""

    def cancel_order(self, req):
        pass

    def query_account(self):
        pass

    def query_position(self):
        pass

    def close(self):
        pass

    def simulate_ticks(self, n: int):
        for i in range(n):
            tick = TickData(
                symbol="BTC",
                exchange=Exchange.LOCAL,
                datetime=datetime.now(),
                last_price=50000.0 + i,
                gateway_name=self.gateway_name,
            )
            self.on_tick(tick)


class MockEngine(BaseEngine):
    def __init__(self, main_engine, event_engine):
        super().__init__(main_engine, event_engine, "MockEngine")
        self.tick_count = 0
        self.event_engine.register(EVENT_TICK, self.process_tick)

    def process_tick(self, event: Event):
        self.tick_count += 1


class MockApp(BaseApp):
    app_name = "MockApp"
    engine_class = MockEngine
    widget_class = None
    icon_name = ""


# ─────────────────────────────────────────────────────────────────────────────
# Test Case
# ─────────────────────────────────────────────────────────────────────────────


class TestDisruptorE2E(unittest.TestCase):
    def setUp(self):
        # Enable Disruptor for these tests
        self.patcher = patch.dict(
            SETTINGS,
            {
                "event.use_disruptor": True,
                "event.buffer_size": 1024,
                "event.wait_strategy": "busy_spin",
            },
        )
        self.patcher.start()

    def tearDown(self):
        self.patcher.stop()

    def test_main_engine_integration(self):
        """Verify Disruptor integration with MainEngine, Gateway and App."""
        print("\nStarting E2E Disruptor Integration Test...")

        # 1. Create MainEngine (will use DisruptorEventEngine via factory)
        main_engine = MainEngine()
        self.assertTrue(main_engine.event_engine.is_active())

        # 2. Add App & Engine
        mock_engine = main_engine.add_app(MockApp)

        # 3. Add Gateway
        gateway = main_engine.add_gateway(MockGateway)

        # 4. Simulate Load
        n_ticks = 5000
        print(f"Simulating {n_ticks} ticks through {gateway.gateway_name}...")
        gateway.simulate_ticks(n_ticks)

        # 5. Verify Processing
        # Wait for events to be processed by Disruptor worker
        timeout = time.time() + 5.0
        while mock_engine.tick_count < n_ticks and time.time() < timeout:
            time.sleep(0.1)

        print(f"Ticks processed by MockEngine: {mock_engine.tick_count}")
        self.assertEqual(mock_engine.tick_count, n_ticks)

        main_engine.close()
        print("E2E Integration Test PASSED.")


if __name__ == "__main__":
    unittest.main()
