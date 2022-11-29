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
 * @file    mds_async_api.h
 *
 * MDS (行情数据服务系统) 异步接口库
 *
 * @version 0.15.9.1    2019/07/01
 *          - 增加支持异步行情接收的API接口库
 *              - 支持异步行情接收
 *              - 支持自动的连接管理 (自动识别异常并重建连接)
 *          - 样例代码参见:
 *              - samples/01_mds_async_tcp_sample.c
 * @version 0.15.9.4    2019/11/19
 *          - 支持在运行过程中重新指定行情订阅条件
 *          - 调整 OnConnect 回调函数的返回值约定 @see F_MDSAPI_ASYNC_ON_DISCONNECT_T
 * @version 0.15.10     2019/12/20
 *          - 重构异步API, 统一交易和行情的异步接口
 * @version 0.15.11     2020/05/29
 *          - 增加辅助的异步API接口
 *              - MdsAsyncApi_IsAllTerminated, 返回异步API相关的所有线程是否都已经安全退出
 *          - 删除并不适用于行情异步API的密码修改接口
 *              - MdsAsyncApi_SendChangePasswordReq
 *
 * @since   2019/07/01
 */


#ifndef _MDS_ASYNC_API_H
#define _MDS_ASYNC_API_H


#include    <mds_api/mds_api.h>
#include    <sutil/net/spk_general_endpoint_define.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 可以同时连接的远程服务器的最大数量 (256) */
#define MDSAPI_ASYNC_MAX_REMOTE_CNT             SPK_ENDPOINT_MAX_REMOTE_CNT

/** 默认的异步API配置区段名称 */
#define MDSAPI_CFG_DEFAULT_SECTION_ASYNC_API    "mds_client.async_api"
/** 默认的CPU亲和性配置区段名称 */
#define MDSAPI_CFG_DEFAULT_SECTION_CPUSET       "cpuset"

/** 默认的异步API线程的CPU亲和性配置项名称 (通信线程) */
#define MDSAPI_CFG_DEFAULT_KEY_CPUSET_COMMUNICATION         \
        "mdsapi_communication"
/** 默认的异步API线程的CPU亲和性配置项名称 (异步回调线程) */
#define MDSAPI_CFG_DEFAULT_KEY_CPUSET_CALLBACK              \
        "mdsapi_callback"
/** 默认的异步API线程的CPU亲和性配置项名称 (I/O线程) */
#define MDSAPI_CFG_DEFAULT_KEY_CPUSET_IO_THREAD             \
        "mdsapi_io_thread"
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * MDS异步API线程的通道配置信息
 */
typedef SEndpointChannelCfgT        MdsAsyncApiChannelCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_ASYNC_CHANNEL_CFG        \
        NULLOBJ_SPK_ENDPOINT_CHANNEL_CFG
/* -------------------------           */


/**
 * MDS异步API的I/O线程配置信息 (用于异步落地行情数据, 可以通过配置文件开启或禁用)
 */
typedef SEndpointIoThreadCfgT       MdsAsyncApiIoThreadCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_ASYNC_IO_THREAD_CFG      \
        NULLOBJ_SPK_ENDPOINT_IO_THREAD_CFG
/* -------------------------           */


/**
 * MDS异步API的运行时上下文环境
 * 该结构体下的字段均为API内部使用和管理, 客户端不应直接修改该结构体下的数据
 */
typedef SEndpointContextT           MdsAsyncApiContextT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_ASYNC_CONTEXT            \
        NULLOBJ_SPK_ENDPOINT_CONTEXT
/* -------------------------           */


/**
 * MDS异步API的连接通道运行时信息
 */
typedef SEndpointChannelT           MdsAsyncApiChannelT;


/* 结构体的初始化值定义 */
#define NULLOBJ_MDSAPI_ASYNC_CHANNEL            \
        NULLOBJ_SPK_ENDPOINT_CHANNEL
/* -------------------------           */


/**
 * MDS异步API的上下文环境的创建参数 (仅做为 CreateContext 接口的参数使用)
 */
typedef struct _MdsAsyncApiContextParams {
    /** 异步队列的大小 */
    int32               asyncQueueSize;

    /** 是否优先使用大页内存来创建异步队列 */
    uint8               isHugepageAble;

    /** 是否启动独立的回调线程来执行回调处理 (否则将直接在通信线程下执行回调处理) */
    uint8               isAsyncCallbackAble;

    /** 是否使用忙等待模式 (TRUE:延迟更低但CPU会被100%占用; FALSE:延迟和CPU使用率相对均衡) */
    uint8               isBusyPollAble;

    /** 是否在启动前预创建并校验所有的连接 */
    uint8               isPreconnectAble;

    /** 是否需要支持对接压缩后的行情数据 */
    uint8               isCompressible;

    /** 是否启用对UDP行情数据的本地行情订阅和过滤功能 */
    uint8               isUdpFilterable;

    /** 为保证64位对齐而设 */
    uint8               __filler[6];
} MdsAsyncApiContextParamsT;


