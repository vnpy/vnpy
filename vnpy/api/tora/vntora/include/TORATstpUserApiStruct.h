/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰信息科技有限公司
///@file TORATstpUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_TORA_TSTPCSTRUCT_H)
#define _TORA_TSTPCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpUserApiDataType.h"

/// fens用户信息
struct CTORATstpFensUserInfoField
{
		
	///登录账户
	TTORATstpLogInAccountType	LogInAccount;

	///登录账户类型
	TTORATstpLogInAccountTypeType	LogInAccountType;


};

/// 价格异常波动行情
struct CTORATstpEffectPriceMarketDataField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///最新价
	TTORATstpPriceType	LastPrice;

	///总成交数量
	TTORATstpLongVolumeType	TotalVolume;

	///成交金额
	TTORATstpMoneyType	Turnover;

	///最后修改时间
	TTORATstpTimeType	UpdateTime;

	///最后修改毫秒
	TTORATstpMillisecType	UpdateMillisec;


};

/// 数量异常波动行情
struct CTORATstpEffectVolumeMarketDataField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///最新价
	TTORATstpPriceType	LastPrice;

	///总成交数量
	TTORATstpLongVolumeType	TotalVolume;

	///成交金额
	TTORATstpMoneyType	Turnover;

	///最后修改时间
	TTORATstpTimeType	UpdateTime;

	///最后修改毫秒
	TTORATstpMillisecType	UpdateMillisec;


};

/// 资金流向数据行情
struct CTORATstpFundsFlowMarketDataField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///最后修改时间
	TTORATstpTimeType	UpdateTime;

	///最后修改毫秒
	TTORATstpMillisecType	UpdateMillisec;

	///散户买入金额
	TTORATstpMoneyType	RetailBuyTurnover;

	///散户买入数量
	TTORATstpLongVolumeType	RetailBuyVolume;

	///散户买入笔数
	TTORATstpLongVolumeType	RetailBuyAmount;

	///散户卖出金额
	TTORATstpMoneyType	RetailSellTurnover;

	///散户卖出数量
	TTORATstpLongVolumeType	RetailSellVolume;

	///散户卖出笔数
	TTORATstpLongVolumeType	RetailSellAmount;

	///中户买入金额
	TTORATstpMoneyType	MiddleBuyTurnover;

	///中户买入数量
	TTORATstpLongVolumeType	MiddleBuyVolume;

	///中户买入笔数
	TTORATstpLongVolumeType	MiddleBuyAmount;

	///中户卖出金额
	TTORATstpMoneyType	MiddleSellTurnover;

	///中户卖出数量
	TTORATstpLongVolumeType	MiddleSellVolume;

	///中户卖出笔数
	TTORATstpLongVolumeType	MiddleSellAmount;

	///大户买入金额
	TTORATstpMoneyType	LargeBuyTurnover;

	///大户买入数量
	TTORATstpLongVolumeType	LargeBuyVolume;

	///大户买入笔数
	TTORATstpLongVolumeType	LargeBuyAmount;

	///大户卖出金额
	TTORATstpMoneyType	LargeSellTurnover;

	///大户卖出数量
	TTORATstpLongVolumeType	LargeSellVolume;

	///大户卖出笔数
	TTORATstpLongVolumeType	LargeSellAmount;

	///机构买入金额
	TTORATstpMoneyType	InstitutionBuyTurnover;

	///机构买入数量
	TTORATstpLongVolumeType	InstitutionBuyVolume;

	///机构买入笔数
	TTORATstpLongVolumeType	InstitutionBuyAmount;

	///机构卖出金额
	TTORATstpMoneyType	InstitutionSellTurnover;

	///机构卖出数量
	TTORATstpLongVolumeType	InstitutionSellVolume;

	///机构卖出笔数
	TTORATstpLongVolumeType	InstitutionSellAmount;


};

/// 登录请求
struct CTORATstpReqUserLoginField
{
		
	///登录账户
	TTORATstpLogInAccountType	LogInAccount;

	///登录账户类型
	TTORATstpLogInAccountTypeType	LogInAccountType;

	///密码(密码认证时必填)
	TTORATstpPasswordType	Password;

	///用户端产品信息
	TTORATstpProductInfoType	UserProductInfo;

	///接口端产品信息
	TTORATstpProductInfoType	InterfaceProductInfo;

	///协议信息
	TTORATstpProtocolInfoType	ProtocolInfo;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///动态密码
	TTORATstpPasswordType	OneTimePassword;

	///终端IP地址
	TTORATstpIPAddressType	ClientIPAddress;

	///接口语言
	TTORATstpLangType	Lang;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///网关Mac地址
	TTORATstpMacAddressType	GWMacAddress;

	///网关内网IP地址
	TTORATstpIPAddressType	GWInnerIPAddress;

	///网关外网IP地址
	TTORATstpIPAddressType	GWOuterIPAddress;

	///经纪公司部门代码（以资金账号方式登录时必填）
	TTORATstpDepartmentIDType	DepartmentID;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;

	///认证方式(指纹认证时必填)
	TTORATstpAuthModeType	AuthMode;

	///设备标识(指纹认证时必填)
	TTORATstpDeviceIDType	DeviceID;

	///设备序列号(指纹认证时必填)
	TTORATstpDeviceSerialType	DeviceSerial;


};

/// 登录应答
struct CTORATstpRspUserLoginField
{
		
	///登录成功时间
	TTORATstpTimeType	LoginTime;

	///登录账户
	TTORATstpLogInAccountType	LogInAccount;

	///登录账户类型
	TTORATstpLogInAccountTypeType	LogInAccountType;

	///交易系统名称
	TTORATstpSystemNameType	SystemName;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///最大报单引用
	TTORATstpOrderRefType	MaxOrderRef;

	///私有流长度
	TTORATstpVolumeType	PrivateFlowCount;

	///公有流长度
	TTORATstpVolumeType	PublicFlowCount;

	///交易发生的日期
	TTORATstpDateType	TradingDay;

	///用户代码
	TTORATstpUserIDType	UserID;

	///用户名称
	TTORATstpUserNameType	UserName;

	///用户类型
	TTORATstpUserTypeType	UserType;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///终端IP地址
	TTORATstpIPAddressType	ClientIPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;

	///通讯流量
	TTORATstpCommFluxType	CommFlux;


};

/// 响应信息
struct CTORATstpRspInfoField
{
		
	///错误代码
	TTORATstpErrorIDType	ErrorID;

	///错误信息
	TTORATstpErrorMsgType	ErrorMsg;


};

/// 用户登出
struct CTORATstpUserLogoutField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;


};

/// 强制交易员退出
struct CTORATstpForceUserLogoutField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;


};

/// 重置用户密码
struct CTORATstpUserPasswordUpdateField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;

	///旧密码
	TTORATstpPasswordType	OldPassword;

	///新密码
	TTORATstpPasswordType	NewPassword;


};

/// 请求录入设备序列
struct CTORATstpReqInputDeviceSerialField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;

	///设备标识
	TTORATstpDeviceIDType	DeviceID;

	///设备序列号
	TTORATstpDeviceSerialType	DeviceSerial;


};

/// 请求录入设备序列应答
struct CTORATstpRspInputDeviceSerialField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;


};

/// 激活用户
struct CTORATstpActivateUserField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;


};

/// 用户会话标识
struct CTORATstpVerifyUserPasswordField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;

	///密码
	TTORATstpPasswordType	Password;


};

/// 输入报单
struct CTORATstpInputOrderField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///投资者说明的对报单的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///用户代码
	TTORATstpUserIDType	UserID;

	///限价单或市价单
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///1．买2．卖
	TTORATstpDirectionType	Direction;

	///按字节表示各单个合约的开平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按字节表示各单个合约的组合套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///当成交量类型为MV时有效
	TTORATstpVolumeType	MinVolume;

	///强平原因
	TTORATstpForceCloseReasonType	ForceCloseReason;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///用户强评标志
	TTORATstpBoolType	UserForceClose;

	///互换单标志
	TTORATstpBoolType	IsSwapOrder;

	///一个交易所的编号
	TTORATstpExchangeIDType	ExchangeID;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///头寸类型
	TTORATstpCreditPositionTypeType	CreditPositionType;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///转入交易单元代码(仅在转托管操作时有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///委托方式
	TTORATstpOperwayType	Operway;

	///条件检查
	TTORATstpCondCheckType	CondCheck;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;


};

/// 报单
struct CTORATstpOrderField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///投资者说明的对报单的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///用户代码
	TTORATstpUserIDType	UserID;

	///限价单或市价单
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///1．买2．卖
	TTORATstpDirectionType	Direction;

	///按字节表示各单个合约的开平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按字节表示各单个合约的组合套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///当成交量类型为MV时有效
	TTORATstpVolumeType	MinVolume;

	///强平原因
	TTORATstpForceCloseReasonType	ForceCloseReason;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///本地报单顺序号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///合约在交易所的代码
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///交易所交易员代码
	TTORATstpTraderIDType	TraderID;

	///报单提交状态
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易发生的日期
	TTORATstpDateType	TradingDay;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///0．全部成交1．部分成交还在队列中2．部分成交不在队列中3．未成交还在队列中4．未成交不在队列中5．撤单
	TTORATstpOrderStatusType	OrderStatus;

	///0．普通1．报价派生2．组合派生
	TTORATstpOrderTypeType	OrderType;

	///报单完成数量
	TTORATstpVolumeType	VolumeTraded;

	///报单未完成数量
	TTORATstpVolumeType	VolumeTotal;

	///报单日期
	TTORATstpDateType	InsertDate;

	///委托时间
	TTORATstpTimeType	InsertTime;

	///撤销时间
	TTORATstpTimeType	CancelTime;

	///最后修改交易所交易员代码
	TTORATstpTraderIDType	ActiveTraderID;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
	TTORATstpSessionIDType	SessionID;

	///说明用户端使用的软件产品和版本号
	TTORATstpProductInfoType	UserProductInfo;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///用户强评标志
	TTORATstpBoolType	UserForceClose;

	///操作用户代码
	TTORATstpUserIDType	ActiveUserID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///头寸类型
	TTORATstpCreditPositionTypeType	CreditPositionType;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///转入交易单元代码(仅在转托管操作时有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///委托方式
	TTORATstpOperwayType	Operway;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///适当性控制业务类别
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///适当性控制通过标示
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///条件检查
	TTORATstpCondCheckType	CondCheck;

	///是否预埋
	TTORATstpBoolType	IsCacheOrder;

	///根据成交价格计算出的本笔成交的金额（不包含费用）
	TTORATstpMoneyType	Turnover;

	///回报附加浮点型数据信息
	TTORATstpFloatInfoType	RtnFloatInfo;

	///回报附加整型数据
	TTORATstpIntInfoType	RtnIntInfo;


};

