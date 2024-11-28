#  Copyright (c) 2024. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
#  Morbi non lorem porttitor neque feugiat blandit. Ut vitae ipsum eget quam lacinia accumsan.
#  Etiam sed turpis ac ipsum condimentum fringilla. Maecenas magna.
#  Proin dapibus sapien vel ante. Aliquam erat volutpat. Pellentesque sagittis ligula eget metus.
#  Vestibulum commodo. Ut rhoncus gravida arcu.

import polars as pl
from typing import Any

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData


class MA_BASE(FactorTemplate):
    factor_name = "ma"
    author: str = ""

    @property
    def window(self):
        return self.params.get_parameter("window")

    @window.setter
    def window(self, value):
        self.params.set_parameters({"window": value})

    @window.getter
    def window(self):
        return self.params.get_parameter("window")

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
