int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "lastLoginTime", myreq.lastLoginTime);
	getChar(req, "tradeDate", myreq.tradeDate);
	getChar(req, "ipGatewayAddress", myreq.ipGatewayAddress);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getInt(req, "loginbatch", &myreq.loginbatch);
	getChar(req, "memberID", myreq.memberID);
	getInt(req, "loginType", &myreq.loginType);
	getInt(req, "portGateway", &myreq.portGateway);
	getChar(req, "obligate", myreq.obligate);
	getInt(req, "gateWayCurLinkNum", &myreq.gateWayCurLinkNum);
	getChar(req, "lastLoginDate", myreq.lastLoginDate);
	getInt(req, "machineID", &myreq.machineID);
	getChar(req, "msg", myreq.msg);
	getChar(req, "lastLoginIp", myreq.lastLoginIp);
	getChar(req, "password", myreq.password);
	getChar(req, "gateWayYYBDB", myreq.gateWayYYBDB);
	getChar(req, "clientName", myreq.clientName);
	getChar(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "loginbatch", &myreq.loginbatch);
	getChar(req, "gateWayYYBDB", myreq.gateWayYYBDB);
	getChar(req, "tradeDate", myreq.tradeDate);
	getInt(req, "machineID", &myreq.machineID);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "traderID", myreq.traderID);
	getChar(req, "memberID", myreq.memberID);
	getChar(req, "obligate", myreq.obligate);
	getInt(req, "gateWayCurLinkNum", &myreq.gateWayCurLinkNum);
	getChar(req, "lastLoginDate", myreq.lastLoginDate);
	getChar(req, "lastLoginTime", myreq.lastLoginTime);
	getChar(req, "msg", myreq.msg);
	getChar(req, "lastLoginIp", myreq.lastLoginIp);
	getChar(req, "password", myreq.password);
	getChar(req, "ipAddress", myreq.ipAddress);
	getChar(req, "clientName", myreq.clientName);
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
	getChar(req, "offsetFlag", myreq.offsetFlag);
	getChar(req, "entrustTime", myreq.entrustTime);
	getChar(req, "LocalOrderNo", myreq.LocalOrderNo);
	getChar(req, "marketID", myreq.marketID);
	getChar(req, "orderNo", myreq.orderNo);
	getChar(req, "tradeWay", myreq.tradeWay);
	getChar(req, "buyOrSell", myreq.buyOrSell);
	getChar(req, "instID", myreq.instID);
	getChar(req, "seatID", myreq.seatID);
	getChar(req, "status", myreq.status);
	getChar(req, "cancelTime", myreq.cancelTime);
	getChar(req, "middleFlag", myreq.middleFlag);
	getChar(req, "middleFlag", myreq.middleFlag);
	getChar(req, "validDate", myreq.validDate);
	getInt(req, "matchQty", &myreq.matchQty);
	getChar(req, "clientID", myreq.clientID);
	getChar(req, "clientID", myreq.clientID);
	getChar(req, "forceoffset_flag", myreq.forceoffset_flag);
	getChar(req, "orderFlag", myreq.orderFlag);
	getInt(req, "volumnCheck", &myreq.volumnCheck);
	getInt(req, "cancelQty", &myreq.cancelQty);
	getChar(req, "priceFlag", myreq.priceFlag);
	getChar(req, "exchangeID", myreq.exchangeID);
	getInt(req, "amount", &myreq.amount);
	getInt(req, "amount", &myreq.amount);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "tradeWay", myreq.tradeWay);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "marketID", myreq.marketID);
	getChar(req, "traderID", myreq.traderID);
	getChar(req, "orderFlag", myreq.orderFlag);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "instID", myreq.instID);
	getChar(req, "traderID", myreq.traderID);
	getChar(req, "memberID", myreq.memberID);
	getChar(req, "clientID", myreq.clientID);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "clientID", myreq.clientID);
	getChar(req, "traderID", myreq.traderID);
	getChar(req, "memberID", myreq.memberID);
	getChar(req, "accountType", myreq.accountType);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "exchangeID", myreq.exchangeID);
	getChar(req, "instID", myreq.instID);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "traderID", myreq.traderID);
	getChar(req, "memberID", myreq.memberID);
	getChar(req, "clientID", myreq.clientID);
	getChar(req, "marketID", myreq.marketID);
	getChar(req, "matchNo", myreq.matchNo);
	getChar(req, "orderNo", myreq.orderNo);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "status", myreq.status);
	getChar(req, "exchangeID", myreq.exchangeID);
	getChar(req, "offsetFlag", myreq.offsetFlag);
	getChar(req, "instID", myreq.instID);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "traderID", myreq.traderID);
	getChar(req, "memberID", myreq.memberID);
	getChar(req, "clientID", myreq.clientID);
	getChar(req, "marketID", myreq.marketID);
	getChar(req, "orderNo", myreq.orderNo);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryStorage(dict req, int nRequestID)
{
	CThostFtdcQryStorageField myreq = CThostFtdcQryStorageField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "traderID", myreq.traderID);
	getChar(req, "memberID", myreq.memberID);
	getChar(req, "clientID", myreq.clientID);
	int i = this->api->ReqQryStorage(&myreq, nRequestID);
	return i;
};

