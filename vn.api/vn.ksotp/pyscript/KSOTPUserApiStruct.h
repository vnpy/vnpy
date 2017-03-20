#ifndef __KSOTPUSERAPISTRUCT_H_INCLUDED_
#define __KSOTPUSERAPISTRUCT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KSOTPUserApiDataType.h"

namespace KingstarAPI
{
///响应信息
struct CKSOTPRspInfoField
{
	///错误代码
	TKSOTPErrorIDType	ErrorID;
	///错误信息
	TKSOTPErrorMsgType	ErrorMsg;
};

///用户登录请求
struct CKSOTPReqUserLoginField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///用户代码
	TKSOTPUserIDType	UserID;
	///密码
	TKSOTPPasswordType	Password;
	///用户端产品信息
	TKSOTPProductInfoType	UserProductInfo;
	///Mac地址
	TKSOTPMacAddressType	MacAddress;
	///终端IP地址
	TKSOTPIPAddressType	ClientIPAddress;
};

///用户登录应答
struct CKSOTPRspUserLoginField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///交易日
	TKSOTPDateType	TradingDay;
	///登录成功时间
	TKSOTPTimeType	LoginTime;
	///用户代码
	TKSOTPUserIDType	UserID;
	///交易系统名称
	TKSOTPSystemNameType	SystemName;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///最大报单引用
	TKSOTPOrderRefType	MaxOrderRef;
	///上证所时间
	TKSOTPTimeType	SSETime;
};

///用户登出请求
struct CKSOTPUserLogoutField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///用户代码
	TKSOTPUserIDType	UserID;
};

///用户口令变更
struct CKSOTPUserPasswordUpdateField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///用户代码
	TKSOTPUserIDType	UserID;
	///原来的口令
	TKSOTPPasswordType	OldPassword;
	///新的口令
	TKSOTPPasswordType	NewPassword;
};

///资金账户口令变更域
struct CKSOTPTradingAccountPasswordUpdateField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///原来的口令
	TKSOTPPasswordType	OldPassword;
	///新的口令
	TKSOTPPasswordType	NewPassword;
};

///输入报单
struct CKSOTPInputOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///报单引用
	TKSOTPOrderRefType	OrderRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///报单价格条件
	TKSOTPOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TKSOTPDirectionType	Direction;
	///开平标志
	TKSOTPOffsetFlagType	OffsetFlag;
	///备兑标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///价格
	TKSOTPPriceType	LimitPrice;
	///数量
	TKSOTPVolumeType	VolumeTotalOriginal;
	///有效期类型
	TKSOTPTimeConditionType	TimeCondition;
	///GTD日期
	TKSOTPDateType	GTDDate;
	///成交量类型
	TKSOTPVolumeConditionType	VolumeCondition;
	///最小成交量
	TKSOTPVolumeType	MinVolume;
	///触发条件
	TKSOTPContingentConditionType	ContingentCondition;
	///止损价
	TKSOTPPriceType	StopPrice;
	///强平原因
	TKSOTPForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TKSOTPBoolType	IsAutoSuspend;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///用户强评标志
	TKSOTPBoolType	UserForceClose;
	///互换单标志
	TKSOTPBoolType	IsSwapOrder;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///输入报单操作
struct CKSOTPInputOrderActionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///报单引用
	TKSOTPOrderRefType	OrderRef;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///报单编号
	TKSOTPOrderSysIDType	OrderSysID;
	///操作标志
	TKSOTPActionFlagType	ActionFlag;
	///价格
	TKSOTPPriceType	LimitPrice;
	///数量变化
	TKSOTPVolumeType	VolumeChange;
	///用户代码
	TKSOTPUserIDType	UserID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
};

///查询报单
struct CKSOTPQryOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///报单编号
	TKSOTPOrderSysIDType	OrderSysID;
};

///查询成交
struct CKSOTPQryTradeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///开始时间
	TKSOTPTimeType	TradeTimeStart;
	///结束时间
	TKSOTPTimeType	TradeTimeEnd;
};

///查询投资者持仓
struct CKSOTPQryInvestorPositionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///投资者持仓
struct CKSOTPInvestorPositionField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///持仓多空方向
	TKSOTPPosiDirectionType	PosiDirection;
	///备兑标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///持仓日期
	TKSOTPPositionDateType	PositionDate;
	///上日持仓
	TKSOTPVolumeType	YdPosition;
	///今日持仓
	TKSOTPVolumeType	Position;
	///多头冻结
	TKSOTPVolumeType	LongFrozen;
	///空头冻结
	TKSOTPVolumeType	ShortFrozen;
	///开仓冻结金额
	TKSOTPMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TKSOTPMoneyType	ShortFrozenAmount;
	///开仓量
	TKSOTPVolumeType	OpenVolume;
	///开仓金额
	TKSOTPMoneyType	OpenAmount;
	///平仓金额
	TKSOTPMoneyType	CloseAmount;
	///持仓成本
	TKSOTPMoneyType	PositionCost;
	///占用的保证金
	TKSOTPMoneyType	UseMargin;
	///冻结的保证金
	TKSOTPMoneyType	FrozenMargin;
	///冻结的资金
	TKSOTPMoneyType	FrozenCash;
	///冻结的手续费
	TKSOTPMoneyType	FrozenCommission;
	///资金差额
	TKSOTPMoneyType	CashIn;
	///手续费
	TKSOTPMoneyType	Commission;
	///平仓盈亏
	TKSOTPMoneyType	CloseProfit;
	///持仓盈亏
	TKSOTPMoneyType	PositionProfit;
	///上次结算价
	TKSOTPPriceType	PreSettlementPrice;
	///本次结算价
	TKSOTPPriceType	SettlementPrice;
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///开仓成本
	TKSOTPMoneyType	OpenCost;
	///交易所保证金
	TKSOTPMoneyType	ExchangeMargin;
	///逐日盯市平仓盈亏
	TKSOTPMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TKSOTPMoneyType	CloseProfitByTrade;
	///今日持仓
	TKSOTPVolumeType	TodayPosition;
	///保证金率
	TKSOTPRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TKSOTPRatioType	MarginRateByVolume;
	///执行冻结
	TKSOTPVolumeType	StrikeFrozen;
	///执行冻结金额
	TKSOTPMoneyType	StrikeFrozenAmount;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///查询资金账户
struct CKSOTPQryTradingAccountField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
};

///资金账户
struct CKSOTPTradingAccountField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///上次结算准备金
	TKSOTPMoneyType	PreBalance;
	///上次占用的保证金
	TKSOTPMoneyType	PreMargin;
	///入金金额
	TKSOTPMoneyType	Deposit;
	///出金金额
	TKSOTPMoneyType	Withdraw;
	///冻结的保证金
	TKSOTPMoneyType	FrozenMargin;
	///冻结的资金
	TKSOTPMoneyType	FrozenCash;
	///冻结的手续费
	TKSOTPMoneyType	FrozenCommission;
	///当前保证金总额
	TKSOTPMoneyType	CurrMargin;
	///资金差额
	TKSOTPMoneyType	CashIn;
	///手续费
	TKSOTPMoneyType	Commission;
	///平仓盈亏
	TKSOTPMoneyType	CloseProfit;
	///持仓盈亏
	TKSOTPMoneyType	PositionProfit;
	///证券结算准备金
	TKSOTPMoneyType	Balance;
	///可用资金
	TKSOTPMoneyType	Available;
	///可取资金
	TKSOTPMoneyType	WithdrawQuota;
	///基本准备金
	TKSOTPMoneyType	Reserve;
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///信用额度
	TKSOTPMoneyType	Credit;
	///质押金额
	TKSOTPMoneyType	Mortgage;
	///交易所保证金
	TKSOTPMoneyType	ExchangeMargin;
	///投资者交割保证金
	TKSOTPMoneyType	DeliveryMargin;
	///交易所交割保证金
	TKSOTPMoneyType	ExchangeDeliveryMargin;
};

