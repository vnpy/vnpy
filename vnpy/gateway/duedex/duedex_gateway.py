""""""

import base64
import hashlib
import hmac
import json
import sys
import time
from copy import copy
from datetime import datetime, timedelta
from threading import Lock
from typing import Any, Dict, List, Callable
from urllib.parse import urlencode
import pytz

import requests
from requests import ConnectionError

from vnpy.event import Event
from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
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
    PositionData,
    AccountData,
    ContractData,
    BarData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)

REST_HOST = "https://api.duedex.com"
BARS_REST_HOST = "https://www.duedex.com/bars"
WEBSOCKET_HOST = "wss://feed.duedex.com/v1/feed"

TESTNET_REST_HOST = "https://api.testnet.duedex.com"
TESTNET_BARS_REST_HOST = "https://testnet.duedex.com/bars"
TESTNET_WEBSOCKET_HOST = "wss://feed.testnet.duedex.com/v1/feed"

STATUS_DUEDEX2VT = {
    "new": Status.NOTTRADED,
    "partiallyFilled": Status.PARTTRADED,
    "filled": Status.ALLTRADED,
    "cancelled": Status.CANCELLED,
}

DIRECTION_VT2DUEDEX = {Direction.LONG: "long", Direction.SHORT: "short"}
DIRECTION_DUEDEX2VT = {v: k for k, v in DIRECTION_VT2DUEDEX.items()}

ORDERTYPE_VT2DUEDEX = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market",
}
ORDERTYPE_DUEDEX2VT = {v: k for k, v in ORDERTYPE_VT2DUEDEX.items()}

INTERVAL_VT2DUEDEX = {
    Interval.MINUTE: "1",
    Interval.HOUR: "60",
    Interval.DAILY: "D",
}

TIMEDELTA_MAP = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}

CHINA_TZ = pytz.timezone("Asia/Shanghai")
UTC_TZ = pytz.utc


