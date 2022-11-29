#ifndef _T_SH_MARKET_
#define _T_SH_MARKET_
#include "tdef.h"

//*****************************************************************************************
//以上服务数据ID保留与原系统兼容，以下服务ID针对每个市场分开定义
//-----------------------------------上海市场--------------------------------------
#define ID_SH_INDEXDATA 1000	 //指数(Stock_IndexData)
#define ID_SH_TRANSACTION 1001   //成交(Stock_Transaction)
#define ID_SH_ORDERQUEUE 1002	//委托队列(Stock_OrderQueue_Head+Stock_OrderQueue)
#define ID_SH_MARKETDATA 1004	//行情数据(Stock_MarketData)
#define ID_SH_MARKETDATA_L1 1005 //用于L1行情 上海(Stock_MarketData_L1)
#define ID_SH_KLINEDATA 1007	 //上交所个股分钟K线数据(T_SH_Kline)
#define ID_SH_BASEINFO 1008		 //上交所产品基础信息
#define ID_SH_ATPTRADE 1010		 //上交所盘后逐笔成交
#define ID_SH_ETFEXTENDS              1011 //上交所ETF扩展行情消息
#pragma pack(push, 1)
// 1.1 股票行情
typedef struct t_SH_StockMarketDataL2
{
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
	T_U32 uHighLimited;			//涨停价
	T_U32 uLowLimited;			//跌停价
	char sPrefix[4];			//证券信息前缀
	T_I32 nSyl1;				//市盈率1 2 位小数 股票：价格/上年每股利润 债券：每百元应计利息
	T_I32 nSyl2;				//市盈率2 2 位小数 股票：价格/本年每股利润 债券：到期收益率 基金：每百份的IOPV 或净值 权证：溢价率
	T_I32 nSD2;					//升跌2（对比上一笔）
	char sTradingPhraseCode[8]; //上交所与深交所字段含义不同，参见以下注解：
								//上交所：该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
								/*  第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘P’表示产品停牌，‘M’表示可恢复交易的熔断时段（盘中集合竞价），‘N’表示不可恢复交易的熔断时段（暂停交易至闭市），‘U’表示收盘集合竞价时段，
		盘后固定价格交易：‘I’表示启动（开市前）时段， ‘A’表示集中撮合时段，‘H’表示连续交易时段，‘D’表示闭市时段，‘F’表示停牌
		第2位： ‘0’表示此产品不可正常交易，‘1’表示此产品可正常交易，无意义填空格。
		第3位：‘0’表示未上市，‘1’表示已上市。
		第4位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’ 表示此产品在当前时段可接受进行新订单申报。无意义填空格。*/

	T_I32 nPreIOPV; //基金T-1日收盘时刻IOPV 仅标的为基金时有效
} Stock_MarketData, T_SH_StockMarketDataL2, *PSH_StockMarketDataL2;

//1.2 上交所Level-1
typedef struct t_SH_StockMarketDataL1
{
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
								//上交所：该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
								/*  第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘P’表示产品停牌，‘M’表示可恢复交易的熔断时段（盘中集合竞价），‘N’表示不可恢复交易的熔断时段（暂停交易至闭市），‘U’表示收盘集合竞价时段，
		盘后固定价格交易：‘I’表示启动（开市前）时段， ‘A’表示集中撮合时段，‘H’表示连续交易时段，‘D’表示闭市时段，‘F’表示停牌
		第2位： ‘0’表示此产品不可正常交易，‘1’表示此产品可正常交易，无意义填空格。
		第3位：‘0’表示未上市，‘1’表示已上市。
		第4位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’ 表示此产品在当前时段可接受进行新订单申报。无意义填空格。*/
	T_I32 nPreIOPV;				//基金T-1日收盘时刻IOPV 仅标的为基金时有效
	T_I32 nIOPV;				//基金IOPV  仅标的为基金时有效

}StockMarketDataL1, T_SH_StockMarketDataL1, *PSH_StockMarketDataL1;

//1.3 逐笔成交(Transaction)
typedef struct t_SH_StockStepTrade
{
	T_I32 nTradeIndex;   //成交序号
	T_I32 nTradeChannel; //成交通道
	T_I32 nTradeTime;	//成交时间 HHMMSSmmm
	T_I32 nTradePrice;   //成交价格 扩大10000倍
	T_I64 iTradeQty;	 //成交数量 股票：股 权证：份 债券：张
	T_I64 iTradeMoney;   //成交金额(元)
	T_I64 iTradeBuyNo;   //买方订单号
	T_I64 iTradeSellNo;  //卖方订单号
	char cTradeBSflag;   //内外盘标识 B -外盘，主动买  B-内盘,主动卖 N 未知
	char sRes[3];		 //保留字段1

}T_SH_StockStepTrade, *PSH_StockStepTrade; //上交所逐笔成交，对应交易所UA3201