///查询投资者
struct CKSOTPQryInvestorField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
};

///投资者
struct CKSOTPInvestorField
{
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者名称
	TKSOTPPartyNameType	InvestorName;
	///证件类型
	TKSOTPIdCardTypeType	IdentifiedCardType;
	///证件号码
	TKSOTPIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TKSOTPBoolType	IsActive;
	///联系电话
	TKSOTPTelephoneType	Telephone;
	///通讯地址
	TKSOTPAddressType	Address;
	///开户日期
	TKSOTPDateType	OpenDate;
	///手机
	TKSOTPMobileType	Mobile;
};

///查询合约账号
struct CKSOTPQryTradingCodeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///交易编码
struct CKSOTPTradingCodeField
{
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///合约账号
	TKSOTPClientIDType	ClientID;
	///是否活跃
	TKSOTPBoolType	IsActive;
	///交易编码类型
	TKSOTPClientIDTypeType	ClientIDType;
};

///查询交易所
struct CKSOTPQryExchangeField
{
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///交易所
struct CKSOTPExchangeField
{
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///交易所名称
	TKSOTPExchangeNameType	ExchangeName;
};

///查询合约
struct CKSOTPQryInstrumentField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///合约
struct CKSOTPInstrumentField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///合约名称
	TKSOTPInstrumentNameType	InstrumentName;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///品种代码
	TKSOTPInstrumentIDType	ProductID;
	///产品类型
	TKSOTPProductClassType	ProductClass;
	///交割年份
	TKSOTPYearType	DeliveryYear;
	///交割月
	TKSOTPMonthType	DeliveryMonth;
	///市价单最大下单量
	TKSOTPVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TKSOTPVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TKSOTPVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TKSOTPVolumeType	MinLimitOrderVolume;
	///合约数量乘数
	TKSOTPVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TKSOTPPriceType	PriceTick;
	///创建日
	TKSOTPDateType	CreateDate;
	///上市日
	TKSOTPDateType	OpenDate;
	///到期日
	TKSOTPDateType	ExpireDate;
	///开始交割日
	TKSOTPDateType	StartDelivDate;
	///结束交割日
	TKSOTPDateType	EndDelivDate;
	///合约生命周期状态
	TKSOTPInstLifePhaseType	InstLifePhase;
	///当前是否交易
	TKSOTPBoolType	IsTrading;
	///持仓类型
	TKSOTPPositionTypeType	PositionType;
	///持仓日期类型
	TKSOTPPositionDateTypeType	PositionDateType;
	///多头保证金率
	TKSOTPRatioType	LongMarginRatio;
	///空头保证金率
	TKSOTPRatioType	ShortMarginRatio;
	///基础商品代码
	TKSOTPInstrumentIDType	UnderlyingInstrID;
	///执行价
	TKSOTPPriceType	StrikePrice;
	///期权类型
	TKSOTPOptionsTypeType	OptionsType;
	///合约基础商品乘数
	TKSOTPUnderlyingMultipleType	UnderlyingMultiple;
	///合约标识码
	TKSOTPInstrumentCodeType	InstrumentCode;
};

///查询投资者持仓明细
struct CKSOTPQryInvestorPositionDetailField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///投资者持仓明细
struct CKSOTPInvestorPositionDetailField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///备兑标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///买卖
	TKSOTPDirectionType	Direction;
	///开仓日期
	TKSOTPDateType	OpenDate;
	///成交编号
	TKSOTPTradeIDType	TradeID;
	///数量
	TKSOTPVolumeType	Volume;
	///开仓价
	TKSOTPPriceType	OpenPrice;
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///成交类型
	TKSOTPTradeTypeType	TradeType;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///逐日盯市平仓盈亏
	TKSOTPMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TKSOTPMoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	TKSOTPMoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	TKSOTPMoneyType	PositionProfitByTrade;
	///投资者保证金
	TKSOTPMoneyType	Margin;
	///交易所保证金
	TKSOTPMoneyType	ExchMargin;
	///保证金率
	TKSOTPRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TKSOTPRatioType	MarginRateByVolume;
	///昨结算价
	TKSOTPPriceType	LastSettlementPrice;
	///结算价
	TKSOTPPriceType	SettlementPrice;
};

///查询交易事件通知
struct CKSOTPQryTradingNoticeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
};

///用户事件通知
struct CKSOTPTradingNoticeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///序列系列号
	TKSOTPSequenceSeriesType	SequenceSeries;
	///用户代码
	TKSOTPUserIDType	UserID;
	///发送时间
	TKSOTPTimeType	SendTime;
	///序列号
	TKSOTPSequenceNoType	SequenceNo;
	///消息正文
	TKSOTPContentType	FieldContent;
};

///用户事件通知信息
struct CKSOTPTradingNoticeInfoField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///发送时间
	TKSOTPTimeType	SendTime;
	///消息正文
	TKSOTPContentType	FieldContent;
	///序列系列号
	TKSOTPSequenceSeriesType	SequenceSeries;
	///序列号
	TKSOTPSequenceNoType	SequenceNo;
};

///输入的执行宣告
struct CKSOTPInputExecOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///执行宣告引用
	TKSOTPOrderRefType	ExecOrderRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///数量
	TKSOTPVolumeType	Volume;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///开平标志
	TKSOTPOffsetFlagType	OffsetFlag;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///执行类型
	TKSOTPActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	TKSOTPPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	TKSOTPExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	TKSOTPExecOrderCloseFlagType	CloseFlag;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///输入执行宣告操作
struct CKSOTPInputExecOrderActionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///执行宣告操作引用
	TKSOTPOrderActionRefType	ExecOrderActionRef;
	///执行宣告引用
	TKSOTPOrderRefType	ExecOrderRef;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///执行宣告操作编号
	TKSOTPExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	TKSOTPActionFlagType	ActionFlag;
	///用户代码
	TKSOTPUserIDType	UserID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
};

///录入锁定
struct CKSOTPInputLockField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///锁定引用
	TKSOTPOrderRefType	LockRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///数量
	TKSOTPVolumeType	Volume;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///锁定类型
	TKSOTPLockTypeType	LockType;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///锁定
struct CKSOTPLockField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///锁定引用
	TKSOTPOrderRefType	LockRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///数量
	TKSOTPVolumeType	Volume;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///锁定类型
	TKSOTPLockTypeType	LockType;
	///本地锁定编号
	TKSOTPOrderLocalIDType	LockLocalID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///会员代码
	TKSOTPParticipantIDType	ParticipantID;
	///客户代码
	TKSOTPClientIDType	ClientID;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TKSOTPTraderIDType	TraderID;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///执行宣告提交状态
	TKSOTPOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TKSOTPSequenceNoType	NotifySequence;
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///锁定编号
	TKSOTPOrderSysIDType	LockSysID;
	///报单日期
	TKSOTPDateType	InsertDate;
	///插入时间
	TKSOTPTimeType	InsertTime;
	///撤销时间
	TKSOTPTimeType	CancelTime;
	///锁定状态
	TKSOTPOrderActionStatusType	LockStatus;
	///结算会员编号
	TKSOTPParticipantIDType	ClearingPartID;
	///序号
	TKSOTPSequenceNoType	SequenceNo;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///用户端产品信息
	TKSOTPProductInfoType	UserProductInfo;
	///状态信息
	TKSOTPErrorMsgType	StatusMsg;
	///操作用户代码
	TKSOTPUserIDType	ActiveUserID;
	///经纪公司报单编号
	TKSOTPSequenceNoType	BrokerLockSeq;
	///营业部编号
	TKSOTPBranchIDType	BranchID;
};

