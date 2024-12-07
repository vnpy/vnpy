import polars as pl
from typing import Any

from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.bar import *

class MA_BASE(FactorTemplate):
    factor_name = "ma"
    author: str = "EvanHong"

    @property
    def window(self):
        return self.params.get_parameter("window")

    @window.setter
    def window(self, value):
        self.params.set_parameters({"window": value})

    @window.getter
    def window(self):
        return self.params.get_parameter("window")

    def __init_dependencies__(self):
        pass


    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.add_params(
            ["window"])  # add parameters to the attribute "params", so that we can recognize this parameter later

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
