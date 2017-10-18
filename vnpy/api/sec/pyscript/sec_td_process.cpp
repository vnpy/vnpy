void TdApi::processFrontDisconnected(Task *task)
{
	PyLock lock;
	this->onFrontDisconnected();
	delete task;
};

void TdApi::processRtnNotice(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspNoticeField *task_data = (DFITCSECRspNoticeField*)task->task_data;
		data["noticeMsg"] = task_data->noticeMsg;
		delete task->task_data;
	}

	this->onRtnNotice(data);
	delete task;
};

void TdApi::processRspError(Task *task)
{
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspError(error);
	delete task;
};

void TdApi::processRspStockUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogin(data, error);
	delete task;
};

void TdApi::processRspStockUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogout(data, error);
	delete task;
};

void TdApi::processRspStockUserPasswordUpdate(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspPasswordUpdateField *task_data = (DFITCSECRspPasswordUpdateField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["passwordType"] = task_data->passwordType;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserPasswordUpdate(data, error);
	delete task;
};

void TdApi::processRspStockEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspEntrustOrderField *task_data = (DFITCStockRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["entrustMsg"] = task_data->entrustMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockEntrustOrder(data, error);
	delete task;
};

void TdApi::processRspStockWithdrawOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspWithdrawOrderField *task_data = (DFITCSECRspWithdrawOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["cancelMsg"] = task_data->cancelMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockWithdrawOrder(data, error);
	delete task;
};

void TdApi::processRspStockQryEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryEntrustOrderField *task_data = (DFITCStockRspQryEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["offerShareholderID"] = task_data->offerShareholderID;
		data["currency"] = task_data->currency;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustType"] = task_data->entrustType;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["entrustTime"] = task_data->entrustTime;
		data["declareTime"] = task_data->declareTime;
		data["declareResult"] = task_data->declareResult;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["accountID"] = task_data->accountID;
		data["noteMsg"] = task_data->noteMsg;
		data["withdrawQty"] = task_data->withdrawQty;
		data["declareOrderID"] = task_data->declareOrderID;
		data["orderType"] = task_data->orderType;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["freezeFundsSerialID"] = task_data->freezeFundsSerialID;
		data["freezeStockSerialID"] = task_data->freezeStockSerialID;
		data["declareDate"] = task_data->declareDate;
		data["declareSerialID"] = task_data->declareSerialID;
		data["entrustDate"] = task_data->entrustDate;
		data["incQryIndex"] = task_data->incQryIndex;
		data["ipAddr"] = task_data->ipAddr;
		data["macAddr"] = task_data->macAddr;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryEntrustOrder(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryRealTimeTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryRealTimeTradeField *task_data = (DFITCStockRspQryRealTimeTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustPrice"] = task_data->entrustPrice;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["currency"] = task_data->currency;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryRealTimeTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQrySerialTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQrySerialTradeField *task_data = (DFITCStockRspQrySerialTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["tradeID"] = task_data->tradeID;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["commission"] = task_data->commission;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["interestQuote"] = task_data->interestQuote;
		data["declareOrderID"] = task_data->declareOrderID;
		data["incQryIndex"] = task_data->incQryIndex;
		data["interest"] = task_data->interest;
		data["tradeTime"] = task_data->tradeTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQrySerialTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryPositionField *task_data = (DFITCStockRspQryPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["sellTurnover"] = task_data->sellTurnover;
		data["sellTradeQty"] = task_data->sellTradeQty;
		data["sellEntrustQty"] = task_data->sellEntrustQty;
		data["buyTurnover"] = task_data->buyTurnover;
		data["buyTradeQty"] = task_data->buyTradeQty;
		data["buyEntrustQty"] = task_data->buyEntrustQty;
		data["nonCirculateQty"] = task_data->nonCirculateQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["openDate"] = task_data->openDate;
		data["ableSellQty"] = task_data->ableSellQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["securityQty"] = task_data->securityQty;
		data["position"] = task_data->position;
		data["unSettleQty"] = task_data->unSettleQty;
		data["changeDate"] = task_data->changeDate;
		data["ablePurchaseQty"] = task_data->ablePurchaseQty;
		data["ableRedemptionQty"] = task_data->ableRedemptionQty;
		data["freezeQty"] = task_data->freezeQty;
		data["offsetSQty"] = task_data->offsetSQty;
		data["offsetBQty"] = task_data->offsetBQty;
		data["purchaseTradeQty"] = task_data->purchaseTradeQty;
		data["redemptionTradeQty"] = task_data->redemptionTradeQty;
		data["tradeUnit"] = task_data->tradeUnit;
		data["totalSellQty"] = task_data->totalSellQty;
		data["totalBuyQty"] = task_data->totalBuyQty;
		data["rationedSharesQty"] = task_data->rationedSharesQty;
		data["purchaseQty"] = task_data->purchaseQty;
		data["dilutedFloatProfitLoss"] = task_data->dilutedFloatProfitLoss;
		data["dilutedBreakevenPrice"] = task_data->dilutedBreakevenPrice;
		data["dilutedCost"] = task_data->dilutedCost;
		data["avgPositionPrice"] = task_data->avgPositionPrice;
		data["floatProfitLoss"] = task_data->floatProfitLoss;
		data["dividend"] = task_data->dividend;
		data["totalFloatProfitLoss"] = task_data->totalFloatProfitLoss;
		data["sellAmount"] = task_data->sellAmount;
		data["buyAmount"] = task_data->buyAmount;
		data["buyAvgPrice"] = task_data->buyAvgPrice;
		data["rationedSharesAmount"] = task_data->rationedSharesAmount;
		data["latestMarket"] = task_data->latestMarket;
		data["breakevenPrice"] = task_data->breakevenPrice;
		data["latestPrice"] = task_data->latestPrice;
		data["nonCirculateMarket"] = task_data->nonCirculateMarket;
		data["interestQuote"] = task_data->interestQuote;
		data["preClosePrice"] = task_data->preClosePrice;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryCapitalAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryCapitalAccountField *task_data = (DFITCStockRspQryCapitalAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["currency"] = task_data->currency;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["accountBalance"] = task_data->accountBalance;
		data["accountStatus"] = task_data->accountStatus;
		data["accountID"] = task_data->accountID;
		data["freezeFunds"] = task_data->freezeFunds;
		data["t2FreezeFunds"] = task_data->t2FreezeFunds;
		data["branchID"] = task_data->branchID;
		data["totalFunds"] = task_data->totalFunds;
		data["totalMarket"] = task_data->totalMarket;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryCapitalAccountInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryAccountField *task_data = (DFITCStockRspQryAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["tel"] = task_data->tel;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["accountIdentityID"] = task_data->accountIdentityID;
		data["accountIdentityType"] = task_data->accountIdentityType;
		data["branchID"] = task_data->branchID;
		data["branchType"] = task_data->branchType;
		data["mobile"] = task_data->mobile;
		data["entrustType"] = task_data->entrustType;
		data["accountStatus"] = task_data->accountStatus;
		data["pwdSynFlag"] = task_data->pwdSynFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryAccountInfo(data, error);
	delete task;
};

void TdApi::processRspStockQryShareholderInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryShareholderField *task_data = (DFITCStockRspQryShareholderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["account"] = task_data->account;
		data["shareholderID"] = task_data->shareholderID;
		data["shareholderSpecProp"] = task_data->shareholderSpecProp;
		data["tradePermissions"] = task_data->tradePermissions;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderStatus"] = task_data->shareholderStatus;
		data["mainAccountFlag"] = task_data->mainAccountFlag;
		data["shareholderCtlProp"] = task_data->shareholderCtlProp;
		data["branchID"] = task_data->branchID;
		data["shareholderType"] = task_data->shareholderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryShareholderInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockTransferFunds(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspTransferFundsField *task_data = (DFITCStockRspTransferFundsField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialID"] = task_data->serialID;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["fundsTransFlag"] = task_data->fundsTransFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockTransferFunds(data, error);
	delete task;
};

void TdApi::processRspStockEntrustBatchOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspEntrustBatchOrderField *task_data = (DFITCStockRspEntrustBatchOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["orderRangeID"] = task_data->orderRangeID;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["sucEntrustCount"] = task_data->sucEntrustCount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockEntrustBatchOrder(data, error);
	delete task;
};

void TdApi::processRspStockWithdrawBatchOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspWithdrawBatchOrderField *task_data = (DFITCStockRspWithdrawBatchOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockWithdrawBatchOrder(data, error);
	delete task;
};

void TdApi::processRspStockCalcAbleEntrustQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspCalcAbleEntrustQtyField *task_data = (DFITCStockRspCalcAbleEntrustQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["ableEntrustQty"] = task_data->ableEntrustQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockCalcAbleEntrustQty(data, error);
	delete task;
};

void TdApi::processRspStockCalcAblePurchaseETFQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspCalcAblePurchaseETFQtyField *task_data = (DFITCStockRspCalcAblePurchaseETFQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["ablePurchaseETFQty"] = task_data->ablePurchaseETFQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockCalcAblePurchaseETFQty(data, error);
	delete task;
};

void TdApi::processRspStockQryFreezeFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeFundsDetailField *task_data = (DFITCStockRspQryFreezeFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryFreezeFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryFreezeStockDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeStockDetailField *task_data = (DFITCStockRspQryFreezeStockDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stockFreezeType"] = task_data->stockFreezeType;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["accountName"] = task_data->accountName;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		data["operatorQty"] = task_data->operatorQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryFreezeStockDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryTransferStockDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTransferStockDetailField *task_data = (DFITCStockRspQryTransferStockDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		data["exchangeID"] = task_data->exchangeID;
		data["stockFreezeType"] = task_data->stockFreezeType;
		data["securityID"] = task_data->securityID;
		data["serialID"] = task_data->serialID;
		data["shareholderID"] = task_data->shareholderID;
		data["summaryMsg"] = task_data->summaryMsg;
		data["operatorTime"] = task_data->operatorTime;
		data["operatorQty"] = task_data->operatorQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryTransferStockDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryTransferFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTransferFundsDetailField *task_data = (DFITCStockRspQryTransferFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryTransferFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryStockInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryStockField *task_data = (DFITCStockRspQryStockField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stopFlag"] = task_data->stopFlag;
		data["latestPrice"] = task_data->latestPrice;
		data["preClosePrice"] = task_data->preClosePrice;
		data["openPrice"] = task_data->openPrice;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["priceHigher"] = task_data->priceHigher;
		data["priceLower"] = task_data->priceLower;
		data["bidPrice1"] = task_data->bidPrice1;
		data["bidQty1"] = task_data->bidQty1;
		data["askPrice1"] = task_data->askPrice1;
		data["askQty1"] = task_data->askQty1;
		data["bidPrice2"] = task_data->bidPrice2;
		data["bidQty2"] = task_data->bidQty2;
		data["askPrice2"] = task_data->askPrice2;
		data["askQty2"] = task_data->askQty2;
		data["bidPrice3"] = task_data->bidPrice3;
		data["bidQty3"] = task_data->bidQty3;
		data["askPrice3"] = task_data->askPrice3;
		data["askQty3"] = task_data->askQty3;
		data["bidPrice4"] = task_data->bidPrice4;
		data["bidQty4"] = task_data->bidQty4;
		data["askPrice4"] = task_data->askPrice4;
		data["askQty4"] = task_data->askQty4;
		data["bidPrice5"] = task_data->bidPrice5;
		data["bidQty5"] = task_data->bidQty5;
		data["askPrice5"] = task_data->askPrice5;
		data["askQty5"] = task_data->askQty5;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["interestQuote"] = task_data->interestQuote;
		data["securityFaceValue"] = task_data->securityFaceValue;
		data["bidTradeFlag"] = task_data->bidTradeFlag;
		data["tradeUnit"] = task_data->tradeUnit;
		data["businessLimit"] = task_data->businessLimit;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["upperLimitPrice"] = task_data->upperLimitPrice;
		data["lowerLimitPrice"] = task_data->lowerLimitPrice;
		data["currency"] = task_data->currency;
		data["orderLimits"] = task_data->orderLimits;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryStockInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryStockStaticInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryStockStaticField *task_data = (DFITCStockRspQryStockStaticField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stopFlag"] = task_data->stopFlag;
		data["preClosePrice"] = task_data->preClosePrice;
		data["openPrice"] = task_data->openPrice;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["interestQuote"] = task_data->interestQuote;
		data["securityFaceValue"] = task_data->securityFaceValue;
		data["bidTradeFlag"] = task_data->bidTradeFlag;
		data["tradeUnit"] = task_data->tradeUnit;
		data["businessLimit"] = task_data->businessLimit;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["upperLimitPrice"] = task_data->upperLimitPrice;
		data["lowerLimitPrice"] = task_data->lowerLimitPrice;
		data["currency"] = task_data->currency;
		data["orderLimits"] = task_data->orderLimits;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryStockStaticInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryTradeTime(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTradeTimeField *task_data = (DFITCStockRspQryTradeTimeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sysTradingDay"] = task_data->sysTradingDay;
		data["sysTime"] = task_data->sysTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryTradeTime(data, error);
	delete task;
};

void TdApi::processStockEntrustOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockEntrustOrderRtnField *task_data = (DFITCStockEntrustOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["entrustQty"] = task_data->entrustQty;
		data["orderConfirmFlag"] = task_data->orderConfirmFlag;
		data["entrustTime"] = task_data->entrustTime;
		data["entrustPrice"] = task_data->entrustPrice;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	this->onStockEntrustOrderRtn(data);
	delete task;
};

void TdApi::processStockTradeRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockTradeRtnField *task_data = (DFITCStockTradeRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["tradeID"] = task_data->tradeID;
		data["tradeTime"] = task_data->tradeTime;
		data["withdrawQty"] = task_data->withdrawQty;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["clearFunds"] = task_data->clearFunds;
		data["totalTradeQty"] = task_data->totalTradeQty;
		data["totalTurnover"] = task_data->totalTurnover;
		data["tradeQty"] = task_data->tradeQty;
		data["tradePrice"] = task_data->tradePrice;
		data["turnover"] = task_data->turnover;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onStockTradeRtn(data);
	delete task;
};

void TdApi::processStockWithdrawOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockWithdrawOrderRtnField *task_data = (DFITCStockWithdrawOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onStockWithdrawOrderRtn(data);
	delete task;
};

void TdApi::processRspSOPUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogin(data, error);
	delete task;
};

void TdApi::processRspSOPUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogout(data, error);
	delete task;
};

void TdApi::processRspSOPUserPasswordUpdate(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspPasswordUpdateField *task_data = (DFITCSECRspPasswordUpdateField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["passwordType"] = task_data->passwordType;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserPasswordUpdate(data, error);
	delete task;
};

void TdApi::processRspSOPEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspEntrustOrderField *task_data = (DFITCSOPRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPEntrustOrder(data, error);
	delete task;
};

void TdApi::processRspSOPGroupSplit(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspEntrustOrderField *task_data = (DFITCSOPRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPGroupSplit(data, error);
	delete task;
};

void TdApi::processRspSOPQryGroupPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryGroupPositionField *task_data = (DFITCSOPRspQryGroupPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["subAccountID"] = task_data->subAccountID;
		data["currency"] = task_data->currency;
		data["capitalID"] = task_data->capitalID;
		data["groupType"] = task_data->groupType;
		data["groupCode"] = task_data->groupCode;
		data["groupQty"] = task_data->groupQty;
		data["enableSplitQty"] = task_data->enableSplitQty;
		data["splitEntrustQty"] = task_data->splitEntrustQty;
		data["splitTradeQty"] = task_data->splitTradeQty;
		data["groupDeposit"] = task_data->groupDeposit;
		data["securityOptionID1"] = task_data->securityOptionID1;
		data["securityOptionID2"] = task_data->securityOptionID2;
		data["securityOptionID3"] = task_data->securityOptionID3;
		data["securityOptionID4"] = task_data->securityOptionID4;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryGroupPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPLockOUnLockStock(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspLockOUnLockStockField *task_data = (DFITCSOPRspLockOUnLockStockField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPLockOUnLockStock(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPWithdrawOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspWithdrawOrderField *task_data = (DFITCSECRspWithdrawOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["cancelMsg"] = task_data->cancelMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPWithdrawOrder(data, error);
	delete task;
};

void TdApi::processRspSOPQryEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryEntrustOrderField *task_data = (DFITCSOPRspQryEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["withdrawOrderID"] = task_data->withdrawOrderID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityOptionID"] = task_data->securityOptionID;
		data["optType"] = task_data->optType;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["coveredFlag"] = task_data->coveredFlag;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustDate"] = task_data->entrustDate;
		data["entrustTime"] = task_data->entrustTime;
		data["offerShareholderID"] = task_data->offerShareholderID;
		data["declareDate"] = task_data->declareDate;
		data["declareTime"] = task_data->declareTime;
		data["declareSerialID"] = task_data->declareSerialID;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["currency"] = task_data->currency;
		data["freezeFunds"] = task_data->freezeFunds;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustType"] = task_data->entrustType;
		data["macAddr"] = task_data->macAddr;
		data["ipAddr"] = task_data->ipAddr;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["orderType"] = task_data->orderType;
		data["incQryIndex"] = task_data->incQryIndex;
		data["capitalID"] = task_data->capitalID;
		data["orderExpiryDate"] = task_data->orderExpiryDate;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryEntrustOrder(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQrySerialTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQrySerialTradeField *task_data = (DFITCSOPRspQrySerialTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["securityID"] = task_data->securityID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["declareOrderID"] = task_data->declareOrderID;
		data["currency"] = task_data->currency;
		data["tradeID"] = task_data->tradeID;
		data["tradeTime"] = task_data->tradeTime;
		data["tradeQty"] = task_data->tradeQty;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["coveredFlag"] = task_data->coveredFlag;
		data["spdOrderID"] = task_data->spdOrderID;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["clearFunds"] = task_data->clearFunds;
		data["rotationTime"] = task_data->rotationTime;
		data["incQryIndex"] = task_data->incQryIndex;
		data["shareholderID"] = task_data->shareholderID;
		data["capitalID"] = task_data->capitalID;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQrySerialTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryPositionField *task_data = (DFITCSOPRspQryPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["subAccountID"] = task_data->subAccountID;
		data["securityOptionID"] = task_data->securityOptionID;
		data["contractID"] = task_data->contractID;
		data["contractName"] = task_data->contractName;
		data["entrustDirection"] = task_data->entrustDirection;
		data["coveredFlag"] = task_data->coveredFlag;
		data["executeDate"] = task_data->executeDate;
		data["totalQty"] = task_data->totalQty;
		data["availableQty"] = task_data->availableQty;
		data["latestPrice"] = task_data->latestPrice;
		data["optionMarket"] = task_data->optionMarket;
		data["freezeQty"] = task_data->freezeQty;
		data["executeQty"] = task_data->executeQty;
		data["openEntrustQty"] = task_data->openEntrustQty;
		data["openTradeQty"] = task_data->openTradeQty;
		data["prePosition"] = task_data->prePosition;
		data["closeEntrustQty"] = task_data->closeEntrustQty;
		data["closeTradeQty"] = task_data->closeTradeQty;
		data["deposit"] = task_data->deposit;
		data["openDeposit"] = task_data->openDeposit;
		data["closeDeposit"] = task_data->closeDeposit;
		data["exchangeDeposit"] = task_data->exchangeDeposit;
		data["exchangeOpenDeposit"] = task_data->exchangeOpenDeposit;
		data["exchangeCloseDeposit"] = task_data->exchangeCloseDeposit;
		data["openAvgPrice"] = task_data->openAvgPrice;
		data["optType"] = task_data->optType;
		data["contractObjectType"] = task_data->contractObjectType;
		data["contractUnit"] = task_data->contractUnit;
		data["currency"] = task_data->currency;
		data["totalTradeCost"] = task_data->totalTradeCost;
		data["tradeCost"] = task_data->tradeCost;
		data["realizeProfitLoss"] = task_data->realizeProfitLoss;
		data["profitLoss"] = task_data->profitLoss;
		data["adjustRemind"] = task_data->adjustRemind;
		data["expireRemind"] = task_data->expireRemind;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryCollateralPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryCollateralPositionField *task_data = (DFITCSOPRspQryCollateralPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["exchangeID"] = task_data->exchangeID;
		data["accountID"] = task_data->accountID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["availableQty"] = task_data->availableQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryCollateralPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryCapitalAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryCapitalAccountField *task_data = (DFITCSOPRspQryCapitalAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["branchID"] = task_data->branchID;
		data["currency"] = task_data->currency;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["freezeFunds"] = task_data->freezeFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["usedDeposit"] = task_data->usedDeposit;
		data["accountStatus"] = task_data->accountStatus;
		data["totalFunds"] = task_data->totalFunds;
		data["totalMarket"] = task_data->totalMarket;
		data["cashAssets"] = task_data->cashAssets;
		data["execGuaranteeRatio"] = task_data->execGuaranteeRatio;
		data["buyLimits"] = task_data->buyLimits;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryCapitalAccountInfo(data, error);
	delete task;
};

void TdApi::processRspSOPQryAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryAccountField *task_data = (DFITCSOPRspQryAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["accountFullName"] = task_data->accountFullName;
		data["branchID"] = task_data->branchID;
		data["identityType"] = task_data->identityType;
		data["accountIdentityID"] = task_data->accountIdentityID;
		data["tel"] = task_data->tel;
		data["mobile"] = task_data->mobile;
		data["accountType"] = task_data->accountType;
		data["accountProp"] = task_data->accountProp;
		data["tradePermissions"] = task_data->tradePermissions;
		data["entrustType"] = task_data->entrustType;
		data["accountStatus"] = task_data->accountStatus;
		data["pwdSynFlag"] = task_data->pwdSynFlag;
		data["accountNodeID"] = task_data->accountNodeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryAccountInfo(data, error);
	delete task;
};

void TdApi::processRspSOPQryShareholderInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryShareholderField *task_data = (DFITCSOPRspQryShareholderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["branchID"] = task_data->branchID;
		data["currency"] = task_data->currency;
		data["shareholderID"] = task_data->shareholderID;
		data["tradePermissions"] = task_data->tradePermissions;
		data["shareholderSpecProp"] = task_data->shareholderSpecProp;
		data["shareholderCtlProp"] = task_data->shareholderCtlProp;
		data["shareholderStatus"] = task_data->shareholderStatus;
		data["mainAccountFlag"] = task_data->mainAccountFlag;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryShareholderInfo(data, error);
	delete task;
};

void TdApi::processRspSOPCalcAbleEntrustQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspCalcAbleEntrustQtyField *task_data = (DFITCSOPRspCalcAbleEntrustQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityOptionID"] = task_data->securityOptionID;
		data["entrustQty"] = task_data->entrustQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPCalcAbleEntrustQty(data, error);
	delete task;
};

void TdApi::processRspSOPQryAbleLockStock(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryAbleLockStockField *task_data = (DFITCSOPRspQryAbleLockStockField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["securityQty"] = task_data->securityQty;
		data["position"] = task_data->position;
		data["avgPositionPrice"] = task_data->avgPositionPrice;
		data["dilutedCost"] = task_data->dilutedCost;
		data["breakevenPrice"] = task_data->breakevenPrice;
		data["dilutedBreakevenPrice"] = task_data->dilutedBreakevenPrice;
		data["ableSellQty"] = task_data->ableSellQty;
		data["latestMarket"] = task_data->latestMarket;
		data["latestPrice"] = task_data->latestPrice;
		data["floatProfitLoss"] = task_data->floatProfitLoss;
		data["dilutedFloatProfitLoss"] = task_data->dilutedFloatProfitLoss;
		data["tradeUnit"] = task_data->tradeUnit;
		data["openBuyQty"] = task_data->openBuyQty;
		data["openSellQty"] = task_data->openSellQty;
		data["buyUnSettleQty"] = task_data->buyUnSettleQty;
		data["sellUnSettleQty"] = task_data->sellUnSettleQty;
		data["openEntrustSellQty"] = task_data->openEntrustSellQty;
		data["ableLockQty"] = task_data->ableLockQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryAbleLockStock(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryContactInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryContactField *task_data = (DFITCSOPRspQryContactField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityOptionID"] = task_data->securityOptionID;
		data["contractID"] = task_data->contractID;
		data["contractName"] = task_data->contractName;
		data["securityID"] = task_data->securityID;
		data["contractObjectType"] = task_data->contractObjectType;
		data["execType"] = task_data->execType;
		data["deliType"] = task_data->deliType;
		data["optType"] = task_data->optType;
		data["contactUnit"] = task_data->contactUnit;
		data["latestPrice"] = task_data->latestPrice;
		data["beginTradingDay"] = task_data->beginTradingDay;
		data["endTradingDay"] = task_data->endTradingDay;
		data["execDate"] = task_data->execDate;
		data["endDate"] = task_data->endDate;
		data["positionUpLimit"] = task_data->positionUpLimit;
		data["priceUpLimit"] = task_data->priceUpLimit;
		data["priceDownLimit"] = task_data->priceDownLimit;
		data["priceHigher"] = task_data->priceHigher;
		data["priceLower"] = task_data->priceLower;
		data["entrustUpLimit"] = task_data->entrustUpLimit;
		data["entrustDownLimit"] = task_data->entrustDownLimit;
		data["entrustUpLimitMarketPri"] = task_data->entrustUpLimitMarketPri;
		data["entrustDownLimitMarketPri"] = task_data->entrustDownLimitMarketPri;
		data["openLimit"] = task_data->openLimit;
		data["stockTradeFlag"] = task_data->stockTradeFlag;
		data["depositUnit"] = task_data->depositUnit;
		data["depositRatioC"] = task_data->depositRatioC;
		data["depositRatioE"] = task_data->depositRatioE;
		data["preClosePrice"] = task_data->preClosePrice;
		data["closePrice"] = task_data->closePrice;
		data["preSettlePrice"] = task_data->preSettlePrice;
		data["openPrice"] = task_data->openPrice;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["settlePrice"] = task_data->settlePrice;
		data["endCashSettlePrice"] = task_data->endCashSettlePrice;
		data["handQty"] = task_data->handQty;
		data["unClosePositionQty"] = task_data->unClosePositionQty;
		data["approachExpireFlag"] = task_data->approachExpireFlag;
		data["tempAdjustFlag"] = task_data->tempAdjustFlag;
		data["stockListFlag"] = task_data->stockListFlag;
		data["execPrice"] = task_data->execPrice;
		data["bidPrice1"] = task_data->bidPrice1;
		data["bidQty1"] = task_data->bidQty1;
		data["bidPrice2"] = task_data->bidPrice2;
		data["bidQty2"] = task_data->bidQty2;
		data["bidPrice3"] = task_data->bidPrice3;
		data["bidQty3"] = task_data->bidQty3;
		data["bidPrice4"] = task_data->bidPrice4;
		data["bidQty4"] = task_data->bidQty4;
		data["bidPrice5"] = task_data->bidPrice5;
		data["bidQty5"] = task_data->bidQty5;
		data["askPrice1"] = task_data->askPrice1;
		data["askQty1"] = task_data->askQty1;
		data["askPrice2"] = task_data->askPrice2;
		data["askQty2"] = task_data->askQty2;
		data["askPrice3"] = task_data->askPrice3;
		data["askQty3"] = task_data->askQty3;
		data["askPrice4"] = task_data->askPrice4;
		data["askQty4"] = task_data->askQty4;
		data["askPrice5"] = task_data->askPrice5;
		data["askQty5"] = task_data->askQty5;
		data["optionIndex"] = task_data->optionIndex;
		data["miniPriceChange"] = task_data->miniPriceChange;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryContactInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPExectueOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspExectueOrderField *task_data = (DFITCSOPRspExectueOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPExectueOrder(data, error);
	delete task;
};

void TdApi::processRspSOPQryExecAssiInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryExecAssiInfoField *task_data = (DFITCSOPRspQryExecAssiInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["tradeDate"] = task_data->tradeDate;
		data["branchID"] = task_data->branchID;
		data["shareholderID"] = task_data->shareholderID;
		data["subAccountID"] = task_data->subAccountID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["optType"] = task_data->optType;
		data["contractObjectType"] = task_data->contractObjectType;
		data["coveredFlag"] = task_data->coveredFlag;
		data["securityOptionID"] = task_data->securityOptionID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["securityID"] = task_data->securityID;
		data["seatID"] = task_data->seatID;
		data["execPrice"] = task_data->execPrice;
		data["execQty"] = task_data->execQty;
		data["tradeQty"] = task_data->tradeQty;
		data["clearFunds"] = task_data->clearFunds;
		data["settleFunds"] = task_data->settleFunds;
		data["commission"] = task_data->commission;
		data["stampTax"] = task_data->stampTax;
		data["transferFee"] = task_data->transferFee;
		data["fee3"] = task_data->fee3;
		data["fee4"] = task_data->fee4;
		data["summaryMsg"] = task_data->summaryMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryExecAssiInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryTradeTime(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryTradeTimeField *task_data = (DFITCSOPRspQryTradeTimeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sysTradingDay"] = task_data->sysTradingDay;
		data["sysTime"] = task_data->sysTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryTradeTime(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryExchangeInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryExchangeInfoField *task_data = (DFITCSOPRspQryExchangeInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["exchangeID"] = task_data->exchangeID;
		data["exchangeName"] = task_data->exchangeName;
		data["callauctionBegining"] = task_data->callauctionBegining;
		data["callauctionEnding"] = task_data->callauctionEnding;
		data["morningOpening"] = task_data->morningOpening;
		data["morningClosing"] = task_data->morningClosing;
		data["afternoonOpening"] = task_data->afternoonOpening;
		data["afternoonClosing"] = task_data->afternoonClosing;
		data["execOpening"] = task_data->execOpening;
		data["execClosing"] = task_data->execClosing;
		data["nightTradeFlag"] = task_data->nightTradeFlag;
		data["nightOpening"] = task_data->nightOpening;
		data["nightClosing"] = task_data->nightClosing;
		data["stockTradeStatus"] = task_data->stockTradeStatus;
		data["currency"] = task_data->currency;
		data["tradingDayFlag"] = task_data->tradingDayFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryExchangeInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryCommission(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryCommissionField *task_data = (DFITCSOPRspQryCommissionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["refType"] = task_data->refType;
		data["contractObjectType"] = task_data->contractObjectType;
		data["securityID"] = task_data->securityID;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["entrustDirection"] = task_data->entrustDirection;
		data["level"] = task_data->level;
		data["costRatio1"] = task_data->costRatio1;
		data["unitCost1"] = task_data->unitCost1;
		data["costUpLimit1"] = task_data->costUpLimit1;
		data["costDonwLimit1"] = task_data->costDonwLimit1;
		data["costRatio2"] = task_data->costRatio2;
		data["unitCost2"] = task_data->unitCost2;
		data["costUpLimit2"] = task_data->costUpLimit2;
		data["costDonwLimit2"] = task_data->costDonwLimit2;
		data["costRatio3"] = task_data->costRatio3;
		data["unitCost3"] = task_data->unitCost3;
		data["costRatio4"] = task_data->costRatio4;
		data["unitCost4"] = task_data->unitCost4;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryCommission(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryDeposit(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryDepositField *task_data = (DFITCSOPRspQryDepositField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["refType"] = task_data->refType;
		data["securityObjectType"] = task_data->securityObjectType;
		data["securityID"] = task_data->securityID;
		data["depositRateC"] = task_data->depositRateC;
		data["depositRateE"] = task_data->depositRateE;
		data["depositUnit"] = task_data->depositUnit;
		data["calcType"] = task_data->calcType;
		data["level"] = task_data->level;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryDeposit(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryContractObjectInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryContractObjectField *task_data = (DFITCSOPRspQryContractObjectField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityName"] = task_data->securityName;
		data["securityID"] = task_data->securityID;
		data["contractObjectType"] = task_data->contractObjectType;
		data["contractObjectStatus"] = task_data->contractObjectStatus;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryContractObjectInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processSOPEntrustOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPEntrustOrderRtnField *task_data = (DFITCSOPEntrustOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["branchID"] = task_data->branchID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["currency"] = task_data->currency;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustTime"] = task_data->entrustTime;
		data["coveredFlag"] = task_data->coveredFlag;
		data["orderType"] = task_data->orderType;
		data["orderExpiryDate"] = task_data->orderExpiryDate;
		data["orderCategory"] = task_data->orderCategory;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	this->onSOPEntrustOrderRtn(data);
	delete task;
};

void TdApi::processSOPTradeRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPTradeRtnField *task_data = (DFITCSOPTradeRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["currency"] = task_data->currency;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["coveredFlag"] = task_data->coveredFlag;
		data["orderCategory"] = task_data->orderCategory;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeQty"] = task_data->tradeQty;
		data["tradeID"] = task_data->tradeID;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		data["tradeTime"] = task_data->tradeTime;
		delete task->task_data;
	}

	this->onSOPTradeRtn(data);
	delete task;
};

void TdApi::processSOPWithdrawOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPWithdrawOrderRtnField *task_data = (DFITCSOPWithdrawOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["currency"] = task_data->currency;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["wdUnFreezeFunds"] = task_data->wdUnFreezeFunds;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	this->onSOPWithdrawOrderRtn(data);
	delete task;
};

void TdApi::processRspFASLUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogin(data, error);
	delete task;
};

void TdApi::processRspFASLUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogout(data, error);
	delete task;
};

void TdApi::processRspFASLQryAbleFinInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspAbleFinInfoField *task_data = (DFITCFASLRspAbleFinInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["accountBanlance"] = task_data->accountBanlance;
		data["ableFinFunds"] = task_data->ableFinFunds;
		data["turnover"] = task_data->turnover;
		data["entrustFreezeFunds"] = task_data->entrustFreezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryAbleFinInfo(data, error);
	delete task;
};

void TdApi::processRspFASLQryAbleSloInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspAbleSloInfoField *task_data = (DFITCFASLRspAbleSloInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		data["ableSloQty"] = task_data->ableSloQty;
		data["securityName"] = task_data->securityName;
		data["entrustQty"] = task_data->entrustQty;
		data["tradeQty"] = task_data->tradeQty;
		data["status"] = task_data->status;
		data["sloDepositRatio"] = task_data->sloDepositRatio;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryAbleSloInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLTransferCollateral(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspTransferCollateralField *task_data = (DFITCFASLRspTransferCollateralField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["localOrderID"] = task_data->localOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLTransferCollateral(data, error);
	delete task;
};

void TdApi::processRspFASLDirectRepayment(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspDirectRepaymentField *task_data = (DFITCFASLRspDirectRepaymentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["realRepayFunds"] = task_data->realRepayFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLDirectRepayment(data, error);
	delete task;
};

void TdApi::processRspFASLRepayStockTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspRepayStockTransferField *task_data = (DFITCFASLRspRepayStockTransferField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["localOrderID"] = task_data->localOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLRepayStockTransfer(data, error);
	delete task;
};

void TdApi::processRspFASLEntrustCrdtOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspEntrustCrdtOrderField *task_data = (DFITCFASLRspEntrustCrdtOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["localOrderID"] = task_data->localOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLEntrustCrdtOrder(data, error);
	delete task;
};

void TdApi::processRspFASLEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspEntrustOrderField *task_data = (DFITCFASLRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLEntrustOrder(data, error);
	delete task;
};

void TdApi::processRspFASLCalcAbleEntrustCrdtQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspCalcAbleEntrustCrdtQtyField *task_data = (DFITCFASLRspCalcAbleEntrustCrdtQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["totalRepayQty"] = task_data->totalRepayQty;
		data["entrustQty"] = task_data->entrustQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLCalcAbleEntrustCrdtQty(data, error);
	delete task;
};

void TdApi::processRspFASLQryCrdtFunds(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryCrdtFundsField *task_data = (DFITCFASLRspQryCrdtFundsField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["availableDeposit"] = task_data->availableDeposit;
		data["maintGuaranteeRatio"] = task_data->maintGuaranteeRatio;
		data["antiMaintGuaranteeRatio"] = task_data->antiMaintGuaranteeRatio;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["clearFunds"] = task_data->clearFunds;
		data["stockMarket"] = task_data->stockMarket;
		data["guaranteeStockSubMarket"] = task_data->guaranteeStockSubMarket;
		data["guaranteeStockMarket"] = task_data->guaranteeStockMarket;
		data["tradeFinLiabilities"] = task_data->tradeFinLiabilities;
		data["tradeSloLiabilities"] = task_data->tradeSloLiabilities;
		data["orderFinLiabilities"] = task_data->orderFinLiabilities;
		data["orderSloLiabilities"] = task_data->orderSloLiabilities;
		data["sloOrderRepay"] = task_data->sloOrderRepay;
		data["fundsBalance"] = task_data->fundsBalance;
		data["closeFunds"] = task_data->closeFunds;
		data["activeCloseFunds"] = task_data->activeCloseFunds;
		data["ableWithdrawalAssetsStand"] = task_data->ableWithdrawalAssetsStand;
		data["withdrawalFunds"] = task_data->withdrawalFunds;
		data["totalAssets"] = task_data->totalAssets;
		data["unTransferStockMarket"] = task_data->unTransferStockMarket;
		data["totalLiabilities"] = task_data->totalLiabilities;
		data["netAssets"] = task_data->netAssets;
		data["sellRepayFunds"] = task_data->sellRepayFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["finProfitLoss"] = task_data->finProfitLoss;
		data["sloProfitLoss"] = task_data->sloProfitLoss;
		data["sloFunds"] = task_data->sloFunds;
		data["finCost"] = task_data->finCost;
		data["sloCost"] = task_data->sloCost;
		data["finCurMarket"] = task_data->finCurMarket;
		data["finUsedDeposit"] = task_data->finUsedDeposit;
		data["sloUsedDeposit"] = task_data->sloUsedDeposit;
		data["finAntiInterest"] = task_data->finAntiInterest;
		data["sloAntiInterest"] = task_data->sloAntiInterest;
		data["shGuaranteeStockMarket"] = task_data->shGuaranteeStockMarket;
		data["szGuaranteeStockMarket"] = task_data->szGuaranteeStockMarket;
		data["finFloatProfit"] = task_data->finFloatProfit;
		data["finFloatLoss"] = task_data->finFloatLoss;
		data["sloFloatProfit"] = task_data->sloFloatProfit;
		data["sloFloatLoss"] = task_data->sloFloatLoss;
		data["finRatio"] = task_data->finRatio;
		data["sloRatio"] = task_data->sloRatio;
		data["contractEndDate"] = task_data->contractEndDate;
		data["finUsedLimits"] = task_data->finUsedLimits;
		data["sloUsedLimits"] = task_data->sloUsedLimits;
		data["finCreditLimits"] = task_data->finCreditLimits;
		data["sloCreditLimits"] = task_data->sloCreditLimits;
		data["ableBuyCollateralFunds"] = task_data->ableBuyCollateralFunds;
		data["ableRepayFunds"] = task_data->ableRepayFunds;
		data["sloAvailableFunds"] = task_data->sloAvailableFunds;
		data["cashAssets"] = task_data->cashAssets;
		data["totalStockMarket"] = task_data->totalStockMarket;
		data["finContractFunds"] = task_data->finContractFunds;
		data["contractObjectMarket"] = task_data->contractObjectMarket;
		data["otherCharges"] = task_data->otherCharges;
		data["sloCurMarket"] = task_data->sloCurMarket;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCrdtFunds(data, error);
	delete task;
};

void TdApi::processRspFASLQryCrdtContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryCrdtContractField *task_data = (DFITCFASLRspQryCrdtContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["conSerialNO"] = task_data->conSerialNO;
		data["contractNO"] = task_data->contractNO;
		data["operatorDate"] = task_data->operatorDate;
		data["endDate"] = task_data->endDate;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["currency"] = task_data->currency;
		data["finQty"] = task_data->finQty;
		data["finFunds"] = task_data->finFunds;
		data["sloQty"] = task_data->sloQty;
		data["sloFunds"] = task_data->sloFunds;
		data["finEntrustQty"] = task_data->finEntrustQty;
		data["finEntrustFunds"] = task_data->finEntrustFunds;
		data["sloEntrustQty"] = task_data->sloEntrustQty;
		data["sloEntrustFunds"] = task_data->sloEntrustFunds;
		data["finTradeQty"] = task_data->finTradeQty;
		data["finTradeFunds"] = task_data->finTradeFunds;
		data["sloTradeQty"] = task_data->sloTradeQty;
		data["sloTradeFunds"] = task_data->sloTradeFunds;
		data["debtPrincipal"] = task_data->debtPrincipal;
		data["repayFunds"] = task_data->repayFunds;
		data["debtQty"] = task_data->debtQty;
		data["repayQty"] = task_data->repayQty;
		data["sellStockRepayFunds"] = task_data->sellStockRepayFunds;
		data["buyStockForRepayEntrustQty//当日买券还券委托数量"] = task_data->buyStockForRepayEntrustQty//当日买券还券委托数量;
		data["buyStockForRepayTradeQty"] = task_data->buyStockForRepayTradeQty;
		data["finCost"] = task_data->finCost;
		data["sloCost"] = task_data->sloCost;
		data["totalInterest"] = task_data->totalInterest;
		data["repaidInterest"] = task_data->repaidInterest;
		data["crdtConStatus"] = task_data->crdtConStatus;
		data["leftInterest"] = task_data->leftInterest;
		data["sloLeftFunds"] = task_data->sloLeftFunds;
		data["buyStockFreezeFunds"] = task_data->buyStockFreezeFunds;
		data["buyStockClearFunds"] = task_data->buyStockClearFunds;
		data["sloLeftAvaiFunds"] = task_data->sloLeftAvaiFunds;
		data["debtQtyEntrustMarket"] = task_data->debtQtyEntrustMarket;
		data["debtQtyTradeMarket"] = task_data->debtQtyTradeMarket;
		data["debtFundsMarket"] = task_data->debtFundsMarket;
		data["finProfitLoss"] = task_data->finProfitLoss;
		data["sloProfitLoss"] = task_data->sloProfitLoss;
		data["entrustQty"] = task_data->entrustQty;
		data["conOpenQty"] = task_data->conOpenQty;
		data["conOpenFunds"] = task_data->conOpenFunds;
		data["conOpenCost"] = task_data->conOpenCost;
		data["conInitQty"] = task_data->conInitQty;
		data["conInitFunds"] = task_data->conInitFunds;
		data["conInitCost"] = task_data->conInitCost;
		data["unRepayConFunds"] = task_data->unRepayConFunds;
		data["unRepayConQty"] = task_data->unRepayConQty;
		data["unRepayConCost"] = task_data->unRepayConCost;
		data["positionNO"] = task_data->positionNO;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCrdtContract(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryCrdtConChangeInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryCrdtConChangeInfoField *task_data = (DFITCFASLRspQryCrdtConChangeInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialNO"] = task_data->serialNO;
		data["conChangeNO"] = task_data->conChangeNO;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityID"] = task_data->securityID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["operatorQty"] = task_data->operatorQty;
		data["operatorDate"] = task_data->operatorDate;
		data["clearFlag"] = task_data->clearFlag;
		data["commission"] = task_data->commission;
		data["operatorFunds2"] = task_data->operatorFunds2;
		data["postFunds"] = task_data->postFunds;
		data["postQty"] = task_data->postQty;
		data["exchangeID"] = task_data->exchangeID;
		data["operatorCost"] = task_data->operatorCost;
		data["postCost"] = task_data->postCost;
		data["operatorInterest"] = task_data->operatorInterest;
		data["postInterest"] = task_data->postInterest;
		data["changeNote"] = task_data->changeNote;
		data["shareholderID"] = task_data->shareholderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCrdtConChangeInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLTransferFunds(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspTransferFundsField *task_data = (DFITCStockRspTransferFundsField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialID"] = task_data->serialID;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["fundsTransFlag"] = task_data->fundsTransFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLTransferFunds(data, error);
	delete task;
};

void TdApi::processRspFASLQryAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryAccountField *task_data = (DFITCStockRspQryAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["tel"] = task_data->tel;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["accountIdentityID"] = task_data->accountIdentityID;
		data["accountIdentityType"] = task_data->accountIdentityType;
		data["branchID"] = task_data->branchID;
		data["branchType"] = task_data->branchType;
		data["mobile"] = task_data->mobile;
		data["entrustType"] = task_data->entrustType;
		data["accountStatus"] = task_data->accountStatus;
		data["pwdSynFlag"] = task_data->pwdSynFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryAccountInfo(data, error);
	delete task;
};

void TdApi::processRspFASLQryCapitalAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryCapitalAccountField *task_data = (DFITCStockRspQryCapitalAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["currency"] = task_data->currency;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["accountBalance"] = task_data->accountBalance;
		data["accountStatus"] = task_data->accountStatus;
		data["accountID"] = task_data->accountID;
		data["freezeFunds"] = task_data->freezeFunds;
		data["t2FreezeFunds"] = task_data->t2FreezeFunds;
		data["branchID"] = task_data->branchID;
		data["totalFunds"] = task_data->totalFunds;
		data["totalMarket"] = task_data->totalMarket;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCapitalAccountInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryShareholderInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryShareholderField *task_data = (DFITCStockRspQryShareholderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["account"] = task_data->account;
		data["shareholderID"] = task_data->shareholderID;
		data["shareholderSpecProp"] = task_data->shareholderSpecProp;
		data["tradePermissions"] = task_data->tradePermissions;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderStatus"] = task_data->shareholderStatus;
		data["mainAccountFlag"] = task_data->mainAccountFlag;
		data["shareholderCtlProp"] = task_data->shareholderCtlProp;
		data["branchID"] = task_data->branchID;
		data["shareholderType"] = task_data->shareholderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryShareholderInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryPositionField *task_data = (DFITCStockRspQryPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["sellTurnover"] = task_data->sellTurnover;
		data["sellTradeQty"] = task_data->sellTradeQty;
		data["sellEntrustQty"] = task_data->sellEntrustQty;
		data["buyTurnover"] = task_data->buyTurnover;
		data["buyTradeQty"] = task_data->buyTradeQty;
		data["buyEntrustQty"] = task_data->buyEntrustQty;
		data["nonCirculateQty"] = task_data->nonCirculateQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["openDate"] = task_data->openDate;
		data["ableSellQty"] = task_data->ableSellQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["securityQty"] = task_data->securityQty;
		data["position"] = task_data->position;
		data["unSettleQty"] = task_data->unSettleQty;
		data["changeDate"] = task_data->changeDate;
		data["ablePurchaseQty"] = task_data->ablePurchaseQty;
		data["ableRedemptionQty"] = task_data->ableRedemptionQty;
		data["freezeQty"] = task_data->freezeQty;
		data["offsetSQty"] = task_data->offsetSQty;
		data["offsetBQty"] = task_data->offsetBQty;
		data["purchaseTradeQty"] = task_data->purchaseTradeQty;
		data["redemptionTradeQty"] = task_data->redemptionTradeQty;
		data["tradeUnit"] = task_data->tradeUnit;
		data["totalSellQty"] = task_data->totalSellQty;
		data["totalBuyQty"] = task_data->totalBuyQty;
		data["rationedSharesQty"] = task_data->rationedSharesQty;
		data["purchaseQty"] = task_data->purchaseQty;
		data["dilutedFloatProfitLoss"] = task_data->dilutedFloatProfitLoss;
		data["dilutedBreakevenPrice"] = task_data->dilutedBreakevenPrice;
		data["dilutedCost"] = task_data->dilutedCost;
		data["avgPositionPrice"] = task_data->avgPositionPrice;
		data["floatProfitLoss"] = task_data->floatProfitLoss;
		data["dividend"] = task_data->dividend;
		data["totalFloatProfitLoss"] = task_data->totalFloatProfitLoss;
		data["sellAmount"] = task_data->sellAmount;
		data["buyAmount"] = task_data->buyAmount;
		data["buyAvgPrice"] = task_data->buyAvgPrice;
		data["rationedSharesAmount"] = task_data->rationedSharesAmount;
		data["latestMarket"] = task_data->latestMarket;
		data["breakevenPrice"] = task_data->breakevenPrice;
		data["latestPrice"] = task_data->latestPrice;
		data["nonCirculateMarket"] = task_data->nonCirculateMarket;
		data["interestQuote"] = task_data->interestQuote;
		data["preClosePrice"] = task_data->preClosePrice;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryEntrustOrderField *task_data = (DFITCStockRspQryEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["offerShareholderID"] = task_data->offerShareholderID;
		data["currency"] = task_data->currency;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustType"] = task_data->entrustType;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["entrustTime"] = task_data->entrustTime;
		data["declareTime"] = task_data->declareTime;
		data["declareResult"] = task_data->declareResult;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["accountID"] = task_data->accountID;
		data["noteMsg"] = task_data->noteMsg;
		data["withdrawQty"] = task_data->withdrawQty;
		data["declareOrderID"] = task_data->declareOrderID;
		data["orderType"] = task_data->orderType;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["freezeFundsSerialID"] = task_data->freezeFundsSerialID;
		data["freezeStockSerialID"] = task_data->freezeStockSerialID;
		data["declareDate"] = task_data->declareDate;
		data["declareSerialID"] = task_data->declareSerialID;
		data["entrustDate"] = task_data->entrustDate;
		data["incQryIndex"] = task_data->incQryIndex;
		data["ipAddr"] = task_data->ipAddr;
		data["macAddr"] = task_data->macAddr;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryEntrustOrder(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQrySerialTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQrySerialTradeField *task_data = (DFITCStockRspQrySerialTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["tradeID"] = task_data->tradeID;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["commission"] = task_data->commission;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["interestQuote"] = task_data->interestQuote;
		data["declareOrderID"] = task_data->declareOrderID;
		data["incQryIndex"] = task_data->incQryIndex;
		data["interest"] = task_data->interest;
		data["tradeTime"] = task_data->tradeTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQrySerialTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryRealTimeTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryRealTimeTradeField *task_data = (DFITCStockRspQryRealTimeTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustPrice"] = task_data->entrustPrice;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["currency"] = task_data->currency;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryRealTimeTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryFreezeFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeFundsDetailField *task_data = (DFITCStockRspQryFreezeFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryFreezeFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryFreezeStockDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeStockDetailField *task_data = (DFITCStockRspQryFreezeStockDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stockFreezeType"] = task_data->stockFreezeType;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["accountName"] = task_data->accountName;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		data["operatorQty"] = task_data->operatorQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryFreezeStockDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryTransferFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTransferFundsDetailField *task_data = (DFITCStockRspQryTransferFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryTransferFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLWithdrawOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspWithdrawOrderField *task_data = (DFITCFASLRspWithdrawOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLWithdrawOrder(data, error);
	delete task;
};

void TdApi::processRspFASLQrySystemTime(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryTradeTimeField *task_data = (DFITCFASLRspQryTradeTimeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sysTradingDay"] = task_data->sysTradingDay;
		data["sysTime"] = task_data->sysTime;
		data["sysWeek"] = task_data->sysWeek;
		data["sysMillisecond"] = task_data->sysMillisecond;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQrySystemTime(data, error);
	delete task;
};

void TdApi::processRspFASLQryTransferredContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryTransferredContractField *task_data = (DFITCFASLRspQryTransferredContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["capitalID"] = task_data->capitalID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		data["ableSellQty"] = task_data->ableSellQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryTransferredContract(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLDesirableFundsOut(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspDesirableFundsOutField *task_data = (DFITCFASLRspDesirableFundsOutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialID"] = task_data->serialID;
		data["accountBanlance"] = task_data->accountBanlance;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLDesirableFundsOut(data, error);
	delete task;
};

void TdApi::processRspFASLQryGuaranteedContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryGuaranteedContractField *task_data = (DFITCFASLRspQryGuaranteedContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["exchangRate"] = task_data->exchangRate;
		data["status"] = task_data->status;
		data["accountType"] = task_data->accountType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryGuaranteedContract(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryUnderlyingContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryUnderlyingContractField *task_data = (DFITCFASLRspQryUnderlyingContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["financeDepositRatio"] = task_data->financeDepositRatio;
		data["securityDepositRatio"] = task_data->securityDepositRatio;
		data["status"] = task_data->status;
		data["accountType"] = task_data->accountType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryUnderlyingContract(data, error, task->task_last);
	delete task;
};

void TdApi::processFASLEntrustOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockEntrustOrderRtnField *task_data = (DFITCStockEntrustOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["entrustQty"] = task_data->entrustQty;
		data["orderConfirmFlag"] = task_data->orderConfirmFlag;
		data["entrustTime"] = task_data->entrustTime;
		data["entrustPrice"] = task_data->entrustPrice;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	this->onFASLEntrustOrderRtn(data);
	delete task;
};

void TdApi::processFASLTradeRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockTradeRtnField *task_data = (DFITCStockTradeRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["tradeID"] = task_data->tradeID;
		data["tradeTime"] = task_data->tradeTime;
		data["withdrawQty"] = task_data->withdrawQty;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["clearFunds"] = task_data->clearFunds;
		data["totalTradeQty"] = task_data->totalTradeQty;
		data["totalTurnover"] = task_data->totalTurnover;
		data["tradeQty"] = task_data->tradeQty;
		data["tradePrice"] = task_data->tradePrice;
		data["turnover"] = task_data->turnover;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onFASLTradeRtn(data);
	delete task;
};

void TdApi::processFASLWithdrawOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockWithdrawOrderRtnField *task_data = (DFITCStockWithdrawOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onFASLWithdrawOrderRtn(data);
	delete task;
};

