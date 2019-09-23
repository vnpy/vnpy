import sys
from dataclasses import dataclass
from datetime import datetime
from threading import Lock
from typing import List, TYPE_CHECKING, Tuple
from urllib.parse import urlencode

from requests import ConnectionError

from vnpy.api.rest import Request, RestClient
from vnpy.trader.constant import Exchange, Interval, OrderType, Product, Status
from vnpy.trader.object import AccountData, BarData, CancelRequest, ContractData, OrderRequest
from .common import (DIRECTION_VT2BYBIT, INTERVAL_VT2BYBIT, ORDER_TYPE_VT2BYBIT, generate_timestamp,
                     parse_datetime, sign, INTERVAL_VT2BYBIT_INT)

if TYPE_CHECKING:
    from vnpy.gateway.bybit import BybitGateway
_ = lambda x: x  # noqa

HOST = "https://api.bybit.com"
TEST_HOST = "https://api-testnet.bybit.com"

# asked from official developer
PRICE_TICKS = {
    "BTCUSD": 0.5,
    "ETHUSD": 0.05,
    "EOSUSD": 0.001,
    "XRPUSD": 0.0001,
}


@dataclass()
class HistoryDataNextInfo:
    symbol: str
    interval: Interval
    end: int


class RequestFailedException(Exception):
    pass


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
