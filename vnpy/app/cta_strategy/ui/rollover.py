from datetime import datetime

from vnpy.trader.engine import MainEngine
from vnpy.trader.constant import OrderType
from vnpy.trader.object import ContractData, OrderRequest, TickData
from vnpy.trader.object import Direction, Offset
from vnpy.trader.ui import QtWidgets
from vnpy.trader.converter import PositionHolding

from ..engine import CtaEngine, APP_NAME
from ..template import CtaTemplate


class RolloverTool(QtWidgets.QDialog):
    """"""

    def __init__(self, cta_engine: CtaEngine) -> None:
        """"""
        super().__init__()

        self.cta_engine = cta_engine
        self.main_engine: MainEngine = cta_engine.main_engine

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("移仓助手")

        self.old_symbol_combo = QtWidgets.QComboBox()
        self.old_symbol_combo.addItems(
            self.cta_engine.symbol_strategy_map.keys()
        )

        self.new_symbol_line = QtWidgets.QLineEdit()

        self.payup_spin = QtWidgets.QSpinBox()
        self.payup_spin.setMinimum(5)

        self.log_edit = QtWidgets.QTextEdit()
        self.log_edit.setReadOnly(True)

        button = QtWidgets.QPushButton("移仓")
        button.clicked.connect(self.roll_all)

        form = QtWidgets.QFormLayout()
        form.addRow("移仓合约", self.old_symbol_combo)
        form.addRow("目标合约", self.new_symbol_line)
        form.addRow("委托超价", self.payup_spin)

        form.addRow(button)
        form.addRow(self.log_edit)

        self.setLayout(form)

    def write_log(self, text: str) -> None:
        """"""
        now = datetime.now()
        text = now.strftime("%H:%M:%S\t") + text
        self.log_edit.append(text)

    def roll_all(self) -> None:
        """"""
        old_symbol = self.old_symbol_combo.currentText()
        new_symbol = self.new_symbol_line.text()
        payup = self.payup_spin.value()

        self.roll_position(old_symbol, new_symbol, payup)

        strategies = self.cta_engine.symbol_strategy_map[old_symbol]
        for strategy in strategies:
            self.roll_strategy(strategy, new_symbol, payup)

    def roll_position(self, old_symbol: str, new_symbol: str, payup: int) -> None:
        """"""
        converter = self.cta_engine.offset_converter
        holding: PositionHolding = converter.get_position_holding(old_symbol)

        # Roll long position
        if holding.long_pos:
            self.send_order(
                old_symbol,
                Direction.SHORT,
                Offset.CLOSE,
                payup,
                holding.long_pos
            )

            self.send_order(
                new_symbol,
                Direction.LONG,
                Offset.OPEN,
                payup,
                holding.long_pos
            )

        # Roll short postiion
        if holding.short_pos:
            self.send_order(
                old_symbol,
                Direction.LONG,
                Offset.CLOSE,
                payup,
                holding.short_pos
            )

            self.send_order(
                new_symbol,
                Direction.SHORT,
                Offset.OPEN,
                payup,
                holding.short_pos
            )

    def roll_strategy(self, strategy: CtaTemplate, vt_symbol: str) -> None:
        """"""
        if not strategy.inited:
            self.write_log(f"无法执行移仓，请先初始化策略{strategy.strategy_name}")
            return

        # Save data of old strategy
        pos = strategy.pos
        name = strategy.strategy_name
        parameters = strategy.get_parameters()

        # Remove old strategy
        self.cta_engine.remove_strategy(name)

        self.write_log(f"移除老策略{name}[{strategy.vt_symbol}]")

        # Add new strategy
        self.cta_engine.add_strategy(
            strategy.__class__.__name__,
            name,
            vt_symbol,
            parameters
        )
        self.write_log(f"创建策略{name}[{vt_symbol}]")

        # Init new strategy
        self.cta_engine.init_strategy(name)
        self.write_log(f"初始化策略{name}[{vt_symbol}]")

        # Update pos to new strategy
        new_strategy: CtaTemplate = self.cta_engine.strategies[name]
        new_strategy.pos = pos
        new_strategy.sync_data()
        self.write_log(f"更新策略仓位{name}[{vt_symbol}]")

    def send_order(
        self,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        payup: int,
        volume: float,
    ):
        """
        Send a new order to server.
        """
        contract: ContractData = self.main_engine.get_contract(vt_symbol)
        tick: TickData = self.main_engine.get_tick(vt_symbol)

        if direction == Direction.LONG:
            price = tick.ask_price_1 + contract.pricetick * payup
        else:
            price = tick.bid_price_1 - contract.pricetick * payup

        original_req: OrderRequest = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            offset=offset,
            type=OrderType.LIMIT,
            price=price,
            volume=volume,
            reference=f"{APP_NAME}_Rollover"
        )

        req_list = self.offset_converter.convert_order_request(original_req, False, False)

        vt_orderids = []
        for req in req_list:
            vt_orderid = self.main_engine.send_order(req, contract.gateway_name)
            if not vt_orderid:
                continue

            vt_orderids.append(vt_orderid)
            self.offset_converter.update_order_request(req, vt_orderid)

            msg = f"发出委托{vt_symbol}，{direction.value} {offset.value}，{volume}@{price}"
            self.write_log(msg)
