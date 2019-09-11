"""
Author: Wudi
bitstamp合约接口
"""

import hashlib
import hmac
import sys
import time
import re
from copy import copy
from datetime import datetime, timedelta
from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from time import sleep

from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Interval
)
from vnpy.trader.gateway import BaseGateway, LocalOrderManager
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    BarData,
    PositionData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)

from vnpy.trader.event import EVENT_TIMER


REST_HOST = "https://www.bitstamp.net/api/v2"
WEBSOCKET_HOST = "wss://ws.bitstamp.net"

STATUS_BITSTAMP2VT = {
    "ACTIVE": Status.NOTTRADED,
    "PARTIALLY FILLED": Status.PARTTRADED,
    "EXECUTED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
}

ORDERTYPE_VT2BITSTAMP = {
    OrderType.LIMIT: "EXCHANGE LIMIT",
    OrderType.MARKET: "EXCHANGE MARKET",
}

DIRECTION_VT2BITSTAMP = {
    Direction.LONG: "Buy",
    Direction.SHORT: "Sell",
}

DIRECTION_BITSTAMP2VT = {
    "0": Direction.LONG,
    "1": Direction.SHORT,
}

INTERVAL_VT2BITSTAMP = {
    Interval.MINUTE: "60",
    Interval.HOUR: "3600",
    Interval.DAILY: "86400",
}

TIMEDELTA_MAP = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}

bitstamp_symbols = set()

symbol_name_map = {}

SYMBOL_BITSTAMP2VT = {
    'bchusd': "BCH/USD", 'bcheur': "BCH/EUR",
    'xrpusd': "XRP/USD", 'ltcusd': "LTC/USD",
    'eurusd': "EUR/USD", 'etheur': "ETH/EUR",
    'xrpeur': "XRP/EUR", 'btceur': "BTC/EUR",
    'ltcbtc': "LTC/BTC", 'btcusd': "BTC/USD",
    'ltceur': "LTC/EUR", 'ethusd': "ETH/USD",
    'xrpbtc': "XRP/BTC", 'bchbtc': "BCH/BTC",
    'ethbtc': "ETH/BTC",
}


