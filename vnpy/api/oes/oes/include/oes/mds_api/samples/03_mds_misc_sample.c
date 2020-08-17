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
 * @file    03_mds_misc_sample.c
 *
 * MDS API接口库的示例程序
 *
 * 示例程序概述:
 * - 创建TCP行情接收线程, 并在该线程下接收和处理行情消息 (@see MdsApiSample_TcpThreadMain)
 * - 创建查询线程, 并在该线程下循环查询行情快照 (@see MdsApiSample_QueryThreadMain)
 * - 创建创建UDP行情组播接收线程, 并在该线程下接收和处理行情消息 (@see MdsApiSample_UdpThreadMain)
 * - 通过通道组同时对接多个UDP行情组播通道 (@see MdsApiSample_CustomizedUdpThreadMain)
 * - 在主线程中循环发送行情订阅请求 (纯粹为了演示行情订阅接口的使用)
 *
 * 该示例程序的内容有些杂而凌乱, 建议先通过 01_mds_subscribe_sample.c、
 * 02_mds_async_api_sample.c 这两个示例程序着手了解API的使用模式
 *
 * @version 0.10.3      2016/07/26
 * @since   2016/07/26
 */


#include    <mds_api/mds_api.h>
#include    <mds_api/parser/mds_protocol_parser.h>
#include    <mds_api/parser/json_parser/mds_json_parser.h>
#include    <sutil/time/spk_times.h>
#include    <sutil/logger/spk_log.h>


/* ===================================================================
 * 行情消息处理的示例代码
 * =================================================================== */

/**
 * 将行情消息转换为JSON格式的文本, 并打印到指定的输出文件
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @param   pOutputFp       输出文件的文件句柄
 * @return  等于0, 成功; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_PrintMsg(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, FILE *pOutputFp) {
    char                encodeBuf[8192] = {0};
    char                *pStrMsg = (char *) NULL;

    if (pSessionInfo->protocolType == SMSG_PROTO_BINARY) {
        /* 将行情消息转换为JSON格式的文本数据 */
        pStrMsg = (char *) MdsJsonParser_EncodeRsp(
                pMsgHead, (MdsMktRspMsgBodyT *) pMsgBody,
                encodeBuf, sizeof(encodeBuf),
                pSessionInfo->channel.remoteAddr);
        if (__spk_unlikely(! pStrMsg)) {
            SLOG_ERROR("编码接收到的行情消息失败! "
                    "msgFlag: %" __SPK_FMT_HH__ "u, " \
                    "msgType: %" __SPK_FMT_HH__ "u, msgSize: %d",
                    pMsgHead->msgFlag, pMsgHead->msgId, pMsgHead->msgSize);
            return SPK_NEG(EBADMSG);
        }
    } else {
        pStrMsg = (char *) pMsgBody;
    }

    if (pMsgHead->msgSize > 0) {
        pStrMsg[pMsgHead->msgSize - 1] = '\0';
        fprintf(pOutputFp,
                "{" \
                "\"msgType\":%" __SPK_FMT_HH__ "u, " \
                "\"mktData\":%s" \
                "}\n",
                pMsgHead->msgId,
                pStrMsg);
    } else {
        fprintf(pOutputFp,
                "{" \
                "\"msgType\":%" __SPK_FMT_HH__ "u, " \
                "\"mktData\":{}" \
                "}\n",
                pMsgHead->msgId);
    }

    return 0;
}


/**
 * 证券行情全幅消息处理
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @return  大于等于0, 成功; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_OnSnapshotFullRefresh(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, MdsMktDataSnapshotT *pRspBody) {
    //TODO 证券行情全幅消息处理

    /* 打印行情消息到控制台 */
    return _MdsApiSample_PrintMsg(pSessionInfo, pMsgHead, pRspBody, stdout);
}


/**
 * Level2逐笔成交消息处理
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @return  大于等于0, 成功; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_OnL2Trade(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, MdsL2TradeT *pRspBody) {
    //TODO Level2逐笔成交消息处理

    /* 打印行情消息到控制台 */
    return _MdsApiSample_PrintMsg(pSessionInfo, pMsgHead, pRspBody, stdout);
}


/**
 * Level2逐笔委托消息处理
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @return  大于等于0, 成功; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_OnL2Order(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, MdsL2OrderT *pRspBody) {
    //TODO Level2逐笔委托消息处理

    /* 打印行情消息到控制台 */
    return _MdsApiSample_PrintMsg(pSessionInfo, pMsgHead, pRspBody, stdout);
}


