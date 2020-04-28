"""
"""
import base64

import json
import threading
import sys
import requests
import math
from Crypto.Cipher import AES
from datetime import datetime
from typing import Dict, Any, List
from urllib import parse

from vnpy.event import Event
from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    Product,
    Status,
    OrderType,
)
from vnpy.trader.gateway import BaseGateway, LocalOrderManager
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    PositionData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
)
from vnpy.trader.event import EVENT_TIMER

AUTHENTICA_URL = "https://dev-kgl.jt00000.com/kgl-third-authorization/oauth/token"
QUOTE_URL = "https://kgl.jt00000.com/hq"

REST_HOST = "https://dev-kgl.jt00000.com/kgl-trade-service"
WEBSOCKET_TRADE_HOST = "ws://dev-kgl.jt00000.com/kgl-trader-push-service/ws"
WEBSOCKET_DATA_HOST = "ws://dev-kgl.jt00000.com/dz_app_ws/ws"

START_PUSH = 200
STOP_PUSH = 201
SYNCHRONIZE_PUSH = 250
QUERY_HISTORY = 36
QUERY_CONTRACT = 52
ON_TICK = 251
PING = 2
PONG = 3
LOGIN = 10
HKSE_MARKET = 2002

STATUS_KAISA2VT = {
    "NEW": Status.NOTTRADED,
    "WA": Status.NOTTRADED,
    "PRO": Status.NOTTRADED,
    "Q": Status.NOTTRADED,
    "REJ": Status.REJECTED,
    "PEX": Status.PARTTRADED,
    "FEX": Status.ALLTRADED,
    "CAN": Status.CANCELLED,
}


ORDERTYPE_VT2KAISA = {
    OrderType.MARKET: "A",
    OrderType.LIMIT: "L",
}
ORDERTYPE_KAISA2VT = {v: k for k, v in ORDERTYPE_VT2KAISA.items()}
ORDERTYPE_KAISA2VT["E"] = OrderType.LIMIT
ORDERTYPE_KAISA2VT["S"] = OrderType.LIMIT
ORDERTYPE_KAISA2VT["I"] = OrderType.LIMIT

DIRECTION_VT2KAISA = {
    Direction.LONG: "B",
    Direction.SHORT: "S",
}
DIRECTION_KAISA2VT = {v: k for k, v in DIRECTION_VT2KAISA.items()}

EXCHANGE_KAISA2VT: Dict[str, Exchange] = {
    "HKEX": Exchange.HKSE
}
EXCHANGE_VT2KAISA = {v: k for k, v in EXCHANGE_KAISA2VT.items()}


