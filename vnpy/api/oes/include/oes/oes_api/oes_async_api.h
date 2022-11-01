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
 * @file    oes_async_api.h
 *
 * OES 异步接口库
 *
 * @version 0.15.10     2019/11/17
 *          - 增加异步API接口库
 *              - 支持异步接收回报数据
 *              - 支持自动的连接管理 (自动识别异常并重建连接)
 *          - 样例代码参见:
 *              - include/oes_api/samples/c_sample/03_oes_async_api_sample.c
 * @version 0.15.11     2020/05/29
 *          - 增加辅助的异步API接口
 *              - OesAsyncApi_SendReportSynchronization, 发送回报同步消息 (仅适用于回报通道)
 *              - OesAsyncApi_IsAllTerminated, 返回异步API相关的所有线程是否都已经安全退出
 *
 * @since   2019/11/17
 */


#ifndef _OES_ASYNC_API_H
#define _OES_ASYNC_API_H


#include    <oes_api/oes_api.h>
#include    <sutil/net/spk_general_endpoint_define.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/** 可以同时连接的远程服务器的最大数量 */
#define OESAPI_ASYNC_MAX_REMOTE_CNT             SPK_ENDPOINT_MAX_REMOTE_CNT

/** 默认的异步API配置区段名称 */
#define OESAPI_CFG_DEFAULT_SECTION_ASYNC_API    "oes_client.async_api"
/** 默认的CPU亲和性配置区段名称 */
#define OESAPI_CFG_DEFAULT_SECTION_CPUSET       "cpuset"

/** 默认的异步API线程的CPU亲和性配置项名称 (通信线程) */
#define OESAPI_CFG_DEFAULT_KEY_CPUSET_COMMUNICATION         \
        "oesapi_report"
/** 默认的异步API线程的CPU亲和性配置项名称 (异步回调线程) */
#define OESAPI_CFG_DEFAULT_KEY_CPUSET_CALLBACK              \
        "oesapi_callback"
/** 默认的异步API线程的CPU亲和性配置项名称 (I/O线程) */
#define OESAPI_CFG_DEFAULT_KEY_CPUSET_IO_THREAD             \
        "oesapi_io_thread"
/* -------------------------           */


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * OES异步API线程的通道配置信息
 */
typedef SEndpointChannelCfgT        OesAsyncApiChannelCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_ASYNC_CHANNEL_CFG        \
        NULLOBJ_SPK_ENDPOINT_CHANNEL_CFG
/* -------------------------           */


/**
 * OES异步API的I/O线程配置信息 (用于异步落地回报数据, 可以通过配置文件开启或禁用)
 */
typedef SEndpointIoThreadCfgT       OesAsyncApiIoThreadCfgT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_ASYNC_IO_THREAD_CFG      \
        NULLOBJ_SPK_ENDPOINT_IO_THREAD_CFG
/* -------------------------           */


/**
 * OES异步API的运行时上下文环境
 * 该结构体下的字段均为API内部使用和管理, 客户端不应直接修改该结构体下的数据
 */
typedef SEndpointContextT           OesAsyncApiContextT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_ASYNC_CONTEXT            \
        NULLOBJ_SPK_ENDPOINT_CONTEXT
/* -------------------------           */


/**
 * OES异步API的连接通道运行时信息
 *
 * <p> @note 关于上一次会话的最大请求数据编号 (针对委托通道)
 * - 将通过 lastOutMsgSeq 字段存储上一次会话实际已发送的出向消息序号, 即: 服务器端最
 *   后接收到的客户委托流水号(clSeqNo)
 * - 该值对应的是服务器端最后接收到并校验通过的(同一环境号下的)客户委托流水号, 效果等价
 *   于 OesApi_InitOrdChannel接口的pLastClSeqNo参数的输出值
 * - 登录成功以后, API会将该值存储在 <code>pAsyncChannel->lastOutMsgSeq</code>
 *   和 <code>pSessionInfo->lastOutMsgSeq</code> 字段中
 * - 该字段在登录成功以后就不会再更新
 * - 客户端若想借用这个字段来维护自增的"客户委托流水号(clSeqNo)"也是可行的, 只是需要注
 *   意该字段在登录后会被重置为服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 * </p>
 *
 * <p> @note 关于最近接收到的回报数据编号 (针对回报通道):
 * - 将通过 lastInMsgSeq 字段存储上一次会话实际接收到的入向消息序号, 即: 最近接收到的
 *   回报数据编号
 * - 该字段会在接收到回报数据并回调OnMsg成功以后实时更新, 可以通过该字段获取到最近接收到
 *   的回报数据编号
 * - 当OnConnect函数指针为空时, 会执行默认的回报订阅处理, 此时会自动从断点位置继续订阅
 *   回报数据
 * - 若指定了OnConnect回调函数(函数指针不为空), 则需要显式的执行回报订阅处理
 * - API会将回报数据的断点位置存储在 <code>pAsyncChannel->lastInMsgSeq</code>
 *   和 <code>pSessionInfo->lastInMsgSeq</code> 字段中, 可以使用该值订阅回报
 * - 客户端可以在OnConnect回调函数中重新设置
 *   <code>pSessionInfo->lastInMsgSeq</code> 的取值来重新指定初始的回报订阅位置,
 *   效果等同于OesApi_InitRptChannel接口的lastRptSeqNum参数:
 *   - 等于0, 从头开始推送回报数据 (默认值)
 *   - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *   - 小于0, 从最新的数据开始推送回报数据
 * </p>
 */
