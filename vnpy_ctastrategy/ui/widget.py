from vnpy.event import Event, EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtCore, QtGui, QtWidgets
from vnpy.trader.ui.widget import (
    BaseCell,
    EnumCell,
    MsgCell,
    TimeCell,
    BaseMonitor
)
from ..base import (
    APP_NAME,
    EVENT_CTA_LOG,
    EVENT_CTA_STOPORDER,
    EVENT_CTA_STRATEGY
)
from ..engine import CtaEngine
from ..locale import _
from .rollover import RolloverTool


class CtaManager(QtWidgets.QWidget):
    """"""

    signal_log: QtCore.Signal = QtCore.Signal(Event)
    signal_strategy: QtCore.Signal = QtCore.Signal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine
        self.cta_engine: CtaEngine = main_engine.get_engine(APP_NAME)  # type: ignore

        self.managers: dict[str, StrategyManager] = {}

        self.init_ui()
        self.register_event()
        self.cta_engine.init_engine()
        self.update_class_combo()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(_("CTA策略"))

        # Create widgets
        self.class_combo: QtWidgets.QComboBox = QtWidgets.QComboBox()

        add_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("添加策略"))
        add_button.clicked.connect(self.add_strategy)

        init_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("全部初始化"))
        init_button.clicked.connect(self.cta_engine.init_all_strategies)

        start_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("全部启动"))
        start_button.clicked.connect(self.cta_engine.start_all_strategies)

        stop_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("全部停止"))
        stop_button.clicked.connect(self.cta_engine.stop_all_strategies)

        clear_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("清空日志"))
        clear_button.clicked.connect(self.clear_log)

        roll_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("移仓助手"))
        roll_button.clicked.connect(self.roll)

        self.scroll_layout: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        self.scroll_layout.addStretch()

        scroll_widget: QtWidgets.QWidget = QtWidgets.QWidget()
        scroll_widget.setLayout(self.scroll_layout)

        self.scroll_area: QtWidgets.QScrollArea = QtWidgets.QScrollArea()
        self.scroll_area.setWidgetResizable(True)
        self.scroll_area.setWidget(scroll_widget)

        self.log_monitor: LogMonitor = LogMonitor(self.main_engine, self.event_engine)

        self.stop_order_monitor: StopOrderMonitor = StopOrderMonitor(
            self.main_engine, self.event_engine
        )

        self.strategy_combo = QtWidgets.QComboBox()
        self.strategy_combo.setMinimumWidth(200)
        find_button = QtWidgets.QPushButton(_("查找"))
        find_button.clicked.connect(self.find_strategy)

        # Set layout
        hbox1: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox1.addWidget(self.class_combo)
        hbox1.addWidget(add_button)
        hbox1.addStretch()
        hbox1.addWidget(self.strategy_combo)
        hbox1.addWidget(find_button)
        hbox1.addStretch()
        hbox1.addWidget(init_button)
        hbox1.addWidget(start_button)
        hbox1.addWidget(stop_button)
        hbox1.addWidget(clear_button)
        hbox1.addWidget(roll_button)

        grid: QtWidgets.QGridLayout = QtWidgets.QGridLayout()
        grid.addWidget(self.scroll_area, 0, 0, 2, 1)
        grid.addWidget(self.stop_order_monitor, 0, 1)
        grid.addWidget(self.log_monitor, 1, 1)

        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addLayout(grid)

        self.setLayout(vbox)

    def update_class_combo(self) -> None:
        """"""
        names = self.cta_engine.get_all_strategy_class_names()
        names.sort()
        self.class_combo.addItems(names)

    def update_strategy_combo(self) -> None:
        """"""
        names = list(self.managers.keys())
        names.sort()

        self.strategy_combo.clear()
        self.strategy_combo.addItems(names)

    def register_event(self) -> None:
        """"""
        self.signal_strategy.connect(self.process_strategy_event)

        self.event_engine.register(
            EVENT_CTA_STRATEGY, self.signal_strategy.emit
        )

    def process_strategy_event(self, event: Event) -> None:
        """
        Update strategy status onto its monitor.
        """
        data = event.data
        strategy_name: str = data["strategy_name"]

        if strategy_name in self.managers:
            manager: StrategyManager = self.managers[strategy_name]
            manager.update_data(data)
        else:
            manager = StrategyManager(self, self.cta_engine, data)
            self.scroll_layout.insertWidget(0, manager)
            self.managers[strategy_name] = manager

            self.update_strategy_combo()

    def remove_strategy(self, strategy_name: str) -> None:
        """"""
        manager: StrategyManager = self.managers.pop(strategy_name)
        manager.deleteLater()

        self.update_strategy_combo()

    def add_strategy(self) -> None:
        """"""
        class_name: str = str(self.class_combo.currentText())
        if not class_name:
            return

        parameters: dict = self.cta_engine.get_strategy_class_parameters(class_name)
        editor: SettingEditor = SettingEditor(parameters, class_name=class_name)
        n: int = editor.exec_()

        if n == editor.DialogCode.Accepted:
            setting: dict = editor.get_setting()
            vt_symbol: str = setting.pop("vt_symbol")
            strategy_name: str = setting.pop("strategy_name")

            self.cta_engine.add_strategy(
                class_name, strategy_name, vt_symbol, setting
            )

    def find_strategy(self) -> None:
        """"""
        strategy_name = self.strategy_combo.currentText()
        if strategy_name:
            manager = self.managers[strategy_name]
            self.scroll_area.ensureWidgetVisible(manager)

    def clear_log(self) -> None:
        """"""
        self.log_monitor.setRowCount(0)

    def show(self) -> None:
        """"""
        self.showMaximized()

    def roll(self) -> None:
        """"""
        dialog: RolloverTool = RolloverTool(self)
        dialog.exec_()


