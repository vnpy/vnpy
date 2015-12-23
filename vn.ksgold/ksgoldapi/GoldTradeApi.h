#ifndef GOLD_TRADE_API_H
#define GOLD_TRADE_API_H

#ifdef GOLDTRADEAPI_EXPORTS
#define GOLDTRADEAPI_LIB __declspec(dllexport)
#else
#ifdef WIN32
#define GOLDTRADEAPI_LIB __declspec(dllimport)
#else
#define GOLDTRADEAPI_LIB 
#endif
#endif


#include <stdio.h>
#include "APIError.h"
#include "KSUserApiStructEx.h"
class CGoldTradeSpi	//回调接口
{
 public:
	virtual ~CGoldTradeSpi(){};
	 //连接建立通知
	virtual void OnFrontConnected(){};

	//连接断开
	virtual void OnFrontDisconnected(int nReason){};


	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	//市场状态通知
	virtual void OnNtyMktStatus(const CThostFtdcMarketStatusField *pfldMktStatus){};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};


	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

	///报单录入请求响应(二级系统检查错误）
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入错误回报(交易所）
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderRtnField *pOrder) {};

	//强退通知
	virtual void OnForceLogout(CThostFtdcUserLogoutField *pLogout) {}; 
	
	//撤单应答
	///报单操作请求响应(二级系统返回包含了错误编码和错误消息)
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作错误回报(交易所返回)
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	//查询客户库存应答
	virtual void OnRspQryClientStorage(CThostFtdcStorageField *pStorage, CThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast){};

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	//virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

};



class GOLDTRADEAPI_LIB CGoldTradeApi 
{
public: 
	static CGoldTradeApi *CreateGoldTradeApi();
	//释放接口
	virtual void Release()=0;
	//注册前置地址
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	//注册API回调接口
	virtual void RegisterSpi(CGoldTradeSpi *pGeneralSpi)=0;	
	//启动API线程
	virtual int Init(bool logflag=true)=0;	
	//停止API线程
	virtual void Join()=0;	


	//用户登录请求
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;

	//用户登出请求
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	//断线重连
	virtual int ReqUserReLogin() = 0;

	//订阅行情
	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;

	//查询期货合约
	virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	//下单请求
	virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	//报单操作请求(撤单)
	virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) = 0;

	//查询持仓请求
	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pInvestorPosition, int nRequestID) = 0;

	//查询资金请求
	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	//成交查询请求
	virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	//委托查询请求
	virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	//查询客户库存请求
	virtual int ReqQryStorage(CThostFtdcQryStorageField *pfldStorage, int nRequestID)=0;


protected:
	virtual ~CGoldTradeApi();



};




#endif