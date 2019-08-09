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


void generate_class_OesEtfComponentBaseInfo(pybind11::object & parent)
{
    // _OesEtfComponentBaseInfo
    pybind11::class_<_OesEtfComponentBaseInfo> c(parent, "_OesEtfComponentBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesEtfComponentBaseInfo>)
        c.def(pybind11::init<>());
    // _OesEtfComponentBaseInfo::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "fundId", fundId);
    // _OesEtfComponentBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "securityId", securityId);
    // _OesEtfComponentBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "mktId", mktId);
    // _OesEtfComponentBaseInfo::subFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "subFlag", subFlag);
    // _OesEtfComponentBaseInfo::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "securityType", securityType);
    // _OesEtfComponentBaseInfo::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "subSecurityType", subSecurityType);
    // _OesEtfComponentBaseInfo::prevClose
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "prevClose", prevClose);
    // _OesEtfComponentBaseInfo::qty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "qty", qty);
    // _OesEtfComponentBaseInfo::premiumRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "premiumRate", premiumRate);
    // _OesEtfComponentBaseInfo::creationSubCash
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "creationSubCash", creationSubCash);
    // _OesEtfComponentBaseInfo::redemptionCashSub
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "redemptionCashSub", redemptionCashSub);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesEtfComponentBaseInfo, c);
    module_vnoes::objects.emplace("_OesEtfComponentBaseInfo", c);
}
void generate_class_OesOptionBaseInfo(pybind11::object & parent)
{
    // _OesOptionBaseInfo
    pybind11::class_<_OesOptionBaseInfo> c(parent, "_OesOptionBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesOptionBaseInfo>)
        c.def(pybind11::init<>());
    // _OesOptionBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "securityId", securityId);
    // _OesOptionBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "mktId", mktId);
    // _OesOptionBaseInfo::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "securityType", securityType);
    // _OesOptionBaseInfo::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "subSecurityType", subSecurityType);
    // _OesOptionBaseInfo::contractType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "contractType", contractType);
    // _OesOptionBaseInfo::openFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "openFlag", openFlag);
    // _OesOptionBaseInfo::optionType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "optionType", optionType);
    // _OesOptionBaseInfo::suspFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "suspFlag", suspFlag);
    // _OesOptionBaseInfo::temporarySuspFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "temporarySuspFlag", temporarySuspFlag);
    // _OesOptionBaseInfo::contractMultiplierUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "contractMultiplierUnit", contractMultiplierUnit);
    // _OesOptionBaseInfo::excPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "excPrice", excPrice);
    // _OesOptionBaseInfo::startDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "startDate", startDate);
    // _OesOptionBaseInfo::endDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "endDate", endDate);
    // _OesOptionBaseInfo::execDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "execDate", execDate);
    // _OesOptionBaseInfo::expDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "expDate", expDate);
    // _OesOptionBaseInfo::closePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "closePrice", closePrice);
    // _OesOptionBaseInfo::settlPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "settlPrice", settlPrice);
    // _OesOptionBaseInfo::roundLot
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "roundLot", roundLot);
    // _OesOptionBaseInfo::tickSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "tickSize", tickSize);
    // _OesOptionBaseInfo::ceilPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "ceilPrice", ceilPrice);
    // _OesOptionBaseInfo::floorPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "floorPrice", floorPrice);
    // _OesOptionBaseInfo::marginUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "marginUnit", marginUnit);
    // _OesOptionBaseInfo::leavesQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "leavesQty", leavesQty);
    // _OesOptionBaseInfo::lmtOrdMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "lmtOrdMaxQty", lmtOrdMaxQty);
    // _OesOptionBaseInfo::lmtOrdMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "lmtOrdMinQty", lmtOrdMinQty);
    // _OesOptionBaseInfo::mktOrdMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "mktOrdMaxQty", mktOrdMaxQty);
    // _OesOptionBaseInfo::mktOrdMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "mktOrdMinQty", mktOrdMinQty);
    // _OesOptionBaseInfo::underlyingSecurityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingSecurityId", underlyingSecurityId);
    // _OesOptionBaseInfo::underlyingMktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingMktId", underlyingMktId);
    // _OesOptionBaseInfo::underlyingSecuType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingSecuType", underlyingSecuType);
    // _OesOptionBaseInfo::closeEndDateFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "closeEndDateFlag", closeEndDateFlag);
    // _OesOptionBaseInfo::__OPTION_BASE_filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "__OPTION_BASE_filler1", __OPTION_BASE_filler1);
    // _OesOptionBaseInfo::underlyingClosePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingClosePrice", underlyingClosePrice);
    // _OesOptionBaseInfo::securityName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "securityName", securityName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOptionBaseInfo, c);
    module_vnoes::objects.emplace("_OesOptionBaseInfo", c);
}
void generate_class_OesCashAssetBaseInfo(pybind11::object & parent)
{
    // _OesCashAssetBaseInfo
    pybind11::class_<_OesCashAssetBaseInfo> c(parent, "_OesCashAssetBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesCashAssetBaseInfo>)
        c.def(pybind11::init<>());
    // _OesCashAssetBaseInfo::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "cashAcctId", cashAcctId);
    // _OesCashAssetBaseInfo::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "custId", custId);
    // _OesCashAssetBaseInfo::currType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "currType", currType);
    // _OesCashAssetBaseInfo::cashType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "cashType", cashType);
    // _OesCashAssetBaseInfo::cashAcctStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "cashAcctStatus", cashAcctStatus);
    // _OesCashAssetBaseInfo::isFundTrsfDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "isFundTrsfDisabled", isFundTrsfDisabled);
    // _OesCashAssetBaseInfo::__CASH_ASSET_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "__CASH_ASSET_BASE_filler", __CASH_ASSET_BASE_filler);
    // _OesCashAssetBaseInfo::beginningBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "beginningBal", beginningBal);
    // _OesCashAssetBaseInfo::beginningAvailableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "beginningAvailableBal", beginningAvailableBal);
    // _OesCashAssetBaseInfo::beginningDrawableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "beginningDrawableBal", beginningDrawableBal);
    // _OesCashAssetBaseInfo::disableBal
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "disableBal", disableBal);
    // _OesCashAssetBaseInfo::reversalAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "reversalAmt", reversalAmt);
    // _OesCashAssetBaseInfo::manualFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "manualFrzAmt", manualFrzAmt);
    // _OesCashAssetBaseInfo::totalDepositAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalDepositAmt", totalDepositAmt);
    // _OesCashAssetBaseInfo::totalWithdrawAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalWithdrawAmt", totalWithdrawAmt);
    // _OesCashAssetBaseInfo::withdrawFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "withdrawFrzAmt", withdrawFrzAmt);
    // _OesCashAssetBaseInfo::totalSellAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalSellAmt", totalSellAmt);
    // _OesCashAssetBaseInfo::totalBuyAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalBuyAmt", totalBuyAmt);
    // _OesCashAssetBaseInfo::buyFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "buyFrzAmt", buyFrzAmt);
    // _OesCashAssetBaseInfo::totalFeeAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalFeeAmt", totalFeeAmt);
    // _OesCashAssetBaseInfo::feeFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "feeFrzAmt", feeFrzAmt);
    // _OesCashAssetBaseInfo::marginAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "marginAmt", marginAmt);
    // _OesCashAssetBaseInfo::marginFrzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "marginFrzAmt", marginFrzAmt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCashAssetBaseInfo, c);
    module_vnoes::objects.emplace("_OesCashAssetBaseInfo", c);
}
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
