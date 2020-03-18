"""
Widget for algo trading.
"""

import csv
from functools import partial
from datetime import datetime

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore

from ..engine import (
    AlgoEngine,
    AlgoTemplate,
    APP_NAME,
    EVENT_ALGO_LOG,
    EVENT_ALGO_PARAMETERS,
    EVENT_ALGO_VARIABLES,
    EVENT_ALGO_SETTING
)
from .display import NAME_DISPLAY_MAP


class AlgoWidget(QtWidgets.QWidget):
    """
    Start connection of a certain gateway.
    """

    def __init__(
        self,
        algo_engine: AlgoEngine,
        algo_template: AlgoTemplate
    ):
        """"""
        super().__init__()

        self.algo_engine = algo_engine
        self.template_name = algo_template.__name__
        self.default_setting = algo_template.default_setting

        self.widgets = {}

        self.init_ui()

    def init_ui(self):
        """
        Initialize line edits and form layout based on setting.
        """
        self.setMaximumWidth(400)

        form = QtWidgets.QFormLayout()

        for field_name, field_value in self.default_setting.items():
            field_type = type(field_value)

            if field_type == list:
                widget = QtWidgets.QComboBox()
                widget.addItems(field_value)
            else:
                widget = QtWidgets.QLineEdit()

            display_name = NAME_DISPLAY_MAP.get(field_name, field_name)

            form.addRow(display_name, widget)
            self.widgets[field_name] = (widget, field_type)

        start_algo_button = QtWidgets.QPushButton("启动算法")
        start_algo_button.clicked.connect(self.start_algo)
        form.addRow(start_algo_button)

        load_csv_button = QtWidgets.QPushButton("CSV启动")
        load_csv_button.clicked.connect(self.load_csv)
        form.addRow(load_csv_button)

        form.addRow(QtWidgets.QLabel(""))
        form.addRow(QtWidgets.QLabel(""))
        form.addRow(QtWidgets.QLabel(""))

        self.setting_name_line = QtWidgets.QLineEdit()
        form.addRow("配置名称", self.setting_name_line)

        save_setting_button = QtWidgets.QPushButton("保存配置")
        save_setting_button.clicked.connect(self.save_setting)
        form.addRow(save_setting_button)

        for button in [
            start_algo_button,
            load_csv_button,
            save_setting_button
        ]:
            button.setFixedHeight(button.sizeHint().height() * 2)

        self.setLayout(form)

    def load_csv(self):
        """"""
        # Get csv file path from dialog
        path, type_ = QtWidgets.QFileDialog.getOpenFileName(
            self,
            u"加载算法配置",
            "",
            "CSV(*.csv)"
        )

        if not path:
            return

        # Create csv DictReader
        with open(path, "r") as f:
            buf = [line for line in f]
            reader = csv.DictReader(buf)

        # Check whether the csv file has all fields
        for field_name in self.widgets.keys():
            if field_name not in reader.fieldnames:
                QtWidgets.QMessageBox.warning(
                    self,
                    "字段缺失",
                    f"CSV文件缺失算法{self.template_name}所需字段{field_name}"
                )
                return

        # Read setting
        settings = []

        for d in reader:
            # Initialize algo setting with template name
            setting = {
                "template_name": self.template_name
            }

            # Read field from each dict of csv line
            for field_name, tp in self.widgets.items():
                field_type = tp[-1]
                field_text = d[field_name]

                if field_type == list:
                    field_value = field_text
                else:
                    try:
                        field_value = field_type(field_text)
                    except ValueError:
                        QtWidgets.QMessageBox.warning(
                            self,
                            "参数错误",
                            f"{field_name}参数类型应为{field_type}，请检查！"
                        )
                        return

                setting[field_name] = field_value

            # Add setting into list
            settings.append(setting)

        # Only start algos if no exception/error occured
        for setting in settings:
            self.algo_engine.start_algo(setting)

    def get_setting(self):
        """
        Get setting value from line edits.
        """
        setting = {"template_name": self.template_name}

        for field_name, tp in self.widgets.items():
            widget, field_type = tp
            if field_type == list:
                field_value = str(widget.currentText())
            else:
                try:
                    field_value = field_type(widget.text())
                except ValueError:
                    display_name = NAME_DISPLAY_MAP.get(field_name, field_name)
                    QtWidgets.QMessageBox.warning(
                        self,
                        "参数错误",
                        f"{display_name}参数类型应为{field_type}，请检查！"
                    )
                    return None

            setting[field_name] = field_value

        return setting

    def start_algo(self):
        """
        Start algo trading.
        """
        setting = self.get_setting()
        if setting:
            self.algo_engine.start_algo(setting)

    def update_setting(self, setting_name: str, setting: dict):
        """
        Update setting into widgets.
        """
        self.setting_name_line.setText(setting_name)

        for name, tp in self.widgets.items():
            widget, _ = tp
            value = setting[name]

            if isinstance(widget, QtWidgets.QLineEdit):
                widget.setText(str(value))
            elif isinstance(widget, QtWidgets.QComboBox):
                ix = widget.findText(value)
                widget.setCurrentIndex(ix)

    def save_setting(self):
        """
        Save algo setting
        """
        setting_name = self.setting_name_line.text()
        if not setting_name:
            return

        setting = self.get_setting()
        if setting:
            self.algo_engine.update_algo_setting(setting_name, setting)


