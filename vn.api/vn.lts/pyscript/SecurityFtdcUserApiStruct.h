/////////////////////////////////////////////////////////////////////////
///@company shanghai liber information Technology Co.,Ltd
///@file SecurityFtdcUserApiStruct.h
///@brief 定义业务数据结构
/////////////////////////////////////////////////////////////////////////

#if !defined(SECURITY_FTDCSTRUCT_H)
#define SECURITY_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SecurityFtdcUserApiDataType.h"

#pragma pack(push)
#pragma pack(1)
///响应信息
struct CSecurityFtdcRspInfoField
{
	///错误代码
	TSecurityFtdcErrorIDType	ErrorID;
	///错误信息
	TSecurityFtdcErrorMsgType	ErrorMsg;
};

///交易所
struct CSecurityFtdcExchangeField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///交易所名称
	TSecurityFtdcExchangeNameType	ExchangeName;
	///交易所属性
	TSecurityFtdcExchangePropertyType	ExchangeProperty;
};

///产品
struct CSecurityFtdcProductField
{
	///产品代码
	TSecurityFtdcInstrumentIDType	ProductID;
	///产品名称
	TSecurityFtdcProductNameType	ProductName;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///产品类型
	TSecurityFtdcProductClassType	ProductClass;
	///合约数量乘数
	TSecurityFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TSecurityFtdcPriceType	PriceTick;
	///市价单最大下单量
	TSecurityFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TSecurityFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TSecurityFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TSecurityFtdcVolumeType	MinLimitOrderVolume;
	///持仓类型
	TSecurityFtdcPositionTypeType	PositionType;
	///持仓日期类型
	TSecurityFtdcPositionDateTypeType	PositionDateType;
	///ETF最小交易单位
	TSecurityFtdcVolumeType	EFTMinTradeVolume;
};

///合约
struct CSecurityFtdcInstrumentField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约名称
	TSecurityFtdcInstrumentNameType	InstrumentName;
	///合约在交易所的代码
	TSecurityFtdcExchangeInstIDType	ExchangeInstID;
	///产品代码
	TSecurityFtdcInstrumentIDType	ProductID;
	///产品类型
	TSecurityFtdcProductClassType	ProductClass;
	///交割年份
	TSecurityFtdcYearType	DeliveryYear;
	///交割月
	TSecurityFtdcMonthType	DeliveryMonth;
	///市价单最大下单量
	TSecurityFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TSecurityFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TSecurityFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TSecurityFtdcVolumeType	MinLimitOrderVolume;
	///合约数量乘数
	TSecurityFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TSecurityFtdcPriceType	PriceTick;
	///创建日
	TSecurityFtdcDateType	CreateDate;
	///上市日
	TSecurityFtdcDateType	OpenDate;
	///到期日
	TSecurityFtdcDateType	ExpireDate;
	///开始交割日
	TSecurityFtdcDateType	StartDelivDate;
	///结束交割日
	TSecurityFtdcDateType	EndDelivDate;
	///合约生命周期状态
	TSecurityFtdcInstLifePhaseType	InstLifePhase;
	///当前是否交易
	TSecurityFtdcBoolType	IsTrading;
	///持仓类型
	TSecurityFtdcPositionTypeType	PositionType;
	///报单能否撤单
	TSecurityFtdcBoolType	OrderCanBeWithdraw;
	///最小买下单单位
	TSecurityFtdcVolumeType	MinBuyVolume;
	///最小卖下单单位
	TSecurityFtdcVolumeType	MinSellVolume;
	///股票权限模版代码
	TSecurityFtdcRightModelIDType	RightModelID;
	///持仓交易类型
	TSecurityFtdcPosTradeTypeType	PosTradeType;
	///市场代码
	TSecurityFtdcInstrumentIDType	MarketID;
	///期权执行价格
	TSecurityFtdcPriceType	ExecPrice;
	///期权单手保证金
	TSecurityFtdcMoneyType	UnitMargin;
	///合约类型
	TSecurityFtdcInstrumentTypeType	InstrumentType;
	///期权保证金参数1
	TSecurityFtdcRatioType	OptionsMarginParam1;
	///期权保证金参数2
	TSecurityFtdcRatioType	OptionsMarginParam2;
};

///经纪公司
struct CSecurityFtdcBrokerField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///经纪公司简称
	TSecurityFtdcBrokerAbbrType	BrokerAbbr;
	///经纪公司名称
	TSecurityFtdcBrokerNameType	BrokerName;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
};

///会员编码和经纪公司编码对照表
struct CSecurityFtdcPartBrokerField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
};

///投资者
struct CSecurityFtdcInvestorField
{
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TSecurityFtdcInvestorIDType	InvestorGroupID;
	///投资者名称
	TSecurityFtdcPartyNameType	InvestorName;
	///证件类型
	TSecurityFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TSecurityFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
	///上海营业部编号
	TSecurityFtdcTraderIDType	SHBranchID;
	///深圳营业部编号
	TSecurityFtdcTraderIDType	SZBranchID;
	///所属结算系统类型
	TSecurityFtdcSettleSystemTypeType	SettleSystemType;
	///投资者期权交易等级
	TSecurityFtdcInvestorLevelType	InvestorLevel;
};

///交易编码
struct CSecurityFtdcTradingCodeField
{
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///客户代码
	TSecurityFtdcClientIDType	ClientID;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
	///AccountID
	TSecurityFtdcAccountIDType	AccountID;
	///交易单元号
	TSecurityFtdcTraderIDType	PBU;
	///ClientType
	TSecurityFtdcClientTypeType	ClientType;
};

///管理用户
struct CSecurityFtdcSuperUserField
{
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///用户名称
	TSecurityFtdcUserNameType	UserName;
	///密码
	TSecurityFtdcPasswordType	Password;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
};

///管理用户功能权限
struct CSecurityFtdcSuperUserFunctionField
{
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///功能代码
	TSecurityFtdcFunctionCodeType	FunctionCode;
};

///经纪公司用户
struct CSecurityFtdcBrokerUserField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///用户名称
	TSecurityFtdcUserNameType	UserName;
	///用户类型
	TSecurityFtdcUserTypeType	UserType;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
	///是否使用令牌
	TSecurityFtdcBoolType	IsUsingOTP;
};

///经纪公司用户功能权限
struct CSecurityFtdcBrokerUserFunctionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///经纪公司功能代码
	TSecurityFtdcBrokerFunctionCodeType	BrokerFunctionCode;
};

