/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_api_struct_compatible.h
///@brief 定义业务的兼容数据结构
/////////////////////////////////////////////////////////////////////////

#if !defined(XTP_FTDCSTRUCT_H)
#define XTP_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xtp_api_data_type.h"

///指定的合约
struct CXTPSpecificInstrumentField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
};


///深度行情
struct CXTPDepthMarketDataField
{
	///交易日
	TXTPDateType	TradingDay;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TXTPExchangeInstIDType	ExchangeInstID;
	///最新价
	TXTPPriceType	LastPrice;
	///上次结算价
	TXTPPriceType	PreSettlementPrice;
	///昨收盘
	TXTPPriceType	PreClosePrice;
	///昨持仓量
	TXTPLargeVolumeType	PreOpenInterest;
	///今开盘
	TXTPPriceType	OpenPrice;
	///最高价
	TXTPPriceType	HighestPrice;
	///最低价
	TXTPPriceType	LowestPrice;
	///数量
	TXTPVolumeType	Volume;
	///成交金额
	TXTPMoneyType	Turnover;
	///持仓量
	TXTPLargeVolumeType	OpenInterest;
	///今收盘
	TXTPPriceType	ClosePrice;
	///本次结算价
	TXTPPriceType	SettlementPrice;
	///涨停板价
	TXTPPriceType	UpperLimitPrice;
	///跌停板价
	TXTPPriceType	LowerLimitPrice;
	///昨虚实度
	TXTPRatioType	PreDelta;
	///今虚实度
	TXTPRatioType	CurrDelta;
	///最后修改时间
	TXTPTimeType	UpdateTime;
	///最后修改毫秒
	TXTPMillisecType	UpdateMillisec;
	///当日均价
	TXTPPriceType	AveragePrice;
	///业务日期
	TXTPDateType	ActionDay;
	///数量(新)
	TXTPLargeVolumeType	Volume_New;

	union {
		struct {
			///申买价一
			TXTPPriceType	BidPrice1;
			///申买价二
			TXTPPriceType	BidPrice2;
			///申买价三
			TXTPPriceType	BidPrice3;
			///申买价四
			TXTPPriceType	BidPrice4;
			///申买价五
			TXTPPriceType	BidPrice5;
			///申买价六
			TXTPPriceType	BidPrice6;
			///申买价七
			TXTPPriceType	BidPrice7;
			///申买价八
			TXTPPriceType	BidPrice8;
			///申买价九
			TXTPPriceType	BidPrice9;
			///申买价十
			TXTPPriceType	BidPrice10;
		};
		struct {
			///十档买盘价
			TXTPPriceType BidPrices[10];
		};
	};
	union {
		struct {
			///申卖价一
			TXTPPriceType	AskPrice1;
			///申卖价二
			TXTPPriceType	AskPrice2;
			///申卖价三
			TXTPPriceType	AskPrice3;
			///申卖价四
			TXTPPriceType	AskPrice4;
			///申卖价五
			TXTPPriceType	AskPrice5;
			///申卖价六
			TXTPPriceType	AskPrice6;
			///申卖价七
			TXTPPriceType	AskPrice7;
			///申卖价八
			TXTPPriceType	AskPrice8;
			///申卖价九
			TXTPPriceType	AskPrice9;
			///申卖价十
			TXTPPriceType	AskPrice10;
		};
		struct {
			///十档申卖价
			TXTPPriceType	AskPrices[10];
		};
	};
	union {
		struct {
			///申买量一
			TXTPVolumeType	BidVolume1;
			///申买量二
			TXTPVolumeType	BidVolume2;
			///申买量三
			TXTPVolumeType	BidVolume3;
			///申买量四
			TXTPVolumeType	BidVolume4;
			///申买量五
			TXTPVolumeType	BidVolume5;
			///申买量六
			TXTPVolumeType	BidVolume6;
			///申买量七
			TXTPVolumeType	BidVolume7;
			///申买量八
			TXTPVolumeType	BidVolume8;
			///申买量九
			TXTPVolumeType	BidVolume9;
			///申买量十
			TXTPVolumeType	BidVolume10;
		};
		struct {
			///十档申买量
			TXTPVolumeType	BidVolumes[10];
		};
	};
	union {
		struct {
			///申卖量一
			TXTPVolumeType	AskVolume1;
			///申卖量二
			TXTPVolumeType	AskVolume2;
			///申卖量三
			TXTPVolumeType	AskVolume3;
			///申卖量四
			TXTPVolumeType	AskVolume4;
			///申卖量五
			TXTPVolumeType	AskVolume5;
			///申卖量六
			TXTPVolumeType	AskVolume6;
			///申卖量七
			TXTPVolumeType	AskVolume7;
			///申卖量八
			TXTPVolumeType	AskVolume8;
			///申卖量九
			TXTPVolumeType	AskVolume9;
			///申卖量十
			TXTPVolumeType	AskVolume10;
		};
		struct {
			///十档申卖量
			TXTPVolumeType	AskVolumes[10];
		};
	};

	///成交笔数
	TXTPVolumeType NumTrades;
	///当前交易状态说明
	char InstrumentStatus[8];
	///委托买入总量
	TXTPVolumeType TotalBidQty;
	///委托卖出总量
	TXTPVolumeType TotalOfferQty;
	///加权平均委买价格
	TXTPPriceType WeightedAvgBidPx;
	///加权平均委卖价格
	TXTPPriceType WeightedAvgOfferPx;
	///债券加权平均委买价格
	TXTPPriceType AltWeightedAvgBidPx;
	///债券加权平均委卖价格
	TXTPPriceType AltWeightedAvgOfferPx;
	///债券到期收益率
	TXTPPriceType YieldToMaturity;
	///ETF净值估值
	TXTPPriceType IOPV;
	///ETF申购笔数
	TXTPVolumeType ETFBuyNumber;
	///ETF赎回笔数
	TXTPVolumeType ETFSellNumber;
	///ETF申购数量
	TXTPLargeVolumeType ETFBuyAmount;
	///ETF赎回数量
	TXTPMoneyType ETFBuyMoney;
	///ETF申购金额
	TXTPLargeVolumeType ETFSellAmount;
	///ETF赎回金额
	TXTPMoneyType ETFSellMoney;
	///权证执行的总数量
	TXTPLargeVolumeType TotalWarrantExecQty;
	///权证跌停价格（元）
	TXTPPriceType WarLowerPx;
	///权证涨停价格（元）
	TXTPPriceType WarUpperPx;
	///买入撤单笔数
	TXTPVolumeType WithdrawBuyNumber;
	///卖出撤单笔数
	TXTPVolumeType WithdrawSellNumber;
	///买入撤单数量
	TXTPLargeVolumeType WithdrawBuyAmount;
	///卖出撤单数量
	TXTPLargeVolumeType WithdrawSellAmount;
	///买入撤单金额
	TXTPMoneyType WithdrawBuyMoney;
	///卖出撤单金额
	TXTPMoneyType WithdrawSellMoney;
	///买入总笔数
	TXTPVolumeType TotalBidNumber;
	///卖出总笔数
	TXTPVolumeType TotalOfferNumber;
	///买入委托成交最大等待时间
	TXTPVolumeType BidTradeMaxDuration;
	///卖出委托成交最大等待时间
	TXTPVolumeType OfferTradeMaxDuration;
	///买方委托价位数
	TXTPVolumeType NumBidOrders;
	///卖方委托价位数
	TXTPVolumeType NumOfferOrders;
	///成交时间（UA3113）
	int TradeTime;
	///闭市标志（UA103/UA104）
	char EndOfDayMaker[4];
	///合约持仓量（UA103）
	TXTPLargeVolumeType TotalLongPosition;
	///市盈率1（2位小数）（UA103）
	double PERatio1;
	///市盈率2（2位小数）（UA103）
	double PERatio2;

};


