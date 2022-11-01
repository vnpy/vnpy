/**
 * 版权所有(C)2012-2016, 大连飞创信息技术有限公司
 * 文件名称：DFITCSECApiStruct.h
 * 文件说明：定义接口所需的数据接口
 * 当前版本：1.6
 * 作者：XSpeed证券项目组
 * 发布日期：2019年11月
 */
#ifndef DFITCSECAPISTRUCT_H_
#define DFITCSECAPISTRUCT_H_


#include "DFITCSECApiDataType.h"

#ifdef WIN32
    #ifdef DFITCSECAPI_EXPORTS
        #define APISTRUCT __declspec(dllexport)
    #else
        #define APISTRUCT __declspec(dllimport)
    #endif//DFITCAPI_EXPORTS
#else
#define APISTRUCT
#endif//WIN32

//重传方式
enum RESUME_TYPE
{
    TERT_QUICK = 0,
    TERT_RESUME,
    TERT_RESTART
};

//ERR-错误信息
struct APISTRUCT DFITCSECRspInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECSessionIDType                sessionID;                //会话标识
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECErrorIDType                  errorID;                  //错误ID
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECMessageType                  errorMsg;                 //错误信息
};

//ERR-消息通知
struct APISTRUCT DFITCSECRspNoticeField
{
    DFITCSECMessageType                  noticeMsg;                 //通知
};

//SEC-登录请求
struct APISTRUCT DFITCSECReqUserLoginField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECPasswordType                 password;                 //密码(Y)
    DFITCSECMDCompressFalgType           compressflag;             //行情压缩标志(N)(只有登录行情账户的时候该字段有效)
    DFITCSECAuthenticCodeType            authenticCode;            //认证码
    DFITCSECAppID                        appID;
    DFITCSECCollectInterfaceType         collectInterType;         //看穿式监管采集接口类型
};

//SEC-登录响应
struct APISTRUCT DFITCSECRspUserLoginField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSessionIDType                sessionID;                //会话编号
    DFITCSECFrontIDType                  frontID;                  //前置编号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECTimeType                     loginTime;                //登录时间
    DFITCSECDateType                     tradingDay;               //交易日
    DFITCSECErrorIDType                  result;                   //结果
    DFITCSECMessageType                  rtnMsg;                   //返回信息
};

//SEC-登出请求
struct APISTRUCT DFITCSECReqUserLogoutField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//SEC-登出响应 
struct APISTRUCT DFITCSECRspUserLogoutField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECErrorIDType                  result;                   //结果
    DFITCSECMessageType                  rtnMsg;                   //返回信息
};

//SEC-更新用户密码请求
struct APISTRUCT DFITCSECReqPasswordUpdateField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECPasswordType                 oldPassword;              //旧密码(Y)
    DFITCSECPasswordType                 newPassword;              //新密码(Y)
    DFITCSECPasswordTypeType             passwordType;             //密码类型(Y)
};

//SEC-更新用户密码响应
struct APISTRUCT DFITCSECRspPasswordUpdateField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECPasswordTypeType             passwordType;             //密码类型
    DFITCSECErrorIDType                  result;                   //更新结果
    DFITCSECMessageType                  rtnMsg;                   //更新返回信息
};

//SEC-更新行情账户密码请求
struct APISTRUCT DFITCSECReqMDPasswordUpdateField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECPasswordType                 oldPassword;              //旧密码(Y)
    DFITCSECPasswordType                 newPassword;              //新密码(Y)
};

//SEC-更新行情账户密码响应
struct APISTRUCT DFITCSECRspMDPasswordUpdateField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECErrorIDType                  result;                   //更新结果
    DFITCSECMessageType                  rtnMsg;                   //更新返回信息
};

//SEC-撤单请求
struct APISTRUCT DFITCSECReqWithdrawOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号(N)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(N)(柜台委托号和本地委托号二选一)
    DFITCSECSessionIDType                sessionID;                //会话编号(N)
};

//SEC-撤单响应
struct APISTRUCT DFITCSECRspWithdrawOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECTimeType                     entrustTime;              //委托时间(股票没有这个字段，期权有)
    DFITCSECMessageType                  cancelMsg;                //撤单返回信息
};

//STOCK-委托请求
struct APISTRUCT DFITCStockReqEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECPriceType                    entrustPrice;             //委托价格(N)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(Y)
    DFITCSECQuantityType                 entrustQty;               //委托数量(Y)
    DFITCSECSecurityIDType               securityID;               //证券代码(Y)
    DFITCSECOrderTypeType                orderType;                //订单类型(Y)
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)
    DFITCSECSeatIDType                   eachSeatID;               //对方席位号(N)
    DFITCSECHKEntrustLimitType           hkEntrustLimit;           //港股交易限制(港股交易：Y)
    DFITCSECHKOrderTypeType              hkOrderType;              //港股订单属性(港股交易：Y)
};

//STOCK-委托响应
struct APISTRUCT DFITCStockRspEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)
    DFITCSECMessageType                  entrustMsg;               //委托返回信息
};

//STOCK-委托查询请求
struct APISTRUCT DFITCStockReqQryEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSpdOrderIDType               spdOrderID;               //委托号(N)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(N)
    DFITCSECSecurityIDType               securityID;               //证券代码(N)
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)
    DFITCSECEntrustQryFlagType           entrustQryFlag;           //查询标志(N)
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志(N)
    DFITCSECIncQryIndexType              incQryIndex;              //增量查询索引值(N)(不能超过int最大值)
};

//STOCK-委托查询响应
struct APISTRUCT DFITCStockRspQryEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECShareholderIDType            offerShareholderID;       //报盘股东号
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECPriceType                    tradePrice;               //成交价格
    DFITCSECTimeType                     tradeTime;                //成交时间
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECFundsType                    clearFunds;               //清算资金
    DFITCSECEntrustTypeType              entrustType;              //委托方式
    DFITCSECSpdOrderIDType               spdOrderID;               //委托号
    DFITCSECPriceType                    entrustPrice;             //委托价格
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECTimeType                     declareTime;              //申报时间
    DFITCSECDeclareResultType            declareResult;            //申报结果
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECFundsType                    freezeFunds;              //冻结资金
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECMessageType                  noteMsg;                  //结果说明
    DFITCSECQuantityType                 withdrawQty;              //撤单数量
    DFITCSECDeclareOrderIDType           declareOrderID;           //申报委托号
    DFITCSECOrderTypeType                orderType;                //订单类型
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号
    DFITCSECSerialIDType                 freezeFundsSerialID;      //资金冻结流水号
    DFITCSECSerialIDType                 freezeStockSerialID;      //证券冻结流水号
    DFITCSECDateType                     declareDate;              //申报日期
    DFITCSECSerialIDType                 declareSerialID;          //申报记录号
    DFITCSECDateType                     entrustDate;              //委托日期
    DFITCSECIncQryIndexType              incQryIndex;              //增量查询索引值
    DFITCSECIPAddressType                ipAddr;                   //IP地址
    DFITCSECMacAddressType               macAddr;                  //MAC地址
};

//STOCK-实时成交查询请求
struct APISTRUCT DFITCStockReqQryRealTimeTradeField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSecurityIDType               securityID;               //证券代码(N)
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(N)
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号(N)
    DFITCSECTradeQryFlagType             queryFlag;                //查询标志(N)
};

//STOCK-实时成交查询响应
struct APISTRUCT DFITCStockRspQryRealTimeTradeField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECDeclareOrderIDType           declareOrderID;           //申报委托号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECPriceType                    entrustPrice;             //委托价格
    DFITCSECQuantityType                 withdrawQty;              //撤单数量
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECPriceType                    tradePrice;               //成交价格
    DFITCSECTimeType                     tradeTime;                //成交时间
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsType                    clearFunds;               //清算资金
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号
    DFITCSECOrderTypeType                orderType;                //订单类型
};

//STOCK-分笔成交查询请求
struct APISTRUCT DFITCStockReqQrySerialTradeField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号(N)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(N)
    DFITCSECSecurityIDType               securityID;               //证券代码(N)
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)
    DFITCSECTradeQryFlagType             tradeQryFlag;             //查询标志(N)
    DFITCSECIncQryIndexType              incQryIndex;              //增量查询索引值(N)
};

//STOCK-分笔成交查询响应
struct APISTRUCT DFITCStockRspQrySerialTradeField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECTradeIDType                  tradeID;                  //成交编号
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECPriceType                    tradePrice;               //成交价格
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECFundsType                    clearFunds;               //清算资金
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityTypeType             securityType;             //证劵类别
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECFundsType                    commission;               //佣金
    DFITCSECSerialIDType                 rtnSerialID;              //回报序号
    DFITCSECFundsType                    interestQuote;            //利息报价
    DFITCSECDeclareOrderIDType           declareOrderID;           //申报委托号
    DFITCSECIncQryIndexType              incQryIndex;              //增量查询索引值
    DFITCSECFundsType                    interest;                 //利息
    DFITCSECTimeType                     tradeTime;                //成交时间
};

//STOCK-持仓查询请求
struct APISTRUCT DFITCStockReqQryPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSecurityIDType               securityID;               //证劵代码(N)
    DFITCSECPositionQryFlagType          posiQryFlag;              //查询标志(N)
};

//STOCK-持仓查询响应
struct APISTRUCT DFITCStockRspQryPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsType                    sellTurnover;             //当日卖出成交金额
    DFITCSECQuantityType                 sellTradeQty;             //当日卖出成交数量
    DFITCSECQuantityType                 sellEntrustQty;           //当日卖出委托数量
    DFITCSECFundsType                    buyTurnover;              //当日买入成交金额
    DFITCSECQuantityType                 buyTradeQty;              //当日买入成交数量
    DFITCSECQuantityType                 buyEntrustQty;            //当日买入委托数量
    DFITCSECQuantityType                 nonCirculateQty;          //非流通数量
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所
    DFITCSECDateType                     openDate;                 //开仓日期
    DFITCSECQuantityType                 ableSellQty;              //可卖出数量
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECQuantityType                 securityQty;              //证券数量
    DFITCSECQuantityType                 position;                 //今持仓量
    DFITCSECQuantityType                 unSettleQty;              //未交收数量
    DFITCSECDateType                     changeDate;               //变动日期
    DFITCSECQuantityType                 ablePurchaseQty;          //可申购数量
    DFITCSECQuantityType                 ableRedemptionQty;        //可赎回数量
    DFITCSECQuantityType                 freezeQty;                //冻结数量
    DFITCSECQuantityType                 offsetSQty;               //卖出抵消数量
    DFITCSECQuantityType                 offsetBQty;               //买入抵消数量
    DFITCSECQuantityType                 purchaseTradeQty;         //申购成交数量
    DFITCSECQuantityType                 redemptionTradeQty;       //赎回成交数量
    DFITCSECTradeUnitType                tradeUnit;                //交易单位(N)
    DFITCSECQuantityType                 totalSellQty;             //累计卖出数量(N)
    DFITCSECQuantityType                 totalBuyQty;              //累计买入数量(N)
    DFITCSECQuantityType                 rationedSharesQty;        //配股数量(N)
    DFITCSECQuantityType                 purchaseQty;              //送股数量(N)
    DFITCSECFundsType                    dilutedFloatProfitLoss;   //摊薄浮动盈亏(N)
    DFITCSECPriceType                    dilutedBreakevenPrice;    //摊薄保本价(N)
    DFITCSECPriceType                    dilutedCost;              //摊薄成本价(N)
    DFITCSECPriceType                    avgPositionPrice;         //持仓均价(N)
    DFITCSECFundsType                    floatProfitLoss;          //浮动盈亏(N)
    DFITCSECFundsType                    dividend;                 //红利金额(N)
    DFITCSECFundsType                    totalFloatProfitLoss;     //累计浮动盈亏(N)
    DFITCSECFundsType                    sellAmount;               //卖出金额(N)
    DFITCSECFundsType                    buyAmount;                //买入金额(N)
    DFITCSECPriceType                    buyAvgPrice;              //买入均价(N)
    DFITCSECFundsType                    rationedSharesAmount;     //配股金额(N)
    DFITCSECFundsType                    latestMarket;             //最新市值(N)
    DFITCSECPriceType                    breakevenPrice;           //保本价(N)
    DFITCSECPriceType                    latestPrice;              //最新价(N)
    DFITCSECFundsType                    nonCirculateMarket;       //非流通市值(N)
    DFITCSECFundsType                    interestQuote;            //利息报价(N)
    DFITCSECPriceType                    preClosePrice;            //昨收盘价(N)(预留)
};

