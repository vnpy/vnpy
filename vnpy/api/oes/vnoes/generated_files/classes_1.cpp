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


void generate_class_OesOrdReqT(pybind11::module &m)
{
    pybind11::class_<OesOrdReqT> c(m, "OesOrdReqT");
    if constexpr (std::is_default_constructible_v<OesOrdReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "ordQty", ordQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "ordPrice", ordPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdReqT, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    AUTOCXXPY_POST_REGISTER_CLASS(OesOrdReqT, c);
    m.attr("_OesOrdReq") = c;
}
void generate_class_OesOrdCancelReqT(pybind11::module &m)
{
    pybind11::class_<OesOrdCancelReqT> c(m, "OesOrdCancelReqT");
    if constexpr (std::is_default_constructible_v<OesOrdCancelReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "__ORD_CANCEL_BASE_INFO_filler1", __ORD_CANCEL_BASE_INFO_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "origClSeqNo", origClSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "origClEnvId", origClEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "__ORD_CANCEL_BASE_INFO_filler2", __ORD_CANCEL_BASE_INFO_filler2);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCancelReqT, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    AUTOCXXPY_POST_REGISTER_CLASS(OesOrdCancelReqT, c);
    m.attr("_OesOrdCancelReq") = c;
}
void generate_class_OesOrdRejectT(pybind11::module &m)
{
    pybind11::class_<OesOrdRejectT> c(m, "OesOrdRejectT");
    if constexpr (std::is_default_constructible_v<OesOrdRejectT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "ordQty", ordQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "ordPrice", ordPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "origClSeqNo", origClSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "origClEnvId", origClEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "ordDate", ordDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "ordTime", ordTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "ordRejReason", ordRejReason);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdRejectT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(OesOrdRejectT, c);
    m.attr("_OesOrdReject") = c;
}
void generate_class_OesOrdCnfmT(pybind11::module &m)
{
    pybind11::class_<OesOrdCnfmT> c(m, "OesOrdCnfmT");
    if constexpr (std::is_default_constructible_v<OesOrdCnfmT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ORD_BASE_INFO_filler", __ORD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordQty", ordQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordPrice", ordPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "origClOrdId", origClOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordReqOrigSendTime", __ordReqOrigSendTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "origClEnvId", origClEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "origClSeqNo", origClSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordDate", ordDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordTime", ordTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordCnfmTime", ordCnfmTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordStatus", ordStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordCnfmSts", ordCnfmSts);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__platformId", __platformId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__tgwGrpNo", __tgwGrpNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__declareFlag", __declareFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ORD_CNFM_BASE_INFO_filler", __ORD_CNFM_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "exchOrdId", exchOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "frzAmt", frzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "frzInterest", frzInterest);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "frzFee", frzFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "cumAmt", cumAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "cumInterest", cumInterest);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "cumFee", cumFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "cumQty", cumQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "canceledQty", canceledQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "ordRejReason", ordRejReason);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "exchErrCode", exchErrCode);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__rowNum", __rowNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__recNum", __recNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordReqOrigRecvTime", __ordReqOrigRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordReqCollectedTime", __ordReqCollectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordReqActualDealTime", __ordReqActualDealTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordReqProcessedTime", __ordReqProcessedTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordCnfmOrigRecvTime", __ordCnfmOrigRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordCnfmCollectedTime", __ordCnfmCollectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordCnfmActualDealTime", __ordCnfmActualDealTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordCnfmProcessedTime", __ordCnfmProcessedTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordDeclareTime", __ordDeclareTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__ordDeclareDoneTime", __ordDeclareDoneTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesOrdCnfmT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(OesOrdCnfmT, c);
    m.attr("OesOrdItemT") = c;
    m.attr("_OesOrdCnfm") = c;
}
void generate_class_OesTrdBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesTrdBaseInfoT> c(m, "OesTrdBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesTrdBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "exchTrdNum", exchTrdNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "trdSide", trdSide);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "__platformId", __platformId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "__trdCnfmType", __trdCnfmType);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "__etfTrdCnfmSeq", __etfTrdCnfmSeq);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "trdDate", trdDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "trdTime", trdTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "trdQty", trdQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "trdPrice", trdPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "trdAmt", trdAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "cumQty", cumQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "__rowNum", __rowNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "__tgwGrpNo", __tgwGrpNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "__TRD_BASE_INFO_filler", __TRD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "origOrdQty", origOrdQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdBaseInfoT, "branchId", branchId);
    AUTOCXXPY_POST_REGISTER_CLASS(OesTrdBaseInfoT, c);
    m.attr("_OesTrdBaseInfo") = c;
}
void generate_class_OesTrdCnfmT(pybind11::module &m)
{
    pybind11::class_<OesTrdCnfmT> c(m, "OesTrdCnfmT");
    if constexpr (std::is_default_constructible_v<OesTrdCnfmT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "exchTrdNum", exchTrdNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "trdSide", trdSide);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__platformId", __platformId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__trdCnfmType", __trdCnfmType);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__etfTrdCnfmSeq", __etfTrdCnfmSeq);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "trdDate", trdDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "trdTime", trdTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "trdQty", trdQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "trdPrice", trdPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "trdAmt", trdAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "cumQty", cumQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__rowNum", __rowNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__tgwGrpNo", __tgwGrpNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__TRD_BASE_INFO_filler", __TRD_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "origOrdQty", origOrdQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "ordStatus", ordStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "ordType", ordType);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "ordBuySellType", ordBuySellType);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "origOrdPrice", origOrdPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "cumAmt", cumAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "cumInterest", cumInterest);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "cumFee", cumFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__trdCnfmOrigRecvTime", __trdCnfmOrigRecvTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__trdCnfmCollectedTime", __trdCnfmCollectedTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__trdCnfmActualDealTime", __trdCnfmActualDealTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__trdCnfmProcessedTime", __trdCnfmProcessedTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesTrdCnfmT, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(OesTrdCnfmT, c);
    m.attr("OesTrdItemT") = c;
    m.attr("_OesTrdCnfm") = c;
}
void generate_class_OesLotWinningBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesLotWinningBaseInfoT> c(m, "OesLotWinningBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesLotWinningBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "lotType", lotType);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "rejReason", rejReason);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "__LOT_WINNING_BASE_INFO_filler", __LOT_WINNING_BASE_INFO_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "lotDate", lotDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "securityName", securityName);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "assignNum", assignNum);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "lotQty", lotQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "lotPrice", lotPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesLotWinningBaseInfoT, "lotAmt", lotAmt);
    AUTOCXXPY_POST_REGISTER_CLASS(OesLotWinningBaseInfoT, c);
    m.attr("_OesLotWinningBaseInfo") = c;
    m.attr("OesLotWinningItemT") = c;
}
void generate_class_OesFundTrsfBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesFundTrsfBaseInfoT> c(m, "OesFundTrsfBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesFundTrsfBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "trdPasswd", trdPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "trsfPasswd", trsfPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfBaseInfoT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesFundTrsfBaseInfoT, c);
    m.attr("_OesFundTrsfBaseInfo") = c;
}
void generate_class_OesFundTrsfReqT(pybind11::module &m)
{
    pybind11::class_<OesFundTrsfReqT> c(m, "OesFundTrsfReqT");
    if constexpr (std::is_default_constructible_v<OesFundTrsfReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "trdPasswd", trdPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "trsfPasswd", trsfPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReqT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesFundTrsfReqT, c);
    m.attr("_OesFundTrsfReq") = c;
}
void generate_class_OesFundTrsfRejectT(pybind11::module &m)
{
    pybind11::class_<OesFundTrsfRejectT> c(m, "OesFundTrsfRejectT");
    if constexpr (std::is_default_constructible_v<OesFundTrsfRejectT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "__FUND_TRSF_BASE_filler", __FUND_TRSF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "trdPasswd", trdPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "trsfPasswd", trsfPasswd);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "ordDate", ordDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "ordTime", ordTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "rejReason", rejReason);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfRejectT, "errorInfo", errorInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesFundTrsfRejectT, c);
    m.attr("_OesFundTrsfReject") = c;
}
void generate_class_OesFundTrsfReportT(pybind11::module &m)
{
    pybind11::class_<OesFundTrsfReportT> c(m, "OesFundTrsfReportT");
    if constexpr (std::is_default_constructible_v<OesFundTrsfReportT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "direct", direct);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "occurAmt", occurAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "fundTrsfId", fundTrsfId);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "counterEntrustNo", counterEntrustNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "operDate", operDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "operTime", operTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "dclrTime", dclrTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "doneTime", doneTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "isAllotOnly", isAllotOnly);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "trsfStatus", trsfStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "__hasCounterTransfered", __hasCounterTransfered);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "rejReason", rejReason);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "counterErrCode", counterErrCode);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "allotSerialNo", allotSerialNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesFundTrsfReportT, "errorInfo", errorInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesFundTrsfReportT, c);
    m.attr("_OesFundTrsfReport") = c;
    m.attr("OesFundTransferSerialItemT") = c;
}
void generate_class_OesIssueBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesIssueBaseInfoT> c(m, "OesIssueBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesIssueBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "isCancelAble", isCancelAble);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "isReApplyAble", isReApplyAble);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "__ISSUE_BASE_filler", __ISSUE_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "securityName", securityName);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "underlyingSecurityId", underlyingSecurityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "startDate", startDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "endDate", endDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "issueQty", issueQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "qtyUnit", qtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "ordMaxQty", ordMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "ordMinQty", ordMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "issuePrice", issuePrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "ceilPrice", ceilPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesIssueBaseInfoT, "floorPrice", floorPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(OesIssueBaseInfoT, c);
    m.attr("_OesIssueBaseInfo") = c;
    m.attr("OesIssueItemT") = c;
}
void generate_class_OesPriceLimitT(pybind11::module &m)
{
    pybind11::class_<OesPriceLimitT> c(m, "OesPriceLimitT");
    if constexpr (std::is_default_constructible_v<OesPriceLimitT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesPriceLimitT, "ceilPrice", ceilPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesPriceLimitT, "floorPrice", floorPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(OesPriceLimitT, c);
    m.attr("_OesPriceLimit") = c;
}
void generate_class_OesStockBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesStockBaseInfoT> c(m, "OesStockBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesStockBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "securityLevel", securityLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "securityRiskLevel", securityRiskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "qualificationClass", qualificationClass);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "isDayTrading", isDayTrading);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "suspFlag", suspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "temporarySuspFlag", temporarySuspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "__filter", __filter);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "buyQtyUnit", buyQtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "sellQtyUnit", sellQtyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "buyOrdMaxQty", buyOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "buyOrdMinQty", buyOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "sellOrdMaxQty", sellOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "sellOrdMinQty", sellOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "priceUnit", priceUnit);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "prevClose", prevClose);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "parPrice", parPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "bondInterest", bondInterest);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "repoExpirationDays", repoExpirationDays);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "cashHoldDays", cashHoldDays);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "priceLimit", priceLimit);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "securityName", securityName);
    c.AUTOCXXPY_DEF_PROPERTY(OesStockBaseInfoT, "fundId", fundId);
    AUTOCXXPY_POST_REGISTER_CLASS(OesStockBaseInfoT, c);
    m.attr("OesStockItemT") = c;
    m.attr("_OesStockBaseInfo") = c;
}
void generate_class_OesEtfBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesEtfBaseInfoT> c(m, "OesEtfBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesEtfBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "isPublishIOPV", isPublishIOPV);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "isCreationAble", isCreationAble);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "isRedemptionAble", isRedemptionAble);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "isDisabled", isDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "__ETF_BASE_filler", __ETF_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "componentCnt", componentCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "creRdmUnit", creRdmUnit);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "maxCashRatio", maxCashRatio);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "nav", nav);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "navPerCU", navPerCU);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "dividendPerCU", dividendPerCU);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "tradingDay", tradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "preTradingDay", preTradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "estiCashCmpoent", estiCashCmpoent);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "cashCmpoent", cashCmpoent);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "creationLimit", creationLimit);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "redemLimit", redemLimit);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "netCreationLimit", netCreationLimit);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfBaseInfoT, "netRedemLimit", netRedemLimit);
    AUTOCXXPY_POST_REGISTER_CLASS(OesEtfBaseInfoT, c);
    m.attr("_OesEtfBaseInfo") = c;
    m.attr("OesEtfItemT") = c;
}
void generate_class_OesEtfComponentBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesEtfComponentBaseInfoT> c(m, "OesEtfComponentBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesEtfComponentBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "subFlag", subFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "prevClose", prevClose);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "qty", qty);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "premiumRate", premiumRate);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "creationSubCash", creationSubCash);
    c.AUTOCXXPY_DEF_PROPERTY(OesEtfComponentBaseInfoT, "redemptionCashSub", redemptionCashSub);
    AUTOCXXPY_POST_REGISTER_CLASS(OesEtfComponentBaseInfoT, c);
    m.attr("_OesEtfComponentBaseInfo") = c;
}
void generate_class_OesOptionBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesOptionBaseInfoT> c(m, "OesOptionBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesOptionBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "contractType", contractType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "openFlag", openFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "optionType", optionType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "suspFlag", suspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "temporarySuspFlag", temporarySuspFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "contractMultiplierUnit", contractMultiplierUnit);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "excPrice", excPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "startDate", startDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "endDate", endDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "execDate", execDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "expDate", expDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "closePrice", closePrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "settlPrice", settlPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "roundLot", roundLot);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "tickSize", tickSize);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "ceilPrice", ceilPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "floorPrice", floorPrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "marginUnit", marginUnit);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "leavesQty", leavesQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "lmtOrdMaxQty", lmtOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "lmtOrdMinQty", lmtOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "mktOrdMaxQty", mktOrdMaxQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "mktOrdMinQty", mktOrdMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "underlyingSecurityId", underlyingSecurityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "underlyingMktId", underlyingMktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "underlyingSecuType", underlyingSecuType);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "closeEndDateFlag", closeEndDateFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "__OPTION_BASE_filler1", __OPTION_BASE_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "underlyingClosePrice", underlyingClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptionBaseInfoT, "securityName", securityName);
    AUTOCXXPY_POST_REGISTER_CLASS(OesOptionBaseInfoT, c);
    m.attr("_OesOptionBaseInfo") = c;
    m.attr("OesOptionItemT") = c;
}
void generate_class_OesCashAssetBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesCashAssetBaseInfoT> c(m, "OesCashAssetBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesCashAssetBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "__CASH_ASSET_BASE_filler", __CASH_ASSET_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "beginningBal", beginningBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "beginningAvailableBal", beginningAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "beginningDrawableBal", beginningDrawableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "disableBal", disableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "reversalAmt", reversalAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "manualFrzAmt", manualFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "totalDepositAmt", totalDepositAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "totalWithdrawAmt", totalWithdrawAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "withdrawFrzAmt", withdrawFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "buyFrzAmt", buyFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "totalFeeAmt", totalFeeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "feeFrzAmt", feeFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "marginAmt", marginAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetBaseInfoT, "marginFrzAmt", marginFrzAmt);
    AUTOCXXPY_POST_REGISTER_CLASS(OesCashAssetBaseInfoT, c);
    m.attr("_OesCashAssetBaseInfo") = c;
}
void generate_class_OesCustBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesCustBaseInfoT> c(m, "OesCustBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesCustBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "custType", custType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "riskLevel", riskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "originRiskLevel", originRiskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "institutionFlag", institutionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "investorClass", investorClass);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "__CUST_BASE_filler1", __CUST_BASE_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustBaseInfoT, "__CUST_BASE_filler2", __CUST_BASE_filler2);
    AUTOCXXPY_POST_REGISTER_CLASS(OesCustBaseInfoT, c);
    m.attr("OesCustItemT") = c;
    m.attr("_OesCustBaseInfo") = c;
}
void generate_class_OesInvAcctBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesInvAcctBaseInfoT> c(m, "OesInvAcctBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesInvAcctBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "acctType", acctType);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "ownerType", ownerType);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "optInvLevel", optInvLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "isTradeDisabled", isTradeDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "limits", limits);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "permissions", permissions);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctBaseInfoT, "subscriptionQuota", subscriptionQuota);
    AUTOCXXPY_POST_REGISTER_CLASS(OesInvAcctBaseInfoT, c);
    m.attr("_OesInvAcctBaseInfo") = c;
}
void generate_class_OesStkHoldingBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesStkHoldingBaseInfoT> c(m, "OesStkHoldingBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesStkHoldingBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "originalHld", originalHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "originalCostAmt", originalCostAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalBuyHld", totalBuyHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalSellHld", totalSellHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "sellFrzHld", sellFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "manualFrzHld", manualFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalBuyFee", totalBuyFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalSellFee", totalSellFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalTrsfInHld", totalTrsfInHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "totalTrsfOutHld", totalTrsfOutHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "trsfOutFrzHld", trsfOutFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "lockHld", lockHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "lockFrzHld", lockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "unlockFrzHld", unlockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "coveredFrzHld", coveredFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingBaseInfoT, "coveredHld", coveredHld);
    AUTOCXXPY_POST_REGISTER_CLASS(OesStkHoldingBaseInfoT, c);
    m.attr("_OesStkHoldingBaseInfo") = c;
}
void generate_class_OesOptHoldingBaseInfoT(pybind11::module &m)
{
    pybind11::class_<OesOptHoldingBaseInfoT> c(m, "OesOptHoldingBaseInfoT");
    if constexpr (std::is_default_constructible_v<OesOptHoldingBaseInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "hldA", hldA);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "hldB", hldB);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "hldC", hldC);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "hldC2", hldC2);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "hldRA", hldRA);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "hldRB", hldRB);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingBaseInfoT, "hldRC", hldRC);
    AUTOCXXPY_POST_REGISTER_CLASS(OesOptHoldingBaseInfoT, c);
    m.attr("_OesOptHoldingBaseInfo") = c;
}
void generate_class_OesMarketStateInfoT(pybind11::module &m)
{
    pybind11::class_<OesMarketStateInfoT> c(m, "OesMarketStateInfoT");
    if constexpr (std::is_default_constructible_v<OesMarketStateInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesMarketStateInfoT, "exchId", exchId);
    c.AUTOCXXPY_DEF_PROPERTY(OesMarketStateInfoT, "platformId", platformId);
    c.AUTOCXXPY_DEF_PROPERTY(OesMarketStateInfoT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesMarketStateInfoT, "mktState", mktState);
    c.AUTOCXXPY_DEF_PROPERTY(OesMarketStateInfoT, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(OesMarketStateInfoT, c);
    m.attr("OesMarketStateItemT") = c;
    m.attr("_OesMarketStateInfo") = c;
}
void generate_class_OesTradingPermissionEntryT(pybind11::module &m)
{
    pybind11::class_<OesTradingPermissionEntryT> c(m, "OesTradingPermissionEntryT");
    if constexpr (std::is_default_constructible_v<OesTradingPermissionEntryT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesTradingPermissionEntryT, "permissionNo", permissionNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesTradingPermissionEntryT, "isDisabled", isDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesTradingPermissionEntryT, "counterAlias", counterAlias);
    c.AUTOCXXPY_DEF_PROPERTY(OesTradingPermissionEntryT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesTradingPermissionEntryT, "permissionCode", permissionCode);
    c.AUTOCXXPY_DEF_PROPERTY(OesTradingPermissionEntryT, "applicableMarkets", applicableMarkets);
    c.AUTOCXXPY_DEF_PROPERTY(OesTradingPermissionEntryT, "permissionMemo", permissionMemo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesTradingPermissionEntryT, c);
    m.attr("_OesTradingPermissionEntry") = c;
}
void generate_class_OesInputSourceInfoT(pybind11::module &m)
{
    pybind11::class_<OesInputSourceInfoT> c(m, "OesInputSourceInfoT");
    if constexpr (std::is_default_constructible_v<OesInputSourceInfoT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesInputSourceInfoT, "sourceIp", sourceIp);
    c.AUTOCXXPY_DEF_PROPERTY(OesInputSourceInfoT, "sourceMac", sourceMac);
    c.AUTOCXXPY_DEF_PROPERTY(OesInputSourceInfoT, "sourceType", sourceType);
    c.AUTOCXXPY_DEF_PROPERTY(OesInputSourceInfoT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesInputSourceInfoT, "sourceDriverId", sourceDriverId);
    AUTOCXXPY_POST_REGISTER_CLASS(OesInputSourceInfoT, c);
    m.attr("_OesInputSourceInfo") = c;
}
void generate_class_SMsgHeadT(pybind11::module &m)
{
    pybind11::class_<SMsgHeadT> c(m, "SMsgHeadT");
    if constexpr (std::is_default_constructible_v<SMsgHeadT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(SMsgHeadT, "msgFlag", msgFlag);
    c.AUTOCXXPY_DEF_PROPERTY(SMsgHeadT, "msgId", msgId);
    c.AUTOCXXPY_DEF_PROPERTY(SMsgHeadT, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(SMsgHeadT, "detailStatus", detailStatus);
    c.AUTOCXXPY_DEF_PROPERTY(SMsgHeadT, "msgSize", msgSize);
    AUTOCXXPY_POST_REGISTER_CLASS(SMsgHeadT, c);
    m.attr("_SMsgHead") = c;
}
void generate_class_OesQryCursorT(pybind11::module &m)
{
    pybind11::class_<OesQryCursorT> c(m, "OesQryCursorT");
    if constexpr (std::is_default_constructible_v<OesQryCursorT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCursorT, "seqNo", seqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCursorT, "isEnd", isEnd);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCursorT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCursorT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCursorT, c);
    m.attr("_OesQryCursor") = c;
}
void generate_class_OesQryReqHeadT(pybind11::module &m)
{
    pybind11::class_<OesQryReqHeadT> c(m, "OesQryReqHeadT");
    if constexpr (std::is_default_constructible_v<OesQryReqHeadT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqHeadT, "maxPageSize", maxPageSize);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryReqHeadT, "lastPosition", lastPosition);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryReqHeadT, c);
    m.attr("_OesQryReqHead") = c;
}
void generate_class_OesQryRspHeadT(pybind11::module &m)
{
    pybind11::class_<OesQryRspHeadT> c(m, "OesQryRspHeadT");
    if constexpr (std::is_default_constructible_v<OesQryRspHeadT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspHeadT, "itemCount", itemCount);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspHeadT, "lastPosition", lastPosition);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspHeadT, "isEnd", isEnd);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspHeadT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryRspHeadT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryRspHeadT, c);
    m.attr("_OesQryRspHead") = c;
}
void generate_class_OesQryOrdFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryOrdFilterT> c(m, "OesQryOrdFilterT");
    if constexpr (std::is_default_constructible_v<OesQryOrdFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "isUnclosedOnly", isUnclosedOnly);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "startTime", startTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "endTime", endTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOrdFilterT, c);
    m.attr("_OesQryOrdFilter") = c;
}
void generate_class_OesQryOrdReqT(pybind11::module &m)
{
    pybind11::class_<OesQryOrdReqT> c(m, "OesQryOrdReqT");
    if constexpr (std::is_default_constructible_v<OesQryOrdReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOrdReqT, c);
    m.attr("_OesQryOrdReq") = c;
}
void generate_class_OesQryOrdRspT(pybind11::module &m)
{
    pybind11::class_<OesQryOrdRspT> c(m, "OesQryOrdRspT");
    if constexpr (std::is_default_constructible_v<OesQryOrdRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOrdRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOrdRspT, c);
    m.attr("_OesQryOrdRsp") = c;
}
void generate_class_OesQryTrdFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryTrdFilterT> c(m, "OesQryTrdFilterT");
    if constexpr (std::is_default_constructible_v<OesQryTrdFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "clOrdId", clOrdId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "startTime", startTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "endTime", endTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryTrdFilterT, c);
    m.attr("_OesQryTrdFilter") = c;
}
void generate_class_OesQryTrdReqT(pybind11::module &m)
{
    pybind11::class_<OesQryTrdReqT> c(m, "OesQryTrdReqT");
    if constexpr (std::is_default_constructible_v<OesQryTrdReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryTrdReqT, c);
    m.attr("_OesQryTrdReq") = c;
}
void generate_class_OesQryTrdRspT(pybind11::module &m)
{
    pybind11::class_<OesQryTrdRspT> c(m, "OesQryTrdRspT");
    if constexpr (std::is_default_constructible_v<OesQryTrdRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryTrdRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryTrdRspT, c);
    m.attr("_OesQryTrdRsp") = c;
}
void generate_class_OesQryCashAssetFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryCashAssetFilterT> c(m, "OesQryCashAssetFilterT");
    if constexpr (std::is_default_constructible_v<OesQryCashAssetFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCashAssetFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCashAssetFilterT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCashAssetFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCashAssetFilterT, c);
    m.attr("_OesQryCashAssetFilter") = c;
}
void generate_class_OesCashAssetItemT(pybind11::module &m)
{
    pybind11::class_<OesCashAssetItemT> c(m, "OesCashAssetItemT");
    if constexpr (std::is_default_constructible_v<OesCashAssetItemT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "__CASH_ASSET_BASE_filler", __CASH_ASSET_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "beginningBal", beginningBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "beginningAvailableBal", beginningAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "beginningDrawableBal", beginningDrawableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "disableBal", disableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "reversalAmt", reversalAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "manualFrzAmt", manualFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "totalDepositAmt", totalDepositAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "totalWithdrawAmt", totalWithdrawAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "withdrawFrzAmt", withdrawFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "buyFrzAmt", buyFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "totalFeeAmt", totalFeeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "feeFrzAmt", feeFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "marginAmt", marginAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "marginFrzAmt", marginFrzAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "currentTotalBal", currentTotalBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "currentAvailableBal", currentAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAssetItemT, "currentDrawableBal", currentDrawableBal);
    AUTOCXXPY_POST_REGISTER_CLASS(OesCashAssetItemT, c);
    m.attr("_OesCashAssetItem") = c;
}
void generate_class_OesQryCashAssetReqT(pybind11::module &m)
{
    pybind11::class_<OesQryCashAssetReqT> c(m, "OesQryCashAssetReqT");
    if constexpr (std::is_default_constructible_v<OesQryCashAssetReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCashAssetReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCashAssetReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCashAssetReqT, c);
    m.attr("_OesQryCashAssetReq") = c;
}
void generate_class_OesQryCashAssetRspT(pybind11::module &m)
{
    pybind11::class_<OesQryCashAssetRspT> c(m, "OesQryCashAssetRspT");
    if constexpr (std::is_default_constructible_v<OesQryCashAssetRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCashAssetRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCashAssetRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCashAssetRspT, c);
    m.attr("_OesQryCashAssetRsp") = c;
}
void generate_class_OesCounterCashItemT(pybind11::module &m)
{
    pybind11::class_<OesCounterCashItemT> c(m, "OesCounterCashItemT");
    if constexpr (std::is_default_constructible_v<OesCounterCashItemT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "custName", custName);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "bankId", bankId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "counterAvailableBal", counterAvailableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "counterDrawableBal", counterDrawableBal);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "counterCashUpdateTime", counterCashUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesCounterCashItemT, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(OesCounterCashItemT, c);
    m.attr("_OesCounterCashItem") = c;
}
void generate_class_OesQryCounterCashReqT(pybind11::module &m)
{
    pybind11::class_<OesQryCounterCashReqT> c(m, "OesQryCounterCashReqT");
    if constexpr (std::is_default_constructible_v<OesQryCounterCashReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCounterCashReqT, "cashAcctId", cashAcctId);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCounterCashReqT, c);
    m.attr("_OesQryCounterCashReq") = c;
}
void generate_class_OesQryCounterCashRspT(pybind11::module &m)
{
    pybind11::class_<OesQryCounterCashRspT> c(m, "OesQryCounterCashRspT");
    if constexpr (std::is_default_constructible_v<OesQryCounterCashRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCounterCashRspT, "counterCashItem", counterCashItem);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCounterCashRspT, c);
    m.attr("_OesQryCounterCashRsp") = c;
}
void generate_class_OesQryStkHoldingFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryStkHoldingFilterT> c(m, "OesQryStkHoldingFilterT");
    if constexpr (std::is_default_constructible_v<OesQryStkHoldingFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingFilterT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingFilterT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingFilterT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryStkHoldingFilterT, c);
    m.attr("OesQryOptHoldingFilterT") = c;
    m.attr("_OesQryStkHoldingFilter") = c;
}
void generate_class_OesStkHoldingItemT(pybind11::module &m)
{
    pybind11::class_<OesStkHoldingItemT> c(m, "OesStkHoldingItemT");
    if constexpr (std::is_default_constructible_v<OesStkHoldingItemT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "originalHld", originalHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "originalCostAmt", originalCostAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalBuyHld", totalBuyHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalSellHld", totalSellHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "sellFrzHld", sellFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "manualFrzHld", manualFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalBuyAmt", totalBuyAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalSellAmt", totalSellAmt);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalBuyFee", totalBuyFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalSellFee", totalSellFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalTrsfInHld", totalTrsfInHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "totalTrsfOutHld", totalTrsfOutHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "trsfOutFrzHld", trsfOutFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "lockHld", lockHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "lockFrzHld", lockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "unlockFrzHld", unlockFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "coveredFrzHld", coveredFrzHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "coveredHld", coveredHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "sellAvlHld", sellAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "trsfOutAvlHld", trsfOutAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "lockAvlHld", lockAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "coveredAvlHld", coveredAvlHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "sumHld", sumHld);
    c.AUTOCXXPY_DEF_PROPERTY(OesStkHoldingItemT, "costPrice", costPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(OesStkHoldingItemT, c);
    m.attr("_OesStkHoldingItem") = c;
}
void generate_class_OesQryStkHoldingReqT(pybind11::module &m)
{
    pybind11::class_<OesQryStkHoldingReqT> c(m, "OesQryStkHoldingReqT");
    if constexpr (std::is_default_constructible_v<OesQryStkHoldingReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryStkHoldingReqT, c);
    m.attr("_OesQryStkHoldingReq") = c;
}
void generate_class_OesQryStkHoldingRspT(pybind11::module &m)
{
    pybind11::class_<OesQryStkHoldingRspT> c(m, "OesQryStkHoldingRspT");
    if constexpr (std::is_default_constructible_v<OesQryStkHoldingRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingRspT, "qryHead", qryHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStkHoldingRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryStkHoldingRspT, c);
    m.attr("_OesQryStkHoldingRsp") = c;
}
void generate_class_OesOptHoldingItemT(pybind11::module &m)
{
    pybind11::class_<OesOptHoldingItemT> c(m, "OesOptHoldingItemT");
    if constexpr (std::is_default_constructible_v<OesOptHoldingItemT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "__HOLD_BASE_filler", __HOLD_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "hldA", hldA);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "hldB", hldB);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "hldC", hldC);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "hldC2", hldC2);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "hldRA", hldRA);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "hldRB", hldRB);
    c.AUTOCXXPY_DEF_PROPERTY(OesOptHoldingItemT, "hldRC", hldRC);
    AUTOCXXPY_POST_REGISTER_CLASS(OesOptHoldingItemT, c);
    m.attr("_OesOptHoldingItem") = c;
}
void generate_class_OesQryOptHoldingReqT(pybind11::module &m)
{
    pybind11::class_<OesQryOptHoldingReqT> c(m, "OesQryOptHoldingReqT");
    if constexpr (std::is_default_constructible_v<OesQryOptHoldingReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptHoldingReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptHoldingReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOptHoldingReqT, c);
    m.attr("_OesQryOptHoldingReq") = c;
}
void generate_class_OesQryOptHoldingRspT(pybind11::module &m)
{
    pybind11::class_<OesQryOptHoldingRspT> c(m, "OesQryOptHoldingRspT");
    if constexpr (std::is_default_constructible_v<OesQryOptHoldingRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptHoldingRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryOptHoldingRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryOptHoldingRspT, c);
    m.attr("_OesQryHoldRsp") = c;
}
void generate_class_OesQryCustFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryCustFilterT> c(m, "OesQryCustFilterT");
    if constexpr (std::is_default_constructible_v<OesQryCustFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCustFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCustFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCustFilterT, c);
    m.attr("_OesQryCustFilter") = c;
}
void generate_class_OesQryCustReqT(pybind11::module &m)
{
    pybind11::class_<OesQryCustReqT> c(m, "OesQryCustReqT");
    if constexpr (std::is_default_constructible_v<OesQryCustReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCustReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCustReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCustReqT, c);
    m.attr("_OesQryCustReq") = c;
}
void generate_class_OesQryCustRspT(pybind11::module &m)
{
    pybind11::class_<OesQryCustRspT> c(m, "OesQryCustRspT");
    if constexpr (std::is_default_constructible_v<OesQryCustRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCustRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCustRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCustRspT, c);
    m.attr("_OesQryCustRsp") = c;
}
void generate_class_OesQryInvAcctFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryInvAcctFilterT> c(m, "OesQryInvAcctFilterT");
    if constexpr (std::is_default_constructible_v<OesQryInvAcctFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctFilterT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryInvAcctFilterT, c);
    m.attr("_OesQryInvAcctFilter") = c;
}
void generate_class_OesInvAcctItemT(pybind11::module &m)
{
    pybind11::class_<OesInvAcctItemT> c(m, "OesInvAcctItemT");
    if constexpr (std::is_default_constructible_v<OesInvAcctItemT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "acctType", acctType);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "ownerType", ownerType);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "optInvLevel", optInvLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "isTradeDisabled", isTradeDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "limits", limits);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "permissions", permissions);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "subscriptionQuota", subscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctItemT, "custId", custId);
    AUTOCXXPY_POST_REGISTER_CLASS(OesInvAcctItemT, c);
    m.attr("_OesInvAcctItem") = c;
}
void generate_class_OesQryInvAcctReqT(pybind11::module &m)
{
    pybind11::class_<OesQryInvAcctReqT> c(m, "OesQryInvAcctReqT");
    if constexpr (std::is_default_constructible_v<OesQryInvAcctReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryInvAcctReqT, c);
    m.attr("_OesQryInvAcctReq") = c;
}
void generate_class_OesQryInvAcctRspT(pybind11::module &m)
{
    pybind11::class_<OesQryInvAcctRspT> c(m, "OesQryInvAcctRspT");
    if constexpr (std::is_default_constructible_v<OesQryInvAcctRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryInvAcctRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryInvAcctRspT, c);
    m.attr("_OesQryInvAcctRsp") = c;
}
void generate_class_OesInvAcctOverviewT(pybind11::module &m)
{
    pybind11::class_<OesInvAcctOverviewT> c(m, "OesInvAcctOverviewT");
    if constexpr (std::is_default_constructible_v<OesInvAcctOverviewT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "acctType", acctType);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "ownerType", ownerType);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "optInvLevel", optInvLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "isTradeDisabled", isTradeDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "__INV_ACCT_BASE_filler", __INV_ACCT_BASE_filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "limits", limits);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "permissions", permissions);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "pbuId", pbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "subscriptionQuota", subscriptionQuota);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "isValid", isValid);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "trdOrdCnt", trdOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "nonTrdOrdCnt", nonTrdOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "cancelOrdCnt", cancelOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "oesRejectOrdCnt", oesRejectOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "exchRejectOrdCnt", exchRejectOrdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "trdCnt", trdCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesInvAcctOverviewT, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(OesInvAcctOverviewT, c);
    m.attr("_OesInvAcctOverview") = c;
}
void generate_class_OesCashAcctOverviewT(pybind11::module &m)
{
    pybind11::class_<OesCashAcctOverviewT> c(m, "OesCashAcctOverviewT");
    if constexpr (std::is_default_constructible_v<OesCashAcctOverviewT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "bankId", bankId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "isValid", isValid);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "cashType", cashType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "cashAcctStatus", cashAcctStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "isFundTrsfDisabled", isFundTrsfDisabled);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesCashAcctOverviewT, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(OesCashAcctOverviewT, c);
    m.attr("_OesCashAcctOverview") = c;
}
void generate_class_OesCustOverviewT(pybind11::module &m)
{
    pybind11::class_<OesCustOverviewT> c(m, "OesCustOverviewT");
    if constexpr (std::is_default_constructible_v<OesCustOverviewT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "custType", custType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "status", status);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "riskLevel", riskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "originRiskLevel", originRiskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "institutionFlag", institutionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "investorClass", investorClass);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "__CUST_BASE_filler1", __CUST_BASE_filler1);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "branchId", branchId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "__CUST_BASE_filler2", __CUST_BASE_filler2);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "custName", custName);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "spotCashAcct", spotCashAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "creditCashAcct", creditCashAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "optionCashAcct", optionCashAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "shSpotInvAcct", shSpotInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "shOptionInvAcct", shOptionInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "szSpotInvAcct", szSpotInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "szOptionInvAcct", szOptionInvAcct);
    c.AUTOCXXPY_DEF_PROPERTY(OesCustOverviewT, "__reserve", __reserve);
    AUTOCXXPY_POST_REGISTER_CLASS(OesCustOverviewT, c);
    m.attr("_OesCustOverview") = c;
}
void generate_class_OesClientOverviewT(pybind11::module &m)
{
    pybind11::class_<OesClientOverviewT> c(m, "OesClientOverviewT");
    if constexpr (std::is_default_constructible_v<OesClientOverviewT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "clientId", clientId);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "clientType", clientType);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "clientStatus", clientStatus);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "isApiForbidden", isApiForbidden);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "isBlockTrader", isBlockTrader);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "logonTime", logonTime);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "clientName", clientName);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "clientMemo", clientMemo);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "sseStkPbuId", sseStkPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "sseOptPbuId", sseOptPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "sseQualificationClass", sseQualificationClass);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "szseStkPbuId", szseStkPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "szseOptPbuId", szseOptPbuId);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "szseQualificationClass", szseQualificationClass);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "__filler3", __filler3);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "currOrdConnected", currOrdConnected);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "currRptConnected", currRptConnected);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "currQryConnected", currQryConnected);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "maxOrdConnect", maxOrdConnect);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "maxRptConnect", maxRptConnect);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "maxQryConnect", maxQryConnect);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "ordTrafficLimit", ordTrafficLimit);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "qryTrafficLimit", qryTrafficLimit);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "__reserve", __reserve);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "associatedCustCnt", associatedCustCnt);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "__filler4", __filler4);
    c.AUTOCXXPY_DEF_PROPERTY(OesClientOverviewT, "custItems", custItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesClientOverviewT, c);
    m.attr("_OesClientOverview") = c;
}
void generate_class_OesQryCommissionRateFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryCommissionRateFilterT> c(m, "OesQryCommissionRateFilterT");
    if constexpr (std::is_default_constructible_v<OesQryCommissionRateFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateFilterT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateFilterT, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCommissionRateFilterT, c);
    m.attr("_OesQryCommissionRateFilter") = c;
}
void generate_class_OesCommissionRateItemT(pybind11::module &m)
{
    pybind11::class_<OesCommissionRateItemT> c(m, "OesCommissionRateItemT");
    if constexpr (std::is_default_constructible_v<OesCommissionRateItemT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "bsType", bsType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "feeType", feeType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "currType", currType);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "calcFeeMode", calcFeeMode);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "feeRate", feeRate);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "minFee", minFee);
    c.AUTOCXXPY_DEF_PROPERTY(OesCommissionRateItemT, "maxFee", maxFee);
    AUTOCXXPY_POST_REGISTER_CLASS(OesCommissionRateItemT, c);
    m.attr("_OesCommissionRateItem") = c;
}
void generate_class_OesQryCommissionRateReqT(pybind11::module &m)
{
    pybind11::class_<OesQryCommissionRateReqT> c(m, "OesQryCommissionRateReqT");
    if constexpr (std::is_default_constructible_v<OesQryCommissionRateReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCommissionRateReqT, c);
    m.attr("_OesQryCommissionRateReq") = c;
}
void generate_class_OesQryCommissionRateRspT(pybind11::module &m)
{
    pybind11::class_<OesQryCommissionRateRspT> c(m, "OesQryCommissionRateRspT");
    if constexpr (std::is_default_constructible_v<OesQryCommissionRateRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryCommissionRateRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryCommissionRateRspT, c);
    m.attr("_OesQryCommissionRateRsp") = c;
}
void generate_class_OesQryFundTransferSerialFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryFundTransferSerialFilterT> c(m, "OesQryFundTransferSerialFilterT");
    if constexpr (std::is_default_constructible_v<OesQryFundTransferSerialFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialFilterT, "cashAcctId", cashAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialFilterT, "clSeqNo", clSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialFilterT, "clEnvId", clEnvId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryFundTransferSerialFilterT, c);
    m.attr("_OesQryFundTransferSerialFilter") = c;
}
void generate_class_OesQryFundTransferSerialReqT(pybind11::module &m)
{
    pybind11::class_<OesQryFundTransferSerialReqT> c(m, "OesQryFundTransferSerialReqT");
    if constexpr (std::is_default_constructible_v<OesQryFundTransferSerialReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryFundTransferSerialReqT, c);
    m.attr("_OesQryFundTransferSerialReq") = c;
}
void generate_class_OesQryFundTransferSerialRspT(pybind11::module &m)
{
    pybind11::class_<OesQryFundTransferSerialRspT> c(m, "OesQryFundTransferSerialRspT");
    if constexpr (std::is_default_constructible_v<OesQryFundTransferSerialRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryFundTransferSerialRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryFundTransferSerialRspT, c);
    m.attr("_OesQryFundTransferSerialRsp") = c;
}
void generate_class_OesQryLotWinningFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryLotWinningFilterT> c(m, "OesQryLotWinningFilterT");
    if constexpr (std::is_default_constructible_v<OesQryLotWinningFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "custId", custId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "invAcctId", invAcctId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "lotType", lotType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "startDate", startDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "endDate", endDate);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryLotWinningFilterT, c);
    m.attr("_OesQryLotWinningFilter") = c;
}
void generate_class_OesQryLotWinningReqT(pybind11::module &m)
{
    pybind11::class_<OesQryLotWinningReqT> c(m, "OesQryLotWinningReqT");
    if constexpr (std::is_default_constructible_v<OesQryLotWinningReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryLotWinningReqT, c);
    m.attr("_OesQryLotWinningReq") = c;
}
void generate_class_OesQryLotWinningRspT(pybind11::module &m)
{
    pybind11::class_<OesQryLotWinningRspT> c(m, "OesQryLotWinningRspT");
    if constexpr (std::is_default_constructible_v<OesQryLotWinningRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryLotWinningRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryLotWinningRspT, c);
    m.attr("_OesQryLotWinningRsp") = c;
}
void generate_class_OesQryIssueFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryIssueFilterT> c(m, "OesQryIssueFilterT");
    if constexpr (std::is_default_constructible_v<OesQryIssueFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueFilterT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryIssueFilterT, c);
    m.attr("_OesQryIssueFilter") = c;
}
void generate_class_OesQryIssueReqT(pybind11::module &m)
{
    pybind11::class_<OesQryIssueReqT> c(m, "OesQryIssueReqT");
    if constexpr (std::is_default_constructible_v<OesQryIssueReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryIssueReqT, c);
    m.attr("_OesQryIssueReq") = c;
}
void generate_class_OesQryIssueRspT(pybind11::module &m)
{
    pybind11::class_<OesQryIssueRspT> c(m, "OesQryIssueRspT");
    if constexpr (std::is_default_constructible_v<OesQryIssueRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryIssueRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryIssueRspT, c);
    m.attr("_OesQryIssueRsp") = c;
}
void generate_class_OesQryStockFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryStockFilterT> c(m, "OesQryStockFilterT");
    if constexpr (std::is_default_constructible_v<OesQryStockFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockFilterT, "securityId", securityId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockFilterT, "securityType", securityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockFilterT, "subSecurityType", subSecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryStockFilterT, c);
    m.attr("_OesQryStockFilter") = c;
}
void generate_class_OesQryStockReqT(pybind11::module &m)
{
    pybind11::class_<OesQryStockReqT> c(m, "OesQryStockReqT");
    if constexpr (std::is_default_constructible_v<OesQryStockReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryStockReqT, c);
    m.attr("_OesQryStockReq") = c;
}
void generate_class_OesQryStockRspT(pybind11::module &m)
{
    pybind11::class_<OesQryStockRspT> c(m, "OesQryStockRspT");
    if constexpr (std::is_default_constructible_v<OesQryStockRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryStockRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryStockRspT, c);
    m.attr("_OesQryStockRsp") = c;
}
void generate_class_OesQryEtfFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryEtfFilterT> c(m, "OesQryEtfFilterT");
    if constexpr (std::is_default_constructible_v<OesQryEtfFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfFilterT, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfFilterT, "mktId", mktId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfFilterT, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryEtfFilterT, c);
    m.attr("_OesQryEtfFilter") = c;
}
void generate_class_OesQryEtfReqT(pybind11::module &m)
{
    pybind11::class_<OesQryEtfReqT> c(m, "OesQryEtfReqT");
    if constexpr (std::is_default_constructible_v<OesQryEtfReqT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfReqT, "reqHead", reqHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfReqT, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryEtfReqT, c);
    m.attr("_OesQryEtfReq") = c;
}
void generate_class_OesQryEtfRspT(pybind11::module &m)
{
    pybind11::class_<OesQryEtfRspT> c(m, "OesQryEtfRspT");
    if constexpr (std::is_default_constructible_v<OesQryEtfRspT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfRspT, "rspHead", rspHead);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfRspT, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryEtfRspT, c);
    m.attr("_OesQryEtfRsp") = c;
}
void generate_class_OesQryEtfComponentFilterT(pybind11::module &m)
{
    pybind11::class_<OesQryEtfComponentFilterT> c(m, "OesQryEtfComponentFilterT");
    if constexpr (std::is_default_constructible_v<OesQryEtfComponentFilterT>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfComponentFilterT, "fundId", fundId);
    c.AUTOCXXPY_DEF_PROPERTY(OesQryEtfComponentFilterT, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(OesQryEtfComponentFilterT, c);
    m.attr("_OesQryEtfComponentFilter") = c;
}
