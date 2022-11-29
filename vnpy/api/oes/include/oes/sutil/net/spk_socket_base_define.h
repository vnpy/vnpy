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
 * @file    spk_socket_base_define.h
 *
 * Socket公共宏定义等头文件
 *
 * @version 1.0 2013/7/18
 * @since   2004/3/26
 */


#ifndef _SPK_SOCKET_BASE_DEFINE_H
#define _SPK_SOCKET_BASE_DEFINE_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 平台相关的预编译宏设置
 * =================================================================== */

#if defined (__WINDOWS__) || defined (__MINGW__)
#   define  __SPK_INVALID_SOCKET        INVALID_SOCKET
#   define  __SPK_IS_INVALID_SOCKET(s)  ((s) == INVALID_SOCKET)

#else
#   define  __SPK_INVALID_SOCKET        -1
#   define  __SPK_IS_INVALID_SOCKET(s)  ((s) < 0)

#endif


#ifndef TCP_KEEPIDLE
#   if defined (__APPLE__)
#       define  TCP_KEEPIDLE            TCP_KEEPALIVE
#   endif
#endif
/* -------------------------           */


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** IP字符串的最大长度 */
#define SPK_MAX_IP_LEN                  (16)
/** IPv6字符串的最大长度 */
#define SPK_MAX_IPV6_LEN                (40)
/** URI最大长度 */
#define SPK_MAX_URI_LEN                 (128)
/** 通信协议类型名称的最大长度 */
#define SPK_MAX_PROTOCOL_NAME_LEN       (32)
/** 通信协议类型描述的最大长度 */
#define SPK_MAX_PROTOCOL_MEMO_LEN       (64)
/** 十六进制整数格式的MAC地址的字节数 */
#define SPK_MAC_SEGS_CNT                (6)
/** MAC地址字符串的最大长度 */
#define SPK_MAX_MAC_LEN                 (20)
/** MAC地址字符串的最大长度(按64位对齐的长度) */
#define SPK_MAX_MAC_ALGIN_LEN           (24)
/** 设备序列号字符串的最大长度 */
#define SPK_MAX_DRIVER_ID_LEN           (24)

/** 最大同时连接请求数 */
#if defined(__MINGW__) || defined(__CYGWIN__) || defined(__WINDOWS__)
#   define  SPK_MAX_SO_BACKLOG          (128)
#else
#   define  SPK_MAX_SO_BACKLOG          (SOMAXCONN)
#endif

/** 默认的最大同时连接请求数 */
#define SPK_DEFAULT_SO_BACKLOG          SPK_MAX_SO_BACKLOG
/** 默认的接收缓存大小（单位: K） */
#define SPK_DEFAULT_SO_RCVBUF           (1024)
/** 默认的发送缓存大小（单位: K） */
#define SPK_DEFAULT_SO_SNDBUF           (1024)
/** 默认的SO_NODELAY取值 */
#define SPK_DEFAULT_TCP_NODELAY         (1)
/** 默认的SO_REUSEADDR取值 */
#define SPK_DEFAULT_SO_REUSEADDR        (1)

/** 默认的连接操作的超时时间 (毫秒) */
#define SPK_DEFAULT_CONN_TIMEOUT_MS     (10000)
/** 最大的连接操作的超时时间 (毫秒) */
#define SPK_MAX_CONN_TIMEOUT_MS         (60000)

/** 默认的SOCKET超时时间 (毫秒) */
#ifndef SPK_DEFAULT_SO_TIMEOUT_MS
#   define  SPK_DEFAULT_SO_TIMEOUT_MS   (15000)
#endif
/** 常用的较短的SOCKET超时时间 (毫秒) */
#define SPK_SHORT_SO_TIMEOUT_MS         (5000)
/** 常用的最短的SOCKET超时时间 (毫秒) */
#define SPK_SHORTEST_SO_TIMEOUT_MS      (1000)
/** 常用的较长的SOCKET超时时间 (毫秒) */
#define SPK_LONG_SO_TIMEOUT_MS          (30000)
/** 常用的最长的SOCKET超时时间 (毫秒) */
#define SPK_LONGEST_SO_TIMEOUT_MS       (60000)

/** 默认的SO_KEEPALIVE取值 */
#define SPK_DEFAULT_SO_KEEPALIVE        (1)
/** 默认的TCP_KEEPIDLE取值 */
#define SPK_DEFAULT_TCP_KEEPIDLE        (300)
/** 默认的TCP_KEEPINTVL取值 */
#define SPK_DEFAULT_TCP_KEEPINTVL       (30)
/** 默认的TCP_KEEPCNT取值 */
#define SPK_DEFAULT_TCP_KEEPCNT         (9)
/* -------------------------           */


/* ===================================================================
 * 常量定义（枚举类型定义）
 * =================================================================== */

/**
 * 通信协议类型
 */
