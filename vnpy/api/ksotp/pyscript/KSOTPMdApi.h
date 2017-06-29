#ifndef __KSOTPMDAPI_H_INCLUDED_
#define __KSOTPMDAPI_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KSOTPUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_OTP_MD_API_EXPORT
#define OTP_MD_API_EXPORT __declspec(dllexport)
#else
#define OTP_MD_API_EXPORT __declspec(dllimport)
#endif
#else
#ifdef  WIN32
#define OTP_MD_API_EXPORT 
#else
#define OTP_MD_API_EXPORT __attribute__((visibility("default")))
#endif
#endif

namespace KingstarAPI
{

class CKSOTPMdSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，客户端需要做重连处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};	

	///登录请求响应
	virtual void OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CKSOTPUserLogoutField *pUserLogout, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅行情应答
	virtual void OnRspSubMarketData(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅询价应答
	virtual void OnRspSubForQuoteRsp(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CKSOTPSpecificInstrumentField *pSpecificInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CKSOTPDepthMarketDataField *pDepthMarketData) {};

	///询价通知
	virtual void OnRtnForQuoteRsp(CKSOTPForQuoteRspField *pForQuoteRsp) {};
};

class OTP_MD_API_EXPORT CKSOTPMdApi
{
public:
	///创建MdApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	///modify for udp marketdata
	static CKSOTPMdApi *CreateOTPMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false, const bool bIsMulticast=false);
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CKSOTPMdSpi *pSpi) = 0;
	
	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(CKSOTPSpecificInstrumentField *ppInstrumentID[], int nCount) = 0;

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(CKSOTPSpecificInstrumentField *ppInstrumentID[], int nCount) = 0;
	
	///订阅询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) = 0;

	///退订询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) = 0;

	///用户登录请求
	virtual int ReqUserLogin(CKSOTPReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	
	///登出请求
	virtual int ReqUserLogout(CKSOTPUserLogoutField *pUserLogout, int nRequestID) = 0;
protected:
	~CKSOTPMdApi(){};
};

}	// end of namespace KingstarAPI

#endif
