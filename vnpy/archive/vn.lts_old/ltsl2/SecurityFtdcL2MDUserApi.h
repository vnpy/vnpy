/////////////////////////////////////////////////////////////////////////
///@company shanghai liber information Technology Co.,Ltd
///@file SecurityFtdcL2MDUserApi.h
///@brief 定义客户端接口
/////////////////////////////////////////////////////////////////////////

#if !defined(SECURITY_L2MD_FTDCUSERAPI_H)
#define SECURITY_L2MD_FTDCUSERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SecurityFtdcL2MDUserApiStruct.h"

_LTS_NS_BEGIN_
#if defined(L2MD_USERAPI_IS_LIB) && defined(WINDOWS)
#ifdef LIB_L2MD_USER_API_EXPORT
#define L2MD_USER_API_EXPORT __declspec(dllexport)
#else
#define L2MD_USER_API_EXPORT __declspec(dllimport)
#endif
#else
#define L2MD_USER_API_EXPORT 
#endif

class CSecurityFtdcL2MDUserSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告
	virtual void OnHeartBeatWarning(int nTimeLapse){};

	///错误应答
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登录请求响应
	virtual void OnRspUserLogin(CSecurityFtdcUserLoginField *pUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅Level2行情应答
	virtual void OnRspSubL2MarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅Level2行情应答
	virtual void OnRspUnSubL2MarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅Level2指数行情应答
	virtual void OnRspSubL2Index(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅Level2指数行情应答
	virtual void OnRspUnSubL2Index(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Level2行情通知
	virtual void OnRtnL2MarketData(CSecurityFtdcL2MarketDataField *pL2MarketData) {};

	///Level2指数行情通知
	virtual void OnRtnL2Index(CSecurityFtdcL2IndexField *pL2Index) {};

	///订阅逐笔委托及成交应答
	virtual void OnRspSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅逐笔委托及成交应答
	virtual void OnRspUnSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Level2委托通知
	virtual void OnRtnL2Order(CSecurityFtdcL2OrderField *pL2Order) {};

	///Level2成交通知
	virtual void OnRtnL2Trade(CSecurityFtdcL2TradeField *pL2Trade) {};

	///通知清理SSE买卖一队列中数量为0的报单
	virtual void OnNtfCheckOrderList(TSecurityFtdcInstrumentIDType InstrumentID, TSecurityFtdcFunctionCodeType FunctionCode) {};
};

#ifndef WINDOWS
	#if __GNUC__ >= 4
		#pragma GCC visibility push(default)
	#endif
#endif
class L2MD_USER_API_EXPORT CSecurityFtdcL2MDUserApi
{
public:
	///创建UserApi
	static CSecurityFtdcL2MDUserApi *CreateFtdcL2MDUserApi(const bool bIsMulticast=false);
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	virtual int Join() = 0;
	
	///获取当前交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CSecurityFtdcL2MDUserSpi *pSpi) = 0;
	
	virtual int SubscribeL2MarketData(char *ppInstrumentID[], int nCount, char* pExchageID) = 0;

	virtual int UnSubscribeL2MarketData(char *ppInstrumentID[], int nCount, char* pExchageID) = 0;
	
	virtual int SubscribeL2Index(char *ppInstrumentID[], int nCount, char* pExchageID) = 0;

	virtual int UnSubscribeL2Index(char *ppInstrumentID[], int nCount, char* pExchageID) = 0;	
	
	virtual int SubscribeL2OrderAndTrade() = 0;
	
	virtual int UnSubscribeL2OrderAndTrade() = 0;

	///登录请求
	virtual int ReqUserLogin(CSecurityFtdcUserLoginField *pUserLogin, int nRequestID) = 0;

	///登出请求
	virtual int ReqUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;
protected:
	~CSecurityFtdcL2MDUserApi(){};
};
#ifndef WINDOWS
	#if __GNUC__ >= 4
		#pragma GCC visibility pop
	#endif
#endif
_LTS_NS_END_
#endif
