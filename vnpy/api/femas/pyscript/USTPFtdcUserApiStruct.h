/////////////////////////////////////////////////////////////////////////
///@system 风控前置系统
///@company CFFEX
///@file USTPFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_USTP_FTDCSTRUCT_H)
#define _USTP_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "USTPFtdcUserApiDataType.h"

///系统用户登录请求
struct CUstpFtdcReqUserLoginField
{
	///交易日
	TUstpFtdcDateType	TradingDay;
	///交易用户代码
	TUstpFtdcUserIDType	UserID;
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///密码
	TUstpFtdcPasswordType	Password;
	///用户端产品信息
	TUstpFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TUstpFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TUstpFtdcProtocolInfoType	ProtocolInfo;
	///IP地址
	TUstpFtdcIPAddressType	IPAddress;
	///Mac地址
	TUstpFtdcMacAddressType	MacAddress;
	///数据中心代码
	TUstpFtdcDataCenterIDType	DataCenterID;
};
///系统用户登录应答
struct CUstpFtdcRspUserLoginField
{
	///交易日
	TUstpFtdcDateType	TradingDay;
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TUstpFtdcUserIDType	UserID;
	///登录成功时间
	TUstpFtdcTimeType	LoginTime;
	///用户最大本地报单号
	TUstpFtdcUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	TUstpFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TUstpFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TUstpFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TUstpFtdcSequenceNoType	UserFlowSize;
};
///用户登出请求
struct CUstpFtdcReqUserLogoutField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TUstpFtdcUserIDType	UserID;
};
///用户登出请求
struct CUstpFtdcRspUserLogoutField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TUstpFtdcUserIDType	UserID;
};
///强制用户退出
struct CUstpFtdcForceUserExitField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TUstpFtdcUserIDType	UserID;
};
///用户口令修改
struct CUstpFtdcUserPasswordUpdateField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TUstpFtdcUserIDType	UserID;
	///旧密码
	TUstpFtdcPasswordType	OldPassword;
	///新密码
	TUstpFtdcPasswordType	NewPassword;
};
///输入报单
struct CUstpFtdcInputOrderField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TUstpFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TUstpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TUstpFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TUstpFtdcDirectionType	Direction;
	///开平标志
	TUstpFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TUstpFtdcHedgeFlagType	HedgeFlag;
	///价格
	TUstpFtdcPriceType	LimitPrice;
	///数量
	TUstpFtdcVolumeType	Volume;
	///有效期类型
	TUstpFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TUstpFtdcDateType	GTDDate;
	///成交量类型
	TUstpFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TUstpFtdcVolumeType	MinVolume;
	///止损价
	TUstpFtdcPriceType	StopPrice;
	///强平原因
	TUstpFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TUstpFtdcBoolType	IsAutoSuspend;
	///业务单元
	TUstpFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TUstpFtdcCustomType	UserCustom;
};
///报单操作
struct CUstpFtdcOrderActionField
{
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///报单编号
	TUstpFtdcOrderSysIDType	OrderSysID;
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///本次撤单操作的本地编号
	TUstpFtdcUserOrderLocalIDType	UserOrderActionLocalID;
	///被撤订单的本地报单编号
	TUstpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单操作标志
	TUstpFtdcActionFlagType	ActionFlag;
	///价格
	TUstpFtdcPriceType	LimitPrice;
	///数量变化
	TUstpFtdcVolumeType	VolumeChange;
};
///内存表导出
struct CUstpFtdcMemDbField
{
	///内存表名
	TUstpFtdcMemTableNameType	MemTableName;
};
///响应信息
struct CUstpFtdcRspInfoField
{
	///错误代码
	TUstpFtdcErrorIDType	ErrorID;
	///错误信息
	TUstpFtdcErrorMsgType	ErrorMsg;
};
///报单查询
struct CUstpFtdcQryOrderField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///报单编号
	TUstpFtdcOrderSysIDType	OrderSysID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
};
///成交查询
struct CUstpFtdcQryTradeField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///成交编号
	TUstpFtdcTradeIDType	TradeID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
};
///合约查询
struct CUstpFtdcQryInstrumentField
{
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///产品代码
	TUstpFtdcProductIDType	ProductID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
};
///合约查询应答
struct CUstpFtdcRspInstrumentField
{
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///品种代码
	TUstpFtdcProductIDType	ProductID;
	///品种名称
	TUstpFtdcProductNameType	ProductName;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TUstpFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TUstpFtdcYearType	DeliveryYear;
	///交割月
	TUstpFtdcMonthType	DeliveryMonth;
	///限价单最大下单量
	TUstpFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TUstpFtdcVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TUstpFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TUstpFtdcVolumeType	MinMarketOrderVolume;
	///数量乘数
	TUstpFtdcVolumeMultipleType	VolumeMultiple;
	///报价单位
	TUstpFtdcPriceTickType	PriceTick;
	///币种
	TUstpFtdcCurrencyType	Currency;
	///多头限仓
	TUstpFtdcVolumeType	LongPosLimit;
	///空头限仓
	TUstpFtdcVolumeType	ShortPosLimit;
	///跌停板价
	TUstpFtdcPriceType	LowerLimitPrice;
	///涨停板价
	TUstpFtdcPriceType	UpperLimitPrice;
	///昨结算
	TUstpFtdcPriceType	PreSettlementPrice;
	///合约交易状态
	TUstpFtdcInstrumentStatusType	InstrumentStatus;
	///创建日
	TUstpFtdcDateType	CreateDate;
	///上市日
	TUstpFtdcDateType	OpenDate;
	///到期日
	TUstpFtdcDateType	ExpireDate;
	///开始交割日
	TUstpFtdcDateType	StartDelivDate;
	///最后交割日
	TUstpFtdcDateType	EndDelivDate;
	///挂牌基准价
	TUstpFtdcPriceType	BasisPrice;
	///当前是否交易
	TUstpFtdcBoolType	IsTrading;
	///基础商品代码
	TUstpFtdcInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TUstpFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TUstpFtdcPositionTypeType	PositionType;
	///执行价
	TUstpFtdcPriceType	StrikePrice;
	///期权类型
	TUstpFtdcOptionsTypeType	OptionsType;
};
///合约状态
struct CUstpFtdcInstrumentStatusField
{
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///品种代码
	TUstpFtdcProductIDType	ProductID;
	///品种名称
	TUstpFtdcProductNameType	ProductName;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TUstpFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TUstpFtdcYearType	DeliveryYear;
	///交割月
	TUstpFtdcMonthType	DeliveryMonth;
	///限价单最大下单量
	TUstpFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TUstpFtdcVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TUstpFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TUstpFtdcVolumeType	MinMarketOrderVolume;
	///数量乘数
	TUstpFtdcVolumeMultipleType	VolumeMultiple;
	///报价单位
	TUstpFtdcPriceTickType	PriceTick;
	///币种
	TUstpFtdcCurrencyType	Currency;
	///多头限仓
	TUstpFtdcVolumeType	LongPosLimit;
	///空头限仓
	TUstpFtdcVolumeType	ShortPosLimit;
	///跌停板价
	TUstpFtdcPriceType	LowerLimitPrice;
	///涨停板价
	TUstpFtdcPriceType	UpperLimitPrice;
	///昨结算
	TUstpFtdcPriceType	PreSettlementPrice;
	///合约交易状态
	TUstpFtdcInstrumentStatusType	InstrumentStatus;
	///创建日
	TUstpFtdcDateType	CreateDate;
	///上市日
	TUstpFtdcDateType	OpenDate;
	///到期日
	TUstpFtdcDateType	ExpireDate;
	///开始交割日
	TUstpFtdcDateType	StartDelivDate;
	///最后交割日
	TUstpFtdcDateType	EndDelivDate;
	///挂牌基准价
	TUstpFtdcPriceType	BasisPrice;
	///当前是否交易
	TUstpFtdcBoolType	IsTrading;
	///基础商品代码
	TUstpFtdcInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TUstpFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TUstpFtdcPositionTypeType	PositionType;
	///执行价
	TUstpFtdcPriceType	StrikePrice;
	///期权类型
	TUstpFtdcOptionsTypeType	OptionsType;
};
///投资者资金查询
struct CUstpFtdcQryInvestorAccountField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
};
///投资者资金应答
struct CUstpFtdcRspInvestorAccountField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///资金帐号
	TUstpFtdcAccountIDType	AccountID;
	///上次结算准备金
	TUstpFtdcMoneyType	PreBalance;
	///入金金额
	TUstpFtdcMoneyType	Deposit;
	///出金金额
	TUstpFtdcMoneyType	Withdraw;
	///冻结的保证金
	TUstpFtdcMoneyType	FrozenMargin;
	///冻结手续费
	TUstpFtdcMoneyType	FrozenFee;
	///冻结权利金
	TUstpFtdcMoneyType	FrozenPremium;
	///手续费
	TUstpFtdcMoneyType	Fee;
	///平仓盈亏
	TUstpFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TUstpFtdcMoneyType	PositionProfit;
	///可用资金
	TUstpFtdcMoneyType	Available;
	///多头冻结的保证金
	TUstpFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TUstpFtdcMoneyType	ShortFrozenMargin;
	///多头占用保证金
	TUstpFtdcMoneyType	LongMargin;
	///空头占用保证金
	TUstpFtdcMoneyType	ShortMargin;
	///当日释放保证金
	TUstpFtdcMoneyType	ReleaseMargin;
	///动态权益
	TUstpFtdcMoneyType	DynamicRights;
	///今日出入金
	TUstpFtdcMoneyType	TodayInOut;
	///占用保证金
	TUstpFtdcMoneyType	Margin;
	///期权权利金收支
	TUstpFtdcMoneyType	Premium;
	///风险度
	TUstpFtdcMoneyType	Risk;
};
///可用投资者查询
struct CUstpFtdcQryUserInvestorField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
};
///可用投资者
struct CUstpFtdcRspUserInvestorField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TUstpFtdcUserIDType	UserID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
};
///交易编码查询
struct CUstpFtdcQryTradingCodeField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
};
///交易编码查询
struct CUstpFtdcRspTradingCodeField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///客户代码
	TUstpFtdcClientIDType	ClientID;
	///客户代码权限
	TUstpFtdcTradingRightType	ClientRight;
	///是否活跃
	TUstpFtdcIsActiveType	IsActive;
};
///交易所查询请求
struct CUstpFtdcQryExchangeField
{
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
};
///交易所查询应答
struct CUstpFtdcRspExchangeField
{
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///交易所名称
	TUstpFtdcExchangeNameType	ExchangeName;
};
///投资者持仓查询请求
struct CUstpFtdcQryInvestorPositionField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
};
///投资者持仓查询应答
struct CUstpFtdcRspInvestorPositionField
{
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///客户代码
	TUstpFtdcClientIDType	ClientID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TUstpFtdcDirectionType	Direction;
	///投机套保标志
	TUstpFtdcHedgeFlagType	HedgeFlag;
	///占用保证金
	TUstpFtdcMoneyType	UsedMargin;
	///今持仓量
	TUstpFtdcVolumeType	Position;
	///今日持仓成本
	TUstpFtdcPriceType	PositionCost;
	///昨持仓量
	TUstpFtdcVolumeType	YdPosition;
	///昨日持仓成本
	TUstpFtdcMoneyType	YdPositionCost;
	///冻结的保证金
	TUstpFtdcMoneyType	FrozenMargin;
	///开仓冻结持仓
	TUstpFtdcVolumeType	FrozenPosition;
	///平仓冻结持仓
	TUstpFtdcVolumeType	FrozenClosing;
	///冻结的权利金
	TUstpFtdcMoneyType	FrozenPremium;
	///最后一笔成交编号
	TUstpFtdcTradeIDType	LastTradeID;
	///最后一笔本地报单编号
	TUstpFtdcOrderLocalIDType	LastOrderLocalID;
	///币种
	TUstpFtdcCurrencyIDType	Currency;
};
///合规参数查询请求
struct CUstpFtdcQryComplianceParamField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
};
///合规参数查询应答
struct CUstpFtdcRspComplianceParamField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///客户号
	TUstpFtdcClientIDType	ClientID;
	///每日最大报单笔
	TUstpFtdcVolumeType	DailyMaxOrder;
	///每日最大撤单笔
	TUstpFtdcVolumeType	DailyMaxOrderAction;
	///每日最大错单笔
	TUstpFtdcVolumeType	DailyMaxErrorOrder;
	///每日最大报单手
	TUstpFtdcVolumeType	DailyMaxOrderVolume;
	///每日最大撤单手
	TUstpFtdcVolumeType	DailyMaxOrderActionVolume;
};
///用户查询
struct CUstpFtdcQryUserField
{
	///交易用户代码
	TUstpFtdcUserIDType	StartUserID;
	///交易用户代码
	TUstpFtdcUserIDType	EndUserID;
};
///用户
struct CUstpFtdcUserField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///用户登录密码
	TUstpFtdcPasswordType	Password;
	///是否活跃
	TUstpFtdcIsActiveType	IsActive;
	///用户名称
	TUstpFtdcUserNameType	UserName;
	///用户类型
	TUstpFtdcUserTypeType	UserType;
	///营业部
	TUstpFtdcDepartmentType	Department;
	///授权功能集
	TUstpFtdcGrantFuncSetType	GrantFuncSet;
	///修改用户编号
	TUstpFtdcUserIDType	SetUserID;
	///操作日期
	TUstpFtdcDateType	CommandDate;
	///操作时间
	TUstpFtdcTimeType	CommandTime;
};
///投资者手续费率查询
struct CUstpFtdcQryInvestorFeeField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
};
///投资者手续费率
struct CUstpFtdcInvestorFeeField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///客户号
	TUstpFtdcClientIDType	ClientID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TUstpFtdcProductIDType	ProductID;
	///开仓手续费按比例
	TUstpFtdcRatioType	OpenFeeRate;
	///开仓手续费按手数
	TUstpFtdcRatioType	OpenFeeAmt;
	///平仓手续费按比例
	TUstpFtdcRatioType	OffsetFeeRate;
	///平仓手续费按手数
	TUstpFtdcRatioType	OffsetFeeAmt;
	///平今仓手续费按比例
	TUstpFtdcRatioType	OTFeeRate;
	///平今仓手续费按手数
	TUstpFtdcRatioType	OTFeeAmt;
};
///投资者保证金率查询
struct CUstpFtdcQryInvestorMarginField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
};
///投资者保证金率
struct CUstpFtdcInvestorMarginField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///客户号
	TUstpFtdcClientIDType	ClientID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///品种代码
	TUstpFtdcProductIDType	ProductID;
	///多头占用保证金按比例
	TUstpFtdcRatioType	LongMarginRate;
	///多头保证金按手数
	TUstpFtdcRatioType	LongMarginAmt;
	///空头占用保证金按比例
	TUstpFtdcRatioType	ShortMarginRate;
	///空头保证金按手数
	TUstpFtdcRatioType	ShortMarginAmt;
};
///成交
struct CUstpFtdcTradeField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///交易日
	TUstpFtdcTradingDayType	TradingDay;
	///会员编号
	TUstpFtdcParticipantIDType	ParticipantID;
	///下单席位号
	TUstpFtdcSeatIDType	SeatID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///客户号
	TUstpFtdcClientIDType	ClientID;
	///用户编号
	TUstpFtdcUserIDType	UserID;
	///成交编号
	TUstpFtdcTradeIDType	TradeID;
	///报单编号
	TUstpFtdcOrderSysIDType	OrderSysID;
	///本地报单编号
	TUstpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TUstpFtdcDirectionType	Direction;
	///开平标志
	TUstpFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TUstpFtdcHedgeFlagType	HedgeFlag;
	///成交价格
	TUstpFtdcPriceType	TradePrice;
	///成交数量
	TUstpFtdcVolumeType	TradeVolume;
	///成交时间
	TUstpFtdcTimeType	TradeTime;
	///清算会员编号
	TUstpFtdcParticipantIDType	ClearingPartID;
};
///报单
struct CUstpFtdcOrderField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TUstpFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TUstpFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TUstpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TUstpFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TUstpFtdcDirectionType	Direction;
	///开平标志
	TUstpFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TUstpFtdcHedgeFlagType	HedgeFlag;
	///价格
	TUstpFtdcPriceType	LimitPrice;
	///数量
	TUstpFtdcVolumeType	Volume;
	///有效期类型
	TUstpFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TUstpFtdcDateType	GTDDate;
	///成交量类型
	TUstpFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TUstpFtdcVolumeType	MinVolume;
	///止损价
	TUstpFtdcPriceType	StopPrice;
	///强平原因
	TUstpFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TUstpFtdcBoolType	IsAutoSuspend;
	///业务单元
	TUstpFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TUstpFtdcCustomType	UserCustom;
	///交易日
	TUstpFtdcTradingDayType	TradingDay;
	///会员编号
	TUstpFtdcParticipantIDType	ParticipantID;
	///客户号
	TUstpFtdcClientIDType	ClientID;
	///下单席位号
	TUstpFtdcSeatIDType	SeatID;
	///插入时间
	TUstpFtdcTimeType	InsertTime;
	///本地报单编号
	TUstpFtdcOrderLocalIDType	OrderLocalID;
	///报单来源
	TUstpFtdcOrderSourceType	OrderSource;
	///报单状态
	TUstpFtdcOrderStatusType	OrderStatus;
	///撤销时间
	TUstpFtdcTimeType	CancelTime;
	///撤单用户编号
	TUstpFtdcUserIDType	CancelUserID;
	///今成交数量
	TUstpFtdcVolumeType	VolumeTraded;
	///剩余数量
	TUstpFtdcVolumeType	VolumeRemain;
};
///数据流回退
struct CUstpFtdcFlowMessageCancelField
{
	///序列系列号
	TUstpFtdcSequenceSeriesType	SequenceSeries;
	///交易日
	TUstpFtdcDateType	TradingDay;
	///数据中心代码
	TUstpFtdcDataCenterIDType	DataCenterID;
	///回退起始序列号
	TUstpFtdcSequenceNoType	StartSequenceNo;
	///回退结束序列号
	TUstpFtdcSequenceNoType	EndSequenceNo;
};
///信息分发
struct CUstpFtdcDisseminationField
{
	///序列系列号
	TUstpFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TUstpFtdcSequenceNoType	SequenceNo;
};
///出入金结果
struct CUstpFtdcInvestorAccountDepositResField
{
	///经纪公司编号
	TUstpFtdcBrokerIDType	BrokerID;
	///用户代码
	TUstpFtdcUserIDType	UserID;
	///投资者编号
	TUstpFtdcInvestorIDType	InvestorID;
	///资金帐号
	TUstpFtdcAccountIDType	AccountID;
	///资金流水号
	TUstpFtdcAccountSeqNoType	AccountSeqNo;
	///金额
	TUstpFtdcMoneyType	Amount;
	///出入金方向
	TUstpFtdcAccountDirectionType	AmountDirection;
	///可用资金
	TUstpFtdcMoneyType	Available;
	///结算准备金
	TUstpFtdcMoneyType	Balance;
};
///行情基础属性
struct CUstpFtdcMarketDataBaseField
{
	///交易日
	TUstpFtdcDateType	TradingDay;
	///结算组代码
	TUstpFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TUstpFtdcSettlementIDType	SettlementID;
	///昨结算
	TUstpFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TUstpFtdcPriceType	PreClosePrice;
	///昨持仓量
	TUstpFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TUstpFtdcRatioType	PreDelta;
};
///行情静态属性
struct CUstpFtdcMarketDataStaticField
{
	///今开盘
	TUstpFtdcPriceType	OpenPrice;
	///最高价
	TUstpFtdcPriceType	HighestPrice;
	///最低价
	TUstpFtdcPriceType	LowestPrice;
	///今收盘
	TUstpFtdcPriceType	ClosePrice;
	///涨停板价
	TUstpFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TUstpFtdcPriceType	LowerLimitPrice;
	///今结算
	TUstpFtdcPriceType	SettlementPrice;
	///今虚实度
	TUstpFtdcRatioType	CurrDelta;
};
///行情最新成交属性
struct CUstpFtdcMarketDataLastMatchField
{
	///最新价
	TUstpFtdcPriceType	LastPrice;
	///数量
	TUstpFtdcVolumeType	Volume;
	///成交金额
	TUstpFtdcMoneyType	Turnover;
	///持仓量
	TUstpFtdcLargeVolumeType	OpenInterest;
};
///行情最优价属性
struct CUstpFtdcMarketDataBestPriceField
{
	///申买价一
	TUstpFtdcPriceType	BidPrice1;
	///申买量一
	TUstpFtdcVolumeType	BidVolume1;
	///申卖价一
	TUstpFtdcPriceType	AskPrice1;
	///申卖量一
	TUstpFtdcVolumeType	AskVolume1;
};
///行情申买二、三属性
struct CUstpFtdcMarketDataBid23Field
{
	///申买价二
	TUstpFtdcPriceType	BidPrice2;
	///申买量二
	TUstpFtdcVolumeType	BidVolume2;
	///申买价三
	TUstpFtdcPriceType	BidPrice3;
	///申买量三
	TUstpFtdcVolumeType	BidVolume3;
};
///行情申卖二、三属性
struct CUstpFtdcMarketDataAsk23Field
{
	///申卖价二
	TUstpFtdcPriceType	AskPrice2;
	///申卖量二
	TUstpFtdcVolumeType	AskVolume2;
	///申卖价三
	TUstpFtdcPriceType	AskPrice3;
	///申卖量三
	TUstpFtdcVolumeType	AskVolume3;
};
///行情申买四、五属性
struct CUstpFtdcMarketDataBid45Field
{
	///申买价四
	TUstpFtdcPriceType	BidPrice4;
	///申买量四
	TUstpFtdcVolumeType	BidVolume4;
	///申买价五
	TUstpFtdcPriceType	BidPrice5;
	///申买量五
	TUstpFtdcVolumeType	BidVolume5;
};
///行情申卖四、五属性
struct CUstpFtdcMarketDataAsk45Field
{
	///申卖价四
	TUstpFtdcPriceType	AskPrice4;
	///申卖量四
	TUstpFtdcVolumeType	AskVolume4;
	///申卖价五
	TUstpFtdcPriceType	AskPrice5;
	///申卖量五
	TUstpFtdcVolumeType	AskVolume5;
};
///行情更新时间属性
struct CUstpFtdcMarketDataUpdateTimeField
{
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TUstpFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TUstpFtdcMillisecType	UpdateMillisec;
};
///深度行情
struct CUstpFtdcDepthMarketDataField
{
	///交易日
	TUstpFtdcDateType	TradingDay;
	///结算组代码
	TUstpFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TUstpFtdcSettlementIDType	SettlementID;
	///昨结算
	TUstpFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TUstpFtdcPriceType	PreClosePrice;
	///昨持仓量
	TUstpFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TUstpFtdcRatioType	PreDelta;
	///今开盘
	TUstpFtdcPriceType	OpenPrice;
	///最高价
	TUstpFtdcPriceType	HighestPrice;
	///最低价
	TUstpFtdcPriceType	LowestPrice;
	///今收盘
	TUstpFtdcPriceType	ClosePrice;
	///涨停板价
	TUstpFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TUstpFtdcPriceType	LowerLimitPrice;
	///今结算
	TUstpFtdcPriceType	SettlementPrice;
	///今虚实度
	TUstpFtdcRatioType	CurrDelta;
	///最新价
	TUstpFtdcPriceType	LastPrice;
	///数量
	TUstpFtdcVolumeType	Volume;
	///成交金额
	TUstpFtdcMoneyType	Turnover;
	///持仓量
	TUstpFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TUstpFtdcPriceType	BidPrice1;
	///申买量一
	TUstpFtdcVolumeType	BidVolume1;
	///申卖价一
	TUstpFtdcPriceType	AskPrice1;
	///申卖量一
	TUstpFtdcVolumeType	AskVolume1;
	///申买价二
	TUstpFtdcPriceType	BidPrice2;
	///申买量二
	TUstpFtdcVolumeType	BidVolume2;
	///申买价三
	TUstpFtdcPriceType	BidPrice3;
	///申买量三
	TUstpFtdcVolumeType	BidVolume3;
	///申卖价二
	TUstpFtdcPriceType	AskPrice2;
	///申卖量二
	TUstpFtdcVolumeType	AskVolume2;
	///申卖价三
	TUstpFtdcPriceType	AskPrice3;
	///申卖量三
	TUstpFtdcVolumeType	AskVolume3;
	///申买价四
	TUstpFtdcPriceType	BidPrice4;
	///申买量四
	TUstpFtdcVolumeType	BidVolume4;
	///申买价五
	TUstpFtdcPriceType	BidPrice5;
	///申买量五
	TUstpFtdcVolumeType	BidVolume5;
	///申卖价四
	TUstpFtdcPriceType	AskPrice4;
	///申卖量四
	TUstpFtdcVolumeType	AskVolume4;
	///申卖价五
	TUstpFtdcPriceType	AskPrice5;
	///申卖量五
	TUstpFtdcVolumeType	AskVolume5;
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TUstpFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TUstpFtdcMillisecType	UpdateMillisec;
};
///订阅合约的相关信息
struct CUstpFtdcSpecificInstrumentField
{
	///合约代码
	TUstpFtdcInstrumentIDType	InstrumentID;
};


#endif
