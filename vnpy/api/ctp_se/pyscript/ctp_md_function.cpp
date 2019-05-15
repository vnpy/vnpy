int MdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "Password", myreq.Password);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int MdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

