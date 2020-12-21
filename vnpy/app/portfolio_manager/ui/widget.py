from typing import Dict, Tuple, Union
from vnpy.trader.object import TradeData
from vnpy.event.engine import Event
from vnpy.trader.ui import QtWidgets, QtCore, QtGui


from vnpy.trader.engine import MainEngine, EventEngine
from vnpy.trader.ui.widget import (
    BaseCell,
    EnumCell,
    DirectionCell,
    TimeCell
)

from ..base import ContractResult, PortfolioResult
from ..engine import (
    APP_NAME,
    EVENT_PM_CONTRACT,
    EVENT_PM_PORTFOLIO,
    EVENT_TRADE,
    PortfolioEngine
)


RED_COLOR = QtGui.QColor("red")
GREEN_COLOR = QtGui.QColor("green")
WHITE_COLOR = QtGui.QColor("white")


class PortfolioManager(QtWidgets.QWidget):
    """"""

    signal_contract = QtCore.pyqtSignal(Event)
    signal_portfolio = QtCore.pyqtSignal(Event)
    signal_trade = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine

        self.portfolio_engine: PortfolioEngine = main_engine.get_engine(APP_NAME)

        self.contract_items: Dict[Tuple(str, str), QtWidgets.QTreeWidgetItem] = {}
        self.portfolio_items: Dict[str, QtWidgets.QTreeWidgetItem] = {}

        self.init_ui()
        self.register_event()
        self.update_trades()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("投资组合")

        labels = [
            "组合名称",
            "本地代码",
            "开盘仓位",
            "当前仓位",
            "交易盈亏",
            "持仓盈亏",
            "总盈亏",
            "多头成交",
            "空头成交"
        ]
        self.column_count = len(labels)

        self.tree = QtWidgets.QTreeWidget()
        self.tree.setColumnCount(self.column_count)
        self.tree.setHeaderLabels(labels)
        self.tree.header().setDefaultAlignment(QtCore.Qt.AlignCenter)
        self.tree.header().setStretchLastSection(False)

        delegate = TreeDelegate()
        self.tree.setItemDelegate(delegate)

        self.monitor = PortfolioTradeMonitor()

        expand_button = QtWidgets.QPushButton("全部展开")
        expand_button.clicked.connect(self.tree.expandAll)

        collapse_button = QtWidgets.QPushButton("全部折叠")
        collapse_button.clicked.connect(self.tree.collapseAll)

        resize_button = QtWidgets.QPushButton("调整列宽")
        resize_button.clicked.connect(self.resize_columns)

        interval_spin = QtWidgets.QSpinBox()
        interval_spin.setMinimum(1)
        interval_spin.setMaximum(60)
        interval_spin.setSuffix("秒")
        interval_spin.setValue(self.portfolio_engine.get_timer_interval())
        interval_spin.valueChanged.connect(self.portfolio_engine.set_timer_interval)

        self.reference_combo = QtWidgets.QComboBox()
        self.reference_combo.setMinimumWidth(200)
        self.reference_combo.addItem("")
        self.reference_combo.currentIndexChanged.connect(self.set_reference_filter)

        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(expand_button)
        hbox1.addWidget(collapse_button)
        hbox1.addWidget(resize_button)
        hbox1.addStretch()
        hbox1.addWidget(QtWidgets.QLabel("刷新频率"))
        hbox1.addWidget(interval_spin)
        hbox1.addStretch()
        hbox1.addWidget(QtWidgets.QLabel("组合成交"))
        hbox1.addWidget(self.reference_combo)

        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(self.tree)
        hbox2.addWidget(self.monitor)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addLayout(hbox2)
        self.setLayout(vbox)

    def register_event(self) -> None:
        """"""
        self.signal_contract.connect(self.process_contract_event)
        self.signal_portfolio.connect(self.process_portfolio_event)
        self.signal_trade.connect(self.process_trade_event)

        self.event_engine.register(EVENT_PM_CONTRACT, self.signal_contract.emit)
        self.event_engine.register(EVENT_PM_PORTFOLIO, self.signal_portfolio.emit)
        self.event_engine.register(EVENT_TRADE, self.signal_trade.emit)

    def update_trades(self) -> None:
        """"""
        trades = self.main_engine.get_all_trades()
        for trade in trades:
            self.monitor.update_trade(trade)

    def get_portfolio_item(self, reference: str) -> QtWidgets.QTreeWidgetItem:
        """"""
        portfolio_item = self.portfolio_items.get(reference, None)

        if not portfolio_item:
            portfolio_item = QtWidgets.QTreeWidgetItem()
            portfolio_item.setText(0, reference)
            for i in range(2, self.column_count):
                portfolio_item.setTextAlignment(i, QtCore.Qt.AlignCenter)

            self.portfolio_items[reference] = portfolio_item
            self.tree.addTopLevelItem(portfolio_item)

            self.reference_combo.addItem(reference)

        return portfolio_item

    def get_contract_item(self, reference: str, vt_symbol: str) -> QtWidgets.QTreeWidgetItem:
        """"""
        key = (reference, vt_symbol)
        contract_item = self.contract_items.get(key, None)

        if not contract_item:
            contract_item = QtWidgets.QTreeWidgetItem()
            contract_item.setText(1, vt_symbol)
            for i in range(2, self.column_count):
                contract_item.setTextAlignment(i, QtCore.Qt.AlignCenter)

            self.contract_items[key] = contract_item

            portfolio_item = self.get_portfolio_item(reference)
            portfolio_item.addChild(contract_item)

        return contract_item

    def process_contract_event(self, event: Event) -> None:
        """"""
        contract_result: ContractResult = event.data

        contract_item = self.get_contract_item(
            contract_result.reference,
            contract_result.vt_symbol
        )
        contract_item.setText(2, str(contract_result.open_pos))
        contract_item.setText(3, str(contract_result.last_pos))
        contract_item.setText(4, str(contract_result.trading_pnl))
        contract_item.setText(5, str(contract_result.holding_pnl))
        contract_item.setText(6, str(contract_result.total_pnl))
        contract_item.setText(7, str(contract_result.long_volume))
        contract_item.setText(8, str(contract_result.short_volume))

        self.update_item_color(contract_item, contract_result)

    def process_portfolio_event(self, event: Event) -> None:
        """"""
        portfolio_result: PortfolioResult = event.data

        portfolio_item = self.get_portfolio_item(portfolio_result.reference)
        portfolio_item.setText(4, str(portfolio_result.trading_pnl))
        portfolio_item.setText(5, str(portfolio_result.holding_pnl))
        portfolio_item.setText(6, str(portfolio_result.total_pnl))

        self.update_item_color(portfolio_item, portfolio_result)

    def process_trade_event(self, event: Event) -> None:
        """"""
        trade: TradeData = event.data
        self.monitor.update_trade(trade)

    def update_item_color(
        self,
        item: QtWidgets.QTreeWidgetItem,
        result: Union[ContractResult, PortfolioResult]
    ):
        start_column = 4
        for n, pnl in enumerate([
            result.trading_pnl,
            result.holding_pnl,
            result.total_pnl
        ]):
            i = n + start_column

            if pnl > 0:
                item.setForeground(i, RED_COLOR)
            elif pnl < 0:
                item.setForeground(i, GREEN_COLOR)
            else:
                item.setForeground(i, WHITE_COLOR)

    def resize_columns(self) -> None:
        """"""
        for i in range(self.column_count):
            self.tree.resizeColumnToContents(i)

    def set_reference_filter(self, filter: str) -> None:
        """"""
        filter = self.reference_combo.currentText()
        self.monitor.set_filter(filter)

    def show(self) -> None:
        """"""
        self.showMaximized()