//1.4 订单队列(Queue)
#ifndef _ORDER_QUEUE_
#define _ORDER_QUEUE_
typedef struct t_OrderQueueHead
{
	T_I32 nItem; //数据个数
} Stock_OrderQueue_Head, T_OrderQueueHead, *POrderQueueHead;
typedef struct t_OrderQueueItem
{
	T_I32 nTime;		  //订单时间(HHMMSSmmmm)
	T_I32 nSide;		  //买卖方向('B':Bid 'S':Ask)
	T_I32 nPrice;		  //成交价格
	T_I32 nOrders;		  //订单数量
	T_I32 nABItems;		  //明细个数
	T_I32 nABVolume[200]; //订单明细
} Stock_OrderQueue, T_OrderQueueItem, *POrderQueueItem;
#endif //_ORDER_QUEUE_

typedef struct t_SH_StockOrderQueue
{
	T_OrderQueueHead tHead;
	T_OrderQueueItem tItem[0];

}StockOrderQueue, T_SH_StockOrderQueue, *PSH_StockOrderQueue;

//1.5 指数
typedef struct t_SH_StockIndex
{
	T_I32 nTime;		  //时间(HHMMSSmmmm)
	T_I32 nOpenIndex;	 //今开盘指数
	T_I32 nHighIndex;	 //最高指数
	T_I32 nLowIndex;	  //最低指数
	T_I32 nLastIndex;	 //最新指数
	T_I64 iTotalVolume;   //参与计算相应指数的交易数量
	T_I64 iTurnover;	  //参与计算相应指数的成交金额
	T_I32 nPreCloseIndex; //前盘指数
} Stock_IndexData, T_SH_StockIndex, *PSH_StockIndex;

//1.6 分钟K线
typedef struct t_SH_Kline
{
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
	T_I32 nTurover;			// 保留1
	T_I32 nValIncrease;		// 保留2
}T_Kline, T_SH_Kline, *PSH_Kline;   // sizeof() = 48