class BitstampGateway(BaseGateway):
    """
    VN Trader Gateway for BITSTAMP connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "username": "",
        "session": 3,
        "proxy_host": "127.0.0.1",
        "proxy_port": 1080,
    }

    exchanges = [Exchange.BITSTAMP]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "BITSTAMP")

        self.order_manager = LocalOrderManager(self)

        self.rest_api = BitstampRestApi(self)
        self.ws_api = BitstampWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        username = setting["username"]
        session = setting["session"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        self.rest_api.connect(key, secret, username,
                              session, proxy_host, proxy_port)
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


class BitstampRestApi(RestClient):
    """
    Bitstamp REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(BitstampRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.key = ""
        self.secret = ""
        self.username = ""

        self.order_count = 1_000_000
        self.connect_time = 0

    def connect(
        self,
        key: str,
        secret: str,
        username: str,
        session: int,
        proxy_host: str,
        proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret.encode()
        self.username = username

        self.connect_time = (
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session)

        self.gateway.write_log("REST API启动成功")

        self.query_contract()
        self.query_account()
        self.query_order()

    def sign(self, request: Request):
        """
        Sign Bitstamp request.
        """
        # Sign
        nonce = int(round(time.time() * 1000000))
        message = f"{nonce}{self.username}{self.key}"

        signature = hmac.new(
            self.secret,
            msg=message.encode('utf-8'),
            digestmod=hashlib.sha256
        ).hexdigest().upper()

        if request.method == "POST":
            if request.data is None:
                request.data = {}

            request.data["key"] = self.key
            request.data["nonce"] = nonce
            request.data["signature"] = signature

        return request

    def query_order(self):
        """"""
        path = "/open_orders/all/"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_query_order
        )

    def on_query_order(self, data, request):
        """获取委托订单"""
        for d in data:
            sys_orderid = d["id"]
            local_orderid = self.order_manager.get_local_orderid(sys_orderid)

            direction = DIRECTION_BITSTAMP2VT[d["type"]]

            order = OrderData(
                orderid=local_orderid,
                symbol=d["currency_pair"],
                exchange=Exchange.BITSTAMP,
                price=float(d["price"]),
                volume=float(d["amount"]),
                traded=float(0),
                direction=direction,
                time=d["datetime"],
                gateway_name=self.gateway_name,
            )

            self.order_manager.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def query_account(self):
        """"""
        path = "/balance/"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_query_account
        )

    def on_query_account(self, data, request):
        """"""
        for d in data:
            if "balance" in d:
                currency = d.replace("_balance", "")
                account = AccountData(
                    accountid=currency,
                    balance=float(data[currency + "_balance"]),
                    frozen=float(data[currency + "_reserved"]),
                    # available=float(data[currency + "_available"]),
                    gateway_name=self.gateway_name
                )

                self.gateway.on_account(account)

        self.on_position(data)

    def query_contract(self):
        """"""
        self.add_request(
            method="GET",
            path="/trading-pairs-info/",
            callback=self.on_query_contract,
        )

    def on_query_contract(self, data, request):
        """"""
        for d in data:
            pricetick = 1 / pow(10, d["base_decimals"])
            min_volume = float(d["minimum_order"])

            contract = ContractData(
                symbol=d["url_symbol"],
                exchange=Exchange.BITSTAMP,
                name=d["name"],
                product=Product.SPOT,
                size=1,
                pricetick=pricetick,
                min_volume=min_volume,
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

    def cancel_order(self, req: CancelRequest):
        """"""
        path = "/cancel_order/"

        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)

        data = {"id": sys_orderid}

        self.add_request(
            method="POST",
            path=path,
            data=data,
            callback=self.on_cancel_order,
            extra=req
        )

    def on_cancel_order(self, data, request):
        """"""
        cancel_request = request.extra
        local_orderid = cancel_request.orderid
        order = self.order_manager.get_order_with_local_orderid(local_orderid)

        if "error" in data:
            local_order.status = Status.REJECTED
        else:
            local_order.status = Status.CANCELLED

            self.gateway.write_log(f"委托撤单成功：{order.orderid})

        self.order_manager.on_order(order)

    def on_cancel_order_error(self, data, request):
        print(f"cancel_order {data}")
        error_msg = data["error"]
        self.gateway.write_log(f"撤单请求出错，信息：{error_msg}")

    def send_order(self, req: OrderRequest):
        """"""

        local_orderid = self.order_manager.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.time = datetime.now().strftime("%H:%M:%S")

        data = {
            "amount": req.volume,
            "price": req.price
        }

        if req.direction == Direction.LONG:
            if req.type == OrderType.LIMIT:
                path = f"/buy/{req.symbol}/"
            elif req.type == OrderType.MARKET:
                path = f"/buy/market/{req.symbol}/"
        else:
            if req.type == OrderType.LIMIT:
                path = f"/sell/{req.symbol}/"
            elif req.type == OrderType.MARKET:
                path = f"/sell/market/{req.symbol}/"

        self.add_request(
            method="POST",
            path=path,
            data=data,
            callback=self.on_send_order,
            extra=order,
        )
        self.order_manager.on_order(order)
        return order.vt_orderid

    def on_send_order(self, data, request):
        """"""
        order = request.extra

        if ["reason"] in data:
            order.status = Status.REJECTED
            self.order_manager.on_order(order)
            return

        sys_orderid = data["id"]
        self.order_manager.update_orderid_map(order.orderid, sys_orderid)

    def on_send_order_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when sending order caused exception.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        print(f"on_failed {request}")

        reason = request.response.json()["reason"]
        code = request.response.json()["code"]
        msg = f"{request.path} 请求失败，状态码：{status_code}，信息： {reason} code: {code}"
        self.gateway.write_log(msg)

        # print(f"reason： {reason} code: {code}")
        path = request.path
        if code in ["API0004"]:
            # nonce 错误重新执行此请求
            if path == "user_transactions/":
                self.user_transactions()
                self.gateway.write_log("重新获取 Transactions 数据")

            elif path == "query_order/all/":
                self.query_order()
                self.gateway.write_log("重新获取委托数据")

            elif path == "cancel_order/":
                self.cancel_order(request.extra)
                self.gateway.write_log(f"重新提交{request.extra.orderid}撤单请求")
            elif path == "balance/":
                self.query_account()
                self.gateway.write_log(f"重新获取balance撤单请求")

            elif ("sell" in path) or ("buy" in path):
                order_data = request.extra

                # update order status
                order_data.status = Status.REJECTED
                self.order_manager.on_order(order_data)

                req = OrderRequest(
                    symbol=order_data.symbol,
                    exchange=order_data.exchange,
                    direction=order_data.direction,
                    type=order_data.type,
                    volume=order_data.volume,
                    price=order_data.price,
                    offset=order_data.offset
                )

                self.send_order(req)
                self.gateway.write_log("重新提交委托请求")

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


class BitstampWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.ticks = {}

    def connect(self, proxy_host: str, proxy_port: int):
        """"""
        self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        self.start()

    def post_connected(self, req: SubscribeRequest):
        """
        测试默认连接btcusd
        :return:
        """
        sleep(1)
        d = {
            "event": "bts:subscribe",
            "data": {
                # "channel": "diff_order_book_" + req.symbol  # "live_trades_btcusd"
                "channel": "order_book_" + req.symbol  # "live_trades_btcusd"
            }
        }
        self.send_packet(d)
        sleep(1)

        d = {
            "event": "bts:subscribe",
            "data": {
                "channel": "live_trades_" + req.symbol  # "live_trades_btcusd"
            }
        }
        self.send_packet(d)

    def on_connected(self):
        """"""
        self.gateway.write_log("行情Websocket API连接刷新")
        # 测试默认提交
        # self.post_connected()
        # self.subscribe(req)

    def subscribe(self, req: SubscribeRequest):
        """"""
        # print(f"webocket subscribe req {req}")
        # Create tick buf data

        tick = TickData(
            symbol=req.symbol,
            # name=symbol_name_map.get(req.symbol, ""),
            name=req.symbol,
            exchange=Exchange.BITSTAMP,
            datetime=datetime.now(),
            gateway_name=self.gateway_name,
        )
        self.ticks[req.symbol.lower()] = tick

        # 默认使用btcusd 连接
        self.post_connected(req)

    def on_packet(self, packet):
        """"""
        # print(f"on_packet {packet}")
        if "bts:request_reconnect" == packet["event"]:
            # 重新连接
            self.post_connected()
        elif "data" == packet["event"]:
            return self.on_market_depth(packet)
        else:
            self.on_data(packet)

    def on_data(self, packet):
        """"""
        if packet["event"] == "trade":
            self.on_trade_update(packet)
        # print("data : {}".format(packet))

    def on_trade_update(self, packet):
        channel = packet["channel"]
        data = packet["data"]
        symbol = str(re.sub("live_.*_", "", channel))
        tick = self.ticks[symbol]
        tick.last_price = float(data["price"])

    def on_market_depth(self, packet):
        """行情深度推送 """

        channel = packet["channel"]
        data = packet["data"]
        # symbol = str(re.sub("live_.*_","", channel))  #live order channel
        symbol = str(re.sub("order_book_", "", channel))
        # print(f"market_detph {data}")
        tick = self.ticks[symbol]
        tick.datetime = datetime.fromtimestamp(int(data['timestamp']) / 1000)

        if symbol in self.ticks:
            tick = self.ticks[symbol]
        else:
            tick = TickData(
                symbol=symbol,
                exchange=Exchange.BITFINEX,
                name=symbol,
                datetime=datetime.now(),
                gateway_name=self.gateway_name,
            )

            self.ticks[symbol] = tick

        if len(data) == 0:
            print("请求数据为空")
            return

        bids = data["bids"]

        for n in range(5):
            # for n in range(len(bids)):
            price, volume = bids[n]
            tick.__setattr__("bid_price_" + str(n + 1), float(price))
            tick.__setattr__("bid_volume_" + str(n + 1), float(volume))

        asks = data["asks"]
        # print(f"bids count {len(bids)} , asks count {len(asks)}")
        for n in range(5):
            # for n in range(len(asks)):
            price, volume = asks[n]
            tick.__setattr__("ask_price_" + str(n + 1), float(price))
            tick.__setattr__("ask_volume_" + str(n + 1), float(volume))

        self.gateway.on_tick(copy(tick))
