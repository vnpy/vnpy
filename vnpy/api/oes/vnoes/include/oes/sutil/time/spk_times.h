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
 * @file    spk_times.h
 *
 * 日期/时间函数的头文件
 *
 * @version $Id$
 * @since   2004.4.26
 */


#ifndef _SPK_TIMES_H
#define _SPK_TIMES_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/cmnlib.h>
#include    <sutil/platform/spk_platforms.h>
#include    <sutil/logger/spk_console_masked_log.h>


#if defined (__WINDOWS__) || defined (__MINGW__)
#   include <sys/timeb.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定义
 * =================================================================== */

/*
 * 日期/时间格式定义
 */
#define     STIME_FORMAT_DATE                   "%Y%m%d"
#define     STIME_FORMAT_FORMATTED_DATE         "%Y-%m-%d"
#define     STIME_FORMAT_SHORT_DATE             "%y%m%d"
#define     STIME_FORMAT_FORMATTED_SHORT_DATE   "%y-%m-%d"
#define     STIME_FORMAT_TIME                   "%H%M%S"
#define     STIME_FORMAT_FORMATTED_TIME         "%H:%M:%S"
#define     STIME_FORMAT_TIMESTAMP              "%Y%m%d%H%M%S"
#define     STIME_FORMAT_FORMATTED_TIMESTAMP    "%Y-%m-%d %H:%M:%S"
/* -------------------------           */


/* ===================================================================
 * 跨平台兼容处理
 * =================================================================== */

#if defined (__WINDOWS__) || defined (__MINGW__)
#   define  __spk_gettimeofday                  __SPK_WIN32_gettimeofday

#   if (defined (_MSC_VER) && _MSC_VER < 1400) \
            || (! defined (_WIN32_WINNT) || _WIN32_WINNT < 0x0600)
#       define  __spk_localtime_r(T, P_TM)      __STime_LocaltimeR((T), (P_TM))
#   else
#       define  __spk_localtime_r(T, P_TM)      localtime_s((P_TM), (T))
#   endif


/* gettimeofday */
int         __SPK_WIN32_gettimeofday(STimevalT *tv, STimezoneT *tz);


#else
#   define  __spk_gettimeofday                  gettimeofday
#   define  __spk_localtime_r(T, P_TM)          localtime_r((T), (P_TM))


#endif
/* -------------------------           */


/* ===================================================================
 * 函数声明
 * =================================================================== */

/*
 * 格式化日期/时间
 */
char*       STime_FormatTime(char *pBuf, const struct tm *pTm,
                    const char *pFormat);

/*
 * 根据给定的格式解析时间字符串
 */
struct tm*  STime_ParseTime(struct tm *pTm, const char *pTimeStr,
                    const char *pFormat);

/*
 * 校验字符串是否是有效的日期型字符串
 */
BOOL        STime_IsValidDate(const char *pStr, const char *pFormat);

/*
 * 校验是否是有效的日期型整数 (YYYYMMDD)
 */
BOOL        STime_IsValidIntDate(int32 date);

/*
 * 返回 timeval 结构体大小
 */
int32       __STime_GetTimevalStructSize();
/* -------------------------           */


/* ===================================================================
 * 宏代码定义
 * =================================================================== */

/**
 * 校验 timeval 结构体大小是否匹配 (用于检查跨平台兼容性的场景)
 */
#define SPK_ASSERT_TIMEVAL_STRUCT_SIZE()                    \
        SLOG_ASSERT2((int32) sizeof(STimevalT) == \
                __STime_GetTimevalStructSize(), \
                "Conflicted struct STimevalT size! localSize[%d], expectSize[%d]", \
                (int32) sizeof(STimevalT), __STime_GetTimevalStructSize())
/* -------------------------           */


/**
 * 返回相差的微秒数
 *
 * @param   pTv1    开始时间
 * @param   pTv2    结束时间
 * @return  相差的微秒数
 */
#define __STIME_DiffTimevalMicrosecond(P_TV1, P_TV2)        \
        ( (int64) ((P_TV2)->tv_sec - (P_TV1)->tv_sec) * 1000000 \
                + (P_TV2)->tv_usec - (P_TV1)->tv_usec )
/* -------------------------           */


/* ===================================================================
 * Inline 方法
 * =================================================================== */

/**
 * 转换并返回tm结构的时间
 *
 * @param       unixSecs    number of seconds since 1970-01-01 00:00:00 +0000 (UTC)
 * @param[out]  pTm         用于输出当前时间的数据缓存
 * @param       timeZone    相对于标准时间的时区差, 例如北京时间的时区为 8
 * @return      tm结构的时间
 * @see         http://www.cnblogs.com/westfly/p/5139645.html
 */
static __inline struct tm*
__STime_FastSecondToDate2(const int64 unixSecs, struct tm *pResult,
        int32 timeZone) {
#   define  K_HOURS_IN_DAY          (24)
#   define  K_MINUTES_IN_HOUR       (60)
#   define  K_DAYS_FROM_UNIXTIME    (2472632)
#   define  K_DAYS_FROM_YEAR        (153)
#   define  K_MAGIC_UNKONWN_FIRST   (146097)
#   define  K_MAGIC_UNKONWN_SEC     (1461)

    int32       hours;
    int32       a, b, c, d, e, m;

    SLOG_ASSERT(pResult);
    pResult->tm_sec = unixSecs % K_MINUTES_IN_HOUR;

    hours = (int32) (unixSecs / K_MINUTES_IN_HOUR);
    pResult->tm_min = hours % K_MINUTES_IN_HOUR;

    hours /= K_MINUTES_IN_HOUR;
    pResult->tm_hour = (hours + timeZone) % K_HOURS_IN_DAY;
    pResult->tm_mday = (hours + timeZone) / K_HOURS_IN_DAY;

    a = pResult->tm_mday + K_DAYS_FROM_UNIXTIME;
    b = (a * 4 + 3) / K_MAGIC_UNKONWN_FIRST;
    c = (-b * K_MAGIC_UNKONWN_FIRST) / 4 + a;
    d = ((c * 4 + 3) / K_MAGIC_UNKONWN_SEC);
    e = -d * K_MAGIC_UNKONWN_SEC;
    e = e / 4 + c;

    m = (5 * e + 2) / K_DAYS_FROM_YEAR;
    pResult->tm_mday = -(K_DAYS_FROM_YEAR * m + 2) / 5 + e + 1;
    pResult->tm_mon = (-m / 10) * 12 + m + 2;
    pResult->tm_year = b * 100 + d - 6700 + (m / 10);

    return pResult;
}