class KaisaGateway(BaseGateway):
    """
    VN Trader Gateway for Kaisa connection.
    """

    authentica_status: bool = False
    token: str = ""
    req_id: int = 0

    default_setting: Dict[str, Any] = {
        "auth_id": "",
        "auth_password": "",
        "user_id": "",
        "password": "",
        "会话数": 3,
    }

    exchanges: List[Exchange] = [Exchange.HKSE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "KAISA")

        self.order_manager = LocalOrderManager(self)

        self.rest_api = KaisaTradeRestApi(self)
        self.trade_ws_api = KaisaTradeWebsocketApi(self)
        self.market_ws_api = KaisaDataWebsocketApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        auth_id = setting["auth_id"]
        auth_password = setting["auth_password"]
        user_id = setting["user_id"]
        _password = setting["password"]
        password = self.encrypt(_password)
        session_number = setting["会话数"]

        if not self.authentica_status:
            self.authentica(auth_id, auth_password)

        if not self.token:
            return

        self.rest_api.connect(
            user_id, password, self.token, session_number)
        self.query_contract()

        self.trade_ws_api.connect(user_id, password, self.token)
        self.market_ws_api.connect(user_id, password, self.token)

    def subscribe(self, req: SubscribeRequest) -> int:
        """"""
        self.market_ws_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        self.rest_api.query_account()

    def query_position(self) -> None:
        """"""
        self.rest_api.query_position()

    def close(self) -> None:
        """"""
        self.rest_api.stop()
        self.trade_ws_api.stop()
        self.market_ws_api.stop()

    def process_timer_event(self, event: Event) -> None:
        """"""
        self.count += 1
        if self.count < 3:
            return

        self.query_account()
        self.query_position()

    def init_query(self) -> None:
        """"""
        self.count = 0
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def write_error(self, data) -> None:
        """"""
        error_code = data["retCode"]
        error_msg = data["retMsg"]

        msg = f"错误号 {error_code}, 错误信息 {error_msg}"

        self.write_error(msg)

    def authentica(self, auth_id: str, auth_password: str) -> None:
        """"""
        params = {
            "username": auth_id,
            "password": auth_password,
            "grant_type": "password",
            "scope": "vnpy"
        }
        headers = {
            "Authorization": "basic dm5weV9jbGllbnQ6dm5weV9jbGllbnRfc2VjcmV0",
            "Content-Type": "application/json"
        }
        response = requests.post(
            url=AUTHENTICA_URL, params=params, headers=headers
        )

        if response.status_code // 100 == 2:
            self.write_log("网关认证成功")
            data = response.json()
            token_body = data["body"]["accessToken"]
            self.token = f"bearer {token_body}"
        else:
            data = response.json()
            error_msg = data["retMsg"]
            self.write_log(f"网关认证失败，原因： {error_msg}")

    def _query_contract(self):
        """"""
        self.req_id += 1
        data = {
            "reqtype": QUERY_CONTRACT,
            "reqid": self.req_id,
            "session": "",
            "data": {
                "marketid": HKSE_MARKET,
                "idtype": 1,
                "beginpos": 0,
                "count": 1000,
                "getquote": 0
            }
        }

        headers = {
            "Authorization": self.token,
            "Content-Type": "application/json"
        }

        response = requests.post(
            url=QUOTE_URL, data=json.dumps(data), headers=headers)
        status = response.status_code

        if status == 200:
            data = response.json()
            symbols = data["data"]["symbol"]

            for d in symbols:
                contract = ContractData(
                    symbol=d["code"],
                    exchange=Exchange.HKSE,
                    name=d["name"],
                    pricetick=math.pow(10, -d["dec"]),
                    size=1,
                    min_volume=d["lotsize"],
                    product=Product.SPOT,
                    history_data=True,
                    gateway_name=self.gateway_name,
                )
                self.on_contract(contract)

            self.write_log("合约信息查询成功")
        else:
            self.write_log("合约查询失败")

    def query_contract(self):
        """"""
        threading.Thread(target=self._query_contract).start()

    def encrypt(self, text):
        """"""
        key = "login&pwd@glob)!"
        iv = "kai&sa!global@)!"

        cryptor = AES.new(key.encode("utf8"), AES.MODE_CBC, iv.encode("utf8"))

        text_ajust = text.ljust(16, "\n")
        ciphertext = cryptor.encrypt(bytes(text_ajust, encoding="utf8"))

        encrypt_password = base64.b64encode(ciphertext)
        password = parse.quote(encrypt_password, "\\")
        return password


