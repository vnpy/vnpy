from typing import Dict, List

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore, QtGui
from vnpy.trader.constant import Direction, Offset, OrderType
from vnpy.trader.object import OrderRequest, ContractData, TickData
from vnpy.trader.event import EVENT_TICK

from ..base import APP_NAME, EVENT_OPTION_NEW_PORTFOLIO
from ..engine import OptionEngine, PRICING_MODELS
from .monitor import (
    OptionMarketMonitor, OptionGreeksMonitor, MonitorCell
)


class OptionManager(QtWidgets.QWidget):
    """"""
    signal_new_portfolio = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.option_engine = main_engine.get_engine(APP_NAME)

        self.portfolio_name: str = ""

        self.market_monitor: OptionMarketMonitor = None
        self.greeks_monitor: OptionGreeksMonitor = None

        self.docks: List[QtWidgets.QDockWidget] = []

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        self.setWindowTitle("OptionMaster")

        self.portfolio_combo = QtWidgets.QComboBox()
        self.portfolio_combo.setFixedWidth(150)
        self.update_portfolio_combo()

        self.portfolio_button = QtWidgets.QPushButton("配置")
        self.portfolio_button.clicked.connect(self.open_portfolio_dialog)

        self.market_button = QtWidgets.QPushButton("T型报价")
        self.greeks_button = QtWidgets.QPushButton("持仓希腊值")
        self.chain_button = QtWidgets.QPushButton("拟合升贴水")
        self.manual_button = QtWidgets.QPushButton("快速交易")

        for button in [
            self.market_button,
            self.greeks_button,
            self.chain_button,
            self.manual_button
        ]:
            button.setEnabled(False)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(QtWidgets.QLabel("期权产品"))
        hbox.addWidget(self.portfolio_combo)
        hbox.addWidget(self.portfolio_button)
        hbox.addWidget(self.market_button)
        hbox.addWidget(self.greeks_button)
        hbox.addWidget(self.manual_button)
        hbox.addWidget(self.chain_button)

        self.setLayout(hbox)

    def register_event(self):
        """"""
        self.signal_new_portfolio.connect(self.process_new_portfolio_event)

        self.event_engine.register(EVENT_OPTION_NEW_PORTFOLIO, self.signal_new_portfolio.emit)

    def process_new_portfolio_event(self, event: Event):
        """"""
        self.update_portfolio_combo()

    def update_portfolio_combo(self):
        """"""
        if not self.portfolio_combo.isEnabled():
            return

        self.portfolio_combo.clear()
        portfolio_names = self.option_engine.get_portfolio_names()
        self.portfolio_combo.addItems(portfolio_names)

    def open_portfolio_dialog(self):
        """"""
        portfolio_name = self.portfolio_combo.currentText()
        if not portfolio_name:
            return

        self.portfolio_name = portfolio_name

        dialog = PortfolioDialog(self.option_engine, portfolio_name)
        result = dialog.exec_()

        if result == dialog.Accepted:
            self.portfolio_combo.setEnabled(False)
            self.portfolio_button.setEnabled(False)

            self.init_widgets()

    def init_widgets(self):
        """"""
        self.market_monitor = OptionMarketMonitor(self.option_engine, self.portfolio_name)
        self.greeks_monitor = OptionGreeksMonitor(self.option_engine, self.portfolio_name)
        self.manual_trader = OptionManualTrader(self.option_engine, self.portfolio_name)

        self.market_monitor.itemDoubleClicked.connect(self.manual_trader.update_symbol)

        self.market_button.clicked.connect(self.market_monitor.showMaximized)
        self.greeks_button.clicked.connect(self.greeks_monitor.showMaximized)
        self.manual_button.clicked.connect(self.manual_trader.show)
        self.chain_button.clicked.connect(self.calculate_underlying_adjustment)

        for button in [
            self.market_button,
            self.greeks_button,
            self.chain_button,
            self.manual_button
        ]:
            button.setEnabled(True)

    def calculate_underlying_adjustment(self):
        """"""
        portfolio = self.option_engine.get_portfolio(self.portfolio_name)

        for chain in portfolio.chains.values():
            chain.calculate_underlying_adjustment()


