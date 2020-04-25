#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "TORATstpMdApi.h"
#include "TORATstpTraderApi.h"
#include "TORATstpUserApiDataType.h"
#include "TORATstpUserApiStruct.h"


void generate_class_CTORATstpQryInvestorField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryInvestorField> c(parent, "CTORATstpQryInvestorField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryInvestorField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryInvestorField, "InvestorID", InvestorID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryInvestorField, c);
    module_vntora::objects.emplace("CTORATstpQryInvestorField", c);
}
void generate_class_CTORATstpInvestorField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInvestorField> c(parent, "CTORATstpInvestorField");
    if constexpr (std::is_default_constructible_v<CTORATstpInvestorField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "InvestorName", InvestorName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "IdCardType", IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "IdCardNo", IdCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "Telephone", Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "Address", Address);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "OpenDate", OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "Mobile", Mobile);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "Operways", Operways);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "CRiskLevel", CRiskLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorField, "ProfInvestorType", ProfInvestorType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInvestorField, c);
    module_vntora::objects.emplace("CTORATstpInvestorField", c);
}
void generate_class_CTORATstpQryShareholderAccountField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryShareholderAccountField> c(parent, "CTORATstpQryShareholderAccountField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryShareholderAccountField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderAccountField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderAccountField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderAccountField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderAccountField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderAccountField, "TradingCodeClass", TradingCodeClass);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryShareholderAccountField, c);
    module_vntora::objects.emplace("CTORATstpQryShareholderAccountField", c);
}
void generate_class_CTORATstpShareholderAccountField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpShareholderAccountField> c(parent, "CTORATstpShareholderAccountField");
    if constexpr (std::is_default_constructible_v<CTORATstpShareholderAccountField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderAccountField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderAccountField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderAccountField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderAccountField, "ClientIDType", ClientIDType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderAccountField, "MarketID", MarketID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpShareholderAccountField, c);
    module_vntora::objects.emplace("CTORATstpShareholderAccountField", c);
}
void generate_class_CTORATstpQryBusinessUnitField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryBusinessUnitField> c(parent, "CTORATstpQryBusinessUnitField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryBusinessUnitField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBusinessUnitField, "InvestorID", InvestorID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryBusinessUnitField, c);
    module_vntora::objects.emplace("CTORATstpQryBusinessUnitField", c);
}
void generate_class_CTORATstpBusinessUnitField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpBusinessUnitField> c(parent, "CTORATstpBusinessUnitField");
    if constexpr (std::is_default_constructible_v<CTORATstpBusinessUnitField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitField, "BusinessUnitName", BusinessUnitName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpBusinessUnitField, c);
    module_vntora::objects.emplace("CTORATstpBusinessUnitField", c);
}
void generate_class_CTORATstpQryBusinessUnitAndTradingAcctField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryBusinessUnitAndTradingAcctField> c(parent, "CTORATstpQryBusinessUnitAndTradingAcctField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryBusinessUnitAndTradingAcctField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBusinessUnitAndTradingAcctField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBusinessUnitAndTradingAcctField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBusinessUnitAndTradingAcctField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBusinessUnitAndTradingAcctField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBusinessUnitAndTradingAcctField, "CurrencyID", CurrencyID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryBusinessUnitAndTradingAcctField, c);
    module_vntora::objects.emplace("CTORATstpQryBusinessUnitAndTradingAcctField", c);
}
void generate_class_CTORATstpBusinessUnitAndTradingAcctField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpBusinessUnitAndTradingAcctField> c(parent, "CTORATstpBusinessUnitAndTradingAcctField");
    if constexpr (std::is_default_constructible_v<CTORATstpBusinessUnitAndTradingAcctField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpBusinessUnitAndTradingAcctField, c);
    module_vntora::objects.emplace("CTORATstpBusinessUnitAndTradingAcctField", c);
}
void generate_class_CTORATstpQryOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryOrderField> c(parent, "CTORATstpQryOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "InsertTimeStart", InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "InsertTimeEnd", InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderField, "IsCancel", IsCancel);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryOrderField, c);
    module_vntora::objects.emplace("CTORATstpQryOrderField", c);
}
void generate_class_CTORATstpQryOrderActionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryOrderActionField> c(parent, "CTORATstpQryOrderActionField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryOrderActionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderActionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderActionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderActionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderActionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderActionField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderActionField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderActionField, "IInfo", IInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryOrderActionField, c);
    module_vntora::objects.emplace("CTORATstpQryOrderActionField", c);
}
void generate_class_CTORATstpQryTradeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryTradeField> c(parent, "CTORATstpQryTradeField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryTradeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "TradeID", TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "TradeTimeStart", TradeTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "TradeTimeEnd", TradeTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradeField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryTradeField, c);
    module_vntora::objects.emplace("CTORATstpQryTradeField", c);
}
void generate_class_CTORATstpQryTradingAccountField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryTradingAccountField> c(parent, "CTORATstpQryTradingAccountField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryTradingAccountField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingAccountField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingAccountField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingAccountField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingAccountField, "AccountType", AccountType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingAccountField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryTradingAccountField, c);
    module_vntora::objects.emplace("CTORATstpQryTradingAccountField", c);
}
void generate_class_CTORATstpTradingAccountField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpTradingAccountField> c(parent, "CTORATstpTradingAccountField");
    if constexpr (std::is_default_constructible_v<CTORATstpTradingAccountField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "Available", Available);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "WithdrawQuota", WithdrawQuota);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "Deposit", Deposit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "Withdraw", Withdraw);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "FrozenMargin", FrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "FrozenCash", FrozenCash);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "FrozenCommission", FrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "CurrMargin", CurrMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "Commission", Commission);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "AccountType", AccountType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "AccountOwner", AccountOwner);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "BankID", BankID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingAccountField, "BankAccountID", BankAccountID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpTradingAccountField, c);
    module_vntora::objects.emplace("CTORATstpTradingAccountField", c);
}
void generate_class_CTORATstpQryPositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryPositionField> c(parent, "CTORATstpQryPositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryPositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryPositionField, c);
    module_vntora::objects.emplace("CTORATstpQryPositionField", c);
}
void generate_class_CTORATstpPositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpPositionField> c(parent, "CTORATstpPositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpPositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "HistoryPos", HistoryPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "HistoryPosFrozen", HistoryPosFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TodayBSPos", TodayBSPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TodayBSFrozen", TodayBSFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TodayPRPos", TodayPRPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TodayPRFrozen", TodayPRFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TotalPosCost", TotalPosCost);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TodaySMPos", TodaySMPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "TodaySMPosFrozen", TodaySMPosFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "MarginBuyPos", MarginBuyPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "ShortSellPos", ShortSellPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "PrePosition", PrePosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "AvailablePosition", AvailablePosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "CurrentPosition", CurrentPosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionField, "LastPrice", LastPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpPositionField, c);
    module_vntora::objects.emplace("CTORATstpPositionField", c);
}
void generate_class_CTORATstpQryTradingFeeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryTradingFeeField> c(parent, "CTORATstpQryTradingFeeField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryTradingFeeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingFeeField, "ExchangeID", ExchangeID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryTradingFeeField, c);
    module_vntora::objects.emplace("CTORATstpQryTradingFeeField", c);
}
void generate_class_CTORATstpTradingFeeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpTradingFeeField> c(parent, "CTORATstpTradingFeeField");
    if constexpr (std::is_default_constructible_v<CTORATstpTradingFeeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "BizClass", BizClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "StampTaxRatioByAmt", StampTaxRatioByAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "StampTaxRatioByPar", StampTaxRatioByPar);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "StampTaxFeePerOrder", StampTaxFeePerOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "StampTaxFeeMin", StampTaxFeeMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "StampTaxFeeMax", StampTaxFeeMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "TransferRatioByAmt", TransferRatioByAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "TransferRatioByPar", TransferRatioByPar);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "TransferFeePerOrder", TransferFeePerOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "TransferFeeMin", TransferFeeMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "TransferFeeMax", TransferFeeMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "HandlingRatioByAmt", HandlingRatioByAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "HandlingRatioByPar", HandlingRatioByPar);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "HandlingFeePerOrder", HandlingFeePerOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "HandlingFeeMin", HandlingFeeMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "HandlingFeeMax", HandlingFeeMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "RegulateRatioByAmt", RegulateRatioByAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "RegulateRatioByPar", RegulateRatioByPar);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "RegulateFeePerOrder", RegulateFeePerOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "RegulateFeeMin", RegulateFeeMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "RegulateFeeMax", RegulateFeeMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "TransferFeeByVolume", TransferFeeByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "HandlingFeeByVolume", HandlingFeeByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SettlementRatioByAmt", SettlementRatioByAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SettlementRatioByPar", SettlementRatioByPar);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SettlementFeePerOrder", SettlementFeePerOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SettlementFeeByVolume", SettlementFeeByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SettlementFeeMin", SettlementFeeMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingFeeField, "SettlementFeeMax", SettlementFeeMax);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpTradingFeeField, c);
    module_vntora::objects.emplace("CTORATstpTradingFeeField", c);
}
void generate_class_CTORATstpQryInvestorTradingFeeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryInvestorTradingFeeField> c(parent, "CTORATstpQryInvestorTradingFeeField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryInvestorTradingFeeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryInvestorTradingFeeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryInvestorTradingFeeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryInvestorTradingFeeField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryInvestorTradingFeeField, c);
    module_vntora::objects.emplace("CTORATstpQryInvestorTradingFeeField", c);
}
void generate_class_CTORATstpInvestorTradingFeeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInvestorTradingFeeField> c(parent, "CTORATstpInvestorTradingFeeField");
    if constexpr (std::is_default_constructible_v<CTORATstpInvestorTradingFeeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "BizClass", BizClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "BrokerageType", BrokerageType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "RatioByAmt", RatioByAmt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "RatioByPar", RatioByPar);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "FeePerOrder", FeePerOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "FeeMin", FeeMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "FeeMax", FeeMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "FeeByVolume", FeeByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorTradingFeeField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInvestorTradingFeeField, c);
    module_vntora::objects.emplace("CTORATstpInvestorTradingFeeField", c);
}
void generate_class_CTORATstpQryIPOQuotaField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryIPOQuotaField> c(parent, "CTORATstpQryIPOQuotaField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryIPOQuotaField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOQuotaField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOQuotaField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOQuotaField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOQuotaField, "ShareholderID", ShareholderID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryIPOQuotaField, c);
    module_vntora::objects.emplace("CTORATstpQryIPOQuotaField", c);
}
void generate_class_CTORATstpIPOQuotaField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpIPOQuotaField> c(parent, "CTORATstpIPOQuotaField");
    if constexpr (std::is_default_constructible_v<CTORATstpIPOQuotaField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOQuotaField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOQuotaField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOQuotaField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOQuotaField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOQuotaField, "MaxVolume", MaxVolume);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpIPOQuotaField, c);
    module_vntora::objects.emplace("CTORATstpIPOQuotaField", c);
}
void generate_class_CTORATstpQryMarketField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryMarketField> c(parent, "CTORATstpQryMarketField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryMarketField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryMarketField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryMarketField, "MarketID", MarketID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryMarketField, c);
    module_vntora::objects.emplace("CTORATstpQryMarketField", c);
}
void generate_class_CTORATstpMarketField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpMarketField> c(parent, "CTORATstpMarketField");
    if constexpr (std::is_default_constructible_v<CTORATstpMarketField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketField, "MarketName", MarketName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketField, "ExchangeID", ExchangeID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpMarketField, c);
    module_vntora::objects.emplace("CTORATstpMarketField", c);
}
void generate_class_CTORATstpQryOrderFundDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryOrderFundDetailField> c(parent, "CTORATstpQryOrderFundDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryOrderFundDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderFundDetailField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderFundDetailField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderFundDetailField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderFundDetailField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderFundDetailField, "InsertTimeStart", InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderFundDetailField, "InsertTimeEnd", InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryOrderFundDetailField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryOrderFundDetailField, c);
    module_vntora::objects.emplace("CTORATstpQryOrderFundDetailField", c);
}
void generate_class_CTORATstpOrderFundDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpOrderFundDetailField> c(parent, "CTORATstpOrderFundDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpOrderFundDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "InstrumentID", InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "TotalFrozen", TotalFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "TotalFee", TotalFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "StampTaxFee", StampTaxFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "HandlingFee", HandlingFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "TransferFee", TransferFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "RegulateFee", RegulateFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "BrokerageFee", BrokerageFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "SettlementFee", SettlementFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "TotalFeeFrozen", TotalFeeFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderFundDetailField, "OrderAmount", OrderAmount);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpOrderFundDetailField, c);
    module_vntora::objects.emplace("CTORATstpOrderFundDetailField", c);
}
void generate_class_CTORATstpQryFundTransferDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryFundTransferDetailField> c(parent, "CTORATstpQryFundTransferDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryFundTransferDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryFundTransferDetailField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryFundTransferDetailField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryFundTransferDetailField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryFundTransferDetailField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryFundTransferDetailField, c);
    module_vntora::objects.emplace("CTORATstpQryFundTransferDetailField", c);
}
void generate_class_CTORATstpFundTransferDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpFundTransferDetailField> c(parent, "CTORATstpFundTransferDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpFundTransferDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "FundSerial", FundSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "Amount", Amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "TransferStatus", TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "OperateSource", OperateSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "OperatorID", OperatorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "OperateDate", OperateDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "BankID", BankID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundTransferDetailField, "BankAccountID", BankAccountID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpFundTransferDetailField, c);
    module_vntora::objects.emplace("CTORATstpFundTransferDetailField", c);
}
void generate_class_CTORATstpQryPositionTransferDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryPositionTransferDetailField> c(parent, "CTORATstpQryPositionTransferDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryPositionTransferDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionTransferDetailField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionTransferDetailField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPositionTransferDetailField, "TransferDirection", TransferDirection);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryPositionTransferDetailField, c);
    module_vntora::objects.emplace("CTORATstpQryPositionTransferDetailField", c);
}
void generate_class_CTORATstpPositionTransferDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpPositionTransferDetailField> c(parent, "CTORATstpPositionTransferDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpPositionTransferDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "PositionSerial", PositionSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "TransferPositionType", TransferPositionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "TransferStatus", TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "HistoryVolume", HistoryVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "TodayBSVolume", TodayBSVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "TodayPRVolume", TodayPRVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "OperatorID", OperatorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "OperateDate", OperateDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPositionTransferDetailField, "StatusMsg", StatusMsg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpPositionTransferDetailField, c);
    module_vntora::objects.emplace("CTORATstpPositionTransferDetailField", c);
}
void generate_class_CTORATstpQryPledgePositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryPledgePositionField> c(parent, "CTORATstpQryPledgePositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryPledgePositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgePositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgePositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgePositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgePositionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgePositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgePositionField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryPledgePositionField, c);
    module_vntora::objects.emplace("CTORATstpQryPledgePositionField", c);
}
void generate_class_CTORATstpPledgePositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpPledgePositionField> c(parent, "CTORATstpPledgePositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpPledgePositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "HisPledgePos", HisPledgePos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "HisPledgePosFrozen", HisPledgePosFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "TodayPledgePos", TodayPledgePos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "TodayPledgePosFrozen", TodayPledgePosFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "PreTotalPledgePos", PreTotalPledgePos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgePositionField, "preAvailablePledgePos", preAvailablePledgePos);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpPledgePositionField, c);
    module_vntora::objects.emplace("CTORATstpPledgePositionField", c);
}
void generate_class_CTORATstpQryPledgeInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryPledgeInfoField> c(parent, "CTORATstpQryPledgeInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryPledgeInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgeInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPledgeInfoField, "SecurityID", SecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryPledgeInfoField, c);
    module_vntora::objects.emplace("CTORATstpQryPledgeInfoField", c);
}
void generate_class_CTORATstpPledgeInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpPledgeInfoField> c(parent, "CTORATstpPledgeInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpPledgeInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "PledgeOrderID", PledgeOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "StandardBondID", StandardBondID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "AllowPledgeIn", AllowPledgeIn);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "AllowPledgeOut", AllowPledgeOut);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "ConversionRate", ConversionRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "PledgeInTradingUnit", PledgeInTradingUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "PledgeOutTradingUnit", PledgeOutTradingUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "PledgeInVolMax", PledgeInVolMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "PledgeInVolMin", PledgeInVolMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "PledgeOutVolMax", PledgeOutVolMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "PledgeOutVolMin", PledgeOutVolMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "IsTodayToPlegeOut", IsTodayToPlegeOut);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPledgeInfoField, "IsCancelOrder", IsCancelOrder);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpPledgeInfoField, c);
    module_vntora::objects.emplace("CTORATstpPledgeInfoField", c);
}
