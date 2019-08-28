void onFrontConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, FutureApi, onFrontConnected);
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
		PYBIND11_OVERLOAD(void, FutureApi, onFrontDisconnected, reqid);
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
		PYBIND11_OVERLOAD(void, FutureApi, onHeartBeatWarning, reqid);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspNeedVerify, last, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspUserLogin, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspUserLogout, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspVerifyCode, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspSafeVerify, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspSetVerifyQA, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspAccount, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQuestion, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspOrderInsert, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspOrderModify, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspOrderCancel, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspPasswordUpdate, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRtnTrade, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRtnOrder, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRtnCapital, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRtnPosition, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryOrder, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryTrade, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryCapital, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryVersion, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryPosition, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryCurrency, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryExchange, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryStrategy(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryStrategy, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCommodity(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryCommodity, data, data, reqid, last);
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
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryInstrument, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchangeTime(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryExchangeTime, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCommodityTime(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryCommodityTime, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTotalPosition(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryTotalPosition, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryStrategyDetail(const dict &data, const dict &data, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FutureApi, onRspQryStrategyDetail, data, data, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

