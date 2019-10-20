""""""
import hashlib
import hmac
import time
from datetime import datetime, timedelta, timezone

from dataclasses import dataclass
from datetime import datetime
from typing import Any, Dict, List, Tuple
import sys
from dataclasses import dataclass
from datetime import datetime
from threading import Lock
from typing import List, TYPE_CHECKING, Tuple
from urllib.parse import urlencode

from requests import ConnectionError

import hashlib
import hmac
import sys
import time
from collections import defaultdict
from copy import copy
from datetime import datetime
from typing import Any, Callable, Dict, TYPE_CHECKING

from sortedcontainers import SortedSet

from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (Exchange, Product)
from vnpy.trader.object import (AccountData, ContractData, SubscribeRequest, TickData, TradeData)
from .common import (DIRECTION_BYBIT2VT, generate_timestamp, local_tz, parse_datetime, sign, utc_tz)



from vnpy.api.rest import Request, RestClient
from vnpy.trader.constant import Exchange, Interval, OrderType, Product, Status
from vnpy.trader.object import AccountData, BarData, CancelRequest, ContractData, OrderRequest
from .common import (DIRECTION_VT2BYBIT, INTERVAL_VT2BYBIT, ORDER_TYPE_VT2BYBIT, generate_timestamp,
                     parse_datetime, sign, INTERVAL_VT2BYBIT_INT)


from vnpy.event import Event
from vnpy.gateway.bybit.rest_api import BybitRestApi, HistoryDataNextInfo
from vnpy.gateway.bybit.websocket_api import BybitWebsocketApi
from vnpy.trader.constant import (Exchange, Interval, OrderType)
from vnpy.trader.constant import Direction, Interval, OrderType, Status
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (BarData, CancelRequest, HistoryRequest, OrderData, OrderRequest,
                                PositionData, SubscribeRequest, TickData)
from .common import (DIRECTION_BYBIT2VT, INTERVAL_VT2BYBIT_INT, OPPOSITE_DIRECTION,
                     ORDER_TYPE_BYBIT2VT, STATUS_BYBIT2VT, STOP_ORDER_STATUS_BYBIT2VT, local_tz,
                     parse_datetime, utc_tz)


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

if TYPE_CHECKING:
    from vnpy.gateway.bybit import BybitGateway

if TYPE_CHECKING:
    from vnpy.gateway.bybit import BybitGateway

HOST = "wss://stream.bybit.com/realtime"
TEST_HOST = "wss://stream-testnet.bybit.com/realtime"


def _(x): return x  # noqa


HOST = "https://api.bybit.com"
TEST_HOST = "https://api-testnet.bybit.com"

# asked from official developer
PRICE_TICKS = {
    "BTCUSD": 0.5,
    "ETHUSD": 0.05,
    "EOSUSD": 0.001,
    "XRPUSD": 0.0001,
}

utc_tz = timezone.utc
local_tz = datetime.now(timezone.utc).astimezone().tzinfo


@dataclass()
class HistoryDataInfo:
    bars: List[BarData]
    extra: Any




@dataclass()
class HistoryDataNextInfo:
    symbol: str
    interval: Interval
    end: int


class RequestFailedException(Exception):
    pass





