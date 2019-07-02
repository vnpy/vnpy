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
 * @file    oes_qry_packets.h
 *
 * 查询消息的报文定义
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 增加客户信息查询功能
 *          - ETF成分股查询应答中增加成分股所属ETF申赎代码
 *          - 佣金查询应答中增加客户代码
 *          - 在登录报文中增加协议版本号信息, 并在登录时校验协议版本号的兼容性
 * @version 0.12.1      2016/12/19
 *          - 整合查询消息中的qryCnt、position等字段, 成为一个新的结构体 OesQryHeadT
 * @version 0.12.3      2017/01/10
 *          - OesHoldItemT 结构体拆分成 OesStkHoldingItemT、OesOptHoldingItemT两个结构体
 *          - 持仓查询相关结构体拆分成股票持仓查询、期权持仓查询专用的结构体
 * @version 0.12.3.5    2017/02/20
 *          - 佣金查询过滤条件中新增一条“证券子类型”的过滤条件
 * @version 0.12.6.2    2017/03/16
 *          - '查询出入金流水信息过滤条件' 中重命名 cashSeqNo => clSeqNo
 *          - 调整查询到的 '出入金流水信息' 结构 (与出入金委托执行回报结构一致)
 *          - 调整佣金查询结果中feeRate字段的精度, 当佣金计算模式为 '按金额' 时,
 *            feeRate 字段所代表的比率单位由 '十万分之一' => '百万分之一'
 * @version 0.12.8.2    2017/05/09
 *          - 客户资金信息(OesCashAssetItemT)中添加字段 '当前冲正金额(红冲蓝补的资金净额, reversalAmt)'
 * @version 0.12.8.2    2017/05/16
 *          - 新增 '证券发行信息查询' 相关报文定义
 *              - 新增字段 查询证券发行信息过滤条件(OesQryIssueFilterT)
 *              - 新增字段 证券发行信息内容(OesIssueItemT)
 *              - 新增字段 查询证券发行信息请求(OesQryIssueReqT)
 *              - 新增字段 查询证券发行信息应答(OesQryIssueRspT)
 * @version 0.12.9_RC1  2017/06/05
 *          - 调整佣金查询结果中feeRate字段的精度, 当佣金计算模式为 '按份数' 时,
 *              feeRate 字段所代表的比率单位由 '万分之一' => '百万分之一'
 * @version 0.15.1      2017/06/26
 *          - '委托查询的过滤条件(OesQryOrdFilterT)' 中
 *              - 新增字段 委托的起始时间(startTime) 和 委托的结束时间(endTime)
 *          - '成交查询的过滤条件(OesQryTrdFilterT)' 中
 *              - 新增字段 成交的起始时间(startTime) 和 成交的结束时间(endTime)
 *          - '持仓查询的返回信息(OesStkHoldingItemT)' 中新增字段 总持仓(sumHld)
 *          - '资金查询的返回信息(OesCashAssetItemT)' 中
 *              - 新增字段 当前余额(currentBal)
 *              - 字段重命名 当前可用余额(tradeAvlAmt => currentAvailableBal)
 *              - 字段重命名 当前可取余额(withdrawAvlAmt => currentDrawableBal)
 * @version 0.15.2      2017/07/18
 *          - 新增 '新股认购、中签信息查询' 相关报文定义
 *              - 新增字段 查询新股认购、中签信息过滤条件(OesQryLotWinningFilterT)
 *              - 新增字段 新股认购、中签信息内容(OesLotWinningItemT)
 *              - 新增字段 查询新股认购、中签信息请求(OesQryLotWinningReqT)
 *              - 新增字段 查询新股认购、中签信息应答(OesQryLotWinningRspT)
 * @version 0.15.4      2017/09/04
 *          - 查询请求中消息头的类型由 'OesQryHeadT' 改为 'OesQryReqHeadT'
 *          - 查询应答中消息头的类型由 'OesQryHeadT' 改为 'OesQryRspHeadT'
 *          - 删除 'OesQryHeadT' 类型定义
 *          - '委托信息查询结果 (OesOrdItemT)' 中增加字段:
 *              - 客户端编号 (clientId)
 *              - 客户端环境号 (clEnvId)
 *              - 原始订单的客户委托流水号 (origClSeqNo)
 *              - 原始订单的客户端环境号 (origClEnvId)
 *              - 交易所订单编号 (exchOrdId)
 *          - '成交信息查询结果 (OesTrdItemT)' 中增加字段:
 *              - 客户端编号 (clientId)
 *              - 客户端环境号 (clEnvId)
 *          - '股票持仓信息 (OesStkHoldingItemT)' 中增加字段:
 *              - 持仓成本 (costAmount)
 *              - 持仓成本价 (costPrice)
 *          - 整理以下结构体定义, 调整了字段顺序, 并删除了个别字段
 *              - 现货产品信息查询结果 (OesStockItemT)
 *              - 期权产品信息查询结果 (OesOptionItemT)
 *              - 证券账户信息查询结果 (OesInvAcctItemT)
 *          - 所有的查询过滤条件(OesQryXXXFilterT) 中增加 userInfo字段,
 *              此字段会在对应的查询应答消息(OesQryXXXRspT) 的应答头中原样带回
 * @version 0.15.5      2017/11/03
 *          - 调整查询应答报文中携带查询数据的最大条目数量
 *          - 调整 '查询请求消息头(OesQryReqHeadT)' 中部分字段：
 *              - '查询窗口大小'字段重命名 pageSize => maxPageSize
 *              - '查询起始位置'字段重命名 position => lastPosition
 *          - 调整 '查询应答消息头(OesQryRspHeadT)' 中部分字段：
 *              - '查询到的信息条目数'字段重命名 itemCnt => itemCount
 *              - '查询到的最后一条信息的位置'字段重命名 position => lastPosition
 *          - 调整 '查询应答消息头(OesQryRspHeadT)' 中部分字段：
 *              - '查询到的信息条目数'字段重命名 itemCnt => itemCount
 *              - '查询到的最后一条信息的位置'字段重命名 position => lastPosition
 *          - '股票持仓信息 (OesStkHoldingItemT)' 结构体中增加字段:
 *              - 证券类型 (securityType)
 *              - 证券子类型 (subSecurityType)
 *          - 调整 '资金信息(OesCashAssetItemT)' 中部分字段:
 *              - '当前余额'字段重命名 currentBal => currentTotalBal
 * @version 0.15.5.2    2018/01/29
 *          - 修正 '佣金查询结果 (OesCommissionRateItemT)' 中 feeRate 字段精度描述不正确的问题
 * @version 0.15.5.6    2018/04/01
 *          - 新增 '市场状态信息查询' 相关报文定义
 *              - 新增字段 查询市场状态信息过滤条件(OesQryMarketStateFilterT)
 *              - 新增字段 市场状态信息内容(OesMarketStateItemT)
 *              - 新增字段 查询市场状态信息请求(OesQryMarketStateReqT)
 *              - 新增字段 查询市场状态信息应答(OesQryMarketStateRspT)
 * @version 0.15.5.14   2018/08/01
 *          - '现货产品信息查询过滤条件(OesQryStockFilterT)' 中新增字段:
 *              - 证券类别(securityType)
 *              - 证券子类别(subSecurityType)
 * @version 0.15.5.16   2018/08/31
 *          - 新增 '查询客户端总览信息' 相关报文定义
 *              - 新增 股东账户总览信息(OesInvAcctOverviewT)
 *              - 新增 资金账户总览信息(OesCashAcctOverviewT)
 *              - 新增 客户总览信息(OesCustOverviewT)
 *              - 新增 客户端总览信息(OesClientOverviewT)
 *              - 新增 主柜资金信息(OesCounterCashItemT)
 *          - 新增 '查询主柜资金信息' 相关报文定义
 *              - 新增 查询主柜资金信息请求(OesQryCounterCashReqT)
 *              - 新增 查询主柜资金信息应答(OesQryCounterCashRspT)
 *              - 新增 主柜资金信息内容(OesCounterCashItemT)
 *          - '客户资金信息内容(OesCashAssetItemT)' 中新增 是否禁止出入金(isFundTrsfDisabled) 字段
 *          - '证券账户信息内容(OesInvAcctItemT)' 中新增 是否禁止交易(isTradeDisabled) 字段
 * @version 0.15.5.16_u3 2018/09/28
 *          - 调整成交信息(OesTrdItemT)的结构体字段
 *              - 调整 v0.15.5.16 版本新增的 '证券子类别(subSecurityType)' 字段的位置
 *              - 增加 '原始委托数量(origOrdQty)' 和 '原始委托价格(origOrdPrice)' 字段
 * @version 0.15.6.14   2018/08/01
 *          - '委托查询的过滤条件(OesQryOrdFilterT)' 中
 *              - 新增字段 证券类别(securityType) 和 买卖类型(bsType)
 *          - '成交查询的过滤条件(OesQryTrdFilterT)' 中
 *              - 新增字段 证券类别(securityType) 和 买卖类型(bsType)
 *          - '股票持仓查询的过滤条件(OesQryStkHoldingFilterT)' 中
 *              - 新增字段 证券类别(securityType)
 * @version 0.15.7.6   2018/11/03
 *          - '证券发行信息查询的过滤条件(OesQryIssueFilterT)' 中
 *              - 新增字段 '产品类型 (productType)'
 *          - '查询股票持仓信息过滤条件(OesQryStkHoldingFilterT)' 中
 *              - 新增字段 '产品类型 (productType)'
 * @version 0.15.9      2019/03/12
 *          - 为了支持科创板, 扩展以下查询结果 (兼容之前版本的API)
 *              - 证券账户信息 (OesInvAcctItemT) 中增加如下字段:
 *                  - 科创板权益 (kcSubscriptionQuota)
 *              - 现货产品信息 (OesStockItemT) 中增加如下字段:
 *                  - 限价买数量上限 (lmtBuyMaxQty)
 *                  - 限价买数量下限 (lmtBuyMinQty)
 *                  - 限价卖数量上限 (lmtSellMaxQty)
 *                  - 限价卖数量下限 (lmtSellMinQty)
 *                  - 市价买数量上限 (mktBuyMaxQty)
 *                  - 市价买数量下限 (mktBuyMinQty)
 *                  - 市价卖数量上限 (mktSellMaxQty)
 *                  - 市价卖数量下限 (mktSellMinQty)
 *              - 客户端总览信息中的股东账户总览 (OesInvAcctOverviewT) 中增加如下字段:
 *                  - 科创板权益 (kcSubscriptionQuota)
 *
 * @since   2015/07/30
 */


