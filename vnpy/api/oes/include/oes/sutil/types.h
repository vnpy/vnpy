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
 * @file    types.h
 *
 * 公共类型定义
 *
 * @version $Id$
 * @since   2011/07/07
 */


#ifndef _SPK_TYPES_H
#define _SPK_TYPES_H


/* ===================================================================
 * 平台类型检测
 * =================================================================== */

#if defined (__LINUX__) || defined (__linux__) || defined (__KERNEL__) \
        || defined (_LINUX) || defined (LINUX)
#   ifndef  __LINUX__
#       define  __LINUX__               (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "LINUX"


#elif defined (__HPUX__) || defined (__hpux) || defined (__HPUX) \
        || defined (__hpux__) || defined (hpux) || defined (HPUX)
#   ifndef  __HPUX__
#       define  __HPUX__                (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "HPUX"


#elif defined (__AIX__) || defined (_AIX)
#   ifndef  __AIX__
#       define  __AIX__                 (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "AIX"


#elif defined (__SOLARIS__) || defined (__solaris__) || defined (__sun__) \
        || defined (__sun) || defined (sun)
#   ifndef  __SOLARIS__
#       define  __SOLARIS__             (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "SOLARIS"


#elif defined (__BSD__) || defined (__FreeBSD__) || defined (__OpenBSD__) \
        || defined (__NetBSD__)
#   ifndef  __BSD__
#       define  __BSD__                 (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "BSD"


#elif defined (__APPLE__) || defined (__MacOSX__) || defined (__MACOSX__)
#   ifndef  __APPLE__
#       define  __APPLE__               (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "APPLE"


#elif defined (__MINGW__) || defined (__MINGW32__) || defined (__MINGW64__) \
        || defined (_MINGW) || defined (MINGW)
#   ifndef  __MINGW__
#       define  __MINGW__               (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "MINGW"


#elif defined (__CYGWIN__) || defined (__CYGWIN32__) || defined (CYGWIN)
#   ifndef  __CYGWIN__
#       define  __CYGWIN__              (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "CYGWIN"


#elif defined (__WINDOWS__) || defined (_WIN32) || defined (_WIN64) \
        || defined (WIN32) || defined (__WIN32__) || defined (__Win32__) \
        || defined(__TOS_WIN__) || defined (_MSC_VER)
#   ifndef  __WINDOWS__
#       define  __WINDOWS__             (1)
#   endif
#   define  __SPK_PLATFORM_NAME__       "WINDOWS"


#else
#   pragma  message("Warning: Neither platform OS type detected!")

#endif
/* -------------------------           */


#if defined (HAVE_CONFIG_H) || defined (USE_GNULIB)
#   include <config.h>
#endif


#if defined (__WINDOWS__) || defined (__MINGW__)
#   if defined (SPK_WINVER) && SPK_WINVER >= 0x0400
#       undef   WINVER
#       undef   _WIN32_WINNT
#       define  WINVER                  SPK_WINVER
#       define  _WIN32_WINNT            WINVER
#   elif defined (__MINGW__) && (!defined (_WIN32_WINNT) || _WIN32_WINNT < 0x0600)
#       undef   WINVER
#       undef   _WIN32_WINNT
#       define  WINVER                  0x0600
#       define  _WIN32_WINNT            WINVER
#   endif

#   ifndef WIN32_LEAN_AND_MEAN
#       define  WIN32_LEAN_AND_MEAN

#       include <windows.h>
#       include <winsock2.h>
#       include <ws2tcpip.h>
#       include <winerror.h>

#       undef   WIN32_LEAN_AND_MEAN
#   else
#       include <windows.h>
#       include <winsock2.h>
#       include <ws2tcpip.h>
#       include <winerror.h>
#   endif
#endif


#include    <stdio.h>
#include    <limits.h>
#include    <errno.h>
#include    <fcntl.h>
#include    <time.h>


#if ! (defined (__WINDOWS__) || (defined (__MINGW__) && ! defined (USE_GNULIB)))
#   include <unistd.h>
#   include <sys/file.h>
#   include <sys/time.h>
#   include <sys/socket.h>
#   include <sys/select.h>

#   if ! defined (__MINGW__)
#       include <poll.h>
#   endif
#endif


#if defined (__LINUX__) || defined (__CYGWIN__) \
        || defined (__HPUX__) || defined (__AIX__) || defined (__SOLARIS__)
#   include <features.h>
#endif
/* -------------------------           */


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 平台相关的预编译宏设置
 * =================================================================== */