class BybitGateway(BaseGateway):
    """
    VN Trader Gateway for BitMEX connection.
    """

    default_setting = {
        "APIKey": "",
        "PrivateKey": "",
        "会话数": 3,
        "服务器": ["REAL", "TESTNET"],
        "代理地址": "",
        "代理端口": "",
    }
    HISTORY_RECORD_PER_REQUEST = 200  # # of records per history request

    exchanges = [Exchange.BYBIT]

    def __init__(self, event_engine):
        """Constructor"""
        super(BybitGateway, self).__init__(event_engine, "BYBIT")

        self.rest_api = BybitRestApi(self)
        self.ws_api = BybitWebsocketApi(self)

        self.ticks: Dict[str, TickData] = {}
        self.orders: Dict[str, OrderData] = {}
        self.local2sys_map: Dict[str, str] = {}
        event_engine.register(EVENT_TIMER, self.process_timer_event)

    def connect(self, setting: dict):
        """"""
        key = setting["ID"]
        secret = setting["Secret"]
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
        self.rest_api.query_orders()
        self.query_contracts()
        self.query_account()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.rest_api.cancel_order(req)

    def query_contracts(self):
        self.rest_api.query_contracts()

    def query_account(self):
        """"""
        self.rest_api.query_position()

    def query_position(self):
        """"""
        self.rest_api.query_position()

    def query_first_history(self,
                            symbol: str,
                            interval: Interval,
                            start: datetime,
                            ) -> Tuple[List[BarData], "HistoryDataNextInfo"]:

        # datetime for a bar is close_time
        # we got open_time from API.
        adjustment = INTERVAL_VT2BYBIT_INT[interval]

        utc_time = start.replace(tzinfo=local_tz).astimezone(tz=utc_tz)
        return self.rest_api.query_history(
            symbol=symbol,
            interval=interval,

            # todo: vnpy: shall all datetime object use tzinfo?
            start=int(utc_time.timestamp()) - adjustment,
        )

    def query_next_history(self,
                           next_info: Any,
                           ):
        data: "HistoryDataNextInfo" = next_info
        return self.rest_api.query_history(
            symbol=data.symbol,
            interval=data.interval,
            start=data.end,
        )

    def query_history(self, req: HistoryRequest):
        """
        todo: vnpy: download in parallel
        todo: vnpy: use yield to simplify logic
        :raises RequestFailedException: if server reply an error.
                Any Exception might be raised from requests.request: network error.
        """
        # todo: this function: test rate limit
        history = []

        symbol = req.symbol
        interval = req.interval
        start = req.start

        bars, next_info = self.query_first_history(
            symbol=symbol,
            interval=interval,
            start=start,
        )
        msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{bars[0].datetime} - {bars[-1].datetime}"
        self.write_log(msg)
        history.extend(bars)
        while True:
            bars, next_info = self.query_next_history(next_info)

            msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{bars[0].datetime} - {bars[-1].datetime}"
            self.write_log(msg)

            # Break if total data count less than <count> (latest date collected)
            if len(bars) < self.HISTORY_RECORD_PER_REQUEST:
                break
            history.extend(bars)
        return history

    def close(self):
        """"""
        self.rest_api.stop()
        self.ws_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        self.rest_api.increase_rate_limit()
        if self.rest_api.alive:
            self.query_account()
            self.rest_api.query_stop_orders()

    def write_log(self, msg: str):
        return super().write_log(msg)

    def parse_order_data(self, data: dict, time_key: str = 'updated_at'):
        """
        Parse order data from json dict.
        todo: gateway: put this function to another place.
        :note: this method will not fill 'time' record. Fill it by yourself.
        """
        # prefer local_id as order_id
        order_id = data["order_link_id"]
        sys_id = data['order_id']
        if not order_id:
            order_id = sys_id

        # saving mapping from order_id to sys_id
        self.local2sys_map[order_id] = sys_id

        order = self.orders.get(order_id, None)
        time = parse_datetime(data[time_key])

        # filter outdated order
        if order is not None and time < order.time:  # string cmp is ok here.
            return None

        # if order not exist(created outside this client)
        # create it.
        if order is None:
            order = OrderData(
                symbol=data["symbol"],
                exchange=Exchange.BYBIT,
                type=ORDER_TYPE_BYBIT2VT[data["order_type"]],
                orderid=order_id,
                direction=DIRECTION_BYBIT2VT[data["side"]],
                price=data["price"],
                volume=data["qty"],
                time=time,
                gateway_name=self.gateway_name,
            )
            self.orders[order.orderid] = order
        order.traded = data.get("cum_exec_qty", order.traded)
        if 'order_status' in data:
            order.status = STATUS_BYBIT2VT[data["order_status"]]
        return order

    def parse_stop_order_data(self, data):
        """
        Parse order data from json dict.
        todo: put this function to another place.
        :note: this method will not fill 'time' record. Fill it by yourself.
        """
        # prefer local_id as order_id
        order_id = data["order_link_id"]
        sys_id = data['stop_order_id']
        if not order_id:
            order_id = sys_id

        # saving mapping from order_id to sys_id
        self.local2sys_map[order_id] = sys_id

        order = self.orders.get(order_id, None)

        # if order not exist(created outside this client)
        # create it.
        if not order:
            order = OrderData(
                symbol=data["symbol"],
                exchange=Exchange.BYBIT,
                type=OrderType.STOP,
                orderid=order_id,
                direction=DIRECTION_BYBIT2VT[data["side"]],
                price=data["price"],
                volume=data["qty"],
                # this should be filled manually
                time=parse_datetime(data['updated_at']),
                gateway_name=self.gateway_name,
            )
            self.orders[order.orderid] = order
            if 'stop_order_status' in data:
                # status = STATUS_BYBIT2VT.get(data["order_status"], None)
                # if status is None:
                #     status = STOP_ORDER_STATUS_BYBIT2VT[data["order_status"]]
                # order.status = status
                order.status = STOP_ORDER_STATUS_BYBIT2VT[data["stop_order_status"]]
        return order

    def orderid2sys(self, order_id: str):
        """
        Convert order_id to sys_id
        """
        return self.local2sys_map[order_id]

    def parse_position_data(self, data):
        position = PositionData(
            gateway_name=self.gateway_name,
            symbol=data["symbol"],
            exchange=Exchange.BYBIT,
            direction=DIRECTION_BYBIT2VT[data['side']],
            volume=data['size'],
            price=data['entry_price']
        )

        # clear opposite direction if necessary
        if position.volume:
            pos2 = PositionData(
                gateway_name=position.gateway_name,
                symbol=position.symbol,
                exchange=Exchange.BYBIT,
                direction=OPPOSITE_DIRECTION[position.direction],
                volume=0,
                price=0,
            )
            return position, pos2
        return position, None

    def on_order(self, order: OrderData):
        """
        Since WebSocket and RestClient will push the same orders asynchronously and separately
        outdated orders should be filtered.
        Outdated orders is filtered by parse_xxx_order_data(), returning None.
        """
        if order is not None:
            super().on_order(order)


