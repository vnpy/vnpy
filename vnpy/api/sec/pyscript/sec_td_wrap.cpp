virtual void onFrontDisconnected()
{
	try
	{
		this->get_override("onFrontDisconnected")();
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnNotice(dict data)
{
	try
	{
		this->get_override("onRtnNotice")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspError(dict error)
{
	try
	{
		this->get_override("onRspError")(error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockUserLogin(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockUserLogin")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockUserLogout(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockUserLogout")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockUserPasswordUpdate(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockUserPasswordUpdate")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockEntrustOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockEntrustOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockWithdrawOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockWithdrawOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryEntrustOrder(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryEntrustOrder")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryRealTimeTrade(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryRealTimeTrade")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQrySerialTrade(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQrySerialTrade")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryPosition(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryPosition")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryCapitalAccountInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryCapitalAccountInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryAccountInfo(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockQryAccountInfo")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryShareholderInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryShareholderInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockTransferFunds(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockTransferFunds")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockEntrustBatchOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockEntrustBatchOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockWithdrawBatchOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockWithdrawBatchOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockCalcAbleEntrustQty(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockCalcAbleEntrustQty")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockCalcAblePurchaseETFQty(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockCalcAblePurchaseETFQty")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryFreezeFundsDetail(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryFreezeFundsDetail")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryFreezeStockDetail(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryFreezeStockDetail")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryTransferStockDetail(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryTransferStockDetail")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryTransferFundsDetail(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryTransferFundsDetail")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryStockInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryStockInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryStockStaticInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspStockQryStockStaticInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockQryTradeTime(dict data, dict error)
{
	try
	{
		this->get_override("onRspStockQryTradeTime")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onStockEntrustOrderRtn(dict data)
{
	try
	{
		this->get_override("onStockEntrustOrderRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onStockTradeRtn(dict data)
{
	try
	{
		this->get_override("onStockTradeRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onStockWithdrawOrderRtn(dict data)
{
	try
	{
		this->get_override("onStockWithdrawOrderRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPUserLogin(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPUserLogin")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPUserLogout(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPUserLogout")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPUserPasswordUpdate(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPUserPasswordUpdate")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPEntrustOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPEntrustOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPGroupSplit(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPGroupSplit")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryGroupPosition(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryGroupPosition")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPLockOUnLockStock(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPLockOUnLockStock")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPWithdrawOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPWithdrawOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryEntrustOrder(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryEntrustOrder")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQrySerialTrade(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQrySerialTrade")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryPosition(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryPosition")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryCollateralPosition(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryCollateralPosition")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryCapitalAccountInfo(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPQryCapitalAccountInfo")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryAccountInfo(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPQryAccountInfo")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryShareholderInfo(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPQryShareholderInfo")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPCalcAbleEntrustQty(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPCalcAbleEntrustQty")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryAbleLockStock(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryAbleLockStock")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryContactInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryContactInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPExectueOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspSOPExectueOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryExecAssiInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryExecAssiInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryTradeTime(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryTradeTime")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryExchangeInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryExchangeInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryCommission(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryCommission")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryDeposit(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryDeposit")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPQryContractObjectInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspSOPQryContractObjectInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onSOPEntrustOrderRtn(dict data)
{
	try
	{
		this->get_override("onSOPEntrustOrderRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onSOPTradeRtn(dict data)
{
	try
	{
		this->get_override("onSOPTradeRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onSOPWithdrawOrderRtn(dict data)
{
	try
	{
		this->get_override("onSOPWithdrawOrderRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLUserLogin(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLUserLogin")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLUserLogout(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLUserLogout")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryAbleFinInfo(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLQryAbleFinInfo")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryAbleSloInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryAbleSloInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLTransferCollateral(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLTransferCollateral")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLDirectRepayment(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLDirectRepayment")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLRepayStockTransfer(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLRepayStockTransfer")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLEntrustCrdtOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLEntrustCrdtOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLEntrustOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLEntrustOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLCalcAbleEntrustCrdtQty(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLCalcAbleEntrustCrdtQty")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryCrdtFunds(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLQryCrdtFunds")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryCrdtContract(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryCrdtContract")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryCrdtConChangeInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryCrdtConChangeInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLTransferFunds(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLTransferFunds")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryAccountInfo(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLQryAccountInfo")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryCapitalAccountInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryCapitalAccountInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryShareholderInfo(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryShareholderInfo")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryPosition(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryPosition")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryEntrustOrder(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryEntrustOrder")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQrySerialTrade(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQrySerialTrade")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryRealTimeTrade(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryRealTimeTrade")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryFreezeFundsDetail(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryFreezeFundsDetail")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryFreezeStockDetail(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryFreezeStockDetail")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryTransferFundsDetail(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryTransferFundsDetail")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLWithdrawOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLWithdrawOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQrySystemTime(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLQrySystemTime")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryTransferredContract(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryTransferredContract")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLDesirableFundsOut(dict data, dict error)
{
	try
	{
		this->get_override("onRspFASLDesirableFundsOut")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryGuaranteedContract(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryGuaranteedContract")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLQryUnderlyingContract(dict data, dict error, bool flag)
{
	try
	{
		this->get_override("onRspFASLQryUnderlyingContract")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onFASLEntrustOrderRtn(dict data)
{
	try
	{
		this->get_override("onFASLEntrustOrderRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onFASLTradeRtn(dict data)
{
	try
	{
		this->get_override("onFASLTradeRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onFASLWithdrawOrderRtn(dict data)
{
	try
	{
		this->get_override("onFASLWithdrawOrderRtn")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

