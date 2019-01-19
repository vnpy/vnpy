from typing import Any

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.ui import QtGui, QtWidgets, QtCore
from vnpy.trader.ui.widget import BaseMonitor, BaseCell, EnumCell, DirectionCell

from ..engine import CtaEngine
from ..base import APP_NAME, EVENT_CTA_LOG, EVENT_CTA_STOPORDER, EVENT_CTA_STRATEGY


class CtaManager(QtWidgets.QWidget):
    """"""
    signal_log = QtCore.pyqtSignal(Event)
    signal_strategy = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        super(CtaManager, self).__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.cta_engine = main_engine.get_engine(APP_NAME)

        self.cta_engine.init_engine()

        self.managers = {}

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        self.setWindowTitle("CTA策略")

        # Create widgets
        self.class_combo = QtWidgets.QComboBox()
        self.class_combo.addItems(
            self.cta_engine.get_all_strategy_class_names()
        )

        add_button = QtWidgets.QPushButton("添加策略")
        add_button.clicked.connect(self.add_strategy)

        init_button = QtWidgets.QPushButton("全部初始化")
        init_button.clicked.connect(self.cta_engine.init_all_strategies)

        start_button = QtWidgets.QPushButton("全部启动")
        start_button.clicked.connect(self.cta_engine.start_all_strategies)

        stop_button = QtWidgets.QPushButton("全部停止")
        stop_button.clicked.connect(self.cta_engine.stop_all_strategies)

        self.scroll_layout = QtWidgets.QVBoxLayout()

        scroll_widget = QtWidgets.QWidget()
        scroll_widget.setLayout(self.scroll_layout)

        scroll_area = QtWidgets.QScrollArea()
        scroll_area.setWidgetResizable(True)
        scroll_area.setWidget(scroll_widget)

        bottom_height = 300

        self.log_monitor = QtWidgets.QTextEdit()
        self.log_monitor.setReadOnly(True)
        self.log_monitor.setMaximumHeight(bottom_height)

        self.stop_order_monitor = StopOrderMonitor(
            self.main_engine,
            self.event_engine
        )
        self.stop_order_monitor.setMaximumHeight(bottom_height)

        # Set layout
        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(self.class_combo)
        hbox1.addWidget(add_button)
        hbox1.addStretch()
        hbox1.addWidget(init_button)
        hbox1.addWidget(start_button)
        hbox1.addWidget(stop_button)

        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(self.log_monitor)
        hbox2.addWidget(self.stop_order_monitor)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addWidget(scroll_area)
        vbox.addLayout(hbox2)

        self.setLayout(vbox)

    def register_event(self):
        """"""
        self.signal_log.connect(self.process_log_event)
        self.signal_strategy.connect(self.process_strategy_event)

        self.event_engine.register(EVENT_CTA_LOG, self.signal_log.emit)
        self.event_engine.register(
            EVENT_CTA_STRATEGY,
            self.signal_strategy.emit
        )

    def process_log_event(self, event):
        """
        Update log output.
        """
        log = event.data
        time = log.time.strftime("%H:%M:S")
        msg = f"{time}:\t{log.msg}"
        self.log_monitor.append(msg)

    def process_strategy_event(self, event):
        """
        Update strategy status onto its monitor.
        """
        data = event.data
        name = data["name"]

        if name in self.managers:
            manager = self.managers[name]
            manager.update_data(data)
        else:
            manager = StrategyManager(self, self.cta_engine, data)
            self.scroll_layout.insertWidget(0, manager)

    def remove_strategy(self, name):
        """"""
        manager = self.managers[name]
        manager.deleteLater()

    def add_strategy(self):
        """"""
        class_name = str(self.class_combo.currentText())
        if not class_name:
            return

        parameters = self.cta_engine.get_strategy_class_parameters(class_name)

        editor = SettingEditor(parameters, class_name=class_name)
        n = editor.exec_()

        if n == editor.Accepted:
            setting = editor.get_setting()
            self.cta_engine.add_strategy(setting)

    def show(self):
        """"""
        self.showMaximized()


