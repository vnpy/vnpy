#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "class_generators.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"
#include "mds_api/parser/json_parser/mds_json_parser.h"
#include "custom/wrapper.hpp"


void init_dispatcher(pybind11::module &m)
{
    autocxxpy::dispatcher::instance().start();
}

void generate_classes(pybind11::module &m)
{
    generate_class_OesOrdReqT(m);
    generate_class_OesOrdCancelReqT(m);
    generate_class_OesOrdRejectT(m);
    generate_class_OesOrdCnfmT(m);
    generate_class_OesTrdBaseInfoT(m);
    generate_class_OesTrdCnfmT(m);
    generate_class_OesLotWinningBaseInfoT(m);
    generate_class_OesFundTrsfBaseInfoT(m);
    generate_class_OesFundTrsfReqT(m);
    generate_class_OesFundTrsfRejectT(m);
    generate_class_OesFundTrsfReportT(m);
    generate_class_OesIssueBaseInfoT(m);
    generate_class_OesPriceLimitT(m);
    generate_class_OesStockBaseInfoT(m);
    generate_class_OesEtfBaseInfoT(m);
    generate_class_OesEtfComponentBaseInfoT(m);
    generate_class_OesOptionBaseInfoT(m);
    generate_class_OesCashAssetBaseInfoT(m);
    generate_class_OesCustBaseInfoT(m);
    generate_class_OesInvAcctBaseInfoT(m);
    generate_class_OesStkHoldingBaseInfoT(m);
    generate_class_OesOptHoldingBaseInfoT(m);
    generate_class_OesMarketStateInfoT(m);
    generate_class_OesTradingPermissionEntryT(m);
    generate_class_OesInputSourceInfoT(m);
    generate_class_SMsgHeadT(m);
    generate_class_OesQryCursorT(m);
    generate_class_OesQryReqHeadT(m);
    generate_class_OesQryRspHeadT(m);
    generate_class_OesQryOrdFilterT(m);
    generate_class_OesQryOrdReqT(m);
    generate_class_OesQryOrdRspT(m);
    generate_class_OesQryTrdFilterT(m);
    generate_class_OesQryTrdReqT(m);
    generate_class_OesQryTrdRspT(m);
    generate_class_OesQryCashAssetFilterT(m);
    generate_class_OesCashAssetItemT(m);
    generate_class_OesQryCashAssetReqT(m);
    generate_class_OesQryCashAssetRspT(m);
    generate_class_OesCounterCashItemT(m);
    generate_class_OesQryCounterCashReqT(m);
    generate_class_OesQryCounterCashRspT(m);
    generate_class_OesQryStkHoldingFilterT(m);
    generate_class_OesStkHoldingItemT(m);
    generate_class_OesQryStkHoldingReqT(m);
    generate_class_OesQryStkHoldingRspT(m);
    generate_class_OesOptHoldingItemT(m);
    generate_class_OesQryOptHoldingReqT(m);
    generate_class_OesQryOptHoldingRspT(m);
    generate_class_OesQryCustFilterT(m);
    generate_class_OesQryCustReqT(m);
    generate_class_OesQryCustRspT(m);
    generate_class_OesQryInvAcctFilterT(m);
    generate_class_OesInvAcctItemT(m);
    generate_class_OesQryInvAcctReqT(m);
    generate_class_OesQryInvAcctRspT(m);
    generate_class_OesInvAcctOverviewT(m);
    generate_class_OesCashAcctOverviewT(m);
    generate_class_OesCustOverviewT(m);
    generate_class_OesClientOverviewT(m);
    generate_class_OesQryCommissionRateFilterT(m);
    generate_class_OesCommissionRateItemT(m);
    generate_class_OesQryCommissionRateReqT(m);
    generate_class_OesQryCommissionRateRspT(m);
    generate_class_OesQryFundTransferSerialFilterT(m);
    generate_class_OesQryFundTransferSerialReqT(m);
    generate_class_OesQryFundTransferSerialRspT(m);
    generate_class_OesQryLotWinningFilterT(m);
    generate_class_OesQryLotWinningReqT(m);
    generate_class_OesQryLotWinningRspT(m);
    generate_class_OesQryIssueFilterT(m);
    generate_class_OesQryIssueReqT(m);
    generate_class_OesQryIssueRspT(m);
    generate_class_OesQryStockFilterT(m);
    generate_class_OesQryStockReqT(m);
    generate_class_OesQryStockRspT(m);
    generate_class_OesQryEtfFilterT(m);
    generate_class_OesQryEtfReqT(m);
    generate_class_OesQryEtfRspT(m);
    generate_class_OesQryEtfComponentFilterT(m);
    generate_class_OesEtfComponentItemT(m);
    generate_class_OesQryEtfComponentReqT(m);
    generate_class_OesQryEtfComponentRspT(m);
    generate_class_OesQryOptionFilterT(m);
    generate_class_OesQryOptionReqT(m);
    generate_class_OesQryOptionRspT(m);
    generate_class_OesQryTradingDayRspT(m);
    generate_class_OesQryMarketStateFilterT(m);
    generate_class_OesQryMarketStateReqT(m);
    generate_class_OesQryMarketStateRspT(m);
    generate_class_OesQryReqMsgT(m);
    generate_class_OesQryRspMsgT(m);
    generate_class_OesLogonReqT(m);
    generate_class_OesLogonRspT(m);
    generate_class_OesReportSynchronizationReqT(m);
    generate_class_OesReportSynchronizationRspT(m);
    generate_class_OesTestRequestReqT(m);
    generate_class_OesTestRequestRspT(m);
    generate_class_OesChangePasswordReqT(m);
    generate_class_OesChangePasswordRspT(m);
    generate_class_OesBatchOrdersHeadT(m);
    generate_class_OesBatchOrdersReqT(m);
    generate_class_OesRptMsgHeadT(m);
    generate_class_OesRptMsgBodyT(m);
    generate_class_OesRptMsgT(m);
    generate_class_OesReqMsgBodyT(m);
    generate_class_OesRspMsgBodyT(m);
    generate_class_SErrMsgT(m);
    generate_class_SDataBufferT(m);
    generate_class__SDataBufferVar(m);
    generate_class_SSocketUriInfoT(m);
    generate_class_SSocketIpPortInfoT(m);
    generate_class_SSocketChannelInfoT(m);
    generate_class_SSocketOptionConfigT(m);
    generate_class_SGeneralClientChannelT(m);
    generate_class_SGeneralClientChannelGroupT(m);
    generate_class_SGeneralClientAddrInfoT(m);
    generate_class_SGeneralClientRemoteCfgT(m);
    generate_class_OesApiSubscribeInfoT(m);
    generate_class_OesApiClientCfgT(m);
    generate_class_OesApiClientEnvT(m);
    generate_class_MdsTradingSessionStatusMsgT(m);
    generate_class_MdsSecurityStatusMsgT(m);
    generate_class_MdsPriceLevelEntryT(m);
    generate_class_MdsMktDataSnapshotHeadT(m);
    generate_class_MdsIndexSnapshotBodyT(m);
    generate_class_MdsStockSnapshotBodyT(m);
    generate_class_MdsL1SnapshotBodyT(m);
    generate_class_MdsL2StockSnapshotBodyT(m);
    generate_class_MdsL2StockSnapshotIncrementalT(m);
    generate_class_MdsL2BestOrdersSnapshotBodyT(m);
    generate_class_MdsL2BestOrdersSnapshotIncrementalT(m);
    generate_class_MdsL2VirtualAuctionPriceT(m);
    generate_class_MdsL2MarketOverviewT(m);
    generate_class_MdsL2SnapshotBodyT(m);
    generate_class_MdsMktDataSnapshotT(m);
    generate_class_MdsL2TradeT(m);
    generate_class_MdsL2OrderT(m);
    generate_class_MdsL2TickLostT(m);
    generate_class_MdsQryMktDataSnapshotReqT(m);
    generate_class_MdsQryTrdSessionStatusReqT(m);
    generate_class_MdsLogonReqT(m);
    generate_class_MdsLogonRspT(m);
    generate_class_MdsMktDataRequestEntryT(m);
    generate_class_MdsMktDataRequestReqT(m);
    generate_class_MdsMktDataRequestReqBufT(m);
    generate_class_MdsMktDataRequestRspT(m);
    generate_class_MdsTestRequestReqT(m);
    generate_class_MdsTestRequestRspT(m);
    generate_class_MdsMktReqMsgBodyT(m);
    generate_class_MdsMktRspMsgBodyT(m);
    generate_class_MdsUdpPktHeadT(m);
    generate_class_MdsApiClientCfgT(m);
    generate_class_MdsApiClientEnvT(m);

}

