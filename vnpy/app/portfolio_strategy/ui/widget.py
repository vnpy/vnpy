from typing import Dict

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtCore, QtGui, QtWidgets
from vnpy.trader.ui.widget import (
    MsgCell,
    TimeCell,
    BaseMonitor
)
from ..base import (
    APP_NAME,
    EVENT_PORTFOLIO_LOG,
    EVENT_PORTFOLIO_STRATEGY
)
from ..engine import StrategyEngine


class PortfolioStrategyManager(QtWidgets.QWidget):
    """"""

    signal_log = QtCore.pyqtSignal(Event)
    signal_strategy = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine
        self.strategy_engine: StrategyEngine = main_engine.get_engine(APP_NAME)

        self.managers: Dict[str, StrategyManager] = {}

        self.init_ui()
        self.register_event()
        self.strategy_engine.init_engine()
        self.update_class_combo()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("组合策略")

        # Create widgets
        self.class_combo = QtWidgets.QComboBox()

        add_button = QtWidgets.QPushButton("添加策略")
        add_button.clicked.connect(self.add_strategy)

        init_button = QtWidgets.QPushButton("全部初始化")
        init_button.clicked.connect(self.strategy_engine.init_all_strategies)

        start_button = QtWidgets.QPushButton("全部启动")
        start_button.clicked.connect(self.strategy_engine.start_all_strategies)

        stop_button = QtWidgets.QPushButton("全部停止")
        stop_button.clicked.connect(self.strategy_engine.stop_all_strategies)

        clear_button = QtWidgets.QPushButton("清空日志")
        clear_button.clicked.connect(self.clear_log)

        self.scroll_layout = QtWidgets.QVBoxLayout()
        self.scroll_layout.addStretch()

        scroll_widget = QtWidgets.QWidget()
        scroll_widget.setLayout(self.scroll_layout)

        scroll_area = QtWidgets.QScrollArea()
        scroll_area.setWidgetResizable(True)
        scroll_area.setWidget(scroll_widget)

        self.log_monitor = LogMonitor(self.main_engine, self.event_engine)

        # Set layout
        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(self.class_combo)
        hbox1.addWidget(add_button)
        hbox1.addStretch()
        hbox1.addWidget(init_button)
        hbox1.addWidget(start_button)
        hbox1.addWidget(stop_button)
        hbox1.addWidget(clear_button)

        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(scroll_area)
        hbox2.addWidget(self.log_monitor)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addLayout(hbox2)

        self.setLayout(vbox)

    def update_class_combo(self):
        """"""
        self.class_combo.addItems(
            self.strategy_engine.get_all_strategy_class_names()
        )

    def register_event(self):
        """"""
        self.signal_strategy.connect(self.process_strategy_event)

        self.event_engine.register(
            EVENT_PORTFOLIO_STRATEGY, self.signal_strategy.emit
        )

    def process_strategy_event(self, event):
        """
        Update strategy status onto its monitor.
        """
        data = event.data
        strategy_name = data["strategy_name"]

        if strategy_name in self.managers:
            manager = self.managers[strategy_name]
            manager.update_data(data)
        else:
            manager = StrategyManager(self, self.strategy_engine, data)
            self.scroll_layout.insertWidget(0, manager)
            self.managers[strategy_name] = manager

    def remove_strategy(self, strategy_name):
        """"""
        manager = self.managers.pop(strategy_name)
        manager.deleteLater()

    def add_strategy(self):
        """"""
        class_name = str(self.class_combo.currentText())
        if not class_name:
            return

        parameters = self.strategy_engine.get_strategy_class_parameters(class_name)
        editor = SettingEditor(parameters, class_name=class_name)
        n = editor.exec_()

        if n == editor.Accepted:
            setting = editor.get_setting()
            vt_symbols = setting.pop("vt_symbols").split(",")
            strategy_name = setting.pop("strategy_name")

            self.strategy_engine.add_strategy(
                class_name, strategy_name, vt_symbols, setting
            )

    def clear_log(self):
        """"""
        self.log_monitor.setRowCount(0)

    def show(self):
        """"""
        self.showMaximized()