/// 用户标识
struct CTORATstpUserRefField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;


};

/// 输入撤单操作
struct CTORATstpInputOrderActionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资者说明的对报单操作的唯一引用
	TTORATstpOrderRefType	OrderActionRef;

	///投资者说明的对报单的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
	TTORATstpSessionIDType	SessionID;

	///一个交易所的编号
	TTORATstpExchangeIDType	ExchangeID;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///操作标志
	TTORATstpActionFlagType	ActionFlag;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量变化
	TTORATstpVolumeType	VolumeChange;

	///用户代码
	TTORATstpUserIDType	UserID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///全系统的唯一报单编号。16位，1-2位为交易所标识，3-5位为经纪公司代码，6-8位为交易单元标识，后面8位为流水号。
	TTORATstpOrderLocalIDType	CancelOrderLocalID;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///委托方式
	TTORATstpOperwayType	Operway;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;


};

/// 报单操作
struct CTORATstpOrderActionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资者说明的对报单操作的唯一引用
	TTORATstpOrderRefType	OrderActionRef;

	///投资者说明的对报单的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
	TTORATstpSessionIDType	SessionID;

	///一个交易所的编号
	TTORATstpExchangeIDType	ExchangeID;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///操作标志
	TTORATstpActionFlagType	ActionFlag;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量变化
	TTORATstpVolumeType	VolumeChange;

	///操作日期
	TTORATstpDateType	ActionDate;

	///操作时间
	TTORATstpTimeType	ActionTime;

	///交易所交易员代码
	TTORATstpTraderIDType	TraderID;

	///本地报单编号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///操作本地编号
	TTORATstpOrderLocalIDType	ActionLocalID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///报单操作状态
	TTORATstpOrderActionStatusType	OrderActionStatus;

	///用户代码
	TTORATstpUserIDType	UserID;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///委托方式
	TTORATstpOperwayType	Operway;


};

/// 成交
struct CTORATstpTradeField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///成交编号
	TTORATstpTradeIDType	TradeID;

	///1.买2.卖
	TTORATstpDirectionType	Direction;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///合约在交易所的代码
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///1．开仓2．平今3．平昨4．强平
	TTORATstpOffsetFlagType	OffsetFlag;

	///1.投机2.套保
	TTORATstpHedgeFlagType	HedgeFlag;

	///成交价格
	TTORATstpPriceType	Price;

	///成交数量
	TTORATstpVolumeType	Volume;

	///成交日期
	TTORATstpDateType	TradeDate;

	///成交时间
	TTORATstpTimeType	TradeTime;

	///交易员在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpTraderIDType	TraderID;

	///本地报单顺序号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易发生的日期
	TTORATstpDateType	TradingDay;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///报单引用
	TTORATstpOrderRefType	OrderRef;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 市场状态
struct CTORATstpMarketStatusField
{
		
	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///市场状态
	TTORATstpMarketStatusType	MarketStatus;


};

/// 条件单录入域
struct CTORATstpInputCondOrderField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///买卖方向
	TTORATstpDirectionType	Direction;

	///条件单价格类型
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///条件单数量类型
	TTORATstpOrderVolumeTypeType	OrderVolumeType;

	///有效期类型
	TTORATstpTimeConditionType	TimeCondition;

	///成交量类型
	TTORATstpVolumeConditionType	VolumeCondition;

	///报单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///组合开平标志
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///组合投机套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///条件报单引用
	TTORATstpOrderRefType	CondOrderRef;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///报单编号
	TTORATstpCondOrderIDType	CondOrderID;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///委托方式
	TTORATstpOperwayType	Operway;

	///条件检查
	TTORATstpCondCheckType	CondCheck;

	///条件单触发条件
	TTORATstpContingentConditionType	ContingentCondition;

	///条件价
	TTORATstpPriceType	ConditionPrice;

	///价格浮动tick数,>0向上浮动,<0向下浮动,=0不浮动
	TTORATstpVolumeType	PriceTicks;

	///数量浮动倍数,必须>=0
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///相关前置编号
	TTORATstpFrontIDType	RelativeFrontID;

	///相关会话编号
	TTORATstpSessionIDType	RelativeSessionID;

	///相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	RelativeParam;

	///附加条件单触发条件
	TTORATstpContingentConditionType	AppendContingentCondition;

	///附加条件价
	TTORATstpPriceType	AppendConditionPrice;

	///附加相关前置编号
	TTORATstpFrontIDType	AppendRelativeFrontID;

	///附加相关会话编号
	TTORATstpSessionIDType	AppendRelativeSessionID;

	///附加相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	AppendRelativeParam;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;


};

/// 条件单域
struct CTORATstpConditionOrderField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///买卖方向
	TTORATstpDirectionType	Direction;

	///条件单价格类型
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///条件单数量类型
	TTORATstpOrderVolumeTypeType	OrderVolumeType;

	///有效期类型
	TTORATstpTimeConditionType	TimeCondition;

	///成交量类型
	TTORATstpVolumeConditionType	VolumeCondition;

	///报单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///组合开平标志
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///组合投机套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///条件报单引用
	TTORATstpOrderRefType	CondOrderRef;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///报单编号
	TTORATstpCondOrderIDType	CondOrderID;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///委托方式
	TTORATstpOperwayType	Operway;

	///条件检查
	TTORATstpCondCheckType	CondCheck;

	///条件单触发条件
	TTORATstpContingentConditionType	ContingentCondition;

	///条件价
	TTORATstpPriceType	ConditionPrice;

	///价格浮动tick数,>0向上浮动,<0向下浮动,=0不浮动
	TTORATstpVolumeType	PriceTicks;

	///数量浮动倍数,必须>=0
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///相关前置编号
	TTORATstpFrontIDType	RelativeFrontID;

	///相关会话编号
	TTORATstpSessionIDType	RelativeSessionID;

	///相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	RelativeParam;

	///附加条件单触发条件
	TTORATstpContingentConditionType	AppendContingentCondition;

	///附加条件价
	TTORATstpPriceType	AppendConditionPrice;

	///附加相关前置编号
	TTORATstpFrontIDType	AppendRelativeFrontID;

	///附加相关会话编号
	TTORATstpSessionIDType	AppendRelativeSessionID;

	///附加相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	AppendRelativeParam;

	///交易发生的日期
	TTORATstpDateType	TradingDay;

	///条件单状态
	TTORATstpCondOrderStatusType	CondOrderStatus;

	///报单日期
	TTORATstpDateType	InsertDate;

	///委托时间
	TTORATstpTimeType	InsertTime;

	///撤销时间
	TTORATstpTimeType	CancelTime;

	///撤销用户
	TTORATstpUserIDType	CancelUser;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
	TTORATstpSessionIDType	SessionID;

	///说明用户端使用的软件产品和版本号
	TTORATstpProductInfoType	UserProductInfo;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///适当性控制业务类别
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///适当性控制通过标识
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///触发日期
	TTORATstpDateType	ActiveDate;

	///触发时间
	TTORATstpTimeType	ActiveTime;


};

/// 条件单操作录入
struct CTORATstpInputCondOrderActionField
{
		
	///请求编号
	TTORATstpRequestIDType	RequestID;

	///一个交易所的编号
	TTORATstpExchangeIDType	ExchangeID;

	///条件单操作引用
	TTORATstpOrderRefType	CondOrderActionRef;

	///条件单引用
	TTORATstpOrderRefType	CondOrderRef;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///报单编号
	TTORATstpCondOrderIDType	CondOrderID;

	///操作标志
	TTORATstpActionFlagType	ActionFlag;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///条件单撤单编号
	TTORATstpCondOrderIDType	CancelCondOrderID;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///委托方式
	TTORATstpOperwayType	Operway;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;


};

/// 查询集中交易系统资金请求
struct CTORATstpReqInquiryJZFundField
{
		
	///资金账户
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 查询集中交易系统资金响应
struct CTORATstpRspInquiryJZFundField
{
		
	///资金账户
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///可用金额
	TTORATstpMoneyType	UsefulMoney;

	///可取额度
	TTORATstpMoneyType	FetchLimit;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 资金转移
struct CTORATstpInputTransferFundField
{
		
	///资金账户
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///申请流水号
	TTORATstpExternalSerialType	ApplySerial;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///转账金额
	TTORATstpMoneyType	Amount;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///银行代码(银证转账时必填)
	TTORATstpBankIDType	BankID;

	///资金密码(证券转银行时必填)
	TTORATstpPasswordType	AccountPassword;

	///银行密码(银行转证券时必填)
	TTORATstpPasswordType	BankPassword;


};

/// 仓位转移
struct CTORATstpInputTransferPositionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///申请流水号
	TTORATstpExternalSerialType	ApplySerial;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///数量
	TTORATstpVolumeType	Volume;

	///转移持仓类型
	TTORATstpTransferPositionTypeType	TransferPositionType;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;


};

/// 资金转移回报
struct CTORATstpTransferFundField
{
		
	///转账流水号(后台编号)
	TTORATstpSerialType	FundSerial;

	///申请流水号
	TTORATstpExternalSerialType	ApplySerial;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///币种代码
	TTORATstpCurrencyIDType	CurrencyID;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///资金账户当日出入金金额
	TTORATstpMoneyType	Amount;

	///转移状态
	TTORATstpTransferStatusType	TransferStatus;