///资金账户
struct CSecurityFtdcTradingAccountField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSecurityFtdcAccountIDType	AccountID;
	///上次质押金额
	TSecurityFtdcMoneyType	PreMortgage;
	///上次信用额度
	TSecurityFtdcMoneyType	PreCredit;
	///上次存款额
	TSecurityFtdcMoneyType	PreDeposit;
	///上次结算准备金
	TSecurityFtdcMoneyType	PreBalance;
	///上次占用的保证金
	TSecurityFtdcMoneyType	PreMargin;
	///利息基数
	TSecurityFtdcMoneyType	InterestBase;
	///利息收入
	TSecurityFtdcMoneyType	Interest;
	///入金金额
	TSecurityFtdcMoneyType	Deposit;
	///出金金额
	TSecurityFtdcMoneyType	Withdraw;
	///冻结的保证金
	TSecurityFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TSecurityFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TSecurityFtdcMoneyType	FrozenCommission;
	///当前保证金总额
	TSecurityFtdcMoneyType	CurrMargin;
	///资金差额
	TSecurityFtdcMoneyType	CashIn;
	///手续费
	TSecurityFtdcMoneyType	Commission;
	///结算准备金
	TSecurityFtdcMoneyType	Balance;
	///现金
	TSecurityFtdcMoneyType	Available;
	///可取资金
	TSecurityFtdcMoneyType	WithdrawQuota;
	///基本准备金
	TSecurityFtdcMoneyType	Reserve;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///保证金可用余额
	TSecurityFtdcMoneyType	Credit;
	///质押金额
	TSecurityFtdcMoneyType	Mortgage;
	///交易所保证金
	TSecurityFtdcMoneyType	ExchangeMargin;
	///投资者交割保证金
	TSecurityFtdcMoneyType	DeliveryMargin;
	///交易所交割保证金
	TSecurityFtdcMoneyType	ExchangeDeliveryMargin;
	///冻结的过户费
	TSecurityFtdcMoneyType	FrozenTransferFee;
	///冻结的印花税
	TSecurityFtdcMoneyType	FrozenStampTax;
	///过户费
	TSecurityFtdcMoneyType	TransferFee;
	///印花税
	TSecurityFtdcMoneyType	StampTax;
	///折算金额
	TSecurityFtdcMoneyType	ConversionAmount;
	///授信额度
	TSecurityFtdcMoneyType	CreditAmount;
	///证券总价值
	TSecurityFtdcMoneyType	StockValue;
	///国债回购占用资金
	TSecurityFtdcMoneyType	BondRepurchaseAmount;
	///国债逆回购占用资金
	TSecurityFtdcMoneyType	ReverseRepurchaseAmount;
	///币种
	TSecurityFtdcCurrencyCodeType	CurrencyCode;
	///账户类型
	TSecurityFtdcAccountTypeType	AccountType;
	///融资买入金额
	TSecurityFtdcMoneyType	MarginTradeAmount;
	///融券卖出金额
	TSecurityFtdcMoneyType	ShortSellAmount;
	///融资持仓盈亏
	TSecurityFtdcMoneyType	MarginTradeProfit;
	///融券持仓盈亏
	TSecurityFtdcMoneyType	ShortSellProfit;
	///融券总市值
	TSecurityFtdcMoneyType	SSStockValue;
	///维持担保比例
	TSecurityFtdcRatioType	CreditRatio;
	///行权冻结资金
	TSecurityFtdcMoneyType	FrozenExecCash;
	///期权买入资金(SSE)
	TSecurityFtdcMoneyType	SSEOptionsBuyAmount;
	///期权买入冻结资金(SSE)
	TSecurityFtdcMoneyType	SSEOptionsBuyFrozenAmount;
	///结算保证金总额
	TSecurityFtdcMoneyType	SettleMargin;
};

///禁止登录用户
struct CSecurityFtdcLoginForbiddenUserField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///深度行情
struct CSecurityFtdcDepthMarketDataField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TSecurityFtdcExchangeInstIDType	ExchangeInstID;
	///最新价
	TSecurityFtdcPriceType	LastPrice;
	///上次结算价
	TSecurityFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TSecurityFtdcPriceType	PreClosePrice;
	///昨持仓量
	TSecurityFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TSecurityFtdcPriceType	OpenPrice;
	///最高价
	TSecurityFtdcPriceType	HighestPrice;
	///最低价
	TSecurityFtdcPriceType	LowestPrice;
	///数量
	TSecurityFtdcLargeVolumeType	Volume;
	///成交金额
	TSecurityFtdcMoneyType	Turnover;
	///持仓量
	TSecurityFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TSecurityFtdcPriceType	ClosePrice;
	///本次结算价
	TSecurityFtdcPriceType	SettlementPrice;
	///涨停板价
	TSecurityFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TSecurityFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TSecurityFtdcRatioType	PreDelta;
	///今虚实度
	TSecurityFtdcRatioType	CurrDelta;
	///昨日基金净值
	TSecurityFtdcPriceType	PreIOPV;
	///基金净值
	TSecurityFtdcPriceType	IOPV;
	///动态参考价格
	TSecurityFtdcPriceType	AuctionPrice;
	///最后修改时间
	TSecurityFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TSecurityFtdcMillisecType	UpdateMillisec;
	///申买价一
	TSecurityFtdcPriceType	BidPrice1;
	///申买量一
	TSecurityFtdcLargeVolumeType	BidVolume1;
	///申卖价一
	TSecurityFtdcPriceType	AskPrice1;
	///申卖量一
	TSecurityFtdcLargeVolumeType	AskVolume1;
	///申买价二
	TSecurityFtdcPriceType	BidPrice2;
	///申买量二
	TSecurityFtdcLargeVolumeType	BidVolume2;
	///申卖价二
	TSecurityFtdcPriceType	AskPrice2;
	///申卖量二
	TSecurityFtdcLargeVolumeType	AskVolume2;
	///申买价三
	TSecurityFtdcPriceType	BidPrice3;
	///申买量三
	TSecurityFtdcLargeVolumeType	BidVolume3;
	///申卖价三
	TSecurityFtdcPriceType	AskPrice3;
	///申卖量三
	TSecurityFtdcLargeVolumeType	AskVolume3;
	///申买价四
	TSecurityFtdcPriceType	BidPrice4;
	///申买量四
	TSecurityFtdcLargeVolumeType	BidVolume4;
	///申卖价四
	TSecurityFtdcPriceType	AskPrice4;
	///申卖量四
	TSecurityFtdcLargeVolumeType	AskVolume4;
	///申买价五
	TSecurityFtdcPriceType	BidPrice5;
	///申买量五
	TSecurityFtdcLargeVolumeType	BidVolume5;
	///申卖价五
	TSecurityFtdcPriceType	AskPrice5;
	///申卖量五
	TSecurityFtdcLargeVolumeType	AskVolume5;
	///当日均价
	TSecurityFtdcPriceType	AveragePrice;
	///业务日期
	TSecurityFtdcDateType	ActionDay;
	///交易阶段
	TSecurityFtdcTradingPhaseType	TradingPhase;
	///开仓限制
	TSecurityFtdcOpenRestrictionType	OpenRestriction;
};

///投资者合约交易权限
struct CSecurityFtdcInstrumentTradingRightField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSecurityFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///买卖
	TSecurityFtdcDirectionType	Direction;
	///交易权限
	TSecurityFtdcTradingRightType	TradingRight;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///股票权限分类
	TSecurityFtdcInstrumentRangeType	InstrumentRange;
};

///投资者持仓明细
struct CSecurityFtdcInvestorPositionDetailField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TSecurityFtdcHedgeFlagType	HedgeFlag;
	///买卖
	TSecurityFtdcDirectionType	Direction;
	///开仓日期
	TSecurityFtdcDateType	OpenDate;
	///成交编号
	TSecurityFtdcTradeIDType	TradeID;
	///数量
	TSecurityFtdcLargeVolumeType	Volume;
	///开仓价
	TSecurityFtdcPriceType	OpenPrice;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///成交类型
	TSecurityFtdcTradeTypeType	TradeType;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///投资者保证金
	TSecurityFtdcMoneyType	Margin;
	///交易所保证金
	TSecurityFtdcMoneyType	ExchMargin;
	///昨结算价
	TSecurityFtdcPriceType	LastSettlementPrice;
	///结算价
	TSecurityFtdcPriceType	SettlementPrice;
	///平仓量
	TSecurityFtdcLargeVolumeType	CloseVolume;
	///平仓金额
	TSecurityFtdcMoneyType	CloseAmount;
	///过户费
	TSecurityFtdcMoneyType	TransferFee;
	///印花税
	TSecurityFtdcMoneyType	StampTax;
	///手续费
	TSecurityFtdcMoneyType	Commission;
	///AccountID
	TSecurityFtdcAccountIDType	AccountID;
	///质押入库数量
	TSecurityFtdcLargeVolumeType	PledgeInPosition;
	///质押入库冻结数量
	TSecurityFtdcLargeVolumeType	PledgeInFrozenPosition;
	///正回购使用的标准券数量
	TSecurityFtdcLargeVolumeType	RepurchasePosition;
	///融资融券金额
	TSecurityFtdcMoneyType	Amount;
	///标的合约代码
	TSecurityFtdcInstrumentIDType	UnderlyingInstrumentID;
};

