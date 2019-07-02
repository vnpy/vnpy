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


void generate_class_OesEtfBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesEtfBaseInfo> c(parent, "_OesEtfBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesEtfBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isPublishIOPV", isPublishIOPV);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isCreationAble", isCreationAble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isRedemptionAble", isRedemptionAble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isDisabled", isDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "__ETF_BASE_filler", __ETF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "componentCnt", componentCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "creRdmUnit", creRdmUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "maxCashRatio", maxCashRatio);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "nav", nav);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "navPerCU", navPerCU);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "dividendPerCU", dividendPerCU);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "tradingDay", tradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "preTradingDay", preTradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "estiCashCmpoent", estiCashCmpoent);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "cashCmpoent", cashCmpoent);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "creationLimit", creationLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "redemLimit", redemLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "netCreationLimit", netCreationLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "netRedemLimit", netRedemLimit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesEtfBaseInfo, c);
    module_vnoes::objects.emplace("_OesEtfBaseInfo", c);
}
void generate_class_OesEtfComponentBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesEtfComponentBaseInfo> c(parent, "_OesEtfComponentBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesEtfComponentBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "subFlag", subFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "prevClose", prevClose);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "premiumRate", premiumRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "creationSubCash", creationSubCash);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentBaseInfo, "redemptionCashSub", redemptionCashSub);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesEtfComponentBaseInfo, c);
    module_vnoes::objects.emplace("_OesEtfComponentBaseInfo", c);
}
void generate_class_OesOptionBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesOptionBaseInfo> c(parent, "_OesOptionBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesOptionBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "contractType", contractType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "openFlag", openFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "optionType", optionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "suspFlag", suspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "temporarySuspFlag", temporarySuspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "contractMultiplierUnit", contractMultiplierUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "excPrice", excPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "startDate", startDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "endDate", endDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "execDate", execDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "expDate", expDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "closePrice", closePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "settlPrice", settlPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "roundLot", roundLot);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "tickSize", tickSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "ceilPrice", ceilPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "floorPrice", floorPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "marginUnit", marginUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "leavesQty", leavesQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "lmtOrdMaxQty", lmtOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "lmtOrdMinQty", lmtOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "mktOrdMaxQty", mktOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "mktOrdMinQty", mktOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingSecurityId", underlyingSecurityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingMktId", underlyingMktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingSecuType", underlyingSecuType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "closeEndDateFlag", closeEndDateFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "__OPTION_BASE_filler1", __OPTION_BASE_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "underlyingClosePrice", underlyingClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptionBaseInfo, "securityName", securityName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOptionBaseInfo, c);
    module_vnoes::objects.emplace("_OesOptionBaseInfo", c);
}
void generate_class_OesCashAssetBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesCashAssetBaseInfo> c(parent, "_OesCashAssetBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesCashAssetBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "__CASH_ASSET_BASE_filler", __CASH_ASSET_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "beginningBal", beginningBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "beginningAvailableBal", beginningAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "beginningDrawableBal", beginningDrawableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "disableBal", disableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "reversalAmt", reversalAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "manualFrzAmt", manualFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalDepositAmt", totalDepositAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalWithdrawAmt", totalWithdrawAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "withdrawFrzAmt", withdrawFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "buyFrzAmt", buyFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "totalFeeAmt", totalFeeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "feeFrzAmt", feeFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "marginAmt", marginAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetBaseInfo, "marginFrzAmt", marginFrzAmt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCashAssetBaseInfo, c);
    module_vnoes::objects.emplace("_OesCashAssetBaseInfo", c);
}
void generate_class_OesCustBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesCustBaseInfo> c(parent, "_OesCustBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesCustBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "custType", custType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "riskLevel", riskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "originRiskLevel", originRiskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "institutionFlag", institutionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "investorClass", investorClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "__CUST_BASE_filler1", __CUST_BASE_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustBaseInfo, "__CUST_BASE_filler2", __CUST_BASE_filler2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCustBaseInfo, c);
    module_vnoes::objects.emplace("_OesCustBaseInfo", c);
}
void generate_class_OesInvAcctBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesInvAcctBaseInfo> c(parent, "_OesInvAcctBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesInvAcctBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "acctType", acctType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "ownerType", ownerType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "optInvLevel", optInvLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "isTradeDisabled", isTradeDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "limits", limits);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "permissions", permissions);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "__INV_ACCT_BASE_filler2", __INV_ACCT_BASE_filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "subscriptionQuota", subscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "kcSubscriptionQuota", kcSubscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctBaseInfo, "__INV_ACCT_BASE_reserve", __INV_ACCT_BASE_reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesInvAcctBaseInfo, c);
    module_vnoes::objects.emplace("_OesInvAcctBaseInfo", c);
}
void generate_class_OesStkHoldingBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesStkHoldingBaseInfo> c(parent, "_OesStkHoldingBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesStkHoldingBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "originalHld", originalHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "originalCostAmt", originalCostAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalBuyHld", totalBuyHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalSellHld", totalSellHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "sellFrzHld", sellFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "manualFrzHld", manualFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalBuyFee", totalBuyFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalSellFee", totalSellFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalTrsfInHld", totalTrsfInHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "totalTrsfOutHld", totalTrsfOutHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "trsfOutFrzHld", trsfOutFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "lockHld", lockHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "lockFrzHld", lockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "unlockFrzHld", unlockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "coveredFrzHld", coveredFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingBaseInfo, "coveredHld", coveredHld);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesStkHoldingBaseInfo, c);
    module_vnoes::objects.emplace("_OesStkHoldingBaseInfo", c);
}
void generate_class_OesOptHoldingBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesOptHoldingBaseInfo> c(parent, "_OesOptHoldingBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesOptHoldingBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldA", hldA);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldB", hldB);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldC", hldC);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldC2", hldC2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldRA", hldRA);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldRB", hldRB);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingBaseInfo, "hldRC", hldRC);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOptHoldingBaseInfo, c);
    module_vnoes::objects.emplace("_OesOptHoldingBaseInfo", c);
}
void generate_class_OesMarketStateInfo(pybind11::object & parent)
{
    pybind11::class_<_OesMarketStateInfo> c(parent, "_OesMarketStateInfo");
    if constexpr (std::is_default_constructible_v<_OesMarketStateInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "platformId", platformId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "mktState", mktState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesMarketStateInfo, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesMarketStateInfo, c);
    module_vnoes::objects.emplace("_OesMarketStateInfo", c);
}
void generate_class_OesTradingPermissionEntry(pybind11::object & parent)
{
    pybind11::class_<_OesTradingPermissionEntry> c(parent, "_OesTradingPermissionEntry");
    if constexpr (std::is_default_constructible_v<_OesTradingPermissionEntry>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "permissionNo", permissionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "isDisabled", isDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "counterAlias", counterAlias);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "permissionCode", permissionCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "applicableMarkets", applicableMarkets);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTradingPermissionEntry, "permissionMemo", permissionMemo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTradingPermissionEntry, c);
    module_vnoes::objects.emplace("_OesTradingPermissionEntry", c);
}
void generate_class_SMsgHead(pybind11::object & parent)
{
    pybind11::class_<_SMsgHead> c(parent, "_SMsgHead");
    if constexpr (std::is_default_constructible_v<_SMsgHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "msgFlag", msgFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "msgId", msgId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "detailStatus", detailStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SMsgHead, "msgSize", msgSize);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SMsgHead, c);
    module_vnoes::objects.emplace("_SMsgHead", c);
}
void generate_class_OesQryCursor(pybind11::object & parent)
{
    pybind11::class_<_OesQryCursor> c(parent, "_OesQryCursor");
    if constexpr (std::is_default_constructible_v<_OesQryCursor>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "seqNo", seqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "isEnd", isEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCursor, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCursor, c);
    module_vnoes::objects.emplace("_OesQryCursor", c);
}
void generate_class_OesQryReqHead(pybind11::object & parent)
{
    pybind11::class_<_OesQryReqHead> c(parent, "_OesQryReqHead");
    if constexpr (std::is_default_constructible_v<_OesQryReqHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqHead, "maxPageSize", maxPageSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqHead, "lastPosition", lastPosition);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryReqHead, c);
    module_vnoes::objects.emplace("_OesQryReqHead", c);
}
void generate_class_OesQryRspHead(pybind11::object & parent)
{
    pybind11::class_<_OesQryRspHead> c(parent, "_OesQryRspHead");
    if constexpr (std::is_default_constructible_v<_OesQryRspHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "itemCount", itemCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "lastPosition", lastPosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "isEnd", isEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspHead, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryRspHead, c);
    module_vnoes::objects.emplace("_OesQryRspHead", c);
}
void generate_class_OesQryOrdFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryOrdFilter> c(parent, "_OesQryOrdFilter");
    if constexpr (std::is_default_constructible_v<_OesQryOrdFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "isUnclosedOnly", isUnclosedOnly);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "startTime", startTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "endTime", endTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOrdFilter, c);
    module_vnoes::objects.emplace("_OesQryOrdFilter", c);
}
void generate_class_OesQryOrdReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryOrdReq> c(parent, "_OesQryOrdReq");
    if constexpr (std::is_default_constructible_v<_OesQryOrdReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOrdReq, c);
    module_vnoes::objects.emplace("_OesQryOrdReq", c);
}
void generate_class_OesQryOrdRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryOrdRsp> c(parent, "_OesQryOrdRsp");
    if constexpr (std::is_default_constructible_v<_OesQryOrdRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOrdRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOrdRsp, c);
    module_vnoes::objects.emplace("_OesQryOrdRsp", c);
}
void generate_class_OesQryTrdFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryTrdFilter> c(parent, "_OesQryTrdFilter");
    if constexpr (std::is_default_constructible_v<_OesQryTrdFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "startTime", startTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "endTime", endTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTrdFilter, c);
    module_vnoes::objects.emplace("_OesQryTrdFilter", c);
}
void generate_class_OesQryTrdReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryTrdReq> c(parent, "_OesQryTrdReq");
    if constexpr (std::is_default_constructible_v<_OesQryTrdReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTrdReq, c);
    module_vnoes::objects.emplace("_OesQryTrdReq", c);
}
void generate_class_OesQryTrdRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryTrdRsp> c(parent, "_OesQryTrdRsp");
    if constexpr (std::is_default_constructible_v<_OesQryTrdRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTrdRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTrdRsp, c);
    module_vnoes::objects.emplace("_OesQryTrdRsp", c);
}
void generate_class_OesQryCashAssetFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryCashAssetFilter> c(parent, "_OesQryCashAssetFilter");
    if constexpr (std::is_default_constructible_v<_OesQryCashAssetFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetFilter, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCashAssetFilter, c);
    module_vnoes::objects.emplace("_OesQryCashAssetFilter", c);
}
void generate_class_OesCashAssetItem(pybind11::object & parent)
{
    pybind11::class_<_OesCashAssetItem> c(parent, "_OesCashAssetItem");
    if constexpr (std::is_default_constructible_v<_OesCashAssetItem>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "__CASH_ASSET_BASE_filler", __CASH_ASSET_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "beginningBal", beginningBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "beginningAvailableBal", beginningAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "beginningDrawableBal", beginningDrawableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "disableBal", disableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "reversalAmt", reversalAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "manualFrzAmt", manualFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalDepositAmt", totalDepositAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalWithdrawAmt", totalWithdrawAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "withdrawFrzAmt", withdrawFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "buyFrzAmt", buyFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "totalFeeAmt", totalFeeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "feeFrzAmt", feeFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "marginAmt", marginAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "marginFrzAmt", marginFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currentTotalBal", currentTotalBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currentAvailableBal", currentAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAssetItem, "currentDrawableBal", currentDrawableBal);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCashAssetItem, c);
    module_vnoes::objects.emplace("_OesCashAssetItem", c);
}
void generate_class_OesQryCashAssetReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryCashAssetReq> c(parent, "_OesQryCashAssetReq");
    if constexpr (std::is_default_constructible_v<_OesQryCashAssetReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCashAssetReq, c);
    module_vnoes::objects.emplace("_OesQryCashAssetReq", c);
}
void generate_class_OesQryCashAssetRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryCashAssetRsp> c(parent, "_OesQryCashAssetRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCashAssetRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCashAssetRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCashAssetRsp, c);
    module_vnoes::objects.emplace("_OesQryCashAssetRsp", c);
}
void generate_class_OesCounterCashItem(pybind11::object & parent)
{
    pybind11::class_<_OesCounterCashItem> c(parent, "_OesCounterCashItem");
    if constexpr (std::is_default_constructible_v<_OesCounterCashItem>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "custName", custName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "bankId", bankId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "counterAvailableBal", counterAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "counterDrawableBal", counterDrawableBal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "counterCashUpdateTime", counterCashUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCounterCashItem, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCounterCashItem, c);
    module_vnoes::objects.emplace("_OesCounterCashItem", c);
}
void generate_class_OesQryCounterCashReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryCounterCashReq> c(parent, "_OesQryCounterCashReq");
    if constexpr (std::is_default_constructible_v<_OesQryCounterCashReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCounterCashReq, "cashAcctId", cashAcctId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCounterCashReq, c);
    module_vnoes::objects.emplace("_OesQryCounterCashReq", c);
}
void generate_class_OesQryCounterCashRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryCounterCashRsp> c(parent, "_OesQryCounterCashRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCounterCashRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCounterCashRsp, "counterCashItem", counterCashItem);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCounterCashRsp, c);
    module_vnoes::objects.emplace("_OesQryCounterCashRsp", c);
}
void generate_class_OesQryStkHoldingFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryStkHoldingFilter> c(parent, "_OesQryStkHoldingFilter");
    if constexpr (std::is_default_constructible_v<_OesQryStkHoldingFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStkHoldingFilter, c);
    module_vnoes::objects.emplace("_OesQryStkHoldingFilter", c);
}
void generate_class_OesStkHoldingItem(pybind11::object & parent)
{
    pybind11::class_<_OesStkHoldingItem> c(parent, "_OesStkHoldingItem");
    if constexpr (std::is_default_constructible_v<_OesStkHoldingItem>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "originalHld", originalHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "originalCostAmt", originalCostAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalBuyHld", totalBuyHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalSellHld", totalSellHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "sellFrzHld", sellFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "manualFrzHld", manualFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalBuyFee", totalBuyFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalSellFee", totalSellFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalTrsfInHld", totalTrsfInHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "totalTrsfOutHld", totalTrsfOutHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "trsfOutFrzHld", trsfOutFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "lockHld", lockHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "lockFrzHld", lockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "unlockFrzHld", unlockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "coveredFrzHld", coveredFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "coveredHld", coveredHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "sellAvlHld", sellAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "trsfOutAvlHld", trsfOutAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "lockAvlHld", lockAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "coveredAvlHld", coveredAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "sumHld", sumHld);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStkHoldingItem, "costPrice", costPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesStkHoldingItem, c);
    module_vnoes::objects.emplace("_OesStkHoldingItem", c);
}
void generate_class_OesQryStkHoldingReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryStkHoldingReq> c(parent, "_OesQryStkHoldingReq");
    if constexpr (std::is_default_constructible_v<_OesQryStkHoldingReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStkHoldingReq, c);
    module_vnoes::objects.emplace("_OesQryStkHoldingReq", c);
}
void generate_class_OesQryStkHoldingRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryStkHoldingRsp> c(parent, "_OesQryStkHoldingRsp");
    if constexpr (std::is_default_constructible_v<_OesQryStkHoldingRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingRsp, "qryHead", qryHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStkHoldingRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStkHoldingRsp, c);
    module_vnoes::objects.emplace("_OesQryStkHoldingRsp", c);
}
void generate_class_OesOptHoldingItem(pybind11::object & parent)
{
    pybind11::class_<_OesOptHoldingItem> c(parent, "_OesOptHoldingItem");
    if constexpr (std::is_default_constructible_v<_OesOptHoldingItem>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldA", hldA);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldB", hldB);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldC", hldC);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldC2", hldC2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldRA", hldRA);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldRB", hldRB);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOptHoldingItem, "hldRC", hldRC);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOptHoldingItem, c);
    module_vnoes::objects.emplace("_OesOptHoldingItem", c);
}
