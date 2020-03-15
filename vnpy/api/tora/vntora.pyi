# noinspection PyUnresolvedReferences
import typing
if typing.TYPE_CHECKING:
    from typing import *
    # noinspection PyUnresolvedReferences
    from enum import Enum
    from .vntora import *


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


class CTORATstpFensUserInfoField():
    
    
    LogInAccount: str
    LogInAccountType: str
    
    
class CTORATstpEffectPriceMarketDataField():
    
    
    ExchangeID: str
    SecurityID: str
    LastPrice: float
    TotalVolume: int
    Turnover: float
    UpdateTime: str
    UpdateMillisec: int
    
    
class CTORATstpEffectVolumeMarketDataField():
    
    
    ExchangeID: str
    SecurityID: str
    LastPrice: float
    TotalVolume: int
    Turnover: float
    UpdateTime: str
    UpdateMillisec: int
    
    
class CTORATstpFundsFlowMarketDataField():
    
    
    ExchangeID: str
    SecurityID: str
    UpdateTime: str
    UpdateMillisec: int
    RetailBuyTurnover: float
    RetailBuyVolume: int
    RetailBuyAmount: int
    RetailSellTurnover: float
    RetailSellVolume: int
    RetailSellAmount: int
    MiddleBuyTurnover: float
    MiddleBuyVolume: int
    MiddleBuyAmount: int
    MiddleSellTurnover: float
    MiddleSellVolume: int
    MiddleSellAmount: int
    LargeBuyTurnover: float
    LargeBuyVolume: int
    LargeBuyAmount: int
    LargeSellTurnover: float
    LargeSellVolume: int
    LargeSellAmount: int
    InstitutionBuyTurnover: float
    InstitutionBuyVolume: int
    InstitutionBuyAmount: int
    InstitutionSellTurnover: float
    InstitutionSellVolume: int
    InstitutionSellAmount: int
    
    
class CTORATstpReqUserLoginField():
    
    
    LogInAccount: str
    LogInAccountType: str
    Password: str
    UserProductInfo: str
    InterfaceProductInfo: str
    ProtocolInfo: str
    MacAddress: str
    OneTimePassword: str
    ClientIPAddress: str
    Lang: str
    TerminalInfo: str
    GWMacAddress: str
    GWInnerIPAddress: str
    GWOuterIPAddress: str
    DepartmentID: str
    HDSerial: str
    AuthMode: str
    DeviceID: str
    DeviceSerial: str
    
    
class CTORATstpRspUserLoginField():
    
    
    LoginTime: str
    LogInAccount: str
    LogInAccountType: str
    SystemName: str
    FrontID: int
    SessionID: int
    MaxOrderRef: str
    PrivateFlowCount: int
    PublicFlowCount: int
    TradingDay: str
    UserID: str
    UserName: str
    UserType: str
    DepartmentID: str
    ClientIPAddress: str
    MacAddress: str
    HDSerial: str
    CommFlux: int
    
    
class CTORATstpRspInfoField():
    
    
    ErrorID: int
    ErrorMsg: str
    
    
class CTORATstpUserLogoutField():
    
    
    UserID: str
    
    
class CTORATstpForceUserLogoutField():
    
    
    UserID: str
    
    
class CTORATstpUserPasswordUpdateField():
    
    
    UserID: str
    OldPassword: str
    NewPassword: str
    
    
class CTORATstpReqInputDeviceSerialField():
    
    
    UserID: str
    DeviceID: str
    DeviceSerial: str
    
    
class CTORATstpRspInputDeviceSerialField():
    
    
    UserID: str
    
    
class CTORATstpActivateUserField():
    
    
    UserID: str
    
    
class CTORATstpVerifyUserPasswordField():
    
    
    UserID: str
    Password: str
    
    
class CTORATstpInputOrderField():
    
    
    InvestorID: str
    SecurityID: str
    OrderRef: str
    UserID: str
    OrderPriceType: str
    Direction: str
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: str
    VolumeCondition: str
    MinVolume: int
    ForceCloseReason: str
    RequestID: int
    UserForceClose: int
    IsSwapOrder: int
    ExchangeID: str
    ShareholderID: str
    BusinessUnitID: str
    AccountID: str
    IPAddress: str
    MacAddress: str
    CreditPositionType: str
    OrderSysID: str
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    TransfereePbuID: str
    Operway: str
    CondCheck: str
    HDSerial: str
    
    
class CTORATstpOrderField():
    
    
    InvestorID: str
    SecurityID: str
    OrderRef: str
    UserID: str
    OrderPriceType: str
    Direction: str
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: str
    VolumeCondition: str
    MinVolume: int
    ForceCloseReason: str
    RequestID: int
    OrderLocalID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    ExchangeInstID: str
    TraderID: str
    OrderSubmitStatus: str
    TradingDay: str
    OrderSysID: str
    OrderStatus: str
    OrderType: str
    VolumeTraded: int
    VolumeTotal: int
    InsertDate: str
    InsertTime: str
    CancelTime: str
    ActiveTraderID: str
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    UserForceClose: int
    ActiveUserID: str
    BusinessUnitID: str
    AccountID: str
    IPAddress: str
    MacAddress: str
    CreditPositionType: str
    BInfo: str
    SInfo: str
    IInfo: int
    TransfereePbuID: str
    Operway: str
    DepartmentID: str
    ProperCtrlBusinessType: str
    ProperCtrlPassFlag: str
    CondCheck: str
    IsCacheOrder: int
    Turnover: float
    RtnFloatInfo: float
    RtnIntInfo: int
    
    
class CTORATstpUserRefField():
    
    
    UserID: str
    
    
class CTORATstpInputOrderActionField():
    
    
    InvestorID: str
    OrderActionRef: str
    OrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OrderSysID: str
    ActionFlag: str
    LimitPrice: float
    VolumeChange: int
    UserID: str
    SecurityID: str
    IPAddress: str
    MacAddress: str
    CancelOrderLocalID: str
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: str
    HDSerial: str
    
    
class CTORATstpOrderActionField():
    
    
    InvestorID: str
    OrderActionRef: str
    OrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OrderSysID: str
    ActionFlag: str
    LimitPrice: float
    VolumeChange: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    OrderLocalID: str
    ActionLocalID: str
    ShareholderID: str
    OrderActionStatus: str
    UserID: str
    StatusMsg: str
    SecurityID: str
    IPAddress: str
    MacAddress: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: str
    
    
class CTORATstpTradeField():
    
    
    InvestorID: str
    SecurityID: str
    UserID: str
    ExchangeID: str
    TradeID: str
    Direction: str
    OrderSysID: str
    MarketID: str
    ShareholderID: str
    ExchangeInstID: str
    OffsetFlag: str
    HedgeFlag: str
    Price: float
    Volume: int
    TradeDate: str
    TradeTime: str
    TraderID: str
    OrderLocalID: str
    TradingDay: str
    BusinessUnitID: str
    AccountID: str
    OrderRef: str
    DepartmentID: str
    
    
class CTORATstpMarketStatusField():
    
    
    MarketID: str
    MarketStatus: str
    
    
class CTORATstpInputCondOrderField():
    
    
    ExchangeID: str
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    Direction: str
    OrderPriceType: str
    OrderVolumeType: str
    TimeCondition: str
    VolumeCondition: str
    LimitPrice: float
    VolumeTotalOriginal: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    CondOrderRef: str
    AccountID: str
    UserID: str
    RequestID: int
    IPAddress: str
    MacAddress: str
    CondOrderID: int
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: str
    CondCheck: str
    ContingentCondition: str
    ConditionPrice: float
    PriceTicks: int
    VolumeMultiple: int
    RelativeFrontID: int
    RelativeSessionID: int
    RelativeParam: str
    AppendContingentCondition: str
    AppendConditionPrice: float
    AppendRelativeFrontID: int
    AppendRelativeSessionID: int
    AppendRelativeParam: str
    HDSerial: str
    
    
class CTORATstpConditionOrderField():
    
    
    ExchangeID: str
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    Direction: str
    OrderPriceType: str
    OrderVolumeType: str
    TimeCondition: str
    VolumeCondition: str
    LimitPrice: float
    VolumeTotalOriginal: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    CondOrderRef: str
    AccountID: str
    UserID: str
    RequestID: int
    IPAddress: str
    MacAddress: str
    CondOrderID: int
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: str
    CondCheck: str
    ContingentCondition: str
    ConditionPrice: float
    PriceTicks: int
    VolumeMultiple: int
    RelativeFrontID: int
    RelativeSessionID: int
    RelativeParam: str
    AppendContingentCondition: str
    AppendConditionPrice: float
    AppendRelativeFrontID: int
    AppendRelativeSessionID: int
    AppendRelativeParam: str
    TradingDay: str
    CondOrderStatus: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    CancelUser: str
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    DepartmentID: str
    ProperCtrlBusinessType: str
    ProperCtrlPassFlag: str
    ActiveDate: str
    ActiveTime: str
    
    
class CTORATstpInputCondOrderActionField():
    
    
    RequestID: int
    ExchangeID: str
    CondOrderActionRef: str
    CondOrderRef: str
    FrontID: int
    SessionID: int
    CondOrderID: int
    ActionFlag: str
    InvestorID: str
    SecurityID: str
    UserID: str
    IPAddress: str
    MacAddress: str
    CancelCondOrderID: int
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: str
    HDSerial: str
    
    
class CTORATstpReqInquiryJZFundField():
    
    
    AccountID: str
    CurrencyID: str
    DepartmentID: str
    
    
class CTORATstpRspInquiryJZFundField():
    
    
    AccountID: str
    CurrencyID: str
    UsefulMoney: float
    FetchLimit: float
    DepartmentID: str
    
    
class CTORATstpInputTransferFundField():
    
    
    AccountID: str
    CurrencyID: str
    ApplySerial: str
    TransferDirection: str
    Amount: float
    DepartmentID: str
    BankID: str
    AccountPassword: str
    BankPassword: str
    
    
class CTORATstpInputTransferPositionField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: str
    ShareholderID: str
    SecurityID: str
    ApplySerial: str
    TransferDirection: str
    Volume: int
    TransferPositionType: str
    MarketID: str
    
    
class CTORATstpTransferFundField():
    
    
    FundSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    AccountID: str
    CurrencyID: str
    TransferDirection: str
    Amount: float
    TransferStatus: str
    OperatorID: str
    OperateDate: str
    OperateTime: str
    DepartmentID: str
    BankAccountID: str
    BankID: str
    
    
class CTORATstpTransferPositionField():
    
    
    PositionSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: str
    ShareholderID: str
    MarketID: str
    SecurityID: str
    TradingDay: str
    TransferDirection: str
    TransferPositionType: str
    HistoryVolume: int
    TodayBSVolume: int
    TodayPRVolume: int
    TransferStatus: str
    OperatorID: str
    OperateDate: str
    OperateTime: str
    
    
class CTORATstpSpecificSecurityField():
    
    
    ExchangeID: str
    SecurityID: str
    
    
class CTORATstpInputTransferCollateralField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: str
    ShareholderID: str
    SecurityID: str
    ApplySerial: str
    CollateralDirection: str
    Volume: int
    MarketID: str
    Operway: str
    
    
class CTORATstpReqInquiryBankAccountFundField():
    
    
    DepartmentID: str
    AccountID: str
    CurrencyID: str
    BankID: str
    BankPassword: str
    
    
class CTORATstpRspInquiryBankAccountFundField():
    
    
    DepartmentID: str
    AccountID: str
    CurrencyID: str
    BankID: str
    BankAccountID: str
    Balance: float
    
    
