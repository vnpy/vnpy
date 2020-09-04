"""
火币交易接口
"""

import re
import urllib
import base64
import json
import zlib
import hashlib
import hmac
import sys
from copy import copy
from datetime import datetime
import pytz
from typing import Dict, List, Any

from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
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
    TradeData,
    AccountData,
    ContractData,
    BarData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)


REST_HOST = "https://api.huobipro.com"
WEBSOCKET_DATA_HOST = "wss://api.huobi.pro/ws"       # Market Data
WEBSOCKET_TRADE_HOST = "wss://api.huobi.pro/ws/v2"     # Account and Order

STATUS_HUOBI2VT = {
    "submitted": Status.NOTTRADED,
    "partial-filled": Status.PARTTRADED,
    "filled": Status.ALLTRADED,
    "cancelling": Status.CANCELLED,
    "partial-canceled": Status.CANCELLED,
    "canceled": Status.CANCELLED,
}

ORDERTYPE_VT2HUOBI = {
    (Direction.LONG, OrderType.MARKET): "buy-market",
    (Direction.SHORT, OrderType.MARKET): "sell-market",
    (Direction.LONG, OrderType.LIMIT): "buy-limit",
    (Direction.SHORT, OrderType.LIMIT): "sell-limit",
}
ORDERTYPE_HUOBI2VT = {v: k for k, v in ORDERTYPE_VT2HUOBI.items()}

INTERVAL_VT2HUOBI = {
    Interval.MINUTE: "1min",
    Interval.HOUR: "60min",
    Interval.DAILY: "1day"
}

CHINA_TZ = pytz.timezone("Asia/Shanghai")

huobi_symbols: set = set()
symbol_name_map: Dict[str, str] = {}
currency_balance: Dict[str, float] = {}


