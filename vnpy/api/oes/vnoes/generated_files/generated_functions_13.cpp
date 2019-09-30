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


void generate_enum_eGeneralClientEncryptType(pybind11::object & parent)
{
    // _eGeneralClientEncryptType
    pybind11::enum_<_eGeneralClientEncryptType> e(parent, "_eGeneralClientEncryptType", pybind11::arithmetic());
    // _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_NONE
    e.value("GENERAL_CLI_ENCRYPT_NONE", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_NONE);
    // _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_MD5
    e.value("GENERAL_CLI_ENCRYPT_MD5", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_MD5);
    // _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_SHA
    e.value("GENERAL_CLI_ENCRYPT_SHA", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_SHA);
    // _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_DES
    e.value("GENERAL_CLI_ENCRYPT_DES", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_DES);
    // _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_AES
    e.value("GENERAL_CLI_ENCRYPT_AES", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_AES);
    // _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_RSA
    e.value("GENERAL_CLI_ENCRYPT_RSA", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_RSA);
    // _eGeneralClientEncryptType::__GENERAL_CLI_ENCRYPT_MASK_DIGESTED
    e.value("__GENERAL_CLI_ENCRYPT_MASK_DIGESTED", _eGeneralClientEncryptType::__GENERAL_CLI_ENCRYPT_MASK_DIGESTED);
    // _eGeneralClientEncryptType::__GENERAL_CLI_ENCRYPT_MASK_ENCRYPTED
    e.value("__GENERAL_CLI_ENCRYPT_MASK_ENCRYPTED", _eGeneralClientEncryptType::__GENERAL_CLI_ENCRYPT_MASK_ENCRYPTED);
    e.export_values();
    module_vnoes::objects.emplace("_eGeneralClientEncryptType", e);
}
void generate_enum_eOesApiChannelType(pybind11::object & parent)
{
    // _eOesApiChannelType
    pybind11::enum_<_eOesApiChannelType> e(parent, "_eOesApiChannelType", pybind11::arithmetic());
    // _eOesApiChannelType::OESAPI_CHANNEL_TYPE_ORDER
    e.value("OESAPI_CHANNEL_TYPE_ORDER", _eOesApiChannelType::OESAPI_CHANNEL_TYPE_ORDER);
    // _eOesApiChannelType::OESAPI_CHANNEL_TYPE_REPORT
    e.value("OESAPI_CHANNEL_TYPE_REPORT", _eOesApiChannelType::OESAPI_CHANNEL_TYPE_REPORT);
    // _eOesApiChannelType::OESAPI_CHANNEL_TYPE_QUERY
    e.value("OESAPI_CHANNEL_TYPE_QUERY", _eOesApiChannelType::OESAPI_CHANNEL_TYPE_QUERY);
    e.export_values();
    module_vnoes::objects.emplace("_eOesApiChannelType", e);
}
void generate_enum_eMdsExchangeId(pybind11::object & parent)
{
    // _eMdsExchangeId
    pybind11::enum_<_eMdsExchangeId> e(parent, "_eMdsExchangeId", pybind11::arithmetic());
    // _eMdsExchangeId::MDS_EXCH_UNDEFINE
    e.value("MDS_EXCH_UNDEFINE", _eMdsExchangeId::MDS_EXCH_UNDEFINE);
    // _eMdsExchangeId::MDS_EXCH_SSE
    e.value("MDS_EXCH_SSE", _eMdsExchangeId::MDS_EXCH_SSE);
    // _eMdsExchangeId::MDS_EXCH_SZSE
    e.value("MDS_EXCH_SZSE", _eMdsExchangeId::MDS_EXCH_SZSE);
    // _eMdsExchangeId::__MAX_MDS_EXCH
    e.value("__MAX_MDS_EXCH", _eMdsExchangeId::__MAX_MDS_EXCH);
    // _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED4
    e.value("__MAX_MDS_EXCH_ALIGNED4", _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED4);
    // _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED8
    e.value("__MAX_MDS_EXCH_ALIGNED8", _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsExchangeId", e);
}
void generate_enum_eMdsMsgSource(pybind11::object & parent)
{
    // _eMdsMsgSource
    pybind11::enum_<_eMdsMsgSource> e(parent, "_eMdsMsgSource", pybind11::arithmetic());
    // _eMdsMsgSource::MDS_MSGSRC_UNDEFINED
    e.value("MDS_MSGSRC_UNDEFINED", _eMdsMsgSource::MDS_MSGSRC_UNDEFINED);
    // _eMdsMsgSource::MDS_MSGSRC_EZEI_TCP
    e.value("MDS_MSGSRC_EZEI_TCP", _eMdsMsgSource::MDS_MSGSRC_EZEI_TCP);
    // _eMdsMsgSource::MDS_MSGSRC_EZEI_UDP
    e.value("MDS_MSGSRC_EZEI_UDP", _eMdsMsgSource::MDS_MSGSRC_EZEI_UDP);
    // _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL2
    e.value("MDS_MSGSRC_VDE_LEVEL2", _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL2);
    // _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL1
    e.value("MDS_MSGSRC_VDE_LEVEL1", _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL1);
    // _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_BINARY
    e.value("MDS_MSGSRC_SZSE_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_BINARY);
    // _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_STEP
    e.value("MDS_MSGSRC_SZSE_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_STEP);
    // _eMdsMsgSource::MDS_MSGSRC_MDS_TCP
    e.value("MDS_MSGSRC_MDS_TCP", _eMdsMsgSource::MDS_MSGSRC_MDS_TCP);
    // _eMdsMsgSource::MDS_MSGSRC_MDS_UDP
    e.value("MDS_MSGSRC_MDS_UDP", _eMdsMsgSource::MDS_MSGSRC_MDS_UDP);
    // _eMdsMsgSource::MDS_MSGSRC_FILE_MKTDT
    e.value("MDS_MSGSRC_FILE_MKTDT", _eMdsMsgSource::MDS_MSGSRC_FILE_MKTDT);
    // _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_BINARY
    e.value("MDS_MSGSRC_SSE_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_BINARY);
    // _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_STEP
    e.value("MDS_MSGSRC_SSE_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_STEP);
    // _eMdsMsgSource::__MAX_MDS_MSGSRC
    e.value("__MAX_MDS_MSGSRC", _eMdsMsgSource::__MAX_MDS_MSGSRC);
    // _eMdsMsgSource::MDS_MSGSRC_MDGW_BINARY
    e.value("MDS_MSGSRC_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_MDGW_BINARY);
    // _eMdsMsgSource::MDS_MSGSRC_MDGW_STEP
    e.value("MDS_MSGSRC_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_MDGW_STEP);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMsgSource", e);
}
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
