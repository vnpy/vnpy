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
 * @file    spk_platforms.h
 *
 * 涉及跨平台兼容处理的函数定义
 *
 * @version 1.0 2017/08/10
 * @since   2017/08/10
 */


#ifndef _SPK_PLATFORMS_H
#define _SPK_PLATFORMS_H


#include    <sutil/types.h>


/* ===================================================================
 * 标准库头文件
 * =================================================================== */

#include    <stdio.h>
#include    <stdlib.h>
#include    <stddef.h>
#include    <ctype.h>
#include    <limits.h>
#include    <signal.h>
#include    <errno.h>
#include    <assert.h>
#include    <fcntl.h>
#include    <time.h>

#include    <stdarg.h>
#include    <string.h>
#include    <memory.h>
#include    <setjmp.h>
#include    <sys/types.h>
#include    <sys/stat.h>
/* -------------------------           */


/*
 * 平台特定的头文件
 */
#if ! (defined (__WINDOWS__) || (defined (__MINGW__) && ! defined (USE_GNULIB)))
#   include <unistd.h>
#   include <sys/file.h>
#   include <sys/time.h>
#   include <sys/socket.h>
#   include <sys/select.h>
#   include <sys/ioctl.h>
#   include <sys/wait.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#   include <netdb.h>
#   include <pthread.h>

#   if ! defined (__MINGW__)
#       include <sys/un.h>
#       include <sys/ipc.h>
#       include <sys/sem.h>
#       include <sys/shm.h>
#       include <sys/mman.h>
#       include <netinet/tcp.h>
#       include <poll.h>
#   else
#       include <sys/uio.h>
#       include "fatal-signal.h"
#       include "nonblocking.h"
#       include "sockets.h"
#   endif
#endif


#if defined (__LINUX__) || defined (__CYGWIN__) || defined (__MINGW__) \
        || defined (__HPUX__) || defined (__AIX__) || defined (__SOLARIS__)
#   include <malloc.h>
#endif


#if defined (__BSD__) || defined (__APPLE__) || defined (__LINUX__)
#   include <sys/uio.h>
#endif


#if defined (__SOLARIS__)
#   include <sys/sockio.h>
#endif


#if defined (__WINDOWS__) || defined (__MINGW__)
#   include <io.h>
#   include <sys/timeb.h>

#   if defined (_MSC_VER) && _MSC_VER >= 1400
#       include <intrin.h>
#   endif
#endif
/* -------------------------           */


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 跨平台兼容性处理
 * =================================================================== */

/* snprintf */
#if (defined (__WINDOWS__) || defined (__MINGW__)) \
        && (!defined (__cplusplus) || (defined(_MSC_VER) && _MSC_VER <= 1800))
#   define  snprintf                        _snprintf
#   define  __SPK_FMT_LL__                  "I64"
#   define  __SPK_FMT_HH__                  ""
#   define  __SPK_FMT_SHORT__               ""


#else
#   define  __SPK_FMT_LL__                  "ll"
#   define  __SPK_FMT_HH__                  "hh"
#   define  __SPK_FMT_SHORT__               "h"

#endif
/* -------------------------           */


/* ===================================================================
 * 涉及跨平台兼容的错误号处理
 * =================================================================== */

/*
 * 判断errno是否是 EAGAIN / EWOULDBLOCK
 * 用于非阻塞I/O
 */
#if defined(EAGAIN) && defined(EWOULDBLOCK) && (EWOULDBLOCK != EAGAIN)
#   define  _SPK_IS_ERRNO_EAGAIN(e)         ((e) == EAGAIN || (e) == EWOULDBLOCK)
#elif defined(EAGAIN)
#   define  _SPK_IS_ERRNO_EAGAIN(e)         ((e) == EAGAIN)
#elif defined(EWOULDBLOCK)
#   define  _SPK_IS_ERRNO_EAGAIN(e)         ((e) == EWOULDBLOCK)
#else
#   error   "Neither EAGAIN nor EWOULDBLOCK is defined!"
#endif
/* -------------------------           */


/*
 * 判断errno是否是 ECONNABORTED
 * 用于非阻塞accept
 */
#if defined(ECONNABORTED)
#   define  _SPK_IS_ERRNO_ECONNABORTED(e)   ((e) == ECONNABORTED)
#else
#   define  _SPK_IS_ERRNO_ECONNABORTED(e)   (0)
#endif
/* -------------------------           */


/*
 * 判断errno是否是 EPROTO
 * 用于非阻塞accept
 */
#if defined(EPROTO)
#   define  _SPK_IS_ERRNO_EPROTO(e)         ((e) == EPROTO)
#else
#   define  _SPK_IS_ERRNO_EPROTO(e)         (0)
#endif
/* -------------------------           */


#if defined (__WINDOWS__)

#   define SPK_GET_ERRNO()                  (__SPlatform_GetErrno())
#   define SPK_GET_NEG_ERRNO()              (__SPlatform_GetNegErrno())
#   define SPK_SET_ERRNO(e)                 (__SPlatform_SetErrno((e)))