class AlgoMonitor(QtWidgets.QTableWidget):
    """"""
    parameters_signal = QtCore.pyqtSignal(Event)
    variables_signal = QtCore.pyqtSignal(Event)

    def __init__(
        self,
        algo_engine: AlgoEngine,
        event_engine: EventEngine,
        mode_active: bool
    ):
        """"""
        super().__init__()

        self.algo_engine = algo_engine
        self.event_engine = event_engine
        self.mode_active = mode_active

        self.algo_cells = {}

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        labels = [
            "",
            "算法",
            "参数",
            "状态"
        ]
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

        self.verticalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.ResizeToContents
        )

        for column in range(2, 4):
            self.horizontalHeader().setSectionResizeMode(
                column,
                QtWidgets.QHeaderView.Stretch
            )
        self.setWordWrap(True)

        if not self.mode_active:
            self.hideColumn(0)

    def register_event(self):
        """"""
        self.parameters_signal.connect(self.process_parameters_event)
        self.variables_signal.connect(self.process_variables_event)

        self.event_engine.register(
            EVENT_ALGO_PARAMETERS, self.parameters_signal.emit)
        self.event_engine.register(
            EVENT_ALGO_VARIABLES, self.variables_signal.emit)

    def process_parameters_event(self, event):
        """"""
        data = event.data
        algo_name = data["algo_name"]
        parameters = data["parameters"]

        cells = self.get_algo_cells(algo_name)
        text = to_text(parameters)
        cells["parameters"].setText(text)

    def process_variables_event(self, event):
        """"""
        data = event.data
        algo_name = data["algo_name"]
        variables = data["variables"]

        cells = self.get_algo_cells(algo_name)
        variables_cell = cells["variables"]
        text = to_text(variables)
        variables_cell.setText(text)

        row = self.row(variables_cell)
        active = variables["active"]

        if self.mode_active:
            if active:
                self.showRow(row)
            else:
                self.hideRow(row)
        else:
            if active:
                self.hideRow(row)
            else:
                self.showRow(row)

    def stop_algo(self, algo_name: str):
        """"""
        self.algo_engine.stop_algo(algo_name)

    def get_algo_cells(self, algo_name: str):
        """"""
        cells = self.algo_cells.get(algo_name, None)

        if not cells:
            stop_func = partial(self.stop_algo, algo_name=algo_name)
            stop_button = QtWidgets.QPushButton("停止")
            stop_button.clicked.connect(stop_func)

            name_cell = QtWidgets.QTableWidgetItem(algo_name)
            parameters_cell = QtWidgets.QTableWidgetItem()
            variables_cell = QtWidgets.QTableWidgetItem()

            self.insertRow(0)
            self.setCellWidget(0, 0, stop_button)
            self.setItem(0, 1, name_cell)
            self.setItem(0, 2, parameters_cell)
            self.setItem(0, 3, variables_cell)

            cells = {
                "name": name_cell,
                "parameters": parameters_cell,
                "variables": variables_cell
            }
            self.algo_cells[algo_name] = cells

        return cells


