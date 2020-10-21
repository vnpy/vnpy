from typing import Dict
from functools import partial

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore


from ..engine import (
    RadarEngine,
    APP_NAME,
    EVENT_RADAR_RULE,
    EVENT_RADAR_UPDATE,
    EVENT_RADAR_LOG
)


class RadarManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.radar_engine: RadarEngine = main_engine.get_engine(APP_NAME)

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("市场雷达")

        self.monitor = RadarMonitor(self.radar_engine)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.monitor)
        self.setLayout(vbox)


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
            "规则名称",
            "最新数值",
            "更新时间",
            "计算公式",
            "A",
            "B",
            "C",
            "D",
            "E",
            " "
        ]

        self.setColumnCount(len(headers))
        self.setHorizontalHeaderLabels(headers)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        self.setAlternatingRowColors(True)

    def register_event(self) -> None:
        """"""
        self.signal_rule.connect(self.process_rule_event)
        self.signal_update.connect(self.process_update_event)
        self.signal_remove.connect(self.process_remove_event)

    def process_rule_event(self, event: Event) -> None:
        """"""
        rule_data = event.data

        name = rule_data["name"]
        formula = rule_data["formula"]
        params = rule_data["params"]

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
            self.setCellWidget(0, 9, remove_button)

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
            }
        else:
            row_cells = self.cells[name]

            row_cells["formula"].setText(formula)
            row_cells["a"].setText(params.get("A", ""))
            row_cells["b"].setText(params.get("B", ""))
            row_cells["c"].setText(params.get("C", ""))
            row_cells["d"].setText(params.get("D", ""))
            row_cells["e"].setText(params.get("E", ""))

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
        row = rule_names.index(name)

        self.radar_engine.remove_rule(name)
        self.radar_engine.save_setting()

        self.removeRow(row)
        self.cells.pop(name)