//1.7 产品基础信息文件接口cpxxMMDD.txt
//除权比例和除息金额扩大100万倍外，其它N(X)类型的数据扩大至10000倍，比如，面值i64FaceValue是扩大10000倍后的值
typedef struct t_CPXX
{
	char szStkCode[6];				 //1证券代码	                C6
	char szISIN[12];				 //2ISIN代码	                C12       ISIN代码（预留）。
	T_U32 uUpdateTime;				 //3记录更新时间	          C8        标识接口中本记录更新时间HH:MM:SS,翻译成HHMMSSmmm格式的整数
	char szStkNameZN[8];			 //4中文证券名称	          C8        中文证券名称
	char szStkNameEn[10];			 //5英文证券名称	         C10       英文证券名称（预留）
	char szUnderlyingCode[6];		 //6基础证券代码	         C6         当产品为权证、可转债等衍生品时，该字段为其标的产品的证券代码。
	char szMktClass[4];				 //7市场种类	               C4          ‘ASHR’表示A股市场；‘BSHR’表示B股市场；‘CSHR’表示国际版市场综业平台集合资产管理计划、债券预发行取‘ASHR’
	char szStkClass[6];				 //8证券类别	               C6          ‘ES’表示股票；‘EU’表示基金；‘D’表示债券； ‘RWS’表示权证；‘FF’表示期货。（参考ISO10962），集合资产管理计划、债券预发行取‘D’
	char szStkSubClass[3];			 //9证券子类别	         C3         自定义详细证券类别
	char szCurrency[3];				 //10货币种类	               C3         货币代码取值：美元：USD；人民币：CNY；（参考ISO4217）
	T_I64 i64FaceValue;				 //11面值	               N15(3)        债券当前面值，单位元，其他产品取0.000
	T_I64 i64MatchQty;				 //12可流通证券未上市数量 	N15 	预留
	char szLastDate[15];			 // 13	最后交易日期	  C15        对于国债预发行产品，为最后交易日期，格式为YYYYMMDD	C15
	T_U32 uListingData;				 //14上市日期	         C8         在上交所首日交易日期，YYYYMMDD
	T_U32 uProductSETId;			 //15产品集SET编号     N3        取值范围从1到999。 用来表明产品的一种分组方式，用于在多主机间进行负载均衡分配。该值在一个交易日内不会变化。	N3
	T_I64 i64BuyNumUnit;			 //16	买数量单位	        N12        买订单的申报数量必须是该字段的整数倍。
	T_I64 i64SellNumUnit;			 //17卖数量单位	        N12        卖订单的申报数量必须是该字段的整数倍。
	T_I64 i64DecalaredLowestNum;	 //18限价申报数量下限      N12	    限价申报数量下限
	T_I64 i64DecalaredHightestNum;   //19限价申报数量上限       N12	    限价申报数量上限
	T_I64 i64PreClosePrice;			 //20前收盘价格	    N11(3)        前收盘价格（如有除权除息，为除权除息后前收盘价） 对于货币市场基金实时申赎，取值为0.010  集合资产管理计划固定填写挂牌首日开盘参考价格	N11(3)
	T_I64 i64PriceLevel;			 //21价格档位	    N11(3)        申报价格的最小变动单位
	char cPriceLimitsType;			 //22涨跌幅限制类型    C1           ‘N’表示有涨跌幅限制类型  //‘R’表示无涨跌幅限制类型 //  ‘S’表示回购涨跌幅控制类型// ‘F’表示基于参考价格的涨跌幅控制// ‘P’表示IPO上市首日的涨跌幅控制类型// ‘U’表示无任何价格涨跌幅控制类型
	T_I64 i64UpLimitsPrice;			 //23涨幅上限价格  N11(3)	    对于N类型涨跌幅限制的产品，该字段当日不会更改，基于前收盘价（已首日上市交易产品为发行价）计算。
	T_I64 i64LowerLimitPrice;		 //24跌幅下限价格  N11(3)	    计算方式参考涨幅上限价格
	T_I64 i64DividendRatio;			 //25除权比例         N11(6)	    每股送股比例,对于国债预发行产品，为保证金比例，单位为%。
	T_I64 i64DividendAmount;		 //26除息金额         N11(6)	    每股分红金额
	char cFinaSubjectFlag;			 //27融资标的标志        C1	     ‘T’表示是融资标的证券//  ‘F’表示不是融资标的证券。
	char cMarginSubjectFlag;		 //28融券标的标志         C1        ‘T’表示是融券标的证券//‘F’表示不是融券标的证券。
	char szProdStatusFlag[20];		 //29产品状态标志      C20       该字段为20位字符串，每位表示允许对应的业务，无定义则填空格。
	T_I64 i64MPDecalaredLowestNum;   //30申报数量下限      N12	    市价申报数量下限
	T_I64 i64MPDecalaredHightestNum; //31申报数量上限       N12	    市价申报数量上限
	char szStkNameZNLong[32];		 //32为“中文证券名称（短）”扩位预留字段，目前为空。
	char szNote[50];				 //33备注                  C50	     保留字段，用于扩展。
									 //对于A股股票和沪伦通CDR本地交易的交易产品，
									 //第1位-15位，填写为该产品市场流通总量，单位为份，右对齐，左补空格。
									 //对于国债预发行产品，备注中补充以下字段，每个字段根据格式定义，参照本文档txt文件对齐方式约定，字段定长，字段间以&分隔，字段及格式定义依次为
									 // 1、招标方式C1，‘1’表示国债预发行利率招标，‘2’表示国债预发行价格招标。
									 // 2、基准价格N11(3)，当价格招标时为基准价格，当利率招标时为基准收益率。
									 // 3、参考久期N6(2)，单位为年。
									 // 4、当期发行量N9，单位为手。
} T_CPXX, T_SH_BaseInfo, *PCPXX, *PSH_BaseInfo;

//1.9 ETF扩展行情消息
typedef struct t_SH_ETFExtends
{
	T_I32		nTime;				     //时间(HHMMSSmmm)
	T_I32       nIOPV;                   //ETF净值估值
	T_I32       nEtfBuyNum;              //ETF申购笔数
	T_I64       i64EtfBuyAmount;         //ETF申购数量
	T_I64       i64EtfBuyMoney;           //ETF申购金额
	T_I32       nEtfSellNum;                //ETF赎回笔数
	T_I64       i64EtfSellAmount;           //ETF赎回数量
	T_I64       i64EtfSellMoney;            //ETF赎回金额
	T_I32       nWithDrawBuyNum;         //买入撤单笔数
	T_I64       i64WithDrawBuyAmount;    //买入撤单数量
	T_I64       i64WithDrawBuyMoney;     //买入撤单金额
	T_I32       nWithDrawSellNum;        //卖出撤单笔数
	T_I64       i64WithDrawSellAmount;   //卖出撤单数量
	T_I64       i64WithDrawSellMoney;    //卖出撤单金额
}T_ETFEXTENDS,T_SH_ETFEXTENDS, *PSH_ETFEXTENDS;
;
#pragma pack(pop)
#endif //_T_SH_MARKET_