/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

#if !defined(Sgit_FTDCSTRUCT_H)
#define Sgit_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SgitFtdcUserApiDataType.h"

///信息分发
struct CSgitFtdcDisseminationField
{
	///序列系列号
	TSgitFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TSgitFtdcSequenceNoType	SequenceNo;
};

///用户登录请求
struct CSgitFtdcReqUserLoginField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///密码
	TSgitFtdcPasswordType	Password;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TSgitFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TSgitFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TSgitFtdcMacAddressType	MacAddress;
	///动态密码
	TSgitFtdcPasswordType	OneTimePassword;
	///终端IP地址
	TSgitFtdcIPAddressType	ClientIPAddress;
};

///用户登录应答
struct CSgitFtdcRspUserLoginField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///登录成功时间
	TSgitFtdcTimeType	LoginTime;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///交易系统名称
	TSgitFtdcSystemNameType	SystemName;
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///最大报单引用
	TSgitFtdcOrderRefType	MaxOrderRef;
	///上期所时间
	TSgitFtdcTimeType	SHFETime;
	///大商所时间
	TSgitFtdcTimeType	DCETime;
	///郑商所时间
	TSgitFtdcTimeType	CZCETime;
	///中金所时间
	TSgitFtdcTimeType	FFEXTime;
};

///用户登出请求
struct CSgitFtdcUserLogoutField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///强制交易员退出
struct CSgitFtdcForceUserLogoutField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///客户端认证请求
struct CSgitFtdcReqAuthenticateField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
	///认证码
	TSgitFtdcAuthCodeType	AuthCode;
};

///客户端认证响应
struct CSgitFtdcRspAuthenticateField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
};

///客户端认证信息
struct CSgitFtdcAuthenticationInfoField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
	///认证信息
	TSgitFtdcAuthInfoType	AuthInfo;
	///是否为认证结果
	TSgitFtdcBoolType	IsResult;
};

///银期转帐报文头
struct CSgitFtdcTransferHeaderField
{
	///版本号，常量，1.0
	TSgitFtdcVersionType	Version;
	///交易代码，必填
	TSgitFtdcTradeCodeType	TradeCode;
	///交易日期，必填，格式：yyyymmdd
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间，必填，格式：hhmmss
	TSgitFtdcTradeTimeType	TradeTime;
	///发起方流水号，N/A
	TSgitFtdcTradeSerialType	TradeSerial;
	///期货公司代码，必填
	TSgitFtdcFutureIDType	FutureID;
	///银行代码，根据查询银行得到，必填
	TSgitFtdcBankIDType	BankID;
	///银行分中心代码，根据查询银行得到，必填
	TSgitFtdcBankBrchIDType	BankBrchID;
	///操作员，N/A
	TSgitFtdcOperNoType	OperNo;
	///交易设备类型，N/A
	TSgitFtdcDeviceIDType	DeviceID;
	///记录数，N/A
	TSgitFtdcRecordNumType	RecordNum;
	///会话编号，N/A
	TSgitFtdcSessionIDType	SessionID;
	///请求编号，N/A
	TSgitFtdcRequestIDType	RequestID;
};

///银行资金转期货请求，TradeCode=202001
struct CSgitFtdcTransferBankToFutureReqField
{
	///期货资金账户
	TSgitFtdcAccountIDType	FutureAccount;
	///密码标志
	TSgitFtdcFuturePwdFlagType	FuturePwdFlag;
	///密码
	TSgitFtdcFutureAccPwdType	FutureAccPwd;
	///转账金额
	TSgitFtdcMoneyType	TradeAmt;
	///客户手续费
	TSgitFtdcMoneyType	CustFee;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	TSgitFtdcCurrencyCodeType	CurrencyCode;
};

///银行资金转期货请求响应
struct CSgitFtdcTransferBankToFutureRspField
{
	///响应代码
	TSgitFtdcRetCodeType	RetCode;
	///响应信息
	TSgitFtdcRetInfoType	RetInfo;
	///资金账户
	TSgitFtdcAccountIDType	FutureAccount;
	///转帐金额
	TSgitFtdcMoneyType	TradeAmt;
	///应收客户手续费
	TSgitFtdcMoneyType	CustFee;
	///币种
	TSgitFtdcCurrencyCodeType	CurrencyCode;
};

///期货资金转银行请求，TradeCode=202002
struct CSgitFtdcTransferFutureToBankReqField
{
	///期货资金账户
	TSgitFtdcAccountIDType	FutureAccount;
	///密码标志
	TSgitFtdcFuturePwdFlagType	FuturePwdFlag;
	///密码
	TSgitFtdcFutureAccPwdType	FutureAccPwd;
	///转账金额
	TSgitFtdcMoneyType	TradeAmt;
	///客户手续费
	TSgitFtdcMoneyType	CustFee;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	TSgitFtdcCurrencyCodeType	CurrencyCode;
};

///期货资金转银行请求响应
struct CSgitFtdcTransferFutureToBankRspField
{
	///响应代码
	TSgitFtdcRetCodeType	RetCode;
	///响应信息
	TSgitFtdcRetInfoType	RetInfo;
	///资金账户
	TSgitFtdcAccountIDType	FutureAccount;
	///转帐金额
	TSgitFtdcMoneyType	TradeAmt;
	///应收客户手续费
	TSgitFtdcMoneyType	CustFee;
	///币种
	TSgitFtdcCurrencyCodeType	CurrencyCode;
};

///查询银行资金请求，TradeCode=204002
struct CSgitFtdcTransferQryBankReqField
{
	///期货资金账户
	TSgitFtdcAccountIDType	FutureAccount;
	///密码标志
	TSgitFtdcFuturePwdFlagType	FuturePwdFlag;
	///密码
	TSgitFtdcFutureAccPwdType	FutureAccPwd;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	TSgitFtdcCurrencyCodeType	CurrencyCode;
};

///查询银行资金请求响应
struct CSgitFtdcTransferQryBankRspField
{
	///响应代码
	TSgitFtdcRetCodeType	RetCode;
	///响应信息
	TSgitFtdcRetInfoType	RetInfo;
	///资金账户
	TSgitFtdcAccountIDType	FutureAccount;
	///银行余额
	TSgitFtdcMoneyType	TradeAmt;
	///银行可用余额
	TSgitFtdcMoneyType	UseAmt;
	///银行可取余额
	TSgitFtdcMoneyType	FetchAmt;
	///币种
	TSgitFtdcCurrencyCodeType	CurrencyCode;
};

///查询银行交易明细请求，TradeCode=204999
struct CSgitFtdcTransferQryDetailReqField
{
	///期货资金账户
	TSgitFtdcAccountIDType	FutureAccount;
};

///查询银行交易明细请求响应
struct CSgitFtdcTransferQryDetailRspField
{
	///交易日期
	TSgitFtdcDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///交易代码
	TSgitFtdcTradeCodeType	TradeCode;
	///期货流水号
	TSgitFtdcTradeSerialNoType	FutureSerial;
	///期货公司代码
	TSgitFtdcFutureIDType	FutureID;
	///资金帐号
	TSgitFtdcFutureAccountType	FutureAccount;
	///银行流水号
	TSgitFtdcTradeSerialNoType	BankSerial;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分中心代码
	TSgitFtdcBankBrchIDType	BankBrchID;
	///银行账号
	TSgitFtdcBankAccountType	BankAccount;
	///证件号码
	TSgitFtdcCertCodeType	CertCode;
	///货币代码
	TSgitFtdcCurrencyCodeType	CurrencyCode;
	///发生金额
	TSgitFtdcMoneyType	TxAmount;
	///有效标志
	TSgitFtdcTransferValidFlagType	Flag;
};

///响应信息
struct CSgitFtdcRspInfoField
{
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///交易所
struct CSgitFtdcExchangeField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///交易所名称
	TSgitFtdcExchangeNameType	ExchangeName;
	///交易所属性
	TSgitFtdcExchangePropertyType	ExchangeProperty;
};

///产品
struct CSgitFtdcProductField
{
	///产品代码
	TSgitFtdcInstrumentIDType	ProductID;
	///产品名称
	TSgitFtdcProductNameType	ProductName;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///产品类型
	TSgitFtdcProductClassType	ProductClass;
	///合约数量乘数
	TSgitFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TSgitFtdcPriceType	PriceTick;
	///市价单最大下单量
	TSgitFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TSgitFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TSgitFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TSgitFtdcVolumeType	MinLimitOrderVolume;
	///持仓类型
	TSgitFtdcPositionTypeType	PositionType;
	///持仓日期类型
	TSgitFtdcPositionDateTypeType	PositionDateType;
};

///合约
struct CSgitFtdcInstrumentField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约名称
	TSgitFtdcInstrumentNameType	InstrumentName;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///产品代码
	TSgitFtdcInstrumentIDType	ProductID;
	///产品类型
	TSgitFtdcProductClassType	ProductClass;
	///交割年份
	TSgitFtdcYearType	DeliveryYear;
	///交割月
	TSgitFtdcMonthType	DeliveryMonth;
	///市价单最大下单量
	TSgitFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TSgitFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TSgitFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TSgitFtdcVolumeType	MinLimitOrderVolume;
	///合约数量乘数
	TSgitFtdcVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TSgitFtdcPriceType	PriceTick;
	///创建日
	TSgitFtdcDateType	CreateDate;
	///上市日
	TSgitFtdcDateType	OpenDate;
	///到期日
	TSgitFtdcDateType	ExpireDate;
	///开始交割日
	TSgitFtdcDateType	StartDelivDate;
	///结束交割日
	TSgitFtdcDateType	EndDelivDate;
	///合约生命周期状态
	TSgitFtdcInstLifePhaseType	InstLifePhase;
	///当前是否交易
	TSgitFtdcBoolType	IsTrading;
	///持仓类型
	TSgitFtdcPositionTypeType	PositionType;
	///持仓日期类型
	TSgitFtdcPositionDateTypeType	PositionDateType;
	///多头保证金率
	TSgitFtdcRatioType	LongMarginRatio;
	///空头保证金率
	TSgitFtdcRatioType	ShortMarginRatio;
};

///经纪公司
struct CSgitFtdcBrokerField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///经纪公司简称
	TSgitFtdcBrokerAbbrType	BrokerAbbr;
	///经纪公司名称
	TSgitFtdcBrokerNameType	BrokerName;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
};

///交易所交易员
struct CSgitFtdcTraderField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///密码
	TSgitFtdcPasswordType	Password;
	///安装数量
	TSgitFtdcInstallCountType	InstallCount;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
};

///投资者
struct CSgitFtdcInvestorField
{
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TSgitFtdcInvestorIDType	InvestorGroupID;
	///投资者名称
	TSgitFtdcPartyNameType	InvestorName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
	///联系电话
	TSgitFtdcTelephoneType	Telephone;
	///通讯地址
	TSgitFtdcAddressType	Address;
	///开户日期
	TSgitFtdcDateType	OpenDate;
	///手机
	TSgitFtdcMobileType	Mobile;
	///手续费率模板代码
	TSgitFtdcInvestorIDType	CommModelID;
};

