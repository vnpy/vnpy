#pragma once

#include <pybind11/pybind11.h>

#include "dispatcher.h"
#include "property_helper.h"
#include "wrapper_helper.h"
#include "class_generators.h"

#include "ctp/ThostFtdcTraderApi.h"



class PyCThostFtdcTraderSpi : public CThostFtdcTraderSpi
{
public:
    void OnFrontConnected() override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnFrontConnected>::call(
            this,"OnFrontConnected"
        );
    }
    void OnFrontDisconnected(int nReason) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnFrontDisconnected>::call(
            this,"OnFrontDisconnected",nReason
        );
    }
    void OnHeartBeatWarning(int nTimeLapse) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnHeartBeatWarning>::call(
            this,"OnHeartBeatWarning",nTimeLapse
        );
    }
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField * pRspAuthenticateField,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspAuthenticate>::call(
            this,"OnRspAuthenticate",pRspAuthenticateField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspUserLogin>::call(
            this,"OnRspUserLogin",pRspUserLogin,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspUserLogout>::call(
            this,"OnRspUserLogout",pUserLogout,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspUserPasswordUpdate>::call(
            this,"OnRspUserPasswordUpdate",pUserPasswordUpdate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField * pTradingAccountPasswordUpdate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspTradingAccountPasswordUpdate>::call(
            this,"OnRspTradingAccountPasswordUpdate",pTradingAccountPasswordUpdate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspOrderInsert(CThostFtdcInputOrderField * pInputOrder,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspOrderInsert>::call(
            this,"OnRspOrderInsert",pInputOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspParkedOrderInsert(CThostFtdcParkedOrderField * pParkedOrder,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspParkedOrderInsert>::call(
            this,"OnRspParkedOrderInsert",pParkedOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField * pParkedOrderAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspParkedOrderAction>::call(
            this,"OnRspParkedOrderAction",pParkedOrderAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspOrderAction(CThostFtdcInputOrderActionField * pInputOrderAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspOrderAction>::call(
            this,"OnRspOrderAction",pInputOrderAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField * pQueryMaxOrderVolume,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQueryMaxOrderVolume>::call(
            this,"OnRspQueryMaxOrderVolume",pQueryMaxOrderVolume,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspSettlementInfoConfirm>::call(
            this,"OnRspSettlementInfoConfirm",pSettlementInfoConfirm,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField * pRemoveParkedOrder,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspRemoveParkedOrder>::call(
            this,"OnRspRemoveParkedOrder",pRemoveParkedOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField * pRemoveParkedOrderAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspRemoveParkedOrderAction>::call(
            this,"OnRspRemoveParkedOrderAction",pRemoveParkedOrderAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspExecOrderInsert(CThostFtdcInputExecOrderField * pInputExecOrder,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspExecOrderInsert>::call(
            this,"OnRspExecOrderInsert",pInputExecOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField * pInputExecOrderAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspExecOrderAction>::call(
            this,"OnRspExecOrderAction",pInputExecOrderAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspForQuoteInsert(CThostFtdcInputForQuoteField * pInputForQuote,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspForQuoteInsert>::call(
            this,"OnRspForQuoteInsert",pInputForQuote,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQuoteInsert(CThostFtdcInputQuoteField * pInputQuote,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQuoteInsert>::call(
            this,"OnRspQuoteInsert",pInputQuote,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQuoteAction(CThostFtdcInputQuoteActionField * pInputQuoteAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQuoteAction>::call(
            this,"OnRspQuoteAction",pInputQuoteAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspLockInsert(CThostFtdcInputLockField * pInputLock,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspLockInsert>::call(
            this,"OnRspLockInsert",pInputLock,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspCombActionInsert(CThostFtdcInputCombActionField * pInputCombAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspCombActionInsert>::call(
            this,"OnRspCombActionInsert",pInputCombAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryOrder(CThostFtdcOrderField * pOrder,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryOrder>::call(
            this,"OnRspQryOrder",pOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTrade(CThostFtdcTradeField * pTrade,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryTrade>::call(
            this,"OnRspQryTrade",pTrade,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField * pInvestorPosition,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInvestorPosition>::call(
            this,"OnRspQryInvestorPosition",pInvestorPosition,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTradingAccount(CThostFtdcTradingAccountField * pTradingAccount,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryTradingAccount>::call(
            this,"OnRspQryTradingAccount",pTradingAccount,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestor(CThostFtdcInvestorField * pInvestor,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInvestor>::call(
            this,"OnRspQryInvestor",pInvestor,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTradingCode(CThostFtdcTradingCodeField * pTradingCode,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryTradingCode>::call(
            this,"OnRspQryTradingCode",pTradingCode,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField * pInstrumentMarginRate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInstrumentMarginRate>::call(
            this,"OnRspQryInstrumentMarginRate",pInstrumentMarginRate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField * pInstrumentCommissionRate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInstrumentCommissionRate>::call(
            this,"OnRspQryInstrumentCommissionRate",pInstrumentCommissionRate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryExchange(CThostFtdcExchangeField * pExchange,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryExchange>::call(
            this,"OnRspQryExchange",pExchange,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryProduct(CThostFtdcProductField * pProduct,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryProduct>::call(
            this,"OnRspQryProduct",pProduct,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInstrument>::call(
            this,"OnRspQryInstrument",pInstrument,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryDepthMarketData>::call(
            this,"OnRspQryDepthMarketData",pDepthMarketData,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField * pSettlementInfo,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQrySettlementInfo>::call(
            this,"OnRspQrySettlementInfo",pSettlementInfo,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTransferBank(CThostFtdcTransferBankField * pTransferBank,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryTransferBank>::call(
            this,"OnRspQryTransferBank",pTransferBank,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField * pInvestorPositionDetail,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInvestorPositionDetail>::call(
            this,"OnRspQryInvestorPositionDetail",pInvestorPositionDetail,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryNotice(CThostFtdcNoticeField * pNotice,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryNotice>::call(
            this,"OnRspQryNotice",pNotice,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQrySettlementInfoConfirm>::call(
            this,"OnRspQrySettlementInfoConfirm",pSettlementInfoConfirm,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField * pInvestorPositionCombineDetail,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInvestorPositionCombineDetail>::call(
            this,"OnRspQryInvestorPositionCombineDetail",pInvestorPositionCombineDetail,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField * pCFMMCTradingAccountKey,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryCFMMCTradingAccountKey>::call(
            this,"OnRspQryCFMMCTradingAccountKey",pCFMMCTradingAccountKey,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField * pEWarrantOffset,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryEWarrantOffset>::call(
            this,"OnRspQryEWarrantOffset",pEWarrantOffset,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField * pInvestorProductGroupMargin,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInvestorProductGroupMargin>::call(
            this,"OnRspQryInvestorProductGroupMargin",pInvestorProductGroupMargin,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField * pExchangeMarginRate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryExchangeMarginRate>::call(
            this,"OnRspQryExchangeMarginRate",pExchangeMarginRate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField * pExchangeMarginRateAdjust,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryExchangeMarginRateAdjust>::call(
            this,"OnRspQryExchangeMarginRateAdjust",pExchangeMarginRateAdjust,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryExchangeRate(CThostFtdcExchangeRateField * pExchangeRate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryExchangeRate>::call(
            this,"OnRspQryExchangeRate",pExchangeRate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField * pSecAgentACIDMap,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQrySecAgentACIDMap>::call(
            this,"OnRspQrySecAgentACIDMap",pSecAgentACIDMap,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryProductExchRate(CThostFtdcProductExchRateField * pProductExchRate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryProductExchRate>::call(
            this,"OnRspQryProductExchRate",pProductExchRate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryProductGroup(CThostFtdcProductGroupField * pProductGroup,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryProductGroup>::call(
            this,"OnRspQryProductGroup",pProductGroup,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField * pOptionInstrTradeCost,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryOptionInstrTradeCost>::call(
            this,"OnRspQryOptionInstrTradeCost",pOptionInstrTradeCost,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField * pOptionInstrCommRate,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryOptionInstrCommRate>::call(
            this,"OnRspQryOptionInstrCommRate",pOptionInstrCommRate,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryExecOrder(CThostFtdcExecOrderField * pExecOrder,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryExecOrder>::call(
            this,"OnRspQryExecOrder",pExecOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryForQuote(CThostFtdcForQuoteField * pForQuote,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryForQuote>::call(
            this,"OnRspQryForQuote",pForQuote,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryQuote(CThostFtdcQuoteField * pQuote,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryQuote>::call(
            this,"OnRspQryQuote",pQuote,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryLock(CThostFtdcLockField * pLock,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryLock>::call(
            this,"OnRspQryLock",pLock,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryLockPosition(CThostFtdcLockPositionField * pLockPosition,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryLockPosition>::call(
            this,"OnRspQryLockPosition",pLockPosition,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestorLevel(CThostFtdcInvestorLevelField * pInvestorLevel,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryInvestorLevel>::call(
            this,"OnRspQryInvestorLevel",pInvestorLevel,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryExecFreeze(CThostFtdcExecFreezeField * pExecFreeze,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryExecFreeze>::call(
            this,"OnRspQryExecFreeze",pExecFreeze,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField * pCombInstrumentGuard,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryCombInstrumentGuard>::call(
            this,"OnRspQryCombInstrumentGuard",pCombInstrumentGuard,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryCombAction(CThostFtdcCombActionField * pCombAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryCombAction>::call(
            this,"OnRspQryCombAction",pCombAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTransferSerial(CThostFtdcTransferSerialField * pTransferSerial,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryTransferSerial>::call(
            this,"OnRspQryTransferSerial",pTransferSerial,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryAccountregister(CThostFtdcAccountregisterField * pAccountregister,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryAccountregister>::call(
            this,"OnRspQryAccountregister",pAccountregister,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspError(CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspError>::call(
            this,"OnRspError",pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnOrder(CThostFtdcOrderField * pOrder) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnOrder>::call(
            this,"OnRtnOrder",pOrder
        );
    }
    void OnRtnTrade(CThostFtdcTradeField * pTrade) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnTrade>::call(
            this,"OnRtnTrade",pTrade
        );
    }
    void OnErrRtnOrderInsert(CThostFtdcInputOrderField * pInputOrder,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnOrderInsert>::call(
            this,"OnErrRtnOrderInsert",pInputOrder,pRspInfo
        );
    }
    void OnErrRtnOrderAction(CThostFtdcOrderActionField * pOrderAction,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnOrderAction>::call(
            this,"OnErrRtnOrderAction",pOrderAction,pRspInfo
        );
    }
    void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField * pInstrumentStatus) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnInstrumentStatus>::call(
            this,"OnRtnInstrumentStatus",pInstrumentStatus
        );
    }
    void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField * pTradingNoticeInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnTradingNotice>::call(
            this,"OnRtnTradingNotice",pTradingNoticeInfo
        );
    }
    void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField * pErrorConditionalOrder) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnErrorConditionalOrder>::call(
            this,"OnRtnErrorConditionalOrder",pErrorConditionalOrder
        );
    }
    void OnRtnExecOrder(CThostFtdcExecOrderField * pExecOrder) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnExecOrder>::call(
            this,"OnRtnExecOrder",pExecOrder
        );
    }
    void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField * pInputExecOrder,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnExecOrderInsert>::call(
            this,"OnErrRtnExecOrderInsert",pInputExecOrder,pRspInfo
        );
    }
    void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField * pExecOrderAction,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnExecOrderAction>::call(
            this,"OnErrRtnExecOrderAction",pExecOrderAction,pRspInfo
        );
    }
    void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField * pInputForQuote,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnForQuoteInsert>::call(
            this,"OnErrRtnForQuoteInsert",pInputForQuote,pRspInfo
        );
    }
    void OnRtnQuote(CThostFtdcQuoteField * pQuote) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnQuote>::call(
            this,"OnRtnQuote",pQuote
        );
    }
    void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField * pInputQuote,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnQuoteInsert>::call(
            this,"OnErrRtnQuoteInsert",pInputQuote,pRspInfo
        );
    }
    void OnErrRtnQuoteAction(CThostFtdcQuoteActionField * pQuoteAction,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnQuoteAction>::call(
            this,"OnErrRtnQuoteAction",pQuoteAction,pRspInfo
        );
    }
    void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField * pForQuoteRsp) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnForQuoteRsp>::call(
            this,"OnRtnForQuoteRsp",pForQuoteRsp
        );
    }
    void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField * pCFMMCTradingAccountToken) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnCFMMCTradingAccountToken>::call(
            this,"OnRtnCFMMCTradingAccountToken",pCFMMCTradingAccountToken
        );
    }
    void OnRtnLock(CThostFtdcLockField * pLock) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnLock>::call(
            this,"OnRtnLock",pLock
        );
    }
    void OnErrRtnLockInsert(CThostFtdcInputLockField * pInputLock,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnLockInsert>::call(
            this,"OnErrRtnLockInsert",pInputLock,pRspInfo
        );
    }
    void OnRtnCombAction(CThostFtdcCombActionField * pCombAction) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnCombAction>::call(
            this,"OnRtnCombAction",pCombAction
        );
    }
    void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField * pInputCombAction,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnCombActionInsert>::call(
            this,"OnErrRtnCombActionInsert",pInputCombAction,pRspInfo
        );
    }
    void OnRspQryContractBank(CThostFtdcContractBankField * pContractBank,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryContractBank>::call(
            this,"OnRspQryContractBank",pContractBank,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryParkedOrder(CThostFtdcParkedOrderField * pParkedOrder,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryParkedOrder>::call(
            this,"OnRspQryParkedOrder",pParkedOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField * pParkedOrderAction,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryParkedOrderAction>::call(
            this,"OnRspQryParkedOrderAction",pParkedOrderAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTradingNotice(CThostFtdcTradingNoticeField * pTradingNotice,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryTradingNotice>::call(
            this,"OnRspQryTradingNotice",pTradingNotice,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField * pBrokerTradingParams,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryBrokerTradingParams>::call(
            this,"OnRspQryBrokerTradingParams",pBrokerTradingParams,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField * pBrokerTradingAlgos,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQryBrokerTradingAlgos>::call(
            this,"OnRspQryBrokerTradingAlgos",pBrokerTradingAlgos,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField * pQueryCFMMCTradingAccountToken,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQueryCFMMCTradingAccountToken>::call(
            this,"OnRspQueryCFMMCTradingAccountToken",pQueryCFMMCTradingAccountToken,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField * pRspTransfer) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnFromBankToFutureByBank>::call(
            this,"OnRtnFromBankToFutureByBank",pRspTransfer
        );
    }
    void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField * pRspTransfer) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnFromFutureToBankByBank>::call(
            this,"OnRtnFromFutureToBankByBank",pRspTransfer
        );
    }
    void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField * pRspRepeal) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnRepealFromBankToFutureByBank>::call(
            this,"OnRtnRepealFromBankToFutureByBank",pRspRepeal
        );
    }
    void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField * pRspRepeal) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnRepealFromFutureToBankByBank>::call(
            this,"OnRtnRepealFromFutureToBankByBank",pRspRepeal
        );
    }
    void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField * pRspTransfer) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnFromBankToFutureByFuture>::call(
            this,"OnRtnFromBankToFutureByFuture",pRspTransfer
        );
    }
    void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField * pRspTransfer) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnFromFutureToBankByFuture>::call(
            this,"OnRtnFromFutureToBankByFuture",pRspTransfer
        );
    }
    void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField * pRspRepeal) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnRepealFromBankToFutureByFutureManual>::call(
            this,"OnRtnRepealFromBankToFutureByFutureManual",pRspRepeal
        );
    }
    void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField * pRspRepeal) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnRepealFromFutureToBankByFutureManual>::call(
            this,"OnRtnRepealFromFutureToBankByFutureManual",pRspRepeal
        );
    }
    void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField * pNotifyQueryAccount) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnQueryBankBalanceByFuture>::call(
            this,"OnRtnQueryBankBalanceByFuture",pNotifyQueryAccount
        );
    }
    void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField * pReqTransfer,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnBankToFutureByFuture>::call(
            this,"OnErrRtnBankToFutureByFuture",pReqTransfer,pRspInfo
        );
    }
    void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField * pReqTransfer,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnFutureToBankByFuture>::call(
            this,"OnErrRtnFutureToBankByFuture",pReqTransfer,pRspInfo
        );
    }
    void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField * pReqRepeal,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnRepealBankToFutureByFutureManual>::call(
            this,"OnErrRtnRepealBankToFutureByFutureManual",pReqRepeal,pRspInfo
        );
    }
    void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField * pReqRepeal,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnRepealFutureToBankByFutureManual>::call(
            this,"OnErrRtnRepealFutureToBankByFutureManual",pReqRepeal,pRspInfo
        );
    }
    void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField * pReqQueryAccount,CThostFtdcRspInfoField * pRspInfo) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnErrRtnQueryBankBalanceByFuture>::call(
            this,"OnErrRtnQueryBankBalanceByFuture",pReqQueryAccount,pRspInfo
        );
    }
    void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField * pRspRepeal) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnRepealFromBankToFutureByFuture>::call(
            this,"OnRtnRepealFromBankToFutureByFuture",pRspRepeal
        );
    }
    void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField * pRspRepeal) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnRepealFromFutureToBankByFuture>::call(
            this,"OnRtnRepealFromFutureToBankByFuture",pRspRepeal
        );
    }
    void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField * pReqTransfer,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspFromBankToFutureByFuture>::call(
            this,"OnRspFromBankToFutureByFuture",pReqTransfer,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField * pReqTransfer,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspFromFutureToBankByFuture>::call(
            this,"OnRspFromFutureToBankByFuture",pReqTransfer,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField * pReqQueryAccount,CThostFtdcRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRspQueryBankAccountMoneyByFuture>::call(
            this,"OnRspQueryBankAccountMoneyByFuture",pReqQueryAccount,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField * pOpenAccount) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnOpenAccountByBank>::call(
            this,"OnRtnOpenAccountByBank",pOpenAccount
        );
    }
    void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField * pCancelAccount) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnCancelAccountByBank>::call(
            this,"OnRtnCancelAccountByBank",pCancelAccount
        );
    }
    void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField * pChangeAccount) override
    {
        return callback_wrapper<&CThostFtdcTraderSpi::OnRtnChangeAccountByBank>::call(
            this,"OnRtnChangeAccountByBank",pChangeAccount
        );
    }

};

class PyCThostFtdcTraderApi : public CThostFtdcTraderApi
{
public:

};

