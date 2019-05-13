#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "xtp_trader_api.h"
#include "xtp_quote_api.h"


void generate_vnxtp(pybind11::module & parent)
{
    {
        auto m = parent.def_submodule("XTP");
        generate_sub_namespace_XTP(m);
    }
    generate_class_XTPRspInfoStruct(parent);
    generate_class_XTPSpecificTickerStruct(parent);
    generate_class_XTPMarketDataStockExData(parent);
    generate_class_XTPMarketDataOptionExData(parent);
    generate_class_XTPMarketDataStruct(parent);
    generate_class_XTPQuoteStaticInfo(parent);
    generate_class_OrderBookStruct(parent);
    generate_class_XTPTickByTickEntrust(parent);
    generate_class_XTPTickByTickTrade(parent);
    generate_class_XTPTickByTickStruct(parent);
    generate_class_XTPTickerPriceInfo(parent);
    generate_class_XTPOrderInsertInfo(parent);
    generate_class_XTPOrderCancelInfo(parent);
    generate_class_XTPOrderInfo(parent);
    generate_class_XTPTradeReport(parent);
    generate_class_XTPQueryOrderReq(parent);
    generate_class_XTPQueryReportByExecIdReq(parent);
    generate_class_XTPQueryTraderReq(parent);
    generate_class_XTPQueryAssetRsp(parent);
    generate_class_XTPQueryStkPositionRsp(parent);
    generate_class_XTPFundTransferNotice(parent);
    generate_class_XTPQueryFundTransferLogReq(parent);
    generate_class_XTPQueryStructuredFundInfoReq(parent);
    generate_class_XTPStructuredFundInfo(parent);
    generate_class_XTPQueryETFBaseReq(parent);
    generate_class_XTPQueryETFBaseRsp(parent);
    generate_class_XTPQueryETFComponentReq(parent);
    generate_class_XTPQueryETFComponentRsp(parent);
    generate_class_XTPQueryIPOTickerRsp(parent);
    generate_class_XTPQueryIPOQuotaRsp(parent);
    generate_class_XTPQueryOptionAuctionInfoReq(parent);
    generate_class_XTPQueryOptionAuctionInfoRsp(parent);
    generate_class_XTPFundTransferReq(parent);
    generate_enum_XTP_LOG_LEVEL(parent);
    generate_enum_XTP_PROTOCOL_TYPE(parent);
    generate_enum_XTP_EXCHANGE_TYPE(parent);
    generate_enum_XTP_MARKET_TYPE(parent);
    generate_enum_XTP_PRICE_TYPE(parent);
    generate_enum_XTP_ORDER_ACTION_STATUS_TYPE(parent);
    generate_enum_XTP_ORDER_STATUS_TYPE(parent);
    generate_enum_XTP_ORDER_SUBMIT_STATUS_TYPE(parent);
    generate_enum_XTP_TE_RESUME_TYPE(parent);
    generate_enum_ETF_REPLACE_TYPE(parent);
    generate_enum_XTP_TICKER_TYPE(parent);
    generate_enum_XTP_BUSINESS_TYPE(parent);
    generate_enum_XTP_ACCOUNT_TYPE(parent);
    generate_enum_XTP_FUND_TRANSFER_TYPE(parent);
    generate_enum_XTP_FUND_OPER_STATUS(parent);
    generate_enum_XTP_SPLIT_MERGE_STATUS(parent);
    generate_enum_XTP_TBT_TYPE(parent);
    generate_enum_XTP_OPT_CALL_OR_PUT_TYPE(parent);
    generate_enum_XTP_OPT_EXERCISE_TYPE_TYPE(parent);
    generate_enum_XTP_POSITION_DIRECTION_TYPE(parent);
    generate_enum_XTP_MARKETDATA_TYPE(parent);
    parent.attr("XTP_VERSION_LEN") = XTP_VERSION_LEN;
    parent.attr("XTP_TRADING_DAY_LEN") = XTP_TRADING_DAY_LEN;
    parent.attr("XTP_TICKER_LEN") = XTP_TICKER_LEN;
    parent.attr("XTP_TICKER_NAME_LEN") = XTP_TICKER_NAME_LEN;
    parent.attr("XTP_LOCAL_ORDER_LEN") = XTP_LOCAL_ORDER_LEN;
    parent.attr("XTP_ORDER_EXCH_LEN") = XTP_ORDER_EXCH_LEN;
    parent.attr("XTP_EXEC_ID_LEN") = XTP_EXEC_ID_LEN;
    parent.attr("XTP_BRANCH_PBU_LEN") = XTP_BRANCH_PBU_LEN;
    parent.attr("XTP_ACCOUNT_NAME_LEN") = XTP_ACCOUNT_NAME_LEN;
    parent.attr("XTP_SIDE_BUY") = XTP_SIDE_BUY;
    parent.attr("XTP_SIDE_SELL") = XTP_SIDE_SELL;
    parent.attr("XTP_SIDE_PURCHASE") = XTP_SIDE_PURCHASE;
    parent.attr("XTP_SIDE_REDEMPTION") = XTP_SIDE_REDEMPTION;
    parent.attr("XTP_SIDE_SPLIT") = XTP_SIDE_SPLIT;
    parent.attr("XTP_SIDE_MERGE") = XTP_SIDE_MERGE;
    parent.attr("XTP_SIDE_COVER") = XTP_SIDE_COVER;
    parent.attr("XTP_SIDE_FREEZE") = XTP_SIDE_FREEZE;
    parent.attr("XTP_SIDE_MARGIN_TRADE") = XTP_SIDE_MARGIN_TRADE;
    parent.attr("XTP_SIDE_SHORT_SELL") = XTP_SIDE_SHORT_SELL;
    parent.attr("XTP_SIDE_REPAY_MARGIN") = XTP_SIDE_REPAY_MARGIN;
    parent.attr("XTP_SIDE_REPAY_STOCK") = XTP_SIDE_REPAY_STOCK;
    parent.attr("XTP_SIDE_CASH_REPAY_MARGIN") = XTP_SIDE_CASH_REPAY_MARGIN;
    parent.attr("XTP_SIDE_STOCK_REPAY_STOCK") = XTP_SIDE_STOCK_REPAY_STOCK;
    parent.attr("XTP_SIDE_UNKNOWN") = XTP_SIDE_UNKNOWN;
    parent.attr("XTP_POSITION_EFFECT_INIT") = XTP_POSITION_EFFECT_INIT;
    parent.attr("XTP_POSITION_EFFECT_OPEN") = XTP_POSITION_EFFECT_OPEN;
    parent.attr("XTP_POSITION_EFFECT_CLOSE") = XTP_POSITION_EFFECT_CLOSE;
    parent.attr("XTP_POSITION_EFFECT_FORCECLOSE") = XTP_POSITION_EFFECT_FORCECLOSE;
    parent.attr("XTP_POSITION_EFFECT_CLOSETODAY") = XTP_POSITION_EFFECT_CLOSETODAY;
    parent.attr("XTP_POSITION_EFFECT_CLOSEYESTERDAY") = XTP_POSITION_EFFECT_CLOSEYESTERDAY;
    parent.attr("XTP_POSITION_EFFECT_FORCEOFF") = XTP_POSITION_EFFECT_FORCEOFF;
    parent.attr("XTP_POSITION_EFFECT_LOCALFORCECLOSE") = XTP_POSITION_EFFECT_LOCALFORCECLOSE;
    parent.attr("XTP_POSITION_EFFECT_UNKNOWN") = XTP_POSITION_EFFECT_UNKNOWN;
    parent.attr("XTP_TRDT_COMMON") = XTP_TRDT_COMMON;
    parent.attr("XTP_TRDT_CASH") = XTP_TRDT_CASH;
    parent.attr("XTP_TRDT_PRIMARY") = XTP_TRDT_PRIMARY;
    parent.attr("XTP_ORDT_Normal") = XTP_ORDT_Normal;
    parent.attr("XTP_ORDT_DeriveFromQuote") = XTP_ORDT_DeriveFromQuote;
    parent.attr("XTP_ORDT_DeriveFromCombination") = XTP_ORDT_DeriveFromCombination;
    parent.attr("XTP_ORDT_Combination") = XTP_ORDT_Combination;
    parent.attr("XTP_ORDT_ConditionalOrder") = XTP_ORDT_ConditionalOrder;
    parent.attr("XTP_ORDT_Swap") = XTP_ORDT_Swap;
    parent.attr("XTP_ERR_MSG_LEN") = XTP_ERR_MSG_LEN;
    parent.attr("XTP_ACCOUNT_PASSWORD_LEN") = XTP_ACCOUNT_PASSWORD_LEN;
    module_vnxtp::cross.record_assign(parent, "XTPRI", "XTPRI", "::XTPRspInfoStruct");
    module_vnxtp::cross.record_assign(parent, "XTPST", "XTPST", "::XTPSpecificTickerStruct");
    module_vnxtp::cross.record_assign(parent, "XTPMD", "XTPMD", "::XTPMarketDataStruct");
    module_vnxtp::cross.record_assign(parent, "XTPQSI", "XTPQSI", "::XTPQuoteStaticInfo");
    module_vnxtp::cross.record_assign(parent, "XTPOB", "XTPOB", "::OrderBookStruct");
    module_vnxtp::cross.record_assign(parent, "XTPTBT", "XTPTBT", "::XTPTickByTickStruct");
    module_vnxtp::cross.record_assign(parent, "XTPTPI", "XTPTPI", "::XTPTickerPriceInfo");
    module_vnxtp::cross.record_assign(parent, "XTPQueryOrderRsp", "XTPQueryOrderRsp", "::XTPOrderInfo");
    module_vnxtp::cross.record_assign(parent, "XTPQueryTradeRsp", "XTPQueryTradeRsp", "::XTPTradeReport");
    module_vnxtp::cross.record_assign(parent, "XTPFundTransferLog", "XTPFundTransferLog", "::XTPFundTransferNotice");
    module_vnxtp::cross.record_assign(parent, "XTPQueryETFBaseRsp", "XTPQueryETFBaseRsp", "::XTPQueryETFBaseRsp");
    module_vnxtp::cross.record_assign(parent, "XTPQueryETFComponentReq", "XTPQueryETFComponentReq", "::XTPQueryETFComponentReq");
    module_vnxtp::cross.record_assign(parent, "XTPFundTransferAck", "XTPFundTransferAck", "::XTPFundTransferNotice");
    generate_caster_(parent);
}
void generate_sub_namespace_XTP(pybind11::module & parent)
{
    {
        auto m = parent.def_submodule("API");
        generate_sub_namespace_XTP_API(m);
    }
    generate_caster_XTP(parent);
}
void generate_sub_namespace_XTP_API(pybind11::module & parent)
{
    generate_class_XTP_API_TraderSpi(parent);
    generate_class_XTP_API_TraderApi(parent);
    generate_class_XTP_API_QuoteSpi(parent);
    generate_class_XTP_API_QuoteApi(parent);
    generate_caster_XTP_API(parent);
}
void generate_class_XTP_API_TraderSpi(pybind11::object & parent)
{
    pybind11::class_<XTP::API::TraderSpi, PyTraderSpi> c(parent, "TraderSpi");
    if constexpr (std::is_default_constructible_v<PyTraderSpi>)
        c.def(pybind11::init<>());
    c.def("OnDisconnected",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnDisconnected
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnError",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnError
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnOrderEvent",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnOrderEvent
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnTradeEvent",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnTradeEvent
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnCancelOrderError",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnCancelOrderError
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryOrder
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryTrade",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryTrade
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryPosition",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryPosition
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryAsset",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryAsset
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryStructuredFund",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryStructuredFund
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryFundTransfer",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryFundTransfer
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnFundTransfer",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnFundTransfer
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryETF",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryETF
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryETFBasket",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryETFBasket
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryIPOInfoList",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryIPOInfoList
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryIPOQuotaInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryIPOQuotaInfo
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryOptionAuctionInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderSpi::OnQueryOptionAuctionInfo
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTP::API::TraderSpi, c);
    module_vnxtp::objects.emplace("XTP::API::TraderSpi", c);
}
void generate_class_XTP_API_TraderApi(pybind11::object & parent)
{
    pybind11::class_<
        XTP::API::TraderApi,
        std::unique_ptr<XTP::API::TraderApi, pybind11::nodelete>,
        PyTraderApi
    > c(parent, "TraderApi");
    if constexpr (std::is_default_constructible_v<PyTraderApi>)
        c.def(pybind11::init<>());
    c.def_static("CreateTraderApi",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::CreateTraderApi
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Release",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::Release
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetTradingDay",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::GetTradingDay
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RegisterSpi",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::RegisterSpi
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetApiLastError",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::GetApiLastError
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetApiVersion",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::GetApiVersion
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetClientIDByXTPID",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::GetClientIDByXTPID
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetAccountByXTPID",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::GetAccountByXTPID
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribePublicTopic",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::SubscribePublicTopic
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetSoftwareVersion",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::SetSoftwareVersion
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetSoftwareKey",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::SetSoftwareKey
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetHeartBeatInterval",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::SetHeartBeatInterval
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
                &XTP::API::TraderApi::Login
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Logout",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::Logout
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("InsertOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::InsertOrder
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("CancelOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::CancelOrder
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryOrderByXTPID",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryOrderByXTPID
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryOrders",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryOrders
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryTradesByXTPID",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryTradesByXTPID
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryTrades",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryTrades
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryPosition",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryPosition
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryAsset",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryAsset
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryStructuredFund",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryStructuredFund
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("FundTransfer",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::FundTransfer
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryFundTransfer",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryFundTransfer
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryETF",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryETF
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryETFTickerBasket",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryETFTickerBasket
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryIPOInfoList",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryIPOInfoList
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryIPOQuotaInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryIPOQuotaInfo
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryOptionAuctionInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::TraderApi::QueryOptionAuctionInfo
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTP::API::TraderApi, c);
    module_vnxtp::objects.emplace("XTP::API::TraderApi", c);
}
