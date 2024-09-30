from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from typing import Optional


class VOLUME_BASE(FactorTemplate):
    factor_name = "VOLUME"

    def on_bar(self, bar: BarData) -> FactorData:
        pass

    def on_tick(self, tick: TickData) -> None:
        pass

    def on_factor(self, factor: FactorData) -> FactorData:
        pass


class VOLUME(VOLUME_BASE):
    factor_name = "volume"

    def on_bar(self, bar: BarData) -> FactorData:
        value = bar.volume
        return FactorData(gateway_name="FactorTemplate", symbol=bar.symbol, exchange=bar.exchange,
                          datetime=bar.datetime,
                          value=value, factor_name=self.factor_name, interval=bar.interval)

    def on_tick(self, tick: TickData) -> None:
        pass

    def on_factor(self, factor: FactorData) -> FactorData:
        pass
