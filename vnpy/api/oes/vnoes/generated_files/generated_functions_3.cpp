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
