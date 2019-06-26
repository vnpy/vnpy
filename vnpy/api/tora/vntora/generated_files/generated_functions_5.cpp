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


void generate_class_CTORATstpQryConversionBondInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryConversionBondInfoField> c(parent, "CTORATstpQryConversionBondInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryConversionBondInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryConversionBondInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryConversionBondInfoField, "SecurityID", SecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryConversionBondInfoField, c);
    module_vntora::objects.emplace("CTORATstpQryConversionBondInfoField", c);
}
void generate_class_CTORATstpConversionBondInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpConversionBondInfoField> c(parent, "CTORATstpConversionBondInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpConversionBondInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "ConvertOrderID", ConvertOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "ConvertPrice", ConvertPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "ConvertVolUnit", ConvertVolUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "ConvertVolMax", ConvertVolMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "ConvertVolMin", ConvertVolMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpConversionBondInfoField, "IsSupportCancel", IsSupportCancel);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpConversionBondInfoField, c);
    module_vntora::objects.emplace("CTORATstpConversionBondInfoField", c);
}
void generate_class_CTORATstpQryBondPutbackInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryBondPutbackInfoField> c(parent, "CTORATstpQryBondPutbackInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryBondPutbackInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBondPutbackInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBondPutbackInfoField, "SecurityID", SecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryBondPutbackInfoField, c);
    module_vntora::objects.emplace("CTORATstpQryBondPutbackInfoField", c);
}
void generate_class_CTORATstpBondPutbackInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpBondPutbackInfoField> c(parent, "CTORATstpBondPutbackInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpBondPutbackInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "PutbackOrderID", PutbackOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "PutbackPrice", PutbackPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "PutbackVolUnit", PutbackVolUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "PutbackVolMax", PutbackVolMax);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "PutbackVolMin", PutbackVolMin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBondPutbackInfoField, "IsSupportCancel", IsSupportCancel);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpBondPutbackInfoField, c);
    module_vntora::objects.emplace("CTORATstpBondPutbackInfoField", c);
}
void generate_class_CTORATstpQryStandardBondPositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryStandardBondPositionField> c(parent, "CTORATstpQryStandardBondPositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryStandardBondPositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryStandardBondPositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryStandardBondPositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryStandardBondPositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryStandardBondPositionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryStandardBondPositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryStandardBondPositionField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryStandardBondPositionField, c);
    module_vntora::objects.emplace("CTORATstpQryStandardBondPositionField", c);
}
void generate_class_CTORATstpStandardBondPositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpStandardBondPositionField> c(parent, "CTORATstpStandardBondPositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpStandardBondPositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "AvailablePosition", AvailablePosition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "AvailablePosFrozen", AvailablePosFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpStandardBondPositionField, "TotalPosition", TotalPosition);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpStandardBondPositionField, c);
    module_vntora::objects.emplace("CTORATstpStandardBondPositionField", c);
}
void generate_class_CTORATstpQryDesignationRegistrationField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryDesignationRegistrationField> c(parent, "CTORATstpQryDesignationRegistrationField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryDesignationRegistrationField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryDesignationRegistrationField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryDesignationRegistrationField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryDesignationRegistrationField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryDesignationRegistrationField, "InsertTimeStart", InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryDesignationRegistrationField, "InsertTimeEnd", InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryDesignationRegistrationField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryDesignationRegistrationField, c);
    module_vntora::objects.emplace("CTORATstpQryDesignationRegistrationField", c);
}
void generate_class_CTORATstpDesignationRegistrationField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpDesignationRegistrationField> c(parent, "CTORATstpDesignationRegistrationField");
    if constexpr (std::is_default_constructible_v<CTORATstpDesignationRegistrationField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "DesignationType", DesignationType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "PbuID", PbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "OrderSubmitStatus", OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "OrderStatus", OrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDesignationRegistrationField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpDesignationRegistrationField, c);
    module_vntora::objects.emplace("CTORATstpDesignationRegistrationField", c);
}
void generate_class_CTORATstpQryCustodyTransferField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryCustodyTransferField> c(parent, "CTORATstpQryCustodyTransferField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryCustodyTransferField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCustodyTransferField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCustodyTransferField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCustodyTransferField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCustodyTransferField, "InsertTimeStart", InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCustodyTransferField, "InsertTimeEnd", InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCustodyTransferField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCustodyTransferField, "SecurityID", SecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryCustodyTransferField, c);
    module_vntora::objects.emplace("CTORATstpQryCustodyTransferField", c);
}
void generate_class_CTORATstpCustodyTransferField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpCustodyTransferField> c(parent, "CTORATstpCustodyTransferField");
    if constexpr (std::is_default_constructible_v<CTORATstpCustodyTransferField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "CustodyTransferType", CustodyTransferType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "PbuID", PbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "OrderSubmitStatus", OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "OrderStatus", OrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "TransfereePbuID", TransfereePbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "OrignalOrderLocalID", OrignalOrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "CancelTime", CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "ActiveTraderID", ActiveTraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCustodyTransferField, "ActiveUserID", ActiveUserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpCustodyTransferField, c);
    module_vntora::objects.emplace("CTORATstpCustodyTransferField", c);
}
void generate_class_CTORATstpQrySpecialMarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQrySpecialMarketDataField> c(parent, "CTORATstpQrySpecialMarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpQrySpecialMarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQrySpecialMarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQrySpecialMarketDataField, "ExchangeID", ExchangeID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQrySpecialMarketDataField, c);
    module_vntora::objects.emplace("CTORATstpQrySpecialMarketDataField", c);
}
void generate_class_CTORATstpSpecialMarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpSpecialMarketDataField> c(parent, "CTORATstpSpecialMarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpSpecialMarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "MovingAvgPrice", MovingAvgPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "MovingAvgPriceSamplingNum", MovingAvgPriceSamplingNum);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "UpdateTime", UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecialMarketDataField, "UpdateMillisec", UpdateMillisec);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpSpecialMarketDataField, c);
    module_vntora::objects.emplace("CTORATstpSpecialMarketDataField", c);
}
void generate_class_CTORATstpQryPrematurityRepoOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryPrematurityRepoOrderField> c(parent, "CTORATstpQryPrematurityRepoOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryPrematurityRepoOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPrematurityRepoOrderField, "TradeID", TradeID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryPrematurityRepoOrderField, c);
    module_vntora::objects.emplace("CTORATstpQryPrematurityRepoOrderField", c);
}
void generate_class_CTORATstpPrematurityRepoOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpPrematurityRepoOrderField> c(parent, "CTORATstpPrematurityRepoOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpPrematurityRepoOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "TradeDay", TradeDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "ExpireDay", ExpireDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "VolumeTraded", VolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "TradeID", TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "RepoTotalMoney", RepoTotalMoney);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPrematurityRepoOrderField, "InterestAmount", InterestAmount);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpPrematurityRepoOrderField, c);
    module_vntora::objects.emplace("CTORATstpPrematurityRepoOrderField", c);
}
void generate_class_CTORATstpQryShareholderParamField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryShareholderParamField> c(parent, "CTORATstpQryShareholderParamField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryShareholderParamField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "TradingCodeClass", TradingCodeClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "ParamType", ParamType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryShareholderParamField, "ExchangeID", ExchangeID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryShareholderParamField, c);
    module_vntora::objects.emplace("CTORATstpQryShareholderParamField", c);
}
void generate_class_CTORATstpShareholderParamField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpShareholderParamField> c(parent, "CTORATstpShareholderParamField");
    if constexpr (std::is_default_constructible_v<CTORATstpShareholderParamField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "TradingCodeClass", TradingCodeClass);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "ParamType", ParamType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpShareholderParamField, "ParamValue", ParamValue);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpShareholderParamField, c);
    module_vntora::objects.emplace("CTORATstpShareholderParamField", c);
}
void generate_class_CTORATstpQryPeripheryPositionTransferDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryPeripheryPositionTransferDetailField> c(parent, "CTORATstpQryPeripheryPositionTransferDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryPeripheryPositionTransferDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPeripheryPositionTransferDetailField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPeripheryPositionTransferDetailField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPeripheryPositionTransferDetailField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPeripheryPositionTransferDetailField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPeripheryPositionTransferDetailField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryPeripheryPositionTransferDetailField, c);
    module_vntora::objects.emplace("CTORATstpQryPeripheryPositionTransferDetailField", c);
}
void generate_class_CTORATstpQryInvestorCondOrderLimitParamField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryInvestorCondOrderLimitParamField> c(parent, "CTORATstpQryInvestorCondOrderLimitParamField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryInvestorCondOrderLimitParamField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryInvestorCondOrderLimitParamField, "InvestorID", InvestorID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryInvestorCondOrderLimitParamField, c);
    module_vntora::objects.emplace("CTORATstpQryInvestorCondOrderLimitParamField", c);
}
void generate_class_CTORATstpInvestorCondOrderLimitParamField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInvestorCondOrderLimitParamField> c(parent, "CTORATstpInvestorCondOrderLimitParamField");
    if constexpr (std::is_default_constructible_v<CTORATstpInvestorCondOrderLimitParamField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorCondOrderLimitParamField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorCondOrderLimitParamField, "MaxCondOrderLimitCnt", MaxCondOrderLimitCnt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInvestorCondOrderLimitParamField, "CurrCondOrderCnt", CurrCondOrderCnt);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInvestorCondOrderLimitParamField, c);
    module_vntora::objects.emplace("CTORATstpInvestorCondOrderLimitParamField", c);
}
void generate_class_CTORATstpQryCondOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryCondOrderField> c(parent, "CTORATstpQryCondOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryCondOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "CondOrderID", CondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "InsertTimeStart", InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "InsertTimeEnd", InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderField, "IInfo", IInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryCondOrderField, c);
    module_vntora::objects.emplace("CTORATstpQryCondOrderField", c);
}
void generate_class_CTORATstpCondOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpCondOrderField> c(parent, "CTORATstpCondOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpCondOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "OrderVolumeType", OrderVolumeType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CondOrderRef", CondOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CondOrderID", CondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ContingentCondition", ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ConditionPrice", ConditionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "PriceTicks", PriceTicks);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "VolumeMultiple", VolumeMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "RelativeFrontID", RelativeFrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "RelativeSessionID", RelativeSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "RelativeParam", RelativeParam);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "AppendContingentCondition", AppendContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "AppendConditionPrice", AppendConditionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "AppendRelativeFrontID", AppendRelativeFrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "AppendRelativeSessionID", AppendRelativeSessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "AppendRelativeParam", AppendRelativeParam);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CondOrderStatus", CondOrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CancelTime", CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "CancelUser", CancelUser);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "UserProductInfo", UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ProperCtrlBusinessType", ProperCtrlBusinessType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ProperCtrlPassFlag", ProperCtrlPassFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ActiveDate", ActiveDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderField, "ActiveTime", ActiveTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpCondOrderField, c);
    module_vntora::objects.emplace("CTORATstpCondOrderField", c);
}
void generate_class_CTORATstpQryCondOrderActionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryCondOrderActionField> c(parent, "CTORATstpQryCondOrderActionField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryCondOrderActionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderActionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderActionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderActionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderActionField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderActionField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryCondOrderActionField, "IInfo", IInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryCondOrderActionField, c);
    module_vntora::objects.emplace("CTORATstpQryCondOrderActionField", c);
}
void generate_class_CTORATstpCondOrderActionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpCondOrderActionField> c(parent, "CTORATstpCondOrderActionField");
    if constexpr (std::is_default_constructible_v<CTORATstpCondOrderActionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "CondOrderActionRef", CondOrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "CondOrderRef", CondOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "CondOrderID", CondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "ActionFlag", ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "CancelCondOrderID", CancelCondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "ActionDate", ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCondOrderActionField, "ActionTime", ActionTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpCondOrderActionField, c);
    module_vntora::objects.emplace("CTORATstpCondOrderActionField", c);
}
void generate_class_CTORATstpQryBrokerUserRoleField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryBrokerUserRoleField> c(parent, "CTORATstpQryBrokerUserRoleField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryBrokerUserRoleField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBrokerUserRoleField, "RoleID", RoleID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryBrokerUserRoleField, c);
    module_vntora::objects.emplace("CTORATstpQryBrokerUserRoleField", c);
}
void generate_class_CTORATstpBrokerUserRoleField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpBrokerUserRoleField> c(parent, "CTORATstpBrokerUserRoleField");
    if constexpr (std::is_default_constructible_v<CTORATstpBrokerUserRoleField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserRoleField, "RoleID", RoleID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserRoleField, "RoleDescription", RoleDescription);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserRoleField, "Functions", Functions);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpBrokerUserRoleField, c);
    module_vntora::objects.emplace("CTORATstpBrokerUserRoleField", c);
}
void generate_class_CTORATstpQryBrokerUserRoleAssignmentField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryBrokerUserRoleAssignmentField> c(parent, "CTORATstpQryBrokerUserRoleAssignmentField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryBrokerUserRoleAssignmentField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBrokerUserRoleAssignmentField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryBrokerUserRoleAssignmentField, c);
    module_vntora::objects.emplace("CTORATstpQryBrokerUserRoleAssignmentField", c);
}
void generate_class_CTORATstpBrokerUserRoleAssignmentField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpBrokerUserRoleAssignmentField> c(parent, "CTORATstpBrokerUserRoleAssignmentField");
    if constexpr (std::is_default_constructible_v<CTORATstpBrokerUserRoleAssignmentField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserRoleAssignmentField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserRoleAssignmentField, "RoleID", RoleID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserRoleAssignmentField, "RoleDescription", RoleDescription);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpBrokerUserRoleAssignmentField, c);
    module_vntora::objects.emplace("CTORATstpBrokerUserRoleAssignmentField", c);
}
void generate_class_CTORATstpQryTradingNoticeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryTradingNoticeField> c(parent, "CTORATstpQryTradingNoticeField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryTradingNoticeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingNoticeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingNoticeField, "InsertDateStart", InsertDateStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingNoticeField, "InsertDateEnd", InsertDateEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingNoticeField, "InsertTimeStart", InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryTradingNoticeField, "InsertTimeEnd", InsertTimeEnd);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryTradingNoticeField, c);
    module_vntora::objects.emplace("CTORATstpQryTradingNoticeField", c);
}
void generate_class_CTORATstpQryIPONumberResultField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryIPONumberResultField> c(parent, "CTORATstpQryIPONumberResultField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryIPONumberResultField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPONumberResultField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPONumberResultField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPONumberResultField, "ShareholderID", ShareholderID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryIPONumberResultField, c);
    module_vntora::objects.emplace("CTORATstpQryIPONumberResultField", c);
}
void generate_class_CTORATstpIPONumberResultField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpIPONumberResultField> c(parent, "CTORATstpIPONumberResultField");
    if constexpr (std::is_default_constructible_v<CTORATstpIPONumberResultField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "Day", Day);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "BeginNumberID", BeginNumberID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPONumberResultField, "Volume", Volume);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpIPONumberResultField, c);
    module_vntora::objects.emplace("CTORATstpIPONumberResultField", c);
}
void generate_class_CTORATstpQryIPOMatchNumberResultField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryIPOMatchNumberResultField> c(parent, "CTORATstpQryIPOMatchNumberResultField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryIPOMatchNumberResultField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOMatchNumberResultField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOMatchNumberResultField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOMatchNumberResultField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOMatchNumberResultField, "MatchNumberID", MatchNumberID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryIPOMatchNumberResultField, c);
    module_vntora::objects.emplace("CTORATstpQryIPOMatchNumberResultField", c);
}
void generate_class_CTORATstpIPOMatchNumberResultField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpIPOMatchNumberResultField> c(parent, "CTORATstpIPOMatchNumberResultField");
    if constexpr (std::is_default_constructible_v<CTORATstpIPOMatchNumberResultField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "Day", Day);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "MatchNumberID", MatchNumberID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOMatchNumberResultField, "Amout", Amout);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpIPOMatchNumberResultField, c);
    module_vntora::objects.emplace("CTORATstpIPOMatchNumberResultField", c);
}
