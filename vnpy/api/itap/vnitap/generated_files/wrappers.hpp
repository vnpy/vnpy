#pragma once

#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "generated_functions.h"

#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"



class PyITapQuoteAPINotify : public ITapQuoteAPINotify
{
public:
    void OnRspLogin(TAPIINT32 errorCode,const TapAPIQuotLoginRspInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnRspLogin>::call(
            this,"OnRspLogin",errorCode,info
        );
    }
    void OnAPIReady() override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnAPIReady>::call(
            this,"OnAPIReady"
        );
    }
    void OnDisconnect(TAPIINT32 reasonCode) override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnDisconnect>::call(
            this,"OnDisconnect",reasonCode
        );
    }
    void OnRspQryCommodity(TAPIUINT32 sessionID,TAPIINT32 errorCode,TAPIYNFLAG isLast,const TapAPIQuoteCommodityInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnRspQryCommodity>::call(
            this,"OnRspQryCommodity",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryContract(TAPIUINT32 sessionID,TAPIINT32 errorCode,TAPIYNFLAG isLast,const TapAPIQuoteContractInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnRspQryContract>::call(
            this,"OnRspQryContract",sessionID,errorCode,isLast,info
        );
    }
    void OnRspSubscribeQuote(TAPIUINT32 sessionID,TAPIINT32 errorCode,TAPIYNFLAG isLast,const TapAPIQuoteWhole * info) override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnRspSubscribeQuote>::call(
            this,"OnRspSubscribeQuote",sessionID,errorCode,isLast,info
        );
    }
    void OnRspUnSubscribeQuote(TAPIUINT32 sessionID,TAPIINT32 errorCode,TAPIYNFLAG isLast,const TapAPIContract * info) override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnRspUnSubscribeQuote>::call(
            this,"OnRspUnSubscribeQuote",sessionID,errorCode,isLast,info
        );
    }
    void OnRtnQuote(const TapAPIQuoteWhole * info) override
    {
        return autocxxpy::callback_wrapper<&ITapQuoteAPINotify::OnRtnQuote>::call(
            this,"OnRtnQuote",info
        );
    }

};

class PyITapQuoteAPI : public ITapQuoteAPI
{
public:

};