///查询锁定
struct CKSOTPQryLockField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///锁定编号
	TKSOTPOrderSysIDType	LockSysID;
};

///执行宣告查询
struct CKSOTPQryExecOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///执行宣告编号
	TKSOTPExecOrderSysIDType	ExecOrderSysID;
};

///输入查询宣告数量
struct CKSOTPQryExecOrderVolumeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///买卖标志
	TKSOTPDirectionType	Direction;
};

///输出查询宣告数量
struct CKSOTPExecOrderVolumeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///可申请执行量
	TKSOTPVolumeType	ExecVolume;
	///可申请放弃量
	TKSOTPVolumeType	ActionVolume;
	///已申请执行量
	TKSOTPVolumeType	ExecedVolume;
	///已申请放弃量 
	TKSOTPVolumeType	ActionedVolume;
	///买卖标志
	TKSOTPDirectionType	Direction;
};

///查询锁定证券仓位
struct CKSOTPQryLockPositionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///锁定证券仓位
struct CKSOTPLockPositionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///数量
	TKSOTPVolumeType	Volume;
	///已锁定数量
	TKSOTPVolumeType	FrozenVolume;
};

///输入查询标的券信息请求
struct CKSOTPQryUnderlyingStockInfoField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///品种代码
	TKSOTPInstrumentIDType	ProductID;
};

///输出查询标的券信息请求
struct CKSOTPUnderlyingStockInfoField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///品种代码
	TKSOTPInstrumentIDType	ProductID;
	///昨收盘
	TKSOTPPriceType	PreClosePrice;
	///安全系数
	TKSOTPRatioType	GuarantRatio;
};

///输入查询个股期权手续费率请求
struct CKSOTPQryOTPInsCommRateField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///输出查询个股期权合约手续费率
struct CKSOTPOTPInsCommRateField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///投资者范围
	TKSOTPInvestorRangeType	InvestorRange;
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///开仓手续费率
	TKSOTPRatioType	OpenRatioByMoney;
	///开仓手续费
	TKSOTPRatioType	OpenRatioByVolume;
	///平仓手续费率
	TKSOTPRatioType	CloseRatioByMoney;
	///平仓手续费
	TKSOTPRatioType	CloseRatioByVolume;
	///平今手续费率
	TKSOTPRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TKSOTPRatioType	CloseTodayRatioByVolume;
	///执行手续费率
	TKSOTPRatioType	StrikeRatioByMoney;
	///执行手续费
	TKSOTPRatioType	StrikeRatioByVolume;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///输入查询个股期权合约保证金率请求
struct CKSOTPQryInstrumentMarginRateField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///输出查询个股期权合约保证金率
struct CKSOTPInstrumentMarginRateField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///投资者范围
	TKSOTPInvestorRangeType	InvestorRange;
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///多头保证金率
	TKSOTPRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TKSOTPMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TKSOTPRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TKSOTPMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TKSOTPBoolType	IsRelative;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///输入个股行权指派信息
struct CKSOTPQryOTPAssignmentField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///买卖
	TKSOTPDirectionType	Direction;
};

///输出个股行权指派信息
struct CKSOTPOTPAssignmentField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///买卖
	TKSOTPDirectionType	Direction;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///合约名称
	TKSOTPInstrumentNameType	InstrumentName;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///上日持仓
	TKSOTPVolumeType	YdPosition;
	///行权指派合约数量
	TKSOTPVolumeType	AssInsVo;
	///行权标的证券数量
	TKSOTPVolumeType	AssProVol;
	///行权指派应付金额
	TKSOTPMoneyType	FeePay;
	///期权C/P标志
	TKSOTPOptionsTypeType	OptionsType;
	///行权交收日
	TKSOTPDateType	DeliveryDay;
	///个股合约标识码
	TKSOTPInstrumentIDType	StockID;
};

///查询行情
struct CKSOTPQryDepthMarketDataField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///深度行情
struct CKSOTPDepthMarketDataField
{
	///交易日
	TKSOTPDateType	TradingDay;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///最新价
	TKSOTPPriceType	LastPrice;
	///上次结算价
	TKSOTPPriceType	PreSettlementPrice;
	///昨收盘
	TKSOTPPriceType	PreClosePrice;
	///昨持仓量
	TKSOTPLargeVolumeType	PreOpenInterest;
	///今开盘
	TKSOTPPriceType	OpenPrice;
	///最高价
	TKSOTPPriceType	HighestPrice;
	///最低价
	TKSOTPPriceType	LowestPrice;
	///数量
	TKSOTPVolumeType	Volume;
	///成交金额
	TKSOTPMoneyType	Turnover;
	///持仓量
	TKSOTPLargeVolumeType	OpenInterest;
	///今收盘
	TKSOTPPriceType	ClosePrice;
	///本次结算价
	TKSOTPPriceType	SettlementPrice;
	///涨停板价
	TKSOTPPriceType	UpperLimitPrice;
	///跌停板价
	TKSOTPPriceType	LowerLimitPrice;
	///昨虚实度
	TKSOTPRatioType	PreDelta;
	///今虚实度
	TKSOTPRatioType	CurrDelta;
	///最后修改时间
	TKSOTPTimeType	UpdateTime;
	///最后修改毫秒
	TKSOTPMillisecType	UpdateMillisec;
	///申买价一
	TKSOTPPriceType	BidPrice1;
	///申买量一
	TKSOTPVolumeType	BidVolume1;
	///申卖价一
	TKSOTPPriceType	AskPrice1;
	///申卖量一
	TKSOTPVolumeType	AskVolume1;
	///申买价二
	TKSOTPPriceType	BidPrice2;
	///申买量二
	TKSOTPVolumeType	BidVolume2;
	///申卖价二
	TKSOTPPriceType	AskPrice2;
	///申卖量二
	TKSOTPVolumeType	AskVolume2;
	///申买价三
	TKSOTPPriceType	BidPrice3;
	///申买量三
	TKSOTPVolumeType	BidVolume3;
	///申卖价三
	TKSOTPPriceType	AskPrice3;
	///申卖量三
	TKSOTPVolumeType	AskVolume3;
	///申买价四
	TKSOTPPriceType	BidPrice4;
	///申买量四
	TKSOTPVolumeType	BidVolume4;
	///申卖价四
	TKSOTPPriceType	AskPrice4;
	///申卖量四
	TKSOTPVolumeType	AskVolume4;
	///申买价五
	TKSOTPPriceType	BidPrice5;
	///申买量五
	TKSOTPVolumeType	BidVolume5;
	///申卖价五
	TKSOTPPriceType	AskPrice5;
	///申卖量五
	TKSOTPVolumeType	AskVolume5;
	///当日均价
	TKSOTPPriceType	AveragePrice;
	///业务日期
	TKSOTPDateType	ActionDay;
};