///债券利息
struct CSecurityFtdcBondInterestField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///利息
	TSecurityFtdcInterestType	Interest;
};

///市值配售信息
struct CSecurityFtdcMarketRationInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///可配售数量
	TSecurityFtdcLargeVolumeType	RationVolume;
};

///合约手续费率
struct CSecurityFtdcInstrumentCommissionRateField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSecurityFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///买卖方向
	TSecurityFtdcDirectionType	Direction;
	///印花税率
	TSecurityFtdcRatioType	StampTaxRateByMoney;
	///印花税率(按手数)
	TSecurityFtdcRatioType	StampTaxRateByVolume;
	///过户费率
	TSecurityFtdcRatioType	TransferFeeRateByMoney;
	///过户费率(按手数)
	TSecurityFtdcRatioType	TransferFeeRateByVolume;
	///交易费
	TSecurityFtdcRatioType	TradeFeeByMoney;
	///交易费(按手数)
	TSecurityFtdcRatioType	TradeFeeByVolume;
	///交易附加费率
	TSecurityFtdcRatioType	MarginByMoney;
	///最小交易费
	TSecurityFtdcPriceType	MinTradeFee;
	///最小过户费
	TSecurityFtdcPriceType	MinTransferFee;
};

///余券信息
struct CSecurityFtdcExcessStockInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///余券数量
	TSecurityFtdcLargeVolumeType	ExcessVolume;
	///余券冻结数量
	TSecurityFtdcLargeVolumeType	ExcessFrozenVolume;
};

///ETF合约
struct CSecurityFtdcETFInstrumentField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///ETF证券代码
	TSecurityFtdcInstrumentIDType	ETFInstrumentID;
	///ETF对应申赎代码
	TSecurityFtdcInstrumentIDType	ETFPurRedInstrumentID;
	///最小申购赎回单位对应的ETF份数
	TSecurityFtdcVolumeType	CreationRedemptionUnit;
	///最大现金替代比例
	TSecurityFtdcRatioType	Maxcashratio;
	///基金当天申购赎回状态
	TSecurityFtdcCreationredemptionStatusType	Creationredemption;
	///预估金额
	TSecurityFtdcMoneyType	EstimateCashComponent;
	///基金申赎单位净值
	TSecurityFtdcMoneyType	ETFNetValue;
	///基金类别
	TSecurityFtdcFundClassType	FundClass;
};

///ETF股票篮
struct CSecurityFtdcETFBasketField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///ETF证券代码
	TSecurityFtdcInstrumentIDType	ETFInstrumentID;
	///股票证券代码
	TSecurityFtdcInstrumentIDType	StockInstrumentID;
	///股票证券名称
	TSecurityFtdcInstrumentNameType	StockInstrumentName;
	///股票数量
	TSecurityFtdcVolumeType	Volume;
	///替代标志
	TSecurityFtdcETFCurrenceReplaceStatusType	CurrenceReplaceStatus;
	///溢价比例
	TSecurityFtdcRatioType	Premium;
	///总金额
	TSecurityFtdcMoneyType	Amount;
};

///OF合约
struct CSecurityFtdcOFInstrumentField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///OF基金代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///基金当天申购赎回状态
	TSecurityFtdcCreationredemptionStatusType	Creationredemption;
	///基金净值
	TSecurityFtdcPriceType	NetPrice;
	///基金类别
	TSecurityFtdcFundClassType	FundClass;
};

///SF合约
struct CSecurityFtdcSFInstrumentField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///基金代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///SF基金代码
	TSecurityFtdcInstrumentIDType	SFInstrumentID;
	///基金当天拆分合并状态
	TSecurityFtdcSplitMergeStatusType	SplitMergeStatus;
	///最小拆分数量
	TSecurityFtdcVolumeType	MinSplitVolume;
	///最小合并数量
	TSecurityFtdcVolumeType	MinMergeVolume;
	///拆分/合并比例
	TSecurityFtdcVolumeType	VolumeRatio;
	///基金净值
	TSecurityFtdcPriceType	NetPrice;
};

///合约单手保证金
struct CSecurityFtdcInstrumentUnitMarginField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///合约单手保证金
	TSecurityFtdcMoneyType	UnitMargin;
};

///期权资金限制参数
struct CSecurityFtdcOptionsFundLimitParamField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///最大可买金额
	TSecurityFtdcMoneyType	MaxBuyAmount;
};

///投资者期权持仓
struct CSecurityFtdcInvestorOptionsPositionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者范围
	TSecurityFtdcInvestorRangeType	InvestorRange;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///InstrumentID
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///最大多头仓位限制
	TSecurityFtdcLargeVolumeType	MaxLongPositionLimit;
	///最大买开量限制
	TSecurityFtdcLargeVolumeType	MaxBuyVolLimit;
	///最大总仓位限制
	TSecurityFtdcLargeVolumeType	MaxPositionLimit;
	///多头持仓
	TSecurityFtdcLargeVolumeType	LongPosition;
	///空头持仓
	TSecurityFtdcLargeVolumeType	ShortPosition;
	///买开量
	TSecurityFtdcLargeVolumeType	BuyVolume;
	///买开冻结量
	TSecurityFtdcLargeVolumeType	BuyFrozenVolume;
	///多头冻结持仓
	TSecurityFtdcLargeVolumeType	LongFrozenPosition;
	///空头冻结持仓
	TSecurityFtdcLargeVolumeType	ShortFrozenPosition;
};

///预交割信息
struct CSecurityFtdcPreDelivInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交割类型
	TSecurityFtdcDelivTypeType	DelivType;
	///标的合约代码
	TSecurityFtdcInstrumentIDType	UnderlyingInstrumentID;
	///交割数量
	TSecurityFtdcLargeVolumeType	DelivVolume;
	///交割金额
	TSecurityFtdcMoneyType	DelivAmount;
	///期权执行数量
	TSecurityFtdcLargeVolumeType	ExecVolume;
	///买卖方向
	TSecurityFtdcDirectionType	Direction;
};

///可融券分配信息
struct CSecurityFtdcCreditStockAssignInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///融券限量
	TSecurityFtdcLargeVolumeType	LimitVolume;
	///上日融券数量
	TSecurityFtdcLargeVolumeType	YDVolume;
	///剩余可融券数量
	TSecurityFtdcLargeVolumeType	LeftVolume;
	///冻结融券数量
	TSecurityFtdcLargeVolumeType	FrozenVolume;
};

///可融资分配信息
struct CSecurityFtdcCreditCashAssignInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///融资限额
	TSecurityFtdcMoneyType	LimitAmount;
	///上日融资金额
	TSecurityFtdcMoneyType	YDAmount;
};