///响应信息
struct CXTPRspInfoField
{
	///错误代码
	TXTPErrorIDType	ErrorID;
	///错误信息
	TXTPErrorMsgType	ErrorMsg;
};

///交易所
struct CXTPExchangeField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///交易所名称
	TXTPExchangeNameType	ExchangeName;
	///交易所属性
	TXTPExchangePropertyType	ExchangeProperty;
};

///产品
struct CXTPProductField
{
	///产品代码
	TXTPInstrumentIDType	ProductID;
	///产品名称
	TXTPProductNameType	ProductName;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///产品类型
	TXTPProductClassType	ProductClass;
	///合约数量乘数
	TXTPVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TXTPPriceType	PriceTick;
	///市价单最大下单量
	TXTPVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TXTPVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TXTPVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TXTPVolumeType	MinLimitOrderVolume;
	///持仓类型
	TXTPPositionTypeType	PositionType;
	///持仓日期类型
	TXTPPositionDateTypeType	PositionDateType;
	///ETF最小交易单位
	TXTPVolumeType	EFTMinTradeVolume;
};

///合约
struct CXTPInstrumentField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约名称
	TXTPInstrumentNameType	InstrumentName;
	///合约在交易所的代码
	TXTPExchangeInstIDType	ExchangeInstID;
	///产品代码
	TXTPInstrumentIDType	ProductID;
	///产品类型
	TXTPProductClassType	ProductClass;
	///交割年份
	TXTPYearType	DeliveryYear;
	///交割月
	TXTPMonthType	DeliveryMonth;
	///市价单最大下单量
	TXTPVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TXTPVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TXTPVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TXTPVolumeType	MinLimitOrderVolume;
	///合约数量乘数
	TXTPVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TXTPPriceType	PriceTick;
	///创建日
	TXTPDateType	CreateDate;
	///上市日
	TXTPDateType	OpenDate;
	///到期日
	TXTPDateType	ExpireDate;
	///开始交割日
	TXTPDateType	StartDelivDate;
	///结束交割日
	TXTPDateType	EndDelivDate;
	///合约生命周期状态
	TXTPInstLifePhaseType	InstLifePhase;
	///当前是否交易
	TXTPBoolType	IsTrading;
	///持仓类型
	TXTPPositionTypeType	PositionType;
	///报单能否撤单
	TXTPBoolType	OrderCanBeWithdraw;
	///最小买下单单位
	TXTPVolumeType	MinBuyVolume;
	///最小卖下单单位
	TXTPVolumeType	MinSellVolume;
	///股票权限模版代码
	TXTPRightModelIDType	RightModelID;
	///持仓交易类型
	TXTPPosTradeTypeType	PosTradeType;
	///市场代码
	TXTPInstrumentIDType	MarketID;
	///期权执行价格
	TXTPPriceType	ExecPrice;
	///期权单手保证金
	TXTPMoneyType	UnitMargin;
	///合约类型
	TXTPInstrumentTypeType	InstrumentType;
	///期权保证金参数1
	TXTPRatioType	OptionsMarginParam1;
	///期权保证金参数2
	TXTPRatioType	OptionsMarginParam2;
};

///经纪公司
struct CXTPBrokerField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///经纪公司简称
	TXTPBrokerAbbrType	BrokerAbbr;
	///经纪公司名称
	TXTPBrokerNameType	BrokerName;
	///是否活跃
	TXTPBoolType	IsActive;
};

///会员编码和经纪公司编码对照表
struct CXTPPartBrokerField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///是否活跃
	TXTPBoolType	IsActive;
};

///投资者
struct CXTPInvestorField
{
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者分组代码
	TXTPInvestorIDType	InvestorGroupID;
	///投资者名称
	TXTPPartyNameType	InvestorName;
	///证件类型
	TXTPIdCardTypeType	IdentifiedCardType;
	///证件号码
	TXTPIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TXTPBoolType	IsActive;
	///上海营业部编号
	TXTPTraderIDType	SHBranchID;
	///深圳营业部编号
	TXTPTraderIDType	SZBranchID;
	///所属结算系统类型
	TXTPSettleSystemTypeType	SettleSystemType;
	///投资者期权交易等级
	TXTPInvestorLevelType	InvestorLevel;
};

///交易编码
struct CXTPTradingCodeField
{
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///客户代码
	TXTPClientIDType	ClientID;
	///是否活跃
	TXTPBoolType	IsActive;
	///AccountID
	TXTPAccountIDType	AccountID;
	///交易单元号
	TXTPTraderIDType	PBU;
	///ClientType
	TXTPClientTypeType	ClientType;
};

///管理用户
struct CXTPSuperUserField
{
	///用户代码
	TXTPUserIDType	UserID;
	///用户名称
	TXTPUserNameType	UserName;
	///密码
	TXTPPasswordType	Password;
	///是否活跃
	TXTPBoolType	IsActive;
};

///管理用户功能权限
struct CXTPSuperUserFunctionField
{
	///用户代码
	TXTPUserIDType	UserID;
	///功能代码
	TXTPFunctionCodeType	FunctionCode;
};

///经纪公司用户
struct CXTPBrokerUserField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///用户名称
	TXTPUserNameType	UserName;
	///用户类型
	TXTPUserTypeType	UserType;
	///是否活跃
	TXTPBoolType	IsActive;
	///是否使用令牌
	TXTPBoolType	IsUsingOTP;
};

///经纪公司用户功能权限
struct CXTPBrokerUserFunctionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///经纪公司功能代码
	TXTPBrokerFunctionCodeType	BrokerFunctionCode;
};