class CTORATstpLev2MarketDataField():
    
    
    SecurityID: str
    ExchangeID: str
    DataTimeStamp: int
    PreClosePrice: float
    OpenPrice: float
    NumTrades: int
    TotalVolumeTrade: int
    TotalValueTrade: float
    TotalBidVolume: int
    AvgBidPrice: float
    TotalAskVolume: int
    AvgAskPrice: float
    HighestPrice: float
    LowestPrice: float
    LastPrice: float
    BidPrice1: float
    BidVolume1: int
    AskPrice1: float
    AskVolume1: int
    AskPrice2: float
    AskVolume2: int
    AskPrice3: float
    AskVolume3: int
    BidPrice2: float
    BidVolume2: int
    BidPrice3: float
    BidVolume3: int
    AskPrice4: float
    AskVolume4: int
    AskPrice5: float
    AskVolume5: int
    BidPrice4: float
    BidVolume4: int
    BidPrice5: float
    BidVolume5: int
    AskPrice6: float
    AskVolume6: int
    AskPrice7: float
    AskVolume7: int
    BidPrice6: float
    BidVolume6: int
    BidPrice7: float
    BidVolume7: int
    AskPrice8: float
    AskVolume8: int
    AskPrice9: float
    AskVolume9: int
    BidPrice8: float
    BidVolume8: int
    BidPrice9: float
    BidVolume9: int
    BidPrice10: float
    BidVolume10: int
    AskPrice10: float
    AskVolume10: int
    Info1: int
    Info2: int
    Info3: int
    UpperLimitPrice: float
    LowerLimitPrice: float
    ClosePrice: float
    MDSecurityStat: str
    
    
class CTORATstpLev2IndexField():
    
    
    ExchangeID: str
    SecurityID: str
    DataTimeStamp: int
    PreCloseIndex: float
    OpenIndex: float
    HighIndex: float
    LowIndex: float
    LastIndex: float
    Turnover: float
    TotalVolumeTraded: int
    Info1: int
    Info2: int
    Info3: int
    
    
class CTORATstpLev2TransactionField():
    
    
    ExchangeID: str
    SecurityID: str
    TradeTime: int
    TradePrice: float
    TradeVolume: int
    ExecType: str
    MainSeq: int
    SubSeq: int
    BuyNo: int
    SellNo: int
    Info1: int
    Info2: int
    Info3: int
    
    
class CTORATstpLev2OrderDetailField():
    
    
    ExchangeID: str
    SecurityID: str
    OrderTime: int
    Price: float
    Volume: int
    Side: str
    OrderType: str
    MainSeq: int
    SubSeq: int
    Info1: int
    Info2: int
    Info3: int
    
    
class CTORATstpUploadTradeDataField():
    
    
    ExchangeID: str
    TradingDay: str
    bForce: int
    
    
class CTORATstpInputDesignationRegistrationField():
    
    
    InvestorID: str
    UserID: str
    DesignationType: str
    ShareholderID: str
    BusinessUnitID: str
    AccountID: str
    OrderSysID: str
    IPAddress: str
    MacAddress: str
    TerminalInfo: str
    HDSerial: str
    
    
class CTORATstpInputCustodyTransferField():
    
    
    InvestorID: str
    UserID: str
    CustodyTransferType: str
    ShareholderID: str
    BusinessUnitID: str
    AccountID: str
    OrderSysID: str
    TransfereePbuID: str
    SecurityID: str
    OrignalOrderLocalID: str
    OrderLocalID: str
    VolumeTotalOriginal: int
    IPAddress: str
    MacAddress: str
    TerminalInfo: str
    HDSerial: str
    
    
class CTORATstpInquiryTradeConcentrationField():
    
    
    ExchangeID: str
    MarketID: str
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    AccountID: str
    ShareholderID: str
    ConcentrationRatio1: float
    ConcentrationRatio2: float
    
    
class CTORATstpInquiryFileOrderField():
    
    
    ExchangeID: str
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderSerialBeg: int
    OrderSerialEnd: int
    CommitStatus: str
    
    
class CTORATstpFileOrderField():
    
    
    RequestID: int
    ExchangeID: str
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderRef: str
    FileOrderType: str
    Direction: str
    LimitPrice: float
    VolumeTotalOriginal: int
    Operway: str
    OrderActionRef: str
    OrderSysID: str
    CondCheck: str
    OrderSerial: int
    CommitStatus: str
    StatusMsg: str
    TimeStamp: int
    
    
class CTORATstpQryRspInfoField():
    
    
    EndFlag: str
    ErrorID: int
    ErrorMsg: str
    
    
class CTORATstpReviewFileOrderField():
    
    
    ExchangeID: str
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderSerialBeg: int
    OrderSerialEnd: int
    
    
class CTORATstpCommitInfoField():
    
    
    OrderSerial: int
    CommitStatus: str
    StatusMsg: str
    
    
class CTORATstpReqInsTradingNoticeField():
    
    
    NoticeSerial: str
    InsertDate: str
    InsertTime: str
    InvestorID: str
    BusinessUnitID: str
    Content: str
    OperatorID: str
    
    
class CTORATstpTradingNoticeField():
    
    
    NoticeSerial: str
    InsertDate: str
    InsertTime: str
    InvestorID: str
    BusinessUnitID: str
    Content: str
    OperatorID: str
    
    
class CTORATstpLoadFileOrderField():
    
    
    InvestorID: str
    bReview: int
    
    
class CTORATstpFileOrderInfoField():
    
    
    RequestID: int
    ExchangeID: str
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderRef: str
    FileOrderType: str
    Direction: str
    LimitPrice: float
    VolumeTotalOriginal: int
    Operway: str
    OrderActionRef: str
    OrderSysID: str
    CondCheck: str
    OrderSerial: int
    CommitStatus: str
    StatusMsg: str
    
    
class CTORATstpReqInquiryMaxOrderVolumeField():
    
    
    ExchangeID: str
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    AccountID: str
    ShareholderID: str
    Direction: str
    OrderPriceType: str
    CombOffsetFlag: str
    CombHedgeFlag: str
    TimeCondition: str
    VolumeCondition: str
    LimitPrice: float
    TransfereePbuID: str
    MaxVolume: int
    
    
class CTORATstpRspInquiryMaxOrderVolumeField():
    
    
    ExchangeID: str
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    AccountID: str
    ShareholderID: str
    Direction: str
    OrderPriceType: str
    CombOffsetFlag: str
    CombHedgeFlag: str
    TimeCondition: str
    VolumeCondition: str
    LimitPrice: float
    TransfereePbuID: str
    MaxVolume: int
    
    
class CTORATstpPeripheryPositionTransferDetailField():
    
    
    PositionSerial: int
    ApplySerial: int
    FrontID: int
    SessionID: int
    TransferDirection: str
    ExchangeID: str
    MarketID: str
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    TodayBSPos: int
    TodayPRPos: int
    HistoryPos: int
    TradingDay: str
    TransferReason: str
    TransferStatus: str
    OperateDate: str
    OperateTime: str
    RepealDate: str
    RepealTime: str
    RepealReason: str
    StatusMsg: str
    
    
class CTORATstpQryHistoryOrderField():
    
    
    ExchangeID: str
    InvestorID: str
    BegDate: str
    EndDate: str
    SecurityID: str
    PageCount: int
    PageLocate: int
    
    
class CTORATstpQryHistoryRspInfoField():
    
    
    ErrorID: int
    ErrorMsg: str
    bPageEnd: int
    
    
class CTORATstpHistoryOrderField():
    
    
    InvestorID: str
    SecurityID: str
    OrderRef: str
    UserID: str
    OrderPriceType: str
    Direction: str
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: str
    VolumeCondition: str
    MinVolume: int
    ForceCloseReason: str
    RequestID: int
    OrderLocalID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    ExchangeInstID: str
    TraderID: str
    OrderSubmitStatus: str
    TradingDay: str
    OrderSysID: str
    OrderStatus: str
    OrderType: str
    VolumeTraded: int
    VolumeTotal: int
    InsertDate: str
    InsertTime: str
    CancelTime: str
    ActiveTraderID: str
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    UserForceClose: int
    ActiveUserID: str
    BusinessUnitID: str
    AccountID: str
    IPAddress: str
    MacAddress: str
    CreditPositionType: str
    BInfo: str
    SInfo: str
    IInfo: int
    TransfereePbuID: str
    Operway: str
    DepartmentID: str
    ProperCtrlBusinessType: str
    ProperCtrlPassFlag: str
    CondCheck: str
    IsCacheOrder: int
    Turnover: float
    RtnFloatInfo: float
    RtnIntInfo: int
    PageLocate: int
    
    
class CTORATstpQryHistoryTradeField():
    
    
    ExchangeID: str
    InvestorID: str
    BegDate: str
    EndDate: str
    SecurityID: str
    PageCount: int
    PageLocate: int
    
    
class CTORATstpHistoryTradeField():
    
    
    InvestorID: str
    SecurityID: str
    UserID: str
    ExchangeID: str
    TradeID: str
    Direction: str
    OrderSysID: str
    MarketID: str
    ShareholderID: str
    ExchangeInstID: str
    OffsetFlag: str
    HedgeFlag: str
    Price: float
    Volume: int
    TradeDate: str
    TradeTime: str
    TraderID: str
    OrderLocalID: str
    TradingDay: str
    BusinessUnitID: str
    AccountID: str
    OrderRef: str
    DepartmentID: str
    PageLocate: int
    
    
class CTORATstpQryExchangeField():
    
    
    ExchangeID: str
    
    
class CTORATstpExchangeField():
    
    
    ExchangeID: str
    ExchangeName: str
    TradingDay: str
    
    
class CTORATstpQryPBUField():
    
    
    PbuID: str
    ExchangeID: str
    MarketID: str
    
    
class CTORATstpPBUField():
    
    
    PbuID: str
    PbuName: str
    ExchangeID: str
    MarketID: str
    
    
class CTORATstpQryMarketDataField():
    
    
    SecurityID: str
    ExchangeID: str
    
    
class CTORATstpMarketDataField():
    
    
    TradingDay: str
    SecurityID: str
    ExchangeID: str
    ExchangeInstID: str
    LastPrice: float
    PreClosePrice: float
    OpenPrice: float
    HighestPrice: float
    LowestPrice: float
    Volume: int
    Turnover: float
    OpenInterest: float
    UpperLimitPrice: float
    LowerLimitPrice: float
    UpdateTime: str
    UpdateMillisec: int
    BidPrice1: float
    BidVolume1: int
    AskPrice1: float
    AskVolume1: int
    BidPrice2: float
    BidVolume2: int
    AskPrice2: float
    AskVolume2: int
    BidPrice3: float
    BidVolume3: int
    AskPrice3: float
    AskVolume3: int
    BidPrice4: float
    BidVolume4: int
    AskPrice4: float
    AskVolume4: int
    BidPrice5: float
    BidVolume5: int
    AskPrice5: float
    AskVolume5: int
    SecurityName: str
    TradingCount: int
    PERatio1: float
    PERatio2: float
    PriceUpDown1: float
    PriceUpDown2: float
    ClosePrice: float
    MDSecurityStat: str
    HWFlag: int
    
    
class CTORATstpQrySecurityField():
    
    
    SecurityID: str
    ExchangeID: str
    ExchangeInstID: str
    ProductID: str
    
    
