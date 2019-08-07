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

#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"


void generate_ITapTrade_typedefs(pybind11::module & parent)
{
    // ITapTrade::TapAPIOrderDeactivateReq
    module_vntap::cross.record_assign(parent, "TapAPIOrderDeactivateReq", "ITapTrade::TapAPIOrderDeactivateReq", "::ITapTrade::TapAPIOrderCancelReq");
    // ITapTrade::TapAPIOrderActivateReq
    module_vntap::cross.record_assign(parent, "TapAPIOrderActivateReq", "ITapTrade::TapAPIOrderActivateReq", "::ITapTrade::TapAPIOrderCancelReq");
    // ITapTrade::TapAPIOrderDeleteReq
    module_vntap::cross.record_assign(parent, "TapAPIOrderDeleteReq", "ITapTrade::TapAPIOrderDeleteReq", "::ITapTrade::TapAPIOrderCancelReq");
    // ITapTrade::TapAPIHisOrderProcessQryRsp
    module_vntap::cross.record_assign(parent, "TapAPIHisOrderProcessQryRsp", "ITapTrade::TapAPIHisOrderProcessQryRsp", "::ITapTrade::TapAPIHisOrderQryRsp");
    // ITapTrade::TapAPIOrderMarketDeleteRsp
    module_vntap::cross.record_assign(parent, "TapAPIOrderMarketDeleteRsp", "ITapTrade::TapAPIOrderMarketDeleteRsp", "::ITapTrade::TapAPIOrderMarketInsertRsp");
    // ITapTrade::TapAPIOrderLocalInputRsp
    module_vntap::cross.record_assign(parent, "TapAPIOrderLocalInputRsp", "ITapTrade::TapAPIOrderLocalInputRsp", "::ITapTrade::TapAPIOrderInfo");
    // ITapTrade::TapAPIOrderLocalModifyRsp
    module_vntap::cross.record_assign(parent, "TapAPIOrderLocalModifyRsp", "ITapTrade::TapAPIOrderLocalModifyRsp", "::ITapTrade::TapAPIOrderInfo");
    // ITapTrade::TapAPIOrderLocalTransferRsp
    module_vntap::cross.record_assign(parent, "TapAPIOrderLocalTransferRsp", "ITapTrade::TapAPIOrderLocalTransferRsp", "::ITapTrade::TapAPIOrderInfo");
    // ITapTrade::TapAPIFillLocalInputRsp
    module_vntap::cross.record_assign(parent, "TapAPIFillLocalInputRsp", "ITapTrade::TapAPIFillLocalInputRsp", "::ITapTrade::TapAPIFillLocalInputReq");
    // ITapTrade::TapAPIFillLocalRemoveRsp
    module_vntap::cross.record_assign(parent, "TapAPIFillLocalRemoveRsp", "ITapTrade::TapAPIFillLocalRemoveRsp", "::ITapTrade::TapAPIFillLocalRemoveReq");
}
void generate_caster_ITapTrade(pybind11::object & parent)
{
    struct caster: c2py::caster{};
    auto c = c2py::caster::bind<caster>(parent, "caster"); 
    // ITapTrade::TapAPIApplicationInfo
    c2py::caster::try_generate<ITapTrade::TapAPIApplicationInfo>(c, "toTapAPIApplicationInfo");
    // ITapTrade::TapAPICommodity
    c2py::caster::try_generate<ITapTrade::TapAPICommodity>(c, "toTapAPICommodity");
    // ITapTrade::TapAPIContract
    c2py::caster::try_generate<ITapTrade::TapAPIContract>(c, "toTapAPIContract");
    // ITapTrade::TapAPIExchangeInfo
    c2py::caster::try_generate<ITapTrade::TapAPIExchangeInfo>(c, "toTapAPIExchangeInfo");
    // ITapTrade::TapAPIChangePasswordReq
    c2py::caster::try_generate<ITapTrade::TapAPIChangePasswordReq>(c, "toTapAPIChangePasswordReq");
    // ITapTrade::TapAPIAuthPasswordReq
    c2py::caster::try_generate<ITapTrade::TapAPIAuthPasswordReq>(c, "toTapAPIAuthPasswordReq");
    // ITapTrade::TapAPITradeLoginAuth
    c2py::caster::try_generate<ITapTrade::TapAPITradeLoginAuth>(c, "toTapAPITradeLoginAuth");
    // ITapTrade::TapAPITradeLoginRspInfo
    c2py::caster::try_generate<ITapTrade::TapAPITradeLoginRspInfo>(c, "toTapAPITradeLoginRspInfo");
    // ITapTrade::TapAPIRequestVertificateCodeRsp
    c2py::caster::try_generate<ITapTrade::TapAPIRequestVertificateCodeRsp>(c, "toTapAPIRequestVertificateCodeRsp");
    // ITapTrade::TapAPIAccQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIAccQryReq>(c, "toTapAPIAccQryReq");
    // ITapTrade::TapAPIAccountInfo
    c2py::caster::try_generate<ITapTrade::TapAPIAccountInfo>(c, "toTapAPIAccountInfo");
    // ITapTrade::TapAPINewOrder
    c2py::caster::try_generate<ITapTrade::TapAPINewOrder>(c, "toTapAPINewOrder");
    // ITapTrade::TapAPIOrderInfo
    c2py::caster::try_generate<ITapTrade::TapAPIOrderInfo>(c, "toTapAPIOrderInfo");
    // ITapTrade::TapAPIOrderInfoNotice
    c2py::caster::try_generate<ITapTrade::TapAPIOrderInfoNotice>(c, "toTapAPIOrderInfoNotice");
    // ITapTrade::TapAPIOrderActionRsp
    c2py::caster::try_generate<ITapTrade::TapAPIOrderActionRsp>(c, "toTapAPIOrderActionRsp");
    // ITapTrade::TapAPIAmendOrder
    c2py::caster::try_generate<ITapTrade::TapAPIAmendOrder>(c, "toTapAPIAmendOrder");
    // ITapTrade::TapAPIOrderCancelReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderCancelReq>(c, "toTapAPIOrderCancelReq");
    // ITapTrade::TapAPIOrderQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderQryReq>(c, "toTapAPIOrderQryReq");
    // ITapTrade::TapAPIOrderProcessQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderProcessQryReq>(c, "toTapAPIOrderProcessQryReq");
    // ITapTrade::TapAPIFillQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIFillQryReq>(c, "toTapAPIFillQryReq");
    // ITapTrade::TapAPIFillInfo
    c2py::caster::try_generate<ITapTrade::TapAPIFillInfo>(c, "toTapAPIFillInfo");
    // ITapTrade::TapAPICloseQryReq
    c2py::caster::try_generate<ITapTrade::TapAPICloseQryReq>(c, "toTapAPICloseQryReq");
    // ITapTrade::TapAPICloseInfo
    c2py::caster::try_generate<ITapTrade::TapAPICloseInfo>(c, "toTapAPICloseInfo");
    // ITapTrade::TapAPIPositionQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIPositionQryReq>(c, "toTapAPIPositionQryReq");
    // ITapTrade::TapAPIPositionInfo
    c2py::caster::try_generate<ITapTrade::TapAPIPositionInfo>(c, "toTapAPIPositionInfo");
    // ITapTrade::TapAPIPositionProfit
    c2py::caster::try_generate<ITapTrade::TapAPIPositionProfit>(c, "toTapAPIPositionProfit");
    // ITapTrade::TapAPIPositionProfitNotice
    c2py::caster::try_generate<ITapTrade::TapAPIPositionProfitNotice>(c, "toTapAPIPositionProfitNotice");
    // ITapTrade::TapAPIPositionSummary
    c2py::caster::try_generate<ITapTrade::TapAPIPositionSummary>(c, "toTapAPIPositionSummary");
    // ITapTrade::TapAPIFundReq
    c2py::caster::try_generate<ITapTrade::TapAPIFundReq>(c, "toTapAPIFundReq");
    // ITapTrade::TapAPIFundData
    c2py::caster::try_generate<ITapTrade::TapAPIFundData>(c, "toTapAPIFundData");
    // ITapTrade::TapAPICommodityInfo
    c2py::caster::try_generate<ITapTrade::TapAPICommodityInfo>(c, "toTapAPICommodityInfo");
    // ITapTrade::TapAPITradeContractInfo
    c2py::caster::try_generate<ITapTrade::TapAPITradeContractInfo>(c, "toTapAPITradeContractInfo");
    // ITapTrade::TapAPICurrencyInfo
    c2py::caster::try_generate<ITapTrade::TapAPICurrencyInfo>(c, "toTapAPICurrencyInfo");
    // ITapTrade::TapAPITradeMessageReq
    c2py::caster::try_generate<ITapTrade::TapAPITradeMessageReq>(c, "toTapAPITradeMessageReq");
    // ITapTrade::TapAPITradeMessage
    c2py::caster::try_generate<ITapTrade::TapAPITradeMessage>(c, "toTapAPITradeMessage");
    // ITapTrade::TapAPIBillQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIBillQryReq>(c, "toTapAPIBillQryReq");
    // ITapTrade::TapAPIBillQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIBillQryRsp>(c, "toTapAPIBillQryRsp");
    // ITapTrade::TapAPIHisOrderQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIHisOrderQryReq>(c, "toTapAPIHisOrderQryReq");
    // ITapTrade::TapAPIHisOrderQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIHisOrderQryRsp>(c, "toTapAPIHisOrderQryRsp");
    // ITapTrade::TapAPIHisMatchQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIHisMatchQryReq>(c, "toTapAPIHisMatchQryReq");
    // ITapTrade::TapAPIHisMatchQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIHisMatchQryRsp>(c, "toTapAPIHisMatchQryRsp");
    // ITapTrade::TapAPIHisOrderProcessQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIHisOrderProcessQryReq>(c, "toTapAPIHisOrderProcessQryReq");
    // ITapTrade::TapAPIHisPositionQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIHisPositionQryReq>(c, "toTapAPIHisPositionQryReq");
    // ITapTrade::TapAPIHisPositionQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIHisPositionQryRsp>(c, "toTapAPIHisPositionQryRsp");
    // ITapTrade::TapAPIHisDeliveryQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIHisDeliveryQryReq>(c, "toTapAPIHisDeliveryQryReq");
    // ITapTrade::TapAPIHisDeliveryQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIHisDeliveryQryRsp>(c, "toTapAPIHisDeliveryQryRsp");
    // ITapTrade::TapAPIAccountCashAdjustQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIAccountCashAdjustQryReq>(c, "toTapAPIAccountCashAdjustQryReq");
    // ITapTrade::TapAPIAccountCashAdjustQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIAccountCashAdjustQryRsp>(c, "toTapAPIAccountCashAdjustQryRsp");
    // ITapTrade::TapAPIAccountFeeRentQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIAccountFeeRentQryReq>(c, "toTapAPIAccountFeeRentQryReq");
    // ITapTrade::TapAPIAccountFeeRentQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIAccountFeeRentQryRsp>(c, "toTapAPIAccountFeeRentQryRsp");
    // ITapTrade::TapAPIAccountMarginRentQryReq
    c2py::caster::try_generate<ITapTrade::TapAPIAccountMarginRentQryReq>(c, "toTapAPIAccountMarginRentQryReq");
    // ITapTrade::TapAPIAccountMarginRentQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIAccountMarginRentQryRsp>(c, "toTapAPIAccountMarginRentQryRsp");
    // ITapTrade::TapAPIOrderQuoteMarketNotice
    c2py::caster::try_generate<ITapTrade::TapAPIOrderQuoteMarketNotice>(c, "toTapAPIOrderQuoteMarketNotice");
    // ITapTrade::TapAPIOrderMarketInsertReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderMarketInsertReq>(c, "toTapAPIOrderMarketInsertReq");
    // ITapTrade::TapAPIOrderMarketInsertRsp
    c2py::caster::try_generate<ITapTrade::TapAPIOrderMarketInsertRsp>(c, "toTapAPIOrderMarketInsertRsp");
    // ITapTrade::TapAPIOrderMarketDeleteReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderMarketDeleteReq>(c, "toTapAPIOrderMarketDeleteReq");
    // ITapTrade::TapAPIOrderLocalRemoveReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalRemoveReq>(c, "toTapAPIOrderLocalRemoveReq");
    // ITapTrade::TapAPIOrderLocalRemoveRsp
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalRemoveRsp>(c, "toTapAPIOrderLocalRemoveRsp");
    // ITapTrade::TapAPIOrderLocalInputReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalInputReq>(c, "toTapAPIOrderLocalInputReq");
    // ITapTrade::TapAPIOrderLocalModifyReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalModifyReq>(c, "toTapAPIOrderLocalModifyReq");
    // ITapTrade::TapAPIOrderLocalTransferReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalTransferReq>(c, "toTapAPIOrderLocalTransferReq");
    // ITapTrade::TapAPIFillLocalInputReq
    c2py::caster::try_generate<ITapTrade::TapAPIFillLocalInputReq>(c, "toTapAPIFillLocalInputReq");
    // ITapTrade::TapAPIFillLocalRemoveReq
    c2py::caster::try_generate<ITapTrade::TapAPIFillLocalRemoveReq>(c, "toTapAPIFillLocalRemoveReq");
    // ITapTrade::TapAPITradingCalendarQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPITradingCalendarQryRsp>(c, "toTapAPITradingCalendarQryRsp");
    // ITapTrade::ITapTradeAPINotify
    c2py::caster::try_generate<ITapTrade::ITapTradeAPINotify>(c, "toITapTradeAPINotify");
    // ITapTrade::ITapTradeAPI
    c2py::caster::try_generate<ITapTrade::ITapTradeAPI>(c, "toITapTradeAPI");
    // ITapTrade::TAPISTR_10
    c2py::caster::try_generate<ITapTrade::TAPISTR_10>(c, "toTAPISTR_10");
    // ITapTrade::TAPISTR_20
    c2py::caster::try_generate<ITapTrade::TAPISTR_20>(c, "toTAPISTR_20");
    // ITapTrade::TAPISTR_30
    c2py::caster::try_generate<ITapTrade::TAPISTR_30>(c, "toTAPISTR_30");
    // ITapTrade::TAPISTR_40
    c2py::caster::try_generate<ITapTrade::TAPISTR_40>(c, "toTAPISTR_40");
    // ITapTrade::TAPISTR_50
    c2py::caster::try_generate<ITapTrade::TAPISTR_50>(c, "toTAPISTR_50");
    // ITapTrade::TAPISTR_70
    c2py::caster::try_generate<ITapTrade::TAPISTR_70>(c, "toTAPISTR_70");
    // ITapTrade::TAPISTR_100
    c2py::caster::try_generate<ITapTrade::TAPISTR_100>(c, "toTAPISTR_100");
    // ITapTrade::TAPISTR_300
    c2py::caster::try_generate<ITapTrade::TAPISTR_300>(c, "toTAPISTR_300");
    // ITapTrade::TAPISTR_500
    c2py::caster::try_generate<ITapTrade::TAPISTR_500>(c, "toTAPISTR_500");
    // ITapTrade::TAPISTR_2000
    c2py::caster::try_generate<ITapTrade::TAPISTR_2000>(c, "toTAPISTR_2000");
    // ITapTrade::TAPIAUTHCODE
    c2py::caster::try_generate<ITapTrade::TAPIAUTHCODE>(c, "toTAPIAUTHCODE");
    // ITapTrade::TAPIMACTYPE
    c2py::caster::try_generate<ITapTrade::TAPIMACTYPE>(c, "toTAPIMACTYPE");
    // ITapTrade::TAPISecondSerialIDType
    c2py::caster::try_generate<ITapTrade::TAPISecondSerialIDType>(c, "toTAPISecondSerialIDType");
    // ITapTrade::TAPICHAR
    c2py::caster::try_generate<ITapTrade::TAPICHAR>(c, "toTAPICHAR");
    // ITapTrade::TAPIClientIDType
    c2py::caster::try_generate<ITapTrade::TAPIClientIDType>(c, "toTAPIClientIDType");
    // ITapTrade::TAPIINT32
    c2py::caster::try_generate<ITapTrade::TAPIINT32>(c, "toTAPIINT32");
    // ITapTrade::TAPIUINT32
    c2py::caster::try_generate<ITapTrade::TAPIUINT32>(c, "toTAPIUINT32");
    // ITapTrade::TAPIINT64
    c2py::caster::try_generate<ITapTrade::TAPIINT64>(c, "toTAPIINT64");
    // ITapTrade::TAPIUINT64
    c2py::caster::try_generate<ITapTrade::TAPIUINT64>(c, "toTAPIUINT64");
    // ITapTrade::TAPIUINT16
    c2py::caster::try_generate<ITapTrade::TAPIUINT16>(c, "toTAPIUINT16");
    // ITapTrade::TAPIUINT8
    c2py::caster::try_generate<ITapTrade::TAPIUINT8>(c, "toTAPIUINT8");
    // ITapTrade::TAPIREAL64
    c2py::caster::try_generate<ITapTrade::TAPIREAL64>(c, "toTAPIREAL64");
    // ITapTrade::TAPIYNFLAG
    c2py::caster::try_generate<ITapTrade::TAPIYNFLAG>(c, "toTAPIYNFLAG");
    // ITapTrade::TAPIPasswordType
    c2py::caster::try_generate<ITapTrade::TAPIPasswordType>(c, "toTAPIPasswordType");
    // ITapTrade::TAPIDTSTAMP
    c2py::caster::try_generate<ITapTrade::TAPIDTSTAMP>(c, "toTAPIDTSTAMP");
    // ITapTrade::TAPIDATETIME
    c2py::caster::try_generate<ITapTrade::TAPIDATETIME>(c, "toTAPIDATETIME");
    // ITapTrade::TAPIDATE
    c2py::caster::try_generate<ITapTrade::TAPIDATE>(c, "toTAPIDATE");
    // ITapTrade::TAPITIME
    c2py::caster::try_generate<ITapTrade::TAPITIME>(c, "toTAPITIME");
    // ITapTrade::TAPILOGLEVEL
    c2py::caster::try_generate<ITapTrade::TAPILOGLEVEL>(c, "toTAPILOGLEVEL");
    // ITapTrade::TAPIOptionType
    c2py::caster::try_generate<ITapTrade::TAPIOptionType>(c, "toTAPIOptionType");
    // ITapTrade::TAPICommodityType
    c2py::caster::try_generate<ITapTrade::TAPICommodityType>(c, "toTAPICommodityType");
    // ITapTrade::TAPICallOrPutFlagType
    c2py::caster::try_generate<ITapTrade::TAPICallOrPutFlagType>(c, "toTAPICallOrPutFlagType");
    // ITapTrade::TAPIAccountType
    c2py::caster::try_generate<ITapTrade::TAPIAccountType>(c, "toTAPIAccountType");
    // ITapTrade::TAPIRightIDType
    c2py::caster::try_generate<ITapTrade::TAPIRightIDType>(c, "toTAPIRightIDType");
    // ITapTrade::TAPIUserTypeType
    c2py::caster::try_generate<ITapTrade::TAPIUserTypeType>(c, "toTAPIUserTypeType");
    // ITapTrade::TAPIAccountState
    c2py::caster::try_generate<ITapTrade::TAPIAccountState>(c, "toTAPIAccountState");
    // ITapTrade::TAPIAccountRightType
    c2py::caster::try_generate<ITapTrade::TAPIAccountRightType>(c, "toTAPIAccountRightType");
    // ITapTrade::TAPIOrderTypeType
    c2py::caster::try_generate<ITapTrade::TAPIOrderTypeType>(c, "toTAPIOrderTypeType");
    // ITapTrade::TAPIOrderSourceType
    c2py::caster::try_generate<ITapTrade::TAPIOrderSourceType>(c, "toTAPIOrderSourceType");
    // ITapTrade::TAPITimeInForceType
    c2py::caster::try_generate<ITapTrade::TAPITimeInForceType>(c, "toTAPITimeInForceType");
    // ITapTrade::TAPISideType
    c2py::caster::try_generate<ITapTrade::TAPISideType>(c, "toTAPISideType");
    // ITapTrade::TAPIPositionEffectType
    c2py::caster::try_generate<ITapTrade::TAPIPositionEffectType>(c, "toTAPIPositionEffectType");
    // ITapTrade::TAPIHedgeFlagType
    c2py::caster::try_generate<ITapTrade::TAPIHedgeFlagType>(c, "toTAPIHedgeFlagType");
    // ITapTrade::TAPIOrderStateType
    c2py::caster::try_generate<ITapTrade::TAPIOrderStateType>(c, "toTAPIOrderStateType");
    // ITapTrade::TAPICalculateModeType
    c2py::caster::try_generate<ITapTrade::TAPICalculateModeType>(c, "toTAPICalculateModeType");
    // ITapTrade::TAPIMatchSourceType
    c2py::caster::try_generate<ITapTrade::TAPIMatchSourceType>(c, "toTAPIMatchSourceType");
    // ITapTrade::TAPIOpenCloseModeType
    c2py::caster::try_generate<ITapTrade::TAPIOpenCloseModeType>(c, "toTAPIOpenCloseModeType");
    // ITapTrade::TAPIFutureAlgType
    c2py::caster::try_generate<ITapTrade::TAPIFutureAlgType>(c, "toTAPIFutureAlgType");
    // ITapTrade::TAPIOptionAlgType
    c2py::caster::try_generate<ITapTrade::TAPIOptionAlgType>(c, "toTAPIOptionAlgType");
    // ITapTrade::TAPISendType
    c2py::caster::try_generate<ITapTrade::TAPISendType>(c, "toTAPISendType");
    // ITapTrade::TAPIBankAccountLWFlagType
    c2py::caster::try_generate<ITapTrade::TAPIBankAccountLWFlagType>(c, "toTAPIBankAccountLWFlagType");
    // ITapTrade::TAPICashAdjustTypeType
    c2py::caster::try_generate<ITapTrade::TAPICashAdjustTypeType>(c, "toTAPICashAdjustTypeType");
    // ITapTrade::TAPIMarginCalculateModeType
    c2py::caster::try_generate<ITapTrade::TAPIMarginCalculateModeType>(c, "toTAPIMarginCalculateModeType");
    // ITapTrade::TAPIOptionMarginCalculateModeType
    c2py::caster::try_generate<ITapTrade::TAPIOptionMarginCalculateModeType>(c, "toTAPIOptionMarginCalculateModeType");
    // ITapTrade::TAPICmbDirectType
    c2py::caster::try_generate<ITapTrade::TAPICmbDirectType>(c, "toTAPICmbDirectType");
    // ITapTrade::TAPIDeliveryModeType
    c2py::caster::try_generate<ITapTrade::TAPIDeliveryModeType>(c, "toTAPIDeliveryModeType");
    // ITapTrade::TAPIContractTypeType
    c2py::caster::try_generate<ITapTrade::TAPIContractTypeType>(c, "toTAPIContractTypeType");
    // ITapTrade::TAPITacticsTypeType
    c2py::caster::try_generate<ITapTrade::TAPITacticsTypeType>(c, "toTAPITacticsTypeType");
    // ITapTrade::TAPIORDERACT
    c2py::caster::try_generate<ITapTrade::TAPIORDERACT>(c, "toTAPIORDERACT");
    // ITapTrade::TAPITriggerConditionType
    c2py::caster::try_generate<ITapTrade::TAPITriggerConditionType>(c, "toTAPITriggerConditionType");
    // ITapTrade::TAPITriggerPriceTypeType
    c2py::caster::try_generate<ITapTrade::TAPITriggerPriceTypeType>(c, "toTAPITriggerPriceTypeType");
    // ITapTrade::TAPITradingStateType
    c2py::caster::try_generate<ITapTrade::TAPITradingStateType>(c, "toTAPITradingStateType");
    // ITapTrade::TAPINoticeIgnoreFlagType
    c2py::caster::try_generate<ITapTrade::TAPINoticeIgnoreFlagType>(c, "toTAPINoticeIgnoreFlagType");
    // ITapTrade::TAPIOrderQryTypeType
    c2py::caster::try_generate<ITapTrade::TAPIOrderQryTypeType>(c, "toTAPIOrderQryTypeType");
    // ITapTrade::TapAPIOrderDeactivateReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderDeactivateReq>(c, "toTapAPIOrderDeactivateReq");
    // ITapTrade::TapAPIOrderActivateReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderActivateReq>(c, "toTapAPIOrderActivateReq");
    // ITapTrade::TapAPIOrderDeleteReq
    c2py::caster::try_generate<ITapTrade::TapAPIOrderDeleteReq>(c, "toTapAPIOrderDeleteReq");
    // ITapTrade::TAPIMsgReceiverType
    c2py::caster::try_generate<ITapTrade::TAPIMsgReceiverType>(c, "toTAPIMsgReceiverType");
    // ITapTrade::TAPIMsgLevelType
    c2py::caster::try_generate<ITapTrade::TAPIMsgLevelType>(c, "toTAPIMsgLevelType");
    // ITapTrade::TAPIMsgTypeType
    c2py::caster::try_generate<ITapTrade::TAPIMsgTypeType>(c, "toTAPIMsgTypeType");
    // ITapTrade::TAPIBillTypeType
    c2py::caster::try_generate<ITapTrade::TAPIBillTypeType>(c, "toTAPIBillTypeType");
    // ITapTrade::TAPIBillFileTypeType
    c2py::caster::try_generate<ITapTrade::TAPIBillFileTypeType>(c, "toTAPIBillFileTypeType");
    // ITapTrade::TapAPIHisOrderProcessQryRsp
    c2py::caster::try_generate<ITapTrade::TapAPIHisOrderProcessQryRsp>(c, "toTapAPIHisOrderProcessQryRsp");
    // ITapTrade::TAPISettleFlagType
    c2py::caster::try_generate<ITapTrade::TAPISettleFlagType>(c, "toTAPISettleFlagType");
    // ITapTrade::TapAPIOrderMarketDeleteRsp
    c2py::caster::try_generate<ITapTrade::TapAPIOrderMarketDeleteRsp>(c, "toTapAPIOrderMarketDeleteRsp");
    // ITapTrade::TapAPIOrderLocalInputRsp
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalInputRsp>(c, "toTapAPIOrderLocalInputRsp");
    // ITapTrade::TapAPIOrderLocalModifyRsp
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalModifyRsp>(c, "toTapAPIOrderLocalModifyRsp");
    // ITapTrade::TapAPIOrderLocalTransferRsp
    c2py::caster::try_generate<ITapTrade::TapAPIOrderLocalTransferRsp>(c, "toTapAPIOrderLocalTransferRsp");
    // ITapTrade::TapAPIFillLocalInputRsp
    c2py::caster::try_generate<ITapTrade::TapAPIFillLocalInputRsp>(c, "toTapAPIFillLocalInputRsp");
    // ITapTrade::TapAPIFillLocalRemoveRsp
    c2py::caster::try_generate<ITapTrade::TapAPIFillLocalRemoveRsp>(c, "toTapAPIFillLocalRemoveRsp");
}
void generate_ITapTrade_caster(pybind11::module & parent)
{
    generate_caster_ITapTrade(parent);
}
void generate_vntap_sub_namespace(pybind11::module & parent)
{
    // ITapTrade
    {
        auto m = parent.def_submodule("ITapTrade");
        generate_sub_namespace_ITapTrade(m);
    }
}
void generate_class_TapAPIApplicationInfo(pybind11::object & parent)
{
    // TapAPIApplicationInfo
    pybind11::class_<TapAPIApplicationInfo> c(parent, "TapAPIApplicationInfo");
    if constexpr (std::is_default_constructible_v<TapAPIApplicationInfo>)
        c.def(pybind11::init<>());
    // TapAPIApplicationInfo::AuthCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIApplicationInfo, "AuthCode", AuthCode);
    // TapAPIApplicationInfo::KeyOperationLogPath
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIApplicationInfo, "KeyOperationLogPath", KeyOperationLogPath);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIApplicationInfo, c);
    module_vntap::objects.emplace("TapAPIApplicationInfo", c);
}
void generate_class_TapAPICommodity(pybind11::object & parent)
{
    // TapAPICommodity
    pybind11::class_<TapAPICommodity> c(parent, "TapAPICommodity");
    if constexpr (std::is_default_constructible_v<TapAPICommodity>)
        c.def(pybind11::init<>());
    // TapAPICommodity::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPICommodity, "ExchangeNo", ExchangeNo);
    // TapAPICommodity::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPICommodity, "CommodityType", CommodityType);
    // TapAPICommodity::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPICommodity, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPICommodity, c);
    module_vntap::objects.emplace("TapAPICommodity", c);
}
void generate_class_TapAPIContract(pybind11::object & parent)
{
    // TapAPIContract
    pybind11::class_<TapAPIContract> c(parent, "TapAPIContract");
    if constexpr (std::is_default_constructible_v<TapAPIContract>)
        c.def(pybind11::init<>());
    // TapAPIContract::Commodity
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "Commodity", Commodity);
    // TapAPIContract::ContractNo1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "ContractNo1", ContractNo1);
    // TapAPIContract::StrikePrice1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "StrikePrice1", StrikePrice1);
    // TapAPIContract::CallOrPutFlag1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "CallOrPutFlag1", CallOrPutFlag1);
    // TapAPIContract::ContractNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "ContractNo2", ContractNo2);
    // TapAPIContract::StrikePrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "StrikePrice2", StrikePrice2);
    // TapAPIContract::CallOrPutFlag2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIContract, "CallOrPutFlag2", CallOrPutFlag2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIContract, c);
    module_vntap::objects.emplace("TapAPIContract", c);
}
void generate_class_TapAPIExchangeInfo(pybind11::object & parent)
{
    // TapAPIExchangeInfo
    pybind11::class_<TapAPIExchangeInfo> c(parent, "TapAPIExchangeInfo");
    if constexpr (std::is_default_constructible_v<TapAPIExchangeInfo>)
        c.def(pybind11::init<>());
    // TapAPIExchangeInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIExchangeInfo, "ExchangeNo", ExchangeNo);
    // TapAPIExchangeInfo::ExchangeName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIExchangeInfo, "ExchangeName", ExchangeName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIExchangeInfo, c);
    module_vntap::objects.emplace("TapAPIExchangeInfo", c);
}
void generate_class_TapAPIChangePasswordReq(pybind11::object & parent)
{
    // TapAPIChangePasswordReq
    pybind11::class_<TapAPIChangePasswordReq> c(parent, "TapAPIChangePasswordReq");
    if constexpr (std::is_default_constructible_v<TapAPIChangePasswordReq>)
        c.def(pybind11::init<>());
    // TapAPIChangePasswordReq::OldPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIChangePasswordReq, "OldPassword", OldPassword);
    // TapAPIChangePasswordReq::NewPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIChangePasswordReq, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIChangePasswordReq, c);
    module_vntap::objects.emplace("TapAPIChangePasswordReq", c);
}
void generate_class_TapAPIQuoteLoginAuth(pybind11::object & parent)
{
    // TapAPIQuoteLoginAuth
    pybind11::class_<TapAPIQuoteLoginAuth> c(parent, "TapAPIQuoteLoginAuth");
    if constexpr (std::is_default_constructible_v<TapAPIQuoteLoginAuth>)
        c.def(pybind11::init<>());
    // TapAPIQuoteLoginAuth::UserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "UserNo", UserNo);
    // TapAPIQuoteLoginAuth::ISModifyPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "ISModifyPassword", ISModifyPassword);
    // TapAPIQuoteLoginAuth::Password
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "Password", Password);
    // TapAPIQuoteLoginAuth::NewPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "NewPassword", NewPassword);
    // TapAPIQuoteLoginAuth::QuoteTempPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "QuoteTempPassword", QuoteTempPassword);
    // TapAPIQuoteLoginAuth::ISDDA
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "ISDDA", ISDDA);
    // TapAPIQuoteLoginAuth::DDASerialNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuoteLoginAuth, "DDASerialNo", DDASerialNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuoteLoginAuth, c);
    module_vntap::objects.emplace("TapAPIQuoteLoginAuth", c);
}
void generate_class_TapAPIQuotLoginRspInfo(pybind11::object & parent)
{
    // TapAPIQuotLoginRspInfo
    pybind11::class_<TapAPIQuotLoginRspInfo> c(parent, "TapAPIQuotLoginRspInfo");
    if constexpr (std::is_default_constructible_v<TapAPIQuotLoginRspInfo>)
        c.def(pybind11::init<>());
    // TapAPIQuotLoginRspInfo::UserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "UserNo", UserNo);
    // TapAPIQuotLoginRspInfo::UserType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "UserType", UserType);
    // TapAPIQuotLoginRspInfo::UserName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "UserName", UserName);
    // TapAPIQuotLoginRspInfo::QuoteTempPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "QuoteTempPassword", QuoteTempPassword);
    // TapAPIQuotLoginRspInfo::ReservedInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "ReservedInfo", ReservedInfo);
    // TapAPIQuotLoginRspInfo::LastLoginIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLoginIP", LastLoginIP);
    // TapAPIQuotLoginRspInfo::LastLoginProt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLoginProt", LastLoginProt);
    // TapAPIQuotLoginRspInfo::LastLoginTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLoginTime", LastLoginTime);
    // TapAPIQuotLoginRspInfo::LastLogoutTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastLogoutTime", LastLogoutTime);
    // TapAPIQuotLoginRspInfo::TradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "TradeDate", TradeDate);
    // TapAPIQuotLoginRspInfo::LastSettleTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "LastSettleTime", LastSettleTime);
    // TapAPIQuotLoginRspInfo::StartTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "StartTime", StartTime);
    // TapAPIQuotLoginRspInfo::InitTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, TapAPIQuotLoginRspInfo, "InitTime", InitTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, TapAPIQuotLoginRspInfo, c);
    module_vntap::objects.emplace("TapAPIQuotLoginRspInfo", c);
}
