from collections import deque

from vnpy.app.factor_maker.engine import FactorEngine
from vnpy.trader.object import TickData, BarData


class FactorTemplate:
    """"""

    max_bar_count: int = 100

    author: str = ""
    parameters: list = ['max_bar_count']
    variables: list = []

    def __init__(self, engine: FactorEngine, factor_name: str, vt_symbols: list[str], setting: dict):
        """"""
        self.engine: FactorEngine = engine
        self.factor_name: str = factor_name
        self.vt_symbols: list[str] = vt_symbols
        self.setting: dict = setting

        self.class_name: str = self.__class__.__name__
        self.inited: bool = False
        self.trading: bool = False

        self.bar_memory: dict[str, deque[BarData]] = {}

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
        if bar.vt_symbol in self.vt_symbols:
            bars = self.bar_memory.get(bar.vt_symbol, deque(maxlen=self.max_bar_count))
            bars.append(bar)

    def on_bars(self, bars: dict[str, BarData]) -> None:
        """"""
        pass



    def on_timer(self) -> None:
        """"""
        pass