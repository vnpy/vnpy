void onFrontConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onFrontConnected);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onFrontDisconnected, reqid);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onHeartBeatWarning, reqid);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspAuthenticate, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspUserLogin, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspUserLogout, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspUserPasswordUpdate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspTradingAccountPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspTradingAccountPasswordUpdate, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspOrderInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspParkedOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspParkedOrderInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspParkedOrderAction, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspOrderAction, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQueryMaxOrderVolume, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSettlementInfoConfirm(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspSettlementInfoConfirm, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspRemoveParkedOrder(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspRemoveParkedOrder, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspRemoveParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspRemoveParkedOrderAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspExecOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspExecOrderInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspExecOrderAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspExecOrderAction, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspForQuoteInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQuoteInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQuoteAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQuoteAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspBatchOrderAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspBatchOrderAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOptionSelfCloseInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspOptionSelfCloseInsert, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOptionSelfCloseAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspOptionSelfCloseAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspCombActionInsert(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspCombActionInsert, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryOrder, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryTrade, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInvestorPosition, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryTradingAccount, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInvestor(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInvestor, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradingCode(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryTradingCode, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInstrumentMarginRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInstrumentMarginRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInstrumentCommissionRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInstrumentCommissionRate, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryExchange, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryProduct(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryProduct, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInstrument, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryDepthMarketData, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySettlementInfo(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQrySettlementInfo, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTransferBank(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryTransferBank, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInvestorPositionDetail(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInvestorPositionDetail, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryNotice(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryNotice, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySettlementInfoConfirm(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQrySettlementInfoConfirm, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInvestorPositionCombineDetail(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInvestorPositionCombineDetail, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCFMMCTradingAccountKey(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryCFMMCTradingAccountKey, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryEWarrantOffset(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryEWarrantOffset, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInvestorProductGroupMargin(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInvestorProductGroupMargin, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchangeMarginRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryExchangeMarginRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchangeMarginRateAdjust(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryExchangeMarginRateAdjust, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryExchangeRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySecAgentACIDMap(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQrySecAgentACIDMap, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryProductExchRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryProductExchRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryProductGroup(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryProductGroup, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryMMInstrumentCommissionRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryMMInstrumentCommissionRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryMMOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryMMOptionInstrCommRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInstrumentOrderCommRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInstrumentOrderCommRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySecAgentTradingAccount(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQrySecAgentTradingAccount, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySecAgentCheckMode(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQrySecAgentCheckMode, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOptionInstrTradeCost(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryOptionInstrTradeCost, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryOptionInstrCommRate, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExecOrder(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryExecOrder, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryForQuote(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryForQuote, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryQuote(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryQuote, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOptionSelfClose(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryOptionSelfClose, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryInvestUnit(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryInvestUnit, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCombInstrumentGuard(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryCombInstrumentGuard, data, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryCombAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTransferSerial(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryTransferSerial, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountregister(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryAccountregister, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspForQuote(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspForQuote, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspError(const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspError, error, reqid, last);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnOrder, data);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnTrade, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnOrderInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnOrderInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnOrderAction(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnOrderAction, data, error);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnInstrumentStatus, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnBulletin(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnBulletin, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnTradingNotice(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnTradingNotice, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnErrorConditionalOrder(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnErrorConditionalOrder, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnExecOrder(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnExecOrder, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnExecOrderInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnExecOrderInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnExecOrderAction(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnExecOrderAction, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnForQuoteInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnForQuoteInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnQuote(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnQuote, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnQuoteInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnQuoteInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnQuoteAction(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnQuoteAction, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnForQuote(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnForQuote, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCFMMCTradingAccountToken(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnCFMMCTradingAccountToken, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnBatchOrderAction(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnBatchOrderAction, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOptionSelfClose(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnOptionSelfClose, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnOptionSelfCloseInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnOptionSelfCloseInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnOptionSelfCloseAction(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnOptionSelfCloseAction, data, error);
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
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnCombAction, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnCombActionInsert(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnCombActionInsert, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryContractBank(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryContractBank, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryParkedOrder(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryParkedOrder, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryParkedOrderAction, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradingNotice(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryTradingNotice, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryBrokerTradingParams(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryBrokerTradingParams, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryBrokerTradingAlgos(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQryBrokerTradingAlgos, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryCFMMCTradingAccountToken(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQueryCFMMCTradingAccountToken, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFromBankToFutureByBank(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnFromBankToFutureByBank, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFromFutureToBankByBank(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnFromFutureToBankByBank, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnRepealFromBankToFutureByBank(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnRepealFromBankToFutureByBank, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnRepealFromFutureToBankByBank(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnRepealFromFutureToBankByBank, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFromBankToFutureByFuture(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnFromBankToFutureByFuture, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFromFutureToBankByFuture(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnFromFutureToBankByFuture, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnRepealFromBankToFutureByFutureManual(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnRepealFromBankToFutureByFutureManual, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnRepealFromFutureToBankByFutureManual(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnRepealFromFutureToBankByFutureManual, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnQueryBankBalanceByFuture(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnQueryBankBalanceByFuture, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnBankToFutureByFuture(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnBankToFutureByFuture, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnFutureToBankByFuture(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnFutureToBankByFuture, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnRepealBankToFutureByFutureManual(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnRepealBankToFutureByFutureManual, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnRepealFutureToBankByFutureManual(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnRepealFutureToBankByFutureManual, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onErrRtnQueryBankBalanceByFuture(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onErrRtnQueryBankBalanceByFuture, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnRepealFromBankToFutureByFuture(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnRepealFromBankToFutureByFuture, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnRepealFromFutureToBankByFuture(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnRepealFromFutureToBankByFuture, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFromBankToFutureByFuture(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspFromBankToFutureByFuture, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFromFutureToBankByFuture(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspFromFutureToBankByFuture, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQueryBankAccountMoneyByFuture(const dict &data, const dict &error, int reqid, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRspQueryBankAccountMoneyByFuture, data, error, reqid, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOpenAccountByBank(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnOpenAccountByBank, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCancelAccountByBank(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnCancelAccountByBank, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnChangeAccountByBank(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, FuturesTdApi, onRtnChangeAccountByBank, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