	///操作人员
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作时间
	TTORATstpTimeType	OperateTime;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///签约银行账户
	TTORATstpBankAccountIDType	BankAccountID;

	///银行代码
	TTORATstpBankIDType	BankID;


};

/// 仓位转移回报
struct CTORATstpTransferPositionField
{
		
	///仓位转移流水号
	TTORATstpSerialType	PositionSerial;

	///申请流水号
	TTORATstpExternalSerialType	ApplySerial;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易日
	TTORATstpDateType	TradingDay;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///转移持仓类型
	TTORATstpTransferPositionTypeType	TransferPositionType;

	///昨日仓位转入转出数量。
	TTORATstpVolumeType	HistoryVolume;

	///今日买卖仓位转入转出数量。
	TTORATstpVolumeType	TodayBSVolume;

	///今日申赎仓位转入转出数量。
	TTORATstpVolumeType	TodayPRVolume;

	///转移状态：0：正常，1：已冲正
	TTORATstpTransferStatusType	TransferStatus;

	///操作人员
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作时间
	TTORATstpTimeType	OperateTime;


};

/// 订阅行情
struct CTORATstpSpecificSecurityField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;


};

/// 担保品转移请求
struct CTORATstpInputTransferCollateralField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///申请流水号
	TTORATstpExternalSerialType	ApplySerial;

	///担保品划转方向
	TTORATstpCollateralDirectionType	CollateralDirection;

	///数量
	TTORATstpVolumeType	Volume;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///委托方式
	TTORATstpOperwayType	Operway;


};

/// 查询银行账户余额请求
struct CTORATstpReqInquiryBankAccountFundField
{
		
	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///银行代码
	TTORATstpBankIDType	BankID;

	///银行密码
	TTORATstpPasswordType	BankPassword;


};

/// 查询银行账户余额响应
struct CTORATstpRspInquiryBankAccountFundField
{
		
	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///银行代码
	TTORATstpBankIDType	BankID;

	///签约银行账户
	TTORATstpBankAccountIDType	BankAccountID;

	///账户余额
	TTORATstpMoneyType	Balance;


};

/// Lev2行情
struct CTORATstpLev2MarketDataField
{
		
	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///行情交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///时间戳
	TTORATstpTimeStampType	DataTimeStamp;

	///昨收盘
	TTORATstpPriceType	PreClosePrice;

	///今开盘
	TTORATstpPriceType	OpenPrice;

	///成交笔数
	TTORATstpLongVolumeType	NumTrades;

	///成交总量
	TTORATstpLongVolumeType	TotalVolumeTrade;

	///成交总金额
	TTORATstpMoneyType	TotalValueTrade;

	///委托买入总量（只有上交所推送）
	TTORATstpLongVolumeType	TotalBidVolume;

	///加权平均委托买价格（只有上交所推送）
	TTORATstpPriceType	AvgBidPrice;

	///委托卖出总量（只有上交所推送）
	TTORATstpLongVolumeType	TotalAskVolume;

	///加权平均委托卖价格（只有上交所推送）
	TTORATstpPriceType	AvgAskPrice;

	///最高价
	TTORATstpPriceType	HighestPrice;

	///最低价
	TTORATstpPriceType	LowestPrice;

	///现价
	TTORATstpPriceType	LastPrice;

	///申买价一
	TTORATstpPriceType	BidPrice1;

	///申买量一
	TTORATstpLongVolumeType	BidVolume1;

	///申卖价一
	TTORATstpPriceType	AskPrice1;

	///申卖量一
	TTORATstpLongVolumeType	AskVolume1;

	///申卖价二
	TTORATstpPriceType	AskPrice2;

	///申卖量二
	TTORATstpLongVolumeType	AskVolume2;

	///申卖价三
	TTORATstpPriceType	AskPrice3;

	///申卖量三
	TTORATstpLongVolumeType	AskVolume3;

	///申买价二
	TTORATstpPriceType	BidPrice2;

	///申买量二
	TTORATstpLongVolumeType	BidVolume2;

	///申买价三
	TTORATstpPriceType	BidPrice3;

	///申买量三
	TTORATstpLongVolumeType	BidVolume3;

	///申卖价四
	TTORATstpPriceType	AskPrice4;

	///申卖量四
	TTORATstpLongVolumeType	AskVolume4;

	///申卖价五
	TTORATstpPriceType	AskPrice5;

	///申卖量五
	TTORATstpLongVolumeType	AskVolume5;

	///申买价四
	TTORATstpPriceType	BidPrice4;

	///申买量四
	TTORATstpLongVolumeType	BidVolume4;

	///申买价五
	TTORATstpPriceType	BidPrice5;

	///申买量五
	TTORATstpLongVolumeType	BidVolume5;

	///申卖价六
	TTORATstpPriceType	AskPrice6;

	///申卖量六
	TTORATstpLongVolumeType	AskVolume6;

	///申卖价七
	TTORATstpPriceType	AskPrice7;

	///申卖量七
	TTORATstpLongVolumeType	AskVolume7;

	///申买价六
	TTORATstpPriceType	BidPrice6;

	///申买量六
	TTORATstpLongVolumeType	BidVolume6;

	///申买价七
	TTORATstpPriceType	BidPrice7;

	///申买量七
	TTORATstpLongVolumeType	BidVolume7;

	///申卖价八
	TTORATstpPriceType	AskPrice8;

	///申卖量八
	TTORATstpLongVolumeType	AskVolume8;

	///申卖价九
	TTORATstpPriceType	AskPrice9;

	///申卖量九
	TTORATstpLongVolumeType	AskVolume9;

	///申买价八
	TTORATstpPriceType	BidPrice8;

	///申买量八
	TTORATstpLongVolumeType	BidVolume8;

	///申买价九
	TTORATstpPriceType	BidPrice9;

	///申买量九
	TTORATstpLongVolumeType	BidVolume9;

	///申买价十
	TTORATstpPriceType	BidPrice10;

	///申买量十
	TTORATstpLongVolumeType	BidVolume10;

	///申卖价十
	TTORATstpPriceType	AskPrice10;

	///申卖量十
	TTORATstpLongVolumeType	AskVolume10;

	///附加信息1
	TTORATstpIntInfoType	Info1;

	///附加信息2
	TTORATstpIntInfoType	Info2;

	///附加信息3
	TTORATstpIntInfoType	Info3;

	///涨停板价(只有深圳行情有效)
	TTORATstpPriceType	UpperLimitPrice;

	///跌停板价(只有深圳行情有效)
	TTORATstpPriceType	LowerLimitPrice;

	///今收盘价(只有上海行情有效)
	TTORATstpPriceType	ClosePrice;

	///行情产品实时状态
	TTORATstpMDSecurityStatType	MDSecurityStat;


};

/// Lev2指数行情
struct CTORATstpLev2IndexField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///时间戳
	TTORATstpTimeStampType	DataTimeStamp;

	///前收盘指数
	TTORATstpPriceType	PreCloseIndex;

	///今开盘指数
	TTORATstpPriceType	OpenIndex;

	///最高指数
	TTORATstpPriceType	HighIndex;

	///最低指数
	TTORATstpPriceType	LowIndex;

	///最新指数
	TTORATstpPriceType	LastIndex;

	///参与计算相应指数的成交金额（元
	TTORATstpMoneyType	Turnover;

	///参与计算相应指数的交易数量(手)
	TTORATstpLongVolumeType	TotalVolumeTraded;

	///附加信息1
	TTORATstpIntInfoType	Info1;

	///附加信息2
	TTORATstpIntInfoType	Info2;

	///附加信息3
	TTORATstpIntInfoType	Info3;


};

/// Lev2逐笔成交
struct CTORATstpLev2TransactionField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///时间戳
	TTORATstpTimeStampType	TradeTime;

	///成交价格
	TTORATstpPriceType	TradePrice;

	///成交数量
	TTORATstpLongVolumeType	TradeVolume;

	///成交类别
	TTORATstpExecTypeType	ExecType;

	///主序号
	TTORATstpSequenceNoType	MainSeq;

	///子序号
	TTORATstpLongSequenceType	SubSeq;

	///买方委托序号
	TTORATstpLongSequenceType	BuyNo;

	///卖方委托序号
	TTORATstpLongSequenceType	SellNo;

	///附加信息1
	TTORATstpIntInfoType	Info1;

	///附加信息2
	TTORATstpIntInfoType	Info2;

	///附加信息3
	TTORATstpIntInfoType	Info3;


};

/// Lev2逐笔委托
struct CTORATstpLev2OrderDetailField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///时间戳
	TTORATstpTimeStampType	OrderTime;

	///委托价格
	TTORATstpPriceType	Price;

	///委托数量
	TTORATstpLongVolumeType	Volume;

	///委托方向
	TTORATstpLSideType	Side;

	///订单类别
	TTORATstpLOrderTypeType	OrderType;

	///主序号
	TTORATstpSequenceNoType	MainSeq;

	///子序号
	TTORATstpSequenceNoType	SubSeq;

	///附加信息1
	TTORATstpIntInfoType	Info1;

	///附加信息2
	TTORATstpIntInfoType	Info2;

	///附加信息3
	TTORATstpIntInfoType	Info3;


};

/// 回传交易数据
struct CTORATstpUploadTradeDataField
{
		
	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///交易日
	TTORATstpDateType	TradingDay;

	///是否强制回传。0=否;1=是
	TTORATstpBoolType	bForce;


};

/// 输入指定交易登记&撤销
struct CTORATstpInputDesignationRegistrationField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///0．指定登记 1．指定撤销
	TTORATstpDesignationTypeType	DesignationType;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;


};

/// 输入深证转托管
struct CTORATstpInputCustodyTransferField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///|．新注册转托管请求 ~．转托管撤单
	TTORATstpCustodyTransferTypeType	CustodyTransferType;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///转入交易单元代码
	TTORATstpPbuIDType	TransfereePbuID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///全系统的唯一报单编号。16位，1-2位为交易所标识，3-5位为经纪公司代码，6-8位为交易单元标识，后面8位为流水号。
	TTORATstpOrderLocalIDType	OrignalOrderLocalID;

	///全系统的唯一报单编号。16位，1-2位为交易所标识，3-5位为经纪公司代码，6-8位为交易单元标识，后面8位为流水号。
	TTORATstpOrderLocalIDType	OrderLocalID;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///硬盘序列号
	TTORATstpHDSerialType	HDSerial;


};

