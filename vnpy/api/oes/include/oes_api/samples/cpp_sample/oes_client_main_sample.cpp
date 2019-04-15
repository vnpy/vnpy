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
 * @file    oes_client_main_sample.c
 *
 * OES API接口库的CPP风格客户端示例
 *
 * @version 1.0 2017/08/24
 * @since   2017/08/24
 */


#include    <iostream>
#include    "oes_client_sample.h"
#include    "oes_client_my_spi_sample.h"


/**
 * 发送委托请求
 *
 * @param   pOesApi         oes客户端
 * @param   mktId           市场代码 @see eOesMarketIdT
 * @param   pSecurityId     股票代码 (char[6]/char[8])
 * @param   pInvAcctId      股东账户代码 (char[10])，可 NULL
 * @param   ordType         委托类型 @see eOesOrdTypeT, eOesOrdTypeShT, eOesOrdTypeSzT
 * @param   bsType          买卖类型 @sse eOesBuySellTypeT
 * @param   ordQty          委托数量 (单位为股/张)
 * @param   ordPrice        委托价格 (单位精确到元后四位，即1元 = 10000)
 *
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
_OesClientMain_SendOrder(Quant360::OesClientApi *pOesApi,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        uint8 ordType, uint8 bsType, int32 ordQty, int32 ordPrice) {
    OesOrdReqT          ordReq = {NULLOBJ_OES_ORD_REQ};

    ordReq.clSeqNo = (int32) ++ pOesApi->apiEnv.ordChannel.lastOutMsgSeq;
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

    return pOesApi->SendOrder(&ordReq);
}


/**
 * 发送撤单请求
 *
 * @param   pOesApi         oes客户端
 * @param   mktId           被撤委托的市场代码 @see eOesMarketIdT
 * @param   pSecurityId     被撤委托股票代码 (char[6]/char[8]), 可空
 * @param   pInvAcctId      被撤委托股东账户代码 (char[10])，可空
 * @param   origClSeqNo     被撤委托的流水号 (若使用 origClOrdId, 则不必填充该字段)
 * @param   origClEnvId     被撤委托的客户端环境号 (小于等于0, 则使用当前会话的 clEnvId)
 * @param   origClOrdId     被撤委托的客户订单编号 (若使用 origClSeqNo, 则不必填充该字段)
 *
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
_OesClientMain_CancelOrder(Quant360::OesClientApi *pOesApi,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        int32 origClSeqNo, int8 origClEnvId, int64 origClOrdId) {
    OesOrdCancelReqT    cancelReq = {NULLOBJ_OES_ORD_CANCEL_REQ};

    cancelReq.clSeqNo = (int32) ++ pOesApi->apiEnv.ordChannel.lastOutMsgSeq;
    cancelReq.mktId = mktId;

    if (pSecurityId) {
        /* 撤单时被撤委托的股票代码可不填 */
        strncpy(cancelReq.securityId, pSecurityId, sizeof(cancelReq.securityId) - 1);
    }

    if (pInvAcctId) {
        /* 撤单时被撤委托的股东账户可不填 */
        strncpy(cancelReq.invAcctId, pInvAcctId, sizeof(cancelReq.invAcctId) - 1);
    }

    cancelReq.origClSeqNo = origClSeqNo;
    cancelReq.origClEnvId = origClEnvId;

    cancelReq.origClOrdId = origClOrdId;

    return pOesApi->SendCancelOrder(&cancelReq);
}

