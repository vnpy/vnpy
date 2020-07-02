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
 * @file    cmnlib.h
 *
 * 宏函数定义 (common lib)
 *
 * @version $Id$
 * @since   2011/07/07
 */


#ifndef _SPK_CMNLIB_H
#define _SPK_CMNLIB_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/platform/spk_platforms.h>

#include    <stdio.h>
#include    <stdlib.h>
#include    <stddef.h>
#include    <string.h>
#include    <ctype.h>
#include    <limits.h>
#include    <time.h>


/*
 * 平台特定的头文件
 */
#if ! defined (__APPLE__)
/* 新版本MacOS下混合编译时该头文件会报编译错误 */
#   include <math.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/* 用于浮点数的精度偏差 */
#define SPK_FLOAT_WINDAGE               (0.0000001F)
/* 用于浮点数舍入的精度偏差 */
#define SPK_FLOAT_ROUNDING_WINDAGE      (0.5000001F)

/* 用于浮点数的精度偏差 */
#define SPK_DOUBLE_WINDAGE              (0.0000000001)
/* 用于浮点数舍入的精度偏差 */
#define SPK_DOUBLE_ROUNDING_WINDAGE     (0.5000000001)
/* -------------------------           */


/* ===================================================================
 * 宏函数定义 (数学函数)
 * =================================================================== */

#undef  SPK_MIN
#define SPK_MIN(a,b)                    ((a) <= (b) ? (a) : (b))

#undef  SPK_MIN_NONZERO
#define SPK_MIN_NONZERO(a,b)            (((a) > 0 && (a) <= (b)) ? (a) : (b))

#undef  SPK_MAX
#define SPK_MAX(a,b)                    ((a) >= (b) ? (a) : (b))

#undef  SPK_ABS
#define SPK_ABS(x)                      ((x) >= 0 ? (x) : -(x))

/* 若x大于等于0则返回x, 否则返回0 */
#undef  SPK_FLOOR_ZERO
#define SPK_FLOOR_ZERO(x)               ((x) > 0 ? (x) : 0)

