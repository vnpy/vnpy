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
 * @file    oes_client_sample.c
 *
 * OES API接口库的示例程序
 *
 * @version 1.0 2016/10/21
 * @since   2016/10/21
 */


#include    <oes_api/oes_api.h>
#include    <sutil/logger/spk_log.h>


/**
 * 发送委托请求
 *
 * 提示:
 * - 可以通过 OesApi_GetClEnvId() 方法获得到当前通道所使用的客户端环境号(clEnvId), 如:
 *   <code>int8 clEnvId = OesApi_GetClEnvId(pOrdChannel);</code>
 *
 * @param   pOrdChannel     委托通道的会话信息
 * @param   mktId           市场代码 (必填) @see eOesMarketIdT
 * @param   pSecurityId     股票代码 (必填)
 * @param   pInvAcctId      股东账户代码 (可不填)
 * @param   ordType         委托类型 (必填) @see eOesOrdTypeT, eOesOrdTypeShT, eOesOrdTypeSzT
 * @param   bsType          买卖类型 (必填) @see eOesBuySellTypeT
 * @param   ordQty          委托数量 (必填, 单位为股/张)
 * @param   ordPrice        委托价格 (必填, 单位精确到元后四位, 即1元 = 10000)
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_SendOrderReq(OesApiSessionInfoT *pOrdChannel,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        uint8 ordType, uint8 bsType, int32 ordQty, int32 ordPrice) {
    OesOrdReqT          ordReq = {NULLOBJ_OES_ORD_REQ};

    SLOG_ASSERT2(pOrdChannel
            && mktId > 0 && mktId < __OES_MKT_ID_MAX
            && pSecurityId && ordType < __OES_ORD_TYPE_FOK_MAX
            && bsType > 0 && bsType < __OES_BS_TYPE_MAX_TRADING
            && ordQty > 0 && ordPrice >= 0,
            "pOrdChannel[%p], mktId[%" __SPK_FMT_HH__ "u], " \
            "pSecurityId[%s], ordType[%" __SPK_FMT_HH__ "u], " \
            "bsType[%" __SPK_FMT_HH__ "u], ordQty[%d], ordPrice[%d]",
            pOrdChannel, mktId, pSecurityId ? pSecurityId : "NULL",
            ordType, bsType, ordQty, ordPrice);

    ordReq.clSeqNo = (int32) ++pOrdChannel->lastOutMsgSeq;
    ordReq.mktId = mktId;
    ordReq.ordType = ordType;
    ordReq.bsType = bsType;

    strncpy(ordReq.securityId, pSecurityId, sizeof(ordReq.securityId) - 1);
    if (pInvAcctId) {
        /* 股东账户可不填 */
        strncpy(ordReq.invAcctId, pInvAcctId, sizeof(ordReq.invAcctId) - 1);
    }

    ordReq.ordQty = ordQty;
    ordReq.ordPrice = ordPrice;

    return OesApi_SendOrderReq(pOrdChannel, &ordReq);
}


/**
 * 发送撤单请求
 *
 * @param   pOrdChannel     委托通道的会话信息
 * @param   mktId           被撤委托的市场代码 (必填) @see eOesMarketIdT
 * @param   pSecurityId     被撤委托的股票代码 (选填, 若不为空则校验待撤订单是否匹配)
 * @param   pInvAcctId      被撤委托的股东账户代码 (选填, 若不为空则校验待撤订单是否匹配)
 * @param   origClSeqNo     被撤委托的流水号 (若使用 origClOrdId, 则不必填充该字段)
 * @param   origClEnvId     被撤委托的客户端环境号 (小于等于0, 则使用当前会话的 clEnvId)
 * @param   origClOrdId     被撤委托的客户订单编号 (若使用 origClSeqNo, 则不必填充该字段)
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_SendOrderCancelReq(OesApiSessionInfoT *pOrdChannel,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        int32 origClSeqNo, int8 origClEnvId, int64 origClOrdId) {
    OesOrdCancelReqT    cancelReq = {NULLOBJ_OES_ORD_CANCEL_REQ};

    SLOG_ASSERT2(pOrdChannel && mktId > 0 && mktId < __OES_MKT_ID_MAX,
            "pOrdChannel[%p], mktId[%" __SPK_FMT_HH__ "u]",
            pOrdChannel, mktId);

    cancelReq.clSeqNo = (int32) ++pOrdChannel->lastOutMsgSeq;
    cancelReq.mktId = mktId;

    if (pSecurityId) {
        /* 撤单时被撤委托的股票代码可不填 */
        strncpy(cancelReq.securityId, pSecurityId,
                sizeof(cancelReq.securityId) - 1);
    }

    if (pInvAcctId) {
        /* 撤单时被撤委托的股东账户可不填 */
        strncpy(cancelReq.invAcctId, pInvAcctId,
                sizeof(cancelReq.invAcctId) - 1);
    }

    cancelReq.origClSeqNo = origClSeqNo;
    cancelReq.origClEnvId = origClEnvId;
    cancelReq.origClOrdId = origClOrdId;

    return OesApi_SendOrderCancelReq(pOrdChannel, &cancelReq);
}


