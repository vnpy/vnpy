import wmi
import socket
from typing import Dict, List
import requests
from datetime import datetime
from time import sleep

from vnpy.api.ufto import py_t2sdk
from vnpy.api.sopt import MdApi
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.utility import get_folder_path
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    OrderType,
    Product,
    Status,
    OptionType
)
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

EXCHANGE_HSOPTION2VT: Dict[str, Exchange] = {
    "1": Exchange.SSE,
    "2": Exchange.SZSE
}
EXCHANGE_VT2HSOPTION = {
    Exchange.SSE: "1",
    Exchange.SZSE: "2"
}

DIRECTION_VT2HSOPTION: Dict[Direction, str] = {
    Direction.LONG: "1",
    Direction.SHORT: "2",
}
DIRECTION_HSOPTION2VT = {v: k for k, v in DIRECTION_VT2HSOPTION.items()}

POS_DIRECTION_VT2HSOPTION: Dict[Direction, str] = {
    Direction.LONG: "0",
    Direction.SHORT: "1",
}

POS_DIRECTION_HSOPTION2VT: Dict[str, Direction] = {
    "0": Direction.LONG,
    "1": Direction.SHORT,
    "2": Direction.SHORT
}

DIRECTION_HSOPTION2VT = {v: k for k, v in DIRECTION_VT2HSOPTION.items()}

OFFSET_HSOPTION2VT: Dict[str, Offset] = {
    "O": Offset.OPEN,
    "C": Offset.CLOSE
}
OFFSET_VT2HSOPTION = {v: k for k, v in OFFSET_HSOPTION2VT.items()}

STATUS_HSOPTION2VT: Dict[str, Status] = {
    "2": Status.NOTTRADED,
    "5": Status.CANCELLED,
    "6": Status.CANCELLED,
    "7": Status.PARTTRADED,
    "8": Status.ALLTRADED,
    "9": Status.REJECTED
}
STATUS_VT2HSOPTION = {v: k for k, v in STATUS_HSOPTION2VT.items()}

ORDERTYPE_VT2HSOPTION = {
    OrderType.LIMIT: "0",
    OrderType.MARKET: "OPB"
}
ORDERTYPE_HSOPTION2VT = {v: k for k, v in ORDERTYPE_VT2HSOPTION.items()}

OPTIONTYPE_HSOPTION2VT = {
    "C": OptionType.CALL,
    "P": OptionType.PUT
}

symbol_exchange_map = {}
symbol_name_map = {}
symbol_size_map = {}

FUNCTION_USER_LOGIN = 331100
FUNCTION_QUERY_POSITION = 338023
FUNCTION_QUERY_ACCOUNT = 338022
FUNCTION_QUERY_ORDER = 338020
FUNCTION_QUERY_TRADE = 338021
FUNCTION_QUERY_CONTRACT = 338000
FUNCTION_SEND_ORDER = 338011
FUNCTION_CANCEL_ORDER = 333012

ISSUE_ORDER = "33012"
ISSUE_TRADE = "33011"