///发给做市商的询价请求
struct CKSOTPForQuoteRspField
{
	///交易日
	TKSOTPDateType	TradingDay;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///询价编号
	TKSOTPOrderSysIDType	ForQuoteSysID;
	///询价时间
	TKSOTPTimeType	ForQuoteTime;
	///业务日期
	TKSOTPDateType	ActionDay;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///报单
struct CKSOTPOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///报单引用
	TKSOTPOrderRefType	OrderRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///报单价格条件
	TKSOTPOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TKSOTPDirectionType	Direction;
	///开平标志
	TKSOTPOffsetFlagType	OffsetFlag;
	///价格
	TKSOTPPriceType	LimitPrice;
	///备兑标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///数量
	TKSOTPVolumeType	VolumeTotalOriginal;
	///有效期类型
	TKSOTPTimeConditionType	TimeCondition;
	///GTD日期
	TKSOTPDateType	GTDDate;
	///成交量类型
	TKSOTPVolumeConditionType	VolumeCondition;
	///最小成交量
	TKSOTPVolumeType	MinVolume;
	///触发条件
	TKSOTPContingentConditionType	ContingentCondition;
	///止损价
	TKSOTPPriceType	StopPrice;
	///强平原因
	TKSOTPForceCloseReasonType	ForceCloseReason;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///本地报单编号
	TKSOTPOrderLocalIDType	OrderLocalID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///会员代码
	TKSOTPParticipantIDType	ParticipantID;
	///合约账号
	TKSOTPClientIDType	ClientID;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TKSOTPTraderIDType	TraderID;
	///报单提交状态
	TKSOTPOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TKSOTPSequenceNoType	NotifySequence;
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///报单编号
	TKSOTPOrderSysIDType	OrderSysID;
	///报单来源
	TKSOTPOrderSourceType	OrderSource;
	///报单状态
	TKSOTPOrderStatusType	OrderStatus;
	///报单类型
	TKSOTPOrderTypeType	OrderType;
	///今成交数量
	TKSOTPVolumeType	VolumeTraded;
	///剩余数量
	TKSOTPVolumeType	VolumeTotal;
	///报单日期
	TKSOTPDateType	InsertDate;
	///委托时间
	TKSOTPTimeType	InsertTime;
	///激活时间
	TKSOTPTimeType	ActiveTime;
	///最后修改时间
	TKSOTPTimeType	UpdateTime;
	///撤销时间
	TKSOTPTimeType	CancelTime;
	///序号
	TKSOTPSequenceNoType	SequenceNo;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///用户端产品信息
	TKSOTPProductInfoType	UserProductInfo;
	///状态信息
	TKSOTPErrorMsgType	StatusMsg;
	///用户强评标志
	TKSOTPBoolType	UserForceClose;
	///操作用户代码
	TKSOTPUserIDType	ActiveUserID;
	///经纪公司报单编号
	TKSOTPSequenceNoType	BrokerOrderSeq;
};

///成交
struct CKSOTPTradeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///报单引用
	TKSOTPOrderRefType	OrderRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///成交编号
	TKSOTPTradeIDType	TradeID;
	///买卖方向
	TKSOTPDirectionType	Direction;
	///报单编号
	TKSOTPOrderSysIDType	OrderSysID;
	///会员代码
	TKSOTPParticipantIDType	ParticipantID;
	///合约账号
	TKSOTPClientIDType	ClientID;
	///交易角色
	TKSOTPTradingRoleType	TradingRole;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///开平标志
	TKSOTPOffsetFlagType	OffsetFlag;
	///备兑标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///价格
	TKSOTPPriceType	Price;
	///数量
	TKSOTPVolumeType	Volume;
	///成交时期
	TKSOTPDateType	TradeDate;
	///成交时间
	TKSOTPTimeType	TradeTime;
	///成交类型
	TKSOTPTradeTypeType	TradeType;
	///成交价来源
	TKSOTPPriceSourceType	PriceSource;
	///交易所交易员代码
	TKSOTPTraderIDType	TraderID;
	///本地报单编号
	TKSOTPOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TKSOTPParticipantIDType	ClearingPartID;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///序号
	TKSOTPSequenceNoType	SequenceNo;
	///交易日
	TKSOTPDateType	TradingDay;
	///经纪公司报单编号
	TKSOTPSequenceNoType	BrokerOrderSeq;
	///成交来源
	TKSOTPTradeSourceType	TradeSource;
};

///执行宣告
struct CKSOTPExecOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///执行宣告引用
	TKSOTPOrderRefType	ExecOrderRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///数量
	TKSOTPVolumeType	Volume;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///开平标志
	TKSOTPOffsetFlagType	OffsetFlag;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///执行类型
	TKSOTPActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	TKSOTPPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	TKSOTPExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	TKSOTPExecOrderCloseFlagType	CloseFlag;
	///本地执行宣告编号
	TKSOTPOrderLocalIDType	ExecOrderLocalID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///会员代码
	TKSOTPParticipantIDType	ParticipantID;
	///客户代码
	TKSOTPClientIDType	ClientID;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TKSOTPTraderIDType	TraderID;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///执行宣告提交状态
	TKSOTPOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TKSOTPSequenceNoType	NotifySequence;
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///执行宣告编号
	TKSOTPExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	TKSOTPDateType	InsertDate;
	///插入时间
	TKSOTPTimeType	InsertTime;
	///撤销时间
	TKSOTPTimeType	CancelTime;
	///执行结果
	TKSOTPExecResultType	ExecResult;
	///结算会员编号
	TKSOTPParticipantIDType	ClearingPartID;
	///序号
	TKSOTPSequenceNoType	SequenceNo;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///用户端产品信息
	TKSOTPProductInfoType	UserProductInfo;
	///状态信息
	TKSOTPErrorMsgType	StatusMsg;
	///操作用户代码
	TKSOTPUserIDType	ActiveUserID;
	///经纪公司报单编号
	TKSOTPSequenceNoType	BrokerExecOrderSeq;
	///营业部编号
	TKSOTPBranchIDType	BranchID;
};

///合约状态
struct CKSOTPInstrumentStatusField
{
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///合约交易状态
	TKSOTPInstrumentStatusType	InstrumentStatus;
	///交易阶段编号
	TKSOTPTradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	TKSOTPTimeType	EnterTime;
	///进入本状态原因
	TKSOTPInstStatusEnterReasonType	EnterReason;
};

///转账请求
struct CKSOTPReqTransferField
{
	///业务功能码
	TKSOTPTradeCodeType	TradeCode;
	///银行代码
	TKSOTPBankIDType	BankID;
	///银行分支机构代码
	TKSOTPBankBrchIDType	BankBranchID;
	///期商代码
	TKSOTPBrokerIDType	BrokerID;
	///期商分支机构代码
	TKSOTPFutureBranchIDType	BrokerBranchID;
	///交易日期
	TKSOTPTradeDateType	TradeDate;
	///交易时间
	TKSOTPTradeTimeType	TradeTime;
	///银行流水号
	TKSOTPBankSerialType	BankSerial;
	///交易系统日期 
	TKSOTPTradeDateType	TradingDay;
	///银期平台消息流水号
	TKSOTPSerialType	PlateSerial;
	///最后分片标志
	TKSOTPLastFragmentType	LastFragment;
	///会话号
	TKSOTPSessionIDType	SessionID;
	///客户姓名
	TKSOTPIndividualNameType	CustomerName;
	///证件类型
	TKSOTPIdCardTypeType	IdCardType;
	///证件号码
	TKSOTPIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TKSOTPCustTypeType	CustType;
	///银行帐号
	TKSOTPBankAccountType	BankAccount;
	///银行密码
	TKSOTPPasswordType	BankPassWord;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///证券密码
	TKSOTPPasswordType	Password;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///证券公司流水号
	TKSOTPFutureSerialType	FutureSerial;
	///用户标识
	TKSOTPUserIDType	UserID;
	///验证客户证件号码标志
	TKSOTPYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///转帐金额
	TKSOTPTradeAmountType	TradeAmount;
	///证券可取金额
	TKSOTPTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TKSOTPFeePayFlagType	FeePayFlag;
	///应收客户费用
	TKSOTPCustFeeType	CustFee;
	///应收证券公司费用
	TKSOTPFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TKSOTPAddInfoType	Message;
	///摘要
	TKSOTPDigestType	Digest;
	///银行帐号类型
	TKSOTPBankAccTypeType	BankAccType;
	///渠道标志
	TKSOTPDeviceIDType	DeviceID;
	///证券单位帐号类型
	TKSOTPBankAccTypeType	BankSecuAccType;
	///证券公司银行编码
	TKSOTPBankCodingForFutureType	BrokerIDByBank;
	///证券单位帐号
	TKSOTPBankAccountType	BankSecuAcc;
	///银行密码标志
	TKSOTPPwdFlagType	BankPwdFlag;
	///证券资金密码核对标志
	TKSOTPPwdFlagType	SecuPwdFlag;
	///交易柜员
	TKSOTPOperNoType	OperNo;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///交易ID
	TKSOTPTIDType	TID;
	///转账交易状态
	TKSOTPTransferStatusType	TransferStatus;
};

