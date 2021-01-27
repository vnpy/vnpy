#ifndef _T_SZ_MARKET_
#define _T_SZ_MARKET_
#include "tdef.h"
//*****************************************************************************************
//以上服务数据ID保留与原系统兼容，以下服务ID针对每个市场分开定义

//-----------------------------------深圳市场--------------------------------------
#define ID_SZ_INDEXDATA 2000	   //指数(Stock_IndexData)
#define ID_SZ_TRANSACTION 2001	 //成交(Stock_TransactionEx)
#define ID_SZ_ORDERQUEUE 2002	  //委托队列(Stock_OrderQueue_Head+Stock_OrderQueue)
#define ID_SZ_STEPORDER 2003	   //逐笔委托(Stock_StepOrder)
#define ID_SZ_MARKETDATA 2004	  //行情数据(Stock_MarketData)
#define ID_SZ_MARKETDATA_L1 2005   //用于L1行情 深圳(Stock_MarketData_L1)
#define ID_SZ_MATCHMARKETDATA 2006 //撮合行情，根据逐笔成交和逐笔委托计算的行情
#define ID_SZ_KLINEDATA 2007	   //深交所个股分钟K线数据(T_SZ_Kline)
#define ID_SZ_BASEINFO 2008		   //深交所证券基础信息(见tszopmarket.h)

#pragma pack(push, 1)
// 1.1 股票行情
typedef struct t_SZ_StockMarketDataL2 {
    T_I32 nTime;				//时间(HHMMSSmmmm)
    T_I32 nStatus;				//状态
    T_U32 uPreClose;			//前收盘价
    T_U32 uOpen;				//开盘价
    T_U32 uHigh;				//最高价
    T_U32 uLow;					//最低价
    T_U32 uMatch;				//最新价
    T_U32 uAskPrice[10];		//申卖价
    T_U32 uAskVol[10];			//申卖量
    T_U32 uBidPrice[10];		//申买价
    T_U32 uBidVol[10];			//申买量
    T_U32 uNumTrades;			//成交笔数
    T_I64 iVolume;				//成交总量
    T_I64 iTurnover;			//成交总金额
    T_I64 iTotalBidVol;			//委托买入总量
    T_I64 iTotalAskVol;			//委托卖出总量
    T_U32 uWeightedAvgBidPrice; //加权平均委买价格
    T_U32 uWeightedAvgAskPrice; //加权平均委卖价格
    T_I32 nIOPV;				//IOPV净值估值
    T_I32 nYieldToMaturity;		//到期收益率
    T_U32 uHighLimited;			//涨停价 999999999 表示无涨停价格限制
    T_U32 uLowLimited;			//跌停价 -999999999 ,用无符号表示成3294967297 表示无跌停价格限制；对于价格不可以为负数的业务，则填写价格档位，表示无跌停价格限制，比如对于股票现货集中竞价业务填写 10
    char sPrefix[4];			//证券信息前缀
    T_I32 nSyl1;				//市盈率1 2 位小数 股票：价格/上年每股利润 债券：每百元应计利息
    T_I32 nSyl2;				//市盈率2 2 位小数 股票：价格/本年每股利润 债券：到期收益率 基金：每百份的IOPV 或净值 权证：溢价率
    T_I32 nSD2;					//升跌2（对比上一笔）
    char sTradingPhraseCode[8]; //上交所与深交所字段含义不同，参见以下注解：
    //深交所：
    //   产品所处的交易阶段代码
    //第 0 位：
    //S=启动（开市前）
    //O=开盘集合竞价
    //T=连续竞价
    //B=休市
    //C=收盘集合竞价
    //E=已闭市
    //H=临时停牌
    //A=盘后交易
    //V=波动性中断
    //第 1 位：
    //0=正常状态
    //1=全天停牌
    T_I32 nPreIOPV; //基金T-1日收盘时刻IOPV 仅标的为基金时有效
} T_SZ_StockMarketDataL2, *PSZ_StockMarketDataL2;

//1.2 L1行情，上交所与深交所均用此结构
typedef struct t_SZ_StockMarketDataL1 {
    T_I32 nTime;				//时间(HHMMSSmmmm)
    T_I32 nStatus;				//状态
    T_U32 uPreClose;			//前收盘价
    T_U32 uOpen;				//开盘价
    T_U32 uHigh;				//最高价
    T_U32 uLow;					//最低价
    T_U32 uMatch;				//最新价
    T_U32 uAskPrice[5];			//申卖价
    T_U32 uAskVol[5];			//申卖量
    T_U32 uBidPrice[5];			//申买价
    T_U32 uBidVol[5];			//申买量
    T_U32 uNumTrades;			//成交笔数
    T_I64 iVolume;				//成交总量
    T_I64 iTurnover;			//成交总金额
    T_U32 uHighLimited;			//涨停价
    T_U32 uLowLimited;			//跌停价
    char sTradingPhraseCode[8]; //上交所与深交所字段含义不同，参见以下注解：
    //深交所：
    //   产品所处的交易阶段代码
    //第 0 位：
    //S=启动（开市前）
    //O=开盘集合竞价
    //T=连续竞价
    //B=休市
    //C=收盘集合竞价
    //E=已闭市
    //H=临时停牌
    //A=盘后交易
    //V=波动性中断
    //第 1 位：
    //0=正常状态
    //1=全天停牌
    T_I32 nPreIOPV; //基金T-1日收盘时刻IOPV 仅标的为基金时有效
    T_I32 nIOPV;	//基金IOPV  仅标的为基金时有效
} T_SZ_StockMarketDataL1, *PSZ_StockMarketDataL1;

