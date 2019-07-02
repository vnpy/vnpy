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
void generate_class_MdsL1Snapshot(pybind11::object & parent)
{
    pybind11::class_<_MdsL1Snapshot> c(parent, "_MdsL1Snapshot");
    if constexpr (std::is_default_constructible_v<_MdsL1Snapshot>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "head", head);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "stock", stock);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "option", option);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL1Snapshot, "index", index);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL1Snapshot, c);
    module_vnoes::objects.emplace("_MdsL1Snapshot", c);
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
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__hasDeletedAtBidTail", __hasDeletedAtBidTail);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "BestOfferPrice", BestOfferPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "HasContainedBestOfferLevel", HasContainedBestOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "NoOfferLevel", NoOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2StockSnapshotIncremental, "__hasDeletedAtOfferTail", __hasDeletedAtOfferTail);
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
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "mdProductType", mdProductType);
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
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "mdProductType", mdProductType);
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
void generate_class_MdsWholeMktMsgBody(pybind11::object & parent)
{
    pybind11::class_<_MdsWholeMktMsgBody> c(parent, "_MdsWholeMktMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsWholeMktMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "mktDataSnapshot", mktDataSnapshot);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "trade", trade);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "order", order);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "trdSessionStatus", trdSessionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "securityStatus", securityStatus);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsWholeMktMsgBody, c);
    module_vnoes::objects.emplace("_MdsWholeMktMsgBody", c);
}
void generate_class_MdsStockStaticInfo(pybind11::object & parent)
{
    pybind11::class_<_MdsStockStaticInfo> c(parent, "_MdsStockStaticInfo");
    if constexpr (std::is_default_constructible_v<_MdsStockStaticInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mdProductType", mdProductType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "oesSecurityType", oesSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "buyQtyUnit", buyQtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtBuyMaxQty", lmtBuyMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "buyOrdMaxQty", buyOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtBuyMinQty", lmtBuyMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "buyOrdMinQty", buyOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktBuyMaxQty", mktBuyMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktBuyMinQty", mktBuyMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "sellQtyUnit", sellQtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtSellMaxQty", lmtSellMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "sellOrdMaxQty", sellOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtSellMinQty", lmtSellMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "sellOrdMinQty", sellOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktSellMaxQty", mktSellMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktSellMinQty", mktSellMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "prevClose", prevClose);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "priceTick", priceTick);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "limitUpPrice", limitUpPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "limitDownPrice", limitDownPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "parPrice", parPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "bondInterest", bondInterest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "securityName", securityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsStockStaticInfo, c);
    module_vnoes::objects.emplace("_MdsStockStaticInfo", c);
}
void generate_class_MdsQryMktDataSnapshotReq(pybind11::object & parent)
{
    pybind11::class_<_MdsQryMktDataSnapshotReq> c(parent, "_MdsQryMktDataSnapshotReq");
    if constexpr (std::is_default_constructible_v<_MdsQryMktDataSnapshotReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "mdProductType", mdProductType);
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
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "mdProductType", mdProductType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryTrdSessionStatusReq, c);
    module_vnoes::objects.emplace("_MdsQryTrdSessionStatusReq", c);
}
void generate_class_MdsQryReqHeadT(pybind11::object & parent)
{
    pybind11::class_<_MdsQryReqHeadT> c(parent, "_MdsQryReqHeadT");
    if constexpr (std::is_default_constructible_v<_MdsQryReqHeadT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryReqHeadT, "maxPageSize", maxPageSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryReqHeadT, "lastPosition", lastPosition);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryReqHeadT, c);
    module_vnoes::objects.emplace("_MdsQryReqHeadT", c);
}
void generate_class_MdsQryRspHeadT(pybind11::object & parent)
{
    pybind11::class_<_MdsQryRspHeadT> c(parent, "_MdsQryRspHeadT");
    if constexpr (std::is_default_constructible_v<_MdsQryRspHeadT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "itemCount", itemCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "lastPosition", lastPosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "isEnd", isEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryRspHeadT, c);
    module_vnoes::objects.emplace("_MdsQryRspHeadT", c);
}
void generate_class_MdsQryCursor(pybind11::object & parent)
{
    pybind11::class_<_MdsQryCursor> c(parent, "_MdsQryCursor");
    if constexpr (std::is_default_constructible_v<_MdsQryCursor>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "seqNo", seqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "isEnd", isEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryCursor, c);
    module_vnoes::objects.emplace("_MdsQryCursor", c);
}
void generate_class_MdsQrySecurityCodeEntry(pybind11::object & parent)
{
    pybind11::class_<_MdsQrySecurityCodeEntry> c(parent, "_MdsQrySecurityCodeEntry");
    if constexpr (std::is_default_constructible_v<_MdsQrySecurityCodeEntry>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "mdProductType", mdProductType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySecurityCodeEntry, c);
    module_vnoes::objects.emplace("_MdsQrySecurityCodeEntry", c);
}
void generate_class_MdsQryStockStaticInfoFilter(pybind11::object & parent)
{
    pybind11::class_<_MdsQryStockStaticInfoFilter> c(parent, "_MdsQryStockStaticInfoFilter");
    if constexpr (std::is_default_constructible_v<_MdsQryStockStaticInfoFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "oesSecurityType", oesSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryStockStaticInfoFilter, c);
    module_vnoes::objects.emplace("_MdsQryStockStaticInfoFilter", c);
}
void generate_class_MdsQryStockStaticInfoReq(pybind11::object & parent)
{
    pybind11::class_<_MdsQryStockStaticInfoReq> c(parent, "_MdsQryStockStaticInfoReq");
    if constexpr (std::is_default_constructible_v<_MdsQryStockStaticInfoReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryStockStaticInfoReq, c);
    module_vnoes::objects.emplace("_MdsQryStockStaticInfoReq", c);
}
void generate_class_MdsQryStockStaticInfoRsp(pybind11::object & parent)
{
    pybind11::class_<_MdsQryStockStaticInfoRsp> c(parent, "_MdsQryStockStaticInfoRsp");
    if constexpr (std::is_default_constructible_v<_MdsQryStockStaticInfoRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryStockStaticInfoRsp, c);
    module_vnoes::objects.emplace("_MdsQryStockStaticInfoRsp", c);
}
void generate_class_MdsQrySnapshotListFilter(pybind11::object & parent)
{
    pybind11::class_<_MdsQrySnapshotListFilter> c(parent, "_MdsQrySnapshotListFilter");
    if constexpr (std::is_default_constructible_v<_MdsQrySnapshotListFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "mdProductType", mdProductType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "oesSecurityType", oesSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "mdLevel", mdLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySnapshotListFilter, c);
    module_vnoes::objects.emplace("_MdsQrySnapshotListFilter", c);
}
void generate_class_MdsQrySnapshotListReq(pybind11::object & parent)
{
    pybind11::class_<_MdsQrySnapshotListReq> c(parent, "_MdsQrySnapshotListReq");
    if constexpr (std::is_default_constructible_v<_MdsQrySnapshotListReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "qryFilter", qryFilter);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "securityCodeCnt", securityCodeCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "securityCodeList", securityCodeList);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySnapshotListReq, c);
    module_vnoes::objects.emplace("_MdsQrySnapshotListReq", c);
}
void generate_class_MdsQrySnapshotListRsp(pybind11::object & parent)
{
    pybind11::class_<_MdsQrySnapshotListRsp> c(parent, "_MdsQrySnapshotListRsp");
    if constexpr (std::is_default_constructible_v<_MdsQrySnapshotListRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySnapshotListRsp, c);
    module_vnoes::objects.emplace("_MdsQrySnapshotListRsp", c);
}
void generate_class_MdsMktDataRequestEntry(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataRequestEntry> c(parent, "_MdsMktDataRequestEntry");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestEntry>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "mdProductType", mdProductType);
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
void generate_class_MdsMktDataRequestReqBuf(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataRequestReqBuf> c(parent, "_MdsMktDataRequestReqBuf");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestReqBuf>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReqBuf, "mktDataRequestReq", mktDataRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReqBuf, "entries", entries);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestReqBuf, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestReqBuf", c);
}
void generate_class_MdsMktDataRequestRsp(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataRequestRsp> c(parent, "_MdsMktDataRequestRsp");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "subMode", subMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "tickType", tickType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "isRequireInitialMktData", isRequireInitialMktData);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "__channelNos", __channelNos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "tickExpireType", tickExpireType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "dataTypes", dataTypes);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "beginTime", beginTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "sseStockSubscribed", sseStockSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "sseIndexSubscribed", sseIndexSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "sseOptionSubscribed", sseOptionSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "szseStockSubscribed", szseStockSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "szseIndexSubscribed", szseIndexSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "szseOptionSubscribed", szseOptionSubscribed);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestRsp, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestRsp", c);
}
void generate_class_MdsTestRequestReq(pybind11::object & parent)
{
    pybind11::class_<_MdsTestRequestReq> c(parent, "_MdsTestRequestReq");
    if constexpr (std::is_default_constructible_v<_MdsTestRequestReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestReq, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestReq, "sendTime", sendTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsTestRequestReq, c);
    module_vnoes::objects.emplace("_MdsTestRequestReq", c);
}
void generate_class_MdsTestRequestRsp(pybind11::object & parent)
{
    pybind11::class_<_MdsTestRequestRsp> c(parent, "_MdsTestRequestRsp");
    if constexpr (std::is_default_constructible_v<_MdsTestRequestRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "origSendTime", origSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "respTime", respTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsTestRequestRsp, c);
    module_vnoes::objects.emplace("_MdsTestRequestRsp", c);
}
void generate_class_MdsChangePasswordReq(pybind11::object & parent)
{
    pybind11::class_<_MdsChangePasswordReq> c(parent, "_MdsChangePasswordReq");
    if constexpr (std::is_default_constructible_v<_MdsChangePasswordReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "oldPassword", oldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "newPassword", newPassword);
    generate_class_decltype_MdsChangePasswordReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsChangePasswordReq, c);
    module_vnoes::objects.emplace("_MdsChangePasswordReq", c);
}
