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


void generate_class_ITapTrade_TapAPIOrderLocalModifyReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalModifyReq> c(parent, "TapAPIOrderLocalModifyReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalModifyReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalModifyReq, "req", req);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalModifyReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalModifyReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderLocalModifyReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderLocalModifyReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalTransferReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalTransferReq> c(parent, "TapAPIOrderLocalTransferReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalTransferReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalTransferReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalTransferReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalTransferReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderLocalTransferReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderLocalTransferReq", c);
}
void generate_class_ITapTrade_TapAPIFillLocalInputReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillLocalInputReq> c(parent, "TapAPIFillLocalInputReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillLocalInputReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "MatchPrice", MatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "MatchQty", MatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "UpperMatchNo", UpperMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "MatchDateTime", MatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "UpperMatchDateTime", UpperMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "IsAddOne", IsAddOne);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "FeeCurrencyGroup", FeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "FeeCurrency", FeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "FeeValue", FeeValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "IsManualFee", IsManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, "ClosePositionPrice", ClosePositionPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIFillLocalInputReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIFillLocalInputReq", c);
}
void generate_class_ITapTrade_TapAPIFillLocalRemoveReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillLocalRemoveReq> c(parent, "TapAPIFillLocalRemoveReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillLocalRemoveReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalRemoveReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillLocalRemoveReq, "MatchNo", MatchNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIFillLocalRemoveReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIFillLocalRemoveReq", c);
}
void generate_class_ITapTrade_TapAPITradingCalendarQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradingCalendarQryRsp> c(parent, "TapAPITradingCalendarQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradingCalendarQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradingCalendarQryRsp, "CurrTradeDate", CurrTradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradingCalendarQryRsp, "LastSettlementDate", LastSettlementDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradingCalendarQryRsp, "PromptDate", PromptDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradingCalendarQryRsp, "LastPromptDate", LastPromptDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPITradingCalendarQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPITradingCalendarQryRsp", c);
}
void generate_class_ITapTrade_ITapTradeAPINotify(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::ITapTradeAPINotify, PyITapTradeAPINotify> c(parent, "ITapTradeAPINotify");
    if constexpr (std::is_default_constructible_v<PyITapTradeAPINotify>)
        c.def(pybind11::init<>());
    c.def("OnConnect",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnConnect
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspLogin",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspLogin
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnContactInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnContactInfo
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspRequestVertificateCode",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspRequestVertificateCode
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnExpriationDate",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnExpriationDate
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnAPIReady",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnAPIReady
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnDisconnect",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnDisconnect
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspChangePassword",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspChangePassword
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspAuthPassword",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspAuthPassword
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryTradingDate",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryTradingDate
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspSetReservedInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspSetReservedInfo
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccount",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryAccount
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryFund",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryFund
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnFund",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnFund
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryExchange",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryExchange
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryCommodity",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryCommodity
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryContract",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryContract
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnContract",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnContract
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderAction",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspOrderAction
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnOrder
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryOrder
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryOrderProcess",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryOrderProcess
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryFill",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryFill
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnFill",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnFill
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryPosition",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryPosition
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnPosition",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnPosition
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryPositionSummary",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryPositionSummary
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnPositionSummary",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnPositionSummary
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnPositionProfit",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryCurrency",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryCurrency
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryTradeMessage",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryTradeMessage
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnTradeMessage",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRtnTradeMessage
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryHisOrder
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisOrderProcess",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryHisOrderProcess
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisMatch",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryHisMatch
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisPosition",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryHisPosition
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryHisDelivery",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryHisDelivery
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccountCashAdjust",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryAccountCashAdjust
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryBill",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryBill
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccountFeeRent",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryAccountFeeRent
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspQryAccountMarginRent",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspQryAccountMarginRent
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspHKMarketOrderInsert",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderInsert
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspHKMarketOrderDelete",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderDelete
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnHKMarketQuoteNotice",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnHKMarketQuoteNotice
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalRemove",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalRemove
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalInput",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalInput
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalModify",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalModify
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspOrderLocalTransfer",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalTransfer
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspFillLocalInput",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspFillLocalInput
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspFillLocalRemove",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPINotify::OnRspFillLocalRemove
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::ITapTradeAPINotify, c);
    module_vnitap::objects.emplace("ITapTrade::ITapTradeAPINotify", c);
}
