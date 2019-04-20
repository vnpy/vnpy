/*
 * Copyright 2016 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    oes_client_sample.h
 *
 * OES API接口库的CPP风格客户端示例
 *
 * @version 1.0 2017/08/24
 * @since   2017/08/24
 */


#ifndef _OES_CLIENT_SAMPLE_H
#define _OES_CLIENT_SAMPLE_H


#include    <oes_api/oes_api.h>
#include    <sutil/compiler.h>
#if ! (defined (__WINDOWS__) || defined (__MINGW__))
#include    <pthread.h>
#endif


namespace   Quant360 {


class   OesClientSpi {
public:
    /* 委托拒绝回报回调 */
    virtual void        OnBusinessReject(int32 errorCode, const OesOrdRejectT *pOrderReject) = 0;
    /* 委托已收回报回调 */
    virtual void        OnOrderInsert(const OesOrdCnfmT *pOrderInsert) = 0;
    /* 委托确认回报回调 */
    virtual void        OnOrderReport(int32 errorCode, const OesOrdCnfmT *pOrderReport) = 0;
    /* 成交确认回报回调 */
    virtual void        OnTradeReport(const OesTrdCnfmT *pTradeReport) = 0;
    /* 资金变动回报回调 */
    virtual void        OnCashAssetVariation(const OesCashAssetItemT *pCashAssetItem) = 0;
    /* 持仓变动回报回调 */
    virtual void        OnStockHoldingVariation(const OesStkHoldingItemT *pStkHoldingItem) = 0;
    /* 出入金委托拒绝回报回调 */
    virtual void        OnFundTrsfReject(int32 errorCode, const OesFundTrsfRejectT *pFundTrsfReject) = 0;
    /* 出入金委托执行回报回调 */
    virtual void        OnFundTrsfReport(int32 errorCode, const OesFundTrsfReportT *pFundTrsfReport) = 0;
    /* 市场状态信息回报回调 */
    virtual void        OnMarketState(const OesMarketStateItemT *pMarketStateItem) = 0;