///证券折算率
struct CSecurityFtdcConversionRateField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///折算比率
	TSecurityFtdcRatioType	ConversionRate;
	///当前是否支持融资交易
	TSecurityFtdcBoolType	IsTradingForMargin;
	///当前是否支持融券交易
	TSecurityFtdcBoolType	IsTradingForShort;
};

///历史信用负债信息
struct CSecurityFtdcHisCreditDebtInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///开仓日期
	TSecurityFtdcDateType	OpenDate;
	///负债类型
	TSecurityFtdcDirectionType	Direction;
	///开仓价
	TSecurityFtdcPriceType	OpenPrice;
	///数量
	TSecurityFtdcLargeVolumeType	Volume;
	///融资融券金额
	TSecurityFtdcMoneyType	Amount;
};

///行情静态信息
struct CSecurityFtdcMarketDataStaticInfoField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///涨停板价
	TSecurityFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TSecurityFtdcPriceType	LowerLimitPrice;
	///昨结算
	TSecurityFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TSecurityFtdcPriceType	PreClosePrice;
	///昨日基金净值
	TSecurityFtdcPriceType	PreIOPV;
	///是否非交易业务
	TSecurityFtdcBoolType	IsNotTrade;
};

///到期回购信息
struct CSecurityFtdcExpireRepurchInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///资金账户代码
	TSecurityFtdcAccountIDType	AccountID;
	///到期类型
	TSecurityFtdcExpireTypeType	ExpireType;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///数量
	TSecurityFtdcLargeVolumeType	Volume;
	///金额
	TSecurityFtdcMoneyType	Amount;
	///利息
	TSecurityFtdcMoneyType	Interest;
};

///债券质押为标准券比例
struct CSecurityFtdcBondPledgeRateField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///折算比率
	TSecurityFtdcRatioType	Ratio;
};

///债券质押代码对照关系
struct CSecurityFtdcPledgeBondField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///质押代码
	TSecurityFtdcInstrumentIDType	PledgeID;
};

///交易所交易员报盘机
struct CSecurityFtdcTraderOfferField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///密码
	TSecurityFtdcPasswordType	Password;
	///报盘类型
	TSecurityFtdcOfferTypeType	OfferType;
	///安装编号
	TSecurityFtdcInstallIDType	InstallID;
	///本地报单编号
	TSecurityFtdcOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TSecurityFtdcTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TSecurityFtdcDateType	ConnectRequestDate;
	///发出连接请求的时间
	TSecurityFtdcTimeType	ConnectRequestTime;
	///上次报告日期
	TSecurityFtdcDateType	LastReportDate;
	///上次报告时间
	TSecurityFtdcTimeType	LastReportTime;
	///完成连接日期
	TSecurityFtdcDateType	ConnectDate;
	///完成连接时间
	TSecurityFtdcTimeType	ConnectTime;
	///启动日期
	TSecurityFtdcDateType	StartDate;
	///启动时间
	TSecurityFtdcTimeType	StartTime;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
};

///交易所行情报盘机
struct CSecurityFtdcMDTraderOfferField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///密码
	TSecurityFtdcPasswordType	Password;
	///报盘类型
	TSecurityFtdcOfferTypeType	OfferType;
	///安装编号
	TSecurityFtdcInstallIDType	InstallID;
	///本地报单编号
	TSecurityFtdcOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TSecurityFtdcTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TSecurityFtdcDateType	ConnectRequestDate;
	///发出连接请求的时间
	TSecurityFtdcTimeType	ConnectRequestTime;
	///上次报告日期
	TSecurityFtdcDateType	LastReportDate;
	///上次报告时间
	TSecurityFtdcTimeType	LastReportTime;
	///完成连接日期
	TSecurityFtdcDateType	ConnectDate;
	///完成连接时间
	TSecurityFtdcTimeType	ConnectTime;
	///启动日期
	TSecurityFtdcDateType	StartDate;
	///启动时间
	TSecurityFtdcTimeType	StartTime;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
};

///前置状态
struct CSecurityFtdcFrontStatusField
{
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///上次报告日期
	TSecurityFtdcDateType	LastReportDate;
	///上次报告时间
	TSecurityFtdcTimeType	LastReportTime;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
};

///用户会话
struct CSecurityFtdcUserSessionField
{
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///登录日期
	TSecurityFtdcDateType	LoginDate;
	///登录时间
	TSecurityFtdcTimeType	LoginTime;
	///IP地址
	TSecurityFtdcIPAddressType	IPAddress;
	///用户端产品信息
	TSecurityFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TSecurityFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TSecurityFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TSecurityFtdcMacAddressType	MacAddress;
};

///报单
struct CSecurityFtdcOrderField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSecurityFtdcOrderRefType	OrderRef;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///报单价格条件
	TSecurityFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSecurityFtdcDirectionType	Direction;
	///组合开平标志
	TSecurityFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSecurityFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSecurityFtdcStockPriceType	LimitPrice;
	///数量
	TSecurityFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSecurityFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSecurityFtdcDateType	GTDDate;
	///成交量类型
	TSecurityFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSecurityFtdcVolumeType	MinVolume;
	///触发条件
	TSecurityFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSecurityFtdcPriceType	StopPrice;
	///强平原因
	TSecurityFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSecurityFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSecurityFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSecurityFtdcRequestIDType	RequestID;
	///本地报单编号
	TSecurityFtdcOrderLocalIDType	OrderLocalID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSecurityFtdcClientIDType	ClientID;
	///合约在交易所的代码
	TSecurityFtdcExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
	///安装编号
	TSecurityFtdcInstallIDType	InstallID;
	///报单提交状态
	TSecurityFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///账户代码
	TSecurityFtdcAccountIDType	AccountID;
	///报单提示序号
	TSecurityFtdcSequenceNoType	NotifySequence;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///报单编号
	TSecurityFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TSecurityFtdcOrderSourceType	OrderSource;
	///报单状态
	TSecurityFtdcOrderStatusType	OrderStatus;
	///报单类型
	TSecurityFtdcOrderTypeType	OrderType;
	///今成交数量
	TSecurityFtdcVolumeType	VolumeTraded;
	///剩余数量
	TSecurityFtdcVolumeType	VolumeTotal;
	///报单日期
	TSecurityFtdcDateType	InsertDate;
	///委托时间
	TSecurityFtdcTimeType	InsertTime;
	///激活时间
	TSecurityFtdcTimeType	ActiveTime;
	///挂起时间
	TSecurityFtdcTimeType	SuspendTime;
	///最后修改时间
	TSecurityFtdcTimeType	UpdateTime;
	///撤销时间
	TSecurityFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TSecurityFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TSecurityFtdcParticipantIDType	ClearingPartID;
	///序号
	TSecurityFtdcSequenceNoType	SequenceNo;
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///用户端产品信息
	TSecurityFtdcProductInfoType	UserProductInfo;
	///状态信息
	TSecurityFtdcErrorMsgType	StatusMsg;
	///用户强评标志
	TSecurityFtdcBoolType	UserForceClose;
	///操作用户代码
	TSecurityFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TSecurityFtdcSequenceNoType	BrokerOrderSeq;
	///相关报单
	TSecurityFtdcOrderSysIDType	RelativeOrderSysID;
	///营业部编号
	TSecurityFtdcBranchIDType	BranchID;
	///成交金额
	TSecurityFtdcMoneyType	TradeAmount;
	///是否ETF
	TSecurityFtdcBoolType	IsETF;
	///合约类型
	TSecurityFtdcInstrumentTypeType	InstrumentType;
};

