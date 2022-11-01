#ifndef _T_SZOP_MARKET_
#define _T_SZOP_MARKET_

#include "tdef.h"
//////////////////////////////////////////////////////////////////////////
//深交所期权行情
//////////////////////////////////////////////////////////////////////////

#define  SZOP        11                 //深交所期权

#define ID_SZOP_BASEINFO      1     //期权基础信息
#define ID_SZOP_MARKETDATA    2     //期权快照行情
#pragma pack(push,1)
//////////////////////////////////////////////////////////////////////////
//深交所所有证券代码共有  securities_YYYYMMDD.xml

typedef struct t_StockParams
{
	char    sIndustryClassification[4];// 行业种类    C4 
	T_I32   nPreviousYearProfitPerShare;//	上年每股利润 		N10(4)
	T_I32   nCurrentYearProfitPerShare;//	本年每股利润  		N10(4)
	char    cOfferingFlag;//	是否处于要约收 	购期 	C1  Y=是 		N=否
}T_STOCKPARAMS;

//基金特有字段 相关证券类别代码（14、15、16、17、18、19、20、23、24、25、26）
typedef struct t_FundParams
{
	T_I64   i64NAV;  //T-1 日基金净值 N13(4) 
}T_FUNDPARAMS;

//债券特有字段 BondParams 相关证券类别代码（5、6、7、8、9、10、11、34、35）
typedef struct t_BondParams
{
	T_I64   i64CouponRate;//    票面年利率    N8(4) 
	T_I64   i64IssuePrice;//	贴现发行价  IssuePrice  N13(4) 
	T_I64   i64Interest;//	每百元应计利息    N12(8) 
	T_I32	nInterestAccrualDate;//发行起息日或本 	次付息起息日 		N8
	T_I32   nMaturityDate; //	到期日    N8 		
	char    cOfferingFlag;//否处于转股回售期 		C1  Y=是 		N=否
}T_BONDPARAMS;

// 权证特有字段 WarrantParams 相关证券类别代码（28）
typedef struct t_WarrantParams
{
	T_I64   i64ExercisePrice; // 行权价 		N13(4) 
	T_I64   i64ExerciseRatio; // 行权比例       N10(4) 
	T_I32	nExerciseBeginDate;//  行权起始日   N8 
	T_I32   nExerciseEndDate; //	行权截止日  N8 
	char    cCallOrPut;//	认购或认沽 	C1  C = Call 	P = Put
	char    cDeliveryType;//	交割方式		C1   S = 证券结算 C = 现金结算 
	T_I64   i64ClearingPrice;//	结算价格 	  N13(4) 
	char    cExerciseType;//	行权方式   	C1  A = 美式 E = 欧式 	B = 百慕大式
	T_I32	nLastTradeDay;//最后交易日 		  N8 
}T_WARRANTPARAMS;

// 质押式回购交易代码特有字段 RepoParams 	相关证券类别代码(12)
typedef struct t_RepoParams
{
	T_I32   nExpirationDays;//购回期限  N4
}T_REPOPARAMS;


//////////////////////////////////////////////////////////////////////////
//期权特有字段  相关证券类别代码（29、30)
typedef struct t_OptionParams
{
	char          cCallOrPut;  //认购或认沽 C1 C=Call P=Put
	T_U16         usListType;  //挂牌类型 N2  1=品种新挂 2=到期加挂 3=调整加挂	4=波动加挂
	T_I32         nDeliveryDay; //交割日期  N8
	T_I32         nDeliveryMonth; //交割月份  N6  YYYYMM
	char          cDeliveryType; //交割方式 C1  S=证券结算 C=现金结算
	T_I32         nExerciseBeginDate;//行权起始日期 N8
	T_I32         nExerciseEndDate;//行权结束日期 N8
	T_I64         i64ExercisePrice;//行权价 N13(4)
	char          cExerciseType;//行权方式 C1 A=美式 E=欧式 B=百慕大式
	T_I32         nLastTradeDay;//最后交易日 N8
	T_U16         usAdjustTimes;//调整次数 N2
	T_I64         i64ContractUnit;//合约单位 N15(2)
	T_I64         i64PrevClearingPrice;//昨日结算价 N13(4)
	T_I64         i64ContractPosition;//合约持仓量  N18(2)
}T_OPTIONPARAMS,*POPTIONPARAMS;