/**
 * 查询客户端总览信息
 *
 * @param   pSessionInfo    会话信息
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
_OesClientMain_QueryClientOverview(Quant360::OesClientApi *pOesApi) {
    OesClientOverviewT  clientOverview = {NULLOBJ_OES_CLIENT_OVERVIEW};
    int32               ret = 0;
    int32               i = 0;

    ret = pOesApi->GetClientOverview(&clientOverview);
    if (ret < 0) {
        return ret;
    }

    printf(">>> 客户端总览信息: {客户端编号[%d], 客户端类型[%hhu], " \
            "客户端状态[%hhu], 客户端名称[%s], 上海现货对应PBU[%d], " \
            "深圳现货对应PBU[%d], 委托通道流控阈值[%d], 查询通道流控阈值[%d], " \
            "关联的客户数量[%d]}\n",
            clientOverview.clientId, clientOverview.clientType,
            clientOverview.clientStatus, clientOverview.clientName,
            clientOverview.sseStkPbuId, clientOverview.szseStkPbuId,
            clientOverview.ordTrafficLimit, clientOverview.qryTrafficLimit,
            clientOverview.associatedCustCnt);

    for (i = 0; i < clientOverview.associatedCustCnt; i++) {
        printf("    >>> 客户总览信息: {客户代码[%s], 客户状态[%hhu], " \
                "风险评级[%hhu], 营业部代码[%d], 客户姓名[%s]}\n",
                clientOverview.custItems[i].custId,
                clientOverview.custItems[i].status,
                clientOverview.custItems[i].riskLevel,
                clientOverview.custItems[i].branchId,
                clientOverview.custItems[i].custName);

        if (clientOverview.custItems[i].spotCashAcct.isValid) {
            printf("        >>> 资金账户总览: {资金账户[%s], " \
                    "资金类型[%hhu], 账户状态[%hhu], 出入金是否禁止[%hhu]}\n",
                    clientOverview.custItems[i].spotCashAcct.cashAcctId,
                    clientOverview.custItems[i].spotCashAcct.cashType,
                    clientOverview.custItems[i].spotCashAcct.cashAcctStatus,
                    clientOverview.custItems[i].spotCashAcct.isFundTrsfDisabled);
        }

        if (clientOverview.custItems[i].shSpotInvAcct.isValid) {
            printf("        >>> 股东账户总览: {股东账户代码[%s], " \
                    "市场代码[%hhu], 账户状态[%hhu], 是否禁止交易[%hhu], 席位号[%d], " \
                    "当日累计有效交易类委托笔数[%d], 当日累计有效非交易类委托笔数[%d], " \
                    "当日累计有效撤单笔数[%d], 当日累计被OES拒绝的委托笔数[%d], " \
                    "当日累计被交易所拒绝的委托笔数[%d], 当日累计成交笔数[%d]}\n",
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
            printf("        >>> 股东账户总览: {股东账户代码[%s], " \
                    "市场代码[%hhu], 账户状态[%hhu], 是否禁止交易[%hhu], 席位号[%d], " \
                    "当日累计有效交易类委托笔数[%d], 当日累计有效非交易类委托笔数[%d], " \
                    "当日累计有效撤单笔数[%d], 当日累计被OES拒绝的委托笔数[%d], " \
                    "当日累计被交易所拒绝的委托笔数[%d], 当日累计成交笔数[%d]}\n",
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
 * 查询市场状态
 *
 * @param   pOesApi         oes客户端
 * @param   exchId          交易所代码 @see eOesExchangeIdT
 * @param   platformId      交易平台类型 @see eOesPlatformIdT
 *
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
_OesClientMain_QueryMarketStatus(Quant360::OesClientApi *pOesApi,
        uint8 exchId, uint8 platformId) {
    OesQryMarketStateFilterT    qryFilter = {NULLOBJ_OES_QRY_MARKET_STATE_FILTER};

    qryFilter.exchId = exchId;
    qryFilter.platformId = platformId;

    /* 也可直接使用 pOesApi->QueryMarketState(NULL, 0) 查询所有的市场状态 */
    return pOesApi->QueryMarketState(&qryFilter, 0);
}


/**
 * 查询资金
 *
 * @param   pOesApi         oes客户端
 * @param   pCashAcctId     资金账户代码
 *
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
_OesClientMain_QueryCashAsset(Quant360::OesClientApi *pOesApi,
        const char *pCashAcctId) {
    OesQryCashAssetFilterT  qryFilter = {NULLOBJ_OES_QRY_CASH_ASSET_FILTER};

    if (pCashAcctId) {
        strncpy(qryFilter.cashAcctId, pCashAcctId,
                sizeof(qryFilter.cashAcctId) - 1);
    }

    /* 也可直接使用 pOesApi->QueryCashAsset(NULL, 0) 查询客户所有资金账户 */
    return pOesApi->QueryCashAsset(&qryFilter, 0);
}