///交易编码
struct CSgitFtdcTradingCodeField
{
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
	///交易编码类型
	TSgitFtdcClientIDTypeType	ClientIDType;
};

///会员编码和经纪公司编码对照表
struct CSgitFtdcPartBrokerField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
};

///管理用户
struct CSgitFtdcSuperUserField
{
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///用户名称
	TSgitFtdcUserNameType	UserName;
	///密码
	TSgitFtdcPasswordType	Password;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
};

///管理用户功能权限
struct CSgitFtdcSuperUserFunctionField
{
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///功能代码
	TSgitFtdcFunctionCodeType	FunctionCode;
};

///投资者组
struct CSgitFtdcInvestorGroupField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TSgitFtdcInvestorIDType	InvestorGroupID;
	///投资者分组名称
	TSgitFtdcInvestorGroupNameType	InvestorGroupName;
};

///资金账户
struct CSgitFtdcTradingAccountField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///上次质押金额
	TSgitFtdcMoneyType	PreMortgage;
	///上次信用额度
	TSgitFtdcMoneyType	PreCredit;
	///上次存款额
	TSgitFtdcMoneyType	PreDeposit;
	///上次结算准备金
	TSgitFtdcMoneyType	PreBalance;
	///上次占用的保证金
	TSgitFtdcMoneyType	PreMargin;
	///利息基数
	TSgitFtdcMoneyType	InterestBase;
	///利息收入
	TSgitFtdcMoneyType	Interest;
	///入金金额
	TSgitFtdcMoneyType	Deposit;
	///出金金额
	TSgitFtdcMoneyType	Withdraw;
	///冻结的保证金
	TSgitFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TSgitFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TSgitFtdcMoneyType	FrozenCommission;
	///当前保证金总额
	TSgitFtdcMoneyType	CurrMargin;
	///资金差额
	TSgitFtdcMoneyType	CashIn;
	///手续费
	TSgitFtdcMoneyType	Commission;
	///平仓盈亏
	TSgitFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TSgitFtdcMoneyType	PositionProfit;
	///期货结算准备金
	TSgitFtdcMoneyType	Balance;
	///可用资金
	TSgitFtdcMoneyType	Available;
	///可取资金
	TSgitFtdcMoneyType	WithdrawQuota;
	///基本准备金
	TSgitFtdcMoneyType	Reserve;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///信用额度
	TSgitFtdcMoneyType	Credit;
	///质押金额
	TSgitFtdcMoneyType	Mortgage;
	///交易所保证金
	TSgitFtdcMoneyType	ExchangeMargin;
	///投资者交割保证金
	TSgitFtdcMoneyType	DeliveryMargin;
	///交易所交割保证金
	TSgitFtdcMoneyType	ExchangeDeliveryMargin;
};

///投资者持仓
struct CSgitFtdcInvestorPositionField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///持仓多空方向
	TSgitFtdcPosiDirectionType	PosiDirection;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///持仓日期
	TSgitFtdcPositionDateType	PositionDate;
	///上日持仓
	TSgitFtdcVolumeType	YdPosition;
	///今日持仓
	TSgitFtdcVolumeType	Position;
	///多头冻结
	TSgitFtdcVolumeType	LongFrozen;
	///空头冻结
	TSgitFtdcVolumeType	ShortFrozen;
	///开仓冻结金额
	TSgitFtdcMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TSgitFtdcMoneyType	ShortFrozenAmount;
	///开仓量
	TSgitFtdcVolumeType	OpenVolume;
	///平仓量
	TSgitFtdcVolumeType	CloseVolume;
	///开仓金额
	TSgitFtdcMoneyType	OpenAmount;
	///平仓金额
	TSgitFtdcMoneyType	CloseAmount;
	///持仓成本
	TSgitFtdcMoneyType	PositionCost;
	///上次占用的保证金
	TSgitFtdcMoneyType	PreMargin;
	///占用的保证金
	TSgitFtdcMoneyType	UseMargin;
	///冻结的保证金
	TSgitFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TSgitFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TSgitFtdcMoneyType	FrozenCommission;
	///资金差额
	TSgitFtdcMoneyType	CashIn;
	///手续费
	TSgitFtdcMoneyType	Commission;
	///平仓盈亏
	TSgitFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TSgitFtdcMoneyType	PositionProfit;
	///上次结算价
	TSgitFtdcPriceType	PreSettlementPrice;
	///本次结算价
	TSgitFtdcPriceType	SettlementPrice;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///开仓成本
	TSgitFtdcMoneyType	OpenCost;
	///交易所保证金
	TSgitFtdcMoneyType	ExchangeMargin;
	///组合成交形成的持仓
	TSgitFtdcVolumeType	CombPosition;
	///组合多头冻结
	TSgitFtdcVolumeType	CombLongFrozen;
	///组合空头冻结
	TSgitFtdcVolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	TSgitFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TSgitFtdcMoneyType	CloseProfitByTrade;
	///今日持仓
	TSgitFtdcVolumeType	TodayPosition;
	///保证金率
	TSgitFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TSgitFtdcRatioType	MarginRateByVolume;
};

///合约保证金率
struct CSgitFtdcInstrumentMarginRateField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TSgitFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TSgitFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TSgitFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TSgitFtdcMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TSgitFtdcBoolType	IsRelative;
};

///合约手续费率
struct CSgitFtdcInstrumentCommissionRateField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TSgitFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TSgitFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TSgitFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TSgitFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TSgitFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TSgitFtdcRatioType	CloseTodayRatioByVolume;
};

///深度行情
struct CSgitFtdcDepthMarketDataField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///最新价
	TSgitFtdcPriceType	LastPrice;
	///上次结算价
	TSgitFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TSgitFtdcPriceType	PreClosePrice;
	///昨持仓量
	TSgitFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TSgitFtdcPriceType	OpenPrice;
	///最高价
	TSgitFtdcPriceType	HighestPrice;
	///最低价
	TSgitFtdcPriceType	LowestPrice;
	///数量
	TSgitFtdcVolumeType	Volume;
	///成交金额
	TSgitFtdcMoneyType	Turnover;
	///持仓量
	TSgitFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TSgitFtdcPriceType	ClosePrice;
	///本次结算价
	TSgitFtdcPriceType	SettlementPrice;
	///涨停板价
	TSgitFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TSgitFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TSgitFtdcRatioType	PreDelta;
	///今虚实度
	TSgitFtdcRatioType	CurrDelta;
	///最后修改时间
	TSgitFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TSgitFtdcMillisecType	UpdateMillisec;
	///申买价一
	TSgitFtdcPriceType	BidPrice1;
	///申买量一
	TSgitFtdcVolumeType	BidVolume1;
	///申卖价一
	TSgitFtdcPriceType	AskPrice1;
	///申卖量一
	TSgitFtdcVolumeType	AskVolume1;
	///申买价二
	TSgitFtdcPriceType	BidPrice2;
	///申买量二
	TSgitFtdcVolumeType	BidVolume2;
	///申卖价二
	TSgitFtdcPriceType	AskPrice2;
	///申卖量二
	TSgitFtdcVolumeType	AskVolume2;
	///申买价三
	TSgitFtdcPriceType	BidPrice3;
	///申买量三
	TSgitFtdcVolumeType	BidVolume3;
	///申卖价三
	TSgitFtdcPriceType	AskPrice3;
	///申卖量三
	TSgitFtdcVolumeType	AskVolume3;
	///申买价四
	TSgitFtdcPriceType	BidPrice4;
	///申买量四
	TSgitFtdcVolumeType	BidVolume4;
	///申卖价四
	TSgitFtdcPriceType	AskPrice4;
	///申卖量四
	TSgitFtdcVolumeType	AskVolume4;
	///申买价五
	TSgitFtdcPriceType	BidPrice5;
	///申买量五
	TSgitFtdcVolumeType	BidVolume5;
	///申卖价五
	TSgitFtdcPriceType	AskPrice5;
	///申卖量五
	TSgitFtdcVolumeType	AskVolume5;
	///当日均价
	TSgitFtdcPriceType	AveragePrice;
};

///投资者合约交易权限
struct CSgitFtdcInstrumentTradingRightField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///交易权限
	TSgitFtdcTradingRightType	TradingRight;
};

///经纪公司用户
struct CSgitFtdcBrokerUserField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///用户名称
	TSgitFtdcUserNameType	UserName;
	///用户类型
	TSgitFtdcUserTypeType	UserType;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
	///是否使用令牌
	TSgitFtdcBoolType	IsUsingOTP;
};

///经纪公司用户口令
struct CSgitFtdcBrokerUserPasswordField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///密码
	TSgitFtdcPasswordType	Password;
};

///经纪公司用户功能权限
struct CSgitFtdcBrokerUserFunctionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///经纪公司功能代码
	TSgitFtdcBrokerFunctionCodeType	BrokerFunctionCode;
};

///交易所交易员报盘机
struct CSgitFtdcTraderOfferField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TSgitFtdcTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TSgitFtdcDateType	ConnectRequestDate;
	///发出连接请求的时间
	TSgitFtdcTimeType	ConnectRequestTime;
	///上次报告日期
	TSgitFtdcDateType	LastReportDate;
	///上次报告时间
	TSgitFtdcTimeType	LastReportTime;
	///完成连接日期
	TSgitFtdcDateType	ConnectDate;
	///完成连接时间
	TSgitFtdcTimeType	ConnectTime;
	///启动日期
	TSgitFtdcDateType	StartDate;
	///启动时间
	TSgitFtdcTimeType	StartTime;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///本席位最大成交编号
	TSgitFtdcTradeIDType	MaxTradeID;
	///本席位最大报单备拷
	TSgitFtdcReturnCodeType	MaxOrderMessageReference;
};

///投资者结算结果
struct CSgitFtdcSettlementInfoField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///序号
	TSgitFtdcSequenceNoType	SequenceNo;
	///消息正文
	TSgitFtdcContentType	Content;
};

///合约保证金率调整
struct CSgitFtdcInstrumentMarginRateAdjustField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TSgitFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TSgitFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TSgitFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TSgitFtdcMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TSgitFtdcBoolType	IsRelative;
};

///交易所保证金率
struct CSgitFtdcExchangeMarginRateField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TSgitFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TSgitFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TSgitFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TSgitFtdcMoneyType	ShortMarginRatioByVolume;
};

