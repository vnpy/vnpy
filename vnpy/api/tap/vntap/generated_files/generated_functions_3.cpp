#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

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
    pybind11::class_<ITapTrade::TapAPIOrderMarketDeleteReq> c(parent, "TapAPIOrderMarketDeleteReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketDeleteReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, "OrderBuyNo", OrderBuyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, "OrderSellNo", OrderSellNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderMarketDeleteReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderMarketDeleteReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalRemoveReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalRemoveReq> c(parent, "TapAPIOrderLocalRemoveReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalRemoveReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalRemoveReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalRemoveRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalRemoveRsp> c(parent, "TapAPIOrderLocalRemoveRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalRemoveRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "req", req);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientLocalIP", ClientLocalIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientMac", ClientMac);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientIP", ClientIP);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalRemoveRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalRemoveRsp", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalInputReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalInputReq> c(parent, "TapAPIOrderLocalInputReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalInputReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchPrice", OrderMatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchPrice2", OrderMatchPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchQty", OrderMatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchQty2", OrderMatchQty2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "OrderState", OrderState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalInputReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalInputReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalModifyReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalModifyReq> c(parent, "TapAPIOrderLocalModifyReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalModifyReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, "req", req);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalModifyReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalModifyReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalTransferReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalTransferReq> c(parent, "TapAPIOrderLocalTransferReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalTransferReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderLocalTransferReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderLocalTransferReq", c);
}
void generate_class_ITapTrade_TapAPIFillLocalInputReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillLocalInputReq> c(parent, "TapAPIFillLocalInputReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillLocalInputReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchPrice", MatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchQty", MatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "UpperMatchNo", UpperMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "MatchDateTime", MatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "UpperMatchDateTime", UpperMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "IsAddOne", IsAddOne);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "FeeCurrencyGroup", FeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "FeeCurrency", FeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "FeeValue", FeeValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "IsManualFee", IsManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, "ClosePositionPrice", ClosePositionPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillLocalInputReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillLocalInputReq", c);
}
void generate_class_ITapTrade_TapAPIFillLocalRemoveReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillLocalRemoveReq> c(parent, "TapAPIFillLocalRemoveReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillLocalRemoveReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalRemoveReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillLocalRemoveReq, "MatchNo", MatchNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillLocalRemoveReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillLocalRemoveReq", c);
}
void generate_class_ITapTrade_TapAPITradingCalendarQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradingCalendarQryRsp> c(parent, "TapAPITradingCalendarQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradingCalendarQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "CurrTradeDate", CurrTradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "LastSettlementDate", LastSettlementDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "PromptDate", PromptDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, "LastPromptDate", LastPromptDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradingCalendarQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradingCalendarQryRsp", c);
}
void generate_class_ITapTrade_ITapTradeAPINotify(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::ITapTradeAPINotify, PyITapTradeAPINotify> c(parent, "ITapTradeAPINotify");
    if constexpr (std::is_default_constructible_v<PyITapTradeAPINotify>)
        c.def(pybind11::init<>());
    c.def("OnConnect",
        &ITapTrade::ITapTradeAPINotify::OnConnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspLogin",
        &ITapTrade::ITapTradeAPINotify::OnRspLogin,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnContactInfo",
        &ITapTrade::ITapTradeAPINotify::OnRtnContactInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspRequestVertificateCode",
        &ITapTrade::ITapTradeAPINotify::OnRspRequestVertificateCode,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnExpriationDate",
        &ITapTrade::ITapTradeAPINotify::OnExpriationDate,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnAPIReady",
        &ITapTrade::ITapTradeAPINotify::OnAPIReady,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnDisconnect",
        &ITapTrade::ITapTradeAPINotify::OnDisconnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspChangePassword",
        &ITapTrade::ITapTradeAPINotify::OnRspChangePassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspAuthPassword",
        &ITapTrade::ITapTradeAPINotify::OnRspAuthPassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryTradingDate",
        &ITapTrade::ITapTradeAPINotify::OnRspQryTradingDate,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspSetReservedInfo",
        &ITapTrade::ITapTradeAPINotify::OnRspSetReservedInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccount",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccount,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryFund",
        &ITapTrade::ITapTradeAPINotify::OnRspQryFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnFund",
        &ITapTrade::ITapTradeAPINotify::OnRtnFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryExchange",
        &ITapTrade::ITapTradeAPINotify::OnRspQryExchange,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryCommodity",
        &ITapTrade::ITapTradeAPINotify::OnRspQryCommodity,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryContract",
        &ITapTrade::ITapTradeAPINotify::OnRspQryContract,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnContract",
        &ITapTrade::ITapTradeAPINotify::OnRtnContract,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderAction",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderAction,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnOrder",
        &ITapTrade::ITapTradeAPINotify::OnRtnOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryOrder",
        &ITapTrade::ITapTradeAPINotify::OnRspQryOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryOrderProcess",
        &ITapTrade::ITapTradeAPINotify::OnRspQryOrderProcess,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryFill",
        &ITapTrade::ITapTradeAPINotify::OnRspQryFill,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnFill",
        &ITapTrade::ITapTradeAPINotify::OnRtnFill,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryPosition",
        &ITapTrade::ITapTradeAPINotify::OnRspQryPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnPosition",
        &ITapTrade::ITapTradeAPINotify::OnRtnPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryPositionSummary",
        &ITapTrade::ITapTradeAPINotify::OnRspQryPositionSummary,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnPositionSummary",
        &ITapTrade::ITapTradeAPINotify::OnRtnPositionSummary,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnPositionProfit",
        &ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryCurrency",
        &ITapTrade::ITapTradeAPINotify::OnRspQryCurrency,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryTradeMessage",
        &ITapTrade::ITapTradeAPINotify::OnRspQryTradeMessage,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnTradeMessage",
        &ITapTrade::ITapTradeAPINotify::OnRtnTradeMessage,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisOrder",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisOrderProcess",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisOrderProcess,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisMatch",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisMatch,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisPosition",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisDelivery",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisDelivery,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccountCashAdjust",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccountCashAdjust,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryBill",
        &ITapTrade::ITapTradeAPINotify::OnRspQryBill,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccountFeeRent",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccountFeeRent,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccountMarginRent",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccountMarginRent,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspHKMarketOrderInsert",
        &ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderInsert,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspHKMarketOrderDelete",
        &ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderDelete,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnHKMarketQuoteNotice",
        &ITapTrade::ITapTradeAPINotify::OnHKMarketQuoteNotice,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalRemove",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalRemove,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalInput",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalInput,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalModify",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalModify,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalTransfer",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalTransfer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspFillLocalInput",
        &ITapTrade::ITapTradeAPINotify::OnRspFillLocalInput,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspFillLocalRemove",
        &ITapTrade::ITapTradeAPINotify::OnRspFillLocalRemove,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::ITapTradeAPINotify, c);
    module_vntap::objects.emplace("ITapTrade::ITapTradeAPINotify", c);
}
void generate_class_ITapTrade_ITapTradeAPI(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::ITapTradeAPI, PyITapTradeAPI> c(parent, "ITapTradeAPI");
    if constexpr (std::is_default_constructible_v<PyITapTradeAPI>)
        c.def(pybind11::init<>());
    c.def("SetAPINotify",
        &ITapTrade::ITapTradeAPI::SetAPINotify,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetHostAddress",
        &ITapTrade::ITapTradeAPI::SetHostAddress,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Login",
        &ITapTrade::ITapTradeAPI::Login,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RequestVertificateCode",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::RequestVertificateCode
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetVertificateCode",
        &ITapTrade::ITapTradeAPI::SetVertificateCode,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Disconnect",
        &ITapTrade::ITapTradeAPI::Disconnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ChangePassword",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::ChangePassword
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("AuthPassword",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::AuthPassword
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("HaveCertainRight",
        &ITapTrade::ITapTradeAPI::HaveCertainRight,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryTradingDate",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryTradingDate
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetReservedInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::SetReservedInfo
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryAccount",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryAccount
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryFund",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryFund
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryExchange",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryExchange
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryCommodity",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryCommodity
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryContract",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryContract
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("InsertOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::InsertOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>,
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("CancelOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::CancelOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("AmendOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::AmendOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ActivateOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::ActivateOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryOrderProcess",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryOrderProcess
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryFill",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryFill
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryPosition",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryPosition
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryPositionSummary",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryPositionSummary
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryCurrency",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryCurrency
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryAccountCashAdjust",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryAccountCashAdjust
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryTradeMessage",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryTradeMessage
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryBill",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryBill
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryHisOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryHisOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryHisOrderProcess",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryHisOrderProcess
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryHisMatch",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryHisMatch
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryHisPosition",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryHisPosition
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryHisDelivery",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryHisDelivery
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryAccountFeeRent",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryAccountFeeRent
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryAccountMarginRent",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::QryAccountMarginRent
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("InsertHKMarketOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::InsertHKMarketOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>,
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>,
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("CancelHKMarketOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::CancelHKMarketOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OrderLocalRemove",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::OrderLocalRemove
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OrderLocalInput",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::OrderLocalInput
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OrderLocalModify",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::OrderLocalModify
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OrderLocalTransfer",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::OrderLocalTransfer
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("FillLocalInput",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::FillLocalInput
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("FillLocalRemove",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::FillLocalRemove
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::ITapTradeAPI, c);
    module_vntap::objects.emplace("ITapTrade::ITapTradeAPI", c);
}
