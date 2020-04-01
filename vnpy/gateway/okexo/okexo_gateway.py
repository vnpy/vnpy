"""
Author: KeKe
"""

import hashlib
import hmac
import sys
import time
import json
import base64
import zlib
from copy import copy
from datetime import datetime, timedelta
from threading import Lock
from urllib.parse import urlencode
from typing import Dict, List

from requests import ConnectionError

from vnpy.event.engine import EventEngine
from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Interval
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    PositionData,
    BarData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)
REST_HOST: str = "https://www.okex.com"
WEBSOCKET_HOST: str = "wss://real.okex.com:8443/ws/v3"

STATE_OKEXO2VT: Dict[str, Status] = {
    "0": Status.NOTTRADED,
    "-2": Status.NOTTRADED,
    "1": Status.PARTTRADED,
    "2": Status.ALLTRADED,
    "-1": Status.CANCELLED,
}

ORDERTYPE_OKEXO2VT: Dict[str, OrderType] = {
    "0": OrderType.LIMIT,
    "1": OrderType.MARKET,
}

SIDE_OKEXO2VT: Dict[str, Direction] = {
    "buy": Direction.LONG,
    "sell": Direction.SHORT,
}
SIDE_VT2OKEXO: Dict[Direction, str] = {
    Direction.LONG: "buy",
    Direction.SHORT: "sell",
}
INTERVAL_VT2OKEXO: Dict[Interval, str] = {
    Interval.MINUTE: "60",
    Interval.HOUR: "3600",
    Interval.DAILY: "86400",
}

underlyings: set = set()


class OkexoGateway(BaseGateway):
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

    exchanges: List[Exchange] = [Exchange.OKEX]

    def __init__(self, event_engine: EventEngine):
        """Constructor"""
        super().__init__(event_engine, "OKEXO")

        self.rest_api = OkexoRestApi(self)
        self.ws_api = OkexoWebsocketApi(self)

        self.orders: Dict[str, OrderData] = {}

    def connect(self, setting: dict) -> None:
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

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> Request:
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        pass

    def query_position(self) -> None:
        """"""
        pass

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """"""
        return self.rest_api.query_history(req)

    def close(self) -> None:
        """"""
        self.rest_api.stop()
        self.ws_api.stop()

    def on_order(self, order: OrderData) -> None:
        """"""
        self.orders[order.orderid] = order
        super().on_order(order)

    def get_order(self, orderid: str):
        """"""
        return self.orders.get(orderid, None)