/**
 * 查询客户端总览信息
 *
 * @param   pSessionInfo    会话信息
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static int32
_OesApiSample_QueryClientOverview(OesApiSessionInfoT *pSessionInfo) {
    OesClientOverviewT  clientOverview = {NULLOBJ_OES_CLIENT_OVERVIEW};
    int32               ret = 0;
    int32               i = 0;

    ret = OesApi_GetClientOverview(pSessionInfo, &clientOverview);
    if (__spk_unlikely(ret < 0)) {
        SLOG_ERROR("Query client overview failure! ret[%d]", ret);
        return ret;
    } else {
        SLOG_DEBUG("Query client overview success! ");
    }

    printf(">>> Client Overview: {clientId[%d], " \
            "clientType[%" __SPK_FMT_HH__ "u], " \
            "clientStatus[%" __SPK_FMT_HH__ "u], " \
            "clientName[%s], businessScope[%" __SPK_FMT_HH__ "u], " \
            "sseStkPbuId[%d], szseStkPbuId[%d], ordTrafficLimit[%d], " \
            "qryTrafficLimit[%d], associatedCustCnt[%d]}\n",
            clientOverview.clientId, clientOverview.clientType,
            clientOverview.clientStatus, clientOverview.clientName,
            clientOverview.businessScope, clientOverview.sseStkPbuId,
            clientOverview.szseStkPbuId, clientOverview.ordTrafficLimit,
            clientOverview.qryTrafficLimit, clientOverview.associatedCustCnt);

    for (i = 0; i < clientOverview.associatedCustCnt; i++) {
        printf("    >>> Cust Overview: {custId[%s], " \
                "status[%" __SPK_FMT_HH__ "u], " \
                "riskLevel[%" __SPK_FMT_HH__ "u], branchId[%d], " \
                "custName[%s]}\n",
                clientOverview.custItems[i].custId,
                clientOverview.custItems[i].status,
                clientOverview.custItems[i].riskLevel,
                clientOverview.custItems[i].branchId,
                clientOverview.custItems[i].custName);

        if (clientOverview.custItems[i].spotCashAcct.isValid) {
            printf("        >>> CashAcct Overview: {cashAcctId[%s], " \
                    "cashType[%" __SPK_FMT_HH__ "u], " \
                    "cashAcctStatus[%" __SPK_FMT_HH__ "u], " \
                    "isFundTrsfDisabled[%" __SPK_FMT_HH__ "u]}\n",
                    clientOverview.custItems[i].spotCashAcct.cashAcctId,
                    clientOverview.custItems[i].spotCashAcct.cashType,
                    clientOverview.custItems[i].spotCashAcct.cashAcctStatus,
                    clientOverview.custItems[i].spotCashAcct.isFundTrsfDisabled);
        }

        if (clientOverview.custItems[i].shSpotInvAcct.isValid) {
            printf("        >>> InvAcct  Overview: {invAcctId[%s], " \
                    "mktId[%" __SPK_FMT_HH__ "u], " \
                    "status[%" __SPK_FMT_HH__ "u], " \
                    "isTradeDisabled[%" __SPK_FMT_HH__ "u], " \
                    "pbuId[%d], trdOrdCnt[%d], " \
                    "nonTrdOrdCnt[%d], cancelOrdCnt[%d], " \
                    "oesRejectOrdCnt[%d], exchRejectOrdCnt[%d], trdCnt[%d]}\n",
                    clientOverview.custItems[i].shSpotInvAcct.invAcctId,
                    clientOverview.custItems[i].shSpotInvAcct.mktId,
                    clientOverview.custItems[i].shSpotInvAcct.status,
                    clientOverview.custItems[i].shSpotInvAcct.isTradeDisabled,
                    clientOverview.custItems[i].shSpotInvAcct.pbuId,
                    clientOverview.custItems[i].shSpotInvAcct.trdOrdCnt,
                    clientOverview.custItems[i].shSpotInvAcct.nonTrdOrdCnt,
                    clientOverview.custItems[i].shSpotInvAcct.cancelOrdCnt,
                    clientOverview.custItems[i].shSpotInvAcct.oesRejectOrdCnt,
                    clientOverview.custItems[i].shSpotInvAcct.exchRejectOrdCnt,
                    clientOverview.custItems[i].shSpotInvAcct.trdCnt);
        }

        if (clientOverview.custItems[i].szSpotInvAcct.isValid) {
            printf("        >>> InvAcct  Overview: {invAcctId[%s], " \
                    "mktId[%" __SPK_FMT_HH__ "u], " \
                    "status[%" __SPK_FMT_HH__ "u], " \
                    "isTradeDisabled[%" __SPK_FMT_HH__ "u], " \
                    "pbuId[%d], trdOrdCnt[%d], " \
                    "nonTrdOrdCnt[%d], cancelOrdCnt[%d], " \
                    "oesRejectOrdCnt[%d], exchRejectOrdCnt[%d], trdCnt[%d]}\n",
                    clientOverview.custItems[i].szSpotInvAcct.invAcctId,
                    clientOverview.custItems[i].szSpotInvAcct.mktId,
                    clientOverview.custItems[i].szSpotInvAcct.status,
                    clientOverview.custItems[i].szSpotInvAcct.isTradeDisabled,
                    clientOverview.custItems[i].szSpotInvAcct.pbuId,
                    clientOverview.custItems[i].szSpotInvAcct.trdOrdCnt,
                    clientOverview.custItems[i].szSpotInvAcct.nonTrdOrdCnt,
                    clientOverview.custItems[i].szSpotInvAcct.cancelOrdCnt,
                    clientOverview.custItems[i].szSpotInvAcct.oesRejectOrdCnt,
                    clientOverview.custItems[i].szSpotInvAcct.exchRejectOrdCnt,
                    clientOverview.custItems[i].szSpotInvAcct.trdCnt);
        }
    }

    return 0;
}


/**
 * 对现货产品查询返回的产品信息进行处理的回调函数
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据 @see OesStockItemT
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static int32
_OesApiSample_OnQryStockCallback(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    OesStockItemT       *pStockItem = (OesStockItemT *) pMsgBody;

    printf(">>> Recv QryStockRsp: {index[%d], isEnd[%c], " \
            "securityId[%s], securityName[%s], mktId[%" __SPK_FMT_HH__ "u], "
            "securityType[%" __SPK_FMT_HH__ "u], " \
            "subSecurityType[%" __SPK_FMT_HH__ "u], " \
            "isDayTrading[%" __SPK_FMT_HH__ "u], " \
            "suspFlag[%" __SPK_FMT_HH__ "u], " \
            "temporarySuspFlag[%" __SPK_FMT_HH__ "u], " \
            "bondInterest[%" __SPK_FMT_LL__ "d], " \
            "buyQtyUnit[%d], sellQtyUnit[%d], priceUnit[%d], "
            "prevClose[%d], ceilPrice[%d], floorPrice[%d]}\n",
            pQryCursor->seqNo, pQryCursor->isEnd ? 'Y' : 'N',
            pStockItem->securityId, pStockItem->securityName,
            pStockItem->mktId,
            pStockItem->securityType, pStockItem->subSecurityType,
            pStockItem->isDayTrading, pStockItem->suspFlag,
            pStockItem->temporarySuspFlag,
            pStockItem->bondInterest,
            pStockItem->buyQtyUnit, pStockItem->sellQtyUnit,
            pStockItem->priceUnit, pStockItem->prevClose,
            pStockItem->priceLimit[OES_TRD_SESS_TYPE_T].ceilPrice,
            pStockItem->priceLimit[OES_TRD_SESS_TYPE_T].floorPrice);

    return 0;
}


/**
 * 查询现货产品信息
 *
 * @param   pQryChannel     查询通道的会话信息
 * @param   pSecurityId     产品代码
 * @param   mktId           市场代码
 * @param   securityType    证券类别
 * @param   subSecurityType 证券子类别
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_QueryStock(OesApiSessionInfoT *pQryChannel,
        const char *pSecurityId, uint8 mktId, uint8 securityType,
        uint8 subSecurityType) {
    OesQryStockFilterT  qryFilter = {NULLOBJ_OES_QRY_STOCK_FILTER};
    int32               ret = 0;

    SLOG_ASSERT(pQryChannel);

    if (pSecurityId) {
        strncpy(qryFilter.securityId, pSecurityId,
                sizeof(qryFilter.securityId) - 1);
    }

    qryFilter.mktId = mktId;
    qryFilter.securityType = securityType;
    qryFilter.subSecurityType = subSecurityType;

    ret = OesApi_QueryStock(pQryChannel, &qryFilter,
            _OesApiSample_OnQryStockCallback, NULL);
    if (__spk_unlikely(ret < 0)) {
        SLOG_ERROR("Query stock failure! ret[%d], pSecurityId[%s], " \
                "mktId[%" __SPK_FMT_HH__ "u], " \
                "securityType[%" __SPK_FMT_HH__ "u], " \
                "subSecurityType[%" __SPK_FMT_HH__ "u]",
                ret, pSecurityId ? pSecurityId : "NULL", mktId,
                securityType, subSecurityType);
        return ret;
    } else {
        SLOG_DEBUG("Query stock success! total count: [%d]", ret);
    }

    return 0;
}


/**
 * 对资金查询返回的资金信息进行处理的回调函数
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据 @see OesCashAssetItemT
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static int32
_OesApiSample_OnQryCashAssetCallback(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    OesCashAssetItemT   *pCashAssetItem = (OesCashAssetItemT *) pMsgBody;

    printf(">>> Recv QryCashRsp: {index[%d], isEnd[%c], " \
            "cashAcctId[%s], custId[%s], " \
            "cashType[%" __SPK_FMT_HH__ "u], " \
            "beginningBal[%" __SPK_FMT_LL__ "d], " \
            "beginningAvailableBal[%" __SPK_FMT_LL__ "d], " \
            "beginningDrawableBal[%" __SPK_FMT_LL__ "d], " \
            "disableBal[%" __SPK_FMT_LL__ "d], " \
            "totalDepositAmt[%" __SPK_FMT_LL__ "d], " \
            "totalWithdrawAmt[%" __SPK_FMT_LL__ "d], " \
            "withdrawFrzAmt[%" __SPK_FMT_LL__ "d], " \
            "totalSellAmt[%" __SPK_FMT_LL__ "d], " \
            "totalBuyAmt[%" __SPK_FMT_LL__ "d], " \
            "buyFrzAmt[%" __SPK_FMT_LL__ "d], " \
            "totalFeeAmt[%" __SPK_FMT_LL__ "d], " \
            "feeFrzAmt[%" __SPK_FMT_LL__ "d], " \
            "marginAmt[%" __SPK_FMT_LL__ "d], " \
            "marginFrzAmt[%" __SPK_FMT_LL__ "d], " \
            "currentTotalBal[%" __SPK_FMT_LL__ "d], " \
            "currentAvailableBal[%" __SPK_FMT_LL__ "d], " \
            "currentDrawableBal[%" __SPK_FMT_LL__ "d]}\n",
            pQryCursor->seqNo, pQryCursor->isEnd ? 'Y' : 'N',
            pCashAssetItem->cashAcctId, pCashAssetItem->custId,
            pCashAssetItem->cashType, pCashAssetItem->beginningBal,
            pCashAssetItem->beginningAvailableBal,
            pCashAssetItem->beginningDrawableBal,
            pCashAssetItem->disableBal, pCashAssetItem->totalDepositAmt,
            pCashAssetItem->totalWithdrawAmt, pCashAssetItem->withdrawFrzAmt,
            pCashAssetItem->totalSellAmt, pCashAssetItem->totalBuyAmt,
            pCashAssetItem->buyFrzAmt, pCashAssetItem->totalFeeAmt,
            pCashAssetItem->feeFrzAmt,
            pCashAssetItem->marginAmt, pCashAssetItem->marginFrzAmt,
            pCashAssetItem->currentTotalBal,
            pCashAssetItem->currentAvailableBal,
            pCashAssetItem->currentDrawableBal);

    return 0;
}


/**
 * 查询资金
 *
 * @param   pQryChannel     查询通道的会话信息
 * @param   pCashAcctId     资金账户代码
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_QueryCashAsset(OesApiSessionInfoT *pQryChannel,
        const char *pCashAcctId) {
    OesQryCashAssetFilterT
                        qryFilter = {NULLOBJ_OES_QRY_CASH_ASSET_FILTER};
    int32               ret = 0;

    SLOG_ASSERT(pQryChannel);

    if (pCashAcctId) {
        strncpy(qryFilter.cashAcctId, pCashAcctId,
                sizeof(qryFilter.cashAcctId) - 1);
    }

    ret = OesApi_QueryCashAsset(pQryChannel, &qryFilter,
            _OesApiSample_OnQryCashAssetCallback, NULL);
    if (__spk_unlikely(ret < 0)) {
        SLOG_ERROR("Query cash asset failure! " \
                "ret[%d], pCashAcctId[%s]",
                ret, pCashAcctId ? pCashAcctId : "NULL");
        return ret;
    } else {
        SLOG_DEBUG("Query cash asset success! total count: [%d]", ret);
    }

    return 0;
}


/**
 * 对股票持仓查询返回的持仓信息进行处理的回调函数
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据 @see OesStkHoldingItemT
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static int32
_OesApiSample_OnQryStkHoldingCallback(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    OesStkHoldingItemT  *pHoldingItem = (OesStkHoldingItemT *) pMsgBody;

    printf(">>> Recv QryStkHoldingRsp: {index[%d], isEnd[%c], " \
            "invAcctId[%s], securityId[%s], mktId[%" __SPK_FMT_HH__ "u], " \
            "sellAvlHld[%" __SPK_FMT_LL__ "d]}\n",
            pQryCursor->seqNo, pQryCursor->isEnd ? 'Y' : 'N',
            pHoldingItem->invAcctId, pHoldingItem->securityId,
            pHoldingItem->mktId, pHoldingItem->sellAvlHld);

    return 0;
}


/**
 * 查询股票持仓
 *
 * @param   pQryChannel     查询通道的会话信息
 * @param   mktId           市场代码 @see eOesMarketIdT
 * @param   pSecurityId     股票代码 (char[6]/char[8])
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_QueryStkHolding(OesApiSessionInfoT *pQryChannel,
        uint8 mktId, const char *pSecurityId) {
    OesQryStkHoldingFilterT
                        qryFilter = {NULLOBJ_OES_QRY_STK_HOLDING_FILTER};
    int32               ret = 0;

    SLOG_ASSERT2(pQryChannel && mktId < __OES_MKT_ID_MAX,
            "pOrdChannel[%p], mktId[%" __SPK_FMT_HH__ "u]",
            pQryChannel, mktId);

    qryFilter.mktId = mktId;
    if (pSecurityId) {
        strncpy(qryFilter.securityId, pSecurityId,
                sizeof(qryFilter.securityId) - 1);
    }

    ret = OesApi_QueryStkHolding(pQryChannel, &qryFilter,
            _OesApiSample_OnQryStkHoldingCallback, NULL);
    if (__spk_unlikely(ret < 0)) {
        SLOG_ERROR("Query stock holding failure! " \
                "ret[%d], mktId[%" __SPK_FMT_HH__ "u], pSecurityId[%s]",
                ret, mktId, pSecurityId ? pSecurityId : "NULL");
        return ret;
    } else {
        SLOG_DEBUG("Query stock holding success! total count: [%d]", ret);
    }

    return 0;
}


/**
 * 对市场状态查询返回的市场状态信息进行处理的回调函数
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据 @see OesMarketStateItemT
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static int32
_OesApiSample_OnQryMarketStateCallback(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    OesMarketStateItemT   *pMktStateItem = (OesMarketStateItemT *) pMsgBody;

    printf(">>> Recv QryMktStatusRsp: {index[%d], isEnd[%c], "
            "exchId[%" __SPK_FMT_HH__ "u], platformId[%" __SPK_FMT_HH__ "u], " \
            "mktId[%" __SPK_FMT_HH__ "u], mktState[%" __SPK_FMT_HH__ "u]}\n",
            pQryCursor->seqNo, pQryCursor->isEnd ? 'Y' : 'N',
            pMktStateItem->exchId, pMktStateItem->platformId,
            pMktStateItem->mktId, pMktStateItem->mktState);

    return 0;
}


/**
 * 查询市场状态
 *
 * @param   pQryChannel     查询通道的会话信息
 * @param   exchId          交易所代码 @see eOesExchangeIdT
 * @param   platformId      交易平台类型 @see eOesPlatformIdT
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_QueryMarketStatus(OesApiSessionInfoT *pQryChannel,
        uint8 exchId, uint8 platformId) {
    OesQryMarketStateFilterT
                        qryFilter = {NULLOBJ_OES_QRY_MARKET_STATE_FILTER};
    int32               ret = 0;

    SLOG_ASSERT2(pQryChannel
            && exchId < __MAX_OES_EXCH && platformId < __OES_PLATFORM_ID_MAX,
            "pOrdChannel[%p], exchId[%" __SPK_FMT_HH__ "u], " \
            "platformId[%" __SPK_FMT_HH__ "u]",
            pQryChannel, exchId, platformId);

    qryFilter.exchId = exchId;
    qryFilter.platformId = platformId;

    ret = OesApi_QueryMarketState(pQryChannel, &qryFilter,
            _OesApiSample_OnQryMarketStateCallback, NULL);
    if (__spk_unlikely(ret < 0)) {
        SLOG_ERROR("Query market state failure! " \
                "ret[%d], exchId[%" __SPK_FMT_HH__ "u], " \
                "platformId[%" __SPK_FMT_HH__ "u]",
                ret, exchId, platformId);
        return ret;
    } else {
        SLOG_DEBUG("Query market state success! total count: [%d]", ret);
    }

    return 0;
}


/**
 * 对执行报告消息进行处理的回调函数
 *
 * @param   pRptChannel     回报通道的会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0, 成功；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_HandleReportMsg(OesApiSessionInfoT *pRptChannel,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    OesRspMsgBodyT      *pRspMsg = (OesRspMsgBodyT *) pMsgBody;
    OesRptMsgT          *pRptMsg = &pRspMsg->rptMsg;

    assert(pRptChannel && pMsgHead && pRspMsg);

    switch (pMsgHead->msgId) {
    case OESMSG_RPT_ORDER_INSERT:               /* OES委托已生成 (已通过风控检查) @see OesOrdCnfmT */
        printf(">>> Recv OrdInsertRsp: {clSeqNo: %d, " \
                "clOrdId: %" __SPK_FMT_LL__ "d}\n",
                pRptMsg->rptBody.ordInsertRsp.clSeqNo,
                pRptMsg->rptBody.ordInsertRsp.clOrdId);
        break;

    case OESMSG_RPT_BUSINESS_REJECT:            /* OES业务拒绝 (未通过风控检查等) @see OesOrdRejectT */
        printf(">>> Recv OrdRejectRsp: {clSeqNo: %d, ordRejReason: %d}\n",
                pRptMsg->rptBody.ordRejectRsp.clSeqNo,
                pRptMsg->rptHead.ordRejReason);
        break;

    case OESMSG_RPT_ORDER_REPORT:               /* 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知) @see OesOrdCnfmT */
        printf(">>> Recv OrdCnfm: {clSeqNo: %d, " \
                "clOrdId: %" __SPK_FMT_LL__ "d}\n",
                pRptMsg->rptBody.ordCnfm.clSeqNo,
                pRptMsg->rptBody.ordCnfm.clOrdId);
        break;

    case OESMSG_RPT_TRADE_REPORT:               /* 交易所成交回报 @see OesTrdCnfmT */
        printf(">>> Recv TrdCnfm: {clSeqNo: %d, " \
                "clOrdId: %" __SPK_FMT_LL__ "d}\n",
                pRptMsg->rptBody.trdCnfm.clSeqNo,
                pRptMsg->rptBody.trdCnfm.clOrdId);

        /* @note 成交回报中已经包含了委托回报的相关信息, 可以通过辅助接口直接从成交回报中提取和生成委托回报数据
        if (pRptMsg->rptBody.trdCnfm.ordStatus == OES_ORD_STATUS_FILLED) {
            OesOrdCnfmT ordReport = {NULLOBJ_OES_ORD_CNFM};
            OesHelper_ExtractOrdReportFromTrd(
                    &pRptMsg->rptBody.trdCnfm, &ordReport);
        }
        */
        break;

    case OESMSG_RPT_CASH_ASSET_VARIATION:       /* 资金变动信息 @see OesCashAssetItemT */
        printf(">>> Recv CashAsset: {cashAcctId: %s, " \
                "currentAvailableBal: %" __SPK_FMT_LL__ "d}\n",
                pRptMsg->rptBody.cashAssetRpt.cashAcctId,
                pRptMsg->rptBody.cashAssetRpt.currentAvailableBal);
        break;

    case OESMSG_RPT_STOCK_HOLDING_VARIATION:    /* 持仓变动信息 (股票) @see OesStkHoldingItemT */
        printf(">>> Recv StkHolding: {invAcctId: %s, securityId: %s, " \
                "mktId: %" __SPK_FMT_HH__ "u, " \
                "sellAvlHld: %" __SPK_FMT_LL__ "d}\n",
                pRptMsg->rptBody.stkHoldingRpt.invAcctId,
                pRptMsg->rptBody.stkHoldingRpt.securityId,
                pRptMsg->rptBody.stkHoldingRpt.mktId,
                pRptMsg->rptBody.stkHoldingRpt.sellAvlHld);
        break;

    case OESMSG_RPT_FUND_TRSF_REJECT:           /* 出入金委托响应-业务拒绝 @see OesFundTrsfRejectT */
        printf(">>> Recv FundTrsfReject: {cashAcctId: %s, rejReason: %d}\n",
                pRptMsg->rptBody.fundTrsfRejectRsp.cashAcctId,
                pRptMsg->rptBody.fundTrsfRejectRsp.rejReason);
        break;

    case OESMSG_RPT_FUND_TRSF_REPORT:           /* 出入金委托执行报告 @see OesFundTrsfReportT */
        printf(">>> Recv FundTrsfReport: {cashAcctId: %s, " \
                "trsfStatus: %" __SPK_FMT_HH__ "u}\n",
                pRptMsg->rptBody.fundTrsfCnfm.cashAcctId,
                pRptMsg->rptBody.fundTrsfCnfm.trsfStatus);
        break;

    case OESMSG_RPT_REPORT_SYNCHRONIZATION:     /* 回报同步响应 @see OesReportSynchronizationRspT */
        printf(">>> Recv report synchronization: " \
                "{subscribeEnvId: %" __SPK_FMT_HH__ "d, " \
                "subscribeRptTypes: %d, " \
                "lastRptSeqNum: %" __SPK_FMT_LL__ "d}\n",
                pRspMsg->reportSynchronizationRsp.subscribeEnvId,
                pRspMsg->reportSynchronizationRsp.subscribeRptTypes,
                pRspMsg->reportSynchronizationRsp.lastRptSeqNum);
        break;

    case OESMSG_RPT_MARKET_STATE:               /* 市场状态信息 @see OesMarketStateInfoT */
        printf(">>> Recv MktStatusReport: " \
                "{exchId: %" __SPK_FMT_HH__ "u, " \
                "platformId: %" __SPK_FMT_HH__ "u, " \
                "mktId: %" __SPK_FMT_HH__ "u, " \
                "mktState: %" __SPK_FMT_HH__ "u}\n",
                pRspMsg->mktStateRpt.exchId,
                pRspMsg->mktStateRpt.platformId,
                pRspMsg->mktStateRpt.mktId,
                pRspMsg->mktStateRpt.mktState);
        break;

    case OESMSG_SESS_HEARTBEAT:
        printf(">>> Recv heartbeat message.\n");
        break;

    case OESMSG_SESS_TEST_REQUEST:
        printf(">>> Recv test-request response message.\n");
        break;

    default:
        fprintf(stderr, "Invalid message type! msgId[0x%02X]\n",
                pMsgHead->msgId);
        break;
    }

    return 0;
}


