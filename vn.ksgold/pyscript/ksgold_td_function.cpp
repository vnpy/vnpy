int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "password", myreq.password);
	getChar(req, "tradeDate", myreq.tradeDate);
	getChar(req, "memberID", myreq.memberID);
	getInt(req, "loginType", &myreq.loginType);
	getChar(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "traderID", myreq.traderID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ProductID", myreq.ProductID);
	getChar(req, "ContractID", myreq.ContractID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "offsetFlag", myreq.offsetFlag);
	getChar(req, "buyOrSell", myreq.buyOrSell);
	getChar(req, "middleFlag", myreq.middleFlag);
	getChar(req, "tradeCode", myreq.tradeCode);
	getChar(req, "instID", myreq.instID);
	getChar(req, "instID", myreq.instID);
	getChar(req, "marketID", myreq.marketID);
	getChar(req, "marketID", myreq.marketID);
	getInt(req, "amount", &myreq.amount);
	getChar(req, "seatID", myreq.seatID);
	getChar(req, "priceFlag", myreq.priceFlag);
	getChar(req, "LocalOrderNo", myreq.LocalOrderNo);
	getChar(req, "tradeWay", myreq.tradeWay);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "status", myreq.status);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "instID", myreq.instID);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "remian", myreq.remian);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "instID", myreq.instID);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "matchNo", myreq.matchNo);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "instID", myreq.instID);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryStorage(dict req, int nRequestID)
{
	CThostFtdcQryStorageField myreq = CThostFtdcQryStorageField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "varietyID", myreq.varietyID);
	int i = this->api->ReqQryStorage(&myreq, nRequestID);
	return i;
};

