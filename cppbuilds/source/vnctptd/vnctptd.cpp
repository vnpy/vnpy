#include <iostream>
#include <string>
#include <string_view>
#include <pybind11/pybind11.h>
#include <ctp/ThostFtdcTraderApi.h>
#include "wrapper.h"

namespace py = pybind11;
using namespace std;

template <class class_type, class value_type>
auto wrap_getter(value_type class_type::*member)
{
	return [member](const class_type &instance)->const value_type & {
		return instance.*member;
	};
}


template <class class_type, class value_type>
auto wrap_setter(value_type class_type::*member)
{
	return [member](class_type &instance, const value_type &value) {
		instance.*member = value;
	};
}

template <size_t size>
using string_literal = char[size];

template <class class_type, size_t size>
auto wrap_getter(typename string_literal<size> class_type::*member)
{
	return [member](const class_type &instance) {
		return std::string_view(instance.*member);
	};
}


template <class class_type, size_t size>
auto wrap_setter(typename string_literal<size> class_type::*member)
{
	return [member](class_type &instance, const std::string_view &value) {
		strcpy_s(instance.*member, value.data());
	};
	//return [member](class_type &instance, const py::str &) {
	//	strcpy_s(instance.*member, str->raw_str());
	//};
}

#define DEF_PROPERTY(cls, name) \
		.def_property(#name, wrap_getter(&cls::name), wrap_setter(&cls::name))

PYBIND11_MODULE(vnctptd, m)
{
    py::class_<CThostFtdcTraderSpi, PyCThostFtdcTraderSpi>(m, "CThostFtdcTraderSpi")
        ;
    py::class_<CThostFtdcTraderApi, PyCThostFtdcTraderApi>(m, "CThostFtdcTraderApi")
		.def_static("CreateFtdcTraderApi", &PyCThostFtdcTraderApi::CreateFtdcTraderApi)
		.def_static("GetApiVersion", &PyCThostFtdcTraderApi::GetApiVersion)
		.def("Release", &PyCThostFtdcTraderApi::Release)
		.def("Init", &PyCThostFtdcTraderApi::Init)
		.def("Join", &PyCThostFtdcTraderApi::Join)
		.def("GetTradingDay", &PyCThostFtdcTraderApi::GetTradingDay)
		.def("RegisterFront", &PyCThostFtdcTraderApi::RegisterFront)
		.def("RegisterNameServer", &PyCThostFtdcTraderApi::RegisterNameServer)
		.def("RegisterFensUserInfo", &PyCThostFtdcTraderApi::RegisterFensUserInfo)
		.def("RegisterSpi", &PyCThostFtdcTraderApi::RegisterSpi)
		.def("SubscribePrivateTopic", &PyCThostFtdcTraderApi::SubscribePrivateTopic)
		.def("SubscribePublicTopic", &PyCThostFtdcTraderApi::SubscribePublicTopic)
		.def("ReqAuthenticate", &PyCThostFtdcTraderApi::ReqAuthenticate)
		.def("ReqUserLogin", &PyCThostFtdcTraderApi::ReqUserLogin)
		.def("ReqUserLogout", &PyCThostFtdcTraderApi::ReqUserLogout)
		.def("ReqUserPasswordUpdate", &PyCThostFtdcTraderApi::ReqUserPasswordUpdate)
		.def("ReqTradingAccountPasswordUpdate", &PyCThostFtdcTraderApi::ReqTradingAccountPasswordUpdate)
		.def("ReqOrderInsert", &PyCThostFtdcTraderApi::ReqOrderInsert)
		.def("ReqParkedOrderInsert", &PyCThostFtdcTraderApi::ReqParkedOrderInsert)
		.def("ReqParkedOrderAction", &PyCThostFtdcTraderApi::ReqParkedOrderAction)
		.def("ReqOrderAction", &PyCThostFtdcTraderApi::ReqOrderAction)
		.def("ReqQueryMaxOrderVolume", &PyCThostFtdcTraderApi::ReqQueryMaxOrderVolume)
		.def("ReqSettlementInfoConfirm", &PyCThostFtdcTraderApi::ReqSettlementInfoConfirm)
		.def("ReqRemoveParkedOrder", &PyCThostFtdcTraderApi::ReqRemoveParkedOrder)
		.def("ReqRemoveParkedOrderAction", &PyCThostFtdcTraderApi::ReqRemoveParkedOrderAction)
		.def("ReqExecOrderInsert", &PyCThostFtdcTraderApi::ReqExecOrderInsert)
		.def("ReqExecOrderAction", &PyCThostFtdcTraderApi::ReqExecOrderAction)
		.def("ReqForQuoteInsert", &PyCThostFtdcTraderApi::ReqForQuoteInsert)
		.def("ReqQuoteInsert", &PyCThostFtdcTraderApi::ReqQuoteInsert)
		.def("ReqQuoteAction", &PyCThostFtdcTraderApi::ReqQuoteAction)
		.def("ReqLockInsert", &PyCThostFtdcTraderApi::ReqLockInsert)
		.def("ReqCombActionInsert", &PyCThostFtdcTraderApi::ReqCombActionInsert)
		.def("ReqQryOrder", &PyCThostFtdcTraderApi::ReqQryOrder)
		.def("ReqQryTrade", &PyCThostFtdcTraderApi::ReqQryTrade)
		.def("ReqQryInvestorPosition", &PyCThostFtdcTraderApi::ReqQryInvestorPosition)
		.def("ReqQryTradingAccount", &PyCThostFtdcTraderApi::ReqQryTradingAccount)
		.def("ReqQryInvestor", &PyCThostFtdcTraderApi::ReqQryInvestor)
		.def("ReqQryTradingCode", &PyCThostFtdcTraderApi::ReqQryTradingCode)
		.def("ReqQryInstrumentMarginRate", &PyCThostFtdcTraderApi::ReqQryInstrumentMarginRate)
		.def("ReqQryInstrumentCommissionRate", &PyCThostFtdcTraderApi::ReqQryInstrumentCommissionRate)
		.def("ReqQryExchange", &PyCThostFtdcTraderApi::ReqQryExchange)
		.def("ReqQryProduct", &PyCThostFtdcTraderApi::ReqQryProduct)
		.def("ReqQryInstrument", &PyCThostFtdcTraderApi::ReqQryInstrument)
		.def("ReqQryDepthMarketData", &PyCThostFtdcTraderApi::ReqQryDepthMarketData)
		.def("ReqQrySettlementInfo", &PyCThostFtdcTraderApi::ReqQrySettlementInfo)
		.def("ReqQryTransferBank", &PyCThostFtdcTraderApi::ReqQryTransferBank)
		.def("ReqQryInvestorPositionDetail", &PyCThostFtdcTraderApi::ReqQryInvestorPositionDetail)
		.def("ReqQryNotice", &PyCThostFtdcTraderApi::ReqQryNotice)
		.def("ReqQrySettlementInfoConfirm", &PyCThostFtdcTraderApi::ReqQrySettlementInfoConfirm)
		.def("ReqQryInvestorPositionCombineDetail", &PyCThostFtdcTraderApi::ReqQryInvestorPositionCombineDetail)
		.def("ReqQryCFMMCTradingAccountKey", &PyCThostFtdcTraderApi::ReqQryCFMMCTradingAccountKey)
		.def("ReqQryEWarrantOffset", &PyCThostFtdcTraderApi::ReqQryEWarrantOffset)
		.def("ReqQryInvestorProductGroupMargin", &PyCThostFtdcTraderApi::ReqQryInvestorProductGroupMargin)
		.def("ReqQryExchangeMarginRate", &PyCThostFtdcTraderApi::ReqQryExchangeMarginRate)
		.def("ReqQryExchangeMarginRateAdjust", &PyCThostFtdcTraderApi::ReqQryExchangeMarginRateAdjust)
		.def("ReqQryExchangeRate", &PyCThostFtdcTraderApi::ReqQryExchangeRate)
		.def("ReqQrySecAgentACIDMap", &PyCThostFtdcTraderApi::ReqQrySecAgentACIDMap)
		.def("ReqQryProductExchRate", &PyCThostFtdcTraderApi::ReqQryProductExchRate)
		.def("ReqQryProductGroup", &PyCThostFtdcTraderApi::ReqQryProductGroup)
		.def("ReqQryOptionInstrTradeCost", &PyCThostFtdcTraderApi::ReqQryOptionInstrTradeCost)
		.def("ReqQryOptionInstrCommRate", &PyCThostFtdcTraderApi::ReqQryOptionInstrCommRate)
		.def("ReqQryExecOrder", &PyCThostFtdcTraderApi::ReqQryExecOrder)
		.def("ReqQryForQuote", &PyCThostFtdcTraderApi::ReqQryForQuote)
		.def("ReqQryQuote", &PyCThostFtdcTraderApi::ReqQryQuote)
		.def("ReqQryLock", &PyCThostFtdcTraderApi::ReqQryLock)
		.def("ReqQryLockPosition", &PyCThostFtdcTraderApi::ReqQryLockPosition)
		.def("ReqQryInvestorLevel", &PyCThostFtdcTraderApi::ReqQryInvestorLevel)
		.def("ReqQryExecFreeze", &PyCThostFtdcTraderApi::ReqQryExecFreeze)
		.def("ReqQryCombInstrumentGuard", &PyCThostFtdcTraderApi::ReqQryCombInstrumentGuard)
		.def("ReqQryCombAction", &PyCThostFtdcTraderApi::ReqQryCombAction)
		.def("ReqQryTransferSerial", &PyCThostFtdcTraderApi::ReqQryTransferSerial)
		.def("ReqQryAccountregister", &PyCThostFtdcTraderApi::ReqQryAccountregister)
		.def("ReqQryContractBank", &PyCThostFtdcTraderApi::ReqQryContractBank)
		.def("ReqQryParkedOrder", &PyCThostFtdcTraderApi::ReqQryParkedOrder)
		.def("ReqQryParkedOrderAction", &PyCThostFtdcTraderApi::ReqQryParkedOrderAction)
		.def("ReqQryTradingNotice", &PyCThostFtdcTraderApi::ReqQryTradingNotice)
		.def("ReqQryBrokerTradingParams", &PyCThostFtdcTraderApi::ReqQryBrokerTradingParams)
		.def("ReqQryBrokerTradingAlgos", &PyCThostFtdcTraderApi::ReqQryBrokerTradingAlgos)
		.def("ReqQueryCFMMCTradingAccountToken", &PyCThostFtdcTraderApi::ReqQueryCFMMCTradingAccountToken)
		.def("ReqFromBankToFutureByFuture", &PyCThostFtdcTraderApi::ReqFromBankToFutureByFuture)
		.def("ReqFromFutureToBankByFuture", &PyCThostFtdcTraderApi::ReqFromFutureToBankByFuture)
		.def("ReqQueryBankAccountMoneyByFuture", &PyCThostFtdcTraderApi::ReqQueryBankAccountMoneyByFuture)
        ;

}
