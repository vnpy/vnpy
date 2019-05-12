from typing import Any, Sequence, Optional

from vnpy.api.itap.vnitap import (
    CreateTapQuoteAPI,
    GetITapTradeAPIVersion,
    GetTapQuoteAPIVersion,
    ITapQuoteAPINotify,
    TapAPIApplicationInfo,
    TapAPIContract,
    TapAPIQuotLoginRspInfo,
    TapAPIQuoteCommodityInfo,
    TapAPIQuoteContractInfo,
    TapAPIQuoteWhole,
    TAPIERROR_SUCCEED,
    TapAPIQuoteLoginAuth,
    ITapQuoteAPI,
    APIYNFLAG_NO,
    FreeTapQuoteAPI,
)

from vnpy.event import EventEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    CancelRequest,
    HistoryRequest,
    OrderRequest,
    SubscribeRequest,
)
from vnpy.api.itap.error_codes import error_map


def error_to_str(err_code: int) -> str:
    try:
        return error_map[err_code]
    except KeyError:
        return f"Unknown error({err_code})"


class QuoteNotify(ITapQuoteAPINotify):
    def OnRspLogin(self, errorCode: int, info: TapAPIQuotLoginRspInfo) -> Any:
        if TAPIERROR_SUCCEED == errorCode:
            print("[+] login succeed!")
        else:
            print(f"[-] login failed! {error_to_str(errorCode)}")

    def OnAPIReady(self) -> Any:
        print("OnApiReady")

    def OnDisconnect(self, reasonCode: int) -> Any:
        print(f"OnDisconnect : {error_to_str(reasonCode)}")

    def OnRspQryCommodity(
        self,
        sessionID: int,
        errorCode: int,
        isLast: int,
        info: TapAPIQuoteCommodityInfo,
    ) -> Any:
        print(f"OnRspQryCommodity : {error_to_str(errorCode)}")

    def OnRspQryContract(
        self, sessionID: int, errorCode: int, isLast: int, info: TapAPIQuoteContractInfo
    ) -> Any:
        print("OnRspQryContract")

    def OnRspSubscribeQuote(
        self, sessionID: int, errorCode: int, isLast: int, info: TapAPIQuoteWhole
    ) -> Any:
        print("OnRspSubscribeQuote")

    def OnRspUnSubscribeQuote(
        self, sessionID: int, errorCode: int, isLast: int, info: TapAPIContract
    ) -> Any:
        print("OnRspUnSubscribeQuote")

    def OnRtnQuote(self, info: TapAPIQuoteWhole) -> Any:
        print("OnRtnQuote")


class ITapGateway(BaseGateway):
    default_setting = {
        "auth_code": "",
        "quote_host": "123.15.58.21",
        "quote_port": 7171,
        "quote_username": "",
        "quote_password": "",
    }

    def __init__(self, event_engine: EventEngine):
        super().__init__(event_engine, "ITAP")
        self.api: Optional[ITapQuoteAPI] = None
        self.quote_notify = QuoteNotify()

    def connect(self, setting: dict):
        auth_code = setting["auth_code"]
        quote_host = setting["quote_host"]
        quote_port = setting["quote_port"]
        quote_username = setting["quote_username"]
        quote_password = setting["quote_password"]
        print("quote version:", GetTapQuoteAPIVersion())
        print("trade version:", GetITapTradeAPIVersion())

        ai = TapAPIApplicationInfo()
        ai.AuthCode = auth_code

        # iResult是输出参数，Python中只能用返回值作为输出。
        # 具体输出了哪些，看pyi的注释
        api, iResult = CreateTapQuoteAPI(ai)
        if api is None:
            error_code = iResult  # 看API文档的注释：iResult就是错误代码
            print(f"CreateTapQuoteAPI error: {error_to_str(error_code)}")
            return  # todo: error report

        api.SetAPINotify(self.quote_notify)
        error_code: int = api.SetHostAddress(quote_host, quote_port)
        if TAPIERROR_SUCCEED != error_code:
            print(f"SetHostAddress error: {error_to_str(error_code)}")
            return

        # login
        la = TapAPIQuoteLoginAuth()
        la.UserNo = quote_username
        la.Password = quote_password
        la.ISDDA = APIYNFLAG_NO
        la.ISModifyPassword = APIYNFLAG_NO
        error_code: int = api.Login(la)  # async
        if TAPIERROR_SUCCEED != error_code:
            print(f"Login error: {error_to_str(error_code)}")
            return
        self.api = api

    def close(self):
        self.api.SetAPINotify(None)
        self.quote_notify = None
        FreeTapQuoteAPI(self.api)
        self.api = None
        pass

    def subscribe(self, req: SubscribeRequest):
        pass

    def send_order(self, req: OrderRequest) -> str:
        pass

    def cancel_order(self, req: CancelRequest):
        pass

    def query_account(self):
        pass

    def query_position(self):
        pass