///资金账户
struct CXTPTradingAccountField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者帐号
	TXTPAccountIDType	AccountID;
	///上次质押金额
	TXTPMoneyType	PreMortgage;
	///上次信用额度
	TXTPMoneyType	PreCredit;
	///上次存款额
	TXTPMoneyType	PreDeposit;
	///上次结算准备金
	TXTPMoneyType	PreBalance;
	///上次占用的保证金
	TXTPMoneyType	PreMargin;
	///利息基数
	TXTPMoneyType	InterestBase;
	///利息收入
	TXTPMoneyType	Interest;
	///入金金额
	TXTPMoneyType	Deposit;
	///出金金额
	TXTPMoneyType	Withdraw;
	///冻结的保证金
	TXTPMoneyType	FrozenMargin;
	///冻结的资金
	TXTPMoneyType	FrozenCash;
	///冻结的手续费
	TXTPMoneyType	FrozenCommission;
	///当前保证金总额
	TXTPMoneyType	CurrMargin;
	///资金差额
	TXTPMoneyType	CashIn;
	///手续费
	TXTPMoneyType	Commission;
	///结算准备金
	TXTPMoneyType	Balance;
	///现金
	TXTPMoneyType	Available;
	///可取资金
	TXTPMoneyType	WithdrawQuota;
	///基本准备金
	TXTPMoneyType	Reserve;
	///交易日
	TXTPDateType	TradingDay;
	///保证金可用余额
	TXTPMoneyType	Credit;
	///质押金额
	TXTPMoneyType	Mortgage;
	///交易所保证金
	TXTPMoneyType	ExchangeMargin;
	///投资者交割保证金
	TXTPMoneyType	DeliveryMargin;
	///交易所交割保证金
	TXTPMoneyType	ExchangeDeliveryMargin;
	///冻结的过户费
	TXTPMoneyType	FrozenTransferFee;
	///冻结的印花税
	TXTPMoneyType	FrozenStampTax;
	///过户费
	TXTPMoneyType	TransferFee;
	///印花税
	TXTPMoneyType	StampTax;
	///折算金额
	TXTPMoneyType	ConversionAmount;
	///授信额度
	TXTPMoneyType	CreditAmount;
	///证券总价值
	TXTPMoneyType	StockValue;
	///国债回购占用资金
	TXTPMoneyType	BondRepurchaseAmount;
	///国债逆回购占用资金
	TXTPMoneyType	ReverseRepurchaseAmount;
	///币种
	TXTPCurrencyCodeType	CurrencyCode;
	///账户类型
	TXTPAccountTypeType	AccountType;
	///融资买入金额
	TXTPMoneyType	MarginTradeAmount;
	///融券卖出金额
	TXTPMoneyType	ShortSellAmount;
	///融资持仓盈亏
	TXTPMoneyType	MarginTradeProfit;
	///融券持仓盈亏
	TXTPMoneyType	ShortSellProfit;
	///融券总市值
	TXTPMoneyType	SSStockValue;
	///维持担保比例
	TXTPRatioType	CreditRatio;
	///行权冻结资金
	TXTPMoneyType	FrozenExecCash;
	///期权买入资金(SSE)
	TXTPMoneyType	SSEOptionsBuyAmount;
	///期权买入冻结资金(SSE)
	TXTPMoneyType	SSEOptionsBuyFrozenAmount;
	///结算保证金总额
	TXTPMoneyType	SettleMargin;
};

///禁止登录用户
struct CXTPLoginForbiddenUserField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///投资者合约交易权限
struct CXTPInstrumentTradingRightField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///投资者范围
	TXTPInvestorRangeType	InvestorRange;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///买卖
	TXTPDirectionType	Direction;
	///交易权限
	TXTPTradingRightType	TradingRight;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///股票权限分类
	TXTPInstrumentRangeType	InstrumentRange;
};

///投资者持仓明细
struct CXTPInvestorPositionDetailField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///投机套保标志
	TXTPHedgeFlagType	HedgeFlag;
	///买卖
	TXTPDirectionType	Direction;
	///开仓日期
	TXTPDateType	OpenDate;
	///成交编号
	TXTPTradeIDType	TradeID;
	///数量
	TXTPVolumeType	Volume;
	///开仓价
	TXTPPriceType	OpenPrice;
	///交易日
	TXTPDateType	TradingDay;
	///成交类型
	TXTPTradeTypeType	TradeType;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///投资者保证金
	TXTPMoneyType	Margin;
	///交易所保证金
	TXTPMoneyType	ExchMargin;
	///昨结算价
	TXTPPriceType	LastSettlementPrice;
	///结算价
	TXTPPriceType	SettlementPrice;
	///平仓量
	TXTPVolumeType	CloseVolume;
	///平仓金额
	TXTPMoneyType	CloseAmount;
	///过户费
	TXTPMoneyType	TransferFee;
	///印花税
	TXTPMoneyType	StampTax;
	///手续费
	TXTPMoneyType	Commission;
	///AccountID
	TXTPAccountIDType	AccountID;
	///质押入库数量
	TXTPVolumeType	PledgeInPosition;
	///质押入库冻结数量
	TXTPVolumeType	PledgeInFrozenPosition;
	///正回购使用的标准券数量
	TXTPVolumeType	RepurchasePosition;
	///融资融券金额
	TXTPMoneyType	Amount;
	///标的合约代码
	TXTPInstrumentIDType	UnderlyingInstrumentID;
};

///债券利息
struct CXTPBondInterestField
{
	///交易日
	TXTPDateType	TradingDay;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///利息
	TXTPInterestType	Interest;
};

///市值配售信息
struct CXTPMarketRationInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///可配售手数
	TXTPVolumeType	RationVolume;
};

///合约手续费率
struct CXTPInstrumentCommissionRateField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///投资者范围
	TXTPInvestorRangeType	InvestorRange;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///买卖方向
	TXTPDirectionType	Direction;
	///印花税率
	TXTPRatioType	StampTaxRateByMoney;
	///印花税率(按手数)
	TXTPRatioType	StampTaxRateByVolume;
	///过户费率
	TXTPRatioType	TransferFeeRateByMoney;
	///过户费率(按手数)
	TXTPRatioType	TransferFeeRateByVolume;
	///交易费
	TXTPRatioType	TradeFeeByMoney;
	///交易费(按手数)
	TXTPRatioType	TradeFeeByVolume;
	///交易附加费率
	TXTPRatioType	MarginByMoney;
	///最小交易费
	TXTPPriceType	MinTradeFee;
};

///余券信息
struct CXTPExcessStockInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///余券数量
	TXTPVolumeType	ExcessVolume;
	///余券冻结数量
	TXTPVolumeType	ExcessFrozenVolume;
};

///ETF合约
struct CXTPETFInstrumentField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///ETF证券代码
	TXTPInstrumentIDType	ETFInstrumentID;
	///ETF对应申赎代码
	TXTPInstrumentIDType	ETFPurRedInstrumentID;
	///最小申购赎回单位对应的ETF份数
	TXTPVolumeType	CreationRedemptionUnit;
	///最大现金替代比例
	TXTPRatioType	Maxcashratio;
	///基金当天申购赎回状态
	TXTPCreationredemptionStatusType	Creationredemption;
	///预估金额
	TXTPMoneyType	EstimateCashComponent;
};

///ETF股票篮
struct CXTPETFBasketField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///ETF证券代码
	TXTPInstrumentIDType	ETFInstrumentID;
	///股票证券代码
	TXTPInstrumentIDType	StockInstrumentID;
	///股票证券名称
	TXTPInstrumentNameType	StockInstrumentName;
	///股票数量
	TXTPVolumeType	Volume;
	///替代标志
	TXTPETFCurrenceReplaceStatusType	CurrenceReplaceStatus;
	///溢价比例
	TXTPRatioType	Premium;
	///总金额
	TXTPMoneyType	Amount;
};

///OF合约
struct CXTPOFInstrumentField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///OF基金代码
	TXTPInstrumentIDType	InstrumentID;
	///基金当天申购赎回状态
	TXTPCreationredemptionStatusType	Creationredemption;
	///基金净值
	TXTPPriceType	NetPrice;
};

///SF合约
struct CXTPSFInstrumentField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///基金代码
	TXTPInstrumentIDType	InstrumentID;
	///SF基金代码
	TXTPInstrumentIDType	SFInstrumentID;
	///基金当天拆分合并状态
	TXTPSplitMergeStatusType	SplitMergeStatus;
	///最小拆分数量
	TXTPVolumeType	MinSplitVolume;
	///最小合并数量
	TXTPVolumeType	MinMergeVolume;
	///拆分/合并比例
	TXTPVolumeType	VolumeRatio;
	///基金净值
	TXTPPriceType	NetPrice;
};