/**
 * 超时检查处理
 *
 * @param   pRptChannel     回报通道的会话信息
 * @return  等于0, 运行正常, 未超时；大于0, 已超时, 需要重建连接；小于0, 失败（错误号）
 */
static inline int32
_OesApiSample_OnTimeout(OesApiClientEnvT *pClientEnv) {
    OesApiSessionInfoT  *pRptChannel = &pClientEnv->rptChannel;
    int64               recvInterval = 0;

    if (pRptChannel->heartBtInt > 0) {
        recvInterval = time((time_t *) NULL) -
                OesApi_GetLastRecvTime(pRptChannel);
        if (recvInterval > pRptChannel->heartBtInt * 2) {
            SLOG_ERROR("会话已超时, 将主动断开与服务器[%s:%d]的连接! " \
                    "lastRecvTime: [%" __SPK_FMT_LL__ "d], " \
                    "lastSendTime: [%" __SPK_FMT_LL__ "d], " \
                    "heartBtInt: [%d], recvInterval: [%" __SPK_FMT_LL__ "d]",
                    pRptChannel->channel.remoteAddr,
                    pRptChannel->channel.remotePort,
                    (int64) pRptChannel->lastRecvTime.tv_sec,
                    (int64) pRptChannel->lastSendTime.tv_sec,
                    pRptChannel->heartBtInt, recvInterval);
            return ETIMEDOUT;
        }
    }

    return 0;
}