//STOCK-客户资金查询请求
struct APISTRUCT DFITCStockReqQryCapitalAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECFundsQryFlagType             FundsQryFlag;             //查询标志(N)
};

//STOCK-客户资金查询响应
struct APISTRUCT DFITCStockRspQryCapitalAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsType                    availableFunds;           //可用资金
    DFITCSECFundsType                    t2AvailableFunds;         //T+2可用资金
    DFITCSECFundsType                    anticipatedInterest;      //预计利息
    DFITCSECFundsType                    accountBalance;           //账户余额
    DFITCSECAccountStatusType            accountStatus;            //帐户状态
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECFundsType                    freezeFunds;              //冻结资金
    DFITCSECFundsType                    t2FreezeFunds;            //T+2冻结资金
    DFITCSECBranchIDType                 branchID;                 //机构代码
    DFITCSECFundsType                    totalFunds;               //总资金(查询标志为1时会返回值
    DFITCSECFundsType                    totalMarket;              //总市值(查询标志为1时会返回值)
};

//STOCK-客户信息查询请求
struct APISTRUCT  DFITCStockReqQryAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//STOCK-客户信息查询响应
struct APISTRUCT  DFITCStockRspQryAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECPhoneIDType                  tel;                      //电话
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECAccountNameType              accountName;              //客户姓名
    DFITCSECAccountIdentityIDType        accountIdentityID;        //证件编号
    DFITCSECAccountIdentityTypeType      accountIdentityType;      //证件类型
    DFITCSECBranchIDType                 branchID;                 //机构编码
    DFITCSBranchTypeType                 branchType;               //机构标志
    DFITCSECPhoneIDType                  mobile;                   //移动电话
    DFITCSECEntrustTypeType              entrustType;              //委托方式
    DFITCSECAccountStatusType            accountStatus;            //客户状态
    DFITCSECPasswdSyncFlagType           pwdSynFlag;               //密码同步标志
};

//STOCK-股东信息查询请求
struct APISTRUCT  DFITCStockReqQryShareholderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
};

//STOCK-股东信息查询响应
struct APISTRUCT  DFITCStockRspQryShareholderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                account;                  //客户号
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECShareholderSpecPropType      shareholderSpecProp;      //股东指定属性
    DFITCSECTradePermissionsType         tradePermissions;         //交易权限
    DFITCSECExchangeIDType               exchangeID;               //交易所
    DFITCSECShareholderStatusType        shareholderStatus;        //股东状态
    DFITCSECMainAccountFlagType          mainAccountFlag;          //主账户标志
    DFITCSECShareholderCtlPropType       shareholderCtlProp;       //股东控制属性
    DFITCSECBranchIDType                 branchID;                 //机构编码
    DFITCSECShareholderTypeType          shareholderType;          //股东类别
};

//STOCK-资金调转请求
struct APISTRUCT  DFITCStockReqTransferFundsField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECCurrencyType                 currency;                 //币种(Y)
    DFITCSECMessageType                  summaryMsg;               //摘要(N)
    DFITCSECFundsType                    operateFunds;             //发生金额(Y)
    DFITCSECFundsTransferFlagType        fundsTransFlag;           //资金调转标志(Y)
};

//STOCK-资金调转响应
struct APISTRUCT  DFITCStockRspTransferFundsField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSerialIDType                 serialID;                 //流水号
    DFITCSECFundsType                    accountBanlance;          //账户余额
    DFITCSECFundsType                    availableFunds;           //可用资金
    DFITCSECFundsType                    t2AvailableFunds;         //T+2可用资金
    DFITCSECFundsTransferFlagType        fundsTransFlag;           //资金调转标志
};

//STOCK-批量委托请求
struct APISTRUCT DFITCStockReqEntrustBatchOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECQuantityType                 entrustCount;             //委托数量(Y)
    DFITCSECEntrustBatchOrderDetailType  entrustDetail;            //委托详细信息(Y)
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)
};

//STOCK-批量委托响应
struct APISTRUCT DFITCStockRspEntrustBatchOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECOrderRangeID                 orderRangeID;             //委托号范围
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号
    DFITCSECQuantityType                 sucEntrustCount;          //成功委托笔数
};

//STOCK-批量撤单请求
struct APISTRUCT DFITCStockReqWithdrawBatchOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECOrderIDRangeType             orderRangeID;             //委托号范围(Y)
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)
};

//STOCK-批量撤单响应
struct APISTRUCT DFITCStockRspWithdrawBatchOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECBatchDeclareResultType       result;                   //撤单结果
};

//STOCK-计算可委托数量请求
struct APISTRUCT DFITCStockReqCalcAbleEntrustQtyField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECPriceType                    entrustPrice;             //委托价格(N)(限价订单必须送入数值)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(N)
    DFITCSECSecurityIDType               securityID;               //证券代码(Y)
    DFITCSECOrderTypeType                orderType;                //订单类型(Y)
};

//STOCK-计算可委托数量响应
struct APISTRUCT DFITCStockRspCalcAbleEntrustQtyField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECQuantityType                 ableEntrustQty;           //可委托数量
};

//STOCK-计算可买入ETF股票篮数请求
struct APISTRUCT DFITCStockReqCalcAblePurchaseETFQtyField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSecurityIDType               securityID;               //证券代码(Y)
};

//STOCK-计算可买入ETF股票篮数响应
struct APISTRUCT DFITCStockRspCalcAblePurchaseETFQtyField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECQuantityType                 ablePurchaseETFQty;       //可委托数量
};

//STOCK-资金冻结明细查询请求
struct APISTRUCT DFITCStockReqQryFreezeFundsDetailField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECCurrencyType                 currency;                 //币种(N)
    DFITCSECFundsFreezeTypeType          fundsFreezeType;          //冻结类别(N)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSerialIDType                 serialID;                 //流水号(N)
};

//STOCK-资金冻结明细查询响应
struct APISTRUCT DFITCStockRspQryFreezeFundsDetailField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsFreezeTypeType          fundsFreezeType;          //冻结类别
    DFITCSECAccountNameType              accountName;              //客户姓名
    DFITCSECMessageType                  summaryMsg;               //摘要
    DFITCSECSerialIDType                 serialID;                 //流水号
    DFITCSECFundsType                    operatorFunds;            //发生金额
    DFITCSECTimeType                     operatorTime;             //发生时间
    DFITCSECBranchIDType                 branchID;                 //机构代码
    DFITCSECDateType                     operatorDate;             //发生日期
};

//STOCK-证券冻结明细查询请求
struct APISTRUCT DFITCStockReqQryFreezeStockDetailField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECStockFreezeTypeType          stockFreezeType;          //冻结类别(N)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSecurityIDType               securityID;               //证券代码(N)
    DFITCSECSerialIDType                 serialID;                 //流水号(N)
};

//STOCK-证券冻结明细查询响应
struct APISTRUCT DFITCStockRspQryFreezeStockDetailField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECStockFreezeTypeType          stockFreezeType;          //冻结类别
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECAccountNameType              accountName;              //客户姓名
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECMessageType                  summaryMsg;               //摘要
    DFITCSECSerialIDType                 serialID;                 //流水号
    DFITCSECTimeType                     operatorTime;             //发生时间
    DFITCSECBranchIDType                 branchID;                 //营业部
    DFITCSECDateType                     operatorDate;             //发生日期
    DFITCSECQuantityType                 operatorQty;              //发生数量
};

//STOCK-查询资金调拨明细请求
struct APISTRUCT DFITCStockReqQryTransferFundsDetailField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECCurrencyType                 currency;                 //币种(N)
    DFITCSECTransFundsFreezeTypeType     fundsFreezeType;          //冻结类别(N)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSerialIDType                 serialID;                 //流水号(N)
};

//STOCK-资金调拨明细查询响应
struct APISTRUCT DFITCStockRspQryTransferFundsDetailField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECTransFundsFreezeTypeType     fundsFreezeType;          //冻结类别
    DFITCSECAccountNameType              accountName;              //客户姓名
    DFITCSECMessageType                  summaryMsg;               //摘要
    DFITCSECSerialIDType                 serialID;                 //流水号
    DFITCSECFundsType                    operatorFunds;            //发生金额
    DFITCSECTimeType                     operatorTime;             //发生时间
    DFITCSECBranchIDType                 branchID;                 //机构代码
    DFITCSECDateType                     operatorDate;             //发生日期
};

//STOCK-查询客户证券调拨明细请求
struct APISTRUCT DFITCStockReqQryTransferStockDetailField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;                //交易所编码(N)
    DFITCSECStockFreezeTypeType          stockFreezeType;           //冻结类别(N)
    DFITCSECIncQryIndexType              incQryIndex;               //增量查询索引值(N)
    DFITCSECSerialIDType                 serialID;                  //流水号(N)
};

//STOCK-查询客户证券调拨明细响应
struct APISTRUCT DFITCStockRspQryTransferStockDetailField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECAccountNameType              accountName;               //客户名称
    DFITCSECBranchIDType                 branchID;                  //机构代码
    DFITCSECDateType                     operatorDate;              //发生日期
    DFITCSECExchangeIDType               exchangeID;                //交易所编码
    DFITCSECStockFreezeTypeType          stockFreezeType;           //冻结类别
    DFITCSECSecurityIDType               securityID;                //证劵代码
    DFITCSECSerialIDType                 serialID;                  //流水号
    DFITCSECShareholderIDType            shareholderID;             //股东号
    DFITCSECMessageType                  summaryMsg;                //摘要
    DFITCSECTimeType                     operatorTime;              //发生时间
    DFITCSECQuantityType                 operatorQty;               //发生数量
};

//STOCK-证券信息查询请求
struct APISTRUCT DFITCStockReqQryStockField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSecurityIDType               securityID;               //证劵代码(Y)
};

