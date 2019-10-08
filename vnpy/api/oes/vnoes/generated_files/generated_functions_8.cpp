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


void generate_class_MdsL2MarketOverview(pybind11::object & parent)
{
    // _MdsL2MarketOverview
    pybind11::class_<_MdsL2MarketOverview> c(parent, "_MdsL2MarketOverview");
    if constexpr (std::is_default_constructible_v<_MdsL2MarketOverview>)
        c.def(pybind11::init<>());
    // _MdsL2MarketOverview::OrigDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "OrigDate", OrigDate);
    // _MdsL2MarketOverview::OrigTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "OrigTime", OrigTime);
    // _MdsL2MarketOverview::__exchSendingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "__exchSendingTime", __exchSendingTime);
    // _MdsL2MarketOverview::__mdsRecvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2MarketOverview, "__mdsRecvTime", __mdsRecvTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2MarketOverview, c);
    module_vnoes::objects.emplace("_MdsL2MarketOverview", c);
}
void generate_class_MdsL2SnapshotBody(pybind11::object & parent)
{
    // _MdsL2SnapshotBody
    pybind11::class_<_MdsL2SnapshotBody> c(parent, "_MdsL2SnapshotBody");
    if constexpr (std::is_default_constructible_v<_MdsL2SnapshotBody>)
        c.def(pybind11::init<>());
    // _MdsL2SnapshotBody::l2Stock
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2Stock", l2Stock);
    // _MdsL2SnapshotBody::l2StockIncremental
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2StockIncremental", l2StockIncremental);
    // _MdsL2SnapshotBody::l2BestOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2BestOrders", l2BestOrders);
    // _MdsL2SnapshotBody::l2BestOrdersIncremental
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2BestOrdersIncremental", l2BestOrdersIncremental);
    // _MdsL2SnapshotBody::index
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "index", index);
    // _MdsL2SnapshotBody::l2MarketOverview
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2SnapshotBody, "l2MarketOverview", l2MarketOverview);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2SnapshotBody, c);
    module_vnoes::objects.emplace("_MdsL2SnapshotBody", c);
}
void generate_class_MdsMktDataSnapshot(pybind11::object & parent)
{
    // _MdsMktDataSnapshot
    pybind11::class_<_MdsMktDataSnapshot> c(parent, "_MdsMktDataSnapshot");
    if constexpr (std::is_default_constructible_v<_MdsMktDataSnapshot>)
        c.def(pybind11::init<>());
    // _MdsMktDataSnapshot::head
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "head", head);
    // _MdsMktDataSnapshot::l2Stock
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2Stock", l2Stock);
    // _MdsMktDataSnapshot::l2StockIncremental
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2StockIncremental", l2StockIncremental);
    // _MdsMktDataSnapshot::l2BestOrders
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2BestOrders", l2BestOrders);
    // _MdsMktDataSnapshot::l2BestOrdersIncremental
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2BestOrdersIncremental", l2BestOrdersIncremental);
    // _MdsMktDataSnapshot::stock
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "stock", stock);
    // _MdsMktDataSnapshot::option
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "option", option);
    // _MdsMktDataSnapshot::index
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "index", index);
    // _MdsMktDataSnapshot::l2MarketOverview
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshot, "l2MarketOverview", l2MarketOverview);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataSnapshot, c);
    module_vnoes::objects.emplace("_MdsMktDataSnapshot", c);
}
void generate_class_MdsL2Trade(pybind11::object & parent)
{
    // _MdsL2Trade
    pybind11::class_<_MdsL2Trade> c(parent, "_MdsL2Trade");
    if constexpr (std::is_default_constructible_v<_MdsL2Trade>)
        c.def(pybind11::init<>());
    // _MdsL2Trade::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "exchId", exchId);
    // _MdsL2Trade::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "mdProductType", mdProductType);
    // _MdsL2Trade::__isRepeated
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__isRepeated", __isRepeated);
    // _MdsL2Trade::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__filler1", __filler1);
    // _MdsL2Trade::tradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "tradeDate", tradeDate);
    // _MdsL2Trade::TransactTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TransactTime", TransactTime);
    // _MdsL2Trade::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "instrId", instrId);
    // _MdsL2Trade::ChannelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "ChannelNo", ChannelNo);
    // _MdsL2Trade::ApplSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "ApplSeqNum", ApplSeqNum);
    // _MdsL2Trade::SecurityID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "SecurityID", SecurityID);
    // _MdsL2Trade::ExecType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "ExecType", ExecType);
    // _MdsL2Trade::TradeBSFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradeBSFlag", TradeBSFlag);
    // _MdsL2Trade::__filler3
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__filler3", __filler3);
    // _MdsL2Trade::__channelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__channelNo", __channelNo);
    // _MdsL2Trade::__origTickSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__origTickSeq", __origTickSeq);
    // _MdsL2Trade::TradePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradePrice", TradePrice);
    // _MdsL2Trade::TradeQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradeQty", TradeQty);
    // _MdsL2Trade::TradeMoney
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "TradeMoney", TradeMoney);
    // _MdsL2Trade::BidApplSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "BidApplSeqNum", BidApplSeqNum);
    // _MdsL2Trade::OfferApplSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "OfferApplSeqNum", OfferApplSeqNum);
    // _MdsL2Trade::__origNetTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__origNetTime", __origNetTime);
    // _MdsL2Trade::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__recvTime", __recvTime);
    // _MdsL2Trade::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__collectedTime", __collectedTime);
    // _MdsL2Trade::__processedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__processedTime", __processedTime);
    // _MdsL2Trade::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Trade, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2Trade, c);
    module_vnoes::objects.emplace("_MdsL2Trade", c);
}
void generate_class_MdsL2Order(pybind11::object & parent)
{
    // _MdsL2Order
    pybind11::class_<_MdsL2Order> c(parent, "_MdsL2Order");
    if constexpr (std::is_default_constructible_v<_MdsL2Order>)
        c.def(pybind11::init<>());
    // _MdsL2Order::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "exchId", exchId);
    // _MdsL2Order::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "mdProductType", mdProductType);
    // _MdsL2Order::__isRepeated
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__isRepeated", __isRepeated);
    // _MdsL2Order::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__filler1", __filler1);
    // _MdsL2Order::tradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "tradeDate", tradeDate);
    // _MdsL2Order::TransactTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "TransactTime", TransactTime);
    // _MdsL2Order::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "instrId", instrId);
    // _MdsL2Order::ChannelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "ChannelNo", ChannelNo);
    // _MdsL2Order::ApplSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "ApplSeqNum", ApplSeqNum);
    // _MdsL2Order::SecurityID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "SecurityID", SecurityID);
    // _MdsL2Order::Side
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "Side", Side);
    // _MdsL2Order::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "OrderType", OrderType);
    // _MdsL2Order::__filler3
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__filler3", __filler3);
    // _MdsL2Order::__channelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__channelNo", __channelNo);
    // _MdsL2Order::__origTickSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__origTickSeq", __origTickSeq);
    // _MdsL2Order::Price
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "Price", Price);
    // _MdsL2Order::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "OrderQty", OrderQty);
    // _MdsL2Order::__origNetTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__origNetTime", __origNetTime);
    // _MdsL2Order::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__recvTime", __recvTime);
    // _MdsL2Order::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__collectedTime", __collectedTime);
    // _MdsL2Order::__processedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__processedTime", __processedTime);
    // _MdsL2Order::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsL2Order, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsL2Order, c);
    module_vnoes::objects.emplace("_MdsL2Order", c);
}
void generate_class_MdsWholeMktMsgBody(pybind11::object & parent)
{
    // _MdsWholeMktMsgBody
    pybind11::class_<_MdsWholeMktMsgBody> c(parent, "_MdsWholeMktMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsWholeMktMsgBody>)
        c.def(pybind11::init<>());
    // _MdsWholeMktMsgBody::mktDataSnapshot
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "mktDataSnapshot", mktDataSnapshot);
    // _MdsWholeMktMsgBody::trade
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "trade", trade);
    // _MdsWholeMktMsgBody::order
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "order", order);
    // _MdsWholeMktMsgBody::trdSessionStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "trdSessionStatus", trdSessionStatus);
    // _MdsWholeMktMsgBody::securityStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsWholeMktMsgBody, "securityStatus", securityStatus);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsWholeMktMsgBody, c);
    module_vnoes::objects.emplace("_MdsWholeMktMsgBody", c);
}
void generate_class_MdsStockStaticInfo(pybind11::object & parent)
{
    // _MdsStockStaticInfo
    pybind11::class_<_MdsStockStaticInfo> c(parent, "_MdsStockStaticInfo");
    if constexpr (std::is_default_constructible_v<_MdsStockStaticInfo>)
        c.def(pybind11::init<>());
    // _MdsStockStaticInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "securityId", securityId);
    // _MdsStockStaticInfo::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "exchId", exchId);
    // _MdsStockStaticInfo::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mdProductType", mdProductType);
    // _MdsStockStaticInfo::oesSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "oesSecurityType", oesSecurityType);
    // _MdsStockStaticInfo::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "subSecurityType", subSecurityType);
    // _MdsStockStaticInfo::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "__filler", __filler);
    // _MdsStockStaticInfo::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "instrId", instrId);
    // _MdsStockStaticInfo::buyQtyUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "buyQtyUnit", buyQtyUnit);
    // _MdsStockStaticInfo::lmtBuyMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtBuyMaxQty", lmtBuyMaxQty);
    // _MdsStockStaticInfo::buyOrdMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "buyOrdMaxQty", buyOrdMaxQty);
    // _MdsStockStaticInfo::lmtBuyMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtBuyMinQty", lmtBuyMinQty);
    // _MdsStockStaticInfo::buyOrdMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "buyOrdMinQty", buyOrdMinQty);
    // _MdsStockStaticInfo::mktBuyMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktBuyMaxQty", mktBuyMaxQty);
    // _MdsStockStaticInfo::mktBuyMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktBuyMinQty", mktBuyMinQty);
    // _MdsStockStaticInfo::sellQtyUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "sellQtyUnit", sellQtyUnit);
    // _MdsStockStaticInfo::lmtSellMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtSellMaxQty", lmtSellMaxQty);
    // _MdsStockStaticInfo::sellOrdMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "sellOrdMaxQty", sellOrdMaxQty);
    // _MdsStockStaticInfo::lmtSellMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "lmtSellMinQty", lmtSellMinQty);
    // _MdsStockStaticInfo::sellOrdMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "sellOrdMinQty", sellOrdMinQty);
    // _MdsStockStaticInfo::mktSellMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktSellMaxQty", mktSellMaxQty);
    // _MdsStockStaticInfo::mktSellMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "mktSellMinQty", mktSellMinQty);
    // _MdsStockStaticInfo::prevClose
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "prevClose", prevClose);
    // _MdsStockStaticInfo::priceTick
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "priceTick", priceTick);
    // _MdsStockStaticInfo::limitUpPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "limitUpPrice", limitUpPrice);
    // _MdsStockStaticInfo::limitDownPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "limitDownPrice", limitDownPrice);
    // _MdsStockStaticInfo::parPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "parPrice", parPrice);
    // _MdsStockStaticInfo::bondInterest
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "bondInterest", bondInterest);
    // _MdsStockStaticInfo::securityName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "securityName", securityName);
    // _MdsStockStaticInfo::__reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsStockStaticInfo, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsStockStaticInfo, c);
    module_vnoes::objects.emplace("_MdsStockStaticInfo", c);
}
void generate_class_MdsQryMktDataSnapshotReq(pybind11::object & parent)
{
    // _MdsQryMktDataSnapshotReq
    pybind11::class_<_MdsQryMktDataSnapshotReq> c(parent, "_MdsQryMktDataSnapshotReq");
    if constexpr (std::is_default_constructible_v<_MdsQryMktDataSnapshotReq>)
        c.def(pybind11::init<>());
    // _MdsQryMktDataSnapshotReq::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "exchId", exchId);
    // _MdsQryMktDataSnapshotReq::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "mdProductType", mdProductType);
    // _MdsQryMktDataSnapshotReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "__filler", __filler);
    // _MdsQryMktDataSnapshotReq::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryMktDataSnapshotReq, "instrId", instrId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryMktDataSnapshotReq, c);
    module_vnoes::objects.emplace("_MdsQryMktDataSnapshotReq", c);
}
void generate_class_MdsQryTrdSessionStatusReq(pybind11::object & parent)
{
    // _MdsQryTrdSessionStatusReq
    pybind11::class_<_MdsQryTrdSessionStatusReq> c(parent, "_MdsQryTrdSessionStatusReq");
    if constexpr (std::is_default_constructible_v<_MdsQryTrdSessionStatusReq>)
        c.def(pybind11::init<>());
    // _MdsQryTrdSessionStatusReq::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "exchId", exchId);
    // _MdsQryTrdSessionStatusReq::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "mdProductType", mdProductType);
    // _MdsQryTrdSessionStatusReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryTrdSessionStatusReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryTrdSessionStatusReq, c);
    module_vnoes::objects.emplace("_MdsQryTrdSessionStatusReq", c);
}
void generate_class_MdsQryReqHeadT(pybind11::object & parent)
{
    // _MdsQryReqHeadT
    pybind11::class_<_MdsQryReqHeadT> c(parent, "_MdsQryReqHeadT");
    if constexpr (std::is_default_constructible_v<_MdsQryReqHeadT>)
        c.def(pybind11::init<>());
    // _MdsQryReqHeadT::maxPageSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryReqHeadT, "maxPageSize", maxPageSize);
    // _MdsQryReqHeadT::lastPosition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryReqHeadT, "lastPosition", lastPosition);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryReqHeadT, c);
    module_vnoes::objects.emplace("_MdsQryReqHeadT", c);
}
void generate_class_MdsQryRspHeadT(pybind11::object & parent)
{
    // _MdsQryRspHeadT
    pybind11::class_<_MdsQryRspHeadT> c(parent, "_MdsQryRspHeadT");
    if constexpr (std::is_default_constructible_v<_MdsQryRspHeadT>)
        c.def(pybind11::init<>());
    // _MdsQryRspHeadT::itemCount
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "itemCount", itemCount);
    // _MdsQryRspHeadT::lastPosition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "lastPosition", lastPosition);
    // _MdsQryRspHeadT::isEnd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "isEnd", isEnd);
    // _MdsQryRspHeadT::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "__filler", __filler);
    // _MdsQryRspHeadT::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryRspHeadT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryRspHeadT, c);
    module_vnoes::objects.emplace("_MdsQryRspHeadT", c);
}
void generate_class_MdsQryCursor(pybind11::object & parent)
{
    // _MdsQryCursor
    pybind11::class_<_MdsQryCursor> c(parent, "_MdsQryCursor");
    if constexpr (std::is_default_constructible_v<_MdsQryCursor>)
        c.def(pybind11::init<>());
    // _MdsQryCursor::seqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "seqNo", seqNo);
    // _MdsQryCursor::isEnd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "isEnd", isEnd);
    // _MdsQryCursor::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "__filler", __filler);
    // _MdsQryCursor::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryCursor, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryCursor, c);
    module_vnoes::objects.emplace("_MdsQryCursor", c);
}
void generate_class_MdsQrySecurityCodeEntry(pybind11::object & parent)
{
    // _MdsQrySecurityCodeEntry
    pybind11::class_<_MdsQrySecurityCodeEntry> c(parent, "_MdsQrySecurityCodeEntry");
    if constexpr (std::is_default_constructible_v<_MdsQrySecurityCodeEntry>)
        c.def(pybind11::init<>());
    // _MdsQrySecurityCodeEntry::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "instrId", instrId);
    // _MdsQrySecurityCodeEntry::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "exchId", exchId);
    // _MdsQrySecurityCodeEntry::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "mdProductType", mdProductType);
    // _MdsQrySecurityCodeEntry::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySecurityCodeEntry, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySecurityCodeEntry, c);
    module_vnoes::objects.emplace("_MdsQrySecurityCodeEntry", c);
}
void generate_class_MdsQryStockStaticInfoFilter(pybind11::object & parent)
{
    // _MdsQryStockStaticInfoFilter
    pybind11::class_<_MdsQryStockStaticInfoFilter> c(parent, "_MdsQryStockStaticInfoFilter");
    if constexpr (std::is_default_constructible_v<_MdsQryStockStaticInfoFilter>)
        c.def(pybind11::init<>());
    // _MdsQryStockStaticInfoFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "securityId", securityId);
    // _MdsQryStockStaticInfoFilter::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "exchId", exchId);
    // _MdsQryStockStaticInfoFilter::oesSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "oesSecurityType", oesSecurityType);
    // _MdsQryStockStaticInfoFilter::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "subSecurityType", subSecurityType);
    // _MdsQryStockStaticInfoFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "__filler", __filler);
    // _MdsQryStockStaticInfoFilter::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "instrId", instrId);
    // _MdsQryStockStaticInfoFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryStockStaticInfoFilter, c);
    module_vnoes::objects.emplace("_MdsQryStockStaticInfoFilter", c);
}
void generate_class_MdsQryStockStaticInfoReq(pybind11::object & parent)
{
    // _MdsQryStockStaticInfoReq
    pybind11::class_<_MdsQryStockStaticInfoReq> c(parent, "_MdsQryStockStaticInfoReq");
    if constexpr (std::is_default_constructible_v<_MdsQryStockStaticInfoReq>)
        c.def(pybind11::init<>());
    // _MdsQryStockStaticInfoReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoReq, "reqHead", reqHead);
    // _MdsQryStockStaticInfoReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryStockStaticInfoReq, c);
    module_vnoes::objects.emplace("_MdsQryStockStaticInfoReq", c);
}
void generate_class_MdsQryStockStaticInfoRsp(pybind11::object & parent)
{
    // _MdsQryStockStaticInfoRsp
    pybind11::class_<_MdsQryStockStaticInfoRsp> c(parent, "_MdsQryStockStaticInfoRsp");
    if constexpr (std::is_default_constructible_v<_MdsQryStockStaticInfoRsp>)
        c.def(pybind11::init<>());
    // _MdsQryStockStaticInfoRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoRsp, "rspHead", rspHead);
    // _MdsQryStockStaticInfoRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQryStockStaticInfoRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQryStockStaticInfoRsp, c);
    module_vnoes::objects.emplace("_MdsQryStockStaticInfoRsp", c);
}
void generate_class_MdsQrySnapshotListFilter(pybind11::object & parent)
{
    // _MdsQrySnapshotListFilter
    pybind11::class_<_MdsQrySnapshotListFilter> c(parent, "_MdsQrySnapshotListFilter");
    if constexpr (std::is_default_constructible_v<_MdsQrySnapshotListFilter>)
        c.def(pybind11::init<>());
    // _MdsQrySnapshotListFilter::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "exchId", exchId);
    // _MdsQrySnapshotListFilter::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "mdProductType", mdProductType);
    // _MdsQrySnapshotListFilter::oesSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "oesSecurityType", oesSecurityType);
    // _MdsQrySnapshotListFilter::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "subSecurityType", subSecurityType);
    // _MdsQrySnapshotListFilter::mdLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "mdLevel", mdLevel);
    // _MdsQrySnapshotListFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "__filler", __filler);
    // _MdsQrySnapshotListFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySnapshotListFilter, c);
    module_vnoes::objects.emplace("_MdsQrySnapshotListFilter", c);
}
void generate_class_MdsQrySnapshotListReq(pybind11::object & parent)
{
    // _MdsQrySnapshotListReq
    pybind11::class_<_MdsQrySnapshotListReq> c(parent, "_MdsQrySnapshotListReq");
    if constexpr (std::is_default_constructible_v<_MdsQrySnapshotListReq>)
        c.def(pybind11::init<>());
    // _MdsQrySnapshotListReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "reqHead", reqHead);
    // _MdsQrySnapshotListReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "qryFilter", qryFilter);
    // _MdsQrySnapshotListReq::securityCodeCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "securityCodeCnt", securityCodeCnt);
    // _MdsQrySnapshotListReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "__filler", __filler);
    // _MdsQrySnapshotListReq::securityCodeList
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListReq, "securityCodeList", securityCodeList);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySnapshotListReq, c);
    module_vnoes::objects.emplace("_MdsQrySnapshotListReq", c);
}
void generate_class_MdsQrySnapshotListRsp(pybind11::object & parent)
{
    // _MdsQrySnapshotListRsp
    pybind11::class_<_MdsQrySnapshotListRsp> c(parent, "_MdsQrySnapshotListRsp");
    if constexpr (std::is_default_constructible_v<_MdsQrySnapshotListRsp>)
        c.def(pybind11::init<>());
    // _MdsQrySnapshotListRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListRsp, "rspHead", rspHead);
    // _MdsQrySnapshotListRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsQrySnapshotListRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsQrySnapshotListRsp, c);
    module_vnoes::objects.emplace("_MdsQrySnapshotListRsp", c);
}
void generate_class_MdsMktDataRequestEntry(pybind11::object & parent)
{
    // _MdsMktDataRequestEntry
    pybind11::class_<_MdsMktDataRequestEntry> c(parent, "_MdsMktDataRequestEntry");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestEntry>)
        c.def(pybind11::init<>());
    // _MdsMktDataRequestEntry::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "exchId", exchId);
    // _MdsMktDataRequestEntry::mdProductType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "mdProductType", mdProductType);
    // _MdsMktDataRequestEntry::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "__filler", __filler);
    // _MdsMktDataRequestEntry::instrId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestEntry, "instrId", instrId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestEntry, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestEntry", c);
}
