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


void generate_class_OesStkHoldingItem(pybind11::object & parent)
{
    // _OesStkHoldingItem
    pybind11::class_<_OesStkHoldingItem> c(parent, "_OesStkHoldingItem");
    if constexpr (std::is_default_constructible_v<_OesStkHoldingItem>)
        c.def(pybind11::init<>());
    // _OesStkHoldingItem::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "invAcctId", invAcctId);
    // _OesStkHoldingItem::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "securityId", securityId);
    // _OesStkHoldingItem::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "mktId", mktId);
    // _OesStkHoldingItem::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "securityType", securityType);
    // _OesStkHoldingItem::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "subSecurityType", subSecurityType);
    // _OesStkHoldingItem::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "productType", productType);
    // _OesStkHoldingItem::__HOLD_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    // _OesStkHoldingItem::originalHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "originalHld", originalHld);
    // _OesStkHoldingItem::originalCostAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "originalCostAmt", originalCostAmt);
    // _OesStkHoldingItem::totalBuyHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalBuyHld", totalBuyHld);
    // _OesStkHoldingItem::totalSellHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalSellHld", totalSellHld);
    // _OesStkHoldingItem::sellFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "sellFrzHld", sellFrzHld);
    // _OesStkHoldingItem::manualFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "manualFrzHld", manualFrzHld);
    // _OesStkHoldingItem::totalBuyAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalBuyAmt", totalBuyAmt);
    // _OesStkHoldingItem::totalSellAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalSellAmt", totalSellAmt);
    // _OesStkHoldingItem::totalBuyFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalBuyFee", totalBuyFee);
    // _OesStkHoldingItem::totalSellFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalSellFee", totalSellFee);
    // _OesStkHoldingItem::totalTrsfInHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalTrsfInHld", totalTrsfInHld);
    // _OesStkHoldingItem::totalTrsfOutHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalTrsfOutHld", totalTrsfOutHld);
    // _OesStkHoldingItem::trsfOutFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "trsfOutFrzHld", trsfOutFrzHld);
    // _OesStkHoldingItem::lockHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "lockHld", lockHld);
    // _OesStkHoldingItem::lockFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "lockFrzHld", lockFrzHld);
    // _OesStkHoldingItem::unlockFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "unlockFrzHld", unlockFrzHld);
    // _OesStkHoldingItem::coveredFrzHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "coveredFrzHld", coveredFrzHld);
    // _OesStkHoldingItem::coveredHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "coveredHld", coveredHld);
    // _OesStkHoldingItem::sellAvlHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "sellAvlHld", sellAvlHld);
    // _OesStkHoldingItem::trsfOutAvlHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "trsfOutAvlHld", trsfOutAvlHld);
    // _OesStkHoldingItem::lockAvlHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "lockAvlHld", lockAvlHld);
    // _OesStkHoldingItem::coveredAvlHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "coveredAvlHld", coveredAvlHld);
    // _OesStkHoldingItem::sumHld
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "sumHld", sumHld);
    // _OesStkHoldingItem::costPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "costPrice", costPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesStkHoldingItem, c);
    module_vnoes::objects.emplace("_OesStkHoldingItem", c);
}
void generate_class_OesQryStkHoldingReq(pybind11::object & parent)
{
    // _OesQryStkHoldingReq
    pybind11::class_<_OesQryStkHoldingReq> c(parent, "_OesQryStkHoldingReq");
    if constexpr (std::is_default_constructible_v<_OesQryStkHoldingReq>)
        c.def(pybind11::init<>());
    // _OesQryStkHoldingReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingReq, "reqHead", reqHead);
    // _OesQryStkHoldingReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStkHoldingReq, c);
    module_vnoes::objects.emplace("_OesQryStkHoldingReq", c);
}
void generate_class_OesQryStkHoldingRsp(pybind11::object & parent)
{
    // _OesQryStkHoldingRsp
    pybind11::class_<_OesQryStkHoldingRsp> c(parent, "_OesQryStkHoldingRsp");
    if constexpr (std::is_default_constructible_v<_OesQryStkHoldingRsp>)
        c.def(pybind11::init<>());
    // _OesQryStkHoldingRsp::qryHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingRsp, "qryHead", qryHead);
    // _OesQryStkHoldingRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStkHoldingRsp, c);
    module_vnoes::objects.emplace("_OesQryStkHoldingRsp", c);
}
void generate_class_OesOptHoldingItem(pybind11::object & parent)
{
    // _OesOptHoldingItem
    pybind11::class_<_OesOptHoldingItem> c(parent, "_OesOptHoldingItem");
    if constexpr (std::is_default_constructible_v<_OesOptHoldingItem>)
        c.def(pybind11::init<>());
    // _OesOptHoldingItem::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "invAcctId", invAcctId);
    // _OesOptHoldingItem::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "securityId", securityId);
    // _OesOptHoldingItem::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "mktId", mktId);
    // _OesOptHoldingItem::__HOLD_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    // _OesOptHoldingItem::hldA
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldA", hldA);
    // _OesOptHoldingItem::hldB
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldB", hldB);
    // _OesOptHoldingItem::hldC
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldC", hldC);
    // _OesOptHoldingItem::hldC2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldC2", hldC2);
    // _OesOptHoldingItem::hldRA
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldRA", hldRA);
    // _OesOptHoldingItem::hldRB
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldRB", hldRB);
    // _OesOptHoldingItem::hldRC
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldRC", hldRC);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOptHoldingItem, c);
    module_vnoes::objects.emplace("_OesOptHoldingItem", c);
}
void generate_class_OesQryOptHoldingReq(pybind11::object & parent)
{
    // _OesQryOptHoldingReq
    pybind11::class_<_OesQryOptHoldingReq> c(parent, "_OesQryOptHoldingReq");
    if constexpr (std::is_default_constructible_v<_OesQryOptHoldingReq>)
        c.def(pybind11::init<>());
    // _OesQryOptHoldingReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptHoldingReq, "reqHead", reqHead);
    // _OesQryOptHoldingReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptHoldingReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptHoldingReq, c);
    module_vnoes::objects.emplace("_OesQryOptHoldingReq", c);
}
void generate_class_OesQryHoldRsp(pybind11::object & parent)
{
    // _OesQryHoldRsp
    pybind11::class_<_OesQryHoldRsp> c(parent, "_OesQryHoldRsp");
    if constexpr (std::is_default_constructible_v<_OesQryHoldRsp>)
        c.def(pybind11::init<>());
    // _OesQryHoldRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryHoldRsp, "rspHead", rspHead);
    // _OesQryHoldRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryHoldRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryHoldRsp, c);
    module_vnoes::objects.emplace("_OesQryHoldRsp", c);
}
void generate_class_OesQryCustFilter(pybind11::object & parent)
{
    // _OesQryCustFilter
    pybind11::class_<_OesQryCustFilter> c(parent, "_OesQryCustFilter");
    if constexpr (std::is_default_constructible_v<_OesQryCustFilter>)
        c.def(pybind11::init<>());
    // _OesQryCustFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustFilter, "custId", custId);
    // _OesQryCustFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCustFilter, c);
    module_vnoes::objects.emplace("_OesQryCustFilter", c);
}
void generate_class_OesQryCustReq(pybind11::object & parent)
{
    // _OesQryCustReq
    pybind11::class_<_OesQryCustReq> c(parent, "_OesQryCustReq");
    if constexpr (std::is_default_constructible_v<_OesQryCustReq>)
        c.def(pybind11::init<>());
    // _OesQryCustReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustReq, "reqHead", reqHead);
    // _OesQryCustReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCustReq, c);
    module_vnoes::objects.emplace("_OesQryCustReq", c);
}
void generate_class_OesQryCustRsp(pybind11::object & parent)
{
    // _OesQryCustRsp
    pybind11::class_<_OesQryCustRsp> c(parent, "_OesQryCustRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCustRsp>)
        c.def(pybind11::init<>());
    // _OesQryCustRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustRsp, "rspHead", rspHead);
    // _OesQryCustRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCustRsp, c);
    module_vnoes::objects.emplace("_OesQryCustRsp", c);
}
void generate_class_OesQryInvAcctFilter(pybind11::object & parent)
{
    // _OesQryInvAcctFilter
    pybind11::class_<_OesQryInvAcctFilter> c(parent, "_OesQryInvAcctFilter");
    if constexpr (std::is_default_constructible_v<_OesQryInvAcctFilter>)
        c.def(pybind11::init<>());
    // _OesQryInvAcctFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "custId", custId);
    // _OesQryInvAcctFilter::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "invAcctId", invAcctId);
    // _OesQryInvAcctFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "mktId", mktId);
    // _OesQryInvAcctFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "__filler", __filler);
    // _OesQryInvAcctFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryInvAcctFilter, c);
    module_vnoes::objects.emplace("_OesQryInvAcctFilter", c);
}
void generate_class_OesInvAcctItem(pybind11::object & parent)
{
    // _OesInvAcctItem
    pybind11::class_<_OesInvAcctItem> c(parent, "_OesInvAcctItem");
    if constexpr (std::is_default_constructible_v<_OesInvAcctItem>)
        c.def(pybind11::init<>());
    // _OesInvAcctItem::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "invAcctId", invAcctId);
    // _OesInvAcctItem::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "mktId", mktId);
    // _OesInvAcctItem::acctType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "acctType", acctType);
    // _OesInvAcctItem::status
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "status", status);
    // _OesInvAcctItem::ownerType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "ownerType", ownerType);
    // _OesInvAcctItem::optInvLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "optInvLevel", optInvLevel);
    // _OesInvAcctItem::isTradeDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "isTradeDisabled", isTradeDisabled);
    // _OesInvAcctItem::__INV_ACCT_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    // _OesInvAcctItem::limits
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "limits", limits);
    // _OesInvAcctItem::permissions
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "permissions", permissions);
    // _OesInvAcctItem::pbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "pbuId", pbuId);
    // _OesInvAcctItem::__INV_ACCT_BASE_filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "__INV_ACCT_BASE_filler2", __INV_ACCT_BASE_filler2);
    // _OesInvAcctItem::subscriptionQuota
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "subscriptionQuota", subscriptionQuota);
    // _OesInvAcctItem::kcSubscriptionQuota
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "kcSubscriptionQuota", kcSubscriptionQuota);
    // _OesInvAcctItem::__INV_ACCT_BASE_reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "__INV_ACCT_BASE_reserve", __INV_ACCT_BASE_reserve);
    // _OesInvAcctItem::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "custId", custId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesInvAcctItem, c);
    module_vnoes::objects.emplace("_OesInvAcctItem", c);
}
void generate_class_OesQryInvAcctReq(pybind11::object & parent)
{
    // _OesQryInvAcctReq
    pybind11::class_<_OesQryInvAcctReq> c(parent, "_OesQryInvAcctReq");
    if constexpr (std::is_default_constructible_v<_OesQryInvAcctReq>)
        c.def(pybind11::init<>());
    // _OesQryInvAcctReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctReq, "reqHead", reqHead);
    // _OesQryInvAcctReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryInvAcctReq, c);
    module_vnoes::objects.emplace("_OesQryInvAcctReq", c);
}
void generate_class_OesQryInvAcctRsp(pybind11::object & parent)
{
    // _OesQryInvAcctRsp
    pybind11::class_<_OesQryInvAcctRsp> c(parent, "_OesQryInvAcctRsp");
    if constexpr (std::is_default_constructible_v<_OesQryInvAcctRsp>)
        c.def(pybind11::init<>());
    // _OesQryInvAcctRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctRsp, "rspHead", rspHead);
    // _OesQryInvAcctRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryInvAcctRsp, c);
    module_vnoes::objects.emplace("_OesQryInvAcctRsp", c);
}
void generate_class_OesInvAcctOverview(pybind11::object & parent)
{
    // _OesInvAcctOverview
    pybind11::class_<_OesInvAcctOverview> c(parent, "_OesInvAcctOverview");
    if constexpr (std::is_default_constructible_v<_OesInvAcctOverview>)
        c.def(pybind11::init<>());
    // _OesInvAcctOverview::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "invAcctId", invAcctId);
    // _OesInvAcctOverview::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "mktId", mktId);
    // _OesInvAcctOverview::acctType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "acctType", acctType);
    // _OesInvAcctOverview::status
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "status", status);
    // _OesInvAcctOverview::ownerType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "ownerType", ownerType);
    // _OesInvAcctOverview::optInvLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "optInvLevel", optInvLevel);
    // _OesInvAcctOverview::isTradeDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "isTradeDisabled", isTradeDisabled);
    // _OesInvAcctOverview::__INV_ACCT_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    // _OesInvAcctOverview::limits
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "limits", limits);
    // _OesInvAcctOverview::permissions
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "permissions", permissions);
    // _OesInvAcctOverview::pbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "pbuId", pbuId);
    // _OesInvAcctOverview::subscriptionQuota
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "subscriptionQuota", subscriptionQuota);
    // _OesInvAcctOverview::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "custId", custId);
    // _OesInvAcctOverview::isValid
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "isValid", isValid);
    // _OesInvAcctOverview::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "__filler", __filler);
    // _OesInvAcctOverview::kcSubscriptionQuota
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "kcSubscriptionQuota", kcSubscriptionQuota);
    // _OesInvAcctOverview::trdOrdCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "trdOrdCnt", trdOrdCnt);
    // _OesInvAcctOverview::nonTrdOrdCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "nonTrdOrdCnt", nonTrdOrdCnt);
    // _OesInvAcctOverview::cancelOrdCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "cancelOrdCnt", cancelOrdCnt);
    // _OesInvAcctOverview::oesRejectOrdCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "oesRejectOrdCnt", oesRejectOrdCnt);
    // _OesInvAcctOverview::exchRejectOrdCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "exchRejectOrdCnt", exchRejectOrdCnt);
    // _OesInvAcctOverview::trdCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "trdCnt", trdCnt);
    // _OesInvAcctOverview::__reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesInvAcctOverview, c);
    module_vnoes::objects.emplace("_OesInvAcctOverview", c);
}
void generate_class_OesCashAcctOverview(pybind11::object & parent)
{
    // _OesCashAcctOverview
    pybind11::class_<_OesCashAcctOverview> c(parent, "_OesCashAcctOverview");
    if constexpr (std::is_default_constructible_v<_OesCashAcctOverview>)
        c.def(pybind11::init<>());
    // _OesCashAcctOverview::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "cashAcctId", cashAcctId);
    // _OesCashAcctOverview::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "custId", custId);
    // _OesCashAcctOverview::bankId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "bankId", bankId);
    // _OesCashAcctOverview::isValid
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "isValid", isValid);
    // _OesCashAcctOverview::cashType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "cashType", cashType);
    // _OesCashAcctOverview::cashAcctStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "cashAcctStatus", cashAcctStatus);
    // _OesCashAcctOverview::currType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "currType", currType);
    // _OesCashAcctOverview::isFundTrsfDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "isFundTrsfDisabled", isFundTrsfDisabled);
    // _OesCashAcctOverview::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "__filler", __filler);
    // _OesCashAcctOverview::__reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCashAcctOverview, c);
    module_vnoes::objects.emplace("_OesCashAcctOverview", c);
}
void generate_class_OesCustOverview(pybind11::object & parent)
{
    // _OesCustOverview
    pybind11::class_<_OesCustOverview> c(parent, "_OesCustOverview");
    if constexpr (std::is_default_constructible_v<_OesCustOverview>)
        c.def(pybind11::init<>());
    // _OesCustOverview::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "custId", custId);
    // _OesCustOverview::custType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "custType", custType);
    // _OesCustOverview::status
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "status", status);
    // _OesCustOverview::riskLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "riskLevel", riskLevel);
    // _OesCustOverview::originRiskLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "originRiskLevel", originRiskLevel);
    // _OesCustOverview::institutionFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "institutionFlag", institutionFlag);
    // _OesCustOverview::investorClass
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "investorClass", investorClass);
    // _OesCustOverview::__CUST_BASE_filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "__CUST_BASE_filler1", __CUST_BASE_filler1);
    // _OesCustOverview::branchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "branchId", branchId);
    // _OesCustOverview::__CUST_BASE_filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "__CUST_BASE_filler2", __CUST_BASE_filler2);
    // _OesCustOverview::custName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "custName", custName);
    // _OesCustOverview::spotCashAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "spotCashAcct", spotCashAcct);
    // _OesCustOverview::creditCashAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "creditCashAcct", creditCashAcct);
    // _OesCustOverview::optionCashAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "optionCashAcct", optionCashAcct);
    // _OesCustOverview::shSpotInvAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "shSpotInvAcct", shSpotInvAcct);
    // _OesCustOverview::shOptionInvAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "shOptionInvAcct", shOptionInvAcct);
    // _OesCustOverview::szSpotInvAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "szSpotInvAcct", szSpotInvAcct);
    // _OesCustOverview::szOptionInvAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "szOptionInvAcct", szOptionInvAcct);
    // _OesCustOverview::__reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCustOverview, c);
    module_vnoes::objects.emplace("_OesCustOverview", c);
}
void generate_class_OesClientOverview(pybind11::object & parent)
{
    // _OesClientOverview
    pybind11::class_<_OesClientOverview> c(parent, "_OesClientOverview");
    if constexpr (std::is_default_constructible_v<_OesClientOverview>)
        c.def(pybind11::init<>());
    // _OesClientOverview::clientId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientId", clientId);
    // _OesClientOverview::clientType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientType", clientType);
    // _OesClientOverview::clientStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientStatus", clientStatus);
    // _OesClientOverview::isApiForbidden
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "isApiForbidden", isApiForbidden);
    // _OesClientOverview::isBlockTrader
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "isBlockTrader", isBlockTrader);
    // _OesClientOverview::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler", __filler);
    // _OesClientOverview::logonTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "logonTime", logonTime);
    // _OesClientOverview::clientName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientName", clientName);
    // _OesClientOverview::clientMemo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientMemo", clientMemo);
    // _OesClientOverview::sseStkPbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "sseStkPbuId", sseStkPbuId);
    // _OesClientOverview::sseOptPbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "sseOptPbuId", sseOptPbuId);
    // _OesClientOverview::sseQualificationClass
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "sseQualificationClass", sseQualificationClass);
    // _OesClientOverview::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler2", __filler2);
    // _OesClientOverview::szseStkPbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "szseStkPbuId", szseStkPbuId);
    // _OesClientOverview::szseOptPbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "szseOptPbuId", szseOptPbuId);
    // _OesClientOverview::szseQualificationClass
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "szseQualificationClass", szseQualificationClass);
    // _OesClientOverview::__filler3
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler3", __filler3);
    // _OesClientOverview::currOrdConnected
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "currOrdConnected", currOrdConnected);
    // _OesClientOverview::currRptConnected
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "currRptConnected", currRptConnected);
    // _OesClientOverview::currQryConnected
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "currQryConnected", currQryConnected);
    // _OesClientOverview::maxOrdConnect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "maxOrdConnect", maxOrdConnect);
    // _OesClientOverview::maxRptConnect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "maxRptConnect", maxRptConnect);
    // _OesClientOverview::maxQryConnect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "maxQryConnect", maxQryConnect);
    // _OesClientOverview::ordTrafficLimit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "ordTrafficLimit", ordTrafficLimit);
    // _OesClientOverview::qryTrafficLimit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "qryTrafficLimit", qryTrafficLimit);
    // _OesClientOverview::__reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__reserve", __reserve);
    // _OesClientOverview::associatedCustCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "associatedCustCnt", associatedCustCnt);
    // _OesClientOverview::__filler4
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler4", __filler4);
    // _OesClientOverview::custItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "custItems", custItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesClientOverview, c);
    module_vnoes::objects.emplace("_OesClientOverview", c);
}
void generate_class_OesQryCommissionRateFilter(pybind11::object & parent)
{
    // _OesQryCommissionRateFilter
    pybind11::class_<_OesQryCommissionRateFilter> c(parent, "_OesQryCommissionRateFilter");
    if constexpr (std::is_default_constructible_v<_OesQryCommissionRateFilter>)
        c.def(pybind11::init<>());
    // _OesQryCommissionRateFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "custId", custId);
    // _OesQryCommissionRateFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "mktId", mktId);
    // _OesQryCommissionRateFilter::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "securityType", securityType);
    // _OesQryCommissionRateFilter::bsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "bsType", bsType);
    // _OesQryCommissionRateFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "__filler", __filler);
    // _OesQryCommissionRateFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCommissionRateFilter, c);
    module_vnoes::objects.emplace("_OesQryCommissionRateFilter", c);
}
void generate_class_OesCommissionRateItem(pybind11::object & parent)
{
    // _OesCommissionRateItem
    pybind11::class_<_OesCommissionRateItem> c(parent, "_OesCommissionRateItem");
    if constexpr (std::is_default_constructible_v<_OesCommissionRateItem>)
        c.def(pybind11::init<>());
    // _OesCommissionRateItem::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "custId", custId);
    // _OesCommissionRateItem::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "securityId", securityId);
    // _OesCommissionRateItem::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "mktId", mktId);
    // _OesCommissionRateItem::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "securityType", securityType);
    // _OesCommissionRateItem::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "subSecurityType", subSecurityType);
    // _OesCommissionRateItem::bsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "bsType", bsType);
    // _OesCommissionRateItem::feeType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "feeType", feeType);
    // _OesCommissionRateItem::currType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "currType", currType);
    // _OesCommissionRateItem::calcFeeMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "calcFeeMode", calcFeeMode);
    // _OesCommissionRateItem::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "__filler", __filler);
    // _OesCommissionRateItem::feeRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "feeRate", feeRate);
    // _OesCommissionRateItem::minFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "minFee", minFee);
    // _OesCommissionRateItem::maxFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "maxFee", maxFee);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCommissionRateItem, c);
    module_vnoes::objects.emplace("_OesCommissionRateItem", c);
}
void generate_class_OesQryCommissionRateReq(pybind11::object & parent)
{
    // _OesQryCommissionRateReq
    pybind11::class_<_OesQryCommissionRateReq> c(parent, "_OesQryCommissionRateReq");
    if constexpr (std::is_default_constructible_v<_OesQryCommissionRateReq>)
        c.def(pybind11::init<>());
    // _OesQryCommissionRateReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateReq, "reqHead", reqHead);
    // _OesQryCommissionRateReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCommissionRateReq, c);
    module_vnoes::objects.emplace("_OesQryCommissionRateReq", c);
}
void generate_class_OesQryCommissionRateRsp(pybind11::object & parent)
{
    // _OesQryCommissionRateRsp
    pybind11::class_<_OesQryCommissionRateRsp> c(parent, "_OesQryCommissionRateRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCommissionRateRsp>)
        c.def(pybind11::init<>());
    // _OesQryCommissionRateRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateRsp, "rspHead", rspHead);
    // _OesQryCommissionRateRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCommissionRateRsp, c);
    module_vnoes::objects.emplace("_OesQryCommissionRateRsp", c);
}
