/**
* 版权所有(C)2012-2016, 大连飞创信息技术有限公司
* 文件名称：DFITCApiStruct.h
* 文件说明：定义接口所需的数据接口
* 当前版本：1.0.14.91
* 作者：XSpeed项目组
* 发布日期：2015年5月6日
*/

#ifndef DFITCAPISTRUCT_H_
#define DFITCAPISTRUCT_H_

#include "DFITCApiDataType.h"

#define APISTRUCT

///心跳包
struct APISTRUCT DFITCTimeOutField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
};


///请求报单数据类型(基本报单)
struct APISTRUCT DFITCInsertOrderField
{
    DFITCAccountIDType                  accountID;                    //资金账户
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号, 由API使用者维护，在同一个会话中不能重复
    DFITCInstrumentIDType               instrumentID;                 //合约代码, 支持目前国内4个期货交易所的所有合约，包括大商所/郑商所的套利合约
    DFITCPriceType                      insertPrice;                  //报单价格, 当报单类型为市价时，该字段不起作用
    DFITCAmountType                     orderAmount;                  //报单数量
    DFITCBuySellTypeType                buySellType;                  //买卖标志
    DFITCOpenCloseTypeType              openCloseType;                //开平标志
    DFITCSpeculatorType                 speculator;                   //投保类型, 支持投机、套利、套保
    DFITCInsertType                     insertType;                   //自动单类别(默认为普通订单)
    DFITCOrderTypeType                  orderType;                    //报单类型, 支持限价 、市价；上期所合约不支持市价，均按限价进行处理
    DFITCOrderPropertyType              orderProperty;                //报单附加属性, 支持None、FAK、FOK
    DFITCInstrumentTypeType             instrumentType;               //合约类型, 可选值：期货、期权
    DFITCAmountType                     minMatchAmount;               //最小成交量
    DFITCReservedType                   reservedType2;                //预留字段2
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCPriceType                      profitLossPrice;              //止盈止损价格        
};


///撤单数据类型
struct APISTRUCT DFITCCancelOrderField
{
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCRequestIDType                  lRequestID;                   //请求ID
};


///委托响应类型
struct APISTRUCT DFITCOrderRspDataRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCPriceType                      fee;                          //手续费,该字段仅供下单时使用
    DFITCPriceType                      margin;                       //冻结保证金,该字段仅供下单时使用
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码 
    DFITCSessionIDType                  sessionID;                    //会话ID  
    DFITCExchangeIDType                 exchangeID;                   //交易所  
    DFITCBuySellTypeType                buySellType;                  //买卖    
    DFITCOpenCloseTypeType              openCloseType;                //开平
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCSpeculatorType                 speculator;                   //投资类别
    DFITCPriceType                      insertPrice;                  //委托价
    DFITCPriceType                      profitLossPrice;              //止盈止损价格
    DFITCAmountType                     minMatchAmount;               //最小成交量
    DFITCAmountType                     orderAmount;                  //委托数量
    DFITCInsertType                     insertType;                   //自动单类别
    DFITCOrderTypeType                  orderType;                    //订单类型	
    DFITCOrderPropertyType              orderProperty;                //订单属性
    DFITCClientIDType                   clientID;                     //交易编码
};



///查询资金数据类型
struct APISTRUCT DFITCCapitalField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
};


///查询持仓数据类型
struct APISTRUCT DFITCPositionField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCInstrumentTypeType             instrumentType;               //合约类型
};


///交易所合约
struct APISTRUCT DFITCExchangeInstrumentField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCExchangeIDType                 exchangeID;                   //交易所编码
    DFITCInstrumentTypeType             instrumentType;               //合约类型
};


///用户登录数据类型
struct APISTRUCT DFITCUserLoginField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCPasswdType                     passwd;                       //密码
    DFITCCompanyIDType                  companyID;                    //厂商ID
};


///用户退出类型
struct APISTRUCT DFITCUserLogoutField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金帐号ID
    DFITCSessionIDType                  sessionID;                    //会话ID
};


///委托回报
struct APISTRUCT DFITCOrderRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCOrderSysIDType                 OrderSysID;                   //报单编号
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
    DFITCSessionIDType                  sessionID;                    //会话ID
    DFITCDateType                       SuspendTime;                  //挂起时间
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所 
    DFITCBuySellTypeType                buySellType;                  //买卖
    DFITCOpenCloseTypeType              openCloseType;                //开平
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCSpeculatorType                 speculator;                   //投资类别
    DFITCPriceType                      insertPrice;                  //委托价
    DFITCPriceType                      profitLossPrice;              //止盈止损价格
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCAmountType                     cancelAmount;                 //撤单数量
    DFITCAmountType                     orderAmount;                  //委托数量
    DFITCInsertType                     insertType;                   //自动单类别
    DFITCOrderTypeType                  orderType;                    //报单类型
    DFITCSPDOrderIDType                 extSpdOrderID;                //算法单编号
    DFITCReservedType                   reservedType2;                //预留字段2	
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCOrderPropertyType              orderProperty;                //订单属性	
    DFITCAmountType                     minMatchAmount;               //最小成交量
    DFITCClientIDType                   clientID;                     //交易编码
    DFITCErrorMsgInfoType               statusMsg;                    //状态信息
};