/**
 * 转换并返回tm结构的时间
 *
 * @param       unixSecs    number of seconds since 1970-01-01 00:00:00 +0000 (UTC)
 * @param[out]  pTm         用于输出当前时间的数据缓存
 * @param       timeZone    相对于标准时间的时区差, 例如北京时间的时区为 8
 * @return      tm结构的时间
 * @see         http://www.cnblogs.com/westfly/p/5139645.html
 */
static __inline struct tm*
__STime_FastSecondToDate(const int64 unixSecs, struct tm *pResult) {
    return __STime_FastSecondToDate2(unixSecs, pResult, 8);
}


/**
 * 转换并返回tm结构的时间
 *
 * @param       unixSecs    number of seconds since 1970-01-01 00:00:00 +0000 (UTC)
 * @param[out]  pTm         用于输出当前时间的数据缓存
 * @return      tm结构的时间
 */
static __inline struct tm*
__STime_LocaltimeR(const time_t *pUnixSecs, struct tm *pResult) {
    return __STime_FastSecondToDate(*pUnixSecs, pResult);
}


/**
 * 返回当前系统时间
 *
 * @return  time_t
 * @see     time()
 */
static __inline time_t
STime_GetSysTime() {
    return time((time_t *) NULL);
}


/**
 * 返回tm结构的当前时间
 *
 * @param[out]  pOutTm  <struct tm *> 用于输出当前时间的数据缓存
 * @return      当前时间 (struct tm *)
 */
static __inline struct tm*
STime_GetCurrentTm(struct tm *pOutTm) {
    return __STime_FastSecondToDate(STime_GetSysTime(), pOutTm);
}


/**
 * 转换并返回tm结构的时间
 *
 * @param[out]  pOutTm      <struct tm *> 用于输出当前时间的数据缓存
 * @param       unixSecs    number of seconds since 1970-01-01 00:00:00 +0000 (UTC)
 * @return      tm结构的时间
 */
static __inline struct tm*
STime_GetTmBySeconds(struct tm *pOutTm, int64 unixSecs) {
    return __STime_FastSecondToDate(unixSecs, pOutTm);
}


/**
 * 返回微秒级的当前时间
 *
 * @param[out]  pTv     用于输出当前时间的数据缓存
 * @return      微秒级时间
 * @see         gettimeofday()
 */
static __inline STimevalT*
STime_GetTimeOfDay(STimevalT *pTv) {
    SLOG_ASSERT(pTv);

    __spk_gettimeofday(pTv, (STimezoneT *) NULL);
    return pTv;
}


/**
 * 返回微秒级的当前时间
 *
 * @param[out]  pTv     用于输出当前时间的数据缓存
 * @return      微秒级时间
 * @see         gettimeofday()
 */
static __inline STimeval32T*
STime_GetTimeOfDay32(STimeval32T *pTv) {
    STimevalT   tv = {0, 0};

    SLOG_ASSERT(pTv);

    __spk_gettimeofday(&tv, (STimezoneT *) NULL);
    pTv->tv_sec = tv.tv_sec;
    pTv->tv_usec = tv.tv_usec;

    return pTv;
}


/**
 * 返回纳秒级的当前时间
 *
 * @param[out]  pTs     用于输出当前时间的数据缓存
 * @return      纳秒级时间
 * @see         clock_gettime()
 */
static __inline STimespecT*
STime_GetClockTime(STimespecT *pTs) {
    SLOG_ASSERT(pTs);

#if defined (__LINUX__)
    clock_gettime(CLOCK_MONOTONIC, pTs);
#else
    STime_GetTimeOfDay((STimevalT *) pTs);
    pTs->tv_nsec *= 1000;
#endif

    return pTs;
}


/**
 * 返回毫秒级的当前时间
 *
 * @return  相对与UTC 1970年1月1日零时的毫秒数
 */
