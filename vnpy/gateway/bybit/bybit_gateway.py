""""""
import hashlib
import hmac
import time
import sys
from datetime import datetime, timedelta, timezone
from typing import Any, Dict, List, Callable
from threading import Lock
from copy import copy

from requests import ConnectionError
# from sortedcontainers import SortedSet

from vnpy.api.websocket import WebsocketClient
from vnpy.api.rest import Request, RestClient
from vnpy.trader.constant import (
    Exchange,
    Interval,
    OrderType,
    Product,
    Status,
    Direction
)
from vnpy.trader.object import (
    AccountData,
    BarData,
    TickData,
    OrderData,
    TradeData,
    ContractData,
    PositionData,
    HistoryRequest,
    SubscribeRequest,
    CancelRequest,
    OrderRequest
)
# from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway, LocalOrderManager


STATUS_BYBIT2VT = {
    "Created": Status.NOTTRADED,
    "New": Status.NOTTRADED,
    "PartiallyFilled": Status.PARTTRADED,
    "Filled": Status.ALLTRADED,
    "Cancelled": Status.CANCELLED,
    "Rejected": Status.REJECTED,
}
STOP_ORDER_STATUS_BYBIT2VT = {
    "Untriggered": Status.NOTTRADED,
    "Triggered": Status.NOTTRADED,
    # Active: triggered and placed.
    # since price is market price, placed == AllTraded?
    "Active": Status.ALLTRADED,
    "Cancelled": Status.CANCELLED,
    "Rejected": Status.REJECTED,
}
DIRECTION_VT2BYBIT = {Direction.LONG: "Buy", Direction.SHORT: "Sell"}
DIRECTION_BYBIT2VT = {v: k for k, v in DIRECTION_VT2BYBIT.items()}
DIRECTION_BYBIT2VT.update({
    "None": Direction.LONG
})

OPPOSITE_DIRECTION = {
    Direction.LONG: Direction.SHORT,
    Direction.SHORT: Direction.LONG,
}

ORDER_TYPE_VT2BYBIT = {
    OrderType.LIMIT: "Limit",
    OrderType.MARKET: "Market",
}
ORDER_TYPE_BYBIT2VT = {v: k for k, v in ORDER_TYPE_VT2BYBIT.items()}

INTERVAL_VT2BYBIT = {
    Interval.MINUTE: "1",
    Interval.HOUR: "60",
    Interval.DAILY: "D",
    Interval.WEEKLY: "W",
}
INTERVAL_VT2BYBIT_INT = {
    Interval.MINUTE: 1,
    Interval.HOUR: 60,
    Interval.DAILY: 60 * 24,
    Interval.WEEKLY: 60 * 24 * 7,
}

TIMEDELTA_MAP = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
    Interval.WEEKLY: timedelta(days=7),
}


REST_HOST = "https://api.bybit.com"
WEBSOCKET_HOST = "wss://stream.bybit.com/realtime"

TESTNET_REST_HOST = "https://api-testnet.bybit.com"
TESTNET_WEBSOCKET_HOST = "wss://stream-testnet.bybit.com/realtime"

# asked from official developer
PRICE_TICKS = {
    "BTCUSD": 0.5,
    "ETHUSD": 0.05,
    "EOSUSD": 0.001,
    "XRPUSD": 0.0001,
}

utc_tz = timezone.utc
local_tz = datetime.now(timezone.utc).astimezone().tzinfo


