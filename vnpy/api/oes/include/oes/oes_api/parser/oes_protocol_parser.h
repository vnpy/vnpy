/*
 * Copyright 2020 the original author or authors.
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
 * @file    oes_protocol_parser.h
 *
 * 协议转换处理
 *
 * @version 1.2 2016/10/24
 * @since   2014/12/23
 */


#ifndef _OES_PROTOCOL_PARSER_H
#define _OES_PROTOCOL_PARSER_H


#include    <oes_global/oes_packets.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 编码/解码函数声明 （非查询消息）
 * =================================================================== */

/**
 * 请求消息解码处理（解码为二进制结构体，用于接收客户端的请求消息）
 *
 * @param[in,out]   pReqHead    消息头
 * @param           pMsgBody    消息体数据
 * @param[out]      pReqMsgBuf  解码后的消息体数据缓存
 * @param           pRemoteInfo 对端身份信息, 用于打印跟踪日志
 * @return  解码后的消息体数据; NULL：解析失败
 */
OesReqMsgBodyT* OesParser_DecodeReq(
                        SMsgHeadT *pReqHead,
                        const void *pMsgBody,
                        OesReqMsgBodyT *pReqMsgBuf,
                        const char *pRemoteInfo);

/**
 * 应答消息编码处理（编码为JSON等格式，用于向客户端发送应答消息）
 *
 * @param[in,out]   pRspHead        消息头
 * @param           pRspBody        待编码的应答数据
 * @param[out]      pBuf            存储编码后数据的缓存区
 * @param           bufSize         缓存区长度
 * @param           pRemoteInfo     对端身份信息, 用于打印跟踪日志
 * @param           isCopyBinary    对于二进制协议，是否也同样将原始数据复制到缓存区
 * @return  编码后的消息体数据; NULL：编码失败
 */
void*           OesParser_EncodeRsp(
                        SMsgHeadT *pRspHead,
                        const OesRspMsgBodyT *pRspBody,
                        char *pBuf,
                        int32 bufSize,
                        const char *pRemoteInfo,
                        BOOL isCopyBinary);

/**
 * 为执行报告回报特别定制的应答消息编码处理（编码为JSON等格式，用于向客户端发送应答消息）
 *
 * @param[in,out]   pRspHead        消息头
 * @param           pRspBody        待编码的应答数据
 * @param[out]      pBuf            存储编码后数据的缓存区
 * @param           bufSize         缓存区长度
 * @param           pRemoteInfo     对端身份信息, 用于打印跟踪日志
 * @param           isCopyBinary    对于二进制协议，是否也同样将原始数据复制到缓存区
 * @return  编码后的消息体数据; NULL：编码失败
 */
void*           OesParser_EncodeRptSpecial(
                        SMsgHeadT *pRspHead,
                        const OesRptMsgHeadT *pRptMsgHead,
                        const OesRptMsgBodyT *pRptMsgBody,
                        char *pBuf,
                        int32 bufSize,
                        const char *pRemoteInfo,
                        BOOL isCopyBinary);
/* -------------------------           */


/* ===================================================================
 * 编码/解码函数声明 （查询消息）
 * =================================================================== */

/**
 * 查询服务接收消息的解析处理
 *
 * @param   pReqHead    待解析报文头
 * @param   pMsgBody    待解析报文体
 * @param   pQryReq     [out] 解析出来的service请求结构
 * @param   pRemoteInfo 对端身份信息, 用于打印跟踪日志
 * @return  请求消息的结构体; NULL：解析失败，ppErrMsg将指向错误信息
 */
OesQryReqMsgT*  OesParser_DecodeQueryReq(
                        SMsgHeadT *pReqHead,
                        const char *pMsgBody,
                        OesQryReqMsgT *pQryReq,
                        const char *pRemoteInfo);

/**
 * 查询服务构造应答消息处理
 *
 * @param   pRspHead    [in/out]消息头
 * @param   pQryRsp     应答消息结构体
 * @param   pBuf        [out] 存储编码后数据的缓存区
 * @param   bufSize     缓存区长度
 * @param   pRemoteInfo 对端身份信息, 用于打印跟踪日志
 * @return  编码后的消息体数据; NULL：编码失败
 */
void*           OesParser_EncodeQueryRsp(
                        SMsgHeadT *pRspHead,
                        const OesQryRspMsgT *pQryRsp,
                        char *pBuf, int32 bufSize,
                        const char *pRemoteInfo);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_PROTOCOL_PARSER_H */
