# encoding: UTF-8
"""
币安交易接口
"""

from __future__ import print_function
import re
import urllib
import json
import hashlib
import hmac
from copy import copy

from time import time

from datetime import datetime, date

from vnpy.event import Event
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
from vnpy.trader.gateway import BaseGateway, LocalOrderManager
from vnpy.trader.object import (
    TickData,
    OrderData,
    BarData,
    TradeData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)
from vnpy.trader.event import EVENT_TIMER

REST_HOST = 'https://api.binance.com'
WEBSOCKET_DATA_HOST = "wss://stream.binance.com:9443/stream?streams="  # Market Data
WEBSOCKET_TRADE_HOST = "wss://stream.binance.com:9443/ws/"

STATUS_BINANCE2VT = {
    "NEW": Status.NOTTRADED,
    "PARTIALLY_FILLED": Status.PARTTRADED,
    "FILLED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
    "REJECTED": Status.CANCELLED,
    "EXPIRED": Status.CANCELLED,
}

ORDERTYPE_VT2BINANCE = {
    OrderType.LIMIT: "LIMIT",
    OrderType.MARKET: "MARKET",
}

TIME_VT2BINANCE = {
    OrderType.FAK: "IOC",
    OrderType.FOK: "FOK",
    OrderType.GTC: "GTC"
}

SIDE_VT2BINANCE = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL",
}

INTERVAL_VT2BINANCE = {
    Interval.MINUTE: "1m",
    Interval.HOUR: "1h",
    Interval.DAILY: "1d"
}

ORDERTYPE_BINANCE2VT = {
    "LIMIT": OrderType.LIMIT,
    "MARKET": OrderType.MARKET,
    "STOP_LOSS": OrderType.STOP,
    "STOP_LOSS_LIMIT": OrderType.STOP,
    "TAKE_PROFIT": OrderType.STOP,
    "TAKE_PROFIT_LIMIT": OrderType.STOP,
    "LIMIT_MAKER": OrderType.LIMIT
}

SIDE_BINANCE2VT = {v: k for k, v in SIDE_VT2BINANCE.items()}

binance_symbols = set()
symbol_name_map = {}