#ifndef _OES_QRY_PACKETS_H
#define _OES_QRY_PACKETS_H


#include    <oes_global/oes_base_model.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 每条查询应答报文中委托信息的最大数量 */
#define OES_MAX_ORD_ITEM_CNT_PER_PACK               (30)

/** 每条查询应答报文中成交信息的最大数量 */
#define OES_MAX_TRD_ITEM_CNT_PER_PACK               (30)

/** 每条查询应答报文中客户资金信息的最大数量 */
#define OES_MAX_CASH_ASSET_ITEM_CNT_PER_PACK        (30)

/** 每条查询应答报文中持仓信息的最大数量 */
#define OES_MAX_HOLDING_ITEM_CNT_PER_PACK           (30)

/** 每条查询应答报文中客户信息的最大数量 */
#define OES_MAX_CUST_ITEM_CNT_PER_PACK              (30)

/** 每条查询应答报文中证券账户信息的最大数量 */
#define OES_MAX_INV_ACCT_ITEM_CNT_PER_PACK          (30)

/** 每条查询应答报文中客户佣金信息的最大数量 */
#define OES_MAX_COMMS_RATE_ITEM_CNT_PER_PACK        (50)

/** 每条查询应答报文中出入金流水记录的最大数量 */
#define OES_MAX_FUND_TRSF_ITEM_CNT_PER_PACK         (30)

/** 每条查询应答报文中新股认购、中签信息的最大数量 */
#define OES_MAX_LOG_WINNING_ITEM_CNT_PER_PACK       (30)

/** 每条查询应答报文中证券发行信息的最大数量 */
#define OES_MAX_ISSUE_ITEM_CNT_PER_PACK             (30)

/** 每条查询应答报文中现货产品信息的最大数量 */
#define OES_MAX_STOCK_ITEM_CNT_PER_PACK             (30)

/** 每条查询应答报文中ETF申赎产品信息的最大数量 */
#define OES_MAX_ETF_ITEM_CNT_PER_PACK               (30)

/** 每条查询应答报文中ETF成分股的最大数量 */
#define OES_MAX_ETF_COMPONENT_ITEM_CNT_PER_PACK     (30)

/** 每条查询应答报文中期权产品的最大数量 */
#define OES_MAX_OPTION_ITEM_CNT_PER_PACK            (30)

/** 每条查询应答报文中市场状态的最大数量 */
#define OES_MAX_MKT_STATE_ITEM_CNT_PER_PACK         (30)

/** 客户端对应的最大客户数量 */
#define OES_MAX_CUST_PER_CLIENT                     (1)
/* -------------------------           */


