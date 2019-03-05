#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "class_generators.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"
#include "mds_api/parser/json_parser/mds_json_parser.h"
#include "custom/wrapper.hpp"


void generate_class_OesEtfComponentItemT(pybind11::module &m)
{
    pybind11::class_<OesEtfComponentItemT> c(m, "OesEtfComponentItemT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "subFlag", subFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "prevClose", prevClose);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "premiumRate", premiumRate);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "creationSubCash", creationSubCash);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "redemptionCashSub", redemptionCashSub);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentItemT, "fundId", fundId);
    AUTOCXXPY_POST_REGISTER_CLASS(OesEtfComponentItemT, c);
}
void generate_class_OesQryEtfComponentReqT(pybind11::module &m)
{
    pybind11::class_<OesQryEtfComponentReqT> c(m, "OesQryEtfComponentReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfComponentReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfComponentReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryEtfComponentReqT, c);
}
void generate_class_OesQryEtfComponentRspT(pybind11::module &m)
{
    pybind11::class_<OesQryEtfComponentRspT> c(m, "OesQryEtfComponentRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfComponentRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfComponentRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryEtfComponentRspT, c);
}
void generate_class_OesQryOptionFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryOptionFilterT> c(m, "OesQryOptionFilterT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionFilterT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOptionFilterT, c);
}
void generate_class_OesQryOptionReqT(pybind11::module &m)
{
    pybind11::class_<OesQryOptionReqT> c(m, "OesQryOptionReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOptionReqT, c);
}
void generate_class_OesQryOptionRspT(pybind11::module &m)
{
    pybind11::class_<OesQryOptionRspT> c(m, "OesQryOptionRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptionRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOptionRspT, c);
}
void generate_class_OesQryTradingDayRspT(pybind11::module &m)
{
    pybind11::class_<OesQryTradingDayRspT> c(m, "OesQryTradingDayRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTradingDayRspT, "tradingDay", tradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTradingDayRspT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryTradingDayRspT, c);
}
void generate_class_OesQryMarketStateFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryMarketStateFilterT> c(m, "OesQryMarketStateFilterT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateFilterT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateFilterT, "platformId", platformId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryMarketStateFilterT, c);
}
void generate_class_OesQryMarketStateReqT(pybind11::module &m)
{
    pybind11::class_<OesQryMarketStateReqT> c(m, "OesQryMarketStateReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryMarketStateReqT, c);
}
void generate_class_OesQryMarketStateRspT(pybind11::module &m)
{
    pybind11::class_<OesQryMarketStateRspT> c(m, "OesQryMarketStateRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryMarketStateRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryMarketStateRspT, c);
}
void generate_class_OesQryReqMsgT(pybind11::module &m)
{
    pybind11::class_<OesQryReqMsgT> c(m, "OesQryReqMsgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryOrd", qryOrd);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryTrd", qryTrd);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryCashAsset", qryCashAsset);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryStkHolding", qryStkHolding);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryOptHolding", qryOptHolding);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryCust", qryCust);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryInvAcct", qryInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryComms", qryComms);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryFundTrsf", qryFundTrsf);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryLotWinning", qryLotWinning);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryIssue", qryIssue);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryStock", qryStock);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryEtf", qryEtf);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryEtfComponent", qryEtfComponent);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryOption", qryOption);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryMktState", qryMktState);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqMsgT, "qryCounterCash", qryCounterCash);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryReqMsgT, c);
}
void generate_class_OesQryRspMsgT(pybind11::module &m)
{
    pybind11::class_<OesQryRspMsgT> c(m, "OesQryRspMsgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "ordRsp", ordRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "trdRsp", trdRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "cashAssetRsp", cashAssetRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "stkHoldingRsp", stkHoldingRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "optHoldingRsp", optHoldingRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "custRsp", custRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "invAcctRsp", invAcctRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "commsRateRsp", commsRateRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "fundTrsfRsp", fundTrsfRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "lotWinningRsp", lotWinningRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "issueRsp", issueRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "stockRsp", stockRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "etfRsp", etfRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "etfComponentRsp", etfComponentRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "optionRsp", optionRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "tradingDay", tradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "mktStateRsp", mktStateRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "clientOverview", clientOverview);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspMsgT, "counterCashRsp", counterCashRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryRspMsgT, c);
}
void generate_class_OesLogonReqT(pybind11::module &m)
{
    pybind11::class_<OesLogonReqT> c(m, "OesLogonReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "applVerId", applVerId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "clientIp", clientIp);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "clientMac", clientMac);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "sourceType", sourceType);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "__protocolHints", __protocolHints);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "lastInMsgSeq", lastInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "lastOutMsgSeq", lastOutMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonReqT, "clientDriverId", clientDriverId);
    AUTOCXXPY_POST_REGISTER_CLASS(OesLogonReqT, c);
}
void generate_class_OesLogonRspT(pybind11::module &m)
{
    pybind11::class_<OesLogonRspT> c(m, "OesLogonRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "applVerId", applVerId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "minVerId", minVerId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "hostNum", hostNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "isLeader", isLeader);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "leaderHostNum", leaderHostNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "clientType", clientType);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "clientStatus", clientStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "__protocolHints", __protocolHints);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "lastInMsgSeq", lastInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(OesLogonRspT, "lastOutMsgSeq", lastOutMsgSeq);
    AUTOCXXPY_POST_REGISTER_CLASS(OesLogonRspT, c);
}
void generate_class_OesReportSynchronizationReqT(pybind11::module &m)
{
    pybind11::class_<OesReportSynchronizationReqT> c(m, "OesReportSynchronizationReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationReqT, "lastRptSeqNum", lastRptSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationReqT, "subscribeEnvId", subscribeEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationReqT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationReqT, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(OesReportSynchronizationReqT, c);
}
void generate_class_OesReportSynchronizationRspT(pybind11::module &m)
{
    pybind11::class_<OesReportSynchronizationRspT> c(m, "OesReportSynchronizationRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationRspT, "lastRptSeqNum", lastRptSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationRspT, "subscribeEnvId", subscribeEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationRspT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesReportSynchronizationRspT, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(OesReportSynchronizationRspT, c);
}
void generate_class_OesTestRequestReqT(pybind11::module &m)
{
    pybind11::class_<OesTestRequestReqT> c(m, "OesTestRequestReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestReqT, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestReqT, "sendTime", sendTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestReqT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(OesTestRequestReqT, c);
}
void generate_class_OesTestRequestRspT(pybind11::module &m)
{
    pybind11::class_<OesTestRequestRspT> c(m, "OesTestRequestRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "origSendTime", origSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "respTime", respTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTestRequestRspT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(OesTestRequestRspT, c);
}
void generate_class_OesChangePasswordReqT(pybind11::module &m)
{
    pybind11::class_<OesChangePasswordReqT> c(m, "OesChangePasswordReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordReqT, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordReqT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordReqT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordReqT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordReqT, "oldPassword", oldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordReqT, "newPassword", newPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(OesChangePasswordReqT, c);
}
void generate_class_OesChangePasswordRspT(pybind11::module &m)
{
    pybind11::class_<OesChangePasswordRspT> c(m, "OesChangePasswordRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "transDate", transDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "transTime", transTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesChangePasswordRspT, "rejReason", rejReason);
    AUTOCXXPY_POST_REGISTER_CLASS(OesChangePasswordRspT, c);
}
void generate_class_OesBatchOrdersHeadT(pybind11::module &m)
{
    pybind11::class_<OesBatchOrdersHeadT> c(m, "OesBatchOrdersHeadT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesBatchOrdersHeadT, "itemCount", itemCount);
    c.AUTOCXXPY_DEF_PROPERTY(OesBatchOrdersHeadT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(OesBatchOrdersHeadT, c);
}
void generate_class_OesBatchOrdersReqT(pybind11::module &m)
{
    pybind11::class_<OesBatchOrdersReqT> c(m, "OesBatchOrdersReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesBatchOrdersReqT, "batchHead", batchHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesBatchOrdersReqT, "items", items);
    AUTOCXXPY_POST_REGISTER_CLASS(OesBatchOrdersReqT, c);
}
void generate_class_OesRptMsgHeadT(pybind11::module &m)
{
    pybind11::class_<OesRptMsgHeadT> c(m, "OesRptMsgHeadT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgHeadT, "rptSeqNum", rptSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgHeadT, "rptMsgType", rptMsgType);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgHeadT, "execType", execType);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgHeadT, "bodyLength", bodyLength);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgHeadT, "ordRejReason", ordRejReason);
    AUTOCXXPY_POST_REGISTER_CLASS(OesRptMsgHeadT, c);
}
void generate_class_OesRptMsgBodyT(pybind11::module &m)
{
    pybind11::class_<OesRptMsgBodyT> c(m, "OesRptMsgBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "ordInsertRsp", ordInsertRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "ordRejectRsp", ordRejectRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "ordCnfm", ordCnfm);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "trdCnfm", trdCnfm);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "fundTrsfRejectRsp", fundTrsfRejectRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "fundTrsfCnfm", fundTrsfCnfm);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "cashAssetRpt", cashAssetRpt);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "stkHoldingRpt", stkHoldingRpt);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgBodyT, "optHoldingRpt", optHoldingRpt);
    AUTOCXXPY_POST_REGISTER_CLASS(OesRptMsgBodyT, c);
}
void generate_class_OesRptMsgT(pybind11::module &m)
{
    pybind11::class_<OesRptMsgT> c(m, "OesRptMsgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgT, "rptHead", rptHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesRptMsgT, "rptBody", rptBody);
    AUTOCXXPY_POST_REGISTER_CLASS(OesRptMsgT, c);
}
void generate_class_OesReqMsgBodyT(pybind11::module &m)
{
    pybind11::class_<OesReqMsgBodyT> c(m, "OesReqMsgBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "ordReq", ordReq);
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "ordCancelReq", ordCancelReq);
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "batchOrdersReq", batchOrdersReq);
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "fundTrsfReq", fundTrsfReq);
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "changePasswordReq", changePasswordReq);
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "testRequestReq", testRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "rptSyncReq", rptSyncReq);
    c.AUTOCXXPY_DEF_PROPERTY(OesReqMsgBodyT, "logonReq", logonReq);
    AUTOCXXPY_POST_REGISTER_CLASS(OesReqMsgBodyT, c);
}
void generate_class_OesRspMsgBodyT(pybind11::module &m)
{
    pybind11::class_<OesRspMsgBodyT> c(m, "OesRspMsgBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesRspMsgBodyT, "rptMsg", rptMsg);
    c.AUTOCXXPY_DEF_PROPERTY(OesRspMsgBodyT, "mktStateRpt", mktStateRpt);
    c.AUTOCXXPY_DEF_PROPERTY(OesRspMsgBodyT, "changePasswordRsp", changePasswordRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesRspMsgBodyT, "testRequestRsp", testRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesRspMsgBodyT, "reportSynchronizationRsp", reportSynchronizationRsp);
    c.AUTOCXXPY_DEF_PROPERTY(OesRspMsgBodyT, "logonRsp", logonRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(OesRspMsgBodyT, c);
}
void generate_class_SErrMsgT(pybind11::module &m)
{
    pybind11::class_<SErrMsgT> c(m, "SErrMsgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SErrMsgT, "__index", __index);
    c.AUTOCXXPY_DEF_PROPERTY(SErrMsgT, "MODULE", MODULE);
    c.AUTOCXXPY_DEF_PROPERTY(SErrMsgT, "CODE", CODE);
    c.AUTOCXXPY_DEF_PROPERTY(SErrMsgT, "__errCode", __errCode);
    c.AUTOCXXPY_DEF_PROPERTY(SErrMsgT, "__msgSize", __msgSize);
    c.AUTOCXXPY_DEF_PROPERTY(SErrMsgT, "MSG", MSG);
    AUTOCXXPY_POST_REGISTER_CLASS(SErrMsgT, c);
}
void generate_class_SDataBufferT(pybind11::module &m)
{
    pybind11::class_<SDataBufferT> c(m, "SDataBufferT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SDataBufferT, "dataSize", dataSize);
    c.AUTOCXXPY_DEF_PROPERTY(SDataBufferT, "bufSize", bufSize);
    c.AUTOCXXPY_DEF_PROPERTY(SDataBufferT, "buffer", buffer);
    c.AUTOCXXPY_DEF_PROPERTY(SDataBufferT, "__ref", __ref);
    AUTOCXXPY_POST_REGISTER_CLASS(SDataBufferT, c);
}
void generate_class__SDataBufferVar(pybind11::module &m)
{
    pybind11::class_<_SDataBufferVar> c(m, "_SDataBufferVar");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(_SDataBufferVar, "dataSize", dataSize);
    c.AUTOCXXPY_DEF_PROPERTY(_SDataBufferVar, "bufSize", bufSize);
    c.AUTOCXXPY_DEF_PROPERTY(_SDataBufferVar, "buffer", buffer);
    c.AUTOCXXPY_DEF_PROPERTY(_SDataBufferVar, "__ref", __ref);
    AUTOCXXPY_POST_REGISTER_CLASS(_SDataBufferVar, c);
}
void generate_class_SSocketUriInfoT(pybind11::module &m)
{
    pybind11::class_<SSocketUriInfoT> c(m, "SSocketUriInfoT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SSocketUriInfoT, "uri", uri);
    AUTOCXXPY_POST_REGISTER_CLASS(SSocketUriInfoT, c);
}
void generate_class_SSocketIpPortInfoT(pybind11::module &m)
{
    pybind11::class_<SSocketIpPortInfoT> c(m, "SSocketIpPortInfoT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SSocketIpPortInfoT, "port", port);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketIpPortInfoT, "ip", ip);
    AUTOCXXPY_POST_REGISTER_CLASS(SSocketIpPortInfoT, c);
}
void generate_class_SSocketChannelInfoT(pybind11::module &m)
{
    pybind11::class_<SSocketChannelInfoT> c(m, "SSocketChannelInfoT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SSocketChannelInfoT, "remotePort", remotePort);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketChannelInfoT, "protocolType", protocolType);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketChannelInfoT, "_isNetByteOrder", _isNetByteOrder);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketChannelInfoT, "_isBroken", _isBroken);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketChannelInfoT, "_isSendBroken", _isSendBroken);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketChannelInfoT, "remoteAddr", remoteAddr);
    AUTOCXXPY_POST_REGISTER_CLASS(SSocketChannelInfoT, c);
}
void generate_class_SSocketOptionConfigT(pybind11::module &m)
{
    pybind11::class_<SSocketOptionConfigT> c(m, "SSocketOptionConfigT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "soRcvbuf", soRcvbuf);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "soSndbuf", soSndbuf);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "tcpNodelay", tcpNodelay);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "quickAck", quickAck);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "mcastTtlNum", mcastTtlNum);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "mcastLoopbackDisabled", mcastLoopbackDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "soBacklog", soBacklog);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "connTimeoutMs", connTimeoutMs);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "keepIdle", keepIdle);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "keepIntvl", keepIntvl);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "keepalive", keepalive);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "keepCnt", keepCnt);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "localSendingPort", localSendingPort);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "localSendingIp", localSendingIp);
    c.AUTOCXXPY_DEF_PROPERTY(SSocketOptionConfigT, "mcastInterfaceIp", mcastInterfaceIp);
    AUTOCXXPY_POST_REGISTER_CLASS(SSocketOptionConfigT, c);
}
void generate_class_SGeneralClientChannelT(pybind11::module &m)
{
    pybind11::class_<SGeneralClientChannelT> c(m, "SGeneralClientChannelT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "testReqInt", testReqInt);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "protocolType", protocolType);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "remoteHostNum", remoteHostNum);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "remoteIsLeader", remoteIsLeader);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "leaderHostNum", leaderHostNum);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__codecBuf", __codecBuf);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__recvBuf", __recvBuf);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__pDataStartPoint", __pDataStartPoint);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__customPtr", __customPtr);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__reavedSize", __reavedSize);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__customFlag", __customFlag);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__totalInMsgSize", __totalInMsgSize);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__totalCompressedSize", __totalCompressedSize);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__totalDecompressSize", __totalDecompressSize);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "firstInMsgSeq", firstInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "lastInMsgSeq", lastInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "nextInMsgSeq", nextInMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "lastRecvTime", lastRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "channel", channel);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "nextOutMsgSeq", nextOutMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "lastOutMsgSeq", lastOutMsgSeq);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "lastSendTime", lastSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "senderCompId", senderCompId);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__magicNumber", __magicNumber);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__magicSize", __magicSize);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__channelType", __channelType);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__clEnvId", __clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__groupFlag", __groupFlag);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__protocolHints", __protocolHints);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__reserveData", __reserveData);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelT, "__extData", __extData);
    AUTOCXXPY_POST_REGISTER_CLASS(SGeneralClientChannelT, c);
}
void generate_class_SGeneralClientChannelGroupT(pybind11::module &m)
{
    pybind11::class_<SGeneralClientChannelGroupT> c(m, "SGeneralClientChannelGroupT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelGroupT, "channelCount", channelCount);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelGroupT, "__customFlag", __customFlag);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelGroupT, "channelList", channelList);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelGroupT, "__maxFd", __maxFd);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelGroupT, "__groupFlag", __groupFlag);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelGroupT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientChannelGroupT, "__fdSet", __fdSet);
    AUTOCXXPY_POST_REGISTER_CLASS(SGeneralClientChannelGroupT, c);
}
void generate_class_SGeneralClientAddrInfoT(pybind11::module &m)
{
    pybind11::class_<SGeneralClientAddrInfoT> c(m, "SGeneralClientAddrInfoT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientAddrInfoT, "uri", uri);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientAddrInfoT, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientAddrInfoT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientAddrInfoT, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientAddrInfoT, "hostNum", hostNum);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientAddrInfoT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(SGeneralClientAddrInfoT, c);
}
void generate_class_SGeneralClientRemoteCfgT(pybind11::module &m)
{
    pybind11::class_<SGeneralClientRemoteCfgT> c(m, "SGeneralClientRemoteCfgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "addrCnt", addrCnt);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "clusterType", clusterType);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "senderCompId", senderCompId);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "targetCompId", targetCompId);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "addrList", addrList);
    c.AUTOCXXPY_DEF_PROPERTY(SGeneralClientRemoteCfgT, "socketOpt", socketOpt);
    AUTOCXXPY_POST_REGISTER_CLASS(SGeneralClientRemoteCfgT, c);
}
void generate_class_OesApiSubscribeInfoT(pybind11::module &m)
{
    pybind11::class_<OesApiSubscribeInfoT> c(m, "OesApiSubscribeInfoT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesApiSubscribeInfoT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesApiSubscribeInfoT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesApiSubscribeInfoT, "rptTypes", rptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(OesApiSubscribeInfoT, c);
}
void generate_class_OesApiClientCfgT(pybind11::module &m)
{
    pybind11::class_<OesApiClientCfgT> c(m, "OesApiClientCfgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesApiClientCfgT, "ordChannelCfg", ordChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(OesApiClientCfgT, "rptChannelCfg", rptChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(OesApiClientCfgT, "qryChannelCfg", qryChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(OesApiClientCfgT, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesApiClientCfgT, c);
}
void generate_class_OesApiClientEnvT(pybind11::module &m)
{
    pybind11::class_<OesApiClientEnvT> c(m, "OesApiClientEnvT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesApiClientEnvT, "ordChannel", ordChannel);
    c.AUTOCXXPY_DEF_PROPERTY(OesApiClientEnvT, "rptChannel", rptChannel);
    c.AUTOCXXPY_DEF_PROPERTY(OesApiClientEnvT, "qryChannel", qryChannel);
    AUTOCXXPY_POST_REGISTER_CLASS(OesApiClientEnvT, c);
}
void generate_class_MdsTradingSessionStatusMsgT(pybind11::module &m)
{
    pybind11::class_<MdsTradingSessionStatusMsgT> c(m, "MdsTradingSessionStatusMsgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__mdsRecvTime", __mdsRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "TotNoRelatedSym", TotNoRelatedSym);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "TradingSessionID", TradingSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTradingSessionStatusMsgT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsTradingSessionStatusMsgT, c);
}
void generate_class_MdsSecurityStatusMsgT(pybind11::module &m)
{
    pybind11::class_<MdsSecurityStatusMsgT> c(m, "MdsSecurityStatusMsgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__mdsRecvTime", __mdsRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "FinancialStatus", FinancialStatus);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "NoSwitch", NoSwitch);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__filler4", __filler4);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "switches", switches);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsSecurityStatusMsgT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsSecurityStatusMsgT, c);
}
void generate_class_MdsPriceLevelEntryT(pybind11::module &m)
{
    pybind11::class_<MdsPriceLevelEntryT> c(m, "MdsPriceLevelEntryT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsPriceLevelEntryT, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(MdsPriceLevelEntryT, "NumberOfOrders", NumberOfOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsPriceLevelEntryT, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsPriceLevelEntryT, c);
}
void generate_class_MdsMktDataSnapshotHeadT(pybind11::module &m)
{
    pybind11::class_<MdsMktDataSnapshotHeadT> c(m, "MdsMktDataSnapshotHeadT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__origMdSource", __origMdSource);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "updateTime", updateTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "bodyLength", bodyLength);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "mdStreamType", mdStreamType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__dataVersion", __dataVersion);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotHeadT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktDataSnapshotHeadT, c);
}
void generate_class_MdsIndexSnapshotBodyT(pybind11::module &m)
{
    pybind11::class_<MdsIndexSnapshotBodyT> c(m, "MdsIndexSnapshotBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "TradingPhaseCode", TradingPhaseCode);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "PrevCloseIdx", PrevCloseIdx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "OpenIdx", OpenIdx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "HighIdx", HighIdx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "LowIdx", LowIdx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "LastIdx", LastIdx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "CloseIdx", CloseIdx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "StockNum", StockNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsIndexSnapshotBodyT, "__filler1", __filler1);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsIndexSnapshotBodyT, c);
}
void generate_class_MdsStockSnapshotBodyT(pybind11::module &m)
{
    pybind11::class_<MdsStockSnapshotBodyT> c(m, "MdsStockSnapshotBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "TradingPhaseCode", TradingPhaseCode);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "PrevClosePx", PrevClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "OpenPx", OpenPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "HighPx", HighPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "LowPx", LowPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "TradePx", TradePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "ClosePx", ClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "IOPV", IOPV);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "NAV", NAV);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "TotalLongPosition", TotalLongPosition);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "BidLevels", BidLevels);
    c.AUTOCXXPY_DEF_PROPERTY(MdsStockSnapshotBodyT, "OfferLevels", OfferLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsStockSnapshotBodyT, c);
}
void generate_class_MdsL1SnapshotBodyT(pybind11::module &m)
{
    pybind11::class_<MdsL1SnapshotBodyT> c(m, "MdsL1SnapshotBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL1SnapshotBodyT, "stock", stock);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL1SnapshotBodyT, "option", option);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL1SnapshotBodyT, "index", index);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL1SnapshotBodyT, c);
}
void generate_class_MdsL2StockSnapshotBodyT(pybind11::module &m)
{
    pybind11::class_<MdsL2StockSnapshotBodyT> c(m, "MdsL2StockSnapshotBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "TradingPhaseCode", TradingPhaseCode);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "PrevClosePx", PrevClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "OpenPx", OpenPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "HighPx", HighPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "LowPx", LowPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "TradePx", TradePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "ClosePx", ClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "IOPV", IOPV);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "NAV", NAV);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "TotalLongPosition", TotalLongPosition);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "TotalBidQty", TotalBidQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "TotalOfferQty", TotalOfferQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "WeightedAvgBidPx", WeightedAvgBidPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "WeightedAvgOfferPx", WeightedAvgOfferPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "BidPriceLevel", BidPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "OfferPriceLevel", OfferPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "BidLevels", BidLevels);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotBodyT, "OfferLevels", OfferLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2StockSnapshotBodyT, c);
}
void generate_class_MdsL2StockSnapshotIncrementalT(pybind11::module &m)
{
    pybind11::class_<MdsL2StockSnapshotIncrementalT> c(m, "MdsL2StockSnapshotIncrementalT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "TotalValueTraded", TotalValueTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "OpenPx", OpenPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "TradePx", TradePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "ClosePx", ClosePx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "IOPV", IOPV);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "TotalBidQty", TotalBidQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "TotalOfferQty", TotalOfferQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "WeightedAvgBidPx", WeightedAvgBidPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "WeightedAvgOfferPx", WeightedAvgOfferPx);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "BidPriceLevel", BidPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "OfferPriceLevel", OfferPriceLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "BestBidPrice", BestBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "HasContainedBestBidLevel", HasContainedBestBidLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "NoBidLevel", NoBidLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "BestOfferPrice", BestOfferPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "HasContainedBestOfferLevel", HasContainedBestOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "NoOfferLevel", NoOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "PriceLevelOperator", PriceLevelOperator);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2StockSnapshotIncrementalT, "PriceLevels", PriceLevels);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2StockSnapshotIncrementalT, c);
}
void generate_class_MdsL2BestOrdersSnapshotBodyT(pybind11::module &m)
{
    pybind11::class_<MdsL2BestOrdersSnapshotBodyT> c(m, "MdsL2BestOrdersSnapshotBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "NoBidOrders", NoBidOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "NoOfferOrders", NoOfferOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "BestBidPrice", BestBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "BestOfferPrice", BestOfferPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "BidOrderQty", BidOrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotBodyT, "OfferOrderQty", OfferOrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2BestOrdersSnapshotBodyT, c);
}
void generate_class_MdsL2BestOrdersSnapshotIncrementalT(pybind11::module &m)
{
    pybind11::class_<MdsL2BestOrdersSnapshotIncrementalT> c(m, "MdsL2BestOrdersSnapshotIncrementalT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "BestBidPrice", BestBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "HasContainedBestBidLevel", HasContainedBestBidLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "ContinualDeletedBidOrders", ContinualDeletedBidOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "NoBidOrders", NoBidOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "BestOfferPrice", BestOfferPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "HasContainedBestOfferLevel", HasContainedBestOfferLevel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "ContinualDeletedOfferOrders", ContinualDeletedOfferOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "NoOfferOrders", NoOfferOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "OperatorEntryID", OperatorEntryID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2BestOrdersSnapshotIncrementalT, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2BestOrdersSnapshotIncrementalT, c);
}
void generate_class_MdsL2VirtualAuctionPriceT(pybind11::module &m)
{
    pybind11::class_<MdsL2VirtualAuctionPriceT> c(m, "MdsL2VirtualAuctionPriceT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2VirtualAuctionPriceT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2VirtualAuctionPriceT, "LeavesSide", LeavesSide);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2VirtualAuctionPriceT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2VirtualAuctionPriceT, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2VirtualAuctionPriceT, "VirtualAuctionQty", VirtualAuctionQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2VirtualAuctionPriceT, "LeavesQty", LeavesQty);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2VirtualAuctionPriceT, c);
}
void generate_class_MdsL2MarketOverviewT(pybind11::module &m)
{
    pybind11::class_<MdsL2MarketOverviewT> c(m, "MdsL2MarketOverviewT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2MarketOverviewT, "OrigDate", OrigDate);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2MarketOverviewT, "OrigTime", OrigTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2MarketOverviewT, "__exchSendingTime", __exchSendingTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2MarketOverviewT, "__mdsRecvTime", __mdsRecvTime);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2MarketOverviewT, c);
}
void generate_class_MdsL2SnapshotBodyT(pybind11::module &m)
{
    pybind11::class_<MdsL2SnapshotBodyT> c(m, "MdsL2SnapshotBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2SnapshotBodyT, "l2Stock", l2Stock);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2SnapshotBodyT, "l2StockIncremental", l2StockIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2SnapshotBodyT, "l2BestOrders", l2BestOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2SnapshotBodyT, "l2BestOrdersIncremental", l2BestOrdersIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2SnapshotBodyT, "index", index);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2SnapshotBodyT, "l2VirtualAuctionPrice", l2VirtualAuctionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2SnapshotBodyT, "l2MarketOverview", l2MarketOverview);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2SnapshotBodyT, c);
}
void generate_class_MdsMktDataSnapshotT(pybind11::module &m)
{
    pybind11::class_<MdsMktDataSnapshotT> c(m, "MdsMktDataSnapshotT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "head", head);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2Stock", l2Stock);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2StockIncremental", l2StockIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2BestOrders", l2BestOrders);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2BestOrdersIncremental", l2BestOrdersIncremental);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "stock", stock);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "option", option);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "index", index);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2VirtualAuctionPrice", l2VirtualAuctionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2MarketOverview", l2MarketOverview);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktDataSnapshotT, c);
}
void generate_class_MdsL2TradeT(pybind11::module &m)
{
    pybind11::class_<MdsL2TradeT> c(m, "MdsL2TradeT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "TransactTime", TransactTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "ChannelNo", ChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "ApplSeqNum", ApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "ExecType", ExecType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "TradeBSFlag", TradeBSFlag);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "TradePrice", TradePrice);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "TradeQty", TradeQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "TradeMoney", TradeMoney);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "BidApplSeqNum", BidApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "OfferApplSeqNum", OfferApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TradeT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2TradeT, c);
}
void generate_class_MdsL2OrderT(pybind11::module &m)
{
    pybind11::class_<MdsL2OrderT> c(m, "MdsL2OrderT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__isRepeated", __isRepeated);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "TransactTime", TransactTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "instrId", instrId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "ChannelNo", ChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "ApplSeqNum", ApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "Side", Side);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__channelNo", __channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__origTickSeq", __origTickSeq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__origNetTime", __origNetTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__processedTime", __processedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2OrderT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2OrderT, c);
}
void generate_class_MdsL2TickLostT(pybind11::module &m)
{
    pybind11::class_<MdsL2TickLostT> c(m, "MdsL2TickLostT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "tradeDate", tradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "lostTime", lostTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "channelNo", channelNo);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "beginApplSeqNum", beginApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "endApplSeqNum", endApplSeqNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsL2TickLostT, "__origTickSeq", __origTickSeq);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsL2TickLostT, c);
}
void generate_class_MdsQryMktDataSnapshotReqT(pybind11::module &m)
{
    pybind11::class_<MdsQryMktDataSnapshotReqT> c(m, "MdsQryMktDataSnapshotReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsQryMktDataSnapshotReqT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsQryMktDataSnapshotReqT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsQryMktDataSnapshotReqT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsQryMktDataSnapshotReqT, "instrId", instrId);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsQryMktDataSnapshotReqT, c);
}
void generate_class_MdsQryTrdSessionStatusReqT(pybind11::module &m)
{
    pybind11::class_<MdsQryTrdSessionStatusReqT> c(m, "MdsQryTrdSessionStatusReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsQryTrdSessionStatusReqT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsQryTrdSessionStatusReqT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsQryTrdSessionStatusReqT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsQryTrdSessionStatusReqT, c);
}
void generate_class_MdsLogonReqT(pybind11::module &m)
{
    pybind11::class_<MdsLogonReqT> c(m, "MdsLogonReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonReqT, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonReqT, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonReqT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonReqT, "password", password);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonReqT, "applVerId", applVerId);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsLogonReqT, c);
}
void generate_class_MdsLogonRspT(pybind11::module &m)
{
    pybind11::class_<MdsLogonRspT> c(m, "MdsLogonRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "heartBtInt", heartBtInt);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "applVerId", applVerId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "minVerId", minVerId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "hostNum", hostNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "isLeader", isLeader);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "leaderHostNum", leaderHostNum);
    c.AUTOCXXPY_DEF_PROPERTY(MdsLogonRspT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsLogonRspT, c);
}
void generate_class_MdsMktDataRequestEntryT(pybind11::module &m)
{
    pybind11::class_<MdsMktDataRequestEntryT> c(m, "MdsMktDataRequestEntryT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestEntryT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestEntryT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestEntryT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestEntryT, "instrId", instrId);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktDataRequestEntryT, c);
}
void generate_class_MdsMktDataRequestReqT(pybind11::module &m)
{
    pybind11::class_<MdsMktDataRequestReqT> c(m, "MdsMktDataRequestReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "subMode", subMode);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "tickType", tickType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "sseStockFlag", sseStockFlag);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "sseIndexFlag", sseIndexFlag);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "sseOptionFlag", sseOptionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "szseStockFlag", szseStockFlag);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "szseIndexFlag", szseIndexFlag);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "szseOptionFlag", szseOptionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "isRequireInitialMktData", isRequireInitialMktData);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "__channelNos", __channelNos);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "tickExpireType", tickExpireType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "dataTypes", dataTypes);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "beginTime", beginTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqT, "subSecurityCnt", subSecurityCnt);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktDataRequestReqT, c);
}
void generate_class_MdsMktDataRequestReqBufT(pybind11::module &m)
{
    pybind11::class_<MdsMktDataRequestReqBufT> c(m, "MdsMktDataRequestReqBufT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqBufT, "mktDataRequestReq", mktDataRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestReqBufT, "entries", entries);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktDataRequestReqBufT, c);
}
void generate_class_MdsMktDataRequestRspT(pybind11::module &m)
{
    pybind11::class_<MdsMktDataRequestRspT> c(m, "MdsMktDataRequestRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "subMode", subMode);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "tickType", tickType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "isRequireInitialMktData", isRequireInitialMktData);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "__channelNos", __channelNos);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "tickExpireType", tickExpireType);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "dataTypes", dataTypes);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "beginTime", beginTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "sseStockSubscribed", sseStockSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "sseIndexSubscribed", sseIndexSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "sseOptionSubscribed", sseOptionSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "szseStockSubscribed", szseStockSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "szseIndexSubscribed", szseIndexSubscribed);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataRequestRspT, "szseOptionSubscribed", szseOptionSubscribed);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktDataRequestRspT, c);
}
void generate_class_MdsTestRequestReqT(pybind11::module &m)
{
    pybind11::class_<MdsTestRequestReqT> c(m, "MdsTestRequestReqT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestReqT, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestReqT, "sendTime", sendTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestReqT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsTestRequestReqT, c);
}
void generate_class_MdsTestRequestRspT(pybind11::module &m)
{
    pybind11::class_<MdsTestRequestRspT> c(m, "MdsTestRequestRspT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "testReqId", testReqId);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "origSendTime", origSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "__filler1", __filler1);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "respTime", respTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "__recvTime", __recvTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "__collectedTime", __collectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(MdsTestRequestRspT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsTestRequestRspT, c);
}
void generate_class_MdsMktReqMsgBodyT(pybind11::module &m)
{
    pybind11::class_<MdsMktReqMsgBodyT> c(m, "MdsMktReqMsgBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktReqMsgBodyT, "wholeMktDataReqBuf", wholeMktDataReqBuf);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktReqMsgBodyT, "mktDataRequestReq", mktDataRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktReqMsgBodyT, "testRequestReq", testRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktReqMsgBodyT, "logonReq", logonReq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktReqMsgBodyT, "qryMktDataSnapshotReq", qryMktDataSnapshotReq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktReqMsgBodyT, "qrySecurityStatusReq", qrySecurityStatusReq);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktReqMsgBodyT, "qryTrdSessionStatusReq", qryTrdSessionStatusReq);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktReqMsgBodyT, c);
}
void generate_class_MdsMktRspMsgBodyT(pybind11::module &m)
{
    pybind11::class_<MdsMktRspMsgBodyT> c(m, "MdsMktRspMsgBodyT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "mktDataRequestRsp", mktDataRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "testRequestRsp", testRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "logonRsp", logonRsp);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "mktDataSnapshot", mktDataSnapshot);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "trade", trade);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "order", order);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "tickLost", tickLost);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "trdSessionStatus", trdSessionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(MdsMktRspMsgBodyT, "securityStatus", securityStatus);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsMktRspMsgBodyT, c);
}
void generate_class_MdsUdpPktHeadT(pybind11::module &m)
{
    pybind11::class_<MdsUdpPktHeadT> c(m, "MdsUdpPktHeadT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsUdpPktHeadT, "msgCnt", msgCnt);
    c.AUTOCXXPY_DEF_PROPERTY(MdsUdpPktHeadT, "pktSiz", pktSiz);
    c.AUTOCXXPY_DEF_PROPERTY(MdsUdpPktHeadT, "pktSeq", pktSeq);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsUdpPktHeadT, c);
}
void generate_class_MdsApiClientCfgT(pybind11::module &m)
{
    pybind11::class_<MdsApiClientCfgT> c(m, "MdsApiClientCfgT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientCfgT, "tcpChannelCfg", tcpChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientCfgT, "qryChannelCfg", qryChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientCfgT, "udpL1ChannelCfg", udpL1ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientCfgT, "udpL2ChannelCfg", udpL2ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientCfgT, "udpTradeChannelCfg", udpTradeChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientCfgT, "udpOrderChannelCfg", udpOrderChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientCfgT, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsApiClientCfgT, c);
}
void generate_class_MdsApiClientEnvT(pybind11::module &m)
{
    pybind11::class_<MdsApiClientEnvT> c(m, "MdsApiClientEnvT");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientEnvT, "tcpChannel", tcpChannel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientEnvT, "qryChannel", qryChannel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientEnvT, "udpL1Channel", udpL1Channel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientEnvT, "udpL2Channel", udpL2Channel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientEnvT, "udpTradeChannel", udpTradeChannel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientEnvT, "udpOrderChannel", udpOrderChannel);
    c.AUTOCXXPY_DEF_PROPERTY(MdsApiClientEnvT, "udpChannelGroup", udpChannelGroup);
    AUTOCXXPY_POST_REGISTER_CLASS(MdsApiClientEnvT, c);
}
