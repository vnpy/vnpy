/*
 * Copyright 2009-2014 the original author or authors.
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
 * @file    oes_query_json_parser.h
 *
 * 查询消息解析
 *
 * @version $Id$
 * @since   2014/12/26
 */


#ifndef _OES_QUERY_JSON_PARSER_H
#define _OES_QUERY_JSON_PARSER_H


#include    <oes_global/oes_packets.h>
#include    <sutil/net/spk_global_packet.h>
#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 函数声明
 * =================================================================== */

/* 查询服务接收到的请求消息解析处理 */
OesQryReqMsgT *
        OesJsonParser_DecodeQueryReq(
                SMsgHeadT *pReqHead,
                const char *pMsgBody,
                OesQryReqMsgT *pQryReq,
                const char *pRemoteInfo);

/* 查询服务构造应答消息处理 */
void *  OesJsonParser_EncodeQueryRsp(
                SMsgHeadT *pRspHead,
                const OesQryRspMsgT *pQryRsp,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);
/* -------------------------           */


/* ===================================================================
 * 用于具体数据条目编/解码处理的函数声明
 * =================================================================== */

/* 编码查询应答条目 */
void*   OesJsonParser_EncodeQueryRspItem(
                SMsgHeadT *pRspHead,
                const void *pQryRspItem,
                char *pBuf,
                int32 bufSize);

/* 客户端总览信息序列化 */
int32 JsonParser_EncodeClientOverview(
                const OesClientOverviewT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条委托查询结果序列化 */
int32   JsonParser_EncodeOrdItem(
                const OesOrdItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条成交查询结果序列化 */
int32   JsonParser_EncodeTrdItem(
                const OesTrdItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条资金查询结果序列化 */
int32   JsonParser_EncodeCashAssetItem(
                const OesCashAssetItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条股东帐户信息查询结果序列化 */
int32   JsonParser_EncodeInvAcctItem(
                const OesInvAcctItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条佣金信息查询结果序列化 */
int32   JsonParser_EncodeCommissionRateItem(
                const OesCommissionRateItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条出入金流水查询结果序列化 */
int32   JsonParser_EncodeFundTransferSerialItem(
                const OesFundTransferSerialItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 股票持仓查询编码单条回报处理 */
int32   JsonParser_EncodeStkHoldingItem(
                const OesStkHoldingItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权持仓查询编码单条回报处理 */
int32   JsonParser_EncodeOptHoldingItem(
                const OesOptHoldingItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权持仓查询编码单条回报处理 */
int32   JsonParser_EncodeLotWinningItem(
                const OesLotWinningItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条证券发行信息查询结果序列化 */
int32   JsonParser_EncodeIssueItem(
                const OesIssueItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条股票产品信息查询结果序列化 */
int32   JsonParser_EncodeStockItem(
                const OesStockItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 客户信息查询编码单条回报处理 */
int32   JsonParser_EncodeCustItem(
                const OesCustItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条ETF产品信息查询结果序列化 */
int32   JsonParser_EncodeEtfItem(
                const OesEtfItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条ETF成份证券信息查询结果序列化 */
int32   JsonParser_EncodeEtfComponentItem(
                const OesEtfComponentItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条期权产品信息查询结果序列化 */
int32   JsonParser_EncodeOptionItem(
                const OesOptionItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条市场状态信息查询结果序列化 */
int32   JsonParser_EncodeMktStatusItem(
                const OesMarketStateItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条通知消息查询结果序列化 */
int32   JsonParser_EncodeNotifyInfoItem(
                const OesNotifyInfoItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 单条主柜资金查询结果序列化 */
int32   JsonParser_EncodeCounterCashItem(
                const OesCounterCashItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权标的锁定查询编码单条回报处理 */
int32   JsonParser_EncodeOptUnderlyingHoldingItem(
                const OesOptUnderlyingHoldingItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权限仓额度查询编码单条回报处理 */
int32   JsonParser_EncodeOptPositionLimitItem(
                const OesOptPositionLimitItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权限购额度信息查询编码单条回报处理 */
int32   JsonParser_EncodeOptPurchaseLimitItem(
                const OesOptPurchaseLimitItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权行权指派查询编码单条回报处理 */
int32   JsonParser_EncodeOptExerciseAssignItem(
                const OesOptExerciseAssignItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权结算单基础信息查询 */
int32   JsonParser_EncodeOptSettlBaseInfo(
                const void *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期权结算单持仓信息查询 */
int32   JsonParser_EncodeOptSettlPosition(
                const void *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 券商参数查询结果序列化 */
int32   JsonParser_EncodeBrokerParams(
                const OesBrokerParamsInfoT *pRspItem,
                char *pBuf, int32 bufSize);

/* 周边应用升级配置信息查询结果序列化 */
int32   JsonParser_EncodeApplUpgradeInfo(
                const OesApplUpgradeInfoT *pUpgradeInfo,
                char *pBuf, int32 bufSize);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_QUERY_JSON_PARSER_H */