/*
 * 64位整型类型检测
 */
#if ! defined(__SPK_INT64_TYPE)
#   if defined (_WIN32) || defined (__WINDOWS__) || defined (__vms)
#       define  __SPK_INT64_TYPE        __int64
#   elif defined (__alpha)
#       define  __SPK_INT64_TYPE        long
#   else
#       define  __SPK_INT64_TYPE        long long
#   endif
#endif
/* -------------------------           */


/*
 * C99 features
 */
#if defined(_ISOC99_SOURCE) \
        || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
#   define  __SPK_STD_C99               (1)
#endif
/* -------------------------           */


/*
 * C89, C90, C94 features
 */
#if defined(__SPK_STD_C99)
#   define  __SPK_STD_C89               (1)
#   define  __SPK_STD_C90               (1)
#   define  __SPK_STD_C94               (1)
#else
#   if defined(__STDC__)
#       define  __SPK_STD_C89           (1)
#       if defined(__STDC_VERSION__)
#           define  __SPK_STD_C90       (1)
#           if (__STDC_VERSION__ >= 199409L)
#               define  __SPK_STD_C94   (1)
#           endif
#       endif
#   endif
#endif
/* -------------------------           */


/*
 * X/Open features
 */
#if defined(_XOPEN_SOURCE)

#   ifndef _XOPEN_VERSION
#       define  _XOPEN_VERSION          (_XOPEN_SOURCE)
#   endif

#   if defined(_XOPEN_UNIX) || defined(_XOPEN_SOURCE_EXTENDED)
#       define  __SPK_STD_UNIX95        (1)
#   endif

#   if _XOPEN_SOURCE >= 500 || _XOPEN_SOURCE >= 500
#       define  __SPK_STD_XOPEN_500     (1)
#       define  __SPK_STD_UNIX98        (1)
#   endif

#   if _XOPEN_SOURCE >= 600 || _XOPEN_SOURCE >= 600
#       define  __SPK_STD_XOPEN_600     (1)
#       define  __SPK_STD_UNIX03        (1)
#   endif

#   if _XOPEN_SOURCE >= 700 || _XOPEN_SOURCE >= 700
#       define  __SPK_STD_XOPEN_700     (1)
#       define  __SPK_STD_UNIX04        (1)
#   endif

#endif
/* -------------------------           */


/* ===================================================================
 * 数据类型定义
 * =================================================================== */

#if ! defined (SPK_HAVE_INTEGER_TYPES)
    typedef signed char                 int8;
    typedef unsigned char               uint8;

    typedef short                       int16;
    typedef unsigned short              uint16;

    typedef int                         int32;
    typedef unsigned int                uint32;

    typedef __SPK_INT64_TYPE            int64;
    typedef unsigned __SPK_INT64_TYPE   uint64;
#endif

#if ! defined (SPK_HAVE_FLOAT_TYPES)
    typedef float                       float32;
    typedef double                      float64;
    typedef long double                 float128;
#endif
/* -------------------------           */


/*
 * NULL 定义
 */
#if ! defined (NULL)
#   ifdef __cplusplus
#       define NULL                     (0L)
#   else
#       define NULL                     ((void*) 0)
#   endif
#endif
/* -------------------------           */


/*
 * BOOL 类型定义
 */
#if ! defined (BOOL) && ! defined (__WINDOWS__)
#   define BOOL                         int
#endif

#if ! defined (TRUE)
#   define TRUE                         (1)
#endif

#if ! defined (FALSE)
#   define FALSE                        (0)
#endif
/* -------------------------           */


/*
 * LLONG_MAX (为了在非C99环境下同样可用)
 */
#if ! defined (LLONG_MAX)
#   define LLONG_MAX                    (9223372036854775807LL)
#   define LLONG_MIN                    (-LLONG_MAX - 1LL)
#endif

#if ! defined (ULLONG_MAX)
#   define ULLONG_MAX                   (18446744073709551615ULL)
#endif
/* -------------------------           */


/* ===================================================================
 * ERRNO 定义
 * =================================================================== */

#if (defined (__WINDOWS__) || defined (__MINGW__)) && ! defined (__CYGWIN__)
#   ifndef ENOMSG
#       define  ENOMSG                  (122)
#   endif

#   ifndef EPROTO
#       define  EPROTO                  (134)
#   endif

#   ifndef EBADMSG
#       define  EBADMSG                 (104)
#   endif