//STOCK-证券信息查询响应
struct APISTRUCT DFITCStockRspQryStockField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECStockTradeFlagType           stopFlag;                 //停牌标志
    DFITCSECPriceType                    latestPrice;              //最新价
    DFITCSECPriceType                    preClosePrice;            //昨收盘价
    DFITCSECPriceType                    openPrice;                //开盘价
    DFITCSECLargeQuantityType            tradeQty;                 //成交数量
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECPriceType                    priceHigher;              //最高价
    DFITCSECPriceType                    priceLower;               //最低价
    DFITCSECPriceType                    bidPrice1;                //申买价一
    DFITCSECQuantityType                 bidQty1;                  //申买量一
    DFITCSECPriceType                    askPrice1;                //申卖价一
    DFITCSECQuantityType                 askQty1;                  //申卖量一
    DFITCSECPriceType                    bidPrice2;                //申买价二
    DFITCSECQuantityType                 bidQty2;                  //申买量二
    DFITCSECPriceType                    askPrice2;                //申卖价二
    DFITCSECQuantityType                 askQty2;                  //申卖量二
    DFITCSECPriceType                    bidPrice3;                //申买价三
    DFITCSECQuantityType                 bidQty3;                  //申买量三
    DFITCSECPriceType                    askPrice3;                //申卖价三
    DFITCSECQuantityType                 askQty3;                  //申卖量三
    DFITCSECPriceType                    bidPrice4;                //申买价四
    DFITCSECQuantityType                 bidQty4;                  //申买量四
    DFITCSECPriceType                    askPrice4;                //申卖价四
    DFITCSECQuantityType                 askQty4;                  //申卖量四
    DFITCSECPriceType                    bidPrice5;                //申买价五
    DFITCSECQuantityType                 bidQty5;                  //申买量五
    DFITCSECPriceType                    askPrice5;                //申卖价五
    DFITCSECQuantityType                 askQty5;                  //申卖量五
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECPriceType                    interestQuote;            //利息报价
    DFITCSECPriceType                    securityFaceValue;        //证券面值
    DFITCSECBidTradeFlagType             bidTradeFlag;             //竞价交易标志
    DFITCSECTradeUnitType                tradeUnit;                //交易单位
    DFITCSECBusinessLimitType            businessLimit;            //买卖限制
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECPriceType                    upperLimitPrice;          //涨停板价
    DFITCSECPriceType                    lowerLimitPrice;          //跌停板价
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECOrderTypeLimitType           orderLimits;              //订单类型限制
};

//STOCK-查询交易时间请求
struct APISTRUCT DFITCStockReqQryTradeTimeField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//STOCK-查询交易时间响应
struct APISTRUCT DFITCStockRspQryTradeTimeField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECDateType                     sysTradingDay;            //系统当前日期
    DFITCSECTimeType                     sysTime;                  //系统当前时间
};

//STOCK-委托回报
struct APISTRUCT DFITCStockEntrustOrderRtnField
{
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSessionIDType                sessionID;                //会话编号
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECQuantityType                 withdrawQty;              //撤单数量
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECFundsType                    freezeFunds;              //冻结资金
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECDeclareResultType            declareResult;            //申报结果
    DFITCSECMessageType                  noteMsg;                  //结果说明
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECOrderConfirmFlagType         orderConfirmFlag;         //委托确认标志
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECPriceType                    entrustPrice;             //委托价格
    DFITCSECOrderTypeType                orderType;                //订单类型
};

//STOCK-成交回报
struct APISTRUCT DFITCStockTradeRtnField
{
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSessionIDType                sessionID;                //会话编号
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECTradeIDType                  tradeID;                  //成交编号
    DFITCSECTimeType                     tradeTime;                //成交时间
    DFITCSECQuantityType                 withdrawQty;              //撤单数量
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECFundsType                    clearFunds;               //清算资金
    DFITCSECQuantityType                 totalTradeQty;            //委托总成交数量
    DFITCSECFundsType                    totalTurnover;            //委托总成交金额
    DFITCSECQuantityType                 tradeQty;                 //本次成交数量
    DFITCSECPriceType                    tradePrice;               //本次成交价格
    DFITCSECFundsType                    turnover;                 //本次成交金额
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECDeclareResultType            declareResult;            //申报结果(预留字段)
    DFITCSECMessageType                  noteMsg;                  //结果说明(预留字段)
};

//STOCK-撤单回报
struct APISTRUCT DFITCStockWithdrawOrderRtnField
{
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSessionIDType                sessionID;                //会话编号
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECQuantityType                 withdrawQty;              //撤单数量
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECFundsType                    freezeFunds;              //冻结资金
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECDeclareResultType            declareResult;            //申报结果(预留字段)
    DFITCSECMessageType                  noteMsg;                  //结果说明(预留字段)
};

//SOP-委托请求
struct APISTRUCT DFITCSOPReqEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSecurityIDType               securityID;               //证劵代码(Y)
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码(N)(预留字段)
    DFITCSECQuantityType                 entrustQty;               //委托数量(Y)
    DFITCSECPriceType                    entrustPrice;             //委托价格(N)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(Y)
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志(Y)
    DFITCSECCoveredFlagType              coveredFlag;              //备兑类型(Y)
    DFITCSECOrderTypeType                orderType;                //订单类型(Y)
    DFITCSECOrderExpiryDateType          orderExpiryDate;          //订单时效限制(N)
    DFITCSECOrderCategoryType            orderCategory;            //委托单类别(Y)
    DFITCSECSerialIDType                 serialID;                 //扩展流水号(N)(预留字段)
    DFITCSECTDevIDType                   devID;                    //厂商ID(N)
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)
};

//SOP-委托响应
struct APISTRUCT DFITCSOPRspEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECFundsType                    freezeFunds;              //冻结资金
};

//SOP-委托回报
struct APISTRUCT DFITCSOPEntrustOrderRtnField
{
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSessionIDType                sessionID;                //会话编号
    DFITCSECBranchIDType                 branchID;                 //机构代码
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志
    DFITCSECPriceType                    entrustPrice;             //委托价格
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECCoveredFlagType              coveredFlag;              //备兑类型
    DFITCSECOrderTypeType                orderType;                //订单类型
    DFITCSECOrderExpiryDateType          orderExpiryDate;          //订单时效限制
    DFITCSECOrderCategoryType            orderCategory;            //委托单类别
    DFITCSECDeclareResultType            declareResult;            //申报结果
    DFITCSECMessageType                  noteMsg;                  //结果说明
    DFITCSECTDevIDType                   devID;                    //厂商ID(N),下单时填入该字段，才会返回
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)，下单时填入该字段，才会返回
    DFITCSECExchangeGroupTypeType        groupType;                //(预留字段) 组合类型(Y)
    DFITCSECGroupCodeType                groupCode;                //(预留字段) 组合编码(Y) 拆分委托时传入该字段才会返回
    DFITCSECSecurityIDType               securityOptionID1;        //(预留字段) 期权代码1腿(Y)
    DFITCSECSecurityIDType               securityOptionID2;        //(预留字段) 期权代码2腿(Y)
    DFITCSECSecurityIDType               securityOptionID3;        //(预留字段) 期权代码3腿(N)(预留字段)
    DFITCSECSecurityIDType               securityOptionID4;        //(预留字段) 期权代码4腿(N)(预留字段)
};

//SOP-成交回报
struct APISTRUCT DFITCSOPTradeRtnField
{
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSessionIDType                sessionID;                //会话编号
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志
    DFITCSECCoveredFlagType              coveredFlag;              //备兑标志
    DFITCSECOrderCategoryType            orderCategory;            //委托单类别
    DFITCSECFundsType                    tradePrice;               //成交价格
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECTradeIDType                  tradeID;                  //成交编号
    DFITCSECSerialIDType                 rtnSerialID;              //回报序号
    DFITCSECDeclareOrderIDType           declareOrderID;           //申报委托号
    DFITCSECDeclareResultType            declareResult;            //申报结果
    DFITCSECMessageType                  noteMsg;                  //结果说明
    DFITCSECTDevIDType                   devID;                    //厂商ID(N),下单时填入该字段，才会返回
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N),下单时填入该字段，才会返回
    DFITCSECTimeType                     tradeTime;                //成交时间
    DFITCSECGroupCodeType                groupCode;                //组合编码(组合成交后才推送)
    DFITCSECExchangeGroupTypeType        groupType;                //(预留字段) 组合类型(Y)
    DFITCSECSecurityIDType               securityOptionID1;        //(预留字段) 期权代码1腿(Y)
    DFITCSECSecurityIDType               securityOptionID2;        //(预留字段) 期权代码2腿(Y)
    DFITCSECSecurityIDType               securityOptionID3;        //(预留字段) 期权代码3腿(N)(预留字段)
    DFITCSECSecurityIDType               securityOptionID4;        //(预留字段) 期权代码4腿(N)(预留字段)
};

//SOP-撤单回报
struct APISTRUCT DFITCSOPWithdrawOrderRtnField
{
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSessionIDType                sessionID;                //会话编号
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志
    DFITCSECQuantityType                 withdrawQty;              //撤单数量
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECDeclareResultType            declareResult;            //申报结果
    DFITCSECMessageType                  noteMsg;                  //结果说明
    DFITCSECFundsType                    wdUnFreezeFunds;          //撤单解冻资金
    DFITCSECTDevIDType                   devID;                    //厂商ID(N),下单时填入该字段，才会返回
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N),下单时填入该字段，才会返回
};

//SOP-做市商报单请求
struct APISTRUCT DFITCSOPReqQuoteEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)(不支持上海)
    DFITCSECSecurityIDType               securityID;               //证劵代码(Y)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(Y)(单边报价需要，双边报价不需要)
    DFITCSECQuantityType                 bidQty;                   //买委托数量(N)
    DFITCSECPriceType                    bidPrice;                 //买委托价格(N)
    DFITCSECOpenCloseFlagType            bidOpenCloseFlag;         //买开平标志(N)
    DFITCSECCoveredFlagType              bidCoveredFlag;           //买备兑标志(N)
    DFITCSECQuantityType                 askQty;                   //卖委托数量(N)
    DFITCSECPriceType                    askPrice;                 //卖委托价格(N)
    DFITCSECOpenCloseFlagType            askOpenCloseFlag;         //卖开平标志(N)
    DFITCSECCoveredFlagType              askCoveredFlag;           //卖备兑标志(N)
    DFITCSECOrderTypeType                orderType;                //订单类型(Y)(上海需要)
    DFITCSECOrderExpiryDateType          orderExpiryDate;          //订单时效限制(N)(上海需要)
    DFITCSECOrderCategoryType            orderCategory;            //委托单类别(Y)(上海需要)
    DFITCSECQuoteIDType                  quoteID;                  //询价编号(N)(深圳需要)
    DFITCSECTDevIDType                   devID;                    //厂商ID(N)
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)
};

//SOP-做市商报单响应
struct APISTRUCT DFITCSOPRspQuoteEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECFundsType                    freezeFunds;              //冻结资金
};

//SOP-证券锁定解锁委托请求
struct APISTRUCT DFITCSOPReqLockOUnLockStockField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码 (N)
    DFITCSECSecurityIDType               securityID;               //合约代码(Y)
    DFITCSECQuantityType                 entrustQty;               //委托数量(Y)
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志(Y)
    DFITCSECTDevIDType                   devID;                    //厂商ID(N)
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)
};

//SOP-证券锁定解锁委托响应
struct APISTRUCT DFITCSOPRspLockOUnLockStockField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECFundsType                    freezeFunds;              //冻结资金
};