/**
 * 查询产品
 *
 * @param   pOesApi         oes客户端
 * @param   pSecurityId     产品代码
 * @param   mktId           市场代码
 * @param   securityType    证券类别
 * @param   subSecurityType 证券子类别
 *
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
_OesClientMain_QueryStock(Quant360::OesClientApi *pOesApi,
        const char *pSecurityId, uint8 mktId, uint8 securityType,
        uint8 subSecurityType) {
    OesQryStockFilterT  qryFilter = {NULLOBJ_OES_QRY_STOCK_FILTER};

    if (pSecurityId) {
        strncpy(qryFilter.securityId, pSecurityId,
                sizeof(qryFilter.securityId) - 1);
    }

    qryFilter.mktId = mktId;
    qryFilter.securityType = securityType;
    qryFilter.subSecurityType = subSecurityType;

    return pOesApi->QueryStock(&qryFilter, 0);
}


/**
 * 查询股票持仓
 *
 * @param   pOesApi         oes客户端
 * @param   mktId           市场代码 @see eOesMarketIdT
 * @param   pSecurityId     股票代码 (char[6]/char[8])
 *
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
_OesClientMain_QueryStkHolding(Quant360::OesClientApi *pOesApi,
        uint8 mktId, const char *pSecurityId) {
    OesQryStkHoldingFilterT qryFilter = {NULLOBJ_OES_QRY_STK_HOLDING_FILTER};

    qryFilter.mktId = mktId;
    if (pSecurityId) {
        strncpy(qryFilter.securityId, pSecurityId,
                sizeof(qryFilter.securityId) - 1);
    }

    /* 也可直接使用 pOesApi->QueryStkHolding(NULL, 0) 查询客户所有持仓 */
    return pOesApi->QueryStkHolding(&qryFilter, 0);
}


