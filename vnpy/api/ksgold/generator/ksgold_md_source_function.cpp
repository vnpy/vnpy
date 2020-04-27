void MdApi::release()
{
	this->api->Release()
};

bool MdApi::init()
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);
	this->api->Init();
};

int MdApi::join()
{
	int i =this->api->Join()
	return i;
};

void MdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront(string pszFrontAddress)
};

void createGoldQutoApi(string pszFlowPath)
{
	this->api = CKSGoldQuotApi::CreateGoldQutoApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

int MdApi::subscribeMarketData(string ppInstrumentID, int reqid)
{
	int i =this->api->SubscribeMarketData(string ppInstrumentID, int reqid)
	return i;
};

int MdApi::unSubscribeMarketData(string ppInstrumentID, int reqid)
{
	int i =this->api->UnSubscribeMarketData(string ppInstrumentID, int reqid)
	return i;
};

int MdApi::reqUserLogin(const dict &req, int reqid)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountID", myreq.AccountID);
	getInt(req, "LoginType", &myreq.LoginType);
	getString(req, "Password", myreq.Password);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "UserProductionInfo", myreq.UserProductionInfo);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int MdApi::reqUserLogout(const dict &req, int reqid)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

