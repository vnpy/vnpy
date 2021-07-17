/*
 * Copyright 2009-2015 the original author or authors.
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
 * @file    oes_qry_credit_packets.h
 *
 * 信用业务查询消息的报文定义
 *
 * @version 0.17        2020/09/16
 *          - 新增 '融资融券合约信息查询' 相关报文定义
 *              - 新增结构体 查询融资融券合约信息过滤条件(OesQryCrdDebtContractFilterT)
 *              - 新增结构体 融资融券合约信息内容(OesCrdDebtContractItemT)
 *              - 新增结构体 查询融资融券合约信息请求(OesQryCrdDebtContractReqT)
 *              - 新增结构体 查询融资融券合约信息应答(OesQryCrdDebtContractRspT)
 *          - 新增 '融资融券合约流水信息查询' 相关报文定义
 *              - 新增结构体 查询融资融券合约流水信息过滤条件(OesQryCrdDebtJournalFilterT)
 *              - 新增结构体 融资融券合约流水信息内容(OesCrdDebtJournalItemT)
 *              - 新增结构体 查询融资融券合约流水信息请求(OesQryCrdDebtJournalReqT)
 *              - 新增结构体 查询融资融券合约流水信息应答(OesQryCrdDebtJournalRspT)
 *          - 新增 '客户单证券融资融券负债统计信息查询' 相关报文定义
 *              - 新增结构体 查询客户单证券融资融券负债统计信息过滤条件(OesQryCrdSecurityDebtStatsFilterT)
 *              - 新增结构体 客户单证券融资融券负债统计信息内容(OesCrdSecurityDebtStatsItemT)
 *              - 新增结构体 查询客户单证券融资融券负债统计信息请求(OesQryCrdSecurityDebtStatsReqT)
 *              - 新增结构体 查询客户单证券融资融券负债统计信息应答(OesQryCrdSecurityDebtStatsRspT)
 *          - 新增 '信用资产信息查询' 相关报文定义
 *              - 新增结构体 查询信用资产信息过滤条件(OesQryCrdCreditAssetFilterT)
 *              - 新增结构体 信用资产信息内容(OesCrdCreditAssetItemT)
 *              - 新增结构体 查询信用资产信息请求(OesQryCrdCreditAssetReqT)
 *              - 新增结构体 查询信用资产信息应答(OesQryCrdCreditAssetRspT)
 *          - 新增 '融资融券业务直接还款信息查询' 相关报文定义
 *              - 新增结构体 查询直接还款信息过滤条件(OesQryCrdCashRepayFilterT)
 *              - 新增结构体 直接还款信息内容(OesCrdCashRepayItemT)
 *              - 新增结构体 查询直接还款信息请求(OesQryCrdCashRepayReqT)
 *              - 新增结构体 查询直接还款信息应答(OesQryCrdCashRepayRspT)
 *          - 新增 '融资融券业务资金头寸信息 (可融资头寸信息) 查询' 相关报文定义
 *              - 新增结构体 查询资金头寸信息过滤条件(OesQryCrdCashPositionFilterT)
 *              - 新增结构体 资金头寸信息内容(OesCrdCashPositionItemT)
 *              - 新增结构体 查询资金头寸信息请求(OesQryCrdCashPositionReqT)
 *              - 新增结构体 查询资金头寸信息应答(OesQryCrdCashPositionRspT)
 *          - 新增 '融资融券业务证券头寸信息 (可融券头寸信息) 查询' 相关报文定义
 *              - 新增结构体 查询证券头寸信息过滤条件(OesQryCrdSecurityPositionFilterT)
 *              - 新增结构体 证券头寸信息内容(OesCrdSecurityPositionItemT)
 *              - 新增结构体 查询证券头寸信息请求(OesQryCrdSecurityPositionReqT)
 *              - 新增结构体 查询证券头寸信息应答(OesQryCrdSecurityPositionRspT)
 *          - 新增 '融资融券业务余券信息查询' 相关报文定义
 *              - 新增结构体 查询余券信息过滤条件(OesQryCrdExcessStockFilterT)
 *              - 新增结构体 余券信息内容(OesCrdExcessStockItemT)
 *              - 新增结构体 查询余券信息请求(OesQryCrdExcessStockReqT)
 *              - 新增结构体 查询余券信息应答(OesQryCrdExcessStockRspT)
 *          - 新增 '融资融券息费利率查询' 相关报文定义
 *              - 新增结构体 融资融券息费利率过滤条件(OesQryCrdInterestRateFilterT)
 *              - 新增结构体 融资融券息费利率内容(OesCommissionRateItemT)
 *              - 新增结构体 查询融资融券息费利率请求(OesQryCrdInterestRateReqT)
 *              - 新增结构体 查询融资融券息费利率应答(OesQryCrdInterestRateRspT)
 * @version 0.17.0.8    2021/04/20
 *          - '客户单证券融资融券负债统计信息 (OesCrdSecurityDebtStatsItemT)'中
 *              - 新增 在途卖出证券持仓市值 (collateralUncomeSellMarketCap) 字段
 *              - 新增 在途转出证券持仓市值 (collateralTrsfOutMarketCap) 字段
 *              - 新增 该证券所有融券合约的合计可归还数量 (securityRepayableQty) 字段
 *          - '信用资产信息 (OesCrdCreditAssetItemT)'中
 *              - 删除 证券总持仓市值 (totalHoldingMarketCap) 字段
 *              - 新增 证券持仓市值 (holdingMarketCap) 字段
 *              - 新增 在途卖出证券持仓市值 (collateralUncomeSellMarketCap) 字段
 *          - 查询融资融券合约信息过滤条件 (OesQryCrdDebtContractFilterT) 中:
 *              - 新增查询条件 历史合约标识(historyContractFlag)
 * @version 0.17.0.9    2021/04/xx
 *          - '信用资产信息 (OesCrdCreditAssetItemT)'中
 *              - 新增 融资融券专项头寸总费用 (creditTotalSpecialFee) 字段
 *              - 新增 融资专项头寸成本费 (marginBuySpecialFee) 字段
 *              - 新增 融券专项头寸成本费 (shortSellSpecialFee) 字段
 *
 * @since   0.17    2020/09/16
 */


