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
 * OES API的C++接口库示例
 *
 * @version 0.15.10     2020/01/15
 *          - 基于异步API重构C++接口示例, 增加如下特性:
 *              - 支持自动的连接管理 (自动识别异常并重建连接)
 *              - 增加和完善了 OnConnected/OnDisconnected 回调接口, 并提供了默认实现
 *                (客户端可以不用实现这两个接口, 采用默认实现即可)
 *          - 删除以下连接重建相关的接口, 不再需要显式的重建连接
 *              - ReconnectOrdChannel
 *              - ReconnectRptChannel
 *              - ReconnectQryChannel
 *              - SendReportSynchronization
 *          - 删除或重名以下公有成员变量
 *              - 删除 apiEnv
 *              - 重命名 apiCfg => _apiCfg
 *          - 简化和废弃了 Start 方法的参数, 具体描述参见 Start 方法的函数注释
 * @since   0.15.4      2017/08/24
 */


#ifndef _OES_CPP_API_SAMPLE_H
#define _OES_CPP_API_SAMPLE_H


#include    <oes_api/oes_async_api.h>
#include    <sutil/compiler.h>


namespace   Quant360 {


/* API类的前置声明 */
class OesClientApi;


/**
 * 交易接口响应类
 */
class OesClientSpi {
public:
    /* 连接或重新连接完成后的回调函数 */
    virtual int32       OnConnected(eOesApiChannelTypeT channelType, OesApiSessionInfoT *pSessionInfo, OesApiSubscribeInfoT *pSubscribeInfo = NULL);
    /* 连接断开后的回调函数 */
    virtual int32       OnDisconnected(eOesApiChannelTypeT channelType, OesApiSessionInfoT *pSessionInfo);

    /* 委托拒绝回报 */
    virtual void        OnBusinessReject(const OesRptMsgHeadT *pRptMsgHead, const OesOrdRejectT *pOrderReject) = 0;
    /* 委托已收回报 */
    virtual void        OnOrderInsert(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderInsert) = 0;
    /* 委托确认回报 */
    virtual void        OnOrderReport(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderReport) = 0;
    /* 成交确认回报 */
    virtual void        OnTradeReport(const OesRptMsgHeadT *pRptMsgHead, const OesTrdCnfmT *pTradeReport) = 0;
    /* 资金变动通知 */
    virtual void        OnCashAssetVariation(const OesCashAssetReportT *pCashAssetRpt) = 0;
    /* 股票持仓变动通知 */
    virtual void        OnStockHoldingVariation(const OesStkHoldingReportT *pStkHoldingRpt) = 0;
    /* 期权持仓变动通知 (适用于期权业务) */
    virtual void        OnOptionHoldingVariation(const OesOptHoldingReportT *pOptHoldingRpt) = 0;
    /* 期权标的持仓变动通知 (适用于期权业务) */
    virtual void        OnOptionUnderlyingHoldingVariation(const OesOptUnderlyingHoldingReportT *pUnderlyingHoldingRpt) = 0;
    /* 期权结算单确认回报 (适用于期权业务) */
    virtual void        OnSettlementConfirmedRpt(const OesRptMsgHeadT *pRptMsgHead, const OesOptSettlementConfirmReportT *pCnfmSettlementRpt) = 0;
    /* 出入金委托拒绝回报 */
    virtual void        OnFundTrsfReject(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfRejectT *pFundTrsfReject) = 0;
    /* 出入金委托执行回报 */
    virtual void        OnFundTrsfReport(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfReportT *pFundTrsfReport) = 0;
    /* 市场状态信息通知 */
    virtual void        OnMarketState(const OesMarketStateItemT *pMarketStateItem) = 0;
    /* 通知消息回报 */
    virtual void        OnNotifyReport(const OesNotifyInfoReportT *pNotifyInfoRpt) = 0;
    /* 回报同步请求的响应 */
    virtual void        OnReportSynchronizationRsp(const OesReportSynchronizationRspT *pReportSynchronization) = 0;

