# encoding: UTF-8
"""
    Author: vigarbuaa
"""

import hashlib
import hmac
import sys
import time
from copy import copy
from threading import Lock
from datetime import datetime
from urllib.parse import urlencode
from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.event import Event
from vnpy.trader.event import EVENT_TIMER

from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Offset,
    Interval
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    PositionData, AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
)

REST_HOST = "https://api.alpaca.markets"
WEBSOCKET_HOST = "wss://api.alpaca.markets/stream"   # Market Data
PAPER_REST_HOST = "https://paper-api.alpaca.markets"
PAPER_WEBSOCKET_HOST = "wss://paper-api.alpaca.markets/stream"  # Market Data
KEY = ""
SECRET = ""

STATUS_ALPACA2VT = {
    "new": Status.SUBMITTING,
    "partial_fill": Status.PARTTRADED,
    "fill": Status.ALLTRADED,
    "cancelled": Status.CANCELLED,
    # "done_for_day": Status.CANCELLED,
    "expired": Status.NOTTRADED
}

DIRECTION_VT2ALPACA = {Direction.LONG: "buy", Direction.SHORT: "sell"}
DIRECTION_ALPACA2VT = {"buy": Direction.LONG, "sell": Direction.SHORT,
                       "long": Direction.LONG, "short": Direction.SHORT}

ORDERTYPE_VT2ALPACA = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market"
}
ORDERTYPE_ALPACA2VT = {v: k for k, v in ORDERTYPE_VT2ALPACA.items()}
GLOBAL_ORDER = {}


