# encoding: UTF-8
"""
币安交易接口
"""

from __future__ import print_function
import re
import urllib
import json
import hashlib
import hmac


from time import time

from datetime import datetime

from vnpy.event import Event
from vnpy.api.rest import RestClient, Request
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Product,
    Status,
    OrderType,
    Interval
)
from vnpy.trader.gateway import BaseGateway, LocalOrderManager
from vnpy.trader.object import (
    OrderData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)
from vnpy.trader.event import EVENT_TIMER


REST_HOST = 'https://api.binance.com'
WEBSOCKET_DATA_HOST = "wss://stream.binance.com:9443/stream?streams="       # Market Data

# DATASTREAM_ENDPOINT = 'wss://stream.binance.com:9443/stream?streams='
# USERSTREAM_ENDPOINT = 'wss://stream.binance.com:9443/ws/'

STATUS_BINANCE2VT = {
    "NEW": Status.NOTTRADED,
    "PARTIALLY_FILLED": Status.PARTTRADED,
    "FILLED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
    "REJECTED": Status.CANCELLED,
    "EXPIRED": Status.CANCELLED,
}

ORDERTYPE_VT2BINANCE = {
    OrderType.LIMIT: "LIMIT",
    OrderType.MARKET: "MARKET",
}

TIME_VT2BINANCE = {
    OrderType.FAK: "IOC",
    OrderType.FOK: "FOK",
    OrderType.GTC: "GTC"
}

SIDE_VT2BINANCE = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL",
}

INTERVAL_VT2BINANCE = {
    Interval.MINUTE: "1min",
    Interval.HOUR: "60min",
    Interval.DAILY: "1day"
}

ORDERTYPE_BINANCE2VT = {
    "LIMIT": OrderType.LIMIT,
    "MARKET": OrderType.MARKET,
    "STOP_LOSS": OrderType.STOP,
    "STOP_LOSS_LIMIT": OrderType.STOP,
    "TAKE_PROFIT": OrderType.STOP,
    "TAKE_PROFIT_LIMIT": OrderType.STOP,
    "LIMIT_MAKER": OrderType.LIMIT
}

SIDE_BINANCE2VT = {v: k for k, v in SIDE_VT2BINANCE.items()}

binance_symbols = set()
symbol_name_map = {}


