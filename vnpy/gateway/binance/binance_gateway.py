# encoding: UTF-8

"""
币安交易接口
"""

import re
import urllib
import base64
import json
import zlib
import hashlib
import hmac
import time
from copy import copy
from datetime import datetime
from threading import Thread

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


REST_HOST = "https://www.binance.com"
WEBSOCKET_TRADE_HOST = "wss://stream.binance.com:9443/ws/"                  # Account and Order
WEBSOCKET_DATA_HOST = "wss://stream.binance.com:9443/stream?streams="       # Market Data

STATUS_BINANCE2VT = {
    "NEW": Status.NOTTRADED,
    "PARTIALLY_FILLED": Status.PARTTRADED,
    "FILLED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
    "REJECTED": Status.REJECTED
}

ORDERTYPE_VT2BINANCE = {
    OrderType.LIMIT: "LIMIT",
    OrderType.MARKET: "MARKET",
    OrderType.STOP: "STOP_LOSS", 
}

ORDERTYPE_BINANCE2VT = {v: k for k, v in ORDERTYPE_VT2BINANCE.items()}

DIRECTION_VT2BINANCE = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL"
}

DIRECTION_BINANCE2VT = {v: k for k, v in DIRECTION_VT2BINANCE.items()}

binance_symbols = set()
symbol_name_map = {}