///报单操作
struct CSecurityFtdcOrderActionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TSecurityFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TSecurityFtdcOrderRefType	OrderRef;
	///请求编号
	TSecurityFtdcRequestIDType	RequestID;
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///操作标志
	TSecurityFtdcActionFlagType	ActionFlag;
	///价格
	TSecurityFtdcPriceType	LimitPrice;
	///数量变化
	TSecurityFtdcVolumeType	VolumeChange;
	///操作日期
	TSecurityFtdcDateType	ActionDate;
	///操作时间
	TSecurityFtdcTimeType	ActionTime;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
	///安装编号
	TSecurityFtdcInstallIDType	InstallID;
	///本地报单编号
	TSecurityFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TSecurityFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSecurityFtdcClientIDType	ClientID;
	///业务单元
	TSecurityFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TSecurityFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///营业部编号
	TSecurityFtdcBranchIDType	BranchID;
	///状态信息
	TSecurityFtdcErrorMsgType	StatusMsg;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///合约类型
	TSecurityFtdcInstrumentTypeType	InstrumentType;
};

///错误报单
struct CSecurityFtdcErrOrderField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSecurityFtdcOrderRefType	OrderRef;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///报单价格条件
	TSecurityFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSecurityFtdcDirectionType	Direction;
	///组合开平标志
	TSecurityFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSecurityFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSecurityFtdcStockPriceType	LimitPrice;
	///数量
	TSecurityFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSecurityFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSecurityFtdcDateType	GTDDate;
	///成交量类型
	TSecurityFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSecurityFtdcVolumeType	MinVolume;
	///触发条件
	TSecurityFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSecurityFtdcPriceType	StopPrice;
	///强平原因
	TSecurityFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSecurityFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSecurityFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSecurityFtdcRequestIDType	RequestID;
	///用户强评标志
	TSecurityFtdcBoolType	UserForceClose;
	///错误代码
	TSecurityFtdcErrorIDType	ErrorID;
	///错误信息
	TSecurityFtdcErrorMsgType	ErrorMsg;
};

///错误报单操作
struct CSecurityFtdcErrOrderActionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TSecurityFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TSecurityFtdcOrderRefType	OrderRef;
	///请求编号
	TSecurityFtdcRequestIDType	RequestID;
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///操作标志
	TSecurityFtdcActionFlagType	ActionFlag;
	///价格
	TSecurityFtdcPriceType	LimitPrice;
	///数量变化
	TSecurityFtdcVolumeType	VolumeChange;
	///操作日期
	TSecurityFtdcDateType	ActionDate;
	///操作时间
	TSecurityFtdcTimeType	ActionTime;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
	///安装编号
	TSecurityFtdcInstallIDType	InstallID;
	///本地报单编号
	TSecurityFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TSecurityFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSecurityFtdcClientIDType	ClientID;
	///业务单元
	TSecurityFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TSecurityFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///营业部编号
	TSecurityFtdcBranchIDType	BranchID;
	///状态信息
	TSecurityFtdcErrorMsgType	StatusMsg;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///错误代码
	TSecurityFtdcErrorIDType	ErrorID;
	///错误信息
	TSecurityFtdcErrorMsgType	ErrorMsg;
	///合约类型
	TSecurityFtdcInstrumentTypeType	InstrumentType;
};

///成交
struct CSecurityFtdcTradeField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSecurityFtdcOrderRefType	OrderRef;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///成交编号
	TSecurityFtdcTradeIDType	TradeID;
	///买卖方向
	TSecurityFtdcDirectionType	Direction;
	///报单编号
	TSecurityFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSecurityFtdcClientIDType	ClientID;
	///交易角色
	TSecurityFtdcTradingRoleType	TradingRole;
	///合约在交易所的代码
	TSecurityFtdcExchangeInstIDType	ExchangeInstID;
	///开平标志
	TSecurityFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TSecurityFtdcHedgeFlagType	HedgeFlag;
	///价格
	TSecurityFtdcStockPriceType	Price;
	///数量
	TSecurityFtdcVolumeType	Volume;
	///成交时期
	TSecurityFtdcDateType	TradeDate;
	///成交时间
	TSecurityFtdcTimeType	TradeTime;
	///成交类型
	TSecurityFtdcTradeTypeType	TradeType;
	///成交价来源
	TSecurityFtdcPriceSourceType	PriceSource;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
	///本地报单编号
	TSecurityFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TSecurityFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TSecurityFtdcBusinessUnitType	BusinessUnit;
	///序号
	TSecurityFtdcSequenceNoType	SequenceNo;
	///成交来源
	TSecurityFtdcTradeSourceType	TradeSource;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///经纪公司报单编号
	TSecurityFtdcSequenceNoType	BrokerOrderSeq;
	///成交金额
	TSecurityFtdcMoneyType	TradeAmount;
	///成交序号
	TSecurityFtdcTradeIndexType	TradeIndex;
};

