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


void generate_enum_eOesLotRejReason(pybind11::object & parent)
{
    // _eOesLotRejReason
    pybind11::enum_<_eOesLotRejReason> e(parent, "_eOesLotRejReason", pybind11::arithmetic());
    // _eOesLotRejReason::OES_LOT_REJ_REASON_DUPLICATE
    e.value("OES_LOT_REJ_REASON_DUPLICATE", _eOesLotRejReason::OES_LOT_REJ_REASON_DUPLICATE);
    // _eOesLotRejReason::OES_LOT_REJ_REASON_INVALID_DUPLICATE
    e.value("OES_LOT_REJ_REASON_INVALID_DUPLICATE", _eOesLotRejReason::OES_LOT_REJ_REASON_INVALID_DUPLICATE);
    // _eOesLotRejReason::OES_LOT_REJ_REASON_OFFLINE_FIRST
    e.value("OES_LOT_REJ_REASON_OFFLINE_FIRST", _eOesLotRejReason::OES_LOT_REJ_REASON_OFFLINE_FIRST);
    // _eOesLotRejReason::OES_LOT_REJ_REASON_BAD_RECORD
    e.value("OES_LOT_REJ_REASON_BAD_RECORD", _eOesLotRejReason::OES_LOT_REJ_REASON_BAD_RECORD);
    // _eOesLotRejReason::OES_LOT_REJ_REASON_UNKNOW
    e.value("OES_LOT_REJ_REASON_UNKNOW", _eOesLotRejReason::OES_LOT_REJ_REASON_UNKNOW);
    e.export_values();
    module_vnoes::objects.emplace("_eOesLotRejReason", e);
}
void generate_enum_eOesOrdStatus(pybind11::object & parent)
{
    // _eOesOrdStatus
    pybind11::enum_<_eOesOrdStatus> e(parent, "_eOesOrdStatus", pybind11::arithmetic());
    // _eOesOrdStatus::OES_ORD_STATUS_UNDEFINE
    e.value("OES_ORD_STATUS_UNDEFINE", _eOesOrdStatus::OES_ORD_STATUS_UNDEFINE);
    // _eOesOrdStatus::OES_ORD_STATUS_NEW
    e.value("OES_ORD_STATUS_NEW", _eOesOrdStatus::OES_ORD_STATUS_NEW);
    // _eOesOrdStatus::OES_ORD_STATUS_DECLARED
    e.value("OES_ORD_STATUS_DECLARED", _eOesOrdStatus::OES_ORD_STATUS_DECLARED);
    // _eOesOrdStatus::OES_ORD_STATUS_PARTIALLY_FILLED
    e.value("OES_ORD_STATUS_PARTIALLY_FILLED", _eOesOrdStatus::OES_ORD_STATUS_PARTIALLY_FILLED);
    // _eOesOrdStatus::__OES_ORD_STATUS_FINAL_MIN
    e.value("__OES_ORD_STATUS_FINAL_MIN", _eOesOrdStatus::__OES_ORD_STATUS_FINAL_MIN);
    // _eOesOrdStatus::OES_ORD_STATUS_CANCEL_DONE
    e.value("OES_ORD_STATUS_CANCEL_DONE", _eOesOrdStatus::OES_ORD_STATUS_CANCEL_DONE);
    // _eOesOrdStatus::OES_ORD_STATUS_PARTIALLY_CANCELED
    e.value("OES_ORD_STATUS_PARTIALLY_CANCELED", _eOesOrdStatus::OES_ORD_STATUS_PARTIALLY_CANCELED);
    // _eOesOrdStatus::OES_ORD_STATUS_CANCELED
    e.value("OES_ORD_STATUS_CANCELED", _eOesOrdStatus::OES_ORD_STATUS_CANCELED);
    // _eOesOrdStatus::OES_ORD_STATUS_FILLED
    e.value("OES_ORD_STATUS_FILLED", _eOesOrdStatus::OES_ORD_STATUS_FILLED);
    // _eOesOrdStatus::__OES_ORD_STATUS_VALID_MAX
    e.value("__OES_ORD_STATUS_VALID_MAX", _eOesOrdStatus::__OES_ORD_STATUS_VALID_MAX);
    // _eOesOrdStatus::__OES_ORD_STATUS_INVALID_MIN
    e.value("__OES_ORD_STATUS_INVALID_MIN", _eOesOrdStatus::__OES_ORD_STATUS_INVALID_MIN);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_OES
    e.value("OES_ORD_STATUS_INVALID_OES", _eOesOrdStatus::OES_ORD_STATUS_INVALID_OES);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_F
    e.value("OES_ORD_STATUS_INVALID_SH_F", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_F);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_E
    e.value("OES_ORD_STATUS_INVALID_SH_E", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_E);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_COMM
    e.value("OES_ORD_STATUS_INVALID_SH_COMM", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SH_COMM);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_F
    e.value("OES_ORD_STATUS_INVALID_SZ_F", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_F);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_E
    e.value("OES_ORD_STATUS_INVALID_SZ_E", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_E);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_REJECT
    e.value("OES_ORD_STATUS_INVALID_SZ_REJECT", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_REJECT);
    // _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN
    e.value("OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN", _eOesOrdStatus::OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN);
    // _eOesOrdStatus::__OES_ORD_STATUS_INVALID_MAX
    e.value("__OES_ORD_STATUS_INVALID_MAX", _eOesOrdStatus::__OES_ORD_STATUS_INVALID_MAX);
    // _eOesOrdStatus::OES_ORD_STATUS_NORMAL
    e.value("OES_ORD_STATUS_NORMAL", _eOesOrdStatus::OES_ORD_STATUS_NORMAL);
    // _eOesOrdStatus::OES_ORD_STATUS_DECLARING
    e.value("OES_ORD_STATUS_DECLARING", _eOesOrdStatus::OES_ORD_STATUS_DECLARING);
    // _eOesOrdStatus::__OES_ORD_STATUS_INVALID_OES
    e.value("__OES_ORD_STATUS_INVALID_OES", _eOesOrdStatus::__OES_ORD_STATUS_INVALID_OES);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdStatus", e);
}
void generate_enum_eOesOrdType(pybind11::object & parent)
{
    // _eOesOrdType
    pybind11::enum_<_eOesOrdType> e(parent, "_eOesOrdType", pybind11::arithmetic());
    // _eOesOrdType::OES_ORD_TYPE_LMT
    e.value("OES_ORD_TYPE_LMT", _eOesOrdType::OES_ORD_TYPE_LMT);
    // _eOesOrdType::OES_ORD_TYPE_LMT_FOK
    e.value("OES_ORD_TYPE_LMT_FOK", _eOesOrdType::OES_ORD_TYPE_LMT_FOK);
    // _eOesOrdType::__OES_ORD_TYPE_LMT_MAX
    e.value("__OES_ORD_TYPE_LMT_MAX", _eOesOrdType::__OES_ORD_TYPE_LMT_MAX);
    // _eOesOrdType::OES_ORD_TYPE_MTL_BEST_5
    e.value("OES_ORD_TYPE_MTL_BEST_5", _eOesOrdType::OES_ORD_TYPE_MTL_BEST_5);
    // _eOesOrdType::OES_ORD_TYPE_MTL_BEST
    e.value("OES_ORD_TYPE_MTL_BEST", _eOesOrdType::OES_ORD_TYPE_MTL_BEST);
    // _eOesOrdType::OES_ORD_TYPE_MTL_SAMEPARTY_BEST
    e.value("OES_ORD_TYPE_MTL_SAMEPARTY_BEST", _eOesOrdType::OES_ORD_TYPE_MTL_SAMEPARTY_BEST);
    // _eOesOrdType::__OES_ORD_TYPE_MTL_MAX
    e.value("__OES_ORD_TYPE_MTL_MAX", _eOesOrdType::__OES_ORD_TYPE_MTL_MAX);
    // _eOesOrdType::OES_ORD_TYPE_FAK_BEST_5
    e.value("OES_ORD_TYPE_FAK_BEST_5", _eOesOrdType::OES_ORD_TYPE_FAK_BEST_5);
    // _eOesOrdType::OES_ORD_TYPE_FAK
    e.value("OES_ORD_TYPE_FAK", _eOesOrdType::OES_ORD_TYPE_FAK);
    // _eOesOrdType::__OES_ORD_TYPE_FAK_MAX
    e.value("__OES_ORD_TYPE_FAK_MAX", _eOesOrdType::__OES_ORD_TYPE_FAK_MAX);
    // _eOesOrdType::OES_ORD_TYPE_FOK
    e.value("OES_ORD_TYPE_FOK", _eOesOrdType::OES_ORD_TYPE_FOK);
    // _eOesOrdType::__OES_ORD_TYPE_FOK_MAX
    e.value("__OES_ORD_TYPE_FOK_MAX", _eOesOrdType::__OES_ORD_TYPE_FOK_MAX);
    // _eOesOrdType::__OES_ORD_TYPE_MAX
    e.value("__OES_ORD_TYPE_MAX", _eOesOrdType::__OES_ORD_TYPE_MAX);
    // _eOesOrdType::__OES_ORD_TYPE_MAX_ALIGNED
    e.value("__OES_ORD_TYPE_MAX_ALIGNED", _eOesOrdType::__OES_ORD_TYPE_MAX_ALIGNED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdType", e);
}
void generate_enum_eOesOrdTypeSh(pybind11::object & parent)
{
    // _eOesOrdTypeSh
    pybind11::enum_<_eOesOrdTypeSh> e(parent, "_eOesOrdTypeSh", pybind11::arithmetic());
    // _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT
    e.value("OES_ORD_TYPE_SH_LMT", _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT);
    // _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT_FOK
    e.value("OES_ORD_TYPE_SH_LMT_FOK", _eOesOrdTypeSh::OES_ORD_TYPE_SH_LMT_FOK);
    // _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_BEST_5
    e.value("OES_ORD_TYPE_SH_MTL_BEST_5", _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_BEST_5);
    // _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_BEST
    e.value("OES_ORD_TYPE_SH_MTL_BEST", _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_BEST);
    // _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_SAMEPARTY_BEST
    e.value("OES_ORD_TYPE_SH_MTL_SAMEPARTY_BEST", _eOesOrdTypeSh::OES_ORD_TYPE_SH_MTL_SAMEPARTY_BEST);
    // _eOesOrdTypeSh::OES_ORD_TYPE_SH_FAK_BEST_5
    e.value("OES_ORD_TYPE_SH_FAK_BEST_5", _eOesOrdTypeSh::OES_ORD_TYPE_SH_FAK_BEST_5);
    // _eOesOrdTypeSh::OES_ORD_TYPE_SH_FOK
    e.value("OES_ORD_TYPE_SH_FOK", _eOesOrdTypeSh::OES_ORD_TYPE_SH_FOK);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdTypeSh", e);
}
void generate_enum_eOesOrdTypeSz(pybind11::object & parent)
{
    // _eOesOrdTypeSz
    pybind11::enum_<_eOesOrdTypeSz> e(parent, "_eOesOrdTypeSz", pybind11::arithmetic());
    // _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT
    e.value("OES_ORD_TYPE_SZ_LMT", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT);
    // _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT_FOK
    e.value("OES_ORD_TYPE_SZ_LMT_FOK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_LMT_FOK);
    // _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_BEST
    e.value("OES_ORD_TYPE_SZ_MTL_BEST", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_BEST);
    // _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST
    e.value("OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST);
    // _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK_BEST_5
    e.value("OES_ORD_TYPE_SZ_FAK_BEST_5", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK_BEST_5);
    // _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK
    e.value("OES_ORD_TYPE_SZ_FAK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FAK);
    // _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FOK
    e.value("OES_ORD_TYPE_SZ_FOK", _eOesOrdTypeSz::OES_ORD_TYPE_SZ_FOK);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdTypeSz", e);
}
void generate_enum_eOesBuySellType(pybind11::object & parent)
{
    // _eOesBuySellType
    pybind11::enum_<_eOesBuySellType> e(parent, "_eOesBuySellType", pybind11::arithmetic());
    // _eOesBuySellType::OES_BS_TYPE_UNDEFINE
    e.value("OES_BS_TYPE_UNDEFINE", _eOesBuySellType::OES_BS_TYPE_UNDEFINE);
    // _eOesBuySellType::OES_BS_TYPE_BUY
    e.value("OES_BS_TYPE_BUY", _eOesBuySellType::OES_BS_TYPE_BUY);
    // _eOesBuySellType::OES_BS_TYPE_SELL
    e.value("OES_BS_TYPE_SELL", _eOesBuySellType::OES_BS_TYPE_SELL);
    // _eOesBuySellType::OES_BS_TYPE_CREATION
    e.value("OES_BS_TYPE_CREATION", _eOesBuySellType::OES_BS_TYPE_CREATION);
    // _eOesBuySellType::OES_BS_TYPE_REDEMPTION
    e.value("OES_BS_TYPE_REDEMPTION", _eOesBuySellType::OES_BS_TYPE_REDEMPTION);
    // _eOesBuySellType::OES_BS_TYPE_CREDIT_BUY
    e.value("OES_BS_TYPE_CREDIT_BUY", _eOesBuySellType::OES_BS_TYPE_CREDIT_BUY);
    // _eOesBuySellType::OES_BS_TYPE_CREDIT_SELL
    e.value("OES_BS_TYPE_CREDIT_SELL", _eOesBuySellType::OES_BS_TYPE_CREDIT_SELL);
    // _eOesBuySellType::OES_BS_TYPE_SUBSCRIPTION
    e.value("OES_BS_TYPE_SUBSCRIPTION", _eOesBuySellType::OES_BS_TYPE_SUBSCRIPTION);
    // _eOesBuySellType::OES_BS_TYPE_ALLOTMENT
    e.value("OES_BS_TYPE_ALLOTMENT", _eOesBuySellType::OES_BS_TYPE_ALLOTMENT);
    // _eOesBuySellType::__OES_BS_TYPE_MAX_SPOT
    e.value("__OES_BS_TYPE_MAX_SPOT", _eOesBuySellType::__OES_BS_TYPE_MAX_SPOT);
    // _eOesBuySellType::__OES_BS_TYPE_MIN_OPTION
    e.value("__OES_BS_TYPE_MIN_OPTION", _eOesBuySellType::__OES_BS_TYPE_MIN_OPTION);
    // _eOesBuySellType::OES_BS_TYPE_BUY_OPEN
    e.value("OES_BS_TYPE_BUY_OPEN", _eOesBuySellType::OES_BS_TYPE_BUY_OPEN);
    // _eOesBuySellType::OES_BS_TYPE_BUY_CLOSE
    e.value("OES_BS_TYPE_BUY_CLOSE", _eOesBuySellType::OES_BS_TYPE_BUY_CLOSE);
    // _eOesBuySellType::OES_BS_TYPE_SELL_OPEN
    e.value("OES_BS_TYPE_SELL_OPEN", _eOesBuySellType::OES_BS_TYPE_SELL_OPEN);
    // _eOesBuySellType::OES_BS_TYPE_SELL_CLOSE
    e.value("OES_BS_TYPE_SELL_CLOSE", _eOesBuySellType::OES_BS_TYPE_SELL_CLOSE);
    // _eOesBuySellType::OES_BS_TYPE_COVERED_OPEN
    e.value("OES_BS_TYPE_COVERED_OPEN", _eOesBuySellType::OES_BS_TYPE_COVERED_OPEN);
    // _eOesBuySellType::OES_BS_TYPE_COVERED_CLOSE
    e.value("OES_BS_TYPE_COVERED_CLOSE", _eOesBuySellType::OES_BS_TYPE_COVERED_CLOSE);
    // _eOesBuySellType::OES_BS_TYPE_OPTION_EXERCISE
    e.value("OES_BS_TYPE_OPTION_EXERCISE", _eOesBuySellType::OES_BS_TYPE_OPTION_EXERCISE);
    // _eOesBuySellType::OES_BS_TYPE_UNDERLYING_FREEZE
    e.value("OES_BS_TYPE_UNDERLYING_FREEZE", _eOesBuySellType::OES_BS_TYPE_UNDERLYING_FREEZE);
    // _eOesBuySellType::OES_BS_TYPE_UNDERLYING_UNFREEZE
    e.value("OES_BS_TYPE_UNDERLYING_UNFREEZE", _eOesBuySellType::OES_BS_TYPE_UNDERLYING_UNFREEZE);
    // _eOesBuySellType::__OES_BS_TYPE_MAX_OPTION
    e.value("__OES_BS_TYPE_MAX_OPTION", _eOesBuySellType::__OES_BS_TYPE_MAX_OPTION);
    // _eOesBuySellType::OES_BS_TYPE_CANCEL
    e.value("OES_BS_TYPE_CANCEL", _eOesBuySellType::OES_BS_TYPE_CANCEL);
    // _eOesBuySellType::__OES_BS_TYPE_MAX_TRADING
    e.value("__OES_BS_TYPE_MAX_TRADING", _eOesBuySellType::__OES_BS_TYPE_MAX_TRADING);
    // _eOesBuySellType::__OES_BS_TYPE_MIN_MGR
    e.value("__OES_BS_TYPE_MIN_MGR", _eOesBuySellType::__OES_BS_TYPE_MIN_MGR);
    // _eOesBuySellType::OES_BS_TYPE_SSE_DESIGNATION
    e.value("OES_BS_TYPE_SSE_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SSE_DESIGNATION);
    // _eOesBuySellType::OES_BS_TYPE_SSE_RECALL_DESIGNATION
    e.value("OES_BS_TYPE_SSE_RECALL_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SSE_RECALL_DESIGNATION);
    // _eOesBuySellType::OES_BS_TYPE_SZSE_DESIGNATION
    e.value("OES_BS_TYPE_SZSE_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SZSE_DESIGNATION);
    // _eOesBuySellType::OES_BS_TYPE_SZSE_CANCEL_DESIGNATION
    e.value("OES_BS_TYPE_SZSE_CANCEL_DESIGNATION", _eOesBuySellType::OES_BS_TYPE_SZSE_CANCEL_DESIGNATION);
    // _eOesBuySellType::__OES_BS_TYPE_MAX_MGR
    e.value("__OES_BS_TYPE_MAX_MGR", _eOesBuySellType::__OES_BS_TYPE_MAX_MGR);
    // _eOesBuySellType::__OES_BS_TYPE_MAX
    e.value("__OES_BS_TYPE_MAX", _eOesBuySellType::__OES_BS_TYPE_MAX);
    // _eOesBuySellType::OES_BS_TYPE_B
    e.value("OES_BS_TYPE_B", _eOesBuySellType::OES_BS_TYPE_B);
    // _eOesBuySellType::OES_BS_TYPE_S
    e.value("OES_BS_TYPE_S", _eOesBuySellType::OES_BS_TYPE_S);
    // _eOesBuySellType::OES_BS_TYPE_KB
    e.value("OES_BS_TYPE_KB", _eOesBuySellType::OES_BS_TYPE_KB);
    // _eOesBuySellType::OES_BS_TYPE_KS
    e.value("OES_BS_TYPE_KS", _eOesBuySellType::OES_BS_TYPE_KS);
    // _eOesBuySellType::OES_BS_TYPE_CB
    e.value("OES_BS_TYPE_CB", _eOesBuySellType::OES_BS_TYPE_CB);
    // _eOesBuySellType::OES_BS_TYPE_CS
    e.value("OES_BS_TYPE_CS", _eOesBuySellType::OES_BS_TYPE_CS);
    // _eOesBuySellType::OES_BS_TYPE_BO
    e.value("OES_BS_TYPE_BO", _eOesBuySellType::OES_BS_TYPE_BO);
    // _eOesBuySellType::OES_BS_TYPE_BC
    e.value("OES_BS_TYPE_BC", _eOesBuySellType::OES_BS_TYPE_BC);
    // _eOesBuySellType::OES_BS_TYPE_SO
    e.value("OES_BS_TYPE_SO", _eOesBuySellType::OES_BS_TYPE_SO);
    // _eOesBuySellType::OES_BS_TYPE_SC
    e.value("OES_BS_TYPE_SC", _eOesBuySellType::OES_BS_TYPE_SC);
    // _eOesBuySellType::OES_BS_TYPE_CO
    e.value("OES_BS_TYPE_CO", _eOesBuySellType::OES_BS_TYPE_CO);
    // _eOesBuySellType::OES_BS_TYPE_CC
    e.value("OES_BS_TYPE_CC", _eOesBuySellType::OES_BS_TYPE_CC);
    // _eOesBuySellType::OES_BS_TYPE_TE
    e.value("OES_BS_TYPE_TE", _eOesBuySellType::OES_BS_TYPE_TE);
    // _eOesBuySellType::OES_BS_TYPE_UF
    e.value("OES_BS_TYPE_UF", _eOesBuySellType::OES_BS_TYPE_UF);
    // _eOesBuySellType::OES_BS_TYPE_UU
    e.value("OES_BS_TYPE_UU", _eOesBuySellType::OES_BS_TYPE_UU);
    e.export_values();
    module_vnoes::objects.emplace("_eOesBuySellType", e);
}
void generate_enum_eOesOrdDir(pybind11::object & parent)
{
    // _eOesOrdDir
    pybind11::enum_<_eOesOrdDir> e(parent, "_eOesOrdDir", pybind11::arithmetic());
    // _eOesOrdDir::OES_ORD_DIR_BUY
    e.value("OES_ORD_DIR_BUY", _eOesOrdDir::OES_ORD_DIR_BUY);
    // _eOesOrdDir::OES_ORD_DIR_SELL
    e.value("OES_ORD_DIR_SELL", _eOesOrdDir::OES_ORD_DIR_SELL);
    // _eOesOrdDir::__OES_ORD_DIR_MAX
    e.value("__OES_ORD_DIR_MAX", _eOesOrdDir::__OES_ORD_DIR_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOrdDir", e);
}
void generate_enum_eOesEtfTrdCnfmType(pybind11::object & parent)
{
    // _eOesEtfTrdCnfmType
    pybind11::enum_<_eOesEtfTrdCnfmType> e(parent, "_eOesEtfTrdCnfmType", pybind11::arithmetic());
    // _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_NONE
    e.value("OES_ETF_TRDCNFM_TYPE_NONE", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_NONE);
    // _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_ETF_FIRST
    e.value("OES_ETF_TRDCNFM_TYPE_ETF_FIRST", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_ETF_FIRST);
    // _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_CMPOENT
    e.value("OES_ETF_TRDCNFM_TYPE_CMPOENT", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_CMPOENT);
    // _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_CASH
    e.value("OES_ETF_TRDCNFM_TYPE_CASH", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_CASH);
    // _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_ETF_LAST
    e.value("OES_ETF_TRDCNFM_TYPE_ETF_LAST", _eOesEtfTrdCnfmType::OES_ETF_TRDCNFM_TYPE_ETF_LAST);
    // _eOesEtfTrdCnfmType::__OES_ETF_TRDCNFM_TYPE_MAX
    e.value("__OES_ETF_TRDCNFM_TYPE_MAX", _eOesEtfTrdCnfmType::__OES_ETF_TRDCNFM_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesEtfTrdCnfmType", e);
}
void generate_enum_eOesEtfSubFlag(pybind11::object & parent)
{
    // _eOesEtfSubFlag
    pybind11::enum_<_eOesEtfSubFlag> e(parent, "_eOesEtfSubFlag", pybind11::arithmetic());
    // _eOesEtfSubFlag::OES_ETF_SUBFLAG_FORBID_SUB
    e.value("OES_ETF_SUBFLAG_FORBID_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_FORBID_SUB);
    // _eOesEtfSubFlag::OES_ETF_SUBFLAG_ALLOW_SUB
    e.value("OES_ETF_SUBFLAG_ALLOW_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_ALLOW_SUB);
    // _eOesEtfSubFlag::OES_ETF_SUBFLAG_MUST_SUB
    e.value("OES_ETF_SUBFLAG_MUST_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_MUST_SUB);
    // _eOesEtfSubFlag::OES_ETF_SUBFLAG_SZ_REFUND_SUB
    e.value("OES_ETF_SUBFLAG_SZ_REFUND_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_SZ_REFUND_SUB);
    // _eOesEtfSubFlag::OES_ETF_SUBFLAG_SZ_MUST_SUB
    e.value("OES_ETF_SUBFLAG_SZ_MUST_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_SZ_MUST_SUB);
    // _eOesEtfSubFlag::OES_ETF_SUBFLAG_OTHER_REFUND_SUB
    e.value("OES_ETF_SUBFLAG_OTHER_REFUND_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_OTHER_REFUND_SUB);
    // _eOesEtfSubFlag::OES_ETF_SUBFLAG_OTHER_MUST_SUB
    e.value("OES_ETF_SUBFLAG_OTHER_MUST_SUB", _eOesEtfSubFlag::OES_ETF_SUBFLAG_OTHER_MUST_SUB);
    e.export_values();
    module_vnoes::objects.emplace("_eOesEtfSubFlag", e);
}
void generate_enum_eOesExecType(pybind11::object & parent)
{
    // _eOesExecType
    pybind11::enum_<_eOesExecType> e(parent, "_eOesExecType", pybind11::arithmetic());
    // _eOesExecType::OES_EXECTYPE_UNDEFINE
    e.value("OES_EXECTYPE_UNDEFINE", _eOesExecType::OES_EXECTYPE_UNDEFINE);
    // _eOesExecType::OES_EXECTYPE_INSERT
    e.value("OES_EXECTYPE_INSERT", _eOesExecType::OES_EXECTYPE_INSERT);
    // _eOesExecType::OES_EXECTYPE_CONFIRMED
    e.value("OES_EXECTYPE_CONFIRMED", _eOesExecType::OES_EXECTYPE_CONFIRMED);
    // _eOesExecType::OES_EXECTYPE_CANCELLED
    e.value("OES_EXECTYPE_CANCELLED", _eOesExecType::OES_EXECTYPE_CANCELLED);
    // _eOesExecType::OES_EXECTYPE_AUTO_CANCELLED
    e.value("OES_EXECTYPE_AUTO_CANCELLED", _eOesExecType::OES_EXECTYPE_AUTO_CANCELLED);
    // _eOesExecType::OES_EXECTYPE_REJECT
    e.value("OES_EXECTYPE_REJECT", _eOesExecType::OES_EXECTYPE_REJECT);
    // _eOesExecType::OES_EXECTYPE_TRADE
    e.value("OES_EXECTYPE_TRADE", _eOesExecType::OES_EXECTYPE_TRADE);
    // _eOesExecType::__OES_EXECTYPE_MAX
    e.value("__OES_EXECTYPE_MAX", _eOesExecType::__OES_EXECTYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesExecType", e);
}
void generate_enum_eOesCurrType(pybind11::object & parent)
{
    // _eOesCurrType
    pybind11::enum_<_eOesCurrType> e(parent, "_eOesCurrType", pybind11::arithmetic());
    // _eOesCurrType::OES_CURR_TYPE_RMB
    e.value("OES_CURR_TYPE_RMB", _eOesCurrType::OES_CURR_TYPE_RMB);
    // _eOesCurrType::OES_CURR_TYPE_HKD
    e.value("OES_CURR_TYPE_HKD", _eOesCurrType::OES_CURR_TYPE_HKD);
    // _eOesCurrType::OES_CURR_TYPE_USD
    e.value("OES_CURR_TYPE_USD", _eOesCurrType::OES_CURR_TYPE_USD);
    // _eOesCurrType::__OES_CURR_TYPE_MAX
    e.value("__OES_CURR_TYPE_MAX", _eOesCurrType::__OES_CURR_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCurrType", e);
}
void generate_enum_eOesFeeType(pybind11::object & parent)
{
    // _eOesFeeType
    pybind11::enum_<_eOesFeeType> e(parent, "_eOesFeeType", pybind11::arithmetic());
    // _eOesFeeType::OES_FEE_TYPE_EXCHANGE_STAMP
    e.value("OES_FEE_TYPE_EXCHANGE_STAMP", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_STAMP);
    // _eOesFeeType::OES_FEE_TYPE_EXCHANGE_TRANSFER
    e.value("OES_FEE_TYPE_EXCHANGE_TRANSFER", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_TRANSFER);
    // _eOesFeeType::OES_FEE_TYPE_EXCHANGE_SETTLEMENT
    e.value("OES_FEE_TYPE_EXCHANGE_SETTLEMENT", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_SETTLEMENT);
    // _eOesFeeType::OES_FEE_TYPE_EXCHANGE_TRADE_RULE
    e.value("OES_FEE_TYPE_EXCHANGE_TRADE_RULE", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_TRADE_RULE);
    // _eOesFeeType::OES_FEE_TYPE_EXCHANGE_EXCHANGE
    e.value("OES_FEE_TYPE_EXCHANGE_EXCHANGE", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_EXCHANGE);
    // _eOesFeeType::OES_FEE_TYPE_EXCHANGE_ADMINFER
    e.value("OES_FEE_TYPE_EXCHANGE_ADMINFER", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_ADMINFER);
    // _eOesFeeType::OES_FEE_TYPE_EXCHANGE_OTHER
    e.value("OES_FEE_TYPE_EXCHANGE_OTHER", _eOesFeeType::OES_FEE_TYPE_EXCHANGE_OTHER);
    // _eOesFeeType::__OES_FEE_TYPE_EXCHANGE_MAX
    e.value("__OES_FEE_TYPE_EXCHANGE_MAX", _eOesFeeType::__OES_FEE_TYPE_EXCHANGE_MAX);
    // _eOesFeeType::OES_FEE_TYPE_BROKER_BACK_END
    e.value("OES_FEE_TYPE_BROKER_BACK_END", _eOesFeeType::OES_FEE_TYPE_BROKER_BACK_END);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFeeType", e);
}
void generate_enum_eOesCalcFeeMode(pybind11::object & parent)
{
    // _eOesCalcFeeMode
    pybind11::enum_<_eOesCalcFeeMode> e(parent, "_eOesCalcFeeMode", pybind11::arithmetic());
    // _eOesCalcFeeMode::OES_CALC_FEE_MODE_AMOUNT
    e.value("OES_CALC_FEE_MODE_AMOUNT", _eOesCalcFeeMode::OES_CALC_FEE_MODE_AMOUNT);
    // _eOesCalcFeeMode::OES_CALC_FEE_MODE_QTY
    e.value("OES_CALC_FEE_MODE_QTY", _eOesCalcFeeMode::OES_CALC_FEE_MODE_QTY);
    // _eOesCalcFeeMode::OES_CALC_FEE_MODE_ORD
    e.value("OES_CALC_FEE_MODE_ORD", _eOesCalcFeeMode::OES_CALC_FEE_MODE_ORD);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCalcFeeMode", e);
}
void generate_enum_eOesFundTrsfDirect(pybind11::object & parent)
{
    // _eOesFundTrsfDirect
    pybind11::enum_<_eOesFundTrsfDirect> e(parent, "_eOesFundTrsfDirect", pybind11::arithmetic());
    // _eOesFundTrsfDirect::OES_FUND_TRSF_DIRECT_IN
    e.value("OES_FUND_TRSF_DIRECT_IN", _eOesFundTrsfDirect::OES_FUND_TRSF_DIRECT_IN);
    // _eOesFundTrsfDirect::OES_FUND_TRSF_DIRECT_OUT
    e.value("OES_FUND_TRSF_DIRECT_OUT", _eOesFundTrsfDirect::OES_FUND_TRSF_DIRECT_OUT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFundTrsfDirect", e);
}
void generate_enum_eOesFundTrsfType(pybind11::object & parent)
{
    // _eOesFundTrsfType
    pybind11::enum_<_eOesFundTrsfType> e(parent, "_eOesFundTrsfType", pybind11::arithmetic());
    // _eOesFundTrsfType::OES_FUND_TRSF_TYPE_OES_BANK
    e.value("OES_FUND_TRSF_TYPE_OES_BANK", _eOesFundTrsfType::OES_FUND_TRSF_TYPE_OES_BANK);
    // _eOesFundTrsfType::OES_FUND_TRSF_TYPE_OES_COUNTER
    e.value("OES_FUND_TRSF_TYPE_OES_COUNTER", _eOesFundTrsfType::OES_FUND_TRSF_TYPE_OES_COUNTER);
    // _eOesFundTrsfType::OES_FUND_TRSF_TYPE_COUNTER_BANK
    e.value("OES_FUND_TRSF_TYPE_COUNTER_BANK", _eOesFundTrsfType::OES_FUND_TRSF_TYPE_COUNTER_BANK);
    // _eOesFundTrsfType::__OES_FUND_TRSF_TYPE_MAX
    e.value("__OES_FUND_TRSF_TYPE_MAX", _eOesFundTrsfType::__OES_FUND_TRSF_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFundTrsfType", e);
}
void generate_enum_eOesFundTrsfStatus(pybind11::object & parent)
{
    // _eOesFundTrsfStatus
    pybind11::enum_<_eOesFundTrsfStatus> e(parent, "_eOesFundTrsfStatus", pybind11::arithmetic());
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_UNDECLARED
    e.value("OES_FUND_TRSF_STS_UNDECLARED", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_UNDECLARED);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DECLARED
    e.value("OES_FUND_TRSF_STS_DECLARED", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DECLARED);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_WAIT_DONE
    e.value("OES_FUND_TRSF_STS_WAIT_DONE", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_WAIT_DONE);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DONE
    e.value("OES_FUND_TRSF_STS_DONE", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DONE);
    // _eOesFundTrsfStatus::__OES_FUND_TRSF_STS_ROLLBACK_MIN
    e.value("__OES_FUND_TRSF_STS_ROLLBACK_MIN", _eOesFundTrsfStatus::__OES_FUND_TRSF_STS_ROLLBACK_MIN);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK
    e.value("OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DECLARED_ROLLBACK
    e.value("OES_FUND_TRSF_STS_DECLARED_ROLLBACK", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_DECLARED_ROLLBACK);
    // _eOesFundTrsfStatus::__OES_FUND_TRSF_STS_INVALID_MIN
    e.value("__OES_FUND_TRSF_STS_INVALID_MIN", _eOesFundTrsfStatus::__OES_FUND_TRSF_STS_INVALID_MIN);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_INVALID_OES
    e.value("OES_FUND_TRSF_STS_INVALID_OES", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_INVALID_OES);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_INVALID_COUNTER
    e.value("OES_FUND_TRSF_STS_INVALID_COUNTER", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_INVALID_COUNTER);
    // _eOesFundTrsfStatus::OES_FUND_TRSF_STS_SUSPENDED
    e.value("OES_FUND_TRSF_STS_SUSPENDED", _eOesFundTrsfStatus::OES_FUND_TRSF_STS_SUSPENDED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesFundTrsfStatus", e);
}
void generate_enum_eOesAcctType(pybind11::object & parent)
{
    // _eOesAcctType
    pybind11::enum_<_eOesAcctType> e(parent, "_eOesAcctType", pybind11::arithmetic());
    // _eOesAcctType::OES_ACCT_TYPE_NORMAL
    e.value("OES_ACCT_TYPE_NORMAL", _eOesAcctType::OES_ACCT_TYPE_NORMAL);
    // _eOesAcctType::OES_ACCT_TYPE_CREDIT
    e.value("OES_ACCT_TYPE_CREDIT", _eOesAcctType::OES_ACCT_TYPE_CREDIT);
    // _eOesAcctType::OES_ACCT_TYPE_OPTION
    e.value("OES_ACCT_TYPE_OPTION", _eOesAcctType::OES_ACCT_TYPE_OPTION);
    // _eOesAcctType::__OES_ACCT_TYPE_MAX
    e.value("__OES_ACCT_TYPE_MAX", _eOesAcctType::__OES_ACCT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesAcctType", e);
}
void generate_enum_eOesCashType(pybind11::object & parent)
{
    // _eOesCashType
    pybind11::enum_<_eOesCashType> e(parent, "_eOesCashType", pybind11::arithmetic());
    // _eOesCashType::OES_CASH_TYPE_SPOT
    e.value("OES_CASH_TYPE_SPOT", _eOesCashType::OES_CASH_TYPE_SPOT);
    // _eOesCashType::OES_CASH_TYPE_CREDIT
    e.value("OES_CASH_TYPE_CREDIT", _eOesCashType::OES_CASH_TYPE_CREDIT);
    // _eOesCashType::OES_CASH_TYPE_OPTION
    e.value("OES_CASH_TYPE_OPTION", _eOesCashType::OES_CASH_TYPE_OPTION);
    // _eOesCashType::__OES_CASH_TYPE_MAX
    e.value("__OES_CASH_TYPE_MAX", _eOesCashType::__OES_CASH_TYPE_MAX);
    // _eOesCashType::OES_CASH_TYPE_CRE
    e.value("OES_CASH_TYPE_CRE", _eOesCashType::OES_CASH_TYPE_CRE);
    // _eOesCashType::OES_CASH_TYPE_OPT
    e.value("OES_CASH_TYPE_OPT", _eOesCashType::OES_CASH_TYPE_OPT);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCashType", e);
}
void generate_enum_eOesAcctStatus(pybind11::object & parent)
{
    // _eOesAcctStatus
    pybind11::enum_<_eOesAcctStatus> e(parent, "_eOesAcctStatus", pybind11::arithmetic());
    // _eOesAcctStatus::OES_ACCT_STATUS_NORMAL
    e.value("OES_ACCT_STATUS_NORMAL", _eOesAcctStatus::OES_ACCT_STATUS_NORMAL);
    // _eOesAcctStatus::OES_ACCT_STATUS_DISABLED
    e.value("OES_ACCT_STATUS_DISABLED", _eOesAcctStatus::OES_ACCT_STATUS_DISABLED);
    // _eOesAcctStatus::OES_ACCT_STATUS_LOCKED
    e.value("OES_ACCT_STATUS_LOCKED", _eOesAcctStatus::OES_ACCT_STATUS_LOCKED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesAcctStatus", e);
}
