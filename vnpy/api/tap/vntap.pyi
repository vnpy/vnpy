# noinspection PyUnresolvedReferences
import typing
if typing.TYPE_CHECKING:
    from typing import *
    # noinspection PyUnresolvedReferences
    from enum import Enum
    from .vntap import *


def set_async_callback_exception_handler(handler: Callable[[AsyncDispatchException], None]):
    """
    set a customize exception handler for async callback in this module(pyd)
    \a handler should return True if it handles that exception,

    :note: If the return value of \a handler is not True, exception will be re-thrown.
    """
    ...


class AsyncDispatchException:
    what: str
    instance: object
    function_name: str


from . import vntap_ITapTrade as ITapTrade
class TapAPIApplicationInfo():
    
    
    AuthCode: str
    KeyOperationLogPath: str
    
    
class TapAPICommodity():
    
    
    ExchangeNo: str
    CommodityType: str
    CommodityNo: str
    
    
class TapAPIContract():
    
    
    Commodity: TapAPICommodity
    ContractNo1: str
    StrikePrice1: str
    CallOrPutFlag1: str
    ContractNo2: str
    StrikePrice2: str
    CallOrPutFlag2: str
    
    
class TapAPIExchangeInfo():
    
    
    ExchangeNo: str
    ExchangeName: str
    
    
class TapAPIChangePasswordReq():
    
    
    OldPassword: str
    NewPassword: str
    
    
class TapAPIQuoteLoginAuth():
    
    
    UserNo: str
    ISModifyPassword: str
    Password: str
    NewPassword: str
    QuoteTempPassword: str
    ISDDA: str
    DDASerialNo: str
    
    
class TapAPIQuotLoginRspInfo():
    
    
    UserNo: str
    UserType: int
    UserName: str
    QuoteTempPassword: str
    ReservedInfo: str
    LastLoginIP: str
    LastLoginProt: int
    LastLoginTime: str
    LastLogoutTime: str
    TradeDate: str
    LastSettleTime: str
    StartTime: str
    InitTime: str
    
    
class TapAPIQuoteCommodityInfo():
    
    
    Commodity: TapAPICommodity
    CommodityName: str
    CommodityEngName: str
    ContractSize: float
    CommodityTickSize: float
    CommodityDenominator: int
    CmbDirect: str
    CommodityContractLen: int
    IsDST: str
    RelateCommodity1: TapAPICommodity
    RelateCommodity2: TapAPICommodity
    
    
class TapAPIQuoteContractInfo():
    
    
    Contract: TapAPIContract
    ContractType: str
    QuoteUnderlyingContract: str
    ContractName: str
    ContractExpDate: str
    LastTradeDate: str
    FirstNoticeDate: str
    
    
class TapAPIQuoteWhole():
    
    
    Contract: TapAPIContract
    CurrencyNo: str
    TradingState: str
    DateTimeStamp: str
    QPreClosingPrice: float
    QPreSettlePrice: float
    QPrePositionQty: int
    QOpeningPrice: float
    QLastPrice: float
    QHighPrice: float
    QLowPrice: float
    QHisHighPrice: float
    QHisLowPrice: float
    QLimitUpPrice: float
    QLimitDownPrice: float
    QTotalQty: int
    QTotalTurnover: float
    QPositionQty: int
    QAveragePrice: float
    QClosingPrice: float
    QSettlePrice: float
    QLastQty: int
    QBidPrice: List[float]
    QBidQty: List[int]
    QAskPrice: List[float]
    QAskQty: List[int]
    QImpliedBidPrice: float
    QImpliedBidQty: int
    QImpliedAskPrice: float
    QImpliedAskQty: int
    QPreDelta: float
    QCurrDelta: float
    QInsideQty: int
    QOutsideQty: int
    QTurnoverRate: float
    Q5DAvgQty: int
    QPERatio: float
    QTotalValue: float
    QNegotiableValue: float
    QPositionTrend: int
    QChangeSpeed: float
    QChangeRate: float
    QChangeValue: float
    QSwing: float
    QTotalBidQty: int
    QTotalAskQty: int
    UnderlyContract: TapAPIContract
    
    
