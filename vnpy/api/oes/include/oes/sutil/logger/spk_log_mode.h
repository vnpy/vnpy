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
 * @file    spk_log_mode.h
 *
 * 日志模式定义头文件
 *
 * @version $Id$
 * @since   2004.12.23
 */


#ifndef _SPK_LOG_MODE_H
#define _SPK_LOG_MODE_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/logger/spk_log_type.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定义
 */
/** 日志内容的最大长度 */
#define     SLOG_MAX_INFO_SIZE      (SPK_MAX_BLOCK_SIZE)
/* TODO 日志内容的最大长度
#define     SLOG_MAX_INFO_SIZE      (PIPE_BUF)
*/

/** 日志模式名称的长度 */
#define     SLOG_MAX_MODE_NAME      (32)
/* -------------------------           */


/**
 * 日志模式结构体定义
 */
typedef struct _SLogMode {
    uint8               mode;                       /**< 日志模式代码 */
    uint8               appenderType;               /**< 日志记录器类型 */
    uint8               isAsyncLog;                 /**< 是否是异步日志 */
    uint8               __filler1[5];               /**< 按64位对齐的填充域 */

    void                *logFn;                     /**< 日志实现函数 */
    void                *__filler2;                 /**< 按64位对齐的填充域 */
    char                name[SLOG_MAX_MODE_NAME];   /**< 日志模式名称 */
} SLogModeT;
/* -------------------------           */


/**
 * 日志级别定义表
 */
extern  SLogModeT __SPK_DLL_IMPORT      __SPK_slogModes[];


/*
 * 日志级别常量定义
 */
/** 日志模式 - 文件日志(FILE) - 等同FILE_ROLLING */
#define SLOG_MODE_FILE                  (&__SPK_slogModes[0])

/** 日志模式 - 文件日志(FILE_ROLLING) - 轮换, 不区分具体日期 */
#define SLOG_MODE_FILE_ROLLING          (&__SPK_slogModes[1])

/** 日志模式 - 文件日志(FILE_DAILY_ROLLING) - 每天N个日志文件(N >= 1) */
#define SLOG_MODE_FILE_DAILY_ROLLING    (&__SPK_slogModes[2])

/** 日志模式 - 文件日志(FILE_DAILY) - 每天一个日志文件 */
#define SLOG_MODE_FILE_DAILY            (&__SPK_slogModes[3])

/** 日志模式 - 控制台日志(CONSOLE) - 等同CONSOLE_STDOUT */
#define SLOG_MODE_CONSOLE               (&__SPK_slogModes[4])

/** 日志模式 - 控制台日志(CONSOLE_STDOUT) - 输出到stdout */
#define SLOG_MODE_CONSOLE_STDOUT        (&__SPK_slogModes[5])

/** 日志模式 - 控制台日志(CONSOLE_STDERR) - 输出到stderr */
#define SLOG_MODE_CONSOLE_STDERR        (&__SPK_slogModes[6])

/** 日志模式 - 异步文件日志(ASYNC_FILE) */
#define SLOG_MODE_ASYNC_FILE            (&__SPK_slogModes[7])
/* -------------------------           */


/*
 * 函数定义
 */

/*
 * 返回名称对应的日志模式
 */
const SLogModeT*
        SLog_GetLogMode(const char *modeName);

/*
 * 返回日志模式对应的日志记录器类型是否是文件记录器
 */
BOOL    SLog_IsFileLogAppender(const SLogModeT *logMode);

/*
 * 返回日志模式对应的日志记录器类型是否是异步日志记录器
 */
BOOL    SLog_IsAsyncLogAppender(const SLogModeT *logMode);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_MODE_H */

