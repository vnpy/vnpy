# noinspection PyUnresolvedReferences
from typing import *
# noinspection PyUnresolvedReferences
from enum import Enum


class CThostFtdcDisseminationField:
    SequenceSeries: int
    SequenceNo: int
    
    ...
    ...
class CThostFtdcReqUserLoginField:
    TradingDay: str
    BrokerID: str
    UserID: str
    Password: str
    UserProductInfo: str
    InterfaceProductInfo: str
    ProtocolInfo: str
    MacAddress: str
    OneTimePassword: str
    ClientIPAddress: str
    LoginRemark: str
    ClientIPPort: int
    
    ...
    ...
class CThostFtdcRspUserLoginField:
    TradingDay: str
    LoginTime: str
    BrokerID: str
    UserID: str
    SystemName: str
    FrontID: int
    SessionID: int
    MaxOrderRef: str
    SHFETime: str
    DCETime: str
    CZCETime: str
    FFEXTime: str
    INETime: str
    
    ...
    ...
class CThostFtdcUserLogoutField:
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcForceUserLogoutField:
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcReqAuthenticateField:
    BrokerID: str
    UserID: str
    UserProductInfo: str
    AuthCode: str
    AppID: str
    
    ...
    ...
class CThostFtdcRspAuthenticateField:
    BrokerID: str
    UserID: str
    UserProductInfo: str
    AppID: str
    AppType: int
    
    ...
    ...
class CThostFtdcAuthenticationInfoField:
    BrokerID: str
    UserID: str
    UserProductInfo: str
    AuthInfo: str
    IsResult: int
    AppID: str
    AppType: int
    
    ...
    ...
class CThostFtdcRspUserLogin2Field:
    TradingDay: str
    LoginTime: str
    BrokerID: str
    UserID: str
    SystemName: str
    FrontID: int
    SessionID: int
    MaxOrderRef: str
    SHFETime: str
    DCETime: str
    CZCETime: str
    FFEXTime: str
    INETime: str
    RandomString: str
    
    ...
    ...
class CThostFtdcTransferHeaderField:
    Version: str
    TradeCode: str
    TradeDate: str
    TradeTime: str
    TradeSerial: str
    FutureID: str
    BankID: str
    BankBrchID: str
    OperNo: str
    DeviceID: str
    RecordNum: str
    SessionID: int
    RequestID: int
    
    ...
    ...
class CThostFtdcTransferBankToFutureReqField:
    FutureAccount: str
    FuturePwdFlag: int
    FutureAccPwd: str
    TradeAmt: float
    CustFee: float
    CurrencyCode: str
    
    ...
    ...
class CThostFtdcTransferBankToFutureRspField:
    RetCode: str
    RetInfo: str
    FutureAccount: str
    TradeAmt: float
    CustFee: float
    CurrencyCode: str
    
    ...
    ...
class CThostFtdcTransferFutureToBankReqField:
    FutureAccount: str
    FuturePwdFlag: int
    FutureAccPwd: str
    TradeAmt: float
    CustFee: float
    CurrencyCode: str
    
    ...
    ...
class CThostFtdcTransferFutureToBankRspField:
    RetCode: str
    RetInfo: str
    FutureAccount: str
    TradeAmt: float
    CustFee: float
    CurrencyCode: str
    
    ...
    ...
class CThostFtdcTransferQryBankReqField:
    FutureAccount: str
    FuturePwdFlag: int
    FutureAccPwd: str
    CurrencyCode: str
    
    ...
    ...
class CThostFtdcTransferQryBankRspField:
    RetCode: str
    RetInfo: str
    FutureAccount: str
    TradeAmt: float
    UseAmt: float
    FetchAmt: float
    CurrencyCode: str
    
    ...
    ...
class CThostFtdcTransferQryDetailReqField:
    FutureAccount: str
    
    ...
    ...
class CThostFtdcTransferQryDetailRspField:
    TradeDate: str
    TradeTime: str
    TradeCode: str
    FutureSerial: int
    FutureID: str
    FutureAccount: str
    BankSerial: int
    BankID: str
    BankBrchID: str
    BankAccount: str
    CertCode: str
    CurrencyCode: str
    TxAmount: float
    Flag: int
    
    ...
    ...
class CThostFtdcRspInfoField:
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcExchangeField:
    ExchangeID: str
    ExchangeName: str
    ExchangeProperty: int
    
    ...
    ...
class CThostFtdcProductField:
    ProductID: str
    ProductName: str
    ExchangeID: str
    ProductClass: int
    VolumeMultiple: int
    PriceTick: float
    MaxMarketOrderVolume: int
    MinMarketOrderVolume: int
    MaxLimitOrderVolume: int
    MinLimitOrderVolume: int
    PositionType: int
    PositionDateType: int
    CloseDealType: int
    TradeCurrencyID: str
    MortgageFundUseRange: int
    ExchangeProductID: str
    UnderlyingMultiple: float
    
    ...
    ...
class CThostFtdcInstrumentField:
    InstrumentID: str
    ExchangeID: str
    InstrumentName: str
    ExchangeInstID: str
    ProductID: str
    ProductClass: int
    DeliveryYear: int
    DeliveryMonth: int
    MaxMarketOrderVolume: int
    MinMarketOrderVolume: int
    MaxLimitOrderVolume: int
    MinLimitOrderVolume: int
    VolumeMultiple: int
    PriceTick: float
    CreateDate: str
    OpenDate: str
    ExpireDate: str
    StartDelivDate: str
    EndDelivDate: str
    InstLifePhase: int
    IsTrading: int
    PositionType: int
    PositionDateType: int
    LongMarginRatio: float
    ShortMarginRatio: float
    MaxMarginSideAlgorithm: int
    UnderlyingInstrID: str
    StrikePrice: float
    OptionsType: int
    UnderlyingMultiple: float
    CombinationType: int
    
    ...
    ...
class CThostFtdcBrokerField:
    BrokerID: str
    BrokerAbbr: str
    BrokerName: str
    IsActive: int
    
    ...
    ...
class CThostFtdcTraderField:
    ExchangeID: str
    TraderID: str
    ParticipantID: str
    Password: str
    InstallCount: int
    BrokerID: str
    
    ...
    ...
class CThostFtdcInvestorField:
    InvestorID: str
    BrokerID: str
    InvestorGroupID: str
    InvestorName: str
    IdentifiedCardType: int
    IdentifiedCardNo: str
    IsActive: int
    Telephone: str
    Address: str
    OpenDate: str
    Mobile: str
    CommModelID: str
    MarginModelID: str
    
    ...
    ...
class CThostFtdcTradingCodeField:
    InvestorID: str
    BrokerID: str
    ExchangeID: str
    ClientID: str
    IsActive: int
    ClientIDType: int
    BranchID: str
    BizType: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcPartBrokerField:
    BrokerID: str
    ExchangeID: str
    ParticipantID: str
    IsActive: int
    
    ...
    ...
class CThostFtdcSuperUserField:
    UserID: str
    UserName: str
    Password: str
    IsActive: int
    
    ...
    ...
class CThostFtdcSuperUserFunctionField:
    UserID: str
    FunctionCode: int
    
    ...
    ...
class CThostFtdcInvestorGroupField:
    BrokerID: str
    InvestorGroupID: str
    InvestorGroupName: str
    
    ...
    ...
class CThostFtdcTradingAccountField:
    BrokerID: str
    AccountID: str
    PreMortgage: float
    PreCredit: float
    PreDeposit: float
    PreBalance: float
    PreMargin: float
    InterestBase: float
    Interest: float
    Deposit: float
    Withdraw: float
    FrozenMargin: float
    FrozenCash: float
    FrozenCommission: float
    CurrMargin: float
    CashIn: float
    Commission: float
    CloseProfit: float
    PositionProfit: float
    Balance: float
    Available: float
    WithdrawQuota: float
    Reserve: float
    TradingDay: str
    SettlementID: int
    Credit: float
    Mortgage: float
    ExchangeMargin: float
    DeliveryMargin: float
    ExchangeDeliveryMargin: float
    ReserveBalance: float
    CurrencyID: str
    PreFundMortgageIn: float
    PreFundMortgageOut: float
    FundMortgageIn: float
    FundMortgageOut: float
    FundMortgageAvailable: float
    MortgageableFund: float
    SpecProductMargin: float
    SpecProductFrozenMargin: float
    SpecProductCommission: float
    SpecProductFrozenCommission: float
    SpecProductPositionProfit: float
    SpecProductCloseProfit: float
    SpecProductPositionProfitByAlg: float
    SpecProductExchangeMargin: float
    BizType: int
    FrozenSwap: float
    RemainSwap: float
    
    ...
    ...
class CThostFtdcInvestorPositionField:
    InstrumentID: str
    BrokerID: str
    InvestorID: str
    PosiDirection: int
    HedgeFlag: int
    PositionDate: int
    YdPosition: int
    Position: int
    LongFrozen: int
    ShortFrozen: int
    LongFrozenAmount: float
    ShortFrozenAmount: float
    OpenVolume: int
    CloseVolume: int
    OpenAmount: float
    CloseAmount: float
    PositionCost: float
    PreMargin: float
    UseMargin: float
    FrozenMargin: float
    FrozenCash: float
    FrozenCommission: float
    CashIn: float
    Commission: float
    CloseProfit: float
    PositionProfit: float
    PreSettlementPrice: float
    SettlementPrice: float
    TradingDay: str
    SettlementID: int
    OpenCost: float
    ExchangeMargin: float
    CombPosition: int
    CombLongFrozen: int
    CombShortFrozen: int
    CloseProfitByDate: float
    CloseProfitByTrade: float
    TodayPosition: int
    MarginRateByMoney: float
    MarginRateByVolume: float
    StrikeFrozen: int
    StrikeFrozenAmount: float
    AbandonFrozen: int
    ExchangeID: str
    YdStrikeFrozen: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcInstrumentMarginRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    HedgeFlag: int
    LongMarginRatioByMoney: float
    LongMarginRatioByVolume: float
    ShortMarginRatioByMoney: float
    ShortMarginRatioByVolume: float
    IsRelative: int
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcInstrumentCommissionRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    OpenRatioByMoney: float
    OpenRatioByVolume: float
    CloseRatioByMoney: float
    CloseRatioByVolume: float
    CloseTodayRatioByMoney: float
    CloseTodayRatioByVolume: float
    ExchangeID: str
    BizType: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcDepthMarketDataField:
    TradingDay: str
    InstrumentID: str
    ExchangeID: str
    ExchangeInstID: str
    LastPrice: float
    PreSettlementPrice: float
    PreClosePrice: float
    PreOpenInterest: float
    OpenPrice: float
    HighestPrice: float
    LowestPrice: float
    Volume: int
    Turnover: float
    OpenInterest: float
    ClosePrice: float
    SettlementPrice: float
    UpperLimitPrice: float
    LowerLimitPrice: float
    PreDelta: float
    CurrDelta: float
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
    AveragePrice: float
    ActionDay: str
    
    ...
    ...
class CThostFtdcInstrumentTradingRightField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    TradingRight: int
    
    ...
    ...
class CThostFtdcBrokerUserField:
    BrokerID: str
    UserID: str
    UserName: str
    UserType: int
    IsActive: int
    IsUsingOTP: int
    IsAuthForce: int
    
    ...
    ...
class CThostFtdcBrokerUserPasswordField:
    BrokerID: str
    UserID: str
    Password: str
    LastUpdateTime: str
    LastLoginTime: str
    ExpireDate: str
    WeakExpireDate: str
    
    ...
    ...
class CThostFtdcBrokerUserFunctionField:
    BrokerID: str
    UserID: str
    BrokerFunctionCode: int
    
    ...
    ...
class CThostFtdcTraderOfferField:
    ExchangeID: str
    TraderID: str
    ParticipantID: str
    Password: str
    InstallID: int
    OrderLocalID: str
    TraderConnectStatus: int
    ConnectRequestDate: str
    ConnectRequestTime: str
    LastReportDate: str
    LastReportTime: str
    ConnectDate: str
    ConnectTime: str
    StartDate: str
    StartTime: str
    TradingDay: str
    BrokerID: str
    MaxTradeID: str
    MaxOrderMessageReference: str
    
    ...
    ...
class CThostFtdcSettlementInfoField:
    TradingDay: str
    SettlementID: int
    BrokerID: str
    InvestorID: str
    SequenceNo: int
    Content: str
    AccountID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcInstrumentMarginRateAdjustField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    HedgeFlag: int
    LongMarginRatioByMoney: float
    LongMarginRatioByVolume: float
    ShortMarginRatioByMoney: float
    ShortMarginRatioByVolume: float
    IsRelative: int
    
    ...
    ...
class CThostFtdcExchangeMarginRateField:
    BrokerID: str
    InstrumentID: str
    HedgeFlag: int
    LongMarginRatioByMoney: float
    LongMarginRatioByVolume: float
    ShortMarginRatioByMoney: float
    ShortMarginRatioByVolume: float
    ExchangeID: str
    
    ...
    ...
class CThostFtdcExchangeMarginRateAdjustField:
    BrokerID: str
    InstrumentID: str
    HedgeFlag: int
    LongMarginRatioByMoney: float
    LongMarginRatioByVolume: float
    ShortMarginRatioByMoney: float
    ShortMarginRatioByVolume: float
    ExchLongMarginRatioByMoney: float
    ExchLongMarginRatioByVolume: float
    ExchShortMarginRatioByMoney: float
    ExchShortMarginRatioByVolume: float
    NoLongMarginRatioByMoney: float
    NoLongMarginRatioByVolume: float
    NoShortMarginRatioByMoney: float
    NoShortMarginRatioByVolume: float
    
    ...
    ...
class CThostFtdcExchangeRateField:
    BrokerID: str
    FromCurrencyID: str
    FromCurrencyUnit: float
    ToCurrencyID: str
    ExchangeRate: float
    
    ...
    ...
class CThostFtdcSettlementRefField:
    TradingDay: str
    SettlementID: int
    
    ...
    ...
class CThostFtdcCurrentTimeField:
    CurrDate: str
    CurrTime: str
    CurrMillisec: int
    ActionDay: str
    
    ...
    ...
class CThostFtdcCommPhaseField:
    TradingDay: str
    CommPhaseNo: int
    SystemID: str
    
    ...
    ...
class CThostFtdcLoginInfoField:
    FrontID: int
    SessionID: int
    BrokerID: str
    UserID: str
    LoginDate: str
    LoginTime: str
    IPAddress: str
    UserProductInfo: str
    InterfaceProductInfo: str
    ProtocolInfo: str
    SystemName: str
    PasswordDeprecated: str
    MaxOrderRef: str
    SHFETime: str
    DCETime: str
    CZCETime: str
    FFEXTime: str
    MacAddress: str
    OneTimePassword: str
    INETime: str
    IsQryControl: int
    LoginRemark: str
    Password: str
    
    ...
    ...
class CThostFtdcLogoutAllField:
    FrontID: int
    SessionID: int
    SystemName: str
    
    ...
    ...
class CThostFtdcFrontStatusField:
    FrontID: int
    LastReportDate: str
    LastReportTime: str
    IsActive: int
    
    ...
    ...
class CThostFtdcUserPasswordUpdateField:
    BrokerID: str
    UserID: str
    OldPassword: str
    NewPassword: str
    
    ...
    ...
class CThostFtdcInputOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OrderRef: str
    UserID: str
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    GTDDate: str
    VolumeCondition: int
    MinVolume: int
    ContingentCondition: int
    StopPrice: float
    ForceCloseReason: int
    IsAutoSuspend: int
    BusinessUnit: str
    RequestID: int
    UserForceClose: int
    IsSwapOrder: int
    ExchangeID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    ClientID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OrderRef: str
    UserID: str
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    GTDDate: str
    VolumeCondition: int
    MinVolume: int
    ContingentCondition: int
    StopPrice: float
    ForceCloseReason: int
    IsAutoSuspend: int
    BusinessUnit: str
    RequestID: int
    OrderLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    OrderSubmitStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    OrderSysID: str
    OrderSource: int
    OrderStatus: int
    OrderType: int
    VolumeTraded: int
    VolumeTotal: int
    InsertDate: str
    InsertTime: str
    ActiveTime: str
    SuspendTime: str
    UpdateTime: str
    CancelTime: str
    ActiveTraderID: str
    ClearingPartID: str
    SequenceNo: int
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    UserForceClose: int
    ActiveUserID: str
    BrokerOrderSeq: int
    RelativeOrderSysID: str
    ZCETotalTradedVolume: int
    IsSwapOrder: int
    BranchID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcExchangeOrderField:
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    GTDDate: str
    VolumeCondition: int
    MinVolume: int
    ContingentCondition: int
    StopPrice: float
    ForceCloseReason: int
    IsAutoSuspend: int
    BusinessUnit: str
    RequestID: int
    OrderLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    OrderSubmitStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    OrderSysID: str
    OrderSource: int
    OrderStatus: int
    OrderType: int
    VolumeTraded: int
    VolumeTotal: int
    InsertDate: str
    InsertTime: str
    ActiveTime: str
    SuspendTime: str
    UpdateTime: str
    CancelTime: str
    ActiveTraderID: str
    ClearingPartID: str
    SequenceNo: int
    BranchID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcExchangeOrderInsertErrorField:
    ExchangeID: str
    ParticipantID: str
    TraderID: str
    InstallID: int
    OrderLocalID: str
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcInputOrderActionField:
    BrokerID: str
    InvestorID: str
    OrderActionRef: int
    OrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OrderSysID: str
    ActionFlag: int
    LimitPrice: float
    VolumeChange: int
    UserID: str
    InstrumentID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcOrderActionField:
    BrokerID: str
    InvestorID: str
    OrderActionRef: int
    OrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OrderSysID: str
    ActionFlag: int
    LimitPrice: float
    VolumeChange: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    OrderLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    StatusMsg: str
    InstrumentID: str
    BranchID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcExchangeOrderActionField:
    ExchangeID: str
    OrderSysID: str
    ActionFlag: int
    LimitPrice: float
    VolumeChange: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    OrderLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    BranchID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcExchangeOrderActionErrorField:
    ExchangeID: str
    OrderSysID: str
    TraderID: str
    InstallID: int
    OrderLocalID: str
    ActionLocalID: str
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcExchangeTradeField:
    ExchangeID: str
    TradeID: str
    Direction: int
    OrderSysID: str
    ParticipantID: str
    ClientID: str
    TradingRole: int
    ExchangeInstID: str
    OffsetFlag: int
    HedgeFlag: int
    Price: float
    Volume: int
    TradeDate: str
    TradeTime: str
    TradeType: int
    PriceSource: int
    TraderID: str
    OrderLocalID: str
    ClearingPartID: str
    BusinessUnit: str
    SequenceNo: int
    TradeSource: int
    
    ...
    ...
class CThostFtdcTradeField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OrderRef: str
    UserID: str
    ExchangeID: str
    TradeID: str
    Direction: int
    OrderSysID: str
    ParticipantID: str
    ClientID: str
    TradingRole: int
    ExchangeInstID: str
    OffsetFlag: int
    HedgeFlag: int
    Price: float
    Volume: int
    TradeDate: str
    TradeTime: str
    TradeType: int
    PriceSource: int
    TraderID: str
    OrderLocalID: str
    ClearingPartID: str
    BusinessUnit: str
    SequenceNo: int
    TradingDay: str
    SettlementID: int
    BrokerOrderSeq: int
    TradeSource: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcUserSessionField:
    FrontID: int
    SessionID: int
    BrokerID: str
    UserID: str
    LoginDate: str
    LoginTime: str
    IPAddress: str
    UserProductInfo: str
    InterfaceProductInfo: str
    ProtocolInfo: str
    MacAddress: str
    LoginRemark: str
    
    ...
    ...
class CThostFtdcQueryMaxOrderVolumeField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    Direction: int
    OffsetFlag: int
    HedgeFlag: int
    MaxVolume: int
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcSettlementInfoConfirmField:
    BrokerID: str
    InvestorID: str
    ConfirmDate: str
    ConfirmTime: str
    SettlementID: int
    AccountID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcSyncDepositField:
    DepositSeqNo: str
    BrokerID: str
    InvestorID: str
    Deposit: float
    IsForce: int
    CurrencyID: str
    
    ...
    ...
class CThostFtdcSyncFundMortgageField:
    MortgageSeqNo: str
    BrokerID: str
    InvestorID: str
    FromCurrencyID: str
    MortgageAmount: float
    ToCurrencyID: str
    
    ...
    ...
class CThostFtdcBrokerSyncField:
    BrokerID: str
    
    ...
    ...
class CThostFtdcSyncingInvestorField:
    InvestorID: str
    BrokerID: str
    InvestorGroupID: str
    InvestorName: str
    IdentifiedCardType: int
    IdentifiedCardNo: str
    IsActive: int
    Telephone: str
    Address: str
    OpenDate: str
    Mobile: str
    CommModelID: str
    MarginModelID: str
    
    ...
    ...
class CThostFtdcSyncingTradingCodeField:
    InvestorID: str
    BrokerID: str
    ExchangeID: str
    ClientID: str
    IsActive: int
    ClientIDType: int
    
    ...
    ...
class CThostFtdcSyncingInvestorGroupField:
    BrokerID: str
    InvestorGroupID: str
    InvestorGroupName: str
    
    ...
    ...
class CThostFtdcSyncingTradingAccountField:
    BrokerID: str
    AccountID: str
    PreMortgage: float
    PreCredit: float
    PreDeposit: float
    PreBalance: float
    PreMargin: float
    InterestBase: float
    Interest: float
    Deposit: float
    Withdraw: float
    FrozenMargin: float
    FrozenCash: float
    FrozenCommission: float
    CurrMargin: float
    CashIn: float
    Commission: float
    CloseProfit: float
    PositionProfit: float
    Balance: float
    Available: float
    WithdrawQuota: float
    Reserve: float
    TradingDay: str
    SettlementID: int
    Credit: float
    Mortgage: float
    ExchangeMargin: float
    DeliveryMargin: float
    ExchangeDeliveryMargin: float
    ReserveBalance: float
    CurrencyID: str
    PreFundMortgageIn: float
    PreFundMortgageOut: float
    FundMortgageIn: float
    FundMortgageOut: float
    FundMortgageAvailable: float
    MortgageableFund: float
    SpecProductMargin: float
    SpecProductFrozenMargin: float
    SpecProductCommission: float
    SpecProductFrozenCommission: float
    SpecProductPositionProfit: float
    SpecProductCloseProfit: float
    SpecProductPositionProfitByAlg: float
    SpecProductExchangeMargin: float
    FrozenSwap: float
    RemainSwap: float
    
    ...
    ...