//优选股特有字段 相关证券类别代码（33）
typedef struct t_PreferredStockParams
{
	char      cOfferingFlag;   //是否处于转股回售期 C1 Y=是 N=否
}T_PREFERREDSTOCKPARAMS;
typedef struct t_BaseInfo
{
	char    sSecurityID[8];         //证券代码 SecurityID C8
	char    sSecurityIDSource[4];   //证券代码源 4=ISIN 102=深圳证券交易所 C4
	char    sSymbol[40];            //证券简称 C40
	char    sEnglishName[40];       //英文简称 对于期权填写合约代码 C40
	char    sISIN[12];              //ISIN代码 C12

	char    sUnderlyingSecurityID[8];//基础证券代码 C8
	char    sUnderlyingSecurityIDSource[4];   //基础证券代码源 102=深圳证券交易所 C4
	T_U32   uListDate;              //上市日期 N8
	T_U16   usSecurityType;         //证券类别 N4
    char    sCurrency[4];           //货币代码 C4   CNY=人民币 HKD=港币
	T_I64   i64QtyUnit;             //数量单位 委托数量字段必须为该证券数量单位的整数倍 N15(2) 此处整型处理，放大10000倍
	char    cDayTrading;            //是否支持当日回转交易 Y=支持 N=不支持 C1
	T_I64   i64PrevClosePx;         //昨日收盘价 N13(4)
	T_U16   usSecurityStatus[20];    //证券状态代码:
	    //1-停牌
		//2-除权
		//3-除息
		//4-ST
		//5-*ST
		//6-上市首日
		//7-公司再融资
		//8-恢复上市首日
		//9-网络投票
		//10-退市整理期
		//12-增发股份上市
		//13-合约调整
		//14-暂停上市后协议转让
	T_I64   i64OutstandingShare;    //总发行量  N18(2)
	T_I64   i64PublicFloatShareQuantity; //流通股数 N18(2)
	T_I64   i64ParValue;//面值 N13(4)
	char    cGageFlag;//是否可作为融资融券可充抵保证金证券 C1  Y=是 N=否
	T_I32   nGageRatio;//可充抵保证金折算率 N5(2)
	char    cCrdBuyUnderlying;//是否为融资标的 C1 Y=是 N=否
	char    cCrdSellUnderlying;//是否为融券标的C1 Y=是 N=否
	T_I32   nPriceCheckMode;  //提价检查方式 N2 0=不检查 	1=不低于最近成交价 	2=不低于昨收价 	3=不低于最高叫买 4=不低于最低叫卖
	char    cPledgeFlag;//是否可质押入库 C1 Y=是 N=否
	T_I64   i64ContractMultiplier;//对回购标准券折算率 N6(5)
	char    sRegularShare[8];//对应回购标准券 C8
	char    cQualificationFlag;//是否需要对该证券作投资者适当性管理		Y=是 		N=否
	union T_EXTENDFIELD //根据证券类别代码 usSecurityType 确定其结构 参见以下表3-2的字典定义
	{
		T_STOCKPARAMS stockParams;    //股票特有字段 StockParams 相关证券类别代码对应（1、2、3、4）
		T_FUNDPARAMS  fundParams;     //基金特有字段 相关证券类别代码（14、15、16、17、18、19、20、23、24、25、26）
		T_BONDPARAMS  bondParams;     //债券特有字段 BondParams 相关证券类别代码（5、6、7、8、9、10、11、34、35）
		T_WARRANTPARAMS warrantParams;// 权证特有字段 WarrantParams 相关证券类别代码（28）
		T_REPOPARAMS repoParams;      // 质押式回购交易代码特有字段 RepoParams 	相关证券类别代码(12)
		T_OPTIONPARAMS optionParmas;  //期权特有字段  相关证券类别代码（29、30)
		T_PREFERREDSTOCKPARAMS preferedStockParams; //优选股特有字段 相关证券类别代码（33）
	}tExtendParmas;
	  
}T_BASEINFO,*PBASEINFO;
 /* 表 3-2 证券类别定义
		类别名称  类别代码
		主板 A 股  1
		中小板股票  2
		创业板股票  3
		主板 B 股  4
		国债 （含地方债） 5
		企业债  6
		公司债  7
		可转债  8
		私募债  9
		可交换私募债  10
		证券公司次级债  11
		质押式回购  12
		资产支持证券  13
		本市场股票 ETF  14
		跨市场股票 ETF  15
		跨境 ETF  16
		本市场实物债券ETF	17
		现金债券 ETF  18
		黄金 ETF  19
		货币 ETF  20
		杠杆 ETF  21（预留）
		商品期货 ETF  22（预留）
		标准 LOF  23
		分级子基金  24
		封闭式基金  25
		仅申赎基金  26
		权证  28
		个股期权  29
		ETF 期权  30
		优先股  33
		证券公司短期债  34
		可交换公司债  35*/



