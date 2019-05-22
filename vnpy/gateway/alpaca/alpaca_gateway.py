# encoding: UTF-8
"""
    please install alpaca_trade_api first
    Author: vigarbuaa
"""

import hashlib
import hmac
import sys
import threading
import time
from copy import copy
from queue import Empty, Queue
from multiprocessing.dummy import Pool
from datetime import datetime
from urllib.parse import urlencode
from vnpy.api.rest import Request, RestClient
from vnpy.event import Event
from vnpy.trader.event import EVENT_TIMER
from vnpy.api.websocket import WebsocketClient
import alpaca_trade_api as tradeapi
from alpaca_trade_api.stream2 import StreamConn
import asyncio

from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    PositionData, AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
)

BASE_URL = "https://paper-api.alpaca.markets"
KEY = "https://api.alpaca.com/"
SECRET = ""

REST_HOST = "https://paper-api.alpaca.markets"
WEBSOCKET_HOST = "https://api.alpaca.com/ws/2"

STATUS_ALPACA2VT = {
    "new": Status.SUBMITTING,
    "open": Status.NOTTRADED,
    "part_filled": Status.PARTTRADED,
    "filled": Status.ALLTRADED,
    "cancelled": Status.CANCELLED,
    "cancelling": Status.CANCELLED,
    "failure": Status.REJECTED,
}
# PRICETYPE_VT2ALPACA = {
#    PriceType.LIMIT: "EXCHANGE LIMIT",
#    PriceType.MARKET: "EXCHANGE MARKET"}
DIRECTION_VT2ALPACA = {Direction.LONG: "buy", Direction.SHORT: "sell"}
DIRECTION_ALPACA2VT = {"buy": Direction.LONG, "sell": Direction.SHORT,
                       "long": Direction.LONG, "short": Direction.SHORT}

ORDERTYPE_VT2ALPACA = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market"
}
ORDERTYPE_ALPACA2VT = {v: k for k, v in ORDERTYPE_VT2ALPACA.items()}