typedef SEndpointChannelT           OesAsyncApiChannelT;


/* 结构体的初始化值定义 */
#define NULLOBJ_OESAPI_ASYNC_CHANNEL            \
        NULLOBJ_SPK_ENDPOINT_CHANNEL
/* -------------------------           */


/**
 * OES异步API的上下文环境的创建参数 (仅做为 CreateContext 接口的参数使用)
 */
typedef struct _OesAsyncApiContextParams {
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

    /** 为保证64位对齐而设 */
    uint8               __filler[8];
} OesAsyncApiContextParamsT;


/* 结构体初始化值定义 */
#define NULLOBJ_OESAPI_ASYNC_CONTEXT_PARAMS     \
        0, 0, 0, 0, 0, {0}

/* 结构体的默认值定义 */
#define DEFAULT_OESAPI_ASYNC_CONTEXT_PARAMS     \
        -1, TRUE, FALSE, TRUE, TRUE, {0}
/* -------------------------           */


/* ===================================================================
 * 回调函数的函数原型定义
 * =================================================================== */

/**
 * 对接收到的回报或应答消息进行处理的回调函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 和 #F_OESAPI_ON_RPT_MSG_T 的定义一致, 回调函数可以通用
 * - 对消息体数据(pMsgBody), 需要按照消息类型(pMsgHead->msgId)转换为对应的消息结构进行处理
 * - 具体使用方式可以参考样例代码中的 OesApiSample_HandleMsg 函数
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
 * @see     eOesMsgTypeT
 * @see     OesRspMsgBodyT
 * @see     OesRptMsgT
 */
typedef F_OESAPI_ON_RPT_MSG_T       F_OESAPI_ASYNC_ON_MSG_T;


/**
 * 异步API线程连接或重新连接完成后的回调函数的函数原型定义
 *
 * <p> 回调函数说明:
 * - 对于回报通道, 需要通过该回调函数完成回报订阅操作。若函数指针为空, 则会使用通道配置中默认的
 *   回报订阅参数进行订阅。若函数指针不为空, 但未订阅回报, 90秒以后服务器端会强制断开连接
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * <p> 关于回报数据的断点恢复 (针对回报通道):
 * - 当OnConnect函数指针为空时, 会执行默认的回报订阅处理, 此时会自动从断点位置继续订阅回报数据
 * - 若指定了OnConnect回调函数(函数指针不为空), 则需要显式的执行回报订阅处理
 * - API会将回报数据的断点位置存储在 <code>pAsyncChannel->lastInMsgSeq</code> 和
 *   <code>pSessionInfo->lastInMsgSeq</code> 字段中, 可以使用该值订阅回报
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
typedef int32   (*F_OESAPI_ASYNC_ON_CONNECT_T) (
                OesAsyncApiChannelT *pAsyncChannel,
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
typedef int32   (*F_OESAPI_ASYNC_ON_DISCONNECT_T) (
                OesAsyncApiChannelT *pAsyncChannel,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 上下文管理接口
 * =================================================================== */

/**
 * 创建异步API的运行时环境 (通过配置文件和默认的配置区段加载相关配置参数)
 *
 * - 与 OesAsyncApi_CreateContextSimple 接口的区别为, 会通过配置文件加载如下配置:
 *   - 日志配置
 *   - 异步API相关的扩展配置: 异步队列的大小、是否启动独立的回调线程来执行回调处理、是否使用
 *     忙等待模式等
 *   - 异步I/O线程配置 (@see OesAsyncApi_LoadIoThreadCfg)
 *   - CPU亲和性配置 (@see OesAsyncApi_LoadCpusetCfg)
 *
 * @param   pCfgFile            配置文件路径 (可为空, 为空则不加载配置文件)
 * @return  非空, 异步API的运行时环境指针; NULL, 失败
 */
