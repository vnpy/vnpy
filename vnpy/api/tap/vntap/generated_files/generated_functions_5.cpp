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


void generate_class_ITapTrade_ITapTradeAPINotify(pybind11::object & parent)
{
    // ITapTrade::ITapTradeAPINotify
    pybind11::class_<ITapTrade::ITapTradeAPINotify, PyITapTradeAPINotify> c(parent, "ITapTradeAPINotify");
    if constexpr (std::is_default_constructible_v<PyITapTradeAPINotify>)
        c.def(pybind11::init<>());
    // ITapTrade::ITapTradeAPINotify::OnConnect
    c.def("OnConnect",
        &ITapTrade::ITapTradeAPINotify::OnConnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspLogin
    c.def("OnRspLogin",
        &ITapTrade::ITapTradeAPINotify::OnRspLogin,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnContactInfo
    c.def("OnRtnContactInfo",
        &ITapTrade::ITapTradeAPINotify::OnRtnContactInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspRequestVertificateCode
    c.def("OnRspRequestVertificateCode",
        &ITapTrade::ITapTradeAPINotify::OnRspRequestVertificateCode,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnExpriationDate
    c.def("OnExpriationDate",
        &ITapTrade::ITapTradeAPINotify::OnExpriationDate,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnAPIReady
    c.def("OnAPIReady",
        &ITapTrade::ITapTradeAPINotify::OnAPIReady,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnDisconnect
    c.def("OnDisconnect",
        &ITapTrade::ITapTradeAPINotify::OnDisconnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspChangePassword
    c.def("OnRspChangePassword",
        &ITapTrade::ITapTradeAPINotify::OnRspChangePassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspAuthPassword
    c.def("OnRspAuthPassword",
        &ITapTrade::ITapTradeAPINotify::OnRspAuthPassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryTradingDate
    c.def("OnRspQryTradingDate",
        &ITapTrade::ITapTradeAPINotify::OnRspQryTradingDate,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspSetReservedInfo
    c.def("OnRspSetReservedInfo",
        &ITapTrade::ITapTradeAPINotify::OnRspSetReservedInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryAccount
    c.def("OnRspQryAccount",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccount,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryFund
    c.def("OnRspQryFund",
        &ITapTrade::ITapTradeAPINotify::OnRspQryFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnFund
    c.def("OnRtnFund",
        &ITapTrade::ITapTradeAPINotify::OnRtnFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryExchange
    c.def("OnRspQryExchange",
        &ITapTrade::ITapTradeAPINotify::OnRspQryExchange,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryCommodity
    c.def("OnRspQryCommodity",
        &ITapTrade::ITapTradeAPINotify::OnRspQryCommodity,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryContract
    c.def("OnRspQryContract",
        &ITapTrade::ITapTradeAPINotify::OnRspQryContract,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnContract
    c.def("OnRtnContract",
        &ITapTrade::ITapTradeAPINotify::OnRtnContract,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspOrderAction
    c.def("OnRspOrderAction",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderAction,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnOrder
    c.def("OnRtnOrder",
        &ITapTrade::ITapTradeAPINotify::OnRtnOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryOrder
    c.def("OnRspQryOrder",
        &ITapTrade::ITapTradeAPINotify::OnRspQryOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryOrderProcess
    c.def("OnRspQryOrderProcess",
        &ITapTrade::ITapTradeAPINotify::OnRspQryOrderProcess,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryFill
    c.def("OnRspQryFill",
        &ITapTrade::ITapTradeAPINotify::OnRspQryFill,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnFill
    c.def("OnRtnFill",
        &ITapTrade::ITapTradeAPINotify::OnRtnFill,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryPosition
    c.def("OnRspQryPosition",
        &ITapTrade::ITapTradeAPINotify::OnRspQryPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnPosition
    c.def("OnRtnPosition",
        &ITapTrade::ITapTradeAPINotify::OnRtnPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryPositionSummary
    c.def("OnRspQryPositionSummary",
        &ITapTrade::ITapTradeAPINotify::OnRspQryPositionSummary,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnPositionSummary
    c.def("OnRtnPositionSummary",
        &ITapTrade::ITapTradeAPINotify::OnRtnPositionSummary,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit
    c.def("OnRtnPositionProfit",
        &ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryCurrency
    c.def("OnRspQryCurrency",
        &ITapTrade::ITapTradeAPINotify::OnRspQryCurrency,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryTradeMessage
    c.def("OnRspQryTradeMessage",
        &ITapTrade::ITapTradeAPINotify::OnRspQryTradeMessage,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRtnTradeMessage
    c.def("OnRtnTradeMessage",
        &ITapTrade::ITapTradeAPINotify::OnRtnTradeMessage,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryHisOrder
    c.def("OnRspQryHisOrder",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryHisOrderProcess
    c.def("OnRspQryHisOrderProcess",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisOrderProcess,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryHisMatch
    c.def("OnRspQryHisMatch",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisMatch,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryHisPosition
    c.def("OnRspQryHisPosition",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryHisDelivery
    c.def("OnRspQryHisDelivery",
        &ITapTrade::ITapTradeAPINotify::OnRspQryHisDelivery,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryAccountCashAdjust
    c.def("OnRspQryAccountCashAdjust",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccountCashAdjust,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryBill
    c.def("OnRspQryBill",
        &ITapTrade::ITapTradeAPINotify::OnRspQryBill,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryAccountFeeRent
    c.def("OnRspQryAccountFeeRent",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccountFeeRent,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspQryAccountMarginRent
    c.def("OnRspQryAccountMarginRent",
        &ITapTrade::ITapTradeAPINotify::OnRspQryAccountMarginRent,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderInsert
    c.def("OnRspHKMarketOrderInsert",
        &ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderInsert,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderDelete
    c.def("OnRspHKMarketOrderDelete",
        &ITapTrade::ITapTradeAPINotify::OnRspHKMarketOrderDelete,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnHKMarketQuoteNotice
    c.def("OnHKMarketQuoteNotice",
        &ITapTrade::ITapTradeAPINotify::OnHKMarketQuoteNotice,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspOrderLocalRemove
    c.def("OnRspOrderLocalRemove",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalRemove,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspOrderLocalInput
    c.def("OnRspOrderLocalInput",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalInput,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspOrderLocalModify
    c.def("OnRspOrderLocalModify",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalModify,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspOrderLocalTransfer
    c.def("OnRspOrderLocalTransfer",
        &ITapTrade::ITapTradeAPINotify::OnRspOrderLocalTransfer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspFillLocalInput
    c.def("OnRspFillLocalInput",
        &ITapTrade::ITapTradeAPINotify::OnRspFillLocalInput,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPINotify::OnRspFillLocalRemove
    c.def("OnRspFillLocalRemove",
        &ITapTrade::ITapTradeAPINotify::OnRspFillLocalRemove,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::ITapTradeAPINotify, c);
    module_vntap::objects.emplace("ITapTrade::ITapTradeAPINotify", c);
}
