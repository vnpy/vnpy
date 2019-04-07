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
 * OES API接口库的CPP风格客户端示例
 *
 * @version 1.0 2017/08/24
 * @since   2017/08/24
 */


#include    <iostream>
#include    "oes_client_sample.h"


namespace Quant360 {


OesClientApi::OesClientApi() {
    isCfg = FALSE;
    isRunning = FALSE;
    terminatedFlag = 0;

    pSpi = NULL;

    memset(&apiCfg, 0, sizeof(OesApiClientCfgT));
    memset(&apiEnv, 0, sizeof(OesApiClientEnvT));
}


OesClientApi::~OesClientApi() {
    /* Do nothing */
}


/**
 * 注册spi回调接口
 *
 * @param   pSpi        spi回调接口
 *
 * @retval  TRUE: 设置成功
 * @retval  FALSE: 设置失败
 */
void
OesClientApi::RegisterSpi(OesClientSpi *pSpi) {
    this->pSpi = pSpi;
}


/**
 * 加载配置文件
 *
 * @param   pCfgFile        配置文件路径
 *
 * @retval  TRUE: 加载成功
 * @retval  FALSE: 加载失败
 */
BOOL
OesClientApi::LoadCfg(const char *pCfgFile) {
    if (isRunning) {
        fprintf(stderr, "运行状态中不能载入配置!\n");
        return FALSE;
    }

    if (! OesApi_ParseAllConfig(pCfgFile, &apiCfg)) {
        fprintf(stderr, "解析配置文件失败! cfgFile[%s]\n", pCfgFile);
        return FALSE;
    }

    /* 初始化日志配置 */
    OesApi_InitLogger(pCfgFile, OESAPI_CFG_DEFAULT_SECTION_LOGGER);

    isCfg = TRUE;
    return TRUE;
}


/**
 * 加载配置结构
 *
 * @param   pApiCfg         API配置结构
 *
 * @retval  TRUE: 加载成功
 * @retval  FALSE: 加载失败
 */
BOOL
OesClientApi::LoadCfg(OesApiClientCfgT *pApiCfg) {
    if (isRunning) {
        fprintf(stderr, "运行状态中不能载入配置!\n");
        return FALSE;
    }

    memcpy(&apiCfg, pApiCfg, sizeof(OesApiClientCfgT));

    isCfg = TRUE;
    return TRUE;
}


/*
 * 设置客户端的IP和MAC
 *
 * @param   pIpStr              点分十进制的IP地址字符串
 * @param   pMacStr             MAC地址字符串 (MAC地址格式 45:38:56:89:78:5A)
 *
 * @retval  TRUE: 设置成功
 * @retval  FALSE: 设置失败
 */
BOOL
OesClientApi::SetCustomizedIpAndMac(const char *pIpStr, const char *pMacStr) {
    return OesApi_SetCustomizedIpAndMac(pIpStr, pMacStr);
}


/*
 * 设置客户端的设备序列号
 *
 * @param   pDriverIdStr        设备序列号字符串
 *
 * @retval  TRUE: 设置成功
 * @retval  FALSE: 设置失败
 */
BOOL
OesClientApi::SetCustomizedDriverId(const char *pDriverIdStr) {
    return OesApi_SetCustomizedDriverId(pDriverIdStr);
}


/*
 * 设置当前线程登录OES时使用的登录用户名
 *
 * @param   pUsername           登录用户名
 *
 */
void
OesClientApi::SetThreadUsername(const char *pUsername) {
    OesApi_SetThreadUsername(pUsername);
}


/*
 * 设置当前线程登录OES时使用的登录密码
 *
 * @param   pPassword           登录密码
 *                              - 支持通过前缀指定密码类型, 如 md5:PASSWORD, txt:PASSWORD
 */
void
OesClientApi::SetThreadPassword(const char *pPassword) {
    OesApi_SetThreadPassword(pPassword);
}


/**
 * 对执行报告消息进行处理的回调函数
 *
 * @param   pRptChannel     回报通道的会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @param   pCallbackParams 外部传入的参数
 *
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
int32
OesClientApi::HandleReportMsg(OesApiSessionInfoT *pRptChannel,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    OesClientSpi        *pSpi = (OesClientSpi *) pCallbackParams;
    OesRspMsgBodyT      *pRspMsg = (OesRspMsgBodyT *) pMsgBody;
    OesRptMsgT          *pRptMsg = &pRspMsg->rptMsg;

    assert(pRptChannel && pMsgHead && pRspMsg);

    switch (pMsgHead->msgId) {
    case OESMSG_RPT_ORDER_INSERT:               /* OES委托已生成 (已通过风控检查) */
        pSpi->OnOrderInsert(&pRptMsg->rptBody.ordInsertRsp);
        break;

