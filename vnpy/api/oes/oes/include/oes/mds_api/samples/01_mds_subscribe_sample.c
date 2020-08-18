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
 * @file    01_mds_subscribe_sample.c
 *
 * MDS-API 行情订阅接口的示例程序
 *
 * 示例程序概述:
 * - 通过 SubscribeByString 接口订阅行情
 *
 * @version 0.12.5      2017/02/20
 * @since   2017/02/20
 */


#include    <mds_api/mds_api.h>
#include    <mds_api/parser/mds_protocol_parser.h>
#include    <mds_api/parser/json_parser/mds_json_parser.h>
#include    <sutil/logger/spk_log.h>


/**
 * 通过证券代码列表, 重新订阅行情数据 (根据代码前缀区分所属市场)
 *
 * @param   pTcpChannel         会话信息
 * @param   pCodeListString     证券代码列表字符串 (以空格或逗号/分号/竖线分割的字符串)
 * @return  TRUE 成功; FALSE 失败
 */
static BOOL
MdsApiSample_ResubscribeByCodePrefix(MdsApiSessionInfoT *pTcpChannel,
        const char *pCodeListString) {
    /* 上海证券代码前缀 */
    static const char       SSE_CODE_PREFIXES[] = \
            "009, 01, 02, "                 /* 国债 */ \
            "10, 11, 12, 13, 18, 19, "      /* 债券 (企业债、可转债等) */ \
            "20, "                          /* 债券 (回购) */ \
            "5, "                           /* 基金 */ \
            "6, "                           /* A股 */ \
            "#000";                         /* 指数 (@note 与深圳股票代码重合) */

    /* 深圳证券代码前缀 */
    static const char       SZSE_CODE_PREFIXES[] = \
            "00, "                          /* 股票 */ \
            "10, 11, 12, 13, "              /* 债券 */ \
            "15, 16, 17, 18, "              /* 基金 */ \
            "30, "                          /* 创业板 */ \
            "39";                           /* 指数 */

    /* 设置SubscribeByString接口使用的数据模式 (tickType=1) */
    MdsApi_SetThreadSubscribeTickType(MDS_TICK_TYPE_LATEST_TIMELY);

    /* 设置SubscribeByString接口使用的逐笔数据的数据重建标识 (实时行情+重建数据) */
    MdsApi_SetThreadSubscribeTickRebuildFlag(
            MDS_TICK_REBUILD_FLAG_INCLUDE_REBUILDED);

    /* 设置SubscribeByString接口使用的初始快照订阅标志 (isRequireInitialMktData) */
    MdsApi_SetThreadSubscribeRequireInitMd(FALSE);

    /* 根据证券代码列表订阅行情, 并通过证券代码前缀来区分和识别所属市场 */
    return MdsApi_SubscribeByStringAndPrefixes(pTcpChannel,
            pCodeListString, (char *) NULL,
            SSE_CODE_PREFIXES, SZSE_CODE_PREFIXES,
            MDS_MD_PRODUCT_TYPE_STOCK, MDS_SUB_MODE_SET,
            MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
                    | MDS_SUB_DATA_TYPE_L2_ORDER
                    | MDS_SUB_DATA_TYPE_L2_TRADE);
}


/**
 * 通过证券代码列表, 重新订阅行情数据 (根据代码后缀区分所属市场, 如果没有指定后缀, 则默认为上证股票)
 *
 * @param   pTcpChannel         会话信息
 * @param   pCodeListString     证券代码列表字符串 (以空格或逗号/分号/竖线分割的字符串)
 * @return  TRUE 成功; FALSE 失败
 */
static BOOL
MdsApiSample_ResubscribeByCodePostfix(MdsApiSessionInfoT *pTcpChannel,
        const char *pCodeListString) {
    /* 设置SubscribeByString接口使用的数据模式 (tickType=1) */
    MdsApi_SetThreadSubscribeTickType(MDS_TICK_TYPE_LATEST_TIMELY);

    /* 设置SubscribeByString接口使用的逐笔数据的数据重建标识 (实时行情+重建数据) */
    MdsApi_SetThreadSubscribeTickRebuildFlag(
            MDS_TICK_REBUILD_FLAG_INCLUDE_REBUILDED);

    /* 设置SubscribeByString接口使用的初始快照订阅标志 (isRequireInitialMktData) */
    MdsApi_SetThreadSubscribeRequireInitMd(FALSE);

    /* 根据证券代码列表订阅行情 */
    return MdsApi_SubscribeByString(pTcpChannel,
            pCodeListString, (char *) NULL,
            MDS_EXCH_SSE, MDS_MD_PRODUCT_TYPE_STOCK, MDS_SUB_MODE_SET,
            MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
                    | MDS_SUB_DATA_TYPE_L2_ORDER
                    | MDS_SUB_DATA_TYPE_L2_TRADE);
}


