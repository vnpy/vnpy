int MdApi::reqUserLogin(dict req)
{
	DFITCUserLoginField myreq = DFITCUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "passwd", myreq.passwd);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "companyID", &myreq.companyID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogin(&myreq);
	return i;
};

int MdApi::reqUserLogout(dict req)
{
	DFITCUserLogoutField myreq = DFITCUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "sessionID", &myreq.sessionID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogout(&myreq);
	return i;
};

int MdApi::reqTradingDay(dict req)
{
	DFITCTradingDayField myreq = DFITCTradingDayField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	int i = this->api->ReqTradingDay(&myreq);
	return i;
};

