int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CQdpFtdcReqUserLoginField myreq = CQdpFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CQdpFtdcReqUserLogoutField myreq = CQdpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CQdpFtdcUserPasswordUpdateField myreq = CQdpFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "NewPassword", myreq.NewPassword);
	getStr(req, "OldPassword", myreq.OldPassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CQdpFtdcInputOrderField myreq = CQdpFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getStr(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "BusinessType", &myreq.BusinessType);
	getStr(req, "GTDDate", myreq.GTDDate);
	getStr(req, "BranchID", myreq.BranchID);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "UserCustom", myreq.UserCustom);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RecNum", &myreq.RecNum);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CQdpFtdcOrderActionField myreq = CQdpFtdcOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getStr(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "FrontID", &myreq.FrontID);
	getInt(req, "RecNum", &myreq.RecNum);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromBankToFutureByFuture(dict req, int nRequestID)
{
	CQdpFtdcReqTransferField myreq = CQdpFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "VerifyCertNoFlag", myreq.VerifyCertNoFlag);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "TradeCode", myreq.TradeCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "CustType", myreq.CustType);
	getStr(req, "BankCodingForFuture", myreq.BankCodingForFuture);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getStr(req, "IdCardType", myreq.IdCardType);
	getStr(req, "Password", myreq.Password);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getStr(req, "TradingTime", myreq.TradingTime);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Message", myreq.Message);
	getDouble(req, "CustFee", &myreq.CustFee);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromBankToFutureByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromFutureToBankByFuture(dict req, int nRequestID)
{
	CQdpFtdcReqTransferField myreq = CQdpFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "VerifyCertNoFlag", myreq.VerifyCertNoFlag);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "TradeCode", myreq.TradeCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "CustType", myreq.CustType);
	getStr(req, "BankCodingForFuture", myreq.BankCodingForFuture);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getStr(req, "IdCardType", myreq.IdCardType);
	getStr(req, "Password", myreq.Password);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getStr(req, "TradingTime", myreq.TradingTime);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Message", myreq.Message);
	getDouble(req, "CustFee", &myreq.CustFee);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromFutureToBankByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CQdpFtdcQryOrderField myreq = CQdpFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CQdpFtdcQryTradeField myreq = CQdpFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "TradeID", myreq.TradeID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryUserInvestor(dict req, int nRequestID)
{
	CQdpFtdcQryUserInvestorField myreq = CQdpFtdcQryUserInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryUserInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorAccount(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorAccountField myreq = CQdpFtdcQryInvestorAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CQdpFtdcQryInstrumentField myreq = CQdpFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CQdpFtdcQryExchangeField myreq = CQdpFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorPositionField myreq = CQdpFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqSubscribeTopic(dict req, int nRequestID)
{
	CQdpFtdcDisseminationField myreq = CQdpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqSubscribeTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTopic(dict req, int nRequestID)
{
	CQdpFtdcDisseminationField myreq = CQdpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqQryTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorFee(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorFeeField myreq = CQdpFtdcQryInvestorFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorFee(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorMargin(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorMarginField myreq = CQdpFtdcQryInvestorMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorMargin(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeDiffTime(dict req, int nRequestID)
{
	CQdpFtdcQryExchangeDiffTimeField myreq = CQdpFtdcQryExchangeDiffTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchangeDiffTime(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryContractBank(dict req, int nRequestID)
{
	CQdpFtdcQryContractBankField myreq = CQdpFtdcQryContractBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getStr(req, "BankID", myreq.BankID);
	int i = this->api->ReqQryContractBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryBankAccountMoneyByFuture(dict req, int nRequestID)
{
	CQdpFtdcReqQueryAccountField myreq = CQdpFtdcReqQueryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "VerifyCertNoFlag", myreq.VerifyCertNoFlag);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "TradeCode", myreq.TradeCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "CustType", myreq.CustType);
	getStr(req, "BankCodingForFuture", myreq.BankCodingForFuture);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getStr(req, "IdCardType", myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getStr(req, "TradeDate", myreq.TradeDate);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqQueryBankAccountMoneyByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferSerial(dict req, int nRequestID)
{
	CQdpFtdcQryTransferSerialField myreq = CQdpFtdcQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySGEDeferRate(dict req, int nRequestID)
{
	CQdpFtdcQrySGEDeferRateField myreq = CQdpFtdcQrySGEDeferRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQrySGEDeferRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryMarketData(dict req, int nRequestID)
{
	CQdpFtdcQryMarketDataField myreq = CQdpFtdcQryMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryMarketData(&myreq, nRequestID);
	return i;
};