///成交回报
struct APISTRUCT DFITCMatchRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCOrderSysIDType                 OrderSysID;                   //报单编号(交易所报单编号)
    DFITCMatchIDType                    matchID;                      //成交编号
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCBuySellTypeType                buySellType;                  //买卖
    DFITCOpenCloseTypeType              openCloseType;                //开平标志
    DFITCPriceType                      matchedPrice;                 //成交价格
    DFITCAmountType                     orderAmount;                  //委托数量
    DFITCAmountType                     matchedAmount;                //成交数量
    DFITCDateType                       matchedTime;                  //成交时间
    DFITCPriceType                      insertPrice;                  //报价
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCMatchType                      matchType;                    //成交类型
    DFITCSpeculatorType                 speculator;                   //投保
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCFeeType                        fee;                          //手续费
    DFITCSessionIDType                  sessionID;                    //会话标识
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCOrderAnswerStatusType          orderStatus;                  //申报结果
    DFITCPriceType                      margin;                       //开仓为保证金,平仓为解冻保证金
    DFITCPriceType                      frozenCapita;                 //成交解冻委托冻结的资金
    DFITCAdjustmentInfoType             adjustmentInfo;               //组合或对锁的保证金调整信息,格式:[合约代码,买卖标志,投资类别,调整金额;] 
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCPriceType                      turnover;                     //成交金额
    DFITCOrderTypeType                  orderType;                    //报单类型
    DFITCInsertType                     insertType;                   //自动单类别
    DFITCClientIDType                   clientID;                     //交易编码
};


///撤单回报
struct APISTRUCT DFITCOrderCanceledRtnField
{
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCOrderSysIDType                 OrderSysID;                   //报单编号  
    DFITCInstrumentIDType               instrumentID;                 //合约代码     
    DFITCPriceType                      insertPrice;                  //报单价格  
    DFITCBuySellTypeType                buySellType;                  //买卖类型
    DFITCOpenCloseTypeType              openCloseType;                //开平标志
    DFITCAmountType                     cancelAmount;                 //撤单数量
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCSpeculatorType                 speculator;                   //投保
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCDateType                       canceledTime;                 //撤单时间
    DFITCSessionIDType                  sessionID;                    //会话标识
    DFITCOrderAnswerStatusType          orderStatus;                  //申报结果
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCAmountType                     orderAmount;                  //委托数量   
    DFITCPriceType                      margin;                       //保证金
    DFITCPriceType                      fee;                          //手续费
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCPriceType                      profitLossPrice;              //止盈止损价格
    DFITCAmountType                     minMatchAmount;               //最小成交量
    DFITCInsertType                     insertType;                   //自动单类别
    DFITCClientIDType                   clientID;                     //交易编码
    DFITCErrorMsgInfoType               statusMsg;                    //状态信息
    DFITCOrderPropertyType              orderProperty;                //报单附加属性
};


///错误信息
struct APISTRUCT DFITCErrorRtnField
{
    DFITCRequestIDType                  requestID;                    //请求ID
    DFITCSessionIDType                  sessionID;                    //会话标识
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCErrorIDType                    nErrorID;                     //错误ID
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCErrorMsgInfoType               errorMsg;                     //错误信息
    DFITCInstrumentIDType               instrumentID;                 //合约代码
};


///返回资金信息
struct APISTRUCT DFITCCapitalInfoRtnField
{
    DFITCRequestIDType                  requestID;                    //请求ID
    DFITCAccountIDType                  accountID;                    //资金帐号
    DFITCEquityType                     preEquity;                    //上日权益
    DFITCEquityType                     todayEquity;                  //当日客户权益
    DFITCProfitLossType                 closeProfitLoss;              //平仓盈亏
    DFITCProfitLossType                 positionProfitLoss;           //持仓盈亏
    DFITCProfitLossType                 frozenMargin;                 //冻结资金
    DFITCProfitLossType                 margin;                       //持仓保证金
    DFITCProfitLossType                 fee;                          //当日手续费
    DFITCProfitLossType                 available;                    //可用资金
    DFITCProfitLossType                 withdraw;                     //可取资金
    DFITCRiskDegreeType                 riskDegree;                   //风险度
    DFITCPremiumType                    todayPremiumIncome;           //本日权利金收入
    DFITCPremiumType                    todayPremiumPay;              //本日权利金付出
    DFITCPremiumType                    yesterdayPremium;             //昨权利金收付
    DFITCMarketValueType                optMarketValue;               //期权市值
    DFITCProfitLossType                 floatProfitLoss;              //浮动盈亏
    DFITCProfitLossType                 totFundOut;                   //总出金
    DFITCProfitLossType                 totFundIn;                    //总入金
};


///返回持仓信息
struct APISTRUCT DFITCPositionInfoRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金帐号ID
    DFITCExchangeIDType                 exchangeID;                   //交易所代码
    DFITCInstrumentIDType               instrumentID;                 //合约号
    DFITCBuySellTypeType                buySellType;                  //买卖
    DFITCPriceType                      openAvgPrice;                 //开仓均价
    DFITCPriceType                      positionAvgPrice;             //持仓均价
    DFITCAmountType                     positionAmount;               //持仓量
    DFITCAmountType                     totalAvaiAmount;              //总可用
    DFITCAmountType                     todayAvaiAmount;              //今可用
    DFITCAmountType                     lastAvaiAmount;               //昨可用
    DFITCAmountType                     todayAmount;                  //今仓
    DFITCAmountType                     lastAmount;                   //昨仓
    DFITCAmountType                     tradingAmount;                //平今挂单量
    DFITCProfitLossType                 datePositionProfitLoss;       //盯市持仓盈亏
    DFITCProfitLossType                 dateCloseProfitLoss;          //盯市平仓盈亏
    DFITCProfitLossType                 dPremium;                     //权利金
    DFITCProfitLossType                 floatProfitLoss;              //浮动盈亏
    DFITCProfitLossType                 dMargin;                      //占用保证金
    DFITCSpeculatorType                 speculator;                   //投保类别
    DFITCClientIDType                   clientID;                     //交易编码
    DFITCPriceType                      preSettlementPrice;           //昨结算价
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCAmountType                     yesterdayTradingAmount;       //平昨挂单量
};


