#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"


void generate_class_ITapTrade_TapAPIApplicationInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIApplicationInfo> c(parent, "TapAPIApplicationInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIApplicationInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIApplicationInfo, "AuthCode", AuthCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIApplicationInfo, "KeyOperationLogPath", KeyOperationLogPath);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIApplicationInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIApplicationInfo", c);
}
void generate_class_ITapTrade_TapAPICommodity(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICommodity> c(parent, "TapAPICommodity");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICommodity>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodity, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodity, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodity, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICommodity, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICommodity", c);
}
void generate_class_ITapTrade_TapAPIContract(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIContract> c(parent, "TapAPIContract");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIContract>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "Commodity", Commodity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "ContractNo1", ContractNo1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "StrikePrice1", StrikePrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "CallOrPutFlag1", CallOrPutFlag1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIContract, "CallOrPutFlag2", CallOrPutFlag2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIContract, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIContract", c);
}
void generate_class_ITapTrade_TapAPIExchangeInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIExchangeInfo> c(parent, "TapAPIExchangeInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIExchangeInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIExchangeInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIExchangeInfo, "ExchangeName", ExchangeName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIExchangeInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIExchangeInfo", c);
}
void generate_class_ITapTrade_TapAPIChangePasswordReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIChangePasswordReq> c(parent, "TapAPIChangePasswordReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIChangePasswordReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "PasswordType", PasswordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "OldPassword", OldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIChangePasswordReq, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIChangePasswordReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIChangePasswordReq", c);
}
void generate_class_ITapTrade_TapAPIAuthPasswordReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAuthPasswordReq> c(parent, "TapAPIAuthPasswordReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAuthPasswordReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, "PasswordType", PasswordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, "Password", Password);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAuthPasswordReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAuthPasswordReq", c);
}
void generate_class_ITapTrade_TapAPITradeLoginAuth(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeLoginAuth> c(parent, "TapAPITradeLoginAuth");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeLoginAuth>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "ISModifyPassword", ISModifyPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "Password", Password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginAuth, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeLoginAuth, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeLoginAuth", c);
}
void generate_class_ITapTrade_TapAPITradeLoginRspInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeLoginRspInfo> c(parent, "TapAPITradeLoginRspInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeLoginRspInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "UserType", UserType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "UserName", UserName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "ReservedInfo", ReservedInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginIP", LastLoginIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginProt", LastLoginProt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginTime", LastLoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastLogoutTime", LastLogoutTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "TradeDate", TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "LastSettleTime", LastSettleTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "StartTime", StartTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, "InitTime", InitTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeLoginRspInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeLoginRspInfo", c);
}
void generate_class_ITapTrade_TapAPIRequestVertificateCodeRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIRequestVertificateCodeRsp> c(parent, "TapAPIRequestVertificateCodeRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIRequestVertificateCodeRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIRequestVertificateCodeRsp, "SecondSerialID", SecondSerialID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIRequestVertificateCodeRsp, "Effective", Effective);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIRequestVertificateCodeRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIRequestVertificateCodeRsp", c);
}
void generate_class_ITapTrade_TapAPIAccQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccQryReq> c(parent, "TapAPIAccQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccQryReq>)
        c.def(pybind11::init<>());
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountInfo> c(parent, "TapAPIAccountInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountType", AccountType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountState", AccountState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountTradeRight", AccountTradeRight);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "CommodityGroupNo", CommodityGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountShortName", AccountShortName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountInfo, "AccountEnShortName", AccountEnShortName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountInfo", c);
}
void generate_class_ITapTrade_TapAPINewOrder(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPINewOrder> c(parent, "TapAPINewOrder");
    if constexpr (std::is_constructible_v<
        ITapTrade::TapAPINewOrder
    >)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "MinClipSize", MinClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "MaxClipSize", MaxClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "ClientID", ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TacticsType", TacticsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TriggerCondition", TriggerCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "TriggerPriceType", TriggerPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPINewOrder, "AddOneIsValid", AddOneIsValid);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPINewOrder, c);
    module_vntap::objects.emplace("ITapTrade::TapAPINewOrder", c);
}
void generate_class_ITapTrade_TapAPIOrderInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderInfo> c(parent, "TapAPIOrderInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "MinClipSize", MinClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "MaxClipSize", MaxClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "LicenseNo", LicenseNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientOrderNo", ClientOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientID", ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TacticsType", TacticsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TriggerCondition", TriggerCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "TriggerPriceType", TriggerPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientLocalIP", ClientLocalIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientMac", ClientMac);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ClientIP", ClientIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderStreamID", OrderStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "UpperChannelNo", UpperChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderLocalNo", OrderLocalNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "UpperStreamID", UpperStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderParentSystemNo", OrderParentSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderInsertUserNo", OrderInsertUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderInsertTime", OrderInsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderCommandUserNo", OrderCommandUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderUpdateUserNo", OrderUpdateUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderUpdateTime", OrderUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderState", OrderState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchPrice", OrderMatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchPrice2", OrderMatchPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchQty", OrderMatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "OrderMatchQty2", OrderMatchQty2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "ErrorText", ErrorText);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsBackInput", IsBackInput);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfo, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderInfo", c);
}
void generate_class_ITapTrade_TapAPIOrderInfoNotice(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderInfoNotice> c(parent, "TapAPIOrderInfoNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderInfoNotice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, "OrderInfo", OrderInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderInfoNotice, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderInfoNotice", c);
}
void generate_class_ITapTrade_TapAPIOrderActionRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderActionRsp> c(parent, "TapAPIOrderActionRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderActionRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderActionRsp, "ActionType", ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderActionRsp, "OrderInfo", OrderInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderActionRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderActionRsp", c);
}
void generate_class_ITapTrade_TapAPIAmendOrder(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAmendOrder> c(parent, "TapAPIAmendOrder");
    if constexpr (std::is_constructible_v<
        ITapTrade::TapAPIAmendOrder
    >)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAmendOrder, "ReqData", ReqData);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAmendOrder, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAmendOrder, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAmendOrder, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAmendOrder", c);
}
void generate_class_ITapTrade_TapAPIOrderCancelReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderCancelReq> c(parent, "TapAPIOrderCancelReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderCancelReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderCancelReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderCancelReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderCancelReq", c);
}
void generate_class_ITapTrade_TapAPIOrderQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderQryReq> c(parent, "TapAPIOrderQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsBackInput", IsBackInput);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQryReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderQryReq", c);
}
void generate_class_ITapTrade_TapAPIOrderProcessQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderProcessQryReq> c(parent, "TapAPIOrderProcessQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderProcessQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderProcessQryReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderProcessQryReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderProcessQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderProcessQryReq", c);
}
void generate_class_ITapTrade_TapAPIFillQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillQryReq> c(parent, "TapAPIFillQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillQryReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillQryReq", c);
}
void generate_class_ITapTrade_TapAPIFillInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillInfo> c(parent, "TapAPIFillInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchNo", MatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "UpperMatchNo", UpperMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ExchangeMatchNo", ExchangeMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchDateTime", MatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "UpperMatchDateTime", UpperMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchPrice", MatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "MatchQty", MatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "IsAddOne", IsAddOne);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "FeeCurrencyGroup", FeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "FeeCurrency", FeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "FeeValue", FeeValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "IsManualFee", IsManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFillInfo, "ClosePrositionPrice", ClosePrositionPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFillInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFillInfo", c);
}
void generate_class_ITapTrade_TapAPICloseQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICloseQryReq> c(parent, "TapAPICloseQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICloseQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseQryReq, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICloseQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICloseQryReq", c);
}
void generate_class_ITapTrade_TapAPICloseInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICloseInfo> c(parent, "TapAPICloseInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICloseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseSide", CloseSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseQty", CloseQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "OpenPrice", OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "ClosePrice", ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "OpenMatchNo", OpenMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "OpenMatchDateTime", OpenMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseMatchNo", CloseMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseMatchDateTime", CloseMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseStreamId", CloseStreamId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICloseInfo, "CloseProfit", CloseProfit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICloseInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICloseInfo", c);
}
void generate_class_ITapTrade_TapAPIPositionQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionQryReq> c(parent, "TapAPIPositionQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionQryReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionQryReq", c);
}
void generate_class_ITapTrade_TapAPIPositionInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionInfo> c(parent, "TapAPIPositionInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionNo", PositionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "MatchNo", MatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionPrice", PositionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionQty", PositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionStreamId", PositionStreamId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "CalculatePrice", CalculatePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "AccountInitialMargin", AccountInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "UpperInitialMargin", UpperInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "PositionProfit", PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "LMEPositionProfit", LMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionInfo, "IsHistory", IsHistory);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionInfo", c);
}
void generate_class_ITapTrade_TapAPIPositionProfit(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionProfit> c(parent, "TapAPIPositionProfit");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionProfit>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "PositionNo", PositionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "PositionStreamId", PositionStreamId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "PositionProfit", PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "LMEPositionProfit", LMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfit, "CalculatePrice", CalculatePrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionProfit, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionProfit", c);
}
void generate_class_ITapTrade_TapAPIPositionProfitNotice(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionProfitNotice> c(parent, "TapAPIPositionProfitNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionProfitNotice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfitNotice, "IsLast", IsLast);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionProfitNotice, "Data", Data);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionProfitNotice, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionProfitNotice", c);
}
void generate_class_ITapTrade_TapAPIPositionSummary(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionSummary> c(parent, "TapAPIPositionSummary");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionSummary>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "PositionPrice", PositionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "PositionQty", PositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIPositionSummary, "HisPositionQty", HisPositionQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIPositionSummary, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIPositionSummary", c);
}
void generate_class_ITapTrade_TapAPIFundReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFundReq> c(parent, "TapAPIFundReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFundReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFundReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFundReq", c);
}
void generate_class_ITapTrade_TapAPIFundData(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFundData> c(parent, "TapAPIFundData");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFundData>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "TradeRate", TradeRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FutureAlg", FutureAlg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "OptionAlg", OptionAlg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreBalance", PreBalance);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreUnExpProfit", PreUnExpProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreLMEPositionProfit", PreLMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreEquity", PreEquity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreAvailable1", PreAvailable1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PreMarketEquity", PreMarketEquity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashInValue", CashInValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashOutValue", CashOutValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashAdjustValue", CashAdjustValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CashPledged", CashPledged);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FrozenFee", FrozenFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FrozenDeposit", FrozenDeposit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountFee", AccountFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "SwapInValue", SwapInValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "SwapOutValue", SwapOutValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PremiumIncome", PremiumIncome);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PremiumPay", PremiumPay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CloseProfit", CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "FrozenFund", FrozenFund);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "UnExpProfit", UnExpProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "ExpProfit", ExpProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "PositionProfit", PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "LmePositionProfit", LmePositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountIntialMargin", AccountIntialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "UpperInitalMargin", UpperInitalMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Discount", Discount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Balance", Balance);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Equity", Equity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "Available", Available);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "CanDraw", CanDraw);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "MarketEquity", MarketEquity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIFundData, "AuthMoney", AuthMoney);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIFundData, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIFundData", c);
}