OesAsyncApiContextT *
        OesAsyncApi_CreateContext(
                const char *pCfgFile);

/**
 * 创建异步API的运行时环境 (通过配置文件和指定的配置区段加载相关配置参数)
 *
 * - 与 OesAsyncApi_CreateContextSimple 接口的区别为, 会通过配置文件加载如下配置:
 *   - 日志配置
 *   - 异步API相关的扩展配置: 异步队列的大小、是否启动独立的回调线程来执行回调处理、是否使用
 *     忙等待模式等
 *   - 异步I/O线程配置 (@see OesAsyncApi_LoadIoThreadCfg)
 *   - CPU亲和性配置 (@see OesAsyncApi_LoadCpusetCfg)
 *
 * @param   pCfgFile            配置文件路径 (可为空, 为空则不加载配置文件)
 * @param   pLoggerSection      日志记录器的配置区段名称 (e.g. "log")
 *                              - 为空则忽略, 不初始化日志记录器
 * @param   pAsyncApiSection    异步API参数的配置区段名称 (e.g. "oes_client.async_api")
 *                              - 为空则忽略, 不加载异步API相关的配置
 * @param   pCpusetSection      CPU亲和性配置的配置区段名称 (e.g. "cpuset")
 *                              - 为空则忽略, 不加载CPU亲和性配置
 * @return  非空, 异步API的运行时环境指针; NULL, 失败
 */