//SOP-分笔成交查询请求
struct APISTRUCT DFITCSOPReqQrySerialTradeField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECSecurityIDType               securityID;               //证劵代码(N)
    DFITCSECSpdOrderIDType               spdOrderID;               //委托号(N)
    DFITCSECIncQryIndexType              incQryIndex;              //增量查询索引值(N)(预留字段)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(N)
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号(N)(预留字段)
    DFITCSECTradeQryFlagType             tradeQryFlag;             //查询标志(N)(预留字段)
    DFITCSECCurrencyType                 currency;                 //币种(N)
    DFITCSECQuantityType                 rowIndex;                 //分页索引值(N)
    DFITCSECQuantityType                 rowCount;                 //每页查询笔数(N)
};

//SOP-分笔成交查询响应
struct APISTRUCT DFITCSOPRspQrySerialTradeField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSerialIDType                 rtnSerialID;              //回报序号
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECDeclareOrderIDType           declareOrderID;           //申报委托号
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECTradeIDType                  tradeID;                  //成交编号
    DFITCSECTimeType                     tradeTime;                //成交时间
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志
    DFITCSECCoveredFlagType              coveredFlag;              //备兑标志
    DFITCSECSpdOrderIDType               spdOrderID;               //委托号
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECPriceType                    tradePrice;               //成交价格
    DFITCSECFundsType                    clearFunds;               //清算资金
    DFITCSECTimeType                     rotationTime;             //回转时间
    DFITCSECIncQryIndexType              incQryIndex;              //分页索引值
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECAccountIDType                capitalID;                //资金账号
    DFITCSECTDevIDType                   devID;                    //厂商ID(N),委托时传入该字段才会返回
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N),委托时传入该字段才会返回
    DFITCSECExchangeGroupTypeType        groupType;                //(预留字段) 组合类型(Y)
    DFITCSECGroupCodeType                groupCode;                //(预留字段) 组合编码(Y) 拆分委托时传入该字段才会返回
    DFITCSECSecurityIDType               securityOptionID1;        //(预留字段) 期权代码1腿(Y)
    DFITCSECSecurityIDType               securityOptionID2;        //(预留字段) 期权代码2腿(Y)
    DFITCSECSecurityIDType               securityOptionID3;        //(预留字段) 期权代码3腿(N)(预留字段)
    DFITCSECSecurityIDType               securityOptionID4;        //(预留字段) 期权代码4腿(N)(预留字段)
};

//SOP-委托查询请求
struct APISTRUCT DFITCSOPReqQryEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECSecurityIDType               securityOptionID;         //期权代码(N)
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志(N)
    DFITCSECSerialIDType                 exSerialID;               //扩展流水号(N)(预留字段)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(N)
    DFITCSECSpdOrderIDType               spdOrderID;               //委托号(N)
    DFITCSECEntrustQryFlagType           entrustQryFlag;           //查询标志(N)
    DFITCSECQuantityType                 rowIndex;                 //分页索引值(N)
    DFITCSECQuantityType                 rowCount;                 //每页查询笔数(N)
};

//SOP-委托查询响应
struct APISTRUCT DFITCSOPRspQryEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSpdOrderIDType               spdOrderID;               //委托号
    DFITCSECDeclareOrderIDType           withdrawOrderID;          //撤销委托号
    DFITCSECDeclareOrderIDType           declareOrderID;           //申报委托号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECWithdrawFlagType             withdrawFlag;             //撤销标志
    DFITCSECSecurityIDType               securityOptionID;         //期权代码
    DFITCSECOptionTypeType               optType;                  //期权类别
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志
    DFITCSECCoveredFlagType              coveredFlag;              //备兑标志
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECPriceType                    entrustPrice;             //委托价格
    DFITCSECDateType                     entrustDate;              //委托日期
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECShareholderIDType            offerShareholderID;       //报盘股东号
    DFITCSECDateType                     declareDate;              //申报日期
    DFITCSECTimeType                     declareTime;              //申报时间
    DFITCSECSerialIDType                 declareSerialID;          //申报记录号
    DFITCSECDeclareResultType            declareResult;            //申报结果
    DFITCSECMessageType                  noteMsg;                  //结果说明
    DFITCSECQuantityType                 withdrawQty;              //撤单数量
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECPriceType                    tradePrice;               //成交价格
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsType                    freezeFunds;              //冻结资金
    DFITCSECFundsType                    clearFunds;               //清算资金
    DFITCSECEntrustTypeType              entrustType;              //委托方式
    DFITCSECMacAddressType               macAddr;                  //MAC地址
    DFITCSECIPAddressType                ipAddr;                   //IP地址
    DFITCSECEntrustBatchIDType           entrustBatchID;           //委托批次号
    DFITCSECOrderTypeType                orderType;                //委托类型
    DFITCSECIncQryIndexType              incQryIndex;              //增量查询索引值
    DFITCSECAccountIDType                capitalID;                //资金账号
    DFITCSECOrderExpiryDateType          orderExpiryDate;          //订单时效限制
    DFITCSECTDevIDType                   devID;                    //厂商ID(N),委托时传入该字段才会返回
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N),委托时传入该字段才会返回
    DFITCSECExchangeGroupTypeType        groupType;                //组合类型(Y)
    DFITCSECGroupCodeType                groupCode;                //组合编码(Y) 拆分委托时传入该字段才会返回
    DFITCSECSecurityIDType               securityOptionID1;        //期权代码1腿(Y)
    DFITCSECSecurityIDType               securityOptionID2;        //期权代码2腿(Y)
    DFITCSECSecurityIDType               securityOptionID3;        //期权代码3腿(N)(预留字段)
    DFITCSECSecurityIDType               securityOptionID4;        //期权代码4腿(N)(预留字段)
};

//SOP-持仓查询请求
struct APISTRUCT DFITCSOPReqQryPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECSecurityIDType               securityOptionID;         //期权代码(N)
    DFITCSECQuantityType                 rowIndex;                 //分页索引值(N)
    DFITCSECQuantityType                 rowCount;                 //每页查询笔数(N)
};

//SOP-持仓查询响应
struct APISTRUCT DFITCSOPRspQryPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码
    DFITCSECSecurityIDType               securityOptionID;         //期权代码
    DFITCSECContractIDType               contractID;               //期权编码
    DFITCSECContractNameType             contractName;             //期权名称
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECCoveredFlagType              coveredFlag;              //备兑标志
    DFITCSECDateType                     executeDate;              //行权日期
    DFITCSECQuantityType                 totalQty;                 //当前数量
    DFITCSECQuantityType                 availableQty;             //可用数量
    DFITCSECFundsType                    latestPrice;              //最新价
    DFITCSECFundsType                    optionMarket;             //期权市值
    DFITCSECQuantityType                 freezeQty;                //冻结数量
    DFITCSECQuantityType                 executeQty;               //执行数量
    DFITCSECQuantityType                 openEntrustQty;           //开仓委托数量
    DFITCSECQuantityType                 openTradeQty;             //开仓成交数量
    DFITCSECQuantityType                 prePosition;              //昨持仓
    DFITCSECQuantityType                 closeEntrustQty;          //平仓委托数量
    DFITCSECQuantityType                 closeTradeQty;            //平仓成交数量
    DFITCSECFundsType                    deposit;                  //保证金
    DFITCSECFundsType                    openDeposit;              //本日开仓保证金
    DFITCSECFundsType                    closeDeposit;             //本日平仓保证金
    DFITCSECFundsType                    exchangeDeposit;          //交易所保证金
    DFITCSECFundsType                    exchangeOpenDeposit;      //交易所开仓保证金
    DFITCSECFundsType                    exchangeCloseDeposit;     //交易所平仓保证金
    DFITCSECFundsType                    openAvgPrice;             //开仓均价
    DFITCSECOptionTypeType               optType;                  //期权类型
    DFITCSECContractObjectTypeType       contractObjectType;       //标的类型
    DFITCSECContractUnitType             contractUnit;             //合约单位
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsType                    totalTradeCost;           //累计交易成本(到昨日位置累计)
    DFITCSECFundsType                    tradeCost;                //本日交易成本(实时更新)
    DFITCSECFundsType                    realizeProfitLoss;        //实现盈亏(预留字段)
    DFITCSECFundsType                    profitLoss;               //盈亏金额(预留字段)
    DFITCSECContractAdjustRemindType     adjustRemind;             //合约调整提醒标志
    DFITCSECContraceExpireRemindType     expireRemind;             //合约即将到期提醒标志
};

//SOP-客户担保持仓查询请求
struct APISTRUCT DFITCSOPReqQryCollateralPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)(交易所、证券代码需要同时传入)
    DFITCSECSecurityIDType               securityID;               //证券代码(N)(交易所、证券代码需要同时传入)
};

//SOP-客户担保持仓查询响应
struct APISTRUCT DFITCSOPRspQryCollateralPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECQuantityType                 availableQty;             //可用数量
};

//SOP-客户资金查询请求
struct APISTRUCT DFITCSOPReqQryCapitalAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECCurrencyType                 currency;                 //币种(N)(当前只支持人民币)
    DFITCSECFundsQryFlagType             FundsQryFlag;             //查询标志(预留字段)
};

//SOP-客户资金查询响应
struct APISTRUCT DFITCSOPRspQryCapitalAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECBranchIDType                 branchID;                 //机构编码
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECFundsType                    accountBanlance;          //账户余额
    DFITCSECFundsType                    availableFunds;           //可用资金
    DFITCSECFundsType                    freezeFunds;              //冻结资金
    DFITCSECFundsType                    anticipatedInterest;      //预计利息
    DFITCSECFundsType                    usedDeposit;              //占用保证金
    DFITCSECAccountStatusType            accountStatus;            //客户状态
    DFITCSECFundsType                    totalFunds;               //总资金
    DFITCSECFundsType                    totalMarket;              //总市值
    DFITCSECFundsType                    cashAssets;               //现金资产
    DFITCSECFundsType                    execGuaranteeRatio;       //履约担保比例
    DFITCSECFundsType                    buyLimits;                //买入额度
};

//SOP-客户信息查询请求
struct APISTRUCT  DFITCSOPReqQryAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//SOP-客户信息查询响应
struct APISTRUCT  DFITCSOPRspQryAccountField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECAccountNameType              accountName;              //客户姓名
    DFITCSECAccountNameType              accountFullName;          //客户全名
    DFITCSECBranchIDType                 branchID;                 //机构编码
    DFITCSECAccountIdentityTypeType      identityType;             //证件类型
    DFITCSECAccountIdentityIDType        accountIdentityID;        //证件编号
    DFITCSECPhoneIDType                  tel;                      //客户电话
    DFITCSECPhoneIDType                  mobile;                   //移动电话
    DFITCSECAccountTypeType              accountType;              //投资者分类
    DFITCSECAccountPropType              accountProp;              //客户属性
    DFITCSECTradePermissionsType         tradePermissions;         //交易权限(预留字段)
    DFITCSECEntrustTypeType              entrustType;              //委托方式
    DFITCSECAccountStatusType            accountStatus;            //客户状态
    DFITCSECPasswdSyncFlagType           pwdSynFlag;               //密码同步标志
    DFITCSECAccountNodeIDType            accountNodeID;            //客户所属节点编号
};

//SOP-可委托数量查询请求
struct APISTRUCT DFITCSOPReqCalcAbleEntrustQtyField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码(N)
    DFITCSECSecurityIDType               securityOptionID;         //期权代码(Y)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(Y)
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志(Y)
    DFITCSECCoveredFlagType              coveredFlag;              //备兑标志(N)
    DFITCSECPriceType                    entrustPrice;             //委托价格(N)
    DFITCSECCheckUpLimitFlagType         checkUpLimit;             //是否检查委托上限(N)
    DFITCSECTDevIDType                   devID;                    //厂商ID(N)
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)
};