///交易所保证金率调整
struct CSgitFtdcExchangeMarginRateAdjustField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///跟随交易所投资者多头保证金率
	TSgitFtdcRatioType	LongMarginRatioByMoney;
	///跟随交易所投资者多头保证金费
	TSgitFtdcMoneyType	LongMarginRatioByVolume;
	///跟随交易所投资者空头保证金率
	TSgitFtdcRatioType	ShortMarginRatioByMoney;
	///跟随交易所投资者空头保证金费
	TSgitFtdcMoneyType	ShortMarginRatioByVolume;
	///交易所多头保证金率
	TSgitFtdcRatioType	ExchLongMarginRatioByMoney;
	///交易所多头保证金费
	TSgitFtdcMoneyType	ExchLongMarginRatioByVolume;
	///交易所空头保证金率
	TSgitFtdcRatioType	ExchShortMarginRatioByMoney;
	///交易所空头保证金费
	TSgitFtdcMoneyType	ExchShortMarginRatioByVolume;
	///不跟随交易所投资者多头保证金率
	TSgitFtdcRatioType	NoLongMarginRatioByMoney;
	///不跟随交易所投资者多头保证金费
	TSgitFtdcMoneyType	NoLongMarginRatioByVolume;
	///不跟随交易所投资者空头保证金率
	TSgitFtdcRatioType	NoShortMarginRatioByMoney;
	///不跟随交易所投资者空头保证金费
	TSgitFtdcMoneyType	NoShortMarginRatioByVolume;
};

///结算引用
struct CSgitFtdcSettlementRefField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
};

///当前时间
struct CSgitFtdcCurrentTimeField
{
	///当前日期
	TSgitFtdcDateType	CurrDate;
	///当前时间
	TSgitFtdcTimeType	CurrTime;
	///当前时间（毫秒）
	TSgitFtdcMillisecType	CurrMillisec;
};

///通讯阶段
struct CSgitFtdcCommPhaseField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///通讯时段编号
	TSgitFtdcCommPhaseNoType	CommPhaseNo;
};

///登录信息
struct CSgitFtdcLoginInfoField
{
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///登录日期
	TSgitFtdcDateType	LoginDate;
	///登录时间
	TSgitFtdcTimeType	LoginTime;
	///IP地址
	TSgitFtdcIPAddressType	IPAddress;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TSgitFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TSgitFtdcProtocolInfoType	ProtocolInfo;
	///系统名称
	TSgitFtdcSystemNameType	SystemName;
	///密码
	TSgitFtdcPasswordType	Password;
	///最大报单引用
	TSgitFtdcOrderRefType	MaxOrderRef;
	///上期所时间
	TSgitFtdcTimeType	SHFETime;
	///大商所时间
	TSgitFtdcTimeType	DCETime;
	///郑商所时间
	TSgitFtdcTimeType	CZCETime;
	///中金所时间
	TSgitFtdcTimeType	FFEXTime;
	///Mac地址
	TSgitFtdcMacAddressType	MacAddress;
	///动态密码
	TSgitFtdcPasswordType	OneTimePassword;
};

///登录信息
struct CSgitFtdcLogoutAllField
{
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///系统名称
	TSgitFtdcSystemNameType	SystemName;
};

///前置状态
struct CSgitFtdcFrontStatusField
{
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///上次报告日期
	TSgitFtdcDateType	LastReportDate;
	///上次报告时间
	TSgitFtdcTimeType	LastReportTime;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
};

///用户口令变更
struct CSgitFtdcUserPasswordUpdateField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///原来的口令
	TSgitFtdcPasswordType	OldPassword;
	///新的口令
	TSgitFtdcPasswordType	NewPassword;
};

///输入报单
struct CSgitFtdcInputOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///报单价格条件
	TSgitFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///组合开平标志
	TSgitFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSgitFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量
	TSgitFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSgitFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSgitFtdcDateType	GTDDate;
	///成交量类型
	TSgitFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSgitFtdcVolumeType	MinVolume;
	///触发条件
	TSgitFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSgitFtdcPriceType	StopPrice;
	///强平原因
	TSgitFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSgitFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///用户强评标志
	TSgitFtdcBoolType	UserForceClose;
};

///报单
struct CSgitFtdcOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///报单价格条件
	TSgitFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///组合开平标志
	TSgitFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSgitFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量
	TSgitFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSgitFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSgitFtdcDateType	GTDDate;
	///成交量类型
	TSgitFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSgitFtdcVolumeType	MinVolume;
	///触发条件
	TSgitFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSgitFtdcPriceType	StopPrice;
	///强平原因
	TSgitFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSgitFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///报单提交状态
	TSgitFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TSgitFtdcSequenceNoType	NotifySequence;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TSgitFtdcOrderSourceType	OrderSource;
	///报单状态
	TSgitFtdcOrderStatusType	OrderStatus;
	///报单类型
	TSgitFtdcOrderTypeType	OrderType;
	///今成交数量
	TSgitFtdcVolumeType	VolumeTraded;
	///剩余数量
	TSgitFtdcVolumeType	VolumeTotal;
	///报单日期
	TSgitFtdcDateType	InsertDate;
	///委托时间
	TSgitFtdcTimeType	InsertTime;
	///激活时间
	TSgitFtdcTimeType	ActiveTime;
	///挂起时间
	TSgitFtdcTimeType	SuspendTime;
	///最后修改时间
	TSgitFtdcTimeType	UpdateTime;
	///撤销时间
	TSgitFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TSgitFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TSgitFtdcParticipantIDType	ClearingPartID;
	///序号
	TSgitFtdcSequenceNoType	SequenceNo;
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
	///状态信息
	TSgitFtdcErrorMsgType	StatusMsg;
	///用户强评标志
	TSgitFtdcBoolType	UserForceClose;
	///操作用户代码
	TSgitFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TSgitFtdcSequenceNoType	BrokerOrderSeq;
	///相关报单
	TSgitFtdcOrderSysIDType	RelativeOrderSysID;
};

///交易所报单
struct CSgitFtdcExchangeOrderField
{
	///报单价格条件
	TSgitFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///组合开平标志
	TSgitFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSgitFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量
	TSgitFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSgitFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSgitFtdcDateType	GTDDate;
	///成交量类型
	TSgitFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSgitFtdcVolumeType	MinVolume;
	///触发条件
	TSgitFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSgitFtdcPriceType	StopPrice;
	///强平原因
	TSgitFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSgitFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///报单提交状态
	TSgitFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TSgitFtdcSequenceNoType	NotifySequence;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TSgitFtdcOrderSourceType	OrderSource;
	///报单状态
	TSgitFtdcOrderStatusType	OrderStatus;
	///报单类型
	TSgitFtdcOrderTypeType	OrderType;
	///今成交数量
	TSgitFtdcVolumeType	VolumeTraded;
	///剩余数量
	TSgitFtdcVolumeType	VolumeTotal;
	///报单日期
	TSgitFtdcDateType	InsertDate;
	///委托时间
	TSgitFtdcTimeType	InsertTime;
	///激活时间
	TSgitFtdcTimeType	ActiveTime;
	///挂起时间
	TSgitFtdcTimeType	SuspendTime;
	///最后修改时间
	TSgitFtdcTimeType	UpdateTime;
	///撤销时间
	TSgitFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TSgitFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TSgitFtdcParticipantIDType	ClearingPartID;
	///序号
	TSgitFtdcSequenceNoType	SequenceNo;
};

///交易所报单插入失败
struct CSgitFtdcExchangeOrderInsertErrorField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///输入报单操作
struct CSgitFtdcInputOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TSgitFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TSgitFtdcActionFlagType	ActionFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量变化
	TSgitFtdcVolumeType	VolumeChange;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///报单操作
struct CSgitFtdcOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TSgitFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TSgitFtdcActionFlagType	ActionFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量变化
	TSgitFtdcVolumeType	VolumeChange;
	///操作日期
	TSgitFtdcDateType	ActionDate;
	///操作时间
	TSgitFtdcTimeType	ActionTime;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TSgitFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TSgitFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///状态信息
	TSgitFtdcErrorMsgType	StatusMsg;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///交易所报单操作
struct CSgitFtdcExchangeOrderActionField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TSgitFtdcActionFlagType	ActionFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量变化
	TSgitFtdcVolumeType	VolumeChange;
	///操作日期
	TSgitFtdcDateType	ActionDate;
	///操作时间
	TSgitFtdcTimeType	ActionTime;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TSgitFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TSgitFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///交易所报单操作失败
struct CSgitFtdcExchangeOrderActionErrorField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TSgitFtdcOrderLocalIDType	ActionLocalID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///交易所成交
struct CSgitFtdcExchangeTradeField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///成交编号
	TSgitFtdcTradeIDType	TradeID;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///交易角色
	TSgitFtdcTradingRoleType	TradingRole;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///开平标志
	TSgitFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///价格
	TSgitFtdcPriceType	Price;
	///数量
	TSgitFtdcVolumeType	Volume;
	///成交时期
	TSgitFtdcDateType	TradeDate;
	///成交时间
	TSgitFtdcTimeType	TradeTime;
	///成交类型
	TSgitFtdcTradeTypeType	TradeType;
	///成交价来源
	TSgitFtdcPriceSourceType	PriceSource;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TSgitFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///序号
	TSgitFtdcSequenceNoType	SequenceNo;
	///成交来源
	TSgitFtdcTradeSourceType	TradeSource;
};

///成交
struct CSgitFtdcTradeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///成交编号
	TSgitFtdcTradeIDType	TradeID;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///交易角色
	TSgitFtdcTradingRoleType	TradingRole;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///开平标志
	TSgitFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///价格
	TSgitFtdcPriceType	Price;
	///数量
	TSgitFtdcVolumeType	Volume;
	///成交时期
	TSgitFtdcDateType	TradeDate;
	///成交时间
	TSgitFtdcTimeType	TradeTime;
	///成交类型
	TSgitFtdcTradeTypeType	TradeType;
	///成交价来源
	TSgitFtdcPriceSourceType	PriceSource;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TSgitFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///序号
	TSgitFtdcSequenceNoType	SequenceNo;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///经纪公司报单编号
	TSgitFtdcSequenceNoType	BrokerOrderSeq;
	///成交来源
	TSgitFtdcTradeSourceType	TradeSource;
};

///用户会话
struct CSgitFtdcUserSessionField
{
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///登录日期
	TSgitFtdcDateType	LoginDate;
	///登录时间
	TSgitFtdcTimeType	LoginTime;
	///IP地址
	TSgitFtdcIPAddressType	IPAddress;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TSgitFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TSgitFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TSgitFtdcMacAddressType	MacAddress;
};

///查询最大报单数量
struct CSgitFtdcQueryMaxOrderVolumeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///开平标志
	TSgitFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///最大允许报单数量
	TSgitFtdcVolumeType	MaxVolume;
};

///投资者结算结果确认信息
struct CSgitFtdcSettlementInfoConfirmField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///确认日期
	TSgitFtdcDateType	ConfirmDate;
	///确认时间
	TSgitFtdcTimeType	ConfirmTime;
};

