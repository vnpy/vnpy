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


void generate_class_CThostFtdcParkedOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcParkedOrderActionField>(m, "CThostFtdcParkedOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, OrderActionRef)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, OrderRef)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, VolumeChange)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, UserID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, ParkedOrderActionID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, UserType)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, Status)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, ErrorID)
        .DEF_PROPERTY(CThostFtdcParkedOrderActionField, ErrorMsg)
    ;
}
void generate_class_CThostFtdcQryParkedOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcQryParkedOrderField>(m, "CThostFtdcQryParkedOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryParkedOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryParkedOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryParkedOrderField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryParkedOrderField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryParkedOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryParkedOrderActionField>(m, "CThostFtdcQryParkedOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, ExchangeID)
    ;
}
void generate_class_CThostFtdcRemoveParkedOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcRemoveParkedOrderField>(m, "CThostFtdcRemoveParkedOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcRemoveParkedOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcRemoveParkedOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcRemoveParkedOrderField, ParkedOrderID)
    ;
}
void generate_class_CThostFtdcRemoveParkedOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcRemoveParkedOrderActionField>(m, "CThostFtdcRemoveParkedOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcRemoveParkedOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcRemoveParkedOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcRemoveParkedOrderActionField, ParkedOrderActionID)
    ;
}
void generate_class_CThostFtdcInvestorWithdrawAlgorithmField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorWithdrawAlgorithmField>(m, "CThostFtdcInvestorWithdrawAlgorithmField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, UsingRatio)
        .DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, FundMortgageRatio)
    ;
}
void generate_class_CThostFtdcQryInvestorPositionCombineDetailField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInvestorPositionCombineDetailField>(m, "CThostFtdcQryInvestorPositionCombineDetailField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, CombInstrumentID)
    ;
}
void generate_class_CThostFtdcMarketDataAveragePriceField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataAveragePriceField>(m, "CThostFtdcMarketDataAveragePriceField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataAveragePriceField, AveragePrice)
    ;
}
void generate_class_CThostFtdcVerifyInvestorPasswordField(pybind11::module &m)
{
    py::class_<CThostFtdcVerifyInvestorPasswordField>(m, "CThostFtdcVerifyInvestorPasswordField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcVerifyInvestorPasswordField, BrokerID)
        .DEF_PROPERTY(CThostFtdcVerifyInvestorPasswordField, InvestorID)
        .DEF_PROPERTY(CThostFtdcVerifyInvestorPasswordField, Password)
    ;
}
void generate_class_CThostFtdcUserIPField(pybind11::module &m)
{
    py::class_<CThostFtdcUserIPField>(m, "CThostFtdcUserIPField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcUserIPField, BrokerID)
        .DEF_PROPERTY(CThostFtdcUserIPField, UserID)
        .DEF_PROPERTY(CThostFtdcUserIPField, IPAddress)
        .DEF_PROPERTY(CThostFtdcUserIPField, IPMask)
        .DEF_PROPERTY(CThostFtdcUserIPField, MacAddress)
    ;
}
void generate_class_CThostFtdcTradingNoticeInfoField(pybind11::module &m)
{
    py::class_<CThostFtdcTradingNoticeInfoField>(m, "CThostFtdcTradingNoticeInfoField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, InvestorID)
        .DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, SendTime)
        .DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, FieldContent)
        .DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, SequenceSeries)
        .DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, SequenceNo)
    ;
}
void generate_class_CThostFtdcTradingNoticeField(pybind11::module &m)
{
    py::class_<CThostFtdcTradingNoticeField>(m, "CThostFtdcTradingNoticeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, SequenceSeries)
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, UserID)
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, SendTime)
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcTradingNoticeField, FieldContent)
    ;
}
void generate_class_CThostFtdcQryTradingNoticeField(pybind11::module &m)
{
    py::class_<CThostFtdcQryTradingNoticeField>(m, "CThostFtdcQryTradingNoticeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryTradingNoticeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryTradingNoticeField, InvestorID)
    ;
}
void generate_class_CThostFtdcQryErrOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcQryErrOrderField>(m, "CThostFtdcQryErrOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryErrOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryErrOrderField, InvestorID)
    ;
}
void generate_class_CThostFtdcErrOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcErrOrderField>(m, "CThostFtdcErrOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcErrOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcErrOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcErrOrderField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcErrOrderField, OrderRef)
        .DEF_PROPERTY(CThostFtdcErrOrderField, UserID)
        .DEF_PROPERTY(CThostFtdcErrOrderField, OrderPriceType)
        .DEF_PROPERTY(CThostFtdcErrOrderField, Direction)
        .DEF_PROPERTY(CThostFtdcErrOrderField, CombOffsetFlag)
        .DEF_PROPERTY(CThostFtdcErrOrderField, CombHedgeFlag)
        .DEF_PROPERTY(CThostFtdcErrOrderField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcErrOrderField, VolumeTotalOriginal)
        .DEF_PROPERTY(CThostFtdcErrOrderField, TimeCondition)
        .DEF_PROPERTY(CThostFtdcErrOrderField, GTDDate)
        .DEF_PROPERTY(CThostFtdcErrOrderField, VolumeCondition)
        .DEF_PROPERTY(CThostFtdcErrOrderField, MinVolume)
        .DEF_PROPERTY(CThostFtdcErrOrderField, ContingentCondition)
        .DEF_PROPERTY(CThostFtdcErrOrderField, StopPrice)
        .DEF_PROPERTY(CThostFtdcErrOrderField, ForceCloseReason)
        .DEF_PROPERTY(CThostFtdcErrOrderField, IsAutoSuspend)
        .DEF_PROPERTY(CThostFtdcErrOrderField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcErrOrderField, RequestID)
        .DEF_PROPERTY(CThostFtdcErrOrderField, UserForceClose)
        .DEF_PROPERTY(CThostFtdcErrOrderField, ErrorID)
        .DEF_PROPERTY(CThostFtdcErrOrderField, ErrorMsg)
        .DEF_PROPERTY(CThostFtdcErrOrderField, IsSwapOrder)
        .DEF_PROPERTY(CThostFtdcErrOrderField, ExchangeID)
    ;
}
void generate_class_CThostFtdcErrorConditionalOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcErrorConditionalOrderField>(m, "CThostFtdcErrorConditionalOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderRef)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UserID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderPriceType)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, Direction)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, CombOffsetFlag)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, CombHedgeFlag)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeTotalOriginal)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, TimeCondition)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, GTDDate)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeCondition)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, MinVolume)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ContingentCondition)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, StopPrice)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ForceCloseReason)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, IsAutoSuspend)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, RequestID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ClientID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, TraderID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InstallID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderSubmitStatus)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, TradingDay)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SettlementID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderSource)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderStatus)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderType)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeTraded)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeTotal)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InsertDate)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InsertTime)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ActiveTime)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SuspendTime)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UpdateTime)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, CancelTime)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ActiveTraderID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ClearingPartID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, FrontID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SessionID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UserForceClose)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ActiveUserID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BrokerOrderSeq)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, RelativeOrderSysID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ZCETotalTradedVolume)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ErrorID)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ErrorMsg)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, IsSwapOrder)
        .DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BranchID)
    ;
}
void generate_class_CThostFtdcQryErrOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcQryErrOrderActionField>(m, "CThostFtdcQryErrOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryErrOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryErrOrderActionField, InvestorID)
    ;
}
void generate_class_CThostFtdcErrOrderActionField(pybind11::module &m)
{
    py::class_<CThostFtdcErrOrderActionField>(m, "CThostFtdcErrOrderActionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderActionRef)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderRef)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, RequestID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, FrontID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, SessionID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderSysID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionFlag)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, VolumeChange)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionDate)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionTime)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, TraderID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, InstallID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionLocalID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ClientID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderActionStatus)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, UserID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, StatusMsg)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, BranchID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ErrorID)
        .DEF_PROPERTY(CThostFtdcErrOrderActionField, ErrorMsg)
    ;
}
void generate_class_CThostFtdcQryExchangeSequenceField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExchangeSequenceField>(m, "CThostFtdcQryExchangeSequenceField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExchangeSequenceField, ExchangeID)
    ;
}
void generate_class_CThostFtdcExchangeSequenceField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeSequenceField>(m, "CThostFtdcExchangeSequenceField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeSequenceField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeSequenceField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcExchangeSequenceField, MarketStatus)
    ;
}
void generate_class_CThostFtdcQueryMaxOrderVolumeWithPriceField(pybind11::module &m)
{
    py::class_<CThostFtdcQueryMaxOrderVolumeWithPriceField>(m, "CThostFtdcQueryMaxOrderVolumeWithPriceField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, Direction)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, OffsetFlag)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, MaxVolume)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, Price)
        .DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryBrokerTradingParamsField(pybind11::module &m)
{
    py::class_<CThostFtdcQryBrokerTradingParamsField>(m, "CThostFtdcQryBrokerTradingParamsField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryBrokerTradingParamsField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryBrokerTradingParamsField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryBrokerTradingParamsField, CurrencyID)
    ;
}
void generate_class_CThostFtdcBrokerTradingParamsField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerTradingParamsField>(m, "CThostFtdcBrokerTradingParamsField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, InvestorID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, MarginPriceType)
        .DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, Algorithm)
        .DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, AvailIncludeCloseProfit)
        .DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, OptionRoyaltyPriceType)
    ;
}
void generate_class_CThostFtdcQryBrokerTradingAlgosField(pybind11::module &m)
{
    py::class_<CThostFtdcQryBrokerTradingAlgosField>(m, "CThostFtdcQryBrokerTradingAlgosField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryBrokerTradingAlgosField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryBrokerTradingAlgosField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryBrokerTradingAlgosField, InstrumentID)
    ;
}
void generate_class_CThostFtdcBrokerTradingAlgosField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerTradingAlgosField>(m, "CThostFtdcBrokerTradingAlgosField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, HandlePositionAlgoID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, FindMarginRateAlgoID)
        .DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, HandleTradingAccountAlgoID)
    ;
}
void generate_class_CThostFtdcQueryBrokerDepositField(pybind11::module &m)
{
    py::class_<CThostFtdcQueryBrokerDepositField>(m, "CThostFtdcQueryBrokerDepositField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQueryBrokerDepositField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQueryBrokerDepositField, ExchangeID)
    ;
}
void generate_class_CThostFtdcBrokerDepositField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerDepositField>(m, "CThostFtdcBrokerDepositField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, TradingDay)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, PreBalance)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, CurrMargin)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, CloseProfit)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, Balance)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, Deposit)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, Withdraw)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, Available)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, Reserve)
        .DEF_PROPERTY(CThostFtdcBrokerDepositField, FrozenMargin)
    ;
}
void generate_class_CThostFtdcQryCFMMCBrokerKeyField(pybind11::module &m)
{
    py::class_<CThostFtdcQryCFMMCBrokerKeyField>(m, "CThostFtdcQryCFMMCBrokerKeyField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryCFMMCBrokerKeyField, BrokerID)
    ;
}
void generate_class_CThostFtdcCFMMCBrokerKeyField(pybind11::module &m)
{
    py::class_<CThostFtdcCFMMCBrokerKeyField>(m, "CThostFtdcCFMMCBrokerKeyField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, BrokerID)
        .DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, CreateDate)
        .DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, CreateTime)
        .DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, KeyID)
        .DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, CurrentKey)
        .DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, KeyKind)
    ;
}
void generate_class_CThostFtdcCFMMCTradingAccountKeyField(pybind11::module &m)
{
    py::class_<CThostFtdcCFMMCTradingAccountKeyField>(m, "CThostFtdcCFMMCTradingAccountKeyField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, BrokerID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, AccountID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, KeyID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, CurrentKey)
    ;
}
void generate_class_CThostFtdcQryCFMMCTradingAccountKeyField(pybind11::module &m)
{
    py::class_<CThostFtdcQryCFMMCTradingAccountKeyField>(m, "CThostFtdcQryCFMMCTradingAccountKeyField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryCFMMCTradingAccountKeyField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryCFMMCTradingAccountKeyField, InvestorID)
    ;
}
void generate_class_CThostFtdcBrokerUserOTPParamField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerUserOTPParamField>(m, "CThostFtdcBrokerUserOTPParamField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, UserID)
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, OTPVendorsID)
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, SerialNumber)
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, AuthKey)
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, LastDrift)
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, LastSuccess)
        .DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, OTPType)
    ;
}
void generate_class_CThostFtdcManualSyncBrokerUserOTPField(pybind11::module &m)
{
    py::class_<CThostFtdcManualSyncBrokerUserOTPField>(m, "CThostFtdcManualSyncBrokerUserOTPField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, BrokerID)
        .DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, UserID)
        .DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, OTPType)
        .DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, FirstOTP)
        .DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, SecondOTP)
    ;
}
void generate_class_CThostFtdcCommRateModelField(pybind11::module &m)
{
    py::class_<CThostFtdcCommRateModelField>(m, "CThostFtdcCommRateModelField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCommRateModelField, BrokerID)
        .DEF_PROPERTY(CThostFtdcCommRateModelField, CommModelID)
        .DEF_PROPERTY(CThostFtdcCommRateModelField, CommModelName)
    ;
}
void generate_class_CThostFtdcQryCommRateModelField(pybind11::module &m)
{
    py::class_<CThostFtdcQryCommRateModelField>(m, "CThostFtdcQryCommRateModelField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryCommRateModelField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryCommRateModelField, CommModelID)
    ;
}
void generate_class_CThostFtdcMarginModelField(pybind11::module &m)
{
    py::class_<CThostFtdcMarginModelField>(m, "CThostFtdcMarginModelField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarginModelField, BrokerID)
        .DEF_PROPERTY(CThostFtdcMarginModelField, MarginModelID)
        .DEF_PROPERTY(CThostFtdcMarginModelField, MarginModelName)
    ;
}
void generate_class_CThostFtdcQryMarginModelField(pybind11::module &m)
{
    py::class_<CThostFtdcQryMarginModelField>(m, "CThostFtdcQryMarginModelField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryMarginModelField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryMarginModelField, MarginModelID)
    ;
}
void generate_class_CThostFtdcEWarrantOffsetField(pybind11::module &m)
{
    py::class_<CThostFtdcEWarrantOffsetField>(m, "CThostFtdcEWarrantOffsetField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, TradingDay)
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, BrokerID)
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, InvestorID)
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, Direction)
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcEWarrantOffsetField, Volume)
    ;
}
void generate_class_CThostFtdcQryEWarrantOffsetField(pybind11::module &m)
{
    py::class_<CThostFtdcQryEWarrantOffsetField>(m, "CThostFtdcQryEWarrantOffsetField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, InstrumentID)
    ;
}
void generate_class_CThostFtdcQryInvestorProductGroupMarginField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInvestorProductGroupMarginField>(m, "CThostFtdcQryInvestorProductGroupMarginField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, ProductGroupID)
        .DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, HedgeFlag)
    ;
}
void generate_class_CThostFtdcInvestorProductGroupMarginField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorProductGroupMarginField>(m, "CThostFtdcInvestorProductGroupMarginField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ProductGroupID)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, TradingDay)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, SettlementID)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, FrozenMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongFrozenMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortFrozenMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, UseMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongUseMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortUseMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ExchMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongExchMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortExchMargin)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, CloseProfit)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, FrozenCommission)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, Commission)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, FrozenCash)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, CashIn)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, PositionProfit)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, OffsetAmount)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongOffsetAmount)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortOffsetAmount)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ExchOffsetAmount)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongExchOffsetAmount)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortExchOffsetAmount)
        .DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, HedgeFlag)
    ;
}
void generate_class_CThostFtdcQueryCFMMCTradingAccountTokenField(pybind11::module &m)
{
    py::class_<CThostFtdcQueryCFMMCTradingAccountTokenField>(m, "CThostFtdcQueryCFMMCTradingAccountTokenField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQueryCFMMCTradingAccountTokenField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQueryCFMMCTradingAccountTokenField, InvestorID)
    ;
}
void generate_class_CThostFtdcCFMMCTradingAccountTokenField(pybind11::module &m)
{
    py::class_<CThostFtdcCFMMCTradingAccountTokenField>(m, "CThostFtdcCFMMCTradingAccountTokenField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, BrokerID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, AccountID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, KeyID)
        .DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, Token)
    ;
}
void generate_class_CThostFtdcInstructionRightField(pybind11::module &m)
{
    py::class_<CThostFtdcInstructionRightField>(m, "CThostFtdcInstructionRightField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInstructionRightField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInstructionRightField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInstructionRightField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInstructionRightField, InstructionRight)
        .DEF_PROPERTY(CThostFtdcInstructionRightField, IsForbidden)
    ;
}
void generate_class_CThostFtdcQryProductGroupField(pybind11::module &m)
{
    py::class_<CThostFtdcQryProductGroupField>(m, "CThostFtdcQryProductGroupField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryProductGroupField, ProductID)
        .DEF_PROPERTY(CThostFtdcQryProductGroupField, ExchangeID)
    ;
}
void generate_class_CThostFtdcProductGroupField(pybind11::module &m)
{
    py::class_<CThostFtdcProductGroupField>(m, "CThostFtdcProductGroupField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcProductGroupField, ProductID)
        .DEF_PROPERTY(CThostFtdcProductGroupField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcProductGroupField, ProductGroupID)
    ;
}
void generate_class_CThostFtdcReqOpenAccountField(pybind11::module &m)
{
    py::class_<CThostFtdcReqOpenAccountField>(m, "CThostFtdcReqOpenAccountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradeCode)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankBranchID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BrokerBranchID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradeDate)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradeTime)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankSerial)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradingDay)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, PlateSerial)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, LastFragment)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, SessionID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, CustomerName)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, IdCardType)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, IdentifiedCardNo)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, Gender)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, CountryCode)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, CustType)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, Address)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, ZipCode)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, Telephone)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, MobilePhone)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, Fax)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, EMail)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, MoneyAccountStatus)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankAccount)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankPassWord)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, AccountID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, Password)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, InstallID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, VerifyCertNoFlag)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, CashExchangeCode)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, Digest)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankAccType)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, DeviceID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankSecuAccType)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BrokerIDByBank)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankSecuAcc)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, SecuPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, OperNo)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, TID)
        .DEF_PROPERTY(CThostFtdcReqOpenAccountField, UserID)
    ;
}
void generate_class_CThostFtdcReqCancelAccountField(pybind11::module &m)
{
    py::class_<CThostFtdcReqCancelAccountField>(m, "CThostFtdcReqCancelAccountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradeCode)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankBranchID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BrokerBranchID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradeDate)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradeTime)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankSerial)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradingDay)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, PlateSerial)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, LastFragment)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, SessionID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, CustomerName)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, IdCardType)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, IdentifiedCardNo)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, Gender)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, CountryCode)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, CustType)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, Address)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, ZipCode)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, Telephone)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, MobilePhone)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, Fax)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, EMail)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, MoneyAccountStatus)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankAccount)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankPassWord)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, AccountID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, Password)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, InstallID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, VerifyCertNoFlag)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, CashExchangeCode)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, Digest)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankAccType)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, DeviceID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankSecuAccType)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BrokerIDByBank)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankSecuAcc)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, SecuPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, OperNo)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, TID)
        .DEF_PROPERTY(CThostFtdcReqCancelAccountField, UserID)
    ;
}
void generate_class_CThostFtdcReqChangeAccountField(pybind11::module &m)
{
    py::class_<CThostFtdcReqChangeAccountField>(m, "CThostFtdcReqChangeAccountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradeCode)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankBranchID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BrokerBranchID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradeDate)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradeTime)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankSerial)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradingDay)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, PlateSerial)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, LastFragment)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, SessionID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, CustomerName)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, IdCardType)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, IdentifiedCardNo)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, Gender)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, CountryCode)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, CustType)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, Address)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, ZipCode)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, Telephone)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, MobilePhone)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, Fax)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, EMail)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, MoneyAccountStatus)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankAccount)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankPassWord)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, NewBankAccount)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, NewBankPassWord)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, AccountID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, Password)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankAccType)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, InstallID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, VerifyCertNoFlag)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BrokerIDByBank)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, SecuPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, TID)
        .DEF_PROPERTY(CThostFtdcReqChangeAccountField, Digest)
    ;
}
void generate_class_CThostFtdcReqTransferField(pybind11::module &m)
{
    py::class_<CThostFtdcReqTransferField>(m, "CThostFtdcReqTransferField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcReqTransferField, TradeCode)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankBranchID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BrokerID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BrokerBranchID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, TradeDate)
        .DEF_PROPERTY(CThostFtdcReqTransferField, TradeTime)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankSerial)
        .DEF_PROPERTY(CThostFtdcReqTransferField, TradingDay)
        .DEF_PROPERTY(CThostFtdcReqTransferField, PlateSerial)
        .DEF_PROPERTY(CThostFtdcReqTransferField, LastFragment)
        .DEF_PROPERTY(CThostFtdcReqTransferField, SessionID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, CustomerName)
        .DEF_PROPERTY(CThostFtdcReqTransferField, IdCardType)
        .DEF_PROPERTY(CThostFtdcReqTransferField, IdentifiedCardNo)
        .DEF_PROPERTY(CThostFtdcReqTransferField, CustType)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankAccount)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankPassWord)
        .DEF_PROPERTY(CThostFtdcReqTransferField, AccountID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, Password)
        .DEF_PROPERTY(CThostFtdcReqTransferField, InstallID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, FutureSerial)
        .DEF_PROPERTY(CThostFtdcReqTransferField, UserID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, VerifyCertNoFlag)
        .DEF_PROPERTY(CThostFtdcReqTransferField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, TradeAmount)
        .DEF_PROPERTY(CThostFtdcReqTransferField, FutureFetchAmount)
        .DEF_PROPERTY(CThostFtdcReqTransferField, FeePayFlag)
        .DEF_PROPERTY(CThostFtdcReqTransferField, CustFee)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BrokerFee)
        .DEF_PROPERTY(CThostFtdcReqTransferField, Message)
        .DEF_PROPERTY(CThostFtdcReqTransferField, Digest)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankAccType)
        .DEF_PROPERTY(CThostFtdcReqTransferField, DeviceID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankSecuAccType)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BrokerIDByBank)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankSecuAcc)
        .DEF_PROPERTY(CThostFtdcReqTransferField, BankPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqTransferField, SecuPwdFlag)
        .DEF_PROPERTY(CThostFtdcReqTransferField, OperNo)
        .DEF_PROPERTY(CThostFtdcReqTransferField, RequestID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, TID)
        .DEF_PROPERTY(CThostFtdcReqTransferField, TransferStatus)
    ;
}