///用户登录返回信息
struct APISTRUCT DFITCUserLoginInfoRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金帐号ID
    DFITCAccountLoginResultType         loginResult;                  //登录结果
    DFITCLocalOrderIDType               initLocalOrderID;             //初始本地委托号
    DFITCSessionIDType                  sessionID;                    //sessionID(会话ID)
    DFITCErrorIDType                    nErrorID;                     //错误ID
    DFITCErrorMsgInfoType               errorMsg;                     //错误信息
    DFITCTimeType                       DCEtime;                      //大商所时间
    DFITCTimeType                       SHFETime;                     //上期所时间
    DFITCTimeType                       CFFEXTime;                    //中金所时间
    DFITCTimeType                       CZCETime;                     //郑商所时间
    DFITCTimeType                       INETime;                      //上能所时间
};


///用户退出返回信息
struct APISTRUCT DFITCUserLogoutInfoRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCAccountLogoutResultType        logoutResult;                 //退出结果
    DFITCErrorIDType                    nErrorID;                     //错误ID
    DFITCErrorMsgInfoType               errorMsg;                     //错误信息
};


///套利合约查询
struct  APISTRUCT DFITCAbiInstrumentField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCExchangeIDType                 exchangeID;                   //交易所代码
};


///套利合约返回信息
struct APISTRUCT DFITCAbiInstrumentRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCExchangeIDType                 exchangeID;                   //交易所编码
    DFITCInstrumentIDType               InstrumentID;                 //合约代码
    DFITCInstrumentNameType             instrumentName;               //合约名称
};


///指定的合约
struct APISTRUCT DFITCSpecificInstrumentField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentIDType               InstrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCInstrumentTypeType             instrumentType;               //合约类型
};


//****************期权扩展行情合约回报定义*************************
///指定的合约信息
struct APISTRUCT DFITCSpecificInstrumentFieldEX
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCFunctionIDType                 FunctionID;                   //功能ID
    DFITCInstrumentIDType               InstrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCInstrumentTypeType             instrumentType;               //合约类型
};
//*****************************************

///行情订阅返回信息
struct APISTRUCT DFITCActiveContractField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCActiveContractType             activeContract;               //有效合约
};


///交易所合约返回信息
struct APISTRUCT DFITCExchangeInstrumentRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCExchangeIDType                 exchangeID;                   //交易所编码
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCVarietyNameType                VarietyName;                  //品种名称
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCAmountType                     orderTopLimit;                //限价委托上限
    DFITCAmountType                     mktOrderTopLimit;             //市价委托上限
    DFITCPriceType                      contractMultiplier;           //合约乘数
    DFITCPriceType                      minPriceFluctuation;          //最小变动价位
    DFITCInstrumentMaturityType         instrumentMaturity;           //合约最后交易日
    DFITCPriceType                      upperLimitPrice;              //涨停板价
    DFITCPriceType                      lowerLimitPrice;              //跌停板价
    DFITCPriceType                      preClosePrice;                //昨收盘
    DFITCPriceType                      preSettlementPrice;           //昨结算价
    DFITCPriceType                      settlementPrice;              //结算价
    DFITCAmountType                     preOpenInterest;              //昨持仓量
    DFITCInstrumentPrefixType           instrumentPrefix;             //合约前缀
    DFITCInstrumenExpirationDateType    instrumentExpiration;         //合约到期日
    DFITCInstrumentIDType               underlying;                   //期权对应的标的合约代码
    DFITCOptionTypeType                 optionType;                   //期权类型
    DFITCPriceType                      strikePrice;                  //执行价格
    DFITCRiskDegreeType                 exchangeRiskDegree;           //交易所期权最低保障风险系数
    DFITCPriceType                      minMargin;                    //单位（手）期权合约最小保证金
    DFITCAmountType                     tradeSize;                    //期权开仓单位
};


///委托查询数据结构
struct APISTRUCT DFITCOrderField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
    DFITCOrderTypeType                  orderType;                    //报单类型
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCInstrumentIDType               instrumentID;                 //合约代码
};


///成交查询数据结构
struct APISTRUCT DFITCMatchField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCOrderTypeType                  orderType;                    //报单类型
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCInstrumentIDType               instrumentID;                 //合约代码
};


///委托查询响应数据结构
struct APISTRUCT DFITCOrderCommRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCBuySellTypeType                buySellType;                  //买卖
    DFITCOpenCloseTypeType              openClose;                    //开平标志
    DFITCPriceType                      insertPrice;                  //委托价
    DFITCAmountType                     orderAmount;                  //委托数量
    DFITCPriceType                      matchedPrice;                 //成交价格
    DFITCAmountType                     matchedAmount;                //成交数量
    DFITCAmountType                     cancelAmount;                 //撤单数量
    DFITCInsertType                     insertType;                   //自动单类别
    DFITCSpeculatorType                 speculator;                   //投保
    DFITCDateType                       commTime;                     //委托时间
    DFITCDateType                       submitTime;                   //申报时间
    DFITCClientIDType                   clientID;                     //交易编码
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCFrontAddrType                  operStation;                  //委托地址
    DFITCAccountIDType                  accountID;                    //客户号
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCSessionIDType                  sessionId;                    //会话ID
    DFITCReservedType                   reservedType2;                //预留字段2
    DFITCOrderSysIDType                 OrderSysID;                   //报单编号
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCPriceType                      margin;                       //保证金
    DFITCPriceType                      fee;                          //手续费
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCPriceType                      profitLossPrice;              //止损止盈价
    DFITCOrderTypeType                  orderType;                    //报单类别
    DFITCOrderPropertyType              orderProperty;                //订单属性
};