/* ===================================================================
 * 查询消息头相关结构体定义
 * =================================================================== */

/**
 * 查询定位的游标结构
 */
typedef struct _OesQryCursor {
    /** 查询位置 */
    int32               seqNo;

    /** 是否是当前最后一个包 */
    int8                isEnd;
    /** 按64位对齐填充域 */
    int8                __filler[3];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCursorT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CURSOR                      \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询请求的消息头定义
 */
typedef struct _OesQryReqHead {
    /** 查询窗口大小 */
    int32               maxPageSize;
    /** 查询起始位置 */
    int32               lastPosition;
} OesQryReqHeadT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_REQ_HEAD                    \
        0, 0
/* -------------------------           */


/**
 * 查询应答的消息头定义
 */
typedef struct _OesQryRspHead {
    /** 查询到的信息条目数 */
    int32               itemCount;
    /** 查询到的最后一条信息的位置 */
    int32               lastPosition;

    /** 是否是当前查询最后一个包 */
    int8                isEnd;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryRspHeadT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_RSP_HEAD                    \
        0, 0, 0, {0}, 0
/* -------------------------           */


/* ===================================================================
 * 查询委托信息相关结构体定义
 * =================================================================== */

/**
 * 查询委托信息过滤条件
 */
typedef struct _OesQryOrdFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 是否仅查询未关闭委托 (包括未全部成交或撤销的委托) */
    uint8               isUnclosedOnly;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 买卖类型  @see eOesBuySellTypeT */
    uint8               bsType;
    /** 按64位对齐填充域 */
    uint8               __filler[3];

    /** 客户委托编号, 可选项 */
    int64               clOrdId;
    /** 客户委托流水号, 可选项 */
    int64               clSeqNo;

    /** 查询委托的起始时间 (格式为 HHMMSSsss, 比如 141205000 表示 14:12:05.000) */
    int32               startTime;
    /** 查询委托的结束时间 (格式为 HHMMSSsss, 比如 141205000 表示 14:12:05.000) */
    int32               endTime;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOrdFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ORD_FILTER                  \
        {0}, {0}, \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询到的委托信息内容
 */
typedef OesOrdCnfmT     OesOrdItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ORD_ITEM                        \
        NULLOBJ_OES_ORD_CNFM
/* -------------------------           */


/**
 * 查询委托信息请求
 */
typedef struct _OesQryOrdReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryOrdFilterT    qryFilter;
} OesQryOrdReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ORD_REQ                     \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ORD_FILTER}
/* -------------------------           */


/**
 * 查询委托信息应答
 */
typedef struct _OesQryOrdRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 委托信息数组 */
    OesOrdItemT         qryItems[OES_MAX_ORD_ITEM_CNT_PER_PACK];
} OesQryOrdRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ORD_RSP                     \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ORD_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询成交信息相关结构体定义
 * =================================================================== */

/**
 * 查询成交信息过滤条件
 */
typedef struct _OesQryTrdFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 买卖类型  @see eOesBuySellTypeT */
    uint8               bsType;
    /** 按64位对齐填充域 */
    uint32              __filler;

    /** 内部委托编号, 可选项 */
    int64               clOrdId;
    /** 客户委托流水号, 可选项 */
    int64               clSeqNo;

    /** 成交开始时间 (格式为 HHMMSSsss, 形如 141205000) */
    int32               startTime;
    /** 成交结束时间 */
    int32               endTime;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryTrdFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRD_FILTER                  \
        {0}, {0}, \
        0, 0, 0, 0, 0, \
        0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询到的成交信息内容
 */
typedef OesTrdCnfmT     OesTrdItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_TRD_ITEM                        \
        NULLOBJ_OES_TRD_CNFM
/* -------------------------           */


/**
 * 查询成交信息请求
 */
typedef struct _OesQryTrdReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryTrdFilterT    qryFilter;
} OesQryTrdReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRD_REQ                     \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_TRD_FILTER}


/**
 * 查询成交信息应答
 */
typedef struct _OesQryTrdRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 成交信息数组 */
    OesTrdItemT         qryItems[OES_MAX_TRD_ITEM_CNT_PER_PACK];
} OesQryTrdRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRD_RSP                     \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_TRD_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询客户资金信息相关结构体定义
 * =================================================================== */

/**
 * 查询客户资金信息过滤条件
 */
typedef struct _OesQryCashAssetFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码, 可选项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCashAssetFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CASH_ASSET_FILTER           \
        {0}, {0}, 0
/* -------------------------           */


/**
 * 客户资金信息内容
 */
typedef struct _OesCashAssetItem {
    __OES_CASH_ASSET_BASE_INFO_PKT;

    /**
     * 当前余额, 包括当前可用余额和在途冻结资金在內的汇总值
     * 可用余额请参考“当前可用余额(currentAvailableBal)”字段
     */
    int64               currentTotalBal;
    /** 当前可用余额 */
    int64               currentAvailableBal;
    /** 当前可取余额 */
    int64               currentDrawableBal;
} OesCashAssetItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CASH_ASSET_ITEM                 \
        __NULLOBJ_OES_CASH_ASSET_BASE_INFO_PKT, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询客户资金信息请求
 */
typedef struct _OesQryCashAssetReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryCashAssetFilterT  qryFilter;
} OesQryCashAssetReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CASH_ASSET_REQ              \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CASH_ASSET_FILTER}
/* -------------------------           */


/**
 * 查询客户资金信息应答
 */
typedef struct _OesQryCashAssetRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 客户资金信息数组 */
    OesCashAssetItemT   qryItems[OES_MAX_CASH_ASSET_ITEM_CNT_PER_PACK];
} OesQryCashAssetRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CASH_ASSET_RSP              \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CASH_ASSET_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询资金信息相关结构体定义
 * =================================================================== */

/**
 * 主柜资金信息内容
 */
typedef struct _OesCounterCashItem {
    /** 资金账户代码 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 客户姓名 */
    char                custName[OES_CUST_NAME_MAX_LEN];
    /** 银行代码 */
    char                bankId[OES_BANK_NO_MAX_LEN];

    uint8               cashType;               /**< 资金账户类别 @see eOesCashTypeT */
    uint8               cashAcctStatus;         /**< 资金账户状态 @see eOesAcctStatusT */
    uint8               currType;               /**< 币种类型 @see eOesCurrTypeT */
    uint8               isFundTrsfDisabled;     /**< 出入金是否禁止标识 */
    uint8               __filler[4];            /**< 按64位对齐填充域 */

    int64               counterAvailableBal;    /**< 主柜可用余额，单位精确到元后四位，即1元 = 10000 */
    int64               counterDrawableBal;     /**< 主柜可取余额，单位精确到元后四位，即1元 = 10000 */
    int64               counterCashUpdateTime;  /**< 主柜资金更新时间 (seconds since the Epoch) */

    int64               __reserve[4];           /**< 保留字段 */
} OesCounterCashItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_COUNTER_CASH_ITEM               \
        {0}, {0}, {0}, {0}, \
        0, 0, 0, 0, {0}, \
        0, 0, 0, {0}