/* 结构体初始化值定义 */
#define NULLOBJ_MDSAPI_ASYNC_CONTEXT_PARAMS     \
        0, 0, 0, 0, 0, 0, 0, {0}

/* 结构体的默认值定义 */
#define DEFAULT_MDSAPI_ASYNC_CONTEXT_PARAMS     \
        -1, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, {0}
/* -------------------------           */


/* ===================================================================
 * 回调函数的函数原型定义
 * =================================================================== */

/**
 * 对接收到的消息进行处理的回调函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 和 #F_MDSAPI_ONMSG_T 的定义一致, 回调函数可以通用
 * - 对消息体数据(pMsgBody), 需要按照消息类型(pMsgHead->msgId)转换为对应的消息结构进行处理
 * - 具体使用方式可以参考样例代码中的 MdsApiSample_HandleMsg 函数
 * - @note 当使用异步回调模式时, 应尽量避免使用会话信息中的数据
 * </p>
 *
 * <p> 线程说明:
 * - OnMsg/OnConnect/OnDisconnect 回调函数均运行在异步API线程下
 * </p>
 *
 * @param   pSessionInfo        会话信息
 * @param   pMsgHead            消息头
 * @param   pMsgBody            消息体数据
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 成功
 * @retval  <0                  小于0, 处理失败, 将尝试断开并重建连接
 *
 * @see     eMdsMsgTypeT
 * @see     MdsMktRspMsgBodyT
 * @see     MdsMktDataSnapshotT
 * @see     MdsL2TradeT
 * @see     MdsL2OrderT
 */
typedef F_MDSAPI_ONMSG_T        F_MDSAPI_ASYNC_ON_MSG_T;


/**
 * 异步API线程连接或重新连接完成后的回调函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 对于TCP通道, 需要通过该回调函数完成行情订阅操作。若函数指针为空, 则会使用通道配置中默认的
 *   订阅参数进行订阅。若函数指针不为空, 但未订阅回报, 90秒以后服务器端会强制断开连接
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * <p> 线程说明:
 * - OnMsg/OnConnect/OnDisconnect 回调函数均运行在异步API线程下
 * </p>
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pCallbackParams     外部传入的参数
 * @retval  =0                  等于0, 成功
 * @retval  >0                  大于0, 处理失败, 将重建连接并继续尝试执行
 * @retval  <0                  小于0, 处理失败, 异步线程将中止运行
 */
typedef int32   (*F_MDSAPI_ASYNC_ON_CONNECT_T) (
                MdsAsyncApiChannelT *pAsyncChannel,
                void *pCallbackParams);


/**
 * 异步API线程连接断开后的回调函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 仅用于通知客户端连接已经断开, 无需做特殊处理, 异步线程会自动尝试重建连接
 * - 若函数指针为空, 异步线程会自动尝试重建连接并继续执行
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * <p> 线程说明:
 * - OnMsg/OnConnect/OnDisconnect 回调函数均运行在异步API线程下
 * </p>
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 异步线程将尝试重建连接并继续执行
 * @retval  <0                  小于0, 异步线程将中止运行
 */