class CThostFtdcSyncingInvestorPositionField:
    InstrumentID: str
    BrokerID: str
    InvestorID: str
    PosiDirection: int
    HedgeFlag: int
    PositionDate: int
    YdPosition: int
    Position: int
    LongFrozen: int
    ShortFrozen: int
    LongFrozenAmount: float
    ShortFrozenAmount: float
    OpenVolume: int
    CloseVolume: int
    OpenAmount: float
    CloseAmount: float
    PositionCost: float
    PreMargin: float
    UseMargin: float
    FrozenMargin: float
    FrozenCash: float
    FrozenCommission: float
    CashIn: float
    Commission: float
    CloseProfit: float
    PositionProfit: float
    PreSettlementPrice: float
    SettlementPrice: float
    TradingDay: str
    SettlementID: int
    OpenCost: float
    ExchangeMargin: float
    CombPosition: int
    CombLongFrozen: int
    CombShortFrozen: int
    CloseProfitByDate: float
    CloseProfitByTrade: float
    TodayPosition: int
    MarginRateByMoney: float
    MarginRateByVolume: float
    StrikeFrozen: int
    StrikeFrozenAmount: float
    AbandonFrozen: int
    ExchangeID: str
    YdStrikeFrozen: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcSyncingInstrumentMarginRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    HedgeFlag: int
    LongMarginRatioByMoney: float
    LongMarginRatioByVolume: float
    ShortMarginRatioByMoney: float
    ShortMarginRatioByVolume: float
    IsRelative: int
    
    ...
    ...
class CThostFtdcSyncingInstrumentCommissionRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    OpenRatioByMoney: float
    OpenRatioByVolume: float
    CloseRatioByMoney: float
    CloseRatioByVolume: float
    CloseTodayRatioByMoney: float
    CloseTodayRatioByVolume: float
    
    ...
    ...
class CThostFtdcSyncingInstrumentTradingRightField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    TradingRight: int
    
    ...
    ...
class CThostFtdcQryOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    OrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryTradeField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    TradeID: str
    TradeTimeStart: str
    TradeTimeEnd: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryInvestorPositionField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryTradingAccountField:
    BrokerID: str
    InvestorID: str
    CurrencyID: str
    BizType: int
    AccountID: str
    
    ...
    ...
class CThostFtdcQryInvestorField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcQryTradingCodeField:
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    ClientID: str
    ClientIDType: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryInvestorGroupField:
    BrokerID: str
    
    ...
    ...
class CThostFtdcQryInstrumentMarginRateField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    HedgeFlag: int
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryInstrumentCommissionRateField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryInstrumentTradingRightField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    
    ...
    ...
class CThostFtdcQryBrokerField:
    BrokerID: str
    
    ...
    ...
class CThostFtdcQryTraderField:
    ExchangeID: str
    ParticipantID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcQrySuperUserFunctionField:
    UserID: str
    
    ...
    ...
class CThostFtdcQryUserSessionField:
    FrontID: int
    SessionID: int
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcQryPartBrokerField:
    ExchangeID: str
    BrokerID: str
    ParticipantID: str
    
    ...
    ...
class CThostFtdcQryFrontStatusField:
    FrontID: int
    
    ...
    ...
class CThostFtdcQryExchangeOrderField:
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcQryOrderActionField:
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryExchangeOrderActionField:
    ParticipantID: str
    ClientID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcQrySuperUserField:
    UserID: str
    
    ...
    ...
class CThostFtdcQryExchangeField:
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryProductField:
    ProductID: str
    ProductClass: int
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryInstrumentField:
    InstrumentID: str
    ExchangeID: str
    ExchangeInstID: str
    ProductID: str
    
    ...
    ...
class CThostFtdcQryDepthMarketDataField:
    InstrumentID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryBrokerUserField:
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcQryBrokerUserFunctionField:
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcQryTraderOfferField:
    ExchangeID: str
    ParticipantID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcQrySyncDepositField:
    BrokerID: str
    DepositSeqNo: str
    
    ...
    ...
class CThostFtdcQrySettlementInfoField:
    BrokerID: str
    InvestorID: str
    TradingDay: str
    AccountID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcQryExchangeMarginRateField:
    BrokerID: str
    InstrumentID: str
    HedgeFlag: int
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryExchangeMarginRateAdjustField:
    BrokerID: str
    InstrumentID: str
    HedgeFlag: int
    
    ...
    ...
class CThostFtdcQryExchangeRateField:
    BrokerID: str
    FromCurrencyID: str
    ToCurrencyID: str
    
    ...
    ...
class CThostFtdcQrySyncFundMortgageField:
    BrokerID: str
    MortgageSeqNo: str
    
    ...
    ...
class CThostFtdcQryHisOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    OrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    TradingDay: str
    SettlementID: int
    
    ...
    ...
class CThostFtdcOptionInstrMiniMarginField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    MinMargin: float
    ValueMethod: int
    IsRelative: int
    
    ...
    ...
class CThostFtdcOptionInstrMarginAdjustField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    SShortMarginRatioByMoney: float
    SShortMarginRatioByVolume: float
    HShortMarginRatioByMoney: float
    HShortMarginRatioByVolume: float
    AShortMarginRatioByMoney: float
    AShortMarginRatioByVolume: float
    IsRelative: int
    MShortMarginRatioByMoney: float
    MShortMarginRatioByVolume: float
    
    ...
    ...
class CThostFtdcOptionInstrCommRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    OpenRatioByMoney: float
    OpenRatioByVolume: float
    CloseRatioByMoney: float
    CloseRatioByVolume: float
    CloseTodayRatioByMoney: float
    CloseTodayRatioByVolume: float
    StrikeRatioByMoney: float
    StrikeRatioByVolume: float
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcOptionInstrTradeCostField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    HedgeFlag: int
    FixedMargin: float
    MiniMargin: float
    Royalty: float
    ExchFixedMargin: float
    ExchMiniMargin: float
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryOptionInstrTradeCostField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    HedgeFlag: int
    InputPrice: float
    UnderlyingPrice: float
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryOptionInstrCommRateField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcIndexPriceField:
    BrokerID: str
    InstrumentID: str
    ClosePrice: float
    
    ...
    ...
class CThostFtdcInputExecOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExecOrderRef: str
    UserID: str
    Volume: int
    RequestID: int
    BusinessUnit: str
    OffsetFlag: int
    HedgeFlag: int
    ActionType: int
    PosiDirection: int
    ReservePositionFlag: int
    CloseFlag: int
    ExchangeID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    ClientID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcInputExecOrderActionField:
    BrokerID: str
    InvestorID: str
    ExecOrderActionRef: int
    ExecOrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    ExecOrderSysID: str
    ActionFlag: int
    UserID: str
    InstrumentID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcExecOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExecOrderRef: str
    UserID: str
    Volume: int
    RequestID: int
    BusinessUnit: str
    OffsetFlag: int
    HedgeFlag: int
    ActionType: int
    PosiDirection: int
    ReservePositionFlag: int
    CloseFlag: int
    ExecOrderLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    OrderSubmitStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    ExecOrderSysID: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    ExecResult: int
    ClearingPartID: str
    SequenceNo: int
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    ActiveUserID: str
    BrokerExecOrderSeq: int
    BranchID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcExecOrderActionField:
    BrokerID: str
    InvestorID: str
    ExecOrderActionRef: int
    ExecOrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    ExecOrderSysID: str
    ActionFlag: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    ExecOrderLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    ActionType: int
    StatusMsg: str
    InstrumentID: str
    BranchID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryExecOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    ExecOrderSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    
    ...
    ...
class CThostFtdcExchangeExecOrderField:
    Volume: int
    RequestID: int
    BusinessUnit: str
    OffsetFlag: int
    HedgeFlag: int
    ActionType: int
    PosiDirection: int
    ReservePositionFlag: int
    CloseFlag: int
    ExecOrderLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    OrderSubmitStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    ExecOrderSysID: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    ExecResult: int
    ClearingPartID: str
    SequenceNo: int
    BranchID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryExchangeExecOrderField:
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcQryExecOrderActionField:
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcExchangeExecOrderActionField:
    ExchangeID: str
    ExecOrderSysID: str
    ActionFlag: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    ExecOrderLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    ActionType: int
    BranchID: str
    IPAddress: str
    MacAddress: str
    ExchangeInstID: str
    Volume: int
    
    ...
    ...
class CThostFtdcQryExchangeExecOrderActionField:
    ParticipantID: str
    ClientID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcErrExecOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExecOrderRef: str
    UserID: str
    Volume: int
    RequestID: int
    BusinessUnit: str
    OffsetFlag: int
    HedgeFlag: int
    ActionType: int
    PosiDirection: int
    ReservePositionFlag: int
    CloseFlag: int
    ExchangeID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    ClientID: str
    IPAddress: str
    MacAddress: str
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcQryErrExecOrderField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcErrExecOrderActionField:
    BrokerID: str
    InvestorID: str
    ExecOrderActionRef: int
    ExecOrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    ExecOrderSysID: str
    ActionFlag: int
    UserID: str
    InstrumentID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcQryErrExecOrderActionField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcOptionInstrTradingRightField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    Direction: int
    TradingRight: int
    
    ...
    ...
class CThostFtdcQryOptionInstrTradingRightField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    Direction: int
    
    ...
    ...
class CThostFtdcInputForQuoteField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ForQuoteRef: str
    UserID: str
    ExchangeID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcForQuoteField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ForQuoteRef: str
    UserID: str
    ForQuoteLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    InsertDate: str
    InsertTime: str
    ForQuoteStatus: int
    FrontID: int
    SessionID: int
    StatusMsg: str
    ActiveUserID: str
    BrokerForQutoSeq: int
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryForQuoteField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcExchangeForQuoteField:
    ForQuoteLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    InsertDate: str
    InsertTime: str
    ForQuoteStatus: int
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryExchangeForQuoteField:
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcInputQuoteField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    QuoteRef: str
    UserID: str
    AskPrice: float
    BidPrice: float
    AskVolume: int
    BidVolume: int
    RequestID: int
    BusinessUnit: str
    AskOffsetFlag: int
    BidOffsetFlag: int
    AskHedgeFlag: int
    BidHedgeFlag: int
    AskOrderRef: str
    BidOrderRef: str
    ForQuoteSysID: str
    ExchangeID: str
    InvestUnitID: str
    ClientID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcInputQuoteActionField:
    BrokerID: str
    InvestorID: str
    QuoteActionRef: int
    QuoteRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    QuoteSysID: str
    ActionFlag: int
    UserID: str
    InstrumentID: str
    InvestUnitID: str
    ClientID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQuoteField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    QuoteRef: str
    UserID: str
    AskPrice: float
    BidPrice: float
    AskVolume: int
    BidVolume: int
    RequestID: int
    BusinessUnit: str
    AskOffsetFlag: int
    BidOffsetFlag: int
    AskHedgeFlag: int
    BidHedgeFlag: int
    QuoteLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    NotifySequence: int
    OrderSubmitStatus: int
    TradingDay: str
    SettlementID: int
    QuoteSysID: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    QuoteStatus: int
    ClearingPartID: str
    SequenceNo: int
    AskOrderSysID: str
    BidOrderSysID: str
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    ActiveUserID: str
    BrokerQuoteSeq: int
    AskOrderRef: str
    BidOrderRef: str
    ForQuoteSysID: str
    BranchID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQuoteActionField:
    BrokerID: str
    InvestorID: str
    QuoteActionRef: int
    QuoteRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    QuoteSysID: str
    ActionFlag: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    QuoteLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    StatusMsg: str
    InstrumentID: str
    BranchID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryQuoteField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    QuoteSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcExchangeQuoteField:
    AskPrice: float
    BidPrice: float
    AskVolume: int
    BidVolume: int
    RequestID: int
    BusinessUnit: str
    AskOffsetFlag: int
    BidOffsetFlag: int
    AskHedgeFlag: int
    BidHedgeFlag: int
    QuoteLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    NotifySequence: int
    OrderSubmitStatus: int
    TradingDay: str
    SettlementID: int
    QuoteSysID: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    QuoteStatus: int
    ClearingPartID: str
    SequenceNo: int
    AskOrderSysID: str
    BidOrderSysID: str
    ForQuoteSysID: str
    BranchID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryExchangeQuoteField:
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcQryQuoteActionField:
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcExchangeQuoteActionField:
    ExchangeID: str
    QuoteSysID: str
    ActionFlag: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    QuoteLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryExchangeQuoteActionField:
    ParticipantID: str
    ClientID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcOptionInstrDeltaField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    Delta: float
    
    ...
    ...
class CThostFtdcForQuoteRspField:
    TradingDay: str
    InstrumentID: str
    ForQuoteSysID: str
    ForQuoteTime: str
    ActionDay: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcStrikeOffsetField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    Offset: float
    OffsetType: int
    
    ...
    ...
class CThostFtdcQryStrikeOffsetField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    
    ...
    ...
class CThostFtdcInputBatchOrderActionField:
    BrokerID: str
    InvestorID: str
    OrderActionRef: int
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    UserID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcBatchOrderActionField:
    BrokerID: str
    InvestorID: str
    OrderActionRef: int
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    StatusMsg: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcExchangeBatchOrderActionField:
    ExchangeID: str
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryBatchOrderActionField:
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcCombInstrumentGuardField:
    BrokerID: str
    InstrumentID: str
    GuarantRatio: float
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryCombInstrumentGuardField:
    BrokerID: str
    InstrumentID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcInputCombActionField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    CombActionRef: str
    UserID: str
    Direction: int
    Volume: int
    CombDirection: int
    HedgeFlag: int
    ExchangeID: str
    IPAddress: str
    MacAddress: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcCombActionField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    CombActionRef: str
    UserID: str
    Direction: int
    Volume: int
    CombDirection: int
    HedgeFlag: int
    ActionLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    ActionStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    SequenceNo: int
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    IPAddress: str
    MacAddress: str
    ComTradeID: str
    BranchID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryCombActionField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcExchangeCombActionField:
    Direction: int
    Volume: int
    CombDirection: int
    HedgeFlag: int
    ActionLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    ActionStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    SequenceNo: int
    IPAddress: str
    MacAddress: str
    ComTradeID: str
    BranchID: str
    
    ...
    ...
class CThostFtdcQryExchangeCombActionField:
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    ExchangeID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcProductExchRateField:
    ProductID: str
    QuoteCurrencyID: str
    ExchangeRate: float
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryProductExchRateField:
    ProductID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcQryForQuoteParamField:
    BrokerID: str
    InstrumentID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcForQuoteParamField:
    BrokerID: str
    InstrumentID: str
    ExchangeID: str
    LastPrice: float
    PriceInterval: float
    
    ...
    ...
class CThostFtdcMMOptionInstrCommRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    OpenRatioByMoney: float
    OpenRatioByVolume: float
    CloseRatioByMoney: float
    CloseRatioByVolume: float
    CloseTodayRatioByMoney: float
    CloseTodayRatioByVolume: float
    StrikeRatioByMoney: float
    StrikeRatioByVolume: float
    
    ...
    ...
class CThostFtdcQryMMOptionInstrCommRateField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    
    ...
    ...
class CThostFtdcMMInstrumentCommissionRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    OpenRatioByMoney: float
    OpenRatioByVolume: float
    CloseRatioByMoney: float
    CloseRatioByVolume: float
    CloseTodayRatioByMoney: float
    CloseTodayRatioByVolume: float
    
    ...
    ...
class CThostFtdcQryMMInstrumentCommissionRateField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    
    ...
    ...
class CThostFtdcInstrumentOrderCommRateField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    HedgeFlag: int
    OrderCommByVolume: float
    OrderActionCommByVolume: float
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryInstrumentOrderCommRateField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    
    ...
    ...
class CThostFtdcTradeParamField:
    BrokerID: str
    TradeParamID: int
    TradeParamValue: str
    Memo: str
    
    ...
    ...
class CThostFtdcInstrumentMarginRateULField:
    InstrumentID: str
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    HedgeFlag: int
    LongMarginRatioByMoney: float
    LongMarginRatioByVolume: float
    ShortMarginRatioByMoney: float
    ShortMarginRatioByVolume: float
    
    ...
    ...
class CThostFtdcFutureLimitPosiParamField:
    InvestorRange: int
    BrokerID: str
    InvestorID: str
    ProductID: str
    SpecOpenVolume: int
    ArbiOpenVolume: int
    OpenVolume: int
    
    ...
    ...
class CThostFtdcLoginForbiddenIPField:
    IPAddress: str
    
    ...
    ...
class CThostFtdcIPListField:
    IPAddress: str
    IsWhite: int
    
    ...
    ...
class CThostFtdcInputOptionSelfCloseField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OptionSelfCloseRef: str
    UserID: str
    Volume: int
    RequestID: int
    BusinessUnit: str
    HedgeFlag: int
    OptSelfCloseFlag: int
    ExchangeID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    ClientID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcInputOptionSelfCloseActionField:
    BrokerID: str
    InvestorID: str
    OptionSelfCloseActionRef: int
    OptionSelfCloseRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OptionSelfCloseSysID: str
    ActionFlag: int
    UserID: str
    InstrumentID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcOptionSelfCloseField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OptionSelfCloseRef: str
    UserID: str
    Volume: int
    RequestID: int
    BusinessUnit: str
    HedgeFlag: int
    OptSelfCloseFlag: int
    OptionSelfCloseLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    OrderSubmitStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    OptionSelfCloseSysID: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    ExecResult: int
    ClearingPartID: str
    SequenceNo: int
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    ActiveUserID: str
    BrokerOptionSelfCloseSeq: int
    BranchID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcOptionSelfCloseActionField:
    BrokerID: str
    InvestorID: str
    OptionSelfCloseActionRef: int
    OptionSelfCloseRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OptionSelfCloseSysID: str
    ActionFlag: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    OptionSelfCloseLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    StatusMsg: str
    InstrumentID: str
    BranchID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryOptionSelfCloseField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    OptionSelfCloseSysID: str
    InsertTimeStart: str
    InsertTimeEnd: str
    
    ...
    ...
class CThostFtdcExchangeOptionSelfCloseField:
    Volume: int
    RequestID: int
    BusinessUnit: str
    HedgeFlag: int
    OptSelfCloseFlag: int
    OptionSelfCloseLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    OrderSubmitStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    OptionSelfCloseSysID: str
    InsertDate: str
    InsertTime: str
    CancelTime: str
    ExecResult: int
    ClearingPartID: str
    SequenceNo: int
    BranchID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryOptionSelfCloseActionField:
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcExchangeOptionSelfCloseActionField:
    ExchangeID: str
    OptionSelfCloseSysID: str
    ActionFlag: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    OptionSelfCloseLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    BranchID: str
    IPAddress: str
    MacAddress: str
    ExchangeInstID: str
    OptSelfCloseFlag: int
    
    ...
    ...
class CThostFtdcSyncDelaySwapField:
    DelaySwapSeqNo: str
    BrokerID: str
    InvestorID: str
    FromCurrencyID: str
    FromAmount: float
    FromFrozenSwap: float
    FromRemainSwap: float
    ToCurrencyID: str
    ToAmount: float
    
    ...
    ...
class CThostFtdcQrySyncDelaySwapField:
    BrokerID: str
    DelaySwapSeqNo: str
    
    ...
    ...
class CThostFtdcInvestUnitField:
    BrokerID: str
    InvestorID: str
    InvestUnitID: str
    InvestorUnitName: str
    InvestorGroupID: str
    CommModelID: str
    MarginModelID: str
    AccountID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcQryInvestUnitField:
    BrokerID: str
    InvestorID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcSecAgentCheckModeField:
    InvestorID: str
    BrokerID: str
    CurrencyID: str
    BrokerSecAgentID: str
    CheckSelfAccount: int
    
    ...
    ...
class CThostFtdcSecAgentTradeInfoField:
    BrokerID: str
    BrokerSecAgentID: str
    InvestorID: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcMarketDataField:
    TradingDay: str
    InstrumentID: str
    ExchangeID: str
    ExchangeInstID: str
    LastPrice: float
    PreSettlementPrice: float
    PreClosePrice: float
    PreOpenInterest: float
    OpenPrice: float
    HighestPrice: float
    LowestPrice: float
    Volume: int
    Turnover: float
    OpenInterest: float
    ClosePrice: float
    SettlementPrice: float
    UpperLimitPrice: float
    LowerLimitPrice: float
    PreDelta: float
    CurrDelta: float
    UpdateTime: str
    UpdateMillisec: int
    ActionDay: str
    
    ...
    ...
class CThostFtdcMarketDataBaseField:
    TradingDay: str
    PreSettlementPrice: float
    PreClosePrice: float
    PreOpenInterest: float
    PreDelta: float
    
    ...
    ...
class CThostFtdcMarketDataStaticField:
    OpenPrice: float
    HighestPrice: float
    LowestPrice: float
    ClosePrice: float
    UpperLimitPrice: float
    LowerLimitPrice: float
    SettlementPrice: float
    CurrDelta: float
    
    ...
    ...
class CThostFtdcMarketDataLastMatchField:
    LastPrice: float
    Volume: int
    Turnover: float
    OpenInterest: float
    
    ...
    ...
class CThostFtdcMarketDataBestPriceField:
    BidPrice1: float
    BidVolume1: int
    AskPrice1: float
    AskVolume1: int
    
    ...
    ...