static __inline int64
STime_GetMillisecondsTime() {
    STimevalT   tv = {0, 0};

    __spk_gettimeofday(&tv, (STimezoneT *) NULL);
    return (int64) tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


/**
 * 返回相差的毫秒数
 *
 * @param   pTv1    开始时间
 * @param   pTv2    结束时间
 * @return  相差的毫秒数
 */
static __inline int64
STime_DiffMillisecond(const STimevalT *pTv1, const STimevalT *pTv2) {
    int64       diff = 0;

    SLOG_ASSERT(pTv1 && pTv2);

    diff = (pTv2->tv_sec - pTv1->tv_sec) * 1000;
    diff += (pTv2->tv_usec - pTv1->tv_usec) / 1000;

    return diff;
}


/**
 * 返回相差的毫秒数
 *
 * @param   pTv1    开始时间
 * @param   pTv2    结束时间
 * @return  相差的毫秒数
 */
static __inline int64
STime_DiffMillisecond32(const STimeval32T *pTv1, const STimeval32T *pTv2) {
    int64       diff = 0;

    SLOG_ASSERT(pTv1 && pTv2);

    diff = (pTv2->tv_sec - pTv1->tv_sec) * 1000;
    diff += (pTv2->tv_usec - pTv1->tv_usec) / 1000;

    return diff;
}


/**
 * 返回相差的毫秒数 (浮点数值)
 *
 * @param   pTv1    开始时间
 * @param   pTv2    结束时间
 * @return  相差的毫秒数
 */
static __inline double
STime_DiffMillisecondFloat(const STimevalT *pTv1, const STimevalT *pTv2) {
    double      diff = 0.0;

    SLOG_ASSERT(pTv1 && pTv2);

    diff = (pTv2->tv_sec - pTv1->tv_sec) * 1000;
    diff += (double) (pTv2->tv_usec - pTv1->tv_usec) / 1000;

    return diff;
}


/**
 * 返回相差的毫秒数 (浮点数值)
 *
 * @param   pTv1    开始时间
 * @param   pTv2    结束时间
 * @return  相差的毫秒数
 */
static __inline double
STime_DiffMillisecondFloat32(const STimeval32T *pTv1, const STimeval32T *pTv2) {
    double      diff = 0.0;

    SLOG_ASSERT(pTv1 && pTv2);

    diff = (pTv2->tv_sec - pTv1->tv_sec) * 1000;
    diff += (double) (pTv2->tv_usec - pTv1->tv_usec) / 1000;

    return diff;
}


/**
 * 返回相差的微秒数
 *
 * @param   pTv1    开始时间
 * @param   pTv2    结束时间
 * @return  相差的微秒数
 */
static __inline int64
STime_DiffMicrosecond(const STimevalT *pTv1, const STimevalT *pTv2) {
    SLOG_ASSERT(pTv1 && pTv2);
    return __STIME_DiffTimevalMicrosecond(pTv1, pTv2);
}


/**
 * 返回相差的微秒数
 *
 * @param   pTv1    开始时间
 * @param   pTv2    结束时间
 * @return  相差的微秒数
 */
static __inline int64
STime_DiffMicrosecond32(const STimeval32T *pTv1, const STimeval32T *pTv2) {
    SLOG_ASSERT(pTv1 && pTv2);
    return __STIME_DiffTimevalMicrosecond(pTv1, pTv2);
}


/**
 * 返回相差的纳秒数
 *
 * @param   pTs1    开始时间
 * @param   pTs2    结束时间
 * @return  相差的纳秒数
 */
static __inline int64
STime_DiffTimespecNs(const STimespecT *pTs1, const STimespecT *pTs2) {
    int64       diff = 0;

    SLOG_ASSERT(pTs1 && pTs2);

    diff = (int64) (pTs2->tv_sec - pTs1->tv_sec) * 1000000000;
    diff += pTs2->tv_nsec - pTs1->tv_nsec;

    return diff;
}


/**
 * 返回相差的微秒数
 *
 * @param   pTs1    开始时间
 * @param   pTs2    结束时间
 * @return  相差的微秒数
 */
static __inline int64
STime_DiffTimespecUs(const STimespecT *pTs1, const STimespecT *pTs2) {
    int64       diff = 0;

    SLOG_ASSERT(pTs1 && pTs2);

    diff = (int64) (pTs2->tv_sec - pTs1->tv_sec) * 1000000;
    diff += (pTs2->tv_nsec - pTs1->tv_nsec) / 1000;

    return diff;
}


/**
 * 返回相差的毫秒数
 *
 * @param   pTs1    开始时间
 * @param   pTs2    结束时间
 * @return  相差的毫秒数
 */
static __inline int64
STime_DiffTimespecMs(const STimespecT *pTs1, const STimespecT *pTs2) {
    int64       diff = 0;

    SLOG_ASSERT(pTs1 && pTs2);

    diff = (int64) (pTs2->tv_sec - pTs1->tv_sec) * 1000;
    diff += (pTs2->tv_nsec - pTs1->tv_nsec) / 1000000;

    return diff;
}


/**
 * 判断是否闰年
 *
 * @param   年份
 * @return  TRUE: 闰年； FALSE: 不是闰年
 */
static __inline BOOL
STime_IsLeapYear(int32 iYear){
    return ((iYear % 4 == 0 && iYear % 100 != 0) || iYear % 400 == 0)
            ? TRUE : FALSE;
}


/**
 * 返回指定月份的自然日天数
 *
 * @param   iYearMonth      指定月份(YYYYMM)
 * @return  >0  自然日天数
 *          <=0 失败
 */
static __inline int32
STime_GetMonthDays(int32 year, int32 month) {
    static const int32  normalDays[] = {
            0, \
            31, 28, 31, 30, 31, 30, \
            31, 31, 30, 31, 30, 31
    };
    static const int32  leapYearDays[] = {
            0, \
            31, 29, 31, 30, 31, 30, \
            31, 31, 30, 31, 30, 31
    };

    if (unlikely(month <= 0 || month > 12)) {
        return 0;
    }

    if (STime_IsLeapYear(year)) {
        return leapYearDays[month];
    }
    return normalDays[month];
}


/**
 * 返回年份
 *
 * @return  年份
 */
static __inline int32
STime_GetYearOfTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return pTm->tm_year + 1900;
}


/**
 * 返回月份
 *
 * @return  月份
 */
static __inline int32
STime_GetMonthOfTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return pTm->tm_mon + 1;
}


/**
 * 返回日期(本月第几日)
 *
 * @return  本月第几日
 */
static __inline int32
STime_GetDayOfTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return pTm->tm_mday;
}


