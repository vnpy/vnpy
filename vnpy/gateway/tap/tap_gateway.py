import sys
from dataclasses import dataclass
from datetime import datetime
from typing import Any, Dict, Optional, Tuple

from vnpy.api.tap.vntap import (
    APIYNFLAG_NO, AsyncDispatchException, CreateTapQuoteAPI,
    FreeTapQuoteAPI, ITapQuoteAPI, ITapQuoteAPINotify,
    TAPIERROR_SUCCEED, TAPI_CALLPUT_FLAG_NONE,
    TAPI_COMMODITY_TYPE_FUTURES, TAPI_COMMODITY_TYPE_INDEX,
    TAPI_COMMODITY_TYPE_OPTION, TAPI_COMMODITY_TYPE_SPOT,
    TAPI_COMMODITY_TYPE_STOCK, TapAPIApplicationInfo, TapAPIContract,
    TapAPIQuotLoginRspInfo, TapAPIQuoteCommodityInfo,
    TapAPIQuoteContractInfo, TapAPIQuoteLoginAuth, TapAPIQuoteWhole,
    set_async_callback_exception_handler,
    CreateITapTradeAPI
)
from vnpy.api.tap.vntap.ITapTrade import (
    ITapTradeAPINotify, ITapTradeAPI,
    TapAPITradeLoginRspInfo,
    TapAPIApplicationInfo as TapTradeAPIApplicationInfo,
    TapAPITradeLoginAuth, TapAPIAccQryReq, TapAPIFundReq,
    TapAPIAccountInfo, TapAPIFundData
)
from vnpy.api.tap.error_codes import error_map

from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Product
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    CancelRequest,
    ContractData,
    OrderRequest,
    SubscribeRequest,
    TickData)

PRODUCT_TYPE_TAP2VT = {
    TAPI_COMMODITY_TYPE_SPOT: Product.SPOT,
    TAPI_COMMODITY_TYPE_FUTURES: Product.FUTURES,
    TAPI_COMMODITY_TYPE_OPTION: Product.OPTION,
    TAPI_COMMODITY_TYPE_INDEX: Product.INDEX,
    TAPI_COMMODITY_TYPE_STOCK: Product.EQUITY,
}

EXCHANGE_TAP2VT = {
    'SGX': Exchange.SGX,
    'INE': Exchange.INE,
    'APEX': Exchange.APEX,
    'NYMEX': Exchange.NYMEX,
    'LME': Exchange.LME,
    'COMEX': Exchange.COMEX,
    'CBOT': Exchange.CBOT,
    'HKEX': Exchange.HKFE,
    'CME': Exchange.CME,
}
EXCHANGE_VT2TAP = {v: k for k, v in EXCHANGE_TAP2VT.items()}


commodity_infos = {}
extra_infos = {}


class TapGateway(BaseGateway):
    """
    VN Trader gateway for Esunny 9.0.
    """

    default_setting = {
        "quote_username": "",
        "quote_password": "",
        "quote_host": "",
        "quote_port": 0,
        "trade_username": "",
        "trade_password": "",
        "trade_host": "",
        "trade_port": 0,
        "auth_code": ""
    }

    exchanges = list(EXCHANGE_VT2TAP.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "TAP")

        self.quote_api = QuoteApi(self)
        self.trade_api = TradeApi(self)

        set_async_callback_exception_handler(
            self._async_callback_exception_handler)

    def connect(self, setting: dict):
        """"""
        quote_username = setting["quote_username"]
        quote_password = setting["quote_password"]
        quote_host = setting["quote_host"]
        quote_port = setting["quote_port"]
        trade_username = setting["trade_username"]
        trade_password = setting["trade_password"]
        trade_host = setting["trade_host"]
        trade_port = setting["trade_port"]
        auth_code = setting["auth_code"]

        self.trade_api.connect(
            trade_username,
            trade_password,
            trade_host,
            trade_port,
            auth_code
        )
        self.quote_api.connect(
            quote_username,
            quote_password,
            quote_host,
            quote_port,
            auth_code
        )

    def close(self):
        """"""
        self.trade_api.close()
        self.quote_api.close()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.quote_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.trade_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.trade_api.cancel_order(req)

    def query_account(self):
        """"""
        self.trade_api.query_account()

    def query_position(self):
        """"""
        self.trade_api.query_position()

    def _async_callback_exception_handler(self, e: AsyncDispatchException):
        """"""
        error_str = (f"发生内部错误，位置：\n{e.instance}.{e.function_name}，详细信息：\n"
                     f"{e.what}\n"
                     )
        print(error_str)
        self.write_log(error_str)
        return True


