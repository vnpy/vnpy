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
    e.value("OES_PERMIS_HLTCDR", _eOesTradingPermission::OES_PERMIS_HLTCDR);
    e.value("OES_PERMIS_CDR", _eOesTradingPermission::OES_PERMIS_CDR);
    e.value("OES_PERMIS_INNOVATION", _eOesTradingPermission::OES_PERMIS_INNOVATION);
    e.value("OES_PERMIS_KSH", _eOesTradingPermission::OES_PERMIS_KSH);
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
void generate_enum_eOesCustType(pybind11::object & parent)
{
    pybind11::enum_<_eOesCustType> e(parent, "_eOesCustType", pybind11::arithmetic());
    e.value("OES_CUST_TYPE_PERSONAL", _eOesCustType::OES_CUST_TYPE_PERSONAL);
    e.value("OES_CUST_TYPE_INSTITUTION", _eOesCustType::OES_CUST_TYPE_INSTITUTION);
    e.value("OES_CUST_TYPE_PROPRIETARY", _eOesCustType::OES_CUST_TYPE_PROPRIETARY);
    e.value("OES_CUST_TYPE_PRODUCT", _eOesCustType::OES_CUST_TYPE_PRODUCT);
    e.value("OES_CUST_TYPE_MKT_MAKER", _eOesCustType::OES_CUST_TYPE_MKT_MAKER);
    e.value("OES_CUST_TYPE_OTHERS", _eOesCustType::OES_CUST_TYPE_OTHERS);
    e.value("__OES_CUST_TYPE_MAX", _eOesCustType::__OES_CUST_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCustType", e);
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
    e.value("OESMSG_RPT_SERVICE_STATE", _eOesMsgType::OESMSG_RPT_SERVICE_STATE);
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
    e.value("OESMSG_QRYMSG_COMMISSION_RATE", _eOesMsgType::OESMSG_QRYMSG_COMMISSION_RATE);
    e.value("OESMSG_QRYMSG_FUND_TRSF", _eOesMsgType::OESMSG_QRYMSG_FUND_TRSF);
    e.value("OESMSG_QRYMSG_ETF", _eOesMsgType::OESMSG_QRYMSG_ETF);
    e.value("OESMSG_QRYMSG_ETF_COMPONENT", _eOesMsgType::OESMSG_QRYMSG_ETF_COMPONENT);
    e.value("OESMSG_QRYMSG_OPTION", _eOesMsgType::OESMSG_QRYMSG_OPTION);
    e.value("OESMSG_QRYMSG_ISSUE", _eOesMsgType::OESMSG_QRYMSG_ISSUE);
    e.value("OESMSG_QRYMSG_LOT_WINNING", _eOesMsgType::OESMSG_QRYMSG_LOT_WINNING);
    e.value("OESMSG_QRYMSG_TRADING_DAY", _eOesMsgType::OESMSG_QRYMSG_TRADING_DAY);
    e.value("OESMSG_QRYMSG_MARKET_STATE", _eOesMsgType::OESMSG_QRYMSG_MARKET_STATE);
    e.value("OESMSG_QRYMSG_COUNTER_CASH", _eOesMsgType::OESMSG_QRYMSG_COUNTER_CASH);
    e.value("OESMSG_QRYMSG_INV_ACCT", _eOesMsgType::OESMSG_QRYMSG_INV_ACCT);
    e.value("OESMSG_QRYMSG_STOCK", _eOesMsgType::OESMSG_QRYMSG_STOCK);
    e.value("__OESMSG_QRYMSG_MAX", _eOesMsgType::__OESMSG_QRYMSG_MAX);
    e.value("OESMSG_SESS_HEARTBEAT", _eOesMsgType::OESMSG_SESS_HEARTBEAT);
    e.value("OESMSG_SESS_TEST_REQUEST", _eOesMsgType::OESMSG_SESS_TEST_REQUEST);
    e.value("OESMSG_SESS_LOGIN_EXTEND", _eOesMsgType::OESMSG_SESS_LOGIN_EXTEND);
    e.value("OESMSG_SESS_LOGOUT", _eOesMsgType::OESMSG_SESS_LOGOUT);
    e.value("OESMSG_RPT_ORDER_REJECT", _eOesMsgType::OESMSG_RPT_ORDER_REJECT);
    e.value("OESMSG_QRYMSG_INV_ACCT_L001508", _eOesMsgType::OESMSG_QRYMSG_INV_ACCT_L001508);
    e.value("OESMSG_QRYMSG_STOCK_L001508", _eOesMsgType::OESMSG_QRYMSG_STOCK_L001508);
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
void generate_enum_eOesProtocolHintsType(pybind11::object & parent)
{
    pybind11::enum_<_eOesProtocolHintsType> e(parent, "_eOesProtocolHintsType", pybind11::arithmetic());
    e.value("OES_PROT_HINTS_TYPE_DEFAULT", _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_DEFAULT);
    e.value("OES_PROT_HINTS_TYPE_COMPRESS", _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_COMPRESS);
    e.value("OES_PROT_HINTS_TYPE_NONE", _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_NONE);
    e.value("__MAX_OES_PROT_HINTS_TYPE", _eOesProtocolHintsType::__MAX_OES_PROT_HINTS_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eOesProtocolHintsType", e);
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
    e.value("__GENERAL_CLI_ENCRYPT_MASK_DIGESTED", _eGeneralClientEncryptType::__GENERAL_CLI_ENCRYPT_MASK_DIGESTED);
    e.value("__GENERAL_CLI_ENCRYPT_MASK_ENCRYPTED", _eGeneralClientEncryptType::__GENERAL_CLI_ENCRYPT_MASK_ENCRYPTED);
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
void generate_enum_eMdsExchangeId(pybind11::object & parent)
{
    pybind11::enum_<_eMdsExchangeId> e(parent, "_eMdsExchangeId", pybind11::arithmetic());
    e.value("MDS_EXCH_UNDEFINE", _eMdsExchangeId::MDS_EXCH_UNDEFINE);
    e.value("MDS_EXCH_SSE", _eMdsExchangeId::MDS_EXCH_SSE);
    e.value("MDS_EXCH_SZSE", _eMdsExchangeId::MDS_EXCH_SZSE);
    e.value("__MAX_MDS_EXCH", _eMdsExchangeId::__MAX_MDS_EXCH);
    e.value("__MAX_MDS_EXCH_ALIGNED4", _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED4);
    e.value("__MAX_MDS_EXCH_ALIGNED8", _eMdsExchangeId::__MAX_MDS_EXCH_ALIGNED8);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsExchangeId", e);
}
void generate_enum_eMdsMsgSource(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMsgSource> e(parent, "_eMdsMsgSource", pybind11::arithmetic());
    e.value("MDS_MSGSRC_UNDEFINED", _eMdsMsgSource::MDS_MSGSRC_UNDEFINED);
    e.value("MDS_MSGSRC_EZEI_TCP", _eMdsMsgSource::MDS_MSGSRC_EZEI_TCP);
    e.value("MDS_MSGSRC_EZEI_UDP", _eMdsMsgSource::MDS_MSGSRC_EZEI_UDP);
    e.value("MDS_MSGSRC_VDE_LEVEL2", _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL2);
    e.value("MDS_MSGSRC_VDE_LEVEL1", _eMdsMsgSource::MDS_MSGSRC_VDE_LEVEL1);
    e.value("MDS_MSGSRC_SZSE_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_BINARY);
    e.value("MDS_MSGSRC_SZSE_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_SZSE_MDGW_STEP);
    e.value("MDS_MSGSRC_MDS_TCP", _eMdsMsgSource::MDS_MSGSRC_MDS_TCP);
    e.value("MDS_MSGSRC_MDS_UDP", _eMdsMsgSource::MDS_MSGSRC_MDS_UDP);
    e.value("MDS_MSGSRC_FILE_MKTDT", _eMdsMsgSource::MDS_MSGSRC_FILE_MKTDT);
    e.value("MDS_MSGSRC_SSE_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_BINARY);
    e.value("MDS_MSGSRC_SSE_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_SSE_MDGW_STEP);
    e.value("__MAX_MDS_MSGSRC", _eMdsMsgSource::__MAX_MDS_MSGSRC);
    e.value("MDS_MSGSRC_MDGW_BINARY", _eMdsMsgSource::MDS_MSGSRC_MDGW_BINARY);
    e.value("MDS_MSGSRC_MDGW_STEP", _eMdsMsgSource::MDS_MSGSRC_MDGW_STEP);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMsgSource", e);
}
void generate_enum_eMdsMdProductType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMdProductType> e(parent, "_eMdsMdProductType", pybind11::arithmetic());
    e.value("MDS_MD_PRODUCT_TYPE_STOCK", _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_STOCK);
    e.value("MDS_MD_PRODUCT_TYPE_INDEX", _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_INDEX);
    e.value("MDS_MD_PRODUCT_TYPE_OPTION", _eMdsMdProductType::MDS_MD_PRODUCT_TYPE_OPTION);
    e.value("__MAX_MDS_MD_PRODUCT_TYPE", _eMdsMdProductType::__MAX_MDS_MD_PRODUCT_TYPE);
    e.value("MDS_SECURITY_TYPE_STOCK", _eMdsMdProductType::MDS_SECURITY_TYPE_STOCK);
    e.value("MDS_SECURITY_TYPE_INDEX", _eMdsMdProductType::MDS_SECURITY_TYPE_INDEX);
    e.value("MDS_SECURITY_TYPE_OPTION", _eMdsMdProductType::MDS_SECURITY_TYPE_OPTION);
    e.value("__MAX_MDS_SECURITY_TYPE", _eMdsMdProductType::__MAX_MDS_SECURITY_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdProductType", e);
}
void generate_enum_eMdsMdStreamType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMdStreamType> e(parent, "_eMdsMdStreamType", pybind11::arithmetic());
    e.value("MDS_MD_STREAM_TYPE_L1_SNAPSHOT", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L1_SNAPSHOT);
    e.value("MDS_MD_STREAM_TYPE_INDEX", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_INDEX);
    e.value("MDS_MD_STREAM_TYPE_OPTION", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OPTION);
    e.value("MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS);
    e.value("MDS_MD_STREAM_TYPE_SSE_L1_BOND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SSE_L1_BOND);
    e.value("MDS_MD_STREAM_TYPE_SSE_L1_FUND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_SSE_L1_FUND);
    e.value("MDS_MD_STREAM_TYPE_L2_SNAPSHOT", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_SNAPSHOT);
    e.value("MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_SNAPSHOT", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_SNAPSHOT);
    e.value("MDS_MD_STREAM_TYPE_L2_SNAPSHOT_INCREMENTAL", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_SNAPSHOT_INCREMENTAL);
    e.value("MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_INCREMENTAL", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_INCREMENTAL);
    e.value("MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW);
    e.value("__MAX_MDS_MD_STREAM_TYPE", _eMdsMdStreamType::__MAX_MDS_MD_STREAM_TYPE);
    e.value("MDS_MD_STREAM_TYPE_BOND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_BOND);
    e.value("MDS_MD_STREAM_TYPE_FUND", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_FUND);
    e.value("MDS_MD_STREAM_TYPE_OTHERS", _eMdsMdStreamType::MDS_MD_STREAM_TYPE_OTHERS);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdStreamType", e);
}
void generate_enum_eMdsMdLevel(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMdLevel> e(parent, "_eMdsMdLevel", pybind11::arithmetic());
    e.value("MDS_MD_LEVEL_0", _eMdsMdLevel::MDS_MD_LEVEL_0);
    e.value("MDS_MD_LEVEL_1", _eMdsMdLevel::MDS_MD_LEVEL_1);
    e.value("MDS_MD_LEVEL_2", _eMdsMdLevel::MDS_MD_LEVEL_2);
    e.value("__MAX_MDS_MD_LEVEL", _eMdsMdLevel::__MAX_MDS_MD_LEVEL);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMdLevel", e);
}
void generate_enum_eMdsL2PriceLevelOperator(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2PriceLevelOperator> e(parent, "_eMdsL2PriceLevelOperator", pybind11::arithmetic());
    e.value("MDS_L2_PX_OPERATOR_ADD", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_ADD);
    e.value("MDS_L2_PX_OPERATOR_UPDATE", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_UPDATE);
    e.value("MDS_L2_PX_OPERATOR_DELETE", _eMdsL2PriceLevelOperator::MDS_L2_PX_OPERATOR_DELETE);
    e.value("__MAX_MDS_L2_PX_OPERATOR", _eMdsL2PriceLevelOperator::__MAX_MDS_L2_PX_OPERATOR);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2PriceLevelOperator", e);
}
void generate_enum_eMdsL2TradeExecType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2TradeExecType> e(parent, "_eMdsL2TradeExecType", pybind11::arithmetic());
    e.value("MDS_L2_TRADE_EXECTYPE_CANCELED", _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_CANCELED);
    e.value("MDS_L2_TRADE_EXECTYPE_TRADE", _eMdsL2TradeExecType::MDS_L2_TRADE_EXECTYPE_TRADE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2TradeExecType", e);
}
void generate_enum_eMdsL2TradeBSFlag(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2TradeBSFlag> e(parent, "_eMdsL2TradeBSFlag", pybind11::arithmetic());
    e.value("MDS_L2_TRADE_BSFLAG_BUY", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_BUY);
    e.value("MDS_L2_TRADE_BSFLAG_SELL", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_SELL);
    e.value("MDS_L2_TRADE_BSFLAG_UNKNOWN", _eMdsL2TradeBSFlag::MDS_L2_TRADE_BSFLAG_UNKNOWN);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2TradeBSFlag", e);
}
void generate_enum_eMdsL2OrderSideT(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2OrderSideT> e(parent, "_eMdsL2OrderSideT", pybind11::arithmetic());
    e.value("MDS_L2_ORDER_SIDE_BUY", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BUY);
    e.value("MDS_L2_ORDER_SIDE_SELL", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_SELL);
    e.value("MDS_L2_ORDER_SIDE_BORROW", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_BORROW);
    e.value("MDS_L2_ORDER_SIDE_LEND", _eMdsL2OrderSideT::MDS_L2_ORDER_SIDE_LEND);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2OrderSideT", e);
}
void generate_enum_eMdsL2OrderType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsL2OrderType> e(parent, "_eMdsL2OrderType", pybind11::arithmetic());
    e.value("MDS_L2_ORDER_TYPE_MKT", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_MKT);
    e.value("MDS_L2_ORDER_TYPE_LMT", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_LMT);
    e.value("MDS_L2_ORDER_TYPE_SAMEPARTY_BEST", _eMdsL2OrderType::MDS_L2_ORDER_TYPE_SAMEPARTY_BEST);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsL2OrderType", e);
}
void generate_enum_eMdsClientType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsClientType> e(parent, "_eMdsClientType", pybind11::arithmetic());
    e.value("MDS_CLIENT_TYPE_UNDEFINED", _eMdsClientType::MDS_CLIENT_TYPE_UNDEFINED);
    e.value("MDS_CLIENT_TYPE_INVESTOR", _eMdsClientType::MDS_CLIENT_TYPE_INVESTOR);
    e.value("MDS_CLIENT_TYPE_VIRTUAL", _eMdsClientType::MDS_CLIENT_TYPE_VIRTUAL);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsClientType", e);
}
void generate_enum_eMdsClientStatus(pybind11::object & parent)
{
    pybind11::enum_<_eMdsClientStatus> e(parent, "_eMdsClientStatus", pybind11::arithmetic());
    e.value("MDS_CLIENT_STATUS_UNACTIVATED", _eMdsClientStatus::MDS_CLIENT_STATUS_UNACTIVATED);
    e.value("MDS_CLIENT_STATUS_ACTIVATED", _eMdsClientStatus::MDS_CLIENT_STATUS_ACTIVATED);
    e.value("MDS_CLIENT_STATUS_PAUSE", _eMdsClientStatus::MDS_CLIENT_STATUS_PAUSE);
    e.value("MDS_CLIENT_STATUS_SUSPENDED", _eMdsClientStatus::MDS_CLIENT_STATUS_SUSPENDED);
    e.value("MDS_CLIENT_STATUS_CANCELLED", _eMdsClientStatus::MDS_CLIENT_STATUS_CANCELLED);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsClientStatus", e);
}
void generate_enum_eMdsMsgType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMsgType> e(parent, "_eMdsMsgType", pybind11::arithmetic());
    e.value("MDS_MSGTYPE_HEARTBEAT", _eMdsMsgType::MDS_MSGTYPE_HEARTBEAT);
    e.value("MDS_MSGTYPE_TEST_REQUEST", _eMdsMsgType::MDS_MSGTYPE_TEST_REQUEST);
    e.value("MDS_MSGTYPE_LOGOUT", _eMdsMsgType::MDS_MSGTYPE_LOGOUT);
    e.value("MDS_MSGTYPE_MARKET_DATA_REQUEST", _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_REQUEST);
    e.value("MDS_MSGTYPE_COMPRESSED_PACKETS", _eMdsMsgType::MDS_MSGTYPE_COMPRESSED_PACKETS);
    e.value("__MDS_MSGTYPE_SESSION_MAX", _eMdsMsgType::__MDS_MSGTYPE_SESSION_MAX);
    e.value("MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH);
    e.value("MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH);
    e.value("MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH", _eMdsMsgType::MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH);
    e.value("MDS_MSGTYPE_TRADING_SESSION_STATUS", _eMdsMsgType::MDS_MSGTYPE_TRADING_SESSION_STATUS);
    e.value("MDS_MSGTYPE_SECURITY_STATUS", _eMdsMsgType::MDS_MSGTYPE_SECURITY_STATUS);
    e.value("__MDS_MSGTYPE_L1_MAX", _eMdsMsgType::__MDS_MSGTYPE_L1_MAX);
    e.value("MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT);
    e.value("MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT);
    e.value("MDS_MSGTYPE_L2_TRADE", _eMdsMsgType::MDS_MSGTYPE_L2_TRADE);
    e.value("MDS_MSGTYPE_L2_ORDER", _eMdsMsgType::MDS_MSGTYPE_L2_ORDER);
    e.value("MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL);
    e.value("MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL", _eMdsMsgType::MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL);
    e.value("MDS_MSGTYPE_L2_MARKET_OVERVIEW", _eMdsMsgType::MDS_MSGTYPE_L2_MARKET_OVERVIEW);
    e.value("MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE", _eMdsMsgType::MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE);
    e.value("__MDS_MSGTYPE_L2_MAX", _eMdsMsgType::__MDS_MSGTYPE_L2_MAX);
    e.value("MDS_MSGTYPE_CMD_CHANGE_PASSWORD", _eMdsMsgType::MDS_MSGTYPE_CMD_CHANGE_PASSWORD);
    e.value("__MDS_MSGTYPE_CMD_MAX", _eMdsMsgType::__MDS_MSGTYPE_CMD_MAX);
    e.value("MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT", _eMdsMsgType::MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT);
    e.value("MDS_MSGTYPE_QRY_SECURITY_STATUS", _eMdsMsgType::MDS_MSGTYPE_QRY_SECURITY_STATUS);
    e.value("MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS", _eMdsMsgType::MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS);
    e.value("MDS_MSGTYPE_QRY_STOCK_STATIC_INFO", _eMdsMsgType::MDS_MSGTYPE_QRY_STOCK_STATIC_INFO);
    e.value("MDS_MSGTYPE_QRY_SNAPSHOT_LIST", _eMdsMsgType::MDS_MSGTYPE_QRY_SNAPSHOT_LIST);
    e.value("__MDS_MSGTYPE_QRY_MAX", _eMdsMsgType::__MDS_MSGTYPE_QRY_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMsgType", e);
}
void generate_enum_eMdsSubscribeMode(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribeMode> e(parent, "_eMdsSubscribeMode", pybind11::arithmetic());
    e.value("MDS_SUB_MODE_SET", _eMdsSubscribeMode::MDS_SUB_MODE_SET);
    e.value("MDS_SUB_MODE_APPEND", _eMdsSubscribeMode::MDS_SUB_MODE_APPEND);
    e.value("MDS_SUB_MODE_DELETE", _eMdsSubscribeMode::MDS_SUB_MODE_DELETE);
    e.value("__MAX_MDS_SUB_MODE", _eMdsSubscribeMode::__MAX_MDS_SUB_MODE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribeMode", e);
}
void generate_enum_eMdsMktSubscribeFlag(pybind11::object & parent)
{
    pybind11::enum_<_eMdsMktSubscribeFlag> e(parent, "_eMdsMktSubscribeFlag", pybind11::arithmetic());
    e.value("MDS_MKT_SUB_FLAG_DEFAULT", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DEFAULT);
    e.value("MDS_MKT_SUB_FLAG_ALL", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_ALL);
    e.value("MDS_MKT_SUB_FLAG_DISABLE", _eMdsMktSubscribeFlag::MDS_MKT_SUB_FLAG_DISABLE);
    e.value("__MAX_MDS_MKT_SUB_FLAG", _eMdsMktSubscribeFlag::__MAX_MDS_MKT_SUB_FLAG);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsMktSubscribeFlag", e);
}
void generate_enum_eMdsSubscribedTickType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribedTickType> e(parent, "_eMdsSubscribedTickType", pybind11::arithmetic());
    e.value("MDS_TICK_TYPE_LATEST_SIMPLIFIED", _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_SIMPLIFIED);
    e.value("MDS_TICK_TYPE_LATEST_TIMELY", _eMdsSubscribedTickType::MDS_TICK_TYPE_LATEST_TIMELY);
    e.value("MDS_TICK_TYPE_ALL_INCREMENTS", _eMdsSubscribedTickType::MDS_TICK_TYPE_ALL_INCREMENTS);
    e.value("__MAX_MDS_TICK_TYPE", _eMdsSubscribedTickType::__MAX_MDS_TICK_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedTickType", e);
}
void generate_enum_eMdsSubscribedTickExpireType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribedTickExpireType> e(parent, "_eMdsSubscribedTickExpireType", pybind11::arithmetic());
    e.value("MDS_TICK_EXPIRE_TYPE_NONE", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_NONE);
    e.value("MDS_TICK_EXPIRE_TYPE_IMMEDIATE", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_IMMEDIATE);
    e.value("MDS_TICK_EXPIRE_TYPE_TIMELY", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMELY);
    e.value("MDS_TICK_EXPIRE_TYPE_TIMEOUT", _eMdsSubscribedTickExpireType::MDS_TICK_EXPIRE_TYPE_TIMEOUT);
    e.value("__MAX_MDS_TICK_EXPIRE_TYPE", _eMdsSubscribedTickExpireType::__MAX_MDS_TICK_EXPIRE_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedTickExpireType", e);
}
void generate_enum_eMdsSubscribeDataType(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribeDataType> e(parent, "_eMdsSubscribeDataType", pybind11::arithmetic());
    e.value("MDS_SUB_DATA_TYPE_DEFAULT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_DEFAULT);
    e.value("MDS_SUB_DATA_TYPE_L1_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L1_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_L2_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_L2_BEST_ORDERS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_BEST_ORDERS);
    e.value("MDS_SUB_DATA_TYPE_L2_TRADE", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_TRADE);
    e.value("MDS_SUB_DATA_TYPE_L2_ORDER", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_ORDER);
    e.value("MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW);
    e.value("MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS);
    e.value("MDS_SUB_DATA_TYPE_SECURITY_STATUS", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_SECURITY_STATUS);
    e.value("MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT);
    e.value("MDS_SUB_DATA_TYPE_NONE", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_NONE);
    e.value("MDS_SUB_DATA_TYPE_ALL", _eMdsSubscribeDataType::MDS_SUB_DATA_TYPE_ALL);
    e.value("__MAX_MDS_SUB_DATA_TYPE", _eMdsSubscribeDataType::__MAX_MDS_SUB_DATA_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribeDataType", e);
}
void generate_enum_eMdsSubscribedChannelNo(pybind11::object & parent)
{
    pybind11::enum_<_eMdsSubscribedChannelNo> e(parent, "_eMdsSubscribedChannelNo", pybind11::arithmetic());
    e.value("MDS_CHANNEL_NO_DEFAULT", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_DEFAULT);
    e.value("MDS_CHANNEL_NO_ONE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ONE);
    e.value("MDS_CHANNEL_NO_TWO", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_TWO);
    e.value("MDS_CHANNEL_NO_THREE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_THREE);
    e.value("MDS_CHANNEL_NO_FOUR", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_FOUR);
    e.value("MDS_CHANNEL_NO_ALL", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_ALL);
    e.value("MDS_CHANNEL_NO_NONE", _eMdsSubscribedChannelNo::MDS_CHANNEL_NO_NONE);
    e.export_values();
    module_vnoes::objects.emplace("_eMdsSubscribedChannelNo", e);
}