#   ifndef ENOTSUP
#       define  ENOTSUP                 (129)
#   endif

#   ifndef ENETRESET
#       define  ENETRESET               (117)
#   endif

#   ifndef ECONNABORTED
#       define  ECONNABORTED            (106)
#   endif

#   ifndef ECANCELED
#       define  ECANCELED               (105)
#   endif

#   ifndef EINPROGRESS
#       define  EINPROGRESS             (112)
#       define  EALREADY                (103)
#       define  ENOTSOCK                (128)
#       define  EDESTADDRREQ            (109)
#       define  EMSGSIZE                (115)
#       define  EPROTOTYPE              (136)
#       define  ENOPROTOOPT             (123)
#       define  EPROTONOSUPPORT         (135)
#       define  EOPNOTSUPP              (130)
#       define  EAFNOSUPPORT            (102)
#       define  EADDRINUSE              (100)
#       define  EADDRNOTAVAIL           (101)
#       define  ENETDOWN                (116)
#       define  ENETUNREACH             (118)
#       define  ECONNRESET              (108)
#       define  ENOBUFS                 (119)
#       define  EISCONN                 (113)
#       define  ENOTCONN                (126)
#       define  ETIMEDOUT               (138)
#       define  ECONNREFUSED            (107)
#       define  ELOOP                   (114)
#       define  EHOSTUNREACH            (110)
#       define  EWOULDBLOCK             (140)
#   endif

#   ifndef ETXTBSY
#       define  ETXTBSY                 (139)
#       define  ENODATA                 (120)
#       define  ENOSR                   (124)
#       define  ENOSTR                  (125)
#       define  ETIME                   (137)
#       define  EOTHER                  (131)
#   endif
#endif


#ifndef EAGAIN
#   if defined(EWOULDBLOCK)
#       define  EAGAIN                  (EWOULDBLOCK)
#   endif
#endif

#ifndef EFTYPE
#   define  EFTYPE                      (EBADF)
#endif

#ifndef EBADMSG
#   define  EBADMSG                     (EINVAL)
#endif

#ifndef ENODATA
#   define  ENODATA                     (ESRCH)
#endif

#ifndef ETIMEDOUT
#   if defined(__WINDOWS__) || defined(__MINGW__)
#       define  ETIMEDOUT               (138)
#   else
#       define  ETIMEDOUT               (110)
#   endif
#endif

#ifndef ENOTCONN
#   define  ENOTCONN                    (EPIPE)
#endif

#ifndef ECONNRESET
#   define  ECONNRESET                  (EPIPE)
#endif

#if ! defined(ENOSYS) && ! defined(ENOTSUP)
#   define  ENOSYS                      (ENODEV)
#   define  ENOTSUP                     (ENODEV)
#elif ! defined(ENOSYS)
#   define  ENOSYS                      (ENOTSUP)
#elif ! defined(ENOTSUP)
#   define  ENOTSUP                     (ENOSYS)
#endif
/* -------------------------           */


/* ===================================================================
 * 为兼容多平台而做的类型定义
 * =================================================================== */

#if defined (__WINDOWS__) || defined (__MINGW__)
    /* socket handle */
#   define  SPK_SOCKET                  SOCKET

#   ifndef  _SPK_STRUCT_TIMEVAL
#       define  _SPK_STRUCT_TIMEVAL     struct timeval
#       define  STimevalT               _SPK_STRUCT_TIMEVAL
#   endif   /* _SPK_STRUCT_TIMEVAL */

#   if defined (_M_X64) || defined (_M_IA64)
        /* Defined for x64 / Itanium Processor Family 64-bit processors */
#       define  __SPK_TIMEVAL_TIME_T    time_t
#   elif defined (_M_IX86)
        /* Defined for x86 processors */
#       define  __SPK_TIMEVAL_TIME_T    long
#   else
        /* 如果需要使用 VS2010 编译 32 位应用, 需要指定预编译宏: _USE_32BIT_TIME_T */
#       define  __SPK_TIMEVAL_TIME_T    time_t
#   endif

#   ifndef  _SPK_STRUCT_TIMESPEC
#   if defined (__MINGW__)
#       define  _SPK_STRUCT_TIMESPEC    struct timespec
#       define  STimespecT              _SPK_STRUCT_TIMESPEC
#   else
#       define  _SPK_STRUCT_TIMESPEC    struct _spk_struct_timespec
        _SPK_STRUCT_TIMESPEC {
            __SPK_TIMEVAL_TIME_T        tv_sec;
            __SPK_TIMEVAL_TIME_T        tv_nsec;
        };
