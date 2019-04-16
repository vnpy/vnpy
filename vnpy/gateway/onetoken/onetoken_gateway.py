# encoding: UTF-8
"""
"""

import hashlib
import hmac
import json
import time
from datetime import datetime
from threading import Lock
from urllib.parse import urlparse

from requests import ConnectionError

from vnpy.api.rest import Request, RestClient
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Status,
    Offset,
    Product
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    PositionData,
    AccountData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    ContractData
)

REST_HOST = 'https://1token.trade/api'

DIRECTION_VT2ONETOKEN = {Direction.LONG: "b", Direction.SHORT: "s"}
DIRECTION_ONETOKEN2VT = {v: k for k, v in DIRECTION_VT2ONETOKEN.items()}


class OnetokenGateway(BaseGateway):
    """
    VN Trader Gateway for 1Token connection
    """

    default_setting = {
        "OT Key": "",
        "OT Secret": "",
        "交易所": "",
        "账户": "",
        "会话数": 3,
        "代理地址": "127.0.0.1",
        "代理端口": 1080,
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(OnetokenGateway, self).__init__(event_engine, "1Token")

        self.rest_api = OnetokenRestApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["OT Key"]
        secret = setting["OT Secret"]
        session_number = setting["会话数"]
        exchange = setting["交易所"].lower()
        account = setting["账户"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]
        self.rest_api.connect(key, secret, session_number,
                              exchange, account, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """"""
        pass
        # self.ws_api.subscribe(req)

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


class OnetokenRestApi(RestClient):
    """
    1Token REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(OnetokenRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.exchange = ""

        self.order_count = 1_000_000
        self.order_count_lock = Lock()

        self.connect_time = 0
        self.account = ""

    def sign(self, request):
        """
        Generate 1Token signature.
        """
        method = request.method

        endpoint = '/' + request.path.split('/', 3)[3]
        # v1/trade/okex/mock-example/info -> okex/mock-example/info
        parsed_url = urlparse(endpoint)
        path = parsed_url.path

        nonce = str(int(time.time() * 1e6))
        data = request.data
        json_str = data if data else ''

        message = method + path + nonce + json_str

        signature = hmac.new(bytes(self.secret, 'utf8'), bytes(message, 'utf8'), digestmod=hashlib.sha256).hexdigest()

        headers = {'Api-Nonce': nonce,
                   'Api-Key': self.key,
                   'Api-Signature': signature,
                   'Content-Type': 'application/json'}
        request.headers = headers

        return request

    def connect(
            self,
            key: str,
            secret: str,
            session_number: int,
            exchange: str,
            account: str,
            proxy_host: str,
            proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret
        self.exchange = exchange
        self.account = account

        self.connect_time = (
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        self.init(REST_HOST, proxy_host, proxy_port)

        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

        self.query_time()
        self.query_contract()
        self.query_account()

    def _new_order_id(self):
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def query_account(self):  # get balance and positions at the same time
        """"""
        self.add_request(
            "GET",
            "/v1/trade/{}/{}/info".format(self.exchange, self.account),
            callback=self.on_query_account
        )

    def on_query_account(self, data, request):
        """This is for WS Example"""
        for account_data in data["position"]:
            _type = account_data['type']
            if 'spot' in _type:  # 统计balance
                account = AccountData(
                    accountid=account_data["contract"],
                    balance=float(account_data["total_amount"]),
                    frozen=float(account_data["frozen"]),
                    gateway_name=self.gateway_name
                )
                self.gateway.on_account(account)
            elif _type == 'future':  # 期货合约
                long_position = PositionData(
                    symbol=account_data["contract"],
                    exchange=Exchange.OKEX,   # todo add Exchange
                    direction=Direction.LONG,
                    volume=account_data['total_amount_long'],
                    frozen=account_data['total_amount_long'] - account_data['available_long'],
                    gateway_name=self.gateway_name,
                    # yd_volume=?
                )
                short_position = PositionData(
                    symbol=account_data["contract"],
                    exchange=Exchange.OKEX,   # todo add Exchange
                    direction=Direction.SHORT,
                    volume=account_data['total_amount_short'],
                    frozen=account_data['total_amount_short'] - account_data['available_short'],
                    gateway_name=self.gateway_name,
                    # yd_volume=?
                )
                self.gateway.on_position(long_position)
                self.gateway.on_position(short_position)

        self.gateway.write_log("账户资金查询成功")
        self.gateway.write_log("账户持仓查询成功")

    def query_time(self):
        """"""
        self.add_request(
            "GET",
            "/v1/basic/time",
            callback=self.on_query_time
        )

    def on_query_time(self, data, request):
        """"""
        server_timestamp = data["server_time"]
        dt = datetime.utcfromtimestamp(server_timestamp)
        server_time = dt.isoformat() + 'Z'
        local_time = datetime.utcnow().isoformat()
        msg = f"服务器时间：{server_time}，本机时间：{local_time}"
        self.gateway.write_log(msg)

    def query_contract(self):
        """"""
        self.add_request(
            "GET",
            "/v1/basic/contracts?exchange={}".format(self.exchange),
            callback=self.on_query_contract
        )

    def on_query_contract(self, data, request):
        """"""
        for instrument_data in data:
            symbol = instrument_data["name"]
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.OKEX,  # todo
                name=symbol,
                product=Product.SPOT,  # todo
                size=float(instrument_data['min_amount']),
                pricetick=float(instrument_data['unit_amount']),
                gateway_name=self.gateway_name
            )
            self.gateway.on_contract(contract)
        self.gateway.write_log("合约信息查询成功")

        # Start websocket api after instruments data collected
        # self.gateway.ws_api.start()

    def send_order(self, req: OrderRequest):
        """"""
        orderid = str(self.connect_time + self._new_order_id())

        data = {
            'contract': self.exchange + '/' + req.symbol,
            'price': float(req.price),
            "bs": DIRECTION_VT2ONETOKEN[req.direction],
            'amount': float(req.volume),
            'client_oid': orderid
        }

        if req.offset == Offset.CLOSE:
            data['options'] = {'close': True}
        data = json.dumps(data)
        order = req.create_order_data(orderid, self.gateway_name)

        self.add_request(
            method="POST",
            path="/v1/trade/{}/{}/orders".format(self.exchange, self.account),
            callback=self.on_send_order,
            data=data,
            params={},
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        params = {
            'client_oid': req.orderid
        }

        self.add_request(
            method="DELETE",
            path="/v1/trade/{}/{}/orders".format(self.exchange, self.account),
            callback=self.on_cancel_order,
            params=params,
            on_error=self.on_cancel_order_error,
            extra=req
        )

    def on_send_order(self, data, request):
        """Websocket will push a new order status"""
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
        """Websocket will push a new order status"""
        pass

    def on_cancel_order_error(
            self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when cancelling order failed on server.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)