class PyITapTradeAPINotify : public ITapTrade::ITapTradeAPINotify
{
public:
    void OnConnect() override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnConnect>::call(
            this,"OnConnect"
        );
    }
    void OnRspLogin(ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPITradeLoginRspInfo * loginRspInfo) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspLogin>::call(
            this,"OnRspLogin",errorCode,loginRspInfo
        );
    }
    void OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TAPISTR_40 ContactInfo) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnContactInfo>::call(
            this,"OnRtnContactInfo",errorCode,isLast,ContactInfo
        );
    }
    void OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIRequestVertificateCodeRsp * rsp) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspRequestVertificateCode>::call(
            this,"OnRspRequestVertificateCode",sessionID,errorCode,rsp
        );
    }
    void OnExpriationDate(ITapTrade::TAPIDATE date,int days) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnExpriationDate>::call(
            this,"OnExpriationDate",date,days
        );
    }
    void OnAPIReady(ITapTrade::TAPIINT32 errorCode) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnAPIReady>::call(
            this,"OnAPIReady",errorCode
        );
    }
    void OnDisconnect(ITapTrade::TAPIINT32 reasonCode) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnDisconnect>::call(
            this,"OnDisconnect",reasonCode
        );
    }
    void OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspChangePassword>::call(
            this,"OnRspChangePassword",sessionID,errorCode
        );
    }
    void OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspAuthPassword>::call(
            this,"OnRspAuthPassword",sessionID,errorCode
        );
    }
    void OnRspQryTradingDate(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPITradingCalendarQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryTradingDate>::call(
            this,"OnRspQryTradingDate",sessionID,errorCode,info
        );
    }
    void OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TAPISTR_50 info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspSetReservedInfo>::call(
            this,"OnRspSetReservedInfo",sessionID,errorCode,info
        );
    }
    void OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIUINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIAccountInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryAccount>::call(
            this,"OnRspQryAccount",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryFund(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIFundData * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryFund>::call(
            this,"OnRspQryFund",sessionID,errorCode,isLast,info
        );
    }
    void OnRtnFund(const ITapTrade::TapAPIFundData * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnFund>::call(
            this,"OnRtnFund",info
        );
    }
    void OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIExchangeInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryExchange>::call(
            this,"OnRspQryExchange",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPICommodityInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryCommodity>::call(
            this,"OnRspQryCommodity",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryContract(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPITradeContractInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryContract>::call(
            this,"OnRspQryContract",sessionID,errorCode,isLast,info
        );
    }
    void OnRtnContract(const ITapTrade::TapAPITradeContractInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnContract>::call(
            this,"OnRtnContract",info
        );
    }
    void OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIOrderActionRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderAction>::call(
            this,"OnRspOrderAction",sessionID,errorCode,info
        );
    }
    void OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnOrder>::call(
            this,"OnRtnOrder",info
        );
    }
    void OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIOrderInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryOrder>::call(
            this,"OnRspQryOrder",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIOrderInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryOrderProcess>::call(
            this,"OnRspQryOrderProcess",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryFill(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIFillInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryFill>::call(
            this,"OnRspQryFill",sessionID,errorCode,isLast,info
        );
    }
    void OnRtnFill(const ITapTrade::TapAPIFillInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnFill>::call(
            this,"OnRtnFill",info
        );
    }
    void OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIPositionInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryPosition>::call(
            this,"OnRspQryPosition",sessionID,errorCode,isLast,info
        );
    }
    void OnRtnPosition(const ITapTrade::TapAPIPositionInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnPosition>::call(
            this,"OnRtnPosition",info
        );
    }
    void OnRspQryPositionSummary(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIPositionSummary * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryPositionSummary>::call(
            this,"OnRspQryPositionSummary",sessionID,errorCode,isLast,info
        );
    }
    void OnRtnPositionSummary(const ITapTrade::TapAPIPositionSummary * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnPositionSummary>::call(
            this,"OnRtnPositionSummary",info
        );
    }
    void OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit>::call(
            this,"OnRtnPositionProfit",info
        );
    }
    void OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPICurrencyInfo * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryCurrency>::call(
            this,"OnRspQryCurrency",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPITradeMessage * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryTradeMessage>::call(
            this,"OnRspQryTradeMessage",sessionID,errorCode,isLast,info
        );
    }
    void OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnTradeMessage>::call(
            this,"OnRtnTradeMessage",info
        );
    }
    void OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIHisOrderQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryHisOrder>::call(
            this,"OnRspQryHisOrder",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIHisOrderProcessQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryHisOrderProcess>::call(
            this,"OnRspQryHisOrderProcess",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIHisMatchQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryHisMatch>::call(
            this,"OnRspQryHisMatch",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIHisPositionQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryHisPosition>::call(
            this,"OnRspQryHisPosition",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIHisDeliveryQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryHisDelivery>::call(
            this,"OnRspQryHisDelivery",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIAccountCashAdjustQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryAccountCashAdjust>::call(
            this,"OnRspQryAccountCashAdjust",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryBill(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIBillQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryBill>::call(
            this,"OnRspQryBill",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIAccountFeeRentQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryAccountFeeRent>::call(
            this,"OnRspQryAccountFeeRent",sessionID,errorCode,isLast,info
        );
    }
    void OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,ITapTrade::TAPIYNFLAG isLast,const ITapTrade::TapAPIAccountMarginRentQryRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspQryAccountMarginRent>::call(
            this,"OnRspQryAccountMarginRent",sessionID,errorCode,isLast,info
        );
    }
    void OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIOrderMarketInsertRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderInsert>::call(
            this,"OnRspHKMarketOrderInsert",sessionID,errorCode,info
        );
    }
    void OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIOrderMarketDeleteRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderDelete>::call(
            this,"OnRspHKMarketOrderDelete",sessionID,errorCode,info
        );
    }
    void OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnHKMarketQuoteNotice>::call(
            this,"OnHKMarketQuoteNotice",info
        );
    }
    void OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIOrderLocalRemoveRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderLocalRemove>::call(
            this,"OnRspOrderLocalRemove",sessionID,errorCode,info
        );
    }
    void OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIOrderLocalInputRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderLocalInput>::call(
            this,"OnRspOrderLocalInput",sessionID,errorCode,info
        );
    }
    void OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIOrderLocalModifyRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderLocalModify>::call(
            this,"OnRspOrderLocalModify",sessionID,errorCode,info
        );
    }
    void OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIOrderLocalTransferRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderLocalTransfer>::call(
            this,"OnRspOrderLocalTransfer",sessionID,errorCode,info
        );
    }
    void OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIFillLocalInputRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspFillLocalInput>::call(
            this,"OnRspFillLocalInput",sessionID,errorCode,info
        );
    }
    void OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode,const ITapTrade::TapAPIFillLocalRemoveRsp * info) override
    {
        return autocxxpy::callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspFillLocalRemove>::call(
            this,"OnRspFillLocalRemove",sessionID,errorCode,info
        );
    }

};

class PyITapTradeAPI : public ITapTrade::ITapTradeAPI
{
public:

};

