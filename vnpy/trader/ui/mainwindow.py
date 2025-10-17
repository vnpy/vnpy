"""
Implements main window of the trading platform.
"""

from types import ModuleType
import webbrowser
from functools import partial
from importlib import import_module
from typing import TypeVar
from collections.abc import Callable

import vnpy
from vnpy.event import EventEngine

from .qt import QtCore, QtGui, QtWidgets
from .widget import (
    BaseMonitor,
    TickMonitor,
    OrderMonitor,
    TradeMonitor,
    PositionMonitor,
    AccountMonitor,
    LogMonitor,
    ActiveOrderMonitor,
    ConnectDialog,
    ContractManager,
    TradingWidget,
    AboutDialog,
    GlobalDialog
)
from ..engine import MainEngine, BaseApp
from ..utility import get_icon_path, TRADER_DIR
from ..locale import _


WidgetType = TypeVar("WidgetType", bound="QtWidgets.QWidget")


class MainWindow(QtWidgets.QMainWindow):
    """
    Main window of the trading platform.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.window_title: str = _("VeighNa Trader 社区版 - {}   [{}]").format(vnpy.__version__, TRADER_DIR)

        self.widgets: dict[str, QtWidgets.QWidget] = {}
        self.monitors: dict[str, BaseMonitor] = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(self.window_title)

        # 为主窗口添加中央缓冲区，给dock分隔条留出可压缩空间，避免“看起来拖不动”的情况
        self.setCentralWidget(QtWidgets.QWidget())

        self.init_dock()
        self.init_toolbar()
        self.init_menu()
        self.load_window_setting("custom")

    def init_dock(self) -> None:
        """"""
        self.trading_widget, trading_dock = self.create_dock(
            TradingWidget, _("交易"), QtCore.Qt.DockWidgetArea.LeftDockWidgetArea
        )
        tick_widget, tick_dock = self.create_dock(
            TickMonitor, _("行情"), QtCore.Qt.DockWidgetArea.RightDockWidgetArea
        )
        order_widget, order_dock = self.create_dock(
            OrderMonitor, _("委托"), QtCore.Qt.DockWidgetArea.RightDockWidgetArea
        )
        active_widget, active_dock = self.create_dock(
            ActiveOrderMonitor, _("活动"), QtCore.Qt.DockWidgetArea.RightDockWidgetArea
        )
        trade_widget, trade_dock = self.create_dock(
            TradeMonitor, _("成交"), QtCore.Qt.DockWidgetArea.RightDockWidgetArea
        )
        log_widget, log_dock = self.create_dock(
            LogMonitor, _("日志"), QtCore.Qt.DockWidgetArea.BottomDockWidgetArea
        )
        account_widget, account_dock = self.create_dock(
            AccountMonitor, _("资金"), QtCore.Qt.DockWidgetArea.BottomDockWidgetArea
        )
        position_widget, position_dock = self.create_dock(
            PositionMonitor, _("持仓"), QtCore.Qt.DockWidgetArea.BottomDockWidgetArea
        )

        self.tabifyDockWidget(active_dock, order_dock)

        self.save_window_setting("default")

        tick_widget.itemDoubleClicked.connect(self.trading_widget.update_with_cell)
        position_widget.itemDoubleClicked.connect(self.trading_widget.update_with_cell)

        # 一次性设定启动时的友好初始宽度；不限制后续拖动（只影响首次默认布局）
        self.resizeDocks([trading_dock, tick_dock], [320, 720], QtCore.Qt.Horizontal)

    def init_menu(self) -> None:
        """"""
        bar: QtWidgets.QMenuBar = self.menuBar()
        bar.setNativeMenuBar(False)     # for mac and linux

        # System menu
        sys_menu: QtWidgets.QMenu = bar.addMenu(_("系统"))

        gateway_names: list = self.main_engine.get_all_gateway_names()
        for name in gateway_names:
            func: Callable = partial(self.connect_gateway, name)
            self.add_action(
                sys_menu,
                _("连接{}").format(name),
                get_icon_path(__file__, "connect.ico"),
                func
            )

        sys_menu.addSeparator()

        self.add_action(
            sys_menu,
            _("退出"),
            get_icon_path(__file__, "exit.ico"),
            self.close
        )

        # App menu
        app_menu: QtWidgets.QMenu = bar.addMenu(_("功能"))

        all_apps: list[BaseApp] = self.main_engine.get_all_apps()
        for app in all_apps:
            ui_module: ModuleType = import_module(app.app_module + ".ui")
            widget_class: type[QtWidgets.QWidget] = getattr(ui_module, app.widget_name)

            func = partial(self.open_widget, widget_class, app.app_name)

            self.add_action(app_menu, app.display_name, app.icon_name, func, True)

        # Global setting editor
        action: QtGui.QAction = QtGui.QAction(_("配置"), self)
        action.triggered.connect(self.edit_global_setting)
        bar.addAction(action)

        # Help menu
        help_menu: QtWidgets.QMenu = bar.addMenu(_("帮助"))

        self.add_action(
            help_menu,
            _("查询合约"),
            get_icon_path(__file__, "contract.ico"),
            partial(self.open_widget, ContractManager, "contract"),
            True
        )

        self.add_action(
            help_menu,
            _("还原窗口"),
            get_icon_path(__file__, "restore.ico"),
            self.restore_window_setting
        )

        self.add_action(
            help_menu,
            _("测试邮件"),
            get_icon_path(__file__, "email.ico"),
            self.send_test_email
        )

        self.add_action(
            help_menu,
            _("社区论坛"),
            get_icon_path(__file__, "forum.ico"),
            self.open_forum,
            True
        )

        self.add_action(
            help_menu,
            _("关于"),
            get_icon_path(__file__, "about.ico"),
            partial(self.open_widget, AboutDialog, "about"),
        )

    def init_toolbar(self) -> None:
        """"""
        self.toolbar: QtWidgets.QToolBar = QtWidgets.QToolBar(self)
        self.toolbar.setObjectName(_("工具栏"))
        self.toolbar.setFloatable(False)
        self.toolbar.setMovable(False)

        # Set button size
        w: int = 40
        size = QtCore.QSize(w, w)
        self.toolbar.setIconSize(size)

        # Set button spacing
        layout: QtWidgets.QLayout | None = self.toolbar.layout()
        if layout:
            layout.setSpacing(10)

        self.addToolBar(QtCore.Qt.ToolBarArea.LeftToolBarArea, self.toolbar)

    def add_action(
        self,
        menu: QtWidgets.QMenu,
        action_name: str,
        icon_name: str,
        func: Callable,
        toolbar: bool = False
    ) -> None:
        """"""
        icon: QtGui.QIcon = QtGui.QIcon(icon_name)

        action: QtGui.QAction = QtGui.QAction(action_name, self)
        action.triggered.connect(func)
        action.setIcon(icon)

        menu.addAction(action)

        if toolbar:
            self.toolbar.addAction(action)

    def create_dock(
        self,
        widget_class: type[WidgetType],
        name: str,
        area: QtCore.Qt.DockWidgetArea
    ) -> tuple[WidgetType, QtWidgets.QDockWidget]:
        """
        Initialize a dock widget.
        """
        widget: WidgetType = widget_class(self.main_engine, self.event_engine)      # type: ignore
        if isinstance(widget, BaseMonitor):
            self.monitors[name] = widget

        dock: QtWidgets.QDockWidget = QtWidgets.QDockWidget(name)
        dock.setWidget(widget)
        dock.setObjectName(name)
        dock.setFeatures(dock.DockWidgetFeature.DockWidgetFloatable | dock.DockWidgetFeature.DockWidgetMovable)
        self.addDockWidget(area, dock)
        return widget, dock

    def connect_gateway(self, gateway_name: str) -> None:
        """
        Open connect dialog for gateway connection.
        """
        dialog: ConnectDialog = ConnectDialog(self.main_engine, gateway_name)
        dialog.exec()

    def closeEvent(self, event: QtGui.QCloseEvent) -> None:
        """
        Call main engine close function before exit.
        """
        reply = QtWidgets.QMessageBox.question(
            self,
            _("退出"),
            _("确认退出？"),
            QtWidgets.QMessageBox.StandardButton.Yes | QtWidgets.QMessageBox.StandardButton.No,
            QtWidgets.QMessageBox.StandardButton.No,
        )

        if reply == QtWidgets.QMessageBox.StandardButton.Yes:
            for widget in self.widgets.values():
                widget.close()

            for monitor in self.monitors.values():
                monitor.save_setting()

            self.save_window_setting("custom")

            self.main_engine.close()

            event.accept()
        else:
            event.ignore()

    def open_widget(self, widget_class: type[QtWidgets.QWidget], name: str) -> None:
        """
        Open contract manager.
        """
        widget: QtWidgets.QWidget | None = self.widgets.get(name, None)
        if not widget:
            widget = widget_class(self.main_engine, self.event_engine)      # type: ignore
            self.widgets[name] = widget

        if isinstance(widget, QtWidgets.QDialog):
            widget.exec()
        else:
            widget.show()

    def save_window_setting(self, name: str) -> None:
        """
        Save current window size and state by trader path and setting name.
        """
        settings: QtCore.QSettings = QtCore.QSettings(self.window_title, name)
        settings.setValue("state", self.saveState())
        settings.setValue("geometry", self.saveGeometry())

    def load_window_setting(self, name: str) -> None:
        """
        Load previous window size and state by trader path and setting name.
        """
        settings: QtCore.QSettings = QtCore.QSettings(self.window_title, name)
        state = settings.value("state")
        geometry = settings.value("geometry")

        # 恢复顺序：先几何尺寸、后布局状态。避免状态与尺寸互相挤压导致分隔条难以拖动
        if isinstance(state, QtCore.QByteArray):
            if isinstance(geometry, QtCore.QByteArray):
                self.restoreGeometry(geometry)
            self.restoreState(state)

    def restore_window_setting(self) -> None:
        """
        Restore window to default setting.
        """
        self.load_window_setting("default")
        self.showMaximized()

    def send_test_email(self) -> None:
        """
        Sending a test email.
        """
        self.main_engine.send_email("VeighNa Trader", "testing", None)

    def open_forum(self) -> None:
        """
        """
        webbrowser.open("https://www.vnpy.com/forum/")

    def edit_global_setting(self) -> None:
        """
        """
        dialog: GlobalDialog = GlobalDialog()
        dialog.exec()
