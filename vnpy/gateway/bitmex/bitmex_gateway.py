# encoding: UTF-8
"""
"""

from __future__ import print_function

import logging
import os
import json
import hashlib
import hmac
import sys
import time
import traceback
from datetime import datetime, timedelta
from copy import copy
from math import pow
from urllib.parse import urlencode

from requests import ConnectionError

from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    SubscribeRequest,
    OrderRequest,
    CancelRequest,
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData
)
from vnpy.trader.constant import Direction, Status, PriceType, Exchange, Product

REST_HOST = "https://www.bitmex.com/api/v1"
WEBSOCKET_HOST = "wss://www.bitmex.com/realtime"

TESTNET_REST_HOST = "https://testnet.bitmex.com/api/v1"
TESTNET_WEBSOCKET_HOST = "wss://testnet.bitmex.com/realtime"

STATUS_BITMEX2VT = {
    "New": Status.NOTTRADED,
    "Partially filled": Status.PARTTRADED,
    "Filled": Status.ALLTRADED,
    "Canceled": Status.CANCELLED,
    "Rejected": Status.REJECTED
}

DIRECTION_VT2BITMEX = {Direction.LONG: "Buy", Direction.SHORT: "Sell"}
DIRECTION_BITMEX2VT = {v: k for k, v in DIRECTION_VT2BITMEX.items()}

PRICETYPE_VT2BITMEX = {PriceType.LIMIT: "Limit", PriceType.MARKET: "Market"}


class BitmexGateway(BaseGateway):
    """
    VN Trader Gateway for BitMEX connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "session": 3,
        "server": ["REAL",
                   "TESTNET"],
        "proxy_host": "127.0.0.1",
        "proxy_port": 1080
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(BitmexGateway, self).__init__(event_engine, "BITMEX")

        self.rest_api = BitmexRestApi(self)
        self.ws_api = BitmexWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session = setting["session"]
        server = setting["server"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        self.rest_api.connect(
            key,
            secret,
            session,
            server,
            proxy_host,
            proxy_port
        )

        self.ws_api.connect(key, secret, server, proxy_host, proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req):
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
        self.ws_api.stop()


class BitmexRestApi(RestClient):
    """
    BitMEX REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(BitmexRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.order_count = 1000000
        self.connect_time = 0

    def sign(self, request):
        """
        Generate BitMEX signature.
        """
        # Sign
        expires = int(time.time() + 5)

        if request.params:
            query = urlencode(request.params)
            path = request.path + "?" + query
        else:
            path = request.path

        if request.data:
            request.data = urlencode(request.data)
        else:
            request.data = ""

        msg = request.method + "/api/v1" + path + str(expires) + request.data
        signature = hmac.new(
            self.secret,
            msg,
            digestmod=hashlib.sha256
        ).hexdigest()

        # Add headers
        headers = {
            "Content-Type": "application/x-www-form-urlencoded",
            "Accept": "application/json",
            "api-key": self.key,
            "api-expires": str(expires),
            "api-signature": signature
        }

        request.headers = headers
        return request

    def connect(
            self,
            key: str,
            secret: str,
            session: int,
            server: str,
            proxy_host: str,
            proxy_port: int
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret

        self.connect_time = int(
            datetime.now().strftime("%y%m%d%H%M%S")
        ) * self.order_count

        if server == "REAL":
            self.init(REST_HOST, proxy_host, proxy_port)
        else:
            self.init(TESTNET_REST_HOST, proxy_host, proxy_port)

        self.start(session)

        self.gateway.write_log(u"REST API启动成功")

    def send_order(self, req: SubscribeRequest):
        """"""
        self.order_count += 1
        orderid = str(self.connect_time + self.order_count)

        data = {
            "symbol": req.symbol,
            "side": DIRECTION_VT2BITMEX[req.direction],
            "ordType": PRICETYPE_VT2BITMEX[req.price_type],
            "price": req.price,
            "orderQty": req.volume,
            "clOrdID": orderid
        }

        # Only add price for limit order.
        if req.price_type == PriceType.LIMIT:
            data["price"] = req.price

        order = req.create_order_data(orderid, self.gateway_name)

        self.add_request(
            "POST",
            "/order",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_failed=self.on_send_order_failed,
            on_error=self.on_send_order_error,
        )

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        orderid = req.orderid

        if orderID.isdigit():
            params = {"clOrdID": orderid}
        else:
            params = {"orderID": orderid}

        self.add_request(
            "DELETE",
            "/order",
            callback=self.on_cancel_order,
            params=params,
            on_error=self.on_cancel_order_error,
        )

    def on_send_order_failed(self, _, request: Request):
        """
        Callback when sending order failed on server.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

    def on_send_order_error(
            self,
            exception_type: type,
            exception_value: Exception,
            tb,
            request: Request
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

    def on_send_order(self, data, request):
        """"""
        pass

    def on_cancel_order_error(
            self,
            exception_type: type,
            exception_value: Exception,
            tb,
            request: Request
    ):
        """
        Callback when cancelling order failed on server.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, Connection_error):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, data, request):
        """"""
        pass

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        msg = f"请求失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_error(
            self,
            exception_type: type,
            exception_value: Exception,
            tb,
            request: Request
    ):
        """
        Callback to handler request exception.
        """
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type,
                                  exception_value,
                                  tb,
                                  request)
        )


class BitmexWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(BitmexWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.callbacks = {
            "trade": self.on_tick,
            "orderBook10": self.on_depth,
            "execution": self.on_trade,
            "order": self.on_order,
            "position": self.on_position,
            "margin": self.on_account,
            "instrument": self.on_contract
        }

        self.ticks = {}
        self.accounts = {}
        self.orders = {}
        self.trades = set()

    def connect(
            self,
            key: str,
            secret: str,
            server: str,
            proxy_host: str,
            proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret.encode()

        if server == "REAL":
            self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        else:
            self.init(TESTNET_WEBSOCKET_HOST, proxy_host, proxy_port)

        self.start()

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data upate.
        """
        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            name=req.symbol,
            datetime=datetime.now(),
            gateway_name=self.gateway_name
        )
        self.ticks[req.symbol] = tick

    def on_connected(self):
        """"""
        self.gateway.write_log(u"Websocket API连接成功")
        self.authenticate()

    def on_disconnected(self):
        """"""
        self.gateway.write_log(u"Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        if "error" in packet:
            self.gateway.write_log(u"Websocket API报错：%s" % packet["error"])

            if "not valid" in packet["error"]:
                self.active = False

        elif "request" in packet:
            req = packet["request"]
            success = packet["success"]

            if success:
                if req["op"] == "authKey":
                    self.gateway.write_log(u"Websocket API验证授权成功")
                    self.subscribe_topic()

        elif "table" in packet:
            name = packet["table"]
            callback = self.callbacks[name]

            if isinstance(packet["data"], list):
                for d in packet["data"]:
                    callback(d)
            else:
                callback(packet["data"])

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type,
                                  exception_value,
                                  tb)
        )

    def authenticate(self):
        """
        Authenticate websockey connection to subscribe private topic.
        """
        expires = int(time.time())
        method = "GET"
        path = "/realtime"
        msg = method + path + str(expires)
        signature = hmac.new(
            self.secret,
            msg.encode(),
            digestmod=hashlib.sha256
        ).hexdigest()

        req = {"op": "authKey", "args": [self.key, expires, signature]}
        self.send_packet(req)

    def subscribe_topic(self):
        """
        Subscribe to all private topics.
        """
        req = {
            "op":
            "subscribe",
            "args": [
                "instrument",
                "trade",
                "orderBook10",
                "execution",
                "order",
                "position",
                "margin"
            ]
        }
        self.send_packet(req)

    def on_tick(self, d):
        """"""
        symbol = d["symbol"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        tick.last_price = d["price"]
        tick.datetime = datetime.strptime(d["timestamp"], "%Y-%m-%d %H:%M:%SZ")
        self.gateway.on_tick(copy(tick))

    def on_depth(self, d):
        """"""
        symbol = d["symbol"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        for n, buf in enumerate(d["bids"][:5]):
            price, volume = buf
            tick.__setattr__("bid_price_%s" % (n + 1), price)
            tick.__setattr__("bid_volume_%s" % (n + 1), volume)

        for n, buf in enumerate(d["asks"][:5]):
            price, volume = buf
            tick.__setattr__("ask_price_%s" % (n + 1), price)
            tick.__setattr__("ask_volume_%s" % (n + 1), volume)

        tick.datetime = datetime.strptime(d["timestamp"], "%Y-%m-%d %H:%M:%SZ")
        self.gateway.on_tick(copy(tick))

    def on_trade(self, d):
        """"""
        if not d["lastQty"]:
            return

        tradeid = d["execID"]
        if tradeid in self.trades:
            return
        self.trades.add(tradeid)

        if d["clOrdID"]:
            orderid = d["clOrdID"]
        else:
            orderid = d["orderID"]

        trade = TradeData(
            symbol=d["symbol"],
            exchange=Exchange.BITMEX,
            orderid=orderid,
            tradeid=tradeid,
            direction=DIRECTION_BITMEX2VT[d["side"]],
            price=d["lastPx"],
            volume=d["lastQty"],
            time=d["timestamp"][0:10].replace("-",
                                              ""),
            gateway_name=self.gateway_name
        )

        self.gateway.on_trade(trade)

    def on_order(self, d):
        """"""
        if "ordStatus" not in d:
            return

        sysid = d["orderID"]
        order = self.orders.get(sysid, None)
        if not order:
            if d["clOrdID"]:
                orderid = d["clOrdID"]
            else:
                orderid = sysid

            time = d["timestamp"][0:10].replace("-", ""),

            order = OrderData(
                symbol=d["symbol"],
                exchange=Exchange.BITMEX,
                orderid=orderid,
                direction=DIRECTION_BITMEX2VT[d["side"]],
                price=d["price"],
                volume=d["orderQty"],
                time=time,
                gateway_name=self.gateway_name
            )
            self.orders[sysid] = order

        order.traded = d.get("cumQty", order.tradedVolume)
        order.status = STATUS_BITMEX2VT.get(d["ordStatus"], STATUS_UNKNOWN)

        self.gateway.on_order(copy(order))

    def on_position(self, d):
        """"""
        position = PositionData(
            symbol=d["symbol"],
            exchange=EXCHANGE_BITMEX,
            direction=DIRECTION_NET,
            position=d["currentQty"],
            gateway_name=self.gateway_name
        )

        self.gateway.on_position(position)

    def on_account(self, d):
        """"""
        accountid = str(d["account"])
        account = self.accounts.get(accountid, None)
        if not account:
            account = AccountData(
                accountid=accountid,
                gateway_name=self.gateway_name
            )
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
            exchange=Exchange.BITMEX,
            name=d["symbol"],
            product=Product.FUTURES,
            pricetick=d["tickSize"],
            size=d["lotSize"],
            gateway_name=self.gateway_name
        )

        self.gateway.on_contract(contract)
