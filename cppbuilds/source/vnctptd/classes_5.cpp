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


void generate_class_CThostFtdcExchangeStockDisposalField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeStockDisposalField>(m, "CThostFtdcExchangeStockDisposalField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, Volume)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, StockDisposalType)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, StockDisposalLocalID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, ClientID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, TraderID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, InstallID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, StockDisposalStatus)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, NotifySequence)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, TradingDay)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, SettlementID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, InsertDate)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, InsertTime)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, BranchID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, StockDisposalSysID)
        .DEF_PROPERTY(CThostFtdcExchangeStockDisposalField, BusinessUnit)
    ;
}
void generate_class_CThostFtdcQryInvestorLevelField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInvestorLevelField>(m, "CThostFtdcQryInvestorLevelField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInvestorLevelField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInvestorLevelField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInvestorLevelField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryForQuoteParamField(pybind11::module &m)
{
    py::class_<CThostFtdcQryForQuoteParamField>(m, "CThostFtdcQryForQuoteParamField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryForQuoteParamField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryForQuoteParamField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryForQuoteParamField, ExchangeID)
    ;
}
void generate_class_CThostFtdcForQuoteParamField(pybind11::module &m)
{
    py::class_<CThostFtdcForQuoteParamField>(m, "CThostFtdcForQuoteParamField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcForQuoteParamField, BrokerID)
        .DEF_PROPERTY(CThostFtdcForQuoteParamField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcForQuoteParamField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcForQuoteParamField, LastPrice)
        .DEF_PROPERTY(CThostFtdcForQuoteParamField, PriceInterval)
    ;
}
void generate_class_CThostFtdcQryExecFreezeField(pybind11::module &m)
{
    py::class_<CThostFtdcQryExecFreezeField>(m, "CThostFtdcQryExecFreezeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryExecFreezeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryExecFreezeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryExecFreezeField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryExecFreezeField, ExchangeID)
    ;
}
void generate_class_CThostFtdcExecFreezeField(pybind11::module &m)
{
    py::class_<CThostFtdcExecFreezeField>(m, "CThostFtdcExecFreezeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExecFreezeField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcExecFreezeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExecFreezeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcExecFreezeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcExecFreezeField, PosiDirection)
        .DEF_PROPERTY(CThostFtdcExecFreezeField, OptionsType)
        .DEF_PROPERTY(CThostFtdcExecFreezeField, Volume)
        .DEF_PROPERTY(CThostFtdcExecFreezeField, FrozenAmount)
    ;
}
void generate_class_CThostFtdcMarketDataField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataField>(m, "CThostFtdcMarketDataField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataField, TradingDay)
        .DEF_PROPERTY(CThostFtdcMarketDataField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcMarketDataField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcMarketDataField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcMarketDataField, LastPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, PreSettlementPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, PreClosePrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, PreOpenInterest)
        .DEF_PROPERTY(CThostFtdcMarketDataField, OpenPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, HighestPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, LowestPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, Volume)
        .DEF_PROPERTY(CThostFtdcMarketDataField, Turnover)
        .DEF_PROPERTY(CThostFtdcMarketDataField, OpenInterest)
        .DEF_PROPERTY(CThostFtdcMarketDataField, ClosePrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, SettlementPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, UpperLimitPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, LowerLimitPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataField, PreDelta)
        .DEF_PROPERTY(CThostFtdcMarketDataField, CurrDelta)
        .DEF_PROPERTY(CThostFtdcMarketDataField, UpdateTime)
        .DEF_PROPERTY(CThostFtdcMarketDataField, UpdateMillisec)
        .DEF_PROPERTY(CThostFtdcMarketDataField, ActionDay)
    ;
}
void generate_class_CThostFtdcMarketDataBaseField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataBaseField>(m, "CThostFtdcMarketDataBaseField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataBaseField, TradingDay)
        .DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreSettlementPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreClosePrice)
        .DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreOpenInterest)
        .DEF_PROPERTY(CThostFtdcMarketDataBaseField, PreDelta)
    ;
}
void generate_class_CThostFtdcMarketDataStaticField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataStaticField>(m, "CThostFtdcMarketDataStaticField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, OpenPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, HighestPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, LowestPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, ClosePrice)
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, UpperLimitPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, LowerLimitPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, SettlementPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataStaticField, CurrDelta)
    ;
}
void generate_class_CThostFtdcMarketDataLastMatchField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataLastMatchField>(m, "CThostFtdcMarketDataLastMatchField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, LastPrice)
        .DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, Volume)
        .DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, Turnover)
        .DEF_PROPERTY(CThostFtdcMarketDataLastMatchField, OpenInterest)
    ;
}
void generate_class_CThostFtdcMarketDataBestPriceField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataBestPriceField>(m, "CThostFtdcMarketDataBestPriceField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, BidPrice1)
        .DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, BidVolume1)
        .DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, AskPrice1)
        .DEF_PROPERTY(CThostFtdcMarketDataBestPriceField, AskVolume1)
    ;
}
void generate_class_CThostFtdcMarketDataBid23Field(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataBid23Field>(m, "CThostFtdcMarketDataBid23Field")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidPrice2)
        .DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidVolume2)
        .DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidPrice3)
        .DEF_PROPERTY(CThostFtdcMarketDataBid23Field, BidVolume3)
    ;
}
void generate_class_CThostFtdcMarketDataAsk23Field(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataAsk23Field>(m, "CThostFtdcMarketDataAsk23Field")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskPrice2)
        .DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskVolume2)
        .DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskPrice3)
        .DEF_PROPERTY(CThostFtdcMarketDataAsk23Field, AskVolume3)
    ;
}
void generate_class_CThostFtdcMarketDataBid45Field(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataBid45Field>(m, "CThostFtdcMarketDataBid45Field")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidPrice4)
        .DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidVolume4)
        .DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidPrice5)
        .DEF_PROPERTY(CThostFtdcMarketDataBid45Field, BidVolume5)
    ;
}
void generate_class_CThostFtdcMarketDataAsk45Field(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataAsk45Field>(m, "CThostFtdcMarketDataAsk45Field")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskPrice4)
        .DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskVolume4)
        .DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskPrice5)
        .DEF_PROPERTY(CThostFtdcMarketDataAsk45Field, AskVolume5)
    ;
}
void generate_class_CThostFtdcMarketDataUpdateTimeField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataUpdateTimeField>(m, "CThostFtdcMarketDataUpdateTimeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, UpdateTime)
        .DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, UpdateMillisec)
        .DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, ActionDay)
        .DEF_PROPERTY(CThostFtdcMarketDataUpdateTimeField, ExchangeID)
    ;
}
void generate_class_CThostFtdcMarketDataExchangeField(pybind11::module &m)
{
    py::class_<CThostFtdcMarketDataExchangeField>(m, "CThostFtdcMarketDataExchangeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMarketDataExchangeField, ExchangeID)
    ;
}
void generate_class_CThostFtdcSpecificInstrumentField(pybind11::module &m)
{
    py::class_<CThostFtdcSpecificInstrumentField>(m, "CThostFtdcSpecificInstrumentField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSpecificInstrumentField, InstrumentID)
    ;
}
void generate_class_CThostFtdcInstrumentStatusField(pybind11::module &m)
{
    py::class_<CThostFtdcInstrumentStatusField>(m, "CThostFtdcInstrumentStatusField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, SettlementGroupID)
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, InstrumentStatus)
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, TradingSegmentSN)
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, EnterTime)
        .DEF_PROPERTY(CThostFtdcInstrumentStatusField, EnterReason)
    ;
}
void generate_class_CThostFtdcQryInstrumentStatusField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInstrumentStatusField>(m, "CThostFtdcQryInstrumentStatusField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInstrumentStatusField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryInstrumentStatusField, ExchangeInstID)
    ;
}
void generate_class_CThostFtdcInvestorAccountField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorAccountField>(m, "CThostFtdcInvestorAccountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorAccountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorAccountField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorAccountField, AccountID)
        .DEF_PROPERTY(CThostFtdcInvestorAccountField, CurrencyID)
    ;
}
void generate_class_CThostFtdcPositionProfitAlgorithmField(pybind11::module &m)
{
    py::class_<CThostFtdcPositionProfitAlgorithmField>(m, "CThostFtdcPositionProfitAlgorithmField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, BrokerID)
        .DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, AccountID)
        .DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, Algorithm)
        .DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, Memo)
        .DEF_PROPERTY(CThostFtdcPositionProfitAlgorithmField, CurrencyID)
    ;
}
void generate_class_CThostFtdcDiscountField(pybind11::module &m)
{
    py::class_<CThostFtdcDiscountField>(m, "CThostFtdcDiscountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcDiscountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcDiscountField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcDiscountField, InvestorID)
        .DEF_PROPERTY(CThostFtdcDiscountField, Discount)
    ;
}
void generate_class_CThostFtdcQryTransferBankField(pybind11::module &m)
{
    py::class_<CThostFtdcQryTransferBankField>(m, "CThostFtdcQryTransferBankField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryTransferBankField, BankID)
        .DEF_PROPERTY(CThostFtdcQryTransferBankField, BankBrchID)
    ;
}
void generate_class_CThostFtdcTransferBankField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferBankField>(m, "CThostFtdcTransferBankField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferBankField, BankID)
        .DEF_PROPERTY(CThostFtdcTransferBankField, BankBrchID)
        .DEF_PROPERTY(CThostFtdcTransferBankField, BankName)
        .DEF_PROPERTY(CThostFtdcTransferBankField, IsActive)
    ;
}
void generate_class_CThostFtdcQryInvestorPositionDetailField(pybind11::module &m)
{
    py::class_<CThostFtdcQryInvestorPositionDetailField>(m, "CThostFtdcQryInvestorPositionDetailField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, InvestorID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcQryInvestorPositionDetailField, ExchangeID)
    ;
}
void generate_class_CThostFtdcInvestorPositionDetailField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorPositionDetailField>(m, "CThostFtdcInvestorPositionDetailField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, Direction)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, OpenDate)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, TradeID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, Volume)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, OpenPrice)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, TradingDay)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, SettlementID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, TradeType)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CombInstrumentID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseProfitByDate)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseProfitByTrade)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, PositionProfitByDate)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, PositionProfitByTrade)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, Margin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, ExchMargin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, MarginRateByMoney)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, MarginRateByVolume)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, LastSettlementPrice)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, SettlementPrice)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseVolume)
        .DEF_PROPERTY(CThostFtdcInvestorPositionDetailField, CloseAmount)
    ;
}
void generate_class_CThostFtdcTradingAccountPasswordField(pybind11::module &m)
{
    py::class_<CThostFtdcTradingAccountPasswordField>(m, "CThostFtdcTradingAccountPasswordField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, AccountID)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, Password)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordField, CurrencyID)
    ;
}
void generate_class_CThostFtdcMDTraderOfferField(pybind11::module &m)
{
    py::class_<CThostFtdcMDTraderOfferField>(m, "CThostFtdcMDTraderOfferField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, TraderID)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, Password)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, InstallID)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, TraderConnectStatus)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectRequestDate)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectRequestTime)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, LastReportDate)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, LastReportTime)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectDate)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, ConnectTime)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, StartDate)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, StartTime)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, TradingDay)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, BrokerID)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, MaxTradeID)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, MaxOrderMessageReference)
        .DEF_PROPERTY(CThostFtdcMDTraderOfferField, BizType)
    ;
}
void generate_class_CThostFtdcQryMDTraderOfferField(pybind11::module &m)
{
    py::class_<CThostFtdcQryMDTraderOfferField>(m, "CThostFtdcQryMDTraderOfferField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryMDTraderOfferField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcQryMDTraderOfferField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcQryMDTraderOfferField, TraderID)
    ;
}
void generate_class_CThostFtdcQryNoticeField(pybind11::module &m)
{
    py::class_<CThostFtdcQryNoticeField>(m, "CThostFtdcQryNoticeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryNoticeField, BrokerID)
    ;
}
void generate_class_CThostFtdcNoticeField(pybind11::module &m)
{
    py::class_<CThostFtdcNoticeField>(m, "CThostFtdcNoticeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcNoticeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcNoticeField, Content)
        .DEF_PROPERTY(CThostFtdcNoticeField, SequenceLabel)
    ;
}
void generate_class_CThostFtdcUserRightField(pybind11::module &m)
{
    py::class_<CThostFtdcUserRightField>(m, "CThostFtdcUserRightField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcUserRightField, BrokerID)
        .DEF_PROPERTY(CThostFtdcUserRightField, UserID)
        .DEF_PROPERTY(CThostFtdcUserRightField, UserRightType)
        .DEF_PROPERTY(CThostFtdcUserRightField, IsForbidden)
    ;
}
void generate_class_CThostFtdcQrySettlementInfoConfirmField(pybind11::module &m)
{
    py::class_<CThostFtdcQrySettlementInfoConfirmField>(m, "CThostFtdcQrySettlementInfoConfirmField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQrySettlementInfoConfirmField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQrySettlementInfoConfirmField, InvestorID)
    ;
}
void generate_class_CThostFtdcLoadSettlementInfoField(pybind11::module &m)
{
    py::class_<CThostFtdcLoadSettlementInfoField>(m, "CThostFtdcLoadSettlementInfoField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLoadSettlementInfoField, BrokerID)
    ;
}
void generate_class_CThostFtdcBrokerWithdrawAlgorithmField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerWithdrawAlgorithmField>(m, "CThostFtdcBrokerWithdrawAlgorithmField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, WithdrawAlgorithm)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, UsingRatio)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, IncludeCloseProfit)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, AllWithoutTrade)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, AvailIncludeCloseProfit)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, IsBrokerUserEvent)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, FundMortgageRatio)
        .DEF_PROPERTY(CThostFtdcBrokerWithdrawAlgorithmField, BalanceAlgorithm)
    ;
}
void generate_class_CThostFtdcTradingAccountPasswordUpdateV1Field(pybind11::module &m)
{
    py::class_<CThostFtdcTradingAccountPasswordUpdateV1Field>(m, "CThostFtdcTradingAccountPasswordUpdateV1Field")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, InvestorID)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, OldPassword)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateV1Field, NewPassword)
    ;
}
void generate_class_CThostFtdcTradingAccountPasswordUpdateField(pybind11::module &m)
{
    py::class_<CThostFtdcTradingAccountPasswordUpdateField>(m, "CThostFtdcTradingAccountPasswordUpdateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, AccountID)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, OldPassword)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, NewPassword)
        .DEF_PROPERTY(CThostFtdcTradingAccountPasswordUpdateField, CurrencyID)
    ;
}
void generate_class_CThostFtdcQryCombinationLegField(pybind11::module &m)
{
    py::class_<CThostFtdcQryCombinationLegField>(m, "CThostFtdcQryCombinationLegField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryCombinationLegField, CombInstrumentID)
        .DEF_PROPERTY(CThostFtdcQryCombinationLegField, LegID)
        .DEF_PROPERTY(CThostFtdcQryCombinationLegField, LegInstrumentID)
    ;
}
void generate_class_CThostFtdcQrySyncStatusField(pybind11::module &m)
{
    py::class_<CThostFtdcQrySyncStatusField>(m, "CThostFtdcQrySyncStatusField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQrySyncStatusField, TradingDay)
    ;
}
void generate_class_CThostFtdcCombinationLegField(pybind11::module &m)
{
    py::class_<CThostFtdcCombinationLegField>(m, "CThostFtdcCombinationLegField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCombinationLegField, CombInstrumentID)
        .DEF_PROPERTY(CThostFtdcCombinationLegField, LegID)
        .DEF_PROPERTY(CThostFtdcCombinationLegField, LegInstrumentID)
        .DEF_PROPERTY(CThostFtdcCombinationLegField, Direction)
        .DEF_PROPERTY(CThostFtdcCombinationLegField, LegMultiple)
        .DEF_PROPERTY(CThostFtdcCombinationLegField, ImplyLevel)
    ;
}
void generate_class_CThostFtdcSyncStatusField(pybind11::module &m)
{
    py::class_<CThostFtdcSyncStatusField>(m, "CThostFtdcSyncStatusField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSyncStatusField, TradingDay)
        .DEF_PROPERTY(CThostFtdcSyncStatusField, DataSyncStatus)
    ;
}
void generate_class_CThostFtdcQryLinkManField(pybind11::module &m)
{
    py::class_<CThostFtdcQryLinkManField>(m, "CThostFtdcQryLinkManField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryLinkManField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryLinkManField, InvestorID)
    ;
}
void generate_class_CThostFtdcLinkManField(pybind11::module &m)
{
    py::class_<CThostFtdcLinkManField>(m, "CThostFtdcLinkManField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLinkManField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLinkManField, InvestorID)
        .DEF_PROPERTY(CThostFtdcLinkManField, PersonType)
        .DEF_PROPERTY(CThostFtdcLinkManField, IdentifiedCardType)
        .DEF_PROPERTY(CThostFtdcLinkManField, IdentifiedCardNo)
        .DEF_PROPERTY(CThostFtdcLinkManField, PersonName)
        .DEF_PROPERTY(CThostFtdcLinkManField, Telephone)
        .DEF_PROPERTY(CThostFtdcLinkManField, Address)
        .DEF_PROPERTY(CThostFtdcLinkManField, ZipCode)
        .DEF_PROPERTY(CThostFtdcLinkManField, Priority)
        .DEF_PROPERTY(CThostFtdcLinkManField, UOAZipCode)
        .DEF_PROPERTY(CThostFtdcLinkManField, PersonFullName)
    ;
}
void generate_class_CThostFtdcQryBrokerUserEventField(pybind11::module &m)
{
    py::class_<CThostFtdcQryBrokerUserEventField>(m, "CThostFtdcQryBrokerUserEventField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryBrokerUserEventField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryBrokerUserEventField, UserID)
        .DEF_PROPERTY(CThostFtdcQryBrokerUserEventField, UserEventType)
    ;
}
void generate_class_CThostFtdcBrokerUserEventField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerUserEventField>(m, "CThostFtdcBrokerUserEventField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, UserID)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, UserEventType)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, EventSequenceNo)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, EventDate)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, EventTime)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, UserEventInfo)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, InvestorID)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcBrokerUserEventField, ExchangeID)
    ;
}
void generate_class_CThostFtdcQryContractBankField(pybind11::module &m)
{
    py::class_<CThostFtdcQryContractBankField>(m, "CThostFtdcQryContractBankField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcQryContractBankField, BrokerID)
        .DEF_PROPERTY(CThostFtdcQryContractBankField, BankID)
        .DEF_PROPERTY(CThostFtdcQryContractBankField, BankBrchID)
    ;
}
void generate_class_CThostFtdcContractBankField(pybind11::module &m)
{
    py::class_<CThostFtdcContractBankField>(m, "CThostFtdcContractBankField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcContractBankField, BrokerID)
        .DEF_PROPERTY(CThostFtdcContractBankField, BankID)
        .DEF_PROPERTY(CThostFtdcContractBankField, BankBrchID)
        .DEF_PROPERTY(CThostFtdcContractBankField, BankName)
    ;
}
void generate_class_CThostFtdcInvestorPositionCombineDetailField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorPositionCombineDetailField>(m, "CThostFtdcInvestorPositionCombineDetailField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TradingDay)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, OpenDate)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, SettlementID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, ComTradeID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TradeID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, Direction)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TotalAmt)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, Margin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, ExchMargin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, MarginRateByMoney)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, MarginRateByVolume)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, LegID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, LegMultiple)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, CombInstrumentID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionCombineDetailField, TradeGroupID)
    ;
}
void generate_class_CThostFtdcParkedOrderField(pybind11::module &m)
{
    py::class_<CThostFtdcParkedOrderField>(m, "CThostFtdcParkedOrderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcParkedOrderField, BrokerID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, InvestorID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, OrderRef)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, UserID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, OrderPriceType)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, Direction)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, CombOffsetFlag)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, CombHedgeFlag)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, LimitPrice)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, VolumeTotalOriginal)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, TimeCondition)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, GTDDate)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, VolumeCondition)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, MinVolume)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, ContingentCondition)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, StopPrice)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, ForceCloseReason)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, IsAutoSuspend)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, BusinessUnit)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, RequestID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, UserForceClose)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, ParkedOrderID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, UserType)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, Status)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, ErrorID)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, ErrorMsg)
        .DEF_PROPERTY(CThostFtdcParkedOrderField, IsSwapOrder)
    ;
}

