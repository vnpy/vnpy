/////////////////////////////////////////////////////////////////////////
/// DriectAccess Trade Engine
/// Copyright (C) Shanghai DirectAccess Technology Co., Ltd.
/// Last Modify 2019/3/18
/// Define Market Struct
/// Author (c) Wang Jian Quan (Franklin)
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "DADataType.h"

// 错误描述
struct CMarketRspInfoField
{
	TDAIntType			ErrorID;						// 错误码
	TDAStringType		ErrorMsg;						// 错误描述
};

// 用户登录请求
struct CMarketReqUserLoginField
{
	TDAStringType		UserId;							// 用户标识
	TDAStringType		UserPwd;						// 用户密码
	TDAStringType		UserType;						// 用户类型
	TDAStringType		MacAddress;						// MAC地址
	TDAStringType		ComputerName;					// 计算机名
	TDAStringType		SoftwareName;					// 软件名称
	TDAStringType		SoftwareVersion;				// 软件版本号
	TDAStringType		AuthorCode;						// 授权码
	TDAStringType		ErrorDescription;				// 错误信息
};

// 用户登录返回
struct CMarketRspUserLoginField
{
	TDAStringType		UserName;						// 用户名    
	TDAStringType		UserPwd;						// 登录密码             
	TDAStringType		UserType;						// 用户类型             
};

// 用户登出请求
struct CMarketReqUserLogoutField
{
	TDAStringType		BrokerID;						// 经纪公司代码
	TDAStringType		UserId;							// 用户代码
	TDAStringType		ErrorDescription;				// 错误信息
};

// 订阅行情请求
struct CMarketReqMarketDataField
{
	TDACharType			MarketType;						// 金融类型
	TDACharType			SubscMode;						// 行情种类
	TDAIntType			MarketCount;					// 单次最大订阅数	
	TDAStringType		MarketTrcode[MAX_SUB_COUNT];	// 单次最大订阅合约
	TDAStringType		ErrorDescription;				// 错误信息
};

// 返回行情数据
struct CMarketRspMarketDataField
{
	TDAStringType		ExchangeCode;					// 交易所代码
	TDAStringType		TreatyCode;						// 合约代码
	TDAStringType		BuyPrice;   					// 买价
	TDAStringType		BuyNumber;   					// 买量
	TDAStringType		SalePrice;   					// 卖价
	TDAStringType		SaleNumber;   					// 卖量
	TDAStringType		CurrPrice;   					// 最新价
	TDAStringType		CurrNumber;   					// 最新量
	TDAStringType		High;   						// 当天最高价
	TDAStringType		Low;   							// 当天最低价
	TDAStringType		Open;   						// 开盘价
	TDAStringType		IntradaySettlePrice;   			// 当日盘中结算价(股票：收盘价)
	TDAStringType		Close;   						// 当天结算价
	TDAStringType		Time;   						// 行情时间
	TDAStringType		FilledNum;   					// 成交量
	TDAStringType		HoldNum;   						// 持仓量
	TDAStringType		BuyPrice2; 						// 买价2
	TDAStringType		BuyPrice3;  					// 买价3
	TDAStringType		BuyPrice4;  					// 买价4
	TDAStringType		BuyPrice5;  					// 买价5
	TDAStringType		BuyNumber2;  					// 买量2
	TDAStringType		BuyNumber3;  					// 买量3
	TDAStringType		BuyNumber4;  					// 买量4
	TDAStringType		BuyNumber5;  					// 买量5
	TDAStringType		SalePrice2;  					// 卖价2
	TDAStringType		SalePrice3;  					// 卖价3
	TDAStringType		SalePrice4;  					// 卖价4
	TDAStringType		SalePrice5;  					// 卖价5
	TDAStringType		SaleNumber2; 					// 卖量2
	TDAStringType		SaleNumber3;  					// 卖量3
	TDAStringType		SaleNumber4;  					// 卖量4
	TDAStringType		SaleNumber5;  					// 卖量5
	TDAStringType		HideBuyPrice; 					// 隐藏买价
	TDAStringType		HideBuyNumber; 					// 隐藏买量
	TDAStringType		HideSalePrice; 					// 隐藏卖价
	TDAStringType		HideSaleNumber;					// 隐藏卖量
	TDAStringType		LimitDownPrice; 				// 跌停价
	TDAStringType		LimitUpPrice;  					// 涨停价
	TDAStringType		TradeDay;   					// 交易日
	TDAStringType		BuyPrice6;						// 买价6
	TDAStringType		BuyPrice7;						// 买价7
	TDAStringType		BuyPrice8;						// 买价8
	TDAStringType		BuyPrice9;						// 买价9
	TDAStringType		BuyPrice10;						// 买价10
	TDAStringType		BuyNumber6;						// 买量6
	TDAStringType		BuyNumber7;						// 买量7
	TDAStringType		BuyNumber8;						// 买量8
	TDAStringType		BuyNumber9;						// 买量9
	TDAStringType		BuyNumber10;					// 买量10
	TDAStringType		SalePrice6;						// 卖价6
	TDAStringType		SalePrice7;						// 卖价7
	TDAStringType		SalePrice8;						// 卖价8
	TDAStringType		SalePrice9;						// 卖价9
	TDAStringType		SalePrice10;					// 卖价10
	TDAStringType		SaleNumber6;					// 卖量6
	TDAStringType		SaleNumber7;					// 卖量7
	TDAStringType		SaleNumber8;					// 卖量8
	TDAStringType		SaleNumber9;					// 卖量9
	TDAStringType		SaleNumber10;					// 卖量10
	TDAStringType		TradeFlag;						// 港交所股票行情：成交类型
	TDAStringType		DataTimestamp;					// 交易所数据时间戳
	TDAStringType		DataSourceId;					// 数据来源
	TDAStringType		CanSellVol;						// 可卖空股数（美股行情用）
	TDAStringType		QuoteType;  					// 行情区分
	TDAStringType		AggressorSide;  				// 主动买或主动卖
	TDAStringType		PreSettlementPrice;  			// 昨结算（股票：昨收盘价）
};

// 订阅经济商请求
struct CMarketReqBrokerDataField
{
	TDAStringType		ContCode;						// 合约代码
	TDAStringType		ErrorDescription;				// 错误信息
};

// 返回经济商数据
struct CMarketRspBrokerDataField
{
	TDABrokerType		BrokerData;						// 经济商数据
};

// 推送交易日结构体
struct CMarketRspTradeDateField
{
	TDAStringType		TradeDate;						// 交易日期
	TDAStringType		TradeProduct;					// 交易产品
};
