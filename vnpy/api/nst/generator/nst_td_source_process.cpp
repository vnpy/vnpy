void TdApi::processFrontConnected(Task *task)
{
	this->onFrontConnected();
};

void TdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspUserLoginField *task_data = (CUftRspUserLoginField*)task->task_data;
		data["MaxOrderRef"] = getIntValue(task_data->MaxOrderRef);
		data["TradeDate"] = task_data->TradeDate;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspInfoField *task_error = (CUftRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogin(data, error);
};

void TdApi::processAnsOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsOrderInsertField *task_data = (CUftAnsOrderInsertField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["ProcessTime"] = task_data->ProcessTime;
		data["TotalTime"] = task_data->TotalTime;
		data["ExchangeTime"] = task_data->ExchangeTime;
		data["SenderID"] = task_data->SenderID;
		data["LocalTimeDelay"] = task_data->LocalTimeDelay;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["Direction"] = task_data->Direction;
		data["EntrustType"] = task_data->EntrustType;
		data["Price"] = task_data->Price;
		data["Amount"] = getIntValue(task_data->Amount);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onAnsOrderInsert(data, error);
};

void TdApi::processRspOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspnOrderInsertField *task_data = (CUftRspnOrderInsertField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["ProcessTime"] = task_data->ProcessTime;
		data["TotalTime"] = task_data->TotalTime;
		data["ExchangeTime"] = task_data->ExchangeTime;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["OrderStatus"] = task_data->OrderStatus;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onRspOrderInsert(data, error);
};

void TdApi::processAnsOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsOrderActionField *task_data = (CUftAnsOrderActionField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["SenderID"] = task_data->SenderID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onAnsOrderAction(data, error);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspnOrderActionField *task_data = (CUftRspnOrderActionField*)task->task_data;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onRspOrderAction(data, error);
};

void TdApi::processOrderRtn(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRtnnOrderField *task_data = (CUftRtnnOrderField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["ProcessTime"] = task_data->ProcessTime;
		data["TotalTime"] = task_data->TotalTime;
		data["ExchangeTime"] = task_data->ExchangeTime;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["VolumeTotal"] = task_data->VolumeTotal;
		data["OrderStatus"] = task_data->OrderStatus;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["EntrustType"] = task_data->EntrustType;
		data["Direction"] = task_data->Direction;
		data["Price"] = task_data->Price;
		data["Amount"] = getIntValue(task_data->Amount);
		delete task_data;
	}
	this->onOrderRtn(data);
};

void TdApi::processTradeRtn(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRtnnTradeField *task_data = (CUftRtnnTradeField*)task->task_data;
		data["BusinessPrice"] = task_data->BusinessPrice;
		data["BusinessTime"] = getIntValue(task_data->BusinessTime);
		data["BusinessAmount"] = getIntValue(task_data->BusinessAmount);
		data["fare"] = task_data->fare;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["BusinessId"] = toUtf(task_data->BusinessId);
		data["OrderSysID"] = task_data->OrderSysID;
		data["session_id"] = task_data->session_id;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["reserve"] = toUtf(task_data->reserve);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["StockCode"] = toUtf(task_data->StockCode);
		delete task_data;
	}
	this->onTradeRtn(data);
};

void TdApi::processRspTradingAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryFundField *task_data = (CUftAnsQueryFundField*)task->task_data;
		data["EnabledBalance"] = task_data->EnabledBalance;
		data["Deposit"] = task_data->Deposit;
		data["BeginBalance"] = task_data->BeginBalance;
		data["Margin"] = task_data->Margin;
		data["Profit"] = task_data->Profit;
		data["TotalFare"] = task_data->TotalFare;
		data["CurrBalance"] = task_data->CurrBalance;
		data["floating_gain_loss"] = task_data->floating_gain_loss;
		data["FrozenBalance"] = task_data->FrozenBalance;
		data["SenderID"] = task_data->SenderID;
		data["EnablePurQuota"] = task_data->EnablePurQuota;
		delete task_data;
	}
	this->onRspTradingAccount(data);
};

void TdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onRspError(error);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryOrderField *task_data = (CUftAnsQueryOrderField*)task->task_data;
		data["Order"] = task_data->Order;
		data["OrderRef"] = task_data->OrderRef;
		data["MaginCheck"] = task_data->MaginCheck;
		data["VolumeTotal"] = getIntValue(task_data->VolumeTotal);
		data["OrderStatus"] = task_data->OrderStatus;
		data["session_id"] = task_data->session_id;
		data["reserve"] = task_data->reserve;
		data["OrderTime"] = getIntValue(task_data->OrderTime);
		data["SenderID"] = task_data->SenderID;
		data["ErrorID"] = getIntValue(task_data->ErrorID);
		data["OrderIndex"] = task_data->OrderIndex;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["Direction"] = task_data->Direction;
		data["EntrustType"] = task_data->EntrustType;
		data["CashMargin"] = task_data->CashMargin;
		data["TGWNo"] = task_data->TGWNo;
		data["Price"] = task_data->Price;
		data["Amount"] = task_data->Amount;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["ClOrdID"] = toUtf(task_data->ClOrdID);
		delete task_data;
	}
	this->onRspQryOrder(data, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryTradeField *task_data = (CUftAnsQueryTradeField*)task->task_data;
		data["BusinessPrice"] = task_data->BusinessPrice;
		data["BusinessTime"] = getIntValue(task_data->BusinessTime);
		data["BusinessAmount"] = getIntValue(task_data->BusinessAmount);
		data["fare"] = task_data->fare;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["BusinessId"] = toUtf(task_data->BusinessId);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["session_id"] = task_data->session_id;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["StockCode"] = toUtf(task_data->StockCode);
		delete task_data;
	}
	this->onRspQryTrade(data, task->task_last);
};

void TdApi::processRspQryInvestorPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryPositionField *task_data = (CUftAnsQueryPositionField*)task->task_data;
		data["futu_code"] = toUtf(task_data->futu_code);
		data["entrust_bs"] = task_data->entrust_bs;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["reserve"] = toUtf(task_data->reserve);
		data["OldEnableAmount"] = getIntValue(task_data->OldEnableAmount);
		data["OldCurrentAmount"] = getIntValue(task_data->OldCurrentAmount);
		data["TodayEnableAmount"] = getIntValue(task_data->TodayEnableAmount);
		data["TodayCurrentAmount"] = getIntValue(task_data->TodayCurrentAmount);
		data["OldOpenBalance"] = task_data->OldOpenBalance;
		data["TodayOpenBalance"] = task_data->TodayOpenBalance;
		data["HoldMargin"] = task_data->HoldMargin;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["EnableAmount"] = task_data->EnableAmount;
		data["CurrentAmount"] = task_data->CurrentAmount;
		delete task_data;
	}
	this->onRspQryInvestorPosition(data, task->task_last);
};

void TdApi::processRspQryChangePwd(Task *task)
{
	this->onRspQryChangePwd();
};

void TdApi::processRspLogout(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspLogout(task->task_data);
};

void TdApi::processRtnInstrumentStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRtnInstrumentStatusField *task_data = (CUftRtnInstrumentStatusField*)task->task_data;
		data["SettlementGroupID"] = toUtf(task_data->SettlementGroupID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Status"] = task_data->Status;
		data["TradingSegmentSN"] = task_data->TradingSegmentSN;
		data["EnterTime"] = toUtf(task_data->EnterTime);
		data["EnterReason"] = task_data->EnterReason;
		data["PlatformID"] = task_data->PlatformID;
		data["PlatformState"] = task_data->PlatformState;
		delete task_data;
	}
	this->onRtnInstrumentStatus(data);
};

void TdApi::processRspTest(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspTest *task_data = (CUftRspTest*)task->task_data;
		data["TimeDelay"] = getIntValue(task_data->TimeDelay);
		delete task_data;
	}
	this->onRspTest(data);
};

void TdApi::processErrRtnOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onErrRtnOrderInsert(error);
};

void TdApi::processErrRtnOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onErrRtnOrderAction(error);
};

