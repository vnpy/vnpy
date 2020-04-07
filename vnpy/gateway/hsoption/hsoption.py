from vnpy.api.t2sdk import py_t2sdk

from vnpy.trader.gateway import BaseGateway
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import Exchange
from vnpy.trader.object import (
    OrderRequest,
    CancelRequest,
    SubscribeRequest
)


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
        "用户名": "",
        "密码": "",
        "经纪商代码": "",
        "交易服务器": "",
        "行情服务器": ""
    }

    exchanges = [Exchange.SSE, Exchange.SZSE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "HSOPTION")

        self.td_api = TdApi(self)
        self.md_api = None

    def connect(self, setting: dict):
        """"""
        userid = setting["用户名"]
        password = setting["密码"]
        # brokerid = setting["经纪商代码"]
        # td_address = setting["交易服务器"]
        # md_address = setting["行情服务器"]

        self.td_api.connect(userid, password)
        self.md_api.connect(userid, password)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.td_api.cancel_order(req)

    def query_account(self):
        """"""
        self.td_api.query_account()

    def query_position(self):
        """"""
        self.td_api.query_position()

    def close(self):
        """"""
        self.td_api.close()
        self.md_api.close()

    def write_error(self, msg: str, error: dict):
        """"""
        error_id = error["ErrorID"]
        error_msg = error["ErrorMsg"]
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



class TdApi:
    """"""

    def __init__(self, gateway: HsoptionGateway):
        """"""
        self.userid = ""
        self.password = ""

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

    def connect(self, userid, password) -> bool:
        """"""
        self.userid = userid
        self.password = password

        self.config = py_t2sdk.pyCConfigInterface()
        self.config.Load("citic.ini")

        self.connection = py_t2sdk.pyConnectionInterface()

        async_callback = py_t2sdk.pyCallbackInterface(
            "hsoption_gateway",
            "TdAsyncCallback"
        )
        async_callback.set_api(self)

        ret = self.connection.Create2BizMsg(async_callback)
        if ret:
            msg = str(self.connection.GetErrorMsg(ret))
            self.gateway.write_log(f"初始化失败，错误码：{ret}，信息：{msg}")
            return False

        ret = self.connection.connect(1000)
        if ret:
            msg = str(self.connection.GetErrorMsg(ret))
            self.gateway.write_log(f"连接失败，错误码：{ret}，信息：{msg}")
            return False

        sub_callback = py_t2sdk.pySubCallBack(
            "hsoption_gateway",
            "TdSubCallback"
        )
        sub_callback.set_api(self)

        bizName = ""
        ret = self.connect.NewSubscriber(sub_callback, bizName, 5000)

        return True

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

        n = self.connect.SendBizMsg(msg, 1)

        packer.FreeMem()
        packer.Release()
        msg.Release()

        return n

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

    def on_login(self, data: dict):
        """"""
        pass


class TdAsyncCallback:
    """"""

    def __init__(self):
        """"""
        self.api: TdApi = None

    def set_api(self, api: TdApi):
        """"""
        self.api = api

    def OnRegister(self):
        """"""
        print("OnRegister")

    def OnClose(self):
        """"""
        print("OnClose")

    def OnReceivedBizMsg(self, hSend, sBuff, iLenght):
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

            self.api.on_callback(function, data)
        else:
            print("error in biz message")

        biz_msg.Release()


class TdSubCallback:
    """"""

    def __init__(self):
        """"""
        self.api: TdApi = None

    def set_api(self, api: TdApi):
        """"""
        self.api = api

    def OnReceived(self, topic, sBuff, iLen):
        """"""
        biz_msg = py_t2sdk.pyIBizMessage()
        biz_msg.SetBuff(sBuff, iLen)
        buf, len = biz_msg.GetContent()

        unpacker = py_t2sdk.pyIF2UnPacker()
        unpacker.Open(buf, len)
        data = unpack_data(unpacker)
        unpacker.Release()

        self.api.on_callback(topic, data)

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