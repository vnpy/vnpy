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

void onRtnNotice(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnNotice, data);
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

void onRspStockUserLogin(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockUserLogin, data, error);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspStockUserLogout, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockUserPasswordUpdate(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockUserPasswordUpdate, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockEntrustOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockEntrustOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockWithdrawOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockWithdrawOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryEntrustOrder(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryEntrustOrder, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryRealTimeTrade(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryRealTimeTrade, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQrySerialTrade(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQrySerialTrade, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryPosition(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryPosition, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryCapitalAccountInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryCapitalAccountInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryAccountInfo(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryAccountInfo, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryShareholderInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryShareholderInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockTransferFunds(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockTransferFunds, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockEntrustBatchOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockEntrustBatchOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockWithdrawBatchOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockWithdrawBatchOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockCalcAbleEntrustQty(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockCalcAbleEntrustQty, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockCalcAblePurchaseETFQty(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockCalcAblePurchaseETFQty, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryFreezeFundsDetail(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryFreezeFundsDetail, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryFreezeStockDetail(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryFreezeStockDetail, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryTransferStockDetail(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryTransferStockDetail, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryTransferFundsDetail(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryTransferFundsDetail, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryStockInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryStockInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryStockStaticInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryStockStaticInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspStockQryTradeTime(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspStockQryTradeTime, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onStockEntrustOrderRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onStockEntrustOrderRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onStockTradeRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onStockTradeRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onStockWithdrawOrderRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onStockWithdrawOrderRtn, data);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPUserLogin, data, error);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPUserLogout, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPUserPasswordUpdate(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPUserPasswordUpdate, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPEntrustOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPEntrustOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQuoteEntrustOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQuoteEntrustOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPGroupSplit(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPGroupSplit, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPGroupExectueOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPGroupExectueOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryGroupPosition(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryGroupPosition, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPLockOUnLockStock(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPLockOUnLockStock, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPWithdrawOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPWithdrawOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryEntrustOrder(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryEntrustOrder, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQrySerialTrade(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQrySerialTrade, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryPosition(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryPosition, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryCollateralPosition(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryCollateralPosition, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryCapitalAccountInfo(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryCapitalAccountInfo, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryAccountInfo(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryAccountInfo, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryShareholderInfo(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryShareholderInfo, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPCalcAbleEntrustQty(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPCalcAbleEntrustQty, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryAbleLockStock(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryAbleLockStock, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryContactInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryContactInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPExectueOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPExectueOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryExecAssiInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryExecAssiInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryTradeTime(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryTradeTime, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryExchangeInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryExchangeInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryCommission(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryCommission, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryDeposit(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryDeposit, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSOPQryContractObjectInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSOPQryContractObjectInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSOPEntrustOrderRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onSOPEntrustOrderRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSOPTradeRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onSOPTradeRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSOPWithdrawOrderRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onSOPWithdrawOrderRtn, data);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLUserLogin, data, error);
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
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLUserLogout, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryAbleFinInfo(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryAbleFinInfo, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryAbleSloInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryAbleSloInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLTransferCollateral(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLTransferCollateral, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLDirectRepayment(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLDirectRepayment, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLRepayStockTransfer(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLRepayStockTransfer, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLEntrustCrdtOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLEntrustCrdtOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLEntrustOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLEntrustOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLCalcAbleEntrustCrdtQty(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLCalcAbleEntrustCrdtQty, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryCrdtFunds(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryCrdtFunds, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryCrdtContract(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryCrdtContract, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryCrdtConChangeInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryCrdtConChangeInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLTransferFunds(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLTransferFunds, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryAccountInfo(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryAccountInfo, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryCapitalAccountInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryCapitalAccountInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryShareholderInfo(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryShareholderInfo, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryPosition(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryPosition, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryEntrustOrder(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryEntrustOrder, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQrySerialTrade(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQrySerialTrade, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryRealTimeTrade(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryRealTimeTrade, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryFreezeFundsDetail(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryFreezeFundsDetail, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryFreezeStockDetail(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryFreezeStockDetail, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryTransferFundsDetail(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryTransferFundsDetail, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLWithdrawOrder(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLWithdrawOrder, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQrySystemTime(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQrySystemTime, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryTransferredContract(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryTransferredContract, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLDesirableFundsOut(const dict &data, const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLDesirableFundsOut, data, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryGuaranteedContract(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryGuaranteedContract, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFASLQryUnderlyingContract(const dict &data, const dict &error, bool last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFASLQryUnderlyingContract, data, error, last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onFASLEntrustOrderRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFASLEntrustOrderRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onFASLTradeRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFASLTradeRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onFASLWithdrawOrderRtn(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFASLWithdrawOrderRtn, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