///成交查询数据响应
struct APISTRUCT DFITCMatchedRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCBuySellTypeType                buySellType;                  //买卖
    DFITCOpenCloseTypeType              openClose;                    //开平
    DFITCPriceType                      matchedPrice;                 //成交价格
    DFITCAmountType                     matchedAmount;                //成交数量
    DFITCPriceType                      matchedMort;                  //成交金额
    DFITCSpeculatorType                 speculator;                   //投保类别
    DFITCDateType                       matchedTime;                  //成交时间
    DFITCMatchIDType                    matchedID;                    //成交编号
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCClientIDType                   clientID;                     //交易编码
    DFITCMatchType                      matchType;                    //成交类型
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCSessionIDType                  sessionId;                    //会话ID
    DFITCReservedType                   reservedType2;                //预留字段2
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCPriceType                      fee;                          //手续费
    DFITCOrderTypeType                  orderType;                    //报单类型
    DFITCOrderSysIDType                 OrderSysID;                   //报单编号
};


///返回合约信息数据结构
struct APISTRUCT DFITCInstrumentRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求编号
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCRatioType                      longMarginRatio;              //多头保证金率
    DFITCRatioType                      shortMarginRatio;             //空头保证金率
    DFITCPriceType                      longMarginRatioByVolume;      //多头保证金费(定额)
    DFITCPriceType                      shortMarginRatioByVolume;     //空头保证金费(定额)
    DFITCRatioType                      openFeeVolRatio;              //开仓手续费 按手数计算
    DFITCRatioType                      closeFeeVolRatio;             //平仓手续费 按手数计算
    DFITCRatioType                      closeTodayFeeVolRatio;        //平今手续费 按手数计算
    DFITCRatioType                      openFeeAmtRatio;              //开仓手续费率 按金额计算
    DFITCRatioType                      closeFeeAmtRatio;             //平仓手续费率 按金额计算
    DFITCRatioType                      closeTodayFeeAmtRatio;        //平今手续费率 按金额计算
    DFITCAmountType                     orderTopLimit;                //限价委托上限
    DFITCPriceType                      contractMultiplier;           //合约乘数
    DFITCPriceType                      minimumPriceChange;           //最小变动价位
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCInstrumentMaturityType         instrumentMaturity;           //合约最后交易日
    DFITCComputeModeType                computeMode;                  //计算方式             
    DFITCPriceType                      atMoneyNorm;                  //平值按定额
    DFITCPriceType                      upperLimitPrice;              //涨停板价
    DFITCPriceType                      lowerLimitPrice;              //跌停板价
    DFITCPriceType                      preClosePrice;                //昨收盘
    DFITCPriceType                      preSettlementPrice;           //昨结算价
    DFITCPriceType                      settlementPrice;              //结算价
    DFITCAmountType                     preOpenInterest;              //昨持仓量
    DFITCRatioType                      optExecRatio;                 //期权：行权按比例 期货：交割按比例
    DFITCRatioType                      optExecRatioPerVol;           //期权：行权按定额 期货：交割按定额
};


///深度行情
struct APISTRUCT DFITCDepthMarketDataField
{
    DFITCDateType                       tradingDay;                   //交易日
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所代码
    DFITCInstrumentIDType               exchangeInstID;               //合约在交易所的代码
    DFITCPriceType                      lastPrice;                    //最新价
    DFITCPriceType                      preSettlementPrice;           //上次结算价
    DFITCPriceType                      preClosePrice;                //昨收盘
    DFITCAmountType                     preOpenInterest;              //昨持仓量
    DFITCPriceType                      openPrice;                    //今开盘
    DFITCPriceType                      highestPrice;                 //最高价
    DFITCPriceType                      lowestPrice;                  //最低价
    DFITCAmountType                     Volume;                       //成交数量
    DFITCPriceType                      turnover;                     //成交金额
    DFITCAmountType                     openInterest;                 //持仓量
    DFITCPriceType                      closePrice;                   //今收盘
    DFITCPriceType                      settlementPrice;              //本次结算价
    DFITCPriceType                      upperLimitPrice;              //涨停板价
    DFITCPriceType                      lowerLimitPrice;              //跌停板价
    DFITCDeltaType                      preDelta;                     //昨虚实度
    DFITCDeltaType                      currDelta;                    //今虚实度
    DFITCDateType                       UpdateTime;                   //最后修改时间
    DFITCMilliSecType                   UpdateMillisec;               //最后修改毫秒
    DFITCPriceType                      BidPrice1;                    //申买价一
    DFITCVolumeType                     BidVolume1;                   //申买量一
    DFITCPriceType                      AskPrice1;                    //申卖价一
    DFITCVolumeType                     AskVolume1;                   //申卖量一
    DFITCPriceType                      BidPrice2;                    //申买价二
    DFITCVolumeType                     BidVolume2;                   //申买量二
    DFITCPriceType                      AskPrice2;                    //申卖价二
    DFITCVolumeType                     AskVolume2;                   //申卖量二
    DFITCPriceType                      BidPrice3;                    //申买价三
    DFITCVolumeType                     BidVolume3;                   //申买量三
    DFITCPriceType                      AskPrice3;                    //申卖价三
    DFITCVolumeType                     AskVolume3;                   //申卖量三
    DFITCPriceType                      BidPrice4;                    //申买价四
    DFITCVolumeType                     BidVolume4;                   //申买量四
    DFITCPriceType                      AskPrice4;                    //申卖价四
    DFITCVolumeType                     AskVolume4;                   //申卖量四
    DFITCPriceType                      BidPrice5;                    //申买价五
    DFITCVolumeType                     BidVolume5;                   //申买量五
    DFITCPriceType                      AskPrice5;                    //申卖价五
    DFITCVolumeType                     AskVolume5;                   //申卖量五
    DFITCPriceType                      AveragePrice;                 //当日均价
    DFITCDateType                       XSpeedTime;                   //柜台系统时间
};

