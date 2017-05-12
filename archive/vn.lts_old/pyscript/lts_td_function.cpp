int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CSecurityFtdcReqUserLoginField myreq = CSecurityFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
	getChar(req, "UserProductInfo", myreq.UserProductInfo);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "AuthCode", myreq.AuthCode);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientIPAddress", myreq.ClientIPAddress);
	getChar(req, "OneTimePassword", myreq.OneTimePassword);
	getChar(req, "ProtocolInfo", myreq.ProtocolInfo);
	getChar(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CSecurityFtdcUserLogoutField myreq = CSecurityFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CSecurityFtdcInputOrderField myreq = CSecurityFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", myreq.ContingentCondition);
	getChar(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "LimitPrice", myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getChar(req, "Direction", myreq.Direction);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", myreq.OrderPriceType);
	getChar(req, "TimeCondition", myreq.TimeCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", myreq.ForceCloseReason);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getChar(req, "GTDDate", myreq.GTDDate);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CSecurityFtdcInputOrderActionField myreq = CSecurityFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OrderLocalID", myreq.OrderLocalID);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", myreq.ActionFlag);
	getInt(req, "FrontID", &myreq.FrontID);
	getChar(req, "BranchPBU", myreq.BranchPBU);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CSecurityFtdcUserPasswordUpdateField myreq = CSecurityFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqTradingAccountPasswordUpdate(dict req, int nRequestID)
{
	CSecurityFtdcTradingAccountPasswordUpdateField myreq = CSecurityFtdcTradingAccountPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqTradingAccountPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CSecurityFtdcQryExchangeField myreq = CSecurityFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryInstrumentField myreq = CSecurityFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ExchangeInstID", myreq.ExchangeInstID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CSecurityFtdcQryInvestorField myreq = CSecurityFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
{
	CSecurityFtdcQryTradingCodeField myreq = CSecurityFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CSecurityFtdcQryTradingAccountField myreq = CSecurityFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req, int nRequestID)
{
	CSecurityFtdcQryDepthMarketDataField myreq = CSecurityFtdcQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryDepthMarketData(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBondInterest(dict req, int nRequestID)
{
	CSecurityFtdcQryBondInterestField myreq = CSecurityFtdcQryBondInterestField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryBondInterest(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryMarketRationInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryMarketRationInfoField myreq = CSecurityFtdcQryMarketRationInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryMarketRationInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentCommissionRate(dict req, int nRequestID)
{
	CSecurityFtdcQryInstrumentCommissionRateField myreq = CSecurityFtdcQryInstrumentCommissionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OffsetFlag", myreq.OffsetFlag);
	getChar(req, "Direction", myreq.Direction);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInstrumentCommissionRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryETFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryETFInstrumentField myreq = CSecurityFtdcQryETFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ETFInstrumentID", myreq.ETFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryETFInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryETFBasket(dict req, int nRequestID)
{
	CSecurityFtdcQryETFBasketField myreq = CSecurityFtdcQryETFBasketField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ETFInstrumentID", myreq.ETFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryETFBasket(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryOFInstrumentField myreq = CSecurityFtdcQryOFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OFInstrumentID", myreq.OFInstrumentID);
	int i = this->api->ReqQryOFInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQrySFInstrumentField myreq = CSecurityFtdcQrySFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "SFInstrumentID", myreq.SFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQrySFInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CSecurityFtdcQryOrderField myreq = CSecurityFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "InsertTimeStart", myreq.InsertTimeStart);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	getChar(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CSecurityFtdcQryTradeField myreq = CSecurityFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "TradeTimeStart", myreq.TradeTimeStart);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "TradeID", myreq.TradeID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "TradeTimeEnd", myreq.TradeTimeEnd);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CSecurityFtdcQryInvestorPositionField myreq = CSecurityFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqFundOutByLiber(dict req, int nRequestID)
{
	CSecurityFtdcInputFundTransferField myreq = CSecurityFtdcInputFundTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountType", myreq.AccountType);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Digest", myreq.Digest);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqFundOutByLiber(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryFundTransferSerial(dict req, int nRequestID)
{
	CSecurityFtdcQryFundTransferSerialField myreq = CSecurityFtdcQryFundTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountType", myreq.AccountType);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryFundTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqFundInterTransfer(dict req, int nRequestID)
{
	CSecurityFtdcFundInterTransferField myreq = CSecurityFtdcFundInterTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SerialID", &myreq.SerialID);
	getChar(req, "TransferType", myreq.TransferType);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Password", myreq.Password);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqFundInterTransfer(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryFundInterTransferSerial(dict req, int nRequestID)
{
	CSecurityFtdcQryFundInterTransferSerialField myreq = CSecurityFtdcQryFundInterTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryFundInterTransferSerial(&myreq, nRequestID);
	return i;
};