//深交所V5版逐笔成交委托行情  对应Binary协议文档4.4.5

typedef struct t_SZ_StepTrade {
    T_U16 usChannelNo;		   //频道代码
    T_I64 i64ApplSeqNum;	   //消息记录号 从1开始计数
    char sMDStreamID[3];	   //行情类别
    T_I64 i64BidApplSeqNum;	//买方委托索引，从1开始计数，0表示无对应委托
    T_I64 i64OfferApplSeqNum;  //卖方委托索引,从1开始计数,0表示无对应委托
    char sSecurityID[8];	   //证券代码
    char sSecurityIDSource[4]; //证券代码源 101=深圳证券交易所
    T_I64 i64LastPx;		   //委托价格
    T_I64 i64LastQty;		   //委托数量
    char cExecType;			   //成交类别 4=撤销 F=成交
    T_I64 i64TransactTime;	 //委托时间
    char sExtendFields[];	  //各业务扩展字段 内容由MDStreamID字段决定，如MDStreamID=011 表示现货（股票，基金，债券等）集中竞价交易逐笔行情，暂表各扩展字段为空
} T_SZ_STEPTRADE, *PSZ_STEPTRADE;
//MDStreamID=011 现货（股票，基金，债券等）集中竞价交易逐笔行情
//MDStreamID=021 质押式回购交易逐笔行情
typedef struct t_SZ_300191ExtendFields {

} T_SZ_300191EXTENDFIELDS, *PSZ_300191EXTENDFIELDS;
//MDStreamID=051 协议交易逐笔意向行情
//MDStreamID=052 协议交易逐笔定价行情
typedef struct t_SZ_300591ExtendFields {

} T_SZ_300591EXTENDFIELDS, *PSZ_300591EXTENDFIELDS;

//MDStreamID=071 转融通证券出借逐笔行情
typedef struct t_SZ_300791ExtendFields {

} T_SZ_300791EXTENDFIELDS, *PSZ_300791EXTENDFIELDS;

//深交所V5版逐笔委托行情

//逐笔委托行情 MsgType=30XX92 对应Binary协议文档4.4.4
typedef struct t_SZ_StepOrder {
    T_U16 usChannelNo;		   //频道代码
    T_I64 i64ApplSeqNum;	   //消息记录号 从1开始计数
    char sMDStreamID[3];	   //行情类别
    char sSecurityID[8];	   //证券代码
    char sSecurityIDSource[4]; //证券代码源 101=深圳证券交易所
    T_I64 i64Price;			   //委托价格
    T_I64 i64OrderQty;		   //委托数量
    char cSide;				   //买卖方向 1=买 2=卖 G=借入 F=借出
    T_I64 i64TransactTime;	 //委托时间
    char sExtendFields[];	  //各业务扩展字段 内容由MDStreamID字段决定，如MDStreamID=011 表示现货（股票，基金，债券等）集中竞价交易逐笔行情
} T_SZ_STEPORDER, *PSZ_STEPORDER;

/***
**  4.4.4.1 集中竞价业务逐笔委托行情扩展字段（ 300192）      表 4-14-1 集中竞价业务逐笔委托行情扩展字段说明
***/
//MDStreamID=011 现货（股票，基金，债券等）集中竞价交易逐笔行情
//MDStreamID=021 质押式回购交易逐笔行情
typedef struct t_SZ_300192ExtendFields {
    char cOrdType; //订单类别 1=市价 2=限价 U=本方最优

} T_SZ_300192EXTENDFIELDS, *PSZ_300192EXTENDFIELDS;

/***
   **  4.4.4.2 协议交易业务逐笔委托行情扩展字段（ 300592）  表 4-14-2 协议交易业务逐笔委托行情扩展字段定义
   ***/
//MDStreamID=051 协议交易逐笔意向行情
//MDStreamID=052 协议交易逐笔定价行情
typedef struct t_SZ_300592ExtendFields {
    char sConfirmID[8];	//定价行情约定号  char[8]    ConfirmID 为空表示是意向行情  否则为定价行情
    char sContactor[12];   // 联系人               char[12]
    char sContactInfo[30]; // 联系方式            char[30]

} T_SZ_300592EXTENDFIELDS, *PSZ_300592EXTENDFIELDS;