///********************************期权扩展行情************************************


struct APISTRUCT DFITCMarketDataFieldEx
{    
    DFITCFunctionIDType                FunctionID;                    //功能号   
    DFITCDateType                      tradingDay;                    //日期 2014-04-01   
    DFITCDateType                      UpdateTime;                    //时间 11:01:29
    DFITCMilliSecType                  UpdateMillisec;                //毫秒 000 
    DFITCInstrumentIDType              instrumentID;                  //期权合约编号
    DFITCExtMarketDataType             ExtMarketData;                 //扩展行情数据	
};
///********************************************************************************


//自定义组合行情
struct APISTRUCT DFITCCustomMarketDataField
{
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCVolumeType                     bidVolume1;                   //买一量
    DFITCPriceType                      bidPrice1;                    //买一价(挂价价差)
    DFITCVolumeType                     askVolume1;                   //卖一量
    DFITCPriceType                      askPrice1;                    //卖一价(对价价差)
    DFITCPriceType                      lastPrice;                    //最新价价差
};

///查询持仓明细
struct APISTRUCT DFITCPositionDetailField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCInstrumentTypeType             instrumentType;               //合约类型
};


///查询持仓明细响应
struct APISTRUCT DFITCPositionDetailRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金帐号ID
    DFITCExchangeIDType                 exchangeID;                   //交易所代码
    DFITCInstrumentIDType               instrumentID;                 //合约号
    DFITCBuySellTypeType                buySellType;                  //买卖
    DFITCPriceType                      openPrice;                    //开仓价
    DFITCAmountType                     volume;                       //手数
    DFITCMatchIDType                    matchID;                      //成交编号
    DFITCDateType                       matchedDate;                  //成交日期
    DFITCProfitLossType                 datePositionProfitLoss;       //盯市持仓盈亏
    DFITCProfitLossType                 dateCloseProfitLoss;          //盯市平仓盈亏
    DFITCProfitLossType                 floatProfitLoss;              //浮动盈亏
    DFITCProfitLossType                 dMargin;                      //占用保证金
    DFITCSpeculatorType                 speculator;                   //投保类别
    DFITCClientIDType                   clientID;                     //交易编码
    DFITCPriceType                      preSettlementPrice;           //昨结算价
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCAmountType                     closeOrderVol;                //平仓委托数量
    DFITCAmountType                     closeMatchVol;                //平仓成交数量
    DFITCPositionDateType               positionDateType;             //持仓日期类型
};


///用户事件通知信息
struct APISTRUCT DFITCTradingNoticeInfoField
{
    DFITCAccountIDType                  accountID;                    //资金帐号ID
    DFITCTimeType                       SendTime;                     //发送时间
    DFITCContentType                    FieldContent;                 //消息正文
    DFITCNoticeType                     noticeType;                   //消息类型
};


///合约交易状态通知信息
struct APISTRUCT DFITCInstrumentStatusField
{
    DFITCExchangeIDType                 ExchangeID;                   //交易所代码
    DFITCInstrumentIDType               InstrumentID;                 //合约代码
    DFITCInstrumentStatusType           InstrumentStatus;             //合约交易状态
    DFITCTradingSegmentSNType           TradingSegmentSN;             //交易阶段编号
    DFITCTimeType                       EnterTime;                    //进入本状态时间
    DFITCInstStatusEnterReasonType      EnterReason;                  //进入本状态原因
};


///用户密码修改
struct APISTRUCT DFITCResetPwdField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金帐号ID
    DFITCPasswdType                     oldpasswd;                    //旧密码
    DFITCPasswdType                     newpasswd;                    //新密码
};


///用户密码修改返回信息
struct APISTRUCT DFITCResetPwdRspField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCExecStateType                  execState;                    //状态标志
};


///账单确认
struct APISTRUCT DFITCBillConfirmField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金帐号ID
    DFITCDateType                       date;                         //确认日期  格式：yyyy.mm.dd
    DFITCConfirmMarkType                confirmFlag;                  //确认标志
};


///账单确认响应
struct APISTRUCT DFITCBillConfirmRspField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCExecStateType                  execState;                    //状态标志
};


///交易编码查询
struct APISTRUCT DFITCQryTradeCodeField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
};


///交易编码查询响应
struct APISTRUCT DFITCQryTradeCodeRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户
    DFITCExchangeIDType                 exchangeCode;                 //交易所编码
    DFITCClientIDType                   clientID;                     //交易编码 
    DFITCClientStatusType               clientStatus;                 //交易编码状态
    DFITCSpeculatorType                 clientIDType;                 //交易编码类型
}; 


///浮盈浮亏是否计算到权益中
struct APISTRUCT DFITCEquityComputModeRtnField
{
    DFITCCapControlModeType             capConMode;                   //资金控制方式,该方式需要用户按位判断,可能为多种组合
    DFITCPriceNoteType                  priceNote;                    //标的期货价格说明
};


///查询账单
struct APISTRUCT DFITCQryBillField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户
    DFITCDateType                       date;                         //查询日期   格式：yyyy.mm.dd
};


///查询账单响应
struct APISTRUCT DFITCQryBillRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户
    DFITCMsgInfoType                    message;                      //返回信息
};


///厂商ID确认请求
struct APISTRUCT DFITCProductField
{
    DFITCProductIDType                  productID;                    //产品编号
    DFITCSoftwareVendorIDType           vendorID;                     //软件供应商编号 
};


