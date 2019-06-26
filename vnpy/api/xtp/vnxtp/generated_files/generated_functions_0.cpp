#include "config.h"

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
    generate_class_XTPCrdCashRepayRsp(parent);
    generate_class_XTPCrdCashRepayDebtInterestFeeRsp(parent);
    generate_class_XTPCrdCashRepayInfo(parent);
    generate_class_XTPCrdDebtInfo(parent);
    generate_class_XTPCrdFundInfo(parent);
    generate_class_XTPClientQueryCrdDebtStockReq(parent);
    generate_class_XTPCrdDebtStockInfo(parent);
    generate_class_XTPClientQueryCrdPositionStockReq(parent);
    generate_class_XTPClientQueryCrdPositionStkInfo(parent);
    generate_class_XTPClientQueryCrdSurplusStkReqInfo(parent);
    generate_class_XTPClientQueryCrdSurplusStkRspInfo(parent);
    generate_class_XTPClientCrdExtendDebtInfo(parent);
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
    generate_enum_XTP_CRD_CR_STATUS(parent);
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
    parent.attr("XTP_CREDIT_DEBT_ID_LEN") = XTP_CREDIT_DEBT_ID_LEN;
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
    parent.attr("XTP_SIDE_STOCK_REPAY_STOCK") = XTP_SIDE_STOCK_REPAY_STOCK;
    parent.attr("XTP_SIDE_SURSTK_TRANS") = XTP_SIDE_SURSTK_TRANS;
    parent.attr("XTP_SIDE_GRTSTK_TRANSIN") = XTP_SIDE_GRTSTK_TRANSIN;
    parent.attr("XTP_SIDE_GRTSTK_TRANSOUT") = XTP_SIDE_GRTSTK_TRANSOUT;
    parent.attr("XTP_SIDE_UNKNOWN") = XTP_SIDE_UNKNOWN;
    parent.attr("XTP_POSITION_EFFECT_INIT") = XTP_POSITION_EFFECT_INIT;
    parent.attr("XTP_POSITION_EFFECT_OPEN") = XTP_POSITION_EFFECT_OPEN;
    parent.attr("XTP_POSITION_EFFECT_CLOSE") = XTP_POSITION_EFFECT_CLOSE;
    parent.attr("XTP_POSITION_EFFECT_FORCECLOSE") = XTP_POSITION_EFFECT_FORCECLOSE;
    parent.attr("XTP_POSITION_EFFECT_CLOSETODAY") = XTP_POSITION_EFFECT_CLOSETODAY;
    parent.attr("XTP_POSITION_EFFECT_CLOSEYESTERDAY") = XTP_POSITION_EFFECT_CLOSEYESTERDAY;
    parent.attr("XTP_POSITION_EFFECT_FORCEOFF") = XTP_POSITION_EFFECT_FORCEOFF;
    parent.attr("XTP_POSITION_EFFECT_LOCALFORCECLOSE") = XTP_POSITION_EFFECT_LOCALFORCECLOSE;
    parent.attr("XTP_POSITION_EFFECT_CREDIT_FORCE_COVER") = XTP_POSITION_EFFECT_CREDIT_FORCE_COVER;
    parent.attr("XTP_POSITION_EFFECT_CREDIT_FORCE_CLEAR") = XTP_POSITION_EFFECT_CREDIT_FORCE_CLEAR;
    parent.attr("XTP_POSITION_EFFECT_CREDIT_FORCE_DEBT") = XTP_POSITION_EFFECT_CREDIT_FORCE_DEBT;
    parent.attr("XTP_POSITION_EFFECT_CREDIT_FORCE_UNCOND") = XTP_POSITION_EFFECT_CREDIT_FORCE_UNCOND;
    parent.attr("XTP_POSITION_EFFECT_UNKNOWN") = XTP_POSITION_EFFECT_UNKNOWN;
    parent.attr("XTP_TRDT_COMMON") = XTP_TRDT_COMMON;
    parent.attr("XTP_TRDT_CASH") = XTP_TRDT_CASH;
    parent.attr("XTP_TRDT_PRIMARY") = XTP_TRDT_PRIMARY;
    parent.attr("XTP_TRDT_CROSS_MKT_CASH") = XTP_TRDT_CROSS_MKT_CASH;
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
    module_vnxtp::cross.record_assign(parent, "XTPCrdDebtInfo", "XTPCrdDebtInfo", "::XTPCrdDebtInfo");
    module_vnxtp::cross.record_assign(parent, "XTPCrdFundInfo", "XTPCrdFundInfo", "::XTPCrdFundInfo");
    module_vnxtp::cross.record_assign(parent, "XTPClientQueryCrdDebtStockReq", "XTPClientQueryCrdDebtStockReq", "::XTPClientQueryCrdDebtStockReq");
    module_vnxtp::cross.record_assign(parent, "XTPCrdDebtStockInfo", "XTPCrdDebtStockInfo", "::XTPCrdDebtStockInfo");
    module_vnxtp::cross.record_assign(parent, "XTPClientQueryCrdPositionStockReq", "XTPClientQueryCrdPositionStockReq", "::XTPClientQueryCrdPositionStockReq");
    module_vnxtp::cross.record_assign(parent, "XTPClientQueryCrdPositionStkInfo", "XTPClientQueryCrdPositionStkInfo", "::XTPClientQueryCrdPositionStkInfo");
    module_vnxtp::cross.record_assign(parent, "XTPClientQueryCrdSurplusStkReqInfo", "XTPClientQueryCrdSurplusStkReqInfo", "::XTPClientQueryCrdSurplusStkReqInfo");
    module_vnxtp::cross.record_assign(parent, "XTPClientQueryCrdSurplusStkRspInfo", "XTPClientQueryCrdSurplusStkRspInfo", "::XTPClientQueryCrdSurplusStkRspInfo");
    module_vnxtp::cross.record_assign(parent, "XTPClientCrdExtendDebtInfo", "XTPClientCrdExtendDebtInfo", "::XTPClientCrdExtendDebtInfo");
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
        &XTP::API::TraderSpi::OnDisconnected,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnError",
        &XTP::API::TraderSpi::OnError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnOrderEvent",
        &XTP::API::TraderSpi::OnOrderEvent,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnTradeEvent",
        &XTP::API::TraderSpi::OnTradeEvent,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnCancelOrderError",
        &XTP::API::TraderSpi::OnCancelOrderError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryOrder",
        &XTP::API::TraderSpi::OnQueryOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryTrade",
        &XTP::API::TraderSpi::OnQueryTrade,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryPosition",
        &XTP::API::TraderSpi::OnQueryPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryAsset",
        &XTP::API::TraderSpi::OnQueryAsset,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryStructuredFund",
        &XTP::API::TraderSpi::OnQueryStructuredFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryFundTransfer",
        &XTP::API::TraderSpi::OnQueryFundTransfer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnFundTransfer",
        &XTP::API::TraderSpi::OnFundTransfer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryETF",
        &XTP::API::TraderSpi::OnQueryETF,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryETFBasket",
        &XTP::API::TraderSpi::OnQueryETFBasket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryIPOInfoList",
        &XTP::API::TraderSpi::OnQueryIPOInfoList,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryIPOQuotaInfo",
        &XTP::API::TraderSpi::OnQueryIPOQuotaInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryOptionAuctionInfo",
        &XTP::API::TraderSpi::OnQueryOptionAuctionInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnCreditCashRepay",
        &XTP::API::TraderSpi::OnCreditCashRepay,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryCreditCashRepayInfo",
        &XTP::API::TraderSpi::OnQueryCreditCashRepayInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryCreditFundInfo",
        &XTP::API::TraderSpi::OnQueryCreditFundInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryCreditDebtInfo",
        &XTP::API::TraderSpi::OnQueryCreditDebtInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryCreditTickerDebtInfo",
        &XTP::API::TraderSpi::OnQueryCreditTickerDebtInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryCreditAssetDebtInfo",
        &XTP::API::TraderSpi::OnQueryCreditAssetDebtInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryCreditTickerAssignInfo",
        &XTP::API::TraderSpi::OnQueryCreditTickerAssignInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryCreditExcessStock",
        &XTP::API::TraderSpi::OnQueryCreditExcessStock,
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
        &XTP::API::TraderApi::CreateTraderApi,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Release",
        &XTP::API::TraderApi::Release,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetTradingDay",
        &XTP::API::TraderApi::GetTradingDay,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RegisterSpi",
        &XTP::API::TraderApi::RegisterSpi,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetApiLastError",
        &XTP::API::TraderApi::GetApiLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetApiVersion",
        &XTP::API::TraderApi::GetApiVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetClientIDByXTPID",
        &XTP::API::TraderApi::GetClientIDByXTPID,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetAccountByXTPID",
        &XTP::API::TraderApi::GetAccountByXTPID,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribePublicTopic",
        &XTP::API::TraderApi::SubscribePublicTopic,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetSoftwareVersion",
        &XTP::API::TraderApi::SetSoftwareVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetSoftwareKey",
        &XTP::API::TraderApi::SetSoftwareKey,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetHeartBeatInterval",
        &XTP::API::TraderApi::SetHeartBeatInterval,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Login",
        &XTP::API::TraderApi::Login,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Logout",
        &XTP::API::TraderApi::Logout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("InsertOrder",
        &XTP::API::TraderApi::InsertOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("CancelOrder",
        &XTP::API::TraderApi::CancelOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryOrderByXTPID",
        &XTP::API::TraderApi::QueryOrderByXTPID,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryOrders",
        &XTP::API::TraderApi::QueryOrders,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryTradesByXTPID",
        &XTP::API::TraderApi::QueryTradesByXTPID,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryTrades",
        &XTP::API::TraderApi::QueryTrades,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryPosition",
        &XTP::API::TraderApi::QueryPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryAsset",
        &XTP::API::TraderApi::QueryAsset,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryStructuredFund",
        &XTP::API::TraderApi::QueryStructuredFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("FundTransfer",
        &XTP::API::TraderApi::FundTransfer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryFundTransfer",
        &XTP::API::TraderApi::QueryFundTransfer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryETF",
        &XTP::API::TraderApi::QueryETF,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryETFTickerBasket",
        &XTP::API::TraderApi::QueryETFTickerBasket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryIPOInfoList",
        &XTP::API::TraderApi::QueryIPOInfoList,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryIPOQuotaInfo",
        &XTP::API::TraderApi::QueryIPOQuotaInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryOptionAuctionInfo",
        &XTP::API::TraderApi::QueryOptionAuctionInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("CreditCashRepay",
        &XTP::API::TraderApi::CreditCashRepay,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryCreditCashRepayInfo",
        &XTP::API::TraderApi::QueryCreditCashRepayInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryCreditFundInfo",
        &XTP::API::TraderApi::QueryCreditFundInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryCreditDebtInfo",
        &XTP::API::TraderApi::QueryCreditDebtInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryCreditTickerDebtInfo",
        &XTP::API::TraderApi::QueryCreditTickerDebtInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryCreditAssetDebtInfo",
        &XTP::API::TraderApi::QueryCreditAssetDebtInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryCreditTickerAssignInfo",
        &XTP::API::TraderApi::QueryCreditTickerAssignInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryCreditExcessStock",
        &XTP::API::TraderApi::QueryCreditExcessStock,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTP::API::TraderApi, c);
    module_vnxtp::objects.emplace("XTP::API::TraderApi", c);
}
void generate_class_XTP_API_QuoteSpi(pybind11::object & parent)
{
    pybind11::class_<XTP::API::QuoteSpi, PyQuoteSpi> c(parent, "QuoteSpi");
    if constexpr (std::is_default_constructible_v<PyQuoteSpi>)
        c.def(pybind11::init<>());
    c.def("OnDisconnected",
        &XTP::API::QuoteSpi::OnDisconnected,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnError",
        &XTP::API::QuoteSpi::OnError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubMarketData",
        &XTP::API::QuoteSpi::OnSubMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubMarketData",
        &XTP::API::QuoteSpi::OnUnSubMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnDepthMarketData",
        &XTP::API::QuoteSpi::OnDepthMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubOrderBook",
        &XTP::API::QuoteSpi::OnSubOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubOrderBook",
        &XTP::API::QuoteSpi::OnUnSubOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnOrderBook",
        &XTP::API::QuoteSpi::OnOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubTickByTick",
        &XTP::API::QuoteSpi::OnSubTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubTickByTick",
        &XTP::API::QuoteSpi::OnUnSubTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnTickByTick",
        &XTP::API::QuoteSpi::OnTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubscribeAllMarketData",
        &XTP::API::QuoteSpi::OnSubscribeAllMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubscribeAllMarketData",
        &XTP::API::QuoteSpi::OnUnSubscribeAllMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubscribeAllOrderBook",
        &XTP::API::QuoteSpi::OnSubscribeAllOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubscribeAllOrderBook",
        &XTP::API::QuoteSpi::OnUnSubscribeAllOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubscribeAllTickByTick",
        &XTP::API::QuoteSpi::OnSubscribeAllTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubscribeAllTickByTick",
        &XTP::API::QuoteSpi::OnUnSubscribeAllTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryAllTickers",
        &XTP::API::QuoteSpi::OnQueryAllTickers,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnQueryTickersPriceInfo",
        &XTP::API::QuoteSpi::OnQueryTickersPriceInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubscribeAllOptionMarketData",
        &XTP::API::QuoteSpi::OnSubscribeAllOptionMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubscribeAllOptionMarketData",
        &XTP::API::QuoteSpi::OnUnSubscribeAllOptionMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubscribeAllOptionOrderBook",
        &XTP::API::QuoteSpi::OnSubscribeAllOptionOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubscribeAllOptionOrderBook",
        &XTP::API::QuoteSpi::OnUnSubscribeAllOptionOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnSubscribeAllOptionTickByTick",
        &XTP::API::QuoteSpi::OnSubscribeAllOptionTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("OnUnSubscribeAllOptionTickByTick",
        &XTP::API::QuoteSpi::OnUnSubscribeAllOptionTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTP::API::QuoteSpi, c);
    module_vnxtp::objects.emplace("XTP::API::QuoteSpi", c);
}
