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


void generate_class_ITapTrade_ITapTradeAPI(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::ITapTradeAPI, PyITapTradeAPI> c(parent, "ITapTradeAPI");
    if constexpr (std::is_default_constructible_v<PyITapTradeAPI>)
        c.def(pybind11::init<>());
    c.def("SetAPINotify",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::SetAPINotify
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetHostAddress",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::SetHostAddress
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Login",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::Login
            >, 
            brigand::list<
            >
        >::value,
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
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::SetVertificateCode
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Disconnect",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::Disconnect
            >, 
            brigand::list<
            >
        >::value,
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
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapTrade::ITapTradeAPI::HaveCertainRight
            >, 
            brigand::list<
            >
        >::value,
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
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::ITapTradeAPI, c);
    module_vnitap::objects.emplace("ITapTrade::ITapTradeAPI", c);
}
void generate_caster_ITapTrade(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
    autocxxpy::caster::try_generate<ITapTrade::TapAPIApplicationInfo>(c, "toTapAPIApplicationInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPICommodity>(c, "toTapAPICommodity)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIContract>(c, "toTapAPIContract)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIExchangeInfo>(c, "toTapAPIExchangeInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIChangePasswordReq>(c, "toTapAPIChangePasswordReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAuthPasswordReq>(c, "toTapAPIAuthPasswordReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPITradeLoginAuth>(c, "toTapAPITradeLoginAuth)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPITradeLoginRspInfo>(c, "toTapAPITradeLoginRspInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIRequestVertificateCodeRsp>(c, "toTapAPIRequestVertificateCodeRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccQryReq>(c, "toTapAPIAccQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccountInfo>(c, "toTapAPIAccountInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPINewOrder>(c, "toTapAPINewOrder)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderInfo>(c, "toTapAPIOrderInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderInfoNotice>(c, "toTapAPIOrderInfoNotice)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderActionRsp>(c, "toTapAPIOrderActionRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAmendOrder>(c, "toTapAPIAmendOrder)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderCancelReq>(c, "toTapAPIOrderCancelReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderQryReq>(c, "toTapAPIOrderQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderProcessQryReq>(c, "toTapAPIOrderProcessQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFillQryReq>(c, "toTapAPIFillQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFillInfo>(c, "toTapAPIFillInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPICloseQryReq>(c, "toTapAPICloseQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPICloseInfo>(c, "toTapAPICloseInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIPositionQryReq>(c, "toTapAPIPositionQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIPositionInfo>(c, "toTapAPIPositionInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIPositionProfit>(c, "toTapAPIPositionProfit)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIPositionProfitNotice>(c, "toTapAPIPositionProfitNotice)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIPositionSummary>(c, "toTapAPIPositionSummary)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFundReq>(c, "toTapAPIFundReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFundData>(c, "toTapAPIFundData)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPICommodityInfo>(c, "toTapAPICommodityInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPITradeContractInfo>(c, "toTapAPITradeContractInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPICurrencyInfo>(c, "toTapAPICurrencyInfo)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPITradeMessageReq>(c, "toTapAPITradeMessageReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPITradeMessage>(c, "toTapAPITradeMessage)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIBillQryReq>(c, "toTapAPIBillQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIBillQryRsp>(c, "toTapAPIBillQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisOrderQryReq>(c, "toTapAPIHisOrderQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisOrderQryRsp>(c, "toTapAPIHisOrderQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisMatchQryReq>(c, "toTapAPIHisMatchQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisMatchQryRsp>(c, "toTapAPIHisMatchQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisOrderProcessQryReq>(c, "toTapAPIHisOrderProcessQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisPositionQryReq>(c, "toTapAPIHisPositionQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisPositionQryRsp>(c, "toTapAPIHisPositionQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisDeliveryQryReq>(c, "toTapAPIHisDeliveryQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisDeliveryQryRsp>(c, "toTapAPIHisDeliveryQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccountCashAdjustQryReq>(c, "toTapAPIAccountCashAdjustQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccountCashAdjustQryRsp>(c, "toTapAPIAccountCashAdjustQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccountFeeRentQryReq>(c, "toTapAPIAccountFeeRentQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccountFeeRentQryRsp>(c, "toTapAPIAccountFeeRentQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccountMarginRentQryReq>(c, "toTapAPIAccountMarginRentQryReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIAccountMarginRentQryRsp>(c, "toTapAPIAccountMarginRentQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderQuoteMarketNotice>(c, "toTapAPIOrderQuoteMarketNotice)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderMarketInsertReq>(c, "toTapAPIOrderMarketInsertReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderMarketInsertRsp>(c, "toTapAPIOrderMarketInsertRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderMarketDeleteReq>(c, "toTapAPIOrderMarketDeleteReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalRemoveReq>(c, "toTapAPIOrderLocalRemoveReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalRemoveRsp>(c, "toTapAPIOrderLocalRemoveRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalInputReq>(c, "toTapAPIOrderLocalInputReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalModifyReq>(c, "toTapAPIOrderLocalModifyReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalTransferReq>(c, "toTapAPIOrderLocalTransferReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFillLocalInputReq>(c, "toTapAPIFillLocalInputReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFillLocalRemoveReq>(c, "toTapAPIFillLocalRemoveReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPITradingCalendarQryRsp>(c, "toTapAPITradingCalendarQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::ITapTradeAPINotify>(c, "toITapTradeAPINotify)");
    autocxxpy::caster::try_generate<ITapTrade::ITapTradeAPI>(c, "toITapTradeAPI)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_10>(c, "toTAPISTR_10)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_20>(c, "toTAPISTR_20)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_30>(c, "toTAPISTR_30)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_40>(c, "toTAPISTR_40)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_50>(c, "toTAPISTR_50)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_70>(c, "toTAPISTR_70)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_100>(c, "toTAPISTR_100)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_300>(c, "toTAPISTR_300)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_500>(c, "toTAPISTR_500)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISTR_2000>(c, "toTAPISTR_2000)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIAUTHCODE>(c, "toTAPIAUTHCODE)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIMACTYPE>(c, "toTAPIMACTYPE)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISecondSerialIDType>(c, "toTAPISecondSerialIDType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPICHAR>(c, "toTAPICHAR)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIClientIDType>(c, "toTAPIClientIDType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIINT32>(c, "toTAPIINT32)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIUINT32>(c, "toTAPIUINT32)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIINT64>(c, "toTAPIINT64)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIUINT64>(c, "toTAPIUINT64)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIUINT16>(c, "toTAPIUINT16)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIUINT8>(c, "toTAPIUINT8)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIREAL64>(c, "toTAPIREAL64)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIYNFLAG>(c, "toTAPIYNFLAG)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIPasswordType>(c, "toTAPIPasswordType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIDTSTAMP>(c, "toTAPIDTSTAMP)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIDATETIME>(c, "toTAPIDATETIME)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIDATE>(c, "toTAPIDATE)");
    autocxxpy::caster::try_generate<ITapTrade::TAPITIME>(c, "toTAPITIME)");
    autocxxpy::caster::try_generate<ITapTrade::TAPILOGLEVEL>(c, "toTAPILOGLEVEL)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOptionType>(c, "toTAPIOptionType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPICommodityType>(c, "toTAPICommodityType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPICallOrPutFlagType>(c, "toTAPICallOrPutFlagType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIAccountType>(c, "toTAPIAccountType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIRightIDType>(c, "toTAPIRightIDType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIUserTypeType>(c, "toTAPIUserTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIAccountState>(c, "toTAPIAccountState)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIAccountRightType>(c, "toTAPIAccountRightType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOrderTypeType>(c, "toTAPIOrderTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOrderSourceType>(c, "toTAPIOrderSourceType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPITimeInForceType>(c, "toTAPITimeInForceType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISideType>(c, "toTAPISideType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIPositionEffectType>(c, "toTAPIPositionEffectType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIHedgeFlagType>(c, "toTAPIHedgeFlagType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOrderStateType>(c, "toTAPIOrderStateType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPICalculateModeType>(c, "toTAPICalculateModeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIMatchSourceType>(c, "toTAPIMatchSourceType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOpenCloseModeType>(c, "toTAPIOpenCloseModeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIFutureAlgType>(c, "toTAPIFutureAlgType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOptionAlgType>(c, "toTAPIOptionAlgType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISendType>(c, "toTAPISendType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIBankAccountLWFlagType>(c, "toTAPIBankAccountLWFlagType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPICashAdjustTypeType>(c, "toTAPICashAdjustTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIMarginCalculateModeType>(c, "toTAPIMarginCalculateModeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOptionMarginCalculateModeType>(c, "toTAPIOptionMarginCalculateModeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPICmbDirectType>(c, "toTAPICmbDirectType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIDeliveryModeType>(c, "toTAPIDeliveryModeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIContractTypeType>(c, "toTAPIContractTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPITacticsTypeType>(c, "toTAPITacticsTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIORDERACT>(c, "toTAPIORDERACT)");
    autocxxpy::caster::try_generate<ITapTrade::TAPITriggerConditionType>(c, "toTAPITriggerConditionType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPITriggerPriceTypeType>(c, "toTAPITriggerPriceTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPITradingStateType>(c, "toTAPITradingStateType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPINoticeIgnoreFlagType>(c, "toTAPINoticeIgnoreFlagType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIOrderQryTypeType>(c, "toTAPIOrderQryTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderDeactivateReq>(c, "toTapAPIOrderDeactivateReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderActivateReq>(c, "toTapAPIOrderActivateReq)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderDeleteReq>(c, "toTapAPIOrderDeleteReq)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIMsgReceiverType>(c, "toTAPIMsgReceiverType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIMsgLevelType>(c, "toTAPIMsgLevelType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIMsgTypeType>(c, "toTAPIMsgTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIBillTypeType>(c, "toTAPIBillTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TAPIBillFileTypeType>(c, "toTAPIBillFileTypeType)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIHisOrderProcessQryRsp>(c, "toTapAPIHisOrderProcessQryRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TAPISettleFlagType>(c, "toTAPISettleFlagType)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderMarketDeleteRsp>(c, "toTapAPIOrderMarketDeleteRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalInputRsp>(c, "toTapAPIOrderLocalInputRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalModifyRsp>(c, "toTapAPIOrderLocalModifyRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIOrderLocalTransferRsp>(c, "toTapAPIOrderLocalTransferRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFillLocalInputRsp>(c, "toTapAPIFillLocalInputRsp)");
    autocxxpy::caster::try_generate<ITapTrade::TapAPIFillLocalRemoveRsp>(c, "toTapAPIFillLocalRemoveRsp)");
}