/**
 * 返回小时数
 *
 * @return  小时数
 */
static __inline int32
STime_GetHourOfTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return pTm->tm_hour;
}


/**
 * 返回分钟数
 *
 * @return  分钟数
 */
static __inline int32
STime_GetMinuteOfTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return pTm->tm_min;
}


/**
 * 返回秒数
 *
 * @return  秒数
 */
static __inline int32
STime_GetSecondOfTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return pTm->tm_sec;
}


/**
 * 返回年份
 *
 * @param   iDate   YYYYMMDD 格式的整型日期
 * @return  年份
 */
static __inline int32
STime_GetYearOfIntDate(int32 iDate) {
    return iDate / 10000;
}


/**
 * 返回月份
 *
 * @param   iDate   YYYYMMDD 格式的整型日期
 * @return  月份
 */
static __inline int32
STime_GetMonthOfIntDate(int32 iDate) {
    return (iDate % 10000) / 100;
}


/**
 * 返回日期(本月第几日)
 *
 * @param   iDate   YYYYMMDD 格式的整型日期
 * @return  本月第几日
 */
static __inline int32
STime_GetDayOfIntDate(int32 iDate) {
    return iDate % 100;
}


/**
 * 返回小时数
 *
 * @param   iTime   HHMMSS 格式的整型时间
 * @return  小时数
 */
static __inline int32
STime_GetHourOfIntTime(int32 iTime) {
    return iTime / 10000;
}


/**
 * 返回分钟数
 *
 * @param   iTime   HHMMSS 格式的整型时间
 * @return  分钟数
 */
static __inline int32
STime_GetMinuteOfIntTime(int32 iTime) {
    return (iTime % 10000) / 100;
}


/**
 * 返回秒数
 *
 * @param   iTime   HHMMSS 格式的整型时间
 * @return  秒数
 */
static __inline int32
STime_GetSecondOfIntTime(int32 iTime) {
    return iTime % 100;
}


/**
 * 返回小时数
 *
 * @param   iTime   HHMMSSsss 格式的整型时间
 * @return  小时数
 */
static __inline int32
STime_GetHourOfIntTimeMs(int32 iTime) {
    return iTime / 10000000;
}


/**
 * 返回分钟数
 *
 * @param   iTime   HHMMSSsss 格式的整型时间
 * @return  分钟数
 */
static __inline int32
STime_GetMinuteOfIntTimeMs(int32 iTime) {
    return (iTime % 10000000) / 100000;
}


/**
 * 返回秒数
 *
 * @param   iTime   HHMMSSsss 格式的整型时间
 * @return  秒数
 */
static __inline int32
STime_GetSecondOfIntTimeMs(int32 iTime) {
    return (iTime % 100000) / 1000;
}


/**
 * 返回毫秒数
 *
 * @param   iTime   HHMMSSsss 格式的整型时间
 * @return  毫秒数
 */
static __inline int32
STime_GetMillisecondOfIntTimeMs(int32 iTime) {
    return iTime % 1000;
}


/**
 * 计算两个整型日期值之间相差的天数
 *
 * @param   beginDate   起始时间 (YYYYMMDD)
 * @param   endDate     结束时间 (YYYYMMDD)
 * @return  相差的天数
 */
static __inline int32
STime_DiffIntDays(int32 iBeginDate, int32 iEndDate) {
    int32           beginYear = 0;
    int32           beginMonth = 0;
    int32           beginDay = 0;
    int32           endYear = 0;
    int32           endMonth = 0;
    int32           endDay = 0;
    int32           y1 = 0;
    int32           m1 = 0;
    int32           d1 = 0;
    int32           y2 = 0;
    int32           m2 = 0;
    int32           d2 = 0;

    beginYear = STime_GetYearOfIntDate(iBeginDate);
    beginMonth = STime_GetMonthOfIntDate(iBeginDate);
    beginDay = STime_GetDayOfIntDate(iBeginDate);

    endYear = STime_GetYearOfIntDate(iEndDate);
    endMonth = STime_GetMonthOfIntDate(iEndDate);
    endDay = STime_GetDayOfIntDate(iEndDate);

    m1 = (beginMonth + 9) % 12;
    y1 = beginYear - m1 / 10;
    d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10
            + (beginDay - 1);

    m2 = (endMonth + 9) % 12;
    y2 = endYear - m2 / 10;
    d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10
            + (endDay - 1);

    return (d2 - d1);
}


/**
 * 计算两个整型时间值之间相差的秒数
 *
 * @param   beginTime   起始时间 (HHMMSS)
 * @param   endTime     结束时间 (HHMMSS)
 * @return  相差的秒数
 */
static __inline int32
STime_DiffIntTime(int32 beginTime, int32 endTime) {
    int32           beginSecs = 0;
    int32           endSecs = 0;

    beginSecs = STime_GetHourOfIntTime(beginTime) * 3600
            + STime_GetMinuteOfIntTime(beginTime) * 60
            + STime_GetSecondOfIntTime(beginTime);

    endSecs = STime_GetHourOfIntTime(endTime) * 3600
            + STime_GetMinuteOfIntTime(endTime) * 60
            + STime_GetSecondOfIntTime(endTime);

    return (endSecs - beginSecs);
}


/**
 * 计算两个整型时间值之间相差的毫秒数
 *
 * @param   beginTime   起始时间 (HHMMSSsss)
 * @param   endTime     结束时间 (HHMMSSsss)
 * @return  相差的毫秒数
 */