//现货 集中竞价交易业务参考信息（ cashauctionpramas) cashauctionparams_YYYYMMDD.xml
typedef struct t_CashAuctionParams
{
	char    sSecurityID[8];         //证券代码 C8
	char    sSecurityIDSource[4];      //102 = 深圳证券交易所 C4
	T_I64   i64BuyQtyUpperLimit;    //买数量上限 N15(2)  买委托数量的上限
	T_I64   i64SellQtyUpperLimit;   //	卖数量上限	N15(2)  卖委托数量的上限
	T_I64   i64BuyQtyUnit;//	买数量单位 		N15(2)  每笔买委托的委托数量必须是买数量单位的整数倍
	T_I64   i64SellQtyUnit; //	卖数量单位	N15(2)  每笔卖委托的委托数量必须是卖数量单位的整数倍
	T_I64   i64PriceTick;  //	价格档位 	N13(4)
	struct  T_PriceLimitSetting //竞价限价参数
	{
		char  cType;// 参数类型 Type C1  O=开盘集合竞价 T=连续竞价 	C=收盘集合竞价
		char  cHasPriceLimit;//否有涨跌 限制 C1 Y=是	N=否
		char  cReferPriceType;//  基准价类型 C1 1=昨收价
		char  cLimitType;  //	涨跌限制类型 C1  1=幅度（百分比） 		2=价格（绝对值）
		T_I64 i64LimitUpRate;//    上涨幅度	N10(3)
		T_I64 i64LimitDownRate; // 下跌幅度 N10(3)
		T_I64 i64LimitUpAbsolute;//  上涨限价 			N10(4)
		T_I64 i64LimitDownAbsolute;//	  下跌限价		N10(4)
		char  cHasAuctionLimit;//  是否有有效竞价范围限制 	C1 	Y=是 	N=否
		char  cAuctionLimitType;// 有效范围限制类型		C1  1=幅度（百分比）2=价格（绝对值）
		T_I64 i64AuctionUpDownRate;//有效范围涨跌幅度	N10(3)
		T_I64 i64AuctionUpDownAbsolute;//	有效范围涨跌价格 	N10(4)
	}tPriceLimitElement[5];
	char  cMarketMakerFlag;//做市商标志 C1  标识是否有做市商 Y=是	N=否
}T_CASHAUCTIONPARAMS;


//衍生品参考信息，目前仅包含期权  derivativeauctionparams_YYYYMMDD.xml

typedef struct t_DerivativeParams
{
	char    sSecurityID[8];         //证券代码 C8
	char    sSecurityIDSource;      //102 = 深圳证券交易所 C4
	T_I64   i64BuyQtyUpperLimit;    //限价买委托数量上限 N15(2)
	T_I64   i64SellQtyUpperLimit;   //限价卖委托数量上限 N15(2)
	T_I64   i64MarketOrderBuyQtyUpperLimit;//  市价买数量上限 N15(2)  市价买委托数量的上限
	T_I64   i64MarketOrderSellQtyUpperLimit;//	市价卖数量上限 N15(2)  市价卖委托数量的上限
	T_I64   i64QuoteOrderBuyQtyUpperLimit;//	报价买数量上限 N15(2)  报价买委托数量的上限
	T_I64   i64QuoteOrderSellQtyUpperLimit; //	报价卖数量上限 	N15(2)  报价卖委托数量的上限
	T_I64   i64BuyQtyUnit;          //买数量单位 N15(2)
	T_I64   i64SellQtyUnit;        //卖数量单位 N15(2)
	T_I64   i64PriceTick;          //价格档位 N13(4)
	T_I64   i64PriceUpperLimit;     //涨停价 N13(4)
	T_I64   i64PriceLowerLimit;     //跌停价 N13(4)
	T_I64   i64LastSellMargin;     //昨卖开每张保证金 N18(4)
	T_I64   i64SellMargin;         //今卖开每张保证金 N18(4)
	T_I32   nMarginRatioParam1;   //保证金比例计算参数一 N4(2)
	T_I32   nMarginRatioParam2;   //保证金比例计算参数一 N4(2)
	char    cMarketMakerFlag;     //做市商标志  C1 Y=是 N=否
}T_DERIVATIVEPARAMS,*PDERIVATIVEPARAMS;

