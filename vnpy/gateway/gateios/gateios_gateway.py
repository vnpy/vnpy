"""
Gate.io 期货接口
"""
import hashlib
import hmac
import json
import sys
import time
from copy import copy
from datetime import datetime, timedelta
from urllib.parse import urlencode
from typing import List, Dict
from pytz import utc as UTC_TZ

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.event import Event
from vnpy.trader.constant import (Direction, Exchange, Interval, OrderType,
                                  Product, Status)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway, LocalOrderManager
from vnpy.trader.object import (AccountData, BarData, CancelRequest,
                                ContractData, HistoryRequest, OrderData,
                                OrderRequest, PositionData, SubscribeRequest,
                                TickData, TradeData)


TESTNET_REST_HOST = "https://fx-api-testnet.gateio.ws/"
REST_HOST = "https://api.gateio.ws"

TESTNET_WEBSOCKET_HOST = "wss://fx-ws-testnet.gateio.ws/v4/ws"
WEBSOCKET_HOST = "wss://fx-ws.gateio.ws/v4/ws"

INTERVAL_VT2GATEIO = {
    Interval.MINUTE: "1m",
    Interval.HOUR: "1h",
    Interval.DAILY: "1d",
}

TIMEDELTA_MAP = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}


class GateiosGateway(BaseGateway):
    """
    VN Trader Gateway for Gate.io future connection.
    """

    default_setting = {
        "API Key": "",
        "Secret Key": "",
        "服务器": ["REAL", "TESTNET"],
        "代理地址": "",
        "代理端口": "",
    }

    exchanges = [Exchange.GATEIO]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "GATEIOS")
        self.order_manager = LocalOrderManager(self)

        self.ws_api = GateiosWebsocketApi(self)
        self.rest_api = GateiosRestApi(self)

    def connect(self, setting: Dict):
        """"""
        key = setting["API Key"]
        secret = setting["Secret Key"]
        server = setting["服务器"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.rest_api.connect(key, secret, server, proxy_host, proxy_port)

        self.init_query()

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
        self.rest_api.query_account()

    def query_position(self):
        """"""
        self.rest_api.query_position()

    def query_history(self, req: HistoryRequest):
        """"""
        return self.rest_api.query_history(req)

    def close(self):
        """"""
        self.rest_api.stop()
        self.ws_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        self.query_account()
        self.query_position()

    def init_query(self):
        """"""
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class GateiosRestApi(RestClient):
    """
    Gateios REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager
        self.ws_api = gateway.ws_api

        self.key = ""
        self.secret = ""
        self.account_id = ""
        self.server = ""
        self.proxy_host = ""
        self.proxy_port = 0

        self.symbols = []

    def sign(self, request):
        """
        Generate signature.
        """
        request.headers = generate_sign(
            self.key,
            self.secret,
            request.method,
            request.path,
            get_params=request.params,
            get_data=request.data
        )

        if not request.data:
            request.data = ""

        return request

    def connect(
        self,
        key: str,
        secret: str,
        server: str,
        proxy_host: str,
        proxy_port: int
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret
        self.server = server
        self.proxy_host = proxy_host
        self.proxy_port = proxy_port

        self.connect_date = int(datetime.now(UTC_TZ).strftime("%y%m%d"))

        if server == "REAL":
            self.init(REST_HOST, proxy_host, proxy_port)
        else:
            self.init(TESTNET_REST_HOST, proxy_host, proxy_port)

        self.start(3)

        self.gateway.write_log("REST API启动成功")

    def query_account(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v4/futures/accounts",
            callback=self.on_query_account
        )

    def query_position(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v4/futures/positions",
            callback=self.on_query_position
        )

    def query_order(self):
        """"""
        for contract in self.symbols:
            params = {
                "contract": contract,
                "status": "open",
            }

            self.add_request(
                method="GET",
                path="/api/v4/futures/orders",
                callback=self.on_query_order,
                params=params
            )

    def query_contract(self):
        """"""
        self.add_request(
            method="GET",
            path="/api/v4/futures/contracts",
            callback=self.on_query_contract
        )

    def query_history(self, req: HistoryRequest):
        """"""
        history = []
        interval = INTERVAL_VT2GATEIO[req.interval]

        params = {
            "contract": req.symbol,
            "limit": 2000,
            "interval": interval,
        }

        resp = self.request(
            method="GET",
            path="/api/v4/futures/candlesticks",
            params=params
        )

        if resp.status_code // 100 != 2:
            msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
            self.gateway.write_log(msg)
        else:
            data = resp.json()
            if not data:
                msg = f"获取历史数据为空"

            for d in data:
                bar = BarData(
                    symbol=req.symbol,
                    exchange=req.exchange,
                    datetime=generate_datetime(d["t"]),
                    interval=req.interval,
                    volume=d["v"],
                    open_price=float(d["o"]),
                    high_price=float(d["h"]),
                    low_price=float(d["l"]),
                    close_price=float(d["c"]),
                    gateway_name=self.gateway_name
                )
                history.append(bar)

            begin = generate_datetime(data[0]["t"])
            end = generate_datetime(data[-1]["t"])

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
        order.datetime = datetime.now(UTC_TZ)

        if req.direction == Direction.SHORT:
            volume = -int(req.volume)
        else:
            volume = int(req.volume)

        request_body = {
            "contract": req.symbol,
            "size": volume,
            "price": str(req.price),
            "close": False,
            "tif": "gtc",
            "text": f"t-{local_orderid}"
        }

        data = json.dumps(request_body)

        self.add_request(
            method="POST",
            path="/api/v4/futures/orders",
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
        if not sys_orderid:
            self.write_log("撤单失败，找不到对应系统委托号{}".format(req.orderid))
            return

        self.add_request(
            method="DELETE",
            path=f"/api/v4/futures/orders/{sys_orderid}",
            callback=self.on_cancel_order,
            on_failed=self.on_cancel_order_failed,
            extra=req
        )

    def on_query_account(self, data, request):
        """"""
        self.account_id = str(data["user"])

        account = AccountData(
            accountid=self.account_id,
            balance=float(data["total"]),
            frozen=float(data["total"]) - float(data["available"]),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_account(account)

        if not self.symbols:
            self.query_contract()

    def on_query_position(self, data, request):
        """"""
        for d in data:
            position = PositionData(
                symbol=d["contract"],
                exchange=Exchange.GATEIO,
                volume=float(d["size"]),
                direction=Direction.NET,
                price=float(d["entry_price"]),
                pnl=float(d["unrealised_pnl"]),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_position(position)

    def on_query_order(self, data, request):
        """"""
        for d in data:
            local_orderid = self.order_manager.new_local_orderid()
            sys_orderid = str(d["id"])

            self.order_manager.update_orderid_map(
                local_orderid=local_orderid,
                sys_orderid=sys_orderid
            )

            if d["size"] > 0:
                direction = Direction.LONG
            else:
                direction = Direction.SHORT

            volume = abs(d["size"])
            traded = abs(d["size"] - d["left"])
            status = get_order_status(d["status"], volume, traded)

            order = OrderData(
                orderid=local_orderid,
                symbol=d["contract"],
                exchange=Exchange.GATEIO,
                price=float(d["price"]),
                volume=abs(volume),
                type=OrderType.LIMIT,
                direction=direction,
                status=status,
                datetime=generate_datetime(d["create_time"]),
                gateway_name=self.gateway_name,
            )
            self.order_manager.on_order(order)

        self.gateway.write_log(f"{order.symbol}合约委托信息查询成功")

    def on_query_contract(self, data, request):  # type: (dict, Request)->None
        """"""
        for d in data:
            symbol = d["name"]
            self.symbols.append(symbol)

            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.GATEIO,
                name=symbol,
                pricetick=float(d["order_price_round"]),
                size=int(d["leverage_min"]),
                min_volume=d["order_size_min"],
                product=Product.FUTURES,
                gateway_name=self.gateway_name,
                history_data=True,
                net_position=True
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

        # Connect websocket api after account id and contract symbols collected
        self.ws_api.connect(
            self.key,
            self.secret,
            self.server,
            self.proxy_host,
            self.proxy_port,
            self.account_id,
            self.symbols
        )

    def on_send_order(self, data, request):
        """"""
        order = request.extra
        sys_orderid = str(data["id"])
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
        if data["status"] == "error":
            error_code = data["err_code"]
            error_msg = data["err_msg"]
            self.gateway.write_log(f"撤单失败，错误代码：{error_code}，信息：{error_msg}")

    def on_cancel_order_failed(self, status_code: str, request: Request):
        """
        Callback when canceling order failed on server.
        """
        msg = f"撤单失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)


class GateiosWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(GateiosWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.key = ""
        self.secret = ""
        self.account_id = ""
        self.symbols = []

        self.trade_count = 0
        self.ticks = {}

    def connect(
        self,
        key: str,
        secret: str,
        server: str,
        proxy_host: str,
        proxy_port: int,
        account_id: str,
        symbols: List[str]
    ):
        """"""
        self.key = key
        self.secret = secret
        self.account_id = account_id
        self.symbols = symbols

        if server == "REAL":
            self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        else:
            self.init(TESTNET_WEBSOCKET_HOST, proxy_host, proxy_port)

        self.start()

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")

        for symbol in self.symbols:
            for channel in [
                "futures.orders",
                "futures.usertrades"
            ]:
                req = self.generate_req(
                    channel=channel,
                    event="subscribe",
                    pay_load=[self.account_id, symbol]
                )
                self.send_packet(req)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data upate.
        """
        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            name=req.symbol,
            datetime=datetime.now(UTC_TZ),
            gateway_name=self.gateway_name,
        )
        self.ticks[req.symbol] = tick

        tick_req = self.generate_req(
            channel="futures.tickers",
            event="subscribe",
            pay_load=[req.symbol]
        )
        self.send_packet(tick_req)

        depth_req = self.generate_req(
            channel="futures.order_book",
            event="subscribe",
            pay_load=[req.symbol, "5", "0"]
        )
        self.send_packet(depth_req)

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: Dict):
        """"""
        timestamp = packet["time"]
        channel = packet["channel"]
        event = packet["event"]
        result = packet["result"]
        error = packet["error"]

        if error:
            self.gateway.write_log("Websocket API报错：%s" % error)
            return

        if channel == "futures.tickers" and event == "update":
            self.on_tick(result, timestamp)
        elif channel == "futures.order_book" and event == "all":
            self.on_depth(result, timestamp)
        elif channel == "futures.orders" and event == "update":
            self.on_order(result, timestamp)
        elif channel == "futures.usertrades" and event == "update":
            self.on_trade(result, timestamp)

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(
            exception_type, exception_value, tb))

    def generate_req(self, channel: str, event: str, pay_load: List):
        """"""
        expires = int(time.time())
        signature = generate_websocket_sign(
            self.secret, channel, event, expires)

        req = {
            "time": expires,
            "channel": channel,
            "event": event,
            "payload": pay_load,
            "auth": {
                "method": "api_key",
                "KEY": self.key,
                "SIGN": signature
            }
        }

        return req

    def on_tick(self, l: List, t: int):
        """"""
        d = l[0]
        symbol = d["contract"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        tick.last_price = float(d["last"])
        tick.volume = int(d["volume_24h"])
        tick.datetime = generate_datetime(t)
        self.gateway.on_tick(copy(tick))

    def on_depth(self, d: Dict, t: int):
        """"""
        symbol = d["contract"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        for n, buf in enumerate(d["bids"][:5]):
            price = float(buf["p"])
            volume = buf["s"]
            tick.__setattr__("bid_price_%s" % (n + 1), price)
            tick.__setattr__("bid_volume_%s" % (n + 1), volume)

        for n, buf in enumerate(d["asks"][:5]):
            price = float(buf["p"])
            volume = buf["s"]
            tick.__setattr__("ask_price_%s" % (n + 1), price)
            tick.__setattr__("ask_volume_%s" % (n + 1), volume)

        tick.datetime = generate_datetime(t)

        self.gateway.on_tick(copy(tick))

    def on_order(self, l: List, t: int):
        """"""
        d = l[0]

        local_orderid = str(d["text"])[2:]

        if d["size"] > 0:
            direction = Direction.LONG
        else:
            direction = Direction.SHORT

        volume = abs(d["size"])
        traded = abs(d["size"] - d["left"])
        status = get_order_status(d["status"], volume, traded)

        order = OrderData(
            orderid=local_orderid,
            symbol=d["contract"],
            exchange=Exchange.GATEIO,
            price=float(d["price"]),
            volume=abs(volume),
            type=OrderType.LIMIT,
            direction=direction,
            status=status,
            datetime=generate_datetime(t),
            gateway_name=self.gateway_name,
        )

        self.order_manager.on_order(order)

    def on_trade(self, l: List, t: int):
        """"""
        d = l[0]

        sys_orderid = d["order_id"]
        order = self.order_manager.get_order_with_sys_orderid(sys_orderid)
        if not order:
            return

        trade = TradeData(
            symbol=order.symbol,
            exchange=order.exchange,
            orderid=order.orderid,
            tradeid=d["id"],
            direction=order.direction,
            price=float(d["price"]),
            volume=abs(d["size"]),
            datetime=generate_datetime(d["create_time"]),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_trade(trade)


def generate_sign(key, secret, method, path, get_params=None, get_data=None):
    """"""
    if get_params:
        params = urlencode(get_params)
    else:
        params = ""

    hashed_data = get_hashed_data(get_data)

    timestamp = str(time.time())

    pay_load = [method, path, params, hashed_data, timestamp]
    pay_load = "\n".join(pay_load)

    signature = hmac.new(
        secret.encode("utf-8"),
        pay_load.encode("utf-8"),
        hashlib.sha512
    ).hexdigest()

    headers = {
        "Accept": "application/json",
        "Content-Type": "application/json",
        "KEY": key,
        "Timestamp": str(timestamp),
        "SIGN": signature
    }

    return headers


def get_hashed_data(get_data):
    """"""
    hashed_data = hashlib.sha512()
    if get_data:
        data = get_data
        hashed_data.update(data.encode("utf-8"))

    return hashed_data.hexdigest()


def generate_websocket_sign(secret, channel, event, time):
    """"""
    message = 'channel=%s&event=%s&time=%s' % (channel, event, time)

    signature = hmac.new(
        secret.encode("utf-8"),
        message.encode("utf-8"),
        hashlib.sha512
    ).hexdigest()

    return signature


def get_order_status(status: str, volume: int, traded: int):
    """"""
    if status == "open":
        if traded:
            return Status.PARTTRADED
        else:
            return Status.NOTTRADED
    else:
        if traded == volume:
            return Status.ALLTRADED
        else:
            return Status.CANCELLED


def generate_datetime(timestamp: float) -> datetime:
    """"""
    dt = datetime.fromtimestamp(timestamp)
    dt = UTC_TZ.localize(dt)
    return dt