///合约单手保证金
struct CXTPInstrumentUnitMarginField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///合约单手保证金
	TXTPMoneyType	UnitMargin;
};

///期权资金限制参数
struct CXTPOptionsFundLimitParamField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///最大可买金额
	TXTPMoneyType	MaxBuyAmount;
};

///投资者期权持仓
struct CXTPInvestorOptionsPositionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者范围
	TXTPInvestorRangeType	InvestorRange;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///InstrumentID
	TXTPInstrumentIDType	InstrumentID;
	///最大多头仓位限制
	TXTPVolumeType	MaxLongPositionLimit;
	///最大买开量限制
	TXTPVolumeType	MaxBuyVolLimit;
	///最大总仓位限制
	TXTPVolumeType	MaxPositionLimit;
	///多头持仓
	TXTPVolumeType	LongPosition;
	///空头持仓
	TXTPVolumeType	ShortPosition;
	///买开量
	TXTPVolumeType	BuyVolume;
	///买开冻结量
	TXTPVolumeType	BuyFrozenVolume;
	///多头冻结持仓
	TXTPVolumeType	LongFrozenPosition;
	///空头冻结持仓
	TXTPVolumeType	ShortFrozenPosition;
};

///预交割信息
struct CXTPPreDelivInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交割类型
	TXTPDelivTypeType	DelivType;
	///标的合约代码
	TXTPInstrumentIDType	UnderlyingInstrumentID;
	///交割数量
	TXTPVolumeType	DelivVolume;
	///交割金额
	TXTPMoneyType	DelivAmount;
	///期权执行数量
	TXTPVolumeType	ExecVolume;
	///买卖方向
	TXTPDirectionType	Direction;
};

///可融券分配信息
struct CXTPCreditStockAssignInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///融券限量
	TXTPVolumeType	LimitVolume;
	///上日融券数量
	TXTPVolumeType	YDVolume;
	///剩余可融券数量
	TXTPVolumeType	LeftVolume;
	///冻结融券数量
	TXTPVolumeType	FrozenVolume;
};

///可融资分配信息
struct CXTPCreditCashAssignInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///融资限额
	TXTPMoneyType	LimitAmount;
	///上日融资金额
	TXTPMoneyType	YDAmount;
};

///证券折算率
struct CXTPConversionRateField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///折算比率
	TXTPRatioType	ConversionRate;
	///当前是否支持融资交易
	TXTPBoolType	IsTradingForMargin;
	///当前是否支持融券交易
	TXTPBoolType	IsTradingForShort;
};

///历史信用负债信息
struct CXTPHisCreditDebtInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///开仓日期
	TXTPDateType	OpenDate;
	///负债类型
	TXTPDirectionType	Direction;
	///开仓价
	TXTPPriceType	OpenPrice;
	///数量
	TXTPVolumeType	Volume;
	///融资融券金额
	TXTPMoneyType	Amount;
};

///交易所交易员报盘机
struct CXTPTraderOfferField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///密码
	TXTPPasswordType	Password;
	///安装编号
	TXTPInstallIDType	InstallID;
	///本地报单编号
	TXTPOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TXTPTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TXTPDateType	ConnectRequestDate;
	///发出连接请求的时间
	TXTPTimeType	ConnectRequestTime;
	///上次报告日期
	TXTPDateType	LastReportDate;
	///上次报告时间
	TXTPTimeType	LastReportTime;
	///完成连接日期
	TXTPDateType	ConnectDate;
	///完成连接时间
	TXTPTimeType	ConnectTime;
	///启动日期
	TXTPDateType	StartDate;
	///启动时间
	TXTPTimeType	StartTime;
	///交易日
	TXTPDateType	TradingDay;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
};

///交易所行情报盘机
struct CXTPMDTraderOfferField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///密码
	TXTPPasswordType	Password;
	///安装编号
	TXTPInstallIDType	InstallID;
	///本地报单编号
	TXTPOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TXTPTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TXTPDateType	ConnectRequestDate;
	///发出连接请求的时间
	TXTPTimeType	ConnectRequestTime;
	///上次报告日期
	TXTPDateType	LastReportDate;
	///上次报告时间
	TXTPTimeType	LastReportTime;
	///完成连接日期
	TXTPDateType	ConnectDate;
	///完成连接时间
	TXTPTimeType	ConnectTime;
	///启动日期
	TXTPDateType	StartDate;
	///启动时间
	TXTPTimeType	StartTime;
	///交易日
	TXTPDateType	TradingDay;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
};

///前置状态
struct CXTPFrontStatusField
{
	///前置编号
	TXTPFrontIDType	FrontID;
	///上次报告日期
	TXTPDateType	LastReportDate;
	///上次报告时间
	TXTPTimeType	LastReportTime;
	///是否活跃
	TXTPBoolType	IsActive;
};

///用户会话
struct CXTPUserSessionField
{
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///登录日期
	TXTPDateType	LoginDate;
	///登录时间
	TXTPTimeType	LoginTime;
	///IP地址
	TXTPIPAddressType	IPAddress;
	///用户端产品信息
	TXTPProductInfoType	UserProductInfo;
	///接口端产品信息
	TXTPProductInfoType	InterfaceProductInfo;
	///协议信息
	TXTPProtocolInfoType	ProtocolInfo;
	///Mac地址
	TXTPMacAddressType	MacAddress;
};

///报单
struct CXTPOrderField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///报单引用
	TXTPOrderRefType	OrderRef;
	///用户代码
	TXTPUserIDType	UserID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///报单价格条件
	TXTPOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TXTPDirectionType	Direction;
	///组合开平标志
	TXTPCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TXTPCombHedgeFlagType	CombHedgeFlag;
	///价格
	TXTPStockPriceType	LimitPrice;
	///数量
	TXTPVolumeType	VolumeTotalOriginal;
	///有效期类型
	TXTPTimeConditionType	TimeCondition;
	///GTD日期
	TXTPDateType	GTDDate;
	///成交量类型
	TXTPVolumeConditionType	VolumeCondition;
	///最小成交量
	TXTPVolumeType	MinVolume;
	///触发条件
	TXTPContingentConditionType	ContingentCondition;
	///止损价
	TXTPPriceType	StopPrice;
	///强平原因
	TXTPForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TXTPBoolType	IsAutoSuspend;
	///业务单元
	TXTPBusinessUnitType	BusinessUnit;
	///请求编号
	TXTPRequestIDType	RequestID;
	///本地报单编号
	TXTPOrderLocalIDType	OrderLocalID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///客户代码
	TXTPClientIDType	ClientID;
	///合约在交易所的代码
	TXTPExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
	///安装编号
	TXTPInstallIDType	InstallID;
	///报单提交状态
	TXTPOrderSubmitStatusType	OrderSubmitStatus;
	///账户代码
	TXTPAccountIDType	AccountID;
	///报单提示序号
	TXTPSequenceNoType	NotifySequence;
	///交易日
	TXTPDateType	TradingDay;
	///报单编号
	TXTPOrderSysIDType	OrderSysID;
	///报单来源
	TXTPOrderSourceType	OrderSource;
	///报单状态
	TXTPOrderStatusType	OrderStatus;
	///报单类型
	TXTPOrderTypeType	OrderType;
	///今成交数量
	TXTPVolumeType	VolumeTraded;
	///剩余数量
	TXTPVolumeType	VolumeTotal;
	///报单日期
	TXTPDateType	InsertDate;
	///委托时间
	TXTPTimeType	InsertTime;
	///激活时间
	TXTPTimeType	ActiveTime;
	///挂起时间
	TXTPTimeType	SuspendTime;
	///最后修改时间
	TXTPTimeType	UpdateTime;
	///撤销时间
	TXTPTimeType	CancelTime;
	///最后修改交易所交易员代码
	TXTPTraderIDType	ActiveTraderID;
	///结算会员编号
	TXTPParticipantIDType	ClearingPartID;
	///序号
	TXTPSequenceNoType	SequenceNo;
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///用户端产品信息
	TXTPProductInfoType	UserProductInfo;
	///状态信息
	TXTPErrorMsgType	StatusMsg;
	///用户强平标志
	TXTPBoolType	UserForceClose;
	///操作用户代码
	TXTPUserIDType	ActiveUserID;
	///经纪公司报单编号
	TXTPSequenceNoType	BrokerOrderSeq;
	///相关报单
	TXTPOrderSysIDType	RelativeOrderSysID;
	///营业部编号
	TXTPBranchIDType	BranchID;
	///成交数量
	TXTPMoneyType	TradeAmount;
	///是否ETF
	TXTPBoolType	IsETF;
	///合约类型
	TXTPInstrumentTypeType	InstrumentType;
};

