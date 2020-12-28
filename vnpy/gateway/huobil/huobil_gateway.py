"""
火币正向永续合约接口
"""

import base64
import hashlib
import hmac
import json
import re
import sys
import urllib
import zlib
from copy import copy
from datetime import datetime, timedelta
from threading import Lock
from typing import Dict, List, Any
from typing import Sequence

import pytz

from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
from vnpy.event import Event
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    Product,
    Status,
    OrderType,
    Interval
)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    BarData,
    AccountData,
    PositionData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)

REST_HOST = "https://api.hbdm.com"
WEBSOCKET_DATA_HOST = "wss://api.hbdm.com/linear-swap-ws"  # Market Data
WEBSOCKET_TRADE_HOST = "wss://api.hbdm.com/linear-swap-notification"  # Account and Order

STATUS_HUOBIS2VT: Dict[int, Status] = {
    3: Status.NOTTRADED,
    4: Status.PARTTRADED,
    5: Status.CANCELLED,
    6: Status.ALLTRADED,
    7: Status.CANCELLED,
}

ORDERTYPE_VT2HUOBIS: Dict[OrderType, Any] = {
    OrderType.MARKET: "optimal_20",
    OrderType.LIMIT: "limit",
    OrderType.FOK: "fok",
    OrderType.FAK: "ioc"
}
ORDERTYPE_HUOBIS2VT: Dict[Any, OrderType] = {v: k for k, v in ORDERTYPE_VT2HUOBIS.items()}
ORDERTYPE_HUOBIS2VT[1] = OrderType.LIMIT
ORDERTYPE_HUOBIS2VT[3] = OrderType.MARKET
ORDERTYPE_HUOBIS2VT[4] = OrderType.MARKET
ORDERTYPE_HUOBIS2VT[5] = OrderType.STOP
ORDERTYPE_HUOBIS2VT[6] = OrderType.LIMIT
ORDERTYPE_HUOBIS2VT["lightning"] = OrderType.MARKET
ORDERTYPE_HUOBIS2VT["optimal_5"] = OrderType.MARKET
ORDERTYPE_HUOBIS2VT["optimal_10"] = OrderType.MARKET
ORDERTYPE_HUOBIS2VT["optimal_20"] = OrderType.MARKET

DIRECTION_VT2HUOBIS: Dict[Direction, str] = {
    Direction.LONG: "buy",
    Direction.SHORT: "sell",
}
DIRECTION_HUOBIS2VT: Dict[str, Direction] = {v: k for k, v in DIRECTION_VT2HUOBIS.items()}

OFFSET_VT2HUOBIS: Dict[Offset, str] = {
    Offset.OPEN: "open",
    Offset.CLOSE: "close",
}
OFFSET_HUOBIS2VT: Dict[str, Offset] = {v: k for k, v in OFFSET_VT2HUOBIS.items()}

INTERVAL_VT2HUOBIS: Dict[Interval, str] = {
    Interval.MINUTE: "1min",
    Interval.HOUR: "60min",
    Interval.DAILY: "1day"
}

TIMEDELTA_MAP: Dict[Interval, timedelta] = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}

CHINA_TZ = pytz.timezone("Asia/Shanghai")


