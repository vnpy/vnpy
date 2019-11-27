/////////////////////////////////////////////////////////////////////////
/// DriectAccess Trade Engine
/// Copyright (C) Shanghai DirectAccess Technology Co., Ltd.
/// Last Modify 2019/3/18
/// Define Future API
/// Author (c) Wang Jian Quan (Franklin)
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "DAFutureStruct.h"

class IFutureEvent
{
	//状态函数
public:
	virtual void OnFrontConnected(){};
	virtual void OnFrontDisconnected(int iReason){};
	virtual void OnHeartBeatWarning(int iTimeLapse){};

	//请求函数
public:
	virtual void OnRspNeedVerify(bool bFirstLogin, bool bHasSetQA) {}
	virtual void OnRspUserLogin(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspUserLogout(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspVerifyCode(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspSafeVerify(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspSetVerifyQA(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspAccount(CFutureRspAccountField *pRspAccount, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQuestion(CFutureRspQuestionField *pRspVersion, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspOrderInsert(CFutureRspOrderInsertField *pRspOrderInsert, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspOrderModify(CFutureRspOrderModifyField *pRspOrderModify, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspOrderCancel(CFutureRspOrderCancelField *pRspOrderCancel, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspPasswordUpdate(CFutureRspPasswordUpdateField *pRspPasswordUpdate, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}

	//推送函数
public:
	virtual void OnRtnTrade(CFutureRtnTradeField *pRtnTrade, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRtnOrder(CFutureRtnOrderField *pRtnOrder, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRtnCapital(CFutureRtnCapitalField *pRtnCapital, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRtnPosition(CFutureRtnPositionField *pRtnPosition, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}

	//查询函数
public:
	virtual void OnRspQryOrder(CFutureRspOrderField *pRspOrder, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryTrade(CFutureRspTradeField *pRspTrade, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryCapital(CFutureRspCapitalField *pRspCapital, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryVersion(CFutureRspVersionField *pRspVersion, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryPosition(CFutureRspPositionField *pRspPosition, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryCurrency(CFutureRspCurrencyField *pRspCurrency, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryExchange(CFutureRspExchangeField *pRspExchange, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryStrategy(CFutureRspStrategyField *pRspStrategy, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryCommodity(CFutureRspCommodityField *pRspCommodity, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryInstrument(CFutureRspInstrumentField *pRspInstrument, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryExchangeTime(CFutureRspExchangeTimeField *pRspExchangeTime, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryCommodityTime(CFutureRspCommodityTimeField *pRspCommodityTime, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryTotalPosition(CFutureRspTotalPositionField *pRspTotalPosition, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspQryStrategyDetail(CFutureRspStrategyDetailField *pRspStrategyDetail, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
};

class DA_API_EXPORT CFutureApi
{
	// 静态函数
public:
	static const char *GetVersion();
	static CFutureApi *CreateFutureApi(bool bRecordLog, const char *lpszLogFileName = "Future.log");

	// 构造函数
public:
	CFutureApi(){};
	virtual ~CFutureApi(){};

	// 初始化函数
public:
	virtual bool Init() = 0;
	virtual void Release() = 0;
	virtual void SetHeartbeatTimeout(int iTimeout) = 0;
	virtual void RegisterSpi(IFutureEvent *pIFutureEvent) = 0;
	virtual void RegisterNameServer(const char *pszNsAddress) = 0;

	// 请求函数
public:
	virtual bool ReqUserLogin(CFutureReqUserLoginField *pReqUserLogin, int iRequestID) = 0;
	virtual bool ReqUserLogout(CFutureReqUserLogoutField *pReqUserLogout, int iRequestID) = 0;
	virtual bool ReqSafeVerify(CFutureReqSafeVerifyField *pReqSafeVerify, int iRequestID) = 0;
	virtual bool ReqVerifyCode(CFutureReqVerifyCodeField *pReqVerifyCode, int iRequestID) = 0;
	virtual bool ReqSetVerifyQA(CFutureReqSetVerifyQAField *pReqSetVerifyQA, int iRequestID) = 0;
	virtual bool ReqGetQuestion(CFutureReqGetQuestionField *pReqGetQuestion, int iRequestID) = 0;
	virtual bool ReqOrderInsert(CFutureReqOrderInsertField *pReqOrderInsert, int iRequestID) = 0;
	virtual bool ReqOrderModify(CFutureReqOrderModifyField *pReqOrderModify, int iRequestID) = 0;
	virtual bool ReqOrderCancel(CFutureReqOrderCancelField *pReqOrderCancel, int iRequestID) = 0;
	virtual bool ReqPasswordUpdate(CFutureReqPasswordUpdateField *pReqPasswordUpdate, int iRequestID) = 0;

	// 查询函数
public:
	virtual bool ReqQryOrder(CFutureQryOrderField *pQryOrder, int iRequestID) = 0;
	virtual bool ReqQryTrade(CFutureQryTradeField *pQryTrade, int iRequestID) = 0;
	virtual bool ReqQryCapital(CFutureQryCapitalField *pQryCapital, int iRequestID) = 0;
	virtual bool ReqQryVersion(CFutureQryVersionField *pQryVersion, int iRequestID) = 0;
	virtual bool ReqQryCurrency(CFutureQryCurrencyField *pQryCurrency, int iRequestID) = 0;
	virtual bool ReqQryExchange(CFutureQryExchangeField *pQryExchange, int iRequestID) = 0;
	virtual bool ReqQryPosition(CFutureQryPositionField *pQryPosition, int iRequestID) = 0;
	virtual bool ReqQryStrategy(CFutureQryStrategyField *pQryStrategy, int iRequestID) = 0;
	virtual bool ReqQryCommodity(CFutureQryCommodityField *pQryCommodity, int iRequestID) = 0;
	virtual bool ReqQryInstrument(CFutureQryInstrumentField *pQryInstrument, int iRequestID) = 0;
	virtual bool ReqQryExchangeTime(CFutureQryExchangeTimeField *pQryExchangeTime, int iRequestID) = 0;
	virtual bool ReqQryCommodityTime(CFutureQryCommodityTimeField *pQryCommodityTime, int iRequestID) = 0;
	virtual bool ReqQryTotalPosition(CFutureQryTotalPositionField *pQryTotalPosition, int iRequestID) = 0;
	virtual bool ReqQryStrategyDetail(CFutureQryStrategyDetailField *pQryStrategyDetail, int iRequestID) = 0;
};