typedef enum _eSSocketProtocolType {
    SPK_SOCKET_PROTOCOL_TCP             = 0,    /**< 通信协议类型 - TCP */
    SPK_SOCKET_PROTOCOL_IPC             = 1,    /**< 通信协议类型 - IPC (Unix Domain Socket) */
    SPK_SOCKET_PROTOCOL_UDP_UCAST       = 2,    /**< 通信协议类型 - UDP-Unicast */
    SPK_SOCKET_PROTOCOL_UDP_MCAST       = 3,    /**< 通信协议类型 - UDP-Multicast */
    SPK_SOCKET_PROTOCOL_PGM             = 4,    /**< 通信协议类型 - PGM */
    SPK_SOCKET_PROTOCOL_EPGM            = 5,    /**< 通信协议类型 - EPGM */
    __MAX_SPK_SOCKET_PROTOCOL
} eSSocketProtocolTypeT;
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * Socket URI地址信息
 */
typedef struct _SSocketUriInfo {
    /** 地址信息 */
    char                uri[SPK_MAX_URI_LEN];
} SSocketUriInfoT;


/* 结构体初始化值定义 */
#define NULLOBJ_SOCKET_URI_INFO             \
        {0}
/* -------------------------           */


/**
 * Socket IP/Port 地址信息
 */
typedef struct _SSocketIpPortInfo {
    /** 端口号 */
    int32               port;
    /** IP地址 */
    char                ip[SPK_MAX_IP_LEN + 4];
} SSocketIpPortInfoT;


/* 结构体初始化值定义 */
#define NULLOBJ_SOCKET_IP_PORT_INFO         \
        0, {0}
/* -------------------------           */


/**
 * Socket 连接通道信息
 */
typedef struct _SSocketChannelInfo {
    union {
        /** Socket描述符 */
        SPK_SOCKET      socketFd;
        /** 按64位对齐的填充域 */
        uint64          __socket_fd_filler;
    };

    /** 套接字端口号 */
    int32               remotePort;

    /**
     * 通信协议类型
     * @see eSSocketProtocolTypeT
     */
    uint8               protocolType;

    /** 是否使用网络字节序 (TRUE 网络字节序；FALSE 本机字节序) */
    uint8               _isNetByteOrder;

    /** 连接是否已破裂 (用于内部处理) */
    uint8               _isBroken;

    /** 标示异步发送线程的连接是否已破裂 (用于内部处理) */
    uint8               _isSendBroken;

    /** 套接字地址或DomainSocket的路径地址 (仅用于显示) */
    char                remoteAddr[SPK_MAX_URI_LEN];

    /** 连接建立时间 (UTC时间, 即相对于1970年的秒数) */
    int64               connectTime;

    /** 标识是否正在尝试连接的过程中 (用于内部处理) */
    uint8               _isTryConnecting;

    /** 按64位对齐的填充域 */
    uint8               __filler[7];
} SSocketChannelInfoT;


/* 结构体初始化值定义 */
#define NULLOBJ_SOCKET_CHANNEL_INFO         \
        {__SPK_INVALID_SOCKET}, 0, \
        0, 0, 0, 0, {0}, \
        0, 0, {0}
/* -------------------------           */


/**
 * 套接口选项配置
 */
typedef struct _SSocketOptionConfig {
    /** socket SO_RCVBUF size (KB) */
    int32               soRcvbuf;
    /** socket SO_SNDBUF size (KB) */
    int32               soSndbuf;

    /** socket TCP_NODELAY option, 0 or 1 */
    int8                tcpNodelay;
    /** socket TCP_QUICKACK option, 0 or 1 */
    int8                quickAck;

    /** mutilcast TTL number */
    int8                mcastTtlNum;
    /** disable mutilcast loopback, 0 or 1 */
    int8                mcastLoopbackDisabled;

    /** BACKLOG size for listen */
    uint16              soBacklog;
    /** 连接操作(connect)的超时时间 (毫秒) */
    uint16              connTimeoutMs;

    /** socket TCP_KEEPIDLE option, 超时时间(秒) */
    int16               keepIdle;
    /** socket TCP_KEEPINTVL option, 间隔时间(秒) */
    int16               keepIntvl;
    /** socket SO_KEEPALIVE option, 0 or 1 */
    int8                keepalive;
    /** socket TCP_KEEPCNT option, 尝试次数 */
    int8                keepCnt;
    /** 按64位对齐的填充域 */
    int8                __filler[6];

    /** 本地绑定的端口地址 (适用于发送端) */
    int32               localSendingPort;
    /** 本地绑定的网络设备接口的IP地址 (适用于发送端) */
    char                localSendingIp[SPK_MAX_IP_LEN + 4];
    /** 用于组播接收和发送的特定网络设备接口的IP地址 */
    char                mcastInterfaceIp[SPK_MAX_IP_LEN + 4];
} SSocketOptionConfigT;


/* 结构体初始化值定义 */
#define NULLOBJ_SOCKET_OPTION_CONFIG        \
        SPK_DEFAULT_SO_RCVBUF, SPK_DEFAULT_SO_SNDBUF, \
        SPK_DEFAULT_TCP_NODELAY, 0, \
        0, 0, \
        SPK_MAX_SO_BACKLOG, SPK_DEFAULT_CONN_TIMEOUT_MS, \
        SPK_DEFAULT_TCP_KEEPIDLE, SPK_DEFAULT_TCP_KEEPINTVL, \
        SPK_DEFAULT_SO_KEEPALIVE, SPK_DEFAULT_TCP_KEEPCNT, \
        {0}, \
        0, {0}, {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_SOCKET_BASE_DEFINE_H */
