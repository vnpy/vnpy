import polars as pl

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from typing import Optional, Any


class OPEN_BASE(FactorTemplate):
    factor_name = "open"


    def on_bar(self, bar: BarData) -> FactorData:
        pass

    def on_tick(self, tick: TickData) -> None:
        pass

    def on_factor(self, factor: FactorData) -> FactorData:
        pass


class OPEN(OPEN_BASE):


    factor_name = "open"



    def on_bar(self, bar: BarData) -> FactorData:
        value = bar.open_price
        return FactorData(gateway_name="FactorTemplate", symbol=bar.symbol, exchange=bar.exchange,
                          datetime=bar.datetime,
                          value=value, factor_name=self.factor_name, interval=bar.interval)

    def on_tick(self, tick: TickData) -> None:
        pass

    def on_factor(self, factor: FactorData) -> FactorData:
        pass

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass