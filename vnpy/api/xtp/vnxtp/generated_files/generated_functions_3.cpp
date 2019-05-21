#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "xtp_trader_api.h"
#include "xtp_quote_api.h"


void generate_class_XTPCrdCashRepayInfo(pybind11::object & parent)
{
    pybind11::class_<XTPCrdCashRepayInfo> c(parent, "XTPCrdCashRepayInfo");
    if constexpr (std::is_default_constructible_v<XTPCrdCashRepayInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayInfo, "xtp_id", xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayInfo, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayInfo, "request_amount", request_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayInfo, "cash_repay_amount", cash_repay_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayInfo, "position_effect", position_effect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayInfo, "error_info", error_info);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPCrdCashRepayInfo, c);
    module_vnxtp::objects.emplace("XTPCrdCashRepayInfo", c);
}
void generate_class_XTPCrdDebtInfo(pybind11::object & parent)
{
    pybind11::class_<XTPCrdDebtInfo> c(parent, "XTPCrdDebtInfo");
    if constexpr (std::is_default_constructible_v<XTPCrdDebtInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "debt_type", debt_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "debt_id", debt_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "position_id", position_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "order_xtp_id", order_xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "debt_status", debt_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "order_date", order_date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "end_date", end_date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "orig_end_date", orig_end_date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "is_extended", is_extended);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "remain_amt", remain_amt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "remain_qty", remain_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "remain_principal", remain_principal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "due_right_qty", due_right_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtInfo, "unknown", unknown);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPCrdDebtInfo, c);
    module_vnxtp::objects.emplace("XTPCrdDebtInfo", c);
}
void generate_class_XTPCrdFundInfo(pybind11::object & parent)
{
    pybind11::class_<XTPCrdFundInfo> c(parent, "XTPCrdFundInfo");
    if constexpr (std::is_default_constructible_v<XTPCrdFundInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdFundInfo, "maintenance_ratio", maintenance_ratio);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdFundInfo, "all_asset", all_asset);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdFundInfo, "all_debt", all_debt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdFundInfo, "line_of_credit", line_of_credit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdFundInfo, "guaranty", guaranty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdFundInfo, "position_amount", position_amount);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPCrdFundInfo, c);
    module_vnxtp::objects.emplace("XTPCrdFundInfo", c);
}
void generate_class_XTPClientQueryCrdDebtStockReq(pybind11::object & parent)
{
    pybind11::class_<XTPClientQueryCrdDebtStockReq> c(parent, "XTPClientQueryCrdDebtStockReq");
    if constexpr (std::is_default_constructible_v<XTPClientQueryCrdDebtStockReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdDebtStockReq, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdDebtStockReq, "ticker", ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPClientQueryCrdDebtStockReq, c);
    module_vnxtp::objects.emplace("XTPClientQueryCrdDebtStockReq", c);
}
void generate_class_XTPCrdDebtStockInfo(pybind11::object & parent)
{
    pybind11::class_<XTPCrdDebtStockInfo> c(parent, "XTPCrdDebtStockInfo");
    if constexpr (std::is_default_constructible_v<XTPCrdDebtStockInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtStockInfo, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtStockInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtStockInfo, "remain_quantity", remain_quantity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdDebtStockInfo, "order_withhold_quantity", order_withhold_quantity);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPCrdDebtStockInfo, c);
    module_vnxtp::objects.emplace("XTPCrdDebtStockInfo", c);
}
void generate_class_XTPClientQueryCrdPositionStockReq(pybind11::object & parent)
{
    pybind11::class_<XTPClientQueryCrdPositionStockReq> c(parent, "XTPClientQueryCrdPositionStockReq");
    if constexpr (std::is_default_constructible_v<XTPClientQueryCrdPositionStockReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStockReq, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStockReq, "ticker", ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPClientQueryCrdPositionStockReq, c);
    module_vnxtp::objects.emplace("XTPClientQueryCrdPositionStockReq", c);
}
void generate_class_XTPClientQueryCrdPositionStkInfo(pybind11::object & parent)
{
    pybind11::class_<XTPClientQueryCrdPositionStkInfo> c(parent, "XTPClientQueryCrdPositionStkInfo");
    if constexpr (std::is_default_constructible_v<XTPClientQueryCrdPositionStkInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStkInfo, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStkInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStkInfo, "limit_qty", limit_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStkInfo, "yesterday_qty", yesterday_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStkInfo, "left_qty", left_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdPositionStkInfo, "frozen_qty", frozen_qty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPClientQueryCrdPositionStkInfo, c);
    module_vnxtp::objects.emplace("XTPClientQueryCrdPositionStkInfo", c);
}
void generate_class_XTPClientQueryCrdSurplusStkReqInfo(pybind11::object & parent)
{
    pybind11::class_<XTPClientQueryCrdSurplusStkReqInfo> c(parent, "XTPClientQueryCrdSurplusStkReqInfo");
    if constexpr (std::is_default_constructible_v<XTPClientQueryCrdSurplusStkReqInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdSurplusStkReqInfo, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdSurplusStkReqInfo, "ticker", ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPClientQueryCrdSurplusStkReqInfo, c);
    module_vnxtp::objects.emplace("XTPClientQueryCrdSurplusStkReqInfo", c);
}
void generate_class_XTPClientQueryCrdSurplusStkRspInfo(pybind11::object & parent)
{
    pybind11::class_<XTPClientQueryCrdSurplusStkRspInfo> c(parent, "XTPClientQueryCrdSurplusStkRspInfo");
    if constexpr (std::is_default_constructible_v<XTPClientQueryCrdSurplusStkRspInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdSurplusStkRspInfo, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdSurplusStkRspInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdSurplusStkRspInfo, "transferable_quantity", transferable_quantity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientQueryCrdSurplusStkRspInfo, "transferred_quantity", transferred_quantity);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPClientQueryCrdSurplusStkRspInfo, c);
    module_vnxtp::objects.emplace("XTPClientQueryCrdSurplusStkRspInfo", c);
}
void generate_class_XTPClientCrdExtendDebtInfo(pybind11::object & parent)
{
    pybind11::class_<XTPClientCrdExtendDebtInfo> c(parent, "XTPClientCrdExtendDebtInfo");
    if constexpr (std::is_default_constructible_v<XTPClientCrdExtendDebtInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientCrdExtendDebtInfo, "xtp_id", xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPClientCrdExtendDebtInfo, "debt_id", debt_id);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPClientCrdExtendDebtInfo, c);
    module_vnxtp::objects.emplace("XTPClientCrdExtendDebtInfo", c);
}
void generate_class_XTPFundTransferReq(pybind11::object & parent)
{
    pybind11::class_<XTPFundTransferReq> c(parent, "XTPFundTransferReq");
    if constexpr (std::is_default_constructible_v<XTPFundTransferReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferReq, "serial_id", serial_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferReq, "fund_account", fund_account);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferReq, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferReq, "amount", amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferReq, "transfer_type", transfer_type);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPFundTransferReq, c);
    module_vnxtp::objects.emplace("XTPFundTransferReq", c);
}
void generate_enum_XTP_LOG_LEVEL(pybind11::object & parent)
{
    pybind11::enum_<XTP_LOG_LEVEL> e(parent, "XTP_LOG_LEVEL", pybind11::arithmetic());
    e.value("XTP_LOG_LEVEL_FATAL", XTP_LOG_LEVEL::XTP_LOG_LEVEL_FATAL);
    e.value("XTP_LOG_LEVEL_ERROR", XTP_LOG_LEVEL::XTP_LOG_LEVEL_ERROR);
    e.value("XTP_LOG_LEVEL_WARNING", XTP_LOG_LEVEL::XTP_LOG_LEVEL_WARNING);
    e.value("XTP_LOG_LEVEL_INFO", XTP_LOG_LEVEL::XTP_LOG_LEVEL_INFO);
    e.value("XTP_LOG_LEVEL_DEBUG", XTP_LOG_LEVEL::XTP_LOG_LEVEL_DEBUG);
    e.value("XTP_LOG_LEVEL_TRACE", XTP_LOG_LEVEL::XTP_LOG_LEVEL_TRACE);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_LOG_LEVEL", e);
}
void generate_enum_XTP_PROTOCOL_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_PROTOCOL_TYPE> e(parent, "XTP_PROTOCOL_TYPE", pybind11::arithmetic());
    e.value("XTP_PROTOCOL_TCP", XTP_PROTOCOL_TYPE::XTP_PROTOCOL_TCP);
    e.value("XTP_PROTOCOL_UDP", XTP_PROTOCOL_TYPE::XTP_PROTOCOL_UDP);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_PROTOCOL_TYPE", e);
}
void generate_enum_XTP_EXCHANGE_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_EXCHANGE_TYPE> e(parent, "XTP_EXCHANGE_TYPE", pybind11::arithmetic());
    e.value("XTP_EXCHANGE_SH", XTP_EXCHANGE_TYPE::XTP_EXCHANGE_SH);
    e.value("XTP_EXCHANGE_SZ", XTP_EXCHANGE_TYPE::XTP_EXCHANGE_SZ);
    e.value("XTP_EXCHANGE_UNKNOWN", XTP_EXCHANGE_TYPE::XTP_EXCHANGE_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_EXCHANGE_TYPE", e);
}
void generate_enum_XTP_MARKET_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_MARKET_TYPE> e(parent, "XTP_MARKET_TYPE", pybind11::arithmetic());
    e.value("XTP_MKT_INIT", XTP_MARKET_TYPE::XTP_MKT_INIT);
    e.value("XTP_MKT_SZ_A", XTP_MARKET_TYPE::XTP_MKT_SZ_A);
    e.value("XTP_MKT_SH_A", XTP_MARKET_TYPE::XTP_MKT_SH_A);
    e.value("XTP_MKT_UNKNOWN", XTP_MARKET_TYPE::XTP_MKT_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_MARKET_TYPE", e);
}
void generate_enum_XTP_PRICE_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_PRICE_TYPE> e(parent, "XTP_PRICE_TYPE", pybind11::arithmetic());
    e.value("XTP_PRICE_LIMIT", XTP_PRICE_TYPE::XTP_PRICE_LIMIT);
    e.value("XTP_PRICE_BEST_OR_CANCEL", XTP_PRICE_TYPE::XTP_PRICE_BEST_OR_CANCEL);
    e.value("XTP_PRICE_BEST5_OR_LIMIT", XTP_PRICE_TYPE::XTP_PRICE_BEST5_OR_LIMIT);
    e.value("XTP_PRICE_BEST5_OR_CANCEL", XTP_PRICE_TYPE::XTP_PRICE_BEST5_OR_CANCEL);
    e.value("XTP_PRICE_ALL_OR_CANCEL", XTP_PRICE_TYPE::XTP_PRICE_ALL_OR_CANCEL);
    e.value("XTP_PRICE_FORWARD_BEST", XTP_PRICE_TYPE::XTP_PRICE_FORWARD_BEST);
    e.value("XTP_PRICE_REVERSE_BEST_LIMIT", XTP_PRICE_TYPE::XTP_PRICE_REVERSE_BEST_LIMIT);
    e.value("XTP_PRICE_LIMIT_OR_CANCEL", XTP_PRICE_TYPE::XTP_PRICE_LIMIT_OR_CANCEL);
    e.value("XTP_PRICE_TYPE_UNKNOWN", XTP_PRICE_TYPE::XTP_PRICE_TYPE_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_PRICE_TYPE", e);
}
void generate_enum_XTP_ORDER_ACTION_STATUS_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_ORDER_ACTION_STATUS_TYPE> e(parent, "XTP_ORDER_ACTION_STATUS_TYPE", pybind11::arithmetic());
    e.value("XTP_ORDER_ACTION_STATUS_SUBMITTED", XTP_ORDER_ACTION_STATUS_TYPE::XTP_ORDER_ACTION_STATUS_SUBMITTED);
    e.value("XTP_ORDER_ACTION_STATUS_ACCEPTED", XTP_ORDER_ACTION_STATUS_TYPE::XTP_ORDER_ACTION_STATUS_ACCEPTED);
    e.value("XTP_ORDER_ACTION_STATUS_REJECTED", XTP_ORDER_ACTION_STATUS_TYPE::XTP_ORDER_ACTION_STATUS_REJECTED);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_ORDER_ACTION_STATUS_TYPE", e);
}
void generate_enum_XTP_ORDER_STATUS_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_ORDER_STATUS_TYPE> e(parent, "XTP_ORDER_STATUS_TYPE", pybind11::arithmetic());
    e.value("XTP_ORDER_STATUS_INIT", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_INIT);
    e.value("XTP_ORDER_STATUS_ALLTRADED", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_ALLTRADED);
    e.value("XTP_ORDER_STATUS_PARTTRADEDQUEUEING", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_PARTTRADEDQUEUEING);
    e.value("XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING);
    e.value("XTP_ORDER_STATUS_NOTRADEQUEUEING", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_NOTRADEQUEUEING);
    e.value("XTP_ORDER_STATUS_CANCELED", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_CANCELED);
    e.value("XTP_ORDER_STATUS_REJECTED", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_REJECTED);
    e.value("XTP_ORDER_STATUS_UNKNOWN", XTP_ORDER_STATUS_TYPE::XTP_ORDER_STATUS_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_ORDER_STATUS_TYPE", e);
}
void generate_enum_XTP_ORDER_SUBMIT_STATUS_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_ORDER_SUBMIT_STATUS_TYPE> e(parent, "XTP_ORDER_SUBMIT_STATUS_TYPE", pybind11::arithmetic());
    e.value("XTP_ORDER_SUBMIT_STATUS_INSERT_SUBMITTED", XTP_ORDER_SUBMIT_STATUS_TYPE::XTP_ORDER_SUBMIT_STATUS_INSERT_SUBMITTED);
    e.value("XTP_ORDER_SUBMIT_STATUS_INSERT_ACCEPTED", XTP_ORDER_SUBMIT_STATUS_TYPE::XTP_ORDER_SUBMIT_STATUS_INSERT_ACCEPTED);
    e.value("XTP_ORDER_SUBMIT_STATUS_INSERT_REJECTED", XTP_ORDER_SUBMIT_STATUS_TYPE::XTP_ORDER_SUBMIT_STATUS_INSERT_REJECTED);
    e.value("XTP_ORDER_SUBMIT_STATUS_CANCEL_SUBMITTED", XTP_ORDER_SUBMIT_STATUS_TYPE::XTP_ORDER_SUBMIT_STATUS_CANCEL_SUBMITTED);
    e.value("XTP_ORDER_SUBMIT_STATUS_CANCEL_REJECTED", XTP_ORDER_SUBMIT_STATUS_TYPE::XTP_ORDER_SUBMIT_STATUS_CANCEL_REJECTED);
    e.value("XTP_ORDER_SUBMIT_STATUS_CANCEL_ACCEPTED", XTP_ORDER_SUBMIT_STATUS_TYPE::XTP_ORDER_SUBMIT_STATUS_CANCEL_ACCEPTED);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_ORDER_SUBMIT_STATUS_TYPE", e);
}
void generate_enum_XTP_TE_RESUME_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_TE_RESUME_TYPE> e(parent, "XTP_TE_RESUME_TYPE", pybind11::arithmetic());
    e.value("XTP_TERT_RESTART", XTP_TE_RESUME_TYPE::XTP_TERT_RESTART);
    e.value("XTP_TERT_RESUME", XTP_TE_RESUME_TYPE::XTP_TERT_RESUME);
    e.value("XTP_TERT_QUICK", XTP_TE_RESUME_TYPE::XTP_TERT_QUICK);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_TE_RESUME_TYPE", e);
}
void generate_enum_ETF_REPLACE_TYPE(pybind11::object & parent)
{
    pybind11::enum_<ETF_REPLACE_TYPE> e(parent, "ETF_REPLACE_TYPE", pybind11::arithmetic());
    e.value("ERT_CASH_FORBIDDEN", ETF_REPLACE_TYPE::ERT_CASH_FORBIDDEN);
    e.value("ERT_CASH_OPTIONAL", ETF_REPLACE_TYPE::ERT_CASH_OPTIONAL);
    e.value("ERT_CASH_MUST", ETF_REPLACE_TYPE::ERT_CASH_MUST);
    e.value("ERT_CASH_RECOMPUTE_INTER_SZ", ETF_REPLACE_TYPE::ERT_CASH_RECOMPUTE_INTER_SZ);
    e.value("ERT_CASH_MUST_INTER_SZ", ETF_REPLACE_TYPE::ERT_CASH_MUST_INTER_SZ);
    e.value("ERT_CASH_RECOMPUTE_INTER_OTHER", ETF_REPLACE_TYPE::ERT_CASH_RECOMPUTE_INTER_OTHER);
    e.value("ERT_CASH_MUST_INTER_OTHER", ETF_REPLACE_TYPE::ERT_CASH_MUST_INTER_OTHER);
    e.value("EPT_INVALID", ETF_REPLACE_TYPE::EPT_INVALID);
    e.export_values();
    module_vnxtp::objects.emplace("ETF_REPLACE_TYPE", e);
}
void generate_enum_XTP_TICKER_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_TICKER_TYPE> e(parent, "XTP_TICKER_TYPE", pybind11::arithmetic());
    e.value("XTP_TICKER_TYPE_STOCK", XTP_TICKER_TYPE::XTP_TICKER_TYPE_STOCK);
    e.value("XTP_TICKER_TYPE_INDEX", XTP_TICKER_TYPE::XTP_TICKER_TYPE_INDEX);
    e.value("XTP_TICKER_TYPE_FUND", XTP_TICKER_TYPE::XTP_TICKER_TYPE_FUND);
    e.value("XTP_TICKER_TYPE_BOND", XTP_TICKER_TYPE::XTP_TICKER_TYPE_BOND);
    e.value("XTP_TICKER_TYPE_OPTION", XTP_TICKER_TYPE::XTP_TICKER_TYPE_OPTION);
    e.value("XTP_TICKER_TYPE_UNKNOWN", XTP_TICKER_TYPE::XTP_TICKER_TYPE_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_TICKER_TYPE", e);
}
void generate_enum_XTP_BUSINESS_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_BUSINESS_TYPE> e(parent, "XTP_BUSINESS_TYPE", pybind11::arithmetic());
    e.value("XTP_BUSINESS_TYPE_CASH", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_CASH);
    e.value("XTP_BUSINESS_TYPE_IPOS", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_IPOS);
    e.value("XTP_BUSINESS_TYPE_REPO", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_REPO);
    e.value("XTP_BUSINESS_TYPE_ETF", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_ETF);
    e.value("XTP_BUSINESS_TYPE_MARGIN", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_MARGIN);
    e.value("XTP_BUSINESS_TYPE_DESIGNATION", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_DESIGNATION);
    e.value("XTP_BUSINESS_TYPE_ALLOTMENT", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_ALLOTMENT);
    e.value("XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION);
    e.value("XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE);
    e.value("XTP_BUSINESS_TYPE_MONEY_FUND", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_MONEY_FUND);
    e.value("XTP_BUSINESS_TYPE_OPTION", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_OPTION);
    e.value("XTP_BUSINESS_TYPE_EXECUTE", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_EXECUTE);
    e.value("XTP_BUSINESS_TYPE_FREEZE", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_FREEZE);
    e.value("XTP_BUSINESS_TYPE_UNKNOWN", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_BUSINESS_TYPE", e);
}
void generate_enum_XTP_ACCOUNT_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_ACCOUNT_TYPE> e(parent, "XTP_ACCOUNT_TYPE", pybind11::arithmetic());
    e.value("XTP_ACCOUNT_NORMAL", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_NORMAL);
    e.value("XTP_ACCOUNT_CREDIT", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_CREDIT);
    e.value("XTP_ACCOUNT_DERIVE", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_DERIVE);
    e.value("XTP_ACCOUNT_UNKNOWN", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_ACCOUNT_TYPE", e);
}
void generate_enum_XTP_FUND_TRANSFER_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_FUND_TRANSFER_TYPE> e(parent, "XTP_FUND_TRANSFER_TYPE", pybind11::arithmetic());
    e.value("XTP_FUND_TRANSFER_OUT", XTP_FUND_TRANSFER_TYPE::XTP_FUND_TRANSFER_OUT);
    e.value("XTP_FUND_TRANSFER_IN", XTP_FUND_TRANSFER_TYPE::XTP_FUND_TRANSFER_IN);
    e.value("XTP_FUND_INTER_TRANSFER_OUT", XTP_FUND_TRANSFER_TYPE::XTP_FUND_INTER_TRANSFER_OUT);
    e.value("XTP_FUND_INTER_TRANSFER_IN", XTP_FUND_TRANSFER_TYPE::XTP_FUND_INTER_TRANSFER_IN);
    e.value("XTP_FUND_TRANSFER_UNKNOWN", XTP_FUND_TRANSFER_TYPE::XTP_FUND_TRANSFER_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_FUND_TRANSFER_TYPE", e);
}
void generate_enum_XTP_FUND_OPER_STATUS(pybind11::object & parent)
{
    pybind11::enum_<XTP_FUND_OPER_STATUS> e(parent, "XTP_FUND_OPER_STATUS", pybind11::arithmetic());
    e.value("XTP_FUND_OPER_PROCESSING", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_PROCESSING);
    e.value("XTP_FUND_OPER_SUCCESS", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_SUCCESS);
    e.value("XTP_FUND_OPER_FAILED", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_FAILED);
    e.value("XTP_FUND_OPER_SUBMITTED", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_SUBMITTED);
    e.value("XTP_FUND_OPER_UNKNOWN", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_FUND_OPER_STATUS", e);
}
void generate_enum_XTP_SPLIT_MERGE_STATUS(pybind11::object & parent)
{
    pybind11::enum_<XTP_SPLIT_MERGE_STATUS> e(parent, "XTP_SPLIT_MERGE_STATUS", pybind11::arithmetic());
    e.value("XTP_SPLIT_MERGE_STATUS_ALLOW", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_ALLOW);
    e.value("XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT);
    e.value("XTP_SPLIT_MERGE_STATUS_ONLY_MERGE", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_ONLY_MERGE);
    e.value("XTP_SPLIT_MERGE_STATUS_FORBIDDEN", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_FORBIDDEN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_SPLIT_MERGE_STATUS", e);
}
void generate_enum_XTP_TBT_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_TBT_TYPE> e(parent, "XTP_TBT_TYPE", pybind11::arithmetic());
    e.value("XTP_TBT_ENTRUST", XTP_TBT_TYPE::XTP_TBT_ENTRUST);
    e.value("XTP_TBT_TRADE", XTP_TBT_TYPE::XTP_TBT_TRADE);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_TBT_TYPE", e);
}
void generate_enum_XTP_OPT_CALL_OR_PUT_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_OPT_CALL_OR_PUT_TYPE> e(parent, "XTP_OPT_CALL_OR_PUT_TYPE", pybind11::arithmetic());
    e.value("XTP_OPT_CALL", XTP_OPT_CALL_OR_PUT_TYPE::XTP_OPT_CALL);
    e.value("XTP_OPT_PUT", XTP_OPT_CALL_OR_PUT_TYPE::XTP_OPT_PUT);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_OPT_CALL_OR_PUT_TYPE", e);
}
void generate_enum_XTP_OPT_EXERCISE_TYPE_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_OPT_EXERCISE_TYPE_TYPE> e(parent, "XTP_OPT_EXERCISE_TYPE_TYPE", pybind11::arithmetic());
    e.value("XTP_OPT_EXERCISE_TYPE_EUR", XTP_OPT_EXERCISE_TYPE_TYPE::XTP_OPT_EXERCISE_TYPE_EUR);
    e.value("XTP_OPT_EXERCISE_TYPE_AME", XTP_OPT_EXERCISE_TYPE_TYPE::XTP_OPT_EXERCISE_TYPE_AME);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_OPT_EXERCISE_TYPE_TYPE", e);
}
void generate_enum_XTP_POSITION_DIRECTION_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_POSITION_DIRECTION_TYPE> e(parent, "XTP_POSITION_DIRECTION_TYPE", pybind11::arithmetic());
    e.value("XTP_POSITION_DIRECTION_NET", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_NET);
    e.value("XTP_POSITION_DIRECTION_LONG", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_LONG);
    e.value("XTP_POSITION_DIRECTION_SHORT", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_SHORT);
    e.value("XTP_POSITION_DIRECTION_COVERED", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_COVERED);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_POSITION_DIRECTION_TYPE", e);
}
void generate_enum_XTP_CRD_CR_STATUS(pybind11::object & parent)
{
    pybind11::enum_<XTP_CRD_CR_STATUS> e(parent, "XTP_CRD_CR_STATUS", pybind11::arithmetic());
    e.value("XTP_CRD_CR_INIT", XTP_CRD_CR_STATUS::XTP_CRD_CR_INIT);
    e.value("XTP_CRD_CR_SUCCESS", XTP_CRD_CR_STATUS::XTP_CRD_CR_SUCCESS);
    e.value("XTP_CRD_CR_FAILED", XTP_CRD_CR_STATUS::XTP_CRD_CR_FAILED);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_CRD_CR_STATUS", e);
}
void generate_enum_XTP_MARKETDATA_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_MARKETDATA_TYPE> e(parent, "XTP_MARKETDATA_TYPE", pybind11::arithmetic());
    e.value("XTP_MARKETDATA_ACTUAL", XTP_MARKETDATA_TYPE::XTP_MARKETDATA_ACTUAL);
    e.value("XTP_MARKETDATA_OPTION", XTP_MARKETDATA_TYPE::XTP_MARKETDATA_OPTION);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_MARKETDATA_TYPE", e);
}
void generate_caster_(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
    autocxxpy::caster::try_generate<XTPRspInfoStruct>(c, "toXTPRspInfoStruct)");
    autocxxpy::caster::try_generate<XTPSpecificTickerStruct>(c, "toXTPSpecificTickerStruct)");
    autocxxpy::caster::try_generate<XTPMarketDataStockExData>(c, "toXTPMarketDataStockExData)");
    autocxxpy::caster::try_generate<XTPMarketDataOptionExData>(c, "toXTPMarketDataOptionExData)");
    autocxxpy::caster::try_generate<XTPMarketDataStruct>(c, "toXTPMarketDataStruct)");
    autocxxpy::caster::try_generate<XTPQuoteStaticInfo>(c, "toXTPQuoteStaticInfo)");
    autocxxpy::caster::try_generate<OrderBookStruct>(c, "toOrderBookStruct)");
    autocxxpy::caster::try_generate<XTPTickByTickEntrust>(c, "toXTPTickByTickEntrust)");
    autocxxpy::caster::try_generate<XTPTickByTickTrade>(c, "toXTPTickByTickTrade)");
    autocxxpy::caster::try_generate<XTPTickByTickStruct>(c, "toXTPTickByTickStruct)");
    autocxxpy::caster::try_generate<XTPTickerPriceInfo>(c, "toXTPTickerPriceInfo)");
    autocxxpy::caster::try_generate<XTPOrderInsertInfo>(c, "toXTPOrderInsertInfo)");
    autocxxpy::caster::try_generate<XTPOrderCancelInfo>(c, "toXTPOrderCancelInfo)");
    autocxxpy::caster::try_generate<XTPOrderInfo>(c, "toXTPOrderInfo)");
    autocxxpy::caster::try_generate<XTPTradeReport>(c, "toXTPTradeReport)");
    autocxxpy::caster::try_generate<XTPQueryOrderReq>(c, "toXTPQueryOrderReq)");
    autocxxpy::caster::try_generate<XTPQueryReportByExecIdReq>(c, "toXTPQueryReportByExecIdReq)");
    autocxxpy::caster::try_generate<XTPQueryTraderReq>(c, "toXTPQueryTraderReq)");
    autocxxpy::caster::try_generate<XTPQueryAssetRsp>(c, "toXTPQueryAssetRsp)");
    autocxxpy::caster::try_generate<XTPQueryStkPositionRsp>(c, "toXTPQueryStkPositionRsp)");
    autocxxpy::caster::try_generate<XTPFundTransferNotice>(c, "toXTPFundTransferNotice)");
    autocxxpy::caster::try_generate<XTPQueryFundTransferLogReq>(c, "toXTPQueryFundTransferLogReq)");
    autocxxpy::caster::try_generate<XTPQueryStructuredFundInfoReq>(c, "toXTPQueryStructuredFundInfoReq)");
    autocxxpy::caster::try_generate<XTPStructuredFundInfo>(c, "toXTPStructuredFundInfo)");
    autocxxpy::caster::try_generate<XTPQueryETFBaseReq>(c, "toXTPQueryETFBaseReq)");
    autocxxpy::caster::try_generate<XTPQueryETFBaseRsp>(c, "toXTPQueryETFBaseRsp)");
    autocxxpy::caster::try_generate<XTPQueryETFComponentReq>(c, "toXTPQueryETFComponentReq)");
    autocxxpy::caster::try_generate<XTPQueryETFComponentRsp>(c, "toXTPQueryETFComponentRsp)");
    autocxxpy::caster::try_generate<XTPQueryIPOTickerRsp>(c, "toXTPQueryIPOTickerRsp)");
    autocxxpy::caster::try_generate<XTPQueryIPOQuotaRsp>(c, "toXTPQueryIPOQuotaRsp)");
    autocxxpy::caster::try_generate<XTPQueryOptionAuctionInfoReq>(c, "toXTPQueryOptionAuctionInfoReq)");
    autocxxpy::caster::try_generate<XTPQueryOptionAuctionInfoRsp>(c, "toXTPQueryOptionAuctionInfoRsp)");
    autocxxpy::caster::try_generate<XTPCrdCashRepayRsp>(c, "toXTPCrdCashRepayRsp)");
    autocxxpy::caster::try_generate<XTPCrdCashRepayDebtInterestFeeRsp>(c, "toXTPCrdCashRepayDebtInterestFeeRsp)");
    autocxxpy::caster::try_generate<XTPCrdCashRepayInfo>(c, "toXTPCrdCashRepayInfo)");
    autocxxpy::caster::try_generate<XTPCrdDebtInfo>(c, "toXTPCrdDebtInfo)");
    autocxxpy::caster::try_generate<XTPCrdFundInfo>(c, "toXTPCrdFundInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdDebtStockReq>(c, "toXTPClientQueryCrdDebtStockReq)");
    autocxxpy::caster::try_generate<XTPCrdDebtStockInfo>(c, "toXTPCrdDebtStockInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdPositionStockReq>(c, "toXTPClientQueryCrdPositionStockReq)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdPositionStkInfo>(c, "toXTPClientQueryCrdPositionStkInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdSurplusStkReqInfo>(c, "toXTPClientQueryCrdSurplusStkReqInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdSurplusStkRspInfo>(c, "toXTPClientQueryCrdSurplusStkRspInfo)");
    autocxxpy::caster::try_generate<XTPClientCrdExtendDebtInfo>(c, "toXTPClientCrdExtendDebtInfo)");
    autocxxpy::caster::try_generate<XTPFundTransferReq>(c, "toXTPFundTransferReq)");
    autocxxpy::caster::try_generate<XTPVersionType>(c, "toXTPVersionType)");
    autocxxpy::caster::try_generate<XTP_LOG_LEVEL>(c, "toXTP_LOG_LEVEL)");
    autocxxpy::caster::try_generate<XTP_PROTOCOL_TYPE>(c, "toXTP_PROTOCOL_TYPE)");
    autocxxpy::caster::try_generate<XTP_EXCHANGE_TYPE>(c, "toXTP_EXCHANGE_TYPE)");
    autocxxpy::caster::try_generate<XTP_MARKET_TYPE>(c, "toXTP_MARKET_TYPE)");
    autocxxpy::caster::try_generate<XTP_PRICE_TYPE>(c, "toXTP_PRICE_TYPE)");
    autocxxpy::caster::try_generate<XTP_SIDE_TYPE>(c, "toXTP_SIDE_TYPE)");
    autocxxpy::caster::try_generate<XTP_POSITION_EFFECT_TYPE>(c, "toXTP_POSITION_EFFECT_TYPE)");
    autocxxpy::caster::try_generate<XTP_ORDER_ACTION_STATUS_TYPE>(c, "toXTP_ORDER_ACTION_STATUS_TYPE)");
    autocxxpy::caster::try_generate<XTP_ORDER_STATUS_TYPE>(c, "toXTP_ORDER_STATUS_TYPE)");
    autocxxpy::caster::try_generate<XTP_ORDER_SUBMIT_STATUS_TYPE>(c, "toXTP_ORDER_SUBMIT_STATUS_TYPE)");
    autocxxpy::caster::try_generate<XTP_TE_RESUME_TYPE>(c, "toXTP_TE_RESUME_TYPE)");
    autocxxpy::caster::try_generate<ETF_REPLACE_TYPE>(c, "toETF_REPLACE_TYPE)");
    autocxxpy::caster::try_generate<XTP_TICKER_TYPE>(c, "toXTP_TICKER_TYPE)");
    autocxxpy::caster::try_generate<XTP_BUSINESS_TYPE>(c, "toXTP_BUSINESS_TYPE)");
    autocxxpy::caster::try_generate<XTP_ACCOUNT_TYPE>(c, "toXTP_ACCOUNT_TYPE)");
    autocxxpy::caster::try_generate<XTP_FUND_TRANSFER_TYPE>(c, "toXTP_FUND_TRANSFER_TYPE)");
    autocxxpy::caster::try_generate<XTP_FUND_OPER_STATUS>(c, "toXTP_FUND_OPER_STATUS)");
    autocxxpy::caster::try_generate<XTP_SPLIT_MERGE_STATUS>(c, "toXTP_SPLIT_MERGE_STATUS)");
    autocxxpy::caster::try_generate<XTP_TBT_TYPE>(c, "toXTP_TBT_TYPE)");
    autocxxpy::caster::try_generate<XTP_OPT_CALL_OR_PUT_TYPE>(c, "toXTP_OPT_CALL_OR_PUT_TYPE)");
    autocxxpy::caster::try_generate<XTP_OPT_EXERCISE_TYPE_TYPE>(c, "toXTP_OPT_EXERCISE_TYPE_TYPE)");
    autocxxpy::caster::try_generate<XTP_POSITION_DIRECTION_TYPE>(c, "toXTP_POSITION_DIRECTION_TYPE)");
    autocxxpy::caster::try_generate<XTP_CRD_CR_STATUS>(c, "toXTP_CRD_CR_STATUS)");
    autocxxpy::caster::try_generate<TXTPTradeTypeType>(c, "toTXTPTradeTypeType)");
    autocxxpy::caster::try_generate<TXTPOrderTypeType>(c, "toTXTPOrderTypeType)");
    autocxxpy::caster::try_generate<XTPRI>(c, "toXTPRI)");
    autocxxpy::caster::try_generate<XTPST>(c, "toXTPST)");
    autocxxpy::caster::try_generate<XTPMD>(c, "toXTPMD)");
    autocxxpy::caster::try_generate<XTPQSI>(c, "toXTPQSI)");
    autocxxpy::caster::try_generate<XTPOB>(c, "toXTPOB)");
    autocxxpy::caster::try_generate<XTPTBT>(c, "toXTPTBT)");
    autocxxpy::caster::try_generate<XTPTPI>(c, "toXTPTPI)");
    autocxxpy::caster::try_generate<XTPQueryOrderRsp>(c, "toXTPQueryOrderRsp)");
    autocxxpy::caster::try_generate<XTPQueryTradeRsp>(c, "toXTPQueryTradeRsp)");
    autocxxpy::caster::try_generate<XTPFundTransferLog>(c, "toXTPFundTransferLog)");
    autocxxpy::caster::try_generate<XTPQueryETFBaseRsp>(c, "toXTPQueryETFBaseRsp)");
    autocxxpy::caster::try_generate<XTPQueryETFComponentReq>(c, "toXTPQueryETFComponentReq)");
    autocxxpy::caster::try_generate<XTPCrdDebtInfo>(c, "toXTPCrdDebtInfo)");
    autocxxpy::caster::try_generate<XTPCrdFundInfo>(c, "toXTPCrdFundInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdDebtStockReq>(c, "toXTPClientQueryCrdDebtStockReq)");
    autocxxpy::caster::try_generate<XTPCrdDebtStockInfo>(c, "toXTPCrdDebtStockInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdPositionStockReq>(c, "toXTPClientQueryCrdPositionStockReq)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdPositionStkInfo>(c, "toXTPClientQueryCrdPositionStkInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdSurplusStkReqInfo>(c, "toXTPClientQueryCrdSurplusStkReqInfo)");
    autocxxpy::caster::try_generate<XTPClientQueryCrdSurplusStkRspInfo>(c, "toXTPClientQueryCrdSurplusStkRspInfo)");
    autocxxpy::caster::try_generate<XTPClientCrdExtendDebtInfo>(c, "toXTPClientCrdExtendDebtInfo)");
    autocxxpy::caster::try_generate<XTPFundTransferAck>(c, "toXTPFundTransferAck)");
}
