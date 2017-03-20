/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

#if !defined(Sgit_FTDCTRADERAPI_H)
#define Sgit_FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SgitFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class CSgitFtdcTraderSpi
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

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CSgitFtdcUserPasswordUpdateField *pUserPasswordUpdate, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CSgitFtdcInputOrderField *pInputOrder, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作请求响应
	virtual void OnRspOrderAction(CSgitFtdcInputOrderActionField *pInputOrderAction, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(CSgitFtdcOrderField *pOrder, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CSgitFtdcTradingAccountField *pTradingAccount, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CSgitFtdcInvestorField *pInvestor, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CSgitFtdcInstrumentField *pInstrument, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	virtual void OnRtnOrder(CSgitFtdcOrderField *pOrder,CSgitFtdcRspInfoField *pRspInfo) {};

	///成交通知
	virtual void OnRtnTrade(CSgitFtdcTradeField *pTrade) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CSgitFtdcInstrumentStatusField *pInstrumentStatus) {};

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CSgitFtdcInvestorPositionDetailField *pInvestorPositionDetail, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CSgitFtdcInvestorPositionField *pInvestorPosition, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};		

	/// 当收到合约价位查询应答时回调该函数
	virtual void onRspMBLQuot(CSgitMBLQuotData *pMBLQuotData,CSgitFtdcRspInfoField *pRspMsg,int nRequestID,bool bIsLast){};

};

class TRADER_API_EXPORT CSgitFtdcTraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CSgitFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
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
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CSgitFtdcTraderSpi *pSpi) = 0;
	
	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        Sgit_TERT_RESTART:从本交易日开始重传
	///        Sgit_TERT_RESUME:从上次收到的续传
	///        Sgit_TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(Sgit_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        Sgit_TERT_RESTART:从本交易日开始重传
	///        Sgit_TERT_RESUME:从上次收到的续传
	///        Sgit_TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(Sgit_TE_RESUME_TYPE nResumeType) = 0;

	///发送就绪指令到前置,通知前置可以给自己发送私有流与公共流
	/// @return 0表示成功
	/// @return 其它参见错误码
	///
	virtual int Ready() = 0;

	///用户登录请求
	virtual int ReqUserLogin(CSgitFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;

	///登出请求
	virtual int ReqUserLogout(CSgitFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	///用户口令更新请求
	virtual int ReqUserPasswordUpdate(CSgitFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(CSgitFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CSgitFtdcInputOrderActionField *pInputOrderAction, int nRequestID) = 0;

	///请求查询报单
	virtual int ReqQryOrder(CSgitFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///请求查询资金账户
	virtual int ReqQryTradingAccount(CSgitFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	///请求查询投资者
	virtual int ReqQryInvestor(CSgitFtdcQryInvestorField *pQryInvestor, int nRequestID) = 0;

	///请求查询合约
	virtual int ReqQryInstrument(CSgitFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///请求查询投资者持仓明细
	virtual int ReqQryInvestorPositionDetail(CSgitFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) = 0;
	
	///请求查询投资者持仓
	virtual int ReqQryInvestorPosition(CSgitFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	/// 发送合约价位查询请求
	virtual int ReqMBLQuot(int iRequestID,CSgitMBLQuotReq *pMBLQuotReq) = 0;

protected:
	~CSgitFtdcTraderApi(){};
};

#endif