///出入金同步
struct CSgitFtdcSyncDepositField
{
	///出入金流水号
	TSgitFtdcDepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///入金金额
	TSgitFtdcMoneyType	Deposit;
	///是否强制进行
	TSgitFtdcBoolType	IsForce;
};

///经纪公司同步
struct CSgitFtdcBrokerSyncField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
};

///正在同步中的投资者
struct CSgitFtdcSyncingInvestorField
{
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TSgitFtdcInvestorIDType	InvestorGroupID;
	///投资者名称
	TSgitFtdcPartyNameType	InvestorName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
	///联系电话
	TSgitFtdcTelephoneType	Telephone;
	///通讯地址
	TSgitFtdcAddressType	Address;
	///开户日期
	TSgitFtdcDateType	OpenDate;
	///手机
	TSgitFtdcMobileType	Mobile;
	///手续费率模板代码
	TSgitFtdcInvestorIDType	CommModelID;
};

///正在同步中的交易代码
struct CSgitFtdcSyncingTradingCodeField
{
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
	///交易编码类型
	TSgitFtdcClientIDTypeType	ClientIDType;
};

///正在同步中的投资者分组
struct CSgitFtdcSyncingInvestorGroupField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者分组代码
	TSgitFtdcInvestorIDType	InvestorGroupID;
	///投资者分组名称
	TSgitFtdcInvestorGroupNameType	InvestorGroupName;
};

///正在同步中的交易账号
struct CSgitFtdcSyncingTradingAccountField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///上次质押金额
	TSgitFtdcMoneyType	PreMortgage;
	///上次信用额度
	TSgitFtdcMoneyType	PreCredit;
	///上次存款额
	TSgitFtdcMoneyType	PreDeposit;
	///上次结算准备金
	TSgitFtdcMoneyType	PreBalance;
	///上次占用的保证金
	TSgitFtdcMoneyType	PreMargin;
	///利息基数
	TSgitFtdcMoneyType	InterestBase;
	///利息收入
	TSgitFtdcMoneyType	Interest;
	///入金金额
	TSgitFtdcMoneyType	Deposit;
	///出金金额
	TSgitFtdcMoneyType	Withdraw;
	///冻结的保证金
	TSgitFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TSgitFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TSgitFtdcMoneyType	FrozenCommission;
	///当前保证金总额
	TSgitFtdcMoneyType	CurrMargin;
	///资金差额
	TSgitFtdcMoneyType	CashIn;
	///手续费
	TSgitFtdcMoneyType	Commission;
	///平仓盈亏
	TSgitFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TSgitFtdcMoneyType	PositionProfit;
	///期货结算准备金
	TSgitFtdcMoneyType	Balance;
	///可用资金
	TSgitFtdcMoneyType	Available;
	///可取资金
	TSgitFtdcMoneyType	WithdrawQuota;
	///基本准备金
	TSgitFtdcMoneyType	Reserve;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///信用额度
	TSgitFtdcMoneyType	Credit;
	///质押金额
	TSgitFtdcMoneyType	Mortgage;
	///交易所保证金
	TSgitFtdcMoneyType	ExchangeMargin;
	///投资者交割保证金
	TSgitFtdcMoneyType	DeliveryMargin;
	///交易所交割保证金
	TSgitFtdcMoneyType	ExchangeDeliveryMargin;
};

///正在同步中的投资者持仓
struct CSgitFtdcSyncingInvestorPositionField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///持仓多空方向
	TSgitFtdcPosiDirectionType	PosiDirection;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///持仓日期
	TSgitFtdcPositionDateType	PositionDate;
	///上日持仓
	TSgitFtdcVolumeType	YdPosition;
	///今日持仓
	TSgitFtdcVolumeType	Position;
	///多头冻结
	TSgitFtdcVolumeType	LongFrozen;
	///空头冻结
	TSgitFtdcVolumeType	ShortFrozen;
	///开仓冻结金额
	TSgitFtdcMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TSgitFtdcMoneyType	ShortFrozenAmount;
	///开仓量
	TSgitFtdcVolumeType	OpenVolume;
	///平仓量
	TSgitFtdcVolumeType	CloseVolume;
	///开仓金额
	TSgitFtdcMoneyType	OpenAmount;
	///平仓金额
	TSgitFtdcMoneyType	CloseAmount;
	///持仓成本
	TSgitFtdcMoneyType	PositionCost;
	///上次占用的保证金
	TSgitFtdcMoneyType	PreMargin;
	///占用的保证金
	TSgitFtdcMoneyType	UseMargin;
	///冻结的保证金
	TSgitFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TSgitFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TSgitFtdcMoneyType	FrozenCommission;
	///资金差额
	TSgitFtdcMoneyType	CashIn;
	///手续费
	TSgitFtdcMoneyType	Commission;
	///平仓盈亏
	TSgitFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TSgitFtdcMoneyType	PositionProfit;
	///上次结算价
	TSgitFtdcPriceType	PreSettlementPrice;
	///本次结算价
	TSgitFtdcPriceType	SettlementPrice;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///开仓成本
	TSgitFtdcMoneyType	OpenCost;
	///交易所保证金
	TSgitFtdcMoneyType	ExchangeMargin;
	///组合成交形成的持仓
	TSgitFtdcVolumeType	CombPosition;
	///组合多头冻结
	TSgitFtdcVolumeType	CombLongFrozen;
	///组合空头冻结
	TSgitFtdcVolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	TSgitFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TSgitFtdcMoneyType	CloseProfitByTrade;
	///今日持仓
	TSgitFtdcVolumeType	TodayPosition;
	///保证金率
	TSgitFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TSgitFtdcRatioType	MarginRateByVolume;
};

///正在同步中的合约保证金率
struct CSgitFtdcSyncingInstrumentMarginRateField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///多头保证金率
	TSgitFtdcRatioType	LongMarginRatioByMoney;
	///多头保证金费
	TSgitFtdcMoneyType	LongMarginRatioByVolume;
	///空头保证金率
	TSgitFtdcRatioType	ShortMarginRatioByMoney;
	///空头保证金费
	TSgitFtdcMoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	TSgitFtdcBoolType	IsRelative;
};

///正在同步中的合约手续费率
struct CSgitFtdcSyncingInstrumentCommissionRateField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///开仓手续费率
	TSgitFtdcRatioType	OpenRatioByMoney;
	///开仓手续费
	TSgitFtdcRatioType	OpenRatioByVolume;
	///平仓手续费率
	TSgitFtdcRatioType	CloseRatioByMoney;
	///平仓手续费
	TSgitFtdcRatioType	CloseRatioByVolume;
	///平今手续费率
	TSgitFtdcRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TSgitFtdcRatioType	CloseTodayRatioByVolume;
};

///正在同步中的合约交易权限
struct CSgitFtdcSyncingInstrumentTradingRightField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///交易权限
	TSgitFtdcTradingRightType	TradingRight;
};

///查询报单
struct CSgitFtdcQryOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///开始时间
	TSgitFtdcTimeType	InsertTimeStart;
	///结束时间
	TSgitFtdcTimeType	InsertTimeEnd;
};

///查询成交
struct CSgitFtdcQryTradeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///成交编号
	TSgitFtdcTradeIDType	TradeID;
	///开始时间
	TSgitFtdcTimeType	TradeTimeStart;
	///结束时间
	TSgitFtdcTimeType	TradeTimeEnd;
};

///查询投资者持仓
struct CSgitFtdcQryInvestorPositionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///查询资金账户
struct CSgitFtdcQryTradingAccountField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///查询投资者
struct CSgitFtdcQryInvestorField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///查询交易编码
struct CSgitFtdcQryTradingCodeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///交易编码类型
	TSgitFtdcClientIDTypeType	ClientIDType;
};

///查询交易编码
struct CSgitFtdcQryInvestorGroupField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
};

///查询交易编码
struct CSgitFtdcQryInstrumentMarginRateField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
};

///查询交易编码
struct CSgitFtdcQryInstrumentCommissionRateField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///查询交易编码
struct CSgitFtdcQryInstrumentTradingRightField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///查询经纪公司
struct CSgitFtdcQryBrokerField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
};

///查询交易员
struct CSgitFtdcQryTraderField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
};

///查询经纪公司会员代码
struct CSgitFtdcQryPartBrokerField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
};

///查询管理用户功能权限
struct CSgitFtdcQrySuperUserFunctionField
{
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///查询用户会话
struct CSgitFtdcQryUserSessionField
{
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///查询前置状态
struct CSgitFtdcQryFrontStatusField
{
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
};

///查询交易所报单
struct CSgitFtdcQryExchangeOrderField
{
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
};

///查询报单操作
struct CSgitFtdcQryOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
};

///查询交易所报单操作
struct CSgitFtdcQryExchangeOrderActionField
{
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
};

///查询管理用户
struct CSgitFtdcQrySuperUserField
{
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///查询交易所
struct CSgitFtdcQryExchangeField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
};

///查询产品
struct CSgitFtdcQryProductField
{
	///产品代码
	TSgitFtdcInstrumentIDType	ProductID;
};

///查询合约
struct CSgitFtdcQryInstrumentField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///产品代码
	TSgitFtdcInstrumentIDType	ProductID;
};

///查询行情
struct CSgitFtdcQryDepthMarketDataField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///查询经纪公司用户
struct CSgitFtdcQryBrokerUserField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///查询经纪公司用户权限
struct CSgitFtdcQryBrokerUserFunctionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
};

///查询交易员报盘机
struct CSgitFtdcQryTraderOfferField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
};

///查询出入金流水
struct CSgitFtdcQrySyncDepositField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///出入金流水号
	TSgitFtdcDepositSeqNoType	DepositSeqNo;
};

///查询投资者结算结果
struct CSgitFtdcQrySettlementInfoField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///交易日
	TSgitFtdcDateType	TradingDay;
};

///查询报单
struct CSgitFtdcQryHisOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///开始时间
	TSgitFtdcTimeType	InsertTimeStart;
	///结束时间
	TSgitFtdcTimeType	InsertTimeEnd;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
};

///市场行情
struct CSgitFtdcMarketDataField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///最新价
	TSgitFtdcPriceType	LastPrice;
	///上次结算价
	TSgitFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TSgitFtdcPriceType	PreClosePrice;
	///昨持仓量
	TSgitFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TSgitFtdcPriceType	OpenPrice;
	///最高价
	TSgitFtdcPriceType	HighestPrice;
	///最低价
	TSgitFtdcPriceType	LowestPrice;
	///数量
	TSgitFtdcVolumeType	Volume;
	///成交金额
	TSgitFtdcMoneyType	Turnover;
	///持仓量
	TSgitFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TSgitFtdcPriceType	ClosePrice;
	///本次结算价
	TSgitFtdcPriceType	SettlementPrice;
	///涨停板价
	TSgitFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TSgitFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TSgitFtdcRatioType	PreDelta;
	///今虚实度
	TSgitFtdcRatioType	CurrDelta;
	///最后修改时间
	TSgitFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TSgitFtdcMillisecType	UpdateMillisec;
};