///厂商ID确认响应
struct APISTRUCT DFITCProductRtnField
{
    DFITCProductIDType                  productID;                    //产品编号
    DFITCSoftwareVendorIDType           vendorID;                     //软件供应商
    DFITCProductOnlineCountType         productOnlineCount;           //产品在线数量
    DFITCBrokerInfoType                 brokerInfoName;               //期货公司名称
    DFITCFrontIDType                    frontID;                      //前置机ID
};

///查询交易日请求
struct APISTRUCT DFITCTradingDayField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
};


///交易日请求响应
struct APISTRUCT DFITCTradingDayRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCDateType                       date;                         //交易日
};


///询价通知订阅请求
struct APISTRUCT DFITCQuoteSubscribeField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCExchangeIDType                 exchangeID;                   //交易所
};

///询价通知订阅响应
struct APISTRUCT DFITCQuoteSubscribeRspField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCExecStateType                  subscribeFlag;                //订阅状态
    DFITCExchangeIDType                 exchangeID;                   //交易所
};

///询价通知退订请求
struct APISTRUCT DFITCQuoteUnSubscribeField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCExchangeIDType                 exchangeID;                   //交易所
};

///询价通知退订响应
struct APISTRUCT DFITCQuoteUnSubscribeRspField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCExecStateType                  subscribeFlag;                //退订状态
    DFITCExchangeIDType                 exchangeID;                   //交易所
};

///询价通知订阅回报
struct APISTRUCT DFITCQuoteSubscribeRtnField
{
    DFITCQuoteIDType                    quoteID;                      //询价编号
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCSourceType                     source;                       //来源
    DFITCDateType                       quoteTime;                    //询价时间
};

///询价通知查询请求
struct APISTRUCT DFITCQryQuoteNoticeField
{
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCInstrumentIDType               instrumentID;                 //合约代码
};

///询价通知查询响应
struct APISTRUCT DFITCQryQuoteNoticeRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCQuoteIDType                    quoteID;                      //询价编号
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCSourceType                     source;                       //来源
    DFITCDateType                       quoteTime;                    //询价时间
};

///做市商报单请求
struct APISTRUCT DFITCQuoteInsertField
{
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCInsertType                     insertType;                   //自动单类别
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCQuoteIDType                    quoteID;                      //询价编号
    DFITCInstrumentTypeType             instrumentType;               //合约类型 
    DFITCAmountType                     bOrderAmount;                 //报单数量（买）
    DFITCAmountType                     sOrderAmount;                 //报单数量（卖）
    DFITCPriceType                      bInsertPrice;                 //委托价格（买）         
    DFITCPriceType                      sInsertPrice;                 //委托价格（卖）          
    DFITCOpenCloseTypeType              bOpenCloseType;               //开平标志（买）  
    DFITCOpenCloseTypeType              sOpenCloseType;               //开平标志（卖）
    DFITCSpeculatorType                 bSpeculator;                  //投资类别（买）       
    DFITCSpeculatorType                 sSpeculator;                  //投资类别（卖）          
    DFITCStayTimeType                   stayTime;                     //停留时间，仅支持郑州。其它情况可设置为0 
    DFITCCustomCategoryType             customCategory;               //自定义类别
};



///做市商报单响应
struct APISTRUCT DFITCQuoteRspField
{  
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号              
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号                
    DFITCRequestIDType                  lRequestID;                   //请求ID                    
    DFITCPriceType                      fee;                          //手续费(仅报价使用)            
    DFITCPriceType                      margin;                       //保证金(仅报价使用)
    DFITCDateType                       orderTime;                    //委托时间(仅报价使用)  
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
    DFITCCustomCategoryType             customCategory;               //自定义类别
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCQuoteIDType                    quoteID;                      //询价编号
    DFITCSessionIDType                  sessionID;                    //会话ID 
    DFITCClientIDType                   clientID;                     //交易编码
};


///做市商报单回报
struct APISTRUCT DFITCQuoteRtnField
{
    DFITCExchangeIDType                 exchangeID;                    //交易所                   
    DFITCClientIDType                   clientID;                      //交易编码  
    DFITCOrderSysIDType                 orderSysID;                    //报单编号
    DFITCInstrumentIDType               instrumentID;                  //合约代码                   
    DFITCLocalOrderIDType               localOrderID;                  //本地委托号                
    DFITCSeatCodeType                   seatCode;                      //席位代码                  
    DFITCOpenCloseTypeType              bOpenCloseType;                //开平标志（买）          
    DFITCOpenCloseTypeType              sOpenCloseType;                //开平标志（卖）             
    DFITCSpeculatorType                 speculator;                    //投资类别                       
    DFITCAmountType                     bOrderAmount;                  //委托数量（买）            
    DFITCAmountType                     sOrderAmount;                  //委托数量（卖）           
    DFITCPriceType                      bInsertPrice;                  //委托价  （买）               
    DFITCPriceType                      sInsertPrice;                  //委托价  （卖）               
    DFITCSPDOrderIDType                 spdOrderID;                    //柜台委托号                               
    DFITCAccountIDType                  accountID;                     //资金账号                     
    DFITCInstrumentTypeType             instrumentType;                //合约类型                  
    DFITCDateType                       suspendTime;                   //挂单时间                               
    DFITCEntrusTellerType               entrusTeller;                  //委托柜员  
    DFITCOrderAnswerStatusType          orderStatus;                   //委托状态 
    DFITCSessionIDType                  sessionID;                     //会话ID
    DFITCQuoteIDType                    quoteID;                       //询价编号
    DFITCErrorMsgInfoType               errorMsg;                      //错误信息
    DFITCCustomCategoryType             customCategory;                //自定义类别
};