class PortfolioTradeMonitor(QtWidgets.QTableWidget):
    """"""

    def __init__(self) -> None:
        """"""
        super().__init__()

        self.init_ui()
        self.filter = ""

    def init_ui(self) -> None:
        """"""
        labels = [
            "组合",
            "成交号",
            "委托号",
            "代码",
            "交易所",
            "方向",
            "开平",
            "价格",
            "数量",
            "时间",
            "接口",
        ]
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

    def update_trade(self, trade: TradeData) -> None:
        """"""
        self.insertRow(0)

        reference_cell = BaseCell(trade.reference, trade)
        tradeid_cell = BaseCell(trade.tradeid, trade)
        orderid_cell = BaseCell(trade.orderid, trade)
        symbol_cell = BaseCell(trade.symbol, trade)
        exchange_cell = EnumCell(trade.exchange, trade)
        direction_cell = DirectionCell(trade.direction, trade)
        offset_cell = EnumCell(trade.offset, trade)
        price_cell = BaseCell(trade.price, trade)
        volume_cell = BaseCell(trade.volume, trade)
        datetime_cell = TimeCell(trade.datetime, trade)
        gateway_cell = BaseCell(trade.gateway_name, trade)

        self.setItem(0, 0, reference_cell)
        self.setItem(0, 1, tradeid_cell)
        self.setItem(0, 2, orderid_cell)
        self.setItem(0, 3, symbol_cell)
        self.setItem(0, 4, exchange_cell)
        self.setItem(0, 5, direction_cell)
        self.setItem(0, 6, offset_cell)
        self.setItem(0, 7, price_cell)
        self.setItem(0, 8, volume_cell)
        self.setItem(0, 9, datetime_cell)
        self.setItem(0, 10, gateway_cell)

        if self.filter and trade.reference != self.filter:
            self.hideRow(0)

    def set_filter(self, filter: str) -> None:
        """"""
        self.filter = filter

        for row in range(self.rowCount()):
            if not filter:
                self.showRow(row)
            else:
                item = self.item(row, 0)
                if item.text() == filter:
                    self.showRow(row)
                else:
                    self.hideRow(row)


class TreeDelegate(QtGui.QStyledItemDelegate):
    """"""

    def sizeHint(
        self,
        option: QtGui.QStyleOptionViewItem,
        index: QtCore.QModelIndex
    ) -> QtCore.QSize:
        """"""
        size = super().sizeHint(option, index)
        size.setHeight(40)
        return size
