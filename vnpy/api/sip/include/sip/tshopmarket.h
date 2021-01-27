#ifndef _T_SHOPTION_H_ 
#define _T_SHOPTION_H_
#include "tdef.h"
#define SHOP     8 //上交所期权市场

//-----------------------------------上交所期权-------------------------------------------
#define ID_SHOP_BASEINFO    0x01   //期权基础信息 对应T_SH_OptionBaseInfo
#define ID_SHOP_MARKETDATA  0x02   //期权市场代码 对应T_SH_OptionMarketData
#define ID_SHOP_LEVELFAST   0x03   //上海期权快速行情  对应T_SH_OptionMarketData

#pragma pack(push,1)
//1.1 上交所期权基础信息
typedef struct t_SHOP_BaseInfo
{

       char  sSecurityID[9];                                //	合约编码	C8	期权合约的合约编码
       char  sContractID[19];                               //	合约交易代码	C19	
       char  sContractSymbol[21];                           //	期权合约简称	C20	
       char  sUnderlyingSecurityID[7];                      //	标的证券代码	C6	
       char  sUnderlyingSymbol[9];                          //	基础证券证券名称	C8	
       char  sUnderlyingType[4];                            //	标的证券类型	C3	EBS – ETF， ASH – A股
       char  cOptionType;	                                //  欧式美式	C1	若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”
       char  cCallOrPut;                                    //	认购认沽	C1	认购，则本字段为“C”；若为认沽，则本字段为“P”
       T_U32 uContractMultiplierUnit;                       //	合约单位	N11	经过除权除息调整后的合约单位
       T_U32 uExercisePrice;	                            //  期权行权价	N11(4)	经过除权除息调整后的期权行权价，精确到0.1厘
       char  sStartDate[9];                                 //	首个交易日	C8	期权首个交易日,YYYYMMDD
       char  sEndDate[9];                                   //	最后交易日	C8	期权最后交易日/行权日，YYYYMMDD 
       char  sExerciseDate[9];                              //	期权行权日	C8	期权行权日，YYYYMMDD 
       char  sDeliveryDate[9];                              //	行权交割日	C8	行权交割日，默认为行权日的下一个交易日，YYYYMMDD
       char  sExpireDate[9];	                            //  期权到期日	C8	期权到期日，YYYYMMDD
       char  cUpdateVersion;	                            //  合约版本号	C1	期权合约的版本号
       T_I64 iTotalLongPosition;                            //	当前合约未平仓数	N12	单位是 （张）
       T_U32 uSecurityClosePx;                              //	合约前收盘价	N11(4)	昨日收盘价，右对齐，单位：元（精确到0.1厘）
       T_U32 uSettlPrice;                                   //	合约前结算价	N11(4)	昨日结算价，如遇除权除息则为调整后的结算价（合约上市首日填写参考价），右对齐，单位：元（精确到0.1厘）
       T_U32 uUnderlyingClosePx;                            //	标的证券前收盘	N11(4)	期权标的证券除权除息调整后的前收盘价格，右对齐，单位：元（精确到0.1厘）
       char  cPriceLimitType;                               //	涨跌幅限制类型	C1	‘N’有涨跌幅限制类型
       T_U32 uDailyPriceUpLimit;                            //	涨幅上限价格	N11(4)	当日期权涨停价格，单位：元（精确到0.1厘）
       T_U32 uDailyPriceDownLimit;                          //	跌幅下限价格	N11(4)	当日期权跌停价格，单位：元（精确到0.1厘）
       T_U32 uMarginUnit;                                   //	单位保证金	N16(2)	当日持有一张合约所需要的保证金数量，精确到分
       T_I32 nMarginRatioParam1;                            //	保证金计算比例参数一	N6(2)	保证金计算参数，单位：%
       T_I32 nMarginRatioParam2;                            //	保证金计算比例参数二	N6(2)	保证金计算参数，单位：%
       T_U32 uRoundLot;                                     //	整手数	N12	一手对应的合约数
       T_U32 uLmtOrdMinFloor;                               //	单笔限价申报下限	N12	单笔限价申报的申报张数下限。
       T_U32 uLmtOrdMaxFloor;                               //	单笔限价申报上限	N12	单笔限价申报的申报张数上限。
       T_U32 uMktOrdMinFloor;                               //	单笔市价申报下限	N12	单笔市价申报的申报张数下限。
       T_U32 uMktOrdMaxFloor;                               //	单笔市价申报上限	N12	单笔市价申报的申报张数上限。
       T_U32 uTickSize;                                     //  最小报价单位	N11(4)	单位：元，精确到0.1厘
       char  sSecurityStatusFlag[9];                        //	期权合约状态信息标签	C8	该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
                                                                /*第1位：‘0’表示可开仓，‘1’表示限制卖出开仓（不.包括备兑开仓）和买入开仓。
                                                                第2位：‘0’表示未连续停牌，‘1’表示连续停牌。
                                                                第3位：‘0’表示未临近到期日，‘1’表示距离到期日不足10个交易日。
                                                                第4位：‘0’表示近期未做调整，‘1’表示最近10个交易日内合约发生过调整。
                                                                第5位：‘A’表示当日新挂牌的合约，‘E’表示存续的合约，‘D’表示当日摘牌的合约。*/
}T_SHOP_BaseInfo,*PSHOP_BaseInfo;

