void TdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void TdApi::processRspAuthenticate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspAuthenticateField *task_data = (CHSRspAuthenticateField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["AppID"] = toUtf(task_data->AppID);
		data["AuthCode"] = toUtf(task_data->AuthCode);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspAuthenticate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspUserLoginField *task_data = (CHSRspUserLoginField*)task->task_data;
		data["BranchID"] = task_data->BranchID;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["UserName"] = toUtf(task_data->UserName);
		data["TradingDay"] = task_data->TradingDay;
		data["PreTradingDay"] = task_data->PreTradingDay;
		data["BillConfirmFlag"] = task_data->BillConfirmFlag;
		data["SessionID"] = task_data->SessionID;
		data["UserApplicationType"] = task_data->UserApplicationType;
		data["UserApplicationInfo"] = toUtf(task_data->UserApplicationInfo);
		data["RiskLevel"] = toUtf(task_data->RiskLevel);
		data["LastMacAddress"] = toUtf(task_data->LastMacAddress);
		data["LastIPAddress"] = toUtf(task_data->LastIPAddress);
		data["LastLoginTime"] = task_data->LastLoginTime;
		data["CZCETime"] = task_data->CZCETime;
		data["DCETime"] = task_data->DCETime;
		data["SHFETime"] = task_data->SHFETime;
		data["CFFEXTime"] = task_data->CFFEXTime;
		data["INETime"] = task_data->INETime;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserPasswordUpdate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspUserPasswordUpdateField *task_data = (CHSRspUserPasswordUpdateField*)task->task_data;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserPasswordUpdate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspOrderInsertField *task_data = (CHSRspOrderInsertField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["OrderCommand"] = toUtf(task_data->OrderCommand);
		data["InsertTime"] = task_data->InsertTime;
		data["MinVolume"] = task_data->MinVolume;
		data["SpringPrice"] = task_data->SpringPrice;
		data["SwapOrderFlag"] = task_data->SwapOrderFlag;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspErrorOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspOrderActionField *task_data = (CHSRspOrderActionField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["OrderStatus"] = task_data->OrderStatus;
		data["InsertTime"] = task_data->InsertTime;
		data["OrderActionRef"] = toUtf(task_data->OrderActionRef);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorExerciseOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspExerciseOrderInsertField *task_data = (CHSRspExerciseOrderInsertField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["SessionID"] = task_data->SessionID;
		data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
		data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["OrderVolume"] = task_data->OrderVolume;
		data["ExerciseType"] = task_data->ExerciseType;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderStatus"] = task_data->OrderStatus;
		data["InsertTime"] = task_data->InsertTime;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspErrorExerciseOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspExerciseOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspExerciseOrderActionField *task_data = (CHSRspExerciseOrderActionField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
		data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
		data["SessionID"] = task_data->SessionID;
		data["OrderStatus"] = task_data->OrderStatus;
		data["ExecOrderActionRef"] = toUtf(task_data->ExecOrderActionRef);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspExerciseOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorLockInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspLockInsertField *task_data = (CHSRspLockInsertField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["LockOrderSysID"] = toUtf(task_data->LockOrderSysID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["LockType"] = task_data->LockType;
		data["OrderVolume"] = task_data->OrderVolume;
		data["UnderlyingAccountID"] = toUtf(task_data->UnderlyingAccountID);
		data["OrderStatus"] = task_data->OrderStatus;
		data["InsertTime"] = task_data->InsertTime;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspErrorLockInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspForQuoteInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspForQuoteInsertField *task_data = (CHSRspForQuoteInsertField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["OrderStatus"] = task_data->OrderStatus;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspForQuoteInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspErrorCombActionInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspCombActionInsertField *task_data = (CHSRspCombActionInsertField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["CombOrderSysID"] = toUtf(task_data->CombOrderSysID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
		data["CombPositionID"] = toUtf(task_data->CombPositionID);
		data["CombDirection"] = task_data->CombDirection;
		data["OrderVolume"] = task_data->OrderVolume;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderStatus"] = task_data->OrderStatus;
		data["InsertTime"] = task_data->InsertTime;
		data["Direction"] = task_data->Direction;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspErrorCombActionInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryMaxOrderVolume(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQueryMaxOrderVolumeField *task_data = (CHSRspQueryMaxOrderVolumeField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["MaxOrderVolume"] = task_data->MaxOrderVolume;
		data["MaxOrderVolumeUnit"] = task_data->MaxOrderVolumeUnit;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["OrderCommand"] = toUtf(task_data->OrderCommand);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderPrice"] = task_data->OrderPrice;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQueryMaxOrderVolume(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryLockVolume(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQueryLockVolumeField *task_data = (CHSRspQueryLockVolumeField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["LockType"] = task_data->LockType;
		data["AvailablePositionVolume"] = task_data->AvailablePositionVolume;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQueryLockVolume(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryExerciseVolume(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQueryExerciseVolumeField *task_data = (CHSRspQueryExerciseVolumeField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["MaxOrderVolumeUnit"] = task_data->MaxOrderVolumeUnit;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQueryExerciseVolume(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryPositionField *task_data = (CHSRspQryPositionField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["HedgeType"] = task_data->HedgeType;
		data["YdPositionVolume"] = task_data->YdPositionVolume;
		data["PositionVolume"] = task_data->PositionVolume;
		data["TodayPositionVolume"] = task_data->TodayPositionVolume;
		data["AvailablePositionVolume"] = task_data->AvailablePositionVolume;
		data["TodayAvailablePositionVolume"] = task_data->TodayAvailablePositionVolume;
		data["PositionMargin"] = task_data->PositionMargin;
		data["Premium"] = task_data->Premium;
		data["Commission"] = task_data->Commission;
		data["OpenFrozenVolume"] = task_data->OpenFrozenVolume;
		data["CloseFrozenVolume"] = task_data->CloseFrozenVolume;
		data["CombVolume"] = task_data->CombVolume;
		data["ExerciseFrozenVolume"] = task_data->ExerciseFrozenVolume;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["ExerciseFrozenMargin"] = task_data->ExerciseFrozenMargin;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["FrozenCommission"] = task_data->FrozenCommission;
		data["OpenVolume"] = task_data->OpenVolume;
		data["CloseVolume"] = task_data->CloseVolume;
		data["OpenBalance"] = task_data->OpenBalance;
		data["CloseBalance"] = task_data->CloseBalance;
		data["OpenCost"] = task_data->OpenCost;
		data["PositionCost"] = task_data->PositionCost;
		data["PositionProfit"] = task_data->PositionProfit;
		data["CloseProfit"] = task_data->CloseProfit;
		data["OptionsMarketValue"] = task_data->OptionsMarketValue;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTradingAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryTradingAccountField *task_data = (CHSRspQryTradingAccountField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["YdBalance"] = task_data->YdBalance;
		data["YdPositionMargin"] = task_data->YdPositionMargin;
		data["YdFundEquity"] = task_data->YdFundEquity;
		data["FundEquity"] = task_data->FundEquity;
		data["OptionsMarketValue"] = task_data->OptionsMarketValue;
		data["Equity"] = task_data->Equity;
		data["AvailableBalance"] = task_data->AvailableBalance;
		data["WithdrawBalance"] = task_data->WithdrawBalance;
		data["Margin"] = task_data->Margin;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["ExerciseFrozenMargin"] = task_data->ExerciseFrozenMargin;
		data["RiskDegree"] = task_data->RiskDegree;
		data["Premium"] = task_data->Premium;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["Commission"] = task_data->Commission;
		data["FrozenCommission"] = task_data->FrozenCommission;
		data["CloseProfit"] = task_data->CloseProfit;
		data["PositionProfit"] = task_data->PositionProfit;
		data["CloseProfitByDate"] = task_data->CloseProfitByDate;
		data["PositionProfitByDate"] = task_data->PositionProfitByDate;
		data["Deposit"] = task_data->Deposit;
		data["Withdraw"] = task_data->Withdraw;
		data["FundMortgage"] = task_data->FundMortgage;
		data["WarrantMortgage"] = task_data->WarrantMortgage;
		data["FrozenBalance"] = task_data->FrozenBalance;
		data["UnFrozenBalance"] = task_data->UnFrozenBalance;
		data["CurrencyID"] = task_data->CurrencyID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTradingAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSOrderField *task_data = (CHSOrderField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["TradeVolume"] = task_data->TradeVolume;
		data["CancelVolume"] = task_data->CancelVolume;
		data["TradePrice"] = task_data->TradePrice;
		data["TradingDay"] = task_data->TradingDay;
		data["InsertDate"] = task_data->InsertDate;
		data["InsertTime"] = task_data->InsertTime;
		data["ReportTime"] = task_data->ReportTime;
		data["OrderCommand"] = toUtf(task_data->OrderCommand);
		data["MinVolume"] = task_data->MinVolume;
		data["SpringPrice"] = task_data->SpringPrice;
		data["SwapOrderFlag"] = task_data->SwapOrderFlag;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["OrderSource"] = task_data->OrderSource;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSTradeField *task_data = (CHSTradeField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeType"] = task_data->HedgeType;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradePrice"] = task_data->TradePrice;
		data["TradingDay"] = task_data->TradingDay;
		data["TradeTime"] = task_data->TradeTime;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSExerciseField *task_data = (CHSExerciseField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
		data["SessionID"] = task_data->SessionID;
		data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["HedgeType"] = task_data->HedgeType;
		data["ExerciseType"] = task_data->ExerciseType;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["InsertDate"] = task_data->InsertDate;
		data["InsertTime"] = task_data->InsertTime;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["OrderSource"] = task_data->OrderSource;
		data["CloseFlag"] = task_data->CloseFlag;
		data["OffsetFlag"] = task_data->OffsetFlag;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryExercise(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryLock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSLockField *task_data = (CHSLockField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["LockOrderSysID"] = toUtf(task_data->LockOrderSysID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["LockType"] = task_data->LockType;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["TradingDay"] = task_data->TradingDay;
		data["InsertTime"] = task_data->InsertTime;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["OrderSource"] = task_data->OrderSource;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryLock(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSCombActionField *task_data = (CHSCombActionField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["CombOrderSysID"] = toUtf(task_data->CombOrderSysID);
		data["CombPositionID"] = toUtf(task_data->CombPositionID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
		data["Direction"] = task_data->Direction;
		data["CombDirection"] = task_data->CombDirection;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["TradingDay"] = task_data->TradingDay;
		data["InsertDate"] = task_data->InsertDate;
		data["InsertTime"] = task_data->InsertTime;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["OrderSource"] = task_data->OrderSource;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryCombAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryPositionCombineDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryPositionCombineDetailField *task_data = (CHSRspQryPositionCombineDetailField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["CombPositionID"] = toUtf(task_data->CombPositionID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
		data["HedgeType"] = task_data->HedgeType;
		data["Direction"] = task_data->Direction;
		data["YdPositionVolume"] = task_data->YdPositionVolume;
		data["AvailablePositionVolume"] = task_data->AvailablePositionVolume;
		data["TotalCombVolume"] = task_data->TotalCombVolume;
		data["TotalSplitVolume"] = task_data->TotalSplitVolume;
		data["PositionMargin"] = task_data->PositionMargin;
		data["OpenDate"] = task_data->OpenDate;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryPositionCombineDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInstrument(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryInstrumentField *task_data = (CHSRspQryInstrumentField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentName"] = toUtf(task_data->InstrumentName);
		data["InstrumentEngName"] = toUtf(task_data->InstrumentEngName);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["ProductType"] = task_data->ProductType;
		data["MaxMarketOrderVolume"] = task_data->MaxMarketOrderVolume;
		data["MinMarketOrderVolume"] = task_data->MinMarketOrderVolume;
		data["MaxLimitOrderVolume"] = task_data->MaxLimitOrderVolume;
		data["MinLimitOrderVolume"] = task_data->MinLimitOrderVolume;
		data["VolumeMultiple"] = task_data->VolumeMultiple;
		data["PriceTick"] = task_data->PriceTick;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["ExercisePrice"] = task_data->ExercisePrice;
		data["OptionsType"] = task_data->OptionsType;
		data["TradingFlag"] = task_data->TradingFlag;
		data["MarketDate"] = task_data->MarketDate;
		data["ExpireDate"] = task_data->ExpireDate;
		data["BeginExerciseDate"] = task_data->BeginExerciseDate;
		data["EndExerciseDate"] = task_data->EndExerciseDate;
		data["BeginDeliveryDate"] = task_data->BeginDeliveryDate;
		data["EndDeliveryDate"] = task_data->EndDeliveryDate;
		data["CurrencyID"] = task_data->CurrencyID;
		data["CombType"] = task_data->CombType;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryInstrument(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCoveredShort(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryCoveredShortField *task_data = (CHSRspQryCoveredShortField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["CoveredLockVolume"] = task_data->CoveredLockVolume;
		data["CoveredShortVolume"] = task_data->CoveredShortVolume;
		data["CoveredEstimateShortVolume"] = task_data->CoveredEstimateShortVolume;
		data["MsgContent"] = toUtf(task_data->MsgContent);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryCoveredShort(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExerciseAssign(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryExerciseAssignField *task_data = (CHSRspQryExerciseAssignField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["PositionType"] = task_data->PositionType;
		data["OptionsType"] = task_data->OptionsType;
		data["ExercisePrice"] = task_data->ExercisePrice;
		data["ExerciseVolume"] = task_data->ExerciseVolume;
		data["DeliveryVolume"] = task_data->DeliveryVolume;
		data["ExerciseFrozenBalance"] = task_data->ExerciseFrozenBalance;
		data["SettlementBalance"] = task_data->SettlementBalance;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryExerciseAssign(data, error, task->task_id, task->task_last);
};

void TdApi::processRspTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspTransferField *task_data = (CHSRspTransferField*)task->task_data;
		data["TransferSerialID"] = task_data->TransferSerialID;
		data["BankID"] = toUtf(task_data->BankID);
		data["TransferType"] = task_data->TransferType;
		data["OccurBalance"] = task_data->OccurBalance;
		data["CurrencyID"] = task_data->CurrencyID;
		data["TransferOccasion"] = toUtf(task_data->TransferOccasion);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspTransfer(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryTransferField *task_data = (CHSRspQryTransferField*)task->task_data;
		data["TransferSerialID"] = task_data->TransferSerialID;
		data["BankID"] = toUtf(task_data->BankID);
		data["BankName"] = toUtf(task_data->BankName);
		data["BusinessName"] = toUtf(task_data->BusinessName);
		data["OccurBalance"] = task_data->OccurBalance;
		data["PostBalance"] = task_data->PostBalance;
		data["TransferTime"] = task_data->TransferTime;
		data["TransferStatus"] = task_data->TransferStatus;
		data["TransferSource"] = task_data->TransferSource;
		data["Remarks"] = toUtf(task_data->Remarks);
		data["CurrencyID"] = task_data->CurrencyID;
		data["OrderSourceDate"] = task_data->OrderSourceDate;
		data["TradingDay"] = task_data->TradingDay;
		data["TransferOccasion"] = toUtf(task_data->TransferOccasion);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTransfer(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryBankBalance(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQueryBankBalanceField *task_data = (CHSRspQueryBankBalanceField*)task->task_data;
		data["TransferSerialID"] = task_data->TransferSerialID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQueryBankBalance(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryBankAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQueryBankAccountField *task_data = (CHSRspQueryBankAccountField*)task->task_data;
		data["BankID"] = toUtf(task_data->BankID);
		data["BankName"] = toUtf(task_data->BankName);
		data["BankAccountID"] = toUtf(task_data->BankAccountID);
		data["CurrencyID"] = task_data->CurrencyID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQueryBankAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQueryBillContent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQueryBillContentField *task_data = (CHSRspQueryBillContentField*)task->task_data;
		data["BillContent"] = toUtf(task_data->BillContent);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQueryBillContent(data, error, task->task_id, task->task_last);
};

void TdApi::processRspBillConfirm(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspBillConfirmField *task_data = (CHSRspBillConfirmField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["BillConfirmStatus"] = task_data->BillConfirmStatus;
		data["ConfirmDate"] = task_data->ConfirmDate;
		data["ConfirmTime"] = task_data->ConfirmTime;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspBillConfirm(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryMargin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryMarginField *task_data = (CHSRspQryMarginField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["HedgeType"] = task_data->HedgeType;
		data["LongMarginRatio"] = task_data->LongMarginRatio;
		data["LongMargin"] = task_data->LongMargin;
		data["ShortMarginRatio"] = task_data->ShortMarginRatio;
		data["ShortMargin"] = task_data->ShortMargin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryMargin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCommission(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryCommissionField *task_data = (CHSRspQryCommissionField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ProductType"] = task_data->ProductType;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["LongOpenCommissionRatio"] = task_data->LongOpenCommissionRatio;
		data["LongOpenCommission"] = task_data->LongOpenCommission;
		data["LongCloseCommissionRatio"] = task_data->LongCloseCommissionRatio;
		data["LongCloseCommission"] = task_data->LongCloseCommission;
		data["LongCloseTodayCommissionRatio"] = task_data->LongCloseTodayCommissionRatio;
		data["LongCloseTodayCommission"] = task_data->LongCloseTodayCommission;
		data["ShortOpenCommissionRatio"] = task_data->ShortOpenCommissionRatio;
		data["ShortOpenCommission"] = task_data->ShortOpenCommission;
		data["ShortCloseCommissionRatio"] = task_data->ShortCloseCommissionRatio;
		data["ShortCloseCommission"] = task_data->ShortCloseCommission;
		data["ShortCloseTodayCommissionRatio"] = task_data->ShortCloseTodayCommissionRatio;
		data["ShortCloseTodayCommission"] = task_data->ShortCloseTodayCommission;
		data["ExerciseCommissionRatio"] = task_data->ExerciseCommissionRatio;
		data["ExerciseCommission"] = task_data->ExerciseCommission;
		data["TradeValueRatio"] = task_data->TradeValueRatio;
		data["StockValue"] = task_data->StockValue;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryCommission(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryPositionDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryPositionDetailField *task_data = (CHSRspQryPositionDetailField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["OpenDate"] = task_data->OpenDate;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["HedgeType"] = task_data->HedgeType;
		data["TradeVolume"] = task_data->TradeVolume;
		data["PositionPrice"] = task_data->PositionPrice;
		data["TodayCloseVolume"] = task_data->TodayCloseVolume;
		data["ArbitragePositionID"] = toUtf(task_data->ArbitragePositionID);
		data["LegID"] = task_data->LegID;
		data["TradeType"] = task_data->TradeType;
		data["PositionMargin"] = task_data->PositionMargin;
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryPositionDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExchangeRate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQryExchangeRateField *task_data = (CHSRspQryExchangeRateField*)task->task_data;
		data["FromCurrencyID"] = task_data->FromCurrencyID;
		data["ToCurrencyID"] = task_data->ToCurrencyID;
		data["ExchangeRate"] = task_data->ExchangeRate;
		data["FromCurrencyUnit"] = task_data->FromCurrencyUnit;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryExchangeRate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQrySysConfig(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSRspQrySysConfigField *task_data = (CHSRspQrySysConfigField*)task->task_data;
		data["ConfigNo"] = task_data->ConfigNo;
		data["ConfigValue"] = toUtf(task_data->ConfigValue);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQrySysConfig(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryDepthMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSDepthMarketDataField *task_data = (CHSDepthMarketDataField*)task->task_data;
		data["TradingDay"] = task_data->TradingDay;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["LastPrice"] = task_data->LastPrice;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["PreClosePrice"] = task_data->PreClosePrice;
		data["OpenPrice"] = task_data->OpenPrice;
		data["HighestPrice"] = task_data->HighestPrice;
		data["LowestPrice"] = task_data->LowestPrice;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradeBalance"] = task_data->TradeBalance;
		data["OpenInterest"] = task_data->OpenInterest;
		data["ClosePrice"] = task_data->ClosePrice;
		data["SettlementPrice"] = task_data->SettlementPrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["PreDelta"] = task_data->PreDelta;
		data["CurrDelta"] = task_data->CurrDelta;
		data["UpdateTime"] = task_data->UpdateTime;
		data["BidPrice1"] = task_data->BidPrice1;
		data["BidVolume1"] = task_data->BidVolume1;
		data["AskPrice1"] = task_data->AskPrice1;
		data["AskVolume1"] = task_data->AskVolume1;
		data["BidPrice2"] = task_data->BidPrice2;
		data["BidVolume2"] = task_data->BidVolume2;
		data["AskPrice2"] = task_data->AskPrice2;
		data["AskVolume2"] = task_data->AskVolume2;
		data["BidPrice3"] = task_data->BidPrice3;
		data["BidVolume3"] = task_data->BidVolume3;
		data["AskPrice3"] = task_data->AskPrice3;
		data["AskVolume3"] = task_data->AskVolume3;
		data["BidPrice4"] = task_data->BidPrice4;
		data["BidVolume4"] = task_data->BidVolume4;
		data["AskPrice4"] = task_data->AskPrice4;
		data["AskVolume4"] = task_data->AskVolume4;
		data["BidPrice5"] = task_data->BidPrice5;
		data["BidVolume5"] = task_data->BidVolume5;
		data["AskPrice5"] = task_data->AskPrice5;
		data["AskVolume5"] = task_data->AskVolume5;
		data["AveragePrice"] = task_data->AveragePrice;
		data["PreOpenInterest"] = task_data->PreOpenInterest;
		data["InstrumentTradeStatus"] = task_data->InstrumentTradeStatus;
		data["OpenRestriction"] = toUtf(task_data->OpenRestriction);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryDepthMarketData(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSTradeField *task_data = (CHSTradeField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeType"] = task_data->HedgeType;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradePrice"] = task_data->TradePrice;
		data["TradingDay"] = task_data->TradingDay;
		data["TradeTime"] = task_data->TradeTime;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		delete task_data;
	}
	this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSOrderField *task_data = (CHSOrderField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerOrderID"] = toUtf(task_data->BrokerOrderID);
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["TradeVolume"] = task_data->TradeVolume;
		data["CancelVolume"] = task_data->CancelVolume;
		data["TradePrice"] = task_data->TradePrice;
		data["TradingDay"] = task_data->TradingDay;
		data["InsertDate"] = task_data->InsertDate;
		data["InsertTime"] = task_data->InsertTime;
		data["ReportTime"] = task_data->ReportTime;
		data["OrderCommand"] = toUtf(task_data->OrderCommand);
		data["MinVolume"] = task_data->MinVolume;
		data["SpringPrice"] = task_data->SpringPrice;
		data["SwapOrderFlag"] = task_data->SwapOrderFlag;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["OrderSource"] = task_data->OrderSource;
		delete task_data;
	}
	this->onRtnOrder(data);
};

void TdApi::processRtnExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSExerciseField *task_data = (CHSExerciseField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["ExerciseOrderSysID"] = toUtf(task_data->ExerciseOrderSysID);
		data["SessionID"] = task_data->SessionID;
		data["ExerciseRef"] = toUtf(task_data->ExerciseRef);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["HedgeType"] = task_data->HedgeType;
		data["ExerciseType"] = task_data->ExerciseType;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["InsertDate"] = task_data->InsertDate;
		data["InsertTime"] = task_data->InsertTime;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["OrderSource"] = task_data->OrderSource;
		data["CloseFlag"] = task_data->CloseFlag;
		data["OffsetFlag"] = task_data->OffsetFlag;
		delete task_data;
	}
	this->onRtnExercise(data);
};

void TdApi::processRtnCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSCombActionField *task_data = (CHSCombActionField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["CombOrderSysID"] = toUtf(task_data->CombOrderSysID);
		data["CombPositionID"] = toUtf(task_data->CombPositionID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["CombStrategyID"] = toUtf(task_data->CombStrategyID);
		data["Direction"] = task_data->Direction;
		data["CombDirection"] = task_data->CombDirection;
		data["HedgeType"] = task_data->HedgeType;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["TradingDay"] = task_data->TradingDay;
		data["InsertDate"] = task_data->InsertDate;
		data["InsertTime"] = task_data->InsertTime;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["OrderSource"] = task_data->OrderSource;
		delete task_data;
	}
	this->onRtnCombAction(data);
};

void TdApi::processRtnLock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSLockField *task_data = (CHSLockField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["LockOrderSysID"] = toUtf(task_data->LockOrderSysID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["LockType"] = task_data->LockType;
		data["OrderVolume"] = task_data->OrderVolume;
		data["OrderStatus"] = task_data->OrderStatus;
		data["TradingDay"] = task_data->TradingDay;
		data["InsertTime"] = task_data->InsertTime;
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["OrderSource"] = task_data->OrderSource;
		delete task_data;
	}
	this->onRtnLock(data);
};

