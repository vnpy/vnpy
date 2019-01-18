#include <iostream>
#include <string>
#include <string_view>
#include <pybind11/pybind11.h>

#include "dispatcher.h"
#include "property_helper.h"
#include "wrapper_helper.h"
#include "class_generators.h"
#include "wrappers.h"

#include "ctp/ThostFtdcTraderApi.h"


void generate_class_CThostFtdcUserPasswordUpdateField(pybind11::module &m)
{
    py::class_<CThostFtdcUserPasswordUpdateField>(m, "CThostFtdcUserPasswordUpdateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, UserID)
        .DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, OldPassword)
        .DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, NewPassword)
    ;
}
void generate_class_CThostFtdcInputOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcInputOrderField>(m, "CThostFtdcInputOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputOrderField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInputOrderField, OrderRef)
        .DEF_PROPERTY(CThostFtdcInputOrderField, UserID)
        .DEF_PROPERTY(CThostFtdcInputOrderField, OrderPriceType)
        .DEF_PROPERTY(CThostFtdcInputOrderField, Direction)
        .DEF_PROPERTY(CThostFtdcInputOrderField, CombOffsetFlag)
        .DEF_PROPERTY(CThostFtdcInputOrderField, CombHedgeFlag)
        .DEF_PROPERTY(CThostFtdcInputOrderField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcInputOrderField, VolumeTotalOriginal)
        .DEF_PROPERTY(CThostFtdcInputOrderField, TimeCondition)
        .DEF_PROPERTY(CThostFtdcInputOrderField, GTDDate)
        .DEF_PROPERTY(CThostFtdcInputOrderField, VolumeCondition)
        .DEF_PROPERTY(CThostFtdcInputOrderField, MinVolume)
        .DEF_PROPERTY(CThostFtdcInputOrderField, ContingentCondition)
        .DEF_PROPERTY(CThostFtdcInputOrderField, StopPrice)
        .DEF_PROPERTY(CThostFtdcInputOrderField, ForceCloseReason)
        .DEF_PROPERTY(CThostFtdcInputOrderField, IsAutoSuspend)
        .DEF_PROPERTY(CThostFtdcInputOrderField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcInputOrderField, RequestID)
        .DEF_PROPERTY(CThostFtdcInputOrderField, UserForceClose)
        .DEF_PROPERTY(CThostFtdcInputOrderField, IsSwapOrder)
        .DEF_PROPERTY(CThostFtdcInputOrderField, ExchangeID)
    ;
}
void generate_class_CThostFtdcOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcOrderField>(m, "CThostFtdcOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcOrderField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderRef)
        .DEF_PROPERTY(CThostFtdcOrderField, UserID)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderPriceType)
        .DEF_PROPERTY(CThostFtdcOrderField, Direction)
        .DEF_PROPERTY(CThostFtdcOrderField, CombOffsetFlag)
        .DEF_PROPERTY(CThostFtdcOrderField, CombHedgeFlag)
        .DEF_PROPERTY(CThostFtdcOrderField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcOrderField, VolumeTotalOriginal)
        .DEF_PROPERTY(CThostFtdcOrderField, TimeCondition)
        .DEF_PROPERTY(CThostFtdcOrderField, GTDDate)
        .DEF_PROPERTY(CThostFtdcOrderField, VolumeCondition)
        .DEF_PROPERTY(CThostFtdcOrderField, MinVolume)
        .DEF_PROPERTY(CThostFtdcOrderField, ContingentCondition)
        .DEF_PROPERTY(CThostFtdcOrderField, StopPrice)
        .DEF_PROPERTY(CThostFtdcOrderField, ForceCloseReason)
        .DEF_PROPERTY(CThostFtdcOrderField, IsAutoSuspend)
        .DEF_PROPERTY(CThostFtdcOrderField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcOrderField, RequestID)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcOrderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcOrderField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcOrderField, ClientID)
        .DEF_PROPERTY(CThostFtdcOrderField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcOrderField, TraderID)
        .DEF_PROPERTY(CThostFtdcOrderField, InstallID)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderSubmitStatus)
        .DEF_PROPERTY(CThostFtdcOrderField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcOrderField, TradingDay)
        .DEF_PROPERTY(CThostFtdcOrderField, SettlementID)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderSource)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderStatus)
        .DEF_PROPERTY(CThostFtdcOrderField, OrderType)
        .DEF_PROPERTY(CThostFtdcOrderField, VolumeTraded)
        .DEF_PROPERTY(CThostFtdcOrderField, VolumeTotal)
        .DEF_PROPERTY(CThostFtdcOrderField, InsertDate)
        .DEF_PROPERTY(CThostFtdcOrderField, InsertTime)
        .DEF_PROPERTY(CThostFtdcOrderField, ActiveTime)
        .DEF_PROPERTY(CThostFtdcOrderField, SuspendTime)
        .DEF_PROPERTY(CThostFtdcOrderField, UpdateTime)
        .DEF_PROPERTY(CThostFtdcOrderField, CancelTime)
        .DEF_PROPERTY(CThostFtdcOrderField, ActiveTraderID)
        .DEF_PROPERTY(CThostFtdcOrderField, ClearingPartID)
        .DEF_PROPERTY(CThostFtdcOrderField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcOrderField, FrontID)
        .DEF_PROPERTY(CThostFtdcOrderField, SessionID)
        .DEF_PROPERTY(CThostFtdcOrderField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcOrderField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcOrderField, UserForceClose)
        .DEF_PROPERTY(CThostFtdcOrderField, ActiveUserID)
        .DEF_PROPERTY(CThostFtdcOrderField, BrokerOrderSeq)
        .DEF_PROPERTY(CThostFtdcOrderField, RelativeOrderSysID)
        .DEF_PROPERTY(CThostFtdcOrderField, ZCETotalTradedVolume)
        .DEF_PROPERTY(CThostFtdcOrderField, IsSwapOrder)
        .DEF_PROPERTY(CThostFtdcOrderField, BranchID)
    ;
}
void generate_class_CThostFtdcExchangeOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeOrderField>(m, "CThostFtdcExchangeOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderPriceType)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, Direction)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, CombOffsetFlag)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, CombHedgeFlag)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeTotalOriginal)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, TimeCondition)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, GTDDate)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeCondition)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, MinVolume)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ContingentCondition)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, StopPrice)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ForceCloseReason)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, IsAutoSuspend)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, RequestID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderSubmitStatus)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, TradingDay)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, SettlementID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderSource)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderStatus)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderType)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeTraded)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeTotal)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, InsertDate)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, InsertTime)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ActiveTime)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, SuspendTime)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, UpdateTime)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, CancelTime)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ActiveTraderID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, ClearingPartID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcExchangeOrderField, BranchID)
    ;
}
void generate_class_CThostFtdcExchangeOrderInsertErrorField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeOrderInsertErrorField>(m, "CThostFtdcExchangeOrderInsertErrorField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ErrorID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ErrorMsg)
    ;
}
void generate_class_CThostFtdcInputOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcInputOrderActionField>(m, "CThostFtdcInputOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, OrderActionRef)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, OrderRef)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, VolumeChange)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, UserID)
        .DEF_PROPERTY(CThostFtdcInputOrderActionField, InstrumentID)
    ;
}
void generate_class_CThostFtdcOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcOrderActionField>(m, "CThostFtdcOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, OrderActionRef)
        .DEF_PROPERTY(CThostFtdcOrderActionField, OrderRef)
        .DEF_PROPERTY(CThostFtdcOrderActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcOrderActionField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcOrderActionField, VolumeChange)
        .DEF_PROPERTY(CThostFtdcOrderActionField, ActionDate)
        .DEF_PROPERTY(CThostFtdcOrderActionField, ActionTime)
        .DEF_PROPERTY(CThostFtdcOrderActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcOrderActionField, OrderActionStatus)
        .DEF_PROPERTY(CThostFtdcOrderActionField, UserID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcOrderActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcOrderActionField, BranchID)
    ;
}
void generate_class_CThostFtdcExchangeOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeOrderActionField>(m, "CThostFtdcExchangeOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, VolumeChange)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionDate)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionTime)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, OrderActionStatus)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, UserID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionField, BranchID)
    ;
}
void generate_class_CThostFtdcExchangeOrderActionErrorField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeOrderActionErrorField>(m, "CThostFtdcExchangeOrderActionErrorField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ErrorID)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ErrorMsg)
        .DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, BrokerID)
    ;
}
void generate_class_CThostFtdcExchangeTradeField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeTradeField>(m, "CThostFtdcExchangeTradeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, Direction)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, TradingRole)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, OffsetFlag)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, Price)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, Volume)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeDate)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeTime)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeType)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, PriceSource)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, ClearingPartID)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeSource)
    ;
}
void generate_class_CThostFtdcTradeField(pybind11::module &m)
{
    py::class_<CThostFtdcTradeField>(m, "CThostFtdcTradeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcTradeField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcTradeField, OrderRef)
        .DEF_PROPERTY(CThostFtdcTradeField, UserID)
        .DEF_PROPERTY(CThostFtdcTradeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcTradeField, TradeID)
        .DEF_PROPERTY(CThostFtdcTradeField, Direction)
        .DEF_PROPERTY(CThostFtdcTradeField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcTradeField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcTradeField, ClientID)
        .DEF_PROPERTY(CThostFtdcTradeField, TradingRole)
        .DEF_PROPERTY(CThostFtdcTradeField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcTradeField, OffsetFlag)
        .DEF_PROPERTY(CThostFtdcTradeField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcTradeField, Price)
        .DEF_PROPERTY(CThostFtdcTradeField, Volume)
        .DEF_PROPERTY(CThostFtdcTradeField, TradeDate)
        .DEF_PROPERTY(CThostFtdcTradeField, TradeTime)
        .DEF_PROPERTY(CThostFtdcTradeField, TradeType)
        .DEF_PROPERTY(CThostFtdcTradeField, PriceSource)
        .DEF_PROPERTY(CThostFtdcTradeField, TraderID)
        .DEF_PROPERTY(CThostFtdcTradeField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcTradeField, ClearingPartID)
        .DEF_PROPERTY(CThostFtdcTradeField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcTradeField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcTradeField, TradingDay)
        .DEF_PROPERTY(CThostFtdcTradeField, SettlementID)
        .DEF_PROPERTY(CThostFtdcTradeField, BrokerOrderSeq)
        .DEF_PROPERTY(CThostFtdcTradeField, TradeSource)
    ;
}
void generate_class_CThostFtdcUserSessionField(pybind11::module &m)
{
    py::class_<CThostFtdcUserSessionField>(m, "CThostFtdcUserSessionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcUserSessionField, FrontID)
        .DEF_PROPERTY(CThostFtdcUserSessionField, SessionID)
        .DEF_PROPERTY(CThostFtdcUserSessionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcUserSessionField, UserID)
        .DEF_PROPERTY(CThostFtdcUserSessionField, LoginDate)
        .DEF_PROPERTY(CThostFtdcUserSessionField, LoginTime)
        .DEF_PROPERTY(CThostFtdcUserSessionField, IPAddress)
        .DEF_PROPERTY(CThostFtdcUserSessionField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcUserSessionField, InterfaceProductInfo)
        .DEF_PROPERTY(CThostFtdcUserSessionField, ProtocolInfo)
        .DEF_PROPERTY(CThostFtdcUserSessionField, MacAddress)
    ;
}
void generate_class_CThostFtdcQueryMaxOrderVolumeField(pybind11::module &m)
{
    py::class_<CThostFtdcQueryMaxOrderVolumeField>(m, "CThostFtdcQueryMaxOrderVolumeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, Direction)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, OffsetFlag)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, MaxVolume)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, ExchangeID)
    ;
}
void generate_class_CThostFtdcSettlementInfoConfirmField(pybind11::module &m)
{
    py::class_<CThostFtdcSettlementInfoConfirmField>(m, "CThostFtdcSettlementInfoConfirmField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, ConfirmDate)
        .DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, ConfirmTime)
    ;
}
void generate_class_CThostFtdcSyncDepositField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncDepositField>(m, "CThostFtdcSyncDepositField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncDepositField, DepositSeqNo)
        .DEF_PROPERTY(CThostFtdcSyncDepositField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncDepositField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncDepositField, Deposit)
        .DEF_PROPERTY(CThostFtdcSyncDepositField, IsForce)
        .DEF_PROPERTY(CThostFtdcSyncDepositField, CurrencyID)
    ;
}
void generate_class_CThostFtdcSyncFundMortgageField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncFundMortgageField>(m, "CThostFtdcSyncFundMortgageField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncFundMortgageField, MortgageSeqNo)
        .DEF_PROPERTY(CThostFtdcSyncFundMortgageField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncFundMortgageField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncFundMortgageField, FromCurrencyID)
        .DEF_PROPERTY(CThostFtdcSyncFundMortgageField, MortgageAmount)
        .DEF_PROPERTY(CThostFtdcSyncFundMortgageField, ToCurrencyID)
    ;
}
void generate_class_CThostFtdcBrokerSyncField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerSyncField>(m, "CThostFtdcBrokerSyncField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerSyncField, BrokerID)
    ;
}
void generate_class_CThostFtdcSyncingInvestorField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingInvestorField>(m, "CThostFtdcSyncingInvestorField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, InvestorGroupID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, InvestorName)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, IdentifiedCardType)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, IdentifiedCardNo)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, IsActive)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, Telephone)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, Address)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, OpenDate)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, Mobile)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, CommModelID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorField, MarginModelID)
    ;
}
void generate_class_CThostFtdcSyncingTradingCodeField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingTradingCodeField>(m, "CThostFtdcSyncingTradingCodeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, ClientID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, IsActive)
        .DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, ClientIDType)
        .DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, BranchID)
    ;
}
void generate_class_CThostFtdcSyncingInvestorGroupField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingInvestorGroupField>(m, "CThostFtdcSyncingInvestorGroupField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingInvestorGroupField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorGroupField, InvestorGroupID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorGroupField, InvestorGroupName)
    ;
}
void generate_class_CThostFtdcSyncingTradingAccountField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingTradingAccountField>(m, "CThostFtdcSyncingTradingAccountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, AccountID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreMortgage)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreCredit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreDeposit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreBalance)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, InterestBase)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Interest)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Deposit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Withdraw)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FrozenMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FrozenCash)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FrozenCommission)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CurrMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CashIn)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Commission)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CloseProfit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PositionProfit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Balance)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Available)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, WithdrawQuota)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Reserve)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, TradingDay)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SettlementID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Credit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Mortgage)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, ExchangeMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, DeliveryMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, ExchangeDeliveryMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, ReserveBalance)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreFundMortgageIn)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreFundMortgageOut)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FundMortgageIn)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FundMortgageOut)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FundMortgageAvailable)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, MortgageableFund)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductFrozenMargin)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductCommission)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductFrozenCommission)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductPositionProfit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductCloseProfit)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductPositionProfitByAlg)
        .DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductExchangeMargin)
    ;
}
void generate_class_CThostFtdcSyncingInvestorPositionField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingInvestorPositionField>(m, "CThostFtdcSyncingInvestorPositionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PosiDirection)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PositionDate)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, YdPosition)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, Position)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, LongFrozen)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ShortFrozen)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, LongFrozenAmount)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ShortFrozenAmount)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, OpenVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, OpenAmount)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseAmount)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PositionCost)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PreMargin)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, UseMargin)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, FrozenMargin)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, FrozenCash)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, FrozenCommission)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CashIn)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, Commission)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseProfit)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PositionProfit)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PreSettlementPrice)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, SettlementPrice)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, TradingDay)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, SettlementID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, OpenCost)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ExchangeMargin)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CombPosition)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CombLongFrozen)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CombShortFrozen)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseProfitByDate)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseProfitByTrade)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, TodayPosition)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, MarginRateByMoney)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, MarginRateByVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, StrikeFrozen)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, StrikeFrozenAmount)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, AbandonFrozen)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, YdStrikeFrozen)
    ;
}
void generate_class_CThostFtdcSyncingInstrumentMarginRateField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingInstrumentMarginRateField>(m, "CThostFtdcSyncingInstrumentMarginRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, LongMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, LongMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, ShortMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, ShortMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, IsRelative)
    ;
}
void generate_class_CThostFtdcSyncingInstrumentCommissionRateField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingInstrumentCommissionRateField>(m, "CThostFtdcSyncingInstrumentCommissionRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, OpenRatioByMoney)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, OpenRatioByVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseRatioByMoney)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseRatioByVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseTodayRatioByMoney)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseTodayRatioByVolume)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, ExchangeID)
    ;
}
void generate_class_CThostFtdcSyncingInstrumentTradingRightField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncingInstrumentTradingRightField>(m, "CThostFtdcSyncingInstrumentTradingRightField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, TradingRight)
        .DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcQryOrderField>(m, "CThostFtdcQryOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryOrderField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryOrderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryOrderField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcQryOrderField, InsertTimeStart)
        .DEF_PROPERTY(CThostFtdcQryOrderField, InsertTimeEnd)
    ;
}
void generate_class_CThostFtdcQryTradeField(pybind11::module &m)
{
    py::class_<CThostFtdcQryTradeField>(m, "CThostFtdcQryTradeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryTradeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryTradeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryTradeField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryTradeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryTradeField, TradeID)
        .DEF_PROPERTY(CThostFtdcQryTradeField, TradeTimeStart)
        .DEF_PROPERTY(CThostFtdcQryTradeField, TradeTimeEnd)
    ;
}
void generate_class_CThostFtdcQryInvestorPositionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInvestorPositionField>(m, "CThostFtdcQryInvestorPositionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryTradingAccountField(pybind11::module &m)
{
    py::class_<CThostFtdcQryTradingAccountField>(m, "CThostFtdcQryTradingAccountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryTradingAccountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryTradingAccountField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryTradingAccountField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcQryTradingAccountField, BizType)
    ;
}
void generate_class_CThostFtdcQryInvestorField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInvestorField>(m, "CThostFtdcQryInvestorField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInvestorField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInvestorField, InvestorID)
    ;
}
void generate_class_CThostFtdcQryTradingCodeField(pybind11::module &m)
{
    py::class_<CThostFtdcQryTradingCodeField>(m, "CThostFtdcQryTradingCodeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryTradingCodeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryTradingCodeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryTradingCodeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryTradingCodeField, ClientID)
        .DEF_PROPERTY(CThostFtdcQryTradingCodeField, ClientIDType)
    ;
}
void generate_class_CThostFtdcQryInvestorGroupField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInvestorGroupField>(m, "CThostFtdcQryInvestorGroupField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInvestorGroupField, BrokerID)
    ;
}
void generate_class_CThostFtdcQryInstrumentMarginRateField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInstrumentMarginRateField>(m, "CThostFtdcQryInstrumentMarginRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, HedgeFlag)
    ;
}
void generate_class_CThostFtdcQryInstrumentCommissionRateField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInstrumentCommissionRateField>(m, "CThostFtdcQryInstrumentCommissionRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryInstrumentTradingRightField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInstrumentTradingRightField>(m, "CThostFtdcQryInstrumentTradingRightField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInstrumentTradingRightField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentTradingRightField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentTradingRightField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentTradingRightField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryBrokerField(pybind11::module &m)
{
    py::class_<CThostFtdcQryBrokerField>(m, "CThostFtdcQryBrokerField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryBrokerField, BrokerID)
    ;
}
void generate_class_CThostFtdcQryTraderField(pybind11::module &m)
{
    py::class_<CThostFtdcQryTraderField>(m, "CThostFtdcQryTraderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryTraderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryTraderField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcQryTraderField, TraderID)
    ;
}
void generate_class_CThostFtdcQrySuperUserFunctionField(pybind11::module &m)
{
    py::class_<CThostFtdcQrySuperUserFunctionField>(m, "CThostFtdcQrySuperUserFunctionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQrySuperUserFunctionField, UserID)
    ;
}
void generate_class_CThostFtdcQryUserSessionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryUserSessionField>(m, "CThostFtdcQryUserSessionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryUserSessionField, FrontID)
        .DEF_PROPERTY(CThostFtdcQryUserSessionField, SessionID)
        .DEF_PROPERTY(CThostFtdcQryUserSessionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryUserSessionField, UserID)
    ;
}
void generate_class_CThostFtdcQryPartBrokerField(pybind11::module &m)
{
    py::class_<CThostFtdcQryPartBrokerField>(m, "CThostFtdcQryPartBrokerField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryPartBrokerField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryPartBrokerField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryPartBrokerField, ParticipantID)
    ;
}
void generate_class_CThostFtdcQryFrontStatusField(pybind11::module &m)
{
    py::class_<CThostFtdcQryFrontStatusField>(m, "CThostFtdcQryFrontStatusField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryFrontStatusField, FrontID)
    ;
}
void generate_class_CThostFtdcQryExchangeOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExchangeOrderField>(m, "CThostFtdcQryExchangeOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ClientID)
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderField, TraderID)
    ;
}
void generate_class_CThostFtdcQryOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryOrderActionField>(m, "CThostFtdcQryOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryOrderActionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryExchangeOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExchangeOrderActionField>(m, "CThostFtdcQryExchangeOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, TraderID)
    ;
}
void generate_class_CThostFtdcQrySuperUserField(pybind11::module &m)
{
    py::class_<CThostFtdcQrySuperUserField>(m, "CThostFtdcQrySuperUserField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQrySuperUserField, UserID)
    ;
}
void generate_class_CThostFtdcQryExchangeField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExchangeField>(m, "CThostFtdcQryExchangeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExchangeField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryProductField(pybind11::module &m)
{
    py::class_<CThostFtdcQryProductField>(m, "CThostFtdcQryProductField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryProductField, ProductID)
        .DEF_PROPERTY(CThostFtdcQryProductField, ProductClass)
        .DEF_PROPERTY(CThostFtdcQryProductField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryInstrumentField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInstrumentField>(m, "CThostFtdcQryInstrumentField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInstrumentField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentField, ProductID)
    ;
}
void generate_class_CThostFtdcQryDepthMarketDataField(pybind11::module &m)
{
    py::class_<CThostFtdcQryDepthMarketDataField>(m, "CThostFtdcQryDepthMarketDataField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryDepthMarketDataField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryDepthMarketDataField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryBrokerUserField(pybind11::module &m)
{
    py::class_<CThostFtdcQryBrokerUserField>(m, "CThostFtdcQryBrokerUserField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryBrokerUserField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryBrokerUserField, UserID)
    ;
}