//SOP-可委托数量查询响应
struct APISTRUCT DFITCSOPRspCalcAbleEntrustQtyField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityOptionID;         //期权代码
    DFITCSECQuantityType                 entrustQty;               //委托数量
};

//SOP-股东信息查询请求
struct APISTRUCT  DFITCSOPReqQryShareholderField
{
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
};

//SOP-股东信息查询响应
struct APISTRUCT  DFITCSOPRspQryShareholderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECBranchIDType                 branchID;                 //机构编码
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECTradePermissionsType         tradePermissions;         //交易权限
    DFITCSECShareholderSpecPropType      shareholderSpecProp;      //股东指定属性
    DFITCSECShareholderCtlPropType       shareholderCtlProp;       //股东控制属性
    DFITCSECShareholderStatusType        shareholderStatus;        //股东状态
    DFITCSECMainAccountFlagType          mainAccountFlag;          //主账户标志
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
};

//SOP-客户可锁定证券查询请求
struct APISTRUCT DFITCSOPReqQryAbleLockStockField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSecurityIDType               securityID;               //证券代码(Y)
};

//SOP-客户可锁定证券查询响应
struct APISTRUCT DFITCSOPRspQryAbleLockStockField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityNameType             securityName;             //证券名称(预留字段)
    DFITCSECQuantityType                 securityQty;              //持有数量(预留字段)
    DFITCSECQuantityType                 position;                 //当前数量(预留字段)
    DFITCSECPriceType                    avgPositionPrice;         //持仓均价(预留字段)
    DFITCSECFundsType                    dilutedCost;              //摊薄成本价(预留字段)
    DFITCSECPriceType                    breakevenPrice;           //保本价(预留字段)
    DFITCSECPriceType                    dilutedBreakevenPrice;    //摊薄保本价(预留字段)
    DFITCSECQuantityType                 ableSellQty;              //可卖出数量
    DFITCSECFundsType                    latestMarket;             //最新市值(预留字段)
    DFITCSECPriceType                    latestPrice;              //最新价(预留字段)
    DFITCSECFundsType                    floatProfitLoss;          //浮动盈亏(预留字段)
    DFITCSECFundsType                    dilutedFloatProfitLoss;   //摊薄浮动盈亏(预留字段)
    DFITCSECTradeUnitType                tradeUnit;                //交易单位(预留字段)
    DFITCSECQuantityType                 openBuyQty;               //今开仓买入持仓量(预留字段)
    DFITCSECQuantityType                 openSellQty;              //今开仓卖出持仓量(预留字段)
    DFITCSECQuantityType                 buyUnSettleQty;           //买入未交收持仓量(预留字段)
    DFITCSECQuantityType                 sellUnSettleQty;          //卖出未交收持仓量(预留字段)
    DFITCSECQuantityType                 openEntrustSellQty;       //今开仓委托卖出量(预留字段)
    DFITCSECQuantityType                 ableLockQty;              //可锁定数量
};

//SOP-客户行权指派信息查询请求
struct APISTRUCT DFITCSOPReqQryExecAssiInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSecurityIDType               securityOptionID;         //期权代码(N)
    DFITCSECDateType                     tradeDate;                //查询日期(N)
};

//SOP-客户行权指派信息查询响应
struct APISTRUCT DFITCSOPRspQryExecAssiInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECDateType                     tradeDate;                //成交日期
    DFITCSECBranchIDType                 branchID;                 //机构代码
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECSubAccountIDType             subAccountID;             //子账户
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECOptionTypeType               optType;                  //期权类型
    DFITCSECContractObjectTypeType       contractObjectType;       //标的类型
    DFITCSECCoveredFlagType              coveredFlag;              //备兑标志
    DFITCSECSecurityIDType               securityOptionID;         //期权代码
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECSecurityIDType               securityID;               //标的代码
    DFITCSECSeatIDType                   seatID;                   //席位代码
    DFITCSECPriceType                    execPrice;                //行权价格
    DFITCSECQuantityType                 execQty;                  //行权数量
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECFundsType                    clearFunds;               //清算金额
    DFITCSECFundsType                    settleFunds;              //结算金额
    DFITCSECFundsType                    commission;               //佣金
    DFITCSECFundsType                    stampTax;                 //印花税
    DFITCSECFundsType                    transferFee;              //过户费
    DFITCSECFundsType                    fee3;                     //费用3
    DFITCSECFundsType                    fee4;                     //费用4
    DFITCSECMessageType                  summaryMsg;               //摘要
};

//SOP-期权合约代码查询请求
struct APISTRUCT DFITCSOPReqQryContactField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECSecurityIDType               securityOptionID;         //期权代码(N)
    DFITCSECSecurityIDType               securityID;               //标的代码(N)
    DFITCSECContractObjectTypeType       contractObjectType;       //标的类型(N)
    DFITCSECOptionTypeType               optType;                  //期权类型(N)
    DFITCSECSecurityIDType               rowIndex;                 //分页索引值(预留字段)(N)
    DFITCSECQuantityType                 rowCount;                 //每页查询笔数(预留字段)(N)
};

//SOP-期权合约代码查询响应
struct APISTRUCT DFITCSOPRspQryContactField
{
    DFITCSECRequestIDType               requestID;                 //请求ID
    DFITCSECAccountIDType               accountID;                 //客户号
    DFITCSECExchangeIDType              exchangeID;                //交易所
    DFITCSECSecurityIDType              securityOptionID;          //期权交易代码(10000031)
    DFITCSECContractIDType              contractID;                //期权标识代码(600104C1406M01200)
    DFITCSECContractNameType            contractName;              //期权名称(上汽集团购6月1200)
    DFITCSECSecurityIDType              securityID;                //标的代码(600104)
    DFITCSECContractObjectTypeType      contractObjectType;        //标的类型
    DFITCSECExecuteTypeType             execType;                  //行权方式
    DFITCSECDeliveryTypeType            deliType;                  //交割方式(预留字段)
    DFITCSECOptionTypeType              optType;                   //期权类型
    DFITCSECContractUnitType            contactUnit;               //合约单位
    DFITCSECFundsType                   latestPrice;               //最新价
    DFITCSECDateType                    beginTradingDay;           //开始交易日
    DFITCSECDateType                    endTradingDay;             //最后交易日
    DFITCSECDateType                    execDate;                  //行权日期
    DFITCSECDateType                    endDate;                   //到期日
    DFITCSECQuantityType                positionUpLimit;           //持仓上限
    DFITCSECFundsType                   priceUpLimit;              //涨停价
    DFITCSECFundsType                   priceDownLimit;            //跌停价
    DFITCSECFundsType                   priceHigher;               //最高价
    DFITCSECFundsType                   priceLower;                //最低价
    DFITCSECQuantityType                entrustUpLimit;            //委托上限
    DFITCSECQuantityType                entrustDownLimit;          //委托下限
    DFITCSECQuantityType                entrustUpLimitMarketPri;   //市价委托上限(MP=Market Price)
    DFITCSECQuantityType                entrustDownLimitMarketPri; //市价委托下限
    DFITCSECOpenLimitsType              openLimit;                 //开仓限制
    DFITCSECStockTradeFlagType          stockTradeFlag;            //停牌标志
    DFITCSECFundsType                   depositUnit;               //单位保证金
    DFITCSECFundsType                   depositRatioC;             //保证金比例1
    DFITCSECFundsType                   depositRatioE;             //保证金比例2
    DFITCSECPriceType                   preClosePrice;             //昨收盘价
    DFITCSECPriceType                   closePrice;                //今收盘价
    DFITCSECPriceType                   preSettlePrice;            //昨结算价
    DFITCSECPriceType                   openPrice;                 //开盘价
    DFITCSECLargeQuantityType           tradeQty;                  //成交数量
    DFITCSECFundsType                   turnover;                  //成交金额
    DFITCSECPriceType                   settlePrice;               //结算价(预留字段)
    DFITCSECPriceType                   endCashSettlePrice;        //到期现金结算价
    DFITCSECQuantityType                handQty;                   //整手数
    DFITCSECQuantityType                unClosePositionQty;        //未平仓合约
    DFITCSECApproachExpireFlagType      approachExpireFlag;        //临近到期标志
    DFITCSECTempAdjuestFlagType         tempAdjustFlag;            //临时调整标志
    DFITCSECStockListFlagType           stockListFlag;             //股票挂牌标志
    DFITCSECFundsType                   execPrice;                 //行权价格
    DFITCSECFundsType                   bidPrice1;                 //申买价1
    DFITCSECQuantityType                bidQty1;                   //申买量1
    DFITCSECFundsType                   bidPrice2;                 //申买价2
    DFITCSECQuantityType                bidQty2;                   //申买量2
    DFITCSECFundsType                   bidPrice3;                 //申买价3
    DFITCSECQuantityType                bidQty3;                   //申买量3
    DFITCSECFundsType                   bidPrice4;                 //申买价4
    DFITCSECQuantityType                bidQty4;                   //申买量4
    DFITCSECFundsType                   bidPrice5;                 //申买价5
    DFITCSECQuantityType                bidQty5;                   //申买量5
    DFITCSECFundsType                   askPrice1;                 //申卖价1
    DFITCSECQuantityType                askQty1;                   //申卖量1
    DFITCSECFundsType                   askPrice2;                 //申卖价2
    DFITCSECQuantityType                askQty2;                   //申卖量2
    DFITCSECFundsType                   askPrice3;                 //申卖价3
    DFITCSECQuantityType                askQty3;                   //申卖量3
    DFITCSECFundsType                   askPrice4;                 //申卖价4
    DFITCSECQuantityType                askQty4;                   //申卖量4
    DFITCSECFundsType                   askPrice5;                 //申卖价5
    DFITCSECQuantityType                askQty5;                   //申卖量5
    DFITCSESecurityOptionIndexType      optionIndex;               //股票期权索引值
    DFITCSECMiniPriceChangeType         miniPriceChange;           //最小变动价位
};

//SOP-期权标的信息查询请求
struct APISTRUCT DFITCSOPReqQryContractObjectField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECSecurityIDType               securityID;               //标的代码(N)
    DFITCSECContractObjectTypeType       securityObjectType;       //标的类型(N)
};

//SOP-期权标的信息查询响应
struct APISTRUCT DFITCSOPRspQryContractObjectField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityNameType             securityName;             //标的证券名称
    DFITCSECSecurityIDType               securityID;               //标的代码
    DFITCSECContractObjectTypeType       contractObjectType;       //标的类型
    DFITCSECContractObjectStatusType     contractObjectStatus;     //标的证券状态
};

//SOP-执行委托请求
struct APISTRUCT DFITCSOPReqExectueOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSecurityIDType               securityOptionID;         //期权代码(Y)
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码(N)
    DFITCSECQuantityType                 entrustQty;               //委托数量(Y)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(Y)
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志(Y)
    DFITCSECTDevIDType                   devID;                    //厂商ID(N)
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)
};

//SOP-执行委托响应
struct APISTRUCT DFITCSOPRspExectueOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECFundsType                    freezeFunds;              //冻结资金
};