class CThostFtdcMarketDataBid23Field:
    BidPrice2: float
    BidVolume2: int
    BidPrice3: float
    BidVolume3: int
    
    ...
    ...
class CThostFtdcMarketDataAsk23Field:
    AskPrice2: float
    AskVolume2: int
    AskPrice3: float
    AskVolume3: int
    
    ...
    ...
class CThostFtdcMarketDataBid45Field:
    BidPrice4: float
    BidVolume4: int
    BidPrice5: float
    BidVolume5: int
    
    ...
    ...
class CThostFtdcMarketDataAsk45Field:
    AskPrice4: float
    AskVolume4: int
    AskPrice5: float
    AskVolume5: int
    
    ...
    ...
class CThostFtdcMarketDataUpdateTimeField:
    InstrumentID: str
    UpdateTime: str
    UpdateMillisec: int
    ActionDay: str
    
    ...
    ...
class CThostFtdcMarketDataExchangeField:
    ExchangeID: str
    
    ...
    ...
class CThostFtdcSpecificInstrumentField:
    InstrumentID: str
    
    ...
    ...
class CThostFtdcInstrumentStatusField:
    ExchangeID: str
    ExchangeInstID: str
    SettlementGroupID: str
    InstrumentID: str
    InstrumentStatus: int
    TradingSegmentSN: int
    EnterTime: str
    EnterReason: int
    
    ...
    ...
class CThostFtdcQryInstrumentStatusField:
    ExchangeID: str
    ExchangeInstID: str
    
    ...
    ...
class CThostFtdcInvestorAccountField:
    BrokerID: str
    InvestorID: str
    AccountID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcPositionProfitAlgorithmField:
    BrokerID: str
    AccountID: str
    Algorithm: int
    Memo: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcDiscountField:
    BrokerID: str
    InvestorRange: int
    InvestorID: str
    Discount: float
    
    ...
    ...
class CThostFtdcQryTransferBankField:
    BankID: str
    BankBrchID: str
    
    ...
    ...
class CThostFtdcTransferBankField:
    BankID: str
    BankBrchID: str
    BankName: str
    IsActive: int
    
    ...
    ...
class CThostFtdcQryInvestorPositionDetailField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcInvestorPositionDetailField:
    InstrumentID: str
    BrokerID: str
    InvestorID: str
    HedgeFlag: int
    Direction: int
    OpenDate: str
    TradeID: str
    Volume: int
    OpenPrice: float
    TradingDay: str
    SettlementID: int
    TradeType: int
    CombInstrumentID: str
    ExchangeID: str
    CloseProfitByDate: float
    CloseProfitByTrade: float
    PositionProfitByDate: float
    PositionProfitByTrade: float
    Margin: float
    ExchMargin: float
    MarginRateByMoney: float
    MarginRateByVolume: float
    LastSettlementPrice: float
    SettlementPrice: float
    CloseVolume: int
    CloseAmount: float
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcTradingAccountPasswordField:
    BrokerID: str
    AccountID: str
    Password: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcMDTraderOfferField:
    ExchangeID: str
    TraderID: str
    ParticipantID: str
    Password: str
    InstallID: int
    OrderLocalID: str
    TraderConnectStatus: int
    ConnectRequestDate: str
    ConnectRequestTime: str
    LastReportDate: str
    LastReportTime: str
    ConnectDate: str
    ConnectTime: str
    StartDate: str
    StartTime: str
    TradingDay: str
    BrokerID: str
    MaxTradeID: str
    MaxOrderMessageReference: str
    
    ...
    ...
class CThostFtdcQryMDTraderOfferField:
    ExchangeID: str
    ParticipantID: str
    TraderID: str
    
    ...
    ...
class CThostFtdcQryNoticeField:
    BrokerID: str
    
    ...
    ...
class CThostFtdcNoticeField:
    BrokerID: str
    Content: str
    SequenceLabel: str
    
    ...
    ...
class CThostFtdcUserRightField:
    BrokerID: str
    UserID: str
    UserRightType: int
    IsForbidden: int
    
    ...
    ...
class CThostFtdcQrySettlementInfoConfirmField:
    BrokerID: str
    InvestorID: str
    AccountID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcLoadSettlementInfoField:
    BrokerID: str
    
    ...
    ...
class CThostFtdcBrokerWithdrawAlgorithmField:
    BrokerID: str
    WithdrawAlgorithm: int
    UsingRatio: float
    IncludeCloseProfit: int
    AllWithoutTrade: int
    AvailIncludeCloseProfit: int
    IsBrokerUserEvent: int
    CurrencyID: str
    FundMortgageRatio: float
    BalanceAlgorithm: int
    
    ...
    ...
class CThostFtdcTradingAccountPasswordUpdateV1Field:
    BrokerID: str
    InvestorID: str
    OldPassword: str
    NewPassword: str
    
    ...
    ...
class CThostFtdcTradingAccountPasswordUpdateField:
    BrokerID: str
    AccountID: str
    OldPassword: str
    NewPassword: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcQryCombinationLegField:
    CombInstrumentID: str
    LegID: int
    LegInstrumentID: str
    
    ...
    ...
class CThostFtdcQrySyncStatusField:
    TradingDay: str
    
    ...
    ...
class CThostFtdcCombinationLegField:
    CombInstrumentID: str
    LegID: int
    LegInstrumentID: str
    Direction: int
    LegMultiple: int
    ImplyLevel: int
    
    ...
    ...
class CThostFtdcSyncStatusField:
    TradingDay: str
    DataSyncStatus: int
    
    ...
    ...
class CThostFtdcQryLinkManField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcLinkManField:
    BrokerID: str
    InvestorID: str
    PersonType: int
    IdentifiedCardType: int
    IdentifiedCardNo: str
    PersonName: str
    Telephone: str
    Address: str
    ZipCode: str
    Priority: int
    UOAZipCode: str
    PersonFullName: str
    
    ...
    ...
class CThostFtdcQryBrokerUserEventField:
    BrokerID: str
    UserID: str
    UserEventType: int
    
    ...
    ...
class CThostFtdcBrokerUserEventField:
    BrokerID: str
    UserID: str
    UserEventType: int
    EventSequenceNo: int
    EventDate: str
    EventTime: str
    UserEventInfo: str
    InvestorID: str
    InstrumentID: str
    
    ...
    ...
class CThostFtdcQryContractBankField:
    BrokerID: str
    BankID: str
    BankBrchID: str
    
    ...
    ...
class CThostFtdcContractBankField:
    BrokerID: str
    BankID: str
    BankBrchID: str
    BankName: str
    
    ...
    ...
class CThostFtdcInvestorPositionCombineDetailField:
    TradingDay: str
    OpenDate: str
    ExchangeID: str
    SettlementID: int
    BrokerID: str
    InvestorID: str
    ComTradeID: str
    TradeID: str
    InstrumentID: str
    HedgeFlag: int
    Direction: int
    TotalAmt: int
    Margin: float
    ExchMargin: float
    MarginRateByMoney: float
    MarginRateByVolume: float
    LegID: int
    LegMultiple: int
    CombInstrumentID: str
    TradeGroupID: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcParkedOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OrderRef: str
    UserID: str
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    GTDDate: str
    VolumeCondition: int
    MinVolume: int
    ContingentCondition: int
    StopPrice: float
    ForceCloseReason: int
    IsAutoSuspend: int
    BusinessUnit: str
    RequestID: int
    UserForceClose: int
    ExchangeID: str
    ParkedOrderID: str
    UserType: int
    Status: int
    ErrorID: int
    ErrorMsg: str
    IsSwapOrder: int
    AccountID: str
    CurrencyID: str
    ClientID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcParkedOrderActionField:
    BrokerID: str
    InvestorID: str
    OrderActionRef: int
    OrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OrderSysID: str
    ActionFlag: int
    LimitPrice: float
    VolumeChange: int
    UserID: str
    InstrumentID: str
    ParkedOrderActionID: str
    UserType: int
    Status: int
    ErrorID: int
    ErrorMsg: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryParkedOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryParkedOrderActionField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcRemoveParkedOrderField:
    BrokerID: str
    InvestorID: str
    ParkedOrderID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcRemoveParkedOrderActionField:
    BrokerID: str
    InvestorID: str
    ParkedOrderActionID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcInvestorWithdrawAlgorithmField:
    BrokerID: str
    InvestorRange: int
    InvestorID: str
    UsingRatio: float
    CurrencyID: str
    FundMortgageRatio: float
    
    ...
    ...
class CThostFtdcQryInvestorPositionCombineDetailField:
    BrokerID: str
    InvestorID: str
    CombInstrumentID: str
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcMarketDataAveragePriceField:
    AveragePrice: float
    
    ...
    ...
class CThostFtdcVerifyInvestorPasswordField:
    BrokerID: str
    InvestorID: str
    Password: str
    
    ...
    ...
class CThostFtdcUserIPField:
    BrokerID: str
    UserID: str
    IPAddress: str
    IPMask: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcTradingNoticeInfoField:
    BrokerID: str
    InvestorID: str
    SendTime: str
    FieldContent: str
    SequenceSeries: int
    SequenceNo: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcTradingNoticeField:
    BrokerID: str
    InvestorRange: int
    InvestorID: str
    SequenceSeries: int
    UserID: str
    SendTime: str
    SequenceNo: int
    FieldContent: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryTradingNoticeField:
    BrokerID: str
    InvestorID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryErrOrderField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcErrOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OrderRef: str
    UserID: str
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    GTDDate: str
    VolumeCondition: int
    MinVolume: int
    ContingentCondition: int
    StopPrice: float
    ForceCloseReason: int
    IsAutoSuspend: int
    BusinessUnit: str
    RequestID: int
    UserForceClose: int
    ErrorID: int
    ErrorMsg: str
    IsSwapOrder: int
    ExchangeID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    ClientID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcErrorConditionalOrderField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    OrderRef: str
    UserID: str
    OrderPriceType: int
    Direction: int
    CombOffsetFlag: str
    CombHedgeFlag: str
    LimitPrice: float
    VolumeTotalOriginal: int
    TimeCondition: int
    GTDDate: str
    VolumeCondition: int
    MinVolume: int
    ContingentCondition: int
    StopPrice: float
    ForceCloseReason: int
    IsAutoSuspend: int
    BusinessUnit: str
    RequestID: int
    OrderLocalID: str
    ExchangeID: str
    ParticipantID: str
    ClientID: str
    ExchangeInstID: str
    TraderID: str
    InstallID: int
    OrderSubmitStatus: int
    NotifySequence: int
    TradingDay: str
    SettlementID: int
    OrderSysID: str
    OrderSource: int
    OrderStatus: int
    OrderType: int
    VolumeTraded: int
    VolumeTotal: int
    InsertDate: str
    InsertTime: str
    ActiveTime: str
    SuspendTime: str
    UpdateTime: str
    CancelTime: str
    ActiveTraderID: str
    ClearingPartID: str
    SequenceNo: int
    FrontID: int
    SessionID: int
    UserProductInfo: str
    StatusMsg: str
    UserForceClose: int
    ActiveUserID: str
    BrokerOrderSeq: int
    RelativeOrderSysID: str
    ZCETotalTradedVolume: int
    ErrorID: int
    ErrorMsg: str
    IsSwapOrder: int
    BranchID: str
    InvestUnitID: str
    AccountID: str
    CurrencyID: str
    IPAddress: str
    MacAddress: str
    
    ...
    ...
class CThostFtdcQryErrOrderActionField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcErrOrderActionField:
    BrokerID: str
    InvestorID: str
    OrderActionRef: int
    OrderRef: str
    RequestID: int
    FrontID: int
    SessionID: int
    ExchangeID: str
    OrderSysID: str
    ActionFlag: int
    LimitPrice: float
    VolumeChange: int
    ActionDate: str
    ActionTime: str
    TraderID: str
    InstallID: int
    OrderLocalID: str
    ActionLocalID: str
    ParticipantID: str
    ClientID: str
    BusinessUnit: str
    OrderActionStatus: int
    UserID: str
    StatusMsg: str
    InstrumentID: str
    BranchID: str
    InvestUnitID: str
    IPAddress: str
    MacAddress: str
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcQryExchangeSequenceField:
    ExchangeID: str
    
    ...
    ...
class CThostFtdcExchangeSequenceField:
    ExchangeID: str
    SequenceNo: int
    MarketStatus: int
    
    ...
    ...
class CThostFtdcQueryMaxOrderVolumeWithPriceField:
    BrokerID: str
    InvestorID: str
    InstrumentID: str
    Direction: int
    OffsetFlag: int
    HedgeFlag: int
    MaxVolume: int
    Price: float
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryBrokerTradingParamsField:
    BrokerID: str
    InvestorID: str
    CurrencyID: str
    AccountID: str
    
    ...
    ...
class CThostFtdcBrokerTradingParamsField:
    BrokerID: str
    InvestorID: str
    MarginPriceType: int
    Algorithm: int
    AvailIncludeCloseProfit: int
    CurrencyID: str
    OptionRoyaltyPriceType: int
    AccountID: str
    
    ...
    ...
class CThostFtdcQryBrokerTradingAlgosField:
    BrokerID: str
    ExchangeID: str
    InstrumentID: str
    
    ...
    ...
class CThostFtdcBrokerTradingAlgosField:
    BrokerID: str
    ExchangeID: str
    InstrumentID: str
    HandlePositionAlgoID: int
    FindMarginRateAlgoID: int
    HandleTradingAccountAlgoID: int
    
    ...
    ...
class CThostFtdcQueryBrokerDepositField:
    BrokerID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcBrokerDepositField:
    TradingDay: str
    BrokerID: str
    ParticipantID: str
    ExchangeID: str
    PreBalance: float
    CurrMargin: float
    CloseProfit: float
    Balance: float
    Deposit: float
    Withdraw: float
    Available: float
    Reserve: float
    FrozenMargin: float
    
    ...
    ...
class CThostFtdcQryCFMMCBrokerKeyField:
    BrokerID: str
    
    ...
    ...
class CThostFtdcCFMMCBrokerKeyField:
    BrokerID: str
    ParticipantID: str
    CreateDate: str
    CreateTime: str
    KeyID: int
    CurrentKey: str
    KeyKind: int
    
    ...
    ...
class CThostFtdcCFMMCTradingAccountKeyField:
    BrokerID: str
    ParticipantID: str
    AccountID: str
    KeyID: int
    CurrentKey: str
    
    ...
    ...
class CThostFtdcQryCFMMCTradingAccountKeyField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcBrokerUserOTPParamField:
    BrokerID: str
    UserID: str
    OTPVendorsID: str
    SerialNumber: str
    AuthKey: str
    LastDrift: int
    LastSuccess: int
    OTPType: int
    
    ...
    ...
class CThostFtdcManualSyncBrokerUserOTPField:
    BrokerID: str
    UserID: str
    OTPType: int
    FirstOTP: str
    SecondOTP: str
    
    ...
    ...
class CThostFtdcCommRateModelField:
    BrokerID: str
    CommModelID: str
    CommModelName: str
    
    ...
    ...
class CThostFtdcQryCommRateModelField:
    BrokerID: str
    CommModelID: str
    
    ...
    ...
class CThostFtdcMarginModelField:
    BrokerID: str
    MarginModelID: str
    MarginModelName: str
    
    ...
    ...
class CThostFtdcQryMarginModelField:
    BrokerID: str
    MarginModelID: str
    
    ...
    ...
class CThostFtdcEWarrantOffsetField:
    TradingDay: str
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    InstrumentID: str
    Direction: int
    HedgeFlag: int
    Volume: int
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryEWarrantOffsetField:
    BrokerID: str
    InvestorID: str
    ExchangeID: str
    InstrumentID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQryInvestorProductGroupMarginField:
    BrokerID: str
    InvestorID: str
    ProductGroupID: str
    HedgeFlag: int
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcInvestorProductGroupMarginField:
    ProductGroupID: str
    BrokerID: str
    InvestorID: str
    TradingDay: str
    SettlementID: int
    FrozenMargin: float
    LongFrozenMargin: float
    ShortFrozenMargin: float
    UseMargin: float
    LongUseMargin: float
    ShortUseMargin: float
    ExchMargin: float
    LongExchMargin: float
    ShortExchMargin: float
    CloseProfit: float
    FrozenCommission: float
    Commission: float
    FrozenCash: float
    CashIn: float
    PositionProfit: float
    OffsetAmount: float
    LongOffsetAmount: float
    ShortOffsetAmount: float
    ExchOffsetAmount: float
    LongExchOffsetAmount: float
    ShortExchOffsetAmount: float
    HedgeFlag: int
    ExchangeID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcQueryCFMMCTradingAccountTokenField:
    BrokerID: str
    InvestorID: str
    InvestUnitID: str
    
    ...
    ...
class CThostFtdcCFMMCTradingAccountTokenField:
    BrokerID: str
    ParticipantID: str
    AccountID: str
    KeyID: int
    Token: str
    
    ...
    ...
class CThostFtdcQryProductGroupField:
    ProductID: str
    ExchangeID: str
    
    ...
    ...
class CThostFtdcProductGroupField:
    ProductID: str
    ExchangeID: str
    ProductGroupID: str
    
    ...
    ...
class CThostFtdcBulletinField:
    ExchangeID: str
    TradingDay: str
    BulletinID: int
    SequenceNo: int
    NewsType: str
    NewsUrgency: int
    SendTime: str
    Abstract: str
    ComeFrom: str
    Content: str
    URLLink: str
    MarketID: str
    
    ...
    ...
class CThostFtdcQryBulletinField:
    ExchangeID: str
    BulletinID: int
    SequenceNo: int
    NewsType: str
    NewsUrgency: int
    
    ...
    ...
class CThostFtdcReqOpenAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    CashExchangeCode: int
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    TID: int
    UserID: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcReqCancelAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    CashExchangeCode: int
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    TID: int
    UserID: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcReqChangeAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    NewBankAccount: str
    NewBankPassWord: str
    AccountID: str
    Password: str
    BankAccType: int
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    BrokerIDByBank: str
    BankPwdFlag: int
    SecuPwdFlag: int
    TID: int
    Digest: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcReqTransferField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    FutureSerial: int
    UserID: str
    VerifyCertNoFlag: int
    CurrencyID: str
    TradeAmount: float
    FutureFetchAmount: float
    FeePayFlag: int
    CustFee: float
    BrokerFee: float
    Message: str
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    RequestID: int
    TID: int
    TransferStatus: int
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcRspTransferField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    FutureSerial: int
    UserID: str
    VerifyCertNoFlag: int
    CurrencyID: str
    TradeAmount: float
    FutureFetchAmount: float
    FeePayFlag: int
    CustFee: float
    BrokerFee: float
    Message: str
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    RequestID: int
    TID: int
    TransferStatus: int
    ErrorID: int
    ErrorMsg: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcReqRepealField:
    RepealTimeInterval: int
    RepealedTimes: int
    BankRepealFlag: int
    BrokerRepealFlag: int
    PlateRepealSerial: int
    BankRepealSerial: str
    FutureRepealSerial: int
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    FutureSerial: int
    UserID: str
    VerifyCertNoFlag: int
    CurrencyID: str
    TradeAmount: float
    FutureFetchAmount: float
    FeePayFlag: int
    CustFee: float
    BrokerFee: float
    Message: str
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    RequestID: int
    TID: int
    TransferStatus: int
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcRspRepealField:
    RepealTimeInterval: int
    RepealedTimes: int
    BankRepealFlag: int
    BrokerRepealFlag: int
    PlateRepealSerial: int
    BankRepealSerial: str
    FutureRepealSerial: int
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    FutureSerial: int
    UserID: str
    VerifyCertNoFlag: int
    CurrencyID: str
    TradeAmount: float
    FutureFetchAmount: float
    FeePayFlag: int
    CustFee: float
    BrokerFee: float
    Message: str
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    RequestID: int
    TID: int
    TransferStatus: int
    ErrorID: int
    ErrorMsg: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcReqQueryAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    FutureSerial: int
    InstallID: int
    UserID: str
    VerifyCertNoFlag: int
    CurrencyID: str
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    RequestID: int
    TID: int
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcRspQueryAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    FutureSerial: int
    InstallID: int
    UserID: str
    VerifyCertNoFlag: int
    CurrencyID: str
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    RequestID: int
    TID: int
    BankUseAmount: float
    BankFetchAmount: float
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcFutureSignIOField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Digest: str
    CurrencyID: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    
    ...
    ...
class CThostFtdcRspFutureSignInField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Digest: str
    CurrencyID: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    ErrorID: int
    ErrorMsg: str
    PinKey: str
    MacKey: str
    
    ...
    ...
class CThostFtdcReqFutureSignOutField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Digest: str
    CurrencyID: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    
    ...
    ...
class CThostFtdcRspFutureSignOutField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Digest: str
    CurrencyID: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcReqQueryTradeResultBySerialField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    Reference: int
    RefrenceIssureType: int
    RefrenceIssure: str
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    CurrencyID: str
    TradeAmount: float
    Digest: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcRspQueryTradeResultBySerialField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    ErrorID: int
    ErrorMsg: str
    Reference: int
    RefrenceIssureType: int
    RefrenceIssure: str
    OriginReturnCode: str
    OriginDescrInfoForReturnCode: str
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    CurrencyID: str
    TradeAmount: float
    Digest: str
    
    ...
    ...
class CThostFtdcReqDayEndFileReadyField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    FileBusinessCode: int
    Digest: str
    
    ...
    ...
class CThostFtdcReturnResultField:
    ReturnCode: str
    DescrInfoForReturnCode: str
    
    ...
    ...
class CThostFtdcVerifyFuturePasswordField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    AccountID: str
    Password: str
    BankAccount: str
    BankPassWord: str
    InstallID: int
    TID: int
    CurrencyID: str
    
    ...
    ...
class CThostFtdcVerifyCustInfoField:
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcVerifyFuturePasswordAndCustInfoField:
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    AccountID: str
    Password: str
    CurrencyID: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcDepositResultInformField:
    DepositSeqNo: str
    BrokerID: str
    InvestorID: str
    Deposit: float
    RequestID: int
    ReturnCode: str
    DescrInfoForReturnCode: str
    
    ...
    ...
