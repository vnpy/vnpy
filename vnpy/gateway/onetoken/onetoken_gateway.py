"""
"""

import hashlib
import sys
import hmac
import json
import time
from datetime import datetime
from threading import Lock
from urllib.parse import urlparse
from copy import copy

from requests import ConnectionError

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Status,
    Offset,
    Product
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    PositionData,
    AccountData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    ContractData,
    OrderData,
    TradeData
)
from vnpy.trader.event import EVENT_TIMER


REST_HOST = "https://1token.trade/api"
# DATA_WEBSOCKET_HOST = "wss://1token.trade/api/v1/ws/tick"
# TRADE_WEBSOCKET_HOST = "wss://1token.trade/api/v1/ws/trade"

DATA_WEBSOCKET_HOST = "wss://cdn.1tokentrade.cn/api/v1/ws/tick"
TRADE_WEBSOCKET_HOST = "wss://cdn.1tokentrade.cn/api/v1/ws/trade"

DIRECTION_VT2ONETOKEN = {Direction.LONG: "b", Direction.SHORT: "s"}
DIRECTION_ONETOKEN2VT = {v: k for k, v in DIRECTION_VT2ONETOKEN.items()}


EXCHANGE_VT2ONETOKEN = {
    Exchange.OKEX: "okex",
    Exchange.HUOBI: "huobi"
}
EXCHANGE_ONETOKEN2VT = {v: k for k, v in EXCHANGE_VT2ONETOKEN.items()}