class BinanceGateway(BaseGateway):
    """
    VN Trader Gateway for Binance connection.
    """

    default_setting = {
        "key": "",
        "secret": "",
        "session_number": 3,
        "proxy_host": "127.0.0.1",
        "proxy_port": 1080,
    }

    exchanges = [Exchange.BINANCE]

    def __init__(self, event_engine):
        """Constructor"""
        super(BinanceGateway, self).__init__(event_engine, "BINANCE")

        self.order_manager = LocalOrderManager(self)

        self.rest_api = BinanceRestApi(self)
        self.trade_ws_api = BinanceTradeWebsocketApi(self)
        self.market_ws_api = BinanceDataWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        session_number = setting["session_number"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        self.rest_api.connect(key, secret, session_number,
                              proxy_host, proxy_port)
        #self.trade_ws_api.connect(key, secret, proxy_host, proxy_port)
        self.market_ws_api.connect(key, secret, proxy_host, proxy_port)

        #self.init_query()

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
        self.rest_api.query_account()

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

class BinanceRestApi(RestClient):
    """
    BINANCE REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(BinanceRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.order_manager = gateway.order_manager
        self.trade_ws_api = BinanceTradeWebsocketApi(self.gateway)

        self.host = ""
        self.key = ""
        self.secret = ""
        self.userStreamKey = ""
        self.keepaliveCount = 0
        self.recvWindow = 5000
        self.time_offset = 0

        self.cancel_requests = {}
        self.orders = {}

    def sign(self, request):
        """
        Generate BINANCE signature.
        """
        if request.params:
            path = request.path + "?" + urllib.parse.urlencode(request.params)
        else:
            request.params = dict()
            path = request.path
        security = "NONE"
        if request.data:
            security = request.data['security']
        
        if security == "SIGNED":
            timestamp = int(time.time() * 1000)
            if self.time_offset > 0:
                timestamp -= abs(self.time_offset)
            elif self.time_offset < 0:
                timestamp += abs(self.time_offset)
            request.params['timestamp'] = timestamp
            request.params['recvWindow'] = self.recvWindow

            query = urllib.parse.urlencode(sorted(request.params.items()))
            signature = hmac.new(self.secret, query.encode('utf-8'), hashlib.sha256).hexdigest()
            query += "&signature={}".format(signature)
            path = request.path + "?" + query
        request.path = path
        request.params = {}
        request.data = {}
        # Add headers
        headers = {
            "Content-Type": "application/x-www-form-urlencoded",
            "Accept": "application/json",
            "X-MBX-APIKEY": self.key
        }
        if security == "SIGNED" or security == "API-KEY":
            request.headers = headers
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
        self.secret = secret.encode()
        self.proxy_port = proxy_port
        self.proxy_host = proxy_host 

        self.host, _ = _split_url(REST_HOST)

        self.init(REST_HOST, proxy_host, proxy_port)
        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

        self.query_time()
        self.query_account()
        self.query_order()
        self.query_contract()
        self.start_userStream()
    
    def query_time(self):
        """"""
        data = {
            "security": "NONE"
        }
        path = '/api/v1/time'
        return self.add_request(
            "GET",
            path,
            callback=self.on_query_time,
            data=data
        )
    
    def query_account(self):
        """"""
        data = {
            "security": "SIGNED"
        }
        self.add_request(
            method="GET",
            path="/api/v3/account",
            callback=self.on_query_account,
            data=data
        )

    def query_order(self):
        """"""
        data = {
            "security": "SIGNED"
        }
        self.add_request(
            method="GET",
            path="/api/v3/openOrders",
            callback=self.on_query_order,
            data=data
        )

    def query_contract(self):
        """"""
        data = {
            "security": "NONE"
        }
        self.add_request(
            method="GET",
            path="/api/v1/exchangeInfo",
            callback=self.on_query_contract,
            data=data
        )

    def send_order(self, req: OrderRequest):
        """"""
        local_orderid = self.order_manager.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.time = datetime.now().strftime("%H:%M:%S")

        data = {
            "security": "SIGNED"
        }

        params = {
            "symbol": req.symbol,
            "timeInForce": "GTC",
            "side": DIRECTION_VT2BINANCE[req.direction],
            "type": ORDERTYPE_VT2BINANCE[req.type],
            "price": str(req.price),
            "quantity": str(req.volume)
        }

        self.add_request(
            method="POST",
            path="/api/v3/order",
            callback=self.on_send_order,
            data=data,
            params=params,
            extra=order,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        self.order_manager.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)

        data = {
            "security": "SIGNED"
        }
        params = {
            "symbol": req.symbol,
            "orderId": req.orderid
        }
        self.add_request(
            method="DELETE",
            path="/api/v3/order",
            callback=self.on_cancel_order,
            params=params,
            data=data,
            extra=req
        )

    def start_userStream(self):
        """"""
        data = {
            "security": "API-KEY"
        }
        self.add_request(
            method="POST",
            path='/api/v1/userDataStream',
            callback=self.on_start_userStream,
            data=data
        )

    def keepalive_userStream(self):
        """"""
        self.keepaliveCount += 1
        if self.keepaliveCount < 1800:
            return
        data = {
            "security": "SIGNED"
        }
        params = {
            'listenKey': self.userStreamKey
        }
        self.add_request(
            method='PUT', 
            path='/api/v1/userDataStream', 
            callback=self.on_keepalive_userStream,
            params=params, 
            data=data
        )

    def close_userStream(self, listenKey):
        """"""
        data = {
            "security": "SIGNED"
        }
        params = {
            'listenKey': listenKey
        }
        self.add_request(
            method='DELETE',
            path='/api/v1/userDataStream',
            callback=self.on_close_userStream,
            params=params,
            data=data
        ) 

    def on_query_time(self, data, request):
        """"""
        time_now = int(time.time() * 1000)
        time_server = int(data["serverTime"])
        server_local_time = time.localtime(float(time_server / 1000))
        now_local_time = time.localtime(float(time_now / 1000))
        self.time_offset = time_now - time_server
        server_time = time.strftime("%Y-%m-%d %H:%M:%S", server_local_time)
        local_time = time.strftime("%Y-%m-%d %H:%M:%S", now_local_time)
        msg = f"服务器时间：{server_time}，本机时间：{local_time}"
        self.gateway.write_log(msg)

    def on_query_account(self, data, request):
        """"""
        for account_data in data["balances"]:
            account = AccountData(
                accountid=account_data["asset"],
                balance=float(account_data["free"]),
                frozen=float(account_data["locked"]),
                gateway_name=self.gateway_name
            )
            self.gateway.on_account(account)

        self.gateway.write_log("账户资金查询成功")

    def on_query_order(self, data, request):
        """"""
        for d in data:
            sys_orderid = d["orderId"]
            local_orderid = self.order_manager.get_local_orderid(sys_orderid)

            direction = DIRECTION_BINANCE2VT[d["side"]]
            order_type = ORDERTYPE_BINANCE2VT[d["type"]]
            dt = datetime.fromtimestamp(d["time"] / 1000)
            time = dt.strftime("%Y-%m-%d %H:%M:%S")

            order = OrderData(
                orderid=sys_orderid,
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

        self.gateway.write_log("委托信息查询成功")

    def on_query_contract(self, data, request):
        """"""
        for d in data["symbols"]:
            base_currency = d["baseAsset"]
            quote_currency = d["quoteAsset"]
            name = f"{base_currency.upper()}/{quote_currency.upper()}"
            pricetick = 0
            min_volume = 0
            for f in d["filters"]:
                if f["filterType"] == "PRICE_FILTER":
                    pricetick = f["tickSize"]
                if f["filterType"] == "LOT_SIZE":
                    min_volume = f["stepSize"]
            contract = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                name=name,
                pricetick=pricetick,
                size=1,
                min_volume=min_volume,
                product=Product.SPOT,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)

            binance_symbols.add(contract.symbol)
            symbol_name_map[contract.symbol] = contract.name

        self.gateway.write_log("合约信息查询成功")

    def on_send_order(self, data, request):
        """"""
        order = request.extra
        if self.check_error(data, "委托"):
            order.status = Status.REJECTED
            self.order_manager.on_order(order)
            return
        order.status = STATUS_BINANCE2VT.get(data["status"], None)
        sys_orderid = data["orderId"]
        self.order_manager.on_order(order)
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
    
    def on_start_userStream(self, data, request):
        self.userStreamKey = data['listenKey']
        self.keepaliveCount = 0
        url = WEBSOCKET_TRADE_HOST + self.userStreamKey
        self.trade_ws_api.connect(
            key=self.key, 
            secret=self.secret, 
            url=url, 
            proxy_host=self.proxy_host, 
            proxy_port=self.proxy_port)

    def on_keepalive_userStream(self, data, request):
        self.gateway.write_log("交易推送刷新成功")
        if self.keepaliveCount >= 1800:
            self.keepaliveCount = 0
            self.keepalive_userStream(self.userStreamKey)

    def on_close_userStream(self, listenKey):
        self.gateway.write_log("交易推送关闭")
    
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
        super(BinanceWebsocketApiBase, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        #self.sign_host = ""
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
        
        #host, path = _split_url(url)
        #self.sign_host = host
        #self.path = path

        self.init(url, proxy_host, proxy_port)
        self.start()

    def login(self):
        """"""
        params = {"op": "auth"}
        #params.update(create_signature(self.key, "GET", self.sign_host, self.path, self.secret))        
        return self.send_packet(params)

    def on_login(self, packet):
        """"""
        pass

    @staticmethod
    def unpack_data(data):
        """"""
        print("==============unpack_data============")
        print(data)
        return json.loads(data)
        #return json.loads(zlib.decompress(data, zlib.Z_BEST_COMPRESSION))

    def on_packet(self, packet):
        """"""
        print("=============on_packet=============")
        print("event type:"+packet["e"])
        print(packet)
        #if packet["e"] == "executionReport":
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


class BinanceTradeWebsocketApi(BinanceWebsocketApiBase):
    """"""
    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.order_manager = gateway.order_manager
        self.order_manager.push_data_callback = self.on_data

        self.req_id = 0

    def connect(self, key, secret, url, proxy_host, proxy_port):
        """"""
        super().connect(key, secret, url, proxy_host, proxy_port)
        self.gateway.write_log("交易Websocket API连接成功")
        self.gateway.rest_api.keepalive_userStream()

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
        pass

    def on_login(self):
        """"""
        pass

    def on_data(self, packet):  # type: (dict)->None
        """"""
        print("==========on_data1=========")
        # push order data change
        if packet["e"] == "executionReport":
            order = OrderData(
                    symbol=packet["s"],
                    exchange=Exchange.BINANCE,
                    orderid=packet["i"],
                    status=STATUS_BINANCE2VT.get(packet["X"], None),
                    traded=float(packet["Z"]),
                    price=float(packet["L"]),
                    time=packet["O"],
                    gateway_name=self.gateway_name
                )
            self.on_order(order)
        # push account data change
        if packet["e"] == "outboundAccountInfo":
            for account_data in packet["B"]:
                account = AccountData(
                    accountid=account_data["a"],
                    balance=float(account_data["f"]),
                    frozen=float(account_data["l"]),
                    gateway_name=self.gateway_name
                )
                self.on_account(account)

    def on_order(self, data: dict):
        """"""
        sys_orderid = data.orderid
        
        order = self.order_manager.get_order_with_sys_orderid(sys_orderid)
        if not order:
            self.order_manager.add_push_data(sys_orderid, data)
            return

        # Push order event
        order.traded = data.traded
        order.status = data.status
        self.order_manager.on_order(order)
        
        # Push trade event
        traded_volume = data.traded
        if not traded_volume:
            return

        trade = TradeData(
            symbol=order.symbol,
            exchange=Exchange.BINANCE,
            orderid=order.orderid,
            direction=order.direction,
            price=float(order.price),
            volume=float(order.traded),
            time=datetime.now().strftime("%H:%M:%S"),
            gateway_name=self.gateway_name,
        )    
        self.gateway.on_trade(trade)

    def on_account(self, data: dict):
        """"""
        self.gateway.on_account(data)

class BinanceDataWebsocketApi(BinanceWebsocketApiBase):
    """"""

    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.req_id = 0
        self.ticks = {}

    def connect(self, key: str, secret: str, proxy_host: str, proxy_port: int):
        """"""
        super().connect(key, secret, WEBSOCKET_DATA_HOST, proxy_host, proxy_port)
        self.gateway.write_log("行情Websocket API连接成功")

    def on_connected(self):
        """"""
        pass
        
    def subscribe(self, req: SubscribeRequest):
        """"""
        symbol = req.symbol
        print("============BinanceDataWebsocketApi.subscribe===========")
        print("symbol"+symbol)
        # Create tick data buffer
        tick = TickData(
            symbol=symbol,
            name=symbol_name_map.get(symbol, ""),
            exchange=Exchange.BINANCE,
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
        print("===================on_data=====================")
        print(packet)
    
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