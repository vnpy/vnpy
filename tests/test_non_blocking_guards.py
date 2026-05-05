import unittest
import time
import threading
from unittest.mock import patch
from vnpy.event import Event
from vnpy.event.disruptor_engine import DisruptorEventEngine
from vnpy.trader.setting import SETTINGS

class TestNonBlockingGuards(unittest.TestCase):
    """
    Guards against issues solved by the try_put architecture:
    1. Deadlock prevention when calling event publication from worker thread.
    2. Non-blocking log publication using try_put.
    """

    def test_explicit_non_blocking_try_put(self):
        """Verifies that try_put returns immediately even if the buffer is full."""
        # Use a very small buffer for testing saturation
        with patch.dict(SETTINGS, {"event.buffer_size": 1024}):
            engine = DisruptorEventEngine(interval=1)
            
            def slow_handler(event):
                if event.type == "slow":
                    time.sleep(0.1) # Faster but still slow
            
            engine.register("slow", slow_handler)
            engine.start()

            # 1. Fill the buffer
            # With 1024 buffer size, pushing 2000 events will definitely saturate it.
            # We use a separate thread to fill it so we don't block the main thread yet.
            def filler():
                for i in range(1500):
                    engine.put(Event("slow", i))
            
            fill_thread = threading.Thread(target=filler)
            fill_thread.start()
            
            # Wait a bit for the filler to start filling
            time.sleep(0.5)
            
            # 2. Try to publish with try_put. This should NOT block.
            start = time.perf_counter()
            success = engine.try_put(Event("any", "test"))
            end = time.perf_counter()
            
            # If it blocked, it would wait for at least one slot to open (0.1s).
            self.assertLess(end - start, 0.05, f"try_put() blocked for {end-start:.4f}s")
            
            engine.stop()
            fill_thread.join(timeout=1.0)

    def test_worker_thread_publication_safety(self):
        """Verifies that the worker thread can use try_put safely without deadlocking."""
        with patch.dict(SETTINGS, {"event.buffer_size": 1024}):
            engine = DisruptorEventEngine(interval=1)
            
            results = []
            
            def recursive_handler(event):
                if event.type == "trigger":
                    # Use try_put inside the worker. Even if buffer is full, it shouldn't deadlock.
                    for i in range(1500):
                        engine.try_put(Event("dummy", i))
                    results.append("success")

            engine.register("trigger", recursive_handler)
            engine.start()
            
            # Trigger the recursive call
            engine.put(Event("trigger"))
            
            # Wait for processing
            time.sleep(1.0)
            
            self.assertIn("success", results, "Worker thread encountered issues during recursive try_put()")
            
            engine.stop()

if __name__ == "__main__":
    unittest.main()
