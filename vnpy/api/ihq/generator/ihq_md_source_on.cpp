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

void onFrontDisconnected(int extra) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onFrontDisconnected, extra);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onHeartBeatWarning(int extra) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onHeartBeatWarning, extra);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspError(const dict &error, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspError, error, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogin(const dict &data, const dict &error, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUserLogin, data, error, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogout(const dict &data, const dict &error, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUserLogout, data, error, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubAllMarketData(int tick, int exchange, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubAllMarketData, tick, exchange, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubAllMarketData(int tick, int exchange, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubAllMarketData, tick, exchange, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubAllTickByTick(int exchange, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubAllTickByTick, exchange, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubAllTickByTick(int exchange, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubAllTickByTick, exchange, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubMarketData(string tickers, int count, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubMarketData, tickers, count, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubMarketData(string tickers, int count, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubMarketData, tickers, count, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubTickByTick(string tickers, int count, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubTickByTick, tickers, count, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubTickByTick(string tickers, int count, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubTickByTick, tickers, count, reqid, result);
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

void onRtnTickByTick(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRtnTickByTick, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOrderBook(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRtnOrderBook, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubOrderBook(string tickers, int count, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubOrderBook, tickers, count, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubOrderBook(string tickers, int count, int reqid, bool result) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubOrderBook, tickers, count, reqid, result);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

