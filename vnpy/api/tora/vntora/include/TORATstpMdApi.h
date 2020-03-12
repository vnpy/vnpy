/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰信息科技有限公司
///@file TORATstpMdApi.h
///@brief 定义了客户端接口
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_TORA_TSTPMDAPI_H)
#define _TORA_TSTPMDAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpUserApiStruct.h"


#ifdef MD_API_EXPORT
#ifdef WINDOWS
#define MD_API_DLL_EXPORT __declspec(dllexport)
#else
#define MD_API_DLL_EXPORT __attribute__ ((visibility("default")))
#endif
#else
#define MD_API_DLL_EXPORT 
#endif

class CTORATstpMdSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///        -3 连接已断开
	///        -4 网络读失败
	///        -5 网络写失败
	///        -6 订阅流错误
	///        -7 流序号错误
	///        -8 错误的心跳报文
	///        -9 错误的报文
	virtual void OnFrontDisconnected(int nReason){};
			
	///错误应答
	virtual void OnRspError(CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登录请求响应
	virtual void OnRspUserLogin(CTORATstpRspUserLoginField *pRspUserLogin, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CTORATstpUserLogoutField *pUserLogout, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅行情应答
	virtual void OnRspSubMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅特定行情应答
	virtual void OnRspSubSpecialMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅特定行情应答
	virtual void OnRspUnSubSpecialMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅资金流向行情应答
	virtual void OnRspSubFundsFlowMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅资金流向行情应答
	virtual void OnRspUnSubFundsFlowMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CTORATstpMarketDataField *pDepthMarketData) {};

	///深度行情通知
	virtual void OnRtnSpecialMarketData(CTORATstpSpecialMarketDataField *pSpecialMarketData) {};

	///价格波动异常行情通知
	virtual void OnRtnEffectPriceMarketData(CTORATstpEffectPriceMarketDataField *pEffectPriceMarketData) {};

	///数量波动异常行情通知
	virtual void OnRtnEffectVolumeMarketData(CTORATstpEffectVolumeMarketDataField *pEffectVolumeMarketData) {};

	///资金流向行情通知
	virtual void OnRtnFundsFlowMarketData(CTORATstpFundsFlowMarketDataField *pFundsFlowMarketData) {};
};

class MD_API_DLL_EXPORT CTORATstpMdApi
{
public:
	///创建MdApi
	///@return 创建出的MdApi
	static CTORATstpMdApi *CreateTstpMdApi();
	
	///获取API版本号
	///@return 版本号
	static const char* GetApiVersion();
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;

	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;

	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	virtual void RegisterNameServer(char *pszNsAddress) = 0;

	///注册衍生服务服务器网络地址
	///@param pszNsAddress：衍生服务服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:15001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”15001”代表服务器端口号。
	virtual void RegisterDeriveServer(char *pszDeriveAddress) = 0;

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CTORATstpMdSpi *pSpi) = 0;
	
	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///订阅特定行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeSpecialMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///退订特定行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeSpecialMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///订阅资金流向行情。
	///@param ppInstrumentID 合约ID
	///@param nCount 要订阅/退订行情的合约个数
	///@remark
	virtual int SubscribeFundsFlowMarketData(char *ppInstrumentID[], int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///退订资金流向行情。
	///@param ppInstrumentID 合约ID
	///@param nCount 要订阅/退订行情的合约个数
	///@remark
	virtual int UnSubscribeFundsFlowMarketData(char *ppInstrumentID[], int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///用户登录请求
	virtual int ReqUserLogin(CTORATstpReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	

	///登出请求
	virtual int ReqUserLogout(CTORATstpUserLogoutField *pUserLogout, int nRequestID) = 0;
protected:
	~CTORATstpMdApi(){};
};
#endif
