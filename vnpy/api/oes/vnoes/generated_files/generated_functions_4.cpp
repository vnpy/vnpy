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
void generate_class_OesQryFundTransferSerialFilter(pybind11::object & parent)
{
    // _OesQryFundTransferSerialFilter
    pybind11::class_<_OesQryFundTransferSerialFilter> c(parent, "_OesQryFundTransferSerialFilter");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialFilter>)
        c.def(pybind11::init<>());
    // _OesQryFundTransferSerialFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "custId", custId);
    // _OesQryFundTransferSerialFilter::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "cashAcctId", cashAcctId);
    // _OesQryFundTransferSerialFilter::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "clSeqNo", clSeqNo);
    // _OesQryFundTransferSerialFilter::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "clEnvId", clEnvId);
    // _OesQryFundTransferSerialFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "__filler", __filler);
    // _OesQryFundTransferSerialFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialFilter, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialFilter", c);
}
void generate_class_OesQryFundTransferSerialReq(pybind11::object & parent)
{
    // _OesQryFundTransferSerialReq
    pybind11::class_<_OesQryFundTransferSerialReq> c(parent, "_OesQryFundTransferSerialReq");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialReq>)
        c.def(pybind11::init<>());
    // _OesQryFundTransferSerialReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialReq, "reqHead", reqHead);
    // _OesQryFundTransferSerialReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialReq, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialReq", c);
}
void generate_class_OesQryFundTransferSerialRsp(pybind11::object & parent)
{
    // _OesQryFundTransferSerialRsp
    pybind11::class_<_OesQryFundTransferSerialRsp> c(parent, "_OesQryFundTransferSerialRsp");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialRsp>)
        c.def(pybind11::init<>());
    // _OesQryFundTransferSerialRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialRsp, "rspHead", rspHead);
    // _OesQryFundTransferSerialRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialRsp, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialRsp", c);
}
void generate_class_OesQryLotWinningFilter(pybind11::object & parent)
{
    // _OesQryLotWinningFilter
    pybind11::class_<_OesQryLotWinningFilter> c(parent, "_OesQryLotWinningFilter");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningFilter>)
        c.def(pybind11::init<>());
    // _OesQryLotWinningFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "custId", custId);
    // _OesQryLotWinningFilter::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "invAcctId", invAcctId);
    // _OesQryLotWinningFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "mktId", mktId);
    // _OesQryLotWinningFilter::lotType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "lotType", lotType);
    // _OesQryLotWinningFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "__filler", __filler);
    // _OesQryLotWinningFilter::startDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "startDate", startDate);
    // _OesQryLotWinningFilter::endDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "endDate", endDate);
    // _OesQryLotWinningFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningFilter, c);
    module_vnoes::objects.emplace("_OesQryLotWinningFilter", c);
}
void generate_class_OesQryLotWinningReq(pybind11::object & parent)
{
    // _OesQryLotWinningReq
    pybind11::class_<_OesQryLotWinningReq> c(parent, "_OesQryLotWinningReq");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningReq>)
        c.def(pybind11::init<>());
    // _OesQryLotWinningReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningReq, "reqHead", reqHead);
    // _OesQryLotWinningReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningReq, c);
    module_vnoes::objects.emplace("_OesQryLotWinningReq", c);
}
void generate_class_OesQryLotWinningRsp(pybind11::object & parent)
{
    // _OesQryLotWinningRsp
    pybind11::class_<_OesQryLotWinningRsp> c(parent, "_OesQryLotWinningRsp");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningRsp>)
        c.def(pybind11::init<>());
    // _OesQryLotWinningRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningRsp, "rspHead", rspHead);
    // _OesQryLotWinningRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningRsp, c);
    module_vnoes::objects.emplace("_OesQryLotWinningRsp", c);
}
void generate_class_OesQryIssueFilter(pybind11::object & parent)
{
    // _OesQryIssueFilter
    pybind11::class_<_OesQryIssueFilter> c(parent, "_OesQryIssueFilter");
    if constexpr (std::is_default_constructible_v<_OesQryIssueFilter>)
        c.def(pybind11::init<>());
    // _OesQryIssueFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "securityId", securityId);
    // _OesQryIssueFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "mktId", mktId);
    // _OesQryIssueFilter::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "productType", productType);
    // _OesQryIssueFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "__filler", __filler);
    // _OesQryIssueFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueFilter, c);
    module_vnoes::objects.emplace("_OesQryIssueFilter", c);
}
void generate_class_OesQryIssueReq(pybind11::object & parent)
{
    // _OesQryIssueReq
    pybind11::class_<_OesQryIssueReq> c(parent, "_OesQryIssueReq");
    if constexpr (std::is_default_constructible_v<_OesQryIssueReq>)
        c.def(pybind11::init<>());
    // _OesQryIssueReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueReq, "reqHead", reqHead);
    // _OesQryIssueReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueReq, c);
    module_vnoes::objects.emplace("_OesQryIssueReq", c);
}
void generate_class_OesQryIssueRsp(pybind11::object & parent)
{
    // _OesQryIssueRsp
    pybind11::class_<_OesQryIssueRsp> c(parent, "_OesQryIssueRsp");
    if constexpr (std::is_default_constructible_v<_OesQryIssueRsp>)
        c.def(pybind11::init<>());
    // _OesQryIssueRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueRsp, "rspHead", rspHead);
    // _OesQryIssueRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueRsp, c);
    module_vnoes::objects.emplace("_OesQryIssueRsp", c);
}
void generate_class_OesQryStockFilter(pybind11::object & parent)
{
    // _OesQryStockFilter
    pybind11::class_<_OesQryStockFilter> c(parent, "_OesQryStockFilter");
    if constexpr (std::is_default_constructible_v<_OesQryStockFilter>)
        c.def(pybind11::init<>());
    // _OesQryStockFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "securityId", securityId);
    // _OesQryStockFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "mktId", mktId);
    // _OesQryStockFilter::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "securityType", securityType);
    // _OesQryStockFilter::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "subSecurityType", subSecurityType);
    // _OesQryStockFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "__filler", __filler);
    // _OesQryStockFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockFilter, c);
    module_vnoes::objects.emplace("_OesQryStockFilter", c);
}
void generate_class_OesQryStockReq(pybind11::object & parent)
{
    // _OesQryStockReq
    pybind11::class_<_OesQryStockReq> c(parent, "_OesQryStockReq");
    if constexpr (std::is_default_constructible_v<_OesQryStockReq>)
        c.def(pybind11::init<>());
    // _OesQryStockReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockReq, "reqHead", reqHead);
    // _OesQryStockReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockReq, c);
    module_vnoes::objects.emplace("_OesQryStockReq", c);
}
void generate_class_OesQryStockRsp(pybind11::object & parent)
{
    // _OesQryStockRsp
    pybind11::class_<_OesQryStockRsp> c(parent, "_OesQryStockRsp");
    if constexpr (std::is_default_constructible_v<_OesQryStockRsp>)
        c.def(pybind11::init<>());
    // _OesQryStockRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockRsp, "rspHead", rspHead);
    // _OesQryStockRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockRsp, c);
    module_vnoes::objects.emplace("_OesQryStockRsp", c);
}