/***
    **  4.4.4.3 转融通证券出借业务逐笔委托行情扩展字段（ 300792）  表 4-14-3 转融通证券出借业务逐笔委托行情扩展字段定义
   ***/
//MDStreamID=071 转融通证券出借逐笔行情
typedef struct t_SZ_300792ExtendFields {
    T_U16 usExpirationDays; // 期限，           uInt16       单位为天数
    T_U8 ucExpirationType;  // 期限类型         uInt8        1=固定期限
} T_SZ_300792EXTENDFIELDS, *PSZ_300792EXTENDFIELDS;

//1.5 订单队列(Queue)
#ifndef _ORDER_QUEUE_
#define _ORDER_QUEUE_

typedef struct t_OrderQueueHead {
    T_I32 nItem; //数据个数
} T_OrderQueueHead, *POrderQueueHead;
typedef struct t_OrderQueueItem {
    T_I32 nTime;		  //订单时间(HHMMSSmmmm)
    T_I32 nSide;		  //买卖方向('B':Bid 'S':Ask)
    T_I32 nPrice;		  //成交价格
    T_I32 nOrders;		  //订单数量
    T_I32 nABItems;		  //明细个数
    T_I32 nABVolume[200]; //订单明细
} T_OrderQueueItem, *POrderQueueItem;

#endif //#define _ORDER_QUEUE_
typedef struct t_SZ_StockOrderQueue {
    T_OrderQueueHead tHead;
    T_OrderQueueItem tItem[0];

} T_SZ_StockOrderQueue, *PSZ_StockOrderQueue;

//1.6 指数
typedef struct t_SZ_StockIndex {
    T_I32 nTime;		  //时间(HHMMSSmmmm)
    T_I32 nOpenIndex;	 //今开盘指数
    T_I32 nHighIndex;	 //最高指数
    T_I32 nLowIndex;	  //最低指数
    T_I32 nLastIndex;	 //最新指数
    T_I64 iTotalVolume;   //参与计算相应指数的交易数量
    T_I64 iTurnover;	  //参与计算相应指数的成交金额
    T_I32 nPreCloseIndex; //前盘指数
} T_SZ_StockIndex, *PSZ_StockIndex;

//1.7 分钟K线
typedef struct t_SZ_Kline {
    T_U32 uDay;				// 日期				YYYYMMDD
    T_I32 nTime;			// 时间(北京时间)	HHMM
    T_I32 nPreClose;		// 前收盘价         单位：1/100分
    T_I32 nValOpen;			// 开盘价			单位：1/100分,比如1表示0.0001元
    T_I32 nValHigh;			// 最高价			单位：1/100分
    T_I32 nValLow;			// 最低价			单位：1/100分
    T_I32 nValClose;		// 收盘价			单位：1/100分
    T_I64 i64Volume;		// 分钟内成交量		单位：该证券的最小交易单位，比如股票为“股”
    T_I64 i64ValTotal;		// 分钟内成交额		单位：元
    T_I64 i64TotalVol;		// 累计成交量		单位：该证券的最小交易单位，比如股票为“股”
    T_I64 i64TotalTurnOver; // 累计成交金额		单位：元
    T_I32 nTurover;			// 换手(百分数)		单位：1/10000，比如1表示0.01%
    T_I32 nValIncrease;		// 涨跌值			单位：1/100分
} T_SZ_Kline, *PSZ_Kline;   // sizeof() = 48

//1.8 撮合行情
typedef struct t_SZ_StockMarketDataLF {
    T_I32 nTime;				//时间(HHMMSSmmmm)
    T_U32 uPreClose;			//前收盘价
    T_U32 uOpen;				//开盘价
    T_U32 uHigh;				//最高价
    T_U32 uLow;					//最低价
    T_U32 uMatch;				//最新价
    T_U32 uAskPrice[10];		//申卖价
    T_U32 uAskVol[10];			//申卖量
    T_U32 uBidPrice[10];		//申买价
    T_U32 uBidVol[10];			//申买量
    T_U32 uNumTrades;			//成交笔数
    T_I64 iVolume;				//成交总量
    T_I64 iTurnover;			//成交总金额
} T_SZ_StockMarketDataLF, *PSZ_StockMarketDataLF;

/**
* @brief 逐笔行情数据
*
**/
typedef struct t_TickByTickData {
    char cType;					//委托:'0' ,成交:'1'
    union {
        T_SZ_STEPORDER		entrust; //逐笔委托
        T_SZ_STEPTRADE		 trade;	//逐笔成交
    } UttData;

} T_SZ_TickByTickData, *PSZ_TickByTickData;
#pragma pack(pop)
#endif //_T_SZ_MARKET_