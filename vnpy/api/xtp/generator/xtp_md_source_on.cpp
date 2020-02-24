void onDisconnected(int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDisconnected, reqid);
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

void onDepthMarketData(const dict &data, int reqid, int reqid, int reqid, int reqid, int reqid, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDepthMarketData, data, reqid, reqid, reqid, reqid, reqid, reqid);
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

void onSubscribeAllMarketData(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllMarketData(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOrderBook(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOrderBook, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOrderBook(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOrderBook, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllTickByTick(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllTickByTick, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllTickByTick(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllTickByTick, data, error);
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

void onSubscribeAllOptionMarketData(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOptionMarketData(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOptionOrderBook(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionOrderBook, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOptionOrderBook(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionOrderBook, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOptionTickByTick(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionTickByTick, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOptionTickByTick(int data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionTickByTick, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

