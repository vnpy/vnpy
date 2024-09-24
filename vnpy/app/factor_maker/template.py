from collections import deque
from abc import abstractmethod
from typing import Optional

from vnpy.app.factor_maker.engine import FactorEngine
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import TickData, BarData, FactorData


class FactorTemplate(object):
    """"""
    VTSYMBOL_TEMPLATE_FACTOR = "factor_{}_{}_{}.{}"  # interval, symbol(ticker), name(factor name), exchange

    author: str = ""
    parameters: list = []
    variables: list = []

    factor_name: str = ""
    freq: Optional[Interval] = None
    symbol: str = ""
    exchange: Exchange = None

    dependencies_factor: list[str] = []
    dependencies_freq: list[Interval] = []
    dependencies_symbol: list[str] = []
    dependencies_exchange: list[Exchange] = []

    status: dict[tuple, bool] = {}  # 用来标识dependencies是否全部ready

    def __init__(self, engine: FactorEngine, setting: dict,
                 ):
        """"""
        self.engine: FactorEngine = engine
        self.setting: dict = setting
        for s in setting.items():
            setattr(self, s[0], s[1])

        self.class_name: str = self.__class__.__name__
        self.inited: bool = False
        self.trading: bool = False

        self.bar_memory: dict[str, deque[BarData]] = {}  # fixme: factor class 不应该保存数据, 所有数据统一存放在engine的memory中

        self.factor_key = self.VTSYMBOL_TEMPLATE_FACTOR.format(self.freq.value, self.symbol, self.factor_name,
                                                               self.exchange.value)

        self.init_status()

    def init_status(self):
        for dep_symbol in self.dependencies_symbol:
            for dep_factor in self.dependencies_factor:
                self.status[(dep_symbol, dep_factor)] = False

    def on_init(self) -> None:
        """"""
        self.inited = True
        msg = f"{self.factor_key}初始化完成"
        self.engine.write_log(msg)

    def on_start(self) -> None:
        """"""
        self.trading = True
        msg = f"{self.factor_key}开始运行"
        self.engine.write_log(msg)
        pass

    def on_stop(self) -> None:
        """"""
        self.trading = False
        msg = f"{self.factor_key}停止运行"
        self.engine.write_log(msg)

    @abstractmethod
    def on_tick(self, tick: TickData) -> None:
        """"""
        pass

    def wrap_data(self, bar: BarData, value: float) -> FactorData:
        """将数据实例化为factor data

        Parameters
        ----------
        bar :
        value :

        Returns
        -------

        """
        factor_data: FactorData = FactorData(
            symbol=bar.symbol,
            exchange=bar.exchange,
            datetime=bar.datetime,
            interval=bar.interval,
            value=value,
            factor_name=self.factor_name,
            gateway_name="factor_template"
        )
        return factor_data

    @abstractmethod
    def on_bar(self, bar: BarData) -> None:
        """"""
        pass

    @abstractmethod
    def on_factor(self, factor: FactorData) -> None:
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
            "factor_name": self.factor_key,
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

    @abstractmethod
    def calculate_polars(self, input_, *args, **kwargs) -> float:
        """具体计算因子值"""
        return 0