class AlpacaGateway(BaseGateway):
    """
    VN Trader Gateway for Alpaca connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "session": 3,
        "服务器": ["REAL", "PAPER"],
        "proxy_host": "127.0.0.1",
        "proxy_port": 1080,
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(AlpacaGateway, self).__init__(event_engine, "ALPACA")

        self.rest_api = AlpacaRestApi(self)
        self.ws_api = AlpacaWebsocketApi(self)
        self.order_map = {}

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session = setting["session"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]
        env = setting['服务器']
        rest_url = REST_HOST if env == "REAL" else PAPER_REST_HOST
        websocket_url = WEBSOCKET_HOST if env == "REAL" else PAPER_WEBSOCKET_HOST
        self.rest_api.connect(key, secret, session,
                              proxy_host, proxy_port, rest_url)
        self.ws_api.connect(key, secret, proxy_host, proxy_port, websocket_url)
        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self):
        """"""
        self.rest_api.query_account()

    def query_position(self):
        """"""
        self.rest_api.query_position()

    def close(self):
        """"""
        self.rest_api.stop()
        self.ws_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        self.count += 1
        if self.count < 5:
            return

        self.query_account()
        self.query_position()

    def init_query(self):
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_timer_event(self, event: Event):
        """"""
        self.count += 1
        if self.count < 5:
            return
        else:
            self.count = 0

        self.query_account()
        self.query_position()


class AlpacaRestApi(RestClient):
    """
    Alpaca REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(AlpacaRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.order_count = 1_000_000
        self.order_count_lock = Lock()
        self.connect_time = 0
        self.order_dict = {}

    def query_account(self):
        path = f"/v1/account"
        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_account
        )

    def on_query_account(self, data, request):
        account = AccountData(
            accountid=data['id'],
            balance=float(data['cash']),
            frozen=float(data['cash']) - float(data['buying_power']),
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def query_position(self):
        path = f"/v1/positions"
        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_position
        )

    def on_query_position(self, data, request):
        for d in data:
            position = PositionData(
                symbol=d['symbol'],
                exchange=Exchange.ALPACA,
                direction=DIRECTION_ALPACA2VT[d['side']],
                volume=d['qty'],
                price=round(d['avg_entry_price'], 3),
                pnl=d['unrealized_pl'],
                gateway_name=self.gateway_name,
            )
            self.gateway.on_position(position)

    def sign(self, request):
        """
        Generate Alpaca signature.
        """
        headers = {
            "APCA-API-KEY-ID": self.key,
            "APCA-API-SECRET-KEY": self.secret,
            'Content-Type': 'application/json'
        }

        request.headers = headers
        request.allow_redirects = False
        return request

    def _new_order_id(self):
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def connect(
        self,
        key: str,
        secret: str,
        session_num: int,
        proxy_host: str,
        proxy_port: int,
        url: str,
    ):
        """
               Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret
        self.init(url, proxy_host, proxy_port)
        self.start(session_num)
        self.connect_time = (
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )
        self.gateway.write_log("ALPACA REST API启动成功")
        self.query_account()
        self.query_position()
        # self.query_contracts()

    def on_send_order(self, data, request: Request):
        remote_order_id = data['id']
        order = request.extra
        self.order_dict[order.orderid] = remote_order_id
        self.gateway.on_order(order)
        GLOBAL_ORDER[remote_order_id] = order

    def on_failed_order(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)
        msg = f"请求失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_error_order(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback to handler request exception.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        print('debug on_error', msg)
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )

    def cancel_order(self, req: CancelRequest):
        """"""
        order_id = req.orderid
        remote_order_id = self.order_dict[order_id]
        if remote_order_id is None:
            print("[error]: can not get remote_order_id from local dict!")
            return
        path = "/v1/orders/" + str(remote_order_id)
        self.add_request(
            "DELETE",
            path,
            callback=self.on_cancel_order,
            on_error=self.on_cancel_order_error,
            extra=req
        )
        print("come to cancel_order", order_id)

    def on_cancel_order(self, data, request):
        """Websocket will push a new order status"""
        pass

    def on_cancel_order_error(self, exception_type: type, exception_value: Exception, tb, request: Request):
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def send_order(self, req: OrderRequest):
        orderid = str(self.connect_time + self._new_order_id())
        raw_dict = {
            "symbol": req.symbol,
            "qty": int(req.volume),
            "side": DIRECTION_VT2ALPACA[req.direction],
            "type": ORDERTYPE_VT2ALPACA[req.type],
            "time_in_force": 'day',
        }
        if raw_dict['type'] == "limit":
            raw_dict['limit_price'] = float(req.price)

        data = raw_dict
        order = req.create_order_data(orderid, self.gateway_name)
        print("debug send_order orderBody extra: ", order)
        self.add_request(
            "POST",
            "/v1/orders",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_failed=self.on_failed_order,
            on_error=self.on_error_order,
            # json_str=data,
        )
        print("debug send_order ret val : ", order.vt_orderid)
        return order.vt_orderid

    def on_query_contracts(self, data, request: Request):
        for instrument_data in data:
            symbol = instrument_data['symbol']
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.ALPACA,
                name=symbol,
                product=Product.SPOT,
                size=1,
                pricetick=0.01,
                gateway_name=self.gateway_name
            )
            self.on_contract(contract)

    def on_failed_query_contracts(self, status_code: int, request: Request):
        pass

    def on_error_query_contracts(self, exception_type: type, exception_value: Exception, tb, request: Request):
        pass

    def query_contracts(self):
        params = {"status": "active"}
        self.add_request(
            "GET",
            "/v1/assets",
            params=params,
            callback=self.on_query_contracts,
            on_failed=self.on_failed_query_contracts,
            on_error=self.on_error_query_contracts,
        )


class AlpacaWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(AlpacaWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_id = 1_000_000
        # self.date = int(datetime.now().strftime('%y%m%d%H%M%S')) * self.orderId
        self.key = ""
        self.secret = ""

        self.callbacks = {
            "trade": self.on_tick,
            "orderBook10": self.on_depth,
            "execution": self.on_trade,
            "order": self.on_order,
            "position": self.on_position,
            "margin": self.on_account,
            "instrument": self.on_contract,
        }

        self.ticks = {}
        self.accounts = {}
        self.orders = {}
        self.trades = set()
        self.tickDict = {}
        self.bidDict = {}
        self.askDict = {}
        self.orderLocalDict = {}
        self.channelDict = {}       # ChannelID : (Channel, Symbol)
        self.channels = ["account_updates", "trade_updates"]

    def connect(
        self, key: str, secret: str, proxy_host: str, proxy_port: int, url: str
    ):
        """"""
        self.key = key
        self.secret = secret
        self.init(url, proxy_host, proxy_port)
        self.start()

    def authenticate(self):
        """"""
        params = {"action": "authenticate", "data": {
            "key_id": self.key, "secret_key": self.secret
        }}
        self.send_packet(params)

    def on_authenticate(self):
        """"""
        params = {"action": "listen", "data": {
            "streams": self.channels
        }}
        self.send_packet(params)

    def subscribe(self, req: SubscribeRequest):
        self.channels.append("A." + req.symbol)
        self.channels.append("Q." + req.symbol)
        print("debug subscribe: {}  ".format(self.channels))
        params = {"action": "listen", "data": {
            "streams": self.channels
        }}
        self.send_packet(params)

    def send_order(self, req: OrderRequest):
        pass

    # ----------------------------------------------------------------------
    def cancel_order(self, req: CancelRequest):
        """"""
        pass

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")
        self.authenticate()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        print("debug on_packet: ", packet)
        if "stream" in packet and "data" in packet:
            stream_ret = packet['stream']
            data_ret = packet['data']
            if(stream_ret == "authorization"):
                self.handle_auth(packet)
            elif(stream_ret == "listening"):
                self.gateway.write_log("listening {}".format(data_ret))
            else:
                self.on_data(packet)
        else:
            print("unrecognize msg", packet)

    # ----------------------------------------------------------------------
    def on_data(self, data):
        print("on_data is {}".format(data))
        stream_ret = data['stream']
        data_ret = data['data']
        if(stream_ret == "account_updates"):
            account = AccountData(
                accountid=data_ret['id'],
                balance=float(data_ret['cash']),
                frozen=float(data_ret['cash']) -
                float(data_ret['cash_withdrawable']),
                gateway_name=self.gateway_name
            )
            self.gateway.on_account(account)
        elif(stream_ret == "trade_updates"):
            d = data_ret['order']
            order_id = d['id']
            order = GLOBAL_ORDER[order_id]
            local_order_id = order.orderid
            order.status = STATUS_ALPACA2VT[data_ret['event']]
            self.gateway.on_order(order)
            if (data_ret['event'] == "fill" or data_ret['event'] == "partial_fill"):
                trade = TradeData(
                    symbol=d["symbol"],
                    exchange=Exchange.ALPACA,
                    orderid=local_order_id,
                    tradeid=d['id'],
                    direction=DIRECTION_ALPACA2VT[d["side"]],
                    price=d["filled_avg_price"],
                    volume=d["filled_qty"],
                    time=data_ret["timestamp"][11:19],
                    gateway_name=self.gateway_name,
                )
                self.gateway.on_trade(trade)
        else:
            pass

    # ----------------------------------------------------------------------
    def handle_auth(self, data):
        stream_ret = data['stream']
        data_ret = data['data']
        if (data_ret['status'] == "authorized"):
            print("authorization success!!!")
            self.gateway.write_log("authorization success!!!")
            self.on_authenticate()
        elif (data_ret['status'] == "unauthorized"):
            print("authorization failed!!!")
            self.gateway.write_log("authorization failed!!!")
        else:
            print("??unhandled status:  ", data)

    # ----------------------------------------------------------------------
    def on_response(self, data):
        """"""
        pass
    # ----------------------------------------------------------------------

    def on_update(self, data):
        """"""
        pass

    # ----------------------------------------------------------------------

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        print("on_error: ", type, Exception, tb)
        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb)
        )

    def subscribe_topic(self):
        pass

    def on_tick(self, d):
        """"""
        pass

    def on_depth(self, d):
        """"""
        pass

    def on_trade(self, d):
        """"""
        pass

    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(s / 1000.0)
        time = dt.strftime("%H:%M:%S.%f")
        return time

    def on_order(self, data):
        """"""
        pass

    def on_position(self, d):
        """"""
        pass

    def on_account(self, d):
        """"""
        pass

    def on_contract(self, d):
        """"""
        pass
