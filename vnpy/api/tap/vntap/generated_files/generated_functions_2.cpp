#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <c2py/c2py.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"


void generate_class_ITapTrade_TapAPICommodityInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPICommodityInfo
    pybind11::class_<ITapTrade::TapAPICommodityInfo> c(parent, "TapAPICommodityInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICommodityInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPICommodityInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPICommodityInfo::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityType", CommodityType);
    // ITapTrade::TapAPICommodityInfo::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPICommodityInfo::CommodityName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityName", CommodityName);
    // ITapTrade::TapAPICommodityInfo::CommodityEngName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityEngName", CommodityEngName);
    // ITapTrade::TapAPICommodityInfo::RelateExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateExchangeNo", RelateExchangeNo);
    // ITapTrade::TapAPICommodityInfo::RelateCommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityType", RelateCommodityType);
    // ITapTrade::TapAPICommodityInfo::RelateCommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityNo", RelateCommodityNo);
    // ITapTrade::TapAPICommodityInfo::RelateExchangeNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateExchangeNo2", RelateExchangeNo2);
    // ITapTrade::TapAPICommodityInfo::RelateCommodityType2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityType2", RelateCommodityType2);
    // ITapTrade::TapAPICommodityInfo::RelateCommodityNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityNo2", RelateCommodityNo2);
    // ITapTrade::TapAPICommodityInfo::CurrencyGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CurrencyGroupNo", CurrencyGroupNo);
    // ITapTrade::TapAPICommodityInfo::TradeCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "TradeCurrency", TradeCurrency);
    // ITapTrade::TapAPICommodityInfo::ContractSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "ContractSize", ContractSize);
    // ITapTrade::TapAPICommodityInfo::OpenCloseMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "OpenCloseMode", OpenCloseMode);
    // ITapTrade::TapAPICommodityInfo::StrikePriceTimes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "StrikePriceTimes", StrikePriceTimes);
    // ITapTrade::TapAPICommodityInfo::CommodityTickSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityTickSize", CommodityTickSize);
    // ITapTrade::TapAPICommodityInfo::CommodityDenominator
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityDenominator", CommodityDenominator);
    // ITapTrade::TapAPICommodityInfo::CmbDirect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CmbDirect", CmbDirect);
    // ITapTrade::TapAPICommodityInfo::DeliveryMode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "DeliveryMode", DeliveryMode);
    // ITapTrade::TapAPICommodityInfo::DeliveryDays
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "DeliveryDays", DeliveryDays);
    // ITapTrade::TapAPICommodityInfo::AddOneTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "AddOneTime", AddOneTime);
    // ITapTrade::TapAPICommodityInfo::CommodityTimeZone
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityTimeZone", CommodityTimeZone);
    // ITapTrade::TapAPICommodityInfo::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICommodityInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICommodityInfo", c);
}
void generate_class_ITapTrade_TapAPITradeContractInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPITradeContractInfo
    pybind11::class_<ITapTrade::TapAPITradeContractInfo> c(parent, "TapAPITradeContractInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeContractInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPITradeContractInfo::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPITradeContractInfo::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CommodityType", CommodityType);
    // ITapTrade::TapAPITradeContractInfo::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPITradeContractInfo::ContractNo1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractNo1", ContractNo1);
    // ITapTrade::TapAPITradeContractInfo::StrikePrice1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "StrikePrice1", StrikePrice1);
    // ITapTrade::TapAPITradeContractInfo::CallOrPutFlag1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CallOrPutFlag1", CallOrPutFlag1);
    // ITapTrade::TapAPITradeContractInfo::ContractNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractNo2", ContractNo2);
    // ITapTrade::TapAPITradeContractInfo::StrikePrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "StrikePrice2", StrikePrice2);
    // ITapTrade::TapAPITradeContractInfo::CallOrPutFlag2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CallOrPutFlag2", CallOrPutFlag2);
    // ITapTrade::TapAPITradeContractInfo::ContractType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractType", ContractType);
    // ITapTrade::TapAPITradeContractInfo::QuoteUnderlyingContract
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "QuoteUnderlyingContract", QuoteUnderlyingContract);
    // ITapTrade::TapAPITradeContractInfo::ContractName
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractName", ContractName);
    // ITapTrade::TapAPITradeContractInfo::ContractExpDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractExpDate", ContractExpDate);
    // ITapTrade::TapAPITradeContractInfo::LastTradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "LastTradeDate", LastTradeDate);
    // ITapTrade::TapAPITradeContractInfo::FirstNoticeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "FirstNoticeDate", FirstNoticeDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeContractInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeContractInfo", c);
}
void generate_class_ITapTrade_TapAPICurrencyInfo(pybind11::object & parent)
{
    // ITapTrade::TapAPICurrencyInfo
    pybind11::class_<ITapTrade::TapAPICurrencyInfo> c(parent, "TapAPICurrencyInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICurrencyInfo>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPICurrencyInfo::CurrencyNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "CurrencyNo", CurrencyNo);
    // ITapTrade::TapAPICurrencyInfo::CurrencyGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "CurrencyGroupNo", CurrencyGroupNo);
    // ITapTrade::TapAPICurrencyInfo::TradeRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "TradeRate", TradeRate);
    // ITapTrade::TapAPICurrencyInfo::TradeRate2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "TradeRate2", TradeRate2);
    // ITapTrade::TapAPICurrencyInfo::FutureAlg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "FutureAlg", FutureAlg);
    // ITapTrade::TapAPICurrencyInfo::OptionAlg
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "OptionAlg", OptionAlg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICurrencyInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICurrencyInfo", c);
}
void generate_class_ITapTrade_TapAPITradeMessageReq(pybind11::object & parent)
{
    // ITapTrade::TapAPITradeMessageReq
    pybind11::class_<ITapTrade::TapAPITradeMessageReq> c(parent, "TapAPITradeMessageReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeMessageReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPITradeMessageReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPITradeMessageReq::AccountAttributeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "AccountAttributeNo", AccountAttributeNo);
    // ITapTrade::TapAPITradeMessageReq::BenginSendDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "BenginSendDateTime", BenginSendDateTime);
    // ITapTrade::TapAPITradeMessageReq::EndSendDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "EndSendDateTime", EndSendDateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeMessageReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeMessageReq", c);
}
void generate_class_ITapTrade_TapAPITradeMessage(pybind11::object & parent)
{
    // ITapTrade::TapAPITradeMessage
    pybind11::class_<ITapTrade::TapAPITradeMessage> c(parent, "TapAPITradeMessage");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeMessage>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPITradeMessage::SerialID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "SerialID", SerialID);
    // ITapTrade::TapAPITradeMessage::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "AccountNo", AccountNo);
    // ITapTrade::TapAPITradeMessage::TMsgValidDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgValidDateTime", TMsgValidDateTime);
    // ITapTrade::TapAPITradeMessage::TMsgTitle
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgTitle", TMsgTitle);
    // ITapTrade::TapAPITradeMessage::TMsgContent
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgContent", TMsgContent);
    // ITapTrade::TapAPITradeMessage::TMsgType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgType", TMsgType);
    // ITapTrade::TapAPITradeMessage::TMsgLevel
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgLevel", TMsgLevel);
    // ITapTrade::TapAPITradeMessage::IsSendBySMS
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "IsSendBySMS", IsSendBySMS);
    // ITapTrade::TapAPITradeMessage::IsSendByEMail
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "IsSendByEMail", IsSendByEMail);
    // ITapTrade::TapAPITradeMessage::Sender
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "Sender", Sender);
    // ITapTrade::TapAPITradeMessage::SendDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "SendDateTime", SendDateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeMessage, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeMessage", c);
}
void generate_class_ITapTrade_TapAPIBillQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIBillQryReq
    pybind11::class_<ITapTrade::TapAPIBillQryReq> c(parent, "TapAPIBillQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIBillQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIBillQryReq::UserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "UserNo", UserNo);
    // ITapTrade::TapAPIBillQryReq::BillType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "BillType", BillType);
    // ITapTrade::TapAPIBillQryReq::BillDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "BillDate", BillDate);
    // ITapTrade::TapAPIBillQryReq::BillFileType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "BillFileType", BillFileType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIBillQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIBillQryReq", c);
}
void generate_class_ITapTrade_TapAPIBillQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIBillQryRsp
    pybind11::class_<ITapTrade::TapAPIBillQryRsp> c(parent, "TapAPIBillQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIBillQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIBillQryRsp::Reqdata
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryRsp, "Reqdata", Reqdata);
    // ITapTrade::TapAPIBillQryRsp::BillLen
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryRsp, "BillLen", BillLen);
    // ITapTrade::TapAPIBillQryRsp::BillText
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryRsp, "BillText", BillText);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIBillQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIBillQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisOrderQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisOrderQryReq
    pybind11::class_<ITapTrade::TapAPIHisOrderQryReq> c(parent, "TapAPIHisOrderQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisOrderQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisOrderQryReq::AccountAttributeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "AccountAttributeNo", AccountAttributeNo);
    // ITapTrade::TapAPIHisOrderQryReq::BeginDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "BeginDate", BeginDate);
    // ITapTrade::TapAPIHisOrderQryReq::EndDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "EndDate", EndDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisOrderQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisOrderQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisOrderQryRsp
    pybind11::class_<ITapTrade::TapAPIHisOrderQryRsp> c(parent, "TapAPIHisOrderQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisOrderQryRsp::Date
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "Date", Date);
    // ITapTrade::TapAPIHisOrderQryRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisOrderQryRsp::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIHisOrderQryRsp::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CommodityType", CommodityType);
    // ITapTrade::TapAPIHisOrderQryRsp::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIHisOrderQryRsp::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ContractNo", ContractNo);
    // ITapTrade::TapAPIHisOrderQryRsp::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIHisOrderQryRsp::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIHisOrderQryRsp::ContractNo2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ContractNo2", ContractNo2);
    // ITapTrade::TapAPIHisOrderQryRsp::StrikePrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "StrikePrice2", StrikePrice2);
    // ITapTrade::TapAPIHisOrderQryRsp::CallOrPutFlag2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CallOrPutFlag2", CallOrPutFlag2);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderType", OrderType);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSource", OrderSource);
    // ITapTrade::TapAPIHisOrderQryRsp::TimeInForce
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TimeInForce", TimeInForce);
    // ITapTrade::TapAPIHisOrderQryRsp::ExpireTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ExpireTime", ExpireTime);
    // ITapTrade::TapAPIHisOrderQryRsp::IsRiskOrder
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsRiskOrder", IsRiskOrder);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSide", OrderSide);
    // ITapTrade::TapAPIHisOrderQryRsp::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPIHisOrderQryRsp::PositionEffect2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "PositionEffect2", PositionEffect2);
    // ITapTrade::TapAPIHisOrderQryRsp::InquiryNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "InquiryNo", InquiryNo);
    // ITapTrade::TapAPIHisOrderQryRsp::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderPrice", OrderPrice);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderPrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderPrice2", OrderPrice2);
    // ITapTrade::TapAPIHisOrderQryRsp::StopPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "StopPrice", StopPrice);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderQty", OrderQty);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderMinQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMinQty", OrderMinQty);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderCanceledQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderCanceledQty", OrderCanceledQty);
    // ITapTrade::TapAPIHisOrderQryRsp::RefInt
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "RefInt", RefInt);
    // ITapTrade::TapAPIHisOrderQryRsp::RefDouble
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "RefDouble", RefDouble);
    // ITapTrade::TapAPIHisOrderQryRsp::RefString
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "RefString", RefString);
    // ITapTrade::TapAPIHisOrderQryRsp::ServerFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ServerFlag", ServerFlag);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderNo", OrderNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderStreamID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderStreamID", OrderStreamID);
    // ITapTrade::TapAPIHisOrderQryRsp::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "UpperNo", UpperNo);
    // ITapTrade::TapAPIHisOrderQryRsp::UpperChannelNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "UpperChannelNo", UpperChannelNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderLocalNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderLocalNo", OrderLocalNo);
    // ITapTrade::TapAPIHisOrderQryRsp::UpperStreamID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "UpperStreamID", UpperStreamID);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSystemNo", OrderSystemNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderExchangeSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderParentSystemNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderParentSystemNo", OrderParentSystemNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderInsertUserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderInsertUserNo", OrderInsertUserNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderInsertTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderInsertTime", OrderInsertTime);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderCommandUserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderCommandUserNo", OrderCommandUserNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderUpdateUserNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderUpdateUserNo", OrderUpdateUserNo);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderUpdateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderUpdateTime", OrderUpdateTime);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderState", OrderState);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderMatchPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchPrice", OrderMatchPrice);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderMatchPrice2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchPrice2", OrderMatchPrice2);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderMatchQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchQty", OrderMatchQty);
    // ITapTrade::TapAPIHisOrderQryRsp::OrderMatchQty2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchQty2", OrderMatchQty2);
    // ITapTrade::TapAPIHisOrderQryRsp::ErrorCode
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ErrorCode", ErrorCode);
    // ITapTrade::TapAPIHisOrderQryRsp::ErrorText
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ErrorText", ErrorText);
    // ITapTrade::TapAPIHisOrderQryRsp::IsBackInput
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsBackInput", IsBackInput);
    // ITapTrade::TapAPIHisOrderQryRsp::IsDeleted
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsDeleted", IsDeleted);
    // ITapTrade::TapAPIHisOrderQryRsp::IsAddOne
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsAddOne", IsAddOne);
    // ITapTrade::TapAPIHisOrderQryRsp::AddOneIsValid
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "AddOneIsValid", AddOneIsValid);
    // ITapTrade::TapAPIHisOrderQryRsp::MinClipSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "MinClipSize", MinClipSize);
    // ITapTrade::TapAPIHisOrderQryRsp::MaxClipSize
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "MaxClipSize", MaxClipSize);
    // ITapTrade::TapAPIHisOrderQryRsp::LicenseNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "LicenseNo", LicenseNo);
    // ITapTrade::TapAPIHisOrderQryRsp::TacticsType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TacticsType", TacticsType);
    // ITapTrade::TapAPIHisOrderQryRsp::TriggerCondition
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TriggerCondition", TriggerCondition);
    // ITapTrade::TapAPIHisOrderQryRsp::TriggerPriceType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TriggerPriceType", TriggerPriceType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisOrderQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisMatchQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisMatchQryReq
    pybind11::class_<ITapTrade::TapAPIHisMatchQryReq> c(parent, "TapAPIHisMatchQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisMatchQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisMatchQryReq::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisMatchQryReq::AccountAttributeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "AccountAttributeNo", AccountAttributeNo);
    // ITapTrade::TapAPIHisMatchQryReq::BeginDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "BeginDate", BeginDate);
    // ITapTrade::TapAPIHisMatchQryReq::EndDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "EndDate", EndDate);
    // ITapTrade::TapAPIHisMatchQryReq::CountType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "CountType", CountType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisMatchQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisMatchQryRsp(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisMatchQryRsp
    pybind11::class_<ITapTrade::TapAPIHisMatchQryRsp> c(parent, "TapAPIHisMatchQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisMatchQryRsp>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisMatchQryRsp::SettleDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "SettleDate", SettleDate);
    // ITapTrade::TapAPIHisMatchQryRsp::TradeDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "TradeDate", TradeDate);
    // ITapTrade::TapAPIHisMatchQryRsp::AccountNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountNo", AccountNo);
    // ITapTrade::TapAPIHisMatchQryRsp::ExchangeNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ExchangeNo", ExchangeNo);
    // ITapTrade::TapAPIHisMatchQryRsp::CommodityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityType", CommodityType);
    // ITapTrade::TapAPIHisMatchQryRsp::CommodityNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityNo", CommodityNo);
    // ITapTrade::TapAPIHisMatchQryRsp::ContractNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ContractNo", ContractNo);
    // ITapTrade::TapAPIHisMatchQryRsp::StrikePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "StrikePrice", StrikePrice);
    // ITapTrade::TapAPIHisMatchQryRsp::CallOrPutFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CallOrPutFlag", CallOrPutFlag);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchSource
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchSource", MatchSource);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchSide
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchSide", MatchSide);
    // ITapTrade::TapAPIHisMatchQryRsp::PositionEffect
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "PositionEffect", PositionEffect);
    // ITapTrade::TapAPIHisMatchQryRsp::HedgeFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "HedgeFlag", HedgeFlag);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchPrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchPrice", MatchPrice);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchQty", MatchQty);
    // ITapTrade::TapAPIHisMatchQryRsp::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "OrderNo", OrderNo);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchNo", MatchNo);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchStreamID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchStreamID", MatchStreamID);
    // ITapTrade::TapAPIHisMatchQryRsp::UpperNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperNo", UpperNo);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchCmbNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchCmbNo", MatchCmbNo);
    // ITapTrade::TapAPIHisMatchQryRsp::ExchangeMatchNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ExchangeMatchNo", ExchangeMatchNo);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchUpperStreamID
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchUpperStreamID", MatchUpperStreamID);
    // ITapTrade::TapAPIHisMatchQryRsp::CommodityCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    // ITapTrade::TapAPIHisMatchQryRsp::CommodityCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityCurrency", CommodityCurrency);
    // ITapTrade::TapAPIHisMatchQryRsp::Turnover
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "Turnover", Turnover);
    // ITapTrade::TapAPIHisMatchQryRsp::PremiumIncome
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "PremiumIncome", PremiumIncome);
    // ITapTrade::TapAPIHisMatchQryRsp::PremiumPay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "PremiumPay", PremiumPay);
    // ITapTrade::TapAPIHisMatchQryRsp::AccountFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFee", AccountFee);
    // ITapTrade::TapAPIHisMatchQryRsp::AccountFeeCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFeeCurrencyGroup", AccountFeeCurrencyGroup);
    // ITapTrade::TapAPIHisMatchQryRsp::AccountFeeCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFeeCurrency", AccountFeeCurrency);
    // ITapTrade::TapAPIHisMatchQryRsp::IsManualFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "IsManualFee", IsManualFee);
    // ITapTrade::TapAPIHisMatchQryRsp::AccountOtherFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountOtherFee", AccountOtherFee);
    // ITapTrade::TapAPIHisMatchQryRsp::UpperFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFee", UpperFee);
    // ITapTrade::TapAPIHisMatchQryRsp::UpperFeeCurrencyGroup
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFeeCurrencyGroup", UpperFeeCurrencyGroup);
    // ITapTrade::TapAPIHisMatchQryRsp::UpperFeeCurrency
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFeeCurrency", UpperFeeCurrency);
    // ITapTrade::TapAPIHisMatchQryRsp::IsUpperManualFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "IsUpperManualFee", IsUpperManualFee);
    // ITapTrade::TapAPIHisMatchQryRsp::UpperOtherFee
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperOtherFee", UpperOtherFee);
    // ITapTrade::TapAPIHisMatchQryRsp::MatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchDateTime", MatchDateTime);
    // ITapTrade::TapAPIHisMatchQryRsp::UpperMatchDateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperMatchDateTime", UpperMatchDateTime);
    // ITapTrade::TapAPIHisMatchQryRsp::CloseProfit
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CloseProfit", CloseProfit);
    // ITapTrade::TapAPIHisMatchQryRsp::ClosePrice
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ClosePrice", ClosePrice);
    // ITapTrade::TapAPIHisMatchQryRsp::CloseQty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CloseQty", CloseQty);
    // ITapTrade::TapAPIHisMatchQryRsp::SettleGroupNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "SettleGroupNo", SettleGroupNo);
    // ITapTrade::TapAPIHisMatchQryRsp::OperatorNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "OperatorNo", OperatorNo);
    // ITapTrade::TapAPIHisMatchQryRsp::OperateTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "OperateTime", OperateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisMatchQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisOrderProcessQryReq(pybind11::object & parent)
{
    // ITapTrade::TapAPIHisOrderProcessQryReq
    pybind11::class_<ITapTrade::TapAPIHisOrderProcessQryReq> c(parent, "TapAPIHisOrderProcessQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderProcessQryReq>)
        c.def(pybind11::init<>());
    // ITapTrade::TapAPIHisOrderProcessQryReq::Date
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderProcessQryReq, "Date", Date);
    // ITapTrade::TapAPIHisOrderProcessQryReq::OrderNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderProcessQryReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisOrderProcessQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisOrderProcessQryReq", c);
}
