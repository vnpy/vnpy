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


void generate_class_ITapTrade_ITapTradeAPI(pybind11::object & parent)
{
    // ITapTrade::ITapTradeAPI
    pybind11::class_<ITapTrade::ITapTradeAPI, PyITapTradeAPI> c(parent, "ITapTradeAPI");
    if constexpr (std::is_default_constructible_v<PyITapTradeAPI>)
        c.def(pybind11::init<>());
    // ITapTrade::ITapTradeAPI::SetAPINotify
    c.def("SetAPINotify",
        &ITapTrade::ITapTradeAPI::SetAPINotify,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::SetHostAddress
    c.def("SetHostAddress",
        &ITapTrade::ITapTradeAPI::SetHostAddress,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::Login
    c.def("Login",
        &ITapTrade::ITapTradeAPI::Login,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::RequestVertificateCode
    c.def("RequestVertificateCode",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::RequestVertificateCode>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::SetVertificateCode
    c.def("SetVertificateCode",
        &ITapTrade::ITapTradeAPI::SetVertificateCode,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::Disconnect
    c.def("Disconnect",
        &ITapTrade::ITapTradeAPI::Disconnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::ChangePassword
    c.def("ChangePassword",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::ChangePassword>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::AuthPassword
    c.def("AuthPassword",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::AuthPassword>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::HaveCertainRight
    c.def("HaveCertainRight",
        &ITapTrade::ITapTradeAPI::HaveCertainRight,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryTradingDate
    c.def("QryTradingDate",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryTradingDate>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::SetReservedInfo
    c.def("SetReservedInfo",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::SetReservedInfo>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryAccount
    c.def("QryAccount",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryAccount>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryFund
    c.def("QryFund",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryFund>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryExchange
    c.def("QryExchange",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryExchange>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryCommodity
    c.def("QryCommodity",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryCommodity>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryContract
    c.def("QryContract",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryContract>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::InsertOrder
    c.def("InsertOrder",
        c2py::apply_function_transform<
            c2py::function_constant<&ITapTrade::ITapTradeAPI::InsertOrder>,
            brigand::list<
                c2py::indexed_transform_holder<c2py::output_argument_transform, 0 + 1/*self*/>,
                c2py::indexed_transform_holder<c2py::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::CancelOrder
    c.def("CancelOrder",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::CancelOrder>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::AmendOrder
    c.def("AmendOrder",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::AmendOrder>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::ActivateOrder
    c.def("ActivateOrder",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::ActivateOrder>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryOrder
    c.def("QryOrder",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryOrder>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryOrderProcess
    c.def("QryOrderProcess",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryOrderProcess>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryFill
    c.def("QryFill",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryFill>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryPosition
    c.def("QryPosition",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryPosition>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryPositionSummary
    c.def("QryPositionSummary",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryPositionSummary>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryCurrency
    c.def("QryCurrency",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryCurrency>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryAccountCashAdjust
    c.def("QryAccountCashAdjust",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryAccountCashAdjust>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryTradeMessage
    c.def("QryTradeMessage",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryTradeMessage>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryBill
    c.def("QryBill",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryBill>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryHisOrder
    c.def("QryHisOrder",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryHisOrder>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryHisOrderProcess
    c.def("QryHisOrderProcess",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryHisOrderProcess>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryHisMatch
    c.def("QryHisMatch",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryHisMatch>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryHisPosition
    c.def("QryHisPosition",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryHisPosition>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryHisDelivery
    c.def("QryHisDelivery",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryHisDelivery>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryAccountFeeRent
    c.def("QryAccountFeeRent",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryAccountFeeRent>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::QryAccountMarginRent
    c.def("QryAccountMarginRent",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::QryAccountMarginRent>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::InsertHKMarketOrder
    c.def("InsertHKMarketOrder",
        c2py::apply_function_transform<
            c2py::function_constant<&ITapTrade::ITapTradeAPI::InsertHKMarketOrder>,
            brigand::list<
                c2py::indexed_transform_holder<c2py::output_argument_transform, 0 + 1/*self*/>,
                c2py::indexed_transform_holder<c2py::output_argument_transform, 0 + 1/*self*/>,
                c2py::indexed_transform_holder<c2py::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::CancelHKMarketOrder
    c.def("CancelHKMarketOrder",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::CancelHKMarketOrder>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::OrderLocalRemove
    c.def("OrderLocalRemove",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::OrderLocalRemove>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::OrderLocalInput
    c.def("OrderLocalInput",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::OrderLocalInput>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::OrderLocalModify
    c.def("OrderLocalModify",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::OrderLocalModify>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::OrderLocalTransfer
    c.def("OrderLocalTransfer",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::OrderLocalTransfer>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::FillLocalInput
    c.def("FillLocalInput",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::FillLocalInput>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapTrade::ITapTradeAPI::FillLocalRemove
    c.def("FillLocalRemove",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapTrade::ITapTradeAPI::FillLocalRemove>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::ITapTradeAPI, c);
    module_vntap::objects.emplace("ITapTrade::ITapTradeAPI", c);
}
void generate_ITapTrade_classes(pybind11::module & parent)
{
    generate_class_ITapTrade_TapAPIApplicationInfo(parent);
    generate_class_ITapTrade_TapAPICommodity(parent);
    generate_class_ITapTrade_TapAPIContract(parent);
    generate_class_ITapTrade_TapAPIExchangeInfo(parent);
    generate_class_ITapTrade_TapAPIChangePasswordReq(parent);
    generate_class_ITapTrade_TapAPIAuthPasswordReq(parent);
    generate_class_ITapTrade_TapAPITradeLoginAuth(parent);
    generate_class_ITapTrade_TapAPITradeLoginRspInfo(parent);
    generate_class_ITapTrade_TapAPIRequestVertificateCodeRsp(parent);
    generate_class_ITapTrade_TapAPIAccQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountInfo(parent);
    generate_class_ITapTrade_TapAPINewOrder(parent);
    generate_class_ITapTrade_TapAPIOrderInfo(parent);
    generate_class_ITapTrade_TapAPIOrderInfoNotice(parent);
    generate_class_ITapTrade_TapAPIOrderActionRsp(parent);
    generate_class_ITapTrade_TapAPIAmendOrder(parent);
    generate_class_ITapTrade_TapAPIOrderCancelReq(parent);
    generate_class_ITapTrade_TapAPIOrderQryReq(parent);
    generate_class_ITapTrade_TapAPIOrderProcessQryReq(parent);
    generate_class_ITapTrade_TapAPIFillQryReq(parent);
    generate_class_ITapTrade_TapAPIFillInfo(parent);
    generate_class_ITapTrade_TapAPICloseQryReq(parent);
    generate_class_ITapTrade_TapAPICloseInfo(parent);
    generate_class_ITapTrade_TapAPIPositionQryReq(parent);
    generate_class_ITapTrade_TapAPIPositionInfo(parent);
    generate_class_ITapTrade_TapAPIPositionProfit(parent);
    generate_class_ITapTrade_TapAPIPositionProfitNotice(parent);
    generate_class_ITapTrade_TapAPIPositionSummary(parent);
    generate_class_ITapTrade_TapAPIFundReq(parent);
    generate_class_ITapTrade_TapAPIFundData(parent);
    generate_class_ITapTrade_TapAPICommodityInfo(parent);
    generate_class_ITapTrade_TapAPITradeContractInfo(parent);
    generate_class_ITapTrade_TapAPICurrencyInfo(parent);
    generate_class_ITapTrade_TapAPITradeMessageReq(parent);
    generate_class_ITapTrade_TapAPITradeMessage(parent);
    generate_class_ITapTrade_TapAPIBillQryReq(parent);
    generate_class_ITapTrade_TapAPIBillQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisOrderQryReq(parent);
    generate_class_ITapTrade_TapAPIHisOrderQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisMatchQryReq(parent);
    generate_class_ITapTrade_TapAPIHisMatchQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisOrderProcessQryReq(parent);
    generate_class_ITapTrade_TapAPIHisPositionQryReq(parent);
    generate_class_ITapTrade_TapAPIHisPositionQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisDeliveryQryReq(parent);
    generate_class_ITapTrade_TapAPIHisDeliveryQryRsp(parent);
    generate_class_ITapTrade_TapAPIAccountCashAdjustQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountCashAdjustQryRsp(parent);
    generate_class_ITapTrade_TapAPIAccountFeeRentQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountFeeRentQryRsp(parent);
    generate_class_ITapTrade_TapAPIAccountMarginRentQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountMarginRentQryRsp(parent);
    generate_class_ITapTrade_TapAPIOrderQuoteMarketNotice(parent);
    generate_class_ITapTrade_TapAPIOrderMarketInsertReq(parent);
    generate_class_ITapTrade_TapAPIOrderMarketInsertRsp(parent);
    generate_class_ITapTrade_TapAPIOrderMarketDeleteReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalRemoveReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalRemoveRsp(parent);
    generate_class_ITapTrade_TapAPIOrderLocalInputReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalModifyReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalTransferReq(parent);
    generate_class_ITapTrade_TapAPIFillLocalInputReq(parent);
    generate_class_ITapTrade_TapAPIFillLocalRemoveReq(parent);
    generate_class_ITapTrade_TapAPITradingCalendarQryRsp(parent);
    generate_class_ITapTrade_ITapTradeAPINotify(parent);
    generate_class_ITapTrade_ITapTradeAPI(parent);
}
void generate_ITapTrade_enums(pybind11::module & parent)
{
    
}
void generate_ITapTrade_functions_0(pybind11::module & parent)
{
    
}
void generate_ITapTrade_functions(pybind11::module & parent)
{
    generate_ITapTrade_functions_0(parent);
}