#   define SPK_IS_EAGAIN(e)                 (__SPlatform_IsErrEagain((e)))
#   define SPK_IS_ECONNABORTED(e)           (__SPlatform_IsErrEconnaborted((e)))
#   define SPK_IS_EPROTO(e)                 (__SPlatform_IsErrEproto((e)))
#   define SPK_IS_ETIMEDOUT(e)              (__SPlatform_IsErrEtimeout((e)))
#   define SPK_IS_EPIPE(e)                  (__SPlatform_IsErrEpipe((e)))
#   define SPK_IS_EINTR(e)                  (__SPlatform_IsErrEintr((e)))
#   define SPK_IS_EBADMSG(e)                (__SPlatform_IsErrEbadmsg((e)))
#   define SPK_IS_EINVAL(e)                 (__SPlatform_IsErrEinval((e)))
#   define SPK_IS_ERANGE(e)                 (__SPlatform_IsErrErange((e)))
#   define SPK_IS_ENOSPC(e)                 (__SPlatform_IsErrEnospc((e)))
#   define SPK_IS_ENOENT(e)                 (__SPlatform_IsErrEnoent((e)))
#   define SPK_IS_ENODATA(e)                (__SPlatform_IsErrEnodata((e)))
#   define SPK_IS_EEXIST(e)                 (__SPlatform_IsErrEexist((e)))

#   define SPK_IS_NEG_EAGAIN(e)             (__SPlatform_IsNegEagain((e)))
#   define SPK_IS_NEG_ECONNABORTED(e)       (__SPlatform_IsNegEconnaborted((e)))
#   define SPK_IS_NEG_EPROTO(e)             (__SPlatform_IsNegEproto((e)))
#   define SPK_IS_NEG_ETIMEDOUT(e)          (__SPlatform_IsNegEtimeout((e)))
#   define SPK_IS_NEG_EPIPE(e)              (__SPlatform_IsNegEpipe((e)))
#   define SPK_IS_NEG_EINTR(e)              (__SPlatform_IsNegEintr((e)))
#   define SPK_IS_NEG_EBADMSG(e)            (__SPlatform_IsNegEbadmsg((e)))
#   define SPK_IS_NEG_EINVAL(e)             (__SPlatform_IsNegEinval((e)))
#   define SPK_IS_NEG_ERANGE(e)             (__SPlatform_IsNegErange((e)))
#   define SPK_IS_NEG_ENOSPC(e)             (__SPlatform_IsNegEnospc((e)))
#   define SPK_IS_NEG_ENOENT(e)             (__SPlatform_IsNegEnoent((e)))
#   define SPK_IS_NEG_ENODATA(e)            (__SPlatform_IsNegEnodata((e)))
#   define SPK_IS_NEG_EEXIST(e)             (__SPlatform_IsNegEexist((e)))

#else

#   define SPK_GET_ERRNO()                  (errno)
#   define SPK_GET_NEG_ERRNO()              ((errno) > 0 ? -(errno) : (errno))
#   define SPK_SET_ERRNO(e)                 (errno = (e))

#   define SPK_IS_EAGAIN(e)                 (_SPK_IS_ERRNO_EAGAIN(e))
#   define SPK_IS_ECONNABORTED(e)           (_SPK_IS_ERRNO_ECONNABORTED(e))
#   define SPK_IS_EPROTO(e)                 (_SPK_IS_ERRNO_EPROTO(e))
#   define SPK_IS_ETIMEDOUT(e)              ((e) == ETIMEDOUT)
#   define SPK_IS_EPIPE(e)                  ((e) == EPIPE)
#   define SPK_IS_EINTR(e)                  ((e) == EINTR)
#   define SPK_IS_EBADMSG(e)                ((e) == EBADMSG)
#   define SPK_IS_EINVAL(e)                 ((e) == EINVAL)
#   define SPK_IS_ERANGE(e)                 ((e) == ERANGE)
#   define SPK_IS_ENOSPC(e)                 ((e) == ENOSPC)
#   define SPK_IS_ENOENT(e)                 ((e) == ENOENT)
#   define SPK_IS_ENODATA(e)                ((e) == ENODATA)
#   define SPK_IS_EEXIST(e)                 ((e) == EEXIST)

#   define SPK_IS_NEG_EAGAIN(e)             (_SPK_IS_ERRNO_EAGAIN(-(e)))
#   define SPK_IS_NEG_ECONNABORTED(e)       (_SPK_IS_ERRNO_ECONNABORTED(-(e)))
#   define SPK_IS_NEG_EPROTO(e)             (_SPK_IS_ERRNO_EPROTO(-(e)))
#   define SPK_IS_NEG_ETIMEDOUT(e)          ((e) == -(ETIMEDOUT))
#   define SPK_IS_NEG_EPIPE(e)              ((e) == -(EPIPE))
#   define SPK_IS_NEG_EINTR(e)              ((e) == -(EINTR))
#   define SPK_IS_NEG_EBADMSG(e)            ((e) == -(EBADMSG))
#   define SPK_IS_NEG_EINVAL(e)             ((e) == -(EINVAL))
#   define SPK_IS_NEG_ERANGE(e)             ((e) == -(ERANGE))
#   define SPK_IS_NEG_ENOSPC(e)             ((e) == -(ENOSPC))
#   define SPK_IS_NEG_ENOENT(e)             ((e) == -(ENOENT))
#   define SPK_IS_NEG_ENODATA(e)            ((e) == -(ENODATA))
#   define SPK_IS_NEG_EEXIST(e)             ((e) == -(EEXIST))