/* -------------------------           */


/**
 * 查询主柜资金信息请求
 */
typedef struct _OesQryCounterCashReq {
    /** 资金账号, 必输项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
} OesQryCounterCashReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COUNTER_CASH_REQ            \
        {0}
/* -------------------------           */


/**
 * 查询主柜资金信息应答
 */
typedef struct _OesQryCounterCashRsp {
    /** 主柜资金信息 */
    OesCounterCashItemT counterCashItem;
} OesQryCounterCashRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COUNTER_CASH_RSP            \
        {NULLOBJ_OES_COUNTER_CASH_ITEM}
/* -------------------------           */


/* ===================================================================
 * 查询股票持仓信息相关结构体定义
 * =================================================================== */

/**
 * 查询股票持仓信息过滤条件
 */
typedef struct _OesQryStkHoldingFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场代码  @see eOesMarketIdT */
    uint8               mktId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 产品类型 @see eOesProductTypeT */
    uint8               productType;
    /** 按64位对齐填充域 */
    uint8               __filler[5];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryStkHoldingFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STK_HOLDING_FILTER          \
        {0}, {0}, {0}, \
        0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询到的股票持仓信息内容
 */
typedef struct _OesStkHoldingItem {
    __OES_STK_HOLDING_BASE_INFO_PKT;

    /** 当前可卖持仓 */
    int64               sellAvlHld;
    /** 当前可转换付出持仓 */
    int64               trsfOutAvlHld;
    /** 当前可锁定持仓 */
    int64               lockAvlHld;
    /** 当前可用于备兑的现货持仓, 可解锁的锁定持仓数量与此相同 */
    int64               coveredAvlHld;
    /**
     * 总持仓, 包括当前可用持仓、不可交易持仓和在途冻结持仓在內的汇总值
     * 可卖持仓请参考“当前可卖持仓(sellAvlHld)”字段
     */
    int64               sumHld;
    /** 持仓成本价 */
    int64               costPrice;
} OesStkHoldingItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_STK_HOLDING_ITEM                \
        __NULLOBJ_OES_STK_HOLDING_BASE_INFO_PKT, \
        0, 0, 0, 0, 0, 0
/* -------------------------           */


/**
 * 查询股票持仓信息请求
 */
typedef struct _OesQryStkHoldingReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryStkHoldingFilterT     qryFilter;
} OesQryStkHoldingReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STK_HOLDING_REQ             \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_STK_HOLDING_FILTER}
/* -------------------------           */


/**
 * 查询股票持仓信息应答
 */
typedef struct _OesQryStkHoldingRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          qryHead;
    /** 持仓信息数组 */
    OesStkHoldingItemT      qryItems[OES_MAX_HOLDING_ITEM_CNT_PER_PACK];
} OesQryStkHoldingRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STK_HOLDING_RSP             \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_STK_HOLDING_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询期权持仓信息相关结构体定义
 * =================================================================== */

/**
 * 查询期权持仓信息过滤条件
 */
typedef OesQryStkHoldingFilterT     OesQryOptHoldingFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_FILTER          \
        NULLOBJ_OES_QRY_STK_HOLDING_FILTER
/* -------------------------           */


/**
 * 查询到的期权持仓信息内容
 */
typedef struct _OesOptHoldingItem {
    __OES_OPT_HOLDING_BASE_INFO_PKT;
} OesOptHoldingItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_HOLDING_ITEM                \
        __NULLOBJ_OES_OPT_HOLDING_BASE_INFO_PKT
/* -------------------------           */


/**
 * 查询期权持仓信息请求
 */
typedef struct _OesQryOptHoldingReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryOptHoldingFilterT     qryFilter;
} OesQryOptHoldingReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_REQ             \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPT_HOLDING_FILTER}
/* -------------------------           */


/**
 * 查询期权持仓信息应答
 */
typedef struct _OesQryHoldRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 持仓信息数组 */
    OesOptHoldingItemT      qryItems[OES_MAX_HOLDING_ITEM_CNT_PER_PACK];
} OesQryOptHoldingRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_RSP             \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPT_HOLDING_ITEM}}
/* -------------------------           */



/* ===================================================================
 * 查询客户信息相关结构体定义
 * =================================================================== */

/**
 * 查询客户信息过滤条件
 */
typedef struct _OesQryCustFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCustFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CUST_FILTER                 \
        {0}, 0
/* -------------------------           */


/**
 * 客户信息内容
 */
typedef OesCustBaseInfoT    OesCustItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CUST_ITEM                       \
        NULLOBJ_OES_CUST_BASE_INFO
/* -------------------------           */


/**
 * 查询客户信息请求
 */
typedef struct _OesQryCustReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryCustFilterT   qryFilter;
} OesQryCustReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CUST_REQ                    \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CUST_FILTER}
/* -------------------------           */


/**
 * 查询客户信息应答
 */
typedef struct _OesQryCustRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 客户信息数组 */
    OesCustItemT        qryItems[OES_MAX_CUST_ITEM_CNT_PER_PACK];
} OesQryCustRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_CUST_RSP                    \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CUST_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询证券账户信息相关结构体定义
 * =================================================================== */

/**
 * 查询证券账户信息过滤条件
 */
typedef struct _OesQryInvAcctFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryInvAcctFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_INV_ACCT_FILTER             \
        {0}, {0}, \
        0, {0}, 0
/* -------------------------           */


/**
 * 证券账户内容
 */
typedef struct _OesInvAcctItem {
    __OES_INV_ACCT_BASE_INFO_PKT;

    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
} OesInvAcctItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_INV_ACCT_ITEM                   \
        __NULLOBJ_OES_INV_ACCT_BASE_INFO_PKT, \
        {0}
/* -------------------------           */


/**
 * 查询证券账户信息请求
 */
typedef struct _OesQryInvAcctReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryInvAcctFilterT    qryFilter;
} OesQryInvAcctReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_INV_ACCT_REQ                \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_INV_ACCT_FILTER}
/* -------------------------           */


