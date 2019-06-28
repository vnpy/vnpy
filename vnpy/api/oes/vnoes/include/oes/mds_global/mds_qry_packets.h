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
 * 查询消息定义
 * =================================================================== */

/**
 * 证券行情查询的请求报文
 */
typedef struct _MdsQryMktDataSnapshotReq {
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               securityType;           /**< 证券类型 @see eMdsSecurityTypeT */
    uint8               __filler[2];            /**< 按64位对齐的填充域 */
    int32               instrId;                /**< 产品代码 */
} MdsQryMktDataSnapshotReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_MKT_DATA_SNAPSHOT_REQ   \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * (深圳)证券实时状态查询的请求报文
 */
typedef MdsQryMktDataSnapshotReqT       MdsQrySecurityStatusReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_SECURITY_STATUS_REQ     \
        NULLOBJ_MDS_QRY_MKT_DATA_SNAPSHOT_REQ
/* -------------------------           */


/**
 * (上证)市场状态查询的请求报文
 */
typedef struct _MdsQryTrdSessionStatusReq {
    uint8               exchId;                 /**< 交易所代码 @see eMdsExchangeIdT */
    uint8               securityType;           /**< 证券类型 @see eMdsSecurityTypeT */
    uint8               __filler[6];            /**< 按64位对齐的填充域 */
} MdsQryTrdSessionStatusReqT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDS_QRY_TRD_SESSION_STATUS_REQ  \
        0, 0, {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_QRY_PACKETS_H */