//SOP-查询交易时间请求
struct APISTRUCT DFITCSOPReqQryTradeTimeField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//SOP-查询交易时间响应
struct APISTRUCT DFITCSOPRspQryTradeTimeField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECDateType                     sysTradingDay;            //系统当前日期
    DFITCSECTimeType                     sysTime;                  //系统当前时间
};

//SOP-获取所有交易所参数请求
struct APISTRUCT DFITCSOPReqQryExchangeInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
};

//SOP-获取所有交易所参数响应
struct APISTRUCT DFITCSOPRspQryExchangeInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECExchangeNameType             exchangeName;             //交易所简称
    DFITCSECTimeType                     callauctionBegining;      //集合竞价开始时间
    DFITCSECTimeType                     callauctionEnding;        //集合竞价结束时间
    DFITCSECTimeType                     morningOpening;           //上午开市时间
    DFITCSECTimeType                     morningClosing;           //上午闭市时间
    DFITCSECTimeType                     afternoonOpening;         //下午开市时间
    DFITCSECTimeType                     afternoonClosing;         //下午闭市时间
    DFITCSECTimeType                     execOpening;              //行权开始时间
    DFITCSECTimeType                     execClosing;              //行权结束时间
    DFITCSECNightTradingFlagType         nightTradeFlag;           //夜市交易标志
    DFITCSECTimeType                     nightOpening;             //夜市开始时间
    DFITCSECTimeType                     nightClosing;             //夜市结束时间
    DFITCSECStockTradeFlagType           stockTradeStatus;         //交易状态
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECTradingDayFlagType           tradingDayFlag;           //交易日标识
};

//SOP-查询手续费参数请求
struct APISTRUCT DFITCSOPReqQryCommissionField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECReferenceTypeType            refType;                  //参数类别(N)
    DFITCSECContractObjectTypeType       contractObjectType;       //标的类型(N)
    DFITCSECSecurityIDType               securityID;               //分类代码(N)
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志(N)
    DFITCSECLvelType                     level;                    //级别(Y)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(N)
};

//SOP-查询手续费参数响应
struct APISTRUCT DFITCSOPRspQryCommissionField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECReferenceTypeType            refType;                  //参数类别
    DFITCSECContractObjectTypeType       contractObjectType;       //标的类型
    DFITCSECSecurityIDType               securityID;               //分类代码
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别
    DFITCSECLvelType                     level;                    //级别
    DFITCSECFundsType                    costRatio1;               //费用比例1
    DFITCSECFundsType                    unitCost1;                //单位费用1
    DFITCSECFundsType                    costUpLimit1;             //费用上限1
    DFITCSECFundsType                    costDonwLimit1;           //费用下限1
    DFITCSECFundsType                    costRatio2;               //费用比例2
    DFITCSECFundsType                    unitCost2;                //单位费用2
    DFITCSECFundsType                    costUpLimit2;             //费用上限2
    DFITCSECFundsType                    costDonwLimit2;           //费用下限2
    DFITCSECFundsType                    costRatio3;               //费用比例3
    DFITCSECFundsType                    unitCost3;                //单位费用3
    DFITCSECFundsType                    costRatio4;               //费用比例4
    DFITCSECFundsType                    unitCost4;                //单位费用4
};

//SOP-查询保证金率参数请求
struct APISTRUCT DFITCSOPReqQryDepositField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
    DFITCSECReferenceTypeType            refType;                  //参数类别(N)
    DFITCSECContractObjectTypeType       securityObjectType;       //标的类型(N)
    DFITCSECSecurityIDType               securityID;               //分类代码(N)
    DFITCSECLvelType                     level;                    //级别(Y)
};

//SOP-查询保证金率参数响应
struct APISTRUCT DFITCSOPRspQryDepositField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECReferenceTypeType            refType;                  //参数类别
    DFITCSECContractObjectTypeType       securityObjectType;       //标的类型
    DFITCSECSecurityIDType               securityID;               //分类代码
    DFITCSECFundsType                    depositRateC;             //保证金比例1
    DFITCSECFundsType                    depositRateE;             //保证金比例2
    DFITCSECFundsType                    depositUnit;              //单位保证金
    DFITCSECCalcTypeType                 calcType;                 //计算方式
    DFITCSECLvelType                     level;                    //级别
};

//FASL-客户可融资信息请求
struct APISTRUCT DFITCFASLReqAbleFinInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//FASL-客户可融资信息响应
struct APISTRUCT DFITCFASLRspAbleFinInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECFundsType                    accountBanlance;          //账户余额
    DFITCSECFundsType                    ableFinFunds;             //可融资资金
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECFundsType                    entrustFreezeFunds;       //委托冻结金额
};

//STOCK-可用行情信息查询请求
struct APISTRUCT DFITCReqQuotQryField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
};

//STOCK-可用行情信息查询响应
struct APISTRUCT DFITCRspQuotQryField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECSecurityNameType             securityName;             //证券名称
};

//FASL-客户可融券信息请求
struct APISTRUCT DFITCFASLReqAbleSloInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//FASL-客户可融券信息响应
struct APISTRUCT DFITCFASLRspAbleSloInfoField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECQuantityType                 ableSloQty;               //可融券数量
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECQuantityType                 entrustQty;               //委托数量
    DFITCSECQuantityType                 tradeQty;                 //成交数量
    DFITCSECTradeStatusType              status;                   //状态
    DFITCSECFundsType                    sloDepositRatio;          //融券保证金比例
};

//FASL-担保物划转请求
struct APISTRUCT DFITCFASLReqTransferCollateralField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSecurityIDType               securityID;               //证劵代码(Y)
    DFITCSECQuantityType                 transferQty;              //划转数量(Y)
};

//FASL-担保物划转响应
struct APISTRUCT DFITCFASLRspTransferCollateralField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
};

//FASL-直接还款请求
struct APISTRUCT DFITCFASLReqDirectRepaymentField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECContractNOType               contractNO;               //指定合约编号(N)
    DFITCSECFundsType                    repayFunds;               //偿还金额(Y)
};

//FASL-直接还款响应
struct APISTRUCT DFITCFASLRspDirectRepaymentField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECFundsType                    realRepayFunds;           //实际还款金额
};

//FASL-还券划转请求
struct APISTRUCT DFITCFASLReqRepayStockTransferField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
    DFITCSECLocalOrderIDType             localOrderID;              //本地委托号(Y)
    DFITCSECExchangeIDType               exchangeID;                //交易所代码(Y)
    DFITCSECQuantityType                 repayQty;                  //还券数量(Y)
    DFITCSECSecurityIDType               securityID;                //证劵代码(Y)
    DFITCSECContractNOType               contractNO;                //指定合约编号(N)
};

//FASL-还券划转响应
struct APISTRUCT DFITCFASLRspRepayStockTransferField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECSpdOrderIDType               spdOrderID;                //柜台委托号
    DFITCSECLocalOrderIDType             localOrderID;              //本地委托号
};

//FASL-信用交易请求
struct APISTRUCT DFITCFASLReqEntrustCrdtOrderField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
    DFITCSECLocalOrderIDType             localOrderID;              //本地委托号(Y)
    DFITCSECEntrustDirectionType         entrustDirection;          //委托类别(Y)
    DFITCSECExchangeIDType               exchangeID;                //交易所代码(Y)
    DFITCSECContractNOType               contractNO;                //指定合约编号(N)
    DFITCSECSecurityIDType               securityID;                //证劵代码(Y)
    DFITCSECOrderTypeType                orderType;                 //订单类型(Y)
    DFITCSECQuantityType                 entrustQty;                //委托数量(Y)
    DFITCSECPriceType                    entrustPrice;              //委托价格(Y)
};

//FASL-信用交易响应
struct APISTRUCT DFITCFASLRspEntrustCrdtOrderField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECSpdOrderIDType               spdOrderID;                //柜台委托号
    DFITCSECLocalOrderIDType             localOrderID;              //本地委托号
};


//FASL-信用委托撤单请求
struct APISTRUCT DFITCFASLReqWithdrawOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号(N)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(N)(柜台委托号和本地委托号二选一)
    DFITCSECSessionIDType                sessionID;                //会话编号(N)
};

//FASL-信用委托撤单响应
struct APISTRUCT DFITCFASLRspWithdrawOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
};


//FASL-融资融券交易请求
struct APISTRUCT DFITCFASLReqEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECLocalOrderIDType             localOrderID;              //本地委托号(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
    DFITCSECEntrustDirectionType         entrustDirection;          //委托类别(Y)
    DFITCSECExchangeIDType               exchangeID;                //交易所代码(Y)
    DFITCSECSecurityIDType               securityID;                //证劵代码(Y)
    DFITCSECOrderTypeType                orderType;                 //订单类型(Y)
    DFITCSECQuantityType                 entrustQty;                //委托数量(Y)
    DFITCSECPriceType                    entrustPrice;              //委托价格(Y)
    DFITCSECPositionSourceType           positionSource;            //头寸来源(N)
};

//FASL-融资融券交易响应
struct APISTRUCT DFITCFASLRspEntrustOrderField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECLocalOrderIDType             localOrderID;              //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;                //柜台委托号
};

//FASL-信用可委托数量查询请求
struct APISTRUCT DFITCFASLReqCalcAbleEntrustCrdtQtyField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
    DFITCSECEntrustDirectionType         entrustDirection;          //委托类别(Y)
    DFITCSECExchangeIDType               exchangeID;                //交易所代码(Y)
    DFITCSECContractNOType               contractNO;                //指定合约编号(N)(预留字段)
    DFITCSECSecurityIDType               securityID;                //证劵代码(Y)
    DFITCSECOrderTypeType                orderType;                 //订单类型(Y)
    DFITCSECPriceType                    entrustPrice;              //委托价格(Y)
    DFITCSECPositionSourceType           positionSource;            //头寸来源(N)
};

//FASL-信用可委托数量查询响应
struct APISTRUCT DFITCFASLRspCalcAbleEntrustCrdtQtyField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECQuantityType                 totalRepayQty;             //总应还数量
    DFITCSECQuantityType                 entrustQty;                //委托数量
};

//FASL-查询信用资金请求
struct APISTRUCT DFITCFASLReqQryCrdtFundsField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
};

