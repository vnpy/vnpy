#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "TORATstpMdApi.h"
#include "TORATstpTraderApi.h"
#include "TORATstpUserApiDataType.h"
#include "TORATstpUserApiStruct.h"


void generate_class_CTORATstpInputCondOrderActionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputCondOrderActionField> c(parent, "CTORATstpInputCondOrderActionField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputCondOrderActionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "CondOrderActionRef", CondOrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "CondOrderRef", CondOrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "CondOrderID", CondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "ActionFlag", ActionFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "CancelCondOrderID", CancelCondOrderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "BInfo", BInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "SInfo", SInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "IInfo", IInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCondOrderActionField, "HDSerial", HDSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputCondOrderActionField, c);
    module_vntora::objects.emplace("CTORATstpInputCondOrderActionField", c);
}
void generate_class_CTORATstpReqInquiryJZFundField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpReqInquiryJZFundField> c(parent, "CTORATstpReqInquiryJZFundField");
    if constexpr (std::is_default_constructible_v<CTORATstpReqInquiryJZFundField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryJZFundField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryJZFundField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryJZFundField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpReqInquiryJZFundField, c);
    module_vntora::objects.emplace("CTORATstpReqInquiryJZFundField", c);
}
void generate_class_CTORATstpRspInquiryJZFundField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpRspInquiryJZFundField> c(parent, "CTORATstpRspInquiryJZFundField");
    if constexpr (std::is_default_constructible_v<CTORATstpRspInquiryJZFundField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryJZFundField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryJZFundField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryJZFundField, "UsefulMoney", UsefulMoney);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryJZFundField, "FetchLimit", FetchLimit);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryJZFundField, "DepartmentID", DepartmentID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpRspInquiryJZFundField, c);
    module_vntora::objects.emplace("CTORATstpRspInquiryJZFundField", c);
}
void generate_class_CTORATstpInputTransferFundField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputTransferFundField> c(parent, "CTORATstpInputTransferFundField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputTransferFundField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "Amount", Amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "BankID", BankID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "AccountPassword", AccountPassword);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferFundField, "BankPassword", BankPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputTransferFundField, c);
    module_vntora::objects.emplace("CTORATstpInputTransferFundField", c);
}
void generate_class_CTORATstpInputTransferPositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputTransferPositionField> c(parent, "CTORATstpInputTransferPositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputTransferPositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "TransferPositionType", TransferPositionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferPositionField, "MarketID", MarketID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputTransferPositionField, c);
    module_vntora::objects.emplace("CTORATstpInputTransferPositionField", c);
}
void generate_class_CTORATstpTransferFundField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpTransferFundField> c(parent, "CTORATstpTransferFundField");
    if constexpr (std::is_default_constructible_v<CTORATstpTransferFundField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "FundSerial", FundSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "Amount", Amount);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "TransferStatus", TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "OperatorID", OperatorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "OperateDate", OperateDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "OperateTime", OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "BankAccountID", BankAccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferFundField, "BankID", BankID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpTransferFundField, c);
    module_vntora::objects.emplace("CTORATstpTransferFundField", c);
}
void generate_class_CTORATstpTransferPositionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpTransferPositionField> c(parent, "CTORATstpTransferPositionField");
    if constexpr (std::is_default_constructible_v<CTORATstpTransferPositionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "PositionSerial", PositionSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "FrontID", FrontID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "SessionID", SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "TransferDirection", TransferDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "TransferPositionType", TransferPositionType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "HistoryVolume", HistoryVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "TodayBSVolume", TodayBSVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "TodayPRVolume", TodayPRVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "TransferStatus", TransferStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "OperatorID", OperatorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "OperateDate", OperateDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTransferPositionField, "OperateTime", OperateTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpTransferPositionField, c);
    module_vntora::objects.emplace("CTORATstpTransferPositionField", c);
}
void generate_class_CTORATstpSpecificSecurityField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpSpecificSecurityField> c(parent, "CTORATstpSpecificSecurityField");
    if constexpr (std::is_default_constructible_v<CTORATstpSpecificSecurityField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecificSecurityField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpSpecificSecurityField, "SecurityID", SecurityID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpSpecificSecurityField, c);
    module_vntora::objects.emplace("CTORATstpSpecificSecurityField", c);
}
void generate_class_CTORATstpInputTransferCollateralField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputTransferCollateralField> c(parent, "CTORATstpInputTransferCollateralField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputTransferCollateralField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "ApplySerial", ApplySerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "CollateralDirection", CollateralDirection);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputTransferCollateralField, "Operway", Operway);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputTransferCollateralField, c);
    module_vntora::objects.emplace("CTORATstpInputTransferCollateralField", c);
}
void generate_class_CTORATstpReqInquiryBankAccountFundField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpReqInquiryBankAccountFundField> c(parent, "CTORATstpReqInquiryBankAccountFundField");
    if constexpr (std::is_default_constructible_v<CTORATstpReqInquiryBankAccountFundField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryBankAccountFundField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryBankAccountFundField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryBankAccountFundField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryBankAccountFundField, "BankID", BankID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInquiryBankAccountFundField, "BankPassword", BankPassword);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpReqInquiryBankAccountFundField, c);
    module_vntora::objects.emplace("CTORATstpReqInquiryBankAccountFundField", c);
}
void generate_class_CTORATstpRspInquiryBankAccountFundField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpRspInquiryBankAccountFundField> c(parent, "CTORATstpRspInquiryBankAccountFundField");
    if constexpr (std::is_default_constructible_v<CTORATstpRspInquiryBankAccountFundField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryBankAccountFundField, "DepartmentID", DepartmentID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryBankAccountFundField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryBankAccountFundField, "CurrencyID", CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryBankAccountFundField, "BankID", BankID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryBankAccountFundField, "BankAccountID", BankAccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpRspInquiryBankAccountFundField, "Balance", Balance);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpRspInquiryBankAccountFundField, c);
    module_vntora::objects.emplace("CTORATstpRspInquiryBankAccountFundField", c);
}
void generate_class_CTORATstpLev2MarketDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpLev2MarketDataField> c(parent, "CTORATstpLev2MarketDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpLev2MarketDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "DataTimeStamp", DataTimeStamp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "PreClosePrice", PreClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "OpenPrice", OpenPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "NumTrades", NumTrades);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "TotalVolumeTrade", TotalVolumeTrade);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "TotalValueTrade", TotalValueTrade);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "TotalBidVolume", TotalBidVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AvgBidPrice", AvgBidPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "TotalAskVolume", TotalAskVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AvgAskPrice", AvgAskPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "HighestPrice", HighestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "LowestPrice", LowestPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "LastPrice", LastPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice1", BidPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume1", BidVolume1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice1", AskPrice1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume1", AskVolume1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice2", AskPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume2", AskVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice3", AskPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume3", AskVolume3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice2", BidPrice2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume2", BidVolume2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice3", BidPrice3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume3", BidVolume3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice4", AskPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume4", AskVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice5", AskPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume5", AskVolume5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice4", BidPrice4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume4", BidVolume4);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice5", BidPrice5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume5", BidVolume5);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice6", AskPrice6);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume6", AskVolume6);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice7", AskPrice7);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume7", AskVolume7);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice6", BidPrice6);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume6", BidVolume6);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice7", BidPrice7);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume7", BidVolume7);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice8", AskPrice8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume8", AskVolume8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice9", AskPrice9);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume9", AskVolume9);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice8", BidPrice8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume8", BidVolume8);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice9", BidPrice9);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume9", BidVolume9);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidPrice10", BidPrice10);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "BidVolume10", BidVolume10);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskPrice10", AskPrice10);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "AskVolume10", AskVolume10);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "Info1", Info1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "Info2", Info2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "Info3", Info3);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "UpperLimitPrice", UpperLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "LowerLimitPrice", LowerLimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "ClosePrice", ClosePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2MarketDataField, "MDSecurityStat", MDSecurityStat);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpLev2MarketDataField, c);
    module_vntora::objects.emplace("CTORATstpLev2MarketDataField", c);
}
void generate_class_CTORATstpLev2IndexField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpLev2IndexField> c(parent, "CTORATstpLev2IndexField");
    if constexpr (std::is_default_constructible_v<CTORATstpLev2IndexField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "DataTimeStamp", DataTimeStamp);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "PreCloseIndex", PreCloseIndex);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "OpenIndex", OpenIndex);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "HighIndex", HighIndex);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "LowIndex", LowIndex);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "LastIndex", LastIndex);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "Turnover", Turnover);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "TotalVolumeTraded", TotalVolumeTraded);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "Info1", Info1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "Info2", Info2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2IndexField, "Info3", Info3);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpLev2IndexField, c);
    module_vntora::objects.emplace("CTORATstpLev2IndexField", c);
}
void generate_class_CTORATstpLev2TransactionField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpLev2TransactionField> c(parent, "CTORATstpLev2TransactionField");
    if constexpr (std::is_default_constructible_v<CTORATstpLev2TransactionField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "TradeTime", TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "TradePrice", TradePrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "TradeVolume", TradeVolume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "ExecType", ExecType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "MainSeq", MainSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "SubSeq", SubSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "BuyNo", BuyNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "SellNo", SellNo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "Info1", Info1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "Info2", Info2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2TransactionField, "Info3", Info3);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpLev2TransactionField, c);
    module_vntora::objects.emplace("CTORATstpLev2TransactionField", c);
}
void generate_class_CTORATstpLev2OrderDetailField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpLev2OrderDetailField> c(parent, "CTORATstpLev2OrderDetailField");
    if constexpr (std::is_default_constructible_v<CTORATstpLev2OrderDetailField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "OrderTime", OrderTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "Price", Price);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "Volume", Volume);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "Side", Side);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "OrderType", OrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "MainSeq", MainSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "SubSeq", SubSeq);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "Info1", Info1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "Info2", Info2);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLev2OrderDetailField, "Info3", Info3);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpLev2OrderDetailField, c);
    module_vntora::objects.emplace("CTORATstpLev2OrderDetailField", c);
}
void generate_class_CTORATstpUploadTradeDataField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpUploadTradeDataField> c(parent, "CTORATstpUploadTradeDataField");
    if constexpr (std::is_default_constructible_v<CTORATstpUploadTradeDataField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUploadTradeDataField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUploadTradeDataField, "TradingDay", TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpUploadTradeDataField, "bForce", bForce);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpUploadTradeDataField, c);
    module_vntora::objects.emplace("CTORATstpUploadTradeDataField", c);
}
void generate_class_CTORATstpInputDesignationRegistrationField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputDesignationRegistrationField> c(parent, "CTORATstpInputDesignationRegistrationField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputDesignationRegistrationField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "DesignationType", DesignationType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputDesignationRegistrationField, "HDSerial", HDSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputDesignationRegistrationField, c);
    module_vntora::objects.emplace("CTORATstpInputDesignationRegistrationField", c);
}
void generate_class_CTORATstpInputCustodyTransferField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInputCustodyTransferField> c(parent, "CTORATstpInputCustodyTransferField");
    if constexpr (std::is_default_constructible_v<CTORATstpInputCustodyTransferField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "UserID", UserID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "CustodyTransferType", CustodyTransferType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "TransfereePbuID", TransfereePbuID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "OrignalOrderLocalID", OrignalOrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "OrderLocalID", OrderLocalID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "IPAddress", IPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "MacAddress", MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "TerminalInfo", TerminalInfo);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInputCustodyTransferField, "HDSerial", HDSerial);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInputCustodyTransferField, c);
    module_vntora::objects.emplace("CTORATstpInputCustodyTransferField", c);
}
void generate_class_CTORATstpInquiryTradeConcentrationField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInquiryTradeConcentrationField> c(parent, "CTORATstpInquiryTradeConcentrationField");
    if constexpr (std::is_default_constructible_v<CTORATstpInquiryTradeConcentrationField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "MarketID", MarketID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "AccountID", AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "ConcentrationRatio1", ConcentrationRatio1);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryTradeConcentrationField, "ConcentrationRatio2", ConcentrationRatio2);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInquiryTradeConcentrationField, c);
    module_vntora::objects.emplace("CTORATstpInquiryTradeConcentrationField", c);
}
void generate_class_CTORATstpInquiryFileOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpInquiryFileOrderField> c(parent, "CTORATstpInquiryFileOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpInquiryFileOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryFileOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryFileOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryFileOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryFileOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryFileOrderField, "OrderSerialBeg", OrderSerialBeg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryFileOrderField, "OrderSerialEnd", OrderSerialEnd);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpInquiryFileOrderField, "CommitStatus", CommitStatus);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpInquiryFileOrderField, c);
    module_vntora::objects.emplace("CTORATstpInquiryFileOrderField", c);
}
void generate_class_CTORATstpFileOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpFileOrderField> c(parent, "CTORATstpFileOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpFileOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "FileOrderType", FileOrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "OrderActionRef", OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "OrderSerial", OrderSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "CommitStatus", CommitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "StatusMsg", StatusMsg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderField, "TimeStamp", TimeStamp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpFileOrderField, c);
    module_vntora::objects.emplace("CTORATstpFileOrderField", c);
}
void generate_class_CTORATstpQryRspInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpQryRspInfoField> c(parent, "CTORATstpQryRspInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpQryRspInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryRspInfoField, "EndFlag", EndFlag);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryRspInfoField, "ErrorID", ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpQryRspInfoField, "ErrorMsg", ErrorMsg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpQryRspInfoField, c);
    module_vntora::objects.emplace("CTORATstpQryRspInfoField", c);
}
void generate_class_CTORATstpReviewFileOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpReviewFileOrderField> c(parent, "CTORATstpReviewFileOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpReviewFileOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReviewFileOrderField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReviewFileOrderField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReviewFileOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReviewFileOrderField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReviewFileOrderField, "OrderSerialBeg", OrderSerialBeg);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReviewFileOrderField, "OrderSerialEnd", OrderSerialEnd);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpReviewFileOrderField, c);
    module_vntora::objects.emplace("CTORATstpReviewFileOrderField", c);
}
void generate_class_CTORATstpCommitInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpCommitInfoField> c(parent, "CTORATstpCommitInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpCommitInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCommitInfoField, "OrderSerial", OrderSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCommitInfoField, "CommitStatus", CommitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpCommitInfoField, "StatusMsg", StatusMsg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpCommitInfoField, c);
    module_vntora::objects.emplace("CTORATstpCommitInfoField", c);
}
void generate_class_CTORATstpReqInsTradingNoticeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpReqInsTradingNoticeField> c(parent, "CTORATstpReqInsTradingNoticeField");
    if constexpr (std::is_default_constructible_v<CTORATstpReqInsTradingNoticeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInsTradingNoticeField, "NoticeSerial", NoticeSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInsTradingNoticeField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInsTradingNoticeField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInsTradingNoticeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInsTradingNoticeField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInsTradingNoticeField, "Content", Content);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpReqInsTradingNoticeField, "OperatorID", OperatorID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpReqInsTradingNoticeField, c);
    module_vntora::objects.emplace("CTORATstpReqInsTradingNoticeField", c);
}
void generate_class_CTORATstpTradingNoticeField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpTradingNoticeField> c(parent, "CTORATstpTradingNoticeField");
    if constexpr (std::is_default_constructible_v<CTORATstpTradingNoticeField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingNoticeField, "NoticeSerial", NoticeSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingNoticeField, "InsertDate", InsertDate);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingNoticeField, "InsertTime", InsertTime);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingNoticeField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingNoticeField, "BusinessUnitID", BusinessUnitID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingNoticeField, "Content", Content);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpTradingNoticeField, "OperatorID", OperatorID);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpTradingNoticeField, c);
    module_vntora::objects.emplace("CTORATstpTradingNoticeField", c);
}
void generate_class_CTORATstpLoadFileOrderField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpLoadFileOrderField> c(parent, "CTORATstpLoadFileOrderField");
    if constexpr (std::is_default_constructible_v<CTORATstpLoadFileOrderField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLoadFileOrderField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpLoadFileOrderField, "bReview", bReview);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpLoadFileOrderField, c);
    module_vntora::objects.emplace("CTORATstpLoadFileOrderField", c);
}
void generate_class_CTORATstpFileOrderInfoField(pybind11::object & parent)
{
    pybind11::class_<CTORATstpFileOrderInfoField> c(parent, "CTORATstpFileOrderInfoField");
    if constexpr (std::is_default_constructible_v<CTORATstpFileOrderInfoField>)
        c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "RequestID", RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "ExchangeID", ExchangeID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "ShareholderID", ShareholderID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "InvestorID", InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "SecurityID", SecurityID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "OrderRef", OrderRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "FileOrderType", FileOrderType);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "Direction", Direction);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "LimitPrice", LimitPrice);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "VolumeTotalOriginal", VolumeTotalOriginal);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "Operway", Operway);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "OrderActionRef", OrderActionRef);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "OrderSysID", OrderSysID);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "CondCheck", CondCheck);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "OrderSerial", OrderSerial);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "CommitStatus", CommitStatus);
    c.AUTOCXXPY_DEF_PROPERTY(tag_vntora, CTORATstpFileOrderInfoField, "StatusMsg", StatusMsg);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpFileOrderInfoField, c);
    module_vntora::objects.emplace("CTORATstpFileOrderInfoField", c);
}