///投资者持仓
struct CSecurityFtdcInvestorPositionField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///持仓多空方向
	TSecurityFtdcPosiDirectionType	PosiDirection;
	///投机套保标志
	TSecurityFtdcHedgeFlagType	HedgeFlag;
	///持仓日期
	TSecurityFtdcPositionDateType	PositionDate;
	///上日持仓
	TSecurityFtdcLargeVolumeType	YdPosition;
	///总持仓
	TSecurityFtdcLargeVolumeType	Position;
	///多头冻结
	TSecurityFtdcLargeVolumeType	LongFrozen;
	///空头冻结
	TSecurityFtdcLargeVolumeType	ShortFrozen;
	///开仓冻结金额
	TSecurityFtdcMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TSecurityFtdcMoneyType	ShortFrozenAmount;
	///开仓量
	TSecurityFtdcLargeVolumeType	OpenVolume;
	///平仓量
	TSecurityFtdcLargeVolumeType	CloseVolume;
	///开仓金额
	TSecurityFtdcMoneyType	OpenAmount;
	///平仓金额
	TSecurityFtdcMoneyType	CloseAmount;
	///持仓成本
	TSecurityFtdcMoneyType	PositionCost;
	///冻结的资金
	TSecurityFtdcMoneyType	FrozenCash;
	///资金差额
	TSecurityFtdcMoneyType	CashIn;
	///手续费
	TSecurityFtdcMoneyType	Commission;
	///上次结算价
	TSecurityFtdcPriceType	PreSettlementPrice;
	///本次结算价
	TSecurityFtdcPriceType	SettlementPrice;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///开仓成本
	TSecurityFtdcMoneyType	OpenCost;
	///交易所保证金
	TSecurityFtdcMoneyType	ExchangeMargin;
	///今日持仓
	TSecurityFtdcLargeVolumeType	TodayPosition;
	///过户费
	TSecurityFtdcMoneyType	TransferFee;
	///印花税
	TSecurityFtdcMoneyType	StampTax;
	///今日申购赎回数量
	TSecurityFtdcLargeVolumeType	TodayPurRedVolume;
	///折算率
	TSecurityFtdcRatioType	ConversionRate;
	///折算金额
	TSecurityFtdcMoneyType	ConversionAmount;
	///证券价值
	TSecurityFtdcMoneyType	StockValue;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///AccountID
	TSecurityFtdcAccountIDType	AccountID;
	///质押入库数量
	TSecurityFtdcLargeVolumeType	PledgeInPosition;
	///正回购使用的标准券数量
	TSecurityFtdcLargeVolumeType	RepurchasePosition;
	///ETF申赎空头冻结
	TSecurityFtdcLargeVolumeType	PurRedShortFrozen;
	///融资买入数量
	TSecurityFtdcLargeVolumeType	MarginTradeVolume;
	///融资买入金额
	TSecurityFtdcMoneyType	MarginTradeAmount;
	///融资买入冻结数量
	TSecurityFtdcLargeVolumeType	MarginTradeFrozenVolume;
	///融资买入冻结金额
	TSecurityFtdcMoneyType	MarginTradeFrozenAmount;
	///融资买入盈亏
	TSecurityFtdcMoneyType	MarginTradeConversionProfit;
	///融券卖出数量
	TSecurityFtdcLargeVolumeType	ShortSellVolume;
	///融券卖出金额
	TSecurityFtdcMoneyType	ShortSellAmount;
	///融券卖出冻结数量
	TSecurityFtdcLargeVolumeType	ShortSellFrozenVolume;
	///融券卖出冻结金额
	TSecurityFtdcMoneyType	ShortSellFrozenAmount;
	///融券卖出盈亏
	TSecurityFtdcMoneyType	ShortSellConversionProfit;
	///融券总市值
	TSecurityFtdcMoneyType	SSStockValue;
	///今日融资持仓
	TSecurityFtdcLargeVolumeType	TodayMTPosition;
	///今日融券持仓
	TSecurityFtdcLargeVolumeType	TodaySSPosition;
	///历史持仓开仓成本
	TSecurityFtdcMoneyType	YdOpenCost;
	///锁定仓位
	TSecurityFtdcLargeVolumeType	LockPosition;
	///备兑仓位
	TSecurityFtdcLargeVolumeType	CoverPosition;
	///锁定冻结仓位
	TSecurityFtdcLargeVolumeType	LockFrozenPosition;
	///解锁冻结仓位
	TSecurityFtdcLargeVolumeType	UnlockFrozenPosition;
	///备兑冻结仓位
	TSecurityFtdcLargeVolumeType	CoverFrozenPosition;
	///行权冻结仓位
	TSecurityFtdcLargeVolumeType	ExecFrozenPosition;
	///上日备兑仓位
	TSecurityFtdcLargeVolumeType	YDCoverPosition;
};

///出入金同步
struct CSecurityFtdcSyncDepositField
{
	///出入金流水号
	TSecurityFtdcDepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///入金金额
	TSecurityFtdcMoneyType	Deposit;
	///是否强制进行
	TSecurityFtdcBoolType	IsForce;
	///账户代码
	TSecurityFtdcAccountIDType	AccountID;
};

///查询交易所
struct CSecurityFtdcQryExchangeField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///查询产品
struct CSecurityFtdcQryProductField
{
	///产品代码
	TSecurityFtdcInstrumentIDType	ProductID;
};

///查询合约
struct CSecurityFtdcQryInstrumentField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TSecurityFtdcExchangeInstIDType	ExchangeInstID;
	///产品代码
	TSecurityFtdcInstrumentIDType	ProductID;
};

///查询经纪公司
struct CSecurityFtdcQryBrokerField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
};

///查询经纪公司会员代码
struct CSecurityFtdcQryPartBrokerField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
};

///查询投资者
struct CSecurityFtdcQryInvestorField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///查询交易编码
struct CSecurityFtdcQryTradingCodeField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///客户代码
	TSecurityFtdcClientIDType	ClientID;
};

///查询管理用户
struct CSecurityFtdcQrySuperUserField
{
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///查询管理用户功能权限
struct CSecurityFtdcQrySuperUserFunctionField
{
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///查询经纪公司用户
struct CSecurityFtdcQryBrokerUserField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///查询经纪公司用户权限
struct CSecurityFtdcQryBrokerUserFunctionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///查询资金账户
struct CSecurityFtdcQryTradingAccountField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///查询禁止登录用户
struct CSecurityFtdcQryLoginForbiddenUserField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///查询行情
struct CSecurityFtdcQryDepthMarketDataField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询合约交易权限
struct CSecurityFtdcQryInstrumentTradingRightField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询投资者持仓明细
struct CSecurityFtdcQryInvestorPositionDetailField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询债券利息
struct CSecurityFtdcQryBondInterestField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询市值配售信息
struct CSecurityFtdcQryMarketRationInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///查询合约手续费率
struct CSecurityFtdcQryInstrumentCommissionRateField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TSecurityFtdcDirectionType	Direction;
	///开平标志
	TSecurityFtdcOffsetFlagType	OffsetFlag;
};

///查询余券信息
struct CSecurityFtdcQryExcessStockInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询投资者帐户关系
struct CSecurityFtdcQryInvestorAccountField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///查询ETF合约
struct CSecurityFtdcQryETFInstrumentField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///ETF证券代码
	TSecurityFtdcInstrumentIDType	ETFInstrumentID;
};

///查询ETF股票篮
struct CSecurityFtdcQryETFBasketField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///ETF证券代码
	TSecurityFtdcInstrumentIDType	ETFInstrumentID;
};

///查询OF合约
struct CSecurityFtdcQryOFInstrumentField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///ETF证券代码
	TSecurityFtdcInstrumentIDType	OFInstrumentID;
};

///查询SF合约
struct CSecurityFtdcQrySFInstrumentField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///ETF证券代码
	TSecurityFtdcInstrumentIDType	SFInstrumentID;
};

///查询合约单手保证金
struct CSecurityFtdcQryInstrumentUnitMarginField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询期权资金限制参数
struct CSecurityFtdcQryOptionsFundLimitParamField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///查询投资者期权持仓
struct CSecurityFtdcQryInvestorOptionsPositionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///标的合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询预交割信息
struct CSecurityFtdcQryPreDelivInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询可融券分配信息
struct CSecurityFtdcQryCreditStockAssignInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询可融资分配信息
struct CSecurityFtdcQryCreditCashAssignInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///查询证券折算率
struct CSecurityFtdcQryConversionRateField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询历史信用负债信息
struct CSecurityFtdcQryHisCreditDebtInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询行情静态信息
struct CSecurityFtdcQryMarketDataStaticInfoField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询到期回购信息
struct CSecurityFtdcQryExpireRepurchInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///查询债券质押为标准券比例
struct CSecurityFtdcQryBondPledgeRateField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询债券质押代码对照关系
struct CSecurityFtdcQryPledgeBondField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询交易员报盘机
struct CSecurityFtdcQryTraderOfferField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
};

///查询行情报盘机
struct CSecurityFtdcQryMDTraderOfferField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSecurityFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
};

///查询前置状态
struct CSecurityFtdcQryFrontStatusField
{
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
};

///查询用户会话
struct CSecurityFtdcQryUserSessionField
{
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///查询报单
struct CSecurityFtdcQryOrderField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSecurityFtdcOrderSysIDType	OrderSysID;
	///开始时间
	TSecurityFtdcTimeType	InsertTimeStart;
	///结束时间
	TSecurityFtdcTimeType	InsertTimeEnd;
};

///查询报单操作
struct CSecurityFtdcQryOrderActionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///查询错误报单
struct CSecurityFtdcQryErrOrderField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///查询错误报单操作
struct CSecurityFtdcQryErrOrderActionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///查询成交
struct CSecurityFtdcQryTradeField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///成交编号
	TSecurityFtdcTradeIDType	TradeID;
	///开始时间
	TSecurityFtdcTimeType	TradeTimeStart;
	///结束时间
	TSecurityFtdcTimeType	TradeTimeEnd;
};