/**
 * (上证)市场状态消息处理
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @return  大于等于0, 成功; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_OnTradingSessionStatus(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, MdsTradingSessionStatusMsgT *pRspBody) {
    //TODO (上证)市场状态消息处理

    /* 打印行情消息到控制台 */
    return _MdsApiSample_PrintMsg(pSessionInfo, pMsgHead, pRspBody, stdout);
}


/**
 * (深圳)证券状态消息处理
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @return  大于等于0, 成功; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_OnSecurityStatus(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, MdsSecurityStatusMsgT *pRspBody) {
    //TODO (深圳)证券状态消息处理

    /* 打印行情消息到控制台 */
    return _MdsApiSample_PrintMsg(pSessionInfo, pMsgHead, pRspBody, stdout);
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
static inline int32
_MdsApiSample_HandleMsg(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    MdsMktRspMsgBodyT   *pRspMsg = (MdsMktRspMsgBodyT *) pMsgBody;

    /*
     * 根据消息类型对行情消息进行处理
     */
    switch (pMsgHead->msgId) {
    case MDS_MSGTYPE_L2_TRADE:
        /* 处理Level2逐笔成交消息 */
        return _MdsApiSample_OnL2Trade(
                pSessionInfo, pMsgHead, &pRspMsg->trade);

    case MDS_MSGTYPE_L2_ORDER:
        /* 处理Level2逐笔委托消息 */
        return _MdsApiSample_OnL2Order(
                pSessionInfo, pMsgHead, &pRspMsg->order);

    case MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT:
    case MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT:
    case MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL:
    case MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL:
    case MDS_MSGTYPE_L2_MARKET_OVERVIEW:
    case MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH:
    case MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH:
    case MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH:
        /* 处理证券行情全幅消息 */
        return _MdsApiSample_OnSnapshotFullRefresh(
                pSessionInfo, pMsgHead, &pRspMsg->mktDataSnapshot);

    case MDS_MSGTYPE_SECURITY_STATUS:
        /* 处理(深圳)证券状态消息 */
        return _MdsApiSample_OnSecurityStatus(
                pSessionInfo, pMsgHead, &pRspMsg->securityStatus);

    case MDS_MSGTYPE_TRADING_SESSION_STATUS:
        /* 处理(上证)市场状态消息 */
        return _MdsApiSample_OnTradingSessionStatus(
                pSessionInfo, pMsgHead, &pRspMsg->trdSessionStatus);

    case MDS_MSGTYPE_MARKET_DATA_REQUEST:
        /* 处理行情订阅请求的应答消息 */
        return _MdsApiSample_PrintMsg(pSessionInfo, pMsgHead,
                &pRspMsg->mktDataRequestRsp, stdout);

    case MDS_MSGTYPE_TEST_REQUEST:
        /* 处理测试请求的应答消息 */
        return _MdsApiSample_PrintMsg(pSessionInfo, pMsgHead,
                &pRspMsg->testRequestRsp, stdout);

    case MDS_MSGTYPE_HEARTBEAT:
        /* 直接忽略心跳消息即可 */
        break;

    default:
        SLOG_ERROR("无效的消息类型, 忽略之! msgId[0x%02X], server[%s:%d]",
                pMsgHead->msgId, pSessionInfo->channel.remoteAddr,
                pSessionInfo->channel.remotePort);
        return EFTYPE;
    }

    return 0;
}


/**
 * 超时检查处理
 *
 * @param   pSessionInfo    会话信息
 * @return  等于0, 运行正常, 未超时; 大于0, 已超时, 需要重建连接; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_OnTimeout(MdsApiSessionInfoT *pSessionInfo) {
    /*
    int64               recvInterval = 0;

    SLOG_ASSERT(pSessionInfo);

    recvInterval = STime_GetSysTime() - MdsApi_GetLastRecvTime(pSessionInfo);
    if (__spk_unlikely(pSessionInfo->heartBtInt > 0
            && recvInterval > pSessionInfo->heartBtInt * 2)) {
        SLOG_ERROR("会话已超时, 将主动断开与服务器[%s:%d]的连接! " \
                "lastRecvTime[%lld], lastSendTime[%lld], " \
                "heartBtInt[%d], recvInterval[%lld]",
                pSessionInfo->channel.remoteAddr,
                pSessionInfo->channel.remotePort,
                MdsApi_GetLastRecvTime(pSessionInfo),
                MdsApi_GetLastSendTime(pSessionInfo),
                pSessionInfo->heartBtInt, recvInterval);
        return ETIMEDOUT;
    }
    */
    return 0;
}