class BybitRestApi(RestClient):
    """
    BitMEX REST API
    """

    def __init__(self, gateway: "BybitGateway"):
        """"""
        super(BybitRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = b""

        self.order_count = 1_000_000
        self.order_count_lock = Lock()

        self.connect_time = 0

        # Use 60 by default, and will update after first request
        self.rate_limit_limit = 60
        self.rate_limit_remaining = 60
        self.rate_limit_sleep = 0

    @property
    def ticks(self):
        return self.gateway.ticks

    def sign(self, request):
        """
        Generate BitMEX signature.
        """

        if request.method == "GET":
            api_params = request.params  # dict 2 sign
            if api_params is None:
                api_params = request.params = {}
        else:  # POST
            api_params = request.data
            if api_params is None:
                api_params = request.data = {}

        expires = generate_timestamp(0)

        api_params['api_key'] = self.key
        api_params['recv_window'] = 30 * 1000
        api_params['timestamp'] = expires

        data2sign = urlencode({k: api_params[k] for k in sorted(api_params)})
        signature = sign(self.secret, data2sign.encode())
        api_params['sign'] = signature

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
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        if server == "REAL":
            self.init(HOST, proxy_host, proxy_port)
        else:
            self.init(TEST_HOST, proxy_host, proxy_port)

        self.start(session_number)

        self.gateway.write_log(_("REST API启动成功"))

    def _new_order_id(self):
        """"""
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest):
        """"""
        if not self.check_rate_limit():
            return ""

        order_id = str(self.connect_time + self._new_order_id())

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
        if req.type != OrderType.STOP:
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
        else:
            assert self.ticks[symbol], _("Subscribe This Symbol before sending StopOrder.")
            last_price = self.ticks[symbol].last_price
            data["order_type"] = 'Market'
            data["stop_px"] = req.price
            data["base_price"] = last_price
            self.add_request(
                "POST",
                "/open-api/stop-order/create",
                callback=self.on_send_stop_order,
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
        sys_id = self.gateway.orderid2sys(req.orderid)
        order = self.gateway.orders[req.orderid]

        if order.type != OrderType.STOP:
            path = "/open-api/order/cancel"
            key = "order_id"
            callback = self.on_cancel_order
        else:
            path = "/open-api/stop-order/cancel"
            key = "stop_order_id"
            callback = self.on_cancel_stop_order

        self.add_request(
            "POST",
            path,
            callback=callback,
            data={
                key: sys_id,
                "symbol": req.symbol,
            },
            on_error=self.on_cancel_order_error,
            extra=order,
        )

    def query_history(self,
                      symbol: str,
                      interval: Interval,
                      start: int,  # unix timestamp
                      limit: int = None,
                      ) -> Tuple[List[BarData], "HistoryDataNextInfo"]:
        """
        Get history data synchronously.
        """
        if limit is None:
            limit = self.gateway.HISTORY_RECORD_PER_REQUEST

        bars = []

        # datetime for a bar is close_time
        # we got open_time from API.
        adjustment = INTERVAL_VT2BYBIT_INT[interval]

        params = {
            "interval": INTERVAL_VT2BYBIT[interval],
            "symbol": symbol,
            "limit": limit,
            "from": start,
        }

        # todo: RestClient: return RestClient.Request object instead of requests.Response.
        resp = self.request(
            "GET",
            "/v2/public/kline/list",
            params=params
        )

        # Break if request failed with other status code
        raw_data = resp.json()
        if not self.is_request_success(raw_data, None):
            msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
            self.gateway.write_log(msg)
            raise RequestFailedException(msg)
        result = raw_data['result']
        for data in result:
            open_time = int(data["open_time"])
            close_time = open_time + adjustment
            close_dt = datetime.fromtimestamp(close_time)
            bar = BarData(
                symbol=symbol,
                exchange=Exchange.BYBIT,
                datetime=close_dt,
                interval=interval,
                volume=data["volume"],
                open_price=data["open"],
                high_price=data["high"],
                low_price=data["low"],
                close_price=data["close"],
                gateway_name=self.gateway_name
            )
            bars.append(bar)

        end = result[-1]["open_time"]
        return bars, HistoryDataNextInfo(symbol, interval, end)

    def on_send_order_failed(self, status_code: int, request: Request):
        """
        Callback when sending order failed on server.
        """
        data = request.response.json()
        self.update_rate_limit(data)

        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg = f"委托失败，错误代码:{data['ret_code']},  错误信息：{data['ret_msg']}"

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

    def on_send_order(self, raw_data: dict, request: Request):
        """"""

        data = raw_data['result']
        order = self.gateway.parse_order_data(data)
        self.gateway.on_order(order)

        self.update_rate_limit(raw_data)

    def on_send_stop_order(self, raw_data: dict, request: Request):
        """"""
        data = raw_data['result']
        order = self.gateway.parse_stop_order_data(data)
        order.time = parse_datetime(data['updated_at'])
        self.gateway.on_order(order)

        self.update_rate_limit(raw_data)

    def on_cancel_order_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when cancelling order failed on server.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, raw_data: dict, request: Request):
        """"""
        data: dict = raw_data['result']

        order = self.gateway.parse_order_data(data)
        self.gateway.on_order(order)
        self.update_rate_limit(data)

    def on_cancel_stop_order(self, raw_data: dict, request: Request):
        """"""
        data: dict = raw_data['result']
        order = self.gateway.parse_stop_order_data(data)
        order.time = parse_datetime(data['updated_at'])
        self.gateway.on_order(order)
        self.update_rate_limit(data)

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        data = request.response.json()
        self._handle_error_response(data, request)

    def _handle_error_response(self, data, request, operation_name: str = None):
        if operation_name is None:
            operation_name = request.path

        self.update_rate_limit(data)
        error_msg = data["ret_msg"]
        error_code = data['ret_code']
        msg = f"请求{operation_name}失败，状态码：{request.status}，错误代码：{error_code}, 信息：{error_msg}"
        msg += f'\n{request}'
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

    def update_rate_limit(self, data: dict):
        """
        Update current request limit remaining status.
        :param data:
        """
        remaining = data.get('rate_limit_status', None)
        if remaining is not None:
            self.rate_limit_remaining = remaining

    def increase_rate_limit(self):
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
            msg = f"请求过于频繁，已被Bybit限制，请等待{self.rate_limit_sleep}秒后再试"
            self.gateway.write_log(msg)
            return False
        # Just local request limit is reached
        elif not self.rate_limit_remaining:
            msg = "请求频率太高，有触发Bybit流控的风险，请稍候再试"
            self.gateway.write_log(msg)
            return False
        else:
            self.rate_limit_remaining -= 1
            return True

    def is_request_success(self, data: dict, request: "Request"):
        return data['ret_code'] == 0

    def query_contracts(self):
        self.add_request("GET",
                         "/v2/public/tickers",
                         self.on_query_contracts)

    def on_query_contracts(self, data: dict, request: "Request"):
        for result in data['result']:
            symbol = result['symbol']
            contract = ContractData(
                gateway_name=self.gateway_name,
                symbol=symbol,
                exchange=Exchange.BYBIT,
                name=symbol,
                product=Product.FUTURES,
                size=1,
                # todo: pricetick: Currently(2019-9-2) unable to query.
                pricetick=PRICE_TICKS.get(symbol, 0.0001),
            )
            self.gateway.on_contract(contract)

    def query_position(self):
        self.add_request("GET",
                         "/position/list",
                         self.on_query_position
                         )

    def on_query_position(self, raw_data: dict, request: "Request"):
        for data in raw_data['result']:
            p1, p2 = self.gateway.parse_position_data(data)
            self.gateway.on_position(p1)
            if p2:
                self.gateway.on_position(p2)

            account = AccountData(
                gateway_name=self.gateway_name,
                accountid=p1.symbol,
                balance=data['wallet_balance'],
                frozen=data['order_margin']
            )
            self.gateway.on_account(account)

    def query_orders(self):
        """
        query all orders, including stop orders
        """
        self.add_request("GET",
                         "/open-api/order/list",
                         callback=self.on_query_orders,
                         )
        self.query_stop_orders()

    def query_stop_orders(self):
        self.add_request("GET",
                         "/open-api/stop-order/list",
                         callback=self.on_query_stop_orders,
                         )

    def on_query_orders(self, raw_data: dict, request: "Request"):
        result = raw_data['result']
        for data in result['data']:
            if data['order_status'] != 'NotActive':  # UnTriggered StopOrder
                order = self.gateway.parse_order_data(data)
                self.gateway.on_order(order)

    def on_query_stop_orders(self, raw_data: dict, request: "Request"):
        result = raw_data['result']
        for data in result['data']:
            order = self.gateway.parse_stop_order_data(data)
            self.gateway.on_order(order)