#       define  STimespecT              _SPK_STRUCT_TIMESPEC
#   endif
#   endif   /* _SPK_STRUCT_TIMESPEC */

#   ifndef  _SPK_STRUCT_TIMEZONE
#       define  _SPK_STRUCT_TIMEZONE    struct _spk_struct_timezone
        _SPK_STRUCT_TIMEZONE {
            int         tz_minuteswest; /* minutes west of Greenwich */
            int         tz_dsttime;     /* type of dst correction */
        };
#       define  STimezoneT              _SPK_STRUCT_TIMEZONE
#   endif   /* _SPK_STRUCT_TIMEZONE */

#   ifndef  _SPK_STRUCT_IOVEC
#       define  _SPK_STRUCT_IOVEC       struct _spk_struct_iovec
        _SPK_STRUCT_IOVEC {
            void *      iov_base;       /* [XSI] Base address of I/O memory region */
            size_t      iov_len;        /* [XSI] Size of region iov_base points to */
        };
#       define  SIovecT                 _SPK_STRUCT_IOVEC
#   endif   /* _SPK_STRUCT_IOVEC */

#   ifndef  _SPK_STRUCT_POLLFD
#   if defined (_WIN32_WINNT) && _WIN32_WINNT >= 0x0600
#       define  _SPK_STRUCT_POLLFD      struct pollfd
#       define  SPollfdT                _SPK_STRUCT_POLLFD
#   else
#       define  _SPK_STRUCT_POLLFD      struct _spk_struct_pollfd
        _SPK_STRUCT_POLLFD {
            SOCKET      fd;
            short       events;
            short       revents;
        };
#       define  SPollfdT                _SPK_STRUCT_POLLFD
#   endif
#   endif   /* _SPK_STRUCT_POLLFD */


#else
    /* socket handle */
#   define  SPK_SOCKET                  int32

#   ifndef  _SPK_STRUCT_TIMEVAL
#       define  _SPK_STRUCT_TIMEVAL     struct timeval
#       define  STimevalT               _SPK_STRUCT_TIMEVAL
#   endif   /* _SPK_STRUCT_TIMEVAL */

#   ifndef  _SPK_STRUCT_TIMESPEC
#       define  _SPK_STRUCT_TIMESPEC    struct timespec
#       define  STimespecT              _SPK_STRUCT_TIMESPEC
#   endif   /* _SPK_STRUCT_TIMESPEC */

#   ifndef  _SPK_STRUCT_TIMEZONE
#       define  _SPK_STRUCT_TIMEZONE    struct timezone
#       define  STimezoneT              _SPK_STRUCT_TIMEZONE
#   endif   /* _SPK_STRUCT_TIMEZONE */

#   ifndef  _SPK_STRUCT_IOVEC
#       define  _SPK_STRUCT_IOVEC       struct iovec
#       define  SIovecT                 _SPK_STRUCT_IOVEC
#   endif   /* _SPK_STRUCT_IOVEC */

#   ifndef  _SPK_STRUCT_POLLFD
#       define  _SPK_STRUCT_POLLFD      struct pollfd
#       define  SPollfdT                _SPK_STRUCT_POLLFD
#   endif   /* _SPK_STRUCT_POLLFD */

#endif
/* -------------------------           */


/*
 * timeval_32
 */
#ifndef _SPK_STRUCT_TIMEVAL32
#   define  _SPK_STRUCT_TIMEVAL32       struct _spk_struct_timeval32
    _SPK_STRUCT_TIMEVAL32
    {
        int32                           tv_sec;         /* seconds */
        int32                           tv_usec;        /* and microseconds */
    };

    typedef _SPK_STRUCT_TIMEVAL32       STimeval32T;
#endif      /* _SPK_STRUCT_TIMEVAL32 */


#ifndef _SPK_STRUCT_TIMESPEC32
#   define  _SPK_STRUCT_TIMESPEC32      struct _spk_struct_timespec32
    _SPK_STRUCT_TIMESPEC32
    {
        int32                           tv_sec;         /* seconds */
        int32                           tv_nsec;        /* and nanoseconds */
    };

    typedef _SPK_STRUCT_TIMESPEC32      STimespec32T;
#endif      /* _SPK_STRUCT_TIMEVAL32 */
/* -------------------------           */


/*
 * timeval_64
 */
