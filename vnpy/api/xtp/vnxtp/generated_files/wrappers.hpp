#pragma once

#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "generated_functions.h"

#include "xtp_trader_api.h"
#include "xtp_quote_api.h"



class PyTraderSpi : public XTP::API::TraderSpi
{
public:
    void OnDisconnected(uint64_t session_id,int reason) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnDisconnected>::call(
            this,"OnDisconnected",session_id,reason
        );
    }
    void OnError(XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnError>::call(
            this,"OnError",error_info
        );
    }
    void OnOrderEvent(XTPOrderInfo * order_info,XTPRI * error_info,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnOrderEvent>::call(
            this,"OnOrderEvent",order_info,error_info,session_id
        );
    }
    void OnTradeEvent(XTPTradeReport * trade_info,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnTradeEvent>::call(
            this,"OnTradeEvent",trade_info,session_id
        );
    }
    void OnCancelOrderError(XTPOrderCancelInfo * cancel_info,XTPRI * error_info,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnCancelOrderError>::call(
            this,"OnCancelOrderError",cancel_info,error_info,session_id
        );
    }
    void OnQueryOrder(XTPQueryOrderRsp * order_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryOrder>::call(
            this,"OnQueryOrder",order_info,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryTrade(XTPQueryTradeRsp * trade_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryTrade>::call(
            this,"OnQueryTrade",trade_info,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryPosition(XTPQueryStkPositionRsp * position,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryPosition>::call(
            this,"OnQueryPosition",position,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryAsset(XTPQueryAssetRsp * asset,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryAsset>::call(
            this,"OnQueryAsset",asset,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryStructuredFund(XTPStructuredFundInfo * fund_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryStructuredFund>::call(
            this,"OnQueryStructuredFund",fund_info,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryFundTransfer(XTPFundTransferNotice * fund_transfer_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryFundTransfer>::call(
            this,"OnQueryFundTransfer",fund_transfer_info,error_info,request_id,is_last,session_id
        );
    }
    void OnFundTransfer(XTPFundTransferNotice * fund_transfer_info,XTPRI * error_info,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnFundTransfer>::call(
            this,"OnFundTransfer",fund_transfer_info,error_info,session_id
        );
    }
    void OnQueryETF(XTPQueryETFBaseRsp * etf_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryETF>::call(
            this,"OnQueryETF",etf_info,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryETFBasket(XTPQueryETFComponentRsp * etf_component_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryETFBasket>::call(
            this,"OnQueryETFBasket",etf_component_info,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryIPOInfoList(XTPQueryIPOTickerRsp * ipo_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryIPOInfoList>::call(
            this,"OnQueryIPOInfoList",ipo_info,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp * quota_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryIPOQuotaInfo>::call(
            this,"OnQueryIPOQuotaInfo",quota_info,error_info,request_id,is_last,session_id
        );
    }
    void OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp * option_info,XTPRI * error_info,int request_id,bool is_last,uint64_t session_id) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::TraderSpi::OnQueryOptionAuctionInfo>::call(
            this,"OnQueryOptionAuctionInfo",option_info,error_info,request_id,is_last,session_id
        );
    }

};

class PyTraderApi : public XTP::API::TraderApi
{
public:

};

class PyQuoteSpi : public XTP::API::QuoteSpi
{
public:
    void OnDisconnected(int reason) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnDisconnected>::call(
            this,"OnDisconnected",reason
        );
    }
    void OnError(XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnError>::call(
            this,"OnError",error_info
        );
    }
    void OnSubMarketData(XTPST * ticker,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubMarketData>::call(
            this,"OnSubMarketData",ticker,error_info,is_last
        );
    }
    void OnUnSubMarketData(XTPST * ticker,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubMarketData>::call(
            this,"OnUnSubMarketData",ticker,error_info,is_last
        );
    }
    void OnDepthMarketData(XTPMD * market_data,int64_t bid1_qty[],int32_t bid1_count,int32_t max_bid1_count,int64_t ask1_qty[],int32_t ask1_count,int32_t max_ask1_count) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnDepthMarketData>::call(
            this,"OnDepthMarketData",market_data,bid1_qty,bid1_count,max_bid1_count,ask1_qty,ask1_count,max_ask1_count
        );
    }
    void OnSubOrderBook(XTPST * ticker,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubOrderBook>::call(
            this,"OnSubOrderBook",ticker,error_info,is_last
        );
    }
    void OnUnSubOrderBook(XTPST * ticker,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubOrderBook>::call(
            this,"OnUnSubOrderBook",ticker,error_info,is_last
        );
    }
    void OnOrderBook(XTPOB * order_book) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnOrderBook>::call(
            this,"OnOrderBook",order_book
        );
    }
    void OnSubTickByTick(XTPST * ticker,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubTickByTick>::call(
            this,"OnSubTickByTick",ticker,error_info,is_last
        );
    }
    void OnUnSubTickByTick(XTPST * ticker,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubTickByTick>::call(
            this,"OnUnSubTickByTick",ticker,error_info,is_last
        );
    }
    void OnTickByTick(XTPTBT * tbt_data) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnTickByTick>::call(
            this,"OnTickByTick",tbt_data
        );
    }
    void OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubscribeAllMarketData>::call(
            this,"OnSubscribeAllMarketData",exchange_id,error_info
        );
    }
    void OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubscribeAllMarketData>::call(
            this,"OnUnSubscribeAllMarketData",exchange_id,error_info
        );
    }
    void OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubscribeAllOrderBook>::call(
            this,"OnSubscribeAllOrderBook",exchange_id,error_info
        );
    }
    void OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubscribeAllOrderBook>::call(
            this,"OnUnSubscribeAllOrderBook",exchange_id,error_info
        );
    }
    void OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubscribeAllTickByTick>::call(
            this,"OnSubscribeAllTickByTick",exchange_id,error_info
        );
    }
    void OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubscribeAllTickByTick>::call(
            this,"OnUnSubscribeAllTickByTick",exchange_id,error_info
        );
    }
    void OnQueryAllTickers(XTPQSI * ticker_info,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnQueryAllTickers>::call(
            this,"OnQueryAllTickers",ticker_info,error_info,is_last
        );
    }
    void OnQueryTickersPriceInfo(XTPTPI * ticker_info,XTPRI * error_info,bool is_last) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnQueryTickersPriceInfo>::call(
            this,"OnQueryTickersPriceInfo",ticker_info,error_info,is_last
        );
    }
    void OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubscribeAllOptionMarketData>::call(
            this,"OnSubscribeAllOptionMarketData",exchange_id,error_info
        );
    }
    void OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubscribeAllOptionMarketData>::call(
            this,"OnUnSubscribeAllOptionMarketData",exchange_id,error_info
        );
    }
    void OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubscribeAllOptionOrderBook>::call(
            this,"OnSubscribeAllOptionOrderBook",exchange_id,error_info
        );
    }
    void OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubscribeAllOptionOrderBook>::call(
            this,"OnUnSubscribeAllOptionOrderBook",exchange_id,error_info
        );
    }
    void OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnSubscribeAllOptionTickByTick>::call(
            this,"OnSubscribeAllOptionTickByTick",exchange_id,error_info
        );
    }
    void OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id,XTPRI * error_info) override
    {
        return autocxxpy::callback_wrapper<&XTP::API::QuoteSpi::OnUnSubscribeAllOptionTickByTick>::call(
            this,"OnUnSubscribeAllOptionTickByTick",exchange_id,error_info
        );
    }

};

class PyQuoteApi : public XTP::API::QuoteApi
{
public:

};

