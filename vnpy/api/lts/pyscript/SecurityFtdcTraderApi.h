/////////////////////////////////////////////////////////////////////////
///@company shanghai liber information Technology Co.,Ltd
///@file SecurityFtdcTraderApi.h
///@brief 定义客户端接口
/////////////////////////////////////////////////////////////////////////

#if !defined(SECURITY_FTDCTRADERAPI_H)
#define SECURITY_FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SecurityFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class CSecurityFtdcTraderSpi
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
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};	

	///错误应答
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登录请求响应
	virtual void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///获取认证随机码请求响应
	virtual void OnRspFetchAuthRandCode(CSecurityFtdcAuthRandCodeField *pAuthRandCode, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作请求响应
	virtual void OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CSecurityFtdcUserPasswordUpdateField *pUserPasswordUpdate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金账户口令更新请求响应
	virtual void OnRspTradingAccountPasswordUpdate(CSecurityFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	virtual void OnRtnOrder(CSecurityFtdcOrderField *pOrder) {};

	///成交通知
	virtual void OnRtnTrade(CSecurityFtdcTradeField *pTrade) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CSecurityFtdcOrderActionField *pOrderAction, CSecurityFtdcRspInfoField *pRspInfo) {};

	///Liber发起出金应答
	virtual void OnRspFundOutByLiber(CSecurityFtdcInputFundTransferField *pInputFundTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Liber发起出金通知
	virtual void OnRtnFundOutByLiber(CSecurityFtdcFundTransferField *pFundTransfer) {};

	///Liber发起出金错误回报
	virtual void OnErrRtnFundOutByLiber(CSecurityFtdcInputFundTransferField *pInputFundTransfer, CSecurityFtdcRspInfoField *pRspInfo) {};

	///银行发起入金通知
	virtual void OnRtnFundInByBank(CSecurityFtdcFundTransferField *pFundTransfer) {};

	///资金内转应答
	virtual void OnRspFundInterTransfer(CSecurityFtdcFundInterTransferField *pFundInterTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金内转流水通知
	virtual void OnRtnFundInterTransferSerial(CSecurityFtdcFundInterTransferSerialField *pFundInterTransferSerial) {};

	///资金内转错误回报
	virtual void OnErrRtnFundInterTransfer(CSecurityFtdcFundInterTransferField *pFundInterTransfer, CSecurityFtdcRspInfoField *pRspInfo) {};
};

#ifndef WINDOWS
	#if __GNUC__ >= 4
		#pragma GCC visibility push(default)
	#endif
#endif

class TRADER_API_EXPORT CSecurityFtdcTraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CSecurityFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
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
	virtual void RegisterSpi(CSecurityFtdcTraderSpi *pSpi) = 0;
	
	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        SECURITY_TERT_RESTART:从本交易日开始重传
	///        SECURITY_TERT_RESUME:从上次收到的续传
	///        SECURITY_TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(SECURITY_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        SECURITY_TERT_RESTART:从本交易日开始重传
	///        SECURITY_TERT_RESUME:从上次收到的续传
	///        SECURITY_TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(SECURITY_TE_RESUME_TYPE nResumeType) = 0;

	///用户登录请求
	virtual int ReqUserLogin(CSecurityFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	

	///登出请求
	virtual int ReqUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	///获取认证随机码请求
	virtual int ReqFetchAuthRandCode(CSecurityFtdcAuthRandCodeField *pAuthRandCode, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, int nRequestID) = 0;

	///用户口令更新请求
	virtual int ReqUserPasswordUpdate(CSecurityFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///资金账户口令更新请求
	virtual int ReqTradingAccountPasswordUpdate(CSecurityFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID) = 0;

	///Liber发起出金请求
	virtual int ReqFundOutByLiber(CSecurityFtdcInputFundTransferField *pInputFundTransfer, int nRequestID) = 0;

	///资金内转请求
	virtual int ReqFundInterTransfer(CSecurityFtdcFundInterTransferField *pFundInterTransfer, int nRequestID) = 0;
protected:
	~CSecurityFtdcTraderApi(){};
};
  
#ifndef WINDOWS
	#if __GNUC__ >= 4
		#pragma GCC visibility pop
	#endif
#endif

#endif
