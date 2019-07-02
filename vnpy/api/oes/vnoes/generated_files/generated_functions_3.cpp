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


void generate_class_OesQryOptHoldingReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryOptHoldingReq> c(parent, "_OesQryOptHoldingReq");
    if constexpr (std::is_default_constructible_v<_OesQryOptHoldingReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptHoldingReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptHoldingReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptHoldingReq, c);
    module_vnoes::objects.emplace("_OesQryOptHoldingReq", c);
}
void generate_class_OesQryHoldRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryHoldRsp> c(parent, "_OesQryHoldRsp");
    if constexpr (std::is_default_constructible_v<_OesQryHoldRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryHoldRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryHoldRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryHoldRsp, c);
    module_vnoes::objects.emplace("_OesQryHoldRsp", c);
}
void generate_class_OesQryCustFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryCustFilter> c(parent, "_OesQryCustFilter");
    if constexpr (std::is_default_constructible_v<_OesQryCustFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCustFilter, c);
    module_vnoes::objects.emplace("_OesQryCustFilter", c);
}
void generate_class_OesQryCustReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryCustReq> c(parent, "_OesQryCustReq");
    if constexpr (std::is_default_constructible_v<_OesQryCustReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCustReq, c);
    module_vnoes::objects.emplace("_OesQryCustReq", c);
}
void generate_class_OesQryCustRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryCustRsp> c(parent, "_OesQryCustRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCustRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCustRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCustRsp, c);
    module_vnoes::objects.emplace("_OesQryCustRsp", c);
}
void generate_class_OesQryInvAcctFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryInvAcctFilter> c(parent, "_OesQryInvAcctFilter");
    if constexpr (std::is_default_constructible_v<_OesQryInvAcctFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryInvAcctFilter, c);
    module_vnoes::objects.emplace("_OesQryInvAcctFilter", c);
}
void generate_class_OesInvAcctItem(pybind11::object & parent)
{
    pybind11::class_<_OesInvAcctItem> c(parent, "_OesInvAcctItem");
    if constexpr (std::is_default_constructible_v<_OesInvAcctItem>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "acctType", acctType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "ownerType", ownerType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "optInvLevel", optInvLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "isTradeDisabled", isTradeDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "limits", limits);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "permissions", permissions);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "__INV_ACCT_BASE_filler2", __INV_ACCT_BASE_filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "subscriptionQuota", subscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "kcSubscriptionQuota", kcSubscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "__INV_ACCT_BASE_reserve", __INV_ACCT_BASE_reserve);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctItem, "custId", custId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesInvAcctItem, c);
    module_vnoes::objects.emplace("_OesInvAcctItem", c);
}
void generate_class_OesQryInvAcctReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryInvAcctReq> c(parent, "_OesQryInvAcctReq");
    if constexpr (std::is_default_constructible_v<_OesQryInvAcctReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryInvAcctReq, c);
    module_vnoes::objects.emplace("_OesQryInvAcctReq", c);
}
void generate_class_OesQryInvAcctRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryInvAcctRsp> c(parent, "_OesQryInvAcctRsp");
    if constexpr (std::is_default_constructible_v<_OesQryInvAcctRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryInvAcctRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryInvAcctRsp, c);
    module_vnoes::objects.emplace("_OesQryInvAcctRsp", c);
}
void generate_class_OesInvAcctOverview(pybind11::object & parent)
{
    pybind11::class_<_OesInvAcctOverview> c(parent, "_OesInvAcctOverview");
    if constexpr (std::is_default_constructible_v<_OesInvAcctOverview>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "acctType", acctType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "ownerType", ownerType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "optInvLevel", optInvLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "isTradeDisabled", isTradeDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "limits", limits);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "permissions", permissions);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "subscriptionQuota", subscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "isValid", isValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "kcSubscriptionQuota", kcSubscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "trdOrdCnt", trdOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "nonTrdOrdCnt", nonTrdOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "cancelOrdCnt", cancelOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "oesRejectOrdCnt", oesRejectOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "exchRejectOrdCnt", exchRejectOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "trdCnt", trdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesInvAcctOverview, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesInvAcctOverview, c);
    module_vnoes::objects.emplace("_OesInvAcctOverview", c);
}
void generate_class_OesCashAcctOverview(pybind11::object & parent)
{
    pybind11::class_<_OesCashAcctOverview> c(parent, "_OesCashAcctOverview");
    if constexpr (std::is_default_constructible_v<_OesCashAcctOverview>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "bankId", bankId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "isValid", isValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCashAcctOverview, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCashAcctOverview, c);
    module_vnoes::objects.emplace("_OesCashAcctOverview", c);
}
void generate_class_OesCustOverview(pybind11::object & parent)
{
    pybind11::class_<_OesCustOverview> c(parent, "_OesCustOverview");
    if constexpr (std::is_default_constructible_v<_OesCustOverview>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "custType", custType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "riskLevel", riskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "originRiskLevel", originRiskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "institutionFlag", institutionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "investorClass", investorClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "__CUST_BASE_filler1", __CUST_BASE_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "__CUST_BASE_filler2", __CUST_BASE_filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "custName", custName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "spotCashAcct", spotCashAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "creditCashAcct", creditCashAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "optionCashAcct", optionCashAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "shSpotInvAcct", shSpotInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "shOptionInvAcct", shOptionInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "szSpotInvAcct", szSpotInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "szOptionInvAcct", szOptionInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCustOverview, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCustOverview, c);
    module_vnoes::objects.emplace("_OesCustOverview", c);
}
void generate_class_OesClientOverview(pybind11::object & parent)
{
    pybind11::class_<_OesClientOverview> c(parent, "_OesClientOverview");
    if constexpr (std::is_default_constructible_v<_OesClientOverview>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientType", clientType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientStatus", clientStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "isApiForbidden", isApiForbidden);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "isBlockTrader", isBlockTrader);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "logonTime", logonTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientName", clientName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "clientMemo", clientMemo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "sseStkPbuId", sseStkPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "sseOptPbuId", sseOptPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "sseQualificationClass", sseQualificationClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "szseStkPbuId", szseStkPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "szseOptPbuId", szseOptPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "szseQualificationClass", szseQualificationClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "currOrdConnected", currOrdConnected);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "currRptConnected", currRptConnected);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "currQryConnected", currQryConnected);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "maxOrdConnect", maxOrdConnect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "maxRptConnect", maxRptConnect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "maxQryConnect", maxQryConnect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "ordTrafficLimit", ordTrafficLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "qryTrafficLimit", qryTrafficLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__reserve", __reserve);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "associatedCustCnt", associatedCustCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "__filler4", __filler4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesClientOverview, "custItems", custItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesClientOverview, c);
    module_vnoes::objects.emplace("_OesClientOverview", c);
}
void generate_class_OesQryCommissionRateFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryCommissionRateFilter> c(parent, "_OesQryCommissionRateFilter");
    if constexpr (std::is_default_constructible_v<_OesQryCommissionRateFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCommissionRateFilter, c);
    module_vnoes::objects.emplace("_OesQryCommissionRateFilter", c);
}
void generate_class_OesCommissionRateItem(pybind11::object & parent)
{
    pybind11::class_<_OesCommissionRateItem> c(parent, "_OesCommissionRateItem");
    if constexpr (std::is_default_constructible_v<_OesCommissionRateItem>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "feeType", feeType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "calcFeeMode", calcFeeMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "feeRate", feeRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "minFee", minFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesCommissionRateItem, "maxFee", maxFee);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesCommissionRateItem, c);
    module_vnoes::objects.emplace("_OesCommissionRateItem", c);
}
void generate_class_OesQryCommissionRateReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryCommissionRateReq> c(parent, "_OesQryCommissionRateReq");
    if constexpr (std::is_default_constructible_v<_OesQryCommissionRateReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCommissionRateReq, c);
    module_vnoes::objects.emplace("_OesQryCommissionRateReq", c);
}
void generate_class_OesQryCommissionRateRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryCommissionRateRsp> c(parent, "_OesQryCommissionRateRsp");
    if constexpr (std::is_default_constructible_v<_OesQryCommissionRateRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryCommissionRateRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryCommissionRateRsp, c);
    module_vnoes::objects.emplace("_OesQryCommissionRateRsp", c);
}
void generate_class_OesQryFundTransferSerialFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryFundTransferSerialFilter> c(parent, "_OesQryFundTransferSerialFilter");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialFilter, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialFilter", c);
}
void generate_class_OesQryFundTransferSerialReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryFundTransferSerialReq> c(parent, "_OesQryFundTransferSerialReq");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialReq, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialReq", c);
}
void generate_class_OesQryFundTransferSerialRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryFundTransferSerialRsp> c(parent, "_OesQryFundTransferSerialRsp");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialRsp, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialRsp", c);
}
void generate_class_OesQryLotWinningFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryLotWinningFilter> c(parent, "_OesQryLotWinningFilter");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "lotType", lotType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "startDate", startDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "endDate", endDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningFilter, c);
    module_vnoes::objects.emplace("_OesQryLotWinningFilter", c);
}
void generate_class_OesQryLotWinningReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryLotWinningReq> c(parent, "_OesQryLotWinningReq");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningReq, c);
    module_vnoes::objects.emplace("_OesQryLotWinningReq", c);
}
void generate_class_OesQryLotWinningRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryLotWinningRsp> c(parent, "_OesQryLotWinningRsp");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningRsp, c);
    module_vnoes::objects.emplace("_OesQryLotWinningRsp", c);
}
void generate_class_OesQryIssueFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryIssueFilter> c(parent, "_OesQryIssueFilter");
    if constexpr (std::is_default_constructible_v<_OesQryIssueFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueFilter, c);
    module_vnoes::objects.emplace("_OesQryIssueFilter", c);
}
void generate_class_OesQryIssueReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryIssueReq> c(parent, "_OesQryIssueReq");
    if constexpr (std::is_default_constructible_v<_OesQryIssueReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueReq, c);
    module_vnoes::objects.emplace("_OesQryIssueReq", c);
}
void generate_class_OesQryIssueRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryIssueRsp> c(parent, "_OesQryIssueRsp");
    if constexpr (std::is_default_constructible_v<_OesQryIssueRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueRsp, c);
    module_vnoes::objects.emplace("_OesQryIssueRsp", c);
}
void generate_class_OesQryStockFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryStockFilter> c(parent, "_OesQryStockFilter");
    if constexpr (std::is_default_constructible_v<_OesQryStockFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockFilter, c);
    module_vnoes::objects.emplace("_OesQryStockFilter", c);
}
void generate_class_OesQryStockReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryStockReq> c(parent, "_OesQryStockReq");
    if constexpr (std::is_default_constructible_v<_OesQryStockReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockReq, c);
    module_vnoes::objects.emplace("_OesQryStockReq", c);
}
void generate_class_OesQryStockRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryStockRsp> c(parent, "_OesQryStockRsp");
    if constexpr (std::is_default_constructible_v<_OesQryStockRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockRsp, c);
    module_vnoes::objects.emplace("_OesQryStockRsp", c);
}
void generate_class_OesQryEtfFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryEtfFilter> c(parent, "_OesQryEtfFilter");
    if constexpr (std::is_default_constructible_v<_OesQryEtfFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfFilter, c);
    module_vnoes::objects.emplace("_OesQryEtfFilter", c);
}
void generate_class_OesQryEtfReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryEtfReq> c(parent, "_OesQryEtfReq");
    if constexpr (std::is_default_constructible_v<_OesQryEtfReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfReq, c);
    module_vnoes::objects.emplace("_OesQryEtfReq", c);
}
void generate_class_OesQryEtfRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryEtfRsp> c(parent, "_OesQryEtfRsp");
    if constexpr (std::is_default_constructible_v<_OesQryEtfRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfRsp, c);
    module_vnoes::objects.emplace("_OesQryEtfRsp", c);
}
void generate_class_OesQryEtfComponentFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryEtfComponentFilter> c(parent, "_OesQryEtfComponentFilter");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentFilter, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentFilter, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentFilter", c);
}
void generate_class_OesEtfComponentItem(pybind11::object & parent)
{
    pybind11::class_<_OesEtfComponentItem> c(parent, "_OesEtfComponentItem");
    if constexpr (std::is_default_constructible_v<_OesEtfComponentItem>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "subFlag", subFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "prevClose", prevClose);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "premiumRate", premiumRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "creationSubCash", creationSubCash);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "redemptionCashSub", redemptionCashSub);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "fundId", fundId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesEtfComponentItem, c);
    module_vnoes::objects.emplace("_OesEtfComponentItem", c);
}
void generate_class_OesQryEtfComponentReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryEtfComponentReq> c(parent, "_OesQryEtfComponentReq");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentReq, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentReq", c);
}
void generate_class_OesQryEtfComponentRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryEtfComponentRsp> c(parent, "_OesQryEtfComponentRsp");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentRsp, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentRsp", c);
}
void generate_class_OesQryOptionFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryOptionFilter> c(parent, "_OesQryOptionFilter");
    if constexpr (std::is_default_constructible_v<_OesQryOptionFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionFilter, c);
    module_vnoes::objects.emplace("_OesQryOptionFilter", c);
}
void generate_class_OesQryOptionReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryOptionReq> c(parent, "_OesQryOptionReq");
    if constexpr (std::is_default_constructible_v<_OesQryOptionReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionReq, c);
    module_vnoes::objects.emplace("_OesQryOptionReq", c);
}
void generate_class_OesQryOptionRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryOptionRsp> c(parent, "_OesQryOptionRsp");
    if constexpr (std::is_default_constructible_v<_OesQryOptionRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionRsp, c);
    module_vnoes::objects.emplace("_OesQryOptionRsp", c);
}
void generate_class_OesQryTradingDayRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryTradingDayRsp> c(parent, "_OesQryTradingDayRsp");
    if constexpr (std::is_default_constructible_v<_OesQryTradingDayRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTradingDayRsp, "tradingDay", tradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTradingDayRsp, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTradingDayRsp, c);
    module_vnoes::objects.emplace("_OesQryTradingDayRsp", c);
}
void generate_class_OesQryMarketStateFilter(pybind11::object & parent)
{
    pybind11::class_<_OesQryMarketStateFilter> c(parent, "_OesQryMarketStateFilter");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateFilter>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "platformId", platformId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateFilter, c);
    module_vnoes::objects.emplace("_OesQryMarketStateFilter", c);
}
void generate_class_OesQryMarketStateReq(pybind11::object & parent)
{
    pybind11::class_<_OesQryMarketStateReq> c(parent, "_OesQryMarketStateReq");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateReq, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateReq, c);
    module_vnoes::objects.emplace("_OesQryMarketStateReq", c);
}
void generate_class_OesQryMarketStateRsp(pybind11::object & parent)
{
    pybind11::class_<_OesQryMarketStateRsp> c(parent, "_OesQryMarketStateRsp");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateRsp, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateRsp, c);
    module_vnoes::objects.emplace("_OesQryMarketStateRsp", c);
}
void generate_class_OesQryReqMsg(pybind11::object & parent)
{
    pybind11::class_<_OesQryReqMsg> c(parent, "_OesQryReqMsg");
    if constexpr (std::is_default_constructible_v<_OesQryReqMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOrd", qryOrd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryTrd", qryTrd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCashAsset", qryCashAsset);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryStkHolding", qryStkHolding);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOptHolding", qryOptHolding);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCust", qryCust);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryInvAcct", qryInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryComms", qryComms);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryFundTrsf", qryFundTrsf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryLotWinning", qryLotWinning);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryIssue", qryIssue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryStock", qryStock);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryEtf", qryEtf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryEtfComponent", qryEtfComponent);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOption", qryOption);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryMktState", qryMktState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCounterCash", qryCounterCash);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryReqMsg, c);
    module_vnoes::objects.emplace("_OesQryReqMsg", c);
}