class StrategyManager(QtWidgets.QWidget):
    """
    Manager for a strategy
    """

    def __init__(
            self,
            cta_manager: CtaManager,
            cta_engine: CtaEngine,
            data: dict
    ):
        """"""
        self.cta_manager = cta_manager
        self.cta_engine = cta_engine

        self.name = data["name"]
        self._data = data

        self.init_ui()

    def init_ui(self):
        """"""
        init_button = QtWidgets.QPushButton("初始化")
        init_button.clicked.connect(self.init_strategy)

        start_button = QtWidgets.QPushButton("启动")
        start_button.clicked.connect(self.start_strategy)

        stop_button = QtWidgets.QPushButton("停止")
        stop_button.clicked.connect(self.stop_strategy)

        edit_button = QtWidgets.QPushButton("编辑")
        edit_button.clicked.connect(self.edit_strategy)

        remove_button = QtWidgets.QPushButton("移除")
        remove_button.clicked.connect(self.remove_strategy)

        self.name_label = QtWidgets.QLabel(f"策略名:{self._data['name']}")
        self.class_label = QtWidgets.QLabel(f"策略类:{self._data['class_name']}")
        self.symbol_label = QtWidgets.QLabel(f"代码:{self._data['vt_symbol']}")
        self.author_label = QtWidgets.QLabel(f"作者:{self._data['author']}")
        self.inited_label = QtWidgets.QLabel(f"inited:{self._data['inited']}")
        self.trading_label = QtWidgets.QLabel(
            f"trading:{self._data['trading']}"
        )
        self.pos_label = QtWidgets.QLabel(f"pos:{self._data['pos']}")

        self.parameters_monitor = DataMonitor(self._data["parameters"])
        self.variables_monitor = DataMonitor(self._data["variables"])

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.name_label)
        hbox.addWidget(self.class_label)
        hbox.addWidget(self.symbol_label)
        hbox.addWidget(self.author_label)
        hbox.addWidget(self.inited_label)
        hbox.addWidget(self.trading_label)
        hbox.addWidget(self.pos_label)
        hbox.addWidget(init_button)
        hbox.addWidget(start_button)
        hbox.addWidget(stop_button)
        hbox.addWidget(edit_button)
        hbox.addWidget(remove_button)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.parameters_monitor)
        vbox.addWidget(self.variables_monitor)
        self.setLayout(vbox)

    def update_data(self, data: dict):
        """"""
        self._data = data

        self.inited_label.setText(f"inited:{data['inited']}")
        self.trading_label.setText(f"trading:{data['trading']}")
        self.pos_label.setText(f"pos:{data['pos']}")

        self.parameters_monitor.update_data(data["parameters"])
        self.variables_monitor.update_data(data["variables"])

    def init_strategy(self):
        """"""
        self.cta_engine.init_strategy(self.name)

    def start_strategy(self):
        """"""
        self.cta_engine.start_strategy(self.name)

    def stop_strategy(self):
        """"""
        self.cta_engine.stop_strategy(self.name)

    def edit_strategy(self):
        """"""
        pass

    def remove_strategy(self):
        """"""
        self.cta_engine.remove_strategy(self.name)
        self.cta_manager.remove_strategy(self.name)


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
        self.setColumnCount(labels)
        self.setHorizontalHeaderLabels(labels)

        self.setRowCount(1)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

        for column, name in enumerate(self._data.items()):
            value = self._data[name]
            cell = QtWidgets.QTableWidgetItem(str(value))
            self.setItem(0, column, cell)
            self.cells[name] = cell

    def update_data(self, data: dict):
        """"""
        for name, value in data.items():
            cell = self.cells[name]
            cell.setText(str(value))


class StrategyCell(BaseCell):
    """
    Cell used for showing strategy name.
    """

    def __init__(self, content: str, data: Any):
        """"""
        super(StrategyCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any):
        """
        Set text using enum.constant.value.
        """
        if content:
            super(StrategyCell, self).set_content(content.name, data)


class StopOrderMonitor(BaseMonitor):
    """
    Monitor for local stop order.
    """
    event_type = EVENT_CTA_STOPORDER
    data_key = "stop_orderid"
    sorting = True

    headers = {
        "stop_orderid": {
            "display": "停止委托号",
            "cell": BaseCell,
            "update": False
        },
        "vt_orderid": {
            "display": "限价委托号",
            "cell": BaseCell,
            "update": True
        },
        "vt_symbol": {
            "display": "代码",
            "cell": BaseCell,
            "update": False
        },
        "order_type": {
            "display": "类型",
            "cell": EnumCell,
            "update": False
        },
        "price": {
            "display": "价格",
            "cell": BaseCell,
            "update": False
        },
        "volume": {
            "display": "数量",
            "cell": BaseCell,
            "update": True
        },
        "status": {
            "display": "状态",
            "cell": EnumCell,
            "update": True
        },
        "strategy": {
            "display": "策略名",
            "cell": StrategyCell,
            "update": True
        }
    }


class SettingEditor(QtWidgets.QDialog):
    """
    For creating new strategy and editing strategy parameters.
    """

    def __init__(
            self,
            parameters: dict,
            strategy_name: str = "",
            class_name: str = ""
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

        # Add vt_symbol and name edit if add new strategy
        if self.class_name:
            self.setWindowTitle(f"添加策略：{self.class_name}")
            button_text = "添加"
            parameters = {"strategy_name": "", "vt_symbol": ""}
            parameters.update(self.parameters)
        else:
            self.setWindowTitle(f"参数编辑：{self.strategy_name}")
            button_text = "确定"
            parameters = self.parameters

        for name, value in parameters.items():
            type_ = type(value)

            edit = QtWidgets.QLineEdit(str(value))
            form.addRow(f"{name} {type_}", edit)

            self.edits[name] = (edit, type_)

        button = QtWidgets.QPushButton(button_text)
        button.clicked.connect(self.accpet)
        form.addRow(button)

        self.setLayout(form)

    def get_setting(self):
        """"""
        setting = {}

        if self.class_name:
            setting["class_name"] = self.class_name

        for name, tp in self.edits.items():
            edit, type_ = tp
            value = type_(edit.text())
            setting[name] = value

        return setting
