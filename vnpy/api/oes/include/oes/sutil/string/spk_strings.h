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
 * @file    spk_strings.h
 *
 * 字符串处理函数的头文件(线程安全)
 *
 * @version $Id$
 * @since   2012/01/05
 */


#ifndef _SPK_STRINGS_H
#define _SPK_STRINGS_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/cmnlib.h>
#include    <sutil/platform/spk_platforms.h>
#include    <sutil/string/spk_string_convert.h>
#include    <sutil/string/spk_string_var.h>
#include    <sutil/string/spk_multi_field_string.h>
#include    <sutil/string/spk_fixed_snprintf.h>
#include    <sutil/string/spk_strverscmp.h>
#include    <sutil/logger/spk_console_masked_log.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 跨平台兼容处理
 * =================================================================== */

#if defined (__WINDOWS__)
#   undef   snprintf
#   define  snprintf                SStr_Snprintf
#endif
/* -------------------------           */


/* ===================================================================
 * 函数声明
 * =================================================================== */

/*
 * compare two strings, and end with endChar
 */
int32   SStr_Strchcmp(const char *s1, const char *s2, int32 endChar);

/*
 * compare two strings ignoring case
 */
int32   SStr_Strncasecmp(const char *s1, const char *s2, int32 n);

/*
 * 替换目标字符串中的待替换字符串
 */
char*   SStr_Replace(char *pBuf, const char *pTarget, const char *pOldStr,
            const char *pNewStr);

/*
 * 替换目标字符串中的待替换字符串(可指定替换个数)
 */
char*   SStr_ReplaceAppointed(char *pBuf, const char *pTarget,
            const char *pOldStr, const char *pNewStr, int32 n);

/*
 * 取得被前、后缀包裹的字符串
 */
char*   SStr_GetWrappedString(char *pBuf, const char *pTarget,
            const char *pPrefix, const char *pPostfix);

/*
 * 构造被前、后缀包裹的字符串
 */
char*   SStr_BuildWrappedString(char *pBuf, const char *pTarget,
            int32 targetLen, const char *pPrefix, const char *pPostfix);

/*
 * 返回字符串是否是以指定的字符串起始的
 */
BOOL    SStr_IsStartWith(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n);

/*
 * 返回字符串是否是以指定的字符串起始的
 */
BOOL    SStr_IsStartWith2(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n, const char **ppAfterMatched);

/*
 * 返回字符串是否是以指定的字符串起始的 (忽略大小写)
 */
BOOL    SStr_IsIgnoreCaseStartWith(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n);

/*
 * 返回字符串是否是以指定的字符串起始的 (忽略大小写)
 */
BOOL    SStr_IsIgnoreCaseStartWith2(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n, const char **ppAfterMatched);

/*
 * 返回字符串是否是以指定的字符串结尾的
 */
BOOL    SStr_IsEndsWith(const char *pStr, const char *pEndsWith);

/*
 * 返回字符串是否是以指定的字符串结尾的 (忽略大小写)
 */
BOOL    SStr_IsIgnoreCaseEndsWith(const char *pStr, const char *pEndsWith);

/*
 * 统计字符串中指定字符出现的次数
 */
int32   SStr_TotalChars(const char *pStr, const char *pChars);
/* -------------------------           */


/* ===================================================================
 * Inline 函数
 * =================================================================== */

/**
 * check a char is any of a set of characters
 */
static __inline BOOL
SStr_IsAnyChar(const char ch, const char *accept) {
    SLOG_ASSERT(accept);
    while (*accept) {
        if (*accept++ == ch) {
            return TRUE;
        }
    }
    return FALSE;
}


/**
 * check a char is any of a set of characters
 */
static __inline BOOL
SStr_IsAnyChar2(const char ch, const char *accept, int len) {
    SLOG_ASSERT(accept);
    while (*accept && len--) {
        if (*accept++ == ch) {
            return TRUE;
        }
    }
    return FALSE;
}


