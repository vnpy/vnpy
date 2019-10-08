from dataclasses import dataclass
from datetime import datetime
from threading import Lock
from typing import Dict, List, Optional, TYPE_CHECKING, Tuple

from requests import ConnectionError

from vnpy.api.rest import Request
from vnpy.gateway.oanda.oanda_api_base import OandaApiBase
from vnpy.trader.constant import Direction, Exchange, Interval, Offset, Product, Status
from vnpy.trader.object import AccountData, BarData, CancelRequest, ContractData, OrderRequest, \
    PositionData
from .oanda_common import (INTERVAL_VT2OANDA, INTERVAL_VT2OANDA_DELTA, ORDER_TYPE_VT2OANDA,
                           STATUS_OANDA2VT, local_tz, parse_datetime, parse_time, utc_tz)

if TYPE_CHECKING:
    from vnpy.gateway.oanda import OandaGateway
_ = lambda x: x  # noqa

HOST = "https://api-fxtrade.oanda.com"
TEST_HOST = "https://api-fxpractice.oanda.com"

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
    end: datetime


class RequestFailedException(Exception):
    pass


class OandaRestApi(OandaApiBase):
    """
    Oanda Rest API
    """

    def __init__(self, gateway: "OandaGateway"):
        """"""
        super().__init__(gateway)

        self.order_count = 1_000_000
        self.order_count_lock = Lock()

        self.connect_time = 0

        self.contracts: Dict[str, ContractData] = {}

        self.last_account_transaction_id: Optional[str] = None

        # used for automatic tests.
        self.account_initialized = False
        self.orders_initialized = False

    def connect(
        self,
        key: str,
        session_number: int,
        server: str,
        proxy_host: str,
        proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key

        self.connect_time = (
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        if server == "REAL":
            self.init(HOST, proxy_host, proxy_port)
        else:
            self.init(TEST_HOST, proxy_host, proxy_port)

        self.start(session_number)

        self.gateway.write_log(_("REST API启动成功"))

    def _new_order_id(self) -> str:
        """"""
        with self.order_count_lock:
            self.order_count += 1
            return f'a{self.connect_time}{self.order_count}'

    @staticmethod
    def is_local_order_id(order_id: str):
        return order_id[0] == 'a'

    def send_order(self, req: OrderRequest):
        """"""
        req.offset = Offset.NONE
        order_id = self._new_order_id()

        symbol = req.symbol
        vol = int(req.volume)
        direction = req.direction
        data = {
            "instrument": symbol,
            # positive for long , negative for short
            "units": vol if direction is Direction.LONG else -vol,
            "clientExtensions": {
                "id": order_id,
            }
        }

        order = req.create_order_data(order_id, self.gateway_name)
        order.time = parse_time(datetime.now().isoformat())

        # Only add price for limit order.
        data["type"] = ORDER_TYPE_VT2OANDA[req.type]
        data["price"] = str(req.price)
        self.gateway.orders[order.orderid] = order
        self.add_request(
            "POST",
            f"/v3/accounts/{self.gateway.account_id}/orders",
            callback=self.on_send_order,
            data={'order': data},
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error,
        )
        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        order_id = req.orderid
        order = self.gateway.orders[order_id]

        if self.is_local_order_id(order_id):
            order_id = '@' + order_id
        self.add_request(
            "PUT",
            f"/v3/accounts/{self.gateway.account_id}/orders/{order_id}/cancel",
            callback=self.on_cancel_order,
            extra=order,
        )

    def query_history(self,
                      symbol: str,
                      interval: Interval,
                      start: datetime,
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
        adjustment = INTERVAL_VT2OANDA_DELTA[interval]

        # todo: RestClient: return RestClient.Request object instead of requests.Response.
        resp = self.request(
            "GET",
            f"/v3/instruments/{symbol}/candles",
            params={
                # "price": "M",  # M for mids, B for bids, A for asks
                "granularity": INTERVAL_VT2OANDA[interval],
                "count": 5000,
                "from": start.isoformat(),
            }
        )

        # Break if request failed with other status code
        raw_data = resp.json()
        # noinspection PyTypeChecker
        if not self.is_request_success(raw_data, None):
            msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
            self.gateway.write_log(msg)
            raise RequestFailedException(msg)
        result = raw_data['candles']
        for data in result:
            bar_data = data['mid']
            open_time = parse_datetime(data["time"])
            close_time = open_time + adjustment
            bar = BarData(
                symbol=symbol,
                exchange=Exchange.OANDA,
                datetime=close_time,
                interval=interval,
                volume=data["volume"],
                open_price=float(bar_data["o"]),
                high_price=float(bar_data["h"]),
                low_price=float(bar_data["l"]),
                close_price=float(bar_data["c"]),
                gateway_name=self.gateway_name
            )
            bars.append(bar)

        end = bars[-1].datetime.replace(tzinfo=utc_tz).astimezone(tz=local_tz)
        return bars, HistoryDataNextInfo(symbol, interval, end)

    def on_send_order_failed(self, status_code: int, request: Request):
        """
        Callback when sending order failed on server.
        """
        data = request.response.json()

        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg = f"委托失败，错误代码:{data.get('errorCode', '')},  错误信息：{data['errorMessage']}"
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
        # order: OrderData = request.extra
        # creation = raw_data.get('orderCreateTransaction', None)
        # if creation is not None:
        #     order.status = Status.NOTTRADED
        #     order.time = creation['time'][11:19]
        #     self.gateway.on_order(order)

        # cancel = raw_data.get('orderCancelTransaction', None)
        # if cancel is not None:
        #     # potential bug: stream API will generate a Status.Cancel Order for this transaction
        #     order.status = Status.REJECTED
        #     order.time = parse_time(cancel['time'])
        pass

    def on_cancel_order(self, raw_data: dict, request: Request):
        """"""
        # order: OrderData = request.extra
        # order.status = Status.CANCELLED
        # order.time = raw_data['orderCancelTransaction']['time'][11:19]
        # self.gateway.on_order(order)
        pass

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        data = request.response.json()
        self._handle_error_response(data, request)

    def _handle_error_response(self, data, request, operation_name: str = None):
        if operation_name is None:
            operation_name = request.path

        # todo: rate limit?

        error_msg = data.get("message", None)
        if error_msg is None:
            error_msg = data.get("errorMessage", None)
        msg = f"请求{operation_name}失败，状态码：{request.status}，错误消息：{error_msg}"
        msg += f'\n{request}'
        self.gateway.write_log(msg)

    def query_positions(self):
        self.add_request("GET",
                         f"/v3/accounts/{self.gateway.account_id}/positions",
                         self.on_query_positions
                         )

    def query_account_changes(self):
        do_nothing = lambda a, b, c, d: None  # noqa

        if self.last_account_transaction_id is not None:
            account_id = self.gateway.account_id
            self.add_request("GET",
                             f"/v3/accounts/{account_id}/changes",
                             params={
                                 "sinceTransactionID": self.last_account_transaction_id
                             },
                             callback=self.on_query_account_changes,
                             extra=account_id,
                             on_error=do_nothing,
                             )

    def on_query_account_changes(self, raw_data: dict, request: "Request"):
        account_id: str = request.extra

        # state: we focus mainly on account balance
        state = raw_data['state']
        NAV = float(state['NAV'])
        pnl = float(state['unrealizedPL'])
        account = AccountData(
            gateway_name=self.gateway_name,
            accountid=account_id,
            balance=NAV - pnl,
            frozen=0,  # no frozen
        )
        self.gateway.on_account(account)

        # changes: we focus mainly on position changes
        changes = raw_data['changes']
        positions = changes['positions']
        unrealized_pnls: Dict[(str, Direction), float] = {}

        # pnl in query_account_changes is different from data returned by query_account
        # we have to get pnl from 'state' record.
        for pos_state_data in state['positions']:
            symbol = pos_state_data['instrument']
            unrealized_pnls[(symbol, Direction.LONG)] = float(pos_state_data['longUnrealizedPL'])
            unrealized_pnls[(symbol, Direction.SHORT)] = float(pos_state_data['shortUnrealizedPL'])

        for pos_data in positions:
            pos_long, pos_short = self.parse_position_data(pos_data)
            symbol = pos_long.symbol
            pos_long.pnl = unrealized_pnls[(symbol, Direction.LONG)]
            pos_short.pnl = unrealized_pnls[(symbol, Direction.SHORT)]
            self.gateway.on_position(pos_long)
            self.gateway.on_position(pos_short)
        self.last_account_transaction_id = raw_data['lastTransactionID']

    def on_query_positions(self, raw_data: dict, request: "Request"):
        for pos_data in raw_data['positions']:
            pos_long, pos_short = self.parse_position_data(pos_data)
            self.gateway.on_position(pos_long)
            self.gateway.on_position(pos_short)

    def parse_position_data(self, pos_data) -> Tuple[PositionData, PositionData]:
        symbol = pos_data['instrument']
        pos_long, pos_short = [
            PositionData(
                gateway_name=self.gateway_name,
                symbol=symbol,
                exchange=Exchange.OANDA,
                direction=direction,
                volume=int(data['units']),
                price=float(data.get('averagePrice', 0.0)),
                pnl=float(data.get('unrealizedPL', 0.0)),
            )
            for direction, data in (
                (Direction.LONG, pos_data['long']),
                (Direction.SHORT, pos_data['short'])
            )
        ]
        return pos_long, pos_short

    def query_orders(self):
        """
        query all orders, including stop orders
        """
        self.add_request("GET",
                         f"/v3/accounts/{self.gateway.account_id}/orders?state=ALL",
                         callback=self.on_query_orders,
                         )

    def on_query_orders(self, raw_data: dict, request: "Request"):
        for data in raw_data['orders']:
            order = self.gateway.parse_order_data(data,
                                                  STATUS_OANDA2VT[data['state']],
                                                  'createTime')
            self.gateway.on_order(order)
        self.orders_initialized = True

    def query_accounts(self):
        self.add_request("GET",
                         "/v3/accounts",
                         callback=self.on_query_accounts,
                         )

    def on_query_accounts(self, raw_data: dict, request: "Request"):
        """
        {"accounts":[{"id":"101-001-12185735-001","tags":[]}]}
        """
        for acc in raw_data['accounts']:
            account_id: str = acc['id']
            self.gateway.account_id = account_id

            self.query_account(account_id)
            self.query_contracts(account_id)
            self.query_orders()
            # self.query_positions()

    def query_account(self, account_id: str):
        self.add_request("GET",
                         f"/v3/accounts/{account_id}",
                         callback=self.on_query_account,
                         )

    def on_query_account(self, raw_data: dict, request: "Request"):
        acc = raw_data['account']
        account_data = AccountData(
            gateway_name=self.gateway_name,
            accountid=acc['id'],
            balance=float(acc['balance']),
            frozen=0,  # no frozen
        )
        self.gateway.on_account(account_data)
        for data in acc['orders']:
            # order = self.parse_order_data(data)
            # self.gateway.on_order(order)
            pass
        for pos_data in acc['positions']:
            pos_long, pos_short = self.parse_position_data(pos_data)
            self.gateway.on_position(pos_long)
            self.gateway.on_position(pos_short)
        for trade in acc['trades']:
            pass
        self.last_account_transaction_id = acc['lastTransactionID']
        self.gateway.stream_api.subscribe_transaction()
        self.account_initialized = True

    @property
    def fully_initialized(self):
        return self.account_initialized and self.orders_initialized

    def query_contracts(self, account_id):
        self.add_request("GET",
                         f"/v3/accounts/{account_id}/instruments",
                         self.on_query_contracts)

    def on_query_contracts(self, data: dict, request: "Request"):
        for ins in data['instruments']:
            symbol = ins['name']
            contract = ContractData(
                gateway_name=self.gateway_name,
                symbol=symbol,
                exchange=Exchange.OANDA,
                name=symbol,
                product=Product.FOREX,
                size=1,
                pricetick=1.0 / pow(10, ins['displayPrecision']),
            )
            self.gateway.on_contract(contract)
            self.contracts[symbol] = contract
        self.gateway.write_log(_("合约信息查询成功"))
