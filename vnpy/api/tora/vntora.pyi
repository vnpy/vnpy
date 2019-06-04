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
    LogInAccountType: int
    
    
class CTORATstpEffectPriceMarketDataField():
    
    
    ExchangeID: int
    SecurityID: str
    LastPrice: float
    TotalVolume: int
    Turnover: float
    UpdateTime: str
    UpdateMillisec: int
    
    
class CTORATstpEffectVolumeMarketDataField():
    
    
    ExchangeID: int
    SecurityID: str
    LastPrice: float
    TotalVolume: int
    Turnover: float
    UpdateTime: str
    UpdateMillisec: int
    
    
class CTORATstpFundsFlowMarketDataField():
    
    
    ExchangeID: int
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
    LogInAccountType: int
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
    AuthMode: int
    DeviceID: str
    DeviceSerial: str
    
    
class CTORATstpRspUserLoginField():
    
    
    LoginTime: str
    LogInAccount: str
    LogInAccountType: int
    SystemName: str
    FrontID: int
    SessionID: int
    MaxOrderRef: str
    PrivateFlowCount: int
    PublicFlowCount: int
    TradingDay: str
    UserID: str
    UserName: str
    UserType: int
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
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    VolumeCondition: int
    MinVolume: int
    ForceCloseReason: int
    RequestID: int
    UserForceClose: int
    IsSwapOrder: int
    ExchangeID: int
    ShareholderID: str
    BusinessUnitID: str
    AccountID: str
    IPAddress: str
    MacAddress: str
    CreditPositionType: int
    OrderSysID: str
    TerminalInfo: str
    BInfo: str
    SInfo: str
    IInfo: int
    TransfereePbuID: str
    Operway: int
    CondCheck: int
    HDSerial: str
    
    
class CTORATstpOrderField():
    
    
    InvestorID: str
    SecurityID: str
    OrderRef: str
    UserID: str
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    VolumeCondition: int
    MinVolume: int
    ForceCloseReason: int
    RequestID: int
    OrderLocalID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    ExchangeInstID: str
    TraderID: str
    OrderSubmitStatus: int
    TradingDay: str
    OrderSysID: str
    OrderStatus: int
    OrderType: int
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
    CreditPositionType: int
    BInfo: str
    SInfo: str
    IInfo: int
    TransfereePbuID: str
    Operway: int
    DepartmentID: str
    ProperCtrlBusinessType: int
    ProperCtrlPassFlag: int
    CondCheck: int
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
    ExchangeID: int
    OrderSysID: str
    ActionFlag: int
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
    Operway: int
    HDSerial: str
    
    
class CTORATstpOrderActionField():
    
    
    InvestorID: str
    OrderActionRef: str
    OrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: int
    OrderSysID: str
    ActionFlag: int
    LimitPrice: float
    VolumeChange: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    OrderLocalID: str
    ActionLocalID: str
    ShareholderID: str
    OrderActionStatus: int
    UserID: str
    StatusMsg: str
    SecurityID: str
    IPAddress: str
    MacAddress: str
    BInfo: str
    SInfo: str
    IInfo: int
    Operway: int
    
    
class CTORATstpTradeField():
    
    
    InvestorID: str
    SecurityID: str
    UserID: str
    ExchangeID: int
    TradeID: str
    Direction: int
    OrderSysID: str
    MarketID: int
    ShareholderID: str
    ExchangeInstID: str
    OffsetFlag: int
    HedgeFlag: int
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
    
    
    MarketID: int
    MarketStatus: int
    
    
class CTORATstpInputCondOrderField():
    
    
    ExchangeID: int
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    Direction: int
    OrderPriceType: int
    OrderVolumeType: int
    TimeCondition: int
    VolumeCondition: int
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
    Operway: int
    CondCheck: int
    ContingentCondition: int
    ConditionPrice: float
    PriceTicks: int
    VolumeMultiple: int
    RelativeFrontID: int
    RelativeSessionID: int
    RelativeParam: str
    AppendContingentCondition: int
    AppendConditionPrice: float
    AppendRelativeFrontID: int
    AppendRelativeSessionID: int
    AppendRelativeParam: str
    HDSerial: str
    
    
class CTORATstpConditionOrderField():
    
    
    ExchangeID: int
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    Direction: int
    OrderPriceType: int
    OrderVolumeType: int
    TimeCondition: int
    VolumeCondition: int
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
    Operway: int
    CondCheck: int
    ContingentCondition: int
    ConditionPrice: float
    PriceTicks: int
    VolumeMultiple: int
    RelativeFrontID: int
    RelativeSessionID: int
    RelativeParam: str
    AppendContingentCondition: int
    AppendConditionPrice: float
    AppendRelativeFrontID: int
    AppendRelativeSessionID: int
    AppendRelativeParam: str
    TradingDay: str
    CondOrderStatus: int
    InsertDate: str
    InsertTime: str
    CancelTime: str
    CancelUser: str
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    DepartmentID: str
    ProperCtrlBusinessType: int
    ProperCtrlPassFlag: int
    ActiveDate: str
    ActiveTime: str
    
    
class CTORATstpInputCondOrderActionField():
    
    
    RequestID: int
    ExchangeID: int
    CondOrderActionRef: str
    CondOrderRef: str
    FrontID: int
    SessionID: int
    CondOrderID: int
    ActionFlag: int
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
    Operway: int
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
    TransferDirection: int
    Amount: float
    DepartmentID: str
    BankID: int
    AccountPassword: str
    BankPassword: str
    
    
class CTORATstpInputTransferPositionField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: int
    ShareholderID: str
    SecurityID: str
    ApplySerial: str
    TransferDirection: int
    Volume: int
    TransferPositionType: int
    MarketID: int
    
    
class CTORATstpTransferFundField():
    
    
    FundSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    AccountID: str
    CurrencyID: str
    TransferDirection: int
    Amount: float
    TransferStatus: int
    OperatorID: str
    OperateDate: str
    OperateTime: str
    DepartmentID: str
    BankAccountID: str
    BankID: int
    
    
class CTORATstpTransferPositionField():
    
    
    PositionSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: int
    ShareholderID: str
    MarketID: int
    SecurityID: str
    TradingDay: str
    TransferDirection: int
    TransferPositionType: int
    HistoryVolume: int
    TodayBSVolume: int
    TodayPRVolume: int
    TransferStatus: int
    OperatorID: str
    OperateDate: str
    OperateTime: str
    
    
class CTORATstpSpecificSecurityField():
    
    
    ExchangeID: int
    SecurityID: str
    
    
class CTORATstpInputTransferCollateralField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: int
    ShareholderID: str
    SecurityID: str
    ApplySerial: str
    CollateralDirection: int
    Volume: int
    MarketID: int
    Operway: int
    
    
