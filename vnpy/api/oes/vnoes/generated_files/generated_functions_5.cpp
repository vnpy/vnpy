#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


void generate_class_SGeneralClientAddrInfo(pybind11::object & parent)
{
    pybind11::class_<_SGeneralClientAddrInfo> c(parent, "_SGeneralClientAddrInfo");
    if constexpr (std::is_default_constructible_v<_SGeneralClientAddrInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "uri", uri);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "hostNum", hostNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientAddrInfo, c);
    module_vnoes::objects.emplace("_SGeneralClientAddrInfo", c);
}
void generate_class_SGeneralClientRemoteCfg(pybind11::object & parent)
{
    pybind11::class_<_SGeneralClientRemoteCfg> c(parent, "_SGeneralClientRemoteCfg");
    if constexpr (std::is_default_constructible_v<_SGeneralClientRemoteCfg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "addrCnt", addrCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "clusterType", clusterType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "senderCompId", senderCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "addrList", addrList);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "socketOpt", socketOpt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientRemoteCfg, c);
    module_vnoes::objects.emplace("_SGeneralClientRemoteCfg", c);
}
void generate_class_OesApiSubscribeInfo(pybind11::object & parent)
{
    pybind11::class_<_OesApiSubscribeInfo> c(parent, "_OesApiSubscribeInfo");
    if constexpr (std::is_default_constructible_v<_OesApiSubscribeInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "rptTypes", rptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiSubscribeInfo, c);
    module_vnoes::objects.emplace("_OesApiSubscribeInfo", c);
}
void generate_class_OesApiClientCfg(pybind11::object & parent)
{
    pybind11::class_<_OesApiClientCfg> c(parent, "_OesApiClientCfg");
    if constexpr (std::is_default_constructible_v<_OesApiClientCfg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "ordChannelCfg", ordChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "rptChannelCfg", rptChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "qryChannelCfg", qryChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiClientCfg, c);
    module_vnoes::objects.emplace("_OesApiClientCfg", c);
}
void generate_class_OesApiClientEnv(pybind11::object & parent)
{
    pybind11::class_<_OesApiClientEnv> c(parent, "_OesApiClientEnv");
    if constexpr (std::is_default_constructible_v<_OesApiClientEnv>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "ordChannel", ordChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "rptChannel", rptChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "qryChannel", qryChannel);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiClientEnv, c);
    module_vnoes::objects.emplace("_OesApiClientEnv", c);
}
void generate_class_MdsTradingSessionStatusMsg(pybind11::object & parent)
{
    pybind11::class_<_MdsTradingSessionStatusMsg> c(parent, "_MdsTradingSessionStatusMsg");
    if constexpr (std::is_default_constructible_v<_MdsTradingSessionStatusMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__mdsRecvTime", __mdsRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "TotNoRelatedSym", TotNoRelatedSym);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "TradingSessionID", TradingSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsTradingSessionStatusMsg, c);
    module_vnoes::objects.emplace("_MdsTradingSessionStatusMsg", c);
}
void generate_class_MdsSecurityStatusMsg(pybind11::object & parent)
{
    pybind11::class_<_MdsSecurityStatusMsg> c(parent, "_MdsSecurityStatusMsg");
    if constexpr (std::is_default_constructible_v<_MdsSecurityStatusMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__mdsRecvTime", __mdsRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "FinancialStatus", FinancialStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "NoSwitch", NoSwitch);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler4", __filler4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "switches", switches);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsSecurityStatusMsg, c);
    module_vnoes::objects.emplace("_MdsSecurityStatusMsg", c);
}
void generate_class_MdsPriceLevelEntry(pybind11::object & parent)
{
    pybind11::class_<_MdsPriceLevelEntry> c(parent, "_MdsPriceLevelEntry");
    if constexpr (std::is_default_constructible_v<_MdsPriceLevelEntry>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "NumberOfOrders", NumberOfOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsPriceLevelEntry, c);
    module_vnoes::objects.emplace("_MdsPriceLevelEntry", c);
}
void generate_class_MdsMktDataSnapshotHead(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataSnapshotHead> c(parent, "_MdsMktDataSnapshotHead");
    if constexpr (std::is_default_constructible_v<_MdsMktDataSnapshotHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origMdSource", __origMdSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "bodyLength", bodyLength);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "mdStreamType", mdStreamType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataSnapshotHead, c);
    module_vnoes::objects.emplace("_MdsMktDataSnapshotHead", c);
}
void generate_class_MdsIndexSnapshotBody(pybind11::object & parent)
{
    pybind11::class_<_MdsIndexSnapshotBody> c(parent, "_MdsIndexSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsIndexSnapshotBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "TradingPhaseCode", TradingPhaseCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "PrevCloseIdx", PrevCloseIdx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "OpenIdx", OpenIdx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "HighIdx", HighIdx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "LowIdx", LowIdx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "LastIdx", LastIdx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "CloseIdx", CloseIdx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "StockNum", StockNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "__filler1", __filler1);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsIndexSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsIndexSnapshotBody", c);
}
void generate_class_MdsStockSnapshotBody(pybind11::object & parent)
{
    pybind11::class_<_MdsStockSnapshotBody> c(parent, "_MdsStockSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsStockSnapshotBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TradingPhaseCode", TradingPhaseCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "PrevClosePx", PrevClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "OpenPx", OpenPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "HighPx", HighPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "LowPx", LowPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TradePx", TradePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "ClosePx", ClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "IOPV", IOPV);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "NAV", NAV);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TotalLongPosition", TotalLongPosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "BidLevels", BidLevels);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "OfferLevels", OfferLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsStockSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsStockSnapshotBody", c);
}
void generate_class_MdsL1SnapshotBody(pybind11::object & parent)
{
    pybind11::class_<_MdsL1SnapshotBody> c(parent, "_MdsL1SnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL1SnapshotBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1SnapshotBody, "stock", stock);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1SnapshotBody, "option", option);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1SnapshotBody, "index", index);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL1SnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL1SnapshotBody", c);
}
void generate_class_MdsL2StockSnapshotBody(pybind11::object & parent)
{
    pybind11::class_<_MdsL2StockSnapshotBody> c(parent, "_MdsL2StockSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL2StockSnapshotBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TradingPhaseCode", TradingPhaseCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "PrevClosePx", PrevClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "OpenPx", OpenPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "HighPx", HighPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "LowPx", LowPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TradePx", TradePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "ClosePx", ClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "IOPV", IOPV);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "NAV", NAV);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalLongPosition", TotalLongPosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalBidQty", TotalBidQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalOfferQty", TotalOfferQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "WeightedAvgBidPx", WeightedAvgBidPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "WeightedAvgOfferPx", WeightedAvgOfferPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "BidPriceLevel", BidPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "OfferPriceLevel", OfferPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "BidLevels", BidLevels);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "OfferLevels", OfferLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2StockSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL2StockSnapshotBody", c);
}
void generate_class_MdsL2StockSnapshotIncremental(pybind11::object & parent)
{
    pybind11::class_<_MdsL2StockSnapshotIncremental> c(parent, "_MdsL2StockSnapshotIncremental");
    if constexpr (std::is_default_constructible_v<_MdsL2StockSnapshotIncremental>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "OpenPx", OpenPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TradePx", TradePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "ClosePx", ClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "IOPV", IOPV);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalBidQty", TotalBidQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalOfferQty", TotalOfferQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "WeightedAvgBidPx", WeightedAvgBidPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "WeightedAvgOfferPx", WeightedAvgOfferPx);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "BidPriceLevel", BidPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "OfferPriceLevel", OfferPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "BestBidPrice", BestBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "HasContainedBestBidLevel", HasContainedBestBidLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "NoBidLevel", NoBidLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "BestOfferPrice", BestOfferPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "HasContainedBestOfferLevel", HasContainedBestOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "NoOfferLevel", NoOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "PriceLevelOperator", PriceLevelOperator);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "PriceLevels", PriceLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2StockSnapshotIncremental, c);
    module_vnoes::objects.emplace("_MdsL2StockSnapshotIncremental", c);
}
void generate_class_MdsL2BestOrdersSnapshotBody(pybind11::object & parent)
{
    pybind11::class_<_MdsL2BestOrdersSnapshotBody> c(parent, "_MdsL2BestOrdersSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL2BestOrdersSnapshotBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "NoBidOrders", NoBidOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "NoOfferOrders", NoOfferOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "BestBidPrice", BestBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "BestOfferPrice", BestOfferPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "BidOrderQty", BidOrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "OfferOrderQty", OfferOrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2BestOrdersSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL2BestOrdersSnapshotBody", c);
}
void generate_class_MdsL2BestOrdersSnapshotIncremental(pybind11::object & parent)
{
    pybind11::class_<_MdsL2BestOrdersSnapshotIncremental> c(parent, "_MdsL2BestOrdersSnapshotIncremental");
    if constexpr (std::is_default_constructible_v<_MdsL2BestOrdersSnapshotIncremental>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "BestBidPrice", BestBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "HasContainedBestBidLevel", HasContainedBestBidLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "ContinualDeletedBidOrders", ContinualDeletedBidOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "NoBidOrders", NoBidOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "BestOfferPrice", BestOfferPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "HasContainedBestOfferLevel", HasContainedBestOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "ContinualDeletedOfferOrders", ContinualDeletedOfferOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "NoOfferOrders", NoOfferOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "OperatorEntryID", OperatorEntryID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, c);
    module_vnoes::objects.emplace("_MdsL2BestOrdersSnapshotIncremental", c);
}
void generate_class_MdsL2VirtualAuctionPrice(pybind11::object & parent)
{
    pybind11::class_<_MdsL2VirtualAuctionPrice> c(parent, "_MdsL2VirtualAuctionPrice");
    if constexpr (std::is_default_constructible_v<_MdsL2VirtualAuctionPrice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2VirtualAuctionPrice, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2VirtualAuctionPrice, "LeavesSide", LeavesSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2VirtualAuctionPrice, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2VirtualAuctionPrice, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2VirtualAuctionPrice, "VirtualAuctionQty", VirtualAuctionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2VirtualAuctionPrice, "LeavesQty", LeavesQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2VirtualAuctionPrice, c);
    module_vnoes::objects.emplace("_MdsL2VirtualAuctionPrice", c);
}
void generate_class_MdsL2MarketOverview(pybind11::object & parent)
{
    pybind11::class_<_MdsL2MarketOverview> c(parent, "_MdsL2MarketOverview");
    if constexpr (std::is_default_constructible_v<_MdsL2MarketOverview>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "OrigDate", OrigDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "OrigTime", OrigTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "__mdsRecvTime", __mdsRecvTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2MarketOverview, c);
    module_vnoes::objects.emplace("_MdsL2MarketOverview", c);
}
void generate_class_MdsL2SnapshotBody(pybind11::object & parent)
{
    pybind11::class_<_MdsL2SnapshotBody> c(parent, "_MdsL2SnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL2SnapshotBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2Stock", l2Stock);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2StockIncremental", l2StockIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2BestOrders", l2BestOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2BestOrdersIncremental", l2BestOrdersIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "index", index);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2VirtualAuctionPrice", l2VirtualAuctionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2MarketOverview", l2MarketOverview);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2SnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL2SnapshotBody", c);
}
void generate_class_MdsMktDataSnapshot(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataSnapshot> c(parent, "_MdsMktDataSnapshot");
    if constexpr (std::is_default_constructible_v<_MdsMktDataSnapshot>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "head", head);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2Stock", l2Stock);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2StockIncremental", l2StockIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2BestOrders", l2BestOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2BestOrdersIncremental", l2BestOrdersIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "stock", stock);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "option", option);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "index", index);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2VirtualAuctionPrice", l2VirtualAuctionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2MarketOverview", l2MarketOverview);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataSnapshot, c);
    module_vnoes::objects.emplace("_MdsMktDataSnapshot", c);
}
void generate_class_MdsL2Trade(pybind11::object & parent)
{
    pybind11::class_<_MdsL2Trade> c(parent, "_MdsL2Trade");
    if constexpr (std::is_default_constructible_v<_MdsL2Trade>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TransactTime", TransactTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "ChannelNo", ChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "ApplSeqNum", ApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "ExecType", ExecType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradeBSFlag", TradeBSFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradePrice", TradePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradeQty", TradeQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradeMoney", TradeMoney);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "BidApplSeqNum", BidApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "OfferApplSeqNum", OfferApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2Trade, c);
    module_vnoes::objects.emplace("_MdsL2Trade", c);
}
void generate_class_MdsL2Order(pybind11::object & parent)
{
    pybind11::class_<_MdsL2Order> c(parent, "_MdsL2Order");
    if constexpr (std::is_default_constructible_v<_MdsL2Order>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "TransactTime", TransactTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "ChannelNo", ChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "ApplSeqNum", ApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "Side", Side);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2Order, c);
    module_vnoes::objects.emplace("_MdsL2Order", c);
}
void generate_class_MdsL2TickLost(pybind11::object & parent)
{
    pybind11::class_<_MdsL2TickLost> c(parent, "_MdsL2TickLost");
    if constexpr (std::is_default_constructible_v<_MdsL2TickLost>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "lostTime", lostTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "channelNo", channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "beginApplSeqNum", beginApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "endApplSeqNum", endApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2TickLost, "__origTickSeq", __origTickSeq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2TickLost, c);
    module_vnoes::objects.emplace("_MdsL2TickLost", c);
}
void generate_class_MdsQryMktDataSnapshotReq(pybind11::object & parent)
{
    pybind11::class_<_MdsQryMktDataSnapshotReq> c(parent, "_MdsQryMktDataSnapshotReq");
    if constexpr (std::is_default_constructible_v<_MdsQryMktDataSnapshotReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "instrId", instrId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryMktDataSnapshotReq, c);
    module_vnoes::objects.emplace("_MdsQryMktDataSnapshotReq", c);
}
void generate_class_MdsQryTrdSessionStatusReq(pybind11::object & parent)
{
    pybind11::class_<_MdsQryTrdSessionStatusReq> c(parent, "_MdsQryTrdSessionStatusReq");
    if constexpr (std::is_default_constructible_v<_MdsQryTrdSessionStatusReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryTrdSessionStatusReq, c);
    module_vnoes::objects.emplace("_MdsQryTrdSessionStatusReq", c);
}
void generate_class_MdsLogonReq(pybind11::object & parent)
{
    pybind11::class_<_MdsLogonReq> c(parent, "_MdsLogonReq");
    if constexpr (std::is_default_constructible_v<_MdsLogonReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonReq, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonReq, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonReq, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonReq, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonReq, "applVerId", applVerId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsLogonReq, c);
    module_vnoes::objects.emplace("_MdsLogonReq", c);
}
void generate_class_MdsLogonRsp(pybind11::object & parent)
{
    pybind11::class_<_MdsLogonRsp> c(parent, "_MdsLogonRsp");
    if constexpr (std::is_default_constructible_v<_MdsLogonRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "applVerId", applVerId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "minVerId", minVerId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "hostNum", hostNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "isLeader", isLeader);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "leaderHostNum", leaderHostNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsLogonRsp, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsLogonRsp, c);
    module_vnoes::objects.emplace("_MdsLogonRsp", c);
}
void generate_class_MdsMktDataRequestEntry(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataRequestEntry> c(parent, "_MdsMktDataRequestEntry");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestEntry>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "instrId", instrId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestEntry, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestEntry", c);
}
void generate_class_MdsMktDataRequestReq(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataRequestReq> c(parent, "_MdsMktDataRequestReq");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "subMode", subMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "tickType", tickType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "sseStockFlag", sseStockFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "sseIndexFlag", sseIndexFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "sseOptionFlag", sseOptionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "szseStockFlag", szseStockFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "szseIndexFlag", szseIndexFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "szseOptionFlag", szseOptionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "isRequireInitialMktData", isRequireInitialMktData);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "__channelNos", __channelNos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "tickExpireType", tickExpireType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "dataTypes", dataTypes);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "beginTime", beginTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "subSecurityCnt", subSecurityCnt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestReq, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestReq", c);
}