class KaisaTradeRestApi(RestClient):
    """
    KAISA REST API
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway: KaisaGateway = gateway
        self.gateway_name: str = gateway.gateway_name
        self.order_manager: LocalOrderManager = gateway.order_manager

        self.host: str = ""
        self.user_id: str = ""
        self.password: str = ""
        self.account_id: str = ""
        self.token: str = ""

        self.trader_count: int = 10000
        self.connect_time: int = 0

        self.trade_order_id = {}

    def sign(self, request) -> Request:
        """
        Generate KAISA signature.
        """
        request.headers = {
            "Authorization": self.token
        }

        if request.method == "POST":
            request.headers["Content-Type"] = "application/json"

        if not request.params:
            request.params = {"accountCode": self.user_id}

        if request.data:
            request.data = json.dumps(request.data)

        return request

    def connect(
        self,
        user_id: str,
        password: str,
        token: str,
        session_number: int,
    ) -> None:
        """
        Initialize connection to REST server.
        """
        self.user_id = user_id
        self.password = password
        self.token = token
        self.connect_time = int(datetime.now().strftime("%y%m%d%H%M%S"))

        self.init(REST_HOST)
        self.start(session_number)

        self.gateway.write_log("REST API启动成功")
        self.login()

    def login(self) -> Request:
        """"""
        data = {
            "channelType": "INTERNET",
            "accountCode": self.user_id,
            "password": self.password
        }
        self.add_request(
            method="POST",
            path="/v1/account/login",
            callback=self.on_login,
            data=data
        )

    def query_account(self) -> Request:
        """"""
        self.add_request(
            method="GET",
            path="/v1/account/accounts/balance",
            callback=self.on_query_account,
        )

    def query_position(self) -> Request:
        """"""
        self.add_request(
            method="GET",
            path="/v1/account/accounts/position",
            callback=self.on_query_position,
        )

    def query_order(self) -> Request:
        """"""
        self.add_request(
            method="GET",
            path="/v1/order/orders",
            callback=self.on_query_order,
        )

    def send_order(self, req: OrderRequest) -> str:
        """"""
        local_orderid = self.order_manager.new_local_orderid()
        order = req.create_order_data(
            local_orderid,
            self.gateway_name
        )
        order.time = datetime.now().strftime("%H:%M:%S")

        data = {
            "channelType": "I",
            "exchangeCode": EXCHANGE_VT2KAISA[req.exchange],
            "accountCode": self.user_id,
            "productCode": req.symbol,
            "price": req.price,
            "qty": int(req.volume),
            "bsFlag": DIRECTION_VT2KAISA[req.direction],
            "orderType": ORDERTYPE_VT2KAISA[req.type],
        }

        self.add_request(
            method="POST",
            path="/v1/order/orders/place",
            callback=self.on_send_order,
            data=data,
            extra=order,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        self.order_manager.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> Request:
        """"""
        sys_orderid = self.order_manager.get_sys_orderid(req.orderid)
        data = {
            "channelType": "I",
            "accountCode": self.user_id,
            "orderID": sys_orderid
        }

        n = self.add_request(
            method="POST",
            path="/v1/order/orders/cancelOrder",
            callback=self.on_cancel_order,
            on_failed=self.on_cancel_order_failed,
            data=data,
            extra=req
        )

        print("cancel order", n)

    def on_login(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "账号登录"):
            return

        self.gateway.write_log("账户登陆成功")
        self.gateway.init_query()
        self.query_order()

    def on_query_account(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询账户"):
            return

        print("on query accout", data)

        body = data["body"]
        account = AccountData(
            accountid=body["accountCode"],
            balance=float(body["cash"]),
            frozen=float(body["frozenCash"]),
            gateway_name=self.gateway_name,
        )

        self.gateway.on_account(account)

    def on_query_position(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询持仓"):
            return

        positions = data["body"]["holdShareUnitList"]

        for d in positions:
            position = PositionData(
                symbol=d["productCode"],
                exchange=EXCHANGE_KAISA2VT[d["exchangeCode"]],
                direction=Direction.NET,
                volume=int(d["qty"]),
                frozen=int(d["qty"]) - int(d["availQty"]),
                price=float(d["avgCost"]),
                pnl=float(d["pl"]),
                gateway_name=self.gateway_name
            )
            self.gateway.on_position(position)

    def on_query_order(self, data: dict, request: Request) -> None:
        """"""
        if self.check_error(data, "查询活动委托"):
            return

        body = data["body"]["mutilOrders"]
        orders = body[::-1]

        for d in orders:
            sys_orderid = d["orderID"]
            local_orderid = self.order_manager.get_local_orderid(sys_orderid)

            print("sys id = ", sys_orderid, "local id=", local_orderid, "\n")

            dt = d["createTime"]
            trade_dt = d["updatedTime"]
            time = datetime.strptime(dt, "%Y-%m-%d %H:%M:%S").time()
            trade_time = datetime.strptime(
                trade_dt, "%Y-%m-%d %H:%M:%S").time()

            traded = int(d["execQty"])

            order = OrderData(
                orderid=local_orderid,
                symbol=d["productCode"],
                exchange=EXCHANGE_KAISA2VT[d["exchangeCode"]],
                price=float(d["price"]),
                volume=int(d["qty"]),
                type=ORDERTYPE_KAISA2VT[d["orderType"]],
                direction=DIRECTION_KAISA2VT[d["bsFlag"]],
                offset=Offset.NONE,
                traded=traded,
                status=STATUS_KAISA2VT[d["orderStatus"]],
                time=time,
                gateway_name=self.gateway_name,
            )
            self.order_manager.on_order(order)

            if traded > 0:
                self.trader_count += 1
                trade = TradeData(
                    orderid=local_orderid,
                    symbol=d["productCode"],
                    exchange=EXCHANGE_KAISA2VT[d["exchangeCode"]],
                    tradeid=self.trader_count,
                    direction=DIRECTION_KAISA2VT[d["bsFlag"]],
                    offset=Offset.NONE,
                    volume=traded,
                    price=float(d["execPrice"]),
                    time=trade_time,
                    gateway_name=self.gateway_name,
                )
                self.gateway.on_trade(trade)

        self.gateway.write_log(f"委托信息查询成功")
        self.gateway.write_log("成交查询成功")

    def on_send_order(self, data: dict, request: Request) -> None:
        """"""
        print("1-on send order", data)
        order = request.extra

        if self.check_error(data, "委托"):
            order.status = Status.REJECTED
            self.order_manager.on_order(order)
            return

        sys_orderid = data["body"]["orderID"]
        self.order_manager.update_orderid_map(order.orderid, sys_orderid)

    def on_send_order_failed(self, status_code: str, request: Request) -> None:
        """
        Callback when sending order failed on server.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg = f"委托失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_send_order_error(
        self,
        exception_type: type,
        exception_value: Exception,
        tb,
        request: Request
    ) -> None:
        """
        Callback when sending order caused exception.
        """
        order = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        # Record exception if not ConnectionError
        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, data: dict, request: Request) -> None:
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

    def on_cancel_order_failed(self, status_code: str, request: Request):
        """
        Callback when canceling order failed on server.
        """
        msg = f"撤单失败，状态码：{status_code}，信息：{request.response.text}"
        self.gateway.write_log(msg)

    def on_error(
        self,
        exception_type: type,
        exception_value: Exception,
        tb,
        request: Request
    ) -> None:
        """
        Callback to handler request exception.
        """
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )

    def check_error(self, data: dict, func: str = ""):
        """"""
        if data["success"]:
            return False

        error_code = data["retCode"]
        error_msg = data["retMsg"]

        self.gateway.write_log(f"{func}请求出错，代码：{error_code}，信息：{error_msg}")
        return True


