import unittest
import time
import signal
from vnpy.event import Event, EventEngine
from vnpy.event.disruptor_engine import DisruptorEventEngine

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

class ParityTests:
    """Mixin for shared parity tests."""
    
    @timeout(5)
    def test_lifecycle(self):
        engine = self.create_engine()
        self.assertFalse(engine.is_active())
        engine.start()
        self.assertTrue(engine.is_active())
        if engine.is_active():
            engine.stop()
        self.assertFalse(engine.is_active())

    @timeout(5)
    def test_inheritance(self):
        engine = self.create_engine()
        self.assertTrue(isinstance(engine, EventEngine))

    @timeout(10)
    def test_registration(self):
        print("    Running test_registration...")
        engine = self.create_engine()
        results = []
        
        def handler(event):
            results.append(event.data)
            
        engine.register("test", handler)
        engine.start()
        
        engine.put(Event("test", 1))
        time.sleep(0.1)
        self.assertEqual(results, [1])
        
        engine.unregister("test", handler)
        engine.put(Event("test", 2))
        time.sleep(0.1)
        self.assertEqual(results, [1])
        
        if engine.is_active():
            engine.stop()

    @timeout(5)
    def test_unregister_cleanup(self):
        print("    Running test_unregister_cleanup...")
        engine = self.create_engine()
        def handler(event): pass
        
        engine.register("test", handler)
        self.assertEqual(engine.get_handler_count("test"), 1)
        
        engine.unregister("test", handler)
        self.assertEqual(engine.get_handler_count("test"), 0)
        # Check that the key is actually gone from the mapping (standard behavior)
        if hasattr(engine, "_handlers"):
            self.assertNotIn("test", engine._handlers)
        
        if engine.is_active():
            engine.stop()

    @timeout(20)
    def test_multi_producer(self):
        print("    Running test_multi_producer...")
        engine = self.create_engine()
        results = []
        def handler(event): results.append(event.data)
        engine.register("test", handler)
        engine.start()
        
        import threading
        def producer(val):
            for _ in range(5): # Reduced count
                engine.put(Event("test", val))
        
        t1 = threading.Thread(target=producer, args=(1,))
        t2 = threading.Thread(target=producer, args=(2,))
        t1.start()
        t2.start()
        t1.join(timeout=2.0)
        t2.join(timeout=2.0)
        
        time.sleep(0.2)
        self.assertEqual(len(results), 10)
        self.assertEqual(results.count(1), 5)
        self.assertEqual(results.count(2), 5)
        
        if engine.is_active():
            engine.stop()

class TestStandardParity(unittest.TestCase, ParityTests):
    def create_engine(self):
        print("  Creating Standard EventEngine")
        # Wrap standard engine to match Disruptor introspection
        engine = EventEngine()
        if not hasattr(engine, "is_active"):
            engine.is_active = lambda: engine._active
        if not hasattr(engine, "get_handler_count"):
            engine.get_handler_count = lambda t: len(engine._handlers.get(t, []))
        return engine

class TestDisruptorParity(unittest.TestCase, ParityTests):
    def create_engine(self, strategy="busy_spin"):
        print(f"  Creating DisruptorEventEngine (strategy={strategy})")
        from vnpy.trader.setting import SETTINGS
        from unittest.mock import patch
        with patch.dict(SETTINGS, {"event.wait_strategy": strategy}):
            return DisruptorEventEngine()

    @timeout(30)
    def test_all_strategies(self):
        strategies = ["busy_spin", "busy_spin_hint", "yielding", "sleeping", "blocking"]
        for s in strategies:
            print(f"    Testing strategy: {s}")
            with self.subTest(strategy=s):
                engine = self.create_engine(strategy=s)
                # Run lifecycle test as a smoke test for each strategy
                engine.start()
                self.assertTrue(engine.is_active())
                engine.put(Event("test", 1))
                time.sleep(0.01)
                engine.stop()
                self.assertFalse(engine.is_active())

if __name__ == "__main__":
    unittest.main()