class QuoteApi(ITapQuoteAPINotify):
    """"""

    def __init__(self, gateway: TapGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.api = None

    def OnRspLogin(self, errorCode: int, info: TapAPIQuotLoginRspInfo):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log("行情服务器登录失败")
        else:
            self.gateway.write_log("行情服务器登录成功")

    def OnAPIReady(self):
        """"""
        self.api.QryCommodity()

    def OnDisconnect(self, reasonCode: int):
        """"""
        self.gateway.write_log(f"行情服务器连接断开，原因：{reasonCode}")

    def OnRspQryCommodity(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIQuoteCommodityInfo,
    ):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log("查询交易品种信息失败")
            return

        commodity_info = CommodityInfo(
            name=info.CommodityName,
            size=info.ContractSize,     # value is 0 in sim environment
            pricetick=info.CommodityTickSize
        )
        commodity_infos[info.Commodity.CommodityNo] = commodity_info

        self.api.QryContract(info.Commodity)

        if isLast == "Y":
            self.gateway.write_log("查询交易品种信息成功")

    def OnRspQryContract(
        self, sessionID: int, errorCode: int, isLast: str, info: TapAPIQuoteContractInfo
    ):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log("查询交易合约信息失败")
            return

        if not info:
            return

        commodity_info = commodity_infos[info.Contract.Commodity.CommodityNo]
        symbol = info.Contract.Commodity.CommodityNo + info.Contract.ContractNo1

        contract = ContractData(
            symbol=symbol,
            exchange=EXCHANGE_TAP2VT[info.Contract.Commodity.ExchangeNo],
            name=symbol,
            product=Product.FUTURES,
            size=commodity_info.size,
            pricetick=commodity_info.pricetick,
            gateway_name=self.gateway.gateway_name
        )
        self.gateway.on_contract(contract)

        extra_info = ExtraInfo(
            name=contract.name,
            commodity_type=info.Contract.Commodity.CommodityType,
            commodity_no=info.Contract.Commodity.CommodityNo,
        )
        extra_infos[(contract.symbol, contract.exchange)] = extra_info

    def OnRspSubscribeQuote(
        self, sessionID: int, errorCode: int, isLast: str, info: TapAPIQuoteWhole
    ):
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log("订阅行情失败")
        else:
            self.update_tick(info)

    def OnRtnQuote(self, info: TapAPIQuoteWhole):
        """"""
        self.update_tick(info)

    def update_tick(self, info: TapAPIQuoteWhole):
        """"""
        symbol = info.Contract.ContractNo1
        exchange = EXCHANGE_TAP2VT[info.Contract.Commodity.ExchangeNo]

        extra_info = extra_infos.get((symbol, exchange), None)
        if not extra_info:
            return

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=parse_datetime(info.DateTimeStamp),
            name=extra_info.name,
            volume=info.QTotalQty,
            last_price=info.QLastPrice,
            last_volume=info.QLastQty,
            limit_up=info.QLimitUpPrice,
            limit_down=info.QLimitDownPrice,
            open_price=info.QOpeningPrice,
            high_price=info.QHighPrice,
            low_price=info.QLowPrice,
            pre_close=info.QPreClosingPrice,
            bid_price_1=info.QBidPrice[0],
            bid_price_2=info.QBidPrice[1],
            bid_price_3=info.QBidPrice[2],
            bid_price_4=info.QBidPrice[3],
            bid_price_5=info.QBidPrice[4],
            ask_price_1=info.QAskPrice[0],
            ask_price_2=info.QAskPrice[1],
            ask_price_3=info.QAskPrice[2],
            ask_price_4=info.QAskPrice[3],
            ask_price_5=info.QAskPrice[4],
            bid_volume_1=info.QBidQty[0],
            bid_volume_2=info.QBidQty[1],
            bid_volume_3=info.QBidQty[2],
            bid_volume_4=info.QBidQty[3],
            bid_volume_5=info.QBidQty[4],
            ask_volume_1=info.QAskQty[0],
            ask_volume_2=info.QAskQty[1],
            ask_volume_3=info.QAskQty[2],
            ask_volume_4=info.QAskQty[3],
            ask_volume_5=info.QAskQty[4],
            gateway_name=self.gateway.gateway_name,
        )
        self.gateway.on_tick(tick)

    def connect(self, username: str, password: str, host: str, port: int, auth_code: str):
        """"""
        # Create API object
        info = TapAPIApplicationInfo()
        info.AuthCode = auth_code

        self.api, iResult = CreateTapQuoteAPI(info)
        if not self.api:
            self.gateway.write_log("行情API初始化失败")
            return

        # Set server address and port
        self.api.SetAPINotify(self)
        self.api.SetHostAddress(host, port)

        # Start connection
        login_auth = TapAPIQuoteLoginAuth()
        login_auth.UserNo = username
        login_auth.Password = password
        login_auth.ISDDA = APIYNFLAG_NO
        login_auth.ISModifyPassword = APIYNFLAG_NO

        self.api.Login(login_auth)

    def close(self):
        """"""
        self.api.SetAPINotify(None)
        FreeTapQuoteAPI(self.api)
        self.api = None

    def subscribe(self, req: SubscribeRequest):
        """"""
        extra_info = extra_infos.get((req.symbol, req.exchange), None)
        if not extra_info:
            self.gateway.write_log(
                f"找不到匹配的合约：{req.symbol}和{req.exchange.value}")
            return

        tap_contract = TapAPIContract()
        tap_contract.Commodity.ExchangeNo = EXCHANGE_VT2TAP[req.exchange]
        tap_contract.Commodity.CommodityType = extra_info.commodity_type
        tap_contract.Commodity.CommodityNo = extra_info.commodity_no
        tap_contract.ContractNo1 = req.symbol
        tap_contract.CallOrPutFlag1 = TAPI_CALLPUT_FLAG_NONE
        tap_contract.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE

        self.api.SubscribeQuote(tap_contract)


