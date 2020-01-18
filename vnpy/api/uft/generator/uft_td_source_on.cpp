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

void onFrontDisconnected(int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFrontDisconnected, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAuthenticate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAuthenticate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspUserLogin, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspUserPasswordUpdate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspErrorOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspErrorOrderInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspErrorExerciseOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspErrorExerciseOrderInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspExerciseOrderAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspExerciseOrderAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspErrorLockInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspErrorLockInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspForQuoteInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspForQuoteInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspErrorCombActionInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspErrorCombActionInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryMaxOrderVolume(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQueryMaxOrderVolume, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryLockVolume(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQueryLockVolume, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryExerciseVolume(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQueryExerciseVolume, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspQryPosition, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTradingAccount, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTrade, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExercise(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryExercise, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryLock(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryLock, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCombAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCombAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPositionCombineDetail(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryPositionCombineDetail, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspQryInstrument, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCoveredShort(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCoveredShort, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExerciseAssign(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryExerciseAssign, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspTransfer(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspTransfer, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTransfer(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTransfer, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryBankBalance(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQueryBankBalance, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryBankAccount(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQueryBankAccount, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryBillContent(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQueryBillContent, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspBillConfirm(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspBillConfirm, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryMargin(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryMargin, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCommission(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCommission, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPositionDetail(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryPositionDetail, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchangeRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryExchangeRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySysConfig(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQrySysConfig, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryDepthMarketData(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryDepthMarketData, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnTrade(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnTrade, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOrder(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnExercise(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnExercise, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCombAction(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnCombAction, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnLock(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnLock, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