class OnetokenGateway(BaseGateway):
    """
    VN Trader Gateway for 1Token connection
    """

    default_setting = {
        "OT Key": "",
        "OT Secret": "",
        "交易所": ["BINANCE", "BITMEX", "OKEX", "OKEF", "HUOBIP", "HUOBIF"],
        "账户": "",
        "会话数": 3,
        "代理地址": "127.0.0.1",
        "代理端口": 1080,
    }

    exchanges = list(EXCHANGE_VT2ONETOKEN.keys())

    def __init__(self, event_engine):
        """Constructor"""
        super(OnetokenGateway, self).__init__(event_engine, "1TOKEN")

        self.rest_api = OnetokenRestApi(self)
        self.data_ws_api = OnetokenDataWebsocketApi(self)
        self.trade_ws_api = OnetokenTradeWebsocketApi(self)

        self.count = 0

    def connect(self, setting: dict):
        """"""
        key = setting["OT Key"]
        secret = setting["OT Secret"]
        session_number = setting["会话数"]
        exchange = setting["交易所"].lower()
        account = setting["账户"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        self.rest_api.connect(key, secret, session_number,
                              exchange, account, proxy_host, proxy_port)
        self.data_ws_api.connect(proxy_host, proxy_port)
        self.trade_ws_api.connect(
            key, secret, exchange, account, proxy_host, proxy_port)

        self.init_ping()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.data_ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self):
        """"""
        pass

    def query_position(self):
        """"""
        pass

    def close(self):
        """"""
        self.rest_api.stop()
        self.data_ws_api.stop()
        self.trade_ws_api.stop()

    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < 20:
            return
        self.count = 0

        self.data_ws_api.ping()
        self.trade_ws_api.ping()

    def init_ping(self):
        """"""
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class OnetokenRestApi(RestClient):
    """
    1Token REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(OnetokenRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.exchange = ""

        self.order_count = 1_000_000
        self.order_count_lock = Lock()

        self.connect_time = 0
        self.account = ""

    def sign(self, request):
        """
        Generate 1Token signature.
        """
        method = request.method

        endpoint = "/" + request.path.split("/", 3)[3]
        # v1/trade/okex/mock-example/info -> okex/mock-example/info
        parsed_url = urlparse(endpoint)
        path = parsed_url.path

        nonce = str(int(time.time() * 1e6))
        data = request.data
        json_str = data if data else ""

        message = method + path + nonce + json_str

        signature = hmac.new(bytes(self.secret, "utf8"), bytes(
            message, "utf8"), digestmod=hashlib.sha256).hexdigest()

        headers = {"Api-Nonce": nonce,
                   "Api-Key": self.key,
                   "Api-Signature": signature,
                   "Content-Type": "application/json"}
        request.headers = headers

        return request

    def connect(
            self,
            key: str,
            secret: str,
            session_number: int,
            exchange: str,
            account: str,
            proxy_host: str,
            proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret
        self.exchange = exchange
        self.account = account

        self.connect_time = (
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        self.init(REST_HOST, proxy_host, proxy_port)

        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

        self.query_time()
        self.query_contract()
        # self.query_account()

    def _new_order_id(self):
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def query_time(self):
        """"""
        self.add_request(
            "GET",
            "/v1/basic/time",
            callback=self.on_query_time
        )

    def on_query_time(self, data, request):
        """"""
        server_timestamp = data["server_time"]
        dt = datetime.utcfromtimestamp(server_timestamp)
        server_time = dt.isoformat() + "Z"
        local_time = datetime.utcnow().isoformat()
        msg = f"服务器时间：{server_time}，本机时间：{local_time}"
        self.gateway.write_log(msg)

    def query_contract(self):
        """"""
        self.add_request(
            "GET",
            "/v1/basic/contracts?exchange={}".format(self.exchange),
            callback=self.on_query_contract
        )

    def on_query_contract(self, data, request):
        """"""
        for instrument_data in data:
            symbol = instrument_data["name"]
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange(instrument_data['symbol'].split('/')[0].upper()),
                name=symbol,
                product=Product.SPOT,  # todo
                size=float(instrument_data["min_amount"]),
                pricetick=float(instrument_data["unit_amount"]),
                gateway_name=self.gateway_name
            )
            self.gateway.on_contract(contract)
        self.gateway.write_log("合约信息查询成功")

        # Start websocket api after instruments data collected
        self.gateway.data_ws_api.start()
        self.gateway.trade_ws_api.start()

    def send_order(self, req: OrderRequest):
        """"""
        orderid = str(self.connect_time + self._new_order_id())

        data = {
            "contract": self.exchange + "/" + req.symbol,
            "price": float(req.price),
            "bs": DIRECTION_VT2ONETOKEN[req.direction],
            "amount": float(req.volume),
            "client_oid": orderid
        }

        if req.offset == Offset.CLOSE:
            data["options"] = {"close": True}
        data = json.dumps(data)
        order = req.create_order_data(orderid, self.gateway_name)

        self.add_request(
            method="POST",
            path="/v1/trade/{}/{}/orders".format(self.exchange, self.account),
            callback=self.on_send_order,
            data=data,
            params={},
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        params = {
            "client_oid": req.orderid
        }

        self.add_request(
            method="DELETE",
            path="/v1/trade/{}/{}/orders".format(self.exchange, self.account),
            callback=self.on_cancel_order,
            params=params,
            on_error=self.on_cancel_order_error,
            extra=req
        )

    def on_send_order(self, data, request):
        """Websocket will push a new order status"""
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
        """Websocket will push a new order status"""
        pass

    def on_cancel_order_error(
            self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when cancelling order failed on server.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)


class OnetokenDataWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.subscribed: Dict[str, SubscribeRequest] = {}
        self.ticks = {}
        self.callbacks = {
            "auth": self.on_login,
            "single-tick-verbose": self.on_tick
        }

    def connect(
        self,
        proxy_host: str,
        proxy_port: int
    ):
        """"""
        self.init(DATA_WEBSOCKET_HOST, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data upate.
        """
        self.subscribed[req.vt_symbol] = req
        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            name=req.symbol,
            datetime=datetime.now(),
            gateway_name=self.gateway_name,
        )

        contract_symbol = f"{req.exchange.value.lower()}/{req.symbol.lower()}"
        self.ticks[contract_symbol] = tick

        req = {
            "uri": "subscribe-single-tick-verbose",
            "contract": contract_symbol
        }
        self.send_packet(req)

    def on_connected(self):
        """"""
        self.gateway.write_log("行情Websocket API连接成功")
        self.login()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("行情Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        channel = packet.get("uri", "")
        if not channel:
            return

        data = packet.get("data", None)
        callback = self.callbacks.get(channel, None)

        if callback:
            callback(data)

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(
            exception_type, exception_value, tb))

    def login(self):
        """
        Need to login befores subscribe to websocket topic.
        """
        req = {"uri": "auth"}
        self.send_packet(req)

        self.callbacks["auth"] = self.on_login

    def on_login(self, data: dict):
        """"""
        self.gateway.write_log("行情Websocket API登录成功")
        for req in list(self.subscribed.values()):
            self.subscribe(req)
            
    def on_tick(self, data: dict):
        """"""
        contract_symbol = data["contract"]
        tick = self.ticks.get(contract_symbol, None)
        if not tick:
            return

        tick.last_price = data["last"]
        tick.datetime = datetime.strptime(
            data["time"][:-6], "%Y-%m-%dT%H:%M:%S.%f")

        bids = data["bids"]
        asks = data["asks"]
        for n, buf in enumerate(bids):
            tick.__setattr__("bid_price_%s" % (n + 1), buf["price"])
            tick.__setattr__("bid_volume_%s" % (n + 1), buf["volume"])

        for n, buf in enumerate(asks):
            tick.__setattr__("ask_price_%s" % (n + 1), buf["price"])
            tick.__setattr__("ask_volume_%s" % (n + 1), buf["volume"])

        self.gateway.on_tick(copy(tick))

    def ping(self):
        """"""
        self.send_packet({"uri": "ping"})


class OnetokenTradeWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.exchange = ""
        self.account = ""

        self.trade_count = 0

        self.callbacks = {
            "sub-info": self.on_subscribe_info,
            "sub-order": self.on_subscribe_order,
            "info": self.on_info,
            "order": self.on_order
        }

    def connect(
        self,
        key: str,
        secret: str,
        exchange: str,
        account: str,
        proxy_host: str,
        proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret
        self.exchange = exchange
        self.account = account

        # Create header for ws connection
        nonce = str(int(time.time() * 1e6))
        path = f"/ws/{self.account}"
        message = "GET" + path + nonce

        signature = hmac.new(bytes(self.secret, "utf8"), bytes(
            message, "utf8"), digestmod=hashlib.sha256).hexdigest()

        header = {
            "Api-Nonce": nonce,
            "Api-Key": self.key,
            "Api-Signature": signature
        }

        host = f"{TRADE_WEBSOCKET_HOST}/{self.exchange}/{self.account}"

        self.init(host, proxy_host, proxy_port, header=header)

    def subscribe_info(self):
        """
        Subscribe to account update.
        """
        self.send_packet({"uri": "sub-info"})

    def subscribe_order(self):
        """
        Subscribe to order update.
        """
        self.send_packet({"uri": "sub-order"})

    def on_connected(self):
        """"""
        self.gateway.write_log("交易Websocket API连接成功")
        self.subscribe_info()
        self.subscribe_order()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("交易Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        # Reply
        if "uri" in packet:
            channel = packet["uri"]

            if "data" in packet:
                data = packet["data"]
            elif "code" in packet:
                data = packet["code"]
            else:
                data = None
        # Push
        elif "action" in packet:
            channel = packet["action"]
            data = packet.get("data", None)
        # Other
        else:
            return

        callback = self.callbacks.get(channel, None)
        if callback:
            callback(data)

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(
            exception_type, exception_value, tb))

    def on_subscribe_info(self, data: str):
        """"""
        if data == "success":
            self.gateway.write_log("账户资金推送订阅成功")

    def on_subscribe_order(self, data: str):
        """"""
        if data == "success":
            self.gateway.write_log("委托更新推送订阅成功")

    def on_info(self, data: dict):
        """"""
        for account_data in data["position"]:
            _type = account_data["type"]

            # Spot
            if "spot" in _type:
                account = AccountData(
                    accountid=account_data["contract"],
                    balance=float(account_data["total_amount"]),
                    frozen=float(account_data["frozen"]),
                    gateway_name=self.gateway_name
                )
                self.gateway.on_account(account)

            # Futures
            elif _type == "future":
                long_position = PositionData(
                    symbol=account_data["contract"],
                    exchange=Exchange(self.exchange.upper()),
                    direction=Direction.LONG,
                    price=account_data["average_open_price_long"],
                    volume=account_data["total_amount_long"],
                    pnl=account_data["unrealized_long"],
                    frozen=account_data["frozen_position_long"],
                    gateway_name=self.gateway_name,
                )
                short_position = PositionData(
                    symbol=account_data["contract"],
                    exchange=Exchange(self.exchange.upper()),
                    direction=Direction.SHORT,
                    price=account_data["average_open_price_short"],
                    volume=account_data["total_amount_short"],
                    pnl=account_data["unrealized_short"],
                    frozen=account_data["frozen_position_short"],
                    gateway_name=self.gateway_name,
                )
                self.gateway.on_position(long_position)
                self.gateway.on_position(short_position)

    def on_order(self, data: dict):
        """"""
        for order_data in data:
            contract_symbol = order_data["contract"]
            exchange_str, symbol = contract_symbol.split("/")
            timestamp = order_data["entrust_time"][11:19]

            orderid = order_data["options"]["client_oid"]

            order = OrderData(
                symbol=symbol,
                exchange=EXCHANGE_ONETOKEN2VT[exchange_str],
                orderid=orderid,
                direction=DIRECTION_ONETOKEN2VT[order_data["bs"]],
                price=order_data["entrust_price"],
                volume=order_data["entrust_amount"],
                traded=order_data["dealt_amount"],
                time=timestamp,
                gateway_name=self.gateway_name
            )

            if order_data["status"] in ("withdrawn", "part-deal-withdrawn"):
                order.status = Status.CANCELLED
            else:
                if order.traded == order.volume:
                    order.status = Status.ALLTRADED
                elif not order.traded:
                    order.status = Status.NOTTRADED
                else:
                    order.status = Status.PARTTRADED

            self.gateway.on_order(order)

            # Push trade data
            if not order_data["last_dealt_amount"]:
                return

            trade_timestamp = order_data["last_update"][11:19]
            self.trade_count += 1
            if order_data["dealt_amount"]:
                self.trade_count += 1
                trade = TradeData(
                    symbol=order.symbol,
                    exchange=order.exchange,
                    orderid=orderid,
                    tradeid=str(self.trade_count),
                    direction=order.direction,
                    price=order_data["average_dealt_price"],
                    volume=order_data["dealt_amount"],
                    gateway_name=self.gateway_name,
                    time=trade_timestamp)
                self.gateway.on_trade(trade)

    def ping(self):
        """"""
        self.send_packet({"uri": "ping"})
