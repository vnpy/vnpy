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


void generate_vntap(pybind11::module & parent)
{
    generate_vntap_sub_namespace(parent);
    generate_vntap_classes(parent);
    generate_vntap_enums(parent);
    generate_vntap_functions(parent);
    generate_vntap_variables(parent);
    generate_vntap_typedefs(parent);
    generate_vntap_caster(parent);
}
void generate_sub_namespace_ITapTrade(pybind11::module & parent)
{
    generate_ITapTrade_sub_namespace(parent);
    generate_ITapTrade_classes(parent);
    generate_ITapTrade_enums(parent);
    generate_ITapTrade_functions(parent);
    generate_ITapTrade_variables(parent);
    generate_ITapTrade_typedefs(parent);
    generate_ITapTrade_caster(parent);
}
void generate_ITapTrade_sub_namespace(pybind11::module & parent)
{
    
}
void generate_class_ITapTrade_TapAPIApplicationInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPIApplicationInfo
    pybind11::class_<ITapTrade::TapAPIApplicationInfo> c(parent, "TapAPIApplicationInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIApplicationInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIApplicationInfo::AuthCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIApplicationInfo, "AuthCode", AuthCode);
    // ITapTrade::TapAPIApplicationInfo::KeyOperationLogPath
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIApplicationInfo, "KeyOperationLogPath", KeyOperationLogPath);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIApplicationInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIApplicationInfo", c);
}
void generate_class_ITapTrade_TapAPICommodity(pybind11::object & parent)
{
    // ITapTrade::TapAPICommodity
    pybind11::class_<ITapTrade::TapAPICommodity> c(parent, "TapAPICommodity");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICommodity>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPICommodity::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodity, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPICommodity::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodity, "CommodityType", CommodityType);
    // ITapTrade::TapAPICommodity::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodity, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICommodity, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICommodity", c);
}
void generate_class_ITapTrade_TapAPIContract(pybind11::object & parent)
{
    // ITapTrade::TapAPIContract
    pybind11::class_<ITapTrade::TapAPIContract> c(parent, "TapAPIContract");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIContract>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIContract::Commodity
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "Commodity", Commodity);
    // ITapTrade::TapAPIContract::ContractNo1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "ContractNo1", ContractNo1);
    // ITapTrade::TapAPIContract::StrikePrice1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "StrikePrice1", StrikePrice1);
    // ITapTrade::TapAPIContract::CallOrPutFlag1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "CallOrPutFlag1", CallOrPutFlag1);
    // ITapTrade::TapAPIContract::ContractNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "ContractNo2", ContractNo2);
    // ITapTrade::TapAPIContract::StrikePrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "StrikePrice2", StrikePrice2);
    // ITapTrade::TapAPIContract::CallOrPutFlag2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "CallOrPutFlag2", CallOrPutFlag2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIContract, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIContract", c);
}
void generate_class_ITapTrade_TapAPIExchangeInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPIExchangeInfo
    pybind11::class_<ITapTrade::TapAPIExchangeInfo> c(parent, "TapAPIExchangeInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIExchangeInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIExchangeInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIExchangeInfo, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIExchangeInfo::ExchangeName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIExchangeInfo, "ExchangeName", ExchangeName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIExchangeInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIExchangeInfo", c);
}
void generate_class_ITapTrade_TapAPIChangePasswordReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIChangePasswordReq
    pybind11::class_<ITapTrade::TapAPIChangePasswordReq> c(parent, "TapAPIChangePasswordReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIChangePasswordReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIChangePasswordReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIChangePasswordReq::PasswordType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "PasswordType", PasswordType);
    // ITapTrade::TapAPIChangePasswordReq::OldPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "OldPassword", OldPassword);
    // ITapTrade::TapAPIChangePasswordReq::NewPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIChangePasswordReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIChangePasswordReq", c);
}
void generate_class_ITapTrade_TapAPIAuthPasswordReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIAuthPasswordReq
    pybind11::class_<ITapTrade::TapAPIAuthPasswordReq> c(parent, "TapAPIAuthPasswordReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAuthPasswordReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAuthPasswordReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIAuthPasswordReq::PasswordType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, "PasswordType", PasswordType);
    // ITapTrade::TapAPIAuthPasswordReq::Password
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, "Password", Password);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAuthPasswordReq", c);
}
void generate_class_ITapTrade_TapAPITradeLoginAuth(pybind11::object & parent)
{
    // ITapTrade::TapAPITradeLoginAuth
    pybind11::class_<ITapTrade::TapAPITradeLoginAuth> c(parent, "TapAPITradeLoginAuth");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeLoginAuth>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPITradeLoginAuth::UserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "UserNo", UserNo);
    // ITapTrade::TapAPITradeLoginAuth::ISModifyPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "ISModifyPassword", ISModifyPassword);
    // ITapTrade::TapAPITradeLoginAuth::Password
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "Password", Password);
    // ITapTrade::TapAPITradeLoginAuth::NewPassword
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeLoginAuth, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeLoginAuth", c);
}
void generate_class_ITapTrade_TapAPITradeLoginRspInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPITradeLoginRspInfo
    pybind11::class_<ITapTrade::TapAPITradeLoginRspInfo> c(parent, "TapAPITradeLoginRspInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeLoginRspInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPITradeLoginRspInfo::UserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "UserNo", UserNo);
    // ITapTrade::TapAPITradeLoginRspInfo::UserType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "UserType", UserType);
    // ITapTrade::TapAPITradeLoginRspInfo::UserName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "UserName", UserName);
    // ITapTrade::TapAPITradeLoginRspInfo::ReservedInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "ReservedInfo", ReservedInfo);
    // ITapTrade::TapAPITradeLoginRspInfo::LastLoginIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginIP", LastLoginIP);
    // ITapTrade::TapAPITradeLoginRspInfo::LastLoginProt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginProt", LastLoginProt);
    // ITapTrade::TapAPITradeLoginRspInfo::LastLoginTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginTime", LastLoginTime);
    // ITapTrade::TapAPITradeLoginRspInfo::LastLogoutTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLogoutTime", LastLogoutTime);
    // ITapTrade::TapAPITradeLoginRspInfo::TradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "TradeDate", TradeDate);
    // ITapTrade::TapAPITradeLoginRspInfo::LastSettleTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastSettleTime", LastSettleTime);
    // ITapTrade::TapAPITradeLoginRspInfo::StartTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "StartTime", StartTime);
    // ITapTrade::TapAPITradeLoginRspInfo::InitTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "InitTime", InitTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeLoginRspInfo", c);
}
void generate_class_ITapTrade_TapAPIRequestVertificateCodeRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIRequestVertificateCodeRsp
    pybind11::class_<ITapTrade::TapAPIRequestVertificateCodeRsp> c(parent, "TapAPIRequestVertificateCodeRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIRequestVertificateCodeRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIRequestVertificateCodeRsp::SecondSerialID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIRequestVertificateCodeRsp, "SecondSerialID", SecondSerialID);
    // ITapTrade::TapAPIRequestVertificateCodeRsp::Effective
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIRequestVertificateCodeRsp, "Effective", Effective);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIRequestVertificateCodeRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIRequestVertificateCodeRsp", c);
}
void generate_class_ITapTrade_TapAPIAccQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccQryReq
    pybind11::class_<ITapTrade::TapAPIAccQryReq> c(parent, "TapAPIAccQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccQryReq>)
        c.def(pybind11::init<>());
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPIAccountInfo
    pybind11::class_<ITapTrade::TapAPIAccountInfo> c(parent, "TapAPIAccountInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAccountInfo::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountNo", AccountNo);
    // ITapTrade::TapAPIAccountInfo::AccountType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountType", AccountType);
    // ITapTrade::TapAPIAccountInfo::AccountState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountState", AccountState);
    // ITapTrade::TapAPIAccountInfo::AccountTradeRight
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountTradeRight", AccountTradeRight);
    // ITapTrade::TapAPIAccountInfo::CommodityGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "CommodityGroupNo", CommodityGroupNo);
    // ITapTrade::TapAPIAccountInfo::AccountShortName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountShortName", AccountShortName);
    // ITapTrade::TapAPIAccountInfo::AccountEnShortName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountEnShortName", AccountEnShortName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountInfo", c);
}
void generate_class_ITapTrade_TapAPINewOrder(pybind11::object & parent)
{
    // ITapTrade::TapAPINewOrder
    pybind11::class_<ITapTrade::TapAPINewOrder> c(parent, "TapAPINewOrder");
    if constexpr (std::is_constructible_v<
        ITapTrade::TapAPINewOrder
    >)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPINewOrder::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "AccountNo", AccountNo);
    // ITapTrade::TapAPINewOrder::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPINewOrder::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CommodityType", CommodityType);
    // ITapTrade::TapAPINewOrder::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPINewOrder::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ContractNo", ContractNo);
    // ITapTrade::TapAPINewOrder::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPINewOrder::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPINewOrder::ContractNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ContractNo2", ContractNo2);
    // ITapTrade::TapAPINewOrder::StrikePrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "StrikePrice2", StrikePrice2);
    // ITapTrade::TapAPINewOrder::CallOrPutFlag2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CallOrPutFlag2", CallOrPutFlag2);
    // ITapTrade::TapAPINewOrder::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderType", OrderType);
    // ITapTrade::TapAPINewOrder::OrderSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderSource", OrderSource);
    // ITapTrade::TapAPINewOrder::TimeInForce
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TimeInForce", TimeInForce);
    // ITapTrade::TapAPINewOrder::ExpireTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ExpireTime", ExpireTime);
    // ITapTrade::TapAPINewOrder::IsRiskOrder
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "IsRiskOrder", IsRiskOrder);
    // ITapTrade::TapAPINewOrder::OrderSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderSide", OrderSide);
    // ITapTrade::TapAPINewOrder::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPINewOrder::PositionEffect2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "PositionEffect2", PositionEffect2);
    // ITapTrade::TapAPINewOrder::InquiryNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "InquiryNo", InquiryNo);
    // ITapTrade::TapAPINewOrder::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPINewOrder::OrderPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderPrice", OrderPrice);
    // ITapTrade::TapAPINewOrder::OrderPrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderPrice2", OrderPrice2);
    // ITapTrade::TapAPINewOrder::StopPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "StopPrice", StopPrice);
    // ITapTrade::TapAPINewOrder::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderQty", OrderQty);
    // ITapTrade::TapAPINewOrder::OrderMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderMinQty", OrderMinQty);
    // ITapTrade::TapAPINewOrder::MinClipSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "MinClipSize", MinClipSize);
    // ITapTrade::TapAPINewOrder::MaxClipSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "MaxClipSize", MaxClipSize);
    // ITapTrade::TapAPINewOrder::RefInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "RefInt", RefInt);
    // ITapTrade::TapAPINewOrder::RefDouble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "RefDouble", RefDouble);
    // ITapTrade::TapAPINewOrder::RefString
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "RefString", RefString);
    // ITapTrade::TapAPINewOrder::ClientID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ClientID", ClientID);
    // ITapTrade::TapAPINewOrder::TacticsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TacticsType", TacticsType);
    // ITapTrade::TapAPINewOrder::TriggerCondition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TriggerCondition", TriggerCondition);
    // ITapTrade::TapAPINewOrder::TriggerPriceType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TriggerPriceType", TriggerPriceType);
    // ITapTrade::TapAPINewOrder::AddOneIsValid
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "AddOneIsValid", AddOneIsValid);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPINewOrder, c);
    module_vntap::objects.emplace("ITapTrade::TapAPINewOrder", c);
}
void generate_class_ITapTrade_TapAPIOrderInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderInfo
    pybind11::class_<ITapTrade::TapAPIOrderInfo> c(parent, "TapAPIOrderInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderInfo::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "AccountNo", AccountNo);
    // ITapTrade::TapAPIOrderInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIOrderInfo::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CommodityType", CommodityType);
    // ITapTrade::TapAPIOrderInfo::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIOrderInfo::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ContractNo", ContractNo);
    // ITapTrade::TapAPIOrderInfo::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIOrderInfo::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIOrderInfo::ContractNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ContractNo2", ContractNo2);
    // ITapTrade::TapAPIOrderInfo::StrikePrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "StrikePrice2", StrikePrice2);
    // ITapTrade::TapAPIOrderInfo::CallOrPutFlag2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CallOrPutFlag2", CallOrPutFlag2);
    // ITapTrade::TapAPIOrderInfo::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderType", OrderType);
    // ITapTrade::TapAPIOrderInfo::OrderSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderSource", OrderSource);
    // ITapTrade::TapAPIOrderInfo::TimeInForce
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TimeInForce", TimeInForce);
    // ITapTrade::TapAPIOrderInfo::ExpireTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ExpireTime", ExpireTime);
    // ITapTrade::TapAPIOrderInfo::IsRiskOrder
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsRiskOrder", IsRiskOrder);
    // ITapTrade::TapAPIOrderInfo::OrderSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderSide", OrderSide);
    // ITapTrade::TapAPIOrderInfo::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPIOrderInfo::PositionEffect2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "PositionEffect2", PositionEffect2);
    // ITapTrade::TapAPIOrderInfo::InquiryNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "InquiryNo", InquiryNo);
    // ITapTrade::TapAPIOrderInfo::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPIOrderInfo::OrderPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderPrice", OrderPrice);
    // ITapTrade::TapAPIOrderInfo::OrderPrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderPrice2", OrderPrice2);
    // ITapTrade::TapAPIOrderInfo::StopPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "StopPrice", StopPrice);
    // ITapTrade::TapAPIOrderInfo::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderQty", OrderQty);
    // ITapTrade::TapAPIOrderInfo::OrderMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMinQty", OrderMinQty);
    // ITapTrade::TapAPIOrderInfo::RefInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "RefInt", RefInt);
    // ITapTrade::TapAPIOrderInfo::RefDouble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "RefDouble", RefDouble);
    // ITapTrade::TapAPIOrderInfo::RefString
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "RefString", RefString);
    // ITapTrade::TapAPIOrderInfo::MinClipSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "MinClipSize", MinClipSize);
    // ITapTrade::TapAPIOrderInfo::MaxClipSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "MaxClipSize", MaxClipSize);
    // ITapTrade::TapAPIOrderInfo::LicenseNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "LicenseNo", LicenseNo);
    // ITapTrade::TapAPIOrderInfo::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderInfo::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderNo", OrderNo);
    // ITapTrade::TapAPIOrderInfo::ClientOrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientOrderNo", ClientOrderNo);
    // ITapTrade::TapAPIOrderInfo::ClientID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientID", ClientID);
    // ITapTrade::TapAPIOrderInfo::TacticsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TacticsType", TacticsType);
    // ITapTrade::TapAPIOrderInfo::TriggerCondition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TriggerCondition", TriggerCondition);
    // ITapTrade::TapAPIOrderInfo::TriggerPriceType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TriggerPriceType", TriggerPriceType);
    // ITapTrade::TapAPIOrderInfo::AddOneIsValid
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "AddOneIsValid", AddOneIsValid);
    // ITapTrade::TapAPIOrderInfo::ClientLocalIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientLocalIP", ClientLocalIP);
    // ITapTrade::TapAPIOrderInfo::ClientMac
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientMac", ClientMac);
    // ITapTrade::TapAPIOrderInfo::ClientIP
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientIP", ClientIP);
    // ITapTrade::TapAPIOrderInfo::OrderStreamID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderStreamID", OrderStreamID);
    // ITapTrade::TapAPIOrderInfo::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "UpperNo", UpperNo);
    // ITapTrade::TapAPIOrderInfo::UpperChannelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "UpperChannelNo", UpperChannelNo);
    // ITapTrade::TapAPIOrderInfo::OrderLocalNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderLocalNo", OrderLocalNo);
    // ITapTrade::TapAPIOrderInfo::UpperStreamID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "UpperStreamID", UpperStreamID);
    // ITapTrade::TapAPIOrderInfo::OrderSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderSystemNo", OrderSystemNo);
    // ITapTrade::TapAPIOrderInfo::OrderExchangeSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    // ITapTrade::TapAPIOrderInfo::OrderParentSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderParentSystemNo", OrderParentSystemNo);
    // ITapTrade::TapAPIOrderInfo::OrderInsertUserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderInsertUserNo", OrderInsertUserNo);
    // ITapTrade::TapAPIOrderInfo::OrderInsertTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderInsertTime", OrderInsertTime);
    // ITapTrade::TapAPIOrderInfo::OrderCommandUserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderCommandUserNo", OrderCommandUserNo);
    // ITapTrade::TapAPIOrderInfo::OrderUpdateUserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderUpdateUserNo", OrderUpdateUserNo);
    // ITapTrade::TapAPIOrderInfo::OrderUpdateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderUpdateTime", OrderUpdateTime);
    // ITapTrade::TapAPIOrderInfo::OrderState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderState", OrderState);
    // ITapTrade::TapAPIOrderInfo::OrderMatchPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchPrice", OrderMatchPrice);
    // ITapTrade::TapAPIOrderInfo::OrderMatchPrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchPrice2", OrderMatchPrice2);
    // ITapTrade::TapAPIOrderInfo::OrderMatchQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchQty", OrderMatchQty);
    // ITapTrade::TapAPIOrderInfo::OrderMatchQty2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchQty2", OrderMatchQty2);
    // ITapTrade::TapAPIOrderInfo::ErrorCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ErrorCode", ErrorCode);
    // ITapTrade::TapAPIOrderInfo::ErrorText
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ErrorText", ErrorText);
    // ITapTrade::TapAPIOrderInfo::IsBackInput
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsBackInput", IsBackInput);
    // ITapTrade::TapAPIOrderInfo::IsDeleted
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsDeleted", IsDeleted);
    // ITapTrade::TapAPIOrderInfo::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderInfo", c);
}
void generate_class_ITapTrade_TapAPIOrderInfoNotice(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderInfoNotice
    pybind11::class_<ITapTrade::TapAPIOrderInfoNotice> c(parent, "TapAPIOrderInfoNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderInfoNotice>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderInfoNotice::SessionID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, "SessionID", SessionID);
    // ITapTrade::TapAPIOrderInfoNotice::ErrorCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, "ErrorCode", ErrorCode);
    // ITapTrade::TapAPIOrderInfoNotice::OrderInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, "OrderInfo", OrderInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderInfoNotice", c);
}
void generate_class_ITapTrade_TapAPIOrderActionRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderActionRsp
    pybind11::class_<ITapTrade::TapAPIOrderActionRsp> c(parent, "TapAPIOrderActionRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderActionRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderActionRsp::ActionType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderActionRsp, "ActionType", ActionType);
    // ITapTrade::TapAPIOrderActionRsp::OrderInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderActionRsp, "OrderInfo", OrderInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderActionRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderActionRsp", c);
}
void generate_class_ITapTrade_TapAPIAmendOrder(pybind11::object & parent)
{
    // ITapTrade::TapAPIAmendOrder
    pybind11::class_<ITapTrade::TapAPIAmendOrder> c(parent, "TapAPIAmendOrder");
    if constexpr (std::is_constructible_v<
        ITapTrade::TapAPIAmendOrder
    >)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIAmendOrder::ReqData
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAmendOrder, "ReqData", ReqData);
    // ITapTrade::TapAPIAmendOrder::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAmendOrder, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIAmendOrder::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAmendOrder, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAmendOrder, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAmendOrder", c);
}
void generate_class_ITapTrade_TapAPIOrderCancelReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIOrderCancelReq
    pybind11::class_<ITapTrade::TapAPIOrderCancelReq> c(parent, "TapAPIOrderCancelReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderCancelReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIOrderCancelReq::RefInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "RefInt", RefInt);
    // ITapTrade::TapAPIOrderCancelReq::RefDouble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "RefDouble", RefDouble);
    // ITapTrade::TapAPIOrderCancelReq::RefString
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "RefString", RefString);
    // ITapTrade::TapAPIOrderCancelReq::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIOrderCancelReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderCancelReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderCancelReq", c);
}
