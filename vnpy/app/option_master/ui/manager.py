from typing import Dict, List, Tuple
from copy import copy
from functools import partial

from vnpy.event import Event
from vnpy.trader.ui import QtWidgets, QtCore
from vnpy.trader.event import EVENT_TICK, EVENT_TIMER

from ..engine import OptionEngine
from ..base import EVENT_OPTION_ALGO_PRICING, EVENT_OPTION_ALGO_TRADING
from .monitor import (
    MonitorCell, IndexCell, BidCell, AskCell, PosCell,
    COLOR_WHITE, COLOR_BLACK
)


class AlgoSpinBox(QtWidgets.QSpinBox):
    """"""

    def __init__(self):
        """"""
        super().__init__()

        self.setMaximum(999999)
        self.setMinimum(-999999)

    def get_value(self):
        """"""
        return self.value()


class AlgoPositiveSpinBox(AlgoSpinBox):
    """"""

    def __init__(self):
        """"""
        super().__init__()

        self.setMinimum(0)


class AlgoDoubleSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    def __init__(self):
        """"""
        super().__init__()

        self.setDecimals(1)
        self.setMaximum(9999.9)
        self.setMinimum(0)

    def get_value(self):
        """"""
        return self.value()


class AlgoCheckBox(QtWidgets.QCheckBox):
    """"""

    def __init__(self):
        """"""
        super().__init__()

    def get_value(self):
        """"""
        return self.isChecked()


class AlgoPricingButton(QtWidgets.QPushButton):
    """"""

    def __init__(self, vt_symbol: str, manager: "ElectronicEyeManager"):
        """"""
        super().__init__()

        self.vt_symbol = vt_symbol
        self.manager = manager

        self.active = False
        self.setText("N")
        self.clicked.connect(self.on_clicked)

    def on_clicked(self):
        """"""
        if self.active:
            self.manager.stop_algo_pricing(self.vt_symbol)
        else:
            self.manager.start_algo_pricing(self.vt_symbol)

    def update_status(self, active: bool):
        """"""
        self.active = active

        if active:
            self.setText("Y")
        else:
            self.setText("N")


class AlgoTradingButton(QtWidgets.QPushButton):
    """"""

    def __init__(self, vt_symbol: str, manager: "ElectronicEyeManager"):
        """"""
        super().__init__()

        self.vt_symbol = vt_symbol
        self.manager = manager

        self.active = False
        self.setText("N")
        self.clicked.connect(self.change_status)

    def change_status(self):
        """"""
        if self.active:
            self.manager.stop_algo_trading(self.vt_symbol)
            self.active = False
            self.setText("N")
        else:
            self.manager.start_algo_trading(self.vt_symbol)
            self.active = True
            self.setText("Y")


