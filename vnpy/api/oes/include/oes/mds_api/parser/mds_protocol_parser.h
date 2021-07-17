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

/**
 * 请求消息编码处理（编码为JSON等格式，用于向服务器发送请求消息）
 *
 * @param[in,out]   pReqHead    消息头
 * @param           pReqBody    待编码的应答数据
 * @param[out]      pBuf        存储编码后数据的缓存区
 * @param           bufSize     缓存区长度
 * @param           pRemoteInfo 对端身份信息, 用于打印跟踪日志
 * @return  编码后的消息体数据; NULL：编码失败
 */
void*               MdsParser_EncodeReq(
                            SMsgHeadT *pReqHead,
                            const MdsMktReqMsgBodyT *pReqBody,
                            char *pBuf,
                            int32 bufSize,
                            const char *pRemoteInfo);

/**
 * 请求消息解码处理（解码为二进制结构体，用于接收客户端的请求消息）
 *
 * @param[in,out]   pReqHead    消息头
 * @param           pMsgBody    消息体数据
 * @param[out]      pReqMsgBuf  解码后的消息体数据缓存
 * @param           pRemoteInfo 对端身份信息, 用于打印跟踪日志
 * @return  解码后的消息体数据; NULL：解析失败
 */
MdsMktReqMsgBodyT*  MdsParser_DecodeReq(
                            SMsgHeadT *pReqHead,
                            const void *pMsgBody,
                            MdsMktReqMsgBodyT *pReqMsgBuf,
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
void*               MdsParser_EncodeRsp(
                            SMsgHeadT *pRspHead,
                            const MdsMktRspMsgBodyT *pRspBody,
                            char *pBuf,
                            int32 bufSize,
                            const char *pRemoteInfo,
                            BOOL isCopyBinary);

/**
 * 应答消息解码处理（解码为二进制结构体，用于接收服务器端返回的应答消息）
 *
 * @param[in,out]   pRspHead    消息头
 * @param           pMsgBody    消息体数据
 * @param[out]      pRspMsgBuf  解码后的消息体数据缓存
 * @param           pRemoteInfo 对端身份信息, 用于打印跟踪日志
 * @return  解码后的消息体数据; NULL：解析失败
 */
MdsMktRspMsgBodyT*  MdsParser_DecodeRsp(
                            SMsgHeadT *pRspHead,
                            const void *pMsgBody,
                            MdsMktRspMsgBodyT *pRspMsgBuf,
                            const char *pRemoteInfo);

/**
 * 返回字符串形式的行情数据类型
 *
 * 上交所 (C5):
 *  - MD001 指数行情数据
 *  - MD002 股票(A、B股)行情数据
 *  - MD003 债券行情数据
 *  - MD004 基金行情数据
 *  - M0301 期权交易行情
 *
 * 深交所 (C3):
 *  - 010   现货(股票,基金,债券等)集中竞价交易快照行情
 *  - 020   质押式回购交易快照行情
 *  - 030   债券分销快照行情 (* 属于综合业务，本系统不处理)
 *  - 040   期权集中竞价交易快照行情 (==> M0301)
 *  - 060   以收盘价交易的盘后定价交易快照行情 (* 属于综合业务，本系统不处理)
 *  - 061   以成交量加权平均价交易的盘后定价交易快照行情 (* 属于综合业务，本系统不处理)
 *  - 900   指数快照行情 (==> MD001)
 *  - 910   成交量统计指标快照行情
 *
 * @param   exchId          交易所代码
 * @param   mdStreamType    行情数据类型
 * @return  行情数据类型字符串
 */
const char*         MdsParser_GetMdStreamIdString(
                            uint8 exchId,
                            uint8 mdStreamType);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_PROTOCOL_PARSER_H */