typedef struct t_SZ_BaseInfo 
{
	T_BASEINFO          tBase;      //基础信息
	T_CASHAUCTIONPARAMS tCashParams;      //现货 集中竞价交易业务参考信息
}T_SZ_BASEINFO,*PSZ_BASEINFO;

typedef struct t_SZOP_BaseInfo
{
	T_BASEINFO          tBase;      //基础信息
	T_DERIVATIVEPARAMS  tDeParmas;  //衍生品信息

}T_SZOP_BASEINFO,*PSZOP_BASEINFO;  //ID_SZOP_BASEINFO

//指数 信息 indexinfo_YYYYMMDD.xml  
typedef struct t_IndexInfo
{
	char    sSecurityID[8];         //指数代码 C8
	char    sSecurityIDSource[4];      //102 = 深圳证券交易所 C4          
	char    sSymbol[40];            //指数简称 C40
	char    sEnglishName[40];       //英文简称 
	char    sCurrency[4];           //计算币种  Currency C4  币种 CNY = 人民币	HKD = 港币
	T_I64   i64PrevCloseIdx;       //昨收指数点位  PrevCloseIdx  N18(5)
			
}T_INDEXINFO;

typedef struct t_SZOP_MarketData
{
	T_I32       nTime; //数据生成时间 HHMMSSmmm格式
	T_U16       usChannelNo; //频道代码
	char        sMDStreamID[3] ;//行情类别
	char        sSecrityID[8];//证券代码
	char        sSecurityIDSource[4];//证券代码源 101=深圳证券交易所
	char        sTradingPhaseCode[8];//产品所处的交易阶段代码 第0位：S=启动（开市前） O=开盘集合竞价 T=连续竞价 B=休市 C=收盘集合竞价 E=已闭市 H=临时停牌 A=盘后交易 第1位：0=正常状态 1=全天停牌
	T_I64       i64PrevClosePx;//昨收价
	T_I64       i64NumTrades; //成交笔数
	T_I64       i64TotalVolumeTrade;//成交总量
	T_I64       i64TotalValueTrade;//成交总金额

	T_I64       i64LastPrice;//最近价
	T_I64       i64OpenPrice;//开盘价
	T_I64       i64HighPrice;//最高价
	T_I64       i64LowPrice;//最低价
	T_I64       i64BuyAvgPrice;//x3=买入汇总（总量及加权平均价）
	T_I64       i64BuyVolumeTrade;//x3=买入汇总（总量及加权平均价）
	T_I64       i64SellAvgPrice;//x4=卖出汇总（总量及加权平均价）
	T_I64       i64SellVolumeTrade;//x4=卖出汇总（总量及加权平均价）
	T_I64       i64OfferPrice[10];//卖委托价格
	T_I64       i64OfferQty[10]; //卖委托量
	T_I64       i64BidPrice[10];//买委托价格
	T_I64       i64BidQty[10];//买委托量
	T_I64       i64PriceUpperLimit;        //涨停价 999999999.9999 表示无涨停价格限制
	T_I64       i64PriceLowerLimit;        //跌停价 对于价格可以为负数的业务，-999999999.9999 表示无跌停价格限制；对于价格不可以为负数的业务，则填写价格档位，表示无跌停价格限制，比如对于股票现货集中竞价业务填写 0.01
	T_I64       i64ContractPosition; //合约持仓量


	//行情条目类别 0=买入 1=卖出 2=最近价 4=开盘价 7=最高价 8=最低价
	//x1= 升跌一 x2=升跌二 x3=买入汇总（总量及加权平均价）x4=卖出汇总（总量及加权平均价）
	//x5=股票市盈率一 x6=股票市盈率二 x7=基金T-1日净值 x8=基金实时参考净值(包括ETF的IOPV)
	//x9=权证溢价率 xe=涨停价 xf=跌停价 xg=合约持仓量
}T_SZOP_MARKETDATA,*PSZOP_MARKETDATA;

#pragma pack(pop)

#endif// _T_SZOP_MARKET_
