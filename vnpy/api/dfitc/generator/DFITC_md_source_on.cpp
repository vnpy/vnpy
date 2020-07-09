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

void onRtnNotice(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRtnNotice, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspError(const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspError, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockUserLogin(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspStockUserLogin, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockUserLogout(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspStockUserLogout, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPUserLogin(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSOPUserLogin, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPUserLogout(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSOPUserLogout, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLUserLogin(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspFASLUserLogin, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLUserLogout(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspFASLUserLogout, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockSubMarketData(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspStockSubMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockUnSubMarketData(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspStockUnSubMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPSubMarketData(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSOPSubMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPUnSubMarketData(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSOPUnSubMarketData, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onStockMarketData(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onStockMarketData, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSOPMarketData(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSOPMarketData, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockAvailableQuot(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspStockAvailableQuot, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSopAvailableQuot(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSopAvailableQuot, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserMDPasswordUpdate(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUserMDPasswordUpdate, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

