import unittest
from unittest.mock import patch
from vnpy.event import create_engine
from vnpy.event.engine import EventEngine
from vnpy.event.disruptor_engine import DisruptorEventEngine
from vnpy.trader.setting import SETTINGS

class TestEngineFactory(unittest.TestCase):
    """
    Test driven development for the create_engine() factory.
    Verifies that the factory correctly respects global SETTINGS.
    """

    def test_default_factory(self):
        """Should return standard EventEngine by default (event.use_disruptor=False)."""
        with patch.dict(SETTINGS, {"event.use_disruptor": False}):
            engine = create_engine()
            self.assertIsInstance(engine, EventEngine)
            self.assertNotIsInstance(engine, DisruptorEventEngine)

    def test_disruptor_factory(self):
        """Should return DisruptorEventEngine when event.use_disruptor=True."""
        with patch.dict(SETTINGS, {"event.use_disruptor": True}):
            engine = create_engine()
            self.assertIsInstance(engine, DisruptorEventEngine)

    def test_factory_parameters(self):
        """Should correctly propagate buffer_size and wait_strategy from SETTINGS."""
        custom_settings = {
            "event.use_disruptor": True,
            "event.buffer_size": 1024,
            "event.wait_strategy": "busy_spin"
        }
        with patch.dict(SETTINGS, custom_settings):
            engine = create_engine()
            self.assertIsInstance(engine, DisruptorEventEngine)
            self.assertEqual(engine._buffer_size, 1024)
            # wait_strategy is internal to the Rust extension, 
            # but we can verify engine starts/stops correctly.
            engine.start()
            self.assertTrue(engine.is_active())
            engine.stop()

    def test_try_put_parity(self):
        """Verifies that try_put exists and behaves correctly on both engine types."""
        from vnpy.event import Event
        
        # Test Standard Engine
        with patch.dict(SETTINGS, {"event.use_disruptor": False}):
            std_engine = create_engine()
            self.assertTrue(hasattr(std_engine, "try_put"))
            success = std_engine.try_put(Event("test", 1))
            self.assertTrue(success)

        # Test Disruptor Engine
        with patch.dict(SETTINGS, {"event.use_disruptor": True}):
            dis_engine = create_engine()
            self.assertTrue(hasattr(dis_engine, "try_put"))
            success = dis_engine.try_put(Event("test", 1))
            self.assertTrue(success)

if __name__ == "__main__":
    unittest.main()