typedef int32   (*F_MDSAPI_ASYNC_ON_DISCONNECT_T) (
                MdsAsyncApiChannelT *pAsyncChannel,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 上下文管理接口
 * =================================================================== */

/**
 * 创建异步API的运行时环境 (通过配置文件和默认的配置区段加载相关配置参数)
 *
 * - 与 MdsAsyncApi_CreateContextSimple 接口的区别为, 会通过配置文件加载如下配置:
 *   - 日志配置
 *   - 异步API相关的扩展配置: 异步队列的大小、是否启动独立的回调线程来执行回调处理、是否使用
 *     忙等待模式、是否需要支持对接压缩后的行情数据等
 *   - 异步I/O线程配置 (@see MdsAsyncApi_LoadIoThreadCfg)
 *   - CPU亲和性配置 (@see MdsAsyncApi_LoadCpusetCfg)
 *
 * @param   pCfgFile            配置文件路径 (可为空, 为空则不加载配置文件)
 * @return  非空, 异步API的运行时环境指针; NULL, 失败
 */
MdsAsyncApiContextT *
        MdsAsyncApi_CreateContext(
                const char *pCfgFile);

/**
 * 创建异步API的运行时环境 (通过配置文件和指定的配置区段加载相关配置参数)
 *
 * - 与 MdsAsyncApi_CreateContextSimple 接口的区别为, 会通过配置文件加载如下配置:
 *   - 日志配置
 *   - 异步API相关的扩展配置: 异步队列的大小、是否启动独立的回调线程来执行回调处理、是否使用
 *     忙等待模式、是否需要支持对接压缩后的行情数据等
 *   - 异步I/O线程配置 (@see MdsAsyncApi_LoadIoThreadCfg)
 *   - CPU亲和性配置 (@see MdsAsyncApi_LoadCpusetCfg)
 *
 * @param   pCfgFile            配置文件路径 (可为空, 为空则不加载配置文件)
 * @param   pLoggerSection      日志记录器的配置区段名称 (e.g. "log")
 *                              - 为空则忽略, 不初始化日志记录器
 * @param   pAsyncApiSection    异步API参数的配置区段名称 (e.g. "mds_client.async_api")
 *                              - 为空则忽略, 不加载异步API相关的配置
 * @param   pCpusetSection      CPU亲和性配置的配置区段名称 (e.g. "cpuset")
 *                              - 为空则忽略, 不加载CPU亲和性配置
 * @return  非空, 异步API的运行时环境指针; NULL, 失败
 */
MdsAsyncApiContextT *
        MdsAsyncApi_CreateContext2(
                const char *pCfgFile,
                const char *pLoggerSection,
                const char *pAsyncApiSection,
                const char *pCpusetSection);

/**
 * 创建异步API的运行时环境 (仅通过函数参数指定必要的配置参数)
 *
 * @param   pLoggerCfgFile      日志配置文件路径
 *                              - 为空则忽略, 不初始化日志记录器
 * @param   pLoggerSection      日志记录器的配置区段名称 (e.g. "log")
 *                              - 为空则使用默认值
 * @param   asyncQueueSize      用于缓存行情数据的消息队列大小 (最大可缓存的消息数量)
 *                              - 等于0, 不创建缓存队列 (无需异步处理或落地行情数据)
 *                              - 小于0, 使用默认值 500000
 * @return  非空, 异步API的运行时环境指针; NULL, 失败
 */
MdsAsyncApiContextT *
        MdsAsyncApi_CreateContextSimple(
                const char *pLoggerCfgFile,
                const char *pLoggerSection,
                int32 asyncQueueSize);

/**
 * 创建异步API的运行时环境 (仅通过函数参数指定必要的配置参数)
 *
 * @param   pLoggerCfgFile      日志配置文件路径
 *                              - 为空则忽略, 不初始化日志记录器
 * @param   pLoggerSection      日志记录器的配置区段名称 (e.g. "log")
 *                              - 为空则使用默认值
 * @param   pContextParams      上下文环境的创建参数
 *                              - 为空则使用默认值
 * @return  非空, 异步API的运行时环境指针; NULL, 失败
 */
MdsAsyncApiContextT *
        MdsAsyncApi_CreateContextSimple2(
                const char *pLoggerCfgFile,
                const char *pLoggerSection,
                const MdsAsyncApiContextParamsT *pContextParams);

/**
 * 释放异步API的运行时环境
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 */
void    MdsAsyncApi_ReleaseContext(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 启动异步API线程
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_Start(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 终止异步API线程
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 */
void    MdsAsyncApi_Stop(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 返回异步API的通信线程是否正在运行过程中
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  TRUE 正在运行过程中; FALSE 已终止或尚未运行
 */
BOOL    MdsAsyncApi_IsRunning(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 返回异步API相关的所有线程是否都已经安全退出 (或尚未运行)
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  TRUE 所有线程均已退出; FALSE 尚未全部退出
 */
BOOL    MdsAsyncApi_IsAllTerminated(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 返回异步API累计已提取和处理过的行情消息数量
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  累计已提取和处理过的行情消息数量 (包括已处理但处理失败的消息)
 */
int64   MdsAsyncApi_GetTotalPicked(
                MdsAsyncApiContextT *pAsyncContext);
/* -------------------------           */


/* ===================================================================
 * 通道管理接口
 * =================================================================== */

/**
 * 返回通道数量 (通道配置信息数量)
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  通道数量 (通道配置信息数量)
 */
int32   MdsAsyncApi_GetChannelCount(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 返回当前已连接的通道数量
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  已连接的通道数量
 */
int32   MdsAsyncApi_GetConnectedChannelCount(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 添加通道配置信息
 *
 * @note 提示:
 * - 不能将TCP通道和UDP通道添加到同一个异步线程中
 * - 异步API尚不支持查询接口, 不能将查询通道添加到异步API中
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pChannelTag     通道配置信息的自定义标签 (可以为空)
 * @param       pRemoteCfg      待添加的通道配置信息 (不可为空)
 * @param       pSubscribeCfg   默认的回报订阅参数 (可以为空)
 * @param       fnOnMsg         进行消息处理的回调函数 (不可为空)
 * @param       pOnMsgParams    fnOnMsg回调函数的参数
 * @param       fnOnConnect     连接或重新连接完成后的回调函数 (可以为空)
 *                              - 若函数指针为空, 则会使用默认的订阅参数进行订阅
 * @param       pOnConnectParams
 *                              fnOnConnect回调函数的参数
 * @param       fnOnDisconnect  连接断开后的回调函数 (可以为空)
 * @param       pOnDisconnectParams
 *                              fnOnDisconnect回调函数的参数
 * @return      非空, 异步API的连接通道信息; 空, 失败
 */
MdsAsyncApiChannelT *
        MdsAsyncApi_AddChannel(
                MdsAsyncApiContextT *pAsyncContext,
                const char *pChannelTag,
                const MdsApiRemoteCfgT *pRemoteCfg,
                const MdsApiSubscribeInfoT *pSubscribeCfg,
                F_MDSAPI_ASYNC_ON_MSG_T fnOnMsg,
                void *pOnMsgParams,
                F_MDSAPI_ASYNC_ON_CONNECT_T fnOnConnect,
                void *pOnConnectParams,
                F_MDSAPI_ASYNC_ON_DISCONNECT_T fnOnDisconnect,
                void *pOnDisconnectParams);

/**
 * 从配置文件中加载并添加通道配置信息
 *
 * @note 提示:
 * - 不能将TCP通道和UDP通道添加到同一个异步线程中
 * - 异步API尚不支持查询接口, 不能将查询通道添加到异步API中
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pChannelTag     通道配置信息的自定义标签 (可以为空)
 * @param       pCfgFile        配置文件路径 (不可为空)
 * @param       pCfgSection     配置区段名称 (不可为空)
 * @param       pAddrKey        服务器地址的配置项关键字 (不可为空)
 * @param       fnOnMsg         进行消息处理的回调函数 (不可为空)
 * @param       pOnMsgParams    fnOnMsg回调函数的参数
 * @param       fnOnConnect     连接或重新连接完成后的回调函数 (可以为空)
 *                              - 若函数指针为空, 则会使用默认的订阅参数进行订阅
 * @param       pOnConnectParams
 *                              fnOnConnect回调函数的参数
 * @param       fnOnDisconnect  连接断开后的回调函数 (可以为空)
 * @param       pOnDisconnectParams
 *                              fnOnDisconnect回调函数的参数
 * @return      非空, 异步API的连接通道信息; 空, 失败
 */
MdsAsyncApiChannelT *
        MdsAsyncApi_AddChannelFromFile(
                MdsAsyncApiContextT *pAsyncContext,
                const char *pChannelTag,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey,
                F_MDSAPI_ASYNC_ON_MSG_T fnOnMsg,
                void *pOnMsgParams,
                F_MDSAPI_ASYNC_ON_CONNECT_T fnOnConnect,
                void *pOnConnectParams,
                F_MDSAPI_ASYNC_ON_DISCONNECT_T fnOnDisconnect,
                void *pOnDisconnectParams);

/**
 * 返回顺序号对应的连接通道信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   channelIndex        通道顺序号
 *                              - 大于0: 返回与指定顺序号相对应的, 并且与指定通道类型相
 *                                匹配的通道信息 (顺序号与通道配置的添加顺序一致)
 *                              - 小于0: 返回第一个与指定通道类型相匹配的通道信息
 *                              - INT_MAX: 返回最后一个与指定通道类型相匹配的通道信息
 * @return  异步API的连接通道信息
 */
MdsAsyncApiChannelT *
        MdsAsyncApi_GetChannel(
                MdsAsyncApiContextT *pAsyncContext,
                int32 channelIndex);

/**
 * 返回标签对应的连接通道信息
 *
 * @note 注意事项:
 * - API不强制要求标签必须唯一, 如果标签不唯一, 则将返回第一个匹配到的通道信息
 * - 标签名称不区分大小写
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   pChannelTag         通道配置信息的自定义标签
 * @return  异步API的连接通道信息
 */
MdsAsyncApiChannelT *
        MdsAsyncApi_GetChannelByTag(
                MdsAsyncApiContextT *pAsyncContext,
                const char *pChannelTag);

/**
 * 遍历所有的连接通道信息并执行回调函数
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   fnCallback          待执行的回调函数 (可以为空)
 *                              - 若返回值小于0, 则将中止遍历并返回该值
 * @param   pParams             回调函数的参数 (可以为空)
 * @return  大于等于0, 成功遍历到的通道数量; 小于0, 参数错误或者回调函数的返回值小于0
 */
int32   MdsAsyncApi_ForeachChannel(
                MdsAsyncApiContextT *pAsyncContext,
                int32 (*fnCallback)(
                        MdsAsyncApiChannelT *pAsyncChannel, void *pParams),
                void *pParams);

/**
 * 遍历所有的连接通道信息并执行回调函数
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   fnCallback          待执行的回调函数 (可以为空)
 *                              - 若返回值小于0, 则将中止遍历并返回该值
 * @param   pParam1             回调函数的参数1 (可以为空)
 * @param   pParam2             回调函数的参数2 (可以为空)
 * @return  大于等于0, 成功遍历到的通道数量; 小于0, 参数错误或者回调函数的返回值小于0
 */
int32   MdsAsyncApi_ForeachChannel2(
                MdsAsyncApiContextT *pAsyncContext,
                int32 (*fnCallback)(
                        MdsAsyncApiChannelT *pAsyncChannel,
                        void *pParam1, void *pParam2),
                void *pParam1,
                void *pParam2);

/**
 * 遍历所有的连接通道信息并执行回调函数
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   fnCallback          待执行的回调函数 (可以为空)
 *                              - 若返回值小于0, 则将中止遍历并返回该值
 * @param   pParam1             回调函数的参数1 (可以为空)
 * @param   pParam2             回调函数的参数2 (可以为空)
 * @param   pParam3             回调函数的参数3 (可以为空)
 * @return  大于等于0, 成功遍历到的通道数量; 小于0, 参数错误或者回调函数的返回值小于0
 */
int32   MdsAsyncApi_ForeachChannel3(
                MdsAsyncApiContextT *pAsyncContext,
                int32 (*fnCallback)(MdsAsyncApiChannelT *pAsyncChannel,
                        void *pParam1, void *pParam2, void *pParam3),
                void *pParam1,
                void *pParam2,
                void *pParam3);

/**
 * 返回通道是否已连接就绪
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @return  TRUE 已连接就绪; FALSE 尚未连接就绪
 */
BOOL    MdsAsyncApi_IsChannelConnected(
                MdsAsyncApiChannelT *pAsyncChannel);

/**
 * 返回通道对应的配置信息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @return  通道配置信息
 */
MdsAsyncApiChannelCfgT *
        MdsAsyncApi_GetChannelCfg(
                MdsAsyncApiChannelT *pAsyncChannel);

/**
 * 返回通道对应的行情订阅配置信息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @return  行情订阅配置信息
 */
MdsApiSubscribeInfoT *
        MdsAsyncApi_GetChannelSubscribeCfg(
                MdsAsyncApiChannelT *pAsyncChannel);
/* -------------------------           */


/* ===================================================================
 * 会话管理接口
 * =================================================================== */

/**
 * 以异步的方式发送证券行情实时订阅请求, 以重新订阅、追加订阅或删除订阅行情数据
 *
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pMktDataRequestReq  行情订阅请求信息
 * @param   pEntries            产品订阅列表
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SubscribeMarketData(
                MdsAsyncApiChannelT *pAsyncChannel,
                const MdsMktDataRequestReqT *pMktDataRequestReq,
                const MdsMktDataRequestEntryT *pEntries);

/**
 * 根据字符串形式的证券代码列表订阅行情信息
 *
 * @note    与 MdsApi_SubscribeByString 接口相同, 无法直接指定 tickType 等订阅参数(均
 *          默认为0), 需要通过 MdsApi_SetThreadSubscribeTickType 等接口来这些订阅参数
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 * @note    订阅的数据类型 (dataTypes) 会以最后一次订阅为准, 所以每次都应该指定为所有待订阅
 *          的数据类型
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pSecurityListStr    证券代码列表字符串
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "", 表示不订阅任何产品的行情
 *                              - 空指针 NULL, 表示订阅所有产品的行情
 * @param   pDelim              证券代码列表的分隔符 (e.g. ",;| \t")
 *                              - 如果为空, 则使用默认的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   exchangeId          证券代码所属的交易所代码 (如果证券代码没有 .SH 或 .SZ 后缀的话)
 * @param   mdProductType       行情类别 (股票(基金、债券)/指数/期权)
 * @param   subMode             订阅模式 (重新订阅/追加订阅/删除订阅)
 * @param   dataTypes           订阅的数据种类 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失败
 *
 * @see     MdsApi_SetThreadSubscribeTickType
 * @see     MdsApi_SetThreadSubscribeTickRebuildFlag
 * @see     MdsApi_SetThreadSubscribeTickExpireType
 * @see     MdsApi_SetThreadSubscribeRequireInitMd
 * @see     MdsApi_SetThreadSubscribeBeginTime
 */
BOOL    MdsAsyncApi_SubscribeByString(
                MdsAsyncApiChannelT *pAsyncChannel,
                const char *pSecurityListStr, const char *pDelim,
                eMdsExchangeIdT exchangeId, eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode, int32 dataTypes);

/**
 * 直接根据字符串形式的证券代码列表订阅行情, 并通过证券代码前缀来区分和识别所属市场
 *
 * @note    代码前缀仅对 pSecurityListStr 参数指定的证券代码生效, 只是为了方便区分证券代码
 *          所属的市场, 并不能直接通过代码前缀自动订阅所有匹配的股票
 * @note    与 MdsApi_SubscribeByString 接口相同, 无法直接指定 tickType 等订阅参数(均
 *          默认为0), 需要通过 MdsApi_SetThreadSubscribeTickType 等接口来这些订阅参数
 * @note    频繁订阅会对当前连接的行情获取速度产生不利影响, 建议每次订阅都尽量指定更多的证券
 *          代码, 以减少订阅次数
 * @note    订阅的数据类型 (dataTypes) 会以最后一次订阅为准, 所以每次都应该指定为所有待订阅
 *          的数据类型
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pSecurityListStr    证券代码列表字符串
 *                              - 证券代码支持以 .SH 或 .SZ 为后缀来指定其所属的交易所
 *                              - 空字符串 "", 表示不订阅任何产品的行情
 *                              - 空指针 NULL, 表示订阅所有产品的行情
 * @param   pDelim              证券代码列表的分隔符 (e.g. ",;| \t")
 *                              - 如果为空, 则使用默认的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   pSseCodePrefixes    以逗号或空格分隔的上海证券代码前缀列表, e.g.
 *                              - "6, 300, 301" 将匹配证券代码列表中所有以 '6' 或 '300'
 *                                或 '301' 起始的证券代码
 *                              - 若为NULL或空字符串, 则不会匹配任何证券代码
 *                              - 上海证券代码前缀参考:
 *                                  - "009, 01, 02, "               //国债
 *                                  - "10, 11, 12, 13, 18, 19, "    //债券 (企业债、可转债等)
 *                                  - "20, "                        //债券 (回购)
 *                                  - "5, "                         //基金
 *                                  - "6, "                         //A股
 *                                  - "000"                         //指数
 * @param   pSzseCodePrefixes   以逗号或空格分隔的深圳证券代码前缀列表
 *                              - 若为NULL或空字符串, 则不会匹配任何证券代码
 *                              - 证券代码前缀可以和上海相同, 此时匹配的证券代码会同时对上海
 *                                和深圳两个市场进行订阅
 *                              - 深圳证券代码前缀参考:
 *                                  - "00, "                        //股票
 *                                  - "10, 11, 12, 13, "            //债券
 *                                  - "15, 16, 17, 18, "            //基金
 *                                  - "30, "                        //创业板
 *                                  - "39"                          //指数
 * @param   mdProductType       行情类别 (股票(基金、债券)/指数/期权)
 * @param   subMode             订阅模式 (重新订阅/追加订阅/删除订阅)
 * @param   dataTypes           订阅的数据种类 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失败
 *
 * @see     MdsApi_SetThreadSubscribeTickType
 * @see     MdsApi_SetThreadSubscribeTickRebuildFlag
 * @see     MdsApi_SetThreadSubscribeTickExpireType
 * @see     MdsApi_SetThreadSubscribeRequireInitMd
 * @see     MdsApi_SetThreadSubscribeBeginTime
 */
BOOL    MdsAsyncApi_SubscribeByStringAndPrefixes(
                MdsAsyncApiChannelT *pAsyncChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                const char *pSseCodePrefixes,
                const char *pSzseCodePrefixes,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/**
 * 发送心跳消息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SendHeartbeat(
                MdsAsyncApiChannelT *pAsyncChannel);

/**
 * 发送测试请求消息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pTestReqId          测试请求标识符 (C32, 可以为空)
 * @param   testReqIdSize       测试请求标识符的长度
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SendTestReq(
                MdsAsyncApiChannelT *pAsyncChannel,
                const char *pTestReqId,
                int32 testReqIdSize);
/* -------------------------           */


/* ===================================================================
 * 辅助的配置管理接口
 * =================================================================== */

/**
 * 从配置文件中加载CPU亲和性配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     配置区段名称
 * @param       pCommunicationCpusetKey
 *                              通信线程的CPU亲和性配置项关键字
 * @param       pCallbackThreadCpusetKey
 *                              异步回调线程的CPU亲和性配置项关键字
 * @param       pIoThreadCpusetKey
 *                              异步I/O线程的CPU亲和性配置项关键字
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_LoadCpusetCfg(
                MdsAsyncApiContextT *pOutThreadCfg,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pCommunicationCpusetKey,
                const char *pCallbackThreadCpusetKey,
                const char *pIoThreadCpusetKey);

/**
 * 设置通信线程的CPU亲和性配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pCommunicationCpuset
 *                              通信线程绑定的CPU列表 (以逗号或空格分割的CPU编号列表, CPU编号从1开始)
 *                              - e.g. "1"      绑定到 0 号核
 *                              - e.g. "1,3,5"  绑定到 0,2,4 号核
 *                              - NULL 或者 "", 不绑定CPU
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetCommunicationCpusetCfg(
                MdsAsyncApiContextT *pAsyncContext,
                const char *pCommunicationCpuset);

/**
 * 返回通信线程的CPU亲和性配置信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  CPU亲和性配置信息
 */
const char *
        MdsAsyncApi_GetCommunicationCpusetCfg(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置异步回调线程的CPU亲和性配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pCallbackThreadCpuset
 *                              异步回调线程绑定的CPU列表 (以逗号或空格分割的CPU编号列表, CPU编号从1开始)
 *                              - e.g. "1"      绑定到 0 号核
 *                              - e.g. "1,3,5"  绑定到 0,2,4 号核
 *                              - NULL 或者 "", 不绑定CPU
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetCallbackThreadCpusetCfg(
                MdsAsyncApiContextT *pAsyncContext,
                const char *pCallbackThreadCpuset);

/**
 * 返回异步回调线程的CPU亲和性配置信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  CPU亲和性配置信息
 */
const char *
        MdsAsyncApi_GetCallbackThreadCpusetCfg(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置异步I/O线程的CPU亲和性配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pIoThreadCpuset 异步I/O线程绑定的CPU列表 (以逗号或空格分割的CPU编号列表, CPU编号从1开始)
 *                              - e.g. "1"      绑定到 0 号核
 *                              - e.g. "1,3,5"  绑定到 0,2,4 号核
 *                              - NULL 或者 "", 不绑定CPU
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetIoThreadCpusetCfg(
                MdsAsyncApiContextT *pAsyncContext,
                const char *pIoThreadCpuset);

/**
 * 返回异步I/O线程的CPU亲和性配置信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  CPU亲和性配置信息
 */
const char *
        MdsAsyncApi_GetIoThreadCpusetCfg(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置是否在启动前预创建并校验所有的连接
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   isPreconnectAble    是否在启动前预创建并校验所有的连接
 *                              TRUE: 启动前预创建并校验所有的连接, 如果连接失败则中止启动
 *                              FALSE: 启动前不预先创建和校验连接 (默认行为)
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetPreconnectAble(
                MdsAsyncApiContextT *pAsyncContext,
                BOOL isPreconnectAble);

/**
 * 返回是否在启动前预创建并校验所有的连接
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否在启动前预创建并校验所有的连接
 */
BOOL    MdsAsyncApi_IsPreconnectAble(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置是否需要支持对接压缩后的行情数据
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       isCompressible  是否需要支持对接压缩后的行情数据
 *                              - 如果可能会对接压缩行情端口, 可以将该参数设置为TRUE, 这
 *                                样就可以同时兼容压缩和非压缩的行情数据
 *                              - 如果确定不会对接压缩行情端口的话, 则可以将该参数设置为
 *                                FALSE, 这样可以避免额外的(微小的)性能消耗
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetCompressible(
                MdsAsyncApiContextT *pAsyncContext,
                BOOL isCompressible);

/**
 * 返回是否支持对接压缩后的行情数据
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否支持对接压缩后的行情数据
 */
BOOL    MdsAsyncApi_IsCompressible(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置是否启用对UDP行情数据的本地行情订阅和过滤功能
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       isUdpFilterable 是否启用对UDP行情数据的本地订阅和过滤功能
 *                              - 如果将该参数设置为TRUE, 则允许通过
 *                                MdsAsyncApi_SubscribeByString 等接口设置 UDP 行
 *                                情的订阅条件, 并在API端完成对行情数据的过滤
 *                              - 如果不需要通过API进行行情数据过滤的话, 可以将该参数设
 *                                置为FALSE, 这样可以避免额外的(微小的)性能消耗
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetUdpFilterable(
                MdsAsyncApiContextT *pAsyncContext,
                BOOL isUdpFilterable);

/**
 * 返回是否启用对UDP行情数据的本地行情订阅和过滤功能
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否启用对UDP行情数据的本地行情订阅和过滤功能
 */
BOOL    MdsAsyncApi_IsUdpFilterable(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置是否接管启动线程
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   isTakeoverStartThread
 *                              设置是否接管启动线程
 *                              - 0: 启动时将创建独立的线程执行通信处理 (默认行为)
 *                              - 1: 无需创建独立的通信线程, 启动时将接管当前线程并直接
 *                                在当前线程下执行通信处理
 *                              - CHAR_MAX: 不创建通信线程, 也不执行除OnConnect回调以
 *                                外的任何消息接收等异步处理, 完全由当前线程控制后续的执
 *                                行 (仅适用于测试场景, 正常情况下不会使用)
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetTakeoverStartThreadFlag(
                MdsAsyncApiContextT *pAsyncContext,
                int32 isTakeoverStartThread);

/**
 * 返回是否接管启动线程
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否接管启动线程
 */
int32   MdsAsyncApi_GetTakeoverStartThreadFlag(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置是否启动独立的回调线程来执行回调处理
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   isAsyncCallbackAble 是否启动独立的回调线程来执行回调处理
 *                              - TRUE: 创建单独的回调线程 (默认行为)
 *                              - FALSE: 不启动单独的回调线程, 直接在通信线程下执行回调处理
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetAsyncCallbackAble(
                MdsAsyncApiContextT *pAsyncContext,
                BOOL isAsyncCallbackAble);

/**
 * 返回是否启动独立的回调线程来执行回调处理
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否启动独立的回调线程来执行回调处理
 */
BOOL    MdsAsyncApi_IsAsyncCallbackAble(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置异步回调线程的忙等待模式
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       isBusyPollAble  是否使用忙等待模式
 *                              TRUE: 使用忙等待模式, 延迟更低, 但CPU会被100%占用
 *                              FALSE: 不使用忙等待模式, 延迟和CPU使用率相对均衡
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetAsyncCallbackBusyPollAble(
                MdsAsyncApiContextT *pAsyncContext,
                int32 callbackThreadBusyPollLevel);

/**
 * 返回异步回调线程的忙等待模式
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否使用忙等待模式
 */
BOOL    MdsAsyncApi_IsAsyncCallbackBusyPollAble(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 返回异步通信队列的长度
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  异步通信队列的长度 (可缓存的最大消息数量)
 */
int64   MdsAsyncApi_GetAsyncQueueLength(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 返回异步通信队列的数据空间大小
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  异步通信队列的数据空间大小 (字节数)
 */
int64   MdsAsyncApi_GetAsyncQueueDataAreaSize(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 设置异步I/O线程配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       isEnabled       使能标志
 * @param       isOutputSimplify
 *                              是否采用精简模式输出数据
 * @param       dataOutputFormat
 *                              数据输出格式
 * @param       pDataOutputFilePath
 *                              数据文件输出路径 (为空:不输出数据; STDOUT/STDERR:标准输出)
 * @param       pStatsOutputFilePath
 *                              统计信息文件输出路径 (为空:不输出数据; STDOUT/STDERR:标准输出)
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_SetIoThreadCfg(
                MdsAsyncApiContextT *pAsyncContext,
                BOOL isEnabled,
                BOOL isOutputSimplify,
                int32 dataOutputFormat,
                const char *pDataOutputFilePath,
                const char *pStatsOutputFilePath);

/**
 * 返回异步I/O线程配置
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  异步I/O线程配置信息
 */
MdsAsyncApiIoThreadCfgT *
        MdsAsyncApi_GetIoThreadCfg(
                MdsAsyncApiContextT *pAsyncContext);

/**
 * 从配置文件中加载异步I/O线程配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     配置区段名称
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    MdsAsyncApi_LoadIoThreadCfg(
                MdsAsyncApiContextT *pAsyncContext,
                const char *pCfgFile,
                const char *pCfgSection);
/* -------------------------           */


/* ===================================================================
 * 辅助的 Inline 函数
 * =================================================================== */

/**
 * 返回异步API线程是否正在运行过程中
 *
 * MdsAsyncApi_IsRunning 接口的 inline 简化版本
 *
 * @param   pAsyncContext       异步API的运行时环境指针 (@note 参数不能为空)
 * @return  TRUE 正在运行过程中; FALSE 已终止或尚未运行
 */
static __inline BOOL
__MdsAsyncApi_IsRunning(MdsAsyncApiContextT *pAsyncContext) {
    return pAsyncContext->pInternalRefs != NULL
            && *((volatile uint8 *) &pAsyncContext->terminateFlag) == 0;
}


/**
 * 返回通道是否已连接就绪
 *
 * MdsAsyncApi_IsChannelConnected 接口的 inline 版本
 *
 * @param   pAsyncChannel       异步API的连接通道信息 (@note 参数不能为空)
 * @return  TRUE 已连接就绪; FALSE 尚未连接就绪
 */
static __inline BOOL
__MdsAsyncApi_IsChannelConnected(MdsAsyncApiChannelT *pAsyncChannel) {
    return pAsyncChannel->pSessionInfo
            && (*((volatile uint8 *) &pAsyncChannel->isConnected)
                    >= SPK_ENDPOINT_CHANNEL_STATUS_READY);
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_ASYNC_API_H */
