import wmi
import json
import urllib
import socket
from typing import Dict

from vnpy.api.ufto import py_t2sdk
from vnpy.trader.gateway import BaseGateway
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
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
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
EXCHANGE_VT2HSOPTION = {v: k for k, v in EXCHANGE_HSOPTION2VT.items()}

DIRECTION_VT2HSOPTION: Dict[Direction, str] = {
    Direction.LONG: "0",
    Direction.SHORT: "1",
}
DIRECTION_HSOPTION2VT = {v: k for k, v in DIRECTION_VT2HSOPTION.items()}

OFFSET_HSOPTION2VT: Dict[str, Offset] = {
    "O": Offset.OPEN,
    "C": Offset.CLOSE
}
OFFSET_VT2HSOPTION = {v: k for k, v in OFFSET_HSOPTION2VT.items()}

FUNCTION_USER_LOGIN = 331100
FUNCTION_QUERY_POSITION = 338023
FUNCTION_QUERY_ACCOUNT = 338022
FUNCTION_QUERY_ORDER = 338020
FUNCTION_QUERY_TRADE = 338021
FUNCTION_SEND_ORDER = 338011
FUNCTION_CANCEL_ORDER = 333012


class HsoptionGateway(BaseGateway):
    """
    VN Trader Gateway for Hundsun Option.
    """

    default_setting = {
        "用户名": "9899012971",
        "密码": "111111",
    }

    exchanges = [Exchange.SSE, Exchange.SZSE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "HSOPTION")

        self.td_api = TdApi(self)
        self.md_api = None

    def connect(self, setting: dict) -> None:
        """"""
        userid = setting["用户名"]
        password = setting["密码"]

        self.td_api.connect(userid, password)
        # self.md_api.connect(userid, password)

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
        self.exit()
        # self.td_api.Close()
        # self.md_api.close()

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


