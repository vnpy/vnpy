/*
 * Copyright 2009-2016 the original author or authors.
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
 * @file    global_packet.h
 *
 * 全局报文定义
 *
 * @version 1.0         2009/10/18
 * @version 1.5         2018/05/03
 *          - 添加新的消息标志:
 *              - SMSG_MSGFLAG_NESTED       嵌套的组合消息 (消息体由一到多条包含消息头的完整消息组成)
 *              - SMSG_MSGFLAG_COMPRESSED   消息体已压缩
 *          - 添加通用的辅助宏定义
 * @since   2009/10/18
 */


#ifndef _SPK_GLOBAL_PACKET_H
#define _SPK_GLOBAL_PACKET_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 消息标志定义
 * =================================================================== */

/**
 * 协议类型, 用于在消息标志中标识消息的协议类型
 */
typedef enum _eSMsgProtocolType {
    SMSG_PROTO_BINARY           = 0x00,     /**< 协议类型-二进制 */
    SMSG_PROTO_JSON             = 0x01,     /**< 协议类型-JSON */
    SMSG_PROTO_FIX              = 0x02,     /**< 协议类型-FIX */
    SMSG_PROTO_PROTOBUF         = 0x03,     /**< 协议类型-ProtocolBuffers */
    __MAX_SMSG_PROTO_TYPE
} eSMsgProtocolTypeT;
/* -------------------------           */


/**
 * 消息标志, 用于在消息标志中标识消息的请求/应答类型
 * 与协议类型复用相同的字段, 通过高4位/低4位进行区分
 */
typedef enum _eSMsgFlag {
    SMSG_MSGFLAG_NONE           = 0x00,     /**< 消息标志-无 */
    SMSG_MSGFLAG_REQ            = 0x00,     /**< 消息标志-请求消息 */
    SMSG_MSGFLAG_RSP            = 0x50,     /**< 消息标志-应答消息 TODO refactor => 0x10 */
    SMSG_MSGFLAG_NESTED         = 0x20,     /**< 消息标志-嵌套的组合消息 (消息体由一到多条包含消息头的完整消息组成) */
    SMSG_MSGFLAG_COMPRESSED     = 0x80,     /**< 消息标志-消息体已压缩 */

    SMSG_MSGFLAG_MASK_RSPFLAG   = 0xF0,     /**< 消息标志掩码-请求/应答标志的掩码 */
    SMSG_MSGFLAG_MASK_PROTOCOL  = 0x0F      /**< 消息标志掩码-协议类型的掩码 */
} eSMsgFlagT;
/* -------------------------           */


/* ===================================================================
 * 通用消息头定义
 * =================================================================== */

/**
 * 通用消息头
 * @see eSMsgFlagT
 */
typedef struct _SMsgHead {
    uint8               msgFlag;            /**< 消息标志 @see eSMsgFlagT */
    uint8               msgId;              /**< 消息代码 */
    uint8               status;             /**< 状态码 */
    uint8               detailStatus;       /**< 明细状态代码 (@note 当消息为嵌套的组合消息时, 复用该字段记录消息体中的消息条数) */
    int32               msgSize;            /**< 消息大小 */
} SMsgHeadT;


/* 消息头尾部填充字段的初始化值定义 (@deprecated 已废弃, 为了兼容而暂时保留) */
#define __NULLOBJ_SPK_MSG_HEAD_TAILER


/* 结构体初始化值定义 */
#define NULLOBJ_SPK_MSG_HEAD                                            \
        0, 0, 0, 0, 0
/* -------------------------           */


/* ===================================================================
 * 通用的辅助宏定义
 * =================================================================== */

/**
 * 返回消息的协议类型
 *
 * @param   msgFlag 消息标志
 * @return  消息的协议类型 @see eSMsgProtocolTypeT
 */
#define SPK_GET_MSG_PROTOCOL_TYPE(msgFlag)                              \
        ( (msgFlag) & SMSG_MSGFLAG_MASK_PROTOCOL )


/**
 * 返回消息的协议类型是否是'BINARY'类型
 *
 * @param   msgFlag 消息标志
 * @return  TRUE 是'BINARY'类型; FALSE 不是'BINARY'类型
 */
#define SPK_IS_MSG_PROTOCOL_BINARY(msgFlag)                             \
        ( SPK_GET_MSG_PROTOCOL_TYPE(msgFlag) == SMSG_PROTO_BINARY )


/**
 * 返回消息的协议类型是否是'JSON'类型
 *
 * @param   msgFlag 消息标志
 * @return  TRUE 是'JSON'类型; FALSE 不是'JSON'类型
 */
#define SPK_IS_MSG_PROTOCOL_JSON(msgFlag)                               \
        ( SPK_GET_MSG_PROTOCOL_TYPE(msgFlag) == SMSG_PROTO_JSON )
/* -------------------------           */


/**
 * 返回消息是否是应答消息
 *
 * @param   msgFlag 消息标志
 * @return  TRUE 是应答消息; FALSE 不是应答消息
 */
#define SPK_HAS_MSG_FLAG_RSP(msgFlag)                                   \
        ( ((msgFlag) & SMSG_MSGFLAG_RSP) == SMSG_MSGFLAG_RSP )


/**
 * 返回消息是否是嵌套的组合消息 (消息体由一到多条包含消息头的完整消息组成)
 *
 * @param   msgFlag 消息标志
 * @return  TRUE 是嵌套的组合消息; FALSE 不是嵌套的组合消息
 */
#define SPK_HAS_MSG_FLAG_NESTED(msgFlag)                                \
        ( ((msgFlag) & SMSG_MSGFLAG_NESTED) == SMSG_MSGFLAG_NESTED )


/**
 * 返回消息是否已压缩
 *
 * @param   msgFlag 消息标志
 * @return  TRUE 已压缩; FALSE 未压缩
 */
#define SPK_HAS_MSG_FLAG_COMPRESSED(msgFlag)                            \
        ( ((msgFlag) & SMSG_MSGFLAG_COMPRESSED) == SMSG_MSGFLAG_COMPRESSED )
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_GLOBAL_PACKET_H */
