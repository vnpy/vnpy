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


void generate_class_ITapTrade_TapAPITradeContractInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeContractInfo> c(parent, "TapAPITradeContractInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeContractInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "ContractNo1", ContractNo1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "StrikePrice1", StrikePrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "CallOrPutFlag1", CallOrPutFlag1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "ContractType", ContractType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "QuoteUnderlyingContract", QuoteUnderlyingContract);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "ContractName", ContractName);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "ContractExpDate", ContractExpDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "LastTradeDate", LastTradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeContractInfo, "FirstNoticeDate", FirstNoticeDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPITradeContractInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPITradeContractInfo", c);
}
void generate_class_ITapTrade_TapAPICurrencyInfo(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPICurrencyInfo> c(parent, "TapAPICurrencyInfo");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPICurrencyInfo>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICurrencyInfo, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICurrencyInfo, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICurrencyInfo, "TradeRate", TradeRate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICurrencyInfo, "TradeRate2", TradeRate2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICurrencyInfo, "FutureAlg", FutureAlg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPICurrencyInfo, "OptionAlg", OptionAlg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPICurrencyInfo, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPICurrencyInfo", c);
}
void generate_class_ITapTrade_TapAPITradeMessageReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeMessageReq> c(parent, "TapAPITradeMessageReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeMessageReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessageReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessageReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessageReq, "BenginSendDateTime", BenginSendDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessageReq, "EndSendDateTime", EndSendDateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPITradeMessageReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPITradeMessageReq", c);
}
void generate_class_ITapTrade_TapAPITradeMessage(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPITradeMessage> c(parent, "TapAPITradeMessage");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPITradeMessage>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "SerialID", SerialID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "TMsgValidDateTime", TMsgValidDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "TMsgTitle", TMsgTitle);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "TMsgContent", TMsgContent);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "TMsgType", TMsgType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "TMsgLevel", TMsgLevel);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "IsSendBySMS", IsSendBySMS);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "IsSendByEMail", IsSendByEMail);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "Sender", Sender);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPITradeMessage, "SendDateTime", SendDateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPITradeMessage, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPITradeMessage", c);
}
void generate_class_ITapTrade_TapAPIBillQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIBillQryReq> c(parent, "TapAPIBillQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIBillQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIBillQryReq, "UserNo", UserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIBillQryReq, "BillType", BillType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIBillQryReq, "BillDate", BillDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIBillQryReq, "BillFileType", BillFileType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIBillQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIBillQryReq", c);
}
void generate_class_ITapTrade_TapAPIBillQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIBillQryRsp> c(parent, "TapAPIBillQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIBillQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIBillQryRsp, "Reqdata", Reqdata);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIBillQryRsp, "BillLen", BillLen);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIBillQryRsp, "BillText", BillText);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIBillQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIBillQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisOrderQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisOrderQryReq> c(parent, "TapAPIHisOrderQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryReq, "EndDate", EndDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisOrderQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisOrderQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisOrderQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisOrderQryRsp> c(parent, "TapAPIHisOrderQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderCanceledQty", OrderCanceledQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderStreamID", OrderStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "UpperChannelNo", UpperChannelNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderLocalNo", OrderLocalNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "UpperStreamID", UpperStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderParentSystemNo", OrderParentSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderInsertUserNo", OrderInsertUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderInsertTime", OrderInsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderCommandUserNo", OrderCommandUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderUpdateUserNo", OrderUpdateUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderUpdateTime", OrderUpdateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderState", OrderState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchPrice", OrderMatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchPrice2", OrderMatchPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchQty", OrderMatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "OrderMatchQty2", OrderMatchQty2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "ErrorText", ErrorText);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "IsBackInput", IsBackInput);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "IsDeleted", IsDeleted);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "IsAddOne", IsAddOne);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "MinClipSize", MinClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "MaxClipSize", MaxClipSize);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "LicenseNo", LicenseNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "TacticsType", TacticsType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "TriggerCondition", TriggerCondition);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, "TriggerPriceType", TriggerPriceType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisOrderQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisOrderQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisMatchQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisMatchQryReq> c(parent, "TapAPIHisMatchQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisMatchQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryReq, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryReq, "CountType", CountType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisMatchQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisMatchQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisMatchQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisMatchQryRsp> c(parent, "TapAPIHisMatchQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisMatchQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "SettleDate", SettleDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "TradeDate", TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchPrice", MatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchQty", MatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchNo", MatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchStreamID", MatchStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchCmbNo", MatchCmbNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "ExchangeMatchNo", ExchangeMatchNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchUpperStreamID", MatchUpperStreamID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityCurrencyGroup", CommodityCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "PremiumIncome", PremiumIncome);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "PremiumPay", PremiumPay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFee", AccountFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFeeCurrencyGroup", AccountFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "AccountFeeCurrency", AccountFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "IsManualFee", IsManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "AccountOtherFee", AccountOtherFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFee", UpperFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFeeCurrencyGroup", UpperFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "UpperFeeCurrency", UpperFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "IsUpperManualFee", IsUpperManualFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "UpperOtherFee", UpperOtherFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "MatchDateTime", MatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "UpperMatchDateTime", UpperMatchDateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "CloseProfit", CloseProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "ClosePrice", ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "CloseQty", CloseQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "SettleGroupNo", SettleGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "OperatorNo", OperatorNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, "OperateTime", OperateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisMatchQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisMatchQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisOrderProcessQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisOrderProcessQryReq> c(parent, "TapAPIHisOrderProcessQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisOrderProcessQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderProcessQryReq, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisOrderProcessQryReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisOrderProcessQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisOrderProcessQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisPositionQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisPositionQryReq> c(parent, "TapAPIHisPositionQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisPositionQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryReq, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryReq, "SettleFlag", SettleFlag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisPositionQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisPositionQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisPositionQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisPositionQryRsp> c(parent, "TapAPIHisPositionQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisPositionQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "SettleDate", SettleDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "OpenDate", OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "MatchSide", MatchSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "PositionPrice", PositionPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "PositionQty", PositionQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "OrderNo", OrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "PositionNo", PositionNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "CurrencyGroup", CurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "Currency", Currency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "PreSettlePrice", PreSettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "SettlePrice", SettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "PositionDProfit", PositionDProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "LMEPositionProfit", LMEPositionProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "OptionMarketValue", OptionMarketValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "AccountInitialMargin", AccountInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "AccountMaintenanceMargin", AccountMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "UpperInitialMargin", UpperInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "UpperMaintenanceMargin", UpperMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, "SettleGroupNo", SettleGroupNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisPositionQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisPositionQryRsp", c);
}
void generate_class_ITapTrade_TapAPIHisDeliveryQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisDeliveryQryReq> c(parent, "TapAPIHisDeliveryQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisDeliveryQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryReq, "EndDate", EndDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryReq, "CountType", CountType);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisDeliveryQryReq", c);
}
void generate_class_ITapTrade_TapAPIHisDeliveryQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIHisDeliveryQryRsp> c(parent, "TapAPIHisDeliveryQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIHisDeliveryQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryDate", DeliveryDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenDate", OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenSide", OpenSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenPrice", OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryPrice", DeliveryPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryQty", DeliveryQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "FrozenQty", FrozenQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "OpenNo", OpenNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityCurrencyGroupy", CommodityCurrencyGroupy);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "CommodityCurrency", CommodityCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "PreSettlePrice", PreSettlePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryProfit", DeliveryProfit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFrozenInitialMargin", AccountFrozenInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFrozenMaintenanceMargin", AccountFrozenMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFrozenInitialMargin", UpperFrozenInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFrozenMaintenanceMargin", UpperFrozenMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFeeCurrencyGroup", AccountFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountFeeCurrency", AccountFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "AccountDeliveryFee", AccountDeliveryFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFeeCurrencyGroup", UpperFeeCurrencyGroup);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperFeeCurrency", UpperFeeCurrency);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "UpperDeliveryFee", UpperDeliveryFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "DeliveryMode", DeliveryMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "OperatorNo", OperatorNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, "SettleGourpNo", SettleGourpNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIHisDeliveryQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIHisDeliveryQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountCashAdjustQryReq> c(parent, "TapAPIAccountCashAdjustQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountCashAdjustQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryReq, "SerialID", SerialID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryReq, "AccountAttributeNo", AccountAttributeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryReq, "BeginDate", BeginDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryReq, "EndDate", EndDate);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccountCashAdjustQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountCashAdjustQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountCashAdjustQryRsp> c(parent, "TapAPIAccountCashAdjustQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountCashAdjustQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "Date", Date);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustType", CashAdjustType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustValue", CashAdjustValue);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CashAdjustRemark", CashAdjustRemark);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "OperatorNo", OperatorNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountBank", AccountBank);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "BankAccount", BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "AccountLWFlag", AccountLWFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CompanyBank", CompanyBank);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "InternalBankAccount", InternalBankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, "CompanyLWFlag", CompanyLWFlag);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccountCashAdjustQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccountCashAdjustQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountFeeRentQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountFeeRentQryReq> c(parent, "TapAPIAccountFeeRentQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountFeeRentQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryReq, "AccountNo", AccountNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccountFeeRentQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountFeeRentQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountFeeRentQryRsp> c(parent, "TapAPIAccountFeeRentQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountFeeRentQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "MatchSource", MatchSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CalculateMode", CalculateMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "OpenCloseFee", OpenCloseFee);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, "CloseTodayFee", CloseTodayFee);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccountFeeRentQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccountFeeRentQryRsp", c);
}
void generate_class_ITapTrade_TapAPIAccountMarginRentQryReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountMarginRentQryReq> c(parent, "TapAPIAccountMarginRentQryReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountMarginRentQryReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryReq, "CommodityNo", CommodityNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccountMarginRentQryReq", c);
}
void generate_class_ITapTrade_TapAPIAccountMarginRentQryRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIAccountMarginRentQryRsp> c(parent, "TapAPIAccountMarginRentQryRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIAccountMarginRentQryRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CalculateMode", CalculateMode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CurrencyGroupNo", CurrencyGroupNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "CurrencyNo", CurrencyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "InitialMargin", InitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "MaintenanceMargin", MaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "SellInitialMargin", SellInitialMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "SellMaintenanceMargin", SellMaintenanceMargin);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, "LockMargin", LockMargin);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIAccountMarginRentQryRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIAccountMarginRentQryRsp", c);
}
void generate_class_ITapTrade_TapAPIOrderQuoteMarketNotice(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderQuoteMarketNotice> c(parent, "TapAPIOrderQuoteMarketNotice");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderQuoteMarketNotice>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, "OrderQty", OrderQty);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderQuoteMarketNotice, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderQuoteMarketNotice", c);
}
void generate_class_ITapTrade_TapAPIOrderMarketInsertReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderMarketInsertReq> c(parent, "TapAPIOrderMarketInsertReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketInsertReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "BuyPositionEffect", BuyPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "SellPositionEffect", SellPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderBuyPrice", OrderBuyPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSellPrice", OrderSellPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderBuyQty", OrderBuyQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "OrderSellQty", OrderSellQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "ClientBuyOrderNo", ClientBuyOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "ClientSellOrderNo", ClientSellOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, "Remark", Remark);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderMarketInsertReq", c);
}
void generate_class_ITapTrade_TapAPIOrderMarketInsertRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderMarketInsertRsp> c(parent, "TapAPIOrderMarketInsertRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketInsertRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "BuyPositionEffect", BuyPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "SellPositionEffect", SellPositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyPrice", OrderBuyPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellPrice", OrderSellPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyQty", OrderBuyQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellQty", OrderSellQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderBuyNo", OrderBuyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderSellNo", OrderSellNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "AddOneIsValid", AddOneIsValid);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderMarketUserNo", OrderMarketUserNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "OrderMarketTime", OrderMarketTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefInt", RefInt);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefDouble", RefDouble);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "RefString", RefString);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientBuyOrderNo", ClientBuyOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientSellOrderNo", ClientSellOrderNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ErrorCode", ErrorCode);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ErrorText", ErrorText);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientLocalIP", ClientLocalIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientMac", ClientMac);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "ClientIP", ClientIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, "Remark", Remark);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderMarketInsertRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderMarketInsertRsp", c);
}
void generate_class_ITapTrade_TapAPIOrderMarketDeleteReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderMarketDeleteReq> c(parent, "TapAPIOrderMarketDeleteReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderMarketDeleteReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketDeleteReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketDeleteReq, "OrderBuyNo", OrderBuyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderMarketDeleteReq, "OrderSellNo", OrderSellNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderMarketDeleteReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderMarketDeleteReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalRemoveReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalRemoveReq> c(parent, "TapAPIOrderLocalRemoveReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalRemoveReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveReq, "ServerFlag", ServerFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveReq, "OrderNo", OrderNo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderLocalRemoveReq", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalRemoveRsp(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalRemoveRsp> c(parent, "TapAPIOrderLocalRemoveRsp");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalRemoveRsp>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveRsp, "req", req);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientLocalIP", ClientLocalIP);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientMac", ClientMac);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveRsp, "ClientIP", ClientIP);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderLocalRemoveRsp, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderLocalRemoveRsp", c);
}
void generate_class_ITapTrade_TapAPIOrderLocalInputReq(pybind11::object & parent)
{
    pybind11::class_<ITapTrade::TapAPIOrderLocalInputReq> c(parent, "TapAPIOrderLocalInputReq");
    if constexpr (std::is_default_constructible_v<ITapTrade::TapAPIOrderLocalInputReq>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "AccountNo", AccountNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "ExchangeNo", ExchangeNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "CommodityType", CommodityType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "CommodityNo", CommodityNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "ContractNo", ContractNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "StrikePrice", StrikePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "CallOrPutFlag", CallOrPutFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "ContractNo2", ContractNo2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "StrikePrice2", StrikePrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "CallOrPutFlag2", CallOrPutFlag2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSource", OrderSource);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "TimeInForce", TimeInForce);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "ExpireTime", ExpireTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "IsRiskOrder", IsRiskOrder);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSide", OrderSide);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "PositionEffect", PositionEffect);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "PositionEffect2", PositionEffect2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "InquiryNo", InquiryNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "HedgeFlag", HedgeFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderPrice", OrderPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderPrice2", OrderPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "StopPrice", StopPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderQty", OrderQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMinQty", OrderMinQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderSystemNo", OrderSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderExchangeSystemNo", OrderExchangeSystemNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "UpperNo", UpperNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchPrice", OrderMatchPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchPrice2", OrderMatchPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchQty", OrderMatchQty);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderMatchQty2", OrderMatchQty2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "OrderState", OrderState);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, "IsAddOne", IsAddOne);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnitap, ITapTrade::TapAPIOrderLocalInputReq, c);
    module_vnitap::objects.emplace("ITapTrade::TapAPIOrderLocalInputReq", c);
}
