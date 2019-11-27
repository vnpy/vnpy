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


void generate_vnoes(pybind11::module & parent)
{
    generate_vnoes_sub_namespace(parent);
    generate_vnoes_classes(parent);
    generate_vnoes_enums(parent);
    generate_vnoes_functions(parent);
    generate_vnoes_variables(parent);
    generate_vnoes_typedefs(parent);
    generate_vnoes_caster(parent);
}
void generate_vnoes_sub_namespace(pybind11::module & parent)
{
    
}
void generate_class_OesOrdReq(pybind11::object & parent)
{
    // _OesOrdReq
    pybind11::class_<_OesOrdReq> c(parent, "_OesOrdReq");
    if constexpr (std::is_default_constructible_v<_OesOrdReq>)
        c.def(pybind11::init<>());
    // _OesOrdReq::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "clSeqNo", clSeqNo);
    // _OesOrdReq::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "mktId", mktId);
    // _OesOrdReq::ordType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "ordType", ordType);
    // _OesOrdReq::bsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "bsType", bsType);
    // _OesOrdReq::__ORD_BASE_INFO_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    // _OesOrdReq::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "invAcctId", invAcctId);
    // _OesOrdReq::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "securityId", securityId);
    // _OesOrdReq::ordQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "ordQty", ordQty);
    // _OesOrdReq::ordPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "ordPrice", ordPrice);
    // _OesOrdReq::origClOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "origClOrdId", origClOrdId);
    // _OesOrdReq::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "userInfo", userInfo);
    // _OesOrdReq::__ordReqOrigSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    generate_class_decltype_OesOrdReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdReq, c);
    module_vnoes::objects.emplace("_OesOrdReq", c);
}
void generate_class_decltype_OesOrdReq_userInfo_(pybind11::object & parent)
{
    // decltype(_OesOrdReq::userInfo)
    pybind11::class_<decltype(_OesOrdReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdReq::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesOrdReq::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "u64", u64);
    // decltype(_OesOrdReq::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "i64", i64);
    // decltype(_OesOrdReq::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "u32", u32);
    // decltype(_OesOrdReq::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "i32", i32);
    // decltype(_OesOrdReq::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdReq::userInfo)", c);
}
void generate_class_OesOrdCancelReq(pybind11::object & parent)
{
    // _OesOrdCancelReq
    pybind11::class_<_OesOrdCancelReq> c(parent, "_OesOrdCancelReq");
    if constexpr (std::is_default_constructible_v<_OesOrdCancelReq>)
        c.def(pybind11::init<>());
    // _OesOrdCancelReq::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "clSeqNo", clSeqNo);
    // _OesOrdCancelReq::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "mktId", mktId);
    // _OesOrdCancelReq::__ORD_CANCEL_BASE_INFO_filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "__ORD_CANCEL_BASE_INFO_filler1", __ORD_CANCEL_BASE_INFO_filler1);
    // _OesOrdCancelReq::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "invAcctId", invAcctId);
    // _OesOrdCancelReq::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "securityId", securityId);
    // _OesOrdCancelReq::origClSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "origClSeqNo", origClSeqNo);
    // _OesOrdCancelReq::origClEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "origClEnvId", origClEnvId);
    // _OesOrdCancelReq::__ORD_CANCEL_BASE_INFO_filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "__ORD_CANCEL_BASE_INFO_filler2", __ORD_CANCEL_BASE_INFO_filler2);
    // _OesOrdCancelReq::origClOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "origClOrdId", origClOrdId);
    // _OesOrdCancelReq::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "userInfo", userInfo);
    // _OesOrdCancelReq::__ordReqOrigSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    generate_class_decltype_OesOrdCancelReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdCancelReq, c);
    module_vnoes::objects.emplace("_OesOrdCancelReq", c);
}
void generate_class_decltype_OesOrdCancelReq_userInfo_(pybind11::object & parent)
{
    // decltype(_OesOrdCancelReq::userInfo)
    pybind11::class_<decltype(_OesOrdCancelReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdCancelReq::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesOrdCancelReq::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "u64", u64);
    // decltype(_OesOrdCancelReq::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "i64", i64);
    // decltype(_OesOrdCancelReq::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "u32", u32);
    // decltype(_OesOrdCancelReq::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "i32", i32);
    // decltype(_OesOrdCancelReq::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdCancelReq::userInfo)", c);
}
void generate_class_OesOrdReject(pybind11::object & parent)
{
    // _OesOrdReject
    pybind11::class_<_OesOrdReject> c(parent, "_OesOrdReject");
    if constexpr (std::is_default_constructible_v<_OesOrdReject>)
        c.def(pybind11::init<>());
    // _OesOrdReject::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "clSeqNo", clSeqNo);
    // _OesOrdReject::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "mktId", mktId);
    // _OesOrdReject::ordType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordType", ordType);
    // _OesOrdReject::bsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "bsType", bsType);
    // _OesOrdReject::__ORD_BASE_INFO_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    // _OesOrdReject::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "invAcctId", invAcctId);
    // _OesOrdReject::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "securityId", securityId);
    // _OesOrdReject::ordQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordQty", ordQty);
    // _OesOrdReject::ordPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordPrice", ordPrice);
    // _OesOrdReject::origClOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "origClOrdId", origClOrdId);
    // _OesOrdReject::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "userInfo", userInfo);
    // _OesOrdReject::__ordReqOrigSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    // _OesOrdReject::origClSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "origClSeqNo", origClSeqNo);
    // _OesOrdReject::origClEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "origClEnvId", origClEnvId);
    // _OesOrdReject::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "clEnvId", clEnvId);
    // _OesOrdReject::clientId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "clientId", clientId);
    // _OesOrdReject::ordDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordDate", ordDate);
    // _OesOrdReject::ordTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordTime", ordTime);
    // _OesOrdReject::ordRejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordRejReason", ordRejReason);
    // _OesOrdReject::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "__filler", __filler);
    generate_class_decltype_OesOrdReject_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdReject, c);
    module_vnoes::objects.emplace("_OesOrdReject", c);
}
void generate_class_decltype_OesOrdReject_userInfo_(pybind11::object & parent)
{
    // decltype(_OesOrdReject::userInfo)
    pybind11::class_<decltype(_OesOrdReject::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdReject::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesOrdReject::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "u64", u64);
    // decltype(_OesOrdReject::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "i64", i64);
    // decltype(_OesOrdReject::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "u32", u32);
    // decltype(_OesOrdReject::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "i32", i32);
    // decltype(_OesOrdReject::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdReject::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdReject::userInfo)", c);
}
void generate_class_OesOrdCnfm(pybind11::object & parent)
{
    // _OesOrdCnfm
    pybind11::class_<_OesOrdCnfm> c(parent, "_OesOrdCnfm");
    if constexpr (std::is_default_constructible_v<_OesOrdCnfm>)
        c.def(pybind11::init<>());
    // _OesOrdCnfm::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clSeqNo", clSeqNo);
    // _OesOrdCnfm::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "mktId", mktId);
    // _OesOrdCnfm::ordType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordType", ordType);
    // _OesOrdCnfm::bsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "bsType", bsType);
    // _OesOrdCnfm::__ORD_BASE_INFO_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    // _OesOrdCnfm::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "invAcctId", invAcctId);
    // _OesOrdCnfm::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "securityId", securityId);
    // _OesOrdCnfm::ordQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordQty", ordQty);
    // _OesOrdCnfm::ordPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordPrice", ordPrice);
    // _OesOrdCnfm::origClOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "origClOrdId", origClOrdId);
    // _OesOrdCnfm::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "userInfo", userInfo);
    // _OesOrdCnfm::__ordReqOrigSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    // _OesOrdCnfm::clOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clOrdId", clOrdId);
    // _OesOrdCnfm::clientId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clientId", clientId);
    // _OesOrdCnfm::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clEnvId", clEnvId);
    // _OesOrdCnfm::origClEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "origClEnvId", origClEnvId);
    // _OesOrdCnfm::origClSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "origClSeqNo", origClSeqNo);
    // _OesOrdCnfm::ordDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordDate", ordDate);
    // _OesOrdCnfm::ordTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordTime", ordTime);
    // _OesOrdCnfm::ordCnfmTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordCnfmTime", ordCnfmTime);
    // _OesOrdCnfm::ordStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordStatus", ordStatus);
    // _OesOrdCnfm::ordCnfmSts
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordCnfmSts", ordCnfmSts);
    // _OesOrdCnfm::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "securityType", securityType);
    // _OesOrdCnfm::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "subSecurityType", subSecurityType);
    // _OesOrdCnfm::__platformId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__platformId", __platformId);
    // _OesOrdCnfm::__tgwGrpNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__tgwGrpNo", __tgwGrpNo);
    // _OesOrdCnfm::__tgwPartitionNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__tgwPartitionNo", __tgwPartitionNo);
    // _OesOrdCnfm::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "productType", productType);
    // _OesOrdCnfm::exchOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "exchOrdId", exchOrdId);
    // _OesOrdCnfm::__declareFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__declareFlag", __declareFlag);
    // _OesOrdCnfm::__ORD_CNFM_BASE_INFO_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ORD_CNFM_BASE_INFO_filler", __ORD_CNFM_BASE_INFO_filler);
    // _OesOrdCnfm::frzAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "frzAmt", frzAmt);
    // _OesOrdCnfm::frzInterest
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "frzInterest", frzInterest);
    // _OesOrdCnfm::frzFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "frzFee", frzFee);
    // _OesOrdCnfm::cumAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumAmt", cumAmt);
    // _OesOrdCnfm::cumInterest
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumInterest", cumInterest);
    // _OesOrdCnfm::cumFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumFee", cumFee);
    // _OesOrdCnfm::cumQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumQty", cumQty);
    // _OesOrdCnfm::canceledQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "canceledQty", canceledQty);
    // _OesOrdCnfm::ordRejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordRejReason", ordRejReason);
    // _OesOrdCnfm::exchErrCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "exchErrCode", exchErrCode);
    // _OesOrdCnfm::pbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "pbuId", pbuId);
    // _OesOrdCnfm::branchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "branchId", branchId);
    // _OesOrdCnfm::__rowNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__rowNum", __rowNum);
    // _OesOrdCnfm::__recNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__recNum", __recNum);
    // _OesOrdCnfm::__ordReqOrigRecvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqOrigRecvTime", __ordReqOrigRecvTime);
    // _OesOrdCnfm::__ordReqCollectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqCollectedTime", __ordReqCollectedTime);
    // _OesOrdCnfm::__ordReqActualDealTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqActualDealTime", __ordReqActualDealTime);
    // _OesOrdCnfm::__ordReqProcessedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqProcessedTime", __ordReqProcessedTime);
    // _OesOrdCnfm::__ordCnfmOrigRecvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmOrigRecvTime", __ordCnfmOrigRecvTime);
    // _OesOrdCnfm::__ordCnfmCollectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmCollectedTime", __ordCnfmCollectedTime);
    // _OesOrdCnfm::__ordCnfmActualDealTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmActualDealTime", __ordCnfmActualDealTime);
    // _OesOrdCnfm::__ordCnfmProcessedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmProcessedTime", __ordCnfmProcessedTime);
    // _OesOrdCnfm::__ordDeclareTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordDeclareTime", __ordDeclareTime);
    // _OesOrdCnfm::__ordDeclareDoneTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordDeclareDoneTime", __ordDeclareDoneTime);
    // _OesOrdCnfm::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__pushingTime", __pushingTime);
    generate_class_decltype_OesOrdCnfm_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdCnfm, c);
    module_vnoes::objects.emplace("_OesOrdCnfm", c);
}
void generate_class_decltype_OesOrdCnfm_userInfo_(pybind11::object & parent)
{
    // decltype(_OesOrdCnfm::userInfo)
    pybind11::class_<decltype(_OesOrdCnfm::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdCnfm::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_OesOrdCnfm::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "u64", u64);
    // decltype(_OesOrdCnfm::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "i64", i64);
    // decltype(_OesOrdCnfm::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "u32", u32);
    // decltype(_OesOrdCnfm::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "i32", i32);
    // decltype(_OesOrdCnfm::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdCnfm::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdCnfm::userInfo)", c);
}
void generate_class_OesTrdBaseInfo(pybind11::object & parent)
{
    // _OesTrdBaseInfo
    pybind11::class_<_OesTrdBaseInfo> c(parent, "_OesTrdBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesTrdBaseInfo>)
        c.def(pybind11::init<>());
    // _OesTrdBaseInfo::exchTrdNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "exchTrdNum", exchTrdNum);
    // _OesTrdBaseInfo::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "mktId", mktId);
    // _OesTrdBaseInfo::trdSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdSide", trdSide);
    // _OesTrdBaseInfo::__platformId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__platformId", __platformId);
    // _OesTrdBaseInfo::__trdCnfmType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__trdCnfmType", __trdCnfmType);
    // _OesTrdBaseInfo::__etfTrdCnfmSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__etfTrdCnfmSeq", __etfTrdCnfmSeq);
    // _OesTrdBaseInfo::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "invAcctId", invAcctId);
    // _OesTrdBaseInfo::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "securityId", securityId);
    // _OesTrdBaseInfo::trdDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdDate", trdDate);
    // _OesTrdBaseInfo::trdTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdTime", trdTime);
    // _OesTrdBaseInfo::trdQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdQty", trdQty);
    // _OesTrdBaseInfo::trdPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdPrice", trdPrice);
    // _OesTrdBaseInfo::trdAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdAmt", trdAmt);
    // _OesTrdBaseInfo::clOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "clOrdId", clOrdId);
    // _OesTrdBaseInfo::cumQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "cumQty", cumQty);
    // _OesTrdBaseInfo::__rowNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__rowNum", __rowNum);
    // _OesTrdBaseInfo::__tgwGrpNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__tgwGrpNo", __tgwGrpNo);
    // _OesTrdBaseInfo::__isTrsfInCashAvailable
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__isTrsfInCashAvailable", __isTrsfInCashAvailable);
    // _OesTrdBaseInfo::__tgwPartitionNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__tgwPartitionNo", __tgwPartitionNo);
    // _OesTrdBaseInfo::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "productType", productType);
    // _OesTrdBaseInfo::origOrdQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "origOrdQty", origOrdQty);
    // _OesTrdBaseInfo::pbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "pbuId", pbuId);
    // _OesTrdBaseInfo::branchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "branchId", branchId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTrdBaseInfo, c);
    module_vnoes::objects.emplace("_OesTrdBaseInfo", c);
}
void generate_class_OesTrdCnfm(pybind11::object & parent)
{
    // _OesTrdCnfm
    pybind11::class_<_OesTrdCnfm> c(parent, "_OesTrdCnfm");
    if constexpr (std::is_default_constructible_v<_OesTrdCnfm>)
        c.def(pybind11::init<>());
    // _OesTrdCnfm::exchTrdNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "exchTrdNum", exchTrdNum);
    // _OesTrdCnfm::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "mktId", mktId);
    // _OesTrdCnfm::trdSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdSide", trdSide);
    // _OesTrdCnfm::__platformId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__platformId", __platformId);
    // _OesTrdCnfm::__trdCnfmType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmType", __trdCnfmType);
    // _OesTrdCnfm::__etfTrdCnfmSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__etfTrdCnfmSeq", __etfTrdCnfmSeq);
    // _OesTrdCnfm::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "invAcctId", invAcctId);
    // _OesTrdCnfm::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "securityId", securityId);
    // _OesTrdCnfm::trdDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdDate", trdDate);
    // _OesTrdCnfm::trdTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdTime", trdTime);
    // _OesTrdCnfm::trdQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdQty", trdQty);
    // _OesTrdCnfm::trdPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdPrice", trdPrice);
    // _OesTrdCnfm::trdAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdAmt", trdAmt);
    // _OesTrdCnfm::clOrdId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clOrdId", clOrdId);
    // _OesTrdCnfm::cumQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumQty", cumQty);
    // _OesTrdCnfm::__rowNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__rowNum", __rowNum);
    // _OesTrdCnfm::__tgwGrpNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__tgwGrpNo", __tgwGrpNo);
    // _OesTrdCnfm::__isTrsfInCashAvailable
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__isTrsfInCashAvailable", __isTrsfInCashAvailable);
    // _OesTrdCnfm::__tgwPartitionNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__tgwPartitionNo", __tgwPartitionNo);
    // _OesTrdCnfm::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "productType", productType);
    // _OesTrdCnfm::origOrdQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "origOrdQty", origOrdQty);
    // _OesTrdCnfm::pbuId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "pbuId", pbuId);
    // _OesTrdCnfm::branchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "branchId", branchId);
    // _OesTrdCnfm::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clSeqNo", clSeqNo);
    // _OesTrdCnfm::clientId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clientId", clientId);
    // _OesTrdCnfm::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clEnvId", clEnvId);
    // _OesTrdCnfm::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "subSecurityType", subSecurityType);
    // _OesTrdCnfm::ordStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "ordStatus", ordStatus);
    // _OesTrdCnfm::ordType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "ordType", ordType);
    // _OesTrdCnfm::ordBuySellType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "ordBuySellType", ordBuySellType);
    // _OesTrdCnfm::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "securityType", securityType);
    // _OesTrdCnfm::origOrdPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "origOrdPrice", origOrdPrice);
    // _OesTrdCnfm::cumAmt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumAmt", cumAmt);
    // _OesTrdCnfm::cumInterest
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumInterest", cumInterest);
    // _OesTrdCnfm::cumFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumFee", cumFee);
    // _OesTrdCnfm::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "userInfo", userInfo);
    // _OesTrdCnfm::__trdCnfmOrigRecvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmOrigRecvTime", __trdCnfmOrigRecvTime);
    // _OesTrdCnfm::__trdCnfmCollectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmCollectedTime", __trdCnfmCollectedTime);
    // _OesTrdCnfm::__trdCnfmActualDealTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmActualDealTime", __trdCnfmActualDealTime);
    // _OesTrdCnfm::__trdCnfmProcessedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmProcessedTime", __trdCnfmProcessedTime);
    // _OesTrdCnfm::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__pushingTime", __pushingTime);
    generate_class_decltype_OesTrdCnfm_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTrdCnfm, c);
    module_vnoes::objects.emplace("_OesTrdCnfm", c);
}
