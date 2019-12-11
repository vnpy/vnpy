void TdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void TdApi::processQryFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onQryFrontConnected();
};

void TdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void TdApi::processQryFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onQryFrontDisconnected(task->task_id);
};

void TdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_id);
};

void TdApi::processPackageStart(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageStart(task->task_id, task->task_id);
};

void TdApi::processPackageEnd(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageEnd(task->task_id, task->task_id);
};

void TdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspError(error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserLoginField *task_data = (CUstpFtdcRspUserLoginField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["ExchangeTime"] = toUtf(task_data->ExchangeTime);
		data["MaxOrderLocalID"] = toUtf(task_data->MaxOrderLocalID);
		data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
		data["DataCenterID"] = task_data->DataCenterID;
		data["PrivateFlowSize"] = task_data->PrivateFlowSize;
		data["UserFlowSize"] = task_data->UserFlowSize;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["FemasVersion"] = toUtf(task_data->FemasVersion);
		data["FemasLifeCycle"] = task_data->FemasLifeCycle;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserLogoutField *task_data = (CUstpFtdcRspUserLogoutField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserPasswordUpdate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcUserPasswordUpdateField *task_data = (CUstpFtdcUserPasswordUpdateField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OldPassword"] = toUtf(task_data->OldPassword);
		data["NewPassword"] = toUtf(task_data->NewPassword);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserPasswordUpdate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputOrderField *task_data = (CUstpFtdcInputOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderActionField *task_data = (CUstpFtdcOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQuoteInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputQuoteField *task_data = (CUstpFtdcInputQuoteField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["QuoteLocalID"] = toUtf(task_data->QuoteLocalID);
		data["BidVolume"] = task_data->BidVolume;
		data["BidOffsetFlag"] = task_data->BidOffsetFlag;
		data["BidHedgeFlag"] = task_data->BidHedgeFlag;
		data["BidPrice"] = task_data->BidPrice;
		data["AskVolume"] = task_data->AskVolume;
		data["AskOffsetFlag"] = task_data->AskOffsetFlag;
		data["AskHedgeFlag"] = task_data->AskHedgeFlag;
		data["AskPrice"] = task_data->AskPrice;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BidUserOrderLocalID"] = toUtf(task_data->BidUserOrderLocalID);
		data["AskUserOrderLocalID"] = toUtf(task_data->AskUserOrderLocalID);
		data["BidOrderLocalID"] = toUtf(task_data->BidOrderLocalID);
		data["AskOrderLocalID"] = toUtf(task_data->AskOrderLocalID);
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["StandByTime"] = task_data->StandByTime;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQuoteInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQuoteAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcQuoteActionField *task_data = (CUstpFtdcQuoteActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["UserQuoteActionLocalID"] = toUtf(task_data->UserQuoteActionLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["Direction"] = task_data->Direction;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQuoteAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspForQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcReqForQuoteField *task_data = (CUstpFtdcReqForQuoteField*)task->task_data;
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ReqForQuoteTime"] = toUtf(task_data->ReqForQuoteTime);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspForQuote(data, error, task->task_id, task->task_last);
};

void TdApi::processRspMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputMarginCombActionField *task_data = (CUstpFtdcInputMarginCombActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["UserActionLocalID"] = toUtf(task_data->UserActionLocalID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["CombVolume"] = task_data->CombVolume;
		data["CombDirection"] = task_data->CombDirection;
		data["ActionLocalID"] = toUtf(task_data->ActionLocalID);
		data["Direction"] = task_data->Direction;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["CombActionStatus"] = task_data->CombActionStatus;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspMarginCombAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcstpUserDepositField *task_data = (CUstpFtdcstpUserDepositField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["Amount"] = task_data->Amount;
		data["AmountDirection"] = task_data->AmountDirection;
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserDeposit(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnFlowMessageCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcFlowMessageCancelField *task_data = (CUstpFtdcFlowMessageCancelField*)task->task_data;
		data["SequenceSeries"] = task_data->SequenceSeries;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["DataCenterID"] = task_data->DataCenterID;
		data["StartSequenceNo"] = task_data->StartSequenceNo;
		data["EndSequenceNo"] = task_data->EndSequenceNo;
		delete task->task_data;
	}
	this->onRtnFlowMessageCancel(data);
};

void TdApi::processRtnTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcTradeField *task_data = (CUstpFtdcTradeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["TradePrice"] = task_data->TradePrice;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["ClearingPartID"] = toUtf(task_data->ClearingPartID);
		data["UsedFee"] = task_data->UsedFee;
		data["UsedMargin"] = task_data->UsedMargin;
		data["Premium"] = task_data->Premium;
		data["Position"] = task_data->Position;
		data["PositionCost"] = task_data->PositionCost;
		data["Available"] = task_data->Available;
		data["Margin"] = task_data->Margin;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ArbiInstrumentID"] = toUtf(task_data->ArbiInstrumentID);
		delete task->task_data;
	}
	this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderField *task_data = (CUstpFtdcOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderSource"] = task_data->OrderSource;
		data["OrderStatus"] = task_data->OrderStatus;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["CancelUserID"] = toUtf(task_data->CancelUserID);
		data["VolumeTraded"] = task_data->VolumeTraded;
		data["VolumeRemain"] = task_data->VolumeRemain;
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		delete task->task_data;
	}
	this->onRtnOrder(data);
};

void TdApi::processErrRtnOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputOrderField *task_data = (CUstpFtdcInputOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderActionField *task_data = (CUstpFtdcOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInstrumentStatusField *task_data = (CUstpFtdcInstrumentStatusField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["ProductName"] = toUtf(task_data->ProductName);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentName"] = toUtf(task_data->InstrumentName);
		data["DeliveryYear"] = task_data->DeliveryYear;
		data["DeliveryMonth"] = task_data->DeliveryMonth;
		data["MaxLimitOrderVolume"] = task_data->MaxLimitOrderVolume;
		data["MinLimitOrderVolume"] = task_data->MinLimitOrderVolume;
		data["MaxMarketOrderVolume"] = task_data->MaxMarketOrderVolume;
		data["MinMarketOrderVolume"] = task_data->MinMarketOrderVolume;
		data["VolumeMultiple"] = task_data->VolumeMultiple;
		data["PriceTick"] = task_data->PriceTick;
		data["Currency"] = task_data->Currency;
		data["LongPosLimit"] = task_data->LongPosLimit;
		data["ShortPosLimit"] = task_data->ShortPosLimit;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["InstrumentStatus"] = task_data->InstrumentStatus;
		data["CreateDate"] = toUtf(task_data->CreateDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["ExpireDate"] = toUtf(task_data->ExpireDate);
		data["StartDelivDate"] = toUtf(task_data->StartDelivDate);
		data["EndDelivDate"] = toUtf(task_data->EndDelivDate);
		data["BasisPrice"] = task_data->BasisPrice;
		data["IsTrading"] = task_data->IsTrading;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["UnderlyingMultiple"] = task_data->UnderlyingMultiple;
		data["PositionType"] = task_data->PositionType;
		data["StrikePrice"] = task_data->StrikePrice;
		data["OptionsType"] = task_data->OptionsType;
		data["CurrencyID"] = toUtf(task_data->CurrencyID);
		data["ArbiType"] = task_data->ArbiType;
		data["InstrumentID_1"] = toUtf(task_data->InstrumentID_1);
		data["Direction_1"] = task_data->Direction_1;
		data["Ratio_1"] = task_data->Ratio_1;
		data["InstrumentID_2"] = toUtf(task_data->InstrumentID_2);
		data["Direction_2"] = task_data->Direction_2;
		data["Ratio_2"] = task_data->Ratio_2;
		data["EnterDate"] = toUtf(task_data->EnterDate);
		delete task->task_data;
	}
	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnInvestorAccountDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInvestorAccountDepositResField *task_data = (CUstpFtdcInvestorAccountDepositResField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["AccountSeqNo"] = toUtf(task_data->AccountSeqNo);
		data["Amount"] = task_data->Amount;
		data["AmountDirection"] = task_data->AmountDirection;
		data["Available"] = task_data->Available;
		data["Balance"] = task_data->Balance;
		delete task->task_data;
	}
	this->onRtnInvestorAccountDeposit(data);
};

void TdApi::processRtnQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRtnQuoteField *task_data = (CUstpFtdcRtnQuoteField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["QuoteLocalID"] = toUtf(task_data->QuoteLocalID);
		data["BidVolume"] = task_data->BidVolume;
		data["BidOffsetFlag"] = task_data->BidOffsetFlag;
		data["BidHedgeFlag"] = task_data->BidHedgeFlag;
		data["BidPrice"] = task_data->BidPrice;
		data["AskVolume"] = task_data->AskVolume;
		data["AskOffsetFlag"] = task_data->AskOffsetFlag;
		data["AskHedgeFlag"] = task_data->AskHedgeFlag;
		data["AskPrice"] = task_data->AskPrice;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BidUserOrderLocalID"] = toUtf(task_data->BidUserOrderLocalID);
		data["AskUserOrderLocalID"] = toUtf(task_data->AskUserOrderLocalID);
		data["BidOrderLocalID"] = toUtf(task_data->BidOrderLocalID);
		data["AskOrderLocalID"] = toUtf(task_data->AskOrderLocalID);
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["StandByTime"] = task_data->StandByTime;
		data["BidOrderSysID"] = toUtf(task_data->BidOrderSysID);
		data["AskOrderSysID"] = toUtf(task_data->AskOrderSysID);
		data["QuoteStatus"] = task_data->QuoteStatus;
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	this->onRtnQuote(data);
};

void TdApi::processErrRtnQuoteInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputQuoteField *task_data = (CUstpFtdcInputQuoteField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["QuoteLocalID"] = toUtf(task_data->QuoteLocalID);
		data["BidVolume"] = task_data->BidVolume;
		data["BidOffsetFlag"] = task_data->BidOffsetFlag;
		data["BidHedgeFlag"] = task_data->BidHedgeFlag;
		data["BidPrice"] = task_data->BidPrice;
		data["AskVolume"] = task_data->AskVolume;
		data["AskOffsetFlag"] = task_data->AskOffsetFlag;
		data["AskHedgeFlag"] = task_data->AskHedgeFlag;
		data["AskPrice"] = task_data->AskPrice;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BidUserOrderLocalID"] = toUtf(task_data->BidUserOrderLocalID);
		data["AskUserOrderLocalID"] = toUtf(task_data->AskUserOrderLocalID);
		data["BidOrderLocalID"] = toUtf(task_data->BidOrderLocalID);
		data["AskOrderLocalID"] = toUtf(task_data->AskOrderLocalID);
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["StandByTime"] = task_data->StandByTime;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnQuoteInsert(data, error);
};

void TdApi::processErrRtnQuoteAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcQuoteActionField *task_data = (CUstpFtdcQuoteActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["UserQuoteActionLocalID"] = toUtf(task_data->UserQuoteActionLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["Direction"] = task_data->Direction;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnQuoteAction(data, error);
};

void TdApi::processRtnForQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcReqForQuoteField *task_data = (CUstpFtdcReqForQuoteField*)task->task_data;
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ReqForQuoteTime"] = toUtf(task_data->ReqForQuoteTime);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	this->onRtnForQuote(data);
};

void TdApi::processRtnMarginCombinationLeg(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcMarginCombinationLegField *task_data = (CUstpFtdcMarginCombinationLegField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["LegID"] = task_data->LegID;
		data["LegInstrumentID"] = toUtf(task_data->LegInstrumentID);
		data["Direction"] = task_data->Direction;
		data["LegMultiple"] = task_data->LegMultiple;
		data["Priority"] = task_data->Priority;
		delete task->task_data;
	}
	this->onRtnMarginCombinationLeg(data);
};

void TdApi::processRtnMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputMarginCombActionField *task_data = (CUstpFtdcInputMarginCombActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["UserActionLocalID"] = toUtf(task_data->UserActionLocalID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["CombVolume"] = task_data->CombVolume;
		data["CombDirection"] = task_data->CombDirection;
		data["ActionLocalID"] = toUtf(task_data->ActionLocalID);
		data["Direction"] = task_data->Direction;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["CombActionStatus"] = task_data->CombActionStatus;
		delete task->task_data;
	}
	this->onRtnMarginCombAction(data);
};

void TdApi::processRtnUserDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcstpUserDepositField *task_data = (CUstpFtdcstpUserDepositField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["Amount"] = task_data->Amount;
		data["AmountDirection"] = task_data->AmountDirection;
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		delete task->task_data;
	}
	this->onRtnUserDeposit(data);
};

void TdApi::processRspQueryUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserLoginField *task_data = (CUstpFtdcRspUserLoginField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["ExchangeTime"] = toUtf(task_data->ExchangeTime);
		data["MaxOrderLocalID"] = toUtf(task_data->MaxOrderLocalID);
		data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
		data["DataCenterID"] = task_data->DataCenterID;
		data["PrivateFlowSize"] = task_data->PrivateFlowSize;
		data["UserFlowSize"] = task_data->UserFlowSize;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["FemasVersion"] = toUtf(task_data->FemasVersion);
		data["FemasLifeCycle"] = task_data->FemasLifeCycle;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQueryUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderField *task_data = (CUstpFtdcOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderSource"] = task_data->OrderSource;
		data["OrderStatus"] = task_data->OrderStatus;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["CancelUserID"] = toUtf(task_data->CancelUserID);
		data["VolumeTraded"] = task_data->VolumeTraded;
		data["VolumeRemain"] = task_data->VolumeRemain;
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcTradeField *task_data = (CUstpFtdcTradeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["TradePrice"] = task_data->TradePrice;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["ClearingPartID"] = toUtf(task_data->ClearingPartID);
		data["UsedFee"] = task_data->UsedFee;
		data["UsedMargin"] = task_data->UsedMargin;
		data["Premium"] = task_data->Premium;
		data["Position"] = task_data->Position;
		data["PositionCost"] = task_data->PositionCost;
		data["Available"] = task_data->Available;
		data["Margin"] = task_data->Margin;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ArbiInstrumentID"] = toUtf(task_data->ArbiInstrumentID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryUserInvestor(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserInvestorField *task_data = (CUstpFtdcRspUserInvestorField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryUserInvestor(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTradingCode(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspTradingCodeField *task_data = (CUstpFtdcRspTradingCodeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ClientRight"] = task_data->ClientRight;
		data["ClientHedgeFlag"] = task_data->ClientHedgeFlag;
		data["IsActive"] = task_data->IsActive;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryTradingCode(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorAccountField *task_data = (CUstpFtdcRspInvestorAccountField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["PreBalance"] = task_data->PreBalance;
		data["Deposit"] = task_data->Deposit;
		data["Withdraw"] = task_data->Withdraw;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["FrozenFee"] = task_data->FrozenFee;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["Fee"] = task_data->Fee;
		data["CloseProfit"] = task_data->CloseProfit;
		data["PositionProfit"] = task_data->PositionProfit;
		data["Available"] = task_data->Available;
		data["LongFrozenMargin"] = task_data->LongFrozenMargin;
		data["ShortFrozenMargin"] = task_data->ShortFrozenMargin;
		data["LongMargin"] = task_data->LongMargin;
		data["ShortMargin"] = task_data->ShortMargin;
		data["ReleaseMargin"] = task_data->ReleaseMargin;
		data["DynamicRights"] = task_data->DynamicRights;
		data["TodayInOut"] = task_data->TodayInOut;
		data["Margin"] = task_data->Margin;
		data["Premium"] = task_data->Premium;
		data["Risk"] = task_data->Risk;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInstrument(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInstrumentField *task_data = (CUstpFtdcRspInstrumentField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["ProductName"] = toUtf(task_data->ProductName);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentName"] = toUtf(task_data->InstrumentName);
		data["DeliveryYear"] = task_data->DeliveryYear;
		data["DeliveryMonth"] = task_data->DeliveryMonth;
		data["MaxLimitOrderVolume"] = task_data->MaxLimitOrderVolume;
		data["MinLimitOrderVolume"] = task_data->MinLimitOrderVolume;
		data["MaxMarketOrderVolume"] = task_data->MaxMarketOrderVolume;
		data["MinMarketOrderVolume"] = task_data->MinMarketOrderVolume;
		data["VolumeMultiple"] = task_data->VolumeMultiple;
		data["PriceTick"] = task_data->PriceTick;
		data["Currency"] = task_data->Currency;
		data["LongPosLimit"] = task_data->LongPosLimit;
		data["ShortPosLimit"] = task_data->ShortPosLimit;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["InstrumentStatus"] = task_data->InstrumentStatus;
		data["CreateDate"] = toUtf(task_data->CreateDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["ExpireDate"] = toUtf(task_data->ExpireDate);
		data["StartDelivDate"] = toUtf(task_data->StartDelivDate);
		data["EndDelivDate"] = toUtf(task_data->EndDelivDate);
		data["BasisPrice"] = task_data->BasisPrice;
		data["IsTrading"] = task_data->IsTrading;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["UnderlyingMultiple"] = task_data->UnderlyingMultiple;
		data["PositionType"] = task_data->PositionType;
		data["StrikePrice"] = task_data->StrikePrice;
		data["OptionsType"] = task_data->OptionsType;
		data["CurrencyID"] = toUtf(task_data->CurrencyID);
		data["ArbiType"] = task_data->ArbiType;
		data["InstrumentID_1"] = toUtf(task_data->InstrumentID_1);
		data["Direction_1"] = task_data->Direction_1;
		data["Ratio_1"] = task_data->Ratio_1;
		data["InstrumentID_2"] = toUtf(task_data->InstrumentID_2);
		data["Direction_2"] = task_data->Direction_2;
		data["Ratio_2"] = task_data->Ratio_2;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInstrument(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExchange(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspExchangeField *task_data = (CUstpFtdcRspExchangeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ExchangeName"] = toUtf(task_data->ExchangeName);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryExchange(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorPositionField *task_data = (CUstpFtdcRspInvestorPositionField*)task->task_data;
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["UsedMargin"] = task_data->UsedMargin;
		data["Position"] = task_data->Position;
		data["PositionCost"] = task_data->PositionCost;
		data["YdPosition"] = task_data->YdPosition;
		data["YdPositionCost"] = task_data->YdPositionCost;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["FrozenPosition"] = task_data->FrozenPosition;
		data["FrozenClosing"] = task_data->FrozenClosing;
		data["YdFrozenClosing"] = task_data->YdFrozenClosing;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["LastTradeID"] = toUtf(task_data->LastTradeID);
		data["LastOrderLocalID"] = toUtf(task_data->LastOrderLocalID);
		data["SpeculationPosition"] = task_data->SpeculationPosition;
		data["ArbitragePosition"] = task_data->ArbitragePosition;
		data["HedgePosition"] = task_data->HedgePosition;
		data["SpecFrozenClosing"] = task_data->SpecFrozenClosing;
		data["HedgeFrozenClosing"] = task_data->HedgeFrozenClosing;
		data["Currency"] = toUtf(task_data->Currency);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryComplianceParam(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspComplianceParamField *task_data = (CUstpFtdcRspComplianceParamField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["DailyMaxOrder"] = task_data->DailyMaxOrder;
		data["DailyMaxOrderAction"] = task_data->DailyMaxOrderAction;
		data["DailyMaxErrorOrder"] = task_data->DailyMaxErrorOrder;
		data["DailyMaxOrderVolume"] = task_data->DailyMaxOrderVolume;
		data["DailyMaxOrderActionVolume"] = task_data->DailyMaxOrderActionVolume;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryComplianceParam(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorFee(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInvestorFeeField *task_data = (CUstpFtdcInvestorFeeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["OpenFeeRate"] = task_data->OpenFeeRate;
		data["OpenFeeAmt"] = task_data->OpenFeeAmt;
		data["OffsetFeeRate"] = task_data->OffsetFeeRate;
		data["OffsetFeeAmt"] = task_data->OffsetFeeAmt;
		data["OTFeeRate"] = task_data->OTFeeRate;
		data["OTFeeAmt"] = task_data->OTFeeAmt;
		data["ExecFeeRate"] = task_data->ExecFeeRate;
		data["ExecFeeAmt"] = task_data->ExecFeeAmt;
		data["PerOrderAmt"] = task_data->PerOrderAmt;
		data["PerCancelAmt"] = task_data->PerCancelAmt;
		data["HedgeFlag"] = task_data->HedgeFlag;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorFee(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorMargin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInvestorMarginField *task_data = (CUstpFtdcInvestorMarginField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["LongMarginRate"] = task_data->LongMarginRate;
		data["LongMarginAmt"] = task_data->LongMarginAmt;
		data["ShortMarginRate"] = task_data->ShortMarginRate;
		data["ShortMarginAmt"] = task_data->ShortMarginAmt;
		data["HedgeFlag"] = task_data->HedgeFlag;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorMargin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorCombPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorCombPositionField *task_data = (CUstpFtdcRspInvestorCombPositionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["Direction"] = task_data->Direction;
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["Leg1InstrumentID"] = toUtf(task_data->Leg1InstrumentID);
		data["Leg2InstrumentID"] = toUtf(task_data->Leg2InstrumentID);
		data["CombPosition"] = task_data->CombPosition;
		data["CombFrozenPosition"] = task_data->CombFrozenPosition;
		data["CombFreeMargin"] = task_data->CombFreeMargin;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorCombPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorLegPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorLegPositionField *task_data = (CUstpFtdcRspInvestorLegPositionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["LongPosition"] = task_data->LongPosition;
		data["ShortPosition"] = task_data->ShortPosition;
		data["LongMargin"] = task_data->LongMargin;
		data["ShortMargin"] = task_data->ShortMargin;
		data["LongFrozenPosition"] = task_data->LongFrozenPosition;
		data["ShortFrozenPosition"] = task_data->ShortFrozenPosition;
		data["LongFrozenMargin"] = task_data->LongFrozenMargin;
		data["ShortFrozenMargin"] = task_data->ShortFrozenMargin;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorLegPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInstrumentGroup(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInstrumentGroupField *task_data = (CUstpFtdcRspInstrumentGroupField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentGroupID"] = toUtf(task_data->InstrumentGroupID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInstrumentGroup(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryClientMarginCombType(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspClientMarginCombTypeField *task_data = (CUstpFtdcRspClientMarginCombTypeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstrumentGroupID"] = toUtf(task_data->InstrumentGroupID);
		data["MarginCombType"] = task_data->MarginCombType;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryClientMarginCombType(data, error, task->task_id, task->task_last);
};

void TdApi::processRspExecOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderField *task_data = (CUstpFtdcInputExecOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Volume"] = task_data->Volume;
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspExecOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspExecOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderActionField *task_data = (CUstpFtdcInputExecOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["OrderType"] = task_data->OrderType;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspExecOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnExecOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcExecOrderField *task_data = (CUstpFtdcExecOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Volume"] = task_data->Volume;
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderSource"] = task_data->OrderSource;
		data["OrderStatus"] = task_data->OrderStatus;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["CancelUserID"] = toUtf(task_data->CancelUserID);
		delete task->task_data;
	}
	this->onRtnExecOrder(data);
};

void TdApi::processErrRtnExecOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderField *task_data = (CUstpFtdcInputExecOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Volume"] = task_data->Volume;
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnExecOrderInsert(data, error);
};

void TdApi::processErrRtnExecOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderActionField *task_data = (CUstpFtdcInputExecOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["OrderType"] = task_data->OrderType;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnExecOrderAction(data, error);
};

void TdApi::processRtnTransferMoney(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcSyncMoneyTransferField *task_data = (CUstpFtdcSyncMoneyTransferField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["BankID"] = toUtf(task_data->BankID);
		data["BankAccount"] = toUtf(task_data->BankAccount);
		data["Currency"] = toUtf(task_data->Currency);
		data["Amount"] = task_data->Amount;
		data["SyncTransMoneyEvent"] = task_data->SyncTransMoneyEvent;
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["TradeSource"] = task_data->TradeSource;
		data["TransSerialNo"] = toUtf(task_data->TransSerialNo);
		data["SerialNo"] = toUtf(task_data->SerialNo);
		data["UserID"] = toUtf(task_data->UserID);
		data["CommandDate"] = toUtf(task_data->CommandDate);
		data["CommandTime"] = toUtf(task_data->CommandTime);
		delete task->task_data;
	}
	this->onRtnTransferMoney(data);
};

void TdApi::processRspQrySystemTime(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspQrySystemTimeField *task_data = (CUstpFtdcRspQrySystemTimeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["SystemTime"] = toUtf(task_data->SystemTime);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQrySystemTime(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryMarginPrefParam(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspQryMarginPrefParamField *task_data = (CUstpFtdcRspQryMarginPrefParamField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["CombInstrumentName"] = toUtf(task_data->CombInstrumentName);
		data["CombType"] = task_data->CombType;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Leg1InstrumentID"] = toUtf(task_data->Leg1InstrumentID);
		data["Leg1ProductID"] = toUtf(task_data->Leg1ProductID);
		data["Leg1Direction"] = task_data->Leg1Direction;
		data["Leg1HedgeFlag"] = task_data->Leg1HedgeFlag;
		data["Leg1SettlementPrice"] = task_data->Leg1SettlementPrice;
		data["Leg2InstrumentID"] = toUtf(task_data->Leg2InstrumentID);
		data["Leg2ProductID"] = toUtf(task_data->Leg2ProductID);
		data["Leg2Direction"] = task_data->Leg2Direction;
		data["Leg2HedgeFlag"] = task_data->Leg2HedgeFlag;
		data["Leg2SettlementPrice"] = task_data->Leg2SettlementPrice;
		data["Priority"] = task_data->Priority;
		data["TradeEna"] = task_data->TradeEna;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryMarginPrefParam(data, error, task->task_id, task->task_last);
};

void TdApi::processRspDSUserCertification(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcDSUserCertRspDataField *task_data = (CUstpFtdcDSUserCertRspDataField*)task->task_data;
		data["AppID"] = toUtf(task_data->AppID);
		data["AppIDType"] = task_data->AppIDType;
		data["UserCertRspData"] = toUtf(task_data->UserCertRspData);
		data["TotalNum"] = task_data->TotalNum;
		data["CurrentNum"] = task_data->CurrentNum;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspDSUserCertification(data, error, task->task_id, task->task_last);
};

void TdApi::processRspDSProxySubmitInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspDSProxySubmitInfo(error, task->task_id, task->task_last);
};

