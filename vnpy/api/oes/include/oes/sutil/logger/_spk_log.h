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
 * @file    _spk_log.h
 *
 * 日志处理程序的头文件
 *
 * <p>相关缩写: <ul>
 * <li>slog: simple logger</li>
 * </ul></p>
 *
 * <p>相关的预定义宏: <ul>
 * <li>NO_LOG: 关闭所有日志</li>
 * <li>NO_DEBUG: 关闭 DEBUG 和 TRACE 级别的日志</li>
 * <li>NO_TRACE: 关闭 TRACE 级别的日志</li>
 * <li>NO_VA_MACRO: 不支持变参宏</li>
 * <li>_CHECK_LOG_FORMAT: 在编译时检查格式化字符串的格式</li>
 * </ul></p>
 *
 * @version $Id$
 * @since   2004/4/26
 */


#ifndef __SPK_LOGGER_H
#define __SPK_LOGGER_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/logger/spk_log_type.h>
#include    <sutil/logger/spk_log_level.h>
#include    <sutil/logger/spk_log_instance.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 日志编译标志
 */

/**
 * 是否支持变参宏
 */
#if defined (NO_VA_MACRO) || (defined (_MSC_VER) && _MSC_VER < 1400)
#   define  _VA_MACRO_ABLE          (0)
#else
#   define  _VA_MACRO_ABLE          (1)
#endif

/**
 * 日志开启标志
 */
#if defined (NO_LOG)
#   define  _LOG_ABLE               (0)
#else
#   define  _LOG_ABLE               (1)
#endif

/**
 * 是否允许登记级别为DEBUG的日志信息
 */
#if defined (NO_DEBUG) || ! _LOG_ABLE
#   define  _LOG_DEBUG_ABLE         (0)
#else
#   define  _LOG_DEBUG_ABLE         (1)
#endif

/**
 * 是否允许登记级别为TRACE的日志信息
 */
#if defined (NO_TRACE) || ! _LOG_ABLE || ! _LOG_DEBUG_ABLE
#   define  _LOG_TRACE_ABLE         (0)
#else
#   define  _LOG_TRACE_ABLE         (1)
#endif
/* -------------------------           */


/**
 * 默认的日志屏蔽标志
 * 可通过日志屏蔽标志来阻止登记指定类型的日志信息
 */
#define DEFAULT_LOG_MASK            (0x0)
#define DEFAULT_NO_VA_LOG_MASK      DEFAULT_LOG_MASK
/* -------------------------           */


/* ===================================================================
 * 接口函数声明
 * =================================================================== */

#if ! _LOG_DEBUG_ABLE
#   define SLog_IsDebugAble()       (FALSE)
#else
#   define SLog_IsDebugAble()       (SLog_IsLogLevelAble(SLOG_LEVEL_DEBUG))
#endif

#if ! _LOG_TRACE_ABLE
#   define SLog_IsTraceAble()       (FALSE)
#else
#   define SLog_IsTraceAble()       (SLog_IsLogLevelAble(SLOG_LEVEL_TRACE))
#endif
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* __SPK_LOGGER_H */


/* ===================================================================
 * 日志宏定义
 * =================================================================== */

/*
 * 根据日志屏蔽标志判断是否需要重置日志宏
 * 编译时可通过指定 SLOG_MASK 宏定制
 */
#if defined(SLOG_MASK)
#   undef   _SLOG_MASK
#   define  _SLOG_MASK      SLOG_MASK
#elif defined(SLOG_MASK_FLAG)
#   undef   _SLOG_MASK
#   define  _SLOG_MASK      SLOG_MASK_FLAG
#else
#   undef   _SLOG_MASK
#   define  _SLOG_MASK      DEFAULT_LOG_MASK
#endif


#if ! defined(_SLOG_MASK)
#   define  _SLOG_MASK      DEFAULT_LOG_MASK
#endif


