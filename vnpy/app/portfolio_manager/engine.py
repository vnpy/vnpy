from datetime import datetime
from typing import Dict, List, Set
from collections import defaultdict
from copy import copy

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (
    EVENT_TRADE, EVENT_ORDER, EVENT_TICK, EVENT_CONTRACT, EVENT_TIMER
)
from vnpy.trader.constant import Direction, Offset, OrderType
from vnpy.trader.object import (
    OrderRequest, CancelRequest, SubscribeRequest,
    OrderData, TradeData, TickData, ContractData
)
from vnpy.trader.utility import load_json, save_json


APP_NAME = "PortfolioManager"

EVENT_PORTFOLIO_UPDATE = "ePortfioUpdate"
EVENT_PORTFOLIO_ORDER = "ePortfioOrder"
EVENT_PORTFOLIO_TRADE = "ePortfioTrade"


class PortfolioEngine(BaseEngine):
    """"""
    setting_filename = "portfolio_manager_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.inited = False

        self.strategies: Dict[str, PortfolioStrategy] = {}
        self.symbol_strategy_map: Dict[str, List] = defaultdict(list)
        self.order_strategy_map: Dict[str, PortfolioStrategy] = {}
        self.active_orders: Set[str] = set()

        self.register_event()

    def init_engine(self):
        """"""
        if self.inited:
            return
        self.inited = True

        self.load_setting()

    def load_setting(self):
        """"""
        setting: dict = load_json(self.setting_filename)

        for d in setting.values():
            self.add_strategy(
                d["name"],
                d["vt_symbol"],
                d["size"],
                d["net_pos"],
                d["open_price"],
                d["last_price"],
                d["create_time"],
                d["note_text"],
            )

    def save_setting(self):
        """"""
        setting: dict = {}

        for strategy in self.strategies.values():
            setting[strategy.name] = {
                "name": strategy.name,
                "vt_symbol": strategy.vt_symbol,
                "size": strategy.size,
                "net_pos": strategy.net_pos,
                "open_price": strategy.open_price,
                "last_price": strategy.last_price,
                "create_time": strategy.create_time,
                "note_text": strategy.note_text,
            }

        save_json(self.setting_filename, setting)

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_timer_event(self, event: Event):
        """"""
        if self.inited:
            self.save_setting()

    def process_contract_event(self, event: Event):
        """"""
        contract: ContractData = event.data

        if contract.vt_symbol in self.symbol_strategy_map:
            self.subscribe_data(contract.vt_symbol)

    def process_order_event(self, event: Event):
        """"""
        order: OrderData = event.data

        if order.vt_orderid not in self.active_orders:
            return

        if not order.is_active():
            self.active_orders.remove(order.vt_orderid)

        strategy: PortfolioStrategy = self.order_strategy_map[order.vt_orderid]
        strategy_order = copy(order)
        strategy_order.gateway_name = strategy.name

        event = Event(EVENT_PORTFOLIO_ORDER, strategy_order)
        self.event_engine.put(event)

    def process_trade_event(self, event: Event):
        """"""
        trade: TradeData = event.data

        strategy: PortfolioStrategy = self.order_strategy_map.get(
            trade.vt_orderid)
        if strategy:
            strategy.update_trade(
                trade.direction,
                trade.volume,
                trade.price
            )

            self.put_strategy_event(strategy.name)

            strategy_trade = copy(trade)
            strategy_trade.gateway_name = strategy.name
            event = Event(EVENT_PORTFOLIO_TRADE, strategy_trade)
            self.event_engine.put(event)

            self.save_setting()

    def process_tick_event(self, event: Event):
        """"""
        tick: TickData = event.data

        strategies: List = self.symbol_strategy_map[tick.vt_symbol]
        for strategy in strategies:
            strategy.update_price(tick.last_price)

            self.put_strategy_event(strategy.name)

    def add_strategy(
        self,
        name: str,
        vt_symbol: str,
        size: int = 0,
        net_pos: int = 0,
        open_price: float = 0,
        last_price: float = 0,
        create_time: str = "",
        note_text: str = ""
    ):
        """"""
        if name in self.strategies:
            return False

        if not size:
            contract = self.main_engine.get_contract(vt_symbol)
            if not contract:
                return False
            size = contract.size

        strategy = PortfolioStrategy(
            name,
            vt_symbol,
            size,
            net_pos,
            open_price,
            last_price,
            create_time,
            note_text
        )

        self.strategies[strategy.name] = strategy
        self.symbol_strategy_map[strategy.vt_symbol].append(strategy)
        self.save_setting()

        self.subscribe_data(vt_symbol)
        self.put_strategy_event(name)

        return True

    def remove_strategy(self, name: str):
        """"""
        if name not in self.strategies:
            return False

        strategy = self.strategies.pop(name)
        self.symbol_strategy_map[strategy.vt_symbol].remove(strategy)

        return True

    def subscribe_data(self, vt_symbol: str):
        """"""
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            return

        req = SubscribeRequest(
            symbol=contract.symbol,
            exchange=contract.exchange
        )
        self.main_engine.subscribe(req, contract.gateway_name)

    def send_order(
        self,
        name: str,
        price: float,
        volume: int,
        direction: Direction,
        offset: Offset = Offset.NONE
    ):
        """"""
        strategy = self.strategies[name]
        vt_symbol = strategy.vt_symbol

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            return False

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            type=OrderType.LIMIT,
            volume=volume,
            price=price,
            offset=offset
        )
        vt_orderid = self.main_engine.send_order(req, contract.gateway_name)

        self.order_strategy_map[vt_orderid] = strategy
        self.active_orders.add(vt_orderid)

        return True

    def cancel_order(self, vt_orderid: str):
        """"""
        if vt_orderid not in self.order_strategy_map:
            return False

        order = self.main_engine.get_order(vt_orderid)

        req = CancelRequest(
            orderid=order.orderid,
            symbol=order.symbol,
            exchange=order.exchange
        )
        self.main_engine.cancel_order(req, order.gateway_name)

        return True

    def cancel_all(self, name: str):
        """"""
        for vt_orderid in self.active_orders:
            strategy = self.order_strategy_map[vt_orderid]
            if strategy.name == name:
                self.cancel_order(vt_orderid)

    def put_strategy_event(self, name: str):
        """"""
        strategy = self.strategies[name]
        event = Event(EVENT_PORTFOLIO_UPDATE, strategy)
        self.event_engine.put(event)

    def stop(self):
        """"""
        self.save_setting()