class CTORATstpReqInquiryBankAccountFundField():
    
    
    DepartmentID: str
    AccountID: str
    CurrencyID: str
    BankID: int
    BankPassword: str
    
    
class CTORATstpRspInquiryBankAccountFundField():
    
    
    DepartmentID: str
    AccountID: str
    CurrencyID: str
    BankID: int
    BankAccountID: str
    Balance: float
    
    
class CTORATstpLev2MarketDataField():
    
    
    SecurityID: str
    ExchangeID: int
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
    MDSecurityStat: int
    
    
class CTORATstpLev2IndexField():
    
    
    ExchangeID: int
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
    
    
    ExchangeID: int
    SecurityID: str
    TradeTime: int
    TradePrice: float
    TradeVolume: int
    ExecType: int
    MainSeq: int
    SubSeq: int
    BuyNo: int
    SellNo: int
    Info1: int
    Info2: int
    Info3: int
    
    
class CTORATstpLev2OrderDetailField():
    
    
    ExchangeID: int
    SecurityID: str
    OrderTime: int
    Price: float
    Volume: int
    Side: int
    OrderType: int
    MainSeq: int
    SubSeq: int
    Info1: int
    Info2: int
    Info3: int
    
    
class CTORATstpUploadTradeDataField():
    
    
    ExchangeID: int
    TradingDay: str
    bForce: int
    
    
class CTORATstpInputDesignationRegistrationField():
    
    
    InvestorID: str
    UserID: str
    DesignationType: int
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
    CustodyTransferType: int
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
    
    
    ExchangeID: int
    MarketID: int
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    AccountID: str
    ShareholderID: str
    ConcentrationRatio1: float
    ConcentrationRatio2: float
    
    
class CTORATstpInquiryFileOrderField():
    
    
    ExchangeID: int
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderSerialBeg: int
    OrderSerialEnd: int
    CommitStatus: int
    
    
class CTORATstpFileOrderField():
    
    
    RequestID: int
    ExchangeID: int
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderRef: str
    FileOrderType: int
    Direction: int
    LimitPrice: float
    VolumeTotalOriginal: int
    Operway: int
    OrderActionRef: str
    OrderSysID: str
    CondCheck: int
    OrderSerial: int
    CommitStatus: int
    StatusMsg: str
    TimeStamp: int
    
    
class CTORATstpQryRspInfoField():
    
    
    EndFlag: int
    ErrorID: int
    ErrorMsg: str
    
    
class CTORATstpReviewFileOrderField():
    
    
    ExchangeID: int
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderSerialBeg: int
    OrderSerialEnd: int
    
    
class CTORATstpCommitInfoField():
    
    
    OrderSerial: int
    CommitStatus: int
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
    ExchangeID: int
    ShareholderID: str
    InvestorID: str
    SecurityID: str
    OrderRef: str
    FileOrderType: int
    Direction: int
    LimitPrice: float
    VolumeTotalOriginal: int
    Operway: int
    OrderActionRef: str
    OrderSysID: str
    CondCheck: int
    OrderSerial: int
    CommitStatus: int
    StatusMsg: str
    
    
class CTORATstpReqInquiryMaxOrderVolumeField():
    
    
    ExchangeID: int
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    AccountID: str
    ShareholderID: str
    Direction: int
    OrderPriceType: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    TimeCondition: int
    VolumeCondition: int
    LimitPrice: float
    TransfereePbuID: str
    MaxVolume: int
    
    
class CTORATstpRspInquiryMaxOrderVolumeField():
    
    
    ExchangeID: int
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    AccountID: str
    ShareholderID: str
    Direction: int
    OrderPriceType: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    TimeCondition: int
    VolumeCondition: int
    LimitPrice: float
    TransfereePbuID: str
    MaxVolume: int
    
    
class CTORATstpPeripheryPositionTransferDetailField():
    
    
    PositionSerial: int
    ApplySerial: int
    FrontID: int
    SessionID: int
    TransferDirection: int
    ExchangeID: int
    MarketID: int
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    TodayBSPos: int
    TodayPRPos: int
    HistoryPos: int
    TradingDay: str
    TransferReason: str
    TransferStatus: int
    OperateDate: str
    OperateTime: str
    RepealDate: str
    RepealTime: str
    RepealReason: str
    StatusMsg: str
    
    
class CTORATstpQryHistoryOrderField():
    
    
    ExchangeID: int
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
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    VolumeCondition: int
    MinVolume: int
    ForceCloseReason: int
    RequestID: int
    OrderLocalID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    ExchangeInstID: str
    TraderID: str
    OrderSubmitStatus: int
    TradingDay: str
    OrderSysID: str
    OrderStatus: int
    OrderType: int
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
    CreditPositionType: int
    BInfo: str
    SInfo: str
    IInfo: int
    TransfereePbuID: str
    Operway: int
    DepartmentID: str
    ProperCtrlBusinessType: int
    ProperCtrlPassFlag: int
    CondCheck: int
    IsCacheOrder: int
    Turnover: float
    RtnFloatInfo: float
    RtnIntInfo: int
    PageLocate: int
    
    
class CTORATstpQryHistoryTradeField():
    
    
    ExchangeID: int
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
    ExchangeID: int
    TradeID: str
    Direction: int
    OrderSysID: str
    MarketID: int
    ShareholderID: str
    ExchangeInstID: str
    OffsetFlag: int
    HedgeFlag: int
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
    
    
    ExchangeID: int
    
    
class CTORATstpExchangeField():
    
    
    ExchangeID: int
    ExchangeName: str
    TradingDay: str
    
    
class CTORATstpQryPBUField():
    
    
    PbuID: str
    ExchangeID: int
    MarketID: int
    
    
class CTORATstpPBUField():
    
    
    PbuID: str
    PbuName: str
    ExchangeID: int
    MarketID: int
    
    
class CTORATstpQryMarketDataField():
    
    
    SecurityID: str
    ExchangeID: int
    
    
class CTORATstpMarketDataField():
    
    
    TradingDay: str
    SecurityID: str
    ExchangeID: int
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
    MDSecurityStat: int
    HWFlag: int
    
    
class CTORATstpQrySecurityField():
    
    
    SecurityID: str
    ExchangeID: int
    ExchangeInstID: str
    ProductID: int
    
    
class CTORATstpSecurityField():
    
    
    SecurityID: str
    ExchangeID: int
    SecurityName: str
    ExchangeInstID: str
    MarketID: int
    ProductID: int
    SecurityType: int
    OrderUnit: int
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
    PositionType: int
    ParValue: float
    SecurityStatus: int
    BondInterest: float
    ConversionRate: float
    IsCollateral: int
    
    
class CTORATstpQryETFFileField():
    
    
    ExchangeID: int
    ETFSecurityID: str
    ETFCreRedSecurityID: str
    
    
