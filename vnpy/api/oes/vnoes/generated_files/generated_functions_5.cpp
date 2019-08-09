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


void generate_class_OesQryEtfFilter(pybind11::object & parent)
{
    // _OesQryEtfFilter
    pybind11::class_<_OesQryEtfFilter> c(parent, "_OesQryEtfFilter");
    if constexpr (std::is_default_constructible_v<_OesQryEtfFilter>)
        c.def(pybind11::init<>());
    // _OesQryEtfFilter::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "fundId", fundId);
    // _OesQryEtfFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "mktId", mktId);
    // _OesQryEtfFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "__filler", __filler);
    // _OesQryEtfFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfFilter, c);
    module_vnoes::objects.emplace("_OesQryEtfFilter", c);
}
void generate_class_OesQryEtfReq(pybind11::object & parent)
{
    // _OesQryEtfReq
    pybind11::class_<_OesQryEtfReq> c(parent, "_OesQryEtfReq");
    if constexpr (std::is_default_constructible_v<_OesQryEtfReq>)
        c.def(pybind11::init<>());
    // _OesQryEtfReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfReq, "reqHead", reqHead);
    // _OesQryEtfReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfReq, c);
    module_vnoes::objects.emplace("_OesQryEtfReq", c);
}
void generate_class_OesQryEtfRsp(pybind11::object & parent)
{
    // _OesQryEtfRsp
    pybind11::class_<_OesQryEtfRsp> c(parent, "_OesQryEtfRsp");
    if constexpr (std::is_default_constructible_v<_OesQryEtfRsp>)
        c.def(pybind11::init<>());
    // _OesQryEtfRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfRsp, "rspHead", rspHead);
    // _OesQryEtfRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfRsp, c);
    module_vnoes::objects.emplace("_OesQryEtfRsp", c);
}
void generate_class_OesQryEtfComponentFilter(pybind11::object & parent)
{
    // _OesQryEtfComponentFilter
    pybind11::class_<_OesQryEtfComponentFilter> c(parent, "_OesQryEtfComponentFilter");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentFilter>)
        c.def(pybind11::init<>());
    // _OesQryEtfComponentFilter::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentFilter, "fundId", fundId);
    // _OesQryEtfComponentFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentFilter, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentFilter", c);
}
void generate_class_OesEtfComponentItem(pybind11::object & parent)
{
    // _OesEtfComponentItem
    pybind11::class_<_OesEtfComponentItem> c(parent, "_OesEtfComponentItem");
    if constexpr (std::is_default_constructible_v<_OesEtfComponentItem>)
        c.def(pybind11::init<>());
    // _OesEtfComponentItem::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "securityId", securityId);
    // _OesEtfComponentItem::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "mktId", mktId);
    // _OesEtfComponentItem::subFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "subFlag", subFlag);
    // _OesEtfComponentItem::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "securityType", securityType);
    // _OesEtfComponentItem::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "subSecurityType", subSecurityType);
    // _OesEtfComponentItem::prevClose
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "prevClose", prevClose);
    // _OesEtfComponentItem::qty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "qty", qty);
    // _OesEtfComponentItem::premiumRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "premiumRate", premiumRate);
    // _OesEtfComponentItem::creationSubCash
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "creationSubCash", creationSubCash);
    // _OesEtfComponentItem::redemptionCashSub
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "redemptionCashSub", redemptionCashSub);
    // _OesEtfComponentItem::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "fundId", fundId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesEtfComponentItem, c);
    module_vnoes::objects.emplace("_OesEtfComponentItem", c);
}
void generate_class_OesQryEtfComponentReq(pybind11::object & parent)
{
    // _OesQryEtfComponentReq
    pybind11::class_<_OesQryEtfComponentReq> c(parent, "_OesQryEtfComponentReq");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentReq>)
        c.def(pybind11::init<>());
    // _OesQryEtfComponentReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentReq, "reqHead", reqHead);
    // _OesQryEtfComponentReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentReq, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentReq", c);
}
void generate_class_OesQryEtfComponentRsp(pybind11::object & parent)
{
    // _OesQryEtfComponentRsp
    pybind11::class_<_OesQryEtfComponentRsp> c(parent, "_OesQryEtfComponentRsp");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentRsp>)
        c.def(pybind11::init<>());
    // _OesQryEtfComponentRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentRsp, "rspHead", rspHead);
    // _OesQryEtfComponentRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentRsp, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentRsp", c);
}
void generate_class_OesQryOptionFilter(pybind11::object & parent)
{
    // _OesQryOptionFilter
    pybind11::class_<_OesQryOptionFilter> c(parent, "_OesQryOptionFilter");
    if constexpr (std::is_default_constructible_v<_OesQryOptionFilter>)
        c.def(pybind11::init<>());
    // _OesQryOptionFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "securityId", securityId);
    // _OesQryOptionFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "mktId", mktId);
    // _OesQryOptionFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "__filler", __filler);
    // _OesQryOptionFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionFilter, c);
    module_vnoes::objects.emplace("_OesQryOptionFilter", c);
}
void generate_class_OesQryOptionReq(pybind11::object & parent)
{
    // _OesQryOptionReq
    pybind11::class_<_OesQryOptionReq> c(parent, "_OesQryOptionReq");
    if constexpr (std::is_default_constructible_v<_OesQryOptionReq>)
        c.def(pybind11::init<>());
    // _OesQryOptionReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionReq, "reqHead", reqHead);
    // _OesQryOptionReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionReq, c);
    module_vnoes::objects.emplace("_OesQryOptionReq", c);
}
void generate_class_OesQryOptionRsp(pybind11::object & parent)
{
    // _OesQryOptionRsp
    pybind11::class_<_OesQryOptionRsp> c(parent, "_OesQryOptionRsp");
    if constexpr (std::is_default_constructible_v<_OesQryOptionRsp>)
        c.def(pybind11::init<>());
    // _OesQryOptionRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionRsp, "rspHead", rspHead);
    // _OesQryOptionRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionRsp, c);
    module_vnoes::objects.emplace("_OesQryOptionRsp", c);
}
void generate_class_OesQryTradingDayRsp(pybind11::object & parent)
{
    // _OesQryTradingDayRsp
    pybind11::class_<_OesQryTradingDayRsp> c(parent, "_OesQryTradingDayRsp");
    if constexpr (std::is_default_constructible_v<_OesQryTradingDayRsp>)
        c.def(pybind11::init<>());
    // _OesQryTradingDayRsp::tradingDay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTradingDayRsp, "tradingDay", tradingDay);
    // _OesQryTradingDayRsp::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTradingDayRsp, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTradingDayRsp, c);
    module_vnoes::objects.emplace("_OesQryTradingDayRsp", c);
}
void generate_class_OesQryMarketStateFilter(pybind11::object & parent)
{
    // _OesQryMarketStateFilter
    pybind11::class_<_OesQryMarketStateFilter> c(parent, "_OesQryMarketStateFilter");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateFilter>)
        c.def(pybind11::init<>());
    // _OesQryMarketStateFilter::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "exchId", exchId);
    // _OesQryMarketStateFilter::platformId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "platformId", platformId);
    // _OesQryMarketStateFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "__filler", __filler);
    // _OesQryMarketStateFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateFilter, c);
    module_vnoes::objects.emplace("_OesQryMarketStateFilter", c);
}
void generate_class_OesQryMarketStateReq(pybind11::object & parent)
{
    // _OesQryMarketStateReq
    pybind11::class_<_OesQryMarketStateReq> c(parent, "_OesQryMarketStateReq");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateReq>)
        c.def(pybind11::init<>());
    // _OesQryMarketStateReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateReq, "reqHead", reqHead);
    // _OesQryMarketStateReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateReq, c);
    module_vnoes::objects.emplace("_OesQryMarketStateReq", c);
}
void generate_class_OesQryMarketStateRsp(pybind11::object & parent)
{
    // _OesQryMarketStateRsp
    pybind11::class_<_OesQryMarketStateRsp> c(parent, "_OesQryMarketStateRsp");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateRsp>)
        c.def(pybind11::init<>());
    // _OesQryMarketStateRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateRsp, "rspHead", rspHead);
    // _OesQryMarketStateRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateRsp, c);
    module_vnoes::objects.emplace("_OesQryMarketStateRsp", c);
}
void generate_class_OesQryReqMsg(pybind11::object & parent)
{
    // _OesQryReqMsg
    pybind11::class_<_OesQryReqMsg> c(parent, "_OesQryReqMsg");
    if constexpr (std::is_default_constructible_v<_OesQryReqMsg>)
        c.def(pybind11::init<>());
    // _OesQryReqMsg::qryOrd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOrd", qryOrd);
    // _OesQryReqMsg::qryTrd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryTrd", qryTrd);
    // _OesQryReqMsg::qryCashAsset
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCashAsset", qryCashAsset);
    // _OesQryReqMsg::qryStkHolding
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryStkHolding", qryStkHolding);
    // _OesQryReqMsg::qryOptHolding
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOptHolding", qryOptHolding);
    // _OesQryReqMsg::qryCust
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCust", qryCust);
    // _OesQryReqMsg::qryInvAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryInvAcct", qryInvAcct);
    // _OesQryReqMsg::qryComms
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryComms", qryComms);
    // _OesQryReqMsg::qryFundTrsf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryFundTrsf", qryFundTrsf);
    // _OesQryReqMsg::qryLotWinning
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryLotWinning", qryLotWinning);
    // _OesQryReqMsg::qryIssue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryIssue", qryIssue);
    // _OesQryReqMsg::qryStock
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryStock", qryStock);
    // _OesQryReqMsg::qryEtf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryEtf", qryEtf);
    // _OesQryReqMsg::qryEtfComponent
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryEtfComponent", qryEtfComponent);
    // _OesQryReqMsg::qryOption
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOption", qryOption);
    // _OesQryReqMsg::qryMktState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryMktState", qryMktState);
    // _OesQryReqMsg::qryCounterCash
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCounterCash", qryCounterCash);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryReqMsg, c);
    module_vnoes::objects.emplace("_OesQryReqMsg", c);
}
void generate_class_OesQryRspMsg(pybind11::object & parent)
{
    // _OesQryRspMsg
    pybind11::class_<_OesQryRspMsg> c(parent, "_OesQryRspMsg");
    if constexpr (std::is_default_constructible_v<_OesQryRspMsg>)
        c.def(pybind11::init<>());
    // _OesQryRspMsg::ordRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "ordRsp", ordRsp);
    // _OesQryRspMsg::trdRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "trdRsp", trdRsp);
    // _OesQryRspMsg::cashAssetRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "cashAssetRsp", cashAssetRsp);
    // _OesQryRspMsg::stkHoldingRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "stkHoldingRsp", stkHoldingRsp);
    // _OesQryRspMsg::optHoldingRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "optHoldingRsp", optHoldingRsp);
    // _OesQryRspMsg::custRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "custRsp", custRsp);
    // _OesQryRspMsg::invAcctRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "invAcctRsp", invAcctRsp);
    // _OesQryRspMsg::commsRateRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "commsRateRsp", commsRateRsp);
    // _OesQryRspMsg::fundTrsfRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "fundTrsfRsp", fundTrsfRsp);
    // _OesQryRspMsg::lotWinningRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "lotWinningRsp", lotWinningRsp);
    // _OesQryRspMsg::issueRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "issueRsp", issueRsp);
    // _OesQryRspMsg::stockRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "stockRsp", stockRsp);
    // _OesQryRspMsg::etfRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "etfRsp", etfRsp);
    // _OesQryRspMsg::etfComponentRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "etfComponentRsp", etfComponentRsp);
    // _OesQryRspMsg::optionRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "optionRsp", optionRsp);
    // _OesQryRspMsg::tradingDay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "tradingDay", tradingDay);
    // _OesQryRspMsg::mktStateRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "mktStateRsp", mktStateRsp);
    // _OesQryRspMsg::clientOverview
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "clientOverview", clientOverview);
    // _OesQryRspMsg::counterCashRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "counterCashRsp", counterCashRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryRspMsg, c);
    module_vnoes::objects.emplace("_OesQryRspMsg", c);
}
void generate_class_OesReportSynchronizationReq(pybind11::object & parent)
{
    // _OesReportSynchronizationReq
    pybind11::class_<_OesReportSynchronizationReq> c(parent, "_OesReportSynchronizationReq");
    if constexpr (std::is_default_constructible_v<_OesReportSynchronizationReq>)
        c.def(pybind11::init<>());
    // _OesReportSynchronizationReq::lastRptSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "lastRptSeqNum", lastRptSeqNum);
    // _OesReportSynchronizationReq::subscribeEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "subscribeEnvId", subscribeEnvId);
    // _OesReportSynchronizationReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "__filler", __filler);
    // _OesReportSynchronizationReq::subscribeRptTypes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReportSynchronizationReq, c);
    module_vnoes::objects.emplace("_OesReportSynchronizationReq", c);
}
void generate_class_OesReportSynchronizationRsp(pybind11::object & parent)
{
    // _OesReportSynchronizationRsp
    pybind11::class_<_OesReportSynchronizationRsp> c(parent, "_OesReportSynchronizationRsp");
    if constexpr (std::is_default_constructible_v<_OesReportSynchronizationRsp>)
        c.def(pybind11::init<>());
    // _OesReportSynchronizationRsp::lastRptSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "lastRptSeqNum", lastRptSeqNum);
    // _OesReportSynchronizationRsp::subscribeEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "subscribeEnvId", subscribeEnvId);
    // _OesReportSynchronizationRsp::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "__filler", __filler);
    // _OesReportSynchronizationRsp::subscribeRptTypes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReportSynchronizationRsp, c);
    module_vnoes::objects.emplace("_OesReportSynchronizationRsp", c);
}
void generate_class_OesTestRequestReq(pybind11::object & parent)
{
    // _OesTestRequestReq
    pybind11::class_<_OesTestRequestReq> c(parent, "_OesTestRequestReq");
    if constexpr (std::is_default_constructible_v<_OesTestRequestReq>)
        c.def(pybind11::init<>());
    // _OesTestRequestReq::testReqId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "testReqId", testReqId);
    // _OesTestRequestReq::sendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "sendTime", sendTime);
    // _OesTestRequestReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTestRequestReq, c);
    module_vnoes::objects.emplace("_OesTestRequestReq", c);
}
void generate_class_OesTestRequestRsp(pybind11::object & parent)
{
    // _OesTestRequestRsp
    pybind11::class_<_OesTestRequestRsp> c(parent, "_OesTestRequestRsp");
    if constexpr (std::is_default_constructible_v<_OesTestRequestRsp>)
        c.def(pybind11::init<>());
    // _OesTestRequestRsp::testReqId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "testReqId", testReqId);
    // _OesTestRequestRsp::origSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "origSendTime", origSendTime);
    // _OesTestRequestRsp::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__filler1", __filler1);
    // _OesTestRequestRsp::respTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "respTime", respTime);
    // _OesTestRequestRsp::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__filler2", __filler2);
    // _OesTestRequestRsp::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__recvTime", __recvTime);
    // _OesTestRequestRsp::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__collectedTime", __collectedTime);
    // _OesTestRequestRsp::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTestRequestRsp, c);
    module_vnoes::objects.emplace("_OesTestRequestRsp", c);
}
void generate_class_OesChangePasswordReq(pybind11::object & parent)
{
    // _OesChangePasswordReq
    pybind11::class_<_OesChangePasswordReq> c(parent, "_OesChangePasswordReq");
    if constexpr (std::is_default_constructible_v<_OesChangePasswordReq>)
        c.def(pybind11::init<>());
    // _OesChangePasswordReq::encryptMethod
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "encryptMethod", encryptMethod);
    // _OesChangePasswordReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "__filler", __filler);
    // _OesChangePasswordReq::username
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "username", username);
    // _OesChangePasswordReq::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "userInfo", userInfo);
    // _OesChangePasswordReq::oldPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "oldPassword", oldPassword);
    // _OesChangePasswordReq::newPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "newPassword", newPassword);
    generate_class_decltype_OesChangePasswordReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesChangePasswordReq, c);
    module_vnoes::objects.emplace("_OesChangePasswordReq", c);
}
void generate_class_decltype_OesChangePasswordReq_userInfo_(pybind11::object & parent)
{
    // decltype(_OesChangePasswordReq::userInfo)
    pybind11::class_<decltype(_OesChangePasswordReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesChangePasswordReq::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesChangePasswordReq::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "u64", u64);
    // decltype(_OesChangePasswordReq::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "i64", i64);
    // decltype(_OesChangePasswordReq::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "u32", u32);
    // decltype(_OesChangePasswordReq::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "i32", i32);
    // decltype(_OesChangePasswordReq::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesChangePasswordReq::userInfo)", c);
}
void generate_class_OesChangePasswordRsp(pybind11::object & parent)
{
    // _OesChangePasswordRsp
    pybind11::class_<_OesChangePasswordRsp> c(parent, "_OesChangePasswordRsp");
    if constexpr (std::is_default_constructible_v<_OesChangePasswordRsp>)
        c.def(pybind11::init<>());
    // _OesChangePasswordRsp::encryptMethod
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "encryptMethod", encryptMethod);
    // _OesChangePasswordRsp::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "__filler", __filler);
    // _OesChangePasswordRsp::username
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "username", username);
    // _OesChangePasswordRsp::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "userInfo", userInfo);
    // _OesChangePasswordRsp::clientId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "clientId", clientId);
    // _OesChangePasswordRsp::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "clEnvId", clEnvId);
    // _OesChangePasswordRsp::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "__filler2", __filler2);
    // _OesChangePasswordRsp::transDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "transDate", transDate);
    // _OesChangePasswordRsp::transTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "transTime", transTime);
    // _OesChangePasswordRsp::rejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "rejReason", rejReason);
    generate_class_decltype_OesChangePasswordRsp_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesChangePasswordRsp, c);
    module_vnoes::objects.emplace("_OesChangePasswordRsp", c);
}
void generate_class_decltype_OesChangePasswordRsp_userInfo_(pybind11::object & parent)
{
    // decltype(_OesChangePasswordRsp::userInfo)
    pybind11::class_<decltype(_OesChangePasswordRsp::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesChangePasswordRsp::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesChangePasswordRsp::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "u64", u64);
    // decltype(_OesChangePasswordRsp::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "i64", i64);
    // decltype(_OesChangePasswordRsp::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "u32", u32);
    // decltype(_OesChangePasswordRsp::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "i32", i32);
    // decltype(_OesChangePasswordRsp::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesChangePasswordRsp::userInfo)", c);
}
void generate_class_OesBatchOrdersHead(pybind11::object & parent)
{
    // _OesBatchOrdersHead
    pybind11::class_<_OesBatchOrdersHead> c(parent, "_OesBatchOrdersHead");
    if constexpr (std::is_default_constructible_v<_OesBatchOrdersHead>)
        c.def(pybind11::init<>());
    // _OesBatchOrdersHead::itemCount
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersHead, "itemCount", itemCount);
    // _OesBatchOrdersHead::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersHead, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesBatchOrdersHead, c);
    module_vnoes::objects.emplace("_OesBatchOrdersHead", c);
}
void generate_class_OesBatchOrdersReq(pybind11::object & parent)
{
    // _OesBatchOrdersReq
    pybind11::class_<_OesBatchOrdersReq> c(parent, "_OesBatchOrdersReq");
    if constexpr (std::is_default_constructible_v<_OesBatchOrdersReq>)
        c.def(pybind11::init<>());
    // _OesBatchOrdersReq::batchHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersReq, "batchHead", batchHead);
    // _OesBatchOrdersReq::items
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersReq, "items", items);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesBatchOrdersReq, c);
    module_vnoes::objects.emplace("_OesBatchOrdersReq", c);
}