/**
 * 查询证券账户信息应答
 */
typedef struct _OesQryInvAcctRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 证券账户信息数组 */
    OesInvAcctItemT     qryItems[OES_MAX_INV_ACCT_ITEM_CNT_PER_PACK];
} OesQryInvAcctRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_INV_ACCT_RSP                \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_INV_ACCT_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询客户端总览信息相关结构体定义
 * =================================================================== */

/**
 * 股东账户总览信息内容
 */
typedef struct _OesInvAcctOverview {
    /** 股东账户代码 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 市场 @see eOesMarketIdT */
    uint8               mktId;

    /** 账户类型 @see eOesAcctTypeT */
    uint8               acctType;
    /** 账户状态 @see eOesAcctStatusT */
    uint8               status;
    /** 股东账户的所有者类型 @see eOesOwnerTypeT */
    uint8               ownerType;
    /** 期权投资者级别 @see eOesOptInvLevelT */
    uint8               optInvLevel;
    /** 是否禁止交易 (仅供API查询使用) */
    uint8               isTradeDisabled;
    /** 按64位对齐填充域 */
    uint8               __INV_ACCT_BASE_filler[2];

    /** 证券账户权限限制 @see eOesTradingLimitT */
    uint64              limits;
    /** 股东权限/客户权限 @see eOesTradingPermissionT */
    uint64              permissions;

    /** 席位号 */
    int32               pbuId;
    /** 主板权益 (新股/配股认购限额) */
    int32               subscriptionQuota;

    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];

    uint8               isValid;                /**< 股东账户是否有效标识 */
    uint8               __filler[3];            /**< 按64位字节对齐的填充域 */
    int32               kcSubscriptionQuota;    /**< 科创板权益 (新股/配股认购限额) */

    int32               trdOrdCnt;              /**< 当日累计有效交易类委托笔数统计 */
    int32               nonTrdOrdCnt;           /**< 当日累计有效非交易类委托笔数统计 */
    int32               cancelOrdCnt;           /**< 当日累计有效撤单笔数统计 */
    int32               oesRejectOrdCnt;        /**< 当日累计被OES拒绝的委托笔数统计 */
    int32               exchRejectOrdCnt;       /**< 当日累计被交易所拒绝的委托笔数统计 */
    int32               trdCnt;                 /**< 当日累计成交笔数统计 */

    int64               __reserve;              /**< 备用字段 */
} OesInvAcctOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_INV_ACCT_OVERVIEW                       \
        {0}, 0, \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, \
        {0}, \
        0, {0}, 0, \
        0, 0, 0, 0, 0, 0, \
        0
/* -------------------------           */


/**
 * 资金账户总览信息内容
 */
typedef struct _OesCashAcctOverview {
    /** 资金账户代码 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 银行代码 */
    char                bankId[OES_BANK_NO_MAX_LEN];

    uint8               isValid;                /**< 资金账户是否有效标识 */
    uint8               cashType;               /**< 资金账户类别 @see eOesCashTypeT */
    uint8               cashAcctStatus;         /**< 资金账户状态 @see eOesAcctStatusT */
    uint8               currType;               /**< 币种类型 @see eOesCurrTypeT */
    uint8               isFundTrsfDisabled;     /**< 出入金是否禁止标识 */
    uint8               __filler[3];            /**< 按64位对齐的填充域 */

    int64               __reserve;              /**< 备用字段 */
} OesCashAcctOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CASH_ACCT_OVERVIEW                       \
        {0}, {0}, {0}, \
        0, 0, 0, 0, 0, {0}, \
        0
/* -------------------------           */


/**
 * 客户总览信息内容
 */
typedef struct _OesCustOverview {
    __OES_CUST_BASE_INFO_PKT;

    /** 客户姓名 */
    char                    custName[OES_CUST_NAME_MAX_LEN];

    OesCashAcctOverviewT    spotCashAcct;           /**< 普通资金账户信息 */
    OesCashAcctOverviewT    creditCashAcct;         /**< 信用资金账户信息 */
    OesCashAcctOverviewT    optionCashAcct;         /**< 衍生品资金账户信息 */

    OesInvAcctOverviewT     shSpotInvAcct;          /**< 上海现货股东账户信息 */
    OesInvAcctOverviewT     shOptionInvAcct;        /**< 上海衍生品股东账户信息 */
    OesInvAcctOverviewT     szSpotInvAcct;          /**< 深圳现货股东账户信息 */
    OesInvAcctOverviewT     szOptionInvAcct;        /**< 深圳衍生品股东账户信息 */

    int64                   __reserve;              /**< 备用字段 */
} OesCustOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CUST_OVERVIEW                       \
        __NULLOBJ_OES_CUST_BASE_INFO_PKT, {0}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        0
/* -------------------------           */


/**
 * 客户端总览信息内容
 */
typedef struct _OesClientOverview {
    int16               clientId;               /**< 客户端编号 */
    uint8               clientType;             /**< 客户端类型  @see eOesClientTypeT */
    uint8               clientStatus;           /**< 客户端状态  @see eOesClientStatusT */
    uint8               isApiForbidden;         /**< API禁用标识 */
    uint8               isBlockTrader;          /**< 是否大宗交易标识 */
    uint8               __filler[2];            /**< 按64位字节对齐的填充域 */
    int64               logonTime;              /**< 客户端登录(委托接收服务)时间 */

    /** 客户端名称 */
    char                clientName[OES_CLIENT_NAME_MAX_LEN];
    /** 客户端说明 */
    char                clientMemo[OES_CLIENT_DESC_MAX_LEN];

    int32               sseStkPbuId;            /**< 上海现货/信用账户对应的PBU代码 */
    int32               sseOptPbuId;            /**< 上海衍生品账户对应的PBU代码 */
    uint8               sseQualificationClass;  /**< 上海股东账户的投资者适当性管理分类 @see eOesQualificationClassT */
    uint8               __filler2[7];           /**< 按64位对齐填充域 */

    int32               szseStkPbuId;           /**< 深圳现货/信用账户对应的PBU代码 */
    int32               szseOptPbuId;           /**< 深圳衍生品账户对应的PBU代码 */
    uint8               szseQualificationClass; /**< 深圳股东账户的投资者适当性管理分类 @see eOesQualificationClassT */
    uint8               __filler3[7];           /**< 按64位对齐填充域 */

    int32               currOrdConnected;       /**< 当前已连接的委托通道数量 */
    int32               currRptConnected;       /**< 当前已连接的回报通道数量 */
    int32               currQryConnected;       /**< 当前已连接的查询通道数量 */
    int32               maxOrdConnect;          /**< 委托通道允许的最大同时连接数量 */
    int32               maxRptConnect;          /**< 回报通道允许的最大同时连接数量 */
    int32               maxQryConnect;          /**< 查询通道允许的最大同时连接数量 */

    int32               ordTrafficLimit;        /**< 委托通道的流量控制 */
    int32               qryTrafficLimit;        /**< 查询通道的流量控制 */
    int64               __reserve;              /**< 备用字段 */

    int32               associatedCustCnt;      /**< 客户端关联的客户数量 */
    int32               __filler4;              /**< 按64位字节对齐的填充域 */

    /** 客户端关联的客户列表 */
    OesCustOverviewT    custItems[OES_MAX_CUST_PER_CLIENT];
} OesClientOverviewT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CLIENT_OVERVIEW                       \
        0, 0, 0, 0, 0, {0}, 0, \
        {0}, {0}, \
        0, 0, 0, {0}, \
        0, 0, 0, {0}, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, \
        {{NULLOBJ_OES_CUST_OVERVIEW}}