//1.2 上海所期权行情
typedef struct t_SHOP_MarketData
{
    T_I32 nDataTimestamp;  //时间戳 HHMMSSmmm  如果期权合约的产品代码为“00000000”，则表示行情时间；
    T_I64 iPreSettlPrice;  //昨日结算价 4 decimal places
    T_I64 iSettlPrice;     //今日结算价	4 decimal places
    T_I64 iOpenPx;         //开盘价	Today’s open price 4 decimal places 如果期权合约的产品代码为“00000000”，则表示收盘标志，	111111表示收盘
    T_I64 iHighPx;         //最高价	Today’s high 4 decimal places
    T_I64 iLowPx;          //最低价	Today’s low  4 decimal places
    T_I64 iLastPx;         //现价 Last price 4 decimal places 如果期权合约的产品代码为“00000000”，则表示记录数 *
    T_I64 iAuctionPrice;   //波动性中断参考价	4 decimal places
    T_I64 iAuctionQty;     //波动性中断集合竞价虚拟匹配量
    T_I64 iTotalLongPosition; //当前合约未平仓数量
    T_I64 iBidSize[5];     // 申买量
    T_I64 iBidPx[5];       // 申买价
    T_I64 iOfferSize[5];   // 申卖量
    T_I64 iOfferPx[5];     // 申卖价
    T_I64 iTotalVolumeTrade; //成交数	Trade volume of this security
    T_I64 iTotalValueTrade;  //成交金额（2位小数）Turnover of this security
    char  sTradingPhaseCode[8]; //成交阶段代码,交易时间段由4位扩至8位 
    //   期权交易状态，取值范围如下：
    //该字段为4位字符串，左起每位表示特定的含义，无定义则填空格。
    //	第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘V’表示波动性中断，‘P’表示临时停牌、‘U’收盘集合竞价。‘M’表示可恢复交易的熔断（盘中集合竞价）,‘N’表示不可恢复交易的熔断（暂停交易至闭市）
    //	第2位：‘0’表示未连续停牌，‘1’表示连续停牌。（预留，暂填空格）
    //	第3位：‘0’表示不限制开仓，‘1’表示限制备兑开仓，‘2’表示卖出开仓，‘3’表示限制卖出开仓、备兑开仓，‘4’表示限制买入开仓，‘5’表示限制买入开仓、备兑开仓，‘6’表示限制买入开仓、卖出开仓，‘7’表示限制买入开仓、卖出开仓、备兑开仓
    //	第4位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’ 表示此产品在当前时段可接受进行新订单申报。
    //	第5位至第8位，预留（暂填空格）
    char sTransactTimeOnly[12];//最近询价时间，格式为HH:MM:SS.000。当日没有询价时，显示默认值00:00:00.000。


}T_SHOP_MarketData,*PSHOP_MarketData;

#pragma pack(pop)
#endif //_T_SHOPTION_H_

    