///做市商撤单回报
struct APISTRUCT DFITCQuoteCanceledRtnField
{
    DFITCExchangeIDType                 exchangeID;                    //交易所                   
    DFITCClientIDType                   clientID;                      //交易编码  
    DFITCOrderSysIDType                 orderSysID;                    //报单编号
    DFITCInstrumentIDType               instrumentID;                  //合约代码                   
    DFITCLocalOrderIDType               localOrderID;                  //本地委托号                
    DFITCSeatCodeType                   seatCode;                      //席位代码                  
    DFITCOpenCloseTypeType              bOpenCloseType;                //开平标志（买）          
    DFITCOpenCloseTypeType              sOpenCloseType;                //开平标志（卖）             
    DFITCSpeculatorType                 speculator;                    //投资类别                       
    DFITCSPDOrderIDType                 spdOrderID;                    //柜台委托号                               
    DFITCAccountIDType                  accountID;                     //资金账号                     
    DFITCEntrusTellerType               entrusTeller;                  //委托柜员       
    DFITCOrderAnswerStatusType          orderStatus;                   //委托状态 
    DFITCAmountType                     cancelAmount;                  //撤单数量                              
    DFITCPriceType                      fee;                           //解冻手续费                  
    DFITCPriceType                      margin;                        //解冻保证金 
    DFITCSessionIDType                  sessionID;                     //会话ID
    DFITCBuySellTypeType                buySellType;                   //买卖标志
    DFITCQuoteIDType                    quoteID;                       //询价编号
    DFITCDateType                       canceledTime;                  //撤单时间
    DFITCCustomCategoryType             customCategory;                //自定义类别
};



///做市商成交回报
struct APISTRUCT DFITCQuoteMatchRtnField
{
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCClientIDType                   clientID;                     //交易编码
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCSeatCodeType                   seatCode;                     //席位代码
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCOpenCloseTypeType              openCloseType;                //开平标志
    DFITCSpeculatorType                 speculator;                   //投资类别  
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCOrderSysIDType                 OrderSysID;                   //报单编号(交易所报单编号)
    DFITCMatchIDType                    matchID;                      //成交编号
    DFITCAmountType                     matchedAmount;                //成交数量
    DFITCPriceType                      matchedPrice;                 //成交价格
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCPriceType                      turnover;                     //成交金额
    DFITCEntrusTellerType               entrusTeller;                 //委托柜员
    DFITCDateType                       matchedTime;                  //成交时间
    DFITCFeeType                        fee;                          //手续费
    DFITCPriceType                      insertPrice;                  //委托价格
    DFITCAmountType                     orderAmount;                  //委托数量
    DFITCOrderAnswerStatusType          orderStatus;                  //申报结果
    DFITCPriceType                      margin;                       //开仓为保证金,平仓为解冻保证金
    DFITCBuySellTypeType                buySellType;                  //买卖
    DFITCAmountType                     closeTodayAmount;             //平今数量
    DFITCPriceType                      closePrice;                   //平仓金额
    DFITCPriceType                      closeTodayPrice;              //平今金额
    DFITCAdjustmentInfoType             adjustmentInfo;               //组合或对锁的保证金调整信息,格式:[合约代码,买卖标志,投资类别,调整金额;] 
    DFITCPriceType                      frozenCapita;                 //成交解冻委托冻结的资金
    DFITCProfitLossType                 dateCloseProfitLoss;          //盯市平仓盈亏
    DFITCInstrumentTypeType             instrumentType;               //合约类型
    DFITCSessionIDType                  sessionID;                    //会话标识
    DFITCLargeMarginDirectType          largeMarginDirect;            //大边保证金方向
    DFITCQuoteIDType                    quoteID;                      //询价编号
    DFITCCustomCategoryType             customCategory;               //自定义类别
};


///批量撤单请求
struct APISTRUCT DFITCCancelAllOrderField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCExchangeIDType                 exchangeID;                   //交易所编码(目前只支持大商所)
};

///批量撤单响应
struct APISTRUCT DFITCCancelAllOrderRspField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
};

///询价请求
struct APISTRUCT DFITCForQuoteField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码
};

///询价请求响应
struct APISTRUCT DFITCForQuoteRspField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCDateType                       commTime;                     //委托时间
};

///询价回报
struct APISTRUCT DFITCForQuoteRtnField
{
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCSessionIDType                  sessionID;                    //会话ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
};

///做市商报价委托查询
struct APISTRUCT DFITCQuoteOrderField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCAccountIDType                  accountID;                    //资金账户
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
};

///做市商报价查询响应
struct APISTRUCT DFITCQuoteOrderRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCPriceType                      margin;                       //保证金
    DFITCPriceType                      fee;                          //手续费
    DFITCLocalOrderIDType               localOrderID;                 //本地委托号
    DFITCAccountIDType                  accountID;                    //客户号
    DFITCDateType                       commTime;                     //委托时间
    DFITCDateType                       submitTime;                   //申报时间
    DFITCExchangeIDType                 exchangeID;                   //交易所ID
    DFITCAmountType                     bOrderAmount;                 //委托数量（买）
    DFITCAmountType                     bMatchedAmount;               //成交数量（买）
    DFITCAmountType                     bCancelAmount;                //撤单数量（买）
    DFITCPriceType                      bInsertPrice;                 //委托价格（买）
    DFITCPriceType                      bMatchedPrice;                //成交价格（买）
    DFITCOpenCloseTypeType              bOpenCloseType;               //开平标志（买）
    DFITCAmountType                     sOrderAmount;                 //委托数量（卖）
    DFITCAmountType                     sMatchedAmount;               //成交数量（卖）
    DFITCAmountType                     sCancelAmount;                //撤单数量（卖）
    DFITCPriceType                      sInsertPrice;                 //委托价格（卖）
    DFITCPriceType                      sMatchedPrice;                //成交价格（卖）
    DFITCOpenCloseTypeType              sOpenCloseType;               //开平标志（卖）
    DFITCFrontAddrType                  operStation;                  //操作站点
    DFITCSessionIDType                  sessionID;                    //会话ID
    DFITCQuoteIDType                    quoteID;                      //询价编号
    DFITCCustomCategoryType             customCategory;               //自定义类别
};

