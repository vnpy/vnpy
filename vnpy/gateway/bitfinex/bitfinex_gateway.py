"""
Author: vigarbuaa
"""

import hashlib
import hmac
import sys
import time
from copy import copy
from datetime import datetime, timedelta
from urllib.parse import urlencode
import pytz

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.event import Event
from vnpy.trader.event import EVENT_TIMER

from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Interval
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    BarData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)

BASE_URL = "https://api.bitfinex.com/"

REST_HOST = "https://api.bitfinex.com/"
WEBSOCKET_HOST = "wss://api-pub.bitfinex.com/ws/2"

STATUS_BITFINEX2VT = {
    "ACTIVE": Status.NOTTRADED,
    "PARTIALLY FILLED": Status.PARTTRADED,
    "EXECUTED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
}

ORDERTYPE_VT2BITFINEX = {
    OrderType.LIMIT: "EXCHANGE LIMIT",
    OrderType.MARKET: "EXCHANGE MARKET",
}
ORDERTYPE_BITFINEX2VT = {
    "EXCHANGE LIMIT": OrderType.LIMIT,
    "EXCHANGE MARKET": OrderType.MARKET,
    "LIMIT": OrderType.LIMIT,
    "MARKET": OrderType.MARKET
}

DIRECTION_VT2BITFINEX = {
    Direction.LONG: "Buy",
    Direction.SHORT: "Sell",
}
DIRECTION_BITFINEX2VT = {
    "Buy": Direction.LONG,
    "Sell": Direction.SHORT,
}

INTERVAL_VT2BITFINEX = {
    Interval.MINUTE: "1m",
    Interval.HOUR: "1h",
    Interval.DAILY: "1D",
}

TIMEDELTA_MAP = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}

UTC_TZ = pytz.utc