    case OESMSG_RPT_BUSINESS_REJECT:            /* OES业务拒绝 (未通过风控检查等) */
        pSpi->OnBusinessReject(pRptMsg->rptHead.ordRejReason,
                &pRptMsg->rptBody.ordRejectRsp);
        break;

    case OESMSG_RPT_ORDER_REPORT:               /* 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知) */
        pSpi->OnOrderReport(pRptMsg->rptHead.ordRejReason,
                &pRptMsg->rptBody.ordCnfm);
        break;

    case OESMSG_RPT_TRADE_REPORT:               /* 交易所成交回报 */
        pSpi->OnTradeReport(&pRptMsg->rptBody.trdCnfm);
        break;

    case OESMSG_RPT_CASH_ASSET_VARIATION:       /* 资金变动信息 */
        pSpi->OnCashAssetVariation(&pRptMsg->rptBody.cashAssetRpt);
        break;

    case OESMSG_RPT_STOCK_HOLDING_VARIATION:    /* 持仓变动信息 (股票) */
        pSpi->OnStockHoldingVariation(&pRptMsg->rptBody.stkHoldingRpt);
        break;

    case OESMSG_RPT_FUND_TRSF_REJECT:           /* 出入金委托响应-业务拒绝 */
        pSpi->OnFundTrsfReject(pRptMsg->rptHead.ordRejReason,
                &pRptMsg->rptBody.fundTrsfRejectRsp);
        break;

    case OESMSG_RPT_FUND_TRSF_REPORT:           /* 出入金委托执行报告 */
        pSpi->OnFundTrsfReport(pRptMsg->rptHead.ordRejReason,
                &pRptMsg->rptBody.fundTrsfCnfm);
        break;

    case OESMSG_RPT_MARKET_STATE:               /* 市场状态信息 */
        pSpi->OnMarketState(&pRspMsg->mktStateRpt);
        break;

    case OESMSG_RPT_REPORT_SYNCHRONIZATION: /* 回报同步响应 */
        break;

    case OESMSG_SESS_HEARTBEAT:
        break;

    default:
        fprintf(stderr, "收到未定义处理方式的回报消息! msgId[0x%02X]\n",
                pMsgHead->msgId);
        break;
    }

    return 0;
}


/**
  * 回报采集处理 (可以做为线程的主函数运行)
  *
  * @param   pRptChannel     回报通道的会话信息
  *
  * @return  TRUE 处理成功; FALSE 处理失败
  */
void *
OesClientApi::RptThreadMain(void *pParams) {
    static const int32  THE_TIMEOUT_MS = 1000;

    OesClientApi        *pApi = (OesClientApi *) pParams;
    OesClientSpi        *pSpi = pApi->pSpi;

    OesApiSessionInfoT  *pRptChannel = &pApi->apiEnv.rptChannel;
    volatile int32      *pTerminatedFlag = &pApi->terminatedFlag;

    int64               recvInterval = 0;
    int32               ret = 0;

    fprintf(stdout, "回报线程启动 ...\n");

    while (! *pTerminatedFlag) {
        /* 等待回报消息到达, 并通过回调函数对消息进行处理 */
        ret = OesApi_WaitReportMsg(pRptChannel, THE_TIMEOUT_MS,
                HandleReportMsg, (void *) pSpi);
        if (ret < 0) {
            if (SPK_IS_NEG_ETIMEDOUT(ret)) {
                /* 执行超时检查 (检查会话是否已超时) */
                if (pRptChannel->heartBtInt > 0) {
                    recvInterval = time(NULL) - OesApi_GetLastRecvTime(pRptChannel);
                    if (recvInterval > pRptChannel->heartBtInt * 2) {
                        fprintf(stderr, "回报会话已超时!\n");
                        goto ON_ERROR;
                    }
                }

                continue;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                fprintf(stderr, "回报会话已断开!\n");
                /* 连接已断开 */
            }
            goto ON_ERROR;
        }
    }

    fprintf(stdout, "回报线程退出 ...\n");

    *pTerminatedFlag = -1;
    return (void *) TRUE;

ON_ERROR:
    fprintf(stderr, "回报线程异常退出 ...\n");

    *pTerminatedFlag = -1;
    return (void *) FALSE;
}


