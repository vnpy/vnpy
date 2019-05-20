#pragma once


#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"


void generate_vnitap(pybind11::module & parent);
void generate_sub_namespace_ITapTrade(pybind11::module & parent);
void generate_class_ITapTrade_TapAPIApplicationInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPICommodity(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIContract(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIExchangeInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIChangePasswordReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAuthPasswordReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPITradeLoginAuth(pybind11::object & parent);
void generate_class_ITapTrade_TapAPITradeLoginRspInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIRequestVertificateCodeRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccountInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPINewOrder(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderInfoNotice(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderActionRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAmendOrder(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderCancelReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderProcessQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIFillQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIFillInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPICloseQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPICloseInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIPositionQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIPositionInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIPositionProfit(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIPositionProfitNotice(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIPositionSummary(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIFundReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIFundData(pybind11::object & parent);
void generate_class_ITapTrade_TapAPICommodityInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPITradeContractInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPICurrencyInfo(pybind11::object & parent);
void generate_class_ITapTrade_TapAPITradeMessageReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPITradeMessage(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIBillQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIBillQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisOrderQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisOrderQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisMatchQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisMatchQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisOrderProcessQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisPositionQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisPositionQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisDeliveryQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIHisDeliveryQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccountFeeRentQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccountFeeRentQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccountMarginRentQryReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIAccountMarginRentQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderQuoteMarketNotice(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderMarketInsertReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderMarketInsertRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderMarketDeleteReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderLocalRemoveReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderLocalRemoveRsp(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderLocalInputReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderLocalModifyReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIOrderLocalTransferReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIFillLocalInputReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPIFillLocalRemoveReq(pybind11::object & parent);
void generate_class_ITapTrade_TapAPITradingCalendarQryRsp(pybind11::object & parent);
void generate_class_ITapTrade_ITapTradeAPINotify(pybind11::object & parent);
void generate_class_ITapTrade_ITapTradeAPI(pybind11::object & parent);
void generate_caster_ITapTrade(pybind11::object & parent);
void generate_class_TapAPIApplicationInfo(pybind11::object & parent);
void generate_class_TapAPICommodity(pybind11::object & parent);
void generate_class_TapAPIContract(pybind11::object & parent);
void generate_class_TapAPIExchangeInfo(pybind11::object & parent);
void generate_class_TapAPIChangePasswordReq(pybind11::object & parent);
void generate_class_TapAPIQuoteLoginAuth(pybind11::object & parent);
void generate_class_TapAPIQuotLoginRspInfo(pybind11::object & parent);
void generate_class_TapAPIQuoteCommodityInfo(pybind11::object & parent);
void generate_class_TapAPIQuoteContractInfo(pybind11::object & parent);
void generate_class_TapAPIQuoteWhole(pybind11::object & parent);
void generate_class_ITapQuoteAPINotify(pybind11::object & parent);
void generate_class_ITapQuoteAPI(pybind11::object & parent);
void generate_caster_(pybind11::object & parent);