///行情基础属性
struct CSgitFtdcMarketDataBaseField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///上次结算价
	TSgitFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TSgitFtdcPriceType	PreClosePrice;
	///昨持仓量
	TSgitFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TSgitFtdcRatioType	PreDelta;
};

///行情静态属性
struct CSgitFtdcMarketDataStaticField
{
	///今开盘
	TSgitFtdcPriceType	OpenPrice;
	///最高价
	TSgitFtdcPriceType	HighestPrice;
	///最低价
	TSgitFtdcPriceType	LowestPrice;
	///今收盘
	TSgitFtdcPriceType	ClosePrice;
	///涨停板价
	TSgitFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TSgitFtdcPriceType	LowerLimitPrice;
	///本次结算价
	TSgitFtdcPriceType	SettlementPrice;
	///今虚实度
	TSgitFtdcRatioType	CurrDelta;
};

///行情最新成交属性
struct CSgitFtdcMarketDataLastMatchField
{
	///最新价
	TSgitFtdcPriceType	LastPrice;
	///数量
	TSgitFtdcVolumeType	Volume;
	///成交金额
	TSgitFtdcMoneyType	Turnover;
	///持仓量
	TSgitFtdcLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CSgitFtdcMarketDataBestPriceField
{
	///申买价一
	TSgitFtdcPriceType	BidPrice1;
	///申买量一
	TSgitFtdcVolumeType	BidVolume1;
	///申卖价一
	TSgitFtdcPriceType	AskPrice1;
	///申卖量一
	TSgitFtdcVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CSgitFtdcMarketDataBid23Field
{
	///申买价二
	TSgitFtdcPriceType	BidPrice2;
	///申买量二
	TSgitFtdcVolumeType	BidVolume2;
	///申买价三
	TSgitFtdcPriceType	BidPrice3;
	///申买量三
	TSgitFtdcVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CSgitFtdcMarketDataAsk23Field
{
	///申卖价二
	TSgitFtdcPriceType	AskPrice2;
	///申卖量二
	TSgitFtdcVolumeType	AskVolume2;
	///申卖价三
	TSgitFtdcPriceType	AskPrice3;
	///申卖量三
	TSgitFtdcVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CSgitFtdcMarketDataBid45Field
{
	///申买价四
	TSgitFtdcPriceType	BidPrice4;
	///申买量四
	TSgitFtdcVolumeType	BidVolume4;
	///申买价五
	TSgitFtdcPriceType	BidPrice5;
	///申买量五
	TSgitFtdcVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CSgitFtdcMarketDataAsk45Field
{
	///申卖价四
	TSgitFtdcPriceType	AskPrice4;
	///申卖量四
	TSgitFtdcVolumeType	AskVolume4;
	///申卖价五
	TSgitFtdcPriceType	AskPrice5;
	///申卖量五
	TSgitFtdcVolumeType	AskVolume5;
};

///行情更新时间属性
struct CSgitFtdcMarketDataUpdateTimeField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TSgitFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TSgitFtdcMillisecType	UpdateMillisec;
};

///行情交易所代码属性
struct CSgitFtdcMarketDataExchangeField
{
	///交易所代码
	TSgitFtdcPriceType	ExchangeID;
};

///指定的合约
struct CSgitFtdcSpecificInstrumentField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///合约状态
struct CSgitFtdcInstrumentStatusField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///结算组代码
	TSgitFtdcSettlementGroupIDType	SettlementGroupID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///合约交易状态
	TSgitFtdcInstrumentStatusType	InstrumentStatus;
	///交易阶段编号
	TSgitFtdcTradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	TSgitFtdcTimeType	EnterTime;
	///进入本状态原因
	TSgitFtdcInstStatusEnterReasonType	EnterReason;
};

///查询合约状态
struct CSgitFtdcQryInstrumentStatusField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
};

///投资者账户
struct CSgitFtdcInvestorAccountField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
};

///浮动盈亏算法
struct CSgitFtdcPositionProfitAlgorithmField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///盈亏算法
	TSgitFtdcAlgorithmType	Algorithm;
	///备注
	TSgitFtdcMemoType	Memo;
};

///会员资金折扣
struct CSgitFtdcDiscountField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///资金折扣比例
	TSgitFtdcRatioType	Discount;
};

///查询转帐银行
struct CSgitFtdcQryTransferBankField
{
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分中心代码
	TSgitFtdcBankBrchIDType	BankBrchID;
};

///转帐银行
struct CSgitFtdcTransferBankField
{
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分中心代码
	TSgitFtdcBankBrchIDType	BankBrchID;
	///银行名称
	TSgitFtdcBankNameType	BankName;
	///是否活跃
	TSgitFtdcBoolType	IsActive;
};

///查询投资者持仓明细
struct CSgitFtdcQryInvestorPositionDetailField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///投资者持仓明细
struct CSgitFtdcInvestorPositionDetailField
{
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///买卖
	TSgitFtdcDirectionType	Direction;
	///开仓日期
	TSgitFtdcDateType	OpenDate;
	///成交编号
	TSgitFtdcTradeIDType	TradeID;
	///数量
	TSgitFtdcVolumeType	Volume;
	///开仓价
	TSgitFtdcPriceType	OpenPrice;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///成交类型
	TSgitFtdcTradeTypeType	TradeType;
	///组合合约代码
	TSgitFtdcInstrumentIDType	CombInstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///逐日盯市平仓盈亏
	TSgitFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TSgitFtdcMoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	TSgitFtdcMoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	TSgitFtdcMoneyType	PositionProfitByTrade;
	///投资者保证金
	TSgitFtdcMoneyType	Margin;
	///交易所保证金
	TSgitFtdcMoneyType	ExchMargin;
	///保证金率
	TSgitFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TSgitFtdcRatioType	MarginRateByVolume;
	///昨结算价
	TSgitFtdcPriceType	LastSettlementPrice;
	///结算价
	TSgitFtdcPriceType	SettlementPrice;
	///平仓量
	TSgitFtdcVolumeType	CloseVolume;
	///平仓金额
	TSgitFtdcMoneyType	CloseAmount;
};

///资金账户口令域
struct CSgitFtdcTradingAccountPasswordField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///密码
	TSgitFtdcPasswordType	Password;
};

///交易所行情报盘机
struct CSgitFtdcMDTraderOfferField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TSgitFtdcTraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	TSgitFtdcDateType	ConnectRequestDate;
	///发出连接请求的时间
	TSgitFtdcTimeType	ConnectRequestTime;
	///上次报告日期
	TSgitFtdcDateType	LastReportDate;
	///上次报告时间
	TSgitFtdcTimeType	LastReportTime;
	///完成连接日期
	TSgitFtdcDateType	ConnectDate;
	///完成连接时间
	TSgitFtdcTimeType	ConnectTime;
	///启动日期
	TSgitFtdcDateType	StartDate;
	///启动时间
	TSgitFtdcTimeType	StartTime;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///本席位最大成交编号
	TSgitFtdcTradeIDType	MaxTradeID;
	///本席位最大报单备拷
	TSgitFtdcReturnCodeType	MaxOrderMessageReference;
};

///查询行情报盘机
struct CSgitFtdcQryMDTraderOfferField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
};

///查询客户通知
struct CSgitFtdcQryNoticeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
};

///客户通知
struct CSgitFtdcNoticeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///消息正文
	TSgitFtdcContentType	Content;
	///经纪公司通知内容序列号
	TSgitFtdcSequenceLabelType	SequenceLabel;
};

///用户权限
struct CSgitFtdcUserRightField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///客户权限类型
	TSgitFtdcUserRightTypeType	UserRightType;
	///是否禁止
	TSgitFtdcBoolType	IsForbidden;
};

///查询结算信息确认域
struct CSgitFtdcQrySettlementInfoConfirmField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///装载结算信息
struct CSgitFtdcLoadSettlementInfoField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
};

///经纪公司可提资金算法表
struct CSgitFtdcBrokerWithdrawAlgorithmField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///可提资金算法
	TSgitFtdcAlgorithmType	WithdrawAlgorithm;
	///资金使用率
	TSgitFtdcRatioType	UsingRatio;
	///可提是否包含平仓盈利
	TSgitFtdcIncludeCloseProfitType	IncludeCloseProfit;
	///本日无仓且无成交客户是否受可提比例限制
	TSgitFtdcAllWithoutTradeType	AllWithoutTrade;
	///可用是否包含平仓盈利
	TSgitFtdcIncludeCloseProfitType	AvailIncludeCloseProfit;
	///是否启用用户事件
	TSgitFtdcBoolType	IsBrokerUserEvent;
};

///资金账户口令变更域
struct CSgitFtdcTradingAccountPasswordUpdateV1Field
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///原来的口令
	TSgitFtdcPasswordType	OldPassword;
	///新的口令
	TSgitFtdcPasswordType	NewPassword;
};

///资金账户口令变更域
struct CSgitFtdcTradingAccountPasswordUpdateField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///原来的口令
	TSgitFtdcPasswordType	OldPassword;
	///新的口令
	TSgitFtdcPasswordType	NewPassword;
};

///查询组合合约分腿
struct CSgitFtdcQryCombinationLegField
{
	///组合合约代码
	TSgitFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TSgitFtdcLegIDType	LegID;
	///单腿合约代码
	TSgitFtdcInstrumentIDType	LegInstrumentID;
};

///查询组合合约分腿
struct CSgitFtdcQrySyncStatusField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
};

///组合交易合约的单腿
struct CSgitFtdcCombinationLegField
{
	///组合合约代码
	TSgitFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TSgitFtdcLegIDType	LegID;
	///单腿合约代码
	TSgitFtdcInstrumentIDType	LegInstrumentID;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///单腿乘数
	TSgitFtdcLegMultipleType	LegMultiple;
	///派生层数
	TSgitFtdcImplyLevelType	ImplyLevel;
};

///数据同步状态
struct CSgitFtdcSyncStatusField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///数据同步状态
	TSgitFtdcDataSyncStatusType	DataSyncStatus;
};

///查询联系人
struct CSgitFtdcQryLinkManField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///联系人
struct CSgitFtdcLinkManField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///联系人类型
	TSgitFtdcPersonTypeType	PersonType;
	///证件类型
	TSgitFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///名称
	TSgitFtdcPartyNameType	PersonName;
	///联系电话
	TSgitFtdcTelephoneType	Telephone;
	///通讯地址
	TSgitFtdcAddressType	Address;
	///邮政编码
	TSgitFtdcZipCodeType	ZipCode;
	///优先级
	TSgitFtdcPriorityType	Priority;
};

///查询经纪公司用户事件
struct CSgitFtdcQryBrokerUserEventField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///用户事件类型
	TSgitFtdcUserEventTypeType	UserEventType;
};

