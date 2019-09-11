"""
Author: Wudi
bitstamp合约接口
"""

import hashlib
import hmac
import sys
import time
import re
import hmac
import hashlib
from copy import copy
from datetime import datetime, timedelta
from urllib.parse import urlencode
from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.event import Event
from urllib import parse
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


REST_HOST = "https://www.bitstamp.net/api/v2/"
REST_HOST_V1 = "https://www.bitstamp.net/api/"
WEBSOCKET_HOST = "wss://ws.bitstamp.net"
HISTORY_HOST = "https://api.blockchain.info/"

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
        "proxy_port": 1087,
    }

    exchanges = [Exchange.BITSTAMP]

    def __init__(self, event_engine):
        """Constructor"""
        super(BitstampGateway, self).__init__(event_engine, "BITSTAMP")

        self.order_manager = LocalOrderManager(self)

        self.rest_api = BitstampRestApi(self)
        self.rest_api_v1 = BitstampRestApiV1(self)
        self.ws_data_api = BitstampDataWebsocketApi(self)
        self.history_api = BitstampHistoryApi(self)
        self.orders = {}

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
        self.ws_data_api.connect(proxy_host, proxy_port)
        self.history_api.connect(key, session, proxy_host, proxy_port)
        self.rest_api_v1.connect(
            key, secret, username, session, proxy_host, proxy_port)

        # 循环监听账户balance
        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        # self.ws_api.subscribe(req)
        self.ws_data_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)
        # return self.ws_data_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        # print(f"show cancel req {req}")
        return self.rest_api.cancel_order(req)

    def get_order(self, orderid: str):
        """"""
        return self.orders.get(orderid, None)

    def check_order(self):
        ids = self.rest_api.get_submit_ids()
        # print(f" show check order ids {ids}")
        for i in ids:

            self.rest_api_v1.order_status(i)
            data = self.rest_api_v1.get_callback_data(i)
            self.rest_api.update_trade(i, data)


    def query_account(self):
        """"""
        self.rest_api.query_account_balance()

    def query_position(self):
        """"""
        pass

    def query_history(self, req: HistoryRequest):
        """"""
        return self.history_api.query_history(req)

    def close(self):
        """"""
        self.rest_api.stop()
        self.rest_api_v1.stop()
        self.ws_data_api.stop()
        self.history_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        self.count += 1
        if self.count < 5:
            return

        self.count = 0
        self.check_order()

    def init_query(self):
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class BitstampRestApiV1(RestClient):
    """Bitstap public api"""

    def __init__(self, gateway: BaseGateway):
        super(BitstampRestApiV1, self).__init__()
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager

        self.key = ""
        self.secret = ""
        self.username = ""
        self.order_count = 1_000_000
        self.connect_time = 0
        self.ticks = {}
        self.push_callback_data = {}

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

        self.init(REST_HOST_V1, proxy_host, proxy_port)
        self.start(session)

        self.gateway.write_log("REST API V1 启动成功")
        # self.order_status()
        # self.query_account_balance()
        # self.cancel_all_orders()

        # self.order_status()
    def get_nonce(self):
        """"""
        nonce = getattr(self, '_nonce', 0)
        print(f"nonce ====== {nonce}")
        if nonce:
            nonce += 1
        # If the unix time is greater though, use that instead (helps low
        # concurrency multi-threaded apps always call with the largest nonce).
        self._nonce = max(int(time.time()), nonce)
        return self._nonce

    def default_data(self, *args, **kwargs):
        """
        Generate a one-time signature and other data required to send a secure
        POST request to the Bitstamp API.
        """
        data = {}
        data['key'] = self.key
        # nonce = self.get_nonce()
        nonce = str(int(round(time.time() * 1000)))

        msg = str(nonce) + self.username + self.key
        print(f"usrname {self.username} nonce {nonce}")
        print(f"msg {msg.encode('utf-8')}")
        signature = hmac.new(
            self.secret,
            msg=msg.encode('utf-8'),
            digestmod=hashlib.sha256).hexdigest().upper()
        data['signature'] = signature
        data['nonce'] = nonce
        return data

    def sign(self, request):
        """
        Generate Bitstamp signature.
        """
        # Sign
        # nonce = str(int(round(time.time() * 1000000)))

        if request.params:
            query = urlencode(request.params)
            path = request.path + "?" + query
        else:
            path = request.path

        if request.data:
            request.data = urlencode(request.data)
        else:
            request.data = ""

        # print(request)

        # msg = request.method + \
        #     "/api/{}{}".format(path, request.data)
        # print(msg)
        headers = {"Content-Type": "application/x-www-form-urlencoded"}

        request.headers = headers
        return request

    def order_status(self, id):
        """"""

        data = self.default_data()
        data["id"] = id
        # data["id"] = 4002801278
        # print(f"ordre status show order {self.order_manager.__dict__}")
        self.add_request(
            method="POST",
            path="order_status/",
            # params=data,
            data=data,
            callback=self.on_order_status,
            extra=id
        )

    def on_order_status(self, data, request):
        """"""
        self.push_callback_data = {}

        print(f"v1 On order status {data}, {data.keys()}")
        print(f" error in data.keys() {'error' in data.keys()} ")
        if "error" in data.keys():
            error_data = data["error"]
            msg = f"{request.path} 请求失败，信息： {error_data}"
            print(msg)
            if error_data == 'Invalid nonce':
                self.order_status(request.extra)
                return

        self.push_callback_data[str(request.extra)] = data

    def get_callback_data(self, id):
        # print(f"get info {id} {self.push_callback_data}")
        if str(id) in self.push_callback_data.keys():
            return self.push_callback_data[str(id)]
        else:
            return {"status": "error", "reason": "id not find"}

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