/* -------------------------           */


/* ===================================================================
 * 查询客户佣金信息相关结构体定义
 * =================================================================== */

/**
 * 查询客户佣金信息过滤条件
 */
typedef struct _OesQryCommissionRateFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /**
     * 证券类别, 可选项。如无需此过滤条件请使用 OES_SECURITY_TYPE_UNDEFINE
     * @see eOesSecurityTypeT
     */
    uint8               securityType;
    /**
     * 买卖类型, 可选项。如无需此过滤条件请使用 OES_BS_TYPE_UNDEFINE
     * @see eOesBuySellTypeT
     */
    uint8               bsType;
    /** 按64位对齐填充域 */
    uint8               __filler[5];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryCommissionRateFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_FILTER      \
        {0}, 0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 客户佣金信息内容定义
 */
typedef struct _OesCommissionRateItem {
    /** 客户代码 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券代码 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市场 @see eOesMarketIdT */
    uint8               mktId;
    /** 证券类别 @see eOesSecurityTypeT */
    uint8               securityType;
    /** 证券子类别 @see eOesSubSecurityTypeT */
    uint8               subSecurityType;
    /** 买卖类型 @see eOesBuySellTypeT */
    uint8               bsType;

    /** 费用标识 @see eOesFeeTypeT */
    uint8               feeType;
    /** 币种 @see eOesCurrTypeT */
    uint8               currType;
    /** 计算模式 @see eOesCalcFeeModeT */
    uint8               calcFeeMode;
    /** 按64位对齐填充域 */
    uint8               __filler;

    /** 费率, 单位精确到千万分之一, 即费率0.02% = 2000 */
    int64               feeRate;
    /** 最低费用, 大于0时有效 (单位：万分之一元) */
    int32               minFee;
    /** 最高费用, 大于0时有效 (单位：万分之一元) */
    int32               maxFee;
} OesCommissionRateItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_COMMISSION_RATE_ITEM            \
        {0}, {0}, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查询客户佣金信息请求
 */
typedef struct _OesQryCommissionRateReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryCommissionRateFilterT qryFilter;
} OesQryCommissionRateReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_REQ         \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_COMMISSION_RATE_FILTER}
/* -------------------------           */


/**
 * 查询客户佣金信息应答
 */
typedef struct _OesQryCommissionRateRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 客户佣金信息数组 */
    OesCommissionRateItemT  qryItems[OES_MAX_COMMS_RATE_ITEM_CNT_PER_PACK];
} OesQryCommissionRateRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_RSP         \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_COMMISSION_RATE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询出入金流水信息相关结构体定义
 * =================================================================== */

/**
 * 查询出入金流水信息过滤条件
 */
typedef struct _OesQryFundTransferSerialFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 资金账户代码, 可选项 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 出入金流水号, 可选项 */
    int32               clSeqNo;
    /** 客户端环境号 */
    int8                clEnvId;
    /** 按64位对齐填充域 */
    uint8               __filler[3];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryFundTransferSerialFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_FILTER \
        {0}, {0}, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询出入金流水信息应答
 */
typedef OesFundTrsfReportT      OesFundTransferSerialItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_FUND_TRANSFER_SERIAL_ITEM       \
        NULLOBJ_OES_FUND_TRSF_REPORT
/* -------------------------           */


/**
 * 查询出入金流水信息请求
 */
typedef struct _OesQryFundTransferSerialReq {
    /** 查询请求消息头 */
    OesQryReqHeadT                  reqHead;
    /** 查询过滤条件 */
    OesQryFundTransferSerialFilterT qryFilter;
} OesQryFundTransferSerialReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_REQ    \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_FILTER}
/* -------------------------           */


/**
 * 查询出入金流水信息应答
 */
typedef struct _OesQryFundTransferSerialRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT              rspHead;
    /** 出入金流水信息数组 */
    OesFundTransferSerialItemT  qryItems[OES_MAX_FUND_TRSF_ITEM_CNT_PER_PACK];
} OesQryFundTransferSerialRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_RSP    \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_FUND_TRANSFER_SERIAL_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询新股配号、中签信息相关结构体定义
 * =================================================================== */

/**
 * 查询新股配号、中签信息过滤条件
 */
typedef struct _OesQryLotWinningFilter {
    /** 客户代码, 可选项 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 证券账户代码, 可选项 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /**
     * 查询记录类型, 可选项。如无需此过滤条件请使用 OES_LOT_TYPE_UNDEFINE
     * @see eOesLotTypeT
     */
    uint8               lotType;
    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 查询起始日期 (格式为 YYYYMMDD) */
    int32               startDate;
    /** 查询结束日期 (格式为 YYYYMMDD) */
    int32               endDate;

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryLotWinningFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_LOT_WINNING_FILTER          \
        {0}, {0}, \
        0, 0, {0}, \
        0, 0, 0
/* -------------------------           */


/**
 * 新股配号、中签信息内容
 */
typedef OesLotWinningBaseInfoT      OesLotWinningItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_LOT_WINNING_ITEM                \
        NULLOBJ_OES_LOT_WINNING_BASE_INFO
/* -------------------------           */


/**
 * 查询新股认购、中签信息请求
 */
typedef struct _OesQryLotWinningReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryLotWinningFilterT     qryFilter;
} OesQryLotWinningReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_LOT_WINNING_REQ             \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_LOT_WINNING_FILTER}
/* -------------------------           */


/**
 * 查询新股配号、中签信息应答
 */
