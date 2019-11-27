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


void generate_class_XTPQueryStkPositionRsp(pybind11::object & parent)
{
    pybind11::class_<XTPQueryStkPositionRsp> c(parent, "XTPQueryStkPositionRsp");
    if constexpr (std::is_default_constructible_v<XTPQueryStkPositionRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "ticker_name", ticker_name);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "total_qty", total_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "sellable_qty", sellable_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "avg_price", avg_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "unrealized_pnl", unrealized_pnl);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "yesterday_position", yesterday_position);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "purchase_redeemable_qty", purchase_redeemable_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "position_direction", position_direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "reserved1", reserved1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "executable_option", executable_option);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "lockable_position", lockable_position);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "executable_underlying", executable_underlying);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "locked_position", locked_position);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "usable_locked_position", usable_locked_position);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStkPositionRsp, "unknown", unknown);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryStkPositionRsp, c);
    module_vnxtp::objects.emplace("XTPQueryStkPositionRsp", c);
}
void generate_class_XTPFundTransferNotice(pybind11::object & parent)
{
    pybind11::class_<XTPFundTransferNotice> c(parent, "XTPFundTransferNotice");
    if constexpr (std::is_default_constructible_v<XTPFundTransferNotice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferNotice, "serial_id", serial_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferNotice, "transfer_type", transfer_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferNotice, "amount", amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferNotice, "oper_status", oper_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPFundTransferNotice, "transfer_time", transfer_time);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPFundTransferNotice, c);
    module_vnxtp::objects.emplace("XTPFundTransferNotice", c);
}
void generate_class_XTPQueryFundTransferLogReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryFundTransferLogReq> c(parent, "XTPQueryFundTransferLogReq");
    if constexpr (std::is_default_constructible_v<XTPQueryFundTransferLogReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryFundTransferLogReq, "serial_id", serial_id);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryFundTransferLogReq, c);
    module_vnxtp::objects.emplace("XTPQueryFundTransferLogReq", c);
}
void generate_class_XTPQueryStructuredFundInfoReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryStructuredFundInfoReq> c(parent, "XTPQueryStructuredFundInfoReq");
    if constexpr (std::is_default_constructible_v<XTPQueryStructuredFundInfoReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStructuredFundInfoReq, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryStructuredFundInfoReq, "sf_ticker", sf_ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryStructuredFundInfoReq, c);
    module_vnxtp::objects.emplace("XTPQueryStructuredFundInfoReq", c);
}
void generate_class_XTPStructuredFundInfo(pybind11::object & parent)
{
    pybind11::class_<XTPStructuredFundInfo> c(parent, "XTPStructuredFundInfo");
    if constexpr (std::is_default_constructible_v<XTPStructuredFundInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "sf_ticker", sf_ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "sf_ticker_name", sf_ticker_name);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "ticker_name", ticker_name);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "split_merge_status", split_merge_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "ratio", ratio);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "min_split_qty", min_split_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "min_merge_qty", min_merge_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPStructuredFundInfo, "net_price", net_price);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPStructuredFundInfo, c);
    module_vnxtp::objects.emplace("XTPStructuredFundInfo", c);
}
void generate_class_XTPQueryETFBaseReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryETFBaseReq> c(parent, "XTPQueryETFBaseReq");
    if constexpr (std::is_default_constructible_v<XTPQueryETFBaseReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseReq, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseReq, "ticker", ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryETFBaseReq, c);
    module_vnxtp::objects.emplace("XTPQueryETFBaseReq", c);
}
void generate_class_XTPQueryETFBaseRsp(pybind11::object & parent)
{
    pybind11::class_<XTPQueryETFBaseRsp> c(parent, "XTPQueryETFBaseRsp");
    if constexpr (std::is_default_constructible_v<XTPQueryETFBaseRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "etf", etf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "subscribe_redemption_ticker", subscribe_redemption_ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "unit", unit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "subscribe_status", subscribe_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "redemption_status", redemption_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "max_cash_ratio", max_cash_ratio);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "estimate_amount", estimate_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "cash_component", cash_component);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "net_value", net_value);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFBaseRsp, "total_amount", total_amount);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryETFBaseRsp, c);
    module_vnxtp::objects.emplace("XTPQueryETFBaseRsp", c);
}
void generate_class_XTPQueryETFComponentReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryETFComponentReq> c(parent, "XTPQueryETFComponentReq");
    if constexpr (std::is_default_constructible_v<XTPQueryETFComponentReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentReq, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentReq, "ticker", ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryETFComponentReq, c);
    module_vnxtp::objects.emplace("XTPQueryETFComponentReq", c);
}
void generate_class_XTPQueryETFComponentRsp(pybind11::object & parent)
{
    pybind11::class_<XTPQueryETFComponentRsp> c(parent, "XTPQueryETFComponentRsp");
    if constexpr (std::is_default_constructible_v<XTPQueryETFComponentRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "component_ticker", component_ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "component_name", component_name);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "quantity", quantity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "component_market", component_market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "replace_type", replace_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "premium_ratio", premium_ratio);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryETFComponentRsp, "amount", amount);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryETFComponentRsp, c);
    module_vnxtp::objects.emplace("XTPQueryETFComponentRsp", c);
}
void generate_class_XTPQueryIPOTickerRsp(pybind11::object & parent)
{
    pybind11::class_<XTPQueryIPOTickerRsp> c(parent, "XTPQueryIPOTickerRsp");
    if constexpr (std::is_default_constructible_v<XTPQueryIPOTickerRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOTickerRsp, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOTickerRsp, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOTickerRsp, "ticker_name", ticker_name);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOTickerRsp, "price", price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOTickerRsp, "unit", unit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOTickerRsp, "qty_upper_limit", qty_upper_limit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryIPOTickerRsp, c);
    module_vnxtp::objects.emplace("XTPQueryIPOTickerRsp", c);
}
void generate_class_XTPQueryIPOQuotaRsp(pybind11::object & parent)
{
    pybind11::class_<XTPQueryIPOQuotaRsp> c(parent, "XTPQueryIPOQuotaRsp");
    if constexpr (std::is_default_constructible_v<XTPQueryIPOQuotaRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOQuotaRsp, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryIPOQuotaRsp, "quantity", quantity);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryIPOQuotaRsp, c);
    module_vnxtp::objects.emplace("XTPQueryIPOQuotaRsp", c);
}
void generate_class_XTPQueryOptionAuctionInfoReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryOptionAuctionInfoReq> c(parent, "XTPQueryOptionAuctionInfoReq");
    if constexpr (std::is_default_constructible_v<XTPQueryOptionAuctionInfoReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoReq, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoReq, "ticker", ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryOptionAuctionInfoReq, c);
    module_vnxtp::objects.emplace("XTPQueryOptionAuctionInfoReq", c);
}
void generate_class_XTPQueryOptionAuctionInfoRsp(pybind11::object & parent)
{
    pybind11::class_<XTPQueryOptionAuctionInfoRsp> c(parent, "XTPQueryOptionAuctionInfoRsp");
    if constexpr (std::is_default_constructible_v<XTPQueryOptionAuctionInfoRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "security_id_source", security_id_source);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "symbol", symbol);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "contract_id", contract_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "underlying_security_id", underlying_security_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "underlying_security_id_source", underlying_security_id_source);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "list_date", list_date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "last_trade_date", last_trade_date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "ticker_type", ticker_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "day_trading", day_trading);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "call_or_put", call_or_put);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "delivery_day", delivery_day);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "delivery_month", delivery_month);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "exercise_type", exercise_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "exercise_begin_date", exercise_begin_date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "exercise_end_date", exercise_end_date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "exercise_price", exercise_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "qty_unit", qty_unit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "contract_unit", contract_unit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "contract_position", contract_position);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "prev_close_price", prev_close_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "prev_clearing_price", prev_clearing_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "lmt_buy_max_qty", lmt_buy_max_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "lmt_buy_min_qty", lmt_buy_min_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "lmt_sell_max_qty", lmt_sell_max_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "lmt_sell_min_qty", lmt_sell_min_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "mkt_buy_max_qty", mkt_buy_max_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "mkt_buy_min_qty", mkt_buy_min_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "mkt_sell_max_qty", mkt_sell_max_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "mkt_sell_min_qty", mkt_sell_min_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "price_tick", price_tick);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "upper_limit_price", upper_limit_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "lower_limit_price", lower_limit_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "sell_margin", sell_margin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "margin_ratio_param1", margin_ratio_param1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "margin_ratio_param2", margin_ratio_param2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, "unknown", unknown);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryOptionAuctionInfoRsp, c);
    module_vnxtp::objects.emplace("XTPQueryOptionAuctionInfoRsp", c);
}
void generate_class_XTPCrdCashRepayRsp(pybind11::object & parent)
{
    pybind11::class_<XTPCrdCashRepayRsp> c(parent, "XTPCrdCashRepayRsp");
    if constexpr (std::is_default_constructible_v<XTPCrdCashRepayRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayRsp, "xtp_id", xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayRsp, "request_amount", request_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayRsp, "cash_repay_amount", cash_repay_amount);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPCrdCashRepayRsp, c);
    module_vnxtp::objects.emplace("XTPCrdCashRepayRsp", c);
}
void generate_class_XTPCrdCashRepayDebtInterestFeeRsp(pybind11::object & parent)
{
    pybind11::class_<XTPCrdCashRepayDebtInterestFeeRsp> c(parent, "XTPCrdCashRepayDebtInterestFeeRsp");
    if constexpr (std::is_default_constructible_v<XTPCrdCashRepayDebtInterestFeeRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayDebtInterestFeeRsp, "xtp_id", xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayDebtInterestFeeRsp, "request_amount", request_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayDebtInterestFeeRsp, "cash_repay_amount", cash_repay_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayDebtInterestFeeRsp, "debt_compact_id", debt_compact_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPCrdCashRepayDebtInterestFeeRsp, "unknow", unknow);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPCrdCashRepayDebtInterestFeeRsp, c);
    module_vnxtp::objects.emplace("XTPCrdCashRepayDebtInterestFeeRsp", c);
}
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