class CTORATstpETFFileField():
    
    
    TradingDay: str
    ExchangeID: int
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
    
    
    ExchangeID: int
    ETFSecurityID: str
    SecurityID: str
    
    
class CTORATstpETFBasketField():
    
    
    TradingDay: str
    ExchangeID: int
    ETFSecurityID: str
    SecurityID: str
    SecurityName: str
    Volume: int
    ETFCurrenceReplaceStatus: int
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
    
    
    ExchangeID: int
    SecurityID: str
    
    
class CTORATstpIPOInfoField():
    
    
    ExchangeID: int
    SecurityID: str
    MarketID: int
    ProductID: int
    SecurityType: int
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
    FunctionID: int
    
    
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
    UserType: int
    
    
class CTORATstpUserField():
    
    
    UserID: str
    UserName: str
    UserType: int
    IsActive: int
    LoginLimit: int
    
    
class CTORATstpQryInvestorField():
    
    
    InvestorID: str
    
    
class CTORATstpInvestorField():
    
    
    InvestorID: str
    InvestorName: str
    IdCardType: int
    IdCardNo: str
    Telephone: str
    Address: str
    OpenDate: str
    Mobile: str
    Operways: str
    CRiskLevel: int
    ProfInvestorType: int
    
    
class CTORATstpQryShareholderAccountField():
    
    
    InvestorID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    TradingCodeClass: int
    
    
class CTORATstpShareholderAccountField():
    
    
    InvestorID: str
    ExchangeID: int
    ShareholderID: str
    ClientIDType: int
    MarketID: int
    
    
class CTORATstpQryBusinessUnitField():
    
    
    InvestorID: str
    
    
class CTORATstpBusinessUnitField():
    
    
    InvestorID: str
    BusinessUnitID: str
    BusinessUnitName: str
    
    
class CTORATstpQryBusinessUnitAndTradingAcctField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ProductID: int
    AccountID: str
    CurrencyID: str
    
    
class CTORATstpBusinessUnitAndTradingAcctField():
    
    
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    ProductID: int
    AccountID: str
    CurrencyID: str
    UserID: str
    
    
class CTORATstpQryOrderField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: int
    MarketID: int
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
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    BInfo: str
    SInfo: str
    IInfo: int
    
    
class CTORATstpQryTradeField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    TradeID: str
    TradeTimeStart: str
    TradeTimeEnd: str
    BusinessUnitID: str
    
    
class CTORATstpQryTradingAccountField():
    
    
    InvestorID: str
    CurrencyID: str
    AccountID: str
    AccountType: int
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
    AccountType: int
    AccountOwner: str
    DepartmentID: str
    BankID: int
    BankAccountID: str
    
    
class CTORATstpQryPositionField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    BusinessUnitID: str
    
    
class CTORATstpPositionField():
    
    
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: int
    MarketID: int
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
    
    
    ExchangeID: int
    
    
class CTORATstpTradingFeeField():
    
    
    ExchangeID: int
    ProductID: int
    SecurityType: int
    SecurityID: str
    BizClass: int
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
    ExchangeID: int
    DepartmentID: str
    
    
class CTORATstpInvestorTradingFeeField():
    
    
    InvestorID: str
    ExchangeID: int
    ProductID: int
    SecurityType: int
    SecurityID: str
    BizClass: int
    BrokerageType: int
    RatioByAmt: float
    RatioByPar: float
    FeePerOrder: float
    FeeMin: float
    FeeMax: float
    FeeByVolume: float
    DepartmentID: str
    
    
class CTORATstpQryIPOQuotaField():
    
    
    InvestorID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    
    
class CTORATstpIPOQuotaField():
    
    
    InvestorID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    MaxVolume: int
    
    
class CTORATstpQryMarketField():
    
    
    ExchangeID: int
    MarketID: int
    
    
class CTORATstpMarketField():
    
    
    MarketID: int
    MarketName: str
    ExchangeID: int
    
    
class CTORATstpQryOrderFundDetailField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: int
    OrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    BusinessUnitID: str
    
    
class CTORATstpOrderFundDetailField():
    
    
    InvestorID: str
    InstrumentID: str
    ExchangeID: int
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
    TransferDirection: int
    DepartmentID: str
    
    
class CTORATstpFundTransferDetailField():
    
    
    FundSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    AccountID: str
    CurrencyID: str
    TransferDirection: int
    Amount: float
    TransferStatus: int
    OperateSource: int
    OperatorID: str
    OperateDate: str
    OperateTime: str
    StatusMsg: str
    DepartmentID: str
    BankID: int
    BankAccountID: str
    
    
class CTORATstpQryPositionTransferDetailField():
    
    
    ShareholderID: str
    SecurityID: str
    TransferDirection: int
    
    
class CTORATstpPositionTransferDetailField():
    
    
    PositionSerial: str
    ApplySerial: str
    FrontID: int
    SessionID: int
    InvestorID: str
    ExchangeID: int
    ShareholderID: str
    MarketID: int
    SecurityID: str
    TradingDay: str
    TransferDirection: int
    TransferPositionType: int
    TransferStatus: int
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
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    BusinessUnitID: str
    
    
class CTORATstpPledgePositionField():
    
    
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    TradingDay: str
    HisPledgePos: int
    HisPledgePosFrozen: int
    TodayPledgePos: int
    TodayPledgePosFrozen: int
    PreTotalPledgePos: int
    preAvailablePledgePos: int
    
    
class CTORATstpQryPledgeInfoField():
    
    
    ExchangeID: int
    SecurityID: str
    
    
class CTORATstpPledgeInfoField():
    
    
    ExchangeID: int
    MarketID: int
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
    
    
    ExchangeID: int
    SecurityID: str
    
    
class CTORATstpConversionBondInfoField():
    
    
    ExchangeID: int
    MarketID: int
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
    
    
    ExchangeID: int
    SecurityID: str
    
    
class CTORATstpBondPutbackInfoField():
    
    
    ExchangeID: int
    MarketID: int
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
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    BusinessUnitID: str
    
    
class CTORATstpStandardBondPositionField():
    
    
    SecurityID: str
    InvestorID: str
    BusinessUnitID: str
    ExchangeID: int
    MarketID: int
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
    DesignationType: int
    OrderLocalID: str
    ShareholderID: str
    PbuID: str
    OrderSubmitStatus: int
    TradingDay: str
    OrderSysID: str
    OrderStatus: int
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
    CustodyTransferType: int
    OrderLocalID: str
    ShareholderID: str
    PbuID: str
    OrderSubmitStatus: int
    TradingDay: str
    OrderSysID: str
    OrderStatus: int
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
    ExchangeID: int
    
    