class AlpacaGateway(BaseGateway):
    """
    VN Trader Gateway for Alpaca connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "session": 3,
        "proxy_host": "127.0.0.1",
        "proxy_port": 1080,
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(AlpacaGateway, self).__init__(event_engine, "ALPACA")

        self.rest_api = None
        self.order_map = {}
        self.queue = Queue()
        self.active = False
        self.pool = None
        self.order_id = 1_000_000
        self.count = 0

    def add_task(self, func, *args):
        """"""
        self.queue.put((func, [*args]))

    def run(self):
        """"""
        while self.active:
            try:
                func, args = self.queue.get(timeout=0.1)
                func(*args)
            except Empty:
                pass

    def connect(self, setting: dict):
        """"""
        self.key = setting["key"]
        self.secret = setting["secret"]
        self.session = setting["session"]
        self.proxy_host = setting["proxy_host"]
        self.proxy_port = setting["proxy_port"]

        print("starting rest api")
        self.rest_api = tradeapi.REST(self.key, self.secret, REST_HOST)
        self.active = True
        self.pool = Pool(5)
        self.pool.apply_async(self.run)
        print("starting stream api")
        t = threading.Thread(target=self.streaming_handler)
        t.daemon = True
        t.start()
        print("rest|stream api done")

        # Put connect task into quque.
        self.add_task(self.query_account)
        # self.add_task(self.query_contract)
        self.add_task(self.query_position)
        self.add_task(self.query_order)

        self.init_query()
        

    def streaming_handler(self):
        stream_api = AlpacaWebsocketApi(self.key, self.secret, REST_HOST,self)
        stream_api.start()

    def query_account(self):
        """"""
        data = self.rest_api.get_account()
        print("deubg query_account: ", data)
        account = AccountData(
            accountid=data.id,
            balance=float(data.cash),
            frozen=float(data.cash) - float(data.buying_power),
            gateway_name=self.gateway_name
        )
        self.on_account(account)
        self.write_log("账户资金查询成功")

    def query_contract(self):
        """"""
        data = self.rest_api.list_assets()
        for instrument_data in data:
            symbol = instrument_data.symbol
            contract = ContractData(
                symbol=symbol,
                exchange=Exchange.ALPACA,  # vigar, need to fix to nasdq ...
                name=symbol,
                product=Product.SPOT,
                size=1,
                pricetick=0.01,
                gateway_name=self.gateway_name
            )
            self.on_contract(contract)
        self.write_log("合约信息查询成功")

    def _gen_unqiue_cid(self):
        # return int(round(time.time() * 1000))
        self.order_id = self.order_id + 1
        local_oid = time.strftime("%y%m%d%H%M%S") + "_" + str(self.order_id)
        return int(local_oid)

    def send_order(self, req: OrderRequest):
        """"""
        local_id = self._gen_unqiue_cid()
        order = req.create_order_data(local_id, self.gateway_name)
        self.on_order(order)
        #self.add_task(self._send_order, req, local_id)
        print("debug send order: ", order.__dict__)
        self._send_order(req, local_id)
        return order.vt_orderid

    # need config
    def _send_order(self, req: OrderRequest, local_id):
        orderid = local_id
        print("debug in _send_order: ", orderid)
        if req.direction == Direction.LONG:
            amount = req.volume
        else:
            amount = -req.volume
        order_type = ORDERTYPE_VT2ALPACA[req.type]
        order_side = DIRECTION_VT2ALPACA[req.direction]

        order = None
        if req.type == OrderType.LIMIT:
            order = self.rest_api.submit_order(
                symbol='b0b6dd9d-8b9b-48a9-ba46-b9d54906e415',
                qty=abs(int(amount)),
                side=order_side,
                type=order_type,
                time_in_force='day',
                client_order_id=str(orderid),
                limit_price=float(req.price),
            )
            print("debug 1", order)
        else:
            order = self.rest_api.submit_order(
                symbol='b0b6dd9d-8b9b-48a9-ba46-b9d54906e415',
                qty=abs(int(amount)),
                side=order_side,
                type=order_type,
                time_in_force='day',
                client_order_id=str(orderid)
            )
            print("debug 2", order)
        return

    # fix
    def subscribe(self, req: SubscribeRequest):
        """"""
        pass

    def query_order(self):
        """"""
        print("come to query_order")
        try:
            data = self.rest_api.list_orders()
            print("queryorders: ", data)
            data = sorted(data, key=lambda x: x.created_at, reverse=False)
            for d in data:
                print("debug order in query_order: ", d)
                order = OrderData(
                    symbol=d.symbol,
                    orderid=d.client_order_id,
                    exchange=Exchange.ALPACA,
                    direction=DIRECTION_ALPACA2VT[d.side],
                    price=d.limit_price if d.limit_price else 0.0,
                    volume=d.qty,
                    # orderType: ORDERTYPE_ALPACA2VT[d.order_type],
                    # traded=i.filled,
                    status=STATUS_ALPACA2VT[d.status],
                    #time=datetime.fromtimestamp(i.created_at / 1000).strftime("%H:%M:%S"),
                    gateway_name=self.gateway_name,
                )
                #self.ID_TIGER2VT[str(i.order_id)] = local_id
                self.on_order(order)

        except:  # noqa
            traceback.print_exc()
            self.write_log("查询委托失败")
            return

        # self.process_order(data)
        # self.process_deal(data)

    # fix
    def cancel_order(self, req: CancelRequest):
        """"""
        print("debug _cancel_order: ", req)
        order = self.rest_api.get_order_by_client_order_id(req.orderid)
        order_id = order.id
        print("debug cancel order: localid: ",
              req.orderid, "--remote_id--", order_id)
        self.rest_api.cancel_order(order_id)

    def query_position(self):
        """"""
        data = self.rest_api.list_positions()
        print("debug query_pos: ", data)
        print("debug query_pos: ", type(data))
        for d in data:
            print("debug query_pos  3: ", d)
            position = PositionData(
                symbol=d.symbol,
                exchange=Exchange.ALPACA,
                direction=DIRECTION_ALPACA2VT[d.side],
                volume=d.qty,
                price=d.avg_entry_price,
                pnl=d.unrealized_pl,
                gateway_name=self.gateway_name,
            )
            print("debug query_position: ", position)
            self.on_position(position)

    def close(self):
        """"""
        self.rest_api.stop()
    
    def init_query(self):
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
    
    def process_timer_event(self, event: Event):
        """"""
        self.count += 1
        if self.count < 5:
            return

        self.query_account()
        self.query_position()


class AlpacaWebsocketApi(object):
    """"""

    def __init__(self, key, secret, base_url,gateway):
        """"""
        self.key = key
        self.secret = secret
        self.base_url = base_url
        self.conn=None
        self.trade_count = 10000
        self.connect_time = None
        self.gateway=gateway

    def start(self):
        self.conn = StreamConn(self.key, self.secret, self.base_url)
        self.conn.on('authenticated')(self.on_auth)
        self.conn.on(r'Q.*')(self.on_q)
        self.conn.on(r'account_updates')(self.on_account_updates)
        self.conn.on(r'trade_updates')(self.on_trade_updates)
        self.connect_time = int(datetime.now().strftime("%y%m%d%H%M%S"))
        self.run()

    def run(self):
        print("---------------stream api --running--------------------")
        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)
        self.conn.run(['account_updates','trade_updates','authorized','^Q.'])

    async def on_account_updates(self,conn, channel, account):
        print('---account---', account)

    async def on_trade_updates(self,conn, channel, trade_raw):
        print('on_trade_updates', trade_raw)
        print('trade_raw event:',trade_raw.event)
        print('trade_raw order:',trade_raw.order)
        event = trade_raw.event
        ret_order=trade_raw.order

        if event == "fill":
            self.trade_count += 1
            tradeid = f"{self.connect_time}{self.trade_count}"
            trade = TradeData(
                symbol=ret_order['symbol'],
                exchange=Exchange.ALPACA,  # vigar, need to fix to nasdq ...
                direction=DIRECTION_ALPACA2VT[ret_order['side']],
                tradeid=tradeid,
                orderid=ret_order['id'],
                price=float(trade_raw.price),
                volume=float(ret_order['qty']),
                time=trade_raw.timestamp[11:19],
                gateway_name=self.gateway.gateway_name,
            )
            print('call gateay on_trade:',trade)
            self.gateway.on_trade(trade)
        else:
            print("trade event is not null")

    async def on_auth(self,conn, stream, msg):
        print('on_auth stream', stream, "  [msg]:", msg)

    async def on_q(self,conn, subject, data):
        print('on_auth subject', subject, "  [data]:", data)

    async def on_bars(self,conn, channel, bar):
        print('on_bars channel:', channel, "  [bar]:", bar)