/// 交易成交集中度
struct CTORATstpInquiryTradeConcentrationField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资者成交量/成交总量
	TTORATstpRatioType	ConcentrationRatio1;

	///投资者成交金额/成交总金额
	TTORATstpRatioType	ConcentrationRatio2;


};

/// 查询文件委托请求
struct CTORATstpInquiryFileOrderField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///委托起始流水号
	TTORATstpSequenceNoType	OrderSerialBeg;

	///委托结束流水号
	TTORATstpSequenceNoType	OrderSerialEnd;

	///委托提交状态
	TTORATstpCommitStatusType	CommitStatus;


};

/// 文件委托
struct CTORATstpFileOrderField
{
		
	///请求编号
	TTORATstpRequestIDType	RequestID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///报单引用
	TTORATstpOrderRefType	OrderRef;

	///文件报单类别
	TTORATstpFileOrderTypeType	FileOrderType;

	///买卖方向
	TTORATstpDirectionType	Direction;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///委托方式
	TTORATstpOperwayType	Operway;

	///报单操作引用
	TTORATstpOrderRefType	OrderActionRef;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///委托检查
	TTORATstpCondCheckType	CondCheck;

	///委托流水号
	TTORATstpSequenceNoType	OrderSerial;

	///文件委托提交状态
	TTORATstpCommitStatusType	CommitStatus;

	///文件委托状态信息
	TTORATstpStatusMsgType	StatusMsg;

	///委托时间戳
	TTORATstpBigTimeStampType	TimeStamp;


};

/// 查询应答域
struct CTORATstpQryRspInfoField
{
		
	///结束标识
	TTORATstpEndFlagType	EndFlag;

	///错误代码
	TTORATstpErrorIDType	ErrorID;

	///错误信息
	TTORATstpErrorMsgType	ErrorMsg;


};

/// 文件委托复核请求
struct CTORATstpReviewFileOrderField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///委托起始流水号
	TTORATstpSequenceNoType	OrderSerialBeg;

	///委托结束流水号
	TTORATstpSequenceNoType	OrderSerialEnd;


};

/// 文件提交信息
struct CTORATstpCommitInfoField
{
		
	///委托流水号
	TTORATstpSequenceNoType	OrderSerial;

	///文件委托提交状态
	TTORATstpCommitStatusType	CommitStatus;

	///文件委托状态信息
	TTORATstpStatusMsgType	StatusMsg;


};

/// 请求插入交易通知
struct CTORATstpReqInsTradingNoticeField
{
		
	///通知流水号
	TTORATstpSerialType	NoticeSerial;

	///通知日期
	TTORATstpDateType	InsertDate;

	///通知时间
	TTORATstpTimeType	InsertTime;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///通知消息内容
	TTORATstpContentType	Content;

	///操作员
	TTORATstpUserIDType	OperatorID;


};

/// 交易通知
struct CTORATstpTradingNoticeField
{
		
	///通知流水号
	TTORATstpSerialType	NoticeSerial;

	///通知日期
	TTORATstpDateType	InsertDate;

	///通知时间
	TTORATstpTimeType	InsertTime;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///通知消息内容
	TTORATstpContentType	Content;

	///操作员
	TTORATstpUserIDType	OperatorID;


};

/// 装载文件委托
struct CTORATstpLoadFileOrderField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///是否需要复核
	TTORATstpBoolType	bReview;


};

/// 文件委托信息
struct CTORATstpFileOrderInfoField
{
		
	///请求编号
	TTORATstpRequestIDType	RequestID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///报单引用
	TTORATstpOrderRefType	OrderRef;

	///文件报单类别
	TTORATstpFileOrderTypeType	FileOrderType;

	///买卖方向
	TTORATstpDirectionType	Direction;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///委托方式
	TTORATstpOperwayType	Operway;

	///报单操作引用
	TTORATstpOrderRefType	OrderActionRef;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///委托检查
	TTORATstpCondCheckType	CondCheck;

	///委托流水号
	TTORATstpSequenceNoType	OrderSerial;

	///文件委托提交状态
	TTORATstpCommitStatusType	CommitStatus;

	///文件委托状态信息
	TTORATstpStatusMsgType	StatusMsg;


};

/// 查询最大报单量请求
struct CTORATstpReqInquiryMaxOrderVolumeField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///买卖方向
	TTORATstpDirectionType	Direction;

	///限价单或市价单
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///按字节表示各单个合约的开平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按字节表示各单个合约的组合套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///转入交易单元代码(仅在转托管操作时有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///最大委托手数
	TTORATstpVolumeType	MaxVolume;


};

/// 查询最大报单量应答
struct CTORATstpRspInquiryMaxOrderVolumeField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///买卖方向
	TTORATstpDirectionType	Direction;

	///限价单或市价单
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///按字节表示各单个合约的开平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按字节表示各单个合约的组合套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///转入交易单元代码(仅在转托管操作时有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///最大委托手数
	TTORATstpVolumeType	MaxVolume;


};

/// 外围系统仓位调拨流水明细
struct CTORATstpPeripheryPositionTransferDetailField
{
		
	///仓位调拨系统流水号
	TTORATstpIntSerialType	PositionSerial;

	///仓位调拨请求流水号
	TTORATstpIntSerialType	ApplySerial;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///仓位调拨方向
	TTORATstpTransferDirectionType	TransferDirection;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///现货系统交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///今日买卖仓位转入转出数量
	TTORATstpVolumeType	TodayBSPos;

	///今日申赎仓位转入数量
	TTORATstpVolumeType	TodayPRPos;

	///昨日仓位转入数量
	TTORATstpVolumeType	HistoryPos;

	///交易日期
	TTORATstpDateType	TradingDay;

	///仓位调拨原因
	TTORATstpTransferReasonType	TransferReason;

	///转移状态
	TTORATstpTransferStatusType	TransferStatus;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作时间
	TTORATstpTimeType	OperateTime;

	///冲正日期
	TTORATstpDateType	RepealDate;

	///冲正时间
	TTORATstpTimeType	RepealTime;

	///冲正原因
	TTORATstpTransferReasonType	RepealReason;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;


};

/// 查询历史委托
struct CTORATstpQryHistoryOrderField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///起始日期
	TTORATstpDateType	BegDate;

	///结束日期
	TTORATstpDateType	EndDate;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///每页记录数
	TTORATstpVolumeType	PageCount;

	///页定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 查询历史响应信息
struct CTORATstpQryHistoryRspInfoField
{
		
	///错误代码
	TTORATstpErrorIDType	ErrorID;

	///错误信息
	TTORATstpErrorMsgType	ErrorMsg;

	///分页是否结束
	TTORATstpBoolType	bPageEnd;


};

/// 历史委托信息
struct CTORATstpHistoryOrderField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///投资者说明的对报单的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///用户代码
	TTORATstpUserIDType	UserID;

	///限价单或市价单
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///1．买2．卖
	TTORATstpDirectionType	Direction;

	///按字节表示各单个合约的开平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按字节表示各单个合约的组合套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///限价单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///当成交量类型为MV时有效
	TTORATstpVolumeType	MinVolume;

	///强平原因
	TTORATstpForceCloseReasonType	ForceCloseReason;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///本地报单顺序号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///合约在交易所的代码
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///交易所交易员代码
	TTORATstpTraderIDType	TraderID;

	///报单提交状态
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易发生的日期
	TTORATstpDateType	TradingDay;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///0．全部成交1．部分成交还在队列中2．部分成交不在队列中3．未成交还在队列中4．未成交不在队列中5．撤单
	TTORATstpOrderStatusType	OrderStatus;

	///0．普通1．报价派生2．组合派生
	TTORATstpOrderTypeType	OrderType;

	///报单完成数量
	TTORATstpVolumeType	VolumeTraded;

	///报单未完成数量
	TTORATstpVolumeType	VolumeTotal;

	///报单日期
	TTORATstpDateType	InsertDate;

	///委托时间
	TTORATstpTimeType	InsertTime;

	///撤销时间
	TTORATstpTimeType	CancelTime;

	///最后修改交易所交易员代码
	TTORATstpTraderIDType	ActiveTraderID;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
	TTORATstpSessionIDType	SessionID;

	///说明用户端使用的软件产品和版本号
	TTORATstpProductInfoType	UserProductInfo;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///用户强评标志
	TTORATstpBoolType	UserForceClose;

	///操作用户代码
	TTORATstpUserIDType	ActiveUserID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///头寸类型
	TTORATstpCreditPositionTypeType	CreditPositionType;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///转入交易单元代码(仅在转托管操作时有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///委托方式
	TTORATstpOperwayType	Operway;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///适当性控制业务类别
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///适当性控制通过标示
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///条件检查
	TTORATstpCondCheckType	CondCheck;

	///是否预埋
	TTORATstpBoolType	IsCacheOrder;

	///根据成交价格计算出的本笔成交的金额（不包含费用）
	TTORATstpMoneyType	Turnover;

	///回报附加浮点型数据信息
	TTORATstpFloatInfoType	RtnFloatInfo;

	///回报附加整型数据
	TTORATstpIntInfoType	RtnIntInfo;

	///页定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 查询历史成交
struct CTORATstpQryHistoryTradeField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///起始日期
	TTORATstpDateType	BegDate;

	///结束日期
	TTORATstpDateType	EndDate;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///每页记录数
	TTORATstpVolumeType	PageCount;

	///页定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 历史成交信息
struct CTORATstpHistoryTradeField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///成交编号
	TTORATstpTradeIDType	TradeID;

	///1.买2.卖
	TTORATstpDirectionType	Direction;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///合约在交易所的代码
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///1．开仓2．平今3．平昨4．强平
	TTORATstpOffsetFlagType	OffsetFlag;

	///1.投机2.套保
	TTORATstpHedgeFlagType	HedgeFlag;

	///成交价格
	TTORATstpPriceType	Price;

	///成交数量
	TTORATstpVolumeType	Volume;

	///成交日期
	TTORATstpDateType	TradeDate;

	///成交时间
	TTORATstpTimeType	TradeTime;

	///交易员在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpTraderIDType	TraderID;

	///本地报单顺序号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易发生的日期
	TTORATstpDateType	TradingDay;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///报单引用
	TTORATstpOrderRefType	OrderRef;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///页定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 查询交易所
