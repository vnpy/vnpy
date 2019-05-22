#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"


void generate_vnitap(pybind11::module & parent)
{
    {
        auto m = parent.def_submodule("ITapTrade");
        generate_sub_namespace_ITapTrade(m);
    }
    generate_class_TapAPIApplicationInfo(parent);
    generate_class_TapAPICommodity(parent);
    generate_class_TapAPIContract(parent);
    generate_class_TapAPIExchangeInfo(parent);
    generate_class_TapAPIChangePasswordReq(parent);
    generate_class_TapAPIQuoteLoginAuth(parent);
    generate_class_TapAPIQuotLoginRspInfo(parent);
    generate_class_TapAPIQuoteCommodityInfo(parent);
    generate_class_TapAPIQuoteContractInfo(parent);
    generate_class_TapAPIQuoteWhole(parent);
    generate_class_ITapQuoteAPINotify(parent);
    generate_class_ITapQuoteAPI(parent);
    parent.def("CreateITapTradeAPI",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &CreateITapTradeAPI
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("FreeITapTradeAPI",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &FreeITapTradeAPI
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("GetITapTradeAPIVersion",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &GetITapTradeAPIVersion
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetITapTradeAPIDataPath",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &SetITapTradeAPIDataPath
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetITapTradeAPILogLevel",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &SetITapTradeAPILogLevel
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("GetITapErrorDescribe",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &GetITapErrorDescribe
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("CreateTapQuoteAPI",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &CreateTapQuoteAPI
            >, 
            brigand::list<
                autocxxpy::indexed_transform_holder<autocxxpy::output_argument_transform, 1>
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("FreeTapQuoteAPI",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &FreeTapQuoteAPI
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("GetTapQuoteAPIVersion",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &GetTapQuoteAPIVersion
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetTapQuoteAPIDataPath",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &SetTapQuoteAPIDataPath
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("SetTapQuoteAPILogLevel",
        autocxxpy::apply_function_transform<
            autocxxpy::function_constant<
                &SetTapQuoteAPILogLevel
            >, 
            brigand::list<
            >
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.attr("APIYNFLAG_YES") = APIYNFLAG_YES;
    parent.attr("APIYNFLAG_NO") = APIYNFLAG_NO;
    parent.attr("APILOGLEVEL_NONE") = APILOGLEVEL_NONE;
    parent.attr("APILOGLEVEL_ERROR") = APILOGLEVEL_ERROR;
    parent.attr("APILOGLEVEL_WARNING") = APILOGLEVEL_WARNING;
    parent.attr("APILOGLEVEL_DEBUG") = APILOGLEVEL_DEBUG;
    parent.attr("TAPI_COMMODITY_TYPE_NONE") = TAPI_COMMODITY_TYPE_NONE;
    parent.attr("TAPI_COMMODITY_TYPE_SPOT") = TAPI_COMMODITY_TYPE_SPOT;
    parent.attr("TAPI_COMMODITY_TYPE_FUTURES") = TAPI_COMMODITY_TYPE_FUTURES;
    parent.attr("TAPI_COMMODITY_TYPE_OPTION") = TAPI_COMMODITY_TYPE_OPTION;
    parent.attr("TAPI_COMMODITY_TYPE_SPREAD_MONTH") = TAPI_COMMODITY_TYPE_SPREAD_MONTH;
    parent.attr("TAPI_COMMODITY_TYPE_SPREAD_COMMODITY") = TAPI_COMMODITY_TYPE_SPREAD_COMMODITY;
    parent.attr("TAPI_COMMODITY_TYPE_BUL") = TAPI_COMMODITY_TYPE_BUL;
    parent.attr("TAPI_COMMODITY_TYPE_BER") = TAPI_COMMODITY_TYPE_BER;
    parent.attr("TAPI_COMMODITY_TYPE_STD") = TAPI_COMMODITY_TYPE_STD;
    parent.attr("TAPI_COMMODITY_TYPE_STG") = TAPI_COMMODITY_TYPE_STG;
    parent.attr("TAPI_COMMODITY_TYPE_PRT") = TAPI_COMMODITY_TYPE_PRT;
    parent.attr("TAPI_COMMODITY_TYPE_BLT") = TAPI_COMMODITY_TYPE_BLT;
    parent.attr("TAPI_COMMODITY_TYPE_BRT") = TAPI_COMMODITY_TYPE_BRT;
    parent.attr("TAPI_COMMODITY_TYPE_DIRECTFOREX") = TAPI_COMMODITY_TYPE_DIRECTFOREX;
    parent.attr("TAPI_COMMODITY_TYPE_INDIRECTFOREX") = TAPI_COMMODITY_TYPE_INDIRECTFOREX;
    parent.attr("TAPI_COMMODITY_TYPE_CROSSFOREX") = TAPI_COMMODITY_TYPE_CROSSFOREX;
    parent.attr("TAPI_COMMODITY_TYPE_INDEX") = TAPI_COMMODITY_TYPE_INDEX;
    parent.attr("TAPI_COMMODITY_TYPE_STOCK") = TAPI_COMMODITY_TYPE_STOCK;
    parent.attr("TAPI_COMMODITY_TYPE_SPOT_TRADINGDEFER") = TAPI_COMMODITY_TYPE_SPOT_TRADINGDEFER;
    parent.attr("TAPI_COMMODITY_TYPE_FUTURE_LOCK") = TAPI_COMMODITY_TYPE_FUTURE_LOCK;
    parent.attr("TAPI_COMMODITY_TYPE_EFP") = TAPI_COMMODITY_TYPE_EFP;
    parent.attr("TAPI_CALLPUT_FLAG_CALL") = TAPI_CALLPUT_FLAG_CALL;
    parent.attr("TAPI_CALLPUT_FLAG_PUT") = TAPI_CALLPUT_FLAG_PUT;
    parent.attr("TAPI_CALLPUT_FLAG_NONE") = TAPI_CALLPUT_FLAG_NONE;
    parent.attr("TAPIERROR_SUCCEED") = TAPIERROR_SUCCEED;
    parent.attr("TAPIERROR_ConnectFail") = TAPIERROR_ConnectFail;
    parent.attr("TAPIERROR_LinkAuthFail") = TAPIERROR_LinkAuthFail;
    parent.attr("TAPIERROR_HostUnavailable") = TAPIERROR_HostUnavailable;
    parent.attr("TAPIERROR_SendDataError") = TAPIERROR_SendDataError;
    parent.attr("TAPIERROR_TestIDError") = TAPIERROR_TestIDError;
    parent.attr("TAPIERROR_NotReadyTestNetwork") = TAPIERROR_NotReadyTestNetwork;
    parent.attr("TAPIERROR_CurTestNotOver") = TAPIERROR_CurTestNotOver;
    parent.attr("TAPIERROR_NOFrontAvailable") = TAPIERROR_NOFrontAvailable;
    parent.attr("TAPIERROR_DataPathAvaiable") = TAPIERROR_DataPathAvaiable;
    parent.attr("TAPIERROR_RepeatLogin") = TAPIERROR_RepeatLogin;
    parent.attr("TAPIERROR_InnerError") = TAPIERROR_InnerError;
    parent.attr("TAPIERROR_LastReqNotFinish") = TAPIERROR_LastReqNotFinish;
    parent.attr("TAPIERROR_InputValueError") = TAPIERROR_InputValueError;
    parent.attr("TAPIERROR_AuthCode_Invalid") = TAPIERROR_AuthCode_Invalid;
    parent.attr("TAPIERROR_AuthCode_Expired") = TAPIERROR_AuthCode_Expired;
    parent.attr("TAPIERROR_AuthCode_TypeNotMatch") = TAPIERROR_AuthCode_TypeNotMatch;
    parent.attr("TAPIERROR_API_NotReady") = TAPIERROR_API_NotReady;
    parent.attr("TAPIERROR_UDP_LISTEN_FAILED") = TAPIERROR_UDP_LISTEN_FAILED;
    parent.attr("TAPIERROR_UDP_LISTENING") = TAPIERROR_UDP_LISTENING;
    parent.attr("TAPIERROR_NotImplemented") = TAPIERROR_NotImplemented;
    parent.attr("TAPIERROR_CallOneTimeOnly") = TAPIERROR_CallOneTimeOnly;
    parent.attr("TAPIERROR_Frequently") = TAPIERROR_Frequently;
    parent.attr("TAPIERROR_INPUTERROR_NULL") = TAPIERROR_INPUTERROR_NULL;
    parent.attr("TAPIERROR_INPUTERROR_TAPIYNFLAG") = TAPIERROR_INPUTERROR_TAPIYNFLAG;
    parent.attr("TAPIERROR_INPUTERROR_TAPILOGLEVEL") = TAPIERROR_INPUTERROR_TAPILOGLEVEL;
    parent.attr("TAPIERROR_INPUTERROR_TAPICommodityType") = TAPIERROR_INPUTERROR_TAPICommodityType;
    parent.attr("TAPIERROR_INPUTERROR_TAPICallOrPutFlagType") = TAPIERROR_INPUTERROR_TAPICallOrPutFlagType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIAccountType") = TAPIERROR_INPUTERROR_TAPIAccountType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIAccountState") = TAPIERROR_INPUTERROR_TAPIAccountState;
    parent.attr("TAPIERROR_INPUTERROR_TAPIAccountFamilyType") = TAPIERROR_INPUTERROR_TAPIAccountFamilyType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderTypeType") = TAPIERROR_INPUTERROR_TAPIOrderTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderSourceType") = TAPIERROR_INPUTERROR_TAPIOrderSourceType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITimeInForceType") = TAPIERROR_INPUTERROR_TAPITimeInForceType;
    parent.attr("TAPIERROR_INPUTERROR_TAPISideType") = TAPIERROR_INPUTERROR_TAPISideType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIPositionEffectType") = TAPIERROR_INPUTERROR_TAPIPositionEffectType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIHedgeFlagType") = TAPIERROR_INPUTERROR_TAPIHedgeFlagType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderStateType") = TAPIERROR_INPUTERROR_TAPIOrderStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPICalculateModeType") = TAPIERROR_INPUTERROR_TAPICalculateModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMatchSourceType") = TAPIERROR_INPUTERROR_TAPIMatchSourceType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOpenCloseModeType") = TAPIERROR_INPUTERROR_TAPIOpenCloseModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIFutureAlgType") = TAPIERROR_INPUTERROR_TAPIFutureAlgType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOptionAlgType") = TAPIERROR_INPUTERROR_TAPIOptionAlgType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType") = TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType") = TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType") = TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPICmbDirectType") = TAPIERROR_INPUTERROR_TAPICmbDirectType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIDeliveryModeType") = TAPIERROR_INPUTERROR_TAPIDeliveryModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIContractTypeType") = TAPIERROR_INPUTERROR_TAPIContractTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITacticsTypeType") = TAPIERROR_INPUTERROR_TAPITacticsTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIORDERACT") = TAPIERROR_INPUTERROR_TAPIORDERACT;
    parent.attr("TAPIERROR_INPUTERROR_TAPITriggerConditionType") = TAPIERROR_INPUTERROR_TAPITriggerConditionType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType") = TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITradingStateType") = TAPIERROR_INPUTERROR_TAPITradingStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMarketLevelType") = TAPIERROR_INPUTERROR_TAPIMarketLevelType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderQryTypeType") = TAPIERROR_INPUTERROR_TAPIOrderQryTypeType;
    parent.attr("TAPIERROR_DISCONNECT_CLOSE_INIT") = TAPIERROR_DISCONNECT_CLOSE_INIT;
    parent.attr("TAPIERROR_DISCONNECT_CLOSE_PASS") = TAPIERROR_DISCONNECT_CLOSE_PASS;
    parent.attr("TAPIERROR_DISCONNECT_READ_ERROR") = TAPIERROR_DISCONNECT_READ_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_WRITE_ERROR") = TAPIERROR_DISCONNECT_WRITE_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_BUF_FULL") = TAPIERROR_DISCONNECT_BUF_FULL;
    parent.attr("TAPIERROR_DISCONNECT_IOCP_ERROR") = TAPIERROR_DISCONNECT_IOCP_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_PARSE_ERROR") = TAPIERROR_DISCONNECT_PARSE_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_CONNECT_TIMEOUT") = TAPIERROR_DISCONNECT_CONNECT_TIMEOUT;
    parent.attr("TAPIERROR_DISCONNECT_INIT_ERROR") = TAPIERROR_DISCONNECT_INIT_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_HAS_CONNECTED") = TAPIERROR_DISCONNECT_HAS_CONNECTED;
    parent.attr("TAPIERROR_DISCONNECT_HAS_EXIT") = TAPIERROR_DISCONNECT_HAS_EXIT;
    parent.attr("TAPIERROR_DISCONNECT_TRY_LATER") = TAPIERROR_DISCONNECT_TRY_LATER;
    parent.attr("TAPIERROR_DISCONNECT_HEARTBEAT_FAILED") = TAPIERROR_DISCONNECT_HEARTBEAT_FAILED;
    parent.attr("TAPIERROR_LOGIN") = TAPIERROR_LOGIN;
    parent.attr("TAPIERROR_LOGIN_USER") = TAPIERROR_LOGIN_USER;
    parent.attr("TAPIERROR_LOGIN_DDA") = TAPIERROR_LOGIN_DDA;
    parent.attr("TAPIERROR_LOGIN_LICENSE") = TAPIERROR_LOGIN_LICENSE;
    parent.attr("TAPIERROR_LOGIN_MODULE") = TAPIERROR_LOGIN_MODULE;
    parent.attr("TAPIERROR_LOGIN_FORCE") = TAPIERROR_LOGIN_FORCE;
    parent.attr("TAPIERROR_LOGIN_STATE") = TAPIERROR_LOGIN_STATE;
    parent.attr("TAPIERROR_LOGIN_PASS") = TAPIERROR_LOGIN_PASS;
    parent.attr("TAPIERROR_LOGIN_RIGHT") = TAPIERROR_LOGIN_RIGHT;
    parent.attr("TAPIERROR_LOGIN_COUNT") = TAPIERROR_LOGIN_COUNT;
    parent.attr("TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES") = TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES;
    parent.attr("TAPIERROR_LOGIN_USER_EXPIRED") = TAPIERROR_LOGIN_USER_EXPIRED;
    parent.attr("TAPIERROR_LOGIN_NO_ACCOUNT") = TAPIERROR_LOGIN_NO_ACCOUNT;
    parent.attr("TAPIERROR_LOGIN_NO_JGT") = TAPIERROR_LOGIN_NO_JGT;
    parent.attr("TAPIERROR_LOGIN_ERROR_TIMES") = TAPIERROR_LOGIN_ERROR_TIMES;
    parent.attr("TAPIERROR_LOGIN_ERROR_AUTHTYPE") = TAPIERROR_LOGIN_ERROR_AUTHTYPE;
    parent.attr("TAPIERROR_LOGIN_ERROR_AUTHEXPIRED") = TAPIERROR_LOGIN_ERROR_AUTHEXPIRED;
    parent.attr("TAPIERROR_LOGIN_ERROR_PASSWDEXPIRED") = TAPIERROR_LOGIN_ERROR_PASSWDEXPIRED;
    parent.attr("TAPIERROR_USERINFO_QRY") = TAPIERROR_USERINFO_QRY;
    parent.attr("TAPIERROR_USERALLRIGHT_QRY") = TAPIERROR_USERALLRIGHT_QRY;
    parent.attr("TAPIERROR_USERALLACCOUNT_QRY") = TAPIERROR_USERALLACCOUNT_QRY;
    parent.attr("TAPIERROR_USERPASSWORD_MOD") = TAPIERROR_USERPASSWORD_MOD;
    parent.attr("TAPIERROR_USERPASSWORD_MOD_SOURCE") = TAPIERROR_USERPASSWORD_MOD_SOURCE;
    parent.attr("TAPIERROR_USERPASSWORD_MOD_SAME") = TAPIERROR_USERPASSWORD_MOD_SAME;
    parent.attr("TAPIERROR_USERPASSWORD_MOD_COMPLEXITY") = TAPIERROR_USERPASSWORD_MOD_COMPLEXITY;
    parent.attr("TAPIERROR_ACCOUNTINFO_QRY") = TAPIERROR_ACCOUNTINFO_QRY;
    parent.attr("TAPIERROR_TRADENO_QRY") = TAPIERROR_TRADENO_QRY;
    parent.attr("TAPIERROR_CONTRACTINFO_QRY") = TAPIERROR_CONTRACTINFO_QRY;
    parent.attr("TAPIERROR_SPECIALOPTIONFUTURE_QRY") = TAPIERROR_SPECIALOPTIONFUTURE_QRY;
    parent.attr("TAPIERROR_COMMODITYORDERTYPE_QRY") = TAPIERROR_COMMODITYORDERTYPE_QRY;
    parent.attr("TAPIERROR_ORDERTIMEINFORCE_QRY") = TAPIERROR_ORDERTIMEINFORCE_QRY;
    parent.attr("TAPIERROR_USER_ORDER_FREQUENCE_QRY") = TAPIERROR_USER_ORDER_FREQUENCE_QRY;
    parent.attr("TAPIERROR_ORDERINSERT_ACCOUNT") = TAPIERROR_ORDERINSERT_ACCOUNT;
    parent.attr("TAPIERROR_ORDERINSERT_ACCOUNT_STATE") = TAPIERROR_ORDERINSERT_ACCOUNT_STATE;
    parent.attr("TAPIERROR_ORDERINSERT_SIDE_TRADE") = TAPIERROR_ORDERINSERT_SIDE_TRADE;
    parent.attr("TAPIERROR_ORDERINSERT_OPTIONS_TRADE") = TAPIERROR_ORDERINSERT_OPTIONS_TRADE;
    parent.attr("TAPIERROR_ORDERINSERT_COMMODITY_TRADE") = TAPIERROR_ORDERINSERT_COMMODITY_TRADE;
    parent.attr("TAPIERROR_ORDERINSERT_OPEN_RIGHT") = TAPIERROR_ORDERINSERT_OPEN_RIGHT;
    parent.attr("TAPIERROR_ORDERINSERT_RISK_CHECK") = TAPIERROR_ORDERINSERT_RISK_CHECK;
    parent.attr("TAPIERROR_ORDERINSERT_CONTRACT") = TAPIERROR_ORDERINSERT_CONTRACT;
    parent.attr("TAPIERROR_ORDERINSERT_TRADEROUTE") = TAPIERROR_ORDERINSERT_TRADEROUTE;
    parent.attr("TAPIERROR_ORDERINSERT_POSITIONMAX") = TAPIERROR_ORDERINSERT_POSITIONMAX;
    parent.attr("TAPIERROR_ORDER_NOTRADE") = TAPIERROR_ORDER_NOTRADE;
    parent.attr("TAPIERROR_ORDER_CLOSE") = TAPIERROR_ORDER_CLOSE;
    parent.attr("TAPIERROR_ORDERINSERT_NOTENOUGHFUND") = TAPIERROR_ORDERINSERT_NOTENOUGHFUND;
    parent.attr("TAPIERROR_ORDERINSERT_ORDERTYPE") = TAPIERROR_ORDERINSERT_ORDERTYPE;
    parent.attr("TAPIERROR_ORDERINSERT_TIMEINFORCE") = TAPIERROR_ORDERINSERT_TIMEINFORCE;
    parent.attr("TAPIERROR_ORDERINSERT_NO_TACTICS") = TAPIERROR_ORDERINSERT_NO_TACTICS;
    parent.attr("TAPIERROR_ORDERINSERT_POSITION_CANNOT_CLOSE") = TAPIERROR_ORDERINSERT_POSITION_CANNOT_CLOSE;
    parent.attr("TAPIERROR_ORDERINSERT_AUTOCHECK_FAIL") = TAPIERROR_ORDERINSERT_AUTOCHECK_FAIL;
    parent.attr("TAPIERROR_ORDERINSERT_LME_NOTREADY") = TAPIERROR_ORDERINSERT_LME_NOTREADY;
    parent.attr("TAPIERROR_ORDERINSERT_CLOSEMODE") = TAPIERROR_ORDERINSERT_CLOSEMODE;
    parent.attr("TAPIERROR_ORDERINSERT_PARENTNOTENOUGHFUND") = TAPIERROR_ORDERINSERT_PARENTNOTENOUGHFUND;
    parent.attr("TAPIERROR_SWAP_CONTRACT") = TAPIERROR_SWAP_CONTRACT;
    parent.attr("TAPIERROR_USERNO_NOTHAS_ACCOUNT") = TAPIERROR_USERNO_NOTHAS_ACCOUNT;
    parent.attr("TAPIERROR_UPPERCHANNEL_BROKEN") = TAPIERROR_UPPERCHANNEL_BROKEN;
    parent.attr("TAPIERROR_UPPERCHANNEL_NOT_EXIST") = TAPIERROR_UPPERCHANNEL_NOT_EXIST;
    parent.attr("TAPIERROR_ORDERDELETE_NOT_SYSNO") = TAPIERROR_ORDERDELETE_NOT_SYSNO;
    parent.attr("TAPIERROR_ORDERDELETE_NOT_STATE") = TAPIERROR_ORDERDELETE_NOT_STATE;
    parent.attr("TAPIERROR_ORDERACTIVE_NOT_STATE") = TAPIERROR_ORDERACTIVE_NOT_STATE;
    parent.attr("TAPIERROR_ORDERCHECK_NOT_STATE") = TAPIERROR_ORDERCHECK_NOT_STATE;
    parent.attr("TAPIERROR_ORDERCHECK_FAIL") = TAPIERROR_ORDERCHECK_FAIL;
    parent.attr("TAPIERROR_ORDERMODIFY_NOT_STATE") = TAPIERROR_ORDERMODIFY_NOT_STATE;
    parent.attr("TAPIERROR_ORDERMODIFY_BACK_INPUT") = TAPIERROR_ORDERMODIFY_BACK_INPUT;
    parent.attr("TAPIERROR_ORDERINSERT_FEE") = TAPIERROR_ORDERINSERT_FEE;
    parent.attr("TAPIERROR_ORDERINSERT_MARGIN") = TAPIERROR_ORDERINSERT_MARGIN;
    parent.attr("TAPIERROR_ORDER_NO_PERMIT") = TAPIERROR_ORDER_NO_PERMIT;
    parent.attr("TAPIERROR_RSPQUOTE_NO_PERMIT") = TAPIERROR_RSPQUOTE_NO_PERMIT;
    parent.attr("TAPIERROR_RSPQUOTE_CHILD_NO_PERMIT") = TAPIERROR_RSPQUOTE_CHILD_NO_PERMIT;
    parent.attr("TAPIERROR_TRADENO_NOT_FIND") = TAPIERROR_TRADENO_NOT_FIND;
    parent.attr("TAPIERROR_ORDER_NO_CLOSE") = TAPIERROR_ORDER_NO_CLOSE;
    parent.attr("TAPIERROR_QRY_QUOTE_NO_PERMIT") = TAPIERROR_QRY_QUOTE_NO_PERMIT;
    parent.attr("TAPIERROR_EXPIREDATE_NO_PERMIT") = TAPIERROR_EXPIREDATE_NO_PERMIT;
    parent.attr("TAPIERROR_CMB_NO_PERMIT") = TAPIERROR_CMB_NO_PERMIT;
    parent.attr("TAPIERROR_ORDERSERVER_NO_PERMIT") = TAPIERROR_ORDERSERVER_NO_PERMIT;
    parent.attr("TAPIERROR_POSITION_CANNOT_EXEC_OR_ABANDON") = TAPIERROR_POSITION_CANNOT_EXEC_OR_ABANDON;
    parent.attr("TAPIERROR_ORDERCHECK_NO_PERMIT") = TAPIERROR_ORDERCHECK_NO_PERMIT;
    parent.attr("TAPIERROR_ORDERMAXOPENVOL_NO_PERMIT") = TAPIERROR_ORDERMAXOPENVOL_NO_PERMIT;
    parent.attr("TAPIERROR_ORDER_QTY_NO_PERMIT") = TAPIERROR_ORDER_QTY_NO_PERMIT;
    parent.attr("TAPIERROR_ORDER_APPLY_NO_PERMIT") = TAPIERROR_ORDER_APPLY_NO_PERMIT;
    parent.attr("TAPIERROR_ORDER_FREQ_OVERRUN") = TAPIERROR_ORDER_FREQ_OVERRUN;
    parent.attr("TAPIERROR_COMB_NO_SIDEORHEDGE") = TAPIERROR_COMB_NO_SIDEORHEDGE;
    parent.attr("TAPIERROR_ORDER_FREQUENCY") = TAPIERROR_ORDER_FREQUENCY;
    parent.attr("TAPIERROR_ORDER_QUERYING") = TAPIERROR_ORDER_QUERYING;
    parent.attr("TAPIERROR_SUBSCRIBEQUOTE_MAX") = TAPIERROR_SUBSCRIBEQUOTE_MAX;
    parent.attr("TAPIERROR_SUBSCRIBEQUOTE_EXCHANGE_MAX") = TAPIERROR_SUBSCRIBEQUOTE_EXCHANGE_MAX;
    parent.attr("TAPIERROR_SUBSCRIBEQUOTE_NO_RIGHT") = TAPIERROR_SUBSCRIBEQUOTE_NO_RIGHT;
    parent.attr("TAPIERROR_SUBSCRIBEQUOTE_NO_EXCHANGE_RIGHT") = TAPIERROR_SUBSCRIBEQUOTE_NO_EXCHANGE_RIGHT;
    parent.attr("TAPIERROR_SUBSCRIBEQUOTE_COMMODITY_NOT_EXIST") = TAPIERROR_SUBSCRIBEQUOTE_COMMODITY_NOT_EXIST;
    parent.attr("TAPIERROR_SUBSCRIBEQUOTE_CONTRACT_MAY_NOT_EXIST") = TAPIERROR_SUBSCRIBEQUOTE_CONTRACT_MAY_NOT_EXIST;
    parent.attr("TAPIERROR_QUOTEFRONT_UNKNOWN_PROTOCOL") = TAPIERROR_QUOTEFRONT_UNKNOWN_PROTOCOL;
    generate_caster_(parent);
}
void generate_sub_namespace_ITapTrade(pybind11::module & parent)
{
    generate_class_ITapTrade_TapAPIApplicationInfo(parent);
    generate_class_ITapTrade_TapAPICommodity(parent);
    generate_class_ITapTrade_TapAPIContract(parent);
    generate_class_ITapTrade_TapAPIExchangeInfo(parent);
    generate_class_ITapTrade_TapAPIChangePasswordReq(parent);
    generate_class_ITapTrade_TapAPIAuthPasswordReq(parent);
    generate_class_ITapTrade_TapAPITradeLoginAuth(parent);
    generate_class_ITapTrade_TapAPITradeLoginRspInfo(parent);
    generate_class_ITapTrade_TapAPIRequestVertificateCodeRsp(parent);
    generate_class_ITapTrade_TapAPIAccQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountInfo(parent);
    generate_class_ITapTrade_TapAPINewOrder(parent);
    generate_class_ITapTrade_TapAPIOrderInfo(parent);
    generate_class_ITapTrade_TapAPIOrderInfoNotice(parent);
    generate_class_ITapTrade_TapAPIOrderActionRsp(parent);
    generate_class_ITapTrade_TapAPIAmendOrder(parent);
    generate_class_ITapTrade_TapAPIOrderCancelReq(parent);
    generate_class_ITapTrade_TapAPIOrderQryReq(parent);
    generate_class_ITapTrade_TapAPIOrderProcessQryReq(parent);
    generate_class_ITapTrade_TapAPIFillQryReq(parent);
    generate_class_ITapTrade_TapAPIFillInfo(parent);
    generate_class_ITapTrade_TapAPICloseQryReq(parent);
    generate_class_ITapTrade_TapAPICloseInfo(parent);
    generate_class_ITapTrade_TapAPIPositionQryReq(parent);
    generate_class_ITapTrade_TapAPIPositionInfo(parent);
    generate_class_ITapTrade_TapAPIPositionProfit(parent);
    generate_class_ITapTrade_TapAPIPositionProfitNotice(parent);
    generate_class_ITapTrade_TapAPIPositionSummary(parent);
    generate_class_ITapTrade_TapAPIFundReq(parent);
    generate_class_ITapTrade_TapAPIFundData(parent);
    generate_class_ITapTrade_TapAPICommodityInfo(parent);
    generate_class_ITapTrade_TapAPITradeContractInfo(parent);
    generate_class_ITapTrade_TapAPICurrencyInfo(parent);
    generate_class_ITapTrade_TapAPITradeMessageReq(parent);
    generate_class_ITapTrade_TapAPITradeMessage(parent);
    generate_class_ITapTrade_TapAPIBillQryReq(parent);
    generate_class_ITapTrade_TapAPIBillQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisOrderQryReq(parent);
    generate_class_ITapTrade_TapAPIHisOrderQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisMatchQryReq(parent);
    generate_class_ITapTrade_TapAPIHisMatchQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisOrderProcessQryReq(parent);
    generate_class_ITapTrade_TapAPIHisPositionQryReq(parent);
    generate_class_ITapTrade_TapAPIHisPositionQryRsp(parent);
    generate_class_ITapTrade_TapAPIHisDeliveryQryReq(parent);
    generate_class_ITapTrade_TapAPIHisDeliveryQryRsp(parent);
    generate_class_ITapTrade_TapAPIAccountCashAdjustQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountCashAdjustQryRsp(parent);
    generate_class_ITapTrade_TapAPIAccountFeeRentQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountFeeRentQryRsp(parent);
    generate_class_ITapTrade_TapAPIAccountMarginRentQryReq(parent);
    generate_class_ITapTrade_TapAPIAccountMarginRentQryRsp(parent);
    generate_class_ITapTrade_TapAPIOrderQuoteMarketNotice(parent);
    generate_class_ITapTrade_TapAPIOrderMarketInsertReq(parent);
    generate_class_ITapTrade_TapAPIOrderMarketInsertRsp(parent);
    generate_class_ITapTrade_TapAPIOrderMarketDeleteReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalRemoveReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalRemoveRsp(parent);
    generate_class_ITapTrade_TapAPIOrderLocalInputReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalModifyReq(parent);
    generate_class_ITapTrade_TapAPIOrderLocalTransferReq(parent);
    generate_class_ITapTrade_TapAPIFillLocalInputReq(parent);
    generate_class_ITapTrade_TapAPIFillLocalRemoveReq(parent);
    generate_class_ITapTrade_TapAPITradingCalendarQryRsp(parent);
    generate_class_ITapTrade_ITapTradeAPINotify(parent);
    generate_class_ITapTrade_ITapTradeAPI(parent);
    parent.attr("APIYNFLAG_YES") = ITapTrade::APIYNFLAG_YES;
    parent.attr("APIYNFLAG_NO") = ITapTrade::APIYNFLAG_NO;
    parent.attr("APIPASSWORD_TRADE") = ITapTrade::APIPASSWORD_TRADE;
    parent.attr("APIPASSWORD_PHONE") = ITapTrade::APIPASSWORD_PHONE;
    parent.attr("APILOGLEVEL_NONE") = ITapTrade::APILOGLEVEL_NONE;
    parent.attr("APILOGLEVEL_ERROR") = ITapTrade::APILOGLEVEL_ERROR;
    parent.attr("APILOGLEVEL_WARNING") = ITapTrade::APILOGLEVEL_WARNING;
    parent.attr("APILOGLEVEL_DEBUG") = ITapTrade::APILOGLEVEL_DEBUG;
    parent.attr("TAPI_OPTION_TYPE_AMERICAN") = ITapTrade::TAPI_OPTION_TYPE_AMERICAN;
    parent.attr("TAPI_OPTION_TYPE_AMERICAN2") = ITapTrade::TAPI_OPTION_TYPE_AMERICAN2;
    parent.attr("TAPI_OPTION_TYPE_EUROPEAN") = ITapTrade::TAPI_OPTION_TYPE_EUROPEAN;
    parent.attr("TAPI_OPTION_TYPE_EUROPEAN2") = ITapTrade::TAPI_OPTION_TYPE_EUROPEAN2;
    parent.attr("TAPI_COMMODITY_TYPE_NONE") = ITapTrade::TAPI_COMMODITY_TYPE_NONE;
    parent.attr("TAPI_COMMODITY_TYPE_SPOT") = ITapTrade::TAPI_COMMODITY_TYPE_SPOT;
    parent.attr("TAPI_COMMODITY_TYPE_FUTURES") = ITapTrade::TAPI_COMMODITY_TYPE_FUTURES;
    parent.attr("TAPI_COMMODITY_TYPE_OPTION") = ITapTrade::TAPI_COMMODITY_TYPE_OPTION;
    parent.attr("TAPI_COMMODITY_TYPE_SPREAD_MONTH") = ITapTrade::TAPI_COMMODITY_TYPE_SPREAD_MONTH;
    parent.attr("TAPI_COMMODITY_TYPE_SPREAD_COMMODITY") = ITapTrade::TAPI_COMMODITY_TYPE_SPREAD_COMMODITY;
    parent.attr("TAPI_COMMODITY_TYPE_BUL") = ITapTrade::TAPI_COMMODITY_TYPE_BUL;
    parent.attr("TAPI_COMMODITY_TYPE_BER") = ITapTrade::TAPI_COMMODITY_TYPE_BER;
    parent.attr("TAPI_COMMODITY_TYPE_STD") = ITapTrade::TAPI_COMMODITY_TYPE_STD;
    parent.attr("TAPI_COMMODITY_TYPE_STG") = ITapTrade::TAPI_COMMODITY_TYPE_STG;
    parent.attr("TAPI_COMMODITY_TYPE_PRT") = ITapTrade::TAPI_COMMODITY_TYPE_PRT;
    parent.attr("TAPI_COMMODITY_TYPE_DIRECTFOREX") = ITapTrade::TAPI_COMMODITY_TYPE_DIRECTFOREX;
    parent.attr("TAPI_COMMODITY_TYPE_INDIRECTFOREX") = ITapTrade::TAPI_COMMODITY_TYPE_INDIRECTFOREX;
    parent.attr("TAPI_COMMODITY_TYPE_CROSSFOREX") = ITapTrade::TAPI_COMMODITY_TYPE_CROSSFOREX;
    parent.attr("TAPI_COMMODITY_TYPE_INDEX") = ITapTrade::TAPI_COMMODITY_TYPE_INDEX;
    parent.attr("TAPI_COMMODITY_TYPE_STOCK") = ITapTrade::TAPI_COMMODITY_TYPE_STOCK;
    parent.attr("TAPI_CALLPUT_FLAG_CALL") = ITapTrade::TAPI_CALLPUT_FLAG_CALL;
    parent.attr("TAPI_CALLPUT_FLAG_PUT") = ITapTrade::TAPI_CALLPUT_FLAG_PUT;
    parent.attr("TAPI_CALLPUT_FLAG_NONE") = ITapTrade::TAPI_CALLPUT_FLAG_NONE;
    parent.attr("TAPI_ACCOUNT_TYPE_PERSON") = ITapTrade::TAPI_ACCOUNT_TYPE_PERSON;
    parent.attr("TAPI_ACCOUNT_TYPE_ORGANIZATION") = ITapTrade::TAPI_ACCOUNT_TYPE_ORGANIZATION;
    parent.attr("TAPI_ACCOUNT_TYPE_AGENT") = ITapTrade::TAPI_ACCOUNT_TYPE_AGENT;
    parent.attr("TAPI_ACCOUNT_TYPE_MARGIN") = ITapTrade::TAPI_ACCOUNT_TYPE_MARGIN;
    parent.attr("TAPI_ACCOUNT_TYPE_HOUSE") = ITapTrade::TAPI_ACCOUNT_TYPE_HOUSE;
    parent.attr("TAPI_ACCOUNT_TYPE_STOCK") = ITapTrade::TAPI_ACCOUNT_TYPE_STOCK;
    parent.attr("TAPI_RIGHT_ORDER_DEL") = ITapTrade::TAPI_RIGHT_ORDER_DEL;
    parent.attr("TAPI_RIGHT_ORDER_CHECK") = ITapTrade::TAPI_RIGHT_ORDER_CHECK;
    parent.attr("TAPI_RIGHT_ONLY_QRY") = ITapTrade::TAPI_RIGHT_ONLY_QRY;
    parent.attr("TAPI_RIGHT_ONLY_OPEN") = ITapTrade::TAPI_RIGHT_ONLY_OPEN;
    parent.attr("TAPI_USERTYPE_CLIENT") = ITapTrade::TAPI_USERTYPE_CLIENT;
    parent.attr("TAPI_USERTYPE_BROKER") = ITapTrade::TAPI_USERTYPE_BROKER;
    parent.attr("TAPI_USERTYPE_TRADER") = ITapTrade::TAPI_USERTYPE_TRADER;
    parent.attr("TAPI_USERTYPE_RISK") = ITapTrade::TAPI_USERTYPE_RISK;
    parent.attr("TAPI_USERTYPE_MANAGER") = ITapTrade::TAPI_USERTYPE_MANAGER;
    parent.attr("TAPI_USERTYPE_QUOTE") = ITapTrade::TAPI_USERTYPE_QUOTE;
    parent.attr("TAPI_ACCOUNT_STATE_NORMAL") = ITapTrade::TAPI_ACCOUNT_STATE_NORMAL;
    parent.attr("TAPI_ACCOUNT_STATE_CANCEL") = ITapTrade::TAPI_ACCOUNT_STATE_CANCEL;
    parent.attr("TAPI_ACCOUNT_STATE_SLEEP") = ITapTrade::TAPI_ACCOUNT_STATE_SLEEP;
    parent.attr("TAPI_ACCOUNT_TRADING_RIGHT_NORMAL") = ITapTrade::TAPI_ACCOUNT_TRADING_RIGHT_NORMAL;
    parent.attr("TAPI_ACCOUNT_TRADING_RIGHT_NOTRADE") = ITapTrade::TAPI_ACCOUNT_TRADING_RIGHT_NOTRADE;
    parent.attr("TAPI_ACCOUNT_TRADING_RIGHT_CLOSE") = ITapTrade::TAPI_ACCOUNT_TRADING_RIGHT_CLOSE;
    parent.attr("TAPI_ORDER_TYPE_MARKET") = ITapTrade::TAPI_ORDER_TYPE_MARKET;
    parent.attr("TAPI_ORDER_TYPE_LIMIT") = ITapTrade::TAPI_ORDER_TYPE_LIMIT;
    parent.attr("TAPI_ORDER_TYPE_STOP_MARKET") = ITapTrade::TAPI_ORDER_TYPE_STOP_MARKET;
    parent.attr("TAPI_ORDER_TYPE_STOP_LIMIT") = ITapTrade::TAPI_ORDER_TYPE_STOP_LIMIT;
    parent.attr("TAPI_ORDER_TYPE_OPT_EXEC") = ITapTrade::TAPI_ORDER_TYPE_OPT_EXEC;
    parent.attr("TAPI_ORDER_TYPE_OPT_ABANDON") = ITapTrade::TAPI_ORDER_TYPE_OPT_ABANDON;
    parent.attr("TAPI_ORDER_TYPE_REQQUOT") = ITapTrade::TAPI_ORDER_TYPE_REQQUOT;
    parent.attr("TAPI_ORDER_TYPE_RSPQUOT") = ITapTrade::TAPI_ORDER_TYPE_RSPQUOT;
    parent.attr("TAPI_ORDER_TYPE_ICEBERG") = ITapTrade::TAPI_ORDER_TYPE_ICEBERG;
    parent.attr("TAPI_ORDER_TYPE_GHOST") = ITapTrade::TAPI_ORDER_TYPE_GHOST;
    parent.attr("TAPI_ORDER_TYPE_HKEX_AUCTION") = ITapTrade::TAPI_ORDER_TYPE_HKEX_AUCTION;
    parent.attr("TAPI_ORDER_TYPE_SWAP") = ITapTrade::TAPI_ORDER_TYPE_SWAP;
    parent.attr("TAPI_ORDER_SOURCE_SELF_ETRADER") = ITapTrade::TAPI_ORDER_SOURCE_SELF_ETRADER;
    parent.attr("TAPI_ORDER_SOURCE_PROXY_ETRADER") = ITapTrade::TAPI_ORDER_SOURCE_PROXY_ETRADER;
    parent.attr("TAPI_ORDER_SOURCE_JTRADER") = ITapTrade::TAPI_ORDER_SOURCE_JTRADER;
    parent.attr("TAPI_ORDER_SOURCE_MANUAL") = ITapTrade::TAPI_ORDER_SOURCE_MANUAL;
    parent.attr("TAPI_ORDER_SOURCE_CARRY") = ITapTrade::TAPI_ORDER_SOURCE_CARRY;
    parent.attr("TAPI_ORDER_SOURCE_PROGRAM") = ITapTrade::TAPI_ORDER_SOURCE_PROGRAM;
    parent.attr("TAPI_ORDER_SOURCE_DELIVERY") = ITapTrade::TAPI_ORDER_SOURCE_DELIVERY;
    parent.attr("TAPI_ORDER_SOURCE_ABANDON") = ITapTrade::TAPI_ORDER_SOURCE_ABANDON;
    parent.attr("TAPI_ORDER_SOURCE_CHANNEL") = ITapTrade::TAPI_ORDER_SOURCE_CHANNEL;
    parent.attr("TAPI_ORDER_TIMEINFORCE_GFD") = ITapTrade::TAPI_ORDER_TIMEINFORCE_GFD;
    parent.attr("TAPI_ORDER_TIMEINFORCE_GTC") = ITapTrade::TAPI_ORDER_TIMEINFORCE_GTC;
    parent.attr("TAPI_ORDER_TIMEINFORCE_GTD") = ITapTrade::TAPI_ORDER_TIMEINFORCE_GTD;
    parent.attr("TAPI_ORDER_TIMEINFORCE_FAK") = ITapTrade::TAPI_ORDER_TIMEINFORCE_FAK;
    parent.attr("TAPI_ORDER_TIMEINFORCE_FOK") = ITapTrade::TAPI_ORDER_TIMEINFORCE_FOK;
    parent.attr("TAPI_SIDE_NONE") = ITapTrade::TAPI_SIDE_NONE;
    parent.attr("TAPI_SIDE_BUY") = ITapTrade::TAPI_SIDE_BUY;
    parent.attr("TAPI_SIDE_SELL") = ITapTrade::TAPI_SIDE_SELL;
    parent.attr("TAPI_PositionEffect_NONE") = ITapTrade::TAPI_PositionEffect_NONE;
    parent.attr("TAPI_PositionEffect_OPEN") = ITapTrade::TAPI_PositionEffect_OPEN;
    parent.attr("TAPI_PositionEffect_COVER") = ITapTrade::TAPI_PositionEffect_COVER;
    parent.attr("TAPI_PositionEffect_COVER_TODAY") = ITapTrade::TAPI_PositionEffect_COVER_TODAY;
    parent.attr("TAPI_HEDGEFLAG_NONE") = ITapTrade::TAPI_HEDGEFLAG_NONE;
    parent.attr("TAPI_HEDGEFLAG_T") = ITapTrade::TAPI_HEDGEFLAG_T;
    parent.attr("TAPI_HEDGEFLAG_B") = ITapTrade::TAPI_HEDGEFLAG_B;
    parent.attr("TAPI_HEDGEFLAG_L") = ITapTrade::TAPI_HEDGEFLAG_L;
    parent.attr("TAPI_ORDER_STATE_SUBMIT") = ITapTrade::TAPI_ORDER_STATE_SUBMIT;
    parent.attr("TAPI_ORDER_STATE_ACCEPT") = ITapTrade::TAPI_ORDER_STATE_ACCEPT;
    parent.attr("TAPI_ORDER_STATE_TRIGGERING") = ITapTrade::TAPI_ORDER_STATE_TRIGGERING;
    parent.attr("TAPI_ORDER_STATE_EXCTRIGGERING") = ITapTrade::TAPI_ORDER_STATE_EXCTRIGGERING;
    parent.attr("TAPI_ORDER_STATE_QUEUED") = ITapTrade::TAPI_ORDER_STATE_QUEUED;
    parent.attr("TAPI_ORDER_STATE_PARTFINISHED") = ITapTrade::TAPI_ORDER_STATE_PARTFINISHED;
    parent.attr("TAPI_ORDER_STATE_FINISHED") = ITapTrade::TAPI_ORDER_STATE_FINISHED;
    parent.attr("TAPI_ORDER_STATE_CANCELING") = ITapTrade::TAPI_ORDER_STATE_CANCELING;
    parent.attr("TAPI_ORDER_STATE_MODIFYING") = ITapTrade::TAPI_ORDER_STATE_MODIFYING;
    parent.attr("TAPI_ORDER_STATE_CANCELED") = ITapTrade::TAPI_ORDER_STATE_CANCELED;
    parent.attr("TAPI_ORDER_STATE_LEFTDELETED") = ITapTrade::TAPI_ORDER_STATE_LEFTDELETED;
    parent.attr("TAPI_ORDER_STATE_FAIL") = ITapTrade::TAPI_ORDER_STATE_FAIL;
    parent.attr("TAPI_ORDER_STATE_DELETED") = ITapTrade::TAPI_ORDER_STATE_DELETED;
    parent.attr("TAPI_ORDER_STATE_SUPPENDED") = ITapTrade::TAPI_ORDER_STATE_SUPPENDED;
    parent.attr("TAPI_ORDER_STATE_DELETEDFOREXPIRE") = ITapTrade::TAPI_ORDER_STATE_DELETEDFOREXPIRE;
    parent.attr("TAPI_ORDER_STATE_EFFECT") = ITapTrade::TAPI_ORDER_STATE_EFFECT;
    parent.attr("TAPI_ORDER_STATE_APPLY") = ITapTrade::TAPI_ORDER_STATE_APPLY;
    parent.attr("TAPI_CALULATE_MODE_COMBINE") = ITapTrade::TAPI_CALULATE_MODE_COMBINE;
    parent.attr("TAPI_CALCULATE_MODE_PERCENTAGE") = ITapTrade::TAPI_CALCULATE_MODE_PERCENTAGE;
    parent.attr("TAPI_CALCULATE_MODE_QUOTA") = ITapTrade::TAPI_CALCULATE_MODE_QUOTA;
    parent.attr("TAPI_CALCULATE_MODE_CHAPERCENTAGE") = ITapTrade::TAPI_CALCULATE_MODE_CHAPERCENTAGE;
    parent.attr("TAPI_CALCULATE_MODE_CHAQUOTA") = ITapTrade::TAPI_CALCULATE_MODE_CHAQUOTA;
    parent.attr("TAPI_CALCULATE_MODE_DISCOUNT") = ITapTrade::TAPI_CALCULATE_MODE_DISCOUNT;
    parent.attr("TAPI_MATCH_SOURCE_ALL") = ITapTrade::TAPI_MATCH_SOURCE_ALL;
    parent.attr("TAPI_MATCH_SOURCE_SELF_ETRADER") = ITapTrade::TAPI_MATCH_SOURCE_SELF_ETRADER;
    parent.attr("TAPI_MATCH_SOURCE_PROXY_ETRADER") = ITapTrade::TAPI_MATCH_SOURCE_PROXY_ETRADER;
    parent.attr("TAPI_MATCH_SOURCE_JTRADER") = ITapTrade::TAPI_MATCH_SOURCE_JTRADER;
    parent.attr("TAPI_MATCH_SOURCE_MANUAL") = ITapTrade::TAPI_MATCH_SOURCE_MANUAL;
    parent.attr("TAPI_MATCH_SOURCE_CARRY") = ITapTrade::TAPI_MATCH_SOURCE_CARRY;
    parent.attr("TAPI_MATCH_SOURCE_PROGRAM") = ITapTrade::TAPI_MATCH_SOURCE_PROGRAM;
    parent.attr("TAPI_MATCH_SOURCE_DELIVERY") = ITapTrade::TAPI_MATCH_SOURCE_DELIVERY;
    parent.attr("TAPI_MATCH_SOURCE_ABANDON") = ITapTrade::TAPI_MATCH_SOURCE_ABANDON;
    parent.attr("TAPI_MATCH_SOURCE_CHANNEL") = ITapTrade::TAPI_MATCH_SOURCE_CHANNEL;
    parent.attr("TAPI_MATCH_SOURCE_ESUNNY_API") = ITapTrade::TAPI_MATCH_SOURCE_ESUNNY_API;
    parent.attr("TAPI_CLOSE_MODE_NONE") = ITapTrade::TAPI_CLOSE_MODE_NONE;
    parent.attr("TAPI_CLOSE_MODE_UNFINISHED") = ITapTrade::TAPI_CLOSE_MODE_UNFINISHED;
    parent.attr("TAPI_CLOSE_MODE_OPENCOVER") = ITapTrade::TAPI_CLOSE_MODE_OPENCOVER;
    parent.attr("TAPI_CLOSE_MODE_CLOSETODAY") = ITapTrade::TAPI_CLOSE_MODE_CLOSETODAY;
    parent.attr("TAPI_FUTURES_ALG_ZHUBI") = ITapTrade::TAPI_FUTURES_ALG_ZHUBI;
    parent.attr("TAPI_FUTURES_ALG_DINGSHI") = ITapTrade::TAPI_FUTURES_ALG_DINGSHI;
    parent.attr("TAPI_OPTION_ALG_FUTURES") = ITapTrade::TAPI_OPTION_ALG_FUTURES;
    parent.attr("TAPI_OPTION_ALG_OPTION") = ITapTrade::TAPI_OPTION_ALG_OPTION;
    parent.attr("SENDTYPE_SMS") = ITapTrade::SENDTYPE_SMS;
    parent.attr("SENDTYPE_MAIL") = ITapTrade::SENDTYPE_MAIL;
    parent.attr("TAPI_LWFlag_L") = ITapTrade::TAPI_LWFlag_L;
    parent.attr("TAPI_LWFlag_W") = ITapTrade::TAPI_LWFlag_W;
    parent.attr("TAPI_CASHINOUT_MODE_FEEADJUST") = ITapTrade::TAPI_CASHINOUT_MODE_FEEADJUST;
    parent.attr("TAPI_CASHINOUT_MODE_YKADJUST") = ITapTrade::TAPI_CASHINOUT_MODE_YKADJUST;
    parent.attr("TAPI_CASHINOUT_MODE_PLEDGE") = ITapTrade::TAPI_CASHINOUT_MODE_PLEDGE;
    parent.attr("TAPI_CASHINOUT_MODE_INTERESTREVENUE") = ITapTrade::TAPI_CASHINOUT_MODE_INTERESTREVENUE;
    parent.attr("TAPI_CASHINOUT_MODE_COLLECTIONCOST") = ITapTrade::TAPI_CASHINOUT_MODE_COLLECTIONCOST;
    parent.attr("TAPI_CASHINOUT_MODE_OTHER") = ITapTrade::TAPI_CASHINOUT_MODE_OTHER;
    parent.attr("TAPI_CASHINOUT_MODE_COMPANY") = ITapTrade::TAPI_CASHINOUT_MODE_COMPANY;
    parent.attr("TAPI_DEPOSITCALCULATE_MODE_FEN") = ITapTrade::TAPI_DEPOSITCALCULATE_MODE_FEN;
    parent.attr("TAPI_DEPOSITCALCULATE_MODE_SUO") = ITapTrade::TAPI_DEPOSITCALCULATE_MODE_SUO;
    parent.attr("TAPI_CMB_DIRECT_FIRST") = ITapTrade::TAPI_CMB_DIRECT_FIRST;
    parent.attr("TAPI_CMB_DIRECT_SECOND") = ITapTrade::TAPI_CMB_DIRECT_SECOND;
    parent.attr("TAPI_DELIVERY_MODE_GOODS") = ITapTrade::TAPI_DELIVERY_MODE_GOODS;
    parent.attr("TAPI_DELIVERY_MODE_CASH") = ITapTrade::TAPI_DELIVERY_MODE_CASH;
    parent.attr("TAPI_DELIVERY_MODE_EXECUTE") = ITapTrade::TAPI_DELIVERY_MODE_EXECUTE;
    parent.attr("TAPI_DELIVERY_MODE_ABANDON") = ITapTrade::TAPI_DELIVERY_MODE_ABANDON;
    parent.attr("TAPI_DELIVERY_MODE_HKF") = ITapTrade::TAPI_DELIVERY_MODE_HKF;
    parent.attr("TAPI_CONTRACT_TYPE_TRADEQUOTE") = ITapTrade::TAPI_CONTRACT_TYPE_TRADEQUOTE;
    parent.attr("TAPI_CONTRACT_TYPE_QUOTE") = ITapTrade::TAPI_CONTRACT_TYPE_QUOTE;
    parent.attr("TAPI_TACTICS_TYPE_NONE") = ITapTrade::TAPI_TACTICS_TYPE_NONE;
    parent.attr("TAPI_TACTICS_TYPE_READY") = ITapTrade::TAPI_TACTICS_TYPE_READY;
    parent.attr("TAPI_TACTICS_TYPE_ATUO") = ITapTrade::TAPI_TACTICS_TYPE_ATUO;
    parent.attr("TAPI_TACTICS_TYPE_CONDITION") = ITapTrade::TAPI_TACTICS_TYPE_CONDITION;
    parent.attr("APIORDER_INSERT") = ITapTrade::APIORDER_INSERT;
    parent.attr("APIORDER_MODIFY") = ITapTrade::APIORDER_MODIFY;
    parent.attr("APIORDER_DELETE") = ITapTrade::APIORDER_DELETE;
    parent.attr("APIORDER_SUSPEND") = ITapTrade::APIORDER_SUSPEND;
    parent.attr("APIORDER_ACTIVATE") = ITapTrade::APIORDER_ACTIVATE;
    parent.attr("APIORDER_SYSTEM_DELETE") = ITapTrade::APIORDER_SYSTEM_DELETE;
    parent.attr("TAPI_TRIGGER_CONDITION_NONE") = ITapTrade::TAPI_TRIGGER_CONDITION_NONE;
    parent.attr("TAPI_TRIGGER_CONDITION_GREAT") = ITapTrade::TAPI_TRIGGER_CONDITION_GREAT;
    parent.attr("TAPI_TRIGGER_CONDITION_LITTLE") = ITapTrade::TAPI_TRIGGER_CONDITION_LITTLE;
    parent.attr("TAPI_TRIGGER_PRICE_NONE") = ITapTrade::TAPI_TRIGGER_PRICE_NONE;
    parent.attr("TAPI_TRIGGER_PRICE_BUY") = ITapTrade::TAPI_TRIGGER_PRICE_BUY;
    parent.attr("TAPI_TRIGGER_PRICE_SELL") = ITapTrade::TAPI_TRIGGER_PRICE_SELL;
    parent.attr("TAPI_TRIGGER_PRICE_LAST") = ITapTrade::TAPI_TRIGGER_PRICE_LAST;
    parent.attr("TAPI_TRADE_STATE_BID") = ITapTrade::TAPI_TRADE_STATE_BID;
    parent.attr("TAPI_TRADE_STATE_MATCH") = ITapTrade::TAPI_TRADE_STATE_MATCH;
    parent.attr("TAPI_TRADE_STATE_CONTINUOUS") = ITapTrade::TAPI_TRADE_STATE_CONTINUOUS;
    parent.attr("TAPI_TRADE_STATE_PAUSED") = ITapTrade::TAPI_TRADE_STATE_PAUSED;
    parent.attr("TAPI_TRADE_STATE_CLOSE") = ITapTrade::TAPI_TRADE_STATE_CLOSE;
    parent.attr("TAPI_TRADE_STATE_DEALLAST") = ITapTrade::TAPI_TRADE_STATE_DEALLAST;
    parent.attr("TAPI_TRADE_STATE_GWDISCONNECT") = ITapTrade::TAPI_TRADE_STATE_GWDISCONNECT;
    parent.attr("TAPI_TRADE_STATE_UNKNOWN") = ITapTrade::TAPI_TRADE_STATE_UNKNOWN;
    parent.attr("TAPI_TRADE_STATE_INITIALIZE") = ITapTrade::TAPI_TRADE_STATE_INITIALIZE;
    parent.attr("TAPI_TRADE_STATE_READY") = ITapTrade::TAPI_TRADE_STATE_READY;
    parent.attr("TAPI_NOTICE_IGNORE_NONE") = ITapTrade::TAPI_NOTICE_IGNORE_NONE;
    parent.attr("TAPI_NOTICE_IGNORE_ALL") = ITapTrade::TAPI_NOTICE_IGNORE_ALL;
    parent.attr("TAPI_NOTICE_IGNORE_FUND") = ITapTrade::TAPI_NOTICE_IGNORE_FUND;
    parent.attr("TAPI_NOTICE_IGNORE_ORDER") = ITapTrade::TAPI_NOTICE_IGNORE_ORDER;
    parent.attr("TAPI_NOTICE_IGNORE_FILL") = ITapTrade::TAPI_NOTICE_IGNORE_FILL;
    parent.attr("TAPI_NOTICE_IGNORE_POSITION") = ITapTrade::TAPI_NOTICE_IGNORE_POSITION;
    parent.attr("TAPI_NOTICE_IGNORE_CLOSE") = ITapTrade::TAPI_NOTICE_IGNORE_CLOSE;
    parent.attr("TAPI_NOTICE_IGNORE_POSITIONPROFIT") = ITapTrade::TAPI_NOTICE_IGNORE_POSITIONPROFIT;
    parent.attr("TAPI_ORDER_QRY_TYPE_ALL") = ITapTrade::TAPI_ORDER_QRY_TYPE_ALL;
    parent.attr("TAPI_ORDER_QRY_TYPE_UNENDED") = ITapTrade::TAPI_ORDER_QRY_TYPE_UNENDED;
    parent.attr("TAPI_MSG_RECEIVER_ACCOUNTNO") = ITapTrade::TAPI_MSG_RECEIVER_ACCOUNTNO;
    parent.attr("TAPI_MSG_RECEIVER_ACCOUNTGROUPNO") = ITapTrade::TAPI_MSG_RECEIVER_ACCOUNTGROUPNO;
    parent.attr("TAPI_MSG_RECEIVER_ATTRIBUTE") = ITapTrade::TAPI_MSG_RECEIVER_ATTRIBUTE;
    parent.attr("TAPI_MSG_RECEIVER_USERNO") = ITapTrade::TAPI_MSG_RECEIVER_USERNO;
    parent.attr("TAPI_MSG_LEVEL_NORMAL") = ITapTrade::TAPI_MSG_LEVEL_NORMAL;
    parent.attr("TAPI_MSG_LEVEL_IMPORTANT") = ITapTrade::TAPI_MSG_LEVEL_IMPORTANT;
    parent.attr("TAPI_MSG_LEVEL_IMERGENCY") = ITapTrade::TAPI_MSG_LEVEL_IMERGENCY;
    parent.attr("TAPI_Msg_TYPE_MANAGER") = ITapTrade::TAPI_Msg_TYPE_MANAGER;
    parent.attr("TAPI_Msg_TYPE_RISKCONTROL") = ITapTrade::TAPI_Msg_TYPE_RISKCONTROL;
    parent.attr("TAPI_BILL_DATE") = ITapTrade::TAPI_BILL_DATE;
    parent.attr("TAPI_BILL_MONTH") = ITapTrade::TAPI_BILL_MONTH;
    parent.attr("TAPI_BILL_FILE_TXT") = ITapTrade::TAPI_BILL_FILE_TXT;
    parent.attr("TAPI_BILL_FILE_PDF") = ITapTrade::TAPI_BILL_FILE_PDF;
    parent.attr("SettleFlag_AutoSettle") = ITapTrade::SettleFlag_AutoSettle;
    parent.attr("SettleFlagh_Manual") = ITapTrade::SettleFlagh_Manual;
    parent.attr("TAPIERROR_LOGIN") = ITapTrade::TAPIERROR_LOGIN;
    parent.attr("TAPIERROR_LOGIN_USER") = ITapTrade::TAPIERROR_LOGIN_USER;
    parent.attr("TAPIERROR_LOGIN_DDA") = ITapTrade::TAPIERROR_LOGIN_DDA;
    parent.attr("TAPIERROR_LOGIN_LICENSE") = ITapTrade::TAPIERROR_LOGIN_LICENSE;
    parent.attr("TAPIERROR_LOGIN_MODULE") = ITapTrade::TAPIERROR_LOGIN_MODULE;
    parent.attr("TAPIERROR_LOGIN_FORCE") = ITapTrade::TAPIERROR_LOGIN_FORCE;
    parent.attr("TAPIERROR_LOGIN_STATE") = ITapTrade::TAPIERROR_LOGIN_STATE;
    parent.attr("TAPIERROR_LOGIN_PASS") = ITapTrade::TAPIERROR_LOGIN_PASS;
    parent.attr("TAPIERROR_LOGIN_RIGHT") = ITapTrade::TAPIERROR_LOGIN_RIGHT;
    parent.attr("TAPIERROR_LOGIN_COUNT") = ITapTrade::TAPIERROR_LOGIN_COUNT;
    parent.attr("TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES") = ITapTrade::TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES;
    parent.attr("TAPIERROR_LOGIN_FREEZE") = ITapTrade::TAPIERROR_LOGIN_FREEZE;
    parent.attr("TAPIERROR_LOGIN_TOFREEZE") = ITapTrade::TAPIERROR_LOGIN_TOFREEZE;
    parent.attr("TAPIERROR_LOGIN_ACCOUNTSTATE") = ITapTrade::TAPIERROR_LOGIN_ACCOUNTSTATE;
    parent.attr("TAPIERROR_LOGIN_SECCERTIFI") = ITapTrade::TAPIERROR_LOGIN_SECCERTIFI;
    parent.attr("TAPIERROR_LOGIN_NOSECONDSET") = ITapTrade::TAPIERROR_LOGIN_NOSECONDSET;
    parent.attr("TAPIERROR_LOGIN_NOTURSTHOST") = ITapTrade::TAPIERROR_LOGIN_NOTURSTHOST;
    parent.attr("TAPITAPIERROR_SECONDCERTIFICATION_FAIL") = ITapTrade::TAPITAPIERROR_SECONDCERTIFICATION_FAIL;
    parent.attr("TAPITAPIERROR_SECONDCERTIFICATION_TIMEOVER") = ITapTrade::TAPITAPIERROR_SECONDCERTIFICATION_TIMEOVER;
    parent.attr("TAPIERROR_CONN_DATABASE") = ITapTrade::TAPIERROR_CONN_DATABASE;
    parent.attr("TAPIERROR_OPER_DATABASE") = ITapTrade::TAPIERROR_OPER_DATABASE;
    parent.attr("TAPIERROR_NEED_ONETOONE") = ITapTrade::TAPIERROR_NEED_ONETOONE;
    parent.attr("TAPIERROR_EXIST_RELATEINFO") = ITapTrade::TAPIERROR_EXIST_RELATEINFO;
    parent.attr("TAPIERROR_EXIST_RELATEINFOOFGROUP") = ITapTrade::TAPIERROR_EXIST_RELATEINFOOFGROUP;
    parent.attr("TAPIERROR_USERPASSWORD_MOD_SOURCE") = ITapTrade::TAPIERROR_USERPASSWORD_MOD_SOURCE;
    parent.attr("TAPIERROR_USERPASSWORD_MOD_SAME") = ITapTrade::TAPIERROR_USERPASSWORD_MOD_SAME;
    parent.attr("TAPIERROR_USERPASSWORD_MOD_COMPLEXITY") = ITapTrade::TAPIERROR_USERPASSWORD_MOD_COMPLEXITY;
    parent.attr("TAPIERROR_CURRENCY_ONLY_ONEBASE") = ITapTrade::TAPIERROR_CURRENCY_ONLY_ONEBASE;
    parent.attr("TAPIERROR_CURRENCY_ONLY_USDHKD") = ITapTrade::TAPIERROR_CURRENCY_ONLY_USDHKD;
    parent.attr("TAPIERROR_ORDERINSERT_ACCOUNT") = ITapTrade::TAPIERROR_ORDERINSERT_ACCOUNT;
    parent.attr("TAPIERROR_ORDERINSERT_ACCOUNT_STATE") = ITapTrade::TAPIERROR_ORDERINSERT_ACCOUNT_STATE;
    parent.attr("TAPIERROR_ORDERINSERT_TRADECENT_ERROR") = ITapTrade::TAPIERROR_ORDERINSERT_TRADECENT_ERROR;
    parent.attr("TAPIERROR_ORDERINSERT_CONTRACT") = ITapTrade::TAPIERROR_ORDERINSERT_CONTRACT;
    parent.attr("TAPIERROR_ORDERINSERT_LME_NOTREADY") = ITapTrade::TAPIERROR_ORDERINSERT_LME_NOTREADY;
    parent.attr("TAPIERROR_ORDERINSERT_ERROR_ORDER_TYPE") = ITapTrade::TAPIERROR_ORDERINSERT_ERROR_ORDER_TYPE;
    parent.attr("TAPIERROR_ORDERINSERT_READY_TYPE_ERROR") = ITapTrade::TAPIERROR_ORDERINSERT_READY_TYPE_ERROR;
    parent.attr("TAPIERROR_ORDERINSERT_ORDER_TYPE_ERROR") = ITapTrade::TAPIERROR_ORDERINSERT_ORDER_TYPE_ERROR;
    parent.attr("TAPIERROR_ORDER_NOTRADE_ACCOUNT") = ITapTrade::TAPIERROR_ORDER_NOTRADE_ACCOUNT;
    parent.attr("TAPIERROR_ORDER_NOTRADE_COM_GROUP") = ITapTrade::TAPIERROR_ORDER_NOTRADE_COM_GROUP;
    parent.attr("TAPIERROR_ORDER_NOTRADE_ACC_CONTRACT") = ITapTrade::TAPIERROR_ORDER_NOTRADE_ACC_CONTRACT;
    parent.attr("TAPIERROR_ORDER_NOTRADE_SYSTEM") = ITapTrade::TAPIERROR_ORDER_NOTRADE_SYSTEM;
    parent.attr("TAPIERROR_ORDER_CLOSE_ACCOUNT") = ITapTrade::TAPIERROR_ORDER_CLOSE_ACCOUNT;
    parent.attr("TAPIERROR_ORDER_CLOSE_ACC_CONTRACT") = ITapTrade::TAPIERROR_ORDER_CLOSE_ACC_CONTRACT;
    parent.attr("TAPIERROR_ORDER_CLOSE_SYSTEM") = ITapTrade::TAPIERROR_ORDER_CLOSE_SYSTEM;
    parent.attr("TAPIERROR_ORDER_CLOSE_DAYS") = ITapTrade::TAPIERROR_ORDER_CLOSE_DAYS;
    parent.attr("TAPIERROR_ORDER_NOTRADE_RISK") = ITapTrade::TAPIERROR_ORDER_NOTRADE_RISK;
    parent.attr("TAPIERROR_ORDER_CLOSE_RISK") = ITapTrade::TAPIERROR_ORDER_CLOSE_RISK;
    parent.attr("TAPIERROR_ORDERINSERT_POSITIONMAX") = ITapTrade::TAPIERROR_ORDERINSERT_POSITIONMAX;
    parent.attr("TAPIERROR_ORDERINSERT_ONCEMAX") = ITapTrade::TAPIERROR_ORDERINSERT_ONCEMAX;
    parent.attr("TAPIERROR_ORDERINSERT_TRADEROUTE") = ITapTrade::TAPIERROR_ORDERINSERT_TRADEROUTE;
    parent.attr("TAPIERROR_ORDER_IN_MOD_PRICE_ERROR") = ITapTrade::TAPIERROR_ORDER_IN_MOD_PRICE_ERROR;
    parent.attr("TAPIERROR_ORDER_IN_GIVEUP_POS_MAX") = ITapTrade::TAPIERROR_ORDER_IN_GIVEUP_POS_MAX;
    parent.attr("TAPIERROR_UPPERCHANNEL_NOT_LOGIN") = ITapTrade::TAPIERROR_UPPERCHANNEL_NOT_LOGIN;
    parent.attr("TAPIERROR_UPPERCHANNEL_NOT_FOUND") = ITapTrade::TAPIERROR_UPPERCHANNEL_NOT_FOUND;
    parent.attr("TAPIERROR_ORDERINSERT_NOTENOUGHFUND") = ITapTrade::TAPIERROR_ORDERINSERT_NOTENOUGHFUND;
    parent.attr("TAPIERROR_ORDERINSERT_FEE") = ITapTrade::TAPIERROR_ORDERINSERT_FEE;
    parent.attr("TAPIERROR_ORDERINSERT_MARGIN") = ITapTrade::TAPIERROR_ORDERINSERT_MARGIN;
    parent.attr("TAPIERROR_ORDERINSERT_BASENOFUND") = ITapTrade::TAPIERROR_ORDERINSERT_BASENOFUND;
    parent.attr("TAPIERROR_ORDERINSERT_MARGINAMOUNT") = ITapTrade::TAPIERROR_ORDERINSERT_MARGINAMOUNT;
    parent.attr("TAPIERROR_ORDERINSERT_OPENRATIO") = ITapTrade::TAPIERROR_ORDERINSERT_OPENRATIO;
    parent.attr("TAPIERROR_ORDERINSERT_GROUP_OPENRATIO") = ITapTrade::TAPIERROR_ORDERINSERT_GROUP_OPENRATIO;
    parent.attr("TAPIERROR_ORDERINSERT_RISKARRAY") = ITapTrade::TAPIERROR_ORDERINSERT_RISKARRAY;
    parent.attr("TAPIERROR_ORDERDELETE_NOT_SYSNO") = ITapTrade::TAPIERROR_ORDERDELETE_NOT_SYSNO;
    parent.attr("TAPIERROR_ORDERDELETE_NOT_STATE") = ITapTrade::TAPIERROR_ORDERDELETE_NOT_STATE;
    parent.attr("TAPIERROR_ORDERDELETE_NO_INPUT") = ITapTrade::TAPIERROR_ORDERDELETE_NO_INPUT;
    parent.attr("TAPIERROR_ORDERMODIFY_NOT_STATE") = ITapTrade::TAPIERROR_ORDERMODIFY_NOT_STATE;
    parent.attr("TAPIERROR_ORDERMODIFY_BACK_INPUT") = ITapTrade::TAPIERROR_ORDERMODIFY_BACK_INPUT;
    parent.attr("TAPIERROR_ORDERMODIFY_RISK_ORDER") = ITapTrade::TAPIERROR_ORDERMODIFY_RISK_ORDER;
    parent.attr("TAPIERROR_ORDERMODIFY_ERROR_QTY") = ITapTrade::TAPIERROR_ORDERMODIFY_ERROR_QTY;
    parent.attr("TAPIERROR_ORDERMODIFY_ERROR_READY") = ITapTrade::TAPIERROR_ORDERMODIFY_ERROR_READY;
    parent.attr("TAPIERROR_ORDERINPUT_CANNOTMOVE") = ITapTrade::TAPIERROR_ORDERINPUT_CANNOTMOVE;
    parent.attr("TAPIERROR_ORDERINPUT_REPEAT") = ITapTrade::TAPIERROR_ORDERINPUT_REPEAT;
    parent.attr("TAPIERROR_CONTRACT_QUOTE") = ITapTrade::TAPIERROR_CONTRACT_QUOTE;
    parent.attr("TAPIERROR_UPPER_ONCEMAX") = ITapTrade::TAPIERROR_UPPER_ONCEMAX;
    parent.attr("TAPIERROR_UPPER_POSITIONMAX") = ITapTrade::TAPIERROR_UPPER_POSITIONMAX;
    parent.attr("TAPIERROR_ORDERINSERT_CLOSEMODE") = ITapTrade::TAPIERROR_ORDERINSERT_CLOSEMODE;
    parent.attr("TAPIERROR_CLOSE_ORDER") = ITapTrade::TAPIERROR_CLOSE_ORDER;
    parent.attr("TAPIERROR_CLOSE_MATCH") = ITapTrade::TAPIERROR_CLOSE_MATCH;
    parent.attr("TAPIERROR_MOD_DEL_NO_ORDER") = ITapTrade::TAPIERROR_MOD_DEL_NO_ORDER;
    parent.attr("TAPIERROR_MOD_DEL_GATEWAY_DISCON") = ITapTrade::TAPIERROR_MOD_DEL_GATEWAY_DISCON;
    parent.attr("TAPIERROR_MATCHINPUT_REPEAT") = ITapTrade::TAPIERROR_MATCHINPUT_REPEAT;
    parent.attr("TAPIERROR_MATCHINPUT_NO_ORDER") = ITapTrade::TAPIERROR_MATCHINPUT_NO_ORDER;
    parent.attr("TAPIERROR_MATCHINPUT_NO_CONTRACT") = ITapTrade::TAPIERROR_MATCHINPUT_NO_CONTRACT;
    parent.attr("TAPIERROR_MATCHINPUT_PARM_ERROR") = ITapTrade::TAPIERROR_MATCHINPUT_PARM_ERROR;
    parent.attr("TAPIERROR_MATCHINPUT_OSTATE_ERROR") = ITapTrade::TAPIERROR_MATCHINPUT_OSTATE_ERROR;
    parent.attr("TAPIERROR_MATCHREMOVE_NO_MATCH") = ITapTrade::TAPIERROR_MATCHREMOVE_NO_MATCH;
    parent.attr("TAPIERROR_MATCHREMOVE_STATE_ERROR") = ITapTrade::TAPIERROR_MATCHREMOVE_STATE_ERROR;
    parent.attr("TAPIERROR_ORDERINPUT_STATE_ERROR") = ITapTrade::TAPIERROR_ORDERINPUT_STATE_ERROR;
    parent.attr("TAPIERROR_ORDERINPUT_MOD_ERROR") = ITapTrade::TAPIERROR_ORDERINPUT_MOD_ERROR;
    parent.attr("TAPIERROR_ORDERREMOVE_ERROR") = ITapTrade::TAPIERROR_ORDERREMOVE_ERROR;
    parent.attr("TAPIERROR_ORDERINPUT_MOD_STATE_ERROR") = ITapTrade::TAPIERROR_ORDERINPUT_MOD_STATE_ERROR;
    parent.attr("TAPIERROR_ORDEREXCHANGE_STATE_ERROR") = ITapTrade::TAPIERROR_ORDEREXCHANGE_STATE_ERROR;
    parent.attr("TAPIERROR_ORDERREMOVE_NOT_ERROR") = ITapTrade::TAPIERROR_ORDERREMOVE_NOT_ERROR;
    parent.attr("TAPIERROR_ORDERMARKET_DELETE_NOTFOUND") = ITapTrade::TAPIERROR_ORDERMARKET_DELETE_NOTFOUND;
    parent.attr("TAPIERROR_ORDERMARKET_DEL_ACCOUNT_NE") = ITapTrade::TAPIERROR_ORDERMARKET_DEL_ACCOUNT_NE;
    parent.attr("TAPIERROR_ORDERMARKET_DEL_COMMODITY_NE") = ITapTrade::TAPIERROR_ORDERMARKET_DEL_COMMODITY_NE;
    parent.attr("TAPIERROR_ORDERMARKET_DEL_CONTRACT_NE") = ITapTrade::TAPIERROR_ORDERMARKET_DEL_CONTRACT_NE;
    parent.attr("TAPIERROR_ORDERMARKET_DEL_SIDE_EQ") = ITapTrade::TAPIERROR_ORDERMARKET_DEL_SIDE_EQ;
    parent.attr("TAPIERROR_ORDERMARKET_DEL_SIDE_ERROR") = ITapTrade::TAPIERROR_ORDERMARKET_DEL_SIDE_ERROR;
    parent.attr("TAPIERROR_ORDERMARKET_OTHER_SIDE_ERROR") = ITapTrade::TAPIERROR_ORDERMARKET_OTHER_SIDE_ERROR;
    parent.attr("TAPIERROR_ORDERACTIVATE_NOTFOUND_ERROR") = ITapTrade::TAPIERROR_ORDERACTIVATE_NOTFOUND_ERROR;
    parent.attr("TAPIERROR_ORDERACTIVATE_STATE_ERROR") = ITapTrade::TAPIERROR_ORDERACTIVATE_STATE_ERROR;
    parent.attr("TAPIERROR_GW_NOT_READY") = ITapTrade::TAPIERROR_GW_NOT_READY;
    parent.attr("TAPIERROR_GW_INVALID_COMMODITY") = ITapTrade::TAPIERROR_GW_INVALID_COMMODITY;
    parent.attr("TAPIERROR_GW_INVALID_CONTRACT") = ITapTrade::TAPIERROR_GW_INVALID_CONTRACT;
    parent.attr("TAPIERROR_GW_INVALID_FIELD") = ITapTrade::TAPIERROR_GW_INVALID_FIELD;
    parent.attr("TAPIERROR_GW_INVALID_PRICE") = ITapTrade::TAPIERROR_GW_INVALID_PRICE;
    parent.attr("TAPIERROR_GW_INVALID_VOLUME") = ITapTrade::TAPIERROR_GW_INVALID_VOLUME;
    parent.attr("TAPIERROR_GW_INVALID_TYPE") = ITapTrade::TAPIERROR_GW_INVALID_TYPE;
    parent.attr("TAPIERROR_GW_INVALID_MODE") = ITapTrade::TAPIERROR_GW_INVALID_MODE;
    parent.attr("TAPIERROR_GW_ORDER_NOT_EXIST") = ITapTrade::TAPIERROR_GW_ORDER_NOT_EXIST;
    parent.attr("TAPIERROR_GW_SEND_FAIL") = ITapTrade::TAPIERROR_GW_SEND_FAIL;
    parent.attr("TAPIERROR_GW_REJ_BYUPPER") = ITapTrade::TAPIERROR_GW_REJ_BYUPPER;
    parent.attr("TAPIERROR_TRADEFRONT_MODULETYPEERR") = ITapTrade::TAPIERROR_TRADEFRONT_MODULETYPEERR;
    parent.attr("TAPIERROR_TRADEFRONT_TOOMANYDATA") = ITapTrade::TAPIERROR_TRADEFRONT_TOOMANYDATA;
    parent.attr("TAPIERROR_TRADEFRONT_NODATA") = ITapTrade::TAPIERROR_TRADEFRONT_NODATA;
    parent.attr("TAPIERROT_TRADEFRONT_NOUSER") = ITapTrade::TAPIERROT_TRADEFRONT_NOUSER;
    parent.attr("TAPIERROR_TRADEFRONT_DISCONNECT_TRADE") = ITapTrade::TAPIERROR_TRADEFRONT_DISCONNECT_TRADE;
    parent.attr("TAPIERROR_TRADEFRONT_DISCONNECT_MANAGE") = ITapTrade::TAPIERROR_TRADEFRONT_DISCONNECT_MANAGE;
    parent.attr("TAPIERROR_TRADEFRONT_ACCOUNT") = ITapTrade::TAPIERROR_TRADEFRONT_ACCOUNT;
    parent.attr("TAPIERROR_TRADEFRONT_ORDER") = ITapTrade::TAPIERROR_TRADEFRONT_ORDER;
    parent.attr("TAPIERROR_TRADEFRONT_FREQUENCY") = ITapTrade::TAPIERROR_TRADEFRONT_FREQUENCY;
    parent.attr("TAPIERROR_TRADEFRONT_RUFUSE") = ITapTrade::TAPIERROR_TRADEFRONT_RUFUSE;
    parent.attr("TAPIERROR_TRADEFRONT_SELFMATCH") = ITapTrade::TAPIERROR_TRADEFRONT_SELFMATCH;
    parent.attr("TAPIERROR_SUCCEED") = ITapTrade::TAPIERROR_SUCCEED;
    parent.attr("TAPIERROR_ConnectFail") = ITapTrade::TAPIERROR_ConnectFail;
    parent.attr("TAPIERROR_LinkAuthFail") = ITapTrade::TAPIERROR_LinkAuthFail;
    parent.attr("TAPIERROR_HostUnavailable") = ITapTrade::TAPIERROR_HostUnavailable;
    parent.attr("TAPIERROR_SendDataError") = ITapTrade::TAPIERROR_SendDataError;
    parent.attr("TAPIERROR_TestIDError") = ITapTrade::TAPIERROR_TestIDError;
    parent.attr("TAPIERROR_NotReadyTestNetwork") = ITapTrade::TAPIERROR_NotReadyTestNetwork;
    parent.attr("TAPIERROR_CurTestNotOver") = ITapTrade::TAPIERROR_CurTestNotOver;
    parent.attr("TAPIERROR_NOFrontAvailable") = ITapTrade::TAPIERROR_NOFrontAvailable;
    parent.attr("TAPIERROR_DataPathAvaiable") = ITapTrade::TAPIERROR_DataPathAvaiable;
    parent.attr("TAPIERROR_RepeatLogin") = ITapTrade::TAPIERROR_RepeatLogin;
    parent.attr("TAPIERROR_InnerError") = ITapTrade::TAPIERROR_InnerError;
    parent.attr("TAPIERROR_LastReqNotFinish") = ITapTrade::TAPIERROR_LastReqNotFinish;
    parent.attr("TAPIERROR_InputValueError") = ITapTrade::TAPIERROR_InputValueError;
    parent.attr("TAPIERROR_AuthCode_Invalid") = ITapTrade::TAPIERROR_AuthCode_Invalid;
    parent.attr("TAPIERROR_AuthCode_Expired") = ITapTrade::TAPIERROR_AuthCode_Expired;
    parent.attr("TAPIERROR_AuthCode_TypeNotMatch") = ITapTrade::TAPIERROR_AuthCode_TypeNotMatch;
    parent.attr("TAPIERROR_API_NotReady") = ITapTrade::TAPIERROR_API_NotReady;
    parent.attr("TAPIERROR_UDP_LISTEN_FAILED") = ITapTrade::TAPIERROR_UDP_LISTEN_FAILED;
    parent.attr("TAPIERROR_UDP_LISTENING") = ITapTrade::TAPIERROR_UDP_LISTENING;
    parent.attr("TAPIERROR_NotImplemented") = ITapTrade::TAPIERROR_NotImplemented;
    parent.attr("TAPIERROR_CallOneTimeOnly") = ITapTrade::TAPIERROR_CallOneTimeOnly;
    parent.attr("TAPIERROR_ORDER_FREQUENCY") = ITapTrade::TAPIERROR_ORDER_FREQUENCY;
    parent.attr("TAPIERROR_RENTQRY_TOOFAST") = ITapTrade::TAPIERROR_RENTQRY_TOOFAST;
    parent.attr("TAPIERROR_CALL_NOCONDITION") = ITapTrade::TAPIERROR_CALL_NOCONDITION;
    parent.attr("TAPIERROR_ORDER_NOTFOUND") = ITapTrade::TAPIERROR_ORDER_NOTFOUND;
    parent.attr("TAPIERROR_LOGPATH_EMPTY") = ITapTrade::TAPIERROR_LOGPATH_EMPTY;
    parent.attr("TAPIERROR_LOGPATH_FAILOPEN") = ITapTrade::TAPIERROR_LOGPATH_FAILOPEN;
    parent.attr("TAPIERROR_RIGHT_TRADER") = ITapTrade::TAPIERROR_RIGHT_TRADER;
    parent.attr("TAPIERROR_RIGHT_ORDERINPUT") = ITapTrade::TAPIERROR_RIGHT_ORDERINPUT;
    parent.attr("TAPIERROR_RIGHT_LOCALOPERATION") = ITapTrade::TAPIERROR_RIGHT_LOCALOPERATION;
    parent.attr("TAPIERROR_RIGHT_ORDERTRANSFER") = ITapTrade::TAPIERROR_RIGHT_ORDERTRANSFER;
    parent.attr("TAPIERROR_FILLINPUT_SYSTEMNO") = ITapTrade::TAPIERROR_FILLINPUT_SYSTEMNO;
    parent.attr("TAPIERROR_FILLREMOVE_MATCHNO") = ITapTrade::TAPIERROR_FILLREMOVE_MATCHNO;
    parent.attr("TAPIERROR_FILLREQMOVE_NOFUND") = ITapTrade::TAPIERROR_FILLREQMOVE_NOFUND;
    parent.attr("TAPIERROR_LOCALMODIFY_ACCOUNT") = ITapTrade::TAPIERROR_LOCALMODIFY_ACCOUNT;
    parent.attr("TAPIERROR_LOCALTRANSFER_ACCOUNT") = ITapTrade::TAPIERROR_LOCALTRANSFER_ACCOUNT;
    parent.attr("TAPIERROR_INPUTERROR_PHONE") = ITapTrade::TAPIERROR_INPUTERROR_PHONE;
    parent.attr("TAPIERROR_ERROR_CONTACT") = ITapTrade::TAPIERROR_ERROR_CONTACT;
    parent.attr("TAPIERROR_ERROR_REJESTVERTIFICATE") = ITapTrade::TAPIERROR_ERROR_REJESTVERTIFICATE;
    parent.attr("TAPIERROR_RIGHT_SETPASSWORD") = ITapTrade::TAPIERROR_RIGHT_SETPASSWORD;
    parent.attr("TAPIERROR_RISK_OPERERROR") = ITapTrade::TAPIERROR_RISK_OPERERROR;
    parent.attr("TAPIERROR_ORDER_MODACCOUNT") = ITapTrade::TAPIERROR_ORDER_MODACCOUNT;
    parent.attr("TAPIERROR_INPUTERROR_NULL") = ITapTrade::TAPIERROR_INPUTERROR_NULL;
    parent.attr("TAPIERROR_INPUTERROR_TAPIYNFLAG") = ITapTrade::TAPIERROR_INPUTERROR_TAPIYNFLAG;
    parent.attr("TAPIERROR_INPUTERROR_TAPILOGLEVEL") = ITapTrade::TAPIERROR_INPUTERROR_TAPILOGLEVEL;
    parent.attr("TAPIERROR_INPUTERROR_TAPICommodityType") = ITapTrade::TAPIERROR_INPUTERROR_TAPICommodityType;
    parent.attr("TAPIERROR_INPUTERROR_TAPICallOrPutFlagType") = ITapTrade::TAPIERROR_INPUTERROR_TAPICallOrPutFlagType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBucketDateFlag") = ITapTrade::TAPIERROR_INPUTERROR_TAPIBucketDateFlag;
    parent.attr("TAPIERROR_INPUTERROR_TAPIHisQuoteType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIHisQuoteType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIAccountType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIAccountType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIUserTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIUserTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIAccountState") = ITapTrade::TAPIERROR_INPUTERROR_TAPIAccountState;
    parent.attr("TAPIERROR_INPUTERROR_TAPIAccountFamilyType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIAccountFamilyType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOrderTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderSourceType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOrderSourceType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITimeInForceType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITimeInForceType;
    parent.attr("TAPIERROR_INPUTERROR_TAPISideType") = ITapTrade::TAPIERROR_INPUTERROR_TAPISideType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIPositionEffectType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIPositionEffectType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIHedgeFlagType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIHedgeFlagType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderStateType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOrderStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPICalculateModeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPICalculateModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMatchSourceType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIMatchSourceType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOpenCloseModeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOpenCloseModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIFutureAlgType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIFutureAlgType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOptionAlgType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOptionAlgType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBankAccountStateType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIBankAccountStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBankAccountSwapStateType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIBankAccountSwapStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBankAccountTransferStateType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIBankAccountTransferStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPICmbDirectType") = ITapTrade::TAPIERROR_INPUTERROR_TAPICmbDirectType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIDeliveryModeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIDeliveryModeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIContractTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIContractTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIPartyTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIPartyTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIPartyCertificateTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIPartyCertificateTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMsgReceiverType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIMsgReceiverType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMsgTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIMsgTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMsgLevelType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIMsgLevelType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITransferDirectType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITransferDirectType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITransferStateType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITransferStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITransferTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITransferTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITransferDeviceIDType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITransferDeviceIDType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITacticsTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITacticsTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIORDERACT") = ITapTrade::TAPIERROR_INPUTERROR_TAPIORDERACT;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBillTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIBillTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIBillFileTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIBillFileTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOFFFlagType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOFFFlagType;
    parent.attr("TAPIERROR_INPUTERROR_TAPICashAdjustTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPICashAdjustTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITriggerConditionType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITriggerConditionType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPITradingStateType") = ITapTrade::TAPIERROR_INPUTERROR_TAPITradingStateType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIMarketLevelType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIMarketLevelType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIOrderQryTypeType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIOrderQryTypeType;
    parent.attr("TAPIERROR_INPUTERROR_TAPIClientID") = ITapTrade::TAPIERROR_INPUTERROR_TAPIClientID;
    parent.attr("TAPIERROR_INPUTERROR_QryHisQuoteParam") = ITapTrade::TAPIERROR_INPUTERROR_QryHisQuoteParam;
    parent.attr("TAPIERROR_INPUTERROR_TAPIIncludeNAN") = ITapTrade::TAPIERROR_INPUTERROR_TAPIIncludeNAN;
    parent.attr("TAPIERROR_INPUTERROR_TAPIExpireTime") = ITapTrade::TAPIERROR_INPUTERROR_TAPIExpireTime;
    parent.attr("TAPIERROR_INPUTERROR_TAPIPasswordType") = ITapTrade::TAPIERROR_INPUTERROR_TAPIPasswordType;
    parent.attr("TAPIERROR_INPUTERROR_TAPISettleFlagType") = ITapTrade::TAPIERROR_INPUTERROR_TAPISettleFlagType;
    parent.attr("TAPIERROR_DISCONNECT_CLOSE_INIT") = ITapTrade::TAPIERROR_DISCONNECT_CLOSE_INIT;
    parent.attr("TAPIERROR_DISCONNECT_CLOSE_PASS") = ITapTrade::TAPIERROR_DISCONNECT_CLOSE_PASS;
    parent.attr("TAPIERROR_DISCONNECT_READ_ERROR") = ITapTrade::TAPIERROR_DISCONNECT_READ_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_WRITE_ERROR") = ITapTrade::TAPIERROR_DISCONNECT_WRITE_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_BUF_FULL") = ITapTrade::TAPIERROR_DISCONNECT_BUF_FULL;
    parent.attr("TAPIERROR_DISCONNECT_IOCP_ERROR") = ITapTrade::TAPIERROR_DISCONNECT_IOCP_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_PARSE_ERROR") = ITapTrade::TAPIERROR_DISCONNECT_PARSE_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_CONNECT_TIMEOUT") = ITapTrade::TAPIERROR_DISCONNECT_CONNECT_TIMEOUT;
    parent.attr("TAPIERROR_DISCONNECT_INIT_ERROR") = ITapTrade::TAPIERROR_DISCONNECT_INIT_ERROR;
    parent.attr("TAPIERROR_DISCONNECT_HAS_CONNECTED") = ITapTrade::TAPIERROR_DISCONNECT_HAS_CONNECTED;
    parent.attr("TAPIERROR_DISCONNECT_HAS_EXIT") = ITapTrade::TAPIERROR_DISCONNECT_HAS_EXIT;
    parent.attr("TAPIERROR_DISCONNECT_TRY_LATER") = ITapTrade::TAPIERROR_DISCONNECT_TRY_LATER;
    module_vnitap::cross.record_assign(parent, "TapAPIOrderDeactivateReq", "ITapTrade::TapAPIOrderDeactivateReq", "::ITapTrade::TapAPIOrderCancelReq");
    module_vnitap::cross.record_assign(parent, "TapAPIOrderActivateReq", "ITapTrade::TapAPIOrderActivateReq", "::ITapTrade::TapAPIOrderCancelReq");
    module_vnitap::cross.record_assign(parent, "TapAPIOrderDeleteReq", "ITapTrade::TapAPIOrderDeleteReq", "::ITapTrade::TapAPIOrderCancelReq");
    module_vnitap::cross.record_assign(parent, "TapAPIHisOrderProcessQryRsp", "ITapTrade::TapAPIHisOrderProcessQryRsp", "::ITapTrade::TapAPIHisOrderQryRsp");
    module_vnitap::cross.record_assign(parent, "TapAPIOrderMarketDeleteRsp", "ITapTrade::TapAPIOrderMarketDeleteRsp", "::ITapTrade::TapAPIOrderMarketInsertRsp");
    module_vnitap::cross.record_assign(parent, "TapAPIOrderLocalInputRsp", "ITapTrade::TapAPIOrderLocalInputRsp", "::ITapTrade::TapAPIOrderInfo");
    module_vnitap::cross.record_assign(parent, "TapAPIOrderLocalModifyRsp", "ITapTrade::TapAPIOrderLocalModifyRsp", "::ITapTrade::TapAPIOrderInfo");
    module_vnitap::cross.record_assign(parent, "TapAPIOrderLocalTransferRsp", "ITapTrade::TapAPIOrderLocalTransferRsp", "::ITapTrade::TapAPIOrderInfo");
    module_vnitap::cross.record_assign(parent, "TapAPIFillLocalInputRsp", "ITapTrade::TapAPIFillLocalInputRsp", "::ITapTrade::TapAPIFillLocalInputReq");
    module_vnitap::cross.record_assign(parent, "TapAPIFillLocalRemoveRsp", "ITapTrade::TapAPIFillLocalRemoveRsp", "::ITapTrade::TapAPIFillLocalRemoveReq");
    generate_caster_ITapTrade(parent);
}
