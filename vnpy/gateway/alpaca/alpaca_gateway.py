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
    OrderType,
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

# PRICETYPE_VT2ALPACA = {
#    PriceType.LIMIT: "EXCHANGE LIMIT",
#    PriceType.MARKET: "EXCHANGE MARKET"}
DIRECTION_VT2ALPACA = {Direction.LONG: "buy", Direction.SHORT: "sell"}
DIRECTION_ALPACA2VT = {"buy": Direction.LONG, "sell": Direction.SHORT}

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
        # self.ws_api = AlpacaWebsocketApi(self)
        self.order_map = {}

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session = setting["session"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        self.rest_api.connect(key, secret, session, proxy_host, proxy_port)

        # self.ws_api.connect(key, secret, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """"""
        pass

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
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
        self.order_id = 1_000_000

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

        headers = {
            "APCA-API-KEY-ID": self.key,
            "APCA-API-SECRET-KEY": self.secret,
        }

        request.headers = headers
        request.allow_redirects = False
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
        self.query_contract()

    def query_account(self):
        """"""
        self.add_request(
            "GET",
            "/v1/account",
            callback=self.on_query_account
        )

    def on_query_account(self, data, request):
        """"""
        print("debug on_query_account: ", type(data), data)
        account = AccountData(
            accountid=data["id"],
            balance=float(data["cash"]),
            frozen=float(data["cash"]) - float(data['buying_power']),
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)
        self.gateway.write_log("账户资金查询成功")

    def query_contract(self):
        """"""
        self.add_request(
            "GET",
            "/v1/assets",
            callback=self.on_query_contract
        )

    def on_query_contract(self, data, request):
        """"""
        for instrument_data in data:
            symbol = instrument_data["symbol"]
            # {"id":"74c0839d-1350-4801-842f-5f79b0d9a49a",
            # "asset_class":"us_equity","exchange":"NASDAQ",
            # "symbol":"NSIT","status":"active","tradable":true}]
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.ALPACA,  # vigar, need to fix to nasdq ...
                name=symbol,
                product=Product.SPOT,
                size=1,
                pricetick=0.01,
                gateway_name=self.gateway_name
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

    def _gen_unqiue_cid(self):
        # return int(round(time.time() * 1000))
        self.order_id = self.order_id + 1
        local_oid = time.strftime("%y%m%d") + str(self.order_id)
        return int(local_oid)
    
    def send_order(self, req: OrderRequest):
        orderid = self._gen_unqiue_cid()

        if req.direction == Direction.LONG:
            amount = req.volume
        else:
            amount = -req.volume
        order_type = ORDERTYPE_VT2ALPACA[req.type]
        order_side = DIRECTION_VT2ALPACA[req.direction]
        data = {
            "symbol": "b0b6dd9d-8b9b-48a9-ba46-b9d54906e415",#req.symbol,
            'qty': int(amount),
            "client_order_id": str(orderid),
            "type": order_type,
            "side": order_side,
            "time_in_force": "day"
        }
        if req.type==OrderType.MARKET:
            data['limit_price']=float(req.price)
        
        order = req.create_order_data(orderid, self.gateway_name)
       
        self.add_request(
            "POST",
            "/v1/orders",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error,
        )

    def on_send_order(self, data, request):
        """Websocket will push a new order status"""
        print("debug on_send_order data: ", data)
        print("debug on_send_order request: ", request)

    def on_send_order_failed(self, status_code: str, request: Request):
        """
        Callback when sending order failed on server.
        """
        print("debug on_send_order_failed data: ", request)
        print("debug on_send_order_failed status code: ", status_code)
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg = f"委托失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_send_order_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when sending order caused exception.
        """
        print("debug on_send_order_error req: ", request)
        print("debug on_send_order_error tb: ", tb)
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

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

    def send_order(self, req: SubscribeRequest):
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
        print("debug on_packet: ", packet)

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