class BinanceGateway(BaseGateway):
    """
    VN Trader Gateway for Binance connection
    """

    default_setting = {
        "API Key": "",
        "Secret Key": "",
        "会话数": 3,
        "代理地址": "",
        "代理端口": "",
    }

    exchanges = [Exchange.BINANCE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "BINANCE")

        self.order_manager = LocalOrderManager(self)

        self.rest_api = BinanceRestApi(self)
        self.trade_ws_api = None
        self.market_ws_api = {}

        self.listen_key = None

        self.proxy_host = ""
        self.proxy_port = 0

    def connect(self, setting: dict):
        """"""
        key = setting["API Key"]
        secret = setting["Secret Key"]
        session_number = setting["会话数"]
        self.proxy_host = setting["代理地址"]
        self.proxy_port = setting["代理端口"]

        if self.proxy_port.isdigit():
            self.proxy_port = int(self.proxy_port)
        else:
            self.proxy_port = 0

        self.rest_api.connect(key, secret, session_number,
                              self.proxy_host, self.proxy_port)
        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        if req.symbol in self.market_ws_api:
            return

        self.market_ws_api[req.symbol] = BinanceDataWebsocketApi(self, self.proxy_host, self.proxy_port)
        self.market_ws_api[req.symbol].subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self):
        """"""
        self.rest_api.query_account()

    def query_position(self):
        """"""
        pass

    def query_history(self, req: HistoryRequest):
        """"""
        return self.rest_api.query_history(req)

    def close(self):
        """"""
        self.rest_api.stop()
        if self.trade_ws_api:
            self.trade_ws_api.stop()
        for k in list(self.market_ws_api.keys()):
            self.market_ws_api[k].stop()
            del self.market_ws_api[k]

    def process_timer_event(self, event: Event):
        """"""
        self.count += 1
        if self.count < 3:
            return

        if self.count % 60 == 0:
            self.rest_api.ping()
        if self.count % 3000 == 0:
            self.rest_api.touch_listen_key()

    def on_listen_key(self, key: str):
        if not key:
            return
        self.listen_key = key
        if self.trade_ws_api:
            self.trade_ws_api.close()
        self.trade_ws_api = BinanceTradeWebsocketApi(self)
        self.trade_ws_api.connect(self.listen_key, self.proxy_host, self.proxy_port)

    def init_query(self):
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class BinanceRestApi(RestClient):
    """
    BINANCE REST API
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
        self.listen_key = None
        self.no_sign = {"/api/v1/ping", "/api/v1/exchangeInfo", "/api/v1/klines", "/api/v1/userDataStream"}
        self.no_sign_but_api_key = {"/api/v1/userDataStream"}
        self.recv_window = 5000
        self.candles_batch_size = 1000

    def sign(self, request):
        """
        Generate BINANCE signature.
        """
        request.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36"
        }
        if request.path not in self.no_sign:
            sorted_params = [
                ("recvWindow", self.recv_window),
                ("timestamp", int(time() * 1000))
            ]

            if request.params:
                sorted_params.extend(list(request.params.items()))
                sorted_params = list(sorted(sorted_params))
            query = urllib.parse.urlencode(sorted_params)
            signature = hmac.new(self.secret.encode('utf-8'), query.encode('utf-8'), hashlib.sha256).hexdigest()

            params_with_signature = dict(sorted_params)
            params_with_signature["signature"] = signature

            request.params = params_with_signature
            request.headers['X-MBX-APIKEY'] = self.key
        elif request.path in self.no_sign_but_api_key:
            request.headers['X-MBX-APIKEY'] = self.key

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
        self.query_listen_key()

    def ping(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v1/ping",
            callback=self.on_ping
        )

    def query_account(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v3/account",
            callback=self.on_query_account
        )

    def query_listen_key(self):
        """"""
        self.add_request(
            method="POST",
            path="/api/v1/userDataStream",
            callback=self.on_listen_key,
        )

    def touch_listen_key(self):
        if not self.listen_key:
            return
        params = {
            "listenKey": self.listen_key
        }
        self.add_request(
            method="PUT",
            path="/api/v1/userDataStream",
            callback=self.on_touch_listen_key,
            params=params
        )

    def query_order(self, symbol=''):
        """"""
        params = {}
        if symbol:
            params['symbol'] = symbol
        self.add_request(
            method="GET",
            path="/api/v3/openOrders",
            callback=self.on_query_order,
            params=params
        )

    def query_contract(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v1/exchangeInfo",
            callback=self.on_exchange_info
        )

    def query_history(self, req: HistoryRequest):
        """"""
        # Huobi restful API doesn't support time specifying. Maximum 2000
        f = int(date_to_timestamp(req.start))
        if f < 1501574400:  # 2017年8月1日TuesdayAM8点00分
            f = 1501574400
        t = int(date_to_timestamp(req.end))
        interval_in_seconds = interval_to_seconds(req.interval)
        max_time_span = interval_in_seconds * self.candles_batch_size

        end = f + max_time_span
        if end > t:
            end = t
        history = []
        loop = 1

        while end <= t:
            self.gateway.write_log(f"下载第{loop}回合数据。")
            params = {
                "symbol": req.symbol,
                "interval": INTERVAL_VT2BINANCE[req.interval],
                "limit": self.candles_batch_size,
                "startTime": str(f * 1000),
                "endTime": str(end * 1000)
            }
            resp = self.request(
                method="GET",
                path="/api/v1/klines",
                params=params
            )

            if resp.status_code // 100 != 2:
                msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
                self.gateway.write_log(msg)
            else:
                data = resp.json()
                if not data:
                    msg = f"获取历史数据为空"
                    self.gateway.write_log(msg)
                else:
                    for d in data:
                        dt = datetime.fromtimestamp(d[0] / 1000)

                        bar = BarData(
                            symbol=req.symbol,
                            exchange=req.exchange,
                            datetime=dt,
                            interval=req.interval,
                            volume=float(d[5]),
                            open_price=float(d[1]),
                            high_price=float(d[2]),
                            low_price=float(d[3]),
                            close_price=float(d[4]),
                            gateway_name=self.gateway_name
                        )
                        history.append(bar)
            loop = loop + 1
            if end == t or loop > 20:
                break
            f = end + interval_in_seconds
            end = f + max_time_span
            if end > t:
                end = t
        begin = history[0].datetime
        end = history[-1].datetime
        msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
        self.gateway.write_log(msg)

        return history

    def send_order(self, req: OrderRequest):
        """"""
        local_orderid = self.order_manager.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.time = datetime.now().strftime("%H:%M:%S")

        params = {
            "symbol": req.symbol,
            "type": ORDERTYPE_VT2BINANCE[req.type],
            "side": SIDE_VT2BINANCE[req.direction],
            "price": str(req.price),
            "quantity": str(req.volume),
            "timeInForce": "GTC",
            "newClientOrderId": local_orderid
        }

        self.add_request(
            method="POST",
            path="/api/v3/order",
            callback=self.on_send_order,
            extra=order,
            params=params,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        self.order_manager.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)

        params = {
            "symbol": req.symbol,
            "orderId": sys_orderid
        }
        path = f"/api/v3/order"
        self.add_request(
            method="DELETE",
            path=path,
            callback=self.on_cancel_order,
            params=params,
            extra=req
        )

    def on_listen_key(self, data, request):
        """"""
        self.listen_key = data["listenKey"]
        self.gateway.on_listen_key(self.listen_key)

    def on_touch_listen_key(self, data, request):
        """ You have to do nothing. """
        pass

    def on_query_account(self, data, request):
        """"""
        for d in data["balances"]:
            account = AccountData(
                accountid=d["asset"],
                balance=float(d["free"]) + float(d["locked"]),
                frozen=float(d["locked"]),
                gateway_name=self.gateway_name,
            )

            if account.balance:
                self.gateway.on_account(account)

    def on_query_order(self, data, request):
        """"""
        for d in data:
            sys_orderid = str(d["orderId"])
            local_orderid = str(d["clientOrderId"])

            order_type = ORDERTYPE_BINANCE2VT[d["type"]]
            direction = SIDE_BINANCE2VT[d["side"]]
            dt = datetime.fromtimestamp(d["time"] / 1000)
            time = dt.strftime("%H:%M:%S")

            order = OrderData(
                orderid=local_orderid,
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                price=float(d["price"]),
                volume=float(d["origQty"]),
                type=order_type,
                direction=direction,
                traded=float(d["executedQty"]),
                status=STATUS_BINANCE2VT.get(d["status"], None),
                time=time,
                gateway_name=self.gateway_name,
            )

            self.order_manager.on_order(order)
            self.order_manager.update_orderid_map(local_orderid, sys_orderid)
            self.order_manager.set_order_count(int(local_orderid))

        self.gateway.write_log("委托信息查询成功")

    def on_exchange_info(self, data, request):  # type: (dict, Request)->None
        """"""
        for d in data["symbols"]:
            base_currency = d["baseAsset"]
            quote_currency = d["quoteAsset"]
            name = f"{base_currency.upper()}/{quote_currency.upper()}"
            pricetick = 1 / pow(10, d["quotePrecision"])
            min_volume = 1 / pow(10, d["baseAssetPrecision"])

            contract = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                name=name,
                pricetick=pricetick,
                size=1,
                min_volume=min_volume,
                product=Product.SPOT,
                gateway_name=self.gateway_name,
                history_data=True,
            )
            self.gateway.on_contract(contract)

            binance_symbols.add(contract.symbol)
            symbol_name_map[contract.symbol] = contract.name

        self.gateway.write_log("合约信息查询成功")

    def on_send_order(self, data, request):
        """"""
        order = request.extra

        if "orderId" not in data:
            order.status = Status.REJECTED
            self.order_manager.on_order(order)
            return
        sys_orderid = str(data["orderId"])

        self.order_manager.update_orderid_map(order.orderid, sys_orderid)
        order.status = STATUS_BINANCE2VT[data["status"]]
        self.order_manager.on_order(order)

    def on_ping(self, data, request):
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
        cancel_request = request.extra
        local_orderid = cancel_request.orderid
        order = self.order_manager.get_order_with_local_orderid(local_orderid)

        order.status = STATUS_BINANCE2VT[data["status"]]
        if order.status == Status.CANCELLED:
            self.gateway.write_log(f"委托撤单成功：{order.orderid}")
            self.query_account()

        self.order_manager.on_order(order)

    def check_error(self, data: dict, func: str = ""):
        """"""
        if data["status"] != "error":
            return False

        error_code = data["err-code"]
        error_msg = data["err-msg"]

        self.gateway.write_log(f"{func}请求出错，代码：{error_code}，信息：{error_msg}")
        return True


class BinanceWebsocketApiBase(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""

    def connect(self, key: str, url: str, proxy_host: str, proxy_port: int):
        """"""
        self.key = key

        self.init(url, proxy_host, proxy_port)
        self.start()

    def on_packet(self, packet):
        """"""
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


class BinanceTradeWebsocketApi(BinanceWebsocketApiBase):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.order_manager = gateway.order_manager
        self.order_manager.push_data_callback = self.on_data

        self.req_id = 0

    def connect(self, key, proxy_host, proxy_port):
        """"""
        super().connect(key, WEBSOCKET_TRADE_HOST + key, proxy_host, proxy_port)

    def on_connected(self):
        """"""
        self.gateway.write_log("交易Websocket API连接成功")

    def on_data(self, packet):  # type: (dict)->None
        """"""
        op = packet.get("e", None)
        if op == "outboundAccountInfo":
            self.on_account(packet)
        elif op == "executionReport":
            self.on_order(packet)

    def on_account(self, data: dict):
        for d in data['B']:
            account = AccountData(
                accountid=d["a"],
                balance=float(d["f"]) + float(d["l"]),
                frozen=float(d["l"]),
                gateway_name=self.gateway_name,
            )

            if account.balance:
                self.gateway.on_account(account)

    def on_order(self, data: dict):
        """"""
        sys_orderid = str(data["i"])

        order = self.order_manager.get_order_with_sys_orderid(sys_orderid)
        if not order:
            self.order_manager.add_push_data(sys_orderid, data)
            return

        traded_volume = float(data["z"])
        last_traded_volume = float(data["l"])

        # Push order event
        order.traded = traded_volume
        order.status = STATUS_BINANCE2VT.get(data["X"], None)
        self.order_manager.on_order(order)

        # Push trade event
        if not last_traded_volume:
            return

        trade = TradeData(
            symbol=order.symbol,
            exchange=Exchange.BINANCE,
            orderid=order.orderid,
            tradeid=str(data["t"]),
            direction=order.direction,
            price=float(data["L"]),
            volume=last_traded_volume,
            time=datetime.fromtimestamp(data["T"] / 1000).strftime("%H:%M:%S"),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_trade(trade)


class BinanceDataWebsocketApi(BinanceWebsocketApiBase):
    """"""

    def __init__(self, gateway, proxy_host: str, proxy_port: int):
        """"""
        super().__init__(gateway)

        self.req_id = 0
        self.ticks = {}
        self.url = None
        self.proxy_host = proxy_host
        self.proxy_port = proxy_port
        self.symbol = ""

    def on_connected(self):
        """"""
        self.gateway.write_log(f"币安{self.symbol}行情Websocket连接成功")

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.symbol = req.symbol
        s = self.symbol.lower() + "@miniTicker"
        self.url = WEBSOCKET_DATA_HOST + s
        super().connect("", self.url, self.proxy_host, self.proxy_port)

        tick = TickData(
            symbol=self.symbol,
            name=symbol_name_map.get(self.symbol, ""),
            exchange=Exchange.BINANCE,
            datetime=datetime.now(),
            gateway_name=self.gateway_name,
        )
        self.ticks[self.symbol] = tick

    def on_data(self, packet):  # type: (dict)->None
        """"""
        if packet["stream"].endswith("@miniTicker"):
            self.on_market_detail(packet["data"])

    def on_market_depth(self, data):
        """行情深度推送 """
        pass

    def on_market_detail(self, data):
        """市场细节推送"""
        if "24hrMiniTicker" != data["e"]:
            return

        symbol = data["s"]
        tick = self.ticks[symbol]
        tick.datetime = datetime.fromtimestamp(data["E"] / 1000)
        tick.last_price = float(data["c"])
        tick.volume = float(data["v"])
        tick.open_price = float(data["o"])
        tick.high_price = float(data["h"])
        tick.low_price = float(data["l"])

        self.gateway.on_tick(copy(tick))


def _split_url(url):
    """
    将url拆分为host和path
    :return: host, path
    """
    result = re.match("\w+://([^/]*)(.*)", url)  # noqa
    if result:
        return result.group(1), result.group(2)


def date_to_timestamp(d: date):
    """"""
    dt = datetime.combine(d, datetime.min.time())
    return dt.timestamp()


def interval_to_seconds(i: Interval):
    if i == Interval.MINUTE:
        return 60
    if i == Interval.HOUR:
        return 60 * 60
    if i == Interval.DAILY:
        return 60 * 60 * 24
    if i == Interval.WEEKLY:
        return 60 * 60 * 24 * 7
    return 0