class RawOrderInfo:

    def __init__(self, raw_data: dict):
        self.id = raw_data['id']
        self.price = raw_data['price']
        self.side = raw_data['side']  # 'Buy', 'Sell'
        self.size = raw_data.get('size', 0)

    def __lt__(self, rhs: "RawOrderInfo"):
        return self.price < rhs.price

    def __eq__(self, rhs: "RawOrderInfo"):
        return self.price == rhs.price

    def __hash__(self):
        return self.id  # price is a string and we don't known its precision


class BybitWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway: "BybitGateway"):
        """"""
        super(BybitWebsocketApi, self).__init__()

        self.server: str = ""  # REAL or TESTNET
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = b""

        self._instrument_info_data: Dict[str, dict] = defaultdict(dict)
        self._orderbook_data: Dict[str, SortedSet[RawOrderInfo]] = defaultdict(SortedSet)

        self.accounts = {}

        self._topic_callbacks = {}

    @property
    def ticks(self):
        return self.gateway.ticks

    @property
    def orders(self):
        return self.gateway.orders

    def connect(
        self, key: str, secret: str, server: str, proxy_host: str, proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret.encode()
        self.proxy_host = proxy_host
        self.proxy_port = proxy_port
        self.server = server

        self.reset_authentication()
        self.start()

    def reset_authentication(self):
        expires = generate_timestamp(30)
        d2s = f"GET/realtime{int(expires)}"
        signature = sign(self.secret, d2s.encode())
        params = f"api_key={self.key}&expires={expires}&signature={signature}"
        if self.server == "REAL":
            host = HOST
        else:
            host = TEST_HOST
        url = f'{host}?{params}'
        self.init(url, self.proxy_host, self.proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data upate.
        """
        symbol = req.symbol
        self._subscribe_topic(f"instrument_info.100ms.{symbol}", self.on_tick)
        self._subscribe_topic(f"orderBookL2_25.{symbol}", self.on_depth)

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接且认证成功")
        self._subscribe_initialize_topics()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")
        self.reset_authentication()

    def on_packet(self, packet: dict):
        """"""
        success = packet.get('success', None)
        topic = packet.get('topic', None)
        if success is not None:
            if success is False:
                self.gateway.write_log("Websocket API报错：%s" % packet["ret_msg"])
        elif topic is not None:
            self._topic_callbacks[topic](topic, packet)
        else:
            self.gateway.write_log(f"unkonwn packet: {packet}")

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(
            exception_type, exception_value, tb))

    def authenticate(self):
        """
        Authenticate websockey connection to subscribe private topic.
        """
        expires = int(time.time())
        method = "GET"
        path = "/realtime"
        msg = method + path + str(expires)
        signature = hmac.new(
            self.secret, msg.encode(), digestmod=hashlib.sha256
        ).hexdigest()

        req = {"op": "authKey", "args": [self.key, expires, signature]}
        self.send_packet(req)

    def _subscribe_topic(self, topic: str, callback: Callable[[str, dict], Any]):
        """
        Subscribe to all private topics.
        """
        self._topic_callbacks[topic] = callback

        req = {
            "op": "subscribe",
            "args": [topic],
        }
        self.send_packet(req)

    def _subscribe_initialize_topics(self):
        """
        Subscribe to all private topics.
        """
        self._subscribe_topic("order", self.on_order)
        self._subscribe_topic("execution", self.on_trade)
        self._subscribe_topic("position", self.on_position)

    def _get_last_tick(self, symbol: str):
        tick = self.ticks.get(symbol, None)
        if tick is None:
            # noinspection PyTypeChecker
            tick = TickData(
                symbol=symbol,
                exchange=Exchange.BYBIT,
                name=symbol,
                datetime=None,  # this will be filled before this new created tick is consumed.
                gateway_name=self.gateway_name,
            )
            self.ticks[symbol] = tick
        return tick

    def on_tick(self, topic: str, raw_data: dict):
        """"""
        # parse incremental data sent from server
        symbol = topic[22:]
        self._update_tick_incremental_data(symbol, raw_data)

        # convert dict into TickData
        last_data = self._instrument_info_data[symbol]
        tick = self._get_last_tick(symbol)
        tick.last_price = last_data["last_price_e4"] / 10000
        tick.datetime = _parse_timestamp_e6(raw_data['timestamp_e6'])
        self.gateway.on_tick(copy(tick))

    def _update_tick_incremental_data(self, symbol, raw_data):
        type_ = raw_data['type']
        data = raw_data['data']
        last_data = self._instrument_info_data[symbol]
        if type_ == 'snapshot':
            last_data.clear()
            last_data.update(data)
        elif type_ == 'delta':
            updates = data['update']
            for update in updates:
                assert update['symbol'] == symbol
                last_data.update(update)
        else:
            self.gateway.write_log(f"Unknown type {type_} in websocket_api.on_tick()")

    def on_depth(self, topic: str, raw_data: dict):
        """"""
        symbol = topic[15:]
        self._update_depth_incremental_data(symbol, raw_data)

        last_data = self._orderbook_data[symbol]

        tick = self._get_last_tick(symbol)
        for n, parsed in enumerate(last_data.islice(20, 25)):
            tick.__setattr__(f"bid_price_{5 - n}", parsed.price)
            tick.__setattr__(f"bid_volume_{5 - n}", parsed.size)

        for n, parsed in enumerate(last_data.islice(25, 30)):
            tick.__setattr__(f"ask_price_{n + 1}", parsed.price)
            tick.__setattr__(f"ask_volume_{n + 1}", parsed.size)

        tick.datetime = _parse_timestamp_e6(raw_data['timestamp_e6'])
        self.gateway.on_tick(copy(tick))

    def _update_depth_incremental_data(self, symbol, raw_data):
        type_ = raw_data['type']
        data = raw_data['data']
        last_data = self._orderbook_data[symbol]
        if type_ == 'snapshot':
            last_data.clear()
            for item in data:
                assert item['symbol'] == symbol
                parsed = RawOrderInfo(item)
                last_data.add(parsed)
        elif type_ == 'delta':
            deletes = data['delete']
            for delete in deletes:
                assert delete['symbol'] == symbol
                parsed = RawOrderInfo(delete)
                last_data.remove(parsed)

            updates = data['update']
            for update in updates:
                assert update['symbol'] == symbol
                parsed = RawOrderInfo(update)
                last_data.remove(parsed)
                last_data.add(parsed)

            inserts = data['insert']
            for insert in inserts:
                assert insert['symbol'] == symbol
                parsed = RawOrderInfo(insert)
                last_data.add(parsed)
        else:
            self.gateway.write_log(f"Unknown type {type_} in websocket_api.on_tick()")

    def on_trade(self, topic: str, raw_data: dict):
        """"""
        for data in raw_data['data']:
            order_id = data['order_link_id']
            if not order_id:
                order_id = data['order_id']
            trade = TradeData(
                symbol=data["symbol"],
                exchange=Exchange.BYBIT,
                orderid=order_id,
                tradeid=data['exec_id'],
                direction=DIRECTION_BYBIT2VT[data["side"]],
                price=data["price"],
                volume=data["exec_qty"],
                time=parse_datetime(data["trade_time"]),
                gateway_name=self.gateway_name,
            )

            self.gateway.on_trade(trade)

    def on_order(self, topic: str, raw_data: dict):
        """"""
        for data in raw_data['data']:
            print(data)
            order = self.gateway.parse_order_data(data, 'timestamp')

            self.gateway.on_order(copy(order))

    def on_position(self, topic: str, raw_data: dict):
        """"""
        for data in raw_data['data']:
            p1, p2 = self.gateway.parse_position_data(data)
            self.gateway.on_position(p1)
            if p2:
                self.gateway.on_position(p2)

    def on_account(self, d):
        """"""
        accountid = str(d["account"])
        account = self.accounts.get(accountid, None)
        if not account:
            account = AccountData(accountid=accountid,
                                  gateway_name=self.gateway_name)
            self.accounts[accountid] = account

        account.balance = d.get("marginBalance", account.balance)
        account.available = d.get("availableMargin", account.available)
        account.frozen = account.balance - account.available

        self.gateway.on_account(copy(account))

    def on_contract(self, d):
        """"""
        if "tickSize" not in d:
            return

        if not d["lotSize"]:
            return

        contract = ContractData(
            symbol=d["symbol"],
            exchange=Exchange.BYBIT,
            name=d["symbol"],
            product=Product.FUTURES,
            pricetick=d["tickSize"],
            size=d["lotSize"],
            stop_supported=True,
            net_position=True,
            history_data=True,
            gateway_name=self.gateway_name,
        )

        self.gateway.on_contract(contract)

    def _ping(self):
        super()._ping()
        self.send_packet({'op': 'ping'})


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
