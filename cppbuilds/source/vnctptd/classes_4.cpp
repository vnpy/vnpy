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


void generate_class_CThostFtdcQryStrikeOffsetField(pybind11::module &m)
{
    py::class_<CThostFtdcQryStrikeOffsetField>(m, "CThostFtdcQryStrikeOffsetField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryStrikeOffsetField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryStrikeOffsetField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryStrikeOffsetField, InstrumentID)
    ;
}
void generate_class_CThostFtdcInputLockField(pybind11::module &m)
{
    py::class_<CThostFtdcInputLockField>(m, "CThostFtdcInputLockField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputLockField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputLockField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputLockField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInputLockField, LockRef)
        .DEF_PROPERTY(CThostFtdcInputLockField, UserID)
        .DEF_PROPERTY(CThostFtdcInputLockField, Volume)
        .DEF_PROPERTY(CThostFtdcInputLockField, RequestID)
        .DEF_PROPERTY(CThostFtdcInputLockField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcInputLockField, LockType)
        .DEF_PROPERTY(CThostFtdcInputLockField, ExchangeID)
    ;
}
void generate_class_CThostFtdcLockField(pybind11::module &m)
{
    py::class_<CThostFtdcLockField>(m, "CThostFtdcLockField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLockField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLockField, InvestorID)
        .DEF_PROPERTY(CThostFtdcLockField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcLockField, LockRef)
        .DEF_PROPERTY(CThostFtdcLockField, UserID)
        .DEF_PROPERTY(CThostFtdcLockField, Volume)
        .DEF_PROPERTY(CThostFtdcLockField, RequestID)
        .DEF_PROPERTY(CThostFtdcLockField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcLockField, LockType)
        .DEF_PROPERTY(CThostFtdcLockField, LockLocalID)
        .DEF_PROPERTY(CThostFtdcLockField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcLockField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcLockField, ClientID)
        .DEF_PROPERTY(CThostFtdcLockField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcLockField, TraderID)
        .DEF_PROPERTY(CThostFtdcLockField, InstallID)
        .DEF_PROPERTY(CThostFtdcLockField, OrderSubmitStatus)
        .DEF_PROPERTY(CThostFtdcLockField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcLockField, TradingDay)
        .DEF_PROPERTY(CThostFtdcLockField, SettlementID)
        .DEF_PROPERTY(CThostFtdcLockField, LockSysID)
        .DEF_PROPERTY(CThostFtdcLockField, InsertDate)
        .DEF_PROPERTY(CThostFtdcLockField, InsertTime)
        .DEF_PROPERTY(CThostFtdcLockField, CancelTime)
        .DEF_PROPERTY(CThostFtdcLockField, LockStatus)
        .DEF_PROPERTY(CThostFtdcLockField, ClearingPartID)
        .DEF_PROPERTY(CThostFtdcLockField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcLockField, FrontID)
        .DEF_PROPERTY(CThostFtdcLockField, SessionID)
        .DEF_PROPERTY(CThostFtdcLockField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcLockField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcLockField, ActiveUserID)
        .DEF_PROPERTY(CThostFtdcLockField, BrokerLockSeq)
        .DEF_PROPERTY(CThostFtdcLockField, BranchID)
    ;
}
void generate_class_CThostFtdcQryLockField(pybind11::module &m)
{
    py::class_<CThostFtdcQryLockField>(m, "CThostFtdcQryLockField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryLockField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryLockField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryLockField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryLockField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryLockField, LockSysID)
        .DEF_PROPERTY(CThostFtdcQryLockField, InsertTimeStart)
        .DEF_PROPERTY(CThostFtdcQryLockField, InsertTimeEnd)
    ;
}
void generate_class_CThostFtdcLockPositionField(pybind11::module &m)
{
    py::class_<CThostFtdcLockPositionField>(m, "CThostFtdcLockPositionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLockPositionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLockPositionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcLockPositionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcLockPositionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcLockPositionField, Volume)
        .DEF_PROPERTY(CThostFtdcLockPositionField, FrozenVolume)
    ;
}
void generate_class_CThostFtdcQryLockPositionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryLockPositionField>(m, "CThostFtdcQryLockPositionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryLockPositionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryLockPositionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryLockPositionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryLockPositionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcETFOptionInstrCommRateField(pybind11::module &m)
{
    py::class_<CThostFtdcETFOptionInstrCommRateField>(m, "CThostFtdcETFOptionInstrCommRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, OpenRatioByMoney)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, OpenRatioByVolume)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, CloseRatioByMoney)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, CloseRatioByVolume)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, CloseTodayRatioByMoney)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, CloseTodayRatioByVolume)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, StrikeRatioByMoney)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, StrikeRatioByVolume)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcETFOptionInstrCommRateField, PosiDirection)
    ;
}
void generate_class_CThostFtdcQryETFOptionInstrCommRateField(pybind11::module &m)
{
    py::class_<CThostFtdcQryETFOptionInstrCommRateField>(m, "CThostFtdcQryETFOptionInstrCommRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryETFOptionInstrCommRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryETFOptionInstrCommRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryETFOptionInstrCommRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryETFOptionInstrCommRateField, ExchangeID)
    ;
}
void generate_class_CThostFtdcPosiFreezeField(pybind11::module &m)
{
    py::class_<CThostFtdcPosiFreezeField>(m, "CThostFtdcPosiFreezeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, TraderID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, InstallID)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, Volume)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, FreezeReasonType)
        .DEF_PROPERTY(CThostFtdcPosiFreezeField, FreezeType)
    ;
}
void generate_class_CThostFtdcQryExchangeLockField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExchangeLockField>(m, "CThostFtdcQryExchangeLockField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExchangeLockField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcQryExchangeLockField, ClientID)
        .DEF_PROPERTY(CThostFtdcQryExchangeLockField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcQryExchangeLockField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryExchangeLockField, TraderID)
    ;
}
void generate_class_CThostFtdcExchangeLockField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeLockField>(m, "CThostFtdcExchangeLockField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeLockField, Volume)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, RequestID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, LockType)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, LockLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, OrderSubmitStatus)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, TradingDay)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, SettlementID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, LockSysID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, InsertDate)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, InsertTime)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, CancelTime)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, LockStatus)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, ClearingPartID)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcExchangeLockField, BranchID)
    ;
}
void generate_class_CThostFtdcExchangeExecOrderActionErrorField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeExecOrderActionErrorField>(m, "CThostFtdcExchangeExecOrderActionErrorField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, ExecOrderSysID)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, ExecOrderLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, ErrorID)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, ErrorMsg)
        .DEF_PROPERTY(CThostFtdcExchangeExecOrderActionErrorField, BrokerID)
    ;
}
void generate_class_CThostFtdcInputBatchOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcInputBatchOrderActionField>(m, "CThostFtdcInputBatchOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, OrderActionRef)
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, UserID)
    ;
}
void generate_class_CThostFtdcBatchOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcBatchOrderActionField>(m, "CThostFtdcBatchOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, OrderActionRef)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, ActionDate)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, ActionTime)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, OrderActionStatus)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, UserID)
        .DEF_PROPERTY(CThostFtdcBatchOrderActionField, StatusMsg)
    ;
}
void generate_class_CThostFtdcExchangeBatchOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeBatchOrderActionField>(m, "CThostFtdcExchangeBatchOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ActionDate)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ActionTime)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, OrderActionStatus)
        .DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, UserID)
    ;
}
void generate_class_CThostFtdcQryBatchOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryBatchOrderActionField>(m, "CThostFtdcQryBatchOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryBatchOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryBatchOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryBatchOrderActionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcLimitPosiField(pybind11::module &m)
{
    py::class_<CThostFtdcLimitPosiField>(m, "CThostFtdcLimitPosiField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLimitPosiField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, InvestorID)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, TotalVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, LongVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, OpenVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, LongAmount)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, TotalVolumeFrozen)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, LongVolumeFrozen)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, OpenVolumeFrozen)
        .DEF_PROPERTY(CThostFtdcLimitPosiField, LongAmountFrozen)
    ;
}
void generate_class_CThostFtdcQryLimitPosiField(pybind11::module &m)
{
    py::class_<CThostFtdcQryLimitPosiField>(m, "CThostFtdcQryLimitPosiField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryLimitPosiField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryLimitPosiField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryLimitPosiField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryLimitPosiField, ExchangeID)
    ;
}
void generate_class_CThostFtdcBrokerLimitPosiField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerLimitPosiField>(m, "CThostFtdcBrokerLimitPosiField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiField, TotalVolume)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiField, LongVolume)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiField, TotalVolumeFrozen)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiField, LongVolumeFrozen)
    ;
}
void generate_class_CThostFtdcQryBrokerLimitPosiField(pybind11::module &m)
{
    py::class_<CThostFtdcQryBrokerLimitPosiField>(m, "CThostFtdcQryBrokerLimitPosiField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryBrokerLimitPosiField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryBrokerLimitPosiField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryBrokerLimitPosiField, ExchangeID)
    ;
}
void generate_class_CThostFtdcLimitPosiSField(pybind11::module &m)
{
    py::class_<CThostFtdcLimitPosiSField>(m, "CThostFtdcLimitPosiSField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, InvestorID)
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, TotalVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, OpenVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, TotalVolumeFrozen)
        .DEF_PROPERTY(CThostFtdcLimitPosiSField, OpenVolumeFrozen)
    ;
}
void generate_class_CThostFtdcQryLimitPosiSField(pybind11::module &m)
{
    py::class_<CThostFtdcQryLimitPosiSField>(m, "CThostFtdcQryLimitPosiSField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryLimitPosiSField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryLimitPosiSField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryLimitPosiSField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryLimitPosiSField, ExchangeID)
    ;
}
void generate_class_CThostFtdcLimitPosiParamField(pybind11::module &m)
{
    py::class_<CThostFtdcLimitPosiParamField>(m, "CThostFtdcLimitPosiParamField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, InvestorID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, TotalVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, LongVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, OpenVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamField, LongAmount)
    ;
}
void generate_class_CThostFtdcBrokerLimitPosiParamField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerLimitPosiParamField>(m, "CThostFtdcBrokerLimitPosiParamField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiParamField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiParamField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiParamField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiParamField, TotalVolume)
        .DEF_PROPERTY(CThostFtdcBrokerLimitPosiParamField, LongVolume)
    ;
}
void generate_class_CThostFtdcLimitPosiParamSField(pybind11::module &m)
{
    py::class_<CThostFtdcLimitPosiParamSField>(m, "CThostFtdcLimitPosiParamSField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLimitPosiParamSField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamSField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamSField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamSField, InvestorID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamSField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamSField, TotalVolume)
        .DEF_PROPERTY(CThostFtdcLimitPosiParamSField, OpenVolume)
    ;
}
void generate_class_CThostFtdcInputStockDisposalActionField(pybind11::module &m)
{
    py::class_<CThostFtdcInputStockDisposalActionField>(m, "CThostFtdcInputStockDisposalActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, StockDisposalActionRef)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, StockDisposalRef)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, StockDisposalSysID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, UserID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalActionField, InstrumentID)
    ;
}
void generate_class_CThostFtdcStockDisposalActionField(pybind11::module &m)
{
    py::class_<CThostFtdcStockDisposalActionField>(m, "CThostFtdcStockDisposalActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, StockDisposalActionRef)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, StockDisposalRef)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, StockDisposalSysID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ActionDate)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ActionTime)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, StockDisposalLocalID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, OrderActionStatus)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, UserID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, ActionType)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcStockDisposalActionField, BranchID)
    ;
}
void generate_class_CThostFtdcQryStockDisposalActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryStockDisposalActionField>(m, "CThostFtdcQryStockDisposalActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryStockDisposalActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryStockDisposalActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryStockDisposalActionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcExchangeStockDisposalActionField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeStockDisposalActionField>(m, "CThostFtdcExchangeStockDisposalActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, StockDisposalSysID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ActionDate)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ActionTime)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, StockDisposalLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, OrderActionStatus)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, UserID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, ActionType)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionField, BranchID)
    ;
}
void generate_class_CThostFtdcQryExchangeStockDisposalActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExchangeStockDisposalActionField>(m, "CThostFtdcQryExchangeStockDisposalActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExchangeStockDisposalActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcQryExchangeStockDisposalActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcQryExchangeStockDisposalActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryExchangeStockDisposalActionField, TraderID)
    ;
}
void generate_class_CThostFtdcQryErrStockDisposalActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryErrStockDisposalActionField>(m, "CThostFtdcQryErrStockDisposalActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryErrStockDisposalActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryErrStockDisposalActionField, InvestorID)
    ;
}
void generate_class_CThostFtdcExchangeStockDisposalActionErrorField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeStockDisposalActionErrorField>(m, "CThostFtdcExchangeStockDisposalActionErrorField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, StockDisposalSysID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, StockDisposalLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, ErrorID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, ErrorMsg)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalActionErrorField, BrokerID)
    ;
}
void generate_class_CThostFtdcErrStockDisposalActionField(pybind11::module &m)
{
    py::class_<CThostFtdcErrStockDisposalActionField>(m, "CThostFtdcErrStockDisposalActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, StockDisposalActionRef)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, StockDisposalRef)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, StockDisposalSysID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, UserID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, ErrorID)
        .DEF_PROPERTY(CThostFtdcErrStockDisposalActionField, ErrorMsg)
    ;
}
void generate_class_CThostFtdcInvestorLevelField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorLevelField>(m, "CThostFtdcInvestorLevelField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorLevelField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorLevelField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorLevelField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInvestorLevelField, LevelType)
    ;
}
void generate_class_CThostFtdcCombInstrumentGuardField(pybind11::module &m)
{
    py::class_<CThostFtdcCombInstrumentGuardField>(m, "CThostFtdcCombInstrumentGuardField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCombInstrumentGuardField, BrokerID)
        .DEF_PROPERTY(CThostFtdcCombInstrumentGuardField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcCombInstrumentGuardField, GuarantRatio)
    ;
}
void generate_class_CThostFtdcQryCombInstrumentGuardField(pybind11::module &m)
{
    py::class_<CThostFtdcQryCombInstrumentGuardField>(m, "CThostFtdcQryCombInstrumentGuardField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryCombInstrumentGuardField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryCombInstrumentGuardField, InstrumentID)
    ;
}
void generate_class_CThostFtdcInputCombActionField(pybind11::module &m)
{
    py::class_<CThostFtdcInputCombActionField>(m, "CThostFtdcInputCombActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputCombActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, CombActionRef)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, UserID)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, Direction)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, Volume)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, CombDirection)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcInputCombActionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcCombActionField(pybind11::module &m)
{
    py::class_<CThostFtdcCombActionField>(m, "CThostFtdcCombActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCombActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcCombActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcCombActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcCombActionField, CombActionRef)
        .DEF_PROPERTY(CThostFtdcCombActionField, UserID)
        .DEF_PROPERTY(CThostFtdcCombActionField, Direction)
        .DEF_PROPERTY(CThostFtdcCombActionField, Volume)
        .DEF_PROPERTY(CThostFtdcCombActionField, CombDirection)
        .DEF_PROPERTY(CThostFtdcCombActionField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcCombActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcCombActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcCombActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcCombActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcCombActionField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcCombActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcCombActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcCombActionField, ActionStatus)
        .DEF_PROPERTY(CThostFtdcCombActionField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcCombActionField, TradingDay)
        .DEF_PROPERTY(CThostFtdcCombActionField, SettlementID)
        .DEF_PROPERTY(CThostFtdcCombActionField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcCombActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcCombActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcCombActionField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcCombActionField, StatusMsg)
    ;
}
void generate_class_CThostFtdcQryCombActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryCombActionField>(m, "CThostFtdcQryCombActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryCombActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryCombActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryCombActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryCombActionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcExchangeCombActionField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeCombActionField>(m, "CThostFtdcExchangeCombActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, Direction)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, Volume)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, CombDirection)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, ActionStatus)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, TradingDay)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, SettlementID)
        .DEF_PROPERTY(CThostFtdcExchangeCombActionField, SequenceNo)
    ;
}
void generate_class_CThostFtdcQryExchangeCombActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExchangeCombActionField>(m, "CThostFtdcQryExchangeCombActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, TraderID)
    ;
}
void generate_class_CThostFtdcProductExchRateField(pybind11::module &m)
{
    py::class_<CThostFtdcProductExchRateField>(m, "CThostFtdcProductExchRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcProductExchRateField, ProductID)
        .DEF_PROPERTY(CThostFtdcProductExchRateField, QuoteCurrencyID)
        .DEF_PROPERTY(CThostFtdcProductExchRateField, ExchangeRate)
    ;
}
void generate_class_CThostFtdcQryProductExchRateField(pybind11::module &m)
{
    py::class_<CThostFtdcQryProductExchRateField>(m, "CThostFtdcQryProductExchRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryProductExchRateField, ProductID)
    ;
}
void generate_class_CThostFtdcInputDesignateField(pybind11::module &m)
{
    py::class_<CThostFtdcInputDesignateField>(m, "CThostFtdcInputDesignateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputDesignateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputDesignateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputDesignateField, DesignateRef)
        .DEF_PROPERTY(CThostFtdcInputDesignateField, UserID)
        .DEF_PROPERTY(CThostFtdcInputDesignateField, DesignateType)
        .DEF_PROPERTY(CThostFtdcInputDesignateField, ExchangeID)
    ;
}
void generate_class_CThostFtdcDesignateField(pybind11::module &m)
{
    py::class_<CThostFtdcDesignateField>(m, "CThostFtdcDesignateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcDesignateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcDesignateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcDesignateField, DesignateRef)
        .DEF_PROPERTY(CThostFtdcDesignateField, UserID)
        .DEF_PROPERTY(CThostFtdcDesignateField, DesignateType)
        .DEF_PROPERTY(CThostFtdcDesignateField, DesignateLocalID)
        .DEF_PROPERTY(CThostFtdcDesignateField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcDesignateField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcDesignateField, ClientID)
        .DEF_PROPERTY(CThostFtdcDesignateField, TraderID)
        .DEF_PROPERTY(CThostFtdcDesignateField, InstallID)
        .DEF_PROPERTY(CThostFtdcDesignateField, DesignateStatus)
        .DEF_PROPERTY(CThostFtdcDesignateField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcDesignateField, TradingDay)
        .DEF_PROPERTY(CThostFtdcDesignateField, SettlementID)
        .DEF_PROPERTY(CThostFtdcDesignateField, InsertDate)
        .DEF_PROPERTY(CThostFtdcDesignateField, InsertTime)
        .DEF_PROPERTY(CThostFtdcDesignateField, FrontID)
        .DEF_PROPERTY(CThostFtdcDesignateField, SessionID)
        .DEF_PROPERTY(CThostFtdcDesignateField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcDesignateField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcDesignateField, BranchID)
    ;
}
void generate_class_CThostFtdcQryDesignateField(pybind11::module &m)
{
    py::class_<CThostFtdcQryDesignateField>(m, "CThostFtdcQryDesignateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryDesignateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryDesignateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryDesignateField, ExchangeID)
    ;
}
void generate_class_CThostFtdcExchangeDesignateField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeDesignateField>(m, "CThostFtdcExchangeDesignateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, DesignateType)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, DesignateLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, DesignateStatus)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, TradingDay)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, SettlementID)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, InsertDate)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, InsertTime)
        .DEF_PROPERTY(CThostFtdcExchangeDesignateField, BranchID)
    ;
}
void generate_class_CThostFtdcInputStockDisposalField(pybind11::module &m)
{
    py::class_<CThostFtdcInputStockDisposalField>(m, "CThostFtdcInputStockDisposalField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, StockDisposalRef)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, UserID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, Volume)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, StockDisposalType)
        .DEF_PROPERTY(CThostFtdcInputStockDisposalField, ExchangeID)
    ;
}
void generate_class_CThostFtdcStockDisposalField(pybind11::module &m)
{
    py::class_<CThostFtdcStockDisposalField>(m, "CThostFtdcStockDisposalField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcStockDisposalField, BrokerID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, InvestorID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, StockDisposalRef)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, UserID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, Volume)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, StockDisposalType)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, StockDisposalLocalID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, ClientID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, TraderID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, InstallID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, StockDisposalStatus)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, TradingDay)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, SettlementID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, InsertDate)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, InsertTime)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, FrontID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, SessionID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, BranchID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, StockDisposalSysID)
        .DEF_PROPERTY(CThostFtdcStockDisposalField, BusinessUnit)
    ;
}
void generate_class_CThostFtdcQryStockDisposalField(pybind11::module &m)
{
    py::class_<CThostFtdcQryStockDisposalField>(m, "CThostFtdcQryStockDisposalField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryStockDisposalField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryStockDisposalField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryStockDisposalField, ExchangeID)
    ;
}

