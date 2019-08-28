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

void onRspUserLogin(const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspUserLogin, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogout(const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspUserLogout, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspVerifyCode(const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspVerifyCode, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSafeVerify(const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspSafeVerify, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSetVerifyQA(const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspSetVerifyQA, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAccount(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspAccount, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQuestion(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQuestion, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderInsert(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspOrderInsert, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderModify(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspOrderModify, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderCancel(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspOrderCancel, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspPasswordUpdate(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspPasswordUpdate, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnTrade(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnTrade, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOrder(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnOrder, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCapital(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnCapital, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPosition(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRtnPosition, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTick(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryTick, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrder(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryOrder, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTrade(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryTrade, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCapital(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryCapital, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryVersion(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryVersion, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPosition(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryPosition, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCurrency(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryCurrency, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchange(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryExchange, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInstrument(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, StockApi, onRspQryInstrument, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