/**
 * search a string for any of a set of characters
 *
 * The strpbrk() function locates the first occurrence in the string s of any
 * of the characters in the string accept.
 *
 * @return  returns a pointer to the character in s that matches one of the
 *          characters in accept, or NULL if no such character is found.
 * @see     strpbrk()
 */
static __inline char *
SStr_Strpbrk(const char *s, const char *accept) {
    if (__spk_unlikely(! s)) {
        return (char *) NULL;
    }

    while (*s) {
        if (SStr_IsAnyChar(*s, accept)) {
            return (char *) s;
        }
        ++s;
    }
    return (char *) NULL;
}


/**
 * search a string for any of a set of characters reverse
 *
 * @return  returns a pointer to the character in s that matches one of the
 *          characters in accept, or NULL if no such character is found.
 */
static __inline char *
SStr_StrpbrkReverse(const char *s, const char *accept) {
    int32   endPos = 0;

    if (__spk_unlikely(! s)) {
        return (char *) NULL;
    }

    endPos = (int32) strlen(s) - 1;
    while (endPos >= 0) {
        if (SStr_IsAnyChar(s[endPos], accept)) {
            return (char *) &s[endPos];
        }
        endPos--;
    }
    return (char *) NULL;
}


/**
 * extract token from string, and return the end of token
 *
 * 注意：
 * 对于theEnd的处理，要注意是否已考虑到对以下两种特殊情况的处理：
 * 1、delim位于字符串首。这时*theEnd == return
 * 2、若字符串不是以delim结尾的，当最后一次返回时，*theEnd == NULL
 */
static __inline char*
SStr_Strsep2(char **ppString, char **ppTokenEnd, const char *pDelim) {
    char    *pBegin = (char *) NULL;
    char    *pEnd = (char *) NULL;

    SLOG_ASSERT(ppString && pDelim && *pDelim);

    pBegin = *ppString;
    if (__spk_unlikely(! pBegin || ! *pBegin)) {
        *ppString = NULL;
        if (ppTokenEnd) {
            *ppTokenEnd = NULL;
        }
        return (char *) pBegin;
    }

    if (pDelim[1] == '\0') {
        if (*pBegin == pDelim[0]) {
            pEnd = pBegin;
        } else {
            pEnd = strchr(pBegin + 1, pDelim[0]);
        }
    } else {
        pEnd = SStr_Strpbrk(pBegin, pDelim);
    }

    if (pEnd) {
        *ppString = pEnd + 1;

        if (ppTokenEnd) {
            *ppTokenEnd = pEnd;
        } else {
            *pEnd = '\0';
        }
    } else {
        *ppString = NULL;

        if (ppTokenEnd) {
            *ppTokenEnd = NULL;
        }
    }

    return pBegin;
}


/**
 * extract token from string
 *
 * If *stringp is  NULL, the strsep() function returns NULL and does
 * nothing else.  Otherwise, this function finds the first token in the
 * string *stringp, where tokens are delimited by symbols in the string
 * delim. This token is terminated with a '\0' character (by overwriting
 * the delimiter) and *stringp  is updated to point past the token.
 * In case no delimiter was found, the token is taken to be the entire
 * string *stringp, and *stringp is made NULL.
 *
 * @return  The strsep() function returns a pointer to the token, that is,
 *          it returns the original value of *stringp.
 * @see     strsep()
 */
static __inline char*
SStr_Strsep(char **stringp, const char *delim) {
    return SStr_Strsep2(stringp, (char **) NULL, delim);
}


/**
 * 返回字符串是否是空字符串
 *
 * @param   pStr    待校验字符串
 * @return  TRUE, 为空; FALSE, 不为空
 */
static __inline BOOL
SStr_IsEmpty(const char *pStr) {
    return (! (pStr && *pStr));
}


/**
 * 返回字符串是否是空字符串
 *
 * @param   pStr    待校验字符串
 * @return  TRUE, 为空; FALSE, 不为空
 */
static __inline BOOL
SStr_IsBlank(const char *pStr) {
    if (pStr) {
        while (*pStr) {
            if (! SPK_ISSPACE(*pStr)) {
                return FALSE;
            }
            pStr++;
        }
    }
    return TRUE;
}


