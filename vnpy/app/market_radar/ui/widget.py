from functools import partial
from typing import Dict
from csv import DictReader

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtCore, QtWidgets

from ..engine import (APP_NAME, EVENT_RADAR_LOG, EVENT_RADAR_RULE,
                      EVENT_RADAR_UPDATE, RadarEngine)


class RadarManager(QtWidgets.QWidget):
    """"""

    signal_log = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.radar_engine: RadarEngine = main_engine.get_engine(APP_NAME)

        self.init_ui()
        self.register_event()

        self.radar_engine.init()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("市场雷达")

        self.radar_monitor = RadarMonitor(self.radar_engine)

        self.log_monitor = QtWidgets.QTextEdit()
        self.log_monitor.setReadOnly(True)
        self.log_monitor.setMaximumHeight(300)

        self.name_line = QtWidgets.QLineEdit()
        self.formula_line = QtWidgets.QLineEdit()
        self.a_line = QtWidgets.QLineEdit()
        self.b_line = QtWidgets.QLineEdit()
        self.c_line = QtWidgets.QLineEdit()
        self.d_line = QtWidgets.QLineEdit()
        self.e_line = QtWidgets.QLineEdit()

        self.ndigits_spin = QtWidgets.QSpinBox()
        self.ndigits_spin.setMinimum(0)
        self.ndigits_spin.setValue(2)

        add_button = QtWidgets.QPushButton("添加")
        add_button.clicked.connect(self.add_rule)

        edit_button = QtWidgets.QPushButton("修改")
        edit_button.clicked.connect(self.edit_rule)

        load_button = QtWidgets.QPushButton("导入CSV")
        load_button.clicked.connect(self.load_csv)

        form = QtWidgets.QFormLayout()
        form.addRow("名称", self.name_line)
        form.addRow("公式", self.formula_line)
        form.addRow("A", self.a_line)
        form.addRow("B", self.b_line)
        form.addRow("C", self.c_line)
        form.addRow("D", self.d_line)
        form.addRow("E", self.e_line)
        form.addRow("小数", self.ndigits_spin)
        form.addRow(add_button)
        form.addRow(edit_button)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(form)
        hbox.addStretch()
        hbox.addWidget(load_button)
        hbox.addStretch()
        hbox.addWidget(self.log_monitor)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.radar_monitor)
        vbox.addLayout(hbox)

        self.setLayout(vbox)

    def register_event(self) -> None:
        """"""
        self.signal_log.connect(self.process_log_event)
        self.event_engine.register(EVENT_RADAR_LOG, self.signal_log.emit)

    def process_log_event(self, event: Event) -> None:
        """"""
        log = event.data
        time_str = log.time.strftime("%H:%M:%S")
        msg = f"{time_str}\t{log.msg}"
        self.log_monitor.append(msg)

    def add_rule(self) -> None:
        """"""
        name, formula, params, ndigits = self.get_rule_setting()
        self.radar_engine.add_rule(name, formula, params, ndigits)
        self.radar_engine.save_setting()

    def edit_rule(self) -> None:
        """"""
        name, formula, params, ndigits = self.get_rule_setting()
        self.radar_engine.edit_rule(name, formula, params, ndigits)
        self.radar_engine.save_setting()

    def get_rule_setting(self) -> tuple:
        """"""
        name = self.name_line.text()
        formula = self.formula_line.text()

        a = self.a_line.text()
        b = self.b_line.text()
        c = self.c_line.text()
        d = self.d_line.text()
        e = self.e_line.text()

        params = {}
        if a:
            params["A"] = a
        if b:
            params["B"] = b
        if c:
            params["C"] = c
        if d:
            params["D"] = d
        if e:
            params["E"] = e

        ndigits = self.ndigits_spin.value()

        return name, formula, params, ndigits

    def show(self):
        """"""
        self.showMaximized()

    def load_csv(self):
        """"""
        path, type_ = QtWidgets.QFileDialog.getOpenFileName(
            self,
            u"导入CSV配置",
            "",
            "CSV(*.csv)"
        )

        if not path:
            return

        # Create csv DictReader
        with open(path, "r") as f:
            reader = DictReader(f)

            for row in reader:
                name = row["名称"]
                formula = row["公式"]
                ndigits = int(row["小数"])

                params = {}
                for param in ["A", "B", "C", "D", "E"]:
                    vt_symbol = row.get(param, "")
                    if vt_symbol:
                        params[param] = vt_symbol

                self.radar_engine.add_rule(name, formula, params, ndigits)
                self.radar_engine.save_setting()


