"""
Gateway for MXC Crypto Exchange.
"""

import hashlib
import hmac
import json
import time
from copy import copy
from datetime import datetime, timedelta
from threading import Lock

from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
from vnpy.event import Event
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Product,
    Status,
    OrderType,
    Interval
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)

REST_HOST = "https://www.mxc.ceo"
WEBSOCKET_HOST = "wss://wbs.mxc.com/raw/ws"

STATUS_MXC2VT = {
    "NEW": Status.NOTTRADED,
    "PARTIALLY_FILLED": Status.PARTTRADED,
    "FILLED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
    "PARTIALLY_CANCELED": Status.PARTTRADED
}

ORDERTYPE_VT2MXC = {
    OrderType.LIMIT: "LIMIT_ORDER",
    OrderType.FOK: "IMMEDIATE_OR_CANCEL"
}
ORDERTYPE_MXC2VT = {v: k for k, v in ORDERTYPE_VT2MXC.items()}

DIRECTION_VT2MXC = {
    Direction.LONG: "BID",
    Direction.SHORT: "ASK"
}
DIRECTION_MXC2VT = {v: k for k, v in DIRECTION_VT2MXC.items()}

INTERVAL_VT2MXC = {
    Interval.MINUTE: "1m",
    Interval.HOUR: "1h",
    Interval.DAILY: "1d",
}

TIMEDELTA_MAP = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}

symbol_name_map = {}