class TdApi:
    """"""

    def __init__(self, gateway: HsoptionGateway):
        """"""
        global td_api
        if not td_api:
            td_api = self

        self.userid = ""
        self.password = ""
        self.op_station = ""
        self.connect_status = False
        self.login_status = False

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
            FUNCTION_SEND_ORDER: self.on_send_order,
            FUNCTION_CANCEL_ORDER: self.on_cancel_order,
        }

    def connect(
        self,
        userid: str,
        password: str,
    ) -> bool:
        """"""
        self.userid = userid
        self.password = password

        # 生成op_station
        data = json.loads(urllib.urlopen("http://ip.jsontest.com/").read())
        iip = data["ip"]
        c = wmi.WMI()

        for interface in c.Win32_NetworkAdapterConfiguration(IPEnabled=1):
            mac = interface.MACAddress     # MAC地址
            lip = interface.IPAddress[0]   # 公网IP

        for processor in c.Win32_Processor():
            cpu = processor.Processorid.strip()   # CPU编号

        for disk in c.Win32_DiskDrive():   # 硬盘编号
            hd = disk.SerialNumber.strip()

        for disk in c.Win32_LogicalDisk(DriveType=3):   # 硬盘分区信息
            pi = ','.join([disk.Caption, disk.Size])

        pcn = socket.gethostname()         # 计算机名称

        opStation = "111111111"

        self.op_station = f"TYJR-{opStation}-IIP.{iip}-LIP.{lip}-MAC.{mac}-HD.{hd}-PCN.{pcn}-CPU.{cpu}-PI.{pi}"

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

        # sub_callback = py_t2sdk.pySubCallBack(
        #     "hsoption_gateway",
        #     "TdSubCallback"
        # )
        # sub_callback.initInstance()
        # # sub_callback.set_api(self)

        # bizName = ""
        # ret = self.connection.NewSubscriber(sub_callback, bizName, 5000)
        # print("3-ret:", ret)

        # If already connected, then login immediately.
        if not self.login_status:
            self.login()

    def on_callback(self, function: int, data: dict) -> None:
        """"""
        func = self.callbacks[function]
        func(data)

    def send_req(self, function: int, req: dict) -> int:
        """"""
        print("send_req, funcion name:", function, "req=", req)
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
        print("send result", n)

        packer.FreeMem()
        packer.Release()
        msg.Release()

        return n

    def generate_req(self) -> Dict[str, str]:
        """"""
        req = {
            "op_branch_no": self.branch_no,
            "op_entrust_way": "3",
            "op_station": "192.168.0.1",  # 1
            "fund_account": self.userid,
            "branch_no": self.branch_no,
            "client_id": self.client_id,
            "password": self.password,
            "password_type": "2",
            "asset_prop": self.asset_prop,
            "sysnode_Id": self.sysnode_Id
        }

        return req

    def login(self):
        """"""
        req = {
            "password_type": "2",
            "input_content": "1",
            "op_entrust_way": "3",
            "password": self.password,
            "account_content": self.userid
        }

        self.send_req(FUNCTION_USER_LOGIN, req)

    def query_account(self) -> int:
        """"""
        if not self.login_status:
            return

        req = self.generate_req()
        print("start query account", req)

        packer = py_t2sdk.pyIF2Packer()
        packer.BeginPack()

        for Field in req.keys():
            packer.AddField(Field)

        for value in req.values():
            packer.AddStr(str(value))

        packer.EndPack()

        msg = py_t2sdk.pyIBizMessage()
        msg.SetFunction(FUNCTION_QUERY_ACCOUNT)
        msg.SetPacketType(0)
        msg.SetContent(packer.GetPackBuf(), packer.GetPackLen())

        ret = self.connection.SendBizMsg(msg)

        iRetAns, pyMsgAns = self.connection.RecvBizMsg(ret,6000)
        #判断返回的句柄是否为0
        if iRetAns == 0:
            print("11111")
            #判断错误码为0正常解包
            print("错误码：", pyMsgAns.GetErrorNo())
            if pyMsgAns.GetErrorNo() == 0:
                print("222222")
                #获取业务内容放入buf
                buf,len = pyMsgAns.GetContent()
                #创建解包器
                LoginUnPack = py_t2sdk.pyIF2UnPacker()
                #这个比较特殊同步异步都要调用进行打开文件，具体使用查看开发文档
                LoginUnPack.Open(buf,len)
                #打印相关应答字段
                unpack_data(LoginUnPack)

                LoginUnPack.Release()

        packer.FreeMem()
        packer.Release()
        msg.Release()

    def query_position(self) -> int:
        """"""
        if not self.login_status:
            return

        req = self.generate_req()
        self.sendReq(FUNCTION_QUERY_POSITION, req)

    def queyr_trade(self) -> int:
        """"""
        req = self.generate_req()
        req['request_num'] = "10000"
        self.sendReq(FUNCTION_QUERY_TRADE, req)

    def queyr_order(self) -> int:
        """"""
        req = self.generate_req()
        self.sendReq(FUNCTION_QUERY_ORDER, req)

    def on_login(self, data: list) -> None:
        """"""
        if not data:
            self.gateway.write_log("交易服务器登录失败")
            return
        else:
            self.gateway.write_log("交易服务器登录成功")

        for d in data:
            self.user_token = d["user_token"]
            self.branch_no = d["branch_no"]
            self.client_id = d["client_id"]
            self.asset_prop = d["asset_prop"]
            self.sysnode_id = d["sysnode_id"]

        self.query_account()

    def on_query_position(self, data: list) -> None:
        """"""
        if not data:
            self.gateway.write_log("持仓查询失败")
            return

        for d in data:
            position = PositionData(
                symbol=d['option_code'],
                exchange=EXCHANGE_HSOPTION2VT(d["exchange_type"]),
                direction=DIRECTION_HSOPTION2VT(d['opthold_type']),
                volume=int(float(d['hold_amount'])),
                pnl=float(d['income_balance']),
                frozen=int((float(d['hold_amount']) - float(d['enable_amount']))),
                gateway_name=self.gateway_name
            )

            self.gateway.on_position(position)

    def on_query_account(self, data: list) -> None:
        """"""
        if not data:
            self.gateway.write_log("账号资金查询失败")
            return

        for d in data:
            account = AccountData(
                accountid=self.userid,
                balance=float(d["total_asset"]),
                available=float(d['enable_balance']),
                frozen=float(d["total_asset"]) - float(d['enable_balance']),
                gateway_name=self.gateway_name
            )
            self.gateway.on_account(account)

    def on_query_order(self, data: list) -> None:
        """"""
        # if not data:
        #     self.gateway.write_log("委托查询失败")
        #     return
        for d in data:
            t = d['business_time'].rjust(6, '0')
            order = OrderData(
                orderid=d["batch_no"],
                symbol=d['option_code'],
                exchange=EXCHANGE_HSOPTION2VT(d["entrust_bs"]),
                direction=DIRECTION_HSOPTION2VT(d['opthold_type']),
                offset=OFFSET_HSOPTION2VT(d['entrust_oc']),
                volume=int(float(d['entrust_amount'])),
                traded=int(float(d['business_amount'])),
                tiem=':'.join([t[:2], t[2:4], t[4:]]),
                gateway_name=self.gateway_name

            )
            self.gateway.on_order(order)

        self.gateway.write_log('委托查询完成')

    def on_query_trade(self, data: list) -> None:
        """"""
        # if not data:
        #     self.gateway.write_log("成交查询失败")
        #     return

        for d in data:
            t = d['business_time'].rjust(6, '0')
            trade = TradeData(
                orderid=self.entrust_batch[d['entrust_no']],
                tradeid=d['business_id'],
                symbol=d['option_code'],
                exchange=EXCHANGE_HSOPTION2VT(d["entrust_bs"]),
                direction=DIRECTION_HSOPTION2VT(d['opthold_type']),
                offset=OFFSET_HSOPTION2VT(d['entrust_oc']),
                price=float(d['opt_business_price']),
                volume=int(float(d['business_amount'])),
                tiem=':'.join([t[:2], t[2:4], t[4:]]),
                gateway_name=self.gateway_name

            )
            self.gateway.on_trade(trade)

        self.gateway.write_log('成交查询完成')

    def on_send_order(self, data: list) -> None:
        """"""
        pass

    def on_cancel_order(self, data: list) -> None:
        """"""
        pass


class TdAsyncCallback:
    """"""

    def __init__(self):
        """"""
        global td_api
        self.td_api = td_api

    def OnRegister(self):
        """"""
        print("OnRegister")
        # self.td_api.query_account()

    def OnClose(self):
        """"""
        print("OnClose")

    def OnReceivedBizMsg(self, hSend, sBuff, iLenght):
        """"""
        print("call_back")
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

    def OnReceived(self, topic, sBuff, iLen):
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


def unpack_data(unpacker: py_t2sdk.pyIF2UnPacker):
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

class TdSpi:

    login_status = False
    client_id = ""
    user_token = ""
    branch_no = ""

    def __init__(self):
        """"""
        print("__init__")

        global td_api
        self.td_api = td_api
        self.on_init = True

    def OnRegister(self):
        """"""
        print("OnRegister\n")

    def OnClose(self):
        """"""
        print("OnClose\n") 

    def OnReceivedBizMsg(self, hSend, sBuff, iLenght):
        print("回调函数信息\n")

td_api = None