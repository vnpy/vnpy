from typing import Optional

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from vnpy.app.factor_maker.factors.bar import OPEN_BASE, HIGH_BASE, LOW_BASE


class FAIR_PRICE_BASE(FactorTemplate):
    factor_name = "fair_price"

    author: str = ""
    variables: list = []
    exchange: Exchange = Exchange.BINANCE
    freq: Interval = Interval.MINUTE

    dependencies_factor: list[str] = [OPEN_BASE.factor_name, HIGH_BASE.factor_name, LOW_BASE.factor_name]


    parameters: list = []

    def __init__(self, engine, symbol, setting,
                 exchange: Optional[Exchange] = Exchange.BINANCE,
                 freq: Optional[Interval] = Interval.MINUTE):
        super().__init__(engine, symbol, setting, exchange, freq)

    def on_bar(self, bar: BarData) -> FactorData:
        pass

    def on_tick(self, tick: TickData) -> None:
        pass

    def on_factor(self, factor: FactorData) -> None:
        open_factor = self.engine.get_factor(factor.symbol, OPEN_BASE.factor_name)
        high_factor = self.engine.get_factor(factor.symbol, HIGH_BASE.factor_name)
        low_factor = self.engine.get_factor(factor.symbol, LOW_BASE.factor_name)

        value = (open_factor.value + high_factor.value + low_factor.value) / 3
        factor = FactorData(gateway_name="FactorTemplate", symbol=factor.symbol, exchange=factor.exchange,
                            datetime=factor.datetime,
                            value=value, factor_name=self.factor_name, interval=factor.interval)
        self.engine.put_factor(factor)
        pass
