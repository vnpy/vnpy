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


void generate_class_XTP_API_QuoteApi(pybind11::object & parent)
{
    pybind11::class_<
        XTP::API::QuoteApi,
        std::unique_ptr<XTP::API::QuoteApi, pybind11::nodelete>,
        PyQuoteApi
    > c(parent, "QuoteApi");
    if constexpr (std::is_default_constructible_v<PyQuoteApi>)
        c.def(pybind11::init<>());
    c.def_static("CreateQuoteApi",
        &XTP::API::QuoteApi::CreateQuoteApi,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Release",
        &XTP::API::QuoteApi::Release,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetTradingDay",
        &XTP::API::QuoteApi::GetTradingDay,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetApiVersion",
        &XTP::API::QuoteApi::GetApiVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("GetApiLastError",
        &XTP::API::QuoteApi::GetApiLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetUDPBufferSize",
        &XTP::API::QuoteApi::SetUDPBufferSize,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RegisterSpi",
        &XTP::API::QuoteApi::RegisterSpi,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SetHeartBeatInterval",
        &XTP::API::QuoteApi::SetHeartBeatInterval,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeMarketData",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::QuoteApi::SubscribeMarketData
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeMarketData",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::QuoteApi::UnSubscribeMarketData
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeOrderBook",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::QuoteApi::SubscribeOrderBook
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeOrderBook",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::QuoteApi::UnSubscribeOrderBook
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeTickByTick",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::QuoteApi::SubscribeTickByTick
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeTickByTick",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::QuoteApi::UnSubscribeTickByTick
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeAllMarketData",
        &XTP::API::QuoteApi::SubscribeAllMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeAllMarketData",
        &XTP::API::QuoteApi::UnSubscribeAllMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeAllOrderBook",
        &XTP::API::QuoteApi::SubscribeAllOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeAllOrderBook",
        &XTP::API::QuoteApi::UnSubscribeAllOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeAllTickByTick",
        &XTP::API::QuoteApi::SubscribeAllTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeAllTickByTick",
        &XTP::API::QuoteApi::UnSubscribeAllTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Login",
        &XTP::API::QuoteApi::Login,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Logout",
        &XTP::API::QuoteApi::Logout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryAllTickers",
        &XTP::API::QuoteApi::QueryAllTickers,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryTickersPriceInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &XTP::API::QuoteApi::QueryTickersPriceInfo
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 0 + 1/*self*/>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("QueryAllTickersPriceInfo",
        &XTP::API::QuoteApi::QueryAllTickersPriceInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeAllOptionMarketData",
        &XTP::API::QuoteApi::SubscribeAllOptionMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeAllOptionMarketData",
        &XTP::API::QuoteApi::UnSubscribeAllOptionMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeAllOptionOrderBook",
        &XTP::API::QuoteApi::SubscribeAllOptionOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeAllOptionOrderBook",
        &XTP::API::QuoteApi::UnSubscribeAllOptionOrderBook,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribeAllOptionTickByTick",
        &XTP::API::QuoteApi::SubscribeAllOptionTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("UnSubscribeAllOptionTickByTick",
        &XTP::API::QuoteApi::UnSubscribeAllOptionTickByTick,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTP::API::QuoteApi, c);
    module_vnxtp::objects.emplace("XTP::API::QuoteApi", c);
}
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
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "repay_stock_aval_banlance", repay_stock_aval_banlance);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnxtp, XTPQueryAssetRsp, "unknown", unknown);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnxtp, XTPQueryAssetRsp, c);
    module_vnxtp::objects.emplace("XTPQueryAssetRsp", c);
}
