void onFrontConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onFrontConnected);
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
		PYBIND11_OVERLOAD(void, StockApi, onFrontDisconnected, reqid);
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
		PYBIND11_OVERLOAD(void, StockApi, onHeartBeatWarning, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspNeedVerify(bool last, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspNeedVerify, last, last);
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
		PYBIND11_OVERLOAD(void, StockApi, onRspUserLogin, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogout(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspUserLogout, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspVerifyCode(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspVerifyCode, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSafeVerify(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspSafeVerify, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSetVerifyQA(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspSetVerifyQA, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAccount(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspAccount, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQuestion(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQuestion, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspOrderInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderModify(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspOrderModify, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderCancel(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspOrderCancel, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspPasswordUpdate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnTrade(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnTrade, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOrder(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnOrder, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCapital(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnCapital, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPosition(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnPosition, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTick(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryTick, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryOrder, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryTrade, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCapital(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryCapital, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryVersion(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryVersion, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryPosition, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCurrency(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryCurrency, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryExchange, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryInstrument, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

