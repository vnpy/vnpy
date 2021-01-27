/** @file
* @brief   平台相关定义和基本头文件
* @author  何仲君
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20120106 初始版本
* @date    20140402 为了更好的与其他头文件共处而调整，增加OS_COMMON_EXT
*/

#ifndef _OS_COMMON_H_
#define _OS_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_AIX) && !defined(OS_AIX)
#define OS_AIX
#endif

#if defined(__hpux) && !defined(OS_HPUX)
#define OS_HPUX
#endif

#if defined(__SVR4) && !defined(OS_SOLARIS)
#define OS_SOLARIS
#endif

#if defined(__FreeBSD__) && !defined(OS_FREEBSD)
#define OS_FREEBSD
#endif

#if defined(__linux) && !defined(OS_LINUX)
#define OS_LINUX
#endif

#if (defined(_WIN32) || defined(_WIN64)) && !defined(OS_WIN)
#define OS_WIN
#endif

#if !defined(OS_WIN) && !defined(OS_LINUX) && !defined(OS_UNIX)
#define OS_UNIX
#endif

#ifdef OS_WIN
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

typedef unsigned long in_addr_t;

#pragma warning(disable: 4996)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#if defined(_MSC_VER) && (_MSC_VER < 1700) // < VS 2012
#if _MSC_VER < 1300
typedef signed char			int8_t;
typedef signed short		int16_t;
typedef signed int			int32_t;
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
#else
typedef signed __int8		int8_t;
typedef signed __int16		int16_t;
typedef signed __int32		int32_t;
typedef unsigned __int8		uint8_t;
typedef unsigned __int16	uint16_t;
typedef unsigned __int32	uint32_t;
#endif
typedef signed __int64		int64_t;
typedef unsigned __int64	uint64_t;

#if defined(_WIN64)
#define __PRI64_PREFIX		"l"
#else
#if _MSC_VER < 1300
#define __PRI64_PREFIX		"I64"
#else
#define __PRI64_PREFIX		"ll"
#endif
#endif

/* Macros for printing format specifiers.  */

/* Decimal notation.  */
# define PRId8          "d"
# define PRId16         "d"
# define PRId32         "d"
# define PRId64         __PRI64_PREFIX "d"

/* Unsigned integers.  */
# define PRIu8          "u"
# define PRIu16         "u"
# define PRIu32         "u"
# define PRIu64         __PRI64_PREFIX "u"

/* lowercase hexadecimal notation.  */
# define PRIx8          "x"
# define PRIx16         "x"
# define PRIx32         "x"
# define PRIx64         __PRI64_PREFIX "x"

# define PRIX8          "X"
# define PRIX16         "X"
# define PRIX32         "X"
# define PRIX64         __PRI64_PREFIX "X"
#else
#include <stdint.h>
//#include <inttypes.h>
#endif


#ifndef EXPORT
#define EXPORT				__declspec(dllexport)
#endif

#else // !OS_WIN

// 应最早包含本文件，或者把_FILE_OFFSET_BITS定义放在编译参数中，如g++ -D_FILE_OFFSET_BITS=64
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS	64
#elif _FILE_OFFSET_BITS != 64
#error "_FILE_OFFSET_BITS != 64"
#endif

#ifndef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE
#endif

#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <inttypes.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <dlfcn.h>
#include <dirent.h>
#include <fnmatch.h>
#include <assert.h>


#endif

#ifdef OS_COMMON_EXT

#ifdef OS_WIN

#ifndef lseek64
#define	lseek64				_lseeki64			
#endif

// 有细节差异的（_snprintf不能保证0结尾），要小心使用
#ifndef snprintf
#define snprintf			_snprintf
#endif

#else

#ifndef O_BINARY
#define O_BINARY			0
#endif

#ifndef O_TEXT
#define O_TEXT				0
#endif

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE    -1
#endif

#ifndef SOCKET
typedef int SOCKET;
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET		(SOCKET)(~0)
#endif

#ifndef closesocket
#define closesocket			close
#endif

#endif

#ifndef O_SYNC
#define O_SYNC				0
#endif

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL		0
#endif

#ifndef MAX_PATH
#define MAX_PATH			260
#endif

#ifndef NEW
#define NEW new(std::nothrow)
#endif


#endif // OS_COMMON_EXT

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <new>
#endif

#endif // _OS_COMMON_H_
