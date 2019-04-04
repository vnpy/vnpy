# encoding: UTF-8

"""
火币交易接口
"""

import hashlib
import hmac
from copy import copy
from datetime import datetime

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Product,
    Status,
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    LogData,
)

import re
import urllib
import base64
import json
import zlib
from vnpy.event.engine import Event, EVENT_TIMER
from vnpy.trader.event import EVENT_LOG


REST_HOST = "https://api.huobi.pro"
WEBSOCKET_MARKET_HOST = "wss://api.huobi.pro/ws"       # 行情
WEBSOCKET_TRADE_HOST = "wss://api.huobi.pro/ws/v1"     # 资金和委托

STATUS_HUOBI2VT = {
    "submitted": Status.SUBMITTING,
    "partial-filled": Status.PARTTRADED,
    "filled": Status.ALLTRADED,
    "cancelling": Status.CANCELLED,
    "partial-canceled": Status.CANCELLED,
    "canceled": Status.CANCELLED,
}


class HuobiGateway(BaseGateway):
    """
    VN Trader Gateway for Huobi connection.
    """

    default_setting = {
        "ID": "",
        "Secret": "",
        "Symbols": "",
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(HuobiGateway, self).__init__(event_engine, "HUOBI")

        self.local_id = 10000

        self.accountDict = {}
        self.orderDict = {}
        self.localOrderDict = {}
        self.orderLocalDict = {}

        self.qry_enabled = False

        self.rest_api = HuobiRestApi(self)
        self.trade_ws_api = HuobiTradeWebsocketApi(self)
        self.market_ws_api = HuobiMarketWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["ID"]
        secret = setting["Secret"]
        symbols = setting["Symbols"]
        
        self.rest_api.connect(symbols, secret, key)
        self.trade_ws_api.connect(symbols, secret, key)
        self.market_ws_api.connect(symbols, secret, key)
        # websocket will push all account status on connected, including asset, position and orders.

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
        pass

    def close(self):
        """"""
        self.rest_api.stop()
        self.trade_ws_api.stop()
        self.market_ws_api.stop()

    def init_query(self):
        """初始化连续查询"""
        if self.qry_enabled:
            # 需要循环的查询函数列表
            self.qry_functionList = [self.qry_info]

            self.qry_count = 0           # 查询触发倒计时
            self.qry_trigger = 1         # 查询触发点
            self.qry_next_function = 0    # 上次运行的查询函数索引

            self.start_query()

    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qry_count += 1

        if self.qry_count > self.qry_trigger:
            # 清空倒计时
            self.qry_count = 0

            # 执行查询函数
            function = self.qry_functionList[self.qry_next_function]
            function()

            # 计算下次查询函数的索引，如果超过了列表长度，则重新设为0
            self.qry_next_function += 1
            if self.qry_next_function == len(self.qry_functionList):
                self.qry_next_function = 0

    def start_query(self):
        """启动连续查询"""
        self.event_engine.register(EVENT_TIMER, self.query)

    def set_qry_enabled(self, qry_enabled):
        """设置是否要启动循环查询"""
        self.qry_enabled = qry_enabled

    def write_log(self, msg):
        """"""
        log = LogData()
        log.log_content = msg
        log.gateway_name = self.gateway_name
        
        event = Event(EVENT_LOG)
        event.dict_["data"] = log
        self.event_engine.put(event)


class HuobiRestApi(RestClient):
    """
    HUOBI REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super(HuobiRestApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.symbols = []
        self.key = ""
        self.secret = ""
        self.sign_host = ""

        self.account_id = ""
        self.cancelReqDict = {}
        self.orderBufDict = {}

        self.accountDict = gateway.accountDict
        self.orderDict = gateway.orderDict
        self.orderLocalDict = gateway.orderLocalDict
        self.localOrderDict = gateway.localOrderDict

        self.account_id = ""
        self.cancelReqDict = {}
        self.orderBufDict = {}

    def sign(self, request):
        """
        Generate HUOBI signature.
        """

        request.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36"
        }
        params_with_signature = create_signature(self.key, request.method, self.sign_host, request.path, self.secret, request.params)
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
        symbols,
        session_number=3,
    ):
        """
        Initialize connection to REST server.
        """
        self.key = key
        self.secret = secret
        self.symbols = symbols

        host, path = _split_url(REST_HOST)
        self.init(REST_HOST)
        
        self.sign_host = host
        self.start(session_number)

        self.gateway.write_log("REST API启动成功")

    def query_account(self):
        """"""
        self.add_request(
            method="GET",
            path="/v1/account/accounts",
            callable=self.on_query_account
        )

    def query_account_balance(self):
        """"""
        # path = "/v1/account/accounts/%s/balance" %self.account_id
        path = f"/v1/account/accounts/{self.account_id}/balance"
        self.add_request(
            method="GET", 
            path=path, 
            callable=self.on_query_account_balance
        )

    def query_order(self):
        """"""
        path = "/v1/order/orders"
        
        today_date = datetime.now().strftime("%Y-%m-%d")
        states_active = "submitted, partial-filled"
        
        for symbol in self.symbols:
            params = {
                "symbol": symbol,
                "states": states_active,
                "end_date": today_date
            }
            self.add_request(
                method="GET", 
                path=path, 
                callable=self.on_query_order, 
                params=params
            )
            
    def query_contract(self):
        """"""
        self.add_request(
            method="GET", 
            path="/v1/common/symbols", 
            callable=self.on_query_contract
        )

    def send_order(self, req: OrderRequest):
        """"""
        self.gateway.local_id += 1

        local_id = str(self.gateway.local_id)

        if req.direction == Direction.LONG:
            type_ = "buy-limit"
        else:
            type_ = "sell-limit"

        data = {
            "account-id": self.account_id,
            "amount": str(req.volume),
            "symbol": req.symbol,
            "type": type_,
            "price": str(req.price),
            "source": "api"
        }
        path = "/v1/order/orders/place"

        self.add_request(
            method="POST", 
            path=path, 
            callable=self.on_send_order, 
            data=data, 
            extra=local_id,
        )

        order = OrderData(
            symbol=req.symbol,
            exchange=Exchange.HUOBI,
            orderid=local_id,
            direction=req.direction,
            price=req.price,
            volume=req.volume,
            time=datetime.now(),
            gateway_name=self.gateway_name,            
        )

        self.orderBufDict[local_id] = order

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        local_id = req.orderid
        order_id = self.localOrderDict.get(local_id, None)
        
        if order_id:
            path = f"/v1/order/orders/{order_id}/submitcancel" 
            self.add_request(
                method="POST", 
                path=path, 
                callable=self.on_cancel_order,
            )
            
            if local_id in self.cancelReqDict:
                del self.cancelReqDict[local_id]
        else:
            self.cancelReqDict[local_id] = req             

    def on_query_account(self, data, request):  # type: (dict, Request)->None
        """"""
        for d in data["data"]:
            if str(d["type"]) == "spot":
                self.account_id = str(d["id"])
                self.gateway.write_log(f"账户代码{self.account_id}查询成功")        
        
        self.query_account_balance()

    def on_query_account_balance(self, data, request):  # type: (dict, Request)->None
        """"""
        status = data.get("status", None)
        if status == "error":
            msg = "错误代码：%s, 错误信息：%s" % (data["err-code"], data["err-msg"])
            self.gateway.write_log(msg)
            return
        
        self.gateway.write_log(u"资金信息查询成功")
        
        for d in data["data"]["list"]:
            currency = d["currency"]
            account = self.accountDict.get(currency, None)

            if not account:
                account = AccountData(
                    account_id=d["currency"],
                    gateway_name=self.gateway_name,
                    available=float(d["balance"]) if d["type"] == "trade" else 0.0,
                    margin=float(d["balance"]) if d["type"] == "frozen" else 0.0,
                    balance=account.margin + account.available,
                )               
                self.accountDict[currency] = account

        for account in self.accountDict.values():
            self.gateway.on_account(account)   
        
        self.query_order()

    def on_query_order(self, data, request):  # type: (dict, Request)->None
        """"""
        status = data.get("status", None)
        if status == "error":
            msg = "错误代码：%s, 错误信息：%s" % (data["err-code"], data["err-msg"])
            self.gateway.write_log(msg)
            return
        
        symbol = request.params["symbol"]
        self.gateway.write_log(f"{symbol}委托信息查询成功")
        
        data["data"].reverse()
        for d in data["data"]:
            order_id = str(d["id"])
            self.gateway.local_id += 1
            local_id = str(self.gateway.local_id)

            self.orderLocalDict[order_id] = local_id
            self.localOrderDict[local_id] = order_id

            if "buy" in d["type"]:
                direction = Direction.LONG
            else:
                direction = Direction.SHORT

            if d["canceled-at"]:
                time = datetime.fromtimestamp(d["canceled-at"] / 1000).strftime("%H:%M:%S")
            else:
                time = datetime.fromtimestamp(d["created-at"] / 1000).strftime("%H:%M:%S")

            order = OrderData(
                orderid=local_id,
                symbol=d["symbol"],
                exchange=Exchange.HUOBI,
                price=float(d["price"]),
                volume=float(d["amount"]),
                direction=direction,
                traded=float(d["field-amount"]),
                status=STATUS_HUOBI2VT.get(d["state"], None),
                time=time,
                gateway_name=self.gateway_name,

            )

            self.orderDict[order_id] = order
            self.gateway.on_order(order)

    def on_query_contract(self, data, request):  # type: (dict, Request)->None
        """"""
        status = data.get("status", None)
        if status == "error":
            msg = "错误代码：%s, 错误信息：%s" % (data["err-code"], data["err-msg"])
            self.gateway.write_log(msg)
            return
        
        self.gateway.write_log("合约信息查询成功")
        
        for d in data["data"]:
            contract = ContractData(
                symbol=d["base-currency"] + d["quote-currency"],
                exchange=Exchange.HUOBI,
                name="/".join([d["base-currency"].upper(), d["quote-currency"].upper()]),
                pricetick=1 / pow(10, d["price-precision"]),
                size=1 / pow(10, d["amount-precision"]),
                product=Product.SPOT,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_contract(contract)
            
        self.query_account()        

    def on_send_order(self, data, request):  # type: (dict, Request)->None
        """"""
        local_id = request.extra
        order = self.orderBufDict[local_id]
        
        status = data.get("status", None)
        
        if status == "error":
            msg = "错误代码：%s, 错误信息：%s" % (data["err-code"], data["err-msg"])
            self.gateway.write_log(msg)
                
            order.status = Status.REJECTED
            self.gateway.on_order(order)
            return
        
        order_id = str(data["data"])
       
        self.localOrderDict[local_id] = order_id
        self.orderDict[order_id] = order
        
        req = self.cancelReqDict.get(local_id, None)
        if req:
            self.cancel_order(req)
    
    def on_cancel_order(self, data, request):  # type: (dict, Request)->None
        """"""
        status = data.get("status", None)
        if status == "error":
            msg = "错误代码：%s, 错误信息：%s" % (data["err-code"], data["err-msg"])
            self.gateway.write_log(msg)
            return
        
        self.gateway.write_log(f"委托撤单成功：{data}")


class HuobiWebsocketApiBase(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(HuobiWebsocketApiBase, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.sign_host = ""
        self.path = ""

    def connect(self, key: str, secret: str, url: str):
        """"""
        self.key = key
        self.secret = secret
        host, path = _split_url(url)
        
        self.init(url)
        self.sign_host = host
        self.path = path
        self.start()

    def login(self):
        """"""
        params = {"op": "auth", }
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
            self.send_packet({"pong": packet["ping"]})
            return
        
        if "err-msg" in packet:
            return self.on_error_msg(packet)
        
        if "op" in packet and packet["op"] == "auth":
            return self.on_login()
        
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
        super(HuobiTradeWebsocketApi, self).__init__(gateway)

        self.req_id = 10000
        
        self.accountDict = gateway.accountDict
        self.orderDict = gateway.orderDict
        self.orderLocalDict = gateway.orderLocalDict
        self.localOrderDict = gateway.localOrderDict

    def connect(self, symbols, key, secret):
        """"""
        self.symbols = symbols       
        super(HuobiTradeWebsocketApi, self).connect(key, secret, WEBSOCKET_TRADE_HOST)

    def subscribe_topic(self):
        """"""
        # 订阅资金变动
        self.req_id += 1
        req = {
            "op": "sub",
            "cid": str(self.req_id),
            "topic": "accounts",            
        }
        self.send_packet(req)
        
        # 订阅委托变动
        for symbol in self.symbols:
            self.req_id += 1
            req = {
                "op": "sub",
                "cid": str(self.req_id),
                "topic": f"orders.{symbol}"            
            }
            self.send_packet(req)

    def on_connected(self):
        """"""
        self.login()

    def on_login(self):
        """"""
        self.gateway.write_log("交易Websocket服务器登录成功")
        
        self.subscribe_topic()

    def on_data(self, packet):  # type: (dict)->None
        """"""
        op = packet.get("op", None)
        if op != "notify":
            return
        
        topic = packet["topic"]
        if topic == "accounts":
            self.on_account(packet["data"])
        elif "orders" in topic:
            self.on_order(packet["data"])

    def on_account(self, data):
        """"""
        for d in data["list"]:
            account = self.accountDict.get(d["currency"], None)
            if not account:
                continue
            
            if d["type"] == "trade":
                account.available = float(d["balance"])
            elif d["type"] == "frozen":
                account.margin = float(d["balance"])
            
            account.balance = account.margin + account.available   
            self.gateway.on_account(account)

    def on_order(self, data: list):
        """"""
        order_id = str(data["order-id"])
        order = self.orderDict.get(order_id, None)
        
        if not order:
            local_id = self._new_order_id()
            local_id = str(local_id)

            self.orderLocalDict[order_id] = local_id
            self.localOrderDict[local_id] = order_id

            if "buy" in data["order-type"]:
                direction = Direction.LONG
            else:
                direction = Direction.SHORT
            
            order = OrderData(
                orderid=local_id,
                symbol=data["symbol"],
                exchange=Exchange.HUOBI,
                price=float(data["order-price"]),
                volume=float(data["order-amount"]),
                direction=direction,
                status=STATUS_HUOBI2VT.get(data["order-state"], None),
                time=datetime.fromtimestamp(data["created-at"] / 1000).strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            order.traded += float(data['filled-amount'])                     
            self.orderDict[order_id] = order               
        self.gateway.onOrder(order)
        
        if float(data["filled-amount"]):
            trade = TradeData(
                orderid=order.orderid,
                tradeid=str(data["seq-id"]),
                symbol=data["symbol"],
                exchange=Exchange.HUOBI,
                direction=order.direction,
                price=float(data["price"]),
                volume=float(data["filled-amount"]),
                time=datetime.now().strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )    
            self.gateway.onTrade(trade)


class HuobiMarketWebsocketApi(HuobiWebsocketApiBase):
    """"""
    def __init__(self, gateway):
        """"""
        super(HuobiMarketWebsocketApi, self).__init__(gateway)

        self.req_id = 10000
        self.tickDict = {}

    def connect(self, symbols, key, secret):
        """"""
        self.symbols = symbols        
        super(HuobiMarketWebsocketApi, self).connect(key, secret, WEBSOCKET_MARKET_HOST)

    def on_connected(self):
        """"""
        self.subscribe_topic()

    def subscribe_topic(self):  # type:()->None
        """"""
        for symbol in self.symbols:
            # 创建Tick对象
            tick = TickData(
                symbol=symbol,
                exchange=Exchange.HUOBI,
                gateway_name=self.gateway_name,
            )

            self.tickDict[symbol] = tick            
            
            # 订阅深度和成交
            self.req_id += 1
            req = {
                "sub": "market.{symbol}.depth.step0",
                "id": str(self.req_id)     
            }
            self.send_packet(req)
            
            self.req_id += 1
            req = {
                "sub": "market.{symbol}.detail",
                "id": str(self.req_id)     
            }
            self.send_packet(req)

    def on_data(self, packet):  # type: (dict)->None
        """"""
        if "ch" in packet:
            if "depth.step" in packet["ch"]:
                self.on_market_depth(packet)
            elif "detail" in packet["ch"]:
                self.on_market_detail(packet)
        elif "err-code" in packet:
            self.gateway.write_log("错误代码：%s, 错误信息：%s" % (data["err-code"], data["err-msg"]))

    def on_market_depth(self, data):
        """行情深度推送 """
        symbol = data["ch"].split(".")[1]

        tick = self.tickDict.get(symbol, None)
        if not tick:
            return

        tick.datetime = datetime.fromtimestamp(data["ts"] / 1000)
        tick.date = tick.datetime.strftime("%Y%m%d")
        tick.time = tick.datetime.strftime("%H:%M:%S.%f")

        bids = data["tick"]["bids"]
        for n in range(5):
            l = bids[n]
            tick.__setattr__("bid_price_" + str(n + 1), float(l[0]))
            tick.__setattr__("bid_volume_" + str(n + 1), float(l[1]))

        asks = data["tick"]["asks"]
        for n in range(5):
            l = asks[n]
            tick.__setattr__("ask_price_" + str(n + 1), float(l[0]))
            tick.__setattr__("ask_volume_" + str(n + 1), float(l[1]))

        if tick.last_price:
            newtick = copy(tick)
            self.gateway.on_tick(newtick)

    def on_market_detail(self, data):
        """市场细节推送"""
        symbol = data["ch"].split(".")[1]

        tick = self.tickDict.get(symbol, None)
        if not tick:
            return

        tick.datetime = datetime.fromtimestamp(data["ts"] / 1000)
        tick.date = tick.datetime.strftime("%Y%m%d")
        tick.time = tick.datetime.strftime("%H:%M:%S.%f")

        t = data["tick"]
        tick.open_price = float(t["open"])
        tick.high_price = float(t["high"])
        tick.low_price = float(t["low"])
        tick.last_price = float(t["close"])
        tick.volume = float(t["vol"])
        tick.pre_close = float(tick.open_price)

        if tick.bid_price_1:
            newtick = copy(tick)
            self.gateway.on_tick(newtick)


def print_dict(d):
    """"""
    print("-" * 30)
    l = d.keys()
    l.sort()
    for k in l:
        print(type(k), k, d[k])


def _split_url(url):
    """
    将url拆分为host和path
    :return: host, path
    """
    m = re.match("\w+://([^/]*)(.*)", url)
    if m:
        return m.group(1), m.group(2)


def create_signature(api_key, method, host, path, secret_key, get_params=None):
    """
    创建签名
    :param get_params: dict 使用GET方法时附带的额外参数(urlparams)
    :return:
    """
    sortedParams = [
        ("AccessKeyId", api_key),
        ("SignatureMethod", "HmacSHA256"),
        ("SignatureVersion", "2"),
        ("Timestamp", datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S"))
    ]
    if get_params:
        sortedParams.extend(get_params.items())
        sortedParams = list(sorted(sortedParams))
    encodeParams = urllib.urlencode(sortedParams)
    
    payload = [method, host, path, encodeParams]
    payload = "\n".join(payload)
    payload = payload.encode(encoding="UTF8")
    
    secret_key = secret_key.encode(encoding="UTF8")
    
    digest = hmac.new(secret_key, payload, digestmod=hashlib.sha256).digest()
    signature = base64.b64encode(digest)
    
    params = dict(sortedParams)
    params["Signature"] = signature
    return params