///银行资金转证券响应
struct CKSOTPRspTransferField
{
	///业务功能码
	TKSOTPTradeCodeType	TradeCode;
	///银行代码
	TKSOTPBankIDType	BankID;
	///银行分支机构代码
	TKSOTPBankBrchIDType	BankBranchID;
	///期商代码
	TKSOTPBrokerIDType	BrokerID;
	///期商分支机构代码
	TKSOTPFutureBranchIDType	BrokerBranchID;
	///交易日期
	TKSOTPTradeDateType	TradeDate;
	///交易时间
	TKSOTPTradeTimeType	TradeTime;
	///银行流水号
	TKSOTPBankSerialType	BankSerial;
	///交易系统日期 
	TKSOTPTradeDateType	TradingDay;
	///银期平台消息流水号
	TKSOTPSerialType	PlateSerial;
	///最后分片标志
	TKSOTPLastFragmentType	LastFragment;
	///会话号
	TKSOTPSessionIDType	SessionID;
	///客户姓名
	TKSOTPIndividualNameType	CustomerName;
	///证件类型
	TKSOTPIdCardTypeType	IdCardType;
	///证件号码
	TKSOTPIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TKSOTPCustTypeType	CustType;
	///银行帐号
	TKSOTPBankAccountType	BankAccount;
	///银行密码
	TKSOTPPasswordType	BankPassWord;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///证券密码
	TKSOTPPasswordType	Password;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///证券公司流水号
	TKSOTPFutureSerialType	FutureSerial;
	///用户标识
	TKSOTPUserIDType	UserID;
	///验证客户证件号码标志
	TKSOTPYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///转帐金额
	TKSOTPTradeAmountType	TradeAmount;
	///证券可取金额
	TKSOTPTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TKSOTPFeePayFlagType	FeePayFlag;
	///应收客户费用
	TKSOTPCustFeeType	CustFee;
	///应收证券公司费用
	TKSOTPFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TKSOTPAddInfoType	Message;
	///摘要
	TKSOTPDigestType	Digest;
	///银行帐号类型
	TKSOTPBankAccTypeType	BankAccType;
	///渠道标志
	TKSOTPDeviceIDType	DeviceID;
	///证券单位帐号类型
	TKSOTPBankAccTypeType	BankSecuAccType;
	///证券公司银行编码
	TKSOTPBankCodingForFutureType	BrokerIDByBank;
	///证券单位帐号
	TKSOTPBankAccountType	BankSecuAcc;
	///银行密码标志
	TKSOTPPwdFlagType	BankPwdFlag;
	///证券资金密码核对标志
	TKSOTPPwdFlagType	SecuPwdFlag;
	///交易柜员
	TKSOTPOperNoType	OperNo;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///交易ID
	TKSOTPTIDType	TID;
	///转账交易状态
	TKSOTPTransferStatusType	TransferStatus;
	///错误代码
	TKSOTPErrorIDType	ErrorID;
	///错误信息
	TKSOTPErrorMsgType	ErrorMsg;
};

///查询签约银行请求
struct CKSOTPQryContractBankField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///银行代码
	TKSOTPBankIDType	BankID;
	///银行分中心代码
	TKSOTPBankBrchIDType	BankBrchID;
};

///查询签约银行响应
struct CKSOTPContractBankField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///银行代码
	TKSOTPBankIDType	BankID;
	///银行分中心代码
	TKSOTPBankBrchIDType	BankBrchID;
	///银行名称
	TKSOTPBankNameType	BankName;
};

///查询账户信息请求
struct CKSOTPReqQueryAccountField
{
	///业务功能码
	TKSOTPTradeCodeType	TradeCode;
	///银行代码
	TKSOTPBankIDType	BankID;
	///银行分支机构代码
	TKSOTPBankBrchIDType	BankBranchID;
	///期商代码
	TKSOTPBrokerIDType	BrokerID;
	///期商分支机构代码
	TKSOTPFutureBranchIDType	BrokerBranchID;
	///交易日期
	TKSOTPTradeDateType	TradeDate;
	///交易时间
	TKSOTPTradeTimeType	TradeTime;
	///银行流水号
	TKSOTPBankSerialType	BankSerial;
	///交易系统日期 
	TKSOTPTradeDateType	TradingDay;
	///银期平台消息流水号
	TKSOTPSerialType	PlateSerial;
	///最后分片标志
	TKSOTPLastFragmentType	LastFragment;
	///会话号
	TKSOTPSessionIDType	SessionID;
	///客户姓名
	TKSOTPIndividualNameType	CustomerName;
	///证件类型
	TKSOTPIdCardTypeType	IdCardType;
	///证件号码
	TKSOTPIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TKSOTPCustTypeType	CustType;
	///银行帐号
	TKSOTPBankAccountType	BankAccount;
	///银行密码
	TKSOTPPasswordType	BankPassWord;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///证券密码
	TKSOTPPasswordType	Password;
	///证券公司流水号
	TKSOTPFutureSerialType	FutureSerial;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///用户标识
	TKSOTPUserIDType	UserID;
	///验证客户证件号码标志
	TKSOTPYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///摘要
	TKSOTPDigestType	Digest;
	///银行帐号类型
	TKSOTPBankAccTypeType	BankAccType;
	///渠道标志
	TKSOTPDeviceIDType	DeviceID;
	///证券单位帐号类型
	TKSOTPBankAccTypeType	BankSecuAccType;
	///证券公司银行编码
	TKSOTPBankCodingForFutureType	BrokerIDByBank;
	///证券单位帐号
	TKSOTPBankAccountType	BankSecuAcc;
	///银行密码标志
	TKSOTPPwdFlagType	BankPwdFlag;
	///证券资金密码核对标志
	TKSOTPPwdFlagType	SecuPwdFlag;
	///交易柜员
	TKSOTPOperNoType	OperNo;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///交易ID
	TKSOTPTIDType	TID;
};

