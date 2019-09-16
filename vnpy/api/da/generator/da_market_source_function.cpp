int MarketApi::reqUserLogin(const dict &req, int reqid)
{
	CMarketReqUserLoginField myreq = CMarketReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserPwd", myreq.UserPwd);
	getString(req, "UserType", myreq.UserType);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "ComputerName", myreq.ComputerName);
	getString(req, "SoftwareName", myreq.SoftwareName);
	getString(req, "SoftwareVersion", myreq.SoftwareVersion);
	getString(req, "AuthorCode", myreq.AuthorCode);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int MarketApi::reqBrokerData(const dict &req, int reqid)
{
	CMarketReqBrokerDataField myreq = CMarketReqBrokerDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ContCode", myreq.ContCode);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqBrokerData(&myreq, reqid);
	return i;
};

int MarketApi::reqMarketData(const dict &req, int reqid)
{
	CMarketReqMarketDataField myreq = CMarketReqMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MarketType", &myreq.MarketType);
	getChar(req, "SubscMode", &myreq.SubscMode);
	getInt(req, "MarketCount", &myreq.MarketCount);
	getString(req, "MarketTrcode[MAX_SUB_COUNT]", myreq.MarketTrcode[MAX_SUB_COUNT]);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqMarketData(&myreq, reqid);
	return i;
};