class ITapQuoteAPINotify():
    
    
    
    
    def OnRspLogin(self, errorCode: int, info: TapAPIQuotLoginRspInfo)->None:
        ...
    def OnAPIReady(self, )->None:
        ...
    def OnDisconnect(self, reasonCode: int)->None:
        ...
    def OnRspQryCommodity(self, sessionID: int, errorCode: int, isLast: str, info: TapAPIQuoteCommodityInfo)->None:
        ...
    def OnRspQryContract(self, sessionID: int, errorCode: int, isLast: str, info: TapAPIQuoteContractInfo)->None:
        ...
    def OnRspSubscribeQuote(self, sessionID: int, errorCode: int, isLast: str, info: TapAPIQuoteWhole)->None:
        ...
    def OnRspUnSubscribeQuote(self, sessionID: int, errorCode: int, isLast: str, info: TapAPIContract)->None:
        ...
    def OnRtnQuote(self, info: TapAPIQuoteWhole)->None:
        ...
class ITapQuoteAPI():
    
    
    
    
    def SetAPINotify(self, apiNotify: ITapQuoteAPINotify)->int:
        ...
    def SetHostAddress(self, IP: str, port: int)->int:
        ...
    def Login(self, loginAuth: TapAPIQuoteLoginAuth)->int:
        ...
    def Disconnect(self, )->int:
        ...
    def QryCommodity(self, )->Tuple[int,int]:
        return "retv","sessionID"
    def QryContract(self, qryReq: TapAPICommodity)->Tuple[int,int]:
        return "retv","sessionID"
    def SubscribeQuote(self, contract: TapAPIContract)->Tuple[int,int]:
        return "retv","sessionID"
    def UnSubscribeQuote(self, contract: TapAPIContract)->Tuple[int,int]:
        return "retv","sessionID"
