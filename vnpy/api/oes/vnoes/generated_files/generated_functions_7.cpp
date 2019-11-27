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


void generate_class_OesApiClientCfg(pybind11::object & parent)
{
    // _OesApiClientCfg
    pybind11::class_<_OesApiClientCfg> c(parent, "_OesApiClientCfg");
    if constexpr (std::is_default_constructible_v<_OesApiClientCfg>)
        c.def(pybind11::init<>());
    // _OesApiClientCfg::ordChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "ordChannelCfg", ordChannelCfg);
    // _OesApiClientCfg::rptChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "rptChannelCfg", rptChannelCfg);
    // _OesApiClientCfg::qryChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "qryChannelCfg", qryChannelCfg);
    // _OesApiClientCfg::subscribeInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiClientCfg, c);
    module_vnoes::objects.emplace("_OesApiClientCfg", c);
}
void generate_class_OesApiClientEnv(pybind11::object & parent)
{
    // _OesApiClientEnv
    pybind11::class_<_OesApiClientEnv> c(parent, "_OesApiClientEnv");
    if constexpr (std::is_default_constructible_v<_OesApiClientEnv>)
        c.def(pybind11::init<>());
    // _OesApiClientEnv::ordChannel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "ordChannel", ordChannel);
    // _OesApiClientEnv::rptChannel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "rptChannel", rptChannel);
    // _OesApiClientEnv::qryChannel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "qryChannel", qryChannel);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiClientEnv, c);
    module_vnoes::objects.emplace("_OesApiClientEnv", c);
}
void generate_class_MdsTradingSessionStatusMsg(pybind11::object & parent)
{
    // _MdsTradingSessionStatusMsg
    pybind11::class_<_MdsTradingSessionStatusMsg> c(parent, "_MdsTradingSessionStatusMsg");
    if constexpr (std::is_default_constructible_v<_MdsTradingSessionStatusMsg>)
        c.def(pybind11::init<>());
    // _MdsTradingSessionStatusMsg::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "exchId", exchId);
    // _MdsTradingSessionStatusMsg::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "mdProductType", mdProductType);
    // _MdsTradingSessionStatusMsg::__isRepeated
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__isRepeated", __isRepeated);
    // _MdsTradingSessionStatusMsg::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__filler1", __filler1);
    // _MdsTradingSessionStatusMsg::tradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "tradeDate", tradeDate);
    // _MdsTradingSessionStatusMsg::updateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "updateTime", updateTime);
    // _MdsTradingSessionStatusMsg::__exchSendingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__exchSendingTime", __exchSendingTime);
    // _MdsTradingSessionStatusMsg::__mdsRecvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__mdsRecvTime", __mdsRecvTime);
    // _MdsTradingSessionStatusMsg::TotNoRelatedSym
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "TotNoRelatedSym", TotNoRelatedSym);
    // _MdsTradingSessionStatusMsg::TradingSessionID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "TradingSessionID", TradingSessionID);
    // _MdsTradingSessionStatusMsg::__filler3
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__filler3", __filler3);
    // _MdsTradingSessionStatusMsg::__dataVersion
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__dataVersion", __dataVersion);
    // _MdsTradingSessionStatusMsg::__origTickSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__origTickSeq", __origTickSeq);
    // _MdsTradingSessionStatusMsg::__origNetTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__origNetTime", __origNetTime);
    // _MdsTradingSessionStatusMsg::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__recvTime", __recvTime);
    // _MdsTradingSessionStatusMsg::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__collectedTime", __collectedTime);
    // _MdsTradingSessionStatusMsg::__processedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__processedTime", __processedTime);
    // _MdsTradingSessionStatusMsg::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsTradingSessionStatusMsg, c);
    module_vnoes::objects.emplace("_MdsTradingSessionStatusMsg", c);
}
void generate_class_MdsSecurityStatusMsg(pybind11::object & parent)
{
    // _MdsSecurityStatusMsg
    pybind11::class_<_MdsSecurityStatusMsg> c(parent, "_MdsSecurityStatusMsg");
    if constexpr (std::is_default_constructible_v<_MdsSecurityStatusMsg>)
        c.def(pybind11::init<>());
    // _MdsSecurityStatusMsg::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "exchId", exchId);
    // _MdsSecurityStatusMsg::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "mdProductType", mdProductType);
    // _MdsSecurityStatusMsg::__isRepeated
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__isRepeated", __isRepeated);
    // _MdsSecurityStatusMsg::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler1", __filler1);
    // _MdsSecurityStatusMsg::tradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "tradeDate", tradeDate);
    // _MdsSecurityStatusMsg::updateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "updateTime", updateTime);
    // _MdsSecurityStatusMsg::__exchSendingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__exchSendingTime", __exchSendingTime);
    // _MdsSecurityStatusMsg::__mdsRecvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__mdsRecvTime", __mdsRecvTime);
    // _MdsSecurityStatusMsg::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "instrId", instrId);
    // _MdsSecurityStatusMsg::SecurityID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "SecurityID", SecurityID);
    // _MdsSecurityStatusMsg::FinancialStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "FinancialStatus", FinancialStatus);
    // _MdsSecurityStatusMsg::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler2", __filler2);
    // _MdsSecurityStatusMsg::__channelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__channelNo", __channelNo);
    // _MdsSecurityStatusMsg::__dataVersion
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__dataVersion", __dataVersion);
    // _MdsSecurityStatusMsg::__origTickSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__origTickSeq", __origTickSeq);
    // _MdsSecurityStatusMsg::NoSwitch
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "NoSwitch", NoSwitch);
    // _MdsSecurityStatusMsg::__filler4
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler4", __filler4);
    // _MdsSecurityStatusMsg::switches
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "switches", switches);
    // _MdsSecurityStatusMsg::__origNetTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__origNetTime", __origNetTime);
    // _MdsSecurityStatusMsg::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__recvTime", __recvTime);
    // _MdsSecurityStatusMsg::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__collectedTime", __collectedTime);
    // _MdsSecurityStatusMsg::__processedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__processedTime", __processedTime);
    // _MdsSecurityStatusMsg::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsSecurityStatusMsg, c);
    module_vnoes::objects.emplace("_MdsSecurityStatusMsg", c);
}
void generate_class_MdsPriceLevelEntry(pybind11::object & parent)
{
    // _MdsPriceLevelEntry
    pybind11::class_<_MdsPriceLevelEntry> c(parent, "_MdsPriceLevelEntry");
    if constexpr (std::is_default_constructible_v<_MdsPriceLevelEntry>)
        c.def(pybind11::init<>());
    // _MdsPriceLevelEntry::Price
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "Price", Price);
    // _MdsPriceLevelEntry::NumberOfOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "NumberOfOrders", NumberOfOrders);
    // _MdsPriceLevelEntry::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsPriceLevelEntry, c);
    module_vnoes::objects.emplace("_MdsPriceLevelEntry", c);
}
void generate_class_MdsMktDataSnapshotHead(pybind11::object & parent)
{
    // _MdsMktDataSnapshotHead
    pybind11::class_<_MdsMktDataSnapshotHead> c(parent, "_MdsMktDataSnapshotHead");
    if constexpr (std::is_default_constructible_v<_MdsMktDataSnapshotHead>)
        c.def(pybind11::init<>());
    // _MdsMktDataSnapshotHead::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "exchId", exchId);
    // _MdsMktDataSnapshotHead::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "mdProductType", mdProductType);
    // _MdsMktDataSnapshotHead::__isRepeated
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__isRepeated", __isRepeated);
    // _MdsMktDataSnapshotHead::__origMdSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origMdSource", __origMdSource);
    // _MdsMktDataSnapshotHead::tradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "tradeDate", tradeDate);
    // _MdsMktDataSnapshotHead::updateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "updateTime", updateTime);
    // _MdsMktDataSnapshotHead::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "instrId", instrId);
    // _MdsMktDataSnapshotHead::bodyLength
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "bodyLength", bodyLength);
    // _MdsMktDataSnapshotHead::mdStreamType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "mdStreamType", mdStreamType);
    // _MdsMktDataSnapshotHead::__channelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__channelNo", __channelNo);
    // _MdsMktDataSnapshotHead::__dataVersion
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__dataVersion", __dataVersion);
    // _MdsMktDataSnapshotHead::__origTickSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origTickSeq", __origTickSeq);
    // _MdsMktDataSnapshotHead::__lastUpdateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__lastUpdateTime", __lastUpdateTime);
    // _MdsMktDataSnapshotHead::__origNetTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origNetTime", __origNetTime);
    // _MdsMktDataSnapshotHead::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__recvTime", __recvTime);
    // _MdsMktDataSnapshotHead::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__collectedTime", __collectedTime);
    // _MdsMktDataSnapshotHead::__processedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__processedTime", __processedTime);
    // _MdsMktDataSnapshotHead::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataSnapshotHead, c);
    module_vnoes::objects.emplace("_MdsMktDataSnapshotHead", c);
}
void generate_class_MdsIndexSnapshotBody(pybind11::object & parent)
{
    // _MdsIndexSnapshotBody
    pybind11::class_<_MdsIndexSnapshotBody> c(parent, "_MdsIndexSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsIndexSnapshotBody>)
        c.def(pybind11::init<>());
    // _MdsIndexSnapshotBody::SecurityID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "SecurityID", SecurityID);
    // _MdsIndexSnapshotBody::TradingPhaseCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "TradingPhaseCode", TradingPhaseCode);
    // _MdsIndexSnapshotBody::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "__filler", __filler);
    // _MdsIndexSnapshotBody::NumTrades
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "NumTrades", NumTrades);
    // _MdsIndexSnapshotBody::TotalVolumeTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    // _MdsIndexSnapshotBody::TotalValueTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "TotalValueTraded", TotalValueTraded);
    // _MdsIndexSnapshotBody::PrevCloseIdx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "PrevCloseIdx", PrevCloseIdx);
    // _MdsIndexSnapshotBody::OpenIdx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "OpenIdx", OpenIdx);
    // _MdsIndexSnapshotBody::HighIdx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "HighIdx", HighIdx);
    // _MdsIndexSnapshotBody::LowIdx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "LowIdx", LowIdx);
    // _MdsIndexSnapshotBody::LastIdx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "LastIdx", LastIdx);
    // _MdsIndexSnapshotBody::CloseIdx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "CloseIdx", CloseIdx);
    // _MdsIndexSnapshotBody::StockNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "StockNum", StockNum);
    // _MdsIndexSnapshotBody::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsIndexSnapshotBody, "__filler1", __filler1);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsIndexSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsIndexSnapshotBody", c);
}
void generate_class_MdsStockSnapshotBody(pybind11::object & parent)
{
    // _MdsStockSnapshotBody
    pybind11::class_<_MdsStockSnapshotBody> c(parent, "_MdsStockSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsStockSnapshotBody>)
        c.def(pybind11::init<>());
    // _MdsStockSnapshotBody::SecurityID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "SecurityID", SecurityID);
    // _MdsStockSnapshotBody::TradingPhaseCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TradingPhaseCode", TradingPhaseCode);
    // _MdsStockSnapshotBody::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "__filler", __filler);
    // _MdsStockSnapshotBody::NumTrades
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "NumTrades", NumTrades);
    // _MdsStockSnapshotBody::TotalVolumeTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    // _MdsStockSnapshotBody::TotalValueTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TotalValueTraded", TotalValueTraded);
    // _MdsStockSnapshotBody::PrevClosePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "PrevClosePx", PrevClosePx);
    // _MdsStockSnapshotBody::OpenPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "OpenPx", OpenPx);
    // _MdsStockSnapshotBody::HighPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "HighPx", HighPx);
    // _MdsStockSnapshotBody::LowPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "LowPx", LowPx);
    // _MdsStockSnapshotBody::TradePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TradePx", TradePx);
    // _MdsStockSnapshotBody::ClosePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "ClosePx", ClosePx);
    // _MdsStockSnapshotBody::IOPV
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "IOPV", IOPV);
    // _MdsStockSnapshotBody::NAV
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "NAV", NAV);
    // _MdsStockSnapshotBody::TotalLongPosition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "TotalLongPosition", TotalLongPosition);
    // _MdsStockSnapshotBody::BidLevels
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "BidLevels", BidLevels);
    // _MdsStockSnapshotBody::OfferLevels
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockSnapshotBody, "OfferLevels", OfferLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsStockSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsStockSnapshotBody", c);
}
void generate_class_MdsL1SnapshotBody(pybind11::object & parent)
{
    // _MdsL1SnapshotBody
    pybind11::class_<_MdsL1SnapshotBody> c(parent, "_MdsL1SnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL1SnapshotBody>)
        c.def(pybind11::init<>());
    // _MdsL1SnapshotBody::stock
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1SnapshotBody, "stock", stock);
    // _MdsL1SnapshotBody::option
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1SnapshotBody, "option", option);
    // _MdsL1SnapshotBody::index
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1SnapshotBody, "index", index);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL1SnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL1SnapshotBody", c);
}
void generate_class_MdsL1Snapshot(pybind11::object & parent)
{
    // _MdsL1Snapshot
    pybind11::class_<_MdsL1Snapshot> c(parent, "_MdsL1Snapshot");
    if constexpr (std::is_default_constructible_v<_MdsL1Snapshot>)
        c.def(pybind11::init<>());
    // _MdsL1Snapshot::head
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "head", head);
    // _MdsL1Snapshot::stock
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "stock", stock);
    // _MdsL1Snapshot::option
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "option", option);
    // _MdsL1Snapshot::index
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "index", index);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL1Snapshot, c);
    module_vnoes::objects.emplace("_MdsL1Snapshot", c);
}
void generate_class_MdsL2StockSnapshotBody(pybind11::object & parent)
{
    // _MdsL2StockSnapshotBody
    pybind11::class_<_MdsL2StockSnapshotBody> c(parent, "_MdsL2StockSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL2StockSnapshotBody>)
        c.def(pybind11::init<>());
    // _MdsL2StockSnapshotBody::SecurityID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "SecurityID", SecurityID);
    // _MdsL2StockSnapshotBody::TradingPhaseCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TradingPhaseCode", TradingPhaseCode);
    // _MdsL2StockSnapshotBody::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "__filler", __filler);
    // _MdsL2StockSnapshotBody::NumTrades
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "NumTrades", NumTrades);
    // _MdsL2StockSnapshotBody::TotalVolumeTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    // _MdsL2StockSnapshotBody::TotalValueTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalValueTraded", TotalValueTraded);
    // _MdsL2StockSnapshotBody::PrevClosePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "PrevClosePx", PrevClosePx);
    // _MdsL2StockSnapshotBody::OpenPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "OpenPx", OpenPx);
    // _MdsL2StockSnapshotBody::HighPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "HighPx", HighPx);
    // _MdsL2StockSnapshotBody::LowPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "LowPx", LowPx);
    // _MdsL2StockSnapshotBody::TradePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TradePx", TradePx);
    // _MdsL2StockSnapshotBody::ClosePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "ClosePx", ClosePx);
    // _MdsL2StockSnapshotBody::IOPV
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "IOPV", IOPV);
    // _MdsL2StockSnapshotBody::NAV
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "NAV", NAV);
    // _MdsL2StockSnapshotBody::TotalLongPosition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalLongPosition", TotalLongPosition);
    // _MdsL2StockSnapshotBody::TotalBidQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalBidQty", TotalBidQty);
    // _MdsL2StockSnapshotBody::TotalOfferQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "TotalOfferQty", TotalOfferQty);
    // _MdsL2StockSnapshotBody::WeightedAvgBidPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "WeightedAvgBidPx", WeightedAvgBidPx);
    // _MdsL2StockSnapshotBody::WeightedAvgOfferPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "WeightedAvgOfferPx", WeightedAvgOfferPx);
    // _MdsL2StockSnapshotBody::BidPriceLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "BidPriceLevel", BidPriceLevel);
    // _MdsL2StockSnapshotBody::OfferPriceLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "OfferPriceLevel", OfferPriceLevel);
    // _MdsL2StockSnapshotBody::BidLevels
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "BidLevels", BidLevels);
    // _MdsL2StockSnapshotBody::OfferLevels
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotBody, "OfferLevels", OfferLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2StockSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL2StockSnapshotBody", c);
}
void generate_class_MdsL2StockSnapshotIncremental(pybind11::object & parent)
{
    // _MdsL2StockSnapshotIncremental
    pybind11::class_<_MdsL2StockSnapshotIncremental> c(parent, "_MdsL2StockSnapshotIncremental");
    if constexpr (std::is_default_constructible_v<_MdsL2StockSnapshotIncremental>)
        c.def(pybind11::init<>());
    // _MdsL2StockSnapshotIncremental::NumTrades
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "NumTrades", NumTrades);
    // _MdsL2StockSnapshotIncremental::TotalVolumeTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalVolumeTraded", TotalVolumeTraded);
    // _MdsL2StockSnapshotIncremental::TotalValueTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalValueTraded", TotalValueTraded);
    // _MdsL2StockSnapshotIncremental::OpenPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "OpenPx", OpenPx);
    // _MdsL2StockSnapshotIncremental::TradePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TradePx", TradePx);
    // _MdsL2StockSnapshotIncremental::ClosePx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "ClosePx", ClosePx);
    // _MdsL2StockSnapshotIncremental::IOPV
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "IOPV", IOPV);
    // _MdsL2StockSnapshotIncremental::TotalBidQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalBidQty", TotalBidQty);
    // _MdsL2StockSnapshotIncremental::TotalOfferQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "TotalOfferQty", TotalOfferQty);
    // _MdsL2StockSnapshotIncremental::WeightedAvgBidPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "WeightedAvgBidPx", WeightedAvgBidPx);
    // _MdsL2StockSnapshotIncremental::WeightedAvgOfferPx
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "WeightedAvgOfferPx", WeightedAvgOfferPx);
    // _MdsL2StockSnapshotIncremental::BidPriceLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "BidPriceLevel", BidPriceLevel);
    // _MdsL2StockSnapshotIncremental::OfferPriceLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "OfferPriceLevel", OfferPriceLevel);
    // _MdsL2StockSnapshotIncremental::BestBidPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "BestBidPrice", BestBidPrice);
    // _MdsL2StockSnapshotIncremental::HasContainedBestBidLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "HasContainedBestBidLevel", HasContainedBestBidLevel);
    // _MdsL2StockSnapshotIncremental::NoBidLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "NoBidLevel", NoBidLevel);
    // _MdsL2StockSnapshotIncremental::__hasDeletedAtBidTail
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__hasDeletedAtBidTail", __hasDeletedAtBidTail);
    // _MdsL2StockSnapshotIncremental::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__filler1", __filler1);
    // _MdsL2StockSnapshotIncremental::BestOfferPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "BestOfferPrice", BestOfferPrice);
    // _MdsL2StockSnapshotIncremental::HasContainedBestOfferLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "HasContainedBestOfferLevel", HasContainedBestOfferLevel);
    // _MdsL2StockSnapshotIncremental::NoOfferLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "NoOfferLevel", NoOfferLevel);
    // _MdsL2StockSnapshotIncremental::__hasDeletedAtOfferTail
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__hasDeletedAtOfferTail", __hasDeletedAtOfferTail);
    // _MdsL2StockSnapshotIncremental::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__filler2", __filler2);
    // _MdsL2StockSnapshotIncremental::PriceLevelOperator
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "PriceLevelOperator", PriceLevelOperator);
    // _MdsL2StockSnapshotIncremental::PriceLevels
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "PriceLevels", PriceLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2StockSnapshotIncremental, c);
    module_vnoes::objects.emplace("_MdsL2StockSnapshotIncremental", c);
}
void generate_class_MdsL2BestOrdersSnapshotBody(pybind11::object & parent)
{
    // _MdsL2BestOrdersSnapshotBody
    pybind11::class_<_MdsL2BestOrdersSnapshotBody> c(parent, "_MdsL2BestOrdersSnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL2BestOrdersSnapshotBody>)
        c.def(pybind11::init<>());
    // _MdsL2BestOrdersSnapshotBody::SecurityID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "SecurityID", SecurityID);
    // _MdsL2BestOrdersSnapshotBody::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "__filler", __filler);
    // _MdsL2BestOrdersSnapshotBody::NoBidOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "NoBidOrders", NoBidOrders);
    // _MdsL2BestOrdersSnapshotBody::NoOfferOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "NoOfferOrders", NoOfferOrders);
    // _MdsL2BestOrdersSnapshotBody::TotalVolumeTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "TotalVolumeTraded", TotalVolumeTraded);
    // _MdsL2BestOrdersSnapshotBody::BestBidPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "BestBidPrice", BestBidPrice);
    // _MdsL2BestOrdersSnapshotBody::BestOfferPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "BestOfferPrice", BestOfferPrice);
    // _MdsL2BestOrdersSnapshotBody::BidOrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "BidOrderQty", BidOrderQty);
    // _MdsL2BestOrdersSnapshotBody::OfferOrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotBody, "OfferOrderQty", OfferOrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2BestOrdersSnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL2BestOrdersSnapshotBody", c);
}
void generate_class_MdsL2BestOrdersSnapshotIncremental(pybind11::object & parent)
{
    // _MdsL2BestOrdersSnapshotIncremental
    pybind11::class_<_MdsL2BestOrdersSnapshotIncremental> c(parent, "_MdsL2BestOrdersSnapshotIncremental");
    if constexpr (std::is_default_constructible_v<_MdsL2BestOrdersSnapshotIncremental>)
        c.def(pybind11::init<>());
    // _MdsL2BestOrdersSnapshotIncremental::TotalVolumeTraded
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "TotalVolumeTraded", TotalVolumeTraded);
    // _MdsL2BestOrdersSnapshotIncremental::BestBidPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "BestBidPrice", BestBidPrice);
    // _MdsL2BestOrdersSnapshotIncremental::HasContainedBestBidLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "HasContainedBestBidLevel", HasContainedBestBidLevel);
    // _MdsL2BestOrdersSnapshotIncremental::ContinualDeletedBidOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "ContinualDeletedBidOrders", ContinualDeletedBidOrders);
    // _MdsL2BestOrdersSnapshotIncremental::NoBidOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "NoBidOrders", NoBidOrders);
    // _MdsL2BestOrdersSnapshotIncremental::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "__filler1", __filler1);
    // _MdsL2BestOrdersSnapshotIncremental::BestOfferPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "BestOfferPrice", BestOfferPrice);
    // _MdsL2BestOrdersSnapshotIncremental::HasContainedBestOfferLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "HasContainedBestOfferLevel", HasContainedBestOfferLevel);
    // _MdsL2BestOrdersSnapshotIncremental::ContinualDeletedOfferOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "ContinualDeletedOfferOrders", ContinualDeletedOfferOrders);
    // _MdsL2BestOrdersSnapshotIncremental::NoOfferOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "NoOfferOrders", NoOfferOrders);
    // _MdsL2BestOrdersSnapshotIncremental::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "__filler2", __filler2);
    // _MdsL2BestOrdersSnapshotIncremental::OperatorEntryID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "OperatorEntryID", OperatorEntryID);
    // _MdsL2BestOrdersSnapshotIncremental::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2BestOrdersSnapshotIncremental, c);
    module_vnoes::objects.emplace("_MdsL2BestOrdersSnapshotIncremental", c);
}
