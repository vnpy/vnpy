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
 * @file    spk_log_level.h
 *
 * 日志级别定义头文件
 *
 * @version $Id$
 * @since   2004.4.26
 */


#ifndef _SPK_LOG_LEVEL_H
#define _SPK_LOG_LEVEL_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定义
 */
#define     SLOG_MAX_LEVEL_NAME         (32)        /**< 日志级别名称的长度 */
/* -------------------------           */


/**
 * 日志级别结构体定义
 */
typedef struct _SLogLevel {
    int8                level;                      /**< 日志级别代码 */
    int8                __filler[7];                /**< 日志级别代码 */

    char                name[SLOG_MAX_LEVEL_NAME];  /**< 日志级别名称 */
} SLogLevelT;
/* -------------------------           */


/**
 * 日志级别定义表
 */
extern  SLogLevelT __SPK_DLL_IMPORT     __SPK_slogLevels[];


/*
 * 日志级别常量定义
 */
/** 日志级别-跟踪信息 (TRACE) */
#define     SLOG_LEVEL_TRACE            (&__SPK_slogLevels[0])
/** 日志级别-调试信息 (DEBUG) */
#define     SLOG_LEVEL_DEBUG            (&__SPK_slogLevels[1])
/** 日志级别-提示信息 (INFO) */
#define     SLOG_LEVEL_INFO             (&__SPK_slogLevels[2])
/** 日志级别-警告信息 (WARN) */
#define     SLOG_LEVEL_WARN             (&__SPK_slogLevels[3])
/** 日志级别-错误信息 (ERROR) */
#define     SLOG_LEVEL_ERROR            (&__SPK_slogLevels[4])

/** 日志级别-业务提示 (BZINF, BZ_INFO) */
#define     SLOG_LEVEL_BZ_INFO          (&__SPK_slogLevels[5])
/** 日志级别-业务警告 (BZWRN, BZ_WARN) */
#define     SLOG_LEVEL_BZ_WARN          (&__SPK_slogLevels[6])
/** 日志级别-业务错误 (BZERR, BZ_ERROR) */
#define     SLOG_LEVEL_BZ_ERROR         (&__SPK_slogLevels[7])
/** 日志级别-致命错误 (FATAL) */
#define     SLOG_LEVEL_FATAL            (&__SPK_slogLevels[8])
/** 日志级别-屏蔽所有日志 (NONE) */
#define     SLOG_LEVEL_NONE             (&__SPK_slogLevels[9])
/* -------------------------           */


/**
 * 日志级别值定义
 */
typedef enum _eSLogLevelValue {
    SLOG_LEVEL_VALUE_TRACE      = 0,                /**< 日志级别-跟踪信息 (TRACE) */
    SLOG_LEVEL_VALUE_DEBUG      = 1,                /**< 日志级别-调试信息 (DEBUG) */
    SLOG_LEVEL_VALUE_INFO       = 2,                /**< 日志级别-提示信息 (INFO) */
    SLOG_LEVEL_VALUE_WARN       = 3,                /**< 日志级别-警告信息 (WARN) */
    SLOG_LEVEL_VALUE_ERROR      = 4,                /**< 日志级别-错误信息 (ERROR) */

    SLOG_LEVEL_VALUE_BZ_INFO    = 5,                /**< 日志级别-业务提示 (BZINF, BZ_INFO) */
    SLOG_LEVEL_VALUE_BZ_WARN    = 6,                /**< 日志级别-业务警告 (BZWRN, BZ_WARN) */
    SLOG_LEVEL_VALUE_BZ_ERROR   = 7,                /**< 日志级别-业务错误 (BZERR, BZ_ERROR) */
    SLOG_LEVEL_VALUE_FATAL      = 8,                /**< 日志级别-致命错误 (FATAL) */
    SLOG_LEVEL_VALUE_NONE       = 9,                /**< 日志级别-屏蔽所有日志 (NONE) */
    __SLOG_LEVEL_VALUE_MAX
} eSLogLevelValueT;
/* -------------------------           */


/*
 * 函数定义
 */

/*
 * 返回名称对应的日志级别
 */
const SLogLevelT*   SLog_GetLogLevel(const char *levelName);

/*
 * 返回日志级别值所对应的日志级别
 */
const SLogLevelT*   SLog_GetLogLevelByValue(int8 levelValue);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_LEVEL_H */