/* ===================================================================
 * 行情接收处理(TCP/UDP)的示例代码
 * =================================================================== */

/**
 * TCP行情接收处理 (可以做为线程的主函数运行)
 *
 * @param   pTcpChannel     TCP行情订阅通道的会话信息
 * @return  TRUE 处理成功; FALSE 处理失败
 */
void*
MdsApiSample_TcpThreadMain(MdsApiSessionInfoT *pTcpChannel) {
    static const int32  THE_TIMEOUT_MS = 5000;
    int32               ret = 0;

    SLOG_ASSERT(pTcpChannel);

    while (1) {
        /* 等待行情消息到达, 并通过回调函数对消息进行处理 */
        ret = MdsApi_WaitOnMsg(pTcpChannel, THE_TIMEOUT_MS,
                _MdsApiSample_HandleMsg, NULL);
        if (__spk_unlikely(ret < 0)) {
            if (__spk_likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 执行超时检查 (检查会话是否已超时) */
                if (__spk_likely(_MdsApiSample_OnTimeout(pTcpChannel) == 0)) {
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

    return (void *) TRUE;

ON_ERROR:
    return (void *) FALSE;
}


/**
 * UDP行情组播接收处理 (可以同时接收多个信道的行情组播, 可以做为线程的主函数运行)
 *
 * @param   pUdpChannelGroup    通道组信息
 * @return  TRUE 处理成功; FALSE 处理失败
 */
void*
MdsApiSample_UdpThreadMain(MdsApiChannelGroupT *pUdpChannelGroup) {
    static const int32  THE_TIMEOUT_MS = 5000;
    int32               ret = 0;

    SLOG_ASSERT(pUdpChannelGroup);

    while (1) {
        /* 等待行情消息到达, 并通过回调函数对消息进行处理 */
        ret = MdsApi_WaitOnUdpChannelGroup(pUdpChannelGroup, THE_TIMEOUT_MS,
                _MdsApiSample_HandleMsg, NULL,
                (SGeneralClientChannelT **) NULL);
        if (__spk_unlikely(ret < 0)) {
            if (__spk_likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 已超时 (在超时时间内没有接收到任何网络消息) */
                continue;
            }

            /* 网络操作或回调函数返回错误 */
            goto ON_ERROR;
        }
    }

    return (void *) TRUE;

ON_ERROR:
    return (void *) FALSE;
}


/**
 * 定制的UDP行情组播接收处理 (显式的处理和接收多个信道的行情组播, 可以做为线程的主函数运行)
 *
 * @param   pNone   没有用处的参数, 为了兼容线程接口而设
 * @return  TRUE 处理成功; FALSE 处理失败
 */
void*
MdsApiSample_CustomizedUdpThreadMain(void *pNone) {
    static const char   THE_CONFIG_FILE_NAME[] = "mds_client_sample.conf";
    static const int32  THE_TIMEOUT_MS = 5000;

    MdsApiChannelGroupT channelGroup = {NULLOBJ_MDSAPI_CHANNEL_GROUP};
    MdsApiSessionInfoT  udpSnap1Channel = {NULLOBJ_MDSAPI_SESSION_INFO};
    MdsApiSessionInfoT  udpSnap2Channel = {NULLOBJ_MDSAPI_SESSION_INFO};
    MdsApiSessionInfoT  udpTick1Channel = {NULLOBJ_MDSAPI_SESSION_INFO};
    MdsApiSessionInfoT  udpTick2Channel = {NULLOBJ_MDSAPI_SESSION_INFO};
    int32               ret = 0;

    MdsApi_InitChannelGroup(&channelGroup);

    /* 初始化 Level1 行情组播接收通道 */
    if (! MdsApi_InitUdpChannel(&udpSnap1Channel, THE_CONFIG_FILE_NAME,
            "mds_client", "udpServer.Snap1")) {
        SLOG_ERROR("Init udp-Snap1 channel failure!");
        goto ON_ERROR;
    } else {
        /* 将连接信息添加到通道组 */
        if (! MdsApi_AddToChannelGroup(&channelGroup, &udpSnap1Channel)) {
            SLOG_ERROR("Add Snap1 to channel group failure!");
            goto ON_ERROR;
        }
    }

    /* 初始化 Level2 快照行情组播接收通道 */
    if (! MdsApi_InitUdpChannel(&udpSnap2Channel, THE_CONFIG_FILE_NAME,
            "mds_client", "udpServer.Snap2")) {
        SLOG_ERROR("Init udp-Snap2 channel failure!");
        goto ON_ERROR;
    } else {
        /* 将连接信息添加到通道组 */
        if (! MdsApi_AddToChannelGroup(&channelGroup, &udpSnap2Channel)) {
            SLOG_ERROR("Add Snap2 to channel group failure!");
            goto ON_ERROR;
        }
    }

    /* 初始化 Level2 逐笔数据(频道1)组播接收通道 */
    if (! MdsApi_InitUdpChannel(&udpTick1Channel, THE_CONFIG_FILE_NAME,
            "mds_client", "udpServer.Tick1")) {
        SLOG_ERROR("Init udp-Tick1 channel failure!");
        goto ON_ERROR;
    } else {
        /* 将连接信息添加到通道组 */
        if (! MdsApi_AddToChannelGroup(&channelGroup, &udpTick1Channel)) {
            SLOG_ERROR("Add TickT1 to channel group failure!");
            goto ON_ERROR;
        }
    }

    /* 初始化 Level2 逐笔数据(频道2)组播接收通道 */
    if (! MdsApi_InitUdpChannel(&udpTick2Channel, THE_CONFIG_FILE_NAME,
            "mds_client", "udpServer.Tick2")) {
        SLOG_ERROR("Init udp-Tick2 channel failure!");
        goto ON_ERROR;
    } else {
        /* 将连接信息添加到通道组 */
        if (! MdsApi_AddToChannelGroup(&channelGroup, &udpTick2Channel)) {
            SLOG_ERROR("Add Tick2 to channel group failure!");
            goto ON_ERROR;
        }
    }

    while (1) {
        /* 等待行情消息到达, 并通过回调函数对消息进行处理 */
        ret = MdsApi_WaitOnUdpChannelGroup(&channelGroup, THE_TIMEOUT_MS,
                _MdsApiSample_HandleMsg, NULL,
                (SGeneralClientChannelT **) NULL);
        if (__spk_unlikely(ret < 0)) {
            if (__spk_likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 已超时 (在超时时间内没有接收到任何网络消息) */
                continue;
            }

            /* 网络操作或回调函数返回错误 */
            goto ON_ERROR;
        }
    }

    return (void *) TRUE;

ON_ERROR:
    MdsApi_DestoryChannelGroup(&channelGroup);
    return (void *) FALSE;
}


/* ===================================================================
 * 行情查询的示例代码
 * =================================================================== */

/**
 * 查询行情快照
 *
 * @param   pQryChannel     查询通道的会话信息
 * @param   exchangeId      交易所代码
 * @param   instrId         产品代码
 * @return  大于等于0, 成功; 小于0, 失败 (错误号)
 */
static inline int32
_MdsApiSample_QueryMktDataSnapshot(MdsApiSessionInfoT *pQryChannel,
        eMdsExchangeIdT exchangeId, int32 instrId) {
    MdsMktDataSnapshotT snapshot = {NULLOBJ_MDS_MKT_DATA_SNAPSHOT};
    int32               ret = 0;

    ret = MdsApi_QueryMktDataSnapshot(pQryChannel, exchangeId,
            MDS_MD_PRODUCT_TYPE_STOCK, instrId, &snapshot);
    if (__spk_unlikely(ret < 0)) {
        SLOG_ERROR("Query snapshot failure! " \
                "ret[%d], exchangeId[%" __SPK_FMT_HH__ "u], instrId[%d]",
                ret, (uint8) exchangeId, instrId);
        return ret;
    }

    SLOG_DEBUG("... Query snapshot success! " \
            "SecurityID[%s], TradePx[%d], updateTime[%09d]",
            snapshot.l2Stock.SecurityID, snapshot.l2Stock.TradePx,
            snapshot.head.updateTime);
    return 0;
}


/**
 * 查询线程的主函数 (可以做为线程的主函数运行)
 *
 * @param   pQryChannel     查询通道的会话信息
 * @return  TRUE 处理成功; FALSE 处理失败
 */
void*
MdsApiSample_QueryThreadMain(MdsApiSessionInfoT *pQryChannel) {
    int32               ret = 0;

    SLOG_ASSERT(pQryChannel);

    while (1) {
        ret = _MdsApiSample_QueryMktDataSnapshot(pQryChannel,
                MDS_EXCH_SSE, 600000);
        if (__spk_unlikely(ret < 0)) {
            goto ON_ERROR;
        }

        SPK_SLEEP_MS(10000);
    }

    return (void *) TRUE;

ON_ERROR:
    return (void *) FALSE;
}


/* ===================================================================
 * 负责建立连接和初始化的主函数
 * =================================================================== */

/**
 * API接口库示例程序的主函数
 */
int32
MdsApiSample_Main() {
    static const char   THE_CONFIG_FILE_NAME[] = "mds_client_sample.conf";
    MdsApiClientEnvT    cliEnv = {NULLOBJ_MDSAPI_CLIENT_ENV};

    /* 因为样例代码会将信息输出到控制台, 所以此处先关闭标准输出缓存 */
    setvbuf(stdout, (char *) NULL, _IONBF, 0);

    /*
     * 设置登录MDS时使用的用户名和密码
     * @note 如通过API接口设置, 则可以不在配置文件中配置;
     */
    // MdsApi_SetThreadUsername("client1");
    // MdsApi_SetThreadPassword("123456");

    /* 初始化客户端环境 (配置文件参见: mds_client_sample.conf) */
    if (! MdsApi_InitAll(&cliEnv, THE_CONFIG_FILE_NAME,
            MDSAPI_CFG_DEFAULT_SECTION_LOGGER, MDSAPI_CFG_DEFAULT_SECTION,
            MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR, MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR,
            (char *) NULL, (char *) NULL, (char *) NULL, (char *) NULL)) {
        return -1;
    }

    /* 直接在主线程内接收行情消息 (@note 实际场景中应该创建单独的行情接收线程)
    if (! MdsApiSample_TcpThreadMain(&cliEnv.tcpChannel)) {
        goto ON_ERROR;
    }
    */

#if ! (defined (__WINDOWS__) || defined (__MINGW__))
    /* Linux 下的独立行情接收线程 */
    {
        pthread_t       tcpThreadId;
        pthread_t       udpThreadId;
        pthread_t       qryThreadId;
        int32           ret = 0;

        /* 创建TCP行情订阅的接收线程 */
        if (MdsApi_IsValidTcpChannel(&cliEnv.tcpChannel)) {
            ret = pthread_create(&tcpThreadId, NULL,
                    (void* (*)(void *)) MdsApiSample_TcpThreadMain,
                    &cliEnv.tcpChannel);
            if (ret != 0) {
                SLOG_ERROR("创建行情接收线程失败! error[%d]", ret);
                goto ON_ERROR;
            }
        }

        /* 创建行情查询线程 */
        if (MdsApi_IsValidQryChannel(&cliEnv.qryChannel)) {
            ret = pthread_create(&qryThreadId, NULL,
                    (void* (*)(void *)) MdsApiSample_QueryThreadMain,
                    &cliEnv.qryChannel);
            if (ret != 0) {
                SLOG_ERROR("创建行情查询线程失败! error[%d]", ret);
                goto ON_ERROR;
            }
        }

        if (1) {
            /* 创建UDP行情组播的接收线程 (需要在 MdsApi_InitAll 函数中指定 pUdpSnap1AddrKey 等组播地址参数) */
            if (MdsApi_IsValidChannelGroup(&cliEnv.udpChannelGroup)) {
                ret = pthread_create(&udpThreadId, NULL,
                        (void* (*)(void *)) MdsApiSample_UdpThreadMain,
                        &cliEnv.udpChannelGroup);
                if (ret != 0) {
                    SLOG_ERROR("创建行情组播接收线程失败! error[%d]", ret);
                    goto ON_ERROR;
                }
            }
        } else {
            /* 定制的UDP行情组播接收线程 (通过程序控制对接哪些组播行情) */
            ret = pthread_create(&udpThreadId, NULL,
                    (void* (*)(void *)) MdsApiSample_CustomizedUdpThreadMain,
                    NULL);
            if (ret != 0) {
                SLOG_ERROR("创建定制的行情组播接收线程失败! error[%d]", ret);
                goto ON_ERROR;
            }
        }
    }

#else
    /* Windows 下的独立行情接收线程 */
    {
        HANDLE          tcpThreadId;
        HANDLE          udpThreadId;
        HANDLE          qryThreadId;

        /* 创建TCP行情订阅的接收线程 */
        if (MdsApi_IsValidTcpChannel(&cliEnv.tcpChannel)) {
            /* 创建行情接收线程 */
            tcpThreadId = CreateThread(NULL, 0,
                    (LPTHREAD_START_ROUTINE) MdsApiSample_TcpThreadMain,
                    (LPVOID) &cliEnv.tcpChannel, 0, NULL);
            if (tcpThreadId == NULL) {
                SLOG_ERROR("创建行情接收线程失败! error[%lu]", GetLastError());
                goto ON_ERROR;
            }
        }

        /* 创建行情查询线程 */
        if (MdsApi_IsValidQryChannel(&cliEnv.qryChannel)) {
            qryThreadId = CreateThread(NULL, 0,
                    (LPTHREAD_START_ROUTINE) MdsApiSample_QueryThreadMain,
                    (LPVOID) &cliEnv.qryChannel, 0, NULL);
            if (qryThreadId == NULL) {
                SLOG_ERROR("创建行情查询线程失败! error[%lu]", GetLastError());
                goto ON_ERROR;
            }
        }

        /* 创建UDP行情组播的接收线程 (如果在配置文件中配置了组播行情地址的话) */
        if (MdsApi_IsValidChannelGroup(&cliEnv.udpChannelGroup)) {
            if (1) {
                udpThreadId = CreateThread(NULL, 0,
                        (LPTHREAD_START_ROUTINE) MdsApiSample_UdpThreadMain,
                        (LPVOID) &cliEnv.udpChannelGroup, 0, NULL);
                if (udpThreadId == NULL) {
                    SLOG_ERROR("创建行情组播接收线程失败! error[%lu]",
                            GetLastError());
                    goto ON_ERROR;
                }
            } else {
                udpThreadId = CreateThread(NULL, 0,
                        (LPTHREAD_START_ROUTINE)
                        MdsApiSample_CustomizedUdpThreadMain,
                        (LPVOID) NULL, 0, NULL);
                if (udpThreadId == NULL) {
                    SLOG_ERROR("创建定制的行情组播接收线程失败! error[%lu]",
                            GetLastError());
                    goto ON_ERROR;
                }
            }
        }
    }

#endif

    /* 为了测试行情订阅接口, 而直接在主线程中循环发送行情订阅请求 */
    {
        STimevalT       beginTime = {0, 0};
        STimevalT       endTime1 = {0, 0};
        STimevalT       endTime2 = {0, 0};

        while (MdsApi_IsValidTcpChannel(&cliEnv.tcpChannel)) {
            SPK_SLEEP_MS(30000);

            SLOG_INFO(">>> Subscribe stock market data ...");
            STime_GetTimeOfDay(&beginTime);

            MdsApi_SubscribeByString(&cliEnv.tcpChannel,
                    "600000, 600001.SH, 000001.SZ", (char *) NULL,
                    MDS_EXCH_SSE, MDS_MD_PRODUCT_TYPE_STOCK, MDS_SUB_MODE_SET,
                    MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                            | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                            | MDS_SUB_DATA_TYPE_L2_TRADE);

            /* 追加订阅 000300 指数行情 */
            STime_GetTimeOfDay(&endTime1);
            SLOG_INFO(">>> Append subscribe index market data ...");

            MdsApi_SubscribeByString(&cliEnv.tcpChannel,
                    "000300.SH", (char *) NULL,
                    MDS_EXCH_SSE, MDS_MD_PRODUCT_TYPE_INDEX, MDS_SUB_MODE_APPEND,
                    MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                            | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                            | MDS_SUB_DATA_TYPE_L2_TRADE);

            STime_GetTimeOfDay(&endTime2);
            SLOG_INFO("<<< Subscribe market data OK!!! runTime[%.2f,  %.2f] ms",
                    STime_DiffMillisecondFloat(&beginTime, &endTime1),
                    STime_DiffMillisecondFloat(&beginTime, &endTime2));
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


int
main(int argc, char *argv[]) {
    return MdsApiSample_Main();
}
