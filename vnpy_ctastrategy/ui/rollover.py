from datetime import datetime
from time import sleep
from typing import TYPE_CHECKING
from copy import copy

from vnpy.trader.engine import MainEngine
from vnpy.trader.constant import OrderType
from vnpy.trader.object import ContractData, OrderRequest, SubscribeRequest, TickData
from vnpy.trader.object import Direction, Offset
from vnpy.trader.ui import QtWidgets
from vnpy.trader.converter import OffsetConverter, PositionHolding

from ..engine import CtaEngine, APP_NAME
from ..template import CtaTemplate
from ..locale import _

if TYPE_CHECKING:
    from .widget import CtaManager


class RolloverTool(QtWidgets.QDialog):
    """"""

    def __init__(self, cta_manager: "CtaManager") -> None:
        """"""
        super().__init__()

        self.cta_manager: CtaManager = cta_manager
        self.cta_engine: CtaEngine = cta_manager.cta_engine
        self.main_engine: MainEngine = cta_manager.main_engine

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(_("移仓助手"))

        old_symbols: list = []
        for vt_symbol, strategies in self.cta_engine.symbol_strategy_map.items():
            if strategies:
                old_symbols.append(vt_symbol)
        self.old_symbol_combo: QtWidgets.QComboBox = QtWidgets.QComboBox()
        self.old_symbol_combo.addItems(old_symbols)

        self.new_symbol_line: QtWidgets.QLineEdit = QtWidgets.QLineEdit()

        self.payup_spin: QtWidgets.QSpinBox = QtWidgets.QSpinBox()
        self.payup_spin.setMinimum(5)

        self.max_volume_spin: QtWidgets.QSpinBox = QtWidgets.QSpinBox()
        self.max_volume_spin.setMinimum(1)
        self.max_volume_spin.setMaximum(10000)
        self.max_volume_spin.setValue(100)

        self.log_edit: QtWidgets.QTextEdit = QtWidgets.QTextEdit()
        self.log_edit.setReadOnly(True)
        self.log_edit.setMinimumWidth(500)

        button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("移仓"))
        button.clicked.connect(self.roll_all)
        button.setFixedHeight(button.sizeHint().height() * 2)

        form: QtWidgets.QFormLayout = QtWidgets.QFormLayout()
        form.addRow(_("移仓合约"), self.old_symbol_combo)
        form.addRow(_("目标合约"), self.new_symbol_line)
        form.addRow(_("委托超价"), self.payup_spin)
        form.addRow(_("单笔上限"), self.max_volume_spin)
        form.addRow(button)

        hbox: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox.addLayout(form)
        hbox.addWidget(self.log_edit)
        self.setLayout(hbox)

    def write_log(self, text: str) -> None:
        """"""
        now: datetime = datetime.now()
        text = now.strftime("%H:%M:%S\t") + text
        self.log_edit.append(text)

    def subscribe(self, vt_symbol: str) -> None:
        """"""
        contract: ContractData | None = self.main_engine.get_contract(vt_symbol)
        if not contract:
            return

        req: SubscribeRequest = SubscribeRequest(contract.symbol, contract.exchange)
        self.main_engine.subscribe(req, contract.gateway_name)

    def roll_all(self) -> None:
        """"""
        old_symbol: str = self.old_symbol_combo.currentText()

        new_symbol: str = self.new_symbol_line.text()
        self.subscribe(new_symbol)
        sleep(1)

        new_tick: TickData | None = self.main_engine.get_tick(new_symbol)
        if not new_tick:
            self.write_log(_("无法获取目标合约{}的盘口数据，请先订阅行情").format(new_symbol))
            return

        payup: int = self.payup_spin.value()

        # Check all strategies inited (pos data loaded from disk json file) and not trading
        strategies: list = self.cta_engine.symbol_strategy_map[old_symbol]
        for strategy in strategies:
            if not strategy.inited:
                self.write_log(_("策略{}尚未初始化，无法执行移仓").format(strategy.strategy_name))
                return

            if strategy.trading:
                self.write_log(_("策略{}正在运行中，无法执行移仓").format(strategy.strategy_name))
                return

        # Roll position first
        self.roll_position(old_symbol, new_symbol, payup)

        # Then roll strategy
        for strategy in copy(strategies):
            self.roll_strategy(strategy, new_symbol)

        # Disable self
        self.setEnabled(False)

    def roll_position(self, old_symbol: str, new_symbol: str, payup: int) -> None:
        """"""
        contract: ContractData = self.main_engine.get_contract(old_symbol)                  # type: ignore
        converter: OffsetConverter = self.main_engine.get_converter(contract.gateway_name)  # type: ignore
        holding: PositionHolding = converter.get_position_holding(old_symbol)               # type: ignore

        # Roll long position
        if holding.long_pos:
            volume: float = holding.long_pos

            self.send_order(
                old_symbol,
                Direction.SHORT,
                Offset.CLOSE,
                payup,
                volume
            )

            self.send_order(
                new_symbol,
                Direction.LONG,
                Offset.OPEN,
                payup,
                volume
            )

        # Roll short postiion
        if holding.short_pos:
            volume = holding.short_pos

            self.send_order(
                old_symbol,
                Direction.LONG,
                Offset.CLOSE,
                payup,
                volume
            )

            self.send_order(
                new_symbol,
                Direction.SHORT,
                Offset.OPEN,
                payup,
                volume
            )

    def roll_strategy(self, strategy: CtaTemplate, vt_symbol: str) -> None:
        """"""
        if not strategy.inited:
            self.cta_engine._init_strategy(strategy.strategy_name)

        # Save data of old strategy
        pos = strategy.pos
        name: str = strategy.strategy_name
        parameters: dict = strategy.get_parameters()

        # Remove old strategy
        result: bool = self.cta_engine.remove_strategy(name)
        if result:
            self.cta_manager.remove_strategy(name)

        self.write_log(_("移除老策略{}[{}]").format(name, strategy.vt_symbol))

        # Add new strategy
        self.cta_engine.add_strategy(
            strategy.__class__.__name__,
            name,
            vt_symbol,
            parameters
        )
        self.write_log(_("创建策略{}[{}]").format(name, vt_symbol))

        # Init new strategy
        self.cta_engine.init_strategy(name)
        self.write_log(_("初始化策略{}[{}]").format(name, vt_symbol))

        # Update pos to new strategy
        new_strategy: CtaTemplate = self.cta_engine.strategies[name]
        new_strategy.pos = pos
        new_strategy.sync_data()
        self.write_log(_("更新策略仓位{}[{}]").format(name, vt_symbol))

    def send_order(
        self,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        payup: int,
        volume: float,
    ) -> None:
        """
        Send a new order to server.
        """
        max_volume: int = self.max_volume_spin.value()

        contract: ContractData | None = self.main_engine.get_contract(vt_symbol)
        tick: TickData | None = self.main_engine.get_tick(vt_symbol)

        if not contract or not tick:
            return

        if direction == Direction.LONG:
            price = tick.ask_price_1 + contract.pricetick * payup
        else:
            price = tick.bid_price_1 - contract.pricetick * payup

        while True:
            order_volume: float = min(volume, max_volume)

            original_req: OrderRequest = OrderRequest(
                symbol=contract.symbol,
                exchange=contract.exchange,
                direction=direction,
                offset=offset,
                type=OrderType.LIMIT,
                price=price,
                volume=order_volume,
                reference=f"{APP_NAME}_Rollover"
            )

            req_list: list[OrderRequest] = self.main_engine.convert_order_request(
                original_req,
                contract.gateway_name,
                False,
                False
            )

            vt_orderids: list = []
            for req in req_list:
                vt_orderid: str = self.main_engine.send_order(req, contract.gateway_name)
                if not vt_orderid:
                    continue

                vt_orderids.append(vt_orderid)
                self.main_engine.update_order_request(req, vt_orderid, contract.gateway_name)

                msg: str = _("发出委托{}，{} {}，{}@{}").format(
                    vt_symbol, direction.value, offset.value, volume, price
                )
                self.write_log(msg)

            # Check whether all volume sent
            volume = volume - order_volume
            if not volume:
                break
