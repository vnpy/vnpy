from typing import Dict, Optional, Union
import polars as pl
from dask.delayed import Delayed

from vnpy.app.factor_maker.template import FactorTemplate

class SimpleMAFactor(FactorTemplate):
    def __init__(self, setting: dict = None, **kwargs):
        super().__init__(setting, **kwargs)
        self.factor_name = "SimpleMA"
        self.window = kwargs.get("window", 10)
        
    def calculate(self, 
                 input_data: Dict[str, Union[pl.DataFrame, Delayed]],
                 memory: Optional[pl.DataFrame] = None) -> pl.DataFrame:
        close = input_data["close"]
        if isinstance(close, Delayed):
            return close  # For testing purposes, just return input
        return close

class CompositeFactor(FactorTemplate):

    dependencies_factor = [
        {
            'SimpleMA': {
                'class_name': 'SimpleMAFactor',
                'params': {'window': 10}
            }
        }
    ]
    
    def __init__(self, setting: dict = None, **kwargs):
        super().__init__(setting, **kwargs)
        self.factor_name = "Composite"

        print(f"composite dependency: -%-{self.dependencies_factor}-%-")
        
    def calculate(self,
                 input_data: Dict[str, Union[pl.DataFrame, Delayed]],
                 memory: Optional[pl.DataFrame] = None) -> pl.DataFrame:
        for factor_key, ma_data in input_data.items():
        #ma_data = input_data['factor_1m_SimpleMA@window_10']
            print(f"Processing {factor_key}")
            # Check if ma_data is a Delayed object
            if isinstance(ma_data, Delayed):
                return ma_data  # For testing purposes, just return input
            return ma_data * 2
