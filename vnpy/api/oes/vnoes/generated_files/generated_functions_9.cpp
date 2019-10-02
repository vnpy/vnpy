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


void generate_class_MdsMktDataRequestReq(pybind11::object & parent)
{
    // _MdsMktDataRequestReq
    pybind11::class_<_MdsMktDataRequestReq> c(parent, "_MdsMktDataRequestReq");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestReq>)
        c.def(pybind11::init<>());
    // _MdsMktDataRequestReq::subMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "subMode", subMode);
    // _MdsMktDataRequestReq::tickType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "tickType", tickType);
    // _MdsMktDataRequestReq::sseStockFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "sseStockFlag", sseStockFlag);
    // _MdsMktDataRequestReq::sseIndexFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "sseIndexFlag", sseIndexFlag);
    // _MdsMktDataRequestReq::sseOptionFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "sseOptionFlag", sseOptionFlag);
    // _MdsMktDataRequestReq::szseStockFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "szseStockFlag", szseStockFlag);
    // _MdsMktDataRequestReq::szseIndexFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "szseIndexFlag", szseIndexFlag);
    // _MdsMktDataRequestReq::szseOptionFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "szseOptionFlag", szseOptionFlag);
    // _MdsMktDataRequestReq::isRequireInitialMktData
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "isRequireInitialMktData", isRequireInitialMktData);
    // _MdsMktDataRequestReq::__channelNos
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "__channelNos", __channelNos);
    // _MdsMktDataRequestReq::tickExpireType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "tickExpireType", tickExpireType);
    // _MdsMktDataRequestReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "__filler", __filler);
    // _MdsMktDataRequestReq::dataTypes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "dataTypes", dataTypes);
    // _MdsMktDataRequestReq::beginTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "beginTime", beginTime);
    // _MdsMktDataRequestReq::subSecurityCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReq, "subSecurityCnt", subSecurityCnt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestReq, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestReq", c);
}
void generate_class_MdsMktDataRequestReqBuf(pybind11::object & parent)
{
    // _MdsMktDataRequestReqBuf
    pybind11::class_<_MdsMktDataRequestReqBuf> c(parent, "_MdsMktDataRequestReqBuf");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestReqBuf>)
        c.def(pybind11::init<>());
    // _MdsMktDataRequestReqBuf::mktDataRequestReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReqBuf, "mktDataRequestReq", mktDataRequestReq);
    // _MdsMktDataRequestReqBuf::entries
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestReqBuf, "entries", entries);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestReqBuf, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestReqBuf", c);
}
void generate_class_MdsMktDataRequestRsp(pybind11::object & parent)
{
    // _MdsMktDataRequestRsp
    pybind11::class_<_MdsMktDataRequestRsp> c(parent, "_MdsMktDataRequestRsp");
    if constexpr (std::is_default_constructible_v<_MdsMktDataRequestRsp>)
        c.def(pybind11::init<>());
    // _MdsMktDataRequestRsp::subMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "subMode", subMode);
    // _MdsMktDataRequestRsp::tickType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "tickType", tickType);
    // _MdsMktDataRequestRsp::isRequireInitialMktData
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "isRequireInitialMktData", isRequireInitialMktData);
    // _MdsMktDataRequestRsp::__channelNos
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "__channelNos", __channelNos);
    // _MdsMktDataRequestRsp::tickExpireType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "tickExpireType", tickExpireType);
    // _MdsMktDataRequestRsp::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "__filler", __filler);
    // _MdsMktDataRequestRsp::dataTypes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "dataTypes", dataTypes);
    // _MdsMktDataRequestRsp::beginTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "beginTime", beginTime);
    // _MdsMktDataRequestRsp::sseStockSubscribed
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "sseStockSubscribed", sseStockSubscribed);
    // _MdsMktDataRequestRsp::sseIndexSubscribed
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "sseIndexSubscribed", sseIndexSubscribed);
    // _MdsMktDataRequestRsp::sseOptionSubscribed
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "sseOptionSubscribed", sseOptionSubscribed);
    // _MdsMktDataRequestRsp::szseStockSubscribed
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "szseStockSubscribed", szseStockSubscribed);
    // _MdsMktDataRequestRsp::szseIndexSubscribed
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "szseIndexSubscribed", szseIndexSubscribed);
    // _MdsMktDataRequestRsp::szseOptionSubscribed
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataRequestRsp, "szseOptionSubscribed", szseOptionSubscribed);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataRequestRsp, c);
    module_vnoes::objects.emplace("_MdsMktDataRequestRsp", c);
}
void generate_class_MdsTestRequestReq(pybind11::object & parent)
{
    // _MdsTestRequestReq
    pybind11::class_<_MdsTestRequestReq> c(parent, "_MdsTestRequestReq");
    if constexpr (std::is_default_constructible_v<_MdsTestRequestReq>)
        c.def(pybind11::init<>());
    // _MdsTestRequestReq::testReqId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestReq, "testReqId", testReqId);
    // _MdsTestRequestReq::sendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestReq, "sendTime", sendTime);
    // _MdsTestRequestReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsTestRequestReq, c);
    module_vnoes::objects.emplace("_MdsTestRequestReq", c);
}
void generate_class_MdsTestRequestRsp(pybind11::object & parent)
{
    // _MdsTestRequestRsp
    pybind11::class_<_MdsTestRequestRsp> c(parent, "_MdsTestRequestRsp");
    if constexpr (std::is_default_constructible_v<_MdsTestRequestRsp>)
        c.def(pybind11::init<>());
    // _MdsTestRequestRsp::testReqId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "testReqId", testReqId);
    // _MdsTestRequestRsp::origSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "origSendTime", origSendTime);
    // _MdsTestRequestRsp::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__filler1", __filler1);
    // _MdsTestRequestRsp::respTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "respTime", respTime);
    // _MdsTestRequestRsp::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__filler2", __filler2);
    // _MdsTestRequestRsp::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__recvTime", __recvTime);
    // _MdsTestRequestRsp::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__collectedTime", __collectedTime);
    // _MdsTestRequestRsp::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTestRequestRsp, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsTestRequestRsp, c);
    module_vnoes::objects.emplace("_MdsTestRequestRsp", c);
}
void generate_class_MdsChangePasswordReq(pybind11::object & parent)
{
    // _MdsChangePasswordReq
    pybind11::class_<_MdsChangePasswordReq> c(parent, "_MdsChangePasswordReq");
    if constexpr (std::is_default_constructible_v<_MdsChangePasswordReq>)
        c.def(pybind11::init<>());
    // _MdsChangePasswordReq::encryptMethod
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "encryptMethod", encryptMethod);
    // _MdsChangePasswordReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "__filler", __filler);
    // _MdsChangePasswordReq::username
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "username", username);
    // _MdsChangePasswordReq::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "userInfo", userInfo);
    // _MdsChangePasswordReq::oldPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "oldPassword", oldPassword);
    // _MdsChangePasswordReq::newPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordReq, "newPassword", newPassword);
    generate_class_decltype_MdsChangePasswordReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsChangePasswordReq, c);
    module_vnoes::objects.emplace("_MdsChangePasswordReq", c);
}
void generate_class_decltype_MdsChangePasswordReq_userInfo_(pybind11::object & parent)
{
    // decltype(_MdsChangePasswordReq::userInfo)
    pybind11::class_<decltype(_MdsChangePasswordReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_MdsChangePasswordReq::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_MdsChangePasswordReq::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "u64", u64);
    // decltype(_MdsChangePasswordReq::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "i64", i64);
    // decltype(_MdsChangePasswordReq::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "u32", u32);
    // decltype(_MdsChangePasswordReq::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "i32", i32);
    // decltype(_MdsChangePasswordReq::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_MdsChangePasswordReq::userInfo)", c);
}
void generate_class_MdsChangePasswordRsp(pybind11::object & parent)
{
    // _MdsChangePasswordRsp
    pybind11::class_<_MdsChangePasswordRsp> c(parent, "_MdsChangePasswordRsp");
    if constexpr (std::is_default_constructible_v<_MdsChangePasswordRsp>)
        c.def(pybind11::init<>());
    // _MdsChangePasswordRsp::encryptMethod
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "encryptMethod", encryptMethod);
    // _MdsChangePasswordRsp::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "__filler", __filler);
    // _MdsChangePasswordRsp::username
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "username", username);
    // _MdsChangePasswordRsp::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "userInfo", userInfo);
    // _MdsChangePasswordRsp::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "__filler2", __filler2);
    // _MdsChangePasswordRsp::transDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "transDate", transDate);
    // _MdsChangePasswordRsp::transTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "transTime", transTime);
    // _MdsChangePasswordRsp::rejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "rejReason", rejReason);
    generate_class_decltype_MdsChangePasswordRsp_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsChangePasswordRsp, c);
    module_vnoes::objects.emplace("_MdsChangePasswordRsp", c);
}
void generate_class_decltype_MdsChangePasswordRsp_userInfo_(pybind11::object & parent)
{
    // decltype(_MdsChangePasswordRsp::userInfo)
    pybind11::class_<decltype(_MdsChangePasswordRsp::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_MdsChangePasswordRsp::userInfo)>)
        c.def(pybind11::init<>());
    // decltype(_MdsChangePasswordRsp::userInfo)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "u64", u64);
    // decltype(_MdsChangePasswordRsp::userInfo)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "i64", i64);
    // decltype(_MdsChangePasswordRsp::userInfo)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "u32", u32);
    // decltype(_MdsChangePasswordRsp::userInfo)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "i32", i32);
    // decltype(_MdsChangePasswordRsp::userInfo)::c8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), c);
    module_vnoes::objects.emplace("decltype(_MdsChangePasswordRsp::userInfo)", c);
}
void generate_class_MdsMktReqMsgBody(pybind11::object & parent)
{
    // _MdsMktReqMsgBody
    pybind11::class_<_MdsMktReqMsgBody> c(parent, "_MdsMktReqMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsMktReqMsgBody>)
        c.def(pybind11::init<>());
    // _MdsMktReqMsgBody::wholeMktDataReqBuf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "wholeMktDataReqBuf", wholeMktDataReqBuf);
    // _MdsMktReqMsgBody::mktDataRequestReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "mktDataRequestReq", mktDataRequestReq);
    // _MdsMktReqMsgBody::testRequestReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "testRequestReq", testRequestReq);
    // _MdsMktReqMsgBody::qryMktDataSnapshotReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryMktDataSnapshotReq", qryMktDataSnapshotReq);
    // _MdsMktReqMsgBody::qrySecurityStatusReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qrySecurityStatusReq", qrySecurityStatusReq);
    // _MdsMktReqMsgBody::qryTrdSessionStatusReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryTrdSessionStatusReq", qryTrdSessionStatusReq);
    // _MdsMktReqMsgBody::qryStockStaticInfoReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryStockStaticInfoReq", qryStockStaticInfoReq);
    // _MdsMktReqMsgBody::qrySnapshotListReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qrySnapshotListReq", qrySnapshotListReq);
    // _MdsMktReqMsgBody::changePasswordReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "changePasswordReq", changePasswordReq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktReqMsgBody, c);
    module_vnoes::objects.emplace("_MdsMktReqMsgBody", c);
}
void generate_class_MdsMktRspMsgBody(pybind11::object & parent)
{
    // _MdsMktRspMsgBody
    pybind11::class_<_MdsMktRspMsgBody> c(parent, "_MdsMktRspMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsMktRspMsgBody>)
        c.def(pybind11::init<>());
    // _MdsMktRspMsgBody::mktDataRequestRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "mktDataRequestRsp", mktDataRequestRsp);
    // _MdsMktRspMsgBody::testRequestRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "testRequestRsp", testRequestRsp);
    // _MdsMktRspMsgBody::mktDataSnapshot
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "mktDataSnapshot", mktDataSnapshot);
    // _MdsMktRspMsgBody::trade
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "trade", trade);
    // _MdsMktRspMsgBody::order
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "order", order);
    // _MdsMktRspMsgBody::trdSessionStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "trdSessionStatus", trdSessionStatus);
    // _MdsMktRspMsgBody::securityStatus
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "securityStatus", securityStatus);
    // _MdsMktRspMsgBody::qryStockStaticInfoRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "qryStockStaticInfoRsp", qryStockStaticInfoRsp);
    // _MdsMktRspMsgBody::qrySnapshotListRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "qrySnapshotListRsp", qrySnapshotListRsp);
    // _MdsMktRspMsgBody::changePasswordRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "changePasswordRsp", changePasswordRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktRspMsgBody, c);
    module_vnoes::objects.emplace("_MdsMktRspMsgBody", c);
}
void generate_class_MdsUdpPktHead(pybind11::object & parent)
{
    // _MdsUdpPktHead
    pybind11::class_<_MdsUdpPktHead> c(parent, "_MdsUdpPktHead");
    if constexpr (std::is_default_constructible_v<_MdsUdpPktHead>)
        c.def(pybind11::init<>());
    // _MdsUdpPktHead::msgCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "msgCnt", msgCnt);
    // _MdsUdpPktHead::pktSiz
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "pktSiz", pktSiz);
    // _MdsUdpPktHead::pktSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "pktSeq", pktSeq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsUdpPktHead, c);
    module_vnoes::objects.emplace("_MdsUdpPktHead", c);
}
void generate_class_MdsApiClientCfg(pybind11::object & parent)
{
    // _MdsApiClientCfg
    pybind11::class_<_MdsApiClientCfg> c(parent, "_MdsApiClientCfg");
    if constexpr (std::is_default_constructible_v<_MdsApiClientCfg>)
        c.def(pybind11::init<>());
    // _MdsApiClientCfg::tcpChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "tcpChannelCfg", tcpChannelCfg);
    // _MdsApiClientCfg::qryChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "qryChannelCfg", qryChannelCfg);
    // _MdsApiClientCfg::udpL1ChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpL1ChannelCfg", udpL1ChannelCfg);
    // _MdsApiClientCfg::udpL2ChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpL2ChannelCfg", udpL2ChannelCfg);
    // _MdsApiClientCfg::udpTick1ChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpTick1ChannelCfg", udpTick1ChannelCfg);
    // _MdsApiClientCfg::udpTradeChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpTradeChannelCfg", udpTradeChannelCfg);
    // _MdsApiClientCfg::udpTick2ChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpTick2ChannelCfg", udpTick2ChannelCfg);
    // _MdsApiClientCfg::udpOrderChannelCfg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpOrderChannelCfg", udpOrderChannelCfg);
    // _MdsApiClientCfg::subscribeInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsApiClientCfg, c);
    module_vnoes::objects.emplace("_MdsApiClientCfg", c);
}
void generate_class_MdsApiClientEnv(pybind11::object & parent)
{
    // _MdsApiClientEnv
    pybind11::class_<_MdsApiClientEnv> c(parent, "_MdsApiClientEnv");
    if constexpr (std::is_default_constructible_v<_MdsApiClientEnv>)
        c.def(pybind11::init<>());
    // _MdsApiClientEnv::tcpChannel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "tcpChannel", tcpChannel);
    // _MdsApiClientEnv::qryChannel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "qryChannel", qryChannel);
    // _MdsApiClientEnv::udpL1Channel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpL1Channel", udpL1Channel);
    // _MdsApiClientEnv::udpL2Channel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpL2Channel", udpL2Channel);
    // _MdsApiClientEnv::udpTick1Channel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpTick1Channel", udpTick1Channel);
    // _MdsApiClientEnv::udpTradeChannel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpTradeChannel", udpTradeChannel);
    // _MdsApiClientEnv::udpTick2Channel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpTick2Channel", udpTick2Channel);
    // _MdsApiClientEnv::udpOrderChannel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpOrderChannel", udpOrderChannel);
    // _MdsApiClientEnv::udpChannelGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpChannelGroup", udpChannelGroup);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsApiClientEnv, c);
    module_vnoes::objects.emplace("_MdsApiClientEnv", c);
}
