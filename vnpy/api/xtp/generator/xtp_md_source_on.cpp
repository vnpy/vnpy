void onDisconnected(int extra) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDisconnected, extra);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onError(const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onError, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubMarketData(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubMarketData, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubMarketData(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubMarketData, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDepthMarketData(const dict &data, int extra, int extra, int extra, int extra, int extra, int extra) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDepthMarketData, data, extra, extra, extra, extra, extra, extra);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubOrderBook(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubOrderBook, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubOrderBook(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubOrderBook, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderBook(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onOrderBook, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubTickByTick(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubTickByTick, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubTickByTick(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubTickByTick, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onTickByTick(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onTickByTick, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllMarketData(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMarketData, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllMarketData(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMarketData, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOrderBook(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOrderBook, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOrderBook(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOrderBook, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllTickByTick(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllTickByTick, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllTickByTick(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllTickByTick, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryAllTickers(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickers, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryTickersPriceInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryTickersPriceInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOptionMarketData(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionMarketData, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOptionMarketData(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionMarketData, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOptionOrderBook(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionOrderBook, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOptionOrderBook(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionOrderBook, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOptionTickByTick(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionTickByTick, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOptionTickByTick(int extra, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionTickByTick, extra, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