/**
 * 启动 Client
 * 会在此函数内建立与服务端的连接，并启动回报线程
 *
 * @param[out]  pLastClSeqNo    返回服务器端最后接收到并校验通过的"客户委托流水号"
 *                                  - NULL表示忽略该参数
 *                                  - 在0.11之前的版本中，“客户委托流水号”是由客户端维护的
 *                                      线性递增序列，用于标识委托数据的唯一性，并防止重复申报
 *                                  - 从0.11版本开始，不再强制要求线性递增，只要维持在同一
 *                                      客户端下的唯一性即可
 * @param[in]   lastRptSeqNum   客户端最后接收到的回报数据的回报编号
 *                                  - 等于0, 从头开始推送回报数据
 *                                  - 大于0, 从该序号开始推送回报数据 (不包括该序号)
 *                                  - 小于0, 从最新的数据开始推送回报数据
 *
  * @return  TRUE 启动成功; FALSE 启动失败
 */
BOOL
OesClientApi::Start(int32 *pLastClSeqNo, int64 lastRptSeqNum) {
    if (! isCfg) {
        fprintf(stderr, "尚未载入配置!\n");
        return FALSE;
    }

    if (isRunning) {
        fprintf(stderr, "重复启动!\n");
        return FALSE;
    }

    if (pSpi == NULL) {
        fprintf(stderr, "尚未注册回调服务!\n");
        return FALSE;
    }

    /* 连接委托通道 */
    if (! OesApi_InitOrdChannel2(&apiEnv.ordChannel, &apiCfg.ordChannelCfg,
            pLastClSeqNo)) {
        fprintf(stderr, "连接委托通道失败!\n");
        goto __ON_ERROR;
    }

    /* 连接回报通道 */
    if (! OesApi_InitRptChannel2(&apiEnv.rptChannel, &apiCfg.rptChannelCfg,
            &apiCfg.subscribeInfo, lastRptSeqNum)) {
        fprintf(stderr, "连接回报通道失败!\n");
        goto __ON_ERROR;
    }

    /* 连接查询通道 */
    if (! OesApi_InitQryChannel2(&apiEnv.qryChannel, &apiCfg.qryChannelCfg)) {
        fprintf(stderr, "连接查询通道失败!\n");
        goto __ON_ERROR;
    }

    terminatedFlag = 0;

#if ! (defined (__WINDOWS__) || defined (__MINGW__))
    {
        pthread_t       rptThreadId;
        int32           ret = 0;

        /* 创建回报接收线程 */
        ret = pthread_create(&rptThreadId, NULL, RptThreadMain, (void *) this);
        if (ret != 0) {
            fprintf(stderr, "创建回报接收线程失败! error[%d - %s]\n",
                    ret, strerror(ret));
            goto __ON_ERROR;
        }
    }
#else
    {
        /* 创建回报接收线程 */
        CreateThread(NULL, 0,
                (LPTHREAD_START_ROUTINE) RptThreadMain,
                (LPVOID) this, 0, NULL);
    }
#endif

    isRunning = TRUE;

    return TRUE;

__ON_ERROR:
    Stop();
    return FALSE;
}


/**
 * 停止Client
 * 会在此函数内断开与服务端的连接，并停止回报线程
 */
void
OesClientApi::Stop(void) {
    if (isRunning) {
        /* 设置回报线程退出标志 (实际场景中请勿参考此部分代码) */
        terminatedFlag = 1;
        /* 回报线程将标志设置为-1后退出, 父进程再释放资源 */
        while(terminatedFlag != -1) {
            SPK_SLEEP_MS(1000);
        }
    }

    OesApi_Logout(&apiEnv.qryChannel, TRUE);
    OesApi_Logout(&apiEnv.rptChannel, TRUE);
    OesApi_Logout(&apiEnv.ordChannel, TRUE);

    isRunning = FALSE;
}


/* ===================================================================
 * 委托申报接口
 * =================================================================== */