/**
 * 进行消息处理的回调函数
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0, 成功; 小于0, 失败 (错误号)
 */
static int32
MdsApiSample_HandleMsg(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    MdsMktRspMsgBodyT   *pRspMsg = (MdsMktRspMsgBodyT *) pMsgBody;

    /* 根据消息类型对行情消息进行处理 */
    switch (pMsgHead->msgId) {
    case MDS_MSGTYPE_L2_TRADE:
        /* 处理Level2逐笔成交消息 @see MdsL2TradeT */
        printf("... 接收到Level2逐笔成交消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->trade.exchId,
                pRspMsg->trade.SecurityID);
        break;

    case MDS_MSGTYPE_L2_ORDER:
        /* 处理Level2逐笔委托消息 @see MdsL2OrderT */
        printf("... 接收到Level2逐笔委托消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->order.exchId,
                pRspMsg->order.SecurityID);
        break;

    case MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT:
        /* 处理Level2快照行情消息 @see MdsL2StockSnapshotBodyT */
        printf("... 接收到Level2快照行情消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.l2Stock.SecurityID);
        break;

    case MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT:
        /* 处理Level2委托队列消息(买一／卖一前五十笔委托明细) @see MdsL2BestOrdersSnapshotBodyT */
        printf("... 接收到Level2委托队列快照行情消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.l2BestOrders.SecurityID);
        break;

    case MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL:
        /* 处理(上证)Level2快照行情的增量更新消息 @see MdsL2StockSnapshotIncrementalT */
        printf("... 接收到(上证)Level2快照行情的增量更新消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], instrId[%06d])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.head.instrId);
        break;

    case MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL:
        /* 处理(上证)Level2委托队列的增量更新消息 @see MdsL2BestOrdersSnapshotIncrementalT */
        printf("... 接收到(上证)Level2委托队列快照行情的增量更新消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], instrId[%06d])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.head.instrId);
        break;

    case MDS_MSGTYPE_L2_MARKET_OVERVIEW:
        /* 处理(上证)Level2市场总览消息 @see MdsL2MarketOverviewT */
        printf("... 接收到(上证)Level2市场总览消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], OrigDate[%d], OrigTime[%09d])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.l2MarketOverview.OrigDate,
                pRspMsg->mktDataSnapshot.l2MarketOverview.OrigTime);
        break;

    case MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH:
        /* 处理Level1快照行情消息 @see MdsStockSnapshotBodyT */
        printf("... 接收到Level1快照行情消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.stock.SecurityID);
        break;

    case MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH:
        /* 处理期权快照行情消息 @see MdsStockSnapshotBodyT */
        printf("... 接收到期权快照行情消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.option.SecurityID);
        break;

    case MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH:
        /* 处理指数行情消息 @see MdsIndexSnapshotBodyT */
        printf("... 接收到指数快照行情消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.index.SecurityID);
        break;

    case MDS_MSGTYPE_SECURITY_STATUS:
        /* 处理(深圳)证券状态消息 @see MdsSecurityStatusMsgT */
        printf("... 接收到(深圳)证券状态消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], SecurityID[%s])\n",
                pRspMsg->securityStatus.exchId,
                pRspMsg->securityStatus.SecurityID);
        break;

    case MDS_MSGTYPE_TRADING_SESSION_STATUS:
        /* 处理(上证)市场状态消息 @see MdsTradingSessionStatusMsgT */
        printf("... 接收到(上证)市场状态消息 (" \
                "exchId[%" __SPK_FMT_HH__ "u], TradingSessionID[%s])\n",
                pRspMsg->trdSessionStatus.exchId,
                pRspMsg->trdSessionStatus.TradingSessionID);
        break;

    case MDS_MSGTYPE_MARKET_DATA_REQUEST:
        /* 处理行情订阅请求的应答消息 @see MdsMktDataRequestRspT */
        if (pMsgHead->status == 0) {
            printf("... 接收到行情订阅请求应答, 行情订阅成功! " \
                    "实际已订阅的证券代码数量: " \
                    "sseStock[%d], sseIndex[%d], sseOption[%d], " \
                    "szseStock[%d], szseIndex[%d], szseOption[%d]\n",
                    pRspMsg->mktDataRequestRsp.sseStockSubscribed,
                    pRspMsg->mktDataRequestRsp.sseIndexSubscribed,
                    pRspMsg->mktDataRequestRsp.sseOptionSubscribed,
                    pRspMsg->mktDataRequestRsp.szseStockSubscribed,
                    pRspMsg->mktDataRequestRsp.szseIndexSubscribed,
                    pRspMsg->mktDataRequestRsp.szseOptionSubscribed);
        } else {
            printf("... 接收到行情订阅请求应答, 行情订阅失败! " \
                    "errCode[%02" __SPK_FMT_HH__ "u%02" __SPK_FMT_HH__ "u]\n",
                    pMsgHead->status, pMsgHead->detailStatus);
        }
        break;

    case MDS_MSGTYPE_TEST_REQUEST:
        /* 处理测试请求的应答消息 @see MdsTestRequestRspT */
        printf("... 接收到测试请求的应答消息 (origSendTime[%s], respTime[%s])\n",
                pRspMsg->testRequestRsp.origSendTime,
                pRspMsg->testRequestRsp.respTime);
        break;

    case MDS_MSGTYPE_HEARTBEAT:
        /* 直接忽略心跳消息即可 */
        printf("... 接收到心跳消息\n");
        break;

    default:
        SLOG_ERROR("无效的消息类型, 忽略之! msgId[0x%02X], server[%s:%d]",
                pMsgHead->msgId, pSessionInfo->channel.remoteAddr,
                pSessionInfo->channel.remotePort);
        return EFTYPE;
    }

    return 0;
}


int
main(int argc, char *argv[]) {
    /* 配置文件名称 */
    static const char   THE_CONFIG_FILE_NAME[] = "mds_client_sample.conf";
    /* 尝试等待行情消息到达的超时时间 (毫秒) */
    static const int32  THE_TIMEOUT_MS = 1000;

    MdsApiClientEnvT    cliEnv = {NULLOBJ_MDSAPI_CLIENT_ENV};
    int32               ret = 0;

    /* 初始化客户端环境 (配置文件参见: mds_client_sample.conf) */
    if (! MdsApi_InitAllByConvention(&cliEnv, THE_CONFIG_FILE_NAME)) {
        return -1;
    }

    /*
     * 将以下的订阅操作禁用掉, 则会保留初始化时的默认订阅 (使用配置文件中的订阅参数)
     * 默认通过 if (0) 禁用了订阅操作, 可以修改为 if (1) 来启用相应的订阅操作
     */
    if (0) {
        /* 根据证券代码列表重新订阅行情 (根据代码前缀区分所属市场) */
        if (! MdsApiSample_ResubscribeByCodePrefix(&cliEnv.tcpChannel,
                "600000, 600001, 000001, 0000002.SZ")) {
            goto ON_ERROR;
        }
    } else if (0) {
        /* 根据证券代码列表重新订阅行情 (根据代码后缀区分所属市场) */
        if (! MdsApiSample_ResubscribeByCodePostfix(&cliEnv.tcpChannel,
                "600000.SH, 600001.SH, 000001.SZ, 0000002.SZ")) {
            goto ON_ERROR;
        }
    }

    while (1) {
        /* 等待行情消息到达, 并通过回调函数对消息进行处理 */
        ret = MdsApi_WaitOnMsg(&cliEnv.tcpChannel, THE_TIMEOUT_MS,
                MdsApiSample_HandleMsg, NULL);
        if (__spk_unlikely(ret < 0)) {
            if (__spk_likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 执行超时检查 (检查会话是否已超时) */
                continue;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 连接已断开 */
            }
            goto ON_ERROR;
        }
    }

    /* 关闭客户端环境, 释放会话数据 */
    MdsApi_LogoutAll(&cliEnv, TRUE);
    return 0;

ON_ERROR:
    /* 直接断开与服务器的连接并释放会话数据 */
    MdsApi_DestoryAll(&cliEnv);
    return -1;
}
