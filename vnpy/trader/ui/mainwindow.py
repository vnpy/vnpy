from PyQt5 import QtWidgets

from vnpy.event import EventEngine
from ..engine import MainEngine


class MainWindow(QtWidgets.QMainWindow):
    """
    Main window of VN Trader.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(MainWindow, self).__init__()
        self.main_engine = main_engine
        self.event_engine = event_engine

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("VN Trader")

    def register_event(self):
        """"""
        pass