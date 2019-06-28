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
void generate_class_MdsMktReqMsgBody(pybind11::object & parent)
{
    pybind11::class_<_MdsMktReqMsgBody> c(parent, "_MdsMktReqMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsMktReqMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "wholeMktDataReqBuf", wholeMktDataReqBuf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "mktDataRequestReq", mktDataRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "testRequestReq", testRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "logonReq", logonReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryMktDataSnapshotReq", qryMktDataSnapshotReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qrySecurityStatusReq", qrySecurityStatusReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryTrdSessionStatusReq", qryTrdSessionStatusReq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktReqMsgBody, c);
    module_vnoes::objects.emplace("_MdsMktReqMsgBody", c);
}
void generate_class_MdsMktRspMsgBody(pybind11::object & parent)
{
    pybind11::class_<_MdsMktRspMsgBody> c(parent, "_MdsMktRspMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsMktRspMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "mktDataRequestRsp", mktDataRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "testRequestRsp", testRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "logonRsp", logonRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "mktDataSnapshot", mktDataSnapshot);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "trade", trade);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "order", order);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "tickLost", tickLost);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "trdSessionStatus", trdSessionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "securityStatus", securityStatus);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktRspMsgBody, c);
    module_vnoes::objects.emplace("_MdsMktRspMsgBody", c);
}
void generate_class_MdsUdpPktHead(pybind11::object & parent)
{
    pybind11::class_<_MdsUdpPktHead> c(parent, "_MdsUdpPktHead");
    if constexpr (std::is_default_constructible_v<_MdsUdpPktHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "msgCnt", msgCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "pktSiz", pktSiz);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "pktSeq", pktSeq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsUdpPktHead, c);
    module_vnoes::objects.emplace("_MdsUdpPktHead", c);
}
void generate_class_MdsApiClientCfg(pybind11::object & parent)
{
    pybind11::class_<_MdsApiClientCfg> c(parent, "_MdsApiClientCfg");
    if constexpr (std::is_default_constructible_v<_MdsApiClientCfg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "tcpChannelCfg", tcpChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "qryChannelCfg", qryChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpL1ChannelCfg", udpL1ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpL2ChannelCfg", udpL2ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpTradeChannelCfg", udpTradeChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpOrderChannelCfg", udpOrderChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsApiClientCfg, c);
    module_vnoes::objects.emplace("_MdsApiClientCfg", c);
}
void generate_class_MdsApiClientEnv(pybind11::object & parent)
{
    pybind11::class_<_MdsApiClientEnv> c(parent, "_MdsApiClientEnv");
    if constexpr (std::is_default_constructible_v<_MdsApiClientEnv>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "tcpChannel", tcpChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "qryChannel", qryChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpL1Channel", udpL1Channel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpL2Channel", udpL2Channel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpTradeChannel", udpTradeChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpOrderChannel", udpOrderChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpChannelGroup", udpChannelGroup);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsApiClientEnv, c);
    module_vnoes::objects.emplace("_MdsApiClientEnv", c);
}
void generate_enum_eOesExchangeId(pybind11::object & parent)
{
    pybind11::enum_<_eOesExchangeId> e(parent, "_eOesExchangeId", pybind11::arithmetic());
    e.value("OES_EXCH_UNDEFINE", _eOesExchangeId::OES_EXCH_UNDEFINE);
    e.value("OES_EXCH_SSE", _eOesExchangeId::OES_EXCH_SSE);
    e.value("OES_EXCH_SZSE", _eOesExchangeId::OES_EXCH_SZSE);
    e.value("__MAX_OES_EXCH", _eOesExchangeId::__MAX_OES_EXCH);
    e.value("OES_EXCHANGE_TYPE_SSE", _eOesExchangeId::OES_EXCHANGE_TYPE_SSE);
    e.value("OES_EXCHANGE_TYPE_SZSE", _eOesExchangeId::OES_EXCHANGE_TYPE_SZSE);
    e.export_values();
    module_vnoes::objects.emplace("_eOesExchangeId", e);
}
void generate_enum_eOesMarketId(pybind11::object & parent)
{
    pybind11::enum_<_eOesMarketId> e(parent, "_eOesMarketId", pybind11::arithmetic());
    e.value("OES_MKT_UNDEFINE", _eOesMarketId::OES_MKT_UNDEFINE);
    e.value("OES_MKT_SH_ASHARE", _eOesMarketId::OES_MKT_SH_ASHARE);
    e.value("OES_MKT_SZ_ASHARE", _eOesMarketId::OES_MKT_SZ_ASHARE);
    e.value("OES_MKT_SH_OPTION", _eOesMarketId::OES_MKT_SH_OPTION);
    e.value("__OES_MKT_ID_MAX", _eOesMarketId::__OES_MKT_ID_MAX);
    e.value("OES_MKT_ID_UNDEFINE", _eOesMarketId::OES_MKT_ID_UNDEFINE);
    e.value("OES_MKT_ID_SH_A", _eOesMarketId::OES_MKT_ID_SH_A);
    e.value("OES_MKT_ID_SZ_A", _eOesMarketId::OES_MKT_ID_SZ_A);
    e.value("OES_MKT_ID_SH_OPT", _eOesMarketId::OES_MKT_ID_SH_OPT);
    e.value("__OES_MKT_ID_MAX_ALIGNED4", _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED4);
    e.value("__OES_MKT_ID_MAX_ALIGNED8", _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMarketId", e);
}
void generate_enum_eOesPlatformId(pybind11::object & parent)
{
    pybind11::enum_<_eOesPlatformId> e(parent, "_eOesPlatformId", pybind11::arithmetic());
    e.value("OES_PLATFORM_UNDEFINE", _eOesPlatformId::OES_PLATFORM_UNDEFINE);
    e.value("OES_PLATFORM_CASH_AUCTION", _eOesPlatformId::OES_PLATFORM_CASH_AUCTION);
    e.value("OES_PLATFORM_FINANCIAL_SERVICES", _eOesPlatformId::OES_PLATFORM_FINANCIAL_SERVICES);
    e.value("OES_PLATFORM_NON_TRADE", _eOesPlatformId::OES_PLATFORM_NON_TRADE);
    e.value("OES_PLATFORM_DERIVATIVE_AUCTION", _eOesPlatformId::OES_PLATFORM_DERIVATIVE_AUCTION);
    e.value("__OES_PLATFORM_ID_MAX", _eOesPlatformId::__OES_PLATFORM_ID_MAX);
    e.value("__OES_PLATFORM_ACTIVE_MAX", _eOesPlatformId::__OES_PLATFORM_ACTIVE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesPlatformId", e);
}
void generate_enum_eOesMarketStatus(pybind11::object & parent)
{
    pybind11::enum_<_eOesMarketStatus> e(parent, "_eOesMarketStatus", pybind11::arithmetic());
    e.value("OES_MKT_STATE_UNDEFINE", _eOesMarketStatus::OES_MKT_STATE_UNDEFINE);
    e.value("OES_MKT_STATE_PRE_OPEN", _eOesMarketStatus::OES_MKT_STATE_PRE_OPEN);
    e.value("OES_MKT_STATE_OPEN_UP_COMING", _eOesMarketStatus::OES_MKT_STATE_OPEN_UP_COMING);
    e.value("OES_MKT_STATE_OPEN", _eOesMarketStatus::OES_MKT_STATE_OPEN);
    e.value("OES_MKT_STATE_HALT", _eOesMarketStatus::OES_MKT_STATE_HALT);
    e.value("OES_MKT_STATE_CLOSE", _eOesMarketStatus::OES_MKT_STATE_CLOSE);
    e.value("__OES_MKT_STATE_MAX", _eOesMarketStatus::__OES_MKT_STATE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMarketStatus", e);
}
void generate_enum_eOesTrdSessType(pybind11::object & parent)
{
    pybind11::enum_<_eOesTrdSessType> e(parent, "_eOesTrdSessType", pybind11::arithmetic());
    e.value("OES_TRD_SESS_TYPE_O", _eOesTrdSessType::OES_TRD_SESS_TYPE_O);
    e.value("OES_TRD_SESS_TYPE_T", _eOesTrdSessType::OES_TRD_SESS_TYPE_T);
    e.value("OES_TRD_SESS_TYPE_C", _eOesTrdSessType::OES_TRD_SESS_TYPE_C);
    e.value("__OES_TRD_SESS_TYPE_MAX", _eOesTrdSessType::__OES_TRD_SESS_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesTrdSessType", e);
}
void generate_enum_eOesSecurityType(pybind11::object & parent)
{
    pybind11::enum_<_eOesSecurityType> e(parent, "_eOesSecurityType", pybind11::arithmetic());
    e.value("OES_SECURITY_TYPE_UNDEFINE", _eOesSecurityType::OES_SECURITY_TYPE_UNDEFINE);
    e.value("OES_SECURITY_TYPE_STOCK", _eOesSecurityType::OES_SECURITY_TYPE_STOCK);
    e.value("OES_SECURITY_TYPE_BOND", _eOesSecurityType::OES_SECURITY_TYPE_BOND);
    e.value("OES_SECURITY_TYPE_ETF", _eOesSecurityType::OES_SECURITY_TYPE_ETF);
    e.value("OES_SECURITY_TYPE_FUND", _eOesSecurityType::OES_SECURITY_TYPE_FUND);
    e.value("OES_SECURITY_TYPE_OPTION", _eOesSecurityType::OES_SECURITY_TYPE_OPTION);
    e.value("__OES_SECURITY_TYPE_MAX", _eOesSecurityType::__OES_SECURITY_TYPE_MAX);
    e.value("__OES_SECURITY_TYPE_NOT_SUPPORT", _eOesSecurityType::__OES_SECURITY_TYPE_NOT_SUPPORT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityType", e);
}
void generate_enum_eOesSubSecurityType(pybind11::object & parent)
{
    pybind11::enum_<_eOesSubSecurityType> e(parent, "_eOesSubSecurityType", pybind11::arithmetic());
    e.value("OES_SUB_SECURITY_TYPE_UNDEFINE", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_UNDEFINE);
    e.value("__OES_SUB_SECURITY_TYPE_STOCK_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MIN);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_ASH", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_ASH);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_SME", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_SME);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_GEM", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_GEM);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_CDR", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_CDR);
    e.value("__OES_SUB_SECURITY_TYPE_STOCK_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_BOND_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MIN);
    e.value("OES_SUB_SECURITY_TYPE_BOND_GBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_GBF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_CBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CBF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_CPF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CPF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_CCF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CCF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_FBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_FBF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_PRP", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_PRP);
    e.value("OES_SUB_SECURITY_TYPE_BOND_STD", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_STD);
    e.value("__OES_SUB_SECURITY_TYPE_BOND_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_ETF_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MIN);
    e.value("OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT);
    e.value("OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT);
    e.value("OES_SUB_SECURITY_TYPE_ETF_BOND", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_BOND);
    e.value("OES_SUB_SECURITY_TYPE_ETF_CURRENCY", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CURRENCY);
    e.value("OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER);
    e.value("OES_SUB_SECURITY_TYPE_ETF_GOLD", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_GOLD);
    e.value("__OES_SUB_SECURITY_TYPE_ETF_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_FUND_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MIN);
    e.value("OES_SUB_SECURITY_TYPE_FUND_LOF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_LOF);
    e.value("OES_SUB_SECURITY_TYPE_FUND_CEF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_CEF);
    e.value("OES_SUB_SECURITY_TYPE_FUND_OEF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_OEF);
    e.value("OES_SUB_SECURITY_TYPE_FUND_GRADED", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_GRADED);
    e.value("__OES_SUB_SECURITY_TYPE_FUND_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_OPTION_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MIN);
    e.value("OES_SUB_SECURITY_TYPE_OPTION_STOCK", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_STOCK);
    e.value("OES_SUB_SECURITY_TYPE_OPTION_ETF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_ETF);
    e.value("__OES_SUB_SECURITY_TYPE_OPTION_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSubSecurityType", e);
}
void generate_enum_eOesSecurityLevel(pybind11::object & parent)
{
    pybind11::enum_<_eOesSecurityLevel> e(parent, "_eOesSecurityLevel", pybind11::arithmetic());
    e.value("OES_SECURITY_LEVEL_UNDEFINE", _eOesSecurityLevel::OES_SECURITY_LEVEL_UNDEFINE);
    e.value("OES_SECURITY_LEVEL_N", _eOesSecurityLevel::OES_SECURITY_LEVEL_N);
    e.value("OES_SECURITY_LEVEL_XST", _eOesSecurityLevel::OES_SECURITY_LEVEL_XST);
    e.value("OES_SECURITY_LEVEL_ST", _eOesSecurityLevel::OES_SECURITY_LEVEL_ST);
    e.value("OES_SECURITY_LEVEL_P", _eOesSecurityLevel::OES_SECURITY_LEVEL_P);
    e.value("OES_SECURITY_LEVEL_T", _eOesSecurityLevel::OES_SECURITY_LEVEL_T);
    e.value("OES_SECURITY_LEVEL_U", _eOesSecurityLevel::OES_SECURITY_LEVEL_U);
    e.value("OES_SECURITY_LEVEL_B", _eOesSecurityLevel::OES_SECURITY_LEVEL_B);
    e.value("__OES_SECURITY_LEVEL_MAX", _eOesSecurityLevel::__OES_SECURITY_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityLevel", e);
}
void generate_enum_eOesSecurityRiskLevel(pybind11::object & parent)
{
    pybind11::enum_<_eOesSecurityRiskLevel> e(parent, "_eOesSecurityRiskLevel", pybind11::arithmetic());
    e.value("OES_RISK_LEVEL_VERY_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_LOW);
    e.value("OES_RISK_LEVEL_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_LOW);
    e.value("OES_RISK_LEVEL_MEDIUM_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_LOW);
    e.value("OES_RISK_LEVEL_MEDIUM", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM);
    e.value("OES_RISK_LEVEL_MEDIUM_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_HIGH);
    e.value("OES_RISK_LEVEL_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_HIGH);
    e.value("OES_RISK_LEVEL_VERY_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_HIGH);
    e.value("__OES_RISK_LEVEL_MAX", _eOesSecurityRiskLevel::__OES_RISK_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityRiskLevel", e);
}