struct CTORATstpQryExchangeField
{
		
	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 交易所
struct CTORATstpExchangeField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所名称
	TTORATstpNameType	ExchangeName;

	///交易日
	TTORATstpDateType	TradingDay;


};

/// 查询PBU
struct CTORATstpQryPBUField
{
		
	///交易单元代码
	TTORATstpPbuIDType	PbuID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;


};

/// PBU
struct CTORATstpPBUField
{
		
	///交易单元代码
	TTORATstpPbuIDType	PbuID;

	///交易单元名称
	TTORATstpNameType	PbuName;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;


};

/// 查询实时行情
struct CTORATstpQryMarketDataField
{
		
	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 实时行情
struct CTORATstpMarketDataField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约在交易所的代码
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///最新价
	TTORATstpPriceType	LastPrice;

	///昨收盘
	TTORATstpPriceType	PreClosePrice;

	///今开盘
	TTORATstpPriceType	OpenPrice;

	///最高价
	TTORATstpPriceType	HighestPrice;

	///最低价
	TTORATstpPriceType	LowestPrice;

	///数量
	TTORATstpLongVolumeType	Volume;

	///成交金额
	TTORATstpMoneyType	Turnover;

	///持仓量
	TTORATstpLargeVolumeType	OpenInterest;

	///涨停板价
	TTORATstpPriceType	UpperLimitPrice;

	///跌停板价
	TTORATstpPriceType	LowerLimitPrice;

	///最后修改时间
	TTORATstpTimeType	UpdateTime;

	///最后修改毫秒
	TTORATstpMillisecType	UpdateMillisec;

	///申买价一
	TTORATstpPriceType	BidPrice1;

	///申买量一
	TTORATstpLongVolumeType	BidVolume1;

	///申卖价一
	TTORATstpPriceType	AskPrice1;

	///申卖量一
	TTORATstpLongVolumeType	AskVolume1;

	///申买价二
	TTORATstpPriceType	BidPrice2;

	///申买量二
	TTORATstpLongVolumeType	BidVolume2;

	///申卖价二
	TTORATstpPriceType	AskPrice2;

	///申卖量二
	TTORATstpLongVolumeType	AskVolume2;

	///申买价三
	TTORATstpPriceType	BidPrice3;

	///申买量三
	TTORATstpLongVolumeType	BidVolume3;

	///申卖价三
	TTORATstpPriceType	AskPrice3;

	///申卖量三
	TTORATstpLongVolumeType	AskVolume3;

	///申买价四
	TTORATstpPriceType	BidPrice4;

	///申买量四
	TTORATstpLongVolumeType	BidVolume4;

	///申卖价四
	TTORATstpPriceType	AskPrice4;

	///申卖量四
	TTORATstpLongVolumeType	AskVolume4;

	///申买价五
	TTORATstpPriceType	BidPrice5;

	///申买量五
	TTORATstpLongVolumeType	BidVolume5;

	///申卖价五
	TTORATstpPriceType	AskPrice5;

	///申卖量五
	TTORATstpLongVolumeType	AskVolume5;

	///合约名称
	TTORATstpSecurityNameType	SecurityName;

	///成交笔数
	TTORATstpLongVolumeType	TradingCount;

	///市盈率1
	TTORATstpRatioType	PERatio1;

	///市盈率2
	TTORATstpRatioType	PERatio2;

	///价格升跌1
	TTORATstpPriceType	PriceUpDown1;

	///价格升跌2
	TTORATstpPriceType	PriceUpDown2;

	///收盘价
	TTORATstpPriceType	ClosePrice;

	///证券实时状态
	TTORATstpMDSecurityStatType	MDSecurityStat;

	///是否风险警示标志0否1是
	TTORATstpBoolType	HWFlag;


};

/// 查询证券信息
struct CTORATstpQrySecurityField
{
		
	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///合约在交易所的代码
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///证券市场中的具体品种，如上海股票
	TTORATstpProductIDType	ProductID;


};

/// 证券信息
struct CTORATstpSecurityField
{
		
	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约名称
	TTORATstpSecurityNameType	SecurityName;

	///合约在交易所的代码
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///产品代码
	TTORATstpProductIDType	ProductID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///申报单位
	TTORATstpOrderUnitType	OrderUnit;

	///买入交易单位
	TTORATstpTradingUnitType	BuyTradingUnit;

	///卖出交易单位
	TTORATstpTradingUnitType	SellTradingUnit;

	///市价单买最大下单量
	TTORATstpVolumeType	MaxMarketOrderBuyVolume;

	///市价单买最小下单量
	TTORATstpVolumeType	MinMarketOrderBuyVolume;

	///限价单买最大下单量
	TTORATstpVolumeType	MaxLimitOrderBuyVolume;

	///限价单买最小下单量
	TTORATstpVolumeType	MinLimitOrderBuyVolume;

	///市价单卖最大下单量
	TTORATstpVolumeType	MaxMarketOrderSellVolume;

	///市价单卖最小下单量
	TTORATstpVolumeType	MinMarketOrderSellVolume;

	///限价单卖最大下单量
	TTORATstpVolumeType	MaxLimitOrderSellVolume;

	///限价单卖最小下单量
	TTORATstpVolumeType	MinLimitOrderSellVolume;

	///数量乘数
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///最小变动价位
	TTORATstpPriceTickType	PriceTick;

	///上市日
	TTORATstpDateType	OpenDate;

	///持仓类型
	TTORATstpPositionTypeType	PositionType;

	///面值
	TTORATstpParValueType	ParValue;

	///证券状态
	TTORATstpSecurityStatusType	SecurityStatus;

	///债券应计利息
	TTORATstpInterestType	BondInterest;

	///折算率
	TTORATstpRatioType	ConversionRate;

	///是否担保品
	TTORATstpBoolType	IsCollateral;


};

/// 查询ETF清单信息
struct CTORATstpQryETFFileField
{
		
	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///ETF二级市场交易代码
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF一级市场申赎代码
	TTORATstpSecurityIDType	ETFCreRedSecurityID;


};

/// ETF清单信息
struct CTORATstpETFFileField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///ETF交易代码
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF申赎代码
	TTORATstpSecurityIDType	ETFCreRedSecurityID;

	///最小申购赎回单位份数
	TTORATstpVolumeType	CreationRedemptionUnit;

	///最大现金替代比例
	TTORATstpRatioType	Maxcashratio;

	///是否允许申购
	TTORATstpBoolType	CreationStatus;

	///是否允许赎回
	TTORATstpBoolType	RedemptionStatus;

	///预估现金差额
	TTORATstpMoneyType	EstimateCashComponent;

	///前一交易日现金差额
	TTORATstpMoneyType	CashComponent;

	///前一交易日基金单位净值
	TTORATstpMoneyType	NAV;

	///前一交易日申赎基准单位净值
	TTORATstpMoneyType	NAVperCU;

	///当日申购赎回基准单位的红利金额
	TTORATstpMoneyType	DividendPerCU;


};

/// 查询ETF成份证券信息
struct CTORATstpQryETFBasketField
{
		
	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///ETF二级市场交易代码
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF篮子中的成分证券代码
	TTORATstpSecurityIDType	SecurityID;


};

/// ETF成份证券信息
struct CTORATstpETFBasketField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///ETF交易代码
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF成份证券代码
	TTORATstpSecurityIDType	SecurityID;

	///证券简称
	TTORATstpSecurityNameType	SecurityName;

	///证券数量
	TTORATstpVolumeType	Volume;

	///替代标志
	TTORATstpETFCurrenceReplaceStatusType	ETFCurrenceReplaceStatus;

	///溢价比例
	TTORATstpRatioType	Premium;

	///申购替代金额
	TTORATstpMoneyType	CreationReplaceAmount;

	///赎回替代金额
	TTORATstpMoneyType	RedemptionReplaceAmount;

	///挂牌市场
	TTORATstpListingMarketType	Market;


};

/// 查询经纪公司部门信息
struct CTORATstpQryDepartmentInfoField
{
		
	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 经纪公司部门信息
struct CTORATstpDepartmentInfoField
{
		
	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///经纪公司部门名称
	TTORATstpNameType	DepartmentName;


};

/// 查询新股信息
struct CTORATstpQryIPOInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///申购代码
	TTORATstpSecurityIDType	SecurityID;


};

/// 新股信息
struct CTORATstpIPOInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///申购代码
	TTORATstpSecurityIDType	SecurityID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///产品代码
	TTORATstpProductIDType	ProductID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///网上申购上限
	TTORATstpVolumeType	OnlineLimit;

	///发行价格
	TTORATstpPriceType	Price;

	///币种代码
	TTORATstpCurrencyIDType	CurrencyID;

	///申购证券名称
	TTORATstpSecurityNameType	SecurityName;

	///新股证券代码
	TTORATstpSecurityIDType	UnderlyingSecurityID;

	///新股证券名称
	TTORATstpSecurityNameType	UnderlyingSecurityName;

	///网上申购最小数量
	TTORATstpVolumeType	OnlineMinVol;

	///网上申购单位数量
	TTORATstpVolumeType	OnlineVolUnit;


};

/// 查询BrokerUserFunction
struct CTORATstpQryBrokerUserFunctionField
{
		
	///交易用户代码
	TTORATstpUserIDType	UserID;


};

/// BrokerUserFunction
struct CTORATstpBrokerUserFunctionField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;

	///功能代码
	TTORATstpFunctionIDType	FunctionID;


};

/// 查询经纪公司用户与投资者关系
struct CTORATstpQryBUProxyField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易用户代码
	TTORATstpUserIDType	UserID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 经纪公司用户与投资者关系