class PortfolioDialog(QtWidgets.QDialog):
    """"""

    def __init__(self, option_engine: OptionEngine, portfolio_name: str):
        """"""
        super().__init__()

        self.option_engine = option_engine
        self.portfolio_name = portfolio_name

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle(f"{self.portfolio_name}组合配置")

        portfolio_setting = self.option_engine.get_portfolio_setting(
            self.portfolio_name
        )

        form = QtWidgets.QFormLayout()

        # Model Combo
        self.model_name_combo = QtWidgets.QComboBox()
        self.model_name_combo.addItems(list(PRICING_MODELS.keys()))

        model_name = portfolio_setting.get("model_name", "")
        if model_name:
            self.model_name_combo.setCurrentIndex(
                self.model_name_combo.findText(model_name)
            )

        form.addRow("模型", self.model_name_combo)

        # Interest rate spin
        self.interest_rate_spin = QtWidgets.QDoubleSpinBox()
        self.interest_rate_spin.setMinimum(0)
        self.interest_rate_spin.setMaximum(20)
        self.interest_rate_spin.setDecimals(1)
        self.interest_rate_spin.setSuffix("%")

        interest_rate = portfolio_setting.get("interest_rate", 0.02)
        self.interest_rate_spin.setValue(interest_rate * 100)

        form.addRow("利率", self.interest_rate_spin)

        # Underlying for each chain
        self.combos: Dict[str, QtWidgets.QComboBox] = {}

        portfolio = self.option_engine.get_portfolio(self.portfolio_name)
        underlying_symbols = self.option_engine.get_underlying_symbols(
            self.portfolio_name
        )

        chain_symbols = list(portfolio._chains.keys())
        chain_symbols.sort()

        chain_underlying_map = portfolio_setting.get("chain_underlying_map", {})

        for chain_symbol in chain_symbols:
            combo = QtWidgets.QComboBox()
            combo.addItem("")
            combo.addItems(underlying_symbols)

            underlying_symbol = chain_underlying_map.get(chain_symbol, "")
            if underlying_symbol:
                combo.setCurrentIndex(combo.findText(underlying_symbol))

            form.addRow(chain_symbol, combo)
            self.combos[chain_symbol] = combo

        # Set layout
        button = QtWidgets.QPushButton("确定")
        button.clicked.connect(self.update_portfolio_setting)
        form.addRow(button)

        self.setLayout(form)

    def update_portfolio_setting(self):
        """"""
        model_name = self.model_name_combo.currentText()
        interest_rate = self.interest_rate_spin.value() / 100

        chain_underlying_map = {}
        for chain_symbol, combo in self.combos.items():
            underlying_symbol = combo.currentText()

            if underlying_symbol:
                chain_underlying_map[chain_symbol] = underlying_symbol

        self.option_engine.update_portfolio_setting(
            self.portfolio_name,
            model_name,
            interest_rate,
            chain_underlying_map
        )

        result = self.option_engine.init_portfolio(self.portfolio_name)

        if result:
            self.accept()
        else:
            self.close()


