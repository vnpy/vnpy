"""
Author: vigarbuaa
"""

import sys
import json
from threading import Lock
from datetime import datetime
import pytz

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.event import Event
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
)


REST_HOST = "https://api.alpaca.markets"                # Live trading
WEBSOCKET_HOST = "wss://api.alpaca.markets/stream"
PAPER_REST_HOST = "https://paper-api.alpaca.markets"    # Paper Trading
PAPER_WEBSOCKET_HOST = "wss://paper-api.alpaca.markets/stream"

DATA_REST_HOST = "https://data.alpaca.markets"


STATUS_ALPACA2VT = {
    "new": Status.NOTTRADED,
    "partially_filled": Status.PARTTRADED,
    "filled": Status.ALLTRADED,
    "canceled": Status.CANCELLED,
    "expired": Status.CANCELLED,
    "rejected": Status.REJECTED
}

DIRECTION_VT2ALPACA = {
    Direction.LONG: "buy",
    Direction.SHORT: "sell"
}
DIRECTION_ALPACA2VT = {
    "buy": Direction.LONG,
    "sell": Direction.SHORT,
    "long": Direction.LONG,
    "short": Direction.SHORT
}

ORDERTYPE_VT2ALPACA = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market"
}
ORDERTYPE_ALPACA2VT = {v: k for k, v in ORDERTYPE_VT2ALPACA.items()}

LOCAL_SYS_MAP = {}
UTC_TZ = pytz.utc


class AlpacaGateway(BaseGateway):
    """
    VN Trader Gateway for Alpaca connection.
    """

    default_setting = {
        "KEY ID": "",
        "Secret Key": "",
        "会话数": 10,
        "服务器": ["REAL", "PAPER"]
    }

    exchanges = [Exchange.SMART]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "ALPACA")

        self.rest_api = AlpacaRestApi(self)
        self.ws_api = AlpacaWebsocketApi(self)
        self.data_rest_api = AlpacaDataRestApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["KEY ID"]
        secret = setting["Secret Key"]
        session = setting["会话数"]
        server = setting["服务器"]

        rest_url = REST_HOST if server == "REAL" else PAPER_REST_HOST
        websocket_url = WEBSOCKET_HOST if server == "REAL" else PAPER_WEBSOCKET_HOST

        self.rest_api.connect(key, secret, session, rest_url)
        self.data_rest_api.connect(key, secret, session)
        self.ws_api.connect(key, secret, websocket_url)

        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.data_rest_api.subscribe(req)

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
        self.data_rest_api.stop()
        self.ws_api.stop()

    def init_query(self):
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_timer_event(self, event: Event):
        """"""
        self.data_rest_api.query_bar()

        self.count += 1
        if self.count < 5:
            return
        self.count = 0

        self.query_account()
        self.query_position()