#ifndef _SPK_STRUCT_TIMEVAL64
#   define  _SPK_STRUCT_TIMEVAL64       struct _spk_struct_timeval64
    _SPK_STRUCT_TIMEVAL64
    {
        int64                           tv_sec;         /* seconds */
        int64                           tv_usec;        /* and microseconds */
    };

    typedef _SPK_STRUCT_TIMEVAL64       STimeval64T;
#endif      /* _SPK_STRUCT_TIMEVAL64 */


#ifndef _SPK_STRUCT_TIMESPEC64
#   define  _SPK_STRUCT_TIMESPEC64      struct _spk_struct_timespec64
    _SPK_STRUCT_TIMESPEC64
    {
        int64                           tv_sec;         /* seconds */
        int64                           tv_nsec;        /* and nanoseconds */
    };

    typedef _SPK_STRUCT_TIMESPEC64      STimespec64T;
#endif      /* _SPK_STRUCT_TIMESPEC64 */
/* -------------------------           */


/* ===================================================================
 * 用于CPU缓存行填充的宏定义
 * =================================================================== */

/* CPU缓存行大小 */
#ifndef SPK_CACHE_LINE_SIZE
#   define  SPK_CACHE_LINE_SIZE         (64)
#endif

#if ! defined(NO_CACHE_LINE_PADDING)
/* 声明CPU缓存行填充字段的宏定义 */
#   define  __SPK_CACHE_LINE_PADDING(VARNAME)           \
            int64   __##VARNAME##_1; \
            int64   __##VARNAME##_2; \
            int64   __##VARNAME##_3; \
            int64   __##VARNAME##_4; \
            int64   __##VARNAME##_5; \
            int64   __##VARNAME##_6; \
            int64   __##VARNAME##_7

/* CPU缓存行填充字段的初始值定义 */
#   define  __NULLOBJ_SPK_CACHE_LINE_PADDING            \
            0, 0, 0, 0, 0, 0, 0,

#   define  __NULLOBJ_SPK_CACHE_LINE_PADDING2           \
            , 0, 0, 0, 0, 0, 0, 0

#else
#   define  __SPK_CACHE_LINE_PADDING(VARNAME)

#   define  __NULLOBJ_SPK_CACHE_LINE_PADDING

#   define  __NULLOBJ_SPK_CACHE_LINE_PADDING2

#endif
/* -------------------------           */


/* ===================================================================
 * DLL_IMPORT & DLL_EXPORT
 * =================================================================== */

#if ! defined(__SPK_DLL_IMPORT)
#   if defined(__WINDOWS__)
#       define __SPK_DLL_IMPORT         __declspec(dllimport)
#       define __SPK_DLL_EXPORT         __declspec(dllexport)
#       define __SPK_DLL_LOCAL
#   elif defined(__MINGW__)
#       define __SPK_DLL_IMPORT
#       define __SPK_DLL_EXPORT
#       define __SPK_DLL_LOCAL
#   elif (__GNUC__ >= 4) && 0
#       define __SPK_DLL_IMPORT         __attribute__ ((visibility ("default")))
#       define __SPK_DLL_EXPORT         __attribute__ ((visibility ("default")))
#       define __SPK_DLL_LOCAL          __attribute__ ((visibility ("hidden")))
#   else
#       define __SPK_DLL_IMPORT
#       define __SPK_DLL_EXPORT
#       define __SPK_DLL_LOCAL
#   endif
#endif
/* -------------------------           */


/* ===================================================================
 * 常用缓存区长度定义
 * =================================================================== */

/* FD_SETSIZE */
#ifndef __SPK_FD_SETSIZE
#   ifdef FD_SETSIZE
#       define __SPK_FD_SETSIZE         FD_SETSIZE
#   else
#       define __SPK_FD_SETSIZE         (1024)
#   endif
#endif

/* 最大文本块长度 */
#ifndef SPK_MAX_BLOCK_SIZE
#   define SPK_MAX_BLOCK_SIZE           (8192)
#endif

/* 最大单行文本长度 */
#ifndef SPK_MAX_LINE_SIZE
#   define SPK_MAX_LINE_SIZE            (1024)
#endif

/* 最大路径长度 */
#ifndef SPK_MAX_PATH_LEN
#   define SPK_MAX_PATH_LEN             (256)
#   define SPK_MAX_PATH_LEN_LONG        (512)
#   define SPK_MAX_PATH_LEN_SHORT       (128)
#endif
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_TYPES_H */
