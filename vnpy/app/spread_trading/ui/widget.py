"""
Widget for spread trading.
"""

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.constant import Direction
from vnpy.trader.ui import QtWidgets, QtCore, QtGui
from vnpy.trader.ui.widget import (
    BaseMonitor, BaseCell,
    BidCell, AskCell,
    TimeCell, MsgCell,
    PnlCell, DirectionCell,
    EnumCell,
)

from ..engine import (
    SpreadEngine,
    APP_NAME,
    EVENT_SPREAD_DATA,
    EVENT_SPREAD_LOG,
    EVENT_SPREAD_ALGO,
    EVENT_SPREAD_STRATEGY
)


class SpreadManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.spread_engine = main_engine.get_engine(APP_NAME)

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("价差交易")

        self.algo_dialog = SpreadAlgoDialog(self.spread_engine)

        self.data_monitor = SpreadDataMonitor(
            self.main_engine,
            self.event_engine
        )
        self.log_monitor = SpreadLogMonitor(
            self.main_engine,
            self.event_engine
        )
        self.algo_monitor = SpreadAlgoMonitor(
            self.main_engine,
            self.event_engine
        )

        vbox1 = QtWidgets.QVBoxLayout()
        vbox1.addWidget(self.algo_dialog)
        vbox1.addStretch()

        vbox2 = QtWidgets.QVBoxLayout()
        vbox2.addWidget(self.data_monitor)
        vbox2.addWidget(self.log_monitor)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(vbox1)
        hbox.addLayout(vbox2)
        hbox.addWidget(self.algo_monitor)

        self.setLayout(hbox)

    def show(self):
        """"""
        self.spread_engine.start()

        self.showMaximized()


class SpreadDataMonitor(BaseMonitor):
    """
    Monitor for spread data.
    """

    event_type = EVENT_SPREAD_DATA
    data_key = "name"
    sorting = False

    headers = {
        "name": {"display": "名称", "cell": BaseCell, "update": False},
        "price_formula": {"display": "定价", "cell": BaseCell, "update": False},
        "trading_formula": {"display": "交易", "cell": BaseCell, "update": False},
        "bid_volume": {"display": "买量", "cell": BidCell, "update": True},
        "bid_price": {"display": "买价", "cell": BidCell, "update": True},
        "ask_price": {"display": "卖价", "cell": AskCell, "update": True},
        "ask_volume": {"display": "卖量", "cell": AskCell, "update": True},
        "net_pos": {"display": "净仓", "cell": PnlCell, "update": True},
        "datetime": {"display": "时间", "cell": TimeCell, "update": True},
    }


class SpreadLogMonitor(QtWidgets.QTextEdit):
    """
    Monitor for log data.
    """
    signal = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        self.setReadOnly(True)

    def register_event(self):
        """"""
        self.signal.connect(self.process_log_event)

        self.event_engine.register(EVENT_SPREAD_LOG, self.signal.emit)

    def process_log_event(self, event: Event):
        """"""
        log = event.data
        msg = f"{log.time}：{log.msg}"
        self.append(msg)


class SpreadAlgoMonitor(BaseMonitor):
    """
    Monitor for algo status.
    """

    event_type = EVENT_SPREAD_ALGO
    data_key = "algoid"
    sorting = False

    headers = {
        "algoid": {"display": "算法", "cell": BaseCell, "update": False},
        "spread_name": {"display": "价差", "cell": BaseCell, "update": False},
        "direction": {"display": "方向", "cell": EnumCell, "update": False},
        "price": {"display": "价格", "cell": BaseCell, "update": False},
        "payup": {"display": "超价", "cell": BaseCell, "update": False},
        "volume": {"display": "数量", "cell": BaseCell, "update": False},
        "traded_volume": {"display": "成交", "cell": BaseCell, "update": True},
        "interval": {"display": "间隔", "cell": BaseCell, "update": False},
        "count": {"display": "计数", "cell": BaseCell, "update": True},
        "status": {"display": "状态", "cell": EnumCell, "update": True},
    }


class SpreadAlgoDialog(QtWidgets.QDialog):
    """"""

    def __init__(self, spread_engine: SpreadEngine):
        """"""
        super().__init__()

        self.spread_engine: SpreadEngine = spread_engine

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("启动算法")

        self.name_line = QtWidgets.QLineEdit()

        self.direction_combo = QtWidgets.QComboBox()
        self.direction_combo.addItems(
            [Direction.LONG.value, Direction.SHORT.value]
        )

        float_validator = QtGui.QDoubleValidator()
        float_validator.setBottom(0)

        self.price_line = QtWidgets.QLineEdit()
        self.price_line.setValidator(float_validator)

        self.volume_line = QtWidgets.QLineEdit()
        self.volume_line.setValidator(float_validator)

        int_validator = QtGui.QIntValidator()

        self.payup_line = QtWidgets.QLineEdit()
        self.payup_line.setValidator(int_validator)

        self.interval_line = QtWidgets.QLineEdit()
        self.interval_line.setValidator(int_validator)

        button_start = QtWidgets.QPushButton("启动")
        button_start.clicked.connect(self.start_algo)

        form = QtWidgets.QFormLayout()
        form.addRow("价差", self.name_line)
        form.addRow("方向", self.direction_combo)
        form.addRow("价格", self.price_line)
        form.addRow("数量", self.volume_line)
        form.addRow("超价", self.payup_line)
        form.addRow("间隔", self.interval_line)
        form.addRow(button_start)

        self.setLayout(form)

    def start_algo(self):
        """"""
        name = self.name_line.text()
        direction = Direction(self.direction_combo.currentText())
        price = float(self.price_line.text())
        volume = float(self.volume_line.text())
        payup = int(self.payup_line.text())
        interval = int(self.interval_line.text())

        self.spread_engine.start_algo(
            name, direction, price, volume, payup, interval
        )
