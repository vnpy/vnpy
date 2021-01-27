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
 * @file    mds_poc_encoder.h
 *
 * POC测试格式的行情消息编码处理
 *
 * @version 0.15.10.6   2020/04/16
 * @since   0.15.10.6   2020/04/16
 */


#ifndef _MDS_POC_ENCODER_H
#define _MDS_POC_ENCODER_H


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
 * 应答消息编码处理（编码为CSV格式，用于向客户端发送应答消息）
 *
 * @param[in,out]   pRspHead        消息头
 * @param[in,out]   pRspBody        原始应答数据结构体
 * @param[out]      pBuf            存储编码后数据的缓存区
 * @param           bufSize         缓存区长度
 * @param           recordNum       记录号 (文件行号)
 * @param           pClRecvTime     客户端时间戳
 * @return          编码后的消息体数据; NULL, 编码失败
 */
void*   MdsPocEncoder_EncodeRsp(
                SMsgHeadT *pRspHead,
                const MdsMktRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                int32 recordNum,
                const STimespec32T *pClRecvTime);

/*
 * 返回应答消息编码后的记录格式 (字段列表)
 *
 * @param           msgType         消息类型
 * @param[out]      pBuf            存储编码后数据的缓存区
 * @param           bufSize         缓存区长度
 * @return          字段列表的长度
 */
int32   MdsPocEncoder_GetRspFields(
                uint8 msgType,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_POC_ENCODER_H */