///查询转账银行
struct APISTRUCT DFITCQryTransferBankField
{
    DFITCAccountIDType                  accountID;                     //资金账号
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCRequestIDType                  lRequestID;                    //请求ID
};

///转帐银行响应
struct APISTRUCT DFITCTransferBankRspField
{
    DFITCAccountIDType                  accountID;                     //客户号
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCBankAccountType                bankAccount;                   //银行账号
    DFITCCurrencyType                   currency;                      //币种
    DFITCDateType                       registDate;                    //登记日期
    DFITCRequestIDType                  lRequestID;                    //请求ID
};

///查询转账流水
struct APISTRUCT DFITCQryTransferSerialField
{
    DFITCAccountIDType                  accountID;                     //资金账号
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCBankAccountType                bankAccount;                   //银行账号
    DFITCRequestIDType                  lRequestID;                    //请求ID
};

///转账流水响应
struct APISTRUCT DFITCTransferSerialRspField
{
    DFITCAccountIDType                  accountID;                     //资金账号
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCBankAccountType                bankAccount;                   //银行账号
    DFITCCurrencyType                   currency;                      //币种代码
    DFITCApplyNumberType                applyNum;                      //申请号
    DFITCTransferType                   type;                          //转账业务类别
    DFITCPriceType                      tradeAmount;                   //转账金额
    DFITCPriceType                      curFutAccountFund;             //本次资金余额
    DFITCSerialType                     bankSerialNum;                 //银行流水号
    DFITCTimeType                       reqTransferTime;               //发起转账时间
    DFITCTimeType                       dealTransferTime;              //转账成功时间
    DFITCProcResultType                 procResult;                    //转账处理结果
    DFITCRequestIDType                  lRequestID;                    //请求ID
};

///资金转账请求信息
struct APISTRUCT DFITCReqTransferField
{
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCBankAccountType                bankAccount;                   //银行账号
    DFITCPasswdType                     bankPassword;                  //银行密码
    DFITCAccountIDType                  accountID;                     //投资者账号
    DFITCPasswdType                     password;                      //期货密码
    DFITCCurrencyType                   currency;                      //币种代码
    DFITCPriceType                      tradeAmount;                   //转账金额
    DFITCRequestIDType                  lRequestID;                    //请求ID
};

///资金转账响应信息
struct APISTRUCT DFITCTransferRspField
{
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCBankAccountType                bankAccount;                   //银行账号
    DFITCAccountIDType                  accountID;                     //投资者账号
    DFITCPriceType                      tradeAmount;                   //转账金额
    DFITCApplyNumberType                applyNumber;                   //转账申请号
    DFITCRequestIDType                  lRequestID;                    //请求ID
};

///资金转账通知信息
struct APISTRUCT DFITCTransferRtnField
{
    DFITCAccountIDType                  accountID;                     //投资者账号
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCBankAccountType                bankAccount;                   //银行账号
    DFITCTransferType                   type;                          //转账类别
    DFITCPriceType                      tradeAmount;                   //转账金额
    DFITCSerialType                     bankSerialNum;                 //银行流水号
    DFITCApplyNumberType                applyNumber;                   //转账申请号
    DFITCSessionIDType                  sessionID;                     //会话ID
};

///银行或主席发起出金冲正通知
struct APISTRUCT DFITCRepealRtnField
{
    DFITCAccountIDType                  accountID;                     //投资者账号
    DFITCBankIDType                     bankID;                        //银行代码
    DFITCBankAccountType                bankAccount;                   //银行账号
    DFITCTransferType                   type;                          //转账类别
    DFITCPriceType                      tradeAmount;                   //转账金额
    DFITCSerialType                     bankSerialNum;                 //银行流水号
    DFITCSerialType                     repealSerial;                  //被冲正流水号
};

///交易状态查询请求
struct APISTRUCT DFITCQryExchangeStatusField
{
    DFITCRequestIDType                  lRequestID;                    //请求ID
    DFITCExchangeIDType                 exchangeID;                    //交易所编码
};

///交易所状态查询响应
struct APISTRUCT DFITCExchangeStatusRspField
{
    DFITCRequestIDType                  lRequestID;                    //请求ID
    DFITCExchangeStatusType             exchangeStatus;                //交易所状态
    DFITCExchangeIDType                 exchangeID;                    //交易所编码
};

///交易所状态通知
struct APISTRUCT DFITCExchangeStatusRtnField
{
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeStatusType             exchangeStatus;               //交易所状态
};

///行情查询请求
struct DFITCQryDepthMarketDataField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所
};

///查询询价请求
struct APISTRUCT DFITCQryForQuoteField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账户ID
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所
};

///查询询价响应
struct APISTRUCT DFITCQryForQuoteRtnField
{
    DFITCRequestIDType                  lRequestID;                   //请求ID
    DFITCAccountIDType                  accountID;                    //资金账号
    DFITCSPDOrderIDType                 spdOrderID;                   //柜台委托号
    DFITCInstrumentIDType               instrumentID;                 //合约代码
    DFITCExchangeIDType                 exchangeID;                   //交易所
    DFITCDateType                       SuspendTime;                  //挂起时间
    DFITCOrderAnswerStatusType          orderStatus;                  //委托状态
};

#endif//DFITCAPISTRUCT_H_