class DuedexGateway(BaseGateway):
    """
    VN Trader Gateway for DueDEX connection.
    """

    default_setting = {
        "API Key": "",
        "API Secret": "",
        "会话数": 3,
        "服务器": ["REAL", "TESTNET"],
        "代理地址": "",
        "代理端口": "",
    }

    exchanges = [Exchange.DUEDEX]

    def __init__(self, event_engine):
        """Constructor"""
        super(DuedexGateway, self).__init__(event_engine, "DUEDEX")

        self.rest_api = DuedexRestApi(self)
        self.ws_api = DuedexWebsocketApi(self)

        event_engine.register(EVENT_TIMER, self.process_timer_event)

    def connect(self, setting: dict):
        """"""
        key = setting["API Key"]
        secret = setting["API Secret"]
        session_number = setting["会话数"]
        server = setting["服务器"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.rest_api.connect(key, secret, session_number,
                              server, proxy_host, proxy_port)

        self.ws_api.connect(key, secret, server, proxy_host, proxy_port)

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

    def process_timer_event(self, event: Event):
        """"""
        self.rest_api.reset_rate_limit()


class DuedexRestApi(RestClient):
    """
    DueDEX REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(DuedexRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.order_count = 1_000_000
        self.order_count_lock = Lock()

        self.connect_time = 0

        # Use 300 by default, and will update after first request
        self.rate_limit_limit = 300
        self.rate_limit_remaining = 300
        self.rate_limit_sleep = 0

        self.bars_url_base: str = ""

    def sign(self, request: Request) -> Request:
        """
        Generate DueDEX signature.
        """
        # Authentication is not required for public endpoints
        if request.path in ["/v1/instrument"]:
            return request

        # Sign
        timestamp = int(time.time() * 1000)
        expiration = timestamp + 30 * 1000

        if request.params:
            query = urlencode(request.params)
        else:
            query = ""

        if request.data:
            body = json.dumps(request.data, separators=(',', ':'))
            request.data = body
        else:
            body = ""

        msg = f"{request.method}|{request.path}|{timestamp}|{expiration}|{query}|{body}"
        signature = hmac.new(
            base64.b64decode(self.secret), msg.encode(), digestmod=hashlib.sha256
        ).hexdigest()

        # Add headers
        headers = {
            "Content-Type": "application/json",
            "Accept": "application/json",
            "Ddx-Timestamp": str(timestamp),
            "Ddx-Expiration": str(expiration),
            "Ddx-Key": self.key,
            "Ddx-Signature": signature,
        }

        request.headers = headers
        return request

    def connect(
        self,
        key: str,
        secret: str,
        session_number: int,
        server: str,
        proxy_host: str,
        proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret.encode()

        self.connect_time = (
            int(datetime.now(UTC_TZ).strftime("%y%m%d%H%M%S")) * self.order_count
        )

        if server == "REAL":
            self.init(REST_HOST, proxy_host, proxy_port)
            self.bars_url_base = BARS_REST_HOST
        else:
            self.init(TESTNET_REST_HOST, proxy_host, proxy_port)
            self.bars_url_base = TESTNET_BARS_REST_HOST

        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

        self.query_contract()

    def _new_order_id(self):
        """"""
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest):
        """"""
        if not self.check_rate_limit():
            return ""

        orderid = "C" + str(self.connect_time + self._new_order_id())

        data = {
            "instrument": req.symbol,
            "clientOrderId": orderid,
            "type": ORDERTYPE_VT2DUEDEX[req.type],
            "side": DIRECTION_VT2DUEDEX[req.direction],
            "size": int(req.volume),
        }

        if req.type == OrderType.LIMIT:
            data["price"] = req.price

        # Check for close order
        if req.offset == Offset.CLOSE:
            data["isCloseOrder"] = True

        order = req.create_order_data(orderid, self.gateway_name)

        self.add_request(
            "POST",
            "/v1/order",
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
        if not self.check_rate_limit():
            return

        data = {"instrument": req.symbol}
        orderid = str(req.orderid)

        if orderid.isdigit():
            data["orderId"] = req.orderid
        else:
            data["clientOrderId"] = req.orderid

        self.add_request(
            "DELETE",
            "/v1/order",
            callback=self.on_cancel_order,
            data=data,
            on_error=self.on_cancel_order_error,
        )

    def query_contract(self) -> Request:
        """"""
        if not self.check_rate_limit():
            return

        self.add_request(
            "GET",
            "/v1/instrument",
            self.on_query_contract
        )

    def query_history(self, req: HistoryRequest):
        """"""
        if not self.check_rate_limit():
            return

        history = []
        while True:
            # Create query params
            params = {
                "symbol": req.symbol,
                "resolution": INTERVAL_VT2DUEDEX[req.interval],
                "from": int(req.start.timestamp()),
                "to": int(req.end.timestamp()),
            }

            # Get response from server
            url = self.bars_url_base + "/v1/tradingView/history"
            resp = requests.get(
                url,
                params=params,
                proxies=self.proxies,
            )

            # Break if request failed with other status code
            if resp.status_code // 100 != 2:
                msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
                self.gateway.write_log(msg)
                break
            else:
                data = resp.json()
                if not data:
                    msg = f"获取历史数据为空，开始时间：{req.start.isoformat()}，结束时间：{req.end.isoformat()}"
                    break
                if data["s"] != "ok":
                    msg = f"获取历史数据失败，状态信息：{data['s']}"
                    break

                for i in range(0, len(data["t"])):
                    dt = datetime.fromtimestamp(data["t"][i])
                    dt = CHINA_TZ.localize(dt)

                    bar = BarData(
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=dt,
                        interval=req.interval,
                        volume=data["v"][i],
                        open_price=data["o"][i],
                        high_price=data["h"][i],
                        low_price=data["l"][i],
                        close_price=data["c"][i],
                        gateway_name=self.gateway_name
                    )
                    history.append(bar)

                begin = history[0].datetime
                end = history[-1].datetime
                msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
                self.gateway.write_log(msg)
                break

        return history

    def on_send_order_failed(self, status_code: str, request: Request):
        """
        Callback when sending order failed on server.
        """
        self.update_rate_limit(request)

        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        if request.response.text:
            data = request.response.json()
            msg = f"委托失败，状态码：{status_code}，类型：{data['code']}, 信息：{data['message']}"
        else:
            msg = f"委托失败，状态码：{status_code}"

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

    def on_send_order(self, data: dict, request: Request):
        """Websocket will push a new order status"""
        self.update_rate_limit(request)

    def on_cancel_order_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when cancelling order failed on server.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, data: dict, request: Request):
        """Websocket will push a new order status"""
        self.update_rate_limit(request)

    def on_query_contract(self, data: dict, request: Request):
        self.update_rate_limit(request)

        if self.check_error("查询合约", data):
            return

        for d in data["data"]:
            contract = ContractData(
                symbol=d["instrumentId"],
                exchange=Exchange.DUEDEX,
                name=d["instrumentId"],
                product=Product.FUTURES,
                size=d["lotSize"],
                pricetick=float(d["tickSize"]),
                min_volume=d["lotSize"],
                net_position=True,
                history_data=True,
                gateway_name=self.gateway_name
            )

            self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        self.update_rate_limit(request)

        data = request.response.json()
        msg = f"请求失败，状态码：{status_code}，类型：{data['code']}, 信息：{data['message']}"
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

    def check_error(self, name: str, data: dict) -> bool:
        """"""
        if data["code"]:
            error_code = data["code"]
            error_msg = data["message"]
            msg = f"{name}失败，错误代码：{error_code}，信息：{error_msg}"
            self.gateway.write_log(msg)
            return True

        return False

    def update_rate_limit(self, request: Request):
        """
        Update current request limit remaining status.
        """
        if request.response is None:
            return
        headers = request.response.headers

        self.rate_limit_remaining = int(
            headers.get("X-Rate-Limit-Remaining", 300))

        self.rate_limit_sleep = int(headers.get("Retry-After", 0))
        if self.rate_limit_sleep:
            self.rate_limit_sleep += 1      # 1 extra second sleep

    def reset_rate_limit(self):
        """
        Reset request limit remaining every 1 second.
        """
        self.rate_limit_remaining += 1
        self.rate_limit_remaining = min(
            self.rate_limit_remaining, self.rate_limit_limit)

        # Countdown of retry sleep seconds
        if self.rate_limit_sleep:
            self.rate_limit_sleep -= 1

    def check_rate_limit(self):
        """
        Check if rate limit is reached before sending out requests.
        """
        # Already received 429 from server
        if self.rate_limit_sleep:
            msg = f"请求过于频繁，已被DueDEX限制，请等待{self.rate_limit_sleep}秒后再试"
            self.gateway.write_log(msg)
            return False
        # Just local request limit is reached
        elif not self.rate_limit_remaining:
            msg = "请求频率太高，有触发DueDEX流控的风险，请稍候再试"
            self.gateway.write_log(msg)
            return False
        else:
            self.rate_limit_remaining -= 1
            return True


class DuedexWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(DuedexWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.callbacks: Dict[str, Callable] = {}
        self.subscribed: Dict[str, SubscribeRequest] = {}
        self.sequences: Dict[str, int] = {}
        self.cached_update_packets: Dict[str, List] = {}

        self.ticks: Dict[str, TickData] = {}
        self.symbol_bids: Dict[str, dict] = {}
        self.symbol_asks: Dict[str, dict] = {}

        self.accounts = {}
        self.orders = {}
        self.positions = {}

    def connect(
        self, key: str, secret: str, server: str, proxy_host: str, proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret.encode()

        if server == "REAL":
            self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        else:
            self.init(TESTNET_WEBSOCKET_HOST, proxy_host, proxy_port)

        self.start()

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to ticker and level data upate.
        """
        self.subscribed[req.symbol] = req

        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            name=req.symbol,
            datetime=datetime.now(UTC_TZ),
            gateway_name=self.gateway_name,
        )
        self.ticks[req.symbol] = tick

        self.subscribe_topic("ticker", self.on_tick, req.symbol)
        self.subscribe_topic("level2", self.on_depth, req.symbol)

    def subscribe_topic(
        self,
        topic: str,
        callback: Callable[[str, dict], Any],
        symbol: str = None,
    ) -> None:
        """"""
        self.callbacks[topic] = callback

        req = {
            "type": "subscribe",
            "channels": [
                {
                    "name": topic,
                }
            ]
        }
        if symbol:
            req["channels"][0]["instruments"] = [symbol]
        self.send_packet(req)

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")
        self.authenticate()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        if "type" in packet:
            if packet["type"] == "challenge":
                self.on_authenticate(packet)
            elif packet["type"] == "auth":
                self.gateway.write_log("Websocket API验证授权成功")
                # Subscribe to all private topics.
                self.subscribe_topic("orders", self.on_order)
                self.subscribe_topic("executions", self.on_trade)
                self.subscribe_topic("positions", self.on_position)
                self.subscribe_topic("margins", self.on_account)

                # Auto re-subscribe market data after reconnected
                for req in self.subscribed.values():
                    self.subscribe(req)
            elif packet["type"] == "subscriptions":
                for channel in packet["channels"]:
                    self.gateway.write_log(
                        "Websocket API成功订阅：%s" % channel["name"])
            elif packet["type"] in ["snapshot", "update"]:
                # Check sequence whether equal the last sequence plus one,
                # if not, disconnect and reconnect.
                sequence = packet["sequence"]
                channel = packet["channel"]
                if packet["type"] == "snapshot":
                    self.sequences[channel] = sequence
                else:
                    if channel in self.sequences:
                        prev_sequence = self.sequences[channel]
                        if prev_sequence + 1 != sequence:
                            raise Exception(
                                f"The sequence of Channel {channel} is error.")
                        else:
                            self.sequences[channel] = sequence
                    else:
                        if channel not in self.cached_update_packets:
                            self.cached_update_packets[channel] = [packet]
                        else:
                            self.cached_update_packets[channel].append(packet)

                callback = self.callbacks[channel]
                callback(packet)

                # Handle update messages received before the snapshot message
                if packet["type"] == "snapshot":
                    if channel in self.cached_update_packets:
                        for cached_packet in self.cached_update_packets[channel]:
                            if cached_packet["sequence"] > self.sequences[channel]:
                                callback(cached_packet)
                        self.cached_update_packets.pop(channel)

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(
            exception_type, exception_value, tb))

    def authenticate(self):
        """
        To authenticate, the client first sends a challenge message.
        """
        req = {"type": "challenge"}
        self.send_packet(req)

    def on_authenticate(self, packet: dict):
        """"""
        signature = hmac.new(
            base64.b64decode(self.secret), packet['challenge'].encode(), digestmod=hashlib.sha256
        ).hexdigest()

        req = {
            "type": "auth",
            "key": self.key,
            "answer": signature,
        }
        self.send_packet(req)

    def on_tick(self, packet: dict):
        """"""
        type_ = packet["type"]
        data = packet["data"]
        timestamp = generate_datetime(packet["timestamp"])

        symbol = data["instrument"]
        tick = self.ticks[symbol]

        if type_ == "snapshot":
            if not data["lastPrice"]:           # Filter last price with 0 value
                return

            tick.last_price = float(data["lastPrice"])
            tick.index_price = float(data["indexPrice"])
            tick.mark_price = float(data["markPrice"])
            tick.open_price = float(data["open"])
            tick.high_price = float(data["high"])
            tick.low_price = float(data["low"])
            tick.volume = float(data["volume"])
            tick.open_interest = float(data["openInterest"])
        else:
            if "lastPrice" in data:
                if not data["lastPrice"]:           # Filter last price with 0 value
                    return
                tick.last_price = float(data["lastPrice"])

            if "indexPrice" in data:
                tick.index_price = float(data["indexPrice"])

            if "markPrice" in data:
                tick.mark_price = float(data["markPrice"])

            if "open" in data:
                tick.open_price = float(data["open"])

            if "high" in data:
                tick.high_price = float(data["high"])

            if "low" in data:
                tick.low_price = float(data["low"])

            if "volume" in data:
                tick.volume = float(data["volume"])

            if "openInterest" in data:
                tick.open_interest = float(data["openInterest"])

        tick.datetime = timestamp
        self.gateway.on_tick(copy(tick))

    def on_depth(self, packet: dict):
        """"""
        type_ = packet["type"]
        data = packet["data"]
        timestamp = generate_datetime(packet["timestamp"])

        # Update depth data into dict buf
        symbol = packet["instrument"]
        tick = self.ticks[symbol]
        bids = self.symbol_bids.setdefault(symbol, {})
        asks = self.symbol_asks.setdefault(symbol, {})

        if type_ == "snapshot":
            bids = {}
            for d in data["bids"]:
                bids[float(d[0])] = int(d[1])

            asks = {}
            for d in data["asks"]:
                asks[float(d[0])] = int(d[1])
        else:
            for d in data["bids"]:
                if 0 == int(d[1]):
                    bids.pop(float(d[0]))
                else:
                    bids[float(d[0])] = int(d[1])

            for d in data["asks"]:
                if 0 == int(d[1]):
                    asks.pop(float(d[0]))
                else:
                    asks[float(d[0])] = int(d[1])

        # Calculate 1-5 bid/ask depth
        bid_keys = list(bids.keys())
        bid_keys.sort(reverse=True)

        ask_keys = list(asks.keys())
        ask_keys.sort()

        for i in range(5):
            n = i + 1

            bid_price = bid_keys[i]
            bid_data = bids[bid_price]
            ask_price = ask_keys[i]
            ask_data = asks[ask_price]

            setattr(tick, f"bid_price_{n}", bid_price)
            setattr(tick, f"bid_volume_{n}", bid_data)
            setattr(tick, f"ask_price_{n}", ask_price)
            setattr(tick, f"ask_volume_{n}", ask_data)

        tick.datetime = timestamp
        self.gateway.on_tick(copy(tick))

    def on_order(self, packet: dict):
        """"""
        for d in packet["data"]:
            symbol = d["instrument"]
            orderid = d["clientOrderId"]
            if not orderid:
                orderid = d["orderId"]
            orderkey = symbol + str(orderid)
            order = self.orders.get(orderkey, None)
            if not order:
                order = OrderData(symbol=symbol, exchange=Exchange.DUEDEX,
                                  orderid=orderid, gateway_name=self.gateway_name
                                  )
                self.orders[orderkey] = order

            if "type" in d:
                order.type = ORDERTYPE_DUEDEX2VT[d["type"]]

            if "side" in d:
                order.direction = DIRECTION_DUEDEX2VT[d["side"]]

            if "price" in d:
                order.price = float(d["price"])

            if "size" in d:
                order.volume = d["size"]

            if "filledSize" in d:
                order.traded = d["filledSize"]

            if "status" in d:
                order.status = STATUS_DUEDEX2VT[d["status"]]

            if "updateTime" in d:
                order.datetime = generate_datetime(d["updateTime"])

            self.gateway.on_order(copy(order))

            if order.status in [Status.ALLTRADED, Status.CANCELLED, Status.REJECTED]:
                self.orders.pop(orderkey)

    def on_trade(self, packet: dict):
        """"""
        for d in packet["data"]:
            orderid = d["clientOrderId"]
            if not orderid:
                orderid = d["orderId"]

            trade = TradeData(
                symbol=d["instrument"],
                exchange=Exchange.DUEDEX,
                orderid=orderid,
                tradeid=d["executionId"],
                direction=DIRECTION_DUEDEX2VT[d["orderSide"]],
                price=float(d["executionPrice"]),
                volume=d["executionSize"],
                datetime=generate_datetime(d["timestamp"]),
                gateway_name=self.gateway_name,
            )

            self.gateway.on_trade(trade)

    def on_position(self, packet: dict):
        """"""
        for d in packet["data"]:
            symbol = d["instrument"]
            position = self.positions.get(symbol, None)
            if not position:
                position = PositionData(symbol=symbol, exchange=Exchange.DUEDEX,
                                        direction=Direction.NET, gateway_name=self.gateway_name)
                self.positions[symbol] = position

            position.volume = d.get("quantity", position.volume)
            position.price = d.get("entryPrice", position.price)
            position.pnl = d.get("unrealisedPnl", position.pnl)

            self.gateway.on_position(copy(position))

    def on_account(self, packet: dict):
        """"""
        for d in packet["data"]:
            accountid = str(d["currency"])
            account = self.accounts.get(accountid, None)
            if not account:
                account = {
                    "available": 0,
                    "orderMargin": 0,
                    "positionMargin": 0,
                }
                self.accounts[accountid] = account

            if "available" in d:
                account["available"] = float(d["available"])

            if "orderMargin" in d:
                account["orderMargin"] = float(d["orderMargin"])

            if "positionMargin" in d:
                account["positionMargin"] = float(d["positionMargin"])

            account = AccountData(
                accountid=accountid,
                balance=account["available"] + account["orderMargin"]
                + account["positionMargin"],
                frozen=account["orderMargin"] + account["positionMargin"],
                gateway_name=self.gateway_name,
            )
            self.gateway.on_account(account)


def generate_datetime(timestamp: str) -> datetime:
    """"""
    dt = datetime.strptime(timestamp, "%Y-%m-%dT%H:%M:%S.%fZ")
    dt = UTC_TZ.localize(dt)
    return dt
