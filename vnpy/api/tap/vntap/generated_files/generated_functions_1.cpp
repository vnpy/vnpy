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


void generate_class_ITapTrade_TapAPIOrderQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderQryReq
    pybind11::class_<ITapTrade::TapAPIOrderQryReq> c(parent, "TapAPIOrderQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIOrderQryReq::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIOrderQryReq::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "CommodityType", CommodityType);
    // ITapTrade::TapAPIOrderQryReq::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIOrderQryReq::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "OrderType", OrderType);
    // ITapTrade::TapAPIOrderQryReq::OrderSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "OrderSource", OrderSource);
    // ITapTrade::TapAPIOrderQryReq::TimeInForce
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "TimeInForce", TimeInForce);
    // ITapTrade::TapAPIOrderQryReq::ExpireTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "ExpireTime", ExpireTime);
    // ITapTrade::TapAPIOrderQryReq::IsRiskOrder
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsRiskOrder", IsRiskOrder);
    // ITapTrade::TapAPIOrderQryReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderQryReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "OrderNo", OrderNo);
    // ITapTrade::TapAPIOrderQryReq::IsBackInput
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsBackInput", IsBackInput);
    // ITapTrade::TapAPIOrderQryReq::IsDeleted
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsDeleted", IsDeleted);
    // ITapTrade::TapAPIOrderQryReq::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderQryReq", c);
}
void generate_class_ITapTrade_TapAPIOrderProcessQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderProcessQryReq
    pybind11::class_<ITapTrade::TapAPIOrderProcessQryReq> c(parent, "TapAPIOrderProcessQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderProcessQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderProcessQryReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderProcessQryReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderProcessQryReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderProcessQryReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderProcessQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderProcessQryReq", c);
}
void generate_class_ITapTrade_TapAPIFillQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIFillQryReq
    pybind11::class_<ITapTrade::TapAPIFillQryReq> c(parent, "TapAPIFillQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIFillQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIFillQryReq::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIFillQryReq::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "CommodityType", CommodityType);
    // ITapTrade::TapAPIFillQryReq::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIFillQryReq::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "ContractNo", ContractNo);
    // ITapTrade::TapAPIFillQryReq::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIFillQryReq::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIFillQryReq::MatchSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "MatchSource", MatchSource);
    // ITapTrade::TapAPIFillQryReq::MatchSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "MatchSide", MatchSide);
    // ITapTrade::TapAPIFillQryReq::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPIFillQryReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIFillQryReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "OrderNo", OrderNo);
    // ITapTrade::TapAPIFillQryReq::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "UpperNo", UpperNo);
    // ITapTrade::TapAPIFillQryReq::IsDeleted
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "IsDeleted", IsDeleted);
    // ITapTrade::TapAPIFillQryReq::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillQryReq", c);
}
void generate_class_ITapTrade_TapAPIFillInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPIFillInfo
    pybind11::class_<ITapTrade::TapAPIFillInfo> c(parent, "TapAPIFillInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIFillInfo::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "AccountNo", AccountNo);
    // ITapTrade::TapAPIFillInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIFillInfo::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "CommodityType", CommodityType);
    // ITapTrade::TapAPIFillInfo::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIFillInfo::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ContractNo", ContractNo);
    // ITapTrade::TapAPIFillInfo::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIFillInfo::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIFillInfo::MatchSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchSource", MatchSource);
    // ITapTrade::TapAPIFillInfo::MatchSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchSide", MatchSide);
    // ITapTrade::TapAPIFillInfo::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPIFillInfo::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIFillInfo::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "OrderNo", OrderNo);
    // ITapTrade::TapAPIFillInfo::OrderSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "OrderSystemNo", OrderSystemNo);
    // ITapTrade::TapAPIFillInfo::MatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchNo", MatchNo);
    // ITapTrade::TapAPIFillInfo::UpperMatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "UpperMatchNo", UpperMatchNo);
    // ITapTrade::TapAPIFillInfo::ExchangeMatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ExchangeMatchNo", ExchangeMatchNo);
    // ITapTrade::TapAPIFillInfo::MatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchDateTime", MatchDateTime);
    // ITapTrade::TapAPIFillInfo::UpperMatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "UpperMatchDateTime", UpperMatchDateTime);
    // ITapTrade::TapAPIFillInfo::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "UpperNo", UpperNo);
    // ITapTrade::TapAPIFillInfo::MatchPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchPrice", MatchPrice);
    // ITapTrade::TapAPIFillInfo::MatchQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchQty", MatchQty);
    // ITapTrade::TapAPIFillInfo::IsDeleted
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "IsDeleted", IsDeleted);
    // ITapTrade::TapAPIFillInfo::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "IsAddOne", IsAddOne);
    // ITapTrade::TapAPIFillInfo::FeeCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "FeeCurrencyGroup", FeeCurrencyGroup);
    // ITapTrade::TapAPIFillInfo::FeeCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "FeeCurrency", FeeCurrency);
    // ITapTrade::TapAPIFillInfo::FeeValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "FeeValue", FeeValue);
    // ITapTrade::TapAPIFillInfo::IsManualFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "IsManualFee", IsManualFee);
    // ITapTrade::TapAPIFillInfo::ClosePrositionPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ClosePrositionPrice", ClosePrositionPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillInfo", c);
}
void generate_class_ITapTrade_TapAPICloseQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPICloseQryReq
    pybind11::class_<ITapTrade::TapAPICloseQryReq> c(parent, "TapAPICloseQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICloseQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPICloseQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPICloseQryReq::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPICloseQryReq::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "CommodityType", CommodityType);
    // ITapTrade::TapAPICloseQryReq::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICloseQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICloseQryReq", c);
}
void generate_class_ITapTrade_TapAPICloseInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPICloseInfo
    pybind11::class_<ITapTrade::TapAPICloseInfo> c(parent, "TapAPICloseInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICloseInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPICloseInfo::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "AccountNo", AccountNo);
    // ITapTrade::TapAPICloseInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPICloseInfo::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityType", CommodityType);
    // ITapTrade::TapAPICloseInfo::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPICloseInfo::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "ContractNo", ContractNo);
    // ITapTrade::TapAPICloseInfo::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPICloseInfo::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPICloseInfo::CloseSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseSide", CloseSide);
    // ITapTrade::TapAPICloseInfo::CloseQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseQty", CloseQty);
    // ITapTrade::TapAPICloseInfo::OpenPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "OpenPrice", OpenPrice);
    // ITapTrade::TapAPICloseInfo::ClosePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "ClosePrice", ClosePrice);
    // ITapTrade::TapAPICloseInfo::OpenMatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "OpenMatchNo", OpenMatchNo);
    // ITapTrade::TapAPICloseInfo::OpenMatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "OpenMatchDateTime", OpenMatchDateTime);
    // ITapTrade::TapAPICloseInfo::CloseMatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseMatchNo", CloseMatchNo);
    // ITapTrade::TapAPICloseInfo::CloseMatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseMatchDateTime", CloseMatchDateTime);
    // ITapTrade::TapAPICloseInfo::CloseStreamId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseStreamId", CloseStreamId);
    // ITapTrade::TapAPICloseInfo::CommodityCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    // ITapTrade::TapAPICloseInfo::CommodityCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityCurrency", CommodityCurrency);
    // ITapTrade::TapAPICloseInfo::CloseProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseProfit", CloseProfit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICloseInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICloseInfo", c);
}
void generate_class_ITapTrade_TapAPIPositionQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIPositionQryReq
    pybind11::class_<ITapTrade::TapAPIPositionQryReq> c(parent, "TapAPIPositionQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIPositionQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionQryReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionQryReq", c);
}
void generate_class_ITapTrade_TapAPIPositionInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPIPositionInfo
    pybind11::class_<ITapTrade::TapAPIPositionInfo> c(parent, "TapAPIPositionInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIPositionInfo::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "AccountNo", AccountNo);
    // ITapTrade::TapAPIPositionInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIPositionInfo::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityType", CommodityType);
    // ITapTrade::TapAPIPositionInfo::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIPositionInfo::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "ContractNo", ContractNo);
    // ITapTrade::TapAPIPositionInfo::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIPositionInfo::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIPositionInfo::MatchSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "MatchSide", MatchSide);
    // ITapTrade::TapAPIPositionInfo::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPIPositionInfo::PositionNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionNo", PositionNo);
    // ITapTrade::TapAPIPositionInfo::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIPositionInfo::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "OrderNo", OrderNo);
    // ITapTrade::TapAPIPositionInfo::MatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "MatchNo", MatchNo);
    // ITapTrade::TapAPIPositionInfo::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "UpperNo", UpperNo);
    // ITapTrade::TapAPIPositionInfo::PositionPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionPrice", PositionPrice);
    // ITapTrade::TapAPIPositionInfo::PositionQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionQty", PositionQty);
    // ITapTrade::TapAPIPositionInfo::PositionStreamId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionStreamId", PositionStreamId);
    // ITapTrade::TapAPIPositionInfo::CommodityCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    // ITapTrade::TapAPIPositionInfo::CommodityCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityCurrency", CommodityCurrency);
    // ITapTrade::TapAPIPositionInfo::CalculatePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CalculatePrice", CalculatePrice);
    // ITapTrade::TapAPIPositionInfo::AccountInitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "AccountInitialMargin", AccountInitialMargin);
    // ITapTrade::TapAPIPositionInfo::AccountMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    // ITapTrade::TapAPIPositionInfo::UpperInitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "UpperInitialMargin", UpperInitialMargin);
    // ITapTrade::TapAPIPositionInfo::UpperMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    // ITapTrade::TapAPIPositionInfo::PositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionProfit", PositionProfit);
    // ITapTrade::TapAPIPositionInfo::LMEPositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "LMEPositionProfit", LMEPositionProfit);
    // ITapTrade::TapAPIPositionInfo::OptionMarketValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "OptionMarketValue", OptionMarketValue);
    // ITapTrade::TapAPIPositionInfo::IsHistory
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "IsHistory", IsHistory);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionInfo", c);
}
void generate_class_ITapTrade_TapAPIPositionProfit(pybind11::object & parent)
{
    // ITapTrade::TapAPIPositionProfit
    pybind11::class_<ITapTrade::TapAPIPositionProfit> c(parent, "TapAPIPositionProfit");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionProfit>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIPositionProfit::PositionNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "PositionNo", PositionNo);
    // ITapTrade::TapAPIPositionProfit::PositionStreamId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "PositionStreamId", PositionStreamId);
    // ITapTrade::TapAPIPositionProfit::PositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "PositionProfit", PositionProfit);
    // ITapTrade::TapAPIPositionProfit::LMEPositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "LMEPositionProfit", LMEPositionProfit);
    // ITapTrade::TapAPIPositionProfit::OptionMarketValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "OptionMarketValue", OptionMarketValue);
    // ITapTrade::TapAPIPositionProfit::CalculatePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "CalculatePrice", CalculatePrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionProfit, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionProfit", c);
}
void generate_class_ITapTrade_TapAPIPositionProfitNotice(pybind11::object & parent)
{
    // ITapTrade::TapAPIPositionProfitNotice
    pybind11::class_<ITapTrade::TapAPIPositionProfitNotice> c(parent, "TapAPIPositionProfitNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionProfitNotice>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIPositionProfitNotice::IsLast
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfitNotice, "IsLast", IsLast);
    // ITapTrade::TapAPIPositionProfitNotice::Data
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfitNotice, "Data", Data);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionProfitNotice, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionProfitNotice", c);
}
void generate_class_ITapTrade_TapAPIPositionSummary(pybind11::object & parent)
{
    // ITapTrade::TapAPIPositionSummary
    pybind11::class_<ITapTrade::TapAPIPositionSummary> c(parent, "TapAPIPositionSummary");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionSummary>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIPositionSummary::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "AccountNo", AccountNo);
    // ITapTrade::TapAPIPositionSummary::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIPositionSummary::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "CommodityType", CommodityType);
    // ITapTrade::TapAPIPositionSummary::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIPositionSummary::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "ContractNo", ContractNo);
    // ITapTrade::TapAPIPositionSummary::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIPositionSummary::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIPositionSummary::MatchSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "MatchSide", MatchSide);
    // ITapTrade::TapAPIPositionSummary::PositionPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "PositionPrice", PositionPrice);
    // ITapTrade::TapAPIPositionSummary::PositionQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "PositionQty", PositionQty);
    // ITapTrade::TapAPIPositionSummary::HisPositionQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "HisPositionQty", HisPositionQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionSummary, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionSummary", c);
}
void generate_class_ITapTrade_TapAPIFundReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIFundReq
    pybind11::class_<ITapTrade::TapAPIFundReq> c(parent, "TapAPIFundReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFundReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIFundReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFundReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFundReq", c);
}
void generate_class_ITapTrade_TapAPIFundData(pybind11::object & parent)
{
    // ITapTrade::TapAPIFundData
    pybind11::class_<ITapTrade::TapAPIFundData> c(parent, "TapAPIFundData");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFundData>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIFundData::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountNo", AccountNo);
    // ITapTrade::TapAPIFundData::CurrencyGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CurrencyGroupNo", CurrencyGroupNo);
    // ITapTrade::TapAPIFundData::CurrencyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CurrencyNo", CurrencyNo);
    // ITapTrade::TapAPIFundData::TradeRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "TradeRate", TradeRate);
    // ITapTrade::TapAPIFundData::FutureAlg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FutureAlg", FutureAlg);
    // ITapTrade::TapAPIFundData::OptionAlg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "OptionAlg", OptionAlg);
    // ITapTrade::TapAPIFundData::PreBalance
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreBalance", PreBalance);
    // ITapTrade::TapAPIFundData::PreUnExpProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreUnExpProfit", PreUnExpProfit);
    // ITapTrade::TapAPIFundData::PreLMEPositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreLMEPositionProfit", PreLMEPositionProfit);
    // ITapTrade::TapAPIFundData::PreEquity
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreEquity", PreEquity);
    // ITapTrade::TapAPIFundData::PreAvailable1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreAvailable1", PreAvailable1);
    // ITapTrade::TapAPIFundData::PreMarketEquity
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreMarketEquity", PreMarketEquity);
    // ITapTrade::TapAPIFundData::CashInValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashInValue", CashInValue);
    // ITapTrade::TapAPIFundData::CashOutValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashOutValue", CashOutValue);
    // ITapTrade::TapAPIFundData::CashAdjustValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashAdjustValue", CashAdjustValue);
    // ITapTrade::TapAPIFundData::CashPledged
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashPledged", CashPledged);
    // ITapTrade::TapAPIFundData::FrozenFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FrozenFee", FrozenFee);
    // ITapTrade::TapAPIFundData::FrozenDeposit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FrozenDeposit", FrozenDeposit);
    // ITapTrade::TapAPIFundData::AccountFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountFee", AccountFee);
    // ITapTrade::TapAPIFundData::SwapInValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "SwapInValue", SwapInValue);
    // ITapTrade::TapAPIFundData::SwapOutValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "SwapOutValue", SwapOutValue);
    // ITapTrade::TapAPIFundData::PremiumIncome
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PremiumIncome", PremiumIncome);
    // ITapTrade::TapAPIFundData::PremiumPay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PremiumPay", PremiumPay);
    // ITapTrade::TapAPIFundData::CloseProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CloseProfit", CloseProfit);
    // ITapTrade::TapAPIFundData::FrozenFund
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FrozenFund", FrozenFund);
    // ITapTrade::TapAPIFundData::UnExpProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "UnExpProfit", UnExpProfit);
    // ITapTrade::TapAPIFundData::ExpProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "ExpProfit", ExpProfit);
    // ITapTrade::TapAPIFundData::PositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PositionProfit", PositionProfit);
    // ITapTrade::TapAPIFundData::LmePositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "LmePositionProfit", LmePositionProfit);
    // ITapTrade::TapAPIFundData::OptionMarketValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "OptionMarketValue", OptionMarketValue);
    // ITapTrade::TapAPIFundData::AccountIntialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountIntialMargin", AccountIntialMargin);
    // ITapTrade::TapAPIFundData::AccountMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    // ITapTrade::TapAPIFundData::UpperInitalMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "UpperInitalMargin", UpperInitalMargin);
    // ITapTrade::TapAPIFundData::UpperMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    // ITapTrade::TapAPIFundData::Discount
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Discount", Discount);
    // ITapTrade::TapAPIFundData::Balance
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Balance", Balance);
    // ITapTrade::TapAPIFundData::Equity
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Equity", Equity);
    // ITapTrade::TapAPIFundData::Available
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Available", Available);
    // ITapTrade::TapAPIFundData::CanDraw
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CanDraw", CanDraw);
    // ITapTrade::TapAPIFundData::MarketEquity
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "MarketEquity", MarketEquity);
    // ITapTrade::TapAPIFundData::AuthMoney
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AuthMoney", AuthMoney);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFundData, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFundData", c);
}
