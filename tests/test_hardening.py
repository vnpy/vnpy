import time
import unittest
import signal
from vnpy.event import Event, DisruptorEventEngine
from vnpy.trader.setting import SETTINGS
from unittest.mock import patch


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


class TestEngineHardening(unittest.TestCase):
    @timeout(15)
    def test_buffer_full_no_deadlock(self):
        """
        Verify that put() blocks but DOES NOT deadlock when buffer is full.
        """
        with patch.dict(SETTINGS, {"event.buffer_size": 128}):
            engine = DisruptorEventEngine()

            # Clog with slow handler
            engine.register("test", lambda e: time.sleep(0.01))
            engine.start()

            # Fill buffer
            for i in range(130):
                engine.try_put(Event("test", i))

            # Next put should block but eventually succeed once worker clears space
            start = time.time()
            engine.put(Event("test", "blocking_call"))
            _ = time.time() - start

            # Should have blocked for some time but succeeded
            self.assertTrue(engine.is_active())
            engine.stop()

    @timeout(10)
    def test_non_blocking_try_put(self):
        """
        Verify that try_put (used for logs) is truly non-blocking.
        """
        with patch.dict(SETTINGS, {"event.buffer_size": 128}):
            engine = DisruptorEventEngine()
            # Use a shorter sleep to avoid long shutdown
            engine.register("test", lambda e: time.sleep(0.01))
            engine.start()

            # Flood to fill the 128-slot buffer
            for i in range(200):
                engine.try_put(Event("test", i))

            start = time.time()
            # This should be instant because it's try_put
            engine.try_put(Event("log", "non-blocking"))
            elapsed = time.perf_counter() - start

            # success should be False because buffer is full
            # elapsed should be very small
            self.assertLess(elapsed, 0.05)
            engine.stop()

    @timeout(10)
    def test_pre_start_buffering(self):
        """
        Verify parity with standard engine: events can be published before start().
        """
        engine = DisruptorEventEngine()
        results = []
        engine.register("test", lambda e: results.append(e.data))

        engine.put(Event("test", "A"))
        engine.put(Event("test", "B"))

        self.assertEqual(len(results), 0)
        engine.start()
        time.sleep(0.2)
        self.assertEqual(len(results), 2)
        self.assertIn("A", results)
        self.assertIn("B", results)
        engine.stop()

    @timeout(10)
    def test_exception_propagation(self):
        """Verify that an exception in a handler stops the engine and is raised in put()."""
        engine = DisruptorEventEngine()

        def bad_handler(event):
            raise ValueError("Handler explosion!")

        engine.register("boom", bad_handler)
        engine.start()

        # 1. Trigger the explosion
        engine.put(Event("boom", "payload"))

        # 2. Wait for worker to catch it and stop
        time.sleep(0.1)

        # 3. Next put() should raise the error
        with self.assertRaises(ValueError):
            engine.put(Event("boom", "payload"))

        self.assertFalse(engine.is_active())
        engine.stop()

    @timeout(10)
    def test_panic_guard_stops_engine(self):
        """Verify that if the worker thread stops, the engine is marked inactive."""
        engine = DisruptorEventEngine()
        engine.start()
        self.assertTrue(engine.is_active())

        # Simulate worker stopping via producer stop
        engine._producer.stop()
        self.assertFalse(engine.is_active())
        engine.stop()

    @timeout(10)
    def test_clean_shutdown_no_leaks(self):
        """Verify multiple start/stop cycles with pending events."""
        engine = DisruptorEventEngine()
        for _ in range(3):
            engine.start()
            for i in range(10):
                engine.put(Event("test", i))
            engine.stop()
            self.assertFalse(engine.is_active())


if __name__ == "__main__":
    unittest.main()