int
main(void) {
    Quant360::OesClientApi  *pOesApi = new Quant360::OesClientApi();
    Quant360::OesClientSpi  *pOesSpi = new OesClientMySpi();

    if (!pOesApi || !pOesSpi) {
        fprintf(stderr, "内存不足!\n");
        return ENOMEM;
    }

    /* 打印API版本信息 */
    fprintf(stdout, "OesClientApi 版本: %s\n",
            Quant360::OesClientApi::GetVersion());

    /* 注册spi回调接口 */
    pOesApi->RegisterSpi(pOesSpi);

    /* 加载配置文件 */
    if (! pOesApi->LoadCfg("oes_client_sample.conf")) {
        fprintf(stderr, "加载配置文件失败!\n");
        return EINVAL;
    }

    /*
     * 设置登录OES时使用的用户名和密码
     * @note 如通过API接口设置，则可以不在配置文件中配置;
     *          支持通过前缀指定密码类型, 如 md5:PASSWORD, txt:PASSWORD
     */
    // pOesApi->SetThreadUsername("customer1");
    // pOesApi->SetThreadPassword("txt:123456");
    // pOesApi->SetThreadPassword("md5:e10adc3949ba59abbe56e057f20f883e");

    /*
     * 设置客户端本地的设备序列号
     * @note 为满足监管需求，需要设置客户端本机的硬盘序列号
     */
    pOesApi->SetCustomizedDriverId("C02TL13QGVC8");

    /* 启动 */
    if (! pOesApi->Start()) {
        fprintf(stderr, "启动API失败!\n");
        return EINVAL;
    }

    /* 打印当前交易日 */
    fprintf(stdout, "服务端交易日: %08d\n", pOesApi->GetTradingDay());

    /* 查询样例 */
    {
        /* 查询 深交所 现货集中竞价平台 市场状态 */
        _OesClientMain_QueryMarketStatus(pOesApi, OES_EXCH_SZSE,
                OES_PLATFORM_CASH_AUCTION);

        /* 查询 客户端总览信息 */
        _OesClientMain_QueryClientOverview(pOesApi);

        /* 查询 所有关联资金账户的资金信息 */
        _OesClientMain_QueryCashAsset(pOesApi, NULL);

        /* 查询 指定资金账户的资金信息 */
        /* _OesClientMain_QueryCashAsset(pOesApi, "XXXXX"); */

        /* 查询 指定上证 600000 的产品信息 */
        _OesClientMain_QueryStock(pOesApi, "600000",
                OES_MKT_ID_UNDEFINE, OES_SECURITY_TYPE_UNDEFINE,
                OES_SUB_SECURITY_TYPE_UNDEFINE);

        /* 查询 上海A股市场 的产品信息 */
        /* _OesClientMain_QueryStock(pOesApi, NULL,
                OES_MKT_ID_SH_A, OES_SECURITY_TYPE_UNDEFINE,
                OES_SUB_SECURITY_TYPE_UNDEFINE); */

        /* 查询 上证 600000 股票的持仓 */
        _OesClientMain_QueryStkHolding(pOesApi, OES_MKT_ID_SH_A, "600000");

        /* 查询 上证 所有股票持仓 */
        _OesClientMain_QueryStkHolding(pOesApi, OES_MKT_ID_SH_A, NULL);

        /* 查询 沪深两市 所有股票持仓 */
        _OesClientMain_QueryStkHolding(pOesApi, OES_MKT_ID_UNDEFINE, NULL);
    }

    /* 委托样例 */
    {
        /* 以 12.67元 购买 浦发银行(600000) 100股 */
        _OesClientMain_SendOrder(pOesApi, OES_MKT_ID_SH_A, "600000", NULL,
                OES_ORD_TYPE_LMT, OES_BS_TYPE_BUY, 100, 126700);

        /* 以 市价 卖出 平安银行(000001) 200股 */
        _OesClientMain_SendOrder(pOesApi, OES_MKT_ID_SZ_A, "000001", NULL,
                OES_ORD_TYPE_SZ_MTL_BEST, OES_BS_TYPE_SELL, 200, 0);

        /*
         * 以 1.235 的报价做 10万元 GC001(204001)逆回购
         * - 逆回购每张标准券100元，委托份数填 (10万元 除以 100元/张 =) 1000张
         *   上证逆回购报价单位是0.005，份数单位是1000张
         */
        _OesClientMain_SendOrder(pOesApi, OES_MKT_ID_SH_A, "204001", NULL,
                OES_ORD_TYPE_LMT, OES_BS_TYPE_CREDIT_SELL, 1000, 12350);

        /*
         * 以 4.321 的报价做 1千元 R-001(131810)逆回购
         * - 逆回购每张标准券100元，委托份数填 (1千元 除以 100元/张 =) 10张
         *   深证逆回购报价单位是0.001，份数单位是10张
         */
        _OesClientMain_SendOrder(pOesApi, OES_MKT_ID_SZ_A, "131810", NULL,
                OES_ORD_TYPE_LMT, OES_BS_TYPE_CREDIT_SELL, 10, 43210);

        /* 以 11.16元 认购 宏达电子(300726) 500股 */
        _OesClientMain_SendOrder(pOesApi, OES_MKT_ID_SZ_A, "300726", NULL,
                OES_ORD_TYPE_LMT, OES_BS_TYPE_SUBSCRIPTION, 500, 111600);

        /*
         * 新股申购的申购额度的查询方式
         * - 新股申购额度通过 查询股东账户信息(OesApi_QueryInvAcct)接口 返回信息中的
         *   OesInvAcctItemT.subscriptionQuota 来获取
         * - 查询股东账户信息(OesApi_QueryInvAcct)接口 在不指定过滤条件的情况下可以依次返回
         *   沪深两市的股东账户信息，需要通过 OesInvAcctItemT.mktId 来区分不同市场的股东账户
         */
    }

    /* 撤单样例 */
    {
        /* 定义 origOrder 作为模拟的待撤委托 */
        OesOrdCnfmT         origOrder = {NULLOBJ_OES_ORD_CNFM};
        origOrder.mktId = OES_MKT_ID_SH_A;
        origOrder.clEnvId = 1;
        origOrder.clSeqNo = 11;
        origOrder.clOrdId = 111;        /* 真实场景中，待撤委托的clOrdId需要通过回报消息获取 */

        /* 通过待撤委托的 clOrdId 进行撤单 */
        _OesClientMain_CancelOrder(pOesApi, origOrder.mktId, NULL, NULL,
                0, 0, origOrder.clOrdId);

        /*
         * 通过待撤委托的 clSeqNo 进行撤单
         * - 如果撤单时 origClEnvId 填0，则默认会使用当前客户端实例的 clEnvId 作为
         *   待撤委托的 origClEnvId 进行撤单
         */
        _OesClientMain_CancelOrder(pOesApi, origOrder.mktId, NULL, NULL,
                origOrder.clSeqNo, origOrder.clEnvId, 0);
    }

    /* 等待回报消息接收完成 */
    SPK_SLEEP_MS(1000);

    /* 停止 */
    pOesApi->Stop();

    delete pOesApi;
    delete pOesSpi;

    return 0;
}
