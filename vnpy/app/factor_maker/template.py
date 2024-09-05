from vnpy.app.factor_maker.engine import FactorEngine


class FactorTemplate:
    """"""

    def __init__(self, engine: FactorEngine, factor_name: str, vt_symbols: list[str], setting: dict):
        """"""
        self.engine: FactorEngine = engine
        self.factor_name: str = factor_name
        self.vt_symbols: list[str] = vt_symbols
        self.setting: dict = setting

        self.strategy_name: str = self.__class__.__name__
        self.inited: bool = False
        self.trading: bool = False

    def on_init(self) -> None:
        """"""
        pass

    def on_start(self) -> None:
        """"""
        pass

    def on_stop(self) -> None:
        """"""
        pass

    def on_tick(self, tick: TickData) -> None:
        """"""
        pass

    def on_bar(self, bar: BarData) -> None:
        """"""
        pass



    def on_timer(self) -> None:
        """"""
        pass