typedef struct _OesQryLotWinningRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 新股认购、中签信息数组 */
    OesLotWinningItemT      qryItems[OES_MAX_LOG_WINNING_ITEM_CNT_PER_PACK];
} OesQryLotWinningRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_LOT_WINNING_RSP             \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_LOT_WINNING_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询证券发行信息相关结构体定义
 * =================================================================== */

/**
 * 查询证券发行信息过滤条件
 */
typedef struct _OesQryIssueFilter {
    /** 证券发行代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;

    /**
     * 产品类型, 默认类型为 OES_PRODUCT_TYPE_IPO
     * @see eOesProductTypeT
     */
    uint8               productType;

    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryIssueFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ISSUE_FILTER                \
        {0}, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 证券发行信息内容
 */
typedef OesIssueBaseInfoT   OesIssueItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ISSUE_ITEM                      \
        NULLOBJ_OES_ISSUE_BASE_INFO
/* -------------------------           */


/**
 * 查询证券发行信息请求
 */
typedef struct _OesQryIssueReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryIssueFilterT  qryFilter;
} OesQryIssueReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ISSUE_REQ                   \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ISSUE_FILTER}
/* -------------------------           */


/**
 * 查询证券发行信息应答
 */
typedef struct _OesQryIssueRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 证券发行信息数组 */
    OesIssueItemT       qryItems[OES_MAX_ISSUE_ITEM_CNT_PER_PACK];
} OesQryIssueRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ISSUE_RSP                   \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ISSUE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询现货产品信息相关结构体定义
 * =================================================================== */

/**
 * 查询现货产品信息过滤条件
 */
typedef struct _OesQryStockFilter {
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 证券类别  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 证券子类别  @see eOesSubSecurityTypeT */
    uint8               subSecurityType;
    /** 按64位对齐填充域 */
    uint8               __filler[5];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryStockFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STOCK_FILTER                \
        {0}, 0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 现货产品信息内容
 */
typedef OesStockBaseInfoT       OesStockItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_STOCK_ITEM                      \
        NULLOBJ_OES_STOCK_BASE_INFO
/* -------------------------           */


/**
 * 查询现货产品信息请求
 */
typedef struct _OesQryStockReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryStockFilterT  qryFilter;
} OesQryStockReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STOCK_REQ                   \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_STOCK_FILTER}
/* -------------------------           */


/**
 * 查询现货产品信息应答
 */
typedef struct _OesQryStockRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 现货产品信息数组 */
    OesStockItemT       qryItems[OES_MAX_STOCK_ITEM_CNT_PER_PACK];
} OesQryStockRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_STOCK_RSP                   \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_STOCK_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询ETF申赎产品信息相关结构体定义
 * =================================================================== */

/**
 * 查询ETF申赎产品信息过滤条件
 */
typedef struct _OesQryEtfFilter {
    /** 基金代码, 可选项 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryEtfFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_FILTER                  \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * ETF申赎产品信息内容
 */
typedef OesEtfBaseInfoT     OesEtfItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ETF_ITEM                        \
        NULLOBJ_OES_ETF_BASE_INFO
/* -------------------------           */


/**
 * 查询ETF申赎产品信息请求
 */
typedef struct _OesQryEtfReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryEtfFilterT    qryFilter;
} OesQryEtfReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_REQ                     \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ETF_FILTER}
/* -------------------------           */


/**
 * 查询ETF申赎产品信息应答
 */
typedef struct _OesQryEtfRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** ETF申赎产品信息数组 */
    OesEtfItemT         qryItems[OES_MAX_ETF_ITEM_CNT_PER_PACK];
} OesQryEtfRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_RSP                     \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ETF_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询Etf成分股信息相关结构体定义
 * =================================================================== */

/**
 * 查询Etf成分股信息过滤条件
 */
typedef struct _OesQryEtfComponentFilter {
    /** ETF基金代码, 必填项 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryEtfComponentFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_FILTER        \
        {0}, 0
/* -------------------------           */


/**
 * EtfComponent成分股信息内容
 */
typedef struct _OesEtfComponentItem {
    /** Etf成分股代码 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];
    /** 市场代码 @see eOesMarketIdT */
    uint8               mktId;
    /** 现金替代标识 @see eOesEtfSubFlagT */
    uint8               subFlag;
    /** 证券类型 @see eOesSecurityTypeT */
    uint8               securityType;
    /** 证券子类型 @see eOesSubSecurityTypeT */
    uint8               subSecurityType;

    /** 昨日收盘价格 */
    int32               prevClose;
    /** 成分证券数量 */
    int32               qty;
    /** 溢价比例, 单位精确到十万分之一, 即溢价比例10% = 10000 */
    int32               premiumRate;

    /** 申购替代金额, 单位精确到元后四位, 即1元 = 10000 */
    int64               creationSubCash;
    /** 赎回替代金额, 单位精确到元后四位, 即1元 = 10000 */
    int64               redemptionCashSub;
    /** 成分股所属ETF的基金代码 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];
} OesEtfComponentItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_ETF_COMPONENET_ITEM             \
        {0}, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, {0}
/* -------------------------           */


/**
 * 查询EtfComponent成分股信息请求
 */
typedef struct _OesQryEtfComponentReq {
    /** 查询请求消息头 */
    OesQryReqHeadT              reqHead;
    /** 查询过滤条件 */
    OesQryEtfComponentFilterT   qryFilter;
} OesQryEtfComponentReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_REQ           \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ETF_COMPONENT_FILTER}
/* -------------------------           */


/**
 * 查询EtfComponent成分股信息应答
 */
typedef struct _OesQryEtfComponentRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** EtfComponent成分股信息数组 */
    OesEtfComponentItemT
                        qryItems[OES_MAX_ETF_COMPONENT_ITEM_CNT_PER_PACK];
} OesQryEtfComponentRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_RSP           \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ETF_COMPONENET_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询期权产品信息相关结构体定义
 * =================================================================== */

/**
 * 查询期权产品信息过滤条件
 */
typedef struct _OesQryOptionFilter {
    /** 证券代码, 可选项 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市场代码, 可选项。如无需此过滤条件请使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位对齐填充域 */
    uint8               __filler[7];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryOptionFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPTION_FILTER               \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * 期权产品信息内容
 */
typedef OesOptionBaseInfoT      OesOptionItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPTION_ITEM                     \
        NULLOBJ_OES_OPTION_BASE_INFO
/* -------------------------           */


/**
 * 查询期权产品信息请求
 */
typedef struct _OesQryOptionReq {
    /** 查询请求消息头 */
    OesQryReqHeadT      reqHead;
    /** 查询过滤条件 */
    OesQryOptionFilterT qryFilter;
} OesQryOptionReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPTION_REQ                  \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPTION_FILTER}
/* -------------------------           */