struct CTORATstpBUProxyField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 查询User
struct CTORATstpQryUserField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;

	///用户类型
	TTORATstpUserTypeType	UserType;


};

/// User
struct CTORATstpUserField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;

	///用户名称
	TTORATstpUserNameType	UserName;

	///用户类型
	TTORATstpUserTypeType	UserType;

	///是否活跃
	TTORATstpBoolType	IsActive;

	///登录限制
	TTORATstpLoginLimitType	LoginLimit;


};

/// 查询投资者
struct CTORATstpQryInvestorField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;


};

/// 投资者
struct CTORATstpInvestorField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资者名称
	TTORATstpInvestorNameType	InvestorName;

	///证件类型
	TTORATstpIdCardTypeType	IdCardType;

	///证件号码
	TTORATstpIdCardNoType	IdCardNo;

	///联系电话
	TTORATstpTelephoneType	Telephone;

	///通讯地址
	TTORATstpAddressType	Address;

	///开户日期
	TTORATstpDateType	OpenDate;

	///手机
	TTORATstpMobileType	Mobile;

	///委托方式
	TTORATstpOperwaysType	Operways;

	///客户风险等级
	TTORATstpCRiskLevelType	CRiskLevel;

	///专业投资者类别
	TTORATstpProfInvestorTypeType	ProfInvestorType;


};

/// 查询交易编码
struct CTORATstpQryShareholderAccountField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///股东代码
	TTORATstpShareholderIDType	ShareholderID;

	///普通，信用，衍生品等
	TTORATstpClientIDTypeType	TradingCodeClass;


};

/// 交易编码
struct CTORATstpShareholderAccountField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///交易编码类型
	TTORATstpClientIDTypeType	ClientIDType;

	///市场代码
	TTORATstpMarketIDType	MarketID;


};

/// 查询投资单元
struct CTORATstpQryBusinessUnitField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;


};

/// 投资单元
struct CTORATstpBusinessUnitField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///投资单元名称
	TTORATstpBusinessUnitNameType	BusinessUnitName;


};

/// 查询投资单元与交易账户关系
struct CTORATstpQryBusinessUnitAndTradingAcctField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///证券市场中的具体品种，如上海股票
	TTORATstpProductIDType	ProductID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;


};

/// 投资单元与交易账户关系
struct CTORATstpBusinessUnitAndTradingAcctField
{
		
	///经纪公司代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///产品代码
	TTORATstpProductIDType	ProductID;

	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///资金账户代码
	TTORATstpCurrencyIDType	CurrencyID;

	///用户代码
	TTORATstpUserIDType	UserID;


};

/// 查询报单
struct CTORATstpQryOrderField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///是否可撤
	TTORATstpBoolType	IsCancel;


};

/// 查询撤单
struct CTORATstpQryOrderActionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///一个交易所的编号
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;


};

/// 查询成交
struct CTORATstpQryTradeField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约在系统中的编号
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///成交编号
	TTORATstpTradeIDType	TradeID;

	///Insert Time
	TTORATstpTimeType	TradeTimeStart;

	///Insert Time
	TTORATstpTimeType	TradeTimeEnd;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 查询资金账户
struct CTORATstpQryTradingAccountField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///资金账户
	TTORATstpAccountIDType	AccountID;

	///1：普通，2：信用，3：衍生品
	TTORATstpAccountTypeType	AccountType;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 资金账户
struct CTORATstpTradingAccountField
{
		
	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///可用资金
	TTORATstpMoneyType	Available;

	///可取资金
	TTORATstpMoneyType	WithdrawQuota;

	///币种代码
	TTORATstpCurrencyIDType	CurrencyID;

	///入金金额
	TTORATstpMoneyType	Deposit;

	///出金金额
	TTORATstpMoneyType	Withdraw;

	///冻结的保证金
	TTORATstpMoneyType	FrozenMargin;

	///冻结的资金
	TTORATstpMoneyType	FrozenCash;

	///冻结的手续费
	TTORATstpMoneyType	FrozenCommission;

	///当前保证金总额
	TTORATstpMoneyType	CurrMargin;

	///手续费
	TTORATstpMoneyType	Commission;

	///资金账户类型
	TTORATstpAccountTypeType	AccountType;

	///资金账户所属投资者代码
	TTORATstpInvestorIDType	AccountOwner;

	///部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///银行代码
	TTORATstpBankIDType	BankID;

	///银行账户
	TTORATstpBankAccountIDType	BankAccountID;


};

/// 查询投资者持仓
struct CTORATstpQryPositionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 投资者持仓
struct CTORATstpPositionField
{
		
	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///交易日
	TTORATstpDateType	TradingDay;

	///昨日持仓
	TTORATstpVolumeType	HistoryPos;

	///昨日持仓冻结
	TTORATstpVolumeType	HistoryPosFrozen;

	///今日买卖持仓
	TTORATstpVolumeType	TodayBSPos;

	///今日买卖持仓冻结
	TTORATstpVolumeType	TodayBSFrozen;

	///今日申赎持仓
	TTORATstpVolumeType	TodayPRPos;

	///今日申赎持仓冻结
	TTORATstpVolumeType	TodayPRFrozen;

	///持仓成本
	TTORATstpMoneyType	TotalPosCost;

	///今日拆分合并持仓
	TTORATstpVolumeType	TodaySMPos;

	///今日拆分合并持仓冻结
	TTORATstpVolumeType	TodaySMPosFrozen;

	///融资仓位
	TTORATstpVolumeType	MarginBuyPos;

	///融券仓位
	TTORATstpVolumeType	ShortSellPos;

	///上次余额(盘中不变)
	TTORATstpVolumeType	PrePosition;

	///股份可用
	TTORATstpVolumeType	AvailablePosition;

	///股份余额
	TTORATstpVolumeType	CurrentPosition;

	///最新价
	TTORATstpPriceType	LastPrice;


};

/// 查询基础交易费用
struct CTORATstpQryTradingFeeField
{
		
	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 基础交易费用
struct CTORATstpTradingFeeField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///产品代码
	TTORATstpProductIDType	ProductID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///业务类别
	TTORATstpBizClassType	BizClass;

	///印花税按金额收取比例
	TTORATstpRatioType	StampTaxRatioByAmt;

	///印花税按面值收取比例
	TTORATstpRatioType	StampTaxRatioByPar;

	///印花税按笔收取金额
	TTORATstpMoneyType	StampTaxFeePerOrder;

	///印花税最低收取金额
	TTORATstpMoneyType	StampTaxFeeMin;

	///印花税最高收取金额
	TTORATstpMoneyType	StampTaxFeeMax;

	///过户费按金额收取比例
	TTORATstpRatioType	TransferRatioByAmt;

	///过户费按面值收取比例
	TTORATstpRatioType	TransferRatioByPar;

	///过户费按笔收取金额
	TTORATstpMoneyType	TransferFeePerOrder;

	///过户费最低收取金额
	TTORATstpMoneyType	TransferFeeMin;

	///过户费最高收取金额
	TTORATstpMoneyType	TransferFeeMax;

	///经手费按金额收取比例
	TTORATstpRatioType	HandlingRatioByAmt;

	///经手费按面值收取比例
	TTORATstpRatioType	HandlingRatioByPar;

	///经手费按笔收取金额
	TTORATstpMoneyType	HandlingFeePerOrder;

	///经手费最低收取金额
	TTORATstpMoneyType	HandlingFeeMin;

	///经手费最高收取金额
	TTORATstpMoneyType	HandlingFeeMax;

	///证管费按金额收取比例
	TTORATstpRatioType	RegulateRatioByAmt;

	///证管费按面值收取比例
	TTORATstpRatioType	RegulateRatioByPar;

	///证管费按笔收取金额
	TTORATstpMoneyType	RegulateFeePerOrder;

	///证管费最低收取金额
	TTORATstpMoneyType	RegulateFeeMin;

	///证管费最高收取金额
	TTORATstpMoneyType	RegulateFeeMax;

	///过户费按数量收取金额
	TTORATstpMoneyType	TransferFeeByVolume;

	///经手费按数量收取金额
	TTORATstpMoneyType	HandlingFeeByVolume;

	///结算费按金额收取比例
	TTORATstpRatioType	SettlementRatioByAmt;

	///结算费按面值收取比例
	TTORATstpRatioType	SettlementRatioByPar;

	///结算费按笔收取金额
	TTORATstpMoneyType	SettlementFeePerOrder;

	///结算费按数量收取金额
	TTORATstpMoneyType	SettlementFeeByVolume;

	///结算费最低收取金额
	TTORATstpMoneyType	SettlementFeeMin;

	///结算费最高收取金额
	TTORATstpMoneyType	SettlementFeeMax;


};

/// 查询佣金费率
struct CTORATstpQryInvestorTradingFeeField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 佣金费率
struct CTORATstpInvestorTradingFeeField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///产品代码
	TTORATstpProductIDType	ProductID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///业务类别
	TTORATstpBizClassType	BizClass;

	///佣金类型
	TTORATstpBrokerageTypeType	BrokerageType;

	///佣金按金额收取比例
	TTORATstpRatioType	RatioByAmt;

	///佣金按面值收取比例
	TTORATstpRatioType	RatioByPar;

	///佣金按笔收取金额
	TTORATstpMoneyType	FeePerOrder;

	///佣金最低收取金额
	TTORATstpMoneyType	FeeMin;

	///佣金最高收取金额
	TTORATstpMoneyType	FeeMax;

	///佣金按数量收取金额
	TTORATstpMoneyType	FeeByVolume;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 查询新股申购额度
struct CTORATstpQryIPOQuotaField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;


};

/// 新股申购额度
struct CTORATstpIPOQuotaField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///可申购额度
	TTORATstpLongVolumeType	MaxVolume;


};

/// 查询市场
struct CTORATstpQryMarketField
{
		
	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;


};

/// 市场
struct CTORATstpMarketField
{
		
	///市场代码
	TTORATstpMarketIDType	MarketID;

	///市场名称
	TTORATstpNameType	MarketName;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;


};

