int MdApi::reqQuot(dict req, int nRequestID)
{
	CSgitSubQuotField myreq = CSgitSubQuotField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ContractID", myreq.ContractID);
	int i = this->api->SubQuot(&myreq, nRequestID);
	return i;
};

int MdApi::reqUserLogin(dict req, int nRequestID)
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

int MdApi::reqUserLogout(dict req, int nRequestID)
{
	CSgitFtdcUserLogoutField myreq = CSgitFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