class HuobilGateway(BaseGateway):
    """
    VN Trader Gateway for Huobis connection.
    """

    default_setting: Dict[str, Any] = {
        "API Key": "",
        "Secret Key": "",
        "会话数": 3,
        "代理地址": "",
        "代理端口": "",
        "保证金模式": "cross",
        "杠杆倍数": 20
    }

    exchanges = [Exchange.HUOBI]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "HUOBIL")

        self.rest_api = HuobilRestApi(self)
        self.trade_ws_api = HuobilTradeWebsocketApi(self)
        self.market_ws_api = HuobilDataWebsocketApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        key = setting["API Key"]
        secret = setting["Secret Key"]
        session_number = setting["会话数"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]
        margin_mode = setting["保证金模式"]
        leverage_ratio = setting["杠杆倍数"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.rest_api.connect(key, secret, session_number, proxy_host, proxy_port, margin_mode, leverage_ratio)
        self.trade_ws_api.connect(key, secret, proxy_host, proxy_port, margin_mode)
        self.market_ws_api.connect(key, secret, proxy_host, proxy_port)

        self.init_query()

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.market_ws_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> Request:
        """"""
        self.rest_api.cancel_order(req)

    def send_orders(self, reqs: Sequence[OrderRequest]) -> str:
        """"""
        return self.rest_api.send_orders(reqs)

    def query_account(self) -> Request:
        """"""
        self.rest_api.query_account()

    def query_position(self) -> Request:
        """"""
        self.rest_api.query_position()

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """"""
        return self.rest_api.query_history(req)

    def close(self) -> None:
        """"""
        self.rest_api.stop()
        self.trade_ws_api.stop()
        self.market_ws_api.stop()

    def process_timer_event(self, event: Event) -> None:
        """"""
        self.count += 1
        if self.count < 3:
            return

        self.query_account()
        self.query_position()

    def init_query(self) -> None:
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class HuobilRestApi(RestClient):
    """
    HUOBIS REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway: HuobilGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.host: str = ""
        self.key: str = ""
        self.secret: str = ""
        self.account_id: str = ""
        self.margin_mode = "cross"

        self.order_count: int = 10000
        self.order_count_lock: Lock = Lock()
        self.connect_time: int = 0

        self.positions: Dict[str, PositionData] = {}
        self.contract_codes: set = set()

    def sign(self, request) -> Request:
        """
        Generate HUOBIS signature.
        """
        request.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36"
        }
        params_with_signature = create_signature(
            self.key,
            request.method,
            self.host,
            request.path,
            self.secret,
            request.params
        )
        request.params = params_with_signature

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
            proxy_port: int,
            margin_mode: str,
            leverage_ratio: int
    ) -> None:
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret
        self.host, _ = _split_url(REST_HOST)
        self.connect_time = int(datetime.now(CHINA_TZ).strftime("%y%m%d%H%M%S"))
        self.margin_mode = margin_mode
        self.leverage_ratio = leverage_ratio

        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

        self.query_contract()

    def query_account(self) -> Request:
        """"""
        if self.margin_mode == "cross":
            self.add_request(
                method="POST",
                path="/linear-swap-api/v1/swap_cross_account_info",
                callback=self.on_query_account
            )
        else:
            self.add_request(
                method="POST",
                path="/linear-swap-api/v1/swap_account_info",
                callback=self.on_query_account
            )

    def query_position(self) -> Request:
        """"""
        if self.margin_mode == "cross":
            path = "/linear-swap-api/v1/swap_cross_position_info"
        else:
            path = "/linear-swap-api/v1/swap_position_info"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_query_position
        )

    def query_order(self) -> Request:
        """"""
        if self.margin_mode == "cross":
            path = "/linear-swap-api/v1/swap_cross_openorders"
        else:
            path = "/linear-swap-api/v1/swap_openorders"

        for contract_code in self.contract_codes:
            # Open Orders
            data = {"contract_code": contract_code}

            self.add_request(
                method="POST",
                path=path,
                callback=self.on_query_order,
                data=data,
                extra=contract_code
            )

    def query_contract(self) -> Request:
        """"""
        self.add_request(
            method="GET",
            path="/linear-swap-api/v1/swap_contract_info",
            callback=self.on_query_contract
        )

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """"""
        history = []
        count = 2000
        start = req.start
        time_delta = TIMEDELTA_MAP[req.interval]

        # Convert symbol
        buf = [i for i in req.symbol if not i.isdigit()]
        symbol = "".join(buf)

        ws_symbol = f"{symbol}"

        while True:
            # Calculate end time
            end = start + time_delta * count

            # Create query params
            params = {
                "contract_code": ws_symbol,
                "period": INTERVAL_VT2HUOBIS[req.interval],
                "from": int(start.timestamp()),
                "to": int(end.timestamp())
            }

            # Get response from server
            resp = self.request(
                "GET",
                "/linear-swap-ex/market/history/kline",
                params=params
            )

            print(params)

            # Break if request failed with other status code
            if resp.status_code // 100 != 2:
                msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
                self.gateway.write_log(msg)
                break
            else:
                data = resp.json()
                if data["status"] != "ok":
                    msg = f"获取历史数据失败，状态码：{data['err-code']}，信息：{data['err-msg']}"
                    self.gateway.write_log(msg)
                    break

                if not data:
                    msg = f"获取历史数据为空"
                    self.gateway.write_log(msg)
                    break

                if not data["data"]:
                    msg = f"获取历史数据为空"
                    self.gateway.write_log(msg)
                    break

                buf = []
                for d in data["data"]:
                    dt = generate_datetime(d["id"])

                    bar = BarData(
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=dt,
                        interval=req.interval,
                        volume=d["vol"],
                        open_price=d["open"],
                        high_price=d["high"],
                        low_price=d["low"],
                        close_price=d["close"],
                        gateway_name=self.gateway_name
                    )
                    buf.append(bar)

                history.extend(buf)

                begin = buf[0].datetime
                end = buf[-1].datetime
                msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
                self.gateway.write_log(msg)

                # Update start time
                start = bar.datetime

                # Break if data end reached
                if len(buf) < count:
                    break

        return history

    def new_local_orderid(self) -> str:
        """"""
        with self.order_count_lock:
            self.order_count += 1
            local_orderid = f"{self.connect_time}{self.order_count}"
            return local_orderid

    def send_order(self, req: OrderRequest) -> str:
        """"""
        local_orderid = self.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.datetime = datetime.now(CHINA_TZ)

        data = {
            "contract_code": req.symbol,
            "client_order_id": int(local_orderid),
            "price": req.price,
            "volume": int(req.volume),
            "direction": DIRECTION_VT2HUOBIS.get(req.direction, ""),
            "offset": OFFSET_VT2HUOBIS.get(req.offset, ""),
            "order_price_type": ORDERTYPE_VT2HUOBIS.get(req.type, ""),
            "lever_rate": self.leverage_ratio
        }

        if self.margin_mode == "cross":
            path = "/linear-swap-api/v1/swap_cross_order"
        else:
            path = "/linear-swap-api/v1/swap_order"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def send_orders(self, reqs: Sequence[OrderRequest]) -> str:
        """"""
        orders_data = []
        orders = []
        vt_orderids = []

        for req in reqs:
            local_orderid = self.new_local_orderid()

            order = req.create_order_data(
                local_orderid,
                self.gateway_name
            )
            order.datetime = datetime.now(CHINA_TZ)
            self.gateway.on_order(order)

            d = {
                "contract_code": req.symbol,
                "client_order_id": int(local_orderid),
                "price": req.price,
                "volume": int(req.volume),
                "direction": DIRECTION_VT2HUOBIS.get(req.direction, ""),
                "offset": OFFSET_VT2HUOBIS.get(req.offset, ""),
                "order_price_type": ORDERTYPE_VT2HUOBIS.get(req.type, ""),
                "lever_rate": 20
            }

            orders_data.append(d)
            orders.append(order)
            vt_orderids.append(order.vt_orderid)

        data = {
            "orders_data": orders_data
        }

        if self.margin_mode == "cross":
            path = "/linear-swap-api/v1/swap_cross_batchorder"
        else:
            path = "/linear-swap-api/v1/swap_batchorder"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_send_orders,
            data=data,
            extra=orders,
            on_error=self.on_send_orders_error,
            on_failed=self.on_send_orders_failed
        )

        return vt_orderids

    def cancel_order(self, req: CancelRequest) -> Request:
        """"""
        buf = [i for i in req.symbol if not i.isdigit()]

        data = {
            "contract_code": "".join(buf),
        }

        orderid = int(req.orderid)
        if orderid > 1000000:
            data["client_order_id"] = orderid
        else:
            data["order_id"] = orderid

        if self.margin_mode == "cross":
            path = "/linear-swap-api/v1/swap_cross_cancel"
        else:
            path = "/linear-swap-api/v1/swap_cancel"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_cancel_order,
            on_failed=self.on_cancel_order_failed,
            data=data,
            extra=req
        )

    def on_query_account(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询账户"):
            return

        for d in data["data"]:
            if d["margin_mode"] == self.margin_mode:
                account = AccountData(
                    accountid=d["margin_asset"],
                    balance=d["margin_balance"],
                    frozen=d["margin_frozen"],
                    gateway_name=self.gateway_name,
                )

                self.gateway.on_account(account)

    def on_query_position(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询持仓"):
            return

        # Clear all buf data
        for position in self.positions.values():
            position.volume = 0
            position.frozen = 0
            position.price = 0
            position.pnl = 0

        for d in data["data"]:
            key = f"{d['contract_code']}_{d['direction']}"
            position = self.positions.get(key, None)

            if not position:
                position = PositionData(
                    symbol=d["contract_code"],
                    exchange=Exchange.HUOBI,
                    direction=DIRECTION_HUOBIS2VT[d["direction"]],
                    gateway_name=self.gateway_name
                )
                self.positions[key] = position

            position.volume = d["volume"]
            position.frozen = d["frozen"]
            position.price = d["cost_hold"]
            position.pnl = d["profit"]

        for position in self.positions.values():
            self.gateway.on_position(position)

    def on_query_order(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询活动委托"):
            return

        for d in data["data"]["orders"]:
            timestamp = d["created_at"]
            dt = generate_datetime(timestamp / 1000)

            if d["client_order_id"]:
                orderid = d["client_order_id"]
            else:
                orderid = d["order_id"]

            order = OrderData(
                orderid=orderid,
                symbol=d["contract_code"],
                exchange=Exchange.HUOBI,
                price=d["price"],
                volume=d["volume"],
                type=ORDERTYPE_HUOBIS2VT[d["order_price_type"]],
                direction=DIRECTION_HUOBIS2VT[d["direction"]],
                offset=OFFSET_HUOBIS2VT[d["offset"]],
                traded=d["trade_volume"],
                status=STATUS_HUOBIS2VT[d["status"]],
                datetime=dt,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_order(order)

        self.gateway.write_log(f"{request.extra}活动委托信息查询成功")

    def on_query_contract(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询合约"):
            return

        for d in data["data"]:
            self.contract_codes.add(d["contract_code"])

            contract = ContractData(
                symbol=d["contract_code"],
                exchange=Exchange.HUOBI,
                name=d["contract_code"],
                pricetick=d["price_tick"],
                size=float(d["contract_size"]),
                min_volume=1,
                product=Product.FUTURES,
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

        self.query_order()

    def on_send_order(self, data: dict, request: Request) -> None:
        """"""
        order = request.extra

        if self.check_error(data, "委托"):
            order.status = Status.REJECTED
            self.gateway.on_order(order)

    def on_send_order_failed(self, status_code: str, request: Request) -> None:
        """
        Callback when sending order failed on server.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg = f"委托失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_send_order_error(
            self,
            exception_type: type,
            exception_value: Exception,
            tb,
            request: Request
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

    def on_cancel_order(self, data: dict, request: Request) -> None:
        """"""
        self.check_error(data, "撤单")

    def on_cancel_order_failed(
            self,
            status_code: str,
            request: Request
    ) -> None:
        """
        Callback when canceling order failed on server.
        """
        msg = f"撤单失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_send_orders(self, data: dict, request: Request) -> None:
        """"""
        orders = request.extra

        errors = data.get("errors", None)
        if errors:
            for d in errors:
                ix = d["index"]
                code = d["err_code"]
                msg = d["err_msg"]

                order = orders[ix]
                order.status = Status.REJECTED
                self.gateway.on_order(order)

                msg = f"批量委托失败，状态码：{code}，信息：{msg}"
                self.gateway.write_log(msg)

    def on_send_orders_failed(
            self,
            status_code: str,
            request: Request
    ) -> None:
        """
        Callback when sending order failed on server.
        """
        orders = request.extra

        for order in orders:
            order.status = Status.REJECTED
            self.gateway.on_order(order)

        msg = f"批量委托失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_send_orders_error(
            self,
            exception_type: type,
            exception_value: Exception,
            tb,
            request: Request
    ):
        """
        Callback when sending order caused exception.
        """
        orders = request.extra

        for order in orders:
            order.status = Status.REJECTED
            self.gateway.on_order(order)

        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_error(
            self,
            exception_type: type,
            exception_value: Exception,
            tb,
            request: Request
    ) -> None:
        """
        Callback to handler request exception.
        """
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )

    def check_error(self, data: dict, func: str = "") -> bool:
        """"""
        if data["status"] != "error":
            return False

        error_code = data["err_code"]
        error_msg = data["err_msg"]

        self.gateway.write_log(f"{func}请求出错，代码：{error_code}，信息：{error_msg}")
        return True


