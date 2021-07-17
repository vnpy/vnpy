/*
 * Copyright 2019 the original author or authors.
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
 * @file    spk_general_endpoint_define.h
 *
 * 通用的通信端点组件定义
 *
 * @version 1.0 2019/12/15
 * @since   2019/12/15
 */


#ifndef _SPK_GENERAL_ENDPOINT_DEFINE_H
#define _SPK_GENERAL_ENDPOINT_DEFINE_H


#include    <sutil/net/spk_general_client_define.h>
#include    <sutil/platform/spk_platforms.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 可以同时连接的远程服务器的最大数量 */
#ifndef SPK_ENDPOINT_MAX_REMOTE_CNT
#   define  SPK_ENDPOINT_MAX_REMOTE_CNT         (128)
#endif
/* -------------------------           */


/* ===================================================================
 * 枚举类型定义
 * =================================================================== */

/**
 * 数据导出格式
 */
typedef enum _eSpkDataExportFormat {
    SPK_ENDPOINT_EXPORT_FORMATE_NONE            = 0,    /**< 空 (不输出数据) */
    SPK_ENDPOINT_EXPORT_FORMATE_JSON            = 1,    /**< JSON格式 */
    SPK_ENDPOINT_EXPORT_FORMATE_CSV             = 2,    /**< CSV/TXT格式 */
    SPK_ENDPOINT_EXPORT_FORMATE_BINARY          = 3,    /**< 原始的二进制结构 */
    SPK_ENDPOINT_EXPORT_FORMATE_POC             = 4     /**< 适用于POC测试的文本格式 */
} eSpkDataExportFormatT;
/* -------------------------           */


/**
 * 连接就绪状态
 */
typedef enum _eSpkEndpointChannelStatus {
    SPK_ENDPOINT_CHANNEL_STATUS_DISCONNECT      = 0,    /**< 尚未连接或连接已断开 */
    SPK_ENDPOINT_CHANNEL_STATUS_CONNECTED       = 1,    /**< 连接已建立 */
    SPK_ENDPOINT_CHANNEL_STATUS_READY           = 2     /**< 连接已就绪 */
} eSpkEndpointChannelStatusT;
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/* 结构体类型的前置声明 */
struct _SEndpointChannel;


/**
 * 通信端点的通道配置信息
 */
