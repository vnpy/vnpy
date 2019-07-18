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


void generate_class_CTORATstpReqInquiryMaxOrderVolumeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpReqInquiryMaxOrderVolumeField> c(parent, "CTORATstpReqInquiryMaxOrderVolumeField");
    if constexpr (std::is_default_constructible_v<CTORATstpReqInquiryMaxOrderVolumeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "TransfereePbuID", TransfereePbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, "MaxVolume", MaxVolume);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpReqInquiryMaxOrderVolumeField, c);
    module_vntora::objects.emplace("CTORATstpReqInquiryMaxOrderVolumeField", c);
}
void generate_class_CTORATstpRspInquiryMaxOrderVolumeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpRspInquiryMaxOrderVolumeField> c(parent, "CTORATstpRspInquiryMaxOrderVolumeField");
    if constexpr (std::is_default_constructible_v<CTORATstpRspInquiryMaxOrderVolumeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "TransfereePbuID", TransfereePbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, "MaxVolume", MaxVolume);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpRspInquiryMaxOrderVolumeField, c);
    module_vntora::objects.emplace("CTORATstpRspInquiryMaxOrderVolumeField", c);
}
void generate_class_CTORATstpPeripheryPositionTransferDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpPeripheryPositionTransferDetailField> c(parent, "CTORATstpPeripheryPositionTransferDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpPeripheryPositionTransferDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "PositionSerial", PositionSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "TodayBSPos", TodayBSPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "TodayPRPos", TodayPRPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "HistoryPos", HistoryPos);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "TransferReason", TransferReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "TransferStatus", TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "OperateDate", OperateDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "RepealDate", RepealDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "RepealTime", RepealTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "RepealReason", RepealReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, "StatusMsg", StatusMsg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpPeripheryPositionTransferDetailField, c);
    module_vntora::objects.emplace("CTORATstpPeripheryPositionTransferDetailField", c);
}
void generate_class_CTORATstpQryHistoryOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryHistoryOrderField> c(parent, "CTORATstpQryHistoryOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryHistoryOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryOrderField, "BegDate", BegDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryOrderField, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryOrderField, "PageCount", PageCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryOrderField, "PageLocate", PageLocate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryHistoryOrderField, c);
    module_vntora::objects.emplace("CTORATstpQryHistoryOrderField", c);
}
void generate_class_CTORATstpQryHistoryRspInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryHistoryRspInfoField> c(parent, "CTORATstpQryHistoryRspInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryHistoryRspInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryRspInfoField, "ErrorID", ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryRspInfoField, "ErrorMsg", ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryRspInfoField, "bPageEnd", bPageEnd);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryHistoryRspInfoField, c);
    module_vntora::objects.emplace("CTORATstpQryHistoryRspInfoField", c);
}
void generate_class_CTORATstpHistoryOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpHistoryOrderField> c(parent, "CTORATstpHistoryOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpHistoryOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "OrderPriceType", OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "CombOffsetFlag", CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "CombHedgeFlag", CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "TimeCondition", TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "VolumeCondition", VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "MinVolume", MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ForceCloseReason", ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ExchangeInstID", ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "TraderID", TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "OrderSubmitStatus", OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "OrderStatus", OrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "VolumeTraded", VolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "VolumeTotal", VolumeTotal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "CancelTime", CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ActiveTraderID", ActiveTraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "UserProductInfo", UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "UserForceClose", UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ActiveUserID", ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "CreditPositionType", CreditPositionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "TransfereePbuID", TransfereePbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ProperCtrlBusinessType", ProperCtrlBusinessType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "ProperCtrlPassFlag", ProperCtrlPassFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "IsCacheOrder", IsCacheOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "RtnFloatInfo", RtnFloatInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "RtnIntInfo", RtnIntInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryOrderField, "PageLocate", PageLocate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpHistoryOrderField, c);
    module_vntora::objects.emplace("CTORATstpHistoryOrderField", c);
}
void generate_class_CTORATstpQryHistoryTradeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryHistoryTradeField> c(parent, "CTORATstpQryHistoryTradeField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryHistoryTradeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryTradeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryTradeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryTradeField, "BegDate", BegDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryTradeField, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryTradeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryTradeField, "PageCount", PageCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryHistoryTradeField, "PageLocate", PageLocate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryHistoryTradeField, c);
    module_vntora::objects.emplace("CTORATstpQryHistoryTradeField", c);
}
void generate_class_CTORATstpHistoryTradeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpHistoryTradeField> c(parent, "CTORATstpHistoryTradeField");
    if constexpr (std::is_default_constructible_v<CTORATstpHistoryTradeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "TradeID", TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "ExchangeInstID", ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "OffsetFlag", OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "TradeDate", TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "TradeTime", TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "TraderID", TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpHistoryTradeField, "PageLocate", PageLocate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpHistoryTradeField, c);
    module_vntora::objects.emplace("CTORATstpHistoryTradeField", c);
}
void generate_class_CTORATstpQryExchangeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryExchangeField> c(parent, "CTORATstpQryExchangeField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryExchangeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryExchangeField, "ExchangeID", ExchangeID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryExchangeField, c);
    module_vntora::objects.emplace("CTORATstpQryExchangeField", c);
}
void generate_class_CTORATstpExchangeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpExchangeField> c(parent, "CTORATstpExchangeField");
    if constexpr (std::is_default_constructible_v<CTORATstpExchangeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpExchangeField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpExchangeField, "ExchangeName", ExchangeName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpExchangeField, "TradingDay", TradingDay);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpExchangeField, c);
    module_vntora::objects.emplace("CTORATstpExchangeField", c);
}
void generate_class_CTORATstpQryPBUField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryPBUField> c(parent, "CTORATstpQryPBUField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryPBUField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPBUField, "PbuID", PbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPBUField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryPBUField, "MarketID", MarketID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryPBUField, c);
    module_vntora::objects.emplace("CTORATstpQryPBUField", c);
}
void generate_class_CTORATstpPBUField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpPBUField> c(parent, "CTORATstpPBUField");
    if constexpr (std::is_default_constructible_v<CTORATstpPBUField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPBUField, "PbuID", PbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPBUField, "PbuName", PbuName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPBUField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpPBUField, "MarketID", MarketID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpPBUField, c);
    module_vntora::objects.emplace("CTORATstpPBUField", c);
}
void generate_class_CTORATstpQryMarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryMarketDataField> c(parent, "CTORATstpQryMarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryMarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryMarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryMarketDataField, "ExchangeID", ExchangeID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryMarketDataField, c);
    module_vntora::objects.emplace("CTORATstpQryMarketDataField", c);
}
void generate_class_CTORATstpMarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpMarketDataField> c(parent, "CTORATstpMarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpMarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "ExchangeInstID", ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "LastPrice", LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "PreClosePrice", PreClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "OpenPrice", OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "HighestPrice", HighestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "LowestPrice", LowestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "OpenInterest", OpenInterest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "UpperLimitPrice", UpperLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "LowerLimitPrice", LowerLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "UpdateTime", UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "UpdateMillisec", UpdateMillisec);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidPrice1", BidPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidVolume1", BidVolume1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskPrice1", AskPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskVolume1", AskVolume1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidPrice2", BidPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidVolume2", BidVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskPrice2", AskPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskVolume2", AskVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidPrice3", BidPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidVolume3", BidVolume3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskPrice3", AskPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskVolume3", AskVolume3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidPrice4", BidPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidVolume4", BidVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskPrice4", AskPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskVolume4", AskVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidPrice5", BidPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "BidVolume5", BidVolume5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskPrice5", AskPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "AskVolume5", AskVolume5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "TradingCount", TradingCount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "PERatio1", PERatio1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "PERatio2", PERatio2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "PriceUpDown1", PriceUpDown1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "PriceUpDown2", PriceUpDown2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "ClosePrice", ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "MDSecurityStat", MDSecurityStat);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpMarketDataField, "HWFlag", HWFlag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpMarketDataField, c);
    module_vntora::objects.emplace("CTORATstpMarketDataField", c);
}
void generate_class_CTORATstpQrySecurityField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQrySecurityField> c(parent, "CTORATstpQrySecurityField");
    if constexpr (std::is_default_constructible_v<CTORATstpQrySecurityField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQrySecurityField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQrySecurityField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQrySecurityField, "ExchangeInstID", ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQrySecurityField, "ProductID", ProductID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQrySecurityField, c);
    module_vntora::objects.emplace("CTORATstpQrySecurityField", c);
}
void generate_class_CTORATstpSecurityField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpSecurityField> c(parent, "CTORATstpSecurityField");
    if constexpr (std::is_default_constructible_v<CTORATstpSecurityField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "ExchangeInstID", ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "OrderUnit", OrderUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "BuyTradingUnit", BuyTradingUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "SellTradingUnit", SellTradingUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MaxMarketOrderBuyVolume", MaxMarketOrderBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MinMarketOrderBuyVolume", MinMarketOrderBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MaxLimitOrderBuyVolume", MaxLimitOrderBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MinLimitOrderBuyVolume", MinLimitOrderBuyVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MaxMarketOrderSellVolume", MaxMarketOrderSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MinMarketOrderSellVolume", MinMarketOrderSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MaxLimitOrderSellVolume", MaxLimitOrderSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "MinLimitOrderSellVolume", MinLimitOrderSellVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "VolumeMultiple", VolumeMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "PriceTick", PriceTick);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "OpenDate", OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "PositionType", PositionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "ParValue", ParValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "SecurityStatus", SecurityStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "BondInterest", BondInterest);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "ConversionRate", ConversionRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSecurityField, "IsCollateral", IsCollateral);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpSecurityField, c);
    module_vntora::objects.emplace("CTORATstpSecurityField", c);
}
void generate_class_CTORATstpQryETFFileField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryETFFileField> c(parent, "CTORATstpQryETFFileField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryETFFileField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryETFFileField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryETFFileField, "ETFSecurityID", ETFSecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryETFFileField, "ETFCreRedSecurityID", ETFCreRedSecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryETFFileField, c);
    module_vntora::objects.emplace("CTORATstpQryETFFileField", c);
}
void generate_class_CTORATstpETFFileField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpETFFileField> c(parent, "CTORATstpETFFileField");
    if constexpr (std::is_default_constructible_v<CTORATstpETFFileField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "ETFSecurityID", ETFSecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "ETFCreRedSecurityID", ETFCreRedSecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "CreationRedemptionUnit", CreationRedemptionUnit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "Maxcashratio", Maxcashratio);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "CreationStatus", CreationStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "RedemptionStatus", RedemptionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "EstimateCashComponent", EstimateCashComponent);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "CashComponent", CashComponent);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "NAV", NAV);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "NAVperCU", NAVperCU);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFFileField, "DividendPerCU", DividendPerCU);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpETFFileField, c);
    module_vntora::objects.emplace("CTORATstpETFFileField", c);
}
void generate_class_CTORATstpQryETFBasketField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryETFBasketField> c(parent, "CTORATstpQryETFBasketField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryETFBasketField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryETFBasketField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryETFBasketField, "ETFSecurityID", ETFSecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryETFBasketField, "SecurityID", SecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryETFBasketField, c);
    module_vntora::objects.emplace("CTORATstpQryETFBasketField", c);
}
void generate_class_CTORATstpETFBasketField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpETFBasketField> c(parent, "CTORATstpETFBasketField");
    if constexpr (std::is_default_constructible_v<CTORATstpETFBasketField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "ETFSecurityID", ETFSecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "ETFCurrenceReplaceStatus", ETFCurrenceReplaceStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "Premium", Premium);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "CreationReplaceAmount", CreationReplaceAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "RedemptionReplaceAmount", RedemptionReplaceAmount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpETFBasketField, "Market", Market);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpETFBasketField, c);
    module_vntora::objects.emplace("CTORATstpETFBasketField", c);
}
void generate_class_CTORATstpQryDepartmentInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryDepartmentInfoField> c(parent, "CTORATstpQryDepartmentInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryDepartmentInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryDepartmentInfoField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryDepartmentInfoField, c);
    module_vntora::objects.emplace("CTORATstpQryDepartmentInfoField", c);
}
void generate_class_CTORATstpDepartmentInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpDepartmentInfoField> c(parent, "CTORATstpDepartmentInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpDepartmentInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDepartmentInfoField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpDepartmentInfoField, "DepartmentName", DepartmentName);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpDepartmentInfoField, c);
    module_vntora::objects.emplace("CTORATstpDepartmentInfoField", c);
}
void generate_class_CTORATstpQryIPOInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryIPOInfoField> c(parent, "CTORATstpQryIPOInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryIPOInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryIPOInfoField, "SecurityID", SecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryIPOInfoField, c);
    module_vntora::objects.emplace("CTORATstpQryIPOInfoField", c);
}
void generate_class_CTORATstpIPOInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpIPOInfoField> c(parent, "CTORATstpIPOInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpIPOInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "ProductID", ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "SecurityType", SecurityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "OnlineLimit", OnlineLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "SecurityName", SecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "UnderlyingSecurityID", UnderlyingSecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "UnderlyingSecurityName", UnderlyingSecurityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "OnlineMinVol", OnlineMinVol);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpIPOInfoField, "OnlineVolUnit", OnlineVolUnit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpIPOInfoField, c);
    module_vntora::objects.emplace("CTORATstpIPOInfoField", c);
}
void generate_class_CTORATstpQryBrokerUserFunctionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryBrokerUserFunctionField> c(parent, "CTORATstpQryBrokerUserFunctionField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryBrokerUserFunctionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBrokerUserFunctionField, "UserID", UserID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryBrokerUserFunctionField, c);
    module_vntora::objects.emplace("CTORATstpQryBrokerUserFunctionField", c);
}
void generate_class_CTORATstpBrokerUserFunctionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpBrokerUserFunctionField> c(parent, "CTORATstpBrokerUserFunctionField");
    if constexpr (std::is_default_constructible_v<CTORATstpBrokerUserFunctionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserFunctionField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBrokerUserFunctionField, "FunctionID", FunctionID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpBrokerUserFunctionField, c);
    module_vntora::objects.emplace("CTORATstpBrokerUserFunctionField", c);
}
void generate_class_CTORATstpQryBUProxyField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryBUProxyField> c(parent, "CTORATstpQryBUProxyField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryBUProxyField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBUProxyField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBUProxyField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryBUProxyField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryBUProxyField, c);
    module_vntora::objects.emplace("CTORATstpQryBUProxyField", c);
}
void generate_class_CTORATstpBUProxyField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpBUProxyField> c(parent, "CTORATstpBUProxyField");
    if constexpr (std::is_default_constructible_v<CTORATstpBUProxyField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBUProxyField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBUProxyField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpBUProxyField, "BusinessUnitID", BusinessUnitID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpBUProxyField, c);
    module_vntora::objects.emplace("CTORATstpBUProxyField", c);
}
void generate_class_CTORATstpQryUserField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryUserField> c(parent, "CTORATstpQryUserField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryUserField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryUserField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryUserField, "UserType", UserType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryUserField, c);
    module_vntora::objects.emplace("CTORATstpQryUserField", c);
}
void generate_class_CTORATstpUserField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpUserField> c(parent, "CTORATstpUserField");
    if constexpr (std::is_default_constructible_v<CTORATstpUserField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserField, "UserName", UserName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserField, "UserType", UserType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserField, "IsActive", IsActive);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUserField, "LoginLimit", LoginLimit);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpUserField, c);
    module_vntora::objects.emplace("CTORATstpUserField", c);
}