/**
 * 发送委托申报请求，非线程安全实现
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * - 关于"客户委托流水号(clSeqNo)"
 *   - 在0.11之前的版本中，“客户委托流水号”是由客户端维护的线性递增序列，用于标识委托数据的
 *     唯一性，并防止重复申报
 *   - 从0.11版本开始，不再强制要求线性递增，只要维持在同一客户端下的唯一性即可
 *   - 客户端可以通过登录后的会话信息中的 lastOutMsgSeq 字段获取到其最后发送到OES服务器的
 *     "客户委托流水号"
 *
 * - 关于"原始订单的客户订单编号(origClOrdId)"
 *   - "客户订单编号(clOrdId)", 是由OES服务器端维护的、在OES内具有唯一性的内部委托编号,
 *     该编号会通过回报数据返回客户端
 *   - 撤单时, 需要将待撤订单的客户订单编号(clOrdId)赋值到撤单请求的 origClOrdId 字段,
 *     OES将根据该字段检索和匹配待撤销的原始订单
 *
 * @param      pOrdReq     待发送的委托申报请求
 *
 * @retval      0           成功
 * @retval      <0          失败 (负的错误号)
 */
int32
OesClientApi::SendOrder(const OesOrdReqT *pOrderReq) {
    return OesApi_SendOrderReq(&apiEnv.ordChannel, pOrderReq);
}


/**
 * 发送撤单请求，非线程安全实现
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * - 关于"客户委托流水号(clSeqNo)"
 *   - 在0.11之前的版本中，“客户委托流水号”是由客户端维护的线性递增序列，用于标识委托数据的
 *     唯一性，并防止重复申报
 *   - 从0.11版本开始，不再强制要求线性递增，只要维持在同一客户端下的唯一性即可
 *   - 客户端可以通过登录后的会话信息中的 lastOutMsgSeq 字段获取到其最后发送到OES服务器的
 *     "客户委托流水号"
 *
 * - 关于"原始订单的客户订单编号(origClOrdId)"
 *   - "客户订单编号(clOrdId)", 是由OES服务器端维护的、在OES内具有唯一性的内部委托编号,
 *     该编号会通过回报数据返回客户端
 *   - 撤单时, 需要将待撤订单的客户订单编号(clOrdId)赋值到撤单请求的 origClOrdId 字段,
 *     OES将根据该字段检索和匹配待撤销的原始订单
 *
 * @param      pCancelReq   待发送的撤单请求
 *
 * @retval      0           成功
 * @retval      <0          失败 (负的错误号)
 */
int32
OesClientApi::SendCancelOrder(const OesOrdCancelReqT *pCancelReq) {
    return OesApi_SendOrderCancelReq(&apiEnv.ordChannel, pCancelReq);
}


/**
 * 发送出入金委托请求，非线程安全实现
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * - 关于"客户委托流水号(clSeqNo)"
 *   - 在0.11之前的版本中，“客户委托流水号”是由客户端维护的线性递增序列，用于标识委托数据的
 *     唯一性，并防止重复申报
 *   - 从0.11版本开始，不再强制要求线性递增，只要维持在同一客户端下的唯一性即可
 *   - 客户端可以通过登录后的会话信息中的 lastOutMsgSeq 字段获取到其最后发送到OES服务器的
 *     "客户委托流水号"
 *
 * @param      pFundTrsfReq     待发送的出入金委托请求
 *
 * @retval      0           成功
 * @retval      <0          失败 (负的错误号)
 */
int32
OesClientApi::SendFundTrsf(const OesFundTrsfReqT *pFundTrsfReq) {
    return OesApi_SendFundTransferReq(&apiEnv.ordChannel, pFundTrsfReq);
}
/* -------------------------           */


/* ===================================================================
 * 查询接口
 * =================================================================== */

/**
 * 获取API的发行版本号
 *
 * @return  API的发行版本号 (如: "0.15.3")
 */
const char *
OesClientApi::GetVersion(void) {
    return OesApi_GetApiVersion();
}


/**
 * 获取当前交易日
 *
 * @retval  >0          当前交易日 (格式：YYYYMMDD)
 * @retval  0           尚未连接查询服务
 * @retval  <0          失败 (负的错误号)
 */
int32
OesClientApi::GetTradingDay(void) {
    return OesApi_GetTradingDay(&apiEnv.qryChannel);
}


/**
 * 获取客户端总览信息
 *
 * @retval  0           查询成功
 * @retval  <0          失败 (负的错误号)
 */
int32
OesClientApi::GetClientOverview(OesClientOverviewT *pClientOverview) {
    return OesApi_GetClientOverview(&apiEnv.qryChannel, pClientOverview);
}


