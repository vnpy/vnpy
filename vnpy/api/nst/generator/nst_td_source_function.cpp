int TdApi::reqUserLogin()
{
	int i = this->api->ReqUserLogin();
	return i;
};

int TdApi::reqUserLogout()
{
	int i = this->api->ReqUserLogout();
	return i;
};

int TdApi::reqOrderAction()
{
	int myreq = int();
	int i = this->api->ReqOrderAction();
	return i;
};

int TdApi::reqTradingAccount()
{
	int i = this->api->ReqTradingAccount();
	return i;
};

int TdApi::reqQryOrder()
{
	char myreq = char();
	int i = this->api->ReqQryOrder();
	return i;
};

int TdApi::reqQryTrade()
{
	char myreq = char();
	int i = this->api->ReqQryTrade();
	return i;
};

int TdApi::reqQryInvestorPosition()
{
	char myreq = char();
	int i = this->api->ReqQryInvestorPosition();
	return i;
};

int TdApi::reqChangePwd()
{
	char myreq = char();
	int i = this->api->ReqChangePwd();
	return i;
};

int TdApi::reqQryTest()
{
	int i = this->api->ReqQryTest();
	return i;
};

