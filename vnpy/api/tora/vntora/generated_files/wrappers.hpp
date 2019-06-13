#pragma once
#include "config.h"

#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "generated_functions.h"

#include "TORATstpMdApi.h"
#include "TORATstpTraderApi.h"
#include "TORATstpUserApiDataType.h"
#include "TORATstpUserApiStruct.h"



class PyCTORATstpMdSpi : public CTORATstpMdSpi
{
public:
    void OnFrontConnected() override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnFrontConnected>::call(
            this,"OnFrontConnected"
        );
    }
    void OnFrontDisconnected(int nReason) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnFrontDisconnected>::call(
            this,"OnFrontDisconnected",nReason
        );
    }
    void OnRspError(CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspError>::call(
            this,"OnRspError",pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserLogin(CTORATstpRspUserLoginField * pRspUserLogin,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspUserLogin>::call(
            this,"OnRspUserLogin",pRspUserLogin,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserLogout(CTORATstpUserLogoutField * pUserLogout,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspUserLogout>::call(
            this,"OnRspUserLogout",pUserLogout,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspSubMarketData(CTORATstpSpecificSecurityField * pSpecificSecurity,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspSubMarketData>::call(
            this,"OnRspSubMarketData",pSpecificSecurity,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUnSubMarketData(CTORATstpSpecificSecurityField * pSpecificSecurity,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspUnSubMarketData>::call(
            this,"OnRspUnSubMarketData",pSpecificSecurity,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspSubSpecialMarketData(CTORATstpSpecificSecurityField * pSpecificSecurity,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspSubSpecialMarketData>::call(
            this,"OnRspSubSpecialMarketData",pSpecificSecurity,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUnSubSpecialMarketData(CTORATstpSpecificSecurityField * pSpecificSecurity,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspUnSubSpecialMarketData>::call(
            this,"OnRspUnSubSpecialMarketData",pSpecificSecurity,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspSubFundsFlowMarketData(CTORATstpSpecificSecurityField * pSpecificSecurity,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspSubFundsFlowMarketData>::call(
            this,"OnRspSubFundsFlowMarketData",pSpecificSecurity,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUnSubFundsFlowMarketData(CTORATstpSpecificSecurityField * pSpecificSecurity,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRspUnSubFundsFlowMarketData>::call(
            this,"OnRspUnSubFundsFlowMarketData",pSpecificSecurity,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnDepthMarketData(CTORATstpMarketDataField * pDepthMarketData) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRtnDepthMarketData>::call(
            this,"OnRtnDepthMarketData",pDepthMarketData
        );
    }
    void OnRtnSpecialMarketData(CTORATstpSpecialMarketDataField * pSpecialMarketData) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRtnSpecialMarketData>::call(
            this,"OnRtnSpecialMarketData",pSpecialMarketData
        );
    }
    void OnRtnEffectPriceMarketData(CTORATstpEffectPriceMarketDataField * pEffectPriceMarketData) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRtnEffectPriceMarketData>::call(
            this,"OnRtnEffectPriceMarketData",pEffectPriceMarketData
        );
    }
    void OnRtnEffectVolumeMarketData(CTORATstpEffectVolumeMarketDataField * pEffectVolumeMarketData) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRtnEffectVolumeMarketData>::call(
            this,"OnRtnEffectVolumeMarketData",pEffectVolumeMarketData
        );
    }
    void OnRtnFundsFlowMarketData(CTORATstpFundsFlowMarketDataField * pFundsFlowMarketData) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpMdSpi::OnRtnFundsFlowMarketData>::call(
            this,"OnRtnFundsFlowMarketData",pFundsFlowMarketData
        );
    }

};

class PyCTORATstpMdApi : public CTORATstpMdApi
{
public:

};

class PyCTORATstpTraderSpi : public CTORATstpTraderSpi
{
public:
    void OnFrontConnected() override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnFrontConnected>::call(
            this,"OnFrontConnected"
        );
    }
    void OnFrontDisconnected(int nReason) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnFrontDisconnected>::call(
            this,"OnFrontDisconnected",nReason
        );
    }
    void OnRspError(CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspError>::call(
            this,"OnRspError",pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserLogin(CTORATstpRspUserLoginField * pRspUserLoginField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspUserLogin>::call(
            this,"OnRspUserLogin",pRspUserLoginField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserLogout(CTORATstpUserLogoutField * pUserLogoutField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspUserLogout>::call(
            this,"OnRspUserLogout",pUserLogoutField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspUserPasswordUpdate(CTORATstpUserPasswordUpdateField * pUserPasswordUpdateField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspUserPasswordUpdate>::call(
            this,"OnRspUserPasswordUpdate",pUserPasswordUpdateField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspInputDeviceSerial(CTORATstpRspInputDeviceSerialField * pRspInputDeviceSerialField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspInputDeviceSerial>::call(
            this,"OnRspInputDeviceSerial",pRspInputDeviceSerialField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspOrderInsert(CTORATstpInputOrderField * pInputOrderField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspOrderInsert>::call(
            this,"OnRspOrderInsert",pInputOrderField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnOrder(CTORATstpOrderField * pOrder) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnOrder>::call(
            this,"OnRtnOrder",pOrder
        );
    }
    void OnErrRtnOrderInsert(CTORATstpInputOrderField * pInputOrder,CTORATstpRspInfoField * pRspInfo) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnErrRtnOrderInsert>::call(
            this,"OnErrRtnOrderInsert",pInputOrder,pRspInfo
        );
    }
    void OnRspOrderAction(CTORATstpInputOrderActionField * pInputOrderActionField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspOrderAction>::call(
            this,"OnRspOrderAction",pInputOrderActionField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnErrRtnOrderAction(CTORATstpOrderActionField * pOrderAction,CTORATstpRspInfoField * pRspInfo) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnErrRtnOrderAction>::call(
            this,"OnErrRtnOrderAction",pOrderAction,pRspInfo
        );
    }
    void OnRtnTrade(CTORATstpTradeField * pTrade) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnTrade>::call(
            this,"OnRtnTrade",pTrade
        );
    }
    void OnRtnMarketStatus(CTORATstpMarketStatusField * pMarketStatus) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnMarketStatus>::call(
            this,"OnRtnMarketStatus",pMarketStatus
        );
    }
    void OnRspCondOrderInsert(CTORATstpInputCondOrderField * pInputCondOrderField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspCondOrderInsert>::call(
            this,"OnRspCondOrderInsert",pInputCondOrderField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnCondOrder(CTORATstpConditionOrderField * pConditionOrder) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnCondOrder>::call(
            this,"OnRtnCondOrder",pConditionOrder
        );
    }
    void OnErrRtnCondOrderInsert(CTORATstpInputCondOrderField * pInputCondOrder,CTORATstpRspInfoField * pRspInfo) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnErrRtnCondOrderInsert>::call(
            this,"OnErrRtnCondOrderInsert",pInputCondOrder,pRspInfo
        );
    }
    void OnRspCondOrderAction(CTORATstpInputCondOrderActionField * pInputCondOrderActionField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspCondOrderAction>::call(
            this,"OnRspCondOrderAction",pInputCondOrderActionField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnErrRtnCondOrderAction(CTORATstpInputCondOrderActionField * pInputCondOrderAction,CTORATstpRspInfoField * pRspInfo) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnErrRtnCondOrderAction>::call(
            this,"OnErrRtnCondOrderAction",pInputCondOrderAction,pRspInfo
        );
    }
    void OnRspInquiryJZFund(CTORATstpRspInquiryJZFundField * pRspInquiryJZFundField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspInquiryJZFund>::call(
            this,"OnRspInquiryJZFund",pRspInquiryJZFundField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspTransferFund(CTORATstpInputTransferFundField * pInputTransferFundField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspTransferFund>::call(
            this,"OnRspTransferFund",pInputTransferFundField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnTransferFund(CTORATstpTransferFundField * pTransferFund) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnTransferFund>::call(
            this,"OnRtnTransferFund",pTransferFund
        );
    }
    void OnErrRtnTransferFund(CTORATstpInputTransferFundField * pInputTransferFund,CTORATstpRspInfoField * pRspInfo) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnErrRtnTransferFund>::call(
            this,"OnErrRtnTransferFund",pInputTransferFund,pRspInfo
        );
    }
    void OnRtnTransferPosition(CTORATstpTransferPositionField * pTransferPosition) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnTransferPosition>::call(
            this,"OnRtnTransferPosition",pTransferPosition
        );
    }
    void OnErrRtnTransferPosition(CTORATstpInputTransferPositionField * pInputTransferPosition,CTORATstpRspInfoField * pRspInfo) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnErrRtnTransferPosition>::call(
            this,"OnErrRtnTransferPosition",pInputTransferPosition,pRspInfo
        );
    }
    void OnRspTransferCollateral(CTORATstpInputTransferCollateralField * pInputTransferCollateralField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspTransferCollateral>::call(
            this,"OnRspTransferCollateral",pInputTransferCollateralField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspInquiryBankAccountFund(CTORATstpRspInquiryBankAccountFundField * pRspInquiryBankAccountFundField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspInquiryBankAccountFund>::call(
            this,"OnRspInquiryBankAccountFund",pRspInquiryBankAccountFundField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspInquiryTradeConcentration(CTORATstpInquiryTradeConcentrationField * pInquiryTradeConcentrationField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspInquiryTradeConcentration>::call(
            this,"OnRspInquiryTradeConcentration",pInquiryTradeConcentrationField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnTradingNotice(CTORATstpTradingNoticeField * pTradingNotice) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnTradingNotice>::call(
            this,"OnRtnTradingNotice",pTradingNotice
        );
    }
    void OnRspInquiryMaxOrderVolume(CTORATstpRspInquiryMaxOrderVolumeField * pRspInquiryMaxOrderVolumeField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspInquiryMaxOrderVolume>::call(
            this,"OnRspInquiryMaxOrderVolume",pRspInquiryMaxOrderVolumeField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRtnPeripheryTransferPosition(CTORATstpPeripheryPositionTransferDetailField * pPeripheryPositionTransferDetail) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRtnPeripheryTransferPosition>::call(
            this,"OnRtnPeripheryTransferPosition",pPeripheryPositionTransferDetail
        );
    }
    void OnRspInquiryHistoryOrder(CTORATstpHistoryOrderField * pHistoryOrderField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspInquiryHistoryOrder>::call(
            this,"OnRspInquiryHistoryOrder",pHistoryOrderField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspInquiryHistoryTrade(CTORATstpHistoryTradeField * pHistoryTradeField,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspInquiryHistoryTrade>::call(
            this,"OnRspInquiryHistoryTrade",pHistoryTradeField,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryExchange(CTORATstpExchangeField * pExchange,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryExchange>::call(
            this,"OnRspQryExchange",pExchange,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryMarketData(CTORATstpMarketDataField * pMarketData,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryMarketData>::call(
            this,"OnRspQryMarketData",pMarketData,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQrySecurity(CTORATstpSecurityField * pSecurity,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQrySecurity>::call(
            this,"OnRspQrySecurity",pSecurity,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryETFFile(CTORATstpETFFileField * pETFFile,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryETFFile>::call(
            this,"OnRspQryETFFile",pETFFile,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryETFBasket(CTORATstpETFBasketField * pETFBasket,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryETFBasket>::call(
            this,"OnRspQryETFBasket",pETFBasket,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryIPOInfo(CTORATstpIPOInfoField * pIPOInfo,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryIPOInfo>::call(
            this,"OnRspQryIPOInfo",pIPOInfo,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryBUProxy(CTORATstpBUProxyField * pBUProxy,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryBUProxy>::call(
            this,"OnRspQryBUProxy",pBUProxy,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryUser(CTORATstpUserField * pUser,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryUser>::call(
            this,"OnRspQryUser",pUser,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestor(CTORATstpInvestorField * pInvestor,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryInvestor>::call(
            this,"OnRspQryInvestor",pInvestor,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryShareholderAccount(CTORATstpShareholderAccountField * pShareholderAccount,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryShareholderAccount>::call(
            this,"OnRspQryShareholderAccount",pShareholderAccount,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryOrder(CTORATstpOrderField * pOrder,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryOrder>::call(
            this,"OnRspQryOrder",pOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryOrderAction(CTORATstpOrderActionField * pOrderAction,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryOrderAction>::call(
            this,"OnRspQryOrderAction",pOrderAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTrade(CTORATstpTradeField * pTrade,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryTrade>::call(
            this,"OnRspQryTrade",pTrade,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTradingAccount(CTORATstpTradingAccountField * pTradingAccount,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryTradingAccount>::call(
            this,"OnRspQryTradingAccount",pTradingAccount,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryPosition(CTORATstpPositionField * pPosition,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryPosition>::call(
            this,"OnRspQryPosition",pPosition,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTradingFee(CTORATstpTradingFeeField * pTradingFee,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryTradingFee>::call(
            this,"OnRspQryTradingFee",pTradingFee,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestorTradingFee(CTORATstpInvestorTradingFeeField * pInvestorTradingFee,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryInvestorTradingFee>::call(
            this,"OnRspQryInvestorTradingFee",pInvestorTradingFee,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryIPOQuota(CTORATstpIPOQuotaField * pIPOQuota,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryIPOQuota>::call(
            this,"OnRspQryIPOQuota",pIPOQuota,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryMarket(CTORATstpMarketField * pMarket,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryMarket>::call(
            this,"OnRspQryMarket",pMarket,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryOrderFundDetail(CTORATstpOrderFundDetailField * pOrderFundDetail,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryOrderFundDetail>::call(
            this,"OnRspQryOrderFundDetail",pOrderFundDetail,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryFundTransferDetail(CTORATstpFundTransferDetailField * pFundTransferDetail,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryFundTransferDetail>::call(
            this,"OnRspQryFundTransferDetail",pFundTransferDetail,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryPositionTransferDetail(CTORATstpPositionTransferDetailField * pPositionTransferDetail,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryPositionTransferDetail>::call(
            this,"OnRspQryPositionTransferDetail",pPositionTransferDetail,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryPledgePosition(CTORATstpPledgePositionField * pPledgePosition,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryPledgePosition>::call(
            this,"OnRspQryPledgePosition",pPledgePosition,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryPledgeInfo(CTORATstpPledgeInfoField * pPledgeInfo,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryPledgeInfo>::call(
            this,"OnRspQryPledgeInfo",pPledgeInfo,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryConversionBondInfo(CTORATstpConversionBondInfoField * pConversionBondInfo,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryConversionBondInfo>::call(
            this,"OnRspQryConversionBondInfo",pConversionBondInfo,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryBondPutbackInfo(CTORATstpBondPutbackInfoField * pBondPutbackInfo,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryBondPutbackInfo>::call(
            this,"OnRspQryBondPutbackInfo",pBondPutbackInfo,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryStandardBondPosition(CTORATstpStandardBondPositionField * pStandardBondPosition,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryStandardBondPosition>::call(
            this,"OnRspQryStandardBondPosition",pStandardBondPosition,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQrySpecialMarketData(CTORATstpSpecialMarketDataField * pSpecialMarketData,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQrySpecialMarketData>::call(
            this,"OnRspQrySpecialMarketData",pSpecialMarketData,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryPrematurityRepoOrder(CTORATstpPrematurityRepoOrderField * pPrematurityRepoOrder,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryPrematurityRepoOrder>::call(
            this,"OnRspQryPrematurityRepoOrder",pPrematurityRepoOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryShareholderParam(CTORATstpShareholderParamField * pShareholderParam,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryShareholderParam>::call(
            this,"OnRspQryShareholderParam",pShareholderParam,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryPeripheryPositionTransferDetail(CTORATstpPeripheryPositionTransferDetailField * pPeripheryPositionTransferDetail,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryPeripheryPositionTransferDetail>::call(
            this,"OnRspQryPeripheryPositionTransferDetail",pPeripheryPositionTransferDetail,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryInvestorCondOrderLimitParam(CTORATstpInvestorCondOrderLimitParamField * pInvestorCondOrderLimitParam,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryInvestorCondOrderLimitParam>::call(
            this,"OnRspQryInvestorCondOrderLimitParam",pInvestorCondOrderLimitParam,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryCondOrder(CTORATstpCondOrderField * pCondOrder,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryCondOrder>::call(
            this,"OnRspQryCondOrder",pCondOrder,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryCondOrderAction(CTORATstpCondOrderActionField * pCondOrderAction,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryCondOrderAction>::call(
            this,"OnRspQryCondOrderAction",pCondOrderAction,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryTradingNotice(CTORATstpTradingNoticeField * pTradingNotice,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryTradingNotice>::call(
            this,"OnRspQryTradingNotice",pTradingNotice,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryIPONumberResult(CTORATstpIPONumberResultField * pIPONumberResult,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryIPONumberResult>::call(
            this,"OnRspQryIPONumberResult",pIPONumberResult,pRspInfo,nRequestID,bIsLast
        );
    }
    void OnRspQryIPOMatchNumberResult(CTORATstpIPOMatchNumberResultField * pIPOMatchNumberResult,CTORATstpRspInfoField * pRspInfo,int nRequestID,bool bIsLast) override
    {
        return autocxxpy::callback_wrapper<&CTORATstpTraderSpi::OnRspQryIPOMatchNumberResult>::call(
            this,"OnRspQryIPOMatchNumberResult",pIPOMatchNumberResult,pRspInfo,nRequestID,bIsLast
        );
    }

};

class PyCTORATstpTraderApi : public CTORATstpTraderApi
{
public:

};