///查询投资者持仓
struct CSecurityFtdcQryInvestorPositionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///查询出入金流水
struct CSecurityFtdcQrySyncDepositField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///出入金流水号
	TSecurityFtdcDepositSeqNoType	DepositSeqNo;
};

///用户口令变更
struct CSecurityFtdcUserPasswordUpdateField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///原来的口令
	TSecurityFtdcPasswordType	OldPassword;
	///新的口令
	TSecurityFtdcPasswordType	NewPassword;
};

///资金账户口令变更域
struct CSecurityFtdcTradingAccountPasswordUpdateField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSecurityFtdcAccountIDType	AccountID;
	///原来的口令
	TSecurityFtdcPasswordType	OldPassword;
	///新的口令
	TSecurityFtdcPasswordType	NewPassword;
};

///手工同步用户动态令牌
struct CSecurityFtdcManualSyncBrokerUserOTPField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///动态令牌类型
	TSecurityFtdcOTPTypeType	OTPType;
	///第一个动态密码
	TSecurityFtdcPasswordType	FirstOTP;
	///第二个动态密码
	TSecurityFtdcPasswordType	SecondOTP;
};

///经纪公司用户口令
struct CSecurityFtdcBrokerUserPasswordField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///密码
	TSecurityFtdcPasswordType	Password;
};

///资金账户口令域
struct CSecurityFtdcTradingAccountPasswordField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSecurityFtdcAccountIDType	AccountID;
	///密码
	TSecurityFtdcPasswordType	Password;
};

///用户权限
struct CSecurityFtdcUserRightField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///客户权限类型
	TSecurityFtdcUserRightTypeType	UserRightType;
	///是否禁止
	TSecurityFtdcBoolType	IsForbidden;
};

///投资者账户
struct CSecurityFtdcInvestorAccountField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///投资者帐号
	TSecurityFtdcAccountIDType	AccountID;
	///是否主账户
	TSecurityFtdcBoolType	IsDefault;
	///账户类型
	TSecurityFtdcAccountTypeType	AccountType;
	///是否活跃
	TSecurityFtdcBoolType	IsActive;
	///上交所交易单元号
	TSecurityFtdcTraderIDType	SHBranchPBU;
	///深交所交易单元号
	TSecurityFtdcTraderIDType	SZBranchPBU;
};

///用户IP
struct CSecurityFtdcUserIPField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///IP地址
	TSecurityFtdcIPAddressType	IPAddress;
	///IP地址掩码
	TSecurityFtdcIPAddressType	IPMask;
	///Mac地址
	TSecurityFtdcMacAddressType	MacAddress;
};

///用户动态令牌参数
struct CSecurityFtdcBrokerUserOTPParamField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///动态令牌提供商
	TSecurityFtdcOTPVendorsIDType	OTPVendorsID;
	///动态令牌序列号
	TSecurityFtdcSerialNumberType	SerialNumber;
	///令牌密钥
	TSecurityFtdcAuthKeyType	AuthKey;
	///漂移值
	TSecurityFtdcLastDriftType	LastDrift;
	///成功值
	TSecurityFtdcLastSuccessType	LastSuccess;
	///动态令牌类型
	TSecurityFtdcOTPTypeType	OTPType;
};

///用户登录请求
struct CSecurityFtdcReqUserLoginField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///密码
	TSecurityFtdcPasswordType	Password;
	///用户端产品信息
	TSecurityFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TSecurityFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TSecurityFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TSecurityFtdcMacAddressType	MacAddress;
	///动态密码
	TSecurityFtdcPasswordType	OneTimePassword;
	///终端IP地址
	TSecurityFtdcIPAddressType	ClientIPAddress;
	///客户端认证码
	TSecurityFtdcAuthCodeType	AuthCode;
	///随机码
	TSecurityFtdcAuthCodeType	RandCode;
	///硬盘序列号
	TSecurityFtdcHDSerialNumberType	HDSerialNumber;
};

///用户登录应答
struct CSecurityFtdcRspUserLoginField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///登录成功时间
	TSecurityFtdcTimeType	LoginTime;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///交易系统名称
	TSecurityFtdcSystemNameType	SystemName;
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///最大报单引用
	TSecurityFtdcOrderRefType	MaxOrderRef;
};

///用户登出请求
struct CSecurityFtdcUserLogoutField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///全部登出信息
struct CSecurityFtdcLogoutAllField
{
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///系统名称
	TSecurityFtdcSystemNameType	SystemName;
};

///强制交易员退出
struct CSecurityFtdcForceUserLogoutField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///经纪公司用户激活
struct CSecurityFtdcActivateBrokerUserField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///认证随机码
struct CSecurityFtdcAuthRandCodeField
{
	///随机码
	TSecurityFtdcAuthCodeType	RandCode;
};

///输入报单
struct CSecurityFtdcInputOrderField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSecurityFtdcOrderRefType	OrderRef;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///报单价格条件
	TSecurityFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSecurityFtdcDirectionType	Direction;
	///组合开平标志
	TSecurityFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSecurityFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSecurityFtdcStockPriceType	LimitPrice;
	///数量
	TSecurityFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSecurityFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSecurityFtdcDateType	GTDDate;
	///成交量类型
	TSecurityFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSecurityFtdcVolumeType	MinVolume;
	///触发条件
	TSecurityFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSecurityFtdcPriceType	StopPrice;
	///强平原因
	TSecurityFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSecurityFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSecurityFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSecurityFtdcRequestIDType	RequestID;
	///用户强评标志
	TSecurityFtdcBoolType	UserForceClose;
};

///输入报单操作
struct CSecurityFtdcInputOrderActionField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TSecurityFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TSecurityFtdcOrderRefType	OrderRef;
	///请求编号
	TSecurityFtdcRequestIDType	RequestID;
	///前置编号
	TSecurityFtdcFrontIDType	FrontID;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///操作标志
	TSecurityFtdcActionFlagType	ActionFlag;
	///价格
	TSecurityFtdcPriceType	LimitPrice;
	///数量变化
	TSecurityFtdcVolumeType	VolumeChange;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所交易员代码
	TSecurityFtdcTraderIDType	BranchPBU;
	///本地报单编号
	TSecurityFtdcOrderLocalIDType	OrderLocalID;
};

///指定的合约
struct CSecurityFtdcSpecificInstrumentField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///指定的交易所
struct CSecurityFtdcSpecificExchangeField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///行情基础属性
struct CSecurityFtdcMarketDataBaseField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///上次结算价
	TSecurityFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TSecurityFtdcPriceType	PreClosePrice;
	///昨持仓量
	TSecurityFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TSecurityFtdcRatioType	PreDelta;
	///昨日基金净值
	TSecurityFtdcPriceType	PreIOPV;
};

///行情静态属性
struct CSecurityFtdcMarketDataStaticField
{
	///今开盘
	TSecurityFtdcPriceType	OpenPrice;
	///最高价
	TSecurityFtdcPriceType	HighestPrice;
	///最低价
	TSecurityFtdcPriceType	LowestPrice;
	///今收盘
	TSecurityFtdcPriceType	ClosePrice;
	///涨停板价
	TSecurityFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TSecurityFtdcPriceType	LowerLimitPrice;
	///本次结算价
	TSecurityFtdcPriceType	SettlementPrice;
	///今虚实度
	TSecurityFtdcRatioType	CurrDelta;
	///基金净值
	TSecurityFtdcPriceType	IOPV;
	///动态参考价格
	TSecurityFtdcPriceType	AuctionPrice;
};

