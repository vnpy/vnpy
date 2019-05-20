#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "xtp_trader_api.h"
#include "xtp_quote_api.h"


void generate_enum_XTP_TE_RESUME_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_TE_RESUME_TYPE> e(parent, "XTP_TE_RESUME_TYPE", pybind11::arithmetic());
    e.value("XTP_TERT_RESTART", XTP_TE_RESUME_TYPE::XTP_TERT_RESTART);
    e.value("XTP_TERT_RESUME", XTP_TE_RESUME_TYPE::XTP_TERT_RESUME);
    e.value("XTP_TERT_QUICK", XTP_TE_RESUME_TYPE::XTP_TERT_QUICK);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_TE_RESUME_TYPE", e);
}
void generate_enum_ETF_REPLACE_TYPE(pybind11::object & parent)
{
    pybind11::enum_<ETF_REPLACE_TYPE> e(parent, "ETF_REPLACE_TYPE", pybind11::arithmetic());
    e.value("ERT_CASH_FORBIDDEN", ETF_REPLACE_TYPE::ERT_CASH_FORBIDDEN);
    e.value("ERT_CASH_OPTIONAL", ETF_REPLACE_TYPE::ERT_CASH_OPTIONAL);
    e.value("ERT_CASH_MUST", ETF_REPLACE_TYPE::ERT_CASH_MUST);
    e.value("ERT_CASH_RECOMPUTE_INTER_SZ", ETF_REPLACE_TYPE::ERT_CASH_RECOMPUTE_INTER_SZ);
    e.value("ERT_CASH_MUST_INTER_SZ", ETF_REPLACE_TYPE::ERT_CASH_MUST_INTER_SZ);
    e.value("ERT_CASH_RECOMPUTE_INTER_OTHER", ETF_REPLACE_TYPE::ERT_CASH_RECOMPUTE_INTER_OTHER);
    e.value("ERT_CASH_MUST_INTER_OTHER", ETF_REPLACE_TYPE::ERT_CASH_MUST_INTER_OTHER);
    e.value("EPT_INVALID", ETF_REPLACE_TYPE::EPT_INVALID);
    e.export_values();
    module_vnxtp::objects.emplace("ETF_REPLACE_TYPE", e);
}
void generate_enum_XTP_TICKER_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_TICKER_TYPE> e(parent, "XTP_TICKER_TYPE", pybind11::arithmetic());
    e.value("XTP_TICKER_TYPE_STOCK", XTP_TICKER_TYPE::XTP_TICKER_TYPE_STOCK);
    e.value("XTP_TICKER_TYPE_INDEX", XTP_TICKER_TYPE::XTP_TICKER_TYPE_INDEX);
    e.value("XTP_TICKER_TYPE_FUND", XTP_TICKER_TYPE::XTP_TICKER_TYPE_FUND);
    e.value("XTP_TICKER_TYPE_BOND", XTP_TICKER_TYPE::XTP_TICKER_TYPE_BOND);
    e.value("XTP_TICKER_TYPE_OPTION", XTP_TICKER_TYPE::XTP_TICKER_TYPE_OPTION);
    e.value("XTP_TICKER_TYPE_UNKNOWN", XTP_TICKER_TYPE::XTP_TICKER_TYPE_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_TICKER_TYPE", e);
}
void generate_enum_XTP_BUSINESS_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_BUSINESS_TYPE> e(parent, "XTP_BUSINESS_TYPE", pybind11::arithmetic());
    e.value("XTP_BUSINESS_TYPE_CASH", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_CASH);
    e.value("XTP_BUSINESS_TYPE_IPOS", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_IPOS);
    e.value("XTP_BUSINESS_TYPE_REPO", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_REPO);
    e.value("XTP_BUSINESS_TYPE_ETF", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_ETF);
    e.value("XTP_BUSINESS_TYPE_MARGIN", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_MARGIN);
    e.value("XTP_BUSINESS_TYPE_DESIGNATION", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_DESIGNATION);
    e.value("XTP_BUSINESS_TYPE_ALLOTMENT", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_ALLOTMENT);
    e.value("XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION);
    e.value("XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE);
    e.value("XTP_BUSINESS_TYPE_MONEY_FUND", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_MONEY_FUND);
    e.value("XTP_BUSINESS_TYPE_OPTION", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_OPTION);
    e.value("XTP_BUSINESS_TYPE_EXECUTE", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_EXECUTE);
    e.value("XTP_BUSINESS_TYPE_FREEZE", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_FREEZE);
    e.value("XTP_BUSINESS_TYPE_UNKNOWN", XTP_BUSINESS_TYPE::XTP_BUSINESS_TYPE_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_BUSINESS_TYPE", e);
}
void generate_enum_XTP_ACCOUNT_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_ACCOUNT_TYPE> e(parent, "XTP_ACCOUNT_TYPE", pybind11::arithmetic());
    e.value("XTP_ACCOUNT_NORMAL", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_NORMAL);
    e.value("XTP_ACCOUNT_CREDIT", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_CREDIT);
    e.value("XTP_ACCOUNT_DERIVE", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_DERIVE);
    e.value("XTP_ACCOUNT_UNKNOWN", XTP_ACCOUNT_TYPE::XTP_ACCOUNT_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_ACCOUNT_TYPE", e);
}
void generate_enum_XTP_FUND_TRANSFER_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_FUND_TRANSFER_TYPE> e(parent, "XTP_FUND_TRANSFER_TYPE", pybind11::arithmetic());
    e.value("XTP_FUND_TRANSFER_OUT", XTP_FUND_TRANSFER_TYPE::XTP_FUND_TRANSFER_OUT);
    e.value("XTP_FUND_TRANSFER_IN", XTP_FUND_TRANSFER_TYPE::XTP_FUND_TRANSFER_IN);
    e.value("XTP_FUND_TRANSFER_UNKNOWN", XTP_FUND_TRANSFER_TYPE::XTP_FUND_TRANSFER_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_FUND_TRANSFER_TYPE", e);
}
void generate_enum_XTP_FUND_OPER_STATUS(pybind11::object & parent)
{
    pybind11::enum_<XTP_FUND_OPER_STATUS> e(parent, "XTP_FUND_OPER_STATUS", pybind11::arithmetic());
    e.value("XTP_FUND_OPER_PROCESSING", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_PROCESSING);
    e.value("XTP_FUND_OPER_SUCCESS", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_SUCCESS);
    e.value("XTP_FUND_OPER_FAILED", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_FAILED);
    e.value("XTP_FUND_OPER_SUBMITTED", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_SUBMITTED);
    e.value("XTP_FUND_OPER_UNKNOWN", XTP_FUND_OPER_STATUS::XTP_FUND_OPER_UNKNOWN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_FUND_OPER_STATUS", e);
}
void generate_enum_XTP_SPLIT_MERGE_STATUS(pybind11::object & parent)
{
    pybind11::enum_<XTP_SPLIT_MERGE_STATUS> e(parent, "XTP_SPLIT_MERGE_STATUS", pybind11::arithmetic());
    e.value("XTP_SPLIT_MERGE_STATUS_ALLOW", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_ALLOW);
    e.value("XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT);
    e.value("XTP_SPLIT_MERGE_STATUS_ONLY_MERGE", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_ONLY_MERGE);
    e.value("XTP_SPLIT_MERGE_STATUS_FORBIDDEN", XTP_SPLIT_MERGE_STATUS::XTP_SPLIT_MERGE_STATUS_FORBIDDEN);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_SPLIT_MERGE_STATUS", e);
}
void generate_enum_XTP_TBT_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_TBT_TYPE> e(parent, "XTP_TBT_TYPE", pybind11::arithmetic());
    e.value("XTP_TBT_ENTRUST", XTP_TBT_TYPE::XTP_TBT_ENTRUST);
    e.value("XTP_TBT_TRADE", XTP_TBT_TYPE::XTP_TBT_TRADE);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_TBT_TYPE", e);
}
void generate_enum_XTP_OPT_CALL_OR_PUT_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_OPT_CALL_OR_PUT_TYPE> e(parent, "XTP_OPT_CALL_OR_PUT_TYPE", pybind11::arithmetic());
    e.value("XTP_OPT_CALL", XTP_OPT_CALL_OR_PUT_TYPE::XTP_OPT_CALL);
    e.value("XTP_OPT_PUT", XTP_OPT_CALL_OR_PUT_TYPE::XTP_OPT_PUT);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_OPT_CALL_OR_PUT_TYPE", e);
}
void generate_enum_XTP_OPT_EXERCISE_TYPE_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_OPT_EXERCISE_TYPE_TYPE> e(parent, "XTP_OPT_EXERCISE_TYPE_TYPE", pybind11::arithmetic());
    e.value("XTP_OPT_EXERCISE_TYPE_EUR", XTP_OPT_EXERCISE_TYPE_TYPE::XTP_OPT_EXERCISE_TYPE_EUR);
    e.value("XTP_OPT_EXERCISE_TYPE_AME", XTP_OPT_EXERCISE_TYPE_TYPE::XTP_OPT_EXERCISE_TYPE_AME);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_OPT_EXERCISE_TYPE_TYPE", e);
}
void generate_enum_XTP_POSITION_DIRECTION_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_POSITION_DIRECTION_TYPE> e(parent, "XTP_POSITION_DIRECTION_TYPE", pybind11::arithmetic());
    e.value("XTP_POSITION_DIRECTION_NET", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_NET);
    e.value("XTP_POSITION_DIRECTION_LONG", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_LONG);
    e.value("XTP_POSITION_DIRECTION_SHORT", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_SHORT);
    e.value("XTP_POSITION_DIRECTION_COVERED", XTP_POSITION_DIRECTION_TYPE::XTP_POSITION_DIRECTION_COVERED);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_POSITION_DIRECTION_TYPE", e);
}
void generate_enum_XTP_MARKETDATA_TYPE(pybind11::object & parent)
{
    pybind11::enum_<XTP_MARKETDATA_TYPE> e(parent, "XTP_MARKETDATA_TYPE", pybind11::arithmetic());
    e.value("XTP_MARKETDATA_ACTUAL", XTP_MARKETDATA_TYPE::XTP_MARKETDATA_ACTUAL);
    e.value("XTP_MARKETDATA_OPTION", XTP_MARKETDATA_TYPE::XTP_MARKETDATA_OPTION);
    e.export_values();
    module_vnxtp::objects.emplace("XTP_MARKETDATA_TYPE", e);
}
void generate_caster_(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
    autocxxpy::caster::try_generate<XTPRspInfoStruct>(c, "toXTPRspInfoStruct)");
    autocxxpy::caster::try_generate<XTPSpecificTickerStruct>(c, "toXTPSpecificTickerStruct)");
    autocxxpy::caster::try_generate<XTPMarketDataStockExData>(c, "toXTPMarketDataStockExData)");
    autocxxpy::caster::try_generate<XTPMarketDataOptionExData>(c, "toXTPMarketDataOptionExData)");
    autocxxpy::caster::try_generate<XTPMarketDataStruct>(c, "toXTPMarketDataStruct)");
    autocxxpy::caster::try_generate<XTPQuoteStaticInfo>(c, "toXTPQuoteStaticInfo)");
    autocxxpy::caster::try_generate<OrderBookStruct>(c, "toOrderBookStruct)");
    autocxxpy::caster::try_generate<XTPTickByTickEntrust>(c, "toXTPTickByTickEntrust)");
    autocxxpy::caster::try_generate<XTPTickByTickTrade>(c, "toXTPTickByTickTrade)");
    autocxxpy::caster::try_generate<XTPTickByTickStruct>(c, "toXTPTickByTickStruct)");
    autocxxpy::caster::try_generate<XTPTickerPriceInfo>(c, "toXTPTickerPriceInfo)");
    autocxxpy::caster::try_generate<XTPOrderInsertInfo>(c, "toXTPOrderInsertInfo)");
    autocxxpy::caster::try_generate<XTPOrderCancelInfo>(c, "toXTPOrderCancelInfo)");
    autocxxpy::caster::try_generate<XTPOrderInfo>(c, "toXTPOrderInfo)");
    autocxxpy::caster::try_generate<XTPTradeReport>(c, "toXTPTradeReport)");
    autocxxpy::caster::try_generate<XTPQueryOrderReq>(c, "toXTPQueryOrderReq)");
    autocxxpy::caster::try_generate<XTPQueryReportByExecIdReq>(c, "toXTPQueryReportByExecIdReq)");
    autocxxpy::caster::try_generate<XTPQueryTraderReq>(c, "toXTPQueryTraderReq)");
    autocxxpy::caster::try_generate<XTPQueryAssetRsp>(c, "toXTPQueryAssetRsp)");
    autocxxpy::caster::try_generate<XTPQueryStkPositionRsp>(c, "toXTPQueryStkPositionRsp)");
    autocxxpy::caster::try_generate<XTPFundTransferNotice>(c, "toXTPFundTransferNotice)");
    autocxxpy::caster::try_generate<XTPQueryFundTransferLogReq>(c, "toXTPQueryFundTransferLogReq)");
    autocxxpy::caster::try_generate<XTPQueryStructuredFundInfoReq>(c, "toXTPQueryStructuredFundInfoReq)");
    autocxxpy::caster::try_generate<XTPStructuredFundInfo>(c, "toXTPStructuredFundInfo)");
    autocxxpy::caster::try_generate<XTPQueryETFBaseReq>(c, "toXTPQueryETFBaseReq)");
    autocxxpy::caster::try_generate<XTPQueryETFBaseRsp>(c, "toXTPQueryETFBaseRsp)");
    autocxxpy::caster::try_generate<XTPQueryETFComponentReq>(c, "toXTPQueryETFComponentReq)");
    autocxxpy::caster::try_generate<XTPQueryETFComponentRsp>(c, "toXTPQueryETFComponentRsp)");
    autocxxpy::caster::try_generate<XTPQueryIPOTickerRsp>(c, "toXTPQueryIPOTickerRsp)");
    autocxxpy::caster::try_generate<XTPQueryIPOQuotaRsp>(c, "toXTPQueryIPOQuotaRsp)");
    autocxxpy::caster::try_generate<XTPQueryOptionAuctionInfoReq>(c, "toXTPQueryOptionAuctionInfoReq)");
    autocxxpy::caster::try_generate<XTPQueryOptionAuctionInfoRsp>(c, "toXTPQueryOptionAuctionInfoRsp)");
    autocxxpy::caster::try_generate<XTPFundTransferReq>(c, "toXTPFundTransferReq)");
    autocxxpy::caster::try_generate<XTPVersionType>(c, "toXTPVersionType)");
    autocxxpy::caster::try_generate<XTP_LOG_LEVEL>(c, "toXTP_LOG_LEVEL)");
    autocxxpy::caster::try_generate<XTP_PROTOCOL_TYPE>(c, "toXTP_PROTOCOL_TYPE)");
    autocxxpy::caster::try_generate<XTP_EXCHANGE_TYPE>(c, "toXTP_EXCHANGE_TYPE)");
    autocxxpy::caster::try_generate<XTP_MARKET_TYPE>(c, "toXTP_MARKET_TYPE)");
    autocxxpy::caster::try_generate<XTP_PRICE_TYPE>(c, "toXTP_PRICE_TYPE)");
    autocxxpy::caster::try_generate<XTP_SIDE_TYPE>(c, "toXTP_SIDE_TYPE)");
    autocxxpy::caster::try_generate<XTP_POSITION_EFFECT_TYPE>(c, "toXTP_POSITION_EFFECT_TYPE)");
    autocxxpy::caster::try_generate<XTP_ORDER_ACTION_STATUS_TYPE>(c, "toXTP_ORDER_ACTION_STATUS_TYPE)");
    autocxxpy::caster::try_generate<XTP_ORDER_STATUS_TYPE>(c, "toXTP_ORDER_STATUS_TYPE)");
    autocxxpy::caster::try_generate<XTP_ORDER_SUBMIT_STATUS_TYPE>(c, "toXTP_ORDER_SUBMIT_STATUS_TYPE)");
    autocxxpy::caster::try_generate<XTP_TE_RESUME_TYPE>(c, "toXTP_TE_RESUME_TYPE)");
    autocxxpy::caster::try_generate<ETF_REPLACE_TYPE>(c, "toETF_REPLACE_TYPE)");
    autocxxpy::caster::try_generate<XTP_TICKER_TYPE>(c, "toXTP_TICKER_TYPE)");
    autocxxpy::caster::try_generate<XTP_BUSINESS_TYPE>(c, "toXTP_BUSINESS_TYPE)");
    autocxxpy::caster::try_generate<XTP_ACCOUNT_TYPE>(c, "toXTP_ACCOUNT_TYPE)");
    autocxxpy::caster::try_generate<XTP_FUND_TRANSFER_TYPE>(c, "toXTP_FUND_TRANSFER_TYPE)");
    autocxxpy::caster::try_generate<XTP_FUND_OPER_STATUS>(c, "toXTP_FUND_OPER_STATUS)");
    autocxxpy::caster::try_generate<XTP_SPLIT_MERGE_STATUS>(c, "toXTP_SPLIT_MERGE_STATUS)");
    autocxxpy::caster::try_generate<XTP_TBT_TYPE>(c, "toXTP_TBT_TYPE)");
    autocxxpy::caster::try_generate<XTP_OPT_CALL_OR_PUT_TYPE>(c, "toXTP_OPT_CALL_OR_PUT_TYPE)");
    autocxxpy::caster::try_generate<XTP_OPT_EXERCISE_TYPE_TYPE>(c, "toXTP_OPT_EXERCISE_TYPE_TYPE)");
    autocxxpy::caster::try_generate<XTP_POSITION_DIRECTION_TYPE>(c, "toXTP_POSITION_DIRECTION_TYPE)");
    autocxxpy::caster::try_generate<TXTPTradeTypeType>(c, "toTXTPTradeTypeType)");
    autocxxpy::caster::try_generate<TXTPOrderTypeType>(c, "toTXTPOrderTypeType)");
    autocxxpy::caster::try_generate<XTPRI>(c, "toXTPRI)");
    autocxxpy::caster::try_generate<XTPST>(c, "toXTPST)");
    autocxxpy::caster::try_generate<XTPMD>(c, "toXTPMD)");
    autocxxpy::caster::try_generate<XTPQSI>(c, "toXTPQSI)");
    autocxxpy::caster::try_generate<XTPOB>(c, "toXTPOB)");
    autocxxpy::caster::try_generate<XTPTBT>(c, "toXTPTBT)");
    autocxxpy::caster::try_generate<XTPTPI>(c, "toXTPTPI)");
    autocxxpy::caster::try_generate<XTPQueryOrderRsp>(c, "toXTPQueryOrderRsp)");
    autocxxpy::caster::try_generate<XTPQueryTradeRsp>(c, "toXTPQueryTradeRsp)");
    autocxxpy::caster::try_generate<XTPFundTransferLog>(c, "toXTPFundTransferLog)");
    autocxxpy::caster::try_generate<XTPQueryETFBaseRsp>(c, "toXTPQueryETFBaseRsp)");
    autocxxpy::caster::try_generate<XTPQueryETFComponentReq>(c, "toXTPQueryETFComponentReq)");
    autocxxpy::caster::try_generate<XTPFundTransferAck>(c, "toXTPFundTransferAck)");
}