class CTORATstpSpecialMarketDataField():
    
    
    TradingDay: str
    ExchangeID: int
    SecurityID: str
    SecurityName: str
    MovingAvgPrice: float
    MovingAvgPriceSamplingNum: int
    UpdateTime: str
    UpdateMillisec: int
    
    
class CTORATstpQryPrematurityRepoOrderField():
    
    
    InvestorID: str
    SecurityID: str
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    BusinessUnitID: str
    OrderLocalID: str
    ProductID: int
    SecurityType: int
    Direction: int
    TradeID: str
    
    
class CTORATstpPrematurityRepoOrderField():
    
    
    ExchangeID: int
    MarketID: int
    InvestorID: str
    ShareholderID: str
    BusinessUnitID: str
    TradeDay: str
    ExpireDay: str
    OrderLocalID: str
    SecurityID: str
    SecurityName: str
    ProductID: int
    SecurityType: int
    Direction: int
    VolumeTraded: int
    Price: float
    Turnover: float
    TradeID: str
    RepoTotalMoney: float
    InterestAmount: float
    
    
class CTORATstpQryShareholderParamField():
    
    
    MarketID: int
    ShareholderID: str
    TradingCodeClass: int
    ProductID: int
    SecurityType: int
    SecurityID: str
    ParamType: int
    ExchangeID: int
    
    
class CTORATstpShareholderParamField():
    
    
    ExchangeID: int
    MarketID: int
    ShareholderID: str
    TradingCodeClass: int
    ProductID: int
    SecurityType: int
    SecurityID: str
    ParamType: int
    ParamValue: str
    
    
class CTORATstpQryPeripheryPositionTransferDetailField():
    
    
    InvestorID: str
    ShareholderID: str
    SecurityID: str
    TransferDirection: int
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
    ExchangeID: int
    ShareholderID: str
    CondOrderID: int
    InsertTimeStart: str
    InsertTimeEnd: str
    BusinessUnitID: str
    BInfo: str
    SInfo: str
    IInfo: int
    
    
class CTORATstpCondOrderField():
    
    
    ExchangeID: int
    InvestorID: str
    BusinessUnitID: str
    ShareholderID: str
    SecurityID: str
    Direction: int
    OrderPriceType: int
    OrderVolumeType: int
    TimeCondition: int
    VolumeCondition: int
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
    Operway: int
    CondCheck: int
    ContingentCondition: int
    ConditionPrice: float
    PriceTicks: int
    VolumeMultiple: int
    RelativeFrontID: int
    RelativeSessionID: int
    RelativeParam: str
    AppendContingentCondition: int
    AppendConditionPrice: float
    AppendRelativeFrontID: int
    AppendRelativeSessionID: int
    AppendRelativeParam: str
    TradingDay: str
    CondOrderStatus: int
    InsertDate: str
    InsertTime: str
    CancelTime: str
    CancelUser: str
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    DepartmentID: str
    ProperCtrlBusinessType: int
    ProperCtrlPassFlag: int
    ActiveDate: str
    ActiveTime: str
    
    
class CTORATstpQryCondOrderActionField():
    
    
    InvestorID: str
    ExchangeID: int
    ShareholderID: str
    BInfo: str
    SInfo: str
    IInfo: int
    
    
class CTORATstpCondOrderActionField():
    
    
    ExchangeID: int
    RequestID: int
    CondOrderActionRef: str
    CondOrderRef: str
    FrontID: int
    SessionID: int
    CondOrderID: int
    ActionFlag: int
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
    Operway: int
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
    ExchangeID: int
    ShareholderID: str
    
    
class CTORATstpIPONumberResultField():
    
    
    ExchangeID: int
    SecurityID: str
    Day: str
    SecurityName: str
    ShareholderID: str
    SecurityType: int
    BeginNumberID: str
    Volume: int
    
    
class CTORATstpQryIPOMatchNumberResultField():
    
    
    SecurityID: str
    ExchangeID: int
    ShareholderID: str
    MatchNumberID: str
    
    
