void onDisconnect() override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onDisconnect);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onError(const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onError, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRiskNotify(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRiskNotify, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onLogin(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onLogin, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onTradeReport(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onTradeReport, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderStatus(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOrderStatus, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOrderRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCancelRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCancelRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOrderRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOrderRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryTradeRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryTradeRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryPositionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryPositionRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCashRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCashRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryJZJYAvailFundRsp(int avail_balance, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryJZJYAvailFundRsp, avail_balance, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onTransferFundInAndOutRsp(int transfer_value, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onTransferFundInAndOutRsp, transfer_value, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onTransferFundBetweenSecuidRsp(int transfer_value, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onTransferFundBetweenSecuidRsp, transfer_value, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryETFRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryETFRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryETFStockRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryETFStockRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryMaxOrderQtyRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryMaxOrderQtyRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIPOMaxPurchaseRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIPOMaxPurchaseRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIPOStockRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIPOStockRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIPODistributionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIPODistributionRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIPOLotteryRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIPOLotteryRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQuerySecurityBaseInfoRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQuerySecurityBaseInfoRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditMortgageInOutRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditMortgageInOutRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditStockBackRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditStockBackRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditPayBackRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditPayBackRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditPayBackByOrderRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditPayBackByOrderRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditStockRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditMortgageHoldRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditMortgageHoldRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditAssetsRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditAssetsRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditFinanceRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditFinanceRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditShortsellRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditShortsellRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditRepayAmountRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditRepayAmountRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditRepayStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditRepayStockRsp, data, error, request_id, last, pos_str);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditSecuritySellQtyRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditSecuritySellQtyRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQuerySecuidRightRsp(string market, int secuid_right, const dict &error, bool last, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQuerySecuidRightRsp, market, secuid_right, error, last, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryHKRateRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryHKRateRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryHKStockRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryHKStockRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryHKFundRsp(const dict &data, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryHKFundRsp, data, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryHKMinPriceUnitRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryHKMinPriceUnitRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryHKTradeCalendarRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryHKTradeCalendarRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryLockSecurityDetailRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryLockSecurityDetailRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onExtendLockSecurityRsp(int apply_sno, int apply_date, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onExtendLockSecurityRsp, apply_sno, apply_date, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryLockSecurityExtensionRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryLockSecurityExtensionRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCancelExtendLockSecurityRsp(int apply_date, string apply_sno, string cancel_sno, const dict &error, int request_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCancelExtendLockSecurityRsp, apply_date, apply_sno, cancel_sno, error, request_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryTransferFundHistoryRsp(const dict &data, const dict &error, int request_id, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryTransferFundHistoryRsp, data, error, request_id, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

