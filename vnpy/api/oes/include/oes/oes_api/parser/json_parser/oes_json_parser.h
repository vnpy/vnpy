/*
 * Copyright 2009-2014 the original author or authors.
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
 * @file    oes_json_parser.h
 *
 * 流消息接收处理
 *
 * @version 1.2 2016/10/24
 * @since   2014/12/23
 */


#ifndef _OES_JSON_PARSER_H
#define _OES_JSON_PARSER_H


#include    <oes_global/oes_packets.h>
#include    <sutil/net/spk_global_packet.h>
#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 函数声明
 * =================================================================== */

/* 请求消息解码处理（用于接收客户端的请求消息） */
OesReqMsgBodyT*
        OesJsonParser_DecodeReq(
                SMsgHeadT *pReqHead,
                const void *pMsgBody,
                OesReqMsgBodyT *pReqMsgBuf,
                const char *pRemoteInfo);

/* 应答消息编码处理（用于向客户端发送应答消息） */
void*   OesJsonParser_EncodeRsp(
                SMsgHeadT *pRspHead,
                const OesRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 为执行报告回报特别定制的应答消息编码处理（编码为JSON格式，用于向客户端发送应答消息） */
void*   OesJsonParser_EncodeRptSpecial(
                SMsgHeadT *pRspHead,
                const OesRptMsgHeadT *pRptMsgHead,
                const OesRptMsgBodyT *pRptMsgBody,
                char *pBuf, int32 bufSize,
                const char *pRemoteInfo);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_JSON_PARSER_H */
