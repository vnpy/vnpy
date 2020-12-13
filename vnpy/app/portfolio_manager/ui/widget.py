from vnpy.trader.ui import QtWidgets


from vnpy.trader.engine import MainEngine, EventEngine

from ..engine import APP_NAME, PortfolioEngine


class PortfolioManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine

        self.portfolio_engine: PortfolioEngine = main_engine.get_engine(APP_NAME)

        self.init_ui()
        self.register_event()

    def init_ui(self) -> None:
        """"""
        pass

    def register_event(self) -> None:
        """"""
        pass
