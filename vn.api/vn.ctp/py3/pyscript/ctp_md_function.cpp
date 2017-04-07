int MdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "Password", myreq.Password);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "TradingDay", myreq.TradingDay);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int MdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

