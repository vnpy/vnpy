"""
"""

import sys
import pytz
from datetime import datetime
from typing import Dict
import json

from vnpy.api.gtja import (
    TdApi,
    MdApi,
    AccountType_Stock,
    PositionSide_Long,
    PositionSide_Short,
    PositionSide_Short_Covered,
    OrderType_LMT,
    OrderFlag_Security_Normal,
    OrderStatus_PendingNew,
    OrderStatus_New,
    OrderStatus_PartiallyFilled,
    OrderStatus_Filled,
    OrderStatus_PendingCancel,
    OrderStatus_Canceling,
    OrderStatus_CancelFilled,
    OrderStatus_PartiallyCanceled,
    OrderStatus_Rejected,
    OrderStatus_CancelRejected,
    MKtype_SH,
    MKtype_SZ,
)
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    OrderType,
    Product,
    Status,
    OptionType
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
)
from vnpy.trader.utility import get_folder_path
from vnpy.trader.event import EVENT_TIMER

MK_GTJA2VT = {
    MKtype_SH: Exchange.SSE,
    MKtype_SZ: Exchange.SZSE

}
MK_VT2GTJA = {v: k for k, v in MK_GTJA2VT.items()}

MAX_FLOAT = sys.float_info.max
CHINA_TZ = pytz.timezone("Asia/Shanghai")

ORDERSTATUS_GTJA2VT = {
    OrderStatus_PendingNew: Status.SUBMITTING,
    OrderStatus_New: Status.NOTTRADED,
    OrderStatus_PartiallyFilled: Status.PARTTRADED,
    OrderStatus_Filled: Status.ALLTRADED,
    OrderStatus_PendingCancel: Status.SUBMITTING,
    OrderStatus_Canceling: Status.CANCELLED,
    OrderStatus_CancelFilled: Status.CANCELLED,
    OrderStatus_PartiallyCanceled: Status.CANCELLED,
    OrderStatus_Rejected: Status.REJECTED,
    OrderStatus_CancelRejected: Status.REJECTED,
}
symbol_exchange_map = {}
symbol_name_map = {}
symbol_size_map = {}

EXCHANGE_GTJA2VT = {
    "SH": Exchange.SSE,
    "SZ": Exchange.SZSE
}
EXCHANGE_VT2GTJA = {v: k for k, v in EXCHANGE_GTJA2VT.items()}
DIRECTION_GTJA2VT = {
    PositionSide_Long: Direction.LONG,
    PositionSide_Short: Direction.SHORT
}
DIRECTION_VT2GTJA = {v: k for k, v in DIRECTION_GTJA2VT.items()}