class CTORATstpIPOMatchNumberResultField():
    
    
    ExchangeID: int
    SecurityID: str
    Day: str
    SecurityName: str
    ShareholderID: str
    SecurityType: int
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
    def SubscribeMarketData(self, ppSecurityID: List[str], ExchageID: int)->int:
        ...
    def UnSubscribeMarketData(self, ppSecurityID: List[str], ExchageID: int)->int:
        ...
    def SubscribeSpecialMarketData(self, ppSecurityID: List[str], ExchageID: int)->int:
        ...
    def UnSubscribeSpecialMarketData(self, ppSecurityID: List[str], ExchageID: int)->int:
        ...
    def SubscribeFundsFlowMarketData(self, ppInstrumentID: List[str], ExchageID: int)->int:
        ...
    def UnSubscribeFundsFlowMarketData(self, ppInstrumentID: List[str], ExchageID: int)->int:
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
TTORATstpExchangeIDType = int
TTORATstpAuthModeType = int
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
TTORATstpPositionTypeType = int
TTORATstpParameterCharValType = str
TTORATstpNameType = str
TTORATstpListingMarketType = str
TTORATstpProductIDType = int
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
TTORATstpBankIDType = int
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
TTORATstpOrderUnitType = int
TTORATstpIdCardTypeType = int
TTORATstpAccountTypeType = int
TTORATstpDirectionType = int
TTORATstpBrokerageTypeType = int
TTORATstpUserTypeType = int
TTORATstpContingentConditionType = int
TTORATstpETFCurrenceReplaceStatusType = int
TTORATstpOperateSourceType = int
TTORATstpOperwayType = int
TTORATstpOperwaysType = str
TTORATstpOrderPriceTypeType = int
TTORATstpOrderVolumeTypeType = int
TTORATstpTimeConditionType = int
TTORATstpVolumeConditionType = int
TTORATstpForceCloseReasonType = int
TTORATstpFileOrderTypeType = int
TTORATstpTransferDirectionType = int
TTORATstpCollateralDirectionType = int
TTORATstpTransferStatusType = int
TTORATstpTransferPositionTypeType = int
TTORATstpSystemNameType = str
TTORATstpRelativeCondParamType = str
TTORATstpOrderStatusType = int
TTORATstpCondOrderStatusType = int
TTORATstpOrderSubmitStatusType = int
TTORATstpOrderTypeType = int
TTORATstpOffsetFlagType = int
TTORATstpHedgeFlagType = int
TTORATstpActionFlagType = int
TTORATstpOrderActionStatusType = int
TTORATstpClientIDTypeType = int
TTORATstpBizClassType = int
TTORATstpCreditPositionTypeType = int
TTORATstpFunctionIDType = int
TTORATstpSecurityTypeType = int
TTORATstpEndFlagType = int
TTORATstpMarketIDType = int
TTORATstpLogInAccountType = str
TTORATstpLogInAccountTypeType = int
TTORATstpMarketStatusType = int
TTORATstpBigsInfoType = str
TTORATstpShortsInfoType = str
TTORATstpIntInfoType = int
TTORATstpFloatInfoType = float
TTORATstpApiGroupIDType = int
TTORATstpApiRunModeType = int
TTORATstpDesignationTypeType = int
TTORATstpCustodyTransferTypeType = int
TTORATstpProperCtrlBusinessTypeType = int
TTORATstpProperCtrlPassFlagType = int
TTORATstpCRiskLevelType = int
TTORATstpProfInvestorTypeType = int
TTORATstpLOrderTypeType = int
TTORATstpLSideType = int
TTORATstpExecTypeType = int
TTORATstpCondCheckType = int
TTORATstpHDSerialType = str
TTORATstpMDSubModeType = int
TTORATstpMDSecurityStatType = int
TTORATstpCommitStatusType = int
TTORATstpParamTypeType = int
TTORATstpContentType = str
TTORATstpStatusMsgType = str
TTORATstpIPONumberIDType = str
TTORATstpPageLocateType = int
CHAR_NULL_VAL: int
TORA_TSTP_EXD_SSE_FO: int
TORA_TSTP_EXD_SZSE_FO: int
TORA_TSTP_EXD_COMM: int
TORA_TSTP_EXD_SSE: int
TORA_TSTP_EXD_SZSE: int
TORA_TSTP_EXD_HK: int
TORA_TSTP_AM_Password: int
TORA_TSTP_AM_FingerPrint: int
TORA_TSTP_PT_Net: int
TORA_TSTP_PT_Gross: int
TORA_TSTP_PID_COMMON: int
TORA_TSTP_PID_SHStock: int
TORA_TSTP_PID_SHWarrant: int
TORA_TSTP_PID_SHFund: int
TORA_TSTP_PID_SHBond: int
TORA_TSTP_PID_SHStandard: int
TORA_TSTP_PID_SHRepurchase: int
TORA_TSTP_PID_SZStock: int
TORA_TSTP_PID_SZWarrant: int
TORA_TSTP_PID_SZFund: int
TORA_TSTP_PID_SZBond: int
TORA_TSTP_PID_SZStandard: int
TORA_TSTP_PID_SZRepurchase: int
TORA_TSTP_BKID_CCB: int
TORA_TSTP_BKID_ABC: int
TORA_TSTP_BKID_ICBC: int
TORA_TSTP_BKID_BOC: int
TORA_TSTP_BKID_CMB: int
TORA_TSTP_BKID_BC: int
TORA_TSTP_BKID_SPDB: int
TORA_TSTP_BKID_CIB: int
TORA_TSTP_BKID_CEB: int
TORA_TSTP_BKID_GDB: int
TORA_TSTP_BKID_NJCB: int
TORA_TSTP_BKID_SHCB: int
TORA_TSTP_BKID_CITICB: int
TORA_TSTP_BKID_HXB: int
TORA_TSTP_BKID_CMBC: int
TORA_TSTP_BKID_PACB: int
TORA_TSTP_BKID_NBCB: int
TORA_TSTP_OUT_Shou: int
TORA_TSTP_OUT_Gu: int
TORA_TSTP_OUT_Fen: int
TORA_TSTP_OUT_Zhang: int
TORA_TSTP_ICT_EID: int
TORA_TSTP_ICT_IDCard: int
TORA_TSTP_ICT_OfficerIDCard: int
TORA_TSTP_ICT_PoliceIDCard: int
TORA_TSTP_ICT_SoldierIDCard: int
TORA_TSTP_ICT_HouseholdRegister: int
TORA_TSTP_ICT_Passport: int
TORA_TSTP_ICT_TaiwanCompatriotIDCard: int
TORA_TSTP_ICT_HomeComingCard: int
TORA_TSTP_ICT_LicenseNo: int
TORA_TSTP_ICT_TaxNo: int
TORA_TSTP_ICT_HMMainlandTravelPermit: int
TORA_TSTP_ICT_TwMainlandTravelPermit: int
TORA_TSTP_ICT_DrivingLicense: int
TORA_TSTP_ICT_SocialID: int
TORA_TSTP_ICT_LocalID: int
TORA_TSTP_ICT_BusinessRegistration: int
TORA_TSTP_ICT_HKMCIDCard: int
TORA_TSTP_ICT_AccountsPermits: int
TORA_TSTP_ICT_OtherCard: int
TORA_TSTP_FAT_Normal: int
TORA_TSTP_FAT_Credit: int
TORA_TSTP_FAT_Derivatives: int
TORA_TSTP_D_Buy: int
TORA_TSTP_D_Sell: int
TORA_TSTP_D_ETFPur: int
TORA_TSTP_D_ETFRed: int
TORA_TSTP_D_IPO: int
TORA_TSTP_D_Repurchase: int
TORA_TSTP_D_ReverseRepur: int
TORA_TSTP_D_OeFundPur: int
TORA_TSTP_D_OeFundRed: int
TORA_TSTP_D_CollateralIn: int
TORA_TSTP_D_CollateralOut: int
TORA_TSTP_D_PledgeIn: int
TORA_TSTP_D_PledgeOut: int
TORA_TSTP_D_Rationed: int
TORA_TSTP_D_Split: int
TORA_TSTP_D_Merge: int
TORA_TSTP_D_MarginBuy: int
TORA_TSTP_D_ShortSell: int
TORA_TSTP_D_SellRepayment: int
TORA_TSTP_D_BuyRepayment: int
TORA_TSTP_D_SecurityRepay: int
TORA_TSTP_D_RemainTransfer: int
TORA_TSTP_D_BondConvertStock: int
TORA_TSTP_D_BondPutback: int
TORA_TSTP_BT_Gross: int
TORA_TSTP_BT_Net: int
TORA_TSTP_UTYPE_BrokerUser: int
TORA_TSTP_UTYPE_SuperUser: int
TORA_TSTP_UTYPE_Investor: int
TORA_TSTP_CC_TradeTouch: int
TORA_TSTP_CC_CancelTouch: int
TORA_TSTP_CC_TimeTouch: int
TORA_TSTP_CC_SegmentTouch: int
TORA_TSTP_CC_LastPriceGreaterThanStopPrice: int
TORA_TSTP_CC_LastPriceLesserThanStopPrice: int
TORA_TSTP_CC_AskPriceGreaterEqualStopPrice: int
TORA_TSTP_CC_AskPriceLesserEqualStopPrice: int
TORA_TSTP_CC_BidPriceGreaterEqualStopPrice: int
TORA_TSTP_CC_BidPriceLesserEqualStopPrice: int
TORA_TSTP_ETFCTSTAT_Forbidden: int
TORA_TSTP_ETFCTSTAT_Allow: int
TORA_TSTP_ETFCTSTAT_Force: int
TORA_TSTP_ETFCTSTAT_CBAllow: int
TORA_TSTP_ETFCTSTAT_CBForce: int
TORA_TSTP_OPRTSRC_DBCommand: int
TORA_TSTP_OPRTSRC_SyncAPI: int
TORA_TSTP_OPERW_Telephone: int
TORA_TSTP_OPERW_OTC: int
TORA_TSTP_OPERW_MobileClient: int
TORA_TSTP_OPERW_PCClient: int
TORA_TSTP_OPERW_TY: int
TORA_TSTP_OPT_AnyPrice: int
TORA_TSTP_OPT_LimitPrice: int
TORA_TSTP_OPT_BestPrice: int
TORA_TSTP_OPT_LastPrice: int
TORA_TSTP_OPT_AskPrice1: int
TORA_TSTP_OPT_BidPrice1: int
TORA_TSTP_OPT_Relative: int
TORA_TSTP_OPT_FiveLevelPrice: int
TORA_TSTP_OPT_HomeBestPrice: int
TORA_TSTP_OVT_CustomVol: int
TORA_TSTP_OVT_RelativeVol: int
TORA_TSTP_TC_IOC: int
TORA_TSTP_TC_GFS: int
TORA_TSTP_TC_GFD: int
TORA_TSTP_TC_GTD: int
TORA_TSTP_TC_GTC: int
TORA_TSTP_TC_GFA: int
TORA_TSTP_VC_AV: int
TORA_TSTP_VC_MV: int
TORA_TSTP_VC_CV: int
TORA_TSTP_FCC_NotForceClose: int
TORA_TSTP_FCC_LackDeposit: int
TORA_TSTP_FCC_ClientOverPositionLimit: int
TORA_TSTP_FCC_MemberOverPositionLimit: int
TORA_TSTP_FCC_NotMultiple: int
TORA_TSTP_FCC_Violation: int
TORA_TSTP_FCC_Other: int
TORA_TSTP_EOT_Review: int
TORA_TSTP_EOT_Cancel: int
TORA_TSTP_EOT_Limit: int
TORA_TSTP_EOT_FRC: int
TORA_TSTP_EOT_FRL: int
TORA_TSTP_EOT_BP: int
TORA_TSTP_EOT_HP: int
TORA_TSTP_EOT_FAK: int
TORA_TSTP_EOT_FOK: int
TORA_TSTP_TRNSD_In: int
TORA_TSTP_TRNSD_Out: int
TORA_TSTP_TRNSD_MoveIn: int
TORA_TSTP_TRNSD_MoveOut: int
TORA_TSTP_TRNSD_Freeze: int
TORA_TSTP_TRNSD_UnFreeze: int
TORA_TSTP_TRNSD_StockToBank: int
TORA_TSTP_TRNSD_BankToStock: int
TORA_TSTP_CLTD_CollateralIn: int
TORA_TSTP_CLTD_CollateralOut: int
TORA_TSTP_TRANST_TranferHandling: int
TORA_TSTP_TRANST_TransferSuccess: int
TORA_TSTP_TRANST_TransferFail: int
TORA_TSTP_TRANST_RepealHandling: int
TORA_TSTP_TRANST_RepealSuccess: int
TORA_TSTP_TRANST_RepealFail: int
TORA_TSTP_TRANST_ExternalAccepted: int
TORA_TSTP_TPT_ALL: int
TORA_TSTP_TPT_History: int
TORA_TSTP_TPT_TodayBS: int
TORA_TSTP_TPT_TodayPR: int
TORA_TSTP_OST_AllTraded: int
TORA_TSTP_OST_PartTradedQueueing: int
TORA_TSTP_OST_PartTradedNotQueueing: int
TORA_TSTP_OST_NoTradeQueueing: int
TORA_TSTP_OST_NoTradeNotQueueing: int
TORA_TSTP_OST_Canceled: int
TORA_TSTP_OST_Unknown: int
TORA_TSTP_OST_NotTouched: int
TORA_TSTP_OST_Touched: int
TORA_TSTP_OST_Cached: int
TORA_TSTP_COST_Initial: int
TORA_TSTP_COST_NotTouched: int
TORA_TSTP_COST_Touched: int
TORA_TSTP_COST_Finished: int
TORA_TSTP_COST_Cancel: int
TORA_TSTP_COST_Failed: int
TORA_TSTP_OSS_UnSubmit: int
TORA_TSTP_OSS_InsertSubmitted: int
TORA_TSTP_OSS_CancelSubmitted: int
TORA_TSTP_OSS_ModifySubmitted: int
TORA_TSTP_OSS_Accepted: int
TORA_TSTP_OSS_InsertRejected: int
TORA_TSTP_OSS_CancelRejected: int
TORA_TSTP_OSS_ModifyRejected: int
TORA_TSTP_ORDT_Normal: int
TORA_TSTP_ORDT_DeriveFromQuote: int
TORA_TSTP_ORDT_DeriveFromCombination: int
TORA_TSTP_ORDT_Combination: int
TORA_TSTP_ORDT_ConditionalOrder: int
TORA_TSTP_ORDT_Swap: int
TORA_TSTP_OF_Open: int
TORA_TSTP_OF_Close: int
TORA_TSTP_OF_ForceClose: int
TORA_TSTP_OF_CloseToday: int
TORA_TSTP_OF_CloseYesterday: int
TORA_TSTP_OF_ForceOff: int
TORA_TSTP_OF_LocalForceClose: int
TORA_TSTP_HF_Speculation: int
TORA_TSTP_HF_Arbitrage: int
TORA_TSTP_HF_Hedge: int
TORA_TSTP_HF_Covered: int
TORA_TSTP_AF_Delete: int
TORA_TSTP_AF_Modify: int
TORA_TSTP_AF_ForceDelete: int
TORA_TSTP_OAS_Submitted: int
TORA_TSTP_OAS_Accepted: int
TORA_TSTP_OAS_Rejected: int
TORA_TSTP_OAS_Cached: int
TORA_TSTP_CIDT_Unknown: int
TORA_TSTP_CIDT_Speculation: int
TORA_TSTP_CIDT_Arbitrage: int
TORA_TSTP_CIDT_Hedge: int
TORA_TSTP_CIDT_Normal: int
TORA_TSTP_CIDT_Credit: int
TORA_TSTP_CIDT_Derivatives: int
TORA_TSTP_BC_Buy: int
TORA_TSTP_BC_Sell: int
TORA_TSTP_BC_ETFPur: int
TORA_TSTP_BC_ETFRed: int
TORA_TSTP_BC_Repurchase: int
TORA_TSTP_BC_ReverseRepur: int
TORA_TSTP_BC_Rationed: int
TORA_TSTP_BC_CustodyTransfer: int
TORA_TSTP_BC_BuyOpen: int
TORA_TSTP_BC_BuyClose: int
TORA_TSTP_BC_SellOpen: int
TORA_TSTP_BC_SellClose: int
TORA_TSTP_BC_CoveredOpen: int
TORA_TSTP_BC_CoveredClose: int
TORA_TSTP_BC_ExecOrder: int
TORA_TSTP_BC_AutoExecOrder: int
TORA_TSTP_CPT_Normal: int
TORA_TSTP_CPT_Special: int
TORA_TSTP_FID_NAN: int
TORA_TSTP_FID_SessionManager: int
TORA_TSTP_FID_UserManager: int
TORA_TSTP_FID_OrderInsert: int
TORA_TSTP_FID_OrderAction: int
TORA_TSTP_FID_AdjustTradingRight: int
TORA_TSTP_FID_MoveFund: int
TORA_TSTP_FID_AddFund: int
TORA_TSTP_FID_SubFund: int
TORA_TSTP_FID_ForceFreezeFund: int
TORA_TSTP_FID_ForceUnFreezeFund: int
TORA_TSTP_FID_AddPosition: int
TORA_TSTP_FID_SubPosition: int
TORA_TSTP_FID_RepealFund: int
TORA_TSTP_FID_RepealPosition: int
TORA_TSTP_FID_CollateralInJZ: int
TORA_TSTP_FID_AdjustTradingFee: int
TORA_TSTP_FID_AdjustSpecPrivilege: int
TORA_TSTP_FID_AdjustShareholderAssociation: int
TORA_TSTP_FID_AdjustSecurity: int
TORA_TSTP_FID_MovePosition: int
TORA_TSTP_FID_AdjustShareholderParam: int
TORA_TSTP_FID_CondOrderInsert: int
TORA_TSTP_FID_CondOrderAction: int
TORA_TSTP_FID_QryCondOrder: int
TORA_TSTP_FID_CondParamAdjust: int
TORA_TSTP_FID_UserRoleManage: int
TORA_TSTP_FID_TradingFeeTemplateManage: int
TORA_TSTP_FID_TradingRightTemplateManage: int
TORA_TSTP_FID_SecurityPriorAuthManage: int
TORA_TSTP_FID_PosiParamManage: int
TORA_TSTP_FID_OrderLocalSeqPrefixAdjust: int
TORA_TSTP_FID_TraderManage: int
TORA_TSTP_FID_IPOManage: int
TORA_TSTP_FID_AppRunManage: int
TORA_TSTP_FID_MarketStatusManage: int
TORA_TSTP_FID_PlatformStatusManage: int
TORA_TSTP_FID_QryTradingAccount: int
TORA_TSTP_FID_QryPositon: int
TORA_TSTP_FID_QryShareholderAccount: int
TORA_TSTP_FID_QryOrder: int
TORA_TSTP_FID_QryTrade: int
TORA_TSTP_FID_QryFundSerial: int
TORA_TSTP_FID_QryPositionSerial: int
TORA_TSTP_FID_DumpTradingAccount: int
TORA_TSTP_FID_DumpPositon: int
TORA_TSTP_FID_DumpShareholderAccount: int
TORA_TSTP_FID_DumpOrder: int
TORA_TSTP_FID_DumpTrade: int
TORA_TSTP_FID_DumpFundSerial: int
TORA_TSTP_FID_DumpPositionSerial: int
TORA_TSTP_FID_UploadTradeData: int
TORA_TSTP_FID_ReviewFundAdjust: int
TORA_TSTP_FID_ReviewPositionAdjust: int
TORA_TSTP_FID_RecordOperateLog: int
TORA_TSTP_FID_TerminalInfoManage: int
TORA_TSTP_FID_QryTradingRight: int
TORA_TSTP_FID_DesignationRegistration: int
TORA_TSTP_FID_CustodyTransfer: int
TORA_TSTP_FID_ForceDelete: int
TORA_TSTP_FID_RiskMgr: int
TORA_TSTP_FID_ReviewUserIPLimitAdjust: int
TORA_TSTP_FID_AdjustUserIPLimit: int
TORA_TSTP_FID_AdjustSystemParam: int
TORA_TSTP_FID_DepartmentInfoManage: int
TORA_TSTP_FID_IPONumberMatchManage: int
TORA_TSTP_FID_CustomerInfoManage: int
TORA_TSTP_FID_QryTradeEvent: int
TORA_TSTP_FID_ExchRtnSeqManage: int
TORA_TSTP_FID_TransferFund: int
TORA_TSTP_STP_COMMON: int
TORA_TSTP_STP_SHAShares: int
TORA_TSTP_STP_SHSingleMarketStockETF: int
TORA_TSTP_STP_SHSingleMarketBondETF: int
TORA_TSTP_STP_SHGoldETF: int
TORA_TSTP_STP_SHTradableMonetaryFund: int
TORA_TSTP_STP_SHBondNation: int
TORA_TSTP_STP_SHBondCorporation: int
TORA_TSTP_STP_SHBondCompany: int
TORA_TSTP_STP_SHBondConversion: int
TORA_TSTP_STP_SHBondSeparation: int
TORA_TSTP_STP_SHASharesOption: int
TORA_TSTP_STP_SHETFOption: int
TORA_TSTP_STP_SHAllotment: int
TORA_TSTP_STP_SHDistributeDebt: int
TORA_TSTP_STP_SHStandard: int
TORA_TSTP_STP_SHRepo: int
TORA_TSTP_STP_SHCEFund: int
TORA_TSTP_STP_SHOEFund: int
TORA_TSTP_STP_SHCrossMarketStockETF: int
TORA_TSTP_STP_SHCrossBorderETF: int
TORA_TSTP_STP_SHMontherStructFund: int
TORA_TSTP_STP_SHSubStructFund: int
TORA_TSTP_STP_SHRealTimeMonetaryFund: int
TORA_TSTP_STP_SHExchangeableBond: int
TORA_TSTP_STP_SHLOF: int
TORA_TSTP_STP_SZMainAShares: int
TORA_TSTP_STP_SZSME: int
TORA_TSTP_STP_SZBondNation: int
TORA_TSTP_STP_SZBondCorporation: int
TORA_TSTP_STP_SZBondCompany: int
TORA_TSTP_STP_SZBondConversion: int
TORA_TSTP_STP_SZBondSeparation: int
TORA_TSTP_STP_SZASharesOption: int
TORA_TSTP_STP_SZETFOption: int
TORA_TSTP_STP_SZCrossBorderETF: int
TORA_TSTP_STP_SZGoldETF: int
TORA_TSTP_STP_SZCashBondETF: int
TORA_TSTP_STP_SZSingleMarketStockETF: int
TORA_TSTP_STP_SZSingleMarketBondETF: int
TORA_TSTP_STP_SZMonetaryFundETF: int
TORA_TSTP_STP_SZGEM: int
TORA_TSTP_STP_SZAllotment: int
TORA_TSTP_STP_SZDistributeDebt: int
TORA_TSTP_STP_SZStandard: int
TORA_TSTP_STP_SZRepo: int
TORA_TSTP_STP_SZCEFund: int
TORA_TSTP_STP_SZOEFund: int
TORA_TSTP_STP_SZCrossBorderOEFund: int
TORA_TSTP_STP_SZCrossMarketStockETF: int
TORA_TSTP_STP_SZLOF: int
TORA_TSTP_STP_SZCrossBorderLOF: int
TORA_TSTP_STP_SZMontherStructFund: int
TORA_TSTP_STP_SZSubStructFund: int
TORA_TSTP_STP_SZMontherCrossBorderStructFund: int
TORA_TSTP_STP_SZSubCrossBorderStructFund: int
TORA_TSTP_STP_SZExchangeableBond: int
TORA_TSTP_STP_SZGEMConversionBond: int
TORA_TSTP_EF_ToBeContinued: int
TORA_TSTP_EF_BatchEnd: int
TORA_TSTP_EF_Completed: int
TORA_TSTP_EF_NOP: int
TORA_TSTP_MKD_COMMON: int
TORA_TSTP_MKD_SHA: int
TORA_TSTP_MKD_SZA: int
TORA_TSTP_MKD_SHB: int
TORA_TSTP_MKD_SZB: int
TORA_TSTP_MKD_SZThreeA: int
TORA_TSTP_MKD_SZThreeB: int
TORA_TSTP_MKD_Foreign: int
TORA_TSTP_LACT_UserID: int
TORA_TSTP_LACT_AccountID: int
TORA_TSTP_LACT_SHAStock: int
TORA_TSTP_LACT_SZAStock: int
TORA_TSTP_LACT_SHBStock: int
TORA_TSTP_LACT_SZBStock: int
TORA_TSTP_LACT_ThreeNewBoardA: int
TORA_TSTP_LACT_ThreeNewBoardB: int
TORA_TSTP_LACT_HKStock: int
TORA_TSTP_MST_UnKnown: int
TORA_TSTP_MST_BeforeTrading: int
TORA_TSTP_MST_Continous: int
TORA_TSTP_MST_Closed: int
TORA_TSTP_MST_OpenCallAuction: int
TORA_TSTP_ARM_Single: int
TORA_TSTP_ARM_Group: int
TORA_TSTP_DT_Register: int
TORA_TSTP_DT_Cancel: int
TORA_TSTP_CT_Register: int
TORA_TSTP_CT_Cancel: int
TORA_TSTP_PCBT_None: int
TORA_TSTP_PCBT_Other: int
TORA_TSTP_PCBT_SHDelisting: int
TORA_TSTP_PCBT_ST: int
TORA_TSTP_PCBT_GEM: int
TORA_TSTP_PCBT_StructFund: int
TORA_TSTP_PCBT_BondQualified: int
TORA_TSTP_PCBT_SuspendBond: int
TORA_TSTP_PCBT_Repurchase: int
TORA_TSTP_PCBT_ReverseRepur: int
TORA_TSTP_PCBT_SZDelisting: int
TORA_TSTP_PCBT_Stock: int
TORA_TSTP_PCBT_CreditStock: int
TORA_TSTP_PCPF_None: int
TORA_TSTP_PCPF_AnywayPass: int
TORA_TSTP_PCPF_MatchPass: int
TORA_TSTP_PCPF_SelectPass: int
TORA_TSTP_PCPF_ProfInvestorPass: int
TORA_TSTP_RLV_Lowest: int
TORA_TSTP_RLV_Conservative: int
TORA_TSTP_RLV_Cautious: int
TORA_TSTP_RLV_Steady: int
TORA_TSTP_RLV_Positive: int
TORA_TSTP_RLV_Aggressive: int
TORA_TSTP_PIT_NotProf: int
TORA_TSTP_PIT_OCInstiPro: int
TORA_TSTP_PIT_InstiPro: int
TORA_TSTP_PIT_PersonPro: int
TORA_TSTP_PIT_ConfirmInstiPro: int
TORA_TSTP_PIT_ConfirmPersonPro: int
TORA_TSTP_LOT_Market: int
TORA_TSTP_LOT_Limit: int
TORA_TSTP_LOT_HomeBest: int
TORA_TSTP_LSD_Buy: int
TORA_TSTP_LSD_Sell: int
TORA_TSTP_LSD_Borrow: int
TORA_TSTP_LSD_Lend: int
TORA_TSTP_ECT_Fill: int
TORA_TSTP_ECT_Cancel: int
TORA_TSTP_CCT_None: int
TORA_TSTP_CCT_SelfDeal: int
TORA_TSTP_MST_TCP: int
TORA_TSTP_MST_UDP: int
TORA_TSTP_MST_MCAST: int
TORA_TSTP_MSST_PreOpen: int
TORA_TSTP_MSST_CallAuction: int
TORA_TSTP_MSST_Continous: int
TORA_TSTP_MSST_Pause: int
TORA_TSTP_MSST_Suspend: int
TORA_TSTP_MSST_LongSuspend: int
TORA_TSTP_MSST_UndulationInt: int
TORA_TSTP_MSST_CircuitBreak: int
TORA_TSTP_MSST_CircuitBreakU: int
TORA_TSTP_MSST_Close: int
TORA_TSTP_MSST_Other: int
TORA_TSTP_MSST_CloseCallAuction: int
TORA_TSTP_FOCS_Init: int
TORA_TSTP_FOCS_Reviewed: int
TORA_TSTP_FOCS_Failed: int
TORA_TSTP_SPT_MaxBuyLimit: int
TORA_TSTP_SPT_MaxSellLimit: int
TORA_TSTP_SPT_LargeBuyLimitRatio: int
TORA_TSTP_SPT_LargeSelLimitRatio: int
TORA_TSTP_SPT_RiskWarnBoardLimitVol: int
TORA_TSTP_SPT_SeriesDecInterval: int
TORA_TSTP_SPT_SeriesLimitPerUnit: int
TORA_TSTP_SPT_ClosePriceScopeRatio: int
TORA_TSTP_SPT_OpenDateLimit: int
TORA_TSTP_SPT_LimitBoardShamRatio: int
TORA_TSTP_SPT_CancelOrderRatio: int
def set_null(v: int)->None:
    ...
def set_null(v: float)->None:
    ...
def set_null(v: int)->None:
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
def is_null(v: int)->bool:
    ...
def is_null(v: int)->bool:
    ...
def is_null(v: int)->bool:
    ...
def is_null(v: str)->bool:
    ...

