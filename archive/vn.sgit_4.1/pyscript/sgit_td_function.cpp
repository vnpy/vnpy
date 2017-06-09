int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CSgitFtdcReqUserLoginField myreq = CSgitFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "UserProductInfo", myreq.UserProductInfo);
	getString(req, "UserID", myreq.UserID);
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ClientIPAddress", myreq.ClientIPAddress);
	getString(req, "OneTimePassword", myreq.OneTimePassword);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	getString(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CSgitFtdcUserLogoutField myreq = CSgitFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CSgitFtdcUserPasswordUpdateField myreq = CSgitFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	getString(req, "NewPassword", myreq.NewPassword);
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CSgitFtdcInputOrderField myreq = CSgitFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getString(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getString(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getString(req, "GTDDate", myreq.GTDDate);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "OrderRef", myreq.OrderRef);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CSgitFtdcInputOrderActionField myreq = CSgitFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getString(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getString(req, "OrderRef", myreq.OrderRef);
	getString(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getString(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CSgitFtdcQryOrderField myreq = CSgitFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InsertTimeStart", myreq.InsertTimeStart);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CSgitFtdcQryTradingAccountField myreq = CSgitFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CSgitFtdcQryInvestorField myreq = CSgitFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CSgitFtdcQryInstrumentField myreq = CSgitFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ExchangeInstID", myreq.ExchangeInstID);
	getString(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(dict req, int nRequestID)
{
	CSgitFtdcQryInvestorPositionDetailField myreq = CSgitFtdcQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPositionDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CSgitFtdcQryInvestorPositionField myreq = CSgitFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

