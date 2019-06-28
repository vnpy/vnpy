#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


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
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdType", e);
}
void generate_enum_eOesOrdTypeSh(pybind11::object & parent)
{
    pybind11::enum_<_eOesOrdTypeSh> e(parent, "_eOesOrdTypeSh", pybind11::arithmetic());
    e.value("OES_ORD_TYPE_SH_LMT", _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT);
    e.value("OES_ORD_TYPE_SH_MTL_BEST_5", _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_BEST_5);
    e.value("OES_ORD_TYPE_SH_FAK_BEST_5", _eOesOrdTypeSh::OES_ORD_TYPE_SH_FAK_BEST_5);
    e.value("OES_ORD_TYPE_SH_LMT_FOK", _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT_FOK);
    e.value("OES_ORD_TYPE_SH_FOK", _eOesOrdTypeSh::OES_ORD_TYPE_SH_FOK);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdTypeSh", e);
}
void generate_enum_eOesOrdTypeSz(pybind11::object & parent)
{
    pybind11::enum_<_eOesOrdTypeSz> e(parent, "_eOesOrdTypeSz", pybind11::arithmetic());
    e.value("OES_ORD_TYPE_SZ_LMT", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT);
    e.value("OES_ORD_TYPE_SZ_MTL_BEST", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_BEST);
    e.value("OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST);
    e.value("OES_ORD_TYPE_SZ_FAK_BEST_5", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK_BEST_5);
    e.value("OES_ORD_TYPE_SZ_FAK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK);
    e.value("OES_ORD_TYPE_SZ_FOK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FOK);
    e.value("OES_ORD_TYPE_SZ_LMT_FOK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT_FOK);
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
    e.value("OES_BS_TYPE_BUY_OPEN", _eOesBuySellType::OES_BS_TYPE_BUY_OPEN);
    e.value("OES_BS_TYPE_BUY_CLOSE", _eOesBuySellType::OES_BS_TYPE_BUY_CLOSE);
    e.value("OES_BS_TYPE_SELL_OPEN", _eOesBuySellType::OES_BS_TYPE_SELL_OPEN);
    e.value("OES_BS_TYPE_SELL_CLOSE", _eOesBuySellType::OES_BS_TYPE_SELL_CLOSE);
    e.value("OES_BS_TYPE_COVERED_OPEN", _eOesBuySellType::OES_BS_TYPE_COVERED_OPEN);
    e.value("OES_BS_TYPE_COVERED_CLOSE", _eOesBuySellType::OES_BS_TYPE_COVERED_CLOSE);
    e.value("OES_BS_TYPE_OPTION_EXERCISE", _eOesBuySellType::OES_BS_TYPE_OPTION_EXERCISE);
    e.value("OES_BS_TYPE_UNDERLYING_FREEZE", _eOesBuySellType::OES_BS_TYPE_UNDERLYING_FREEZE);
    e.value("OES_BS_TYPE_UNDERLYING_UNFREEZE", _eOesBuySellType::OES_BS_TYPE_UNDERLYING_UNFREEZE);
    e.value("OES_BS_TYPE_CANCEL", _eOesBuySellType::OES_BS_TYPE_CANCEL);
    e.value("__OES_BS_TYPE_MAX_TRADING", _eOesBuySellType::__OES_BS_TYPE_MAX_TRADING);
    e.value("OES_BS_TYPE_SSE_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SSE_DESIGNATION);
    e.value("OES_BS_TYPE_SSE_RECALL_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SSE_RECALL_DESIGNATION);
    e.value("OES_BS_TYPE_SZSE_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SZSE_DESIGNATION);
    e.value("OES_BS_TYPE_SZSE_CANCEL_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SZSE_CANCEL_DESIGNATION);
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
void generate_enum_eOesCashType(pybind11::object & parent)
{
    pybind11::enum_<_eOesCashType> e(parent, "_eOesCashType", pybind11::arithmetic());
    e.value("OES_CASH_TYPE_SPOT", _eOesCashType::OES_CASH_TYPE_SPOT);
    e.value("OES_CASH_TYPE_CREDIT", _eOesCashType::OES_CASH_TYPE_CREDIT);
    e.value("OES_CASH_TYPE_OPTION", _eOesCashType::OES_CASH_TYPE_OPTION);
    e.value("__OES_CASH_TYPE_MAX", _eOesCashType::__OES_CASH_TYPE_MAX);
    e.value("OES_CASH_TYPE_CRE", _eOesCashType::OES_CASH_TYPE_CRE);
    e.value("OES_CASH_TYPE_OPT", _eOesCashType::OES_CASH_TYPE_OPT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCashType", e);
}
void generate_enum_eOesAcctStatus(pybind11::object & parent)
{
    pybind11::enum_<_eOesAcctStatus> e(parent, "_eOesAcctStatus", pybind11::arithmetic());
    e.value("OES_ACCT_STATUS_NORMAL", _eOesAcctStatus::OES_ACCT_STATUS_NORMAL);
    e.value("OES_ACCT_STATUS_DISABLED", _eOesAcctStatus::OES_ACCT_STATUS_DISABLED);
    e.value("OES_ACCT_STATUS_LOCKED", _eOesAcctStatus::OES_ACCT_STATUS_LOCKED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesAcctStatus", e);
}
void generate_enum_eOesTradingPermission(pybind11::object & parent)
{
    pybind11::enum_<_eOesTradingPermission> e(parent, "_eOesTradingPermission", pybind11::arithmetic());
    e.value("OES_PERMIS_MARKET_ORDER", _eOesTradingPermission::OES_PERMIS_MARKET_ORDER);
    e.value("OES_PERMIS_STRUCTURED_FUND", _eOesTradingPermission::OES_PERMIS_STRUCTURED_FUND);
    e.value("OES_PERMIS_BOND_QUALIFIED_INVESTOR", _eOesTradingPermission::OES_PERMIS_BOND_QUALIFIED_INVESTOR);
    e.value("OES_PERMIS_XXX4", _eOesTradingPermission::OES_PERMIS_XXX4);
    e.value("OES_PERMIS_DELISTING", _eOesTradingPermission::OES_PERMIS_DELISTING);
    e.value("OES_PERMIS_RISK_WARNING", _eOesTradingPermission::OES_PERMIS_RISK_WARNING);
    e.value("OES_PERMIS_SINGLE_MARKET_ETF", _eOesTradingPermission::OES_PERMIS_SINGLE_MARKET_ETF);
    e.value("OES_PERMIS_CROSS_BORDER_ETF", _eOesTradingPermission::OES_PERMIS_CROSS_BORDER_ETF);
    e.value("OES_PERMIS_CROSS_MARKET_ETF", _eOesTradingPermission::OES_PERMIS_CROSS_MARKET_ETF);
    e.value("OES_PERMIS_CURRENCY_ETF", _eOesTradingPermission::OES_PERMIS_CURRENCY_ETF);
    e.value("OES_PERMIS_STOCK_PLEDGE_REPURCHASE", _eOesTradingPermission::OES_PERMIS_STOCK_PLEDGE_REPURCHASE);
    e.value("OES_PERMIS_PLEDGE_REPURCHASE", _eOesTradingPermission::OES_PERMIS_PLEDGE_REPURCHASE);
    e.value("OES_PERMIS_GEM", _eOesTradingPermission::OES_PERMIS_GEM);
    e.value("OES_PERMIS_SH_HK_STOCK_CONNECT", _eOesTradingPermission::OES_PERMIS_SH_HK_STOCK_CONNECT);
    e.value("OES_PERMIS_SZ_HK_STOCK_CONNECT", _eOesTradingPermission::OES_PERMIS_SZ_HK_STOCK_CONNECT);
    e.value("OES_PERMIS_CDR", _eOesTradingPermission::OES_PERMIS_CDR);
    e.value("OES_PERMIS_INNOVATION", _eOesTradingPermission::OES_PERMIS_INNOVATION);
    e.value("__OES_PERMIS_ALL", _eOesTradingPermission::__OES_PERMIS_ALL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesTradingPermission", e);
}
void generate_enum_eOesTradingLimit(pybind11::object & parent)
{
    pybind11::enum_<_eOesTradingLimit> e(parent, "_eOesTradingLimit", pybind11::arithmetic());
    e.value("OES_LIMIT_BUY", _eOesTradingLimit::OES_LIMIT_BUY);
    e.value("OES_LIMIT_SELL", _eOesTradingLimit::OES_LIMIT_SELL);
    e.value("OES_LIMIT_RECALL_DESIGNATION", _eOesTradingLimit::OES_LIMIT_RECALL_DESIGNATION);
    e.value("OES_LIMIT_DESIGNATION", _eOesTradingLimit::OES_LIMIT_DESIGNATION);
    e.value("OES_LIMIT_REPO", _eOesTradingLimit::OES_LIMIT_REPO);
    e.value("OES_LIMIT_REVERSE_REPO", _eOesTradingLimit::OES_LIMIT_REVERSE_REPO);
    e.value("OES_LIMIT_SUBSCRIPTION", _eOesTradingLimit::OES_LIMIT_SUBSCRIPTION);
    e.value("OES_LIMIT_CREDIT_BUY", _eOesTradingLimit::OES_LIMIT_CREDIT_BUY);
    e.value("OES_LIMIT_CREDIT_SELL", _eOesTradingLimit::OES_LIMIT_CREDIT_SELL);
    e.value("__OES_LIMIT_ALL", _eOesTradingLimit::__OES_LIMIT_ALL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesTradingLimit", e);
}
void generate_enum_eOesQualificationClass(pybind11::object & parent)
{
    pybind11::enum_<_eOesQualificationClass> e(parent, "_eOesQualificationClass", pybind11::arithmetic());
    e.value("OES_QUALIFICATION_PUBLIC_INVESTOR", _eOesQualificationClass::OES_QUALIFICATION_PUBLIC_INVESTOR);
    e.value("OES_QUALIFICATION_QUALIFIED_INVESTOR", _eOesQualificationClass::OES_QUALIFICATION_QUALIFIED_INVESTOR);
    e.value("OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL", _eOesQualificationClass::OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesQualificationClass", e);
}
void generate_enum_eOesInvestorClass(pybind11::object & parent)
{
    pybind11::enum_<_eOesInvestorClass> e(parent, "_eOesInvestorClass", pybind11::arithmetic());
    e.value("OES_INVESTOR_CLASS_NORMAL", _eOesInvestorClass::OES_INVESTOR_CLASS_NORMAL);
    e.value("OES_INVESTOR_CLASS_PROFESSIONAL_A", _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_A);
    e.value("OES_INVESTOR_CLASS_PROFESSIONAL_B", _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_B);
    e.value("OES_INVESTOR_CLASS_PROFESSIONAL_C", _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_C);
    e.export_values();
    module_vnoes::objects.emplace("_eOesInvestorClass", e);
}
void generate_enum_eOesOwnerType(pybind11::object & parent)
{
    pybind11::enum_<_eOesOwnerType> e(parent, "_eOesOwnerType", pybind11::arithmetic());
    e.value("OES_OWNER_TYPE_PERSONAL", _eOesOwnerType::OES_OWNER_TYPE_PERSONAL);
    e.value("OES_OWNER_TYPE_EXCHANGE", _eOesOwnerType::OES_OWNER_TYPE_EXCHANGE);
    e.value("OES_OWNER_TYPE_MEMBER", _eOesOwnerType::OES_OWNER_TYPE_MEMBER);
    e.value("OES_OWNER_TYPE_INSTITUTION", _eOesOwnerType::OES_OWNER_TYPE_INSTITUTION);
    e.value("OES_OWNER_TYPE_PROPRIETARY", _eOesOwnerType::OES_OWNER_TYPE_PROPRIETARY);
    e.value("OES_OWNER_TYPE_MKT_MAKER", _eOesOwnerType::OES_OWNER_TYPE_MKT_MAKER);
    e.value("OES_OWNER_TYPE_SETTLEMENT", _eOesOwnerType::OES_OWNER_TYPE_SETTLEMENT);
    e.value("__OES_OWNER_TYPE_MAX", _eOesOwnerType::__OES_OWNER_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOwnerType", e);
}
void generate_enum_eOesClientType(pybind11::object & parent)
{
    pybind11::enum_<_eOesClientType> e(parent, "_eOesClientType", pybind11::arithmetic());
    e.value("OES_CLIENT_TYPE_UNDEFINED", _eOesClientType::OES_CLIENT_TYPE_UNDEFINED);
    e.value("OES_CLIENT_TYPE_INVESTOR", _eOesClientType::OES_CLIENT_TYPE_INVESTOR);
    e.value("OES_CLIENT_TYPE_VIRTUAL", _eOesClientType::OES_CLIENT_TYPE_VIRTUAL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesClientType", e);
}
void generate_enum_eOesClientStatus(pybind11::object & parent)
{
    pybind11::enum_<_eOesClientStatus> e(parent, "_eOesClientStatus", pybind11::arithmetic());
    e.value("OES_CLIENT_STATUS_UNACTIVATED", _eOesClientStatus::OES_CLIENT_STATUS_UNACTIVATED);
    e.value("OES_CLIENT_STATUS_ACTIVATED", _eOesClientStatus::OES_CLIENT_STATUS_ACTIVATED);
    e.value("OES_CLIENT_STATUS_PAUSE", _eOesClientStatus::OES_CLIENT_STATUS_PAUSE);
    e.value("OES_CLIENT_STATUS_SUSPENDED", _eOesClientStatus::OES_CLIENT_STATUS_SUSPENDED);
    e.value("OES_CLIENT_STATUS_CANCELLED", _eOesClientStatus::OES_CLIENT_STATUS_CANCELLED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesClientStatus", e);
}
void generate_enum_eOesOptContractType(pybind11::object & parent)
{
    pybind11::enum_<_eOesOptContractType> e(parent, "_eOesOptContractType", pybind11::arithmetic());
    e.value("OES_OPT_CONTRACT_TYPE_CALL", _eOesOptContractType::OES_OPT_CONTRACT_TYPE_CALL);
    e.value("OES_OPT_CONTRACT_TYPE_PUT", _eOesOptContractType::OES_OPT_CONTRACT_TYPE_PUT);
    e.value("__OES_OPT_CONTRACT_TYPE_MAX", _eOesOptContractType::__OES_OPT_CONTRACT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptContractType", e);
}
void generate_enum_eOesOptInvLevel(pybind11::object & parent)
{
    pybind11::enum_<_eOesOptInvLevel> e(parent, "_eOesOptInvLevel", pybind11::arithmetic());
    e.value("OES_OPT_INV_LEVEL_B", _eOesOptInvLevel::OES_OPT_INV_LEVEL_B);
    e.value("OES_OPT_INV_LEVEL_L", _eOesOptInvLevel::OES_OPT_INV_LEVEL_L);
    e.value("OES_OPT_INV_LEVEL_A", _eOesOptInvLevel::OES_OPT_INV_LEVEL_A);
    e.value("__OES_OPT_INV_LEVEL_MAX", _eOesOptInvLevel::__OES_OPT_INV_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptInvLevel", e);
}
void generate_enum_eOpenFlagType(pybind11::object & parent)
{
    pybind11::enum_<_eOpenFlagType> e(parent, "_eOpenFlagType", pybind11::arithmetic());
    e.value("OPEN_FLAG_TYPE_ALLOW", _eOpenFlagType::OPEN_FLAG_TYPE_ALLOW);
    e.value("OPEN_FLAG_TYPE_FORBID", _eOpenFlagType::OPEN_FLAG_TYPE_FORBID);
    e.value("__OPEN_FLAG_TYPE_MAX", _eOpenFlagType::__OPEN_FLAG_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOpenFlagType", e);
}
void generate_enum_eOesOptionOpenFlag(pybind11::object & parent)
{
    pybind11::enum_<_eOesOptionOpenFlag> e(parent, "_eOesOptionOpenFlag", pybind11::arithmetic());
    e.value("OES_OPTION_OPEN_FLAG_ALLOW", _eOesOptionOpenFlag::OES_OPTION_OPEN_FLAG_ALLOW);
    e.value("OES_OPTION_OPEN_FLAG_FORBID", _eOesOptionOpenFlag::OES_OPTION_OPEN_FLAG_FORBID);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptionOpenFlag", e);
}
void generate_enum_eOesPositionEff(pybind11::object & parent)
{
    pybind11::enum_<_eOesPositionEff> e(parent, "_eOesPositionEff", pybind11::arithmetic());
    e.value("OES_POSITION_INVALID", _eOesPositionEff::OES_POSITION_INVALID);
    e.value("OES_POSITION_OPEN", _eOesPositionEff::OES_POSITION_OPEN);
    e.value("OES_POSITION_CLOSE", _eOesPositionEff::OES_POSITION_CLOSE);
    e.export_values();
    module_vnoes::objects.emplace("_eOesPositionEff", e);
}
void generate_enum_eOesOptionType(pybind11::object & parent)
{
    pybind11::enum_<_eOesOptionType> e(parent, "_eOesOptionType", pybind11::arithmetic());
    e.value("OES_OPTION_TYPE_E", _eOesOptionType::OES_OPTION_TYPE_E);
    e.value("OES_OPTION_TYPE_A", _eOesOptionType::OES_OPTION_TYPE_A);
    e.value("__OES_OPTION_TYPE_MAX", _eOesOptionType::__OES_OPTION_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptionType", e);
}
void generate_enum_eSMsgProtocolType(pybind11::object & parent)
{
    pybind11::enum_<_eSMsgProtocolType> e(parent, "_eSMsgProtocolType", pybind11::arithmetic());
    e.value("SMSG_PROTO_BINARY", _eSMsgProtocolType::SMSG_PROTO_BINARY);
    e.value("SMSG_PROTO_JSON", _eSMsgProtocolType::SMSG_PROTO_JSON);
    e.value("SMSG_PROTO_FIX", _eSMsgProtocolType::SMSG_PROTO_FIX);
    e.value("SMSG_PROTO_PROTOBUF", _eSMsgProtocolType::SMSG_PROTO_PROTOBUF);
    e.value("__MAX_SMSG_PROTO_TYPE", _eSMsgProtocolType::__MAX_SMSG_PROTO_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eSMsgProtocolType", e);
}
void generate_enum_eSMsgFlag(pybind11::object & parent)
{
    pybind11::enum_<_eSMsgFlag> e(parent, "_eSMsgFlag", pybind11::arithmetic());
    e.value("SMSG_MSGFLAG_NONE", _eSMsgFlag::SMSG_MSGFLAG_NONE);
    e.value("SMSG_MSGFLAG_REQ", _eSMsgFlag::SMSG_MSGFLAG_REQ);
    e.value("SMSG_MSGFLAG_RSP", _eSMsgFlag::SMSG_MSGFLAG_RSP);
    e.value("SMSG_MSGFLAG_NESTED", _eSMsgFlag::SMSG_MSGFLAG_NESTED);
    e.value("SMSG_MSGFLAG_COMPRESSED", _eSMsgFlag::SMSG_MSGFLAG_COMPRESSED);
    e.value("SMSG_MSGFLAG_MASK_RSPFLAG", _eSMsgFlag::SMSG_MSGFLAG_MASK_RSPFLAG);
    e.value("SMSG_MSGFLAG_MASK_PROTOCOL", _eSMsgFlag::SMSG_MSGFLAG_MASK_PROTOCOL);
    e.export_values();
    module_vnoes::objects.emplace("_eSMsgFlag", e);
}
void generate_enum_eOesMsgType(pybind11::object & parent)
{
    pybind11::enum_<_eOesMsgType> e(parent, "_eOesMsgType", pybind11::arithmetic());
    e.value("OESMSG_ORD_NEW_ORDER", _eOesMsgType::OESMSG_ORD_NEW_ORDER);
    e.value("OESMSG_ORD_CANCEL_REQUEST", _eOesMsgType::OESMSG_ORD_CANCEL_REQUEST);
    e.value("OESMSG_ORD_BATCH_ORDERS", _eOesMsgType::OESMSG_ORD_BATCH_ORDERS);
    e.value("__OESMSG_ORD_MAX", _eOesMsgType::__OESMSG_ORD_MAX);
    e.value("__OESMSG_RPT_MIN", _eOesMsgType::__OESMSG_RPT_MIN);
    e.value("OESMSG_RPT_MARKET_STATE", _eOesMsgType::OESMSG_RPT_MARKET_STATE);
    e.value("OESMSG_RPT_REPORT_SYNCHRONIZATION", _eOesMsgType::OESMSG_RPT_REPORT_SYNCHRONIZATION);
    e.value("OESMSG_RPT_BUSINESS_REJECT", _eOesMsgType::OESMSG_RPT_BUSINESS_REJECT);
    e.value("OESMSG_RPT_ORDER_INSERT", _eOesMsgType::OESMSG_RPT_ORDER_INSERT);
    e.value("OESMSG_RPT_ORDER_REPORT", _eOesMsgType::OESMSG_RPT_ORDER_REPORT);
    e.value("OESMSG_RPT_TRADE_REPORT", _eOesMsgType::OESMSG_RPT_TRADE_REPORT);
    e.value("OESMSG_RPT_FUND_TRSF_REJECT", _eOesMsgType::OESMSG_RPT_FUND_TRSF_REJECT);
    e.value("OESMSG_RPT_FUND_TRSF_REPORT", _eOesMsgType::OESMSG_RPT_FUND_TRSF_REPORT);
    e.value("OESMSG_RPT_CASH_ASSET_VARIATION", _eOesMsgType::OESMSG_RPT_CASH_ASSET_VARIATION);
    e.value("OESMSG_RPT_STOCK_HOLDING_VARIATION", _eOesMsgType::OESMSG_RPT_STOCK_HOLDING_VARIATION);
    e.value("OESMSG_RPT_OPTION_HOLDING_VARIATION", _eOesMsgType::OESMSG_RPT_OPTION_HOLDING_VARIATION);
    e.value("__OESMSG_RPT_MAX", _eOesMsgType::__OESMSG_RPT_MAX);
    e.value("__OESMSG_NONTRD_MIN", _eOesMsgType::__OESMSG_NONTRD_MIN);
    e.value("OESMSG_NONTRD_FUND_TRSF_REQ", _eOesMsgType::OESMSG_NONTRD_FUND_TRSF_REQ);
    e.value("OESMSG_NONTRD_CHANGE_PASSWORD", _eOesMsgType::OESMSG_NONTRD_CHANGE_PASSWORD);
    e.value("__OESMSG_NONTRD_MAX", _eOesMsgType::__OESMSG_NONTRD_MAX);
    e.value("__OESMSG_QRYMSG_MIN", _eOesMsgType::__OESMSG_QRYMSG_MIN);
    e.value("OESMSG_QRYMSG_CLIENT_OVERVIEW", _eOesMsgType::OESMSG_QRYMSG_CLIENT_OVERVIEW);
    e.value("OESMSG_QRYMSG_ORD", _eOesMsgType::OESMSG_QRYMSG_ORD);
    e.value("OESMSG_QRYMSG_TRD", _eOesMsgType::OESMSG_QRYMSG_TRD);
    e.value("OESMSG_QRYMSG_CASH_ASSET", _eOesMsgType::OESMSG_QRYMSG_CASH_ASSET);
    e.value("OESMSG_QRYMSG_STK_HLD", _eOesMsgType::OESMSG_QRYMSG_STK_HLD);
    e.value("OESMSG_QRYMSG_OPT_HLD", _eOesMsgType::OESMSG_QRYMSG_OPT_HLD);
    e.value("OESMSG_QRYMSG_CUST", _eOesMsgType::OESMSG_QRYMSG_CUST);
    e.value("OESMSG_QRYMSG_INV_ACCT", _eOesMsgType::OESMSG_QRYMSG_INV_ACCT);
    e.value("OESMSG_QRYMSG_COMMISSION_RATE", _eOesMsgType::OESMSG_QRYMSG_COMMISSION_RATE);
    e.value("OESMSG_QRYMSG_FUND_TRSF", _eOesMsgType::OESMSG_QRYMSG_FUND_TRSF);
    e.value("OESMSG_QRYMSG_STOCK", _eOesMsgType::OESMSG_QRYMSG_STOCK);
    e.value("OESMSG_QRYMSG_ETF", _eOesMsgType::OESMSG_QRYMSG_ETF);
    e.value("OESMSG_QRYMSG_ETF_COMPONENT", _eOesMsgType::OESMSG_QRYMSG_ETF_COMPONENT);
    e.value("OESMSG_QRYMSG_OPTION", _eOesMsgType::OESMSG_QRYMSG_OPTION);
    e.value("OESMSG_QRYMSG_ISSUE", _eOesMsgType::OESMSG_QRYMSG_ISSUE);
    e.value("OESMSG_QRYMSG_LOT_WINNING", _eOesMsgType::OESMSG_QRYMSG_LOT_WINNING);
    e.value("OESMSG_QRYMSG_TRADING_DAY", _eOesMsgType::OESMSG_QRYMSG_TRADING_DAY);
    e.value("OESMSG_QRYMSG_MARKET_STATE", _eOesMsgType::OESMSG_QRYMSG_MARKET_STATE);
    e.value("OESMSG_QRYMSG_COUNTER_CASH", _eOesMsgType::OESMSG_QRYMSG_COUNTER_CASH);
    e.value("__OESMSG_QRYMSG_MAX", _eOesMsgType::__OESMSG_QRYMSG_MAX);
    e.value("OESMSG_SESS_TRD_LOGIN", _eOesMsgType::OESMSG_SESS_TRD_LOGIN);
    e.value("OESMSG_SESS_RPT_LOGIN", _eOesMsgType::OESMSG_SESS_RPT_LOGIN);
    e.value("OESMSG_SESS_QRY_LOGIN", _eOesMsgType::OESMSG_SESS_QRY_LOGIN);
    e.value("OESMSG_SESS_HEARTBEAT", _eOesMsgType::OESMSG_SESS_HEARTBEAT);
    e.value("OESMSG_SESS_TEST_REQUEST", _eOesMsgType::OESMSG_SESS_TEST_REQUEST);
    e.value("OESMSG_SESS_LOGOUT", _eOesMsgType::OESMSG_SESS_LOGOUT);
    e.value("OESMSG_RPT_ORDER_REJECT", _eOesMsgType::OESMSG_RPT_ORDER_REJECT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMsgType", e);
}
void generate_enum_eOesSubscribeReportType(pybind11::object & parent)
{
    pybind11::enum_<_eOesSubscribeReportType> e(parent, "_eOesSubscribeReportType", pybind11::arithmetic());
    e.value("OES_SUB_RPT_TYPE_DEFAULT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_DEFAULT);
    e.value("OES_SUB_RPT_TYPE_BUSINESS_REJECT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_BUSINESS_REJECT);
    e.value("OES_SUB_RPT_TYPE_ORDER_INSERT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ORDER_INSERT);
    e.value("OES_SUB_RPT_TYPE_ORDER_REPORT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ORDER_REPORT);
    e.value("OES_SUB_RPT_TYPE_TRADE_REPORT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_TRADE_REPORT);
    e.value("OES_SUB_RPT_TYPE_FUND_TRSF_REPORT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_FUND_TRSF_REPORT);
    e.value("OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION);
    e.value("OES_SUB_RPT_TYPE_HOLDING_VARIATION", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_HOLDING_VARIATION);
    e.value("OES_SUB_RPT_TYPE_MARKET_STATE", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_MARKET_STATE);
    e.value("OES_SUB_RPT_TYPE_ALL", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ALL);
    e.value("__MAX_OES_SUB_RPT_TYPE", _eOesSubscribeReportType::__MAX_OES_SUB_RPT_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSubscribeReportType", e);
}
void generate_enum_eSSocketProtocolType(pybind11::object & parent)
{
    pybind11::enum_<_eSSocketProtocolType> e(parent, "_eSSocketProtocolType", pybind11::arithmetic());
    e.value("SPK_SOCKET_PROTOCOL_TCP", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_TCP);
    e.value("SPK_SOCKET_PROTOCOL_IPC", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_IPC);
    e.value("SPK_SOCKET_PROTOCOL_UDP_UCAST", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_UDP_UCAST);
    e.value("SPK_SOCKET_PROTOCOL_UDP_MCAST", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_UDP_MCAST);
    e.value("SPK_SOCKET_PROTOCOL_PGM", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_PGM);
    e.value("SPK_SOCKET_PROTOCOL_EPGM", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_EPGM);
    e.value("__MAX_SPK_SOCKET_PROTOCOL", _eSSocketProtocolType::__MAX_SPK_SOCKET_PROTOCOL);
    e.export_values();
    module_vnoes::objects.emplace("_eSSocketProtocolType", e);
}
void generate_enum_eGeneralClientClusterType(pybind11::object & parent)
{
    pybind11::enum_<_eGeneralClientClusterType> e(parent, "_eGeneralClientClusterType", pybind11::arithmetic());
    e.value("GENERAL_CLI_CLUSTER_UNDEFINED", _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_UNDEFINED);
    e.value("GENERAL_CLI_CLUSTER_REPLICA_SET", _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_REPLICA_SET);
    e.value("GENERAL_CLI_CLUSTER_PEER_NODES", _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_PEER_NODES);
    e.value("__MAX_GENERAL_CLI_CLUSTER_TYPE", _eGeneralClientClusterType::__MAX_GENERAL_CLI_CLUSTER_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eGeneralClientClusterType", e);
}
void generate_enum_eGeneralClientEncryptType(pybind11::object & parent)
{
    pybind11::enum_<_eGeneralClientEncryptType> e(parent, "_eGeneralClientEncryptType", pybind11::arithmetic());
    e.value("GENERAL_CLI_ENCRYPT_NONE", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_NONE);
    e.value("GENERAL_CLI_ENCRYPT_MD5", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_MD5);
    e.value("GENERAL_CLI_ENCRYPT_SHA", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_SHA);
    e.value("GENERAL_CLI_ENCRYPT_DES", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_DES);
    e.value("GENERAL_CLI_ENCRYPT_AES", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_AES);
    e.value("GENERAL_CLI_ENCRYPT_RSA", _eGeneralClientEncryptType::GENERAL_CLI_ENCRYPT_RSA);
    e.export_values();
    module_vnoes::objects.emplace("_eGeneralClientEncryptType", e);
}
void generate_enum_eOesApiChannelType(pybind11::object & parent)
{
    pybind11::enum_<_eOesApiChannelType> e(parent, "_eOesApiChannelType", pybind11::arithmetic());
    e.value("OESAPI_CHANNEL_TYPE_ORDER", _eOesApiChannelType::OESAPI_CHANNEL_TYPE_ORDER);
    e.value("OESAPI_CHANNEL_TYPE_REPORT", _eOesApiChannelType::OESAPI_CHANNEL_TYPE_REPORT);
    e.value("OESAPI_CHANNEL_TYPE_QUERY", _eOesApiChannelType::OESAPI_CHANNEL_TYPE_QUERY);
    e.export_values();
    module_vnoes::objects.emplace("_eOesApiChannelType", e);
}