class GtjaGateway(BaseGateway):
    """
    VN Trader Gateway for CTP .
    """

    default_setting = {
        "用户名": "",
        "密码": "",
        "交易服务器": "",
        "机构代号": "",
        "营业部代号": "",
        "网关": "",
    }

    exchanges = [Exchange.SSE, Exchange.SZSE]

    date = ""

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "GTJA")

        self.td_api = GtjaTdApi(self)
        self.md_api = GtjaMdApi(self)

    def connect(self, setting: dict):
        """"""
        userid = setting["用户名"]
        password = setting["密码"]
        td_address = setting["交易服务器"]
        orgid = setting["机构代号"]
        barnchid = setting["营业部代号"]
        system_id = setting["网关"]

        td_host, td_port = tuple(td_address.split(":"))

        # self.td_api.connect(userid, password, orgid, barnchid, system_id, td_host, td_port)

        self.md_api.connect()
        self.date = datetime.now().strftime("%Y%m%d%H%M")
    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.md_api.subscrbie(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.td_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        self.td_api.query_account()

    def query_position(self):
        """"""
        self.td_api.query_position()

    def close(self) -> None:
        """"""
        self.td_api.close()

    def write_error(self, msg: str, error: dict):
        """"""
        error_id = error["err_code"]
        error_msg = error["err_msg"]
        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)

    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

    def init_query(self):
        """"""
        self.count = 0
        self.query_functions = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class GtjaMdApi(MdApi):

    def __init__(self, gateway: GtjaGateway):
        """"""
        super().__init__()

        self.gateway: GtjaGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.userid: str = ""
        self.password: str = ""
        self.client_id: int = 0
        self.server_ip: str = ""
        self.server_port: int = 0
        self.protocol: int = 0
        self.session_id: int = 0

        self.connect_status: bool = False
        self.login_status: bool = False

        self.sse_inited: bool = False
        self.szse_inited: bool = False

    def onDisconnected(self, reason: int) -> None:
        """"""
        print("onDisconected", reason)
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开, 原因{reason}")

        self.login_server()

    def onSubscribe(self, error):
        """"""
        print("onSubcrieb", error)
        if error["errcode"]:
            self.gateway.write_log(f"订阅失败，错误码{error['errcode']}，信息{error['errstr']}")

    def onDepthMarketData(self, mk_type: int, symbol: str, data: dict) -> None:
        """"""
        pass


    def OnMarketData(self, mk_type: int, symbol: str, data: dict) -> None:
        """"""
        timestamp = f"{self.gateway.date}{str(data['nTime'])}"
        dt = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")
        dt = CHINA_TZ.localize(dt)

        tick = TickData(
            symbol=symbol,
            exchange=MK_GTJA2VT[mk_type],
            datetime=dt,
            volume=data["iVolume"],
            last_price=data["uMatch"],
            limit_up=data["uHighLimited"],
            limit_down=data["uLowLimited"],
            open_price=data["uOpen"],
            high_price=data["uHigh"],
            low_price=data["uLow"],
            pre_close=data["uPreClose"],
            gateway_name=self.gateway_name
        )

        tick.bid_price_1, tick.bid_price_2, tick.bid_price_3, tick.bid_price_4, tick.bid_price_5 = data["bid"][0:5]
        tick.ask_price_1, tick.ask_price_2, tick.ask_price_3, tick.ask_price_4, tick.ask_price_5 = data["ask"][0:5]
        tick.bid_volume_1, tick.bid_volume_2, tick.bid_volume_3, tick.bid_volume_4, tick.bid_volume_5 = data["bid_qty"][0:5]
        tick.ask_volume_1, tick.ask_volume_2, tick.ask_volume_3, tick.ask_volume_4, tick.ask_volume_5 = data["ask_qty"][0:5]

        pricetick = symbol_pricetick_map.get(tick.vt_symbol, 0)
        if pricetick:
            tick.bid_price_1 = round_to(tick.bid_price_1, pricetick)
            tick.bid_price_2 = round_to(tick.bid_price_2, pricetick)
            tick.bid_price_3 = round_to(tick.bid_price_3, pricetick)
            tick.bid_price_4 = round_to(tick.bid_price_4, pricetick)
            tick.bid_price_5 = round_to(tick.bid_price_5, pricetick)
            tick.ask_price_1 = round_to(tick.ask_price_1, pricetick)
            tick.ask_price_2 = round_to(tick.ask_price_2, pricetick)
            tick.ask_price_3 = round_to(tick.ask_price_3, pricetick)
            tick.ask_price_4 = round_to(tick.ask_price_4, pricetick)
            tick.ask_price_5 = round_to(tick.ask_price_5, pricetick)

        tick.name = symbol_name_map.get(tick.vt_symbol, tick.symbol)
        self.gateway.on_tick(tick)



    # def onQueryAllTickers(self, data: dict, error: dict, last: bool) -> None:
    #     """"""
    #     contract = ContractData(
    #         symbol=data["ticker"],
    #         exchange=EXCHANGE_Gtja2VT[data["exchange_id"]],
    #         name=data["ticker_name"],
    #         product=PRODUCT_Gtja2VT[data["ticker_type"]],
    #         size=1,
    #         pricetick=data["price_tick"],
    #         min_volume=data["buy_qty_unit"],
    #         gateway_name=self.gateway_name
    #     )

    #     if contract.product != Product.OPTION:
    #         self.gateway.on_contract(contract)

    #     symbol_name_map[contract.vt_symbol] = contract.name
    #     symbol_pricetick_map[contract.vt_symbol] = contract.pricetick

    #     if last:
    #         self.gateway.write_log(f"{contract.exchange.value}合约信息查询成功")

    #         if contract.exchange == Exchange.SSE:
    #             self.sse_inited = True
    #         else:
    #             self.szse_inited = True

    #         if self.sse_inited and self.szse_inited:
    #             self.gateway.td_api.query_option_info()

    def connect(
        self,
        # userid: str,
        # password: str,
        # client_id: int,
        # server_ip: str,
        # server_port: int,
        # quote_protocol: int
    ) -> None:
        """"""
        # self.userid = userid
        # self.password = password
        # self.client_id = client_id
        # self.server_ip = server_ip
        # self.server_port = server_port
        # self.protocol = PROTOCOL_VT2Gtja[quote_protocol]
        a_cfg = "{\"ip0\":\"101.231.93.225\",\"port0\":16004,\"ip1\":\"101.231.93.225\",\"port1\":16005,\"connect_mode\":\"NR\",\"username\":\"gxjy_tst5\",\"password\":\"1uHnE8GMN7tPl\"}"
        b_cfg = "{\"ip0\":\"101.231.93.225\"|\"port0\":16004|\"ip1\":\"101.231.93.225\"|\"port1\":16005|\"connect_mode\":\"LNK\"|\"username\":\"gxjy_tst5\"|\"password\":\"1uHnE8GMN7tPl\"}"
        cfg = {
            # "ip0": "101.231.93.225",
            # "port0": 16004,
            "ip1": "101.231.93.225",
            "port1": 16004,
            "connect_mode": "NR",
            "username": "gxjy_tst5",
            "password": "1uHnE8GMN7tPl"
        }

        g_cfg = json.dumps(cfg)
        # print("login dict=", a_cfg)

        # Create API object
        if not self.connect_status:
            a = self.createMdApi(b_cfg)
            n = self.login()
            print("create=",a, ",,login python=",n)
            if not a:
                self.gateway.write_log("行情登录成功")
                self.connect_status = True
                self.login_status = True
            else:
                self.gateway.write_log(f"行情登录失败，错误号{n}")
        else:
            self.gateway.write_log("行情接口已登录，请勿重复操作")

    def close(self) -> None:
        """"""
        if self.connect_status:
            self.exit()

    def subscrbie(self, req: SubscribeRequest) -> None:
        """"""
        # if self.login_status:
        if True:
            gtja_exchange = MK_VT2GTJA.get(req.exchange, "")
            
            n = self.subscribeMarketData(gtja_exchange, req.symbol)
            print("subcribe:",n, "@",gtja_exchange, req.symbol)
            

    def query_contract(self) -> None:
        """"""
        for exchange_id in EXCHANGE_Gtja2VT.keys():
            self.queryAllTickers(exchange_id)