class BitfinexGateway(BaseGateway):
    """
    VN Trader Gateway for bitfineX connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "session": 3,
        "proxy_host": "127.0.0.1",
        "proxy_port": 1080,
        "margin": ["False", "True"]
    }

    exchanges = [Exchange.BITFINEX]

    def __init__(self, event_engine):
        """Constructor"""
        super(BitfinexGateway, self).__init__(event_engine, "BITFINEX")

        self.timer_count = 0
        self.resubscribe_interval = 60

        self.rest_api = BitfinexRestApi(self)
        self.ws_api = BitfinexWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session = setting["session"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        if setting["margin"] == "True":
            margin = True
        else:
            margin = False

        self.rest_api.connect(key, secret, session, proxy_host, proxy_port)
        self.ws_api.connect(key, secret, proxy_host, proxy_port, margin)

        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.ws_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.ws_api.cancel_order(req)

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
        self.timer_count += 1

        if self.timer_count < self.resubscribe_interval:
            return

        self.timer_count = 0
        self.ws_api.resubscribe()


class BitfinexRestApi(RestClient):
    """
    BitfineX REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(BitfinexRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""

        self.order_count = 1_000_000
        self.connect_time = 0

    def sign(self, request):
        """
        Generate BitfineX signature.
        """
        # Sign
        nonce = str(int(round(time.time() * 1000000)))

        if request.params:
            query = urlencode(request.params)
            path = request.path + "?" + query
        else:
            path = request.path

        if request.data:
            request.data = urlencode(request.data)
        else:
            request.data = ""

        msg = request.method + \
            "/api/v2/{}{}{}".format(path, nonce, request.data)
        signature = hmac.new(
            self.secret, msg.encode("utf8"), digestmod=hashlib.sha384
        ).hexdigest()

        # Add headers
        headers = {
            "bfx-nonce": nonce,
            "bfx-apikey": self.key,
            "bfx-signature": signature,
            "content-type": "application/json"
        }

        request.headers = headers
        return request

    def connect(
        self,
        key: str,
        secret: str,
        session: int,
        proxy_host: str,
        proxy_port: int
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret.encode()

        self.connect_time = (
            int(datetime.now(UTC_TZ).strftime("%y%m%d%H%M%S")) * self.order_count
        )

        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session)

        self.gateway.write_log("REST API启动成功")
        self.query_contract()

    def query_contract(self):
        """"""
        self.add_request(
            method="GET",
            path="/v1/symbols_details",
            callback=self.on_query_contract,
        )

    def on_query_contract(self, data, request):
        """"""
        for d in data:
            contract = ContractData(
                symbol=d["pair"].upper(),
                exchange=Exchange.BITFINEX,
                name=d["pair"].upper(),
                product=Product.SPOT,
                size=1,
                pricetick=1 / pow(10, d["price_precision"]),
                min_volume=float(d["minimum_order_size"]),
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("账户资金查询成功")

    def on_failed(self, status_code: int, request: Request):
        """
        Callback to handle request failed.
        """
        msg = f"请求失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

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

    def query_history(self, req: HistoryRequest):
        """"""
        history = []
        limit = 5000

        interval = INTERVAL_VT2BITFINEX[req.interval]
        path = f"/v2/candles/trade:{interval}:t{req.symbol}/hist"

        start_time = req.start

        while True:
            # Create query params
            params = {
                "limit": 5000,
                "start": datetime.timestamp(start_time) * 1000,
                "sort": 1
            }

            # Get response from server
            resp = self.request(
                "GET",
                path,
                params=params
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
                    break

                buf = []

                for l in data:
                    ts, o, c, h, l, v = l

                    bar = BarData(
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=generate_datetime(ts),
                        interval=req.interval,
                        volume=v,
                        open_price=o,
                        high_price=h,
                        low_price=l,
                        close_price=c,
                        gateway_name=self.gateway_name
                    )
                    buf.append(bar)

                history.extend(buf)

                begin = buf[0].datetime
                end = buf[-1].datetime
                msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
                self.gateway.write_log(msg)

                # Break if total data count less than 5000 (latest date collected)
                if len(data) < limit:
                    break

                # Update start time
                start_time = bar.datetime + TIMEDELTA_MAP[req.interval]

        return history


class BitfinexWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(BitfinexWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_id = 1_000_000
        self.trade_id = 1_000_000
        self.key = ""
        self.secret = ""

        self.ticks = {}
        self.accounts = {}
        self.orders = {}
        self.trades = set()
        self.ticks = {}
        self.bids = {}
        self.asks = {}
        self.channels = {}       # channel_id : (Channel, Symbol)

        self.subscribed = {}

    def connect(
        self,
        key: str,
        secret: str,
        proxy_host: str,
        proxy_port: int,
        margin: bool
    ):
        """"""
        self.key = key
        self.secret = secret.encode()
        self.margin = margin
        self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        self.start()

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data update.
        """
        if req.symbol not in self.subscribed:
            self.subscribed[req.symbol] = req

        d = {
            "event": "subscribe",
            "channel": "book",
            "symbol": req.symbol,
        }
        self.send_packet(d)

        d = {
            "event": "subscribe",
            "channel": "ticker",
            "symbol": req.symbol,
        }
        self.send_packet(d)

        return int(round(time.time() * 1000))

    def resubscribe(self):
        """"""
        for req in self.subscribed.values():
            self.subscribe(req)

    def _gen_unqiue_cid(self):
        self.order_id += 1
        local_oid = time.strftime("%y%m%d") + str(self.order_id)
        return int(local_oid)

    def send_order(self, req: OrderRequest):
        orderid = self._gen_unqiue_cid()

        if req.direction == Direction.LONG:
            amount = req.volume
        else:
            amount = -req.volume

        order_type = ORDERTYPE_VT2BITFINEX[req.type]
        if self.margin:
            order_type = order_type.replace("EXCHANGE ", "")

        o = {
            "cid": orderid,
            "type": order_type,
            "symbol": "t" + req.symbol,
            "amount": str(amount),
            "price": str(req.price),
        }

        request = [0, "on", None, o]

        order = req.create_order_data(orderid, self.gateway_name)
        self.send_packet(request)

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        orderid = req.orderid
        date_str = "20" + str(orderid)[0:6]
        date = date_str[0:4] + "-" + date_str[4:6] + "-" + date_str[6:8]

        request = [
            0,
            "oc",
            None,
            {
                "cid": int(orderid),
                "cid_date": date
            }
        ]

        self.send_packet(request)

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接成功")
        self.authenticate()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")

    def on_packet(self, packet: dict):
        """"""
        if isinstance(packet, dict):
            self.on_response(packet)
        else:
            self.on_update(packet)

    def on_response(self, data):
        """"""
        if "event" not in data:
            return

        if data["event"] == "subscribed":
            symbol = str(data["symbol"].replace("t", ""))
            self.channels[data["chanId"]] = (data["channel"], symbol)

    def on_update(self, data):
        """"""
        if data[1] == "hb":
            return

        channel_id = data[0]

        if not channel_id:
            self.on_trade_update(data)
        else:
            self.on_data_update(data)

    def on_data_update(self, data):
        """"""
        channel_id = data[0]
        channel, symbol = self.channels[channel_id]
        symbol = str(symbol.replace("t", ""))

        # Get the Tick object
        if symbol in self.ticks:
            tick = self.ticks[symbol]
        else:
            tick = TickData(
                symbol=symbol,
                exchange=Exchange.BITFINEX,
                name=symbol,
                datetime=datetime.now(UTC_TZ),
                gateway_name=self.gateway_name,
            )

            self.ticks[symbol] = tick

        l_data1 = data[1]

        # Update general quote
        if channel == "ticker":
            tick.volume = float(l_data1[-3])
            tick.high_price = float(l_data1[-2])
            tick.low_price = float(l_data1[-1])
            tick.last_price = float(l_data1[-4])
            tick.open_price = float(tick.last_price - l_data1[4])

        # Update deep quote
        elif channel == "book":
            bid = self.bids.setdefault(symbol, {})
            ask = self.asks.setdefault(symbol, {})

            if len(l_data1) > 3:
                for price, count, amount in l_data1:
                    price = float(price)
                    count = int(count)
                    amount = float(amount)

                    if amount > 0:
                        bid[price] = amount
                    else:
                        ask[price] = -amount
            else:
                price, count, amount = l_data1
                price = float(price)
                count = int(count)
                amount = float(amount)

                if not count:
                    if price in bid:
                        del bid[price]
                    elif price in ask:
                        del ask[price]
                else:
                    if amount > 0:
                        bid[price] = amount
                    else:
                        ask[price] = -amount

            try:
                # BID
                bid_keys = bid.keys()
                bidPriceList = sorted(bid_keys, reverse=True)

                tick.bid_price_1 = bidPriceList[0]
                tick.bid_price_2 = bidPriceList[1]
                tick.bid_price_3 = bidPriceList[2]
                tick.bid_price_4 = bidPriceList[3]
                tick.bid_price_5 = bidPriceList[4]

                tick.bid_volume_1 = bid[tick.bid_price_1]
                tick.bid_volume_2 = bid[tick.bid_price_2]
                tick.bid_volume_3 = bid[tick.bid_price_3]
                tick.bid_volume_4 = bid[tick.bid_price_4]
                tick.bid_volume_5 = bid[tick.bid_price_5]

                # ASK
                ask_keys = ask.keys()
                askPriceList = sorted(ask_keys)

                tick.ask_price_1 = askPriceList[0]
                tick.ask_price_2 = askPriceList[1]
                tick.ask_price_3 = askPriceList[2]
                tick.ask_price_4 = askPriceList[3]
                tick.ask_price_5 = askPriceList[4]

                tick.ask_volume_1 = ask[tick.ask_price_1]
                tick.ask_volume_2 = ask[tick.ask_price_2]
                tick.ask_volume_3 = ask[tick.ask_price_3]
                tick.ask_volume_4 = ask[tick.ask_price_4]
                tick.ask_volume_5 = ask[tick.ask_price_5]
            except IndexError:
                return

        dt = datetime.now(UTC_TZ)
        tick.datetime = dt

        self.gateway.on_tick(copy(tick))

    def on_wallet(self, data):
        """"""
        # Exchange Mode
        if not self.margin and str(data[0]) != "exchange":
            return
        # Margin Mode
        elif self.margin and str(data[0]) != "margin":
            return

        accountid = str(data[1])
        account = self.accounts.get(accountid, None)
        if not account:
            account = AccountData(
                accountid=accountid,
                gateway_name=self.gateway_name,
            )

        account.balance = float(data[2])
        account.available = 0.0
        account.frozen = 0.0
        self.gateway.on_account(copy(account))

    def on_trade_update(self, data):
        """"""
        name = data[1]
        info = data[2]

        if name == "ws":
            for l in info:
                self.on_wallet(l)
            self.gateway.write_log("账户资金获取成功")
        elif name == "wu":
            self.on_wallet(info)
        elif name == "os":
            for l in info:
                self.on_order(l)
            self.gateway.write_log("活动委托获取成功")
        elif name in ["on", "ou", "oc"]:
            self.on_order(info)
        elif name == "te":
            self.on_trade(info)
        elif name == "n":
            self.on_order_error(info)

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb)
        )

    def authenticate(self):
        """
        Authenticate websocket connection to subscribe private topic.
        """
        nonce = int(time.time() * 1000000)
        authPayload = "AUTH" + str(nonce)
        signature = hmac.new(
            self.secret, authPayload.encode(), digestmod=hashlib.sha384
        ).hexdigest()

        req = {
            "apiKey": self.key,
            "event": "auth",
            "authPayload": authPayload,
            "authNonce": nonce,
            "authSig": signature
        }

        self.send_packet(req)

    def subscribe_topic(self):
        """
        Subscribe to all private topics.
        """
        req = {
            "op": "subscribe",
            "args": [
                "instrument",
                "trade",
                "orderBook10",
                "execution",
                "order",
                "position",
                "margin",
            ],
        }
        self.send_packet(req)

    def on_trade(self, data):
        """"""
        self.trade_id += 1

        if data[4] > 0:
            direction = Direction.LONG
        else:
            direction = Direction.SHORT

        trade = TradeData(
            symbol=str(data[1].replace("t", "")),
            exchange=Exchange.BITFINEX,
            orderid=data[-1],
            direction=direction,
            volume=abs(data[4]),
            price=data[5],
            tradeid=str(self.trade_id),
            datetime=generate_datetime(data[2]),
            gateway_name=self.gateway_name,
        )
        self.gateway.on_trade(trade)

    def on_order_error(self, d):
        """"""
        if d[-2] != "ERROR":
            return

        data = d[4]
        error_info = d[-1]

        # Filter cancel of non-existing order
        orderid = str(data[2])
        if orderid == "None":
            self.gateway.write_log("撤单失败，委托不存在")
            return

        if data[6] > 0:
            direction = Direction.LONG
        else:
            direction = Direction.SHORT

        order = OrderData(
            symbol=str(data[3].replace("t", "")),
            exchange=Exchange.BITFINEX,
            type=ORDERTYPE_BITFINEX2VT[data[8]],
            orderid=orderid,
            status=Status.REJECTED,
            direction=direction,
            price=float(data[16]),
            volume=abs(data[6]),
            datetime=generate_datetime(d[0]),
            gateway_name=self.gateway_name,
        )

        self.gateway.on_order(copy(order))

        self.gateway.write_log(f"委托拒单：{error_info}")

    def on_order(self, data):
        """"""
        orderid = str(data[2])

        if data[7] > 0:
            direction = Direction.LONG
        else:
            direction = Direction.SHORT

        order_status = str(data[13].split("@")[0]).replace(" ", "")
        if order_status == "CANCELED":
            dt = generate_datetime(data[5])
        else:
            dt = generate_datetime(data[4])

        order = OrderData(
            symbol=str(data[3].replace("t", "")),
            exchange=Exchange.BITFINEX,
            orderid=orderid,
            type=ORDERTYPE_BITFINEX2VT[data[8]],
            status=STATUS_BITFINEX2VT[order_status],
            direction=direction,
            price=float(data[16]),
            volume=abs(data[7]),
            traded=abs(data[7]) - abs(data[6]),
            datetime=dt,
            gateway_name=self.gateway_name,
        )

        self.gateway.on_order(copy(order))


def generate_datetime(timestamp: float) -> datetime:
    """"""
    dt = datetime.fromtimestamp(timestamp / 1000)
    dt = UTC_TZ.localize(dt)
    return dt