#endif


#define SPK_IS_ERRNO_EAGAIN()               (SPK_IS_EAGAIN(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_ECONNABORTED()         (SPK_IS_ECONNABORTED(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_EPROTO()               (SPK_IS_EPROTO(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_ETIMEDOUT()            (SPK_IS_ETIMEDOUT(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_EPIPE()                (SPK_IS_EPIPE(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_EINTR()                (SPK_IS_EINTR(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_EBADMSG()              (SPK_IS_EBADMSG(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_EINVAL()               (SPK_IS_EINVAL(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_ERANGE()               (SPK_IS_ERANGE(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_ENOSPC()               (SPK_IS_ENOSPC(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_ENOENT()               (SPK_IS_ENOENT(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_ENODATA()              (SPK_IS_ENODATA(SPK_GET_ERRNO()))
#define SPK_IS_ERRNO_EEXIST()               (SPK_IS_EEXIST(SPK_GET_ERRNO()))
/* -------------------------           */


/* ===================================================================
 * 函数声明
 * =================================================================== */

/* 返回错误号 errno */
int32       __SPlatform_GetErrno(void);

/* 返回负的错误号 */
int32       __SPlatform_GetNegErrno(void);

/* 设置错误号 errno */
void        __SPlatform_SetErrno(int32 err);

/* 返回错误号是否是 EAGAIN */
BOOL        __SPlatform_IsErrEagain(int32 err);
/* 返回错误号是否是 ECONNABORTED */
BOOL        __SPlatform_IsErrEconnaborted(int32 err);
/* 返回错误号是否是 EPROTO */
BOOL        __SPlatform_IsErrEproto(int32 err);
/* 返回错误号是否是 ETIMEDOUT */
BOOL        __SPlatform_IsErrEtimeout(int32 err);
/* 返回错误号是否是 EPIPE */
BOOL        __SPlatform_IsErrEpipe(int32 err);
/* 返回错误号是否是 EINTR */
BOOL        __SPlatform_IsErrEintr(int32 err);
/* 返回错误号是否是 EBADMSG */
BOOL        __SPlatform_IsErrEbadmsg(int32 err);
/* 返回错误号是否是 EINVAL */
BOOL        __SPlatform_IsErrEinval(int32 err);
/* 返回错误号是否是 ERANGE */
BOOL        __SPlatform_IsErrErange(int32 err);
/* 返回错误号是否是 ENOSPC */
BOOL        __SPlatform_IsErrEnospc(int32 err);
/* 返回错误号是否是 ENOENT */
BOOL        __SPlatform_IsErrEnoent(int32 err);
/* 返回错误号是否是 ENODATA */
BOOL        __SPlatform_IsErrEnodata(int32 err);
/* 返回错误号是否是 EEXIST */
BOOL        __SPlatform_IsErrEexist(int32 err);

/* 返回错误号是否是负的 EAGAIN */
BOOL        __SPlatform_IsNegEagain(int32 err);
/* 返回错误号是否是负的 ECONNABORTED */
BOOL        __SPlatform_IsNegEconnaborted(int32 err);
/* 返回错误号是否是负的 EPROTO */
BOOL        __SPlatform_IsNegEproto(int32 err);
/* 返回错误号是否是负的 ETIMEDOUT */
BOOL        __SPlatform_IsNegEtimeout(int32 err);
/* 返回错误号是否是负的 EPIPE */
BOOL        __SPlatform_IsNegEpipe(int32 err);
/* 返回错误号是否是负的 EINTR */
BOOL        __SPlatform_IsNegEintr(int32 err);
/* 返回错误号是否是负的 EBADMSG */
BOOL        __SPlatform_IsNegEbadmsg(int32 err);
/* 返回错误号是否是负的 EINVAL */
BOOL        __SPlatform_IsNegEinval(int32 err);
/* 返回错误号是否是负的 ERANGE */
BOOL        __SPlatform_IsNegErange(int32 err);
/* 返回错误号是否是负的 ENOSPC */
BOOL        __SPlatform_IsNegEnospc(int32 err);
/* 返回错误号是否是负的 ENOENT */
BOOL        __SPlatform_IsNegEnoent(int32 err);
/* 返回错误号是否是负的 ENODATA */
BOOL        __SPlatform_IsNegEnodata(int32 err);
/* 返回错误号是否是负的 EEXIST */
BOOL        __SPlatform_IsNegEexist(int32 err);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_PLATFORMS_H */