class KaisaWebsocketApiBase(WebsocketClient):
    """"""

    def __init__(self, gateway):
        """"""
        super(KaisaWebsocketApiBase, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.user_id: str = ""
        self.password: str = ""

    def connect(
        self,
        user_id: str,
        password: str,
        token: str,
        url: str
    ) -> None:
        """"""
        self.user_id = user_id
        self.password = password

        self.init(
            host=url,
            header={"Authorization": token}
        )

        self.start()

    def generate_req(self, reqtype: int, data: dict) -> dict:

        self.gateway.req_id += 1
        req = {
            "reqtype": reqtype,
            "reqid": self.gateway.req_id,
            "session": "",
            "data": data
        }
        return req

    def on_packet(self, packet: dict) -> None:
        """"""
        reqtype = packet["reqtype"]
        data = packet["data"]

        if packet["status"] != 0:
            error_msg = packet["msg"]
            msg = f"请求{reqtype}出错，错误信息{error_msg}"
            self.gateway.write_log(msg)
        else:
            if reqtype == PING:
                req = self.generate_req(PONG, {"ts": data["ts"]})
                self.send_packet(req)
            else:
                self.on_data(reqtype, data)

    def on_data(self, reqtype: int, data: dict) -> None:
        """"""
        print("data : {}".format(data))


class KaisaTradeWebsocketApi(KaisaWebsocketApiBase):
    """"""
    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.order_manager = gateway.order_manager
        self.order_manager.push_data_callback = self.on_data

    def connect(self, user_id: str, password: str, token: str) -> None:
        """"""
        super().connect(user_id, password, token, WEBSOCKET_TRADE_HOST)

    def on_connected(self) -> None:
        """"""
        self.gateway.write_log("交易Websocket API连接成功")

    def on_data(self, reqtype: int, data: dict) -> None:
        """"""
        print("Td 事件：",  reqtype, "数据：", data)
        # op = packet.get("op", None)
        # if op != "notify":
        #     return

        # topic = packet["topic"]
        # if "orders" in topic:
        #     self.on_order(packet)

    def on_order(self, data: dict) -> None:
        """"""
        sys_orderid = str(data["order-id"])

        order = self.order_manager.get_order_with_sys_orderid(sys_orderid)
        if not order:
            self.order_manager.add_push_data(sys_orderid, data)
            return

        dt = datetime.fromtimestamp(data["created_at"] / 1000)
        time = dt.strftime("%H:%M:%S")

        if data["client_order_id"]:
            orderid = data["client_order_id"]
        else:
            orderid = data["order_id"]

        order = OrderData(
            symbol=data["contract_code"],
            exchange=Exchange.HKSE,
            orderid=orderid,
            type=ORDERTYPE_KAISA2VT[data["order_price_type"]],
            direction=DIRECTION_KAISA2VT[data["direction"]],
            price=data["price"],
            volume=data["volume"],
            traded=data["trade_volume"],
            status=STATUS_KAISA2VT[data["status"]],
            time=time,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        # Push trade event
        trades = data["trade"]
        if not trades:
            return

        for d in trades:

            dt = datetime.fromtimestamp(d["created_at"] / 1000)
            time = dt.strftime("%H:%M:%S")
            self.rest_api.trader_count += 1

            trade = TradeData(
                symbol=order.symbol,
                exchange=Exchange.HKSE,
                orderid=order.orderid,
                tradeid=self.rest_api.trader_count,
                direction=order.direction,
                offset=order.offset,
                price=d["trade_price"],
                volume=d["trade_volume"],
                time=time,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_trade(trade)


class KaisaDataWebsocketApi(KaisaWebsocketApiBase):
    """"""
    connected_status: bool = False

    def __init__(self, gateway):
        """"""
        super().__init__(gateway)

        self.callbacks = {
            START_PUSH: self.on_start_subscribe,
            STOP_PUSH: self.on_stop_subscribe,
            SYNCHRONIZE_PUSH: self.on_depth,
            ON_TICK: self.on_tick,
        }

    def on_connected(self) -> None:
        """"""
        print("行情websocket   on connected")
        self.gateway.write_log("行情Websocket API连接成功")
        self.connected_status = True

    def on_data(self, reqtype: int, data: dict) -> None:
        """"""
        func = self.callbacks[reqtype]
        func(data)

    def on_tick(self, data):
        """"""
        ticks = data["tick"]

        for d in ticks:
            millisecond = str(d["millisecond"]).ljust(6, "0")
            dt = f"{d['time']}.{millisecond}"
            dt_ = datetime.strptime(dt, "%Y-%m-%d %H:%M:%S.%f")
            tick = TickData(
                symbol=d["code"],
                exchange=Exchange.HKSE,
                datetime=dt_,
                volume=d["volume"],
                last_price=d["price"],
                gateway_name=self.gateway_name
            )
            self.on_tick(tick)

    def on_depth(self, data: dict) -> None:
        """"""
        pass

    def on_start_subscribe(self, data: dict) -> None:
        """"""
        pass

    def on_stop_subscribe(self, data: dict) -> None:
        """"""
        pass

    def connect(self, userid: str, password: str, token: str) -> None:
        """"""
        super().connect(userid, password, token, WEBSOCKET_DATA_HOST)

    def subscribe(self, req: SubscribeRequest) -> int:
        """"""
        if not self.connected_status:
            return

        data = [{
            "market": 2002,
            "code": req.symbol,
            "type": 3,
            "language": 0
            }]

        req = self.generate_req(200, data)

        self.send_packet(req)
