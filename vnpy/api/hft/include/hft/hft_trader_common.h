/**
 * @file    hft_trader_common.h
 * @brief   公共类型和数据定义
 */

#ifndef _HFT_TRADER_COMMON_H_
#define _HFT_TRADER_COMMON_H_

#ifdef _WIN32
#ifdef HFTSDK_EXPORTS
#define HFT_TRADER_EXPORT __declspec(dllexport)
#else
#define HFT_TRADER_EXPORT __declspec(dllimport)
#endif
#else
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define HFT_TRADER_EXPORT __global
#elif (defined(__GNUC__) && __GNUC__ >= 4) || defined(__INTEL_COMPILER)
#define HFT_TRADER_EXPORT __attribute__((visibility("default")))
#else
#define HFT_TRADER_EXPORT
#endif
#endif

#if defined(__osf__)
#include <inttypes.h>
#elif _MSC_VER && _MSC_VER < 1600
#ifndef int8_t
typedef signed char int8_t;
#endif
#ifndef int16_t
typedef short int16_t;
#endif
#ifndef int32_t
typedef int int32_t;
#endif
#ifndef int64_t
typedef long long int64_t;
#endif
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned short uint16_t;
#endif
#ifndef uint32_t
typedef unsigned int uint32_t;
#endif
#ifndef uint64_t
typedef unsigned long long uint64_t;
#endif
#else
#include <stdint.h>
#endif  // _MSC_VER

#ifdef SWIG
#undef HFT_TRADER_EXPORT
#define HFT_TRADER_EXPORT
#endif

namespace HFT {

// 委托号长度，保存最多31个字符
const int LEN_ID = 32;
// 系统标识ID长度，保存最多39个字符
const int LEN_SYS_ID = 40;
// 交易市场+证券代码长度，保存最多31个字符
const int LEN_SYMBOL = 32;
// 证券名字长度
const int LEN_SYMBOL_NAME = 64;
// 错误消息长度，保存最多255个字符
const int LEN_ERR_MSG = 256;
// IP地址长度，保存最多39个字符
const int LEN_IP_ADDR = 40;
// 客户代码+资金账户,保存最多18个字符
const int LEN_CUST_ID = 19;
// 客户密码，保存最多64个字符
const int LEN_PASSWORD = 65;
// 一户通号码+委托编号，保存最多32个字符
const int LEN_ACCOUNT_ID = 33;
// 一户通加密标识，保存最多2个字符
const int LEN_CIF_TYPE = 3;
// 终端信息长度，保存最多256个字符
const int LEN_TERM_INFO = 257;
// 股东代码长度，保存最多20个字符
const int LEN_SECU_ID = 21;
// 股票代码长度，保存最多20个字符
const int LEN_STK_CODE = 21;
// 币种代码长度，保存最多3个字符
const int LEN_MONY_TYPE = 4;
// 机构代码+机构分支长度，保存最多4个字符
const int LEN_ORG_ID = 5;
// 委托席位长度，保存最多16个字符
const int LEN_SEAT = 17;
// 内部代码长度，保存最多12个字符
const int LEN_TA_CODE = 13;
// 备注长度，保存最多512个字符
const int LEN_REMARK = 513;
// 备注长度，保存最多128个字符
const int LEN_REMARK1 = 129;
// 市场长度，保存最多7个字符
const int LEN_MARKET = 8;

// 响应的错误消息
struct ErrorInfo {
    int32_t err_code;           // 错误码
    char err_msg[LEN_ERR_MSG];  // 错误消息，Windows是GBK，Linux是UTF8

    ErrorInfo() : err_code(0) {
        err_msg[0] = 0;
    }
};

// IP和端口信息
struct IpAddr {
    char ip[LEN_IP_ADDR];       // ip地址
    int port;                   // 端口

    IpAddr() : port(0) {
        ip[0] = 0;
    }
};

// 日志级别
enum LogLevel {
    LogLevel_Debug,     // 调试级别
    LogLevel_Info,      // 信息级别
    LogLevel_Warn,      // 警告级别
    LogLevel_Error,     // 错误级别
    LogLevel_Critical,  // 致命级别
};

}   // namespace HFT

#endif  // _HFT_TRADER_COMMON_H_
