int MdApi::reqStockUserLogin(const dict &req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	getString(req, "authenticCode", myreq.authenticCode);
	getString(req, "appID", myreq.appID);
	getInt(req, "collectInterType", &myreq.collectInterType);
	int i = this->api->ReqStockUserLogin(&myreq);
	return i;
};

int MdApi::reqStockUserLogout(const dict &req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockUserLogout(&myreq);
	return i;
};

int MdApi::reqSOPUserLogin(const dict &req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	getString(req, "authenticCode", myreq.authenticCode);
	getString(req, "appID", myreq.appID);
	getInt(req, "collectInterType", &myreq.collectInterType);
	int i = this->api->ReqSOPUserLogin(&myreq);
	return i;
};

int MdApi::reqFASLUserLogin(const dict &req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	getString(req, "authenticCode", myreq.authenticCode);
	getString(req, "appID", myreq.appID);
	getInt(req, "collectInterType", &myreq.collectInterType);
	int i = this->api->ReqFASLUserLogin(&myreq);
	return i;
};

int MdApi::reqSOPUserLogout(const dict &req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqSOPUserLogout(&myreq);
	return i;
};

int MdApi::reqFASLUserLogout(const dict &req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLUserLogout(&myreq);
	return i;
};

int MdApi::reqStockAvailableQuotQry(const dict &req)
{
	DFITCReqQuotQryField myreq = DFITCReqQuotQryField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqStockAvailableQuotQry(&myreq);
	return i;
};

int MdApi::reqSopAvailableQuotQry(const dict &req)
{
	DFITCReqQuotQryField myreq = DFITCReqQuotQryField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqSopAvailableQuotQry(&myreq);
	return i;
};

int MdApi::reqUserMDPasswordUpdate(const dict &req)
{
	DFITCSECReqMDPasswordUpdateField myreq = DFITCSECReqMDPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "oldPassword", myreq.oldPassword);
	getString(req, "newPassword", myreq.newPassword);
	int i = this->api->ReqUserMDPasswordUpdate(&myreq);
	return i;
};

