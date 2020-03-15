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


void generate_class_TapAPIQuoteCommodityInfo(pybind11::object & parent)
{
    // TapAPIQuoteCommodityInfo
    pybind11::class_<TapAPIQuoteCommodityInfo> c(parent, "TapAPIQuoteCommodityInfo");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteCommodityInfo>)
        c.def(pybind11::init<>());
    // TapAPIQuoteCommodityInfo::Commodity
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "Commodity", Commodity);
    // TapAPIQuoteCommodityInfo::CommodityName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityName", CommodityName);
    // TapAPIQuoteCommodityInfo::CommodityEngName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityEngName", CommodityEngName);
    // TapAPIQuoteCommodityInfo::ContractSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "ContractSize", ContractSize);
    // TapAPIQuoteCommodityInfo::CommodityTickSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityTickSize", CommodityTickSize);
    // TapAPIQuoteCommodityInfo::CommodityDenominator
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityDenominator", CommodityDenominator);
    // TapAPIQuoteCommodityInfo::CmbDirect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CmbDirect", CmbDirect);
    // TapAPIQuoteCommodityInfo::CommodityContractLen
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityContractLen", CommodityContractLen);
    // TapAPIQuoteCommodityInfo::IsDST
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "IsDST", IsDST);
    // TapAPIQuoteCommodityInfo::RelateCommodity1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "RelateCommodity1", RelateCommodity1);
    // TapAPIQuoteCommodityInfo::RelateCommodity2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "RelateCommodity2", RelateCommodity2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteCommodityInfo, c);
    module_vntap::objects.emplace("TapAPIQuoteCommodityInfo", c);
}
void generate_class_TapAPIQuoteContractInfo(pybind11::object & parent)
{
    // TapAPIQuoteContractInfo
    pybind11::class_<TapAPIQuoteContractInfo> c(parent, "TapAPIQuoteContractInfo");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteContractInfo>)
        c.def(pybind11::init<>());
    // TapAPIQuoteContractInfo::Contract
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "Contract", Contract);
    // TapAPIQuoteContractInfo::ContractType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "ContractType", ContractType);
    // TapAPIQuoteContractInfo::QuoteUnderlyingContract
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "QuoteUnderlyingContract", QuoteUnderlyingContract);
    // TapAPIQuoteContractInfo::ContractName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "ContractName", ContractName);
    // TapAPIQuoteContractInfo::ContractExpDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "ContractExpDate", ContractExpDate);
    // TapAPIQuoteContractInfo::LastTradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "LastTradeDate", LastTradeDate);
    // TapAPIQuoteContractInfo::FirstNoticeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "FirstNoticeDate", FirstNoticeDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteContractInfo, c);
    module_vntap::objects.emplace("TapAPIQuoteContractInfo", c);
}
void generate_class_TapAPIQuoteWhole(pybind11::object & parent)
{
    // TapAPIQuoteWhole
    pybind11::class_<TapAPIQuoteWhole> c(parent, "TapAPIQuoteWhole");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteWhole>)
        c.def(pybind11::init<>());
    // TapAPIQuoteWhole::Contract
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "Contract", Contract);
    // TapAPIQuoteWhole::CurrencyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "CurrencyNo", CurrencyNo);
    // TapAPIQuoteWhole::TradingState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "TradingState", TradingState);
    // TapAPIQuoteWhole::DateTimeStamp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "DateTimeStamp", DateTimeStamp);
    // TapAPIQuoteWhole::QPreClosingPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPreClosingPrice", QPreClosingPrice);
    // TapAPIQuoteWhole::QPreSettlePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPreSettlePrice", QPreSettlePrice);
    // TapAPIQuoteWhole::QPrePositionQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPrePositionQty", QPrePositionQty);
    // TapAPIQuoteWhole::QOpeningPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QOpeningPrice", QOpeningPrice);
    // TapAPIQuoteWhole::QLastPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLastPrice", QLastPrice);
    // TapAPIQuoteWhole::QHighPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QHighPrice", QHighPrice);
    // TapAPIQuoteWhole::QLowPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLowPrice", QLowPrice);
    // TapAPIQuoteWhole::QHisHighPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QHisHighPrice", QHisHighPrice);
    // TapAPIQuoteWhole::QHisLowPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QHisLowPrice", QHisLowPrice);
    // TapAPIQuoteWhole::QLimitUpPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLimitUpPrice", QLimitUpPrice);
    // TapAPIQuoteWhole::QLimitDownPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLimitDownPrice", QLimitDownPrice);
    // TapAPIQuoteWhole::QTotalQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalQty", QTotalQty);
    // TapAPIQuoteWhole::QTotalTurnover
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalTurnover", QTotalTurnover);
    // TapAPIQuoteWhole::QPositionQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPositionQty", QPositionQty);
    // TapAPIQuoteWhole::QAveragePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QAveragePrice", QAveragePrice);
    // TapAPIQuoteWhole::QClosingPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QClosingPrice", QClosingPrice);
    // TapAPIQuoteWhole::QSettlePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QSettlePrice", QSettlePrice);
    // TapAPIQuoteWhole::QLastQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLastQty", QLastQty);
    // TapAPIQuoteWhole::QBidPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QBidPrice", QBidPrice);
    // TapAPIQuoteWhole::QBidQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QBidQty", QBidQty);
    // TapAPIQuoteWhole::QAskPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QAskPrice", QAskPrice);
    // TapAPIQuoteWhole::QAskQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QAskQty", QAskQty);
    // TapAPIQuoteWhole::QImpliedBidPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedBidPrice", QImpliedBidPrice);
    // TapAPIQuoteWhole::QImpliedBidQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedBidQty", QImpliedBidQty);
    // TapAPIQuoteWhole::QImpliedAskPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedAskPrice", QImpliedAskPrice);
    // TapAPIQuoteWhole::QImpliedAskQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedAskQty", QImpliedAskQty);
    // TapAPIQuoteWhole::QPreDelta
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPreDelta", QPreDelta);
    // TapAPIQuoteWhole::QCurrDelta
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QCurrDelta", QCurrDelta);
    // TapAPIQuoteWhole::QInsideQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QInsideQty", QInsideQty);
    // TapAPIQuoteWhole::QOutsideQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QOutsideQty", QOutsideQty);
    // TapAPIQuoteWhole::QTurnoverRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTurnoverRate", QTurnoverRate);
    // TapAPIQuoteWhole::Q5DAvgQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "Q5DAvgQty", Q5DAvgQty);
    // TapAPIQuoteWhole::QPERatio
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPERatio", QPERatio);
    // TapAPIQuoteWhole::QTotalValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalValue", QTotalValue);
    // TapAPIQuoteWhole::QNegotiableValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QNegotiableValue", QNegotiableValue);
    // TapAPIQuoteWhole::QPositionTrend
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPositionTrend", QPositionTrend);
    // TapAPIQuoteWhole::QChangeSpeed
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QChangeSpeed", QChangeSpeed);
    // TapAPIQuoteWhole::QChangeRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QChangeRate", QChangeRate);
    // TapAPIQuoteWhole::QChangeValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QChangeValue", QChangeValue);
    // TapAPIQuoteWhole::QSwing
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QSwing", QSwing);
    // TapAPIQuoteWhole::QTotalBidQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalBidQty", QTotalBidQty);
    // TapAPIQuoteWhole::QTotalAskQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalAskQty", QTotalAskQty);
    // TapAPIQuoteWhole::UnderlyContract
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "UnderlyContract", UnderlyContract);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteWhole, c);
    module_vntap::objects.emplace("TapAPIQuoteWhole", c);
}
void generate_class_ITapQuoteAPINotify(pybind11::object & parent)
{
    // ITapQuoteAPINotify
    pybind11::class_<ITapQuoteAPINotify, PyITapQuoteAPINotify> c(parent, "ITapQuoteAPINotify");
    if constexpr (std::is_default_constructible_v<PyITapQuoteAPINotify>)
        c.def(pybind11::init<>());
    // ITapQuoteAPINotify::OnRspLogin
    c.def("OnRspLogin",
        &ITapQuoteAPINotify::OnRspLogin,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPINotify::OnAPIReady
    c.def("OnAPIReady",
        &ITapQuoteAPINotify::OnAPIReady,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPINotify::OnDisconnect
    c.def("OnDisconnect",
        &ITapQuoteAPINotify::OnDisconnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPINotify::OnRspQryCommodity
    c.def("OnRspQryCommodity",
        &ITapQuoteAPINotify::OnRspQryCommodity,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPINotify::OnRspQryContract
    c.def("OnRspQryContract",
        &ITapQuoteAPINotify::OnRspQryContract,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPINotify::OnRspSubscribeQuote
    c.def("OnRspSubscribeQuote",
        &ITapQuoteAPINotify::OnRspSubscribeQuote,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPINotify::OnRspUnSubscribeQuote
    c.def("OnRspUnSubscribeQuote",
        &ITapQuoteAPINotify::OnRspUnSubscribeQuote,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPINotify::OnRtnQuote
    c.def("OnRtnQuote",
        &ITapQuoteAPINotify::OnRtnQuote,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapQuoteAPINotify, c);
    module_vntap::objects.emplace("ITapQuoteAPINotify", c);
}
void generate_class_ITapQuoteAPI(pybind11::object & parent)
{
    // ITapQuoteAPI
    pybind11::class_<ITapQuoteAPI, PyITapQuoteAPI> c(parent, "ITapQuoteAPI");
    if constexpr (std::is_default_constructible_v<PyITapQuoteAPI>)
        c.def(pybind11::init<>());
    // ITapQuoteAPI::SetAPINotify
    c.def("SetAPINotify",
        &ITapQuoteAPI::SetAPINotify,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPI::SetHostAddress
    c.def("SetHostAddress",
        &ITapQuoteAPI::SetHostAddress,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPI::Login
    c.def("Login",
        &ITapQuoteAPI::Login,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPI::Disconnect
    c.def("Disconnect",
        &ITapQuoteAPI::Disconnect,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPI::QryCommodity
    c.def("QryCommodity",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapQuoteAPI::QryCommodity>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPI::QryContract
    c.def("QryContract",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapQuoteAPI::QryContract>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPI::SubscribeQuote
    c.def("SubscribeQuote",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapQuoteAPI::SubscribeQuote>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    // ITapQuoteAPI::UnSubscribeQuote
    c.def("UnSubscribeQuote",
        c2py::output_argument_transform < 
            c2py::function_constant<&ITapQuoteAPI::UnSubscribeQuote>,
            std::integral_constant<int, 0 + 1/*self*/>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapQuoteAPI, c);
    module_vntap::objects.emplace("ITapQuoteAPI", c);
}
void generate_vntap_classes(pybind11::module & parent)
{
    generate_class_TapAPIApplicationInfo(parent);
    generate_class_TapAPICommodity(parent);
    generate_class_TapAPIContract(parent);
    generate_class_TapAPIExchangeInfo(parent);
    generate_class_TapAPIChangePasswordReq(parent);
    generate_class_TapAPIQuoteLoginAuth(parent);
    generate_class_TapAPIQuotLoginRspInfo(parent);
    generate_class_TapAPIQuoteCommodityInfo(parent);
    generate_class_TapAPIQuoteContractInfo(parent);
    generate_class_TapAPIQuoteWhole(parent);
    generate_class_ITapQuoteAPINotify(parent);
    generate_class_ITapQuoteAPI(parent);
}
void generate_vntap_enums(pybind11::module & parent)
{
    
}
void generate_vntap_functions_0(pybind11::module & parent)
{
    parent.def("CreateITapTradeAPI",
        c2py::output_argument_transform < 
            c2py::function_constant<&CreateITapTradeAPI>,
            std::integral_constant<int, 1>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("FreeITapTradeAPI",
        &FreeITapTradeAPI,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("GetITapTradeAPIVersion",
        &GetITapTradeAPIVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetITapTradeAPIDataPath",
        &SetITapTradeAPIDataPath,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetITapTradeAPILogLevel",
        &SetITapTradeAPILogLevel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("GetITapErrorDescribe",
        &GetITapErrorDescribe,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("CreateTapQuoteAPI",
        c2py::output_argument_transform < 
            c2py::function_constant<&CreateTapQuoteAPI>,
            std::integral_constant<int, 1>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("FreeTapQuoteAPI",
        &FreeTapQuoteAPI,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("GetTapQuoteAPIVersion",
        &GetTapQuoteAPIVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetTapQuoteAPIDataPath",
        &SetTapQuoteAPIDataPath,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetTapQuoteAPILogLevel",
        &SetTapQuoteAPILogLevel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
}
void generate_vntap_functions(pybind11::module & parent)
{
    generate_vntap_functions_0(parent);
}
