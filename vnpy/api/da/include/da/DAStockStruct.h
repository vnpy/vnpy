/////////////////////////////////////////////////////////////////////////
/// DriectAccess Trade Engine
/// Copyright (C) Shanghai DirectAccess Technology Co., Ltd.
/// Last Modify 2019/3/18
/// Define Stock Struct
/// Author (c) Wang Jian Quan (Franklin)
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "DADataType.h"

// 错误描述
struct CStockRspInfoField 
{
	TDAIntType			ErrorID;							// 错误码
	TDAStringType		ErrorMsg;							// 错误描述
};
// 用户登录请求
struct CStockReqUserLoginField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		UserPwd;							// 用户密码
	TDAStringType		UserType;							// 用户类型
	TDAStringType		MacAddress;							// MAC地址
	TDAStringType		ComputerName;						// 计算机名
	TDAStringType		SoftwareName;						// 软件名称
	TDAStringType		SoftwareVersion;					// 软件版本号
	TDAStringType		AuthorCode;							// 授权码
	TDAStringType		ErrorDescription;					// 错误信息
};
// 用户登录返回
struct CStockRspAccountField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		UserName;							// 用户名    
	TDAStringType		UserType;							// 用户类型             
	TDAStringType		LoginPwd;							// 登录密码             
	TDAStringType		AccountNo;							// 资金账号              
	TDAStringType		TradePwd;							// 交易密码             
	TDAStringType		IsSimulation;						// 是否模拟用户              
	TDAStringType		FrontendIp;							// 前置机IP地址              
	TDAStringType		FrontendPort;						// 前置机端口号            
	TDAStringType		CurrencyNo;							// 帐户币种           
	TDAStringType		UserState;							// 用户状态 C消户 U在用 D冻结         
	TDAStringType		SelAll;								// 是否可以卖空期权             
	TDAStringType		Strategy;							// 是否可以下自定义策略单              
	TDAStringType		Inner;								// 是否可以下国内单             
	TDAStringType		YingSun;							// 是否可以使用止损止盈和条件单功能          
	TDAStringType		ChaoDan;							// 是否可以使用炒单手功能             
	TDAStringType		Option;								// 是否可以交易期权：0             
	TDAStringType		CmeMarket;							// 是否可以获取CME行情：0              
	TDAStringType		CmeCOMEXMarket;						// 是否可以获取CME_COMEX行情               
	TDAStringType		CmeNYMEXMarket;						// 是否可以获取CME_NYMEX行情               
	TDAStringType		CmeCBTMarket;						// 是否可以获取CME_CBT行情               
	TDAStringType		IceUSMarket;						// 是否可以获取ICE US行情              
	TDAStringType		IceECMarket;						// 是否可以获取ICE EC行情             
	TDAStringType		IceEFMarket;						// 是否可以获取ICE EF行情             
	TDAStringType		CanTradeStockHK;					// 是否可以交易港股             
	TDAStringType		CanTradeStockAM;					// 是否可以交易美股            
	TDAStringType		MultiLogin;							// 是否可以多处登录          
	TDAStringType		SellStockHK;						// 是否可以卖空港股              
	TDAStringType		SellStockAM;						// 是否可以卖空美股                
	TDAStringType		CanTradeStockKRX;					// 是否可以交易韩股               
	TDAStringType		HkexMarket;							// 是否可以获取期货港交所HKEX行情：0：不可以；1：可以（不使用优惠行情）；2：境内使用优惠行情；3：境外使用优惠行情 mantis1080 mantis393           
	TDAStringType		IdNumber;							// 用户身份证（股票传身份证类型，只有类型为1时才能选88的优惠行情；期货传身份证号码，15位或18位是国内客户）    
	TDAStringType		HkexMarketFee;						// 港交所行情收费金额（为0时表示在豁免期，大于0表示开始收费）       
	TDAStringType		IsProfessional;						// CME行情权限是否是专业版（1：是；0：否）  
	TDAStringType		IsOverSea;							// 是否境外登录       
	TDAStringType		IsFirstLogin;						// 是否新设备初次登录 
	TDAStringType		UserMobile;							// 用户手机号 
	TDAStringType		HasSetQA;							// 是否已经设置了密保问题答案 
	TDAStringType		CanTradeStockSGXQ;					// 是否可以交易新加坡股      
	TDAStringType		ExistMac;							// 是否已经绑定过设备mac地址：1：是；0 or other：不是   
	TDAStringType		RatioINE;							// 上海能源可取资金系数          
	TDAStringType		EurexMarket;						// 是否可以获取Eurex行情：0：不可以；1：可以（亚太区优惠）；2：可以（非专业）；3：可以（专业投资者）；4：不可以，需提示（亚太区以外使用亚太区优惠行情）   
	TDAStringType		HkexIsOverMaxTerminal;				// 是否超过最大终端数:0:未超过,非0超过      
	TDAStringType		HkexOverMoney;						// 港交所超过终端数收费      
	TDAStringType		CanTradeStockAU;					// 是否可交易澳股      
	TDAStringType		NyFlag;								// 能源标示
};
// 用户登出请求
struct CStockReqUserLogoutField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		ErrorDescription;					// 错误信息
};
// 新增订单请求
struct CStockReqOrderInsertField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		UserType;							// 用户类型：1：一般用户；2：机构通用户；
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		LocalNo;							// 本地编号
	TDAStringType		TradePwd;							// 交易密码
	TDAStringType		IsRiskOrder;						// 用户下单类型：C或是空客户下单；D：是del下单 R：强平下单（风控）；Y：盈损单；T：条件单
	TDAStringType		ExchangeCode;						// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		BuySale;							// 买还是卖：1=buy 2=sell
	TDAStringType		AddReduce;							// 开仓还是平仓：1=开仓 2=平仓，3=平今
	TDAStringType		OrderNumber;						// 下单数
	TDAStringType		OrderPrice;							// 下单价格
	TDAStringType		TradeType;							// 交易方式：1=regular 2=FOK 3=IOC
	TDAStringType		PriceType;							// 定单类型：1=限价单, 2=市价单，3=限价止损（stop to limit），4=止损（stop to market）
	TDAStringType		HtsType;							// 跨期合约下单： "STARTEGY";自定义策略下单："SELFDEFINE"
	TDAStringType		ForceID;							// 强平编号
	TDAStringType		TriggerPrice;						// 触发价格
	TDAStringType		ValidDate;							// 有效日期（1=当日有效, 2=永久有效（GTC），3=OPG，4=IOC，5=FOK，6=GTD，7=ATC，8=FAK）
	TDAStringType		StrategyId;							// 策略ID 20130726 add
	TDAStringType		MaxShow;							// 显示委托量 20150803 add 必须小于委托量
	TDAStringType		MinQty;								// 最小成交量 20150901 add 必须小于等于委托量 有效日期=4IOC时 MaxShow>=1小于委托量时是FOK，等于委托量时是FAK
	TDAStringType		ErrorDescription;					// 错误信息
};
// 新增订单返回
struct CStockRspOrderInsertField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		SystemNo;							// 系统编号
	TDAStringType		LocalNo;							// 本地编号
	TDAStringType		OrderNo;							// 定单号
	TDAStringType		OrigOrderNo;						// 原定单号
	TDAStringType		OrderMethod;						// 下单方式：1：定单；2：改单；3：撤单
	TDAStringType		AcceptType;							// （废弃）
	TDAStringType		ExchangeCode;						// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		BuySale;							// 买还是卖：1=buy 2=sell
	TDAStringType		OrderNumber;						// 下单数
	TDAStringType		OrderPrice;							// 下单价格
	TDAStringType		FilledNumber;						// 已成交数
	TDAStringType		FilledPrice;						// 成交均价
	TDAStringType		TradeType;							// 交易方式：1=regular 2=FOK 3=IOC
	TDAStringType		PriceType;							// 定单类型：1=限价单, 2=市价单，3=限价止损（stop to limit），4=止损（stop to market）
	TDAStringType		HtsType;							// 0=regular 1=HTS
	TDAStringType		OrderDate;							// 下单日期
	TDAStringType		OrderTime;							// 下单时间
	TDAStringType		ErrorCode;							// 错误代码
	TDAStringType		OrderState;							// 订单状态（1：已请求；2：已排队；3：部分成交；4：完全成交；5：已撤余单；6：已撤单；7：指令失败；8：待送出；9：待更改；A：待撤单）
	TDAStringType		IsRiskOrder;						// 用户下单类型：C或是空客户下单；D：是del下单 R：强平下单（风控）；Y：盈损单；T：条件单
	TDAStringType		CancelUserId;						// 撤单的用户标识
	TDAStringType		TriggerPrice;						// 触发价格
	TDAStringType		ValidDate;							// 有效日期（1=当日有效, 2=永久有效（GTC），3=OPG，4=IOC，5=FOK，6=GTD，7=ATC，8=FAK）
	TDAStringType		AddReduce;							// 开仓还是平仓：1=开仓 2=平仓，3=平今，4=平昨
	TDAStringType		StrategyId;							// 策略ID 20130726 add
	TDAStringType		MaxShow;							// 显示委托量 20150803 add 必须小于委托量
	TDAStringType		MinQty;								// 最小成交量 
	TDAStringType		ExchangeTime;						// 交易所返回时间
	TDAStringType		CancelTime;							// 撤单时间
};
// 修改订单请求
struct CStockReqOrderModifyField
{
	TDAStringType		SystemNo;							// 系统编号
	TDAStringType		UserId;								// 用户标识
	TDAStringType		UserType;							// 用户类型：1：一般用户；2：机构通用户；
	TDAStringType		LocalNo;							// 本地编号
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		TradePwd;							// 交易密码
	TDAStringType		OrderNo;							// 定单号
	TDAStringType		ExchangeCode;						// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		BuySale;							// 买还是卖：1=buy 2=sell
	TDAStringType		OrderNumber;						// 下单数
	TDAStringType		OrderPrice;							// 下单价格
	TDAStringType		FilledNumber;						// 已成交数 
	TDAStringType		ModifyNumber;						// 改单数 
	TDAStringType		ModifyPrice;						// 改单价格
	TDAStringType		TradeType;							// 交易方式：1=regular 2=FOK 3=IOC
	TDAStringType		PriceType;							// 价格类型：1=限价单, 2=市价单，3=限价止损（stop to limit），4=止损（stop to market）
	TDAStringType		IsRiskOrder;						// 用户下单类型：C或是空客户下单；D：是del下单 R：强平下单（风控）
	TDAStringType		TriggerPrice;						// 触发价格
	TDAStringType		ModifyTriggerPrice;					// 改单触发价格
	TDAStringType		ValidDate;							// 有效日期（1：当日有效；2：永久有效）
	TDAStringType		ErrorDescription;					// 错误信息
};
// 修改订单返回
typedef CStockRspOrderInsertField CStockRspOrderModifyField;
// 撤单请求
struct CStockReqOrderCancelField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		UserType;							// 用户类型：1：一般用户；2：机构通用户；
	TDAStringType		LocalNo;							// 本地编号
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		TradePwd;							// 交易密码
	TDAStringType		IsSimulation;						// 是否模拟用户：1：是；0 or other：不是
	TDAStringType		SystemNo;							// 系统编号
	TDAStringType		OrderNo;							// 定单号
	TDAStringType		ExchangeCode;						// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		BuySale;							// 买还是卖：1=buy 2=sell
	TDAStringType		OrderNumber;						// 下单数
	TDAStringType		OrderPrice;							// 下单价格
	TDAStringType		FilledNumber;						// 已成交数 
	TDAStringType		TradeType;							// 交易方式：1=regular 2=FOK 3=IOC
	TDAStringType		PriceType;							// 价格类型：1=limit order, 2=market order
	TDAStringType		HtsType;							// 0=regular 1=HTS
	TDAStringType		IsRiskOrder;						// 用户下单类型：C或是空客户下单；D：是del下单 R：强平下单（风控）
	TDAStringType		ErrorDescription;					// 错误信息
};
// 撤单返回
struct CStockRspOrderCancelField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		SystemNo;							// 系统编号
	TDAStringType		LocalNo;							// 本地号
	TDAStringType		OrderNo;							// 定单号
	TDAStringType		CancelNo;							// 撤单号
	TDAStringType		ExchangeCode;						// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		BuySale;							// 买还是卖：1=buy 2=sell
	TDAStringType		OrderNumber;						// 下单数
	TDAStringType		OrderPrice;							// 下单价格
	TDAStringType		FilledNumber;						// 已成交数
	TDAStringType		CancelNumber;						// 已撤单数
	TDAStringType		TradeType;							// 交易方式：1=regular 2=FOK 3=IOC
	TDAStringType		PriceType;							// 价格类型：1=limit order, 2=market order
	TDAStringType		HtsType;							// 0=regular 1=HTS
	TDAStringType		CancelDate;							// 撤单日期
	TDAStringType		CancelTime;							// 撤单时间
	TDAStringType		ErrorCode;							// 错误代码 改为存放订单状态（1：已请求；2：已排队；3：部分成交；4：完全成交；5：已撤余单；6：已撤单；7：指令失败；8：待送出；9：待更改；10：待撤单）
	TDAStringType		IsRiskOrder;						// 用户下单类型：C或是空客户下单；D：是del下单 R：强平下单（风控）
};
// 修改密码请求
struct CStockReqPasswordUpdateField
{
	TDAStringType		UserId;								// 用户代码
	TDAStringType		OldPassword;						// 用户原密码
	TDAStringType		NewPassword;						// 用户新密码
	TDAStringType		ErrorDescription;					// 错误信息
};
// 修改密码返回
struct CStockRspPasswordUpdateField
{
	TDAStringType		UserId;								// 用户代码
	TDAStringType		OldPassword;						// 用户原密码
	TDAStringType		NewPassword;						// 用户新密码
};
// 查询订单请求
struct CStockQryOrderField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		UserType;							// 用户类型：1：一般用户；2：机构通用户；
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		TradePwd;							// 交易密码
	TDAStringType		IsSimulation;						// 是否模拟用户：1：是；0 or other：不是
	TDAStringType		OrderNo;							// 取得指定订单号以后的定单
	TDAStringType		OrderDateTime;						// 取得指定订单时间以后的定单（格式：yyyy-MM-dd hh:mm:ss）
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询订单返回
struct CStockRspOrderField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		SystemNo;							// 系统编号
	TDAStringType		LocalNo;							// 本地编号
	TDAStringType		OrderNo;							// 定单号
	TDAStringType		OrigOrderNo;						// 原定单号
	TDAStringType		OrderMethod;						// 下单方式：1：定单；2：改单；3：撤单
	TDAStringType		AcceptType;							// （废弃）
	TDAStringType		ExchangeCode;						// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		BuySale;							// 买还是卖：1=buy 2=sell
	TDAStringType		OrderNumber;						// 下单数
	TDAStringType		OrderPrice;							// 下单价格
	TDAStringType		FilledNumber;						// 已成交数
	TDAStringType		FilledPrice;						// 成交均价
	TDAStringType		TradeType;							// 交易方式：1=regular 2=FOK 3=IOC
	TDAStringType		PriceType;							// 定单类型：1=限价单, 2=市价单，3=限价止损（stop to limit），4=止损（stop to market）
	TDAStringType		HtsType;							// 0=regular 1=HTS
	TDAStringType		OrderDate;							// 下单日期
	TDAStringType		OrderTime;							// 下单时间
	TDAStringType		ErrorCode;							// 错误代码
	TDAStringType		OrderState;							// 订单状态（1：已请求；2：已排队；3：部分成交；4：完全成交；5：已撤余单；6：已撤单；7：指令失败；8：待送出；9：待更改；A：待撤单）
	TDAStringType		IsRiskOrder;						// 用户下单类型：C或是空客户下单；D：是del下单 R：强平下单（风控）；Y：盈损单；T：条件单
	TDAStringType		CancelUserId;						// 撤单的用户标识
	TDAStringType		TriggerPrice;						// 触发价格
	TDAStringType		ValidDate;							// 有效日期（1=当日有效, 2=永久有效（GTC），3=OPG，4=IOC，5=FOK，6=GTD，7=ATC，8=FAK）
	TDAStringType		AddReduce;							// 开仓还是平仓：1=开仓 2=平仓，3=平今，4=平昨
	TDAStringType		StrategyId;							// 策略ID 20130726 add
	TDAStringType		MaxShow;							// 显示委托量 20150803 add 必须小于委托量
	TDAStringType		MinQty;								// 最小成交量 
	TDAStringType		ExchangeTime;						// 交易所返回时间
	TDAStringType		CancelTime;							// 撤单时间
};
// 查询成交请求
struct CStockQryTradeField
{
	TDAStringType		UserId;								// 用户		
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询成交返回
struct CStockRspTradeField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		AccountNo;							// 资金账号
	TDAStringType		FilledNo;							// 成交编号（要包括7位的订单编号，一共11位）
	TDAStringType		OrderNo;							// 定单号
	TDAStringType		SystemNo;							// 系统编号
	TDAStringType		LocalNo;							// 本地编号
	TDAStringType		ExchangeCode;						// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		BuySale;							// 买还是卖：1=buy 2=sell
	TDAStringType		FilledNumber;						// 成交数
	TDAStringType		FilledPrice;						// 成交价格
	TDAStringType		FilledDate;							// 成交日期(yyyy-MM-dd)
	TDAStringType		FilledTime;							// 成交时间(hh:mm:ss)
	TDAStringType		Commsion;							// 成交手续费
	TDAStringType		OrderNumber;						// 委托数量
	TDAStringType		OrderPrice;							// 委托价格
	TDAStringType		DeliveryDate;						// 合约交割日期(yyyyMMdd)
	TDAStringType		FilledType;							// 成交类别(N：普通下单成交；C、T：调期模拟成交)
	TDAStringType		OrderType;							// 定单类型（1=限价单, 2=市价单，3=限价止损（stop to limit），4=止损（stop to market）
	TDAStringType		ValidDate;							// 有效日期（1=当日有效, 2=永久有效）
	TDAStringType		AddReduce;							// 开仓还是平仓：1=开仓 2=平仓，3=平今，4=平昨
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询合约请求
struct CStockQryInstrumentField
{
	TDAIntType			PageIndex;							// 查询多少条,每次返回的条数
	TDAStringType		ExchangeNo;							// 交易所代码，如果填写值，查询一个交易所的合约
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询合约返回
struct CStockRspInstrumentField
{
	TDAStringType		ExchangeNo;							// 交易所编号 
	TDAStringType		ExchangeName;						// 交易所名称 
	TDAStringType		CommodityNo;						// 合约NO
	TDAStringType		CommodityName;						// 商品名 
	TDAStringType		CommodityType;						// 商品类别 
	TDAStringType		CurrencyNo;							// 货币编号 
	TDAStringType		CurrencyName;						// 货币名称 
	TDADoubleType		ProductDot;							// 点值（一个最小跳点的价值）   
	TDADoubleType		UpperTick;							// 最小变动单位 
	TDADoubleType		SettlePrice;						// 上日结算价 
	TDAStringType		TradeMonth;							// 交易月 (yyyyMM)/交割日 (yyyyMMdd)
	TDAIntType			DotNum;								// 行情小数点位数
	TDAIntType			LowerTick;							// 进阶单位
	TDAIntType			DotNumCarry;						// 调期小数点位数
	TDADoubleType		UpperTickCarry;						// 调期最小变动单位
	TDAStringType		FirstNoticeDay;						// 首次通知日 (yyyyMMdd)
	TDADoubleType		FreezenPercent;						// 冻结保证金百分比 
	TDADoubleType		FreezenMoney;						// 冻结保证金固定值 
	TDADoubleType		FeeMoney;							// 固定手续费 
	TDADoubleType		FeePercent;							// 百分比手续费 
	TDADoubleType		PriceStrike;						// 现货商品昨结算价 
	TDADoubleType		ProductDotStrike;					// 现货商品点值  
	TDADoubleType		UpperTickStrike;					// 现货商品最小变动单位 
	TDAStringType		LastTradeDay;						// 最后交易日 (yyyyMMdd)(期货专用)
	TDAStringType		LastUpdateDay;						// 最后更新日 (yyyyMMdd)(期货专用)
	TDADoubleType		CriticalPrice;						// 期权临界价格 (期货专用)
	TDADoubleType		CriticalMinChangedPrice;			// 期权临界价格以下的最小跳点 (期货专用)
	TDAStringType		ExchangeSub;						// 实际交易所(CME细分成3个交易所:CME,CME_COMEX,CME_NYMEX)(期货专用)
	TDAStringType		OptionType;							// 期权类型(R：看涨；F：看跌)(期货专用)
	TDAStringType		OptionMonth;						// 期权年月(yyyyMM)(期货专用)
	TDAStringType		OptionStrikePrice;					// 期权执行价格(期货专用)
	TDAStringType		OptionCommodityNo;					// 期权对应期货商品编号(期货专用)
	TDAStringType		OptionContractNo;					// 期权对应期货合约编号(期货专用)
	TDAStringType		MortgagePercent;					// 按揭价值百分比
	TDAStringType		UpperTickCode;						// 最小变动单位代码
	TDAStringType		LotSize;							// 最小批量
	TDAStringType		FlatTime;							// 平仓时间标志(控制T+1：0代表T+0，可以当天卖出平仓；1代表T+1，必须隔天卖出平仓；N代表T+N)
	TDAStringType		CommodityFNameEN;					// 商品名（英文）
	TDAStringType		CanSell;							// 是否支持卖空（0或空：不可以；1：可以）
	TDADoubleType		SellRate;							// 卖空时的按金比例（例：0.5）
	TDADoubleType		SellMax;							// 卖空持仓上限额
	TDADoubleType		StrikeRate;							// 换股比率，表示一份窝轮牛熊証，相当于多少正股
	TDADoubleType		StrikePrice;						// 行使价
	TDADoubleType		ReceivePrice;						// 收回价
	TDAStringType		ExpireDate;							// 到期日（yyyy-MM-dd）
	TDADoubleType		SellRateKeep;						// 卖空时的维持按金比例（例：0.5）
	TDAStringType		StrikeCommodityNo;					// 涡轮牛熊证对应正股编号
	TDAStringType		CallPutFlag;						// 涡轮牛熊证的涨跌标志(C:涨；P:跌)
	TDAStringType		Publisher;							// 涡轮牛熊证的发行人
};
// 查询交易所请求
struct CStockQryExchangeField
{
	TDAStringType		ProductGroupID;
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询交易所返回
struct CStockRspExchangeField
{
	TDAStringType		ExchangeNo;							// 交易所编号
	TDAStringType		ExchangeName;						// 交易所名称
	TDAStringType		SettleType;							// 交易所类型（HK：港股；US：美股）
	TDAStringType 		NameEN;								// 交易所名称（英文）
};
// 查询资金请求
struct CStockQryCapitalField
{
	TDACharType			Unused;								// 不使用	
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询资金返回
struct CStockRspCapitalField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		InMoney;							// 入金
	TDAStringType		OutMoney;							// 出金
	TDAStringType		TodayCanUse;						// 今可用
	TDAStringType		TodayAmount;						// 今结存
	TDAStringType		TodayBalance;						// 今权益
	TDAStringType		FreezenMoney;						// 冻结资金
	TDAStringType		Commission;							// 佣金
	TDAStringType		Margin;								// 保证金
	TDAStringType		OldCanUse;							// 昨可用
	TDAStringType		OldAmount;							// 昨结存
	TDAStringType		OldBalance;							// 昨权益
	TDAStringType		FloatingProfit;						// 浮动盈亏
	TDAStringType		CurrencyNo;							// 币种编号 
	TDAMoneyType		CurrencyRate;						// 货币与基本的汇率
	TDAMoneyType		UnexpiredProfit;					// 未到期平盈
	TDAMoneyType		UnaccountProfit;					// 未结平盈
	TDAMoneyType		KeepDeposit;						// 维持保证金
	TDAMoneyType		Royalty;							// 期权权利金
	TDAMoneyType		Credit;								// 信任额度
	TDAMoneyType		AddCapital;							// 配资资金
	TDAMoneyType		IniEquity;							// 初始资金
	TDAStringType		AccountNo;							// 资金帐号 1
	TDAMoneyType		MortgageMoney;						// 按揭价值 20150610 added for 港股
	TDAMoneyType		MarginLimit;						// 孖展上限额度 20150727 added for 港股
	TDAMoneyType		BorrowValue;						// 借货价值 20150727 added for 港股
	TDAMoneyType		T1;									// T1 20160219 added for 港股
	TDAMoneyType		T2;									// T2 20160219 added for 港股
	TDAMoneyType		T3;									// T3 20160219 added for 港股
	TDAMoneyType		TN;									// Tn 20160219 added for 港股
	TDAMoneyType		TradeLimit;							// 交易限额
	TDAMoneyType		CanCashOut;							// 可取资金
	TDAMoneyType		AccruedCrInt;						// 月存款利息
	TDAMoneyType		AccruedDrInt;						// 月欠款利息
	TDAMoneyType		CrossMax;							// 跨市场资金限额
	TDAMoneyType		SellFreezenMoney;					// 卖空冻结资金
	TDAMoneyType		SellInterest;						// 卖空利息
	TDAMoneyType		SellNeedAddMargin;					// 需补按金
	TDAStringType		NetProfit;							// 净盈利 1
	TDAStringType		ProfitRate;							// 盈利率 1
	TDAStringType		RiskRate;							// 风险率 1
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询持仓请求
struct CStockQryPositionField
{
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询持仓返回
struct CStockRspPositionField
{
	TDAStringType		ClientNo;							// 用户标识
	TDAStringType		ExchangeNo;							// 交易所
	TDAStringType		CommodityNo;						// 证券代码
	TDAStringType		Direct;								// 持仓方向（1：持买；2：持卖）
	TDADoubleType		HoldPrice;							// 持仓成本价
	TDAIntType			CanTradeVol;						// 可卖数量
	TDAIntType			TodayBuyVol;						// 今买数量
	TDAIntType			FrozenVol;							// 冻结数量
	TDADoubleType		TotalBuyMoney;						// 持有期内买入金额总和
	TDADoubleType		TotalSellMoney;						// 持有期内卖出金额总和
	TDAIntType			TotalBuyVol;						// 持有期内买入数量
	TDAIntType			TotalSellVol;						// 持有期内卖出数量
	TDAStringType		OpenDate;							// 首次开仓日期(yyyy-MM-dd)
	TDADoubleType		FlatProfit;							// 平仓盈利
	TDAIntType			HkexT1;								// 港股T+1数量
	TDAIntType			HkexT2;								// 港股T+2数量
	TDAIntType			HkexT3;								// 美股T+3数量
	TDAIntType			UnsettleVol;						// 港股未交收数量=T1+T2
	TDAIntType			SettledVol;							// 港股已交收数量
	TDAIntType			HoldVol;							// 持仓数量
	TDAIntType			TodaySaleVol;						// 今卖数量
	TDADoubleType		SellFrozenMoney;					// 卖空冻结资金
	TDADoubleType		OpenPrice;							// 开仓均价
};
// 查询跳点请求
struct CStockQryTickField
{
	TDACharType			Unused;								// 不使用
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询跳点返回
struct CStockRspTickField
{
	TDAStringType		UpperTickCode;						// 最小变动单位代码
	TDAStringType		PriceFrom;							// 最小变动单位开始行情价格
	TDAStringType		UpperTick;							// 行情最小变动单位
	TDAStringType		ProductDot;							// 最小变动单位对应的点值
	TDAStringType		DotNum;								// 行情小数位数
	TDAStringType		LowerTick;							// 进价单位
};
// 查询货币请求
struct CStockQryCurrencyField
{
	TDACharType			Unused;								// 不使用
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询货币返回
struct CStockRspCurrencyField
{
	TDAStringType		CurrencyNo;							// 货币编号
	TDAIntType			IsBase;								// 基币货币编号
	TDADoubleType		ChangeRate;							// 与基币的换算汇率
	TDAStringType		CurrencyName;						// 货币名称
	TDAStringType		CurrencyNameEN;						// 货币名称（英文）
};
// 查询版本请求
struct CStockQryVersionField
{
	TDAStringType		UserId;								// 用户标识
	TDAStringType		UserPwd;							// 用户密码
	TDAStringType		ErrorDescription;					// 错误信息
};
// 查询版本返回
struct CStockRspVersionField
{
	TDAStringType		Version;							// 版本号
	TDAStringType		MustUpdate;							// 是否必须更新到新版本才能正常使用（0：可以不更新；1：必须更新）
	TDAStringType		MustVersion;						// 必须要更到的版本号
	TDAStringType		VersionContent_CN;					// 版本内容中文
	TDAStringType		VersionContent_US;					// 版本内容英文
};
//-------------------------------------------------------------------------
// 推送订单变化
struct CStockRtnOrderField
{
	TDAStringType		LocalOrderNo;						// 本地订单号
	TDAStringType		ExchangeNo;							// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		OrderNo;							// 定单号
	TDAIntType			OrderNumber;						// 委托数量
	TDAIntType			FilledNumber;						// 已成交数量
	TDAPriceType		FilledAdvPrice;						// 成交均价
	TDAIntType			BuyHoldNumber;						// 持买数量
	TDAPriceType		BuyHoldOpenPrice;					// 持买开仓均价
	TDAPriceType		BuyHoldPrice;						// 持买均价
	TDAIntType			SaleHoldNumber;						// 持卖数量
	TDAPriceType		SaleHoldOpenPrice;					// 持卖开仓均价
	TDAPriceType		SaleHoldPrice;						// 持卖均价
	TDAStringType		IsCanceled;							// 是否已经撤单（0：没有；1：已撤单）
	TDAPriceType		FilledTotalFee;						// 成交总的手续费
	TDAIntType			Status;								// 顺序号
	TDAStringType		AccountNo;							// 资金帐号
	TDAStringType		HoldType;							// 持仓类型（0：昨仓；1：今仓）
	TDAPriceType		HoldMarginBuy;						// 持买保证金
	TDAPriceType		HoldMarginSale;						// 持卖保证金
	TDAPriceType		CurrPrice;							// 最新价
	TDAPriceType		FloatProfit;						// 浮动盈亏
};
// 推送资金变化
struct CStockRtnCapitalField
{
	TDAStringType		ClientNo;							// 客户号
	TDAStringType		AccountNo;							// 资金帐号
	TDAStringType		CurrencyNo;							// 币种
	TDAPriceType		Available;							// 今可用
	TDAPriceType		YAvailable;							// 昨可用
	TDAPriceType		CanCashOut;							// 今可出
	TDAPriceType		Money;								// 今结存
	TDAPriceType		ExpiredProfit;						// 平仓盈亏
	TDAPriceType		FrozenDeposit;						// 冻结资金
	TDAPriceType		Fee;								// 手续费
	TDAPriceType		Deposit;							// 保证金
	TDAPriceType		KeepDeposit;						// 维持保证金
	TDAIntType			Status;								// 状态
	TDAPriceType		InMoney;							// 入金
	TDAPriceType		OutMoney;							// 出金
	TDAPriceType		UnexpiredProfit;					// 未到期平盈
	TDAPriceType		TodayTotal;							// 今权益
	TDAPriceType		UnaccountProfit;					// 未结平盈
	TDAPriceType		Royalty;							// 期权权利金
	TDAStringType		ExchangeNo;							// 交易所代码
	TDAStringType		TreatyCode;							// 合约代码
	TDAStringType		OrderNo;							// 定单号
	TDAIntType			OrderNumber;						// 委托数量
	TDAIntType			FilledNumber;						// 已成交数量
	TDAPriceType		FilledAdvPrice;						// 成交均价
	TDAIntType			BuyHoldNumber;						// 持买数量
	TDAPriceType		BuyHoldOpenPrice;					// 持买开仓均价
	TDAPriceType		BuyHoldPrice;						// 持买均价
	TDAIntType			SaleHoldNumber;						// 持卖数量
	TDAPriceType		SaleHoldOpenPrice;					// 持卖开仓均价
	TDAPriceType		SaleHoldPrice;						// 持卖均价
	TDAStringType		IsCanceled;							// 是否已经撤单（0：没有；1：已撤单）
	TDAPriceType		FilledTotalFee;						// 成交总的手续费
	TDAPriceType		Credit;								// 信任额度
	TDAPriceType		MarginLimit;						// 孖展上限额度 20150727 added for 港股
	TDAPriceType		BorrowValue;						// 借货价值 20150727 added for 港股
	TDAPriceType		MortgageMoney;						// 按揭价值 20150727 added for 港股
	TDAPriceType		T1;									// T1 20160219 added for 港股
	TDAPriceType		T2;									// T2 20160219 added for 港股
	TDAPriceType		T3;									// T3 20160219 added for 港股
	TDAPriceType		TN;									// Tn 20160219 added for 港股
	TDAPriceType		TradeLimit;							// 交易限额
	TDAPriceType		FCrossMax;							// 跨市场资金限额
	TDAPriceType		SellFreezenMoney;					// 卖空冻结资金
	TDAPriceType		SellInterest;						// 卖空利息
	TDAPriceType		SellNeedAddMargin;					// 需补按金
};
// 推送持仓变化
typedef CStockRspPositionField CStockRtnPositionField;
// 推送成交返回
typedef CStockRspTradeField	CStockRtnTradeField;
//-------------------------------------------------------------------------
// 获取问题
struct CStockReqGetQuestionField
{
	TDAIntType			Unused;								// 用户帐号
	TDAStringType		ErrorDescription;					// 错误信息
};
// 获取问题返回
struct CStockRspQuestionField
{
	TDAStringType		QuestionType;						// 问题类型	0：国际期货，1：国际股票
	TDAStringType		QuestionId;							// 问题编号
	TDAStringType		QuestionCN;							// 问题（中文）
	TDAStringType		QuestionEN;							// 问题（英文）
};
// 安全验证请求
struct CStockReqSafeVerifyField
{
	TDAStringType		UserId;								// 用户帐号
	TDAStringType		UserPwd;							// 交易密码
	TDAStringType		Type;								// 类别
	TDAStringType		Question;							// 密保问题编号
	TDAStringType		Answer;								// 密保问题答案
	TDAStringType		MobileNumber;						// 手机号
	TDAStringType		VerifyCode;							// 手机验证码
	TDAStringType		SaveMac;							// 是否需要记住该设备
	TDAStringType		MacAddress;							// MAC地址
	TDAStringType		ErrorDescription;					// 错误信息
};
// 设置验证问题答案
struct CStockReqSetVerifyQAField
{
	TDAStringType		UserId;								// 用户帐号
	TDAStringType		UserPwd;							// 交易密码
	TDAStringType		Type;								// 类别
	TDAStringType		Question;							// 密保问题编号
	TDAStringType		Answer;								// 密保问题答案
	TDAStringType		MobileNumber;						// 手机号
	TDAStringType		VerifyCode;							// 手机验证码
	TDAStringType		SaveMac;							// 是否需要记住该设备
	TDAStringType		ErrorDescription;					// 错误信息
};
// 请求验证码
struct CStockReqVerifyCodeField
{
	TDAStringType		UserId;								// 用户帐号
	TDAStringType		UserPwd;							// 交易密码
	TDAStringType		Type;								// 类别
	TDAStringType		Question;							// 密保问题编号
	TDAStringType		Answer;								// 密保问题答案
	TDAStringType		MobileNumber;						// 手机号
	TDAStringType		VerifyCode;							// 手机验证码
	TDAStringType		ErrorDescription;					// 错误信息
};
