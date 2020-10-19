from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets


from ..engine import (
    RadarEngine,
    APP_NAME,
)


class RadarManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.radar_engine: RadarEngine = main_engine.get_engine(APP_NAME)

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("市场雷达")

        vbox = QtWidgets.QVBoxLayout()
        self.setLayout(vbox)
