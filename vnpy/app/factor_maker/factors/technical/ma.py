import polars as pl
from typing import Any

from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.bar import *


class MA_BASE(FactorTemplate):
    factor_name = "ma"
    author: str = "EvanHong"

    def __init_dependencies__(self):
        pass

    def __init__(self, setting, window=None):
        super().__init__(setting, window=window)


class MA(MA_BASE):
    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass
