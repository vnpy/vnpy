#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

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
    pybind11::class_<ITapTrade::TapAPICommodityInfo> c(parent, "TapAPICommodityInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICommodityInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityName", CommodityName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityEngName", CommodityEngName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateExchangeNo", RelateExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityType", RelateCommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityNo", RelateCommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateExchangeNo2", RelateExchangeNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityType2", RelateCommodityType2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "RelateCommodityNo2", RelateCommodityNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "TradeCurrency", TradeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "ContractSize", ContractSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "OpenCloseMode", OpenCloseMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "StrikePriceTimes", StrikePriceTimes);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityTickSize", CommodityTickSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityDenominator", CommodityDenominator);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CmbDirect", CmbDirect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "DeliveryMode", DeliveryMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "DeliveryDays", DeliveryDays);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "AddOneTime", AddOneTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "CommodityTimeZone", CommodityTimeZone);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICommodityInfo, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICommodityInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICommodityInfo", c);
}
void generate_class_ITapTrade_TapAPITradeContractInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeContractInfo> c(parent, "TapAPITradeContractInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeContractInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractNo1", ContractNo1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "StrikePrice1", StrikePrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CallOrPutFlag1", CallOrPutFlag1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractType", ContractType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "QuoteUnderlyingContract", QuoteUnderlyingContract);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractName", ContractName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "ContractExpDate", ContractExpDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "LastTradeDate", LastTradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeContractInfo, "FirstNoticeDate", FirstNoticeDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeContractInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeContractInfo", c);
}
void generate_class_ITapTrade_TapAPICurrencyInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICurrencyInfo> c(parent, "TapAPICurrencyInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICurrencyInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "TradeRate", TradeRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "TradeRate2", TradeRate2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "FutureAlg", FutureAlg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPICurrencyInfo, "OptionAlg", OptionAlg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPICurrencyInfo, c);
    module_vntap::objects.emplace("ITapTrade::TapAPICurrencyInfo", c);
}
void generate_class_ITapTrade_TapAPITradeMessageReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeMessageReq> c(parent, "TapAPITradeMessageReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeMessageReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "BenginSendDateTime", BenginSendDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessageReq, "EndSendDateTime", EndSendDateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeMessageReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeMessageReq", c);
}
void generate_class_ITapTrade_TapAPITradeMessage(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeMessage> c(parent, "TapAPITradeMessage");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeMessage>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "SerialID", SerialID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgValidDateTime", TMsgValidDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgTitle", TMsgTitle);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgContent", TMsgContent);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgType", TMsgType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "TMsgLevel", TMsgLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "IsSendBySMS", IsSendBySMS);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "IsSendByEMail", IsSendByEMail);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "Sender", Sender);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPITradeMessage, "SendDateTime", SendDateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPITradeMessage, c);
    module_vntap::objects.emplace("ITapTrade::TapAPITradeMessage", c);
}
void generate_class_ITapTrade_TapAPIBillQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIBillQryReq> c(parent, "TapAPIBillQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIBillQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "BillType", BillType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "BillDate", BillDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryReq, "BillFileType", BillFileType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIBillQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIBillQryReq", c);
}
void generate_class_ITapTrade_TapAPIBillQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIBillQryRsp> c(parent, "TapAPIBillQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIBillQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryRsp, "Reqdata", Reqdata);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryRsp, "BillLen", BillLen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIBillQryRsp, "BillText", BillText);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIBillQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIBillQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisOrderQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisOrderQryReq> c(parent, "TapAPIHisOrderQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, "EndDate", EndDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisOrderQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisOrderQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisOrderQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisOrderQryRsp> c(parent, "TapAPIHisOrderQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderCanceledQty", OrderCanceledQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderStreamID", OrderStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "UpperChannelNo", UpperChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderLocalNo", OrderLocalNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "UpperStreamID", UpperStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderParentSystemNo", OrderParentSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderInsertUserNo", OrderInsertUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderInsertTime", OrderInsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderCommandUserNo", OrderCommandUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderUpdateUserNo", OrderUpdateUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderUpdateTime", OrderUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderState", OrderState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchPrice", OrderMatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchPrice2", OrderMatchPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchQty", OrderMatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchQty2", OrderMatchQty2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "ErrorText", ErrorText);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsBackInput", IsBackInput);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "IsAddOne", IsAddOne);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "MinClipSize", MinClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "MaxClipSize", MaxClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "LicenseNo", LicenseNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TacticsType", TacticsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TriggerCondition", TriggerCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, "TriggerPriceType", TriggerPriceType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisOrderQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisOrderQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisMatchQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisMatchQryReq> c(parent, "TapAPIHisMatchQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisMatchQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, "CountType", CountType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisMatchQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisMatchQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisMatchQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisMatchQryRsp> c(parent, "TapAPIHisMatchQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisMatchQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "SettleDate", SettleDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "TradeDate", TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchPrice", MatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchQty", MatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchNo", MatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchStreamID", MatchStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchCmbNo", MatchCmbNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ExchangeMatchNo", ExchangeMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchUpperStreamID", MatchUpperStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "PremiumIncome", PremiumIncome);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "PremiumPay", PremiumPay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFee", AccountFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFeeCurrencyGroup", AccountFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFeeCurrency", AccountFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "IsManualFee", IsManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "AccountOtherFee", AccountOtherFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFee", UpperFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFeeCurrencyGroup", UpperFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFeeCurrency", UpperFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "IsUpperManualFee", IsUpperManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperOtherFee", UpperOtherFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "MatchDateTime", MatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "UpperMatchDateTime", UpperMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CloseProfit", CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "ClosePrice", ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "CloseQty", CloseQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "SettleGroupNo", SettleGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "OperatorNo", OperatorNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, "OperateTime", OperateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisMatchQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisMatchQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisOrderProcessQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisOrderProcessQryReq> c(parent, "TapAPIHisOrderProcessQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderProcessQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderProcessQryReq, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisOrderProcessQryReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisOrderProcessQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisOrderProcessQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisPositionQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisPositionQryReq> c(parent, "TapAPIHisPositionQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisPositionQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, "SettleFlag", SettleFlag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisPositionQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisPositionQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisPositionQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisPositionQryRsp> c(parent, "TapAPIHisPositionQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisPositionQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "SettleDate", SettleDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "OpenDate", OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionPrice", PositionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionQty", PositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionNo", PositionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "CurrencyGroup", CurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "Currency", Currency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PreSettlePrice", PreSettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "SettlePrice", SettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "PositionDProfit", PositionDProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "LMEPositionProfit", LMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "AccountInitialMargin", AccountInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "UpperInitialMargin", UpperInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, "SettleGroupNo", SettleGroupNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisPositionQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisPositionQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisDeliveryQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisDeliveryQryReq> c(parent, "TapAPIHisDeliveryQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisDeliveryQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, "CountType", CountType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisDeliveryQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisDeliveryQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisDeliveryQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisDeliveryQryRsp> c(parent, "TapAPIHisDeliveryQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisDeliveryQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryDate", DeliveryDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenDate", OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenSide", OpenSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenPrice", OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryPrice", DeliveryPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryQty", DeliveryQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "FrozenQty", FrozenQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenNo", OpenNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityCurrencyGroupy", CommodityCurrencyGroupy);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "PreSettlePrice", PreSettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryProfit", DeliveryProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFrozenInitialMargin", AccountFrozenInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFrozenMaintenanceMargin", AccountFrozenMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFrozenInitialMargin", UpperFrozenInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFrozenMaintenanceMargin", UpperFrozenMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFeeCurrencyGroup", AccountFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFeeCurrency", AccountFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountDeliveryFee", AccountDeliveryFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFeeCurrencyGroup", UpperFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFeeCurrency", UpperFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperDeliveryFee", UpperDeliveryFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryMode", DeliveryMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OperatorNo", OperatorNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, "SettleGourpNo", SettleGourpNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIHisDeliveryQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIHisDeliveryQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountCashAdjustQryReq> c(parent, "TapAPIAccountCashAdjustQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountCashAdjustQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "SerialID", SerialID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, "EndDate", EndDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountCashAdjustQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountCashAdjustQryRsp> c(parent, "TapAPIAccountCashAdjustQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountCashAdjustQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustType", CashAdjustType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustValue", CashAdjustValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustRemark", CashAdjustRemark);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "OperatorNo", OperatorNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountBank", AccountBank);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "BankAccount", BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountLWFlag", AccountLWFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CompanyBank", CompanyBank);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "InternalBankAccount", InternalBankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CompanyLWFlag", CompanyLWFlag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountCashAdjustQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountCashAdjustQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountFeeRentQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountFeeRentQryReq> c(parent, "TapAPIAccountFeeRentQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountFeeRentQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountFeeRentQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountFeeRentQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountFeeRentQryRsp> c(parent, "TapAPIAccountFeeRentQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountFeeRentQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CalculateMode", CalculateMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "OpenCloseFee", OpenCloseFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CloseTodayFee", CloseTodayFee);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountFeeRentQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountFeeRentQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountMarginRentQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountMarginRentQryReq> c(parent, "TapAPIAccountMarginRentQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountMarginRentQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountMarginRentQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountMarginRentQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountMarginRentQryRsp> c(parent, "TapAPIAccountMarginRentQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountMarginRentQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CalculateMode", CalculateMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "InitialMargin", InitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "MaintenanceMargin", MaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "SellInitialMargin", SellInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "SellMaintenanceMargin", SellMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, "LockMargin", LockMargin);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIAccountMarginRentQryRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIAccountMarginRentQryRsp", c);
}
void generate_class_ITapTrade_TapAPIOrderQuoteMarketNotice(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderQuoteMarketNotice> c(parent, "TapAPIOrderQuoteMarketNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderQuoteMarketNotice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderQuoteMarketNotice, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderQuoteMarketNotice", c);
}
void generate_class_ITapTrade_TapAPIOrderMarketInsertReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderMarketInsertReq> c(parent, "TapAPIOrderMarketInsertReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketInsertReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "BuyPositionEffect", BuyPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "SellPositionEffect", SellPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderBuyPrice", OrderBuyPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSellPrice", OrderSellPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderBuyQty", OrderBuyQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSellQty", OrderSellQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ClientBuyOrderNo", ClientBuyOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "ClientSellOrderNo", ClientSellOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, "Remark", Remark);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderMarketInsertReq, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderMarketInsertReq", c);
}
void generate_class_ITapTrade_TapAPIOrderMarketInsertRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderMarketInsertRsp> c(parent, "TapAPIOrderMarketInsertRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketInsertRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "BuyPositionEffect", BuyPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "SellPositionEffect", SellPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyPrice", OrderBuyPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellPrice", OrderSellPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyQty", OrderBuyQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellQty", OrderSellQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyNo", OrderBuyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellNo", OrderSellNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderMarketUserNo", OrderMarketUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderMarketTime", OrderMarketTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientBuyOrderNo", ClientBuyOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientSellOrderNo", ClientSellOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ErrorText", ErrorText);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientLocalIP", ClientLocalIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientMac", ClientMac);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientIP", ClientIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, "Remark", Remark);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntap, ITapTrade::TapAPIOrderMarketInsertRsp, c);
    module_vntap::objects.emplace("ITapTrade::TapAPIOrderMarketInsertRsp", c);
}