class OptionManualTrader(QtWidgets.QWidget):
    """"""
    signal_tick = QtCore.pyqtSignal(TickData)

    def __init__(self, option_engine: OptionEngine, portfolio_name: str):
        """"""
        super().__init__()

        self.option_engine = option_engine
        self.main_engine: MainEngine = option_engine.main_engine
        self.event_engine: EventEngine = option_engine.event_engine

        self.contracts: Dict[str, ContractData] = {}
        self.vt_symbol = ""

        self.init_ui()
        self.init_contracts()

    def init_ui(self):
        """"""
        self.setWindowTitle("期权交易")

        # Trading Area
        self.symbol_line = QtWidgets.QLineEdit()
        self.symbol_line.returnPressed.connect(self._update_symbol)

        float_validator = QtGui.QDoubleValidator()
        float_validator.setBottom(0)

        self.price_line = QtWidgets.QLineEdit()
        self.price_line.setValidator(float_validator)

        int_validator = QtGui.QIntValidator()
        int_validator.setBottom(0)

        self.volume_line = QtWidgets.QLineEdit()
        self.volume_line.setValidator(int_validator)

        self.direction_combo = QtWidgets.QComboBox()
        self.direction_combo.addItems([
            Direction.LONG.value,
            Direction.SHORT.value
        ])

        self.offset_combo = QtWidgets.QComboBox()
        self.offset_combo.addItems([
            Offset.OPEN.value,
            Offset.CLOSE.value
        ])

        order_button = QtWidgets.QPushButton("委托")
        order_button.clicked.connect(self.send_order)

        cancel_button = QtWidgets.QPushButton("全撤")
        cancel_button.clicked.connect(self.cancel_all)

        form1 = QtWidgets.QFormLayout()
        form1.addRow("代码", self.symbol_line)
        form1.addRow("方向", self.direction_combo)
        form1.addRow("开平", self.offset_combo)
        form1.addRow("价格", self.price_line)
        form1.addRow("数量", self.volume_line)
        form1.addRow(order_button)
        form1.addRow(cancel_button)

        # Depth Area
        bid_color = "rgb(255,174,201)"
        ask_color = "rgb(160,255,160)"

        self.bp1_label = self.create_label(bid_color)
        self.bp2_label = self.create_label(bid_color)
        self.bp3_label = self.create_label(bid_color)
        self.bp4_label = self.create_label(bid_color)
        self.bp5_label = self.create_label(bid_color)

        self.bv1_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv2_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv3_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv4_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv5_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)

        self.ap1_label = self.create_label(ask_color)
        self.ap2_label = self.create_label(ask_color)
        self.ap3_label = self.create_label(ask_color)
        self.ap4_label = self.create_label(ask_color)
        self.ap5_label = self.create_label(ask_color)

        self.av1_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av2_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av3_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av4_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av5_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)

        self.lp_label = self.create_label()
        self.return_label = self.create_label(alignment=QtCore.Qt.AlignRight)

        min_width = 70
        self.lp_label.setMinimumWidth(min_width)
        self.return_label.setMinimumWidth(min_width)

        form2 = QtWidgets.QFormLayout()
        form2.addRow(self.ap5_label, self.av5_label)
        form2.addRow(self.ap4_label, self.av4_label)
        form2.addRow(self.ap3_label, self.av3_label)
        form2.addRow(self.ap2_label, self.av2_label)
        form2.addRow(self.ap1_label, self.av1_label)
        form2.addRow(self.lp_label, self.return_label)
        form2.addRow(self.bp1_label, self.bv1_label)
        form2.addRow(self.bp2_label, self.bv2_label)
        form2.addRow(self.bp3_label, self.bv3_label)
        form2.addRow(self.bp4_label, self.bv4_label)
        form2.addRow(self.bp5_label, self.bv5_label)

        # Set layout
        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(form1)
        hbox.addLayout(form2)
        self.setLayout(hbox)

    def init_contracts(self):
        """"""
        contracts = self.main_engine.get_all_contracts()
        for contract in contracts:
            self.contracts[contract.symbol] = contract

    def connect_signal(self):
        """"""
        self.signal_tick.connect(self.update_tick)

    def send_order(self):
        """"""
        symbol = self.symbol_line.text()
        contract = self.contracts.get(symbol, None)
        if not contract:
            return

        price_text = self.price_line.text()
        volume_text = self.volume_line.text()

        if not price_text or not volume_text:
            return

        price = float(price_text)
        volume = int(volume_text)
        direction = Direction(self.direction_combo.currentText())
        offset = Offset(self.offset_combo.currentText())

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            type=OrderType.LIMIT,
            offset=offset,
            volume=volume,
            price=price
        )
        self.main_engine.send_order(req, contract.gateway_name)

    def cancel_all(self):
        """"""
        for order in self.main_engine.get_all_active_orders():
            req = order.create_cancel_request()
            self.main_engine.cancel_order(req, order.gateway_name)

    def update_symbol(self, cell: MonitorCell):
        """"""
        if not cell.vt_symbol:
            return

        symbol = cell.vt_symbol.split(".")[0]
        self.symbol_line.setText(symbol)
        self._update_symbol()

    def _update_symbol(self):
        """"""
        symbol = self.symbol_line.text()
        contract = self.contracts.get(symbol, None)

        if contract and contract.vt_symbol == self.vt_symbol:
            return

        if self.vt_symbol:
            self.event_engine.unregister(EVENT_TICK + self.vt_symbol, self.process_tick_event)
            self.clear_data()
            self.vt_symbol = ""

        if not contract:
            return

        vt_symbol = contract.vt_symbol
        self.vt_symbol = vt_symbol

        tick = self.main_engine.get_tick(vt_symbol)
        if tick:
            self.update_tick(tick)

        self.event_engine.unregister(EVENT_TICK + vt_symbol, self.process_tick_event)

    def create_label(self, color: str = "", alignment: int = QtCore.Qt.AlignLeft):
        """
        Create label with certain font color.
        """
        label = QtWidgets.QLabel("-")
        if color:
            label.setStyleSheet(f"color:{color}")
        label.setAlignment(alignment)
        return label

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data

        if tick.vt_symbol != self.vt_symbol:
            return

        self.signal_tick.emit(tick)

    def update_tick(self, tick: TickData):
        """"""
        self.lp_label.setText(str(tick.last_price))
        self.bp1_label.setText(str(tick.bid_price_1))
        self.bv1_label.setText(str(tick.bid_volume_1))
        self.ap1_label.setText(str(tick.ask_price_1))
        self.av1_label.setText(str(tick.ask_volume_1))

        if tick.pre_close:
            r = (tick.last_price / tick.pre_close - 1) * 100
            self.return_label.setText(f"{r:.2f}%")

        if tick.bid_price_2:
            self.bp2_label.setText(str(tick.bid_price_2))
            self.bv2_label.setText(str(tick.bid_volume_2))
            self.ap2_label.setText(str(tick.ask_price_2))
            self.av2_label.setText(str(tick.ask_volume_2))

            self.bp3_label.setText(str(tick.bid_price_3))
            self.bv3_label.setText(str(tick.bid_volume_3))
            self.ap3_label.setText(str(tick.ask_price_3))
            self.av3_label.setText(str(tick.ask_volume_3))

            self.bp4_label.setText(str(tick.bid_price_4))
            self.bv4_label.setText(str(tick.bid_volume_4))
            self.ap4_label.setText(str(tick.ask_price_4))
            self.av4_label.setText(str(tick.ask_volume_4))

            self.bp5_label.setText(str(tick.bid_price_5))
            self.bv5_label.setText(str(tick.bid_volume_5))
            self.ap5_label.setText(str(tick.ask_price_5))
            self.av5_label.setText(str(tick.ask_volume_5))

    def clear_data(self):
        """"""
        self.lp_label.setText("-")
        self.return_label.setText("-")
        self.bp1_label.setText("-")
        self.bv1_label.setText("-")
        self.ap1_label.setText("-")
        self.av1_label.setText("-")

        self.bp2_label.setText("-")
        self.bv2_label.setText("-")
        self.ap2_label.setText("-")
        self.av2_label.setText("-")

        self.bp3_label.setText("-")
        self.bv3_label.setText("-")
        self.ap3_label.setText("-")
        self.av3_label.setText("-")

        self.bp4_label.setText("-")
        self.bv4_label.setText("-")
        self.ap4_label.setText("-")
        self.av4_label.setText("-")

        self.bp5_label.setText("-")
        self.bv5_label.setText("-")
        self.ap5_label.setText("-")
        self.av5_label.setText("-")
