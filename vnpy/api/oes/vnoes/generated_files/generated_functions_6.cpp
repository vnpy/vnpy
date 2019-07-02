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


void generate_class_decltype_MdsChangePasswordReq_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_MdsChangePasswordReq::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_MdsChangePasswordReq::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_MdsChangePasswordReq::userInfo), c);
    module_vnoes::objects.emplace("decltype(_MdsChangePasswordReq::userInfo)", c);
}
void generate_class_MdsChangePasswordRsp(pybind11::object & parent)
{
    pybind11::class_<_MdsChangePasswordRsp> c(parent, "_MdsChangePasswordRsp");
    if constexpr (std::is_default_constructible_v<_MdsChangePasswordRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "encryptMethod", encryptMethod);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "__filler", __filler);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "username", username);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "userInfo", userInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "__filler2", __filler2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "transDate", transDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "transTime", transTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsChangePasswordRsp, "rejReason", rejReason);
    generate_class_decltype_MdsChangePasswordRsp_userInfo_(c);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsChangePasswordRsp, c);
    module_vnoes::objects.emplace("_MdsChangePasswordRsp", c);
}
void generate_class_decltype_MdsChangePasswordRsp_userInfo_(pybind11::object & parent)
{
    pybind11::class_<decltype(_MdsChangePasswordRsp::userInfo)> c(parent, "decltype(userInfo)");
    if constexpr (std::is_default_constructible_v<decltype(_MdsChangePasswordRsp::userInfo)>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "u64", u64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "i64", i64);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "u32", u32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "i32", i32);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), "c8", c8);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, decltype(_MdsChangePasswordRsp::userInfo), c);
    module_vnoes::objects.emplace("decltype(_MdsChangePasswordRsp::userInfo)", c);
}
void generate_class_MdsMktReqMsgBody(pybind11::object & parent)
{
    pybind11::class_<_MdsMktReqMsgBody> c(parent, "_MdsMktReqMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsMktReqMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "wholeMktDataReqBuf", wholeMktDataReqBuf);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "mktDataRequestReq", mktDataRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "testRequestReq", testRequestReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryMktDataSnapshotReq", qryMktDataSnapshotReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qrySecurityStatusReq", qrySecurityStatusReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryTrdSessionStatusReq", qryTrdSessionStatusReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qryStockStaticInfoReq", qryStockStaticInfoReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "qrySnapshotListReq", qrySnapshotListReq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktReqMsgBody, "changePasswordReq", changePasswordReq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktReqMsgBody, c);
    module_vnoes::objects.emplace("_MdsMktReqMsgBody", c);
}
void generate_class_MdsMktRspMsgBody(pybind11::object & parent)
{
    pybind11::class_<_MdsMktRspMsgBody> c(parent, "_MdsMktRspMsgBody");
    if constexpr (std::is_default_constructible_v<_MdsMktRspMsgBody>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "mktDataRequestRsp", mktDataRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "testRequestRsp", testRequestRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "mktDataSnapshot", mktDataSnapshot);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "trade", trade);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "order", order);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "trdSessionStatus", trdSessionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "securityStatus", securityStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "qryStockStaticInfoRsp", qryStockStaticInfoRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "qrySnapshotListRsp", qrySnapshotListRsp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsMktRspMsgBody, "changePasswordRsp", changePasswordRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsMktRspMsgBody, c);
    module_vnoes::objects.emplace("_MdsMktRspMsgBody", c);
}
void generate_class_MdsUdpPktHead(pybind11::object & parent)
{
    pybind11::class_<_MdsUdpPktHead> c(parent, "_MdsUdpPktHead");
    if constexpr (std::is_default_constructible_v<_MdsUdpPktHead>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "msgCnt", msgCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "pktSiz", pktSiz);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsUdpPktHead, "pktSeq", pktSeq);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsUdpPktHead, c);
    module_vnoes::objects.emplace("_MdsUdpPktHead", c);
}
void generate_class_MdsApiClientCfg(pybind11::object & parent)
{
    pybind11::class_<_MdsApiClientCfg> c(parent, "_MdsApiClientCfg");
    if constexpr (std::is_default_constructible_v<_MdsApiClientCfg>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "tcpChannelCfg", tcpChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "qryChannelCfg", qryChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpL1ChannelCfg", udpL1ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpL2ChannelCfg", udpL2ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpTick1ChannelCfg", udpTick1ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpTradeChannelCfg", udpTradeChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpTick2ChannelCfg", udpTick2ChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "udpOrderChannelCfg", udpOrderChannelCfg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientCfg, "subscribeInfo", subscribeInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsApiClientCfg, c);
    module_vnoes::objects.emplace("_MdsApiClientCfg", c);
}
void generate_class_MdsApiClientEnv(pybind11::object & parent)
{
    pybind11::class_<_MdsApiClientEnv> c(parent, "_MdsApiClientEnv");
    if constexpr (std::is_default_constructible_v<_MdsApiClientEnv>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "tcpChannel", tcpChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "qryChannel", qryChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpL1Channel", udpL1Channel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpL2Channel", udpL2Channel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpTick1Channel", udpTick1Channel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpTradeChannel", udpTradeChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpTick2Channel", udpTick2Channel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpOrderChannel", udpOrderChannel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _MdsApiClientEnv, "udpChannelGroup", udpChannelGroup);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _MdsApiClientEnv, c);
    module_vnoes::objects.emplace("_MdsApiClientEnv", c);
}
void generate_enum_eOesExchangeId(pybind11::object & parent)
{
    pybind11::enum_<_eOesExchangeId> e(parent, "_eOesExchangeId", pybind11::arithmetic());
    e.value("OES_EXCH_UNDEFINE", _eOesExchangeId::OES_EXCH_UNDEFINE);
    e.value("OES_EXCH_SSE", _eOesExchangeId::OES_EXCH_SSE);
    e.value("OES_EXCH_SZSE", _eOesExchangeId::OES_EXCH_SZSE);
    e.value("__MAX_OES_EXCH", _eOesExchangeId::__MAX_OES_EXCH);
    e.value("OES_EXCHANGE_TYPE_SSE", _eOesExchangeId::OES_EXCHANGE_TYPE_SSE);
    e.value("OES_EXCHANGE_TYPE_SZSE", _eOesExchangeId::OES_EXCHANGE_TYPE_SZSE);
    e.value("__OES_EXCH_ID_MAX_ALIGNED4", _eOesExchangeId::__OES_EXCH_ID_MAX_ALIGNED4);
    e.value("__OES_EXCH_ID_MAX_ALIGNED8", _eOesExchangeId::__OES_EXCH_ID_MAX_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eOesExchangeId", e);
}
void generate_enum_eOesMarketId(pybind11::object & parent)
{
    pybind11::enum_<_eOesMarketId> e(parent, "_eOesMarketId", pybind11::arithmetic());
    e.value("OES_MKT_UNDEFINE", _eOesMarketId::OES_MKT_UNDEFINE);
    e.value("OES_MKT_SH_ASHARE", _eOesMarketId::OES_MKT_SH_ASHARE);
    e.value("OES_MKT_SZ_ASHARE", _eOesMarketId::OES_MKT_SZ_ASHARE);
    e.value("OES_MKT_SH_OPTION", _eOesMarketId::OES_MKT_SH_OPTION);
    e.value("__OES_MKT_ID_MAX", _eOesMarketId::__OES_MKT_ID_MAX);
    e.value("OES_MKT_ID_UNDEFINE", _eOesMarketId::OES_MKT_ID_UNDEFINE);
    e.value("OES_MKT_ID_SH_A", _eOesMarketId::OES_MKT_ID_SH_A);
    e.value("OES_MKT_ID_SZ_A", _eOesMarketId::OES_MKT_ID_SZ_A);
    e.value("OES_MKT_ID_SH_OPT", _eOesMarketId::OES_MKT_ID_SH_OPT);
    e.value("__OES_MKT_ID_MAX_ALIGNED4", _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED4);
    e.value("__OES_MKT_ID_MAX_ALIGNED8", _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMarketId", e);
}
void generate_enum_eOesPlatformId(pybind11::object & parent)
{
    pybind11::enum_<_eOesPlatformId> e(parent, "_eOesPlatformId", pybind11::arithmetic());
    e.value("OES_PLATFORM_UNDEFINE", _eOesPlatformId::OES_PLATFORM_UNDEFINE);
    e.value("OES_PLATFORM_CASH_AUCTION", _eOesPlatformId::OES_PLATFORM_CASH_AUCTION);
    e.value("OES_PLATFORM_FINANCIAL_SERVICES", _eOesPlatformId::OES_PLATFORM_FINANCIAL_SERVICES);
    e.value("OES_PLATFORM_NON_TRADE", _eOesPlatformId::OES_PLATFORM_NON_TRADE);
    e.value("OES_PLATFORM_DERIVATIVE_AUCTION", _eOesPlatformId::OES_PLATFORM_DERIVATIVE_AUCTION);
    e.value("__OES_PLATFORM_ID_MAX", _eOesPlatformId::__OES_PLATFORM_ID_MAX);
    e.value("__OES_PLATFORM_ID_MAX_ALIGNED8", _eOesPlatformId::__OES_PLATFORM_ID_MAX_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eOesPlatformId", e);
}
void generate_enum_eOesMarketState(pybind11::object & parent)
{
    pybind11::enum_<_eOesMarketState> e(parent, "_eOesMarketState", pybind11::arithmetic());
    e.value("OES_MKT_STATE_UNDEFINE", _eOesMarketState::OES_MKT_STATE_UNDEFINE);
    e.value("OES_MKT_STATE_PRE_OPEN", _eOesMarketState::OES_MKT_STATE_PRE_OPEN);
    e.value("OES_MKT_STATE_OPEN_UP_COMING", _eOesMarketState::OES_MKT_STATE_OPEN_UP_COMING);
    e.value("OES_MKT_STATE_OPEN", _eOesMarketState::OES_MKT_STATE_OPEN);
    e.value("OES_MKT_STATE_HALT", _eOesMarketState::OES_MKT_STATE_HALT);
    e.value("OES_MKT_STATE_CLOSE", _eOesMarketState::OES_MKT_STATE_CLOSE);
    e.value("__OES_MKT_STATE_MAX", _eOesMarketState::__OES_MKT_STATE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMarketState", e);
}
void generate_enum_eOesTrdSessType(pybind11::object & parent)
{
    pybind11::enum_<_eOesTrdSessType> e(parent, "_eOesTrdSessType", pybind11::arithmetic());
    e.value("OES_TRD_SESS_TYPE_O", _eOesTrdSessType::OES_TRD_SESS_TYPE_O);
    e.value("OES_TRD_SESS_TYPE_T", _eOesTrdSessType::OES_TRD_SESS_TYPE_T);
    e.value("OES_TRD_SESS_TYPE_C", _eOesTrdSessType::OES_TRD_SESS_TYPE_C);
    e.value("__OES_TRD_SESS_TYPE_MAX", _eOesTrdSessType::__OES_TRD_SESS_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesTrdSessType", e);
}
void generate_enum_eOesProductType(pybind11::object & parent)
{
    pybind11::enum_<_eOesProductType> e(parent, "_eOesProductType", pybind11::arithmetic());
    e.value("OES_PRODUCT_TYPE_UNDEFINE", _eOesProductType::OES_PRODUCT_TYPE_UNDEFINE);
    e.value("OES_PRODUCT_TYPE_EQUITY", _eOesProductType::OES_PRODUCT_TYPE_EQUITY);
    e.value("OES_PRODUCT_TYPE_BOND_STD", _eOesProductType::OES_PRODUCT_TYPE_BOND_STD);
    e.value("OES_PRODUCT_TYPE_IPO", _eOesProductType::OES_PRODUCT_TYPE_IPO);
    e.value("OES_PRODUCT_TYPE_ALLOTMENT", _eOesProductType::OES_PRODUCT_TYPE_ALLOTMENT);
    e.value("OES_PRODUCT_TYPE_OPTION", _eOesProductType::OES_PRODUCT_TYPE_OPTION);
    e.value("__OES_PRODUCT_TYPE_MAX", _eOesProductType::__OES_PRODUCT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesProductType", e);
}
void generate_enum_eOesSecurityType(pybind11::object & parent)
{
    pybind11::enum_<_eOesSecurityType> e(parent, "_eOesSecurityType", pybind11::arithmetic());
    e.value("OES_SECURITY_TYPE_UNDEFINE", _eOesSecurityType::OES_SECURITY_TYPE_UNDEFINE);
    e.value("OES_SECURITY_TYPE_STOCK", _eOesSecurityType::OES_SECURITY_TYPE_STOCK);
    e.value("OES_SECURITY_TYPE_BOND", _eOesSecurityType::OES_SECURITY_TYPE_BOND);
    e.value("OES_SECURITY_TYPE_ETF", _eOesSecurityType::OES_SECURITY_TYPE_ETF);
    e.value("OES_SECURITY_TYPE_FUND", _eOesSecurityType::OES_SECURITY_TYPE_FUND);
    e.value("OES_SECURITY_TYPE_OPTION", _eOesSecurityType::OES_SECURITY_TYPE_OPTION);
    e.value("__OES_SECURITY_TYPE_MAX", _eOesSecurityType::__OES_SECURITY_TYPE_MAX);
    e.value("__OES_SECURITY_TYPE_NOT_SUPPORT", _eOesSecurityType::__OES_SECURITY_TYPE_NOT_SUPPORT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityType", e);
}
void generate_enum_eOesSubSecurityType(pybind11::object & parent)
{
    pybind11::enum_<_eOesSubSecurityType> e(parent, "_eOesSubSecurityType", pybind11::arithmetic());
    e.value("OES_SUB_SECURITY_TYPE_UNDEFINE", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_UNDEFINE);
    e.value("__OES_SUB_SECURITY_TYPE_STOCK_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MIN);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_ASH", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_ASH);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_SME", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_SME);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_GEM", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_GEM);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_KSH", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_KSH);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_KCDR", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_KCDR);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_CDR", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_CDR);
    e.value("OES_SUB_SECURITY_TYPE_STOCK_HLTCDR", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_HLTCDR);
    e.value("__OES_SUB_SECURITY_TYPE_STOCK_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_BOND_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MIN);
    e.value("OES_SUB_SECURITY_TYPE_BOND_GBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_GBF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_CBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CBF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_CPF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CPF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_CCF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CCF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_FBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_FBF);
    e.value("OES_SUB_SECURITY_TYPE_BOND_PRP", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_PRP);
    e.value("OES_SUB_SECURITY_TYPE_BOND_STD", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_STD);
    e.value("__OES_SUB_SECURITY_TYPE_BOND_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_ETF_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MIN);
    e.value("OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT);
    e.value("OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT);
    e.value("OES_SUB_SECURITY_TYPE_ETF_BOND", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_BOND);
    e.value("OES_SUB_SECURITY_TYPE_ETF_CURRENCY", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CURRENCY);
    e.value("OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER);
    e.value("OES_SUB_SECURITY_TYPE_ETF_GOLD", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_GOLD);
    e.value("__OES_SUB_SECURITY_TYPE_ETF_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_FUND_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MIN);
    e.value("OES_SUB_SECURITY_TYPE_FUND_LOF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_LOF);
    e.value("OES_SUB_SECURITY_TYPE_FUND_CEF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_CEF);
    e.value("OES_SUB_SECURITY_TYPE_FUND_OEF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_OEF);
    e.value("OES_SUB_SECURITY_TYPE_FUND_GRADED", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_GRADED);
    e.value("__OES_SUB_SECURITY_TYPE_FUND_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_OPTION_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MIN);
    e.value("OES_SUB_SECURITY_TYPE_OPTION_ETF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_ETF);
    e.value("OES_SUB_SECURITY_TYPE_OPTION_STOCK", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_STOCK);
    e.value("__OES_SUB_SECURITY_TYPE_OPTION_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MAX);
    e.value("__OES_SUB_SECURITY_TYPE_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSubSecurityType", e);
}
void generate_enum_eOesSecurityLevel(pybind11::object & parent)
{
    pybind11::enum_<_eOesSecurityLevel> e(parent, "_eOesSecurityLevel", pybind11::arithmetic());
    e.value("OES_SECURITY_LEVEL_UNDEFINE", _eOesSecurityLevel::OES_SECURITY_LEVEL_UNDEFINE);
    e.value("OES_SECURITY_LEVEL_N", _eOesSecurityLevel::OES_SECURITY_LEVEL_N);
    e.value("OES_SECURITY_LEVEL_XST", _eOesSecurityLevel::OES_SECURITY_LEVEL_XST);
    e.value("OES_SECURITY_LEVEL_ST", _eOesSecurityLevel::OES_SECURITY_LEVEL_ST);
    e.value("OES_SECURITY_LEVEL_P", _eOesSecurityLevel::OES_SECURITY_LEVEL_P);
    e.value("OES_SECURITY_LEVEL_T", _eOesSecurityLevel::OES_SECURITY_LEVEL_T);
    e.value("OES_SECURITY_LEVEL_U", _eOesSecurityLevel::OES_SECURITY_LEVEL_U);
    e.value("OES_SECURITY_LEVEL_B", _eOesSecurityLevel::OES_SECURITY_LEVEL_B);
    e.value("__OES_SECURITY_LEVEL_MAX", _eOesSecurityLevel::__OES_SECURITY_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityLevel", e);
}
void generate_enum_eOesSecurityRiskLevel(pybind11::object & parent)
{
    pybind11::enum_<_eOesSecurityRiskLevel> e(parent, "_eOesSecurityRiskLevel", pybind11::arithmetic());
    e.value("OES_RISK_LEVEL_VERY_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_LOW);
    e.value("OES_RISK_LEVEL_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_LOW);
    e.value("OES_RISK_LEVEL_MEDIUM_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_LOW);
    e.value("OES_RISK_LEVEL_MEDIUM", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM);
    e.value("OES_RISK_LEVEL_MEDIUM_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_HIGH);
    e.value("OES_RISK_LEVEL_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_HIGH);
    e.value("OES_RISK_LEVEL_VERY_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_HIGH);
    e.value("__OES_RISK_LEVEL_MAX", _eOesSecurityRiskLevel::__OES_RISK_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityRiskLevel", e);
}
void generate_enum_eOesSecuritySuspFlag(pybind11::object & parent)
{
    pybind11::enum_<_eOesSecuritySuspFlag> e(parent, "_eOesSecuritySuspFlag", pybind11::arithmetic());
    e.value("OES_SUSPFLAG_NONE", _eOesSecuritySuspFlag::OES_SUSPFLAG_NONE);
    e.value("OES_SUSPFLAG_EXCHANGE", _eOesSecuritySuspFlag::OES_SUSPFLAG_EXCHANGE);
    e.value("OES_SUSPFLAG_BROKER", _eOesSecuritySuspFlag::OES_SUSPFLAG_BROKER);
    e.value("__OES_SUSPFLAG_OTHER", _eOesSecuritySuspFlag::__OES_SUSPFLAG_OTHER);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecuritySuspFlag", e);
}
void generate_enum_eOesLotType(pybind11::object & parent)
{
    pybind11::enum_<_eOesLotType> e(parent, "_eOesLotType", pybind11::arithmetic());
    e.value("OES_LOT_TYPE_UNDEFINE", _eOesLotType::OES_LOT_TYPE_UNDEFINE);
    e.value("OES_LOT_TYPE_FAILED", _eOesLotType::OES_LOT_TYPE_FAILED);
    e.value("OES_LOT_TYPE_ASSIGNMENT", _eOesLotType::OES_LOT_TYPE_ASSIGNMENT);
    e.value("OES_LOT_TYPE_LOTTERY", _eOesLotType::OES_LOT_TYPE_LOTTERY);
    e.value("__OES_LOT_TYPE_MAX", _eOesLotType::__OES_LOT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesLotType", e);
}
void generate_enum_eOesLotRejReason(pybind11::object & parent)
{
    pybind11::enum_<_eOesLotRejReason> e(parent, "_eOesLotRejReason", pybind11::arithmetic());
    e.value("OES_LOT_REJ_REASON_DUPLICATE", _eOesLotRejReason::OES_LOT_REJ_REASON_DUPLICATE);
    e.value("OES_LOT_REJ_REASON_INVALID_DUPLICATE", _eOesLotRejReason::OES_LOT_REJ_REASON_INVALID_DUPLICATE);
    e.value("OES_LOT_REJ_REASON_OFFLINE_FIRST", _eOesLotRejReason::OES_LOT_REJ_REASON_OFFLINE_FIRST);
    e.value("OES_LOT_REJ_REASON_BAD_RECORD", _eOesLotRejReason::OES_LOT_REJ_REASON_BAD_RECORD);
    e.value("OES_LOT_REJ_REASON_UNKNOW", _eOesLotRejReason::OES_LOT_REJ_REASON_UNKNOW);
    e.export_values();
    module_vnoes::objects.emplace("_eOesLotRejReason", e);
}
void generate_enum_eOesOrdStatus(pybind11::object & parent)
{
    pybind11::enum_<_eOesOrdStatus> e(parent, "_eOesOrdStatus", pybind11::arithmetic());
    e.value("OES_ORD_STATUS_UNDEFINE", _eOesOrdStatus::OES_ORD_STATUS_UNDEFINE);
    e.value("OES_ORD_STATUS_NEW", _eOesOrdStatus::OES_ORD_STATUS_NEW);
    e.value("OES_ORD_STATUS_DECLARED", _eOesOrdStatus::OES_ORD_STATUS_DECLARED);
    e.value("OES_ORD_STATUS_PARTIALLY_FILLED", _eOesOrdStatus::OES_ORD_STATUS_PARTIALLY_FILLED);
    e.value("__OES_ORD_STATUS_FINAL_MIN", _eOesOrdStatus::__OES_ORD_STATUS_FINAL_MIN);
    e.value("OES_ORD_STATUS_CANCEL_DONE", _eOesOrdStatus::OES_ORD_STATUS_CANCEL_DONE);
    e.value("OES_ORD_STATUS_PARTIALLY_CANCELED", _eOesOrdStatus::OES_ORD_STATUS_PARTIALLY_CANCELED);
    e.value("OES_ORD_STATUS_CANCELED", _eOesOrdStatus::OES_ORD_STATUS_CANCELED);
    e.value("OES_ORD_STATUS_FILLED", _eOesOrdStatus::OES_ORD_STATUS_FILLED);
    e.value("__OES_ORD_STATUS_VALID_MAX", _eOesOrdStatus::__OES_ORD_STATUS_VALID_MAX);
    e.value("__OES_ORD_STATUS_INVALID_MIN", _eOesOrdStatus::__OES_ORD_STATUS_INVALID_MIN);
    e.value("OES_ORD_STATUS_INVALID_OES", _eOesOrdStatus::OES_ORD_STATUS_INVALID_OES);
    e.value("OES_ORD_STATUS_INVALID_SH_F", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_F);
    e.value("OES_ORD_STATUS_INVALID_SH_E", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_E);
    e.value("OES_ORD_STATUS_INVALID_SH_COMM", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_COMM);
    e.value("OES_ORD_STATUS_INVALID_SZ_F", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_F);
    e.value("OES_ORD_STATUS_INVALID_SZ_E", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_E);
    e.value("OES_ORD_STATUS_INVALID_SZ_REJECT", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_REJECT);
    e.value("OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN);
    e.value("__OES_ORD_STATUS_INVALID_MAX", _eOesOrdStatus::__OES_ORD_STATUS_INVALID_MAX);
    e.value("OES_ORD_STATUS_NORMAL", _eOesOrdStatus::OES_ORD_STATUS_NORMAL);
    e.value("OES_ORD_STATUS_DECLARING", _eOesOrdStatus::OES_ORD_STATUS_DECLARING);
    e.value("__OES_ORD_STATUS_INVALID_OES", _eOesOrdStatus::__OES_ORD_STATUS_INVALID_OES);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdStatus", e);
}
void generate_enum_eOesOrdType(pybind11::object & parent)
{
    pybind11::enum_<_eOesOrdType> e(parent, "_eOesOrdType", pybind11::arithmetic());
    e.value("OES_ORD_TYPE_LMT", _eOesOrdType::OES_ORD_TYPE_LMT);
    e.value("OES_ORD_TYPE_LMT_FOK", _eOesOrdType::OES_ORD_TYPE_LMT_FOK);
    e.value("__OES_ORD_TYPE_LMT_MAX", _eOesOrdType::__OES_ORD_TYPE_LMT_MAX);
    e.value("OES_ORD_TYPE_MTL_BEST_5", _eOesOrdType::OES_ORD_TYPE_MTL_BEST_5);
    e.value("OES_ORD_TYPE_MTL_BEST", _eOesOrdType::OES_ORD_TYPE_MTL_BEST);
    e.value("OES_ORD_TYPE_MTL_SAMEPARTY_BEST", _eOesOrdType::OES_ORD_TYPE_MTL_SAMEPARTY_BEST);
    e.value("__OES_ORD_TYPE_MTL_MAX", _eOesOrdType::__OES_ORD_TYPE_MTL_MAX);
    e.value("OES_ORD_TYPE_FAK_BEST_5", _eOesOrdType::OES_ORD_TYPE_FAK_BEST_5);
    e.value("OES_ORD_TYPE_FAK", _eOesOrdType::OES_ORD_TYPE_FAK);
    e.value("__OES_ORD_TYPE_FAK_MAX", _eOesOrdType::__OES_ORD_TYPE_FAK_MAX);
    e.value("OES_ORD_TYPE_FOK", _eOesOrdType::OES_ORD_TYPE_FOK);
    e.value("__OES_ORD_TYPE_FOK_MAX", _eOesOrdType::__OES_ORD_TYPE_FOK_MAX);
    e.value("__OES_ORD_TYPE_MAX", _eOesOrdType::__OES_ORD_TYPE_MAX);
    e.value("__OES_ORD_TYPE_MAX_ALIGNED", _eOesOrdType::__OES_ORD_TYPE_MAX_ALIGNED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdType", e);
}
void generate_enum_eOesOrdTypeSh(pybind11::object & parent)
{
    pybind11::enum_<_eOesOrdTypeSh> e(parent, "_eOesOrdTypeSh", pybind11::arithmetic());
    e.value("OES_ORD_TYPE_SH_LMT", _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT);
    e.value("OES_ORD_TYPE_SH_LMT_FOK", _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT_FOK);
    e.value("OES_ORD_TYPE_SH_MTL_BEST_5", _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_BEST_5);
    e.value("OES_ORD_TYPE_SH_MTL_BEST", _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_BEST);
    e.value("OES_ORD_TYPE_SH_MTL_SAMEPARTY_BEST", _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_SAMEPARTY_BEST);
    e.value("OES_ORD_TYPE_SH_FAK_BEST_5", _eOesOrdTypeSh::OES_ORD_TYPE_SH_FAK_BEST_5);
    e.value("OES_ORD_TYPE_SH_FOK", _eOesOrdTypeSh::OES_ORD_TYPE_SH_FOK);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdTypeSh", e);
}
void generate_enum_eOesOrdTypeSz(pybind11::object & parent)
{
    pybind11::enum_<_eOesOrdTypeSz> e(parent, "_eOesOrdTypeSz", pybind11::arithmetic());
    e.value("OES_ORD_TYPE_SZ_LMT", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT);
    e.value("OES_ORD_TYPE_SZ_LMT_FOK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT_FOK);
    e.value("OES_ORD_TYPE_SZ_MTL_BEST", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_BEST);
    e.value("OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST);
    e.value("OES_ORD_TYPE_SZ_FAK_BEST_5", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK_BEST_5);
    e.value("OES_ORD_TYPE_SZ_FAK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK);
    e.value("OES_ORD_TYPE_SZ_FOK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FOK);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdTypeSz", e);
}
void generate_enum_eOesBuySellType(pybind11::object & parent)
{
    pybind11::enum_<_eOesBuySellType> e(parent, "_eOesBuySellType", pybind11::arithmetic());
    e.value("OES_BS_TYPE_UNDEFINE", _eOesBuySellType::OES_BS_TYPE_UNDEFINE);
    e.value("OES_BS_TYPE_BUY", _eOesBuySellType::OES_BS_TYPE_BUY);
    e.value("OES_BS_TYPE_SELL", _eOesBuySellType::OES_BS_TYPE_SELL);
    e.value("OES_BS_TYPE_CREATION", _eOesBuySellType::OES_BS_TYPE_CREATION);
    e.value("OES_BS_TYPE_REDEMPTION", _eOesBuySellType::OES_BS_TYPE_REDEMPTION);
    e.value("OES_BS_TYPE_CREDIT_BUY", _eOesBuySellType::OES_BS_TYPE_CREDIT_BUY);
    e.value("OES_BS_TYPE_CREDIT_SELL", _eOesBuySellType::OES_BS_TYPE_CREDIT_SELL);
    e.value("OES_BS_TYPE_SUBSCRIPTION", _eOesBuySellType::OES_BS_TYPE_SUBSCRIPTION);
    e.value("OES_BS_TYPE_ALLOTMENT", _eOesBuySellType::OES_BS_TYPE_ALLOTMENT);
    e.value("__OES_BS_TYPE_MAX_SPOT", _eOesBuySellType::__OES_BS_TYPE_MAX_SPOT);
    e.value("__OES_BS_TYPE_MIN_OPTION", _eOesBuySellType::__OES_BS_TYPE_MIN_OPTION);
    e.value("OES_BS_TYPE_BUY_OPEN", _eOesBuySellType::OES_BS_TYPE_BUY_OPEN);
    e.value("OES_BS_TYPE_BUY_CLOSE", _eOesBuySellType::OES_BS_TYPE_BUY_CLOSE);
    e.value("OES_BS_TYPE_SELL_OPEN", _eOesBuySellType::OES_BS_TYPE_SELL_OPEN);
    e.value("OES_BS_TYPE_SELL_CLOSE", _eOesBuySellType::OES_BS_TYPE_SELL_CLOSE);
    e.value("OES_BS_TYPE_COVERED_OPEN", _eOesBuySellType::OES_BS_TYPE_COVERED_OPEN);
    e.value("OES_BS_TYPE_COVERED_CLOSE", _eOesBuySellType::OES_BS_TYPE_COVERED_CLOSE);
    e.value("OES_BS_TYPE_OPTION_EXERCISE", _eOesBuySellType::OES_BS_TYPE_OPTION_EXERCISE);
    e.value("OES_BS_TYPE_UNDERLYING_FREEZE", _eOesBuySellType::OES_BS_TYPE_UNDERLYING_FREEZE);
    e.value("OES_BS_TYPE_UNDERLYING_UNFREEZE", _eOesBuySellType::OES_BS_TYPE_UNDERLYING_UNFREEZE);
    e.value("__OES_BS_TYPE_MAX_OPTION", _eOesBuySellType::__OES_BS_TYPE_MAX_OPTION);
    e.value("OES_BS_TYPE_CANCEL", _eOesBuySellType::OES_BS_TYPE_CANCEL);
    e.value("__OES_BS_TYPE_MAX_TRADING", _eOesBuySellType::__OES_BS_TYPE_MAX_TRADING);
    e.value("__OES_BS_TYPE_MIN_MGR", _eOesBuySellType::__OES_BS_TYPE_MIN_MGR);
    e.value("OES_BS_TYPE_SSE_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SSE_DESIGNATION);
    e.value("OES_BS_TYPE_SSE_RECALL_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SSE_RECALL_DESIGNATION);
    e.value("OES_BS_TYPE_SZSE_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SZSE_DESIGNATION);
    e.value("OES_BS_TYPE_SZSE_CANCEL_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SZSE_CANCEL_DESIGNATION);
    e.value("__OES_BS_TYPE_MAX_MGR", _eOesBuySellType::__OES_BS_TYPE_MAX_MGR);
    e.value("__OES_BS_TYPE_MAX", _eOesBuySellType::__OES_BS_TYPE_MAX);
    e.value("OES_BS_TYPE_B", _eOesBuySellType::OES_BS_TYPE_B);
    e.value("OES_BS_TYPE_S", _eOesBuySellType::OES_BS_TYPE_S);
    e.value("OES_BS_TYPE_KB", _eOesBuySellType::OES_BS_TYPE_KB);
    e.value("OES_BS_TYPE_KS", _eOesBuySellType::OES_BS_TYPE_KS);
    e.value("OES_BS_TYPE_CB", _eOesBuySellType::OES_BS_TYPE_CB);
    e.value("OES_BS_TYPE_CS", _eOesBuySellType::OES_BS_TYPE_CS);
    e.value("OES_BS_TYPE_BO", _eOesBuySellType::OES_BS_TYPE_BO);
    e.value("OES_BS_TYPE_BC", _eOesBuySellType::OES_BS_TYPE_BC);
    e.value("OES_BS_TYPE_SO", _eOesBuySellType::OES_BS_TYPE_SO);
    e.value("OES_BS_TYPE_SC", _eOesBuySellType::OES_BS_TYPE_SC);
    e.value("OES_BS_TYPE_CO", _eOesBuySellType::OES_BS_TYPE_CO);
    e.value("OES_BS_TYPE_CC", _eOesBuySellType::OES_BS_TYPE_CC);
    e.value("OES_BS_TYPE_TE", _eOesBuySellType::OES_BS_TYPE_TE);
    e.value("OES_BS_TYPE_UF", _eOesBuySellType::OES_BS_TYPE_UF);
    e.value("OES_BS_TYPE_UU", _eOesBuySellType::OES_BS_TYPE_UU);
    e.export_values();
    module_vnoes::objects.emplace("_eOesBuySellType", e);
}
void generate_enum_eOesOrdDir(pybind11::object & parent)
{
    pybind11::enum_<_eOesOrdDir> e(parent, "_eOesOrdDir", pybind11::arithmetic());
    e.value("OES_ORD_DIR_BUY", _eOesOrdDir::OES_ORD_DIR_BUY);
    e.value("OES_ORD_DIR_SELL", _eOesOrdDir::OES_ORD_DIR_SELL);
    e.value("__OES_ORD_DIR_MAX", _eOesOrdDir::__OES_ORD_DIR_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdDir", e);
}
void generate_enum_eOesEtfTrdCnfmType(pybind11::object & parent)
{
    pybind11::enum_<_eOesEtfTrdCnfmType> e(parent, "_eOesEtfTrdCnfmType", pybind11::arithmetic());
    e.value("OES_ETF_TRDCNFM_TYPE_NONE", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_NONE);
    e.value("OES_ETF_TRDCNFM_TYPE_ETF_FIRST", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_ETF_FIRST);
    e.value("OES_ETF_TRDCNFM_TYPE_CMPOENT", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_CMPOENT);
    e.value("OES_ETF_TRDCNFM_TYPE_CASH", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_CASH);
    e.value("OES_ETF_TRDCNFM_TYPE_ETF_LAST", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_ETF_LAST);
    e.value("__OES_ETF_TRDCNFM_TYPE_MAX", _eOesEtfTrdCnfmType::__OES_ETF_TRDCNFM_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesEtfTrdCnfmType", e);
}
void generate_enum_eOesEtfSubFlag(pybind11::object & parent)
{
    pybind11::enum_<_eOesEtfSubFlag> e(parent, "_eOesEtfSubFlag", pybind11::arithmetic());
    e.value("OES_ETF_SUBFLAG_FORBID_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_FORBID_SUB);
    e.value("OES_ETF_SUBFLAG_ALLOW_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_ALLOW_SUB);
    e.value("OES_ETF_SUBFLAG_MUST_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_MUST_SUB);
    e.value("OES_ETF_SUBFLAG_SZ_REFUND_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_SZ_REFUND_SUB);
    e.value("OES_ETF_SUBFLAG_SZ_MUST_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_SZ_MUST_SUB);
    e.value("OES_ETF_SUBFLAG_OTHER_REFUND_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_OTHER_REFUND_SUB);
    e.value("OES_ETF_SUBFLAG_OTHER_MUST_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_OTHER_MUST_SUB);
    e.export_values();
    module_vnoes::objects.emplace("_eOesEtfSubFlag", e);
}
void generate_enum_eOesExecType(pybind11::object & parent)
{
    pybind11::enum_<_eOesExecType> e(parent, "_eOesExecType", pybind11::arithmetic());
    e.value("OES_EXECTYPE_UNDEFINE", _eOesExecType::OES_EXECTYPE_UNDEFINE);
    e.value("OES_EXECTYPE_INSERT", _eOesExecType::OES_EXECTYPE_INSERT);
    e.value("OES_EXECTYPE_CONFIRMED", _eOesExecType::OES_EXECTYPE_CONFIRMED);
    e.value("OES_EXECTYPE_CANCELLED", _eOesExecType::OES_EXECTYPE_CANCELLED);
    e.value("OES_EXECTYPE_AUTO_CANCELLED", _eOesExecType::OES_EXECTYPE_AUTO_CANCELLED);
    e.value("OES_EXECTYPE_REJECT", _eOesExecType::OES_EXECTYPE_REJECT);
    e.value("OES_EXECTYPE_TRADE", _eOesExecType::OES_EXECTYPE_TRADE);
    e.value("__OES_EXECTYPE_MAX", _eOesExecType::__OES_EXECTYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesExecType", e);
}
void generate_enum_eOesCurrType(pybind11::object & parent)
{
    pybind11::enum_<_eOesCurrType> e(parent, "_eOesCurrType", pybind11::arithmetic());
    e.value("OES_CURR_TYPE_RMB", _eOesCurrType::OES_CURR_TYPE_RMB);
    e.value("OES_CURR_TYPE_HKD", _eOesCurrType::OES_CURR_TYPE_HKD);
    e.value("OES_CURR_TYPE_USD", _eOesCurrType::OES_CURR_TYPE_USD);
    e.value("__OES_CURR_TYPE_MAX", _eOesCurrType::__OES_CURR_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCurrType", e);
}
void generate_enum_eOesFeeType(pybind11::object & parent)
{
    pybind11::enum_<_eOesFeeType> e(parent, "_eOesFeeType", pybind11::arithmetic());
    e.value("OES_FEE_TYPE_EXCHANGE_STAMP", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_STAMP);
    e.value("OES_FEE_TYPE_EXCHANGE_TRANSFER", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_TRANSFER);
    e.value("OES_FEE_TYPE_EXCHANGE_SETTLEMENT", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_SETTLEMENT);
    e.value("OES_FEE_TYPE_EXCHANGE_TRADE_RULE", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_TRADE_RULE);
    e.value("OES_FEE_TYPE_EXCHANGE_EXCHANGE", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_EXCHANGE);
    e.value("OES_FEE_TYPE_EXCHANGE_ADMINFER", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_ADMINFER);
    e.value("OES_FEE_TYPE_EXCHANGE_OTHER", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_OTHER);
    e.value("__OES_FEE_TYPE_EXCHANGE_MAX", _eOesFeeType::__OES_FEE_TYPE_EXCHANGE_MAX);
    e.value("OES_FEE_TYPE_BROKER_BACK_END", _eOesFeeType::OES_FEE_TYPE_BROKER_BACK_END);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFeeType", e);
}
void generate_enum_eOesCalcFeeMode(pybind11::object & parent)
{
    pybind11::enum_<_eOesCalcFeeMode> e(parent, "_eOesCalcFeeMode", pybind11::arithmetic());
    e.value("OES_CALC_FEE_MODE_AMOUNT", _eOesCalcFeeMode::OES_CALC_FEE_MODE_AMOUNT);
    e.value("OES_CALC_FEE_MODE_QTY", _eOesCalcFeeMode::OES_CALC_FEE_MODE_QTY);
    e.value("OES_CALC_FEE_MODE_ORD", _eOesCalcFeeMode::OES_CALC_FEE_MODE_ORD);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCalcFeeMode", e);
}
void generate_enum_eOesFundTrsfDirect(pybind11::object & parent)
{
    pybind11::enum_<_eOesFundTrsfDirect> e(parent, "_eOesFundTrsfDirect", pybind11::arithmetic());
    e.value("OES_FUND_TRSF_DIRECT_IN", _eOesFundTrsfDirect::OES_FUND_TRSF_DIRECT_IN);
    e.value("OES_FUND_TRSF_DIRECT_OUT", _eOesFundTrsfDirect::OES_FUND_TRSF_DIRECT_OUT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFundTrsfDirect", e);
}
void generate_enum_eOesFundTrsfType(pybind11::object & parent)
{
    pybind11::enum_<_eOesFundTrsfType> e(parent, "_eOesFundTrsfType", pybind11::arithmetic());
    e.value("OES_FUND_TRSF_TYPE_OES_BANK", _eOesFundTrsfType::OES_FUND_TRSF_TYPE_OES_BANK);
    e.value("OES_FUND_TRSF_TYPE_OES_COUNTER", _eOesFundTrsfType::OES_FUND_TRSF_TYPE_OES_COUNTER);
    e.value("OES_FUND_TRSF_TYPE_COUNTER_BANK", _eOesFundTrsfType::OES_FUND_TRSF_TYPE_COUNTER_BANK);
    e.value("__OES_FUND_TRSF_TYPE_MAX", _eOesFundTrsfType::__OES_FUND_TRSF_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFundTrsfType", e);
}
void generate_enum_eOesFundTrsfStatus(pybind11::object & parent)
{
    pybind11::enum_<_eOesFundTrsfStatus> e(parent, "_eOesFundTrsfStatus", pybind11::arithmetic());
    e.value("OES_FUND_TRSF_STS_UNDECLARED", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_UNDECLARED);
    e.value("OES_FUND_TRSF_STS_DECLARED", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DECLARED);
    e.value("OES_FUND_TRSF_STS_WAIT_DONE", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_WAIT_DONE);
    e.value("OES_FUND_TRSF_STS_DONE", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DONE);
    e.value("__OES_FUND_TRSF_STS_ROLLBACK_MIN", _eOesFundTrsfStatus::__OES_FUND_TRSF_STS_ROLLBACK_MIN);
    e.value("OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK);
    e.value("OES_FUND_TRSF_STS_DECLARED_ROLLBACK", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DECLARED_ROLLBACK);
    e.value("__OES_FUND_TRSF_STS_INVALID_MIN", _eOesFundTrsfStatus::__OES_FUND_TRSF_STS_INVALID_MIN);
    e.value("OES_FUND_TRSF_STS_INVALID_OES", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_INVALID_OES);
    e.value("OES_FUND_TRSF_STS_INVALID_COUNTER", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_INVALID_COUNTER);
    e.value("OES_FUND_TRSF_STS_SUSPENDED", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_SUSPENDED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFundTrsfStatus", e);
}
void generate_enum_eOesAcctType(pybind11::object & parent)
{
    pybind11::enum_<_eOesAcctType> e(parent, "_eOesAcctType", pybind11::arithmetic());
    e.value("OES_ACCT_TYPE_NORMAL", _eOesAcctType::OES_ACCT_TYPE_NORMAL);
    e.value("OES_ACCT_TYPE_CREDIT", _eOesAcctType::OES_ACCT_TYPE_CREDIT);
    e.value("OES_ACCT_TYPE_OPTION", _eOesAcctType::OES_ACCT_TYPE_OPTION);
    e.value("__OES_ACCT_TYPE_MAX", _eOesAcctType::__OES_ACCT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesAcctType", e);
}
