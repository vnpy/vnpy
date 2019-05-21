import sys
from dataclasses import dataclass
from datetime import datetime
from typing import Any, Dict, Optional, Tuple

from vnpy.api.itap.vnitap import (APIYNFLAG_NO, AsyncDispatchException, CreateTapQuoteAPI,
                                  FreeTapQuoteAPI, ITapQuoteAPI, ITapQuoteAPINotify,
                                  TAPIERROR_SUCCEED, TAPI_CALLPUT_FLAG_NONE,
                                  TAPI_COMMODITY_TYPE_FUTURES, TAPI_COMMODITY_TYPE_INDEX,
                                  TAPI_COMMODITY_TYPE_OPTION, TAPI_COMMODITY_TYPE_SPOT,
                                  TAPI_COMMODITY_TYPE_STOCK, TapAPIApplicationInfo, TapAPIContract,
                                  TapAPIQuotLoginRspInfo, TapAPIQuoteCommodityInfo,
                                  TapAPIQuoteContractInfo, TapAPIQuoteLoginAuth, TapAPIQuoteWhole,
                                  set_async_callback_exception_handler)

from vnpy.api.itap.error_codes import error_map
from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Product
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    CancelRequest,
    ContractData,
    OrderRequest,
    SubscribeRequest,
    TickData)

PRODUCT_TYPE_ITAP2VT = {
    TAPI_COMMODITY_TYPE_SPOT: Product.SPOT,
    TAPI_COMMODITY_TYPE_FUTURES: Product.FUTURES,
    TAPI_COMMODITY_TYPE_OPTION: Product.OPTION,
    TAPI_COMMODITY_TYPE_INDEX: Product.INDEX,
    TAPI_COMMODITY_TYPE_STOCK: Product.EQUITY,
}

EXCHANGE_ITAP2VT = {
    'SGX': Exchange.SGX,
    'INE': Exchange.INE,
    'APEX': Exchange.APEX,
    'NYMEX': Exchange.NYMEX,
    'LME': Exchange.LME,
    'COMEX': Exchange.COMEX,  # verify: I added this exchange in vnpy, is this correct?
    'CBOT': Exchange.CBOT,
    'HKEX': Exchange.HKFE,  # verify: is this correct?,
    'CME': Exchange.CME,
}
EXCHANGE_VT2ITAP = {v: k for k, v in EXCHANGE_ITAP2VT.items()}


def parse_datetime(dt_str: str):
    # todo: 我不知道这个时间所用的是哪种时间
    # yyyy-MM-dd hh:nn:ss.xxx
    return datetime.strptime(dt_str, "%Y-%m-%d %H:%M:%S.%f")


def error_to_str(err_code: int) -> str:
    try:
        return error_map[err_code]
    except KeyError:
        return f"Unknown error({err_code})"


@dataclass()
class ContractExtraInfo:
    """
    缓存一些ITAP API不直接提供的信息，而且仅仅保存这些信息。Symbol之类的作为键就不保存在这里面了
    """
    name: str
    commodity_type: int
    commodity_no: str


class QuoteNotify(ITapQuoteAPINotify):

    def __init__(self, gateway: "ITapGateway"):
        super().__init__()
        self.gateway = gateway

    @property
    def api(self) -> ITapQuoteAPI:
        return self.gateway.api

    def OnRspLogin(self, errorCode: int, info: TapAPIQuotLoginRspInfo) -> Any:
        if self.gateway.if_error_write_log(errorCode, "OnRspQryCommodity"):
            self.gateway.write_log("行情服务器登录失败")
            return
        self.gateway.write_log("行情服务器登录成功")

    def OnAPIReady(self) -> Any:
        print("OnApiReady")
        error_code, sessionId = self.api.QryCommodity()
        if self.gateway.if_error_write_log(error_code, "api.QryCommodity"):
            return

    def OnDisconnect(self, reasonCode: int) -> Any:
        print(f"OnDisconnect : {error_to_str(reasonCode)}")

    def OnRspQryCommodity(
        self,
        sessionID: int,
        errorCode: int,
        isLast: int,
        info: TapAPIQuoteCommodityInfo,
    ) -> Any:
        if self.gateway.if_error_write_log(errorCode, "OnRspQryCommodity"):
            return

        error_code, session_id = self.api.QryContract(info.Commodity)
        if self.gateway.if_error_write_log(error_code, "api.QryContract"):
            return

    def OnRspQryContract(
        self, sessionID: int, errorCode: int, isLast: int, info: TapAPIQuoteContractInfo
    ) -> Any:
        if self.gateway.if_error_write_log(errorCode, "OnRspQryContract"):
            return
        if info is not None:  # isLast == True ==> info is None
            symbol = info.Contract.ContractNo1  # what's the different between No1 and No2?
            exchange = EXCHANGE_ITAP2VT[info.Contract.Commodity.ExchangeNo]
            name = info.ContractName
            contract_data = ContractData(
                gateway_name=self.gateway.gateway_name,
                symbol=symbol,
                exchange=exchange,
                name=name,
                product=PRODUCT_TYPE_ITAP2VT.get(info.ContractType, Product.EQUITY),
                size=1,  # verify: no key for this
                pricetick=1,  # verify: no key for this
                min_volume=1,  # verify: no key for this
                # ...
            )
            contract_extra_info = ContractExtraInfo(
                name=name,
                commodity_type=info.Contract.Commodity.CommodityType,
                commodity_no=info.Contract.Commodity.CommodityNo,
            )
            self.gateway.contract_extra_infos[(symbol, exchange)] = contract_extra_info
            self.gateway.on_contract(contract_data)

    def OnRspSubscribeQuote(
        self, sessionID: int, errorCode: int, isLast: int, info: TapAPIQuoteWhole
    ) -> Any:
        print("OnRspSubscribeQuote")
        if self.gateway.if_error_write_log(errorCode, "OnRspSubscribeQuote"):
            return

    def OnRspUnSubscribeQuote(
        self, sessionID: int, errorCode: int, isLast: int, info: TapAPIContract
    ) -> Any:
        print("OnRspUnSubscribeQuote")
        if self.gateway.if_error_write_log(errorCode, "OnRspUnSubscribeQuote"):
            return

    def OnRtnQuote(self, info: TapAPIQuoteWhole) -> Any:
        symbol = info.Contract.ContractNo1
        exchange = EXCHANGE_ITAP2VT[info.Contract.Commodity.ExchangeNo]
        extra_info = self.gateway.contract_extra_infos[(symbol, exchange)]
        tick = TickData(
            gateway_name=self.gateway.gateway_name,
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
        )
        self.gateway.on_tick(tick=tick)


