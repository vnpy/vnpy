#ifndef _T_CZCE_MARKET_
#define _T_CZCE_MARKET_
#include "tdef.h"

//*****************************************************************************************
//以上服务数据ID保留与原系统兼容，以下服务ID针对每个市场分开定义

//-----------------------------------郑商所-----------------------------------------------
#define ID_CZCE_BASEINFO 4001	 //期货及期权基础信息
#define ID_CZCE_MARKETDATA 4002   //期货及期权行情数据
#define ID_CZCE_FORQOUTE 4003	 //询价通知
#define ID_CZCE_MARKETDATAL2 4004 //期货及期权L2行情数据

#pragma pack(push, 1)
//1.1 郑商所期货行情
typedef struct t_CZCE_FutursMarketData
{
	T_I32 nTime;			//时间(HHMMSSmmmm)
	T_I32 nStatus;			//状态
	T_I64 iPreOpenInterest; //昨持仓
	T_U32 uPreClose;		//昨收盘价
	T_U32 uPreSettlePrice;  //昨结算
	T_U32 uOpen;			//开盘价
	T_U32 uHigh;			//最高价
	T_U32 uLow;				//最低价
	T_U32 uMatch;			//最新价
	T_I64 iVolume;			//成交总量
	T_I64 iTurnover;		//成交总金额
	T_I64 iOpenInterest;	//持仓总量
	T_U32 uClose;			//今收盘
	T_U32 uSettlePrice;		//今结算
	T_U32 uHighLimited;		//涨停价
	T_U32 uLowLimited;		//跌停价
	T_I32 nPreDelta;		//昨虚实度
	T_I32 nCurrDelta;		//今虚实度
	T_U32 uAskPrice[5];		//申卖价
	T_U32 uAskVol[5];		//申卖量
	T_U32 uBidPrice[5];		//申买价
	T_U32 uBidVol[5];		//申买量
	char sTradingStatus;	//交易状态
	char sRevs[3];			//保留字段
} T_CZCE_FutursMarketData, *PCZCE_FutursMarketData;
//1.2 郑商所期货基础信息
/////产品类型-------------------------------------------------------
///期货
#define THOST_FTDC_PC_Futures '1'
///期货期权
#define THOST_FTDC_PC_Options '2'
///组合
#define THOST_FTDC_PC_Combination '3'
///即期
#define THOST_FTDC_PC_Spot '4'
///期转现
#define THOST_FTDC_PC_EFP '5'
///现货期权
#define THOST_FTDC_PC_SpotOption '6'
//合约生命周期-----------------------------------------
///未上市
#define THOST_FTDC_IP_NotStart '0'
///上市
#define THOST_FTDC_IP_Started '1'
///停牌
#define THOST_FTDC_IP_Pause '2'
///到期
#define THOST_FTDC_IP_Expired '3'
//持仓类型-------------------------------------------------
///净持仓
#define THOST_FTDC_PT_Net '1'
///综合持仓
#define THOST_FTDC_PT_Gross '2'

/////////////////////////////////////////////////////////////////////////
//////持仓日期类型
/////////////////////////////////////////////////////////////////////////
///使用历史持仓
#define THOST_FTDC_PDT_UseHistory '1'
///不使用历史持仓
#define THOST_FTDC_PDT_NoUseHistory '2'

/////////////////////////////////////////////////////////////////////////
///大额单边保证金算法类型
/////////////////////////////////////////////////////////////////////////
///不使用大额单边保证金算法
#define THOST_FTDC_MMSA_NO '0'
///使用大额单边保证金算法
#define THOST_FTDC_MMSA_YES '1'

/////////////////////////////////////////////////////////////////////////
///期权类型类型
/////////////////////////////////////////////////////////////////////////
///看涨
#define THOST_FTDC_CP_CallOptions '1'
///看跌
#define THOST_FTDC_CP_PutOptions '2'

