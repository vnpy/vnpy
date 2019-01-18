from vnpy.event import EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.ui import QtGui, QtWidgets


class CtaManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        super(CtaManager, self).__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine