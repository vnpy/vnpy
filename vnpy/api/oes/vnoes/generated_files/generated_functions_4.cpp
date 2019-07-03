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


void generate_class_OesQryRspMsg(pybind11::object & parent)
{
    pybind11::class_<_OesQryRspMsg> c(parent, "_OesQryRspMsg");
    if constexpr (std::is_default_constructible_v<_OesQryRspMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "ordRsp", ordRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "trdRsp", trdRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "cashAssetRsp", cashAssetRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "stkHoldingRsp", stkHoldingRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "optHoldingRsp", optHoldingRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "custRsp", custRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "invAcctRsp", invAcctRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "commsRateRsp", commsRateRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "fundTrsfRsp", fundTrsfRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "lotWinningRsp", lotWinningRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "issueRsp", issueRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "stockRsp", stockRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "etfRsp", etfRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "etfComponentRsp", etfComponentRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "optionRsp", optionRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "tradingDay", tradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "mktStateRsp", mktStateRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "clientOverview", clientOverview);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "counterCashRsp", counterCashRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryRspMsg, c);
    module_vnoes::objects.emplace("_OesQryRspMsg", c);
}
void generate_class_OesReportSynchronizationReq(pybind11::object & parent)
{
    pybind11::class_<_OesReportSynchronizationReq> c(parent, "_OesReportSynchronizationReq");
    if constexpr (std::is_default_constructible_v<_OesReportSynchronizationReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "lastRptSeqNum", lastRptSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "subscribeEnvId", subscribeEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReportSynchronizationReq, c);
    module_vnoes::objects.emplace("_OesReportSynchronizationReq", c);
}
void generate_class_OesReportSynchronizationRsp(pybind11::object & parent)
{
    pybind11::class_<_OesReportSynchronizationRsp> c(parent, "_OesReportSynchronizationRsp");
    if constexpr (std::is_default_constructible_v<_OesReportSynchronizationRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "lastRptSeqNum", lastRptSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "subscribeEnvId", subscribeEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReportSynchronizationRsp, c);
    module_vnoes::objects.emplace("_OesReportSynchronizationRsp", c);
}
void generate_class_OesTestRequestReq(pybind11::object & parent)
{
    pybind11::class_<_OesTestRequestReq> c(parent, "_OesTestRequestReq");
    if constexpr (std::is_default_constructible_v<_OesTestRequestReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "sendTime", sendTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTestRequestReq, c);
    module_vnoes::objects.emplace("_OesTestRequestReq", c);
}
void generate_class_OesTestRequestRsp(pybind11::object & parent)
{
    pybind11::class_<_OesTestRequestRsp> c(parent, "_OesTestRequestRsp");
    if constexpr (std::is_default_constructible_v<_OesTestRequestRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "origSendTime", origSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "respTime", respTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTestRequestRsp, c);
    module_vnoes::objects.emplace("_OesTestRequestRsp", c);
}
void generate_class_OesChangePasswordReq(pybind11::object & parent)
{
    pybind11::class_<_OesChangePasswordReq> c(parent, "_OesChangePasswordReq");
    if constexpr (std::is_default_constructible_v<_OesChangePasswordReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "oldPassword", oldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordReq, "newPassword", newPassword);
    generate_class_decltype_OesChangePasswordReq_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesChangePasswordReq, c);
    module_vnoes::objects.emplace("_OesChangePasswordReq", c);
}
void generate_class_decltype_OesChangePasswordReq_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesChangePasswordReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesChangePasswordReq::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesChangePasswordReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesChangePasswordReq::userInfo)", c);
}
void generate_class_OesChangePasswordRsp(pybind11::object & parent)
{
    pybind11::class_<_OesChangePasswordRsp> c(parent, "_OesChangePasswordRsp");
    if constexpr (std::is_default_constructible_v<_OesChangePasswordRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "transDate", transDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "transTime", transTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesChangePasswordRsp, "rejReason", rejReason);
    generate_class_decltype_OesChangePasswordRsp_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesChangePasswordRsp, c);
    module_vnoes::objects.emplace("_OesChangePasswordRsp", c);
}
void generate_class_decltype_OesChangePasswordRsp_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_OesChangePasswordRsp::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_OesChangePasswordRsp::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_OesChangePasswordRsp::userInfo), c);
    module_vnoes::objects.emplace("decltype(_OesChangePasswordRsp::userInfo)", c);
}
void generate_class_OesBatchOrdersHead(pybind11::object & parent)
{
    pybind11::class_<_OesBatchOrdersHead> c(parent, "_OesBatchOrdersHead");
    if constexpr (std::is_default_constructible_v<_OesBatchOrdersHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersHead, "itemCount", itemCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersHead, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesBatchOrdersHead, c);
    module_vnoes::objects.emplace("_OesBatchOrdersHead", c);
}
void generate_class_OesBatchOrdersReq(pybind11::object & parent)
{
    pybind11::class_<_OesBatchOrdersReq> c(parent, "_OesBatchOrdersReq");
    if constexpr (std::is_default_constructible_v<_OesBatchOrdersReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersReq, "batchHead", batchHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesBatchOrdersReq, "items", items);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesBatchOrdersReq, c);
    module_vnoes::objects.emplace("_OesBatchOrdersReq", c);
}
void generate_class_OesRptMsgHead(pybind11::object & parent)
{
    pybind11::class_<_OesRptMsgHead> c(parent, "_OesRptMsgHead");
    if constexpr (std::is_default_constructible_v<_OesRptMsgHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "rptSeqNum", rptSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "rptMsgType", rptMsgType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "execType", execType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "bodyLength", bodyLength);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "ordRejReason", ordRejReason);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRptMsgHead, c);
    module_vnoes::objects.emplace("_OesRptMsgHead", c);
}
void generate_class_OesRptMsgBody(pybind11::object & parent)
{
    pybind11::class_<_OesRptMsgBody> c(parent, "_OesRptMsgBody");
    if constexpr (std::is_default_constructible_v<_OesRptMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "ordInsertRsp", ordInsertRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "ordRejectRsp", ordRejectRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "ordCnfm", ordCnfm);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "trdCnfm", trdCnfm);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "fundTrsfRejectRsp", fundTrsfRejectRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "fundTrsfCnfm", fundTrsfCnfm);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "cashAssetRpt", cashAssetRpt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "stkHoldingRpt", stkHoldingRpt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "optHoldingRpt", optHoldingRpt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRptMsgBody, c);
    module_vnoes::objects.emplace("_OesRptMsgBody", c);
}
void generate_class_OesRptMsg(pybind11::object & parent)
{
    pybind11::class_<_OesRptMsg> c(parent, "_OesRptMsg");
    if constexpr (std::is_default_constructible_v<_OesRptMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsg, "rptHead", rptHead);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsg, "rptBody", rptBody);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRptMsg, c);
    module_vnoes::objects.emplace("_OesRptMsg", c);
}
void generate_class_OesReqMsgBody(pybind11::object & parent)
{
    pybind11::class_<_OesReqMsgBody> c(parent, "_OesReqMsgBody");
    if constexpr (std::is_default_constructible_v<_OesReqMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "ordReq", ordReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "ordCancelReq", ordCancelReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "batchOrdersReq", batchOrdersReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "fundTrsfReq", fundTrsfReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "changePasswordReq", changePasswordReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "testRequestReq", testRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "rptSyncReq", rptSyncReq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReqMsgBody, c);
    module_vnoes::objects.emplace("_OesReqMsgBody", c);
}
void generate_class_OesRspMsgBody(pybind11::object & parent)
{
    pybind11::class_<_OesRspMsgBody> c(parent, "_OesRspMsgBody");
    if constexpr (std::is_default_constructible_v<_OesRspMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "rptMsg", rptMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "mktStateRpt", mktStateRpt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "changePasswordRsp", changePasswordRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "testRequestRsp", testRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "reportSynchronizationRsp", reportSynchronizationRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRspMsgBody, c);
    module_vnoes::objects.emplace("_OesRspMsgBody", c);
}
void generate_class_SErrMsg(pybind11::object & parent)
{
    pybind11::class_<_SErrMsg> c(parent, "_SErrMsg");
    if constexpr (std::is_default_constructible_v<_SErrMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "__index", __index);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "MODULE", MODULE);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "CODE", CODE);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "__errCode", __errCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "__msgSize", __msgSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "MSG", MSG);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SErrMsg, c);
    module_vnoes::objects.emplace("_SErrMsg", c);
}
void generate_class_SDataBuffer(pybind11::object & parent)
{
    pybind11::class_<_SDataBuffer> c(parent, "_SDataBuffer");
    if constexpr (std::is_default_constructible_v<_SDataBuffer>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "dataSize", dataSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "bufSize", bufSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "buffer", buffer);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "__ref", __ref);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SDataBuffer, c);
    module_vnoes::objects.emplace("_SDataBuffer", c);
}
void generate_class_SDataBufferVar(pybind11::object & parent)
{
    pybind11::class_<_SDataBufferVar> c(parent, "_SDataBufferVar");
    if constexpr (std::is_default_constructible_v<_SDataBufferVar>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "dataSize", dataSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "bufSize", bufSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "buffer", buffer);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "__ref", __ref);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SDataBufferVar, c);
    module_vnoes::objects.emplace("_SDataBufferVar", c);
}
void generate_class_SSocketUriInfo(pybind11::object & parent)
{
    pybind11::class_<_SSocketUriInfo> c(parent, "_SSocketUriInfo");
    if constexpr (std::is_default_constructible_v<_SSocketUriInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketUriInfo, "uri", uri);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketUriInfo, c);
    module_vnoes::objects.emplace("_SSocketUriInfo", c);
}
void generate_class_SSocketIpPortInfo(pybind11::object & parent)
{
    pybind11::class_<_SSocketIpPortInfo> c(parent, "_SSocketIpPortInfo");
    if constexpr (std::is_default_constructible_v<_SSocketIpPortInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketIpPortInfo, "port", port);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketIpPortInfo, "ip", ip);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketIpPortInfo, c);
    module_vnoes::objects.emplace("_SSocketIpPortInfo", c);
}
void generate_class_SSocketChannelInfo(pybind11::object & parent)
{
    pybind11::class_<_SSocketChannelInfo> c(parent, "_SSocketChannelInfo");
    if constexpr (std::is_default_constructible_v<_SSocketChannelInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "socketFd", socketFd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "__socket_fd_filler", __socket_fd_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "remotePort", remotePort);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "protocolType", protocolType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "_isNetByteOrder", _isNetByteOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "_isBroken", _isBroken);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "_isSendBroken", _isSendBroken);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "remoteAddr", remoteAddr);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketChannelInfo, c);
    module_vnoes::objects.emplace("_SSocketChannelInfo", c);
}
void generate_class_SSocketOptionConfig(pybind11::object & parent)
{
    pybind11::class_<_SSocketOptionConfig> c(parent, "_SSocketOptionConfig");
    if constexpr (std::is_default_constructible_v<_SSocketOptionConfig>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "soRcvbuf", soRcvbuf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "soSndbuf", soSndbuf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "tcpNodelay", tcpNodelay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "quickAck", quickAck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "mcastTtlNum", mcastTtlNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "mcastLoopbackDisabled", mcastLoopbackDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "soBacklog", soBacklog);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "connTimeoutMs", connTimeoutMs);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepIdle", keepIdle);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepIntvl", keepIntvl);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepalive", keepalive);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepCnt", keepCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "localSendingPort", localSendingPort);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "localSendingIp", localSendingIp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "mcastInterfaceIp", mcastInterfaceIp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketOptionConfig, c);
    module_vnoes::objects.emplace("_SSocketOptionConfig", c);
}
void generate_class_SGeneralClientChannel(pybind11::object & parent)
{
    pybind11::class_<_SGeneralClientChannel> c(parent, "_SGeneralClientChannel");
    if constexpr (std::is_default_constructible_v<_SGeneralClientChannel>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "socketFd", socketFd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__socket_fd_filler", __socket_fd_filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "testReqInt", testReqInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "protocolType", protocolType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "remoteSetNum", remoteSetNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "remoteHostNum", remoteHostNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "remoteIsLeader", remoteIsLeader);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "leaderHostNum", leaderHostNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__codecBuf", __codecBuf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__recvBuf", __recvBuf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__pDataStartPoint", __pDataStartPoint);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__customPtr", __customPtr);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__reavedSize", __reavedSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__customFlag", __customFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__totalInMsgSize", __totalInMsgSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__totalCompressedSize", __totalCompressedSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__totalDecompressSize", __totalDecompressSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "firstInMsgSeq", firstInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastInMsgSeq", lastInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "nextInMsgSeq", nextInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastRecvTime", lastRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "channel", channel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "nextOutMsgSeq", nextOutMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastOutMsgSeq", lastOutMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastSendTime", lastSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "senderCompId", senderCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__magicNumber", __magicNumber);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__magicSize", __magicSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__channelType", __channelType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__clEnvId", __clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__groupFlag", __groupFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__protocolHints", __protocolHints);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__reserveData", __reserveData);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__extData", __extData);
    generate_class_decltype_SGeneralClientChannel_reserveData_(c);
    generate_class_decltype_SGeneralClientChannel_extData_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientChannel, c);
    module_vnoes::objects.emplace("_SGeneralClientChannel", c);
}
void generate_class_decltype_SGeneralClientChannel_reserveData_(pybind11::object & parent)
{
    pybind11::class_<decltype(_SGeneralClientChannel::__reserveData)> c(parent, "decltype(__reserveData)");
    if constexpr (std::is_default_constructible_v<decltype(_SGeneralClientChannel::__reserveData)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "buf", buf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i8", i8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u8", u8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i16", i16);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u16", u16);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "ptr", ptr);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "__padding", __padding);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), c);
    module_vnoes::objects.emplace("decltype(_SGeneralClientChannel::__reserveData)", c);
}
void generate_class_decltype_SGeneralClientChannel_extData_(pybind11::object & parent)
{
    pybind11::class_<decltype(_SGeneralClientChannel::__extData)> c(parent, "decltype(__extData)");
    if constexpr (std::is_default_constructible_v<decltype(_SGeneralClientChannel::__extData)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "buf", buf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i8", i8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u8", u8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i16", i16);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u16", u16);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "ptr", ptr);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_SGeneralClientChannel::__extData), c);
    module_vnoes::objects.emplace("decltype(_SGeneralClientChannel::__extData)", c);
}
void generate_class_SGeneralClientChannelGroup(pybind11::object & parent)
{
    pybind11::class_<_SGeneralClientChannelGroup> c(parent, "_SGeneralClientChannelGroup");
    if constexpr (std::is_default_constructible_v<_SGeneralClientChannelGroup>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "channelCount", channelCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__customFlag", __customFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "channelList", channelList);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__maxFd", __maxFd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__maxFdCnt", __maxFdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__groupFlag", __groupFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__fdArray", __fdArray);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__fdSet", __fdSet);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientChannelGroup, c);
    module_vnoes::objects.emplace("_SGeneralClientChannelGroup", c);
}
void generate_class_SGeneralClientAddrInfo(pybind11::object & parent)
{
    pybind11::class_<_SGeneralClientAddrInfo> c(parent, "_SGeneralClientAddrInfo");
    if constexpr (std::is_default_constructible_v<_SGeneralClientAddrInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "uri", uri);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "hostNum", hostNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientAddrInfo, c);
    module_vnoes::objects.emplace("_SGeneralClientAddrInfo", c);
}
void generate_class_SGeneralClientRemoteCfg(pybind11::object & parent)
{
    pybind11::class_<_SGeneralClientRemoteCfg> c(parent, "_SGeneralClientRemoteCfg");
    if constexpr (std::is_default_constructible_v<_SGeneralClientRemoteCfg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "addrCnt", addrCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "clusterType", clusterType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "senderCompId", senderCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "addrList", addrList);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "socketOpt", socketOpt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientRemoteCfg, c);
    module_vnoes::objects.emplace("_SGeneralClientRemoteCfg", c);
}
void generate_class_OesApiSubscribeInfo(pybind11::object & parent)
{
    pybind11::class_<_OesApiSubscribeInfo> c(parent, "_OesApiSubscribeInfo");
    if constexpr (std::is_default_constructible_v<_OesApiSubscribeInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "rptTypes", rptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiSubscribeInfo, c);
    module_vnoes::objects.emplace("_OesApiSubscribeInfo", c);
}
void generate_class_OesApiClientCfg(pybind11::object & parent)
{
    pybind11::class_<_OesApiClientCfg> c(parent, "_OesApiClientCfg");
    if constexpr (std::is_default_constructible_v<_OesApiClientCfg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "ordChannelCfg", ordChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "rptChannelCfg", rptChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "qryChannelCfg", qryChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientCfg, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiClientCfg, c);
    module_vnoes::objects.emplace("_OesApiClientCfg", c);
}
void generate_class_OesApiClientEnv(pybind11::object & parent)
{
    pybind11::class_<_OesApiClientEnv> c(parent, "_OesApiClientEnv");
    if constexpr (std::is_default_constructible_v<_OesApiClientEnv>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "ordChannel", ordChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "rptChannel", rptChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiClientEnv, "qryChannel", qryChannel);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiClientEnv, c);
    module_vnoes::objects.emplace("_OesApiClientEnv", c);
}
void generate_class_MdsTradingSessionStatusMsg(pybind11::object & parent)
{
    pybind11::class_<_MdsTradingSessionStatusMsg> c(parent, "_MdsTradingSessionStatusMsg");
    if constexpr (std::is_default_constructible_v<_MdsTradingSessionStatusMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "mdProductType", mdProductType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__mdsRecvTime", __mdsRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "TotNoRelatedSym", TotNoRelatedSym);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "TradingSessionID", TradingSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsTradingSessionStatusMsg, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsTradingSessionStatusMsg, c);
    module_vnoes::objects.emplace("_MdsTradingSessionStatusMsg", c);
}
void generate_class_MdsSecurityStatusMsg(pybind11::object & parent)
{
    pybind11::class_<_MdsSecurityStatusMsg> c(parent, "_MdsSecurityStatusMsg");
    if constexpr (std::is_default_constructible_v<_MdsSecurityStatusMsg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "mdProductType", mdProductType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__mdsRecvTime", __mdsRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "FinancialStatus", FinancialStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "NoSwitch", NoSwitch);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__filler4", __filler4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "switches", switches);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsSecurityStatusMsg, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsSecurityStatusMsg, c);
    module_vnoes::objects.emplace("_MdsSecurityStatusMsg", c);
}
void generate_class_MdsPriceLevelEntry(pybind11::object & parent)
{
    pybind11::class_<_MdsPriceLevelEntry> c(parent, "_MdsPriceLevelEntry");
    if constexpr (std::is_default_constructible_v<_MdsPriceLevelEntry>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "NumberOfOrders", NumberOfOrders);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsPriceLevelEntry, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsPriceLevelEntry, c);
    module_vnoes::objects.emplace("_MdsPriceLevelEntry", c);
}
void generate_class_MdsMktDataSnapshotHead(pybind11::object & parent)
{
    pybind11::class_<_MdsMktDataSnapshotHead> c(parent, "_MdsMktDataSnapshotHead");
    if constexpr (std::is_default_constructible_v<_MdsMktDataSnapshotHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "mdProductType", mdProductType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origMdSource", __origMdSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "bodyLength", bodyLength);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "mdStreamType", mdStreamType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__lastUpdateTime", __lastUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktDataSnapshotHead, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktDataSnapshotHead, c);
    module_vnoes::objects.emplace("_MdsMktDataSnapshotHead", c);
}
