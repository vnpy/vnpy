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


void generate_vnoes_enums(pybind11::module & parent)
{
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
}
void generate_vnoes_functions_0(pybind11::module & parent)
{
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
}
void generate_vnoes_functions_1(pybind11::module & parent)
{
    parent.def("OesApi_WaitReportMsg",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_WaitReportMsg>,
            std::integral_constant<int, 2>
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
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryOrder>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryTrade",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryTrade>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCashAsset",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryCashAsset>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryStkHolding",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryStkHolding>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOptHolding",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryOptHolding>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryLotWinning",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryLotWinning>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCustInfo",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryCustInfo>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryInvAcct",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryInvAcct>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryCommissionRate",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryCommissionRate>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryFundTransferSerial",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryFundTransferSerial>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryIssue",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryIssue>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
}
void generate_vnoes_functions_2(pybind11::module & parent)
{
    parent.def("OesApi_QueryStock",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryStock>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryEtf",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryEtf>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryEtfComponent",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryEtfComponent>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryOption",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryOption>,
            std::integral_constant<int, 2>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_QueryMarketState",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&OesApi_QueryMarketState>,
            std::integral_constant<int, 2>
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
        c2py::inout_argument_transform < 
            c2py::function_constant<&OesApi_InitAll>,
            std::integral_constant<int, 8>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAllByConvention",
        c2py::inout_argument_transform < 
            c2py::function_constant<&OesApi_InitAllByConvention>,
            std::integral_constant<int, 3>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("OesApi_InitAllByCfgStruct",
        c2py::inout_argument_transform < 
            c2py::function_constant<&OesApi_InitAllByCfgStruct>,
            std::integral_constant<int, 3>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
}
