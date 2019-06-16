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
from copy import copy
from datetime import datetime

from vnpy.event import Event
from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Product,
    Status,
    OrderType
)
from vnpy.trader.gateway import BaseGateway, LocalOrderManager
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest
)
from vnpy.trader.event import EVENT_TIMER


REST_HOST = "https://api.huobipro.com"
WEBSOCKET_DATA_HOST = "wss://api.huobi.pro/ws"       # Market Data
WEBSOCKET_TRADE_HOST = "wss://api.huobi.pro/ws/v1"     # Account and Order

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


huobi_symbols = set()
symbol_name_map = {}


class HuobiGateway(BaseGateway):
    """
    VN Trader Gateway for Huobi connection.
    """

    default_setting = {
        "API Key": "",
        "Secret Key": "",
        "会话数": 3,
        "代理地址": "",
        "代理端口": "",
    }

    exchanges = [Exchange.HUOBI]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "HUOBI")

        self.order_manager = LocalOrderManager(self)

        self.rest_api = HuobiRestApi(self)
        self.trade_ws_api = HuobiTradeWebsocketApi(self)
        self.market_ws_api = HuobiDataWebsocketApi(self)

    def connect(self, setting: dict):
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

        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.market_ws_api.subscribe(req)
        self.trade_ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self):
        """"""
        self.rest_api.query_account_balance()

    def query_position(self):
        """"""
        pass

    def close(self):
        """"""
        self.rest_api.stop()
        self.trade_ws_api.stop()
        self.market_ws_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        self.count += 1
        if self.count < 3:
            return

        self.query_account()

    def init_query(self):
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class HuobiRestApi(RestClient):
    """
    HUOBI REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.host = ""
        self.key = ""
        self.secret = ""
        self.account_id = ""

    def sign(self, request):
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
    ):
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

    def query_account(self):
        """"""
        self.add_request(
            method="GET",
            path="/v1/account/accounts",
            callback=self.on_query_account
        )

    def query_account_balance(self):
        """"""
        path = f"/v1/account/accounts/{self.account_id}/balance"
        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_account_balance
        )

    def query_order(self):
        """"""
        self.add_request(
            method="GET",
            path="/v1/order/openOrders",
            callback=self.on_query_order
        )

    def query_contract(self):
        """"""
        self.add_request(
            method="GET",
            path="/v1/common/symbols",
            callback=self.on_query_contract
        )

    def send_order(self, req: OrderRequest):
        """"""
        huobi_type = ORDERTYPE_VT2HUOBI.get(
            (req.direction, req.type), ""
        )

        local_orderid = self.order_manager.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.time = datetime.now().strftime("%H:%M:%S")

        data = {
            "account-id": self.account_id,
            "amount": str(req.volume),
            "symbol": req.symbol,
            "type": huobi_type,
            "price": str(req.price),
            "source": "api"
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

        self.order_manager.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)

        path = f"/v1/order/orders/{sys_orderid}/submitcancel"
        self.add_request(
            method="POST",
            path=path,
            callback=self.on_cancel_order,
            extra=req
        )

    def on_query_account(self, data, request):
        """"""
        if self.check_error(data, "查询账户"):
            return

        for d in data["data"]:
            if d["type"] == "spot":
                self.account_id = d["id"]
                self.gateway.write_log(f"账户代码{self.account_id}查询成功")

        self.query_account_balance()

    def on_query_account_balance(self, data, request):
        """"""
        if self.check_error(data, "查询账户资金"):
            return

        buf = {}
        for d in data["data"]["list"]:
            currency = d["currency"]
            currency_data = buf.setdefault(currency, {})
            currency_data[d["type"]] = float(d["balance"])

        for currency, currency_data in buf.items():
            account = AccountData(
                accountid=currency,
                balance=currency_data["trade"] + currency_data["frozen"],
                frozen=currency_data["frozen"],
                gateway_name=self.gateway_name,
            )

            if account.balance:
                self.gateway.on_account(account)

    def on_query_order(self, data, request):
        """"""
        if self.check_error(data, "查询委托"):
            return

        for d in data["data"]:
            sys_orderid = d["id"]
            local_orderid = self.order_manager.get_local_orderid(sys_orderid)

            direction, order_type = ORDERTYPE_HUOBI2VT[d["type"]]
            dt = datetime.fromtimestamp(d["created-at"] / 1000)
            time = dt.strftime("%H:%M:%S")

            order = OrderData(
                orderid=local_orderid,
                symbol=d["symbol"],
                exchange=Exchange.HUOBI,
                price=float(d["price"]),
                volume=float(d["amount"]),
                type=order_type,
                direction=direction,
                traded=float(d["filled-amount"]),
                status=STATUS_HUOBI2VT.get(d["state"], None),
                time=time,
                gateway_name=self.gateway_name,
            )

            self.order_manager.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def on_query_contract(self, data, request):  # type: (dict, Request)->None
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
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

            huobi_symbols.add(contract.symbol)
            symbol_name_map[contract.symbol] = contract.name

        self.gateway.write_log("合约信息查询成功")

    def on_send_order(self, data, request):
        """"""
        order = request.extra

        if self.check_error(data, "委托"):
            order.status = Status.REJECTED
            self.order_manager.on_order(order)
            return

        sys_orderid = data["data"]
        self.order_manager.update_orderid_map(order.orderid, sys_orderid)

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
        cancel_request = request.extra
        local_orderid = cancel_request.orderid
        order = self.order_manager.get_order_with_local_orderid(local_orderid)
        
        if self.check_error(data, "撤单"):
            order.status = Status.REJECTED
        else:
            order.status = Status.CANCELLED
            self.gateway.write_log(f"委托撤单成功：{order.orderid}")
        
        self.order_manager.on_order(order)
        
    def check_error(self, data: dict, func: str = ""):
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

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.sign_host = ""
        self.path = ""

    def connect(
        self, 
        key: str, 
        secret: str, 
        url: str, 
        proxy_host: str, 
        proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret
        
        host, path = _split_url(url)
        self.sign_host = host
        self.path = path

        self.init(url, proxy_host, proxy_port)
        self.start()

    def login(self):
        """"""
        params = {"op": "auth"}
        params.update(create_signature(self.key, "GET", self.sign_host, self.path, self.secret))        
        return self.send_packet(params)

    def on_login(self, packet):
        """"""
        pass

    @staticmethod
    def unpack_data(data):
        """"""
        return json.loads(zlib.decompress(data, 31)) 

    def on_packet(self, packet):
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
    
    def on_data(self, packet): 
        """"""
        print("data : {}".format(packet))

    def on_error_msg(self, packet): 
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

        self.order_manager = gateway.order_manager
        self.order_manager.push_data_callback = self.on_data

        self.req_id = 0

    def connect(self, key, secret, proxy_host, proxy_port):
        """"""
        super().connect(key, secret, WEBSOCKET_TRADE_HOST, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.req_id += 1
        req = {
            "op": "sub",
            "cid": str(self.req_id),
            "topic": f"orders.{req.symbol}"
        }
        self.send_packet(req)

    def on_connected(self):
        """"""
        self.gateway.write_log("交易Websocket API连接成功")
        self.login()

    def on_login(self):
        """"""
        self.gateway.write_log("交易Websocket API登录成功")

    def on_data(self, packet):  # type: (dict)->None
        """"""
        op = packet.get("op", None)
        if op != "notify":
            return
        
        topic = packet["topic"]
        if "orders" in topic:
            self.on_order(packet["data"])

    def on_order(self, data: dict):
        """"""
        sys_orderid = str(data["order-id"])
        
        order = self.order_manager.get_order_with_sys_orderid(sys_orderid)
        if not order:
            self.order_manager.add_push_data(sys_orderid, data)
            return
        
        traded_volume = float(data["filled-amount"])

        # Push order event
        order.traded += traded_volume
        order.status = STATUS_HUOBI2VT.get(data["order-state"], None)
        self.order_manager.on_order(order)
        
        # Push trade event
        if not traded_volume:
            return

        trade = TradeData(
            symbol=order.symbol,
            exchange=Exchange.HUOBI,
            orderid=order.orderid,
            tradeid=str(data["seq-id"]),
            direction=order.direction,
            price=float(data["price"]),
            volume=float(data["filled-amount"]),
            time=datetime.now().strftime("%H:%M:%S"),
            gateway_name=self.gateway_name,
        )    
        self.gateway.on_trade(trade)


class HuobiDataWebsocketApi(HuobiWebsocketApiBase):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.req_id = 0
        self.ticks = {}

    def connect(self, key: str, secret: str, proxy_host: str, proxy_port: int):
        """"""
        super().connect(key, secret, WEBSOCKET_DATA_HOST, proxy_host, proxy_port)

    def on_connected(self):
        """"""
        self.gateway.write_log("行情Websocket API连接成功")
        
    def subscribe(self, req: SubscribeRequest):
        """"""
        symbol = req.symbol

        # Create tick data buffer
        tick = TickData(
            symbol=symbol,
            name=symbol_name_map.get(symbol, ""),
            exchange=Exchange.HUOBI,
            datetime=datetime.now(),
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

    def on_data(self, packet):  # type: (dict)->None
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

    def on_market_depth(self, data):
        """行情深度推送 """
        symbol = data["ch"].split(".")[1]
        tick = self.ticks[symbol]
        tick.datetime = datetime.fromtimestamp(data["ts"] / 1000)
        
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

    def on_market_detail(self, data):
        """市场细节推送"""
        symbol = data["ch"].split(".")[1]
        tick = self.ticks[symbol]
        tick.datetime = datetime.fromtimestamp(data["ts"] / 1000)
        
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


def create_signature(api_key, method, host, path, secret_key, get_params=None):
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
