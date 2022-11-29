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
 * @file    mds_json_parser.h
 *
 * 行情订阅服务的消息解析处理
 *
 * @version 1.0 2016/2/19
 * @since   2016/1/3
 */


#ifndef _MDS_JSON_PARSER_H
#define _MDS_JSON_PARSER_H


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
void*   MdsJsonParser_EncodeReq(
                SMsgHeadT *pReqHead,
                const MdsMktReqMsgBodyT *pReqBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 请求消息解码处理（用于接收客户端的请求消息） */
MdsMktReqMsgBodyT*
        MdsJsonParser_DecodeReq(
                SMsgHeadT *pReqHead,
                const void *pMsgBody,
                MdsMktReqMsgBodyT *pReqMsgBuf,
                const char *pRemoteInfo);

/* 应答消息编码处理（用于向客户端发送应答消息） */
void*   MdsJsonParser_EncodeRsp(
                SMsgHeadT *pRspHead,
                const MdsMktRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 应答消息编码处理（编码为精简的JSON格式） */
void*   MdsJsonParser_EncodeRspSimplify(
                SMsgHeadT *pRspHead,
                const MdsMktRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 应答消息解码处理（用于接收服务器端返回的应答消息） */
MdsMktRspMsgBodyT*
        MdsJsonParser_DecodeRsp(
                SMsgHeadT *pRspHead,
                const void *pMsgBody,
                MdsMktRspMsgBodyT *pRspMsgBuf,
                const char *pRemoteInfo);
/* -------------------------           */


/* ===================================================================
 * 用于具体数据条目的编码/解码处理的函数声明
 * =================================================================== */

/* 证券静态信息条目的编码处理 */
int32   MdsJsonParser_EncodeStockStaticItem(
                const MdsStockStaticInfoT *pItem,
                char *pBuf,
                int32 bufSize);

/* 期权静态信息条目的编码处理 */
int32   MdsJsonParser_EncodeOptionStaticItem(
                const MdsOptionStaticInfoT *pItem,
                char *pBuf,
                int32 bufSize);

/* 行情快照条目的编码处理 */
int32   MdsJsonParser_EncodeSnapshotListItem(
                const MdsL1SnapshotT *pItem,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_JSON_PARSER_H */