class CTORATstpSecurityField():
    
    
    SecurityID: str
    ExchangeID: str
    SecurityName: str
    ExchangeInstID: str
    MarketID: str
    ProductID: str
    SecurityType: str
    OrderUnit: str
    BuyTradingUnit: int
    SellTradingUnit: int
    MaxMarketOrderBuyVolume: int
    MinMarketOrderBuyVolume: int
    MaxLimitOrderBuyVolume: int
    MinLimitOrderBuyVolume: int
    MaxMarketOrderSellVolume: int
    MinMarketOrderSellVolume: int
    MaxLimitOrderSellVolume: int
    MinLimitOrderSellVolume: int
    VolumeMultiple: int
    PriceTick: float
    OpenDate: str
    PositionType: str
    ParValue: float
    SecurityStatus: int
    BondInterest: float
    ConversionRate: float
    IsCollateral: int
    
    
class CTORATstpQryETFFileField():
    
    
    ExchangeID: str
    ETFSecurityID: str
    ETFCreRedSecurityID: str
    
    
class CTORATstpETFFileField():
    
    
    TradingDay: str
    ExchangeID: str
    ETFSecurityID: str
    ETFCreRedSecurityID: str
    CreationRedemptionUnit: int
    Maxcashratio: float
    CreationStatus: int
    RedemptionStatus: int
    EstimateCashComponent: float
    CashComponent: float
    NAV: float
    NAVperCU: float
    DividendPerCU: float
    
    
class CTORATstpQryETFBasketField():
    
    
    ExchangeID: str
    ETFSecurityID: str
    SecurityID: str
    
    
class CTORATstpETFBasketField():
    
    
    TradingDay: str
    ExchangeID: str
    ETFSecurityID: str
    SecurityID: str
    SecurityName: str
    Volume: int
    ETFCurrenceReplaceStatus: str
    Premium: float
    CreationReplaceAmount: float
    RedemptionReplaceAmount: float
    Market: str
    
    
class CTORATstpQryDepartmentInfoField():
    
    
    DepartmentID: str
    
    
class CTORATstpDepartmentInfoField():
    
    
    DepartmentID: str
    DepartmentName: str
    
    
class CTORATstpQryIPOInfoField():
    
    
    ExchangeID: str
    SecurityID: str
    
    
class CTORATstpIPOInfoField():
    
    
    ExchangeID: str
    SecurityID: str
    MarketID: str
    ProductID: str
    SecurityType: str
    OnlineLimit: int
    Price: float
    CurrencyID: str
    SecurityName: str
    UnderlyingSecurityID: str
    UnderlyingSecurityName: str
    OnlineMinVol: int
    OnlineVolUnit: int
    
    
class CTORATstpQryBrokerUserFunctionField():
    
    
    UserID: str
    
    
class CTORATstpBrokerUserFunctionField():
    
    
    UserID: str
    FunctionID: str
    
    
class CTORATstpQryBUProxyField():
    
    
    InvestorID: str
    UserID: str
    BusinessUnitID: str
    
    
class CTORATstpBUProxyField():
    
    
    InvestorID: str
    UserID: str
    BusinessUnitID: str
    
    
class CTORATstpQryUserField():
    
    
    UserID: str
    UserType: str
    
    
class CTORATstpUserField():
    
    
    UserID: str
    UserName: str
    UserType: str
    IsActive: int
    LoginLimit: int
    
    
class CTORATstpQryInvestorField():
    
    
    InvestorID: str
    
    
class CTORATstpInvestorField():
    
    
    InvestorID: str
    InvestorName: str
    IdCardType: str
    IdCardNo: str
    Telephone: str
    Address: str
    OpenDate: str
    Mobile: str
    Operways: str
    CRiskLevel: str
    ProfInvestorType: str
    
    
class CTORATstpQryShareholderAccountField():
    
    
    InvestorID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    TradingCodeClass: str
    
    
class CTORATstpShareholderAccountField():
    
    
    InvestorID: str
    ExchangeID: str
    ShareholderID: str
    ClientIDType: str
    MarketID: str
    
    
class CTORATstpQryBusinessUnitField():
    
    
    InvestorID: str
    
    
class CTORATstpBusinessUnitField():
    
    
    InvestorID: str
    BusinessUnitID: str
    BusinessUnitName: str
    
    
class CTORATstpQryBusinessUnitAndTradingAcctField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ProductID: str
    AccountID: str
    CurrencyID: str
    
    
class CTORATstpBusinessUnitAndTradingAcctField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    ProductID: str
    AccountID: str
    CurrencyID: str
    UserID: str
    
    
class CTORATstpQryOrderField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    OrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    BusinessUnitID: str
    BInfo: str
    SInfo: str
    IInfo: int
    IsCancel: int
    
    
class CTORATstpQryOrderActionField():
    
    
    InvestorID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    BInfo: str
    SInfo: str
    IInfo: int
    
    
class CTORATstpQryTradeField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    TradeID: str
    TradeTimeStart: str
    TradeTimeEnd: str
    BusinessUnitID: str
    
    
class CTORATstpQryTradingAccountField():
    
    
    InvestorID: str
    CurrencyID: str
    AccountID: str
    AccountType: str
    DepartmentID: str
    
    
class CTORATstpTradingAccountField():
    
    
    AccountID: str
    Available: float
    WithdrawQuota: float
    CurrencyID: str
    Deposit: float
    Withdraw: float
    FrozenMargin: float
    FrozenCash: float
    FrozenCommission: float
    CurrMargin: float
    Commission: float
    AccountType: str
    AccountOwner: str
    DepartmentID: str
    BankID: str
    BankAccountID: str
    
    
class CTORATstpQryPositionField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    BusinessUnitID: str
    
    
class CTORATstpPositionField():
    
    
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    TradingDay: str
    HistoryPos: int
    HistoryPosFrozen: int
    TodayBSPos: int
    TodayBSFrozen: int
    TodayPRPos: int
    TodayPRFrozen: int
    TotalPosCost: float
    TodaySMPos: int
    TodaySMPosFrozen: int
    MarginBuyPos: int
    ShortSellPos: int
    PrePosition: int
    AvailablePosition: int
    CurrentPosition: int
    LastPrice: float
    
    
class CTORATstpQryTradingFeeField():
    
    
    ExchangeID: str
    
    
class CTORATstpTradingFeeField():
    
    
    ExchangeID: str
    ProductID: str
    SecurityType: str
    SecurityID: str
    BizClass: str
    StampTaxRatioByAmt: float
    StampTaxRatioByPar: float
    StampTaxFeePerOrder: float
    StampTaxFeeMin: float
    StampTaxFeeMax: float
    TransferRatioByAmt: float
    TransferRatioByPar: float
    TransferFeePerOrder: float
    TransferFeeMin: float
    TransferFeeMax: float
    HandlingRatioByAmt: float
    HandlingRatioByPar: float
    HandlingFeePerOrder: float
    HandlingFeeMin: float
    HandlingFeeMax: float
    RegulateRatioByAmt: float
    RegulateRatioByPar: float
    RegulateFeePerOrder: float
    RegulateFeeMin: float
    RegulateFeeMax: float
    TransferFeeByVolume: float
    HandlingFeeByVolume: float
    SettlementRatioByAmt: float
    SettlementRatioByPar: float
    SettlementFeePerOrder: float
    SettlementFeeByVolume: float
    SettlementFeeMin: float
    SettlementFeeMax: float
    
    
class CTORATstpQryInvestorTradingFeeField():
    
    
    InvestorID: str
    ExchangeID: str
    DepartmentID: str
    
    
class CTORATstpInvestorTradingFeeField():
    
    
    InvestorID: str
    ExchangeID: str
    ProductID: str
    SecurityType: str
    SecurityID: str
    BizClass: str
    BrokerageType: str
    RatioByAmt: float
    RatioByPar: float
    FeePerOrder: float
    FeeMin: float
    FeeMax: float
    FeeByVolume: float
    DepartmentID: str
    
    
class CTORATstpQryIPOQuotaField():
    
    
    InvestorID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    
    
class CTORATstpIPOQuotaField():
    
    
    InvestorID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    MaxVolume: int
    
    
class CTORATstpQryMarketField():
    
    
    ExchangeID: str
    MarketID: str
    
    
class CTORATstpMarketField():
    
    
    MarketID: str
    MarketName: str
    ExchangeID: str
    
    
class CTORATstpQryOrderFundDetailField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    OrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    BusinessUnitID: str
    
    
class CTORATstpOrderFundDetailField():
    
    
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    TradingDay: str
    OrderSysID: str
    BusinessUnitID: str
    AccountID: str
    TotalFrozen: float
    TotalFee: float
    StampTaxFee: float
    HandlingFee: float
    TransferFee: float
    RegulateFee: float
    BrokerageFee: float
    SettlementFee: float
    TotalFeeFrozen: float
    OrderAmount: float
    
    
class CTORATstpQryFundTransferDetailField():
    
    
    AccountID: str
    CurrencyID: str
    TransferDirection: str
    DepartmentID: str
    
    
class CTORATstpFundTransferDetailField():
    
    
    FundSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    AccountID: str
    CurrencyID: str
    TransferDirection: str
    Amount: float
    TransferStatus: str
    OperateSource: str
    OperatorID: str
    OperateDate: str
    OperateTime: str
    StatusMsg: str
    DepartmentID: str
    BankID: str
    BankAccountID: str
    
    
class CTORATstpQryPositionTransferDetailField():
    
    
    ShareholderID: str
    SecurityID: str
    TransferDirection: str
    
    
class CTORATstpPositionTransferDetailField():
    
    
    PositionSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    InvestorID: str
    ExchangeID: str
    ShareholderID: str
    MarketID: str
    SecurityID: str
    TradingDay: str
    TransferDirection: str
    TransferPositionType: str
    TransferStatus: str
    HistoryVolume: int
    TodayBSVolume: int
    TodayPRVolume: int
    OperatorID: str
    OperateDate: str
    OperateTime: str
    BusinessUnitID: str
    StatusMsg: str
    
    
class CTORATstpQryPledgePositionField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    BusinessUnitID: str
    
    
class CTORATstpPledgePositionField():
    
    
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    TradingDay: str
    HisPledgePos: int
    HisPledgePosFrozen: int
    TodayPledgePos: int
    TodayPledgePosFrozen: int
    PreTotalPledgePos: int
    preAvailablePledgePos: int
    
    
class CTORATstpQryPledgeInfoField():
    
    
    ExchangeID: str
    SecurityID: str
    
    
class CTORATstpPledgeInfoField():
    
    
    ExchangeID: str
    MarketID: str
    SecurityID: str
    PledgeOrderID: str
    StandardBondID: str
    AllowPledgeIn: int
    AllowPledgeOut: int
    ConversionRate: float
    PledgeInTradingUnit: int
    PledgeOutTradingUnit: int
    PledgeInVolMax: int
    PledgeInVolMin: int
    PledgeOutVolMax: int
    PledgeOutVolMin: int
    IsTodayToPlegeOut: int
    IsCancelOrder: int
    
    
class CTORATstpQryConversionBondInfoField():
    
    
    ExchangeID: str
    SecurityID: str
    
    
class CTORATstpConversionBondInfoField():
    
    
    ExchangeID: str
    MarketID: str
    SecurityID: str
    ConvertOrderID: str
    ConvertPrice: float
    ConvertVolUnit: int
    ConvertVolMax: int
    ConvertVolMin: int
    BeginDate: str
    EndDate: str
    IsSupportCancel: int
    
    
class CTORATstpQryBondPutbackInfoField():
    
    
    ExchangeID: str
    SecurityID: str
    
    
class CTORATstpBondPutbackInfoField():
    
    
    ExchangeID: str
    MarketID: str
    SecurityID: str
    PutbackOrderID: str
    PutbackPrice: float
    PutbackVolUnit: int
    PutbackVolMax: int
    PutbackVolMin: int
    BeginDate: str
    EndDate: str
    IsSupportCancel: int
    
    