void generate_functions(pybind11::module &m)
{
    m.def("SPlatform_GetErrno",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_GetErrno
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_GetNegErrno",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_GetNegErrno
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_SetErrno",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_SetErrno
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsErrEagain",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsErrEagain
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsErrEconnaborted",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsErrEconnaborted
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsErrEtimeout",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsErrEtimeout
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsErrEpipe",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsErrEpipe
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsErrEintr",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsErrEintr
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsErrEbadmsg",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsErrEbadmsg
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsNegEagain",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsNegEagain
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsNegEconnaborted",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsNegEconnaborted
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsNegEtimeout",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsNegEtimeout
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsNegEpipe",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsNegEpipe
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsNegEintr",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsNegEintr
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("SPlatform_IsNegEbadmsg",
        autocxxpy::calling_wrapper_v<
        &::__SPlatform_IsNegEbadmsg
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SendOrderReq",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SendOrderReq
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SendOrderCancelReq",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SendOrderCancelReq
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SendBatchOrdersReq2",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SendBatchOrdersReq2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SendFundTransferReq",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SendFundTransferReq
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SendChangePasswordReq",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SendChangePasswordReq
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_WaitReportMsg",
        autocxxpy::calling_wrapper_v<
        &::OesApi_WaitReportMsg
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetApiVersion",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetApiVersion
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetTradingDay",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetTradingDay
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetClientOverview",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetClientOverview
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QuerySingleOrder",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QuerySingleOrder
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QuerySingleCashAsset",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QuerySingleCashAsset
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QuerySingleStkHolding",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QuerySingleStkHolding
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QuerySingleOptHolding",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QuerySingleOptHolding
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryOrder",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryOrder
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryTrade",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryTrade
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryCashAsset",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryCashAsset
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryStkHolding",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryStkHolding
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryOptHolding",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryOptHolding
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryLotWinning",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryLotWinning
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryCustInfo",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryCustInfo
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryInvAcct",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryInvAcct
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryCommissionRate",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryCommissionRate
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryFundTransferSerial",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryFundTransferSerial
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryIssue",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryIssue
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryStock",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryStock
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryEtf",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryEtf
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryEtfComponent",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryEtfComponent
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryOption",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryOption
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryMarketState",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryMarketState
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_QueryCounterCash",
        autocxxpy::calling_wrapper_v<
        &::OesApi_QueryCounterCash
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_Logon",
        autocxxpy::calling_wrapper_v<
        &::OesApi_Logon
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_LogonReplicaSet",
        autocxxpy::calling_wrapper_v<
        &::OesApi_LogonReplicaSet
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_LogonPeerNodes",
        autocxxpy::calling_wrapper_v<
        &::OesApi_LogonPeerNodes
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SendReportSynchronization",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SendReportSynchronization
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SendHeartbeat",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SendHeartbeat
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_TestOrdChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_TestOrdChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_TestOrdChannel2",
        autocxxpy::calling_wrapper_v<
        &::OesApi_TestOrdChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_TestRptChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_TestRptChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_TestRptChannel2",
        autocxxpy::calling_wrapper_v<
        &::OesApi_TestRptChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_Logout",
        autocxxpy::calling_wrapper_v<
        &::OesApi_Logout
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_Destory",
        autocxxpy::calling_wrapper_v<
        &::OesApi_Destory
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitAll",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitAll
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitAllByConvention",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitAllByConvention
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_LogoutAll",
        autocxxpy::calling_wrapper_v<
        &::OesApi_LogoutAll
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_DestoryAll",
        autocxxpy::calling_wrapper_v<
        &::OesApi_DestoryAll
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitLogger",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitLogger
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_ResetThreadLoggerName",
        autocxxpy::calling_wrapper_v<
        &::OesApi_ResetThreadLoggerName
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitOrdChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitOrdChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitOrdChannel2",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitOrdChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitRptChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitRptChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitRptChannel2",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitRptChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitQryChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitQryChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitQryChannel2",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitQryChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_ParseAddrListString",
        autocxxpy::calling_wrapper_v<
        &::OesApi_ParseAddrListString
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_ParseConfigFromFile",
        autocxxpy::calling_wrapper_v<
        &::OesApi_ParseConfigFromFile
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_ParseAllConfig",
        autocxxpy::calling_wrapper_v<
        &::OesApi_ParseAllConfig
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_InitChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::OesApi_InitChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_DestoryChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::OesApi_DestoryChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_AddToChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::OesApi_AddToChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_DeleteFromChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::OesApi_DeleteFromChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetFromChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetFromChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetFromChannelGroupBySocket",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetFromChannelGroupBySocket
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_ForeachInChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::OesApi_ForeachInChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SetThreadUsername",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SetThreadUsername
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetThreadUsername",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetThreadUsername
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SetThreadPassword",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SetThreadPassword
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SetThreadEnvId",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SetThreadEnvId
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetThreadEnvId",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetThreadEnvId
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SetCustomizedIpAndMac",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SetCustomizedIpAndMac
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetCustomizedIp",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetCustomizedIp
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetCustomizedMac",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetCustomizedMac
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SetCustomizedDriverId",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SetCustomizedDriverId
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetCustomizedDriverId",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetCustomizedDriverId
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetClEnvId",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetClEnvId
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetLastRecvTime",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetLastRecvTime
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetLastSendTime",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetLastSendTime
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_HasMoreCachedData",
        autocxxpy::calling_wrapper_v<
        &::OesApi_HasMoreCachedData
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_IsValidOrdChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_IsValidOrdChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_IsValidRptChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_IsValidRptChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_IsValidQryChannel",
        autocxxpy::calling_wrapper_v<
        &::OesApi_IsValidQryChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_IsValidChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::OesApi_IsValidChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetLastError",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetLastError
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_SetLastError",
        autocxxpy::calling_wrapper_v<
        &::OesApi_SetLastError
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetErrorMsg",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetErrorMsg
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("OesApi_GetErrorMsg2",
        autocxxpy::calling_wrapper_v<
        &::OesApi_GetErrorMsg2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_Logon",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_Logon
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_LogonReplicaSet",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_LogonReplicaSet
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_LogonPeerNodes",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_LogonPeerNodes
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_SyncSubscribeOnLogon",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_SyncSubscribeOnLogon
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_SubscribeMarketData",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_SubscribeMarketData
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_SendHeartbeat",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_SendHeartbeat
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_SendTestRequest",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_SendTestRequest
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_Logout",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_Logout
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_Destory",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_Destory
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_WaitOnMsg",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_WaitOnMsg
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_WaitOnMsgCompressible",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_WaitOnMsgCompressible
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetApiVersion",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetApiVersion
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_QueryMktDataSnapshot",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_QueryMktDataSnapshot
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_QuerySecurityStatus",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_QuerySecurityStatus
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_QueryTrdSessionStatus",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_QueryTrdSessionStatus
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_ConnectToUdpMcast",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_ConnectToUdpMcast
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_WaitOnUdpMsg",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_WaitOnUdpMsg
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitAll",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitAll
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitAllByConvention",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitAllByConvention
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_LogoutAll",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_LogoutAll
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_DestoryAll",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_DestoryAll
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitLogger",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitLogger
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_ResetThreadLoggerName",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_ResetThreadLoggerName
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitTcpChannel",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitTcpChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitTcpChannel2",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitTcpChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitQryChannel",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitQryChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitQryChannel2",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitQryChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitUdpChannel",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitUdpChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitUdpChannel2",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitUdpChannel2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_ParseAddrListString",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_ParseAddrListString
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_ParseConfigFromFile",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_ParseConfigFromFile
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_ParseAllConfig",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_ParseAllConfig
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_InitChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_InitChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_DestoryChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_DestoryChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_AddToChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_AddToChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_DeleteFromChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_DeleteFromChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetFromChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetFromChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetFromChannelGroupBySocket",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetFromChannelGroupBySocket
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_ForeachInChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_ForeachInChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_SetThreadUsername",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_SetThreadUsername
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetThreadUsername",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetThreadUsername
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_SetThreadPassword",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_SetThreadPassword
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetLastRecvTime",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetLastRecvTime
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetLastSendTime",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetLastSendTime
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_HasMoreCachedData",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_HasMoreCachedData
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_IsValidTcpChannel",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_IsValidTcpChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_IsValidQryChannel",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_IsValidQryChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_IsValidUdpChannel",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_IsValidUdpChannel
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_IsValidChannelGroup",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_IsValidChannelGroup
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetLastError",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetLastError
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_SetLastError",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_SetLastError
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetErrorMsg",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetErrorMsg
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsApi_GetErrorMsg2",
        autocxxpy::calling_wrapper_v<
        &::MdsApi_GetErrorMsg2
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsHelper_SetTickTypeOnSubscribeByString",
        autocxxpy::calling_wrapper_v<
        &::MdsHelper_SetTickTypeOnSubscribeByString
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsHelper_ClearSubscribeRequestEntries",
        autocxxpy::calling_wrapper_v<
        &::MdsHelper_ClearSubscribeRequestEntries
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsHelper_SetSubscribeRequestMode",
        autocxxpy::calling_wrapper_v<
        &::MdsHelper_SetSubscribeRequestMode
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsHelper_SetSubscribeRequestTickType",
        autocxxpy::calling_wrapper_v<
        &::MdsHelper_SetSubscribeRequestTickType
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsHelper_SetSubscribeRequestDataTypes",
        autocxxpy::calling_wrapper_v<
        &::MdsHelper_SetSubscribeRequestDataTypes
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsHelper_SetSubscribeRequestSubFlag",
        autocxxpy::calling_wrapper_v<
        &::MdsHelper_SetSubscribeRequestSubFlag
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsHelper_AddSubscribeRequestEntry",
        autocxxpy::calling_wrapper_v<
        &::MdsHelper_AddSubscribeRequestEntry
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsJsonParser_EncodeReq",
        autocxxpy::calling_wrapper_v<
        &::MdsJsonParser_EncodeReq
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsJsonParser_DecodeReq",
        autocxxpy::calling_wrapper_v<
        &::MdsJsonParser_DecodeReq
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsJsonParser_EncodeRsp",
        autocxxpy::calling_wrapper_v<
        &::MdsJsonParser_EncodeRsp
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsJsonParser_EncodeRspSimplify",
        autocxxpy::calling_wrapper_v<
        &::MdsJsonParser_EncodeRspSimplify
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    m.def("MdsJsonParser_DecodeRsp",
        autocxxpy::calling_wrapper_v<
        &::MdsJsonParser_DecodeRsp
        >,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );

}

void generate_enums(pybind11::module &m)
{
    pybind11::enum_<eOesExchangeIdT>(m, "eOesExchangeIdT", pybind11::arithmetic())
        .value("OES_EXCH_UNDEFINE", eOesExchangeIdT::OES_EXCH_UNDEFINE)
        .value("OES_EXCH_SSE", eOesExchangeIdT::OES_EXCH_SSE)
        .value("OES_EXCH_SZSE", eOesExchangeIdT::OES_EXCH_SZSE)
        .value("__MAX_OES_EXCH", eOesExchangeIdT::__MAX_OES_EXCH)
        .value("OES_EXCHANGE_TYPE_SSE", eOesExchangeIdT::OES_EXCHANGE_TYPE_SSE)
        .value("OES_EXCHANGE_TYPE_SZSE", eOesExchangeIdT::OES_EXCHANGE_TYPE_SZSE)
        .export_values()
    ;
    pybind11::enum_<eOesMarketIdT>(m, "eOesMarketIdT", pybind11::arithmetic())
        .value("OES_MKT_UNDEFINE", eOesMarketIdT::OES_MKT_UNDEFINE)
        .value("OES_MKT_SH_ASHARE", eOesMarketIdT::OES_MKT_SH_ASHARE)
        .value("OES_MKT_SZ_ASHARE", eOesMarketIdT::OES_MKT_SZ_ASHARE)
        .value("OES_MKT_SH_OPTION", eOesMarketIdT::OES_MKT_SH_OPTION)
        .value("__OES_MKT_ID_MAX", eOesMarketIdT::__OES_MKT_ID_MAX)
        .value("OES_MKT_ID_UNDEFINE", eOesMarketIdT::OES_MKT_ID_UNDEFINE)
        .value("OES_MKT_ID_SH_A", eOesMarketIdT::OES_MKT_ID_SH_A)
        .value("OES_MKT_ID_SZ_A", eOesMarketIdT::OES_MKT_ID_SZ_A)
        .value("OES_MKT_ID_SH_OPT", eOesMarketIdT::OES_MKT_ID_SH_OPT)
        .value("__OES_MKT_ID_MAX_ALIGNED4", eOesMarketIdT::__OES_MKT_ID_MAX_ALIGNED4)
        .value("__OES_MKT_ID_MAX_ALIGNED8", eOesMarketIdT::__OES_MKT_ID_MAX_ALIGNED8)
        .export_values()
    ;
    pybind11::enum_<eOesPlatformIdT>(m, "eOesPlatformIdT", pybind11::arithmetic())
        .value("OES_PLATFORM_UNDEFINE", eOesPlatformIdT::OES_PLATFORM_UNDEFINE)
        .value("OES_PLATFORM_CASH_AUCTION", eOesPlatformIdT::OES_PLATFORM_CASH_AUCTION)
        .value("OES_PLATFORM_FINANCIAL_SERVICES", eOesPlatformIdT::OES_PLATFORM_FINANCIAL_SERVICES)
        .value("OES_PLATFORM_NON_TRADE", eOesPlatformIdT::OES_PLATFORM_NON_TRADE)
        .value("OES_PLATFORM_DERIVATIVE_AUCTION", eOesPlatformIdT::OES_PLATFORM_DERIVATIVE_AUCTION)
        .value("__OES_PLATFORM_ID_MAX", eOesPlatformIdT::__OES_PLATFORM_ID_MAX)
        .value("__OES_PLATFORM_ACTIVE_MAX", eOesPlatformIdT::__OES_PLATFORM_ACTIVE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesMarketStatusT>(m, "eOesMarketStatusT", pybind11::arithmetic())
        .value("OES_MKT_STATE_UNDEFINE", eOesMarketStatusT::OES_MKT_STATE_UNDEFINE)
        .value("OES_MKT_STATE_PRE_OPEN", eOesMarketStatusT::OES_MKT_STATE_PRE_OPEN)
        .value("OES_MKT_STATE_OPEN_UP_COMING", eOesMarketStatusT::OES_MKT_STATE_OPEN_UP_COMING)
        .value("OES_MKT_STATE_OPEN", eOesMarketStatusT::OES_MKT_STATE_OPEN)
        .value("OES_MKT_STATE_HALT", eOesMarketStatusT::OES_MKT_STATE_HALT)
        .value("OES_MKT_STATE_CLOSE", eOesMarketStatusT::OES_MKT_STATE_CLOSE)
        .value("__OES_MKT_STATE_MAX", eOesMarketStatusT::__OES_MKT_STATE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesTrdSessTypeT>(m, "eOesTrdSessTypeT", pybind11::arithmetic())
        .value("OES_TRD_SESS_TYPE_O", eOesTrdSessTypeT::OES_TRD_SESS_TYPE_O)
        .value("OES_TRD_SESS_TYPE_T", eOesTrdSessTypeT::OES_TRD_SESS_TYPE_T)
        .value("OES_TRD_SESS_TYPE_C", eOesTrdSessTypeT::OES_TRD_SESS_TYPE_C)
        .value("__OES_TRD_SESS_TYPE_MAX", eOesTrdSessTypeT::__OES_TRD_SESS_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesSecurityTypeT>(m, "eOesSecurityTypeT", pybind11::arithmetic())
        .value("OES_SECURITY_TYPE_UNDEFINE", eOesSecurityTypeT::OES_SECURITY_TYPE_UNDEFINE)
        .value("OES_SECURITY_TYPE_STOCK", eOesSecurityTypeT::OES_SECURITY_TYPE_STOCK)
        .value("OES_SECURITY_TYPE_BOND", eOesSecurityTypeT::OES_SECURITY_TYPE_BOND)
        .value("OES_SECURITY_TYPE_ETF", eOesSecurityTypeT::OES_SECURITY_TYPE_ETF)
        .value("OES_SECURITY_TYPE_FUND", eOesSecurityTypeT::OES_SECURITY_TYPE_FUND)
        .value("OES_SECURITY_TYPE_OPTION", eOesSecurityTypeT::OES_SECURITY_TYPE_OPTION)
        .value("__OES_SECURITY_TYPE_MAX", eOesSecurityTypeT::__OES_SECURITY_TYPE_MAX)
        .value("__OES_SECURITY_TYPE_NOT_SUPPORT", eOesSecurityTypeT::__OES_SECURITY_TYPE_NOT_SUPPORT)
        .export_values()
    ;
    pybind11::enum_<eOesSubSecurityTypeT>(m, "eOesSubSecurityTypeT", pybind11::arithmetic())
        .value("OES_SUB_SECURITY_TYPE_UNDEFINE", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_UNDEFINE)
        .value("__OES_SUB_SECURITY_TYPE_STOCK_MIN", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_STOCK_MIN)
        .value("OES_SUB_SECURITY_TYPE_STOCK_ASH", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_STOCK_ASH)
        .value("OES_SUB_SECURITY_TYPE_STOCK_SME", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_STOCK_SME)
        .value("OES_SUB_SECURITY_TYPE_STOCK_GEM", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_STOCK_GEM)
        .value("OES_SUB_SECURITY_TYPE_STOCK_CDR", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_STOCK_CDR)
        .value("__OES_SUB_SECURITY_TYPE_STOCK_MAX", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_STOCK_MAX)
        .value("__OES_SUB_SECURITY_TYPE_BOND_MIN", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_BOND_MIN)
        .value("OES_SUB_SECURITY_TYPE_BOND_GBF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_BOND_GBF)
        .value("OES_SUB_SECURITY_TYPE_BOND_CBF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_BOND_CBF)
        .value("OES_SUB_SECURITY_TYPE_BOND_CPF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_BOND_CPF)
        .value("OES_SUB_SECURITY_TYPE_BOND_CCF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_BOND_CCF)
        .value("OES_SUB_SECURITY_TYPE_BOND_FBF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_BOND_FBF)
        .value("OES_SUB_SECURITY_TYPE_BOND_PRP", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_BOND_PRP)
        .value("OES_SUB_SECURITY_TYPE_BOND_STD", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_BOND_STD)
        .value("__OES_SUB_SECURITY_TYPE_BOND_MAX", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_BOND_MAX)
        .value("__OES_SUB_SECURITY_TYPE_ETF_MIN", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_ETF_MIN)
        .value("OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT)
        .value("OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT)
        .value("OES_SUB_SECURITY_TYPE_ETF_BOND", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_ETF_BOND)
        .value("OES_SUB_SECURITY_TYPE_ETF_CURRENCY", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_ETF_CURRENCY)
        .value("OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER)
        .value("OES_SUB_SECURITY_TYPE_ETF_GOLD", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_ETF_GOLD)
        .value("__OES_SUB_SECURITY_TYPE_ETF_MAX", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_ETF_MAX)
        .value("__OES_SUB_SECURITY_TYPE_FUND_MIN", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_FUND_MIN)
        .value("OES_SUB_SECURITY_TYPE_FUND_LOF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_FUND_LOF)
        .value("OES_SUB_SECURITY_TYPE_FUND_CEF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_FUND_CEF)
        .value("OES_SUB_SECURITY_TYPE_FUND_OEF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_FUND_OEF)
        .value("OES_SUB_SECURITY_TYPE_FUND_GRADED", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_FUND_GRADED)
        .value("__OES_SUB_SECURITY_TYPE_FUND_MAX", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_FUND_MAX)
        .value("__OES_SUB_SECURITY_TYPE_OPTION_MIN", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_OPTION_MIN)
        .value("OES_SUB_SECURITY_TYPE_OPTION_STOCK", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_OPTION_STOCK)
        .value("OES_SUB_SECURITY_TYPE_OPTION_ETF", eOesSubSecurityTypeT::OES_SUB_SECURITY_TYPE_OPTION_ETF)
        .value("__OES_SUB_SECURITY_TYPE_OPTION_MAX", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_OPTION_MAX)
        .value("__OES_SUB_SECURITY_TYPE_MAX", eOesSubSecurityTypeT::__OES_SUB_SECURITY_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesSecurityLevelT>(m, "eOesSecurityLevelT", pybind11::arithmetic())
        .value("OES_SECURITY_LEVEL_UNDEFINE", eOesSecurityLevelT::OES_SECURITY_LEVEL_UNDEFINE)
        .value("OES_SECURITY_LEVEL_N", eOesSecurityLevelT::OES_SECURITY_LEVEL_N)
        .value("OES_SECURITY_LEVEL_XST", eOesSecurityLevelT::OES_SECURITY_LEVEL_XST)
        .value("OES_SECURITY_LEVEL_ST", eOesSecurityLevelT::OES_SECURITY_LEVEL_ST)
        .value("OES_SECURITY_LEVEL_P", eOesSecurityLevelT::OES_SECURITY_LEVEL_P)
        .value("OES_SECURITY_LEVEL_T", eOesSecurityLevelT::OES_SECURITY_LEVEL_T)
        .value("OES_SECURITY_LEVEL_U", eOesSecurityLevelT::OES_SECURITY_LEVEL_U)
        .value("OES_SECURITY_LEVEL_B", eOesSecurityLevelT::OES_SECURITY_LEVEL_B)
        .value("__OES_SECURITY_LEVEL_MAX", eOesSecurityLevelT::__OES_SECURITY_LEVEL_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesSecurityRiskLevelT>(m, "eOesSecurityRiskLevelT", pybind11::arithmetic())
        .value("OES_RISK_LEVEL_VERY_LOW", eOesSecurityRiskLevelT::OES_RISK_LEVEL_VERY_LOW)
        .value("OES_RISK_LEVEL_LOW", eOesSecurityRiskLevelT::OES_RISK_LEVEL_LOW)
        .value("OES_RISK_LEVEL_MEDIUM_LOW", eOesSecurityRiskLevelT::OES_RISK_LEVEL_MEDIUM_LOW)
        .value("OES_RISK_LEVEL_MEDIUM", eOesSecurityRiskLevelT::OES_RISK_LEVEL_MEDIUM)
        .value("OES_RISK_LEVEL_MEDIUM_HIGH", eOesSecurityRiskLevelT::OES_RISK_LEVEL_MEDIUM_HIGH)
        .value("OES_RISK_LEVEL_HIGH", eOesSecurityRiskLevelT::OES_RISK_LEVEL_HIGH)
        .value("OES_RISK_LEVEL_VERY_HIGH", eOesSecurityRiskLevelT::OES_RISK_LEVEL_VERY_HIGH)
        .value("__OES_RISK_LEVEL_MAX", eOesSecurityRiskLevelT::__OES_RISK_LEVEL_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesSecuritySuspFlagT>(m, "eOesSecuritySuspFlagT", pybind11::arithmetic())
        .value("OES_SUSPFLAG_NONE", eOesSecuritySuspFlagT::OES_SUSPFLAG_NONE)
        .value("OES_SUSPFLAG_EXCHANGE", eOesSecuritySuspFlagT::OES_SUSPFLAG_EXCHANGE)
        .value("OES_SUSPFLAG_BROKER", eOesSecuritySuspFlagT::OES_SUSPFLAG_BROKER)
        .value("__OES_SUSPFLAG_OTHER", eOesSecuritySuspFlagT::__OES_SUSPFLAG_OTHER)
        .export_values()
    ;
    pybind11::enum_<eOesOrdStatusT>(m, "eOesOrdStatusT", pybind11::arithmetic())
        .value("OES_ORD_STATUS_UNDEFINE", eOesOrdStatusT::OES_ORD_STATUS_UNDEFINE)
        .value("OES_ORD_STATUS_NEW", eOesOrdStatusT::OES_ORD_STATUS_NEW)
        .value("OES_ORD_STATUS_DECLARED", eOesOrdStatusT::OES_ORD_STATUS_DECLARED)
        .value("OES_ORD_STATUS_PARTIALLY_FILLED", eOesOrdStatusT::OES_ORD_STATUS_PARTIALLY_FILLED)
        .value("__OES_ORD_STATUS_FINAL_MIN", eOesOrdStatusT::__OES_ORD_STATUS_FINAL_MIN)
        .value("OES_ORD_STATUS_CANCEL_DONE", eOesOrdStatusT::OES_ORD_STATUS_CANCEL_DONE)
        .value("OES_ORD_STATUS_PARTIALLY_CANCELED", eOesOrdStatusT::OES_ORD_STATUS_PARTIALLY_CANCELED)
        .value("OES_ORD_STATUS_CANCELED", eOesOrdStatusT::OES_ORD_STATUS_CANCELED)
        .value("OES_ORD_STATUS_FILLED", eOesOrdStatusT::OES_ORD_STATUS_FILLED)
        .value("__OES_ORD_STATUS_VALID_MAX", eOesOrdStatusT::__OES_ORD_STATUS_VALID_MAX)
        .value("__OES_ORD_STATUS_INVALID_MIN", eOesOrdStatusT::__OES_ORD_STATUS_INVALID_MIN)
        .value("OES_ORD_STATUS_INVALID_OES", eOesOrdStatusT::OES_ORD_STATUS_INVALID_OES)
        .value("OES_ORD_STATUS_INVALID_SH_F", eOesOrdStatusT::OES_ORD_STATUS_INVALID_SH_F)
        .value("OES_ORD_STATUS_INVALID_SH_E", eOesOrdStatusT::OES_ORD_STATUS_INVALID_SH_E)
        .value("OES_ORD_STATUS_INVALID_SH_COMM", eOesOrdStatusT::OES_ORD_STATUS_INVALID_SH_COMM)
        .value("OES_ORD_STATUS_INVALID_SZ_F", eOesOrdStatusT::OES_ORD_STATUS_INVALID_SZ_F)
        .value("OES_ORD_STATUS_INVALID_SZ_E", eOesOrdStatusT::OES_ORD_STATUS_INVALID_SZ_E)
        .value("OES_ORD_STATUS_INVALID_SZ_REJECT", eOesOrdStatusT::OES_ORD_STATUS_INVALID_SZ_REJECT)
        .value("OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN", eOesOrdStatusT::OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN)
        .value("__OES_ORD_STATUS_INVALID_MAX", eOesOrdStatusT::__OES_ORD_STATUS_INVALID_MAX)
        .value("OES_ORD_STATUS_NORMAL", eOesOrdStatusT::OES_ORD_STATUS_NORMAL)
        .value("OES_ORD_STATUS_DECLARING", eOesOrdStatusT::OES_ORD_STATUS_DECLARING)
        .value("__OES_ORD_STATUS_INVALID_OES", eOesOrdStatusT::__OES_ORD_STATUS_INVALID_OES)
        .export_values()
    ;
    pybind11::enum_<eOesOrdTypeT>(m, "eOesOrdTypeT", pybind11::arithmetic())
        .value("OES_ORD_TYPE_LMT", eOesOrdTypeT::OES_ORD_TYPE_LMT)
        .value("OES_ORD_TYPE_LMT_FOK", eOesOrdTypeT::OES_ORD_TYPE_LMT_FOK)
        .value("__OES_ORD_TYPE_LMT_MAX", eOesOrdTypeT::__OES_ORD_TYPE_LMT_MAX)
        .value("OES_ORD_TYPE_MTL_BEST_5", eOesOrdTypeT::OES_ORD_TYPE_MTL_BEST_5)
        .value("OES_ORD_TYPE_MTL_BEST", eOesOrdTypeT::OES_ORD_TYPE_MTL_BEST)
        .value("OES_ORD_TYPE_MTL_SAMEPARTY_BEST", eOesOrdTypeT::OES_ORD_TYPE_MTL_SAMEPARTY_BEST)
        .value("__OES_ORD_TYPE_MTL_MAX", eOesOrdTypeT::__OES_ORD_TYPE_MTL_MAX)
        .value("OES_ORD_TYPE_FAK_BEST_5", eOesOrdTypeT::OES_ORD_TYPE_FAK_BEST_5)
        .value("OES_ORD_TYPE_FAK", eOesOrdTypeT::OES_ORD_TYPE_FAK)
        .value("__OES_ORD_TYPE_FAK_MAX", eOesOrdTypeT::__OES_ORD_TYPE_FAK_MAX)
        .value("OES_ORD_TYPE_FOK", eOesOrdTypeT::OES_ORD_TYPE_FOK)
        .value("__OES_ORD_TYPE_FOK_MAX", eOesOrdTypeT::__OES_ORD_TYPE_FOK_MAX)
        .value("__OES_ORD_TYPE_MAX", eOesOrdTypeT::__OES_ORD_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesOrdTypeShT>(m, "eOesOrdTypeShT", pybind11::arithmetic())
        .value("OES_ORD_TYPE_SH_LMT", eOesOrdTypeShT::OES_ORD_TYPE_SH_LMT)
        .value("OES_ORD_TYPE_SH_MTL_BEST_5", eOesOrdTypeShT::OES_ORD_TYPE_SH_MTL_BEST_5)
        .value("OES_ORD_TYPE_SH_FAK_BEST_5", eOesOrdTypeShT::OES_ORD_TYPE_SH_FAK_BEST_5)
        .value("OES_ORD_TYPE_SH_LMT_FOK", eOesOrdTypeShT::OES_ORD_TYPE_SH_LMT_FOK)
        .value("OES_ORD_TYPE_SH_FOK", eOesOrdTypeShT::OES_ORD_TYPE_SH_FOK)
        .export_values()
    ;
    pybind11::enum_<eOesOrdTypeSzT>(m, "eOesOrdTypeSzT", pybind11::arithmetic())
        .value("OES_ORD_TYPE_SZ_LMT", eOesOrdTypeSzT::OES_ORD_TYPE_SZ_LMT)
        .value("OES_ORD_TYPE_SZ_MTL_BEST", eOesOrdTypeSzT::OES_ORD_TYPE_SZ_MTL_BEST)
        .value("OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST", eOesOrdTypeSzT::OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST)
        .value("OES_ORD_TYPE_SZ_FAK_BEST_5", eOesOrdTypeSzT::OES_ORD_TYPE_SZ_FAK_BEST_5)
        .value("OES_ORD_TYPE_SZ_FAK", eOesOrdTypeSzT::OES_ORD_TYPE_SZ_FAK)
        .value("OES_ORD_TYPE_SZ_FOK", eOesOrdTypeSzT::OES_ORD_TYPE_SZ_FOK)
        .value("OES_ORD_TYPE_SZ_LMT_FOK", eOesOrdTypeSzT::OES_ORD_TYPE_SZ_LMT_FOK)
        .export_values()
    ;
    pybind11::enum_<eOesBuySellTypeT>(m, "eOesBuySellTypeT", pybind11::arithmetic())
        .value("OES_BS_TYPE_UNDEFINE", eOesBuySellTypeT::OES_BS_TYPE_UNDEFINE)
        .value("OES_BS_TYPE_BUY", eOesBuySellTypeT::OES_BS_TYPE_BUY)
        .value("OES_BS_TYPE_SELL", eOesBuySellTypeT::OES_BS_TYPE_SELL)
        .value("OES_BS_TYPE_CREATION", eOesBuySellTypeT::OES_BS_TYPE_CREATION)
        .value("OES_BS_TYPE_REDEMPTION", eOesBuySellTypeT::OES_BS_TYPE_REDEMPTION)
        .value("OES_BS_TYPE_CREDIT_BUY", eOesBuySellTypeT::OES_BS_TYPE_CREDIT_BUY)
        .value("OES_BS_TYPE_CREDIT_SELL", eOesBuySellTypeT::OES_BS_TYPE_CREDIT_SELL)
        .value("OES_BS_TYPE_SUBSCRIPTION", eOesBuySellTypeT::OES_BS_TYPE_SUBSCRIPTION)
        .value("OES_BS_TYPE_BUY_OPEN", eOesBuySellTypeT::OES_BS_TYPE_BUY_OPEN)
        .value("OES_BS_TYPE_BUY_CLOSE", eOesBuySellTypeT::OES_BS_TYPE_BUY_CLOSE)
        .value("OES_BS_TYPE_SELL_OPEN", eOesBuySellTypeT::OES_BS_TYPE_SELL_OPEN)
        .value("OES_BS_TYPE_SELL_CLOSE", eOesBuySellTypeT::OES_BS_TYPE_SELL_CLOSE)
        .value("OES_BS_TYPE_COVERED_OPEN", eOesBuySellTypeT::OES_BS_TYPE_COVERED_OPEN)
        .value("OES_BS_TYPE_COVERED_CLOSE", eOesBuySellTypeT::OES_BS_TYPE_COVERED_CLOSE)
        .value("OES_BS_TYPE_OPTION_EXERCISE", eOesBuySellTypeT::OES_BS_TYPE_OPTION_EXERCISE)
        .value("OES_BS_TYPE_UNDERLYING_FREEZE", eOesBuySellTypeT::OES_BS_TYPE_UNDERLYING_FREEZE)
        .value("OES_BS_TYPE_UNDERLYING_UNFREEZE", eOesBuySellTypeT::OES_BS_TYPE_UNDERLYING_UNFREEZE)
        .value("OES_BS_TYPE_CANCEL", eOesBuySellTypeT::OES_BS_TYPE_CANCEL)
        .value("__OES_BS_TYPE_MAX_TRADING", eOesBuySellTypeT::__OES_BS_TYPE_MAX_TRADING)
        .value("OES_BS_TYPE_SSE_DESIGNATION", eOesBuySellTypeT::OES_BS_TYPE_SSE_DESIGNATION)
        .value("OES_BS_TYPE_SSE_RECALL_DESIGNATION", eOesBuySellTypeT::OES_BS_TYPE_SSE_RECALL_DESIGNATION)
        .value("OES_BS_TYPE_SZSE_DESIGNATION", eOesBuySellTypeT::OES_BS_TYPE_SZSE_DESIGNATION)
        .value("OES_BS_TYPE_SZSE_CANCEL_DESIGNATION", eOesBuySellTypeT::OES_BS_TYPE_SZSE_CANCEL_DESIGNATION)
        .value("__OES_BS_TYPE_MAX", eOesBuySellTypeT::__OES_BS_TYPE_MAX)
        .value("OES_BS_TYPE_B", eOesBuySellTypeT::OES_BS_TYPE_B)
        .value("OES_BS_TYPE_S", eOesBuySellTypeT::OES_BS_TYPE_S)
        .value("OES_BS_TYPE_KB", eOesBuySellTypeT::OES_BS_TYPE_KB)
        .value("OES_BS_TYPE_KS", eOesBuySellTypeT::OES_BS_TYPE_KS)
        .value("OES_BS_TYPE_CB", eOesBuySellTypeT::OES_BS_TYPE_CB)
        .value("OES_BS_TYPE_CS", eOesBuySellTypeT::OES_BS_TYPE_CS)
        .value("OES_BS_TYPE_BO", eOesBuySellTypeT::OES_BS_TYPE_BO)
        .value("OES_BS_TYPE_BC", eOesBuySellTypeT::OES_BS_TYPE_BC)
        .value("OES_BS_TYPE_SO", eOesBuySellTypeT::OES_BS_TYPE_SO)
        .value("OES_BS_TYPE_SC", eOesBuySellTypeT::OES_BS_TYPE_SC)
        .value("OES_BS_TYPE_CO", eOesBuySellTypeT::OES_BS_TYPE_CO)
        .value("OES_BS_TYPE_CC", eOesBuySellTypeT::OES_BS_TYPE_CC)
        .value("OES_BS_TYPE_TE", eOesBuySellTypeT::OES_BS_TYPE_TE)
        .value("OES_BS_TYPE_UF", eOesBuySellTypeT::OES_BS_TYPE_UF)
        .value("OES_BS_TYPE_UU", eOesBuySellTypeT::OES_BS_TYPE_UU)
        .export_values()
    ;
    pybind11::enum_<eOesOrdDirT>(m, "eOesOrdDirT", pybind11::arithmetic())
        .value("OES_ORD_DIR_BUY", eOesOrdDirT::OES_ORD_DIR_BUY)
        .value("OES_ORD_DIR_SELL", eOesOrdDirT::OES_ORD_DIR_SELL)
        .value("__OES_ORD_DIR_MAX", eOesOrdDirT::__OES_ORD_DIR_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesEtfTrdCnfmTypeT>(m, "eOesEtfTrdCnfmTypeT", pybind11::arithmetic())
        .value("OES_ETF_TRDCNFM_TYPE_NONE", eOesEtfTrdCnfmTypeT::OES_ETF_TRDCNFM_TYPE_NONE)
        .value("OES_ETF_TRDCNFM_TYPE_ETF_FIRST", eOesEtfTrdCnfmTypeT::OES_ETF_TRDCNFM_TYPE_ETF_FIRST)
        .value("OES_ETF_TRDCNFM_TYPE_CMPOENT", eOesEtfTrdCnfmTypeT::OES_ETF_TRDCNFM_TYPE_CMPOENT)
        .value("OES_ETF_TRDCNFM_TYPE_CASH", eOesEtfTrdCnfmTypeT::OES_ETF_TRDCNFM_TYPE_CASH)
        .value("OES_ETF_TRDCNFM_TYPE_ETF_LAST", eOesEtfTrdCnfmTypeT::OES_ETF_TRDCNFM_TYPE_ETF_LAST)
        .value("__OES_ETF_TRDCNFM_TYPE_MAX", eOesEtfTrdCnfmTypeT::__OES_ETF_TRDCNFM_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesEtfSubFlagT>(m, "eOesEtfSubFlagT", pybind11::arithmetic())
        .value("OES_ETF_SUBFLAG_FORBID_SUB", eOesEtfSubFlagT::OES_ETF_SUBFLAG_FORBID_SUB)
        .value("OES_ETF_SUBFLAG_ALLOW_SUB", eOesEtfSubFlagT::OES_ETF_SUBFLAG_ALLOW_SUB)
        .value("OES_ETF_SUBFLAG_MUST_SUB", eOesEtfSubFlagT::OES_ETF_SUBFLAG_MUST_SUB)
        .value("OES_ETF_SUBFLAG_SZ_REFUND_SUB", eOesEtfSubFlagT::OES_ETF_SUBFLAG_SZ_REFUND_SUB)
        .value("OES_ETF_SUBFLAG_SZ_MUST_SUB", eOesEtfSubFlagT::OES_ETF_SUBFLAG_SZ_MUST_SUB)
        .value("OES_ETF_SUBFLAG_OTHER_REFUND_SUB", eOesEtfSubFlagT::OES_ETF_SUBFLAG_OTHER_REFUND_SUB)
        .value("OES_ETF_SUBFLAG_OTHER_MUST_SUB", eOesEtfSubFlagT::OES_ETF_SUBFLAG_OTHER_MUST_SUB)
        .export_values()
    ;
    pybind11::enum_<eOesLotTypeT>(m, "eOesLotTypeT", pybind11::arithmetic())
        .value("OES_LOT_TYPE_UNDEFINE", eOesLotTypeT::OES_LOT_TYPE_UNDEFINE)
        .value("OES_LOT_TYPE_FAILED", eOesLotTypeT::OES_LOT_TYPE_FAILED)
        .value("OES_LOT_TYPE_ASSIGNMENT", eOesLotTypeT::OES_LOT_TYPE_ASSIGNMENT)
        .value("OES_LOT_TYPE_LOTTERY", eOesLotTypeT::OES_LOT_TYPE_LOTTERY)
        .value("__OES_LOT_TYPE_MAX", eOesLotTypeT::__OES_LOT_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesLotRejReasonT>(m, "eOesLotRejReasonT", pybind11::arithmetic())
        .value("OES_LOT_REJ_REASON_DUPLICATE", eOesLotRejReasonT::OES_LOT_REJ_REASON_DUPLICATE)
        .value("OES_LOT_REJ_REASON_INVALID_DUPLICATE", eOesLotRejReasonT::OES_LOT_REJ_REASON_INVALID_DUPLICATE)
        .value("OES_LOT_REJ_REASON_OFFLINE_FIRST", eOesLotRejReasonT::OES_LOT_REJ_REASON_OFFLINE_FIRST)
        .value("OES_LOT_REJ_REASON_BAD_RECORD", eOesLotRejReasonT::OES_LOT_REJ_REASON_BAD_RECORD)
        .value("OES_LOT_REJ_REASON_UNKNOW", eOesLotRejReasonT::OES_LOT_REJ_REASON_UNKNOW)
        .export_values()
    ;
    pybind11::enum_<eOesExecTypeT>(m, "eOesExecTypeT", pybind11::arithmetic())
        .value("OES_EXECTYPE_UNDEFINE", eOesExecTypeT::OES_EXECTYPE_UNDEFINE)
        .value("OES_EXECTYPE_INSERT", eOesExecTypeT::OES_EXECTYPE_INSERT)
        .value("OES_EXECTYPE_CONFIRMED", eOesExecTypeT::OES_EXECTYPE_CONFIRMED)
        .value("OES_EXECTYPE_CANCELLED", eOesExecTypeT::OES_EXECTYPE_CANCELLED)
        .value("OES_EXECTYPE_AUTO_CANCELLED", eOesExecTypeT::OES_EXECTYPE_AUTO_CANCELLED)
        .value("OES_EXECTYPE_REJECT", eOesExecTypeT::OES_EXECTYPE_REJECT)
        .value("OES_EXECTYPE_TRADE", eOesExecTypeT::OES_EXECTYPE_TRADE)
        .value("__OES_EXECTYPE_MAX", eOesExecTypeT::__OES_EXECTYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesCurrTypeT>(m, "eOesCurrTypeT", pybind11::arithmetic())
        .value("OES_CURR_TYPE_RMB", eOesCurrTypeT::OES_CURR_TYPE_RMB)
        .value("OES_CURR_TYPE_HKD", eOesCurrTypeT::OES_CURR_TYPE_HKD)
        .value("OES_CURR_TYPE_USD", eOesCurrTypeT::OES_CURR_TYPE_USD)
        .value("__OES_CURR_TYPE_MAX", eOesCurrTypeT::__OES_CURR_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesFeeTypeT>(m, "eOesFeeTypeT", pybind11::arithmetic())
        .value("OES_FEE_TYPE_EXCHANGE_STAMP", eOesFeeTypeT::OES_FEE_TYPE_EXCHANGE_STAMP)
        .value("OES_FEE_TYPE_EXCHANGE_TRANSFER", eOesFeeTypeT::OES_FEE_TYPE_EXCHANGE_TRANSFER)
        .value("OES_FEE_TYPE_EXCHANGE_SETTLEMENT", eOesFeeTypeT::OES_FEE_TYPE_EXCHANGE_SETTLEMENT)
        .value("OES_FEE_TYPE_EXCHANGE_TRADE_RULE", eOesFeeTypeT::OES_FEE_TYPE_EXCHANGE_TRADE_RULE)
        .value("OES_FEE_TYPE_EXCHANGE_EXCHANGE", eOesFeeTypeT::OES_FEE_TYPE_EXCHANGE_EXCHANGE)
        .value("OES_FEE_TYPE_EXCHANGE_ADMINFER", eOesFeeTypeT::OES_FEE_TYPE_EXCHANGE_ADMINFER)
        .value("OES_FEE_TYPE_EXCHANGE_OTHER", eOesFeeTypeT::OES_FEE_TYPE_EXCHANGE_OTHER)
        .value("__OES_FEE_TYPE_EXCHANGE_MAX", eOesFeeTypeT::__OES_FEE_TYPE_EXCHANGE_MAX)
        .value("OES_FEE_TYPE_BROKER_BACK_END", eOesFeeTypeT::OES_FEE_TYPE_BROKER_BACK_END)
        .export_values()
    ;
    pybind11::enum_<eOesCalcFeeModeT>(m, "eOesCalcFeeModeT", pybind11::arithmetic())
        .value("OES_CALC_FEE_MODE_AMOUNT", eOesCalcFeeModeT::OES_CALC_FEE_MODE_AMOUNT)
        .value("OES_CALC_FEE_MODE_QTY", eOesCalcFeeModeT::OES_CALC_FEE_MODE_QTY)
        .value("OES_CALC_FEE_MODE_ORD", eOesCalcFeeModeT::OES_CALC_FEE_MODE_ORD)
        .export_values()
    ;
    pybind11::enum_<eOesFundTrsfDirectT>(m, "eOesFundTrsfDirectT", pybind11::arithmetic())
        .value("OES_FUND_TRSF_DIRECT_IN", eOesFundTrsfDirectT::OES_FUND_TRSF_DIRECT_IN)
        .value("OES_FUND_TRSF_DIRECT_OUT", eOesFundTrsfDirectT::OES_FUND_TRSF_DIRECT_OUT)
        .export_values()
    ;
    pybind11::enum_<eOesFundTrsfTypeT>(m, "eOesFundTrsfTypeT", pybind11::arithmetic())
        .value("OES_FUND_TRSF_TYPE_OES_BANK", eOesFundTrsfTypeT::OES_FUND_TRSF_TYPE_OES_BANK)
        .value("OES_FUND_TRSF_TYPE_OES_COUNTER", eOesFundTrsfTypeT::OES_FUND_TRSF_TYPE_OES_COUNTER)
        .value("OES_FUND_TRSF_TYPE_COUNTER_BANK", eOesFundTrsfTypeT::OES_FUND_TRSF_TYPE_COUNTER_BANK)
        .value("__OES_FUND_TRSF_TYPE_MAX", eOesFundTrsfTypeT::__OES_FUND_TRSF_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesFundTrsfStatusT>(m, "eOesFundTrsfStatusT", pybind11::arithmetic())
        .value("OES_FUND_TRSF_STS_UNDECLARED", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_UNDECLARED)
        .value("OES_FUND_TRSF_STS_DECLARED", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_DECLARED)
        .value("OES_FUND_TRSF_STS_WAIT_DONE", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_WAIT_DONE)
        .value("OES_FUND_TRSF_STS_DONE", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_DONE)
        .value("__OES_FUND_TRSF_STS_ROLLBACK_MIN", eOesFundTrsfStatusT::__OES_FUND_TRSF_STS_ROLLBACK_MIN)
        .value("OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK)
        .value("OES_FUND_TRSF_STS_DECLARED_ROLLBACK", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_DECLARED_ROLLBACK)
        .value("__OES_FUND_TRSF_STS_INVALID_MIN", eOesFundTrsfStatusT::__OES_FUND_TRSF_STS_INVALID_MIN)
        .value("OES_FUND_TRSF_STS_INVALID_OES", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_INVALID_OES)
        .value("OES_FUND_TRSF_STS_INVALID_COUNTER", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_INVALID_COUNTER)
        .value("OES_FUND_TRSF_STS_SUSPENDED", eOesFundTrsfStatusT::OES_FUND_TRSF_STS_SUSPENDED)
        .export_values()
    ;
    pybind11::enum_<eOesAcctTypeT>(m, "eOesAcctTypeT", pybind11::arithmetic())
        .value("OES_ACCT_TYPE_NORMAL", eOesAcctTypeT::OES_ACCT_TYPE_NORMAL)
        .value("OES_ACCT_TYPE_CREDIT", eOesAcctTypeT::OES_ACCT_TYPE_CREDIT)
        .value("OES_ACCT_TYPE_OPTION", eOesAcctTypeT::OES_ACCT_TYPE_OPTION)
        .value("__OES_ACCT_TYPE_MAX", eOesAcctTypeT::__OES_ACCT_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesCashTypeT>(m, "eOesCashTypeT", pybind11::arithmetic())
        .value("OES_CASH_TYPE_SPOT", eOesCashTypeT::OES_CASH_TYPE_SPOT)
        .value("OES_CASH_TYPE_CREDIT", eOesCashTypeT::OES_CASH_TYPE_CREDIT)
        .value("OES_CASH_TYPE_OPTION", eOesCashTypeT::OES_CASH_TYPE_OPTION)
        .value("__OES_CASH_TYPE_MAX", eOesCashTypeT::__OES_CASH_TYPE_MAX)
        .value("OES_CASH_TYPE_CRE", eOesCashTypeT::OES_CASH_TYPE_CRE)
        .value("OES_CASH_TYPE_OPT", eOesCashTypeT::OES_CASH_TYPE_OPT)
        .export_values()
    ;
    pybind11::enum_<eOesAcctStatusT>(m, "eOesAcctStatusT", pybind11::arithmetic())
        .value("OES_ACCT_STATUS_NORMAL", eOesAcctStatusT::OES_ACCT_STATUS_NORMAL)
        .value("OES_ACCT_STATUS_DISABLED", eOesAcctStatusT::OES_ACCT_STATUS_DISABLED)
        .value("OES_ACCT_STATUS_LOCKED", eOesAcctStatusT::OES_ACCT_STATUS_LOCKED)
        .export_values()
    ;
    pybind11::enum_<eOesTradingPermissionT>(m, "eOesTradingPermissionT", pybind11::arithmetic())
        .value("OES_PERMIS_MARKET_ORDER", eOesTradingPermissionT::OES_PERMIS_MARKET_ORDER)
        .value("OES_PERMIS_STRUCTURED_FUND", eOesTradingPermissionT::OES_PERMIS_STRUCTURED_FUND)
        .value("OES_PERMIS_BOND_QUALIFIED_INVESTOR", eOesTradingPermissionT::OES_PERMIS_BOND_QUALIFIED_INVESTOR)
        .value("OES_PERMIS_XXX4", eOesTradingPermissionT::OES_PERMIS_XXX4)
        .value("OES_PERMIS_DELISTING", eOesTradingPermissionT::OES_PERMIS_DELISTING)
        .value("OES_PERMIS_RISK_WARNING", eOesTradingPermissionT::OES_PERMIS_RISK_WARNING)
        .value("OES_PERMIS_SINGLE_MARKET_ETF", eOesTradingPermissionT::OES_PERMIS_SINGLE_MARKET_ETF)
        .value("OES_PERMIS_CROSS_BORDER_ETF", eOesTradingPermissionT::OES_PERMIS_CROSS_BORDER_ETF)
        .value("OES_PERMIS_CROSS_MARKET_ETF", eOesTradingPermissionT::OES_PERMIS_CROSS_MARKET_ETF)
        .value("OES_PERMIS_CURRENCY_ETF", eOesTradingPermissionT::OES_PERMIS_CURRENCY_ETF)
        .value("OES_PERMIS_STOCK_PLEDGE_REPURCHASE", eOesTradingPermissionT::OES_PERMIS_STOCK_PLEDGE_REPURCHASE)
        .value("OES_PERMIS_PLEDGE_REPURCHASE", eOesTradingPermissionT::OES_PERMIS_PLEDGE_REPURCHASE)
        .value("OES_PERMIS_GEM", eOesTradingPermissionT::OES_PERMIS_GEM)
        .value("OES_PERMIS_SH_HK_STOCK_CONNECT", eOesTradingPermissionT::OES_PERMIS_SH_HK_STOCK_CONNECT)
        .value("OES_PERMIS_SZ_HK_STOCK_CONNECT", eOesTradingPermissionT::OES_PERMIS_SZ_HK_STOCK_CONNECT)
        .value("OES_PERMIS_CDR", eOesTradingPermissionT::OES_PERMIS_CDR)
        .value("OES_PERMIS_INNOVATION", eOesTradingPermissionT::OES_PERMIS_INNOVATION)
        .value("__OES_PERMIS_ALL", eOesTradingPermissionT::__OES_PERMIS_ALL)
        .export_values()
    ;
    pybind11::enum_<eOesTradingLimitT>(m, "eOesTradingLimitT", pybind11::arithmetic())
        .value("OES_LIMIT_BUY", eOesTradingLimitT::OES_LIMIT_BUY)
        .value("OES_LIMIT_SELL", eOesTradingLimitT::OES_LIMIT_SELL)
        .value("OES_LIMIT_RECALL_DESIGNATION", eOesTradingLimitT::OES_LIMIT_RECALL_DESIGNATION)
        .value("OES_LIMIT_DESIGNATION", eOesTradingLimitT::OES_LIMIT_DESIGNATION)
        .value("OES_LIMIT_REPO", eOesTradingLimitT::OES_LIMIT_REPO)
        .value("OES_LIMIT_REVERSE_REPO", eOesTradingLimitT::OES_LIMIT_REVERSE_REPO)
        .value("OES_LIMIT_SUBSCRIPTION", eOesTradingLimitT::OES_LIMIT_SUBSCRIPTION)
        .value("OES_LIMIT_CREDIT_BUY", eOesTradingLimitT::OES_LIMIT_CREDIT_BUY)
        .value("OES_LIMIT_CREDIT_SELL", eOesTradingLimitT::OES_LIMIT_CREDIT_SELL)
        .value("__OES_LIMIT_ALL", eOesTradingLimitT::__OES_LIMIT_ALL)
        .export_values()
    ;
    pybind11::enum_<eOesQualificationClassT>(m, "eOesQualificationClassT", pybind11::arithmetic())
        .value("OES_QUALIFICATION_PUBLIC_INVESTOR", eOesQualificationClassT::OES_QUALIFICATION_PUBLIC_INVESTOR)
        .value("OES_QUALIFICATION_QUALIFIED_INVESTOR", eOesQualificationClassT::OES_QUALIFICATION_QUALIFIED_INVESTOR)
        .value("OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL", eOesQualificationClassT::OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL)
        .export_values()
    ;
    pybind11::enum_<eOesInvestorClassT>(m, "eOesInvestorClassT", pybind11::arithmetic())
        .value("OES_INVESTOR_CLASS_NORMAL", eOesInvestorClassT::OES_INVESTOR_CLASS_NORMAL)
        .value("OES_INVESTOR_CLASS_PROFESSIONAL_A", eOesInvestorClassT::OES_INVESTOR_CLASS_PROFESSIONAL_A)
        .value("OES_INVESTOR_CLASS_PROFESSIONAL_B", eOesInvestorClassT::OES_INVESTOR_CLASS_PROFESSIONAL_B)
        .value("OES_INVESTOR_CLASS_PROFESSIONAL_C", eOesInvestorClassT::OES_INVESTOR_CLASS_PROFESSIONAL_C)
        .export_values()
    ;
    pybind11::enum_<eOesOwnerTypeT>(m, "eOesOwnerTypeT", pybind11::arithmetic())
        .value("OES_OWNER_TYPE_PERSONAL", eOesOwnerTypeT::OES_OWNER_TYPE_PERSONAL)
        .value("OES_OWNER_TYPE_EXCHANGE", eOesOwnerTypeT::OES_OWNER_TYPE_EXCHANGE)
        .value("OES_OWNER_TYPE_MEMBER", eOesOwnerTypeT::OES_OWNER_TYPE_MEMBER)
        .value("OES_OWNER_TYPE_INSTITUTION", eOesOwnerTypeT::OES_OWNER_TYPE_INSTITUTION)
        .value("OES_OWNER_TYPE_PROPRIETARY", eOesOwnerTypeT::OES_OWNER_TYPE_PROPRIETARY)
        .value("OES_OWNER_TYPE_MKT_MAKER", eOesOwnerTypeT::OES_OWNER_TYPE_MKT_MAKER)
        .value("OES_OWNER_TYPE_SETTLEMENT", eOesOwnerTypeT::OES_OWNER_TYPE_SETTLEMENT)
        .value("__OES_OWNER_TYPE_MAX", eOesOwnerTypeT::__OES_OWNER_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesClientTypeT>(m, "eOesClientTypeT", pybind11::arithmetic())
        .value("OES_CLIENT_TYPE_UNDEFINED", eOesClientTypeT::OES_CLIENT_TYPE_UNDEFINED)
        .value("OES_CLIENT_TYPE_INVESTOR", eOesClientTypeT::OES_CLIENT_TYPE_INVESTOR)
        .value("OES_CLIENT_TYPE_VIRTUAL", eOesClientTypeT::OES_CLIENT_TYPE_VIRTUAL)
        .export_values()
    ;
    pybind11::enum_<eOesClientStatusT>(m, "eOesClientStatusT", pybind11::arithmetic())
        .value("OES_CLIENT_STATUS_UNACTIVATED", eOesClientStatusT::OES_CLIENT_STATUS_UNACTIVATED)
        .value("OES_CLIENT_STATUS_ACTIVATED", eOesClientStatusT::OES_CLIENT_STATUS_ACTIVATED)
        .value("OES_CLIENT_STATUS_PAUSE", eOesClientStatusT::OES_CLIENT_STATUS_PAUSE)
        .value("OES_CLIENT_STATUS_SUSPENDED", eOesClientStatusT::OES_CLIENT_STATUS_SUSPENDED)
        .value("OES_CLIENT_STATUS_CANCELLED", eOesClientStatusT::OES_CLIENT_STATUS_CANCELLED)
        .export_values()
    ;
    pybind11::enum_<eOesOptContractTypeT>(m, "eOesOptContractTypeT", pybind11::arithmetic())
        .value("OES_OPT_CONTRACT_TYPE_CALL", eOesOptContractTypeT::OES_OPT_CONTRACT_TYPE_CALL)
        .value("OES_OPT_CONTRACT_TYPE_PUT", eOesOptContractTypeT::OES_OPT_CONTRACT_TYPE_PUT)
        .value("__OES_OPT_CONTRACT_TYPE_MAX", eOesOptContractTypeT::__OES_OPT_CONTRACT_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesOptInvLevelT>(m, "eOesOptInvLevelT", pybind11::arithmetic())
        .value("OES_OPT_INV_LEVEL_B", eOesOptInvLevelT::OES_OPT_INV_LEVEL_B)
        .value("OES_OPT_INV_LEVEL_L", eOesOptInvLevelT::OES_OPT_INV_LEVEL_L)
        .value("OES_OPT_INV_LEVEL_A", eOesOptInvLevelT::OES_OPT_INV_LEVEL_A)
        .value("__OES_OPT_INV_LEVEL_MAX", eOesOptInvLevelT::__OES_OPT_INV_LEVEL_MAX)
        .export_values()
    ;
    pybind11::enum_<eOpenFlagTypeT>(m, "eOpenFlagTypeT", pybind11::arithmetic())
        .value("OPEN_FLAG_TYPE_ALLOW", eOpenFlagTypeT::OPEN_FLAG_TYPE_ALLOW)
        .value("OPEN_FLAG_TYPE_FORBID", eOpenFlagTypeT::OPEN_FLAG_TYPE_FORBID)
        .value("__OPEN_FLAG_TYPE_MAX", eOpenFlagTypeT::__OPEN_FLAG_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eOesOptionOpenFlagT>(m, "eOesOptionOpenFlagT", pybind11::arithmetic())
        .value("OES_OPTION_OPEN_FLAG_ALLOW", eOesOptionOpenFlagT::OES_OPTION_OPEN_FLAG_ALLOW)
        .value("OES_OPTION_OPEN_FLAG_FORBID", eOesOptionOpenFlagT::OES_OPTION_OPEN_FLAG_FORBID)
        .export_values()
    ;
    pybind11::enum_<eOesPositionEffT>(m, "eOesPositionEffT", pybind11::arithmetic())
        .value("OES_POSITION_INVALID", eOesPositionEffT::OES_POSITION_INVALID)
        .value("OES_POSITION_OPEN", eOesPositionEffT::OES_POSITION_OPEN)
        .value("OES_POSITION_CLOSE", eOesPositionEffT::OES_POSITION_CLOSE)
        .export_values()
    ;
    pybind11::enum_<eOesOptionTypeT>(m, "eOesOptionTypeT", pybind11::arithmetic())
        .value("OES_OPTION_TYPE_E", eOesOptionTypeT::OES_OPTION_TYPE_E)
        .value("OES_OPTION_TYPE_A", eOesOptionTypeT::OES_OPTION_TYPE_A)
        .value("__OES_OPTION_TYPE_MAX", eOesOptionTypeT::__OES_OPTION_TYPE_MAX)
        .export_values()
    ;
    pybind11::enum_<eSMsgProtocolTypeT>(m, "eSMsgProtocolTypeT", pybind11::arithmetic())
        .value("SMSG_PROTO_BINARY", eSMsgProtocolTypeT::SMSG_PROTO_BINARY)
        .value("SMSG_PROTO_JSON", eSMsgProtocolTypeT::SMSG_PROTO_JSON)
        .value("SMSG_PROTO_FIX", eSMsgProtocolTypeT::SMSG_PROTO_FIX)
        .value("SMSG_PROTO_PROTOBUF", eSMsgProtocolTypeT::SMSG_PROTO_PROTOBUF)
        .value("__MAX_SMSG_PROTO_TYPE", eSMsgProtocolTypeT::__MAX_SMSG_PROTO_TYPE)
        .export_values()
    ;
    pybind11::enum_<eSMsgFlagT>(m, "eSMsgFlagT", pybind11::arithmetic())
        .value("SMSG_MSGFLAG_NONE", eSMsgFlagT::SMSG_MSGFLAG_NONE)
        .value("SMSG_MSGFLAG_REQ", eSMsgFlagT::SMSG_MSGFLAG_REQ)
        .value("SMSG_MSGFLAG_RSP", eSMsgFlagT::SMSG_MSGFLAG_RSP)
        .value("SMSG_MSGFLAG_NESTED", eSMsgFlagT::SMSG_MSGFLAG_NESTED)
        .value("SMSG_MSGFLAG_COMPRESSED", eSMsgFlagT::SMSG_MSGFLAG_COMPRESSED)
        .value("SMSG_MSGFLAG_MASK_RSPFLAG", eSMsgFlagT::SMSG_MSGFLAG_MASK_RSPFLAG)
        .value("SMSG_MSGFLAG_MASK_PROTOCOL", eSMsgFlagT::SMSG_MSGFLAG_MASK_PROTOCOL)
        .export_values()
    ;
    pybind11::enum_<eOesMsgTypeT>(m, "eOesMsgTypeT", pybind11::arithmetic())
        .value("OESMSG_ORD_NEW_ORDER", eOesMsgTypeT::OESMSG_ORD_NEW_ORDER)
        .value("OESMSG_ORD_CANCEL_REQUEST", eOesMsgTypeT::OESMSG_ORD_CANCEL_REQUEST)
        .value("OESMSG_ORD_BATCH_ORDERS", eOesMsgTypeT::OESMSG_ORD_BATCH_ORDERS)
        .value("__OESMSG_ORD_MAX", eOesMsgTypeT::__OESMSG_ORD_MAX)
        .value("__OESMSG_RPT_MIN", eOesMsgTypeT::__OESMSG_RPT_MIN)
        .value("OESMSG_RPT_MARKET_STATE", eOesMsgTypeT::OESMSG_RPT_MARKET_STATE)
        .value("OESMSG_RPT_REPORT_SYNCHRONIZATION", eOesMsgTypeT::OESMSG_RPT_REPORT_SYNCHRONIZATION)
        .value("OESMSG_RPT_BUSINESS_REJECT", eOesMsgTypeT::OESMSG_RPT_BUSINESS_REJECT)
        .value("OESMSG_RPT_ORDER_INSERT", eOesMsgTypeT::OESMSG_RPT_ORDER_INSERT)
        .value("OESMSG_RPT_ORDER_REPORT", eOesMsgTypeT::OESMSG_RPT_ORDER_REPORT)
        .value("OESMSG_RPT_TRADE_REPORT", eOesMsgTypeT::OESMSG_RPT_TRADE_REPORT)
        .value("OESMSG_RPT_FUND_TRSF_REJECT", eOesMsgTypeT::OESMSG_RPT_FUND_TRSF_REJECT)
        .value("OESMSG_RPT_FUND_TRSF_REPORT", eOesMsgTypeT::OESMSG_RPT_FUND_TRSF_REPORT)
        .value("OESMSG_RPT_CASH_ASSET_VARIATION", eOesMsgTypeT::OESMSG_RPT_CASH_ASSET_VARIATION)
        .value("OESMSG_RPT_STOCK_HOLDING_VARIATION", eOesMsgTypeT::OESMSG_RPT_STOCK_HOLDING_VARIATION)
        .value("OESMSG_RPT_OPTION_HOLDING_VARIATION", eOesMsgTypeT::OESMSG_RPT_OPTION_HOLDING_VARIATION)
        .value("__OESMSG_RPT_MAX", eOesMsgTypeT::__OESMSG_RPT_MAX)
        .value("__OESMSG_NONTRD_MIN", eOesMsgTypeT::__OESMSG_NONTRD_MIN)
        .value("OESMSG_NONTRD_FUND_TRSF_REQ", eOesMsgTypeT::OESMSG_NONTRD_FUND_TRSF_REQ)
        .value("OESMSG_NONTRD_CHANGE_PASSWORD", eOesMsgTypeT::OESMSG_NONTRD_CHANGE_PASSWORD)
        .value("__OESMSG_NONTRD_MAX", eOesMsgTypeT::__OESMSG_NONTRD_MAX)
        .value("__OESMSG_QRYMSG_MIN", eOesMsgTypeT::__OESMSG_QRYMSG_MIN)
        .value("OESMSG_QRYMSG_CLIENT_OVERVIEW", eOesMsgTypeT::OESMSG_QRYMSG_CLIENT_OVERVIEW)
        .value("OESMSG_QRYMSG_ORD", eOesMsgTypeT::OESMSG_QRYMSG_ORD)
        .value("OESMSG_QRYMSG_TRD", eOesMsgTypeT::OESMSG_QRYMSG_TRD)
        .value("OESMSG_QRYMSG_CASH_ASSET", eOesMsgTypeT::OESMSG_QRYMSG_CASH_ASSET)
        .value("OESMSG_QRYMSG_STK_HLD", eOesMsgTypeT::OESMSG_QRYMSG_STK_HLD)
        .value("OESMSG_QRYMSG_OPT_HLD", eOesMsgTypeT::OESMSG_QRYMSG_OPT_HLD)
        .value("OESMSG_QRYMSG_CUST", eOesMsgTypeT::OESMSG_QRYMSG_CUST)
        .value("OESMSG_QRYMSG_INV_ACCT", eOesMsgTypeT::OESMSG_QRYMSG_INV_ACCT)
        .value("OESMSG_QRYMSG_COMMISSION_RATE", eOesMsgTypeT::OESMSG_QRYMSG_COMMISSION_RATE)
        .value("OESMSG_QRYMSG_FUND_TRSF", eOesMsgTypeT::OESMSG_QRYMSG_FUND_TRSF)
        .value("OESMSG_QRYMSG_STOCK", eOesMsgTypeT::OESMSG_QRYMSG_STOCK)
        .value("OESMSG_QRYMSG_ETF", eOesMsgTypeT::OESMSG_QRYMSG_ETF)
        .value("OESMSG_QRYMSG_ETF_COMPONENT", eOesMsgTypeT::OESMSG_QRYMSG_ETF_COMPONENT)
        .value("OESMSG_QRYMSG_OPTION", eOesMsgTypeT::OESMSG_QRYMSG_OPTION)
        .value("OESMSG_QRYMSG_ISSUE", eOesMsgTypeT::OESMSG_QRYMSG_ISSUE)
        .value("OESMSG_QRYMSG_LOT_WINNING", eOesMsgTypeT::OESMSG_QRYMSG_LOT_WINNING)
        .value("OESMSG_QRYMSG_TRADING_DAY", eOesMsgTypeT::OESMSG_QRYMSG_TRADING_DAY)
        .value("OESMSG_QRYMSG_MARKET_STATE", eOesMsgTypeT::OESMSG_QRYMSG_MARKET_STATE)
        .value("OESMSG_QRYMSG_COUNTER_CASH", eOesMsgTypeT::OESMSG_QRYMSG_COUNTER_CASH)
        .value("__OESMSG_QRYMSG_MAX", eOesMsgTypeT::__OESMSG_QRYMSG_MAX)
        .value("OESMSG_SESS_TRD_LOGIN", eOesMsgTypeT::OESMSG_SESS_TRD_LOGIN)
        .value("OESMSG_SESS_RPT_LOGIN", eOesMsgTypeT::OESMSG_SESS_RPT_LOGIN)
        .value("OESMSG_SESS_QRY_LOGIN", eOesMsgTypeT::OESMSG_SESS_QRY_LOGIN)
        .value("OESMSG_SESS_HEARTBEAT", eOesMsgTypeT::OESMSG_SESS_HEARTBEAT)
        .value("OESMSG_SESS_TEST_REQUEST", eOesMsgTypeT::OESMSG_SESS_TEST_REQUEST)
        .value("OESMSG_SESS_LOGOUT", eOesMsgTypeT::OESMSG_SESS_LOGOUT)
        .value("OESMSG_RPT_ORDER_REJECT", eOesMsgTypeT::OESMSG_RPT_ORDER_REJECT)
        .export_values()
    ;
    pybind11::enum_<eOesSubscribeReportTypeT>(m, "eOesSubscribeReportTypeT", pybind11::arithmetic())
        .value("OES_SUB_RPT_TYPE_DEFAULT", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_DEFAULT)
        .value("OES_SUB_RPT_TYPE_BUSINESS_REJECT", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_BUSINESS_REJECT)
        .value("OES_SUB_RPT_TYPE_ORDER_INSERT", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_ORDER_INSERT)
        .value("OES_SUB_RPT_TYPE_ORDER_REPORT", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_ORDER_REPORT)
        .value("OES_SUB_RPT_TYPE_TRADE_REPORT", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_TRADE_REPORT)
        .value("OES_SUB_RPT_TYPE_FUND_TRSF_REPORT", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_FUND_TRSF_REPORT)
        .value("OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION)
        .value("OES_SUB_RPT_TYPE_HOLDING_VARIATION", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_HOLDING_VARIATION)
        .value("OES_SUB_RPT_TYPE_MARKET_STATE", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_MARKET_STATE)
        .value("OES_SUB_RPT_TYPE_ALL", eOesSubscribeReportTypeT::OES_SUB_RPT_TYPE_ALL)
        .value("__MAX_OES_SUB_RPT_TYPE", eOesSubscribeReportTypeT::__MAX_OES_SUB_RPT_TYPE)
        .export_values()
    ;
    pybind11::enum_<eSSocketProtocolTypeT>(m, "eSSocketProtocolTypeT", pybind11::arithmetic())
        .value("SPK_SOCKET_PROTOCOL_TCP", eSSocketProtocolTypeT::SPK_SOCKET_PROTOCOL_TCP)
        .value("SPK_SOCKET_PROTOCOL_IPC", eSSocketProtocolTypeT::SPK_SOCKET_PROTOCOL_IPC)
        .value("SPK_SOCKET_PROTOCOL_UDP_UCAST", eSSocketProtocolTypeT::SPK_SOCKET_PROTOCOL_UDP_UCAST)
        .value("SPK_SOCKET_PROTOCOL_UDP_MCAST", eSSocketProtocolTypeT::SPK_SOCKET_PROTOCOL_UDP_MCAST)
        .value("SPK_SOCKET_PROTOCOL_PGM", eSSocketProtocolTypeT::SPK_SOCKET_PROTOCOL_PGM)
        .value("SPK_SOCKET_PROTOCOL_EPGM", eSSocketProtocolTypeT::SPK_SOCKET_PROTOCOL_EPGM)
        .value("__MAX_SPK_SOCKET_PROTOCOL", eSSocketProtocolTypeT::__MAX_SPK_SOCKET_PROTOCOL)
        .export_values()
    ;
    pybind11::enum_<eGeneralClientClusterTypeT>(m, "eGeneralClientClusterTypeT", pybind11::arithmetic())
        .value("GENERAL_CLI_CLUSTER_UNDEFINED", eGeneralClientClusterTypeT::GENERAL_CLI_CLUSTER_UNDEFINED)
        .value("GENERAL_CLI_CLUSTER_REPLICA_SET", eGeneralClientClusterTypeT::GENERAL_CLI_CLUSTER_REPLICA_SET)
        .value("GENERAL_CLI_CLUSTER_PEER_NODES", eGeneralClientClusterTypeT::GENERAL_CLI_CLUSTER_PEER_NODES)
        .value("__MAX_GENERAL_CLI_CLUSTER_TYPE", eGeneralClientClusterTypeT::__MAX_GENERAL_CLI_CLUSTER_TYPE)
        .export_values()
    ;
    pybind11::enum_<eGeneralClientEncryptTypeT>(m, "eGeneralClientEncryptTypeT", pybind11::arithmetic())
        .value("GENERAL_CLI_ENCRYPT_NONE", eGeneralClientEncryptTypeT::GENERAL_CLI_ENCRYPT_NONE)
        .value("GENERAL_CLI_ENCRYPT_MD5", eGeneralClientEncryptTypeT::GENERAL_CLI_ENCRYPT_MD5)
        .value("GENERAL_CLI_ENCRYPT_SHA", eGeneralClientEncryptTypeT::GENERAL_CLI_ENCRYPT_SHA)
        .value("GENERAL_CLI_ENCRYPT_DES", eGeneralClientEncryptTypeT::GENERAL_CLI_ENCRYPT_DES)
        .value("GENERAL_CLI_ENCRYPT_AES", eGeneralClientEncryptTypeT::GENERAL_CLI_ENCRYPT_AES)
        .value("GENERAL_CLI_ENCRYPT_RSA", eGeneralClientEncryptTypeT::GENERAL_CLI_ENCRYPT_RSA)
        .export_values()
    ;
    pybind11::enum_<eOesApiChannelTypeT>(m, "eOesApiChannelTypeT", pybind11::arithmetic())
        .value("OESAPI_CHANNEL_TYPE_ORDER", eOesApiChannelTypeT::OESAPI_CHANNEL_TYPE_ORDER)
        .value("OESAPI_CHANNEL_TYPE_REPORT", eOesApiChannelTypeT::OESAPI_CHANNEL_TYPE_REPORT)
        .value("OESAPI_CHANNEL_TYPE_QUERY", eOesApiChannelTypeT::OESAPI_CHANNEL_TYPE_QUERY)
        .export_values()
    ;
    pybind11::enum_<eMdsExchangeIdT>(m, "eMdsExchangeIdT", pybind11::arithmetic())
        .value("MDS_EXCH_SSE", eMdsExchangeIdT::MDS_EXCH_SSE)
        .value("MDS_EXCH_SZSE", eMdsExchangeIdT::MDS_EXCH_SZSE)
        .value("__MAX_MDS_EXCH", eMdsExchangeIdT::__MAX_MDS_EXCH)
        .value("__MAX_MDS_EXCH_ALIGNED4", eMdsExchangeIdT::__MAX_MDS_EXCH_ALIGNED4)
        .value("__MAX_MDS_EXCH_ALIGNED8", eMdsExchangeIdT::__MAX_MDS_EXCH_ALIGNED8)
        .export_values()
    ;
    pybind11::enum_<eMdsMsgSourceT>(m, "eMdsMsgSourceT", pybind11::arithmetic())
        .value("MDS_MSGSRC_UNDEFINED", eMdsMsgSourceT::MDS_MSGSRC_UNDEFINED)
        .value("MDS_MSGSRC_EZEI_TCP", eMdsMsgSourceT::MDS_MSGSRC_EZEI_TCP)
        .value("MDS_MSGSRC_EZEI_UDP", eMdsMsgSourceT::MDS_MSGSRC_EZEI_UDP)
        .value("MDS_MSGSRC_VDE_LEVEL2", eMdsMsgSourceT::MDS_MSGSRC_VDE_LEVEL2)
        .value("MDS_MSGSRC_VDE_LEVEL1", eMdsMsgSourceT::MDS_MSGSRC_VDE_LEVEL1)
        .value("MDS_MSGSRC_SZSE_MDGW_BINARY", eMdsMsgSourceT::MDS_MSGSRC_SZSE_MDGW_BINARY)
        .value("MDS_MSGSRC_SZSE_MDGW_STEP", eMdsMsgSourceT::MDS_MSGSRC_SZSE_MDGW_STEP)
        .value("MDS_MSGSRC_MDS_TCP", eMdsMsgSourceT::MDS_MSGSRC_MDS_TCP)
        .value("MDS_MSGSRC_MDS_UDP", eMdsMsgSourceT::MDS_MSGSRC_MDS_UDP)
        .value("MDS_MSGSRC_FILE_MKTDT", eMdsMsgSourceT::MDS_MSGSRC_FILE_MKTDT)
        .value("MDS_MSGSRC_SSE_MDGW_BINARY", eMdsMsgSourceT::MDS_MSGSRC_SSE_MDGW_BINARY)
        .value("MDS_MSGSRC_SSE_MDGW_STEP", eMdsMsgSourceT::MDS_MSGSRC_SSE_MDGW_STEP)
        .value("__MAX_MDS_MSGSRC", eMdsMsgSourceT::__MAX_MDS_MSGSRC)
        .value("MDS_MSGSRC_MDGW_BINARY", eMdsMsgSourceT::MDS_MSGSRC_MDGW_BINARY)
        .value("MDS_MSGSRC_MDGW_STEP", eMdsMsgSourceT::MDS_MSGSRC_MDGW_STEP)
        .export_values()
    ;
    pybind11::enum_<eMdsSecurityTypeT>(m, "eMdsSecurityTypeT", pybind11::arithmetic())
        .value("MDS_SECURITY_TYPE_STOCK", eMdsSecurityTypeT::MDS_SECURITY_TYPE_STOCK)
        .value("MDS_SECURITY_TYPE_INDEX", eMdsSecurityTypeT::MDS_SECURITY_TYPE_INDEX)
        .value("MDS_SECURITY_TYPE_OPTION", eMdsSecurityTypeT::MDS_SECURITY_TYPE_OPTION)
        .value("__MAX_MDS_SECURITY_TYPE", eMdsSecurityTypeT::__MAX_MDS_SECURITY_TYPE)
        .export_values()
    ;
    pybind11::enum_<eMdsMdStreamTypeT>(m, "eMdsMdStreamTypeT", pybind11::arithmetic())
        .value("MDS_MD_STREAM_TYPE_INDEX", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_INDEX)
        .value("MDS_MD_STREAM_TYPE_STOCK", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_STOCK)
        .value("MDS_MD_STREAM_TYPE_BOND", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_BOND)
        .value("MDS_MD_STREAM_TYPE_FUND", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_FUND)
        .value("MDS_MD_STREAM_TYPE_SZSE_STOCK", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_SZSE_STOCK)
        .value("MDS_MD_STREAM_TYPE_SZSE_REPO", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_SZSE_REPO)
        .value("MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS)
        .value("MDS_MD_STREAM_TYPE_OPTION", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_OPTION)
        .value("MDS_MD_STREAM_TYPE_OTHERS", eMdsMdStreamTypeT::MDS_MD_STREAM_TYPE_OTHERS)
        .value("__MAX_MDS_MD_STREAM_TYPE", eMdsMdStreamTypeT::__MAX_MDS_MD_STREAM_TYPE)
        .export_values()
    ;
    pybind11::enum_<eMdsMdLevelT>(m, "eMdsMdLevelT", pybind11::arithmetic())
        .value("MDS_MD_LEVEL_0", eMdsMdLevelT::MDS_MD_LEVEL_0)
        .value("MDS_MD_LEVEL_1", eMdsMdLevelT::MDS_MD_LEVEL_1)
        .value("MDS_MD_LEVEL_2", eMdsMdLevelT::MDS_MD_LEVEL_2)
        .value("__MAX_MDS_MD_LEVEL", eMdsMdLevelT::__MAX_MDS_MD_LEVEL)
        .export_values()
    ;
    pybind11::enum_<eMdsL2PriceLevelOperatorT>(m, "eMdsL2PriceLevelOperatorT", pybind11::arithmetic())
        .value("MDS_L2_PX_OPERATOR_ADD", eMdsL2PriceLevelOperatorT::MDS_L2_PX_OPERATOR_ADD)
        .value("MDS_L2_PX_OPERATOR_UPDATE", eMdsL2PriceLevelOperatorT::MDS_L2_PX_OPERATOR_UPDATE)
        .value("MDS_L2_PX_OPERATOR_DELETE", eMdsL2PriceLevelOperatorT::MDS_L2_PX_OPERATOR_DELETE)
        .value("__MAX_MDS_L2_PX_OPERATOR", eMdsL2PriceLevelOperatorT::__MAX_MDS_L2_PX_OPERATOR)
        .export_values()
    ;
    pybind11::enum_<eMdsL2VirtualAuctionSideT>(m, "eMdsL2VirtualAuctionSideT", pybind11::arithmetic())
        .value("MDS_L2_VIRTUAL_AUCTION_SIDE_NONE", eMdsL2VirtualAuctionSideT::MDS_L2_VIRTUAL_AUCTION_SIDE_NONE)
        .value("MDS_L2_VIRTUAL_AUCTION_SIDE_BID", eMdsL2VirtualAuctionSideT::MDS_L2_VIRTUAL_AUCTION_SIDE_BID)
        .value("MDS_L2_VIRTUAL_AUCTION_SIDE_OFFER", eMdsL2VirtualAuctionSideT::MDS_L2_VIRTUAL_AUCTION_SIDE_OFFER)
        .export_values()
    ;
    pybind11::enum_<eMdsL2TradeExecTypeT>(m, "eMdsL2TradeExecTypeT", pybind11::arithmetic())
        .value("MDS_L2_TRADE_EXECTYPE_CANCELED", eMdsL2TradeExecTypeT::MDS_L2_TRADE_EXECTYPE_CANCELED)
        .value("MDS_L2_TRADE_EXECTYPE_TRADE", eMdsL2TradeExecTypeT::MDS_L2_TRADE_EXECTYPE_TRADE)
        .export_values()
    ;
    pybind11::enum_<eMdsL2TradeBSFlagT>(m, "eMdsL2TradeBSFlagT", pybind11::arithmetic())
        .value("MDS_L2_TRADE_BSFLAG_BUY", eMdsL2TradeBSFlagT::MDS_L2_TRADE_BSFLAG_BUY)
        .value("MDS_L2_TRADE_BSFLAG_SELL", eMdsL2TradeBSFlagT::MDS_L2_TRADE_BSFLAG_SELL)
        .value("MDS_L2_TRADE_BSFLAG_UNKNOWN", eMdsL2TradeBSFlagT::MDS_L2_TRADE_BSFLAG_UNKNOWN)
        .export_values()
    ;
    pybind11::enum_<eMdsL2OrderSideT>(m, "eMdsL2OrderSideT", pybind11::arithmetic())
        .value("MDS_L2_ORDER_SIDE_BUY", eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BUY)
        .value("MDS_L2_ORDER_SIDE_SELL", eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_SELL)
        .value("MDS_L2_ORDER_SIDE_BORROW", eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BORROW)
        .value("MDS_L2_ORDER_SIDE_LEND", eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_LEND)
        .export_values()
    ;
    pybind11::enum_<eMdsL2OrderTypeT>(m, "eMdsL2OrderTypeT", pybind11::arithmetic())
        .value("MDS_L2_ORDER_TYPE_MKT", eMdsL2OrderTypeT::MDS_L2_ORDER_TYPE_MKT)
        .value("MDS_L2_ORDER_TYPE_LMT", eMdsL2OrderTypeT::MDS_L2_ORDER_TYPE_LMT)
        .value("MDS_L2_ORDER_TYPE_SAMEPARTY_BEST", eMdsL2OrderTypeT::MDS_L2_ORDER_TYPE_SAMEPARTY_BEST)
        .export_values()
    ;
    pybind11::enum_<eMdsClientTypeT>(m, "eMdsClientTypeT", pybind11::arithmetic())
        .value("MDS_CLIENT_TYPE_UNDEFINED", eMdsClientTypeT::MDS_CLIENT_TYPE_UNDEFINED)
        .value("MDS_CLIENT_TYPE_INVESTOR", eMdsClientTypeT::MDS_CLIENT_TYPE_INVESTOR)
        .value("MDS_CLIENT_TYPE_VIRTUAL", eMdsClientTypeT::MDS_CLIENT_TYPE_VIRTUAL)
        .export_values()
    ;
    pybind11::enum_<eMdsClientStatusT>(m, "eMdsClientStatusT", pybind11::arithmetic())
        .value("MDS_CLIENT_STATUS_UNACTIVATED", eMdsClientStatusT::MDS_CLIENT_STATUS_UNACTIVATED)
        .value("MDS_CLIENT_STATUS_ACTIVATED", eMdsClientStatusT::MDS_CLIENT_STATUS_ACTIVATED)
        .value("MDS_CLIENT_STATUS_PAUSE", eMdsClientStatusT::MDS_CLIENT_STATUS_PAUSE)
        .value("MDS_CLIENT_STATUS_SUSPENDED", eMdsClientStatusT::MDS_CLIENT_STATUS_SUSPENDED)
        .value("MDS_CLIENT_STATUS_CANCELLED", eMdsClientStatusT::MDS_CLIENT_STATUS_CANCELLED)
        .export_values()
    ;
    pybind11::enum_<eMdsMsgTypeT>(m, "eMdsMsgTypeT", pybind11::arithmetic())
        .value("MDS_MSGTYPE_HEARTBEAT", eMdsMsgTypeT::MDS_MSGTYPE_HEARTBEAT)
        .value("MDS_MSGTYPE_TEST_REQUEST", eMdsMsgTypeT::MDS_MSGTYPE_TEST_REQUEST)
        .value("MDS_MSGTYPE_LOGON", eMdsMsgTypeT::MDS_MSGTYPE_LOGON)
        .value("MDS_MSGTYPE_LOGOUT", eMdsMsgTypeT::MDS_MSGTYPE_LOGOUT)
        .value("MDS_MSGTYPE_MARKET_DATA_REQUEST", eMdsMsgTypeT::MDS_MSGTYPE_MARKET_DATA_REQUEST)
        .value("MDS_MSGTYPE_COMPRESSED_PACKETS", eMdsMsgTypeT::MDS_MSGTYPE_COMPRESSED_PACKETS)
        .value("__MDS_MSGTYPE_SESSION_MAX", eMdsMsgTypeT::__MDS_MSGTYPE_SESSION_MAX)
        .value("MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH", eMdsMsgTypeT::MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH)
        .value("MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH", eMdsMsgTypeT::MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH)
        .value("MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH", eMdsMsgTypeT::MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH)
        .value("MDS_MSGTYPE_TRADING_SESSION_STATUS", eMdsMsgTypeT::MDS_MSGTYPE_TRADING_SESSION_STATUS)
        .value("MDS_MSGTYPE_SECURITY_STATUS", eMdsMsgTypeT::MDS_MSGTYPE_SECURITY_STATUS)
        .value("__MDS_MSGTYPE_L1_MAX", eMdsMsgTypeT::__MDS_MSGTYPE_L1_MAX)
        .value("MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT", eMdsMsgTypeT::MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT)
        .value("MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT", eMdsMsgTypeT::MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT)
        .value("MDS_MSGTYPE_L2_TRADE", eMdsMsgTypeT::MDS_MSGTYPE_L2_TRADE)
        .value("MDS_MSGTYPE_L2_ORDER", eMdsMsgTypeT::MDS_MSGTYPE_L2_ORDER)
        .value("MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL", eMdsMsgTypeT::MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL)
        .value("MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL", eMdsMsgTypeT::MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL)
        .value("MDS_MSGTYPE_L2_MARKET_OVERVIEW", eMdsMsgTypeT::MDS_MSGTYPE_L2_MARKET_OVERVIEW)
        .value("MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE", eMdsMsgTypeT::MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE)
        .value("__MDS_MSGTYPE_L2_MAX", eMdsMsgTypeT::__MDS_MSGTYPE_L2_MAX)
        .value("MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT", eMdsMsgTypeT::MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT)
        .value("MDS_MSGTYPE_QRY_SECURITY_STATUS", eMdsMsgTypeT::MDS_MSGTYPE_QRY_SECURITY_STATUS)
        .value("MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS", eMdsMsgTypeT::MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS)
        .value("__MDS_MSGTYPE_QRY_MAX", eMdsMsgTypeT::__MDS_MSGTYPE_QRY_MAX)
        .export_values()
    ;
    pybind11::enum_<eMdsSubscribeModeT>(m, "eMdsSubscribeModeT", pybind11::arithmetic())
        .value("MDS_SUB_MODE_SET", eMdsSubscribeModeT::MDS_SUB_MODE_SET)
        .value("MDS_SUB_MODE_APPEND", eMdsSubscribeModeT::MDS_SUB_MODE_APPEND)
        .value("MDS_SUB_MODE_DELETE", eMdsSubscribeModeT::MDS_SUB_MODE_DELETE)
        .value("__MAX_MDS_SUB_MODE", eMdsSubscribeModeT::__MAX_MDS_SUB_MODE)
        .export_values()
    ;
    pybind11::enum_<eMdsMktSubscribeFlagT>(m, "eMdsMktSubscribeFlagT", pybind11::arithmetic())
        .value("MDS_MKT_SUB_FLAG_DEFAULT", eMdsMktSubscribeFlagT::MDS_MKT_SUB_FLAG_DEFAULT)
        .value("MDS_MKT_SUB_FLAG_ALL", eMdsMktSubscribeFlagT::MDS_MKT_SUB_FLAG_ALL)
        .value("MDS_MKT_SUB_FLAG_DISABLE", eMdsMktSubscribeFlagT::MDS_MKT_SUB_FLAG_DISABLE)
        .value("__MAX_MDS_MKT_SUB_FLAG", eMdsMktSubscribeFlagT::__MAX_MDS_MKT_SUB_FLAG)
        .export_values()
    ;
    pybind11::enum_<eMdsSubscribedTickTypeT>(m, "eMdsSubscribedTickTypeT", pybind11::arithmetic())
        .value("MDS_TICK_TYPE_LATEST_SIMPLIFIED", eMdsSubscribedTickTypeT::MDS_TICK_TYPE_LATEST_SIMPLIFIED)
        .value("MDS_TICK_TYPE_LATEST_TIMELY", eMdsSubscribedTickTypeT::MDS_TICK_TYPE_LATEST_TIMELY)
        .value("MDS_TICK_TYPE_ALL_INCREMENTS", eMdsSubscribedTickTypeT::MDS_TICK_TYPE_ALL_INCREMENTS)
        .value("__MAX_MDS_TICK_TYPE", eMdsSubscribedTickTypeT::__MAX_MDS_TICK_TYPE)
        .export_values()
    ;
    pybind11::enum_<eMdsSubscribedTickExpireTypeT>(m, "eMdsSubscribedTickExpireTypeT", pybind11::arithmetic())
        .value("MDS_TICK_EXPIRE_TYPE_NONE", eMdsSubscribedTickExpireTypeT::MDS_TICK_EXPIRE_TYPE_NONE)
        .value("MDS_TICK_EXPIRE_TYPE_IMMEDIATE", eMdsSubscribedTickExpireTypeT::MDS_TICK_EXPIRE_TYPE_IMMEDIATE)
        .value("MDS_TICK_EXPIRE_TYPE_TIMELY", eMdsSubscribedTickExpireTypeT::MDS_TICK_EXPIRE_TYPE_TIMELY)
        .value("MDS_TICK_EXPIRE_TYPE_TIMEOUT", eMdsSubscribedTickExpireTypeT::MDS_TICK_EXPIRE_TYPE_TIMEOUT)
        .value("__MAX_MDS_TICK_EXPIRE_TYPE", eMdsSubscribedTickExpireTypeT::__MAX_MDS_TICK_EXPIRE_TYPE)
        .export_values()
    ;
    pybind11::enum_<eMdsSubscribeDataTypeT>(m, "eMdsSubscribeDataTypeT", pybind11::arithmetic())
        .value("MDS_SUB_DATA_TYPE_DEFAULT", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_DEFAULT)
        .value("MDS_SUB_DATA_TYPE_L1_SNAPSHOT", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_L1_SNAPSHOT)
        .value("MDS_SUB_DATA_TYPE_L2_SNAPSHOT", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_L2_SNAPSHOT)
        .value("MDS_SUB_DATA_TYPE_L2_BEST_ORDERS", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_L2_BEST_ORDERS)
        .value("MDS_SUB_DATA_TYPE_L2_TRADE", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_L2_TRADE)
        .value("MDS_SUB_DATA_TYPE_L2_ORDER", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_L2_ORDER)
        .value("MDS_SUB_DATA_TYPE_L2_VIRTUAL_AUCTION_PRICE", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_L2_VIRTUAL_AUCTION_PRICE)
        .value("MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW)
        .value("MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS)
        .value("MDS_SUB_DATA_TYPE_SECURITY_STATUS", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_SECURITY_STATUS)
        .value("MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT)
        .value("MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT)
        .value("MDS_SUB_DATA_TYPE_NONE", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_NONE)
        .value("MDS_SUB_DATA_TYPE_ALL", eMdsSubscribeDataTypeT::MDS_SUB_DATA_TYPE_ALL)
        .value("__MAX_MDS_SUB_DATA_TYPE", eMdsSubscribeDataTypeT::__MAX_MDS_SUB_DATA_TYPE)
        .export_values()
    ;
    pybind11::enum_<eMdsTickChannelNoT>(m, "eMdsTickChannelNoT", pybind11::arithmetic())
        .value("MDS_CHANNEL_NO_DEFAULT", eMdsTickChannelNoT::MDS_CHANNEL_NO_DEFAULT)
        .value("MDS_CHANNEL_NO_ONE", eMdsTickChannelNoT::MDS_CHANNEL_NO_ONE)
        .value("MDS_CHANNEL_NO_TWO", eMdsTickChannelNoT::MDS_CHANNEL_NO_TWO)
        .value("MDS_CHANNEL_NO_THREE", eMdsTickChannelNoT::MDS_CHANNEL_NO_THREE)
        .value("MDS_CHANNEL_NO_FOUR", eMdsTickChannelNoT::MDS_CHANNEL_NO_FOUR)
        .value("MDS_CHANNEL_NO_ALL", eMdsTickChannelNoT::MDS_CHANNEL_NO_ALL)
        .value("MDS_CHANNEL_NO_NONE", eMdsTickChannelNoT::MDS_CHANNEL_NO_NONE)
        .export_values()
    ;
    pybind11::enum_<eMdsApiChannelTypeT>(m, "eMdsApiChannelTypeT", pybind11::arithmetic())
        .value("MDSAPI_CHANNEL_TYPE_TCP", eMdsApiChannelTypeT::MDSAPI_CHANNEL_TYPE_TCP)
        .value("MDSAPI_CHANNEL_TYPE_UDP", eMdsApiChannelTypeT::MDSAPI_CHANNEL_TYPE_UDP)
        .value("MDSAPI_CHANNEL_TYPE_QUERY", eMdsApiChannelTypeT::MDSAPI_CHANNEL_TYPE_QUERY)
        .export_values()
    ;

}

void generate_constants(pybind11::module &m)
{
    m.add_object("OES_APPL_VER_ID", pybind11::str("0.15.7.4"));
    m.add_object("OES_MIN_APPL_VER_ID", pybind11::str("0.15.5"));
    m.add_object("OESAPI_CFG_DEFAULT_SECTION", pybind11::str("oes_client"));
    m.add_object("OESAPI_CFG_DEFAULT_SECTION_LOGGER", pybind11::str("log"));
    m.add_object("OESAPI_CFG_DEFAULT_KEY_ORD_ADDR", pybind11::str("ordServer"));
    m.add_object("OESAPI_CFG_DEFAULT_KEY_RPT_ADDR", pybind11::str("rptServer"));
    m.add_object("OESAPI_CFG_DEFAULT_KEY_QRY_ADDR", pybind11::str("qryServer"));
    m.add_object("OESAPI_DEFAULT_STRING_DELIM", pybind11::str(",;| \t\r\n"));
    m.add_object("MDS_APPL_VER_ID", pybind11::str("0.15.7.4"));
    m.add_object("MDS_MIN_APPL_VER_ID", pybind11::str("0.15.5"));
    m.add_object("MDSAPI_CFG_DEFAULT_SECTION", pybind11::str("mds_client"));
    m.add_object("MDSAPI_CFG_DEFAULT_SECTION_LOGGER", pybind11::str("log"));
    m.add_object("MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR", pybind11::str("tcpServer"));
    m.add_object("MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR", pybind11::str("qryServer"));
    m.add_object("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1", pybind11::str("udpServer.L1"));
    m.add_object("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2", pybind11::str("udpServer.L2"));
    m.add_object("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE", pybind11::str("udpServer.TickTrade"));
    m.add_object("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER", pybind11::str("udpServer.TickOrder"));
    m.add_object("MDSAPI_DEFAULT_STRING_DELIM", pybind11::str(",;| \t\r\n"));

}

void generate_constants_class(pybind11::module &m)
{
    struct constants_class{};
    pybind11::class_<constants_class> c(m, "constants");
    c.attr("OES_APPL_VER_ID") = pybind11::str("0.15.7.4");
    c.attr("OES_MIN_APPL_VER_ID") = pybind11::str("0.15.5");
    c.attr("OESAPI_CFG_DEFAULT_SECTION") = pybind11::str("oes_client");
    c.attr("OESAPI_CFG_DEFAULT_SECTION_LOGGER") = pybind11::str("log");
    c.attr("OESAPI_CFG_DEFAULT_KEY_ORD_ADDR") = pybind11::str("ordServer");
    c.attr("OESAPI_CFG_DEFAULT_KEY_RPT_ADDR") = pybind11::str("rptServer");
    c.attr("OESAPI_CFG_DEFAULT_KEY_QRY_ADDR") = pybind11::str("qryServer");
    c.attr("OESAPI_DEFAULT_STRING_DELIM") = pybind11::str(",;| \t\r\n");
    c.attr("MDS_APPL_VER_ID") = pybind11::str("0.15.7.4");
    c.attr("MDS_MIN_APPL_VER_ID") = pybind11::str("0.15.5");
    c.attr("MDSAPI_CFG_DEFAULT_SECTION") = pybind11::str("mds_client");
    c.attr("MDSAPI_CFG_DEFAULT_SECTION_LOGGER") = pybind11::str("log");
    c.attr("MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR") = pybind11::str("tcpServer");
    c.attr("MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR") = pybind11::str("qryServer");
    c.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1") = pybind11::str("udpServer.L1");
    c.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2") = pybind11::str("udpServer.L2");
    c.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE") = pybind11::str("udpServer.TickTrade");
    c.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER") = pybind11::str("udpServer.TickOrder");
    c.attr("MDSAPI_DEFAULT_STRING_DELIM") = pybind11::str(",;| \t\r\n");

}

void init_caster(pybind11::module &m)
{
    auto c = autocxxpy::caster::bind(m, "cast"); 
    c.def("toOesOrdReqT", 
        &autocxxpy::caster::copy<OesOrdReqT>
        );
    c.def("to_OesOrdReq", 
        &autocxxpy::caster::copy<OesOrdReqT>
        );
    c.def("toOesOrdCancelReqT", 
        &autocxxpy::caster::copy<OesOrdCancelReqT>
        );
    c.def("to_OesOrdCancelReq", 
        &autocxxpy::caster::copy<OesOrdCancelReqT>
        );
    c.def("toOesOrdRejectT", 
        &autocxxpy::caster::copy<OesOrdRejectT>
        );
    c.def("to_OesOrdReject", 
        &autocxxpy::caster::copy<OesOrdRejectT>
        );
    c.def("toOesOrdCnfmT", 
        &autocxxpy::caster::copy<OesOrdItemT>
        );
    c.def("toOesOrdItemT", 
        &autocxxpy::caster::copy<OesOrdItemT>
        );
    c.def("to_OesOrdCnfm", 
        &autocxxpy::caster::copy<OesOrdCnfmT>
        );
    c.def("toOesTrdBaseInfoT", 
        &autocxxpy::caster::copy<OesTrdBaseInfoT>
        );
    c.def("to_OesTrdBaseInfo", 
        &autocxxpy::caster::copy<OesTrdBaseInfoT>
        );
    c.def("toOesTrdCnfmT", 
        &autocxxpy::caster::copy<OesTrdItemT>
        );
    c.def("toOesTrdItemT", 
        &autocxxpy::caster::copy<OesTrdItemT>
        );
    c.def("to_OesTrdCnfm", 
        &autocxxpy::caster::copy<OesTrdCnfmT>
        );
    c.def("toOesLotWinningBaseInfoT", 
        &autocxxpy::caster::copy<OesLotWinningItemT>
        );
    c.def("to_OesLotWinningBaseInfo", 
        &autocxxpy::caster::copy<OesLotWinningBaseInfoT>
        );
    c.def("toOesLotWinningItemT", 
        &autocxxpy::caster::copy<OesLotWinningItemT>
        );
    c.def("toOesFundTrsfBaseInfoT", 
        &autocxxpy::caster::copy<OesFundTrsfBaseInfoT>
        );
    c.def("to_OesFundTrsfBaseInfo", 
        &autocxxpy::caster::copy<OesFundTrsfBaseInfoT>
        );
    c.def("toOesFundTrsfReqT", 
        &autocxxpy::caster::copy<OesFundTrsfReqT>
        );
    c.def("to_OesFundTrsfReq", 
        &autocxxpy::caster::copy<OesFundTrsfReqT>
        );
    c.def("toOesFundTrsfRejectT", 
        &autocxxpy::caster::copy<OesFundTrsfRejectT>
        );
    c.def("to_OesFundTrsfReject", 
        &autocxxpy::caster::copy<OesFundTrsfRejectT>
        );
    c.def("toOesFundTrsfReportT", 
        &autocxxpy::caster::copy<OesFundTransferSerialItemT>
        );
    c.def("to_OesFundTrsfReport", 
        &autocxxpy::caster::copy<OesFundTrsfReportT>
        );
    c.def("toOesFundTransferSerialItemT", 
        &autocxxpy::caster::copy<OesFundTransferSerialItemT>
        );
    c.def("toOesIssueBaseInfoT", 
        &autocxxpy::caster::copy<OesIssueItemT>
        );
    c.def("to_OesIssueBaseInfo", 
        &autocxxpy::caster::copy<OesIssueBaseInfoT>
        );
    c.def("toOesIssueItemT", 
        &autocxxpy::caster::copy<OesIssueItemT>
        );
    c.def("toOesPriceLimitT", 
        &autocxxpy::caster::copy<OesPriceLimitT>
        );
    c.def("to_OesPriceLimit", 
        &autocxxpy::caster::copy<OesPriceLimitT>
        );
    c.def("toOesStockBaseInfoT", 
        &autocxxpy::caster::copy<OesStockItemT>
        );
    c.def("toOesStockItemT", 
        &autocxxpy::caster::copy<OesStockItemT>
        );
    c.def("to_OesStockBaseInfo", 
        &autocxxpy::caster::copy<OesStockBaseInfoT>
        );
    c.def("toOesEtfBaseInfoT", 
        &autocxxpy::caster::copy<OesEtfItemT>
        );
    c.def("to_OesEtfBaseInfo", 
        &autocxxpy::caster::copy<OesEtfBaseInfoT>
        );
    c.def("toOesEtfItemT", 
        &autocxxpy::caster::copy<OesEtfItemT>
        );
    c.def("toOesEtfComponentBaseInfoT", 
        &autocxxpy::caster::copy<OesEtfComponentBaseInfoT>
        );
    c.def("to_OesEtfComponentBaseInfo", 
        &autocxxpy::caster::copy<OesEtfComponentBaseInfoT>
        );
    c.def("toOesOptionBaseInfoT", 
        &autocxxpy::caster::copy<OesOptionItemT>
        );
    c.def("to_OesOptionBaseInfo", 
        &autocxxpy::caster::copy<OesOptionBaseInfoT>
        );
    c.def("toOesOptionItemT", 
        &autocxxpy::caster::copy<OesOptionItemT>
        );
    c.def("toOesCashAssetBaseInfoT", 
        &autocxxpy::caster::copy<OesCashAssetBaseInfoT>
        );
    c.def("to_OesCashAssetBaseInfo", 
        &autocxxpy::caster::copy<OesCashAssetBaseInfoT>
        );
    c.def("toOesCustBaseInfoT", 
        &autocxxpy::caster::copy<OesCustItemT>
        );
    c.def("toOesCustItemT", 
        &autocxxpy::caster::copy<OesCustItemT>
        );
    c.def("to_OesCustBaseInfo", 
        &autocxxpy::caster::copy<OesCustBaseInfoT>
        );
    c.def("toOesInvAcctBaseInfoT", 
        &autocxxpy::caster::copy<OesInvAcctBaseInfoT>
        );
    c.def("to_OesInvAcctBaseInfo", 
        &autocxxpy::caster::copy<OesInvAcctBaseInfoT>
        );
    c.def("toOesStkHoldingBaseInfoT", 
        &autocxxpy::caster::copy<OesStkHoldingBaseInfoT>
        );
    c.def("to_OesStkHoldingBaseInfo", 
        &autocxxpy::caster::copy<OesStkHoldingBaseInfoT>
        );
    c.def("toOesOptHoldingBaseInfoT", 
        &autocxxpy::caster::copy<OesOptHoldingBaseInfoT>
        );
    c.def("to_OesOptHoldingBaseInfo", 
        &autocxxpy::caster::copy<OesOptHoldingBaseInfoT>
        );
    c.def("toOesMarketStateInfoT", 
        &autocxxpy::caster::copy<OesMarketStateItemT>
        );
    c.def("toOesMarketStateItemT", 
        &autocxxpy::caster::copy<OesMarketStateItemT>
        );
    c.def("to_OesMarketStateInfo", 
        &autocxxpy::caster::copy<OesMarketStateInfoT>
        );
    c.def("toOesTradingPermissionEntryT", 
        &autocxxpy::caster::copy<OesTradingPermissionEntryT>
        );
    c.def("to_OesTradingPermissionEntry", 
        &autocxxpy::caster::copy<OesTradingPermissionEntryT>
        );
    c.def("toOesInputSourceInfoT", 
        &autocxxpy::caster::copy<OesInputSourceInfoT>
        );
    c.def("to_OesInputSourceInfo", 
        &autocxxpy::caster::copy<OesInputSourceInfoT>
        );
    c.def("toSMsgHeadT", 
        &autocxxpy::caster::copy<SMsgHeadT>
        );
    c.def("to_SMsgHead", 
        &autocxxpy::caster::copy<SMsgHeadT>
        );
    c.def("toOesQryCursorT", 
        &autocxxpy::caster::copy<OesQryCursorT>
        );
    c.def("to_OesQryCursor", 
        &autocxxpy::caster::copy<OesQryCursorT>
        );
    c.def("toOesQryReqHeadT", 
        &autocxxpy::caster::copy<OesQryReqHeadT>
        );
    c.def("to_OesQryReqHead", 
        &autocxxpy::caster::copy<OesQryReqHeadT>
        );
    c.def("toOesQryRspHeadT", 
        &autocxxpy::caster::copy<OesQryRspHeadT>
        );
    c.def("to_OesQryRspHead", 
        &autocxxpy::caster::copy<OesQryRspHeadT>
        );
    c.def("toOesQryOrdFilterT", 
        &autocxxpy::caster::copy<OesQryOrdFilterT>
        );
    c.def("to_OesQryOrdFilter", 
        &autocxxpy::caster::copy<OesQryOrdFilterT>
        );
    c.def("toOesQryOrdReqT", 
        &autocxxpy::caster::copy<OesQryOrdReqT>
        );
    c.def("to_OesQryOrdReq", 
        &autocxxpy::caster::copy<OesQryOrdReqT>
        );
    c.def("toOesQryOrdRspT", 
        &autocxxpy::caster::copy<OesQryOrdRspT>
        );
    c.def("to_OesQryOrdRsp", 
        &autocxxpy::caster::copy<OesQryOrdRspT>
        );
    c.def("toOesQryTrdFilterT", 
        &autocxxpy::caster::copy<OesQryTrdFilterT>
        );
    c.def("to_OesQryTrdFilter", 
        &autocxxpy::caster::copy<OesQryTrdFilterT>
        );
    c.def("toOesQryTrdReqT", 
        &autocxxpy::caster::copy<OesQryTrdReqT>
        );
    c.def("to_OesQryTrdReq", 
        &autocxxpy::caster::copy<OesQryTrdReqT>
        );
    c.def("toOesQryTrdRspT", 
        &autocxxpy::caster::copy<OesQryTrdRspT>
        );
    c.def("to_OesQryTrdRsp", 
        &autocxxpy::caster::copy<OesQryTrdRspT>
        );
    c.def("toOesQryCashAssetFilterT", 
        &autocxxpy::caster::copy<OesQryCashAssetFilterT>
        );
    c.def("to_OesQryCashAssetFilter", 
        &autocxxpy::caster::copy<OesQryCashAssetFilterT>
        );
    c.def("toOesCashAssetItemT", 
        &autocxxpy::caster::copy<OesCashAssetItemT>
        );
    c.def("to_OesCashAssetItem", 
        &autocxxpy::caster::copy<OesCashAssetItemT>
        );
    c.def("toOesQryCashAssetReqT", 
        &autocxxpy::caster::copy<OesQryCashAssetReqT>
        );
    c.def("to_OesQryCashAssetReq", 
        &autocxxpy::caster::copy<OesQryCashAssetReqT>
        );
    c.def("toOesQryCashAssetRspT", 
        &autocxxpy::caster::copy<OesQryCashAssetRspT>
        );
    c.def("to_OesQryCashAssetRsp", 
        &autocxxpy::caster::copy<OesQryCashAssetRspT>
        );
    c.def("toOesCounterCashItemT", 
        &autocxxpy::caster::copy<OesCounterCashItemT>
        );
    c.def("to_OesCounterCashItem", 
        &autocxxpy::caster::copy<OesCounterCashItemT>
        );
    c.def("toOesQryCounterCashReqT", 
        &autocxxpy::caster::copy<OesQryCounterCashReqT>
        );
    c.def("to_OesQryCounterCashReq", 
        &autocxxpy::caster::copy<OesQryCounterCashReqT>
        );
    c.def("toOesQryCounterCashRspT", 
        &autocxxpy::caster::copy<OesQryCounterCashRspT>
        );
    c.def("to_OesQryCounterCashRsp", 
        &autocxxpy::caster::copy<OesQryCounterCashRspT>
        );
    c.def("toOesQryStkHoldingFilterT", 
        &autocxxpy::caster::copy<OesQryOptHoldingFilterT>
        );
    c.def("toOesQryOptHoldingFilterT", 
        &autocxxpy::caster::copy<OesQryOptHoldingFilterT>
        );
    c.def("to_OesQryStkHoldingFilter", 
        &autocxxpy::caster::copy<OesQryStkHoldingFilterT>
        );
    c.def("toOesStkHoldingItemT", 
        &autocxxpy::caster::copy<OesStkHoldingItemT>
        );
    c.def("to_OesStkHoldingItem", 
        &autocxxpy::caster::copy<OesStkHoldingItemT>
        );
    c.def("toOesQryStkHoldingReqT", 
        &autocxxpy::caster::copy<OesQryStkHoldingReqT>
        );
    c.def("to_OesQryStkHoldingReq", 
        &autocxxpy::caster::copy<OesQryStkHoldingReqT>
        );
    c.def("toOesQryStkHoldingRspT", 
        &autocxxpy::caster::copy<OesQryStkHoldingRspT>
        );
    c.def("to_OesQryStkHoldingRsp", 
        &autocxxpy::caster::copy<OesQryStkHoldingRspT>
        );
    c.def("toOesOptHoldingItemT", 
        &autocxxpy::caster::copy<OesOptHoldingItemT>
        );
    c.def("to_OesOptHoldingItem", 
        &autocxxpy::caster::copy<OesOptHoldingItemT>
        );
    c.def("toOesQryOptHoldingReqT", 
        &autocxxpy::caster::copy<OesQryOptHoldingReqT>
        );
    c.def("to_OesQryOptHoldingReq", 
        &autocxxpy::caster::copy<OesQryOptHoldingReqT>
        );
    c.def("toOesQryOptHoldingRspT", 
        &autocxxpy::caster::copy<OesQryOptHoldingRspT>
        );
    c.def("to_OesQryHoldRsp", 
        &autocxxpy::caster::copy<OesQryOptHoldingRspT>
        );
    c.def("toOesQryCustFilterT", 
        &autocxxpy::caster::copy<OesQryCustFilterT>
        );
    c.def("to_OesQryCustFilter", 
        &autocxxpy::caster::copy<OesQryCustFilterT>
        );
    c.def("toOesQryCustReqT", 
        &autocxxpy::caster::copy<OesQryCustReqT>
        );
    c.def("to_OesQryCustReq", 
        &autocxxpy::caster::copy<OesQryCustReqT>
        );
    c.def("toOesQryCustRspT", 
        &autocxxpy::caster::copy<OesQryCustRspT>
        );
    c.def("to_OesQryCustRsp", 
        &autocxxpy::caster::copy<OesQryCustRspT>
        );
    c.def("toOesQryInvAcctFilterT", 
        &autocxxpy::caster::copy<OesQryInvAcctFilterT>
        );
    c.def("to_OesQryInvAcctFilter", 
        &autocxxpy::caster::copy<OesQryInvAcctFilterT>
        );
    c.def("toOesInvAcctItemT", 
        &autocxxpy::caster::copy<OesInvAcctItemT>
        );
    c.def("to_OesInvAcctItem", 
        &autocxxpy::caster::copy<OesInvAcctItemT>
        );
    c.def("toOesQryInvAcctReqT", 
        &autocxxpy::caster::copy<OesQryInvAcctReqT>
        );
    c.def("to_OesQryInvAcctReq", 
        &autocxxpy::caster::copy<OesQryInvAcctReqT>
        );
    c.def("toOesQryInvAcctRspT", 
        &autocxxpy::caster::copy<OesQryInvAcctRspT>
        );
    c.def("to_OesQryInvAcctRsp", 
        &autocxxpy::caster::copy<OesQryInvAcctRspT>
        );
    c.def("toOesInvAcctOverviewT", 
        &autocxxpy::caster::copy<OesInvAcctOverviewT>
        );
    c.def("to_OesInvAcctOverview", 
        &autocxxpy::caster::copy<OesInvAcctOverviewT>
        );
    c.def("toOesCashAcctOverviewT", 
        &autocxxpy::caster::copy<OesCashAcctOverviewT>
        );
    c.def("to_OesCashAcctOverview", 
        &autocxxpy::caster::copy<OesCashAcctOverviewT>
        );
    c.def("toOesCustOverviewT", 
        &autocxxpy::caster::copy<OesCustOverviewT>
        );
    c.def("to_OesCustOverview", 
        &autocxxpy::caster::copy<OesCustOverviewT>
        );
    c.def("toOesClientOverviewT", 
        &autocxxpy::caster::copy<OesClientOverviewT>
        );
    c.def("to_OesClientOverview", 
        &autocxxpy::caster::copy<OesClientOverviewT>
        );
    c.def("toOesQryCommissionRateFilterT", 
        &autocxxpy::caster::copy<OesQryCommissionRateFilterT>
        );
    c.def("to_OesQryCommissionRateFilter", 
        &autocxxpy::caster::copy<OesQryCommissionRateFilterT>
        );
    c.def("toOesCommissionRateItemT", 
        &autocxxpy::caster::copy<OesCommissionRateItemT>
        );
    c.def("to_OesCommissionRateItem", 
        &autocxxpy::caster::copy<OesCommissionRateItemT>
        );
    c.def("toOesQryCommissionRateReqT", 
        &autocxxpy::caster::copy<OesQryCommissionRateReqT>
        );
    c.def("to_OesQryCommissionRateReq", 
        &autocxxpy::caster::copy<OesQryCommissionRateReqT>
        );
    c.def("toOesQryCommissionRateRspT", 
        &autocxxpy::caster::copy<OesQryCommissionRateRspT>
        );
    c.def("to_OesQryCommissionRateRsp", 
        &autocxxpy::caster::copy<OesQryCommissionRateRspT>
        );
    c.def("toOesQryFundTransferSerialFilterT", 
        &autocxxpy::caster::copy<OesQryFundTransferSerialFilterT>
        );
    c.def("to_OesQryFundTransferSerialFilter", 
        &autocxxpy::caster::copy<OesQryFundTransferSerialFilterT>
        );
    c.def("toOesQryFundTransferSerialReqT", 
        &autocxxpy::caster::copy<OesQryFundTransferSerialReqT>
        );
    c.def("to_OesQryFundTransferSerialReq", 
        &autocxxpy::caster::copy<OesQryFundTransferSerialReqT>
        );
    c.def("toOesQryFundTransferSerialRspT", 
        &autocxxpy::caster::copy<OesQryFundTransferSerialRspT>
        );
    c.def("to_OesQryFundTransferSerialRsp", 
        &autocxxpy::caster::copy<OesQryFundTransferSerialRspT>
        );
    c.def("toOesQryLotWinningFilterT", 
        &autocxxpy::caster::copy<OesQryLotWinningFilterT>
        );
    c.def("to_OesQryLotWinningFilter", 
        &autocxxpy::caster::copy<OesQryLotWinningFilterT>
        );
    c.def("toOesQryLotWinningReqT", 
        &autocxxpy::caster::copy<OesQryLotWinningReqT>
        );
    c.def("to_OesQryLotWinningReq", 
        &autocxxpy::caster::copy<OesQryLotWinningReqT>
        );
    c.def("toOesQryLotWinningRspT", 
        &autocxxpy::caster::copy<OesQryLotWinningRspT>
        );
    c.def("to_OesQryLotWinningRsp", 
        &autocxxpy::caster::copy<OesQryLotWinningRspT>
        );
    c.def("toOesQryIssueFilterT", 
        &autocxxpy::caster::copy<OesQryIssueFilterT>
        );
    c.def("to_OesQryIssueFilter", 
        &autocxxpy::caster::copy<OesQryIssueFilterT>
        );
    c.def("toOesQryIssueReqT", 
        &autocxxpy::caster::copy<OesQryIssueReqT>
        );
    c.def("to_OesQryIssueReq", 
        &autocxxpy::caster::copy<OesQryIssueReqT>
        );
    c.def("toOesQryIssueRspT", 
        &autocxxpy::caster::copy<OesQryIssueRspT>
        );
    c.def("to_OesQryIssueRsp", 
        &autocxxpy::caster::copy<OesQryIssueRspT>
        );
    c.def("toOesQryStockFilterT", 
        &autocxxpy::caster::copy<OesQryStockFilterT>
        );
    c.def("to_OesQryStockFilter", 
        &autocxxpy::caster::copy<OesQryStockFilterT>
        );
    c.def("toOesQryStockReqT", 
        &autocxxpy::caster::copy<OesQryStockReqT>
        );
    c.def("to_OesQryStockReq", 
        &autocxxpy::caster::copy<OesQryStockReqT>
        );
    c.def("toOesQryStockRspT", 
        &autocxxpy::caster::copy<OesQryStockRspT>
        );
    c.def("to_OesQryStockRsp", 
        &autocxxpy::caster::copy<OesQryStockRspT>
        );
    c.def("toOesQryEtfFilterT", 
        &autocxxpy::caster::copy<OesQryEtfFilterT>
        );
    c.def("to_OesQryEtfFilter", 
        &autocxxpy::caster::copy<OesQryEtfFilterT>
        );
    c.def("toOesQryEtfReqT", 
        &autocxxpy::caster::copy<OesQryEtfReqT>
        );
    c.def("to_OesQryEtfReq", 
        &autocxxpy::caster::copy<OesQryEtfReqT>
        );
    c.def("toOesQryEtfRspT", 
        &autocxxpy::caster::copy<OesQryEtfRspT>
        );
    c.def("to_OesQryEtfRsp", 
        &autocxxpy::caster::copy<OesQryEtfRspT>
        );
    c.def("toOesQryEtfComponentFilterT", 
        &autocxxpy::caster::copy<OesQryEtfComponentFilterT>
        );
    c.def("to_OesQryEtfComponentFilter", 
        &autocxxpy::caster::copy<OesQryEtfComponentFilterT>
        );
    c.def("toOesEtfComponentItemT", 
        &autocxxpy::caster::copy<OesEtfComponentItemT>
        );
    c.def("to_OesEtfComponentItem", 
        &autocxxpy::caster::copy<OesEtfComponentItemT>
        );
    c.def("toOesQryEtfComponentReqT", 
        &autocxxpy::caster::copy<OesQryEtfComponentReqT>
        );
    c.def("to_OesQryEtfComponentReq", 
        &autocxxpy::caster::copy<OesQryEtfComponentReqT>
        );
    c.def("toOesQryEtfComponentRspT", 
        &autocxxpy::caster::copy<OesQryEtfComponentRspT>
        );
    c.def("to_OesQryEtfComponentRsp", 
        &autocxxpy::caster::copy<OesQryEtfComponentRspT>
        );
    c.def("toOesQryOptionFilterT", 
        &autocxxpy::caster::copy<OesQryOptionFilterT>
        );
    c.def("to_OesQryOptionFilter", 
        &autocxxpy::caster::copy<OesQryOptionFilterT>
        );
    c.def("toOesQryOptionReqT", 
        &autocxxpy::caster::copy<OesQryOptionReqT>
        );
    c.def("to_OesQryOptionReq", 
        &autocxxpy::caster::copy<OesQryOptionReqT>
        );
    c.def("toOesQryOptionRspT", 
        &autocxxpy::caster::copy<OesQryOptionRspT>
        );
    c.def("to_OesQryOptionRsp", 
        &autocxxpy::caster::copy<OesQryOptionRspT>
        );
    c.def("toOesQryTradingDayRspT", 
        &autocxxpy::caster::copy<OesQryTradingDayRspT>
        );
    c.def("to_OesQryTradingDayRsp", 
        &autocxxpy::caster::copy<OesQryTradingDayRspT>
        );
    c.def("toOesQryMarketStateFilterT", 
        &autocxxpy::caster::copy<OesQryMarketStateFilterT>
        );
    c.def("to_OesQryMarketStateFilter", 
        &autocxxpy::caster::copy<OesQryMarketStateFilterT>
        );
    c.def("toOesQryMarketStateReqT", 
        &autocxxpy::caster::copy<OesQryMarketStateReqT>
        );
    c.def("to_OesQryMarketStateReq", 
        &autocxxpy::caster::copy<OesQryMarketStateReqT>
        );
    c.def("toOesQryMarketStateRspT", 
        &autocxxpy::caster::copy<OesQryMarketStateRspT>
        );
    c.def("to_OesQryMarketStateRsp", 
        &autocxxpy::caster::copy<OesQryMarketStateRspT>
        );
    c.def("toOesQryReqMsgT", 
        &autocxxpy::caster::copy<OesQryReqMsgT>
        );
    c.def("to_OesQryReqMsg", 
        &autocxxpy::caster::copy<OesQryReqMsgT>
        );
    c.def("toOesQryRspMsgT", 
        &autocxxpy::caster::copy<OesQryRspMsgT>
        );
    c.def("to_OesQryRspMsg", 
        &autocxxpy::caster::copy<OesQryRspMsgT>
        );
    c.def("toOesLogonReqT", 
        &autocxxpy::caster::copy<OesLogonReqT>
        );
    c.def("to_OesLogonReq", 
        &autocxxpy::caster::copy<OesLogonReqT>
        );
    c.def("toOesLogonRspT", 
        &autocxxpy::caster::copy<OesLogonRspT>
        );
    c.def("to_OesLogonRsp", 
        &autocxxpy::caster::copy<OesLogonRspT>
        );
    c.def("toOesReportSynchronizationReqT", 
        &autocxxpy::caster::copy<OesReportSynchronizationReqT>
        );
    c.def("to_OesReportSynchronizationReq", 
        &autocxxpy::caster::copy<OesReportSynchronizationReqT>
        );
    c.def("toOesReportSynchronizationRspT", 
        &autocxxpy::caster::copy<OesReportSynchronizationRspT>
        );
    c.def("to_OesReportSynchronizationRsp", 
        &autocxxpy::caster::copy<OesReportSynchronizationRspT>
        );
    c.def("toOesTestRequestReqT", 
        &autocxxpy::caster::copy<OesTestRequestReqT>
        );
    c.def("to_OesTestRequestReq", 
        &autocxxpy::caster::copy<OesTestRequestReqT>
        );
    c.def("toOesTestRequestRspT", 
        &autocxxpy::caster::copy<OesTestRequestRspT>
        );
    c.def("to_OesTestRequestRsp", 
        &autocxxpy::caster::copy<OesTestRequestRspT>
        );
    c.def("toOesChangePasswordReqT", 
        &autocxxpy::caster::copy<OesChangePasswordReqT>
        );
    c.def("to_OesChangePasswordReq", 
        &autocxxpy::caster::copy<OesChangePasswordReqT>
        );
    c.def("toOesChangePasswordRspT", 
        &autocxxpy::caster::copy<OesChangePasswordRspT>
        );
    c.def("to_OesChangePasswordRsp", 
        &autocxxpy::caster::copy<OesChangePasswordRspT>
        );
    c.def("toOesBatchOrdersHeadT", 
        &autocxxpy::caster::copy<OesBatchOrdersHeadT>
        );
    c.def("to_OesBatchOrdersHead", 
        &autocxxpy::caster::copy<OesBatchOrdersHeadT>
        );
    c.def("toOesBatchOrdersReqT", 
        &autocxxpy::caster::copy<OesBatchOrdersReqT>
        );
    c.def("to_OesBatchOrdersReq", 
        &autocxxpy::caster::copy<OesBatchOrdersReqT>
        );
    c.def("toOesRptMsgHeadT", 
        &autocxxpy::caster::copy<OesRptMsgHeadT>
        );
    c.def("to_OesRptMsgHead", 
        &autocxxpy::caster::copy<OesRptMsgHeadT>
        );
    c.def("toOesRptMsgBodyT", 
        &autocxxpy::caster::copy<OesRptMsgBodyT>
        );
    c.def("to_OesRptMsgBody", 
        &autocxxpy::caster::copy<OesRptMsgBodyT>
        );
    c.def("toOesRptMsgT", 
        &autocxxpy::caster::copy<OesRptMsgT>
        );
    c.def("to_OesRptMsg", 
        &autocxxpy::caster::copy<OesRptMsgT>
        );
    c.def("toOesReqMsgBodyT", 
        &autocxxpy::caster::copy<OesReqMsgBodyT>
        );
    c.def("to_OesReqMsgBody", 
        &autocxxpy::caster::copy<OesReqMsgBodyT>
        );
    c.def("toOesRspMsgBodyT", 
        &autocxxpy::caster::copy<OesRspMsgBodyT>
        );
    c.def("to_OesRspMsgBody", 
        &autocxxpy::caster::copy<OesRspMsgBodyT>
        );
    c.def("toSErrMsgT", 
        &autocxxpy::caster::copy<SErrMsgT>
        );
    c.def("to_SErrMsg", 
        &autocxxpy::caster::copy<SErrMsgT>
        );
    c.def("toSDataBufferT", 
        &autocxxpy::caster::copy<SDataBufferT>
        );
    c.def("to_SDataBuffer", 
        &autocxxpy::caster::copy<SDataBufferT>
        );
    c.def("to_SDataBufferVar", 
        &autocxxpy::caster::copy<_SDataBufferVar>
        );
    c.def("toSSocketUriInfoT", 
        &autocxxpy::caster::copy<SSocketUriInfoT>
        );
    c.def("to_SSocketUriInfo", 
        &autocxxpy::caster::copy<SSocketUriInfoT>
        );
    c.def("toSSocketIpPortInfoT", 
        &autocxxpy::caster::copy<SSocketIpPortInfoT>
        );
    c.def("to_SSocketIpPortInfo", 
        &autocxxpy::caster::copy<SSocketIpPortInfoT>
        );
    c.def("toSSocketChannelInfoT", 
        &autocxxpy::caster::copy<SSocketChannelInfoT>
        );
    c.def("to_SSocketChannelInfo", 
        &autocxxpy::caster::copy<SSocketChannelInfoT>
        );
    c.def("toSSocketOptionConfigT", 
        &autocxxpy::caster::copy<SSocketOptionConfigT>
        );
    c.def("to_SSocketOptionConfig", 
        &autocxxpy::caster::copy<SSocketOptionConfigT>
        );
    c.def("toSGeneralClientChannelT", 
        &autocxxpy::caster::copy<MdsApiSessionInfoT>
        );
    c.def("toMdsApiSessionInfoT", 
        &autocxxpy::caster::copy<MdsApiSessionInfoT>
        );
    c.def("to_SGeneralClientChannel", 
        &autocxxpy::caster::copy<SGeneralClientChannelT>
        );
    c.def("toOesApiSessionInfoT", 
        &autocxxpy::caster::copy<OesApiSessionInfoT>
        );
    c.def("toSGeneralClientChannelGroupT", 
        &autocxxpy::caster::copy<MdsApiChannelGroupT>
        );
    c.def("to_SGeneralClientChannelGroup", 
        &autocxxpy::caster::copy<SGeneralClientChannelGroupT>
        );
    c.def("toOesApiChannelGroupT", 
        &autocxxpy::caster::copy<OesApiChannelGroupT>
        );
    c.def("toMdsApiChannelGroupT", 
        &autocxxpy::caster::copy<MdsApiChannelGroupT>
        );
    c.def("toSGeneralClientAddrInfoT", 
        &autocxxpy::caster::copy<MdsApiAddrInfoT>
        );
    c.def("toMdsApiAddrInfoT", 
        &autocxxpy::caster::copy<MdsApiAddrInfoT>
        );
    c.def("toOesApiAddrInfoT", 
        &autocxxpy::caster::copy<OesApiAddrInfoT>
        );
    c.def("to_SGeneralClientAddrInfo", 
        &autocxxpy::caster::copy<SGeneralClientAddrInfoT>
        );
    c.def("toSGeneralClientRemoteCfgT", 
        &autocxxpy::caster::copy<MdsApiRemoteCfgT>
        );
    c.def("to_SGeneralClientRemoteCfg", 
        &autocxxpy::caster::copy<SGeneralClientRemoteCfgT>
        );
    c.def("toMdsApiRemoteCfgT", 
        &autocxxpy::caster::copy<MdsApiRemoteCfgT>
        );
    c.def("toOesApiRemoteCfgT", 
        &autocxxpy::caster::copy<OesApiRemoteCfgT>
        );
    c.def("toOesApiSubscribeInfoT", 
        &autocxxpy::caster::copy<OesApiSubscribeInfoT>
        );
    c.def("to_OesApiSubscribeInfo", 
        &autocxxpy::caster::copy<OesApiSubscribeInfoT>
        );
    c.def("toOesApiClientCfgT", 
        &autocxxpy::caster::copy<OesApiClientCfgT>
        );
    c.def("to_OesApiClientCfg", 
        &autocxxpy::caster::copy<OesApiClientCfgT>
        );
    c.def("toOesApiClientEnvT", 
        &autocxxpy::caster::copy<OesApiClientEnvT>
        );
    c.def("to_OesApiClientEnv", 
        &autocxxpy::caster::copy<OesApiClientEnvT>
        );
    c.def("toMdsTradingSessionStatusMsgT", 
        &autocxxpy::caster::copy<MdsTradingSessionStatusMsgT>
        );
    c.def("to_MdsTradingSessionStatusMsg", 
        &autocxxpy::caster::copy<MdsTradingSessionStatusMsgT>
        );
    c.def("toMdsSecurityStatusMsgT", 
        &autocxxpy::caster::copy<MdsSecurityStatusMsgT>
        );
    c.def("to_MdsSecurityStatusMsg", 
        &autocxxpy::caster::copy<MdsSecurityStatusMsgT>
        );
    c.def("toMdsPriceLevelEntryT", 
        &autocxxpy::caster::copy<MdsPriceLevelEntryT>
        );
    c.def("to_MdsPriceLevelEntry", 
        &autocxxpy::caster::copy<MdsPriceLevelEntryT>
        );
    c.def("toMdsMktDataSnapshotHeadT", 
        &autocxxpy::caster::copy<MdsMktDataSnapshotHeadT>
        );
    c.def("to_MdsMktDataSnapshotHead", 
        &autocxxpy::caster::copy<MdsMktDataSnapshotHeadT>
        );
    c.def("toMdsIndexSnapshotBodyT", 
        &autocxxpy::caster::copy<MdsIndexSnapshotBodyT>
        );
    c.def("to_MdsIndexSnapshotBody", 
        &autocxxpy::caster::copy<MdsIndexSnapshotBodyT>
        );
    c.def("toMdsStockSnapshotBodyT", 
        &autocxxpy::caster::copy<MdsStockSnapshotBodyT>
        );
    c.def("to_MdsStockSnapshotBody", 
        &autocxxpy::caster::copy<MdsStockSnapshotBodyT>
        );
    c.def("toMdsL1SnapshotBodyT", 
        &autocxxpy::caster::copy<MdsL1SnapshotBodyT>
        );
    c.def("to_MdsL1SnapshotBody", 
        &autocxxpy::caster::copy<MdsL1SnapshotBodyT>
        );
    c.def("toMdsL2StockSnapshotBodyT", 
        &autocxxpy::caster::copy<MdsL2StockSnapshotBodyT>
        );
    c.def("to_MdsL2StockSnapshotBody", 
        &autocxxpy::caster::copy<MdsL2StockSnapshotBodyT>
        );
    c.def("toMdsL2StockSnapshotIncrementalT", 
        &autocxxpy::caster::copy<MdsL2StockSnapshotIncrementalT>
        );
    c.def("to_MdsL2StockSnapshotIncremental", 
        &autocxxpy::caster::copy<MdsL2StockSnapshotIncrementalT>
        );
    c.def("toMdsL2BestOrdersSnapshotBodyT", 
        &autocxxpy::caster::copy<MdsL2BestOrdersSnapshotBodyT>
        );
    c.def("to_MdsL2BestOrdersSnapshotBody", 
        &autocxxpy::caster::copy<MdsL2BestOrdersSnapshotBodyT>
        );
    c.def("toMdsL2BestOrdersSnapshotIncrementalT", 
        &autocxxpy::caster::copy<MdsL2BestOrdersSnapshotIncrementalT>
        );
    c.def("to_MdsL2BestOrdersSnapshotIncremental", 
        &autocxxpy::caster::copy<MdsL2BestOrdersSnapshotIncrementalT>
        );
    c.def("toMdsL2VirtualAuctionPriceT", 
        &autocxxpy::caster::copy<MdsL2VirtualAuctionPriceT>
        );
    c.def("to_MdsL2VirtualAuctionPrice", 
        &autocxxpy::caster::copy<MdsL2VirtualAuctionPriceT>
        );
    c.def("toMdsL2MarketOverviewT", 
        &autocxxpy::caster::copy<MdsL2MarketOverviewT>
        );
    c.def("to_MdsL2MarketOverview", 
        &autocxxpy::caster::copy<MdsL2MarketOverviewT>
        );
    c.def("toMdsL2SnapshotBodyT", 
        &autocxxpy::caster::copy<MdsL2SnapshotBodyT>
        );
    c.def("to_MdsL2SnapshotBody", 
        &autocxxpy::caster::copy<MdsL2SnapshotBodyT>
        );
    c.def("toMdsMktDataSnapshotT", 
        &autocxxpy::caster::copy<MdsMktDataSnapshotT>
        );
    c.def("to_MdsMktDataSnapshot", 
        &autocxxpy::caster::copy<MdsMktDataSnapshotT>
        );
    c.def("toMdsL2TradeT", 
        &autocxxpy::caster::copy<MdsL2TradeT>
        );
    c.def("to_MdsL2Trade", 
        &autocxxpy::caster::copy<MdsL2TradeT>
        );
    c.def("toMdsL2OrderT", 
        &autocxxpy::caster::copy<MdsL2OrderT>
        );
    c.def("to_MdsL2Order", 
        &autocxxpy::caster::copy<MdsL2OrderT>
        );
    c.def("toMdsL2TickLostT", 
        &autocxxpy::caster::copy<MdsL2TickLostT>
        );
    c.def("to_MdsL2TickLost", 
        &autocxxpy::caster::copy<MdsL2TickLostT>
        );
    c.def("toMdsQryMktDataSnapshotReqT", 
        &autocxxpy::caster::copy<MdsQrySecurityStatusReqT>
        );
    c.def("toMdsQrySecurityStatusReqT", 
        &autocxxpy::caster::copy<MdsQrySecurityStatusReqT>
        );
    c.def("to_MdsQryMktDataSnapshotReq", 
        &autocxxpy::caster::copy<MdsQryMktDataSnapshotReqT>
        );
    c.def("toMdsQryTrdSessionStatusReqT", 
        &autocxxpy::caster::copy<MdsQryTrdSessionStatusReqT>
        );
    c.def("to_MdsQryTrdSessionStatusReq", 
        &autocxxpy::caster::copy<MdsQryTrdSessionStatusReqT>
        );
    c.def("toMdsLogonReqT", 
        &autocxxpy::caster::copy<MdsLogonReqT>
        );
    c.def("to_MdsLogonReq", 
        &autocxxpy::caster::copy<MdsLogonReqT>
        );
    c.def("toMdsLogonRspT", 
        &autocxxpy::caster::copy<MdsLogonRspT>
        );
    c.def("to_MdsLogonRsp", 
        &autocxxpy::caster::copy<MdsLogonRspT>
        );
    c.def("toMdsMktDataRequestEntryT", 
        &autocxxpy::caster::copy<MdsMktDataRequestEntryT>
        );
    c.def("to_MdsMktDataRequestEntry", 
        &autocxxpy::caster::copy<MdsMktDataRequestEntryT>
        );
    c.def("toMdsMktDataRequestReqT", 
        &autocxxpy::caster::copy<MdsMktDataRequestReqT>
        );
    c.def("to_MdsMktDataRequestReq", 
        &autocxxpy::caster::copy<MdsMktDataRequestReqT>
        );
    c.def("toMdsMktDataRequestReqBufT", 
        &autocxxpy::caster::copy<MdsApiSubscribeInfoT>
        );
    c.def("toMdsApiSubscribeInfoT", 
        &autocxxpy::caster::copy<MdsApiSubscribeInfoT>
        );
    c.def("to_MdsMktDataRequestReqBuf", 
        &autocxxpy::caster::copy<MdsMktDataRequestReqBufT>
        );
    c.def("toMdsMktDataRequestRspT", 
        &autocxxpy::caster::copy<MdsMktDataRequestRspT>
        );
    c.def("to_MdsMktDataRequestRsp", 
        &autocxxpy::caster::copy<MdsMktDataRequestRspT>
        );
    c.def("toMdsTestRequestReqT", 
        &autocxxpy::caster::copy<MdsTestRequestReqT>
        );
    c.def("to_MdsTestRequestReq", 
        &autocxxpy::caster::copy<MdsTestRequestReqT>
        );
    c.def("toMdsTestRequestRspT", 
        &autocxxpy::caster::copy<MdsTestRequestRspT>
        );
    c.def("to_MdsTestRequestRsp", 
        &autocxxpy::caster::copy<MdsTestRequestRspT>
        );
    c.def("toMdsMktReqMsgBodyT", 
        &autocxxpy::caster::copy<MdsMktReqMsgBodyT>
        );
    c.def("to_MdsMktReqMsgBody", 
        &autocxxpy::caster::copy<MdsMktReqMsgBodyT>
        );
    c.def("toMdsMktRspMsgBodyT", 
        &autocxxpy::caster::copy<MdsMktRspMsgBodyT>
        );
    c.def("to_MdsMktRspMsgBody", 
        &autocxxpy::caster::copy<MdsMktRspMsgBodyT>
        );
    c.def("toMdsUdpPktHeadT", 
        &autocxxpy::caster::copy<MdsUdpPktHeadT>
        );
    c.def("to_MdsUdpPktHead", 
        &autocxxpy::caster::copy<MdsUdpPktHeadT>
        );
    c.def("toMdsApiClientCfgT", 
        &autocxxpy::caster::copy<MdsApiClientCfgT>
        );
    c.def("to_MdsApiClientCfg", 
        &autocxxpy::caster::copy<MdsApiClientCfgT>
        );
    c.def("toMdsApiClientEnvT", 
        &autocxxpy::caster::copy<MdsApiClientEnvT>
        );
    c.def("to_MdsApiClientEnv", 
        &autocxxpy::caster::copy<MdsApiClientEnvT>
        );

}

// begin generated code - combined_class_generator_definitions
// code will appear only when split_in_files is off

// end generated code


void additional_init(pybind11::module &m)
{
    autocxxpy::additional_init<tag_vnoes>::init(m);
}

PYBIND11_MODULE(vnoes, m)
{
    generate_classes(m);
    generate_functions(m);
    generate_constants(m);
    generate_constants_class(m);
    generate_enums(m);
    init_caster(m);

    additional_init(m);

    init_dispatcher(m);
}