class MXCGateway(BaseGateway):
    """
    VN Trader Gateway for MXC connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "session_number": 3,
        "proxy_host": "",
        "proxy_port": 0,
    }

    exchanges = [Exchange.MXC]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "MXC")

        self.ws_api = MXCWebsocketApi(self)
        self.rest_api = MXCRestApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session_number = setting["session_number"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        self.rest_api.connect(key, secret, session_number,
                              proxy_host, proxy_port)
        self.ws_api.connect(proxy_host, proxy_port)

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
        pass


class MXCRestApi(RestClient):
    """
    MXC REST API
    """

    def __init__(self, gateway: MXCGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.ws_api = self.gateway.ws_api

        self.key = ""
        self.secret = ""

        self.recv_window = 5000
        self.time_offset = 0

        self.order_count = 1_000_000
        self.order_count_lock = Lock()
        self.connect_time = 0

    def sign(self, request):
        """
        Generate MXC signature.
        """
        params = {
            'api_key': self.key,
            'req_time': int(time.time()),
        }
        if request.params:
            params.update(request.params)
        params_str = '&'.join('{}={}'.format(k, params[k]) for k in sorted(params))
        to_sign = '\n'.join([request.method, request.path, params_str])
        params.update({'sign': hmac.new(self.secret, to_sign.encode(), hashlib.sha256).hexdigest()})

        request.params = params
        if request.data:
            request.data = json.dumps(request.data)

        # Add headers
        headers = {
            "Content-Type": "application/json",
            "Accept": "application/json",
        }

        request.headers = headers

        return request

    def connect(
            self,
            key: str,
            secret: str,
            session_number: int,
            proxy_host: str,
            proxy_port: int
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret.encode()
        self.proxy_port = proxy_port
        self.proxy_host = proxy_host

        self.connect_time = (
                int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session_number)

        self.gateway.write_log("REST API启动成功")
        self.query_time()
        self.query_contract()
        self.query_account()

    def query_time(self):
        """"""
        path = "/open/api/v2/common/timestamp"

        return self.add_request(
            "GET",
            path,
            callback=self.on_query_time,
        )

    def query_account(self):
        """"""
        self.add_request(
            method="GET",
            path="/open/api/v2/account/info",
            callback=self.on_query_account,
        )

    def query_order(self):
        """"""
        self.add_request(
            method="GET",
            path="/open/api/v2/order/open_orders",
            callback=self.on_query_order,
        )

    def query_contract(self):
        """"""
        self.add_request(
            method="GET",
            path="/open/api/v2/market/symbols",
            callback=self.on_query_contract,
        )

    def _new_order_id(self):
        """"""
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest):
        """"""
        orderid = str(self.connect_time + self._new_order_id())
        order = req.create_order_data(
            orderid,
            self.gateway_name
        )
        self.gateway.on_order(order)

        data = {
            'price': req.price,
            'quantity': req.volume,
            'symbol': req.symbol,
            'client_id': orderid,
            'side': DIRECTION_VT2MXC[req.direction],
            'place_type': ORDERTYPE_VT2MXC[req.type]
        }

        self.add_request(
            method="POST",
            path="/open/api/v2/order/place",
            callback=self.on_send_order,
            data=json.dumps(data),
            extra=order,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        params = {
            "order_ids": req.orderid
        }

        self.add_request(
            method="DELETE",
            path="/open/api/v2/order/cancel",
            callback=self.on_cancel_order,
            params=params,
            extra=req
        )

    def on_query_time(self, data, request):
        """"""
        local_time = int(time.time() * 1000)
        server_time = int(data["data"])
        self.time_offset = local_time - server_time

    def on_query_account(self, data, request):
        """"""
        data = data['data']
        for asset, asset_data in data.items():
            account = AccountData(
                accountid=asset,
                balance=float(asset_data["available"]) + float(asset_data["frozen"]),
                frozen=float(asset_data["frozen"]),
                gateway_name=self.gateway_name
            )

            if account.balance:
                self.gateway.on_account(account)

        self.gateway.write_log("账户资金查询成功")

    def on_query_order(self, data, request):
        """"""
        for d in data["data"]:
            dt = datetime.fromtimestamp(d["create_time"] / 1000)
            time = dt.strftime("%Y-%m-%d %H:%M:%S")

            order = OrderData(
                orderid=d["id"],
                symbol=d["symbol"],
                exchange=Exchange.MXC,
                price=float(d["price"]),
                volume=float(d["quantity"]),
                type=ORDERTYPE_MXC2VT.get(d.get('place_type')),
                direction=DIRECTION_MXC2VT[d["type"]],
                traded=float(d["quantity"]) - float(d["remain_quantity"]),
                status=STATUS_MXC2VT.get(d["state"], None),
                time=time,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def on_query_contract(self, data, request):
        """"""
        for d in data["data"]:
            name = d["symbol"]

            pricetick = 0.1 ** d["price_scale"]
            min_volume = 0.1 ** d["quantity_scale"]

            contract = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.MXC,
                name=name,
                pricetick=pricetick,
                size=1,
                min_volume=min_volume,
                product=Product.SPOT,
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

            symbol_name_map[contract.symbol] = contract.name

        self.gateway.write_log("合约信息查询成功")

    def on_send_order(self, data, request):
        """"""
        pass

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

    def on_cancel_order(self, data, request):
        """"""
        pass

    def on_start_user_stream(self, data, request):
        """"""
        pass

    def on_keep_user_stream(self, data, request):
        """"""
        pass

    def query_history(self, req: HistoryRequest):
        """"""
        pass


class MXCWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.ticks = {}

    def connect(self, proxy_host, proxy_port):
        """"""
        self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        self.start()

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data update.
        """
        if req.symbol not in symbol_name_map:
            self.gateway.write_log(f"找不到该合约代码{req.symbol}")
            return
        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            name=req.symbol,
            datetime=datetime.now(),
            gateway_name=self.gateway_name,
        )
        self.ticks[req.symbol] = tick
        d = {
            "op": "sub.limit.depth",
            "symbol": req.symbol,
            "depth": 5
        }
        self.send_packet(d)
        d = {
            "op": "sub.kline",
            "symbol": req.symbol,
            "interval": "Day1"
        }
        self.send_packet(d)
        self.start()

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")

    def on_packet(self, packet: dict):
        """"""
        channel = packet["channel"]
        symbol = packet['symbol']
        data = packet["data"]

        tick = self.ticks[symbol]

        if channel == "push.kline":
            tick.volume = float(data['v'])
            tick.open_price = float(data['o'])
            tick.high_price = float(data['h'])
            tick.low_price = float(data['l'])
            tick.last_price = float(data['c'])
            tick.datetime = datetime.fromtimestamp(float(data['t']))
        else:
            bids = data["bids"]
            for n in range(5):
                price, volume = bids[n]
                tick.__setattr__("bid_price_" + str(n + 1), float(price))
                tick.__setattr__("bid_volume_" + str(n + 1), float(volume))

            asks = data["asks"]
            for n in range(5):
                price, volume = asks[n]
                tick.__setattr__("ask_price_" + str(n + 1), float(price))
                tick.__setattr__("ask_volume_" + str(n + 1), float(volume))

        if tick.last_price:
            self.gateway.on_tick(copy(tick))