//FASL-查询信用资金响应
struct APISTRUCT DFITCFASLRspQryCrdtFundsField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECFundsType                    availableDeposit;          //可用保证金
    DFITCSECFundsType                    maintGuaranteeRatio;       //维持担保比例
    DFITCSECFundsType                    antiMaintGuaranteeRatio;   //预计维持担保比例
    DFITCSECFundsType                    accountBanlance;           //账户余额
    DFITCSECFundsType                    availableFunds;            //可用资金
    DFITCSECFundsType                    clearFunds;                //清算资金
    DFITCSECFundsType                    stockMarket;               //证券市值
    DFITCSECFundsType                    guaranteeStockSubMarket;   //当天担保证券提交市值
    DFITCSECFundsType                    guaranteeStockMarket;      //担保证券市值
    DFITCSECFundsType                    tradeFinLiabilities;       //融资负债(已成交)
    DFITCSECFundsType                    tradeSloLiabilities;       //融券负债(已成交)
    DFITCSECFundsType                    orderFinLiabilities;       //融资负债(未成交)
    DFITCSECFundsType                    orderSloLiabilities;       //融券负债(未成交)
    DFITCSECFundsType                    sloOrderRepay;             //融券归还(未成交)
    DFITCSECFundsType                    fundsBalance;              //资金差额
    DFITCSECFundsType                    closeFunds;                //平仓金额
    DFITCSECFundsType                    activeCloseFunds;          //主动平仓金额
    DFITCSECFundsType                    ableWithdrawalAssetsStand; //可提资产标准
    DFITCSECFundsType                    withdrawalFunds;           //可取资金
    DFITCSECFundsType                    totalAssets;               //总资产
    DFITCSECFundsType                    unTransferStockMarket;     //未过户市值
    DFITCSECFundsType                    totalLiabilities;          //总负债
    DFITCSECFundsType                    netAssets;                 //净资产
    DFITCSECFundsType                    sellRepayFunds;            //本日卖出还款金额
    DFITCSECFundsType                    anticipatedInterest;       //预计利息/费用
    DFITCSECFundsType                    finProfitLoss;             //融资盈亏
    DFITCSECFundsType                    sloProfitLoss;             //融券盈亏
    DFITCSECFundsType                    sloFunds;                  //融券金额
    DFITCSECFundsType                    finCost;                   //融资费用
    DFITCSECFundsType                    sloCost;                   //融券费用
    DFITCSECFundsType                    finCurMarket;              //融资当前市值
    DFITCSECFundsType                    finUsedDeposit;            //融资占用保证金
    DFITCSECFundsType                    sloUsedDeposit;            //融券占用保证金
    DFITCSECFundsType                    finAntiInterest;           //融资预计利息
    DFITCSECFundsType                    sloAntiInterest;           //融券预计利息
    DFITCSECFundsType                    shGuaranteeStockMarket;    //上海担保证券市值
    DFITCSECFundsType                    szGuaranteeStockMarket;    //深圳担保证券市值
    DFITCSECFundsType                    finFloatProfit;            //融资浮盈折算
    DFITCSECFundsType                    finFloatLoss;              //融资浮亏
    DFITCSECFundsType                    sloFloatProfit;            //融券浮盈折算
    DFITCSECFundsType                    sloFloatLoss;              //融券浮亏
    DFITCSECFundsType                    finRatio;                  //融资利率
    DFITCSECFundsType                    sloRatio;                  //融券利率
    DFITCSECDateType                     contractEndDate;           //合同到期日
    DFITCSECFundsType                    finUsedLimits;             //融资已用额度
    DFITCSECFundsType                    sloUsedLimits;             //融券已用额度
    DFITCSECFundsType                    finCreditLimits;           //融资授信额度
    DFITCSECFundsType                    sloCreditLimits;           //融券授信额度
    DFITCSECFundsType                    ableBuyCollateralFunds;    //可买担保品资金
    DFITCSECFundsType                    ableRepayFunds;            //可还款金额
    DFITCSECFundsType                    sloAvailableFunds;         //融券可用资金
    DFITCSECFundsType                    cashAssets;                //现金资产(所有资产、包括融券卖出)
    DFITCSECFundsType                    totalStockMarket;          //所有证券市值(包含融资买入、非担保品)
    DFITCSECFundsType                    finContractFunds;          //融资合约金额(不包含费用)
    DFITCSECFundsType                    contractObjectMarket;      //标的证券市值
    DFITCSECFundsType                    otherCharges;              //其他费用
    DFITCSECFundsType                    sloCurMarket;              //融券当前市值
};

//FASL-信用合约信息请求
struct APISTRUCT DFITCFASLReqQryCrdtContractField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
    DFITCSECDateType                     openBeginDate;             //开仓起始日期(N)
    DFITCSECDateType                     openEndDate;               //开仓结束日期(N)
    DFITCSECCrdtContractQryFlagType      crdtConQryFlag;            //查询标志(N)
    DFITCSECSpdOrderIDType               spdOrderID;                //柜台委托号(N)
    DFITCSECEntrustDirectionType         entrustDirection;          //委托类别(N)
    DFITCSECExchangeIDType               exchangeID;                //交易所代码(N)
    DFITCSECContractNOType               contractNO;                //指定合约编号(N)
    DFITCSECSecurityIDType               securityID;                //证劵代码(N)
    DFITCSECSerialIDType                 conSerialID;               //合约流水号(N)
};

//FASL-信用合约信息响应
struct APISTRUCT DFITCFASLRspQryCrdtContractField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECSerialIDType                 conSerialNO;               //合约流水号
    DFITCSECContractNOType               contractNO;                //指定合约编号
    DFITCSECDateType                     operatorDate;              //发生日期
    DFITCSECDateType                     endDate;                   //到期日期
    DFITCSECSpdOrderIDType               spdOrderID;                //柜台委托号
    DFITCSECEntrustDirectionType         entrustDirection;          //委托类别
    DFITCSECExchangeIDType               exchangeID;                //交易所代码
    DFITCSECSecurityIDType               securityID;                //证劵代码
    DFITCSECSecurityNameType             securityName;              //证券名称
    DFITCSECCurrencyType                 currency;                  //币种
    DFITCSECQuantityType                 finQty;                    //融资数量
    DFITCSECFundsType                    finFunds;                  //融资金额
    DFITCSECQuantityType                 sloQty;                    //融券数量
    DFITCSECFundsType                    sloFunds;                  //融券金额
    DFITCSECQuantityType                 finEntrustQty;             //当日融资委托数量
    DFITCSECFundsType                    finEntrustFunds;           //当日融资委托金额
    DFITCSECQuantityType                 sloEntrustQty;             //当日融券委托数量
    DFITCSECFundsType                    sloEntrustFunds;           //当日融券委托金额
    DFITCSECQuantityType                 finTradeQty;               //当日融资成交数量
    DFITCSECFundsType                    finTradeFunds;             //当日融资成交金额
    DFITCSECQuantityType                 sloTradeQty;               //当日融券成交数量
    DFITCSECFundsType                    sloTradeFunds;             //当日融券成交金额
    DFITCSECFundsType                    debtPrincipal;             //负债本金
    DFITCSECFundsType                    repayFunds;                //还款金额
    DFITCSECQuantityType                 debtQty;                   //负债数量
    DFITCSECQuantityType                 repayQty;                  //还劵数量
    DFITCSECFundsType                    sellStockRepayFunds;       //当日卖券还款额
    DFITCSECQuantityType                 buyStockForRepayEntrustQty;//当日买券还券委托数量
    DFITCSECQuantityType                 buyStockForRepayTradeQty;  //当日买券还券成交数量
    DFITCSECFundsType                    finCost;                   //融资费用
    DFITCSECFundsType                    sloCost;                   //融券费用
    DFITCSECFundsType                    totalInterest;             //总利息
    DFITCSECFundsType                    repaidInterest;            //已归还利息
    DFITCSECCrdtContractStatusType       crdtConStatus;             //合约状态(预留字段)
    DFITCSECFundsType                    leftInterest;              //剩余利息
    DFITCSECFundsType                    sloLeftFunds;              //融券剩余资金
    DFITCSECFundsType                    buyStockFreezeFunds;       //买券冻结金额
    DFITCSECFundsType                    buyStockClearFunds;        //买券清算金额
    DFITCSECFundsType                    sloLeftAvaiFunds;          //融券剩余可用(买券还券可用资金)
    DFITCSECFundsType                    debtQtyEntrustMarket;      //负债数量(委托后)市值
    DFITCSECFundsType                    debtQtyTradeMarket;        //负债数量(成交后)市值
    DFITCSECFundsType                    debtFundsMarket;           //负债金额市值
    DFITCSECFundsType                    finProfitLoss;             //融资盈亏
    DFITCSECFundsType                    sloProfitLoss;             //融券盈亏
    DFITCSECQuantityType                 entrustQty;                //委托数量
    DFITCSECQuantityType                 conOpenQty;                //合约开仓数量
    DFITCSECFundsType                    conOpenFunds;              //合约开仓金额
    DFITCSECFundsType                    conOpenCost;               //合约开仓费用
    DFITCSECQuantityType                 conInitQty;                //期初合约数量
    DFITCSECFundsType                    conInitFunds;              //期初合约金额
    DFITCSECFundsType                    conInitCost;               //期初合约费用
    DFITCSECFundsType                    unRepayConFunds;           //未还合约金额
    DFITCSECQuantityType                 unRepayConQty;             //未还合约数量
    DFITCSECFundsType                    unRepayConCost;            //未还合约费用
    DFITCSECPositionNOType               positionNO;                //头寸编号
};

//FASL-信用合约变动信息查询请求
struct APISTRUCT DFITCFASLReqQryCrdtConChangeInfoField
{
    DFITCSECRequestIDType                requestID;                 //请求ID(Y)
    DFITCSECAccountIDType                accountID;                 //客户号(Y)
    DFITCSECWithdrawFlagType             withdrawFlag;              //撤销标志(N)
    DFITCSECEntrustDirectionType         entrustDirection;          //委托类别(N)
    DFITCSECExchangeIDType               exchangeID;                //交易所代码(N)
    DFITCSECSecurityIDType               securityID;                //证劵代码(N)
    DFITCSECSerialIDType                 conSerialNO;               //合约流水号(N)
};

//FASL-信用合约变动信息查询响应
struct APISTRUCT DFITCFASLRspQryCrdtConChangeInfoField
{
    DFITCSECRequestIDType                requestID;                 //请求ID
    DFITCSECAccountIDType                accountID;                 //客户号
    DFITCSECSerialIDType                 serialNO;                  //合约流水号
    DFITCSECContractNOType               conChangeNO;               //合约变动序号
    DFITCSECWithdrawFlagType             withdrawFlag;              //撤销标志(预留字段)
    DFITCSECSecurityIDType               securityID;                //证劵代码
    DFITCSECEntrustDirectionType         entrustDirection;          //委托类别
    DFITCSECFundsType                    operatorFunds;             //发生金额
    DFITCSECTimeType                     operatorTime;              //发生时间
    DFITCSECQuantityType                 operatorQty;               //发生数量
    DFITCSECDateType                     operatorDate;              //发生日期
    DFITCSECClearFlagType                clearFlag;                 //清算标志
    DFITCSECFundsType                    commission;                //手续费
    DFITCSECFundsType                    operatorFunds2;            //发生金额(预留字段)
    DFITCSECFundsType                    postFunds;                 //后资金额
    DFITCSECQuantityType                 postQty;                   //后证券额
    DFITCSECExchangeIDType               exchangeID;                //交易所代码
    DFITCSECFundsType                    operatorCost;              //发生费用
    DFITCSECFundsType                    postCost;                  //后余费用
    DFITCSECFundsType                    operatorInterest;          //发生利息
    DFITCSECFundsType                    postInterest;              //后余利息
    DFITCSECMessageType                  changeNote;                //变动说明
    DFITCSECShareholderIDType            shareholderID;             //股东号
};

//FASL-查询系统时间请求
struct APISTRUCT DFITCFASLReqQryTradeTimeField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSystemQryFlagType            flag;                     //高精度返回标志(N)
};

//FASL-查询系统时间响应
struct APISTRUCT DFITCFASLRspQryTradeTimeField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECDateType                     sysTradingDay;            //系统当前日期
    DFITCSECTimeType                     sysTime;                  //系统当前时间
    DFITCSECWeekType                     sysWeek;                  //系统当前星期(flag为1时才返回)
    DFITCSECMillisecondType              sysMillisecond;           //系统当前毫秒(flag为1时才返回)
};

//FASL-可转入担保证券查询
struct APISTRUCT DFITCFASLReqQryTransferredContractField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECSecurityIDType               securityID;               //证券代码(N)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(N)
};

