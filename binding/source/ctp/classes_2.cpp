#include <iostream>
#include <string>
#include <pybind11/pybind11.h>

#include "dispatcher.hpp"
#include "property_helper.hpp"
#include "wrapper_helper.hpp"
#include "wrappers.hpp"

#include "class_generators.h"

#include "api/ThostFtdcTraderApi.h"
#include "api/ThostFtdcMdApi.h"
#include "custom_wrappers/spi.hpp"


void generate_class_CThostFtdcQryBrokerUserField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBrokerUserField> c(m, "CThostFtdcQryBrokerUserField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerUserField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerUserField, UserID);
}
void generate_class_CThostFtdcQryBrokerUserFunctionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBrokerUserFunctionField> c(m, "CThostFtdcQryBrokerUserFunctionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerUserFunctionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerUserFunctionField, UserID);
}
void generate_class_CThostFtdcQryTraderOfferField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTraderOfferField> c(m, "CThostFtdcQryTraderOfferField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTraderOfferField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTraderOfferField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTraderOfferField, TraderID);
}
void generate_class_CThostFtdcQrySyncDepositField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySyncDepositField> c(m, "CThostFtdcQrySyncDepositField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySyncDepositField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySyncDepositField, DepositSeqNo);
}
void generate_class_CThostFtdcQrySettlementInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySettlementInfoField> c(m, "CThostFtdcQrySettlementInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoField, CurrencyID);
}
void generate_class_CThostFtdcQryExchangeMarginRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeMarginRateField> c(m, "CThostFtdcQryExchangeMarginRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeMarginRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeMarginRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeMarginRateField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeMarginRateField, ExchangeID);
}
void generate_class_CThostFtdcQryExchangeMarginRateAdjustField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeMarginRateAdjustField> c(m, "CThostFtdcQryExchangeMarginRateAdjustField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeMarginRateAdjustField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeMarginRateAdjustField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeMarginRateAdjustField, HedgeFlag);
}
void generate_class_CThostFtdcQryExchangeRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeRateField> c(m, "CThostFtdcQryExchangeRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeRateField, FromCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeRateField, ToCurrencyID);
}
void generate_class_CThostFtdcQrySyncFundMortgageField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySyncFundMortgageField> c(m, "CThostFtdcQrySyncFundMortgageField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySyncFundMortgageField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySyncFundMortgageField, MortgageSeqNo);
}
void generate_class_CThostFtdcQryHisOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryHisOrderField> c(m, "CThostFtdcQryHisOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryHisOrderField, SettlementID);
}
void generate_class_CThostFtdcOptionInstrMiniMarginField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionInstrMiniMarginField> c(m, "CThostFtdcOptionInstrMiniMarginField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMiniMarginField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMiniMarginField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMiniMarginField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMiniMarginField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMiniMarginField, MinMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMiniMarginField, ValueMethod);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMiniMarginField, IsRelative);
}
void generate_class_CThostFtdcOptionInstrMarginAdjustField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionInstrMarginAdjustField> c(m, "CThostFtdcOptionInstrMarginAdjustField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, SShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, SShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, HShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, HShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, AShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, AShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, IsRelative);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, MShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrMarginAdjustField, MShortMarginRatioByVolume);
}
void generate_class_CThostFtdcOptionInstrCommRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionInstrCommRateField> c(m, "CThostFtdcOptionInstrCommRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, OpenRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, OpenRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, CloseRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, CloseRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, CloseTodayRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, CloseTodayRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, StrikeRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, StrikeRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrCommRateField, InvestUnitID);
}
void generate_class_CThostFtdcOptionInstrTradeCostField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionInstrTradeCostField> c(m, "CThostFtdcOptionInstrTradeCostField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, FixedMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, MiniMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, Royalty);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, ExchFixedMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, ExchMiniMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradeCostField, InvestUnitID);
}
void generate_class_CThostFtdcQryOptionInstrTradeCostField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryOptionInstrTradeCostField> c(m, "CThostFtdcQryOptionInstrTradeCostField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, InputPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, UnderlyingPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradeCostField, InvestUnitID);
}
void generate_class_CThostFtdcQryOptionInstrCommRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryOptionInstrCommRateField> c(m, "CThostFtdcQryOptionInstrCommRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrCommRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrCommRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrCommRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrCommRateField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrCommRateField, InvestUnitID);
}
void generate_class_CThostFtdcIndexPriceField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcIndexPriceField> c(m, "CThostFtdcIndexPriceField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcIndexPriceField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcIndexPriceField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcIndexPriceField, ClosePrice);
}
void generate_class_CThostFtdcInputExecOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputExecOrderField> c(m, "CThostFtdcInputExecOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, ExecOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, PosiDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, ReservePositionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, CloseFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderField, MacAddress);
}
void generate_class_CThostFtdcInputExecOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputExecOrderActionField> c(m, "CThostFtdcInputExecOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, ExecOrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, ExecOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, ExecOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputExecOrderActionField, MacAddress);
}
void generate_class_CThostFtdcExecOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExecOrderField> c(m, "CThostFtdcExecOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ExecOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, PosiDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ReservePositionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, CloseFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ExecOrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ExecOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ExecResult);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, BrokerExecOrderSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderField, MacAddress);
}
void generate_class_CThostFtdcExecOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExecOrderActionField> c(m, "CThostFtdcExecOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ExecOrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ExecOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ExecOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ExecOrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExecOrderActionField, MacAddress);
}
void generate_class_CThostFtdcQryExecOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExecOrderField> c(m, "CThostFtdcQryExecOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderField, ExecOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderField, InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderField, InsertTimeEnd);
}
void generate_class_CThostFtdcExchangeExecOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeExecOrderField> c(m, "CThostFtdcExchangeExecOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, PosiDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ReservePositionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, CloseFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ExecOrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ExecOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ExecResult);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderField, MacAddress);
}
void generate_class_CThostFtdcQryExchangeExecOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeExecOrderField> c(m, "CThostFtdcQryExchangeExecOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderField, TraderID);
}
void generate_class_CThostFtdcQryExecOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExecOrderActionField> c(m, "CThostFtdcQryExecOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExecOrderActionField, ExchangeID);
}
void generate_class_CThostFtdcExchangeExecOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeExecOrderActionField> c(m, "CThostFtdcExchangeExecOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ExecOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ExecOrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeExecOrderActionField, Volume);
}
void generate_class_CThostFtdcQryExchangeExecOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeExecOrderActionField> c(m, "CThostFtdcQryExchangeExecOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeExecOrderActionField, TraderID);
}
void generate_class_CThostFtdcErrExecOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcErrExecOrderField> c(m, "CThostFtdcErrExecOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, ExecOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, ActionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, PosiDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, ReservePositionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, CloseFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderField, ErrorMsg);
}
void generate_class_CThostFtdcQryErrExecOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryErrExecOrderField> c(m, "CThostFtdcQryErrExecOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrExecOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrExecOrderField, InvestorID);
}
void generate_class_CThostFtdcErrExecOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcErrExecOrderActionField> c(m, "CThostFtdcErrExecOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, ExecOrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, ExecOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, ExecOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrExecOrderActionField, ErrorMsg);
}
void generate_class_CThostFtdcQryErrExecOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryErrExecOrderActionField> c(m, "CThostFtdcQryErrExecOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrExecOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrExecOrderActionField, InvestorID);
}
void generate_class_CThostFtdcOptionInstrTradingRightField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionInstrTradingRightField> c(m, "CThostFtdcOptionInstrTradingRightField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradingRightField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradingRightField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradingRightField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradingRightField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradingRightField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrTradingRightField, TradingRight);
}
void generate_class_CThostFtdcQryOptionInstrTradingRightField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryOptionInstrTradingRightField> c(m, "CThostFtdcQryOptionInstrTradingRightField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradingRightField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradingRightField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradingRightField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionInstrTradingRightField, Direction);
}
void generate_class_CThostFtdcInputForQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputForQuoteField> c(m, "CThostFtdcInputForQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, ForQuoteRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputForQuoteField, MacAddress);
}
void generate_class_CThostFtdcForQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcForQuoteField> c(m, "CThostFtdcForQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ForQuoteRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ForQuoteLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ForQuoteStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, BrokerForQutoSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteField, MacAddress);
}
void generate_class_CThostFtdcQryForQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryForQuoteField> c(m, "CThostFtdcQryForQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteField, InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteField, InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteField, InvestUnitID);
}
void generate_class_CThostFtdcExchangeForQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeForQuoteField> c(m, "CThostFtdcExchangeForQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, ForQuoteLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, ForQuoteStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeForQuoteField, MacAddress);
}
void generate_class_CThostFtdcQryExchangeForQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeForQuoteField> c(m, "CThostFtdcQryExchangeForQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeForQuoteField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeForQuoteField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeForQuoteField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeForQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeForQuoteField, TraderID);
}
void generate_class_CThostFtdcInputQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputQuoteField> c(m, "CThostFtdcInputQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, QuoteRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, AskPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, BidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, AskVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, BidVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, AskOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, BidOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, AskHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, BidHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, AskOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, BidOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, ForQuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteField, MacAddress);
}
void generate_class_CThostFtdcInputQuoteActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputQuoteActionField> c(m, "CThostFtdcInputQuoteActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, QuoteActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, QuoteRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, QuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputQuoteActionField, MacAddress);
}
void generate_class_CThostFtdcQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQuoteField> c(m, "CThostFtdcQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, QuoteRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, AskPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, AskVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BidVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, AskOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BidOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, AskHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BidHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, QuoteLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, QuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, QuoteStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, AskOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BidOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BrokerQuoteSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, AskOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BidOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, ForQuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteField, MacAddress);
}
void generate_class_CThostFtdcQuoteActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQuoteActionField> c(m, "CThostFtdcQuoteActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, QuoteActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, QuoteRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, QuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, QuoteLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQuoteActionField, MacAddress);
}
void generate_class_CThostFtdcQryQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryQuoteField> c(m, "CThostFtdcQryQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, QuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteField, InvestUnitID);
}
void generate_class_CThostFtdcExchangeQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeQuoteField> c(m, "CThostFtdcExchangeQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, AskPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, BidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, AskVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, BidVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, AskOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, BidOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, AskHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, BidHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, QuoteLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, QuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, QuoteStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, AskOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, BidOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, ForQuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteField, MacAddress);
}
void generate_class_CThostFtdcQryExchangeQuoteField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeQuoteField> c(m, "CThostFtdcQryExchangeQuoteField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteField, TraderID);
}
void generate_class_CThostFtdcQryQuoteActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryQuoteActionField> c(m, "CThostFtdcQryQuoteActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryQuoteActionField, ExchangeID);
}
void generate_class_CThostFtdcExchangeQuoteActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeQuoteActionField> c(m, "CThostFtdcExchangeQuoteActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, QuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, QuoteLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeQuoteActionField, MacAddress);
}
void generate_class_CThostFtdcQryExchangeQuoteActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeQuoteActionField> c(m, "CThostFtdcQryExchangeQuoteActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeQuoteActionField, TraderID);
}
void generate_class_CThostFtdcOptionInstrDeltaField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionInstrDeltaField> c(m, "CThostFtdcOptionInstrDeltaField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrDeltaField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrDeltaField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrDeltaField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrDeltaField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionInstrDeltaField, Delta);
}
void generate_class_CThostFtdcForQuoteRspField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcForQuoteRspField> c(m, "CThostFtdcForQuoteRspField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteRspField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteRspField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteRspField, ForQuoteSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteRspField, ForQuoteTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteRspField, ActionDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteRspField, ExchangeID);
}
void generate_class_CThostFtdcStrikeOffsetField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcStrikeOffsetField> c(m, "CThostFtdcStrikeOffsetField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcStrikeOffsetField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcStrikeOffsetField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcStrikeOffsetField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcStrikeOffsetField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcStrikeOffsetField, Offset);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcStrikeOffsetField, OffsetType);
}
void generate_class_CThostFtdcQryStrikeOffsetField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryStrikeOffsetField> c(m, "CThostFtdcQryStrikeOffsetField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryStrikeOffsetField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryStrikeOffsetField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryStrikeOffsetField, InstrumentID);
}
void generate_class_CThostFtdcInputBatchOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputBatchOrderActionField> c(m, "CThostFtdcInputBatchOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputBatchOrderActionField, MacAddress);
}
void generate_class_CThostFtdcBatchOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBatchOrderActionField> c(m, "CThostFtdcBatchOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBatchOrderActionField, MacAddress);
}
void generate_class_CThostFtdcExchangeBatchOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeBatchOrderActionField> c(m, "CThostFtdcExchangeBatchOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeBatchOrderActionField, MacAddress);
}
void generate_class_CThostFtdcQryBatchOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBatchOrderActionField> c(m, "CThostFtdcQryBatchOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBatchOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBatchOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBatchOrderActionField, ExchangeID);
}
void generate_class_CThostFtdcCombInstrumentGuardField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCombInstrumentGuardField> c(m, "CThostFtdcCombInstrumentGuardField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombInstrumentGuardField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombInstrumentGuardField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombInstrumentGuardField, GuarantRatio);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombInstrumentGuardField, ExchangeID);
}
void generate_class_CThostFtdcQryCombInstrumentGuardField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryCombInstrumentGuardField> c(m, "CThostFtdcQryCombInstrumentGuardField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombInstrumentGuardField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombInstrumentGuardField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombInstrumentGuardField, ExchangeID);
}
void generate_class_CThostFtdcInputCombActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputCombActionField> c(m, "CThostFtdcInputCombActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, CombActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, CombDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputCombActionField, InvestUnitID);
}
void generate_class_CThostFtdcCombActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCombActionField> c(m, "CThostFtdcCombActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, CombActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, CombDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, ActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, ComTradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombActionField, InvestUnitID);
}
void generate_class_CThostFtdcQryCombActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryCombActionField> c(m, "CThostFtdcQryCombActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombActionField, InvestUnitID);
}
void generate_class_CThostFtdcExchangeCombActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeCombActionField> c(m, "CThostFtdcExchangeCombActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, CombDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, ActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, ComTradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeCombActionField, BranchID);
}
void generate_class_CThostFtdcQryExchangeCombActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeCombActionField> c(m, "CThostFtdcQryExchangeCombActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeCombActionField, TraderID);
}
void generate_class_CThostFtdcProductExchRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcProductExchRateField> c(m, "CThostFtdcProductExchRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductExchRateField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductExchRateField, QuoteCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductExchRateField, ExchangeRate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductExchRateField, ExchangeID);
}
void generate_class_CThostFtdcQryProductExchRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryProductExchRateField> c(m, "CThostFtdcQryProductExchRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryProductExchRateField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryProductExchRateField, ExchangeID);
}
void generate_class_CThostFtdcQryForQuoteParamField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryForQuoteParamField> c(m, "CThostFtdcQryForQuoteParamField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteParamField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteParamField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryForQuoteParamField, ExchangeID);
}
void generate_class_CThostFtdcForQuoteParamField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcForQuoteParamField> c(m, "CThostFtdcForQuoteParamField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteParamField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteParamField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteParamField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteParamField, LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForQuoteParamField, PriceInterval);
}
void generate_class_CThostFtdcMMOptionInstrCommRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMMOptionInstrCommRateField> c(m, "CThostFtdcMMOptionInstrCommRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, OpenRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, OpenRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, CloseRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, CloseRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, CloseTodayRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, CloseTodayRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, StrikeRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMOptionInstrCommRateField, StrikeRatioByVolume);
}
void generate_class_CThostFtdcQryMMOptionInstrCommRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryMMOptionInstrCommRateField> c(m, "CThostFtdcQryMMOptionInstrCommRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMMOptionInstrCommRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMMOptionInstrCommRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMMOptionInstrCommRateField, InstrumentID);
}
void generate_class_CThostFtdcMMInstrumentCommissionRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMMInstrumentCommissionRateField> c(m, "CThostFtdcMMInstrumentCommissionRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, OpenRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, OpenRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, CloseRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, CloseRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, CloseTodayRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMMInstrumentCommissionRateField, CloseTodayRatioByVolume);
}
void generate_class_CThostFtdcQryMMInstrumentCommissionRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryMMInstrumentCommissionRateField> c(m, "CThostFtdcQryMMInstrumentCommissionRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMMInstrumentCommissionRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMMInstrumentCommissionRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMMInstrumentCommissionRateField, InstrumentID);
}
void generate_class_CThostFtdcInstrumentOrderCommRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentOrderCommRateField> c(m, "CThostFtdcInstrumentOrderCommRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, OrderCommByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, OrderActionCommByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentOrderCommRateField, InvestUnitID);
}
void generate_class_CThostFtdcQryInstrumentOrderCommRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInstrumentOrderCommRateField> c(m, "CThostFtdcQryInstrumentOrderCommRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentOrderCommRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentOrderCommRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentOrderCommRateField, InstrumentID);
}
void generate_class_CThostFtdcTradeParamField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradeParamField> c(m, "CThostFtdcTradeParamField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeParamField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeParamField, TradeParamID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeParamField, TradeParamValue);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeParamField, Memo);
}
void generate_class_CThostFtdcInstrumentMarginRateULField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentMarginRateULField> c(m, "CThostFtdcInstrumentMarginRateULField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, LongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, LongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, ShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateULField, ShortMarginRatioByVolume);
}
void generate_class_CThostFtdcFutureLimitPosiParamField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcFutureLimitPosiParamField> c(m, "CThostFtdcFutureLimitPosiParamField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureLimitPosiParamField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureLimitPosiParamField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureLimitPosiParamField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureLimitPosiParamField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureLimitPosiParamField, SpecOpenVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureLimitPosiParamField, ArbiOpenVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureLimitPosiParamField, OpenVolume);
}
void generate_class_CThostFtdcLoginForbiddenIPField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcLoginForbiddenIPField> c(m, "CThostFtdcLoginForbiddenIPField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginForbiddenIPField, IPAddress);
}
void generate_class_CThostFtdcIPListField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcIPListField> c(m, "CThostFtdcIPListField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcIPListField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcIPListField, IsWhite);
}
void generate_class_CThostFtdcInputOptionSelfCloseField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputOptionSelfCloseField> c(m, "CThostFtdcInputOptionSelfCloseField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, OptionSelfCloseRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, OptSelfCloseFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseField, MacAddress);
}
void generate_class_CThostFtdcInputOptionSelfCloseActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputOptionSelfCloseActionField> c(m, "CThostFtdcInputOptionSelfCloseActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, OptionSelfCloseActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, OptionSelfCloseRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, OptionSelfCloseSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOptionSelfCloseActionField, MacAddress);
}
void generate_class_CThostFtdcOptionSelfCloseField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionSelfCloseField> c(m, "CThostFtdcOptionSelfCloseField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, OptionSelfCloseRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, OptSelfCloseFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, OptionSelfCloseLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, OptionSelfCloseSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, ExecResult);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, BrokerOptionSelfCloseSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseField, MacAddress);
}
void generate_class_CThostFtdcOptionSelfCloseActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOptionSelfCloseActionField> c(m, "CThostFtdcOptionSelfCloseActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, OptionSelfCloseActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, OptionSelfCloseRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, OptionSelfCloseSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, OptionSelfCloseLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOptionSelfCloseActionField, MacAddress);
}
void generate_class_CThostFtdcQryOptionSelfCloseField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryOptionSelfCloseField> c(m, "CThostFtdcQryOptionSelfCloseField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseField, OptionSelfCloseSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseField, InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseField, InsertTimeEnd);
}
void generate_class_CThostFtdcExchangeOptionSelfCloseField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeOptionSelfCloseField> c(m, "CThostFtdcExchangeOptionSelfCloseField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, OptSelfCloseFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, OptionSelfCloseLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, OptionSelfCloseSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, ExecResult);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseField, MacAddress);
}
void generate_class_CThostFtdcQryOptionSelfCloseActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryOptionSelfCloseActionField> c(m, "CThostFtdcQryOptionSelfCloseActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOptionSelfCloseActionField, ExchangeID);
}
void generate_class_CThostFtdcExchangeOptionSelfCloseActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeOptionSelfCloseActionField> c(m, "CThostFtdcExchangeOptionSelfCloseActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, OptionSelfCloseSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, OptionSelfCloseLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOptionSelfCloseActionField, OptSelfCloseFlag);
}
void generate_class_CThostFtdcSyncDelaySwapField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncDelaySwapField> c(m, "CThostFtdcSyncDelaySwapField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, DelaySwapSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, FromCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, FromAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, FromFrozenSwap);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, FromRemainSwap);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, ToCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDelaySwapField, ToAmount);
}
void generate_class_CThostFtdcQrySyncDelaySwapField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySyncDelaySwapField> c(m, "CThostFtdcQrySyncDelaySwapField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySyncDelaySwapField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySyncDelaySwapField, DelaySwapSeqNo);
}
void generate_class_CThostFtdcInvestUnitField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestUnitField> c(m, "CThostFtdcInvestUnitField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, InvestorUnitName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, InvestorGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, CommModelID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, MarginModelID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestUnitField, CurrencyID);
}
void generate_class_CThostFtdcQryInvestUnitField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInvestUnitField> c(m, "CThostFtdcQryInvestUnitField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestUnitField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestUnitField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestUnitField, InvestUnitID);
}
void generate_class_CThostFtdcSecAgentCheckModeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSecAgentCheckModeField> c(m, "CThostFtdcSecAgentCheckModeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentCheckModeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentCheckModeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentCheckModeField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentCheckModeField, BrokerSecAgentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentCheckModeField, CheckSelfAccount);
}
void generate_class_CThostFtdcSecAgentTradeInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSecAgentTradeInfoField> c(m, "CThostFtdcSecAgentTradeInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentTradeInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentTradeInfoField, BrokerSecAgentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentTradeInfoField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentTradeInfoField, LongCustomerName);
}
void generate_class_CThostFtdcMarketDataField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataField> c(m, "CThostFtdcMarketDataField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, PreSettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, PreClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, PreOpenInterest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, HighestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, LowestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, OpenInterest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, SettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, UpperLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, LowerLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, PreDelta);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, CurrDelta);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, UpdateMillisec);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataField, ActionDay);
}
void generate_class_CThostFtdcMarketDataBaseField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataBaseField> c(m, "CThostFtdcMarketDataBaseField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBaseField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreSettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreOpenInterest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreDelta);
}
void generate_class_CThostFtdcMarketDataStaticField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataStaticField> c(m, "CThostFtdcMarketDataStaticField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, HighestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, LowestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, UpperLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, LowerLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, SettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataStaticField, CurrDelta);
}
void generate_class_CThostFtdcMarketDataLastMatchField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataLastMatchField> c(m, "CThostFtdcMarketDataLastMatchField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, OpenInterest);
}
void generate_class_CThostFtdcMarketDataBestPriceField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataBestPriceField> c(m, "CThostFtdcMarketDataBestPriceField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, BidPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, BidVolume1);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, AskPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, AskVolume1);
}
void generate_class_CThostFtdcMarketDataBid23Field(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataBid23Field> c(m, "CThostFtdcMarketDataBid23Field");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidVolume3);
}
void generate_class_CThostFtdcMarketDataAsk23Field(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataAsk23Field> c(m, "CThostFtdcMarketDataAsk23Field");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskVolume3);
}
void generate_class_CThostFtdcMarketDataBid45Field(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataBid45Field> c(m, "CThostFtdcMarketDataBid45Field");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidVolume5);
}
