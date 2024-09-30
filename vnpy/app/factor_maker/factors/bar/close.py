from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData


class CLOSE_BASE(FactorTemplate):
    factor_name = "close"

    author: str = ""
    variables: list = []
    exchange: Exchange = Exchange.BINANCE
    freq: Interval = Interval.MINUTE

    parameters: list = []

    def on_bar(self, bar: BarData) -> FactorData:
        value = bar.close_price
        return FactorData(gateway_name="FactorTemplate", symbol=bar.symbol, exchange=bar.exchange,
                          datetime=bar.datetime,
                          value=value, factor_name=self.factor_name, interval=bar.interval)

    def on_tick(self, tick: TickData) -> None:
        pass

class CLOSE(CLOSE_BASE):
    factor_name = "close"

    def on_bar(self, bar: BarData) -> FactorData:
        value = bar.close_price
        return FactorData(gateway_name="FactorTemplate", symbol=bar.symbol, exchange=bar.exchange,
                          datetime=bar.datetime,
                          value=value, factor_name=self.factor_name, interval=bar.interval)

    def on_tick(self, tick: TickData) -> None:
        pass

    def on_factor(self, factor: FactorData) -> FactorData:
        pass