//FASL-可转入担保证券查询响应
struct APISTRUCT DFITCFASLRspQryTransferredContractField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECAccountIDType                capitalID;                //资金账号
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECQuantityType                 ableSellQty;              //可卖出(转出)数量
};

//FASL-客户可取资金调出
struct APISTRUCT DFITCFASLReqDesirableFundsOutField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECCurrencyType                 currency;                 //币种(Y)
    DFITCSECFundsType                    operateFunds;             //发生金额(Y)
    DFITCSECMessageType                  summaryMsg;               //摘要(N)
};

//FASL-客户可取资金调出响应
struct APISTRUCT DFITCFASLRspDesirableFundsOutField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECSerialIDType                 serialID;                 //流水号
    DFITCSECFundsType                    accountBanlance;          //账户余额
};

//FASL-担保证券查询
struct APISTRUCT DFITCFASLReqQryGuaranteedContractField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//FASL-担保证券查询响应
struct APISTRUCT DFITCFASLRspQryGuaranteedContractField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECFundsType                    exchangRate;              //折算率
    DFITCSECTradeStatusType              status;                   //状态
    DFITCSECAccountType                  accountType;              //类型
};

//FASL-标的证券查询
struct APISTRUCT DFITCFASLReqQryUnderlyingContractField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//FASL-标的证券查询响应
struct APISTRUCT DFITCFASLRspQryUnderlyingContractField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECFundsType                    financeDepositRatio;      //融资保证金比例
    DFITCSECFundsType                    securityDepositRatio;     //融券保证金比例
    DFITCSECTradeStatusType              status;                   //状态
    DFITCSECAccountType                  accountType;              //类型
};


//QUOTE-指定的合约
struct APISTRUCT DFITCSECSpecificInstrumentField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECSecurityIDType               securityID;               //合约代码
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
};

//sop 特有的
struct APISTRUCT DFITCSOPSpecificDataField
{
    DFITCSECContractIDType               contractID;               //期权标识代码(601318C1412M03500)
    DFITCSECFundsType                    execPrice;                //行权价格
    DFITCSECFundsType                    preSettlePrice;           //昨结算价
    DFITCSECFundsType                    settlePrice;              //结算价
    DFITCSECLargeQuantityType            positionQty;              //持仓数量
    DFITCSECFundsType                    auctionPrice;             //动态参考价格
    DFITCSECTimeType                     latestEnquiryTime;        //预留时间字段
};

//stock 特有的
struct APISTRUCT DFITCStockSpecificDataField
{
    DFITCSECFundsType                    peRadio1;                 //市盈率1
    DFITCSECFundsType                    peRadio2;                 //市盈率2
};

//共有静态的
struct APISTRUCT DFITCStaticDataField
{
    DFITCSECSecurityIDType               securityID;               //证券代码
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECDateType                     tradingDay;               //交易日
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECFundsType                    preClosePrice;            //昨收盘
    DFITCSECFundsType                    openPrice;                //今开盘
    DFITCSECFundsType                    upperLimitPrice;          //涨停板价
    DFITCSECFundsType                    lowerLimitPrice;          //跌停板价

};

//共有动态的
struct APISTRUCT DFITCSharedDataField
{
    DFITCSECFundsType                    latestPrice;              //最新价
    DFITCSECFundsType                    turnover;                 //成交金额
    DFITCSECFundsType                    highestPrice;             //最高价
    DFITCSECFundsType                    lowestPrice;              //最低价
    DFITCSECLargeQuantityType            tradeQty;                 //成交数量
    DFITCSECTimeType                     updateTime;               //时间戳
    DFITCSECFundsType                    bidPrice1;                //申买价一
    DFITCSECLargeQuantityType            bidQty1;                  //申买量一
    DFITCSECFundsType                    askPrice1;                //申卖价一
    DFITCSECLargeQuantityType            askQty1;                  //申卖量一
    DFITCSECFundsType                    bidPrice2;                //申买价二
    DFITCSECLargeQuantityType            bidQty2;                  //申买量二
    DFITCSECFundsType                    askPrice2;                //申卖价二
    DFITCSECLargeQuantityType            askQty2;                  //申卖量二
    DFITCSECFundsType                    bidPrice3;                //申买价三
    DFITCSECLargeQuantityType            bidQty3;                  //申买量三
    DFITCSECFundsType                    askPrice3;                //申卖价三
    DFITCSECLargeQuantityType            askQty3;                  //申卖量三
    DFITCSECFundsType                    bidPrice4;                //申买价四
    DFITCSECLargeQuantityType            bidQty4;                  //申买量四
    DFITCSECFundsType                    askPrice4;                //申卖价四
    DFITCSECLargeQuantityType            askQty4;                  //申卖量四
    DFITCSECFundsType                    bidPrice5;                //申买价五
    DFITCSECLargeQuantityType            bidQty5;                  //申买量五
    DFITCSECFundsType                    askPrice5;                //申卖价五
    DFITCSECLargeQuantityType            askQty5;                  //申卖量五
    DFITCSECTradingPhaseCodeType         tradingPhaseCode;         //产品实时阶段及标志
};

struct APISTRUCT DFITCSOPDepthMarketDataField
{
    struct DFITCSOPSpecificDataField     specificDataField;        //特有的
    struct DFITCStaticDataField          staticDataField;          //共有的静态
    struct DFITCSharedDataField          sharedDataField;          //公有的动态 
};

struct APISTRUCT DFITCStockDepthMarketDataField
{
    struct DFITCStockSpecificDataField   specificDataField;        //特有的
    struct DFITCStaticDataField          staticDataField;          //共有的静态
    struct DFITCSharedDataField          sharedDataField ;         //公有的动态 
};

//STOCK-证券静态信息查询请求
struct APISTRUCT DFITCStockReqQryStockStaticField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
};

//STOCK-证券静态信息查询响应
struct APISTRUCT DFITCStockRspQryStockStaticField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECStockTradeFlagType           stopFlag;                 //停牌标志
    DFITCSECPriceType                    preClosePrice;            //昨收盘价
    DFITCSECPriceType                    openPrice;                //今开盘价
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECSecurityIDType               securityID;               //证劵代码
    DFITCSECPriceType                    interestQuote;            //利息报价
    DFITCSECPriceType                    securityFaceValue;        //证券面值
    DFITCSECBidTradeFlagType             bidTradeFlag;             //竞价交易标志
    DFITCSECTradeUnitType                tradeUnit;                //交易单位
    DFITCSECBusinessLimitType            businessLimit;            //买卖限制
    DFITCSECSecurityTypeType             securityType;             //证券类别
    DFITCSECSecurityNameType             securityName;             //证券名称
    DFITCSECPriceType                    upperLimitPrice;          //涨停板价
    DFITCSECPriceType                    lowerLimitPrice;          //跌停板价
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECOrderTypeLimitType           orderLimits;              //订单类型限制
};

//SOP-交易所持仓组合拆分委托请求
struct APISTRUCT DFITCSOPReqGroupSplitField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSecurityIDType               securityOptionID;         //期权代码(Y)
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码(N)(预留字段)
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志(Y)
    DFITCSECExchangeGroupTypeType        groupType;                //组合类型(Y)
    DFITCSECGroupCodeType                groupCode;                //组合编码(Y)
    DFITCSECSecurityIDType               securityOptionID1;        //期权代码1腿(Y)
    DFITCSECSecurityIDType               securityOptionID2;        //期权代码2腿(Y)
    DFITCSECSecurityIDType               securityOptionID3;        //期权代码3腿(N)(预留字段)
    DFITCSECSecurityIDType               securityOptionID4;        //期权代码4腿(N)(预留字段)
    DFITCSECQuantityType                 entrustQty;               //委托数量(Y)
    DFITCSECTDevIDType                   devID;                    //厂商ID(N)
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)
};

//SOP-期权组合行权委托请求
struct APISTRUCT DFITCSOPReqGroupExectueOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号(Y)
    DFITCSECExchangeIDType               exchangeID;               //交易所代码(Y)
    DFITCSECSecurityIDType               securityOptionID1;        //期权代码1腿(Y)
    DFITCSECSecurityIDType               securityOptionID2;        //期权代码2腿(Y)
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码(N)(预留字段)
    DFITCSECQuantityType                 entrustQty;               //委托数量(Y)
    DFITCSECEntrustDirectionType         entrustDirection;         //委托类别(Y)
    DFITCSECOpenCloseFlagType            openCloseFlag;            //开平标志(Y)
    DFITCSECOrderCategoryType            orderCategory;            //委托单类别(Y)
    DFITCSECTDevIDType                   devID;                    //厂商ID(N)
    DFITCSECTDevDecInfoType              devDecInfo;               //用户自定义字段(N)
};

//SOP-期权组合行权委托响应
struct APISTRUCT DFITCSOPRspGroupExectueOrderField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECLocalOrderIDType             localOrderID;             //本地委托号
    DFITCSECSpdOrderIDType               spdOrderID;               //柜台委托号
    DFITCSECTimeType                     entrustTime;              //委托时间
    DFITCSECFundsType                    freezeFunds;              //冻结资金
};

//SOP-查询客户组合持仓明细请求
struct APISTRUCT DFITCSOPReqQryGroupPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID(Y)
    DFITCSECAccountIDType                accountID;                //客户号(Y)
};

//SOP-查询客户组合持仓明细响应
struct APISTRUCT DFITCSOPRspQryGroupPositionField
{
    DFITCSECRequestIDType                requestID;                //请求ID
    DFITCSECAccountIDType                accountID;                //客户号
    DFITCSECExchangeIDType               exchangeID;               //交易所代码
    DFITCSECShareholderIDType            shareholderID;            //股东号
    DFITCSECSubAccountIDType             subAccountID;             //子账户编码
    DFITCSECCurrencyType                 currency;                 //币种
    DFITCSECAccountIDType                capitalID;                //资金账号
    DFITCSECExchangeGroupTypeType        groupType;                //组合类型
    DFITCSECGroupCodeType                groupCode;                //组合编码
    DFITCSECQuantityType                 groupQty;                 //组合数量
    DFITCSECQuantityType                 enableSplitQty;           //可拆分数量
    DFITCSECQuantityType                 splitEntrustQty;          //拆分委托数量
    DFITCSECQuantityType                 splitTradeQty;            //拆分成交数量
    DFITCSECFundsType                    groupDeposit;             //组合保证金
    DFITCSECSecurityIDType               securityOptionID1;        //期权代码1腿
    DFITCSECSecurityIDType               securityOptionID2;        //期权代码2腿
    DFITCSECSecurityIDType               securityOptionID3;        //期权代码3腿
    DFITCSECSecurityIDType               securityOptionID4;        //期权代码4腿
};

//终端信息
struct APISTRUCT DFITCTerminalInfoField
{
    DFITCSECSystemInfo                   systemInfo;               //采集信息
    DFITCSECSecretkeyVer                 secretkeyVer;             //秘钥版本
    DFITCSECAppID                        appID;                    //AppID
    DFITCSECExceptionFlag                exceptionFlag;            //异常标识
    DFITCSECClientPublicIP               clientPublicIP;           //客户终端公网IP地址
    DFITCSECClientPublicPort             clientPublicPort;         //客户终端公网端口号
    DFITCSECClientLoginTime              clientLoginTime;          //客户终端登录时间
    DFITCSECSystemInfoIntegrity          systemInfo_integrity;     //采集信息完整性
};

#endif
