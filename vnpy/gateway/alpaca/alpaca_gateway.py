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
PAPER_REST_HOST = "https://paper-api.alpaca.markets"
KEY = ""
SECRET = ""

STATUS_ALPACA2VT = {
    "new": Status.SUBMITTING,
    "open": Status.NOTTRADED,
    "part_filled": Status.PARTTRADED,
    "filled": Status.ALLTRADED,
    "cancelled": Status.CANCELLED,
    "cancelling": Status.CANCELLED,
    "failure": Status.REJECTED,
}

DIRECTION_VT2ALPACA = {Direction.LONG: "buy", Direction.SHORT: "sell"}
DIRECTION_ALPACA2VT = {"buy": Direction.LONG, "sell": Direction.SHORT,
                       "long": Direction.LONG, "short": Direction.SHORT}

ORDERTYPE_VT2ALPACA = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market"
}
ORDERTYPE_ALPACA2VT = {v: k for k, v in ORDERTYPE_VT2ALPACA.items()}

class AlpacaGateway(BaseGateway):
    """
    VN Trader Gateway for Alpaca connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "session": 3,
        "proxy_host": "127.0.0.1",
        "proxy_port": 1080,
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(AlpacaGateway, self).__init__(event_engine, "ALPACA")

        self.rest_api = AlpacaRestApi(self)
        #self.ws_api = AlpacaWebsocketApi(self)
        self.order_map = {}

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session = setting["session"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        self.rest_api.connect(key, secret, session, proxy_host, proxy_port)

        #self.ws_api.connect(key, secret, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """"""
        #self.ws_api.subscribe(req)
        pass

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        #self.ws_api.cancel_order(req)
        pass

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
        print(
            self.gateway_name,
            self.key,
            self.secret,
            self.order_count,
            self.connect_time)

    def query_account(self):
        print("call query_account")
        path = f"/v1/account"
        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_account
        )
    
    def on_query_account(self, data, request):
        print("debug on_query_account: ", data, request)
        account = AccountData(
            accountid=data['id'],
            balance=float(data['cash']),
            frozen=float(data['cash']) - float(data['buying_power']),
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)
    
    def query_position(self):
        print("call query_position")
        path = f"/v1/positions"
        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_position
        )

    def on_query_position(self, data, request):
        print("debug on_query_position: ", data,"!!!", request)
        for d in data:
            position = PositionData(
                symbol=d['symbol'],
                exchange=Exchange.ALPACA,
                direction=DIRECTION_ALPACA2VT[d['side']],
                volume=d['qty'],
                price=d['avg_entry_price'],
                pnl=d['unrealized_pl'],
                gateway_name=self.gateway_name,
            )
            self.gateway.on_position(position)



    def sign(self, request):
        """
        Generate Alpaca signature.
        """
        #msg = request.method + \
        #    "/api/v1/{}{}{}".format(path, nonce, request.data)
        headers = {
            "APCA-API-KEY-ID": self.key,
            "APCA-API-SECRET-KEY": self.secret,
        }

        request.headers = headers
        request.allow_redirects=False
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
    ):
        """
               Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret

        self.init(PAPER_REST_HOST, proxy_host, proxy_port)
        print("rest connect: ", PAPER_REST_HOST, proxy_host, proxy_port)
        self.start(session_num)
        self.connect_time = (
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )
        print("rest client connected",self.connect_time)
        self.gateway.write_log("ALPACA REST API启动成功")
        self.query_account()
        self.query_position()

    def on_send_order(self, status_code: int, request: Request):
        print("debug on send order: ", status_code, request)
        pass

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        msg = f"请求失败，状态码：{status_code}，信息：{request.response.text}"
        print('debug on_failed', msg)
        self.gateway.write_log(msg)

    def on_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback to handler request exception.
        """
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        print('debug on_error', msg)
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )

    def send_order(self, req: OrderRequest):
        orderid = str(self.connect_time + self._new_order_id())
        raw_dict={
            "symbol": req.symbol,
            "qty": int(req.volume),
            "side": DIRECTION_VT2ALPACA[req.direction],
            "type": ORDERTYPE_VT2ALPACA[req.type],
            "time_in_force":'day',
        }
        if raw_dict['type'] == "limit":
            raw_dict['limit_price'] = float(req.price)

        data = raw_dict
        order = req.create_order_data(orderid, self.gateway_name)
        self.add_request(
            "POST",
            "/v1/orders",
            callback=self.on_send_order,
            #data=data,
            extra=order,
            on_failed=self.on_failed,
            on_error=self.on_error,
            json_str=data,
        )
        self.gateway.on_order(order)
        return order.vt_orderid
        

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

    def connect(
        self, key: str, secret: str, proxy_host: str, proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret.encode()

        self.init(WEBSOCKET_HOST, proxy_host, proxy_port)

        self.start()

    def subscribe(self, req: SubscribeRequest):
        pass

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

    # need debug 20190404
    def on_packet(self, packet: dict):
        """"""
        print("debug on_packet: " , packet)

    # ----------------------------------------------------------------------
    def on_response(self, data):
        """"""
        pass
    # ----------------------------------------------------------------------
    def on_update(self, data):
        """"""
        pass

    # ----------------------------------------------------------------------
    def on_wallet(self, data):
        """"""
        pass

    # ----------------------------------------------------------------------
    def on_trade_update(self, data):
        """"""
        pass

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        print("on_error: " ,type,Exception,tb)
        pass

    # debug OK , 0405
    def authenticate(self):
        pass

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