/**
 * 查询委托信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryOrder(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryOrder(
            (OesOrdItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询委托信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryOrder(const OesQryOrdFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryOrder(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryOrder, (void *) pSpi);
}


/**
 * 查询成交信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryTrade(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryTrade(
            (OesTrdItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询成交信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryTrade(const OesQryTrdFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryTrade(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryTrade, (void *) pSpi);
}


/**
 * 查询客户资金信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryCashAsset(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryCashAsset(
            (OesCashAssetItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询客户资金信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryCashAsset(const OesQryCashAssetFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryCashAsset(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryCashAsset, (void *) pSpi);
}


/**
 * 查询股票持仓信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryStkHolding(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryStkHolding(
            (OesStkHoldingItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询股票持仓信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryStkHolding(const OesQryStkHoldingFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryStkHolding(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryStkHolding, (void *) pSpi);
}


/**
 * 查询新股配号、中签信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryLotWinning(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryLotWinning(
            (OesLotWinningItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询新股配号、中签信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryLotWinning(const OesQryLotWinningFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryLotWinning(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryLotWinning, (void *) pSpi);
}


/**
 * 查询客户信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryCustInfo(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryCustInfo(
            (OesCustItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询客户信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryCustInfo(const OesQryCustFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryCustInfo(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryCustInfo, (void *) pSpi);
}


/**
 * 查询证券账户信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryInvAcct(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryInvAcct(
            (OesInvAcctItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 使用回调函数形式的查询证券账户信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryInvAcct(const OesQryInvAcctFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryInvAcct(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryInvAcct, (void *) pSpi);
}


/**
 * 查询客户佣金信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryCommissionRate(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryCommissionRate(
            (OesCommissionRateItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询客户佣金信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryCommissionRate(const OesQryCommissionRateFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryCommissionRate(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryCommissionRate, (void *) pSpi);
}


/**
 * 查询出入金流水回调包裹函数
 */
static __inline int32
_OesClientApi_QueryFundTransferSerial(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryFundTransferSerial(
            (OesFundTransferSerialItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询出入金流水，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryFundTransferSerial(const OesQryFundTransferSerialFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryFundTransferSerial(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryFundTransferSerial, (void *) pSpi);
}


/**
 * 查询证券发行产品信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryIssue(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryIssue(
            (OesIssueItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询证券发行产品信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryIssue(const OesQryIssueFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryIssue(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryIssue, (void *) pSpi);
}


/**
 * 查询现货产品信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryStock(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryStock(
            (OesStockItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询现货产品信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryStock(const OesQryStockFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryStock(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryStock, (void *) pSpi);
}


/**
 * 查询ETF申赎产品信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryEtf(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryEtf(
            (OesEtfItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询ETF申赎产品信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryEtf(const OesQryEtfFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryEtf(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryEtf, (void *) pSpi);
}


/**
 * 查询ETF成分股信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryEtfComponent(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryEtfComponent(
            (OesEtfComponentItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询ETF成分股信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryEtfComponent(const OesQryEtfComponentFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryEtfComponent(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryEtfComponent, (void *) pSpi);
}


/**
 * 查询市场状态信息回调包裹函数
 */
static __inline int32
_OesClientApi_QueryMarketState(OesApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pQryCursor,
        void *pCallbackParams) {
    ((OesClientSpi *) pCallbackParams)->OnQueryMarketState(
            (OesMarketStateItemT *) pMsgBody, pQryCursor,
            ((OesClientSpi *) pCallbackParams)->currentRequestId);
    return 0;
}


/**
 * 查询市场状态信息，非线程安全实现
 *
 * @param   pQryFilter          查询条件过滤条件
 *
 * @retval  >=0                 成功查询到的记录数
 * @retval  <0                  失败 (负的错误号)
 */
int32
OesClientApi::QueryMarketState(const OesQryMarketStateFilterT *pQryFilter, int32 requestId) {
    pSpi->currentRequestId = requestId;

    return OesApi_QueryMarketState(&apiEnv.qryChannel, pQryFilter,
            _OesClientApi_QueryMarketState, (void *) pSpi);
}


}
