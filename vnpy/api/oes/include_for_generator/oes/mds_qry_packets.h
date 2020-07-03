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
 * @file    mds_qry_packets.h
 *
 * 查询消息的报文定义
 *
 * @version 0.8.7 2016/07/30
 * @since   2016/02/10
 */


#ifndef _MDS_QRY_PACKETS_H
#define _MDS_QRY_PACKETS_H


#include    <mds_global/mds_base_model.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 查询应答报文中的最大证券静态信息数量 */
#define MDS_QRYRSP_MAX_STOCK_CNT                (200)
/** 查询应答报文中的最大期权静态信息数量 */
#define MDS_QRYRSP_MAX_OPTION_CNT               (100)
/* -------------------------           */


/* ===================================================================
 * 单条查询的查询消息定义
 * =================================================================== */

/**
 * 证券行情查询的请求报文
 */
typedef struct _MdsQryMktDataSnapshotReq {
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/指数/期权) @see eMdsMdProductTypeT */
    uint8               __filler[2];            /**< 按64位对齐的填充域 */
    int32               instrId;                /**< 产品代码 */
} MdsQryMktDataSnapshotReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_MKT_DATA_SNAPSHOT_REQ           \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * (深圳)证券实时状态查询的请求报文
 */
typedef MdsQryMktDataSnapshotReqT       MdsQrySecurityStatusReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_SECURITY_STATUS_REQ             \
        NULLOBJ_MDS_QRY_MKT_DATA_SNAPSHOT_REQ
/* -------------------------           */


/**
 * (上证)市场状态查询的请求报文
 */
typedef struct _MdsQryTrdSessionStatusReq {
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/指数/期权) @see eMdsMdProductTypeT */
    uint8               __filler[6];            /**< 按64位对齐的填充域 */
} MdsQryTrdSessionStatusReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_TRD_SESSION_STATUS_REQ          \
        0, 0, {0}
/* -------------------------           */


/* ===================================================================
 * 批量查询的查询消息头定义
 * =================================================================== */

/**
 * 查询请求的消息头定义
 */
typedef struct _MdsQryReqHeadT {
    int32               maxPageSize;            /**< 最大分页大小 */
    int32               lastPosition;           /**< 查询起始位置 */
} MdsQryReqHeadT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_REQ_HEAD                        \
        0, 0
/* -------------------------           */


/**
 * 查询应答的消息头定义
 */
typedef struct _MdsQryRspHeadT {
    int32               itemCount;              /**< 查询到的信息条目数 */
    int32               lastPosition;           /**< 查询到的最后一条信息的位置 */

    int8                isEnd;                  /**< 是否是当前查询最后一个包 */
    uint8               __filler[7];            /**< 按64位对齐填充域 */

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} MdsQryRspHeadT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_RSP_HEAD                        \
        0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查询定位的游标结构
 */
typedef struct _MdsQryCursor {
    /** 查询位置 */
    int32               seqNo;

    /** 是否是当前最后一个包 */
    int8                isEnd;
    /** 按64位对齐填充域 */
    int8                __filler[3];

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} MdsQryCursorT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_CURSOR                          \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 行情查询请求中的证券代码信息
 */
typedef struct _MdsQrySecurityCodeEntry {
    int32               instrId;                /**< 产品代码 */
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/期权/指数) @see eMdsMdProductTypeT */
    uint8               __filler[2];            /**< 按64位对齐的填充域 */
} MdsQrySecurityCodeEntryT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_SECURITY_CODE_ENTRY             \
        0, 0, 0, {0}
/* -------------------------           */


/* ===================================================================
 * 证券静态信息查询相关结构体定义
 * =================================================================== */

/**
 * 证券静态信息查询的过滤条件定义
 */
typedef struct _MdsQryStockStaticInfoFilter {
    /** 产品代码 C6 / C8 (如: '600000' 等) */
    char                securityId[MDS_MAX_POSTFIXED_INSTR_CODE_LEN];
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               oesSecurityType;        /**< 证券类型 (股票/债券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 证券子类型 @see eOesSubSecurityTypeT */
    uint8               __filler[5];            /**< 按64位对齐的填充域 */
    int32               instrId;                /**< 产品代码 (转换为整数类型的产品代码)
                                                     如果同时指定 securityId, 则优先使用 securityId */

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} MdsQryStockStaticInfoFilterT;


/**
 * 证券静态信息查询的请求报文
 */
typedef struct _MdsQryStockStaticInfoReq {
    /** 查询请求的消息头 */
    MdsQryReqHeadT      reqHead;
    /** 查询请求的过滤条件 */
    MdsQryStockStaticInfoFilterT
                        qryFilter;
} MdsQryStockStaticInfoReqT;


/**
 * 证券静态信息查询的应答报文
 */
