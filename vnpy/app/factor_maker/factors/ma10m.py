from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.object import TickData, BarData, Exchange, Interval,FactorData


class MA10_BASE(FactorTemplate):
    lookback_period: int = 10

    author: str = ""
    parameters: list = ['lookback_period']
    variables: list = []
    exchange: Exchange = Exchange.BINANCE
    freq: Interval = Interval.MINUTE
    dependencies: list[str] = []

    def on_bar(self, bar: BarData) -> None:
        value = 0
        return value

    def on_tick(self, tick: TickData) -> None:
        pass


class MA10_F1(FactorTemplate):
    def __init__(self, settings):
        self.factor_name = 'ma10'
        self.symbol = settings['symbol']

        self.vt_symbol = ''

        self.dependencies = ['open', 'volume', 'macd']


class MA10_F2(FactorTemplate):
    def __init__(self, settings):
        self.factor_name = 'ma10'
        self.symbol = settings['symbol']

        self.vt_symbol = ''

        self.dependencies = ['open', 'volume', 'macd']


class MA10_F3(FactorTemplate):
    def __init__(self, settings):
        self.factor_name = 'ma10'
        self.symbol = settings['symbol']

        self.vt_symbol = ''

        self.dependencies = ['open', 'volume', 'macd']
