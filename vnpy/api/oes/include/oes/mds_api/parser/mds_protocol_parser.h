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
 * @file    mds_protocol_parser.h
 *
 * 协议转换处理
 *
 * @version 1.0 2016/2/20
 * @since   2016/1/3
 */


#ifndef _MDS_PROTOCOL_PARSER_H
#define _MDS_PROTOCOL_PARSER_H


#include    <mds_global/mds_mkt_packets.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 消息编码/解码函数声明
 * =================================================================== */

/*
 * 请求消息编码处理（编码为JSON等格式，用于向服务器发送请求消息）
 */
void*               MdsParser_EncodeReq(
                            SMsgHeadT *pReqHead,
                            const MdsMktReqMsgBodyT *pReqBody,
                            char *pBuf,
                            int32 bufSize,
                            const char *pRemoteInfo);

/*
 * 请求消息解码处理（解码为二进制结构体，用于接收客户端的请求消息）
 */
MdsMktReqMsgBodyT*  MdsParser_DecodeReq(
                            SMsgHeadT *pReqHead,
                            const void *pMsgBody,
                            MdsMktReqMsgBodyT *pReqMsgBuf,
                            const char *pRemoteInfo);

/*
 * 应答消息编码处理（编码为JSON等格式，用于向客户端发送应答消息）
 */
void*               MdsParser_EncodeRsp(
                            SMsgHeadT *pRspHead,
                            const MdsMktRspMsgBodyT *pRspBody,
                            char *pBuf,
                            int32 bufSize,
                            const char *pRemoteInfo,
                            BOOL isCopyBinary);

/*
 * 应答消息解码处理（解码为二进制结构体，用于接收服务器端返回的应答消息）
 */
MdsMktRspMsgBodyT*  MdsParser_DecodeRsp(
                            SMsgHeadT *pRspHead,
                            const void *pMsgBody,
                            MdsMktRspMsgBodyT *pRspMsgBuf,
                            const char *pRemoteInfo);

/*
 * 返回字符串形式的行情数据类型
 */
const char*         MdsParser_GetMdStreamIdString(
                            uint8 exchId,
                            uint8 mdStreamType);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_PROTOCOL_PARSER_H */
