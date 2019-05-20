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
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIApplicationInfo, "AuthCode", AuthCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIApplicationInfo, "KeyOperationLogPath", KeyOperationLogPath);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIApplicationInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIApplicationInfo", c);
}
void generate_class_ITapTrade_TapAPICommodity(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICommodity> c(parent, "TapAPICommodity");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICommodity>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodity, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodity, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodity, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPICommodity, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPICommodity", c);
}
void generate_class_ITapTrade_TapAPIContract(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIContract> c(parent, "TapAPIContract");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIContract>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIContract, "Commodity", Commodity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIContract, "ContractNo1", ContractNo1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIContract, "StrikePrice1", StrikePrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIContract, "CallOrPutFlag1", CallOrPutFlag1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIContract, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIContract, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIContract, "CallOrPutFlag2", CallOrPutFlag2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIContract, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIContract", c);
}
void generate_class_ITapTrade_TapAPIExchangeInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIExchangeInfo> c(parent, "TapAPIExchangeInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIExchangeInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIExchangeInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIExchangeInfo, "ExchangeName", ExchangeName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIExchangeInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIExchangeInfo", c);
}
void generate_class_ITapTrade_TapAPIChangePasswordReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIChangePasswordReq> c(parent, "TapAPIChangePasswordReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIChangePasswordReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIChangePasswordReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIChangePasswordReq, "PasswordType", PasswordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIChangePasswordReq, "OldPassword", OldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIChangePasswordReq, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIChangePasswordReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIChangePasswordReq", c);
}
void generate_class_ITapTrade_TapAPIAuthPasswordReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAuthPasswordReq> c(parent, "TapAPIAuthPasswordReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAuthPasswordReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAuthPasswordReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAuthPasswordReq, "PasswordType", PasswordType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAuthPasswordReq, "Password", Password);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAuthPasswordReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAuthPasswordReq", c);
}
void generate_class_ITapTrade_TapAPITradeLoginAuth(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeLoginAuth> c(parent, "TapAPITradeLoginAuth");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeLoginAuth>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginAuth, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginAuth, "ISModifyPassword", ISModifyPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginAuth, "Password", Password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginAuth, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPITradeLoginAuth, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPITradeLoginAuth", c);
}
void generate_class_ITapTrade_TapAPITradeLoginRspInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeLoginRspInfo> c(parent, "TapAPITradeLoginRspInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeLoginRspInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "UserType", UserType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "UserName", UserName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "ReservedInfo", ReservedInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginIP", LastLoginIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginProt", LastLoginProt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "LastLoginTime", LastLoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "LastLogoutTime", LastLogoutTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "TradeDate", TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "LastSettleTime", LastSettleTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "StartTime", StartTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, "InitTime", InitTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPITradeLoginRspInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPITradeLoginRspInfo", c);
}
void generate_class_ITapTrade_TapAPIRequestVertificateCodeRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIRequestVertificateCodeRsp> c(parent, "TapAPIRequestVertificateCodeRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIRequestVertificateCodeRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIRequestVertificateCodeRsp, "SecondSerialID", SecondSerialID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIRequestVertificateCodeRsp, "Effective", Effective);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIRequestVertificateCodeRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIRequestVertificateCodeRsp", c);
}
void generate_class_ITapTrade_TapAPIAccQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccQryReq> c(parent, "TapAPIAccQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccQryReq>)
        c.def(pybind11::init<>());
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountInfo> c(parent, "TapAPIAccountInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountInfo, "AccountType", AccountType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountInfo, "AccountState", AccountState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountInfo, "AccountTradeRight", AccountTradeRight);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountInfo, "CommodityGroupNo", CommodityGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountInfo, "AccountShortName", AccountShortName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountInfo, "AccountEnShortName", AccountEnShortName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccountInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccountInfo", c);
}
void generate_class_ITapTrade_TapAPINewOrder(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPINewOrder> c(parent, "TapAPINewOrder");
    if constexpr (std::is_constructible_v<
        ITapTrade::TapAPINewOrder
    >)
        c.def(pybind11::init<ITapTrade::TapAPINewOrder>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "MinClipSize", MinClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "MaxClipSize", MaxClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "ClientID", ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "TacticsType", TacticsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "TriggerCondition", TriggerCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "TriggerPriceType", TriggerPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPINewOrder, "AddOneIsValid", AddOneIsValid);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPINewOrder, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPINewOrder", c);
}
void generate_class_ITapTrade_TapAPIOrderInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderInfo> c(parent, "TapAPIOrderInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "MinClipSize", MinClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "MaxClipSize", MaxClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "LicenseNo", LicenseNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ClientOrderNo", ClientOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ClientID", ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "TacticsType", TacticsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "TriggerCondition", TriggerCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "TriggerPriceType", TriggerPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ClientLocalIP", ClientLocalIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ClientMac", ClientMac);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ClientIP", ClientIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderStreamID", OrderStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "UpperChannelNo", UpperChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderLocalNo", OrderLocalNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "UpperStreamID", UpperStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderParentSystemNo", OrderParentSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderInsertUserNo", OrderInsertUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderInsertTime", OrderInsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderCommandUserNo", OrderCommandUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderUpdateUserNo", OrderUpdateUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderUpdateTime", OrderUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderState", OrderState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderMatchPrice", OrderMatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderMatchPrice2", OrderMatchPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderMatchQty", OrderMatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "OrderMatchQty2", OrderMatchQty2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "ErrorText", ErrorText);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "IsBackInput", IsBackInput);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfo, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderInfo", c);
}
void generate_class_ITapTrade_TapAPIOrderInfoNotice(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderInfoNotice> c(parent, "TapAPIOrderInfoNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderInfoNotice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfoNotice, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfoNotice, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderInfoNotice, "OrderInfo", OrderInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderInfoNotice, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderInfoNotice", c);
}
void generate_class_ITapTrade_TapAPIOrderActionRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderActionRsp> c(parent, "TapAPIOrderActionRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderActionRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderActionRsp, "ActionType", ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderActionRsp, "OrderInfo", OrderInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderActionRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderActionRsp", c);
}
void generate_class_ITapTrade_TapAPIAmendOrder(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAmendOrder> c(parent, "TapAPIAmendOrder");
    if constexpr (std::is_constructible_v<
        ITapTrade::TapAPIAmendOrder
    >)
        c.def(pybind11::init<ITapTrade::TapAPIAmendOrder>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAmendOrder, "ReqData", ReqData);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAmendOrder, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAmendOrder, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAmendOrder, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAmendOrder", c);
}
void generate_class_ITapTrade_TapAPIOrderCancelReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderCancelReq> c(parent, "TapAPIOrderCancelReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderCancelReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderCancelReq, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderCancelReq, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderCancelReq, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderCancelReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderCancelReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderCancelReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderCancelReq", c);
}
void generate_class_ITapTrade_TapAPIOrderQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderQryReq> c(parent, "TapAPIOrderQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "IsBackInput", IsBackInput);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQryReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderQryReq", c);
}
void generate_class_ITapTrade_TapAPIOrderProcessQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderProcessQryReq> c(parent, "TapAPIOrderProcessQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderProcessQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderProcessQryReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderProcessQryReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderProcessQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderProcessQryReq", c);
}
void generate_class_ITapTrade_TapAPIFillQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillQryReq> c(parent, "TapAPIFillQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillQryReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIFillQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIFillQryReq", c);
}
void generate_class_ITapTrade_TapAPIFillInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFillInfo> c(parent, "TapAPIFillInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFillInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "MatchNo", MatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "UpperMatchNo", UpperMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "ExchangeMatchNo", ExchangeMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "MatchDateTime", MatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "UpperMatchDateTime", UpperMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "MatchPrice", MatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "MatchQty", MatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "IsAddOne", IsAddOne);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "FeeCurrencyGroup", FeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "FeeCurrency", FeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "FeeValue", FeeValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "IsManualFee", IsManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFillInfo, "ClosePrositionPrice", ClosePrositionPrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIFillInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIFillInfo", c);
}
void generate_class_ITapTrade_TapAPICloseQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICloseQryReq> c(parent, "TapAPICloseQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICloseQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseQryReq, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPICloseQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPICloseQryReq", c);
}
void generate_class_ITapTrade_TapAPICloseInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICloseInfo> c(parent, "TapAPICloseInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICloseInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CloseSide", CloseSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CloseQty", CloseQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "OpenPrice", OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "ClosePrice", ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "OpenMatchNo", OpenMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "OpenMatchDateTime", OpenMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CloseMatchNo", CloseMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CloseMatchDateTime", CloseMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CloseStreamId", CloseStreamId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICloseInfo, "CloseProfit", CloseProfit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPICloseInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPICloseInfo", c);
}
void generate_class_ITapTrade_TapAPIPositionQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionQryReq> c(parent, "TapAPIPositionQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionQryReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIPositionQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIPositionQryReq", c);
}
void generate_class_ITapTrade_TapAPIPositionInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionInfo> c(parent, "TapAPIPositionInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "PositionNo", PositionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "MatchNo", MatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "PositionPrice", PositionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "PositionQty", PositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "PositionStreamId", PositionStreamId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "CalculatePrice", CalculatePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "AccountInitialMargin", AccountInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "UpperInitialMargin", UpperInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "PositionProfit", PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "LMEPositionProfit", LMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionInfo, "IsHistory", IsHistory);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIPositionInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIPositionInfo", c);
}
void generate_class_ITapTrade_TapAPIPositionProfit(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionProfit> c(parent, "TapAPIPositionProfit");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionProfit>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfit, "PositionNo", PositionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfit, "PositionStreamId", PositionStreamId);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfit, "PositionProfit", PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfit, "LMEPositionProfit", LMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfit, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfit, "CalculatePrice", CalculatePrice);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIPositionProfit, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIPositionProfit", c);
}
void generate_class_ITapTrade_TapAPIPositionProfitNotice(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionProfitNotice> c(parent, "TapAPIPositionProfitNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionProfitNotice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfitNotice, "IsLast", IsLast);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionProfitNotice, "Data", Data);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIPositionProfitNotice, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIPositionProfitNotice", c);
}
void generate_class_ITapTrade_TapAPIPositionSummary(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIPositionSummary> c(parent, "TapAPIPositionSummary");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIPositionSummary>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "PositionPrice", PositionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "PositionQty", PositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIPositionSummary, "HisPositionQty", HisPositionQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIPositionSummary, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIPositionSummary", c);
}
void generate_class_ITapTrade_TapAPIFundReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFundReq> c(parent, "TapAPIFundReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFundReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIFundReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIFundReq", c);
}
void generate_class_ITapTrade_TapAPIFundData(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIFundData> c(parent, "TapAPIFundData");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIFundData>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "TradeRate", TradeRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "FutureAlg", FutureAlg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "OptionAlg", OptionAlg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PreBalance", PreBalance);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PreUnExpProfit", PreUnExpProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PreLMEPositionProfit", PreLMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PreEquity", PreEquity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PreAvailable1", PreAvailable1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PreMarketEquity", PreMarketEquity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CashInValue", CashInValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CashOutValue", CashOutValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CashAdjustValue", CashAdjustValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CashPledged", CashPledged);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "FrozenFee", FrozenFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "FrozenDeposit", FrozenDeposit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "AccountFee", AccountFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "SwapInValue", SwapInValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "SwapOutValue", SwapOutValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PremiumIncome", PremiumIncome);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PremiumPay", PremiumPay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CloseProfit", CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "FrozenFund", FrozenFund);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "UnExpProfit", UnExpProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "ExpProfit", ExpProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "PositionProfit", PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "LmePositionProfit", LmePositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "AccountIntialMargin", AccountIntialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "UpperInitalMargin", UpperInitalMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "Discount", Discount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "Balance", Balance);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "Equity", Equity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "Available", Available);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "CanDraw", CanDraw);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "MarketEquity", MarketEquity);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIFundData, "AuthMoney", AuthMoney);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIFundData, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIFundData", c);
}
void generate_class_ITapTrade_TapAPICommodityInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICommodityInfo> c(parent, "TapAPICommodityInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICommodityInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CommodityName", CommodityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CommodityEngName", CommodityEngName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "RelateExchangeNo", RelateExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "RelateCommodityType", RelateCommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "RelateCommodityNo", RelateCommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "RelateExchangeNo2", RelateExchangeNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "RelateCommodityType2", RelateCommodityType2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "RelateCommodityNo2", RelateCommodityNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "TradeCurrency", TradeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "ContractSize", ContractSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "OpenCloseMode", OpenCloseMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "StrikePriceTimes", StrikePriceTimes);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CommodityTickSize", CommodityTickSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CommodityDenominator", CommodityDenominator);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CmbDirect", CmbDirect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "DeliveryMode", DeliveryMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "DeliveryDays", DeliveryDays);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "AddOneTime", AddOneTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "CommodityTimeZone", CommodityTimeZone);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICommodityInfo, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPICommodityInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPICommodityInfo", c);
}
