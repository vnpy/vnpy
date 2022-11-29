/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_monitor_guest_api.h
///@brief 定义Monitor用户接口
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_MONITOR_GUEST_API_H_
#define _XTP_MONITOR_GUEST_API_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xtp_monitor_api_struct_common.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MONITOR_GUEST_API_EXPORT
#define MONITOR_GUEST_API_EXPORT __declspec(dllexport)
#else
#define MONITOR_GUEST_API_EXPORT __declspec(dllimport)
#endif
#else
#define MONITOR_GUEST_API_EXPORT 
#endif

#ifdef __cplusplus
extern "C" {
#endif

	///是否允许监控客户端登录的回调函数
	///@param username 监控客户端登录的用户名
	///@param password 监控客户端登录的密码经过MD5加密后的字串
	///@param mac_add 监控客户端登录的mac地址
	///@param ip 监控客户端登录的ip
	///@return 允许登录返回0，否则返回错误码
	typedef int32_t(*MonitorClientLoginFunc)(const char* username, const char* password, const char* mac_add, const char* ip);

	///启动策略的回调函数
	///@return 启动成功返回0，否则返回错误码
	typedef int32_t(*StartFunc)();

	///停止策略的回调函数
	///@return 停止成功返回0，否则返回错误码
	typedef int32_t(*StopFunc)();

	///断线通知的回调函数，当Monitor Guest从Monitor Server 断开后，此函数会被调用
	typedef void(*DisconnectedFunc)();

	///设置key所对应值的回调函数
	///@param key 需要设置的索引关键字
	///@param value 对应索引关键字key所需要设置的值
	///@return 设置成功返回0，否则返回错误码，xtp monitor的默认错误码：1-guest程序已断开，2-key过长，超限，3-value过长，超限。请用户自行设定非默认错误码的错误码
	typedef int32_t(*MonitorClientSetParameterFunc)(const char* key, const char* value);

	///注册验证监控账户登录的回调函数
	///@return 注册是否成功，成功返回true，失败返回false，此时可以通过GetApiLastError()获取失败原因
	///@param func 检查监控账户是否允许登录的验证函数的函数指针，需要用户自己实现
	MONITOR_GUEST_API_EXPORT bool RegisterMonitorClientLoginFunc(MonitorClientLoginFunc func);

	///注册启动策略的回调函数
	///@return 注册是否成功，成功返回true，失败返回false，此时可以通过GetApiLastError()获取失败原因
	///@param func 启动策略函数的函数指针，需要用户自己实现
	MONITOR_GUEST_API_EXPORT bool RegisterStartFunc(StartFunc func);

	///注册停止策略的回调函数
	///@return 注册是否成功，成功返回true，失败返回false，此时可以通过GetApiLastError()获取失败原因
	///@param func 停止策略函数的函数指针，需要用户自己实现
	MONITOR_GUEST_API_EXPORT bool RegisterStopFunc(StopFunc func);

	///注册断线通知的回调函数
	///@return 注册是否成功，成功返回true，失败返回false，此时可以通过GetApiLastError()获取失败原因
	///@param func 断线通知函数的函数指针，需要用户自己实现
	MONITOR_GUEST_API_EXPORT bool RegisterDisconnectedFunc(DisconnectedFunc func);

	///注册设置key所对应值的回调函数
	///@return 注册是否成功，成功返回true，失败返回false，此时可以通过GetApiLastError()获取失败原因
	///@param func 断线通知函数的函数指针，需要用户自己实现
	MONITOR_GUEST_API_EXPORT bool RegisterSetParameterFunc(MonitorClientSetParameterFunc func);

	///登录Host服务器，调用之前需要先注册好上述3个回调函数
	///@return 登录是否成功，“0”表示登录成功，“-1”表示连接服务器出错，此时用户可以调用GetApiLastError()来获取错误代码，“-2”表示已存在连接，不允许重复登录，“-3”表示输入有错误
	///@param ip 服务器地址
	///@param port 服务器端口号
	///@param user 登录用户名
	///@param strategy_is_start 当前策略是否在运行状态，是的话为true，否则为false
	MONITOR_GUEST_API_EXPORT int32_t ConnectToMonitor(const char* ip, int port, const char* user, bool strategy_is_start);

	///将监控日志发往监控客户端
	///@return 发送请求是否成功，“0”表示请求成功，非“0”表示请求失败，此时用户可以调用GetApiLastError()来获取错误信息
	///@param level 日志级别，对应取值为：fatal - 0, error - 1, warning - 2, info - 3, debug -4, trace -5
	///@param topic 日志主题，由用户自定义
	///@param log_text 日志具体信息，由用户自定义
	///@param alarm_wav_index 音效索引值，例如“1”，监控客户端会播放“1.wav”音效，用户可以在监控客户端自定义音效，默认-1表示不播放音效
	MONITOR_GUEST_API_EXPORT int32_t SendMsg(int level, const char* topic, const char* log_text, int alarm_wav_index = -1);

	///获取API的系统错误
	///@param error_info 具体的错误信息，包括错误代码和错误原因
	///@remark 此函数为当ConnectToHost、SendMsg等函数调用失败时才需要调用，查看具体的失败原因
	MONITOR_GUEST_API_EXPORT void GetApiLastError(XTPHRI *error_info);

#ifdef __cplusplus
}
#endif


#endif
