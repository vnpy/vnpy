void onFrontConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onFrontConnected);
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
		PYBIND11_OVERLOAD(void, MdApi, onFrontDisconnected, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspDepthMarketDataSubscribe(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspDepthMarketDataSubscribe, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspDepthMarketDataCancel(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspDepthMarketDataCancel, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnDepthMarketData(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRtnDepthMarketData, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

