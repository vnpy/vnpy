void onFrontConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFrontConnected);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogin(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspUserLogin, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onAnsOrderInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onAnsOrderInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onAnsOrderAction(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onAnsOrderAction, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderAction(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOrderRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onTradeRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onTradeRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspTradingAccount(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspTradingAccount, data);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspError, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrder(const dict &data, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, data, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTrade(const dict &data, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTrade, data, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInvestorPosition(const dict &data, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorPosition, data, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryChangePwd() override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryChangePwd);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspLogout(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspLogout, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnInstrumentStatus(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnInstrumentStatus, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspTest(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspTest, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnOrderInsert(const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderInsert, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnOrderAction(const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderAction, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