///行情最新成交属性
struct CSecurityFtdcMarketDataLastMatchField
{
	///最新价
	TSecurityFtdcPriceType	LastPrice;
	///数量
	TSecurityFtdcLargeVolumeType	Volume;
	///成交金额
	TSecurityFtdcMoneyType	Turnover;
	///持仓量
	TSecurityFtdcLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CSecurityFtdcMarketDataBestPriceField
{
	///申买价一
	TSecurityFtdcPriceType	BidPrice1;
	///申买量一
	TSecurityFtdcLargeVolumeType	BidVolume1;
	///申卖价一
	TSecurityFtdcPriceType	AskPrice1;
	///申卖量一
	TSecurityFtdcLargeVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CSecurityFtdcMarketDataBid23Field
{
	///申买价二
	TSecurityFtdcPriceType	BidPrice2;
	///申买量二
	TSecurityFtdcLargeVolumeType	BidVolume2;
	///申买价三
	TSecurityFtdcPriceType	BidPrice3;
	///申买量三
	TSecurityFtdcLargeVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CSecurityFtdcMarketDataAsk23Field
{
	///申卖价二
	TSecurityFtdcPriceType	AskPrice2;
	///申卖量二
	TSecurityFtdcLargeVolumeType	AskVolume2;
	///申卖价三
	TSecurityFtdcPriceType	AskPrice3;
	///申卖量三
	TSecurityFtdcLargeVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CSecurityFtdcMarketDataBid45Field
{
	///申买价四
	TSecurityFtdcPriceType	BidPrice4;
	///申买量四
	TSecurityFtdcLargeVolumeType	BidVolume4;
	///申买价五
	TSecurityFtdcPriceType	BidPrice5;
	///申买量五
	TSecurityFtdcLargeVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CSecurityFtdcMarketDataAsk45Field
{
	///申卖价四
	TSecurityFtdcPriceType	AskPrice4;
	///申卖量四
	TSecurityFtdcLargeVolumeType	AskVolume4;
	///申卖价五
	TSecurityFtdcPriceType	AskPrice5;
	///申卖量五
	TSecurityFtdcLargeVolumeType	AskVolume5;
};

///行情更新时间属性
struct CSecurityFtdcMarketDataUpdateTimeField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TSecurityFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TSecurityFtdcMillisecType	UpdateMillisec;
	///业务日期
	TSecurityFtdcDateType	ActionDay;
	///交易阶段
	TSecurityFtdcTradingPhaseType	TradingPhase;
	///开仓限制
	TSecurityFtdcOpenRestrictionType	OpenRestriction;
};

///成交均价
struct CSecurityFtdcMarketDataAveragePriceField
{
	///当日均价
	TSecurityFtdcPriceType	AveragePrice;
};

///行情交易所代码属性
struct CSecurityFtdcMarketDataExchangeField
{
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///信息分发
struct CSecurityFtdcDisseminationField
{
	///序列系列号
	TSecurityFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TSecurityFtdcSequenceNoType	SequenceNo;
};

///资金转账输入
struct CSecurityFtdcInputFundTransferField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///投资者资金帐号
	TSecurityFtdcAccountIDType	AccountID;
	///资金帐户密码
	TSecurityFtdcPasswordType	Password;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///交易金额
	TSecurityFtdcTradeAmountType	TradeAmount;
	///摘要
	TSecurityFtdcDigestType	Digest;
	///账户类型
	TSecurityFtdcAccountTypeType	AccountType;
};

///资金转账
struct CSecurityFtdcFundTransferField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///投资者资金帐号
	TSecurityFtdcAccountIDType	AccountID;
	///资金帐户密码
	TSecurityFtdcPasswordType	Password;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///交易金额
	TSecurityFtdcTradeAmountType	TradeAmount;
	///摘要
	TSecurityFtdcDigestType	Digest;
	///会话编号
	TSecurityFtdcSessionIDType	SessionID;
	///Liber核心流水号
	TSecurityFtdcLiberSerialType	LiberSerial;
	///转账平台流水号
	TSecurityFtdcPlateSerialType	PlateSerial;
	///第三方流水号
	TSecurityFtdcBankSerialType	TransferSerial;
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///转账时间
	TSecurityFtdcTimeType	TradeTime;
	///出入金方向
	TSecurityFtdcFundDirectionType	FundDirection;
	///错误代码
	TSecurityFtdcErrorIDType	ErrorID;
	///错误信息
	TSecurityFtdcErrorMsgType	ErrorMsg;
};

///资金转账查询请求
struct CSecurityFtdcQryFundTransferSerialField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者资金帐号
	TSecurityFtdcAccountIDType	AccountID;
	///账户类型
	TSecurityFtdcAccountTypeType	AccountType;
};

///资金内转
struct CSecurityFtdcFundInterTransferField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///资金账户代码
	TSecurityFtdcAccountIDType	AccountID;
	///资金账户密码
	TSecurityFtdcPasswordType	Password;
	///金额
	TSecurityFtdcTradeAmountType	TradeAmount;
	///内转类型
	TSecurityFtdcFundInterTransferTypeType	TransferType;
	///资金内转编号
	TSecurityFtdcLiberSerialType	SerialID;
};

///资金内转流水
struct CSecurityFtdcFundInterTransferSerialField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///资金账户代码
	TSecurityFtdcAccountIDType	AccountID;
	///资金账户密码
	TSecurityFtdcPasswordType	Password;
	///金额
	TSecurityFtdcTradeAmountType	TradeAmount;
	///内转类型
	TSecurityFtdcFundInterTransferTypeType	TransferType;
	///资金内转编号
	TSecurityFtdcLiberSerialType	SerialID;
	///转账时间
	TSecurityFtdcTimeType	TransferTime;
	///错误代码
	TSecurityFtdcErrorIDType	ErrorID;
	///错误信息
	TSecurityFtdcErrorMsgType	ErrorMsg;
};

///资金内转流水查询请求
struct CSecurityFtdcQryFundInterTransferSerialField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSecurityFtdcInvestorIDType	InvestorID;
};

///获取数据库信息
struct CSecurityFtdcFetchDBInfoField
{
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///密码
	TSecurityFtdcPasswordType	Password;
	///数据库索引
	TSecurityFtdcUserNameType	DBIndex;
	///数据库IP地址
	TSecurityFtdcIPAddressType	IPAddress;
	///数据库IP端口
	TSecurityFtdcIPPortType	IPPort;
	///数据库名称
	TSecurityFtdcUserNameType	DBName;
	///数据库用户名
	TSecurityFtdcUserIDType	DBUserID;
	///数据库密码
	TSecurityFtdcPasswordType	DBPassword;
};

///MD用户信息
struct CSecurityFtdcMDUserInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///用户名称
	TSecurityFtdcUserNameType	UserName;
	///密码
	TSecurityFtdcPasswordType	Password;
	///行情系统编号
	TSecurityFtdcSequenceNoType	MDSysID;
	///股票最大订阅数量
	TSecurityFtdcVolumeType	MaxStockCount;
	///期权最大订阅数量
	TSecurityFtdcVolumeType	MaxOptionsCount;
};


#pragma pack(pop) 
#endif
