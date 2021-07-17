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
 * @file    spk_log_instance.h
 *
 * 日志记录器实例管理接口的头文件 (非线程安全)
 *
 * @version $Id$
 * @since   2005.10.31
 */


#ifndef _SPK_LOG_INSTANCE_H
#define _SPK_LOG_INSTANCE_H


#include    <sutil/types.h>
#include    <sutil/logger/spk_log_level.h>
#include    <sutil/logger/spk_log_mode.h>
#include    <sutil/logger/spk_log_config.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 结构体定义
 * =================================================================== */

/**
 * 日志记录器定义
 */
typedef struct _SLogAppender {
    /** 日志模式 */
    const SLogModeT     *pLogMode;
    /** 日志登记函数 */
    void                (*fnLogger) (
                        const struct _SLogAppender *pLogAppender,
                        const char *pLogFile,
                        const SLogLevelT *pLevel,
                        const char *pMsg,
                        int32 msgLength);

    void                *pShmAddr;              /**< 异步日志队列的共享内存地址 */
    void                *pQueueAccessor;        /**< 异步日志队列的存取器指针 */

    int8                minLogLevel;            /**< 日志登记的起始级别 */
    int8                maxLogLevel;            /**< 日志登记的最高级别 */
    uint8               appenderType;           /**< 日志记录器类型 */
    uint8               isAsyncLog;             /**< 是否是异步日志 */

    int32               maxFileLength;          /**< 日志文件最大长度 */
    int32               maxBackupCount;         /**< 日志文件最大备份数 */

    int32               appenderIndex;          /**< 日志记录器序号 */
    int32               asyncQueueSize;         /**< 异步日志的消息队列大小 */
    int32               asyncQueueShmId;        /**< 异步日志的共享内存ID (0 表示使用默认值) */

    /** 日志配置区段名称 */
    char                logSection[SLOGCFG_MAX_SECTION_LENGTH];
    /** 日志文件名称 */
    char                logFile[SPK_MAX_PATH_LEN];
} SLogAppenderT;


/* 结构体初始化值定义 */
#define NULLOBJ_LOG_APPENDER                    \
        0, 0, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, \
        {0}, {0}
/* -------------------------           */


/* ===================================================================
 * 普通的日志记录器(非异步日志)函数声明
 * =================================================================== */

/* 根据配置文件初始化日志实例 */
BOOL    SLog_InitLogger(
                const char *pConfigFile,
                const char *pRootSection,
                const char *pLogSystemName);

/* 根据配置文件初始化日志实例(可指定配置项名称) */
BOOL    SLog_InitLoggerExceptive(
                const char *pConfigFile,
                const char *pRootSection,
                const char *pRootCategoryField,
                const char *pLogSystemName);

/* 根据配置结构初始化日志实例 */
BOOL    SLog_BuildLogInstance(
                const SLogCfgItemT *pLogConfigs,
                int32 logConfigCount,
                const SLogCfgSectionInfoT *pLogSections,
                int32 logSectionCount,
                const char *pLogSystemName,
                const SLogLevelT *pAllowableMinLogLevel);

/* 重新解析、应用日志配置 */
BOOL    SLog_RebuildLogInstance();

/* 重新解析、应用日志配置 */
BOOL    SLog_RebuildLogInstance2(
                const char *pLogSystemName);

/* 重新解析、应用日志配置 */
BOOL    SLog_RebuildThreadInstance();

/* 重新解析、应用日志配置 */
BOOL    SLog_RebuildThreadInstance2(
                const char *pLogSystemName);

/* 返回日志系统是否已初始化 */
BOOL    SLog_IsInstanceInitialized();

/* 返回日志系统名称 */
const char*
        SLog_GetLogSystemName();

/* 设置日志系统名称 */
void    SLog_SetLogSystemName(
                const char *pLogSystemName);

/* 设置线程级别的日志系统名称 */
void    SLog_SetThreadLogName(
                const char *pLogSystemName);

/* 返回最小日志登记级别 */
const SLogLevelT*
        SLog_GetMinLogLevel();

/* 设置最小日志登记级别 */
void    SLog_SetMinLogLevel(
                const SLogLevelT *pMinLogLevel);

/* 返回日志记录器所对应的日志文件路径 */
const char*
        SLog_GetLogFile(
                const SLogAppenderT *pAppender);

/* 设置线程级别的最小日志登记级别 */
void    SLog_SetThreadMinLogLevel(
                const SLogLevelT *pMinLogLevel);

/* 返回最小日志登记级别的级别限定 (通过SetMinLogLevel设置的最小日志级别将不会低于该限定) */
const SLogLevelT*
        SLog_GetMinLevelLimit();

/* 设置最小日志登记级别的级别限定 (通过SetMinLogLevel设置的最小日志级别将不能低于该限定) */
void    SLog_SetMinLevelLimit(
                const SLogLevelT *pMinLogLevel);

/* 判断指定的日志级别是否可用 */
BOOL    SLog_IsLogLevelAble(
                const SLogLevelT *pLevel);

/* 返回日志屏蔽标志 */
int32   SLog_GetLogMask();

/* 设置日志屏蔽标志 */
void    SLog_SetLogMask(int32 logMask);

/* 重置日志屏蔽标志 */
void    SLog_ResetLogMask();

/* 关闭所有的日志屏蔽标志 (使能所有类型的日志输出) */
void    SLog_DisableAllMask();

