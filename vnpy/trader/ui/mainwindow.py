from PyQt5 import QtWidgets, QtCore

from vnpy.event import EventEngine
from ..engine import MainEngine
from .widget import (
    TickMonitor,
    OrderMonitor,
    TradeMonitor,
    PositionMonitor,
    AccountMonitor,
    LogMonitor
)


class MainWindow(QtWidgets.QMainWindow):
    """
    Main window of VN Trader.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(MainWindow, self).__init__()
        self.main_engine = main_engine
        self.event_engine = event_engine

        self.widgets = {}

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("VN Trader")
        self.init_dock()
        self.init_menu()

    def init_dock(self):
        """"""
        tick_widget, tick_dock = self.create_dock(TickMonitor, "行情", QtCore.Qt.RightDockWidgetArea)
        order_widget, order_dock = self.create_dock(OrderMonitor, "委托", QtCore.Qt.RightDockWidgetArea)
        trade_widget, trade_dock = self.create_dock(TradeMonitor, "成交", QtCore.Qt.RightDockWidgetArea)
        log_widget, log_dock = self.create_dock(LogMonitor, "日志", QtCore.Qt.BottomDockWidgetArea)
        account_widget, account_dock = self.create_dock(AccountMonitor, "资金", QtCore.Qt.BottomDockWidgetArea)
        position_widget, position_dock = self.create_dock(PositionMonitor, "持仓", QtCore.Qt.BottomDockWidgetArea)

    def init_menu(self):
        """"""
        pass

    def create_dock(
            self,
            widget_class: QtWidgets.QWidget,
            name: str,
            area: int
    ):
        """
        Initialize a dock widget.
        """
        widget = widget_class(self.main_engine, self.event_engine)

        dock = QtWidgets.QDockWidget(name)
        dock.setWidget(widget)
        dock.setObjectName(name)
        dock.setFeatures(dock.DockWidgetFloatable | dock.DockWidgetMovable)
        self.addDockWidget(area, dock)
        return widget, dock