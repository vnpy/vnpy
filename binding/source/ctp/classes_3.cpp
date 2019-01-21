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


void generate_class_CThostFtdcMarketDataAsk45Field(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataAsk45Field> c(m, "CThostFtdcMarketDataAsk45Field");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskVolume5);
}
void generate_class_CThostFtdcMarketDataUpdateTimeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataUpdateTimeField> c(m, "CThostFtdcMarketDataUpdateTimeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, UpdateMillisec);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, ActionDay);
}
void generate_class_CThostFtdcMarketDataExchangeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataExchangeField> c(m, "CThostFtdcMarketDataExchangeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataExchangeField, ExchangeID);
}
void generate_class_CThostFtdcSpecificInstrumentField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSpecificInstrumentField> c(m, "CThostFtdcSpecificInstrumentField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSpecificInstrumentField, InstrumentID);
}
void generate_class_CThostFtdcInstrumentStatusField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentStatusField> c(m, "CThostFtdcInstrumentStatusField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, SettlementGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, InstrumentStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, TradingSegmentSN);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, EnterTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentStatusField, EnterReason);
}
void generate_class_CThostFtdcQryInstrumentStatusField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInstrumentStatusField> c(m, "CThostFtdcQryInstrumentStatusField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentStatusField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentStatusField, ExchangeInstID);
}
void generate_class_CThostFtdcInvestorAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorAccountField> c(m, "CThostFtdcInvestorAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorAccountField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorAccountField, CurrencyID);
}
void generate_class_CThostFtdcPositionProfitAlgorithmField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcPositionProfitAlgorithmField> c(m, "CThostFtdcPositionProfitAlgorithmField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, Algorithm);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, Memo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, CurrencyID);
}
void generate_class_CThostFtdcDiscountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcDiscountField> c(m, "CThostFtdcDiscountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDiscountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDiscountField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDiscountField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDiscountField, Discount);
}
void generate_class_CThostFtdcQryTransferBankField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTransferBankField> c(m, "CThostFtdcQryTransferBankField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTransferBankField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTransferBankField, BankBrchID);
}
void generate_class_CThostFtdcTransferBankField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferBankField> c(m, "CThostFtdcTransferBankField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankField, BankBrchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankField, BankName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankField, IsActive);
}
void generate_class_CThostFtdcQryInvestorPositionDetailField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInvestorPositionDetailField> c(m, "CThostFtdcQryInvestorPositionDetailField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, InvestUnitID);
}
void generate_class_CThostFtdcInvestorPositionDetailField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorPositionDetailField> c(m, "CThostFtdcInvestorPositionDetailField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, TradeType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CombInstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseProfitByDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseProfitByTrade);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, PositionProfitByDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, PositionProfitByTrade);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, Margin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, ExchMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, MarginRateByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, MarginRateByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, LastSettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, SettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, InvestUnitID);
}
void generate_class_CThostFtdcTradingAccountPasswordField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingAccountPasswordField> c(m, "CThostFtdcTradingAccountPasswordField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, CurrencyID);
}
void generate_class_CThostFtdcMDTraderOfferField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMDTraderOfferField> c(m, "CThostFtdcMDTraderOfferField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, TraderConnectStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectRequestDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectRequestTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, LastReportDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, LastReportTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, StartDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, StartTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, MaxTradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMDTraderOfferField, MaxOrderMessageReference);
}
void generate_class_CThostFtdcQryMDTraderOfferField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryMDTraderOfferField> c(m, "CThostFtdcQryMDTraderOfferField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMDTraderOfferField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMDTraderOfferField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMDTraderOfferField, TraderID);
}
void generate_class_CThostFtdcQryNoticeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryNoticeField> c(m, "CThostFtdcQryNoticeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryNoticeField, BrokerID);
}
void generate_class_CThostFtdcNoticeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcNoticeField> c(m, "CThostFtdcNoticeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNoticeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNoticeField, Content);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNoticeField, SequenceLabel);
}
void generate_class_CThostFtdcUserRightField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcUserRightField> c(m, "CThostFtdcUserRightField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserRightField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserRightField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserRightField, UserRightType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserRightField, IsForbidden);
}
void generate_class_CThostFtdcQrySettlementInfoConfirmField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySettlementInfoConfirmField> c(m, "CThostFtdcQrySettlementInfoConfirmField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoConfirmField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoConfirmField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoConfirmField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySettlementInfoConfirmField, CurrencyID);
}
void generate_class_CThostFtdcLoadSettlementInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcLoadSettlementInfoField> c(m, "CThostFtdcLoadSettlementInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoadSettlementInfoField, BrokerID);
}
void generate_class_CThostFtdcBrokerWithdrawAlgorithmField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerWithdrawAlgorithmField> c(m, "CThostFtdcBrokerWithdrawAlgorithmField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, WithdrawAlgorithm);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, UsingRatio);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, IncludeCloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, AllWithoutTrade);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, AvailIncludeCloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, IsBrokerUserEvent);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, FundMortgageRatio);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, BalanceAlgorithm);
}
void generate_class_CThostFtdcTradingAccountPasswordUpdateV1Field(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingAccountPasswordUpdateV1Field> c(m, "CThostFtdcTradingAccountPasswordUpdateV1Field");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, OldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, NewPassword);
}
void generate_class_CThostFtdcTradingAccountPasswordUpdateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingAccountPasswordUpdateField> c(m, "CThostFtdcTradingAccountPasswordUpdateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, OldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, NewPassword);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, CurrencyID);
}
void generate_class_CThostFtdcQryCombinationLegField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryCombinationLegField> c(m, "CThostFtdcQryCombinationLegField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombinationLegField, CombInstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombinationLegField, LegID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCombinationLegField, LegInstrumentID);
}
void generate_class_CThostFtdcQrySyncStatusField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySyncStatusField> c(m, "CThostFtdcQrySyncStatusField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySyncStatusField, TradingDay);
}
void generate_class_CThostFtdcCombinationLegField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCombinationLegField> c(m, "CThostFtdcCombinationLegField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombinationLegField, CombInstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombinationLegField, LegID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombinationLegField, LegInstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombinationLegField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombinationLegField, LegMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCombinationLegField, ImplyLevel);
}
void generate_class_CThostFtdcSyncStatusField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncStatusField> c(m, "CThostFtdcSyncStatusField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncStatusField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncStatusField, DataSyncStatus);
}
void generate_class_CThostFtdcQryLinkManField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryLinkManField> c(m, "CThostFtdcQryLinkManField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryLinkManField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryLinkManField, InvestorID);
}
void generate_class_CThostFtdcLinkManField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcLinkManField> c(m, "CThostFtdcLinkManField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, PersonType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, IdentifiedCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, PersonName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, Priority);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, UOAZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLinkManField, PersonFullName);
}
void generate_class_CThostFtdcQryBrokerUserEventField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBrokerUserEventField> c(m, "CThostFtdcQryBrokerUserEventField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerUserEventField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerUserEventField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerUserEventField, UserEventType);
}
void generate_class_CThostFtdcBrokerUserEventField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerUserEventField> c(m, "CThostFtdcBrokerUserEventField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, UserEventType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, EventSequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, EventDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, EventTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, UserEventInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserEventField, InstrumentID);
}
void generate_class_CThostFtdcQryContractBankField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryContractBankField> c(m, "CThostFtdcQryContractBankField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryContractBankField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryContractBankField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryContractBankField, BankBrchID);
}
void generate_class_CThostFtdcContractBankField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcContractBankField> c(m, "CThostFtdcContractBankField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcContractBankField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcContractBankField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcContractBankField, BankBrchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcContractBankField, BankName);
}
void generate_class_CThostFtdcInvestorPositionCombineDetailField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorPositionCombineDetailField> c(m, "CThostFtdcInvestorPositionCombineDetailField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, ComTradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TotalAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, Margin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, ExchMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, MarginRateByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, MarginRateByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, LegID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, LegMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, CombInstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TradeGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, InvestUnitID);
}
void generate_class_CThostFtdcParkedOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcParkedOrderField> c(m, "CThostFtdcParkedOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, GTDDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, IsAutoSuspend);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, ParkedOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, UserType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, Status);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, IsSwapOrder);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderField, MacAddress);
}
void generate_class_CThostFtdcParkedOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcParkedOrderActionField> c(m, "CThostFtdcParkedOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, VolumeChange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, ParkedOrderActionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, UserType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, Status);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcParkedOrderActionField, MacAddress);
}
void generate_class_CThostFtdcQryParkedOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryParkedOrderField> c(m, "CThostFtdcQryParkedOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderField, InvestUnitID);
}
void generate_class_CThostFtdcQryParkedOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryParkedOrderActionField> c(m, "CThostFtdcQryParkedOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryParkedOrderActionField, InvestUnitID);
}
void generate_class_CThostFtdcRemoveParkedOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRemoveParkedOrderField> c(m, "CThostFtdcRemoveParkedOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderField, ParkedOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderField, InvestUnitID);
}
void generate_class_CThostFtdcRemoveParkedOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRemoveParkedOrderActionField> c(m, "CThostFtdcRemoveParkedOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderActionField, ParkedOrderActionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRemoveParkedOrderActionField, InvestUnitID);
}
void generate_class_CThostFtdcInvestorWithdrawAlgorithmField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorWithdrawAlgorithmField> c(m, "CThostFtdcInvestorWithdrawAlgorithmField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, UsingRatio);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorWithdrawAlgorithmField, FundMortgageRatio);
}
void generate_class_CThostFtdcQryInvestorPositionCombineDetailField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInvestorPositionCombineDetailField> c(m, "CThostFtdcQryInvestorPositionCombineDetailField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, CombInstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionCombineDetailField, InvestUnitID);
}
void generate_class_CThostFtdcMarketDataAveragePriceField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarketDataAveragePriceField> c(m, "CThostFtdcMarketDataAveragePriceField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarketDataAveragePriceField, AveragePrice);
}
void generate_class_CThostFtdcVerifyInvestorPasswordField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcVerifyInvestorPasswordField> c(m, "CThostFtdcVerifyInvestorPasswordField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyInvestorPasswordField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyInvestorPasswordField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyInvestorPasswordField, Password);
}
void generate_class_CThostFtdcUserIPField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcUserIPField> c(m, "CThostFtdcUserIPField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserIPField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserIPField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserIPField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserIPField, IPMask);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserIPField, MacAddress);
}
void generate_class_CThostFtdcTradingNoticeInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingNoticeInfoField> c(m, "CThostFtdcTradingNoticeInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, SendTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, FieldContent);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, SequenceSeries);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeInfoField, InvestUnitID);
}
void generate_class_CThostFtdcTradingNoticeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingNoticeField> c(m, "CThostFtdcTradingNoticeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, SequenceSeries);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, SendTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, FieldContent);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingNoticeField, InvestUnitID);
}
void generate_class_CThostFtdcQryTradingNoticeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTradingNoticeField> c(m, "CThostFtdcQryTradingNoticeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingNoticeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingNoticeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingNoticeField, InvestUnitID);
}
void generate_class_CThostFtdcQryErrOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryErrOrderField> c(m, "CThostFtdcQryErrOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrOrderField, InvestorID);
}
void generate_class_CThostFtdcErrOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcErrOrderField> c(m, "CThostFtdcErrOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, GTDDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, IsAutoSuspend);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, IsSwapOrder);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderField, MacAddress);
}
void generate_class_CThostFtdcErrorConditionalOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcErrorConditionalOrderField> c(m, "CThostFtdcErrorConditionalOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, GTDDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, IsAutoSuspend);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, VolumeTotal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ActiveTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SuspendTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ActiveTraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BrokerOrderSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, RelativeOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ZCETotalTradedVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, IsSwapOrder);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrorConditionalOrderField, MacAddress);
}
void generate_class_CThostFtdcQryErrOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryErrOrderActionField> c(m, "CThostFtdcQryErrOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryErrOrderActionField, InvestorID);
}
void generate_class_CThostFtdcErrOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcErrOrderActionField> c(m, "CThostFtdcErrOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, VolumeChange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcErrOrderActionField, ErrorMsg);
}
void generate_class_CThostFtdcQryExchangeSequenceField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeSequenceField> c(m, "CThostFtdcQryExchangeSequenceField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeSequenceField, ExchangeID);
}
void generate_class_CThostFtdcExchangeSequenceField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeSequenceField> c(m, "CThostFtdcExchangeSequenceField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeSequenceField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeSequenceField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeSequenceField, MarketStatus);
}
void generate_class_CThostFtdcQueryMaxOrderVolumeWithPriceField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQueryMaxOrderVolumeWithPriceField> c(m, "CThostFtdcQueryMaxOrderVolumeWithPriceField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, MaxVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, Price);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeWithPriceField, InvestUnitID);
}
void generate_class_CThostFtdcQryBrokerTradingParamsField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBrokerTradingParamsField> c(m, "CThostFtdcQryBrokerTradingParamsField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerTradingParamsField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerTradingParamsField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerTradingParamsField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerTradingParamsField, AccountID);
}
void generate_class_CThostFtdcBrokerTradingParamsField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerTradingParamsField> c(m, "CThostFtdcBrokerTradingParamsField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, MarginPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, Algorithm);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, AvailIncludeCloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, OptionRoyaltyPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingParamsField, AccountID);
}
void generate_class_CThostFtdcQryBrokerTradingAlgosField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBrokerTradingAlgosField> c(m, "CThostFtdcQryBrokerTradingAlgosField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerTradingAlgosField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerTradingAlgosField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerTradingAlgosField, InstrumentID);
}
void generate_class_CThostFtdcBrokerTradingAlgosField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerTradingAlgosField> c(m, "CThostFtdcBrokerTradingAlgosField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, HandlePositionAlgoID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, FindMarginRateAlgoID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerTradingAlgosField, HandleTradingAccountAlgoID);
}
void generate_class_CThostFtdcQueryBrokerDepositField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQueryBrokerDepositField> c(m, "CThostFtdcQueryBrokerDepositField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryBrokerDepositField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryBrokerDepositField, ExchangeID);
}
void generate_class_CThostFtdcBrokerDepositField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerDepositField> c(m, "CThostFtdcBrokerDepositField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, PreBalance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, CurrMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, Balance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, Deposit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, Withdraw);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, Available);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, Reserve);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerDepositField, FrozenMargin);
}
void generate_class_CThostFtdcQryCFMMCBrokerKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryCFMMCBrokerKeyField> c(m, "CThostFtdcQryCFMMCBrokerKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCFMMCBrokerKeyField, BrokerID);
}
void generate_class_CThostFtdcCFMMCBrokerKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCFMMCBrokerKeyField> c(m, "CThostFtdcCFMMCBrokerKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, CreateDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, CreateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, KeyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, CurrentKey);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCBrokerKeyField, KeyKind);
}
void generate_class_CThostFtdcCFMMCTradingAccountKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCFMMCTradingAccountKeyField> c(m, "CThostFtdcCFMMCTradingAccountKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, KeyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountKeyField, CurrentKey);
}
void generate_class_CThostFtdcQryCFMMCTradingAccountKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryCFMMCTradingAccountKeyField> c(m, "CThostFtdcQryCFMMCTradingAccountKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCFMMCTradingAccountKeyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCFMMCTradingAccountKeyField, InvestorID);
}
void generate_class_CThostFtdcBrokerUserOTPParamField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerUserOTPParamField> c(m, "CThostFtdcBrokerUserOTPParamField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, OTPVendorsID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, SerialNumber);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, AuthKey);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, LastDrift);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, LastSuccess);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserOTPParamField, OTPType);
}
void generate_class_CThostFtdcManualSyncBrokerUserOTPField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcManualSyncBrokerUserOTPField> c(m, "CThostFtdcManualSyncBrokerUserOTPField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, OTPType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, FirstOTP);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcManualSyncBrokerUserOTPField, SecondOTP);
}
void generate_class_CThostFtdcCommRateModelField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCommRateModelField> c(m, "CThostFtdcCommRateModelField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCommRateModelField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCommRateModelField, CommModelID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCommRateModelField, CommModelName);
}
void generate_class_CThostFtdcQryCommRateModelField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryCommRateModelField> c(m, "CThostFtdcQryCommRateModelField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCommRateModelField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCommRateModelField, CommModelID);
}
void generate_class_CThostFtdcMarginModelField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMarginModelField> c(m, "CThostFtdcMarginModelField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarginModelField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarginModelField, MarginModelID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMarginModelField, MarginModelName);
}
void generate_class_CThostFtdcQryMarginModelField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryMarginModelField> c(m, "CThostFtdcQryMarginModelField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMarginModelField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryMarginModelField, MarginModelID);
}
void generate_class_CThostFtdcEWarrantOffsetField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcEWarrantOffsetField> c(m, "CThostFtdcEWarrantOffsetField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcEWarrantOffsetField, InvestUnitID);
}
void generate_class_CThostFtdcQryEWarrantOffsetField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryEWarrantOffsetField> c(m, "CThostFtdcQryEWarrantOffsetField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryEWarrantOffsetField, InvestUnitID);
}
void generate_class_CThostFtdcQryInvestorProductGroupMarginField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInvestorProductGroupMarginField> c(m, "CThostFtdcQryInvestorProductGroupMarginField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, ProductGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorProductGroupMarginField, InvestUnitID);
}
void generate_class_CThostFtdcInvestorProductGroupMarginField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorProductGroupMarginField> c(m, "CThostFtdcInvestorProductGroupMarginField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ProductGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, FrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongFrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortFrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, UseMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongUseMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortUseMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ExchMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongExchMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortExchMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, FrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, Commission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, FrozenCash);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, CashIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, OffsetAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongOffsetAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortOffsetAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ExchOffsetAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, LongExchOffsetAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ShortExchOffsetAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorProductGroupMarginField, InvestUnitID);
}
void generate_class_CThostFtdcQueryCFMMCTradingAccountTokenField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQueryCFMMCTradingAccountTokenField> c(m, "CThostFtdcQueryCFMMCTradingAccountTokenField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryCFMMCTradingAccountTokenField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryCFMMCTradingAccountTokenField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryCFMMCTradingAccountTokenField, InvestUnitID);
}
void generate_class_CThostFtdcCFMMCTradingAccountTokenField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCFMMCTradingAccountTokenField> c(m, "CThostFtdcCFMMCTradingAccountTokenField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, KeyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCFMMCTradingAccountTokenField, Token);
}
void generate_class_CThostFtdcQryProductGroupField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryProductGroupField> c(m, "CThostFtdcQryProductGroupField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryProductGroupField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryProductGroupField, ExchangeID);
}
void generate_class_CThostFtdcProductGroupField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcProductGroupField> c(m, "CThostFtdcProductGroupField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductGroupField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductGroupField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductGroupField, ProductGroupID);
}
void generate_class_CThostFtdcBulletinField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBulletinField> c(m, "CThostFtdcBulletinField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, BulletinID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, NewsType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, NewsUrgency);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, SendTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, Abstract);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, ComeFrom);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, Content);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, URLLink);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBulletinField, MarketID);
}
void generate_class_CThostFtdcQryBulletinField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBulletinField> c(m, "CThostFtdcQryBulletinField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBulletinField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBulletinField, BulletinID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBulletinField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBulletinField, NewsType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBulletinField, NewsUrgency);
}
void generate_class_CThostFtdcReqOpenAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqOpenAccountField> c(m, "CThostFtdcReqOpenAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, CashExchangeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqOpenAccountField, LongCustomerName);
}
void generate_class_CThostFtdcReqCancelAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqCancelAccountField> c(m, "CThostFtdcReqCancelAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, CashExchangeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqCancelAccountField, LongCustomerName);
}
void generate_class_CThostFtdcReqChangeAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqChangeAccountField> c(m, "CThostFtdcReqChangeAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, NewBankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, NewBankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqChangeAccountField, LongCustomerName);
}
void generate_class_CThostFtdcReqTransferField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqTransferField> c(m, "CThostFtdcReqTransferField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, TradeAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, FutureFetchAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, FeePayFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BrokerFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, Message);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqTransferField, LongCustomerName);
}
void generate_class_CThostFtdcRspTransferField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspTransferField> c(m, "CThostFtdcRspTransferField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, TradeAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, FutureFetchAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, FeePayFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BrokerFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, Message);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspTransferField, LongCustomerName);
}
void generate_class_CThostFtdcReqRepealField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqRepealField> c(m, "CThostFtdcReqRepealField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, RepealTimeInterval);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, RepealedTimes);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankRepealFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BrokerRepealFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, PlateRepealSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankRepealSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, FutureRepealSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, TradeAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, FutureFetchAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, FeePayFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BrokerFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, Message);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqRepealField, LongCustomerName);
}
void generate_class_CThostFtdcRspRepealField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspRepealField> c(m, "CThostFtdcRspRepealField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, RepealTimeInterval);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, RepealedTimes);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankRepealFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BrokerRepealFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, PlateRepealSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankRepealSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, FutureRepealSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, TradeAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, FutureFetchAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, FeePayFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BrokerFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, Message);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspRepealField, LongCustomerName);
}
void generate_class_CThostFtdcReqQueryAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqQueryAccountField> c(m, "CThostFtdcReqQueryAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryAccountField, LongCustomerName);
}
void generate_class_CThostFtdcRspQueryAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspQueryAccountField> c(m, "CThostFtdcRspQueryAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankUseAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, BankFetchAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryAccountField, LongCustomerName);
}
void generate_class_CThostFtdcFutureSignIOField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcFutureSignIOField> c(m, "CThostFtdcFutureSignIOField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFutureSignIOField, TID);
}
void generate_class_CThostFtdcRspFutureSignInField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspFutureSignInField> c(m, "CThostFtdcRspFutureSignInField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, PinKey);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignInField, MacKey);
}
void generate_class_CThostFtdcReqFutureSignOutField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqFutureSignOutField> c(m, "CThostFtdcReqFutureSignOutField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqFutureSignOutField, TID);
}
void generate_class_CThostFtdcRspFutureSignOutField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspFutureSignOutField> c(m, "CThostFtdcRspFutureSignOutField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspFutureSignOutField, ErrorMsg);
}
void generate_class_CThostFtdcReqQueryTradeResultBySerialField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqQueryTradeResultBySerialField> c(m, "CThostFtdcReqQueryTradeResultBySerialField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, Reference);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, RefrenceIssureType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, RefrenceIssure);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, TradeAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqQueryTradeResultBySerialField, LongCustomerName);
}
void generate_class_CThostFtdcRspQueryTradeResultBySerialField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspQueryTradeResultBySerialField> c(m, "CThostFtdcRspQueryTradeResultBySerialField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, Reference);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, RefrenceIssureType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, RefrenceIssure);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, OriginReturnCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, OriginDescrInfoForReturnCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, TradeAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspQueryTradeResultBySerialField, Digest);
}
void generate_class_CThostFtdcReqDayEndFileReadyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqDayEndFileReadyField> c(m, "CThostFtdcReqDayEndFileReadyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, FileBusinessCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqDayEndFileReadyField, Digest);
}
void generate_class_CThostFtdcReturnResultField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReturnResultField> c(m, "CThostFtdcReturnResultField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReturnResultField, ReturnCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReturnResultField, DescrInfoForReturnCode);
}