class BybitGateway(BaseGateway):
    """
    VN Trader Gateway for ByBit connection.
    """

    default_setting = {
        "ID": "",
        "Secret": "",
        "服务器": ["REAL", "TESTNET"],
        "代理地址": "",
        "代理端口": "",
    }

    exchanges = [Exchange.BYBIT]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "BYBIT")

        self.order_manager = LocalOrderManager(self)
        self.rest_api = BybitRestApi(self)
        self.ws_api = BybitWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["ID"]
        secret = setting["Secret"]
        server = setting["服务器"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.rest_api.connect(key, secret, server, proxy_host, proxy_port)
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
        return self.rest_api.query_history()

    def close(self):
        """"""
        self.rest_api.stop()
        self.ws_api.stop()


class BybitRestApi(RestClient):
    """
    ByBit REST API
    """

    def __init__(self, gateway: BybitGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.key = ""
        self.secret = b""

        self.order_count = 1_000_000
        self.order_count_lock = Lock()
        self.connect_time = 0

    def sign(self, request: Request):
        """
        Generate ByBit signature.
        """
        if request.method == "GET":
            api_params = request.params
            if api_params is None:
                api_params = request.params = {}
        else:
            api_params = request.data
            if api_params is None:
                api_params = request.data = {}

        api_params["api_key"] = self.key
        api_params["recv_window"] = 30 * 1000
        api_params["timestamp"] = generate_timestamp(-1)

        data2sign = "&".join([f"{k}={v}" for k, v in sorted(api_params.items())])
        signature = sign(self.secret, data2sign.encode())
        api_params["sign"] = signature

        return request

    def connect(
        self,
        key: str,
        secret: str,
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
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        if server == "REAL":
            self.init(REST_HOST, proxy_host, proxy_port)
        else:
            self.init(TESTNET_REST_HOST, proxy_host, proxy_port)

        self.start(3)
        self.gateway.write_log("REST API启动成功")

        self.query_contract()
        self.query_order()
        self.query_position()

    def send_order(self, req: OrderRequest):
        """"""
        order_id = self.order_manager.new_local_orderid()

        symbol = req.symbol
        data = {
            "symbol": symbol,
            "side": DIRECTION_VT2BYBIT[req.direction],
            "qty": int(req.volume),
            "order_link_id": order_id,
            "time_in_force": "GoodTillCancel"
        }

        order = req.create_order_data(order_id, self.gateway_name)
        order.time = datetime.now().isoformat()[11:19]

        # Only add price for limit order.
        data["order_type"] = ORDER_TYPE_VT2BYBIT[req.type]
        data["price"] = req.price
        self.add_request(
            "POST",
            "/open-api/order/create",
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
        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)
        data = {
            "order_id": sys_orderid,
            "symbol": req.symbol,
        }

        self.add_request(
            "POST",
            path="/open-api/order/cancel",
            data=data,
            callback=self.on_cancel_order
        )

    def query_history(
        self,
        symbol: str,
        interval: Interval,
        start: int,  # unix timestamp
        limit: int = None,
    ) -> List[BarData]:
        """"""
        pass

    def on_send_order_failed(self, status_code: int, request: Request):
        """
        Callback when sending order failed on server.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        data = request.response.json()
        error_msg = data["ret_msg"]
        error_code = data["ret_code"]
        msg = f"委托失败，错误代码:{error_code},  错误信息：{error_msg}"
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
        """"""
        result = data["result"]
        self.order_manager.update_orderid_map(
            result["order_link_id"],
            result["order_id"]
        )

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
        """"""
        pass

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        data = request.response.json()

        error_msg = data["ret_msg"]
        error_code = data["ret_code"]

        msg = f"请求失败，状态码：{request.status}，错误代码：{error_code}, 信息：{error_msg}"

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

    def query_contract(self):
        """"""
        self.add_request(
            "GET",
            "/v2/public/symbols",
            self.on_query_contract
        )

    def check_error(self, name: str, data: dict):
        """"""
        if data["ret_code"]:
            error_code = data["ret_code"]
            error_msg = data["ret_msg"]
            msg = f"{name}失败，错误代码：{error_code}，信息：{error_msg}"
            self.gateway.write_log(msg)
            return True

        return False

    def on_query_contract(self, data: dict, request: Request):
        """"""
        if self.check_error("查询合约", data):
            return

        for d in data["result"]:
            contract = ContractData(
                gateway_name=self.gateway_name,
                symbol=d["name"],
                exchange=Exchange.BYBIT,
                name=d["name"],
                product=Product.FUTURES,
                size=1,
                pricetick=d["price_filter"]["tick_size"],
                min_volume=d["lot_size_filter"]["qty_step"]
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

    def query_position(self):
        """"""
        self.add_request(
            "GET",
            "/position/list",
            self.on_query_position
        )

    def on_query_position(self, data: dict, request: Request):
        """"""
        if self.check_error("查询持仓", data):
            return

        for d in data["result"]:
            if d["side"] == "Buy":
                volume = d["size"]
            else:
                volume = -d["size"]

            position = PositionData(
                symbol=d["symbol"],
                exchange=Exchange.BYBIT,
                direction=Direction.NET,
                volume=volume,
                price=d["entry_price"],
                pnl=d["unrealised_pnl"],
                gateway_name=self.gateway_name
            )
            self.gateway.on_position(position)

            account = AccountData(
                accountid=d["symbol"].replace("USD", ""),
                balance=d["wallet_balance"],
                frozen=d["order_margin"],
                gateway_name=self.gateway_name,
            )
            self.gateway.on_account(account)

    def query_order(self, page: int = 1):
        """"""
        params = {
            "limit": 50,
            "page": page,
            "order_status": "Created,New,PartiallyFilled"
        }

        self.add_request(
            "GET",
            "/open-api/order/list",
            callback=self.on_query_order,
            params=params
        )

    def on_query_order(self, data: dict, request: Request):
        """"""
        if self.check_error("查询委托", data):
            return

        result = data["result"]
        if not result:
            self.gateway.write_log("委托信息查询成功")
            return

        for d in result["data"]:
            sys_orderid = d["order_id"]

            # Use sys_orderid as local_orderid when
            # order placed from other source
            local_orderid = d["order_link_id"]
            if not local_orderid:
                local_orderid = sys_orderid

            self.order_manager.update_orderid_map(
                local_orderid,
                sys_orderid
            )

            order = OrderData(
                symbol=d["symbol"],
                exchange=Exchange.BYBIT,
                orderid=local_orderid,
                type=ORDER_TYPE_BYBIT2VT[d["order_type"]],
                direction=DIRECTION_BYBIT2VT[d["side"]],
                price=d["price"],
                volume=d["qty"],
                traded=d["cum_exec_qty"],
                status=STATUS_BYBIT2VT[d["order_status"]],
                time=d["created_at"],
                gateway_name=self.gateway_name
            )
            self.gateway.on_order(order)

        if result["current_page"] != result["last_page"]:
            self.query_order(result["current_page"] + 1)
        else:
            self.gateway.write_log("委托信息查询成功")


class RawOrderInfo:

    def __init__(self, data: dict):
        self.id = data["id"]
        self.price = data["price"]
        self.side = data["side"]  # "Buy", "Sell"
        self.size = data.get("size", 0)

    def __lt__(self, rhs: "RawOrderInfo"):
        return self.price < rhs.price

    def __eq__(self, rhs: "RawOrderInfo"):
        return self.price == rhs.price

    def __hash__(self):
        return self.id  # price is a string and we don"t known its precision


class BybitWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway: BybitGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.key = ""
        self.secret = b""
        self.server: str = ""  # REAL or TESTNET

        self.callbacks: Dict[str, Callable] = {}
        self.ticks: Dict[str, TickData] = {}

        self.symbol_bids: Dict[str, dict] = {}
        self.symbol_asks: Dict[str, dict] = {}

    def connect(
        self, key: str, secret: str, server: str, proxy_host: str, proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret.encode()
        self.proxy_host = proxy_host
        self.proxy_port = proxy_port
        self.server = server

        if self.server == "REAL":
            url = WEBSOCKET_HOST
        else:
            url = TESTNET_WEBSOCKET_HOST

        self.init(url, self.proxy_host, self.proxy_port)
        self.start()

    def login(self):
        """"""
        expires = generate_timestamp(30)
        msg = f"GET/realtime{int(expires)}"
        signature = sign(self.secret, msg.encode())

        req = {
            "op": "auth",
            "args": [self.key, expires, signature]
        }
        self.send_packet(req)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data upate.
        """
        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            datetime=datetime.now(),
            name=req.symbol,
            gateway_name=self.gateway_name
        )
        self.ticks[req.symbol] = tick

        self.subscribe_topic(f"instrument_info.100ms.{req.symbol}", self.on_tick)
        self.subscribe_topic(f"orderBookL2_25.{req.symbol}", self.on_depth)

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")
        self.login()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        print(packet)
        if "topic" not in packet:
            op = packet["request"]["op"]
            if op == "auth":
                self.on_login(packet)
        else:
            channel = packet["topic"]
            callback = self.callbacks[channel]
            callback(packet)

        # success = packet.get("success", None)
        # topic = packet.get("topic", None)
        # if success is not None:
        #     if success is False:
        #         self.gateway.write_log("Websocket API报错：%s" % packet["ret_msg"])
        # elif topic is not None:
        #     self.callbacks[topic](topic, packet)
        # else:
        #     self.gateway.write_log(f"unkonwn packet: {packet}")

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(
            exception_type, exception_value, tb))

    def on_login(self, packet: dict):
        """"""
        success = packet.get("success", False)
        if success:
            self.gateway.write_log("Websocket API登录成功")

            self.subscribe_topic("order", self.on_order)
            self.subscribe_topic("execution", self.on_trade)
            self.subscribe_topic("position", self.on_position)
        else:
            self.gateway.write_log("Websocket API登录失败")

    def subscribe_topic(self, topic: str, callback: Callable[[str, dict], Any]):
        """
        Subscribe to all private topics.
        """
        self.callbacks[topic] = callback

        req = {
            "op": "subscribe",
            "args": [topic],
        }
        self.send_packet(req)

    def on_tick(self, packet: dict):
        """"""
        topic = packet["topic"]
        type_ = packet["type"]
        data = packet["data"]
        timestamp = packet["timestamp_e6"]

        symbol = topic.replace("instrument_info.100ms.", "")
        tick = self.ticks[symbol]

        if type_ == "snapshot":
            tick.last_price = data["last_price_e4"] / 10000
            tick.volume = data["volume_24h"]
        else:
            update = data["update"][0]

            if "last_price_e4" in update:
                tick.last_price = update["last_price_e4"] / 10000

            if "volume_24h" in update:
                tick.volume = update["volume_24h"]

        tick.datetime = datetime.fromtimestamp(timestamp / 1_000_000)
        self.gateway.on_tick(copy(tick))

    def on_depth(self, packet: dict):
        """"""
        topic = packet["topic"]
        type_ = packet["type"]
        data = packet["data"]
        timestamp = packet["timestamp_e6"]

        # Update depth data into dict buf
        symbol = topic.replace("orderBookL2_25.", "")
        tick = self.ticks[symbol]
        bids = self.symbol_bids.setdefault(symbol, {})
        asks = self.symbol_asks.setdefault(symbol, {})

        if type_ == "snapshot":
            for d in data:
                price = float(d["price"])

                if d["side"] == "Buy":
                    bids[price] = d
                else:
                    asks[price] = d
        else:
            for d in data["delete"]:
                price = float(d["price"])
                if d["side"] == "Buy":
                    bids.pop(price)
                else:
                    asks.pop(price)

            for d in (data["update"] + data["insert"]):
                price = float(d["price"])
                if d["side"] == "Buy":
                    bids[price] = d
                else:
                    asks[price] = d

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
            setattr(tick, f"bid_volume_{n}", bid_data["size"])
            setattr(tick, f"ask_price_{n}", ask_price)
            setattr(tick, f"ask_volume_{n}", ask_data["size"])

        tick.datetime = datetime.fromtimestamp(timestamp / 1_000_000)
        self.gateway.on_tick(copy(tick))

    def on_trade(self, topic: str, data: dict):
        """"""
        for data in data["data"]:
            order_id = data["order_link_id"]
            if not order_id:
                order_id = data["order_id"]
            trade = TradeData(
                symbol=data["symbol"],
                exchange=Exchange.BYBIT,
                orderid=order_id,
                tradeid=data["exec_id"],
                direction=DIRECTION_BYBIT2VT[data["side"]],
                price=data["price"],
                volume=data["exec_qty"],
                time=parse_datetime(data["trade_time"]),
                gateway_name=self.gateway_name,
            )

            self.gateway.on_trade(trade)

    def on_order(self, topic: str, data: dict):
        """"""
        for data in data["data"]:
            print(data)
            order = self.gateway.parse_order_data(data, "timestamp")

            self.gateway.on_order(copy(order))

    def on_position(self, topic: str, data: dict):
        """"""
        for data in data["data"]:
            p1, p2 = self.gateway.parse_position_data(data)
            self.gateway.on_position(p1)
            if p2:
                self.gateway.on_position(p2)


def _parse_timestamp_e6(timestamp: int):
    return datetime.fromtimestamp(timestamp / 1_000_000, utc_tz).astimezone(tz=local_tz)


def generate_timestamp(expire_after: float = 30) -> int:
    """
    :param expire_after: expires in seconds.
    :return: timestamp in milliseconds
    """
    return int(time.time() * 1000 + expire_after * 1000)


def sign(secret: bytes, data: bytes) -> str:
    """"""
    return hmac.new(
        secret, data, digestmod=hashlib.sha256
    ).hexdigest()


def parse_datetime(dt: str) -> str:
    return dt[11:19]