///查询经纪公司用户事件
struct CSgitFtdcBrokerUserEventField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///用户事件类型
	TSgitFtdcUserEventTypeType	UserEventType;
	///用户事件序号
	TSgitFtdcSequenceNoType	EventSequenceNo;
	///事件发生日期
	TSgitFtdcDateType	EventDate;
	///事件发生时间
	TSgitFtdcTimeType	EventTime;
	///用户事件信息
	TSgitFtdcUserEventInfoType	UserEventInfo;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///查询签约银行请求
struct CSgitFtdcQryContractBankField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分中心代码
	TSgitFtdcBankBrchIDType	BankBrchID;
};

///查询签约银行响应
struct CSgitFtdcContractBankField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分中心代码
	TSgitFtdcBankBrchIDType	BankBrchID;
	///银行名称
	TSgitFtdcBankNameType	BankName;
};

///投资者组合持仓明细
struct CSgitFtdcInvestorPositionCombineDetailField
{
	///交易日
	TSgitFtdcDateType	TradingDay;
	///开仓日期
	TSgitFtdcDateType	OpenDate;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///组合编号
	TSgitFtdcTradeIDType	ComTradeID;
	///撮合编号
	TSgitFtdcTradeIDType	TradeID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///买卖
	TSgitFtdcDirectionType	Direction;
	///持仓量
	TSgitFtdcVolumeType	TotalAmt;
	///投资者保证金
	TSgitFtdcMoneyType	Margin;
	///交易所保证金
	TSgitFtdcMoneyType	ExchMargin;
	///保证金率
	TSgitFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TSgitFtdcRatioType	MarginRateByVolume;
	///单腿编号
	TSgitFtdcLegIDType	LegID;
	///单腿乘数
	TSgitFtdcLegMultipleType	LegMultiple;
	///组合持仓合约编码
	TSgitFtdcInstrumentIDType	CombInstrumentID;
};

///预埋单
struct CSgitFtdcParkedOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///报单价格条件
	TSgitFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///组合开平标志
	TSgitFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSgitFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量
	TSgitFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSgitFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSgitFtdcDateType	GTDDate;
	///成交量类型
	TSgitFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSgitFtdcVolumeType	MinVolume;
	///触发条件
	TSgitFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSgitFtdcPriceType	StopPrice;
	///强平原因
	TSgitFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSgitFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///用户强评标志
	TSgitFtdcBoolType	UserForceClose;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///预埋报单编号
	TSgitFtdcParkedOrderIDType	ParkedOrderID;
	///用户类型
	TSgitFtdcUserTypeType	UserType;
	///预埋单状态
	TSgitFtdcParkedOrderStatusType	Status;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///输入预埋单操作
struct CSgitFtdcParkedOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TSgitFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TSgitFtdcActionFlagType	ActionFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量变化
	TSgitFtdcVolumeType	VolumeChange;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///预埋撤单单编号
	TSgitFtdcParkedOrderActionIDType	ParkedOrderActionID;
	///用户类型
	TSgitFtdcUserTypeType	UserType;
	///预埋撤单状态
	TSgitFtdcParkedOrderStatusType	Status;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///查询预埋单
struct CSgitFtdcQryParkedOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
};

///查询预埋撤单
struct CSgitFtdcQryParkedOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
};

///删除预埋单
struct CSgitFtdcRemoveParkedOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///预埋报单编号
	TSgitFtdcParkedOrderIDType	ParkedOrderID;
};

///删除预埋撤单
struct CSgitFtdcRemoveParkedOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///预埋撤单编号
	TSgitFtdcParkedOrderActionIDType	ParkedOrderActionID;
};

///经纪公司可提资金算法表
struct CSgitFtdcInvestorWithdrawAlgorithmField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///可提资金比例
	TSgitFtdcRatioType	UsingRatio;
};

///查询组合持仓明细
struct CSgitFtdcQryInvestorPositionCombineDetailField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///组合持仓合约编码
	TSgitFtdcInstrumentIDType	CombInstrumentID;
};

///成交均价
struct CSgitFtdcMarketDataAveragePriceField
{
	///当日均价
	TSgitFtdcPriceType	AveragePrice;
};

///校验投资者密码
struct CSgitFtdcVerifyInvestorPasswordField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///密码
	TSgitFtdcPasswordType	Password;
};

///用户IP
struct CSgitFtdcUserIPField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///IP地址
	TSgitFtdcIPAddressType	IPAddress;
	///IP地址掩码
	TSgitFtdcIPAddressType	IPMask;
	///Mac地址
	TSgitFtdcMacAddressType	MacAddress;
};

///用户事件通知信息
struct CSgitFtdcTradingNoticeInfoField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///发送时间
	TSgitFtdcTimeType	SendTime;
	///消息正文
	TSgitFtdcContentType	FieldContent;
	///序列系列号
	TSgitFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TSgitFtdcSequenceNoType	SequenceNo;
};

///用户事件通知
struct CSgitFtdcTradingNoticeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者范围
	TSgitFtdcInvestorRangeType	InvestorRange;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///序列系列号
	TSgitFtdcSequenceSeriesType	SequenceSeries;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///发送时间
	TSgitFtdcTimeType	SendTime;
	///序列号
	TSgitFtdcSequenceNoType	SequenceNo;
	///消息正文
	TSgitFtdcContentType	FieldContent;
};

///查询交易事件通知
struct CSgitFtdcQryTradingNoticeField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///查询错误报单
struct CSgitFtdcQryErrOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///错误报单
struct CSgitFtdcErrOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///报单价格条件
	TSgitFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///组合开平标志
	TSgitFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSgitFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量
	TSgitFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSgitFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSgitFtdcDateType	GTDDate;
	///成交量类型
	TSgitFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSgitFtdcVolumeType	MinVolume;
	///触发条件
	TSgitFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSgitFtdcPriceType	StopPrice;
	///强平原因
	TSgitFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSgitFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///用户强评标志
	TSgitFtdcBoolType	UserForceClose;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///查询错误报单操作
struct CSgitFtdcErrorConditionalOrderField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///报单价格条件
	TSgitFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///组合开平标志
	TSgitFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TSgitFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量
	TSgitFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TSgitFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TSgitFtdcDateType	GTDDate;
	///成交量类型
	TSgitFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TSgitFtdcVolumeType	MinVolume;
	///触发条件
	TSgitFtdcContingentConditionType	ContingentCondition;
	///止损价
	TSgitFtdcPriceType	StopPrice;
	///强平原因
	TSgitFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TSgitFtdcBoolType	IsAutoSuspend;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///合约在交易所的代码
	TSgitFtdcExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///报单提交状态
	TSgitFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TSgitFtdcSequenceNoType	NotifySequence;
	///交易日
	TSgitFtdcDateType	TradingDay;
	///结算编号
	TSgitFtdcSettlementIDType	SettlementID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TSgitFtdcOrderSourceType	OrderSource;
	///报单状态
	TSgitFtdcOrderStatusType	OrderStatus;
	///报单类型
	TSgitFtdcOrderTypeType	OrderType;
	///今成交数量
	TSgitFtdcVolumeType	VolumeTraded;
	///剩余数量
	TSgitFtdcVolumeType	VolumeTotal;
	///报单日期
	TSgitFtdcDateType	InsertDate;
	///委托时间
	TSgitFtdcTimeType	InsertTime;
	///激活时间
	TSgitFtdcTimeType	ActiveTime;
	///挂起时间
	TSgitFtdcTimeType	SuspendTime;
	///最后修改时间
	TSgitFtdcTimeType	UpdateTime;
	///撤销时间
	TSgitFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TSgitFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TSgitFtdcParticipantIDType	ClearingPartID;
	///序号
	TSgitFtdcSequenceNoType	SequenceNo;
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///用户端产品信息
	TSgitFtdcProductInfoType	UserProductInfo;
	///状态信息
	TSgitFtdcErrorMsgType	StatusMsg;
	///用户强评标志
	TSgitFtdcBoolType	UserForceClose;
	///操作用户代码
	TSgitFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TSgitFtdcSequenceNoType	BrokerOrderSeq;
	///相关报单
	TSgitFtdcOrderSysIDType	RelativeOrderSysID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///查询错误报单操作
struct CSgitFtdcQryErrOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///错误报单操作
struct CSgitFtdcErrOrderActionField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///报单操作引用
	TSgitFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	TSgitFtdcOrderRefType	OrderRef;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///前置编号
	TSgitFtdcFrontIDType	FrontID;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///报单编号
	TSgitFtdcOrderSysIDType	OrderSysID;
	///操作标志
	TSgitFtdcActionFlagType	ActionFlag;
	///价格
	TSgitFtdcPriceType	LimitPrice;
	///数量变化
	TSgitFtdcVolumeType	VolumeChange;
	///操作日期
	TSgitFtdcDateType	ActionDate;
	///操作时间
	TSgitFtdcTimeType	ActionTime;
	///交易所交易员代码
	TSgitFtdcTraderIDType	TraderID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///本地报单编号
	TSgitFtdcOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TSgitFtdcOrderLocalIDType	ActionLocalID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///客户代码
	TSgitFtdcClientIDType	ClientID;
	///业务单元
	TSgitFtdcBusinessUnitType	BusinessUnit;
	///报单操作状态
	TSgitFtdcOrderActionStatusType	OrderActionStatus;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///状态信息
	TSgitFtdcErrorMsgType	StatusMsg;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///查询交易所状态
struct CSgitFtdcQryExchangeSequenceField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
};

///交易所状态
struct CSgitFtdcExchangeSequenceField
{
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///序号
	TSgitFtdcSequenceNoType	SequenceNo;
	///合约交易状态
	TSgitFtdcInstrumentStatusType	MarketStatus;
};

///根据价格查询最大报单数量
struct CSgitFtdcQueryMaxOrderVolumeWithPriceField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///开平标志
	TSgitFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///最大允许报单数量
	TSgitFtdcVolumeType	MaxVolume;
	///报单价格
	TSgitFtdcPriceType	Price;
};

///查询经纪公司交易参数
struct CSgitFtdcQryBrokerTradingParamsField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///经纪公司交易参数
struct CSgitFtdcBrokerTradingParamsField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///保证金价格类型
	TSgitFtdcMarginPriceTypeType	MarginPriceType;
	///盈亏算法
	TSgitFtdcAlgorithmType	Algorithm;
	///可用是否包含平仓盈利
	TSgitFtdcIncludeCloseProfitType	AvailIncludeCloseProfit;
};

///查询经纪公司交易算法
struct CSgitFtdcQryBrokerTradingAlgosField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///经纪公司交易算法
struct CSgitFtdcBrokerTradingAlgosField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///持仓处理算法编号
	TSgitFtdcHandlePositionAlgoIDType	HandlePositionAlgoID;
	///寻找保证金率算法编号
	TSgitFtdcFindMarginRateAlgoIDType	FindMarginRateAlgoID;
	///资金处理算法编号
	TSgitFtdcHandleTradingAccountAlgoIDType	HandleTradingAccountAlgoID;
};