class ElectronicEyeManager(QtWidgets.QTableWidget):
    """"""

    signal_tick = QtCore.pyqtSignal(Event)
    signal_pricing = QtCore.pyqtSignal(Event)
    signal_trading = QtCore.pyqtSignal(Event)

    headers: List[Dict] = [
        {"name": "bid_volume", "display": "买量", "cell": BidCell},
        {"name": "bid_price", "display": "买价", "cell": BidCell},
        {"name": "ask_price", "display": "卖价", "cell": AskCell},
        {"name": "ask_volume", "display": "卖量", "cell": AskCell},
        {"name": "algo_bid_price", "display": "目标\n买价", "cell": BidCell},
        {"name": "algo_ask_price", "display": "目标\n卖价", "cell": AskCell},
        {"name": "algo_spread", "display": "价差", "cell": MonitorCell},
        {"name": "theo_price", "display": "理论价", "cell": MonitorCell},
        {"name": "pricing_impv", "display": "定价\n隐波", "cell": MonitorCell},
        {"name": "net_pos", "display": "净持仓", "cell": PosCell},

        {"name": "price_spread", "display": "价格\n价差", "cell": AlgoDoubleSpinBox},
        {"name": "volatility_spread", "display": "隐波\n价差", "cell": AlgoDoubleSpinBox},
        {"name": "max_pos", "display": "持仓\n上限", "cell": AlgoPositiveSpinBox},
        {"name": "target_pos", "display": "目标\n持仓", "cell": AlgoSpinBox},
        {"name": "max_order_size", "display": "最大\n委托", "cell": AlgoPositiveSpinBox},
        {"name": "long_allowed", "display": "买入", "cell": AlgoCheckBox},
        {"name": "short_allowed", "display": "卖出", "cell": AlgoCheckBox},
        {"name": "pricing_active", "display": "定价", "cell": AlgoPricingButton},
        {"name": "trading_active", "display": "交易", "cell": AlgoTradingButton},

    ]

    def __init__(self, option_engine: OptionEngine, portfolio_name: str):
        """"""
        super().__init__()

        self.option_engine = option_engine
        self.event_engine = option_engine.event_engine
        self.algo_engine = option_engine.algo_engine
        self.portfolio_name = portfolio_name

        self.cells: Dict[str, Dict] = {}

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        self.setWindowTitle("电子眼")
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

        # Set table row and column numbers
        portfolio = self.option_engine.get_portfolio(self.portfolio_name)

        row_count = 0
        for chain in portfolio.chains.values():
            row_count += (1 + len(chain.indexes))
        self.setRowCount(row_count)

        column_count = len(self.headers) * 2 + 1
        self.setColumnCount(column_count)

        call_labels = [d["display"] for d in self.headers]
        put_labels = copy(call_labels)
        put_labels.reverse()
        labels = call_labels + ["行权价"] + put_labels
        self.setHorizontalHeaderLabels(labels)

        # Init cells
        strike_column = len(self.headers)
        current_row = 0

        chain_symbols = list(portfolio.chains.keys())
        chain_symbols.sort()

        for chain_symbol in chain_symbols:
            chain = portfolio.get_chain(chain_symbol)

            self.setItem(
                current_row,
                strike_column,
                IndexCell(chain.chain_symbol.split(".")[0])
            )

            for index in chain.indexes:
                call = chain.calls[index]
                put = chain.puts[index]

                current_row += 1

                # Call cells
                call_cells = {}

                for column, d in enumerate(self.headers):
                    cell_type = d["cell"]

                    if issubclass(cell_type, QtWidgets.QPushButton):
                        cell = cell_type(call.vt_symbol, self)
                    else:
                        cell = cell_type()

                    call_cells[d["name"]] = cell

                    if isinstance(cell, QtWidgets.QTableWidgetItem):
                        self.setItem(current_row, column, cell)
                    else:
                        self.setCellWidget(current_row, column, cell)

                self.cells[call.vt_symbol] = call_cells

                # Put cells
                put_cells = {}
                put_headers = copy(self.headers)
                put_headers.reverse()

                for column, d in enumerate(put_headers):
                    column += (strike_column + 1)

                    cell_type = d["cell"]

                    if issubclass(cell_type, QtWidgets.QPushButton):
                        cell = cell_type(put.vt_symbol, self)
                    else:
                        cell = cell_type()

                    put_cells[d["name"]] = cell

                    if isinstance(cell, QtWidgets.QTableWidgetItem):
                        self.setItem(current_row, column, cell)
                    else:
                        self.setCellWidget(current_row, column, cell)

                self.cells[put.vt_symbol] = put_cells

                # Strike cell
                index_cell = IndexCell(str(call.chain_index))
                self.setItem(current_row, strike_column, index_cell)

            # Move to next row
            current_row += 1

    def register_event(self):
        """"""
        self.signal_pricing.connect(self.process_pricing_event)
        self.signal_trading.connect(self.process_trading_event)
        self.signal_tick.connect(self.process_tick_event)

        self.event_engine.register(
            EVENT_OPTION_ALGO_PRICING,
            self.signal_pricing.emit
        )
        self.event_engine.register(
            EVENT_OPTION_ALGO_TRADING,
            self.signal_trading.emit
        )
        self.event_engine.register(
            EVENT_TICK,
            self.signal_tick.emit
        )

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data
        cells = self.cells.get(tick.vt_symbol, None)
        if not cells:
            return

        cells["bid_price"].setText(str(tick.bid_price_1))
        cells["ask_price"].setText(str(tick.ask_price_1))
        cells["bid_volume"].setText(str(tick.bid_volume_1))
        cells["ask_volume"].setText(str(tick.ask_volume_1))

    def process_pricing_event(self, event: Event):
        """"""
        algo = event.data
        cells = self.cells[algo.vt_symbol]

        if algo.theo_price:
            cells["algo_bid_price"].setText(str(algo.algo_bid_price))
            cells["algo_ask_price"].setText(str(algo.algo_ask_price))
            cells["algo_spread"].setText(str(algo.algo_spread))
            cells["theo_price"].setText(str(algo.theo_price))
            cells["pricing_impv"].setText(str(algo.pricing_impv))
        else:
            cells["algo_bid_price"].setText("")
            cells["algo_ask_price"].setText("")
            cells["algo_spread"].setText("")
            cells["theo_price"].setText("")
            cells["pricing_impv"].setText("")

    def process_trading_event(self, event: Event):
        """"""
        algo = event.data

        cells = self.cells[algo.vt_symbol]
        cells["net_pos"].setText(str(algo.net_pos))

    def start_algo_pricing(self, vt_symbol: str):
        """"""
        cells = self.cells[vt_symbol]

        params = {}
        for name in ["price_spread", "volatility_spread"]:
            params[name] = cells[name].get_value()

        self.algo_engine.start_algo_pricing(vt_symbol, params)

    def stop_algo_pricing(self, vt_symbol: str):
        """"""
        self.algo_engine.stop_algo_pricing(vt_symbol)

    def start_algo_trading(self, vt_symbol: str):
        """"""
        cells = self.cells[vt_symbol]

        params = {}
        for name in [
            "long_allowed",
            "short_allowed",
            "max_pos",
            "target_pos",
            "max_order_size"
        ]:
            params[name] = cells[name].get_value()

        self.algo_engine.start_algo_trading(vt_symbol, params)

    def stop_algo_trading(self, vt_symbol: str):
        """"""
        self.algo_engine.stop_algo_trading(vt_symbol)

    def show(self):
        """"""
        self.algo_engine.init_engine(self.portfolio_name)
        self.resizeColumnsToContents()
        super().showMaximized()


class VolatilityDoubleSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    def __init__(self):
        """"""
        super().__init__()

        self.setDecimals(1)
        self.setSuffix("%")
        self.setMaximum(200.0)
        self.setMinimum(0)

    def get_value(self):
        """"""
        return self.value()


class PricingVolatilityManager(QtWidgets.QTabWidget):
    """"""

    signal_timer = QtCore.pyqtSignal(Event)

    def __init__(self, option_engine: OptionEngine, portfolio_name: str):
        """"""
        super().__init__()

        self.option_engine = option_engine
        self.event_engine = option_engine.event_engine
        self.portfolio = option_engine.get_portfolio(portfolio_name)

        self.cells: Dict[Tuple, Dict] = {}
        self.chain_symbols: List[str] = []
        self.chain_atm_index: Dict[str, str] = {}

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        self.setWindowTitle("波动率管理")

        self.chain_symbols = list(self.portfolio.chains.keys())
        self.chain_symbols.sort()

        for chain_symbol in self.chain_symbols:
            chain = self.portfolio.get_chain(chain_symbol)

            table = QtWidgets.QTableWidget()
            table.setEditTriggers(table.NoEditTriggers)
            table.verticalHeader().setVisible(False)
            table.setColumnCount(4)
            table.setRowCount(len(chain.indexes))
            table.setHorizontalHeaderLabels([
                "行权价",
                "中值隐波",
                "定价隐波",
                "拟合"
            ])
            table.horizontalHeader().setSectionResizeMode(
                QtWidgets.QHeaderView.Stretch
            )

            for row, index in enumerate(chain.indexes):
                index_cell = IndexCell(index)
                mid_impv_cell = MonitorCell("")

                set_func = partial(
                    self.set_pricing_impv,
                    chain_symbol=chain_symbol,
                    index=index
                )
                pricing_impv_spin = VolatilityDoubleSpinBox()
                pricing_impv_spin.valueChanged.connect(set_func)

                check = QtWidgets.QCheckBox()

                table.setItem(row, 0, index_cell)
                table.setItem(row, 1, mid_impv_cell)
                table.setCellWidget(row, 2, pricing_impv_spin)
                table.setCellWidget(row, 3, check)

                cells = {
                    "mid_impv": mid_impv_cell,
                    "pricing_impv": pricing_impv_spin,
                    "check": check
                }

                self.cells[(chain_symbol, index)] = cells

            reset_func = partial(self.reset_pricing_impv, chain_symbol=chain_symbol)
            button_reset = QtWidgets.QPushButton("重置")
            button_reset.clicked.connect(reset_func)

            increase_func = partial(self.increase_pricing_impv, chain_symbol=chain_symbol)
            button_increase = QtWidgets.QPushButton("+0.1%")
            button_increase.clicked.connect(increase_func)

            decrease_func = partial(self.decrease_pricing_impv, chain_symbol=chain_symbol)
            button_decrease = QtWidgets.QPushButton("-0.1%")
            button_decrease.clicked.connect(decrease_func)

            hbox = QtWidgets.QHBoxLayout()
            hbox.addWidget(button_reset)
            hbox.addWidget(button_increase)
            hbox.addWidget(button_decrease)

            vbox = QtWidgets.QVBoxLayout()
            vbox.addLayout(hbox)
            vbox.addWidget(table)

            chain_widget = QtWidgets.QWidget()
            chain_widget.setLayout(vbox)
            self.addTab(chain_widget, chain_symbol)

            self.update_pricing_impv(chain_symbol)

            self.default_foreground = mid_impv_cell.foreground()
            self.default_background = mid_impv_cell.background()

    def register_event(self):
        """"""
        self.signal_timer.connect(self.process_timer_event)

        self.event_engine.register(EVENT_TIMER, self.signal_timer.emit)

    def process_timer_event(self, event: Event):
        """"""
        for chain_symbol in self.chain_symbols:
            self.update_mid_impv(chain_symbol)

    def reset_pricing_impv(self, chain_symbol: str):
        """
        Set pricing impv to the otm mid impv of each strike price.
        """
        chain = self.portfolio.get_chain(chain_symbol)
        atm_index = chain.atm_index

        for index in chain.indexes:
            call = chain.calls[index]
            put = chain.puts[index]

            if index >= atm_index:
                otm = call
            else:
                otm = put

            call.pricing_impv = otm.mid_impv
            put.pricing_impv = otm.mid_impv

        self.update_pricing_impv(chain_symbol)

    def increase_pricing_impv(self, chain_symbol: str):
        """
        Increase pricing impv of all options within a chain by 0.1%.
        """
        chain = self.portfolio.get_chain(chain_symbol)

        for option in chain.options.values():
            option.pricing_impv += 0.001

        self.update_pricing_impv(chain_symbol)

    def decrease_pricing_impv(self, chain_symbol: str):
        """
        Decrease pricing impv of all options within a chain by 0.1%.
        """
        chain = self.portfolio.get_chain(chain_symbol)

        for option in chain.options.values():
            option.pricing_impv -= 0.001

        self.update_pricing_impv(chain_symbol)

    def set_pricing_impv(self, value: float, chain_symbol: str, index: str):
        """"""
        new_impv = value / 100

        chain = self.portfolio.get_chain(chain_symbol)

        call = chain.calls[index]
        call.pricing_impv = new_impv

        put = chain.puts[index]
        put.pricing_impv = new_impv

    def update_pricing_impv(self, chain_symbol: str):
        """"""
        chain = self.portfolio.get_chain(chain_symbol)
        atm_index = chain.atm_index

        for index in chain.indexes:
            if index >= atm_index:
                otm = chain.calls[index]
            else:
                otm = chain.puts[index]

            value = round(otm.pricing_impv * 100, 1)
            cells = self.cells[(chain_symbol, index)]
            cells["pricing_impv"].setValue(value)

    def update_mid_impv(self, chain_symbol: str):
        """"""
        chain = self.portfolio.get_chain(chain_symbol)
        atm_index = chain.atm_index

        for index in chain.indexes:
            if index >= atm_index:
                otm = chain.calls[index]
            else:
                otm = chain.puts[index]

            cells = self.cells[(chain_symbol, index)]
            cells["mid_impv"].setText(f"{otm.mid_impv:.1%}")

        current_atm_index = self.chain_atm_index.get(chain_symbol, "")
        if current_atm_index == atm_index:
            return
        self.chain_atm_index[chain_symbol] = atm_index

        if current_atm_index:
            old_cells = self.cells[(chain_symbol, current_atm_index)]
            old_cells["mid_impv"].setForeground(self.default_foreground)
            old_cells["mid_impv"].setBackground(self.default_background)

        new_cells = self.cells[(chain_symbol, atm_index)]
        new_cells["mid_impv"].setForeground(COLOR_BLACK)
        new_cells["mid_impv"].setBackground(COLOR_WHITE)
