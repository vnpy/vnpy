from copy import copy
from typing import Any, Dict
from datetime import datetime
from tzlocal import get_localzone

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    OrderRequest, CancelRequest, SubscribeRequest,
    ContractData, OrderData, TradeData, TickData, LogData
)
from vnpy.trader.event import (
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_TICK,
    EVENT_CONTRACT,
    EVENT_LOG
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

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.slippage: int = 0
        self.order_count: int = 100000

        self.active_orders: Dict[str, Dict[str, OrderData]] = {}
        self.gateway_map: Dict[str, str] = {}
        self.ticks: Dict[str, TickData] = {}

        self._subscribe = main_engine.subscribe

        main_engine.subscribe = self.subscribe
        main_engine.send_order = self.send_order
        main_engine.cancel_order = self.cancel_order

        self.register_event()

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.event_engine.register(EVENT_TICK, self.process_tick_event)

    def process_contract_event(self, event: Event) -> None:
        """"""
        contract: ContractData = event.data
        self.gateway_map[contract.vt_symbol] = contract.gateway_name
        contract.gateway_name = GATEWAY_NAME

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

        # Reject unsupported order type
        if order.type in {OrderType.FAK, OrderType.FOK, OrderType.RFQ}:
            order.status = Status.REJECTED
        elif order.type == OrderType.STOP and not contract.stop_supported:
            order.status = Status.REJECTED

        # Put simulated order update event from exchange
        if order.status == Status.REJECTED:
            self.write_log(f"委托被拒单，不支持的委托类型{order.type.value}")
        else:
            order.datetime = datetime.now(LOCAL_TZ)
            order.status = Status.NOTTRADED
            active_orders = self.active_orders.setdefault(order.vt_symbol, {})
            active_orders[orderid] = order

        self.put_event(EVENT_ORDER, copy(order))

        return vt_orderid

    def cancel_order(self, req: CancelRequest, gateway_name: str) -> None:
        """"""
        active_orders: Dict[str, OrderRequest] = self.active_orders[req.vt_symbol]

        if req.orderid in active_orders:
            order: OrderData = active_orders.pop(req.orderid)
            order.status = Status.CANCELLED
            self.put_event(EVENT_ORDER, copy(order))

    def put_event(self, event_type: str, data: Any) -> None:
        """"""
        event = Event(event_type, data)
        self.event_engine.put(event)

    def cross_order(self, order: OrderData, tick: TickData):
        """"""
        contract = self.main_engine.get_contract(order.vt_symbol)

        trade_price = 0

        # Cross market order immediately after received
        if order.type == OrderType.MARKET:
            if order.direction == Direction.LONG:
                trade_price = tick.ask_price_1 + self.slippage * contract.pricetick
            else:
                trade_price = tick.bid_price_1 - self.slippage * contract.pricetick
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
                    trade_price = tick.ask_price_1 + self.slippage * contract.pricetick
            else:
                if tick.bid_price_1 <= order.price:
                    trade_price = tick.bid_price_1 - self.slippage * contract.pricetick

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

    def write_log(self, msg: str) -> None:
        """"""
        log = LogData(msg=msg, gateway_name=GATEWAY_NAME)
        self.put_event(EVENT_LOG, log)