OesAsyncApiContextT *
        OesAsyncApi_CreateContext2(
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
 * @param   asyncQueueSize      用于缓存回报数据的消息队列大小 (最大可缓存的消息数量)
 *                              - 等于0, 不创建缓存队列 (无需异步处理或落地回报数据)
 *                              - 小于0, 使用默认值 100000
 * @return  非空, 异步API的运行时环境指针; NULL, 失败
 */
OesAsyncApiContextT *
        OesAsyncApi_CreateContextSimple(
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
OesAsyncApiContextT *
        OesAsyncApi_CreateContextSimple2(
                const char *pLoggerCfgFile,
                const char *pLoggerSection,
                const OesAsyncApiContextParamsT *pContextParams);

/**
 * 释放异步API的运行时环境
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 */
void    OesAsyncApi_ReleaseContext(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 启动异步API线程
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_Start(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 终止异步API线程
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 */
void    OesAsyncApi_Stop(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 返回异步API的通信线程是否正在运行过程中
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  TRUE 正在运行过程中; FALSE 已终止或尚未运行
 */
BOOL    OesAsyncApi_IsRunning(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 返回异步API相关的所有线程是否都已经安全退出 (或尚未运行)
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  TRUE 所有线程均已退出; FALSE 尚未全部退出
 */
BOOL    OesAsyncApi_IsAllTerminated(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 返回异步API累计已提取和处理过的回报/应答消息数量
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  累计已提取和处理过的消息数量 (包括已处理但处理失败的消息)
 */
int64   OesAsyncApi_GetTotalPicked(
                OesAsyncApiContextT *pAsyncContext);
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
int32   OesAsyncApi_GetChannelCount(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 返回当前已连接的通道数量
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  已连接的通道数量
 */
int32   OesAsyncApi_GetConnectedChannelCount(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 添加通道配置信息
 *
 * @note 提示:
 * - 可以将委托通道和回报通道依次添加到同一个异步线程中
 * - 异步API尚不支持查询接口, 不能将查询通道添加到异步API中
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       channelType     待添加的通道类型, 仅支持如下两种类型:
 *                              - 1: 委托通道 (@see OESAPI_CHANNEL_TYPE_ORDER)
 *                              - 2: 回报通道 (@see OESAPI_CHANNEL_TYPE_REPORT)
 * @param       pChannelTag     通道配置信息的自定义标签 (可以为空)
 * @param       pRemoteCfg      待添加的通道配置信息 (不可为空)
 * @param       pSubscribeCfg   默认的回报订阅参数 (可以为空)
 * @param       fnOnMsg         进行消息处理的回调函数 (不可为空)
 * @param       pOnMsgParams    fnOnMsg回调函数的参数
 * @param       fnOnConnect     连接或重新连接完成后的回调函数 (可以为空)
 *                              - 若函数指针为空, 则会使用默认的回报订阅参数进行订阅
 * @param       pOnConnectParams
 *                              fnOnConnect回调函数的参数
 * @param       fnOnDisconnect  连接断开后的回调函数 (可以为空)
 * @param       pOnDisconnectParams
 *                              fnOnDisconnect回调函数的参数
 * @return      非空, 异步API的连接通道信息; 空, 失败
 */
OesAsyncApiChannelT *
        OesAsyncApi_AddChannel(
                OesAsyncApiContextT *pAsyncContext,
                eOesApiChannelTypeT channelType,
                const char *pChannelTag,
                const OesApiRemoteCfgT *pRemoteCfg,
                const OesApiSubscribeInfoT *pSubscribeCfg,
                F_OESAPI_ASYNC_ON_MSG_T fnOnMsg,
                void *pOnMsgParams,
                F_OESAPI_ASYNC_ON_CONNECT_T fnOnConnect,
                void *pOnConnectParams,
                F_OESAPI_ASYNC_ON_DISCONNECT_T fnOnDisconnect,
                void *pOnDisconnectParams);

/**
 * 从配置文件中加载通道配置信息, 并添加到异步API线程配置中
 *
 * @note 提示:
 * - 可以将委托通道和回报通道依次添加到同一个异步线程中
 * - 异步API尚不支持查询接口, 不能将查询通道添加到异步API中
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       channelType     待添加的通道类型, 仅支持如下两种类型:
 *                              - 1: 委托通道 (@see OESAPI_CHANNEL_TYPE_ORDER)
 *                              - 2: 回报通道 (@see OESAPI_CHANNEL_TYPE_REPORT)
 * @param       pChannelTag     通道配置信息的自定义标签 (可以为空)
 * @param       pCfgFile        配置文件路径 (不可为空)
 * @param       pCfgSection     配置区段名称 (不可为空)
 * @param       pAddrKey        服务器地址的配置项关键字 (不可为空)
 * @param       fnOnMsg         进行消息处理的回调函数 (不可为空)
 * @param       pOnMsgParams    fnOnMsg回调函数的参数
 * @param       fnOnConnect     连接或重新连接完成后的回调函数 (可以为空)
 *                              - 若函数指针为空, 则会使用默认的回报订阅参数进行订阅
 * @param       pOnConnectParams
 *                              fnOnConnect回调函数的参数
 * @param       fnOnDisconnect  连接断开后的回调函数 (可以为空)
 * @param       pOnDisconnectParams
 *                              fnOnDisconnect回调函数的参数
 * @return      非空, 异步API的连接通道信息; 空, 失败
 */
OesAsyncApiChannelT *
        OesAsyncApi_AddChannelFromFile(
                OesAsyncApiContextT *pAsyncContext,
                eOesApiChannelTypeT channelType,
                const char *pChannelTag,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey,
                F_OESAPI_ASYNC_ON_MSG_T fnOnMsg,
                void *pOnMsgParams,
                F_OESAPI_ASYNC_ON_CONNECT_T fnOnConnect,
                void *pOnConnectParams,
                F_OESAPI_ASYNC_ON_DISCONNECT_T fnOnDisconnect,
                void *pOnDisconnectParams);

/**
 * 返回顺序号对应的连接通道信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   channelType         通道类型
 *                              - 0: 任意类型
 *                              - 1: 委托通道 (@see OESAPI_CHANNEL_TYPE_ORDER)
 *                              - 2: 回报通道 (@see OESAPI_CHANNEL_TYPE_REPORT)
 * @param   channelIndex        通道顺序号
 *                              - 大于0: 返回与指定顺序号相对应的, 并且与指定通道类型相
 *                                匹配的通道信息 (顺序号与通道配置的添加顺序一致)
 *                              - 小于0: 返回第一个与指定通道类型相匹配的通道信息
 *                              - INT_MAX: 返回最后一个与指定通道类型相匹配的通道信息
 * @return  异步API的连接通道信息
 */
OesAsyncApiChannelT *
        OesAsyncApi_GetChannel(
                OesAsyncApiContextT *pAsyncContext,
                int32 channelType,
                int32 channelIndex);

/**
 * 返回标签对应的连接通道信息
 *
 * @note 注意事项:
 * - API不强制要求标签必须唯一, 如果标签不唯一, 则将返回第一个匹配到的通道信息
 * - 标签名称不区分大小写
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   channelType         通道类型
 *                              - 0: 任意类型
 *                              - 1: 委托通道 (@see OESAPI_CHANNEL_TYPE_ORDER)
 *                              - 2: 回报通道 (@see OESAPI_CHANNEL_TYPE_REPORT)
 * @param   pChannelTag         通道配置信息的自定义标签
 * @return  异步API的连接通道信息
 */
OesAsyncApiChannelT *
        OesAsyncApi_GetChannelByTag(
                OesAsyncApiContextT *pAsyncContext,
                int32 channelType,
                const char *pChannelTag);

/**
 * 遍历所有的连接通道信息并执行回调函数
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   channelType         待遍历的通道类型
 *                              - 0: 所有类型
 *                              - 1: 委托通道 (@see OESAPI_CHANNEL_TYPE_ORDER)
 *                              - 2: 回报通道 (@see OESAPI_CHANNEL_TYPE_REPORT)
 * @param   fnCallback          待执行的回调函数 (可以为空)
 *                              - 若返回值小于0, 则将中止遍历并返回该值
 * @param   pParams             回调函数的参数 (可以为空)
 * @return  大于等于0, 成功遍历到的通道数量; 小于0, 参数错误或者回调函数的返回值小于0
 */
int32   OesAsyncApi_ForeachChannel(
                OesAsyncApiContextT *pAsyncContext,
                int32 channelType,
                int32 (*fnCallback)(
                        OesAsyncApiChannelT *pAsyncChannel, void *pParams),
                void *pParams);

/**
 * 遍历所有的连接通道信息并执行回调函数
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   channelType         待遍历的通道类型
 *                              - 0: 所有类型
 *                              - 1: 委托通道 (@see OESAPI_CHANNEL_TYPE_ORDER)
 *                              - 2: 回报通道 (@see OESAPI_CHANNEL_TYPE_REPORT)
 * @param   fnCallback          待执行的回调函数 (可以为空)
 *                              - 若返回值小于0, 则将中止遍历并返回该值
 * @param   pParam1             回调函数的参数1 (可以为空)
 * @param   pParam2             回调函数的参数2 (可以为空)
 * @return  大于等于0, 成功遍历到的通道数量; 小于0, 参数错误或者回调函数的返回值小于0
 */
int32   OesAsyncApi_ForeachChannel2(
                OesAsyncApiContextT *pAsyncContext,
                int32 channelType,
                int32 (*fnCallback)(
                        OesAsyncApiChannelT *pAsyncChannel,
                        void *pParam1, void *pParam2),
                void *pParam1,
                void *pParam2);

/**
 * 遍历所有的连接通道信息并执行回调函数
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   channelType         待遍历的通道类型
 *                              - 0: 所有类型
 *                              - 1: 委托通道 (@see OESAPI_CHANNEL_TYPE_ORDER)
 *                              - 2: 回报通道 (@see OESAPI_CHANNEL_TYPE_REPORT)
 * @param   fnCallback          待执行的回调函数 (可以为空)
 *                              - 若返回值小于0, 则将中止遍历并返回该值
 * @param   pParam1             回调函数的参数1 (可以为空)
 * @param   pParam2             回调函数的参数2 (可以为空)
 * @param   pParam3             回调函数的参数3 (可以为空)
 * @return  大于等于0, 成功遍历到的通道数量; 小于0, 参数错误或者回调函数的返回值小于0
 */
int32   OesAsyncApi_ForeachChannel3(
                OesAsyncApiContextT *pAsyncContext,
                int32 channelType,
                int32 (*fnCallback)(OesAsyncApiChannelT *pAsyncChannel,
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
BOOL    OesAsyncApi_IsChannelConnected(
                OesAsyncApiChannelT *pAsyncChannel);

/**
 * 返回通道对应的配置信息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @return  通道配置信息
 */
OesAsyncApiChannelCfgT *
        OesAsyncApi_GetChannelCfg(
                OesAsyncApiChannelT *pAsyncChannel);

/**
 * 返回通道对应的回报订阅配置信息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @return  回报订阅配置信息
 */
OesApiSubscribeInfoT *
        OesAsyncApi_GetChannelSubscribeCfg(
                OesAsyncApiChannelT *pAsyncChannel);

/**
 * 注册和连接通道有共生关系的会话信息
 * 当连接通道断开后将自动触发有共生关系的会话信息断开
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pObserverSession    有共生关系的会话信息
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_RegisterSymbioticSession(
                OesAsyncApiChannelT *pAsyncChannel,
                OesApiSessionInfoT  *pObserverSession);
/* -------------------------           */


/* ===================================================================
 * 委托申报接口
 * =================================================================== */

/**
 * 发送委托申报请求
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * @param       pAsyncOrdChannel
 *                              异步API的委托连接通道
 * @param       pOrdReq         待发送的委托申报请求
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesAsyncApi_SendOrderReq(
                OesAsyncApiChannelT *pAsyncOrdChannel,
                const OesOrdReqT *pOrdReq);

/**
 * 发送撤单请求
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * @param       pAsyncOrdChannel
 *                              异步API的委托连接通道
 * @param       pCancelReq      待发送的撤单请求
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesAsyncApi_SendOrderCancelReq(
                OesAsyncApiChannelT *pAsyncOrdChannel,
                const OesOrdCancelReqT *pCancelReq);

/**
 * 批量发送多条委托请求
 * 以批量的形式同时发送多笔委托申报, 而风控检查等处理结果则仍以单笔委托为单位通过回报数据返回
 *
 * - 批量委托的委托请求填充规则与单条委托完全相同, 回报处理规则也与单条委托完全相同:
 *   - 每笔委托请求的 "客户委托流水号(clSeqNo)" 同样必须填充, 并需要维持在同一客户端下的唯一性
 *   - 服务器端的处理结果则仍将以单笔委托为单位通过回报数据返回
 *
 * @param       pAsyncOrdChannel
 *                              异步API的委托连接通道
 * @param       ppOrdPtrList    待发送的委托请求列表 (指针数组)
 * @param       ordCount        待发送的委托请求数量
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesAsyncApi_SendBatchOrdersReq(
                OesAsyncApiChannelT *pAsyncOrdChannel,
                const OesOrdReqT *ppOrdPtrList[],
                int32 ordCount);

/**
 * 批量发送多条委托请求
 * 以批量的形式同时发送多笔委托申报, 而风控检查等处理结果则仍以单笔委托为单位通过回报数据返回
 *
 * - 批量委托的委托请求填充规则与单条委托完全相同, 回报处理规则也与单条委托完全相同:
 *   - 每笔委托请求的 "客户委托流水号(clSeqNo)" 同样必须填充, 并需要维持在同一客户端下的唯一性
 *   - 服务器端的处理结果则仍将以单笔委托为单位通过回报数据返回
 *
 * @param       pAsyncOrdChannel
 *                              异步API的委托连接通道
 * @param       pOrdReqArray    待发送的委托请求数组 (连续的存储空间)
 * @param       ordCount        待发送的委托请求数量
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesAsyncApi_SendBatchOrdersReq2(
                OesAsyncApiChannelT *pAsyncOrdChannel,
                OesOrdReqT *pOrdReqArray,
                int32 ordCount);

/**
 * 发送出入金委托请求
 * 以单向异步消息的方式发送委托申报到OES服务器, OES的实时风控检查等处理结果将通过回报数据返回
 *
 * @param       pAsyncOrdChannel
 *                              异步API的委托连接通道
 * @param       pFundTrsfReq    待发送的出入金委托请求
 * @retval      0               成功
 * @retval      <0              失败 (负的错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesAsyncApi_SendFundTransferReq(
                OesAsyncApiChannelT *pAsyncOrdChannel,
                const OesFundTrsfReqT *pFundTrsfReq);

/**
 * 异步发送密码修改请求 (修改客户端登录密码)
 * 密码修改请求将通过委托通道发送到OES服务器, 仅发送请求不接收应答消息
 *
 * @param       pAsyncOrdChannel
 *                              异步API的委托连接通道
 * @param[in]   pChangePasswordReq
 *                              待发送的密码修改请求
 * @retval      0               成功
 * @retval      <0              API调用失败 (负的错误号)
 * @retval      >0              服务端业务处理失败 (OES错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesAsyncApi_SendChangePasswordReq(
                OesAsyncApiChannelT *pAsyncOrdChannel,
                const OesChangePasswordReqT *pChangePasswordReq);
/* -------------------------           */


/* ===================================================================
 * 期权业务特有的委托接口
 * =================================================================== */

/**
 * 期权账户结算单确认
 * 结算单确认请求将通过委托通道发送到OES服务器, 并将采用同步请求/应答的方式直接返回处理结果
 *
 * - 结算单确认后, 方可进行委托申报和出入金请求
 *
 * @param       pAsyncOrdChannel
 *                              异步API的委托连接通道
 * @param[in]   pOptSettlementConfirmReq
 *                              待发送的结算单确认请求
 *                              - 客户端仅关联一个客户时, 可传空指针或不指定客户代码
 * @param[out]  pOptSettlementConfirmRsp
 *                              用于输出结算单确认请求应答的缓存区
 * @retval      0               成功
 * @retval      <0              API调用失败 (负的错误号)
 * @retval      >0              服务端业务处理失败 (OES错误号)
 *
 * @exception   EINVAL          传入参数非法
 * @exception   EPIPE           连接已破裂
 * @exception   Others          由send()系统调用返回的错误
 */
int32   OesAsyncApi_SendOptSettlementConfirmReq(
                OesAsyncApiChannelT *pAsyncOrdChannel,
                const OesOptSettlementConfirmReqT *pOptSettlementConfirmReq,
                OesOptSettlementConfirmRspT *pOptSettlementConfirmRsp);
/* -------------------------           */


/* ===================================================================
 * 会话管理接口
 * =================================================================== */

/**
 * 发送回报同步消息 (仅适用于回报通道)
 *
 * @param   pAsyncRptChannel    异步API的回报连接通道
 * @param   subscribeEnvId      待订阅的客户端环境号
 *                              - 大于0, 区分环境号, 仅订阅环境号对应的回报数据
 *                              - 等于0, 不区分环境号, 订阅该客户下的所有回报数据
 *                              - 小于0, 复用添加通道时指定的默认配置
 *                                  - @note 此处与同步API不同. 小于0时, 同步API为不区
 *                                    分环境号
 * @param   subscribeRptTypes   待订阅的回报消息种类 (e.g.
 *                              OES_SUB_RPT_TYPE_ORDER_INSERT
 *                              | OES_SUB_RPT_TYPE_ORDER_REPORT
 *                              | OES_SUB_RPT_TYPE_TRADE_REPORT)
 *                              @see eOesSubscribeReportTypeT
 *                              - 小于0, 复用添加通道时指定的默认配置
 *                                  - @note 此处与同步API不同. 小于0时, 同步API为订阅
 *                                    所有类型的消息
 * @param   lastRptSeqNum       客户端最后接收到的回报数据的回报编号
 *                              - 等于0, 从头开始推送回报数据
 *                              - 大于0, 从指定的回报编号开始推送回报数据
 *                              - 小于0, 从上次接收到的断点位置开始
 *                                  - @note 此处与同步API不同. 小于0时, 同步API为从最
 *                                    新的数据开始推送回报数据
 *                                  - 如果明确需要只从最新的数据开始推送回报数据, 可以指
 *                                    定一个特别大的数 (例如 INT_MAX)
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_SendReportSynchronization(
                OesAsyncApiChannelT *pAsyncRptChannel,
                int8 subscribeEnvId,
                int32 subscribeRptTypes,
                int64 lastRptSeqNum);

/**
 * 发送心跳消息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_SendHeartbeat(
                OesAsyncApiChannelT *pAsyncChannel);

/**
 * 发送测试请求消息
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pTestReqId          测试请求标识符 (C32, 可以为空)
 * @param   testReqIdSize       测试请求标识符的长度
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_SendTestReq(
                OesAsyncApiChannelT *pAsyncChannel,
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
 *                              通信线程(回报接收线程)的CPU亲和性配置项关键字
 * @param       pCallbackThreadCpusetKey
 *                              异步回调线程的CPU亲和性配置项关键字
 * @param       pIoThreadCpusetKey
 *                              异步I/O线程的CPU亲和性配置项关键字
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_LoadCpusetCfg(
                OesAsyncApiContextT *pAsyncContext,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pCommunicationCpusetKey,
                const char *pCallbackThreadCpusetKey,
                const char *pIoThreadCpusetKey);

/**
 * 设置通信线程(回报接收线程)的CPU亲和性配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pCommunicationCpuset
 *                              通信线程绑定的CPU列表 (以逗号或空格分割的CPU编号列表, CPU编号从1开始)
 *                              - e.g. "1"      绑定到 0 号核
 *                              - e.g. "1,3,5"  绑定到 0,2,4 号核
 *                              - NULL 或者 "", 不绑定CPU
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_SetCommunicationCpusetCfg(
                OesAsyncApiContextT *pAsyncContext,
                const char *pCommunicationCpuset);

/**
 * 返回通信线程(回报接收线程)的CPU亲和性配置信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  CPU亲和性配置信息
 */
const char *
        OesAsyncApi_GetCommunicationCpusetCfg(
                OesAsyncApiContextT *pAsyncContext);

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
BOOL    OesAsyncApi_SetCallbackThreadCpusetCfg(
                OesAsyncApiContextT *pAsyncContext,
                const char *pCallbackThreadCpuset);

/**
 * 返回异步回调线程的CPU亲和性配置信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  CPU亲和性配置信息
 */
const char *
        OesAsyncApi_GetCallbackThreadCpusetCfg(
                OesAsyncApiContextT *pAsyncContext);

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
BOOL    OesAsyncApi_SetIoThreadCpusetCfg(
                OesAsyncApiContextT *pAsyncContext,
                const char *pIoThreadCpuset);

/**
 * 返回异步I/O线程的CPU亲和性配置信息
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  CPU亲和性配置信息
 */
const char *
        OesAsyncApi_GetIoThreadCpusetCfg(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 设置是否在启动前预创建并校验所有的连接
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   isPreconnectAble    是否在启动前预创建并校验所有的连接
 *                              TRUE: 启动前预创建并校验所有的连接, 如果连接失败则中止启动
 *                              FALSE: 启动前不预先创建和校验连接 (默认行为)
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_SetPreconnectAble(
                OesAsyncApiContextT *pAsyncContext,
                BOOL isPreconnectAble);

/**
 * 返回是否在启动前预创建并校验所有的连接
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否在启动前预创建并校验所有的连接
 */
BOOL    OesAsyncApi_IsPreconnectAble(
                OesAsyncApiContextT *pAsyncContext);

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
BOOL    OesAsyncApi_SetTakeoverStartThreadFlag(
                OesAsyncApiContextT *pAsyncContext,
                int32 isTakeoverStartThread);

/**
 * 返回是否接管启动线程
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否接管启动线程
 */
int32   OesAsyncApi_GetTakeoverStartThreadFlag(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 设置是否启动独立的回调线程来执行回调处理
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @param   isAsyncCallbackAble 是否启动独立的回调线程来执行回调处理
 *                              - TRUE: 创建单独的回调线程
 *                              - FALSE: 不启动单独的回调线程, 直接在通信线程下执行回调处理 (默认行为)
 * @return  TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_SetAsyncCallbackAble(
                OesAsyncApiContextT *pAsyncContext,
                BOOL isAsyncCallbackAble);

/**
 * 返回是否启动独立的回调线程来执行回调处理
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否启动独立的回调线程来执行回调处理
 */
BOOL    OesAsyncApi_IsAsyncCallbackAble(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 设置异步回调线程的忙等待模式
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       isBusyPollAble  是否使用忙等待模式
 *                              TRUE: 使用忙等待模式, 延迟更低, 但CPU会被100%占用
 *                              FALSE: 不使用忙等待模式, 延迟和CPU使用率相对均衡
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_SetAsyncCallbackBusyPollAble(
                OesAsyncApiContextT *pAsyncContext,
                BOOL isBusyPollAble);

/**
 * 返回异步回调线程的忙等待模式
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  是否使用忙等待模式
 */
BOOL    OesAsyncApi_IsAsyncCallbackBusyPollAble(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 返回异步通信队列的长度
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  异步通信队列的长度 (可缓存的最大消息数量)
 */
int64   OesAsyncApi_GetAsyncQueueLength(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 返回异步通信队列的数据空间大小
 *
 * @param   pAsyncContext       异步API的运行时环境指针
 * @return  异步通信队列的数据空间大小 (字节数)
 */
int64   OesAsyncApi_GetAsyncQueueDataAreaSize(
                OesAsyncApiContextT *pAsyncContext);

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
BOOL    OesAsyncApi_SetIoThreadCfg(
                OesAsyncApiContextT *pAsyncContext,
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
OesAsyncApiIoThreadCfgT *
        OesAsyncApi_GetIoThreadCfg(
                OesAsyncApiContextT *pAsyncContext);

/**
 * 从配置文件中加载异步I/O线程配置
 *
 * @param[out]  pAsyncContext   异步API的运行时环境指针
 * @param       pCfgFile        配置文件路径
 * @param       pCfgSection     配置区段名称
 * @return      TRUE 成功; FALSE 失败
 */
BOOL    OesAsyncApi_LoadIoThreadCfg(
                OesAsyncApiContextT *pAsyncContext,
                const char *pCfgFile,
                const char *pCfgSection);
/* -------------------------           */


/* ===================================================================
 * 辅助的 Inline 函数
 * =================================================================== */

/**
 * 返回异步API线程是否正在运行过程中
 *
 * OesAsyncApi_IsRunning 接口的 inline 简化版本
 *
 * @param   pAsyncContext       异步API的运行时环境指针 (@note 参数不能为空)
 * @return  TRUE 正在运行过程中; FALSE 已终止或尚未运行
 */
static __inline BOOL
__OesAsyncApi_IsRunning(OesAsyncApiContextT *pAsyncContext) {
    return pAsyncContext->pInternalRefs != NULL
            && *((volatile uint8 *) &pAsyncContext->terminateFlag) == 0;
}


/**
 * 返回通道是否已连接就绪
 *
 * OesAsyncApi_IsChannelConnected 接口的 inline 版本
 *
 * @param   pAsyncChannel       异步API的连接通道信息 (@note 参数不能为空)
 * @return  TRUE 已连接就绪; FALSE 尚未连接就绪
 */
static __inline BOOL
__OesAsyncApi_IsChannelConnected(OesAsyncApiChannelT *pAsyncChannel) {
    return pAsyncChannel->pSessionInfo
            && (*((volatile uint8 *) &pAsyncChannel->isConnected)
                    >= SPK_ENDPOINT_CHANNEL_STATUS_READY);
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_ASYNC_API_H */