class TradeApi(ITapTradeAPINotify):
    """"""

    def __init__(self, gateway: TapGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.api = None

    def OnConnect(self):
        """"""
        self.gateway.write_log("交易服务器连接成功")

    def OnRspLogin(self, errorCode: int, info: TapAPITradeLoginRspInfo):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            error_msg = error_to_str(errorCode)
            self.gateway.write_log(f"交易服务器登录失败：{error_msg}")
        else:
            self.gateway.write_log("交易服务器登录成功")

    def OnRspQryAccount(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIFundData
    ):
        req = TapAPIFundReq()
        req.AccountNo = info.AccountNo
        self.api.QryFund(req)

    def OnRspQryFund(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIAccountInfo
    ):
        self.update_account(info)

    def update_account(self, info: TapAPIAccountInfo):
        """"""
        account = AccountData()

    def connect(self, username: str, password: str, host: str, port: int, auth_code: str):
        """"""
        # Create API object
        info = TapTradeAPIApplicationInfo()
        info.AuthCode = auth_code

        self.api, iResult = CreateITapTradeAPI(info)
        if not self.api:
            self.gateway.write_log("交易API初始化失败")
            return

        # Set server address and port
        self.api.SetAPINotify(self)
        self.api.SetHostAddress(host, port, False)

        # Start connection
        login_auth = TapAPITradeLoginAuth()
        login_auth.UserNo = username
        login_auth.Password = password
        login_auth.ISModifyPassword = APIYNFLAG_NO

        self.api.Login(login_auth)

    def send_order(self, req: OrderRequest):
        """"""
        pass

    def cancel_order(self, req: CancelRequest):
        """"""
        pass

    def query_account(self):
        """"""
        req = TapAPIAccQryReq()
        self.api.QryAccount(req)

    def query_position(self):
        """"""
        pass


def parse_datetime(dt_str: str):
    """"""
    try:
        dt = datetime.strptime(dt_str, "%Y-%m-%d %H:%M:%S.%f")
    except ValueError:
        dt = datetime(1970, 1, 1)
    return dt


def error_to_str(err_code: int) -> str:
    """"""
    try:
        return error_map[err_code]
    except KeyError:
        return f"Unknown error({err_code})"


@dataclass
class ExtraInfo:
    """"""
    name: str
    commodity_type: int
    commodity_no: str


@dataclass
class CommodityInfo:
    """"""
    name: str
    size: int
    pricetick: float
