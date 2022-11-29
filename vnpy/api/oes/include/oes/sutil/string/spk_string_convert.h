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
 * @file    spk_string_convert.h
 *
 * 字符串类型转换函数
 *
 * @version $Id$
 * @since   2012/01/05
 */


#ifndef _SPK_STRING_CONVERT_H
#define _SPK_STRING_CONVERT_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/platform/spk_platforms.h>
#include    <sutil/string/spk_string_var.h>
#include    <sutil/string/spk_multi_field_string.h>
#include    <sutil/platform/spk_platforms.h>
#include    <sutil/logger/spk_console_masked_log.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 跨平台兼容处理
 * =================================================================== */

#if defined (__WINDOWS__) || defined (__MINGW__)
#   if (defined (_MSC_VER) && _MSC_VER < 1400) \
            || (! defined (_WIN32_WINNT) || _WIN32_WINNT < 0x0600)
#       define  __spk_strtoll           __SPK_WIN32_strtoll
#   else
#       define  __spk_strtoll           _strtoi64
#   endif


/* strtoll */
int64       __SPK_WIN32_strtoll(const char *pStr, char **ppEndPtr, int base);


#else
#   define  __spk_strtoll               strtoll


#endif
/* -------------------------           */


/* ===================================================================
 * 类型转换函数声明 (字符串 --> 数值型)
 * ("数值型 --> 字符串" 类的类型转换函数定义在后面的 Inline 函数区)
 * =================================================================== */

/*
 * 转换字符串至int32
 */
int32   SStr_Strtoi(const char *pStr, int32 *pValue);

/*
 * 转换字符串至long
 */
int32   SStr_Strtol(const char *pStr, long *pValue);

/*
 * 转换字符串至int64
 */
int32   SStr_Strtoll(const char *pStr, int64 *pValue);

/*
 * 转换字符串至float
 */
int32   SStr_Strtof(const char *pStr, float *pValue);

/*
 * 转换字符串至double
 */
int32   SStr_Strtod(const char *pStr, double *pValue);

/*
 * 转换字符串至long double
 */
int32   SStr_Strtold(const char *pStr, float128 *pValue);

/*
 * 整型数值转为字符串
 */
char*   SStr_ItoStr(char *pBuf, int32 num);

/*
 * 长整型数值转为字符串
 */
char*   SStr_LtoStr(char *pBuf, long num);

/*
 * int64型数值转为字符串
 */
char*   SStr_LltoStr(char *pBuf, int64 num);

/*
 * float128型数值转为字符串
 */
char*   SStr_LdtoStr(char *pBuf, float128 num, int32 scale);

/*
 * float128型数值转为字符串
 */
char*   SStr_FixedLdtoStr(char *pBuf, float128 num, int32 precision,
                int32 scale);

/*
 * 整型数值转为十六进制形式的字符串
 */
char*   SStr_XtoStr(char *pBuf, int32 num);

/*
 * 校验字符串是否是有效的十进制整型数值字符串
 */
BOOL    SStr_IsDecimalInteger(const char *pStr);

/**
 * 校验字符串是否是有效的十六进制整型数值字符串
 */
BOOL    SStr_IsHexInteger(const char *pStr);

/*
 * 校验字符串是否是有效的整型数值字符串
 */
BOOL    SStr_IsInteger(const char *pStr, BOOL isUnitAble);

/*
 * 校验字符串是否是有效的数值型字符串
 */
BOOL    SStr_IsNumeric(const char *pStr, BOOL isUnitAble);

/*
 * 转换带单位的数值型字符串为长整型数值
 */
int64   SStr_ParseUnittedInteger(const char *pStr);

/*
 * 转换带单位的数值型字符串为长整型数值 (可指定当字符串为空时的默认值)
 */
int64   SStr_ParseUnittedInteger2(const char *pStr, int32 defaultValue);

/*
 * 解析BOOL型字符串
 */
