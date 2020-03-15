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


void generate_vnoes_classes(pybind11::module & parent)
{
    generate_class_OesOrdReq(parent);
    generate_class_OesOrdCancelReq(parent);
    generate_class_OesOrdReject(parent);
    generate_class_OesOrdCnfm(parent);
    generate_class_OesTrdBaseInfo(parent);
    generate_class_OesTrdCnfm(parent);
    generate_class_OesLotWinningBaseInfo(parent);
    generate_class_OesFundTrsfBaseInfo(parent);
    generate_class_OesFundTrsfReq(parent);
    generate_class_OesFundTrsfReject(parent);
    generate_class_OesFundTrsfReport(parent);
    generate_class_OesIssueBaseInfo(parent);
    generate_class_OesPriceLimit(parent);
    generate_class_OesStockBaseInfo(parent);
    generate_class_OesEtfBaseInfo(parent);
    generate_class_OesEtfComponentBaseInfo(parent);
    generate_class_OesOptionBaseInfo(parent);
    generate_class_OesCashAssetBaseInfo(parent);
    generate_class_OesCustBaseInfo(parent);
    generate_class_OesInvAcctBaseInfo(parent);
    generate_class_OesStkHoldingBaseInfo(parent);
    generate_class_OesOptHoldingBaseInfo(parent);
    generate_class_OesMarketStateInfo(parent);
    generate_class_OesTradingPermissionEntry(parent);
    generate_class_SMsgHead(parent);
    generate_class_OesQryCursor(parent);
    generate_class_OesQryReqHead(parent);
    generate_class_OesQryRspHead(parent);
    generate_class_OesQryOrdFilter(parent);
    generate_class_OesQryOrdReq(parent);
    generate_class_OesQryOrdRsp(parent);
    generate_class_OesQryTrdFilter(parent);
    generate_class_OesQryTrdReq(parent);
    generate_class_OesQryTrdRsp(parent);
    generate_class_OesQryCashAssetFilter(parent);
    generate_class_OesCashAssetItem(parent);
    generate_class_OesQryCashAssetReq(parent);
    generate_class_OesQryCashAssetRsp(parent);
    generate_class_OesCounterCashItem(parent);
    generate_class_OesQryCounterCashReq(parent);
    generate_class_OesQryCounterCashRsp(parent);
    generate_class_OesQryStkHoldingFilter(parent);
    generate_class_OesStkHoldingItem(parent);
    generate_class_OesQryStkHoldingReq(parent);
    generate_class_OesQryStkHoldingRsp(parent);
    generate_class_OesOptHoldingItem(parent);
    generate_class_OesQryOptHoldingReq(parent);
    generate_class_OesQryHoldRsp(parent);
    generate_class_OesQryCustFilter(parent);
    generate_class_OesQryCustReq(parent);
    generate_class_OesQryCustRsp(parent);
    generate_class_OesQryInvAcctFilter(parent);
    generate_class_OesInvAcctItem(parent);
    generate_class_OesQryInvAcctReq(parent);
    generate_class_OesQryInvAcctRsp(parent);
    generate_class_OesInvAcctOverview(parent);
    generate_class_OesCashAcctOverview(parent);
    generate_class_OesCustOverview(parent);
    generate_class_OesClientOverview(parent);
    generate_class_OesQryCommissionRateFilter(parent);
    generate_class_OesCommissionRateItem(parent);
    generate_class_OesQryCommissionRateReq(parent);
    generate_class_OesQryCommissionRateRsp(parent);
    generate_class_OesQryFundTransferSerialFilter(parent);
    generate_class_OesQryFundTransferSerialReq(parent);
    generate_class_OesQryFundTransferSerialRsp(parent);
    generate_class_OesQryLotWinningFilter(parent);
    generate_class_OesQryLotWinningReq(parent);
    generate_class_OesQryLotWinningRsp(parent);
    generate_class_OesQryIssueFilter(parent);
    generate_class_OesQryIssueReq(parent);
    generate_class_OesQryIssueRsp(parent);
    generate_class_OesQryStockFilter(parent);
    generate_class_OesQryStockReq(parent);
    generate_class_OesQryStockRsp(parent);
    generate_class_OesQryEtfFilter(parent);
    generate_class_OesQryEtfReq(parent);
    generate_class_OesQryEtfRsp(parent);
    generate_class_OesQryEtfComponentFilter(parent);
    generate_class_OesEtfComponentItem(parent);
    generate_class_OesQryEtfComponentReq(parent);
    generate_class_OesQryEtfComponentRsp(parent);
    generate_class_OesQryOptionFilter(parent);
    generate_class_OesQryOptionReq(parent);
    generate_class_OesQryOptionRsp(parent);
    generate_class_OesQryTradingDayRsp(parent);
    generate_class_OesQryMarketStateFilter(parent);
    generate_class_OesQryMarketStateReq(parent);
    generate_class_OesQryMarketStateRsp(parent);
    generate_class_OesQryReqMsg(parent);
    generate_class_OesQryRspMsg(parent);
    generate_class_OesReportSynchronizationReq(parent);
    generate_class_OesReportSynchronizationRsp(parent);
    generate_class_OesTestRequestReq(parent);
    generate_class_OesTestRequestRsp(parent);
    generate_class_OesChangePasswordReq(parent);
    generate_class_OesChangePasswordRsp(parent);
    generate_class_OesBatchOrdersHead(parent);
    generate_class_OesBatchOrdersReq(parent);
    generate_class_OesRptMsgHead(parent);
    generate_class_OesRptMsgBody(parent);
    generate_class_OesRptMsg(parent);
    generate_class_OesReqMsgBody(parent);
    generate_class_OesRspMsgBody(parent);
    generate_class_SErrMsg(parent);
    generate_class_SDataBuffer(parent);
    generate_class_SDataBufferVar(parent);
    generate_class_SSocketUriInfo(parent);
    generate_class_SSocketIpPortInfo(parent);
    generate_class_SSocketChannelInfo(parent);
    generate_class_SSocketOptionConfig(parent);
    generate_class_SGeneralClientChannel(parent);
    generate_class_SGeneralClientChannelGroup(parent);
    generate_class_SGeneralClientAddrInfo(parent);
    generate_class_SGeneralClientRemoteCfg(parent);
    generate_class_OesApiSubscribeInfo(parent);
    generate_class_OesApiClientCfg(parent);
    generate_class_OesApiClientEnv(parent);
    generate_class_MdsTradingSessionStatusMsg(parent);
    generate_class_MdsSecurityStatusMsg(parent);
    generate_class_MdsPriceLevelEntry(parent);
    generate_class_MdsMktDataSnapshotHead(parent);
    generate_class_MdsIndexSnapshotBody(parent);
    generate_class_MdsStockSnapshotBody(parent);
    generate_class_MdsL1SnapshotBody(parent);
    generate_class_MdsL1Snapshot(parent);
    generate_class_MdsL2StockSnapshotBody(parent);
    generate_class_MdsL2StockSnapshotIncremental(parent);
    generate_class_MdsL2BestOrdersSnapshotBody(parent);
    generate_class_MdsL2BestOrdersSnapshotIncremental(parent);
    generate_class_MdsL2MarketOverview(parent);
    generate_class_MdsL2SnapshotBody(parent);
    generate_class_MdsMktDataSnapshot(parent);
    generate_class_MdsL2Trade(parent);
    generate_class_MdsL2Order(parent);
    generate_class_MdsWholeMktMsgBody(parent);
    generate_class_MdsStockStaticInfo(parent);
    generate_class_MdsQryMktDataSnapshotReq(parent);
    generate_class_MdsQryTrdSessionStatusReq(parent);
    generate_class_MdsQryReqHeadT(parent);
    generate_class_MdsQryRspHeadT(parent);
    generate_class_MdsQryCursor(parent);
    generate_class_MdsQrySecurityCodeEntry(parent);
    generate_class_MdsQryStockStaticInfoFilter(parent);
    generate_class_MdsQryStockStaticInfoReq(parent);
    generate_class_MdsQryStockStaticInfoRsp(parent);
    generate_class_MdsQrySnapshotListFilter(parent);
    generate_class_MdsQrySnapshotListReq(parent);
    generate_class_MdsQrySnapshotListRsp(parent);
    generate_class_MdsMktDataRequestEntry(parent);
    generate_class_MdsMktDataRequestReq(parent);
    generate_class_MdsMktDataRequestReqBuf(parent);
    generate_class_MdsMktDataRequestRsp(parent);
    generate_class_MdsTestRequestReq(parent);
    generate_class_MdsTestRequestRsp(parent);
    generate_class_MdsChangePasswordReq(parent);
    generate_class_MdsChangePasswordRsp(parent);
    generate_class_MdsMktReqMsgBody(parent);
    generate_class_MdsMktRspMsgBody(parent);
    generate_class_MdsUdpPktHead(parent);
    generate_class_MdsApiClientCfg(parent);
    generate_class_MdsApiClientEnv(parent);
}
void generate_enum_eOesExchangeId(pybind11::object & parent)
{
    // _eOesExchangeId
    pybind11::enum_<_eOesExchangeId> e(parent, "_eOesExchangeId", pybind11::arithmetic());
    // _eOesExchangeId::OES_EXCH_UNDEFINE
    e.value("OES_EXCH_UNDEFINE", _eOesExchangeId::OES_EXCH_UNDEFINE);
    // _eOesExchangeId::OES_EXCH_SSE
    e.value("OES_EXCH_SSE", _eOesExchangeId::OES_EXCH_SSE);
    // _eOesExchangeId::OES_EXCH_SZSE
    e.value("OES_EXCH_SZSE", _eOesExchangeId::OES_EXCH_SZSE);
    // _eOesExchangeId::__MAX_OES_EXCH
    e.value("__MAX_OES_EXCH", _eOesExchangeId::__MAX_OES_EXCH);
    // _eOesExchangeId::OES_EXCHANGE_TYPE_SSE
    e.value("OES_EXCHANGE_TYPE_SSE", _eOesExchangeId::OES_EXCHANGE_TYPE_SSE);
    // _eOesExchangeId::OES_EXCHANGE_TYPE_SZSE
    e.value("OES_EXCHANGE_TYPE_SZSE", _eOesExchangeId::OES_EXCHANGE_TYPE_SZSE);
    // _eOesExchangeId::__OES_EXCH_ID_MAX_ALIGNED4
    e.value("__OES_EXCH_ID_MAX_ALIGNED4", _eOesExchangeId::__OES_EXCH_ID_MAX_ALIGNED4);
    // _eOesExchangeId::__OES_EXCH_ID_MAX_ALIGNED8
    e.value("__OES_EXCH_ID_MAX_ALIGNED8", _eOesExchangeId::__OES_EXCH_ID_MAX_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eOesExchangeId", e);
}
void generate_enum_eOesMarketId(pybind11::object & parent)
{
    // _eOesMarketId
    pybind11::enum_<_eOesMarketId> e(parent, "_eOesMarketId", pybind11::arithmetic());
    // _eOesMarketId::OES_MKT_UNDEFINE
    e.value("OES_MKT_UNDEFINE", _eOesMarketId::OES_MKT_UNDEFINE);
    // _eOesMarketId::OES_MKT_SH_ASHARE
    e.value("OES_MKT_SH_ASHARE", _eOesMarketId::OES_MKT_SH_ASHARE);
    // _eOesMarketId::OES_MKT_SZ_ASHARE
    e.value("OES_MKT_SZ_ASHARE", _eOesMarketId::OES_MKT_SZ_ASHARE);
    // _eOesMarketId::OES_MKT_SH_OPTION
    e.value("OES_MKT_SH_OPTION", _eOesMarketId::OES_MKT_SH_OPTION);
    // _eOesMarketId::__OES_MKT_ID_MAX
    e.value("__OES_MKT_ID_MAX", _eOesMarketId::__OES_MKT_ID_MAX);
    // _eOesMarketId::OES_MKT_ID_UNDEFINE
    e.value("OES_MKT_ID_UNDEFINE", _eOesMarketId::OES_MKT_ID_UNDEFINE);
    // _eOesMarketId::OES_MKT_ID_SH_A
    e.value("OES_MKT_ID_SH_A", _eOesMarketId::OES_MKT_ID_SH_A);
    // _eOesMarketId::OES_MKT_ID_SZ_A
    e.value("OES_MKT_ID_SZ_A", _eOesMarketId::OES_MKT_ID_SZ_A);
    // _eOesMarketId::OES_MKT_ID_SH_OPT
    e.value("OES_MKT_ID_SH_OPT", _eOesMarketId::OES_MKT_ID_SH_OPT);
    // _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED4
    e.value("__OES_MKT_ID_MAX_ALIGNED4", _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED4);
    // _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED8
    e.value("__OES_MKT_ID_MAX_ALIGNED8", _eOesMarketId::__OES_MKT_ID_MAX_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMarketId", e);
}
void generate_enum_eOesPlatformId(pybind11::object & parent)
{
    // _eOesPlatformId
    pybind11::enum_<_eOesPlatformId> e(parent, "_eOesPlatformId", pybind11::arithmetic());
    // _eOesPlatformId::OES_PLATFORM_UNDEFINE
    e.value("OES_PLATFORM_UNDEFINE", _eOesPlatformId::OES_PLATFORM_UNDEFINE);
    // _eOesPlatformId::OES_PLATFORM_CASH_AUCTION
    e.value("OES_PLATFORM_CASH_AUCTION", _eOesPlatformId::OES_PLATFORM_CASH_AUCTION);
    // _eOesPlatformId::OES_PLATFORM_FINANCIAL_SERVICES
    e.value("OES_PLATFORM_FINANCIAL_SERVICES", _eOesPlatformId::OES_PLATFORM_FINANCIAL_SERVICES);
    // _eOesPlatformId::OES_PLATFORM_NON_TRADE
    e.value("OES_PLATFORM_NON_TRADE", _eOesPlatformId::OES_PLATFORM_NON_TRADE);
    // _eOesPlatformId::OES_PLATFORM_DERIVATIVE_AUCTION
    e.value("OES_PLATFORM_DERIVATIVE_AUCTION", _eOesPlatformId::OES_PLATFORM_DERIVATIVE_AUCTION);
    // _eOesPlatformId::__OES_PLATFORM_ID_MAX
    e.value("__OES_PLATFORM_ID_MAX", _eOesPlatformId::__OES_PLATFORM_ID_MAX);
    // _eOesPlatformId::__OES_PLATFORM_ID_MAX_ALIGNED8
    e.value("__OES_PLATFORM_ID_MAX_ALIGNED8", _eOesPlatformId::__OES_PLATFORM_ID_MAX_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eOesPlatformId", e);
}
void generate_enum_eOesMarketState(pybind11::object & parent)
{
    // _eOesMarketState
    pybind11::enum_<_eOesMarketState> e(parent, "_eOesMarketState", pybind11::arithmetic());
    // _eOesMarketState::OES_MKT_STATE_UNDEFINE
    e.value("OES_MKT_STATE_UNDEFINE", _eOesMarketState::OES_MKT_STATE_UNDEFINE);
    // _eOesMarketState::OES_MKT_STATE_PRE_OPEN
    e.value("OES_MKT_STATE_PRE_OPEN", _eOesMarketState::OES_MKT_STATE_PRE_OPEN);
    // _eOesMarketState::OES_MKT_STATE_OPEN_UP_COMING
    e.value("OES_MKT_STATE_OPEN_UP_COMING", _eOesMarketState::OES_MKT_STATE_OPEN_UP_COMING);
    // _eOesMarketState::OES_MKT_STATE_OPEN
    e.value("OES_MKT_STATE_OPEN", _eOesMarketState::OES_MKT_STATE_OPEN);
    // _eOesMarketState::OES_MKT_STATE_HALT
    e.value("OES_MKT_STATE_HALT", _eOesMarketState::OES_MKT_STATE_HALT);
    // _eOesMarketState::OES_MKT_STATE_CLOSE
    e.value("OES_MKT_STATE_CLOSE", _eOesMarketState::OES_MKT_STATE_CLOSE);
    // _eOesMarketState::__OES_MKT_STATE_MAX
    e.value("__OES_MKT_STATE_MAX", _eOesMarketState::__OES_MKT_STATE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMarketState", e);
}
void generate_enum_eOesTrdSessType(pybind11::object & parent)
{
    // _eOesTrdSessType
    pybind11::enum_<_eOesTrdSessType> e(parent, "_eOesTrdSessType", pybind11::arithmetic());
    // _eOesTrdSessType::OES_TRD_SESS_TYPE_O
    e.value("OES_TRD_SESS_TYPE_O", _eOesTrdSessType::OES_TRD_SESS_TYPE_O);
    // _eOesTrdSessType::OES_TRD_SESS_TYPE_T
    e.value("OES_TRD_SESS_TYPE_T", _eOesTrdSessType::OES_TRD_SESS_TYPE_T);
    // _eOesTrdSessType::OES_TRD_SESS_TYPE_C
    e.value("OES_TRD_SESS_TYPE_C", _eOesTrdSessType::OES_TRD_SESS_TYPE_C);
    // _eOesTrdSessType::__OES_TRD_SESS_TYPE_MAX
    e.value("__OES_TRD_SESS_TYPE_MAX", _eOesTrdSessType::__OES_TRD_SESS_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesTrdSessType", e);
}
void generate_enum_eOesProductType(pybind11::object & parent)
{
    // _eOesProductType
    pybind11::enum_<_eOesProductType> e(parent, "_eOesProductType", pybind11::arithmetic());
    // _eOesProductType::OES_PRODUCT_TYPE_UNDEFINE
    e.value("OES_PRODUCT_TYPE_UNDEFINE", _eOesProductType::OES_PRODUCT_TYPE_UNDEFINE);
    // _eOesProductType::OES_PRODUCT_TYPE_EQUITY
    e.value("OES_PRODUCT_TYPE_EQUITY", _eOesProductType::OES_PRODUCT_TYPE_EQUITY);
    // _eOesProductType::OES_PRODUCT_TYPE_BOND_STD
    e.value("OES_PRODUCT_TYPE_BOND_STD", _eOesProductType::OES_PRODUCT_TYPE_BOND_STD);
    // _eOesProductType::OES_PRODUCT_TYPE_IPO
    e.value("OES_PRODUCT_TYPE_IPO", _eOesProductType::OES_PRODUCT_TYPE_IPO);
    // _eOesProductType::OES_PRODUCT_TYPE_ALLOTMENT
    e.value("OES_PRODUCT_TYPE_ALLOTMENT", _eOesProductType::OES_PRODUCT_TYPE_ALLOTMENT);
    // _eOesProductType::OES_PRODUCT_TYPE_OPTION
    e.value("OES_PRODUCT_TYPE_OPTION", _eOesProductType::OES_PRODUCT_TYPE_OPTION);
    // _eOesProductType::__OES_PRODUCT_TYPE_MAX
    e.value("__OES_PRODUCT_TYPE_MAX", _eOesProductType::__OES_PRODUCT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesProductType", e);
}
void generate_enum_eOesSecurityType(pybind11::object & parent)
{
    // _eOesSecurityType
    pybind11::enum_<_eOesSecurityType> e(parent, "_eOesSecurityType", pybind11::arithmetic());
    // _eOesSecurityType::OES_SECURITY_TYPE_UNDEFINE
    e.value("OES_SECURITY_TYPE_UNDEFINE", _eOesSecurityType::OES_SECURITY_TYPE_UNDEFINE);
    // _eOesSecurityType::OES_SECURITY_TYPE_STOCK
    e.value("OES_SECURITY_TYPE_STOCK", _eOesSecurityType::OES_SECURITY_TYPE_STOCK);
    // _eOesSecurityType::OES_SECURITY_TYPE_BOND
    e.value("OES_SECURITY_TYPE_BOND", _eOesSecurityType::OES_SECURITY_TYPE_BOND);
    // _eOesSecurityType::OES_SECURITY_TYPE_ETF
    e.value("OES_SECURITY_TYPE_ETF", _eOesSecurityType::OES_SECURITY_TYPE_ETF);
    // _eOesSecurityType::OES_SECURITY_TYPE_FUND
    e.value("OES_SECURITY_TYPE_FUND", _eOesSecurityType::OES_SECURITY_TYPE_FUND);
    // _eOesSecurityType::OES_SECURITY_TYPE_OPTION
    e.value("OES_SECURITY_TYPE_OPTION", _eOesSecurityType::OES_SECURITY_TYPE_OPTION);
    // _eOesSecurityType::__OES_SECURITY_TYPE_MAX
    e.value("__OES_SECURITY_TYPE_MAX", _eOesSecurityType::__OES_SECURITY_TYPE_MAX);
    // _eOesSecurityType::__OES_SECURITY_TYPE_NOT_SUPPORT
    e.value("__OES_SECURITY_TYPE_NOT_SUPPORT", _eOesSecurityType::__OES_SECURITY_TYPE_NOT_SUPPORT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityType", e);
}
void generate_enum_eOesSubSecurityType(pybind11::object & parent)
{
    // _eOesSubSecurityType
    pybind11::enum_<_eOesSubSecurityType> e(parent, "_eOesSubSecurityType", pybind11::arithmetic());
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_UNDEFINE
    e.value("OES_SUB_SECURITY_TYPE_UNDEFINE", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_UNDEFINE);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MIN
    e.value("__OES_SUB_SECURITY_TYPE_STOCK_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MIN);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_ASH
    e.value("OES_SUB_SECURITY_TYPE_STOCK_ASH", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_ASH);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_SME
    e.value("OES_SUB_SECURITY_TYPE_STOCK_SME", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_SME);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_GEM
    e.value("OES_SUB_SECURITY_TYPE_STOCK_GEM", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_GEM);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_KSH
    e.value("OES_SUB_SECURITY_TYPE_STOCK_KSH", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_KSH);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_KCDR
    e.value("OES_SUB_SECURITY_TYPE_STOCK_KCDR", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_KCDR);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_CDR
    e.value("OES_SUB_SECURITY_TYPE_STOCK_CDR", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_CDR);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_HLTCDR
    e.value("OES_SUB_SECURITY_TYPE_STOCK_HLTCDR", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_STOCK_HLTCDR);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MAX
    e.value("__OES_SUB_SECURITY_TYPE_STOCK_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_STOCK_MAX);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MIN
    e.value("__OES_SUB_SECURITY_TYPE_BOND_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MIN);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_GBF
    e.value("OES_SUB_SECURITY_TYPE_BOND_GBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_GBF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CBF
    e.value("OES_SUB_SECURITY_TYPE_BOND_CBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CBF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CPF
    e.value("OES_SUB_SECURITY_TYPE_BOND_CPF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CPF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CCF
    e.value("OES_SUB_SECURITY_TYPE_BOND_CCF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_CCF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_FBF
    e.value("OES_SUB_SECURITY_TYPE_BOND_FBF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_FBF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_PRP
    e.value("OES_SUB_SECURITY_TYPE_BOND_PRP", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_PRP);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_STD
    e.value("OES_SUB_SECURITY_TYPE_BOND_STD", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_BOND_STD);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MAX
    e.value("__OES_SUB_SECURITY_TYPE_BOND_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_BOND_MAX);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MIN
    e.value("__OES_SUB_SECURITY_TYPE_ETF_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MIN);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT
    e.value("OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT
    e.value("OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_BOND
    e.value("OES_SUB_SECURITY_TYPE_ETF_BOND", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_BOND);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CURRENCY
    e.value("OES_SUB_SECURITY_TYPE_ETF_CURRENCY", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CURRENCY);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER
    e.value("OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_GOLD
    e.value("OES_SUB_SECURITY_TYPE_ETF_GOLD", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_ETF_GOLD);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MAX
    e.value("__OES_SUB_SECURITY_TYPE_ETF_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_ETF_MAX);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MIN
    e.value("__OES_SUB_SECURITY_TYPE_FUND_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MIN);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_LOF
    e.value("OES_SUB_SECURITY_TYPE_FUND_LOF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_LOF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_CEF
    e.value("OES_SUB_SECURITY_TYPE_FUND_CEF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_CEF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_OEF
    e.value("OES_SUB_SECURITY_TYPE_FUND_OEF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_OEF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_GRADED
    e.value("OES_SUB_SECURITY_TYPE_FUND_GRADED", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_FUND_GRADED);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MAX
    e.value("__OES_SUB_SECURITY_TYPE_FUND_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_FUND_MAX);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MIN
    e.value("__OES_SUB_SECURITY_TYPE_OPTION_MIN", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MIN);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_ETF
    e.value("OES_SUB_SECURITY_TYPE_OPTION_ETF", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_ETF);
    // _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_STOCK
    e.value("OES_SUB_SECURITY_TYPE_OPTION_STOCK", _eOesSubSecurityType::OES_SUB_SECURITY_TYPE_OPTION_STOCK);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MAX
    e.value("__OES_SUB_SECURITY_TYPE_OPTION_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_OPTION_MAX);
    // _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_MAX
    e.value("__OES_SUB_SECURITY_TYPE_MAX", _eOesSubSecurityType::__OES_SUB_SECURITY_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSubSecurityType", e);
}
void generate_enum_eOesSecurityLevel(pybind11::object & parent)
{
    // _eOesSecurityLevel
    pybind11::enum_<_eOesSecurityLevel> e(parent, "_eOesSecurityLevel", pybind11::arithmetic());
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_UNDEFINE
    e.value("OES_SECURITY_LEVEL_UNDEFINE", _eOesSecurityLevel::OES_SECURITY_LEVEL_UNDEFINE);
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_N
    e.value("OES_SECURITY_LEVEL_N", _eOesSecurityLevel::OES_SECURITY_LEVEL_N);
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_XST
    e.value("OES_SECURITY_LEVEL_XST", _eOesSecurityLevel::OES_SECURITY_LEVEL_XST);
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_ST
    e.value("OES_SECURITY_LEVEL_ST", _eOesSecurityLevel::OES_SECURITY_LEVEL_ST);
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_P
    e.value("OES_SECURITY_LEVEL_P", _eOesSecurityLevel::OES_SECURITY_LEVEL_P);
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_T
    e.value("OES_SECURITY_LEVEL_T", _eOesSecurityLevel::OES_SECURITY_LEVEL_T);
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_U
    e.value("OES_SECURITY_LEVEL_U", _eOesSecurityLevel::OES_SECURITY_LEVEL_U);
    // _eOesSecurityLevel::OES_SECURITY_LEVEL_B
    e.value("OES_SECURITY_LEVEL_B", _eOesSecurityLevel::OES_SECURITY_LEVEL_B);
    // _eOesSecurityLevel::__OES_SECURITY_LEVEL_MAX
    e.value("__OES_SECURITY_LEVEL_MAX", _eOesSecurityLevel::__OES_SECURITY_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityLevel", e);
}
void generate_enum_eOesSecurityRiskLevel(pybind11::object & parent)
{
    // _eOesSecurityRiskLevel
    pybind11::enum_<_eOesSecurityRiskLevel> e(parent, "_eOesSecurityRiskLevel", pybind11::arithmetic());
    // _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_LOW
    e.value("OES_RISK_LEVEL_VERY_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_LOW);
    // _eOesSecurityRiskLevel::OES_RISK_LEVEL_LOW
    e.value("OES_RISK_LEVEL_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_LOW);
    // _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_LOW
    e.value("OES_RISK_LEVEL_MEDIUM_LOW", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_LOW);
    // _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM
    e.value("OES_RISK_LEVEL_MEDIUM", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM);
    // _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_HIGH
    e.value("OES_RISK_LEVEL_MEDIUM_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_MEDIUM_HIGH);
    // _eOesSecurityRiskLevel::OES_RISK_LEVEL_HIGH
    e.value("OES_RISK_LEVEL_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_HIGH);
    // _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_HIGH
    e.value("OES_RISK_LEVEL_VERY_HIGH", _eOesSecurityRiskLevel::OES_RISK_LEVEL_VERY_HIGH);
    // _eOesSecurityRiskLevel::__OES_RISK_LEVEL_MAX
    e.value("__OES_RISK_LEVEL_MAX", _eOesSecurityRiskLevel::__OES_RISK_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecurityRiskLevel", e);
}
void generate_enum_eOesSecuritySuspFlag(pybind11::object & parent)
{
    // _eOesSecuritySuspFlag
    pybind11::enum_<_eOesSecuritySuspFlag> e(parent, "_eOesSecuritySuspFlag", pybind11::arithmetic());
    // _eOesSecuritySuspFlag::OES_SUSPFLAG_NONE
    e.value("OES_SUSPFLAG_NONE", _eOesSecuritySuspFlag::OES_SUSPFLAG_NONE);
    // _eOesSecuritySuspFlag::OES_SUSPFLAG_EXCHANGE
    e.value("OES_SUSPFLAG_EXCHANGE", _eOesSecuritySuspFlag::OES_SUSPFLAG_EXCHANGE);
    // _eOesSecuritySuspFlag::OES_SUSPFLAG_BROKER
    e.value("OES_SUSPFLAG_BROKER", _eOesSecuritySuspFlag::OES_SUSPFLAG_BROKER);
    // _eOesSecuritySuspFlag::__OES_SUSPFLAG_OTHER
    e.value("__OES_SUSPFLAG_OTHER", _eOesSecuritySuspFlag::__OES_SUSPFLAG_OTHER);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSecuritySuspFlag", e);
}
void generate_enum_eOesLotType(pybind11::object & parent)
{
    // _eOesLotType
    pybind11::enum_<_eOesLotType> e(parent, "_eOesLotType", pybind11::arithmetic());
    // _eOesLotType::OES_LOT_TYPE_UNDEFINE
    e.value("OES_LOT_TYPE_UNDEFINE", _eOesLotType::OES_LOT_TYPE_UNDEFINE);
    // _eOesLotType::OES_LOT_TYPE_FAILED
    e.value("OES_LOT_TYPE_FAILED", _eOesLotType::OES_LOT_TYPE_FAILED);
    // _eOesLotType::OES_LOT_TYPE_ASSIGNMENT
    e.value("OES_LOT_TYPE_ASSIGNMENT", _eOesLotType::OES_LOT_TYPE_ASSIGNMENT);
    // _eOesLotType::OES_LOT_TYPE_LOTTERY
    e.value("OES_LOT_TYPE_LOTTERY", _eOesLotType::OES_LOT_TYPE_LOTTERY);
    // _eOesLotType::__OES_LOT_TYPE_MAX
    e.value("__OES_LOT_TYPE_MAX", _eOesLotType::__OES_LOT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesLotType", e);
}
