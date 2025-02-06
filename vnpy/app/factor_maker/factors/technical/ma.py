import polars as pl
from typing import Any, Optional, Union, Dict,List,Type

from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.bar import *


class MA_BASE(FactorTemplate):
    factor_name = "ma"
    author: str = "EvanHong"

    # dependencies_factor: List[Type[FactorTemplate]] = [MA, MA]


    def __init_dependencies__(self):
        pass

    def __init__(self, setting, window=None):
        super().__init__(setting, window=window)


    def on_bar(self, bar: BarData) -> None:
        value = 0
        return value

    def on_tick(self, tick: TickData) -> None:
        pass


class MA(MA_BASE):

    def on_bar(self, bar: BarData) -> FactorData:
        value = bar.close_price
        return FactorData(gateway_name="FactorTemplate", symbol=bar.symbol, exchange=bar.exchange,
                          datetime=bar.datetime,
                          value=value, factor_name=self.factor_name, interval=bar.interval)

    def on_tick(self, tick: TickData) -> None:
        pass

    def on_factor(self, factor: FactorData) -> FactorData:
        pass

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], *args, **kwargs) -> Any:
        if isinstance(input_data, dict):
            fast = input_data.get(self.ma_fast.factor_key)
            slow = input_data.get(self.ma_slow.factor_key)
            # compute macd
            macd = fast - slow

        else:
            raise ValueError("The input_data must be a dictionary.")
