import unittest
from unittest.mock import MagicMock, patch
import json
import tempfile
import os
import polars as pl
from datetime import datetime

from tests.app.factor_maker.utils.test_utils import generate_test_bars
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.app.factor_maker.engine import FactorEngine
from vnpy.trader.constant import Interval
from vnpy.app.factor_maker.factors.test_factors import SimpleMAFactor, CompositeFactor
from vnpy.trader.utility import load_json

class TestFactorMaker(unittest.TestCase):
    """
    Test suite for Factor Maker Engine
    """
    
    def setUp(self):
        """Set up test environment"""
        self.event_engine = EventEngine()
        self.main_engine = MainEngine(self.event_engine)
        
        # Mock symbols
        self.main_engine.vt_symbols = ["BTC-USD.TEST", "ETH-USD.TEST"]
        
        # Create temporary setting file
        self.temp_dir = tempfile.mkdtemp()
        self.setting_file = os.path.join(self.temp_dir, "factor_maker_setting.json")
        self.create_test_settings()
        
        # Initialize engine
        self.factor_engine = FactorEngine(self.main_engine, self.event_engine)
        self.factor_engine.setting_filename = self.setting_file

        self.factor_engine.init_engine(fake=True)

                
    def create_test_settings(self):
        """Create test factor settings"""
        settings = {
            "factor_1m_SimpleMA": {  # Match the VTSYMBOL_TEMPLATE format
                "class_name": "SimpleMAFactor",
                "freq": "1m",
                "params": {"window": 10}
            },
            "factor_1m_Composite": {  # Match the VTSYMBOL_TEMPLATE format
                "class_name": "CompositeFactor",
                "freq": "1m",
                "params": {},
                "dependencies_factor": [{
                    "SimpleMA": {
                        "class_name": "SimpleMAFactor",
                        "params": {"window": 10}
                    }
                }]
            }
        }
        with open(self.setting_file, 'w') as f:
            json.dump(settings, f)
    
    def test_basic_initialization(self):
        """Test if engine initializes correctly"""
        self.assertTrue(hasattr(self.factor_engine, 'flattened_factors'))
        self.assertTrue(len(self.factor_engine.flattened_factors) > 0)

    def test_memory_structure(self):
        """Test if memory structures are correctly initialized"""
        self.assertTrue(all(k in self.factor_engine.memory_bar for k in ['open', 'high', 'low', 'close', 'volume']))
        self.assertTrue(len(self.factor_engine.memory_factor) > 0)

    def test_factor_calculation(self):
        """Test basic factor calculation workflow"""
        
        # Generate and process test data
        test_bars = generate_test_bars(self.main_engine.vt_symbols, days=1)
        
        # Process the first bar to initialize
        first_bars = test_bars[0]
        dt = list(first_bars.values())[0].datetime
        self.factor_engine.on_bars(dt, first_bars)
        
        # Verify factors are initialized
        self.assertTrue(len(self.factor_engine.memory_factor) > 0)
        self.assertTrue(any('SimpleMA' in key for key in self.factor_engine.memory_factor.keys()))
        
        # Process remaining bars
        for bar_dict in test_bars[1:]:
            dt = list(bar_dict.values())[0].datetime
            self.factor_engine.on_bars(dt, bar_dict)
        
        # Verify calculations
        for factor_name, factor_data in self.factor_engine.memory_factor.items():
            self.assertIsInstance(factor_data, pl.DataFrame)
            self.assertTrue(len(factor_data) > 0)
            self.assertTrue('datetime' in factor_data.columns)

    def test_dependency_resolution(self):
        """Test factor dependency resolution"""
        
        # Check dependencies are properly resolved
        self.assertTrue(len(self.factor_engine.flattened_factors) >= 2)
        composite = self.factor_engine.flattened_factors.get("factor_1m_Composite@noparams")
        self.assertTrue(len(composite.dependencies_factor) > 0)
        
    def test_error_handling(self):
        """Test error handling and circuit breaker"""
        
        # Simulate calculation errors
        with patch.object(self.factor_engine, 'execute_calculation') as mock_calc:
            mock_calc.side_effect = Exception("Test error")
            
            with self.assertRaises(RuntimeError):
                for _ in range(self.factor_engine.error_threshold + 1):
                    self.factor_engine.on_bars(datetime.now(), {})
                    
    def tearDown(self):
        """Clean up"""
        self.factor_engine.close()
        self.main_engine.close()
        os.remove(self.setting_file)
        os.rmdir(self.temp_dir)

if __name__ == '__main__':
    unittest.main()
