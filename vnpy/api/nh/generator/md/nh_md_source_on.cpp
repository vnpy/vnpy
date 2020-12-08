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

void onFrontDisConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onFrontDisConnected);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onHeartBeatWarning(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onHeartBeatWarning, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspError(const dict &data, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspError, data, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnMarketData(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRtnMarketData, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUtpLogin(const dict &data, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUtpLogin, data, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUtpLogout(const dict &data, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUtpLogout, data, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubscribe(const dict &data, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubscribe, data, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubscribe(const dict &data, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubscribe, data, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchange(const dict &data, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspQryExchange, data, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInstrument(const dict &data, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspQryInstrument, data, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

