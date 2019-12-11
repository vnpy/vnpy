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


void generate_class_decltype_OesTrdCnfm_userInfo_(pybind11::object & parent)
{
    // decltype(_OesTrdCnfm::userInfo)
    pybind11::class_<decltype(_OesTrdCnfm::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesTrdCnfm::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesTrdCnfm::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "u64", u64);
    // decltype(_OesTrdCnfm::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "i64", i64);
    // decltype(_OesTrdCnfm::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "u32", u32);
    // decltype(_OesTrdCnfm::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "i32", i32);
    // decltype(_OesTrdCnfm::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesTrdCnfm::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesTrdCnfm::userInfo)", c);
}
void generate_class_OesLotWinningBaseInfo(pybind11::object & parent)
{
    // _OesLotWinningBaseInfo
    pybind11::class_<_OesLotWinningBaseInfo> c(parent, "_OesLotWinningBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesLotWinningBaseInfo>)
        c.def(pybind11::init<>());
    // _OesLotWinningBaseInfo::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "invAcctId", invAcctId);
    // _OesLotWinningBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "securityId", securityId);
    // _OesLotWinningBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "mktId", mktId);
    // _OesLotWinningBaseInfo::lotType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotType", lotType);
    // _OesLotWinningBaseInfo::rejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "rejReason", rejReason);
    // _OesLotWinningBaseInfo::__LOT_WINNING_BASE_INFO_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "__LOT_WINNING_BASE_INFO_filler", __LOT_WINNING_BASE_INFO_filler);
    // _OesLotWinningBaseInfo::lotDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotDate", lotDate);
    // _OesLotWinningBaseInfo::securityName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "securityName", securityName);
    // _OesLotWinningBaseInfo::assignNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "assignNum", assignNum);
    // _OesLotWinningBaseInfo::lotQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotQty", lotQty);
    // _OesLotWinningBaseInfo::lotPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotPrice", lotPrice);
    // _OesLotWinningBaseInfo::lotAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotAmt", lotAmt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesLotWinningBaseInfo, c);
    module_vnoes::objects.emplace("_OesLotWinningBaseInfo", c);
}
void generate_class_OesFundTrsfBaseInfo(pybind11::object & parent)
{
    // _OesFundTrsfBaseInfo
    pybind11::class_<_OesFundTrsfBaseInfo> c(parent, "_OesFundTrsfBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfBaseInfo>)
        c.def(pybind11::init<>());
    // _OesFundTrsfBaseInfo::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "clSeqNo", clSeqNo);
    // _OesFundTrsfBaseInfo::direct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "direct", direct);
    // _OesFundTrsfBaseInfo::isAllotOnly
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "isAllotOnly", isAllotOnly);
    // _OesFundTrsfBaseInfo::__FUND_TRSF_BASE_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    // _OesFundTrsfBaseInfo::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "cashAcctId", cashAcctId);
    // _OesFundTrsfBaseInfo::trdPasswd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "trdPasswd", trdPasswd);
    // _OesFundTrsfBaseInfo::trsfPasswd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "trsfPasswd", trsfPasswd);
    // _OesFundTrsfBaseInfo::occurAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "occurAmt", occurAmt);
    // _OesFundTrsfBaseInfo::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "userInfo", userInfo);
    generate_class_decltype_OesFundTrsfBaseInfo_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfBaseInfo, c);
    module_vnoes::objects.emplace("_OesFundTrsfBaseInfo", c);
}
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
