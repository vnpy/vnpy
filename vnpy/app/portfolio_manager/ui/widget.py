from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.constant import Direction, Offset
from vnpy.trader.ui import QtWidgets, QtGui
from vnpy.trader.ui.widget import (
    BaseMonitor, BaseCell,
    PnlCell, DirectionCell, EnumCell,
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

        self.trading_widget = StrategyTradingWidget(self.portfolio_engine)
        self.management_widget = StrategyManagementWidget(
            self.portfolio_engine,
            self.trading_widget,
            strategy_monitor
        )

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.management_widget)
        vbox.addWidget(self.create_group("策略", strategy_monitor))
        vbox.addWidget(self.trading_widget)
        vbox.addWidget(self.create_group("委托", order_monitor))
        vbox.addWidget(self.create_group("成交", trade_monitor))

        self.setLayout(vbox)

    def show(self):
        """"""
        self.portfolio_engine.init_engine()
        self.management_widget.update_combo()

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
        "realized_pnl": {"display": "平仓盈亏", "cell": PnlCell, "update": True},
        "create_time": {"display": "创建时间", "cell": BaseCell, "update": False},
    }

    def remove_strategy(self, name: str):
        """"""
        if name not in self.cells:
            return

        row_cells = self.cells.pop(name)
        row = self.row(row_cells["net_pos"])
        self.removeRow(row)


class PortfolioTradeMonitor(BaseMonitor):
    """
    Monitor for trade data.
    """

    event_type = EVENT_PORTFOLIO_TRADE
    data_key = ""

    headers = {
        "gateway_name": {"display": "策略名称", "cell": BaseCell, "update": False},
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
        "gateway_name": {"display": "策略名称", "cell": BaseCell, "update": False},
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


class StrategyTradingWidget(QtWidgets.QWidget):
    """"""

    def __init__(self, portfolio_engine: PortfolioEngine):
        """"""
        super().__init__()

        self.portfolio_engine = portfolio_engine
        self.init_ui()
        self.update_combo()

    def init_ui(self):
        """"""
        self.name_combo = QtWidgets.QComboBox()

        self.direction_combo = QtWidgets.QComboBox()
        self.direction_combo.addItems(
            [Direction.LONG.value, Direction.SHORT.value])

        self.offset_combo = QtWidgets.QComboBox()
        self.offset_combo.addItems([offset.value for offset in Offset])

        double_validator = QtGui.QDoubleValidator()
        double_validator.setBottom(0)

        self.price_line = QtWidgets.QLineEdit()
        self.price_line.setValidator(double_validator)

        self.volume_line = QtWidgets.QLineEdit()
        self.volume_line.setValidator(double_validator)

        for w in [
            self.name_combo,
            self.price_line,
            self.volume_line,
            self.direction_combo,
            self.offset_combo
        ]:
            w.setFixedWidth(150)

        send_button = QtWidgets.QPushButton("委托")
        send_button.clicked.connect(self.send_order)
        send_button.setFixedWidth(70)

        cancel_button = QtWidgets.QPushButton("全撤")
        cancel_button.clicked.connect(self.cancel_all)
        cancel_button.setFixedWidth(70)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(QtWidgets.QLabel("策略名称"))
        hbox.addWidget(self.name_combo)
        hbox.addWidget(QtWidgets.QLabel("方向"))
        hbox.addWidget(self.direction_combo)
        hbox.addWidget(QtWidgets.QLabel("开平"))
        hbox.addWidget(self.offset_combo)
        hbox.addWidget(QtWidgets.QLabel("价格"))
        hbox.addWidget(self.price_line)
        hbox.addWidget(QtWidgets.QLabel("数量"))
        hbox.addWidget(self.volume_line)
        hbox.addWidget(send_button)
        hbox.addWidget(cancel_button)
        hbox.addStretch()

        self.setLayout(hbox)

    def send_order(self):
        """"""
        name = self.name_combo.currentText()

        price_text = self.price_line.text()
        volume_text = self.volume_line.text()

        if not price_text or not volume_text:
            return

        price = float(price_text)
        volume = float(volume_text)
        direction = Direction(self.direction_combo.currentText())
        offset = Offset(self.offset_combo.currentText())

        self.portfolio_engine.send_order(
            name,
            price,
            volume,
            direction,
            offset
        )

    def cancel_all(self):
        """"""
        name = self.name_combo.currentText()
        self.portfolio_engine.cancel_all(name)

    def update_combo(self):
        """"""
        strategy_names = list(self.portfolio_engine.strategies.keys())

        self.name_combo.clear()
        self.name_combo.addItems(strategy_names)


class StrategyManagementWidget(QtWidgets.QWidget):
    """"""

    def __init__(
        self,
        portfolio_engine: PortfolioEngine,
        trading_widget: StrategyTradingWidget,
        strategy_monitor: PortfolioStrategyMonitor
    ):
        """"""
        super().__init__()

        self.portfolio_engine = portfolio_engine
        self.trading_widget = trading_widget
        self.strategy_monitor = strategy_monitor

        self.init_ui()
        self.update_combo()

    def init_ui(self):
        """"""
        self.name_line = QtWidgets.QLineEdit()
        self.symbol_line = QtWidgets.QLineEdit()
        self.remove_combo = QtWidgets.QComboBox()

        for w in [
            self.name_line,
            self.symbol_line,
            self.remove_combo
        ]:
            w.setFixedWidth(150)

        add_button = QtWidgets.QPushButton("创建策略")
        add_button.clicked.connect(self.add_strategy)

        remove_button = QtWidgets.QPushButton("移除策略")
        remove_button.clicked.connect(self.remove_strategy)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(QtWidgets.QLabel("策略名称"))
        hbox.addWidget(self.name_line)
        hbox.addWidget(QtWidgets.QLabel("交易合约"))
        hbox.addWidget(self.symbol_line)
        hbox.addWidget(add_button)
        hbox.addStretch()
        hbox.addWidget(self.remove_combo)
        hbox.addWidget(remove_button)

        self.setLayout(hbox)

    def add_strategy(self):
        """"""
        name = self.name_line.text()
        vt_symbol = self.symbol_line.text()

        if not name or not vt_symbol:
            QtWidgets.QMessageBox.information(
                self,
                "提示",
                "请输入策略名称和交易合约",
                QtWidgets.QMessageBox.Ok
            )

        result = self.portfolio_engine.add_strategy(name, vt_symbol)

        if result:
            QtWidgets.QMessageBox.information(
                self,
                "提示",
                "策略创建成功",
                QtWidgets.QMessageBox.Ok
            )

            self.update_combo()
        else:
            QtWidgets.QMessageBox.warning(
                self,
                "提示",
                "策略创建失败，存在重名或找不到合约",
                QtWidgets.QMessageBox.Ok
            )

    def remove_strategy(self):
        """"""
        name = self.remove_combo.currentText()

        if not name:
            return

        result = self.portfolio_engine.remove_strategy(name)

        if result:
            QtWidgets.QMessageBox.information(
                self,
                "提示",
                "策略移除成功",
                QtWidgets.QMessageBox.Ok
            )

            self.update_combo()

            self.strategy_monitor.remove_strategy(name)
        else:
            QtWidgets.QMessageBox.warning(
                self,
                "提示",
                "策略移除失败，不存在该策略",
                QtWidgets.QMessageBox.Ok
            )

    def update_combo(self):
        """"""
        strategy_names = list(self.portfolio_engine.strategies.keys())

        self.remove_combo.clear()
        self.remove_combo.addItems(strategy_names)

        self.trading_widget.update_combo()
