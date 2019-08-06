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


void generate_class_OesCustBaseInfo(pybind11::object & parent)
{
    // _OesCustBaseInfo
    pybind11::class_<_OesCustBaseInfo> c(parent, "_OesCustBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesCustBaseInfo>)
        c.def(pybind11::init<>());
    // _OesCustBaseInfo::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "custId", custId);
    // _OesCustBaseInfo::custType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "custType", custType);
    // _OesCustBaseInfo::status
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "status", status);
    // _OesCustBaseInfo::riskLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "riskLevel", riskLevel);
    // _OesCustBaseInfo::originRiskLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "originRiskLevel", originRiskLevel);
    // _OesCustBaseInfo::institutionFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "institutionFlag", institutionFlag);
    // _OesCustBaseInfo::investorClass
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "investorClass", investorClass);
    // _OesCustBaseInfo::__CUST_BASE_filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "__CUST_BASE_filler1", __CUST_BASE_filler1);
    // _OesCustBaseInfo::branchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "branchId", branchId);
    // _OesCustBaseInfo::__CUST_BASE_filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "__CUST_BASE_filler2", __CUST_BASE_filler2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCustBaseInfo, c);
    module_vnoes::objects.emplace("_OesCustBaseInfo", c);
}
void generate_class_OesInvAcctBaseInfo(pybind11::object & parent)
{
    // _OesInvAcctBaseInfo
    pybind11::class_<_OesInvAcctBaseInfo> c(parent, "_OesInvAcctBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesInvAcctBaseInfo>)
        c.def(pybind11::init<>());
    // _OesInvAcctBaseInfo::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "invAcctId", invAcctId);
    // _OesInvAcctBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "mktId", mktId);
    // _OesInvAcctBaseInfo::acctType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "acctType", acctType);
    // _OesInvAcctBaseInfo::status
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "status", status);
    // _OesInvAcctBaseInfo::ownerType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "ownerType", ownerType);
    // _OesInvAcctBaseInfo::optInvLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "optInvLevel", optInvLevel);
    // _OesInvAcctBaseInfo::isTradeDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "isTradeDisabled", isTradeDisabled);
    // _OesInvAcctBaseInfo::__INV_ACCT_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    // _OesInvAcctBaseInfo::limits
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "limits", limits);
    // _OesInvAcctBaseInfo::permissions
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "permissions", permissions);
    // _OesInvAcctBaseInfo::pbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "pbuId", pbuId);
    // _OesInvAcctBaseInfo::__INV_ACCT_BASE_filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "__INV_ACCT_BASE_filler2", __INV_ACCT_BASE_filler2);
    // _OesInvAcctBaseInfo::subscriptionQuota
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "subscriptionQuota", subscriptionQuota);
    // _OesInvAcctBaseInfo::kcSubscriptionQuota
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "kcSubscriptionQuota", kcSubscriptionQuota);
    // _OesInvAcctBaseInfo::__INV_ACCT_BASE_reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "__INV_ACCT_BASE_reserve", __INV_ACCT_BASE_reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesInvAcctBaseInfo, c);
    module_vnoes::objects.emplace("_OesInvAcctBaseInfo", c);
}
void generate_class_OesStkHoldingBaseInfo(pybind11::object & parent)
{
    // _OesStkHoldingBaseInfo
    pybind11::class_<_OesStkHoldingBaseInfo> c(parent, "_OesStkHoldingBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesStkHoldingBaseInfo>)
        c.def(pybind11::init<>());
    // _OesStkHoldingBaseInfo::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "invAcctId", invAcctId);
    // _OesStkHoldingBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "securityId", securityId);
    // _OesStkHoldingBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "mktId", mktId);
    // _OesStkHoldingBaseInfo::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "securityType", securityType);
    // _OesStkHoldingBaseInfo::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "subSecurityType", subSecurityType);
    // _OesStkHoldingBaseInfo::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "productType", productType);
    // _OesStkHoldingBaseInfo::__HOLD_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    // _OesStkHoldingBaseInfo::originalHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "originalHld", originalHld);
    // _OesStkHoldingBaseInfo::originalCostAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "originalCostAmt", originalCostAmt);
    // _OesStkHoldingBaseInfo::totalBuyHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalBuyHld", totalBuyHld);
    // _OesStkHoldingBaseInfo::totalSellHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalSellHld", totalSellHld);
    // _OesStkHoldingBaseInfo::sellFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "sellFrzHld", sellFrzHld);
    // _OesStkHoldingBaseInfo::manualFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "manualFrzHld", manualFrzHld);
    // _OesStkHoldingBaseInfo::totalBuyAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalBuyAmt", totalBuyAmt);
    // _OesStkHoldingBaseInfo::totalSellAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalSellAmt", totalSellAmt);
    // _OesStkHoldingBaseInfo::totalBuyFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalBuyFee", totalBuyFee);
    // _OesStkHoldingBaseInfo::totalSellFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalSellFee", totalSellFee);
    // _OesStkHoldingBaseInfo::totalTrsfInHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalTrsfInHld", totalTrsfInHld);
    // _OesStkHoldingBaseInfo::totalTrsfOutHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalTrsfOutHld", totalTrsfOutHld);
    // _OesStkHoldingBaseInfo::trsfOutFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "trsfOutFrzHld", trsfOutFrzHld);
    // _OesStkHoldingBaseInfo::lockHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "lockHld", lockHld);
    // _OesStkHoldingBaseInfo::lockFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "lockFrzHld", lockFrzHld);
    // _OesStkHoldingBaseInfo::unlockFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "unlockFrzHld", unlockFrzHld);
    // _OesStkHoldingBaseInfo::coveredFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "coveredFrzHld", coveredFrzHld);
    // _OesStkHoldingBaseInfo::coveredHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "coveredHld", coveredHld);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesStkHoldingBaseInfo, c);
    module_vnoes::objects.emplace("_OesStkHoldingBaseInfo", c);
}
void generate_class_OesOptHoldingBaseInfo(pybind11::object & parent)
{
    // _OesOptHoldingBaseInfo
    pybind11::class_<_OesOptHoldingBaseInfo> c(parent, "_OesOptHoldingBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesOptHoldingBaseInfo>)
        c.def(pybind11::init<>());
    // _OesOptHoldingBaseInfo::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "invAcctId", invAcctId);
    // _OesOptHoldingBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "securityId", securityId);
    // _OesOptHoldingBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "mktId", mktId);
    // _OesOptHoldingBaseInfo::__HOLD_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    // _OesOptHoldingBaseInfo::hldA
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldA", hldA);
    // _OesOptHoldingBaseInfo::hldB
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldB", hldB);
    // _OesOptHoldingBaseInfo::hldC
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldC", hldC);
    // _OesOptHoldingBaseInfo::hldC2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldC2", hldC2);
    // _OesOptHoldingBaseInfo::hldRA
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldRA", hldRA);
    // _OesOptHoldingBaseInfo::hldRB
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldRB", hldRB);
    // _OesOptHoldingBaseInfo::hldRC
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldRC", hldRC);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOptHoldingBaseInfo, c);
    module_vnoes::objects.emplace("_OesOptHoldingBaseInfo", c);
}
void generate_class_OesMarketStateInfo(pybind11::object & parent)
{
    // _OesMarketStateInfo
    pybind11::class_<_OesMarketStateInfo> c(parent, "_OesMarketStateInfo");
    if constexpr (std::is_default_constructible_v<_OesMarketStateInfo>)
        c.def(pybind11::init<>());
    // _OesMarketStateInfo::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "exchId", exchId);
    // _OesMarketStateInfo::platformId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "platformId", platformId);
    // _OesMarketStateInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "mktId", mktId);
    // _OesMarketStateInfo::mktState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "mktState", mktState);
    // _OesMarketStateInfo::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesMarketStateInfo, c);
    module_vnoes::objects.emplace("_OesMarketStateInfo", c);
}
void generate_class_OesTradingPermissionEntry(pybind11::object & parent)
{
    // _OesTradingPermissionEntry
    pybind11::class_<_OesTradingPermissionEntry> c(parent, "_OesTradingPermissionEntry");
    if constexpr (std::is_default_constructible_v<_OesTradingPermissionEntry>)
        c.def(pybind11::init<>());
    // _OesTradingPermissionEntry::permissionNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "permissionNo", permissionNo);
    // _OesTradingPermissionEntry::isDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "isDisabled", isDisabled);
    // _OesTradingPermissionEntry::counterAlias
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "counterAlias", counterAlias);
    // _OesTradingPermissionEntry::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "__filler", __filler);
    // _OesTradingPermissionEntry::permissionCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "permissionCode", permissionCode);
    // _OesTradingPermissionEntry::applicableMarkets
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "applicableMarkets", applicableMarkets);
    // _OesTradingPermissionEntry::permissionMemo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "permissionMemo", permissionMemo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTradingPermissionEntry, c);
    module_vnoes::objects.emplace("_OesTradingPermissionEntry", c);
}
void generate_class_SMsgHead(pybind11::object & parent)
{
    // _SMsgHead
    pybind11::class_<_SMsgHead> c(parent, "_SMsgHead");
    if constexpr (std::is_default_constructible_v<_SMsgHead>)
        c.def(pybind11::init<>());
    // _SMsgHead::msgFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "msgFlag", msgFlag);
    // _SMsgHead::msgId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "msgId", msgId);
    // _SMsgHead::status
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "status", status);
    // _SMsgHead::detailStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "detailStatus", detailStatus);
    // _SMsgHead::msgSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "msgSize", msgSize);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SMsgHead, c);
    module_vnoes::objects.emplace("_SMsgHead", c);
}
void generate_class_OesQryCursor(pybind11::object & parent)
{
    // _OesQryCursor
    pybind11::class_<_OesQryCursor> c(parent, "_OesQryCursor");
    if constexpr (std::is_default_constructible_v<_OesQryCursor>)
        c.def(pybind11::init<>());
    // _OesQryCursor::seqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "seqNo", seqNo);
    // _OesQryCursor::isEnd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "isEnd", isEnd);
    // _OesQryCursor::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "__filler", __filler);
    // _OesQryCursor::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCursor, c);
    module_vnoes::objects.emplace("_OesQryCursor", c);
}
void generate_class_OesQryReqHead(pybind11::object & parent)
{
    // _OesQryReqHead
    pybind11::class_<_OesQryReqHead> c(parent, "_OesQryReqHead");
    if constexpr (std::is_default_constructible_v<_OesQryReqHead>)
        c.def(pybind11::init<>());
    // _OesQryReqHead::maxPageSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqHead, "maxPageSize", maxPageSize);
    // _OesQryReqHead::lastPosition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqHead, "lastPosition", lastPosition);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryReqHead, c);
    module_vnoes::objects.emplace("_OesQryReqHead", c);
}
void generate_class_OesQryRspHead(pybind11::object & parent)
{
    // _OesQryRspHead
    pybind11::class_<_OesQryRspHead> c(parent, "_OesQryRspHead");
    if constexpr (std::is_default_constructible_v<_OesQryRspHead>)
        c.def(pybind11::init<>());
    // _OesQryRspHead::itemCount
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "itemCount", itemCount);
    // _OesQryRspHead::lastPosition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "lastPosition", lastPosition);
    // _OesQryRspHead::isEnd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "isEnd", isEnd);
    // _OesQryRspHead::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "__filler", __filler);
    // _OesQryRspHead::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryRspHead, c);
    module_vnoes::objects.emplace("_OesQryRspHead", c);
}
void generate_class_OesQryOrdFilter(pybind11::object & parent)
{
    // _OesQryOrdFilter
    pybind11::class_<_OesQryOrdFilter> c(parent, "_OesQryOrdFilter");
    if constexpr (std::is_default_constructible_v<_OesQryOrdFilter>)
        c.def(pybind11::init<>());
    // _OesQryOrdFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "custId", custId);
    // _OesQryOrdFilter::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "invAcctId", invAcctId);
    // _OesQryOrdFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "mktId", mktId);
    // _OesQryOrdFilter::isUnclosedOnly
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "isUnclosedOnly", isUnclosedOnly);
    // _OesQryOrdFilter::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "clEnvId", clEnvId);
    // _OesQryOrdFilter::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "securityType", securityType);
    // _OesQryOrdFilter::bsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "bsType", bsType);
    // _OesQryOrdFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "__filler", __filler);
    // _OesQryOrdFilter::clOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "clOrdId", clOrdId);
    // _OesQryOrdFilter::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "clSeqNo", clSeqNo);
    // _OesQryOrdFilter::startTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "startTime", startTime);
    // _OesQryOrdFilter::endTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "endTime", endTime);
    // _OesQryOrdFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOrdFilter, c);
    module_vnoes::objects.emplace("_OesQryOrdFilter", c);
}
void generate_class_OesQryOrdReq(pybind11::object & parent)
{
    // _OesQryOrdReq
    pybind11::class_<_OesQryOrdReq> c(parent, "_OesQryOrdReq");
    if constexpr (std::is_default_constructible_v<_OesQryOrdReq>)
        c.def(pybind11::init<>());
    // _OesQryOrdReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdReq, "reqHead", reqHead);
    // _OesQryOrdReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOrdReq, c);
    module_vnoes::objects.emplace("_OesQryOrdReq", c);
}
void generate_class_OesQryOrdRsp(pybind11::object & parent)
{
    // _OesQryOrdRsp
    pybind11::class_<_OesQryOrdRsp> c(parent, "_OesQryOrdRsp");
    if constexpr (std::is_default_constructible_v<_OesQryOrdRsp>)
        c.def(pybind11::init<>());
    // _OesQryOrdRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdRsp, "rspHead", rspHead);
    // _OesQryOrdRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOrdRsp, c);
    module_vnoes::objects.emplace("_OesQryOrdRsp", c);
}
void generate_class_OesQryTrdFilter(pybind11::object & parent)
{
    // _OesQryTrdFilter
    pybind11::class_<_OesQryTrdFilter> c(parent, "_OesQryTrdFilter");
    if constexpr (std::is_default_constructible_v<_OesQryTrdFilter>)
        c.def(pybind11::init<>());
    // _OesQryTrdFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "custId", custId);
    // _OesQryTrdFilter::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "invAcctId", invAcctId);
    // _OesQryTrdFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "mktId", mktId);
    // _OesQryTrdFilter::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "clEnvId", clEnvId);
    // _OesQryTrdFilter::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "securityType", securityType);
    // _OesQryTrdFilter::bsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "bsType", bsType);
    // _OesQryTrdFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "__filler", __filler);
    // _OesQryTrdFilter::clOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "clOrdId", clOrdId);
    // _OesQryTrdFilter::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "clSeqNo", clSeqNo);
    // _OesQryTrdFilter::startTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "startTime", startTime);
    // _OesQryTrdFilter::endTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "endTime", endTime);
    // _OesQryTrdFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTrdFilter, c);
    module_vnoes::objects.emplace("_OesQryTrdFilter", c);
}
void generate_class_OesQryTrdReq(pybind11::object & parent)
{
    // _OesQryTrdReq
    pybind11::class_<_OesQryTrdReq> c(parent, "_OesQryTrdReq");
    if constexpr (std::is_default_constructible_v<_OesQryTrdReq>)
        c.def(pybind11::init<>());
    // _OesQryTrdReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdReq, "reqHead", reqHead);
    // _OesQryTrdReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTrdReq, c);
    module_vnoes::objects.emplace("_OesQryTrdReq", c);
}
void generate_class_OesQryTrdRsp(pybind11::object & parent)
{
    // _OesQryTrdRsp
    pybind11::class_<_OesQryTrdRsp> c(parent, "_OesQryTrdRsp");
    if constexpr (std::is_default_constructible_v<_OesQryTrdRsp>)
        c.def(pybind11::init<>());
    // _OesQryTrdRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdRsp, "rspHead", rspHead);
    // _OesQryTrdRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTrdRsp, c);
    module_vnoes::objects.emplace("_OesQryTrdRsp", c);
}
void generate_class_OesQryCashAssetFilter(pybind11::object & parent)
{
    // _OesQryCashAssetFilter
    pybind11::class_<_OesQryCashAssetFilter> c(parent, "_OesQryCashAssetFilter");
    if constexpr (std::is_default_constructible_v<_OesQryCashAssetFilter>)
        c.def(pybind11::init<>());
    // _OesQryCashAssetFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetFilter, "custId", custId);
    // _OesQryCashAssetFilter::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetFilter, "cashAcctId", cashAcctId);
    // _OesQryCashAssetFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCashAssetFilter, c);
    module_vnoes::objects.emplace("_OesQryCashAssetFilter", c);
}
void generate_class_OesCashAssetItem(pybind11::object & parent)
{
    // _OesCashAssetItem
    pybind11::class_<_OesCashAssetItem> c(parent, "_OesCashAssetItem");
    if constexpr (std::is_default_constructible_v<_OesCashAssetItem>)
        c.def(pybind11::init<>());
    // _OesCashAssetItem::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "cashAcctId", cashAcctId);
    // _OesCashAssetItem::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "custId", custId);
    // _OesCashAssetItem::currType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currType", currType);
    // _OesCashAssetItem::cashType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "cashType", cashType);
    // _OesCashAssetItem::cashAcctStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "cashAcctStatus", cashAcctStatus);
    // _OesCashAssetItem::isFundTrsfDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "isFundTrsfDisabled", isFundTrsfDisabled);
    // _OesCashAssetItem::__CASH_ASSET_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "__CASH_ASSET_BASE_filler", __CASH_ASSET_BASE_filler);
    // _OesCashAssetItem::beginningBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "beginningBal", beginningBal);
    // _OesCashAssetItem::beginningAvailableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "beginningAvailableBal", beginningAvailableBal);
    // _OesCashAssetItem::beginningDrawableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "beginningDrawableBal", beginningDrawableBal);
    // _OesCashAssetItem::disableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "disableBal", disableBal);
    // _OesCashAssetItem::reversalAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "reversalAmt", reversalAmt);
    // _OesCashAssetItem::manualFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "manualFrzAmt", manualFrzAmt);
    // _OesCashAssetItem::totalDepositAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalDepositAmt", totalDepositAmt);
    // _OesCashAssetItem::totalWithdrawAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalWithdrawAmt", totalWithdrawAmt);
    // _OesCashAssetItem::withdrawFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "withdrawFrzAmt", withdrawFrzAmt);
    // _OesCashAssetItem::totalSellAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalSellAmt", totalSellAmt);
    // _OesCashAssetItem::totalBuyAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalBuyAmt", totalBuyAmt);
    // _OesCashAssetItem::buyFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "buyFrzAmt", buyFrzAmt);
    // _OesCashAssetItem::totalFeeAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalFeeAmt", totalFeeAmt);
    // _OesCashAssetItem::feeFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "feeFrzAmt", feeFrzAmt);
    // _OesCashAssetItem::marginAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "marginAmt", marginAmt);
    // _OesCashAssetItem::marginFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "marginFrzAmt", marginFrzAmt);
    // _OesCashAssetItem::currentTotalBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currentTotalBal", currentTotalBal);
    // _OesCashAssetItem::currentAvailableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currentAvailableBal", currentAvailableBal);
    // _OesCashAssetItem::currentDrawableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currentDrawableBal", currentDrawableBal);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCashAssetItem, c);
    module_vnoes::objects.emplace("_OesCashAssetItem", c);
}
void generate_class_OesQryCashAssetReq(pybind11::object & parent)
{
    // _OesQryCashAssetReq
    pybind11::class_<_OesQryCashAssetReq> c(parent, "_OesQryCashAssetReq");
    if constexpr (std::is_default_constructible_v<_OesQryCashAssetReq>)
        c.def(pybind11::init<>());
    // _OesQryCashAssetReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetReq, "reqHead", reqHead);
    // _OesQryCashAssetReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCashAssetReq, c);
    module_vnoes::objects.emplace("_OesQryCashAssetReq", c);
}
void generate_class_OesQryCashAssetRsp(pybind11::object & parent)
{
    // _OesQryCashAssetRsp
    pybind11::class_<_OesQryCashAssetRsp> c(parent, "_OesQryCashAssetRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCashAssetRsp>)
        c.def(pybind11::init<>());
    // _OesQryCashAssetRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetRsp, "rspHead", rspHead);
    // _OesQryCashAssetRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCashAssetRsp, c);
    module_vnoes::objects.emplace("_OesQryCashAssetRsp", c);
}
void generate_class_OesCounterCashItem(pybind11::object & parent)
{
    // _OesCounterCashItem
    pybind11::class_<_OesCounterCashItem> c(parent, "_OesCounterCashItem");
    if constexpr (std::is_default_constructible_v<_OesCounterCashItem>)
        c.def(pybind11::init<>());
    // _OesCounterCashItem::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "cashAcctId", cashAcctId);
    // _OesCounterCashItem::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "custId", custId);
    // _OesCounterCashItem::custName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "custName", custName);
    // _OesCounterCashItem::bankId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "bankId", bankId);
    // _OesCounterCashItem::cashType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "cashType", cashType);
    // _OesCounterCashItem::cashAcctStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "cashAcctStatus", cashAcctStatus);
    // _OesCounterCashItem::currType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "currType", currType);
    // _OesCounterCashItem::isFundTrsfDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "isFundTrsfDisabled", isFundTrsfDisabled);
    // _OesCounterCashItem::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "__filler", __filler);
    // _OesCounterCashItem::counterAvailableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "counterAvailableBal", counterAvailableBal);
    // _OesCounterCashItem::counterDrawableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "counterDrawableBal", counterDrawableBal);
    // _OesCounterCashItem::counterCashUpdateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "counterCashUpdateTime", counterCashUpdateTime);
    // _OesCounterCashItem::__reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCounterCashItem, c);
    module_vnoes::objects.emplace("_OesCounterCashItem", c);
}
void generate_class_OesQryCounterCashReq(pybind11::object & parent)
{
    // _OesQryCounterCashReq
    pybind11::class_<_OesQryCounterCashReq> c(parent, "_OesQryCounterCashReq");
    if constexpr (std::is_default_constructible_v<_OesQryCounterCashReq>)
        c.def(pybind11::init<>());
    // _OesQryCounterCashReq::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCounterCashReq, "cashAcctId", cashAcctId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCounterCashReq, c);
    module_vnoes::objects.emplace("_OesQryCounterCashReq", c);
}
void generate_class_OesQryCounterCashRsp(pybind11::object & parent)
{
    // _OesQryCounterCashRsp
    pybind11::class_<_OesQryCounterCashRsp> c(parent, "_OesQryCounterCashRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCounterCashRsp>)
        c.def(pybind11::init<>());
    // _OesQryCounterCashRsp::counterCashItem
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCounterCashRsp, "counterCashItem", counterCashItem);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCounterCashRsp, c);
    module_vnoes::objects.emplace("_OesQryCounterCashRsp", c);
}
void generate_class_OesQryStkHoldingFilter(pybind11::object & parent)
{
    // _OesQryStkHoldingFilter
    pybind11::class_<_OesQryStkHoldingFilter> c(parent, "_OesQryStkHoldingFilter");
    if constexpr (std::is_default_constructible_v<_OesQryStkHoldingFilter>)
        c.def(pybind11::init<>());
    // _OesQryStkHoldingFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "custId", custId);
    // _OesQryStkHoldingFilter::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "invAcctId", invAcctId);
    // _OesQryStkHoldingFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "securityId", securityId);
    // _OesQryStkHoldingFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "mktId", mktId);
    // _OesQryStkHoldingFilter::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "securityType", securityType);
    // _OesQryStkHoldingFilter::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "productType", productType);
    // _OesQryStkHoldingFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "__filler", __filler);
    // _OesQryStkHoldingFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStkHoldingFilter, c);
    module_vnoes::objects.emplace("_OesQryStkHoldingFilter", c);
}