class CTORATstpQryStandardBondPositionField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    BusinessUnitID: str
    
    
class CTORATstpStandardBondPositionField():
    
    
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    TradingDay: str
    AvailablePosition: float
    AvailablePosFrozen: float
    TotalPosition: float
    
    
class CTORATstpQryDesignationRegistrationField():
    
    
    InvestorID: str
    ShareholderID: str
    OrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    BusinessUnitID: str
    
    
class CTORATstpDesignationRegistrationField():
    
    
    InvestorID: str
    UserID: str
    DesignationType: str
    OrderLocalID: str
    ShareholderID: str
    PbuID: str
    OrderSubmitStatus: str
    TradingDay: str
    OrderSysID: str
    OrderStatus: str
    InsertDate: str
    InsertTime: str
    StatusMsg: str
    BusinessUnitID: str
    AccountID: str
    CurrencyID: str
    DepartmentID: str
    
    
class CTORATstpQryCustodyTransferField():
    
    
    InvestorID: str
    ShareholderID: str
    OrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    BusinessUnitID: str
    SecurityID: str
    
    
class CTORATstpCustodyTransferField():
    
    
    InvestorID: str
    UserID: str
    CustodyTransferType: str
    OrderLocalID: str
    ShareholderID: str
    PbuID: str
    OrderSubmitStatus: str
    TradingDay: str
    OrderSysID: str
    OrderStatus: str
    InsertDate: str
    InsertTime: str
    StatusMsg: str
    BusinessUnitID: str
    AccountID: str
    CurrencyID: str
    DepartmentID: str
    TransfereePbuID: str
    SecurityID: str
    OrignalOrderLocalID: str
    VolumeTotalOriginal: int
    CancelTime: str
    ActiveTraderID: str
    ActiveUserID: str
    
    
class CTORATstpQrySpecialMarketDataField():
    
    
    SecurityID: str
    ExchangeID: str
    
    
class CTORATstpSpecialMarketDataField():
    
    
    TradingDay: str
    ExchangeID: str
    SecurityID: str
    SecurityName: str
    MovingAvgPrice: float
    MovingAvgPriceSamplingNum: int
    UpdateTime: str
    UpdateMillisec: int
    
    
class CTORATstpQryPrematurityRepoOrderField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    BusinessUnitID: str
    OrderLocalID: str
    ProductID: str
    SecurityType: str
    Direction: str
    TradeID: str
    
    
class CTORATstpPrematurityRepoOrderField():
    
    
    ExchangeID: str
    MarketID: str
    InvestorID: str
    ShareholderID: str
    BusinessUnitID: str
    TradeDay: str
    ExpireDay: str
    OrderLocalID: str
    SecurityID: str
    SecurityName: str
    ProductID: str
    SecurityType: str
    Direction: str
    VolumeTraded: int
    Price: float
    Turnover: float
    TradeID: str
    RepoTotalMoney: float
    InterestAmount: float
    
    
class CTORATstpQryShareholderParamField():
    
    
    MarketID: str
    ShareholderID: str
    TradingCodeClass: str
    ProductID: str
    SecurityType: str
    SecurityID: str
    ParamType: str
    ExchangeID: str
    
    
class CTORATstpShareholderParamField():
    
    
    ExchangeID: str
    MarketID: str
    ShareholderID: str
    TradingCodeClass: str
    ProductID: str
    SecurityType: str
    SecurityID: str
    ParamType: str
    ParamValue: str
    
    
class CTORATstpQryPeripheryPositionTransferDetailField():
    
    
    InvestorID: str
    ShareholderID: str
    SecurityID: str
    TransferDirection: str
    BusinessUnitID: str
    
    
class CTORATstpQryInvestorCondOrderLimitParamField():
    
    
    InvestorID: str
    
    
class CTORATstpInvestorCondOrderLimitParamField():
    
    
    InvestorID: str
    MaxCondOrderLimitCnt: int
    CurrCondOrderCnt: int
    
    
class CTORATstpQryCondOrderField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: str
    ShareholderID: str
    CondOrderID: int
    InsertTimeStart: str
    InsertTimeEnd: str
    BusinessUnitID: str
    BInfo: str
    SInfo: str
    IInfo: int
    
    
class CTORATstpCondOrderField():
    
    
    ExchangeID: str
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    Direction: str
    OrderPriceType: str
    OrderVolumeType: str
    TimeCondition: str
    VolumeCondition: str
    LimitPrice: float
    VolumeTotalOriginal: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    CondOrderRef: str
    AccountID: str
    UserID: str
    RequestID: int
    IPAddress: str
    MacAddress: str
    CondOrderID: int
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: str
    CondCheck: str
    ContingentCondition: str
    ConditionPrice: float
    PriceTicks: int
    VolumeMultiple: int
    RelativeFrontID: int
    RelativeSessionID: int
    RelativeParam: str
    AppendContingentCondition: str
    AppendConditionPrice: float
    AppendRelativeFrontID: int
    AppendRelativeSessionID: int
    AppendRelativeParam: str
    TradingDay: str
    CondOrderStatus: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    CancelUser: str
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    DepartmentID: str
    ProperCtrlBusinessType: str
    ProperCtrlPassFlag: str
    ActiveDate: str
    ActiveTime: str
    
    
class CTORATstpQryCondOrderActionField():
    
    
    InvestorID: str
    ExchangeID: str
    ShareholderID: str
    BInfo: str
    SInfo: str
    IInfo: int
    
    
class CTORATstpCondOrderActionField():
    
    
    ExchangeID: str
    RequestID: int
    CondOrderActionRef: str
    CondOrderRef: str
    FrontID: int
    SessionID: int
    CondOrderID: int
    ActionFlag: str
    InvestorID: str
    SecurityID: str
    UserID: str
    CancelCondOrderID: int
    IPAddress: str
    MacAddress: str
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: str
    BusinessUnitID: str
    ShareholderID: str
    ActionDate: str
    ActionTime: str
    
    
class CTORATstpQryBrokerUserRoleField():
    
    
    RoleID: int
    
    
class CTORATstpBrokerUserRoleField():
    
    
    RoleID: int
    RoleDescription: str
    Functions: str
    
    
class CTORATstpQryBrokerUserRoleAssignmentField():
    
    
    UserID: str
    
    
class CTORATstpBrokerUserRoleAssignmentField():
    
    
    UserID: str
    RoleID: int
    RoleDescription: str
    
    
class CTORATstpQryTradingNoticeField():
    
    
    InvestorID: str
    InsertDateStart: str
    InsertDateEnd: str
    InsertTimeStart: str
    InsertTimeEnd: str
    
    
class CTORATstpQryIPONumberResultField():
    
    
    SecurityID: str
    ExchangeID: str
    ShareholderID: str
    
    
class CTORATstpIPONumberResultField():
    
    
    ExchangeID: str
    SecurityID: str
    Day: str
    SecurityName: str
    ShareholderID: str
    SecurityType: str
    BeginNumberID: str
    Volume: int
    
    
class CTORATstpQryIPOMatchNumberResultField():
    
    
    SecurityID: str
    ExchangeID: str
    ShareholderID: str
    MatchNumberID: str
    
    
class CTORATstpIPOMatchNumberResultField():
    
    
    ExchangeID: str
    SecurityID: str
    Day: str
    SecurityName: str
    ShareholderID: str
    SecurityType: str
    MatchNumberID: str
    Volume: int
    Price: float
    Amout: float
    
    
