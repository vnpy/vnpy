void onConnected(const dict &data, const dict &data, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onConnected, data, data, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDisconnected(const dict &data, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onDisconnected, data, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onBusinessReject(const dict &error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onBusinessReject, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderInsert(const dict &error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOrderInsert, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderReport(const dict &error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOrderReport, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onTradeReport(const dict &error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onTradeReport, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCashAssetVariation(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCashAssetVariation, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onStockHoldingVariation(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onStockHoldingVariation, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOptionHoldingVariation(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOptionHoldingVariation, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOptionUnderlyingHoldingVariation(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOptionUnderlyingHoldingVariation, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSettlementConfirmedRpt(const dict &error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onSettlementConfirmedRpt, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onFundTrsfReject(const dict &error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFundTrsfReject, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onFundTrsfReport(const dict &error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFundTrsfReport, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onMarketState(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onMarketState, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onNotifyReport(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onNotifyReport, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onReportSynchronizationRsp(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onReportSynchronizationRsp, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOrder(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOrder, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryTrade(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryTrade, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCashAsset(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCashAsset, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryStkHolding(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryStkHolding, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryLotWinning(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryLotWinning, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCustInfo(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCustInfo, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryInvAcct(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryInvAcct, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCommissionRate(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCommissionRate, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryFundTransferSerial(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryFundTransferSerial, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIssue(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIssue, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryStock(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryStock, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryEtf(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryEtf, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryEtfComponent(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryEtfComponent, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryMarketState(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryMarketState, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOption(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOption, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptHolding(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptHolding, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptUnderlyingHolding(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptUnderlyingHolding, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptPositionLimit(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptPositionLimit, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptPurchaseLimit(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptPurchaseLimit, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptExerciseAssign(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptExerciseAssign, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryNotifyInfo(const dict &data, const dict &error, int reqid) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryNotifyInfo, data, error, reqid);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

