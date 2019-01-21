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


void generate_class_CThostFtdcDisseminationField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcDisseminationField> c(m, "CThostFtdcDisseminationField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDisseminationField, SequenceSeries);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDisseminationField, SequenceNo);
}
void generate_class_CThostFtdcReqUserLoginField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqUserLoginField> c(m, "CThostFtdcReqUserLoginField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, InterfaceProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, ProtocolInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, OneTimePassword);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, ClientIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, LoginRemark);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginField, ClientIPPort);
}
void generate_class_CThostFtdcRspUserLoginField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspUserLoginField> c(m, "CThostFtdcRspUserLoginField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, LoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, SystemName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, MaxOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, SHFETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, DCETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, CZCETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, FFEXTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLoginField, INETime);
}
void generate_class_CThostFtdcUserLogoutField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcUserLogoutField> c(m, "CThostFtdcUserLogoutField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserLogoutField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserLogoutField, UserID);
}
void generate_class_CThostFtdcForceUserLogoutField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcForceUserLogoutField> c(m, "CThostFtdcForceUserLogoutField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForceUserLogoutField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcForceUserLogoutField, UserID);
}
void generate_class_CThostFtdcReqAuthenticateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqAuthenticateField> c(m, "CThostFtdcReqAuthenticateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqAuthenticateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqAuthenticateField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqAuthenticateField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqAuthenticateField, AuthCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqAuthenticateField, AppID);
}
void generate_class_CThostFtdcRspAuthenticateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspAuthenticateField> c(m, "CThostFtdcRspAuthenticateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspAuthenticateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspAuthenticateField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspAuthenticateField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspAuthenticateField, AppID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspAuthenticateField, AppType);
}
void generate_class_CThostFtdcAuthenticationInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcAuthenticationInfoField> c(m, "CThostFtdcAuthenticationInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAuthenticationInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAuthenticationInfoField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAuthenticationInfoField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAuthenticationInfoField, AuthInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAuthenticationInfoField, IsResult);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAuthenticationInfoField, AppID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAuthenticationInfoField, AppType);
}
void generate_class_CThostFtdcRspUserLogin2Field(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspUserLogin2Field> c(m, "CThostFtdcRspUserLogin2Field");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, LoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, SystemName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, MaxOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, SHFETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, DCETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, CZCETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, FFEXTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, INETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserLogin2Field, RandomString);
}
void generate_class_CThostFtdcTransferHeaderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferHeaderField> c(m, "CThostFtdcTransferHeaderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, Version);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, TradeSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, FutureID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, BankBrchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, RecordNum);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferHeaderField, RequestID);
}
void generate_class_CThostFtdcTransferBankToFutureReqField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferBankToFutureReqField> c(m, "CThostFtdcTransferBankToFutureReqField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, FutureAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, FuturePwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, FutureAccPwd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, TradeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureReqField, CurrencyCode);
}
void generate_class_CThostFtdcTransferBankToFutureRspField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferBankToFutureRspField> c(m, "CThostFtdcTransferBankToFutureRspField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, RetCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, RetInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, FutureAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, TradeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferBankToFutureRspField, CurrencyCode);
}
void generate_class_CThostFtdcTransferFutureToBankReqField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferFutureToBankReqField> c(m, "CThostFtdcTransferFutureToBankReqField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, FutureAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, FuturePwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, FutureAccPwd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, TradeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankReqField, CurrencyCode);
}
void generate_class_CThostFtdcTransferFutureToBankRspField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferFutureToBankRspField> c(m, "CThostFtdcTransferFutureToBankRspField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, RetCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, RetInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, FutureAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, TradeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferFutureToBankRspField, CurrencyCode);
}
void generate_class_CThostFtdcTransferQryBankReqField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferQryBankReqField> c(m, "CThostFtdcTransferQryBankReqField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankReqField, FutureAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankReqField, FuturePwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankReqField, FutureAccPwd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankReqField, CurrencyCode);
}
void generate_class_CThostFtdcTransferQryBankRspField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferQryBankRspField> c(m, "CThostFtdcTransferQryBankRspField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankRspField, RetCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankRspField, RetInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankRspField, FutureAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankRspField, TradeAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankRspField, UseAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankRspField, FetchAmt);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryBankRspField, CurrencyCode);
}
void generate_class_CThostFtdcTransferQryDetailReqField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferQryDetailReqField> c(m, "CThostFtdcTransferQryDetailReqField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailReqField, FutureAccount);
}
void generate_class_CThostFtdcTransferQryDetailRspField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferQryDetailRspField> c(m, "CThostFtdcTransferQryDetailRspField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, FutureID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, FutureAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankBrchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, CertCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, CurrencyCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, TxAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferQryDetailRspField, Flag);
}
void generate_class_CThostFtdcRspInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspInfoField> c(m, "CThostFtdcRspInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspInfoField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspInfoField, ErrorMsg);
}
void generate_class_CThostFtdcExchangeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeField> c(m, "CThostFtdcExchangeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeField, ExchangeName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeField, ExchangeProperty);
}
void generate_class_CThostFtdcProductField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcProductField> c(m, "CThostFtdcProductField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, ProductName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, ProductClass);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, VolumeMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, PriceTick);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, MaxMarketOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, MinMarketOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, MaxLimitOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, MinLimitOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, PositionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, PositionDateType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, CloseDealType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, TradeCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, MortgageFundUseRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, ExchangeProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcProductField, UnderlyingMultiple);
}
void generate_class_CThostFtdcInstrumentField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentField> c(m, "CThostFtdcInstrumentField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, InstrumentName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, ProductClass);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, DeliveryYear);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, DeliveryMonth);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, MaxMarketOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, MinMarketOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, MaxLimitOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, MinLimitOrderVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, VolumeMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, PriceTick);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, CreateDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, ExpireDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, StartDelivDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, EndDelivDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, InstLifePhase);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, IsTrading);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, PositionType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, PositionDateType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, LongMarginRatio);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, ShortMarginRatio);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, MaxMarginSideAlgorithm);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, UnderlyingInstrID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, OptionsType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, UnderlyingMultiple);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentField, CombinationType);
}
void generate_class_CThostFtdcBrokerField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerField> c(m, "CThostFtdcBrokerField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerField, BrokerAbbr);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerField, BrokerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerField, IsActive);
}
void generate_class_CThostFtdcTraderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTraderField> c(m, "CThostFtdcTraderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderField, InstallCount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderField, BrokerID);
}
void generate_class_CThostFtdcInvestorField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorField> c(m, "CThostFtdcInvestorField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, InvestorGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, InvestorName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, IdentifiedCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, IsActive);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, Mobile);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, CommModelID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorField, MarginModelID);
}
void generate_class_CThostFtdcTradingCodeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingCodeField> c(m, "CThostFtdcTradingCodeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, IsActive);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, ClientIDType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, BizType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingCodeField, InvestUnitID);
}
void generate_class_CThostFtdcPartBrokerField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcPartBrokerField> c(m, "CThostFtdcPartBrokerField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPartBrokerField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPartBrokerField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPartBrokerField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcPartBrokerField, IsActive);
}
void generate_class_CThostFtdcSuperUserField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSuperUserField> c(m, "CThostFtdcSuperUserField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSuperUserField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSuperUserField, UserName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSuperUserField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSuperUserField, IsActive);
}
void generate_class_CThostFtdcSuperUserFunctionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSuperUserFunctionField> c(m, "CThostFtdcSuperUserFunctionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSuperUserFunctionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSuperUserFunctionField, FunctionCode);
}
void generate_class_CThostFtdcInvestorGroupField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorGroupField> c(m, "CThostFtdcInvestorGroupField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorGroupField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorGroupField, InvestorGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorGroupField, InvestorGroupName);
}
void generate_class_CThostFtdcTradingAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingAccountField> c(m, "CThostFtdcTradingAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PreMortgage);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PreCredit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PreDeposit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PreBalance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PreMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, InterestBase);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Interest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Deposit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Withdraw);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, FrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, FrozenCash);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, FrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, CurrMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, CashIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Commission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Balance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Available);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, WithdrawQuota);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Reserve);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Credit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, Mortgage);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, ExchangeMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, DeliveryMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, ExchangeDeliveryMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, ReserveBalance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PreFundMortgageIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, PreFundMortgageOut);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, FundMortgageIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, FundMortgageOut);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, FundMortgageAvailable);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, MortgageableFund);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductFrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductFrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductCloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductPositionProfitByAlg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, SpecProductExchangeMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, BizType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, FrozenSwap);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountField, RemainSwap);
}
void generate_class_CThostFtdcInvestorPositionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInvestorPositionField> c(m, "CThostFtdcInvestorPositionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, PosiDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, PositionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, YdPosition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, Position);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, LongFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, ShortFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, LongFrozenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, ShortFrozenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, OpenVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, OpenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, PositionCost);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, PreMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, UseMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, FrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, FrozenCash);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, FrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CashIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, Commission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, PreSettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, SettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, OpenCost);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, ExchangeMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CombPosition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CombLongFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CombShortFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseProfitByDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, CloseProfitByTrade);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, TodayPosition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, MarginRateByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, MarginRateByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, StrikeFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, StrikeFrozenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, AbandonFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, YdStrikeFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInvestorPositionField, InvestUnitID);
}
void generate_class_CThostFtdcInstrumentMarginRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentMarginRateField> c(m, "CThostFtdcInstrumentMarginRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, LongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, LongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, ShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, ShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, IsRelative);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateField, InvestUnitID);
}
void generate_class_CThostFtdcInstrumentCommissionRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentCommissionRateField> c(m, "CThostFtdcInstrumentCommissionRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, OpenRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, OpenRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseTodayRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, CloseTodayRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, BizType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentCommissionRateField, InvestUnitID);
}
void generate_class_CThostFtdcDepthMarketDataField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcDepthMarketDataField> c(m, "CThostFtdcDepthMarketDataField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreSettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreOpenInterest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, HighestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, LowestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, OpenInterest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, SettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, UpperLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, LowerLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, PreDelta);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, CurrDelta);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, UpdateMillisec);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume1);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume1);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume3);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume3);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, BidVolume5);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AskVolume5);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, AveragePrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepthMarketDataField, ActionDay);
}
void generate_class_CThostFtdcInstrumentTradingRightField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentTradingRightField> c(m, "CThostFtdcInstrumentTradingRightField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentTradingRightField, TradingRight);
}
void generate_class_CThostFtdcBrokerUserField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerUserField> c(m, "CThostFtdcBrokerUserField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserField, UserName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserField, UserType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserField, IsActive);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserField, IsUsingOTP);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserField, IsAuthForce);
}
void generate_class_CThostFtdcBrokerUserPasswordField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerUserPasswordField> c(m, "CThostFtdcBrokerUserPasswordField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, LastUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, LastLoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, ExpireDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserPasswordField, WeakExpireDate);
}
void generate_class_CThostFtdcBrokerUserFunctionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerUserFunctionField> c(m, "CThostFtdcBrokerUserFunctionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserFunctionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserFunctionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserFunctionField, BrokerFunctionCode);
}
void generate_class_CThostFtdcTraderOfferField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTraderOfferField> c(m, "CThostFtdcTraderOfferField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, TraderConnectStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectRequestDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectRequestTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, LastReportDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, LastReportTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, ConnectTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, StartDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, StartTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, MaxTradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTraderOfferField, MaxOrderMessageReference);
}
void generate_class_CThostFtdcSettlementInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSettlementInfoField> c(m, "CThostFtdcSettlementInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, Content);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoField, CurrencyID);
}
void generate_class_CThostFtdcInstrumentMarginRateAdjustField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInstrumentMarginRateAdjustField> c(m, "CThostFtdcInstrumentMarginRateAdjustField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, LongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, LongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, ShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, ShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInstrumentMarginRateAdjustField, IsRelative);
}
void generate_class_CThostFtdcExchangeMarginRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeMarginRateField> c(m, "CThostFtdcExchangeMarginRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, LongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, LongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, ShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, ShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateField, ExchangeID);
}
void generate_class_CThostFtdcExchangeMarginRateAdjustField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeMarginRateAdjustField> c(m, "CThostFtdcExchangeMarginRateAdjustField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, LongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, LongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchLongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchLongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, ExchShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoLongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoLongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeMarginRateAdjustField, NoShortMarginRatioByVolume);
}
void generate_class_CThostFtdcExchangeRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeRateField> c(m, "CThostFtdcExchangeRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeRateField, FromCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeRateField, FromCurrencyUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeRateField, ToCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeRateField, ExchangeRate);
}
void generate_class_CThostFtdcSettlementRefField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSettlementRefField> c(m, "CThostFtdcSettlementRefField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementRefField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementRefField, SettlementID);
}
void generate_class_CThostFtdcCurrentTimeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCurrentTimeField> c(m, "CThostFtdcCurrentTimeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCurrentTimeField, CurrDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCurrentTimeField, CurrTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCurrentTimeField, CurrMillisec);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCurrentTimeField, ActionDay);
}
void generate_class_CThostFtdcCommPhaseField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCommPhaseField> c(m, "CThostFtdcCommPhaseField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCommPhaseField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCommPhaseField, CommPhaseNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCommPhaseField, SystemID);
}
void generate_class_CThostFtdcLoginInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcLoginInfoField> c(m, "CThostFtdcLoginInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, LoginDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, LoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, InterfaceProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, ProtocolInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, SystemName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, PasswordDeprecated);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, MaxOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, SHFETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, DCETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, CZCETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, FFEXTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, OneTimePassword);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, INETime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, IsQryControl);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, LoginRemark);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginInfoField, Password);
}
void generate_class_CThostFtdcLogoutAllField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcLogoutAllField> c(m, "CThostFtdcLogoutAllField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLogoutAllField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLogoutAllField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLogoutAllField, SystemName);
}
void generate_class_CThostFtdcFrontStatusField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcFrontStatusField> c(m, "CThostFtdcFrontStatusField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFrontStatusField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFrontStatusField, LastReportDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFrontStatusField, LastReportTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFrontStatusField, IsActive);
}
void generate_class_CThostFtdcUserPasswordUpdateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcUserPasswordUpdateField> c(m, "CThostFtdcUserPasswordUpdateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, OldPassword);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserPasswordUpdateField, NewPassword);
}
void generate_class_CThostFtdcInputOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputOrderField> c(m, "CThostFtdcInputOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, GTDDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, IsAutoSuspend);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, IsSwapOrder);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderField, MacAddress);
}
void generate_class_CThostFtdcOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOrderField> c(m, "CThostFtdcOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, GTDDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, IsAutoSuspend);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, VolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, VolumeTotal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ActiveTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, SuspendTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ActiveTraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, UserForceClose);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ActiveUserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, BrokerOrderSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, RelativeOrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, ZCETotalTradedVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, IsSwapOrder);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderField, MacAddress);
}
void generate_class_CThostFtdcExchangeOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeOrderField> c(m, "CThostFtdcExchangeOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderPriceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, CombOffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, CombHedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, TimeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, GTDDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, MinVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ContingentCondition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ForceCloseReason);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, IsAutoSuspend);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderSubmitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, NotifySequence);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, VolumeTotal);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ActiveTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, SuspendTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, UpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, CancelTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ActiveTraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderField, MacAddress);
}
void generate_class_CThostFtdcExchangeOrderInsertErrorField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeOrderInsertErrorField> c(m, "CThostFtdcExchangeOrderInsertErrorField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderInsertErrorField, ErrorMsg);
}
void generate_class_CThostFtdcInputOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcInputOrderActionField> c(m, "CThostFtdcInputOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, VolumeChange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcInputOrderActionField, MacAddress);
}
void generate_class_CThostFtdcOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOrderActionField> c(m, "CThostFtdcOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, VolumeChange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, InvestUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOrderActionField, MacAddress);
}
void generate_class_CThostFtdcExchangeOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeOrderActionField> c(m, "CThostFtdcExchangeOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, VolumeChange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, OrderActionStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, BranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionField, MacAddress);
}
void generate_class_CThostFtdcExchangeOrderActionErrorField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeOrderActionErrorField> c(m, "CThostFtdcExchangeOrderActionErrorField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ActionLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeOrderActionErrorField, ErrorMsg);
}
void generate_class_CThostFtdcExchangeTradeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcExchangeTradeField> c(m, "CThostFtdcExchangeTradeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, TradingRole);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, Price);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, PriceSource);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcExchangeTradeField, TradeSource);
}
void generate_class_CThostFtdcTradeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradeField> c(m, "CThostFtdcTradeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TradingRole);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, Price);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, Volume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TradeType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, PriceSource);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TraderID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, ClearingPartID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, BusinessUnit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, SequenceNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, BrokerOrderSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, TradeSource);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradeField, InvestUnitID);
}
void generate_class_CThostFtdcUserSessionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcUserSessionField> c(m, "CThostFtdcUserSessionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, LoginDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, LoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, InterfaceProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, ProtocolInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSessionField, LoginRemark);
}
void generate_class_CThostFtdcQueryMaxOrderVolumeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQueryMaxOrderVolumeField> c(m, "CThostFtdcQueryMaxOrderVolumeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, Direction);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, OffsetFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, MaxVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryMaxOrderVolumeField, InvestUnitID);
}
void generate_class_CThostFtdcSettlementInfoConfirmField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSettlementInfoConfirmField> c(m, "CThostFtdcSettlementInfoConfirmField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, ConfirmDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, ConfirmTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSettlementInfoConfirmField, CurrencyID);
}
void generate_class_CThostFtdcSyncDepositField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncDepositField> c(m, "CThostFtdcSyncDepositField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDepositField, DepositSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDepositField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDepositField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDepositField, Deposit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDepositField, IsForce);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncDepositField, CurrencyID);
}
void generate_class_CThostFtdcSyncFundMortgageField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncFundMortgageField> c(m, "CThostFtdcSyncFundMortgageField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncFundMortgageField, MortgageSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncFundMortgageField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncFundMortgageField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncFundMortgageField, FromCurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncFundMortgageField, MortgageAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncFundMortgageField, ToCurrencyID);
}
void generate_class_CThostFtdcBrokerSyncField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerSyncField> c(m, "CThostFtdcBrokerSyncField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerSyncField, BrokerID);
}
void generate_class_CThostFtdcSyncingInvestorField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingInvestorField> c(m, "CThostFtdcSyncingInvestorField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, InvestorGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, InvestorName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, IdentifiedCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, IsActive);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, Mobile);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, CommModelID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorField, MarginModelID);
}
void generate_class_CThostFtdcSyncingTradingCodeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingTradingCodeField> c(m, "CThostFtdcSyncingTradingCodeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, IsActive);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingCodeField, ClientIDType);
}
void generate_class_CThostFtdcSyncingInvestorGroupField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingInvestorGroupField> c(m, "CThostFtdcSyncingInvestorGroupField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorGroupField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorGroupField, InvestorGroupID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorGroupField, InvestorGroupName);
}
void generate_class_CThostFtdcSyncingTradingAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingTradingAccountField> c(m, "CThostFtdcSyncingTradingAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreMortgage);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreCredit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreDeposit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreBalance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, InterestBase);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Interest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Deposit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Withdraw);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FrozenCash);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CurrMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CashIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Commission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Balance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Available);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, WithdrawQuota);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Reserve);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Credit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, Mortgage);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, ExchangeMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, DeliveryMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, ExchangeDeliveryMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, ReserveBalance);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreFundMortgageIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, PreFundMortgageOut);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FundMortgageIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FundMortgageOut);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FundMortgageAvailable);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, MortgageableFund);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductFrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductFrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductCloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductPositionProfitByAlg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, SpecProductExchangeMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, FrozenSwap);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingTradingAccountField, RemainSwap);
}
void generate_class_CThostFtdcSyncingInvestorPositionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingInvestorPositionField> c(m, "CThostFtdcSyncingInvestorPositionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PosiDirection);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PositionDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, YdPosition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, Position);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, LongFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ShortFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, LongFrozenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ShortFrozenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, OpenVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, OpenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PositionCost);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PreMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, UseMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, FrozenMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, FrozenCash);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, FrozenCommission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CashIn);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, Commission);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, PreSettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, SettlementPrice);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, SettlementID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, OpenCost);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ExchangeMargin);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CombPosition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CombLongFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CombShortFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseProfitByDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, CloseProfitByTrade);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, TodayPosition);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, MarginRateByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, MarginRateByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, StrikeFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, StrikeFrozenAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, AbandonFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, YdStrikeFrozen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInvestorPositionField, InvestUnitID);
}
void generate_class_CThostFtdcSyncingInstrumentMarginRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingInstrumentMarginRateField> c(m, "CThostFtdcSyncingInstrumentMarginRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, LongMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, LongMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, ShortMarginRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, ShortMarginRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentMarginRateField, IsRelative);
}
void generate_class_CThostFtdcSyncingInstrumentCommissionRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingInstrumentCommissionRateField> c(m, "CThostFtdcSyncingInstrumentCommissionRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, OpenRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, OpenRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseRatioByVolume);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseTodayRatioByMoney);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentCommissionRateField, CloseTodayRatioByVolume);
}
void generate_class_CThostFtdcSyncingInstrumentTradingRightField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSyncingInstrumentTradingRightField> c(m, "CThostFtdcSyncingInstrumentTradingRightField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSyncingInstrumentTradingRightField, TradingRight);
}
void generate_class_CThostFtdcQryOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryOrderField> c(m, "CThostFtdcQryOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, InsertTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, InsertTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderField, InvestUnitID);
}
void generate_class_CThostFtdcQryTradeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTradeField> c(m, "CThostFtdcQryTradeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, TradeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, TradeTimeStart);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, TradeTimeEnd);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradeField, InvestUnitID);
}
void generate_class_CThostFtdcQryInvestorPositionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInvestorPositionField> c(m, "CThostFtdcQryInvestorPositionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorPositionField, InvestUnitID);
}
void generate_class_CThostFtdcQryTradingAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTradingAccountField> c(m, "CThostFtdcQryTradingAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingAccountField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingAccountField, BizType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingAccountField, AccountID);
}
void generate_class_CThostFtdcQryInvestorField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInvestorField> c(m, "CThostFtdcQryInvestorField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorField, InvestorID);
}
void generate_class_CThostFtdcQryTradingCodeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTradingCodeField> c(m, "CThostFtdcQryTradingCodeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingCodeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingCodeField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingCodeField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingCodeField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingCodeField, ClientIDType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTradingCodeField, InvestUnitID);
}
void generate_class_CThostFtdcQryInvestorGroupField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInvestorGroupField> c(m, "CThostFtdcQryInvestorGroupField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInvestorGroupField, BrokerID);
}
void generate_class_CThostFtdcQryInstrumentMarginRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInstrumentMarginRateField> c(m, "CThostFtdcQryInstrumentMarginRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentMarginRateField, InvestUnitID);
}
void generate_class_CThostFtdcQryInstrumentCommissionRateField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInstrumentCommissionRateField> c(m, "CThostFtdcQryInstrumentCommissionRateField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentCommissionRateField, InvestUnitID);
}
void generate_class_CThostFtdcQryInstrumentTradingRightField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInstrumentTradingRightField> c(m, "CThostFtdcQryInstrumentTradingRightField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentTradingRightField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentTradingRightField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentTradingRightField, InstrumentID);
}
void generate_class_CThostFtdcQryBrokerField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryBrokerField> c(m, "CThostFtdcQryBrokerField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryBrokerField, BrokerID);
}
void generate_class_CThostFtdcQryTraderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTraderField> c(m, "CThostFtdcQryTraderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTraderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTraderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTraderField, TraderID);
}
void generate_class_CThostFtdcQrySuperUserFunctionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySuperUserFunctionField> c(m, "CThostFtdcQrySuperUserFunctionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySuperUserFunctionField, UserID);
}
void generate_class_CThostFtdcQryUserSessionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryUserSessionField> c(m, "CThostFtdcQryUserSessionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryUserSessionField, FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryUserSessionField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryUserSessionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryUserSessionField, UserID);
}
void generate_class_CThostFtdcQryPartBrokerField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryPartBrokerField> c(m, "CThostFtdcQryPartBrokerField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryPartBrokerField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryPartBrokerField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryPartBrokerField, ParticipantID);
}
void generate_class_CThostFtdcQryFrontStatusField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryFrontStatusField> c(m, "CThostFtdcQryFrontStatusField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryFrontStatusField, FrontID);
}
void generate_class_CThostFtdcQryExchangeOrderField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeOrderField> c(m, "CThostFtdcQryExchangeOrderField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderField, TraderID);
}
void generate_class_CThostFtdcQryOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryOrderActionField> c(m, "CThostFtdcQryOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderActionField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderActionField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryOrderActionField, ExchangeID);
}
void generate_class_CThostFtdcQryExchangeOrderActionField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeOrderActionField> c(m, "CThostFtdcQryExchangeOrderActionField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, ParticipantID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, ClientID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeOrderActionField, TraderID);
}
void generate_class_CThostFtdcQrySuperUserField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySuperUserField> c(m, "CThostFtdcQrySuperUserField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySuperUserField, UserID);
}
void generate_class_CThostFtdcQryExchangeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryExchangeField> c(m, "CThostFtdcQryExchangeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryExchangeField, ExchangeID);
}
void generate_class_CThostFtdcQryProductField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryProductField> c(m, "CThostFtdcQryProductField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryProductField, ProductID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryProductField, ProductClass);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryProductField, ExchangeID);
}
void generate_class_CThostFtdcQryInstrumentField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryInstrumentField> c(m, "CThostFtdcQryInstrumentField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentField, ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentField, ExchangeInstID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryInstrumentField, ProductID);
}
void generate_class_CThostFtdcQryDepthMarketDataField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryDepthMarketDataField> c(m, "CThostFtdcQryDepthMarketDataField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryDepthMarketDataField, InstrumentID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryDepthMarketDataField, ExchangeID);
}
