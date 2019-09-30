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


void generate_enum_eOesTradingPermission(pybind11::object & parent)
{
    // _eOesTradingPermission
    pybind11::enum_<_eOesTradingPermission> e(parent, "_eOesTradingPermission", pybind11::arithmetic());
    // _eOesTradingPermission::OES_PERMIS_MARKET_ORDER
    e.value("OES_PERMIS_MARKET_ORDER", _eOesTradingPermission::OES_PERMIS_MARKET_ORDER);
    // _eOesTradingPermission::OES_PERMIS_STRUCTURED_FUND
    e.value("OES_PERMIS_STRUCTURED_FUND", _eOesTradingPermission::OES_PERMIS_STRUCTURED_FUND);
    // _eOesTradingPermission::OES_PERMIS_BOND_QUALIFIED_INVESTOR
    e.value("OES_PERMIS_BOND_QUALIFIED_INVESTOR", _eOesTradingPermission::OES_PERMIS_BOND_QUALIFIED_INVESTOR);
    // _eOesTradingPermission::OES_PERMIS_XXX4
    e.value("OES_PERMIS_XXX4", _eOesTradingPermission::OES_PERMIS_XXX4);
    // _eOesTradingPermission::OES_PERMIS_DELISTING
    e.value("OES_PERMIS_DELISTING", _eOesTradingPermission::OES_PERMIS_DELISTING);
    // _eOesTradingPermission::OES_PERMIS_RISK_WARNING
    e.value("OES_PERMIS_RISK_WARNING", _eOesTradingPermission::OES_PERMIS_RISK_WARNING);
    // _eOesTradingPermission::OES_PERMIS_SINGLE_MARKET_ETF
    e.value("OES_PERMIS_SINGLE_MARKET_ETF", _eOesTradingPermission::OES_PERMIS_SINGLE_MARKET_ETF);
    // _eOesTradingPermission::OES_PERMIS_CROSS_BORDER_ETF
    e.value("OES_PERMIS_CROSS_BORDER_ETF", _eOesTradingPermission::OES_PERMIS_CROSS_BORDER_ETF);
    // _eOesTradingPermission::OES_PERMIS_CROSS_MARKET_ETF
    e.value("OES_PERMIS_CROSS_MARKET_ETF", _eOesTradingPermission::OES_PERMIS_CROSS_MARKET_ETF);
    // _eOesTradingPermission::OES_PERMIS_CURRENCY_ETF
    e.value("OES_PERMIS_CURRENCY_ETF", _eOesTradingPermission::OES_PERMIS_CURRENCY_ETF);
    // _eOesTradingPermission::OES_PERMIS_STOCK_PLEDGE_REPURCHASE
    e.value("OES_PERMIS_STOCK_PLEDGE_REPURCHASE", _eOesTradingPermission::OES_PERMIS_STOCK_PLEDGE_REPURCHASE);
    // _eOesTradingPermission::OES_PERMIS_PLEDGE_REPURCHASE
    e.value("OES_PERMIS_PLEDGE_REPURCHASE", _eOesTradingPermission::OES_PERMIS_PLEDGE_REPURCHASE);
    // _eOesTradingPermission::OES_PERMIS_GEM
    e.value("OES_PERMIS_GEM", _eOesTradingPermission::OES_PERMIS_GEM);
    // _eOesTradingPermission::OES_PERMIS_SH_HK_STOCK_CONNECT
    e.value("OES_PERMIS_SH_HK_STOCK_CONNECT", _eOesTradingPermission::OES_PERMIS_SH_HK_STOCK_CONNECT);
    // _eOesTradingPermission::OES_PERMIS_SZ_HK_STOCK_CONNECT
    e.value("OES_PERMIS_SZ_HK_STOCK_CONNECT", _eOesTradingPermission::OES_PERMIS_SZ_HK_STOCK_CONNECT);
    // _eOesTradingPermission::OES_PERMIS_HLTCDR
    e.value("OES_PERMIS_HLTCDR", _eOesTradingPermission::OES_PERMIS_HLTCDR);
    // _eOesTradingPermission::OES_PERMIS_CDR
    e.value("OES_PERMIS_CDR", _eOesTradingPermission::OES_PERMIS_CDR);
    // _eOesTradingPermission::OES_PERMIS_INNOVATION
    e.value("OES_PERMIS_INNOVATION", _eOesTradingPermission::OES_PERMIS_INNOVATION);
    // _eOesTradingPermission::OES_PERMIS_KSH
    e.value("OES_PERMIS_KSH", _eOesTradingPermission::OES_PERMIS_KSH);
    // _eOesTradingPermission::__OES_PERMIS_ALL
    e.value("__OES_PERMIS_ALL", _eOesTradingPermission::__OES_PERMIS_ALL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesTradingPermission", e);
}
void generate_enum_eOesTradingLimit(pybind11::object & parent)
{
    // _eOesTradingLimit
    pybind11::enum_<_eOesTradingLimit> e(parent, "_eOesTradingLimit", pybind11::arithmetic());
    // _eOesTradingLimit::OES_LIMIT_BUY
    e.value("OES_LIMIT_BUY", _eOesTradingLimit::OES_LIMIT_BUY);
    // _eOesTradingLimit::OES_LIMIT_SELL
    e.value("OES_LIMIT_SELL", _eOesTradingLimit::OES_LIMIT_SELL);
    // _eOesTradingLimit::OES_LIMIT_RECALL_DESIGNATION
    e.value("OES_LIMIT_RECALL_DESIGNATION", _eOesTradingLimit::OES_LIMIT_RECALL_DESIGNATION);
    // _eOesTradingLimit::OES_LIMIT_DESIGNATION
    e.value("OES_LIMIT_DESIGNATION", _eOesTradingLimit::OES_LIMIT_DESIGNATION);
    // _eOesTradingLimit::OES_LIMIT_REPO
    e.value("OES_LIMIT_REPO", _eOesTradingLimit::OES_LIMIT_REPO);
    // _eOesTradingLimit::OES_LIMIT_REVERSE_REPO
    e.value("OES_LIMIT_REVERSE_REPO", _eOesTradingLimit::OES_LIMIT_REVERSE_REPO);
    // _eOesTradingLimit::OES_LIMIT_SUBSCRIPTION
    e.value("OES_LIMIT_SUBSCRIPTION", _eOesTradingLimit::OES_LIMIT_SUBSCRIPTION);
    // _eOesTradingLimit::OES_LIMIT_CREDIT_BUY
    e.value("OES_LIMIT_CREDIT_BUY", _eOesTradingLimit::OES_LIMIT_CREDIT_BUY);
    // _eOesTradingLimit::OES_LIMIT_CREDIT_SELL
    e.value("OES_LIMIT_CREDIT_SELL", _eOesTradingLimit::OES_LIMIT_CREDIT_SELL);
    // _eOesTradingLimit::__OES_LIMIT_ALL
    e.value("__OES_LIMIT_ALL", _eOesTradingLimit::__OES_LIMIT_ALL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesTradingLimit", e);
}
void generate_enum_eOesQualificationClass(pybind11::object & parent)
{
    // _eOesQualificationClass
    pybind11::enum_<_eOesQualificationClass> e(parent, "_eOesQualificationClass", pybind11::arithmetic());
    // _eOesQualificationClass::OES_QUALIFICATION_PUBLIC_INVESTOR
    e.value("OES_QUALIFICATION_PUBLIC_INVESTOR", _eOesQualificationClass::OES_QUALIFICATION_PUBLIC_INVESTOR);
    // _eOesQualificationClass::OES_QUALIFICATION_QUALIFIED_INVESTOR
    e.value("OES_QUALIFICATION_QUALIFIED_INVESTOR", _eOesQualificationClass::OES_QUALIFICATION_QUALIFIED_INVESTOR);
    // _eOesQualificationClass::OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL
    e.value("OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL", _eOesQualificationClass::OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesQualificationClass", e);
}
void generate_enum_eOesInvestorClass(pybind11::object & parent)
{
    // _eOesInvestorClass
    pybind11::enum_<_eOesInvestorClass> e(parent, "_eOesInvestorClass", pybind11::arithmetic());
    // _eOesInvestorClass::OES_INVESTOR_CLASS_NORMAL
    e.value("OES_INVESTOR_CLASS_NORMAL", _eOesInvestorClass::OES_INVESTOR_CLASS_NORMAL);
    // _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_A
    e.value("OES_INVESTOR_CLASS_PROFESSIONAL_A", _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_A);
    // _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_B
    e.value("OES_INVESTOR_CLASS_PROFESSIONAL_B", _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_B);
    // _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_C
    e.value("OES_INVESTOR_CLASS_PROFESSIONAL_C", _eOesInvestorClass::OES_INVESTOR_CLASS_PROFESSIONAL_C);
    e.export_values();
    module_vnoes::objects.emplace("_eOesInvestorClass", e);
}
void generate_enum_eOesCustType(pybind11::object & parent)
{
    // _eOesCustType
    pybind11::enum_<_eOesCustType> e(parent, "_eOesCustType", pybind11::arithmetic());
    // _eOesCustType::OES_CUST_TYPE_PERSONAL
    e.value("OES_CUST_TYPE_PERSONAL", _eOesCustType::OES_CUST_TYPE_PERSONAL);
    // _eOesCustType::OES_CUST_TYPE_INSTITUTION
    e.value("OES_CUST_TYPE_INSTITUTION", _eOesCustType::OES_CUST_TYPE_INSTITUTION);
    // _eOesCustType::OES_CUST_TYPE_PROPRIETARY
    e.value("OES_CUST_TYPE_PROPRIETARY", _eOesCustType::OES_CUST_TYPE_PROPRIETARY);
    // _eOesCustType::OES_CUST_TYPE_PRODUCT
    e.value("OES_CUST_TYPE_PRODUCT", _eOesCustType::OES_CUST_TYPE_PRODUCT);
    // _eOesCustType::OES_CUST_TYPE_MKT_MAKER
    e.value("OES_CUST_TYPE_MKT_MAKER", _eOesCustType::OES_CUST_TYPE_MKT_MAKER);
    // _eOesCustType::OES_CUST_TYPE_OTHERS
    e.value("OES_CUST_TYPE_OTHERS", _eOesCustType::OES_CUST_TYPE_OTHERS);
    // _eOesCustType::__OES_CUST_TYPE_MAX
    e.value("__OES_CUST_TYPE_MAX", _eOesCustType::__OES_CUST_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesCustType", e);
}
void generate_enum_eOesOwnerType(pybind11::object & parent)
{
    // _eOesOwnerType
    pybind11::enum_<_eOesOwnerType> e(parent, "_eOesOwnerType", pybind11::arithmetic());
    // _eOesOwnerType::OES_OWNER_TYPE_PERSONAL
    e.value("OES_OWNER_TYPE_PERSONAL", _eOesOwnerType::OES_OWNER_TYPE_PERSONAL);
    // _eOesOwnerType::OES_OWNER_TYPE_EXCHANGE
    e.value("OES_OWNER_TYPE_EXCHANGE", _eOesOwnerType::OES_OWNER_TYPE_EXCHANGE);
    // _eOesOwnerType::OES_OWNER_TYPE_MEMBER
    e.value("OES_OWNER_TYPE_MEMBER", _eOesOwnerType::OES_OWNER_TYPE_MEMBER);
    // _eOesOwnerType::OES_OWNER_TYPE_INSTITUTION
    e.value("OES_OWNER_TYPE_INSTITUTION", _eOesOwnerType::OES_OWNER_TYPE_INSTITUTION);
    // _eOesOwnerType::OES_OWNER_TYPE_PROPRIETARY
    e.value("OES_OWNER_TYPE_PROPRIETARY", _eOesOwnerType::OES_OWNER_TYPE_PROPRIETARY);
    // _eOesOwnerType::OES_OWNER_TYPE_MKT_MAKER
    e.value("OES_OWNER_TYPE_MKT_MAKER", _eOesOwnerType::OES_OWNER_TYPE_MKT_MAKER);
    // _eOesOwnerType::OES_OWNER_TYPE_SETTLEMENT
    e.value("OES_OWNER_TYPE_SETTLEMENT", _eOesOwnerType::OES_OWNER_TYPE_SETTLEMENT);
    // _eOesOwnerType::__OES_OWNER_TYPE_MAX
    e.value("__OES_OWNER_TYPE_MAX", _eOesOwnerType::__OES_OWNER_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOwnerType", e);
}
void generate_enum_eOesClientType(pybind11::object & parent)
{
    // _eOesClientType
    pybind11::enum_<_eOesClientType> e(parent, "_eOesClientType", pybind11::arithmetic());
    // _eOesClientType::OES_CLIENT_TYPE_UNDEFINED
    e.value("OES_CLIENT_TYPE_UNDEFINED", _eOesClientType::OES_CLIENT_TYPE_UNDEFINED);
    // _eOesClientType::OES_CLIENT_TYPE_INVESTOR
    e.value("OES_CLIENT_TYPE_INVESTOR", _eOesClientType::OES_CLIENT_TYPE_INVESTOR);
    // _eOesClientType::OES_CLIENT_TYPE_VIRTUAL
    e.value("OES_CLIENT_TYPE_VIRTUAL", _eOesClientType::OES_CLIENT_TYPE_VIRTUAL);
    e.export_values();
    module_vnoes::objects.emplace("_eOesClientType", e);
}
void generate_enum_eOesClientStatus(pybind11::object & parent)
{
    // _eOesClientStatus
    pybind11::enum_<_eOesClientStatus> e(parent, "_eOesClientStatus", pybind11::arithmetic());
    // _eOesClientStatus::OES_CLIENT_STATUS_UNACTIVATED
    e.value("OES_CLIENT_STATUS_UNACTIVATED", _eOesClientStatus::OES_CLIENT_STATUS_UNACTIVATED);
    // _eOesClientStatus::OES_CLIENT_STATUS_ACTIVATED
    e.value("OES_CLIENT_STATUS_ACTIVATED", _eOesClientStatus::OES_CLIENT_STATUS_ACTIVATED);
    // _eOesClientStatus::OES_CLIENT_STATUS_PAUSE
    e.value("OES_CLIENT_STATUS_PAUSE", _eOesClientStatus::OES_CLIENT_STATUS_PAUSE);
    // _eOesClientStatus::OES_CLIENT_STATUS_SUSPENDED
    e.value("OES_CLIENT_STATUS_SUSPENDED", _eOesClientStatus::OES_CLIENT_STATUS_SUSPENDED);
    // _eOesClientStatus::OES_CLIENT_STATUS_CANCELLED
    e.value("OES_CLIENT_STATUS_CANCELLED", _eOesClientStatus::OES_CLIENT_STATUS_CANCELLED);
    e.export_values();
    module_vnoes::objects.emplace("_eOesClientStatus", e);
}
void generate_enum_eOesOptContractType(pybind11::object & parent)
{
    // _eOesOptContractType
    pybind11::enum_<_eOesOptContractType> e(parent, "_eOesOptContractType", pybind11::arithmetic());
    // _eOesOptContractType::OES_OPT_CONTRACT_TYPE_CALL
    e.value("OES_OPT_CONTRACT_TYPE_CALL", _eOesOptContractType::OES_OPT_CONTRACT_TYPE_CALL);
    // _eOesOptContractType::OES_OPT_CONTRACT_TYPE_PUT
    e.value("OES_OPT_CONTRACT_TYPE_PUT", _eOesOptContractType::OES_OPT_CONTRACT_TYPE_PUT);
    // _eOesOptContractType::__OES_OPT_CONTRACT_TYPE_MAX
    e.value("__OES_OPT_CONTRACT_TYPE_MAX", _eOesOptContractType::__OES_OPT_CONTRACT_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptContractType", e);
}
void generate_enum_eOesOptInvLevel(pybind11::object & parent)
{
    // _eOesOptInvLevel
    pybind11::enum_<_eOesOptInvLevel> e(parent, "_eOesOptInvLevel", pybind11::arithmetic());
    // _eOesOptInvLevel::OES_OPT_INV_LEVEL_B
    e.value("OES_OPT_INV_LEVEL_B", _eOesOptInvLevel::OES_OPT_INV_LEVEL_B);
    // _eOesOptInvLevel::OES_OPT_INV_LEVEL_L
    e.value("OES_OPT_INV_LEVEL_L", _eOesOptInvLevel::OES_OPT_INV_LEVEL_L);
    // _eOesOptInvLevel::OES_OPT_INV_LEVEL_A
    e.value("OES_OPT_INV_LEVEL_A", _eOesOptInvLevel::OES_OPT_INV_LEVEL_A);
    // _eOesOptInvLevel::__OES_OPT_INV_LEVEL_MAX
    e.value("__OES_OPT_INV_LEVEL_MAX", _eOesOptInvLevel::__OES_OPT_INV_LEVEL_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptInvLevel", e);
}
void generate_enum_eOpenFlagType(pybind11::object & parent)
{
    // _eOpenFlagType
    pybind11::enum_<_eOpenFlagType> e(parent, "_eOpenFlagType", pybind11::arithmetic());
    // _eOpenFlagType::OPEN_FLAG_TYPE_ALLOW
    e.value("OPEN_FLAG_TYPE_ALLOW", _eOpenFlagType::OPEN_FLAG_TYPE_ALLOW);
    // _eOpenFlagType::OPEN_FLAG_TYPE_FORBID
    e.value("OPEN_FLAG_TYPE_FORBID", _eOpenFlagType::OPEN_FLAG_TYPE_FORBID);
    // _eOpenFlagType::__OPEN_FLAG_TYPE_MAX
    e.value("__OPEN_FLAG_TYPE_MAX", _eOpenFlagType::__OPEN_FLAG_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOpenFlagType", e);
}
void generate_enum_eOesOptionOpenFlag(pybind11::object & parent)
{
    // _eOesOptionOpenFlag
    pybind11::enum_<_eOesOptionOpenFlag> e(parent, "_eOesOptionOpenFlag", pybind11::arithmetic());
    // _eOesOptionOpenFlag::OES_OPTION_OPEN_FLAG_ALLOW
    e.value("OES_OPTION_OPEN_FLAG_ALLOW", _eOesOptionOpenFlag::OES_OPTION_OPEN_FLAG_ALLOW);
    // _eOesOptionOpenFlag::OES_OPTION_OPEN_FLAG_FORBID
    e.value("OES_OPTION_OPEN_FLAG_FORBID", _eOesOptionOpenFlag::OES_OPTION_OPEN_FLAG_FORBID);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptionOpenFlag", e);
}
void generate_enum_eOesPositionEff(pybind11::object & parent)
{
    // _eOesPositionEff
    pybind11::enum_<_eOesPositionEff> e(parent, "_eOesPositionEff", pybind11::arithmetic());
    // _eOesPositionEff::OES_POSITION_INVALID
    e.value("OES_POSITION_INVALID", _eOesPositionEff::OES_POSITION_INVALID);
    // _eOesPositionEff::OES_POSITION_OPEN
    e.value("OES_POSITION_OPEN", _eOesPositionEff::OES_POSITION_OPEN);
    // _eOesPositionEff::OES_POSITION_CLOSE
    e.value("OES_POSITION_CLOSE", _eOesPositionEff::OES_POSITION_CLOSE);
    e.export_values();
    module_vnoes::objects.emplace("_eOesPositionEff", e);
}
void generate_enum_eOesOptionType(pybind11::object & parent)
{
    // _eOesOptionType
    pybind11::enum_<_eOesOptionType> e(parent, "_eOesOptionType", pybind11::arithmetic());
    // _eOesOptionType::OES_OPTION_TYPE_E
    e.value("OES_OPTION_TYPE_E", _eOesOptionType::OES_OPTION_TYPE_E);
    // _eOesOptionType::OES_OPTION_TYPE_A
    e.value("OES_OPTION_TYPE_A", _eOesOptionType::OES_OPTION_TYPE_A);
    // _eOesOptionType::__OES_OPTION_TYPE_MAX
    e.value("__OES_OPTION_TYPE_MAX", _eOesOptionType::__OES_OPTION_TYPE_MAX);
    e.export_values();
    module_vnoes::objects.emplace("_eOesOptionType", e);
}
void generate_enum_eSMsgProtocolType(pybind11::object & parent)
{
    // _eSMsgProtocolType
    pybind11::enum_<_eSMsgProtocolType> e(parent, "_eSMsgProtocolType", pybind11::arithmetic());
    // _eSMsgProtocolType::SMSG_PROTO_BINARY
    e.value("SMSG_PROTO_BINARY", _eSMsgProtocolType::SMSG_PROTO_BINARY);
    // _eSMsgProtocolType::SMSG_PROTO_JSON
    e.value("SMSG_PROTO_JSON", _eSMsgProtocolType::SMSG_PROTO_JSON);
    // _eSMsgProtocolType::SMSG_PROTO_FIX
    e.value("SMSG_PROTO_FIX", _eSMsgProtocolType::SMSG_PROTO_FIX);
    // _eSMsgProtocolType::SMSG_PROTO_PROTOBUF
    e.value("SMSG_PROTO_PROTOBUF", _eSMsgProtocolType::SMSG_PROTO_PROTOBUF);
    // _eSMsgProtocolType::__MAX_SMSG_PROTO_TYPE
    e.value("__MAX_SMSG_PROTO_TYPE", _eSMsgProtocolType::__MAX_SMSG_PROTO_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eSMsgProtocolType", e);
}
void generate_enum_eSMsgFlag(pybind11::object & parent)
{
    // _eSMsgFlag
    pybind11::enum_<_eSMsgFlag> e(parent, "_eSMsgFlag", pybind11::arithmetic());
    // _eSMsgFlag::SMSG_MSGFLAG_NONE
    e.value("SMSG_MSGFLAG_NONE", _eSMsgFlag::SMSG_MSGFLAG_NONE);
    // _eSMsgFlag::SMSG_MSGFLAG_REQ
    e.value("SMSG_MSGFLAG_REQ", _eSMsgFlag::SMSG_MSGFLAG_REQ);
    // _eSMsgFlag::SMSG_MSGFLAG_RSP
    e.value("SMSG_MSGFLAG_RSP", _eSMsgFlag::SMSG_MSGFLAG_RSP);
    // _eSMsgFlag::SMSG_MSGFLAG_NESTED
    e.value("SMSG_MSGFLAG_NESTED", _eSMsgFlag::SMSG_MSGFLAG_NESTED);
    // _eSMsgFlag::SMSG_MSGFLAG_COMPRESSED
    e.value("SMSG_MSGFLAG_COMPRESSED", _eSMsgFlag::SMSG_MSGFLAG_COMPRESSED);
    // _eSMsgFlag::SMSG_MSGFLAG_MASK_RSPFLAG
    e.value("SMSG_MSGFLAG_MASK_RSPFLAG", _eSMsgFlag::SMSG_MSGFLAG_MASK_RSPFLAG);
    // _eSMsgFlag::SMSG_MSGFLAG_MASK_PROTOCOL
    e.value("SMSG_MSGFLAG_MASK_PROTOCOL", _eSMsgFlag::SMSG_MSGFLAG_MASK_PROTOCOL);
    e.export_values();
    module_vnoes::objects.emplace("_eSMsgFlag", e);
}
void generate_enum_eOesMsgType(pybind11::object & parent)
{
    // _eOesMsgType
    pybind11::enum_<_eOesMsgType> e(parent, "_eOesMsgType", pybind11::arithmetic());
    // _eOesMsgType::OESMSG_ORD_NEW_ORDER
    e.value("OESMSG_ORD_NEW_ORDER", _eOesMsgType::OESMSG_ORD_NEW_ORDER);
    // _eOesMsgType::OESMSG_ORD_CANCEL_REQUEST
    e.value("OESMSG_ORD_CANCEL_REQUEST", _eOesMsgType::OESMSG_ORD_CANCEL_REQUEST);
    // _eOesMsgType::OESMSG_ORD_BATCH_ORDERS
    e.value("OESMSG_ORD_BATCH_ORDERS", _eOesMsgType::OESMSG_ORD_BATCH_ORDERS);
    // _eOesMsgType::__OESMSG_ORD_MAX
    e.value("__OESMSG_ORD_MAX", _eOesMsgType::__OESMSG_ORD_MAX);
    // _eOesMsgType::__OESMSG_RPT_MIN
    e.value("__OESMSG_RPT_MIN", _eOesMsgType::__OESMSG_RPT_MIN);
    // _eOesMsgType::OESMSG_RPT_MARKET_STATE
    e.value("OESMSG_RPT_MARKET_STATE", _eOesMsgType::OESMSG_RPT_MARKET_STATE);
    // _eOesMsgType::OESMSG_RPT_REPORT_SYNCHRONIZATION
    e.value("OESMSG_RPT_REPORT_SYNCHRONIZATION", _eOesMsgType::OESMSG_RPT_REPORT_SYNCHRONIZATION);
    // _eOesMsgType::OESMSG_RPT_BUSINESS_REJECT
    e.value("OESMSG_RPT_BUSINESS_REJECT", _eOesMsgType::OESMSG_RPT_BUSINESS_REJECT);
    // _eOesMsgType::OESMSG_RPT_ORDER_INSERT
    e.value("OESMSG_RPT_ORDER_INSERT", _eOesMsgType::OESMSG_RPT_ORDER_INSERT);
    // _eOesMsgType::OESMSG_RPT_ORDER_REPORT
    e.value("OESMSG_RPT_ORDER_REPORT", _eOesMsgType::OESMSG_RPT_ORDER_REPORT);
    // _eOesMsgType::OESMSG_RPT_TRADE_REPORT
    e.value("OESMSG_RPT_TRADE_REPORT", _eOesMsgType::OESMSG_RPT_TRADE_REPORT);
    // _eOesMsgType::OESMSG_RPT_FUND_TRSF_REJECT
    e.value("OESMSG_RPT_FUND_TRSF_REJECT", _eOesMsgType::OESMSG_RPT_FUND_TRSF_REJECT);
    // _eOesMsgType::OESMSG_RPT_FUND_TRSF_REPORT
    e.value("OESMSG_RPT_FUND_TRSF_REPORT", _eOesMsgType::OESMSG_RPT_FUND_TRSF_REPORT);
    // _eOesMsgType::OESMSG_RPT_CASH_ASSET_VARIATION
    e.value("OESMSG_RPT_CASH_ASSET_VARIATION", _eOesMsgType::OESMSG_RPT_CASH_ASSET_VARIATION);
    // _eOesMsgType::OESMSG_RPT_STOCK_HOLDING_VARIATION
    e.value("OESMSG_RPT_STOCK_HOLDING_VARIATION", _eOesMsgType::OESMSG_RPT_STOCK_HOLDING_VARIATION);
    // _eOesMsgType::OESMSG_RPT_OPTION_HOLDING_VARIATION
    e.value("OESMSG_RPT_OPTION_HOLDING_VARIATION", _eOesMsgType::OESMSG_RPT_OPTION_HOLDING_VARIATION);
    // _eOesMsgType::OESMSG_RPT_SERVICE_STATE
    e.value("OESMSG_RPT_SERVICE_STATE", _eOesMsgType::OESMSG_RPT_SERVICE_STATE);
    // _eOesMsgType::__OESMSG_RPT_MAX
    e.value("__OESMSG_RPT_MAX", _eOesMsgType::__OESMSG_RPT_MAX);
    // _eOesMsgType::__OESMSG_NONTRD_MIN
    e.value("__OESMSG_NONTRD_MIN", _eOesMsgType::__OESMSG_NONTRD_MIN);
    // _eOesMsgType::OESMSG_NONTRD_FUND_TRSF_REQ
    e.value("OESMSG_NONTRD_FUND_TRSF_REQ", _eOesMsgType::OESMSG_NONTRD_FUND_TRSF_REQ);
    // _eOesMsgType::OESMSG_NONTRD_CHANGE_PASSWORD
    e.value("OESMSG_NONTRD_CHANGE_PASSWORD", _eOesMsgType::OESMSG_NONTRD_CHANGE_PASSWORD);
    // _eOesMsgType::__OESMSG_NONTRD_MAX
    e.value("__OESMSG_NONTRD_MAX", _eOesMsgType::__OESMSG_NONTRD_MAX);
    // _eOesMsgType::__OESMSG_QRYMSG_MIN
    e.value("__OESMSG_QRYMSG_MIN", _eOesMsgType::__OESMSG_QRYMSG_MIN);
    // _eOesMsgType::OESMSG_QRYMSG_CLIENT_OVERVIEW
    e.value("OESMSG_QRYMSG_CLIENT_OVERVIEW", _eOesMsgType::OESMSG_QRYMSG_CLIENT_OVERVIEW);
    // _eOesMsgType::OESMSG_QRYMSG_ORD
    e.value("OESMSG_QRYMSG_ORD", _eOesMsgType::OESMSG_QRYMSG_ORD);
    // _eOesMsgType::OESMSG_QRYMSG_TRD
    e.value("OESMSG_QRYMSG_TRD", _eOesMsgType::OESMSG_QRYMSG_TRD);
    // _eOesMsgType::OESMSG_QRYMSG_CASH_ASSET
    e.value("OESMSG_QRYMSG_CASH_ASSET", _eOesMsgType::OESMSG_QRYMSG_CASH_ASSET);
    // _eOesMsgType::OESMSG_QRYMSG_STK_HLD
    e.value("OESMSG_QRYMSG_STK_HLD", _eOesMsgType::OESMSG_QRYMSG_STK_HLD);
    // _eOesMsgType::OESMSG_QRYMSG_OPT_HLD
    e.value("OESMSG_QRYMSG_OPT_HLD", _eOesMsgType::OESMSG_QRYMSG_OPT_HLD);
    // _eOesMsgType::OESMSG_QRYMSG_CUST
    e.value("OESMSG_QRYMSG_CUST", _eOesMsgType::OESMSG_QRYMSG_CUST);
    // _eOesMsgType::OESMSG_QRYMSG_COMMISSION_RATE
    e.value("OESMSG_QRYMSG_COMMISSION_RATE", _eOesMsgType::OESMSG_QRYMSG_COMMISSION_RATE);
    // _eOesMsgType::OESMSG_QRYMSG_FUND_TRSF
    e.value("OESMSG_QRYMSG_FUND_TRSF", _eOesMsgType::OESMSG_QRYMSG_FUND_TRSF);
    // _eOesMsgType::OESMSG_QRYMSG_ETF
    e.value("OESMSG_QRYMSG_ETF", _eOesMsgType::OESMSG_QRYMSG_ETF);
    // _eOesMsgType::OESMSG_QRYMSG_ETF_COMPONENT
    e.value("OESMSG_QRYMSG_ETF_COMPONENT", _eOesMsgType::OESMSG_QRYMSG_ETF_COMPONENT);
    // _eOesMsgType::OESMSG_QRYMSG_OPTION
    e.value("OESMSG_QRYMSG_OPTION", _eOesMsgType::OESMSG_QRYMSG_OPTION);
    // _eOesMsgType::OESMSG_QRYMSG_ISSUE
    e.value("OESMSG_QRYMSG_ISSUE", _eOesMsgType::OESMSG_QRYMSG_ISSUE);
    // _eOesMsgType::OESMSG_QRYMSG_LOT_WINNING
    e.value("OESMSG_QRYMSG_LOT_WINNING", _eOesMsgType::OESMSG_QRYMSG_LOT_WINNING);
    // _eOesMsgType::OESMSG_QRYMSG_TRADING_DAY
    e.value("OESMSG_QRYMSG_TRADING_DAY", _eOesMsgType::OESMSG_QRYMSG_TRADING_DAY);
    // _eOesMsgType::OESMSG_QRYMSG_MARKET_STATE
    e.value("OESMSG_QRYMSG_MARKET_STATE", _eOesMsgType::OESMSG_QRYMSG_MARKET_STATE);
    // _eOesMsgType::OESMSG_QRYMSG_COUNTER_CASH
    e.value("OESMSG_QRYMSG_COUNTER_CASH", _eOesMsgType::OESMSG_QRYMSG_COUNTER_CASH);
    // _eOesMsgType::OESMSG_QRYMSG_INV_ACCT
    e.value("OESMSG_QRYMSG_INV_ACCT", _eOesMsgType::OESMSG_QRYMSG_INV_ACCT);
    // _eOesMsgType::OESMSG_QRYMSG_STOCK
    e.value("OESMSG_QRYMSG_STOCK", _eOesMsgType::OESMSG_QRYMSG_STOCK);
    // _eOesMsgType::__OESMSG_QRYMSG_MAX
    e.value("__OESMSG_QRYMSG_MAX", _eOesMsgType::__OESMSG_QRYMSG_MAX);
    // _eOesMsgType::OESMSG_SESS_HEARTBEAT
    e.value("OESMSG_SESS_HEARTBEAT", _eOesMsgType::OESMSG_SESS_HEARTBEAT);
    // _eOesMsgType::OESMSG_SESS_TEST_REQUEST
    e.value("OESMSG_SESS_TEST_REQUEST", _eOesMsgType::OESMSG_SESS_TEST_REQUEST);
    // _eOesMsgType::OESMSG_SESS_LOGIN_EXTEND
    e.value("OESMSG_SESS_LOGIN_EXTEND", _eOesMsgType::OESMSG_SESS_LOGIN_EXTEND);
    // _eOesMsgType::OESMSG_SESS_LOGOUT
    e.value("OESMSG_SESS_LOGOUT", _eOesMsgType::OESMSG_SESS_LOGOUT);
    // _eOesMsgType::OESMSG_RPT_ORDER_REJECT
    e.value("OESMSG_RPT_ORDER_REJECT", _eOesMsgType::OESMSG_RPT_ORDER_REJECT);
    // _eOesMsgType::OESMSG_QRYMSG_INV_ACCT_L001508
    e.value("OESMSG_QRYMSG_INV_ACCT_L001508", _eOesMsgType::OESMSG_QRYMSG_INV_ACCT_L001508);
    // _eOesMsgType::OESMSG_QRYMSG_STOCK_L001508
    e.value("OESMSG_QRYMSG_STOCK_L001508", _eOesMsgType::OESMSG_QRYMSG_STOCK_L001508);
    e.export_values();
    module_vnoes::objects.emplace("_eOesMsgType", e);
}
void generate_enum_eOesSubscribeReportType(pybind11::object & parent)
{
    // _eOesSubscribeReportType
    pybind11::enum_<_eOesSubscribeReportType> e(parent, "_eOesSubscribeReportType", pybind11::arithmetic());
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_DEFAULT
    e.value("OES_SUB_RPT_TYPE_DEFAULT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_DEFAULT);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_BUSINESS_REJECT
    e.value("OES_SUB_RPT_TYPE_BUSINESS_REJECT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_BUSINESS_REJECT);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ORDER_INSERT
    e.value("OES_SUB_RPT_TYPE_ORDER_INSERT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ORDER_INSERT);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ORDER_REPORT
    e.value("OES_SUB_RPT_TYPE_ORDER_REPORT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ORDER_REPORT);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_TRADE_REPORT
    e.value("OES_SUB_RPT_TYPE_TRADE_REPORT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_TRADE_REPORT);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_FUND_TRSF_REPORT
    e.value("OES_SUB_RPT_TYPE_FUND_TRSF_REPORT", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_FUND_TRSF_REPORT);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION
    e.value("OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_HOLDING_VARIATION
    e.value("OES_SUB_RPT_TYPE_HOLDING_VARIATION", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_HOLDING_VARIATION);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_MARKET_STATE
    e.value("OES_SUB_RPT_TYPE_MARKET_STATE", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_MARKET_STATE);
    // _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ALL
    e.value("OES_SUB_RPT_TYPE_ALL", _eOesSubscribeReportType::OES_SUB_RPT_TYPE_ALL);
    // _eOesSubscribeReportType::__MAX_OES_SUB_RPT_TYPE
    e.value("__MAX_OES_SUB_RPT_TYPE", _eOesSubscribeReportType::__MAX_OES_SUB_RPT_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eOesSubscribeReportType", e);
}
void generate_enum_eOesProtocolHintsType(pybind11::object & parent)
{
    // _eOesProtocolHintsType
    pybind11::enum_<_eOesProtocolHintsType> e(parent, "_eOesProtocolHintsType", pybind11::arithmetic());
    // _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_DEFAULT
    e.value("OES_PROT_HINTS_TYPE_DEFAULT", _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_DEFAULT);
    // _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_COMPRESS
    e.value("OES_PROT_HINTS_TYPE_COMPRESS", _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_COMPRESS);
    // _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_NONE
    e.value("OES_PROT_HINTS_TYPE_NONE", _eOesProtocolHintsType::OES_PROT_HINTS_TYPE_NONE);
    // _eOesProtocolHintsType::__MAX_OES_PROT_HINTS_TYPE
    e.value("__MAX_OES_PROT_HINTS_TYPE", _eOesProtocolHintsType::__MAX_OES_PROT_HINTS_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eOesProtocolHintsType", e);
}
void generate_enum_eSSocketProtocolType(pybind11::object & parent)
{
    // _eSSocketProtocolType
    pybind11::enum_<_eSSocketProtocolType> e(parent, "_eSSocketProtocolType", pybind11::arithmetic());
    // _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_TCP
    e.value("SPK_SOCKET_PROTOCOL_TCP", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_TCP);
    // _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_IPC
    e.value("SPK_SOCKET_PROTOCOL_IPC", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_IPC);
    // _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_UDP_UCAST
    e.value("SPK_SOCKET_PROTOCOL_UDP_UCAST", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_UDP_UCAST);
    // _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_UDP_MCAST
    e.value("SPK_SOCKET_PROTOCOL_UDP_MCAST", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_UDP_MCAST);
    // _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_PGM
    e.value("SPK_SOCKET_PROTOCOL_PGM", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_PGM);
    // _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_EPGM
    e.value("SPK_SOCKET_PROTOCOL_EPGM", _eSSocketProtocolType::SPK_SOCKET_PROTOCOL_EPGM);
    // _eSSocketProtocolType::__MAX_SPK_SOCKET_PROTOCOL
    e.value("__MAX_SPK_SOCKET_PROTOCOL", _eSSocketProtocolType::__MAX_SPK_SOCKET_PROTOCOL);
    e.export_values();
    module_vnoes::objects.emplace("_eSSocketProtocolType", e);
}
void generate_enum_eGeneralClientClusterType(pybind11::object & parent)
{
    // _eGeneralClientClusterType
    pybind11::enum_<_eGeneralClientClusterType> e(parent, "_eGeneralClientClusterType", pybind11::arithmetic());
    // _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_UNDEFINED
    e.value("GENERAL_CLI_CLUSTER_UNDEFINED", _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_UNDEFINED);
    // _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_REPLICA_SET
    e.value("GENERAL_CLI_CLUSTER_REPLICA_SET", _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_REPLICA_SET);
    // _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_PEER_NODES
    e.value("GENERAL_CLI_CLUSTER_PEER_NODES", _eGeneralClientClusterType::GENERAL_CLI_CLUSTER_PEER_NODES);
    // _eGeneralClientClusterType::__MAX_GENERAL_CLI_CLUSTER_TYPE
    e.value("__MAX_GENERAL_CLI_CLUSTER_TYPE", _eGeneralClientClusterType::__MAX_GENERAL_CLI_CLUSTER_TYPE);
    e.export_values();
    module_vnoes::objects.emplace("_eGeneralClientClusterType", e);
}
