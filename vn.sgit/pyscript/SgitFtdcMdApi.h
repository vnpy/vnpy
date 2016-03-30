/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

#if !defined(Sgit_FTDCMDAPI_H)
#define Sgit_FTDCMDAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SgitFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

class CSgitFtdcMdSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param pErrMsg 错误原因
	virtual void OnFrontDisconnected(char *pErrMsg){};	

	///登录请求响应
	virtual void OnRspUserLogin(CSgitFtdcRspUserLoginField *pRspUserLogin, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CSgitFtdcUserLogoutField *pUserLogout, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CSgitFtdcDepthMarketDataField *pDepthMarketData) {};
};

class MD_API_EXPORT CSgitFtdcMdApi
{
public:
	///创建MdApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CSgitFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "");
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	///isLogged 开发调试时使用true，可以打印出收到的消息包内容
	virtual void Init(bool isLogged) = 0;
	
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

	/**用多播时TCP配置也需要设置
	*调用该函数，默认采用tcp模式发送行情
	*设置多播的配置 MlCast://hostIP$multiaddress:port，
	*如果只有一张网卡可以 MlCast://ANY$multiaddress:port	
	* @param szMlCastAddr 本机ip地址、多播组及端口	
	*/
	virtual void SetMultiCastAddr(char *szMlCastAddr) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CSgitFtdcMdSpi *pSpi) = 0;
	///订阅市场流。
	///@param nResumeType 公共流重传方式  
	///        Sgit_TERT_RESTART:从本交易日开始重传
	///        Sgit_TERT_RESUME:从上次收到的续传
	///        Sgit_TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribeMarketTopic(Sgit_TE_RESUME_TYPE nResumeType) = 0;

	///
	/// 发送行情订阅
	/// @param iRequestID 请求号
	/// @param pMBLQuotReq 行情订阅请求域
	/// @return 0表示成功
	/// @return 其它表示失败
	///
	virtual int SubQuot(CSgitSubQuotField *pSgitSubQuotField)=0;
	///发送就绪指令到前置,通知前置可以给自己发送私有流与公共流
	/// @return 0表示成功
	/// @return 其它参见错误码
	///
	virtual int Ready() = 0;

	///用户登录请求
	virtual int ReqUserLogin(CSgitFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;

	///登出请求
	virtual int ReqUserLogout(CSgitFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;
protected:
	~CSgitFtdcMdApi(){};
};

#endif