class GtjaTdApi(TdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super(GtjaTdApi, self).__init__()

        self.gateway: GtjaGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.reqid: int = 0
        self.order_count: int = 1000
        self.tradeid: int = 1000

        self.connect_status: bool = False
        self.login_status: bool = False
        self.auth_status: bool = False
        self.login_failed: bool = False

        self.userid: str = ""
        self.password: str = ""
        self.orders: Dict[str, OrderData] = {}

        self.account_id: int = 0
        self.cust_id: int = 0

        self.sysid_orderid_map = {}
        self.orderid_sysid_map = {}

    def _new_orderid(self) -> str:
        """"""
        self.order_count += 1
        orderid = f"{self.gateway.date}_{self.order_count}"
        return orderid

    def onError(self, error: dict, reqid: int) -> None:
        """"""
        self.gateway.write_error("错误", error)

    def onRiskNotify(self, data: dict) -> None:
        """"""
        status = data["alarm_status"]
        rule = data["alarm_rule"]
        self.gateway.write_log(f"触发风险警告，状态{status}，类型{rule}")

    def onDisconnect(self) -> None:
        """"""
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开")

    def onLogin(self, data: dict, error: dict) -> None:
        """"""
        if not error["err_code"]:
            self.account_id = data["account_id"]
            self.cust_id = data["cust_id"]

            self.login_status = True
            self.gateway.write_log(f"交易服务器登录成功")
            self.gateway.init_query()
            self.query_order()
            self.query_trade()
        else:
            self.login_failed = True
            self.gateway.write_error("交易服务器登录失败", error)

    def onTradeReport(self, data) -> None:
        print("onTrade", data)
        self.tradeid += 1
        exchange, symbol = tuple(data["symbol"].split("."))
        dt = f"{data['trade_date']} {data['trade_time']}"
        orderid = data["cl_order_id"]
        sysid = data["order_id"]

        if not orderid and sysid:
            orderid = self._new_orderid()

        trade = TradeData(
            tradeid=self.tradeid,
            orderid=orderid,
            gateway_name=self.gateway_name,
            symbol=symbol,
            exchange=EXCHANGE_GTJA2VT[exchange],
            direction=DIRECTION_GTJA2VT[data["side"]],
            price=data["price"]/10000,
            volume=data["volume"],
            datetime=datetime.strptime(dt, "%Y%m%d %H%M%S%f"),
        )

        order = self.orders[orderid]
        order.datetime = trade.datetime
        order.traded += trade.volume
        if order.traded == order.volume:
            order.status = Status.ALLTRADED
        else:
            order.status = Status.PARTTRADED

        self.gateway.on_order(order)
        self.gateway.on_trade(trade)

    def onOrderRsp(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ):
        """"""
        print("onOrder", data)
        orderid = data["cl_order_id"]
        order = self.orders[orderid]
        if error["err_code"]:
            self.gateway.write_error("交易委托失败", error)
            order.status = Status.REJECTED
            order.datetime = datetime.now()
            self.gateway.on_order(order)
        else:
            sysid = data["order_id"]
            self.sysid_orderid_map[sysid] = orderid
            self.orderid_sysid_map[orderid] = sysid

    def onCancelRsp(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        # print("onCancelRsp", data, error)
        if error["err_code"]:
            self.gateway.write_error("交易撤单失败", error)

    def onQueryPositionRsp(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool,
        pos: str
    ) -> None:
        """"""
        exchange, symbol = tuple(data["symbol"].split("."))

        pos = PositionData(
            gateway_name=self.gateway_name,
            symbol=symbol,
            exchange=EXCHANGE_GTJA2VT[exchange],
            direction=Direction.NET,
            volume=data["volume"],
            price=data["cost_price"]/10000,
            pnl=data["total_income"]/10000,
        )
        self.gateway.on_position(pos)

    def onQueryCashRsp(self, data: dict, error: dict, reqid: int) -> None:
        """"""
        if not error["err_code"]:
            account = AccountData(
                accountid=data["account_id"],
                balance=data["total_amount"] / 10000,
                frozen=(data["total_amount"] - data["avail_amount"]) / 10000,
                gateway_name=self.gateway_name
            )
            self.gateway.on_account(account)

    def onQueryOrderRsp(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool,
        pos: str
    ) -> None:
        """"""
        if error["err_code"] == 14020:
            return

        exchange, symbol = tuple(data["symbol"].split("."))
        dt = f"{data['order_date']} {data['order_time']}"
        orderid = data["cl_order_id"]
        sysid = data["order_id"]

        if not orderid and sysid:
            orderid = self._new_orderid()

        order = OrderData(
            orderid=orderid,
            gateway_name=self.gateway_name,
            symbol=symbol,
            exchange=EXCHANGE_GTJA2VT[exchange],
            direction=DIRECTION_GTJA2VT[data["side"]],
            price=data["price"]/10000,
            volume=data["volume"],
            status=ORDERSTATUS_GTJA2VT[data["order_status"]],
            datetime=datetime.strptime(dt, "%Y%m%d %H%M%S%f"),
        )
        self.orders[orderid] = order
        self.sysid_orderid_map[sysid] = orderid
        self.orderid_sysid_map[orderid] = sysid
        self.gateway.on_order(order)

    def onQueryTradeRsp(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool,
        pos: str
    ) -> None:
        """"""
        if error["err_code"] == 14020:
            return

        self.tradeid += 1
        exchange, symbol = tuple(data["symbol"].split("."))
        dt = f"{data['trade_date']} {data['trade_time']}"
        orderid = data["cl_order_id"]
        sysid = data["order_id"]

        if not orderid and sysid:
            orderid = self._new_orderid()

        trade = TradeData(
            tradeid=self.tradeid,
            orderid=orderid,
            gateway_name=self.gateway_name,
            symbol=symbol,
            exchange=EXCHANGE_GTJA2VT[exchange],
            direction=DIRECTION_GTJA2VT[data["side"]],
            price=data["price"]/10000,
            volume=data["volume"],
            datetime=datetime.strptime(dt, "%Y%m%d %H%M%S%f"),
        )

        self.gateway.on_trade(trade)

    def connect(
        self,
        userid: str,
        password: str,
        orgid: str,
        branchid: str,
        system_id: str,
        host: str,
        port: str,
    ) -> None:
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.date = datetime.now().strftime("%Y%m%d%H%M")

        if not self.connect_status:

            path = get_folder_path(self.gateway_name.lower())
            self.setLogConfig("D:/gtja")
            self.createTraderApi()

            account_info = {
                "account_id": userid,
                "account_type": AccountType_Stock,
                "account_pwd": password,
                "cust_orgid": orgid,
                "cust_branchid": branchid,
                "cl_system_id": system_id,
            }

            terminal_info = "PC;IIP=106.14.230.54;IPORT=50002;LIP=192.168.6.5;MAC=54EE750B1713^54EE750B1716;HD=TF655AY91GHRVL;CPU=BFEBFBFF004065@ClientName;V1.0.1"

            self.login(host, int(port), account_info, terminal_info)

            self.connect_status = True

    def send_order(self, req: OrderRequest) -> str:
        """
        Send new order.
        """
        self.reqid += 1
        orderid = self._new_orderid()
        order = req.create_order_data(orderid, self.gateway_name)
        exchange = EXCHANGE_VT2GTJA[req.exchange]
        gtja_symbol = f"{exchange}.{req.symbol}"
        order_req = {
            "cl_order_id": orderid,
            "symbol": gtja_symbol,
            "order_type": OrderType_LMT,
            "side": DIRECTION_VT2GTJA[req.direction],
            "volume": int(req.volume),
            "price": int(req.price * 10000),
            "order_flag": OrderFlag_Security_Normal,

        }
        self.order(order_req, self.reqid)
        self.orders[orderid] = order
        self.gateway.on_order(order)
        return order.vt_orderid

    def query_order(self) -> None:
        self.reqid += 1
        self.queryOrders(
            "", 500, self.reqid, 0
        )

    def query_trade(self) -> None:
        self.reqid += 1
        self.queryTrades(
            "", 500, self.reqid
        )

    def cancel_order(self, req: CancelRequest) -> None:
        """
        Cancel existing order.
        """
        self.reqid += 1
        sysid = self.orderid_sysid_map[req.orderid]
        order_req = {
            "order_id": sysid
        }
        self.cancelOrder(order_req, self.reqid)

    def query_account(self) -> None:
        """
        Query account balance data.
        """
        self.reqid += 1
        self.queryCash(self.reqid)

    def query_position(self) -> None:
        """
        Query position holding data.
        """

        self.reqid += 1
        self.queryPositions(
            "",
            500,
            self.reqid
        )

    def close(self) -> None:
        """"""
        if self.connect_status:
            self.exit()


def adjust_price(price: float) -> float:
    """"""
    if price == MAX_FLOAT:
        price = 0
    return price