/// 查询报单明细资金
struct CTORATstpQryOrderFundDetailField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///系统报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 报单明细资金
struct CTORATstpOrderFundDetailField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约代码
	TTORATstpSecurityIDType	InstrumentID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易日
	TTORATstpDateType	TradingDay;

	///系统报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///初始冻结金额
	TTORATstpMoneyType	TotalFrozen;

	///总费用
	TTORATstpMoneyType	TotalFee;

	///印花税
	TTORATstpMoneyType	StampTaxFee;

	///经手费
	TTORATstpMoneyType	HandlingFee;

	///过户费
	TTORATstpMoneyType	TransferFee;

	///证管费
	TTORATstpMoneyType	RegulateFee;

	///佣金
	TTORATstpMoneyType	BrokerageFee;

	///结算费
	TTORATstpMoneyType	SettlementFee;

	///初始冻结费用合计
	TTORATstpMoneyType	TotalFeeFrozen;

	///报单初始冻结金额
	TTORATstpMoneyType	OrderAmount;


};

/// 查询资金转移流水
struct CTORATstpQryFundTransferDetailField
{
		
	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 资金转移流水
struct CTORATstpFundTransferDetailField
{
		
	///转账流水号
	TTORATstpSerialType	FundSerial;

	///申请流水号
	TTORATstpExternalSerialType	ApplySerial;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///出入金金额
	TTORATstpMoneyType	Amount;

	///转移状态
	TTORATstpTransferStatusType	TransferStatus;

	///操作来源
	TTORATstpOperateSourceType	OperateSource;

	///操作人员
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作时间
	TTORATstpTimeType	OperateTime;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///银行代码
	TTORATstpBankIDType	BankID;

	///签约银行账户
	TTORATstpBankAccountIDType	BankAccountID;


};

/// 查询持仓转移流水
struct CTORATstpQryPositionTransferDetailField
{
		
	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;


};

/// 持仓转移流水
struct CTORATstpPositionTransferDetailField
{
		
	///流水号
	TTORATstpSerialType	PositionSerial;

	///申请流水号
	TTORATstpExternalSerialType	ApplySerial;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易日期
	TTORATstpDateType	TradingDay;

	///转移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///转移持仓类型
	TTORATstpTransferPositionTypeType	TransferPositionType;

	///转移状态
	TTORATstpTransferStatusType	TransferStatus;

	///昨日仓位数量
	TTORATstpVolumeType	HistoryVolume;

	///今日买卖仓位数量
	TTORATstpVolumeType	TodayBSVolume;

	///今日申赎仓位数量
	TTORATstpVolumeType	TodayPRVolume;

	///操作人员
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作时间
	TTORATstpTimeType	OperateTime;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;


};

/// 查询投资者质押持仓
struct CTORATstpQryPledgePositionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 投资者质押持仓
struct CTORATstpPledgePositionField
{
		
	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///交易日
	TTORATstpDateType	TradingDay;

	///昨日质押持仓
	TTORATstpVolumeType	HisPledgePos;

	///昨日质押持仓冻结
	TTORATstpVolumeType	HisPledgePosFrozen;

	///今日入库的质押持仓
	TTORATstpVolumeType	TodayPledgePos;

	///今日入库的质押持仓冻结
	TTORATstpVolumeType	TodayPledgePosFrozen;

	///昨日质押入库的现券总量
	TTORATstpVolumeType	PreTotalPledgePos;

	///昨日质押入库的现券可用数量
	TTORATstpVolumeType	preAvailablePledgePos;


};

/// 查询证券质押信息
struct CTORATstpQryPledgeInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;


};

/// 证券质押信息
struct CTORATstpPledgeInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///质押申报代码
	TTORATstpSecurityIDType	PledgeOrderID;

	///标准券代码
	TTORATstpSecurityIDType	StandardBondID;

	///是否可入库
	TTORATstpBoolType	AllowPledgeIn;

	///是否可出库
	TTORATstpBoolType	AllowPledgeOut;

	///标准券折算率/折算值
	TTORATstpRatioType	ConversionRate;

	///每次可以入库的最小交易单位
	TTORATstpTradingUnitType	PledgeInTradingUnit;

	///每次可以出库的最小交易单位
	TTORATstpTradingUnitType	PledgeOutTradingUnit;

	///证券可以入库的最大数量
	TTORATstpVolumeType	PledgeInVolMax;

	///证券可以入库的最小数量
	TTORATstpVolumeType	PledgeInVolMin;

	///证券可以出库的最大数量
	TTORATstpVolumeType	PledgeOutVolMax;

	///证券可以出库的最小数量
	TTORATstpVolumeType	PledgeOutVolMin;

	///当日质押入库的质押券是否能出库
	TTORATstpBoolType	IsTodayToPlegeOut;

	///是否可撤单
	TTORATstpBoolType	IsCancelOrder;


};

/// 查询可转债信息
struct CTORATstpQryConversionBondInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;


};

/// 可转债信息
struct CTORATstpConversionBondInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///转股申报代码
	TTORATstpSecurityIDType	ConvertOrderID;

	///转股价格
	TTORATstpPriceType	ConvertPrice;

	///每次可以转股最小交易单位
	TTORATstpTradingUnitType	ConvertVolUnit;

	///证券可以转股的最大数量
	TTORATstpVolumeType	ConvertVolMax;

	///证券可以转股的最小数量
	TTORATstpVolumeType	ConvertVolMin;

	///转股开始日期
	TTORATstpDateType	BeginDate;

	///转股截至日期
	TTORATstpDateType	EndDate;

	///是否可撤单
	TTORATstpBoolType	IsSupportCancel;


};

/// 查询债券回售信息
struct CTORATstpQryBondPutbackInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;


};

/// 债券回售信息
struct CTORATstpBondPutbackInfoField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///回售申报代码
	TTORATstpSecurityIDType	PutbackOrderID;

	///回售价格
	TTORATstpPriceType	PutbackPrice;

	///每次可以回售最小交易单位
	TTORATstpTradingUnitType	PutbackVolUnit;

	///债券可以回售的最大数量
	TTORATstpVolumeType	PutbackVolMax;

	///债券可以回售的最小数量
	TTORATstpVolumeType	PutbackVolMin;

	///回售开始日期
	TTORATstpDateType	BeginDate;

	///回售截至日期
	TTORATstpDateType	EndDate;

	///是否可撤单
	TTORATstpBoolType	IsSupportCancel;


};

/// 查询投资者标准券额度
struct CTORATstpQryStandardBondPositionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 投资者标准券额度
struct CTORATstpStandardBondPositionField
{
		
	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///交易日
	TTORATstpDateType	TradingDay;

	///标准券可用额度
	TTORATstpPositionVolumeType	AvailablePosition;

	///标准券可用额度冻结
	TTORATstpPositionVolumeType	AvailablePosFrozen;

	///标准券额度总量
	TTORATstpPositionVolumeType	TotalPosition;


};

/// 查询指定交易登记&撤销报单
struct CTORATstpQryDesignationRegistrationField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///全系统的唯一报单编号。16位，1-2位为交易所标识，3-5位为经纪公司代码，6-8位为交易单元标识，后面8位为流水号。
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 指定交易登记&撤销报单
struct CTORATstpDesignationRegistrationField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///买卖方向
	TTORATstpDesignationTypeType	DesignationType;

	///本地报单编号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///交易单元代码
	TTORATstpPbuIDType	PbuID;

	///报单提交状态
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易日
	TTORATstpDateType	TradingDay;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///报单状态
	TTORATstpOrderStatusType	OrderStatus;

	///报单日期
	TTORATstpDateType	InsertDate;

	///委托时间
	TTORATstpTimeType	InsertTime;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 深证转托管报单表
struct CTORATstpQryCustodyTransferField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///目前该字段存放的是上证所和深圳的股东代码。
	TTORATstpShareholderIDType	ShareholderID;

	///全系统的唯一报单编号。16位，1-2位为交易所标识，3-5位为经纪公司代码，6-8位为交易单元标识，后面8位为流水号。
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;


};

/// 转托管报单表
struct CTORATstpCustodyTransferField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///转托管类型
	TTORATstpCustodyTransferTypeType	CustodyTransferType;

	///本地报单编号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///客户代码
	TTORATstpShareholderIDType	ShareholderID;

	///交易单元代码
	TTORATstpPbuIDType	PbuID;

	///报单提交状态
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易日
	TTORATstpDateType	TradingDay;

	///报单编号
	TTORATstpOrderSysIDType	OrderSysID;

	///报单状态
	TTORATstpOrderStatusType	OrderStatus;

	///报单日期
	TTORATstpDateType	InsertDate;

	///委托时间
	TTORATstpTimeType	InsertTime;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///币种
	TTORATstpCurrencyIDType	CurrencyID;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///转入交易单元代码
	TTORATstpPbuIDType	TransfereePbuID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///本地撤单编号,被主动撤单的转托管的原始编号
	TTORATstpOrderLocalIDType	OrignalOrderLocalID;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///撤销时间
	TTORATstpTimeType	CancelTime;

	///撤销交易单元代码
	TTORATstpPbuIDType	ActiveTraderID;

	///撤销操作员
	TTORATstpUserIDType	ActiveUserID;


};

/// 查询实时特别行情
struct CTORATstpQrySpecialMarketDataField
{
		
	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 实时特别行情
struct CTORATstpSpecialMarketDataField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///证券名称
	TTORATstpSecurityNameType	SecurityName;

	///移动平均价
	TTORATstpPriceType	MovingAvgPrice;

	///移动平均价的采样数量
	TTORATstpVolumeType	MovingAvgPriceSamplingNum;

	///最后修改时间
	TTORATstpTimeType	UpdateTime;

	///最后修改毫秒
	TTORATstpMillisecType	UpdateMillisec;


};

/// 查询未到期债券质押回购委托
struct CTORATstpQryPrematurityRepoOrderField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市场，如沪A、沪B市场
	TTORATstpMarketIDType	MarketID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///报单编号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///证券品种代码
	TTORATstpProductIDType	ProductID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///报单类别
	TTORATstpDirectionType	Direction;

	///成交编号
	TTORATstpTradeIDType	TradeID;


};