///报单操作
struct CXTPOrderActionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///报单操作引用
	TXTPOrderActionRefType	OrderActionRef;
	///报单引用
	TXTPOrderRefType	OrderRef;
	///请求编号
	TXTPRequestIDType	RequestID;
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///操作标志
	TXTPActionFlagType	ActionFlag;
	///价格
	TXTPPriceType	LimitPrice;
	///数量变化
	TXTPVolumeType	VolumeChange;
	///操作日期
	TXTPDateType	ActionDate;
	///操作时间
	TXTPTimeType	ActionTime;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
	///安装编号
	TXTPInstallIDType	InstallID;
	///本地报单编号
	TXTPOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TXTPOrderLocalIDType	ActionLocalID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///客户代码
	TXTPClientIDType	ClientID;
	///业务单元
	TXTPBusinessUnitType	BusinessUnit;
	///报单操作状态
	TXTPOrderActionStatusType	OrderActionStatus;
	///用户代码
	TXTPUserIDType	UserID;
	///营业部编号
	TXTPBranchIDType	BranchID;
	///状态信息
	TXTPErrorMsgType	StatusMsg;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///合约类型
	TXTPInstrumentTypeType	InstrumentType;
};

///错误报单
struct CXTPErrOrderField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///报单引用
	TXTPOrderRefType	OrderRef;
	///用户代码
	TXTPUserIDType	UserID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///报单价格条件
	TXTPOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TXTPDirectionType	Direction;
	///组合开平标志
	TXTPCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TXTPCombHedgeFlagType	CombHedgeFlag;
	///价格
	TXTPStockPriceType	LimitPrice;
	///数量
	TXTPVolumeType	VolumeTotalOriginal;
	///有效期类型
	TXTPTimeConditionType	TimeCondition;
	///GTD日期
	TXTPDateType	GTDDate;
	///成交量类型
	TXTPVolumeConditionType	VolumeCondition;
	///最小成交量
	TXTPVolumeType	MinVolume;
	///触发条件
	TXTPContingentConditionType	ContingentCondition;
	///止损价
	TXTPPriceType	StopPrice;
	///强平原因
	TXTPForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TXTPBoolType	IsAutoSuspend;
	///业务单元
	TXTPBusinessUnitType	BusinessUnit;
	///请求编号
	TXTPRequestIDType	RequestID;
	///用户强平标志
	TXTPBoolType	UserForceClose;
	///错误代码
	TXTPErrorIDType	ErrorID;
	///错误信息
	TXTPErrorMsgType	ErrorMsg;
};

///错误报单操作
struct CXTPErrOrderActionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///报单操作引用
	TXTPOrderActionRefType	OrderActionRef;
	///报单引用
	TXTPOrderRefType	OrderRef;
	///请求编号
	TXTPRequestIDType	RequestID;
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///操作标志
	TXTPActionFlagType	ActionFlag;
	///价格
	TXTPPriceType	LimitPrice;
	///数量变化
	TXTPVolumeType	VolumeChange;
	///操作日期
	TXTPDateType	ActionDate;
	///操作时间
	TXTPTimeType	ActionTime;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
	///安装编号
	TXTPInstallIDType	InstallID;
	///本地报单编号
	TXTPOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TXTPOrderLocalIDType	ActionLocalID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///客户代码
	TXTPClientIDType	ClientID;
	///业务单元
	TXTPBusinessUnitType	BusinessUnit;
	///报单操作状态
	TXTPOrderActionStatusType	OrderActionStatus;
	///用户代码
	TXTPUserIDType	UserID;
	///营业部编号
	TXTPBranchIDType	BranchID;
	///状态信息
	TXTPErrorMsgType	StatusMsg;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///错误代码
	TXTPErrorIDType	ErrorID;
	///错误信息
	TXTPErrorMsgType	ErrorMsg;
	///合约类型
	TXTPInstrumentTypeType	InstrumentType;
};

///成交
struct CXTPTradeField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///报单引用
	TXTPOrderRefType	OrderRef;
	///用户代码
	TXTPUserIDType	UserID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///成交编号
	TXTPTradeIDType	TradeID;
	///买卖方向
	TXTPDirectionType	Direction;
	///报单编号
	TXTPOrderSysIDType	OrderSysID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///客户代码
	TXTPClientIDType	ClientID;
	///交易角色
	TXTPTradingRoleType	TradingRole;
	///合约在交易所的代码
	TXTPExchangeInstIDType	ExchangeInstID;
	///开平标志
	TXTPOffsetFlagType	OffsetFlag;
	///投机套保标志
	TXTPHedgeFlagType	HedgeFlag;
	///价格
	TXTPStockPriceType	Price;
	///数量
	TXTPVolumeType	Volume;
	///成交时期
	TXTPDateType	TradeDate;
	///成交时间
	TXTPTimeType	TradeTime;
	///成交类型
	TXTPTradeTypeType	TradeType;
	///成交价来源
	TXTPPriceSourceType	PriceSource;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
	///本地报单编号
	TXTPOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TXTPParticipantIDType	ClearingPartID;
	///业务单元
	TXTPBusinessUnitType	BusinessUnit;
	///序号
	TXTPSequenceNoType	SequenceNo;
	///成交来源
	TXTPTradeSourceType	TradeSource;
	///交易日
	TXTPDateType	TradingDay;
	///经纪公司报单编号
	TXTPSequenceNoType	BrokerOrderSeq;
	///成交金额
	TXTPMoneyType	TradeAmount;
	///成交序号
	TXTPTradeIndexType	TradeIndex;
};