class ActiveAlgoMonitor(AlgoMonitor):
    """
    Monitor for active algos.
    """

    def __init__(self, algo_engine: AlgoEngine, event_engine: EventEngine):
        """"""
        super().__init__(algo_engine, event_engine, True)


class InactiveAlgoMonitor(AlgoMonitor):
    """
    Monitor for inactive algos.
    """

    def __init__(self, algo_engine: AlgoEngine, event_engine: EventEngine):
        """"""
        super().__init__(algo_engine, event_engine, False)


class SettingMonitor(QtWidgets.QTableWidget):
    """"""
    setting_signal = QtCore.pyqtSignal(Event)
    use_signal = QtCore.pyqtSignal(dict)

    def __init__(self, algo_engine: AlgoEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.algo_engine = algo_engine
        self.event_engine = event_engine

        self.settings = {}
        self.setting_cells = {}

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        labels = [
            "",
            "",
            "名称",
            "配置"
        ]
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

        self.verticalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.ResizeToContents
        )

        self.horizontalHeader().setSectionResizeMode(
            3,
            QtWidgets.QHeaderView.Stretch
        )
        self.setWordWrap(True)

    def register_event(self):
        """"""
        self.setting_signal.connect(self.process_setting_event)

        self.event_engine.register(
            EVENT_ALGO_SETTING, self.setting_signal.emit)

    def process_setting_event(self, event):
        """"""
        data = event.data
        setting_name = data["setting_name"]
        setting = data["setting"]
        cells = self.get_setting_cells(setting_name)

        if setting:
            self.settings[setting_name] = setting

            cells["setting"].setText(to_text(setting))
        else:
            if setting_name in self.settings:
                self.settings.pop(setting_name)

            row = self.row(cells["setting"])
            self.removeRow(row)

            self.setting_cells.pop(setting_name)

    def get_setting_cells(self, setting_name: str):
        """"""
        cells = self.setting_cells.get(setting_name, None)

        if not cells:
            use_func = partial(self.use_setting, setting_name=setting_name)
            use_button = QtWidgets.QPushButton("使用")
            use_button.clicked.connect(use_func)

            remove_func = partial(self.remove_setting,
                                  setting_name=setting_name)
            remove_button = QtWidgets.QPushButton("移除")
            remove_button.clicked.connect(remove_func)

            name_cell = QtWidgets.QTableWidgetItem(setting_name)
            setting_cell = QtWidgets.QTableWidgetItem()

            self.insertRow(0)
            self.setCellWidget(0, 0, use_button)
            self.setCellWidget(0, 1, remove_button)
            self.setItem(0, 2, name_cell)
            self.setItem(0, 3, setting_cell)

            cells = {
                "name": name_cell,
                "setting": setting_cell
            }
            self.setting_cells[setting_name] = cells

        return cells

    def use_setting(self, setting_name: str):
        """"""
        setting = self.settings[setting_name]
        setting["setting_name"] = setting_name
        self.use_signal.emit(setting)

    def remove_setting(self, setting_name: str):
        """"""
        self.algo_engine.remove_algo_setting(setting_name)