class StrategyManager(QtWidgets.QFrame):
    """
    Manager for a strategy
    """

    def __init__(
        self, cta_manager: CtaManager, cta_engine: CtaEngine, data: dict
    ) -> None:
        """"""
        super().__init__()

        self.cta_manager: CtaManager = cta_manager
        self.cta_engine: CtaEngine = cta_engine

        self.strategy_name: str = data["strategy_name"]
        self._data: dict = data

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setFixedHeight(300)
        self.setFrameShape(self.Shape.Box)
        self.setLineWidth(1)

        self.init_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("初始化"))
        self.init_button.clicked.connect(self.init_strategy)

        self.start_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("启动"))
        self.start_button.clicked.connect(self.start_strategy)
        self.start_button.setEnabled(False)

        self.stop_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("停止"))
        self.stop_button.clicked.connect(self.stop_strategy)
        self.stop_button.setEnabled(False)

        self.edit_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("编辑"))
        self.edit_button.clicked.connect(self.edit_strategy)

        self.remove_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("移除"))
        self.remove_button.clicked.connect(self.remove_strategy)

        strategy_name: str = self._data["strategy_name"]
        vt_symbol: str = self._data["vt_symbol"]
        class_name: str = self._data["class_name"]
        author: str = self._data["author"]

        label_text: str = (
            f"{strategy_name}  -  {vt_symbol}  ({class_name} by {author})"
        )
        label: QtWidgets.QLabel = QtWidgets.QLabel(label_text)
        label.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

        self.parameters_monitor: DataMonitor = DataMonitor(self._data["parameters"])
        self.variables_monitor: DataMonitor = DataMonitor(self._data["variables"])

        hbox: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.init_button)
        hbox.addWidget(self.start_button)
        hbox.addWidget(self.stop_button)
        hbox.addWidget(self.edit_button)
        hbox.addWidget(self.remove_button)

        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addWidget(label)
        vbox.addLayout(hbox)
        vbox.addWidget(self.parameters_monitor)
        vbox.addWidget(self.variables_monitor)
        self.setLayout(vbox)

    def update_data(self, data: dict) -> None:
        """"""
        self._data = data

        self.parameters_monitor.update_data(data["parameters"])
        self.variables_monitor.update_data(data["variables"])

        # Update button status
        variables: dict = data["variables"]
        inited: bool = variables["inited"]
        trading: bool = variables["trading"]

        if not inited:
            return
        self.init_button.setEnabled(False)

        if trading:
            self.start_button.setEnabled(False)
            self.stop_button.setEnabled(True)
            self.edit_button.setEnabled(False)
            self.remove_button.setEnabled(False)
        else:
            self.start_button.setEnabled(True)
            self.stop_button.setEnabled(False)
            self.edit_button.setEnabled(True)
            self.remove_button.setEnabled(True)

    def init_strategy(self) -> None:
        """"""
        self.cta_engine.init_strategy(self.strategy_name)

    def start_strategy(self) -> None:
        """"""
        self.cta_engine.start_strategy(self.strategy_name)

    def stop_strategy(self) -> None:
        """"""
        self.cta_engine.stop_strategy(self.strategy_name)

    def edit_strategy(self) -> None:
        """"""
        strategy_name: str = self._data["strategy_name"]

        parameters: dict = self.cta_engine.get_strategy_parameters(strategy_name)
        editor: SettingEditor = SettingEditor(parameters, strategy_name=strategy_name)
        n: int = editor.exec_()

        if n == editor.DialogCode.Accepted:
            setting: dict = editor.get_setting()
            self.cta_engine.edit_strategy(strategy_name, setting)

    def remove_strategy(self) -> None:
        """"""
        result: bool = self.cta_engine.remove_strategy(self.strategy_name)

        # Only remove strategy gui manager if it has been removed from engine
        if result:
            self.cta_manager.remove_strategy(self.strategy_name)


