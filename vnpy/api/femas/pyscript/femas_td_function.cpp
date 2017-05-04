int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CUstpFtdcReqUserLoginField myreq = CUstpFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
	getChar(req, "UserProductInfo", myreq.UserProductInfo);
	getChar(req, "UserID", myreq.UserID);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ProtocolInfo", myreq.ProtocolInfo);
	getChar(req, "Password", myreq.Password);
	getChar(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CUstpFtdcReqUserLogoutField myreq = CUstpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CUstpFtdcUserPasswordUpdateField myreq = CUstpFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CUstpFtdcInputOrderField myreq = CUstpFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getChar(req, "HedgeFlag", myreq.HedgeFlag);
	getChar(req, "HedgeFlag", myreq.HedgeFlag);
	getChar(req, "Direction", myreq.Direction);
	getChar(req, "OffsetFlag", myreq.OffsetFlag);
	getChar(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "OrderPriceType", myreq.OrderPriceType);
	getChar(req, "TimeCondition", myreq.TimeCondition);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", myreq.ForceCloseReason);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "GTDDate", myreq.GTDDate);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "UserCustom", myreq.UserCustom);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", myreq.VolumeCondition);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CUstpFtdcOrderActionField myreq = CUstpFtdcOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", myreq.ActionFlag);
	getChar(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getChar(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CUstpFtdcQryOrderField myreq = CUstpFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CUstpFtdcQryTradeField myreq = CUstpFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "TradeID", myreq.TradeID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryUserInvestor(dict req, int nRequestID)
{
	CUstpFtdcQryUserInvestorField myreq = CUstpFtdcQryUserInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryUserInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
{
	CUstpFtdcQryTradingCodeField myreq = CUstpFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorAccount(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorAccountField myreq = CUstpFtdcQryInvestorAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CUstpFtdcQryInstrumentField myreq = CUstpFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CUstpFtdcQryExchangeField myreq = CUstpFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorPositionField myreq = CUstpFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqSubscribeTopic(dict req, int nRequestID)
{
	CUstpFtdcDisseminationField myreq = CUstpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqSubscribeTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryComplianceParam(dict req, int nRequestID)
{
	CUstpFtdcQryComplianceParamField myreq = CUstpFtdcQryComplianceParamField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryComplianceParam(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTopic(dict req, int nRequestID)
{
	CUstpFtdcDisseminationField myreq = CUstpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqQryTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorFee(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorFeeField myreq = CUstpFtdcQryInvestorFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorFee(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorMargin(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorMarginField myreq = CUstpFtdcQryInvestorMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorMargin(&myreq, nRequestID);
	return i;
};