class OkexoRestApi(RestClient):
    """
    OKEXO REST API
    """

    def __init__(self, gateway: "OkexoGateway"):
        """"""
        super().__init__()

        self.gateway: OkexoGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.key: str = ""
        self.secret: str = ""
        self.passphrase: str = ""

        self.order_count: int = 10000
        self.order_count_lock: Lock = Lock()

        self.connect_time: int = 0

    def sign(self, request: Request) -> Request:
        """
        Generate OKEXo signature.
        """
        # Sign
        timestamp = get_timestamp()
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
    ) -> None:
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
        self.query_underlying()

    def _new_order_id(self) -> int:
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest) -> str:
        """"""
        # Need both offset and direction for sending order.

        orderid = f"a{self.connect_time}{self._new_order_id()}"

        if req.direction == Direction.LONG:
            side = "buy"
        else:
            side = "sell"

        data = {
            "client_oid": orderid,
            "instrument_id": req.symbol,
            "price": str(req.price),
            "size": str(int(req.volume)),
            "side": side,
        }

        if req.type == OrderType.MARKET:
            data["match_price"] = "1"
        else:
            data["match_price"] = "0"

        order = req.create_order_data(orderid, self.gateway_name)

        self.add_request(
            "POST",
            "/api/option/v3/order",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error,
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> Request:
        """"""
        item = req.symbol.split("-")
        underlying = f"{item[0]}-{item[1]}"

        path = f"/api/option/v3/cancel_order/{underlying}/{req.orderid}"
        self.add_request(
            "POST",
            path,
            callback=self.on_cancel_order,
            on_error=self.on_cancel_order_error,
            on_failed=self.on_cancel_order_failed,
            extra=req
        )

    def query_underlying(self) -> Request:
        """"""
        self.add_request(
            "GET",
            "/api/option/v3/underlying",
            callback=self.on_query_underlying
        )

    def query_contract(self) -> Request:
        """"""
        for underlying in underlyings:
            self.add_request(
                "GET",
                f"/api/option/v3/instruments/{underlying}",
                callback=self.on_query_contract
            )

    def query_account(self) -> Request:
        """"""
        for underlying in underlyings:
            self.add_request(
                "GET",
                f"/api/option/v3/accounts/{underlying}",
                callback=self.on_query_account
            )

    def query_order(self) -> Request:
        """"""
        for underlying in underlyings:

            # get waiting orders
            self.add_request(
                "GET",
                f"/api/option/v3/orders/{underlying}?state=0",
                callback=self.on_query_order
            )

            # get part traded orders
            self.add_request(
                "GET",
                f"/api/option/v3/orders/{underlying}?state=1",
                callback=self.on_query_order
            )

    def query_position(self) -> Request:
        """"""
        for underlying in underlyings:
            self.add_request(
                "GET",
                f"/api/option/v3/{underlying}/position",
                callback=self.on_query_position
            )

    def query_time(self) -> Request:
        """"""
        self.add_request(
            "GET",
            "/api/general/v3/time",
            callback=self.on_query_time
        )

    def on_query_underlying(self, data: List[str], request: Request) -> None:
        """"""
        for underlying in data:
            underlyings.add(underlying)

        self.gateway.write_log("期权标的信息查询成功")
        self.query_contract()

    def on_query_contract(self, data: List, request: Request) -> None:
        """"""
        if not data:
            return

        for instrument_data in data:
            symbol = instrument_data["instrument_id"]
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.OKEX,
                name=symbol,
                product=Product.OPTION,
                size=float(instrument_data["contract_val"]),
                pricetick=float(instrument_data["tick_size"]),
                option_strike=int(instrument_data["strike"]),
                option_underlying=instrument_data["underlying"],
                option_type=instrument_data["option_type"],
                option_expiry=datetime.strptime(instrument_data["delivery"], "%Y-%m-%dT%H:%M:%S.%fZ"),
                option_portfolio=instrument_data["underlying"] + "_O",
                option_index=instrument_data["strike"],
                history_data=True,
                net_position=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("期权合约信息查询成功")
        # Start websocket api after instruments data collected
        self.gateway.ws_api.start()

        # and query pending orders
        self.query_account()
        self.query_position()
        self.query_order()

    def on_query_account(self, data: dict, request: Request) -> None:
        """"""
        equity = float(data["equity"])
        if equity:
            account = AccountData(
                accountid=data["underlying"],
                balance=float(data["equity"]),
                frozen=float(data.get("margin_for_unfilled", 0)),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_account(account)

            self.gateway.write_log(f"{account.accountid}账户资金查询成功")

    def on_query_position(self, data: dict, request: Request) -> None:
        """"""
        if not data["holding"]:
            return

        for pos_data in data["holding"]:
            pos = PositionData(
                symbol=pos_data["instrument_id"],
                exchange=Exchange.OKEX,
                direction=Direction.NET,
                volume=int(pos_data["position"]),
                frozen=float(pos_data["avail_position"]) - float(pos_data["avail_position"]),
                price=float(pos_data["avg_cost"]),
                pnl=float(pos_data["realized_pnl"]),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_position(pos)

    def on_query_order(self, data: dict, request: Request) -> None:
        """"""
        for order_data in data["order_info"]:
            direction = SIDE_OKEXO2VT[order_data["side"]]
            order = OrderData(
                symbol=order_data["instrument_id"],
                exchange=Exchange.OKEX,
                type=ORDERTYPE_OKEXO2VT[order_data["order_type"]],
                orderid=order_data["client_oid"],
                direction=direction,
                traded=int(order_data["filled_qty"]),
                price=float(order_data["price"]),
                volume=float(order_data["size"]),
                time=utc_to_local(order_data["timestamp"]).strftime("%H:%M:%S"),
                status=STATE_OKEXO2VT[order_data["state"]],
                gateway_name=self.gateway_name,
            )
            self.gateway.on_order(order)

    def on_query_time(self, data: dict, request: Request) -> None:
        """"""
        server_time = data["iso"]
        local_time = datetime.utcnow().isoformat()
        msg = f"服务器时间：{server_time}，本机时间：{local_time}"
        self.gateway.write_log(msg)

    def on_send_order_failed(self, status_code: str, request: Request) -> None:
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
    ) -> None:
        """
        Callback when sending order caused exception.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_send_order(self, data: dict, request: Request) -> None:
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
    ) -> None:
        """
        Callback when cancelling order failed on server.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, data, request) -> None:
        """
        Websocket will push a new order status
        """
        pass

    def on_cancel_order_failed(self, status_code: int, request: Request) -> None:
        """
        If cancel failed, mark order status to be rejected.
        """
        req = request.extra
        order = self.gateway.get_order(req.orderid)
        if order:
            order.status = Status.REJECTED
            self.gateway.on_order(order)

    def on_failed(self, status_code: int, request: Request) -> None:
        """
        Callback to handle request failed.
        """
        msg = f"请求失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ) -> None:
        """
        Callback to handler request exception.
        """
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """"""
        buf = {}
        end_time = None

        for i in range(10):
            path = f"/api/option/v3/instruments/{req.symbol}/candles"

            # Create query params
            params = {
                "granularity": INTERVAL_VT2OKEXO[req.interval]
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
                    dt = utc_to_local(ts)
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


class OkexoWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__()

        self.ping_interval: int = 20     # OKEX use 30 seconds for ping

        self.gateway: OkexoGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.key: str = ""
        self.secret: str = ""
        self.passphrase: str = ""

        self.trade_count: int = 10000
        self.connect_time: int = 0

        self.callbacks: Dict[str, callable] = {}
        self.ticks: Dict[str, TickData] = {}

    def connect(
        self,
        key: str,
        secret: str,
        passphrase: str,
        proxy_host: str,
        proxy_port: int
    ) -> None:
        """"""
        self.key = key
        self.secret = secret.encode()
        self.passphrase = passphrase

        self.connect_time = int(datetime.now().strftime("%y%m%d%H%M%S"))

        self.init(WEBSOCKET_HOST, proxy_host, proxy_port)

    def unpack_data(self, data) -> json.JSONDecoder:
        """"""
        return json.loads(zlib.decompress(data, -zlib.MAX_WBITS))

    def subscribe(self, req: SubscribeRequest) -> None:
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

        channel_ticker = f"option/ticker:{req.symbol}"
        channel_depth = f"option/depth5:{req.symbol}"

        self.callbacks[channel_ticker] = self.on_ticker
        self.callbacks[channel_depth] = self.on_depth

        req = {
            "op": "subscribe",
            "args": [channel_ticker, channel_depth]
        }
        self.send_packet(req)

    def on_connected(self) -> None:
        """"""
        self.gateway.write_log("Websocket API连接成功")
        self.login()

    def on_disconnected(self) -> None:
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: dict) -> None:
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

    def on_error(self, exception_type: type, exception_value: Exception, tb) -> None:
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(exception_type, exception_value, tb))

    def login(self) -> None:
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

    def subscribe_topic(self) -> None:
        """
        Subscribe to all private topics.
        """
        self.callbacks["option/ticker"] = self.on_ticker
        self.callbacks["option/depth5"] = self.on_depth
        self.callbacks["option/account"] = self.on_account
        self.callbacks["option/order"] = self.on_order
        self.callbacks["option/position"] = self.on_position

        # Subscribe to order update
        channels = []
        for underlying in underlyings:
            channel = f"option/order:{underlying}"
            channels.append(channel)

        req = {
            "op": "subscribe",
            "args": channels
        }
        self.send_packet(req)

        # Subscribe to account update
        channels = []
        for underlying in underlyings:
            channel = f"option/account:{underlying}"
            channels.append(channel)

        req = {
            "op": "subscribe",
            "args": channels
        }
        self.send_packet(req)

        # Subscribe to position update
        channels = []
        for underlying in underlyings:
            channel = f"option/position:{underlying}"
            channels.append(channel)

        req = {
            "op": "subscribe",
            "args": channels
        }

        self.send_packet(req)

    def on_login(self, data: dict) -> None:
        """"""
        success = data.get("success", False)

        if success:
            self.gateway.write_log("Websocket API登录成功")
            self.subscribe_topic()
        else:
            self.gateway.write_log("Websocket API登录失败")

    def on_ticker(self, data: dict) -> None:
        """"""
        symbol = data["instrument_id"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        tick.last_price = float(data["last"])
        tick.high_price = float(data["high_24h"])
        tick.low_price = float(data["low_24h"])
        tick.volume = float(data["volume_24h"])
        tick.datetime = utc_to_local(data["timestamp"])

        self.gateway.on_tick(copy(tick))

    def on_depth(self, data: dict) -> None:
        """"""
        symbol = data["instrument_id"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        bids = data["bids"]
        asks = data["asks"]
        for n, buf in enumerate(bids):
            price, volume, _, __ = buf
            tick.__setattr__("bid_price_%s" % (n + 1), float(price))
            tick.__setattr__("bid_volume_%s" % (n + 1), int(volume))

        for n, buf in enumerate(asks):
            price, volume, _, __ = buf
            tick.__setattr__("ask_price_%s" % (n + 1), float(price))
            tick.__setattr__("ask_volume_%s" % (n + 1), int(volume))

        tick.datetime = utc_to_local(data["timestamp"])
        self.gateway.on_tick(copy(tick))

    def on_order(self, data: dict) -> None:
        """"""
        direction = SIDE_OKEXO2VT[data["side"]]
        order = OrderData(
            symbol=data["instrument_id"],
            exchange=Exchange.OKEX,
            type=ORDERTYPE_OKEXO2VT[data["order_type"]],
            orderid=data["client_oid"],
            direction=direction,
            price=float(data["price"]),
            volume=float(data["size"]),
            traded=float(data["filled_qty"]),
            time=utc_to_local(data["timestamp"]).strftime("%H:%M:%S"),
            status=STATE_OKEXO2VT[data["state"]],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_order(copy(order))

        trade_volume = data.get("last_fill_qty", 0)
        if not trade_volume or float(trade_volume) == 0:
            return

        self.trade_count += 1
        tradeid = f"{self.connect_time}{self.trade_count}"

        trade = TradeData(
            symbol=order.symbol,
            exchange=order.exchange,
            orderid=order.orderid,
            tradeid=tradeid,
            direction=order.direction,
            offset=order.offset,
            price=float(data["last_fill_px"]),
            volume=float(trade_volume),
            time=order.time,
            gateway_name=self.gateway_name,
        )
        self.gateway.on_trade(trade)

    def on_account(self, data: dict) -> None:
        """"""
        account = AccountData(
            accountid=data["underlying"],
            balance=float(data["equity"]),
            frozen=float(data.get("margin_for_unfilled", 0)),
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def on_position(self, data: dict) -> None:
        """"""
        pos = PositionData(
            symbol=data["instrument_id"],
            exchange=Exchange.OKEX,
            direction=Direction.NET,
            volume=int(data["position"]),
            frozen=float(data["avail_position"]) - float(data["avail_position"]),
            price=float(data["avg_cost"]),
            pnl=float(data["realized_pnl"]),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_position(pos)


def generate_signature(msg: str, secret_key: str) -> bytes:
    """OKEX V3 signature"""
    return base64.b64encode(hmac.new(secret_key, msg.encode(), hashlib.sha256).digest())


def get_timestamp() -> str:
    """"""
    now = datetime.utcnow()
    timestamp = now.isoformat("T", "milliseconds")
    return timestamp + "Z"


def utc_to_local(timestamp) -> datetime:
    time = datetime.strptime(timestamp, "%Y-%m-%dT%H:%M:%S.%fZ")
    utc_time = time + timedelta(hours=8)
    return utc_time
