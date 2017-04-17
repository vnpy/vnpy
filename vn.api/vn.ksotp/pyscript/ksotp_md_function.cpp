SubscribeMarketData
{
	CKSOTPSpecificInstrumentField myreq = CKSOTPSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->SubscribeMarketData(&myreq, nRequestID);
	return i;
};

UnSubscribeMarketData
{
	CKSOTPSpecificInstrumentField myreq = CKSOTPSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->UnSubscribeMarketData(&myreq, nRequestID);
	return i;
};

ReqUserLogin
{
	CKSOTPReqUserLoginField myreq = CKSOTPReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
	getChar(req, "UserProductInfo", myreq.UserProductInfo);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientIPAddress", myreq.ClientIPAddress);
	getChar(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

ReqUserLogout
{
	CKSOTPUserLogoutField myreq = CKSOTPUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

