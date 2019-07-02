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


void generate_vnoes(pybind11::module & parent)
{
    generate_class_spk_struct_timespec(parent);
    generate_class_spk_struct_timezone(parent);
    generate_class_spk_struct_iovec(parent);
    generate_class_spk_struct_timeval32(parent);
    generate_class_spk_struct_timeval64(parent);
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
    generate_enum_eOesExchangeId(parent);
    generate_enum_eOesMarketId(parent);
    generate_enum_eOesPlatformId(parent);
    generate_enum_eOesMarketState(parent);
    generate_enum_eOesTrdSessType(parent);
    generate_enum_eOesProductType(parent);
    generate_enum_eOesSecurityType(parent);
    generate_enum_eOesSubSecurityType(parent);
    generate_enum_eOesSecurityLevel(parent);
    generate_enum_eOesSecurityRiskLevel(parent);
    generate_enum_eOesSecuritySuspFlag(parent);
    generate_enum_eOesLotType(parent);
    generate_enum_eOesLotRejReason(parent);
    generate_enum_eOesOrdStatus(parent);
    generate_enum_eOesOrdType(parent);
    generate_enum_eOesOrdTypeSh(parent);
    generate_enum_eOesOrdTypeSz(parent);
    generate_enum_eOesBuySellType(parent);
    generate_enum_eOesOrdDir(parent);
    generate_enum_eOesEtfTrdCnfmType(parent);
    generate_enum_eOesEtfSubFlag(parent);
    generate_enum_eOesExecType(parent);
    generate_enum_eOesCurrType(parent);
    generate_enum_eOesFeeType(parent);
    generate_enum_eOesCalcFeeMode(parent);
    generate_enum_eOesFundTrsfDirect(parent);
    generate_enum_eOesFundTrsfType(parent);
    generate_enum_eOesFundTrsfStatus(parent);
    generate_enum_eOesAcctType(parent);
    generate_enum_eOesCashType(parent);
    generate_enum_eOesAcctStatus(parent);
    generate_enum_eOesTradingPermission(parent);
    generate_enum_eOesTradingLimit(parent);
    generate_enum_eOesQualificationClass(parent);
    generate_enum_eOesInvestorClass(parent);
    generate_enum_eOesCustType(parent);
    generate_enum_eOesOwnerType(parent);
    generate_enum_eOesClientType(parent);
    generate_enum_eOesClientStatus(parent);
    generate_enum_eOesOptContractType(parent);
    generate_enum_eOesOptInvLevel(parent);
    generate_enum_eOpenFlagType(parent);
    generate_enum_eOesOptionOpenFlag(parent);
    generate_enum_eOesPositionEff(parent);
    generate_enum_eOesOptionType(parent);
    generate_enum_eSMsgProtocolType(parent);
    generate_enum_eSMsgFlag(parent);
    generate_enum_eOesMsgType(parent);
    generate_enum_eOesSubscribeReportType(parent);
    generate_enum_eOesProtocolHintsType(parent);
    generate_enum_eSSocketProtocolType(parent);
    generate_enum_eGeneralClientClusterType(parent);
    generate_enum_eGeneralClientEncryptType(parent);
    generate_enum_eOesApiChannelType(parent);
    generate_enum_eMdsExchangeId(parent);
    generate_enum_eMdsMsgSource(parent);
    generate_enum_eMdsMdProductType(parent);
    generate_enum_eMdsMdStreamType(parent);
    generate_enum_eMdsMdLevel(parent);
    generate_enum_eMdsL2PriceLevelOperator(parent);
    generate_enum_eMdsL2TradeExecType(parent);
    generate_enum_eMdsL2TradeBSFlag(parent);
    generate_enum_eMdsL2OrderSideT(parent);
    generate_enum_eMdsL2OrderType(parent);
    generate_enum_eMdsClientType(parent);
    generate_enum_eMdsClientStatus(parent);
    generate_enum_eMdsMsgType(parent);
    generate_enum_eMdsSubscribeMode(parent);
    generate_enum_eMdsMktSubscribeFlag(parent);
    generate_enum_eMdsSubscribedTickType(parent);
    generate_enum_eMdsSubscribedTickExpireType(parent);
    generate_enum_eMdsSubscribeDataType(parent);
    generate_enum_eMdsSubscribedChannelNo(parent);
    generate_enum_eMdsProtocolHintsType(parent);
    generate_enum_eMdsApiChannelType(parent);
    parent.def("__SPlatform_GetErrno",
        &__SPlatform_GetErrno,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_GetNegErrno",
        &__SPlatform_GetNegErrno,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_SetErrno",
        &__SPlatform_SetErrno,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEagain",
        &__SPlatform_IsErrEagain,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEconnaborted",
        &__SPlatform_IsErrEconnaborted,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEtimeout",
        &__SPlatform_IsErrEtimeout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEpipe",
        &__SPlatform_IsErrEpipe,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEintr",
        &__SPlatform_IsErrEintr,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsErrEbadmsg",
        &__SPlatform_IsErrEbadmsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEagain",
        &__SPlatform_IsNegEagain,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEconnaborted",
        &__SPlatform_IsNegEconnaborted,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEtimeout",
        &__SPlatform_IsNegEtimeout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEpipe",
        &__SPlatform_IsNegEpipe,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEintr",
        &__SPlatform_IsNegEintr,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("__SPlatform_IsNegEbadmsg",
        &__SPlatform_IsNegEbadmsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendOrderReq",
        &OesApi_SendOrderReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendOrderCancelReq",
        &OesApi_SendOrderCancelReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendBatchOrdersReq2",
        &OesApi_SendBatchOrdersReq2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendFundTransferReq",
        &OesApi_SendFundTransferReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendChangePasswordReq",
        &OesApi_SendChangePasswordReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_WaitReportMsg",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_WaitReportMsg
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_RecvReportMsg",
        &OesApi_RecvReportMsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetApiVersion",
        &OesApi_GetApiVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetTradingDay",
        &OesApi_GetTradingDay,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetClientOverview",
        &OesApi_GetClientOverview,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleOrder",
        &OesApi_QuerySingleOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleCashAsset",
        &OesApi_QuerySingleCashAsset,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleStkHolding",
        &OesApi_QuerySingleStkHolding,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QuerySingleOptHolding",
        &OesApi_QuerySingleOptHolding,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOrder",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryOrder
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryTrade",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryTrade
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCashAsset",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryCashAsset
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryStkHolding",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryStkHolding
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOptHolding",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryOptHolding
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryLotWinning",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryLotWinning
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCustInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryCustInfo
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryInvAcct",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryInvAcct
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCommissionRate",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryCommissionRate
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryFundTransferSerial",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryFundTransferSerial
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryIssue",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryIssue
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryStock",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryStock
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryEtf",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryEtf
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryEtfComponent",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryEtfComponent
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOption",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryOption
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryMarketState",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_QueryMarketState
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCounterCash",
        &OesApi_QueryCounterCash,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_Logon",
        &OesApi_Logon,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_LogonReplicaSet",
        &OesApi_LogonReplicaSet,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_LogonPeerNodes",
        &OesApi_LogonPeerNodes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendReportSynchronization",
        &OesApi_SendReportSynchronization,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SendHeartbeat",
        &OesApi_SendHeartbeat,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestOrdChannel",
        &OesApi_TestOrdChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestOrdChannel2",
        &OesApi_TestOrdChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestRptChannel",
        &OesApi_TestRptChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_TestRptChannel2",
        &OesApi_TestRptChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_Logout",
        &OesApi_Logout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_Destory",
        &OesApi_Destory,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAll",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_InitAll
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::inout_argument_transform, 8>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAllByConvention",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_InitAllByConvention
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::inout_argument_transform, 3>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAllByCfgStruct",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_InitAllByCfgStruct
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::inout_argument_transform, 3>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_LogoutAll",
        &OesApi_LogoutAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_DestoryAll",
        &OesApi_DestoryAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitLogger",
        &OesApi_InitLogger,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ResetThreadLoggerName",
        &OesApi_ResetThreadLoggerName,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitOrdChannel",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_InitOrdChannel
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::inout_argument_transform, 4>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitOrdChannel2",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_InitOrdChannel2
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::inout_argument_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitRptChannel",
        &OesApi_InitRptChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitRptChannel2",
        &OesApi_InitRptChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitQryChannel",
        &OesApi_InitQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitQryChannel2",
        &OesApi_InitQryChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ParseAddrListString",
        &OesApi_ParseAddrListString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ParseConfigFromFile",
        &OesApi_ParseConfigFromFile,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ParseAllConfig",
        &OesApi_ParseAllConfig,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitChannelGroup",
        &OesApi_InitChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_DestoryChannelGroup",
        &OesApi_DestoryChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_AddToChannelGroup",
        &OesApi_AddToChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_DeleteFromChannelGroup",
        &OesApi_DeleteFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetFromChannelGroup",
        &OesApi_GetFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetFromChannelGroupBySocket",
        &OesApi_GetFromChannelGroupBySocket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_ForeachInChannelGroup",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &OesApi_ForeachInChannelGroup
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadUsername",
        &OesApi_SetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetThreadUsername",
        &OesApi_GetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadPassword",
        &OesApi_SetThreadPassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadEnvId",
        &OesApi_SetThreadEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetThreadEnvId",
        &OesApi_GetThreadEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetThreadSubscribeEnvId",
        &OesApi_SetThreadSubscribeEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetThreadSubscribeEnvId",
        &OesApi_GetThreadSubscribeEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedIpAndMac",
        &OesApi_SetCustomizedIpAndMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedIp",
        &OesApi_SetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedMac",
        &OesApi_SetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetCustomizedIp",
        &OesApi_GetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetCustomizedMac",
        &OesApi_GetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetCustomizedDriverId",
        &OesApi_SetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetCustomizedDriverId",
        &OesApi_GetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetClEnvId",
        &OesApi_GetClEnvId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetLastRecvTime",
        &OesApi_GetLastRecvTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetLastSendTime",
        &OesApi_GetLastSendTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_HasMoreCachedData",
        &OesApi_HasMoreCachedData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidOrdChannel",
        &OesApi_IsValidOrdChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidRptChannel",
        &OesApi_IsValidRptChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidQryChannel",
        &OesApi_IsValidQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_IsValidChannelGroup",
        &OesApi_IsValidChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetLastError",
        &OesApi_GetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_SetLastError",
        &OesApi_SetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetErrorMsg",
        &OesApi_GetErrorMsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_GetErrorMsg2",
        &OesApi_GetErrorMsg2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesHelper_ExtractOrdReportFromTrd",
        &OesHelper_ExtractOrdReportFromTrd,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_Logon",
        &MdsApi_Logon,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_LogonReplicaSet",
        &MdsApi_LogonReplicaSet,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_LogonPeerNodes",
        &MdsApi_LogonPeerNodes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SyncSubscribeOnLogon",
        &MdsApi_SyncSubscribeOnLogon,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeMarketData",
        &MdsApi_SubscribeMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByString",
        &MdsApi_SubscribeByString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByString2",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_SubscribeByString2
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByStringAndPrefixes",
        &MdsApi_SubscribeByStringAndPrefixes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SubscribeByStringAndPrefixes2",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_SubscribeByStringAndPrefixes2
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SendHeartbeat",
        &MdsApi_SendHeartbeat,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SendTestRequest",
        &MdsApi_SendTestRequest,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_Logout",
        &MdsApi_Logout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_Destory",
        &MdsApi_Destory,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_WaitOnMsg",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_WaitOnMsg
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_WaitOnMsgCompressible",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_WaitOnMsgCompressible
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetApiVersion",
        &MdsApi_GetApiVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QueryMktDataSnapshot",
        &MdsApi_QueryMktDataSnapshot,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QuerySecurityStatus",
        &MdsApi_QuerySecurityStatus,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QueryTrdSessionStatus",
        &MdsApi_QueryTrdSessionStatus,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QueryStockStaticInfo",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_QueryStockStaticInfo
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QuerySnapshotList",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_QuerySnapshotList
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 4>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_QuerySnapshotList2",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_QuerySnapshotList2
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 4>,
                autocxxpy::indexed_transform_holder<autocxxpy::string_array_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SendChangePasswordReq",
        &MdsApi_SendChangePasswordReq,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ConnectToUdpMcast",
        &MdsApi_ConnectToUdpMcast,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_WaitOnUdpMsg",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_WaitOnUdpMsg
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 2>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitAll",
        &MdsApi_InitAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitAllByConvention",
        &MdsApi_InitAllByConvention,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitAllByCfgStruct",
        &MdsApi_InitAllByCfgStruct,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_LogoutAll",
        &MdsApi_LogoutAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DestoryAll",
        &MdsApi_DestoryAll,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitLogger",
        &MdsApi_InitLogger,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ResetThreadLoggerName",
        &MdsApi_ResetThreadLoggerName,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitTcpChannel",
        &MdsApi_InitTcpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitTcpChannel2",
        &MdsApi_InitTcpChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitQryChannel",
        &MdsApi_InitQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitQryChannel2",
        &MdsApi_InitQryChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitUdpChannel",
        &MdsApi_InitUdpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitUdpChannel2",
        &MdsApi_InitUdpChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseAddrListString",
        &MdsApi_ParseAddrListString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseConfigFromFile",
        &MdsApi_ParseConfigFromFile,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseAllConfig",
        &MdsApi_ParseAllConfig,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitChannelGroup",
        &MdsApi_InitChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DestoryChannelGroup",
        &MdsApi_DestoryChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_AddToChannelGroup",
        &MdsApi_AddToChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DeleteFromChannelGroup",
        &MdsApi_DeleteFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetFromChannelGroup",
        &MdsApi_GetFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetFromChannelGroupBySocket",
        &MdsApi_GetFromChannelGroupBySocket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ForeachInChannelGroup",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &MdsApi_ForeachInChannelGroup
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::c_function_callback_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetThreadUsername",
        &MdsApi_SetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetThreadUsername",
        &MdsApi_GetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetThreadPassword",
        &MdsApi_SetThreadPassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedIp",
        &MdsApi_SetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedMac",
        &MdsApi_SetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedIp",
        &MdsApi_GetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedMac",
        &MdsApi_GetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedDriverId",
        &MdsApi_SetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedDriverId",
        &MdsApi_GetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastRecvTime",
        &MdsApi_GetLastRecvTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastSendTime",
        &MdsApi_GetLastSendTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_HasMoreCachedData",
        &MdsApi_HasMoreCachedData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidTcpChannel",
        &MdsApi_IsValidTcpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidQryChannel",
        &MdsApi_IsValidQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidUdpChannel",
        &MdsApi_IsValidUdpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidChannelGroup",
        &MdsApi_IsValidChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastError",
        &MdsApi_GetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetLastError",
        &MdsApi_SetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetErrorMsg",
        &MdsApi_GetErrorMsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetErrorMsg2",
        &MdsApi_GetErrorMsg2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetTickTypeOnSubscribeByString",
        &MdsHelper_SetTickTypeOnSubscribeByString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_ClearSubscribeRequestEntries",
        &MdsHelper_ClearSubscribeRequestEntries,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestMode",
        &MdsHelper_SetSubscribeRequestMode,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestTickType",
        &MdsHelper_SetSubscribeRequestTickType,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestDataTypes",
        &MdsHelper_SetSubscribeRequestDataTypes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestSubFlag",
        &MdsHelper_SetSubscribeRequestSubFlag,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_AddSubscribeRequestEntry",
        &MdsHelper_AddSubscribeRequestEntry,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.attr("OES_APPL_VER_ID") = OES_APPL_VER_ID;
    parent.attr("OES_MIN_APPL_VER_ID") = OES_MIN_APPL_VER_ID;
    parent.attr("OESAPI_CFG_DEFAULT_SECTION") = OESAPI_CFG_DEFAULT_SECTION;
    parent.attr("OESAPI_CFG_DEFAULT_SECTION_LOGGER") = OESAPI_CFG_DEFAULT_SECTION_LOGGER;
    parent.attr("OESAPI_CFG_DEFAULT_KEY_ORD_ADDR") = OESAPI_CFG_DEFAULT_KEY_ORD_ADDR;
    parent.attr("OESAPI_CFG_DEFAULT_KEY_RPT_ADDR") = OESAPI_CFG_DEFAULT_KEY_RPT_ADDR;
    parent.attr("OESAPI_CFG_DEFAULT_KEY_QRY_ADDR") = OESAPI_CFG_DEFAULT_KEY_QRY_ADDR;
    parent.attr("OESAPI_DEFAULT_STRING_DELIM") = OESAPI_DEFAULT_STRING_DELIM;
    parent.attr("MDS_APPL_VER_ID") = MDS_APPL_VER_ID;
    parent.attr("MDS_MIN_APPL_VER_ID") = MDS_MIN_APPL_VER_ID;
    parent.attr("MDSAPI_CFG_DEFAULT_SECTION") = MDSAPI_CFG_DEFAULT_SECTION;
    parent.attr("MDSAPI_CFG_DEFAULT_SECTION_LOGGER") = MDSAPI_CFG_DEFAULT_SECTION_LOGGER;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR") = MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR") = MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE;
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER;
    parent.attr("MDSAPI_DEFAULT_STRING_DELIM") = MDSAPI_DEFAULT_STRING_DELIM;
    module_vnoes::cross.record_assign(parent, "STimeval32T", "STimeval32T", "::_spk_struct_timeval32");
    module_vnoes::cross.record_assign(parent, "STimeval64T", "STimeval64T", "::_spk_struct_timeval64");
    module_vnoes::cross.record_assign(parent, "eOesExchangeIdT", "eOesExchangeIdT", "::_eOesExchangeId");
    module_vnoes::cross.record_assign(parent, "eOesMarketIdT", "eOesMarketIdT", "::_eOesMarketId");
    module_vnoes::cross.record_assign(parent, "eOesPlatformIdT", "eOesPlatformIdT", "::_eOesPlatformId");
    module_vnoes::cross.record_assign(parent, "eOesMarketStateT", "eOesMarketStateT", "::_eOesMarketState");
    module_vnoes::cross.record_assign(parent, "eOesTrdSessTypeT", "eOesTrdSessTypeT", "::_eOesTrdSessType");
    module_vnoes::cross.record_assign(parent, "eOesProductTypeT", "eOesProductTypeT", "::_eOesProductType");
    module_vnoes::cross.record_assign(parent, "eOesSecurityTypeT", "eOesSecurityTypeT", "::_eOesSecurityType");
    module_vnoes::cross.record_assign(parent, "eOesSubSecurityTypeT", "eOesSubSecurityTypeT", "::_eOesSubSecurityType");
    module_vnoes::cross.record_assign(parent, "eOesSecurityLevelT", "eOesSecurityLevelT", "::_eOesSecurityLevel");
    module_vnoes::cross.record_assign(parent, "eOesSecurityRiskLevelT", "eOesSecurityRiskLevelT", "::_eOesSecurityRiskLevel");
    module_vnoes::cross.record_assign(parent, "eOesSecuritySuspFlagT", "eOesSecuritySuspFlagT", "::_eOesSecuritySuspFlag");
    module_vnoes::cross.record_assign(parent, "eOesLotTypeT", "eOesLotTypeT", "::_eOesLotType");
    module_vnoes::cross.record_assign(parent, "eOesLotRejReasonT", "eOesLotRejReasonT", "::_eOesLotRejReason");
    module_vnoes::cross.record_assign(parent, "eOesOrdStatusT", "eOesOrdStatusT", "::_eOesOrdStatus");
    module_vnoes::cross.record_assign(parent, "eOesOrdTypeT", "eOesOrdTypeT", "::_eOesOrdType");
    module_vnoes::cross.record_assign(parent, "eOesOrdTypeShT", "eOesOrdTypeShT", "::_eOesOrdTypeSh");
    module_vnoes::cross.record_assign(parent, "eOesOrdTypeSzT", "eOesOrdTypeSzT", "::_eOesOrdTypeSz");
    module_vnoes::cross.record_assign(parent, "eOesBuySellTypeT", "eOesBuySellTypeT", "::_eOesBuySellType");
    module_vnoes::cross.record_assign(parent, "eOesOrdDirT", "eOesOrdDirT", "::_eOesOrdDir");
    module_vnoes::cross.record_assign(parent, "eOesEtfTrdCnfmTypeT", "eOesEtfTrdCnfmTypeT", "::_eOesEtfTrdCnfmType");
    module_vnoes::cross.record_assign(parent, "eOesEtfSubFlagT", "eOesEtfSubFlagT", "::_eOesEtfSubFlag");
    module_vnoes::cross.record_assign(parent, "eOesExecTypeT", "eOesExecTypeT", "::_eOesExecType");
    module_vnoes::cross.record_assign(parent, "eOesCurrTypeT", "eOesCurrTypeT", "::_eOesCurrType");
    module_vnoes::cross.record_assign(parent, "eOesFeeTypeT", "eOesFeeTypeT", "::_eOesFeeType");
    module_vnoes::cross.record_assign(parent, "eOesCalcFeeModeT", "eOesCalcFeeModeT", "::_eOesCalcFeeMode");
    module_vnoes::cross.record_assign(parent, "eOesFundTrsfDirectT", "eOesFundTrsfDirectT", "::_eOesFundTrsfDirect");
    module_vnoes::cross.record_assign(parent, "eOesFundTrsfTypeT", "eOesFundTrsfTypeT", "::_eOesFundTrsfType");
    module_vnoes::cross.record_assign(parent, "eOesFundTrsfStatusT", "eOesFundTrsfStatusT", "::_eOesFundTrsfStatus");
    module_vnoes::cross.record_assign(parent, "eOesAcctTypeT", "eOesAcctTypeT", "::_eOesAcctType");
    module_vnoes::cross.record_assign(parent, "eOesCashTypeT", "eOesCashTypeT", "::_eOesCashType");
    module_vnoes::cross.record_assign(parent, "eOesAcctStatusT", "eOesAcctStatusT", "::_eOesAcctStatus");
    module_vnoes::cross.record_assign(parent, "eOesTradingPermissionT", "eOesTradingPermissionT", "::_eOesTradingPermission");
    module_vnoes::cross.record_assign(parent, "eOesTradingLimitT", "eOesTradingLimitT", "::_eOesTradingLimit");
    module_vnoes::cross.record_assign(parent, "eOesQualificationClassT", "eOesQualificationClassT", "::_eOesQualificationClass");
    module_vnoes::cross.record_assign(parent, "eOesInvestorClassT", "eOesInvestorClassT", "::_eOesInvestorClass");
    module_vnoes::cross.record_assign(parent, "eOesCustTypeT", "eOesCustTypeT", "::_eOesCustType");
    module_vnoes::cross.record_assign(parent, "eOesOwnerTypeT", "eOesOwnerTypeT", "::_eOesOwnerType");
    module_vnoes::cross.record_assign(parent, "eOesClientTypeT", "eOesClientTypeT", "::_eOesClientType");
    module_vnoes::cross.record_assign(parent, "eOesClientStatusT", "eOesClientStatusT", "::_eOesClientStatus");
    module_vnoes::cross.record_assign(parent, "eOesOptContractTypeT", "eOesOptContractTypeT", "::_eOesOptContractType");
    module_vnoes::cross.record_assign(parent, "eOesOptInvLevelT", "eOesOptInvLevelT", "::_eOesOptInvLevel");
    module_vnoes::cross.record_assign(parent, "eOpenFlagTypeT", "eOpenFlagTypeT", "::_eOpenFlagType");
    module_vnoes::cross.record_assign(parent, "eOesOptionOpenFlagT", "eOesOptionOpenFlagT", "::_eOesOptionOpenFlag");
    module_vnoes::cross.record_assign(parent, "eOesPositionEffT", "eOesPositionEffT", "::_eOesPositionEff");
    module_vnoes::cross.record_assign(parent, "eOesOptionTypeT", "eOesOptionTypeT", "::_eOesOptionType");
    module_vnoes::cross.record_assign(parent, "OesOrdReqT", "OesOrdReqT", "::_OesOrdReq");
    module_vnoes::cross.record_assign(parent, "OesOrdCancelReqT", "OesOrdCancelReqT", "::_OesOrdCancelReq");
    module_vnoes::cross.record_assign(parent, "OesOrdRejectT", "OesOrdRejectT", "::_OesOrdReject");
    module_vnoes::cross.record_assign(parent, "OesOrdCnfmT", "OesOrdCnfmT", "::_OesOrdCnfm");
    module_vnoes::cross.record_assign(parent, "OesTrdBaseInfoT", "OesTrdBaseInfoT", "::_OesTrdBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesTrdCnfmT", "OesTrdCnfmT", "::_OesTrdCnfm");
    module_vnoes::cross.record_assign(parent, "OesLotWinningBaseInfoT", "OesLotWinningBaseInfoT", "::_OesLotWinningBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesFundTrsfBaseInfoT", "OesFundTrsfBaseInfoT", "::_OesFundTrsfBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesFundTrsfReqT", "OesFundTrsfReqT", "::_OesFundTrsfReq");
    module_vnoes::cross.record_assign(parent, "OesFundTrsfRejectT", "OesFundTrsfRejectT", "::_OesFundTrsfReject");
    module_vnoes::cross.record_assign(parent, "OesFundTrsfReportT", "OesFundTrsfReportT", "::_OesFundTrsfReport");
    module_vnoes::cross.record_assign(parent, "OesIssueBaseInfoT", "OesIssueBaseInfoT", "::_OesIssueBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesPriceLimitT", "OesPriceLimitT", "::_OesPriceLimit");
    module_vnoes::cross.record_assign(parent, "OesStockBaseInfoT", "OesStockBaseInfoT", "::_OesStockBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesEtfBaseInfoT", "OesEtfBaseInfoT", "::_OesEtfBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesEtfComponentBaseInfoT", "OesEtfComponentBaseInfoT", "::_OesEtfComponentBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesOptionBaseInfoT", "OesOptionBaseInfoT", "::_OesOptionBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesCashAssetBaseInfoT", "OesCashAssetBaseInfoT", "::_OesCashAssetBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesCustBaseInfoT", "OesCustBaseInfoT", "::_OesCustBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesInvAcctBaseInfoT", "OesInvAcctBaseInfoT", "::_OesInvAcctBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesStkHoldingBaseInfoT", "OesStkHoldingBaseInfoT", "::_OesStkHoldingBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesOptHoldingBaseInfoT", "OesOptHoldingBaseInfoT", "::_OesOptHoldingBaseInfo");
    module_vnoes::cross.record_assign(parent, "OesMarketStateInfoT", "OesMarketStateInfoT", "::_OesMarketStateInfo");
    module_vnoes::cross.record_assign(parent, "OesTradingPermissionEntryT", "OesTradingPermissionEntryT", "::_OesTradingPermissionEntry");
    module_vnoes::cross.record_assign(parent, "eSMsgProtocolTypeT", "eSMsgProtocolTypeT", "::_eSMsgProtocolType");
    module_vnoes::cross.record_assign(parent, "eSMsgFlagT", "eSMsgFlagT", "::_eSMsgFlag");
    module_vnoes::cross.record_assign(parent, "SMsgHeadT", "SMsgHeadT", "::_SMsgHead");
    module_vnoes::cross.record_assign(parent, "OesQryCursorT", "OesQryCursorT", "::_OesQryCursor");
    module_vnoes::cross.record_assign(parent, "OesQryReqHeadT", "OesQryReqHeadT", "::_OesQryReqHead");
    module_vnoes::cross.record_assign(parent, "OesQryRspHeadT", "OesQryRspHeadT", "::_OesQryRspHead");
    module_vnoes::cross.record_assign(parent, "OesQryOrdFilterT", "OesQryOrdFilterT", "::_OesQryOrdFilter");
    module_vnoes::cross.record_assign(parent, "OesQryOrdReqT", "OesQryOrdReqT", "::_OesQryOrdReq");
    module_vnoes::cross.record_assign(parent, "OesQryOrdRspT", "OesQryOrdRspT", "::_OesQryOrdRsp");
    module_vnoes::cross.record_assign(parent, "OesQryTrdFilterT", "OesQryTrdFilterT", "::_OesQryTrdFilter");
    module_vnoes::cross.record_assign(parent, "OesQryTrdReqT", "OesQryTrdReqT", "::_OesQryTrdReq");
    module_vnoes::cross.record_assign(parent, "OesQryTrdRspT", "OesQryTrdRspT", "::_OesQryTrdRsp");
    module_vnoes::cross.record_assign(parent, "OesQryCashAssetFilterT", "OesQryCashAssetFilterT", "::_OesQryCashAssetFilter");
    module_vnoes::cross.record_assign(parent, "OesCashAssetItemT", "OesCashAssetItemT", "::_OesCashAssetItem");
    module_vnoes::cross.record_assign(parent, "OesQryCashAssetReqT", "OesQryCashAssetReqT", "::_OesQryCashAssetReq");
    module_vnoes::cross.record_assign(parent, "OesQryCashAssetRspT", "OesQryCashAssetRspT", "::_OesQryCashAssetRsp");
    module_vnoes::cross.record_assign(parent, "OesCounterCashItemT", "OesCounterCashItemT", "::_OesCounterCashItem");
    module_vnoes::cross.record_assign(parent, "OesQryCounterCashReqT", "OesQryCounterCashReqT", "::_OesQryCounterCashReq");
    module_vnoes::cross.record_assign(parent, "OesQryCounterCashRspT", "OesQryCounterCashRspT", "::_OesQryCounterCashRsp");
    module_vnoes::cross.record_assign(parent, "OesQryStkHoldingFilterT", "OesQryStkHoldingFilterT", "::_OesQryStkHoldingFilter");
    module_vnoes::cross.record_assign(parent, "OesStkHoldingItemT", "OesStkHoldingItemT", "::_OesStkHoldingItem");
    module_vnoes::cross.record_assign(parent, "OesQryStkHoldingReqT", "OesQryStkHoldingReqT", "::_OesQryStkHoldingReq");
    module_vnoes::cross.record_assign(parent, "OesQryStkHoldingRspT", "OesQryStkHoldingRspT", "::_OesQryStkHoldingRsp");
    module_vnoes::cross.record_assign(parent, "OesOptHoldingItemT", "OesOptHoldingItemT", "::_OesOptHoldingItem");
    module_vnoes::cross.record_assign(parent, "OesQryOptHoldingReqT", "OesQryOptHoldingReqT", "::_OesQryOptHoldingReq");
    module_vnoes::cross.record_assign(parent, "OesQryOptHoldingRspT", "OesQryOptHoldingRspT", "::_OesQryHoldRsp");
    module_vnoes::cross.record_assign(parent, "OesQryCustFilterT", "OesQryCustFilterT", "::_OesQryCustFilter");
    module_vnoes::cross.record_assign(parent, "OesQryCustReqT", "OesQryCustReqT", "::_OesQryCustReq");
    module_vnoes::cross.record_assign(parent, "OesQryCustRspT", "OesQryCustRspT", "::_OesQryCustRsp");
    module_vnoes::cross.record_assign(parent, "OesQryInvAcctFilterT", "OesQryInvAcctFilterT", "::_OesQryInvAcctFilter");
    module_vnoes::cross.record_assign(parent, "OesInvAcctItemT", "OesInvAcctItemT", "::_OesInvAcctItem");
    module_vnoes::cross.record_assign(parent, "OesQryInvAcctReqT", "OesQryInvAcctReqT", "::_OesQryInvAcctReq");
    module_vnoes::cross.record_assign(parent, "OesQryInvAcctRspT", "OesQryInvAcctRspT", "::_OesQryInvAcctRsp");
    module_vnoes::cross.record_assign(parent, "OesInvAcctOverviewT", "OesInvAcctOverviewT", "::_OesInvAcctOverview");
    module_vnoes::cross.record_assign(parent, "OesCashAcctOverviewT", "OesCashAcctOverviewT", "::_OesCashAcctOverview");
    module_vnoes::cross.record_assign(parent, "OesCustOverviewT", "OesCustOverviewT", "::_OesCustOverview");
    module_vnoes::cross.record_assign(parent, "OesClientOverviewT", "OesClientOverviewT", "::_OesClientOverview");
    module_vnoes::cross.record_assign(parent, "OesQryCommissionRateFilterT", "OesQryCommissionRateFilterT", "::_OesQryCommissionRateFilter");
    module_vnoes::cross.record_assign(parent, "OesCommissionRateItemT", "OesCommissionRateItemT", "::_OesCommissionRateItem");
    module_vnoes::cross.record_assign(parent, "OesQryCommissionRateReqT", "OesQryCommissionRateReqT", "::_OesQryCommissionRateReq");
    module_vnoes::cross.record_assign(parent, "OesQryCommissionRateRspT", "OesQryCommissionRateRspT", "::_OesQryCommissionRateRsp");
    module_vnoes::cross.record_assign(parent, "OesQryFundTransferSerialFilterT", "OesQryFundTransferSerialFilterT", "::_OesQryFundTransferSerialFilter");
    module_vnoes::cross.record_assign(parent, "OesQryFundTransferSerialReqT", "OesQryFundTransferSerialReqT", "::_OesQryFundTransferSerialReq");
    module_vnoes::cross.record_assign(parent, "OesQryFundTransferSerialRspT", "OesQryFundTransferSerialRspT", "::_OesQryFundTransferSerialRsp");
    module_vnoes::cross.record_assign(parent, "OesQryLotWinningFilterT", "OesQryLotWinningFilterT", "::_OesQryLotWinningFilter");
    module_vnoes::cross.record_assign(parent, "OesQryLotWinningReqT", "OesQryLotWinningReqT", "::_OesQryLotWinningReq");
    module_vnoes::cross.record_assign(parent, "OesQryLotWinningRspT", "OesQryLotWinningRspT", "::_OesQryLotWinningRsp");
    module_vnoes::cross.record_assign(parent, "OesQryIssueFilterT", "OesQryIssueFilterT", "::_OesQryIssueFilter");
    module_vnoes::cross.record_assign(parent, "OesQryIssueReqT", "OesQryIssueReqT", "::_OesQryIssueReq");
    module_vnoes::cross.record_assign(parent, "OesQryIssueRspT", "OesQryIssueRspT", "::_OesQryIssueRsp");
    module_vnoes::cross.record_assign(parent, "OesQryStockFilterT", "OesQryStockFilterT", "::_OesQryStockFilter");
    module_vnoes::cross.record_assign(parent, "OesQryStockReqT", "OesQryStockReqT", "::_OesQryStockReq");
    module_vnoes::cross.record_assign(parent, "OesQryStockRspT", "OesQryStockRspT", "::_OesQryStockRsp");
    module_vnoes::cross.record_assign(parent, "OesQryEtfFilterT", "OesQryEtfFilterT", "::_OesQryEtfFilter");
    module_vnoes::cross.record_assign(parent, "OesQryEtfReqT", "OesQryEtfReqT", "::_OesQryEtfReq");
    module_vnoes::cross.record_assign(parent, "OesQryEtfRspT", "OesQryEtfRspT", "::_OesQryEtfRsp");
    module_vnoes::cross.record_assign(parent, "OesQryEtfComponentFilterT", "OesQryEtfComponentFilterT", "::_OesQryEtfComponentFilter");
    module_vnoes::cross.record_assign(parent, "OesEtfComponentItemT", "OesEtfComponentItemT", "::_OesEtfComponentItem");
    module_vnoes::cross.record_assign(parent, "OesQryEtfComponentReqT", "OesQryEtfComponentReqT", "::_OesQryEtfComponentReq");
    module_vnoes::cross.record_assign(parent, "OesQryEtfComponentRspT", "OesQryEtfComponentRspT", "::_OesQryEtfComponentRsp");
    module_vnoes::cross.record_assign(parent, "OesQryOptionFilterT", "OesQryOptionFilterT", "::_OesQryOptionFilter");
    module_vnoes::cross.record_assign(parent, "OesQryOptionReqT", "OesQryOptionReqT", "::_OesQryOptionReq");
    module_vnoes::cross.record_assign(parent, "OesQryOptionRspT", "OesQryOptionRspT", "::_OesQryOptionRsp");
    module_vnoes::cross.record_assign(parent, "OesQryTradingDayRspT", "OesQryTradingDayRspT", "::_OesQryTradingDayRsp");
    module_vnoes::cross.record_assign(parent, "OesQryMarketStateFilterT", "OesQryMarketStateFilterT", "::_OesQryMarketStateFilter");
    module_vnoes::cross.record_assign(parent, "OesQryMarketStateReqT", "OesQryMarketStateReqT", "::_OesQryMarketStateReq");
    module_vnoes::cross.record_assign(parent, "OesQryMarketStateRspT", "OesQryMarketStateRspT", "::_OesQryMarketStateRsp");
    module_vnoes::cross.record_assign(parent, "OesQryReqMsgT", "OesQryReqMsgT", "::_OesQryReqMsg");
    module_vnoes::cross.record_assign(parent, "OesQryRspMsgT", "OesQryRspMsgT", "::_OesQryRspMsg");
    module_vnoes::cross.record_assign(parent, "eOesMsgTypeT", "eOesMsgTypeT", "::_eOesMsgType");
    module_vnoes::cross.record_assign(parent, "eOesSubscribeReportTypeT", "eOesSubscribeReportTypeT", "::_eOesSubscribeReportType");
    module_vnoes::cross.record_assign(parent, "eOesProtocolHintsTypeT", "eOesProtocolHintsTypeT", "::_eOesProtocolHintsType");
    module_vnoes::cross.record_assign(parent, "OesReportSynchronizationReqT", "OesReportSynchronizationReqT", "::_OesReportSynchronizationReq");
    module_vnoes::cross.record_assign(parent, "OesReportSynchronizationRspT", "OesReportSynchronizationRspT", "::_OesReportSynchronizationRsp");
    module_vnoes::cross.record_assign(parent, "OesTestRequestReqT", "OesTestRequestReqT", "::_OesTestRequestReq");
    module_vnoes::cross.record_assign(parent, "OesTestRequestRspT", "OesTestRequestRspT", "::_OesTestRequestRsp");
    module_vnoes::cross.record_assign(parent, "OesChangePasswordReqT", "OesChangePasswordReqT", "::_OesChangePasswordReq");
    module_vnoes::cross.record_assign(parent, "OesChangePasswordRspT", "OesChangePasswordRspT", "::_OesChangePasswordRsp");
    module_vnoes::cross.record_assign(parent, "OesBatchOrdersHeadT", "OesBatchOrdersHeadT", "::_OesBatchOrdersHead");
    module_vnoes::cross.record_assign(parent, "OesBatchOrdersReqT", "OesBatchOrdersReqT", "::_OesBatchOrdersReq");
    module_vnoes::cross.record_assign(parent, "OesRptMsgHeadT", "OesRptMsgHeadT", "::_OesRptMsgHead");
    module_vnoes::cross.record_assign(parent, "OesRptMsgBodyT", "OesRptMsgBodyT", "::_OesRptMsgBody");
    module_vnoes::cross.record_assign(parent, "OesRptMsgT", "OesRptMsgT", "::_OesRptMsg");
    module_vnoes::cross.record_assign(parent, "OesReqMsgBodyT", "OesReqMsgBodyT", "::_OesReqMsgBody");
    module_vnoes::cross.record_assign(parent, "OesRspMsgBodyT", "OesRspMsgBodyT", "::_OesRspMsgBody");
    module_vnoes::cross.record_assign(parent, "SErrMsgT", "SErrMsgT", "::_SErrMsg");
    module_vnoes::cross.record_assign(parent, "SDataBufferT", "SDataBufferT", "::_SDataBuffer");
    module_vnoes::cross.record_assign(parent, "eSSocketProtocolTypeT", "eSSocketProtocolTypeT", "::_eSSocketProtocolType");
    module_vnoes::cross.record_assign(parent, "SSocketUriInfoT", "SSocketUriInfoT", "::_SSocketUriInfo");
    module_vnoes::cross.record_assign(parent, "SSocketIpPortInfoT", "SSocketIpPortInfoT", "::_SSocketIpPortInfo");
    module_vnoes::cross.record_assign(parent, "SSocketChannelInfoT", "SSocketChannelInfoT", "::_SSocketChannelInfo");
    module_vnoes::cross.record_assign(parent, "SSocketOptionConfigT", "SSocketOptionConfigT", "::_SSocketOptionConfig");
    module_vnoes::cross.record_assign(parent, "eGeneralClientClusterTypeT", "eGeneralClientClusterTypeT", "::_eGeneralClientClusterType");
    module_vnoes::cross.record_assign(parent, "eGeneralClientEncryptTypeT", "eGeneralClientEncryptTypeT", "::_eGeneralClientEncryptType");
    module_vnoes::cross.record_assign(parent, "SGeneralClientChannelT", "SGeneralClientChannelT", "::_SGeneralClientChannel");
    module_vnoes::cross.record_assign(parent, "SGeneralClientChannelGroupT", "SGeneralClientChannelGroupT", "::_SGeneralClientChannelGroup");
    module_vnoes::cross.record_assign(parent, "SGeneralClientAddrInfoT", "SGeneralClientAddrInfoT", "::_SGeneralClientAddrInfo");
    module_vnoes::cross.record_assign(parent, "SGeneralClientRemoteCfgT", "SGeneralClientRemoteCfgT", "::_SGeneralClientRemoteCfg");
    module_vnoes::cross.record_assign(parent, "eOesApiChannelTypeT", "eOesApiChannelTypeT", "::_eOesApiChannelType");
    module_vnoes::cross.record_assign(parent, "OesApiSubscribeInfoT", "OesApiSubscribeInfoT", "::_OesApiSubscribeInfo");
    module_vnoes::cross.record_assign(parent, "OesApiClientCfgT", "OesApiClientCfgT", "::_OesApiClientCfg");
    module_vnoes::cross.record_assign(parent, "OesApiClientEnvT", "OesApiClientEnvT", "::_OesApiClientEnv");
    module_vnoes::cross.record_assign(parent, "eMdsExchangeIdT", "eMdsExchangeIdT", "::_eMdsExchangeId");
    module_vnoes::cross.record_assign(parent, "eMdsMsgSourceT", "eMdsMsgSourceT", "::_eMdsMsgSource");
    module_vnoes::cross.record_assign(parent, "eMdsMdProductTypeT", "eMdsMdProductTypeT", "::_eMdsMdProductType");
    module_vnoes::cross.record_assign(parent, "eMdsMdStreamTypeT", "eMdsMdStreamTypeT", "::_eMdsMdStreamType");
    module_vnoes::cross.record_assign(parent, "eMdsMdLevelT", "eMdsMdLevelT", "::_eMdsMdLevel");
    module_vnoes::cross.record_assign(parent, "eMdsL2PriceLevelOperatorT", "eMdsL2PriceLevelOperatorT", "::_eMdsL2PriceLevelOperator");
    module_vnoes::cross.record_assign(parent, "eMdsL2TradeExecTypeT", "eMdsL2TradeExecTypeT", "::_eMdsL2TradeExecType");
    module_vnoes::cross.record_assign(parent, "eMdsL2TradeBSFlagT", "eMdsL2TradeBSFlagT", "::_eMdsL2TradeBSFlag");
    module_vnoes::cross.record_assign(parent, "eMdsL2OrderSideT", "eMdsL2OrderSideT", "::_eMdsL2OrderSideT");
    module_vnoes::cross.record_assign(parent, "eMdsL2OrderTypeT", "eMdsL2OrderTypeT", "::_eMdsL2OrderType");
    module_vnoes::cross.record_assign(parent, "eMdsClientTypeT", "eMdsClientTypeT", "::_eMdsClientType");
    module_vnoes::cross.record_assign(parent, "eMdsClientStatusT", "eMdsClientStatusT", "::_eMdsClientStatus");
    module_vnoes::cross.record_assign(parent, "MdsTradingSessionStatusMsgT", "MdsTradingSessionStatusMsgT", "::_MdsTradingSessionStatusMsg");
    module_vnoes::cross.record_assign(parent, "MdsSecurityStatusMsgT", "MdsSecurityStatusMsgT", "::_MdsSecurityStatusMsg");
    module_vnoes::cross.record_assign(parent, "MdsPriceLevelEntryT", "MdsPriceLevelEntryT", "::_MdsPriceLevelEntry");
    module_vnoes::cross.record_assign(parent, "MdsMktDataSnapshotHeadT", "MdsMktDataSnapshotHeadT", "::_MdsMktDataSnapshotHead");
    module_vnoes::cross.record_assign(parent, "MdsIndexSnapshotBodyT", "MdsIndexSnapshotBodyT", "::_MdsIndexSnapshotBody");
    module_vnoes::cross.record_assign(parent, "MdsStockSnapshotBodyT", "MdsStockSnapshotBodyT", "::_MdsStockSnapshotBody");
    module_vnoes::cross.record_assign(parent, "MdsL1SnapshotBodyT", "MdsL1SnapshotBodyT", "::_MdsL1SnapshotBody");
    module_vnoes::cross.record_assign(parent, "MdsL1SnapshotT", "MdsL1SnapshotT", "::_MdsL1Snapshot");
    module_vnoes::cross.record_assign(parent, "MdsL2StockSnapshotBodyT", "MdsL2StockSnapshotBodyT", "::_MdsL2StockSnapshotBody");
    module_vnoes::cross.record_assign(parent, "MdsL2StockSnapshotIncrementalT", "MdsL2StockSnapshotIncrementalT", "::_MdsL2StockSnapshotIncremental");
    module_vnoes::cross.record_assign(parent, "MdsL2BestOrdersSnapshotBodyT", "MdsL2BestOrdersSnapshotBodyT", "::_MdsL2BestOrdersSnapshotBody");
    module_vnoes::cross.record_assign(parent, "MdsL2BestOrdersSnapshotIncrementalT", "MdsL2BestOrdersSnapshotIncrementalT", "::_MdsL2BestOrdersSnapshotIncremental");
    module_vnoes::cross.record_assign(parent, "MdsL2MarketOverviewT", "MdsL2MarketOverviewT", "::_MdsL2MarketOverview");
    module_vnoes::cross.record_assign(parent, "MdsL2SnapshotBodyT", "MdsL2SnapshotBodyT", "::_MdsL2SnapshotBody");
    module_vnoes::cross.record_assign(parent, "MdsMktDataSnapshotT", "MdsMktDataSnapshotT", "::_MdsMktDataSnapshot");
    module_vnoes::cross.record_assign(parent, "MdsL2TradeT", "MdsL2TradeT", "::_MdsL2Trade");
    module_vnoes::cross.record_assign(parent, "MdsL2OrderT", "MdsL2OrderT", "::_MdsL2Order");
    module_vnoes::cross.record_assign(parent, "MdsWholeMktMsgBodyT", "MdsWholeMktMsgBodyT", "::_MdsWholeMktMsgBody");
    module_vnoes::cross.record_assign(parent, "MdsStockStaticInfoT", "MdsStockStaticInfoT", "::_MdsStockStaticInfo");
    module_vnoes::cross.record_assign(parent, "MdsQryMktDataSnapshotReqT", "MdsQryMktDataSnapshotReqT", "::_MdsQryMktDataSnapshotReq");
    module_vnoes::cross.record_assign(parent, "MdsQryTrdSessionStatusReqT", "MdsQryTrdSessionStatusReqT", "::_MdsQryTrdSessionStatusReq");
    module_vnoes::cross.record_assign(parent, "MdsQryReqHeadT", "MdsQryReqHeadT", "::_MdsQryReqHeadT");
    module_vnoes::cross.record_assign(parent, "MdsQryRspHeadT", "MdsQryRspHeadT", "::_MdsQryRspHeadT");
    module_vnoes::cross.record_assign(parent, "MdsQryCursorT", "MdsQryCursorT", "::_MdsQryCursor");
    module_vnoes::cross.record_assign(parent, "MdsQrySecurityCodeEntryT", "MdsQrySecurityCodeEntryT", "::_MdsQrySecurityCodeEntry");
    module_vnoes::cross.record_assign(parent, "MdsQryStockStaticInfoFilterT", "MdsQryStockStaticInfoFilterT", "::_MdsQryStockStaticInfoFilter");
    module_vnoes::cross.record_assign(parent, "MdsQryStockStaticInfoReqT", "MdsQryStockStaticInfoReqT", "::_MdsQryStockStaticInfoReq");
    module_vnoes::cross.record_assign(parent, "MdsQryStockStaticInfoRspT", "MdsQryStockStaticInfoRspT", "::_MdsQryStockStaticInfoRsp");
    module_vnoes::cross.record_assign(parent, "MdsQrySnapshotListFilterT", "MdsQrySnapshotListFilterT", "::_MdsQrySnapshotListFilter");
    module_vnoes::cross.record_assign(parent, "MdsQrySnapshotListReqT", "MdsQrySnapshotListReqT", "::_MdsQrySnapshotListReq");
    module_vnoes::cross.record_assign(parent, "MdsQrySnapshotListRspT", "MdsQrySnapshotListRspT", "::_MdsQrySnapshotListRsp");
    module_vnoes::cross.record_assign(parent, "eMdsMsgTypeT", "eMdsMsgTypeT", "::_eMdsMsgType");
    module_vnoes::cross.record_assign(parent, "eMdsSubscribeModeT", "eMdsSubscribeModeT", "::_eMdsSubscribeMode");
    module_vnoes::cross.record_assign(parent, "eMdsMktSubscribeFlagT", "eMdsMktSubscribeFlagT", "::_eMdsMktSubscribeFlag");
    module_vnoes::cross.record_assign(parent, "eMdsSubscribedTickTypeT", "eMdsSubscribedTickTypeT", "::_eMdsSubscribedTickType");
    module_vnoes::cross.record_assign(parent, "eMdsSubscribedTickExpireTypeT", "eMdsSubscribedTickExpireTypeT", "::_eMdsSubscribedTickExpireType");
    module_vnoes::cross.record_assign(parent, "eMdsSubscribeDataTypeT", "eMdsSubscribeDataTypeT", "::_eMdsSubscribeDataType");
    module_vnoes::cross.record_assign(parent, "eMdsTickChannelNoT", "eMdsTickChannelNoT", "::_eMdsSubscribedChannelNo");
    module_vnoes::cross.record_assign(parent, "eMdsProtocolHintsTypeT", "eMdsProtocolHintsTypeT", "::_eMdsProtocolHintsType");
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestEntryT", "MdsMktDataRequestEntryT", "::_MdsMktDataRequestEntry");
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestReqT", "MdsMktDataRequestReqT", "::_MdsMktDataRequestReq");
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestReqBufT", "MdsMktDataRequestReqBufT", "::_MdsMktDataRequestReqBuf");
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestRspT", "MdsMktDataRequestRspT", "::_MdsMktDataRequestRsp");
    module_vnoes::cross.record_assign(parent, "MdsTestRequestReqT", "MdsTestRequestReqT", "::_MdsTestRequestReq");
    module_vnoes::cross.record_assign(parent, "MdsTestRequestRspT", "MdsTestRequestRspT", "::_MdsTestRequestRsp");
    module_vnoes::cross.record_assign(parent, "MdsChangePasswordReqT", "MdsChangePasswordReqT", "::_MdsChangePasswordReq");
    module_vnoes::cross.record_assign(parent, "MdsChangePasswordRspT", "MdsChangePasswordRspT", "::_MdsChangePasswordRsp");
    module_vnoes::cross.record_assign(parent, "MdsMktReqMsgBodyT", "MdsMktReqMsgBodyT", "::_MdsMktReqMsgBody");
    module_vnoes::cross.record_assign(parent, "MdsMktRspMsgBodyT", "MdsMktRspMsgBodyT", "::_MdsMktRspMsgBody");
    module_vnoes::cross.record_assign(parent, "MdsUdpPktHeadT", "MdsUdpPktHeadT", "::_MdsUdpPktHead");
    module_vnoes::cross.record_assign(parent, "eMdsApiChannelTypeT", "eMdsApiChannelTypeT", "::_eMdsApiChannelType");
    module_vnoes::cross.record_assign(parent, "MdsApiClientCfgT", "MdsApiClientCfgT", "::_MdsApiClientCfg");
    module_vnoes::cross.record_assign(parent, "MdsApiClientEnvT", "MdsApiClientEnvT", "::_MdsApiClientEnv");
    generate_caster_(parent);
}
