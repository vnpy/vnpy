void onFrontConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onFrontConnected);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onFrontDisconnected(int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onFrontDisconnected, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onHeartBeatWarning(int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onHeartBeatWarning, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspRawData(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onRspRawData, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogin(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onRspUserLogin, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspTradeDate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onRspTradeDate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspBrokerData(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onRspBrokerData, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspMarketData(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MarketApi, onRspMarketData, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