class HuobilWebsocketApiBase(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(HuobilWebsocketApiBase, self).__init__()

        self.gateway: HuobilGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.key: str = ""
        self.secret: str = ""
        self.sign_host: str = ""
        self.path: str = ""
        self.req_id: int = 0

    def connect(
            self,
            key: str,
            secret: str,
            url: str,
            proxy_host: str,
            proxy_port: int
    ) -> None:
        """"""
        self.key = key
        self.secret = secret

        host, path = _split_url(url)
        self.sign_host = host
        self.path = path

        self.init(url, proxy_host, proxy_port)
        self.start()

    def login(self) -> int:
        """"""
        self.req_id += 1

        params = {
            "op": "auth",
            "type": "api",
            "cid": str(self.req_id),
        }
        params.update(
            create_signature(
                self.key,
                "GET",
                self.sign_host,
                self.path,
                self.secret
            )
        )
        return self.send_packet(params)

    def on_login(self, packet) -> None:
        """"""
        pass

    @staticmethod
    def unpack_data(data) -> json.JSONDecoder:
        """"""
        return json.loads(zlib.decompress(data, 31))

    def on_packet(self, packet) -> None:
        """"""
        if "ping" in packet:
            req = {"pong": packet["ping"]}
            self.send_packet(req)
        elif "op" in packet and packet["op"] == "ping":
            req = {
                "op": "pong",
                "ts": packet["ts"]
            }
            self.send_packet(req)
        elif "err-msg" in packet:
            return self.on_error_msg(packet)
        elif "op" in packet and packet["op"] == "auth":
            return self.on_login()
        else:
            self.on_data(packet)

    def on_data(self, packet) -> None:
        """"""
        print("data : {}".format(packet))

    def on_error_msg(self, packet) -> None:
        """"""
        msg = packet["err-msg"]
        if msg == "invalid pong":
            return

        self.gateway.write_log(packet["err-msg"])


class HuobilTradeWebsocketApi(HuobilWebsocketApiBase):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

    def connect(
            self,
            key: str,
            secret: str,
            proxy_host: str,
            proxy_port: int,
            margin_mode: str
    ) -> None:
        """"""
        super().connect(
            key,
            secret,
            WEBSOCKET_TRADE_HOST,
            proxy_host,
            proxy_port
        )

        self.margin_mode = margin_mode

    def subscribe(self) -> int:
        """"""
        self.req_id += 1
        if self.margin_mode == "cross":
            topic = "orders_cross.*"
        else:
            topic = "orders.*"

        req = {
            "op": "sub",
            "cid": str(self.req_id),
            "topic": topic
        }

        self.send_packet(req)

    def on_connected(self) -> None:
        """"""
        self.gateway.write_log("交易Websocket API连接成功")
        self.login()

    def on_login(self) -> None:
        """"""
        self.gateway.write_log("交易Websocket API登录成功")
        self.subscribe()

    def on_data(self, packet) -> None:
        """"""
        op = packet.get("op", None)
        if op != "notify":
            return

        topic = packet["topic"]
        if "orders" in topic:
            self.on_order(packet)

    def on_order(self, data: dict) -> None:
        """"""
        dt = generate_datetime(data["created_at"] / 1000)

        if data["client_order_id"]:
            orderid = data["client_order_id"]
        else:
            orderid = data["order_id"]

        order = OrderData(
            symbol=data["contract_code"],
            exchange=Exchange.HUOBI,
            orderid=orderid,
            type=ORDERTYPE_HUOBIS2VT[data["order_price_type"]],
            direction=DIRECTION_HUOBIS2VT[data["direction"]],
            offset=OFFSET_HUOBIS2VT[data["offset"]],
            price=data["price"],
            volume=data["volume"],
            traded=data["trade_volume"],
            status=STATUS_HUOBIS2VT[data["status"]],
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        # Push trade event
        trades = data["trade"]
        if not trades:
            return

        for d in trades:
            dt = generate_datetime(d["created_at"] / 1000)

            trade = TradeData(
                symbol=order.symbol,
                exchange=Exchange.HUOBI,
                orderid=order.orderid,
                tradeid=str(d["id"]),
                direction=order.direction,
                offset=order.offset,
                price=d["trade_price"],
                volume=d["trade_volume"],
                datetime=dt,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_trade(trade)


class HuobilDataWebsocketApi(HuobilWebsocketApiBase):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.ticks = {}

    def connect(
            self,
            key: str,
            secret: str,
            proxy_host: str,
            proxy_port: int
    ) -> None:
        """"""
        super().connect(
            key,
            secret,
            WEBSOCKET_DATA_HOST,
            proxy_host,
            proxy_port
        )

    def on_connected(self) -> None:
        """"""
        self.gateway.write_log("行情Websocket API连接成功")

        for ws_symbol in self.ticks.keys():
            self.subscribe_data(ws_symbol)

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        buf = [i for i in req.symbol if not i.isdigit()]
        symbol = "".join(buf)

        ws_symbol = f"{symbol}"

        # Create tick data buffer
        tick = TickData(
            symbol=req.symbol,
            name=req.symbol,
            exchange=Exchange.HUOBI,
            datetime=datetime.now(CHINA_TZ),
            gateway_name=self.gateway_name,
        )
        self.ticks[ws_symbol] = tick

        self.subscribe_data(ws_symbol)

    def subscribe_data(self, ws_symbol: str) -> None:
        """"""
        # Subscribe to market depth update
        self.req_id += 1
        req = {
            "sub": f"market.{ws_symbol}.depth.step0",
            "id": str(self.req_id)
        }
        self.send_packet(req)

        # Subscribe to market detail update
        self.req_id += 1
        req = {
            "sub": f"market.{ws_symbol}.detail",
            "id": str(self.req_id)
        }
        self.send_packet(req)

    def on_data(self, packet) -> None:
        """"""
        channel = packet.get("ch", None)
        if channel:
            if "depth.step" in channel:
                self.on_market_depth(packet)
            elif "detail" in channel:
                self.on_market_detail(packet)
        elif "err_code" in packet:
            code = packet["err_code"]
            msg = packet["err_msg"]
            self.gateway.write_log(f"错误代码：{code}, 错误信息：{msg}")

    def on_market_depth(self, data: dict) -> None:
        """行情深度推送 """
        ws_symbol = data["ch"].split(".")[1]
        tick = self.ticks[ws_symbol]
        tick.datetime = generate_datetime(data["ts"] / 1000)

        tick_data = data["tick"]
        if "bids" not in tick_data or "asks" not in tick_data:
            return

        bids = tick_data["bids"]
        for n in range(5):
            price, volume = bids[n]
            tick.__setattr__("bid_price_" + str(n + 1), float(price))
            tick.__setattr__("bid_volume_" + str(n + 1), float(volume))

        asks = tick_data["asks"]
        for n in range(5):
            price, volume = asks[n]
            tick.__setattr__("ask_price_" + str(n + 1), float(price))
            tick.__setattr__("ask_volume_" + str(n + 1), float(volume))

        if tick.last_price:
            self.gateway.on_tick(copy(tick))

    def on_market_detail(self, data: dict) -> None:
        """市场细节推送"""
        ws_symbol = data["ch"].split(".")[1]
        tick = self.ticks[ws_symbol]
        tick.datetime = generate_datetime(data["ts"] / 1000)

        tick_data = data["tick"]
        tick.open_price = tick_data["open"]
        tick.high_price = tick_data["high"]
        tick.low_price = tick_data["low"]
        tick.last_price = tick_data["close"]
        tick.volume = tick_data["vol"]

        if tick.bid_price_1:
            self.gateway.on_tick(copy(tick))


def _split_url(url) -> str:
    """
    将url拆分为host和path
    :return: host, path
    """
    result = re.match("\w+://([^/]*)(.*)", url)  # noqa
    if result:
        return result.group(1), result.group(2)


def create_signature(
        api_key: str,
        method: str,
        host: str,
        path: str,
        secret_key: str,
        get_params=None
) -> Dict:
    """
    创建签名
    :param get_params: dict 使用GET方法时附带的额外参数(urlparams)
    :return:
    """
    sorted_params = [
        ("AccessKeyId", api_key),
        ("SignatureMethod", "HmacSHA256"),
        ("SignatureVersion", "2"),
        ("Timestamp", datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S"))
    ]

    if get_params:
        sorted_params.extend(list(get_params.items()))
        sorted_params = list(sorted(sorted_params))
    encode_params = urllib.parse.urlencode(sorted_params)

    payload = [method, host, path, encode_params]
    payload = "\n".join(payload)
    payload = payload.encode(encoding="UTF8")

    secret_key = secret_key.encode(encoding="UTF8")

    digest = hmac.new(secret_key, payload, digestmod=hashlib.sha256).digest()
    signature = base64.b64encode(digest)

    params = dict(sorted_params)
    params["Signature"] = signature.decode("UTF8")
    return params


def generate_datetime(timestamp: float) -> datetime:
    """"""
    dt = datetime.fromtimestamp(timestamp)
    dt = CHINA_TZ.localize(dt)
    return dt
