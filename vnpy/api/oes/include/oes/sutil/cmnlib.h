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
#define SPK_FLOAT_WINDAGE               (0.0000001)
/* 用于浮点数舍入的精度偏差 */
#define SPK_FLOAT_ROUNDING_WINDAGE      (0.5000001)

/* 用于浮点数的精度偏差 */
#define SPK_DOUBLE_WINDAGE              (0.00000000000001)
/* 用于浮点数舍入的精度偏差 */
#define SPK_DOUBLE_ROUNDING_WINDAGE     (0.50000000000001)
/* -------------------------           */


/* ===================================================================
 * 宏函数定义 (数学函数)
 * =================================================================== */

#undef  SPK_MIN
#define SPK_MIN(a,b)                    ( (a) <= (b) ? (a) : (b) )

/* @note 仅适用于b明确大于0的场景 */
#undef  SPK_MIN_NONNEG
#define SPK_MIN_NONNEG(a,b)             ( ((a) >= 0 && (a) <= (b)) ? (a) : (b) )

/* @note 仅适用于b明确大于0的场景 */
#undef  SPK_MIN_NONZERO
#define SPK_MIN_NONZERO(a,b)            ( ((a) > 0 && (a) <= (b)) ? (a) : (b) )

/* @note 仅适用于b明确大于0的场景 */
#undef  SPK_MIN_NONNEG_FLOAT
#define SPK_MIN_NONNEG_FLOAT(a,b)       \
        ( ((a) >= -SPK_DOUBLE_ROUNDING_WINDAGE && (a) <= (b)) ? (a) : (b) )

/* @note 仅适用于b明确大于0的场景 */
#undef  SPK_MIN_NONZERO_FLOAT
#define SPK_MIN_NONZERO_FLOAT(a,b)      \
        ( ((a) > SPK_DOUBLE_ROUNDING_WINDAGE && (a) <= (b)) ? (a) : (b) )

#undef  SPK_MAX
#define SPK_MAX(a,b)                    ( (a) >= (b) ? (a) : (b) )

#undef  SPK_ABS
#define SPK_ABS(x)                      ( (x) >= 0 ? (x) : -(x) )

/* 若x大于等于0则返回x, 否则返回0 */
#undef  SPK_FLOOR_ZERO
#define SPK_FLOOR_ZERO(x)               ( (x) > 0 ? (x) : 0 )

#undef  SPK_CLAMP
#define SPK_CLAMP(x, low, high)         \
        ( ((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)) )

#undef  SPK_XOR
#define SPK_XOR(e, f)                   ( ((e) && !(f)) || (!(e) && (f)) )

#undef  SPK_ROUND
#define SPK_ROUND(f)                    ( (int32) (f + SPK_FLOAT_ROUNDING_WINDAGE) )

#undef  SPK_ROUND64
#define SPK_ROUND64(f)                  ( (int64) (f + SPK_DOUBLE_ROUNDING_WINDAGE) )

#undef  SPK_FLOOR
#define SPK_FLOOR(f)                    ( (int32) (f + SPK_FLOAT_WINDAGE) )

#undef  SPK_FLOOR64
#define SPK_FLOOR64(f)                  ( (int64) (f + SPK_DOUBLE_WINDAGE) )

#undef  SPK_CEIL
#define SPK_CEIL(f)                     \
        ( (f) - (int32)(f) > SPK_FLOAT_WINDAGE ? (int32)(f) + 1 : (int32)(f) )

#undef  SPK_CEIL64
#define SPK_CEIL64(f)                   \
        ( (f) - (int64)(f) > SPK_DOUBLE_WINDAGE ? (int64)(f) + 1 : (int64)(f) )
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
#define SPK_DOUBLE_TO_INT64_PRECISELY   SPK_SIGNED_DOUBLE_TO_INT64_PRECISELY
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

/* @note 仅适用于取值确定不会超过浮点数精度范围的场景 */
#define SPK_UNSIGNED_DOUBLE_TO_INT64(d, multiplier)     \
        ( (int64) ((d) * (multiplier) + SPK_DOUBLE_ROUNDING_WINDAGE) )

#define SPK_UNSIGNED_DOUBLE_TO_INT64_PRECISELY(         \
                d, realPrecision, finalPrecision)       \
        ( ((int64) ((d) * (realPrecision) + SPK_DOUBLE_ROUNDING_WINDAGE)) \
                * (finalPrecision / realPrecision) )

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

/* @note 仅适用于取值确定不会超过浮点数精度范围的场景 */
#define SPK_SIGNED_DOUBLE_TO_INT64(d, multiplier)       \
        ( (int64) ((d) * (multiplier) \
                + ((d) >= 0.0 ? SPK_DOUBLE_ROUNDING_WINDAGE : \
                        -SPK_DOUBLE_ROUNDING_WINDAGE)) )

#define SPK_SIGNED_DOUBLE_TO_INT64_PRECISELY(           \
                d, realPrecision, finalPrecision)       \
        ( ((int64) ((d) * (realPrecision) \
                + ((d) >= 0.0 ? SPK_DOUBLE_ROUNDING_WINDAGE : \
                        -SPK_DOUBLE_ROUNDING_WINDAGE))) \
                * (finalPrecision / realPrecision) )

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

#undef  SPK_IF_ZERO_FLOAT
#define SPK_IF_ZERO_FLOAT(x,v)          ((x) > SPK_DOUBLE_WINDAGE ? (x) : (v))

/* 若x为负数则返回v, 否则返回x */
#undef  SPK_IF_NEG
#define SPK_IF_NEG(x,v)                 ((x) < 0 ? (v) : (x))

#undef  SPK_IF_NEG_FLOAT
#define SPK_IF_NEG_FLOAT(x,v)           ((x) < -SPK_DOUBLE_WINDAGE ? (v) : (x))

/* 若x为非负数则返回v, 否则返回x */
#undef  SPK_IF_NONNEG
#define SPK_IF_NONNEG(x,v)              ((x) < 0 ? (x) : (v))

#undef  SPK_IF_NONNEG_FLOAT
#define SPK_IF_NONNEG_FLOAT(x,v)        ((x) < -SPK_DOUBLE_WINDAGE ? (x) : (v))
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

#undef  SPK_ISPRINT
#ifdef  isprint
#   define  SPK_ISPRINT(c)              isprint((int) c)
#else
#   define  SPK_ISPRINT(c)              ((c) >= ' ' && (c) <= '~')
#endif

/* 与SPK_ISPRINT相比, 仅少空格字符(' ') */
#undef  SPK_ISVISIBLE
#define SPK_ISVISIBLE(c)                ((c) >= '!' && (c) <= '~')

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
#define SPK_BITS_ISSET_N(x, n)          ( ((x) & (1ULL << (n))) > 0 )

/*
 * 设置相应位
 */
#undef  SPK_BITS_SET_N
#define SPK_BITS_SET_N(x, n)            ( (x) | (1ULL << (n)) )

#undef  SPK_BITS_SET_N_DIRECT
#define SPK_BITS_SET_N_DIRECT(x, n)     ( (x) |= (1ULL << (n)) )

/*
 * 清除相应位
 */
#undef  SPK_BITS_CLR_N
#define SPK_BITS_CLR_N(x, n)            ( (x) & ~(1ULL << (n)) )

#undef  SPK_BITS_CLR_N_DIRECT
#define SPK_BITS_CLR_N_DIRECT(x, n)     ( (x) &= ~(1ULL << (n)) )
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


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_CMNLIB_H */