#ifndef _OES_QRY_CREDIT_PACKETS_H
#define _OES_QRY_CREDIT_PACKETS_H


#include    <oes_global/oes_base_model.h>
#include    <oes_global/oes_base_credit_model.h>
#include    <oes_global/oes_qry_packets.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 每条查询应答报文中融资融券合约信息的最大数量 */
#define OES_MAX_CRD_DEBT_CONTRACT_ITEM_CNT_PER_PACK         (30)

/** 每条查询应答报文中客户单证券融资融券负债统计信息的最大数量 */
#define OES_MAX_CRD_SECURITY_DEBT_STATS_ITEM_CNT_PER_PACK   (30)

/** 每条查询应答报文中融资融券合约流水信息的最大数量 */
#define OES_MAX_CRD_DEBT_JOURNAL_ITEM_CNT_PER_PACK          (30)

/** 每条查询应答报文中信用资产信息的最大数量 */
#define OES_MAX_CREDIT_ASSET_ITEM_CNT_PER_PACK              (30)

/** 每条查询应答报文中直接还款信息的最大数量 */
#define OES_MAX_CRD_CASH_REPAY_ITEM_CNT_PER_PACK            (30)

/** 每条查询应答报文中资金头寸信息 (可融资头寸信息) 的最大数量 */
#define OES_MAX_CRD_CASH_POSITION_ITEM_CNT_PER_PACK         (30)

/** 每条查询应答报文中证券头寸信息 (可融券头寸信息) 的最大数量 */
#define OES_MAX_CRD_SECURITY_POSITION_ITEM_CNT_PER_PACK     (30)

/** 每条查询应答报文中余券信息的最大数量 */
#define OES_MAX_CRD_EXCESS_STOCK_ITEM_CNT_PER_PACK          (30)