static __inline int32
STime_DiffIntTimeMs(int32 beginTimeMs, int32 endTimeMs) {
    int32           beginMs = 0;
    int32           endMs = 0;

    beginMs = STime_GetHourOfIntTimeMs(beginTimeMs) * 3600 * 1000
            + STime_GetMinuteOfIntTimeMs(beginTimeMs) * 60 * 1000
            + beginTimeMs % 100000;

    endMs = STime_GetHourOfIntTimeMs(endTimeMs) * 3600 * 1000
            + STime_GetMinuteOfIntTimeMs(endTimeMs) * 60 * 1000
            + endTimeMs % 100000;

    return (endMs - beginMs);
}


/**
 * 格式化时间为yyyymmdd格式的日期字符串
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTm     tm 结构
 * @return      yyyymmdd格式的日期字符串
 */
static __inline char*
STime_FormatTmToDate(char *pBuf, const struct tm *pTm) {
    SLOG_ASSERT(pBuf && pTm);
    snprintf(pBuf, 9, "%d%02d%02d",
            pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
    return pBuf;
}


/**
 * 格式化时间为yyyy-mm-dd格式的日期字符串
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTm     tm 结构
 * @return      yyyy-mm-dd格式的日期字符串
 */
static __inline char*
STime_FormatTmToDate2(char *pBuf, const struct tm *pTm) {
    SLOG_ASSERT(pBuf && pTm);
    snprintf(pBuf, 11, "%d-%02d-%02d",
            pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
    return pBuf;
}


/**
 * 格式化时间为yyyy*mm*dd格式的日期字符串
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTm     tm 结构
 * @return      yyyy*mm*dd格式的日期字符串
 */
static __inline char*
STime_FormatTmToDate3(char *pBuf, const struct tm *pTm, char delimChar) {
    SLOG_ASSERT(pBuf && pTm);
    snprintf(pBuf, 11, "%d%c%02d%c%02d",
            pTm->tm_year + 1900, delimChar,
            pTm->tm_mon + 1, delimChar,
            pTm->tm_mday);
    return pBuf;
}


/**
 * 格式化时间为hhmmss格式的时间字符串
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTm     tm 结构
 * @return      hhmmss格式的时间字符串
 */
static __inline char*
STime_FormatTmToTime(char *pBuf, const struct tm *pTm) {
    SLOG_ASSERT(pBuf && pTm);
    snprintf(pBuf, 7, "%02d%02d%02d",
            pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
    return pBuf;
}


/**
 * 格式化时间为hh:mm:ss格式的时间字符串
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTm     tm 结构
 * @return      hh:mm:ss格式的时间字符串
 */
static __inline char*
STime_FormatTmToTime2(char *pBuf, const struct tm *pTm) {
    SLOG_ASSERT(pBuf && pTm);
    snprintf(pBuf, 9, "%02d:%02d:%02d",
            pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
    return pBuf;
}


/**
 * 格式化时间为hh*mm*ss格式的时间字符串
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTm     tm 结构
 * @return      hh*mm*ss格式的时间字符串
 */
static __inline char*
STime_FormatTmToTime3(char *pBuf, const struct tm *pTm, char delimChar) {
    SLOG_ASSERT(pBuf && pTm);
    snprintf(pBuf, 9, "%02d%c%02d%c%02d",
            pTm->tm_hour, delimChar,
            pTm->tm_min, delimChar,
            pTm->tm_sec);
    return pBuf;
}


/**
 * 格式化时间为YYYYMMDD-HH:mm:SS格式的17位日期字符串
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTm     tm 结构
 * @return      YYYYMMDD-HH:mm:SS格式的17位日期字符串
 */
static __inline char*
STime_FormatTmToTimestamp(char *pBuf, const struct tm *pTm) {
    SLOG_ASSERT(pBuf && pTm);
    snprintf(pBuf, 18, "%d%02d%02d-%02d:%02d:%02d",
            pTm->tm_year + 1900,
            pTm->tm_mon + 1,
            pTm->tm_mday,
            pTm->tm_hour,
            pTm->tm_min,
            pTm->tm_sec);
    return pBuf;
}


/**
 * 格式化时间为形如"YYYYMMDD-HH:mm:SS"的17位时间戳字符串返回
 *
 * @param[out]  pBuf        缓存区指针
 * @param       unixSecs    number of seconds since 1970-01-01 00:00:00 +0000 (UTC)
 * @return      形如"YYYYMMDD-HH:mm:SS"的17位时间戳字符串
 */
static __inline char*
STime_FormatUnixTimestamp(char *pBuf, int64 unixSecs) {
    struct tm       tm1;

    SLOG_ASSERT(pBuf);

    __STime_FastSecondToDate(unixSecs, &tm1);

    snprintf(pBuf, 18, "%d%02d%02d-%02d:%02d:%02d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec);
    return pBuf;
}


/**
 * 格式化时间为形如"YYYYMMDD-HH:mm:SS"的17位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTv     待格式化的时间
 * @return      形如"YYYYMMDD-HH:mm:SS"的17位时间戳字符串
 */
static __inline char*
STime_FormatTimevalSecs(char *pBuf, const STimevalT *pTv) {
    struct tm       tm1;

    SLOG_ASSERT(pBuf && pTv);

    __STime_FastSecondToDate(pTv->tv_sec, &tm1);

    snprintf(pBuf, 18, "%d%02d%02d-%02d:%02d:%02d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec);
    return pBuf;
}


/**
 * 格式化时间为形如"YYYYMMDD-HH:mm:SS.sss"的21位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTv     待格式化的时间
 * @return      形如"YYYYMMDD-HH:mm:SS.sss"的21位时间戳字符串
 */
static __inline char*
STime_FormatTimevalMs(char *pBuf, const STimevalT *pTv) {
    struct tm       tm1;

    SLOG_ASSERT(pBuf && pTv);

    __STime_FastSecondToDate(pTv->tv_sec, &tm1);

    snprintf(pBuf, 22, "%d%02d%02d-%02d:%02d:%02d.%03d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec,
            (int32) (pTv->tv_usec / 1000));
    return pBuf;
}


/**
 * 格式化时间为形如"YYYYMMDD-HH:mm:SS.ssss"的22位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTv     待格式化的时间
 * @return      形如"YYYYMMDD-HH:mm:SS.ssss"的22位时间戳字符串
 */
static __inline char*
STime_FormatTimevalMs4(char *pBuf, const STimevalT *pTv) {
    struct tm       tm1;

    SLOG_ASSERT(pBuf && pTv);

    __STime_FastSecondToDate(pTv->tv_sec, &tm1);

    snprintf(pBuf, 23, "%d%02d%02d-%02d:%02d:%02d.%04d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec,
            (int32) (pTv->tv_usec / 100));
    return pBuf;
}


/**
 * 格式化时间为形如"YYYYMMDD-HH:mm:SS.sss"的21位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTs     待格式化的时间
 * @return      形如"YYYYMMDD-HH:mm:SS.sss"的21位时间戳字符串
 */
static __inline char*
STime_FormatTimespecMs(char *pBuf, const STimespecT *pTs) {
    struct tm       tm1;

    SLOG_ASSERT(pBuf && pTs);

    __STime_FastSecondToDate(pTs->tv_sec, &tm1);

    snprintf(pBuf, 22, "%d%02d%02d-%02d:%02d:%02d.%03d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec,
            (int32) (pTs->tv_nsec / 1000000));
    return pBuf;
}


/**
 * 格式化时间为形如"YYYYMMDD-HH:mm:SS.ssss"的22位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @param       pTs     待格式化的时间
 * @return      形如"YYYYMMDD-HH:mm:SS.ssss"的22位时间戳字符串
 */
static __inline char*
STime_FormatTimespecMs4(char *pBuf, const STimespecT *pTs) {
    struct tm       tm1;

    SLOG_ASSERT(pBuf && pTs);

    __STime_FastSecondToDate(pTs->tv_sec, &tm1);

    snprintf(pBuf, 23, "%d%02d%02d-%02d:%02d:%02d.%04d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec,
            (int32) (pTs->tv_nsec / 100000));
    return pBuf;
}


/**
 * 返回当前时间, 以形如"YYYYMMDD-HH:mm:SS"的17位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @return      形如"YYYYMMDD-HH:mm:SS"的17位时间戳字符串
 */
static __inline char*
STime_GetFormattedTimestamp(char *pBuf) {
    struct tm       tm1;

    SLOG_ASSERT(pBuf);
    return STime_FormatTmToTimestamp(pBuf, STime_GetCurrentTm(&tm1));
}


/**
 * 返回当前时间, 以形如"YYYYMMDD-HH:mm:SS.sss"的21位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @return      形如"YYYYMMDD-HH:mm:SS.sss"的21位时间戳字符串
 */
static __inline char*
STime_GetFormattedTimestampMs(char *pBuf) {
    STimevalT       tv;

    SLOG_ASSERT(pBuf);
    return STime_FormatTimevalMs(pBuf, STime_GetTimeOfDay(&tv));
}


/**
 * 返回当前时间, 以形如"YYYYMMDD-HH:mm:SS.ssss"的2s位时间戳字符串返回
 *
 * @param[out]  pBuf    缓存区指针
 * @return      形如"YYYYMMDD-HH:mm:SS.ssss"的22位时间戳字符串
 */
static __inline char*
STime_GetFormattedTimestampMs4(char *pBuf) {
    STimevalT       tv;

    SLOG_ASSERT(pBuf);
    return STime_FormatTimevalMs4(pBuf, STime_GetTimeOfDay(&tv));
}


/**
 * 转换日期为yyyymmdd格式的int型日期值
 *
 * @param[in]   tm1     tm 结构
 * @return      yyyymmdd格式的int型日期值
 */
static __inline int32
STime_GetIntDateFromTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return (pTm->tm_year + 1900) * 10000 + (pTm->tm_mon + 1) * 100
            + pTm->tm_mday;
}


/**
 * 转换日期为hhmmss格式的int型时间值
 *
 * @param[in]   tm1     tm 结构
 * @return      hhmmss格式的int型时间值
 */
static __inline int32
STime_GetIntTimeFromTm(const struct tm *pTm) {
    SLOG_ASSERT(pTm);
    return pTm->tm_hour * 10000 + pTm->tm_min * 100 + pTm->tm_sec;
}


/**
 * 转换INT型日期/时间到 tm 结构
 *
 * @param[out]  pTm     <struct tm *> tm 结构
 * @param       iDate   yyyymmdd格式的int型日期值
 * @param       iTime   hhmmss格式的int型时间值
 * @return      tm 结构
 */
static __inline struct tm*
STime_ConvertIntToTm(struct tm *pOutTm, int32 iDate, int32 iTime) {
    SLOG_ASSERT(pOutTm);
    memset(pOutTm, 0, sizeof(struct tm));

    if (likely(iDate > 0)) {
        pOutTm->tm_year = STime_GetYearOfIntDate(iDate) - 1900;
        pOutTm->tm_mon = STime_GetMonthOfIntDate(iDate) - 1;
        pOutTm->tm_mday = STime_GetDayOfIntDate(iDate);
    }

    if (likely(iTime > 0)) {
        pOutTm->tm_hour = STime_GetHourOfIntTime(iTime);
        pOutTm->tm_min = STime_GetMinuteOfIntTime(iTime);
        pOutTm->tm_sec = STime_GetSecondOfIntTime(iTime);
    }

    return pOutTm;
}


/**
 * 转换INT型日期/时间为日历时间
 *
 * @param   iDate   yyyymmdd格式的int型日期值
 * @param   iTime   hhmmss格式的int型时间值
 * @return  日历时间, 即到UTC 1970年1月1日零时的秒数
 */
static __inline int64
STime_ConvertIntToSeconds(int32 iDate, int32 iTime) {
    struct tm   tm1;

    STime_ConvertIntToTm(&tm1, iDate, iTime);
    return mktime(&tm1);
}


/**
 * 返回当前日期的整数表示(YYYYMMDD)
 *
 * @return  int32 当前日期, 格式为YYYYMMDD
 */
static __inline int32
STime_GetIntDate() {
    struct tm   tm1;
    return STime_GetIntDateFromTm(STime_GetCurrentTm(&tm1));
}


/**
 * 返回当前时间的整数表示(HHMMSS)
 *
 * @return  int32 当前时间, 格式为HHMMSS
 */
static __inline int32
STime_GetIntTime() {
    struct tm   tm1;
    return STime_GetIntTimeFromTm(STime_GetCurrentTm(&tm1));
}


/**
 * 返回当前时间的整数表示(HHMMSSsss)
 *
 * @return  int32 当前时间(毫秒), 格式为HHMMSSsss
 */
static __inline int32
STime_GetIntTimeMs() {
    struct tm       tm1;
    STimevalT       tv;

    STime_GetTimeOfDay(&tv);
    STime_GetTmBySeconds(&tm1, tv.tv_sec);

    return STime_GetIntTimeFromTm(&tm1) * 1000 + tv.tv_usec / 1000;
}


/**
 * 返回当前日期的整数表示(YYYYMMDD)
 *
 * @param   time    日历时间, 即到UTC 1970年1月1日零时的秒数
 * @return  int32 当前日期, 格式为YYYYMMDD
 */
static __inline int32
STime_GetIntDateFromSeconds(int64 time) {
    struct tm   tm1;
    return STime_GetIntDateFromTm(STime_GetTmBySeconds(&tm1, time));
}


/**
 * 返回当前时间的整数表示(HHMMSS)
 *
 * @param   time    日历时间, 即到UTC 1970年1月1日零时的秒数
 * @return  int32 当前时间(秒), 格式为HHMMSS
 */
static __inline int32
STime_GetIntTimeFromSeconds(int64 time) {
    struct tm   tm1;
    return STime_GetIntTimeFromTm(STime_GetTmBySeconds(&tm1, time));
}


/**
 * 返回精度为毫秒的UTC相对时间
 *
 * @param   pTv     当前时间
 * @return  相对与UTC 1970年1月1日零时的毫秒数
 */
static __inline int64
STime_GetMillisecondsFromTimeval(const STimevalT *pTv) {
    SLOG_ASSERT(pTv);
    return (int64) pTv->tv_sec * 1000 + pTv->tv_usec / 1000;
}


/**
 * 返回精度为毫秒的UTC相对时间
 *
 * @param   pTv     当前时间
 * @return  相对与UTC 1970年1月1日零时的毫秒数
 */
static __inline int64
STime_GetMillisecondsFromTimeval32(const STimeval32T *pTv) {
    SLOG_ASSERT(pTv);
    return (int64) pTv->tv_sec * 1000 + pTv->tv_usec / 1000;
}


/**
 * 返回当前日期的整数表示(YYYYMMDD)
 *
 * @param   pTv     当前时间
 * @return  int32 当前日期, 格式为YYYYMMDD
 */
static __inline int32
STime_GetIntDateFromTimeval(const STimevalT *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return STime_GetIntDateFromTm(&tm1);
}


/**
 * 返回当前日期的整数表示(YYYYMMDD)
 *
 * @param   pTv     当前时间
 * @return  int32 当前日期, 格式为YYYYMMDD
 */
static __inline int32
STime_GetIntDateFromTimeval32(const STimeval32T *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return STime_GetIntDateFromTm(&tm1);
}


/**
 * 返回当前时间的整数表示(秒, HHMMSS)
 *
 * @param   pTv     当前时间
 * @return  int32 当前时间(秒), 格式为HHMMSS
 */
static __inline int32
STime_GetIntTimeFromTimeval(const STimevalT *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return STime_GetIntTimeFromTm(&tm1);
}


/**
 * 返回当前时间的整数表示(秒, HHMMSS)
 *
 * @param   pTv     当前时间
 * @return  int32 当前时间(秒), 格式为HHMMSS
 */
static __inline int32
STime_GetIntTimeFromTimeval32(const STimeval32T *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return STime_GetIntTimeFromTm(&tm1);
}


/**
 * 返回当前时间的整数表示(毫秒, HHMMSSsss)
 *
 * @param   pTv     当前时间
 * @return  int32 当前时间(毫秒), 格式为HHMMSSsss
 */
static __inline int32
STime_GetIntTimeMsFromTimeval(const STimevalT *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return STime_GetIntTimeFromTm(&tm1) * 1000 + pTv->tv_usec / 1000;
}


/**
 * 返回当前时间的整数表示(毫秒, HHMMSSsss)
 *
 * @param   pTv     当前时间
 * @return  int32 当前时间(毫秒), 格式为HHMMSSsss
 */
static __inline int32
STime_GetIntTimeMsFromTimeval32(const STimeval32T *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return STime_GetIntTimeFromTm(&tm1) * 1000 + pTv->tv_usec / 1000;
}


/**
 * 返回当前时间戳的整数表示(YYYYMMDDHHMMSSsss)
 *
 * @param   pTv     当前时间
 * @return  int64 当前时间, 格式为YYYYMMDDHHMMSSsss
 */
static __inline int64
STime_GetIntTimestampFromTimeval(const STimevalT *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return (int64) STime_GetIntDateFromTm(&tm1) * 1000000000
            + STime_GetIntTimeFromTm(&tm1) * 1000 + pTv->tv_usec / 1000;
}


/**
 * 返回当前时间戳的整数表示(YYYYMMDDHHMMSSsss)
 *
 * @param   pTv     当前时间
 * @return  int64 当前时间, 格式为YYYYMMDDHHMMSSsss
 */
static __inline int64
STime_GetIntTimestampFromTimeval32(const STimeval32T *pTv) {
    struct tm   tm1;

    SLOG_ASSERT(pTv);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    return (int64) STime_GetIntDateFromTm(&tm1) * 1000000000
            + STime_GetIntTimeFromTm(&tm1) * 1000 + pTv->tv_usec / 1000;
}


/**
 * 输出当前时间戳的整数表示
 *
 * @param       pTv         当前时间
 * @param[out]  pOutDate    输出当前日期, 格式为YYYYMMDD
 * @param[out]  pOutTimeMs  输出当前时间(毫秒), 格式为HHMMSSsss
 */
static __inline void
STime_GetIntTimestamp2FromTimeval(const STimevalT *pTv, int32 *pOutDate,
        int32 *pOutTimeMs) {
    struct tm   tm1;

    SLOG_ASSERT(pTv && pOutDate && pOutTimeMs);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    *pOutDate = STime_GetIntDateFromTm(&tm1);
    *pOutTimeMs = STime_GetIntTimeFromTm(&tm1) * 1000 + pTv->tv_usec / 1000;
}


/**
 * 输出当前时间戳的整数表示
 *
 * @param       pTv         当前时间
 * @param[out]  pOutDate    输出当前日期, 格式为YYYYMMDD
 * @param[out]  pOutTimeMs  输出当前时间(毫秒), 格式为HHMMSSsss
 */
static __inline void
STime_GetIntTimestamp2FromTimeval32(const STimeval32T *pTv, int32 *pOutDate,
        int32 *pOutTimeMs) {
    struct tm   tm1;

    SLOG_ASSERT(pTv && pOutDate && pOutTimeMs);
    STime_GetTmBySeconds(&tm1, pTv->tv_sec);

    *pOutDate = STime_GetIntDateFromTm(&tm1);
    *pOutTimeMs = STime_GetIntTimeFromTm(&tm1) * 1000 + pTv->tv_usec / 1000;
}


/**
 * 返回当前日期的整数表示(YYYYMMDD)
 *
 * @param   pTs     当前时间
 * @return  int32 当前日期, 格式为YYYYMMDD
 */
static __inline int32
STime_GetIntDateFromTimespec(const STimespecT *pTs) {
    struct tm   tm1;

    SLOG_ASSERT(pTs);
    STime_GetTmBySeconds(&tm1, pTs->tv_sec);

    return STime_GetIntDateFromTm(&tm1);
}


/**
 * 返回当前时间的整数表示(秒, HHMMSS)
 *
 * @param   pTs     当前时间
 * @return  int32 当前时间(秒), 格式为HHMMSS
 */
static __inline int32
STime_GetIntTimeFromTimespec(const STimespecT *pTs) {
    struct tm   tm1;

    SLOG_ASSERT(pTs);
    STime_GetTmBySeconds(&tm1, pTs->tv_sec);

    return STime_GetIntTimeFromTm(&tm1);
}


/**
 * 返回当前时间的整数表示(毫秒, HHMMSSsss)
 *
 * @param   pTs     当前时间
 * @return  int32 当前时间(毫秒), 格式为HHMMSSsss
 */
static __inline int32
STime_GetIntTimeMsFromTimespec(const STimespecT *pTs) {
    struct tm   tm1;

    SLOG_ASSERT(pTs);
    STime_GetTmBySeconds(&tm1, pTs->tv_sec);

    return STime_GetIntTimeFromTm(&tm1) * 1000
            + (int32) (pTs->tv_nsec / 1000000);
}


/**
 * 返回当前时间戳的整数表示(YYYYMMDDHHMMSSsss)
 *
 * @param   pTs     当前时间
 * @return  int64 当前时间, 格式为YYYYMMDDHHMMSSsss
 */
static __inline int64
STime_GetIntTimestampFromTimespec(const STimespecT *pTs) {
    struct tm   tm1;

    SLOG_ASSERT(pTs);
    STime_GetTmBySeconds(&tm1, pTs->tv_sec);

    return (int64) STime_GetIntDateFromTm(&tm1) * 1000000000
            + STime_GetIntTimeFromTm(&tm1) * 1000 + pTs->tv_nsec / 1000000;
}


/**
 * 输出当前时间戳的整数表示
 *
 * @param       pTs         当前时间
 * @param[out]  pOutDate    输出当前日期, 格式为YYYYMMDD
 * @param[out]  pOutTimeMs  输出当前时间(毫秒), 格式为HHMMSSsss
 */
static __inline void
STime_GetIntTimestampFromTimespec2(const STimespecT *pTs, int32 *pOutDate,
        int32 *pOutTimeMs) {
    struct tm   tm1;

    SLOG_ASSERT(pTs && pOutDate && pOutTimeMs);
    STime_GetTmBySeconds(&tm1, pTs->tv_sec);

    *pOutDate = STime_GetIntDateFromTm(&tm1);
    *pOutTimeMs = STime_GetIntTimeFromTm(&tm1) * 1000
            + (int32) (pTs->tv_nsec / 1000000);
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_TIMES_H */