class CThostFtdcReqSyncKeyField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Message: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    
    ...
    ...
class CThostFtdcRspSyncKeyField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Message: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcNotifyQueryAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    CustType: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    FutureSerial: int
    InstallID: int
    UserID: str
    VerifyCertNoFlag: int
    CurrencyID: str
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    RequestID: int
    TID: int
    BankUseAmount: float
    BankFetchAmount: float
    ErrorID: int
    ErrorMsg: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcTransferSerialField:
    PlateSerial: int
    TradeDate: str
    TradingDay: str
    TradeTime: str
    TradeCode: str
    SessionID: int
    BankID: str
    BankBranchID: str
    BankAccType: int
    BankAccount: str
    BankSerial: str
    BrokerID: str
    BrokerBranchID: str
    FutureAccType: int
    AccountID: str
    InvestorID: str
    FutureSerial: int
    IdCardType: int
    IdentifiedCardNo: str
    CurrencyID: str
    TradeAmount: float
    CustFee: float
    BrokerFee: float
    AvailabilityFlag: int
    OperatorCode: str
    BankNewAccount: str
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcQryTransferSerialField:
    BrokerID: str
    AccountID: str
    BankID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcNotifyFutureSignInField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Digest: str
    CurrencyID: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    ErrorID: int
    ErrorMsg: str
    PinKey: str
    MacKey: str
    
    ...
    ...
class CThostFtdcNotifyFutureSignOutField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Digest: str
    CurrencyID: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcNotifySyncKeyField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    InstallID: int
    UserID: str
    Message: str
    DeviceID: str
    BrokerIDByBank: str
    OperNo: str
    RequestID: int
    TID: int
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcQryAccountregisterField:
    BrokerID: str
    AccountID: str
    BankID: str
    BankBranchID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcAccountregisterField:
    TradeDay: str
    BankID: str
    BankBranchID: str
    BankAccount: str
    BrokerID: str
    BrokerBranchID: str
    AccountID: str
    IdCardType: int
    IdentifiedCardNo: str
    CustomerName: str
    CurrencyID: str
    OpenOrDestroy: int
    RegDate: str
    OutDate: str
    TID: int
    CustType: int
    BankAccType: int
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcOpenAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    CashExchangeCode: int
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    TID: int
    UserID: str
    ErrorID: int
    ErrorMsg: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcCancelAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    AccountID: str
    Password: str
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    CashExchangeCode: int
    Digest: str
    BankAccType: int
    DeviceID: str
    BankSecuAccType: int
    BrokerIDByBank: str
    BankSecuAcc: str
    BankPwdFlag: int
    SecuPwdFlag: int
    OperNo: str
    TID: int
    UserID: str
    ErrorID: int
    ErrorMsg: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcChangeAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    NewBankAccount: str
    NewBankPassWord: str
    AccountID: str
    Password: str
    BankAccType: int
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    BrokerIDByBank: str
    BankPwdFlag: int
    SecuPwdFlag: int
    TID: int
    Digest: str
    ErrorID: int
    ErrorMsg: str
    LongCustomerName: str
    
    ...
    ...
class CThostFtdcSecAgentACIDMapField:
    BrokerID: str
    UserID: str
    AccountID: str
    CurrencyID: str
    BrokerSecAgentID: str
    
    ...
    ...
class CThostFtdcQrySecAgentACIDMapField:
    BrokerID: str
    UserID: str
    AccountID: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcUserRightsAssignField:
    BrokerID: str
    UserID: str
    DRIdentityID: int
    
    ...
    ...
class CThostFtdcBrokerUserRightAssignField:
    BrokerID: str
    DRIdentityID: int
    Tradeable: int
    
    ...
    ...
class CThostFtdcDRTransferField:
    OrigDRIdentityID: int
    DestDRIdentityID: int
    OrigBrokerID: str
    DestBrokerID: str
    
    ...
    ...
class CThostFtdcFensUserInfoField:
    BrokerID: str
    UserID: str
    LoginMode: int
    
    ...
    ...
class CThostFtdcCurrTransferIdentityField:
    IdentityID: int
    
    ...
    ...
class CThostFtdcLoginForbiddenUserField:
    BrokerID: str
    UserID: str
    IPAddress: str
    
    ...
    ...
class CThostFtdcQryLoginForbiddenUserField:
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcMulticastGroupInfoField:
    GroupIP: str
    GroupPort: int
    SourceIP: str
    
    ...
    ...
class CThostFtdcTradingAccountReserveField:
    BrokerID: str
    AccountID: str
    Reserve: float
    CurrencyID: str
    
    ...
    ...
class CThostFtdcQryLoginForbiddenIPField:
    IPAddress: str
    
    ...
    ...
class CThostFtdcQryIPListField:
    IPAddress: str
    
    ...
    ...
class CThostFtdcQryUserRightsAssignField:
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcReserveOpenAccountConfirmField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    Digest: str
    BankAccType: int
    BrokerIDByBank: str
    TID: int
    AccountID: str
    Password: str
    BankReserveOpenSeq: str
    BookDate: str
    BookPsw: str
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcReserveOpenAccountField:
    TradeCode: str
    BankID: str
    BankBranchID: str
    BrokerID: str
    BrokerBranchID: str
    TradeDate: str
    TradeTime: str
    BankSerial: str
    TradingDay: str
    PlateSerial: int
    LastFragment: int
    SessionID: int
    CustomerName: str
    IdCardType: int
    IdentifiedCardNo: str
    Gender: int
    CountryCode: str
    CustType: int
    Address: str
    ZipCode: str
    Telephone: str
    MobilePhone: str
    Fax: str
    EMail: str
    MoneyAccountStatus: int
    BankAccount: str
    BankPassWord: str
    InstallID: int
    VerifyCertNoFlag: int
    CurrencyID: str
    Digest: str
    BankAccType: int
    BrokerIDByBank: str
    TID: int
    ReserveOpenAccStas: int
    ErrorID: int
    ErrorMsg: str
    
    ...
    ...
class CThostFtdcAccountPropertyField:
    BrokerID: str
    AccountID: str
    BankID: str
    BankAccount: str
    OpenName: str
    OpenBank: str
    IsActive: int
    AccountSourceType: int
    OpenDate: str
    CancelDate: str
    OperatorID: str
    OperateDate: str
    OperateTime: str
    CurrencyID: str
    
    ...
    ...
class CThostFtdcQryCurrDRIdentityField:
    DRIdentityID: int
    
    ...
    ...
class CThostFtdcCurrDRIdentityField:
    DRIdentityID: int
    
    ...
    ...
class CThostFtdcQrySecAgentCheckModeField:
    BrokerID: str
    InvestorID: str
    
    ...
    ...
class CThostFtdcQrySecAgentTradeInfoField:
    BrokerID: str
    BrokerSecAgentID: str
    
    ...
    ...
class CThostFtdcUserSystemInfoField:
    BrokerID: str
    UserID: str
    ClientSystemInfoLen: int
    ClientSystemInfo: str
    ClientPublicIP: str
    ClientIPPort: int
    ClientLoginTime: str
    ClientAppID: str
    
    ...
    ...
class CThostFtdcReqUserAuthMethodField:
    TradingDay: str
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcRspUserAuthMethodField:
    UsableAuthMethod: int
    
    ...
    ...
class CThostFtdcReqGenUserCaptchaField:
    TradingDay: str
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcRspGenUserCaptchaField:
    BrokerID: str
    UserID: str
    CaptchaInfoLen: int
    CaptchaInfo: str
    
    ...
    ...
class CThostFtdcReqGenUserTextField:
    TradingDay: str
    BrokerID: str
    UserID: str
    
    ...
    ...
class CThostFtdcRspGenUserTextField:
    UserTextSeq: int
    
    ...
    ...
class CThostFtdcReqUserLoginWithCaptchaField:
    TradingDay: str
    BrokerID: str
    UserID: str
    Password: str
    UserProductInfo: str
    InterfaceProductInfo: str
    ProtocolInfo: str
    MacAddress: str
    ClientIPAddress: str
    LoginRemark: str
    Captcha: str
    ClientIPPort: int
    
    ...
    ...
class CThostFtdcReqUserLoginWithTextField:
    TradingDay: str
    BrokerID: str
    UserID: str
    Password: str
    UserProductInfo: str
    InterfaceProductInfo: str
    ProtocolInfo: str
    MacAddress: str
    ClientIPAddress: str
    LoginRemark: str
    Text: str
    ClientIPPort: int
    
    ...
    ...
class CThostFtdcReqUserLoginWithOTPField:
    TradingDay: str
    BrokerID: str
    UserID: str
    Password: str
    UserProductInfo: str
    InterfaceProductInfo: str
    ProtocolInfo: str
    MacAddress: str
    ClientIPAddress: str
    LoginRemark: str
    OTPPassword: str
    ClientIPPort: int
    
    ...
    ...
class CThostFtdcReqApiHandshakeField:
    CryptoKeyVersion: str
    
    ...
    ...
class CThostFtdcRspApiHandshakeField:
    FrontHandshakeDataLen: int
    FrontHandshakeData: str
    IsApiAuthEnabled: int
    
    ...
    ...
class CThostFtdcReqVerifyApiKeyField:
    ApiHandshakeDataLen: int
    ApiHandshakeData: str
    
    ...
    ...
class CThostFtdcDepartmentUserField:
    BrokerID: str
    UserID: str
    InvestorRange: int
    InvestorID: str
    
    ...
    ...
class CThostFtdcQueryFreqField:
    QueryFreq: int
    
    ...
    ...