/** 每条查询应答报文中融资融券息费利率的最大数量 */
#define OES_MAX_CRD_INTEREST_RATE_ITEM_CNT_PER_PACK         (50)
/* -------------------------           */


/* ===================================================================
 * 查询融资融券合约信息相关结构体定义
 * =================================================================== */

/**
 * 查询融资融券合约信息过滤条件
 */
typedef struct _OesQryCrdDebtContractFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];
    /** 合约编号, 可选项 */
    char                debtId[OES_CREDIT_DEBT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;

    /** 是否仅查询未了结的融资融券合约 */
    uint8               isUnclosedOnly;
    /** 负债类型 @see eOesCrdDebtTypeT */
    uint8               debtType;
    /** 历史合约标识 (0:未指定, 1:是历史合约, 2:不是历史合约) */
    uint8               historyContractFlag;
    /** 按64位对齐填充域 */
    uint8               __filler[4];

    /** 查询融资融券合约的起始日期 (格式为 YYYYMMDD, 形如 20160830) */
    int32               startDate;
    /** 查询融资融券合约的结束日期 (格式为 YYYYMMDD, 形如 20160830)) */
    int32               endDate;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdDebtContractFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_DEBT_CONTRACT_FILTER        \
        {0}, {0}, {0}, {0}, \
        0, 0, 0, 0, {0}, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询到的融资融券合约信息内容
 */
typedef OesCrdDebtContractReportT   OesCrdDebtContractItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_DEBT_CONTRACT_ITEM              \
        NULLOBJ_OES_CRD_DEBT_CONTRACT_REPORT
/* -------------------------           */


/**
 * 查询融资融券合约信息请求
 */
typedef struct _OesQryCrdDebtContractReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdDebtContractFilterT
                        qryFilter;
} OesQryCrdDebtContractReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_DEBT_CONTRACT_REQ           \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_DEBT_CONTRACT_FILTER}
/* -------------------------           */


/**
 * 查询融资融券合约信息应答
 */
typedef struct _OesQryCrdDebtContractRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 融资融券合约信息数组 */
    OesCrdDebtContractItemT
                        qryItems[OES_MAX_CRD_DEBT_CONTRACT_ITEM_CNT_PER_PACK];
} OesQryCrdDebtContractRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_DEBT_CONTRACT_RSP           \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_DEBT_CONTRACT_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询融资融券合约负债流水相关结构体定义
 * =================================================================== */

/**
 * 查询融资融券合约流水信息过滤条件
 */
typedef struct _OesQryCrdDebtJournalFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];
    /** 合约编号, 可选项 */
    char                debtId[OES_CREDIT_DEBT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 负债类型 @see eOesCrdDebtTypeT */
    uint8               debtType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 查询融资融券合约流水的起始日期 (目前仅支持查询当日流水, 格式为 YYYYMMDD, 形如 20160830) */
    int32               startDate;
    /** 查询融资融券合约流水的结束日期 (格式为 YYYYMMDD, 形如 20160830)) */
    int32               endDate;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdDebtJournalFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_DEBT_JOURNAL_FILTER         \
        {0}, {0}, {0}, {0}, \
        0, 0, {0}, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询到的融资融券合约流水信息内容
 */
typedef struct _OesCrdDebtJournalItem {
    __OES_CRD_DEBT_JOURNAL_BASE_INFO_PKT;

    /** 保留字段 */
    char                __reserve[64];
} OesCrdDebtJournalItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_DEBT_JOURNAL_ITEM               \
        NULLOBJ_OES_CRD_DEBT_JOURNAL_BASE_INFO, \
        {0}
/* -------------------------           */


/*
 * 查询融资融券合约流水信息请求
 */
typedef struct _OesQryCrdDebtJournalReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdDebtJournalFilterT
                        qryFilter;
} OesQryCrdDebtJournalReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_DEBT_JOURNAL_REQ            \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_DEBT_JOURNAL_FILTER}
/* -------------------------           */


/*
 * 查询融资融券合约流水信息应答
 */
typedef struct _OesQryCrdDebtJournalRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 融资融券合约流水信息数组 */
    OesCrdDebtJournalItemT
                        qryItems[OES_MAX_CRD_DEBT_JOURNAL_ITEM_CNT_PER_PACK];
} OesQryCrdDebtJournalRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_DEBT_JOURNAL_RSP            \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_DEBT_JOURNAL_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询客户单证券融资融券负债统计信息相关结构体定义
 * =================================================================== */

/**
 * 查询客户单证券融资融券负债统计信息过滤条件
 */
typedef struct _OesQryCrdSecurityDebtStatsFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];
    /** 市场代码  @see eOesMarketIdT */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdSecurityDebtStatsFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_SECURITY_DEBT_STATS_FILTER  \
        {0}, {0}, {0}, 0, {0}, \
        0
/* -------------------------           */


/**
 * 查询到的客户单证券融资融券负债统计信息内容
 */
typedef OesCrdSecurityDebtStatsBaseInfoT    OesCrdSecurityDebtStatsItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_SECURITY_DEBT_STATS_ITEM        \
        NULLOBJ_OES_CRD_SECURITY_DEBT_STATS_BASE_INFO
/* -------------------------           */


/**
 * 查询客户单证券融资融券负债统计信息请求
 */
typedef struct _OesQryCrdSecurityDebtStatsReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdSecurityDebtStatsFilterT
                        qryFilter;
} OesQryCrdSecurityDebtStatsReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_SECURITY_DEBT_STATS_REQ     \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_SECURITY_DEBT_STATS_FILTER}
/* -------------------------           */


/**
 * 查询客户单证券融资融券负债统计信息应答
 */
typedef struct _OesQryCrdSecurityDebtStatsRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 客户单证券融资融券负债统计信息数组 */
    OesCrdSecurityDebtStatsItemT
                        qryItems[OES_MAX_CRD_SECURITY_DEBT_STATS_ITEM_CNT_PER_PACK];
} OesQryCrdSecurityDebtStatsRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_SECURITY_DEBT_STATS_RSP     \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_SECURITY_DEBT_STATS_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询信用资产信息相关结构体定义
 * =================================================================== */

/**
 * 查询信用资产信息过滤条件
 */
typedef struct _OesQryCrdCreditAssetFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码, 可选项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdCreditAssetFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CREDIT_ASSET_FILTER         \
        {0}, {0}, 0
/* -------------------------           */


/**
 * 查询到的信用资产信息内容
 */
typedef OesCrdCreditAssetBaseInfoT  OesCrdCreditAssetItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_CREDIT_ASSET_ITEM               \
        NULLOBJ_OES_CRD_CREDIT_ASSET_BASE_INFO
/* -------------------------           */


/**
 * 查询信用资产信息请求
 */
typedef struct _OesQryCrdCreditAssetReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdCreditAssetFilterT
                        qryFilter;
} OesQryCrdCreditAssetReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CREDIT_ASSET_REQ            \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_CREDIT_ASSET_FILTER}
/* -------------------------           */


/**
 * 查询信用资产信息应答
 */
typedef struct _OesQryCrdCreditAssetRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 信用资产信息数组 */
    OesCrdCreditAssetItemT
                        qryItems[OES_MAX_CREDIT_ASSET_ITEM_CNT_PER_PACK];
} OesQryCrdCreditAssetRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CREDIT_ASSET_RSP            \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_CREDIT_ASSET_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询融资融券业务直接还款信息相关结构体定义
 * =================================================================== */

/**
 * 查询融资融券业务直接还款信息过滤条件
 */
typedef struct _OesQryCrdCashRepayFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码, 可选项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 直接还款指令流水号, 可选项 */
    int32               clSeqNo;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 按64位对齐填充域 */
    uint8               __filler[3];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdCashRepayFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CASH_REPAY_FILTER           \
        {0}, {0}, \
        0, 0, {0}, \
        0
/* -------------------------           */


