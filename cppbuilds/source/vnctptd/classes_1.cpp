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


void generate_class_CThostFtdcDisseminationField(pybind11::module &m)
{
    py::class_<CThostFtdcDisseminationField>(m, "CThostFtdcDisseminationField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcDisseminationField, SequenceSeries)
        .DEF_PROPERTY(CThostFtdcDisseminationField, SequenceNo)
    ;
}
void generate_class_CThostFtdcReqUserLoginField(pybind11::module &m)
{
    py::class_<CThostFtdcReqUserLoginField>(m, "CThostFtdcReqUserLoginField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, TradingDay)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, BrokerID)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, UserID)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, Password)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, InterfaceProductInfo)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, ProtocolInfo)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, MacAddress)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, OneTimePassword)
        .DEF_PROPERTY(CThostFtdcReqUserLoginField, ClientIPAddress)
    ;
}
void generate_class_CThostFtdcRspUserLoginField(pybind11::module &m)
{
    py::class_<CThostFtdcRspUserLoginField>(m, "CThostFtdcRspUserLoginField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, TradingDay)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, LoginTime)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, BrokerID)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, UserID)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, SystemName)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, FrontID)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, SessionID)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, MaxOrderRef)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, SHFETime)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, DCETime)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, CZCETime)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, FFEXTime)
        .DEF_PROPERTY(CThostFtdcRspUserLoginField, INETime)
    ;
}
void generate_class_CThostFtdcUserLogoutField(pybind11::module &m)
{
    py::class_<CThostFtdcUserLogoutField>(m, "CThostFtdcUserLogoutField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcUserLogoutField, BrokerID)
        .DEF_PROPERTY(CThostFtdcUserLogoutField, UserID)
    ;
}
void generate_class_CThostFtdcForceUserLogoutField(pybind11::module &m)
{
    py::class_<CThostFtdcForceUserLogoutField>(m, "CThostFtdcForceUserLogoutField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcForceUserLogoutField, BrokerID)
        .DEF_PROPERTY(CThostFtdcForceUserLogoutField, UserID)
    ;
}
void generate_class_CThostFtdcReqAuthenticateField(pybind11::module &m)
{
    py::class_<CThostFtdcReqAuthenticateField>(m, "CThostFtdcReqAuthenticateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcReqAuthenticateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcReqAuthenticateField, UserID)
        .DEF_PROPERTY(CThostFtdcReqAuthenticateField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcReqAuthenticateField, AuthCode)
    ;
}
void generate_class_CThostFtdcRspAuthenticateField(pybind11::module &m)
{
    py::class_<CThostFtdcRspAuthenticateField>(m, "CThostFtdcRspAuthenticateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcRspAuthenticateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcRspAuthenticateField, UserID)
        .DEF_PROPERTY(CThostFtdcRspAuthenticateField, UserProductInfo)
    ;
}
void generate_class_CThostFtdcAuthenticationInfoField(pybind11::module &m)
{
    py::class_<CThostFtdcAuthenticationInfoField>(m, "CThostFtdcAuthenticationInfoField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcAuthenticationInfoField, BrokerID)
        .DEF_PROPERTY(CThostFtdcAuthenticationInfoField, UserID)
        .DEF_PROPERTY(CThostFtdcAuthenticationInfoField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcAuthenticationInfoField, AuthInfo)
        .DEF_PROPERTY(CThostFtdcAuthenticationInfoField, IsResult)
    ;
}
void generate_class_CThostFtdcTransferHeaderField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferHeaderField>(m, "CThostFtdcTransferHeaderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, Version)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeCode)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeDate)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeTime)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeSerial)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, FutureID)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, BankID)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, BankBrchID)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, OperNo)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, DeviceID)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, RecordNum)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, SessionID)
        .DEF_PROPERTY(CThostFtdcTransferHeaderField, RequestID)
    ;
}
void generate_class_CThostFtdcTransferBankToFutureReqField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferBankToFutureReqField>(m, "CThostFtdcTransferBankToFutureReqField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, FutureAccount)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, FuturePwdFlag)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, FutureAccPwd)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, TradeAmt)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, CustFee)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, CurrencyCode)
    ;
}
void generate_class_CThostFtdcTransferBankToFutureRspField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferBankToFutureRspField>(m, "CThostFtdcTransferBankToFutureRspField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, RetCode)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, RetInfo)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, FutureAccount)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, TradeAmt)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, CustFee)
        .DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, CurrencyCode)
    ;
}
void generate_class_CThostFtdcTransferFutureToBankReqField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferFutureToBankReqField>(m, "CThostFtdcTransferFutureToBankReqField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, FutureAccount)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, FuturePwdFlag)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, FutureAccPwd)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, TradeAmt)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, CustFee)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, CurrencyCode)
    ;
}
void generate_class_CThostFtdcTransferFutureToBankRspField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferFutureToBankRspField>(m, "CThostFtdcTransferFutureToBankRspField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, RetCode)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, RetInfo)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, FutureAccount)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, TradeAmt)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, CustFee)
        .DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, CurrencyCode)
    ;
}
void generate_class_CThostFtdcTransferQryBankReqField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferQryBankReqField>(m, "CThostFtdcTransferQryBankReqField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferQryBankReqField, FutureAccount)
        .DEF_PROPERTY(CThostFtdcTransferQryBankReqField, FuturePwdFlag)
        .DEF_PROPERTY(CThostFtdcTransferQryBankReqField, FutureAccPwd)
        .DEF_PROPERTY(CThostFtdcTransferQryBankReqField, CurrencyCode)
    ;
}
void generate_class_CThostFtdcTransferQryBankRspField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferQryBankRspField>(m, "CThostFtdcTransferQryBankRspField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferQryBankRspField, RetCode)
        .DEF_PROPERTY(CThostFtdcTransferQryBankRspField, RetInfo)
        .DEF_PROPERTY(CThostFtdcTransferQryBankRspField, FutureAccount)
        .DEF_PROPERTY(CThostFtdcTransferQryBankRspField, TradeAmt)
        .DEF_PROPERTY(CThostFtdcTransferQryBankRspField, UseAmt)
        .DEF_PROPERTY(CThostFtdcTransferQryBankRspField, FetchAmt)
        .DEF_PROPERTY(CThostFtdcTransferQryBankRspField, CurrencyCode)
    ;
}
void generate_class_CThostFtdcTransferQryDetailReqField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferQryDetailReqField>(m, "CThostFtdcTransferQryDetailReqField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferQryDetailReqField, FutureAccount)
    ;
}
void generate_class_CThostFtdcTransferQryDetailRspField(pybind11::module &m)
{
    py::class_<CThostFtdcTransferQryDetailRspField>(m, "CThostFtdcTransferQryDetailRspField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TradeDate)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TradeTime)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TradeCode)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, FutureSerial)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, FutureID)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, FutureAccount)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankSerial)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankID)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankBrchID)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankAccount)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, CertCode)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, CurrencyCode)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TxAmount)
        .DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, Flag)
    ;
}
void generate_class_CThostFtdcRspInfoField(pybind11::module &m)
{
    py::class_<CThostFtdcRspInfoField>(m, "CThostFtdcRspInfoField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcRspInfoField, ErrorID)
        .DEF_PROPERTY(CThostFtdcRspInfoField, ErrorMsg)
    ;
}
void generate_class_CThostFtdcExchangeField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeField>(m, "CThostFtdcExchangeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcExchangeField, ExchangeName)
        .DEF_PROPERTY(CThostFtdcExchangeField, ExchangeProperty)
    ;
}
void generate_class_CThostFtdcProductField(pybind11::module &m)
{
    py::class_<CThostFtdcProductField>(m, "CThostFtdcProductField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcProductField, ProductID)
        .DEF_PROPERTY(CThostFtdcProductField, ProductName)
        .DEF_PROPERTY(CThostFtdcProductField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcProductField, ProductClass)
        .DEF_PROPERTY(CThostFtdcProductField, VolumeMultiple)
        .DEF_PROPERTY(CThostFtdcProductField, PriceTick)
        .DEF_PROPERTY(CThostFtdcProductField, MaxMarketOrderVolume)
        .DEF_PROPERTY(CThostFtdcProductField, MinMarketOrderVolume)
        .DEF_PROPERTY(CThostFtdcProductField, MaxLimitOrderVolume)
        .DEF_PROPERTY(CThostFtdcProductField, MinLimitOrderVolume)
        .DEF_PROPERTY(CThostFtdcProductField, PositionType)
        .DEF_PROPERTY(CThostFtdcProductField, PositionDateType)
        .DEF_PROPERTY(CThostFtdcProductField, CloseDealType)
        .DEF_PROPERTY(CThostFtdcProductField, TradeCurrencyID)
        .DEF_PROPERTY(CThostFtdcProductField, MortgageFundUseRange)
        .DEF_PROPERTY(CThostFtdcProductField, ExchangeProductID)
        .DEF_PROPERTY(CThostFtdcProductField, UnderlyingMultiple)
    ;
}
void generate_class_CThostFtdcInstrumentField(pybind11::module &m)
{
    py::class_<CThostFtdcInstrumentField>(m, "CThostFtdcInstrumentField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInstrumentField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInstrumentField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInstrumentField, InstrumentName)
        .DEF_PROPERTY(CThostFtdcInstrumentField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcInstrumentField, ProductID)
        .DEF_PROPERTY(CThostFtdcInstrumentField, ProductClass)
        .DEF_PROPERTY(CThostFtdcInstrumentField, DeliveryYear)
        .DEF_PROPERTY(CThostFtdcInstrumentField, DeliveryMonth)
        .DEF_PROPERTY(CThostFtdcInstrumentField, MaxMarketOrderVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentField, MinMarketOrderVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentField, MaxLimitOrderVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentField, MinLimitOrderVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentField, VolumeMultiple)
        .DEF_PROPERTY(CThostFtdcInstrumentField, PriceTick)
        .DEF_PROPERTY(CThostFtdcInstrumentField, CreateDate)
        .DEF_PROPERTY(CThostFtdcInstrumentField, OpenDate)
        .DEF_PROPERTY(CThostFtdcInstrumentField, ExpireDate)
        .DEF_PROPERTY(CThostFtdcInstrumentField, StartDelivDate)
        .DEF_PROPERTY(CThostFtdcInstrumentField, EndDelivDate)
        .DEF_PROPERTY(CThostFtdcInstrumentField, InstLifePhase)
        .DEF_PROPERTY(CThostFtdcInstrumentField, IsTrading)
        .DEF_PROPERTY(CThostFtdcInstrumentField, PositionType)
        .DEF_PROPERTY(CThostFtdcInstrumentField, PositionDateType)
        .DEF_PROPERTY(CThostFtdcInstrumentField, LongMarginRatio)
        .DEF_PROPERTY(CThostFtdcInstrumentField, ShortMarginRatio)
        .DEF_PROPERTY(CThostFtdcInstrumentField, MaxMarginSideAlgorithm)
        .DEF_PROPERTY(CThostFtdcInstrumentField, UnderlyingInstrID)
        .DEF_PROPERTY(CThostFtdcInstrumentField, StrikePrice)
        .DEF_PROPERTY(CThostFtdcInstrumentField, OptionsType)
        .DEF_PROPERTY(CThostFtdcInstrumentField, UnderlyingMultiple)
        .DEF_PROPERTY(CThostFtdcInstrumentField, CombinationType)
        .DEF_PROPERTY(CThostFtdcInstrumentField, MinBuyVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentField, MinSellVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentField, InstrumentCode)
    ;
}
void generate_class_CThostFtdcBrokerField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerField>(m, "CThostFtdcBrokerField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerField, BrokerAbbr)
        .DEF_PROPERTY(CThostFtdcBrokerField, BrokerName)
        .DEF_PROPERTY(CThostFtdcBrokerField, IsActive)
    ;
}
void generate_class_CThostFtdcTraderField(pybind11::module &m)
{
    py::class_<CThostFtdcTraderField>(m, "CThostFtdcTraderField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTraderField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcTraderField, TraderID)
        .DEF_PROPERTY(CThostFtdcTraderField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcTraderField, Password)
        .DEF_PROPERTY(CThostFtdcTraderField, InstallCount)
        .DEF_PROPERTY(CThostFtdcTraderField, BrokerID)
    ;
}
void generate_class_CThostFtdcInvestorField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorField>(m, "CThostFtdcInvestorField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorField, InvestorGroupID)
        .DEF_PROPERTY(CThostFtdcInvestorField, InvestorName)
        .DEF_PROPERTY(CThostFtdcInvestorField, IdentifiedCardType)
        .DEF_PROPERTY(CThostFtdcInvestorField, IdentifiedCardNo)
        .DEF_PROPERTY(CThostFtdcInvestorField, IsActive)
        .DEF_PROPERTY(CThostFtdcInvestorField, Telephone)
        .DEF_PROPERTY(CThostFtdcInvestorField, Address)
        .DEF_PROPERTY(CThostFtdcInvestorField, OpenDate)
        .DEF_PROPERTY(CThostFtdcInvestorField, Mobile)
        .DEF_PROPERTY(CThostFtdcInvestorField, CommModelID)
        .DEF_PROPERTY(CThostFtdcInvestorField, MarginModelID)
    ;
}
void generate_class_CThostFtdcTradingCodeField(pybind11::module &m)
{
    py::class_<CThostFtdcTradingCodeField>(m, "CThostFtdcTradingCodeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradingCodeField, InvestorID)
        .DEF_PROPERTY(CThostFtdcTradingCodeField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradingCodeField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcTradingCodeField, ClientID)
        .DEF_PROPERTY(CThostFtdcTradingCodeField, IsActive)
        .DEF_PROPERTY(CThostFtdcTradingCodeField, ClientIDType)
        .DEF_PROPERTY(CThostFtdcTradingCodeField, BranchID)
        .DEF_PROPERTY(CThostFtdcTradingCodeField, BizType)
    ;
}
void generate_class_CThostFtdcPartBrokerField(pybind11::module &m)
{
    py::class_<CThostFtdcPartBrokerField>(m, "CThostFtdcPartBrokerField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcPartBrokerField, BrokerID)
        .DEF_PROPERTY(CThostFtdcPartBrokerField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcPartBrokerField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcPartBrokerField, IsActive)
    ;
}
void generate_class_CThostFtdcSuperUserField(pybind11::module &m)
{
    py::class_<CThostFtdcSuperUserField>(m, "CThostFtdcSuperUserField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSuperUserField, UserID)
        .DEF_PROPERTY(CThostFtdcSuperUserField, UserName)
        .DEF_PROPERTY(CThostFtdcSuperUserField, Password)
        .DEF_PROPERTY(CThostFtdcSuperUserField, IsActive)
    ;
}
void generate_class_CThostFtdcSuperUserFunctionField(pybind11::module &m)
{
    py::class_<CThostFtdcSuperUserFunctionField>(m, "CThostFtdcSuperUserFunctionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSuperUserFunctionField, UserID)
        .DEF_PROPERTY(CThostFtdcSuperUserFunctionField, FunctionCode)
    ;
}
void generate_class_CThostFtdcInvestorGroupField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorGroupField>(m, "CThostFtdcInvestorGroupField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorGroupField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorGroupField, InvestorGroupID)
        .DEF_PROPERTY(CThostFtdcInvestorGroupField, InvestorGroupName)
    ;
}
void generate_class_CThostFtdcTradingAccountField(pybind11::module &m)
{
    py::class_<CThostFtdcTradingAccountField>(m, "CThostFtdcTradingAccountField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTradingAccountField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, AccountID)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PreMortgage)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PreCredit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PreDeposit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PreBalance)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PreMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, InterestBase)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Interest)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Deposit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Withdraw)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, FrozenMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, FrozenCash)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, FrozenCommission)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, CurrMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, CashIn)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Commission)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, CloseProfit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PositionProfit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Balance)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Available)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, WithdrawQuota)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Reserve)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, TradingDay)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SettlementID)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Credit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, Mortgage)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, ExchangeMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, DeliveryMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, ExchangeDeliveryMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, ReserveBalance)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, CurrencyID)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PreFundMortgageIn)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, PreFundMortgageOut)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, FundMortgageIn)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, FundMortgageOut)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, FundMortgageAvailable)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, MortgageableFund)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductFrozenMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductCommission)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductFrozenCommission)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductPositionProfit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductCloseProfit)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductPositionProfitByAlg)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductExchangeMargin)
        .DEF_PROPERTY(CThostFtdcTradingAccountField, BizType)
    ;
}
void generate_class_CThostFtdcInvestorPositionField(pybind11::module &m)
{
    py::class_<CThostFtdcInvestorPositionField>(m, "CThostFtdcInvestorPositionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, PosiDirection)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, PositionDate)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, YdPosition)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, Position)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, LongFrozen)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, ShortFrozen)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, LongFrozenAmount)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, ShortFrozenAmount)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, OpenVolume)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseVolume)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, OpenAmount)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseAmount)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, PositionCost)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, PreMargin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, UseMargin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, FrozenMargin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, FrozenCash)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, FrozenCommission)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CashIn)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, Commission)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseProfit)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, PositionProfit)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, PreSettlementPrice)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, SettlementPrice)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, TradingDay)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, SettlementID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, OpenCost)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, ExchangeMargin)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CombPosition)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CombLongFrozen)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CombShortFrozen)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseProfitByDate)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseProfitByTrade)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, TodayPosition)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, MarginRateByMoney)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, MarginRateByVolume)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, StrikeFrozen)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, StrikeFrozenAmount)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, AbandonFrozen)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInvestorPositionField, YdStrikeFrozen)
    ;
}
void generate_class_CThostFtdcInstrumentMarginRateField(pybind11::module &m)
{
    py::class_<CThostFtdcInstrumentMarginRateField>(m, "CThostFtdcInstrumentMarginRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, LongMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, LongMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, ShortMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, ShortMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, IsRelative)
    ;
}
void generate_class_CThostFtdcInstrumentCommissionRateField(pybind11::module &m)
{
    py::class_<CThostFtdcInstrumentCommissionRateField>(m, "CThostFtdcInstrumentCommissionRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, OpenRatioByMoney)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, OpenRatioByVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseRatioByMoney)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseRatioByVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseTodayRatioByMoney)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseTodayRatioByVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, BizType)
    ;
}
void generate_class_CThostFtdcDepthMarketDataField(pybind11::module &m)
{
    py::class_<CThostFtdcDepthMarketDataField>(m, "CThostFtdcDepthMarketDataField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, TradingDay)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, ExchangeInstID)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, LastPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreSettlementPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreClosePrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreOpenInterest)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, OpenPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, HighestPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, LowestPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, Volume)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, Turnover)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, OpenInterest)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, ClosePrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, SettlementPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, UpperLimitPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, LowerLimitPrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreDelta)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, CurrDelta)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, UpdateTime)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, UpdateMillisec)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice1)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume1)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice1)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume1)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice2)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume2)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice2)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume2)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice3)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume3)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice3)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume3)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice4)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume4)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice4)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume4)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice5)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume5)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice5)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume5)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, AveragePrice)
        .DEF_PROPERTY(CThostFtdcDepthMarketDataField, ActionDay)
    ;
}
void generate_class_CThostFtdcInstrumentTradingRightField(pybind11::module &m)
{
    py::class_<CThostFtdcInstrumentTradingRightField>(m, "CThostFtdcInstrumentTradingRightField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, TradingRight)
        .DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, BizType)
    ;
}
void generate_class_CThostFtdcBrokerUserField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerUserField>(m, "CThostFtdcBrokerUserField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerUserField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerUserField, UserID)
        .DEF_PROPERTY(CThostFtdcBrokerUserField, UserName)
        .DEF_PROPERTY(CThostFtdcBrokerUserField, UserType)
        .DEF_PROPERTY(CThostFtdcBrokerUserField, IsActive)
        .DEF_PROPERTY(CThostFtdcBrokerUserField, IsUsingOTP)
    ;
}
void generate_class_CThostFtdcBrokerUserPasswordField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerUserPasswordField>(m, "CThostFtdcBrokerUserPasswordField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, UserID)
        .DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, Password)
    ;
}
void generate_class_CThostFtdcBrokerUserFunctionField(pybind11::module &m)
{
    py::class_<CThostFtdcBrokerUserFunctionField>(m, "CThostFtdcBrokerUserFunctionField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcBrokerUserFunctionField, BrokerID)
        .DEF_PROPERTY(CThostFtdcBrokerUserFunctionField, UserID)
        .DEF_PROPERTY(CThostFtdcBrokerUserFunctionField, BrokerFunctionCode)
    ;
}
void generate_class_CThostFtdcTraderOfferField(pybind11::module &m)
{
    py::class_<CThostFtdcTraderOfferField>(m, "CThostFtdcTraderOfferField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcTraderOfferField, ExchangeID)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, TraderID)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, ParticipantID)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, Password)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, InstallID)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, OrderLocalID)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, TraderConnectStatus)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectRequestDate)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectRequestTime)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, LastReportDate)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, LastReportTime)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectDate)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectTime)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, StartDate)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, StartTime)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, TradingDay)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, BrokerID)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, MaxTradeID)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, MaxOrderMessageReference)
        .DEF_PROPERTY(CThostFtdcTraderOfferField, BizType)
    ;
}
void generate_class_CThostFtdcSettlementInfoField(pybind11::module &m)
{
    py::class_<CThostFtdcSettlementInfoField>(m, "CThostFtdcSettlementInfoField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSettlementInfoField, TradingDay)
        .DEF_PROPERTY(CThostFtdcSettlementInfoField, SettlementID)
        .DEF_PROPERTY(CThostFtdcSettlementInfoField, BrokerID)
        .DEF_PROPERTY(CThostFtdcSettlementInfoField, InvestorID)
        .DEF_PROPERTY(CThostFtdcSettlementInfoField, SequenceNo)
        .DEF_PROPERTY(CThostFtdcSettlementInfoField, Content)
    ;
}
void generate_class_CThostFtdcInstrumentMarginRateAdjustField(pybind11::module &m)
{
    py::class_<CThostFtdcInstrumentMarginRateAdjustField>(m, "CThostFtdcInstrumentMarginRateAdjustField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, InvestorRange)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, BrokerID)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, InvestorID)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, LongMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, LongMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, ShortMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, ShortMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, IsRelative)
    ;
}
void generate_class_CThostFtdcExchangeMarginRateField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeMarginRateField>(m, "CThostFtdcExchangeMarginRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateField, LongMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateField, LongMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateField, ShortMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateField, ShortMarginRatioByVolume)
    ;
}
void generate_class_CThostFtdcExchangeMarginRateAdjustField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeMarginRateAdjustField>(m, "CThostFtdcExchangeMarginRateAdjustField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, BrokerID)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, InstrumentID)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, HedgeFlag)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, LongMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, LongMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ShortMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ShortMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchLongMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchLongMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchShortMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchShortMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoLongMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoLongMarginRatioByVolume)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoShortMarginRatioByMoney)
        .DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoShortMarginRatioByVolume)
    ;
}
void generate_class_CThostFtdcExchangeRateField(pybind11::module &m)
{
    py::class_<CThostFtdcExchangeRateField>(m, "CThostFtdcExchangeRateField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcExchangeRateField, BrokerID)
        .DEF_PROPERTY(CThostFtdcExchangeRateField, FromCurrencyID)
        .DEF_PROPERTY(CThostFtdcExchangeRateField, FromCurrencyUnit)
        .DEF_PROPERTY(CThostFtdcExchangeRateField, ToCurrencyID)
        .DEF_PROPERTY(CThostFtdcExchangeRateField, ExchangeRate)
    ;
}
void generate_class_CThostFtdcSettlementRefField(pybind11::module &m)
{
    py::class_<CThostFtdcSettlementRefField>(m, "CThostFtdcSettlementRefField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcSettlementRefField, TradingDay)
        .DEF_PROPERTY(CThostFtdcSettlementRefField, SettlementID)
    ;
}
void generate_class_CThostFtdcCurrentTimeField(pybind11::module &m)
{
    py::class_<CThostFtdcCurrentTimeField>(m, "CThostFtdcCurrentTimeField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCurrentTimeField, CurrDate)
        .DEF_PROPERTY(CThostFtdcCurrentTimeField, CurrTime)
        .DEF_PROPERTY(CThostFtdcCurrentTimeField, CurrMillisec)
        .DEF_PROPERTY(CThostFtdcCurrentTimeField, ActionDay)
    ;
}
void generate_class_CThostFtdcCommPhaseField(pybind11::module &m)
{
    py::class_<CThostFtdcCommPhaseField>(m, "CThostFtdcCommPhaseField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcCommPhaseField, TradingDay)
        .DEF_PROPERTY(CThostFtdcCommPhaseField, CommPhaseNo)
        .DEF_PROPERTY(CThostFtdcCommPhaseField, SystemID)
    ;
}
void generate_class_CThostFtdcLoginInfoField(pybind11::module &m)
{
    py::class_<CThostFtdcLoginInfoField>(m, "CThostFtdcLoginInfoField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLoginInfoField, FrontID)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, SessionID)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, BrokerID)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, UserID)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, LoginDate)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, LoginTime)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, IPAddress)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, UserProductInfo)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, InterfaceProductInfo)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, ProtocolInfo)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, SystemName)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, Password)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, MaxOrderRef)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, SHFETime)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, DCETime)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, CZCETime)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, FFEXTime)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, MacAddress)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, OneTimePassword)
        .DEF_PROPERTY(CThostFtdcLoginInfoField, INETime)
    ;
}
void generate_class_CThostFtdcLogoutAllField(pybind11::module &m)
{
    py::class_<CThostFtdcLogoutAllField>(m, "CThostFtdcLogoutAllField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcLogoutAllField, FrontID)
        .DEF_PROPERTY(CThostFtdcLogoutAllField, SessionID)
        .DEF_PROPERTY(CThostFtdcLogoutAllField, SystemName)
    ;
}
void generate_class_CThostFtdcFrontStatusField(pybind11::module &m)
{
    py::class_<CThostFtdcFrontStatusField>(m, "CThostFtdcFrontStatusField")
        .def(py::init<>())
        .DEF_PROPERTY(CThostFtdcFrontStatusField, FrontID)
        .DEF_PROPERTY(CThostFtdcFrontStatusField, LastReportDate)
        .DEF_PROPERTY(CThostFtdcFrontStatusField, LastReportTime)
        .DEF_PROPERTY(CThostFtdcFrontStatusField, IsActive)
    ;
}