TAPISTR_10 = str
TAPISTR_20 = str
TAPISTR_30 = str
TAPISTR_40 = str
TAPISTR_50 = str
TAPISTR_70 = str
TAPISTR_100 = str
TAPISTR_300 = str
TAPISTR_500 = str
TAPISTR_2000 = str
TAPIAUTHCODE = str
TAPICHAR = str
TAPIINT32 = int
TAPIUINT32 = int
TAPIINT64 = int
TAPIUINT64 = int
TAPIUINT16 = int
TAPIUINT8 = int
TAPIREAL64 = float
TAPIYNFLAG = str
TAPIDTSTAMP = str
TAPIDATETIME = str
TAPIDATE = str
TAPITIME = str
TAPILOGLEVEL = str
TAPICommodityType = str
TAPICallOrPutFlagType = str
TAPIQPRICE = float
TAPIQVOLUME = int
TAPIQDIFF = int
APIYNFLAG_YES: str
APIYNFLAG_NO: str
APILOGLEVEL_NONE: str
APILOGLEVEL_ERROR: str
APILOGLEVEL_WARNING: str
APILOGLEVEL_DEBUG: str
TAPI_COMMODITY_TYPE_NONE: str
TAPI_COMMODITY_TYPE_SPOT: str
TAPI_COMMODITY_TYPE_FUTURES: str
TAPI_COMMODITY_TYPE_OPTION: str
TAPI_COMMODITY_TYPE_SPREAD_MONTH: str
TAPI_COMMODITY_TYPE_SPREAD_COMMODITY: str
TAPI_COMMODITY_TYPE_BUL: str
TAPI_COMMODITY_TYPE_BER: str
TAPI_COMMODITY_TYPE_STD: str
TAPI_COMMODITY_TYPE_STG: str
TAPI_COMMODITY_TYPE_PRT: str
TAPI_COMMODITY_TYPE_BLT: str
TAPI_COMMODITY_TYPE_BRT: str
TAPI_COMMODITY_TYPE_DIRECTFOREX: str
TAPI_COMMODITY_TYPE_INDIRECTFOREX: str
TAPI_COMMODITY_TYPE_CROSSFOREX: str
TAPI_COMMODITY_TYPE_INDEX: str
TAPI_COMMODITY_TYPE_STOCK: str
TAPI_COMMODITY_TYPE_SPOT_TRADINGDEFER: str
TAPI_COMMODITY_TYPE_FUTURE_LOCK: str
TAPI_COMMODITY_TYPE_EFP: str
TAPI_CALLPUT_FLAG_CALL: str
TAPI_CALLPUT_FLAG_PUT: str
TAPI_CALLPUT_FLAG_NONE: str
TAPIERROR_SUCCEED: int
TAPIERROR_ConnectFail: int
TAPIERROR_LinkAuthFail: int
TAPIERROR_HostUnavailable: int
TAPIERROR_SendDataError: int
TAPIERROR_TestIDError: int
TAPIERROR_NotReadyTestNetwork: int
TAPIERROR_CurTestNotOver: int
TAPIERROR_NOFrontAvailable: int
TAPIERROR_DataPathAvaiable: int
TAPIERROR_RepeatLogin: int
TAPIERROR_InnerError: int
TAPIERROR_LastReqNotFinish: int
TAPIERROR_InputValueError: int
TAPIERROR_AuthCode_Invalid: int
TAPIERROR_AuthCode_Expired: int
TAPIERROR_AuthCode_TypeNotMatch: int
TAPIERROR_API_NotReady: int
TAPIERROR_UDP_LISTEN_FAILED: int
TAPIERROR_UDP_LISTENING: int
TAPIERROR_NotImplemented: int
TAPIERROR_CallOneTimeOnly: int
TAPIERROR_Frequently: int
TAPIERROR_INPUTERROR_NULL: int
TAPIERROR_INPUTERROR_TAPIYNFLAG: int
TAPIERROR_INPUTERROR_TAPILOGLEVEL: int
TAPIERROR_INPUTERROR_TAPICommodityType: int
TAPIERROR_INPUTERROR_TAPICallOrPutFlagType: int
TAPIERROR_INPUTERROR_TAPIAccountType: int
TAPIERROR_INPUTERROR_TAPIAccountState: int
TAPIERROR_INPUTERROR_TAPIAccountFamilyType: int
TAPIERROR_INPUTERROR_TAPIOrderTypeType: int
TAPIERROR_INPUTERROR_TAPIOrderSourceType: int
TAPIERROR_INPUTERROR_TAPITimeInForceType: int
TAPIERROR_INPUTERROR_TAPISideType: int
TAPIERROR_INPUTERROR_TAPIPositionEffectType: int
TAPIERROR_INPUTERROR_TAPIHedgeFlagType: int
TAPIERROR_INPUTERROR_TAPIOrderStateType: int
TAPIERROR_INPUTERROR_TAPICalculateModeType: int
TAPIERROR_INPUTERROR_TAPIMatchSourceType: int
TAPIERROR_INPUTERROR_TAPIOpenCloseModeType: int
TAPIERROR_INPUTERROR_TAPIFutureAlgType: int
TAPIERROR_INPUTERROR_TAPIOptionAlgType: int
TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType: int
TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType: int
TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType: int
TAPIERROR_INPUTERROR_TAPICmbDirectType: int
TAPIERROR_INPUTERROR_TAPIDeliveryModeType: int
TAPIERROR_INPUTERROR_TAPIContractTypeType: int
TAPIERROR_INPUTERROR_TAPITacticsTypeType: int
TAPIERROR_INPUTERROR_TAPIORDERACT: int
TAPIERROR_INPUTERROR_TAPITriggerConditionType: int
TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType: int
TAPIERROR_INPUTERROR_TAPITradingStateType: int
TAPIERROR_INPUTERROR_TAPIMarketLevelType: int
TAPIERROR_INPUTERROR_TAPIOrderQryTypeType: int
TAPIERROR_DISCONNECT_CLOSE_INIT: int
TAPIERROR_DISCONNECT_CLOSE_PASS: int
TAPIERROR_DISCONNECT_READ_ERROR: int
TAPIERROR_DISCONNECT_WRITE_ERROR: int
TAPIERROR_DISCONNECT_BUF_FULL: int
TAPIERROR_DISCONNECT_IOCP_ERROR: int
TAPIERROR_DISCONNECT_PARSE_ERROR: int
TAPIERROR_DISCONNECT_CONNECT_TIMEOUT: int
TAPIERROR_DISCONNECT_INIT_ERROR: int
TAPIERROR_DISCONNECT_HAS_CONNECTED: int
TAPIERROR_DISCONNECT_HAS_EXIT: int
TAPIERROR_DISCONNECT_TRY_LATER: int
TAPIERROR_DISCONNECT_HEARTBEAT_FAILED: int
TAPIERROR_LOGIN: int
TAPIERROR_LOGIN_USER: int
TAPIERROR_LOGIN_DDA: int
TAPIERROR_LOGIN_LICENSE: int
TAPIERROR_LOGIN_MODULE: int
TAPIERROR_LOGIN_FORCE: int
TAPIERROR_LOGIN_STATE: int
TAPIERROR_LOGIN_PASS: int
TAPIERROR_LOGIN_RIGHT: int
TAPIERROR_LOGIN_COUNT: int
TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES: int
TAPIERROR_LOGIN_USER_EXPIRED: int
TAPIERROR_LOGIN_NO_ACCOUNT: int
TAPIERROR_LOGIN_NO_JGT: int
TAPIERROR_LOGIN_ERROR_TIMES: int
TAPIERROR_LOGIN_ERROR_AUTHTYPE: int
TAPIERROR_LOGIN_ERROR_AUTHEXPIRED: int
TAPIERROR_LOGIN_ERROR_PASSWDEXPIRED: int
TAPIERROR_USERINFO_QRY: int
TAPIERROR_USERALLRIGHT_QRY: int
TAPIERROR_USERALLACCOUNT_QRY: int
TAPIERROR_USERPASSWORD_MOD: int
TAPIERROR_USERPASSWORD_MOD_SOURCE: int
TAPIERROR_USERPASSWORD_MOD_SAME: int
TAPIERROR_USERPASSWORD_MOD_COMPLEXITY: int
TAPIERROR_ACCOUNTINFO_QRY: int
TAPIERROR_TRADENO_QRY: int
TAPIERROR_CONTRACTINFO_QRY: int
TAPIERROR_SPECIALOPTIONFUTURE_QRY: int
TAPIERROR_COMMODITYORDERTYPE_QRY: int
TAPIERROR_ORDERTIMEINFORCE_QRY: int
TAPIERROR_USER_ORDER_FREQUENCE_QRY: int
TAPIERROR_ORDERINSERT_ACCOUNT: int
TAPIERROR_ORDERINSERT_ACCOUNT_STATE: int
TAPIERROR_ORDERINSERT_SIDE_TRADE: int
TAPIERROR_ORDERINSERT_OPTIONS_TRADE: int
TAPIERROR_ORDERINSERT_COMMODITY_TRADE: int
TAPIERROR_ORDERINSERT_OPEN_RIGHT: int
TAPIERROR_ORDERINSERT_RISK_CHECK: int
TAPIERROR_ORDERINSERT_CONTRACT: int
TAPIERROR_ORDERINSERT_TRADEROUTE: int
TAPIERROR_ORDERINSERT_POSITIONMAX: int
TAPIERROR_ORDER_NOTRADE: int
TAPIERROR_ORDER_CLOSE: int
TAPIERROR_ORDERINSERT_NOTENOUGHFUND: int
TAPIERROR_ORDERINSERT_ORDERTYPE: int
TAPIERROR_ORDERINSERT_TIMEINFORCE: int
TAPIERROR_ORDERINSERT_NO_TACTICS: int
TAPIERROR_ORDERINSERT_POSITION_CANNOT_CLOSE: int
TAPIERROR_ORDERINSERT_AUTOCHECK_FAIL: int
TAPIERROR_ORDERINSERT_LME_NOTREADY: int
TAPIERROR_ORDERINSERT_CLOSEMODE: int
TAPIERROR_ORDERINSERT_PARENTNOTENOUGHFUND: int
TAPIERROR_SWAP_CONTRACT: int
TAPIERROR_USERNO_NOTHAS_ACCOUNT: int
TAPIERROR_UPPERCHANNEL_BROKEN: int
TAPIERROR_UPPERCHANNEL_NOT_EXIST: int
TAPIERROR_ORDERDELETE_NOT_SYSNO: int
TAPIERROR_ORDERDELETE_NOT_STATE: int
TAPIERROR_ORDERACTIVE_NOT_STATE: int
TAPIERROR_ORDERCHECK_NOT_STATE: int
TAPIERROR_ORDERCHECK_FAIL: int
TAPIERROR_ORDERMODIFY_NOT_STATE: int
TAPIERROR_ORDERMODIFY_BACK_INPUT: int
TAPIERROR_ORDERINSERT_FEE: int
TAPIERROR_ORDERINSERT_MARGIN: int
TAPIERROR_ORDER_NO_PERMIT: int
TAPIERROR_RSPQUOTE_NO_PERMIT: int
TAPIERROR_RSPQUOTE_CHILD_NO_PERMIT: int
TAPIERROR_TRADENO_NOT_FIND: int
TAPIERROR_ORDER_NO_CLOSE: int
TAPIERROR_QRY_QUOTE_NO_PERMIT: int
TAPIERROR_EXPIREDATE_NO_PERMIT: int
TAPIERROR_CMB_NO_PERMIT: int
TAPIERROR_ORDERSERVER_NO_PERMIT: int
TAPIERROR_POSITION_CANNOT_EXEC_OR_ABANDON: int
TAPIERROR_ORDERCHECK_NO_PERMIT: int
TAPIERROR_ORDERMAXOPENVOL_NO_PERMIT: int
TAPIERROR_ORDER_QTY_NO_PERMIT: int
TAPIERROR_ORDER_APPLY_NO_PERMIT: int
TAPIERROR_ORDER_FREQ_OVERRUN: int
TAPIERROR_COMB_NO_SIDEORHEDGE: int
TAPIERROR_ORDER_FREQUENCY: int
TAPIERROR_ORDER_QUERYING: int
TAPIERROR_SUBSCRIBEQUOTE_MAX: int
TAPIERROR_SUBSCRIBEQUOTE_EXCHANGE_MAX: int
TAPIERROR_SUBSCRIBEQUOTE_NO_RIGHT: int
TAPIERROR_SUBSCRIBEQUOTE_NO_EXCHANGE_RIGHT: int
TAPIERROR_SUBSCRIBEQUOTE_COMMODITY_NOT_EXIST: int
TAPIERROR_SUBSCRIBEQUOTE_CONTRACT_MAY_NOT_EXIST: int
TAPIERROR_QUOTEFRONT_UNKNOWN_PROTOCOL: int
def CreateITapTradeAPI(appInfo: ITapTrade.TapAPIApplicationInfo)->Tuple[ITapTrade.ITapTradeAPI,int]:
    return "retv","iResult"
def FreeITapTradeAPI(apiObj: ITapTrade.ITapTradeAPI)->None:
    ...
def GetITapTradeAPIVersion()->str:
    ...
def SetITapTradeAPIDataPath(path: str)->int:
    ...
def SetITapTradeAPILogLevel(level: str)->int:
    ...
def GetITapErrorDescribe(errorCode: int)->str:
    ...
def CreateTapQuoteAPI(appInfo: TapAPIApplicationInfo)->Tuple[ITapQuoteAPI,int]:
    return "retv","iResult"
def FreeTapQuoteAPI(apiObj: ITapQuoteAPI)->None:
    ...
def GetTapQuoteAPIVersion()->str:
    ...
def SetTapQuoteAPIDataPath(path: str)->int:
    ...
def SetTapQuoteAPILogLevel(level: str)->int:
    ...