///查询经纪公司资金
struct CSgitFtdcQueryBrokerDepositField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
};

///经纪公司资金
struct CSgitFtdcBrokerDepositField
{
	///交易日期
	TSgitFtdcTradeDateType	TradingDay;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///会员代码
	TSgitFtdcParticipantIDType	ParticipantID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///上次结算准备金
	TSgitFtdcMoneyType	PreBalance;
	///当前保证金总额
	TSgitFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TSgitFtdcMoneyType	CloseProfit;
	///期货结算准备金
	TSgitFtdcMoneyType	Balance;
	///入金金额
	TSgitFtdcMoneyType	Deposit;
	///出金金额
	TSgitFtdcMoneyType	Withdraw;
	///可提资金
	TSgitFtdcMoneyType	Available;
	///基本准备金
	TSgitFtdcMoneyType	Reserve;
	///冻结的保证金
	TSgitFtdcMoneyType	FrozenMargin;
};

///查询保证金监管系统经纪公司密钥
struct CSgitFtdcQryCFMMCBrokerKeyField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
};

///保证金监管系统经纪公司密钥
struct CSgitFtdcCFMMCBrokerKeyField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///经纪公司统一编码
	TSgitFtdcParticipantIDType	ParticipantID;
	///密钥生成日期
	TSgitFtdcDateType	CreateDate;
	///密钥生成时间
	TSgitFtdcTimeType	CreateTime;
	///密钥编号
	TSgitFtdcSequenceNoType	KeyID;
	///动态密钥
	TSgitFtdcCFMMCKeyType	CurrentKey;
	///动态密钥类型
	TSgitFtdcCFMMCKeyKindType	KeyKind;
};

///保证金监管系统经纪公司资金账户密钥
struct CSgitFtdcCFMMCTradingAccountKeyField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///经纪公司统一编码
	TSgitFtdcParticipantIDType	ParticipantID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///密钥编号
	TSgitFtdcSequenceNoType	KeyID;
	///动态密钥
	TSgitFtdcCFMMCKeyType	CurrentKey;
};

///请求查询保证金监管系统经纪公司资金账户密钥
struct CSgitFtdcQryCFMMCTradingAccountKeyField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
};

///用户动态令牌参数
struct CSgitFtdcBrokerUserOTPParamField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///动态令牌提供商
	TSgitFtdcOTPVendorsIDType	OTPVendorsID;
	///动态令牌序列号
	TSgitFtdcSerialNumberType	SerialNumber;
	///令牌密钥
	TSgitFtdcAuthKeyType	AuthKey;
	///漂移值
	TSgitFtdcLastDriftType	LastDrift;
	///成功值
	TSgitFtdcLastSuccessType	LastSuccess;
	///动态令牌类型
	TSgitFtdcOTPTypeType	OTPType;
};

///手工同步用户动态令牌
struct CSgitFtdcManualSyncBrokerUserOTPField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///动态令牌类型
	TSgitFtdcOTPTypeType	OTPType;
	///第一个动态密码
	TSgitFtdcPasswordType	FirstOTP;
	///第二个动态密码
	TSgitFtdcPasswordType	SecondOTP;
};

///投资者手续费率模板
struct CSgitFtdcCommRateModelField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///手续费率模板代码
	TSgitFtdcInvestorIDType	CommModelID;
	///模板名称
	TSgitFtdcCommModelNameType	CommModelName;
};

///请求查询投资者手续费率模板
struct CSgitFtdcQryCommRateModelField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///手续费率模板代码
	TSgitFtdcInvestorIDType	CommModelID;
};

///仓单折抵信息
struct CSgitFtdcEWarrantOffsetField
{
	///交易日期
	TSgitFtdcTradeDateType	TradingDay;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TSgitFtdcDirectionType	Direction;
	///投机套保标志
	TSgitFtdcHedgeFlagType	HedgeFlag;
	///数量
	TSgitFtdcVolumeType	Volume;
};

///查询仓单折抵信息
struct CSgitFtdcQryEWarrantOffsetField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///交易所代码
	TSgitFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSgitFtdcInstrumentIDType	InstrumentID;
};

///转帐开户请求
struct CSgitFtdcReqOpenAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TSgitFtdcGenderType	Gender;
	///国家代码
	TSgitFtdcCountryCodeType	CountryCode;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///地址
	TSgitFtdcAddressType	Address;
	///邮编
	TSgitFtdcZipCodeType	ZipCode;
	///电话号码
	TSgitFtdcTelephoneType	Telephone;
	///手机
	TSgitFtdcMobilePhoneType	MobilePhone;
	///传真
	TSgitFtdcFaxType	Fax;
	///电子邮件
	TSgitFtdcEMailType	EMail;
	///资金账户状态
	TSgitFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TSgitFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///交易ID
	TSgitFtdcTIDType	TID;
};

///转帐销户请求
struct CSgitFtdcReqCancelAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TSgitFtdcGenderType	Gender;
	///国家代码
	TSgitFtdcCountryCodeType	CountryCode;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///地址
	TSgitFtdcAddressType	Address;
	///邮编
	TSgitFtdcZipCodeType	ZipCode;
	///电话号码
	TSgitFtdcTelephoneType	Telephone;
	///手机
	TSgitFtdcMobilePhoneType	MobilePhone;
	///传真
	TSgitFtdcFaxType	Fax;
	///电子邮件
	TSgitFtdcEMailType	EMail;
	///资金账户状态
	TSgitFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TSgitFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///交易ID
	TSgitFtdcTIDType	TID;
};

///变更银行账户请求
struct CSgitFtdcReqChangeAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TSgitFtdcGenderType	Gender;
	///国家代码
	TSgitFtdcCountryCodeType	CountryCode;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///地址
	TSgitFtdcAddressType	Address;
	///邮编
	TSgitFtdcZipCodeType	ZipCode;
	///电话号码
	TSgitFtdcTelephoneType	Telephone;
	///手机
	TSgitFtdcMobilePhoneType	MobilePhone;
	///传真
	TSgitFtdcFaxType	Fax;
	///电子邮件
	TSgitFtdcEMailType	EMail;
	///资金账户状态
	TSgitFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///新银行帐号
	TSgitFtdcBankAccountType	NewBankAccount;
	///新银行密码
	TSgitFtdcPasswordType	NewBankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易ID
	TSgitFtdcTIDType	TID;
	///摘要
	TSgitFtdcDigestType	Digest;
};

///转账请求
struct CSgitFtdcReqTransferField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TSgitFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TSgitFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TSgitFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TSgitFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TSgitFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TSgitFtdcAddInfoType	Message;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///转账交易状态
	TSgitFtdcTransferStatusType	TransferStatus;
};

///银行发起银行资金转期货响应
struct CSgitFtdcRspTransferField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TSgitFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TSgitFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TSgitFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TSgitFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TSgitFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TSgitFtdcAddInfoType	Message;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///转账交易状态
	TSgitFtdcTransferStatusType	TransferStatus;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///冲正请求
struct CSgitFtdcReqRepealField
{
	///冲正时间间隔
	TSgitFtdcRepealTimeIntervalType	RepealTimeInterval;
	///已经冲正次数
	TSgitFtdcRepealedTimesType	RepealedTimes;
	///银行冲正标志
	TSgitFtdcBankRepealFlagType	BankRepealFlag;
	///期商冲正标志
	TSgitFtdcBrokerRepealFlagType	BrokerRepealFlag;
	///被冲正平台流水号
	TSgitFtdcPlateSerialType	PlateRepealSerial;
	///被冲正银行流水号
	TSgitFtdcBankSerialType	BankRepealSerial;
	///被冲正期货流水号
	TSgitFtdcFutureSerialType	FutureRepealSerial;
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TSgitFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TSgitFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TSgitFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TSgitFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TSgitFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TSgitFtdcAddInfoType	Message;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///转账交易状态
	TSgitFtdcTransferStatusType	TransferStatus;
};

///冲正响应
struct CSgitFtdcRspRepealField
{
	///冲正时间间隔
	TSgitFtdcRepealTimeIntervalType	RepealTimeInterval;
	///已经冲正次数
	TSgitFtdcRepealedTimesType	RepealedTimes;
	///银行冲正标志
	TSgitFtdcBankRepealFlagType	BankRepealFlag;
	///期商冲正标志
	TSgitFtdcBrokerRepealFlagType	BrokerRepealFlag;
	///被冲正平台流水号
	TSgitFtdcPlateSerialType	PlateRepealSerial;
	///被冲正银行流水号
	TSgitFtdcBankSerialType	BankRepealSerial;
	///被冲正期货流水号
	TSgitFtdcFutureSerialType	FutureRepealSerial;
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TSgitFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TSgitFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TSgitFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TSgitFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TSgitFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TSgitFtdcAddInfoType	Message;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///转账交易状态
	TSgitFtdcTransferStatusType	TransferStatus;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///查询账户信息请求
struct CSgitFtdcReqQueryAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
};

///查询账户信息响应
struct CSgitFtdcRspQueryAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///银行可用金额
	TSgitFtdcTradeAmountType	BankUseAmount;
	///银行可取金额
	TSgitFtdcTradeAmountType	BankFetchAmount;
};

///期商签到签退
struct CSgitFtdcFutureSignIOField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
};

///期商签到响应
struct CSgitFtdcRspFutureSignInField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
	///PIN密钥
	TSgitFtdcPasswordKeyType	PinKey;
	///MAC密钥
	TSgitFtdcPasswordKeyType	MacKey;
};

///期商签退请求
struct CSgitFtdcReqFutureSignOutField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
};

///期商签退响应
struct CSgitFtdcRspFutureSignOutField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///查询指定流水号的交易结果请求
struct CSgitFtdcReqQueryTradeResultBySerialField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///流水号
	TSgitFtdcSerialType	Reference;
	///本流水号发布者的机构类型
	TSgitFtdcInstitutionTypeType	RefrenceIssureType;
	///本流水号发布者机构编码
	TSgitFtdcOrganCodeType	RefrenceIssure;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TSgitFtdcTradeAmountType	TradeAmount;
	///摘要
	TSgitFtdcDigestType	Digest;
};

///查询指定流水号的交易结果响应
struct CSgitFtdcRspQueryTradeResultBySerialField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
	///流水号
	TSgitFtdcSerialType	Reference;
	///本流水号发布者的机构类型
	TSgitFtdcInstitutionTypeType	RefrenceIssureType;
	///本流水号发布者机构编码
	TSgitFtdcOrganCodeType	RefrenceIssure;
	///原始返回代码
	TSgitFtdcReturnCodeType	OriginReturnCode;
	///原始返回码描述
	TSgitFtdcDescrInfoForReturnCodeType	OriginDescrInfoForReturnCode;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TSgitFtdcTradeAmountType	TradeAmount;
	///摘要
	TSgitFtdcDigestType	Digest;
};