class BitstampHistoryApi(RestClient):

    def __init__(self, gateway: BaseGateway):
        super(BitstampHistoryApi, self).__init__()
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

    def connect(
            self,
            key: str,
            # secret: str,
            # username: str,
            session: int,
            proxy_host: str,
            proxy_port: int,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.init(HISTORY_HOST, proxy_host, proxy_port)
        self.start(session)

        self.gateway.write_log("REST history API启动成功")
        # self.order_status()
        # self.query_account_balance()
        # self.cancel_all_orders()

    def query_history(self, req: HistoryRequest):
        """
        https://www.bitstamp.net/ajax/tradeview/price-history/?step=1800&currency_pair=BTC%2FUSD&start_datetime=2019-06-13T00:02:17.000Z&end_datetime=2019-06-29T13:02:15.000Z
        :params {step  currency_pair start_datetime end_datetime
        "https://api.blockchain.info/price/bar-series?exchange=bitstamp&base=BTC&quote=USD&start=1523111200&scale=60&end=1523439439"
        :params { "exchange" : exchange, "base" : base, "quote" : quote, "start" : start timestamp, "scale": 60 86400... , "end" : timestamp}

        HistoryRequest = {
            symbol: str
            exchange: Exchange
            start: datetime
            end: datetime = None
            interval: Interval = None
        }
        """
        print(f"History {req}")

        history = []
        limit = 1000
        step = int(INTERVAL_VT2BITSTAMP[req.interval])
        symbol = SYMBOL_BITSTAMP2VT[req.symbol]
        base, quote = symbol.split("/")
        start_time = int(datetime.timestamp(req.start))
        path = "price/bar-series"

        while True:
            if req.end:
                # print(f"start time {start_time}")
                end_time = start_time + \
                    int(INTERVAL_VT2BITSTAMP[req.interval]) * 1000
                # print(f"end time {end_time}")

            # Create query params
            params = {
                "exchange": "bitstamp",
                "base": base,
                "quote": quote,
                "start": start_time,
                "end": end_time,
                "scale": step
            }
            """
            btcusd.BITSTAMP
            """
            # Get response from server
            resp = self.request(
                "GET",
                path,
                params=params,
            )

            # Break if request failed with other status code
            if resp.status_code // 100 != 2:
                msg = f"获取历史数据失败，状态码：{resp.status_code}，信息：{resp.text}"
                self.gateway.write_log(msg)
                break
            else:
                data = resp.json()
                if not data:
                    msg = f"获取历史数据为空，开始时间：{start_time}"
                    self.gateway.write_log(msg)
                    break

                buf = []

                for l in data:

                    dt = datetime.fromtimestamp(l["start"])
                    bar = BarData(
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=dt,
                        interval=req.interval,
                        volume=l["volume"],
                        open_price=l["open"],
                        high_price=l["high"],
                        low_price=l["low"],
                        close_price=l["close"],
                        gateway_name=self.gateway_name
                    )
                    buf.append(bar)

                history.extend(buf)

                begin = buf[0].datetime
                end = buf[-1].datetime
                msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
                self.gateway.write_log(msg)

                # # Break if total data count less than 1000 (latest date collected)
                # if len(data) < limit:
                #     break

                if int(datetime.timestamp(req.end)) < end_time:
                    break

                # Update start time
                start_time = int(datetime.timestamp(end))
                print(f"update start time {start_time}")
                # start_time = datetime.timestamp(bar.datetime) + int(TIMEDELTA_MAP[req.interval])

        return history


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
        self.ticks = {}
        self.trade_id = 1_000_000
        self.submit_ids = []  # sys_id
        self.trades = []
        self.position = {}

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
        # self.api_v1.connect(key, secret, username, session, proxy_host, proxy_port)

        self.start(session)

        self.gateway.write_log("REST API启动成功")
        self.query_contract()
        self.query_account_balance()
        # self.query_ticker()
        self.open_orders()
        self.user_transactions()

    def get_signature(self):
        nonce = str(int(round(time.time() * 1000000)))
        message = nonce + self.username + self.key
        print(message)
        signature = hmac.new(
            self.secret,
            msg=message.encode('utf-8'),
            digestmod=hashlib.sha256
        ).hexdigest().upper()
        print(signature)

        return signature

    def get_nonce(self):
        """"""
        nonce = getattr(self, '_nonce', 0)
        print(f"nonce ====== {nonce}")
        if nonce:
            nonce += 1
        # If the unix time is greater though, use that instead (helps low
        # concurrency multi-threaded apps always call with the largest nonce).
        self._nonce = max(int(time.time()), nonce)
        return self._nonce

    def default_data(self, *args, **kwargs):
        """
        Generate a one-time signature and other data required to send a secure
        POST request to the Bitstamp API.
        """
        data = {}
        data['key'] = self.key
        # nonce = self.get_nonce()
        nonce = str(int(round(time.time() * 1000)))

        msg = str(nonce) + self.username + self.key
        print(f"usrname {self.username} nonce {nonce}")
        print(f"msg {msg.encode('utf-8')}")
        signature = hmac.new(
            self.secret,
            msg=msg.encode('utf-8'),
            digestmod=hashlib.sha256).hexdigest().upper()
        data['signature'] = signature
        data['nonce'] = nonce
        return data

    def sign(self, request):
        """
        Generate BitfineX signature.
        """
        # Sign
        # nonce = str(int(round(time.time() * 1000000)))

        if request.params:
            query = urlencode(request.params)
            path = request.path + "?" + query
        else:
            path = request.path

        if request.data:
            request.data = urlencode(request.data)
        else:
            request.data = ""

        # print(request)
        #
        # msg = request.method + \
        #     "/api/v2/{}{}".format(path, request.data)
        # print(msg)
        headers = {"Content-Type": "application/x-www-form-urlencoded"}

        request.headers = headers
        return request

    def user_transactions(self, offset=0, limit=100, descending=True,
                          symbol=""):
        """账户转账记录"""
        data = self.default_data()
        data["offset"] = offset
        data["limit"] = limit
        data["sort"] = 'desc' if descending else 'asc'

        path = "user_transactions/"

        self.add_request(
            method="POST",
            path=path + symbol,
            data=data,
            callback=self.on_user_transactions,
        )

    def on_user_transactions(self, data, request):
        """
        Transaction type: 0 - deposit; 1 - withdrawal; 2 - market trade; 14 - sub account transfer.
        :param data:
        :param request:
        :return:
        """
        # print(f"transaction {data}")
        if not data:
            self.user_transactions()
            self.gateway.write_log("无 transcations 数据重新请求")
            return

        self.on_trade(data)



    def on_trade(self, data):
        """"""
        # self.trade_id += 1

        for d in data:
            if int(d["type"]) == 2:  # 交易记录
                btc = d["btc"]
                usd = d["usd"]
                btcusd = d["btc_usd"]
                tradetime = d["datetime"]
                fee = d["fee"]
                tradeid = d["id"]
                orderid = d["order_id"]

                if tradeid in self.trades:
                    # print(f"交易记录已存在")
                    continue

                if float(btc) > 0:
                    direction = Direction.LONG
                else:
                    direction = Direction.SHORT
                symbol = "BTC/USD" if float(btc) != 0 else ""

                trade = TradeData(
                    symbol=symbol,
                    exchange=Exchange.BITSTAMP,
                    orderid=orderid,
                    tradeid=tradeid,
                    direction=direction,
                    price=btcusd,
                    volume=abs(float(btc)),
                    time=tradetime,
                    gateway_name=self.gateway_name,
                )
                self.trades.append(tradeid)
                self.gateway.on_trade(trade)

    def update_trade(self, id, data):
        """
        check_order 中使用
        更新order成交状态
        """
        # print(f"update trade data {data}")
        if "error" in data.keys():
            self.gateway.write_log(f"Update Trade Error, Info: {data}")
            return

        order = self.order_manager.get_order_with_sys_orderid(id)
        local_id = self.order_manager.get_local_orderid(id)
        status = data["status"]
        if status == "Open":
            print(f"LocalId {local_id} still Submiting ")
            return

        if status == "Finished":

            btc_volume = sum(float(x["btc"]) for x in data["transactions"])
            usd_volume = sum(float(x["usd"]) for x in data["transactions"])

            if btc_volume == order.volume:
                order.status = Status.ALLTRADED
                order.traded = btc_volume
                self.gateway.write_log(f"委托成交完成：成交量 {btc_volume} 本地单号 {local_id} 系统单号 {id}")
                self.order_manager.on_order(order)
                """保留 后续验证是否需要提交到on order信息中"""
                self.gateway.on_order(order)

                """提交结束，移除检查订单id"""
                self.submit_ids.remove(str(id))

            else:
                order.status = Status.PARTTRADED
                order.traded = btc_volume
                self.gateway.write_log(f"委托部分成交：成交量 {btc_volume} 本地单号 {local_id} 系统单号 {id}")
                self.order_manager.on_order(order)
                """保留 后续验证是否需要提交到on order信息中"""
                self.gateway.on_order(order)

            self.query_account_balance()
            """更新线上交易记录"""
            self.user_transactions()


    def open_orders(self, symbol="all"):
        """
        id	Transaction ID.
        datetime	Date and time.
        type	Type: 0 - buy; 1 - sell.
        price	Price.
        amount	Amount.
        currency_pair (if all currency pairs)
        :param base:
        :param quote:
        :return:
        """

        path = "open_orders/" + symbol + "/"
        data = self.default_data()
        self.add_request(
            method="POST",
            path=path,
            data=data,
            callback=self.on_open_order,
        )

    def on_open_order(self, data, request):
        """获取委托订单"""

        if type(data) == "dict":
            if self.check_error(data, "查询委托"):
                return
        for d in data:
            sys_orderid = d["id"]
            local_orderid = self.order_manager.get_local_orderid(sys_orderid)
            direction = DIRECTION_BITSTAMP2VT[d["type"]]
            if sys_orderid not in self.submit_ids:
                self.submit_ids.append(sys_orderid)

            print(f"on open ids {d}")
            order = OrderData(
                # orderid=d["id"],
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
            """保留 后续验证是否需要提交到on order信息中"""
            self.gateway.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def cancel_order(self, req: CancelRequest):
        """"""
        path = "cancel_order/"
        data = self.default_data()

        # 测试 nonce 报错使用
        # if req.exchange != None:
        #     data["nonce"] = 1234123

        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)
        data["id"] = sys_orderid

        # print(f"request cancel order id {req.orderid}, {sys_orderid}")
        # print(self.order_manager)

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
        local_order = self.order_manager.get_order_with_local_orderid(
            local_orderid)
        sys_orderid = self.order_manager.get_sys_orderid(local_orderid)
        if self.check_error(data, "撤单"):
            local_order.status = Status.REJECTED
        else:
            local_order.status = Status.CANCELLED

            self.gateway.write_log(
                f"委托撤单成功：本地单号 {local_order.orderid} 系统单号 {sys_orderid}")

        # 更新本地 order 数据
        self.order_manager.on_order(local_order)
        # 更新 gate order 数据
        self.gateway.on_order(copy(local_order))
        # 更新账户资金数据
        self.query_account_balance()

        # # 移除提交状态id list
        # print(f"cancel order {sys_orderid}")
        # print(f"submit_ids {self.submit_ids}")
        if str(sys_orderid) in self.submit_ids:
            self.submit_ids.remove(str(sys_orderid))
        else:
            self.gateway.write_log(f"本地订单号不存在 {self.submit_ids}")

    def on_cancel_order_error(self, data, request):
        print(f"cancel_order {data}")
        error_msg = data["error"]
        self.gateway.write_log(f"撤单请求出错，信息：{error_msg}")

    def cancel_all_orders(self):
        """path ="https://www.bitstamp.net/api/cancel_all_orders/"""
        pass

    def send_order(self, req: OrderRequest):
        """
        only limit order
        :param req:
        :return:
        """
        print(f"send order req  {req}")
        data = self.default_data()
        data["amount"] = req.volume
        data["price"] = req.price
        symbol = req.symbol
        side = DIRECTION_VT2BITSTAMP[req.direction].lower()
        # print(f"in gate_way {symbol}, direction {req.direction}, \
        #         dir info {DIRECTION_VT2BITSTAMP[req.direction]}, \
        #         type{req.type, ORDERTYPE_VT2BITSTAMP[req.type]}, \
        #         bitstmap_type {req}")

        # data =  {'amount': 0.0001, 'price': 11000}
        path = side + "/" + symbol + "/"
        local_orderid = self.order_manager.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.time = datetime.now().strftime("%H:%M:%S")

        self.add_request(
            method="POST",
            path=path,
            data=data,
            callback=self.on_send_order,
            extra=order,
            # on_error=self.on_send_order_error,
        )
        self.order_manager.on_order(order)
        return order.vt_orderid

    def on_send_order(self, data, request):
        """"""
        local_order = request.extra
        local_order_id = local_order.orderid
        # order = self.order_manager.get_order_with_local_orderid(local_order_id)
        # print(f"[in on send order] get local order{order}")
        if self.check_error(data, "委托"):
            local_order.status = Status.REJECTED
            self.order_manager.on_order(local_order)
            return

        # local_order.orderid = data["id"]
        # 提交后切换为未成交 , 直到trade 返回获取成交后切换为成交状态
        local_order.status = Status.NOTTRADED
        self.order_manager.update_orderid_map(local_order_id, data["id"])
        self.order_manager.on_order(local_order)
        self.gateway.on_order(local_order)
        self.gateway.write_log(
            f"委托提交成功： 系统单号 {data['id']} ：本地单号 {local_order_id}")

        # 添加已经提交订单监控列表
        print(f"新增订单 {data['id']}")
        if data["id"] not in self.submit_ids:
            self.submit_ids.append(data["id"])

        # 更新资金数据
        self.query_account_balance()

    def get_submit_ids(self):
        """更新订单状态"""
        return self.submit_ids

    def find_id_by_status(self, data):
        pass

    def check_error(self, data: dict, func: str = ""):
        """"""
        if "status" in data.keys():
            error_msg = data["reason"]["__all__"]
            self.gateway.write_log(f"{func}请求出错，信息：{error_msg}")
            return True
        else:
            return False

    def on_send_order_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback when sending order caused exception.
        """
        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def query_account_balance(self):
        """"""
        path = "balance/"
        data = self.default_data()
        self.add_request(
            method="POST",
            path=path,
            data=data,
            callback=self.on_query_account_balance
        )

    def on_query_account_balance(self, data, request):
        """"""
        # print(f"on_balance {data}")

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

    def on_position(self, data):
        # print(data)
        position = PositionData(
            symbol="btcusd",
            exchange=Exchange.BITSTAMP,
            direction=Direction.NET,
            # volume = float(data.get("btc_balance", 0)),
            # notional = float(data.get("usd_balance", 0)),
            notional=float(data.get("btc_balance", 0)),
            # notional=float(data.get("usd_balance", 0)),
            #last_notional = round( (d.get("currentQty", 0.0) / d.get("lastPrice", 0.0)) if ( not d.get("lastPrice", 0.0) and not d.get("currentQty", 0.0)) else 0, 8),
            gateway_name=self.gateway_name,

        )
        self.gateway.on_position(position)

    def query_contract(self):
        """
        查询合约信息
        :return:
        """
        self.add_request(
            method="get",
            path="trading-pairs-info/",
            callback=self.on_query_contract,
        )

    def query_ticker(self, symbol):
        """查询ticker 信息"""
        # print(f"qurey ticker{symbol}")
        self.add_request(
            method="get",
            path="ticker/" + symbol,
            callback=self.on_query_ticker,
        )

    def on_query_ticker(self, data, request):

        symbol = request.path.replace("ticker/", "")
        ticker_rest_data = data
        print(symbol)
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

        tick.volume = float(ticker_rest_data['volume'])
        tick.high_price = float(ticker_rest_data['high'])
        tick.low_price = float(ticker_rest_data['low'])
        tick.open_price = float(ticker_rest_data['open'])

        self.gateway.on_tick(copy(tick))

    def on_query_contract(self, data, request):
        """"""
        for d in data:
            contract = ContractData(
                symbol=d["url_symbol"],
                exchange=Exchange.BITSTAMP,
                name=d["name"].upper(),
                product=Product.SPOT,
                size=1,
                pricetick=1 / pow(10, d["base_decimals"]),
                min_volume=float(d["minimum_order"].split(" ")[0]),
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

            bitstamp_symbols.add(contract.symbol)
            symbol_name_map[contract.symbol] = contract.name

        self.gateway.write_log("交易对查询成功")

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

            elif path == "open_orders/all/":
                self.open_orders()
                self.gateway.write_log("重新获取委托数据")

            elif path == "cancel_order/":
                self.cancel_order(request.extra)
                self.gateway.write_log(f"重新提交{request.extra.orderid}撤单请求")
            elif path == "balance/":
                self.query_account_balance()
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

    def buy_market_order(self, amount, base="btc", quote="usd"):
        """"""
        pass

    def buy_limit_order(self, amount, base="btc", quote="usd"):
        """"""
        pass

    def sell_limit_order(self, amount, price, base="btc", quote="usd", limit_price=None, ioc_order=False):
        """"""
        pass

    def sell_market_order(self, amount, base="btc", quote="usd"):
        """"""
        pass


class BitstampDataWebsocketApi(WebsocketClient):
    def __init__(self, gateway):
        """"""
        super(BitstampDataWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

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
