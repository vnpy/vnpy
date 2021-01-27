/////////////////////////////////////////////////////////////////////////
/// DriectAccess Trade Engine
/// Copyright (C) Shanghai DirectAccess Technology Co., Ltd.
/// Last Modify 2019/3/18
/// Define Stock API
/// Author (c) Wang Jian Quan (Franklin)
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "DAStockStruct.h"

class IStockEvent
{
    //状态函数
public:
    virtual void OnFrontConnected() {};
    virtual void OnFrontDisconnected(int iReason) {};
    virtual void OnHeartBeatWarning(int iTimeLapse) {};

    //请求函数
public:
    virtual void OnRspNeedVerify(bool bFirstLogin, bool bHasSetQA) {}
    virtual void OnRspUserLogin(CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspUserLogout(CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspVerifyCode(CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspSafeVerify(CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspSetVerifyQA(CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspAccount(CStockRspAccountField *pRspAccount, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQuestion(CStockRspQuestionField *pRspQuestion, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspOrderInsert(CStockRspOrderInsertField *pRspOrderInsert, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspOrderModify(CStockRspOrderModifyField *pRspOrderModify, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspOrderCancel(CStockRspOrderCancelField *pRspOrderCancel, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspPasswordUpdate(CStockRspPasswordUpdateField *pRspPasswordUpdate, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}

    //推送函数
public:
    virtual void OnRtnTrade(CStockRtnTradeField *pRtnTrade, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRtnOrder(CStockRtnOrderField *pRtnOrder, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRtnCapital(CStockRtnCapitalField *pRtnCapital, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRtnPosition(CStockRtnPositionField *pRtnPosition, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}

    //查询函数
public:
    virtual void OnRspQryTick(CStockRspTickField *pRspTick, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryOrder(CStockRspOrderField *pRspOrder, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryTrade(CStockRspTradeField *pRspTrade, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryCapital(CStockRspCapitalField *pRspCapital, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryVersion(CStockRspVersionField *pRspVersion, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryPosition(CStockRspPositionField *pRspPosition, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryCurrency(CStockRspCurrencyField *pRspCurrency, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryExchange(CStockRspExchangeField *pRspExchange, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
    virtual void OnRspQryInstrument(CStockRspInstrumentField *pRspInstrument, CStockRspInfoField *pRspInfo, int iRequestID, bool bIsLast) {}
};

class DA_API_EXPORT CStockApi
{
    // 静态函数
public:
    static const char *GetVersion();
    static CStockApi *CreateStockApi(bool bRecordLog, const char* lpszLogFileName = "Stock.log");

    // 构造函数
public:
    CStockApi() {};
    virtual ~CStockApi() {};

    // 初始化函数
public:
    virtual bool Init() = 0;
    virtual void Release() = 0;
    virtual void SetHeartbeatTimeout(int iTimeout) = 0;
    virtual void RegisterSpi(IStockEvent *pIStockEvent) = 0;
    virtual void RegisterNameServer(const char *pszNsAddress) = 0;

    // 请求函数
public:
    virtual bool ReqUserLogin(CStockReqUserLoginField *pReqUserLogin, int iRequestID) = 0;
    virtual bool ReqUserLogout(CStockReqUserLogoutField *pReqUserLogout, int iRequestID) = 0;
    virtual bool ReqSafeVerify(CStockReqSafeVerifyField *pReqSafeVerify, int iRequestID) = 0;
    virtual bool ReqVerifyCode(CStockReqVerifyCodeField *pReqVerifyCode, int iRequestID) = 0;
    virtual bool ReqSetVerifyQA(CStockReqSetVerifyQAField *pReqSetVerifyQA, int iRequestID) = 0;
    virtual bool ReqGetQuestion(CStockReqGetQuestionField *pReqGetQuestion, int iRequestID) = 0;
    virtual bool ReqOrderInsert(CStockReqOrderInsertField *pReqOrderInsert, int iRequestID) = 0;
    virtual bool ReqOrderModify(CStockReqOrderModifyField *pReqOrderModify, int iRequestID) = 0;
    virtual bool ReqOrderCancel(CStockReqOrderCancelField *pReqOrderCancel, int iRequestID) = 0;
    virtual bool ReqPasswordUpdate(CStockReqPasswordUpdateField *pReqPasswordUpdate, int iRequestID) = 0;

    // 查询函数
public:
    virtual bool ReqQryTick(CStockQryTickField *pQryTick, int iRequestID) = 0;
    virtual bool ReqQryOrder(CStockQryOrderField *pQryOrder, int iRequestID) = 0;
    virtual bool ReqQryTrade(CStockQryTradeField *pQryTrade, int iRequestID) = 0;
    virtual bool ReqQryCapital(CStockQryCapitalField *pQryCapital, int iRequestID) = 0;
    virtual bool ReqQryVersion(CStockQryVersionField *pQryVersion, int iRequestID) = 0;
    virtual bool ReqQryPosition(CStockQryPositionField *pQryPosition, int iRequestID) = 0;
    virtual bool ReqQryCurrency(CStockQryCurrencyField *pQryCurrency, int iRequestID) = 0;
    virtual bool ReqQryExchange(CStockQryExchangeField *pQryExchange, int iRequestID) = 0;
    virtual bool ReqQryInstrument(CStockQryInstrumentField *pQryInstrument, int iRequestID) = 0;
};