#if defined(__SLOG_LOGGER_MACROS_H)
#   undef   __SLOG_LOGGER_MACROS_H

#   undef   SLOG_LOG
#   undef   SLOG_TRACE
#   undef   SLOG_DEBUG
#   undef   SLOG_INFO
#   undef   SLOG_WARN
#   undef   SLOG_ERROR
#   undef   SLOG_BZ_INFO
#   undef   SLOG_BZ_WARN
#   undef   SLOG_BZ_ERROR
#   undef   SLOG_FATAL

#   undef   SLOG_ASSERT
#   undef   SLOG_ASSERT_RV
#   undef   SLOG_ASSERT_NV
#endif


#ifndef __SLOG_LOGGER_MACROS_H
#define __SLOG_LOGGER_MACROS_H


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 日志函数(宏函数)定义
 */
#if _VA_MACRO_ABLE

#   if _LOG_TRACE_ABLE
        /**
         * SLOG_TRACE, 跟踪信息登记宏函数
         * 以级别LOG_TRACE登记日志
         *
         * <pre>
         * SLOG_TRACE("log info");
         * SLOG_TRACE("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_TRACE(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_TRACE, __VA_ARGS__)
#   else
#       define  SLOG_TRACE(...)
#   endif

#   if _LOG_DEBUG_ABLE
        /**
         * SLOG_DEBUG, 调试信息登记宏函数
         * 以级别LOG_DEBUG登记日志
         *
         * <pre>
         * SLOG_DEBUG("log info");
         * SLOG_DEBUG("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_DEBUG(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_DEBUG, __VA_ARGS__)
#   else
#       define  SLOG_DEBUG(...)
#   endif

#   if _LOG_ABLE
        /**
         * SLOG_LOG, 日志登记宏函数, 为简化日志函数的使用而设
         * 可在调用时指定日志屏蔽标志和日志登记级别
         *
         * <pre>
         * SLOG_LOG(level, "log info");
         * SLOG_LOG(level, "log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_LOG(...)       \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, __VA_ARGS__)

        /**
         * SLOG_INFO, 提示信息登记宏函数
         * 以级别LOG_INFO登记日志
         *
         * <pre>
         * SLOG_INFO("log info");
         * SLOG_INFO("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_INFO(...)      \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_INFO, __VA_ARGS__)

        /**
         * SLOG_WARN, 警告信息登记宏函数
         * 以级别LOG_WARN登记日志
         *
         * <pre>
         * SLOG_WARN("log info");
         * SLOG_WARN("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_WARN(...)      \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_WARN, __VA_ARGS__)

        /**
         * SLOG_ERROR, 错误信息登记宏函数
         * 以级别LOG_ERROR登记日志
         *
         * <pre>
         * SLOG_ERROR("log info");
         * SLOG_ERROR("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_ERROR(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_ERROR, __VA_ARGS__)

        /**
         * SLOG_BZ_INFO, 业务提示信息登记宏函数
         * 以级别BZ_INFO登记日志
         *
         * <pre>
         * SLOG_BZ_INFO("log info");
         * SLOG_BZ_INFO("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_BZ_INFO(...)   \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_BZ_INFO, \
                        __VA_ARGS__)

        /**
         * SLOG_BZ_WARN, 业务警告信息登记宏函数
         * 以级别BZ_WARN登记日志
         *
         * <pre>
         * SLOG_BZ_WARN("log info");
         * SLOG_BZ_WARN("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_BZ_WARN(...)   \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_BZ_WARN, \
                        __VA_ARGS__)

        /**
         * SLOG_BZ_ERROR, 业务错误信息登记宏函数
         * 以级别BZ_ERROR登记日志
         *
         * <pre>
         * SLOG_BZ_ERROR("log info");
         * SLOG_BZ_ERROR("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_BZ_ERROR(...)  \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_BZ_ERROR, \
                        __VA_ARGS__)

        /**
         * SLOG_FATAL, 致命错误信息登记宏函数
         * 以级别LOG_FATAL登记日志
         *
         * <pre>
         * SLOG_FATAL("log info");
         * SLOG_FATAL("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_FATAL(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_FATAL, __VA_ARGS__)

#   else    /* _LOG_ABLE */
#       define  SLOG_LOG(...)
#       define  SLOG_INFO(...)
#       define  SLOG_WARN(...)
#       define  SLOG_ERROR(...)
#       define  SLOG_BZ_INFO(...)
#       define  SLOG_BZ_WARN(...)
#       define  SLOG_BZ_ERROR(...)
#       define  SLOG_FATAL(...)
#   endif   /* _LOG_ABLE */