///日终文件就绪请求
struct CSgitFtdcReqDayEndFileReadyField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///文件业务功能
	TSgitFtdcFileBusinessCodeType	FileBusinessCode;
	///摘要
	TSgitFtdcDigestType	Digest;
};

///返回结果
struct CSgitFtdcReturnResultField
{
	///返回代码
	TSgitFtdcReturnCodeType	ReturnCode;
	///返回码描述
	TSgitFtdcDescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///验证期货资金密码
struct CSgitFtdcVerifyFuturePasswordField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///交易ID
	TSgitFtdcTIDType	TID;
};

///验证客户信息
struct CSgitFtdcVerifyCustInfoField
{
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
};

///验证期货资金密码和客户信息
struct CSgitFtdcVerifyFuturePasswordAndCustInfoField
{
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
};

///验证期货资金密码和客户信息
struct CSgitFtdcDepositResultInformField
{
	///出入金流水号，该流水号为银期报盘返回的流水号
	TSgitFtdcDepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///入金金额
	TSgitFtdcMoneyType	Deposit;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///返回代码
	TSgitFtdcReturnCodeType	ReturnCode;
	///返回码描述
	TSgitFtdcDescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///交易核心向银期报盘发出密钥同步请求
struct CSgitFtdcReqSyncKeyField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///交易核心给银期报盘的消息
	TSgitFtdcAddInfoType	Message;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
};

///交易核心向银期报盘发出密钥同步响应
struct CSgitFtdcRspSyncKeyField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///交易核心给银期报盘的消息
	TSgitFtdcAddInfoType	Message;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///查询账户信息通知
struct CSgitFtdcNotifyQueryAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///银行可用金额
	TSgitFtdcTradeAmountType	BankUseAmount;
	///银行可取金额
	TSgitFtdcTradeAmountType	BankFetchAmount;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///银期转账交易流水表
struct CSgitFtdcTransferSerialField
{
	///平台流水号
	TSgitFtdcPlateSerialType	PlateSerial;
	///交易发起方日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易日期
	TSgitFtdcDateType	TradingDay;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///交易代码
	TSgitFtdcTradeCodeType	TradeCode;
	///会话编号
	TSgitFtdcSessionIDType	SessionID;
	///银行编码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构编码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///期货公司编码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///期货公司帐号类型
	TSgitFtdcFutureAccTypeType	FutureAccType;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///投资者代码
	TSgitFtdcInvestorIDType	InvestorID;
	///期货公司流水号
	TSgitFtdcFutureSerialType	FutureSerial;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///交易金额
	TSgitFtdcTradeAmountType	TradeAmount;
	///应收客户费用
	TSgitFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TSgitFtdcFutureFeeType	BrokerFee;
	///有效标志
	TSgitFtdcAvailabilityFlagType	AvailabilityFlag;
	///操作员
	TSgitFtdcOperatorCodeType	OperatorCode;
	///新银行帐号
	TSgitFtdcBankAccountType	BankNewAccount;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///请求查询转帐流水
struct CSgitFtdcQryTransferSerialField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///银行编码
	TSgitFtdcBankIDType	BankID;
};

///期商签到通知
struct CSgitFtdcNotifyFutureSignInField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
	///PIN密钥
	TSgitFtdcPasswordKeyType	PinKey;
	///MAC密钥
	TSgitFtdcPasswordKeyType	MacKey;
};

///期商签退通知
struct CSgitFtdcNotifyFutureSignOutField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///交易核心向银期报盘发出密钥同步处理结果的通知
struct CSgitFtdcNotifySyncKeyField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///用户标识
	TSgitFtdcUserIDType	UserID;
	///交易核心给银期报盘的消息
	TSgitFtdcAddInfoType	Message;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///请求编号
	TSgitFtdcRequestIDType	RequestID;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///请求查询银期签约关系
struct CSgitFtdcQryAccountregisterField
{
	///经纪公司代码
	TSgitFtdcBrokerIDType	BrokerID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///银行编码
	TSgitFtdcBankIDType	BankID;
};

///客户开销户信息表
struct CSgitFtdcAccountregisterField
{
	///交易日期
	TSgitFtdcTradeDateType	TradeDay;
	///银行编码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构编码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///期货公司编码
	TSgitFtdcBrokerIDType	BrokerID;
	///期货公司分支机构编码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///开销户类别
	TSgitFtdcOpenOrDestroyType	OpenOrDestroy;
	///签约日期
	TSgitFtdcTradeDateType	RegDate;
	///解约日期
	TSgitFtdcTradeDateType	OutDate;
	///交易ID
	TSgitFtdcTIDType	TID;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
};

///银期开户信息
struct CSgitFtdcOpenAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TSgitFtdcGenderType	Gender;
	///国家代码
	TSgitFtdcCountryCodeType	CountryCode;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///地址
	TSgitFtdcAddressType	Address;
	///邮编
	TSgitFtdcZipCodeType	ZipCode;
	///电话号码
	TSgitFtdcTelephoneType	Telephone;
	///手机
	TSgitFtdcMobilePhoneType	MobilePhone;
	///传真
	TSgitFtdcFaxType	Fax;
	///电子邮件
	TSgitFtdcEMailType	EMail;
	///资金账户状态
	TSgitFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TSgitFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///银期销户信息
struct CSgitFtdcCancelAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TSgitFtdcGenderType	Gender;
	///国家代码
	TSgitFtdcCountryCodeType	CountryCode;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///地址
	TSgitFtdcAddressType	Address;
	///邮编
	TSgitFtdcZipCodeType	ZipCode;
	///电话号码
	TSgitFtdcTelephoneType	Telephone;
	///手机
	TSgitFtdcMobilePhoneType	MobilePhone;
	///传真
	TSgitFtdcFaxType	Fax;
	///电子邮件
	TSgitFtdcEMailType	EMail;
	///资金账户状态
	TSgitFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///汇钞标志
	TSgitFtdcCashExchangeCodeType	CashExchangeCode;
	///摘要
	TSgitFtdcDigestType	Digest;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TSgitFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TSgitFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TSgitFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TSgitFtdcOperNoType	OperNo;
	///交易ID
	TSgitFtdcTIDType	TID;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///银期变更银行账号信息
struct CSgitFtdcChangeAccountField
{
	///业务功能码
	TSgitFtdcTradeCodeType	TradeCode;
	///银行代码
	TSgitFtdcBankIDType	BankID;
	///银行分支机构代码
	TSgitFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TSgitFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TSgitFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TSgitFtdcTradeDateType	TradeDate;
	///交易时间
	TSgitFtdcTradeTimeType	TradeTime;
	///银行流水号
	TSgitFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TSgitFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TSgitFtdcSerialType	PlateSerial;
	///最后分片标志
	TSgitFtdcLastFragmentType	LastFragment;
	///会话号
	TSgitFtdcSessionIDType	SessionID;
	///客户姓名
	TSgitFtdcIndividualNameType	CustomerName;
	///证件类型
	TSgitFtdcIdCardTypeType	IdCardType;
	///证件号码
	TSgitFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///性别
	TSgitFtdcGenderType	Gender;
	///国家代码
	TSgitFtdcCountryCodeType	CountryCode;
	///客户类型
	TSgitFtdcCustTypeType	CustType;
	///地址
	TSgitFtdcAddressType	Address;
	///邮编
	TSgitFtdcZipCodeType	ZipCode;
	///电话号码
	TSgitFtdcTelephoneType	Telephone;
	///手机
	TSgitFtdcMobilePhoneType	MobilePhone;
	///传真
	TSgitFtdcFaxType	Fax;
	///电子邮件
	TSgitFtdcEMailType	EMail;
	///资金账户状态
	TSgitFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	TSgitFtdcBankAccountType	BankAccount;
	///银行密码
	TSgitFtdcPasswordType	BankPassWord;
	///新银行帐号
	TSgitFtdcBankAccountType	NewBankAccount;
	///新银行密码
	TSgitFtdcPasswordType	NewBankPassWord;
	///投资者帐号
	TSgitFtdcAccountIDType	AccountID;
	///期货密码
	TSgitFtdcPasswordType	Password;
	///银行帐号类型
	TSgitFtdcBankAccTypeType	BankAccType;
	///安装编号
	TSgitFtdcInstallIDType	InstallID;
	///验证客户证件号码标志
	TSgitFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TSgitFtdcCurrencyIDType	CurrencyID;
	///期货公司银行编码
	TSgitFtdcBankCodingForFutureType	BrokerIDByBank;
	///银行密码标志
	TSgitFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TSgitFtdcPwdFlagType	SecuPwdFlag;
	///交易ID
	TSgitFtdcTIDType	TID;
	///摘要
	TSgitFtdcDigestType	Digest;
	///错误代码
	TSgitFtdcErrorIDType	ErrorID;
	///错误信息
	TSgitFtdcErrorMsgType	ErrorMsg;
};

///灾备中心交易权限
struct CSgitFtdcUserRightsAssignField
{
	///应用单元代码
	TSgitFtdcBrokerIDType	BrokerID;
	///用户代码
	TSgitFtdcUserIDType	UserID;
	///交易中心代码
	TSgitFtdcDRIdentityIDType	DRIdentityID;
};

///经济公司是否有在本标示的交易权限
struct CSgitFtdcBrokerUserRightAssignField
{
	///应用单元代码
	TSgitFtdcBrokerIDType	BrokerID;
	///交易中心代码
	TSgitFtdcDRIdentityIDType	DRIdentityID;
	///能否交易
	TSgitFtdcBoolType	Tradeable;
};

///灾备交易转换报文
struct CSgitFtdcDRTransferField
{
	///原交易中心代码
	TSgitFtdcDRIdentityIDType	OrigDRIdentityID;
	///目标交易中心代码
	TSgitFtdcDRIdentityIDType	DestDRIdentityID;
	///原应用单元代码
	TSgitFtdcBrokerIDType	OrigBrokerID;
	///目标易用单元代码
	TSgitFtdcBrokerIDType	DestBrokerID;
};

//合约价位查询域
struct CSgitMBLQuotReq
{
	TSgitFtdcInstrumentIDType  StartContractID;     //起始合约号
	TSgitFtdcInstrumentIDType  EndContractID;       //结束合约号
	TSgitFtdcDirectionType     BsFlag;              //买卖标志
};

//合约价位域
struct CSgitMBLQuotData
{
	TSgitFtdcInstrumentIDType  ContractID;          //合约号
	TSgitFtdcDirectionType     BsFlag;              //买卖标志
	TSgitFtdcPriceType         Price;               //价格
	TSgitFtdcVolumeType        Qty;                 //数量
};

//订阅合约行情行情
struct CSgitSubQuotField
{
	TSgitFtdcInstrumentIDType  ContractID;     //合约号
};

#endif