///查询账户信息响应
struct CKSOTPRspQueryAccountField
{
	///业务功能码
	TKSOTPTradeCodeType	TradeCode;
	///银行代码
	TKSOTPBankIDType	BankID;
	///银行分支机构代码
	TKSOTPBankBrchIDType	BankBranchID;
	///期商代码
	TKSOTPBrokerIDType	BrokerID;
	///期商分支机构代码
	TKSOTPFutureBranchIDType	BrokerBranchID;
	///交易日期
	TKSOTPTradeDateType	TradeDate;
	///交易时间
	TKSOTPTradeTimeType	TradeTime;
	///银行流水号
	TKSOTPBankSerialType	BankSerial;
	///交易系统日期 
	TKSOTPTradeDateType	TradingDay;
	///银期平台消息流水号
	TKSOTPSerialType	PlateSerial;
	///最后分片标志
	TKSOTPLastFragmentType	LastFragment;
	///会话号
	TKSOTPSessionIDType	SessionID;
	///客户姓名
	TKSOTPIndividualNameType	CustomerName;
	///证件类型
	TKSOTPIdCardTypeType	IdCardType;
	///证件号码
	TKSOTPIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TKSOTPCustTypeType	CustType;
	///银行帐号
	TKSOTPBankAccountType	BankAccount;
	///银行密码
	TKSOTPPasswordType	BankPassWord;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///证券密码
	TKSOTPPasswordType	Password;
	///证券公司流水号
	TKSOTPFutureSerialType	FutureSerial;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///用户标识
	TKSOTPUserIDType	UserID;
	///验证客户证件号码标志
	TKSOTPYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///摘要
	TKSOTPDigestType	Digest;
	///银行帐号类型
	TKSOTPBankAccTypeType	BankAccType;
	///渠道标志
	TKSOTPDeviceIDType	DeviceID;
	///证券单位帐号类型
	TKSOTPBankAccTypeType	BankSecuAccType;
	///证券公司银行编码
	TKSOTPBankCodingForFutureType	BrokerIDByBank;
	///证券单位帐号
	TKSOTPBankAccountType	BankSecuAcc;
	///银行密码标志
	TKSOTPPwdFlagType	BankPwdFlag;
	///证券资金密码核对标志
	TKSOTPPwdFlagType	SecuPwdFlag;
	///交易柜员
	TKSOTPOperNoType	OperNo;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///交易ID
	TKSOTPTIDType	TID;
	///银行可用金额
	TKSOTPTradeAmountType	BankUseAmount;
	///银行可取金额
	TKSOTPTradeAmountType	BankFetchAmount;
};

///请求查询转帐流水
struct CKSOTPQryTransferSerialField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///银行编码
	TKSOTPBankIDType	BankID;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
};

///查询账户信息通知
struct CKSOTPNotifyQueryAccountField
{
	///业务功能码
	TKSOTPTradeCodeType	TradeCode;
	///银行代码
	TKSOTPBankIDType	BankID;
	///银行分支机构代码
	TKSOTPBankBrchIDType	BankBranchID;
	///期商代码
	TKSOTPBrokerIDType	BrokerID;
	///期商分支机构代码
	TKSOTPFutureBranchIDType	BrokerBranchID;
	///交易日期
	TKSOTPTradeDateType	TradeDate;
	///交易时间
	TKSOTPTradeTimeType	TradeTime;
	///银行流水号
	TKSOTPBankSerialType	BankSerial;
	///交易系统日期 
	TKSOTPTradeDateType	TradingDay;
	///银期平台消息流水号
	TKSOTPSerialType	PlateSerial;
	///最后分片标志
	TKSOTPLastFragmentType	LastFragment;
	///会话号
	TKSOTPSessionIDType	SessionID;
	///客户姓名
	TKSOTPIndividualNameType	CustomerName;
	///证件类型
	TKSOTPIdCardTypeType	IdCardType;
	///证件号码
	TKSOTPIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TKSOTPCustTypeType	CustType;
	///银行帐号
	TKSOTPBankAccountType	BankAccount;
	///银行密码
	TKSOTPPasswordType	BankPassWord;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///证券密码
	TKSOTPPasswordType	Password;
	///证券公司流水号
	TKSOTPFutureSerialType	FutureSerial;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///用户标识
	TKSOTPUserIDType	UserID;
	///验证客户证件号码标志
	TKSOTPYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///摘要
	TKSOTPDigestType	Digest;
	///银行帐号类型
	TKSOTPBankAccTypeType	BankAccType;
	///渠道标志
	TKSOTPDeviceIDType	DeviceID;
	///证券单位帐号类型
	TKSOTPBankAccTypeType	BankSecuAccType;
	///证券公司银行编码
	TKSOTPBankCodingForFutureType	BrokerIDByBank;
	///证券单位帐号
	TKSOTPBankAccountType	BankSecuAcc;
	///银行密码标志
	TKSOTPPwdFlagType	BankPwdFlag;
	///证券资金密码核对标志
	TKSOTPPwdFlagType	SecuPwdFlag;
	///交易柜员
	TKSOTPOperNoType	OperNo;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///交易ID
	TKSOTPTIDType	TID;
	///银行可用金额
	TKSOTPTradeAmountType	BankUseAmount;
	///银行可取金额
	TKSOTPTradeAmountType	BankFetchAmount;
	///错误代码
	TKSOTPErrorIDType	ErrorID;
	///错误信息
	TKSOTPErrorMsgType	ErrorMsg;
};

///银期转账交易流水表
struct CKSOTPTransferSerialField
{
	///平台流水号
	TKSOTPPlateSerialType	PlateSerial;
	///交易发起方日期
	TKSOTPTradeDateType	TradeDate;
	///交易日期
	TKSOTPDateType	TradingDay;
	///交易时间
	TKSOTPTradeTimeType	TradeTime;
	///交易代码
	TKSOTPTradeCodeType	TradeCode;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///银行编码
	TKSOTPBankIDType	BankID;
	///银行分支机构编码
	TKSOTPBankBrchIDType	BankBranchID;
	///银行帐号类型
	TKSOTPBankAccTypeType	BankAccType;
	///银行帐号
	TKSOTPBankAccountType	BankAccount;
	///银行流水号
	TKSOTPBankSerialType	BankSerial;
	///证券公司编码
	TKSOTPBrokerIDType	BrokerID;
	///期商分支机构代码
	TKSOTPFutureBranchIDType	BrokerBranchID;
	///证券公司帐号类型
	TKSOTPFutureAccTypeType	FutureAccType;
	///投资者帐号
	TKSOTPAccountIDType	AccountID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///证券公司流水号
	TKSOTPFutureSerialType	FutureSerial;
	///证件类型
	TKSOTPIdCardTypeType	IdCardType;
	///证件号码
	TKSOTPIdentifiedCardNoType	IdentifiedCardNo;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///交易金额
	TKSOTPTradeAmountType	TradeAmount;
	///应收客户费用
	TKSOTPCustFeeType	CustFee;
	///应收证券公司费用
	TKSOTPFutureFeeType	BrokerFee;
	///有效标志
	TKSOTPAvailabilityFlagType	AvailabilityFlag;
	///操作员
	TKSOTPOperatorCodeType	OperatorCode;
	///新银行帐号
	TKSOTPBankAccountType	BankNewAccount;
	///错误代码
	TKSOTPErrorIDType	ErrorID;
	///错误信息
	TKSOTPErrorMsgType	ErrorMsg;
};

///指定的合约
struct CKSOTPSpecificInstrumentField
{
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///查询客户交易级别
struct CKSOTPQryInvestorTradeLevelField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
};

///客户交易级别
struct CKSOTPInvestorTradeLevelField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///交易级别
	TKSOTPTradeLevelType	TradeLevel;
};

///查询个股限购额度
struct CKSOTPQryPurchaseLimitAmtField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
};

///个股限购额度
struct CKSOTPPurchaseLimitAmtField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///限购额度
	TKSOTPMoneyType	PurLimitAmt;
};

///查询个股限仓额度
struct CKSOTPQryPositionLimitVolField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///保护性标志
	TKSOTPProtectFlagType	ProtectFlag;
	///期权C/P标志
	TKSOTPOptionsTypeType	OptionsType;
	///控制范围
	TKSOTPControlRangeType	ControlRange;
};

///查询个股限仓额度
struct CKSOTPPositionLimitVolField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///保护性标志
	TKSOTPProtectFlagType	ProtectFlag;
	///期权C/P标志
	TKSOTPOptionsTypeType	OptionsType;
	///控制范围
	TKSOTPControlRangeType	ControlRange;
	///限仓额度
	TKSOTPVolumeType	PosiLimitVol;
};

