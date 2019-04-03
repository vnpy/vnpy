# encoding: UTF-8
"""
"""

import hashlib
import hmac
import sys
import time
import json
import base64
import zlib
from copy import copy
from datetime import datetime
from threading import Lock
from urllib.parse import urlencode

from requests import ConnectionError

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Offset
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

REST_HOST = "https://www.okex.com"
WEBSOCKET_HOST = "wss://real.okex.com:10442/ws/v3"

STATUS_OKEX2VT = {
    "ordering": Status.SUBMITTING,
    "open": Status.NOTTRADED,
    "part_filled": Status.PARTTRADED,
    "filled": Status.ALLTRADED,
    "cancelled": Status.CANCELLED,
    "cancelling": Status.CANCELLED,
    "failure": Status.REJECTED,
}

DIRECTION_VT2OKEX = {Direction.LONG: "buy", Direction.SHORT: "sell"}
DIRECTION_OKEX2VT = {v: k for k, v in DIRECTION_VT2OKEX.items()}

ORDERTYPE_VT2OKEX = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market"
}
ORDERTYPE_OKEX2VT = {v: k for k, v in ORDERTYPE_VT2OKEX.items()}


instruments = set()
currencies = set()


class OkexGateway(BaseGateway):
    """
    VN Trader Gateway for OKEX connection.
    """

    default_setting = {
        "API Key": "",
        "Secret Key": "",
        "Passphrase": "",
        "会话数": 3,
        "代理地址": "127.0.0.1",
        "代理端口": 1080,
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(OkexGateway, self).__init__(event_engine, "OKEX")

        self.rest_api = OkexRestApi(self)
        self.ws_api = OkexWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["API Key"]
        secret = setting["Secret Key"]
        passphrase = setting["Passphrase"]
        session_number = setting["会话数"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        self.rest_api.connect(key, secret, passphrase,
                              session_number, proxy_host, proxy_port)

        self.ws_api.connect(key, secret, passphrase, proxy_host, proxy_port)

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
        pass

    def query_position(self):
        """"""
        pass

    def close(self):
        """"""
        self.rest_api.stop()
        self.ws_api.stop()


class OkexRestApi(RestClient):
    """
    OKEX REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(OkexRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.passphrase = ""

        self.order_count = 10000
        self.order_count_lock = Lock()

        self.connect_time = 0

    def sign(self, request):
        """
        Generate OKEX signature.
        """
        # Sign
        # timestamp = str(time.time())
        timestamp = get_timestamp()
        request.data = json.dumps(request.data)

        if request.params:
            path = request.path + '?' + urlencode(request.params)
        else:
            path = request.path

        msg = timestamp + request.method + path + request.data
        signature = generate_signature(msg, self.secret)

        # Add headers
        request.headers = {
            'OK-ACCESS-KEY': self.key,
            'OK-ACCESS-SIGN': signature,
            'OK-ACCESS-TIMESTAMP': timestamp,
            'OK-ACCESS-PASSPHRASE': self.passphrase,
            'Content-Type': 'application/json'
        }
        return request

    def connect(
        self,
        key: str,
        secret: str,
        passphrase: str,
        session_number: int,
        proxy_host: str,
        proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret.encode()
        self.passphrase = passphrase

        self.connect_time = int(datetime.now().strftime("%y%m%d%H%M%S"))
        
        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session_number)
        self.gateway.write_log("REST API启动成功")

        self.query_time()
        self.query_contract()
        self.query_account()
        self.query_order()

    def _new_order_id(self):
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest):
        """"""
        orderid = f"a{self.connect_time}{self._new_order_id()}"
        
        data = {
            "client_oid": orderid,
            "type": ORDERTYPE_VT2OKEX[req.type],
            "side": DIRECTION_VT2OKEX[req.direction],
            "instrument_id": req.symbol
        }

        if req.type == OrderType.MARKET:
            if req.direction == Direction.LONG:
                data["notional"] = req.volume
            else:
                data["size"] = req.volume
        else:
            data["price"] = req.price
            data["size"] = req.volume

        order = req.create_order_data(orderid, self.gateway_name)

        self.add_request(
            "POST",
            "/api/spot/v3/orders",
            callback = self.on_send_order,
            data = data,
            extra = order,
            on_failed = self.on_send_order_failed,
            on_error = self.on_send_order_error,
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        data={
            "instrument_id": req.symbol,
            "client_oid": req.orderid
        }

        path = "/api/spot/v3/cancel_orders/" + req.orderid
        self.add_request(
            "POST",
            path,
            callback = self.on_cancel_order,
            data = data,
            on_error = self.on_cancel_order_error,
        )

    def query_contract(self):
        """"""
        self.add_request(
            "GET",
            "/api/spot/v3/instruments",
            callback = self.on_query_contract
        )

    def query_account(self):
        """"""
        self.add_request(
            "GET",
            "/api/spot/v3/accounts",
            callback = self.on_query_account
        )

    def query_order(self):
        """"""
        self.add_request(
            "GET",
            "/api/spot/v3/orders_pending",
            callback = self.on_query_order
        )

    def query_time(self):
        """"""
        self.add_request(
            "GET",
            "/api/general/v3/time",
            callback=self.on_query_time
        )

    def on_query_contract(self, data, request):
        """"""
        for instrument_data in data:
            symbol = instrument_data["instrument_id"]
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.OKEX,
                name=symbol,
                product=Product.SPOT,
                size=1,
                pricetick = instrument_data["tick_size"],
                gateway_name = self.gateway_name
            )
            self.gateway.on_contract(contract)

            instruments.add(instrument_data["instrument_id"])
            currencies.add(instrument_data["base_currency"])
            currencies.add(instrument_data["quote_currency"])

        self.gateway.write_log("合约信息查询成功")

        # Start websocket api after instruments data collected
        self.gateway.ws_api.start()

    def on_query_account(self, data, request):
        """"""
        for account_data in data:
            account = AccountData(
                accountid=account_data["currency"],
                balance=float(account_data["balance"]),
                frozen=float(account_data["hold"]),
                gateway_name=self.gateway_name
            )
            self.gateway.on_account(account)

        self.gateway.write_log("账户资金查询成功")

    def on_query_order(self, data, request):
        """"""
        for order_data in data:
            order = OrderData(
                symbol=order_data["instrument_id"],
                exchange=Exchange.OKEX,
                type=ORDERTYPE_OKEX2VT[order_data["type"]],
                orderid=order_data["client_oid"],
                direction=DIRECTION_OKEX2VT[order_data["side"]],
                price=float(order_data["price"]),
                volume=float(order_data["size"]),
                time=order_data["timestamp"][11:19],
                status=STATUS_OKEX2VT[order_data["status"]],
                gateway_name=self.gateway_name,
            )
            self.gateway.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def on_query_time(self, data, request):
        """"""
        server_time = data["iso"]
        local_time = datetime.utcnow().isoformat()
        msg = f"服务器时间：{server_time}，本机时间：{local_time}"
        self.gateway.write_log(msg)

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

    def on_send_order(self, data, request):
        """Websocket will push a new order status"""
        order = request.extra

        error_msg = data["error_message"]
        if error_msg:
            order.status = Status.REJECTED
            self.gateway.on_order(order)
        
        self.gateway.write_log(f"委托失败：{error_msg}")

    def on_cancel_order_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when cancelling order failed on server.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, data, request):
        """Websocket will push a new order status"""
        pass

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


class OkexWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(OkexWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.passphrase = ""

        self.trade_count = 10000
        self.connect_time = 0

        self.callbacks = {}
        self.ticks = {}

    def connect(
        self,
        key: str,
        secret: str,
        passphrase: str,
        proxy_host: str,
        proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret.encode()
        self.passphrase = passphrase

        self.connect_time = int(datetime.now().strftime("%y%m%d%H%M%S"))

        self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        # self.start()

    def unpack_data(self, data):
        """"""
        return json.loads(zlib.decompress(data, -zlib.MAX_WBITS))

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data upate.
        """
        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            name=req.symbol,
            datetime=datetime.now(),
            gateway_name=self.gateway_name,
        )
        self.ticks[req.symbol] = tick

        channel_ticker = f"spot/ticker:{req.symbol}"
        channel_depth = f"spot/depth5:{req.symbol}"

        self.callbacks[channel_ticker] = self.on_ticker
        self.callbacks[channel_depth] = self.on_depth

        req = {
            "op": "subscribe",
            "args": [channel_ticker, channel_depth]
        }
        self.send_packet(req)

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")
        self.login()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        if "event" in packet:
            event = packet["event"]
            if event == "subscribe":
                return
            elif event == "error":
                msg = packet["message"]
                self.gateway.write_log(f"Websocket API请求异常：{msg}")
            elif event == "login":
                self.on_login(packet)
        else:
            channel = packet["table"]
            data = packet["data"]
            callback = self.callbacks[channel]

            try:
                for d in data:
                    callback(d)
            except:
                import traceback
                traceback.print_exc()
                print(packet)

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
        timestamp = str(time.time())

        msg = timestamp + 'GET' + '/users/self/verify'
        signature = generate_signature(msg, self.secret)

        req = {
            "op": "login",
            "args": [
                self.key,
                self.passphrase,
                timestamp,
                signature.decode("utf-8")
            ]
        }
        self.send_packet(req)
        self.callbacks['login'] = self.on_login

    def subscribe_topic(self):
        """
        Subscribe to all private topics.
        """
        self.callbacks["spot/ticker"] = self.on_ticker
        self.callbacks["spot/depth5"] = self.on_depth
        self.callbacks["spot/account"] = self.on_account
        self.callbacks["spot/order"] = self.on_order

        # Subscribe to order update
        channels = []
        for instrument_id in instruments:
            channel = f"spot/order:{instrument_id}"
            channels.append(channel)

        req = {
            "op": "subscribe",
            "args": channels
        }
        self.send_packet(req)

        # Subscribe to account update
        channels = []
        for currency in currencies:
            channel = f"spot/account:{currency}"
            channels.append(channel)

        req = {
            "op": "subscribe",
            "args": channels
        }
        self.send_packet(req)

    def on_login(self, data: dict):
        """"""
        success = data.get("success", False)

        if success:
            self.gateway.write_log("Websocket API登录成功")
            self.subscribe_topic()
        else:
            self.gateway.write_log("Websocket API登录失败")

    def on_ticker(self, d):
        """"""
        symbol = d["instrument_id"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        tick.last_price = d["last"]
        tick.open = d["open_24h"]
        tick.high = d["high_24h"]
        tick.low = d["low_24h"]
        tick.volume = d["base_volume_24h"]
        tick.datetime = datetime.strptime(
            d["timestamp"], "%Y-%m-%dT%H:%M:%S.%fZ")
        self.gateway.on_tick(copy(tick))

    def on_depth(self, d):
        """"""
        for tick_data in d:
            symbol = d["instrument_id"]
            tick = self.ticks.get(symbol, None)
            if not tick:
                return

            bids = d["bids"]
            asks = d["asks"]
            for n, buf in enumerate(bids):
                price, volume, _ = buf
                tick.__setattr__("bid_price_%s" % (n + 1), price)
                tick.__setattr__("bid_volume_%s" % (n + 1), volume)

            for n, buf in enumerate(asks):
                price, volume, _ = buf
                tick.__setattr__("ask_price_%s" % (n + 1), price)
                tick.__setattr__("ask_volume_%s" % (n + 1), volume)

            tick.datetime = datetime.strptime(
                d["timestamp"], "%Y-%m-%dT%H:%M:%S.%fZ")
            self.gateway.on_tick(copy(tick))

    def on_order(self, d):
        """"""
        order = OrderData(
            symbol=d["instrument_id"],
            exchange=Exchange.OKEX,
            type=ORDERTYPE_OKEX2VT[d["type"]],
            orderid=d["client_oid"],
            direction=DIRECTION_OKEX2VT[d["side"]],
            price=d["price"],
            volume=d["size"],
            traded=d["filled_size"],
            time=d["timestamp"][11:19],
            status=STATUS_OKEX2VT[d["status"]],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_order(copy(order))

        trade_volume = float(d.get("last_fill_qty", 0))
        if not trade_volume:
            return

        self.trade_count += 1
        tradeid = f"{self.connect_time}{self.trade_count}"

        trade = TradeData(
            symbol=order.symbol,
            exchange=order.exchange,
            orderid=order.orderid,
            tradeid=tradeid,
            direction=order.direction,
            price=float(d["last_fill_px"]),
            volume=float(trade_volume),
            time=d["last_fill_time"][11:19],
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def on_account(self, d):
        """"""
        account = AccountData(
            accountid=d["currency"],
            balance=float(d["balance"]),
            frozen=float(d["hold"]),
            gateway_name=self.gateway_name
        )
        
        self.gateway.on_account(copy(account))


def generate_signature(msg: str, secret_key: str):
    """OKEX V3 signature"""
    return base64.b64encode(hmac.new(secret_key, msg.encode(), hashlib.sha256).digest())


def get_timestamp():
    """"""
    now = datetime.utcnow()
    timestamp = now.isoformat("T", "milliseconds")
    return timestamp + "Z"