/**
 * 回报采集处理 (可以做为线程的主函数运行)
 *
 * @param   pRptChannel     回报通道的会话信息
 * @return  TRUE 处理成功; FALSE 处理失败
 */
void*
OesApiSample_ReportThreadMain(OesApiClientEnvT *pClientEnv) {
    static const int32  THE_TIMEOUT_MS = 1000;

    OesApiSessionInfoT  *pRptChannel = &pClientEnv->rptChannel;
    volatile int32      *pThreadTerminatedFlag = &pRptChannel->__customFlag;
    int32               ret = 0;

    while (! *pThreadTerminatedFlag) {
        /* 等待回报消息到达, 并通过回调函数对消息进行处理 */
        ret = OesApi_WaitReportMsg(pRptChannel, THE_TIMEOUT_MS,
                _OesApiSample_HandleReportMsg, NULL);
        if (__spk_unlikely(ret < 0)) {
            if (__spk_likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 执行超时检查 (检查会话是否已超时) */
                if (__spk_likely(_OesApiSample_OnTimeout(pClientEnv) == 0)) {
                    continue;
                }

                /* 会话已超时 */
                goto ON_ERROR;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 连接已断开 */
            }
            goto ON_ERROR;
        }
    }

    *pThreadTerminatedFlag = -1;
    return (void *) TRUE;

ON_ERROR:
    *pThreadTerminatedFlag = -1;
    return (void *) FALSE;
}


