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


void generate_class_ITapTrade_TapAPIHisPositionQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisPositionQryReq
    pybind11::class_<ITapTrade::TapAPIHisPositionQryReq> c(parent, "TapAPIHisPositionQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisPositionQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisPositionQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisPositionQryReq::Date
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, "Date", Date);
    // ITapTrade::TapAPIHisPositionQryReq::SettleFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, "SettleFlag", SettleFlag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisPositionQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisPositionQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisPositionQryRsp
    pybind11::class_<ITapTrade::TapAPIHisPositionQryRsp> c(parent, "TapAPIHisPositionQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisPositionQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisPositionQryRsp::SettleDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "SettleDate", SettleDate);
    // ITapTrade::TapAPIHisPositionQryRsp::OpenDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "OpenDate", OpenDate);
    // ITapTrade::TapAPIHisPositionQryRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisPositionQryRsp::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIHisPositionQryRsp::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CommodityType", CommodityType);
    // ITapTrade::TapAPIHisPositionQryRsp::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIHisPositionQryRsp::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "ContractNo", ContractNo);
    // ITapTrade::TapAPIHisPositionQryRsp::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIHisPositionQryRsp::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIHisPositionQryRsp::MatchSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "MatchSide", MatchSide);
    // ITapTrade::TapAPIHisPositionQryRsp::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPIHisPositionQryRsp::PositionPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionPrice", PositionPrice);
    // ITapTrade::TapAPIHisPositionQryRsp::PositionQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionQty", PositionQty);
    // ITapTrade::TapAPIHisPositionQryRsp::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "OrderNo", OrderNo);
    // ITapTrade::TapAPIHisPositionQryRsp::PositionNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionNo", PositionNo);
    // ITapTrade::TapAPIHisPositionQryRsp::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "UpperNo", UpperNo);
    // ITapTrade::TapAPIHisPositionQryRsp::CurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CurrencyGroup", CurrencyGroup);
    // ITapTrade::TapAPIHisPositionQryRsp::Currency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "Currency", Currency);
    // ITapTrade::TapAPIHisPositionQryRsp::PreSettlePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PreSettlePrice", PreSettlePrice);
    // ITapTrade::TapAPIHisPositionQryRsp::SettlePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "SettlePrice", SettlePrice);
    // ITapTrade::TapAPIHisPositionQryRsp::PositionDProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionDProfit", PositionDProfit);
    // ITapTrade::TapAPIHisPositionQryRsp::LMEPositionProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "LMEPositionProfit", LMEPositionProfit);
    // ITapTrade::TapAPIHisPositionQryRsp::OptionMarketValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "OptionMarketValue", OptionMarketValue);
    // ITapTrade::TapAPIHisPositionQryRsp::AccountInitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "AccountInitialMargin", AccountInitialMargin);
    // ITapTrade::TapAPIHisPositionQryRsp::AccountMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    // ITapTrade::TapAPIHisPositionQryRsp::UpperInitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "UpperInitialMargin", UpperInitialMargin);
    // ITapTrade::TapAPIHisPositionQryRsp::UpperMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    // ITapTrade::TapAPIHisPositionQryRsp::SettleGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "SettleGroupNo", SettleGroupNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisPositionQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisDeliveryQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisDeliveryQryReq
    pybind11::class_<ITapTrade::TapAPIHisDeliveryQryReq> c(parent, "TapAPIHisDeliveryQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisDeliveryQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisDeliveryQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisDeliveryQryReq::AccountAttributeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "AccountAttributeNo", AccountAttributeNo);
    // ITapTrade::TapAPIHisDeliveryQryReq::BeginDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "BeginDate", BeginDate);
    // ITapTrade::TapAPIHisDeliveryQryReq::EndDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "EndDate", EndDate);
    // ITapTrade::TapAPIHisDeliveryQryReq::CountType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "CountType", CountType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisDeliveryQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisDeliveryQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisDeliveryQryRsp
    pybind11::class_<ITapTrade::TapAPIHisDeliveryQryRsp> c(parent, "TapAPIHisDeliveryQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisDeliveryQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisDeliveryQryRsp::DeliveryDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryDate", DeliveryDate);
    // ITapTrade::TapAPIHisDeliveryQryRsp::OpenDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenDate", OpenDate);
    // ITapTrade::TapAPIHisDeliveryQryRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisDeliveryQryRsp::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIHisDeliveryQryRsp::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityType", CommodityType);
    // ITapTrade::TapAPIHisDeliveryQryRsp::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIHisDeliveryQryRsp::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "ContractNo", ContractNo);
    // ITapTrade::TapAPIHisDeliveryQryRsp::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIHisDeliveryQryRsp::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIHisDeliveryQryRsp::MatchSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "MatchSource", MatchSource);
    // ITapTrade::TapAPIHisDeliveryQryRsp::OpenSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenSide", OpenSide);
    // ITapTrade::TapAPIHisDeliveryQryRsp::OpenPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenPrice", OpenPrice);
    // ITapTrade::TapAPIHisDeliveryQryRsp::DeliveryPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryPrice", DeliveryPrice);
    // ITapTrade::TapAPIHisDeliveryQryRsp::DeliveryQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryQty", DeliveryQty);
    // ITapTrade::TapAPIHisDeliveryQryRsp::FrozenQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "FrozenQty", FrozenQty);
    // ITapTrade::TapAPIHisDeliveryQryRsp::OpenNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenNo", OpenNo);
    // ITapTrade::TapAPIHisDeliveryQryRsp::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperNo", UpperNo);
    // ITapTrade::TapAPIHisDeliveryQryRsp::CommodityCurrencyGroupy
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityCurrencyGroupy", CommodityCurrencyGroupy);
    // ITapTrade::TapAPIHisDeliveryQryRsp::CommodityCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityCurrency", CommodityCurrency);
    // ITapTrade::TapAPIHisDeliveryQryRsp::PreSettlePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "PreSettlePrice", PreSettlePrice);
    // ITapTrade::TapAPIHisDeliveryQryRsp::DeliveryProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryProfit", DeliveryProfit);
    // ITapTrade::TapAPIHisDeliveryQryRsp::AccountFrozenInitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFrozenInitialMargin", AccountFrozenInitialMargin);
    // ITapTrade::TapAPIHisDeliveryQryRsp::AccountFrozenMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFrozenMaintenanceMargin", AccountFrozenMaintenanceMargin);
    // ITapTrade::TapAPIHisDeliveryQryRsp::UpperFrozenInitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFrozenInitialMargin", UpperFrozenInitialMargin);
    // ITapTrade::TapAPIHisDeliveryQryRsp::UpperFrozenMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFrozenMaintenanceMargin", UpperFrozenMaintenanceMargin);
    // ITapTrade::TapAPIHisDeliveryQryRsp::AccountFeeCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFeeCurrencyGroup", AccountFeeCurrencyGroup);
    // ITapTrade::TapAPIHisDeliveryQryRsp::AccountFeeCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFeeCurrency", AccountFeeCurrency);
    // ITapTrade::TapAPIHisDeliveryQryRsp::AccountDeliveryFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountDeliveryFee", AccountDeliveryFee);
    // ITapTrade::TapAPIHisDeliveryQryRsp::UpperFeeCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFeeCurrencyGroup", UpperFeeCurrencyGroup);
    // ITapTrade::TapAPIHisDeliveryQryRsp::UpperFeeCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFeeCurrency", UpperFeeCurrency);
    // ITapTrade::TapAPIHisDeliveryQryRsp::UpperDeliveryFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperDeliveryFee", UpperDeliveryFee);
    // ITapTrade::TapAPIHisDeliveryQryRsp::DeliveryMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryMode", DeliveryMode);
    // ITapTrade::TapAPIHisDeliveryQryRsp::OperatorNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OperatorNo", OperatorNo);
    // ITapTrade::TapAPIHisDeliveryQryRsp::OperateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OperateTime", OperateTime);
    // ITapTrade::TapAPIHisDeliveryQryRsp::SettleGourpNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "SettleGourpNo", SettleGourpNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisDeliveryQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccountCashAdjustQryReq
    pybind11::class_<ITapTrade::TapAPIAccountCashAdjustQryReq> c(parent, "TapAPIAccountCashAdjustQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountCashAdjustQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAccountCashAdjustQryReq::SerialID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "SerialID", SerialID);
    // ITapTrade::TapAPIAccountCashAdjustQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIAccountCashAdjustQryReq::AccountAttributeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "AccountAttributeNo", AccountAttributeNo);
    // ITapTrade::TapAPIAccountCashAdjustQryReq::BeginDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "BeginDate", BeginDate);
    // ITapTrade::TapAPIAccountCashAdjustQryReq::EndDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "EndDate", EndDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountCashAdjustQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccountCashAdjustQryRsp
    pybind11::class_<ITapTrade::TapAPIAccountCashAdjustQryRsp> c(parent, "TapAPIAccountCashAdjustQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountCashAdjustQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::Date
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "Date", Date);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::CashAdjustType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustType", CashAdjustType);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::CurrencyGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::CurrencyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CurrencyNo", CurrencyNo);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::CashAdjustValue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustValue", CashAdjustValue);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::CashAdjustRemark
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustRemark", CashAdjustRemark);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::OperateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "OperateTime", OperateTime);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::OperatorNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "OperatorNo", OperatorNo);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::AccountBank
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountBank", AccountBank);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::BankAccount
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "BankAccount", BankAccount);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::AccountLWFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountLWFlag", AccountLWFlag);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::CompanyBank
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CompanyBank", CompanyBank);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::InternalBankAccount
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "InternalBankAccount", InternalBankAccount);
    // ITapTrade::TapAPIAccountCashAdjustQryRsp::CompanyLWFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CompanyLWFlag", CompanyLWFlag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountCashAdjustQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountFeeRentQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccountFeeRentQryReq
    pybind11::class_<ITapTrade::TapAPIAccountFeeRentQryReq> c(parent, "TapAPIAccountFeeRentQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountFeeRentQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAccountFeeRentQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountFeeRentQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountFeeRentQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccountFeeRentQryRsp
    pybind11::class_<ITapTrade::TapAPIAccountFeeRentQryRsp> c(parent, "TapAPIAccountFeeRentQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountFeeRentQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAccountFeeRentQryRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CommodityType", CommodityType);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::MatchSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "MatchSource", MatchSource);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::CalculateMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CalculateMode", CalculateMode);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::CurrencyGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::CurrencyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CurrencyNo", CurrencyNo);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::OpenCloseFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "OpenCloseFee", OpenCloseFee);
    // ITapTrade::TapAPIAccountFeeRentQryRsp::CloseTodayFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CloseTodayFee", CloseTodayFee);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountFeeRentQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountMarginRentQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccountMarginRentQryReq
    pybind11::class_<ITapTrade::TapAPIAccountMarginRentQryReq> c(parent, "TapAPIAccountMarginRentQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountMarginRentQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAccountMarginRentQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIAccountMarginRentQryReq::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIAccountMarginRentQryReq::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "CommodityType", CommodityType);
    // ITapTrade::TapAPIAccountMarginRentQryReq::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountMarginRentQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountMarginRentQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccountMarginRentQryRsp
    pybind11::class_<ITapTrade::TapAPIAccountMarginRentQryRsp> c(parent, "TapAPIAccountMarginRentQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountMarginRentQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAccountMarginRentQryRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CommodityType", CommodityType);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "ContractNo", ContractNo);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::CalculateMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CalculateMode", CalculateMode);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::CurrencyGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::CurrencyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CurrencyNo", CurrencyNo);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::InitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "InitialMargin", InitialMargin);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::MaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "MaintenanceMargin", MaintenanceMargin);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::SellInitialMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "SellInitialMargin", SellInitialMargin);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::SellMaintenanceMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "SellMaintenanceMargin", SellMaintenanceMargin);
    // ITapTrade::TapAPIAccountMarginRentQryRsp::LockMargin
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "LockMargin", LockMargin);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountMarginRentQryRsp", c);
}
void generate_class_ITapTrade_TapAPIOrderQuoteMarketNotice(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderQuoteMarketNotice
    pybind11::class_<ITapTrade::TapAPIOrderQuoteMarketNotice> c(parent, "TapAPIOrderQuoteMarketNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderQuoteMarketNotice>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderQuoteMarketNotice::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIOrderQuoteMarketNotice::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CommodityType", CommodityType);
    // ITapTrade::TapAPIOrderQuoteMarketNotice::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIOrderQuoteMarketNotice::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "ContractNo", ContractNo);
    // ITapTrade::TapAPIOrderQuoteMarketNotice::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIOrderQuoteMarketNotice::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIOrderQuoteMarketNotice::OrderSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "OrderSide", OrderSide);
    // ITapTrade::TapAPIOrderQuoteMarketNotice::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderQuoteMarketNotice", c);
}
void generate_class_ITapTrade_TapAPIOrderMarketInsertReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderMarketInsertReq
    pybind11::class_<ITapTrade::TapAPIOrderMarketInsertReq> c(parent, "TapAPIOrderMarketInsertReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketInsertReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderMarketInsertReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIOrderMarketInsertReq::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIOrderMarketInsertReq::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "CommodityType", CommodityType);
    // ITapTrade::TapAPIOrderMarketInsertReq::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIOrderMarketInsertReq::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ContractNo", ContractNo);
    // ITapTrade::TapAPIOrderMarketInsertReq::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIOrderMarketInsertReq::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIOrderMarketInsertReq::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderType", OrderType);
    // ITapTrade::TapAPIOrderMarketInsertReq::TimeInForce
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "TimeInForce", TimeInForce);
    // ITapTrade::TapAPIOrderMarketInsertReq::ExpireTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ExpireTime", ExpireTime);
    // ITapTrade::TapAPIOrderMarketInsertReq::OrderSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSource", OrderSource);
    // ITapTrade::TapAPIOrderMarketInsertReq::BuyPositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "BuyPositionEffect", BuyPositionEffect);
    // ITapTrade::TapAPIOrderMarketInsertReq::SellPositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "SellPositionEffect", SellPositionEffect);
    // ITapTrade::TapAPIOrderMarketInsertReq::AddOneIsValid
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "AddOneIsValid", AddOneIsValid);
    // ITapTrade::TapAPIOrderMarketInsertReq::OrderBuyPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderBuyPrice", OrderBuyPrice);
    // ITapTrade::TapAPIOrderMarketInsertReq::OrderSellPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSellPrice", OrderSellPrice);
    // ITapTrade::TapAPIOrderMarketInsertReq::OrderBuyQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderBuyQty", OrderBuyQty);
    // ITapTrade::TapAPIOrderMarketInsertReq::OrderSellQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSellQty", OrderSellQty);
    // ITapTrade::TapAPIOrderMarketInsertReq::ClientBuyOrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ClientBuyOrderNo", ClientBuyOrderNo);
    // ITapTrade::TapAPIOrderMarketInsertReq::ClientSellOrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ClientSellOrderNo", ClientSellOrderNo);
    // ITapTrade::TapAPIOrderMarketInsertReq::RefInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "RefInt", RefInt);
    // ITapTrade::TapAPIOrderMarketInsertReq::RefDouble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "RefDouble", RefDouble);
    // ITapTrade::TapAPIOrderMarketInsertReq::RefString
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "RefString", RefString);
    // ITapTrade::TapAPIOrderMarketInsertReq::Remark
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "Remark", Remark);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderMarketInsertReq", c);
}
void generate_class_ITapTrade_TapAPIOrderMarketInsertRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderMarketInsertRsp
    pybind11::class_<ITapTrade::TapAPIOrderMarketInsertRsp> c(parent, "TapAPIOrderMarketInsertRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketInsertRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderMarketInsertRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "CommodityType", CommodityType);
    // ITapTrade::TapAPIOrderMarketInsertRsp::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ContractNo", ContractNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIOrderMarketInsertRsp::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderType", OrderType);
    // ITapTrade::TapAPIOrderMarketInsertRsp::TimeInForce
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "TimeInForce", TimeInForce);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ExpireTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ExpireTime", ExpireTime);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSource", OrderSource);
    // ITapTrade::TapAPIOrderMarketInsertRsp::BuyPositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "BuyPositionEffect", BuyPositionEffect);
    // ITapTrade::TapAPIOrderMarketInsertRsp::SellPositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "SellPositionEffect", SellPositionEffect);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderBuyPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyPrice", OrderBuyPrice);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderSellPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellPrice", OrderSellPrice);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderBuyQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyQty", OrderBuyQty);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderSellQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellQty", OrderSellQty);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderBuyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyNo", OrderBuyNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderSellNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellNo", OrderSellNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::AddOneIsValid
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "AddOneIsValid", AddOneIsValid);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderMarketUserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderMarketUserNo", OrderMarketUserNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::OrderMarketTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderMarketTime", OrderMarketTime);
    // ITapTrade::TapAPIOrderMarketInsertRsp::RefInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefInt", RefInt);
    // ITapTrade::TapAPIOrderMarketInsertRsp::RefDouble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefDouble", RefDouble);
    // ITapTrade::TapAPIOrderMarketInsertRsp::RefString
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefString", RefString);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ClientBuyOrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientBuyOrderNo", ClientBuyOrderNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ClientSellOrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientSellOrderNo", ClientSellOrderNo);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ErrorCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ErrorCode", ErrorCode);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ErrorText
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ErrorText", ErrorText);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ClientLocalIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientLocalIP", ClientLocalIP);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ClientMac
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientMac", ClientMac);
    // ITapTrade::TapAPIOrderMarketInsertRsp::ClientIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientIP", ClientIP);
    // ITapTrade::TapAPIOrderMarketInsertRsp::Remark
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "Remark", Remark);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderMarketInsertRsp", c);
}
