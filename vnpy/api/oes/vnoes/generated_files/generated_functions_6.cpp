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


void generate_class_OesRptMsgHead(pybind11::object & parent)
{
    // _OesRptMsgHead
    pybind11::class_<_OesRptMsgHead> c(parent, "_OesRptMsgHead");
    if constexpr (std::is_default_constructible_v<_OesRptMsgHead>)
        c.def(pybind11::init<>());
    // _OesRptMsgHead::rptSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "rptSeqNum", rptSeqNum);
    // _OesRptMsgHead::rptMsgType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "rptMsgType", rptMsgType);
    // _OesRptMsgHead::execType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "execType", execType);
    // _OesRptMsgHead::bodyLength
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "bodyLength", bodyLength);
    // _OesRptMsgHead::ordRejReason
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgHead, "ordRejReason", ordRejReason);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRptMsgHead, c);
    module_vnoes::objects.emplace("_OesRptMsgHead", c);
}
void generate_class_OesRptMsgBody(pybind11::object & parent)
{
    // _OesRptMsgBody
    pybind11::class_<_OesRptMsgBody> c(parent, "_OesRptMsgBody");
    if constexpr (std::is_default_constructible_v<_OesRptMsgBody>)
        c.def(pybind11::init<>());
    // _OesRptMsgBody::ordInsertRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "ordInsertRsp", ordInsertRsp);
    // _OesRptMsgBody::ordRejectRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "ordRejectRsp", ordRejectRsp);
    // _OesRptMsgBody::ordCnfm
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "ordCnfm", ordCnfm);
    // _OesRptMsgBody::trdCnfm
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "trdCnfm", trdCnfm);
    // _OesRptMsgBody::fundTrsfRejectRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "fundTrsfRejectRsp", fundTrsfRejectRsp);
    // _OesRptMsgBody::fundTrsfCnfm
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "fundTrsfCnfm", fundTrsfCnfm);
    // _OesRptMsgBody::cashAssetRpt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "cashAssetRpt", cashAssetRpt);
    // _OesRptMsgBody::stkHoldingRpt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "stkHoldingRpt", stkHoldingRpt);
    // _OesRptMsgBody::optHoldingRpt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsgBody, "optHoldingRpt", optHoldingRpt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRptMsgBody, c);
    module_vnoes::objects.emplace("_OesRptMsgBody", c);
}
void generate_class_OesRptMsg(pybind11::object & parent)
{
    // _OesRptMsg
    pybind11::class_<_OesRptMsg> c(parent, "_OesRptMsg");
    if constexpr (std::is_default_constructible_v<_OesRptMsg>)
        c.def(pybind11::init<>());
    // _OesRptMsg::rptHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsg, "rptHead", rptHead);
    // _OesRptMsg::rptBody
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRptMsg, "rptBody", rptBody);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRptMsg, c);
    module_vnoes::objects.emplace("_OesRptMsg", c);
}
void generate_class_OesReqMsgBody(pybind11::object & parent)
{
    // _OesReqMsgBody
    pybind11::class_<_OesReqMsgBody> c(parent, "_OesReqMsgBody");
    if constexpr (std::is_default_constructible_v<_OesReqMsgBody>)
        c.def(pybind11::init<>());
    // _OesReqMsgBody::ordReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "ordReq", ordReq);
    // _OesReqMsgBody::ordCancelReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "ordCancelReq", ordCancelReq);
    // _OesReqMsgBody::batchOrdersReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "batchOrdersReq", batchOrdersReq);
    // _OesReqMsgBody::fundTrsfReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "fundTrsfReq", fundTrsfReq);
    // _OesReqMsgBody::changePasswordReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "changePasswordReq", changePasswordReq);
    // _OesReqMsgBody::testRequestReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "testRequestReq", testRequestReq);
    // _OesReqMsgBody::rptSyncReq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReqMsgBody, "rptSyncReq", rptSyncReq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReqMsgBody, c);
    module_vnoes::objects.emplace("_OesReqMsgBody", c);
}
void generate_class_OesRspMsgBody(pybind11::object & parent)
{
    // _OesRspMsgBody
    pybind11::class_<_OesRspMsgBody> c(parent, "_OesRspMsgBody");
    if constexpr (std::is_default_constructible_v<_OesRspMsgBody>)
        c.def(pybind11::init<>());
    // _OesRspMsgBody::rptMsg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "rptMsg", rptMsg);
    // _OesRspMsgBody::mktStateRpt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "mktStateRpt", mktStateRpt);
    // _OesRspMsgBody::changePasswordRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "changePasswordRsp", changePasswordRsp);
    // _OesRspMsgBody::testRequestRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "testRequestRsp", testRequestRsp);
    // _OesRspMsgBody::reportSynchronizationRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesRspMsgBody, "reportSynchronizationRsp", reportSynchronizationRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesRspMsgBody, c);
    module_vnoes::objects.emplace("_OesRspMsgBody", c);
}
void generate_class_SErrMsg(pybind11::object & parent)
{
    // _SErrMsg
    pybind11::class_<_SErrMsg> c(parent, "_SErrMsg");
    if constexpr (std::is_default_constructible_v<_SErrMsg>)
        c.def(pybind11::init<>());
    // _SErrMsg::__index
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "__index", __index);
    // _SErrMsg::MODULE
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "MODULE", MODULE);
    // _SErrMsg::CODE
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "CODE", CODE);
    // _SErrMsg::__errCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "__errCode", __errCode);
    // _SErrMsg::__msgSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "__msgSize", __msgSize);
    // _SErrMsg::MSG
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SErrMsg, "MSG", MSG);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SErrMsg, c);
    module_vnoes::objects.emplace("_SErrMsg", c);
}
void generate_class_SDataBuffer(pybind11::object & parent)
{
    // _SDataBuffer
    pybind11::class_<_SDataBuffer> c(parent, "_SDataBuffer");
    if constexpr (std::is_default_constructible_v<_SDataBuffer>)
        c.def(pybind11::init<>());
    // _SDataBuffer::dataSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "dataSize", dataSize);
    // _SDataBuffer::bufSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "bufSize", bufSize);
    // _SDataBuffer::buffer
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "buffer", buffer);
    // _SDataBuffer::__ref
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBuffer, "__ref", __ref);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SDataBuffer, c);
    module_vnoes::objects.emplace("_SDataBuffer", c);
}
void generate_class_SDataBufferVar(pybind11::object & parent)
{
    // _SDataBufferVar
    pybind11::class_<_SDataBufferVar> c(parent, "_SDataBufferVar");
    if constexpr (std::is_default_constructible_v<_SDataBufferVar>)
        c.def(pybind11::init<>());
    // _SDataBufferVar::dataSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "dataSize", dataSize);
    // _SDataBufferVar::bufSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "bufSize", bufSize);
    // _SDataBufferVar::buffer
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "buffer", buffer);
    // _SDataBufferVar::__ref
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SDataBufferVar, "__ref", __ref);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SDataBufferVar, c);
    module_vnoes::objects.emplace("_SDataBufferVar", c);
}
void generate_class_SSocketUriInfo(pybind11::object & parent)
{
    // _SSocketUriInfo
    pybind11::class_<_SSocketUriInfo> c(parent, "_SSocketUriInfo");
    if constexpr (std::is_default_constructible_v<_SSocketUriInfo>)
        c.def(pybind11::init<>());
    // _SSocketUriInfo::uri
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketUriInfo, "uri", uri);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketUriInfo, c);
    module_vnoes::objects.emplace("_SSocketUriInfo", c);
}
void generate_class_SSocketIpPortInfo(pybind11::object & parent)
{
    // _SSocketIpPortInfo
    pybind11::class_<_SSocketIpPortInfo> c(parent, "_SSocketIpPortInfo");
    if constexpr (std::is_default_constructible_v<_SSocketIpPortInfo>)
        c.def(pybind11::init<>());
    // _SSocketIpPortInfo::port
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketIpPortInfo, "port", port);
    // _SSocketIpPortInfo::ip
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketIpPortInfo, "ip", ip);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketIpPortInfo, c);
    module_vnoes::objects.emplace("_SSocketIpPortInfo", c);
}
void generate_class_SSocketChannelInfo(pybind11::object & parent)
{
    // _SSocketChannelInfo
    pybind11::class_<_SSocketChannelInfo> c(parent, "_SSocketChannelInfo");
    if constexpr (std::is_default_constructible_v<_SSocketChannelInfo>)
        c.def(pybind11::init<>());
    // _SSocketChannelInfo::socketFd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "socketFd", socketFd);
    // _SSocketChannelInfo::__socket_fd_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "__socket_fd_filler", __socket_fd_filler);
    // _SSocketChannelInfo::remotePort
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "remotePort", remotePort);
    // _SSocketChannelInfo::protocolType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "protocolType", protocolType);
    // _SSocketChannelInfo::_isNetByteOrder
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "_isNetByteOrder", _isNetByteOrder);
    // _SSocketChannelInfo::_isBroken
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "_isBroken", _isBroken);
    // _SSocketChannelInfo::_isSendBroken
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "_isSendBroken", _isSendBroken);
    // _SSocketChannelInfo::remoteAddr
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketChannelInfo, "remoteAddr", remoteAddr);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketChannelInfo, c);
    module_vnoes::objects.emplace("_SSocketChannelInfo", c);
}
void generate_class_SSocketOptionConfig(pybind11::object & parent)
{
    // _SSocketOptionConfig
    pybind11::class_<_SSocketOptionConfig> c(parent, "_SSocketOptionConfig");
    if constexpr (std::is_default_constructible_v<_SSocketOptionConfig>)
        c.def(pybind11::init<>());
    // _SSocketOptionConfig::soRcvbuf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "soRcvbuf", soRcvbuf);
    // _SSocketOptionConfig::soSndbuf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "soSndbuf", soSndbuf);
    // _SSocketOptionConfig::tcpNodelay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "tcpNodelay", tcpNodelay);
    // _SSocketOptionConfig::quickAck
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "quickAck", quickAck);
    // _SSocketOptionConfig::mcastTtlNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "mcastTtlNum", mcastTtlNum);
    // _SSocketOptionConfig::mcastLoopbackDisabled
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "mcastLoopbackDisabled", mcastLoopbackDisabled);
    // _SSocketOptionConfig::soBacklog
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "soBacklog", soBacklog);
    // _SSocketOptionConfig::connTimeoutMs
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "connTimeoutMs", connTimeoutMs);
    // _SSocketOptionConfig::keepIdle
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepIdle", keepIdle);
    // _SSocketOptionConfig::keepIntvl
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepIntvl", keepIntvl);
    // _SSocketOptionConfig::keepalive
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepalive", keepalive);
    // _SSocketOptionConfig::keepCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "keepCnt", keepCnt);
    // _SSocketOptionConfig::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "__filler", __filler);
    // _SSocketOptionConfig::localSendingPort
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "localSendingPort", localSendingPort);
    // _SSocketOptionConfig::localSendingIp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "localSendingIp", localSendingIp);
    // _SSocketOptionConfig::mcastInterfaceIp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SSocketOptionConfig, "mcastInterfaceIp", mcastInterfaceIp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SSocketOptionConfig, c);
    module_vnoes::objects.emplace("_SSocketOptionConfig", c);
}
void generate_class_SGeneralClientChannel(pybind11::object & parent)
{
    // _SGeneralClientChannel
    pybind11::class_<_SGeneralClientChannel> c(parent, "_SGeneralClientChannel");
    if constexpr (std::is_default_constructible_v<_SGeneralClientChannel>)
        c.def(pybind11::init<>());
    // _SGeneralClientChannel::socketFd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "socketFd", socketFd);
    // _SGeneralClientChannel::__socket_fd_filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__socket_fd_filler", __socket_fd_filler);
    // _SGeneralClientChannel::heartBtInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "heartBtInt", heartBtInt);
    // _SGeneralClientChannel::testReqInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "testReqInt", testReqInt);
    // _SGeneralClientChannel::protocolType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "protocolType", protocolType);
    // _SGeneralClientChannel::remoteSetNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "remoteSetNum", remoteSetNum);
    // _SGeneralClientChannel::remoteHostNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "remoteHostNum", remoteHostNum);
    // _SGeneralClientChannel::remoteIsLeader
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "remoteIsLeader", remoteIsLeader);
    // _SGeneralClientChannel::leaderHostNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "leaderHostNum", leaderHostNum);
    // _SGeneralClientChannel::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__filler1", __filler1);
    // _SGeneralClientChannel::__codecBuf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__codecBuf", __codecBuf);
    // _SGeneralClientChannel::__recvBuf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__recvBuf", __recvBuf);
    // _SGeneralClientChannel::__pDataStartPoint
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__pDataStartPoint", __pDataStartPoint);
    // _SGeneralClientChannel::__customPtr
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__customPtr", __customPtr);
    // _SGeneralClientChannel::__reavedSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__reavedSize", __reavedSize);
    // _SGeneralClientChannel::__customFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__customFlag", __customFlag);
    // _SGeneralClientChannel::__totalInMsgSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__totalInMsgSize", __totalInMsgSize);
    // _SGeneralClientChannel::__totalCompressedSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__totalCompressedSize", __totalCompressedSize);
    // _SGeneralClientChannel::__totalDecompressSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__totalDecompressSize", __totalDecompressSize);
    // _SGeneralClientChannel::firstInMsgSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "firstInMsgSeq", firstInMsgSeq);
    // _SGeneralClientChannel::lastInMsgSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastInMsgSeq", lastInMsgSeq);
    // _SGeneralClientChannel::nextInMsgSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "nextInMsgSeq", nextInMsgSeq);
    // _SGeneralClientChannel::lastRecvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastRecvTime", lastRecvTime);
    // _SGeneralClientChannel::channel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "channel", channel);
    // _SGeneralClientChannel::nextOutMsgSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "nextOutMsgSeq", nextOutMsgSeq);
    // _SGeneralClientChannel::lastOutMsgSeq
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastOutMsgSeq", lastOutMsgSeq);
    // _SGeneralClientChannel::lastSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "lastSendTime", lastSendTime);
    // _SGeneralClientChannel::senderCompId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "senderCompId", senderCompId);
    // _SGeneralClientChannel::targetCompId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "targetCompId", targetCompId);
    // _SGeneralClientChannel::__magicNumber
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__magicNumber", __magicNumber);
    // _SGeneralClientChannel::__magicSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__magicSize", __magicSize);
    // _SGeneralClientChannel::__channelType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__channelType", __channelType);
    // _SGeneralClientChannel::__clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__clEnvId", __clEnvId);
    // _SGeneralClientChannel::__groupFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__groupFlag", __groupFlag);
    // _SGeneralClientChannel::__protocolHints
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__protocolHints", __protocolHints);
    // _SGeneralClientChannel::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__filler", __filler);
    // _SGeneralClientChannel::__reserveData
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__reserveData", __reserveData);
    // _SGeneralClientChannel::__extData
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannel, "__extData", __extData);
    generate_class_decltype_SGeneralClientChannel_reserveData_(c);
    generate_class_decltype_SGeneralClientChannel_extData_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientChannel, c);
    module_vnoes::objects.emplace("_SGeneralClientChannel", c);
}
void generate_class_decltype_SGeneralClientChannel_reserveData_(pybind11::object & parent)
{
    // decltype(_SGeneralClientChannel::__reserveData)
    pybind11::class_<decltype(_SGeneralClientChannel::__reserveData)> c(parent, "decltype(__reserveData)");
    if constexpr (std::is_default_constructible_v<decltype(_SGeneralClientChannel::__reserveData)>)
        c.def(pybind11::init<>());
    // decltype(_SGeneralClientChannel::__reserveData)::buf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "buf", buf);
    // decltype(_SGeneralClientChannel::__reserveData)::i8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i8", i8);
    // decltype(_SGeneralClientChannel::__reserveData)::u8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u8", u8);
    // decltype(_SGeneralClientChannel::__reserveData)::i16
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i16", i16);
    // decltype(_SGeneralClientChannel::__reserveData)::u16
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u16", u16);
    // decltype(_SGeneralClientChannel::__reserveData)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i32", i32);
    // decltype(_SGeneralClientChannel::__reserveData)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u32", u32);
    // decltype(_SGeneralClientChannel::__reserveData)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "i64", i64);
    // decltype(_SGeneralClientChannel::__reserveData)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "u64", u64);
    // decltype(_SGeneralClientChannel::__reserveData)::ptr
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "ptr", ptr);
    // decltype(_SGeneralClientChannel::__reserveData)::__padding
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), "__padding", __padding);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_SGeneralClientChannel::__reserveData), c);
    module_vnoes::objects.emplace("decltype(_SGeneralClientChannel::__reserveData)", c);
}
void generate_class_decltype_SGeneralClientChannel_extData_(pybind11::object & parent)
{
    // decltype(_SGeneralClientChannel::__extData)
    pybind11::class_<decltype(_SGeneralClientChannel::__extData)> c(parent, "decltype(__extData)");
    if constexpr (std::is_default_constructible_v<decltype(_SGeneralClientChannel::__extData)>)
        c.def(pybind11::init<>());
    // decltype(_SGeneralClientChannel::__extData)::buf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "buf", buf);
    // decltype(_SGeneralClientChannel::__extData)::i8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i8", i8);
    // decltype(_SGeneralClientChannel::__extData)::u8
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u8", u8);
    // decltype(_SGeneralClientChannel::__extData)::i16
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i16", i16);
    // decltype(_SGeneralClientChannel::__extData)::u16
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u16", u16);
    // decltype(_SGeneralClientChannel::__extData)::i32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i32", i32);
    // decltype(_SGeneralClientChannel::__extData)::u32
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u32", u32);
    // decltype(_SGeneralClientChannel::__extData)::i64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "i64", i64);
    // decltype(_SGeneralClientChannel::__extData)::u64
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "u64", u64);
    // decltype(_SGeneralClientChannel::__extData)::ptr
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_SGeneralClientChannel::__extData), "ptr", ptr);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_SGeneralClientChannel::__extData), c);
    module_vnoes::objects.emplace("decltype(_SGeneralClientChannel::__extData)", c);
}
void generate_class_SGeneralClientChannelGroup(pybind11::object & parent)
{
    // _SGeneralClientChannelGroup
    pybind11::class_<_SGeneralClientChannelGroup> c(parent, "_SGeneralClientChannelGroup");
    if constexpr (std::is_default_constructible_v<_SGeneralClientChannelGroup>)
        c.def(pybind11::init<>());
    // _SGeneralClientChannelGroup::channelCount
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "channelCount", channelCount);
    // _SGeneralClientChannelGroup::__customFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__customFlag", __customFlag);
    // _SGeneralClientChannelGroup::channelList
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "channelList", channelList);
    // _SGeneralClientChannelGroup::__maxFd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__maxFd", __maxFd);
    // _SGeneralClientChannelGroup::__maxFdCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__maxFdCnt", __maxFdCnt);
    // _SGeneralClientChannelGroup::__groupFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__groupFlag", __groupFlag);
    // _SGeneralClientChannelGroup::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__filler", __filler);
    // _SGeneralClientChannelGroup::__fdArray
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__fdArray", __fdArray);
    // _SGeneralClientChannelGroup::__fdSet
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientChannelGroup, "__fdSet", __fdSet);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientChannelGroup, c);
    module_vnoes::objects.emplace("_SGeneralClientChannelGroup", c);
}
void generate_class_SGeneralClientAddrInfo(pybind11::object & parent)
{
    // _SGeneralClientAddrInfo
    pybind11::class_<_SGeneralClientAddrInfo> c(parent, "_SGeneralClientAddrInfo");
    if constexpr (std::is_default_constructible_v<_SGeneralClientAddrInfo>)
        c.def(pybind11::init<>());
    // _SGeneralClientAddrInfo::uri
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "uri", uri);
    // _SGeneralClientAddrInfo::targetCompId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "targetCompId", targetCompId);
    // _SGeneralClientAddrInfo::username
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "username", username);
    // _SGeneralClientAddrInfo::password
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "password", password);
    // _SGeneralClientAddrInfo::hostNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "hostNum", hostNum);
    // _SGeneralClientAddrInfo::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientAddrInfo, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientAddrInfo, c);
    module_vnoes::objects.emplace("_SGeneralClientAddrInfo", c);
}
void generate_class_SGeneralClientRemoteCfg(pybind11::object & parent)
{
    // _SGeneralClientRemoteCfg
    pybind11::class_<_SGeneralClientRemoteCfg> c(parent, "_SGeneralClientRemoteCfg");
    if constexpr (std::is_default_constructible_v<_SGeneralClientRemoteCfg>)
        c.def(pybind11::init<>());
    // _SGeneralClientRemoteCfg::addrCnt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "addrCnt", addrCnt);
    // _SGeneralClientRemoteCfg::heartBtInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "heartBtInt", heartBtInt);
    // _SGeneralClientRemoteCfg::clusterType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "clusterType", clusterType);
    // _SGeneralClientRemoteCfg::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "clEnvId", clEnvId);
    // _SGeneralClientRemoteCfg::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "__filler", __filler);
    // _SGeneralClientRemoteCfg::senderCompId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "senderCompId", senderCompId);
    // _SGeneralClientRemoteCfg::targetCompId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "targetCompId", targetCompId);
    // _SGeneralClientRemoteCfg::username
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "username", username);
    // _SGeneralClientRemoteCfg::password
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "password", password);
    // _SGeneralClientRemoteCfg::addrList
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "addrList", addrList);
    // _SGeneralClientRemoteCfg::socketOpt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _SGeneralClientRemoteCfg, "socketOpt", socketOpt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _SGeneralClientRemoteCfg, c);
    module_vnoes::objects.emplace("_SGeneralClientRemoteCfg", c);
}
void generate_class_OesApiSubscribeInfo(pybind11::object & parent)
{
    // _OesApiSubscribeInfo
    pybind11::class_<_OesApiSubscribeInfo> c(parent, "_OesApiSubscribeInfo");
    if constexpr (std::is_default_constructible_v<_OesApiSubscribeInfo>)
        c.def(pybind11::init<>());
    // _OesApiSubscribeInfo::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "clEnvId", clEnvId);
    // _OesApiSubscribeInfo::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "__filler", __filler);
    // _OesApiSubscribeInfo::rptTypes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesApiSubscribeInfo, "rptTypes", rptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesApiSubscribeInfo, c);
    module_vnoes::objects.emplace("_OesApiSubscribeInfo", c);
}
