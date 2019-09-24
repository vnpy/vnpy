from copy import copy
from dataclasses import dataclass
from functools import partial
from http.client import IncompleteRead, RemoteDisconnected
from typing import Callable, TYPE_CHECKING, Type

from urllib3.exceptions import ProtocolError

from vnpy.api.rest import Request
from vnpy.trader.constant import Exchange, Interval, Offset, Status
from vnpy.trader.object import OrderData, SubscribeRequest, TickData, TradeData
from .oanda_api_base import OandaApiBase
from .oanda_common import (parse_datetime, parse_time)

if TYPE_CHECKING:
    from vnpy.gateway.oanda import OandaGateway
_ = lambda x: x  # noqa

HOST = "https://stream-fxtrade.oanda.com"
TEST_HOST = "https://stream-fxpractice.oanda.com"

# asked from official developer
PRICE_TICKS = {
    "BTCUSD": 0.5,
    "ETHUSD": 0.05,
    "EOSUSD": 0.001,
    "XRPUSD": 0.0001,
}


@dataclass()
class HistoryDataNextInfo:
    symbol: str
    interval: Interval
    end: int


class RequestFailedException(Exception):
    pass


class OandaStreamApi(OandaApiBase):
    """
    Oanda Streaming API
    """

    def __init__(self, gateway: "OandaGateway"):
        """"""
        super().__init__(gateway)

        self.fully_initialized = False

        self._transaction_callbacks = {
            'ORDER_FILL': self.on_order_filled,
            'MARKET_ORDER': self.on_order,
            'LIMIT_ORDER': self.on_order,
            'STOP_ORDER': self.on_order,
            'ORDER_CANCEL': self.on_order_canceled,

            # 'HEARTBEAT': do_nothing,
        }

    def connect(
        self,
        key: str,
        session_number: int,
        server: str,
        proxy_host: str,
        proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key

        if server == "REAL":
            self.init(HOST, proxy_host, proxy_port)
        else:
            self.init(TEST_HOST, proxy_host, proxy_port)

        self.start(session_number)

        self.gateway.write_log(_("Streaming API启动成功"))

    def subscribe(self, req: SubscribeRequest):
        # noinspection PyTypeChecker
        self.add_streaming_request(
            "GET",
            f"/v3/accounts/{self.gateway.account_id}/pricing/stream?instruments={req.symbol}",
            callback=self.on_price,
            on_error=partial(self.on_streaming_error, partial(self.subscribe, copy(req))),
        )

    def on_price(self, data: dict, request: Request):
        type_ = data['type']
        if type_ == 'PRICE':
            symbol = data['instrument']
            # only one level of bids/asks
            bid = data['bids'][0]
            ask = data['asks'][0]
            tick = TickData(
                gateway_name=self.gateway_name,
                symbol=symbol,
                exchange=Exchange.OANDA,
                datetime=parse_datetime(data['time']),
                name=symbol,
                bid_price_1=float(bid['price']),
                bid_volume_1=bid['liquidity'],
                ask_price_1=float(ask['price']),
                ask_volume_1=ask['liquidity'],
            )
            self.gateway.on_tick(tick)

    def has_error(self, target_type: Type[Exception], e: Exception):
        """check if error type \a target_error exists inside \a e"""
        if isinstance(e, target_type):
            return True
        for arg in e.args:
            if isinstance(arg, Exception) and self.has_error(target_type, arg):
                return True
        return False

    def on_streaming_error(self,
                           re_subscribe: Callable,
                           exception_type: type,
                           exception_value: Exception,
                           tb,
                           request: Request,
                           ):
        """normally triggered by network error."""
        # skip known errors
        known = False
        for et in (ProtocolError, IncompleteRead, RemoteDisconnected,):
            if self.has_error(et, exception_value):
                known = True
                break

        if known:
            # re-subscribe
            re_subscribe()
        # write log for any unknown errors
        else:
            super().on_error(exception_type, exception_value, tb, request)

    def subscribe_transaction(self):
        # noinspection PyTypeChecker
        self.add_streaming_request(
            "GET",
            f"/v3/accounts/{self.gateway.account_id}/transactions/stream",
            callback=self.on_transaction,
            on_connected=self.on_subscribed_transaction,
            on_error=partial(self.on_streaming_error, partial(self.subscribe_transaction, )),
        )

    def on_subscribed_transaction(self, request: "Request"):
        self.fully_initialized = True

    def on_transaction(self, data: dict, request: "Request"):
        type_ = data['type']
        callback = self._transaction_callbacks.get(type_, None)
        if callback is not None:
            callback(data, request)
        elif type_ != "HEARTBEAT":
            print(type_)

    def on_order(self, data: dict, request: "Request"):
        order = self.gateway.parse_order_data(data,
                                              Status.NOTTRADED,
                                              'time',
                                              )
        self.gateway.on_order(order)

    def on_order_canceled(self, data: dict, request: "Request"):
        order_id = data.get('clientOrderID', None)
        if order_id is None:
            order_id = data['id']
        order = self.gateway.orders[order_id]
        order.status = Status.CANCELLED
        order.time = parse_time(data['time'])
        self.gateway.on_order(order)

    def on_order_filled(self, data: dict, request: "Request"):
        order_id = data.get('clientOrderID', None)
        if order_id is None:
            order_id = data['orderID']

        order: OrderData = self.gateway.orders[order_id]

        # # new API:
        # price = 0.0
        # if 'tradeOpened' in data:
        #     price += float(data['tradeOpened']['price'])
        # if 'tradeReduced' in data:
        #     price += float(data['tradeReduced']['price'])
        # if 'tradeClosed' in data:
        #     price += sum([float(i['price']) for i in data['tradeClosed']])

        # note: 'price' record is Deprecated
        # but since this is faster and easier, we use this record.
        price = float(data['price'])

        # for Oanda, one order fill is a single trade.
        trade = TradeData(
            gateway_name=self.gateway_name,
            symbol=order.symbol,
            exchange=Exchange.OANDA,
            orderid=order_id,
            tradeid=order_id,
            direction=order.direction,
            offset=Offset.NONE,
            price=price,
            volume=order.volume,
            time=parse_time(data['time']),
        )
        self.gateway.on_trade(trade)

        # this message indicate that this order is full filled.
        # ps: oanda's order has only two state: NOTTRADED, ALLTRADED. It it my settings error?
        order.traded = order.volume
        order.status = Status.ALLTRADED
        # order.time = trade.time
        order.time = parse_time(data['time'])
        self.gateway.on_order(order)

    # quick references
    on_tick = on_price
    on_trade = on_order_filled