class DataMonitor(QtWidgets.QTableWidget):
    """
    Table monitor for parameters and variables.
    """

    def __init__(self, data: dict) -> None:
        """"""
        super().__init__()

        self._data: dict = data
        self.cells: dict = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        labels: list = list(self._data.keys())
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)

        self.setRowCount(1)
        self.verticalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.ResizeMode.Stretch
        )
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.EditTrigger.NoEditTriggers)

        for column, name in enumerate(self._data.keys()):
            value = self._data[name]

            cell: QtWidgets.QTableWidgetItem = QtWidgets.QTableWidgetItem(str(value))
            cell.setTextAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

            self.setItem(0, column, cell)
            self.cells[name] = cell

    def update_data(self, data: dict) -> None:
        """"""
        for name, value in data.items():
            cell: QtWidgets.QTableWidgetItem = self.cells[name]
            cell.setText(str(value))


class StopOrderMonitor(BaseMonitor):
    """
    Monitor for local stop order.
    """

    event_type: str = EVENT_CTA_STOPORDER
    data_key: str = "stop_orderid"
    sorting: bool = True

    headers: dict = {
        "stop_orderid": {
            "display": _("停止委托号"),
            "cell": BaseCell,
            "update": False,
        },
        "vt_orderids": {"display": _("限价委托号"), "cell": BaseCell, "update": True},
        "vt_symbol": {"display": _("本地代码"), "cell": BaseCell, "update": False},
        "direction": {"display": _("方向"), "cell": EnumCell, "update": False},
        "offset": {"display": _("开平"), "cell": EnumCell, "update": False},
        "price": {"display": _("价格"), "cell": BaseCell, "update": False},
        "volume": {"display": _("数量"), "cell": BaseCell, "update": False},
        "status": {"display": _("状态"), "cell": EnumCell, "update": True},
        "datetime": {"display": _("时间"), "cell": TimeCell, "update": False},
        "lock": {"display": _("锁仓"), "cell": BaseCell, "update": False},
        "net": {"display": _("净仓"), "cell": BaseCell, "update": False},
        "strategy_name": {"display": _("策略名"), "cell": BaseCell, "update": False},
    }

    def __del__(self) -> None:
        """"""
        pass


class LogMonitor(BaseMonitor):
    """
    Monitor for log data.
    """

    event_type: str = EVENT_CTA_LOG
    data_key: str = ""
    sorting: bool = False

    headers: dict = {
        "time": {"display": _("时间"), "cell": TimeCell, "update": False},
        "msg": {"display": _("信息"), "cell": MsgCell, "update": False},
    }

    def init_ui(self) -> None:
        """
        Stretch last column.
        """
        super().init_ui()

        self.horizontalHeader().setSectionResizeMode(
            1, QtWidgets.QHeaderView.ResizeMode.Stretch
        )

    def insert_new_row(self, data: dict) -> None:
        """
        Insert a new row at the top of table.
        """
        super().insert_new_row(data)
        self.resizeRowToContents(0)


class SettingEditor(QtWidgets.QDialog):
    """
    For creating new strategy and editing strategy parameters.
    """

    def __init__(
        self, parameters: dict, strategy_name: str = "", class_name: str = ""
    ) -> None:
        """"""
        super().__init__()

        self.parameters: dict = parameters
        self.strategy_name: str = strategy_name
        self.class_name: str = class_name

        self.edits: dict = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        form: QtWidgets.QFormLayout = QtWidgets.QFormLayout()

        # Add vt_symbol and name edit if add new strategy
        if self.class_name:
            self.setWindowTitle(_("添加策略：{}").format(self.class_name))
            button_text: str = _("添加")
            parameters: dict = {"strategy_name": "", "vt_symbol": ""}
            parameters.update(self.parameters)
        else:
            self.setWindowTitle(_("参数编辑：{}").format(self.strategy_name))
            button_text = _("确定")
            parameters = self.parameters

        for name, value in parameters.items():
            type_: type = type(value)

            edit: QtWidgets.QLineEdit = QtWidgets.QLineEdit(str(value))
            if type_ is int:
                int_validator: QtGui.QIntValidator = QtGui.QIntValidator()
                edit.setValidator(int_validator)
            elif type_ is float:
                double_validator: QtGui.QDoubleValidator = QtGui.QDoubleValidator()
                edit.setValidator(double_validator)

            form.addRow(f"{name} {type_}", edit)

            self.edits[name] = (edit, type_)

        button: QtWidgets.QPushButton = QtWidgets.QPushButton(button_text)
        button.clicked.connect(self.accept)
        form.addRow(button)

        widget: QtWidgets.QWidget = QtWidgets.QWidget()
        widget.setLayout(form)

        scroll: QtWidgets.QScrollArea = QtWidgets.QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(widget)

        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addWidget(scroll)
        self.setLayout(vbox)

    def get_setting(self) -> dict:
        """"""
        setting: dict = {}

        if self.class_name:
            setting["class_name"] = self.class_name

        for name, tp in self.edits.items():
            edit, type_ = tp
            value_text = edit.text()

            if type_ is bool:
                if value_text == "True":
                    value = True
                else:
                    value = False
            else:
                value = type_(value_text)

            setting[name] = value

        return setting