/////////////////////////////////////////////////////////////////////////
///组合类型类型
/////////////////////////////////////////////////////////////////////////
///期货组合
#define THOST_FTDC_COMBT_Future '0'
///垂直价差BUL
#define THOST_FTDC_COMBT_BUL '1'
///垂直价差BER
#define THOST_FTDC_COMBT_BER '2'
///跨式组合
#define THOST_FTDC_COMBT_STD '3'
///宽跨式组合
#define THOST_FTDC_COMBT_STG '4'
///备兑组合
#define THOST_FTDC_COMBT_PRT '5'
///时间价差组合
#define THOST_FTDC_COMBT_CLD '6'

/////////////////////////////////////////////////////////////////////////
///合约交易状态类型
/////////////////////////////////////////////////////////////////////////
///开盘前
#define THOST_FTDC_IS_BeforeTrading '0'
///非交易
#define THOST_FTDC_IS_NoTrading '1'
///连续交易
#define THOST_FTDC_IS_Continous '2'
///集合竞价报单
#define THOST_FTDC_IS_AuctionOrdering '3'
///集合竞价价格平衡
#define THOST_FTDC_IS_AuctionBalance '4'
///集合竞价撮合
#define THOST_FTDC_IS_AuctionMatch '5'
///收盘
#define THOST_FTDC_IS_Closed '6'

typedef struct t_CZCE_BaseInfo
{
	///合约代码
	char sInstrumentID[31];
	///交易所代码
	char sExchangeID[9];
	///合约名称
	char sInstrumentName[21];
	///合约在交易所的代码
	char sExchangeInstID[31];
	///产品代码
	char sProductID[31];
	///产品类型
	char cProductClass;
	///交割年份
	T_I32 nDeliveryYear;
	///交割月
	T_I32 nDeliveryMonth;
	///市价单最大下单量
	T_I32 nMaxMarketOrderVolume;
	///市价单最小下单量
	T_I32 nMinMarketOrderVolume;
	///限价单最大下单量
	T_I32 nMaxLimitOrderVolume;
	///限价单最小下单量
	T_I32 nMinLimitOrderVolume;
	///合约数量乘数
	T_I32 nVolumeMultiple;
	///最小变动价位,扩大10000倍
	T_I64 i64PriceTick;
	///创建日
	T_I32 nCreateDate;
	///上市日
	T_I32 nOpenDate;
	///到期日
	T_I32 nExpireDate;
	///开始交割日
	T_I32 nStartDelivDate;
	///结束交割日
	T_I32 nEndDelivDate;
	///合约生命周期状态
	char cInstLifePhase;
	///当前是否交易
	T_I32 nIsTrading;
	///持仓类型
	char cPositionType;
	///持仓日期类型
	char cPositionDateType;
	///多头保证金率,扩大至10000倍
	T_I64 i64LongMarginRatio;
	///空头保证金率,扩大至10000倍
	T_I64 i64ShortMarginRatio;
	///是否使用大额单边保证金算法
	char cMaxMarginSideAlgorithm;
	///基础商品代码
	char sUnderlyingInstrID[31];
	///执行价,扩大至10000倍
	T_I64 i64StrikePrice;
	///期权类型
	char cOptionsType;
	///合约基础商品乘数,扩大至10000倍
	T_I64 i64UnderlyingMultiple;
	///组合类型
	char cCombinationType;
} T_CZCE_BaseInfo, *PCZCE_BaseInfo;

///发给做市商的询价请求
typedef struct t_CZCE_ForQuote
{
	///交易日
	T_I32 nTradingDay;
	///合约代码
	char sInstrumentID[31];
	///询价编号
	char sForQuoteSysID[21];
	///询价时间
	T_I32 nForQuoteTime;
	///业务日期
	int nActionDay;
	///交易所代码
	char sExchangeID[9];
} T_CZCE_ForQuote;
#pragma pack(pop)
#endif //_T_CZCE_MARKET_