#undef  SPK_CLAMP
#define SPK_CLAMP(x, low, high)         \
        (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#undef  SPK_XOR
#define SPK_XOR(e, f)                   (((e) && !(f)) || (!(e) && (f)))

#undef  SPK_ROUND
#define SPK_ROUND(f)                    ((int32) (f + SPK_FLOAT_ROUNDING_WINDAGE))

#undef  SPK_ROUND64
#define SPK_ROUND64(f)                  ((int64) (f + SPK_DOUBLE_ROUNDING_WINDAGE))

#undef  SPK_FLOOR
#define SPK_FLOOR(f)                    ((int32) (f + SPK_FLOAT_WINDAGE))

#undef  SPK_FLOOR64
#define SPK_FLOOR64(f)                  ((int64) (f + SPK_DOUBLE_WINDAGE))

#undef  SPK_CEIL
#define SPK_CEIL(f)                     \
        ((f) - (int32)(f) > SPK_FLOAT_WINDAGE ? (int32)(f) + 1 : (int32)(f))

#undef  SPK_CEIL64
#define SPK_CEIL64(f)                   \
        ((f) - (int64)(f) > SPK_DOUBLE_WINDAGE ? (int64)(f) + 1 : (int64)(f))
/* -------------------------           */


/*
 * 对浮点数进行乘法操作，并返回转换为整型数值后的结果
 */
#undef  SPK_FLOAT_TO_INT32
#undef  SPK_FLOAT_TO_INT64
#undef  SPK_DOUBLE_TO_INT32
#undef  SPK_DOUBLE_TO_INT64
#undef  SPK_TO_DOUBLE

#define SPK_FLOAT_TO_INT32              SPK_SIGNED_FLOAT_TO_INT32
#define SPK_FLOAT_TO_INT64              SPK_SIGNED_FLOAT_TO_INT64
#define SPK_DOUBLE_TO_INT32             SPK_SIGNED_DOUBLE_TO_INT32
#define SPK_DOUBLE_TO_INT64             SPK_SIGNED_DOUBLE_TO_INT64
#define SPK_TO_DOUBLE                   SPK_SIGNED_TO_DOUBLE


/* 对浮点数进行转换操作 (不考虑为负的情况) */
#undef  SPK_UNSIGNED_FLOAT_TO_INT32
#undef  SPK_UNSIGNED_FLOAT_TO_INT64
#undef  SPK_UNSIGNED_DOUBLE_TO_INT32
#undef  SPK_UNSIGNED_DOUBLE_TO_INT64
#undef  SPK_UNSIGNED_TO_DOUBLE

#define SPK_UNSIGNED_FLOAT_TO_INT32(f, multiplier)      \
        ( (int32) ((f) * (multiplier) + SPK_FLOAT_ROUNDING_WINDAGE) )

#define SPK_UNSIGNED_FLOAT_TO_INT64(f, multiplier)      \
        ( (int64) ((f) * (multiplier) + SPK_FLOAT_ROUNDING_WINDAGE) )

#define SPK_UNSIGNED_DOUBLE_TO_INT32(d, multiplier)     \
        ( (int32) ((d) * (multiplier) + SPK_DOUBLE_ROUNDING_WINDAGE) )

#define SPK_UNSIGNED_DOUBLE_TO_INT64(d, multiplier)     \
        ( (int64) ((d) * (multiplier) + SPK_DOUBLE_ROUNDING_WINDAGE) )

#define SPK_UNSIGNED_TO_DOUBLE(i, multiplier)           \
        ( ((double) (i) / (multiplier)) + SPK_DOUBLE_WINDAGE )


/* 对浮点数进行转换操作 (支持负数) */
#undef  SPK_SIGNED_FLOAT_TO_INT32
#undef  SPK_SIGNED_FLOAT_TO_INT64
#undef  SPK_SIGNED_DOUBLE_TO_INT32
#undef  SPK_SIGNED_DOUBLE_TO_INT64
#undef  SPK_SIGNED_TO_DOUBLE

#define SPK_SIGNED_FLOAT_TO_INT32(f, multiplier)        \
        ( (int32) ((f) * (multiplier) \
                + ((f) >= 0.0F ? SPK_FLOAT_ROUNDING_WINDAGE : \
                        -SPK_FLOAT_ROUNDING_WINDAGE)) )

#define SPK_SIGNED_FLOAT_TO_INT64(f, multiplier)        \
        ( (int64) ((f) * (multiplier) \
                + ((f) >= 0.0F ? SPK_FLOAT_ROUNDING_WINDAGE : \
                        -SPK_FLOAT_ROUNDING_WINDAGE)) )

#define SPK_SIGNED_DOUBLE_TO_INT32(d, multiplier)       \
        ( (int32) ((d) * (multiplier) \
                + ((d) >= 0.0 ? SPK_DOUBLE_ROUNDING_WINDAGE : \
                        -SPK_DOUBLE_ROUNDING_WINDAGE)) )

#define SPK_SIGNED_DOUBLE_TO_INT64(d, multiplier)       \
        ( (int64) ((d) * (multiplier) \
                + ((d) >= 0.0 ? SPK_DOUBLE_ROUNDING_WINDAGE : \
                        -SPK_DOUBLE_ROUNDING_WINDAGE)) )

#define SPK_SIGNED_TO_DOUBLE(i, multiplier)             \
        ( ((double) (i) / (multiplier)) \
                + ((i) >= 0 ? SPK_DOUBLE_WINDAGE :\
                        -SPK_DOUBLE_WINDAGE) )
/* -------------------------           */


/* 计算数组长度 */
#undef  SPK_DIM
#define SPK_DIM(x)                      (sizeof((x)) / sizeof((x)[0]))

/* 若x小于等于0则返回v, 否则返回x */
#undef  SPK_IF_ZERO
#define SPK_IF_ZERO(x,v)                ((x) > 0 ? (x) : (v))

/* 若x为负数则返回v, 否则返回x */
#undef  SPK_IF_NEG
#define SPK_IF_NEG(x,v)                 ((x) < 0 ? (v) : (x))

/* 若x为非负数则返回v, 否则返回x */
#undef  SPK_IF_NONNEG
#define SPK_IF_NONNEG(x,v)              ((x) < 0 ? (x) : (v))
/* -------------------------           */


/* ===================================================================
 * 宏函数定义 (字符处理)
 * =================================================================== */

#undef  SPK_ISASCII
#ifdef  isascii
#   define  SPK_ISASCII(c)              isascii(c)
#else
#   define  SPK_ISASCII(c)              (((c) & ~0x7f) == 0)
#endif

#undef  SPK_ISUPPER
#ifdef  isupper
#   define  SPK_ISUPPER(c)              isupper(c)
#else
#   define  SPK_ISUPPER(c)              ('A' <= (c) && (c) <= 'Z')
#endif

#undef  SPK_ISLOWER
#ifdef  islower
#   define  SPK_ISLOWER(c)              islower(c)
#else
#   define  SPK_ISLOWER(c)              ('a' <= (c) && (c) <= 'z')
#endif

#undef  SPK_ISDIGIT
#ifdef  isdigit
#   define  SPK_ISDIGIT(c)              isdigit(c)
#else
#   define  SPK_ISDIGIT(c)              ('0' <= (c) && (c) <= '9')
#endif

#undef  SPK_ISALPHA
#ifdef  isalpha
#   define  SPK_ISALPHA(c)              isalpha(c)
#else
#   define  SPK_ISALPHA(c)              (SPK_ISUPPER(c) || SPK_ISLOWER(c))
#endif

#undef  SPK_ISALNUM
#ifdef  isalnum
#   define  SPK_ISALNUM(c)              isalnum(c)
#else
#   define  SPK_ISALNUM(c)              (SPK_ISDIGIT(c) || SPK_ISALPHA(c))
#endif

#undef  SPK_ISXDIGIT
#ifdef  isxdigit
#   define  SPK_ISXDIGIT(c)             isxdigit(c)
#else
#   define  SPK_ISXDIGIT(c)             \
            (SPK_ISDIGIT(c) || ('A' <= (c) && (c) <= 'F') || \
                    ('a' <= (c) && (c) <= 'f'))
#endif

#undef  SPK_ISBLANK
#ifdef  isblank
#   define  SPK_ISBLANK(c)              isblank(c)
#else
#   define  SPK_ISBLANK(c)              ((c) == ' ' || (c) == '\t')
#endif

#undef  SPK_ISSPACE
#ifdef  isspace
#   define  SPK_ISSPACE(c)              isspace((int) c)
#else
#   define  SPK_ISSPACE(c)              \
            ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#endif

#undef  SPK_TOUPPER
# ifdef toupper
#   define  SPK_TOUPPER(c)              toupper(c)
#else
#   define  SPK_TOUPPER(c)              \
            (SPK_ISLOWER(c) ? 'A' + ((c) - 'a') : (c))
#endif

#undef  SPK_TOLOWER
# ifdef tolower
#   define  SPK_TOLOWER(c)              tolower(c)
#else
#   define  SPK_TOLOWER(c)              \
            (SPK_ISUPPER(c) ? 'a' + ((c) - 'A') : (c))
#endif
/* -------------------------           */


/* ===================================================================
 * 宏函数定义 (字节序转换)
 * =================================================================== */

#undef  SPK_SWAP_INT16
#undef  SPK_SWAP_INT32
#undef  SPK_SWAP_INT64
#undef  SPK_SWAP_INT16_DIRECT
#undef  SPK_SWAP_INT32_DIRECT
#undef  SPK_SWAP_INT64_DIRECT

/* Swap 2 byte, 16 bit values (for Big and Little Endian Byte Order) */
#define SPK_SWAP_INT16(val)                     \
        ( ((((uint16) val) >> 8) & 0x00FF) \
                | ((((uint16) val) << 8) & 0xFF00) )

/* Swap 4 byte, 32 bit values */
#define SPK_SWAP_INT32(val)                     \
        ( ((((uint32) val) >> 24) & 0x000000FF) \
                | ((((uint32) val) >>  8) & 0x0000FF00) \
                | ((((uint32) val) <<  8) & 0x00FF0000) \
                | ((((uint32) val) << 24) & 0xFF000000) )

/* Swap 8 byte, 64 bit values */
#define SPK_SWAP_INT64(val)                     \
        ( ((((uint64) val) >> 56) & 0x00000000000000FF) \
                | ((((uint64) val) >> 40) & 0x000000000000FF00) \
                | ((((uint64) val) >> 24) & 0x0000000000FF0000) \
                | ((((uint64) val) >>  8) & 0x00000000FF000000) \
                | ((((uint64) val) <<  8) & 0x000000FF00000000) \
                | ((((uint64) val) << 24) & 0x0000FF0000000000) \
                | ((((uint64) val) << 40) & 0x00FF000000000000) \
                | ((((uint64) val) << 56) & 0xFF00000000000000) )

/* Swap 2 byte, 16 bit values direct */
#define SPK_SWAP_INT16_DIRECT(x)                \
        ( *(uint16 *) &(x) = SPK_SWAP_INT16(*(uint16 *) &(x)) )

/* Swap 4 byte, 32 bit values direct */
#define SPK_SWAP_INT32_DIRECT(x)                \
        ( *(uint32 *) &(x) = SPK_SWAP_INT32(*(uint32 *) &(x)) )

/* Swap 8 byte, 64 bit values direct */
#define SPK_SWAP_INT64_DIRECT(x)                \
        ( *(uint64 *) &(x) = SPK_SWAP_INT64(*(uint64 *) &(x)) )
/* -------------------------           */


/* ===================================================================
 * 宏函数定义 (位操作函数)
 * =================================================================== */

/*
 * 测试相应位是否已设置
 */
#undef  SPK_BITS_ISSET
#define SPK_BITS_ISSET(x, f)            ( ((x) & (f)) == (f) )

#undef  SPK_BITS_ISSET_ANY
#define SPK_BITS_ISSET_ANY(x, f)        ( ((x) & (f)) != 0 )

/*
 * 设置相应位
 */
#undef  SPK_BITS_SET
#define SPK_BITS_SET(x, f)              ( (x) | (f) )

#undef  SPK_BITS_SET_DIRECT
#define SPK_BITS_SET_DIRECT(x, f)       ( (x) |= (f) )

/*
 * 清除相应位
 */
#undef  SPK_BITS_CLR
#define SPK_BITS_CLR(x, f)              ( (x) & ~(f) )

#undef  SPK_BITS_CLR_U32
#define SPK_BITS_CLR_U32(x, f)          ( (x) & ~((uint32) f) )

#undef  SPK_BITS_CLR_U64
#define SPK_BITS_CLR_U64(x, f)          ( (x) & ~((uint64) f) )

#undef  SPK_BITS_CLR_DIRECT
#define SPK_BITS_CLR_DIRECT(x, f)       ( (x) &= ~(f) )

#undef  SPK_BITS_CLR_DIRECT_U32
#define SPK_BITS_CLR_DIRECT_U32(x, f)   ( (x) &= ~((uint32) f) )

#undef  SPK_BITS_CLR_DIRECT_U64
#define SPK_BITS_CLR_DIRECT_U64(x, f)   ( (x) &= ~((uint64) f) )
/* -------------------------           */


/*
 * 测试相应位是否已设置
 */
#undef  SPK_BITS_ISSET_N
#define SPK_BITS_ISSET_N(x, n)          ( ((x) & (1 << (n))) > 0 )

/*
 * 设置相应位
 */
#undef  SPK_BITS_SET_N
#define SPK_BITS_SET_N(x, n)            ( (x) | (1 << (n)) )

#undef  SPK_BITS_SET_N_DIRECT
#define SPK_BITS_SET_N_DIRECT(x, n)     ( (x) |= (1 << (n)) )

/*
 * 清除相应位
 */
#undef  SPK_BITS_CLR_N
#define SPK_BITS_CLR_N(x, n)            ( (x) & ~(1 << (n)) )

#undef  SPK_BITS_CLR_N_DIRECT
#define SPK_BITS_CLR_N_DIRECT(x, n)     ( (x) &= ~(1 << (n)) )
/* -------------------------           */


/* ===================================================================
 * 宏函数定义 (指针判断)
 * =================================================================== */

/*
 * 若x为空则返回v
 */
#undef  SPK_IF_NULL
#define SPK_IF_NULL(x,v)                ((void*) (x) == (void*) 0 ? (v) : (x))

/*
 * 若x为空则返回v, 不为空返回z
 */
#undef  SPK_SWITCH_NULL
#define SPK_SWITCH_NULL(x,v,y)          ((void*) (x) == (void*) 0 ? (v) : (y))

/*
 * 若字符串s为空则返回"NULL", 否则返回s
 */
#undef  SPK_SWITCH_NULL_STR
#define SPK_SWITCH_NULL_STR(s)          \
        ((void*) (s) == (void*) 0 ? "NULL" : (s))

/*
 * 若x为空则返回字符串"IS-NULL", 否则返回字符串"NOT-NULL"
 */
#undef  SPK_ANNOUNCE_IS_NULL
#define SPK_ANNOUNCE_IS_NULL(x)         \
        ((void*) (x) == (void*) 0 ? "IS-NULL" : "NOT-NULL")
/* -------------------------           */


/* ===================================================================
 * 忙等待方法定义
 * =================================================================== */

/*
 * 根据构建类型设置忙等待策略
 */
#if defined (__DEBUG)
#   if ! defined (BUSY_YIELD_TO_SLEEP) && ! defined (NO_BUSY_YIELD_TO_SLEEP)
#       define  BUSY_YIELD_TO_SLEEP         (1)
#   endif
#endif


#if defined (NO_BUSY_YIELD_TO_WAITING)
#   undef   BUSY_YIELD_TO_WAITING
#endif

#if defined (NO_BUSY_YIELD_TO_SLEEP)
#   undef   BUSY_YIELD_TO_SLEEP
#endif
/* -------------------------           */


/*
 * 忙等待级别定义
 */
typedef enum _eSpkBusyPollLevel {
    SPK_BUSY_POLL_LEVEL_BUSY_WAITING    = 0,    /* 忙等待级别-忙等待 */
    SPK_BUSY_POLL_LEVEL_SCHED_YIELD     = 1,    /* 忙等待级别-让出CPU */
    SPK_BUSY_POLL_LEVEL_SLEEP_YIELD     = 2,    /* 忙等待级别-以睡眠的方式让出CPU(睡眠1纳秒或1微秒) */
    SPK_BUSY_POLL_LEVEL_SLEEP           = 3,    /* 忙等待级别-睡眠(睡眠1毫秒) */
    __MAX_SPK_BUSY_POLL_LEVEL           = 1000
} eSpkBusyPollLevelT;
/* -------------------------           */


/*
 * 根据忙等待级别进行忙等待时的睡眠处理
 *
 * @param   BUSY_POLL_LEVEL 忙等待级别定义 @see eSpkBusyPollLevelT
 */
#undef  SPK_BUSY_POLL_YIELD
#define SPK_BUSY_POLL_YIELD(BUSY_POLL_LEVEL)    \
    do { \
        if (__spk_likely((BUSY_POLL_LEVEL) == SPK_BUSY_POLL_LEVEL_BUSY_WAITING)) { \
            SPK_BUSY_YIELD2(); \
        } else if ((BUSY_POLL_LEVEL) == SPK_BUSY_POLL_LEVEL_SCHED_YIELD) { \
            SPK_SCHED_YIELD(); \
        } else if ((BUSY_POLL_LEVEL) == SPK_BUSY_POLL_LEVEL_SLEEP_YIELD) { \
            SPK_SLEEP_YIELD(); \
        } else if ((BUSY_POLL_LEVEL) <= SPK_BUSY_POLL_LEVEL_SLEEP) { \
            SPK_SLEEP_MS(1); \
        } else { \
            SPK_SLEEP_MS((BUSY_POLL_LEVEL)); \
        } \
    } while (0)
/* -------------------------           */


/*
 * 用于忙等待时的睡眠处理
 */
#undef  SPK_BUSY_YIELD
#if defined (BUSY_YIELD_TO_WAITING)
#   define  SPK_BUSY_YIELD(LOOP_VAR)            __SPK_CPU_RELAX()

#elif defined (BUSY_YIELD_TO_SLEEP)
#   define  SPK_BUSY_YIELD(LOOP_VAR)            \
    do { \
        switch (((LOOP_VAR)++ & 0x0F)) { \
        case 0x03: \
            SPK_SCHED_YIELD(); \
            break; \
        case 0x0F: \
            SPK_SLEEP_YIELD(); \
            break; \
        } \
        __SPK_CPU_RELAX(); \
    } while (0)

#else
#   define  SPK_BUSY_YIELD(LOOP_VAR)            \
    do { \
        if (((LOOP_VAR)++ & 0x07) == 0x07) { \
            SPK_SCHED_YIELD(); \
        } else { \
            __SPK_CPU_RELAX(); \
        } \
    } while (0)

#endif


#undef  SPK_BUSY_YIELD2
#if defined (BUSY_YIELD_TO_WAITING)
#   define  SPK_BUSY_YIELD2()                   __SPK_CPU_RELAX()

#elif defined (BUSY_YIELD_TO_SLEEP)
#   define  SPK_BUSY_YIELD2()                   SPK_SLEEP_YIELD()

#else
#   define  SPK_BUSY_YIELD2()                   SPK_SCHED_YIELD()

#endif
/* -------------------------           */


/*
 * 用于忙等待时的睡眠处理
 */
#undef  SPK_BUSY_SLEEP
#define SPK_BUSY_SLEEP(LOOP_VAR)                \
    do { \
        switch (((LOOP_VAR)++ & 0x0F)) { \
        case 0x03: \
            SPK_SCHED_YIELD(); \
            break; \
        case 0x0F: \
            SPK_SLEEP_YIELD(); \
            break; \
        } \
        __SPK_CPU_RELAX(); \
    } while (0)


#undef  SPK_BUSY_SLEEP2
#define SPK_BUSY_SLEEP2()                       SPK_SLEEP_YIELD()
/* -------------------------           */


/*
 * 忙等待, 直至条件不再成立
 */
#undef  SPK_BUSY_WAITING
#define SPK_BUSY_WAITING(COND)                  \
    do { \
        while (__spk_unlikely((COND))) { \
            __SPK_CPU_RELAX(); \
        } \
    } while (0)
/* -------------------------           */


/*
 * 忙等待, 直至条件不再成立
 */
#undef  SPK_BUSY_YIELD_WAITING
#if defined (BUSY_YIELD_TO_WAITING)
#   define  SPK_BUSY_YIELD_WAITING(COND)        SPK_BUSY_WAITING(COND)

#elif defined (BUSY_YIELD_TO_SLEEP)
#   define  SPK_BUSY_YIELD_WAITING(COND)        SPK_BUSY_SLEEP_WAITING(COND)

#else
#   define  SPK_BUSY_YIELD_WAITING(COND)        \
    do { \
        uint32  __BUSY_YIELD_loop = 0; \
        while (__spk_unlikely((COND))) { \
            SPK_BUSY_YIELD(__BUSY_YIELD_loop); \
        } \
    } while (0)

#endif
/* -------------------------           */


/*
 * 忙等待, 直至条件不再成立
 */
#undef  SPK_BUSY_SLEEP_WAITING
#define SPK_BUSY_SLEEP_WAITING(COND)            \
    do { \
        uint32  __BUSY_SLEEP_loop = 0; \
        while (__spk_unlikely((COND))) { \
            SPK_BUSY_SLEEP(__BUSY_SLEEP_loop); \
        } \
    } while (0)
/* -------------------------           */


/* ===================================================================
 * 忙等待操作块定义
 * =================================================================== */

/*
 * 忙等待操作块
 * 忙等待, 直至条件不再成立
 *
 * <p>同步块由3个宏组成:<ul>
 * <li> ● _YIELD_WAITING_BEGIN </li>
 * <li> ● _YIELD_WAITING_ELSE </li>
 * <li> ● _YIELD_WAITING_END </li>
 * </ul></p>
 *
 * <p>忙等待操作块示例: <pre>
 *      _YIELD_WAITING_BEGIN(! isXxxCompleted) {
 *          // do something
 *          ...;
 *      }
 *      _YIELD_WAITING_ELSE() {
 *          // do something
 *          ...;
 *      }
 *      _YIELD_WAITING_END();
 * </pre></p>
 *
 * @param   COND    忙等待的等待条件
 */
#if !defined (_YIELD_WAITING_BEGIN)
#if defined (BUSY_YIELD_TO_WAITING)
#   define  _YIELD_WAITING_BEGIN(COND)          \
    do { \
        while ((COND)) {


#   define  _YIELD_WAITING_YIELD()              \
        SPK_BUSY_YIELD2()


#   define  _YIELD_WAITING_WITH_TICK(COND)      \
    do { \
        uint32  __YIELD_WAITING_BEGIN_loop = 0; \
        while ((COND)) {


#   define  _YIELD_WAITING_TICK(N)              \
        (((__YIELD_WAITING_BEGIN_loop++) & (N)) == (N))


#   define  _YIELD_WAITING_ELSE()               \
            _YIELD_WAITING_YIELD(); \
        } \
        {


#   define  _YIELD_WAITING_END()                \
            _YIELD_WAITING_YIELD(); \
        } \
    } while (0)


#elif defined (BUSY_YIELD_TO_SLEEP)
#   define  _YIELD_WAITING_BEGIN(COND)          _SLEEP_WAITING_BEGIN(COND)
#   define  _YIELD_WAITING_YIELD()              _SLEEP_WAITING_YIELD()
#   define  _YIELD_WAITING_WITH_TICK(COND)      _SLEEP_WAITING_WITH_TICK(COND)
#   define  _YIELD_WAITING_TICK(N)              _SLEEP_WAITING_TICK(N)
#   define  _YIELD_WAITING_ELSE()               _SLEEP_WAITING_ELSE()
#   define  _YIELD_WAITING_END()                _SLEEP_WAITING_END()


#else
#   define  _YIELD_WAITING_BEGIN(COND)          \
    do { \
        uint32  __YIELD_WAITING_BEGIN_loop = 0; \
        while ((COND)) {


#   define  _YIELD_WAITING_YIELD()              \
        SPK_BUSY_YIELD(__YIELD_WAITING_BEGIN_loop)


#   define  _YIELD_WAITING_WITH_TICK(COND)      _YIELD_WAITING_BEGIN(COND)
#   define  _YIELD_WAITING_TICK(N)              \
        ((__YIELD_WAITING_BEGIN_loop & (N)) == (N))


#   define  _YIELD_WAITING_ELSE()               \
            _YIELD_WAITING_YIELD(); \
        } \
        {


#   define  _YIELD_WAITING_END()                \
            _YIELD_WAITING_YIELD(); \
        } \
    } while (0)


#endif
#endif  /* !defined (_YIELD_WAITING_BEGIN) */
/* -------------------------           */


/*
 * 忙等待操作块
 * 忙等待, 直至条件不再成立
 *
 * <p>同步块由3个宏组成:<ul>
 * <li> ● _SLEEP_WAITING_BEGIN </li>
 * <li> ● _SLEEP_WAITING_ELSE </li>
 * <li> ● _SLEEP_WAITING_END </li>
 * </ul></p>
 *
 * <p>忙等待操作块示例: <pre>
 *      _SLEEP_WAITING_BEGIN(! isXxxCompleted) {
 *          // do something
 *          ...;
 *      }
 *      _SLEEP_WAITING_ELSE() {
 *          // do something
 *          ...;
 *      }
 *      _SLEEP_WAITING_END();
 * </pre></p>
 *
 * @param   COND    忙等待的等待条件
 */
#if !defined (_SLEEP_WAITING_BEGIN)
#   define  _SLEEP_WAITING_BEGIN(COND)          \
    do { \
        uint32  __SLEEP_WAITING_BEGIN_loop = 0; \
        while ((COND)) {


#   define  _SLEEP_WAITING_YIELD()              \
        SPK_BUSY_SLEEP(__SLEEP_WAITING_BEGIN_loop)


#   define  _SLEEP_WAITING_WITH_TICK(COND)      _SLEEP_WAITING_BEGIN(COND)
#   define  _SLEEP_WAITING_TICK(N)              \
        ((__SLEEP_WAITING_BEGIN_loop & (N)) == (N))


#   define  _SLEEP_WAITING_ELSE()               \
            _SLEEP_WAITING_YIELD(); \
        } \
        {


#   define  _SLEEP_WAITING_END()                \
            _SLEEP_WAITING_YIELD(); \
        } \
    } while (0)

#endif
/* -------------------------           */


/* ===================================================================
 * 检查是否需要使用 tcmalloc 或 jemalloc
 * =================================================================== */

#if defined (USE_TCMALLOC)
#   define  SPK_MALLOC_LIB_VER                  \
            ("tcmalloc-" __XSTRING(TC_VERSION_MAJOR) "." \
                    __XSTRING(TC_VERSION_MINOR))

#   include <gperftools/tcmalloc.h>

#   if ! ((TC_VERSION_MAJOR == 2 && TC_VERSION_MINOR >= 4) \
            || (TC_VERSION_MAJOR > 2))
#       error "Newer version of tcmalloc required"
#   endif

#elif defined (USE_JEMALLOC)
#   define  SPK_MALLOC_LIB_VER                  \
            ("jemalloc-" __XSTRING(JEMALLOC_VERSION_MAJOR) "." \
                    __XSTRING(JEMALLOC_VERSION_MINOR) "." \
                    __XSTRING(JEMALLOC_VERSION_BUGFIX))

#   include <jemalloc/jemalloc.h>

#   if ! ((JEMALLOC_VERSION_MAJOR == 3 && JEMALLOC_VERSION_MINOR >= 0) \
            || (JEMALLOC_VERSION_MAJOR > 3))
#       error "Newer version of jemalloc required"
#   endif
#endif
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_CMNLIB_H */
