"""
Widget for spread trading.
"""

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore
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

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.data_monitor)
        vbox.addWidget(self.log_monitor)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(vbox)
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