///查询投资者结算结果
struct CKSOTPQrySettlementInfoField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易日
	TKSOTPDateType	TradingDay;
};

///查询结算信息确认域
struct CKSOTPQrySettlementInfoConfirmField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
};

///投资者结算结果确认信息
struct CKSOTPSettlementInfoConfirmField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///确认日期
	TKSOTPDateType	ConfirmDate;
	///确认时间
	TKSOTPTimeType	ConfirmTime;
};

///投资者结算结果
struct CKSOTPSettlementInfoField
{
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///序号
	TKSOTPSequenceNoType	SequenceNo;
	///消息正文
	TKSOTPContentType	Content;
};

///查询历史报单
struct CKSOTPQryHistoryOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///本地报单编号
	TKSOTPOrderLocalIDType	OrderLocalID;
	///品种代码
	TKSOTPInstrumentIDType	ProductID;
	///开始日期
	TKSOTPDateType	OrderDataStart;
	///结束日期
	TKSOTPDateType	OrderDataEnd;
};

///查询历史成交
struct CKSOTPQryHistoryTradeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///品种代码
	TKSOTPInstrumentIDType	ProductID;
	///开始日期
	TKSOTPDateType	TradeDataStart;
	///结束日期
	TKSOTPDateType	TradeDataEnd;
};

///查询历史行权指派明细
struct CKSOTPQryHistoryAssignmentField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///投保标记
	TKSOTPHedgeFlagType	HedgeFlag;
	///期权类型
	TKSOTPOptionsTypeType	OptionsType;
	///交割月
	TKSOTPDateType	DeliveryMonth;
	///持仓方向
	TKSOTPPosiDirectionType	PosiDirection;
};

///查询行权交割明细
struct CKSOTPQryDelivDetailField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///交割月
	TKSOTPDateType	DeliveryMonth;
	///个股交收查询类型
	TKSOTPDelivModeType	DelivMode;
};

///自动行权执行操作
struct CKSOTPAutoExecOrderActionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///自动行权阈值(0-不自动行权,非0-代表超过阀值会自动行权(20代表20%))
	TKSOTPVolumeType	RangeVol;
};

///历史行权指派明细
struct CKSOTPHistoryAssignmentField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易日期
	TKSOTPTradeDateType	TradingDay;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///客户代码
	TKSOTPClientIDType	ClientID;
	///标的证券代码
	TKSOTPInstrumentIDType	StockInstr;
	///投保标记
	TKSOTPHedgeFlagType	HedgeFlag;
	///期权类型
	TKSOTPOptionsTypeType	OptionsType;
	///持仓方向
	TKSOTPPosiDirectionType	PosiDirection;
	///执行价
	TKSOTPPriceType	StrikePrice;
	///行权指派数量
	TKSOTPVolumeType	ExecVol;
	///标的证券应收付数量
	TKSOTPVolumeType	IOVol;
	///应收付金额
	TKSOTPMoneyType	IOAmt;
	///行权交收日
	TKSOTPDateType	DelivDate;
};

///行权交割明细
struct CKSOTPDelivDetailField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///标的证券代码
	TKSOTPInstrumentIDType	StockInstr;
	///应收/应付/扣券证券数量
	TKSOTPVolumeType	IOVol;
	///实收付数量
	TKSOTPVolumeType	IOVolInFact;
	///结算价
	TKSOTPPriceType	SettlementPrice;
	///扣券面值/结算金额
	TKSOTPMoneyType	SettlementAmt;
	///行权交收日
	TKSOTPDateType	DelivDate;
	///业务类型名称
	TKSOTPFunctionNameType	FunctionName;
};

///历史报单
struct CKSOTPHistoryOrderField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///客户姓名
	TKSOTPIndividualNameType	CustomerName;
	///合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///本地报单编号
	TKSOTPOrderLocalIDType	OrderLocalID;
	///申报时间
	TKSOTPTimeType	InsertTime;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///成交价格
	TKSOTPPriceType	TradePrice;
	///成交金额
	TKSOTPMoneyType	TradeAmount;
	///成交数量
	TKSOTPVolumeType	VolumeTraded;
	///冻结解冻金额
	TKSOTPMoneyType	FrozenAmount;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///序号
	TKSOTPSequenceNoType	SequenceNo;
	///买卖方向
	TKSOTPDirectionType	Direction;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///用户端产品信息
	TKSOTPProductInfoType	UserProductInfo;
	///请求编号
	TKSOTPRequestIDType	RequestID;
	///报单引用
	TKSOTPOrderRefType	OrderRef;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///委托价格
	TKSOTPPriceType	OrderPrice;
	///委托来源
	TKSOTPOrderSourceType	OrderSource;
	///委托日期
	TKSOTPDateType	InsertDate;
	///委托时间
	TKSOTPTimeType	OrderTime;
	///委托数量
	TKSOTPVolumeType	VolumeTotalOriginal;
	///委托状态
	TKSOTPOrderStatusType	OrderStatus;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///产品名称
	TKSOTPProductNameType	ProductName;
	///产品类型
	TKSOTPProductClassType	ProductClass;
	///投保买卖开平标志
	TKSOTPOffsetFlagType	OffsetFlag;
	///业务类型名称
	TKSOTPFunctionNameType	FunctionName;
};

///历史成交
struct CKSOTPHistoryTradeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///客户姓名
	TKSOTPIndividualNameType	CustomerName;
	///本地报单编号
	TKSOTPOrderLocalIDType	OrderLocalID;
	///币种代码
	TKSOTPCurrencyIDType	CurrencyID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///产品名称
	TKSOTPProductNameType	ProductName;
	///成交数量
	TKSOTPVolumeType	VolumeTraded;
	///成交金额
	TKSOTPMoneyType	TradeAmount;
	///成交日期
	TKSOTPDateType	TradeDate;
	///成交时间
	TKSOTPTimeType	TradeTime;
	///投保买卖开平标志
	TKSOTPOffsetFlagType	OffsetFlag;
	///业务单元
	TKSOTPBusinessUnitType	BusinessUnit;
	///手续费
	TKSOTPMoneyType	Commission;
	///备注
	TKSOTPMemoType	Memo;
	///报盘时间
	TKSOTPTimeType	TraderOfferTime;
	///成交价格
	TKSOTPPriceType	TradePrice;	
	///期权交易编码
	TKSOTPClientIDType	ClientID;
	///期权类型
	TKSOTPOptionsTypeType	OptionsType;
	///备兑标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///权利仓数量
	TKSOTPVolumeType	RoyaltyVolume;
	///义务仓数量
	TKSOTPVolumeType	ObligationVolume;
	///权利仓金额
	TKSOTPMoneyType	RoyaltyAmount;
	///义务仓金额
	TKSOTPMoneyType	ObligationAmount;
	///成交编号
	TKSOTPTradeIDType	TradeID;
	///业务类型名称
	TKSOTPFunctionNameType	FunctionName;
};

///个股组合拆分委托
struct CKSOTPInputCombActionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///策略代码
	TKSOTPCombStrategyIDType	StrategyID;
	///合约代码1
	TKSOTPInstrumentIDType	InstrumentID1;
	///合约代码2
	TKSOTPInstrumentIDType	InstrumentID2;
	///合约代码3
	TKSOTPInstrumentIDType	InstrumentID3;
	///合约代码4
	TKSOTPInstrumentIDType	InstrumentID4;
	///组合引用
	TKSOTPOrderRefType	CombActionRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///买卖方向1
	TKSOTPDirectionType	Direction1;
	///买卖方向2
	TKSOTPDirectionType	Direction2;
	///买卖方向3
	TKSOTPDirectionType	Direction3;
	///买卖方向4
	TKSOTPDirectionType	Direction4;
	///强拆标记
	TKSOTPCombActionType	 CombActionFlag;
	///数量
	TKSOTPVolumeType	Volume;
	///组合拆分标记
	TKSOTPCombDirectionType	CombDirection;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///交易所组合编号
	TKSOTPTradeIDType	ComTradeID;
};

