from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.constant import Direction, Offset
from vnpy.trader.ui import QtWidgets, QtCore, QtGui
from vnpy.trader.ui.widget import (
    BaseMonitor, BaseCell,
    BidCell, AskCell,
    TimeCell, PnlCell,
    DirectionCell, EnumCell,
)

from ..engine import (
    PortfolioEngine,
    APP_NAME,
    EVENT_PORTFOLIO_UPDATE,
    EVENT_PORTFOLIO_TRADE,
    EVENT_PORTFOLIO_ORDER
)


class PortfolioManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine

        self.portfolio_engine = main_engine.get_engine(APP_NAME)

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("投资组合")

        strategy_monitor = PortfolioStrategyMonitor(
            self.main_engine, self.event_engine)
        order_monitor = PortfolioOrderMonitor(
            self.main_engine, self.event_engine)
        trade_monitor = PortfolioTradeMonitor(
            self.main_engine, self.event_engine)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.create_group("策略", strategy_monitor))
        vbox.addWidget(self.create_group("委托", order_monitor))
        vbox.addWidget(self.create_group("成交", trade_monitor))

        self.setLayout(vbox)

    def show(self):
        """"""
        self.portfolio_engine.load_setting()
        self.showMaximized()

    def create_group(self, title: str, widget: QtWidgets.QWidget):
        """"""
        group = QtWidgets.QGroupBox()

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(widget)

        group.setLayout(vbox)
        group.setTitle(title)

        return group


class PortfolioStrategyMonitor(BaseMonitor):
    """
    Monitor for portfolio strategy.
    """

    event_type = EVENT_PORTFOLIO_UPDATE
    data_key = "name"
    sorting = False

    headers = {
        "name": {"display": "策略名称", "cell": BaseCell, "update": False},
        "vt_symbol": {"display": "交易合约", "cell": BaseCell, "update": False},
        "size": {"display": "合约乘数", "cell": BaseCell, "update": False},
        "net_pos": {"display": "策略持仓", "cell": BaseCell, "update": True},
        "open_price": {"display": "持仓价格", "cell": BaseCell, "update": True},
        "last_price": {"display": "最新价格", "cell": BaseCell, "update": True},
        "pos_pnl": {"display": "持仓盈亏", "cell": PnlCell, "update": True},
        "create_time": {"display": "创建时间", "cell": BaseCell, "update": False},
    }


class PortfolioTradeMonitor(BaseMonitor):
    """
    Monitor for trade data.
    """

    event_type = EVENT_PORTFOLIO_TRADE
    data_key = ""

    headers = {
        "gateway_name": {"display": "接口名称", "cell": BaseCell, "update": False},
        "tradeid": {"display": "成交号 ", "cell": BaseCell, "update": False},
        "orderid": {"display": "委托号", "cell": BaseCell, "update": False},
        "symbol": {"display": "代码", "cell": BaseCell, "update": False},
        "exchange": {"display": "交易所", "cell": EnumCell, "update": False},
        "direction": {"display": "方向", "cell": DirectionCell, "update": False},
        "offset": {"display": "开平", "cell": EnumCell, "update": False},
        "price": {"display": "价格", "cell": BaseCell, "update": False},
        "volume": {"display": "数量", "cell": BaseCell, "update": False},
        "time": {"display": "时间", "cell": BaseCell, "update": False},
    }


class PortfolioOrderMonitor(BaseMonitor):
    """
    Monitor for order data.
    """

    event_type = EVENT_PORTFOLIO_ORDER
    data_key = "vt_orderid"
    sorting = True

    headers = {
        "gateway_name": {"display": "接口名称", "cell": BaseCell, "update": False},
        "orderid": {"display": "委托号", "cell": BaseCell, "update": False},
        "symbol": {"display": "代码", "cell": BaseCell, "update": False},
        "exchange": {"display": "交易所", "cell": EnumCell, "update": False},
        "type": {"display": "类型", "cell": EnumCell, "update": False},
        "direction": {"display": "方向", "cell": DirectionCell, "update": False},
        "offset": {"display": "开平", "cell": EnumCell, "update": False},
        "price": {"display": "价格", "cell": BaseCell, "update": False},
        "volume": {"display": "总数量", "cell": BaseCell, "update": True},
        "traded": {"display": "已成交", "cell": BaseCell, "update": True},
        "status": {"display": "状态", "cell": EnumCell, "update": True},
        "time": {"display": "时间", "cell": BaseCell, "update": True},
    }

    def init_ui(self):
        """
        Connect signal.
        """
        super(PortfolioOrderMonitor, self).init_ui()

        self.setToolTip("双击单元格撤单")
        self.itemDoubleClicked.connect(self.cancel_order)

    def cancel_order(self, cell):
        """
        Cancel order if cell double clicked.
        """
        order = cell.get_data()
        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)