class ITapGateway(BaseGateway):
    default_setting = {
        "auth_code": "",
        "quote_host": "123.15.58.21",
        "quote_port": 7171,
        "quote_username": "",
        "quote_password": "",
    }
    exchanges = list(EXCHANGE_VT2ITAP.keys())

    def __init__(self, event_engine: EventEngine):
        super().__init__(event_engine, "ITAP")
        self.api: Optional[ITapQuoteAPI] = None
        self.quote_notify = QuoteNotify(self)

        # [symbol, exchange] : [CommodityType, CommodityNo]
        self.contract_extra_infos: Dict[Tuple[str, Exchange], ContractExtraInfo] = {}
        set_async_callback_exception_handler(self._async_callback_exception_handler)

    def connect(self, setting: dict):
        auth_code = setting["auth_code"]
        quote_host = setting["quote_host"]
        quote_port = setting["quote_port"]
        quote_username = setting["quote_username"]
        quote_password = setting["quote_password"]
        # print("quote version:", GetTapQuoteAPIVersion())
        # print("trade version:", GetITapTradeAPIVersion())

        ai = TapAPIApplicationInfo()
        ai.AuthCode = auth_code

        # iResult是输出参数，Python中只能用返回值作为输出。
        # 具体输出了哪些，可以看pyi的注释
        api, iResult = CreateTapQuoteAPI(ai)
        if api is None:
            self.if_error_write_log(iResult, "CreateTapQuoteAPI")
            return

        assert self.api is None
        self.api = api

        api.SetAPINotify(self.quote_notify)
        error_code: int = api.SetHostAddress(quote_host, quote_port)
        if self.if_error_write_log(error_code, "SetHostAddress"):
            return

        # login
        la = TapAPIQuoteLoginAuth()
        la.UserNo = quote_username
        la.Password = quote_password
        la.ISDDA = APIYNFLAG_NO
        la.ISModifyPassword = APIYNFLAG_NO
        error_code: int = api.Login(la)  # async
        if self.if_error_write_log(error_code, "api.Login"):
            return

    def close(self):
        self.api.SetAPINotify(None)
        self.quote_notify = None
        FreeTapQuoteAPI(self.api)
        self.api = None
        pass

    def subscribe(self, req: SubscribeRequest):
        contract = TapAPIContract()
        extra_info = self.contract_extra_infos[(req.symbol, req.exchange)]
        contract.Commodity.ExchangeNo = EXCHANGE_VT2ITAP[req.exchange]
        contract.Commodity.CommodityType = extra_info.commodity_type
        contract.Commodity.CommodityNo = extra_info.commodity_no
        contract.ContractNo1 = req.symbol
        contract.CallOrPutFlag1 = TAPI_CALLPUT_FLAG_NONE
        contract.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE
        error_code, session_id = self.api.SubscribeQuote(contract)
        if self.if_error_write_log(error_code, "api.SubscribeQuote"):
            return

    def send_order(self, req: OrderRequest) -> str:
        pass

    def cancel_order(self, req: CancelRequest):
        pass

    def query_account(self):
        pass

    def query_position(self):
        pass

    def _async_callback_exception_handler(self, e: AsyncDispatchException):
        error_str = (f"发生内部错误，位置：\n{e.instance}.{e.function_name}，详细信息：\n"
                     f"{e.what}\n"
                     )
        print(error_str, file=sys.stderr, flush=True)
        self.write_log(error_str)
        return True

    def if_error_write_log(self, error_code: int, function: str):
        """
        检查返回值，如果发生错误，调用write_log报告该错误，并返回True
        :return: 若有错误发生，返回True
        """
        if TAPIERROR_SUCCEED != error_code:
            error_msg = f"调用{function}时出错：\n{error_to_str(error_code)}"
            self.write_log(error_msg)
            print(error_msg, file=sys.stderr)
            return True