class StrategyManager(QtWidgets.QFrame):
    """
    Manager for a strategy
    """

    def __init__(
        self,
        strategy_manager: PortfolioStrategyManager,
        strategy_engine: StrategyEngine,
        data: dict
    ):
        """"""
        super().__init__()

        self.strategy_manager = strategy_manager
        self.strategy_engine = strategy_engine

        self.strategy_name = data["strategy_name"]
        self._data = data

        self.init_ui()

    def init_ui(self):
        """"""
        self.setFixedHeight(300)
        self.setFrameShape(self.Box)
        self.setLineWidth(1)

        self.init_button = QtWidgets.QPushButton("初始化")
        self.init_button.clicked.connect(self.init_strategy)

        self.start_button = QtWidgets.QPushButton("启动")
        self.start_button.clicked.connect(self.start_strategy)
        self.start_button.setEnabled(False)

        self.stop_button = QtWidgets.QPushButton("停止")
        self.stop_button.clicked.connect(self.stop_strategy)
        self.stop_button.setEnabled(False)

        self.edit_button = QtWidgets.QPushButton("编辑")
        self.edit_button.clicked.connect(self.edit_strategy)

        self.remove_button = QtWidgets.QPushButton("移除")
        self.remove_button.clicked.connect(self.remove_strategy)

        strategy_name = self._data["strategy_name"]
        class_name = self._data["class_name"]
        author = self._data["author"]

        label_text = (
            f"{strategy_name}  -  ({class_name} by {author})"
        )
        label = QtWidgets.QLabel(label_text)
        label.setAlignment(QtCore.Qt.AlignCenter)

        self.parameters_monitor = DataMonitor(self._data["parameters"])
        self.variables_monitor = DataMonitor(self._data["variables"])

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.init_button)
        hbox.addWidget(self.start_button)
        hbox.addWidget(self.stop_button)
        hbox.addWidget(self.edit_button)
        hbox.addWidget(self.remove_button)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(label)
        vbox.addLayout(hbox)
        vbox.addWidget(self.parameters_monitor)
        vbox.addWidget(self.variables_monitor)
        self.setLayout(vbox)

    def update_data(self, data: dict):
        """"""
        self._data = data

        self.parameters_monitor.update_data(data["parameters"])
        self.variables_monitor.update_data(data["variables"])

        # Update button status
        variables = data["variables"]
        inited = variables["inited"]
        trading = variables["trading"]

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

    def init_strategy(self):
        """"""
        self.strategy_engine.init_strategy(self.strategy_name)

    def start_strategy(self):
        """"""
        self.strategy_engine.start_strategy(self.strategy_name)

    def stop_strategy(self):
        """"""
        self.strategy_engine.stop_strategy(self.strategy_name)

    def edit_strategy(self):
        """"""
        strategy_name = self._data["strategy_name"]

        parameters = self.strategy_engine.get_strategy_parameters(strategy_name)
        editor = SettingEditor(parameters, strategy_name=strategy_name)
        n = editor.exec_()

        if n == editor.Accepted:
            setting = editor.get_setting()
            self.strategy_engine.edit_strategy(strategy_name, setting)

    def remove_strategy(self):
        """"""
        result = self.strategy_engine.remove_strategy(self.strategy_name)

        # Only remove strategy gui manager if it has been removed from engine
        if result:
            self.strategy_manager.remove_strategy(self.strategy_name)


class DataMonitor(QtWidgets.QTableWidget):
    """
    Table monitor for parameters and variables.
    """

    def __init__(self, data: dict):
        """"""
        super(DataMonitor, self).__init__()

        self._data = data
        self.cells = {}

        self.init_ui()

    def init_ui(self):
        """"""
        labels = list(self._data.keys())
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)

        self.setRowCount(1)
        self.verticalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.Stretch
        )
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

        for column, name in enumerate(self._data.keys()):
            value = self._data[name]

            cell = QtWidgets.QTableWidgetItem(str(value))
            cell.setTextAlignment(QtCore.Qt.AlignCenter)

            self.setItem(0, column, cell)
            self.cells[name] = cell

    def update_data(self, data: dict):
        """"""
        for name, value in data.items():
            cell = self.cells[name]
            cell.setText(str(value))


class LogMonitor(BaseMonitor):
    """
    Monitor for log data.
    """

    event_type = EVENT_PORTFOLIO_LOG
    data_key = ""
    sorting = False

    headers = {
        "time": {"display": "时间", "cell": TimeCell, "update": False},
        "msg": {"display": "信息", "cell": MsgCell, "update": False},
    }

    def init_ui(self):
        """
        Stretch last column.
        """
        super(LogMonitor, self).init_ui()

        self.horizontalHeader().setSectionResizeMode(
            1, QtWidgets.QHeaderView.Stretch
        )

    def insert_new_row(self, data):
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
    ):
        """"""
        super(SettingEditor, self).__init__()

        self.parameters = parameters
        self.strategy_name = strategy_name
        self.class_name = class_name

        self.edits = {}

        self.init_ui()

    def init_ui(self):
        """"""
        form = QtWidgets.QFormLayout()

        # Add vt_symbols and name edit if add new strategy
        if self.class_name:
            self.setWindowTitle(f"添加策略：{self.class_name}")
            button_text = "添加"
            parameters = {"strategy_name": "", "vt_symbols": ""}
            parameters.update(self.parameters)
        else:
            self.setWindowTitle(f"参数编辑：{self.strategy_name}")
            button_text = "确定"
            parameters = self.parameters

        for name, value in parameters.items():
            type_ = type(value)

            edit = QtWidgets.QLineEdit(str(value))
            if type_ is int:
                validator = QtGui.QIntValidator()
                edit.setValidator(validator)
            elif type_ is float:
                validator = QtGui.QDoubleValidator()
                edit.setValidator(validator)

            form.addRow(f"{name} {type_}", edit)

            self.edits[name] = (edit, type_)

        button = QtWidgets.QPushButton(button_text)
        button.clicked.connect(self.accept)
        form.addRow(button)

        self.setLayout(form)

    def get_setting(self):
        """"""
        setting = {}

        if self.class_name:
            setting["class_name"] = self.class_name

        for name, tp in self.edits.items():
            edit, type_ = tp
            value_text = edit.text()

            if type_ == bool:
                if value_text == "True":
                    value = True
                else:
                    value = False
            else:
                value = type_(value_text)

            setting[name] = value

        return setting
