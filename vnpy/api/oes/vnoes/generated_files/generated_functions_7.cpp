#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


void generate_enum_eMdsExchangeId(pybind11::object & parent)
{
    pybind11::enum_<_eMdsExchangeId> e(parent, "_eMdsExchangeId", pybind11::arithmetic());
    e.value("MDS_EXCH_SSE", _eMdsExchangeId::MDS_EXCH_SSE);
    e.value("MDS_EXCH_SZSE", _eMdsExchangeId::MDS_EXCH_SZSE);
    e.value("__MAX_MDS_EXCH", _eMdsExchangeId::__MAX_MDS_EXCH);
    e.value("__MAX_MDS_EXCH_ALIGNED4", _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED4);
    e.value("__MAX_MDS_EXCH_ALIGNED8", _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsExchangeId", e);
}
void generate_enum_eMdsMsgSource(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMsgSource> e(parent, "_eMdsMsgSource", pybind11::arithmetic());
    e.value("MDS_MSGSRC_UNDEFINED", _eMdsMsgSource::MDS_MSGSRC_UNDEFINED);
    e.value("MDS_MSGSRC_EZEI_TCP", _eMdsMsgSource::MDS_MSGSRC_EZEI_TCP);
    e.value("MDS_MSGSRC_EZEI_UDP", _eMdsMsgSource::MDS_MSGSRC_EZEI_UDP);
    e.value("MDS_MSGSRC_VDE_LEVEL2", _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL2);
    e.value("MDS_MSGSRC_VDE_LEVEL1", _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL1);
    e.value("MDS_MSGSRC_SZSE_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_BINARY);
    e.value("MDS_MSGSRC_SZSE_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_STEP);
    e.value("MDS_MSGSRC_MDS_TCP", _eMdsMsgSource::MDS_MSGSRC_MDS_TCP);
    e.value("MDS_MSGSRC_MDS_UDP", _eMdsMsgSource::MDS_MSGSRC_MDS_UDP);
    e.value("MDS_MSGSRC_FILE_MKTDT", _eMdsMsgSource::MDS_MSGSRC_FILE_MKTDT);
    e.value("MDS_MSGSRC_SSE_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_BINARY);
    e.value("MDS_MSGSRC_SSE_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_STEP);
    e.value("__MAX_MDS_MSGSRC", _eMdsMsgSource::__MAX_MDS_MSGSRC);
    e.value("MDS_MSGSRC_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_MDGW_BINARY);
    e.value("MDS_MSGSRC_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_MDGW_STEP);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMsgSource", e);
}
void generate_enum_eMdsSecurityType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSecurityType> e(parent, "_eMdsSecurityType", pybind11::arithmetic());
    e.value("MDS_SECURITY_TYPE_STOCK", _eMdsSecurityType::MDS_SECURITY_TYPE_STOCK);
    e.value("MDS_SECURITY_TYPE_INDEX", _eMdsSecurityType::MDS_SECURITY_TYPE_INDEX);
    e.value("MDS_SECURITY_TYPE_OPTION", _eMdsSecurityType::MDS_SECURITY_TYPE_OPTION);
    e.value("__MAX_MDS_SECURITY_TYPE", _eMdsSecurityType::__MAX_MDS_SECURITY_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSecurityType", e);
}
void generate_enum_eMdsMdStreamType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMdStreamType> e(parent, "_eMdsMdStreamType", pybind11::arithmetic());
    e.value("MDS_MD_STREAM_TYPE_INDEX", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_INDEX);
    e.value("MDS_MD_STREAM_TYPE_STOCK", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_STOCK);
    e.value("MDS_MD_STREAM_TYPE_BOND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_BOND);
    e.value("MDS_MD_STREAM_TYPE_FUND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_FUND);
    e.value("MDS_MD_STREAM_TYPE_SZSE_STOCK", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SZSE_STOCK);
    e.value("MDS_MD_STREAM_TYPE_SZSE_REPO", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SZSE_REPO);
    e.value("MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS);
    e.value("MDS_MD_STREAM_TYPE_OPTION", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OPTION);
    e.value("MDS_MD_STREAM_TYPE_OTHERS", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OTHERS);
    e.value("__MAX_MDS_MD_STREAM_TYPE", _eMdsMdStreamType::__MAX_MDS_MD_STREAM_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdStreamType", e);
}
void generate_enum_eMdsMdLevel(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMdLevel> e(parent, "_eMdsMdLevel", pybind11::arithmetic());
    e.value("MDS_MD_LEVEL_0", _eMdsMdLevel::MDS_MD_LEVEL_0);
    e.value("MDS_MD_LEVEL_1", _eMdsMdLevel::MDS_MD_LEVEL_1);
    e.value("MDS_MD_LEVEL_2", _eMdsMdLevel::MDS_MD_LEVEL_2);
    e.value("__MAX_MDS_MD_LEVEL", _eMdsMdLevel::__MAX_MDS_MD_LEVEL);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdLevel", e);
}
void generate_enum_eMdsL2PriceLevelOperator(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2PriceLevelOperator> e(parent, "_eMdsL2PriceLevelOperator", pybind11::arithmetic());
    e.value("MDS_L2_PX_OPERATOR_ADD", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_ADD);
    e.value("MDS_L2_PX_OPERATOR_UPDATE", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_UPDATE);
    e.value("MDS_L2_PX_OPERATOR_DELETE", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_DELETE);
    e.value("__MAX_MDS_L2_PX_OPERATOR", _eMdsL2PriceLevelOperator::__MAX_MDS_L2_PX_OPERATOR);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2PriceLevelOperator", e);
}
void generate_enum_eMdsL2VirtualAuctionSide(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2VirtualAuctionSide> e(parent, "_eMdsL2VirtualAuctionSide", pybind11::arithmetic());
    e.value("MDS_L2_VIRTUAL_AUCTION_SIDE_NONE", _eMdsL2VirtualAuctionSide::MDS_L2_VIRTUAL_AUCTION_SIDE_NONE);
    e.value("MDS_L2_VIRTUAL_AUCTION_SIDE_BID", _eMdsL2VirtualAuctionSide::MDS_L2_VIRTUAL_AUCTION_SIDE_BID);
    e.value("MDS_L2_VIRTUAL_AUCTION_SIDE_OFFER", _eMdsL2VirtualAuctionSide::MDS_L2_VIRTUAL_AUCTION_SIDE_OFFER);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2VirtualAuctionSide", e);
}
void generate_enum_eMdsL2TradeExecType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2TradeExecType> e(parent, "_eMdsL2TradeExecType", pybind11::arithmetic());
    e.value("MDS_L2_TRADE_EXECTYPE_CANCELED", _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_CANCELED);
    e.value("MDS_L2_TRADE_EXECTYPE_TRADE", _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_TRADE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2TradeExecType", e);
}
void generate_enum_eMdsL2TradeBSFlag(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2TradeBSFlag> e(parent, "_eMdsL2TradeBSFlag", pybind11::arithmetic());
    e.value("MDS_L2_TRADE_BSFLAG_BUY", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_BUY);
    e.value("MDS_L2_TRADE_BSFLAG_SELL", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_SELL);
    e.value("MDS_L2_TRADE_BSFLAG_UNKNOWN", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_UNKNOWN);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2TradeBSFlag", e);
}
void generate_enum_eMdsL2OrderSideT(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2OrderSideT> e(parent, "_eMdsL2OrderSideT", pybind11::arithmetic());
    e.value("MDS_L2_ORDER_SIDE_BUY", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BUY);
    e.value("MDS_L2_ORDER_SIDE_SELL", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_SELL);
    e.value("MDS_L2_ORDER_SIDE_BORROW", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BORROW);
    e.value("MDS_L2_ORDER_SIDE_LEND", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_LEND);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2OrderSideT", e);
}
void generate_enum_eMdsL2OrderType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2OrderType> e(parent, "_eMdsL2OrderType", pybind11::arithmetic());
    e.value("MDS_L2_ORDER_TYPE_MKT", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_MKT);
    e.value("MDS_L2_ORDER_TYPE_LMT", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_LMT);
    e.value("MDS_L2_ORDER_TYPE_SAMEPARTY_BEST", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_SAMEPARTY_BEST);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2OrderType", e);
}
void generate_enum_eMdsClientType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsClientType> e(parent, "_eMdsClientType", pybind11::arithmetic());
    e.value("MDS_CLIENT_TYPE_UNDEFINED", _eMdsClientType::MDS_CLIENT_TYPE_UNDEFINED);
    e.value("MDS_CLIENT_TYPE_INVESTOR", _eMdsClientType::MDS_CLIENT_TYPE_INVESTOR);
    e.value("MDS_CLIENT_TYPE_VIRTUAL", _eMdsClientType::MDS_CLIENT_TYPE_VIRTUAL);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsClientType", e);
}
void generate_enum_eMdsClientStatus(pybind11::object & parent)
{
    pybind11::enum_<_eMdsClientStatus> e(parent, "_eMdsClientStatus", pybind11::arithmetic());
    e.value("MDS_CLIENT_STATUS_UNACTIVATED", _eMdsClientStatus::MDS_CLIENT_STATUS_UNACTIVATED);
    e.value("MDS_CLIENT_STATUS_ACTIVATED", _eMdsClientStatus::MDS_CLIENT_STATUS_ACTIVATED);
    e.value("MDS_CLIENT_STATUS_PAUSE", _eMdsClientStatus::MDS_CLIENT_STATUS_PAUSE);
    e.value("MDS_CLIENT_STATUS_SUSPENDED", _eMdsClientStatus::MDS_CLIENT_STATUS_SUSPENDED);
    e.value("MDS_CLIENT_STATUS_CANCELLED", _eMdsClientStatus::MDS_CLIENT_STATUS_CANCELLED);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsClientStatus", e);
}
void generate_enum_eMdsMsgType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMsgType> e(parent, "_eMdsMsgType", pybind11::arithmetic());
    e.value("MDS_MSGTYPE_HEARTBEAT", _eMdsMsgType::MDS_MSGTYPE_HEARTBEAT);
    e.value("MDS_MSGTYPE_TEST_REQUEST", _eMdsMsgType::MDS_MSGTYPE_TEST_REQUEST);
    e.value("MDS_MSGTYPE_LOGON", _eMdsMsgType::MDS_MSGTYPE_LOGON);
    e.value("MDS_MSGTYPE_LOGOUT", _eMdsMsgType::MDS_MSGTYPE_LOGOUT);
    e.value("MDS_MSGTYPE_MARKET_DATA_REQUEST", _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_REQUEST);
    e.value("MDS_MSGTYPE_COMPRESSED_PACKETS", _eMdsMsgType::MDS_MSGTYPE_COMPRESSED_PACKETS);
    e.value("__MDS_MSGTYPE_SESSION_MAX", _eMdsMsgType::__MDS_MSGTYPE_SESSION_MAX);
    e.value("MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH);
    e.value("MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH);
    e.value("MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH);
    e.value("MDS_MSGTYPE_TRADING_SESSION_STATUS", _eMdsMsgType::MDS_MSGTYPE_TRADING_SESSION_STATUS);
    e.value("MDS_MSGTYPE_SECURITY_STATUS", _eMdsMsgType::MDS_MSGTYPE_SECURITY_STATUS);
    e.value("__MDS_MSGTYPE_L1_MAX", _eMdsMsgType::__MDS_MSGTYPE_L1_MAX);
    e.value("MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT);
    e.value("MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT);
    e.value("MDS_MSGTYPE_L2_TRADE", _eMdsMsgType::MDS_MSGTYPE_L2_TRADE);
    e.value("MDS_MSGTYPE_L2_ORDER", _eMdsMsgType::MDS_MSGTYPE_L2_ORDER);
    e.value("MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL);
    e.value("MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL", _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL);
    e.value("MDS_MSGTYPE_L2_MARKET_OVERVIEW", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_OVERVIEW);
    e.value("MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE", _eMdsMsgType::MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE);
    e.value("__MDS_MSGTYPE_L2_MAX", _eMdsMsgType::__MDS_MSGTYPE_L2_MAX);
    e.value("MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT);
    e.value("MDS_MSGTYPE_QRY_SECURITY_STATUS", _eMdsMsgType::MDS_MSGTYPE_QRY_SECURITY_STATUS);
    e.value("MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS", _eMdsMsgType::MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS);
    e.value("__MDS_MSGTYPE_QRY_MAX", _eMdsMsgType::__MDS_MSGTYPE_QRY_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMsgType", e);
}
void generate_enum_eMdsSubscribeMode(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribeMode> e(parent, "_eMdsSubscribeMode", pybind11::arithmetic());
    e.value("MDS_SUB_MODE_SET", _eMdsSubscribeMode::MDS_SUB_MODE_SET);
    e.value("MDS_SUB_MODE_APPEND", _eMdsSubscribeMode::MDS_SUB_MODE_APPEND);
    e.value("MDS_SUB_MODE_DELETE", _eMdsSubscribeMode::MDS_SUB_MODE_DELETE);
    e.value("__MAX_MDS_SUB_MODE", _eMdsSubscribeMode::__MAX_MDS_SUB_MODE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribeMode", e);
}
void generate_enum_eMdsMktSubscribeFlag(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMktSubscribeFlag> e(parent, "_eMdsMktSubscribeFlag", pybind11::arithmetic());
    e.value("MDS_MKT_SUB_FLAG_DEFAULT", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DEFAULT);
    e.value("MDS_MKT_SUB_FLAG_ALL", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_ALL);
    e.value("MDS_MKT_SUB_FLAG_DISABLE", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DISABLE);
    e.value("__MAX_MDS_MKT_SUB_FLAG", _eMdsMktSubscribeFlag::__MAX_MDS_MKT_SUB_FLAG);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMktSubscribeFlag", e);
}
void generate_enum_eMdsSubscribedTickType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribedTickType> e(parent, "_eMdsSubscribedTickType", pybind11::arithmetic());
    e.value("MDS_TICK_TYPE_LATEST_SIMPLIFIED", _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_SIMPLIFIED);
    e.value("MDS_TICK_TYPE_LATEST_TIMELY", _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_TIMELY);
    e.value("MDS_TICK_TYPE_ALL_INCREMENTS", _eMdsSubscribedTickType::MDS_TICK_TYPE_ALL_INCREMENTS);
    e.value("__MAX_MDS_TICK_TYPE", _eMdsSubscribedTickType::__MAX_MDS_TICK_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedTickType", e);
}
void generate_enum_eMdsSubscribedTickExpireType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribedTickExpireType> e(parent, "_eMdsSubscribedTickExpireType", pybind11::arithmetic());
    e.value("MDS_TICK_EXPIRE_TYPE_NONE", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_NONE);
    e.value("MDS_TICK_EXPIRE_TYPE_IMMEDIATE", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_IMMEDIATE);
    e.value("MDS_TICK_EXPIRE_TYPE_TIMELY", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMELY);
    e.value("MDS_TICK_EXPIRE_TYPE_TIMEOUT", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMEOUT);
    e.value("__MAX_MDS_TICK_EXPIRE_TYPE", _eMdsSubscribedTickExpireType::__MAX_MDS_TICK_EXPIRE_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedTickExpireType", e);
}
void generate_enum_eMdsSubscribeDataType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribeDataType> e(parent, "_eMdsSubscribeDataType", pybind11::arithmetic());
    e.value("MDS_SUB_DATA_TYPE_DEFAULT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_DEFAULT);
    e.value("MDS_SUB_DATA_TYPE_L1_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L1_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_L2_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_L2_BEST_ORDERS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_BEST_ORDERS);
    e.value("MDS_SUB_DATA_TYPE_L2_TRADE", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_TRADE);
    e.value("MDS_SUB_DATA_TYPE_L2_ORDER", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_ORDER);
    e.value("MDS_SUB_DATA_TYPE_L2_VIRTUAL_AUCTION_PRICE", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_VIRTUAL_AUCTION_PRICE);
    e.value("MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW);
    e.value("MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS);
    e.value("MDS_SUB_DATA_TYPE_SECURITY_STATUS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_SECURITY_STATUS);
    e.value("MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_NONE", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_NONE);
    e.value("MDS_SUB_DATA_TYPE_ALL", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_ALL);
    e.value("__MAX_MDS_SUB_DATA_TYPE", _eMdsSubscribeDataType::__MAX_MDS_SUB_DATA_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribeDataType", e);
}
void generate_enum_eMdsSubscribedChannelNo(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribedChannelNo> e(parent, "_eMdsSubscribedChannelNo", pybind11::arithmetic());
    e.value("MDS_CHANNEL_NO_DEFAULT", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_DEFAULT);
    e.value("MDS_CHANNEL_NO_ONE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ONE);
    e.value("MDS_CHANNEL_NO_TWO", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_TWO);
    e.value("MDS_CHANNEL_NO_THREE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_THREE);
    e.value("MDS_CHANNEL_NO_FOUR", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_FOUR);
    e.value("MDS_CHANNEL_NO_ALL", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ALL);
    e.value("MDS_CHANNEL_NO_NONE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_NONE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedChannelNo", e);
}
void generate_enum_eMdsApiChannelType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsApiChannelType> e(parent, "_eMdsApiChannelType", pybind11::arithmetic());
    e.value("MDSAPI_CHANNEL_TYPE_TCP", _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_TCP);
    e.value("MDSAPI_CHANNEL_TYPE_UDP", _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_UDP);
    e.value("MDSAPI_CHANNEL_TYPE_QUERY", _eMdsApiChannelType::MDSAPI_CHANNEL_TYPE_QUERY);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsApiChannelType", e);
}
void generate_caster_(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
    autocxxpy::caster::try_generate<_spk_struct_timespec>(c, "to_spk_struct_timespec)");
    autocxxpy::caster::try_generate<_spk_struct_timezone>(c, "to_spk_struct_timezone)");
    autocxxpy::caster::try_generate<_spk_struct_iovec>(c, "to_spk_struct_iovec)");
    autocxxpy::caster::try_generate<_spk_struct_timeval32>(c, "to_spk_struct_timeval32)");
    autocxxpy::caster::try_generate<_spk_struct_timeval64>(c, "to_spk_struct_timeval64)");
    autocxxpy::caster::try_generate<_OesOrdReq>(c, "to_OesOrdReq)");
    autocxxpy::caster::try_generate<_OesOrdCancelReq>(c, "to_OesOrdCancelReq)");
    autocxxpy::caster::try_generate<_OesOrdReject>(c, "to_OesOrdReject)");
    autocxxpy::caster::try_generate<_OesOrdCnfm>(c, "to_OesOrdCnfm)");
    autocxxpy::caster::try_generate<_OesTrdBaseInfo>(c, "to_OesTrdBaseInfo)");
    autocxxpy::caster::try_generate<_OesTrdCnfm>(c, "to_OesTrdCnfm)");
    autocxxpy::caster::try_generate<_OesLotWinningBaseInfo>(c, "to_OesLotWinningBaseInfo)");
    autocxxpy::caster::try_generate<_OesFundTrsfBaseInfo>(c, "to_OesFundTrsfBaseInfo)");
    autocxxpy::caster::try_generate<_OesFundTrsfReq>(c, "to_OesFundTrsfReq)");
    autocxxpy::caster::try_generate<_OesFundTrsfReject>(c, "to_OesFundTrsfReject)");
    autocxxpy::caster::try_generate<_OesFundTrsfReport>(c, "to_OesFundTrsfReport)");
    autocxxpy::caster::try_generate<_OesIssueBaseInfo>(c, "to_OesIssueBaseInfo)");
    autocxxpy::caster::try_generate<_OesPriceLimit>(c, "to_OesPriceLimit)");
    autocxxpy::caster::try_generate<_OesStockBaseInfo>(c, "to_OesStockBaseInfo)");
    autocxxpy::caster::try_generate<_OesEtfBaseInfo>(c, "to_OesEtfBaseInfo)");
    autocxxpy::caster::try_generate<_OesEtfComponentBaseInfo>(c, "to_OesEtfComponentBaseInfo)");
    autocxxpy::caster::try_generate<_OesOptionBaseInfo>(c, "to_OesOptionBaseInfo)");
    autocxxpy::caster::try_generate<_OesCashAssetBaseInfo>(c, "to_OesCashAssetBaseInfo)");
    autocxxpy::caster::try_generate<_OesCustBaseInfo>(c, "to_OesCustBaseInfo)");
    autocxxpy::caster::try_generate<_OesInvAcctBaseInfo>(c, "to_OesInvAcctBaseInfo)");
    autocxxpy::caster::try_generate<_OesStkHoldingBaseInfo>(c, "to_OesStkHoldingBaseInfo)");
    autocxxpy::caster::try_generate<_OesOptHoldingBaseInfo>(c, "to_OesOptHoldingBaseInfo)");
    autocxxpy::caster::try_generate<_OesMarketStateInfo>(c, "to_OesMarketStateInfo)");
    autocxxpy::caster::try_generate<_OesTradingPermissionEntry>(c, "to_OesTradingPermissionEntry)");
    autocxxpy::caster::try_generate<_OesInputSourceInfo>(c, "to_OesInputSourceInfo)");
    autocxxpy::caster::try_generate<_SMsgHead>(c, "to_SMsgHead)");
    autocxxpy::caster::try_generate<_OesQryCursor>(c, "to_OesQryCursor)");
    autocxxpy::caster::try_generate<_OesQryReqHead>(c, "to_OesQryReqHead)");
    autocxxpy::caster::try_generate<_OesQryRspHead>(c, "to_OesQryRspHead)");
    autocxxpy::caster::try_generate<_OesQryOrdFilter>(c, "to_OesQryOrdFilter)");
    autocxxpy::caster::try_generate<_OesQryOrdReq>(c, "to_OesQryOrdReq)");
    autocxxpy::caster::try_generate<_OesQryOrdRsp>(c, "to_OesQryOrdRsp)");
    autocxxpy::caster::try_generate<_OesQryTrdFilter>(c, "to_OesQryTrdFilter)");
    autocxxpy::caster::try_generate<_OesQryTrdReq>(c, "to_OesQryTrdReq)");
    autocxxpy::caster::try_generate<_OesQryTrdRsp>(c, "to_OesQryTrdRsp)");
    autocxxpy::caster::try_generate<_OesQryCashAssetFilter>(c, "to_OesQryCashAssetFilter)");
    autocxxpy::caster::try_generate<_OesCashAssetItem>(c, "to_OesCashAssetItem)");
    autocxxpy::caster::try_generate<_OesQryCashAssetReq>(c, "to_OesQryCashAssetReq)");
    autocxxpy::caster::try_generate<_OesQryCashAssetRsp>(c, "to_OesQryCashAssetRsp)");
    autocxxpy::caster::try_generate<_OesCounterCashItem>(c, "to_OesCounterCashItem)");
    autocxxpy::caster::try_generate<_OesQryCounterCashReq>(c, "to_OesQryCounterCashReq)");
    autocxxpy::caster::try_generate<_OesQryCounterCashRsp>(c, "to_OesQryCounterCashRsp)");
    autocxxpy::caster::try_generate<_OesQryStkHoldingFilter>(c, "to_OesQryStkHoldingFilter)");
    autocxxpy::caster::try_generate<_OesStkHoldingItem>(c, "to_OesStkHoldingItem)");
    autocxxpy::caster::try_generate<_OesQryStkHoldingReq>(c, "to_OesQryStkHoldingReq)");
    autocxxpy::caster::try_generate<_OesQryStkHoldingRsp>(c, "to_OesQryStkHoldingRsp)");
    autocxxpy::caster::try_generate<_OesOptHoldingItem>(c, "to_OesOptHoldingItem)");
    autocxxpy::caster::try_generate<_OesQryOptHoldingReq>(c, "to_OesQryOptHoldingReq)");
    autocxxpy::caster::try_generate<_OesQryHoldRsp>(c, "to_OesQryHoldRsp)");
    autocxxpy::caster::try_generate<_OesQryCustFilter>(c, "to_OesQryCustFilter)");
    autocxxpy::caster::try_generate<_OesQryCustReq>(c, "to_OesQryCustReq)");
    autocxxpy::caster::try_generate<_OesQryCustRsp>(c, "to_OesQryCustRsp)");
    autocxxpy::caster::try_generate<_OesQryInvAcctFilter>(c, "to_OesQryInvAcctFilter)");
    autocxxpy::caster::try_generate<_OesInvAcctItem>(c, "to_OesInvAcctItem)");
    autocxxpy::caster::try_generate<_OesQryInvAcctReq>(c, "to_OesQryInvAcctReq)");
    autocxxpy::caster::try_generate<_OesQryInvAcctRsp>(c, "to_OesQryInvAcctRsp)");
    autocxxpy::caster::try_generate<_OesInvAcctOverview>(c, "to_OesInvAcctOverview)");
    autocxxpy::caster::try_generate<_OesCashAcctOverview>(c, "to_OesCashAcctOverview)");
    autocxxpy::caster::try_generate<_OesCustOverview>(c, "to_OesCustOverview)");
    autocxxpy::caster::try_generate<_OesClientOverview>(c, "to_OesClientOverview)");
    autocxxpy::caster::try_generate<_OesQryCommissionRateFilter>(c, "to_OesQryCommissionRateFilter)");
    autocxxpy::caster::try_generate<_OesCommissionRateItem>(c, "to_OesCommissionRateItem)");
    autocxxpy::caster::try_generate<_OesQryCommissionRateReq>(c, "to_OesQryCommissionRateReq)");
    autocxxpy::caster::try_generate<_OesQryCommissionRateRsp>(c, "to_OesQryCommissionRateRsp)");
    autocxxpy::caster::try_generate<_OesQryFundTransferSerialFilter>(c, "to_OesQryFundTransferSerialFilter)");
    autocxxpy::caster::try_generate<_OesQryFundTransferSerialReq>(c, "to_OesQryFundTransferSerialReq)");
    autocxxpy::caster::try_generate<_OesQryFundTransferSerialRsp>(c, "to_OesQryFundTransferSerialRsp)");
    autocxxpy::caster::try_generate<_OesQryLotWinningFilter>(c, "to_OesQryLotWinningFilter)");
    autocxxpy::caster::try_generate<_OesQryLotWinningReq>(c, "to_OesQryLotWinningReq)");
    autocxxpy::caster::try_generate<_OesQryLotWinningRsp>(c, "to_OesQryLotWinningRsp)");
    autocxxpy::caster::try_generate<_OesQryIssueFilter>(c, "to_OesQryIssueFilter)");
    autocxxpy::caster::try_generate<_OesQryIssueReq>(c, "to_OesQryIssueReq)");
    autocxxpy::caster::try_generate<_OesQryIssueRsp>(c, "to_OesQryIssueRsp)");
    autocxxpy::caster::try_generate<_OesQryStockFilter>(c, "to_OesQryStockFilter)");
    autocxxpy::caster::try_generate<_OesQryStockReq>(c, "to_OesQryStockReq)");
    autocxxpy::caster::try_generate<_OesQryStockRsp>(c, "to_OesQryStockRsp)");
    autocxxpy::caster::try_generate<_OesQryEtfFilter>(c, "to_OesQryEtfFilter)");
    autocxxpy::caster::try_generate<_OesQryEtfReq>(c, "to_OesQryEtfReq)");
    autocxxpy::caster::try_generate<_OesQryEtfRsp>(c, "to_OesQryEtfRsp)");
    autocxxpy::caster::try_generate<_OesQryEtfComponentFilter>(c, "to_OesQryEtfComponentFilter)");
    autocxxpy::caster::try_generate<_OesEtfComponentItem>(c, "to_OesEtfComponentItem)");
    autocxxpy::caster::try_generate<_OesQryEtfComponentReq>(c, "to_OesQryEtfComponentReq)");
    autocxxpy::caster::try_generate<_OesQryEtfComponentRsp>(c, "to_OesQryEtfComponentRsp)");
    autocxxpy::caster::try_generate<_OesQryOptionFilter>(c, "to_OesQryOptionFilter)");
    autocxxpy::caster::try_generate<_OesQryOptionReq>(c, "to_OesQryOptionReq)");
    autocxxpy::caster::try_generate<_OesQryOptionRsp>(c, "to_OesQryOptionRsp)");
    autocxxpy::caster::try_generate<_OesQryTradingDayRsp>(c, "to_OesQryTradingDayRsp)");
    autocxxpy::caster::try_generate<_OesQryMarketStateFilter>(c, "to_OesQryMarketStateFilter)");
    autocxxpy::caster::try_generate<_OesQryMarketStateReq>(c, "to_OesQryMarketStateReq)");
    autocxxpy::caster::try_generate<_OesQryMarketStateRsp>(c, "to_OesQryMarketStateRsp)");
    autocxxpy::caster::try_generate<_OesQryReqMsg>(c, "to_OesQryReqMsg)");
    autocxxpy::caster::try_generate<_OesQryRspMsg>(c, "to_OesQryRspMsg)");
    autocxxpy::caster::try_generate<_OesLogonReq>(c, "to_OesLogonReq)");
    autocxxpy::caster::try_generate<_OesLogonRsp>(c, "to_OesLogonRsp)");
    autocxxpy::caster::try_generate<_OesReportSynchronizationReq>(c, "to_OesReportSynchronizationReq)");
    autocxxpy::caster::try_generate<_OesReportSynchronizationRsp>(c, "to_OesReportSynchronizationRsp)");
    autocxxpy::caster::try_generate<_OesTestRequestReq>(c, "to_OesTestRequestReq)");
    autocxxpy::caster::try_generate<_OesTestRequestRsp>(c, "to_OesTestRequestRsp)");
    autocxxpy::caster::try_generate<_OesChangePasswordReq>(c, "to_OesChangePasswordReq)");
    autocxxpy::caster::try_generate<_OesChangePasswordRsp>(c, "to_OesChangePasswordRsp)");
    autocxxpy::caster::try_generate<_OesBatchOrdersHead>(c, "to_OesBatchOrdersHead)");
    autocxxpy::caster::try_generate<_OesBatchOrdersReq>(c, "to_OesBatchOrdersReq)");
    autocxxpy::caster::try_generate<_OesRptMsgHead>(c, "to_OesRptMsgHead)");
    autocxxpy::caster::try_generate<_OesRptMsgBody>(c, "to_OesRptMsgBody)");
    autocxxpy::caster::try_generate<_OesRptMsg>(c, "to_OesRptMsg)");
    autocxxpy::caster::try_generate<_OesReqMsgBody>(c, "to_OesReqMsgBody)");
    autocxxpy::caster::try_generate<_OesRspMsgBody>(c, "to_OesRspMsgBody)");
    autocxxpy::caster::try_generate<_SErrMsg>(c, "to_SErrMsg)");
    autocxxpy::caster::try_generate<_SDataBuffer>(c, "to_SDataBuffer)");
    autocxxpy::caster::try_generate<_SDataBufferVar>(c, "to_SDataBufferVar)");
    autocxxpy::caster::try_generate<_SSocketUriInfo>(c, "to_SSocketUriInfo)");
    autocxxpy::caster::try_generate<_SSocketIpPortInfo>(c, "to_SSocketIpPortInfo)");
    autocxxpy::caster::try_generate<_SSocketChannelInfo>(c, "to_SSocketChannelInfo)");
    autocxxpy::caster::try_generate<_SSocketOptionConfig>(c, "to_SSocketOptionConfig)");
    autocxxpy::caster::try_generate<_SGeneralClientChannel>(c, "to_SGeneralClientChannel)");
    autocxxpy::caster::try_generate<_SGeneralClientChannelGroup>(c, "to_SGeneralClientChannelGroup)");
    autocxxpy::caster::try_generate<_SGeneralClientAddrInfo>(c, "to_SGeneralClientAddrInfo)");
    autocxxpy::caster::try_generate<_SGeneralClientRemoteCfg>(c, "to_SGeneralClientRemoteCfg)");
    autocxxpy::caster::try_generate<_OesApiSubscribeInfo>(c, "to_OesApiSubscribeInfo)");
    autocxxpy::caster::try_generate<_OesApiClientCfg>(c, "to_OesApiClientCfg)");
    autocxxpy::caster::try_generate<_OesApiClientEnv>(c, "to_OesApiClientEnv)");
    autocxxpy::caster::try_generate<_MdsTradingSessionStatusMsg>(c, "to_MdsTradingSessionStatusMsg)");
    autocxxpy::caster::try_generate<_MdsSecurityStatusMsg>(c, "to_MdsSecurityStatusMsg)");
    autocxxpy::caster::try_generate<_MdsPriceLevelEntry>(c, "to_MdsPriceLevelEntry)");
    autocxxpy::caster::try_generate<_MdsMktDataSnapshotHead>(c, "to_MdsMktDataSnapshotHead)");
    autocxxpy::caster::try_generate<_MdsIndexSnapshotBody>(c, "to_MdsIndexSnapshotBody)");
    autocxxpy::caster::try_generate<_MdsStockSnapshotBody>(c, "to_MdsStockSnapshotBody)");
    autocxxpy::caster::try_generate<_MdsL1SnapshotBody>(c, "to_MdsL1SnapshotBody)");
    autocxxpy::caster::try_generate<_MdsL2StockSnapshotBody>(c, "to_MdsL2StockSnapshotBody)");
    autocxxpy::caster::try_generate<_MdsL2StockSnapshotIncremental>(c, "to_MdsL2StockSnapshotIncremental)");
    autocxxpy::caster::try_generate<_MdsL2BestOrdersSnapshotBody>(c, "to_MdsL2BestOrdersSnapshotBody)");
    autocxxpy::caster::try_generate<_MdsL2BestOrdersSnapshotIncremental>(c, "to_MdsL2BestOrdersSnapshotIncremental)");
    autocxxpy::caster::try_generate<_MdsL2VirtualAuctionPrice>(c, "to_MdsL2VirtualAuctionPrice)");
    autocxxpy::caster::try_generate<_MdsL2MarketOverview>(c, "to_MdsL2MarketOverview)");
    autocxxpy::caster::try_generate<_MdsL2SnapshotBody>(c, "to_MdsL2SnapshotBody)");
    autocxxpy::caster::try_generate<_MdsMktDataSnapshot>(c, "to_MdsMktDataSnapshot)");
    autocxxpy::caster::try_generate<_MdsL2Trade>(c, "to_MdsL2Trade)");
    autocxxpy::caster::try_generate<_MdsL2Order>(c, "to_MdsL2Order)");
    autocxxpy::caster::try_generate<_MdsL2TickLost>(c, "to_MdsL2TickLost)");
    autocxxpy::caster::try_generate<_MdsQryMktDataSnapshotReq>(c, "to_MdsQryMktDataSnapshotReq)");
    autocxxpy::caster::try_generate<_MdsQryTrdSessionStatusReq>(c, "to_MdsQryTrdSessionStatusReq)");
    autocxxpy::caster::try_generate<_MdsLogonReq>(c, "to_MdsLogonReq)");
    autocxxpy::caster::try_generate<_MdsLogonRsp>(c, "to_MdsLogonRsp)");
    autocxxpy::caster::try_generate<_MdsMktDataRequestEntry>(c, "to_MdsMktDataRequestEntry)");
    autocxxpy::caster::try_generate<_MdsMktDataRequestReq>(c, "to_MdsMktDataRequestReq)");
    autocxxpy::caster::try_generate<_MdsMktDataRequestReqBuf>(c, "to_MdsMktDataRequestReqBuf)");
    autocxxpy::caster::try_generate<_MdsMktDataRequestRsp>(c, "to_MdsMktDataRequestRsp)");
    autocxxpy::caster::try_generate<_MdsTestRequestReq>(c, "to_MdsTestRequestReq)");
    autocxxpy::caster::try_generate<_MdsTestRequestRsp>(c, "to_MdsTestRequestRsp)");
    autocxxpy::caster::try_generate<_MdsMktReqMsgBody>(c, "to_MdsMktReqMsgBody)");
    autocxxpy::caster::try_generate<_MdsMktRspMsgBody>(c, "to_MdsMktRspMsgBody)");
    autocxxpy::caster::try_generate<_MdsUdpPktHead>(c, "to_MdsUdpPktHead)");
    autocxxpy::caster::try_generate<_MdsApiClientCfg>(c, "to_MdsApiClientCfg)");
    autocxxpy::caster::try_generate<_MdsApiClientEnv>(c, "to_MdsApiClientEnv)");
    autocxxpy::caster::try_generate<int8>(c, "toint8)");
    autocxxpy::caster::try_generate<uint8>(c, "touint8)");
    autocxxpy::caster::try_generate<int16>(c, "toint16)");
    autocxxpy::caster::try_generate<uint16>(c, "touint16)");
    autocxxpy::caster::try_generate<int32>(c, "toint32)");
    autocxxpy::caster::try_generate<uint32>(c, "touint32)");
    autocxxpy::caster::try_generate<int64>(c, "toint64)");
    autocxxpy::caster::try_generate<uint64>(c, "touint64)");
    autocxxpy::caster::try_generate<float32>(c, "tofloat32)");
    autocxxpy::caster::try_generate<float64>(c, "tofloat64)");
    autocxxpy::caster::try_generate<float128>(c, "tofloat128)");
    autocxxpy::caster::try_generate<STimeval32T>(c, "toSTimeval32T)");
    autocxxpy::caster::try_generate<STimeval64T>(c, "toSTimeval64T)");
    autocxxpy::caster::try_generate<eOesExchangeIdT>(c, "toeOesExchangeIdT)");
    autocxxpy::caster::try_generate<eOesMarketIdT>(c, "toeOesMarketIdT)");
    autocxxpy::caster::try_generate<eOesPlatformIdT>(c, "toeOesPlatformIdT)");
    autocxxpy::caster::try_generate<eOesMarketStatusT>(c, "toeOesMarketStatusT)");
    autocxxpy::caster::try_generate<eOesTrdSessTypeT>(c, "toeOesTrdSessTypeT)");
    autocxxpy::caster::try_generate<eOesSecurityTypeT>(c, "toeOesSecurityTypeT)");
    autocxxpy::caster::try_generate<eOesSubSecurityTypeT>(c, "toeOesSubSecurityTypeT)");
    autocxxpy::caster::try_generate<eOesSecurityLevelT>(c, "toeOesSecurityLevelT)");
    autocxxpy::caster::try_generate<eOesSecurityRiskLevelT>(c, "toeOesSecurityRiskLevelT)");
    autocxxpy::caster::try_generate<eOesSecuritySuspFlagT>(c, "toeOesSecuritySuspFlagT)");
    autocxxpy::caster::try_generate<eOesOrdStatusT>(c, "toeOesOrdStatusT)");
    autocxxpy::caster::try_generate<eOesOrdTypeT>(c, "toeOesOrdTypeT)");
    autocxxpy::caster::try_generate<eOesOrdTypeShT>(c, "toeOesOrdTypeShT)");
    autocxxpy::caster::try_generate<eOesOrdTypeSzT>(c, "toeOesOrdTypeSzT)");
    autocxxpy::caster::try_generate<eOesBuySellTypeT>(c, "toeOesBuySellTypeT)");
    autocxxpy::caster::try_generate<eOesOrdDirT>(c, "toeOesOrdDirT)");
    autocxxpy::caster::try_generate<eOesEtfTrdCnfmTypeT>(c, "toeOesEtfTrdCnfmTypeT)");
    autocxxpy::caster::try_generate<eOesEtfSubFlagT>(c, "toeOesEtfSubFlagT)");
    autocxxpy::caster::try_generate<eOesLotTypeT>(c, "toeOesLotTypeT)");
    autocxxpy::caster::try_generate<eOesLotRejReasonT>(c, "toeOesLotRejReasonT)");
    autocxxpy::caster::try_generate<eOesExecTypeT>(c, "toeOesExecTypeT)");
    autocxxpy::caster::try_generate<eOesCurrTypeT>(c, "toeOesCurrTypeT)");
    autocxxpy::caster::try_generate<eOesFeeTypeT>(c, "toeOesFeeTypeT)");
    autocxxpy::caster::try_generate<eOesCalcFeeModeT>(c, "toeOesCalcFeeModeT)");
    autocxxpy::caster::try_generate<eOesFundTrsfDirectT>(c, "toeOesFundTrsfDirectT)");
    autocxxpy::caster::try_generate<eOesFundTrsfTypeT>(c, "toeOesFundTrsfTypeT)");
    autocxxpy::caster::try_generate<eOesFundTrsfStatusT>(c, "toeOesFundTrsfStatusT)");
    autocxxpy::caster::try_generate<eOesAcctTypeT>(c, "toeOesAcctTypeT)");
    autocxxpy::caster::try_generate<eOesCashTypeT>(c, "toeOesCashTypeT)");
    autocxxpy::caster::try_generate<eOesAcctStatusT>(c, "toeOesAcctStatusT)");
    autocxxpy::caster::try_generate<eOesTradingPermissionT>(c, "toeOesTradingPermissionT)");
    autocxxpy::caster::try_generate<eOesTradingLimitT>(c, "toeOesTradingLimitT)");
    autocxxpy::caster::try_generate<eOesQualificationClassT>(c, "toeOesQualificationClassT)");
    autocxxpy::caster::try_generate<eOesInvestorClassT>(c, "toeOesInvestorClassT)");
    autocxxpy::caster::try_generate<eOesOwnerTypeT>(c, "toeOesOwnerTypeT)");
    autocxxpy::caster::try_generate<eOesClientTypeT>(c, "toeOesClientTypeT)");
    autocxxpy::caster::try_generate<eOesClientStatusT>(c, "toeOesClientStatusT)");
    autocxxpy::caster::try_generate<eOesOptContractTypeT>(c, "toeOesOptContractTypeT)");
    autocxxpy::caster::try_generate<eOesOptInvLevelT>(c, "toeOesOptInvLevelT)");
    autocxxpy::caster::try_generate<eOpenFlagTypeT>(c, "toeOpenFlagTypeT)");
    autocxxpy::caster::try_generate<eOesOptionOpenFlagT>(c, "toeOesOptionOpenFlagT)");
    autocxxpy::caster::try_generate<eOesPositionEffT>(c, "toeOesPositionEffT)");
    autocxxpy::caster::try_generate<eOesOptionTypeT>(c, "toeOesOptionTypeT)");
    autocxxpy::caster::try_generate<OesOrdReqT>(c, "toOesOrdReqT)");
    autocxxpy::caster::try_generate<OesOrdCancelReqT>(c, "toOesOrdCancelReqT)");
    autocxxpy::caster::try_generate<OesOrdRejectT>(c, "toOesOrdRejectT)");
    autocxxpy::caster::try_generate<OesOrdCnfmT>(c, "toOesOrdCnfmT)");
    autocxxpy::caster::try_generate<OesTrdBaseInfoT>(c, "toOesTrdBaseInfoT)");
    autocxxpy::caster::try_generate<OesTrdCnfmT>(c, "toOesTrdCnfmT)");
    autocxxpy::caster::try_generate<OesLotWinningBaseInfoT>(c, "toOesLotWinningBaseInfoT)");
    autocxxpy::caster::try_generate<OesFundTrsfBaseInfoT>(c, "toOesFundTrsfBaseInfoT)");
    autocxxpy::caster::try_generate<OesFundTrsfReqT>(c, "toOesFundTrsfReqT)");
    autocxxpy::caster::try_generate<OesFundTrsfRejectT>(c, "toOesFundTrsfRejectT)");
    autocxxpy::caster::try_generate<OesFundTrsfReportT>(c, "toOesFundTrsfReportT)");
    autocxxpy::caster::try_generate<OesIssueBaseInfoT>(c, "toOesIssueBaseInfoT)");
    autocxxpy::caster::try_generate<OesPriceLimitT>(c, "toOesPriceLimitT)");
    autocxxpy::caster::try_generate<OesStockBaseInfoT>(c, "toOesStockBaseInfoT)");
    autocxxpy::caster::try_generate<OesEtfBaseInfoT>(c, "toOesEtfBaseInfoT)");
    autocxxpy::caster::try_generate<OesEtfComponentBaseInfoT>(c, "toOesEtfComponentBaseInfoT)");
    autocxxpy::caster::try_generate<OesOptionBaseInfoT>(c, "toOesOptionBaseInfoT)");
    autocxxpy::caster::try_generate<OesCashAssetBaseInfoT>(c, "toOesCashAssetBaseInfoT)");
    autocxxpy::caster::try_generate<OesCustBaseInfoT>(c, "toOesCustBaseInfoT)");
    autocxxpy::caster::try_generate<OesInvAcctBaseInfoT>(c, "toOesInvAcctBaseInfoT)");
    autocxxpy::caster::try_generate<OesStkHoldingBaseInfoT>(c, "toOesStkHoldingBaseInfoT)");
    autocxxpy::caster::try_generate<OesOptHoldingBaseInfoT>(c, "toOesOptHoldingBaseInfoT)");
    autocxxpy::caster::try_generate<OesMarketStateInfoT>(c, "toOesMarketStateInfoT)");
    autocxxpy::caster::try_generate<OesTradingPermissionEntryT>(c, "toOesTradingPermissionEntryT)");
    autocxxpy::caster::try_generate<OesInputSourceInfoT>(c, "toOesInputSourceInfoT)");
    autocxxpy::caster::try_generate<eSMsgProtocolTypeT>(c, "toeSMsgProtocolTypeT)");
    autocxxpy::caster::try_generate<eSMsgFlagT>(c, "toeSMsgFlagT)");
    autocxxpy::caster::try_generate<SMsgHeadT>(c, "toSMsgHeadT)");
    autocxxpy::caster::try_generate<OesQryCursorT>(c, "toOesQryCursorT)");
    autocxxpy::caster::try_generate<OesQryReqHeadT>(c, "toOesQryReqHeadT)");
    autocxxpy::caster::try_generate<OesQryRspHeadT>(c, "toOesQryRspHeadT)");
    autocxxpy::caster::try_generate<OesQryOrdFilterT>(c, "toOesQryOrdFilterT)");
    autocxxpy::caster::try_generate<OesOrdItemT>(c, "toOesOrdItemT)");
    autocxxpy::caster::try_generate<OesQryOrdReqT>(c, "toOesQryOrdReqT)");
    autocxxpy::caster::try_generate<OesQryOrdRspT>(c, "toOesQryOrdRspT)");
    autocxxpy::caster::try_generate<OesQryTrdFilterT>(c, "toOesQryTrdFilterT)");
    autocxxpy::caster::try_generate<OesTrdItemT>(c, "toOesTrdItemT)");
    autocxxpy::caster::try_generate<OesQryTrdReqT>(c, "toOesQryTrdReqT)");
    autocxxpy::caster::try_generate<OesQryTrdRspT>(c, "toOesQryTrdRspT)");
    autocxxpy::caster::try_generate<OesQryCashAssetFilterT>(c, "toOesQryCashAssetFilterT)");
    autocxxpy::caster::try_generate<OesCashAssetItemT>(c, "toOesCashAssetItemT)");
    autocxxpy::caster::try_generate<OesQryCashAssetReqT>(c, "toOesQryCashAssetReqT)");
    autocxxpy::caster::try_generate<OesQryCashAssetRspT>(c, "toOesQryCashAssetRspT)");
    autocxxpy::caster::try_generate<OesCounterCashItemT>(c, "toOesCounterCashItemT)");
    autocxxpy::caster::try_generate<OesQryCounterCashReqT>(c, "toOesQryCounterCashReqT)");
    autocxxpy::caster::try_generate<OesQryCounterCashRspT>(c, "toOesQryCounterCashRspT)");
    autocxxpy::caster::try_generate<OesQryStkHoldingFilterT>(c, "toOesQryStkHoldingFilterT)");
    autocxxpy::caster::try_generate<OesStkHoldingItemT>(c, "toOesStkHoldingItemT)");
    autocxxpy::caster::try_generate<OesQryStkHoldingReqT>(c, "toOesQryStkHoldingReqT)");
    autocxxpy::caster::try_generate<OesQryStkHoldingRspT>(c, "toOesQryStkHoldingRspT)");
    autocxxpy::caster::try_generate<OesQryOptHoldingFilterT>(c, "toOesQryOptHoldingFilterT)");
    autocxxpy::caster::try_generate<OesOptHoldingItemT>(c, "toOesOptHoldingItemT)");
    autocxxpy::caster::try_generate<OesQryOptHoldingReqT>(c, "toOesQryOptHoldingReqT)");
    autocxxpy::caster::try_generate<OesQryOptHoldingRspT>(c, "toOesQryOptHoldingRspT)");
    autocxxpy::caster::try_generate<OesQryCustFilterT>(c, "toOesQryCustFilterT)");
    autocxxpy::caster::try_generate<OesCustItemT>(c, "toOesCustItemT)");
    autocxxpy::caster::try_generate<OesQryCustReqT>(c, "toOesQryCustReqT)");
    autocxxpy::caster::try_generate<OesQryCustRspT>(c, "toOesQryCustRspT)");
    autocxxpy::caster::try_generate<OesQryInvAcctFilterT>(c, "toOesQryInvAcctFilterT)");
    autocxxpy::caster::try_generate<OesInvAcctItemT>(c, "toOesInvAcctItemT)");
    autocxxpy::caster::try_generate<OesQryInvAcctReqT>(c, "toOesQryInvAcctReqT)");
    autocxxpy::caster::try_generate<OesQryInvAcctRspT>(c, "toOesQryInvAcctRspT)");
    autocxxpy::caster::try_generate<OesInvAcctOverviewT>(c, "toOesInvAcctOverviewT)");
    autocxxpy::caster::try_generate<OesCashAcctOverviewT>(c, "toOesCashAcctOverviewT)");
    autocxxpy::caster::try_generate<OesCustOverviewT>(c, "toOesCustOverviewT)");
    autocxxpy::caster::try_generate<OesClientOverviewT>(c, "toOesClientOverviewT)");
    autocxxpy::caster::try_generate<OesQryCommissionRateFilterT>(c, "toOesQryCommissionRateFilterT)");
    autocxxpy::caster::try_generate<OesCommissionRateItemT>(c, "toOesCommissionRateItemT)");
    autocxxpy::caster::try_generate<OesQryCommissionRateReqT>(c, "toOesQryCommissionRateReqT)");
    autocxxpy::caster::try_generate<OesQryCommissionRateRspT>(c, "toOesQryCommissionRateRspT)");
    autocxxpy::caster::try_generate<OesQryFundTransferSerialFilterT>(c, "toOesQryFundTransferSerialFilterT)");
    autocxxpy::caster::try_generate<OesFundTransferSerialItemT>(c, "toOesFundTransferSerialItemT)");
    autocxxpy::caster::try_generate<OesQryFundTransferSerialReqT>(c, "toOesQryFundTransferSerialReqT)");
    autocxxpy::caster::try_generate<OesQryFundTransferSerialRspT>(c, "toOesQryFundTransferSerialRspT)");
    autocxxpy::caster::try_generate<OesQryLotWinningFilterT>(c, "toOesQryLotWinningFilterT)");
    autocxxpy::caster::try_generate<OesLotWinningItemT>(c, "toOesLotWinningItemT)");
    autocxxpy::caster::try_generate<OesQryLotWinningReqT>(c, "toOesQryLotWinningReqT)");
    autocxxpy::caster::try_generate<OesQryLotWinningRspT>(c, "toOesQryLotWinningRspT)");
    autocxxpy::caster::try_generate<OesQryIssueFilterT>(c, "toOesQryIssueFilterT)");
    autocxxpy::caster::try_generate<OesIssueItemT>(c, "toOesIssueItemT)");
    autocxxpy::caster::try_generate<OesQryIssueReqT>(c, "toOesQryIssueReqT)");
    autocxxpy::caster::try_generate<OesQryIssueRspT>(c, "toOesQryIssueRspT)");
    autocxxpy::caster::try_generate<OesQryStockFilterT>(c, "toOesQryStockFilterT)");
    autocxxpy::caster::try_generate<OesStockItemT>(c, "toOesStockItemT)");
    autocxxpy::caster::try_generate<OesQryStockReqT>(c, "toOesQryStockReqT)");
    autocxxpy::caster::try_generate<OesQryStockRspT>(c, "toOesQryStockRspT)");
    autocxxpy::caster::try_generate<OesQryEtfFilterT>(c, "toOesQryEtfFilterT)");
    autocxxpy::caster::try_generate<OesEtfItemT>(c, "toOesEtfItemT)");
    autocxxpy::caster::try_generate<OesQryEtfReqT>(c, "toOesQryEtfReqT)");
    autocxxpy::caster::try_generate<OesQryEtfRspT>(c, "toOesQryEtfRspT)");
    autocxxpy::caster::try_generate<OesQryEtfComponentFilterT>(c, "toOesQryEtfComponentFilterT)");
    autocxxpy::caster::try_generate<OesEtfComponentItemT>(c, "toOesEtfComponentItemT)");
    autocxxpy::caster::try_generate<OesQryEtfComponentReqT>(c, "toOesQryEtfComponentReqT)");
    autocxxpy::caster::try_generate<OesQryEtfComponentRspT>(c, "toOesQryEtfComponentRspT)");
    autocxxpy::caster::try_generate<OesQryOptionFilterT>(c, "toOesQryOptionFilterT)");
    autocxxpy::caster::try_generate<OesOptionItemT>(c, "toOesOptionItemT)");
    autocxxpy::caster::try_generate<OesQryOptionReqT>(c, "toOesQryOptionReqT)");
    autocxxpy::caster::try_generate<OesQryOptionRspT>(c, "toOesQryOptionRspT)");
    autocxxpy::caster::try_generate<OesQryTradingDayRspT>(c, "toOesQryTradingDayRspT)");
    autocxxpy::caster::try_generate<OesQryMarketStateFilterT>(c, "toOesQryMarketStateFilterT)");
    autocxxpy::caster::try_generate<OesMarketStateItemT>(c, "toOesMarketStateItemT)");
    autocxxpy::caster::try_generate<OesQryMarketStateReqT>(c, "toOesQryMarketStateReqT)");
    autocxxpy::caster::try_generate<OesQryMarketStateRspT>(c, "toOesQryMarketStateRspT)");
    autocxxpy::caster::try_generate<OesQryReqMsgT>(c, "toOesQryReqMsgT)");
    autocxxpy::caster::try_generate<OesQryRspMsgT>(c, "toOesQryRspMsgT)");
    autocxxpy::caster::try_generate<eOesMsgTypeT>(c, "toeOesMsgTypeT)");
    autocxxpy::caster::try_generate<eOesSubscribeReportTypeT>(c, "toeOesSubscribeReportTypeT)");
    autocxxpy::caster::try_generate<OesLogonReqT>(c, "toOesLogonReqT)");
    autocxxpy::caster::try_generate<OesLogonRspT>(c, "toOesLogonRspT)");
    autocxxpy::caster::try_generate<OesReportSynchronizationReqT>(c, "toOesReportSynchronizationReqT)");
    autocxxpy::caster::try_generate<OesReportSynchronizationRspT>(c, "toOesReportSynchronizationRspT)");
    autocxxpy::caster::try_generate<OesTestRequestReqT>(c, "toOesTestRequestReqT)");
    autocxxpy::caster::try_generate<OesTestRequestRspT>(c, "toOesTestRequestRspT)");
    autocxxpy::caster::try_generate<OesChangePasswordReqT>(c, "toOesChangePasswordReqT)");
    autocxxpy::caster::try_generate<OesChangePasswordRspT>(c, "toOesChangePasswordRspT)");
    autocxxpy::caster::try_generate<OesBatchOrdersHeadT>(c, "toOesBatchOrdersHeadT)");
    autocxxpy::caster::try_generate<OesBatchOrdersReqT>(c, "toOesBatchOrdersReqT)");
    autocxxpy::caster::try_generate<OesRptMsgHeadT>(c, "toOesRptMsgHeadT)");
    autocxxpy::caster::try_generate<OesRptMsgBodyT>(c, "toOesRptMsgBodyT)");
    autocxxpy::caster::try_generate<OesRptMsgT>(c, "toOesRptMsgT)");
    autocxxpy::caster::try_generate<OesReqMsgBodyT>(c, "toOesReqMsgBodyT)");
    autocxxpy::caster::try_generate<OesRspMsgBodyT>(c, "toOesRspMsgBodyT)");
    autocxxpy::caster::try_generate<SErrMsgT>(c, "toSErrMsgT)");
    autocxxpy::caster::try_generate<SDataBufferT>(c, "toSDataBufferT)");
    autocxxpy::caster::try_generate<eSSocketProtocolTypeT>(c, "toeSSocketProtocolTypeT)");
    autocxxpy::caster::try_generate<SSocketUriInfoT>(c, "toSSocketUriInfoT)");
    autocxxpy::caster::try_generate<SSocketIpPortInfoT>(c, "toSSocketIpPortInfoT)");
    autocxxpy::caster::try_generate<SSocketChannelInfoT>(c, "toSSocketChannelInfoT)");
    autocxxpy::caster::try_generate<SSocketOptionConfigT>(c, "toSSocketOptionConfigT)");
    autocxxpy::caster::try_generate<eGeneralClientClusterTypeT>(c, "toeGeneralClientClusterTypeT)");
    autocxxpy::caster::try_generate<eGeneralClientEncryptTypeT>(c, "toeGeneralClientEncryptTypeT)");
    autocxxpy::caster::try_generate<SGeneralClientChannelT>(c, "toSGeneralClientChannelT)");
    autocxxpy::caster::try_generate<SGeneralClientChannelGroupT>(c, "toSGeneralClientChannelGroupT)");
    autocxxpy::caster::try_generate<SGeneralClientAddrInfoT>(c, "toSGeneralClientAddrInfoT)");
    autocxxpy::caster::try_generate<SGeneralClientRemoteCfgT>(c, "toSGeneralClientRemoteCfgT)");
    autocxxpy::caster::try_generate<eOesApiChannelTypeT>(c, "toeOesApiChannelTypeT)");
    autocxxpy::caster::try_generate<OesApiSessionInfoT>(c, "toOesApiSessionInfoT)");
    autocxxpy::caster::try_generate<OesApiChannelGroupT>(c, "toOesApiChannelGroupT)");
    autocxxpy::caster::try_generate<OesApiAddrInfoT>(c, "toOesApiAddrInfoT)");
    autocxxpy::caster::try_generate<OesApiRemoteCfgT>(c, "toOesApiRemoteCfgT)");
    autocxxpy::caster::try_generate<OesApiSubscribeInfoT>(c, "toOesApiSubscribeInfoT)");
    autocxxpy::caster::try_generate<OesApiClientCfgT>(c, "toOesApiClientCfgT)");
    autocxxpy::caster::try_generate<OesApiClientEnvT>(c, "toOesApiClientEnvT)");
    autocxxpy::caster::try_generate<F_OESAPI_ON_RPT_MSG_T>(c, "toF_OESAPI_ON_RPT_MSG_T)");
    autocxxpy::caster::try_generate<F_OESAPI_ON_QRY_MSG_T>(c, "toF_OESAPI_ON_QRY_MSG_T)");
    autocxxpy::caster::try_generate<eMdsExchangeIdT>(c, "toeMdsExchangeIdT)");
    autocxxpy::caster::try_generate<eMdsMsgSourceT>(c, "toeMdsMsgSourceT)");
    autocxxpy::caster::try_generate<eMdsSecurityTypeT>(c, "toeMdsSecurityTypeT)");
    autocxxpy::caster::try_generate<eMdsMdStreamTypeT>(c, "toeMdsMdStreamTypeT)");
    autocxxpy::caster::try_generate<eMdsMdLevelT>(c, "toeMdsMdLevelT)");
    autocxxpy::caster::try_generate<eMdsL2PriceLevelOperatorT>(c, "toeMdsL2PriceLevelOperatorT)");
    autocxxpy::caster::try_generate<eMdsL2VirtualAuctionSideT>(c, "toeMdsL2VirtualAuctionSideT)");
    autocxxpy::caster::try_generate<eMdsL2TradeExecTypeT>(c, "toeMdsL2TradeExecTypeT)");
    autocxxpy::caster::try_generate<eMdsL2TradeBSFlagT>(c, "toeMdsL2TradeBSFlagT)");
    autocxxpy::caster::try_generate<eMdsL2OrderSideT>(c, "toeMdsL2OrderSideT)");
    autocxxpy::caster::try_generate<eMdsL2OrderTypeT>(c, "toeMdsL2OrderTypeT)");
    autocxxpy::caster::try_generate<eMdsClientTypeT>(c, "toeMdsClientTypeT)");
    autocxxpy::caster::try_generate<eMdsClientStatusT>(c, "toeMdsClientStatusT)");
    autocxxpy::caster::try_generate<MdsTradingSessionStatusMsgT>(c, "toMdsTradingSessionStatusMsgT)");
    autocxxpy::caster::try_generate<MdsSecurityStatusMsgT>(c, "toMdsSecurityStatusMsgT)");
    autocxxpy::caster::try_generate<MdsPriceLevelEntryT>(c, "toMdsPriceLevelEntryT)");
    autocxxpy::caster::try_generate<MdsMktDataSnapshotHeadT>(c, "toMdsMktDataSnapshotHeadT)");
    autocxxpy::caster::try_generate<MdsIndexSnapshotBodyT>(c, "toMdsIndexSnapshotBodyT)");
    autocxxpy::caster::try_generate<MdsStockSnapshotBodyT>(c, "toMdsStockSnapshotBodyT)");
    autocxxpy::caster::try_generate<MdsL1SnapshotBodyT>(c, "toMdsL1SnapshotBodyT)");
    autocxxpy::caster::try_generate<MdsL2StockSnapshotBodyT>(c, "toMdsL2StockSnapshotBodyT)");
    autocxxpy::caster::try_generate<MdsL2StockSnapshotIncrementalT>(c, "toMdsL2StockSnapshotIncrementalT)");
    autocxxpy::caster::try_generate<MdsL2BestOrdersSnapshotBodyT>(c, "toMdsL2BestOrdersSnapshotBodyT)");
    autocxxpy::caster::try_generate<MdsL2BestOrdersSnapshotIncrementalT>(c, "toMdsL2BestOrdersSnapshotIncrementalT)");
    autocxxpy::caster::try_generate<MdsL2VirtualAuctionPriceT>(c, "toMdsL2VirtualAuctionPriceT)");
    autocxxpy::caster::try_generate<MdsL2MarketOverviewT>(c, "toMdsL2MarketOverviewT)");
    autocxxpy::caster::try_generate<MdsL2SnapshotBodyT>(c, "toMdsL2SnapshotBodyT)");
    autocxxpy::caster::try_generate<MdsMktDataSnapshotT>(c, "toMdsMktDataSnapshotT)");
    autocxxpy::caster::try_generate<MdsL2TradeT>(c, "toMdsL2TradeT)");
    autocxxpy::caster::try_generate<MdsL2OrderT>(c, "toMdsL2OrderT)");
    autocxxpy::caster::try_generate<MdsL2TickLostT>(c, "toMdsL2TickLostT)");
    autocxxpy::caster::try_generate<MdsQryMktDataSnapshotReqT>(c, "toMdsQryMktDataSnapshotReqT)");
    autocxxpy::caster::try_generate<MdsQrySecurityStatusReqT>(c, "toMdsQrySecurityStatusReqT)");
    autocxxpy::caster::try_generate<MdsQryTrdSessionStatusReqT>(c, "toMdsQryTrdSessionStatusReqT)");
    autocxxpy::caster::try_generate<eMdsMsgTypeT>(c, "toeMdsMsgTypeT)");
    autocxxpy::caster::try_generate<eMdsSubscribeModeT>(c, "toeMdsSubscribeModeT)");
    autocxxpy::caster::try_generate<eMdsMktSubscribeFlagT>(c, "toeMdsMktSubscribeFlagT)");
    autocxxpy::caster::try_generate<eMdsSubscribedTickTypeT>(c, "toeMdsSubscribedTickTypeT)");
    autocxxpy::caster::try_generate<eMdsSubscribedTickExpireTypeT>(c, "toeMdsSubscribedTickExpireTypeT)");
    autocxxpy::caster::try_generate<eMdsSubscribeDataTypeT>(c, "toeMdsSubscribeDataTypeT)");
    autocxxpy::caster::try_generate<eMdsTickChannelNoT>(c, "toeMdsTickChannelNoT)");
    autocxxpy::caster::try_generate<MdsLogonReqT>(c, "toMdsLogonReqT)");
    autocxxpy::caster::try_generate<MdsLogonRspT>(c, "toMdsLogonRspT)");
    autocxxpy::caster::try_generate<MdsMktDataRequestEntryT>(c, "toMdsMktDataRequestEntryT)");
    autocxxpy::caster::try_generate<MdsMktDataRequestReqT>(c, "toMdsMktDataRequestReqT)");
    autocxxpy::caster::try_generate<MdsMktDataRequestReqBufT>(c, "toMdsMktDataRequestReqBufT)");
    autocxxpy::caster::try_generate<MdsMktDataRequestRspT>(c, "toMdsMktDataRequestRspT)");
    autocxxpy::caster::try_generate<MdsTestRequestReqT>(c, "toMdsTestRequestReqT)");
    autocxxpy::caster::try_generate<MdsTestRequestRspT>(c, "toMdsTestRequestRspT)");
    autocxxpy::caster::try_generate<MdsMktReqMsgBodyT>(c, "toMdsMktReqMsgBodyT)");
    autocxxpy::caster::try_generate<MdsMktRspMsgBodyT>(c, "toMdsMktRspMsgBodyT)");
    autocxxpy::caster::try_generate<MdsUdpPktHeadT>(c, "toMdsUdpPktHeadT)");
    autocxxpy::caster::try_generate<eMdsApiChannelTypeT>(c, "toeMdsApiChannelTypeT)");
    autocxxpy::caster::try_generate<MdsApiSessionInfoT>(c, "toMdsApiSessionInfoT)");
    autocxxpy::caster::try_generate<MdsApiChannelGroupT>(c, "toMdsApiChannelGroupT)");
    autocxxpy::caster::try_generate<MdsApiAddrInfoT>(c, "toMdsApiAddrInfoT)");
    autocxxpy::caster::try_generate<MdsApiRemoteCfgT>(c, "toMdsApiRemoteCfgT)");
    autocxxpy::caster::try_generate<MdsApiSubscribeInfoT>(c, "toMdsApiSubscribeInfoT)");
    autocxxpy::caster::try_generate<MdsApiClientCfgT>(c, "toMdsApiClientCfgT)");
    autocxxpy::caster::try_generate<MdsApiClientEnvT>(c, "toMdsApiClientEnvT)");
    autocxxpy::caster::try_generate<F_MDSAPI_ONMSG_T>(c, "toF_MDSAPI_ONMSG_T)");
}