///投资者持仓
struct CXTPInvestorPositionField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///持仓多空方向
	TXTPPosiDirectionType	PosiDirection;
	///投机套保标志
	TXTPHedgeFlagType	HedgeFlag;
	///持仓日期
	TXTPPositionDateType	PositionDate;
	///上日持仓
	TXTPVolumeType	YdPosition;
	///总持仓
	TXTPVolumeType	Position;
	///多头冻结
	TXTPVolumeType	LongFrozen;
	///空头冻结
	TXTPVolumeType	ShortFrozen;
	///开仓冻结金额
	TXTPMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TXTPMoneyType	ShortFrozenAmount;
	///开仓量
	TXTPVolumeType	OpenVolume;
	///平仓量
	TXTPVolumeType	CloseVolume;
	///开仓金额
	TXTPMoneyType	OpenAmount;
	///平仓金额
	TXTPMoneyType	CloseAmount;
	///持仓成本
	TXTPMoneyType	PositionCost;
	///冻结的资金
	TXTPMoneyType	FrozenCash;
	///资金差额
	TXTPMoneyType	CashIn;
	///手续费
	TXTPMoneyType	Commission;
	///上次结算价
	TXTPPriceType	PreSettlementPrice;
	///本次结算价
	TXTPPriceType	SettlementPrice;
	///交易日
	TXTPDateType	TradingDay;
	///开仓成本
	TXTPMoneyType	OpenCost;
	///交易所保证金
	TXTPMoneyType	ExchangeMargin;
	///今日持仓
	TXTPVolumeType	TodayPosition;
	///过户费
	TXTPMoneyType	TransferFee;
	///印花税
	TXTPMoneyType	StampTax;
	///今日申购赎回数量
	TXTPVolumeType	TodayPurRedVolume;
	///折算率
	TXTPRatioType	ConversionRate;
	///折算金额
	TXTPMoneyType	ConversionAmount;
	///证券价值
	TXTPMoneyType	StockValue;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///AccountID
	TXTPAccountIDType	AccountID;
	///质押入库数量
	TXTPVolumeType	PledgeInPosition;
	///正回购使用的标准券数量
	TXTPVolumeType	RepurchasePosition;
	///ETF申赎空头冻结
	TXTPVolumeType	PurRedShortFrozen;
	///融资买入数量
	TXTPVolumeType	MarginTradeVolume;
	///融资买入金额
	TXTPMoneyType	MarginTradeAmount;
	///融资买入冻结数量
	TXTPVolumeType	MarginTradeFrozenVolume;
	///融资买入冻结金额
	TXTPMoneyType	MarginTradeFrozenAmount;
	///融资买入盈亏
	TXTPMoneyType	MarginTradeConversionProfit;
	///融券卖出数量
	TXTPVolumeType	ShortSellVolume;
	///融券卖出金额
	TXTPMoneyType	ShortSellAmount;
	///融券卖出冻结数量
	TXTPVolumeType	ShortSellFrozenVolume;
	///融券卖出冻结金额
	TXTPMoneyType	ShortSellFrozenAmount;
	///融券卖出盈亏
	TXTPMoneyType	ShortSellConversionProfit;
	///融券总市值
	TXTPMoneyType	SSStockValue;
	///今日融资持仓
	TXTPVolumeType	TodayMTPosition;
	///今日融券持仓
	TXTPVolumeType	TodaySSPosition;
	///历史持仓开仓成本
	TXTPMoneyType	YdOpenCost;
	///锁定仓位
	TXTPVolumeType	LockPosition;
	///备兑仓位
	TXTPVolumeType	CoverPosition;
	///锁定冻结仓位
	TXTPVolumeType	LockFrozenPosition;
	///解锁冻结仓位
	TXTPVolumeType	UnlockFrozenPosition;
	///备兑冻结仓位
	TXTPVolumeType	CoverFrozenPosition;
	///行权冻结仓位
	TXTPVolumeType	ExecFrozenPosition;
	///上日备兑仓位
	TXTPVolumeType	YDCoverPosition;
};

///出入金同步
struct CXTPSyncDepositField
{
	///出入金流水号
	TXTPDepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///入金金额
	TXTPMoneyType	Deposit;
	///是否强制进行
	TXTPBoolType	IsForce;
	///账户代
	TXTPAccountIDType	AccountID;
};

///查询交易所
struct CXTPQryExchangeField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
};

///查询产品
struct CXTPQryProductField
{
	///产品代码
	TXTPInstrumentIDType	ProductID;
};

///查询合约
struct CXTPQryInstrumentField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TXTPExchangeInstIDType	ExchangeInstID;
	///产品代码
	TXTPInstrumentIDType	ProductID;
};

///查询经纪公司
struct CXTPQryBrokerField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
};

///查询经纪公司会员代码
struct CXTPQryPartBrokerField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
};

///查询投资者
struct CXTPQryInvestorField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
};

///查询交易编码
struct CXTPQryTradingCodeField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///客户代码
	TXTPClientIDType	ClientID;
};

///查询管理用户
struct CXTPQrySuperUserField
{
	///用户代码
	TXTPUserIDType	UserID;
};

///查询管理用户功能权限
struct CXTPQrySuperUserFunctionField
{
	///用户代码
	TXTPUserIDType	UserID;
};

///查询经纪公司用户
struct CXTPQryBrokerUserField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///查询经纪公司用户权限
struct CXTPQryBrokerUserFunctionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///查询资金账户
struct CXTPQryTradingAccountField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
};

///查询禁止登录用户
struct CXTPQryLoginForbiddenUserField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///查询行情
struct CXTPQryDepthMarketDataField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询合约交易权限
struct CXTPQryInstrumentTradingRightField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询投资者持仓明细
struct CXTPQryInvestorPositionDetailField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询债券利息
struct CXTPQryBondInterestField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询市值配售信息
struct CXTPQryMarketRationInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者帐号
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
};

///查询合约手续费率
struct CXTPQryInstrumentCommissionRateField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///买卖方向
	TXTPDirectionType	Direction;
	///开平标志
	TXTPOffsetFlagType	OffsetFlag;
};

///查询余券信息
struct CXTPQryExcessStockInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询投资者帐户关系
struct CXTPQryInvestorAccountField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
};

///查询ETF合约
struct CXTPQryETFInstrumentField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///ETF证券代码
	TXTPInstrumentIDType	ETFInstrumentID;
};

///查询ETF股票篮
struct CXTPQryETFBasketField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///ETF证券代码
	TXTPInstrumentIDType	ETFInstrumentID;
};

///查询OF合约
struct CXTPQryOFInstrumentField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///ETF证券代码
	TXTPInstrumentIDType	OFInstrumentID;
};

///查询SF合约
struct CXTPQrySFInstrumentField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///ETF证券代码
	TXTPInstrumentIDType	SFInstrumentID;
};

///查询合约单手保证金
struct CXTPQryInstrumentUnitMarginField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询期权资金限制参数
struct CXTPQryOptionsFundLimitParamField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
};

///查询投资者期权持仓
struct CXTPQryInvestorOptionsPositionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///标的合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询预交割信息
struct CXTPQryPreDelivInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询可融券分配信息
struct CXTPQryCreditStockAssignInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询可融资分配信息
struct CXTPQryCreditCashAssignInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
};

///查询证券折算率
struct CXTPQryConversionRateField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询历史信用负债信息
struct CXTPQryHisCreditDebtInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询交易员报盘机
struct CXTPQryTraderOfferField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
};

///查询行情报盘机
struct CXTPQryMDTraderOfferField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///会员代码
	TXTPParticipantIDType	ParticipantID;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
};

///查询前置状态
struct CXTPQryFrontStatusField
{
	///前置编号
	TXTPFrontIDType	FrontID;
};