/**
 * 查询到的融资融券业务直接还款信息内容
 */
typedef OesCrdCashRepayReportT      OesCrdCashRepayItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_CASH_REPAY_ITEM                 \
        NULLOBJ_OES_CRD_CASH_REPAY_REPORT
/* -------------------------           */


/**
 * 查询融资融券业务直接还款信息请求
 */
typedef struct _OesQryCrdCashRepayReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdCashRepayFilterT
                        qryFilter;
} OesQryCrdCashRepayReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CASH_REPAY_REQ              \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_CASH_REPAY_FILTER}
/* -------------------------           */


/**
 * 查询融资融券业务直接还款信息应答
 */
typedef struct _OesQryCrdCashRepayRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 融资融券业务直接还款信息数组 */
    OesCrdCashRepayItemT
                        qryItems[OES_MAX_CRD_CASH_REPAY_ITEM_CNT_PER_PACK];
} OesQryCrdCashRepayRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CASH_REPAY_RSP              \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_CASH_REPAY_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询融资融券业务资金头寸信息 (可融资头寸信息) 相关结构体定义
 * =================================================================== */

/**
 * 查询资金头寸信息 (可融资头寸信息) 过滤条件
 */
typedef struct _OesQryCrdCashPositionFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码, 可选项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 头寸性质, 可选项 @see eOesCrdCashGroupPropertyT */
    uint8               cashGroupProperty;
    /** 按64位对齐的填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdCashPositionFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CASH_POSITION_FILTER        \
        {0}, {0}, 0, {0}, 0
/* -------------------------           */


/**
 * 查询到的资金头寸信息 (可融资头寸信息) 内容
 */
typedef struct _OesCrdCashPositionItem {
    __OES_CRD_CASH_POSITION_BASE_INFO_PKT;

    /** 资金头寸剩余可融资金额 */
    int64               availableBalance;
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /** 保留字段 */
    char                __reserve[16];
} OesCrdCashPositionItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_CASH_POSITION_ITEM              \
        __NULLOBJ_OES_CRD_CASH_POSITION_BASE_INFO_PKT, \
        0, {0}, \
        {0}
/* -------------------------           */


/**
 * 查询融资融券业务资金头寸信息 (可融资头寸信息) 请求
 */
typedef struct _OesQryCrdCashPositionReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdCashPositionFilterT
                        qryFilter;
} OesQryCrdCashPositionReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CASH_POSITION_REQ           \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_CASH_POSITION_FILTER}


/**
 * 查询融资融券业务资金头寸信息 (可融资头寸信息) 应答
 */
typedef struct _OesQryCrdCashPositionRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 融资融券业务资金头寸信息数组 */
    OesCrdCashPositionItemT
                        qryItems[OES_MAX_CRD_CASH_POSITION_ITEM_CNT_PER_PACK];
} OesQryCrdCashPositionRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_CASH_POSITION_RSP           \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_CASH_POSITION_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询融资融券业务证券头寸信息 (可融券头寸信息) 相关结构体定义
 * =================================================================== */

/**
 * 查询融资融券业务证券头寸信息 (可融券头寸信息) 过滤条件
 */
typedef struct _OesQryCrdSecurityPositionFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码, 可选项 @see eOesMarketIdT */
    uint8               mktId;
    /** 头寸性质, 可选项 @see eOesCrdCashGroupPropertyT */
    uint8               cashGroupProperty;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdSecurityPositionFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_SECURITY_POSITION_FILTER    \
        {0}, {0}, {0}, \
        0, 0, {0}, \
        0
/* -------------------------           */


/**
 * 查询到的证券头寸信息 (可融券头寸信息) 内容
 */
typedef struct _OesCrdSecurityPositionItem {
    __OES_CRD_SECURITY_POSITION_BASE_INFO_PKT;

    /** 当前可用头寸数量 */
    int64               availablePositionQty;
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /** 保留字段 */
    char                __reserve[32];
} OesCrdSecurityPositionItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_SECURITY_POSITION_ITEM          \
        __NULLOBJ_OES_CRD_SECURITY_POSITION_BASE_INFO_PKT, \
        0, {0}, \
        {0}
