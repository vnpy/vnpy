from copy import copy
from typing import Any, Dict, Tuple, Optional
from datetime import datetime
from tzlocal import get_localzone

from vnpy.event import Event, EventEngine
from vnpy.trader.utility import extract_vt_symbol, save_json, load_json
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    OrderRequest, CancelRequest, SubscribeRequest,
    ContractData, OrderData, TradeData, TickData,
    LogData, PositionData
)
from vnpy.trader.event import (
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_TICK,
    EVENT_POSITION,
    EVENT_CONTRACT,
    EVENT_LOG,
    EVENT_TIMER
)
from vnpy.trader.constant import (
    Status,
    OrderType,
    Direction,
    Offset
)


LOCAL_TZ = get_localzone()
APP_NAME = "PaperAccount"
GATEWAY_NAME = "PAPER"


class PaperEngine(BaseEngine):
    """"""
    setting_filename = "paper_account_setting.json"
    data_filename = "paper_account_data.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.trade_slippage: int = 0
        self.timer_interval: int = 3
        self.instant_trade: bool = False

        self.order_count: int = 100000
        self.timer_count: int = 0

        self.active_orders: Dict[str, Dict[str, OrderData]] = {}
        self.gateway_map: Dict[str, str] = {}
        self.ticks: Dict[str, TickData] = {}
        self.positions: Dict[Tuple[str, Direction], PositionData] = {}

        # Patch main engine functions
        self._subscribe = main_engine.subscribe

        main_engine.subscribe = self.subscribe
        main_engine.send_order = self.send_order
        main_engine.cancel_order = self.cancel_order

        self.load_setting()
        self.load_data()
        self.register_event()

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_contract_event(self, event: Event) -> None:
        """"""
        contract: ContractData = event.data
        self.gateway_map[contract.vt_symbol] = contract.gateway_name
        contract.gateway_name = GATEWAY_NAME

        for direciton in Direction:
            key = (contract.vt_symbol, direciton)
            if key in self.positions:
                position = self.positions[key]
                self.put_event(EVENT_POSITION, position)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data
        tick.gateway_name = GATEWAY_NAME

        self.ticks[tick.vt_symbol] = tick

        if tick.vt_symbol not in self.active_orders:
            return

        active_orders = self.active_orders[tick.vt_symbol]
        if not active_orders:
            return

        for orderid, order in list(active_orders.items()):
            self.cross_order(order, tick)

            if not order.is_active():
                active_orders.pop(orderid)

    def process_timer_event(self, event: Event) -> None:
        """"""
        self.timer_count += 1
        if self.timer_count < self.timer_interval:
            return
        self.timer_count = 0

        for position in self.positions.values():
            self.calculate_pnl(position)
            self.put_event(EVENT_POSITION, copy(position))

    def calculate_pnl(self, position: PositionData) -> None:
        """"""
        tick = self.ticks.get(position.vt_symbol, None)

        if tick:
            contract = self.main_engine.get_contract(position.vt_symbol)

            if position.direction == Direction.SHORT:
                multiplier = -position.volume * contract.size
            else:
                multiplier = position.volume * contract.size

            position.pnl = (tick.last_price - position.price) * multiplier
            position.pnl = round(position.pnl, 2)

    def subscribe(self, req: SubscribeRequest, gateway_name: str) -> None:
        """"""
        original_gateway_name = self.gateway_map.get(req.vt_symbol, "")
        if original_gateway_name:
            self._subscribe(req, original_gateway_name)

    def send_order(self, req: OrderRequest, gateway_name: str) -> str:
        """"""
        contract: ContractData = self.main_engine.get_contract(req.vt_symbol)
        if not contract:
            self.write_log(f"委托失败，找不到该合约{req.vt_symbol}")
            return ""

        self.order_count += 1
        now = datetime.now().strftime("%y%m%d%H%M%S")
        orderid = now + str(self.order_count)
        vt_orderid = f"{GATEWAY_NAME}.{orderid}"

        # Put simulated order update event from gateway
        order = req.create_order_data(orderid, GATEWAY_NAME)
        self.put_event(EVENT_ORDER, copy(order))

        # Check if order is valid
        updated_position = self.check_order_valid(order, contract)

        # Put simulated order update event from exchange
        if order.status != Status.REJECTED:
            order.datetime = datetime.now(LOCAL_TZ)
            order.status = Status.NOTTRADED
            active_orders = self.active_orders.setdefault(order.vt_symbol, {})
            active_orders[orderid] = order

        self.put_event(EVENT_ORDER, copy(order))

        # Update position frozen for close order
        if updated_position:
            self.put_event(EVENT_POSITION, copy(updated_position))

        # Cross order immediately with last tick data
        if self.instant_trade:
            tick = self.ticks.get(order.vt_symbol, None)
            if tick:
                self.cross_order(order, tick)

                if not order.is_active():
                    active_orders.pop(orderid)

        return vt_orderid

    def cancel_order(self, req: CancelRequest, gateway_name: str) -> None:
        """"""
        active_orders: Dict[str, OrderRequest] = self.active_orders[req.vt_symbol]

        if req.orderid in active_orders:
            order: OrderData = active_orders.pop(req.orderid)
            order.status = Status.CANCELLED
            self.put_event(EVENT_ORDER, copy(order))

            # Free frozen position volume
            contract = self.main_engine.get_contract(order.vt_symbol)
            if contract.net_position:
                return

            if order.offset == Offset.OPEN:
                return

            if order.direction == Direction.LONG:
                position = self.get_position(order.vt_symbol, Direction.SHORT)
            else:
                position = self.get_position(order.vt_symbol, Direction.LONG)
            position.frozen -= order.volume

            self.put_event(EVENT_POSITION, copy(position))

    def put_event(self, event_type: str, data: Any) -> None:
        """"""
        event = Event(event_type, data)
        self.event_engine.put(event)

    def check_order_valid(self, order: OrderData, contract: ContractData) -> Optional[PositionData]:
        """"""
        # Reject unsupported order type
        if order.type in {OrderType.FAK, OrderType.FOK, OrderType.RFQ}:
            order.status = Status.REJECTED
        elif order.type == OrderType.STOP and not contract.stop_supported:
            order.status = Status.REJECTED

        if order.status == Status.REJECTED:
            self.write_log(f"委托被拒单，不支持的委托类型{order.type.value}")

        # Reject close order if no more available position
        if contract.net_position or order.offset == Offset.OPEN:
            return

        if order.direction == Direction.LONG:
            short_position = self.get_position(order.vt_symbol, Direction.SHORT)
            available = short_position.volume - short_position.frozen

            if order.volume > available:
                order.status = Status.REJECTED
            else:
                short_position.frozen += order.volume
                return short_position
        else:
            long_position = self.get_position(order.vt_symbol, Direction.LONG)
            available = long_position.volume - long_position.frozen

            if order.volume > available:
                order.status = Status.REJECTED
            else:
                long_position.frozen += order.volume
                return long_position

            if order.status == Status.REJECTED:
                self.write_log(f"委托被拒单，可平仓位不足")

    def cross_order(self, order: OrderData, tick: TickData):
        """"""
        contract = self.main_engine.get_contract(order.vt_symbol)

        trade_price = 0

        # Cross market order immediately after received
        if order.type == OrderType.MARKET:
            if order.direction == Direction.LONG:
                trade_price = tick.ask_price_1 + self.trade_slippage * contract.pricetick
            else:
                trade_price = tick.bid_price_1 - self.trade_slippage * contract.pricetick
        # Cross limit order only if price touched
        elif order.type == OrderType.LIMIT:
            if order.direction == Direction.LONG:
                if order.price >= tick.ask_price_1:
                    trade_price = tick.ask_price_1
            else:
                if order.price <= tick.bid_price_1:
                    trade_price = tick.bid_price_1
        # Cross limit order only if price broken
        elif order.type == OrderType.STOP:
            if order.direction == Direction.LONG:
                if tick.ask_price_1 >= order.price:
                    trade_price = tick.ask_price_1 + self.trade_slippage * contract.pricetick
            else:
                if tick.bid_price_1 <= order.price:
                    trade_price = tick.bid_price_1 - self.trade_slippage * contract.pricetick

        if trade_price:
            order.status = Status.ALLTRADED
            order.traded = order.volume
            self.put_event(EVENT_ORDER, order)

            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=order.orderid,
                direction=order.direction,
                offset=order.offset,
                price=trade_price,
                volume=order.volume,
                datetime=datetime.now(LOCAL_TZ),
                gateway_name=order.gateway_name
            )
            self.put_event(EVENT_TRADE, trade)

            self.update_position(trade, contract)

    def update_position(self, trade: TradeData, contract: ContractData):
        """"""
        vt_symbol = trade.vt_symbol

        # Net position mode
        if contract.net_position:
            position = self.get_position(vt_symbol, Direction.NET)

            old_volume = position.volume
            old_cost = position.volume * position.price

            if trade.direction == Direction.LONG:
                pos_change = trade.volume
            else:
                pos_change = -trade.volume

            new_volume = position.volume + pos_change

            # No position holding, clear price
            if not new_volume:
                position.price = 0
            # Position direction changed, set to open price
            elif (
                (new_volume > 0 and old_volume < 0)
                or (new_volume < 0 and old_volume > 0)
            ):
                position.price = trade.price
            # Position is add on the same direction
            elif (
                (old_volume >= 0 and pos_change > 0)
                or (old_volume <= 0 and pos_change < 0)
            ):
                new_cost = old_cost + pos_change * trade.price
                position.price = new_cost / new_volume

            position.volume = new_volume
            self.calculate_pnl(position)
            self.put_event(EVENT_POSITION, copy(position))
        # Long/Short position mode
        else:
            long_position = self.get_position(vt_symbol, Direction.LONG)
            short_position = self.get_position(vt_symbol, Direction.SHORT)

            if trade.direction == Direction.LONG:
                if trade.offset == Offset.OPEN:
                    old_cost = long_position.volume * long_position.price
                    new_cost = old_cost + trade.volume * trade.price

                    long_position.volume += trade.volume
                    long_position.price = new_cost / long_position.volume
                else:
                    short_position.volume -= trade.volume
                    short_position.frozen -= trade.volume

                    if not short_position.volume:
                        short_position.price = 0
            else:
                if trade.offset == Offset.OPEN:
                    old_cost = short_position.volume * short_position.price
                    new_cost = old_cost + trade.volume * trade.price

                    short_position.volume += trade.volume
                    short_position.price = new_cost / short_position.volume
                else:
                    long_position.volume -= trade.volume
                    long_position.frozen -= trade.volume

                    if not long_position.volume:
                        long_position.price = 0

            self.calculate_pnl(long_position)
            self.calculate_pnl(short_position)

            self.put_event(EVENT_POSITION, copy(long_position))
            self.put_event(EVENT_POSITION, copy(short_position))

        self.save_data()

    def get_position(self, vt_symbol: str, direction: Direction):
        """"""
        key = (vt_symbol, direction)

        if key in self.positions:
            return self.positions[key]
        else:
            symbol, exchange = extract_vt_symbol(vt_symbol)
            position = PositionData(
                symbol=symbol,
                exchange=exchange,
                direction=direction,
                gateway_name=GATEWAY_NAME
            )

            self.positions[key] = position
            return position

    def write_log(self, msg: str) -> None:
        """"""
        log = LogData(msg=msg, gateway_name=GATEWAY_NAME)
        self.put_event(EVENT_LOG, log)

    def save_data(self) -> None:
        """"""
        position_data = []

        for position in self.positions.values():
            if not position.volume:
                continue

            d = {
                "vt_symbol": position.vt_symbol,
                "volume": position.volume,
                "price": position.price,
                "direction": position.direction.value
            }
            position_data.append(d)

        save_json(self.data_filename, position_data)

    def load_data(self) -> None:
        """"""
        position_data = load_json(self.data_filename)

        for d in position_data:
            vt_symbol = d["vt_symbol"]
            direction = Direction(d["direction"])

            position = self.get_position(vt_symbol, direction)
            position.volume = d["volume"]
            position.price = d["price"]

    def load_setting(self) -> None:
        """"""
        setting = load_json(self.setting_filename)

        if setting:
            self.trade_slippage = setting["trade_slippage"]
            self.timer_interval = setting["timer_interval"]
            self.instant_trade = setting["instant_trade"]

    def save_setting(self) -> None:
        """"""
        setting = {
            "trade_slippage": self.trade_slippage,
            "timer_interval": self.timer_interval,
            "instant_trade": self.instant_trade
        }
        save_json(self.setting_filename, setting)

    def clear_position(self) -> None:
        """"""
        for position in self.positions.values():
            position.volume = 0
            position.frozen = 0
            position.price = 0
            self.put_event(EVENT_POSITION, position)

        self.save_data()

    def set_trade_slippage(self, trade_slippage: int) -> None:
        """"""
        self.trade_slippage = trade_slippage
        self.save_setting()

    def set_timer_interval(self, timer_interval: int) -> None:
        """"""
        self.timer_interval = timer_interval
        self.save_setting()

    def set_instant_trade(self, instant_trade: bool) -> None:
        """"""
        self.instant_trade = bool(instant_trade)
        self.save_setting()