///查询用户会话
struct CXTPQryUserSessionField
{
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///查询报单
struct CXTPQryOrderField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///报单编号
	TXTPOrderSysIDType	OrderSysID;
	///开始时间
	TXTPTimeType	InsertTimeStart;
	///结束时间
	TXTPTimeType	InsertTimeEnd;
};

///查询报单操作
struct CXTPQryOrderActionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
};

///查询错误报单
struct CXTPQryErrOrderField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
};

///查询错误报单操作
struct CXTPQryErrOrderActionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
};

///查询成交
struct CXTPQryTradeField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///成交编号
	TXTPTradeIDType	TradeID;
	///开始时间
	TXTPTimeType	TradeTimeStart;
	///结束时间
	TXTPTimeType	TradeTimeEnd;
};

///查询投资者持仓
struct CXTPQryInvestorPositionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
};

///查询出入金流水
struct CXTPQrySyncDepositField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///出入金流水号
	TXTPDepositSeqNoType	DepositSeqNo;
};

///用户口令变更
struct CXTPUserPasswordUpdateField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///原来的口令
	TXTPPasswordType	OldPassword;
	///新的口令
	TXTPPasswordType	NewPassword;
};

///资金账户口令变更域
struct CXTPTradingAccountPasswordUpdateField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者帐号
	TXTPAccountIDType	AccountID;
	///原来的口令
	TXTPPasswordType	OldPassword;
	///新的口令
	TXTPPasswordType	NewPassword;
};

///手工同步用户动态令牌
struct CXTPManualSyncBrokerUserOTPField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///动态令牌类型
	TXTPOTPTypeType	OTPType;
	///第一个动态密码
	TXTPPasswordType	FirstOTP;
	///第二个动态密码
	TXTPPasswordType	SecondOTP;
};

///经纪公司用户口令
struct CXTPBrokerUserPasswordField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///密码
	TXTPPasswordType	Password;
};

///资金账户口令域
struct CXTPTradingAccountPasswordField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者帐号
	TXTPAccountIDType	AccountID;
	///密码
	TXTPPasswordType	Password;
};

///用户权限
struct CXTPUserRightField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///客户权限类型
	TXTPUserRightTypeType	UserRightType;
	///是否禁止
	TXTPBoolType	IsForbidden;
};

///投资者账户
struct CXTPInvestorAccountField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///投资者帐号
	TXTPAccountIDType	AccountID;
	///是否主账户
	TXTPBoolType	IsDefault;
	///账户类型
	TXTPAccountTypeType	AccountType;
	///是否活跃
	TXTPBoolType	IsActive;
	///上交所交易单元号
	TXTPTraderIDType	SHBranchPBU;
	///深交所交易单元号
	TXTPTraderIDType	SZBranchPBU;
};

///用户IP
struct CXTPUserIPField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///IP地址
	TXTPIPAddressType	IPAddress;
	///IP地址掩码
	TXTPIPAddressType	IPMask;
	///Mac地址
	TXTPMacAddressType	MacAddress;
};

///用户动态令牌参数
struct CXTPBrokerUserOTPParamField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///动态令牌提供商
	TXTPOTPVendorsIDType	OTPVendorsID;
	///动态令牌序列号
	TXTPSerialNumberType	SerialNumber;
	///令牌密钥
	TXTPAuthKeyType	AuthKey;
	///漂移值
	TXTPLastDriftType	LastDrift;
	///成功值
	TXTPLastSuccessType	LastSuccess;
	///动态令牌类型
	TXTPOTPTypeType	OTPType;
};

///用户登录请求
struct CXTPReqUserLoginField
{
	///交易日
	TXTPDateType	TradingDay;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///密码
	TXTPPasswordType	Password;
	///用户端产品信息
	TXTPProductInfoType	UserProductInfo;
	///接口端产品信息
	TXTPProductInfoType	InterfaceProductInfo;
	///协议信息
	TXTPProtocolInfoType	ProtocolInfo;
	///Mac地址
	TXTPMacAddressType	MacAddress;
	///动态密码
	TXTPPasswordType	OneTimePassword;
	///终端IP地址
	TXTPIPAddressType	ClientIPAddress;
	///客户端认证码
	TXTPAuthCodeType	AuthCode;
};

///用户登录应答
struct CXTPRspUserLoginField
{
	///交易日
	TXTPDateType	TradingDay;
	///登录成功时间
	TXTPTimeType	LoginTime;
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///交易系统名称
	TXTPSystemNameType	SystemName;
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///最大报单引用
	TXTPOrderRefType	MaxOrderRef;
};

///用户登出请求
struct CXTPUserLogoutField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///全部登出信息
struct CXTPLogoutAllField
{
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///系统名称
	TXTPSystemNameType	SystemName;
};

///强制交易员退出
struct CXTPForceUserLogoutField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///经纪公司用户激活
struct CXTPActivateBrokerUserField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
};

///输入报单
struct CXTPInputOrderField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///报单引用
	TXTPOrderRefType	OrderRef;
	///用户代码
	TXTPUserIDType	UserID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///报单价格条件
	TXTPOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TXTPDirectionType	Direction;
	///组合开平标志
	TXTPCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TXTPCombHedgeFlagType	CombHedgeFlag;
	///价格
	TXTPStockPriceType	LimitPrice;
	///数量
	TXTPVolumeType	VolumeTotalOriginal;
	///有效期类型
	TXTPTimeConditionType	TimeCondition;
	///GTD日期
	TXTPDateType	GTDDate;
	///成交量类型
	TXTPVolumeConditionType	VolumeCondition;
	///最小成交量
	TXTPVolumeType	MinVolume;
	///触发条件
	TXTPContingentConditionType	ContingentCondition;
	///止损价
	TXTPPriceType	StopPrice;
	///强平原因
	TXTPForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TXTPBoolType	IsAutoSuspend;
	///业务单元
	TXTPBusinessUnitType	BusinessUnit;
	///请求编号
	TXTPRequestIDType	RequestID;
	///用户强平标志
	TXTPBoolType	UserForceClose;
};

///输入报单操作
struct CXTPInputOrderActionField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///报单操作引用
	TXTPOrderActionRefType	OrderActionRef;
	///报单引用
	TXTPOrderRefType	OrderRef;
	///请求编号
	TXTPRequestIDType	RequestID;
	///前置编号
	TXTPFrontIDType	FrontID;
	///会话编号
	TXTPSessionIDType	SessionID;
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
	///操作标志
	TXTPActionFlagType	ActionFlag;
	///价格
	TXTPPriceType	LimitPrice;
	///数量变化
	TXTPVolumeType	VolumeChange;
	///用户代码
	TXTPUserIDType	UserID;
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///交易所交易员代码
	TXTPTraderIDType	BranchPBU;
	///本地报单编号
	TXTPOrderLocalIDType	OrderLocalID;
};

///指定的合约
// struct CXTPSpecificInstrumentField
// {
// 	///合约代码
// 	TXTPInstrumentIDType	InstrumentID;
// 	///交易所代码
// 	TXTPExchangeIDType	ExchangeID;
// };

///指定的交易所
struct CXTPSpecificExchangeField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
};

///行情基础属性
struct CXTPMarketDataBaseField
{
	///交易日
	TXTPDateType	TradingDay;
	///上次结算价
	TXTPPriceType	PreSettlementPrice;
	///昨收盘
	TXTPPriceType	PreClosePrice;
	///昨持仓量
	TXTPLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TXTPRatioType	PreDelta;
};