#else       /* _VA_MACRO_ABLE */

#   if _LOG_ABLE
#       ifdef _SLOG_MASK
#           define      SLOG_LOG        _SLog_LogFullSimplenessMasked
#           define      SLOG_INFO       _SLog_InfoSimplenessMasked
#           define      SLOG_WARN       _SLog_WarnSimplenessMasked
#           define      SLOG_ERROR      _SLog_ErrorSimplenessMasked
#           define      SLOG_BZ_INFO    _SLog_BzInfoSimplenessMasked
#           define      SLOG_BZ_WARN    _SLog_BzWarnSimplenessMasked
#           define      SLOG_BZ_ERROR   _SLog_BzErrorSimplenessMasked
#           define      SLOG_FATAL      _SLog_FatalSimplenessMasked
#       else
#           define      SLOG_LOG        _SLog_LogFullSimpleness
#           define      SLOG_INFO       _SLog_InfoSimpleness
#           define      SLOG_WARN       _SLog_WarnSimpleness
#           define      SLOG_ERROR      _SLog_ErrorSimpleness
#           define      SLOG_BZ_INFO    _SLog_BzInfoSimpleness
#           define      SLOG_BZ_WARN    _SLog_BzWarnSimpleness
#           define      SLOG_BZ_ERROR   _SLog_BzErrorSimpleness
#           define      SLOG_FATAL      _SLog_FatalSimpleness
#       endif

#       if _LOG_TRACE_ABLE
#           ifdef _SLOG_MASK
#               define  SLOG_TRACE      _SLog_TraceSimplenessMasked
#           else
#               define  SLOG_TRACE      _SLog_TraceSimpleness
#           endif
#       else
#           define      SLOG_TRACE
#       endif

#       if _LOG_DEBUG_ABLE
#           ifdef _SLOG_MASK
#               define  SLOG_DEBUG      _SLog_DebugSimplenessMasked
#           else
#               define  SLOG_DEBUG      _SLog_DebugSimpleness
#           endif
#       else
#           define      SLOG_DEBUG
#       endif
#   else    /* _LOG_ABLE */
#       define          SLOG_LOG
#       define          SLOG_TRACE
#       define          SLOG_DEBUG
#       define          SLOG_INFO
#       define          SLOG_WARN
#       define          SLOG_ERROR
#       define          SLOG_BZ_INFO
#       define          SLOG_BZ_WARN
#       define          SLOG_BZ_ERROR
#       define          SLOG_FATAL
#   endif   /* _LOG_ABLE */

#   ifndef __FUNCTION__
#       define  __FUNCTION__    ""
#   endif

#endif      /* _VA_MACRO_ABLE */
/* -------------------------           */


/* ===================================================================
 * 为了在编译时检查格式化字符串而设置的日志函数替换宏
 * =================================================================== */

#if defined(_CHECK_LOG_FORMAT)
#   undef   SLOG_TRACE
#   undef   SLOG_DEBUG
#   undef   SLOG_INFO
#   undef   SLOG_WARN
#   undef   SLOG_ERROR
#   undef   SLOG_BZ_INFO
#   undef   SLOG_BZ_WARN
#   undef   SLOG_BZ_ERROR
#   undef   SLOG_FATAL