typedef struct _MdsQryStockStaticInfoRsp {
    /** 查询应答的消息头 */
    MdsQryRspHeadT      rspHead;
    /** 证券静态信息数组 (最大大小为 MDS_QRYRSP_MAX_STOCK_CNT) */
    MdsStockStaticInfoT qryItems[1];
} MdsQryStockStaticInfoRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_FILTER        \
        {0}, 0, 0, 0, {0}, 0, \
        0

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_REQ           \
        {NULLOBJ_MDS_QRY_REQ_HEAD}, \
        {NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_FILTER}

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_RSP           \
        {NULLOBJ_MDS_QRY_RSP_HEAD}, \
        {{NULLOBJ_MDS_STOCK_STATIC_INFO}}
/* -------------------------           */


/**
 * 期权合约静态信息查询的过滤条件定义
 */
typedef struct _MdsQryOptionStaticInfoFilter {
    /** 产品代码 C6 / C8 (如: '600000' 等) */
    char                securityId[MDS_MAX_POSTFIXED_INSTR_CODE_LEN];
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               oesSecurityType;        /**< 证券类型 (股票/债券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 证券子类型 @see eOesSubSecurityTypeT */
    uint8               __filler[5];            /**< 按64位对齐的填充域 */
    int32               instrId;                /**< 产品代码 (转换为整数类型的产品代码)
                                                     如果同时指定 securityId, 则优先使用 securityId */

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} MdsQryOptionStaticInfoFilterT;


/**
 * 期权合约静态信息查询的请求报文
 */
typedef struct _MdsQryOptionStaticInfoReq {
    /** 查询请求的消息头 */
    MdsQryReqHeadT      reqHead;
    /** 查询请求的过滤条件 */
    MdsQryOptionStaticInfoFilterT
                        qryFilter;
} MdsQryOptionStaticInfoReqT;


/**
 * 期权合约静态信息查询的应答报文
 */
typedef struct _MdsQryOptionStaticInfoRsp {
    /** 查询应答的消息头 */
    MdsQryRspHeadT      rspHead;
    /** 期权合约静态信息数组 (最大大小为 MDS_QRYRSP_MAX_STOCK_CNT) */
    MdsOptionStaticInfoT
                        qryItems[1];
} MdsQryOptionStaticInfoRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_OPTION_STATIC_INFO_FILTER       \
        {0}, 0, 0, 0, {0}, 0, \
        0

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_OPTION_STATIC_INFO_REQ          \
        {NULLOBJ_MDS_QRY_REQ_HEAD}, \
        {NULLOBJ_MDS_QRY_OPTION_STATIC_INFO_FILTER}

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_OPTION_STATIC_INFO_RSP          \
        {NULLOBJ_MDS_QRY_RSP_HEAD}, \
        {{NULLOBJ_MDS_OPTION_STATIC_INFO}}
/* -------------------------           */


/* ===================================================================
 * 快照信息查询相关结构体定义
 * =================================================================== */

/**
 * 行情快照信息查询的过滤条件定义
 */
typedef struct _MdsQrySnapshotListFilter {
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情类别 (股票/期权/指数) @see eMdsMdProductTypeT */
    uint8               oesSecurityType;        /**< 证券类型 (股票/债券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 证券子类型 @see eOesSubSecurityTypeT */
    uint8               mdLevel;                /**< 行情数据级别 (Level1 / Level2) @see eMdsMdLevelT */
    uint8               __filler[11];           /**< 按64位对齐的填充域 */

    /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
    int64               userInfo;
} MdsQrySnapshotListFilterT;


/**
 * 行情快照信息查询的请求报文
 */
typedef struct _MdsQrySnapshotListReq {
    /** 查询请求的消息头 */
    MdsQryReqHeadT      reqHead;
    /** 查询请求的过滤条件 */
    MdsQrySnapshotListFilterT
                        qryFilter;

    /** 待查询的证券代码数量 */
    int32               securityCodeCnt;
    /**< 按64位对齐的填充域 */
    int32               __filler;
    /** 待查询的证券代码列表 (最大大小为 MDS_QRYRSP_MAX_STOCK_CNT) */
    MdsQrySecurityCodeEntryT
                        securityCodeList[1];
} MdsQrySnapshotListReqT;


/**
 * 行情快照信息查询的应答报文
 */
typedef struct _MdsQrySnapshotListRsp {
    /** 查询应答的消息头 */
    MdsQryRspHeadT      rspHead;
    /** 五档快照信息数组 (最大大小为 MDS_QRYRSP_MAX_STOCK_CNT) */
    MdsL1SnapshotT      qryItems[1];
} MdsQrySnapshotListRspT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_SNAPSHOT_LIST_FILTER            \
        0, 0, 0, 0, 0, {0}, \
        0

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_SNAPSHOT_LIST_REQ               \
        {NULLOBJ_MDS_QRY_REQ_HEAD}, \
        {NULLOBJ_MDS_QRY_SNAPSHOT_LIST_FILTER}, \
        0, 0, \
        {{NULLOBJ_MDS_QRY_SECURITY_CODE_ENTRY}}

/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_SNAPSHOT_LIST_RSP               \
        {NULLOBJ_MDS_QRY_RSP_HEAD}, \
        {{NULLOBJ_MDS_L1_SNAPSHOT}}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_QRY_PACKETS_H */
