"""
Implements main window of VN Trader.
"""

from functools import partial

from PyQt5 import QtWidgets, QtCore, QtGui

from vnpy.event import EventEngine
from ..engine import MainEngine
from ..utility import get_icon_path
from .widget import (
    TickMonitor,
    OrderMonitor,
    TradeMonitor,
    PositionMonitor,
    AccountMonitor,
    LogMonitor,
    ConnectDialog,
    TradingWidget
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

        self.connect_dialogs = {}
        self.widgets = {}

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("VN Trader")
        self.init_dock()
        self.init_menu()

    def init_dock(self):
        """"""
        trading_widget, trading_dock = self.create_dock(TradingWidget, "交易", QtCore.Qt.LeftDockWidgetArea)
        tick_widget, tick_dock = self.create_dock(TickMonitor, "行情", QtCore.Qt.RightDockWidgetArea)
        order_widget, order_dock = self.create_dock(OrderMonitor, "委托", QtCore.Qt.RightDockWidgetArea)
        trade_widget, trade_dock = self.create_dock(TradeMonitor, "成交", QtCore.Qt.RightDockWidgetArea)
        log_widget, log_dock = self.create_dock(LogMonitor, "日志", QtCore.Qt.BottomDockWidgetArea)
        account_widget, account_dock = self.create_dock(AccountMonitor, "资金", QtCore.Qt.BottomDockWidgetArea)
        position_widget, position_dock = self.create_dock(PositionMonitor, "持仓", QtCore.Qt.BottomDockWidgetArea)

    def init_menu(self):
        """"""
        bar = self.menuBar()

        sys_menu = bar.addMenu("系统")
        app_menu = bar.addMenu("功能")
        help_menu = bar.addMenu("帮助")

        gateway_names = self.main_engine.get_all_gateway_names()
        for name in gateway_names:
            func = partial(self.connect, name)
            icon = QtGui.QIcon(get_icon_path(__file__, "connect.ico"))

            action = QtWidgets.QAction(f"连接{name}", self)
            action.triggered.connect(func)
            action.setIcon(icon)

            sys_menu.addAction(action)

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

    def connect(self, gateway_name: str):
        """
        Open connect dialog for gateway connection.
        """
        dialog = self.connect_dialogs.get(gateway_name, None)
        if not dialog:
            dialog = ConnectDialog(self.main_engine, gateway_name)

        dialog.exec()

    def closeEvent(self, event):
        """
        Call main engine close function before exit.
        """
        reply = QtWidgets.QMessageBox.question(
            self,
            "退出",
            "确认退出？",
            QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No,
            QtWidgets.QMessageBox.No
        )

        if reply == QtWidgets.QMessageBox.Yes:
            for widget in self.widgets.values():
                widget.close()

            self.main_engine.close()

            event.accept()
        else:
            event.ignore()