#   define  SLOG_TRACE      printf
#   define  SLOG_DEBUG      printf
#   define  SLOG_INFO       printf
#   define  SLOG_WARN       printf
#   define  SLOG_ERROR      printf
#   define  SLOG_BZ_INFO    printf
#   define  SLOG_BZ_WARN    printf
#   define  SLOG_BZ_ERROR   printf
#   define  SLOG_FATAL      printf
#endif
/* -------------------------           */


/* ===================================================================
 * ASSERT 定义
 * =================================================================== */

#if ! defined(NDEBUG)

/**
 * assert, 若未定义 NDEBUG, 则记录错误日志并结束进程
 */
#   define  SLOG_ASSERT(EXPR)                       \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                assert((EXPR)); \
            } \
        } while (0)

/**
 * assert, 若未定义 NDEBUG, 则记录错误日志并结束进程
 */
#if _VA_MACRO_ABLE
#   define  SLOG_ASSERT2(EXPR, ...)                 \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                assert((EXPR)); \
            } \
        } while (0)
#else   /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT2                _SLog_AssertSimpleness
#endif

#else

#if _VA_MACRO_ABLE
#   define  SLOG_ASSERT(EXPR)
#   define  SLOG_ASSERT2(EXPR, ...)
#else   /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT(EXPR)
#   define  SLOG_ASSERT2
#endif

#endif
/* -------------------------           */


#if defined(ENABLE_SOFT_ASSERT)

/**
 * 记录错误日志并直接从函数返回指定的值
 */
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)                \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                return (RETURN_VAL); \
            } \
        } while (0)

/**
 * 记录错误日志并直接从函数返回指定的值
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_RV2(EXPR, RETURN_VAL, ...)          \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                return (RETURN_VAL); \
            } \
        } while (0)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_RV2             _SLog_AssertSimplenessRV
# endif

/**
 * 记录错误日志并直接从void函数返回
 */
#   define  SLOG_ASSERT_NV(EXPR)                            \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                return; \
            } \
        } while (0)

/**
 * 记录错误日志并直接从void函数返回
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_NV2(EXPR, ...)                      \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                return; \
            } \
        } while (0)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_NV2             _SLog_AssertSimpleness
# endif

#elif ! defined(NDEBUG)                 /* elif ENABLE_SOFT_ASSERT */

/**
 * assert, 若未定义 NDEBUG, 则记录错误日志并结束进程
 */
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)                \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                assert((EXPR)); \
            } \
        } while (0)

/**
 * assert, 若未定义 NDEBUG, 则记录错误日志并结束进程
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_RV2(EXPR, RETURN_VAL, ...)          \
        do { \
            if (__spk_unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                assert((EXPR)); \
            } \
        } while (0)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_RV2             _SLog_AssertSimplenessRV
# endif

/**
 * assert, 若未定义 NDEBUG, 则记录错误日志并结束进程
 */
#   define  SLOG_ASSERT_NV(EXPR)                            \
            SLOG_ASSERT_RV((EXPR), 0)

/**
 * assert, 若未定义 NDEBUG, 则记录错误日志并结束进程
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_NV2(EXPR, ...)                      \
            SLOG_ASSERT_RV2((EXPR), 0, __VA_ARGS__)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_NV2             _SLog_AssertSimpleness
# endif

#else                                   /* else ENABLE_SOFT_ASSERT */

# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)
#   define  SLOG_ASSERT_RV2(EXPR, RETURN_VAL, ...)

#   define  SLOG_ASSERT_NV(EXPR)
#   define  SLOG_ASSERT_NV2(EXPR, ...)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)
#   define  SLOG_ASSERT_RV2

#   define  SLOG_ASSERT_NV(EXPR)
#   define  SLOG_ASSERT_NV2
# endif

#endif
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* __SLOG_LOGGER_MACROS_H */