class BinanceGateway(BaseGateway):
    """
    VN Trader Gateway for Binance connection
    """

    default_setting = {
        "API Key": "",
        "Secret Key": "",
        "会话数": 3,
        "代理地址": "",
        "代理端口": "",
    }

    exchanges = [Exchange.BINANCE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "BINANCE")

        self.order_manager = LocalOrderManager(self)

        self.rest_api = BinanceRestApi(self)

        self.active = False

        self.dataStreamNameList = []
        self.dataStreamUrl = ''
        self.dataStreamActive = False
        self.dataStreamWs = None
        self.dataStreamThread = None
        
        self.userStreamKey = ''
        self.userStreamUrl = ''
        self.userStreamActive = False
        self.userStreamWs = None
        self.userStreamThread = None   
        
        self.keepaliveCount = 0
        self.keepaliveThread = None
        
    def connect(self, setting: dict):
        """"""
        key = setting["API Key"]
        secret = setting["Secret Key"]
        session_number = setting["会话数"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.rest_api.connect(key, secret, session_number,
                              proxy_host, proxy_port)

        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.market_ws_api.subscribe(req)
        # self.trade_ws_api.subscribe(req)

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
        pass

    def query_history(self, req: HistoryRequest):
        """"""
        return self.rest_api.query_history(req)

    def close(self):
        """"""
        self.rest_api.stop()
        # self.trade_ws_api.stop()
        # self.market_ws_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        self.count += 1
        if self.count < 3:
            return

        if self.count % 60 == 0:
            self.rest_api.ping()
        # if self.count % 5 == 0:
        #     self.query_account()

    def init_query(self):
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class BinanceRestApi(RestClient):
    """
    BINANCE REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.host = ""
        self.key = ""
        self.secret = ""
        self.account_id = ""
        self.no_sign_requests = {"/api/v1/ping", "/api/v1/exchangeInfo"}
        self.recvWindow = 5000

    def sign(self, request):
        """
        Generate BINANCE signature.
        """
        request.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36"
        }
        if request.path not in self.no_sign_requests:
            sorted_params = [
                # ("AccessKeyId", self.key),
                # ("SignatureMethod", "HmacSHA256"),
                # ("SignatureVersion", "2"),
                ("recvWindow", self.recvWindow),
                ("timestamp", int(time() * 1000))
            ]

            if request.params:
                sorted_params.extend(list(request.params.items()))
                sorted_params = list(sorted(sorted_params))
            query = urllib.parse.urlencode(sorted_params)
            signature = hmac.new(self.secret.encode('utf-8'), query.encode('utf-8'), hashlib.sha256).hexdigest()

            params_with_signature = dict(sorted_params)
            params_with_signature["signature"] = signature

            request.params = params_with_signature
            request.headers['X-MBX-APIKEY'] = self.key

        if request.method == "POST":
            request.headers["Content-Type"] = "application/json"

            if request.data:
                request.data = json.dumps(request.data)

        return request

    def connect(
        self,
        key: str,
        secret: str,
        session_number: int,
        proxy_host: str,
        proxy_port: int
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret

        self.host, _ = _split_url(REST_HOST)

        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

        # self.ping()
        self.query_contract()
        self.query_account()
        self.query_order()

    def ping(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v1/ping",
            callback=self.on_ping
        )

    def query_account(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v3/account",
            callback=self.on_query_account
        )

    def query_order(self, symbol=''):
        """"""
        params = {}
        if symbol:
            params['symbol'] = symbol
        self.add_request(
            method="GET",
            path="/api/v3/openOrders",
            callback=self.on_query_order,
            params=params
        )

    def query_contract(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v1/exchangeInfo",
            callback=self.on_exchange_info
        )

    def send_order(self, req: OrderRequest):
        """"""
        local_orderid = self.order_manager.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.time = datetime.now().strftime("%H:%M:%S")

        params = {
            "symbol": req.symbol,
            "type": ORDERTYPE_VT2BINANCE[req.type],
            "side": SIDE_VT2BINANCE[req.direction],
            "price": str(req.price),
            "quantity": str(req.volume),
            "timeInForce": "GTC",
            "newClientOrderId": local_orderid
        }

        self.add_request(
            method="POST",
            path="/api/v3/order",
            callback=self.on_send_order,
            extra=order,
            params=params,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        self.order_manager.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)

        params = {
            "symbol": req.symbol,
            "orderId": sys_orderid
        }
        path = f"/api/v3/order"
        self.add_request(
            method="DELETE",
            path=path,
            callback=self.on_cancel_order,
            params=params,
            extra=req
        )

    def on_query_account(self, data, request):
        """"""
        for d in data["balances"]:
            account = AccountData(
                accountid=d["asset"],
                balance=float(d["free"]) + float(d["locked"]),
                frozen=float(d["locked"]),
                gateway_name=self.gateway_name,
            )

            if account.balance:
                self.gateway.on_account(account)

    def on_query_order(self, data, request):
        """"""

        for d in data:
            sys_orderid = d["orderId"]
            local_orderid = d["clientOrderId"]

            order_type = ORDERTYPE_BINANCE2VT[d["type"]]
            direction = SIDE_BINANCE2VT[d["side"]]
            dt = datetime.fromtimestamp(d["time"] / 1000)
            time = dt.strftime("%H:%M:%S")

            order = OrderData(
                orderid=local_orderid,
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                price=float(d["price"]),
                volume=float(d["origQty"]),
                type=order_type,
                direction=direction,
                traded=float(d["executedQty"]),
                status=STATUS_BINANCE2VT.get(d["status"], None),
                time=time,
                gateway_name=self.gateway_name,
            )

            self.order_manager.on_order(order)
            self.order_manager.update_orderid_map(local_orderid, sys_orderid)
            self.order_manager.set_order_count(int(local_orderid))

        self.gateway.write_log("委托信息查询成功")

    def on_exchange_info(self, data, request):  # type: (dict, Request)->None
        """"""
        for d in data["symbols"]:
            base_currency = d["baseAsset"]
            quote_currency = d["quoteAsset"]
            name = f"{base_currency.upper()}/{quote_currency.upper()}"
            pricetick = 1 / pow(10, d["quotePrecision"])
            min_volume = 1 / pow(10, d["baseAssetPrecision"])
            
            contract = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                name=name,
                pricetick=pricetick,
                size=1,
                min_volume=min_volume,
                product=Product.SPOT,
                gateway_name=self.gateway_name,
                history_data=True,
            )
            self.gateway.on_contract(contract)

            binance_symbols.add(contract.symbol)
            symbol_name_map[contract.symbol] = contract.name

        self.gateway.write_log("合约信息查询成功")

    def on_send_order(self, data, request):
        """"""
        order = request.extra

        if "orderId" not in data:
            order.status = Status.REJECTED
            self.order_manager.on_order(order)
            return
        sys_orderid = data["orderId"]

        self.order_manager.update_orderid_map(order.orderid, sys_orderid)
        order.status = STATUS_BINANCE2VT[data["status"]]
        self.order_manager.on_order(order)

    def on_ping(self, data, request):
        """"""
        pass

    def on_send_order_failed(self, status_code: str, request: Request):
        """
        Callback when sending order failed on server.
        """
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
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, data, request):
        """"""
        cancel_request = request.extra
        local_orderid = cancel_request.orderid
        order = self.order_manager.get_order_with_local_orderid(local_orderid)

        order.status = STATUS_BINANCE2VT[data["status"]]
        if order.status == Status.CANCELLED:
            self.gateway.write_log(f"委托撤单成功：{order.orderid}")
            self.query_account()
        
        self.order_manager.on_order(order)
        
    def check_error(self, data: dict, func: str = ""):
        """"""
        if data["status"] != "error":
            return False
        
        error_code = data["err-code"]
        error_msg = data["err-msg"]

        self.gateway.write_log(f"{func}请求出错，代码：{error_code}，信息：{error_msg}")
        return True


def _split_url(url):
    """
    将url拆分为host和path
    :return: host, path
    """
    result = re.match("\w+://([^/]*)(.*)", url)  # noqa
    if result:
        return result.group(1), result.group(2)