/* 关闭指定类型的日志屏蔽标志 (使能指定类型的日志输出) */
void    SLog_DisableSpecifyMask(int32 logMask);

/* 开启所有的日志屏蔽标志 (屏蔽所有类型的日志输出) */
void    SLog_EnableAllMask();

/* 开启指定类型的日志屏蔽标志 (屏蔽指定类型的日志输出) */
void    SLog_EnableSpecifyMask(int32 logMask);

/* 返回日志记录器列表 */
const SLogAppenderT*
        SLog_GetLogAppenderList();

/* 返回指定位置的日志记录器 */
const SLogAppenderT*
        SLog_GetLogAppender(int32 index);

/* 检索并返还与日志配置区段名称相匹配的日志记录器 */
const SLogAppenderT*
        SLog_GetLogAppenderByName(const char *pSectionName);

/* 返回日志记录器个数 */
int32   SLog_GetLogAppenderCount();

/* 返回原始日志配置项个数 */
int32   SLog_GetOriginalLogConfigItemsCount();

/* 返回指定位置的原始日志配置项 */
const SLogCfgItemT*
        SLog_GetOriginalLogConfigItem(int32 index);

/* 返回默认的日志记录器 */
const SLogAppenderT*
        SLog_GetDefaultLogAppender();

/* 打印日志配置信息 */
void    SLog_PrintLogInstanceInfo(FILE *fp);
/* -------------------------           */


/* ===================================================================
 * 异步日志相关的函数声明
 * =================================================================== */

/* 创建所有异步日志使用的共享内存队列 */
BOOL    SLog_CreateAsyncLogQueues();

/* 释放所有异步日志使用的共享内存队列 */
BOOL    SLog_ReleaseAsyncLogQueues();

/* 激活所有的异步日志记录器 */
BOOL    SLog_EnableAsyncLogAppenders();

/* 激活指定的异步日志记录器 */
BOOL    SLog_EnableAsyncLogAppender(SLogAppenderT *pLogAppender);

/* 禁用所有的异步日志记录器 (改为使用普通的日志文件模式) */
BOOL    SLog_DisableAsyncLogAppenders();

/* 禁用指定的异步日志记录器 (改为使用普通的日志文件模式, 并断开与日志队列的连接) */
BOOL    SLog_DisableAsyncLogAppender(SLogAppenderT *pLogAppender);

/* 禁用指定的异步日志记录器 (改为使用普通的日志文件模式) */
BOOL    SLog_DisableAsyncLogAppender2(
                SLogAppenderT *pLogAppender,
                BOOL detachQueue);

/* 创建并启动所有的异步日志记录器的文件写入线程 */
int32   SLog_StartAsyncLogWriterThreads(
                volatile int32 *pNormalTerminatedFlag,
                volatile int32 *pExceptionAbortedFlag,
                BOOL isWaitThreadsTerminated);
/* -------------------------           */


/* ===================================================================
 * 隐含的接口函数声明, 外部不应直接使用这些接口, 而应该使用相应的宏接口
 * =================================================================== */

/* 日志登记处理实现声明 */
void    _SLog_LogImpl(
                const char *pSrcFile,
                int32 fileNameLength,
                int32 srcLine,
                const char *pSrcFunction,
                int32 logMask,
                const SLogLevelT *pLevel,
                const char *fmt, ...);
/* -------------------------           */


/* ===================================================================
 * 隐含的接口函数声明, 外部不应直接使用这些接口, 而应该使用响应的宏接口
 * 为不支持变参宏的系统而设
 * =================================================================== */

/*
 * 日志登记处理实现声明 (为不支持变参宏的系统而设)
 */
void    _SLog_LogSimpleness(const char *fmt, ...);
void    _SLog_LogFullSimpleness(SLogLevelT *level, const char *fmt, ...);
void    _SLog_TraceSimpleness(const char *fmt, ...);
void    _SLog_DebugSimpleness(const char *fmt, ...);
void    _SLog_InfoSimpleness(const char *fmt, ...);
void    _SLog_WarnSimpleness(const char *fmt, ...);
void    _SLog_ErrorSimpleness(const char *fmt, ...);
void    _SLog_BzInfoSimpleness(const char *fmt, ...);
void    _SLog_BzWarnSimpleness(const char *fmt, ...);
void    _SLog_BzErrorSimpleness(const char *fmt, ...);
void    _SLog_FatalSimpleness(const char *fmt, ...);

void    _SLog_LogSimplenessMasked(const char *fmt, ...);
void    _SLog_LogFullSimplenessMasked(SLogLevelT *level, const char *fmt, ...);
void    _SLog_TraceSimplenessMasked(const char *fmt, ...);
void    _SLog_DebugSimplenessMasked(const char *fmt, ...);
void    _SLog_InfoSimplenessMasked(const char *fmt, ...);
void    _SLog_WarnSimplenessMasked(const char *fmt, ...);
void    _SLog_ErrorSimplenessMasked(const char *fmt, ...);
void    _SLog_BzInfoSimplenessMasked(const char *fmt, ...);
void    _SLog_BzWarnSimplenessMasked(const char *fmt, ...);
void    _SLog_BzErrorSimplenessMasked(const char *fmt, ...);
void    _SLog_FatalSimplenessMasked(const char *fmt, ...);

void    _SLog_AssertSimpleness(BOOL EXPR, const char *fmt, ...);
void*   _SLog_AssertSimplenessRV(BOOL EXPR, void *retValue,
                const char *fmt, ...);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_INSTANCE_H */