class RadarCell(QtWidgets.QTableWidgetItem):
    """"""

    def __init__(self, text: str = ""):
        """"""
        super().__init__(text)
        self.setTextAlignment(QtCore.Qt.AlignCenter)


class RadarMonitor(QtWidgets.QTableWidget):
    """"""

    signal_rule = QtCore.pyqtSignal(Event)
    signal_update = QtCore.pyqtSignal(Event)

    def __init__(self, radar_engine: RadarEngine):
        """"""
        super().__init__()

        self.radar_engine: RadarEngine = radar_engine
        self.event_engine: EventEngine = radar_engine.event_engine

        self.cells: Dict[str, Dict[str, RadarCell]] = {}

        self.init_ui()
        self.register_event()

    def init_ui(self) -> None:
        """"""
        headers = [
            "名称",
            "数值",
            "时间",
            "公式",
            "A",
            "B",
            "C",
            "D",
            "E",
            "小数",
            " "
        ]

        self.setColumnCount(len(headers))
        self.setHorizontalHeaderLabels(headers)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        self.setAlternatingRowColors(True)

        h_header = self.horizontalHeader()
        h_header.setSectionResizeMode(h_header.Stretch)

    def register_event(self) -> None:
        """"""
        self.signal_rule.connect(self.process_rule_event)
        self.signal_update.connect(self.process_update_event)

        self.event_engine.register(EVENT_RADAR_RULE, self.signal_rule.emit)
        self.event_engine.register(EVENT_RADAR_UPDATE, self.signal_update.emit)

    def process_rule_event(self, event: Event) -> None:
        """"""
        rule_data = event.data

        name = rule_data["name"]
        formula = rule_data["formula"]
        params = rule_data["params"]
        ndigits = rule_data["ndigits"]

        if name not in self.cells:
            name_cell = RadarCell(name)
            value_cell = RadarCell()
            time_cell = RadarCell()
            formula_cell = RadarCell(formula)
            a_cell = RadarCell(params.get("A", ""))
            b_cell = RadarCell(params.get("B", ""))
            c_cell = RadarCell(params.get("C", ""))
            d_cell = RadarCell(params.get("D", ""))
            e_cell = RadarCell(params.get("E", ""))
            ndigits_cell = RadarCell(str(ndigits))

            remove_func = partial(self.remove_rule, name)
            remove_button = QtWidgets.QPushButton("删除")
            remove_button.clicked.connect(remove_func)

            self.insertRow(0)
            self.setItem(0, 0, name_cell)
            self.setItem(0, 1, value_cell)
            self.setItem(0, 2, time_cell)
            self.setItem(0, 3, formula_cell)
            self.setItem(0, 4, a_cell)
            self.setItem(0, 5, b_cell)
            self.setItem(0, 6, c_cell)
            self.setItem(0, 7, d_cell)
            self.setItem(0, 8, e_cell)
            self.setItem(0, 9, ndigits_cell)
            self.setCellWidget(0, 10, remove_button)

            self.cells[name] = {
                "name": name_cell,
                "value": value_cell,
                "time": time_cell,
                "formula": formula_cell,
                "a": a_cell,
                "b": b_cell,
                "c": c_cell,
                "d": d_cell,
                "e": e_cell,
                "ndigits": ndigits_cell
            }
        else:
            row_cells = self.cells[name]

            row_cells["formula"].setText(formula)
            row_cells["a"].setText(params.get("A", ""))
            row_cells["b"].setText(params.get("B", ""))
            row_cells["c"].setText(params.get("C", ""))
            row_cells["d"].setText(params.get("D", ""))
            row_cells["e"].setText(params.get("E", ""))
            row_cells["ndigits"].setText(str(ndigits))

    def process_update_event(self, event: Event) -> None:
        """"""
        radar_data = event.data

        row_cells = self.cells.get(radar_data["name"], None)
        if row_cells:
            row_cells["value"].setText(str(radar_data["value"]))
            row_cells["time"].setText(str(radar_data["time"]))

    def remove_rule(self, name: str) -> None:
        """"""
        rule_names = list(self.cells.keys())
        rule_names.reverse()
        row = rule_names.index(name)

        self.cells.pop(name)
        self.removeRow(row)

        self.radar_engine.remove_rule(name)
        self.radar_engine.save_setting()
