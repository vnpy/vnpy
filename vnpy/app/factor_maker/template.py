from collections import deque

from vnpy.app.factor_maker.engine import FactorEngine
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import TickData, BarData


class FactorTemplate:
    """"""
    VTSYMBOL_TEMPLATE_FACTOR = VTSYMBOL_TEMPLATE_FACTOR = "factor_{}_{}_{}.{}"  # interval, symbol(ticker), name(factor name), exchange

    lookback_period: int = 10

    author: str = ""
    vt_symbol: str = "momentum_10min.BINANCE"
    parameters: list = ['lookback_period']
    variables: list = []
    exchange: Exchange = Exchange.BINANCE
    frequency: Interval = Interval.MINUTE
    dependencies: list[str] = []

    def __init__(self, engine: FactorEngine, ticker: str, setting: dict):
        """"""
        self.engine: FactorEngine = engine
        #self.factor_name: str = factor_name
        self.ticker: str = ticker
        self.setting: dict = setting

        self.class_name: str = self.__class__.__name__
        self.inited: bool = False
        self.trading: bool = False

        self.bar_memory: dict[str, deque[BarData]] = {}

        self.factor_name = self.VTSYMBOL_TEMPLATE_FACTOR.format(self.frequency.value, self.ticker, self.factor_name,
                                                                self.exchange.value)

    def on_init(self) -> None:
        """"""
        self.inited = True
        msg = f"{self.factor_name}初始化完成"
        self.engine.write_log(msg)

    def on_start(self) -> None:
        """"""
        self.trading = True
        msg = f"{self.factor_name}开始运行"
        self.engine.write_log(msg)
        pass

    def on_stop(self) -> None:
        """"""
        self.trading = False
        msg = f"{self.factor_name}停止运行"
        self.engine.write_log(msg)

    def on_tick(self, tick: TickData) -> None:
        """"""
        pass

    def on_bar(self, bar: BarData) -> None:
        """"""
        pass

    def on_bars(self, bars: dict[str, BarData]) -> None:
        """"""
        pass

    def on_timer(self) -> None:
        """"""
        pass

    def get_parameters(self):
        factor_parameters: dict = {}
        for name in self.parameters:
            factor_parameters[name] = getattr(self, name)
        return factor_parameters

    @classmethod
    def get_class_parameters(cls) -> dict:
        """查取策略默认参数"""
        class_parameters: dict = {}
        for name in cls.parameters:
            class_parameters[name] = getattr(cls, name)
        return class_parameters

    def update_setting(self, setting):
        """设置策略参数"""
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

    def get_data(self) -> dict:
        """查询策略状态数据"""
        factor_data: dict = {
            "factor_name": self.factor_name,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables()
        }
        return factor_data

    def get_variables(self) -> dict:
        """查询策略变量"""
        factor_variables: dict = {}
        for name in self.variables:
            if name in ["inited", "trading"]:
                continue
            factor_variables[name] = getattr(self, name)
        return factor_variables
