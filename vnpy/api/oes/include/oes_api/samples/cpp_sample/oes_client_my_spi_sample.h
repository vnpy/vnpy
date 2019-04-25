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
 * @file    oes_client_my_spi_sample.h
 *
 * OES API接口库的CPP风格客户端示例。客户需要实现自己的SPI定义
 *
 * @version 1.0 2017/08/24
 * @since   2017/08/24
 */

#ifndef _OES_CLIENT_MY_SPI_SAMPLE_H
#define _OES_CLIENT_MY_SPI_SAMPLE_H


#include    "oes_client_sample.h"


class   OesClientMySpi: public Quant360::OesClientSpi {
public:
    /* 委托拒绝回报 */
    virtual void        OnBusinessReject(int32 errorCode, const OesOrdRejectT *pOrderReject);
    /* 委托已收回报 */
    virtual void        OnOrderInsert(const OesOrdCnfmT *pOrderInsert);
    /* 委托确认回报 */
    virtual void        OnOrderReport(int32 errorCode, const OesOrdCnfmT *pOrderReport);
    /* 成交确认回报 */
    virtual void        OnTradeReport(const OesTrdCnfmT *pTradeReport);
    /* 资金变动回报 */
    virtual void        OnCashAssetVariation(const OesCashAssetItemT *pCashAssetItem);
    /* 持仓变动回报 */
    virtual void        OnStockHoldingVariation(const OesStkHoldingItemT *pStkHoldingItem);
    /* 出入金委托拒绝回报 */
    virtual void        OnFundTrsfReject(int32 errorCode, const OesFundTrsfRejectT *pFundTrsfReject);
    /* 出入金委托执行回报 */
    virtual void        OnFundTrsfReport(int32 errorCode, const OesFundTrsfReportT *pFundTrsfReport);
    /* 市场状态信息回报 */
    virtual void        OnMarketState(const OesMarketStateItemT *pMarketStateItem);

    /* 查询委托信息回调 */
    virtual void        OnQueryOrder(const OesOrdItemT *pOrder, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询成交信息回调 */
    virtual void        OnQueryTrade(const OesTrdItemT *pTrade, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询资金信息回调 */
    virtual void        OnQueryCashAsset(const OesCashAssetItemT *pCashAsset, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询持仓信息回调 */
    virtual void        OnQueryStkHolding(const OesStkHoldingItemT *pStkHolding, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询配号、中签信息回调 */
    virtual void        OnQueryLotWinning(const OesLotWinningItemT *pLotWinning, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询客户信息回调 */
    virtual void        OnQueryCustInfo(const OesCustItemT *pCust, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询股东账户信息回调 */
    virtual void        OnQueryInvAcct(const OesInvAcctItemT *pInvAcct, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询佣金信息回调 */
    virtual void        OnQueryCommissionRate(const OesCommissionRateItemT *pCommissionRate, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询出入金流水信息回调 */
    virtual void        OnQueryFundTransferSerial(const OesFundTransferSerialItemT *pFundTrsf, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询证券发行信息回调 */
    virtual void        OnQueryIssue(const OesIssueItemT *pIssue, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询证券信息回调 */
    virtual void        OnQueryStock(const OesStockItemT *pStock, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询ETF产品信息回调 */
    virtual void        OnQueryEtf(const OesEtfItemT *pEtf, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询ETF成分股信息回调 */
    virtual void        OnQueryEtfComponent(const OesEtfComponentItemT *pEtfComponent, const OesQryCursorT *pCursor, int32 requestId);
    /* 查询市场状态信息回调 */
    virtual void        OnQueryMarketState(const OesMarketStateItemT *pMarketState, const OesQryCursorT *pCursor, int32 requestId);

public:
    OesClientMySpi(int32 something = 0);
    virtual ~OesClientMySpi();

private:
    int32               something;
};


#endif /* _OES_CLIENT_MY_SPI_SAMPLE_H */
