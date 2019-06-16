#pragma once


#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "xtp_trader_api.h"
#include "xtp_quote_api.h"


void generate_vnxtp(pybind11::module & parent);
void generate_sub_namespace_XTP(pybind11::module & parent);
void generate_sub_namespace_XTP_API(pybind11::module & parent);
void generate_class_XTP_API_TraderSpi(pybind11::object & parent);
void generate_class_XTP_API_TraderApi(pybind11::object & parent);
void generate_class_XTP_API_QuoteSpi(pybind11::object & parent);
void generate_class_XTP_API_QuoteApi(pybind11::object & parent);
void generate_caster_XTP_API(pybind11::object & parent);
void generate_caster_XTP(pybind11::object & parent);
void generate_class_XTPRspInfoStruct(pybind11::object & parent);
void generate_class_XTPSpecificTickerStruct(pybind11::object & parent);
void generate_class_XTPMarketDataStockExData(pybind11::object & parent);
void generate_class_XTPMarketDataOptionExData(pybind11::object & parent);
void generate_class_XTPMarketDataStruct(pybind11::object & parent);
void generate_class_XTPQuoteStaticInfo(pybind11::object & parent);
void generate_class_OrderBookStruct(pybind11::object & parent);
void generate_class_XTPTickByTickEntrust(pybind11::object & parent);
void generate_class_XTPTickByTickTrade(pybind11::object & parent);
void generate_class_XTPTickByTickStruct(pybind11::object & parent);
void generate_class_XTPTickerPriceInfo(pybind11::object & parent);
void generate_class_XTPOrderInsertInfo(pybind11::object & parent);
void generate_class_XTPOrderCancelInfo(pybind11::object & parent);
void generate_class_XTPOrderInfo(pybind11::object & parent);
void generate_class_XTPTradeReport(pybind11::object & parent);
void generate_class_XTPQueryOrderReq(pybind11::object & parent);
void generate_class_XTPQueryReportByExecIdReq(pybind11::object & parent);
void generate_class_XTPQueryTraderReq(pybind11::object & parent);
void generate_class_XTPQueryAssetRsp(pybind11::object & parent);
void generate_class_XTPQueryStkPositionRsp(pybind11::object & parent);
void generate_class_XTPFundTransferNotice(pybind11::object & parent);
void generate_class_XTPQueryFundTransferLogReq(pybind11::object & parent);
void generate_class_XTPQueryStructuredFundInfoReq(pybind11::object & parent);
void generate_class_XTPStructuredFundInfo(pybind11::object & parent);
void generate_class_XTPQueryETFBaseReq(pybind11::object & parent);
void generate_class_XTPQueryETFBaseRsp(pybind11::object & parent);
void generate_class_XTPQueryETFComponentReq(pybind11::object & parent);
void generate_class_XTPQueryETFComponentRsp(pybind11::object & parent);
void generate_class_XTPQueryIPOTickerRsp(pybind11::object & parent);
void generate_class_XTPQueryIPOQuotaRsp(pybind11::object & parent);
void generate_class_XTPQueryOptionAuctionInfoReq(pybind11::object & parent);
void generate_class_XTPQueryOptionAuctionInfoRsp(pybind11::object & parent);
void generate_class_XTPCrdCashRepayRsp(pybind11::object & parent);
void generate_class_XTPCrdCashRepayDebtInterestFeeRsp(pybind11::object & parent);
void generate_class_XTPCrdCashRepayInfo(pybind11::object & parent);
void generate_class_XTPCrdDebtInfo(pybind11::object & parent);
void generate_class_XTPCrdFundInfo(pybind11::object & parent);
void generate_class_XTPClientQueryCrdDebtStockReq(pybind11::object & parent);
void generate_class_XTPCrdDebtStockInfo(pybind11::object & parent);
void generate_class_XTPClientQueryCrdPositionStockReq(pybind11::object & parent);
void generate_class_XTPClientQueryCrdPositionStkInfo(pybind11::object & parent);
void generate_class_XTPClientQueryCrdSurplusStkReqInfo(pybind11::object & parent);
void generate_class_XTPClientQueryCrdSurplusStkRspInfo(pybind11::object & parent);
void generate_class_XTPClientCrdExtendDebtInfo(pybind11::object & parent);
void generate_class_XTPFundTransferReq(pybind11::object & parent);
void generate_enum_XTP_LOG_LEVEL(pybind11::object & parent);
void generate_enum_XTP_PROTOCOL_TYPE(pybind11::object & parent);
void generate_enum_XTP_EXCHANGE_TYPE(pybind11::object & parent);
void generate_enum_XTP_MARKET_TYPE(pybind11::object & parent);
void generate_enum_XTP_PRICE_TYPE(pybind11::object & parent);
void generate_enum_XTP_ORDER_ACTION_STATUS_TYPE(pybind11::object & parent);
void generate_enum_XTP_ORDER_STATUS_TYPE(pybind11::object & parent);
void generate_enum_XTP_ORDER_SUBMIT_STATUS_TYPE(pybind11::object & parent);
void generate_enum_XTP_TE_RESUME_TYPE(pybind11::object & parent);
void generate_enum_ETF_REPLACE_TYPE(pybind11::object & parent);
void generate_enum_XTP_TICKER_TYPE(pybind11::object & parent);
void generate_enum_XTP_BUSINESS_TYPE(pybind11::object & parent);
void generate_enum_XTP_ACCOUNT_TYPE(pybind11::object & parent);
void generate_enum_XTP_FUND_TRANSFER_TYPE(pybind11::object & parent);
void generate_enum_XTP_FUND_OPER_STATUS(pybind11::object & parent);
void generate_enum_XTP_SPLIT_MERGE_STATUS(pybind11::object & parent);
void generate_enum_XTP_TBT_TYPE(pybind11::object & parent);
void generate_enum_XTP_OPT_CALL_OR_PUT_TYPE(pybind11::object & parent);
void generate_enum_XTP_OPT_EXERCISE_TYPE_TYPE(pybind11::object & parent);
void generate_enum_XTP_POSITION_DIRECTION_TYPE(pybind11::object & parent);
void generate_enum_XTP_CRD_CR_STATUS(pybind11::object & parent);
void generate_enum_XTP_MARKETDATA_TYPE(pybind11::object & parent);
void generate_caster_(pybind11::object & parent);


