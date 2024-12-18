import polars as pl

from vnpy.app.factor_maker.factors.bar.bar_base import BarFactor
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from typing import Optional, Any, Union, Dict


class OPEN(BarFactor):
    factor_name = "open"
    dependencies_factor = []

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        return input_data["ohlcv"]["open"]

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], *args, **kwargs) -> Any:
        if isinstance(input_data, dict):
            return input_data["ohlcv"]["open"]
        return input_data["ohlcv"]["open"]