    /* 查询委托信息回调 */
    virtual void        OnQueryOrder(const OesOrdItemT *pOrder, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询成交信息回调 */
    virtual void        OnQueryTrade(const OesTrdItemT *pTrade, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询资金信息回调 */
    virtual void        OnQueryCashAsset(const OesCashAssetItemT *pCashAsset, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询股票持仓信息回调 */
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
    /* 查询ETF成份证券信息回调 */
    virtual void        OnQueryEtfComponent(const OesEtfComponentItemT *pEtfComponent, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询市场状态信息回调 */
    virtual void        OnQueryMarketState(const OesMarketStateItemT *pMarketState, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询期权产品信息回调 (适用于期权业务) */
    virtual void        OnQueryOption(const OesOptionItemT *pOption, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询期权持仓信息回调 (适用于期权业务) */
    virtual void        OnQueryOptHolding(const OesOptHoldingItemT *pOptHolding, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询期权标的持仓信息回调 (适用于期权业务) */
    virtual void        OnQueryOptUnderlyingHolding(const OesOptUnderlyingHoldingItemT *pUnderlyingHld, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询期权限仓额度信息回调 (适用于期权业务) */
    virtual void        OnQueryOptPositionLimit(const OesOptPositionLimitItemT *pPositionLimit, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询期权限购额度信息回调 (适用于期权业务) */
    virtual void        OnQueryOptPurchaseLimit(const OesOptPurchaseLimitItemT *pPurchaseLimit, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询期权行权指派信息回调 (适用于期权业务) */
    virtual void        OnQueryOptExerciseAssign(const OesOptExerciseAssignItemT *pExerciseAssign, const OesQryCursorT *pCursor, int32 requestId) = 0;
    /* 查询通知消息回调 */
    virtual void        OnQueryNotifyInfo(const OesNotifyInfoItemT *pNotifyInfo, const OesQryCursorT *pCursor, int32 requestId) = 0;

public:
    OesClientSpi();
    virtual ~OesClientSpi() {};

public:
    OesClientApi        *pApi;
    int32               currentRequestId;
};


/**
 * 交易接口类
 */
class OesClientApi {
public:
    static const char * GetVersion(void);

public:
    OesClientApi();
    virtual ~OesClientApi();

    /* 注册SPI回调接口 (需要在 LoadCfg 前调用) */
    void                RegisterSpi(OesClientSpi *pSpi);
    /* 加载配置文件并初始化相关资源 */
    BOOL                LoadCfg(const char *pCfgFile);
    /* 加载配置信息并初始化相关资源 */
    BOOL                LoadCfg(OesApiClientCfgT *pApiCfg, const char *pCfgFile = NULL);
    /* 设置客户端的IP和MAC (需要在 Start 前调用) */
    BOOL                SetCustomizedIpAndMac(const char *pIpStr, const char *pMacStr);
    /* 设置客户端的IP地址 (需要在 Start 前调用) */
    BOOL                SetCustomizedIp(const char *pIpStr);
    /* 设置客户端的MAC地址 (需要在 Start 前调用) */
    BOOL                SetCustomizedMac(const char *pMacStr);
    /* 设置客户端的设备序列号 (需要在 Start 前调用) */
    BOOL                SetCustomizedDriverId(const char *pDriverStr);
    /* 设置当前线程登录OES时使用的登录用户名 (需要在 Start 前调用) */
    void                SetThreadUsername(const char *pUsername);
    /* 设置当前线程登录OES时使用的登录密码 (需要在 Start 前调用) */
    void                SetThreadPassword(const char *pPassword);
    /* 设置当前线程登录OES时使用的客户端环境号 (需要在 Start 前调用) */
    void                SetThreadEnvId(int8 clEnvId);
    /* 设置当前线程订阅回报使用的客户端环境号 (需要在 Start 前调用) */
    void                SetThreadSubscribeEnvId(int8 subscribeEnvId);

    /* 启动实例 */
    BOOL                Start(int32 *pLastClSeqNo = NULL, int64 lastRptSeqNum = -1);
    /* 停止实例并释放相关资源 */
    void                Stop(void);

    /* 发送交易委托请求 */
    int32               SendOrder(const OesOrdReqT *pOrderReq);
    /* 发送撤单请求 */
    int32               SendCancelOrder(const OesOrdCancelReqT *pCancelReq);
    /* 发送批量委托请求(以指针数组形式存放批量委托) */
    int32               SendBatchOrders(const OesOrdReqT *ppOrdPtrList[], int32 ordCount);
    /* 发送批量委托请求(以数组形式存放批量委托) */
    int32               SendBatchOrders(OesOrdReqT *pOrdReqArray, int32 ordCount);
    /* 发送出入金请求 */
    int32               SendFundTrsf(const OesFundTrsfReqT *pFundTrsfReq);
    /* 客户端密码修改请求 */
    int32               SendChangePassword(const OesChangePasswordReqT *pChangePasswordReq);
    /* 期权账户结算单确认请求 (适用于期权业务) */
    int32               SendOptSettlementConfirm(const OesOptSettlementConfirmReqT *pOptSettleCnfmReq, OesOptSettlementConfirmRspT *pOptSettleCnfmRsp);

    /* 获取交易日期 */
    int32               GetTradingDay(void);
    /* 获取客户端总览信息 */
    int32               GetClientOverview(OesClientOverviewT *pClientOverview);
    /* 查询所有委托信息 */
    int32               QueryOrder(const OesQryOrdFilterT *pQryFilter, int32 requestId = 0);
    /* 查询成交信息 */
    int32               QueryTrade(const OesQryTrdFilterT *pQryFilter, int32 requestId = 0);
    /* 查询客户资金信息 */
    int32               QueryCashAsset(const OesQryCashAssetFilterT *pQryFilter, int32 requestId = 0);
    /* 查询股票持仓信息 */
    int32               QueryStkHolding(const OesQryStkHoldingFilterT *pQryFilter, int32 requestId = 0);
    /* 查询新股配号、中签信息 */
    int32               QueryLotWinning(const OesQryLotWinningFilterT *pQryFilter, int32 requestId = 0);
    /* 查询客户信息 */
    int32               QueryCustInfo(const OesQryCustFilterT *pQryFilter, int32 requestId = 0);
    /* 查询证券账户信息 */
    int32               QueryInvAcct(const OesQryInvAcctFilterT *pQryFilter, int32 requestId = 0);
    /* 查询佣金信息 */
    int32               QueryCommissionRate(const OesQryCommissionRateFilterT *pQryFilter, int32 requestId = 0);
    /* 查询出入金流水 */
    int32               QueryFundTransferSerial(const OesQryFundTransferSerialFilterT *pQryFilter, int32 requestId = 0);
    /* 查询证券发行产品信息 */
    int32               QueryIssue(const OesQryIssueFilterT *pQryFilter, int32 requestId = 0);
    /* 查询现货产品信息 */
    int32               QueryStock(const OesQryStockFilterT *pQryFilter, int32 requestId = 0);
    /* 查询ETF申赎产品信息 */
    int32               QueryEtf(const OesQryEtfFilterT *pQryFilter, int32 requestId = 0);
    /* 查询ETF成份证券信息 */
    int32               QueryEtfComponent(const OesQryEtfComponentFilterT *pQryFilter, int32 requestId = 0);
    /* 查询市场状态信息 */
    int32               QueryMarketState(const OesQryMarketStateFilterT *pQryFilter, int32 requestId = 0);
    /* 查询主柜资金信息 */
    int32               QueryCounterCash(const char *pCashAcctId, OesCounterCashItemT *pCounterCashItem, int32 requestId = 0);
    /* 查询期权产品信息 (适用于期权业务) */
    int32               QueryOption(const OesQryOptionFilterT *pQryFilter, int32 requestId = 0);
    /* 查询期权持仓信息 (适用于期权业务) */
    int32               QueryOptHolding(const OesQryOptHoldingFilterT *pQryFilter, int32 requestId = 0);
    /* 查询期权标的持仓 (适用于期权业务) */
    int32               QueryOptUnderlyingHolding(const OesQryOptUnderlyingHoldingFilterT *pQryFilter, int32 requestId = 0);
    /* 查询期权限仓额度 (适用于期权业务) */
    int32               QueryOptPositionLimit(const OesQryOptPositionLimitFilterT *pQryFilter, int32 requestId = 0);
    /* 查询期权限购额度 (适用于期权业务) */
    int32               QueryOptPurchaseLimit(const OesQryOptPurchaseLimitFilterT *pQryFilter, int32 requestId = 0);
    /* 查询期权行权指派信息 (适用于期权业务) */
    int32               QueryOptExerciseAssign(const OesQryOptExerciseAssignFilterT *pQryFilter, int32 requestId = 0);
    /* 查询期权结算单信息 (适用于期权业务) */
    int32               QueryOptSettlementStatement(const char *pCustId, char *pSettleBuf, int32 bufSize, int32 requestId = 0);
    /* 查询通知消息 */
    int32               QueryNotifyInfo(const OesQryNotifyInfoFilterT *pQryFilter, int32 requestId = 0);

private:
    /* 禁止拷贝构造函数 */
    OesClientApi(const OesClientApi&);
    /* 禁止赋值函数 */
    OesClientApi&       operator=(const OesClientApi&);

public:
    /* 为了方便客户端使用而内置的流水号计数器, 可以基于该字段来递增维护客户端委托流水号 */
    int32               defaultClSeqNo;

protected:
    OesApiClientCfgT    _apiCfg;
    OesApiSessionInfoT  _qryChannel;
    BOOL                _isInitialized;
    BOOL                _isRunning;

    OesClientSpi        *_pSpi;
    OesAsyncApiContextT *_pAsyncContext;
    OesAsyncApiChannelT *_pDefaultOrdChannel;
    OesAsyncApiChannelT *_pDefaultRptChannel;
    OesApiSessionInfoT  *_pQryChannel;
};


}


#endif /* _OES_CPP_API_SAMPLE_H */
