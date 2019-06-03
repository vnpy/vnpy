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


void generate_class_TapAPIApplicationInfo(pybind11::object & parent)
{
    pybind11::class_<TapAPIApplicationInfo> c(parent, "TapAPIApplicationInfo");
    if constexpr (std::is_default_constructible_v<TapAPIApplicationInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIApplicationInfo, "AuthCode", AuthCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIApplicationInfo, "KeyOperationLogPath", KeyOperationLogPath);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIApplicationInfo, c);
    module_vntap::objects.emplace("TapAPIApplicationInfo", c);
}
void generate_class_TapAPICommodity(pybind11::object & parent)
{
    pybind11::class_<TapAPICommodity> c(parent, "TapAPICommodity");
    if constexpr (std::is_default_constructible_v<TapAPICommodity>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPICommodity, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPICommodity, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPICommodity, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPICommodity, c);
    module_vntap::objects.emplace("TapAPICommodity", c);
}
void generate_class_TapAPIContract(pybind11::object & parent)
{
    pybind11::class_<TapAPIContract> c(parent, "TapAPIContract");
    if constexpr (std::is_default_constructible_v<TapAPIContract>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "Commodity", Commodity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "ContractNo1", ContractNo1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "StrikePrice1", StrikePrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "CallOrPutFlag1", CallOrPutFlag1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "CallOrPutFlag2", CallOrPutFlag2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIContract, c);
    module_vntap::objects.emplace("TapAPIContract", c);
}
void generate_class_TapAPIExchangeInfo(pybind11::object & parent)
{
    pybind11::class_<TapAPIExchangeInfo> c(parent, "TapAPIExchangeInfo");
    if constexpr (std::is_default_constructible_v<TapAPIExchangeInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIExchangeInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIExchangeInfo, "ExchangeName", ExchangeName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIExchangeInfo, c);
    module_vntap::objects.emplace("TapAPIExchangeInfo", c);
}
void generate_class_TapAPIChangePasswordReq(pybind11::object & parent)
{
    pybind11::class_<TapAPIChangePasswordReq> c(parent, "TapAPIChangePasswordReq");
    if constexpr (std::is_default_constructible_v<TapAPIChangePasswordReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIChangePasswordReq, "OldPassword", OldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIChangePasswordReq, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIChangePasswordReq, c);
    module_vntap::objects.emplace("TapAPIChangePasswordReq", c);
}
void generate_class_TapAPIQuoteLoginAuth(pybind11::object & parent)
{
    pybind11::class_<TapAPIQuoteLoginAuth> c(parent, "TapAPIQuoteLoginAuth");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteLoginAuth>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "ISModifyPassword", ISModifyPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "Password", Password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "NewPassword", NewPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "QuoteTempPassword", QuoteTempPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "ISDDA", ISDDA);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "DDASerialNo", DDASerialNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteLoginAuth, c);
    module_vntap::objects.emplace("TapAPIQuoteLoginAuth", c);
}
void generate_class_TapAPIQuotLoginRspInfo(pybind11::object & parent)
{
    pybind11::class_<TapAPIQuotLoginRspInfo> c(parent, "TapAPIQuotLoginRspInfo");
    if constexpr (std::is_default_constructible_v<TapAPIQuotLoginRspInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "UserType", UserType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "UserName", UserName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "QuoteTempPassword", QuoteTempPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "ReservedInfo", ReservedInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLoginIP", LastLoginIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLoginProt", LastLoginProt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLoginTime", LastLoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLogoutTime", LastLogoutTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "TradeDate", TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastSettleTime", LastSettleTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "StartTime", StartTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "InitTime", InitTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuotLoginRspInfo, c);
    module_vntap::objects.emplace("TapAPIQuotLoginRspInfo", c);
}
void generate_class_TapAPIQuoteCommodityInfo(pybind11::object & parent)
{
    pybind11::class_<TapAPIQuoteCommodityInfo> c(parent, "TapAPIQuoteCommodityInfo");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteCommodityInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "Commodity", Commodity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityName", CommodityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityEngName", CommodityEngName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "ContractSize", ContractSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityTickSize", CommodityTickSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityDenominator", CommodityDenominator);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CmbDirect", CmbDirect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "CommodityContractLen", CommodityContractLen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "IsDST", IsDST);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "RelateCommodity1", RelateCommodity1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteCommodityInfo, "RelateCommodity2", RelateCommodity2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteCommodityInfo, c);
    module_vntap::objects.emplace("TapAPIQuoteCommodityInfo", c);
}
void generate_class_TapAPIQuoteContractInfo(pybind11::object & parent)
{
    pybind11::class_<TapAPIQuoteContractInfo> c(parent, "TapAPIQuoteContractInfo");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteContractInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "Contract", Contract);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "ContractType", ContractType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "QuoteUnderlyingContract", QuoteUnderlyingContract);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "ContractName", ContractName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "ContractExpDate", ContractExpDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "LastTradeDate", LastTradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteContractInfo, "FirstNoticeDate", FirstNoticeDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteContractInfo, c);
    module_vntap::objects.emplace("TapAPIQuoteContractInfo", c);
}
void generate_class_TapAPIQuoteWhole(pybind11::object & parent)
{
    pybind11::class_<TapAPIQuoteWhole> c(parent, "TapAPIQuoteWhole");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteWhole>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "Contract", Contract);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "TradingState", TradingState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "DateTimeStamp", DateTimeStamp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPreClosingPrice", QPreClosingPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPreSettlePrice", QPreSettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPrePositionQty", QPrePositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QOpeningPrice", QOpeningPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLastPrice", QLastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QHighPrice", QHighPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLowPrice", QLowPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QHisHighPrice", QHisHighPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QHisLowPrice", QHisLowPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLimitUpPrice", QLimitUpPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLimitDownPrice", QLimitDownPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalQty", QTotalQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalTurnover", QTotalTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPositionQty", QPositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QAveragePrice", QAveragePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QClosingPrice", QClosingPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QSettlePrice", QSettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QLastQty", QLastQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QBidPrice", QBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QBidQty", QBidQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QAskPrice", QAskPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QAskQty", QAskQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedBidPrice", QImpliedBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedBidQty", QImpliedBidQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedAskPrice", QImpliedAskPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QImpliedAskQty", QImpliedAskQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPreDelta", QPreDelta);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QCurrDelta", QCurrDelta);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QInsideQty", QInsideQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QOutsideQty", QOutsideQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTurnoverRate", QTurnoverRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "Q5DAvgQty", Q5DAvgQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPERatio", QPERatio);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalValue", QTotalValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QNegotiableValue", QNegotiableValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QPositionTrend", QPositionTrend);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QChangeSpeed", QChangeSpeed);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QChangeRate", QChangeRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QChangeValue", QChangeValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QSwing", QSwing);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalBidQty", QTotalBidQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "QTotalAskQty", QTotalAskQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteWhole, "UnderlyContract", UnderlyContract);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteWhole, c);
    module_vntap::objects.emplace("TapAPIQuoteWhole", c);
}
void generate_class_ITapQuoteAPINotify(pybind11::object & parent)
{
    pybind11::class_<ITapQuoteAPINotify, PyITapQuoteAPINotify> c(parent, "ITapQuoteAPINotify");
    if constexpr (std::is_default_constructible_v<PyITapQuoteAPINotify>)
        c.def(pybind11::init<>());
    c.def("OnRspLogin",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPINotify::OnRspLogin
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
                &ITapQuoteAPINotify::OnAPIReady
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
                &ITapQuoteAPINotify::OnDisconnect
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
                &ITapQuoteAPINotify::OnRspQryCommodity
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
                &ITapQuoteAPINotify::OnRspQryContract
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspSubscribeQuote",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPINotify::OnRspSubscribeQuote
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRspUnSubscribeQuote",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPINotify::OnRspUnSubscribeQuote
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnRtnQuote",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPINotify::OnRtnQuote
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapQuoteAPINotify, c);
    module_vntap::objects.emplace("ITapQuoteAPINotify", c);
}
void generate_class_ITapQuoteAPI(pybind11::object & parent)
{
    pybind11::class_<ITapQuoteAPI, PyITapQuoteAPI> c(parent, "ITapQuoteAPI");
    if constexpr (std::is_default_constructible_v<PyITapQuoteAPI>)
        c.def(pybind11::init<>());
    c.def("SetAPINotify",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPI::SetAPINotify
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
                &ITapQuoteAPI::SetHostAddress
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
                &ITapQuoteAPI::Login
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
                &ITapQuoteAPI::Disconnect
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QryCommodity",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPI::QryCommodity
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
                &ITapQuoteAPI::QryContract
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeQuote",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPI::SubscribeQuote
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeQuote",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &ITapQuoteAPI::UnSubscribeQuote
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapQuoteAPI, c);
    module_vntap::objects.emplace("ITapQuoteAPI", c);
}
void generate_caster_(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
    autocxxpy::caster::try_generate<TapAPIApplicationInfo>(c, "toTapAPIApplicationInfo)");
    autocxxpy::caster::try_generate<TapAPICommodity>(c, "toTapAPICommodity)");
    autocxxpy::caster::try_generate<TapAPIContract>(c, "toTapAPIContract)");
    autocxxpy::caster::try_generate<TapAPIExchangeInfo>(c, "toTapAPIExchangeInfo)");
    autocxxpy::caster::try_generate<TapAPIChangePasswordReq>(c, "toTapAPIChangePasswordReq)");
    autocxxpy::caster::try_generate<TapAPIQuoteLoginAuth>(c, "toTapAPIQuoteLoginAuth)");
    autocxxpy::caster::try_generate<TapAPIQuotLoginRspInfo>(c, "toTapAPIQuotLoginRspInfo)");
    autocxxpy::caster::try_generate<TapAPIQuoteCommodityInfo>(c, "toTapAPIQuoteCommodityInfo)");
    autocxxpy::caster::try_generate<TapAPIQuoteContractInfo>(c, "toTapAPIQuoteContractInfo)");
    autocxxpy::caster::try_generate<TapAPIQuoteWhole>(c, "toTapAPIQuoteWhole)");
    autocxxpy::caster::try_generate<ITapQuoteAPINotify>(c, "toITapQuoteAPINotify)");
    autocxxpy::caster::try_generate<ITapQuoteAPI>(c, "toITapQuoteAPI)");
    autocxxpy::caster::try_generate<TAPISTR_10>(c, "toTAPISTR_10)");
    autocxxpy::caster::try_generate<TAPISTR_20>(c, "toTAPISTR_20)");
    autocxxpy::caster::try_generate<TAPISTR_30>(c, "toTAPISTR_30)");
    autocxxpy::caster::try_generate<TAPISTR_40>(c, "toTAPISTR_40)");
    autocxxpy::caster::try_generate<TAPISTR_50>(c, "toTAPISTR_50)");
    autocxxpy::caster::try_generate<TAPISTR_70>(c, "toTAPISTR_70)");
    autocxxpy::caster::try_generate<TAPISTR_100>(c, "toTAPISTR_100)");
    autocxxpy::caster::try_generate<TAPISTR_300>(c, "toTAPISTR_300)");
    autocxxpy::caster::try_generate<TAPISTR_500>(c, "toTAPISTR_500)");
    autocxxpy::caster::try_generate<TAPISTR_2000>(c, "toTAPISTR_2000)");
    autocxxpy::caster::try_generate<TAPIAUTHCODE>(c, "toTAPIAUTHCODE)");
    autocxxpy::caster::try_generate<TAPICHAR>(c, "toTAPICHAR)");
    autocxxpy::caster::try_generate<TAPIINT32>(c, "toTAPIINT32)");
    autocxxpy::caster::try_generate<TAPIUINT32>(c, "toTAPIUINT32)");
    autocxxpy::caster::try_generate<TAPIINT64>(c, "toTAPIINT64)");
    autocxxpy::caster::try_generate<TAPIUINT64>(c, "toTAPIUINT64)");
    autocxxpy::caster::try_generate<TAPIUINT16>(c, "toTAPIUINT16)");
    autocxxpy::caster::try_generate<TAPIUINT8>(c, "toTAPIUINT8)");
    autocxxpy::caster::try_generate<TAPIREAL64>(c, "toTAPIREAL64)");
    autocxxpy::caster::try_generate<TAPIYNFLAG>(c, "toTAPIYNFLAG)");
    autocxxpy::caster::try_generate<TAPIDTSTAMP>(c, "toTAPIDTSTAMP)");
    autocxxpy::caster::try_generate<TAPIDATETIME>(c, "toTAPIDATETIME)");
    autocxxpy::caster::try_generate<TAPIDATE>(c, "toTAPIDATE)");
    autocxxpy::caster::try_generate<TAPITIME>(c, "toTAPITIME)");
    autocxxpy::caster::try_generate<TAPILOGLEVEL>(c, "toTAPILOGLEVEL)");
    autocxxpy::caster::try_generate<TAPICommodityType>(c, "toTAPICommodityType)");
    autocxxpy::caster::try_generate<TAPICallOrPutFlagType>(c, "toTAPICallOrPutFlagType)");
    autocxxpy::caster::try_generate<TAPIQPRICE>(c, "toTAPIQPRICE)");
    autocxxpy::caster::try_generate<TAPIQVOLUME>(c, "toTAPIQVOLUME)");
    autocxxpy::caster::try_generate<TAPIQDIFF>(c, "toTAPIQDIFF)");
}
