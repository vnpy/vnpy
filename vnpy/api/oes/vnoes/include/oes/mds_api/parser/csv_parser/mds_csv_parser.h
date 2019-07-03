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
 * @file    mds_csv_parser.h
 *
 * 行情订阅服务的消息解析处理
 *
 * @version 0.15.7.6    2019/01/05
 * @version 0.15.8_u6   2019/05/07
 *          - 调整 CSV 行情数据的输出格式
 *              - 废弃 __origNetTime 字段, 保留字段位置以兼容之前格式, 但字段名称修改为 __zero, 取值固定为0
 *              - 为指数行情增加 __origMdSource 字段
 *
 * @since   2019/01/05
 */


#ifndef _MDS_CSV_PARSER_H
#define _MDS_CSV_PARSER_H


#include    <mds_global/mds_mkt_packets.h>
#include    <sutil/net/spk_global_packet.h>
#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 函数声明
 * =================================================================== */

/* 请求消息编码处理（用于向服务器发送请求消息） */
void*   MdsCsvParser_EncodeReq(
                SMsgHeadT *pReqHead,
                const MdsMktReqMsgBodyT *pReqBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 请求消息解码处理（用于接收客户端的请求消息） */
MdsMktReqMsgBodyT*
        MdsCsvParser_DecodeReq(
                SMsgHeadT *pReqHead,
                const void *pMsgBody,
                MdsMktReqMsgBodyT *pReqMsgBuf,
                const char *pRemoteInfo);

/* 应答消息编码处理（用于向客户端发送应答消息） */
void*   MdsCsvParser_EncodeRsp(
                SMsgHeadT *pRspHead,
                const MdsMktRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 应答消息解码处理（用于接收服务器端返回的应答消息） */
MdsMktRspMsgBodyT*
        MdsCsvParser_DecodeRsp(
                SMsgHeadT *pRspHead,
                const void *pMsgBody,
                MdsMktRspMsgBodyT *pRspMsgBuf,
                const char *pRemoteInfo);

/* 返回应答消息编码后的记录格式 (字段列表) */
int32   MdsCsvParser_GetRspFields(
                uint8 msgType,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


/* ===================================================================
 * 用于具体数据条目的编码/解码处理的函数声明
 * =================================================================== */

/* 证券静态信息条目的编码处理 */
int32   MdsCsvParser_EncodeStockStaticItem(
                const MdsStockStaticInfoT *pItem,
                char *pBuf,
                int32 bufSize);

/* 行情快照条目的编码处理 */
int32   MdsCsvParser_EncodeSnapshotListItem(
                const MdsL1SnapshotT *pItem,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_CSV_PARSER_H */