class LogMonitor(QtWidgets.QTableWidget):
    """"""
    signal = QtCore.pyqtSignal(Event)

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__()

        self.event_engine = event_engine

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        labels = [
            "时间",
            "信息"
        ]
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

        self.verticalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.ResizeToContents
        )

        self.horizontalHeader().setSectionResizeMode(
            1,
            QtWidgets.QHeaderView.Stretch
        )
        self.setWordWrap(True)

    def register_event(self):
        """"""
        self.signal.connect(self.process_log_event)

        self.event_engine.register(EVENT_ALGO_LOG, self.signal.emit)

    def process_log_event(self, event):
        """"""
        log = event.data
        msg = log.msg
        timestamp = datetime.now().strftime("%H:%M:%S")

        timestamp_cell = QtWidgets.QTableWidgetItem(timestamp)
        msg_cell = QtWidgets.QTableWidgetItem(msg)

        self.insertRow(0)
        self.setItem(0, 0, timestamp_cell)
        self.setItem(0, 1, msg_cell)


class AlgoManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.algo_engine = main_engine.get_engine(APP_NAME)

        self.algo_widgets = {}

        self.init_ui()
        self.algo_engine.init_engine()

    def init_ui(self):
        """"""
        self.setWindowTitle("算法交易")

        # Left side control widgets
        self.template_combo = QtWidgets.QComboBox()
        self.template_combo.currentIndexChanged.connect(self.show_algo_widget)

        form = QtWidgets.QFormLayout()
        form.addRow("算法", self.template_combo)
        widget = QtWidgets.QWidget()
        widget.setLayout(form)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(widget)

        for algo_template in self.algo_engine.algo_templates.values():
            widget = AlgoWidget(self.algo_engine, algo_template)
            vbox.addWidget(widget)

            template_name = algo_template.__name__
            display_name = algo_template.display_name

            self.algo_widgets[template_name] = widget
            self.template_combo.addItem(display_name, template_name)

        vbox.addStretch()

        stop_all_button = QtWidgets.QPushButton("全部停止")
        stop_all_button.setFixedHeight(stop_all_button.sizeHint().height() * 2)
        stop_all_button.clicked.connect(self.algo_engine.stop_all)

        vbox.addWidget(stop_all_button)

        # Right side monitor widgets
        active_algo_monitor = ActiveAlgoMonitor(
            self.algo_engine, self.event_engine
        )
        inactive_algo_monitor = InactiveAlgoMonitor(
            self.algo_engine, self.event_engine
        )
        tab1 = QtWidgets.QTabWidget()
        tab1.addTab(active_algo_monitor, "执行中")
        tab1.addTab(inactive_algo_monitor, "已结束")

        log_monitor = LogMonitor(self.event_engine)
        tab2 = QtWidgets.QTabWidget()
        tab2.addTab(log_monitor, "日志")

        setting_monitor = SettingMonitor(self.algo_engine, self.event_engine)
        setting_monitor.use_signal.connect(self.use_setting)
        tab3 = QtWidgets.QTabWidget()
        tab3.addTab(setting_monitor, "配置")

        grid = QtWidgets.QGridLayout()
        grid.addWidget(tab1, 0, 0, 1, 2)
        grid.addWidget(tab2, 1, 0)
        grid.addWidget(tab3, 1, 1)

        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addLayout(vbox)
        hbox2.addLayout(grid)
        self.setLayout(hbox2)

        self.show_algo_widget()

    def show_algo_widget(self):
        """"""
        ix = self.template_combo.currentIndex()
        current_name = self.template_combo.itemData(ix)

        for template_name, widget in self.algo_widgets.items():
            if template_name == current_name:
                widget.show()
            else:
                widget.hide()

    def use_setting(self, setting: dict):
        """"""
        setting_name = setting["setting_name"]
        template_name = setting["template_name"]

        widget = self.algo_widgets[template_name]
        widget.update_setting(setting_name, setting)

        ix = self.template_combo.findData(template_name)
        self.template_combo.setCurrentIndex(ix)
        self.show_algo_widget()

    def show(self):
        """"""
        self.showMaximized()


def to_text(data: dict):
    """
    Convert dict data into string.
    """
    buf = []
    for key, value in data.items():
        key = NAME_DISPLAY_MAP.get(key, key)
        buf.append(f"{key}：{value}")
    text = "，".join(buf)
    return text
