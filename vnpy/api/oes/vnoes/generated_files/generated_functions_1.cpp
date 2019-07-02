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


void generate_class_spk_struct_timespec(pybind11::object & parent)
{
    pybind11::class_<_spk_struct_timespec> c(parent, "_spk_struct_timespec");
    if constexpr (std::is_default_constructible_v<_spk_struct_timespec>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timespec, "tv_sec", tv_sec);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timespec, "tv_nsec", tv_nsec);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _spk_struct_timespec, c);
    module_vnoes::objects.emplace("_spk_struct_timespec", c);
}
void generate_class_spk_struct_timezone(pybind11::object & parent)
{
    pybind11::class_<_spk_struct_timezone> c(parent, "_spk_struct_timezone");
    if constexpr (std::is_default_constructible_v<_spk_struct_timezone>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timezone, "tz_minuteswest", tz_minuteswest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timezone, "tz_dsttime", tz_dsttime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _spk_struct_timezone, c);
    module_vnoes::objects.emplace("_spk_struct_timezone", c);
}
void generate_class_spk_struct_iovec(pybind11::object & parent)
{
    pybind11::class_<_spk_struct_iovec> c(parent, "_spk_struct_iovec");
    if constexpr (std::is_default_constructible_v<_spk_struct_iovec>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_iovec, "iov_base", iov_base);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_iovec, "iov_len", iov_len);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _spk_struct_iovec, c);
    module_vnoes::objects.emplace("_spk_struct_iovec", c);
}
void generate_class_spk_struct_timeval32(pybind11::object & parent)
{
    pybind11::class_<_spk_struct_timeval32> c(parent, "_spk_struct_timeval32");
    if constexpr (std::is_default_constructible_v<_spk_struct_timeval32>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timeval32, "tv_sec", tv_sec);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timeval32, "tv_usec", tv_usec);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _spk_struct_timeval32, c);
    module_vnoes::objects.emplace("_spk_struct_timeval32", c);
}
void generate_class_spk_struct_timeval64(pybind11::object & parent)
{
    pybind11::class_<_spk_struct_timeval64> c(parent, "_spk_struct_timeval64");
    if constexpr (std::is_default_constructible_v<_spk_struct_timeval64>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timeval64, "tv_sec", tv_sec);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _spk_struct_timeval64, "tv_usec", tv_usec);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _spk_struct_timeval64, c);
    module_vnoes::objects.emplace("_spk_struct_timeval64", c);
}
void generate_class_OesOrdReq(pybind11::object & parent)
{
    pybind11::class_<_OesOrdReq> c(parent, "_OesOrdReq");
    if constexpr (std::is_default_constructible_v<_OesOrdReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "ordQty", ordQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "ordPrice", ordPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReq, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    generate_class_decltype_OesOrdReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdReq, c);
    module_vnoes::objects.emplace("_OesOrdReq", c);
}
void generate_class_decltype_OesOrdReq_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesOrdReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdReq::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdReq::userInfo)", c);
}
void generate_class_OesOrdCancelReq(pybind11::object & parent)
{
    pybind11::class_<_OesOrdCancelReq> c(parent, "_OesOrdCancelReq");
    if constexpr (std::is_default_constructible_v<_OesOrdCancelReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "__ORD_CANCEL_BASE_INFO_filler1", __ORD_CANCEL_BASE_INFO_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "origClSeqNo", origClSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "origClEnvId", origClEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "__ORD_CANCEL_BASE_INFO_filler2", __ORD_CANCEL_BASE_INFO_filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCancelReq, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    generate_class_decltype_OesOrdCancelReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdCancelReq, c);
    module_vnoes::objects.emplace("_OesOrdCancelReq", c);
}
void generate_class_decltype_OesOrdCancelReq_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesOrdCancelReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdCancelReq::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdCancelReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdCancelReq::userInfo)", c);
}
void generate_class_OesOrdReject(pybind11::object & parent)
{
    pybind11::class_<_OesOrdReject> c(parent, "_OesOrdReject");
    if constexpr (std::is_default_constructible_v<_OesOrdReject>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordQty", ordQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordPrice", ordPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "origClSeqNo", origClSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "origClEnvId", origClEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordDate", ordDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordTime", ordTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "ordRejReason", ordRejReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdReject, "__filler", __filler);
    generate_class_decltype_OesOrdReject_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdReject, c);
    module_vnoes::objects.emplace("_OesOrdReject", c);
}
void generate_class_decltype_OesOrdReject_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesOrdReject::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdReject::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdReject::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdReject::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdReject::userInfo)", c);
}
void generate_class_OesOrdCnfm(pybind11::object & parent)
{
    pybind11::class_<_OesOrdCnfm> c(parent, "_OesOrdCnfm");
    if constexpr (std::is_default_constructible_v<_OesOrdCnfm>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordQty", ordQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordPrice", ordPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "origClEnvId", origClEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "origClSeqNo", origClSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordDate", ordDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordTime", ordTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordCnfmTime", ordCnfmTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordStatus", ordStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordCnfmSts", ordCnfmSts);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__platformId", __platformId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__tgwGrpNo", __tgwGrpNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__tgwPartitionNo", __tgwPartitionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "exchOrdId", exchOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__declareFlag", __declareFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ORD_CNFM_BASE_INFO_filler", __ORD_CNFM_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "frzAmt", frzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "frzInterest", frzInterest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "frzFee", frzFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumAmt", cumAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumInterest", cumInterest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumFee", cumFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "cumQty", cumQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "canceledQty", canceledQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "ordRejReason", ordRejReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "exchErrCode", exchErrCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__rowNum", __rowNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__recNum", __recNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqOrigRecvTime", __ordReqOrigRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqCollectedTime", __ordReqCollectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqActualDealTime", __ordReqActualDealTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordReqProcessedTime", __ordReqProcessedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmOrigRecvTime", __ordCnfmOrigRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmCollectedTime", __ordCnfmCollectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmActualDealTime", __ordCnfmActualDealTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordCnfmProcessedTime", __ordCnfmProcessedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordDeclareTime", __ordDeclareTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__ordDeclareDoneTime", __ordDeclareDoneTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesOrdCnfm, "__pushingTime", __pushingTime);
    generate_class_decltype_OesOrdCnfm_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesOrdCnfm, c);
    module_vnoes::objects.emplace("_OesOrdCnfm", c);
}
void generate_class_decltype_OesOrdCnfm_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesOrdCnfm::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesOrdCnfm::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesOrdCnfm::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesOrdCnfm::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesOrdCnfm::userInfo)", c);
}
void generate_class_OesTrdBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesTrdBaseInfo> c(parent, "_OesTrdBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesTrdBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "exchTrdNum", exchTrdNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdSide", trdSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__platformId", __platformId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__trdCnfmType", __trdCnfmType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__etfTrdCnfmSeq", __etfTrdCnfmSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdDate", trdDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdTime", trdTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdQty", trdQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdPrice", trdPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "trdAmt", trdAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "cumQty", cumQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__rowNum", __rowNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__tgwGrpNo", __tgwGrpNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__isTrsfInCashAvailable", __isTrsfInCashAvailable);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "__tgwPartitionNo", __tgwPartitionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "origOrdQty", origOrdQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdBaseInfo, "branchId", branchId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTrdBaseInfo, c);
    module_vnoes::objects.emplace("_OesTrdBaseInfo", c);
}
void generate_class_OesTrdCnfm(pybind11::object & parent)
{
    pybind11::class_<_OesTrdCnfm> c(parent, "_OesTrdCnfm");
    if constexpr (std::is_default_constructible_v<_OesTrdCnfm>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "exchTrdNum", exchTrdNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdSide", trdSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__platformId", __platformId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmType", __trdCnfmType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__etfTrdCnfmSeq", __etfTrdCnfmSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdDate", trdDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdTime", trdTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdQty", trdQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdPrice", trdPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "trdAmt", trdAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumQty", cumQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__rowNum", __rowNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__tgwGrpNo", __tgwGrpNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__isTrsfInCashAvailable", __isTrsfInCashAvailable);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__tgwPartitionNo", __tgwPartitionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "origOrdQty", origOrdQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "ordStatus", ordStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "ordBuySellType", ordBuySellType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "origOrdPrice", origOrdPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumAmt", cumAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumInterest", cumInterest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "cumFee", cumFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmOrigRecvTime", __trdCnfmOrigRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmCollectedTime", __trdCnfmCollectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmActualDealTime", __trdCnfmActualDealTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__trdCnfmProcessedTime", __trdCnfmProcessedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTrdCnfm, "__pushingTime", __pushingTime);
    generate_class_decltype_OesTrdCnfm_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTrdCnfm, c);
    module_vnoes::objects.emplace("_OesTrdCnfm", c);
}
void generate_class_decltype_OesTrdCnfm_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesTrdCnfm::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesTrdCnfm::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesTrdCnfm::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesTrdCnfm::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesTrdCnfm::userInfo)", c);
}
void generate_class_OesLotWinningBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesLotWinningBaseInfo> c(parent, "_OesLotWinningBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesLotWinningBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotType", lotType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "rejReason", rejReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "__LOT_WINNING_BASE_INFO_filler", __LOT_WINNING_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotDate", lotDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "securityName", securityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "assignNum", assignNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotQty", lotQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotPrice", lotPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesLotWinningBaseInfo, "lotAmt", lotAmt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesLotWinningBaseInfo, c);
    module_vnoes::objects.emplace("_OesLotWinningBaseInfo", c);
}
void generate_class_OesFundTrsfBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesFundTrsfBaseInfo> c(parent, "_OesFundTrsfBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "trdPasswd", trdPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "trsfPasswd", trsfPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfBaseInfo, "userInfo", userInfo);
    generate_class_decltype_OesFundTrsfBaseInfo_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfBaseInfo, c);
    module_vnoes::objects.emplace("_OesFundTrsfBaseInfo", c);
}
void generate_class_decltype_OesFundTrsfBaseInfo_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesFundTrsfBaseInfo::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfBaseInfo::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfBaseInfo::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfBaseInfo::userInfo)", c);
}
void generate_class_OesFundTrsfReq(pybind11::object & parent)
{
    pybind11::class_<_OesFundTrsfReq> c(parent, "_OesFundTrsfReq");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "trdPasswd", trdPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "trsfPasswd", trsfPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReq, "userInfo", userInfo);
    generate_class_decltype_OesFundTrsfReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfReq, c);
    module_vnoes::objects.emplace("_OesFundTrsfReq", c);
}
void generate_class_decltype_OesFundTrsfReq_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesFundTrsfReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfReq::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfReq::userInfo)", c);
}
void generate_class_OesFundTrsfReject(pybind11::object & parent)
{
    pybind11::class_<_OesFundTrsfReject> c(parent, "_OesFundTrsfReject");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfReject>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "trdPasswd", trdPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "trsfPasswd", trsfPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "ordDate", ordDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "ordTime", ordTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "rejReason", rejReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReject, "errorInfo", errorInfo);
    generate_class_decltype_OesFundTrsfReject_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfReject, c);
    module_vnoes::objects.emplace("_OesFundTrsfReject", c);
}
void generate_class_decltype_OesFundTrsfReject_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesFundTrsfReject::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfReject::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfReject::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfReject::userInfo)", c);
}
void generate_class_OesFundTrsfReport(pybind11::object & parent)
{
    pybind11::class_<_OesFundTrsfReport> c(parent, "_OesFundTrsfReport");
    if constexpr (std::is_default_constructible_v<_OesFundTrsfReport>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "fundTrsfId", fundTrsfId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "counterEntrustNo", counterEntrustNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "operDate", operDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "operTime", operTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "dclrTime", dclrTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "doneTime", doneTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "trsfStatus", trsfStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "__hasCounterTransfered", __hasCounterTransfered);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "rejReason", rejReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "counterErrCode", counterErrCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "allotSerialNo", allotSerialNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesFundTrsfReport, "errorInfo", errorInfo);
    generate_class_decltype_OesFundTrsfReport_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesFundTrsfReport, c);
    module_vnoes::objects.emplace("_OesFundTrsfReport", c);
}
void generate_class_decltype_OesFundTrsfReport_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesFundTrsfReport::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesFundTrsfReport::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesFundTrsfReport::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesFundTrsfReport::userInfo)", c);
}
void generate_class_OesIssueBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesIssueBaseInfo> c(parent, "_OesIssueBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesIssueBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "isCancelAble", isCancelAble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "isReApplyAble", isReApplyAble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "__ISSUE_BASE_filler", __ISSUE_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "securityName", securityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "underlyingSecurityId", underlyingSecurityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "startDate", startDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "endDate", endDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "issueQty", issueQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "qtyUnit", qtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "ordMaxQty", ordMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "ordMinQty", ordMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "issuePrice", issuePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "upperLimitPrice", upperLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "ceilPrice", ceilPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "lowerLimitPrice", lowerLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesIssueBaseInfo, "floorPrice", floorPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesIssueBaseInfo, c);
    module_vnoes::objects.emplace("_OesIssueBaseInfo", c);
}
void generate_class_OesPriceLimit(pybind11::object & parent)
{
    pybind11::class_<_OesPriceLimit> c(parent, "_OesPriceLimit");
    if constexpr (std::is_default_constructible_v<_OesPriceLimit>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "upperLimitPrice", upperLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "ceilPrice", ceilPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "lowerLimitPrice", lowerLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesPriceLimit, "floorPrice", floorPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesPriceLimit, c);
    module_vnoes::objects.emplace("_OesPriceLimit", c);
}
void generate_class_OesStockBaseInfo(pybind11::object & parent)
{
    pybind11::class_<_OesStockBaseInfo> c(parent, "_OesStockBaseInfo");
    if constexpr (std::is_default_constructible_v<_OesStockBaseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "productType", productType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityLevel", securityLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityRiskLevel", securityRiskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "qualificationClass", qualificationClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "isDayTrading", isDayTrading);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "suspFlag", suspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "temporarySuspFlag", temporarySuspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "__STOCK_BASE_filler", __STOCK_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "buyQtyUnit", buyQtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtBuyMaxQty", lmtBuyMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "buyOrdMaxQty", buyOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtBuyMinQty", lmtBuyMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "buyOrdMinQty", buyOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktBuyMaxQty", mktBuyMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktBuyMinQty", mktBuyMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "sellQtyUnit", sellQtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtSellMaxQty", lmtSellMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "sellOrdMaxQty", sellOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "lmtSellMinQty", lmtSellMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "sellOrdMinQty", sellOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktSellMaxQty", mktSellMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "mktSellMinQty", mktSellMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "priceTick", priceTick);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "priceUnit", priceUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "prevClose", prevClose);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "parPrice", parPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "bondInterest", bondInterest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "repoExpirationDays", repoExpirationDays);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "cashHoldDays", cashHoldDays);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "priceLimit", priceLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "securityName", securityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesStockBaseInfo, "__STOCK_BASE_reserve", __STOCK_BASE_reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesStockBaseInfo, c);
    module_vnoes::objects.emplace("_OesStockBaseInfo", c);
}
