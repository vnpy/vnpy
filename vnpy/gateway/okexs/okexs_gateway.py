"""
Author: nanoric
"""

import base64
import hashlib
import hmac
import json
import sys
import time
import zlib
from copy import copy
from datetime import datetime, timezone
from threading import Lock
from urllib.parse import urlencode
from typing import Dict

from requests import ConnectionError

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (Direction, Exchange, Interval, Offset, OrderType, Product, Status)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (AccountData, BarData, CancelRequest, ContractData, HistoryRequest,
                                OrderData, OrderRequest, PositionData, SubscribeRequest, TickData,
                                TradeData)

_ = lambda x: x  # noqa
REST_HOST = "https://www.okex.com"
WEBSOCKET_HOST = "wss://real.okex.com:8443/ws/v3"

STATUS_OKEXS2VT = {
    "0": Status.NOTTRADED,
    "1": Status.PARTTRADED,
    "2": Status.ALLTRADED,
    "3": Status.SUBMITTING,
    "4": Status.SUBMITTING,
    "-1": Status.CANCELLED,
    "-2": Status.REJECTED
}

ORDERTYPE_OKEXS2VT = {
    "0": OrderType.LIMIT,
    "1": OrderType.MARKET,
}

TYPE_OKEXS2VT = {
    "1": (Offset.OPEN, Direction.LONG),
    "2": (Offset.OPEN, Direction.SHORT),
    "3": (Offset.CLOSE, Direction.SHORT),
    "4": (Offset.CLOSE, Direction.LONG),
}
TYPE_VT2OKEXS = {v: k for k, v in TYPE_OKEXS2VT.items()}

DIRECTION_OKEXS2VT = {
    "long": Direction.LONG,
    "short": Direction.SHORT,
}

INTERVAL_VT2OKEXS = {
    Interval.MINUTE: "60",
    Interval.HOUR: "3600",
    Interval.DAILY: "86400",
}

instruments = set()
utc_tz = timezone.utc
local_tz = datetime.now(timezone.utc).astimezone().tzinfo