class AlpacaRestApi(RestClient):
    """
    Alpaca REST API
    """

    def __init__(self, gateway: AlpacaGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.order_count = 1_000_000
        self.order_count_lock = Lock()

        self.connect_time = 0

        self.cancel_reqs = {}

    def sign(self, request):
        """
        Generate Alpaca signature.
        """
        headers = {
            "APCA-API-KEY-ID": self.key,
            "APCA-API-SECRET-KEY": self.secret,
            "Content-Type": "application/json"
        }

        request.headers = headers
        request.allow_redirects = False
        request.data = json.dumps(request.data)
        return request

    def connect(
        self,
        key: str,
        secret: str,
        session_num: int,
        url: str,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret

        self.connect_time = (
            int(datetime.now(UTC_TZ).strftime("%y%m%d%H%M%S")) * self.order_count
        )

        self.init(url)
        self.start(session_num)

        self.gateway.write_log("REST API启动成功")
        self.query_contract()
        self.query_account()
        self.query_position()
        self.query_order()

    def query_contract(self):
        """"""
        params = {"status": "active"}

        self.add_request(
            "GET",
            "/v2/assets",
            params=params,
            callback=self.on_query_contract
        )

    def query_account(self):
        """"""
        self.add_request(
            method="GET",
            path="/v2/account",
            callback=self.on_query_account
        )

    def query_position(self):
        """"""
        self.add_request(
            method="GET",
            path="/v2/positions",
            callback=self.on_query_position
        )

    def query_order(self):
        """"""
        params = {
            "status": "open"
        }

        self.add_request(
            method="GET",
            path="/v2/orders",
            params=params,
            callback=self.on_query_order
        )

    def _new_order_id(self):
        """"""
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest):
        """"""
        local_orderid = str(self.connect_time + self._new_order_id())

        data = {
            "symbol": req.symbol,
            "qty": str(req.volume),
            "side": DIRECTION_VT2ALPACA[req.direction],
            "type": ORDERTYPE_VT2ALPACA[req.type],
            "time_in_force": "day",
            "client_order_id": local_orderid
        }

        if data["type"] == "limit":
            data["limit_price"] = str(req.price)

        order = req.create_order_data(local_orderid, self.gateway_name)
        self.gateway.on_order(order)

        self.add_request(
            "POST",
            "/v2/orders",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error,
        )

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        sys_orderid = LOCAL_SYS_MAP.get(req.orderid, None)
        if not sys_orderid:
            self.cancel_reqs[req.orderid] = req
            return

        path = f"/v2/orders/{sys_orderid}"

        self.add_request(
            "DELETE",
            path,
            callback=self.on_cancel_order,
            extra=req
        )

    def on_query_contract(self, data, request: Request):
        """"""
        for d in data:
            symbol = d["symbol"]

            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.SMART,
                name=symbol,
                product=Product.SPOT,
                size=1,
                pricetick=0.01,
                gateway_name=self.gateway_name
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

    def on_query_account(self, data, request):
        """"""
        account = AccountData(
            accountid=data["id"],
            balance=float(data["equity"]),
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def on_query_position(self, data, request):
        """"""
        for d in data:
            position = PositionData(
                symbol=d["symbol"],
                exchange=Exchange.SMART,
                direction=DIRECTION_ALPACA2VT[d["side"]],
                volume=int(d["qty"]),
                price=float(d["avg_entry_price"]),
                pnl=float(d["unrealized_pl"]),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_position(position)

    def update_order(self, d: dict):
        """"""
        sys_orderid = d["id"]
        local_orderid = d["client_order_id"]
        LOCAL_SYS_MAP[local_orderid] = sys_orderid

        direction = DIRECTION_ALPACA2VT[d["side"]]
        order_type = ORDERTYPE_ALPACA2VT[d["type"]]

        order = OrderData(
            orderid=local_orderid,
            symbol=d["symbol"],
            exchange=Exchange.SMART,
            price=float(d["limit_price"]),
            volume=float(d["qty"]),
            type=order_type,
            direction=direction,
            traded=float(d["filled_qty"]),
            status=STATUS_ALPACA2VT.get(d["status"], Status.SUBMITTING),
            datetime=generate_datetime(d["created_at"]),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_order(order)

    def on_query_order(self, data, request):
        """"""
        for d in data:
            self.update_order(d)

        self.gateway.write_log("委托信息查询成功")

    def on_send_order(self, data, request: Request):
        """"""
        self.update_order(data)

        order = request.extra
        if order.orderid in self.cancel_reqs:
            req = self.cancel_reqs.pop(order.orderid)
            self.cancel_order(req)

    def on_send_order_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg = f"请求失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_send_order_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback to handler request exception.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )

    def on_cancel_order(self, data, request):
        """"""
        req = request.extra
        msg = f"撤单成功，委托号：{req.orderid}"
        self.gateway.write_log(msg)


class AlpacaWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway: AlpacaGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.trade_count = 0

        self.key = ""
        self.secret = ""

    def connect(
        self, key: str, secret: str, url: str
    ):
        """"""
        self.key = key
        self.secret = secret

        self.init(url)
        self.start()

    def authenticate(self):
        """"""
        params = {
            "action": "authenticate",
            "data": {
                "key_id": self.key,
                "secret_key": self.secret
            }
        }
        self.send_packet(params)

    def on_authenticate(self, data):
        """"""
        if data["status"] == "authorized":
            self.gateway.write_log("Websocket API登录成功")
        else:
            self.gateway.write_log("Websocket API登录失败")
            return

        params = {
            "action": "listen",
            "data": {
                "streams": ["trade_updates", "account_updates"]
            }
        }
        self.send_packet(params)

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")
        self.authenticate()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        stream = packet["stream"]
        data = packet["data"]

        if stream == "authorization":
            self.on_authenticate(data)
        elif stream == "listening":
            streams = data["streams"]

            if "trade_updates" in streams:
                self.gateway.write_log("委托成交推送订阅成功")

            if "account_updates" in streams:
                self.gateway.write_log("资金变化推送订阅成功")

        elif stream == "trade_updates":
            self.on_order(data)
        elif stream == "account_updates":
            self.on_account(data)

    def on_order(self, data):
        """"""
        # Update order
        d = data["order"]
        sys_orderid = d["id"]
        local_orderid = d["client_order_id"]
        LOCAL_SYS_MAP[local_orderid] = sys_orderid

        direction = DIRECTION_ALPACA2VT[d["side"]]
        order_type = ORDERTYPE_ALPACA2VT[d["type"]]

        order = OrderData(
            orderid=local_orderid,
            symbol=d["symbol"],
            exchange=Exchange.SMART,
            price=float(d["limit_price"]),
            volume=float(d["qty"]),
            type=order_type,
            direction=direction,
            traded=float(d["filled_qty"]),
            status=STATUS_ALPACA2VT.get(d["status"], Status.SUBMITTING),
            datetime=generate_datetime(d["created_at"]),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_order(order)

        # Update Trade
        event = data.get("event", "")
        if event != "fill":
            return

        self.trade_count += 1

        trade = TradeData(
            symbol=order.symbol,
            exchange=order.exchange,
            orderid=order.orderid,
            tradeid=str(self.trade_count),
            direction=order.direction,
            price=float(data["price"]),
            volume=int(data["qty"]),
            datetime=generate_datetime(data["timestamp"]),
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def on_account(self, data):
        """"""
        account = AccountData(
            accountid=data["id"],
            balance=float(data["equity"]),
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)


class AlpacaDataRestApi(RestClient):
    """
    Alpaca Market Data REST API
    """

    def __init__(self, gateway: AlpacaGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.symbols = set()

    def sign(self, request):
        """
        Generate Alpaca signature.
        """
        headers = {
            "APCA-API-KEY-ID": self.key,
            "APCA-API-SECRET-KEY": self.secret,
            "Content-Type": "application/json"
        }

        request.headers = headers
        request.allow_redirects = False
        return request

    def connect(
        self,
        key: str,
        secret: str,
        session_num: int
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret

        self.init(DATA_REST_HOST)
        self.start(session_num)

        self.gateway.write_log("行情REST API启动成功")

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.symbols.add(req.symbol)

    def query_bar(self):
        """"""
        if not self._active or not self.symbols:
            return

        params = {
            "symbols": ",".join(list(self.symbols)),
            "limit": 1
        }

        self.add_request(
            method="GET",
            path="/v1/bars/1Min",
            params=params,
            callback=self.on_query_bar
        )

    def on_query_bar(self, data, request):
        """"""
        for symbol, buf in data.items():
            d = buf[0]

            tick = TickData(
                symbol=symbol,
                exchange=Exchange.SMART,
                datetime=datetime.now(UTC_TZ),
                name=symbol,
                open_price=d["o"],
                high_price=d["h"],
                low_price=d["l"],
                last_price=d["c"],
                gateway_name=self.gateway_name
            )

            self.gateway.on_tick(tick)


def generate_datetime(time_str: str) -> datetime:
    """"""
    dt = datetime.strptime(time_str, "%Y-%m-%dT%H:%M:%SZ")
    dt = UTC_TZ.localize(dt)
    return dt