/**
 * 返回字符串是否全是有效的ASCII可见字符 (不能包含空格和不可见字符等)
 *
 * @param   pStr    待校验字符串
 * @return  TRUE, 有效; FALSE, 无效
 */
static __inline BOOL
SStr_IsVisibleAsciiString(const char *pStr) {
    if (__spk_unlikely(SStr_IsEmpty(pStr))) {
        return FALSE;
    }

    while (*pStr) {
        if (__spk_unlikely(*pStr < '!' || *pStr > '~')) {
            return FALSE;
        }
        pStr++;
    }

    return TRUE;
}


/**
 * 返回字符串是否是有效的MD5字符串
 * (字母+数字)
 *
 * @param   pStr    待校验字符串
 * @return  TRUE, 有效; FALSE, 无效
 */
static __inline BOOL
SStr_IsValidMd5String(const char *pStr) {
    static const int32  _MD5_STRING_LENGTH = 32;
    int32               i = 0;

    if (__spk_unlikely(SStr_IsEmpty(pStr))) {
        return FALSE;
    }

    while (pStr[i]) {
        if (__spk_unlikely(! SPK_ISALNUM(pStr[i]))) {
            return FALSE;
        }
        i++;
    }

    return i == _MD5_STRING_LENGTH ? TRUE : FALSE;
}


/**
 * 返回字符串是否是有效的密码串
 * (字母+数字, 以及 '@._-' 这几个邮箱地址相关的特殊字符)
 *
 * @param   pStr    待校验字符串
 * @return  TRUE, 有效; FALSE, 无效
 */
static __inline BOOL
SStr_IsValidPasswdString(const char *pStr) {
    if (__spk_unlikely(SStr_IsEmpty(pStr))) {
        return FALSE;
    }

    while (*pStr) {
        if (__spk_unlikely(! SPK_ISALNUM(*pStr)
                && ! SStr_IsAnyChar(*pStr, "@._-"))) {
            return FALSE;
        }
        pStr++;
    }

    return TRUE;
}


/**
 * 校验密码强度
 * (只能包含字母+数字, 以及 '@._-' 这几个邮箱地址相关的特殊字符)
 * (若指定密码强度或密码最小长度, 须符合对应限制条件)
 *
 * @param   pStr          待校验字符串
 * @param   strength      密码强度, 0表示无限制
 * @param   minLength     密码最小长度, 0表示无限制
 * @return  等于0: 有效; 大于0: 密码强度弱; 小于0: 密码包含无效字符
 */
static __inline int32
SStr_CheckPasswdStrength(const char *pStr, int32 strength, int32 minLength) {
    static const int32  _STRONGEST_PASSWD_STRENGTH = 4;
    int32               uppercaseCnt = 0;
    int32               lowercaseCnt = 0;
    int32               digitCnt = 0;
    int32               symbolCnt = 0;
    int32               totalLength = 0;
    int32               strengthLevel = 0;

    if (__spk_unlikely(SStr_IsEmpty(pStr))) {
        return SPK_NEG(EINVAL);
    }

    while (*pStr) {
        if (SPK_ISUPPER(*pStr)) {
            uppercaseCnt++;
        } else if (SPK_ISLOWER(*pStr)) {
            lowercaseCnt++;
        } else if (SPK_ISDIGIT(*pStr)) {
            digitCnt++;
        } else if (SStr_IsAnyChar(*pStr, "@._-")) {
            symbolCnt++;
        } else {
            return SPK_NEG(EINVAL);
        }
        pStr++;
    }

    totalLength = uppercaseCnt + lowercaseCnt + digitCnt + symbolCnt;
    strengthLevel = (uppercaseCnt > 0 ? 1 : 0)
            + (lowercaseCnt > 0 ? 1 : 0)
            + (digitCnt > 0 ? 1 : 0)
            + (symbolCnt > 0 ? 1 : 0);
    if (__spk_unlikely((minLength > 0 && totalLength < minLength)
            || strengthLevel < SPK_MIN(strength, _STRONGEST_PASSWD_STRENGTH))) {
        return EINVAL;
    }

    return 0;
}