/**
 * 查询期权产品信息应答
 */
typedef struct _OesQryOptionRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT      rspHead;
    /** 期权产品信息数组 */
    OesOptionItemT      qryItems[OES_MAX_OPTION_ITEM_CNT_PER_PACK];
} OesQryOptionRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_OPTION_RSP                  \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPTION_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查询当前交易日信息相关结构体定义
 * =================================================================== */

/**
 * 查询当前交易日信息应答
 */
typedef struct _OesQryTradingDayRsp {
    /** 交易日 */
    int32               tradingDay;
    /** 按64位对齐填充域 */
    int32               __filler;
} OesQryTradingDayRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_TRADING_DAY_RSP             \
        0, 0
/* -------------------------           */


/* ===================================================================
 * 查询市场状态信息相关结构体定义
 * =================================================================== */

/**
 * 查询市场状态信息过滤条件
 */
typedef struct _OesQryMarketStateFilter {
    /**
     * 交易所代码 (可选项, 为 0 则匹配所有交易所)
     * @see eOesExchangeIdT
     */
    uint8               exchId;

    /**
     * 交易平台代码 (可选项, 为 0 则匹配所有交易平台)
     * @see eOesPlatformIdT
     */
    uint8               platformId;

    /** 按64位对齐填充域 */
    uint8               __filler[6];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} OesQryMarketStateFilterT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_MARKET_STATE_FILTER             \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 市场状态信息内容
 *
 */
typedef OesMarketStateInfoT     OesMarketStateItemT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_MARKET_STATE_ITEM                   \
        NULLOBJ_OES_MARKET_STATE_INFO
/* -------------------------           */


/**
 * 查询市场状态信息请求
 */
typedef struct _OesQryMarketStateReq {
    /** 查询请求消息头 */
    OesQryReqHeadT          reqHead;
    /** 查询过滤条件 */
    OesQryMarketStateFilterT
                            qryFilter;
} OesQryMarketStateReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_MARKET_STATE_REQ                \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_MARKET_STATE_FILTER}
/* -------------------------           */


/**
 * 查询市场状态信息应答
 */
typedef struct _OesQryMarketStateRsp {
    /** 查询应答消息头 */
    OesQryRspHeadT          rspHead;
    /** 市场状态信息数组 */
    OesMarketStateItemT     qryItems[OES_MAX_MKT_STATE_ITEM_CNT_PER_PACK];
} OesQryMarketStateRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_MARKET_STATE_RSP                \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_MARKET_STATE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 统一的查询消息定义
 * =================================================================== */

/**
 * 统一的查询请求消息定义
 */
typedef union _OesQryReqMsg {
    OesQryOrdReqT                   qryOrd;             /**< 查询委托信息请求 */
    OesQryTrdReqT                   qryTrd;             /**< 查询成交信息请求 */
    OesQryCashAssetReqT             qryCashAsset;       /**< 查询客户资金信息请求 */
    OesQryStkHoldingReqT            qryStkHolding;      /**< 查询股票持仓信息请求 */
    OesQryOptHoldingReqT            qryOptHolding;      /**< 查询期权持仓信息请求 */
    OesQryCustReqT                  qryCust;            /**< 查询客户信息请求 */
    OesQryInvAcctReqT               qryInvAcct;         /**< 查询证券账户请求 */
    OesQryCommissionRateReqT        qryComms;           /**< 查询客户佣金信息请求 */
    OesQryFundTransferSerialReqT    qryFundTrsf;        /**< 查询出入金信息请求 */
    OesQryLotWinningReqT            qryLotWinning;      /**< 查询新股配号、中签信息请求 */
    OesQryIssueReqT                 qryIssue;           /**< 查询证券发行信息请求 */
    OesQryStockReqT                 qryStock;           /**< 查询现货产品信息请求 */
    OesQryEtfReqT                   qryEtf;             /**< 查询ETF申赎产品信息请求 */
    OesQryEtfComponentReqT          qryEtfComponent;    /**< 查询ETF成分股信息请求 */
    OesQryOptionReqT                qryOption;          /**< 查询期权产品信息请求 */
    OesQryMarketStateReqT           qryMktState;        /**< 查询市场状态信息请求 */
    OesQryCounterCashReqT           qryCounterCash;     /**< 查询主柜资金信息请求 */
} OesQryReqMsgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_REQ_MSG                         \
        {NULLOBJ_OES_QRY_ORD_REQ}
/* -------------------------           */


/**
 * 统一的查询应答消息定义
 */
typedef union _OesQryRspMsg {
    OesQryOrdRspT                   ordRsp;             /**< 查询委托信息应答 */
    OesQryTrdRspT                   trdRsp;             /**< 查询成交信息应答 */
    OesQryCashAssetRspT             cashAssetRsp;       /**< 查询客户资金信息应答 */
    OesQryStkHoldingRspT            stkHoldingRsp;      /**< 查询股票持仓信息应答 */
    OesQryOptHoldingRspT            optHoldingRsp;      /**< 查询期权持仓信息应答 */
    OesQryCustRspT                  custRsp;            /**< 查询客户信息应答W */
    OesQryInvAcctRspT               invAcctRsp;         /**< 查询证券账户应答 */
    OesQryCommissionRateRspT        commsRateRsp;       /**< 查询客户佣金信息应答 */
    OesQryFundTransferSerialRspT    fundTrsfRsp;        /**< 查询出入金流水信息应答 */
    OesQryLotWinningRspT            lotWinningRsp;      /**< 查询新股配号、中签信息应答 */
    OesQryIssueRspT                 issueRsp;           /**< 查询证券发行信息应答 */
    OesQryStockRspT                 stockRsp;           /**< 查询现货产品信息应答 */
    OesQryEtfRspT                   etfRsp;             /**< 查询ETF申赎产品信息应答 */
    OesQryEtfComponentRspT          etfComponentRsp;    /**< 查询ETF成分股信息应答 */
    OesQryOptionRspT                optionRsp;          /**< 查询期权产品信息应答 */
    OesQryTradingDayRspT            tradingDay;         /**< 查询当前交易日信息应答 */
    OesQryMarketStateRspT           mktStateRsp;        /**< 查询市场状态信息应答 */
    OesClientOverviewT              clientOverview;     /**< 客户端总览信息 */
    OesQryCounterCashRspT           counterCashRsp;     /**< 客户主柜资金信息 */
} OesQryRspMsgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_RSP_MSG                         \
        {NULLOBJ_OES_QRY_ORD_RSP}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_QRY_PACKETS_H */
