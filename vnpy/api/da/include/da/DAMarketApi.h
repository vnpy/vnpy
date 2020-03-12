/////////////////////////////////////////////////////////////////////////
/// DriectAccess Trade Engine
/// Copyright (C) Shanghai DirectAccess Technology Co., Ltd.
/// Last Modify 2019/3/18
/// Define Market API
/// Author (c) Wang Jian Quan (Franklin)
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "DAMarketStruct.h"

class IMarketEvent
{
	//״̬����
public:
	virtual void OnFrontConnected() {};
	virtual void OnFrontDisconnected(int iReason) {};
	virtual void OnHeartBeatWarning(int iTimeLapse) {};

	//������
public:
	virtual void OnRspRawData(const char* rawData) {}
	virtual void OnRspUserLogin(CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {};
	virtual void OnRspTradeDate(CMarketRspTradeDateField *pRspTradeDate, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspBrokerData(CMarketRspBrokerDataField *pRspBrokerData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
	virtual void OnRspMarketData(CMarketRspMarketDataField *pRspMarketData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
};

class DA_API_EXPORT CMarketApi
{
	// ��̬����
public:
	static const char *GetVersion();
	static CMarketApi *CreateMarketApi(bool bRecordLog, const char* lpszLogFileName = "Market.log");

	// ���캯��
public:
	CMarketApi() {};
	virtual ~CMarketApi() {};

	// ��ʼ������
public:
	virtual bool Init() = 0;
	virtual void Release() = 0;
	virtual void SetHeartbeatTimeout(int iTimeout) = 0;
	virtual void RegisterSpi(IMarketEvent *pIMarketEvent) = 0;
	virtual void RegisterNameServer(const char *pszNsAddress) = 0;

	// ������
public:
	virtual bool ReqUserLogin(CMarketReqUserLoginField *pReqUserLoginField, int iRequestID) = 0;
	virtual bool ReqBrokerData(CMarketReqBrokerDataField *pReqBrokerDataField, int iRequestID) = 0;
	virtual bool ReqMarketData(CMarketReqMarketDataField *pReqMarketDataField, int iRequestID) = 0;
};