/**
 * 若字符串为空则返回指定的值
 */
static __inline const char*
SStr_SwitchBlankStr(const char *s, const char *v) {
    return SStr_IsBlank(s) ? v : s;
}


/**
 * 返回跳过左端空格后的字符串
 *
 * @param   pStr    字符串
 * @return  跳过左端空格后的字符串指针
 */
static __inline const char*
SStr_Ltrim(const char *pStr) {
    if (__spk_unlikely(! pStr)) {
        return (const char *) NULL;
    }

    while (SPK_ISSPACE(*pStr)) {
        pStr++;
    }
    return pStr;
}


/**
 * 跳过字符串起始的空格和'0'
 *
 * @param   pStr    字符串
 * @return  跳过左端空格和'0'后的字符串指针
 */
static __inline const char*
SStr_LtrimZero(const char *pStr) {
    char        ch = 0;
    char        prev = 0;

    if (__spk_unlikely(! pStr)) {
        return (const char *) NULL;
    }

    while ((ch = *pStr) == '0' || SPK_ISSPACE(ch)) {
        pStr++;
        prev = ch;
    }

    if ((*pStr == 'x' || *pStr == '.') && prev == '0') {
        pStr--;
    }
    return pStr;
}


/**
 * 去除字符串右端的空格
 *
 * @param   pStr    字符串
 * @return  去除空格后的字符串
 */
static __inline char*
SStr_RtrimRude(char *pStr) {
    int32   endPos = 0;

    if (__spk_unlikely(! pStr)) {
        return (char *) NULL;
    }

    endPos = (int32) strlen(pStr) - 1;
    while (endPos >= 0 && SPK_ISSPACE(pStr[endPos])) {
        endPos--;
    }

    pStr[++endPos] = '\0';
    return pStr;
}


/**
 * 去除字符串前后端的空格
 *
 * @param   pStr    字符串
 * @return  去除空格后的字符串
 */
static __inline char*
SStr_TrimRude(char *pStr) {
    return SStr_RtrimRude((char *) SStr_Ltrim(pStr));
}


/**
 * 返回转换为大写后的字符串
 */
static __inline char*
SStr_ToUpper(char *pStr) {
    char    *pPtr = pStr;

    if (__spk_unlikely(! pStr)) {
        return (char *) NULL;
    }

    while (*pPtr) {
        *pPtr = SPK_TOUPPER((int32) *pPtr);
        pPtr++;
    }
    return pStr;
}


/**
 * 返回转换为大写后的字符串
 */