class HuobiGateway(BaseGateway):
    """
    VN Trader Gateway for Huobi connection.
    """

    default_setting: Dict[str, Any] = {
        "API Key": "",
        "Secret Key": "",
        "会话数": 3,
        "代理地址": "",
        "代理端口": "",
    }

    exchanges: List[Exchange] = [Exchange.HUOBI]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "HUOBI")

        self.rest_api = HuobiRestApi(self)
        self.trade_ws_api = HuobiTradeWebsocketApi(self)
        self.market_ws_api = HuobiDataWebsocketApi(self)

        self.orders: Dict[str, OrderData] = {}

    def get_order(self, orderid: str) -> OrderData:
        """"""
        return self.orders.get(orderid, None)

    def on_order(self, order: OrderData) -> None:
        """"""
        self.orders[order.orderid] = order
        super().on_order(order)

    def connect(self, setting: dict) -> None:
        """"""
        key = setting["API Key"]
        secret = setting["Secret Key"]
        session_number = setting["会话数"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.rest_api.connect(key, secret, session_number,
                              proxy_host, proxy_port)
        self.trade_ws_api.connect(key, secret, proxy_host, proxy_port)
        self.market_ws_api.connect(key, secret, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.market_ws_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        pass

    def query_position(self) -> None:
        """"""
        pass

    def query_history(self, req: HistoryRequest):
        """"""
        return self.rest_api.query_history(req)

    def close(self) -> None:
        """"""
        self.rest_api.stop()
        self.trade_ws_api.stop()
        self.market_ws_api.stop()


class HuobiRestApi(RestClient):
    """
    HUOBI REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway: HuobiGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.host: str = ""
        self.key: str = ""
        self.secret: str = ""
        self.account_id: str = ""

        self.order_count = 0

    def new_orderid(self):
        """"""
        prefix = datetime.now().strftime("%Y%m%d-%H%M%S-")

        self.order_count += 1
        suffix = str(self.order_count).rjust(8, "0")

        orderid = prefix + suffix
        return orderid

    def sign(self, request: Request) -> Request:
        """
        Generate HUOBI signature.
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
        proxy_port: int
    ) -> None:
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret

        self.host, _ = _split_url(REST_HOST)

        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

        self.query_contract()
        self.query_account()
        self.query_order()

    def query_account(self) -> None:
        """"""
        self.add_request(
            method="GET",
            path="/v1/account/accounts",
            callback=self.on_query_account
        )

    def query_order(self) -> None:
        """"""
        self.add_request(
            method="GET",
            path="/v1/order/openOrders",
            callback=self.on_query_order
        )

    def query_contract(self) -> None:
        """"""
        self.add_request(
            method="GET",
            path="/v1/common/symbols",
            callback=self.on_query_contract
        )

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """"""
        # Create query params
        params = {
            "symbol": req.symbol,
            "period": INTERVAL_VT2HUOBI[req.interval],
            "size": 2000
        }

        # Get response from server
        resp = self.request(
            "GET",
            "/market/history/kline",
            params=params
        )

        # Break if request failed with other status code
        history = []

        if resp.status_code // 100 != 2:
            msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
            self.gateway.write_log(msg)
        else:
            data = resp.json()
            if not data:
                msg = f"获取历史数据为空"
                self.gateway.write_log(msg)
            else:
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
                    history.append(bar)

                begin = history[0].datetime
                end = history[-1].datetime
                msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
                self.gateway.write_log(msg)

        return history

    def send_order(self, req: OrderRequest) -> str:
        """"""
        huobi_type = ORDERTYPE_VT2HUOBI.get(
            (req.direction, req.type), ""
        )

        orderid = self.new_orderid()
        order = req.create_order_data(orderid, self.gateway_name)
        order.datetime = datetime.now(CHINA_TZ)

        data = {
            "account-id": self.account_id,
            "amount": str(req.volume),
            "symbol": req.symbol,
            "type": huobi_type,
            "price": str(req.price),
            "source": "api",
            "client-order-id": orderid
        }

        self.add_request(
            method="POST",
            path="/v1/order/orders/place",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        data = {"client-order-id": req.orderid}

        self.add_request(
            method="POST",
            path="/v1/order/orders/submitCancelClientOrder",
            data=data,
            callback=self.on_cancel_order,
            extra=req
        )

    def on_query_account(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询账户"):
            return

        for d in data["data"]:
            if d["type"] == "spot":
                self.account_id = d["id"]
                self.gateway.write_log(f"账户代码{self.account_id}查询成功")

    def on_query_order(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询委托"):
            return

        for d in data["data"]:
            direction, order_type = ORDERTYPE_HUOBI2VT[d["type"]]
            dt = generate_datetime(d["created-at"] / 1000)

            order = OrderData(
                orderid=d["client-order-id"],
                symbol=d["symbol"],
                exchange=Exchange.HUOBI,
                price=float(d["price"]),
                volume=float(d["amount"]),
                type=order_type,
                direction=direction,
                traded=float(d["filled-amount"]),
                status=STATUS_HUOBI2VT.get(d["state"], None),
                datetime=dt,
                gateway_name=self.gateway_name,
            )

            self.gateway.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def on_query_contract(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询合约"):
            return

        for d in data["data"]:
            base_currency = d["base-currency"]
            quote_currency = d["quote-currency"]
            name = f"{base_currency.upper()}/{quote_currency.upper()}"
            pricetick = 1 / pow(10, d["price-precision"])
            min_volume = 1 / pow(10, d["amount-precision"])

            contract = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.HUOBI,
                name=name,
                pricetick=pricetick,
                size=1,
                min_volume=min_volume,
                product=Product.SPOT,
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

            huobi_symbols.add(contract.symbol)
            symbol_name_map[contract.symbol] = contract.name

        self.gateway.write_log("合约信息查询成功")

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

    def on_cancel_order(self, data: dict, request: Request) -> None:
        """"""
        cancel_request = request.extra
        order = self.gateway.get_order(cancel_request.orderid)
        if not order:
            return

        if self.check_error(data, "撤单"):
            order.status = Status.REJECTED
        else:
            order.status = Status.CANCELLED
            self.gateway.write_log(f"委托撤单成功：{order.orderid}")

        self.gateway.on_order(order)

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

        error_code = data["err-code"]
        error_msg = data["err-msg"]

        self.gateway.write_log(f"{func}请求出错，代码：{error_code}，信息：{error_msg}")
        return True


class HuobiWebsocketApiBase(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__()

        self.gateway: HuobiGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.key: str = ""
        self.secret: str = ""
        self.sign_host: str = ""
        self.path: str = ""

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
        params = create_signature_v2(
            self.key,
            "GET",
            self.sign_host,
            self.path,
            self.secret
        )

        req = {
            "action": "req",
            "ch": "auth",
            "params": params
        }

        return self.send_packet(req)

    def on_login(self, packet: dict) -> None:
        """"""
        pass

    @staticmethod
    def unpack_data(data):
        """"""
        if isinstance(data, bytes):
            buf = zlib.decompress(data, 31)
        else:
            buf = data

        return json.loads(buf)

    def on_packet(self, packet: dict):
        """"""
        # print("on packet", packet)
        if "ping" in packet:
            req = {"pong": packet["ping"]}
            self.send_packet(req)
        elif "action" in packet and packet["action"] == "ping":
            req = {
                "action": "pong",
                "ts": packet["data"]["ts"]
            }
            self.send_packet(req)
        elif "err-msg" in packet:
            return self.on_error_msg(packet)
        elif "action" in packet and packet["action"] == "req":
            return self.on_login(packet)
        else:
            self.on_data(packet)

    def on_data(self, packet: dict) -> None:
        """"""
        print("data : {}".format(packet))

    def on_error_msg(self, packet: dict) -> None:
        """"""
        msg = packet["err-msg"]
        if msg == "invalid pong":
            return

        self.gateway.write_log(packet["err-msg"])


class HuobiTradeWebsocketApi(HuobiWebsocketApiBase):
    """"""
    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.req_id: int = 0

    def connect(
        self,
        key: str,
        secret: str,
        proxy_host: str,
        proxy_port: int
    ):
        """"""
        super().connect(
            key,
            secret,
            WEBSOCKET_TRADE_HOST,
            proxy_host,
            proxy_port
        )

    def subscribe_order_update(self) -> None:
        """"""
        self.req_id += 1
        req = {
            "action": "sub",
            "ch": f"orders#*"
        }
        self.send_packet(req)

    def subscribe_account_update(self) -> None:
        """"""
        req = {
            "action": "sub",
            "ch": "accounts.update#1"
        }
        self.send_packet(req)

    def on_connected(self) -> None:
        """"""
        self.gateway.write_log("交易Websocket API连接成功")
        self.login()

    def on_login(self, packet: dict) -> None:
        """"""
        if "data" in packet and not packet["data"]:
            self.gateway.write_log("交易Websocket API登录成功")

            self.subscribe_order_update()
            self.subscribe_account_update()
        else:
            msg = packet["message"]
            error_msg = f"交易Websocket API登录失败，原因：{msg}"
            self.gateway.write_log(error_msg)

    def on_data(self, packet: dict) -> None:
        """"""
        if "sub" in packet["action"]:
            return

        ch = packet["ch"]
        if "orders" in ch:
            self.on_order(packet["data"])
        elif "accounts" in ch:
            self.on_account(packet["data"])

    def on_account(self, data: dict) -> None:
        """"""
        if not data:
            return

        currency = data["currency"]

        change_type = data["changeType"]
        if not change_type:
            balance = float(data["balance"])
            frozen = balance - float(data["available"])
            currency_balance[currency] = balance

        elif "place" in change_type:
            if "available" not in data:
                return
            balance = currency_balance[currency]
            frozen = balance - float(data["available"])
        else:
            frozen = 0.0
            if "balance" in data:
                balance = float(data["balance"])
            else:
                balance = float(data["available"])
            currency_balance[currency] = balance

        account = AccountData(
            accountid=currency,
            balance=balance,
            frozen=frozen,
            gateway_name=self.gateway_name,
        )
        self.gateway.on_account(account)

    def on_order(self, data: dict) -> None:
        """"""
        orderid = data["clientOrderId"]
        order = self.gateway.get_order(orderid)
        if not order:
            return

        traded_volume = float(data.get("tradeVolume", 0))

        # Push order event
        order.traded += traded_volume
        order.status = STATUS_HUOBI2VT.get(data["orderStatus"], None)
        self.gateway.on_order(order)

        # Push trade event
        if not traded_volume:
            return

        trade = TradeData(
            symbol=order.symbol,
            exchange=Exchange.HUOBI,
            orderid=order.orderid,
            tradeid=str(data["tradeId"]),
            direction=order.direction,
            price=float(data["tradePrice"]),
            volume=float(data["tradeVolume"]),
            datetime=datetime.now(CHINA_TZ),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_trade(trade)


class HuobiDataWebsocketApi(HuobiWebsocketApiBase):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.req_id: int = 0
        self.ticks: Dict[str, TickData] = {}

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

        for symbol in self.ticks.keys():
            self.subscribe_by_symbol(symbol)

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        symbol = req.symbol
        self.subscribe_by_symbol(symbol)

    def subscribe_by_symbol(self, symbol: str) -> None:
        """"""
        # Create tick data buffer
        tick = TickData(
            symbol=symbol,
            name=symbol_name_map.get(symbol, ""),
            exchange=Exchange.HUOBI,
            datetime=datetime.now(CHINA_TZ),
            gateway_name=self.gateway_name,
        )
        self.ticks[symbol] = tick

        # Subscribe to market depth update
        self.req_id += 1
        req = {
            "sub": f"market.{symbol}.depth.step0",
            "id": str(self.req_id)
        }
        self.send_packet(req)

        # Subscribe to market detail update
        self.req_id += 1
        req = {
            "sub": f"market.{symbol}.detail",
            "id": str(self.req_id)
        }
        self.send_packet(req)

    def on_data(self, packet: dict) -> None:
        """"""
        channel = packet.get("ch", None)
        if channel:
            if "depth.step" in channel:
                self.on_market_depth(packet)
            elif "detail" in channel:
                self.on_market_detail(packet)
        elif "err-code" in packet:
            code = packet["err-code"]
            msg = packet["err-msg"]
            self.gateway.write_log(f"错误代码：{code}, 错误信息：{msg}")

    def on_market_depth(self, data: dict) -> None:
        """行情深度推送 """
        symbol = data["ch"].split(".")[1]
        tick = self.ticks[symbol]
        tick.datetime = generate_datetime(data["ts"] / 1000)

        bids = data["tick"]["bids"]
        for n in range(5):
            price, volume = bids[n]
            tick.__setattr__("bid_price_" + str(n + 1), float(price))
            tick.__setattr__("bid_volume_" + str(n + 1), float(volume))

        asks = data["tick"]["asks"]
        for n in range(5):
            price, volume = asks[n]
            tick.__setattr__("ask_price_" + str(n + 1), float(price))
            tick.__setattr__("ask_volume_" + str(n + 1), float(volume))

        if tick.last_price:
            self.gateway.on_tick(copy(tick))

    def on_market_detail(self, data: dict) -> None:
        """市场细节推送"""
        symbol = data["ch"].split(".")[1]
        tick = self.ticks[symbol]
        tick.datetime = generate_datetime(data["ts"] / 1000)

        tick_data = data["tick"]
        tick.open_price = float(tick_data["open"])
        tick.high_price = float(tick_data["high"])
        tick.low_price = float(tick_data["low"])
        tick.last_price = float(tick_data["close"])
        tick.volume = float(tick_data["vol"])

        if tick.bid_price_1:
            self.gateway.on_tick(copy(tick))


def _split_url(url):
    """
    将url拆分为host和path
    :return: host, path
    """
    result = re.match("\w+://([^/]*)(.*)", url)  # noqa
    if result:
        return result.group(1), result.group(2)


def create_signature(
    api_key,
    method,
    host,
    path,
    secret_key,
    get_params=None
) -> Dict[str, str]:
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


def create_signature_v2(
    api_key,
    method,
    host,
    path,
    secret_key,
    get_params=None
) -> Dict[str, str]:
    """
    创建签名
    :param get_params: dict 使用GET方法时附带的额外参数(urlparams)
    :return:
    """
    sorted_params = [
        ("accessKey", api_key),
        ("signatureMethod", "HmacSHA256"),
        ("signatureVersion", "2.1"),
        ("timestamp", datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S"))
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
    params["authType"] = "api"
    params["signature"] = signature.decode("UTF8")
    return params


def generate_datetime(timestamp: float) -> datetime:
    """"""
    dt = datetime.fromtimestamp(timestamp)
    dt = CHINA_TZ.localize(dt)
    return dt