class OkexsGateway(BaseGateway):
    """
    VN Trader Gateway for OKEX connection.
    """

    default_setting = {
        "API Key": "",
        "Secret Key": "",
        "Passphrase": "",
        "会话数": 3,
        "代理地址": "",
        "代理端口": "",
    }

    exchanges = [Exchange.OKEX]

    def __init__(self, event_engine):
        """Constructor"""
        super(OkexsGateway, self).__init__(event_engine, "OKEXS")

        self.rest_api = OkexsRestApi(self)
        self.ws_api = OkexsWebsocketApi(self)

        self.orders = {}

    def connect(self, setting: dict):
        """"""
        key = setting["API Key"]
        secret = setting["Secret Key"]
        passphrase = setting["Passphrase"]
        session_number = setting["会话数"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

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

    def query_history(self, req: HistoryRequest):
        """"""
        return self.rest_api.query_history(req)

    def close(self):
        """"""
        self.rest_api.stop()
        self.ws_api.stop()

    def on_order(self, order: OrderData):
        """"""
        self.orders[order.orderid] = order
        super().on_order(order)

    def get_order(self, orderid: str):
        """"""
        return self.orders.get(orderid, None)


class OkexsRestApi(RestClient):
    """
    OKEX Swap REST API
    """

    def __init__(self, gateway: "OkexsGateway"):
        """"""
        super(OkexsRestApi, self).__init__()

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
        Generate OKEX Swap signature.
        """
        # Sign
        timestamp = generate_timestamp()
        request.data = json.dumps(request.data)

        if request.params:
            path = request.path + "?" + urlencode(request.params)
        else:
            path = request.path

        msg = timestamp + request.method + path + request.data
        signature = generate_signature(msg, self.secret)

        # Add headers
        request.headers = {
            "OK-ACCESS-KEY": self.key,
            "OK-ACCESS-SIGN": signature,
            "OK-ACCESS-TIMESTAMP": timestamp,
            "OK-ACCESS-PASSPHRASE": self.passphrase,
            "Content-Type": "application/json"
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
        self.query_accounts()
        self.query_position()

    def _new_order_id(self):
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest):
        """"""
        # Need both offset and direction for sending order.
        if (req.offset, req.direction) not in TYPE_VT2OKEXS:
            return ""

        orderid = f"a{self.connect_time}{self._new_order_id()}"

        data = {
            "client_oid": orderid,
            "type": TYPE_VT2OKEXS[(req.offset, req.direction)],
            "instrument_id": req.symbol,
            "price": str(req.price),
            "size": str(int(req.volume)),
        }

        if req.type == OrderType.MARKET:
            data["match_price"] = "1"
        else:
            data["match_price"] = "0"

        order = req.create_order_data(orderid, self.gateway_name)

        self.add_request(
            "POST",
            "/api/swap/v3/order",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error,
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        self.add_request(
            "POST",
            f"/api/swap/v3/cancel_order/{req.symbol}/{req.orderid}",
            callback=self.on_cancel_order,
            on_error=self.on_cancel_order_error,
            on_failed=self.on_cancel_order_failed,
            extra=req
        )

    def query_contract(self):
        """"""
        self.add_request(
            "GET",
            "/api/swap/v3/instruments",
            callback=self.on_query_contracts
        )

    def query_accounts(self):
        """"""
        self.add_request(
            "GET",
            "/api/swap/v3/accounts",
            callback=self.on_query_accounts
        )

    def query_orders(self):
        """"""
        for instrument in instruments:
            # get waiting orders
            self.add_request(
                "GET",
                f"/api/swap/v3/orders/{instrument}?status=0",
                callback=self.on_query_order,
            )

            # get part traded orders
            self.add_request(
                "GET",
                f"/api/swap/v3/orders/{instrument}?status=1",
                callback=self.on_query_order,
            )

    def query_position(self):
        """"""
        self.add_request(
            "GET",
            "/api/swap/v3/position",
            callback=self.on_query_position
        )

    def query_time(self):
        """"""
        self.add_request(
            "GET",
            "/api/general/v3/time",
            callback=self.on_query_time
        )

    def on_query_contracts(self, data, request):
        """"""
        for instrument_data in data:
            symbol = instrument_data["instrument_id"]
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.OKEX,
                name=symbol,
                product=Product.FUTURES,
                size=int(instrument_data["size_increment"]),
                pricetick=float(instrument_data["tick_size"]),
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

            instruments.add(instrument_data["instrument_id"])

        self.gateway.write_log("合约信息查询成功")

        # Start websocket api after instruments data collected
        self.gateway.ws_api.start()

        # and query pending orders
        self.query_orders()

    def on_query_accounts(self, data, request):
        """"""
        for info in data['info']:
            account = _parse_account_info(info, gateway_name=self.gateway_name)
            self.gateway.on_account(account)

        self.gateway.write_log("账户资金查询成功")

    def on_query_position(self, datas, request):
        """"""
        for data in datas:
            holdings = data['holding']

            for holding in holdings:
                symbol = holding["instrument_id"].upper()
                pos = _parse_position_holding(holding, symbol=symbol,
                                              gateway_name=self.gateway_name)
                self.gateway.on_position(pos)

    def on_query_order(self, data, request):
        """"""
        for order_info in data["order_info"]:
            order = _parse_order_info(order_info, gateway_name=self.gateway_name)
            self.gateway.on_order(order)

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
        order.time = datetime.now().strftime("%H:%M:%S.%f")
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
        """
        Websocket will push a new order status
        """
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
        """
        Websocket will push a new order status
        """
        pass

    def on_cancel_order_failed(self, status_code: int, request: Request):
        """
        If cancel failed, mark order status to be rejected.
        """
        req = request.extra
        order = self.gateway.get_order(req.orderid)
        if order:
            order.status = Status.REJECTED
            self.gateway.on_order(order)

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

    def query_history(self, req: HistoryRequest):
        """"""
        buf = {}
        end_time = None

        for i in range(10):
            path = f"/api/swap/v3/instruments/{req.symbol}/candles"

            # Create query params
            params = {
                "granularity": INTERVAL_VT2OKEXS[req.interval]
            }

            if end_time:
                params["end"] = end_time

            # Get response from server
            resp = self.request(
                "GET",
                path,
                params=params
            )

            # Break if request failed with other status code
            if resp.status_code // 100 != 2:
                msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
                self.gateway.write_log(msg)
                break
            else:
                data = resp.json()
                if not data:
                    msg = f"获取历史数据为空"
                    break

                for l in data:
                    ts, o, h, l, c, v, _ = l
                    dt = datetime.strptime(ts, "%Y-%m-%dT%H:%M:%S.%fZ")
                    bar = BarData(
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=dt,
                        interval=req.interval,
                        volume=float(v),
                        open_price=float(o),
                        high_price=float(h),
                        low_price=float(l),
                        close_price=float(c),
                        gateway_name=self.gateway_name
                    )
                    buf[bar.datetime] = bar

                begin = data[-1][0]
                end = data[0][0]
                msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
                self.gateway.write_log(msg)

                # Update start time
                end_time = begin

        index = list(buf.keys())
        index.sort()

        history = [buf[i] for i in index]
        return history


class OkexsWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(OkexsWebsocketApi, self).__init__()
        self.ping_interval = 20  # OKEX use 30 seconds for ping

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.passphrase = ""

        self._last_trade_id = 10000
        self.connect_time = 0

        self.subscribed: Dict[str, SubscribeRequest] = {}
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

    def unpack_data(self, data):
        """"""
        return json.loads(zlib.decompress(data, -zlib.MAX_WBITS))

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
        self.ticks[req.symbol] = tick

        channel_ticker = f"swap/ticker:{req.symbol}"
        channel_depth = f"swap/depth5:{req.symbol}"

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
            callback = self.callbacks.get(channel, None)

            if callback:
                for d in data:
                    callback(d)

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(exception_type, exception_value, tb))

    def login(self):
        """
        Need to login befores subscribe to websocket topic.
        """
        timestamp = str(time.time())

        msg = timestamp + "GET" + "/users/self/verify"
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
        self.callbacks["login"] = self.on_login

    def subscribe_topic(self):
        """
        Subscribe to all private topics.
        """
        self.callbacks["swap/ticker"] = self.on_ticker
        self.callbacks["swap/depth5"] = self.on_depth
        self.callbacks["swap/account"] = self.on_account
        self.callbacks["swap/order"] = self.on_order
        self.callbacks["swap/position"] = self.on_position

        # Subscribe to order update
        channels = []
        for instrument_id in instruments:
            channel = f"swap/order:{instrument_id}"
            channels.append(channel)

        req = {
            "op": "subscribe",
            "args": channels
        }
        self.send_packet(req)

        # Subscribe to account update
        channels = []
        for instrument in instruments:
            if instrument != "USD":
                channel = f"swap/account:{instrument}"
                channels.append(channel)

        req = {
            "op": "subscribe",
            "args": channels
        }
        self.send_packet(req)

        # Subscribe to position update
        channels = []
        for instrument_id in instruments:
            channel = f"swap/position:{instrument_id}"
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

            for req in list(self.subscribed.values()):
                self.subscribe(req)
        else:
            self.gateway.write_log("Websocket API登录失败")

    def on_ticker(self, d):
        """"""
        symbol = d["instrument_id"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        # Filter last price with 0 value
        last_price = float(d["last"])
        if not last_price:
            return

        tick.last_price = last_price
        tick.high_price = float(d["high_24h"])
        tick.low_price = float(d["low_24h"])
        tick.volume = float(d["volume_24h"])
        tick.datetime = _parse_timestamp(d["timestamp"])

        self.gateway.on_tick(copy(tick))

    def on_depth(self, d):
        """"""
        symbol = d["instrument_id"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        bids = d["bids"]
        asks = d["asks"]
        for n, buf in enumerate(bids):
            price, volume, _, __ = buf
            tick.__setattr__("bid_price_%s" % (n + 1), price)
            tick.__setattr__("bid_volume_%s" % (n + 1), volume)

        for n, buf in enumerate(asks):
            price, volume, _, __ = buf
            tick.__setattr__("ask_price_%s" % (n + 1), price)
            tick.__setattr__("ask_volume_%s" % (n + 1), volume)

        tick.datetime = _parse_timestamp(d["timestamp"])
        self.gateway.on_tick(copy(tick))

    def on_order(self, data):
        """"""
        order = _parse_order_info(data, gateway_name=self.gateway_name)
        self.gateway.on_order(copy(order))

        traded_volume = float(data.get("last_fill_qty", 0))
        if traded_volume != 0:
            tradeid = f"{self.connect_time}{self._last_trade_id}"
            self._last_trade_id += 1

            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=tradeid,
                direction=order.direction,
                offset=order.offset,
                price=float(data["last_fill_px"]),
                volume=float(traded_volume),
                time=order.time,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_trade(trade)

    def on_account(self, data):
        """"""
        account = _parse_account_info(data, gateway_name=self.gateway_name)
        self.gateway.on_account(account)

    def on_position(self, data):
        """"""
        holdings = data['holding']
        symbol = data['instrument_id']
        for holding in holdings:
            pos = _parse_position_holding(holding=holding, symbol=symbol,
                                          gateway_name=self.gateway_name)
            self.gateway.on_position(pos)


def generate_signature(msg: str, secret_key: str):
    """OKEX V3 signature"""
    return base64.b64encode(hmac.new(secret_key, msg.encode(), hashlib.sha256).digest())


def generate_timestamp():
    """"""
    now = datetime.utcnow()
    timestamp = now.isoformat("T", "milliseconds")
    return timestamp + "Z"


def _parse_timestamp(timestamp):
    """parse timestamp into local time."""
    time = datetime.strptime(timestamp, "%Y-%m-%dT%H:%M:%S.%fZ")
    utc_time = time.replace(tzinfo=utc_tz)
    local_time = utc_time.astimezone(local_tz)
    return local_time


def _parse_position_holding(holding, symbol, gateway_name):
    """parse single 'holding' record in replied position data to PositionData. """
    position = int(holding["position"])
    pos = PositionData(
        symbol=symbol,
        exchange=Exchange.OKEX,
        direction=DIRECTION_OKEXS2VT[holding['side']],
        volume=position,
        frozen=float(position - float(holding["avail_position"])),
        price=float(holding['avg_cost']),
        pnl=float(holding['realized_pnl']),
        gateway_name=gateway_name,
    )
    return pos


def _parse_account_info(info, gateway_name):
    """
    parse single 'info' record inside account reply to AccountData.
    """
    account = AccountData(
        accountid=info['instrument_id'].upper(),
        balance=float(info["equity"]),
        frozen=float(info["margin_frozen"]),
        gateway_name=gateway_name,
    )
    return account


def _parse_order_info(order_info, gateway_name: str):
    offset, direction = TYPE_OKEXS2VT[order_info["type"]]
    order_id = order_info["client_oid"]
    if not order_id:
        order_id = order_info["order_id"]
    order = OrderData(
        symbol=order_info["instrument_id"],
        exchange=Exchange.OKEX,
        type=ORDERTYPE_OKEXS2VT[order_info["order_type"]],
        orderid=order_id,
        direction=direction,
        offset=offset,
        traded=int(order_info["filled_qty"]),
        price=float(order_info["price"]),
        volume=float(order_info["size"]),
        time=_parse_timestamp(order_info["timestamp"]).strftime("%H:%M:%S"),
        status=STATUS_OKEXS2VT[order_info["status"]],
        gateway_name=gateway_name,
    )
    return order