/// 未到期债券质押回购委托
struct CTORATstpPrematurityRepoOrderField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///成交日期
	TTORATstpDateType	TradeDay;

	///到期日期
	TTORATstpDateType	ExpireDay;

	///报单编号
	TTORATstpOrderLocalIDType	OrderLocalID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///证券名称
	TTORATstpSecurityNameType	SecurityName;

	///证券品种代码
	TTORATstpProductIDType	ProductID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///报单类别
	TTORATstpDirectionType	Direction;

	///成交数量
	TTORATstpVolumeType	VolumeTraded;

	///成交价格
	TTORATstpPriceType	Price;

	///成交金额
	TTORATstpMoneyType	Turnover;

	///成交编号
	TTORATstpTradeIDType	TradeID;

	///购回应收金额
	TTORATstpMoneyType	RepoTotalMoney;

	///利息金额
	TTORATstpMoneyType	InterestAmount;


};

/// 查询股东参数
struct CTORATstpQryShareholderParamField
{
		
	///市场代码
	TTORATstpMarketIDType	MarketID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///普通，信用，衍生品等
	TTORATstpClientIDTypeType	TradingCodeClass;

	///产品类别
	TTORATstpProductIDType	ProductID;

	///证券类别
	TTORATstpSecurityTypeType	SecurityType;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///参数类型
	TTORATstpParamTypeType	ParamType;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;


};

/// 股东参数
struct CTORATstpShareholderParamField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///市场代码
	TTORATstpMarketIDType	MarketID;

	///交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///账户类型
	TTORATstpClientIDTypeType	TradingCodeClass;

	///证券品种
	TTORATstpProductIDType	ProductID;

	///证券类别
	TTORATstpSecurityTypeType	SecurityType;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///股东参数类型
	TTORATstpParamTypeType	ParamType;

	///股东参数值
	TTORATstpParameterCharValType	ParamValue;


};

/// 查询外围系统仓位调拨流水
struct CTORATstpQryPeripheryPositionTransferDetailField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///现货系统交易账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///仓位调拨方向
	TTORATstpTransferDirectionType	TransferDirection;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 查询投资者条件单限制参数
struct CTORATstpQryInvestorCondOrderLimitParamField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;


};

/// 投资者条件单限制参数
struct CTORATstpInvestorCondOrderLimitParamField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///最大条件单数
	TTORATstpVolumeType	MaxCondOrderLimitCnt;

	///当前条件单数
	TTORATstpVolumeType	CurrCondOrderCnt;


};

/// 查询条件单
struct CTORATstpQryCondOrderField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码，目前支持 SSE(上海证券交易所)和SZSE(深圳证券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
	TTORATstpShareholderIDType	ShareholderID;

	///报单编号
	TTORATstpCondOrderIDType	CondOrderID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;


};

/// 条件单
struct CTORATstpCondOrderField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///买卖方向
	TTORATstpDirectionType	Direction;

	///条件单价格类型
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///条件单数量类型
	TTORATstpOrderVolumeTypeType	OrderVolumeType;

	///有效期类型
	TTORATstpTimeConditionType	TimeCondition;

	///成交量类型
	TTORATstpVolumeConditionType	VolumeCondition;

	///报单价格
	TTORATstpPriceType	LimitPrice;

	///报单数量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///组合开平标志
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///组合投机套保标志
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///条件报单引用
	TTORATstpOrderRefType	CondOrderRef;

	///资金账户代码
	TTORATstpAccountIDType	AccountID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///条件报单编号
	TTORATstpCondOrderIDType	CondOrderID;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///委托方式
	TTORATstpOperwayType	Operway;

	///条件检查
	TTORATstpCondCheckType	CondCheck;

	///触发条件
	TTORATstpContingentConditionType	ContingentCondition;

	///条件价
	TTORATstpPriceType	ConditionPrice;

	///价格浮动tick数
	TTORATstpVolumeType	PriceTicks;

	///数量浮动倍数
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///相关前置编号
	TTORATstpFrontIDType	RelativeFrontID;

	///相关会话编号
	TTORATstpSessionIDType	RelativeSessionID;

	///相关条件参数
	TTORATstpRelativeCondParamType	RelativeParam;

	///附加触发条件
	TTORATstpContingentConditionType	AppendContingentCondition;

	///附加条件价
	TTORATstpPriceType	AppendConditionPrice;

	///附加相关前置编号
	TTORATstpFrontIDType	AppendRelativeFrontID;

	///附加相关会话编号
	TTORATstpSessionIDType	AppendRelativeSessionID;

	///附加相关条件参数
	TTORATstpRelativeCondParamType	AppendRelativeParam;

	///交易日
	TTORATstpDateType	TradingDay;

	///条件单状态
	TTORATstpCondOrderStatusType	CondOrderStatus;

	///报单日期
	TTORATstpDateType	InsertDate;

	///委托时间
	TTORATstpTimeType	InsertTime;

	///撤销时间
	TTORATstpTimeType	CancelTime;

	///撤销用户
	TTORATstpUserIDType	CancelUser;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///用户端产品信息
	TTORATstpProductInfoType	UserProductInfo;

	///状态信息
	TTORATstpErrorMsgType	StatusMsg;

	///经纪公司部门代码
	TTORATstpDepartmentIDType	DepartmentID;

	///适当性控制业务类别
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///适当性控制通过标示
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///触发日期
	TTORATstpDateType	ActiveDate;

	///触发时间
	TTORATstpTimeType	ActiveTime;


};

/// 查询条件单撤单
struct CTORATstpQryCondOrderActionField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///一个交易所的编号
	TTORATstpExchangeIDType	ExchangeID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;


};

/// 条件单撤单
struct CTORATstpCondOrderActionField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///请求编号
	TTORATstpRequestIDType	RequestID;

	///条件单操作引用
	TTORATstpOrderRefType	CondOrderActionRef;

	///条件单引用
	TTORATstpOrderRefType	CondOrderRef;

	///前置编号
	TTORATstpFrontIDType	FrontID;

	///会话编号
	TTORATstpSessionIDType	SessionID;

	///条件单编号
	TTORATstpCondOrderIDType	CondOrderID;

	///操作标志
	TTORATstpActionFlagType	ActionFlag;

	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///合约代码
	TTORATstpSecurityIDType	SecurityID;

	///用户代码
	TTORATstpUserIDType	UserID;

	///条件单撤单编号
	TTORATstpCondOrderIDType	CancelCondOrderID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///MAC地址
	TTORATstpMacAddressType	MacAddress;

	///终端信息
	TTORATstpTerminalInfoType	TerminalInfo;

	///长字符串附加信息
	TTORATstpBigsInfoType	BInfo;

	///短字符串附加信息
	TTORATstpShortsInfoType	SInfo;

	///整形附加信息
	TTORATstpIntInfoType	IInfo;

	///委托方式
	TTORATstpOperwayType	Operway;

	///投资单元代码
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股东账户代码
	TTORATstpShareholderIDType	ShareholderID;

	///操作日期
	TTORATstpDateType	ActionDate;

	///操作时间
	TTORATstpTimeType	ActionTime;


};

/// 查询BrokerUserRole
struct CTORATstpQryBrokerUserRoleField
{
		
	///角色编号
	TTORATstpRoleIDType	RoleID;


};

/// BrokerUserRole
struct CTORATstpBrokerUserRoleField
{
		
	///角色编号
	TTORATstpRoleIDType	RoleID;

	///角色描述
	TTORATstpRoleDescriptionType	RoleDescription;

	///功能权限集合
	TTORATstpFunctionsType	Functions;


};

/// 查询BrokerUserRoleAssignment
struct CTORATstpQryBrokerUserRoleAssignmentField
{
		
	///交易用户代码
	TTORATstpUserIDType	UserID;


};

/// BrokerUserRoleAssignment
struct CTORATstpBrokerUserRoleAssignmentField
{
		
	///用户代码
	TTORATstpUserIDType	UserID;

	///角色编号
	TTORATstpRoleIDType	RoleID;

	///角色描述
	TTORATstpRoleDescriptionType	RoleDescription;


};

/// 查询交易通知
struct CTORATstpQryTradingNoticeField
{
		
	///投资者代码
	TTORATstpInvestorIDType	InvestorID;

	///Insert Date
	TTORATstpDateType	InsertDateStart;

	///Insert Date
	TTORATstpDateType	InsertDateEnd;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;


};

/// 查询新股申购配号结果
struct CTORATstpQryIPONumberResultField
{
		
	///申购代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///股东代码
	TTORATstpShareholderIDType	ShareholderID;


};

/// 新股申购配号结果
struct CTORATstpIPONumberResultField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///日期
	TTORATstpDateType	Day;

	///申购证券名称
	TTORATstpSecurityNameType	SecurityName;

	///股东代码
	TTORATstpShareholderIDType	ShareholderID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///起始配号
	TTORATstpIPONumberIDType	BeginNumberID;

	///配号数量
	TTORATstpVolumeType	Volume;


};

/// 查询新股申购中签结果
struct CTORATstpQryIPOMatchNumberResultField
{
		
	///申购代码
	TTORATstpSecurityIDType	SecurityID;

	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///股东代码
	TTORATstpShareholderIDType	ShareholderID;

	///中签配号
	TTORATstpIPONumberIDType	MatchNumberID;


};

/// 新股申购中签结果
struct CTORATstpIPOMatchNumberResultField
{
		
	///交易所代码
	TTORATstpExchangeIDType	ExchangeID;

	///证券代码
	TTORATstpSecurityIDType	SecurityID;

	///日期
	TTORATstpDateType	Day;

	///申购证券名称
	TTORATstpSecurityNameType	SecurityName;

	///股东代码
	TTORATstpShareholderIDType	ShareholderID;

	///证券类别代码
	TTORATstpSecurityTypeType	SecurityType;

	///中签配号
	TTORATstpIPONumberIDType	MatchNumberID;

	///此中签号拥有的证券数量
	TTORATstpVolumeType	Volume;

	///申购价格
	TTORATstpPriceType	Price;

	///申购金额
	TTORATstpMoneyType	Amout;


};

#endif