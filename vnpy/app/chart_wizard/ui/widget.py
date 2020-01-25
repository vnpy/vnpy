from typing import Dict, List
from datetime import datetime, timedelta

from vnpy.event import EventEngine, Event
from vnpy.chart import ChartWidget, CandleItem, VolumeItem
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore
from vnpy.trader.event import EVENT_TICK
from vnpy.trader.object import TickData, BarData
from vnpy.trader.utility import BarGenerator
from vnpy.trader.constant import Interval

from ..engine import APP_NAME, EVENT_CHART_HISTORY, ChartWizardEngine


class ChartWizardWidget(QtWidgets.QWidget):
    """"""
    signal_tick = QtCore.pyqtSignal(Event)
    signal_history = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.chart_engine: ChartWizardEngine = main_engine.get_engine(APP_NAME)

        self.bgs: Dict[str, BarGenerator] = {}
        self.charts: Dict[str, ChartWidget] = {}

        self.init_ui()
        self.register_event()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("K线图表")

        self.mid_area: QtWidgets.QMdiArea = QtWidgets.QMdiArea()
        self.symbol_line: QtWidgets.QLineEdit = QtWidgets.QLineEdit()

        self.button = QtWidgets.QPushButton("新建图表")
        self.button.clicked.connect(self.new_chart)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(QtWidgets.QLabel("本地代码"))
        hbox.addWidget(self.symbol_line)
        hbox.addWidget(self.button)
        hbox.addStretch()

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.mid_area)

    def create_chart(self) -> ChartWidget:
        """"""
        chart = ChartWidget()
        chart.add_plot("candle", hide_x_axis=True)
        chart.add_plot("volume", maximum_height=200)
        chart.add_item(CandleItem, "candle", "candle")
        chart.add_item(VolumeItem, "volume", "volume")
        chart.add_cursor()
        return chart

    def new_chart(self) -> None:
        """"""
        # Filter invalid vt_symbol
        vt_symbol = self.symbol_line.text()
        if not vt_symbol:
            return

        if vt_symbol in self.charts:
            return

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            return

        # Create new chart
        self.bgs[vt_symbol] = BarGenerator(self.on_bar)

        chart = self.new_chart()
        self.charts[vt_symbol] = chart

        sub_window = self.mid_area.addSubWindow(chart)
        sub_window.setWindowTitle(vt_symbol)

        # Query history data
        end = datetime.now()
        start = end - timedelta(days=10)

        self.chart_engine.query_history(
            vt_symbol,
            Interval.MINUTE,
            start,
            end
        )

    def register_event(self) -> None:
        """"""
        self.signal_tick.connect(self.process_tick_event)
        self.signal_history.connect(self.process_history_event)

        self.event_engine.register(EVENT_CHART_HISTORY, self.signal_history.emit)
        self.event_engine.register(EVENT_TICK, self.signal_tick.emit)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data
        bg = self.bgs.get(tick.vt_symbol, None)

        if bg:
            bg.update_tick(tick)

    def process_history_event(self, event: Event) -> None:
        """"""
        history: List[BarData] = event.data
        bar = history[0]

        chart = self.charts[bar.vt_symbol]
        chart.update_history(history)

    def on_bar(self, bar: BarData):
        """"""
        chart = self.charts[bar.vt_symbol]
        chart.update_bar(bar)
