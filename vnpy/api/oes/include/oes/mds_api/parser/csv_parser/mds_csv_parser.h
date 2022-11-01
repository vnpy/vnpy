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
#include    <mds_api/mds_api.h>
#include    <sutil/net/spk_global_packet.h>
#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 函数声明
 * =================================================================== */

/*
 * 请求消息编码处理（编码为JSON格式，用于向服务器发送请求消息）
 *
 * @param[in,out]   pReqHead        消息头
 * @param[in,out]   pReqBody        原始请求数据结构体
 * @param[out]      pBuf            存储编码后数据的缓存区
 * @param           bufSize         缓存区长度
 * @param           pRemoteInfo     对端身份信息, 用于打印跟踪日志
 * @return          编码后的消息体数据; NULL, 编码失败
 */
void*   MdsCsvParser_EncodeReq(
                SMsgHeadT *pReqHead,
                const MdsMktReqMsgBodyT *pReqBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/*
 * 请求消息解码处理（解码为二进制结构体，用于接收客户端的请求消息）
 *
 * @param[in,out]   pReqHead        消息头
 * @param[in]       pMsgBody        消息体数据
 * @param[out]      pReqMsgBuf      解码后的消息体数据缓存
 * @param           pRemoteInfo     对端身份信息, 用于打印跟踪日志
 * @return          解码后的消息体数据; NULL, 解析失败
 */
MdsMktReqMsgBodyT*
        MdsCsvParser_DecodeReq(
                SMsgHeadT *pReqHead,
                const void *pMsgBody,
                MdsMktReqMsgBodyT *pReqMsgBuf,
                const char *pRemoteInfo);

/*
 * 应答消息编码处理（编码为CSV格式，用于向客户端发送应答消息）
 *
 * @param[in,out]   pRspHead        消息头
 * @param[in,out]   pRspBody        原始应答数据结构体
 * @param[out]      pBuf            存储编码后数据的缓存区
 * @param           bufSize         缓存区长度
 * @param           pRemoteInfo     对端身份信息, 用于打印跟踪日志
 * @return          编码后的消息体数据; NULL, 编码失败
 */
void*   MdsCsvParser_EncodeRsp(
                SMsgHeadT *pRspHead,
                const MdsMktRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/*
 * 应答消息解码处理（解码为二进制结构体，用于接收服务器端返回的应答消息）
 *
 * @param[in,out]   pRspHead        消息头
 * @param[in]       pMsgBody        消息体数据
 * @param[out]      pRspMsgBuf      解码后的消息体数据缓存
 * @param           pRemoteInfo     对端身份信息, 用于打印跟踪日志
 * @return          解码后的消息体数据; NULL, 解析失败
 */
MdsMktRspMsgBodyT*
        MdsCsvParser_DecodeRsp(
                SMsgHeadT *pRspHead,
                const void *pMsgBody,
                MdsMktRspMsgBodyT *pRspMsgBuf,
                const char *pRemoteInfo);

/*
 * 返回应答消息编码后的记录格式 (字段列表)
 *
 * @param           msgType         消息类型
 * @param[out]      pBuf            存储编码后数据的缓存区
 * @param           bufSize         缓存区长度
 * @return          字段列表的长度
 */
int32   MdsCsvParser_GetRspFields(
                uint8 msgType,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


/* ===================================================================
 * CVS行情数据文件解析相关的函数声明
 * =================================================================== */

/*
 * 解析CVS格式的行情数据文件
 *
 * @param   pCsvFile            数据文件的路径
 * @param   pOnMsgCallback      进行消息处理的回调函数
 * @param   pCallbackParams     回调函数的参数
 * @return  大于等于0, 成功处理的记录数量;
 *          小于0, 处理失败 (负的错误号)
 */
int32   MdsCsvParser_ParseCsvFile(
                const char *pCsvFile,
                F_MDSAPI_ONMSG_T pOnMsgCallback,
                void *pCallbackParams);

/*
 * 解析完整的CVS格式行情数据记录 (形如: MsgId,value1,value2,... 的CSV行情数据记录)
 *
 * @param[in]       pCsvRecord      CSV格式的完整数据记录
 * @param[out]      pOutMsgHead     输出解码后的消息头数据
 * @param[out]      pOutMsgBuf      输出解码后的消息体数据
 * @return          解码后的消息体数据; NULL, 解析失败
 */
MdsMktRspMsgBodyT*
        MdsCsvParser_DecodeCsvRecord(
                const char *pCsvRecord,
                SMsgHeadT *pOutMsgHead,
                MdsMktRspMsgBodyT *pOutMsgBuf);
/* -------------------------           */


/* ===================================================================
 * 用于具体数据条目的编码/解码处理的函数声明
 * =================================================================== */

/*
 * 证券静态信息条目的编码处理
 *
 * @param[in]   pRspItem    单条证券静态信息
 * @param[out]  pBuf        序列化后数据的缓存区
 * @param[in]   bufSize     缓存区长度
 * @return  序列化后的消息体数据长度
 */
int32   MdsCsvParser_EncodeStockStaticItem(
                const MdsStockStaticInfoT *pItem,
                char *pBuf,
                int32 bufSize);

/*
 * 期权静态信息条目的编码处理
 *
 * @param[in]   pRspItem    单条期权静态信息
 * @param[out]  pBuf        序列化后数据的缓存区
 * @param[in]   bufSize     缓存区长度
 * @return  序列化后的消息体数据长度
 */
int32   MdsCsvParser_EncodeOptionStaticItem(
                const MdsOptionStaticInfoT *pItem,
                char *pBuf,
                int32 bufSize);

/*
 * 行情快照条目的编码处理
 *
 * @param[in]   pRspItem    单条行情快照
 * @param[out]  pBuf        序列化后数据的缓存区
 * @param[in]   bufSize     缓存区长度
 * @return  序列化后的消息体数据长度
 */
int32   MdsCsvParser_EncodeSnapshotListItem(
                const MdsL1SnapshotT *pItem,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_CSV_PARSER_H */
