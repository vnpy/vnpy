# encoding: UTF-8
"""
    Author: vigarbuaa
"""

import hashlib
import hmac
import sys
import time
from copy import copy
from datetime import datetime
from urllib.parse import urlencode
from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient

from vnpy.trader.constant import (
    Direction,
    Exchange,
    PriceType,
    Product,
    Status,
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

BASE_URL = "https://paper-api.alpaca.markets"
KEY = "https://api.alpaca.com/"
SECRET = ""

REST_HOST = "https://paper-api.alpaca.markets"
WEBSOCKET_HOST = "https://api.alpaca.com/ws/2"

STATUS_ALPACA2VT = {
    "ACTIVE": Status.NOTTRADED,
    "PARTIALLY FILLED": Status.PARTTRADED,
    "EXECUTED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
}

PRICETYPE_VT2ALPACA = {
    PriceType.LIMIT: "EXCHANGE LIMIT",
    PriceType.MARKET: "EXCHANGE MARKET"}
DIRECTION_VT2ALPACA = {Direction.LONG: "Buy", Direction.SHORT: "Sell"}
DIRECTION_ALPACA2VT = {"Buy": Direction.LONG, "Sell": Direction.SHORT}


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
        self.ws_api = AlpacaWebsocketApi(self)
        self.order_map = {}

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session = setting["session"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        self.rest_api.connect(key, secret, session, proxy_host, proxy_port)

        self.ws_api.connect(key, secret, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        # return self.rest_api.send_order(req)
        return self.ws_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.ws_api.cancel_order(req)

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
        self.connect_time = 0
        print(
            self.gateway_name,
            self.key,
            self.secret,
            self.order_count,
            self.connect_time)

    def sign(self, request):
        """
        Generate Alpaca signature.
        """

        msg = request.method + \
            "/api/v1/{}{}{}".format(path, nonce, request.data)
        headers = {
            "APCA-API-KEY-ID": self.key,
            "APCA-API-SECRET-KEY": self.secret,
        }

        request.headers = headers
        request.allow_redirects=False
        return request

    def connect(
        self,
        key: str,
        secret: str,
        session: int,
        proxy_host: str,
        proxy_port: int,
    ):
        """
               Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret

        self.init(REST_HOST, proxy_host, proxy_port)
        print("rest connect: ", REST_HOST, proxy_host, proxy_port)
        self.start(session)
        print("rest client connected")
        self.gateway.write_log("ALPACA REST API启动成功")
        self.query_account()

    def query_account(self):
        """"""
        print("debug query_account: ")
        self.add_request(
            "GET",
            "/v1/account",
            callback=self.on_query_account
        )

    def on_query_account(self, data, request):
        """"""
        print("debug on_query_account: ",data)
        for account_data in data:
            account = AccountData(
                accountid=account_data["currency"],
                balance=float(account_data["balance"]),
                frozen=float(account_data["hold"]),
                gateway_name=self.gateway_name
            )
            self.gateway.on_account(account)

        self.gateway.write_log("账户资金查询成功")



    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        msg = f"请求失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback to handler request exception.
        """
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
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