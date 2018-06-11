int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CSecurityFtdcUserLoginField myreq = CSecurityFtdcUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "Password", myreq.Password);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "DataLevel", myreq.DataLevel);
	getChar(req, "UserID", myreq.UserID);
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