class HsoptionGateway(BaseGateway):
    """
    VN Trader Gateway for Hundsun Option.
    """

    default_setting = {
        "恒生用户名": "9899012971",
        "恒生密码": "111111",
        "CTP用户名": "",
        "CTP密码": "",
        "CTP经纪商代码": "",
        "CTP行情服务器": "",
    }

    exchanges = [Exchange.SSE, Exchange.SZSE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "HSOPTION")

        self.td_api = TdApi(self)
        self.md_api = SoptMdApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        hs_userid = setting["恒生用户名"]
        hs_password = setting["恒生密码"]

        ctp_userid = setting["CTP用户名"]
        ctp_password = setting["CTP密码"]
        ctp_brokerid = setting["CTP经纪商代码"]
        ctp_md_address = setting["CTP行情服务器"]

        if not ctp_md_address.startswith("tcp://"):
            ctp_md_address = "tcp://" + ctp_md_address

        self.md_api.connect(
            ctp_md_address, ctp_userid, ctp_password, ctp_brokerid)
        self.td_api.connect(hs_userid, hs_password)

        self.init_query()

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.td_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        self.td_api.query_account()

    def query_position(self) -> None:
        """"""
        self.td_api.query_position()

    def close(self) -> None:
        """"""
        self.td_api.close()
        self.md_api.close()

    def write_error(self, msg: str, error: dict) -> None:
        """"""
        error_id = error["ErrorID"]
        error_msg = error["ErrorMsg"]
        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)

    def process_timer_event(self, event) -> None:
        """"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

    def init_query(self) -> None:
        """"""
        self.count = 0
        self.query_functions = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class SoptMdApi(MdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0

        self.connect_status = False
        self.login_status = False
        self.subscribed = set()

        self.userid = ""
        self.password = ""
        self.brokerid = ""

    def onFrontConnected(self) -> None:
        """
        Callback when front server is connected.
        """
        self.gateway.write_log("行情服务器连接成功")
        self.login()

    def onFrontDisconnected(self, reason: int) -> None:
        """
        Callback when front server is disconnected.
        """
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开，原因{reason}")

    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """
        Callback when user is logged in.
        """
        if not error["ErrorID"]:
            self.login_status = True
            self.gateway.write_log("行情服务器登录成功")

            for symbol in self.subscribed:
                self.subscribeMarketData(symbol)
        else:
            self.gateway.write_error("行情服务器登录失败", error)

    def onRspError(self, error: dict, reqid: int, last: bool) -> None:
        """
        Callback when error occured.
        """
        self.gateway.write_error("行情接口报错", error)

    def onRspSubMarketData(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        if not error or not error["ErrorID"]:
            return

        self.gateway.write_error("行情订阅失败", error)

    def onRtnDepthMarketData(self, data: dict) -> None:
        """
        Callback of tick data update.
        """
        print("onRtnDepthMarketData", data)
        symbol = data["InstrumentID"]
        print("4")
        exchange = symbol_exchange_map.get(symbol, "")
        print("5")
        if not exchange:
            return
        print("6")
        timestamp = f"{data["TradingDay"]} {data["UpdateTime"]}.{int(data["UpdateMillisec"]/100)}"
        print("7")
        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=datetime.strptime(timestamp, "%Y%m%d %H:%M:%S.%f"),
            name=symbol_name_map[symbol],
            volume=data["Volume"],
            open_interest=data["OpenInterest"],
            last_price=data["LastPrice"],
            limit_up=data["UpperLimitPrice"],
            limit_down=data["LowerLimitPrice"],
            open_price=data["OpenPrice"],
            high_price=data["HighestPrice"],
            low_price=data["LowestPrice"],
            pre_close=data["PreClosePrice"],
            bid_price_1=data["BidPrice1"],
            ask_price_1=data["AskPrice1"],
            bid_volume_1=data["BidVolume1"],
            ask_volume_1=data["AskVolume1"],
            gateway_name=self.gateway_name
        )

        tick.bid_price_2 = data["BidPrice2"]
        tick.bid_price_3 = data["BidPrice3"]
        tick.bid_price_4 = data["BidPrice4"]
        tick.bid_price_5 = data["BidPrice5"]

        tick.ask_price_2 = data["AskPrice2"]
        tick.ask_price_3 = data["AskPrice3"]
        tick.ask_price_4 = data["AskPrice4"]
        tick.ask_price_5 = data["AskPrice5"]

        tick.bid_volume_2 = data["BidVolume2"]
        tick.bid_volume_3 = data["BidVolume3"]
        tick.bid_volume_4 = data["BidVolume4"]
        tick.bid_volume_5 = data["BidVolume5"]

        tick.ask_volume_2 = data["AskVolume2"]
        tick.ask_volume_3 = data["AskVolume3"]
        tick.ask_volume_4 = data["AskVolume4"]
        tick.ask_volume_5 = data["AskVolume5"]

        self.gateway.on_tick(tick)

    def connect(
        self,
        address: str,
        userid: str,
        password: str,
        brokerid: int
    ) -> None:
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.brokerid = brokerid

        # If not connected, then start connection first.
        if not self.connect_status:
            path = get_folder_path(self.gateway_name.lower())
            self.createFtdcMdApi(str(path) + "\\Md")
            self.registerFront(address)
            self.init()
            self.connect_status = True

            # Sleep 1 second and check trigger callback manually
            # (temp fix of the bug of Huaxi futures SOPT system)
            sleep(1)
            if not self.login_status:
                self.onFrontConnected()

        # If already connected, then login immediately.
        elif not self.login_status:
            self.login()

    def login(self) -> None:
        """
        Login onto server.
        """
        req = {
            "UserID": self.userid,
            "Password": self.password,
            "BrokerID": self.brokerid
        }

        self.reqid += 1
        self.reqUserLogin(req, self.reqid)

        sleep(3)
        self.gateway.write_log("行情服务器登录成功")
        self.login_status = True

    def subscribe(self, req: SubscribeRequest) -> None:
        """
        Subscribe to tick data update.
        """
        if self.login_status:
            self.subscribeMarketData(req.symbol)
        self.subscribed.add(req.symbol)

    def close(self) -> None:
        """
        Close the connection.
        """
        if self.connect_status:
            self.exit()


class TdApi:
    """"""

    def __init__(self, gateway: HsoptionGateway):
        """"""
        global td_api
        if not td_api:
            td_api = self

        self.userid: str = ""
        self.password: str = ""
        self.op_station: str = ""
        self.connect_status: bool = False
        self.login_status: bool = False
        self.batch_no: int = 1000000

        self.batch_entrust_id: Dict[str, str] = {}
        self.entrust_batch_id: Dict[str, str] = {}
        self.orders: Dict[str, OrderData] = {}
        self.cancels: Dict[str, CancelRequest] = {}

        self.gateway: HsoptionGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.config: py_t2sdk.pyCConfigInterface = None
        self.connection: py_t2sdk.pyConnectionInterface = None

        self.callbacks = {
            FUNCTION_USER_LOGIN: self.on_login,
            FUNCTION_QUERY_POSITION: self.on_query_position,
            FUNCTION_QUERY_ACCOUNT: self.on_query_account,
            FUNCTION_QUERY_ORDER: self.on_query_order,
            FUNCTION_QUERY_TRADE: self.on_query_trade,
            FUNCTION_QUERY_CONTRACT: self.on_query_contract,
            FUNCTION_SEND_ORDER: self.on_send_order,
            FUNCTION_CANCEL_ORDER: self.on_cancel_order,

            ISSUE_ORDER: self.on_return_order,
            ISSUE_TRADE: self.on_return_trade,
        }

    def connect(
        self,
        userid: str,
        password: str,
    ) -> None:
        """"""
        self.userid = userid
        self.password = password

        self.op_station = self.generate_op_station()

        # If not connected, then start connection first.
        if not self.connect_status:
            self.config = py_t2sdk.pyCConfigInterface()
            self.config.Load("citic.ini")

            self.connection = py_t2sdk.pyConnectionInterface(self.config)

            async_callback = py_t2sdk.pyCallbackInterface(
                "vnpy.gateway.hsoption.hsoption_gateway",
                "TdAsyncCallback"
            )
            async_callback.InitInstance()

            ret = self.connection.Create2BizMsg(async_callback)
            if ret:
                msg = str(self.connection.GetErrorMsg(ret))
                self.gateway.write_log(f"初始化失败，错误码：{ret}，信息：{msg}")

            ret = self.connection.Connect(1000)
            if ret:
                msg = str(self.connection.GetErrorMsg(ret))
                self.gateway.write_log(f"连接失败，错误码：{ret}，信息：{msg}")

            self.connect_status = True
            self.gateway.write_log("交易服务器连接成功")

        # If already connected, then login immediately.
        if not self.login_status:
            self.login()

    def on_query_position(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("持仓查询失败")
            return

        for d in data:

            position = PositionData(
                symbol=d["option_code"],
                exchange=EXCHANGE_HSOPTION2VT[d["exchange_type"]],
                direction=POS_DIRECTION_HSOPTION2VT[d["opthold_type"]],
                volume=int(float(d["hold_amount"])),
                pnl=float(d["income_balance"]),
                price=float(d["opt_cost_price"]),
                frozen=int((float(d["hold_amount"]) - float(d["enable_amount"]))),
                gateway_name=self.gateway_name
            )
            self.gateway.on_position(position)

    def on_query_account(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("账号资金查询失败")
            return

        for d in data:
            account = AccountData(
                accountid=self.userid,
                balance=float(d["total_asset"]),
                frozen=float(d["total_asset"]) - float(d["enable_balance"]),
                gateway_name=self.gateway_name
            )
        self.gateway.on_account(account)
        self.query_position()

    def on_query_order(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("委托查询完成")
            return

        for d in data:
            t = d["entrust_time"].rjust(6, "0")
            dt = ":".join([t[: 2], t[2: 4], t[4:]])

            batch_no = d["batch_no"]
            self.batch_no = max(self.batch_no, int(batch_no))
            self.batch_entrust_id[batch_no] = d["entrust_no"]
            self.entrust_batch_id[d["entrust_no"]] = batch_no

            order = OrderData(
                symbol=d["option_code"],
                exchange=EXCHANGE_HSOPTION2VT[d["exchange_type"]],
                direction=DIRECTION_HSOPTION2VT[d["entrust_bs"]],
                status=STATUS_HSOPTION2VT[d["entrust_status"]],
                orderid=batch_no,
                offset=OFFSET_HSOPTION2VT[d["entrust_oc"]],
                volume=int(float(d["entrust_amount"])),
                traded=int(float(d["business_amount"])),
                time=dt,
                gateway_name=self.gateway_name

            )
            self.gateway.on_order(order)
            self.orders[batch_no] = order

        self.gateway.write_log("委托查询完成")

    def on_query_trade(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("成交查询完成")
            return

        for d in data:
            price = float(d["opt_business_price"])
            if price == 0:
                continue

            t = d["business_time"].rjust(6, "0")
            dt = ":".join([t[: 2], t[2: 4], t[4:]])
            batch_no = self.entrust_batch_id[d["entrust_no"]]

            trade = TradeData(
                orderid=batch_no,
                tradeid=d["business_id"],
                symbol=d["option_code"],
                exchange=EXCHANGE_HSOPTION2VT[d["exchange_type"]],
                direction=DIRECTION_HSOPTION2VT[d["entrust_bs"]],
                offset=OFFSET_HSOPTION2VT[d["entrust_oc"]],
                price=price,
                volume=int(float(d["business_amount"])),
                time=dt,
                gateway_name=self.gateway_name
            )
            self.gateway.on_trade(trade)

        self.gateway.write_log("成交查询完成")

        self.subcribe_order()
        self.subcribe_trade()

    def on_query_contract(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("合约查询失败")
            return

        for d in data:
            contract = ContractData(
                symbol=d["option_code"],
                exchange=EXCHANGE_HSOPTION2VT[d["exchange_type"]],
                name=d["option_name"],
                size=int(float(d["amount_per_hand"])),
                pricetick=float(d["opt_price_step"]),
                option_strike=float(d["exercise_price"]),
                option_underlying=d["stock_code"],
                product=Product.OPTION,
                option_type=OPTIONTYPE_HSOPTION2VT[d["option_type"]],
                option_expiry=d["end_date"],
                gateway_name=self.gateway_name
            )
            self.gateway.on_contract(contract)

        self.gateway.write_log("合约查询完成")
        self.query_order()
        self.query_trade()

    def on_send_order(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("委托失败")
            return

        for d in data:
            batch_no = d["batch_no"]
            self.batch_entrust_id[batch_no] = d["entrust_no"]
            self.entrust_batch_id[d["entrust_no"]] = batch_no

            if batch_no in self.cancels:
                cancel_req = self.cancels[batch_no]
                self.cancel_order(cancel_req)

            order = self.orders[batch_no]
            t = d["entrust_time"].rjust(6, "0")
            order.time = ":".join([t[:2], t[2:4], t[4:]])
            self.gateway.on_order(order)

    def on_cancel_order(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("撤单失败")
            return

    def on_return_order(self, data: List[Dict[str, str]]) -> None:
        """"""
        print("on return order", data)

        ## test
        for d in data:
            entrust_no = d["entrust_no"]
            if entrust_no not in self.entrust_batch_id:
                return

            batch_no = self.entrust_batch_id[entrust_no]
            order = self.orders[batch_no]

            order.status = STATUS_HSOPTION2VT[d["entrust_status"]]
            order.traded = int(float(d["business_amount"]))

            self.gateway.on_order(order)

    def on_return_trade(self, data: List[Dict[str, str]]) -> None:
        """"""
        print("on return trade", data)

        ## test
        for d in data:
            traded = int(float(d["business_amount"]))
            entrust_no = d["entrust_no"]

            batch_no = self.entrust_batch_id[entrust_no]
            t = d["business_time"].rjust(6, "0")
            dt = ":".join([t[:2], t[2:4], t[4:]])

            if traded > 0:
                trade = TradeData(
                    symbol=d["option_code"],
                    exchange=EXCHANGE_HSOPTION2VT[d["exchange_type"]],
                    orderid=batch_no,
                    tradeid=d["business_id"],
                    direction=DIRECTION_HSOPTION2VT[d["entrust_bs"]],
                    offset=OFFSET_HSOPTION2VT[d["entrust_oc"]],
                    price=float(d["opt_business_price"]),
                    volume=int(float(d["business_amount"])),

                    time=dt,
                    gateway_name=self.gateway_name,
                )
                self.gateway_name.on_trade(trade)

            order = self.orders[batch_no]
            if traded > 0:
                order.traded += traded
            order.status = STATUS_HSOPTION2VT[d["entrust_status"]]
            self.gateway.on_order(order)

    def on_callback(self, function: int, data: dict) -> None:
        """"""
        func = self.callbacks[function]
        func(data)

    def send_req(self, function: int, req: dict) -> int:
        """"""
        packer = py_t2sdk.pyIF2Packer()
        packer.BeginPack()

        for Field in req.keys():
            packer.AddField(Field)

        for value in req.values():
            packer.AddStr(str(value))

        packer.EndPack()

        msg = py_t2sdk.pyIBizMessage()
        msg.SetFunction(function)
        msg.SetPacketType(0)
        msg.SetContent(packer.GetPackBuf(), packer.GetPackLen())

        n = self.connection.SendBizMsg(msg, 1)

        packer.FreeMem()
        packer.Release()
        msg.Release()

        return n

    def generate_req(self) -> Dict[str, str]:
        """"""
        req = {
            "op_branch_no": self.branch_no,
            "op_entrust_way": "3",
            "op_station": self.op_station,
            "fund_account": self.userid,
            "branch_no": self.branch_no,
            "client_id": self.client_id,
            "password": self.password,
            "password_type": "2",
            "asset_prop": self.asset_prop,
            "sysnode_Id": self.sysnode_id
        }

        return req

    def generate_op_station(self):
        """""""
        company = "SHWL"

        f = requests.request("GET", "http://myip.dnsomatic.com")
        iip = f.text

        c = wmi.WMI()

        for interface in c.Win32_NetworkAdapterConfiguration(IPEnabled=1):
            mac = interface.MACAddress     # MAC地址
            lip = interface.IPAddress[0]   # 公网IP

        for processor in c.Win32_Processor():
            cpu = processor.Processorid.strip()   # CPU编号

        for disk in c.Win32_DiskDrive():   # 硬盘编号
            hd = disk.SerialNumber.strip()

        for disk in c.Win32_LogicalDisk(DriveType=3):   # 硬盘分区信息
            pi = ",".join([disk.Caption, disk.Size])

        pcn = socket.gethostname()         # 计算机名称

        op_station = f"TYJR-{company}-IIP.{iip}-LIP.{lip}-MAC.{mac}-HD.{hd}-PCN.{pcn}-CPU.{cpu}-PI.{pi}"

        return op_station

    def login(self) -> int:
        """"""
        req = {
            "password_type": "2",
            "input_content": "1",
            "op_entrust_way": "3",
            "password": self.password,
            "account_content": self.userid
        }

        self.send_req(FUNCTION_USER_LOGIN, req)

    def send_order(self, req: OrderRequest) -> int:
        """
        Send new order.
        """
        print("req.exchange=", req.exchange)
        req = self.generate_req()
        req["exchange_type"] = EXCHANGE_VT2HSOPTION[req.exchange]
        req["option_code"] = req.symbol
        req["entrust_amount"] = str(req.volume)
        req["opt_entrust_price"] = str(req.price)
        req["entrust_bs"] = DIRECTION_VT2HSOPTION[req.direction]
        req["entrust_oc"] = OFFSET_VT2HSOPTION[req.offset]
        req["covered_flag"] = ""
        req["entrust_prop"] = ORDERTYPE_VT2HSOPTION[req.type]

        self.batch_no += 1
        batch_no = str(self.batch_no)
        req["batch_no"] = batch_no

        self.send_req(FUNCTION_SEND_ORDER, req)

        order = req.create_order_data(batch_no, self.gateway_name)
        self.gateway.on_order(order)

        self.orders[batch_no] = order

        return order.vt_orderid

    def subcribe_topic(self, biz_name: str, topic_name: str) -> int:
        """"""
        # Create subscrbe callback
        sub_callback = py_t2sdk.pySubCallBack(
            "vnpy.gateway.hsoption.hsoption_gateway",
            "TdSubCallback"
        )
        sub_callback.initInstance()

        # Create subscriber
        ret, subscriber = self.connection.NewSubscriber(
            sub_callback,
            biz_name,
            5000
        )
        if ret != 0:
            print(str(self.connection.GetMCLastError(), encoding="gbk"))
            return

        # Set subscribe parameters
        sub_param = py_t2sdk.pySubscribeParamInterface()
        sub_param.SetTopicName(topic_name)
        sub_param.SetFilter("branch_no", str(self.branch_no))
        sub_param.SetFilter("fund_account", str(self.userid))

        # Pack data
        packer = py_t2sdk.pyIF2Packer()
        packer.BeginPack()
        packer.AddField("fund_account")
        packer.AddField("password")
        packer.AddStr(self.userid)
        packer.AddStr(self.password)
        packer.EndPack()

        # Start subcribe
        unpacker = py_t2sdk.pyIF2UnPacker()
        result = subscriber.SubscribeTopic(sub_param, 5000, unpacker, packer)

        packer.FreeMem()
        packer.Release()
        unpacker.Release()
        sub_param.Release()

        return result

    def cancel_order(self, req: CancelRequest) -> None:
        """
        Cancel existing order.
        """
        batch_no = req.orderid

        if batch_no not in self.batch_entrust_id:
            self.cancels[batch_no] = req
            return

        req = self.generate_req()
        entrust_no = self.batch_entrust_id[batch_no]
        req["entrust_no"] = entrust_no

        self.send_req(FUNCTION_CANCEL_ORDER, req)

        if batch_no in self.cancels:
            del self.cancels[batch_no]

    def query_account(self) -> int:
        """"""
        if not self.login_status:
            return

        req = self.generate_req()
        self.send_req(FUNCTION_QUERY_ACCOUNT, req)

    def query_position(self) -> int:
        """"""
        if not self.login_status:
            return

        req = self.generate_req()
        self.send_req(FUNCTION_QUERY_POSITION, req)

    def query_trade(self) -> int:
        """"""
        print("query trade")
        req = self.generate_req()
        req["request_num"] = "10000"
        self.send_req(FUNCTION_QUERY_TRADE, req)

    def query_order(self) -> int:
        """"""
        req = self.generate_req()
        req["request_num"] = "10000"
        self.send_req(FUNCTION_QUERY_ORDER, req)

    def query_contract(self) -> int:
        """"""
        req = self.generate_req()
        req["request_num"] = "10000"
        self.send_req(FUNCTION_QUERY_CONTRACT, req)

    def on_login(self, data: List[Dict[str, str]]) -> None:
        """"""
        if not data:
            self.gateway.write_log("交易服务器登录失败")
            return
        else:
            self.gateway.write_log("交易服务器登录成功")

            self.login_status = True

        for d in data:
            self.user_token = d["user_token"]
            self.branch_no = d["branch_no"]
            self.client_id = d["client_id"]
            self.asset_prop = d["asset_prop"]
            self.sysnode_id = d["sysnode_id"]

        self.query_contract()

    def subcribe_order(self):
        """"""
        n = self.subcribe_topic("order_subcriber", ISSUE_ORDER)
        if n <= 0:
            msg = f"委托订阅失败，原因{self.connection.GetErrorMsg(n)}"
            self.gateway.write_log(msg)
        else:
            self.gateway.write_log("委托回报订阅成功")

    def subcribe_trade(self):
        """"""
        n = self.subcribe_topic("trade_subcriber", ISSUE_TRADE)
        if n <= 0:
            msg = f"成交订阅失败，原因{self.connection.GetErrorMsg(n)}"
            self.gateway.write_log(msg)
        else:
            self.gateway.write_log("成交回报订阅成功")


class TdAsyncCallback:
    """"""

    def __init__(self):
        """"""
        global td_api
        self.td_api = td_api

    def OnRegister(self) -> None:
        """"""
        print("OnRegister")

    def OnClose(self) -> None:
        """"""
        print("OnClose")

    def OnReceivedBizMsg(self, hSend, sBuff, iLenght) -> None:
        """"""
        biz_msg = py_t2sdk.pyIBizMessage()
        biz_msg.SetBuff(sBuff, iLenght)
        ret = biz_msg.GetReturnCode()

        if not ret:
            function = biz_msg.GetFunction()
            buf, len = biz_msg.GetContent()

            unpacker = py_t2sdk.pyIF2UnPacker()
            unpacker.Open(buf, len)
            data = unpack_data(unpacker)
            unpacker.Release()

            global td_api
            self.td_api.on_callback(function, data)
        else:
            print("error in biz message")

        biz_msg.Release()


class TdSubCallback:
    """"""

    def __init__(self):
        """"""
        self.api: TdApi = None
        global td_api
        self.td_api = td_api

    def OnReceived(self, topic, sBuff, iLen) -> None:
        """"""
        biz_msg = py_t2sdk.pyIBizMessage()
        biz_msg.SetBuff(sBuff, iLen)
        buf, len = biz_msg.GetContent()

        unpacker = py_t2sdk.pyIF2UnPacker()
        unpacker.Open(buf, len)
        data = unpack_data(unpacker)
        unpacker.Release()

        global td_api

        self.td_api.on_callback(topic, data)

        biz_msg.Release()


def unpack_data(unpacker: py_t2sdk.pyIF2UnPacker) -> List[Dict[str, str]]:
    """"""
    row_count = unpacker.GetRowCount()
    col_count = unpacker.GetColCount()

    data = []
    for row_index in range(row_count):
        d = {}
        for col_index in range(col_count):
            name = unpacker.GetColName(col_index)
            value = unpacker.GetStrByIndex(col_index)
            d[name] = value

        unpacker.Next()
        data.append(d)

    return data

td_api = None