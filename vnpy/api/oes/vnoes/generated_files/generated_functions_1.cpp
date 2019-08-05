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


void generate_class_decltype_OesFundTrsfBaseInfo_userInfo_(pybind11::object & parent)
{
    // decltype(_OesFundTrsfBaseInfo::userInfo)
    pybind11::class_<decltype(_OesFundTrsfBaseInfo::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfBaseInfo::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesFundTrsfBaseInfo::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "u64", u64);
    // decltype(_OesFundTrsfBaseInfo::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "i64", i64);
    // decltype(_OesFundTrsfBaseInfo::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "u32", u32);
    // decltype(_OesFundTrsfBaseInfo::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "i32", i32);
    // decltype(_OesFundTrsfBaseInfo::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfBaseInfo::userInfo)", c);
}
void generate_class_OesFundTrsfReq(pybind11::object & parent)
{
    // _OesFundTrsfReq
    pybind11::class_<_OesFundTrsfReq> c(parent, "_OesFundTrsfReq");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfReq>)
        c.def(pybind11::init<>());
    // _OesFundTrsfReq::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "clSeqNo", clSeqNo);
    // _OesFundTrsfReq::direct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "direct", direct);
    // _OesFundTrsfReq::isAllotOnly
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "isAllotOnly", isAllotOnly);
    // _OesFundTrsfReq::__FUND_TRSF_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    // _OesFundTrsfReq::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "cashAcctId", cashAcctId);
    // _OesFundTrsfReq::trdPasswd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "trdPasswd", trdPasswd);
    // _OesFundTrsfReq::trsfPasswd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "trsfPasswd", trsfPasswd);
    // _OesFundTrsfReq::occurAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "occurAmt", occurAmt);
    // _OesFundTrsfReq::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "userInfo", userInfo);
    generate_class_decltype_OesFundTrsfReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfReq, c);
    module_vnoes::objects.emplace("_OesFundTrsfReq", c);
}
void generate_class_decltype_OesFundTrsfReq_userInfo_(pybind11::object & parent)
{
    // decltype(_OesFundTrsfReq::userInfo)
    pybind11::class_<decltype(_OesFundTrsfReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfReq::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesFundTrsfReq::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "u64", u64);
    // decltype(_OesFundTrsfReq::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "i64", i64);
    // decltype(_OesFundTrsfReq::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "u32", u32);
    // decltype(_OesFundTrsfReq::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "i32", i32);
    // decltype(_OesFundTrsfReq::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfReq::userInfo)", c);
}
void generate_class_OesFundTrsfReject(pybind11::object & parent)
{
    // _OesFundTrsfReject
    pybind11::class_<_OesFundTrsfReject> c(parent, "_OesFundTrsfReject");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfReject>)
        c.def(pybind11::init<>());
    // _OesFundTrsfReject::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "clSeqNo", clSeqNo);
    // _OesFundTrsfReject::direct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "direct", direct);
    // _OesFundTrsfReject::isAllotOnly
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "isAllotOnly", isAllotOnly);
    // _OesFundTrsfReject::__FUND_TRSF_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    // _OesFundTrsfReject::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "cashAcctId", cashAcctId);
    // _OesFundTrsfReject::trdPasswd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "trdPasswd", trdPasswd);
    // _OesFundTrsfReject::trsfPasswd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "trsfPasswd", trsfPasswd);
    // _OesFundTrsfReject::occurAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "occurAmt", occurAmt);
    // _OesFundTrsfReject::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "userInfo", userInfo);
    // _OesFundTrsfReject::ordDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "ordDate", ordDate);
    // _OesFundTrsfReject::ordTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "ordTime", ordTime);
    // _OesFundTrsfReject::clientId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "clientId", clientId);
    // _OesFundTrsfReject::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "clEnvId", clEnvId);
    // _OesFundTrsfReject::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "__filler", __filler);
    // _OesFundTrsfReject::rejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "rejReason", rejReason);
    // _OesFundTrsfReject::errorInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "errorInfo", errorInfo);
    generate_class_decltype_OesFundTrsfReject_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfReject, c);
    module_vnoes::objects.emplace("_OesFundTrsfReject", c);
}
void generate_class_decltype_OesFundTrsfReject_userInfo_(pybind11::object & parent)
{
    // decltype(_OesFundTrsfReject::userInfo)
    pybind11::class_<decltype(_OesFundTrsfReject::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfReject::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesFundTrsfReject::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "u64", u64);
    // decltype(_OesFundTrsfReject::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "i64", i64);
    // decltype(_OesFundTrsfReject::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "u32", u32);
    // decltype(_OesFundTrsfReject::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "i32", i32);
    // decltype(_OesFundTrsfReject::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfReject::userInfo)", c);
}
void generate_class_OesFundTrsfReport(pybind11::object & parent)
{
    // _OesFundTrsfReport
    pybind11::class_<_OesFundTrsfReport> c(parent, "_OesFundTrsfReport");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfReport>)
        c.def(pybind11::init<>());
    // _OesFundTrsfReport::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "clSeqNo", clSeqNo);
    // _OesFundTrsfReport::clientId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "clientId", clientId);
    // _OesFundTrsfReport::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "clEnvId", clEnvId);
    // _OesFundTrsfReport::direct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "direct", direct);
    // _OesFundTrsfReport::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "cashAcctId", cashAcctId);
    // _OesFundTrsfReport::occurAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "occurAmt", occurAmt);
    // _OesFundTrsfReport::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "userInfo", userInfo);
    // _OesFundTrsfReport::fundTrsfId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "fundTrsfId", fundTrsfId);
    // _OesFundTrsfReport::counterEntrustNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "counterEntrustNo", counterEntrustNo);
    // _OesFundTrsfReport::operDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "operDate", operDate);
    // _OesFundTrsfReport::operTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "operTime", operTime);
    // _OesFundTrsfReport::dclrTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "dclrTime", dclrTime);
    // _OesFundTrsfReport::doneTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "doneTime", doneTime);
    // _OesFundTrsfReport::isAllotOnly
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "isAllotOnly", isAllotOnly);
    // _OesFundTrsfReport::trsfStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "trsfStatus", trsfStatus);
    // _OesFundTrsfReport::__hasCounterTransfered
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "__hasCounterTransfered", __hasCounterTransfered);
    // _OesFundTrsfReport::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "__filler", __filler);
    // _OesFundTrsfReport::rejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "rejReason", rejReason);
    // _OesFundTrsfReport::counterErrCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "counterErrCode", counterErrCode);
    // _OesFundTrsfReport::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "__filler2", __filler2);
    // _OesFundTrsfReport::allotSerialNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "allotSerialNo", allotSerialNo);
    // _OesFundTrsfReport::errorInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "errorInfo", errorInfo);
    generate_class_decltype_OesFundTrsfReport_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfReport, c);
    module_vnoes::objects.emplace("_OesFundTrsfReport", c);
}
void generate_class_decltype_OesFundTrsfReport_userInfo_(pybind11::object & parent)
{
    // decltype(_OesFundTrsfReport::userInfo)
    pybind11::class_<decltype(_OesFundTrsfReport::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfReport::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesFundTrsfReport::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "u64", u64);
    // decltype(_OesFundTrsfReport::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "i64", i64);
    // decltype(_OesFundTrsfReport::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "u32", u32);
    // decltype(_OesFundTrsfReport::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "i32", i32);
    // decltype(_OesFundTrsfReport::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfReport::userInfo)", c);
}
void generate_class_OesIssueBaseInfo(pybind11::object & parent)
{
    // _OesIssueBaseInfo
    pybind11::class_<_OesIssueBaseInfo> c(parent, "_OesIssueBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesIssueBaseInfo>)
        c.def(pybind11::init<>());
    // _OesIssueBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "securityId", securityId);
    // _OesIssueBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "mktId", mktId);
    // _OesIssueBaseInfo::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "securityType", securityType);
    // _OesIssueBaseInfo::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "subSecurityType", subSecurityType);
    // _OesIssueBaseInfo::isCancelAble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "isCancelAble", isCancelAble);
    // _OesIssueBaseInfo::isReApplyAble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "isReApplyAble", isReApplyAble);
    // _OesIssueBaseInfo::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "productType", productType);
    // _OesIssueBaseInfo::__ISSUE_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "__ISSUE_BASE_filler", __ISSUE_BASE_filler);
    // _OesIssueBaseInfo::securityName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "securityName", securityName);
    // _OesIssueBaseInfo::underlyingSecurityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "underlyingSecurityId", underlyingSecurityId);
    // _OesIssueBaseInfo::startDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "startDate", startDate);
    // _OesIssueBaseInfo::endDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "endDate", endDate);
    // _OesIssueBaseInfo::issueQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "issueQty", issueQty);
    // _OesIssueBaseInfo::qtyUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "qtyUnit", qtyUnit);
    // _OesIssueBaseInfo::ordMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "ordMaxQty", ordMaxQty);
    // _OesIssueBaseInfo::ordMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "ordMinQty", ordMinQty);
    // _OesIssueBaseInfo::issuePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "issuePrice", issuePrice);
    // _OesIssueBaseInfo::upperLimitPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "upperLimitPrice", upperLimitPrice);
    // _OesIssueBaseInfo::ceilPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "ceilPrice", ceilPrice);
    // _OesIssueBaseInfo::lowerLimitPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "lowerLimitPrice", lowerLimitPrice);
    // _OesIssueBaseInfo::floorPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "floorPrice", floorPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesIssueBaseInfo, c);
    module_vnoes::objects.emplace("_OesIssueBaseInfo", c);
}
void generate_class_OesPriceLimit(pybind11::object & parent)
{
    // _OesPriceLimit
    pybind11::class_<_OesPriceLimit> c(parent, "_OesPriceLimit");
    if constexpr (std::is_default_constructible_v<_OesPriceLimit>)
        c.def(pybind11::init<>());
    // _OesPriceLimit::upperLimitPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "upperLimitPrice", upperLimitPrice);
    // _OesPriceLimit::ceilPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "ceilPrice", ceilPrice);
    // _OesPriceLimit::lowerLimitPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "lowerLimitPrice", lowerLimitPrice);
    // _OesPriceLimit::floorPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "floorPrice", floorPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesPriceLimit, c);
    module_vnoes::objects.emplace("_OesPriceLimit", c);
}
void generate_class_OesStockBaseInfo(pybind11::object & parent)
{
    // _OesStockBaseInfo
    pybind11::class_<_OesStockBaseInfo> c(parent, "_OesStockBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesStockBaseInfo>)
        c.def(pybind11::init<>());
    // _OesStockBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityId", securityId);
    // _OesStockBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktId", mktId);
    // _OesStockBaseInfo::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "productType", productType);
    // _OesStockBaseInfo::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityType", securityType);
    // _OesStockBaseInfo::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "subSecurityType", subSecurityType);
    // _OesStockBaseInfo::securityLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityLevel", securityLevel);
    // _OesStockBaseInfo::securityRiskLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityRiskLevel", securityRiskLevel);
    // _OesStockBaseInfo::currType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "currType", currType);
    // _OesStockBaseInfo::qualificationClass
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "qualificationClass", qualificationClass);
    // _OesStockBaseInfo::isDayTrading
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "isDayTrading", isDayTrading);
    // _OesStockBaseInfo::suspFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "suspFlag", suspFlag);
    // _OesStockBaseInfo::temporarySuspFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "temporarySuspFlag", temporarySuspFlag);
    // _OesStockBaseInfo::__STOCK_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "__STOCK_BASE_filler", __STOCK_BASE_filler);
    // _OesStockBaseInfo::buyQtyUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "buyQtyUnit", buyQtyUnit);
    // _OesStockBaseInfo::lmtBuyMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtBuyMaxQty", lmtBuyMaxQty);
    // _OesStockBaseInfo::buyOrdMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "buyOrdMaxQty", buyOrdMaxQty);
    // _OesStockBaseInfo::lmtBuyMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtBuyMinQty", lmtBuyMinQty);
    // _OesStockBaseInfo::buyOrdMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "buyOrdMinQty", buyOrdMinQty);
    // _OesStockBaseInfo::mktBuyMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktBuyMaxQty", mktBuyMaxQty);
    // _OesStockBaseInfo::mktBuyMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktBuyMinQty", mktBuyMinQty);
    // _OesStockBaseInfo::sellQtyUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "sellQtyUnit", sellQtyUnit);
    // _OesStockBaseInfo::lmtSellMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtSellMaxQty", lmtSellMaxQty);
    // _OesStockBaseInfo::sellOrdMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "sellOrdMaxQty", sellOrdMaxQty);
    // _OesStockBaseInfo::lmtSellMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtSellMinQty", lmtSellMinQty);
    // _OesStockBaseInfo::sellOrdMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "sellOrdMinQty", sellOrdMinQty);
    // _OesStockBaseInfo::mktSellMaxQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktSellMaxQty", mktSellMaxQty);
    // _OesStockBaseInfo::mktSellMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktSellMinQty", mktSellMinQty);
    // _OesStockBaseInfo::priceTick
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "priceTick", priceTick);
    // _OesStockBaseInfo::priceUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "priceUnit", priceUnit);
    // _OesStockBaseInfo::prevClose
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "prevClose", prevClose);
    // _OesStockBaseInfo::parPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "parPrice", parPrice);
    // _OesStockBaseInfo::bondInterest
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "bondInterest", bondInterest);
    // _OesStockBaseInfo::repoExpirationDays
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "repoExpirationDays", repoExpirationDays);
    // _OesStockBaseInfo::cashHoldDays
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "cashHoldDays", cashHoldDays);
    // _OesStockBaseInfo::priceLimit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "priceLimit", priceLimit);
    // _OesStockBaseInfo::securityName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityName", securityName);
    // _OesStockBaseInfo::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "fundId", fundId);
    // _OesStockBaseInfo::__STOCK_BASE_reserve
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "__STOCK_BASE_reserve", __STOCK_BASE_reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesStockBaseInfo, c);
    module_vnoes::objects.emplace("_OesStockBaseInfo", c);
}
void generate_class_OesEtfBaseInfo(pybind11::object & parent)
{
    // _OesEtfBaseInfo
    pybind11::class_<_OesEtfBaseInfo> c(parent, "_OesEtfBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesEtfBaseInfo>)
        c.def(pybind11::init<>());
    // _OesEtfBaseInfo::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "fundId", fundId);
    // _OesEtfBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "securityId", securityId);
    // _OesEtfBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "mktId", mktId);
    // _OesEtfBaseInfo::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "securityType", securityType);
    // _OesEtfBaseInfo::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "subSecurityType", subSecurityType);
    // _OesEtfBaseInfo::isPublishIOPV
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isPublishIOPV", isPublishIOPV);
    // _OesEtfBaseInfo::isCreationAble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isCreationAble", isCreationAble);
    // _OesEtfBaseInfo::isRedemptionAble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isRedemptionAble", isRedemptionAble);
    // _OesEtfBaseInfo::isDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "isDisabled", isDisabled);
    // _OesEtfBaseInfo::__ETF_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "__ETF_BASE_filler", __ETF_BASE_filler);
    // _OesEtfBaseInfo::componentCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "componentCnt", componentCnt);
    // _OesEtfBaseInfo::creRdmUnit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "creRdmUnit", creRdmUnit);
    // _OesEtfBaseInfo::maxCashRatio
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "maxCashRatio", maxCashRatio);
    // _OesEtfBaseInfo::nav
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "nav", nav);
    // _OesEtfBaseInfo::navPerCU
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "navPerCU", navPerCU);
    // _OesEtfBaseInfo::dividendPerCU
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "dividendPerCU", dividendPerCU);
    // _OesEtfBaseInfo::tradingDay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "tradingDay", tradingDay);
    // _OesEtfBaseInfo::preTradingDay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "preTradingDay", preTradingDay);
    // _OesEtfBaseInfo::estiCashCmpoent
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "estiCashCmpoent", estiCashCmpoent);
    // _OesEtfBaseInfo::cashCmpoent
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "cashCmpoent", cashCmpoent);
    // _OesEtfBaseInfo::creationLimit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "creationLimit", creationLimit);
    // _OesEtfBaseInfo::redemLimit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "redemLimit", redemLimit);
    // _OesEtfBaseInfo::netCreationLimit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "netCreationLimit", netCreationLimit);
    // _OesEtfBaseInfo::netRedemLimit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfBaseInfo, "netRedemLimit", netRedemLimit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesEtfBaseInfo, c);
    module_vnoes::objects.emplace("_OesEtfBaseInfo", c);
}
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
