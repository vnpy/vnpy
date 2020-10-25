int MdApi::ReqUserLogin(CIStoneReqUserLogin pReqUserLogin,int nRequestID)
{
	CIStoneReqUserLogin myreq = CIStoneReqUserLogin();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "UserID", myreq.UserID);
	getString(req, "Password", myreq.Password);
	getString(req, "UserProductInfo", myreq.UserProductInfo);
	getString(req, "IPAddress", myreq.IPAddress);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqUserLogin(&myreq,nRequestI);
	return i;
};

int MdApi::ReqUserLogout(CIStoneReqUserLogout pReqUserLogout,int nRequestID)
{
	CIStoneReqUserLogout myreq = CIStoneReqUserLogout();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogout(&myreq,nRequestI);
	return i;
};

int MdApi::subAllMarketData(int tickType,int exchangeID,int nRequestID)
{
	int i = this->api->subAllMarketData(tickTypeexchangeIDnRequestI);
	return i;
};

int MdApi::unSubAllMarketData(int tickType,int exchangeID,int nRequestID)
{
	int i = this->api->unSubAllMarketData(tickTypeexchangeIDnRequestI);
	return i;
};

int MdApi::subAllTickByTick(int exchangeID,int nRequestID)
{
	int i = this->api->subAllTickByTick(exchangeIDnRequestI);
	return i;
};

int MdApi::unSubAllTickByTick(int exchangeID,int nRequestID)
{
	int i = this->api->unSubAllTickByTick(exchangeIDnRequestI);
	return i;
};

int MdApi::subMarketData(string ppInstrumentID,int nCount,int nRequestID)
{
	int i = this->api->subMarketData(ppInstrumentIDnCountnRequestI);
	return i;
};

int MdApi::unSubMarketData(string ppInstrumentID,int nCount,int nRequestID)
{
	int i = this->api->unSubMarketData(ppInstrumentIDnCountnRequestI);
	return i;
};

int MdApi::subTickByTick(string ppInstrumentID,int nCount,int nRequestID)
{
	int i = this->api->subTickByTick(ppInstrumentIDnCountnRequestI);
	return i;
};

int MdApi::unSubTickByTick(string ppInstrumentID,int nCount,int nRequestID)
{
	int i = this->api->unSubTickByTick(ppInstrumentIDnCountnRequestI);
	return i;
};

int MdApi::subAllOrderBook(int exchangeID,int nRequestID)
{
	int i = this->api->subAllOrderBook(exchangeIDnRequestI);
	return i;
};

int MdApi::unSubAllOrderBook(int exchangeID,int nRequestID)
{
	int i = this->api->unSubAllOrderBook(exchangeIDnRequestI);
	return i;
};

int MdApi::subOrderBook(string ppInstrumentID,int nCount,int nRequestID)
{
	int i = this->api->subOrderBook(ppInstrumentIDnCountnRequestI);
	return i;
};

int MdApi::unSubOrderBook(string ppInstrumentID,int nCount,int nRequestID)
{
	int i = this->api->unSubOrderBook(ppInstrumentIDnCountnRequestI);
	return i;
};

