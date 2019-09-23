import hashlib
import hmac
import sys
import time
from collections import defaultdict
from copy import copy
from datetime import datetime
from typing import Any, Callable, Dict, TYPE_CHECKING

from sortedcontainers import SortedSet

from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (Exchange, Product)
from vnpy.trader.object import (AccountData, ContractData, SubscribeRequest, TickData, TradeData)
from .common import (DIRECTION_BYBIT2VT, generate_timestamp, local_tz, parse_datetime, sign, utc_tz)

if TYPE_CHECKING:
    from vnpy.gateway.bybit import BybitGateway

HOST = "wss://stream.bybit.com/realtime"
TEST_HOST = "wss://stream-testnet.bybit.com/realtime"


class RawOrderInfo:

    def __init__(self, raw_data: dict):
        self.id = raw_data['id']
        self.price = raw_data['price']
        self.side = raw_data['side']  # 'Buy', 'Sell'
        self.size = raw_data.get('size', 0)

    def __lt__(self, rhs: "RawOrderInfo"):
        return self.price < rhs.price

    def __eq__(self, rhs: "RawOrderInfo"):
        return self.price == rhs.price

    def __hash__(self):
        return self.id  # price is a string and we don't known its precision


class BybitWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway: "BybitGateway"):
        """"""
        super(BybitWebsocketApi, self).__init__()

        self.server: str = ""  # REAL or TESTNET
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = b""

        self._instrument_info_data: Dict[str, dict] = defaultdict(dict)
        self._orderbook_data: Dict[str, SortedSet[RawOrderInfo]] = defaultdict(SortedSet)

        self.accounts = {}

        self._topic_callbacks = {}

    @property
    def ticks(self):
        return self.gateway.ticks

    @property
    def orders(self):
        return self.gateway.orders

    def connect(
        self, key: str, secret: str, server: str, proxy_host: str, proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret.encode()
        self.proxy_host = proxy_host
        self.proxy_port = proxy_port
        self.server = server

        self.reset_authentication()
        self.start()

    def reset_authentication(self):
        expires = generate_timestamp(30)
        d2s = f"GET/realtime{int(expires)}"
        signature = sign(self.secret, d2s.encode())
        params = f"api_key={self.key}&expires={expires}&signature={signature}"
        if self.server == "REAL":
            host = HOST
        else:
            host = TEST_HOST
        url = f'{host}?{params}'
        self.init(url, self.proxy_host, self.proxy_port)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data upate.
        """
        symbol = req.symbol
        self._subscribe_topic(f"instrument_info.100ms.{symbol}", self.on_tick)
        self._subscribe_topic(f"orderBookL2_25.{symbol}", self.on_depth)

    def on_connected(self):
        """"""
        self.gateway.write_log("Websocket API连接且认证成功")
        self._subscribe_initialize_topics()

    def on_disconnected(self):
        """"""
        self.gateway.write_log("Websocket API连接断开")
        self.reset_authentication()

    def on_packet(self, packet: dict):
        """"""
        success = packet.get('success', None)
        topic = packet.get('topic', None)
        if success is not None:
            if success is False:
                self.gateway.write_log("Websocket API报错：%s" % packet["ret_msg"])
        elif topic is not None:
            self._topic_callbacks[topic](topic, packet)
        else:
            self.gateway.write_log(f"unkonwn packet: {packet}")

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """"""
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(self.exception_detail(
            exception_type, exception_value, tb))

    def authenticate(self):
        """
        Authenticate websockey connection to subscribe private topic.
        """
        expires = int(time.time())
        method = "GET"
        path = "/realtime"
        msg = method + path + str(expires)
        signature = hmac.new(
            self.secret, msg.encode(), digestmod=hashlib.sha256
        ).hexdigest()

        req = {"op": "authKey", "args": [self.key, expires, signature]}
        self.send_packet(req)

    def _subscribe_topic(self, topic: str, callback: Callable[[str, dict], Any]):
        """
        Subscribe to all private topics.
        """
        self._topic_callbacks[topic] = callback

        req = {
            "op": "subscribe",
            "args": [topic],
        }
        self.send_packet(req)

    def _subscribe_initialize_topics(self):
        """
        Subscribe to all private topics.
        """
        self._subscribe_topic("order", self.on_order)
        self._subscribe_topic("execution", self.on_trade)
        self._subscribe_topic("position", self.on_position)

    def _get_last_tick(self, symbol: str):
        tick = self.ticks.get(symbol, None)
        if tick is None:
            # noinspection PyTypeChecker
            tick = TickData(
                symbol=symbol,
                exchange=Exchange.BYBIT,
                name=symbol,
                datetime=None,  # this will be filled before this new created tick is consumed.
                gateway_name=self.gateway_name,
            )
            self.ticks[symbol] = tick
        return tick

    def on_tick(self, topic: str, raw_data: dict):
        """"""
        # parse incremental data sent from server
        symbol = topic[22:]
        self._update_tick_incremental_data(symbol, raw_data)

        # convert dict into TickData
        last_data = self._instrument_info_data[symbol]
        tick = self._get_last_tick(symbol)
        tick.last_price = last_data["last_price_e4"] / 10000
        tick.datetime = _parse_timestamp_e6(raw_data['timestamp_e6'])
        self.gateway.on_tick(copy(tick))

    def _update_tick_incremental_data(self, symbol, raw_data):
        type_ = raw_data['type']
        data = raw_data['data']
        last_data = self._instrument_info_data[symbol]
        if type_ == 'snapshot':
            last_data.clear()
            last_data.update(data)
        elif type_ == 'delta':
            updates = data['update']
            for update in updates:
                assert update['symbol'] == symbol
                last_data.update(update)
        else:
            self.gateway.write_log(f"Unknown type {type_} in websocket_api.on_tick()")

    def on_depth(self, topic: str, raw_data: dict):
        """"""
        symbol = topic[15:]
        self._update_depth_incremental_data(symbol, raw_data)

        last_data = self._orderbook_data[symbol]

        tick = self._get_last_tick(symbol)
        for n, parsed in enumerate(last_data.islice(20, 25)):
            tick.__setattr__(f"bid_price_{5 - n}", parsed.price)
            tick.__setattr__(f"bid_volume_{5 - n}", parsed.size)

        for n, parsed in enumerate(last_data.islice(25, 30)):
            tick.__setattr__(f"ask_price_{n + 1}", parsed.price)
            tick.__setattr__(f"ask_volume_{n + 1}", parsed.size)

        tick.datetime = _parse_timestamp_e6(raw_data['timestamp_e6'])
        self.gateway.on_tick(copy(tick))

    def _update_depth_incremental_data(self, symbol, raw_data):
        type_ = raw_data['type']
        data = raw_data['data']
        last_data = self._orderbook_data[symbol]
        if type_ == 'snapshot':
            last_data.clear()
            for item in data:
                assert item['symbol'] == symbol
                parsed = RawOrderInfo(item)
                last_data.add(parsed)
        elif type_ == 'delta':
            deletes = data['delete']
            for delete in deletes:
                assert delete['symbol'] == symbol
                parsed = RawOrderInfo(delete)
                last_data.remove(parsed)

            updates = data['update']
            for update in updates:
                assert update['symbol'] == symbol
                parsed = RawOrderInfo(update)
                last_data.remove(parsed)
                last_data.add(parsed)

            inserts = data['insert']
            for insert in inserts:
                assert insert['symbol'] == symbol
                parsed = RawOrderInfo(insert)
                last_data.add(parsed)
        else:
            self.gateway.write_log(f"Unknown type {type_} in websocket_api.on_tick()")

    def on_trade(self, topic: str, raw_data: dict):
        """"""
        for data in raw_data['data']:
            order_id = data['order_link_id']
            if not order_id:
                order_id = data['order_id']
            trade = TradeData(
                symbol=data["symbol"],
                exchange=Exchange.BYBIT,
                orderid=order_id,
                tradeid=data['exec_id'],
                direction=DIRECTION_BYBIT2VT[data["side"]],
                price=data["price"],
                volume=data["exec_qty"],
                time=parse_datetime(data["trade_time"]),
                gateway_name=self.gateway_name,
            )

            self.gateway.on_trade(trade)

    def on_order(self, topic: str, raw_data: dict):
        """"""
        for data in raw_data['data']:
            print(data)
            order = self.gateway.parse_order_data(data, 'timestamp')

            self.gateway.on_order(copy(order))

    def on_position(self, topic: str, raw_data: dict):
        """"""
        for data in raw_data['data']:
            p1, p2 = self.gateway.parse_position_data(data)
            self.gateway.on_position(p1)
            if p2:
                self.gateway.on_position(p2)

    def on_account(self, d):
        """"""
        accountid = str(d["account"])
        account = self.accounts.get(accountid, None)
        if not account:
            account = AccountData(accountid=accountid,
                                  gateway_name=self.gateway_name)
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
            exchange=Exchange.BYBIT,
            name=d["symbol"],
            product=Product.FUTURES,
            pricetick=d["tickSize"],
            size=d["lotSize"],
            stop_supported=True,
            net_position=True,
            history_data=True,
            gateway_name=self.gateway_name,
        )

        self.gateway.on_contract(contract)

    def _ping(self):
        super()._ping()
        self.send_packet({'op': 'ping'})


def _parse_timestamp_e6(timestamp: int):
    return datetime.fromtimestamp(timestamp / 1_000_000, utc_tz).astimezone(tz=local_tz)
