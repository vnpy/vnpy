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

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


void generate_enum_eMdsMdProductType(pybind11::object & parent)
{
    // _eMdsMdProductType
    pybind11::enum_<_eMdsMdProductType> e(parent, "_eMdsMdProductType", pybind11::arithmetic());
    // _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_STOCK
    e.value("MDS_MD_PRODUCT_TYPE_STOCK", _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_STOCK);
    // _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_INDEX
    e.value("MDS_MD_PRODUCT_TYPE_INDEX", _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_INDEX);
    // _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_OPTION
    e.value("MDS_MD_PRODUCT_TYPE_OPTION", _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_OPTION);
    // _eMdsMdProductType::__MAX_MDS_MD_PRODUCT_TYPE
    e.value("__MAX_MDS_MD_PRODUCT_TYPE", _eMdsMdProductType::__MAX_MDS_MD_PRODUCT_TYPE);
    // _eMdsMdProductType::MDS_SECURITY_TYPE_STOCK
    e.value("MDS_SECURITY_TYPE_STOCK", _eMdsMdProductType::MDS_SECURITY_TYPE_STOCK);
    // _eMdsMdProductType::MDS_SECURITY_TYPE_INDEX
    e.value("MDS_SECURITY_TYPE_INDEX", _eMdsMdProductType::MDS_SECURITY_TYPE_INDEX);
    // _eMdsMdProductType::MDS_SECURITY_TYPE_OPTION
    e.value("MDS_SECURITY_TYPE_OPTION", _eMdsMdProductType::MDS_SECURITY_TYPE_OPTION);
    // _eMdsMdProductType::__MAX_MDS_SECURITY_TYPE
    e.value("__MAX_MDS_SECURITY_TYPE", _eMdsMdProductType::__MAX_MDS_SECURITY_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdProductType", e);
}
void generate_enum_eMdsMdStreamType(pybind11::object & parent)
{
    // _eMdsMdStreamType
    pybind11::enum_<_eMdsMdStreamType> e(parent, "_eMdsMdStreamType", pybind11::arithmetic());
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L1_SNAPSHOT
    e.value("MDS_MD_STREAM_TYPE_L1_SNAPSHOT", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L1_SNAPSHOT);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_INDEX
    e.value("MDS_MD_STREAM_TYPE_INDEX", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_INDEX);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OPTION
    e.value("MDS_MD_STREAM_TYPE_OPTION", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OPTION);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS
    e.value("MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SSE_L1_BOND
    e.value("MDS_MD_STREAM_TYPE_SSE_L1_BOND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SSE_L1_BOND);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SSE_L1_FUND
    e.value("MDS_MD_STREAM_TYPE_SSE_L1_FUND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SSE_L1_FUND);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_SNAPSHOT
    e.value("MDS_MD_STREAM_TYPE_L2_SNAPSHOT", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_SNAPSHOT);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_SNAPSHOT
    e.value("MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_SNAPSHOT", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_SNAPSHOT);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_SNAPSHOT_INCREMENTAL
    e.value("MDS_MD_STREAM_TYPE_L2_SNAPSHOT_INCREMENTAL", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_SNAPSHOT_INCREMENTAL);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_INCREMENTAL
    e.value("MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_INCREMENTAL", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_INCREMENTAL);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW
    e.value("MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW);
    // _eMdsMdStreamType::__MAX_MDS_MD_STREAM_TYPE
    e.value("__MAX_MDS_MD_STREAM_TYPE", _eMdsMdStreamType::__MAX_MDS_MD_STREAM_TYPE);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_BOND
    e.value("MDS_MD_STREAM_TYPE_BOND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_BOND);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_FUND
    e.value("MDS_MD_STREAM_TYPE_FUND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_FUND);
    // _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OTHERS
    e.value("MDS_MD_STREAM_TYPE_OTHERS", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OTHERS);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdStreamType", e);
}
void generate_enum_eMdsMdLevel(pybind11::object & parent)
{
    // _eMdsMdLevel
    pybind11::enum_<_eMdsMdLevel> e(parent, "_eMdsMdLevel", pybind11::arithmetic());
    // _eMdsMdLevel::MDS_MD_LEVEL_0
    e.value("MDS_MD_LEVEL_0", _eMdsMdLevel::MDS_MD_LEVEL_0);
    // _eMdsMdLevel::MDS_MD_LEVEL_1
    e.value("MDS_MD_LEVEL_1", _eMdsMdLevel::MDS_MD_LEVEL_1);
    // _eMdsMdLevel::MDS_MD_LEVEL_2
    e.value("MDS_MD_LEVEL_2", _eMdsMdLevel::MDS_MD_LEVEL_2);
    // _eMdsMdLevel::__MAX_MDS_MD_LEVEL
    e.value("__MAX_MDS_MD_LEVEL", _eMdsMdLevel::__MAX_MDS_MD_LEVEL);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdLevel", e);
}
void generate_enum_eMdsL2PriceLevelOperator(pybind11::object & parent)
{
    // _eMdsL2PriceLevelOperator
    pybind11::enum_<_eMdsL2PriceLevelOperator> e(parent, "_eMdsL2PriceLevelOperator", pybind11::arithmetic());
    // _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_ADD
    e.value("MDS_L2_PX_OPERATOR_ADD", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_ADD);
    // _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_UPDATE
    e.value("MDS_L2_PX_OPERATOR_UPDATE", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_UPDATE);
    // _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_DELETE
    e.value("MDS_L2_PX_OPERATOR_DELETE", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_DELETE);
    // _eMdsL2PriceLevelOperator::__MAX_MDS_L2_PX_OPERATOR
    e.value("__MAX_MDS_L2_PX_OPERATOR", _eMdsL2PriceLevelOperator::__MAX_MDS_L2_PX_OPERATOR);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2PriceLevelOperator", e);
}
void generate_enum_eMdsL2TradeExecType(pybind11::object & parent)
{
    // _eMdsL2TradeExecType
    pybind11::enum_<_eMdsL2TradeExecType> e(parent, "_eMdsL2TradeExecType", pybind11::arithmetic());
    // _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_CANCELED
    e.value("MDS_L2_TRADE_EXECTYPE_CANCELED", _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_CANCELED);
    // _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_TRADE
    e.value("MDS_L2_TRADE_EXECTYPE_TRADE", _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_TRADE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2TradeExecType", e);
}
void generate_enum_eMdsL2TradeBSFlag(pybind11::object & parent)
{
    // _eMdsL2TradeBSFlag
    pybind11::enum_<_eMdsL2TradeBSFlag> e(parent, "_eMdsL2TradeBSFlag", pybind11::arithmetic());
    // _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_BUY
    e.value("MDS_L2_TRADE_BSFLAG_BUY", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_BUY);
    // _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_SELL
    e.value("MDS_L2_TRADE_BSFLAG_SELL", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_SELL);
    // _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_UNKNOWN
    e.value("MDS_L2_TRADE_BSFLAG_UNKNOWN", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_UNKNOWN);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2TradeBSFlag", e);
}
void generate_enum_eMdsL2OrderSideT(pybind11::object & parent)
{
    // _eMdsL2OrderSideT
    pybind11::enum_<_eMdsL2OrderSideT> e(parent, "_eMdsL2OrderSideT", pybind11::arithmetic());
    // _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BUY
    e.value("MDS_L2_ORDER_SIDE_BUY", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BUY);
    // _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_SELL
    e.value("MDS_L2_ORDER_SIDE_SELL", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_SELL);
    // _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BORROW
    e.value("MDS_L2_ORDER_SIDE_BORROW", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BORROW);
    // _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_LEND
    e.value("MDS_L2_ORDER_SIDE_LEND", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_LEND);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2OrderSideT", e);
}
void generate_enum_eMdsL2OrderType(pybind11::object & parent)
{
    // _eMdsL2OrderType
    pybind11::enum_<_eMdsL2OrderType> e(parent, "_eMdsL2OrderType", pybind11::arithmetic());
    // _eMdsL2OrderType::MDS_L2_ORDER_TYPE_MKT
    e.value("MDS_L2_ORDER_TYPE_MKT", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_MKT);
    // _eMdsL2OrderType::MDS_L2_ORDER_TYPE_LMT
    e.value("MDS_L2_ORDER_TYPE_LMT", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_LMT);
    // _eMdsL2OrderType::MDS_L2_ORDER_TYPE_SAMEPARTY_BEST
    e.value("MDS_L2_ORDER_TYPE_SAMEPARTY_BEST", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_SAMEPARTY_BEST);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2OrderType", e);
}
void generate_enum_eMdsClientType(pybind11::object & parent)
{
    // _eMdsClientType
    pybind11::enum_<_eMdsClientType> e(parent, "_eMdsClientType", pybind11::arithmetic());
    // _eMdsClientType::MDS_CLIENT_TYPE_UNDEFINED
    e.value("MDS_CLIENT_TYPE_UNDEFINED", _eMdsClientType::MDS_CLIENT_TYPE_UNDEFINED);
    // _eMdsClientType::MDS_CLIENT_TYPE_INVESTOR
    e.value("MDS_CLIENT_TYPE_INVESTOR", _eMdsClientType::MDS_CLIENT_TYPE_INVESTOR);
    // _eMdsClientType::MDS_CLIENT_TYPE_VIRTUAL
    e.value("MDS_CLIENT_TYPE_VIRTUAL", _eMdsClientType::MDS_CLIENT_TYPE_VIRTUAL);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsClientType", e);
}
void generate_enum_eMdsClientStatus(pybind11::object & parent)
{
    // _eMdsClientStatus
    pybind11::enum_<_eMdsClientStatus> e(parent, "_eMdsClientStatus", pybind11::arithmetic());
    // _eMdsClientStatus::MDS_CLIENT_STATUS_UNACTIVATED
    e.value("MDS_CLIENT_STATUS_UNACTIVATED", _eMdsClientStatus::MDS_CLIENT_STATUS_UNACTIVATED);
    // _eMdsClientStatus::MDS_CLIENT_STATUS_ACTIVATED
    e.value("MDS_CLIENT_STATUS_ACTIVATED", _eMdsClientStatus::MDS_CLIENT_STATUS_ACTIVATED);
    // _eMdsClientStatus::MDS_CLIENT_STATUS_PAUSE
    e.value("MDS_CLIENT_STATUS_PAUSE", _eMdsClientStatus::MDS_CLIENT_STATUS_PAUSE);
    // _eMdsClientStatus::MDS_CLIENT_STATUS_SUSPENDED
    e.value("MDS_CLIENT_STATUS_SUSPENDED", _eMdsClientStatus::MDS_CLIENT_STATUS_SUSPENDED);
    // _eMdsClientStatus::MDS_CLIENT_STATUS_CANCELLED
    e.value("MDS_CLIENT_STATUS_CANCELLED", _eMdsClientStatus::MDS_CLIENT_STATUS_CANCELLED);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsClientStatus", e);
}
void generate_enum_eMdsMsgType(pybind11::object & parent)
{
    // _eMdsMsgType
    pybind11::enum_<_eMdsMsgType> e(parent, "_eMdsMsgType", pybind11::arithmetic());
    // _eMdsMsgType::MDS_MSGTYPE_HEARTBEAT
    e.value("MDS_MSGTYPE_HEARTBEAT", _eMdsMsgType::MDS_MSGTYPE_HEARTBEAT);
    // _eMdsMsgType::MDS_MSGTYPE_TEST_REQUEST
    e.value("MDS_MSGTYPE_TEST_REQUEST", _eMdsMsgType::MDS_MSGTYPE_TEST_REQUEST);
    // _eMdsMsgType::MDS_MSGTYPE_LOGOUT
    e.value("MDS_MSGTYPE_LOGOUT", _eMdsMsgType::MDS_MSGTYPE_LOGOUT);
    // _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_REQUEST
    e.value("MDS_MSGTYPE_MARKET_DATA_REQUEST", _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_REQUEST);
    // _eMdsMsgType::MDS_MSGTYPE_COMPRESSED_PACKETS
    e.value("MDS_MSGTYPE_COMPRESSED_PACKETS", _eMdsMsgType::MDS_MSGTYPE_COMPRESSED_PACKETS);
    // _eMdsMsgType::__MDS_MSGTYPE_SESSION_MAX
    e.value("__MDS_MSGTYPE_SESSION_MAX", _eMdsMsgType::__MDS_MSGTYPE_SESSION_MAX);
    // _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH
    e.value("MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH);
    // _eMdsMsgType::MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH
    e.value("MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH);
    // _eMdsMsgType::MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH
    e.value("MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH);
    // _eMdsMsgType::MDS_MSGTYPE_TRADING_SESSION_STATUS
    e.value("MDS_MSGTYPE_TRADING_SESSION_STATUS", _eMdsMsgType::MDS_MSGTYPE_TRADING_SESSION_STATUS);
    // _eMdsMsgType::MDS_MSGTYPE_SECURITY_STATUS
    e.value("MDS_MSGTYPE_SECURITY_STATUS", _eMdsMsgType::MDS_MSGTYPE_SECURITY_STATUS);
    // _eMdsMsgType::__MDS_MSGTYPE_L1_MAX
    e.value("__MDS_MSGTYPE_L1_MAX", _eMdsMsgType::__MDS_MSGTYPE_L1_MAX);
    // _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT
    e.value("MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT);
    // _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT
    e.value("MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT);
    // _eMdsMsgType::MDS_MSGTYPE_L2_TRADE
    e.value("MDS_MSGTYPE_L2_TRADE", _eMdsMsgType::MDS_MSGTYPE_L2_TRADE);
    // _eMdsMsgType::MDS_MSGTYPE_L2_ORDER
    e.value("MDS_MSGTYPE_L2_ORDER", _eMdsMsgType::MDS_MSGTYPE_L2_ORDER);
    // _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL
    e.value("MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL);
    // _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL
    e.value("MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL", _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL);
    // _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_OVERVIEW
    e.value("MDS_MSGTYPE_L2_MARKET_OVERVIEW", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_OVERVIEW);
    // _eMdsMsgType::MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE
    e.value("MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE", _eMdsMsgType::MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE);
    // _eMdsMsgType::__MDS_MSGTYPE_L2_MAX
    e.value("__MDS_MSGTYPE_L2_MAX", _eMdsMsgType::__MDS_MSGTYPE_L2_MAX);
    // _eMdsMsgType::MDS_MSGTYPE_CMD_CHANGE_PASSWORD
    e.value("MDS_MSGTYPE_CMD_CHANGE_PASSWORD", _eMdsMsgType::MDS_MSGTYPE_CMD_CHANGE_PASSWORD);
    // _eMdsMsgType::__MDS_MSGTYPE_CMD_MAX
    e.value("__MDS_MSGTYPE_CMD_MAX", _eMdsMsgType::__MDS_MSGTYPE_CMD_MAX);
    // _eMdsMsgType::MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT
    e.value("MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT);
    // _eMdsMsgType::MDS_MSGTYPE_QRY_SECURITY_STATUS
    e.value("MDS_MSGTYPE_QRY_SECURITY_STATUS", _eMdsMsgType::MDS_MSGTYPE_QRY_SECURITY_STATUS);
    // _eMdsMsgType::MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS
    e.value("MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS", _eMdsMsgType::MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS);
    // _eMdsMsgType::MDS_MSGTYPE_QRY_STOCK_STATIC_INFO
    e.value("MDS_MSGTYPE_QRY_STOCK_STATIC_INFO", _eMdsMsgType::MDS_MSGTYPE_QRY_STOCK_STATIC_INFO);
    // _eMdsMsgType::MDS_MSGTYPE_QRY_SNAPSHOT_LIST
    e.value("MDS_MSGTYPE_QRY_SNAPSHOT_LIST", _eMdsMsgType::MDS_MSGTYPE_QRY_SNAPSHOT_LIST);
    // _eMdsMsgType::__MDS_MSGTYPE_QRY_MAX
    e.value("__MDS_MSGTYPE_QRY_MAX", _eMdsMsgType::__MDS_MSGTYPE_QRY_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMsgType", e);
}
void generate_enum_eMdsSubscribeMode(pybind11::object & parent)
{
    // _eMdsSubscribeMode
    pybind11::enum_<_eMdsSubscribeMode> e(parent, "_eMdsSubscribeMode", pybind11::arithmetic());
    // _eMdsSubscribeMode::MDS_SUB_MODE_SET
    e.value("MDS_SUB_MODE_SET", _eMdsSubscribeMode::MDS_SUB_MODE_SET);
    // _eMdsSubscribeMode::MDS_SUB_MODE_APPEND
    e.value("MDS_SUB_MODE_APPEND", _eMdsSubscribeMode::MDS_SUB_MODE_APPEND);
    // _eMdsSubscribeMode::MDS_SUB_MODE_DELETE
    e.value("MDS_SUB_MODE_DELETE", _eMdsSubscribeMode::MDS_SUB_MODE_DELETE);
    // _eMdsSubscribeMode::__MAX_MDS_SUB_MODE
    e.value("__MAX_MDS_SUB_MODE", _eMdsSubscribeMode::__MAX_MDS_SUB_MODE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribeMode", e);
}
void generate_enum_eMdsMktSubscribeFlag(pybind11::object & parent)
{
    // _eMdsMktSubscribeFlag
    pybind11::enum_<_eMdsMktSubscribeFlag> e(parent, "_eMdsMktSubscribeFlag", pybind11::arithmetic());
    // _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DEFAULT
    e.value("MDS_MKT_SUB_FLAG_DEFAULT", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DEFAULT);
    // _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_ALL
    e.value("MDS_MKT_SUB_FLAG_ALL", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_ALL);
    // _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DISABLE
    e.value("MDS_MKT_SUB_FLAG_DISABLE", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DISABLE);
    // _eMdsMktSubscribeFlag::__MAX_MDS_MKT_SUB_FLAG
    e.value("__MAX_MDS_MKT_SUB_FLAG", _eMdsMktSubscribeFlag::__MAX_MDS_MKT_SUB_FLAG);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMktSubscribeFlag", e);
}
void generate_enum_eMdsSubscribedTickType(pybind11::object & parent)
{
    // _eMdsSubscribedTickType
    pybind11::enum_<_eMdsSubscribedTickType> e(parent, "_eMdsSubscribedTickType", pybind11::arithmetic());
    // _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_SIMPLIFIED
    e.value("MDS_TICK_TYPE_LATEST_SIMPLIFIED", _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_SIMPLIFIED);
    // _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_TIMELY
    e.value("MDS_TICK_TYPE_LATEST_TIMELY", _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_TIMELY);
    // _eMdsSubscribedTickType::MDS_TICK_TYPE_ALL_INCREMENTS
    e.value("MDS_TICK_TYPE_ALL_INCREMENTS", _eMdsSubscribedTickType::MDS_TICK_TYPE_ALL_INCREMENTS);
    // _eMdsSubscribedTickType::__MAX_MDS_TICK_TYPE
    e.value("__MAX_MDS_TICK_TYPE", _eMdsSubscribedTickType::__MAX_MDS_TICK_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedTickType", e);
}
void generate_enum_eMdsSubscribedTickExpireType(pybind11::object & parent)
{
    // _eMdsSubscribedTickExpireType
    pybind11::enum_<_eMdsSubscribedTickExpireType> e(parent, "_eMdsSubscribedTickExpireType", pybind11::arithmetic());
    // _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_NONE
    e.value("MDS_TICK_EXPIRE_TYPE_NONE", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_NONE);
    // _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_IMMEDIATE
    e.value("MDS_TICK_EXPIRE_TYPE_IMMEDIATE", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_IMMEDIATE);
    // _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMELY
    e.value("MDS_TICK_EXPIRE_TYPE_TIMELY", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMELY);
    // _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMEOUT
    e.value("MDS_TICK_EXPIRE_TYPE_TIMEOUT", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMEOUT);
    // _eMdsSubscribedTickExpireType::__MAX_MDS_TICK_EXPIRE_TYPE
    e.value("__MAX_MDS_TICK_EXPIRE_TYPE", _eMdsSubscribedTickExpireType::__MAX_MDS_TICK_EXPIRE_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedTickExpireType", e);
}
void generate_enum_eMdsSubscribeDataType(pybind11::object & parent)
{
    // _eMdsSubscribeDataType
    pybind11::enum_<_eMdsSubscribeDataType> e(parent, "_eMdsSubscribeDataType", pybind11::arithmetic());
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_DEFAULT
    e.value("MDS_SUB_DATA_TYPE_DEFAULT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_DEFAULT);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L1_SNAPSHOT
    e.value("MDS_SUB_DATA_TYPE_L1_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L1_SNAPSHOT);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_SNAPSHOT
    e.value("MDS_SUB_DATA_TYPE_L2_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_SNAPSHOT);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
    e.value("MDS_SUB_DATA_TYPE_L2_BEST_ORDERS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_BEST_ORDERS);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_TRADE
    e.value("MDS_SUB_DATA_TYPE_L2_TRADE", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_TRADE);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_ORDER
    e.value("MDS_SUB_DATA_TYPE_L2_ORDER", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_ORDER);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW
    e.value("MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS
    e.value("MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_SECURITY_STATUS
    e.value("MDS_SUB_DATA_TYPE_SECURITY_STATUS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_SECURITY_STATUS);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT
    e.value("MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT
    e.value("MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_NONE
    e.value("MDS_SUB_DATA_TYPE_NONE", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_NONE);
    // _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_ALL
    e.value("MDS_SUB_DATA_TYPE_ALL", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_ALL);
    // _eMdsSubscribeDataType::__MAX_MDS_SUB_DATA_TYPE
    e.value("__MAX_MDS_SUB_DATA_TYPE", _eMdsSubscribeDataType::__MAX_MDS_SUB_DATA_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribeDataType", e);
}
void generate_enum_eMdsSubscribedChannelNo(pybind11::object & parent)
{
    // _eMdsSubscribedChannelNo
    pybind11::enum_<_eMdsSubscribedChannelNo> e(parent, "_eMdsSubscribedChannelNo", pybind11::arithmetic());
    // _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_DEFAULT
    e.value("MDS_CHANNEL_NO_DEFAULT", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_DEFAULT);
    // _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ONE
    e.value("MDS_CHANNEL_NO_ONE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ONE);
    // _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_TWO
    e.value("MDS_CHANNEL_NO_TWO", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_TWO);
    // _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_THREE
    e.value("MDS_CHANNEL_NO_THREE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_THREE);
    // _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_FOUR
    e.value("MDS_CHANNEL_NO_FOUR", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_FOUR);
    // _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ALL
    e.value("MDS_CHANNEL_NO_ALL", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ALL);
    // _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_NONE
    e.value("MDS_CHANNEL_NO_NONE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_NONE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedChannelNo", e);
}
void generate_enum_eMdsProtocolHintsType(pybind11::object & parent)
{
    // _eMdsProtocolHintsType
    pybind11::enum_<_eMdsProtocolHintsType> e(parent, "_eMdsProtocolHintsType", pybind11::arithmetic());
    // _eMdsProtocolHintsType::MDS_PROT_HINTS_TYPE_DEFAULT
    e.value("MDS_PROT_HINTS_TYPE_DEFAULT", _eMdsProtocolHintsType::MDS_PROT_HINTS_TYPE_DEFAULT);
    // _eMdsProtocolHintsType::MDS_PROT_HINTS_TYPE_COMPRESS
    e.value("MDS_PROT_HINTS_TYPE_COMPRESS", _eMdsProtocolHintsType::MDS_PROT_HINTS_TYPE_COMPRESS);
    // _eMdsProtocolHintsType::MDS_PROT_HINTS_TYPE_NONE
    e.value("MDS_PROT_HINTS_TYPE_NONE", _eMdsProtocolHintsType::MDS_PROT_HINTS_TYPE_NONE);
    // _eMdsProtocolHintsType::__MAX_MDS_PROT_HINTS_TYPE
    e.value("__MAX_MDS_PROT_HINTS_TYPE", _eMdsProtocolHintsType::__MAX_MDS_PROT_HINTS_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsProtocolHintsType", e);
}
void generate_enum_eMdsApiChannelType(pybind11::object & parent)
{
    // _eMdsApiChannelType
    pybind11::enum_<_eMdsApiChannelType> e(parent, "_eMdsApiChannelType", pybind11::arithmetic());
    // _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_TCP
    e.value("MDSAPI_CHANNEL_TYPE_TCP", _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_TCP);
    // _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_UDP
    e.value("MDSAPI_CHANNEL_TYPE_UDP", _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_UDP);
    // _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_QUERY
    e.value("MDSAPI_CHANNEL_TYPE_QUERY", _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_QUERY);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsApiChannelType", e);
}
void generate_vnoes_enums(pybind11::module & parent)
{
    generate_enum_eOesExchangeId(parent);
    generate_enum_eOesMarketId(parent);
    generate_enum_eOesPlatformId(parent);
    generate_enum_eOesMarketState(parent);
    generate_enum_eOesTrdSessType(parent);
    generate_enum_eOesProductType(parent);
    generate_enum_eOesSecurityType(parent);
    generate_enum_eOesSubSecurityType(parent);
    generate_enum_eOesSecurityLevel(parent);
    generate_enum_eOesSecurityRiskLevel(parent);
    generate_enum_eOesSecuritySuspFlag(parent);
    generate_enum_eOesLotType(parent);
    generate_enum_eOesLotRejReason(parent);
    generate_enum_eOesOrdStatus(parent);
    generate_enum_eOesOrdType(parent);
    generate_enum_eOesOrdTypeSh(parent);
    generate_enum_eOesOrdTypeSz(parent);
    generate_enum_eOesBuySellType(parent);
    generate_enum_eOesOrdDir(parent);
    generate_enum_eOesEtfTrdCnfmType(parent);
    generate_enum_eOesEtfSubFlag(parent);
    generate_enum_eOesExecType(parent);
    generate_enum_eOesCurrType(parent);
    generate_enum_eOesFeeType(parent);
    generate_enum_eOesCalcFeeMode(parent);
    generate_enum_eOesFundTrsfDirect(parent);
    generate_enum_eOesFundTrsfType(parent);
    generate_enum_eOesFundTrsfStatus(parent);
    generate_enum_eOesAcctType(parent);
    generate_enum_eOesCashType(parent);
    generate_enum_eOesAcctStatus(parent);
    generate_enum_eOesTradingPermission(parent);
    generate_enum_eOesTradingLimit(parent);
    generate_enum_eOesQualificationClass(parent);
    generate_enum_eOesInvestorClass(parent);
    generate_enum_eOesCustType(parent);
    generate_enum_eOesOwnerType(parent);
    generate_enum_eOesClientType(parent);
    generate_enum_eOesClientStatus(parent);
    generate_enum_eOesOptContractType(parent);
    generate_enum_eOesOptInvLevel(parent);
    generate_enum_eOpenFlagType(parent);
    generate_enum_eOesOptionOpenFlag(parent);
    generate_enum_eOesPositionEff(parent);
    generate_enum_eOesOptionType(parent);
    generate_enum_eSMsgProtocolType(parent);
    generate_enum_eSMsgFlag(parent);
    generate_enum_eOesMsgType(parent);
    generate_enum_eOesSubscribeReportType(parent);
    generate_enum_eOesProtocolHintsType(parent);
    generate_enum_eSSocketProtocolType(parent);
    generate_enum_eGeneralClientClusterType(parent);
    generate_enum_eGeneralClientEncryptType(parent);
    generate_enum_eOesApiChannelType(parent);
    generate_enum_eMdsExchangeId(parent);
    generate_enum_eMdsMsgSource(parent);
    generate_enum_eMdsMdProductType(parent);
    generate_enum_eMdsMdStreamType(parent);
    generate_enum_eMdsMdLevel(parent);
    generate_enum_eMdsL2PriceLevelOperator(parent);
    generate_enum_eMdsL2TradeExecType(parent);
    generate_enum_eMdsL2TradeBSFlag(parent);
    generate_enum_eMdsL2OrderSideT(parent);
    generate_enum_eMdsL2OrderType(parent);
    generate_enum_eMdsClientType(parent);
    generate_enum_eMdsClientStatus(parent);
    generate_enum_eMdsMsgType(parent);
    generate_enum_eMdsSubscribeMode(parent);
    generate_enum_eMdsMktSubscribeFlag(parent);
    generate_enum_eMdsSubscribedTickType(parent);
    generate_enum_eMdsSubscribedTickExpireType(parent);
    generate_enum_eMdsSubscribeDataType(parent);
    generate_enum_eMdsSubscribedChannelNo(parent);
    generate_enum_eMdsProtocolHintsType(parent);
    generate_enum_eMdsApiChannelType(parent);
}
void generate_vnoes_functions(pybind11::module & parent)
{
    parent.def("__SPlatform_GetErrno",
        &__SPlatform_GetErrno,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_GetNegErrno",
        &__SPlatform_GetNegErrno,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_SetErrno",
        &__SPlatform_SetErrno,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEagain",
        &__SPlatform_IsErrEagain,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEconnaborted",
        &__SPlatform_IsErrEconnaborted,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEtimeout",
        &__SPlatform_IsErrEtimeout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEpipe",
        &__SPlatform_IsErrEpipe,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEintr",
        &__SPlatform_IsErrEintr,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEbadmsg",
        &__SPlatform_IsErrEbadmsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEagain",
        &__SPlatform_IsNegEagain,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEconnaborted",
        &__SPlatform_IsNegEconnaborted,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEtimeout",
        &__SPlatform_IsNegEtimeout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEpipe",
        &__SPlatform_IsNegEpipe,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEintr",
        &__SPlatform_IsNegEintr,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEbadmsg",
        &__SPlatform_IsNegEbadmsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendOrderReq",
        &OesApi_SendOrderReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendOrderCancelReq",
        &OesApi_SendOrderCancelReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendBatchOrdersReq2",
        &OesApi_SendBatchOrdersReq2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendFundTransferReq",
        &OesApi_SendFundTransferReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendChangePasswordReq",
        &OesApi_SendChangePasswordReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_WaitReportMsg",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_WaitReportMsg
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_RecvReportMsg",
        &OesApi_RecvReportMsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetApiVersion",
        &OesApi_GetApiVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetTradingDay",
        &OesApi_GetTradingDay,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetClientOverview",
        &OesApi_GetClientOverview,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleOrder",
        &OesApi_QuerySingleOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleCashAsset",
        &OesApi_QuerySingleCashAsset,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleStkHolding",
        &OesApi_QuerySingleStkHolding,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleOptHolding",
        &OesApi_QuerySingleOptHolding,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOrder",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryOrder
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryTrade",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryTrade
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCashAsset",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryCashAsset
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryStkHolding",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryStkHolding
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOptHolding",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryOptHolding
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryLotWinning",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryLotWinning
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCustInfo",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryCustInfo
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryInvAcct",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryInvAcct
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCommissionRate",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryCommissionRate
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryFundTransferSerial",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryFundTransferSerial
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryIssue",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryIssue
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryStock",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryStock
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryEtf",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryEtf
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryEtfComponent",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryEtfComponent
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOption",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryOption
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryMarketState",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_QueryMarketState
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCounterCash",
        &OesApi_QueryCounterCash,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_Logon",
        &OesApi_Logon,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_LogonReplicaSet",
        &OesApi_LogonReplicaSet,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_LogonPeerNodes",
        &OesApi_LogonPeerNodes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendReportSynchronization",
        &OesApi_SendReportSynchronization,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendHeartbeat",
        &OesApi_SendHeartbeat,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestOrdChannel",
        &OesApi_TestOrdChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestOrdChannel2",
        &OesApi_TestOrdChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestRptChannel",
        &OesApi_TestRptChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestRptChannel2",
        &OesApi_TestRptChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_Logout",
        &OesApi_Logout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_Destory",
        &OesApi_Destory,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAll",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_InitAll
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::inout_argument_transform, 8>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAllByConvention",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_InitAllByConvention
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::inout_argument_transform, 3>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAllByCfgStruct",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_InitAllByCfgStruct
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::inout_argument_transform, 3>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_LogoutAll",
        &OesApi_LogoutAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_DestoryAll",
        &OesApi_DestoryAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitLogger",
        &OesApi_InitLogger,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ResetThreadLoggerName",
        &OesApi_ResetThreadLoggerName,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitOrdChannel",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_InitOrdChannel
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::inout_argument_transform, 4>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitOrdChannel2",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_InitOrdChannel2
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::inout_argument_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitRptChannel",
        &OesApi_InitRptChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitRptChannel2",
        &OesApi_InitRptChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitQryChannel",
        &OesApi_InitQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitQryChannel2",
        &OesApi_InitQryChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ParseAddrListString",
        &OesApi_ParseAddrListString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ParseConfigFromFile",
        &OesApi_ParseConfigFromFile,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ParseAllConfig",
        &OesApi_ParseAllConfig,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitChannelGroup",
        &OesApi_InitChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_DestoryChannelGroup",
        &OesApi_DestoryChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_AddToChannelGroup",
        &OesApi_AddToChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_DeleteFromChannelGroup",
        &OesApi_DeleteFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetFromChannelGroup",
        &OesApi_GetFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetFromChannelGroupBySocket",
        &OesApi_GetFromChannelGroupBySocket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ForeachInChannelGroup",
        c2py::apply_function_transform<
            c2py::function_constant<
                &OesApi_ForeachInChannelGroup
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadUsername",
        &OesApi_SetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetThreadUsername",
        &OesApi_GetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadPassword",
        &OesApi_SetThreadPassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadEnvId",
        &OesApi_SetThreadEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetThreadEnvId",
        &OesApi_GetThreadEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadSubscribeEnvId",
        &OesApi_SetThreadSubscribeEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetThreadSubscribeEnvId",
        &OesApi_GetThreadSubscribeEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedIpAndMac",
        &OesApi_SetCustomizedIpAndMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedIp",
        &OesApi_SetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedMac",
        &OesApi_SetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetCustomizedIp",
        &OesApi_GetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetCustomizedMac",
        &OesApi_GetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedDriverId",
        &OesApi_SetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetCustomizedDriverId",
        &OesApi_GetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetClEnvId",
        &OesApi_GetClEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetLastRecvTime",
        &OesApi_GetLastRecvTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetLastSendTime",
        &OesApi_GetLastSendTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_HasMoreCachedData",
        &OesApi_HasMoreCachedData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidOrdChannel",
        &OesApi_IsValidOrdChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidRptChannel",
        &OesApi_IsValidRptChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidQryChannel",
        &OesApi_IsValidQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidChannelGroup",
        &OesApi_IsValidChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetLastError",
        &OesApi_GetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetLastError",
        &OesApi_SetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetErrorMsg",
        &OesApi_GetErrorMsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetErrorMsg2",
        &OesApi_GetErrorMsg2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesHelper_ExtractOrdReportFromTrd",
        &OesHelper_ExtractOrdReportFromTrd,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_Logon",
        &MdsApi_Logon,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_LogonReplicaSet",
        &MdsApi_LogonReplicaSet,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_LogonPeerNodes",
        &MdsApi_LogonPeerNodes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SyncSubscribeOnLogon",
        &MdsApi_SyncSubscribeOnLogon,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeMarketData",
        &MdsApi_SubscribeMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByString",
        &MdsApi_SubscribeByString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByString2",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_SubscribeByString2
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::string_array_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByStringAndPrefixes",
        &MdsApi_SubscribeByStringAndPrefixes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByStringAndPrefixes2",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_SubscribeByStringAndPrefixes2
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::string_array_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SendHeartbeat",
        &MdsApi_SendHeartbeat,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SendTestRequest",
        &MdsApi_SendTestRequest,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_Logout",
        &MdsApi_Logout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_Destory",
        &MdsApi_Destory,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_WaitOnMsg",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_WaitOnMsg
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_WaitOnMsgCompressible",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_WaitOnMsgCompressible
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetApiVersion",
        &MdsApi_GetApiVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QueryMktDataSnapshot",
        &MdsApi_QueryMktDataSnapshot,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QuerySecurityStatus",
        &MdsApi_QuerySecurityStatus,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QueryTrdSessionStatus",
        &MdsApi_QueryTrdSessionStatus,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QueryStockStaticInfo",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_QueryStockStaticInfo
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QuerySnapshotList",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_QuerySnapshotList
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 4>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QuerySnapshotList2",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_QuerySnapshotList2
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 4>,
                c2py::indexed_transform_holder<c2py::string_array_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SendChangePasswordReq",
        &MdsApi_SendChangePasswordReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ConnectToUdpMcast",
        &MdsApi_ConnectToUdpMcast,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_WaitOnUdpMsg",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_WaitOnUdpMsg
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitAll",
        &MdsApi_InitAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitAllByConvention",
        &MdsApi_InitAllByConvention,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitAllByCfgStruct",
        &MdsApi_InitAllByCfgStruct,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_LogoutAll",
        &MdsApi_LogoutAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DestoryAll",
        &MdsApi_DestoryAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitLogger",
        &MdsApi_InitLogger,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ResetThreadLoggerName",
        &MdsApi_ResetThreadLoggerName,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitTcpChannel",
        &MdsApi_InitTcpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitTcpChannel2",
        &MdsApi_InitTcpChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitQryChannel",
        &MdsApi_InitQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitQryChannel2",
        &MdsApi_InitQryChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitUdpChannel",
        &MdsApi_InitUdpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitUdpChannel2",
        &MdsApi_InitUdpChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseAddrListString",
        &MdsApi_ParseAddrListString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseConfigFromFile",
        &MdsApi_ParseConfigFromFile,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseAllConfig",
        &MdsApi_ParseAllConfig,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitChannelGroup",
        &MdsApi_InitChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DestoryChannelGroup",
        &MdsApi_DestoryChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_AddToChannelGroup",
        &MdsApi_AddToChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DeleteFromChannelGroup",
        &MdsApi_DeleteFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetFromChannelGroup",
        &MdsApi_GetFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetFromChannelGroupBySocket",
        &MdsApi_GetFromChannelGroupBySocket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ForeachInChannelGroup",
        c2py::apply_function_transform<
            c2py::function_constant<
                &MdsApi_ForeachInChannelGroup
            >, 
            brigand::list<
                c2py::indexed_transform_holder<c2py::c_function_callback_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetThreadUsername",
        &MdsApi_SetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetThreadUsername",
        &MdsApi_GetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetThreadPassword",
        &MdsApi_SetThreadPassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedIp",
        &MdsApi_SetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedMac",
        &MdsApi_SetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedIp",
        &MdsApi_GetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedMac",
        &MdsApi_GetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedDriverId",
        &MdsApi_SetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedDriverId",
        &MdsApi_GetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastRecvTime",
        &MdsApi_GetLastRecvTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastSendTime",
        &MdsApi_GetLastSendTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_HasMoreCachedData",
        &MdsApi_HasMoreCachedData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidTcpChannel",
        &MdsApi_IsValidTcpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidQryChannel",
        &MdsApi_IsValidQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidUdpChannel",
        &MdsApi_IsValidUdpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidChannelGroup",
        &MdsApi_IsValidChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastError",
        &MdsApi_GetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetLastError",
        &MdsApi_SetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetErrorMsg",
        &MdsApi_GetErrorMsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetErrorMsg2",
        &MdsApi_GetErrorMsg2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetTickTypeOnSubscribeByString",
        &MdsHelper_SetTickTypeOnSubscribeByString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_ClearSubscribeRequestEntries",
        &MdsHelper_ClearSubscribeRequestEntries,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestMode",
        &MdsHelper_SetSubscribeRequestMode,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestTickType",
        &MdsHelper_SetSubscribeRequestTickType,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestDataTypes",
        &MdsHelper_SetSubscribeRequestDataTypes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestSubFlag",
        &MdsHelper_SetSubscribeRequestSubFlag,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_AddSubscribeRequestEntry",
        &MdsHelper_AddSubscribeRequestEntry,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
}