    /* 查询委托信息回调 */
    virtual void        OnQueryOrder(const OesOrdItemT *pOrder, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询成交信息回调 */
    virtual void        OnQueryTrade(const OesTrdItemT *pTrade, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询资金信息回调 */
    virtual void        OnQueryCashAsset(const OesCashAssetItemT *pCashAsset, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询持仓信息回调 */
    virtual void        OnQueryStkHolding(const OesStkHoldingItemT *pStkHolding, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询配号、中签信息回调 */
    virtual void        OnQueryLotWinning(const OesLotWinningItemT *pLotWinning, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询客户信息回调 */
    virtual void        OnQueryCustInfo(const OesCustItemT *pCust, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询股东账户信息回调 */
    virtual void        OnQueryInvAcct(const OesInvAcctItemT *pInvAcct, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询佣金信息回调 */
    virtual void        OnQueryCommissionRate(const OesCommissionRateItemT *pCommissionRate, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询出入金流水信息回调 */
    virtual void        OnQueryFundTransferSerial(const OesFundTransferSerialItemT *pFundTrsf, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询证券发行信息回调 */
    virtual void        OnQueryIssue(const OesIssueItemT *pIssue, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询证券信息回调 */
    virtual void        OnQueryStock(const OesStockItemT *pStock, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询ETF产品信息回调 */
    virtual void        OnQueryEtf(const OesEtfItemT *pEtf, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询ETF成分股信息回调 */
    virtual void        OnQueryEtfComponent(const OesEtfComponentItemT *pEtfComponent, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询市场状态信息回调 */
    virtual void        OnQueryMarketState(const OesMarketStateItemT *pMarketState, const OesQryCursorT *pCursor, int32 requestId) = 0;

public:
    virtual ~OesClientSpi() {};

public:
    int32               currentRequestId;
};


class   OesClientApi {
public:
    static const char * GetVersion(void);

public:
    OesClientApi();

    virtual ~OesClientApi();

    /* 注册spi回调接口 */
    void                RegisterSpi(OesClientSpi *pSpi);
    /* 加载配置文件 */
    BOOL                LoadCfg(const char *pCfgFile);
    /* 加载配置结构 */
    BOOL                LoadCfg(OesApiClientCfgT *pApiCfg);
    /* 设置客户端的IP和MAC。需要在 start() 前调用 */
    BOOL                SetCustomizedIpAndMac(const char *pIpStr, const char *pMacStr);
    /* 设置客户端的设备序列号。需要在 start() 前调用 */
    BOOL                SetCustomizedDriverId(const char *pDriverStr);
    /* 设置当前线程登录OES时使用的登录用户名。需要在 start() 前调用 */
    void                SetThreadUsername(const char *pUsername);
    /* 设置当前线程登录OES时使用的登录密码。需要在 start() 前调用 */
    void                SetThreadPassword(const char *pPassword);

    /* 启动Client */
    BOOL                Start(int32 *pLastClSeqNo = NULL, int64 lastRptSeqNum = -1);
    /* 停止Client */
    void                Stop(void);

    /* 发送交易委托请求，非线程安全实现 */
    int32               SendOrder(const OesOrdReqT *pOrderReq);
    /* 发送撤单请求，非线程安全实现 */
    int32               SendCancelOrder(const OesOrdCancelReqT *pCancelReq);
    /* 发送出入金请求，非线程安全实现 */
    int32               SendFundTrsf(const OesFundTrsfReqT *pFundTrsfReq);

    /* 获取交易日期 */
    int32               GetTradingDay(void);
    /* 获取客户端总览信息 */
    int32               GetClientOverview(OesClientOverviewT *pClientOverview);
    /* 查询所有委托信息，非线程安全实现 */
    int32               QueryOrder(const OesQryOrdFilterT *pQryFilter, int32 requestId = 0);
    /* 查询成交信息，非线程安全实现 */
    int32               QueryTrade(const OesQryTrdFilterT *pQryFilter, int32 requestId = 0);
    /* 查询客户资金信息，非线程安全实现 */
    int32               QueryCashAsset(const OesQryCashAssetFilterT *pQryFilter, int32 requestId = 0);
    /* 查询股票持仓信息，非线程安全实现 */
    int32               QueryStkHolding(const OesQryStkHoldingFilterT *pQryFilter, int32 requestId = 0);
    /* 查询新股配号、中签信息，非线程安全实现 */
    int32               QueryLotWinning(const OesQryLotWinningFilterT *pQryFilter, int32 requestId = 0);
    /* 查询客户信息，非线程安全实现 */
    int32               QueryCustInfo(const OesQryCustFilterT *pQryFilter, int32 requestId = 0);
    /* 查询证券账户信息，非线程安全实现 */
    int32               QueryInvAcct(const OesQryInvAcctFilterT *pQryFilter, int32 requestId = 0);
    /* 查询佣金信息，非线程安全实现 */
    int32               QueryCommissionRate(const OesQryCommissionRateFilterT *pQryFilter, int32 requestId = 0);
    /* 查询出入金流水，非线程安全实现 */
    int32               QueryFundTransferSerial(const OesQryFundTransferSerialFilterT *pQryFilter, int32 requestId = 0);
    /* 查询证券发行产品信息，非线程安全实现 */
    int32               QueryIssue(const OesQryIssueFilterT *pQryFilter, int32 requestId = 0);
    /* 查询现货产品信息，非线程安全实现 */
    int32               QueryStock(const OesQryStockFilterT *pQryFilter, int32 requestId = 0);
    /* 查询ETF申赎产品信息，非线程安全实现 */
    int32               QueryEtf(const OesQryEtfFilterT *pQryFilter, int32 requestId = 0);
    /* 查询ETF成分股信息，非线程安全实现 */
    int32               QueryEtfComponent(const OesQryEtfComponentFilterT *pQryFilter, int32 requestId = 0);
    /* 查询市场状态信息，非线程安全实现 */
    int32               QueryMarketState(const OesQryMarketStateFilterT *pQryFilter, int32 requestId = 0);

private:
    /* 内部的回调处理函数，可以考虑不定义在类中 */
    static int32        HandleReportMsg(OesApiSessionInfoT *pRptChannel, SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams);
    static void *       RptThreadMain(void *pParams);

private:
    /* 禁止拷贝构造函数 */
    OesClientApi(const OesClientApi&);
    /* 禁止赋值函数 */
    OesClientApi&       operator=(const OesClientApi&);

public:
    OesApiClientCfgT    apiCfg;
    OesApiClientEnvT    apiEnv;

private:
    BOOL                isCfg;
    BOOL                isRunning;
    volatile int32      terminatedFlag;

    OesClientSpi        *pSpi;
};


}


#endif /* _OES_CLIENT_SAMPLE_H */
