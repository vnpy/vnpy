#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <c2py/c2py.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"


void generate_class_ITapTrade_TapAPIOrderMarketDeleteReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderMarketDeleteReq
    pybind11::class_<ITapTrade::TapAPIOrderMarketDeleteReq> c(parent, "TapAPIOrderMarketDeleteReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketDeleteReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderMarketDeleteReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderMarketDeleteReq::OrderBuyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, "OrderBuyNo", OrderBuyNo);
    // ITapTrade::TapAPIOrderMarketDeleteReq::OrderSellNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, "OrderSellNo", OrderSellNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderMarketDeleteReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalRemoveReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderLocalRemoveReq
    pybind11::class_<ITapTrade::TapAPIOrderLocalRemoveReq> c(parent, "TapAPIOrderLocalRemoveReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalRemoveReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderLocalRemoveReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderLocalRemoveReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalRemoveReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalRemoveRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderLocalRemoveRsp
    pybind11::class_<ITapTrade::TapAPIOrderLocalRemoveRsp> c(parent, "TapAPIOrderLocalRemoveRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalRemoveRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderLocalRemoveRsp::req
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "req", req);
    // ITapTrade::TapAPIOrderLocalRemoveRsp::ClientLocalIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientLocalIP", ClientLocalIP);
    // ITapTrade::TapAPIOrderLocalRemoveRsp::ClientMac
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientMac", ClientMac);
    // ITapTrade::TapAPIOrderLocalRemoveRsp::ClientIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientIP", ClientIP);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalRemoveRsp", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalInputReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderLocalInputReq
    pybind11::class_<ITapTrade::TapAPIOrderLocalInputReq> c(parent, "TapAPIOrderLocalInputReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalInputReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderLocalInputReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIOrderLocalInputReq::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIOrderLocalInputReq::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CommodityType", CommodityType);
    // ITapTrade::TapAPIOrderLocalInputReq::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIOrderLocalInputReq::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ContractNo", ContractNo);
    // ITapTrade::TapAPIOrderLocalInputReq::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIOrderLocalInputReq::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIOrderLocalInputReq::ContractNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ContractNo2", ContractNo2);
    // ITapTrade::TapAPIOrderLocalInputReq::StrikePrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "StrikePrice2", StrikePrice2);
    // ITapTrade::TapAPIOrderLocalInputReq::CallOrPutFlag2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CallOrPutFlag2", CallOrPutFlag2);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderType", OrderType);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSource", OrderSource);
    // ITapTrade::TapAPIOrderLocalInputReq::TimeInForce
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "TimeInForce", TimeInForce);
    // ITapTrade::TapAPIOrderLocalInputReq::ExpireTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ExpireTime", ExpireTime);
    // ITapTrade::TapAPIOrderLocalInputReq::IsRiskOrder
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "IsRiskOrder", IsRiskOrder);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSide", OrderSide);
    // ITapTrade::TapAPIOrderLocalInputReq::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPIOrderLocalInputReq::PositionEffect2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "PositionEffect2", PositionEffect2);
    // ITapTrade::TapAPIOrderLocalInputReq::InquiryNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "InquiryNo", InquiryNo);
    // ITapTrade::TapAPIOrderLocalInputReq::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderPrice", OrderPrice);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderPrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderPrice2", OrderPrice2);
    // ITapTrade::TapAPIOrderLocalInputReq::StopPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "StopPrice", StopPrice);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderQty", OrderQty);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMinQty", OrderMinQty);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSystemNo", OrderSystemNo);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderExchangeSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    // ITapTrade::TapAPIOrderLocalInputReq::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "UpperNo", UpperNo);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderMatchPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchPrice", OrderMatchPrice);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderMatchPrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchPrice2", OrderMatchPrice2);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderMatchQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchQty", OrderMatchQty);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderMatchQty2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchQty2", OrderMatchQty2);
    // ITapTrade::TapAPIOrderLocalInputReq::OrderState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderState", OrderState);
    // ITapTrade::TapAPIOrderLocalInputReq::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalInputReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalModifyReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderLocalModifyReq
    pybind11::class_<ITapTrade::TapAPIOrderLocalModifyReq> c(parent, "TapAPIOrderLocalModifyReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalModifyReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderLocalModifyReq::req
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, "req", req);
    // ITapTrade::TapAPIOrderLocalModifyReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderLocalModifyReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalModifyReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalTransferReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderLocalTransferReq
    pybind11::class_<ITapTrade::TapAPIOrderLocalTransferReq> c(parent, "TapAPIOrderLocalTransferReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalTransferReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderLocalTransferReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIOrderLocalTransferReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderLocalTransferReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalTransferReq", c);
}
void generate_class_ITapTrade_TapAPIFillLocalInputReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIFillLocalInputReq
    pybind11::class_<ITapTrade::TapAPIFillLocalInputReq> c(parent, "TapAPIFillLocalInputReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillLocalInputReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIFillLocalInputReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIFillLocalInputReq::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIFillLocalInputReq::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "CommodityType", CommodityType);
    // ITapTrade::TapAPIFillLocalInputReq::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIFillLocalInputReq::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "ContractNo", ContractNo);
    // ITapTrade::TapAPIFillLocalInputReq::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIFillLocalInputReq::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIFillLocalInputReq::MatchSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchSide", MatchSide);
    // ITapTrade::TapAPIFillLocalInputReq::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPIFillLocalInputReq::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPIFillLocalInputReq::MatchPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchPrice", MatchPrice);
    // ITapTrade::TapAPIFillLocalInputReq::MatchQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchQty", MatchQty);
    // ITapTrade::TapAPIFillLocalInputReq::OrderSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "OrderSystemNo", OrderSystemNo);
    // ITapTrade::TapAPIFillLocalInputReq::UpperMatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "UpperMatchNo", UpperMatchNo);
    // ITapTrade::TapAPIFillLocalInputReq::MatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchDateTime", MatchDateTime);
    // ITapTrade::TapAPIFillLocalInputReq::UpperMatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "UpperMatchDateTime", UpperMatchDateTime);
    // ITapTrade::TapAPIFillLocalInputReq::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "UpperNo", UpperNo);
    // ITapTrade::TapAPIFillLocalInputReq::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "IsAddOne", IsAddOne);
    // ITapTrade::TapAPIFillLocalInputReq::FeeCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "FeeCurrencyGroup", FeeCurrencyGroup);
    // ITapTrade::TapAPIFillLocalInputReq::FeeCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "FeeCurrency", FeeCurrency);
    // ITapTrade::TapAPIFillLocalInputReq::FeeValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "FeeValue", FeeValue);
    // ITapTrade::TapAPIFillLocalInputReq::IsManualFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "IsManualFee", IsManualFee);
    // ITapTrade::TapAPIFillLocalInputReq::ClosePositionPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "ClosePositionPrice", ClosePositionPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillLocalInputReq", c);
}
void generate_class_ITapTrade_TapAPIFillLocalRemoveReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIFillLocalRemoveReq
    pybind11::class_<ITapTrade::TapAPIFillLocalRemoveReq> c(parent, "TapAPIFillLocalRemoveReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillLocalRemoveReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIFillLocalRemoveReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalRemoveReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIFillLocalRemoveReq::MatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalRemoveReq, "MatchNo", MatchNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillLocalRemoveReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillLocalRemoveReq", c);
}
void generate_class_ITapTrade_TapAPITradingCalendarQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPITradingCalendarQryRsp
    pybind11::class_<ITapTrade::TapAPITradingCalendarQryRsp> c(parent, "TapAPITradingCalendarQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradingCalendarQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPITradingCalendarQryRsp::CurrTradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "CurrTradeDate", CurrTradeDate);
    // ITapTrade::TapAPITradingCalendarQryRsp::LastSettlementDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "LastSettlementDate", LastSettlementDate);
    // ITapTrade::TapAPITradingCalendarQryRsp::PromptDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "PromptDate", PromptDate);
    // ITapTrade::TapAPITradingCalendarQryRsp::LastPromptDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "LastPromptDate", LastPromptDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradingCalendarQryRsp", c);
}
