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


void generate_class_CThostFtdcVerifyFuturePasswordField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcVerifyFuturePasswordField> c(m, "CThostFtdcVerifyFuturePasswordField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordField, CurrencyID);
}
void generate_class_CThostFtdcVerifyCustInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcVerifyCustInfoField> c(m, "CThostFtdcVerifyCustInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyCustInfoField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyCustInfoField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyCustInfoField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyCustInfoField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyCustInfoField, LongCustomerName);
}
void generate_class_CThostFtdcVerifyFuturePasswordAndCustInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcVerifyFuturePasswordAndCustInfoField> c(m, "CThostFtdcVerifyFuturePasswordAndCustInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcVerifyFuturePasswordAndCustInfoField, LongCustomerName);
}
void generate_class_CThostFtdcDepositResultInformField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcDepositResultInformField> c(m, "CThostFtdcDepositResultInformField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepositResultInformField, DepositSeqNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepositResultInformField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepositResultInformField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepositResultInformField, Deposit);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepositResultInformField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepositResultInformField, ReturnCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepositResultInformField, DescrInfoForReturnCode);
}
void generate_class_CThostFtdcReqSyncKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqSyncKeyField> c(m, "CThostFtdcReqSyncKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, Message);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqSyncKeyField, TID);
}
void generate_class_CThostFtdcRspSyncKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspSyncKeyField> c(m, "CThostFtdcRspSyncKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, Message);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspSyncKeyField, ErrorMsg);
}
void generate_class_CThostFtdcNotifyQueryAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcNotifyQueryAccountField> c(m, "CThostFtdcNotifyQueryAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankUseAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, BankFetchAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyQueryAccountField, LongCustomerName);
}
void generate_class_CThostFtdcTransferSerialField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTransferSerialField> c(m, "CThostFtdcTransferSerialField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, FutureAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, InvestorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, FutureSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, TradeAmount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, CustFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BrokerFee);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, AvailabilityFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, OperatorCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, BankNewAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTransferSerialField, ErrorMsg);
}
void generate_class_CThostFtdcQryTransferSerialField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryTransferSerialField> c(m, "CThostFtdcQryTransferSerialField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTransferSerialField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTransferSerialField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTransferSerialField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryTransferSerialField, CurrencyID);
}
void generate_class_CThostFtdcNotifyFutureSignInField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcNotifyFutureSignInField> c(m, "CThostFtdcNotifyFutureSignInField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, PinKey);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignInField, MacKey);
}
void generate_class_CThostFtdcNotifyFutureSignOutField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcNotifyFutureSignOutField> c(m, "CThostFtdcNotifyFutureSignOutField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifyFutureSignOutField, ErrorMsg);
}
void generate_class_CThostFtdcNotifySyncKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcNotifySyncKeyField> c(m, "CThostFtdcNotifySyncKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, Message);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, RequestID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcNotifySyncKeyField, ErrorMsg);
}
void generate_class_CThostFtdcQryAccountregisterField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryAccountregisterField> c(m, "CThostFtdcQryAccountregisterField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryAccountregisterField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryAccountregisterField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryAccountregisterField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryAccountregisterField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryAccountregisterField, CurrencyID);
}
void generate_class_CThostFtdcAccountregisterField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcAccountregisterField> c(m, "CThostFtdcAccountregisterField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, TradeDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, OpenOrDestroy);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, RegDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, OutDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountregisterField, LongCustomerName);
}
void generate_class_CThostFtdcOpenAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcOpenAccountField> c(m, "CThostFtdcOpenAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, CashExchangeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcOpenAccountField, LongCustomerName);
}
void generate_class_CThostFtdcCancelAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCancelAccountField> c(m, "CThostFtdcCancelAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, CashExchangeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, DeviceID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankSecuAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankSecuAcc);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, OperNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCancelAccountField, LongCustomerName);
}
void generate_class_CThostFtdcChangeAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcChangeAccountField> c(m, "CThostFtdcChangeAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, NewBankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, NewBankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, BankPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, SecuPwdFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, ErrorMsg);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcChangeAccountField, LongCustomerName);
}
void generate_class_CThostFtdcSecAgentACIDMapField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcSecAgentACIDMapField> c(m, "CThostFtdcSecAgentACIDMapField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentACIDMapField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentACIDMapField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentACIDMapField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentACIDMapField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcSecAgentACIDMapField, BrokerSecAgentID);
}
void generate_class_CThostFtdcQrySecAgentACIDMapField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySecAgentACIDMapField> c(m, "CThostFtdcQrySecAgentACIDMapField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentACIDMapField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentACIDMapField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentACIDMapField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentACIDMapField, CurrencyID);
}
void generate_class_CThostFtdcUserRightsAssignField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcUserRightsAssignField> c(m, "CThostFtdcUserRightsAssignField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserRightsAssignField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserRightsAssignField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserRightsAssignField, DRIdentityID);
}
void generate_class_CThostFtdcBrokerUserRightAssignField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcBrokerUserRightAssignField> c(m, "CThostFtdcBrokerUserRightAssignField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserRightAssignField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserRightAssignField, DRIdentityID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcBrokerUserRightAssignField, Tradeable);
}
void generate_class_CThostFtdcDRTransferField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcDRTransferField> c(m, "CThostFtdcDRTransferField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDRTransferField, OrigDRIdentityID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDRTransferField, DestDRIdentityID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDRTransferField, OrigBrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDRTransferField, DestBrokerID);
}
void generate_class_CThostFtdcFensUserInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcFensUserInfoField> c(m, "CThostFtdcFensUserInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFensUserInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFensUserInfoField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcFensUserInfoField, LoginMode);
}
void generate_class_CThostFtdcCurrTransferIdentityField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCurrTransferIdentityField> c(m, "CThostFtdcCurrTransferIdentityField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCurrTransferIdentityField, IdentityID);
}
void generate_class_CThostFtdcLoginForbiddenUserField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcLoginForbiddenUserField> c(m, "CThostFtdcLoginForbiddenUserField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginForbiddenUserField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginForbiddenUserField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcLoginForbiddenUserField, IPAddress);
}
void generate_class_CThostFtdcQryLoginForbiddenUserField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryLoginForbiddenUserField> c(m, "CThostFtdcQryLoginForbiddenUserField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryLoginForbiddenUserField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryLoginForbiddenUserField, UserID);
}
void generate_class_CThostFtdcMulticastGroupInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcMulticastGroupInfoField> c(m, "CThostFtdcMulticastGroupInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMulticastGroupInfoField, GroupIP);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMulticastGroupInfoField, GroupPort);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcMulticastGroupInfoField, SourceIP);
}
void generate_class_CThostFtdcTradingAccountReserveField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcTradingAccountReserveField> c(m, "CThostFtdcTradingAccountReserveField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountReserveField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountReserveField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountReserveField, Reserve);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcTradingAccountReserveField, CurrencyID);
}
void generate_class_CThostFtdcQryLoginForbiddenIPField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryLoginForbiddenIPField> c(m, "CThostFtdcQryLoginForbiddenIPField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryLoginForbiddenIPField, IPAddress);
}
void generate_class_CThostFtdcQryIPListField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryIPListField> c(m, "CThostFtdcQryIPListField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryIPListField, IPAddress);
}
void generate_class_CThostFtdcQryUserRightsAssignField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryUserRightsAssignField> c(m, "CThostFtdcQryUserRightsAssignField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryUserRightsAssignField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryUserRightsAssignField, UserID);
}
void generate_class_CThostFtdcReserveOpenAccountConfirmField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReserveOpenAccountConfirmField> c(m, "CThostFtdcReserveOpenAccountConfirmField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BankReserveOpenSeq);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BookDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, BookPsw);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountConfirmField, ErrorMsg);
}
void generate_class_CThostFtdcReserveOpenAccountField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReserveOpenAccountField> c(m, "CThostFtdcReserveOpenAccountField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, TradeCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BankBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BrokerBranchID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, TradeDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, TradeTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BankSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, PlateSerial);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, LastFragment);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, SessionID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, CustomerName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, IdCardType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, IdentifiedCardNo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, Gender);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, CountryCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, CustType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, Address);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, ZipCode);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, Telephone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, MobilePhone);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, Fax);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, EMail);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, MoneyAccountStatus);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BankPassWord);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, InstallID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, VerifyCertNoFlag);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, CurrencyID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, Digest);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BankAccType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, BrokerIDByBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, TID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, ReserveOpenAccStas);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, ErrorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReserveOpenAccountField, ErrorMsg);
}
void generate_class_CThostFtdcAccountPropertyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcAccountPropertyField> c(m, "CThostFtdcAccountPropertyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, AccountID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, BankID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, BankAccount);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, OpenName);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, OpenBank);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, IsActive);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, AccountSourceType);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, OpenDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, CancelDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, OperatorID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, OperateDate);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, OperateTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcAccountPropertyField, CurrencyID);
}
void generate_class_CThostFtdcQryCurrDRIdentityField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQryCurrDRIdentityField> c(m, "CThostFtdcQryCurrDRIdentityField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQryCurrDRIdentityField, DRIdentityID);
}
void generate_class_CThostFtdcCurrDRIdentityField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcCurrDRIdentityField> c(m, "CThostFtdcCurrDRIdentityField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcCurrDRIdentityField, DRIdentityID);
}
void generate_class_CThostFtdcQrySecAgentCheckModeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySecAgentCheckModeField> c(m, "CThostFtdcQrySecAgentCheckModeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentCheckModeField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentCheckModeField, InvestorID);
}
void generate_class_CThostFtdcQrySecAgentTradeInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQrySecAgentTradeInfoField> c(m, "CThostFtdcQrySecAgentTradeInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentTradeInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQrySecAgentTradeInfoField, BrokerSecAgentID);
}
void generate_class_CThostFtdcUserSystemInfoField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcUserSystemInfoField> c(m, "CThostFtdcUserSystemInfoField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, ClientSystemInfoLen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, ClientSystemInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, ClientPublicIP);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, ClientIPPort);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, ClientLoginTime);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcUserSystemInfoField, ClientAppID);
}
void generate_class_CThostFtdcReqUserAuthMethodField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqUserAuthMethodField> c(m, "CThostFtdcReqUserAuthMethodField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserAuthMethodField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserAuthMethodField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserAuthMethodField, UserID);
}
void generate_class_CThostFtdcRspUserAuthMethodField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspUserAuthMethodField> c(m, "CThostFtdcRspUserAuthMethodField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspUserAuthMethodField, UsableAuthMethod);
}
void generate_class_CThostFtdcReqGenUserCaptchaField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqGenUserCaptchaField> c(m, "CThostFtdcReqGenUserCaptchaField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqGenUserCaptchaField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqGenUserCaptchaField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqGenUserCaptchaField, UserID);
}
void generate_class_CThostFtdcRspGenUserCaptchaField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspGenUserCaptchaField> c(m, "CThostFtdcRspGenUserCaptchaField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspGenUserCaptchaField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspGenUserCaptchaField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspGenUserCaptchaField, CaptchaInfoLen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspGenUserCaptchaField, CaptchaInfo);
}
void generate_class_CThostFtdcReqGenUserTextField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqGenUserTextField> c(m, "CThostFtdcReqGenUserTextField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqGenUserTextField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqGenUserTextField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqGenUserTextField, UserID);
}
void generate_class_CThostFtdcRspGenUserTextField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspGenUserTextField> c(m, "CThostFtdcRspGenUserTextField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspGenUserTextField, UserTextSeq);
}
void generate_class_CThostFtdcReqUserLoginWithCaptchaField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqUserLoginWithCaptchaField> c(m, "CThostFtdcReqUserLoginWithCaptchaField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, InterfaceProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, ProtocolInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, ClientIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, LoginRemark);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, Captcha);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithCaptchaField, ClientIPPort);
}
void generate_class_CThostFtdcReqUserLoginWithTextField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqUserLoginWithTextField> c(m, "CThostFtdcReqUserLoginWithTextField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, InterfaceProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, ProtocolInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, ClientIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, LoginRemark);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, Text);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithTextField, ClientIPPort);
}
void generate_class_CThostFtdcReqUserLoginWithOTPField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqUserLoginWithOTPField> c(m, "CThostFtdcReqUserLoginWithOTPField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, TradingDay);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, Password);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, UserProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, InterfaceProductInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, ProtocolInfo);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, MacAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, ClientIPAddress);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, LoginRemark);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, OTPPassword);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqUserLoginWithOTPField, ClientIPPort);
}
void generate_class_CThostFtdcReqApiHandshakeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqApiHandshakeField> c(m, "CThostFtdcReqApiHandshakeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqApiHandshakeField, CryptoKeyVersion);
}
void generate_class_CThostFtdcRspApiHandshakeField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcRspApiHandshakeField> c(m, "CThostFtdcRspApiHandshakeField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspApiHandshakeField, FrontHandshakeDataLen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspApiHandshakeField, FrontHandshakeData);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcRspApiHandshakeField, IsApiAuthEnabled);
}
void generate_class_CThostFtdcReqVerifyApiKeyField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcReqVerifyApiKeyField> c(m, "CThostFtdcReqVerifyApiKeyField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqVerifyApiKeyField, ApiHandshakeDataLen);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcReqVerifyApiKeyField, ApiHandshakeData);
}
void generate_class_CThostFtdcDepartmentUserField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcDepartmentUserField> c(m, "CThostFtdcDepartmentUserField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepartmentUserField, BrokerID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepartmentUserField, UserID);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepartmentUserField, InvestorRange);
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcDepartmentUserField, InvestorID);
}
void generate_class_CThostFtdcQueryFreqField(pybind11::module &m)
{
    pybind11::class_<CThostFtdcQueryFreqField> c(m, "CThostFtdcQueryFreqField");
    c.def(pybind11::init<>());
    c.AUTOCXXPY_DEF_PROPERTY(CThostFtdcQueryFreqField, QueryFreq);
}
void generate_class_CThostFtdcTraderSpi(pybind11::module &m)
{
    pybind11::class_<
        CThostFtdcTraderSpi,
        std::unique_ptr<CThostFtdcTraderSpi, pybind11::nodelete>,
        PyCThostFtdcTraderSpi
    > c(m, "CThostFtdcTraderSpi");
    c.def(pybind11::init<>());
    c.def("OnFrontConnected",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnFrontConnected
        >::value
    );
    c.def("OnFrontDisconnected",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnFrontDisconnected
        >::value
    );
    c.def("OnHeartBeatWarning",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnHeartBeatWarning
        >::value
    );
    c.def("OnRspAuthenticate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspAuthenticate
        >::value
    );
    c.def("OnRspUserLogin",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspUserLogin
        >::value
    );
    c.def("OnRspUserLogout",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspUserLogout
        >::value
    );
    c.def("OnRspUserPasswordUpdate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspUserPasswordUpdate
        >::value
    );
    c.def("OnRspTradingAccountPasswordUpdate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspTradingAccountPasswordUpdate
        >::value
    );
    c.def("OnRspUserAuthMethod",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspUserAuthMethod
        >::value
    );
    c.def("OnRspGenUserCaptcha",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspGenUserCaptcha
        >::value
    );
    c.def("OnRspGenUserText",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspGenUserText
        >::value
    );
    c.def("OnRspOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspOrderInsert
        >::value
    );
    c.def("OnRspParkedOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspParkedOrderInsert
        >::value
    );
    c.def("OnRspParkedOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspParkedOrderAction
        >::value
    );
    c.def("OnRspOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspOrderAction
        >::value
    );
    c.def("OnRspQueryMaxOrderVolume",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQueryMaxOrderVolume
        >::value
    );
    c.def("OnRspSettlementInfoConfirm",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspSettlementInfoConfirm
        >::value
    );
    c.def("OnRspRemoveParkedOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspRemoveParkedOrder
        >::value
    );
    c.def("OnRspRemoveParkedOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspRemoveParkedOrderAction
        >::value
    );
    c.def("OnRspExecOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspExecOrderInsert
        >::value
    );
    c.def("OnRspExecOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspExecOrderAction
        >::value
    );
    c.def("OnRspForQuoteInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspForQuoteInsert
        >::value
    );
    c.def("OnRspQuoteInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQuoteInsert
        >::value
    );
    c.def("OnRspQuoteAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQuoteAction
        >::value
    );
    c.def("OnRspBatchOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspBatchOrderAction
        >::value
    );
    c.def("OnRspOptionSelfCloseInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspOptionSelfCloseInsert
        >::value
    );
    c.def("OnRspOptionSelfCloseAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspOptionSelfCloseAction
        >::value
    );
    c.def("OnRspCombActionInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspCombActionInsert
        >::value
    );
    c.def("OnRspQryOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryOrder
        >::value
    );
    c.def("OnRspQryTrade",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryTrade
        >::value
    );
    c.def("OnRspQryInvestorPosition",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInvestorPosition
        >::value
    );
    c.def("OnRspQryTradingAccount",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryTradingAccount
        >::value
    );
    c.def("OnRspQryInvestor",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInvestor
        >::value
    );
    c.def("OnRspQryTradingCode",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryTradingCode
        >::value
    );
    c.def("OnRspQryInstrumentMarginRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInstrumentMarginRate
        >::value
    );
    c.def("OnRspQryInstrumentCommissionRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInstrumentCommissionRate
        >::value
    );
    c.def("OnRspQryExchange",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryExchange
        >::value
    );
    c.def("OnRspQryProduct",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryProduct
        >::value
    );
    c.def("OnRspQryInstrument",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInstrument
        >::value
    );
    c.def("OnRspQryDepthMarketData",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryDepthMarketData
        >::value
    );
    c.def("OnRspQrySettlementInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQrySettlementInfo
        >::value
    );
    c.def("OnRspQryTransferBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryTransferBank
        >::value
    );
    c.def("OnRspQryInvestorPositionDetail",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInvestorPositionDetail
        >::value
    );
    c.def("OnRspQryNotice",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryNotice
        >::value
    );
    c.def("OnRspQrySettlementInfoConfirm",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQrySettlementInfoConfirm
        >::value
    );
    c.def("OnRspQryInvestorPositionCombineDetail",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInvestorPositionCombineDetail
        >::value
    );
    c.def("OnRspQryCFMMCTradingAccountKey",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryCFMMCTradingAccountKey
        >::value
    );
    c.def("OnRspQryEWarrantOffset",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryEWarrantOffset
        >::value
    );
    c.def("OnRspQryInvestorProductGroupMargin",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInvestorProductGroupMargin
        >::value
    );
    c.def("OnRspQryExchangeMarginRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryExchangeMarginRate
        >::value
    );
    c.def("OnRspQryExchangeMarginRateAdjust",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryExchangeMarginRateAdjust
        >::value
    );
    c.def("OnRspQryExchangeRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryExchangeRate
        >::value
    );
    c.def("OnRspQrySecAgentACIDMap",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQrySecAgentACIDMap
        >::value
    );
    c.def("OnRspQryProductExchRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryProductExchRate
        >::value
    );
    c.def("OnRspQryProductGroup",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryProductGroup
        >::value
    );
    c.def("OnRspQryMMInstrumentCommissionRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryMMInstrumentCommissionRate
        >::value
    );
    c.def("OnRspQryMMOptionInstrCommRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryMMOptionInstrCommRate
        >::value
    );
    c.def("OnRspQryInstrumentOrderCommRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInstrumentOrderCommRate
        >::value
    );
    c.def("OnRspQrySecAgentTradingAccount",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQrySecAgentTradingAccount
        >::value
    );
    c.def("OnRspQrySecAgentCheckMode",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQrySecAgentCheckMode
        >::value
    );
    c.def("OnRspQrySecAgentTradeInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQrySecAgentTradeInfo
        >::value
    );
    c.def("OnRspQryOptionInstrTradeCost",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryOptionInstrTradeCost
        >::value
    );
    c.def("OnRspQryOptionInstrCommRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryOptionInstrCommRate
        >::value
    );
    c.def("OnRspQryExecOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryExecOrder
        >::value
    );
    c.def("OnRspQryForQuote",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryForQuote
        >::value
    );
    c.def("OnRspQryQuote",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryQuote
        >::value
    );
    c.def("OnRspQryOptionSelfClose",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryOptionSelfClose
        >::value
    );
    c.def("OnRspQryInvestUnit",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryInvestUnit
        >::value
    );
    c.def("OnRspQryCombInstrumentGuard",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryCombInstrumentGuard
        >::value
    );
    c.def("OnRspQryCombAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryCombAction
        >::value
    );
    c.def("OnRspQryTransferSerial",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryTransferSerial
        >::value
    );
    c.def("OnRspQryAccountregister",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryAccountregister
        >::value
    );
    c.def("OnRspError",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspError
        >::value
    );
    c.def("OnRtnOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnOrder
        >::value
    );
    c.def("OnRtnTrade",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnTrade
        >::value
    );
    c.def("OnErrRtnOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnOrderInsert
        >::value
    );
    c.def("OnErrRtnOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnOrderAction
        >::value
    );
    c.def("OnRtnInstrumentStatus",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnInstrumentStatus
        >::value
    );
    c.def("OnRtnBulletin",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnBulletin
        >::value
    );
    c.def("OnRtnTradingNotice",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnTradingNotice
        >::value
    );
    c.def("OnRtnErrorConditionalOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnErrorConditionalOrder
        >::value
    );
    c.def("OnRtnExecOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnExecOrder
        >::value
    );
    c.def("OnErrRtnExecOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnExecOrderInsert
        >::value
    );
    c.def("OnErrRtnExecOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnExecOrderAction
        >::value
    );
    c.def("OnErrRtnForQuoteInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnForQuoteInsert
        >::value
    );
    c.def("OnRtnQuote",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnQuote
        >::value
    );
    c.def("OnErrRtnQuoteInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnQuoteInsert
        >::value
    );
    c.def("OnErrRtnQuoteAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnQuoteAction
        >::value
    );
    c.def("OnRtnForQuoteRsp",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnForQuoteRsp
        >::value
    );
    c.def("OnRtnCFMMCTradingAccountToken",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnCFMMCTradingAccountToken
        >::value
    );
    c.def("OnErrRtnBatchOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnBatchOrderAction
        >::value
    );
    c.def("OnRtnOptionSelfClose",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnOptionSelfClose
        >::value
    );
    c.def("OnErrRtnOptionSelfCloseInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnOptionSelfCloseInsert
        >::value
    );
    c.def("OnErrRtnOptionSelfCloseAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnOptionSelfCloseAction
        >::value
    );
    c.def("OnRtnCombAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnCombAction
        >::value
    );
    c.def("OnErrRtnCombActionInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnCombActionInsert
        >::value
    );
    c.def("OnRspQryContractBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryContractBank
        >::value
    );
    c.def("OnRspQryParkedOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryParkedOrder
        >::value
    );
    c.def("OnRspQryParkedOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryParkedOrderAction
        >::value
    );
    c.def("OnRspQryTradingNotice",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryTradingNotice
        >::value
    );
    c.def("OnRspQryBrokerTradingParams",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryBrokerTradingParams
        >::value
    );
    c.def("OnRspQryBrokerTradingAlgos",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQryBrokerTradingAlgos
        >::value
    );
    c.def("OnRspQueryCFMMCTradingAccountToken",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQueryCFMMCTradingAccountToken
        >::value
    );
    c.def("OnRtnFromBankToFutureByBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnFromBankToFutureByBank
        >::value
    );
    c.def("OnRtnFromFutureToBankByBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnFromFutureToBankByBank
        >::value
    );
    c.def("OnRtnRepealFromBankToFutureByBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnRepealFromBankToFutureByBank
        >::value
    );
    c.def("OnRtnRepealFromFutureToBankByBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnRepealFromFutureToBankByBank
        >::value
    );
    c.def("OnRtnFromBankToFutureByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnFromBankToFutureByFuture
        >::value
    );
    c.def("OnRtnFromFutureToBankByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnFromFutureToBankByFuture
        >::value
    );
    c.def("OnRtnRepealFromBankToFutureByFutureManual",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnRepealFromBankToFutureByFutureManual
        >::value
    );
    c.def("OnRtnRepealFromFutureToBankByFutureManual",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnRepealFromFutureToBankByFutureManual
        >::value
    );
    c.def("OnRtnQueryBankBalanceByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnQueryBankBalanceByFuture
        >::value
    );
    c.def("OnErrRtnBankToFutureByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnBankToFutureByFuture
        >::value
    );
    c.def("OnErrRtnFutureToBankByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnFutureToBankByFuture
        >::value
    );
    c.def("OnErrRtnRepealBankToFutureByFutureManual",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnRepealBankToFutureByFutureManual
        >::value
    );
    c.def("OnErrRtnRepealFutureToBankByFutureManual",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnRepealFutureToBankByFutureManual
        >::value
    );
    c.def("OnErrRtnQueryBankBalanceByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnErrRtnQueryBankBalanceByFuture
        >::value
    );
    c.def("OnRtnRepealFromBankToFutureByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnRepealFromBankToFutureByFuture
        >::value
    );
    c.def("OnRtnRepealFromFutureToBankByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnRepealFromFutureToBankByFuture
        >::value
    );
    c.def("OnRspFromBankToFutureByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspFromBankToFutureByFuture
        >::value
    );
    c.def("OnRspFromFutureToBankByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspFromFutureToBankByFuture
        >::value
    );
    c.def("OnRspQueryBankAccountMoneyByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRspQueryBankAccountMoneyByFuture
        >::value
    );
    c.def("OnRtnOpenAccountByBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnOpenAccountByBank
        >::value
    );
    c.def("OnRtnCancelAccountByBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnCancelAccountByBank
        >::value
    );
    c.def("OnRtnChangeAccountByBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderSpi::OnRtnChangeAccountByBank
        >::value
    );
}
void generate_class_CThostFtdcTraderApi(pybind11::module &m)
{
    pybind11::class_<
        CThostFtdcTraderApi,
        std::unique_ptr<CThostFtdcTraderApi, pybind11::nodelete>,
        PyCThostFtdcTraderApi
    > c(m, "CThostFtdcTraderApi");
    c.def_static("CreateFtdcTraderApi",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::CreateFtdcTraderApi
        >::value
    );
    c.def_static("GetApiVersion",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::GetApiVersion
        >::value
    );
    c.def("Release",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::Release
        >::value
    );
    c.def("Init",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::Init
        >::value
    );
    c.def("Join",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::Join
        >::value
    );
    c.def("GetTradingDay",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::GetTradingDay
        >::value
    );
    c.def("RegisterFront",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::RegisterFront
        >::value
    );
    c.def("RegisterNameServer",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::RegisterNameServer
        >::value
    );
    c.def("RegisterFensUserInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::RegisterFensUserInfo
        >::value
    );
    c.def("RegisterSpi",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::RegisterSpi
        >::value
    );
    c.def("SubscribePrivateTopic",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::SubscribePrivateTopic
        >::value
    );
    c.def("SubscribePublicTopic",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::SubscribePublicTopic
        >::value
    );
    c.def("ReqAuthenticate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqAuthenticate
        >::value
    );
    c.def("RegisterUserSystemInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::RegisterUserSystemInfo
        >::value
    );
    c.def("SubmitUserSystemInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::SubmitUserSystemInfo
        >::value
    );
    c.def("ReqUserLogin",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqUserLogin
        >::value
    );
    c.def("ReqUserLogout",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqUserLogout
        >::value
    );
    c.def("ReqUserPasswordUpdate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqUserPasswordUpdate
        >::value
    );
    c.def("ReqTradingAccountPasswordUpdate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqTradingAccountPasswordUpdate
        >::value
    );
    c.def("ReqUserAuthMethod",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqUserAuthMethod
        >::value
    );
    c.def("ReqGenUserCaptcha",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqGenUserCaptcha
        >::value
    );
    c.def("ReqGenUserText",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqGenUserText
        >::value
    );
    c.def("ReqUserLoginWithCaptcha",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqUserLoginWithCaptcha
        >::value
    );
    c.def("ReqUserLoginWithText",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqUserLoginWithText
        >::value
    );
    c.def("ReqUserLoginWithOTP",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqUserLoginWithOTP
        >::value
    );
    c.def("ReqOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqOrderInsert
        >::value
    );
    c.def("ReqParkedOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqParkedOrderInsert
        >::value
    );
    c.def("ReqParkedOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqParkedOrderAction
        >::value
    );
    c.def("ReqOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqOrderAction
        >::value
    );
    c.def("ReqQueryMaxOrderVolume",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQueryMaxOrderVolume
        >::value
    );
    c.def("ReqSettlementInfoConfirm",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqSettlementInfoConfirm
        >::value
    );
    c.def("ReqRemoveParkedOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqRemoveParkedOrder
        >::value
    );
    c.def("ReqRemoveParkedOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqRemoveParkedOrderAction
        >::value
    );
    c.def("ReqExecOrderInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqExecOrderInsert
        >::value
    );
    c.def("ReqExecOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqExecOrderAction
        >::value
    );
    c.def("ReqForQuoteInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqForQuoteInsert
        >::value
    );
    c.def("ReqQuoteInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQuoteInsert
        >::value
    );
    c.def("ReqQuoteAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQuoteAction
        >::value
    );
    c.def("ReqBatchOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqBatchOrderAction
        >::value
    );
    c.def("ReqOptionSelfCloseInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqOptionSelfCloseInsert
        >::value
    );
    c.def("ReqOptionSelfCloseAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqOptionSelfCloseAction
        >::value
    );
    c.def("ReqCombActionInsert",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqCombActionInsert
        >::value
    );
    c.def("ReqQryOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryOrder
        >::value
    );
    c.def("ReqQryTrade",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryTrade
        >::value
    );
    c.def("ReqQryInvestorPosition",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInvestorPosition
        >::value
    );
    c.def("ReqQryTradingAccount",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryTradingAccount
        >::value
    );
    c.def("ReqQryInvestor",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInvestor
        >::value
    );
    c.def("ReqQryTradingCode",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryTradingCode
        >::value
    );
    c.def("ReqQryInstrumentMarginRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInstrumentMarginRate
        >::value
    );
    c.def("ReqQryInstrumentCommissionRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInstrumentCommissionRate
        >::value
    );
    c.def("ReqQryExchange",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryExchange
        >::value
    );
    c.def("ReqQryProduct",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryProduct
        >::value
    );
    c.def("ReqQryInstrument",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInstrument
        >::value
    );
    c.def("ReqQryDepthMarketData",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryDepthMarketData
        >::value
    );
    c.def("ReqQrySettlementInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQrySettlementInfo
        >::value
    );
    c.def("ReqQryTransferBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryTransferBank
        >::value
    );
    c.def("ReqQryInvestorPositionDetail",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInvestorPositionDetail
        >::value
    );
    c.def("ReqQryNotice",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryNotice
        >::value
    );
    c.def("ReqQrySettlementInfoConfirm",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQrySettlementInfoConfirm
        >::value
    );
    c.def("ReqQryInvestorPositionCombineDetail",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInvestorPositionCombineDetail
        >::value
    );
    c.def("ReqQryCFMMCTradingAccountKey",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryCFMMCTradingAccountKey
        >::value
    );
    c.def("ReqQryEWarrantOffset",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryEWarrantOffset
        >::value
    );
    c.def("ReqQryInvestorProductGroupMargin",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInvestorProductGroupMargin
        >::value
    );
    c.def("ReqQryExchangeMarginRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryExchangeMarginRate
        >::value
    );
    c.def("ReqQryExchangeMarginRateAdjust",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryExchangeMarginRateAdjust
        >::value
    );
    c.def("ReqQryExchangeRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryExchangeRate
        >::value
    );
    c.def("ReqQrySecAgentACIDMap",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQrySecAgentACIDMap
        >::value
    );
    c.def("ReqQryProductExchRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryProductExchRate
        >::value
    );
    c.def("ReqQryProductGroup",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryProductGroup
        >::value
    );
    c.def("ReqQryMMInstrumentCommissionRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryMMInstrumentCommissionRate
        >::value
    );
    c.def("ReqQryMMOptionInstrCommRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryMMOptionInstrCommRate
        >::value
    );
    c.def("ReqQryInstrumentOrderCommRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInstrumentOrderCommRate
        >::value
    );
    c.def("ReqQrySecAgentTradingAccount",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQrySecAgentTradingAccount
        >::value
    );
    c.def("ReqQrySecAgentCheckMode",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQrySecAgentCheckMode
        >::value
    );
    c.def("ReqQrySecAgentTradeInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQrySecAgentTradeInfo
        >::value
    );
    c.def("ReqQryOptionInstrTradeCost",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryOptionInstrTradeCost
        >::value
    );
    c.def("ReqQryOptionInstrCommRate",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryOptionInstrCommRate
        >::value
    );
    c.def("ReqQryExecOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryExecOrder
        >::value
    );
    c.def("ReqQryForQuote",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryForQuote
        >::value
    );
    c.def("ReqQryQuote",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryQuote
        >::value
    );
    c.def("ReqQryOptionSelfClose",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryOptionSelfClose
        >::value
    );
    c.def("ReqQryInvestUnit",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryInvestUnit
        >::value
    );
    c.def("ReqQryCombInstrumentGuard",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryCombInstrumentGuard
        >::value
    );
    c.def("ReqQryCombAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryCombAction
        >::value
    );
    c.def("ReqQryTransferSerial",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryTransferSerial
        >::value
    );
    c.def("ReqQryAccountregister",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryAccountregister
        >::value
    );
    c.def("ReqQryContractBank",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryContractBank
        >::value
    );
    c.def("ReqQryParkedOrder",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryParkedOrder
        >::value
    );
    c.def("ReqQryParkedOrderAction",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryParkedOrderAction
        >::value
    );
    c.def("ReqQryTradingNotice",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryTradingNotice
        >::value
    );
    c.def("ReqQryBrokerTradingParams",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryBrokerTradingParams
        >::value
    );
    c.def("ReqQryBrokerTradingAlgos",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQryBrokerTradingAlgos
        >::value
    );
    c.def("ReqQueryCFMMCTradingAccountToken",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQueryCFMMCTradingAccountToken
        >::value
    );
    c.def("ReqFromBankToFutureByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqFromBankToFutureByFuture
        >::value
    );
    c.def("ReqFromFutureToBankByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqFromFutureToBankByFuture
        >::value
    );
    c.def("ReqQueryBankAccountMoneyByFuture",
        autocxxpy::calling_wrapper<
        &CThostFtdcTraderApi::ReqQueryBankAccountMoneyByFuture
        >::value
    );
}
void generate_class_CThostFtdcMdSpi(pybind11::module &m)
{
    pybind11::class_<
        CThostFtdcMdSpi,
        std::unique_ptr<CThostFtdcMdSpi, pybind11::nodelete>,
        PyCThostFtdcMdSpi
    > c(m, "CThostFtdcMdSpi");
    c.def(pybind11::init<>());
    c.def("OnFrontConnected",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnFrontConnected
        >::value
    );
    c.def("OnFrontDisconnected",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnFrontDisconnected
        >::value
    );
    c.def("OnHeartBeatWarning",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnHeartBeatWarning
        >::value
    );
    c.def("OnRspUserLogin",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRspUserLogin
        >::value
    );
    c.def("OnRspUserLogout",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRspUserLogout
        >::value
    );
    c.def("OnRspError",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRspError
        >::value
    );
    c.def("OnRspSubMarketData",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRspSubMarketData
        >::value
    );
    c.def("OnRspUnSubMarketData",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRspUnSubMarketData
        >::value
    );
    c.def("OnRspSubForQuoteRsp",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRspSubForQuoteRsp
        >::value
    );
    c.def("OnRspUnSubForQuoteRsp",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRspUnSubForQuoteRsp
        >::value
    );
    c.def("OnRtnDepthMarketData",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRtnDepthMarketData
        >::value
    );
    c.def("OnRtnForQuoteRsp",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdSpi::OnRtnForQuoteRsp
        >::value
    );
}
void generate_class_CThostFtdcMdApi(pybind11::module &m)
{
    pybind11::class_<
        CThostFtdcMdApi,
        std::unique_ptr<CThostFtdcMdApi, pybind11::nodelete>,
        PyCThostFtdcMdApi
    > c(m, "CThostFtdcMdApi");
    c.def_static("CreateFtdcMdApi",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::CreateFtdcMdApi
        >::value
    );
    c.def_static("GetApiVersion",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::GetApiVersion
        >::value
    );
    c.def("Release",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::Release
        >::value
    );
    c.def("Init",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::Init
        >::value
    );
    c.def("Join",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::Join
        >::value
    );
    c.def("GetTradingDay",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::GetTradingDay
        >::value
    );
    c.def("RegisterFront",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::RegisterFront
        >::value
    );
    c.def("RegisterNameServer",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::RegisterNameServer
        >::value
    );
    c.def("RegisterFensUserInfo",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::RegisterFensUserInfo
        >::value
    );
    c.def("RegisterSpi",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::RegisterSpi
        >::value
    );
    c.def("SubscribeMarketData",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::SubscribeMarketData
        >::value
    );
    c.def("UnSubscribeMarketData",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::UnSubscribeMarketData
        >::value
    );
    c.def("SubscribeForQuoteRsp",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::SubscribeForQuoteRsp
        >::value
    );
    c.def("UnSubscribeForQuoteRsp",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::UnSubscribeForQuoteRsp
        >::value
    );
    c.def("ReqUserLogin",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::ReqUserLogin
        >::value
    );
    c.def("ReqUserLogout",
        autocxxpy::calling_wrapper<
        &CThostFtdcMdApi::ReqUserLogout
        >::value
    );
}
