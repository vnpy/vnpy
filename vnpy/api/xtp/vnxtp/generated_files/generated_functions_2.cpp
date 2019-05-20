#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "xtp_trader_api.h"
#include "xtp_quote_api.h"


void generate_caster_XTP_API(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
    autocxxpy::caster::try_generate<XTP::API::TraderSpi>(c, "toTraderSpi)");
    autocxxpy::caster::try_generate<XTP::API::TraderApi>(c, "toTraderApi)");
    autocxxpy::caster::try_generate<XTP::API::QuoteSpi>(c, "toQuoteSpi)");
    autocxxpy::caster::try_generate<XTP::API::QuoteApi>(c, "toQuoteApi)");
}
void generate_caster_XTP(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
}
void generate_class_XTPRspInfoStruct(pybind11::object & parent)
{
    pybind11::class_<XTPRspInfoStruct> c(parent, "XTPRspInfoStruct");
    if constexpr (std::is_default_constructible_v<XTPRspInfoStruct>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPRspInfoStruct, "error_id", error_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPRspInfoStruct, "error_msg", error_msg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPRspInfoStruct, c);
    module_vnxtp::objects.emplace("XTPRspInfoStruct", c);
}
void generate_class_XTPSpecificTickerStruct(pybind11::object & parent)
{
    pybind11::class_<XTPSpecificTickerStruct> c(parent, "XTPSpecificTickerStruct");
    if constexpr (std::is_default_constructible_v<XTPSpecificTickerStruct>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPSpecificTickerStruct, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPSpecificTickerStruct, "ticker", ticker);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPSpecificTickerStruct, c);
    module_vnxtp::objects.emplace("XTPSpecificTickerStruct", c);
}
void generate_class_XTPMarketDataStockExData(pybind11::object & parent)
{
    pybind11::class_<XTPMarketDataStockExData> c(parent, "XTPMarketDataStockExData");
    if constexpr (std::is_default_constructible_v<XTPMarketDataStockExData>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "total_bid_qty", total_bid_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "total_ask_qty", total_ask_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "ma_bid_price", ma_bid_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "ma_ask_price", ma_ask_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "ma_bond_bid_price", ma_bond_bid_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "ma_bond_ask_price", ma_bond_ask_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "yield_to_maturity", yield_to_maturity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "iopv", iopv);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "etf_buy_count", etf_buy_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "etf_sell_count", etf_sell_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "etf_buy_qty", etf_buy_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "etf_buy_money", etf_buy_money);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "etf_sell_qty", etf_sell_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "etf_sell_money", etf_sell_money);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "total_warrant_exec_qty", total_warrant_exec_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "warrant_lower_price", warrant_lower_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "warrant_upper_price", warrant_upper_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "cancel_buy_count", cancel_buy_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "cancel_sell_count", cancel_sell_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "cancel_buy_qty", cancel_buy_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "cancel_sell_qty", cancel_sell_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "cancel_buy_money", cancel_buy_money);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "cancel_sell_money", cancel_sell_money);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "total_buy_count", total_buy_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "total_sell_count", total_sell_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "duration_after_buy", duration_after_buy);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "duration_after_sell", duration_after_sell);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "num_bid_orders", num_bid_orders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "num_ask_orders", num_ask_orders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "pre_iopv", pre_iopv);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "r1", r1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStockExData, "r2", r2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPMarketDataStockExData, c);
    module_vnxtp::objects.emplace("XTPMarketDataStockExData", c);
}
void generate_class_XTPMarketDataOptionExData(pybind11::object & parent)
{
    pybind11::class_<XTPMarketDataOptionExData> c(parent, "XTPMarketDataOptionExData");
    if constexpr (std::is_default_constructible_v<XTPMarketDataOptionExData>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataOptionExData, "auction_price", auction_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataOptionExData, "auction_qty", auction_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataOptionExData, "last_enquiry_time", last_enquiry_time);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPMarketDataOptionExData, c);
    module_vnxtp::objects.emplace("XTPMarketDataOptionExData", c);
}
void generate_class_XTPMarketDataStruct(pybind11::object & parent)
{
    pybind11::class_<XTPMarketDataStruct> c(parent, "XTPMarketDataStruct");
    if constexpr (std::is_default_constructible_v<XTPMarketDataStruct>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "last_price", last_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "pre_close_price", pre_close_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "open_price", open_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "high_price", high_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "low_price", low_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "close_price", close_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "pre_total_long_positon", pre_total_long_positon);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "total_long_positon", total_long_positon);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "pre_settl_price", pre_settl_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "settl_price", settl_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "upper_limit_price", upper_limit_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "lower_limit_price", lower_limit_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "pre_delta", pre_delta);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "curr_delta", curr_delta);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "data_time", data_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "turnover", turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "avg_price", avg_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "bid", bid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "ask", ask);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "bid_qty", bid_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "ask_qty", ask_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "trades_count", trades_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "ticker_status", ticker_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "stk", stk);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "opt", opt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "data_type", data_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPMarketDataStruct, "r4", r4);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPMarketDataStruct, c);
    module_vnxtp::objects.emplace("XTPMarketDataStruct", c);
}
void generate_class_XTPQuoteStaticInfo(pybind11::object & parent)
{
    pybind11::class_<XTPQuoteStaticInfo> c(parent, "XTPQuoteStaticInfo");
    if constexpr (std::is_default_constructible_v<XTPQuoteStaticInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "ticker_name", ticker_name);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "ticker_type", ticker_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "pre_close_price", pre_close_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "upper_limit_price", upper_limit_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "lower_limit_price", lower_limit_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "price_tick", price_tick);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "buy_qty_unit", buy_qty_unit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQuoteStaticInfo, "sell_qty_unit", sell_qty_unit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQuoteStaticInfo, c);
    module_vnxtp::objects.emplace("XTPQuoteStaticInfo", c);
}
void generate_class_OrderBookStruct(pybind11::object & parent)
{
    pybind11::class_<OrderBookStruct> c(parent, "OrderBookStruct");
    if constexpr (std::is_default_constructible_v<OrderBookStruct>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "last_price", last_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "turnover", turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "trades_count", trades_count);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "bid", bid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "ask", ask);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "bid_qty", bid_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "ask_qty", ask_qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, OrderBookStruct, "data_time", data_time);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, OrderBookStruct, c);
    module_vnxtp::objects.emplace("OrderBookStruct", c);
}
void generate_class_XTPTickByTickEntrust(pybind11::object & parent)
{
    pybind11::class_<XTPTickByTickEntrust> c(parent, "XTPTickByTickEntrust");
    if constexpr (std::is_default_constructible_v<XTPTickByTickEntrust>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickEntrust, "channel_no", channel_no);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickEntrust, "seq", seq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickEntrust, "price", price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickEntrust, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickEntrust, "side", side);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickEntrust, "ord_type", ord_type);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPTickByTickEntrust, c);
    module_vnxtp::objects.emplace("XTPTickByTickEntrust", c);
}
void generate_class_XTPTickByTickTrade(pybind11::object & parent)
{
    pybind11::class_<XTPTickByTickTrade> c(parent, "XTPTickByTickTrade");
    if constexpr (std::is_default_constructible_v<XTPTickByTickTrade>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "channel_no", channel_no);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "seq", seq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "price", price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "money", money);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "bid_no", bid_no);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "ask_no", ask_no);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickTrade, "trade_flag", trade_flag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPTickByTickTrade, c);
    module_vnxtp::objects.emplace("XTPTickByTickTrade", c);
}
void generate_class_XTPTickByTickStruct(pybind11::object & parent)
{
    pybind11::class_<XTPTickByTickStruct> c(parent, "XTPTickByTickStruct");
    if constexpr (std::is_default_constructible_v<XTPTickByTickStruct>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickStruct, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickStruct, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickStruct, "seq", seq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickStruct, "data_time", data_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickStruct, "type", type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickStruct, "entrust", entrust);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickByTickStruct, "trade", trade);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPTickByTickStruct, c);
    module_vnxtp::objects.emplace("XTPTickByTickStruct", c);
}
void generate_class_XTPTickerPriceInfo(pybind11::object & parent)
{
    pybind11::class_<XTPTickerPriceInfo> c(parent, "XTPTickerPriceInfo");
    if constexpr (std::is_default_constructible_v<XTPTickerPriceInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickerPriceInfo, "exchange_id", exchange_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickerPriceInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTickerPriceInfo, "last_price", last_price);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPTickerPriceInfo, c);
    module_vnxtp::objects.emplace("XTPTickerPriceInfo", c);
}
void generate_class_XTPOrderInsertInfo(pybind11::object & parent)
{
    pybind11::class_<XTPOrderInsertInfo> c(parent, "XTPOrderInsertInfo");
    if constexpr (std::is_default_constructible_v<XTPOrderInsertInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "order_xtp_id", order_xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "order_client_id", order_client_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "price", price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "stop_price", stop_price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "quantity", quantity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "price_type", price_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "side", side);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "position_effect", position_effect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "reserved1", reserved1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "reserved2", reserved2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInsertInfo, "business_type", business_type);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPOrderInsertInfo, c);
    module_vnxtp::objects.emplace("XTPOrderInsertInfo", c);
}
void generate_class_XTPOrderCancelInfo(pybind11::object & parent)
{
    pybind11::class_<XTPOrderCancelInfo> c(parent, "XTPOrderCancelInfo");
    if constexpr (std::is_default_constructible_v<XTPOrderCancelInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderCancelInfo, "order_cancel_xtp_id", order_cancel_xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderCancelInfo, "order_xtp_id", order_xtp_id);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPOrderCancelInfo, c);
    module_vnxtp::objects.emplace("XTPOrderCancelInfo", c);
}
void generate_class_XTPOrderInfo(pybind11::object & parent)
{
    pybind11::class_<XTPOrderInfo> c(parent, "XTPOrderInfo");
    if constexpr (std::is_default_constructible_v<XTPOrderInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_xtp_id", order_xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_client_id", order_client_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_cancel_client_id", order_cancel_client_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_cancel_xtp_id", order_cancel_xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "price", price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "quantity", quantity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "price_type", price_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "side", side);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "position_effect", position_effect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "reserved1", reserved1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "reserved2", reserved2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "business_type", business_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "qty_traded", qty_traded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "qty_left", qty_left);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "insert_time", insert_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "update_time", update_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "cancel_time", cancel_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "trade_amount", trade_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_local_id", order_local_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_status", order_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_submit_status", order_submit_status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPOrderInfo, "order_type", order_type);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPOrderInfo, c);
    module_vnxtp::objects.emplace("XTPOrderInfo", c);
}
void generate_class_XTPTradeReport(pybind11::object & parent)
{
    pybind11::class_<XTPTradeReport> c(parent, "XTPTradeReport");
    if constexpr (std::is_default_constructible_v<XTPTradeReport>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "order_xtp_id", order_xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "order_client_id", order_client_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "market", market);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "local_order_id", local_order_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "exec_id", exec_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "price", price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "quantity", quantity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "trade_time", trade_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "trade_amount", trade_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "report_index", report_index);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "order_exch_id", order_exch_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "trade_type", trade_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "side", side);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "position_effect", position_effect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "reserved1", reserved1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "reserved2", reserved2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "business_type", business_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPTradeReport, "branch_pbu", branch_pbu);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPTradeReport, c);
    module_vnxtp::objects.emplace("XTPTradeReport", c);
}
void generate_class_XTPQueryOrderReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryOrderReq> c(parent, "XTPQueryOrderReq");
    if constexpr (std::is_default_constructible_v<XTPQueryOrderReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOrderReq, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOrderReq, "begin_time", begin_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryOrderReq, "end_time", end_time);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryOrderReq, c);
    module_vnxtp::objects.emplace("XTPQueryOrderReq", c);
}
void generate_class_XTPQueryReportByExecIdReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryReportByExecIdReq> c(parent, "XTPQueryReportByExecIdReq");
    if constexpr (std::is_default_constructible_v<XTPQueryReportByExecIdReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryReportByExecIdReq, "order_xtp_id", order_xtp_id);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryReportByExecIdReq, "exec_id", exec_id);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryReportByExecIdReq, c);
    module_vnxtp::objects.emplace("XTPQueryReportByExecIdReq", c);
}
void generate_class_XTPQueryTraderReq(pybind11::object & parent)
{
    pybind11::class_<XTPQueryTraderReq> c(parent, "XTPQueryTraderReq");
    if constexpr (std::is_default_constructible_v<XTPQueryTraderReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryTraderReq, "ticker", ticker);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryTraderReq, "begin_time", begin_time);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryTraderReq, "end_time", end_time);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryTraderReq, c);
    module_vnxtp::objects.emplace("XTPQueryTraderReq", c);
}
void generate_class_XTPQueryAssetRsp(pybind11::object & parent)
{
    pybind11::class_<XTPQueryAssetRsp> c(parent, "XTPQueryAssetRsp");
    if constexpr (std::is_default_constructible_v<XTPQueryAssetRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "total_asset", total_asset);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "buying_power", buying_power);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "security_asset", security_asset);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "fund_buy_amount", fund_buy_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "fund_buy_fee", fund_buy_fee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "fund_sell_amount", fund_sell_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "fund_sell_fee", fund_sell_fee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "withholding_amount", withholding_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "account_type", account_type);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "frozen_margin", frozen_margin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "frozen_exec_cash", frozen_exec_cash);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "frozen_exec_fee", frozen_exec_fee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "pay_later", pay_later);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "preadva_pay", preadva_pay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "orig_banlance", orig_banlance);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "banlance", banlance);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "deposit_withdraw", deposit_withdraw);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "trade_netting", trade_netting);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "captial_asset", captial_asset);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "force_freeze_amount", force_freeze_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "preferred_amount", preferred_amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "unknown", unknown);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryAssetRsp, c);
    module_vnxtp::objects.emplace("XTPQueryAssetRsp", c);
}
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
