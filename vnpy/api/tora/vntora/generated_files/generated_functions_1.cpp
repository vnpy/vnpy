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


void generate_class_CTORATstpFensUserInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpFensUserInfoField> c(parent, "CTORATstpFensUserInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpFensUserInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFensUserInfoField, "LogInAccount", LogInAccount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFensUserInfoField, "LogInAccountType", LogInAccountType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpFensUserInfoField, c);
    module_vntora::objects.emplace("CTORATstpFensUserInfoField", c);
}
void generate_class_CTORATstpEffectPriceMarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpEffectPriceMarketDataField> c(parent, "CTORATstpEffectPriceMarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpEffectPriceMarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectPriceMarketDataField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectPriceMarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectPriceMarketDataField, "LastPrice", LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectPriceMarketDataField, "TotalVolume", TotalVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectPriceMarketDataField, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectPriceMarketDataField, "UpdateTime", UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectPriceMarketDataField, "UpdateMillisec", UpdateMillisec);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpEffectPriceMarketDataField, c);
    module_vntora::objects.emplace("CTORATstpEffectPriceMarketDataField", c);
}
void generate_class_CTORATstpEffectVolumeMarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpEffectVolumeMarketDataField> c(parent, "CTORATstpEffectVolumeMarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpEffectVolumeMarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectVolumeMarketDataField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectVolumeMarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectVolumeMarketDataField, "LastPrice", LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectVolumeMarketDataField, "TotalVolume", TotalVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectVolumeMarketDataField, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectVolumeMarketDataField, "UpdateTime", UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpEffectVolumeMarketDataField, "UpdateMillisec", UpdateMillisec);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpEffectVolumeMarketDataField, c);
    module_vntora::objects.emplace("CTORATstpEffectVolumeMarketDataField", c);
}
void generate_class_CTORATstpFundsFlowMarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpFundsFlowMarketDataField> c(parent, "CTORATstpFundsFlowMarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpFundsFlowMarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "UpdateTime", UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "UpdateMillisec", UpdateMillisec);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "RetailBuyTurnover", RetailBuyTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "RetailBuyVolume", RetailBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "RetailBuyAmount", RetailBuyAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "RetailSellTurnover", RetailSellTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "RetailSellVolume", RetailSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "RetailSellAmount", RetailSellAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "MiddleBuyTurnover", MiddleBuyTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "MiddleBuyVolume", MiddleBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "MiddleBuyAmount", MiddleBuyAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "MiddleSellTurnover", MiddleSellTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "MiddleSellVolume", MiddleSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "MiddleSellAmount", MiddleSellAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "LargeBuyTurnover", LargeBuyTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "LargeBuyVolume", LargeBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "LargeBuyAmount", LargeBuyAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "LargeSellTurnover", LargeSellTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "LargeSellVolume", LargeSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "LargeSellAmount", LargeSellAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "InstitutionBuyTurnover", InstitutionBuyTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "InstitutionBuyVolume", InstitutionBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "InstitutionBuyAmount", InstitutionBuyAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "InstitutionSellTurnover", InstitutionSellTurnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "InstitutionSellVolume", InstitutionSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFundsFlowMarketDataField, "InstitutionSellAmount", InstitutionSellAmount);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpFundsFlowMarketDataField, c);
    module_vntora::objects.emplace("CTORATstpFundsFlowMarketDataField", c);
}
void generate_class_CTORATstpReqUserLoginField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpReqUserLoginField> c(parent, "CTORATstpReqUserLoginField");
    if constexpr (std::is_default_constructible_v<CTORATstpReqUserLoginField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "LogInAccount", LogInAccount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "LogInAccountType", LogInAccountType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "Password", Password);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "UserProductInfo", UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "InterfaceProductInfo", InterfaceProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "ProtocolInfo", ProtocolInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "OneTimePassword", OneTimePassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "ClientIPAddress", ClientIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "Lang", Lang);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "GWMacAddress", GWMacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "GWInnerIPAddress", GWInnerIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "GWOuterIPAddress", GWOuterIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "HDSerial", HDSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "AuthMode", AuthMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "DeviceID", DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqUserLoginField, "DeviceSerial", DeviceSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpReqUserLoginField, c);
    module_vntora::objects.emplace("CTORATstpReqUserLoginField", c);
}
void generate_class_CTORATstpRspUserLoginField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpRspUserLoginField> c(parent, "CTORATstpRspUserLoginField");
    if constexpr (std::is_default_constructible_v<CTORATstpRspUserLoginField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "LoginTime", LoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "LogInAccount", LogInAccount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "LogInAccountType", LogInAccountType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "SystemName", SystemName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "MaxOrderRef", MaxOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "PrivateFlowCount", PrivateFlowCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "PublicFlowCount", PublicFlowCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "UserName", UserName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "UserType", UserType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "ClientIPAddress", ClientIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "HDSerial", HDSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspUserLoginField, "CommFlux", CommFlux);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpRspUserLoginField, c);
    module_vntora::objects.emplace("CTORATstpRspUserLoginField", c);
}
void generate_class_CTORATstpRspInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpRspInfoField> c(parent, "CTORATstpRspInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpRspInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInfoField, "ErrorID", ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInfoField, "ErrorMsg", ErrorMsg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpRspInfoField, c);
    module_vntora::objects.emplace("CTORATstpRspInfoField", c);
}
void generate_class_CTORATstpUserLogoutField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpUserLogoutField> c(parent, "CTORATstpUserLogoutField");
    if constexpr (std::is_default_constructible_v<CTORATstpUserLogoutField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserLogoutField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpUserLogoutField, c);
    module_vntora::objects.emplace("CTORATstpUserLogoutField", c);
}
void generate_class_CTORATstpForceUserLogoutField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpForceUserLogoutField> c(parent, "CTORATstpForceUserLogoutField");
    if constexpr (std::is_default_constructible_v<CTORATstpForceUserLogoutField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpForceUserLogoutField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpForceUserLogoutField, c);
    module_vntora::objects.emplace("CTORATstpForceUserLogoutField", c);
}
void generate_class_CTORATstpUserPasswordUpdateField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpUserPasswordUpdateField> c(parent, "CTORATstpUserPasswordUpdateField");
    if constexpr (std::is_default_constructible_v<CTORATstpUserPasswordUpdateField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserPasswordUpdateField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserPasswordUpdateField, "OldPassword", OldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserPasswordUpdateField, "NewPassword", NewPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpUserPasswordUpdateField, c);
    module_vntora::objects.emplace("CTORATstpUserPasswordUpdateField", c);
}
void generate_class_CTORATstpReqInputDeviceSerialField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpReqInputDeviceSerialField> c(parent, "CTORATstpReqInputDeviceSerialField");
    if constexpr (std::is_default_constructible_v<CTORATstpReqInputDeviceSerialField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInputDeviceSerialField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInputDeviceSerialField, "DeviceID", DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInputDeviceSerialField, "DeviceSerial", DeviceSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpReqInputDeviceSerialField, c);
    module_vntora::objects.emplace("CTORATstpReqInputDeviceSerialField", c);
}
void generate_class_CTORATstpRspInputDeviceSerialField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpRspInputDeviceSerialField> c(parent, "CTORATstpRspInputDeviceSerialField");
    if constexpr (std::is_default_constructible_v<CTORATstpRspInputDeviceSerialField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInputDeviceSerialField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpRspInputDeviceSerialField, c);
    module_vntora::objects.emplace("CTORATstpRspInputDeviceSerialField", c);
}
void generate_class_CTORATstpActivateUserField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpActivateUserField> c(parent, "CTORATstpActivateUserField");
    if constexpr (std::is_default_constructible_v<CTORATstpActivateUserField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpActivateUserField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpActivateUserField, c);
    module_vntora::objects.emplace("CTORATstpActivateUserField", c);
}
void generate_class_CTORATstpVerifyUserPasswordField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpVerifyUserPasswordField> c(parent, "CTORATstpVerifyUserPasswordField");
    if constexpr (std::is_default_constructible_v<CTORATstpVerifyUserPasswordField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpVerifyUserPasswordField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpVerifyUserPasswordField, "Password", Password);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpVerifyUserPasswordField, c);
    module_vntora::objects.emplace("CTORATstpVerifyUserPasswordField", c);
}
void generate_class_CTORATstpInputOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputOrderField> c(parent, "CTORATstpInputOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "MinVolume", MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "ForceCloseReason", ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "UserForceClose", UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "IsSwapOrder", IsSwapOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "CreditPositionType", CreditPositionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "TransfereePbuID", TransfereePbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderField, "HDSerial", HDSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputOrderField, c);
    module_vntora::objects.emplace("CTORATstpInputOrderField", c);
}
void generate_class_CTORATstpOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpOrderField> c(parent, "CTORATstpOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "MinVolume", MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ForceCloseReason", ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ExchangeInstID", ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "TraderID", TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "OrderSubmitStatus", OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "OrderStatus", OrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "VolumeTraded", VolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "VolumeTotal", VolumeTotal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "CancelTime", CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ActiveTraderID", ActiveTraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "UserProductInfo", UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "UserForceClose", UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ActiveUserID", ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "CreditPositionType", CreditPositionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "TransfereePbuID", TransfereePbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ProperCtrlBusinessType", ProperCtrlBusinessType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "ProperCtrlPassFlag", ProperCtrlPassFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "IsCacheOrder", IsCacheOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "RtnFloatInfo", RtnFloatInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderField, "RtnIntInfo", RtnIntInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpOrderField, c);
    module_vntora::objects.emplace("CTORATstpOrderField", c);
}
void generate_class_CTORATstpUserRefField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpUserRefField> c(parent, "CTORATstpUserRefField");
    if constexpr (std::is_default_constructible_v<CTORATstpUserRefField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserRefField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpUserRefField, c);
    module_vntora::objects.emplace("CTORATstpUserRefField", c);
}
void generate_class_CTORATstpInputOrderActionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputOrderActionField> c(parent, "CTORATstpInputOrderActionField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputOrderActionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "OrderActionRef", OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "ActionFlag", ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "VolumeChange", VolumeChange);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "CancelOrderLocalID", CancelOrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputOrderActionField, "HDSerial", HDSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputOrderActionField, c);
    module_vntora::objects.emplace("CTORATstpInputOrderActionField", c);
}
void generate_class_CTORATstpOrderActionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpOrderActionField> c(parent, "CTORATstpOrderActionField");
    if constexpr (std::is_default_constructible_v<CTORATstpOrderActionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "OrderActionRef", OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "ActionFlag", ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "VolumeChange", VolumeChange);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "ActionDate", ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "ActionTime", ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "TraderID", TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "ActionLocalID", ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "OrderActionStatus", OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpOrderActionField, "Operway", Operway);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpOrderActionField, c);
    module_vntora::objects.emplace("CTORATstpOrderActionField", c);
}
void generate_class_CTORATstpTradeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpTradeField> c(parent, "CTORATstpTradeField");
    if constexpr (std::is_default_constructible_v<CTORATstpTradeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "TradeID", TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "ExchangeInstID", ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "OffsetFlag", OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "TradeDate", TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "TradeTime", TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "TraderID", TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradeField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpTradeField, c);
    module_vntora::objects.emplace("CTORATstpTradeField", c);
}
void generate_class_CTORATstpMarketStatusField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpMarketStatusField> c(parent, "CTORATstpMarketStatusField");
    if constexpr (std::is_default_constructible_v<CTORATstpMarketStatusField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketStatusField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketStatusField, "MarketStatus", MarketStatus);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpMarketStatusField, c);
    module_vntora::objects.emplace("CTORATstpMarketStatusField", c);
}
void generate_class_CTORATstpInputCondOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputCondOrderField> c(parent, "CTORATstpInputCondOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputCondOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "OrderVolumeType", OrderVolumeType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "CondOrderRef", CondOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "CondOrderID", CondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "ContingentCondition", ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "ConditionPrice", ConditionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "PriceTicks", PriceTicks);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "VolumeMultiple", VolumeMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "RelativeFrontID", RelativeFrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "RelativeSessionID", RelativeSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "RelativeParam", RelativeParam);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "AppendContingentCondition", AppendContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "AppendConditionPrice", AppendConditionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "AppendRelativeFrontID", AppendRelativeFrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "AppendRelativeSessionID", AppendRelativeSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "AppendRelativeParam", AppendRelativeParam);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderField, "HDSerial", HDSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputCondOrderField, c);
    module_vntora::objects.emplace("CTORATstpInputCondOrderField", c);
}
void generate_class_CTORATstpConditionOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpConditionOrderField> c(parent, "CTORATstpConditionOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpConditionOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "OrderVolumeType", OrderVolumeType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CondOrderRef", CondOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CondOrderID", CondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ContingentCondition", ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ConditionPrice", ConditionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "PriceTicks", PriceTicks);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "VolumeMultiple", VolumeMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "RelativeFrontID", RelativeFrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "RelativeSessionID", RelativeSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "RelativeParam", RelativeParam);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "AppendContingentCondition", AppendContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "AppendConditionPrice", AppendConditionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "AppendRelativeFrontID", AppendRelativeFrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "AppendRelativeSessionID", AppendRelativeSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "AppendRelativeParam", AppendRelativeParam);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CondOrderStatus", CondOrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CancelTime", CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "CancelUser", CancelUser);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "UserProductInfo", UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ProperCtrlBusinessType", ProperCtrlBusinessType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ProperCtrlPassFlag", ProperCtrlPassFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ActiveDate", ActiveDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConditionOrderField, "ActiveTime", ActiveTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpConditionOrderField, c);
    module_vntora::objects.emplace("CTORATstpConditionOrderField", c);
}