class PortfolioStrategy:
    """"""

    def __init__(
        self,
        name: str,
        vt_symbol: str,
        size: int,
        net_pos: int,
        open_price: float,
        last_price: float,
        create_time: str,
        note_text: str
    ):
        """"""
        self.name: str = name
        self.vt_symbol: str = vt_symbol
        self.size: int = size

        self.net_pos: int = net_pos
        self.open_price: float = open_price
        self.last_price: float = last_price

        self.pos_pnl: float = 0
        self.realized_pnl: float = 0

        self.create_time: str = ""
        if create_time:
            self.create_time = create_time
        else:
            self.create_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        self.note_text: str = note_text

        self.calculate_pnl()

    def calculate_pnl(self):
        """"""
        self.pos_pnl = (self.last_price - self.open_price) * \
            self.net_pos * self.size

    def update_trade(
        self,
        trade_direction: Direction,
        trade_volume: int,
        trade_price: float
    ):
        """"""
        old_cost = self.net_pos * self.open_price

        if trade_direction == Direction.LONG:
            new_pos = self.net_pos + trade_volume

            # Open new long position
            if self.net_pos >= 0:
                new_cost = old_cost + trade_volume * trade_price
                self.open_price = new_cost / new_pos
            # Close short position
            else:
                close_volume = min(trade_volume, abs(self.net_pos))
                realized_pnl = (trade_price - self.open_price) * \
                    close_volume * (-1)
                self.realized_pnl += realized_pnl

                if new_pos > 0:
                    self.open_price = trade_price

            # Update net pos
            self.net_pos = new_pos

        else:
            new_pos = self.net_pos - trade_volume

            # Open new short position
            if self.net_pos <= 0:
                new_cost = old_cost - trade_volume * trade_price
                self.open_price = new_cost / new_pos
            # Close long position
            else:
                close_volume = min(trade_volume, abs(self.net_pos))
                realized_pnl = (trade_price - self.open_price) * close_volume
                self.realized_pnl += realized_pnl

                if new_pos < 0:
                    self.open_price = trade_price

            # Update net pos
            self.net_pos = new_pos

        self.calculate_pnl()

    def update_price(self, last_price: float):
        """"""
        self.last_price = last_price
        self.calculate_pnl()

    def update_note(self, note_text: str):
        """"""
        self.note_text = note_text