/* -------------------------           */


/**
 * 查询融资融券业务证券头寸信息 (可融券头寸信息) 请求
 */
typedef struct _OesQryCrdSecurityPositionReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdSecurityPositionFilterT
                        qryFilter;
} OesQryCrdSecurityPositionReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_SECURITY_POSITION_REQ       \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_SECURITY_POSITION_FILTER}
/* -------------------------           */


/**
 * 查询融资融券业务证券头寸信息 (可融券头寸信息) 应答
 */
typedef struct _OesQryCrdSecurityPositionRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 融资融券业务证券头寸信息 (可融券头寸信息) 数组 */
    OesCrdSecurityPositionItemT
                        qryItems[OES_MAX_CRD_SECURITY_POSITION_ITEM_CNT_PER_PACK];
} OesQryCrdSecurityPositionRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_SECURITY_POSITION_RSP       \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_SECURITY_POSITION_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询融资融券业务余券信息相关结构体定义
 * =================================================================== */

/**
 * 查询融资融券业务余券信息过滤条件
 */
typedef struct _OesQryCrdExcessStockFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码, 可选项 @see eOesMarketIdT */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdExcessStockFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_EXCESS_STOCK_FILTER         \
        {0}, {0}, {0}, \
        0, {0}, \
        0
/* -------------------------           */


/**
 * 查询到的余券信息内容
 */
typedef OesCrdExcessStockBaseInfoT  OesCrdExcessStockItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_EXCESS_STOCK_ITEM               \
        NULLOBJ_OES_CRD_EXCESS_STOCK_BASE_INFO
/* -------------------------           */


/**
 * 查询融资融券业务余券信息请求
 */
typedef struct _OesQryCrdExcessStockReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCrdExcessStockFilterT
                        qryFilter;
} OesQryCrdExcessStockReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_EXCESS_STOCK_REQ            \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_EXCESS_STOCK_FILTER}
/* -------------------------           */


/**
 * 查询融资融券业务余券信息应答
 */
typedef struct _OesQryCrdExcessStockRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 融资融券业务余券信息数组 */
    OesCrdExcessStockItemT
                        qryItems[OES_MAX_CRD_EXCESS_STOCK_ITEM_CNT_PER_PACK];
} OesQryCrdExcessStockRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_EXCESS_STOCK_RSP            \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_EXCESS_STOCK_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询融资融券息费利率相关结构体定义
 * =================================================================== */

/**
 * 查询融资融券息费利率过滤条件
 */
typedef struct _OesQryCrdInterestRateFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /**
     * 买卖类型, 可选项。如无需此过滤条件请使用 OES_BS_TYPE_UNDEFINE
     * @see eOesBuySellTypeT
     */
    uint8               bsType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCrdInterestRateFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_INTEREST_RATE_FILTER        \
        {0}, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 融资融券息费利率内容定义
 */
typedef OesCommissionRateItemT      OesCrdInterestRateItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CRD_INTEREST_RATE_ITEM              \
        NULLOBJ_OES_COMMISSION_RATE_ITEM
/* -------------------------           */


/**
 * 查询融资融券息费利率请求
 */
typedef struct _OesQryCrdInterestRateReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryCrdInterestRateFilterT
                            qryFilter;
} OesQryCrdInterestRateReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_INTEREST_RATE_REQ           \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CRD_INTEREST_RATE_FILTER}
/* -------------------------           */


/**
 * 查询融资融券息费利率应答
 */
typedef struct _OesQryCrdInterestRateRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 客户佣金信息数组 */
    OesCrdInterestRateItemT qryItems[OES_MAX_CRD_INTEREST_RATE_ITEM_CNT_PER_PACK];
} OesQryCrdInterestRateRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CRD_INTEREST_RATE_RSP           \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CRD_INTEREST_RATE_ITEM}}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_QRY_CREDIT_PACKETS_H */