///个股组合拆分
struct CKSOTPCombActionField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///完整合约代码
	TKSOTPInstrumentIDType	InstrumentID;
	///策略代码
	TKSOTPCombStrategyIDType	StrategyID;
	///合约代码1
	TKSOTPInstrumentIDType	InstrumentID1;
	///合约代码2
	TKSOTPInstrumentIDType	InstrumentID2;
	///合约代码3
	TKSOTPInstrumentIDType	InstrumentID3;
	///合约代码4
	TKSOTPInstrumentIDType	InstrumentID4;
	///组合引用
	TKSOTPOrderRefType	CombActionRef;
	///用户代码
	TKSOTPUserIDType	UserID;
	///买卖方向1
	TKSOTPDirectionType	Direction1;
	///买卖方向2
	TKSOTPDirectionType	Direction2;
	///买卖方向3
	TKSOTPDirectionType	Direction3;
	///买卖方向4
	TKSOTPDirectionType	Direction4;
	///强拆标记
	TKSOTPCombActionType	 CombActionFlag;
	///数量
	TKSOTPVolumeType	Volume;
	///组合拆分标记
	TKSOTPCombDirectionType	CombDirection;
	///投机套保标志
	TKSOTPHedgeFlagType	HedgeFlag;
	///本地申请组合编号
	TKSOTPOrderLocalIDType	ActionLocalID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///会员代码
	TKSOTPParticipantIDType	ParticipantID;
	///客户代码
	TKSOTPClientIDType	ClientID;
	///合约在交易所的代码
	TKSOTPExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TKSOTPTraderIDType	TraderID;
	///安装编号
	TKSOTPInstallIDType	InstallID;
	///组合状态
	TKSOTPOrderActionStatusType	ActionStatus;
	///报单提示序号
	TKSOTPSequenceNoType	NotifySequence;
	///交易日
	TKSOTPDateType	TradingDay;
	///结算编号
	TKSOTPSettlementIDType	SettlementID;
	///序号
	TKSOTPSequenceNoType	SequenceNo;
	///前置编号
	TKSOTPFrontIDType	FrontID;
	///会话编号
	TKSOTPSessionIDType	SessionID;
	///用户端产品信息
	TKSOTPProductInfoType	UserProductInfo;
	///状态信息
	TKSOTPErrorMsgType	StatusMsg;
	///交易所组合编号
	TKSOTPTradeIDType	ComTradeID;
	///报单来源
	TKSOTPOrderSourceType	OrderSource;
};

///查询个股组合持仓明细
struct CKSOTPQryInvestorPositionCombineDetailField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///产品代码
	TKSOTPInstrumentIDType	ProductID;
	///交易所组合编号
	TKSOTPTradeIDType	ComTradeID;
};

///个股组合持仓明细
struct CKSOTPInvestorPositionCombineDetailField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///交易编码
	TKSOTPClientIDType	ClientID;
	///组合编号
	TKSOTPTradeIDType	ComTradeID;
	///策略代码
	TKSOTPCombStrategyIDType	StrategyID;
	///合约代码1
	TKSOTPInstrumentIDType	InstrumentID1;
	///合约代码2
	TKSOTPInstrumentIDType	InstrumentID2;
	///合约代码3
	TKSOTPInstrumentIDType	InstrumentID3;
	///合约代码4
	TKSOTPInstrumentIDType	InstrumentID4;
	///保证金
	TKSOTPMoneyType	Margin;
	///距离自动拆分日天数
	TKSOTPVolumeType	CombActionVolume;
	///投保标记
	TKSOTPHedgeFlagType	HedgeFlag;
	///持仓量
	TKSOTPVolumeType	TotalAmt;
	///买卖方向1
	TKSOTPDirectionType	Direction1;
	///买卖方向2
	TKSOTPDirectionType	Direction2;
	///买卖方向3
	TKSOTPDirectionType	Direction3;
	///买卖方向4
	TKSOTPDirectionType	Direction4;
	///组合买卖方向
	TKSOTPDirectionType	CombDirection;
};

///个股可组合可拆分手数查询请求
struct CKSOTPQryCombActionVolumeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///交易所代码
	TKSOTPExchangeIDType	ExchangeID;
	///策略代码
	TKSOTPCombStrategyIDType	StrategyID;
	///合约代码1
	TKSOTPInstrumentIDType	InstrumentID1;
	///合约代码2
	TKSOTPInstrumentIDType	InstrumentID2;
	///合约代码3
	TKSOTPInstrumentIDType	InstrumentID3;
	///合约代码4
	TKSOTPInstrumentIDType	InstrumentID4;
	///投保标记
	TKSOTPHedgeFlagType	HedgeFlag;
	///买卖方向1
	TKSOTPDirectionType	Direction1;
	///买卖方向2
	TKSOTPDirectionType	Direction2;
	///买卖方向3
	TKSOTPDirectionType	Direction3;
	///买卖方向4
	TKSOTPDirectionType	Direction4;
	///强拆标记
	TKSOTPCombActionType	 CombActionFlag;
	///组合拆分标记
	TKSOTPCombDirectionType	CombDirection;
	///组合编号
	TKSOTPTradeIDType	ComTradeID;
};

///个股可组合可拆分手数
struct CKSOTPCombActionVolumeField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///最大可组合数量
	TKSOTPVolumeType	MaxCombVolume;
	///最大可拆分数量
	TKSOTPVolumeType	MaxActionVolume;
};

///客户每日出金额度申请请求
struct CKSOTPInputFundOutCreditApplyField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///当日出金额度
	TKSOTPMoneyType	FundOutCredit;
	///当日出金额度操作类型
	TKSOTPFOCreditApplyType	CreditApplyFlag;
	///流水号
	TKSOTPTradeSerialNoType	CreditSerial;
};

///客户每日出金额度查询请求
struct CKSOTPQryFundOutCreditField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
};

///客户每日出金额度查询
struct CKSOTPRspQryFundOutCreditField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///当日出金额度
	TKSOTPMoneyType	FundOutCredit;
	///当日已出金额度
	TKSOTPMoneyType	FundOutedCredit;
	///最后更新日期
	TKSOTPDateType	UpdateDate;
	///设置日期
	TKSOTPDateType	SetDate;
	///设置时间
	TKSOTPTimeType	SetTime;
};

///客户每日出金额度申请查询请求
struct CKSOTPQryFundOutCreditApplyField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///查询开始日期
	TKSOTPDateType	QryCreditStart;
	///查询结束日期
	TKSOTPDateType	QryCreditEnd;
	///当日出金额度处理状态
	TKSOTPFOCreditStatusType	DealStatus;
};

///客户每日出金额度申请查询
struct CKSOTPRspQryFundOutCreditApplyField
{
	///经纪公司代码
	TKSOTPBrokerIDType	BrokerID;
	///投资者代码
	TKSOTPInvestorIDType	InvestorID;
	///流水号
	TKSOTPTradeSerialNoType	CreditSerial;
	///申请出金额度
	TKSOTPMoneyType	FundOutCredit;
	///当日出金额度处理状态
	TKSOTPFOCreditStatusType	DealStatus;
	///申请日期
	TKSOTPDateType	ApplyDate;
	///申请时间
	TKSOTPTimeType	ApplyTime;
	///审核日期
	TKSOTPDateType	ConfirmDate;
	///审核时间
	TKSOTPTimeType	ConfirmTime;
};
}// end of namespace KingstarAPI

#endif