class CTORATstpMdSpi():
    
    
    
    
    def OnFrontConnected(self, )->None:
        ...
    def OnFrontDisconnected(self, nReason: int)->None:
        ...
    def OnRspError(self, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUserLogin(self, pRspUserLogin: CTORATstpRspUserLoginField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUserLogout(self, pUserLogout: CTORATstpUserLogoutField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspSubMarketData(self, pSpecificSecurity: CTORATstpSpecificSecurityField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUnSubMarketData(self, pSpecificSecurity: CTORATstpSpecificSecurityField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspSubSpecialMarketData(self, pSpecificSecurity: CTORATstpSpecificSecurityField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUnSubSpecialMarketData(self, pSpecificSecurity: CTORATstpSpecificSecurityField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspSubFundsFlowMarketData(self, pSpecificSecurity: CTORATstpSpecificSecurityField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUnSubFundsFlowMarketData(self, pSpecificSecurity: CTORATstpSpecificSecurityField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRtnDepthMarketData(self, pDepthMarketData: CTORATstpMarketDataField)->None:
        ...
    def OnRtnSpecialMarketData(self, pSpecialMarketData: CTORATstpSpecialMarketDataField)->None:
        ...
    def OnRtnEffectPriceMarketData(self, pEffectPriceMarketData: CTORATstpEffectPriceMarketDataField)->None:
        ...
    def OnRtnEffectVolumeMarketData(self, pEffectVolumeMarketData: CTORATstpEffectVolumeMarketDataField)->None:
        ...
    def OnRtnFundsFlowMarketData(self, pFundsFlowMarketData: CTORATstpFundsFlowMarketDataField)->None:
        ...
class CTORATstpMdApi():
    
    
    
    
    @staticmethod
    def CreateTstpMdApi()->CTORATstpMdApi:
        ...
    @staticmethod
    def GetApiVersion()->str:
        ...
    def Release(self, )->None:
        ...
    def Init(self, )->None:
        ...
    def Join(self, )->int:
        ...
    def RegisterFront(self, pszFrontAddress: str)->None:
        ...
    def RegisterNameServer(self, pszNsAddress: str)->None:
        ...
    def RegisterDeriveServer(self, pszDeriveAddress: str)->None:
        ...
    def RegisterSpi(self, pSpi: CTORATstpMdSpi)->None:
        ...
    def SubscribeMarketData(self, ppSecurityID: List[str], ExchageID: str)->int:
        ...
    def UnSubscribeMarketData(self, ppSecurityID: List[str], ExchageID: str)->int:
        ...
    def SubscribeSpecialMarketData(self, ppSecurityID: List[str], ExchageID: str)->int:
        ...
    def UnSubscribeSpecialMarketData(self, ppSecurityID: List[str], ExchageID: str)->int:
        ...
    def SubscribeFundsFlowMarketData(self, ppInstrumentID: List[str], ExchageID: str)->int:
        ...
    def UnSubscribeFundsFlowMarketData(self, ppInstrumentID: List[str], ExchageID: str)->int:
        ...
    def ReqUserLogin(self, pReqUserLoginField: CTORATstpReqUserLoginField, nRequestID: int)->int:
        ...
    def ReqUserLogout(self, pUserLogout: CTORATstpUserLogoutField, nRequestID: int)->int:
        ...
class CTORATstpTraderSpi():
    
    
    
    
    def OnFrontConnected(self, )->None:
        ...
    def OnFrontDisconnected(self, nReason: int)->None:
        ...
    def OnRspError(self, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUserLogin(self, pRspUserLoginField: CTORATstpRspUserLoginField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUserLogout(self, pUserLogoutField: CTORATstpUserLogoutField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspUserPasswordUpdate(self, pUserPasswordUpdateField: CTORATstpUserPasswordUpdateField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspInputDeviceSerial(self, pRspInputDeviceSerialField: CTORATstpRspInputDeviceSerialField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspOrderInsert(self, pInputOrderField: CTORATstpInputOrderField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRtnOrder(self, pOrder: CTORATstpOrderField)->None:
        ...
    def OnErrRtnOrderInsert(self, pInputOrder: CTORATstpInputOrderField, pRspInfo: CTORATstpRspInfoField)->None:
        ...
    def OnRspOrderAction(self, pInputOrderActionField: CTORATstpInputOrderActionField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnErrRtnOrderAction(self, pOrderAction: CTORATstpOrderActionField, pRspInfo: CTORATstpRspInfoField)->None:
        ...
    def OnRtnTrade(self, pTrade: CTORATstpTradeField)->None:
        ...
    def OnRtnMarketStatus(self, pMarketStatus: CTORATstpMarketStatusField)->None:
        ...
    def OnRspCondOrderInsert(self, pInputCondOrderField: CTORATstpInputCondOrderField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRtnCondOrder(self, pConditionOrder: CTORATstpConditionOrderField)->None:
        ...
    def OnErrRtnCondOrderInsert(self, pInputCondOrder: CTORATstpInputCondOrderField, pRspInfo: CTORATstpRspInfoField)->None:
        ...
    def OnRspCondOrderAction(self, pInputCondOrderActionField: CTORATstpInputCondOrderActionField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnErrRtnCondOrderAction(self, pInputCondOrderAction: CTORATstpInputCondOrderActionField, pRspInfo: CTORATstpRspInfoField)->None:
        ...
    def OnRspInquiryJZFund(self, pRspInquiryJZFundField: CTORATstpRspInquiryJZFundField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspTransferFund(self, pInputTransferFundField: CTORATstpInputTransferFundField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRtnTransferFund(self, pTransferFund: CTORATstpTransferFundField)->None:
        ...
    def OnErrRtnTransferFund(self, pInputTransferFund: CTORATstpInputTransferFundField, pRspInfo: CTORATstpRspInfoField)->None:
        ...
    def OnRtnTransferPosition(self, pTransferPosition: CTORATstpTransferPositionField)->None:
        ...
    def OnErrRtnTransferPosition(self, pInputTransferPosition: CTORATstpInputTransferPositionField, pRspInfo: CTORATstpRspInfoField)->None:
        ...
    def OnRspTransferCollateral(self, pInputTransferCollateralField: CTORATstpInputTransferCollateralField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspInquiryBankAccountFund(self, pRspInquiryBankAccountFundField: CTORATstpRspInquiryBankAccountFundField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspInquiryTradeConcentration(self, pInquiryTradeConcentrationField: CTORATstpInquiryTradeConcentrationField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRtnTradingNotice(self, pTradingNotice: CTORATstpTradingNoticeField)->None:
        ...
    def OnRspInquiryMaxOrderVolume(self, pRspInquiryMaxOrderVolumeField: CTORATstpRspInquiryMaxOrderVolumeField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRtnPeripheryTransferPosition(self, pPeripheryPositionTransferDetail: CTORATstpPeripheryPositionTransferDetailField)->None:
        ...
    def OnRspInquiryHistoryOrder(self, pHistoryOrderField: CTORATstpHistoryOrderField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspInquiryHistoryTrade(self, pHistoryTradeField: CTORATstpHistoryTradeField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryExchange(self, pExchange: CTORATstpExchangeField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryMarketData(self, pMarketData: CTORATstpMarketDataField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQrySecurity(self, pSecurity: CTORATstpSecurityField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryETFFile(self, pETFFile: CTORATstpETFFileField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryETFBasket(self, pETFBasket: CTORATstpETFBasketField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryIPOInfo(self, pIPOInfo: CTORATstpIPOInfoField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryBUProxy(self, pBUProxy: CTORATstpBUProxyField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryUser(self, pUser: CTORATstpUserField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryInvestor(self, pInvestor: CTORATstpInvestorField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryShareholderAccount(self, pShareholderAccount: CTORATstpShareholderAccountField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryOrder(self, pOrder: CTORATstpOrderField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryOrderAction(self, pOrderAction: CTORATstpOrderActionField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryTrade(self, pTrade: CTORATstpTradeField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryTradingAccount(self, pTradingAccount: CTORATstpTradingAccountField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryPosition(self, pPosition: CTORATstpPositionField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryTradingFee(self, pTradingFee: CTORATstpTradingFeeField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryInvestorTradingFee(self, pInvestorTradingFee: CTORATstpInvestorTradingFeeField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryIPOQuota(self, pIPOQuota: CTORATstpIPOQuotaField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryMarket(self, pMarket: CTORATstpMarketField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryOrderFundDetail(self, pOrderFundDetail: CTORATstpOrderFundDetailField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryFundTransferDetail(self, pFundTransferDetail: CTORATstpFundTransferDetailField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryPositionTransferDetail(self, pPositionTransferDetail: CTORATstpPositionTransferDetailField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryPledgePosition(self, pPledgePosition: CTORATstpPledgePositionField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryPledgeInfo(self, pPledgeInfo: CTORATstpPledgeInfoField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryConversionBondInfo(self, pConversionBondInfo: CTORATstpConversionBondInfoField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryBondPutbackInfo(self, pBondPutbackInfo: CTORATstpBondPutbackInfoField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryStandardBondPosition(self, pStandardBondPosition: CTORATstpStandardBondPositionField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQrySpecialMarketData(self, pSpecialMarketData: CTORATstpSpecialMarketDataField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryPrematurityRepoOrder(self, pPrematurityRepoOrder: CTORATstpPrematurityRepoOrderField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryShareholderParam(self, pShareholderParam: CTORATstpShareholderParamField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryPeripheryPositionTransferDetail(self, pPeripheryPositionTransferDetail: CTORATstpPeripheryPositionTransferDetailField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryInvestorCondOrderLimitParam(self, pInvestorCondOrderLimitParam: CTORATstpInvestorCondOrderLimitParamField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryCondOrder(self, pCondOrder: CTORATstpCondOrderField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryCondOrderAction(self, pCondOrderAction: CTORATstpCondOrderActionField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryTradingNotice(self, pTradingNotice: CTORATstpTradingNoticeField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryIPONumberResult(self, pIPONumberResult: CTORATstpIPONumberResultField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
    def OnRspQryIPOMatchNumberResult(self, pIPOMatchNumberResult: CTORATstpIPOMatchNumberResultField, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool)->None:
        ...
class CTORATstpTraderApi():
    
    
    
    
    @staticmethod
    def CreateTstpTraderApi(pszFlowPath: str, bEncrypt: bool)->CTORATstpTraderApi:
        ...
    @staticmethod
    def GetApiVersion()->str:
        ...
    def Release(self, )->None:
        ...
    def Init(self, )->None:
        ...
    def Join(self, )->int:
        ...
    def RegisterFront(self, pszFrontAddress: str)->None:
        ...
    def RegisterNameServer(self, pszNsAddress: str)->None:
        ...
    def RegisterDeriveServer(self, pszDeriveAddress: str)->None:
        ...
    def RegisterSpi(self, pSpi: CTORATstpTraderSpi)->None:
        ...
    def SubscribePrivateTopic(self, nResumeType: TORA_TE_RESUME_TYPE)->None:
        ...
    def SubscribePublicTopic(self, nResumeType: TORA_TE_RESUME_TYPE)->None:
        ...
    def ReqUserLogin(self, pReqUserLoginField: CTORATstpReqUserLoginField, nRequestID: int)->int:
        ...
    def ReqUserLogout(self, pUserLogoutField: CTORATstpUserLogoutField, nRequestID: int)->int:
        ...
    def ReqUserPasswordUpdate(self, pUserPasswordUpdateField: CTORATstpUserPasswordUpdateField, nRequestID: int)->int:
        ...
    def ReqInputDeviceSerial(self, pReqInputDeviceSerialField: CTORATstpReqInputDeviceSerialField, nRequestID: int)->int:
        ...
    def ReqOrderInsert(self, pInputOrderField: CTORATstpInputOrderField, nRequestID: int)->int:
        ...
    def ReqOrderAction(self, pInputOrderActionField: CTORATstpInputOrderActionField, nRequestID: int)->int:
        ...
    def ReqCondOrderInsert(self, pInputCondOrderField: CTORATstpInputCondOrderField, nRequestID: int)->int:
        ...
    def ReqCondOrderAction(self, pInputCondOrderActionField: CTORATstpInputCondOrderActionField, nRequestID: int)->int:
        ...
    def ReqInquiryJZFund(self, pReqInquiryJZFundField: CTORATstpReqInquiryJZFundField, nRequestID: int)->int:
        ...
    def ReqTransferFund(self, pInputTransferFundField: CTORATstpInputTransferFundField, nRequestID: int)->int:
        ...
    def ReqTransferCollateral(self, pInputTransferCollateralField: CTORATstpInputTransferCollateralField, nRequestID: int)->int:
        ...
    def ReqInquiryBankAccountFund(self, pReqInquiryBankAccountFundField: CTORATstpReqInquiryBankAccountFundField, nRequestID: int)->int:
        ...
    def ReqInquiryTradeConcentration(self, pInquiryTradeConcentrationField: CTORATstpInquiryTradeConcentrationField, nRequestID: int)->int:
        ...
    def ReqInquiryMaxOrderVolume(self, pReqInquiryMaxOrderVolumeField: CTORATstpReqInquiryMaxOrderVolumeField, nRequestID: int)->int:
        ...
    def ReqInquiryHistoryOrder(self, pQryHistoryOrderField: CTORATstpQryHistoryOrderField, nRequestID: int)->int:
        ...
    def ReqInquiryHistoryTrade(self, pQryHistoryTradeField: CTORATstpQryHistoryTradeField, nRequestID: int)->int:
        ...
    def ReqQryExchange(self, pQryExchangeField: CTORATstpQryExchangeField, nRequestID: int)->int:
        ...
    def ReqQryMarketData(self, pQryMarketDataField: CTORATstpQryMarketDataField, nRequestID: int)->int:
        ...
    def ReqQrySecurity(self, pQrySecurityField: CTORATstpQrySecurityField, nRequestID: int)->int:
        ...
    def ReqQryETFFile(self, pQryETFFileField: CTORATstpQryETFFileField, nRequestID: int)->int:
        ...
    def ReqQryETFBasket(self, pQryETFBasketField: CTORATstpQryETFBasketField, nRequestID: int)->int:
        ...
    def ReqQryIPOInfo(self, pQryIPOInfoField: CTORATstpQryIPOInfoField, nRequestID: int)->int:
        ...
    def ReqQryBUProxy(self, pQryBUProxyField: CTORATstpQryBUProxyField, nRequestID: int)->int:
        ...
    def ReqQryUser(self, pQryUserField: CTORATstpQryUserField, nRequestID: int)->int:
        ...
    def ReqQryInvestor(self, pQryInvestorField: CTORATstpQryInvestorField, nRequestID: int)->int:
        ...
    def ReqQryShareholderAccount(self, pQryShareholderAccountField: CTORATstpQryShareholderAccountField, nRequestID: int)->int:
        ...
    def ReqQryOrder(self, pQryOrderField: CTORATstpQryOrderField, nRequestID: int)->int:
        ...
    def ReqQryOrderAction(self, pQryOrderActionField: CTORATstpQryOrderActionField, nRequestID: int)->int:
        ...
    def ReqQryTrade(self, pQryTradeField: CTORATstpQryTradeField, nRequestID: int)->int:
        ...
    def ReqQryTradingAccount(self, pQryTradingAccountField: CTORATstpQryTradingAccountField, nRequestID: int)->int:
        ...
    def ReqQryPosition(self, pQryPositionField: CTORATstpQryPositionField, nRequestID: int)->int:
        ...
    def ReqQryTradingFee(self, pQryTradingFeeField: CTORATstpQryTradingFeeField, nRequestID: int)->int:
        ...
    def ReqQryInvestorTradingFee(self, pQryInvestorTradingFeeField: CTORATstpQryInvestorTradingFeeField, nRequestID: int)->int:
        ...
    def ReqQryIPOQuota(self, pQryIPOQuotaField: CTORATstpQryIPOQuotaField, nRequestID: int)->int:
        ...
    def ReqQryMarket(self, pQryMarketField: CTORATstpQryMarketField, nRequestID: int)->int:
        ...
    def ReqQryOrderFundDetail(self, pQryOrderFundDetailField: CTORATstpQryOrderFundDetailField, nRequestID: int)->int:
        ...
    def ReqQryFundTransferDetail(self, pQryFundTransferDetailField: CTORATstpQryFundTransferDetailField, nRequestID: int)->int:
        ...
    def ReqQryPositionTransferDetail(self, pQryPositionTransferDetailField: CTORATstpQryPositionTransferDetailField, nRequestID: int)->int:
        ...
    def ReqQryPledgePosition(self, pQryPledgePositionField: CTORATstpQryPledgePositionField, nRequestID: int)->int:
        ...
    def ReqQryPledgeInfo(self, pQryPledgeInfoField: CTORATstpQryPledgeInfoField, nRequestID: int)->int:
        ...
    def ReqQryConversionBondInfo(self, pQryConversionBondInfoField: CTORATstpQryConversionBondInfoField, nRequestID: int)->int:
        ...
    def ReqQryBondPutbackInfo(self, pQryBondPutbackInfoField: CTORATstpQryBondPutbackInfoField, nRequestID: int)->int:
        ...
    def ReqQryStandardBondPosition(self, pQryStandardBondPositionField: CTORATstpQryStandardBondPositionField, nRequestID: int)->int:
        ...
    def ReqQrySpecialMarketData(self, pQrySpecialMarketDataField: CTORATstpQrySpecialMarketDataField, nRequestID: int)->int:
        ...
    def ReqQryPrematurityRepoOrder(self, pQryPrematurityRepoOrderField: CTORATstpQryPrematurityRepoOrderField, nRequestID: int)->int:
        ...
    def ReqQryShareholderParam(self, pQryShareholderParamField: CTORATstpQryShareholderParamField, nRequestID: int)->int:
        ...
    def ReqQryPeripheryPositionTransferDetail(self, pQryPeripheryPositionTransferDetailField: CTORATstpQryPeripheryPositionTransferDetailField, nRequestID: int)->int:
        ...
    def ReqQryInvestorCondOrderLimitParam(self, pQryInvestorCondOrderLimitParamField: CTORATstpQryInvestorCondOrderLimitParamField, nRequestID: int)->int:
        ...
    def ReqQryCondOrder(self, pQryCondOrderField: CTORATstpQryCondOrderField, nRequestID: int)->int:
        ...
    def ReqQryCondOrderAction(self, pQryCondOrderActionField: CTORATstpQryCondOrderActionField, nRequestID: int)->int:
        ...
    def ReqQryTradingNotice(self, pQryTradingNoticeField: CTORATstpQryTradingNoticeField, nRequestID: int)->int:
        ...
    def ReqQryIPONumberResult(self, pQryIPONumberResultField: CTORATstpQryIPONumberResultField, nRequestID: int)->int:
        ...
    def ReqQryIPOMatchNumberResult(self, pQryIPOMatchNumberResultField: CTORATstpQryIPOMatchNumberResultField, nRequestID: int)->int:
        ...
class TORA_TE_RESUME_TYPE(Enum):
    TORA_TERT_RESTART: TORA_TE_RESUME_TYPE
    TORA_TERT_RESUME: TORA_TE_RESUME_TYPE
    TORA_TERT_QUICK: TORA_TE_RESUME_TYPE
TTORATstpDateType = str
TTORATstpTimeType = str
TTORATstpMillisecType = int
TTORATstpPriceType = float
TTORATstpRatioType = float
TTORATstpMoneyType = float
TTORATstpVolumeType = int
TTORATstpLargeVolumeType = float
TTORATstpBoolType = int
TTORATstpSequenceNoType = int
TTORATstpSerialType = str
TTORATstpCommFluxType = int
TTORATstpRoleIDType = int
TTORATstpRoleDescriptionType = str
TTORATstpFunctionsType = str
TTORATstpDeviceIDType = str
TTORATstpDeviceSerialType = str
TTORATstpExchangeIDType = str
TTORATstpAuthModeType = str
TTORATstpVolumeMultipleType = int
TTORATstpIdCardNoType = str
TTORATstpUserIDType = str
TTORATstpTradeIDType = str
TTORATstpOrderSysIDType = str
TTORATstpCondOrderIDType = int
TTORATstpPasswordType = str
TTORATstpFrontIDType = int
TTORATstpSessionIDType = int
TTORATstpProductInfoType = str
TTORATstpProtocolInfoType = str
TTORATstpErrorIDType = int
TTORATstpErrorMsgType = str
TTORATstpPositionTypeType = str
TTORATstpParameterCharValType = str
TTORATstpNameType = str
TTORATstpListingMarketType = str
TTORATstpProductIDType = str
TTORATstpSecurityIDType = str
TTORATstpParValueType = float
TTORATstpPriceTickType = float
TTORATstpTradingUnitType = int
TTORATstpSecurityStatusType = int
TTORATstpAccountIDType = str
TTORATstpInvestorIDType = str
TTORATstpAddressType = str
TTORATstpDepartmentIDType = str
TTORATstpTerminalInfoType = str
TTORATstpShareholderIDType = str
TTORATstpPbuIDType = str
TTORATstpIPAddressType = str
TTORATstpMacAddressType = str
TTORATstpLangType = str
TTORATstpInterestType = float
TTORATstpOrderLocalIDType = str
TTORATstpPositionVolumeType = float
TTORATstpBusinessUnitIDType = str
TTORATstpBusinessUnitNameType = str
TTORATstpTimeStampType = int
TTORATstpBigTimeStampType = int
TTORATstpSecurityNameType = str
TTORATstpExternalSerialType = str
TTORATstpOrderRefType = str
TTORATstpRequestIDType = int
TTORATstpIntSerialType = int
TTORATstpInvestorNameType = str
TTORATstpUserNameType = str
TTORATstpLoginLimitType = int
TTORATstpCurrencyIDType = str
TTORATstpBankIDType = str
TTORATstpBankAccountIDType = str
TTORATstpTransferReasonType = str
TTORATstpCombOffsetFlagType = str
TTORATstpCombHedgeFlagType = str
TTORATstpExchangeInstIDType = str
TTORATstpTelephoneType = str
TTORATstpMobileType = str
TTORATstpTraderIDType = str
TTORATstpLongVolumeType = int
TTORATstpLongSequenceType = int
TTORATstpOrderUnitType = str
TTORATstpIdCardTypeType = str
TTORATstpAccountTypeType = str
TTORATstpDirectionType = str
TTORATstpBrokerageTypeType = str
TTORATstpUserTypeType = str
TTORATstpContingentConditionType = str
TTORATstpETFCurrenceReplaceStatusType = str
TTORATstpOperateSourceType = str
TTORATstpOperwayType = str
TTORATstpOperwaysType = str
TTORATstpOrderPriceTypeType = str
TTORATstpOrderVolumeTypeType = str
TTORATstpTimeConditionType = str
TTORATstpVolumeConditionType = str
TTORATstpForceCloseReasonType = str
TTORATstpFileOrderTypeType = str
TTORATstpTransferDirectionType = str
TTORATstpCollateralDirectionType = str
TTORATstpTransferStatusType = str
TTORATstpTransferPositionTypeType = str
TTORATstpSystemNameType = str
TTORATstpRelativeCondParamType = str
TTORATstpOrderStatusType = str
TTORATstpCondOrderStatusType = str
TTORATstpOrderSubmitStatusType = str
TTORATstpOrderTypeType = str
TTORATstpOffsetFlagType = str
TTORATstpHedgeFlagType = str
TTORATstpActionFlagType = str
TTORATstpOrderActionStatusType = str
TTORATstpClientIDTypeType = str
TTORATstpBizClassType = str
TTORATstpCreditPositionTypeType = str
TTORATstpFunctionIDType = str
TTORATstpSecurityTypeType = str
TTORATstpEndFlagType = str
TTORATstpMarketIDType = str
TTORATstpLogInAccountType = str
TTORATstpLogInAccountTypeType = str
TTORATstpMarketStatusType = str
TTORATstpBigsInfoType = str
TTORATstpShortsInfoType = str
TTORATstpIntInfoType = int
TTORATstpFloatInfoType = float
TTORATstpApiGroupIDType = int
TTORATstpApiRunModeType = str
TTORATstpDesignationTypeType = str
TTORATstpCustodyTransferTypeType = str
TTORATstpProperCtrlBusinessTypeType = str
TTORATstpProperCtrlPassFlagType = str
TTORATstpCRiskLevelType = str
TTORATstpProfInvestorTypeType = str
TTORATstpLOrderTypeType = str
TTORATstpLSideType = str
TTORATstpExecTypeType = str
TTORATstpCondCheckType = str
TTORATstpHDSerialType = str
TTORATstpMDSubModeType = str
TTORATstpMDSecurityStatType = str
TTORATstpCommitStatusType = str
TTORATstpParamTypeType = str
TTORATstpContentType = str
TTORATstpStatusMsgType = str
TTORATstpIPONumberIDType = str
TTORATstpPageLocateType = int
CHAR_NULL_VAL: int
TORA_TSTP_EXD_SSE_FO: str
TORA_TSTP_EXD_SZSE_FO: str
TORA_TSTP_EXD_COMM: str
TORA_TSTP_EXD_SSE: str
TORA_TSTP_EXD_SZSE: str
TORA_TSTP_EXD_HK: str
TORA_TSTP_AM_Password: str
TORA_TSTP_AM_FingerPrint: str
TORA_TSTP_PT_Net: str
TORA_TSTP_PT_Gross: str
TORA_TSTP_PID_COMMON: str
TORA_TSTP_PID_SHStock: str
TORA_TSTP_PID_SHWarrant: str
TORA_TSTP_PID_SHFund: str
TORA_TSTP_PID_SHBond: str
TORA_TSTP_PID_SHStandard: str
TORA_TSTP_PID_SHRepurchase: str
TORA_TSTP_PID_SZStock: str
TORA_TSTP_PID_SZWarrant: str
TORA_TSTP_PID_SZFund: str
TORA_TSTP_PID_SZBond: str
TORA_TSTP_PID_SZStandard: str
TORA_TSTP_PID_SZRepurchase: str
TORA_TSTP_BKID_CCB: str
TORA_TSTP_BKID_ABC: str
TORA_TSTP_BKID_ICBC: str
TORA_TSTP_BKID_BOC: str
TORA_TSTP_BKID_CMB: str
TORA_TSTP_BKID_BC: str
TORA_TSTP_BKID_SPDB: str
TORA_TSTP_BKID_CIB: str
TORA_TSTP_BKID_CEB: str
TORA_TSTP_BKID_GDB: str
TORA_TSTP_BKID_NJCB: str
TORA_TSTP_BKID_SHCB: str
TORA_TSTP_BKID_CITICB: str
TORA_TSTP_BKID_HXB: str
TORA_TSTP_BKID_CMBC: str
TORA_TSTP_BKID_PACB: str
TORA_TSTP_BKID_NBCB: str
TORA_TSTP_OUT_Shou: str
TORA_TSTP_OUT_Gu: str
TORA_TSTP_OUT_Fen: str
TORA_TSTP_OUT_Zhang: str
TORA_TSTP_ICT_EID: str
TORA_TSTP_ICT_IDCard: str
TORA_TSTP_ICT_OfficerIDCard: str
TORA_TSTP_ICT_PoliceIDCard: str
TORA_TSTP_ICT_SoldierIDCard: str
TORA_TSTP_ICT_HouseholdRegister: str
TORA_TSTP_ICT_Passport: str
TORA_TSTP_ICT_TaiwanCompatriotIDCard: str
TORA_TSTP_ICT_HomeComingCard: str
TORA_TSTP_ICT_LicenseNo: str
TORA_TSTP_ICT_TaxNo: str
TORA_TSTP_ICT_HMMainlandTravelPermit: str
TORA_TSTP_ICT_TwMainlandTravelPermit: str
TORA_TSTP_ICT_DrivingLicense: str
TORA_TSTP_ICT_SocialID: str
TORA_TSTP_ICT_LocalID: str
TORA_TSTP_ICT_BusinessRegistration: str
TORA_TSTP_ICT_HKMCIDCard: str
TORA_TSTP_ICT_AccountsPermits: str
TORA_TSTP_ICT_OtherCard: str
TORA_TSTP_FAT_Normal: str
TORA_TSTP_FAT_Credit: str
TORA_TSTP_FAT_Derivatives: str
TORA_TSTP_D_Buy: str
TORA_TSTP_D_Sell: str
TORA_TSTP_D_ETFPur: str
TORA_TSTP_D_ETFRed: str
TORA_TSTP_D_IPO: str
TORA_TSTP_D_Repurchase: str
TORA_TSTP_D_ReverseRepur: str
TORA_TSTP_D_OeFundPur: str
TORA_TSTP_D_OeFundRed: str
TORA_TSTP_D_CollateralIn: str
TORA_TSTP_D_CollateralOut: str
TORA_TSTP_D_PledgeIn: str
TORA_TSTP_D_PledgeOut: str
TORA_TSTP_D_Rationed: str
TORA_TSTP_D_Split: str
TORA_TSTP_D_Merge: str
TORA_TSTP_D_MarginBuy: str
TORA_TSTP_D_ShortSell: str
TORA_TSTP_D_SellRepayment: str
TORA_TSTP_D_BuyRepayment: str
TORA_TSTP_D_SecurityRepay: str
TORA_TSTP_D_RemainTransfer: str
TORA_TSTP_D_BondConvertStock: str
TORA_TSTP_D_BondPutback: str
TORA_TSTP_BT_Gross: str
TORA_TSTP_BT_Net: str
TORA_TSTP_UTYPE_BrokerUser: str
TORA_TSTP_UTYPE_SuperUser: str
TORA_TSTP_UTYPE_Investor: str
TORA_TSTP_CC_TradeTouch: str
TORA_TSTP_CC_CancelTouch: str
TORA_TSTP_CC_TimeTouch: str
TORA_TSTP_CC_SegmentTouch: str
TORA_TSTP_CC_LastPriceGreaterThanStopPrice: str
TORA_TSTP_CC_LastPriceLesserThanStopPrice: str
TORA_TSTP_CC_AskPriceGreaterEqualStopPrice: str
TORA_TSTP_CC_AskPriceLesserEqualStopPrice: str
TORA_TSTP_CC_BidPriceGreaterEqualStopPrice: str
TORA_TSTP_CC_BidPriceLesserEqualStopPrice: str
TORA_TSTP_ETFCTSTAT_Forbidden: str
TORA_TSTP_ETFCTSTAT_Allow: str
TORA_TSTP_ETFCTSTAT_Force: str
TORA_TSTP_ETFCTSTAT_CBAllow: str
TORA_TSTP_ETFCTSTAT_CBForce: str
TORA_TSTP_OPRTSRC_DBCommand: str
TORA_TSTP_OPRTSRC_SyncAPI: str
TORA_TSTP_OPERW_Telephone: str
TORA_TSTP_OPERW_OTC: str
TORA_TSTP_OPERW_MobileClient: str
TORA_TSTP_OPERW_PCClient: str
TORA_TSTP_OPERW_TY: str
TORA_TSTP_OPT_AnyPrice: str
TORA_TSTP_OPT_LimitPrice: str
TORA_TSTP_OPT_BestPrice: str
TORA_TSTP_OPT_LastPrice: str
TORA_TSTP_OPT_AskPrice1: str
TORA_TSTP_OPT_BidPrice1: str
TORA_TSTP_OPT_Relative: str
TORA_TSTP_OPT_FiveLevelPrice: str
TORA_TSTP_OPT_HomeBestPrice: str
TORA_TSTP_OVT_CustomVol: str
TORA_TSTP_OVT_RelativeVol: str
TORA_TSTP_TC_IOC: str
TORA_TSTP_TC_GFS: str
TORA_TSTP_TC_GFD: str
TORA_TSTP_TC_GTD: str
TORA_TSTP_TC_GTC: str
TORA_TSTP_TC_GFA: str
TORA_TSTP_VC_AV: str
TORA_TSTP_VC_MV: str
TORA_TSTP_VC_CV: str
TORA_TSTP_FCC_NotForceClose: str
TORA_TSTP_FCC_LackDeposit: str
TORA_TSTP_FCC_ClientOverPositionLimit: str
TORA_TSTP_FCC_MemberOverPositionLimit: str
TORA_TSTP_FCC_NotMultiple: str
TORA_TSTP_FCC_Violation: str
TORA_TSTP_FCC_Other: str
TORA_TSTP_EOT_Review: str
TORA_TSTP_EOT_Cancel: str
TORA_TSTP_EOT_Limit: str
TORA_TSTP_EOT_FRC: str
TORA_TSTP_EOT_FRL: str
TORA_TSTP_EOT_BP: str
TORA_TSTP_EOT_HP: str
TORA_TSTP_EOT_FAK: str
TORA_TSTP_EOT_FOK: str
TORA_TSTP_TRNSD_In: str
TORA_TSTP_TRNSD_Out: str
TORA_TSTP_TRNSD_MoveIn: str
TORA_TSTP_TRNSD_MoveOut: str
TORA_TSTP_TRNSD_Freeze: str
TORA_TSTP_TRNSD_UnFreeze: str
TORA_TSTP_TRNSD_StockToBank: str
TORA_TSTP_TRNSD_BankToStock: str
TORA_TSTP_CLTD_CollateralIn: str
TORA_TSTP_CLTD_CollateralOut: str
TORA_TSTP_TRANST_TranferHandling: str
TORA_TSTP_TRANST_TransferSuccess: str
TORA_TSTP_TRANST_TransferFail: str
TORA_TSTP_TRANST_RepealHandling: str
TORA_TSTP_TRANST_RepealSuccess: str
TORA_TSTP_TRANST_RepealFail: str
TORA_TSTP_TRANST_ExternalAccepted: str
TORA_TSTP_TPT_ALL: str
TORA_TSTP_TPT_History: str
TORA_TSTP_TPT_TodayBS: str
TORA_TSTP_TPT_TodayPR: str
TORA_TSTP_OST_AllTraded: str
TORA_TSTP_OST_PartTradedQueueing: str
TORA_TSTP_OST_PartTradedNotQueueing: str
TORA_TSTP_OST_NoTradeQueueing: str
TORA_TSTP_OST_NoTradeNotQueueing: str
TORA_TSTP_OST_Canceled: str
TORA_TSTP_OST_Unknown: str
TORA_TSTP_OST_NotTouched: str
TORA_TSTP_OST_Touched: str
TORA_TSTP_OST_Cached: str
TORA_TSTP_COST_Initial: str
TORA_TSTP_COST_NotTouched: str
TORA_TSTP_COST_Touched: str
TORA_TSTP_COST_Finished: str
TORA_TSTP_COST_Cancel: str
TORA_TSTP_COST_Failed: str
TORA_TSTP_OSS_UnSubmit: str
TORA_TSTP_OSS_InsertSubmitted: str
TORA_TSTP_OSS_CancelSubmitted: str
TORA_TSTP_OSS_ModifySubmitted: str
TORA_TSTP_OSS_Accepted: str
TORA_TSTP_OSS_InsertRejected: str
TORA_TSTP_OSS_CancelRejected: str
TORA_TSTP_OSS_ModifyRejected: str
TORA_TSTP_ORDT_Normal: str
TORA_TSTP_ORDT_DeriveFromQuote: str
TORA_TSTP_ORDT_DeriveFromCombination: str
TORA_TSTP_ORDT_Combination: str
TORA_TSTP_ORDT_ConditionalOrder: str
TORA_TSTP_ORDT_Swap: str
TORA_TSTP_OF_Open: str
TORA_TSTP_OF_Close: str
TORA_TSTP_OF_ForceClose: str
TORA_TSTP_OF_CloseToday: str
TORA_TSTP_OF_CloseYesterday: str
TORA_TSTP_OF_ForceOff: str
TORA_TSTP_OF_LocalForceClose: str
TORA_TSTP_HF_Speculation: str
TORA_TSTP_HF_Arbitrage: str
TORA_TSTP_HF_Hedge: str
TORA_TSTP_HF_Covered: str
TORA_TSTP_AF_Delete: str
TORA_TSTP_AF_Modify: str
TORA_TSTP_AF_ForceDelete: str
TORA_TSTP_OAS_Submitted: str
TORA_TSTP_OAS_Accepted: str
TORA_TSTP_OAS_Rejected: str
TORA_TSTP_OAS_Cached: str
TORA_TSTP_CIDT_Unknown: str
TORA_TSTP_CIDT_Speculation: str
TORA_TSTP_CIDT_Arbitrage: str
TORA_TSTP_CIDT_Hedge: str
TORA_TSTP_CIDT_Normal: str
TORA_TSTP_CIDT_Credit: str
TORA_TSTP_CIDT_Derivatives: str
TORA_TSTP_BC_Buy: str
TORA_TSTP_BC_Sell: str
TORA_TSTP_BC_ETFPur: str
TORA_TSTP_BC_ETFRed: str
TORA_TSTP_BC_Repurchase: str
TORA_TSTP_BC_ReverseRepur: str
TORA_TSTP_BC_Rationed: str
TORA_TSTP_BC_CustodyTransfer: str
TORA_TSTP_BC_BuyOpen: str
TORA_TSTP_BC_BuyClose: str
TORA_TSTP_BC_SellOpen: str
TORA_TSTP_BC_SellClose: str
TORA_TSTP_BC_CoveredOpen: str
TORA_TSTP_BC_CoveredClose: str
TORA_TSTP_BC_ExecOrder: str
TORA_TSTP_BC_AutoExecOrder: str
TORA_TSTP_CPT_Normal: str
TORA_TSTP_CPT_Special: str
TORA_TSTP_FID_NAN: str
TORA_TSTP_FID_SessionManager: str
TORA_TSTP_FID_UserManager: str
TORA_TSTP_FID_OrderInsert: str
TORA_TSTP_FID_OrderAction: str
TORA_TSTP_FID_AdjustTradingRight: str
TORA_TSTP_FID_MoveFund: str
TORA_TSTP_FID_AddFund: str
TORA_TSTP_FID_SubFund: str
TORA_TSTP_FID_ForceFreezeFund: str
TORA_TSTP_FID_ForceUnFreezeFund: str
TORA_TSTP_FID_AddPosition: str
TORA_TSTP_FID_SubPosition: str
TORA_TSTP_FID_RepealFund: str
TORA_TSTP_FID_RepealPosition: str
TORA_TSTP_FID_CollateralInJZ: str
TORA_TSTP_FID_AdjustTradingFee: str
TORA_TSTP_FID_AdjustSpecPrivilege: str
TORA_TSTP_FID_AdjustShareholderAssociation: str
TORA_TSTP_FID_AdjustSecurity: str
TORA_TSTP_FID_MovePosition: str
TORA_TSTP_FID_AdjustShareholderParam: str
TORA_TSTP_FID_CondOrderInsert: str
TORA_TSTP_FID_CondOrderAction: str
TORA_TSTP_FID_QryCondOrder: str
TORA_TSTP_FID_CondParamAdjust: str
TORA_TSTP_FID_UserRoleManage: str
TORA_TSTP_FID_TradingFeeTemplateManage: str
TORA_TSTP_FID_TradingRightTemplateManage: str
TORA_TSTP_FID_SecurityPriorAuthManage: str
TORA_TSTP_FID_PosiParamManage: str
TORA_TSTP_FID_OrderLocalSeqPrefixAdjust: str
TORA_TSTP_FID_TraderManage: str
TORA_TSTP_FID_IPOManage: str
TORA_TSTP_FID_AppRunManage: str
TORA_TSTP_FID_MarketStatusManage: str
TORA_TSTP_FID_PlatformStatusManage: str
TORA_TSTP_FID_QryTradingAccount: str
TORA_TSTP_FID_QryPositon: str
TORA_TSTP_FID_QryShareholderAccount: str
TORA_TSTP_FID_QryOrder: str
TORA_TSTP_FID_QryTrade: str
TORA_TSTP_FID_QryFundSerial: str
TORA_TSTP_FID_QryPositionSerial: str
TORA_TSTP_FID_DumpTradingAccount: str
TORA_TSTP_FID_DumpPositon: str
TORA_TSTP_FID_DumpShareholderAccount: str
TORA_TSTP_FID_DumpOrder: str
TORA_TSTP_FID_DumpTrade: str
TORA_TSTP_FID_DumpFundSerial: str
TORA_TSTP_FID_DumpPositionSerial: str
TORA_TSTP_FID_UploadTradeData: str
TORA_TSTP_FID_ReviewFundAdjust: str
TORA_TSTP_FID_ReviewPositionAdjust: str
TORA_TSTP_FID_RecordOperateLog: str
TORA_TSTP_FID_TerminalInfoManage: str
TORA_TSTP_FID_QryTradingRight: str
TORA_TSTP_FID_DesignationRegistration: str
TORA_TSTP_FID_CustodyTransfer: str
TORA_TSTP_FID_ForceDelete: str
TORA_TSTP_FID_RiskMgr: str
TORA_TSTP_FID_ReviewUserIPLimitAdjust: str
TORA_TSTP_FID_AdjustUserIPLimit: str
TORA_TSTP_FID_AdjustSystemParam: str
TORA_TSTP_FID_DepartmentInfoManage: str
TORA_TSTP_FID_IPONumberMatchManage: str
TORA_TSTP_FID_CustomerInfoManage: str
TORA_TSTP_FID_QryTradeEvent: str
TORA_TSTP_FID_ExchRtnSeqManage: str
TORA_TSTP_FID_TransferFund: str
TORA_TSTP_STP_COMMON: str
TORA_TSTP_STP_SHAShares: str
TORA_TSTP_STP_SHSingleMarketStockETF: str
TORA_TSTP_STP_SHSingleMarketBondETF: str
TORA_TSTP_STP_SHGoldETF: str
TORA_TSTP_STP_SHTradableMonetaryFund: str
TORA_TSTP_STP_SHBondNation: str
TORA_TSTP_STP_SHBondCorporation: str
TORA_TSTP_STP_SHBondCompany: str
TORA_TSTP_STP_SHBondConversion: str
TORA_TSTP_STP_SHBondSeparation: str
TORA_TSTP_STP_SHASharesOption: str
TORA_TSTP_STP_SHETFOption: str
TORA_TSTP_STP_SHAllotment: str
TORA_TSTP_STP_SHDistributeDebt: str
TORA_TSTP_STP_SHStandard: str
TORA_TSTP_STP_SHRepo: str
TORA_TSTP_STP_SHCEFund: str
TORA_TSTP_STP_SHOEFund: str
TORA_TSTP_STP_SHCrossMarketStockETF: str
TORA_TSTP_STP_SHCrossBorderETF: str
TORA_TSTP_STP_SHMontherStructFund: str
TORA_TSTP_STP_SHSubStructFund: str
TORA_TSTP_STP_SHRealTimeMonetaryFund: str
TORA_TSTP_STP_SHExchangeableBond: str
TORA_TSTP_STP_SHLOF: str
TORA_TSTP_STP_SZMainAShares: str
TORA_TSTP_STP_SZSME: str
TORA_TSTP_STP_SZBondNation: str
TORA_TSTP_STP_SZBondCorporation: str
TORA_TSTP_STP_SZBondCompany: str
TORA_TSTP_STP_SZBondConversion: str
TORA_TSTP_STP_SZBondSeparation: str
TORA_TSTP_STP_SZASharesOption: str
TORA_TSTP_STP_SZETFOption: str
TORA_TSTP_STP_SZCrossBorderETF: str
TORA_TSTP_STP_SZGoldETF: str
TORA_TSTP_STP_SZCashBondETF: str
TORA_TSTP_STP_SZSingleMarketStockETF: str
TORA_TSTP_STP_SZSingleMarketBondETF: str
TORA_TSTP_STP_SZMonetaryFundETF: str
TORA_TSTP_STP_SZGEM: str
TORA_TSTP_STP_SZAllotment: str
TORA_TSTP_STP_SZDistributeDebt: str
TORA_TSTP_STP_SZStandard: str
TORA_TSTP_STP_SZRepo: str
TORA_TSTP_STP_SZCEFund: str
TORA_TSTP_STP_SZOEFund: str
TORA_TSTP_STP_SZCrossBorderOEFund: str
TORA_TSTP_STP_SZCrossMarketStockETF: str
TORA_TSTP_STP_SZLOF: str
TORA_TSTP_STP_SZCrossBorderLOF: str
TORA_TSTP_STP_SZMontherStructFund: str
TORA_TSTP_STP_SZSubStructFund: str
TORA_TSTP_STP_SZMontherCrossBorderStructFund: str
TORA_TSTP_STP_SZSubCrossBorderStructFund: str
TORA_TSTP_STP_SZExchangeableBond: str
TORA_TSTP_STP_SZGEMConversionBond: str
TORA_TSTP_EF_ToBeContinued: str
TORA_TSTP_EF_BatchEnd: str
TORA_TSTP_EF_Completed: str
TORA_TSTP_EF_NOP: str
TORA_TSTP_MKD_COMMON: str
TORA_TSTP_MKD_SHA: str
TORA_TSTP_MKD_SZA: str
TORA_TSTP_MKD_SHB: str
TORA_TSTP_MKD_SZB: str
TORA_TSTP_MKD_SZThreeA: str
TORA_TSTP_MKD_SZThreeB: str
TORA_TSTP_MKD_Foreign: str
TORA_TSTP_LACT_UserID: str
TORA_TSTP_LACT_AccountID: str
TORA_TSTP_LACT_SHAStock: str
TORA_TSTP_LACT_SZAStock: str
TORA_TSTP_LACT_SHBStock: str
TORA_TSTP_LACT_SZBStock: str
TORA_TSTP_LACT_ThreeNewBoardA: str
TORA_TSTP_LACT_ThreeNewBoardB: str
TORA_TSTP_LACT_HKStock: str
TORA_TSTP_MST_UnKnown: str
TORA_TSTP_MST_BeforeTrading: str
TORA_TSTP_MST_Continous: str
TORA_TSTP_MST_Closed: str
TORA_TSTP_MST_OpenCallAuction: str
TORA_TSTP_ARM_Single: str
TORA_TSTP_ARM_Group: str
TORA_TSTP_DT_Register: str
TORA_TSTP_DT_Cancel: str
TORA_TSTP_CT_Register: str
TORA_TSTP_CT_Cancel: str
TORA_TSTP_PCBT_None: str
TORA_TSTP_PCBT_Other: str
TORA_TSTP_PCBT_SHDelisting: str
TORA_TSTP_PCBT_ST: str
TORA_TSTP_PCBT_GEM: str
TORA_TSTP_PCBT_StructFund: str
TORA_TSTP_PCBT_BondQualified: str
TORA_TSTP_PCBT_SuspendBond: str
TORA_TSTP_PCBT_Repurchase: str
TORA_TSTP_PCBT_ReverseRepur: str
TORA_TSTP_PCBT_SZDelisting: str
TORA_TSTP_PCBT_Stock: str
TORA_TSTP_PCBT_CreditStock: str
TORA_TSTP_PCPF_None: str
TORA_TSTP_PCPF_AnywayPass: str
TORA_TSTP_PCPF_MatchPass: str
TORA_TSTP_PCPF_SelectPass: str
TORA_TSTP_PCPF_ProfInvestorPass: str
TORA_TSTP_RLV_Lowest: str
TORA_TSTP_RLV_Conservative: str
TORA_TSTP_RLV_Cautious: str
TORA_TSTP_RLV_Steady: str
TORA_TSTP_RLV_Positive: str
TORA_TSTP_RLV_Aggressive: str
TORA_TSTP_PIT_NotProf: str
TORA_TSTP_PIT_OCInstiPro: str
TORA_TSTP_PIT_InstiPro: str
TORA_TSTP_PIT_PersonPro: str
TORA_TSTP_PIT_ConfirmInstiPro: str
TORA_TSTP_PIT_ConfirmPersonPro: str
TORA_TSTP_LOT_Market: str
TORA_TSTP_LOT_Limit: str
TORA_TSTP_LOT_HomeBest: str
TORA_TSTP_LSD_Buy: str
TORA_TSTP_LSD_Sell: str
TORA_TSTP_LSD_Borrow: str
TORA_TSTP_LSD_Lend: str
TORA_TSTP_ECT_Fill: str
TORA_TSTP_ECT_Cancel: str
TORA_TSTP_CCT_None: str
TORA_TSTP_CCT_SelfDeal: str
TORA_TSTP_MST_TCP: str
TORA_TSTP_MST_UDP: str
TORA_TSTP_MST_MCAST: str
TORA_TSTP_MSST_PreOpen: str
TORA_TSTP_MSST_CallAuction: str
TORA_TSTP_MSST_Continous: str
TORA_TSTP_MSST_Pause: str
TORA_TSTP_MSST_Suspend: str
TORA_TSTP_MSST_LongSuspend: str
TORA_TSTP_MSST_UndulationInt: str
TORA_TSTP_MSST_CircuitBreak: str
TORA_TSTP_MSST_CircuitBreakU: str
TORA_TSTP_MSST_Close: str
TORA_TSTP_MSST_Other: str
TORA_TSTP_MSST_CloseCallAuction: str
TORA_TSTP_FOCS_Init: str
TORA_TSTP_FOCS_Reviewed: str
TORA_TSTP_FOCS_Failed: str
TORA_TSTP_SPT_MaxBuyLimit: str
TORA_TSTP_SPT_MaxSellLimit: str
TORA_TSTP_SPT_LargeBuyLimitRatio: str
TORA_TSTP_SPT_LargeSelLimitRatio: str
TORA_TSTP_SPT_RiskWarnBoardLimitVol: str
TORA_TSTP_SPT_SeriesDecInterval: str
TORA_TSTP_SPT_SeriesLimitPerUnit: str
TORA_TSTP_SPT_ClosePriceScopeRatio: str
TORA_TSTP_SPT_OpenDateLimit: str
TORA_TSTP_SPT_LimitBoardShamRatio: str
TORA_TSTP_SPT_CancelOrderRatio: str
def set_null(v: int)->None:
    ...
def set_null(v: float)->None:
    ...
def set_null(v: str)->None:
    ...
def set_null(v: int)->None:
    ...
def set_null(v: int)->None:
    ...
def set_null(v: str)->None:
    ...
def is_null(v: int)->bool:
    ...
def is_null(v: float)->bool:
    ...
def is_null(v: str)->bool:
    ...
def is_null(v: int)->bool:
    ...
def is_null(v: int)->bool:
    ...
def is_null(v: str)->bool:
    ...