/**
 * API接口库示例程序的主函数
 */
int32
OesApiSample_Main() {
    static const char   THE_CONFIG_FILE_NAME[] = "oes_client_sample.conf";
    OesApiClientEnvT    cliEnv = {NULLOBJ_OESAPI_CLIENT_ENV};

    /* 因为样例代码会将信息输出到控制台, 所以此处先关闭标准输出缓存 */
    setvbuf(stdout, (char *) NULL, _IONBF, 0);

    /*
     * 1. 设置 线程私有变量 以及 自定义参数信息
     *  - 可设置的线程私有变量包括: 登录用户名、登录密码、客户端环境号以及订阅回报使用的客户端环境号
     *      - 登录时会优先使用设置的线程变量值替换配置文件中的配置信息
     *  - 自定义信息包括: IP地址、MAC地址、设备序列号
     *      - IP和MAC地址在登录时会尝试自动获取, 自动获取失败时会使用自设置
     *      - 设备序列号目前不会从自动获取, 需要主动设置以防止券商控制导致的登录失败, 同时满足监管需求
     */
    {
        /* 设置当前线程使用的登录用户名 */
        // OesApi_SetThreadUsername("customer1");

        /*
         * 设置当前线程使用的登录密码
         * @note 如通过API接口设置, 则可以不在配置文件中配置;
         *  - 支持通过前缀指定密码类型, 如 md5:PASSWORD, txt:PASSWORD
         */
        // OesApi_SetThreadPassword("txt:123456");
        // OesApi_SetThreadPassword("md5:e10adc3949ba59abbe56e057f20f883e");

        /* 设置客户端本地的设备序列号 */
        OesApi_SetCustomizedDriverId("ABCDEFGHIJKLMN");
    }

    /*
     * 2. 初始化客户端环境
     *  - 一次性初始化多个通道时, 可通过如下接口完成初始化:
     *      - OesApi_InitAll
     *      - OesApi_InitAllByConvention
     *      - OesApi_InitAllByCfgStruct
     *  - 对单个通道进行初始化时, 可通过如下接口完成初始化:
     *      - OesApi_InitOrdChannel / OesApi_InitOrdChannel2
     *      - OesApi_InitRptChannel / OesApi_InitRptChannel2
     *      - OesApi_InitQryChannel / OesApi_InitQryChannel2
     */
    {
        /* 初始化客户端环境 (配置文件参见: oes_client_sample.conf) */
        if (! OesApi_InitAll(&cliEnv, THE_CONFIG_FILE_NAME,
                OESAPI_CFG_DEFAULT_SECTION_LOGGER, OESAPI_CFG_DEFAULT_SECTION,
                OESAPI_CFG_DEFAULT_KEY_ORD_ADDR, OESAPI_CFG_DEFAULT_KEY_RPT_ADDR,
                OESAPI_CFG_DEFAULT_KEY_QRY_ADDR, 0, (int32 *) NULL)) {
            return -1;
        }
    }

    /* 3. 创建回报接收进程 */
#if ! (defined (__WINDOWS__) || defined (__MINGW__))
    {
        pthread_t       rptThreadId;
        int32           ret = 0;

        ret = pthread_create(&rptThreadId, NULL,
                (void* (*)(void *)) OesApiSample_ReportThreadMain,
                &cliEnv);
        if (ret != 0) {
            SLOG_ERROR("创建回报接收线程失败! error[%d]", ret);
            goto ON_ERROR;
        }
    }
#else
    {
        HANDLE          rptThreadId;

        /* 创建回报接收线程 */
        rptThreadId = CreateThread(NULL, 0,
                (LPTHREAD_START_ROUTINE) OesApiSample_ReportThreadMain,
                (LPVOID) &cliEnv, 0, NULL);
        if (rptThreadId == NULL) {
            SLOG_ERROR("创建回报接收线程失败! error[%lu]", GetLastError());
            goto ON_ERROR;
        }
    }
#endif

    /*
     * 4. 查询接口使用样例
     *  - 查询接口分为单条查询和批量查询两类
     *      - 单条查询直接返回查询结果(返回值标识查询是否成功)
     *      - 批量查询以回调方式返回查询结果(返回值除标识是否成功外, 还代表查询到的总条数)
     *          - 查询到的总条数为0时不会触发回调
     */
    {
        /* 查询 深交所-现货集中竞价平台 市场状态 */
        _OesApiSample_QueryMarketStatus(&cliEnv.qryChannel, OES_EXCH_SZSE,
                OES_PLATFORM_CASH_AUCTION);

        /* 查询 客户端总览信息 */
        _OesApiSample_QueryClientOverview(&cliEnv.qryChannel);

        /* 查询 所有关联资金账户的资金信息 */
        _OesApiSample_QueryCashAsset(&cliEnv.qryChannel, NULL);

        /* 查询 指定资金账户的资金信息 */
        /* _OesApiSample_QueryCashAsset(&cliEnv.qryChannel, "指定资金账户"); */

        /* 查询 指定上证 600000 的产品信息 */
        _OesApiSample_QueryStock(&cliEnv.qryChannel, "600000",
                OES_MKT_ID_UNDEFINE, OES_SECURITY_TYPE_UNDEFINE,
                OES_SUB_SECURITY_TYPE_UNDEFINE);

        /* 查询 上海A股市场 的产品信息 */
        /* _OesApiSample_QueryStock(&cliEnv.qryChannel, NULL,
                OES_MKT_SH_ASHARE, OES_SECURITY_TYPE_UNDEFINE,
                OES_SUB_SECURITY_TYPE_UNDEFINE); */

        /* 查询 上证 600000 股票的持仓 */
        _OesApiSample_QueryStkHolding(&cliEnv.qryChannel, OES_MKT_SH_ASHARE,
                "600000");

        /* 查询 上证 所有股票持仓 */
        _OesApiSample_QueryStkHolding(&cliEnv.qryChannel, OES_MKT_SH_ASHARE,
                NULL);

        /* 查询 沪深两市 所有股票持仓 */
        _OesApiSample_QueryStkHolding(&cliEnv.qryChannel, OES_MKT_ID_UNDEFINE,
                NULL);
    }

    /*
     * 5. 委托接口使用样例
     *  - 委托接口分为单笔委托申报和批量委托申报
     *  - 委托申报为单向异步方式发送, 申报处理结果将通过回报数据返回
     */
    {
        /*
         * 上海A股市场的买卖
         *  - 以 12.67元 购买 浦发银行(600000) 100股
         */
        _OesApiSample_SendOrderReq(&cliEnv.ordChannel, OES_MKT_SH_ASHARE,
                "600000", NULL, OES_ORD_TYPE_LMT, OES_BS_TYPE_BUY,
                100, 126700);

        /*
         * 深圳A股市场的买卖
         *  - 以 市价 卖出 平安银行(000001) 200股
         */
        _OesApiSample_SendOrderReq(&cliEnv.ordChannel, OES_MKT_SZ_ASHARE,
                "000001", NULL, OES_ORD_TYPE_SZ_MTL_BEST, OES_BS_TYPE_SELL,
                200, 0);

        /*
         * 上海市场的逆回购交易
         *  - 以 1.235 的报价做 10万元 GC001(204001)逆回购
         *      - 逆回购每张标准券100元, 委托份数填 (10万元 除以 100元/张 =) 1000张
         *      - 上证逆回购报价单位是0.005, 份数单位是1000张
         */
        _OesApiSample_SendOrderReq(&cliEnv.ordChannel, OES_MKT_SH_ASHARE,
                "204001", NULL, OES_ORD_TYPE_LMT, OES_BS_TYPE_CREDIT_SELL,
                1000, 12350);

        /*
         * 深圳市场的逆回购交易
         *  - 以 4.321 的报价做 1千元 R-001(131810)逆回购
         *      - 逆回购每张标准券100元, 委托份数填 (1千元 除以 100元/张 =) 10张
         *      - 深证逆回购报价单位是0.001, 份数单位是10张
         */
        _OesApiSample_SendOrderReq(&cliEnv.ordChannel, OES_MKT_SZ_ASHARE,
                "131810", NULL, OES_ORD_TYPE_LMT, OES_BS_TYPE_CREDIT_SELL,
                10, 43210);

        /*
         * 深圳市场的新股认购
         *  - 认购 迈为股份(300751) 500股
         *  - 新股申购额度通过 查询股东账户信息(OesApi_QueryInvAcct)接口 返回信息中的
         *      OesInvAcctItemT.subscriptionQuota 来获取
         */
        _OesApiSample_SendOrderReq(&cliEnv.ordChannel, OES_MKT_SZ_ASHARE,
                "300751", NULL, OES_ORD_TYPE_LMT, OES_BS_TYPE_SUBSCRIPTION,
                500, 0);

        /*
         * 深圳市场的配股认购
         *  - 以 发行价 认购 万顺配债(380057) 500股
         */
        _OesApiSample_SendOrderReq(&cliEnv.ordChannel, OES_MKT_SZ_ASHARE,
                "380057", NULL, OES_ORD_TYPE_LMT, OES_BS_TYPE_ALLOTMENT,
                500, 0);
    }

    /*
     * 6. 撤单接口使用样例
     *  - 可以通过指定"待撤订单的客户订单编号(origClOrdId)"予以撤单
     *  - 可以通过指定"待撤订单的客户委托流水号(origClSeqNo)"予以撤单
     *      - 需结合"待撤订单的客户端环境号(origClEnvId)", 不指定时使用当前会话的clEnvId
     *  - 如下交易类型不支持撤单:
     *      - 上海/深圳市场的新股申购委托
     *      - 上海市场的配股申购委托
     */
    {
        /* 定义 origOrder 作为模拟的待撤委托 */
        OesOrdCnfmT     origOrder = {NULLOBJ_OES_ORD_CNFM};
        origOrder.mktId = OES_MKT_SH_ASHARE;
        origOrder.clEnvId = 0;
        origOrder.clSeqNo = 11;
        origOrder.clOrdId = 111;            /* 真实场景中, 待撤委托的clOrdId需要通过回报消息获取 */

        /* 通过待撤委托的 clOrdId 进行撤单 */
        _OesApiSample_SendOrderCancelReq(&cliEnv.ordChannel,
                origOrder.mktId, NULL, NULL, 0, 0, origOrder.clOrdId);

        /* 通过待撤委托的 clSeqNo 进行撤单 */
        _OesApiSample_SendOrderCancelReq(&cliEnv.ordChannel,
                origOrder.mktId, NULL, NULL,
                origOrder.clSeqNo, origOrder.clEnvId, 0);
    }

    /* 7. 通知并等待回报线程退出 (实际场景中请勿参考此部分代码) */
    {
        /* 等待回报消息接收完成 */
        SPK_SLEEP_MS(1000);

        /* 设置回报线程退出标志 */
        *((volatile int32 *) &cliEnv.rptChannel.__customFlag) = 1;

        /* 回报线程将标志设置为-1后退出, 父进程再释放资源 */
        while(*((volatile int32 *) &cliEnv.rptChannel.__customFlag) != -1) {
            SPK_SLEEP_MS(1000);
        }
    }

    /* 8. 发送注销消息, 并释放会话数据 */
    fprintf(stdout, "\n运行结束, 即将退出...\n\n");

    OesApi_LogoutAll(&cliEnv, TRUE);
    return 0;

ON_ERROR:
    /* 直接关闭连接, 并释放会话数据 */
    OesApi_DestoryAll(&cliEnv);
    return -1;
}

int
main(int argc, char *argv[]) {
    return OesApiSample_Main();
}