///行情静态属性
struct CXTPMarketDataStaticField
{
	///今开盘
	TXTPPriceType	OpenPrice;
	///最高价
	TXTPPriceType	HighestPrice;
	///最低价
	TXTPPriceType	LowestPrice;
	///今收盘
	TXTPPriceType	ClosePrice;
	///涨停板价
	TXTPPriceType	UpperLimitPrice;
	///跌停板价
	TXTPPriceType	LowerLimitPrice;
	///本次结算价
	TXTPPriceType	SettlementPrice;
	///今虚实度
	TXTPRatioType	CurrDelta;
};

///行情最新成交属性
struct CXTPMarketDataLastMatchField
{
	///最新价
	TXTPPriceType	LastPrice;
	///数量
	TXTPVolumeType	Volume;
	///成交金额
	TXTPMoneyType	Turnover;
	///持仓量
	TXTPLargeVolumeType	OpenInterest;
	///数量(新)
	TXTPLargeVolumeType	Volume_New;
};

///行情最优价属性
struct CXTPMarketDataBestPriceField
{
	///申买价一
	TXTPPriceType	BidPrice1;
	///申买量一
	TXTPVolumeType	BidVolume1;
	///申卖价一
	TXTPPriceType	AskPrice1;
	///申卖量一
	TXTPVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CXTPMarketDataBid23Field
{
	///申买价二
	TXTPPriceType	BidPrice2;
	///申买量二
	TXTPVolumeType	BidVolume2;
	///申买价三
	TXTPPriceType	BidPrice3;
	///申买量三
	TXTPVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CXTPMarketDataAsk23Field
{
	///申卖价二
	TXTPPriceType	AskPrice2;
	///申卖量二
	TXTPVolumeType	AskVolume2;
	///申卖价三
	TXTPPriceType	AskPrice3;
	///申卖量三
	TXTPVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CXTPMarketDataBid45Field
{
	///申买价四
	TXTPPriceType	BidPrice4;
	///申买量四
	TXTPVolumeType	BidVolume4;
	///申买价五
	TXTPPriceType	BidPrice5;
	///申买量五
	TXTPVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CXTPMarketDataAsk45Field
{
	///申卖价四
	TXTPPriceType	AskPrice4;
	///申卖量四
	TXTPVolumeType	AskVolume4;
	///申卖价五
	TXTPPriceType	AskPrice5;
	///申卖量五
	TXTPVolumeType	AskVolume5;
};

///行情更新时间属性
struct CXTPMarketDataUpdateTimeField
{
	///合约代码
	TXTPInstrumentIDType	InstrumentID;
	///最后修改时间
	TXTPTimeType	UpdateTime;
	///最后修改毫秒
	TXTPMillisecType	UpdateMillisec;
	///业务日期
	TXTPDateType	ActionDay;
};

///成交均价
struct CXTPMarketDataAveragePriceField
{
	///当日均价
	TXTPPriceType	AveragePrice;
};

///行情交易所代码属性
struct CXTPMarketDataExchangeField
{
	///交易所代码
	TXTPExchangeIDType	ExchangeID;
};

///信息分发
struct CXTPDisseminationField
{
	///序列系列号
	TXTPSequenceSeriesType	SequenceSeries;
	///序列号
	TXTPSequenceNoType	SequenceNo;
};

///资金转账输入
struct CXTPInputFundTransferField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///投资者资金帐号
	TXTPAccountIDType	AccountID;
	///资金帐户密码
	TXTPPasswordType	Password;
	///用户代码
	TXTPUserIDType	UserID;
	///交易金额
	TXTPTradeAmountType	TradeAmount;
	///摘要
	TXTPDigestType	Digest;
	///账户类型
	TXTPAccountTypeType	AccountType;
};

///资金转账
struct CXTPFundTransferField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///投资者资金帐号
	TXTPAccountIDType	AccountID;
	///资金帐户密码
	TXTPPasswordType	Password;
	///用户代码
	TXTPUserIDType	UserID;
	///交易金额
	TXTPTradeAmountType	TradeAmount;
	///摘要
	TXTPDigestType	Digest;
	///会话编号
	TXTPSessionIDType	SessionID;
	///Liber核心流水号
	TXTPLiberSerialType	LiberSerial;
	///转账平台流水号
	TXTPPlateSerialType	PlateSerial;
	///第三方流水号
	TXTPBankSerialType	TransferSerial;
	///交易日
	TXTPDateType	TradingDay;
	///转账时间
	TXTPTimeType	TradeTime;
	///出入金方向
	TXTPFundDirectionType	FundDirection;
	///错误代码
	TXTPErrorIDType	ErrorID;
	///错误信息
	TXTPErrorMsgType	ErrorMsg;
};

///资金转账查询请求
struct CXTPQryFundTransferSerialField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者资金帐号
	TXTPAccountIDType	AccountID;
	///账户类型
	TXTPAccountTypeType	AccountType;
};

///资金内转
struct CXTPFundInterTransferField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///用户代码
	TXTPUserIDType	UserID;
	///资金账户代码
	TXTPAccountIDType	AccountID;
	///资金账户密码
	TXTPPasswordType	Password;
	///金额
	TXTPTradeAmountType	TradeAmount;
	///内转类型
	TXTPFundInterTransferTypeType	TransferType;
	///资金内转编号
	TXTPLiberSerialType	SerialID;
};

///资金内转流水
struct CXTPFundInterTransferSerialField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
	///用户代码
	TXTPUserIDType	UserID;
	///资金账户代码
	TXTPAccountIDType	AccountID;
	///资金账户密码
	TXTPPasswordType	Password;
	///金额
	TXTPTradeAmountType	TradeAmount;
	///内转类型
	TXTPFundInterTransferTypeType	TransferType;
	///资金内转编号
	TXTPLiberSerialType	SerialID;
	///转账时间
	TXTPTimeType	TransferTime;
	///错误代码
	TXTPErrorIDType	ErrorID;
	///错误信息
	TXTPErrorMsgType	ErrorMsg;
};

///资金内转流水查询请求
struct CXTPQryFundInterTransferSerialField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///投资者代码
	TXTPInvestorIDType	InvestorID;
};

///获取数据库信息
struct CXTPFetchDBInfoField
{
	///用户代码
	TXTPUserIDType	UserID;
	///密码
	TXTPPasswordType	Password;
	///数据库索引
	TXTPUserNameType	DBIndex;
	///数据库IP地址
	TXTPIPAddressType	IPAddress;
	///数据库IP端口
	TXTPIPPortType	IPPort;
	///数据库名称
	TXTPUserNameType	DBName;
	///数据库用户名
	TXTPUserIDType	DBUserID;
	///数据库密码
	TXTPPasswordType	DBPassword;
};

///MD用户信息
struct CXTPMDUserInfoField
{
	///经纪公司代码
	TXTPBrokerIDType	BrokerID;
	///用户代码
	TXTPUserIDType	UserID;
	///用户名称
	TXTPUserNameType	UserName;
	///密码
	TXTPPasswordType	Password;
	///行情系统编号
	TXTPSequenceNoType	MDSysID;
	///股票最大订阅数量
	TXTPVolumeType	MaxStockCount;
	///期权最大订阅数量
	TXTPVolumeType	MaxOptionsCount;
};


#endif