class CThostFtdcTraderSpi:
    
    def OnFrontConnected(self, 
        ) -> None:
        
        ...
    
    def OnFrontDisconnected(self, 
            nReason: int,
        ) -> None:
        
        ...
    
    def OnHeartBeatWarning(self, 
            nTimeLapse: int,
        ) -> None:
        
        ...
    
    def OnRspAuthenticate(self, 
            pRspAuthenticateField: CThostFtdcRspAuthenticateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspUserLogin(self, 
            pRspUserLogin: CThostFtdcRspUserLoginField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspUserLogout(self, 
            pUserLogout: CThostFtdcUserLogoutField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspUserPasswordUpdate(self, 
            pUserPasswordUpdate: CThostFtdcUserPasswordUpdateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspTradingAccountPasswordUpdate(self, 
            pTradingAccountPasswordUpdate: CThostFtdcTradingAccountPasswordUpdateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspUserAuthMethod(self, 
            pRspUserAuthMethod: CThostFtdcRspUserAuthMethodField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspGenUserCaptcha(self, 
            pRspGenUserCaptcha: CThostFtdcRspGenUserCaptchaField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspGenUserText(self, 
            pRspGenUserText: CThostFtdcRspGenUserTextField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspOrderInsert(self, 
            pInputOrder: CThostFtdcInputOrderField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspParkedOrderInsert(self, 
            pParkedOrder: CThostFtdcParkedOrderField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspParkedOrderAction(self, 
            pParkedOrderAction: CThostFtdcParkedOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspOrderAction(self, 
            pInputOrderAction: CThostFtdcInputOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQueryMaxOrderVolume(self, 
            pQueryMaxOrderVolume: CThostFtdcQueryMaxOrderVolumeField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspSettlementInfoConfirm(self, 
            pSettlementInfoConfirm: CThostFtdcSettlementInfoConfirmField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspRemoveParkedOrder(self, 
            pRemoveParkedOrder: CThostFtdcRemoveParkedOrderField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspRemoveParkedOrderAction(self, 
            pRemoveParkedOrderAction: CThostFtdcRemoveParkedOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspExecOrderInsert(self, 
            pInputExecOrder: CThostFtdcInputExecOrderField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspExecOrderAction(self, 
            pInputExecOrderAction: CThostFtdcInputExecOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspForQuoteInsert(self, 
            pInputForQuote: CThostFtdcInputForQuoteField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQuoteInsert(self, 
            pInputQuote: CThostFtdcInputQuoteField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQuoteAction(self, 
            pInputQuoteAction: CThostFtdcInputQuoteActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspBatchOrderAction(self, 
            pInputBatchOrderAction: CThostFtdcInputBatchOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspOptionSelfCloseInsert(self, 
            pInputOptionSelfClose: CThostFtdcInputOptionSelfCloseField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspOptionSelfCloseAction(self, 
            pInputOptionSelfCloseAction: CThostFtdcInputOptionSelfCloseActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspCombActionInsert(self, 
            pInputCombAction: CThostFtdcInputCombActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryOrder(self, 
            pOrder: CThostFtdcOrderField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryTrade(self, 
            pTrade: CThostFtdcTradeField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInvestorPosition(self, 
            pInvestorPosition: CThostFtdcInvestorPositionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryTradingAccount(self, 
            pTradingAccount: CThostFtdcTradingAccountField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInvestor(self, 
            pInvestor: CThostFtdcInvestorField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryTradingCode(self, 
            pTradingCode: CThostFtdcTradingCodeField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInstrumentMarginRate(self, 
            pInstrumentMarginRate: CThostFtdcInstrumentMarginRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInstrumentCommissionRate(self, 
            pInstrumentCommissionRate: CThostFtdcInstrumentCommissionRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryExchange(self, 
            pExchange: CThostFtdcExchangeField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryProduct(self, 
            pProduct: CThostFtdcProductField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInstrument(self, 
            pInstrument: CThostFtdcInstrumentField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryDepthMarketData(self, 
            pDepthMarketData: CThostFtdcDepthMarketDataField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQrySettlementInfo(self, 
            pSettlementInfo: CThostFtdcSettlementInfoField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryTransferBank(self, 
            pTransferBank: CThostFtdcTransferBankField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInvestorPositionDetail(self, 
            pInvestorPositionDetail: CThostFtdcInvestorPositionDetailField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryNotice(self, 
            pNotice: CThostFtdcNoticeField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQrySettlementInfoConfirm(self, 
            pSettlementInfoConfirm: CThostFtdcSettlementInfoConfirmField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInvestorPositionCombineDetail(self, 
            pInvestorPositionCombineDetail: CThostFtdcInvestorPositionCombineDetailField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryCFMMCTradingAccountKey(self, 
            pCFMMCTradingAccountKey: CThostFtdcCFMMCTradingAccountKeyField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryEWarrantOffset(self, 
            pEWarrantOffset: CThostFtdcEWarrantOffsetField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInvestorProductGroupMargin(self, 
            pInvestorProductGroupMargin: CThostFtdcInvestorProductGroupMarginField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryExchangeMarginRate(self, 
            pExchangeMarginRate: CThostFtdcExchangeMarginRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryExchangeMarginRateAdjust(self, 
            pExchangeMarginRateAdjust: CThostFtdcExchangeMarginRateAdjustField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryExchangeRate(self, 
            pExchangeRate: CThostFtdcExchangeRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQrySecAgentACIDMap(self, 
            pSecAgentACIDMap: CThostFtdcSecAgentACIDMapField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryProductExchRate(self, 
            pProductExchRate: CThostFtdcProductExchRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryProductGroup(self, 
            pProductGroup: CThostFtdcProductGroupField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryMMInstrumentCommissionRate(self, 
            pMMInstrumentCommissionRate: CThostFtdcMMInstrumentCommissionRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryMMOptionInstrCommRate(self, 
            pMMOptionInstrCommRate: CThostFtdcMMOptionInstrCommRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInstrumentOrderCommRate(self, 
            pInstrumentOrderCommRate: CThostFtdcInstrumentOrderCommRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQrySecAgentTradingAccount(self, 
            pTradingAccount: CThostFtdcTradingAccountField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQrySecAgentCheckMode(self, 
            pSecAgentCheckMode: CThostFtdcSecAgentCheckModeField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQrySecAgentTradeInfo(self, 
            pSecAgentTradeInfo: CThostFtdcSecAgentTradeInfoField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryOptionInstrTradeCost(self, 
            pOptionInstrTradeCost: CThostFtdcOptionInstrTradeCostField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryOptionInstrCommRate(self, 
            pOptionInstrCommRate: CThostFtdcOptionInstrCommRateField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryExecOrder(self, 
            pExecOrder: CThostFtdcExecOrderField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryForQuote(self, 
            pForQuote: CThostFtdcForQuoteField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryQuote(self, 
            pQuote: CThostFtdcQuoteField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryOptionSelfClose(self, 
            pOptionSelfClose: CThostFtdcOptionSelfCloseField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryInvestUnit(self, 
            pInvestUnit: CThostFtdcInvestUnitField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryCombInstrumentGuard(self, 
            pCombInstrumentGuard: CThostFtdcCombInstrumentGuardField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryCombAction(self, 
            pCombAction: CThostFtdcCombActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryTransferSerial(self, 
            pTransferSerial: CThostFtdcTransferSerialField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryAccountregister(self, 
            pAccountregister: CThostFtdcAccountregisterField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspError(self, 
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRtnOrder(self, 
            pOrder: CThostFtdcOrderField,
        ) -> None:
        
        ...
    
    def OnRtnTrade(self, 
            pTrade: CThostFtdcTradeField,
        ) -> None:
        
        ...
    
    def OnErrRtnOrderInsert(self, 
            pInputOrder: CThostFtdcInputOrderField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnOrderAction(self, 
            pOrderAction: CThostFtdcOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnRtnInstrumentStatus(self, 
            pInstrumentStatus: CThostFtdcInstrumentStatusField,
        ) -> None:
        
        ...
    
    def OnRtnBulletin(self, 
            pBulletin: CThostFtdcBulletinField,
        ) -> None:
        
        ...
    
    def OnRtnTradingNotice(self, 
            pTradingNoticeInfo: CThostFtdcTradingNoticeInfoField,
        ) -> None:
        
        ...
    
    def OnRtnErrorConditionalOrder(self, 
            pErrorConditionalOrder: CThostFtdcErrorConditionalOrderField,
        ) -> None:
        
        ...
    
    def OnRtnExecOrder(self, 
            pExecOrder: CThostFtdcExecOrderField,
        ) -> None:
        
        ...
    
    def OnErrRtnExecOrderInsert(self, 
            pInputExecOrder: CThostFtdcInputExecOrderField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnExecOrderAction(self, 
            pExecOrderAction: CThostFtdcExecOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnForQuoteInsert(self, 
            pInputForQuote: CThostFtdcInputForQuoteField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnRtnQuote(self, 
            pQuote: CThostFtdcQuoteField,
        ) -> None:
        
        ...
    
    def OnErrRtnQuoteInsert(self, 
            pInputQuote: CThostFtdcInputQuoteField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnQuoteAction(self, 
            pQuoteAction: CThostFtdcQuoteActionField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnRtnForQuoteRsp(self, 
            pForQuoteRsp: CThostFtdcForQuoteRspField,
        ) -> None:
        
        ...
    
    def OnRtnCFMMCTradingAccountToken(self, 
            pCFMMCTradingAccountToken: CThostFtdcCFMMCTradingAccountTokenField,
        ) -> None:
        
        ...
    
    def OnErrRtnBatchOrderAction(self, 
            pBatchOrderAction: CThostFtdcBatchOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnRtnOptionSelfClose(self, 
            pOptionSelfClose: CThostFtdcOptionSelfCloseField,
        ) -> None:
        
        ...
    
    def OnErrRtnOptionSelfCloseInsert(self, 
            pInputOptionSelfClose: CThostFtdcInputOptionSelfCloseField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnOptionSelfCloseAction(self, 
            pOptionSelfCloseAction: CThostFtdcOptionSelfCloseActionField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnRtnCombAction(self, 
            pCombAction: CThostFtdcCombActionField,
        ) -> None:
        
        ...
    
    def OnErrRtnCombActionInsert(self, 
            pInputCombAction: CThostFtdcInputCombActionField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnRspQryContractBank(self, 
            pContractBank: CThostFtdcContractBankField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryParkedOrder(self, 
            pParkedOrder: CThostFtdcParkedOrderField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryParkedOrderAction(self, 
            pParkedOrderAction: CThostFtdcParkedOrderActionField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryTradingNotice(self, 
            pTradingNotice: CThostFtdcTradingNoticeField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryBrokerTradingParams(self, 
            pBrokerTradingParams: CThostFtdcBrokerTradingParamsField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQryBrokerTradingAlgos(self, 
            pBrokerTradingAlgos: CThostFtdcBrokerTradingAlgosField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQueryCFMMCTradingAccountToken(self, 
            pQueryCFMMCTradingAccountToken: CThostFtdcQueryCFMMCTradingAccountTokenField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRtnFromBankToFutureByBank(self, 
            pRspTransfer: CThostFtdcRspTransferField,
        ) -> None:
        
        ...
    
    def OnRtnFromFutureToBankByBank(self, 
            pRspTransfer: CThostFtdcRspTransferField,
        ) -> None:
        
        ...
    
    def OnRtnRepealFromBankToFutureByBank(self, 
            pRspRepeal: CThostFtdcRspRepealField,
        ) -> None:
        
        ...
    
    def OnRtnRepealFromFutureToBankByBank(self, 
            pRspRepeal: CThostFtdcRspRepealField,
        ) -> None:
        
        ...
    
    def OnRtnFromBankToFutureByFuture(self, 
            pRspTransfer: CThostFtdcRspTransferField,
        ) -> None:
        
        ...
    
    def OnRtnFromFutureToBankByFuture(self, 
            pRspTransfer: CThostFtdcRspTransferField,
        ) -> None:
        
        ...
    
    def OnRtnRepealFromBankToFutureByFutureManual(self, 
            pRspRepeal: CThostFtdcRspRepealField,
        ) -> None:
        
        ...
    
    def OnRtnRepealFromFutureToBankByFutureManual(self, 
            pRspRepeal: CThostFtdcRspRepealField,
        ) -> None:
        
        ...
    
    def OnRtnQueryBankBalanceByFuture(self, 
            pNotifyQueryAccount: CThostFtdcNotifyQueryAccountField,
        ) -> None:
        
        ...
    
    def OnErrRtnBankToFutureByFuture(self, 
            pReqTransfer: CThostFtdcReqTransferField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnFutureToBankByFuture(self, 
            pReqTransfer: CThostFtdcReqTransferField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnRepealBankToFutureByFutureManual(self, 
            pReqRepeal: CThostFtdcReqRepealField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnRepealFutureToBankByFutureManual(self, 
            pReqRepeal: CThostFtdcReqRepealField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnErrRtnQueryBankBalanceByFuture(self, 
            pReqQueryAccount: CThostFtdcReqQueryAccountField,
            pRspInfo: CThostFtdcRspInfoField,
        ) -> None:
        
        ...
    
    def OnRtnRepealFromBankToFutureByFuture(self, 
            pRspRepeal: CThostFtdcRspRepealField,
        ) -> None:
        
        ...
    
    def OnRtnRepealFromFutureToBankByFuture(self, 
            pRspRepeal: CThostFtdcRspRepealField,
        ) -> None:
        
        ...
    
    def OnRspFromBankToFutureByFuture(self, 
            pReqTransfer: CThostFtdcReqTransferField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspFromFutureToBankByFuture(self, 
            pReqTransfer: CThostFtdcReqTransferField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspQueryBankAccountMoneyByFuture(self, 
            pReqQueryAccount: CThostFtdcReqQueryAccountField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRtnOpenAccountByBank(self, 
            pOpenAccount: CThostFtdcOpenAccountField,
        ) -> None:
        
        ...
    
    def OnRtnCancelAccountByBank(self, 
            pCancelAccount: CThostFtdcCancelAccountField,
        ) -> None:
        
        ...
    
    def OnRtnChangeAccountByBank(self, 
            pChangeAccount: CThostFtdcChangeAccountField,
        ) -> None:
        
        ...
    
    ...
    ...
class CThostFtdcTraderApi:
    
    @staticmethod
    def CreateFtdcTraderApi(
            pszFlowPath: str,
        ) -> CThostFtdcTraderApi:
        
        ...
    
    @staticmethod
    def GetApiVersion(
        ) -> str:
        
        ...
    
    def Release(self, 
        ) -> None:
        
        ...
    
    def Init(self, 
        ) -> None:
        
        ...
    
    def Join(self, 
        ) -> int:
        
        ...
    
    def GetTradingDay(self, 
        ) -> str:
        
        ...
    
    def RegisterFront(self, 
            pszFrontAddress: str,
        ) -> None:
        
        ...
    
    def RegisterNameServer(self, 
            pszNsAddress: str,
        ) -> None:
        
        ...
    
    def RegisterFensUserInfo(self, 
            pFensUserInfo: CThostFtdcFensUserInfoField,
        ) -> None:
        
        ...
    
    def RegisterSpi(self, 
            pSpi: CThostFtdcTraderSpi,
        ) -> None:
        
        ...
    
    def SubscribePrivateTopic(self, 
            nResumeType: THOST_TE_RESUME_TYPE,
        ) -> None:
        
        ...
    
    def SubscribePublicTopic(self, 
            nResumeType: THOST_TE_RESUME_TYPE,
        ) -> None:
        
        ...
    
    def ReqAuthenticate(self, 
            pReqAuthenticateField: CThostFtdcReqAuthenticateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def RegisterUserSystemInfo(self, 
            pUserSystemInfo: CThostFtdcUserSystemInfoField,
        ) -> int:
        
        ...
    
    def SubmitUserSystemInfo(self, 
            pUserSystemInfo: CThostFtdcUserSystemInfoField,
        ) -> int:
        
        ...
    
    def ReqUserLogin(self, 
            pReqUserLoginField: CThostFtdcReqUserLoginField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqUserLogout(self, 
            pUserLogout: CThostFtdcUserLogoutField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqUserPasswordUpdate(self, 
            pUserPasswordUpdate: CThostFtdcUserPasswordUpdateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqTradingAccountPasswordUpdate(self, 
            pTradingAccountPasswordUpdate: CThostFtdcTradingAccountPasswordUpdateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqUserAuthMethod(self, 
            pReqUserAuthMethod: CThostFtdcReqUserAuthMethodField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqGenUserCaptcha(self, 
            pReqGenUserCaptcha: CThostFtdcReqGenUserCaptchaField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqGenUserText(self, 
            pReqGenUserText: CThostFtdcReqGenUserTextField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqUserLoginWithCaptcha(self, 
            pReqUserLoginWithCaptcha: CThostFtdcReqUserLoginWithCaptchaField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqUserLoginWithText(self, 
            pReqUserLoginWithText: CThostFtdcReqUserLoginWithTextField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqUserLoginWithOTP(self, 
            pReqUserLoginWithOTP: CThostFtdcReqUserLoginWithOTPField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqOrderInsert(self, 
            pInputOrder: CThostFtdcInputOrderField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqParkedOrderInsert(self, 
            pParkedOrder: CThostFtdcParkedOrderField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqParkedOrderAction(self, 
            pParkedOrderAction: CThostFtdcParkedOrderActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqOrderAction(self, 
            pInputOrderAction: CThostFtdcInputOrderActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQueryMaxOrderVolume(self, 
            pQueryMaxOrderVolume: CThostFtdcQueryMaxOrderVolumeField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqSettlementInfoConfirm(self, 
            pSettlementInfoConfirm: CThostFtdcSettlementInfoConfirmField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqRemoveParkedOrder(self, 
            pRemoveParkedOrder: CThostFtdcRemoveParkedOrderField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqRemoveParkedOrderAction(self, 
            pRemoveParkedOrderAction: CThostFtdcRemoveParkedOrderActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqExecOrderInsert(self, 
            pInputExecOrder: CThostFtdcInputExecOrderField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqExecOrderAction(self, 
            pInputExecOrderAction: CThostFtdcInputExecOrderActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqForQuoteInsert(self, 
            pInputForQuote: CThostFtdcInputForQuoteField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQuoteInsert(self, 
            pInputQuote: CThostFtdcInputQuoteField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQuoteAction(self, 
            pInputQuoteAction: CThostFtdcInputQuoteActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqBatchOrderAction(self, 
            pInputBatchOrderAction: CThostFtdcInputBatchOrderActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqOptionSelfCloseInsert(self, 
            pInputOptionSelfClose: CThostFtdcInputOptionSelfCloseField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqOptionSelfCloseAction(self, 
            pInputOptionSelfCloseAction: CThostFtdcInputOptionSelfCloseActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqCombActionInsert(self, 
            pInputCombAction: CThostFtdcInputCombActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryOrder(self, 
            pQryOrder: CThostFtdcQryOrderField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryTrade(self, 
            pQryTrade: CThostFtdcQryTradeField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInvestorPosition(self, 
            pQryInvestorPosition: CThostFtdcQryInvestorPositionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryTradingAccount(self, 
            pQryTradingAccount: CThostFtdcQryTradingAccountField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInvestor(self, 
            pQryInvestor: CThostFtdcQryInvestorField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryTradingCode(self, 
            pQryTradingCode: CThostFtdcQryTradingCodeField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInstrumentMarginRate(self, 
            pQryInstrumentMarginRate: CThostFtdcQryInstrumentMarginRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInstrumentCommissionRate(self, 
            pQryInstrumentCommissionRate: CThostFtdcQryInstrumentCommissionRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryExchange(self, 
            pQryExchange: CThostFtdcQryExchangeField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryProduct(self, 
            pQryProduct: CThostFtdcQryProductField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInstrument(self, 
            pQryInstrument: CThostFtdcQryInstrumentField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryDepthMarketData(self, 
            pQryDepthMarketData: CThostFtdcQryDepthMarketDataField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQrySettlementInfo(self, 
            pQrySettlementInfo: CThostFtdcQrySettlementInfoField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryTransferBank(self, 
            pQryTransferBank: CThostFtdcQryTransferBankField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInvestorPositionDetail(self, 
            pQryInvestorPositionDetail: CThostFtdcQryInvestorPositionDetailField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryNotice(self, 
            pQryNotice: CThostFtdcQryNoticeField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQrySettlementInfoConfirm(self, 
            pQrySettlementInfoConfirm: CThostFtdcQrySettlementInfoConfirmField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInvestorPositionCombineDetail(self, 
            pQryInvestorPositionCombineDetail: CThostFtdcQryInvestorPositionCombineDetailField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryCFMMCTradingAccountKey(self, 
            pQryCFMMCTradingAccountKey: CThostFtdcQryCFMMCTradingAccountKeyField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryEWarrantOffset(self, 
            pQryEWarrantOffset: CThostFtdcQryEWarrantOffsetField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInvestorProductGroupMargin(self, 
            pQryInvestorProductGroupMargin: CThostFtdcQryInvestorProductGroupMarginField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryExchangeMarginRate(self, 
            pQryExchangeMarginRate: CThostFtdcQryExchangeMarginRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryExchangeMarginRateAdjust(self, 
            pQryExchangeMarginRateAdjust: CThostFtdcQryExchangeMarginRateAdjustField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryExchangeRate(self, 
            pQryExchangeRate: CThostFtdcQryExchangeRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQrySecAgentACIDMap(self, 
            pQrySecAgentACIDMap: CThostFtdcQrySecAgentACIDMapField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryProductExchRate(self, 
            pQryProductExchRate: CThostFtdcQryProductExchRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryProductGroup(self, 
            pQryProductGroup: CThostFtdcQryProductGroupField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryMMInstrumentCommissionRate(self, 
            pQryMMInstrumentCommissionRate: CThostFtdcQryMMInstrumentCommissionRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryMMOptionInstrCommRate(self, 
            pQryMMOptionInstrCommRate: CThostFtdcQryMMOptionInstrCommRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInstrumentOrderCommRate(self, 
            pQryInstrumentOrderCommRate: CThostFtdcQryInstrumentOrderCommRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQrySecAgentTradingAccount(self, 
            pQryTradingAccount: CThostFtdcQryTradingAccountField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQrySecAgentCheckMode(self, 
            pQrySecAgentCheckMode: CThostFtdcQrySecAgentCheckModeField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQrySecAgentTradeInfo(self, 
            pQrySecAgentTradeInfo: CThostFtdcQrySecAgentTradeInfoField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryOptionInstrTradeCost(self, 
            pQryOptionInstrTradeCost: CThostFtdcQryOptionInstrTradeCostField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryOptionInstrCommRate(self, 
            pQryOptionInstrCommRate: CThostFtdcQryOptionInstrCommRateField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryExecOrder(self, 
            pQryExecOrder: CThostFtdcQryExecOrderField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryForQuote(self, 
            pQryForQuote: CThostFtdcQryForQuoteField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryQuote(self, 
            pQryQuote: CThostFtdcQryQuoteField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryOptionSelfClose(self, 
            pQryOptionSelfClose: CThostFtdcQryOptionSelfCloseField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryInvestUnit(self, 
            pQryInvestUnit: CThostFtdcQryInvestUnitField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryCombInstrumentGuard(self, 
            pQryCombInstrumentGuard: CThostFtdcQryCombInstrumentGuardField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryCombAction(self, 
            pQryCombAction: CThostFtdcQryCombActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryTransferSerial(self, 
            pQryTransferSerial: CThostFtdcQryTransferSerialField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryAccountregister(self, 
            pQryAccountregister: CThostFtdcQryAccountregisterField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryContractBank(self, 
            pQryContractBank: CThostFtdcQryContractBankField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryParkedOrder(self, 
            pQryParkedOrder: CThostFtdcQryParkedOrderField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryParkedOrderAction(self, 
            pQryParkedOrderAction: CThostFtdcQryParkedOrderActionField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryTradingNotice(self, 
            pQryTradingNotice: CThostFtdcQryTradingNoticeField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryBrokerTradingParams(self, 
            pQryBrokerTradingParams: CThostFtdcQryBrokerTradingParamsField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQryBrokerTradingAlgos(self, 
            pQryBrokerTradingAlgos: CThostFtdcQryBrokerTradingAlgosField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQueryCFMMCTradingAccountToken(self, 
            pQueryCFMMCTradingAccountToken: CThostFtdcQueryCFMMCTradingAccountTokenField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqFromBankToFutureByFuture(self, 
            pReqTransfer: CThostFtdcReqTransferField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqFromFutureToBankByFuture(self, 
            pReqTransfer: CThostFtdcReqTransferField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqQueryBankAccountMoneyByFuture(self, 
            pReqQueryAccount: CThostFtdcReqQueryAccountField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    ...
    ...
class CThostFtdcMdSpi:
    
    def OnFrontConnected(self, 
        ) -> None:
        
        ...
    
    def OnFrontDisconnected(self, 
            nReason: int,
        ) -> None:
        
        ...
    
    def OnHeartBeatWarning(self, 
            nTimeLapse: int,
        ) -> None:
        
        ...
    
    def OnRspUserLogin(self, 
            pRspUserLogin: CThostFtdcRspUserLoginField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspUserLogout(self, 
            pUserLogout: CThostFtdcUserLogoutField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspError(self, 
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspSubMarketData(self, 
            pSpecificInstrument: CThostFtdcSpecificInstrumentField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspUnSubMarketData(self, 
            pSpecificInstrument: CThostFtdcSpecificInstrumentField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspSubForQuoteRsp(self, 
            pSpecificInstrument: CThostFtdcSpecificInstrumentField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRspUnSubForQuoteRsp(self, 
            pSpecificInstrument: CThostFtdcSpecificInstrumentField,
            pRspInfo: CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
        ) -> None:
        
        ...
    
    def OnRtnDepthMarketData(self, 
            pDepthMarketData: CThostFtdcDepthMarketDataField,
        ) -> None:
        
        ...
    
    def OnRtnForQuoteRsp(self, 
            pForQuoteRsp: CThostFtdcForQuoteRspField,
        ) -> None:
        
        ...
    
    ...
    ...
class CThostFtdcMdApi:
    
    @staticmethod
    def CreateFtdcMdApi(
            pszFlowPath: str,
            bIsUsingUdp: bool,
            bIsMulticast: bool,
        ) -> CThostFtdcMdApi:
        
        ...
    
    @staticmethod
    def GetApiVersion(
        ) -> str:
        
        ...
    
    def Release(self, 
        ) -> None:
        
        ...
    
    def Init(self, 
        ) -> None:
        
        ...
    
    def Join(self, 
        ) -> int:
        
        ...
    
    def GetTradingDay(self, 
        ) -> str:
        
        ...
    
    def RegisterFront(self, 
            pszFrontAddress: str,
        ) -> None:
        
        ...
    
    def RegisterNameServer(self, 
            pszNsAddress: str,
        ) -> None:
        
        ...
    
    def RegisterFensUserInfo(self, 
            pFensUserInfo: CThostFtdcFensUserInfoField,
        ) -> None:
        
        ...
    
    def RegisterSpi(self, 
            pSpi: CThostFtdcMdSpi,
        ) -> None:
        
        ...
    
    def SubscribeMarketData(self, 
            ppInstrumentID: char *[],  # unknown what to wrap in py
            nCount: int,
        ) -> int:
        
        ...
    
    def UnSubscribeMarketData(self, 
            ppInstrumentID: char *[],  # unknown what to wrap in py
            nCount: int,
        ) -> int:
        
        ...
    
    def SubscribeForQuoteRsp(self, 
            ppInstrumentID: char *[],  # unknown what to wrap in py
            nCount: int,
        ) -> int:
        
        ...
    
    def UnSubscribeForQuoteRsp(self, 
            ppInstrumentID: char *[],  # unknown what to wrap in py
            nCount: int,
        ) -> int:
        
        ...
    
    def ReqUserLogin(self, 
            pReqUserLoginField: CThostFtdcReqUserLoginField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    def ReqUserLogout(self, 
            pUserLogout: CThostFtdcUserLogoutField,
            nRequestID: int,
        ) -> int:
        
        ...
    
    ...
    ...
THOST_FTDC_EXP_Normal: int = 48
THOST_FTDC_EXP_GenOrderByTrade: int = 49
THOST_FTDC_ICT_EID: int = 48
THOST_FTDC_ICT_IDCard: int = 49
THOST_FTDC_ICT_OfficerIDCard: int = 50
THOST_FTDC_ICT_PoliceIDCard: int = 51
THOST_FTDC_ICT_SoldierIDCard: int = 52
THOST_FTDC_ICT_HouseholdRegister: int = 53
THOST_FTDC_ICT_Passport: int = 54
THOST_FTDC_ICT_TaiwanCompatriotIDCard: int = 55
THOST_FTDC_ICT_HomeComingCard: int = 56
THOST_FTDC_ICT_LicenseNo: int = 57
THOST_FTDC_ICT_TaxNo: int = 65
THOST_FTDC_ICT_HMMainlandTravelPermit: int = 66
THOST_FTDC_ICT_TwMainlandTravelPermit: int = 67
THOST_FTDC_ICT_DrivingLicense: int = 68
THOST_FTDC_ICT_SocialID: int = 70
THOST_FTDC_ICT_LocalID: int = 71
THOST_FTDC_ICT_BusinessRegistration: int = 72
THOST_FTDC_ICT_HKMCIDCard: int = 73
THOST_FTDC_ICT_AccountsPermits: int = 74
THOST_FTDC_ICT_FrgPrmtRdCard: int = 75
THOST_FTDC_ICT_CptMngPrdLetter: int = 76
THOST_FTDC_ICT_OtherCard: int = 120
THOST_FTDC_IR_All: int = 49
THOST_FTDC_IR_Group: int = 50
THOST_FTDC_IR_Single: int = 51
THOST_FTDC_DR_All: int = 49
THOST_FTDC_DR_Group: int = 50
THOST_FTDC_DR_Single: int = 51
THOST_FTDC_DS_Asynchronous: int = 49
THOST_FTDC_DS_Synchronizing: int = 50
THOST_FTDC_DS_Synchronized: int = 51
THOST_FTDC_BDS_Synchronized: int = 49
THOST_FTDC_BDS_Synchronizing: int = 50
THOST_FTDC_ECS_NoConnection: int = 49
THOST_FTDC_ECS_QryInstrumentSent: int = 50
THOST_FTDC_ECS_GotInformation: int = 57
THOST_FTDC_TCS_NotConnected: int = 49
THOST_FTDC_TCS_Connected: int = 50
THOST_FTDC_TCS_QryInstrumentSent: int = 51
THOST_FTDC_TCS_SubPrivateFlow: int = 52
THOST_FTDC_FC_DataAsync: int = 49
THOST_FTDC_FC_ForceUserLogout: int = 50
THOST_FTDC_FC_UserPasswordUpdate: int = 51
THOST_FTDC_FC_BrokerPasswordUpdate: int = 52
THOST_FTDC_FC_InvestorPasswordUpdate: int = 53
THOST_FTDC_FC_OrderInsert: int = 54
THOST_FTDC_FC_OrderAction: int = 55
THOST_FTDC_FC_SyncSystemData: int = 56
THOST_FTDC_FC_SyncBrokerData: int = 57
THOST_FTDC_FC_BachSyncBrokerData: int = 65
THOST_FTDC_FC_SuperQuery: int = 66
THOST_FTDC_FC_ParkedOrderInsert: int = 67
THOST_FTDC_FC_ParkedOrderAction: int = 68
THOST_FTDC_FC_SyncOTP: int = 69
THOST_FTDC_FC_DeleteOrder: int = 70
THOST_FTDC_BFC_ForceUserLogout: int = 49
THOST_FTDC_BFC_UserPasswordUpdate: int = 50
THOST_FTDC_BFC_SyncBrokerData: int = 51
THOST_FTDC_BFC_BachSyncBrokerData: int = 52
THOST_FTDC_BFC_OrderInsert: int = 53
THOST_FTDC_BFC_OrderAction: int = 54
THOST_FTDC_BFC_AllQuery: int = 55
THOST_FTDC_BFC_log: int = 97
THOST_FTDC_BFC_BaseQry: int = 98
THOST_FTDC_BFC_TradeQry: int = 99
THOST_FTDC_BFC_Trade: int = 100
THOST_FTDC_BFC_Virement: int = 101
THOST_FTDC_BFC_Risk: int = 102
THOST_FTDC_BFC_Session: int = 103
THOST_FTDC_BFC_RiskNoticeCtl: int = 104
THOST_FTDC_BFC_RiskNotice: int = 105
THOST_FTDC_BFC_BrokerDeposit: int = 106
THOST_FTDC_BFC_QueryFund: int = 107
THOST_FTDC_BFC_QueryOrder: int = 108
THOST_FTDC_BFC_QueryTrade: int = 109
THOST_FTDC_BFC_QueryPosition: int = 110
THOST_FTDC_BFC_QueryMarketData: int = 111
THOST_FTDC_BFC_QueryUserEvent: int = 112
THOST_FTDC_BFC_QueryRiskNotify: int = 113
THOST_FTDC_BFC_QueryFundChange: int = 114
THOST_FTDC_BFC_QueryInvestor: int = 115
THOST_FTDC_BFC_QueryTradingCode: int = 116
THOST_FTDC_BFC_ForceClose: int = 117
THOST_FTDC_BFC_PressTest: int = 118
THOST_FTDC_BFC_RemainCalc: int = 119
THOST_FTDC_BFC_NetPositionInd: int = 120
THOST_FTDC_BFC_RiskPredict: int = 121
THOST_FTDC_BFC_DataExport: int = 122
THOST_FTDC_BFC_RiskTargetSetup: int = 65
THOST_FTDC_BFC_MarketDataWarn: int = 66
THOST_FTDC_BFC_QryBizNotice: int = 67
THOST_FTDC_BFC_CfgBizNotice: int = 68
THOST_FTDC_BFC_SyncOTP: int = 69
THOST_FTDC_BFC_SendBizNotice: int = 70
THOST_FTDC_BFC_CfgRiskLevelStd: int = 71
THOST_FTDC_BFC_TbCommand: int = 72
THOST_FTDC_BFC_DeleteOrder: int = 74
THOST_FTDC_BFC_ParkedOrderInsert: int = 75
THOST_FTDC_BFC_ParkedOrderAction: int = 76
THOST_FTDC_BFC_ExecOrderNoCheck: int = 77
THOST_FTDC_BFC_Designate: int = 78
THOST_FTDC_BFC_StockDisposal: int = 79
THOST_FTDC_BFC_BrokerDepositWarn: int = 81
THOST_FTDC_BFC_CoverWarn: int = 83
THOST_FTDC_BFC_PreExecOrder: int = 84
THOST_FTDC_BFC_ExecOrderRisk: int = 80
THOST_FTDC_BFC_PosiLimitWarn: int = 85
THOST_FTDC_BFC_QryPosiLimit: int = 86
THOST_FTDC_BFC_FBSign: int = 87
THOST_FTDC_BFC_FBAccount: int = 88
THOST_FTDC_OAS_Submitted: int = 97
THOST_FTDC_OAS_Accepted: int = 98
THOST_FTDC_OAS_Rejected: int = 99
THOST_FTDC_OST_AllTraded: int = 48
THOST_FTDC_OST_PartTradedQueueing: int = 49
THOST_FTDC_OST_PartTradedNotQueueing: int = 50
THOST_FTDC_OST_NoTradeQueueing: int = 51
THOST_FTDC_OST_NoTradeNotQueueing: int = 52
THOST_FTDC_OST_Canceled: int = 53
THOST_FTDC_OST_Unknown: int = 97
THOST_FTDC_OST_NotTouched: int = 98
THOST_FTDC_OST_Touched: int = 99
THOST_FTDC_OSS_InsertSubmitted: int = 48
THOST_FTDC_OSS_CancelSubmitted: int = 49
THOST_FTDC_OSS_ModifySubmitted: int = 50
THOST_FTDC_OSS_Accepted: int = 51
THOST_FTDC_OSS_InsertRejected: int = 52
THOST_FTDC_OSS_CancelRejected: int = 53
THOST_FTDC_OSS_ModifyRejected: int = 54
THOST_FTDC_PSD_Today: int = 49
THOST_FTDC_PSD_History: int = 50
THOST_FTDC_PDT_UseHistory: int = 49
THOST_FTDC_PDT_NoUseHistory: int = 50
THOST_FTDC_ER_Broker: int = 49
THOST_FTDC_ER_Host: int = 50
THOST_FTDC_ER_Maker: int = 51
THOST_FTDC_PC_Futures: int = 49
THOST_FTDC_PC_Options: int = 50
THOST_FTDC_PC_Combination: int = 51
THOST_FTDC_PC_Spot: int = 52
THOST_FTDC_PC_EFP: int = 53
THOST_FTDC_PC_SpotOption: int = 54
THOST_FTDC_IP_NotStart: int = 48
THOST_FTDC_IP_Started: int = 49
THOST_FTDC_IP_Pause: int = 50
THOST_FTDC_IP_Expired: int = 51
THOST_FTDC_D_Buy: int = 48
THOST_FTDC_D_Sell: int = 49
THOST_FTDC_PT_Net: int = 49
THOST_FTDC_PT_Gross: int = 50
THOST_FTDC_PD_Net: int = 49
THOST_FTDC_PD_Long: int = 50
THOST_FTDC_PD_Short: int = 51
THOST_FTDC_SS_NonActive: int = 49
THOST_FTDC_SS_Startup: int = 50
THOST_FTDC_SS_Operating: int = 51
THOST_FTDC_SS_Settlement: int = 52
THOST_FTDC_SS_SettlementFinished: int = 53
THOST_FTDC_RA_Trade: int = 48
THOST_FTDC_RA_Settlement: int = 49
THOST_FTDC_HF_Speculation: int = 49
THOST_FTDC_HF_Arbitrage: int = 50
THOST_FTDC_HF_Hedge: int = 51
THOST_FTDC_HF_MarketMaker: int = 53
THOST_FTDC_BHF_Speculation: int = 49
THOST_FTDC_BHF_Arbitrage: int = 50
THOST_FTDC_BHF_Hedge: int = 51
THOST_FTDC_CIDT_Speculation: int = 49
THOST_FTDC_CIDT_Arbitrage: int = 50
THOST_FTDC_CIDT_Hedge: int = 51
THOST_FTDC_CIDT_MarketMaker: int = 53
THOST_FTDC_OPT_AnyPrice: int = 49
THOST_FTDC_OPT_LimitPrice: int = 50
THOST_FTDC_OPT_BestPrice: int = 51
THOST_FTDC_OPT_LastPrice: int = 52
THOST_FTDC_OPT_LastPricePlusOneTicks: int = 53
THOST_FTDC_OPT_LastPricePlusTwoTicks: int = 54
THOST_FTDC_OPT_LastPricePlusThreeTicks: int = 55
THOST_FTDC_OPT_AskPrice1: int = 56
THOST_FTDC_OPT_AskPrice1PlusOneTicks: int = 57
THOST_FTDC_OPT_AskPrice1PlusTwoTicks: int = 65
THOST_FTDC_OPT_AskPrice1PlusThreeTicks: int = 66
THOST_FTDC_OPT_BidPrice1: int = 67
THOST_FTDC_OPT_BidPrice1PlusOneTicks: int = 68
THOST_FTDC_OPT_BidPrice1PlusTwoTicks: int = 69
THOST_FTDC_OPT_BidPrice1PlusThreeTicks: int = 70
THOST_FTDC_OPT_FiveLevelPrice: int = 71
THOST_FTDC_OF_Open: int = 48
THOST_FTDC_OF_Close: int = 49
THOST_FTDC_OF_ForceClose: int = 50
THOST_FTDC_OF_CloseToday: int = 51
THOST_FTDC_OF_CloseYesterday: int = 52
THOST_FTDC_OF_ForceOff: int = 53
THOST_FTDC_OF_LocalForceClose: int = 54
THOST_FTDC_FCC_NotForceClose: int = 48
THOST_FTDC_FCC_LackDeposit: int = 49
THOST_FTDC_FCC_ClientOverPositionLimit: int = 50
THOST_FTDC_FCC_MemberOverPositionLimit: int = 51
THOST_FTDC_FCC_NotMultiple: int = 52
THOST_FTDC_FCC_Violation: int = 53
THOST_FTDC_FCC_Other: int = 54
THOST_FTDC_FCC_PersonDeliv: int = 55
THOST_FTDC_ORDT_Normal: int = 48
THOST_FTDC_ORDT_DeriveFromQuote: int = 49
THOST_FTDC_ORDT_DeriveFromCombination: int = 50
THOST_FTDC_ORDT_Combination: int = 51
THOST_FTDC_ORDT_ConditionalOrder: int = 52
THOST_FTDC_ORDT_Swap: int = 53
THOST_FTDC_ORDT_DeriveFromEFP: int = 54
THOST_FTDC_TC_IOC: int = 49
THOST_FTDC_TC_GFS: int = 50
THOST_FTDC_TC_GFD: int = 51
THOST_FTDC_TC_GTD: int = 52
THOST_FTDC_TC_GTC: int = 53
THOST_FTDC_TC_GFA: int = 54
THOST_FTDC_VC_AV: int = 49
THOST_FTDC_VC_MV: int = 50
THOST_FTDC_VC_CV: int = 51
THOST_FTDC_CC_Immediately: int = 49
THOST_FTDC_CC_Touch: int = 50
THOST_FTDC_CC_TouchProfit: int = 51
THOST_FTDC_CC_ParkedOrder: int = 52
THOST_FTDC_CC_LastPriceGreaterThanStopPrice: int = 53
THOST_FTDC_CC_LastPriceGreaterEqualStopPrice: int = 54
THOST_FTDC_CC_LastPriceLesserThanStopPrice: int = 55
THOST_FTDC_CC_LastPriceLesserEqualStopPrice: int = 56
THOST_FTDC_CC_AskPriceGreaterThanStopPrice: int = 57
THOST_FTDC_CC_AskPriceGreaterEqualStopPrice: int = 65
THOST_FTDC_CC_AskPriceLesserThanStopPrice: int = 66
THOST_FTDC_CC_AskPriceLesserEqualStopPrice: int = 67
THOST_FTDC_CC_BidPriceGreaterThanStopPrice: int = 68
THOST_FTDC_CC_BidPriceGreaterEqualStopPrice: int = 69
THOST_FTDC_CC_BidPriceLesserThanStopPrice: int = 70
THOST_FTDC_CC_BidPriceLesserEqualStopPrice: int = 72
THOST_FTDC_AF_Delete: int = 48
THOST_FTDC_AF_Modify: int = 51
THOST_FTDC_TR_Allow: int = 48
THOST_FTDC_TR_CloseOnly: int = 49
THOST_FTDC_TR_Forbidden: int = 50
THOST_FTDC_OSRC_Participant: int = 48
THOST_FTDC_OSRC_Administrator: int = 49
THOST_FTDC_TRDT_SplitCombination: int = 35
THOST_FTDC_TRDT_Common: int = 48
THOST_FTDC_TRDT_OptionsExecution: int = 49
THOST_FTDC_TRDT_OTC: int = 50
THOST_FTDC_TRDT_EFPDerived: int = 51
THOST_FTDC_TRDT_CombinationDerived: int = 52
THOST_FTDC_PSRC_LastPrice: int = 48
THOST_FTDC_PSRC_Buy: int = 49
THOST_FTDC_PSRC_Sell: int = 50
THOST_FTDC_IS_BeforeTrading: int = 48
THOST_FTDC_IS_NoTrading: int = 49
THOST_FTDC_IS_Continous: int = 50
THOST_FTDC_IS_AuctionOrdering: int = 51
THOST_FTDC_IS_AuctionBalance: int = 52
THOST_FTDC_IS_AuctionMatch: int = 53
THOST_FTDC_IS_Closed: int = 54
THOST_FTDC_IER_Automatic: int = 49
THOST_FTDC_IER_Manual: int = 50
THOST_FTDC_IER_Fuse: int = 51
THOST_FTDC_BS_NoUpload: int = 49
THOST_FTDC_BS_Uploaded: int = 50
THOST_FTDC_BS_Failed: int = 51
THOST_FTDC_RS_All: int = 49
THOST_FTDC_RS_ByProduct: int = 50
THOST_FTDC_RP_ByVolume: int = 49
THOST_FTDC_RP_ByFeeOnHand: int = 50
THOST_FTDC_RL_Level1: int = 49
THOST_FTDC_RL_Level2: int = 50
THOST_FTDC_RL_Level3: int = 51
THOST_FTDC_RL_Level4: int = 52
THOST_FTDC_RL_Level5: int = 53
THOST_FTDC_RL_Level6: int = 54
THOST_FTDC_RL_Level7: int = 55
THOST_FTDC_RL_Level8: int = 56
THOST_FTDC_RL_Level9: int = 57
THOST_FTDC_RSD_ByPeriod: int = 49
THOST_FTDC_RSD_ByStandard: int = 50
THOST_FTDC_MT_Out: int = 48
THOST_FTDC_MT_In: int = 49
THOST_FTDC_ISPI_MortgageRatio: int = 52
THOST_FTDC_ISPI_MarginWay: int = 53
THOST_FTDC_ISPI_BillDeposit: int = 57
THOST_FTDC_ESPI_MortgageRatio: int = 49
THOST_FTDC_ESPI_OtherFundItem: int = 50
THOST_FTDC_ESPI_OtherFundImport: int = 51
THOST_FTDC_ESPI_CFFEXMinPrepa: int = 54
THOST_FTDC_ESPI_CZCESettlementType: int = 55
THOST_FTDC_ESPI_ExchDelivFeeMode: int = 57
THOST_FTDC_ESPI_DelivFeeMode: int = 48
THOST_FTDC_ESPI_CZCEComMarginType: int = 65
THOST_FTDC_ESPI_DceComMarginType: int = 66
THOST_FTDC_ESPI_OptOutDisCountRate: int = 97
THOST_FTDC_ESPI_OptMiniGuarantee: int = 98
THOST_FTDC_SPI_InvestorIDMinLength: int = 49
THOST_FTDC_SPI_AccountIDMinLength: int = 50
THOST_FTDC_SPI_UserRightLogon: int = 51
THOST_FTDC_SPI_SettlementBillTrade: int = 52
THOST_FTDC_SPI_TradingCode: int = 53
THOST_FTDC_SPI_CheckFund: int = 54
THOST_FTDC_SPI_CommModelRight: int = 55
THOST_FTDC_SPI_MarginModelRight: int = 57
THOST_FTDC_SPI_IsStandardActive: int = 56
THOST_FTDC_SPI_UploadSettlementFile: int = 85
THOST_FTDC_SPI_DownloadCSRCFile: int = 68
THOST_FTDC_SPI_SettlementBillFile: int = 83
THOST_FTDC_SPI_CSRCOthersFile: int = 67
THOST_FTDC_SPI_InvestorPhoto: int = 80
THOST_FTDC_SPI_CSRCData: int = 82
THOST_FTDC_SPI_InvestorPwdModel: int = 73
THOST_FTDC_SPI_CFFEXInvestorSettleFile: int = 70
THOST_FTDC_SPI_InvestorIDType: int = 97
THOST_FTDC_SPI_FreezeMaxReMain: int = 114
THOST_FTDC_SPI_IsSync: int = 65
THOST_FTDC_SPI_RelieveOpenLimit: int = 79
THOST_FTDC_SPI_IsStandardFreeze: int = 88
THOST_FTDC_SPI_CZCENormalProductHedge: int = 66
THOST_FTDC_TPID_EncryptionStandard: int = 69
THOST_FTDC_TPID_RiskMode: int = 82
THOST_FTDC_TPID_RiskModeGlobal: int = 71
THOST_FTDC_TPID_modeEncode: int = 80
THOST_FTDC_TPID_tickMode: int = 84
THOST_FTDC_TPID_SingleUserSessionMaxNum: int = 83
THOST_FTDC_TPID_LoginFailMaxNum: int = 76
THOST_FTDC_TPID_IsAuthForce: int = 65
THOST_FTDC_TPID_IsPosiFreeze: int = 70
THOST_FTDC_TPID_IsPosiLimit: int = 77
THOST_FTDC_TPID_ForQuoteTimeInterval: int = 81
THOST_FTDC_TPID_IsFuturePosiLimit: int = 66
THOST_FTDC_TPID_IsFutureOrderFreq: int = 67
THOST_FTDC_TPID_IsExecOrderProfit: int = 72
THOST_FTDC_TPID_IsCheckBankAcc: int = 73
THOST_FTDC_TPID_PasswordDeadLine: int = 74
THOST_FTDC_TPID_IsStrongPassword: int = 75
THOST_FTDC_TPID_BalanceMorgage: int = 97
THOST_FTDC_TPID_MinPwdLen: int = 79
THOST_FTDC_TPID_LoginFailMaxNumForIP: int = 85
THOST_FTDC_TPID_PasswordPeriod: int = 86
THOST_FTDC_FI_SettlementFund: int = 70
THOST_FTDC_FI_Trade: int = 84
THOST_FTDC_FI_InvestorPosition: int = 80
THOST_FTDC_FI_SubEntryFund: int = 79
THOST_FTDC_FI_CZCECombinationPos: int = 67
THOST_FTDC_FI_CSRCData: int = 82
THOST_FTDC_FI_CZCEClose: int = 76
THOST_FTDC_FI_CZCENoClose: int = 78
THOST_FTDC_FI_PositionDtl: int = 68
THOST_FTDC_FI_OptionStrike: int = 83
THOST_FTDC_FI_SettlementPriceComparison: int = 77
THOST_FTDC_FI_NonTradePosChange: int = 66
THOST_FTDC_FUT_Settlement: int = 48
THOST_FTDC_FUT_Check: int = 49
THOST_FTDC_FFT_Txt: int = 48
THOST_FTDC_FFT_Zip: int = 49
THOST_FTDC_FFT_DBF: int = 50
THOST_FTDC_FUS_SucceedUpload: int = 49
THOST_FTDC_FUS_FailedUpload: int = 50
THOST_FTDC_FUS_SucceedLoad: int = 51
THOST_FTDC_FUS_PartSucceedLoad: int = 52
THOST_FTDC_FUS_FailedLoad: int = 53
THOST_FTDC_TD_Out: int = 48
THOST_FTDC_TD_In: int = 49
THOST_FTDC_SC_NoSpecialRule: int = 48
THOST_FTDC_SC_NoSpringFestival: int = 49
THOST_FTDC_IPT_LastSettlement: int = 49
THOST_FTDC_IPT_LaseClose: int = 50
THOST_FTDC_PLP_Active: int = 49
THOST_FTDC_PLP_NonActive: int = 50
THOST_FTDC_PLP_Canceled: int = 51
THOST_FTDC_DM_CashDeliv: int = 49
THOST_FTDC_DM_CommodityDeliv: int = 50
THOST_FTDC_FIOT_FundIO: int = 49
THOST_FTDC_FIOT_Transfer: int = 50
THOST_FTDC_FIOT_SwapCurrency: int = 51
THOST_FTDC_FT_Deposite: int = 49
THOST_FTDC_FT_ItemFund: int = 50
THOST_FTDC_FT_Company: int = 51
THOST_FTDC_FT_InnerTransfer: int = 52
THOST_FTDC_FD_In: int = 49
THOST_FTDC_FD_Out: int = 50
THOST_FTDC_FS_Record: int = 49
THOST_FTDC_FS_Check: int = 50
THOST_FTDC_FS_Charge: int = 51
THOST_FTDC_PS_None: int = 49
THOST_FTDC_PS_Publishing: int = 50
THOST_FTDC_PS_Published: int = 51
THOST_FTDC_ES_NonActive: int = 49
THOST_FTDC_ES_Startup: int = 50
THOST_FTDC_ES_Initialize: int = 51
THOST_FTDC_ES_Initialized: int = 52
THOST_FTDC_ES_Close: int = 53
THOST_FTDC_ES_Closed: int = 54
THOST_FTDC_ES_Settlement: int = 55
THOST_FTDC_STS_Initialize: int = 48
THOST_FTDC_STS_Settlementing: int = 49
THOST_FTDC_STS_Settlemented: int = 50
THOST_FTDC_STS_Finished: int = 51
THOST_FTDC_CT_Person: int = 48
THOST_FTDC_CT_Company: int = 49
THOST_FTDC_CT_Fund: int = 50
THOST_FTDC_CT_SpecialOrgan: int = 51
THOST_FTDC_CT_Asset: int = 52
THOST_FTDC_BT_Trade: int = 48
THOST_FTDC_BT_TradeSettle: int = 49
THOST_FTDC_FAS_Low: int = 49
THOST_FTDC_FAS_Normal: int = 50
THOST_FTDC_FAS_Focus: int = 51
THOST_FTDC_FAS_Risk: int = 52
THOST_FTDC_FAS_ByTrade: int = 49
THOST_FTDC_FAS_ByDeliv: int = 50
THOST_FTDC_FAS_None: int = 51
THOST_FTDC_FAS_FixFee: int = 52
THOST_FTDC_PWDT_Trade: int = 49
THOST_FTDC_PWDT_Account: int = 50
THOST_FTDC_AG_All: int = 49
THOST_FTDC_AG_OnlyLost: int = 50
THOST_FTDC_AG_OnlyGain: int = 51
THOST_FTDC_AG_None: int = 52
THOST_FTDC_ICP_Include: int = 48
THOST_FTDC_ICP_NotInclude: int = 50
THOST_FTDC_AWT_Enable: int = 48
THOST_FTDC_AWT_Disable: int = 50
THOST_FTDC_AWT_NoHoldEnable: int = 51
THOST_FTDC_FPWD_UnCheck: int = 48
THOST_FTDC_FPWD_Check: int = 49
THOST_FTDC_TT_BankToFuture: int = 48
THOST_FTDC_TT_FutureToBank: int = 49
THOST_FTDC_TVF_Invalid: int = 48
THOST_FTDC_TVF_Valid: int = 49
THOST_FTDC_TVF_Reverse: int = 50
THOST_FTDC_RN_CD: int = 48
THOST_FTDC_RN_ZT: int = 49
THOST_FTDC_RN_QT: int = 50
THOST_FTDC_SEX_None: int = 48
THOST_FTDC_SEX_Man: int = 49
THOST_FTDC_SEX_Woman: int = 50
THOST_FTDC_UT_Investor: int = 48
THOST_FTDC_UT_Operator: int = 49
THOST_FTDC_UT_SuperUser: int = 50
THOST_FTDC_RATETYPE_MarginRate: int = 50
THOST_FTDC_NOTETYPE_TradeSettleBill: int = 49
THOST_FTDC_NOTETYPE_TradeSettleMonth: int = 50
THOST_FTDC_NOTETYPE_CallMarginNotes: int = 51
THOST_FTDC_NOTETYPE_ForceCloseNotes: int = 52
THOST_FTDC_NOTETYPE_TradeNotes: int = 53
THOST_FTDC_NOTETYPE_DelivNotes: int = 54
THOST_FTDC_SBS_Day: int = 49
THOST_FTDC_SBS_Volume: int = 50
THOST_FTDC_ST_Day: int = 48
THOST_FTDC_ST_Month: int = 49
THOST_FTDC_URT_Logon: int = 49
THOST_FTDC_URT_Transfer: int = 50
THOST_FTDC_URT_EMail: int = 51
THOST_FTDC_URT_Fax: int = 52
THOST_FTDC_URT_ConditionOrder: int = 53
THOST_FTDC_MPT_PreSettlementPrice: int = 49
THOST_FTDC_MPT_SettlementPrice: int = 50
THOST_FTDC_MPT_AveragePrice: int = 51
THOST_FTDC_MPT_OpenPrice: int = 52
THOST_FTDC_BGS_None: int = 48
THOST_FTDC_BGS_NoGenerated: int = 49
THOST_FTDC_BGS_Generated: int = 50
THOST_FTDC_AT_HandlePositionAlgo: int = 49
THOST_FTDC_AT_FindMarginRateAlgo: int = 50
THOST_FTDC_HPA_Base: int = 49
THOST_FTDC_HPA_DCE: int = 50
THOST_FTDC_HPA_CZCE: int = 51
THOST_FTDC_FMRA_Base: int = 49
THOST_FTDC_FMRA_DCE: int = 50
THOST_FTDC_FMRA_CZCE: int = 51
THOST_FTDC_HTAA_Base: int = 49
THOST_FTDC_HTAA_DCE: int = 50
THOST_FTDC_HTAA_CZCE: int = 51
THOST_FTDC_PST_Order: int = 49
THOST_FTDC_PST_Open: int = 50
THOST_FTDC_PST_Fund: int = 51
THOST_FTDC_PST_Settlement: int = 52
THOST_FTDC_PST_Company: int = 53
THOST_FTDC_PST_Corporation: int = 54
THOST_FTDC_PST_LinkMan: int = 55
THOST_FTDC_PST_Ledger: int = 56
THOST_FTDC_PST_Trustee: int = 57
THOST_FTDC_PST_TrusteeCorporation: int = 65
THOST_FTDC_PST_TrusteeOpen: int = 66
THOST_FTDC_PST_TrusteeContact: int = 67
THOST_FTDC_PST_ForeignerRefer: int = 68
THOST_FTDC_PST_CorporationRefer: int = 69
THOST_FTDC_QIR_All: int = 49
THOST_FTDC_QIR_Group: int = 50
THOST_FTDC_QIR_Single: int = 51
THOST_FTDC_IRS_Normal: int = 49
THOST_FTDC_IRS_Warn: int = 50
THOST_FTDC_IRS_Call: int = 51
THOST_FTDC_IRS_Force: int = 52
THOST_FTDC_IRS_Exception: int = 53
THOST_FTDC_UET_Login: int = 49
THOST_FTDC_UET_Logout: int = 50
THOST_FTDC_UET_Trading: int = 51
THOST_FTDC_UET_TradingError: int = 52
THOST_FTDC_UET_UpdatePassword: int = 53
THOST_FTDC_UET_Authenticate: int = 54
THOST_FTDC_UET_Other: int = 57
THOST_FTDC_ICS_Close: int = 48
THOST_FTDC_ICS_CloseToday: int = 49
THOST_FTDC_SM_Non: int = 48
THOST_FTDC_SM_Instrument: int = 49
THOST_FTDC_SM_Product: int = 50
THOST_FTDC_SM_Investor: int = 51
THOST_FTDC_PAOS_NotSend: int = 49
THOST_FTDC_PAOS_Send: int = 50
THOST_FTDC_PAOS_Deleted: int = 51
THOST_FTDC_VDS_Dealing: int = 49
THOST_FTDC_VDS_DeaclSucceed: int = 50
THOST_FTDC_ORGS_Standard: int = 48
THOST_FTDC_ORGS_ESunny: int = 49
THOST_FTDC_ORGS_KingStarV6: int = 50
THOST_FTDC_VTS_NaturalDeal: int = 48
THOST_FTDC_VTS_SucceedEnd: int = 49
THOST_FTDC_VTS_FailedEND: int = 50
THOST_FTDC_VTS_Exception: int = 51
THOST_FTDC_VTS_ManualDeal: int = 52
THOST_FTDC_VTS_MesException: int = 53
THOST_FTDC_VTS_SysException: int = 54
THOST_FTDC_VBAT_BankBook: int = 49
THOST_FTDC_VBAT_BankCard: int = 50
THOST_FTDC_VBAT_CreditCard: int = 51
THOST_FTDC_VMS_Natural: int = 48
THOST_FTDC_VMS_Canceled: int = 57
THOST_FTDC_VAA_NoAvailAbility: int = 48
THOST_FTDC_VAA_AvailAbility: int = 49
THOST_FTDC_VAA_Repeal: int = 50
THOST_FTDC_VTC_BankBankToFuture: int = 53035779791614
THOST_FTDC_VTC_BankFutureToBank: int = 53035779791615
THOST_FTDC_VTC_FutureBankToFuture: int = 54113983700989
THOST_FTDC_VTC_FutureFutureToBank: int = 54113983700990
THOST_FTDC_GEN_Program: int = 48
THOST_FTDC_GEN_HandWork: int = 49
THOST_FTDC_CFMMCKK_REQUEST: int = 82
THOST_FTDC_CFMMCKK_AUTO: int = 65
THOST_FTDC_CFMMCKK_MANUAL: int = 77
THOST_FTDC_CFT_IDCard: int = 48
THOST_FTDC_CFT_Passport: int = 49
THOST_FTDC_CFT_OfficerIDCard: int = 50
THOST_FTDC_CFT_SoldierIDCard: int = 51
THOST_FTDC_CFT_HomeComingCard: int = 52
THOST_FTDC_CFT_HouseholdRegister: int = 53
THOST_FTDC_CFT_LicenseNo: int = 54
THOST_FTDC_CFT_InstitutionCodeCard: int = 55
THOST_FTDC_CFT_TempLicenseNo: int = 56
THOST_FTDC_CFT_NoEnterpriseLicenseNo: int = 57
THOST_FTDC_CFT_OtherCard: int = 120
THOST_FTDC_CFT_SuperDepAgree: int = 97
THOST_FTDC_FBC_Others: int = 48
THOST_FTDC_FBC_TransferDetails: int = 49
THOST_FTDC_FBC_CustAccStatus: int = 50
THOST_FTDC_FBC_AccountTradeDetails: int = 51
THOST_FTDC_FBC_FutureAccountChangeInfoDetails: int = 52
THOST_FTDC_FBC_CustMoneyDetail: int = 53
THOST_FTDC_FBC_CustCancelAccountInfo: int = 54
THOST_FTDC_FBC_CustMoneyResult: int = 55
THOST_FTDC_FBC_OthersExceptionResult: int = 56
THOST_FTDC_FBC_CustInterestNetMoneyDetails: int = 57
THOST_FTDC_FBC_CustMoneySendAndReceiveDetails: int = 97
THOST_FTDC_FBC_CorporationMoneyTotal: int = 98
THOST_FTDC_FBC_MainbodyMoneyTotal: int = 99
THOST_FTDC_FBC_MainPartMonitorData: int = 100
THOST_FTDC_FBC_PreparationMoney: int = 101
THOST_FTDC_FBC_BankMoneyMonitorData: int = 102
THOST_FTDC_CEC_Exchange: int = 49
THOST_FTDC_CEC_Cash: int = 50
THOST_FTDC_YNI_Yes: int = 48
THOST_FTDC_YNI_No: int = 49
THOST_FTDC_BLT_CurrentMoney: int = 48
THOST_FTDC_BLT_UsableMoney: int = 49
THOST_FTDC_BLT_FetchableMoney: int = 50
THOST_FTDC_BLT_FreezeMoney: int = 51
THOST_FTDC_GD_Unknown: int = 48
THOST_FTDC_GD_Male: int = 49
THOST_FTDC_GD_Female: int = 50
THOST_FTDC_FPF_BEN: int = 48
THOST_FTDC_FPF_OUR: int = 49
THOST_FTDC_FPF_SHA: int = 50
THOST_FTDC_PWKT_ExchangeKey: int = 48
THOST_FTDC_PWKT_PassWordKey: int = 49
THOST_FTDC_PWKT_MACKey: int = 50
THOST_FTDC_PWKT_MessageKey: int = 51
THOST_FTDC_PWT_Query: int = 48
THOST_FTDC_PWT_Fetch: int = 49
THOST_FTDC_PWT_Transfer: int = 50
THOST_FTDC_PWT_Trade: int = 51
THOST_FTDC_EM_NoEncry: int = 48
THOST_FTDC_EM_DES: int = 49
THOST_FTDC_EM_3DES: int = 50
THOST_FTDC_BRF_BankNotNeedRepeal: int = 48
THOST_FTDC_BRF_BankWaitingRepeal: int = 49
THOST_FTDC_BRF_BankBeenRepealed: int = 50
THOST_FTDC_BRORF_BrokerNotNeedRepeal: int = 48
THOST_FTDC_BRORF_BrokerWaitingRepeal: int = 49
THOST_FTDC_BRORF_BrokerBeenRepealed: int = 50
THOST_FTDC_TS_Bank: int = 48
THOST_FTDC_TS_Future: int = 49
THOST_FTDC_TS_Store: int = 50
THOST_FTDC_LF_Yes: int = 48
THOST_FTDC_LF_No: int = 49
THOST_FTDC_BAS_Normal: int = 48
THOST_FTDC_BAS_Freeze: int = 49
THOST_FTDC_BAS_ReportLoss: int = 50
THOST_FTDC_MAS_Normal: int = 48
THOST_FTDC_MAS_Cancel: int = 49
THOST_FTDC_MSS_Point: int = 48
THOST_FTDC_MSS_PrePoint: int = 49
THOST_FTDC_MSS_CancelPoint: int = 50
THOST_FTDC_SYT_FutureBankTransfer: int = 48
THOST_FTDC_SYT_StockBankTransfer: int = 49
THOST_FTDC_SYT_TheThirdPartStore: int = 50
THOST_FTDC_TEF_NormalProcessing: int = 48
THOST_FTDC_TEF_Success: int = 49
THOST_FTDC_TEF_Failed: int = 50
THOST_FTDC_TEF_Abnormal: int = 51
THOST_FTDC_TEF_ManualProcessedForException: int = 52
THOST_FTDC_TEF_CommuFailedNeedManualProcess: int = 53
THOST_FTDC_TEF_SysErrorNeedManualProcess: int = 54
THOST_FTDC_PSS_NotProcess: int = 48
THOST_FTDC_PSS_StartProcess: int = 49
THOST_FTDC_PSS_Finished: int = 50
THOST_FTDC_CUSTT_Person: int = 48
THOST_FTDC_CUSTT_Institution: int = 49
THOST_FTDC_FBTTD_FromBankToFuture: int = 49
THOST_FTDC_FBTTD_FromFutureToBank: int = 50
THOST_FTDC_OOD_Open: int = 49
THOST_FTDC_OOD_Destroy: int = 48
THOST_FTDC_AVAF_Invalid: int = 48
THOST_FTDC_AVAF_Valid: int = 49
THOST_FTDC_AVAF_Repeal: int = 50
THOST_FTDC_OT_Bank: int = 49
THOST_FTDC_OT_Future: int = 50
THOST_FTDC_OT_PlateForm: int = 57
THOST_FTDC_OL_HeadQuarters: int = 49
THOST_FTDC_OL_Branch: int = 50
THOST_FTDC_PID_FutureProtocal: int = 48
THOST_FTDC_PID_ICBCProtocal: int = 49
THOST_FTDC_PID_ABCProtocal: int = 50
THOST_FTDC_PID_CBCProtocal: int = 51
THOST_FTDC_PID_CCBProtocal: int = 52
THOST_FTDC_PID_BOCOMProtocal: int = 53
THOST_FTDC_PID_FBTPlateFormProtocal: int = 88
THOST_FTDC_CM_ShortConnect: int = 48
THOST_FTDC_CM_LongConnect: int = 49
THOST_FTDC_SRM_ASync: int = 48
THOST_FTDC_SRM_Sync: int = 49
THOST_FTDC_BAT_BankBook: int = 49
THOST_FTDC_BAT_SavingCard: int = 50
THOST_FTDC_BAT_CreditCard: int = 51
THOST_FTDC_FAT_BankBook: int = 49
THOST_FTDC_FAT_SavingCard: int = 50
THOST_FTDC_FAT_CreditCard: int = 51
THOST_FTDC_OS_Ready: int = 48
THOST_FTDC_OS_CheckIn: int = 49
THOST_FTDC_OS_CheckOut: int = 50
THOST_FTDC_OS_CheckFileArrived: int = 51
THOST_FTDC_OS_CheckDetail: int = 52
THOST_FTDC_OS_DayEndClean: int = 53
THOST_FTDC_OS_Invalid: int = 57
THOST_FTDC_CCBFM_ByAmount: int = 49
THOST_FTDC_CCBFM_ByMonth: int = 50
THOST_FTDC_CAPIT_Client: int = 49
THOST_FTDC_CAPIT_Server: int = 50
THOST_FTDC_CAPIT_UserApi: int = 51
THOST_FTDC_LS_Connected: int = 49
THOST_FTDC_LS_Disconnected: int = 50
THOST_FTDC_BPWDF_NoCheck: int = 48
THOST_FTDC_BPWDF_BlankCheck: int = 49
THOST_FTDC_BPWDF_EncryptCheck: int = 50
THOST_FTDC_SAT_AccountID: int = 49
THOST_FTDC_SAT_CardID: int = 50
THOST_FTDC_SAT_SHStockholderID: int = 51
THOST_FTDC_SAT_SZStockholderID: int = 52
THOST_FTDC_TRFS_Normal: int = 48
THOST_FTDC_TRFS_Repealed: int = 49
THOST_FTDC_SPTYPE_Broker: int = 48
THOST_FTDC_SPTYPE_Bank: int = 49
THOST_FTDC_REQRSP_Request: int = 48
THOST_FTDC_REQRSP_Response: int = 49
THOST_FTDC_FBTUET_SignIn: int = 48
THOST_FTDC_FBTUET_FromBankToFuture: int = 49
THOST_FTDC_FBTUET_FromFutureToBank: int = 50
THOST_FTDC_FBTUET_OpenAccount: int = 51
THOST_FTDC_FBTUET_CancelAccount: int = 52
THOST_FTDC_FBTUET_ChangeAccount: int = 53
THOST_FTDC_FBTUET_RepealFromBankToFuture: int = 54
THOST_FTDC_FBTUET_RepealFromFutureToBank: int = 55
THOST_FTDC_FBTUET_QueryBankAccount: int = 56
THOST_FTDC_FBTUET_QueryFutureAccount: int = 57
THOST_FTDC_FBTUET_SignOut: int = 65
THOST_FTDC_FBTUET_SyncKey: int = 66
THOST_FTDC_FBTUET_ReserveOpenAccount: int = 67
THOST_FTDC_FBTUET_CancelReserveOpenAccount: int = 68
THOST_FTDC_FBTUET_ReserveOpenAccountConfirm: int = 69
THOST_FTDC_FBTUET_Other: int = 90
THOST_FTDC_DBOP_Insert: int = 48
THOST_FTDC_DBOP_Update: int = 49
THOST_FTDC_DBOP_Delete: int = 50
THOST_FTDC_SYNF_Yes: int = 48
THOST_FTDC_SYNF_No: int = 49
THOST_FTDC_SYNT_OneOffSync: int = 48
THOST_FTDC_SYNT_TimerSync: int = 49
THOST_FTDC_SYNT_TimerFullSync: int = 50
THOST_FTDC_FBEDIR_Settlement: int = 48
THOST_FTDC_FBEDIR_Sale: int = 49
THOST_FTDC_FBERES_Success: int = 48
THOST_FTDC_FBERES_InsufficientBalance: int = 49
THOST_FTDC_FBERES_UnknownTrading: int = 56
THOST_FTDC_FBERES_Fail: int = 120
THOST_FTDC_FBEES_Normal: int = 48
THOST_FTDC_FBEES_ReExchange: int = 49
THOST_FTDC_FBEFG_DataPackage: int = 48
THOST_FTDC_FBEFG_File: int = 49
THOST_FTDC_FBEAT_NotTrade: int = 48
THOST_FTDC_FBEAT_Trade: int = 49
THOST_FTDC_FBEUET_SignIn: int = 48
THOST_FTDC_FBEUET_Exchange: int = 49
THOST_FTDC_FBEUET_ReExchange: int = 50
THOST_FTDC_FBEUET_QueryBankAccount: int = 51
THOST_FTDC_FBEUET_QueryExchDetial: int = 52
THOST_FTDC_FBEUET_QueryExchSummary: int = 53
THOST_FTDC_FBEUET_QueryExchRate: int = 54
THOST_FTDC_FBEUET_CheckBankAccount: int = 55
THOST_FTDC_FBEUET_SignOut: int = 56
THOST_FTDC_FBEUET_Other: int = 90
THOST_FTDC_FBERF_UnProcessed: int = 48
THOST_FTDC_FBERF_WaitSend: int = 49
THOST_FTDC_FBERF_SendSuccess: int = 50
THOST_FTDC_FBERF_SendFailed: int = 51
THOST_FTDC_FBERF_WaitReSend: int = 52
THOST_FTDC_NC_NOERROR: int = 48
THOST_FTDC_NC_Warn: int = 49
THOST_FTDC_NC_Call: int = 50
THOST_FTDC_NC_Force: int = 51
THOST_FTDC_NC_CHUANCANG: int = 52
THOST_FTDC_NC_Exception: int = 53
THOST_FTDC_FCT_Manual: int = 48
THOST_FTDC_FCT_Single: int = 49
THOST_FTDC_FCT_Group: int = 50
THOST_FTDC_RNM_System: int = 48
THOST_FTDC_RNM_SMS: int = 49
THOST_FTDC_RNM_EMail: int = 50
THOST_FTDC_RNM_Manual: int = 51
THOST_FTDC_RNS_NotGen: int = 48
THOST_FTDC_RNS_Generated: int = 49
THOST_FTDC_RNS_SendError: int = 50
THOST_FTDC_RNS_SendOk: int = 51
THOST_FTDC_RNS_Received: int = 52
THOST_FTDC_RNS_Confirmed: int = 53
THOST_FTDC_RUE_ExportData: int = 48
THOST_FTDC_COST_LastPriceAsc: int = 48
THOST_FTDC_COST_LastPriceDesc: int = 49
THOST_FTDC_COST_AskPriceAsc: int = 50
THOST_FTDC_COST_AskPriceDesc: int = 51
THOST_FTDC_COST_BidPriceAsc: int = 52
THOST_FTDC_COST_BidPriceDesc: int = 53
THOST_FTDC_UOAST_NoSend: int = 48
THOST_FTDC_UOAST_Sended: int = 49
THOST_FTDC_UOAST_Generated: int = 50
THOST_FTDC_UOAST_SendFail: int = 51
THOST_FTDC_UOAST_Success: int = 52
THOST_FTDC_UOAST_Fail: int = 53
THOST_FTDC_UOAST_Cancel: int = 54
THOST_FTDC_UOACS_NoApply: int = 49
THOST_FTDC_UOACS_Submited: int = 50
THOST_FTDC_UOACS_Sended: int = 51
THOST_FTDC_UOACS_Success: int = 52
THOST_FTDC_UOACS_Refuse: int = 53
THOST_FTDC_UOACS_Cancel: int = 54
THOST_FTDC_QT_Radio: int = 49
THOST_FTDC_QT_Option: int = 50
THOST_FTDC_QT_Blank: int = 51
THOST_FTDC_BT_Request: int = 49
THOST_FTDC_BT_Response: int = 50
THOST_FTDC_BT_Notice: int = 51
THOST_FTDC_CRC_Success: int = 48
THOST_FTDC_CRC_Working: int = 49
THOST_FTDC_CRC_InfoFail: int = 50
THOST_FTDC_CRC_IDCardFail: int = 51
THOST_FTDC_CRC_OtherFail: int = 52
THOST_FTDC_CfMMCCT_All: int = 48
THOST_FTDC_CfMMCCT_Person: int = 49
THOST_FTDC_CfMMCCT_Company: int = 50
THOST_FTDC_CfMMCCT_Other: int = 51
THOST_FTDC_CfMMCCT_SpecialOrgan: int = 52
THOST_FTDC_CfMMCCT_Asset: int = 53
THOST_FTDC_EIDT_SHFE: int = 83
THOST_FTDC_EIDT_CZCE: int = 90
THOST_FTDC_EIDT_DCE: int = 68
THOST_FTDC_EIDT_CFFEX: int = 74
THOST_FTDC_EIDT_INE: int = 78
THOST_FTDC_ECIDT_Hedge: int = 49
THOST_FTDC_ECIDT_Arbitrage: int = 50
THOST_FTDC_ECIDT_Speculation: int = 51
THOST_FTDC_UF_NoUpdate: int = 48
THOST_FTDC_UF_Success: int = 49
THOST_FTDC_UF_Fail: int = 50
THOST_FTDC_UF_TCSuccess: int = 51
THOST_FTDC_UF_TCFail: int = 52
THOST_FTDC_UF_Cancel: int = 53
THOST_FTDC_AOID_OpenInvestor: int = 49
THOST_FTDC_AOID_ModifyIDCard: int = 50
THOST_FTDC_AOID_ModifyNoIDCard: int = 51
THOST_FTDC_AOID_ApplyTradingCode: int = 52
THOST_FTDC_AOID_CancelTradingCode: int = 53
THOST_FTDC_AOID_CancelInvestor: int = 54
THOST_FTDC_AOID_FreezeAccount: int = 56
THOST_FTDC_AOID_ActiveFreezeAccount: int = 57
THOST_FTDC_ASID_NoComplete: int = 49
THOST_FTDC_ASID_Submited: int = 50
THOST_FTDC_ASID_Checked: int = 51
THOST_FTDC_ASID_Refused: int = 52
THOST_FTDC_ASID_Deleted: int = 53
THOST_FTDC_UOASM_ByAPI: int = 49
THOST_FTDC_UOASM_ByFile: int = 50
THOST_FTDC_EvM_ADD: int = 49
THOST_FTDC_EvM_UPDATE: int = 50
THOST_FTDC_EvM_DELETE: int = 51
THOST_FTDC_EvM_CHECK: int = 52
THOST_FTDC_EvM_COPY: int = 53
THOST_FTDC_EvM_CANCEL: int = 54
THOST_FTDC_EvM_Reverse: int = 55
THOST_FTDC_UOAA_ASR: int = 49
THOST_FTDC_UOAA_ASNR: int = 50
THOST_FTDC_UOAA_NSAR: int = 51
THOST_FTDC_UOAA_NSR: int = 52
THOST_FTDC_EvM_InvestorGroupFlow: int = 49
THOST_FTDC_EvM_InvestorRate: int = 50
THOST_FTDC_EvM_InvestorCommRateModel: int = 51
THOST_FTDC_CL_Zero: int = 48
THOST_FTDC_CL_One: int = 49
THOST_FTDC_CL_Two: int = 50
THOST_FTDC_CHS_Init: int = 48
THOST_FTDC_CHS_Checking: int = 49
THOST_FTDC_CHS_Checked: int = 50
THOST_FTDC_CHS_Refuse: int = 51
THOST_FTDC_CHS_Cancel: int = 52
THOST_FTDC_CHU_Unused: int = 48
THOST_FTDC_CHU_Used: int = 49
THOST_FTDC_CHU_Fail: int = 50
THOST_FTDC_BAO_ByAccProperty: int = 48
THOST_FTDC_BAO_ByFBTransfer: int = 49
THOST_FTDC_MBTS_ByInstrument: int = 48
THOST_FTDC_MBTS_ByDayInsPrc: int = 49
THOST_FTDC_MBTS_ByDayIns: int = 50
THOST_FTDC_FTC_BankLaunchBankToBroker: int = 53035779791614
THOST_FTDC_FTC_BrokerLaunchBankToBroker: int = 54113983700989
THOST_FTDC_FTC_BankLaunchBrokerToBank: int = 53035779791615
THOST_FTDC_FTC_BrokerLaunchBrokerToBank: int = 54113983700990
THOST_FTDC_OTP_NONE: int = 48
THOST_FTDC_OTP_TOTP: int = 49
THOST_FTDC_OTPS_Unused: int = 48
THOST_FTDC_OTPS_Used: int = 49
THOST_FTDC_OTPS_Disuse: int = 50
THOST_FTDC_BUT_Investor: int = 49
THOST_FTDC_BUT_BrokerUser: int = 50
THOST_FTDC_FUTT_Commodity: int = 49
THOST_FTDC_FUTT_Financial: int = 50
THOST_FTDC_FET_Restriction: int = 48
THOST_FTDC_FET_TodayRestriction: int = 49
THOST_FTDC_FET_Transfer: int = 50
THOST_FTDC_FET_Credit: int = 51
THOST_FTDC_FET_InvestorWithdrawAlm: int = 52
THOST_FTDC_FET_BankRestriction: int = 53
THOST_FTDC_FET_Accountregister: int = 54
THOST_FTDC_FET_ExchangeFundIO: int = 55
THOST_FTDC_FET_InvestorFundIO: int = 56
THOST_FTDC_AST_FBTransfer: int = 48
THOST_FTDC_AST_ManualEntry: int = 49
THOST_FTDC_CST_UnifyAccount: int = 48
THOST_FTDC_CST_ManualEntry: int = 49
THOST_FTDC_UR_All: int = 48
THOST_FTDC_UR_Single: int = 49
THOST_FTDC_BG_Investor: int = 50
THOST_FTDC_BG_Group: int = 49
THOST_FTDC_TSSM_Instrument: int = 49
THOST_FTDC_TSSM_Product: int = 50
THOST_FTDC_TSSM_Exchange: int = 51
THOST_FTDC_ESM_Relative: int = 49
THOST_FTDC_ESM_Typical: int = 50
THOST_FTDC_RIR_All: int = 49
THOST_FTDC_RIR_Model: int = 50
THOST_FTDC_RIR_Single: int = 51
THOST_FTDC_SDS_Initialize: int = 48
THOST_FTDC_SDS_Settlementing: int = 49
THOST_FTDC_SDS_Settlemented: int = 50
THOST_FTDC_TSRC_NORMAL: int = 48
THOST_FTDC_TSRC_QUERY: int = 49
THOST_FTDC_FSM_Product: int = 49
THOST_FTDC_FSM_Exchange: int = 50
THOST_FTDC_FSM_All: int = 51
THOST_FTDC_BIR_Property: int = 49
THOST_FTDC_BIR_All: int = 50
THOST_FTDC_PIR_All: int = 49
THOST_FTDC_PIR_Property: int = 50
THOST_FTDC_PIR_Single: int = 51
THOST_FTDC_FIS_NoCreate: int = 48
THOST_FTDC_FIS_Created: int = 49
THOST_FTDC_FIS_Failed: int = 50
THOST_FTDC_FGS_FileTransmit: int = 48
THOST_FTDC_FGS_FileGen: int = 49
THOST_FTDC_SoM_Add: int = 49
THOST_FTDC_SoM_Update: int = 50
THOST_FTDC_SoM_Delete: int = 51
THOST_FTDC_SoM_Copy: int = 52
THOST_FTDC_SoM_AcTive: int = 53
THOST_FTDC_SoM_CanCel: int = 54
THOST_FTDC_SoM_ReSet: int = 55
THOST_FTDC_SoT_UpdatePassword: int = 48
THOST_FTDC_SoT_UserDepartment: int = 49
THOST_FTDC_SoT_RoleManager: int = 50
THOST_FTDC_SoT_RoleFunction: int = 51
THOST_FTDC_SoT_BaseParam: int = 52
THOST_FTDC_SoT_SetUserID: int = 53
THOST_FTDC_SoT_SetUserRole: int = 54
THOST_FTDC_SoT_UserIpRestriction: int = 55
THOST_FTDC_SoT_DepartmentManager: int = 56
THOST_FTDC_SoT_DepartmentCopy: int = 57
THOST_FTDC_SoT_Tradingcode: int = 65
THOST_FTDC_SoT_InvestorStatus: int = 66
THOST_FTDC_SoT_InvestorAuthority: int = 67
THOST_FTDC_SoT_PropertySet: int = 68
THOST_FTDC_SoT_ReSetInvestorPasswd: int = 69
THOST_FTDC_SoT_InvestorPersonalityInfo: int = 70
THOST_FTDC_CSRCQ_Current: int = 48
THOST_FTDC_CSRCQ_History: int = 49
THOST_FTDC_FRS_Normal: int = 49
THOST_FTDC_FRS_Freeze: int = 48
THOST_FTDC_STST_Standard: int = 48
THOST_FTDC_STST_NonStandard: int = 49
THOST_FTDC_RPT_Freeze: int = 49
THOST_FTDC_RPT_FreezeActive: int = 50
THOST_FTDC_RPT_OpenLimit: int = 51
THOST_FTDC_RPT_RelieveOpenLimit: int = 52
THOST_FTDC_AMLDS_Normal: int = 48
THOST_FTDC_AMLDS_Deleted: int = 49
THOST_FTDC_AMLCHS_Init: int = 48
THOST_FTDC_AMLCHS_Checking: int = 49
THOST_FTDC_AMLCHS_Checked: int = 50
THOST_FTDC_AMLCHS_RefuseReport: int = 51
THOST_FTDC_AMLDT_DrawDay: int = 48
THOST_FTDC_AMLDT_TouchDay: int = 49
THOST_FTDC_AMLCL_CheckLevel0: int = 48
THOST_FTDC_AMLCL_CheckLevel1: int = 49
THOST_FTDC_AMLCL_CheckLevel2: int = 50
THOST_FTDC_AMLCL_CheckLevel3: int = 51
THOST_FTDC_EFT_CSV: int = 48
THOST_FTDC_EFT_EXCEL: int = 49
THOST_FTDC_EFT_DBF: int = 50
THOST_FTDC_SMT_Before: int = 49
THOST_FTDC_SMT_Settlement: int = 50
THOST_FTDC_SMT_After: int = 51
THOST_FTDC_SMT_Settlemented: int = 52
THOST_FTDC_SML_Must: int = 49
THOST_FTDC_SML_Alarm: int = 50
THOST_FTDC_SML_Prompt: int = 51
THOST_FTDC_SML_Ignore: int = 52
THOST_FTDC_SMG_Exhcange: int = 49
THOST_FTDC_SMG_ASP: int = 50
THOST_FTDC_SMG_CSRC: int = 51
THOST_FTDC_LUT_Repeatable: int = 49
THOST_FTDC_LUT_Unrepeatable: int = 50
THOST_FTDC_DAR_Settle: int = 49
THOST_FTDC_DAR_Exchange: int = 50
THOST_FTDC_DAR_CSRC: int = 51
THOST_FTDC_MGT_ExchMarginRate: int = 48
THOST_FTDC_MGT_InstrMarginRate: int = 49
THOST_FTDC_MGT_InstrMarginRateTrade: int = 50
THOST_FTDC_ACT_Intraday: int = 49
THOST_FTDC_ACT_Long: int = 50
THOST_FTDC_MRT_Exchange: int = 49
THOST_FTDC_MRT_Investor: int = 50
THOST_FTDC_MRT_InvestorTrade: int = 51
THOST_FTDC_BUS_UnBak: int = 48
THOST_FTDC_BUS_BakUp: int = 49
THOST_FTDC_BUS_BakUped: int = 50
THOST_FTDC_BUS_BakFail: int = 51
THOST_FTDC_SIS_UnInitialize: int = 48
THOST_FTDC_SIS_Initialize: int = 49
THOST_FTDC_SIS_Initialized: int = 50
THOST_FTDC_SRS_NoCreate: int = 48
THOST_FTDC_SRS_Create: int = 49
THOST_FTDC_SRS_Created: int = 50
THOST_FTDC_SRS_CreateFail: int = 51
THOST_FTDC_SSS_UnSaveData: int = 48
THOST_FTDC_SSS_SaveDatad: int = 49
THOST_FTDC_SAS_UnArchived: int = 48
THOST_FTDC_SAS_Archiving: int = 49
THOST_FTDC_SAS_Archived: int = 50
THOST_FTDC_SAS_ArchiveFail: int = 51
THOST_FTDC_CTPT_Unkown: int = 48
THOST_FTDC_CTPT_MainCenter: int = 49
THOST_FTDC_CTPT_BackUp: int = 50
THOST_FTDC_CDT_Normal: int = 48
THOST_FTDC_CDT_SpecFirst: int = 49
THOST_FTDC_MFUR_None: int = 48
THOST_FTDC_MFUR_Margin: int = 49
THOST_FTDC_MFUR_All: int = 50
THOST_FTDC_MFUR_CNY3: int = 51
THOST_FTDC_SPT_CzceHedge: int = 49
THOST_FTDC_SPT_IneForeignCurrency: int = 50
THOST_FTDC_SPT_DceOpenClose: int = 51
THOST_FTDC_FMT_Mortgage: int = 49
THOST_FTDC_FMT_Redemption: int = 50
THOST_FTDC_ASPI_BaseMargin: int = 49
THOST_FTDC_ASPI_LowestInterest: int = 50
THOST_FTDC_FMD_In: int = 49
THOST_FTDC_FMD_Out: int = 50
THOST_FTDC_BT_Profit: int = 48
THOST_FTDC_BT_Loss: int = 49
THOST_FTDC_BT_Other: int = 90
THOST_FTDC_SST_Manual: int = 48
THOST_FTDC_SST_Automatic: int = 49
THOST_FTDC_CED_Settlement: int = 48
THOST_FTDC_CED_Sale: int = 49
THOST_FTDC_CSS_Entry: int = 49
THOST_FTDC_CSS_Approve: int = 50
THOST_FTDC_CSS_Refuse: int = 51
THOST_FTDC_CSS_Revoke: int = 52
THOST_FTDC_CSS_Send: int = 53
THOST_FTDC_CSS_Success: int = 54
THOST_FTDC_CSS_Failure: int = 55
THOST_FTDC_REQF_NoSend: int = 48
THOST_FTDC_REQF_SendSuccess: int = 49
THOST_FTDC_REQF_SendFailed: int = 50
THOST_FTDC_REQF_WaitReSend: int = 51
THOST_FTDC_RESF_Success: int = 48
THOST_FTDC_RESF_InsuffiCient: int = 49
THOST_FTDC_RESF_UnKnown: int = 56
THOST_FTDC_EXS_Before: int = 48
THOST_FTDC_EXS_After: int = 49
THOST_FTDC_CR_Domestic: int = 49
THOST_FTDC_CR_GMT: int = 50
THOST_FTDC_CR_Foreign: int = 51
THOST_FTDC_HB_No: int = 48
THOST_FTDC_HB_Yes: int = 49
THOST_FTDC_SM_Normal: int = 49
THOST_FTDC_SM_Emerge: int = 50
THOST_FTDC_SM_Restore: int = 51
THOST_FTDC_TPT_Full: int = 49
THOST_FTDC_TPT_Increment: int = 50
THOST_FTDC_TPT_BackUp: int = 51
THOST_FTDC_LM_Trade: int = 48
THOST_FTDC_LM_Transfer: int = 49
THOST_FTDC_CPT_Instrument: int = 49
THOST_FTDC_CPT_Margin: int = 50
THOST_FTDC_HT_Yes: int = 49
THOST_FTDC_HT_No: int = 48
THOST_FTDC_AMT_Bank: int = 49
THOST_FTDC_AMT_Securities: int = 50
THOST_FTDC_AMT_Fund: int = 51
THOST_FTDC_AMT_Insurance: int = 52
THOST_FTDC_AMT_Trust: int = 53
THOST_FTDC_AMT_Other: int = 57
THOST_FTDC_CFIOT_FundIO: int = 48
THOST_FTDC_CFIOT_SwapCurrency: int = 49
THOST_FTDC_CAT_Futures: int = 49
THOST_FTDC_CAT_AssetmgrFuture: int = 50
THOST_FTDC_CAT_AssetmgrTrustee: int = 51
THOST_FTDC_CAT_AssetmgrTransfer: int = 52
THOST_FTDC_LT_Chinese: int = 49
THOST_FTDC_LT_English: int = 50
THOST_FTDC_AMCT_Person: int = 49
THOST_FTDC_AMCT_Organ: int = 50
THOST_FTDC_AMCT_SpecialOrgan: int = 52
THOST_FTDC_ASST_Futures: int = 51
THOST_FTDC_ASST_SpecialOrgan: int = 52
THOST_FTDC_CIT_HasExch: int = 48
THOST_FTDC_CIT_HasATP: int = 49
THOST_FTDC_CIT_HasDiff: int = 50
THOST_FTDC_DT_HandDeliv: int = 49
THOST_FTDC_DT_PersonDeliv: int = 50
THOST_FTDC_MMSA_NO: int = 48
THOST_FTDC_MMSA_YES: int = 49
THOST_FTDC_CACT_Person: int = 48
THOST_FTDC_CACT_Company: int = 49
THOST_FTDC_CACT_Other: int = 50
THOST_FTDC_UOAAT_Futures: int = 49
THOST_FTDC_UOAAT_SpecialOrgan: int = 50
THOST_FTDC_DEN_Buy: int = 48
THOST_FTDC_DEN_Sell: int = 49
THOST_FTDC_OFEN_Open: int = 48
THOST_FTDC_OFEN_Close: int = 49
THOST_FTDC_OFEN_ForceClose: int = 50
THOST_FTDC_OFEN_CloseToday: int = 51
THOST_FTDC_OFEN_CloseYesterday: int = 52
THOST_FTDC_OFEN_ForceOff: int = 53
THOST_FTDC_OFEN_LocalForceClose: int = 54
THOST_FTDC_HFEN_Speculation: int = 49
THOST_FTDC_HFEN_Arbitrage: int = 50
THOST_FTDC_HFEN_Hedge: int = 51
THOST_FTDC_FIOTEN_FundIO: int = 49
THOST_FTDC_FIOTEN_Transfer: int = 50
THOST_FTDC_FIOTEN_SwapCurrency: int = 51
THOST_FTDC_FTEN_Deposite: int = 49
THOST_FTDC_FTEN_ItemFund: int = 50
THOST_FTDC_FTEN_Company: int = 51
THOST_FTDC_FTEN_InnerTransfer: int = 52
THOST_FTDC_FDEN_In: int = 49
THOST_FTDC_FDEN_Out: int = 50
THOST_FTDC_FMDEN_In: int = 49
THOST_FTDC_FMDEN_Out: int = 50
THOST_FTDC_CP_CallOptions: int = 49
THOST_FTDC_CP_PutOptions: int = 50
THOST_FTDC_STM_Continental: int = 48
THOST_FTDC_STM_American: int = 49
THOST_FTDC_STM_Bermuda: int = 50
THOST_FTDC_STT_Hedge: int = 48
THOST_FTDC_STT_Match: int = 49
THOST_FTDC_APPT_NotStrikeNum: int = 52
THOST_FTDC_GUDS_Gen: int = 48
THOST_FTDC_GUDS_Hand: int = 49
THOST_FTDC_OER_NoExec: int = 110
THOST_FTDC_OER_Canceled: int = 99
THOST_FTDC_OER_OK: int = 48
THOST_FTDC_OER_NoPosition: int = 49
THOST_FTDC_OER_NoDeposit: int = 50
THOST_FTDC_OER_NoParticipant: int = 51
THOST_FTDC_OER_NoClient: int = 52
THOST_FTDC_OER_NoInstrument: int = 54
THOST_FTDC_OER_NoRight: int = 55
THOST_FTDC_OER_InvalidVolume: int = 56
THOST_FTDC_OER_NoEnoughHistoryTrade: int = 57
THOST_FTDC_OER_Unknown: int = 97
THOST_FTDC_COMBT_Future: int = 48
THOST_FTDC_COMBT_BUL: int = 49
THOST_FTDC_COMBT_BER: int = 50
THOST_FTDC_COMBT_STD: int = 51
THOST_FTDC_COMBT_STG: int = 52
THOST_FTDC_COMBT_PRT: int = 53
THOST_FTDC_COMBT_CLD: int = 54
THOST_FTDC_ORPT_PreSettlementPrice: int = 49
THOST_FTDC_ORPT_OpenPrice: int = 52
THOST_FTDC_ORPT_MaxPreSettlementPrice: int = 53
THOST_FTDC_BLAG_Default: int = 49
THOST_FTDC_BLAG_IncludeOptValLost: int = 50
THOST_FTDC_ACTP_Exec: int = 49
THOST_FTDC_ACTP_Abandon: int = 50
THOST_FTDC_FQST_Submitted: int = 97
THOST_FTDC_FQST_Accepted: int = 98
THOST_FTDC_FQST_Rejected: int = 99
THOST_FTDC_VM_Absolute: int = 48
THOST_FTDC_VM_Ratio: int = 49
THOST_FTDC_EOPF_Reserve: int = 48
THOST_FTDC_EOPF_UnReserve: int = 49
THOST_FTDC_EOCF_AutoClose: int = 48
THOST_FTDC_EOCF_NotToClose: int = 49
THOST_FTDC_PTE_Futures: int = 49
THOST_FTDC_PTE_Options: int = 50
THOST_FTDC_CUFN_CUFN_O: int = 79
THOST_FTDC_CUFN_CUFN_T: int = 84
THOST_FTDC_CUFN_CUFN_P: int = 80
THOST_FTDC_CUFN_CUFN_N: int = 78
THOST_FTDC_CUFN_CUFN_L: int = 76
THOST_FTDC_CUFN_CUFN_F: int = 70
THOST_FTDC_CUFN_CUFN_C: int = 67
THOST_FTDC_CUFN_CUFN_M: int = 77
THOST_FTDC_DUFN_DUFN_O: int = 79
THOST_FTDC_DUFN_DUFN_T: int = 84
THOST_FTDC_DUFN_DUFN_P: int = 80
THOST_FTDC_DUFN_DUFN_F: int = 70
THOST_FTDC_DUFN_DUFN_C: int = 67
THOST_FTDC_DUFN_DUFN_D: int = 68
THOST_FTDC_DUFN_DUFN_M: int = 77
THOST_FTDC_DUFN_DUFN_S: int = 83
THOST_FTDC_SUFN_SUFN_O: int = 79
THOST_FTDC_SUFN_SUFN_T: int = 84
THOST_FTDC_SUFN_SUFN_P: int = 80
THOST_FTDC_SUFN_SUFN_F: int = 70
THOST_FTDC_CFUFN_SUFN_T: int = 84
THOST_FTDC_CFUFN_SUFN_P: int = 80
THOST_FTDC_CFUFN_SUFN_F: int = 70
THOST_FTDC_CFUFN_SUFN_S: int = 83
THOST_FTDC_CMDR_Comb: int = 48
THOST_FTDC_CMDR_UnComb: int = 49
THOST_FTDC_STOV_RealValue: int = 49
THOST_FTDC_STOV_ProfitValue: int = 50
THOST_FTDC_STOV_RealRatio: int = 51
THOST_FTDC_STOV_ProfitRatio: int = 52
THOST_FTDC_ROAST_Processing: int = 48
THOST_FTDC_ROAST_Cancelled: int = 49
THOST_FTDC_ROAST_Opened: int = 50
THOST_FTDC_ROAST_Invalid: int = 51
THOST_FTDC_WPSR_Lib: int = 49
THOST_FTDC_WPSR_Manual: int = 50
THOST_FTDC_OSCF_CloseSelfOptionPosition: int = 49
THOST_FTDC_OSCF_ReserveOptionPosition: int = 50
THOST_FTDC_OSCF_SellCloseSelfFuturePosition: int = 51
THOST_FTDC_OSCF_ReserveFuturePosition: int = 52
THOST_FTDC_BZTP_Future: int = 49
THOST_FTDC_BZTP_Stock: int = 50
THOST_FTDC_APP_TYPE_Investor: int = 49
THOST_FTDC_APP_TYPE_InvestorRelay: int = 50
THOST_FTDC_APP_TYPE_OperatorRelay: int = 51
THOST_FTDC_APP_TYPE_UnKnown: int = 52
THOST_FTDC_RV_Right: int = 48
THOST_FTDC_RV_Refuse: int = 49
THOST_FTDC_OTC_TRDT_Block: int = 48
THOST_FTDC_OTC_TRDT_EFP: int = 49
THOST_FTDC_OTC_MT_DV01: int = 49
THOST_FTDC_OTC_MT_ParValue: int = 50
class THOST_TE_RESUME_TYPE:
    THOST_TERT_RESTART: THOST_TE_RESUME_TYPE
    THOST_TERT_RESUME: THOST_TE_RESUME_TYPE = 1
    THOST_TERT_QUICK: THOST_TE_RESUME_TYPE = 2
    ...