typedef struct _SEndpointChannelCfg {
    /** 通道顺序号 (根据添加的次序自动设置) */
    int32                   channelIndex;
    /** 通道类型 */
    int32                   channelType;
    /** 通道标签 */
    char                    channelTag[GENERAL_CLI_MAX_NAME_LEN];

    /** 远程主机配置信息 */
    SGeneralClientRemoteCfgT
                            remoteCfg;

    /**
     * 对接收到的应答或回报消息进行处理的回调函数
     * - 若回调函数返回小于0的数, 将尝试断开并重建连接
     *
     * @see F_GENERAL_CLI_ON_MSG_T
     */
    int32                   (*fnOnMsg) (
            SGeneralClientChannelT *pSessionInfo,
            SMsgHeadT *pMsgHead,
            void *pMsgItem,
            void *pCallbackParams);
    /** 传递给fnOnMsg回调函数的参数 */
    void                    *pOnMsgParams;

    /**
     * 连接或重新连接完成后的回调函数
     * - 需要通过该回调函数完成回报订阅操作
     * - 若函数指针为空, 则会使用通道配置中默认的回报订阅参数进行订阅
     * - 若函数指针不为空, 但未订阅回报, 90秒以后服务器端会强制断开连接
     * - 若回调函数返回小于0的数, 则通信线程将中止运行
     *
     * @see F_SPK_ENDPOINT_ON_CONNECT_T
     */
    int32                   (*fnOnConnect) (
            struct _SEndpointChannel *pAsyncChannel,
            void *pCallbackParams);
    /** 传递给fnOnConnect回调函数的参数 */
    void                    *pOnConnectParams;

    /**
     * 连接断开后的回调函数
     * - 无需做特殊处理, 通信线程会自动尝试重建连接
     * - 若函数指针为空, 通信线程会自动尝试重建连接并继续执行
     * - 若回调函数返回小于0的数, 则通信线程将中止运行
     *
     * @see F_SPK_ENDPOINT_ON_DISCONNECT_T
     */
    int32                   (*fnOnDisconnect) (
            struct _SEndpointChannel *pAsyncChannel,
            void *pCallbackParams);
    /** 传递给fnOnDisconnect回调函数的参数 */
    void                    *pOnDisconnectParams;

    /** 可以由应用层自定义使用的, 用于存储自定义数据的扩展空间 */
    union {
        char                buf[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        int8                i8[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        uint8               u8[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        int16               i16[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 2];
        uint16              u16[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 2];
        int32               i32[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 4];
        uint32              u32[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 4];
        int64               i64[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
        uint64              u64[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
        void                *ptr[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
    } customData;

} SEndpointChannelCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_SPK_ENDPOINT_CHANNEL_CFG                                \
        0, 0, {0}, \
        {NULLOBJ_GENERAL_CLIENT_REMOTE_CFG}, \
        0, 0, 0, 0, 0, 0, \
        {{0}}
/* -------------------------           */


/**
 * 通信端点的异步I/O线程配置信息
 */
typedef struct _SEndpointIoThreadCfg {
    /** 使能标志 */
    uint8                   enable;

    /** 是否采用精简模式输出数据 */
    uint8                   isOutputSimplify;

    /** 是否采用追加模式输出数据 */
    uint8                   isAppendMode;

    /** I/O线程是否使用忙等待模式 (仅用于延迟测量场景, 否则I/O线程没有必要使用忙等待模式) */
    uint8                   isIoThreadBusyPollAble;

    /** 数据输出格式 */
    int32                   dataOutputFormat;

    /** 数据文件路径 (为空:不输出数据; STDOUT/STDERR:标准输出) */
    char                    dataOutputPath[SPK_MAX_PATH_LEN];

    /** 统计信息文件路径 (为空:不输出数据; STDOUT/STDERR:标准输出) */
    char                    statsOutputPath[SPK_MAX_PATH_LEN];
} SEndpointIoThreadCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_SPK_ENDPOINT_IO_THREAD_CFG                              \
        0, 0, 0, 0, 0, \
        {0}, {0}
/* -------------------------           */


/**
 * 通信端点的运行时上下文环境
 * 该结构体下的字段均为组件内部使用和管理, 客户端不应直接修改该结构体下的数据
 */
typedef struct _SEndpointContext {
    /** 内部参考数据指针 */
    void                    *pInternalRefs;
    /** 按64位对齐的填充域 */
    void                    *__filler;

    /** 通知线程终止运行的标志变量 */
    volatile uint8          terminateFlag;
    /** 按64位对齐的填充域 */
    uint8                   __filler2[7];
} SEndpointContextT;


/* 结构体的初始化值定义 */
#define NULLOBJ_SPK_ENDPOINT_CONTEXT                                    \
        0, 0, 0, {0}
/* -------------------------           */


/**
 * 通信端点的连接通道运行时信息
 */
typedef struct _SEndpointChannel {
    /** 会话信息指针 */
    SGeneralClientChannelT  *pSessionInfo;
    /** 通信端点的运行时上下文环境指针 */
    SEndpointContextT       *pContext;

    /** 通道配置信息指针 */
    SEndpointChannelCfgT    *pChannelCfg;
    /** 扩展的通道配置数据 (由基础库负责分配空间, 由应用层或API负责解释和维护) */
    void                    *pExtChannelCfg;

    /** 标识通道是否已连接就绪 */
    volatile uint8          isConnected;
    /** 通信协议类型 (由异步端点启动时自动检测和赋值) @see eSSocketProtocolTypeT */
    uint8                   protocolType;
    /** 是否是无连接的UDP类型通信协议 */
    uint8                   isUdpChannel;
    /** 按64位对齐的填充域 */
    uint8                   __filler[5];

    /** 最近/上一次会话实际接收到的入向消息序号 (由应用层或API负责维护) */
    volatile int64          lastInMsgSeq;
    /** 最近/上一次会话实际已发送的出向消息序号 (由应用层或API负责维护) */
    volatile int64          lastOutMsgSeq;
} SEndpointChannelT;


/* 结构体的初始化值定义 */
#define NULLOBJ_SPK_ENDPOINT_CHANNEL                                    \
        0, 0, \
        0, 0, \
        0, 0, 0, {0}, \
        0, 0
/* -------------------------           */


/* ===================================================================
 * 回调函数的函数原型定义
 * =================================================================== */

/**
 * 连接完成后的回调函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 若回调函数返回小于0的数, 则通信线程将中止运行
 * </p>
 *
 * <p> 线程说明:
 * - OnMsg/OnConnect/OnDisconnect 回调函数均运行在通信线程下
 * </p>
 *
 * @param   pAsyncChannel       通信端点的连接通道信息
 * @param   pCallbackParams     外部传入的参数
 * @retval  =0                  等于0, 成功
 * @retval  >0                  大于0, 处理失败, 将重建连接并继续尝试执行
 * @retval  <0                  小于0, 处理失败, 通信线程将中止运行
 */
typedef int32   (*F_SPK_ENDPOINT_ON_CONNECT_T) (
                SEndpointChannelT *pAsyncChannel,
                void *pCallbackParams);


/**
 * 连接断开后的回调函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 仅用于通知客户端连接已经断开, 无需做特殊处理, 通信线程会自动尝试重建连接
 * - 若函数指针为空, 通信线程会自动尝试重建连接并继续执行
 * - 若回调函数返回小于0的数, 则通信线程将中止运行
 * </p>
 *
 * <p> 线程说明:
 * - OnMsg/OnConnect/OnDisconnect 回调函数均运行在通信线程下
 * </p>
 *
 * @param   pAsyncChannel       通信端点的连接通道信息
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 通信线程将尝试重建连接并继续执行
 * @retval  <0                  小于0, 通信线程将中止运行
 */
typedef int32   (*F_SPK_ENDPOINT_ON_DISCONNECT_T) (
                SEndpointChannelT *pAsyncChannel,
                void *pCallbackParams);

/**
 * 通信线程/回调线程初始化函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 若回调函数返回小于0的数, 则线程将中止运行
 * </p>
 *
 * <p> 线程说明:
 * - 如果为通信线程或回调线程指定了初始化函数, 则线程启动后将回调该初始化函数
 * </p>
 *
 * @param   pAsyncContext       通信端点的运行时环境
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 成功
 * @retval  <0                  小于0, 处理失败, 线程将中止运行
 */
typedef int32   (*F_SPK_ENDPOINT_ON_THREAD_START_T) (
                SEndpointContextT *pAsyncContext,
                void *pCallbackParams);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_GENERAL_ENDPOINT_DEFINE_H */