int32   SStr_ParseBoolean(const char *pStr);

/*
 * 解析BOOL型字符串 (可指定当字符串为空时的默认值)
 */
int32   SStr_ParseBoolean2(const char *pStr, int32 defaultValue);
/* -------------------------           */


/* ===================================================================
 * 类型转换相关的 Inline 函数 (数值型 --> 字符串)
 * =================================================================== */

/**
 * 解析10进制数值型字符串
 *
 * @param   pValue  待转换的数值字符串
 * @return  转换后的数值
 */
static __inline long
SStr_StrtoL10(const char *pValue) {
    return strtol(pValue, (char **) NULL, 10);
}


/**
 * 解析10进制数值型字符串 (若参数为空则返回0)
 *
 * @param   pValue  待转换的数值字符串
 * @return  转换后的数值
 */
static __inline long
SStr_StrtoL10Nullable(const char *pValue) {
    if (__spk_unlikely(! pValue)) {
        return 0;
    }
    return SStr_StrtoL10(pValue);
}


/**
 * 解析10进制数值型字符串
 *
 * @param   pValue  待转换的数值字符串
 * @return  转换后的数值
 */
static __inline int64
SStr_StrtoLL10(const char *pValue) {
    return __spk_strtoll(pValue, (char **) NULL, 10);
}


/**
 * 解析10进制数值型字符串 (若参数为空则返回0)
 *
 * @param   pValue  待转换的数值字符串
 * @return  转换后的数值
 */
static __inline int64
SStr_StrtoLL10Nullable(const char *pValue) {
    if (__spk_unlikely(! pValue)) {
        return 0;
    }
    return SStr_StrtoLL10(pValue);
}


/**
 * 解析10进制数值型字符串
 *
 * @param   pValue  待转换的数值字符串
 * @return  转换后的数值
 */
static __inline int32
SStr_StrtoI10(const char *pValue) {
    return (int32) SStr_StrtoL10(pValue);
}


/**
 * 解析10进制数值型字符串 (若参数为空则返回0)
 *
 * @param   pValue  待转换的数值字符串
 * @return  转换后的数值
 */
static __inline int32
SStr_StrtoI10Nullable(const char *pValue) {
    if (__spk_unlikely(! pValue)) {
        return 0;
    }
    return SStr_StrtoI10(pValue);
}


/**
 * 解析指定长度的10进制数值型字符串
 *
 * @param   pValue  待转换的数值字符串
 * @param   len     数值字符串的有效长度
 * @return  转换后的数值
 */
static __inline long
SStr_FixedStrtoL10(const char *pValue, int32 len) {
    char            __tmpBuf[32];

    SLOG_ASSERT(pValue && len < (int32) sizeof(__tmpBuf));
    memcpy(__tmpBuf, pValue, len);
    __tmpBuf[len] = '\0';

    return strtol(__tmpBuf, (char **) NULL, 10);
}


/**
 * 解析指定长度的10进制数值型字符串
 *
 * @param   pValue  待转换的数值字符串
 * @param   len     数值字符串的有效长度
 * @return  转换后的数值
 */
static __inline int64
SStr_FixedStrtoLL10(const char *pValue, int32 len) {
    char            __tmpBuf[32];

    SLOG_ASSERT(pValue && len < (int32) sizeof(__tmpBuf));
    memcpy(__tmpBuf, pValue, len);
    __tmpBuf[len] = '\0';

    return SStr_StrtoLL10(__tmpBuf);
}


/**
 * 解析指定长度的10进制数值型字符串
 *
 * @param   pValue  待转换的数值字符串
 * @param   len     数值字符串的有效长度
 * @return  转换后的数值
 */
static __inline int32
SStr_FixedStrtoI10(const char *pValue, int32 len) {
    return (int32) SStr_FixedStrtoL10(pValue, len);
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_STRING_CONVERT_H */