static __inline char*
SStr_ToUpperR(char *pBuf, const char *pStr) {
    int32   j = 0;

    SLOG_ASSERT(pBuf);
    if (__spk_unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (pStr[j]) {
        pBuf[j] = SPK_TOUPPER((int32) pStr[j]);
        j++;
    }
    pBuf[j] = '\0';

    return pBuf;
}


/**
 * 返回转换为小写后的字符串
 */
static __inline char*
SStr_ToLower(char *pStr) {
    char    *pPtr = pStr;

    if (__spk_unlikely(! pStr)) {
        return (char *) NULL;
    }

    while (*pPtr != '\0') {
        *pPtr = SPK_TOLOWER((int32) *pPtr);
        pPtr++;
    }
    return pStr;
}


/**
 * 返回转换为小写后的字符串
 */
static __inline char*
SStr_ToLowerR(char *pBuf, const char *pStr) {
    char    *pPtr = pBuf;
    int32   j = 0;

    SLOG_ASSERT(pBuf);
    if (__spk_unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (pStr[j]) {
        pPtr[j] = SPK_TOLOWER((int32) pStr[j]);
        j++;
    }

    pPtr[j] = '\0';
    return pPtr;
}


/**
 * 拷贝指定长度的字符串
 * <p>需保证缓存有足够的空间(maxStrLen + 1)</p>
 *
 * @param[out]  pBuf            用于输出数据的缓存区指针
 * @param       pStr            待拷贝的字符串
 * @param       maxStrLen       最大有效字符长度(不包括结尾的'\0')，即buf的长度需至少
 *                              为 maxStrLen + 1
 * @param[out]  pOutCopyLen     拷贝字符串的长度
 * @return      返回拷贝后字符串
 */
static __inline char*
SStr_StrCopy2(char *pBuf, const char *pStr, int32 maxStrLen,
        int32 *pOutCopyLen) {
    char    *pPtr = pBuf;

    SLOG_ASSERT(pPtr);

    if (__spk_likely(pStr)) {
        while (*pStr && maxStrLen-- != 0) {
            *pPtr++ = *pStr++;
        }
    }

    *pPtr = '\0';

    if (pOutCopyLen) {
        *pOutCopyLen = (int32) (pPtr - pBuf);
    }

    return pBuf;
}


/**
 * 拷贝指定长度的字符串
 * <p>需保证缓存有足够的空间(maxStrLen + 1)</p>
 *
 * @param[out]  pBuf            用于输出数据的缓存区指针
 * @param       pStr            待拷贝的字符串
 * @param       maxStrLen       最大有效字符长度(不包括结尾的'\0')，即buf的长度需至少
 *                              为 maxStrLen + 1
 * @return      返回拷贝后字符串
 */
static __inline char*
SStr_StrCopy(char *pBuf, const char *pStr, int32 maxStrLen) {
    return SStr_StrCopy2(pBuf, pStr, maxStrLen, (int32 *) NULL);
}


/**
 * 拷贝指定长度的字符串
 * <p>需保证缓存有足够的空间(maxStrlen + 1)</p>
 *
 * @param   strLen      有效字符长度(不包括结尾的'\0')，即buf的长度需至少为 strLen + 1
 */
static __inline char*
SStr_StrFixedLengthCopy(char *pBuf, const char *pStr, int32 strLen) {
    SLOG_ASSERT(pBuf);

    if (__spk_likely(pStr && strLen > 0)) {
        memcpy(pBuf, pStr, strLen);
        pBuf[strLen] = '\0';
    } else {
        *pBuf = '\0';
    }
    return pBuf;
}


/**
 * 从字符串中拷贝指定位置的子字符串
 *
 * @param[out]  pBuf        用于输出数据的缓存区指针
 * @param       pStr        待拷贝的字符串
 * @param       from        子字符串的开始位置 (从0开始计数, 小于等于0则从头开始复制)
 * @param       subLen      子字符串的长度 (小于等于0表示从末尾开始计数的子字符串结束位置)
 *                          - 大于0, 子字符串的长度
 *                          - 等于0, 复制从 from 至末尾的所有字符
 *                          - 小于0, 末尾开始计数的子字符串结束位置
 * @return      返回复制到字符串
 */
static __inline char*
SStr_SubStrCopy(char *pBuf, const char *pStr, int32 from, int32 subLen) {
    int32               totalLen = 0;

    SLOG_ASSERT(pBuf);
    if (__spk_unlikely(SStr_IsEmpty(pStr))) {
        *pBuf = '\0';
        return pBuf;
    }

    totalLen = (int32) strlen(pStr);
    if (from < 0) {
        from = 0;
    } else if (__spk_unlikely(from >= totalLen)) {
        *pBuf = '\0';
        return pBuf;
    }

    if (subLen <= 0) {
        subLen = (totalLen + subLen) - from;
    } else {
        subLen = SPK_MIN(subLen, totalLen - from);
    }

    if (__spk_likely(subLen > 0)) {
        SStr_StrCopy(pBuf, pStr + from, subLen);
    } else {
        *pBuf = '\0';
    }
    return pBuf;
}


/**
 * 连接两个字符串到新字符串中
 * <p>需保证缓存有足够的空间(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   最大有效字符长度(不包括结尾的'\0')，即buf的长度需至少
 *                      为 maxStrlen + 1
 */
static __inline char*
SStr_StrCat(char *pBuf, const char *s1, const char *s2, int32 maxStrlen) {
    char    *pPtr = pBuf;

    SLOG_ASSERT(pPtr);

    if (__spk_likely(s1)) {
        while (*s1 && maxStrlen != 0) {
            *pPtr++ = *s1++;
            maxStrlen--;
        }
    }

    if (__spk_likely(s2)) {
        while (*s2 && maxStrlen-- != 0) {
            *pPtr++ = *s2++;
        }
    }

    *pPtr = '\0';
    return pBuf;
}


/**
 * 连接字符串并将字符串指针移动到新字符串末尾
 *
 * @return 原字符串地址
 */
static __inline char*
SStr_StrCatP(char **ppString, const char *s, int32 *pMaxStrlen) {
    char                *pBegin = (char *) NULL;
    char                *pEnd = (char *) NULL;
    int32               maxStrlen = -1;

    if (__spk_unlikely(! ppString || ! *ppString)) {
        return (char *) NULL;
    } else if (__spk_unlikely(! s)) {
        return *ppString;
    } else {
        pBegin = pEnd = *ppString;
    }

    if (__spk_likely(pMaxStrlen)) {
        maxStrlen = *pMaxStrlen;
        if (__spk_unlikely(maxStrlen == 0)) {
            return pBegin;
        }
    }

    while (*pEnd) {
        pEnd++;
    }

    while (*s && maxStrlen != 0) {
        *pEnd++ = *s++;
        maxStrlen--;
    }

    if (__spk_likely(pMaxStrlen)) {
        *pMaxStrlen = maxStrlen;
    }

    *pEnd = '\0';
    *ppString = pEnd;

    return pBegin;
}


/**
 * 连接字符和字符串
 * <p>需保证缓存有足够的空间(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   参数 pStr 的最大字符串长度，buf的长度需至少为 maxStrlen + 1
 */
static __inline char*
SStr_StrCatChStr(char *pBuf, char ch, const char *pStr, int32 maxStrlen) {
    SLOG_ASSERT(pBuf && pStr);

    *pBuf = ch;
    memcpy(pBuf + 1, pStr, maxStrlen);

    pBuf[maxStrlen + 1] = '\0';
    return pBuf;
}


/**
 * 拷贝字符串并去除空格
 * <p>需保证缓存有足够的空间(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   最大有效字符长度(不包括结尾的'\0')，即buf的长度需至少
 *                      为 maxStrlen + 1
 */
static __inline char*
SStr_StrTrimCopy(char *pBuf, const char *pStr, int32 maxStrlen) {
    char    *pPtr = pBuf;

    SLOG_ASSERT(pPtr);

    if (__spk_unlikely(SStr_IsEmpty(pStr))) {
        *pBuf = '\0';
        return pBuf;
    }

    while (SPK_ISSPACE(*pStr)) {
        pStr++;
    }

    while (*pStr && maxStrlen-- != 0) {
        *pPtr++ = *pStr++;
    }

    do {
        *pPtr-- = '\0';
    } while (pPtr >= pBuf && SPK_ISSPACE(*pPtr));

    pPtr++;
    *pPtr = '\0';

    return pBuf;
}


/**
 * 先拷贝字符串再去除空格
 * <p>需保证缓存有足够的空间(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   最大有效字符长度(不包括结尾的'\0')，即buf的长度需至少
 *                      为 maxStrlen + 1
 */
static __inline char*
SStr_StrFixedLengthTrimCopy(char *pBuf, const char *pStr, int32 maxStrlen) {
    char    *pPtr = pBuf;

    SLOG_ASSERT(pPtr);
    if (__spk_unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (SPK_ISSPACE(*pStr) && maxStrlen != 0) {
        pStr++;
        maxStrlen--;
    }

    while (*pStr && maxStrlen-- != 0) {
        *pPtr++ = *pStr++;
    }

    do {
        pPtr--;
    } while (pPtr >= pBuf && SPK_ISSPACE(*pPtr));

    pPtr++;
    *pPtr = '\0';

    return pBuf;
}


/**
 * 以右对齐的方式拷贝字符串并去除空格
 * <p>需保证缓存有足够的空间(maxlen + 1)</p>
 *
 * @param   alignedLen  最大有效字符长度(不包括结尾的'\0')，即buf的长度需至少
 *                      为 alignedLen + 1
 */
static __inline char*
SStr_StrRightAlignmentCopy(char *pBuf, const char *pStr, int32 alignedLen,
        char leftFiller) {
    const char  *pPtr = (const char *) NULL;
    int32       len = alignedLen;

    if (__spk_unlikely(alignedLen <= 0)) {
        return SStr_StrTrimCopy(pBuf, pStr, alignedLen);
    }

    SLOG_ASSERT(pBuf);
    if (__spk_unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (SPK_ISSPACE(*pStr)) {
        pStr++;
    }

    pPtr = pStr;
    while (*pPtr && len != 0) {
        pPtr++;
        len--;
    }

    do {
        pPtr--;
        len++;
    } while (len <= alignedLen && SPK_ISSPACE(*pPtr));
    len--;

    memset(pBuf, leftFiller, len);
    memcpy(pBuf + len, pStr, alignedLen - len);

    pBuf[alignedLen] = '\0';
    return pBuf;
}


/**
 * 跳过空字符
 */
static __inline char*
SStr_SkipSpaces(char **ppStr) {
    SLOG_ASSERT(ppStr);

    while (SPK_ISSPACE(**ppStr)) {
        (*ppStr) ++;
    }
    return *ppStr;
}


/**
 * 从字符串末端反向跳过空字符
 */
static __inline void
SStr_SkipSpacesReverse(char **ppEnd, char *pBegin) {
    char    *pOriginEnd;

    SLOG_ASSERT(ppEnd);

    pOriginEnd = *ppEnd;
    while (*ppEnd > pBegin && SPK_ISSPACE(**ppEnd)) {
        (*ppEnd) --;
    }

    if (*ppEnd < pOriginEnd) {
        *((*ppEnd) + 1) = '\0';
    }

    if (SPK_ISSPACE(**ppEnd)) {
        **ppEnd = '\0';
    } else {
        (*ppEnd) ++;
    }
}


/**
 * 跳过所有字符直到指定的字符串末尾
 *
 * @param   ppStr       <in/out: char**> 待处理字符串的指针的指针
 * @param   pSkipKey    <char*> 待跳过的字符串指针
 * @return  小于0, 未找到指定的字符串; 大于等于0, 已跳过字符串的起始位置(相对值)
 */
static __inline int32
SStr_SkipString(char **ppStr, const char *pSkipKey) {
    char    *pStrFound = (char*) NULL;
    int32   offset = 0;

    SLOG_ASSERT(ppStr && pSkipKey);

    if (! (pStrFound = strstr(*ppStr, pSkipKey))) {
        return SPK_NEG(ENOENT);
    }

    offset = (int32) (pStrFound - *ppStr);
    *ppStr = pStrFound + strlen(pSkipKey);

    return offset;
}


/**
 * 替换字符串中的指定字符
 *
 * @param   pStr    待处理的字符串
 * @return  已替换的字符数量
 */
static __inline int32
SStr_ReplaceChar(char *pStr, const char c1, const char c2, int32 n) {
    int32   count = 0;

    SLOG_ASSERT(pStr);

    while (*pStr && n) {
        if (*pStr == c1) {
            *pStr = c2;
            n--;
            count++;
        }
        pStr ++;
    }
    return count;
}


/**
 * 从后面开始替换字符串中的指定字符
 *
 * @param   pStr    待处理的字符串
 * @return
 */
static __inline int32
SStr_ReplaceCharReverse(char *pStr, const char c1, const char c2, int32 n) {
    int32   endPos = 0;
    int32   count = 0;

    SLOG_ASSERT(pStr);

    endPos = strlen(pStr) - 1;
    while (endPos >= 0 && n) {
        if (pStr[endPos] == c1) {
            pStr[endPos] = c2;
            n--;
            count++;
        }
        endPos--;
    }
    return count;
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_STRINGS_H */
