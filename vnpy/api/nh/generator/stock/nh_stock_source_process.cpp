void StockTdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void StockTdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void StockTdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_id);
};

void StockTdApi::processPackageStart(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageStart(task->task_id, task->task_id);
};

void StockTdApi::processPackageEnd(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageEnd(task->task_id, task->task_id);
};

void StockTdApi::processRspSubscribeTopic(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcDisseminationField *task_data = (CStockFtdcDisseminationField*)task->task_data;
		data["SequenceSeries"] = task_data->SequenceSeries;
		data["SequenceNo"] = task_data->SequenceNo;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspSubscribeTopic(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspUserLoginField *task_data = (CStockFtdcRspUserLoginField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["MaxClOrdID"] = task_data->MaxClOrdID;
		data["UserID"] = toUtf(task_data->UserID);
		data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
		data["DataCenterID"] = task_data->DataCenterID;
		data["PrivateFlowSize"] = task_data->PrivateFlowSize;
		data["UserFlowSize"] = task_data->UserFlowSize;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspUserLogoutField *task_data = (CStockFtdcRspUserLogoutField*)task->task_data;
		data["UserID"] = toUtf(task_data->UserID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspUserPasswordUpdate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcUserPasswordUpdateField *task_data = (CStockFtdcUserPasswordUpdateField*)task->task_data;
		data["UserID"] = toUtf(task_data->UserID);
		data["OldPassword"] = toUtf(task_data->OldPassword);
		data["NewPassword"] = toUtf(task_data->NewPassword);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserPasswordUpdate(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspStockInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockInsertRspField *task_data = (CStockFtdcStockInsertRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdType"] = task_data->OrdType;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["Qty2"] = task_data->Qty2;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspStockInsert(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspStockCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockCancelRspField *task_data = (CStockFtdcStockCancelRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["OrigClOrdId"] = task_data->OrigClOrdId;
		data["Qty2"] = task_data->Qty2;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspStockCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspOptionsInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsInsertRspField *task_data = (CStockFtdcOptionsInsertRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["LeavesQty"] = task_data->LeavesQty;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOptionsInsert(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspOptionsCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsCancelRspField *task_data = (CStockFtdcOptionsCancelRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrigClOrdID"] = task_data->OrigClOrdID;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["LeavesQty"] = task_data->LeavesQty;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOptionsCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQuoteInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcQuoteInsertRspField *task_data = (CStockFtdcQuoteInsertRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		data["BidPx"] = task_data->BidPx;
		data["AskPx"] = task_data->AskPx;
		data["BidSize"] = task_data->BidSize;
		data["AskSize"] = task_data->AskSize;
		data["BidPositionEffect"] = task_data->BidPositionEffect;
		data["AskPositionEffect"] = task_data->AskPositionEffect;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQuoteInsert(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspForQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcForQuoteRspField *task_data = (CStockFtdcForQuoteRspField*)task->task_data;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspForQuote(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQuoteCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcQuoteCancelRspField *task_data = (CStockFtdcQuoteCancelRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrigClOrdID"] = task_data->OrigClOrdID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQuoteCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspStockLock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockLockRspField *task_data = (CStockFtdcStockLockRspField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspStockLock(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseRspField *task_data = (CStockFtdcExerciseRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspExercise(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspExerciseCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseCancelRspField *task_data = (CStockFtdcExerciseCancelRspField*)task->task_data;
		data["OrigClOrdID"] = task_data->OrigClOrdID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspExerciseCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryPartAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspPartAccountField *task_data = (CStockFtdcRspPartAccountField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["PreBalance"] = task_data->PreBalance;
		data["Balance"] = task_data->Balance;
		data["Available"] = task_data->Available;
		data["CurrMargin"] = task_data->CurrMargin;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["CombMargin"] = task_data->CombMargin;
		data["Premium"] = task_data->Premium;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["Commi"] = task_data->Commi;
		data["FrozenCommi"] = task_data->FrozenCommi;
		data["CloseProfit"] = task_data->CloseProfit;
		data["PosiProfit"] = task_data->PosiProfit;
		data["Deposit"] = task_data->Deposit;
		data["Withdraw"] = task_data->Withdraw;
		data["BaseReserve"] = task_data->BaseReserve;
		data["SaveDouble1"] = task_data->SaveDouble1;
		data["SaveDouble2"] = task_data->SaveDouble2;
		data["SaveDouble3"] = task_data->SaveDouble3;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryPartAccount(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryStockOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryStockOrderField *task_data = (CStockFtdcRspQryStockOrderField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdType"] = task_data->OrdType;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["Qty2"] = task_data->Qty2;
		data["OrdStatus"] = task_data->OrdStatus;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryStockOrder(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryOptionsOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryOptionsOrderField *task_data = (CStockFtdcRspQryOptionsOrderField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["LeavesQty"] = task_data->LeavesQty;
		data["OwnerType"] = task_data->OwnerType;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["PositionEffect"] = task_data->PositionEffect;
		data["OrdType"] = task_data->OrdType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["UserID"] = toUtf(task_data->UserID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOptionsOrder(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryQuoteOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryQuoteOrderField *task_data = (CStockFtdcRspQryQuoteOrderField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdStatus"] = task_data->OrdStatus;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OwnerType"] = task_data->OwnerType;
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		data["BidPx"] = task_data->BidPx;
		data["AskPx"] = task_data->AskPx;
		data["BidSize"] = task_data->BidSize;
		data["AskSize"] = task_data->AskSize;
		data["BidPositionEffect"] = task_data->BidPositionEffect;
		data["AskPositionEffect"] = task_data->AskPositionEffect;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryQuoteOrder(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryStockTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockTradeField *task_data = (CStockFtdcStockTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["TradeVolume"] = task_data->TradeVolume;
		data["Side"] = task_data->Side;
		data["Cjjg"] = task_data->Cjjg;
		data["Cjje"] = task_data->Cjje;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryStockTrade(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryOptionsTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsTradeField *task_data = (CStockFtdcOptionsTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["ExecID"] = toUtf(task_data->ExecID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["LastPx"] = task_data->LastPx;
		data["LastQty"] = task_data->LastQty;
		data["LeavesQty"] = task_data->LeavesQty;
		data["Side"] = task_data->Side;
		data["PositionEffect"] = task_data->PositionEffect;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OrigTime"] = toUtf(task_data->OrigTime);
		data["ExecType"] = task_data->ExecType;
		data["OwnerType"] = task_data->OwnerType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["TotalValueTraded"] = task_data->TotalValueTraded;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOptionsTrade(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspPositionField *task_data = (CStockFtdcRspPositionField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Converd"] = task_data->Converd;
		data["Side"] = task_data->Side;
		data["YdPosition"] = task_data->YdPosition;
		data["Position"] = task_data->Position;
		data["TodayPosition"] = task_data->TodayPosition;
		data["BuyTradeVolume"] = task_data->BuyTradeVolume;
		data["SellTradeVolume"] = task_data->SellTradeVolume;
		data["PositionCost"] = task_data->PositionCost;
		data["YdPositionCost"] = task_data->YdPositionCost;
		data["UseMargin"] = task_data->UseMargin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryPosition(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryTopic(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcDisseminationField *task_data = (CStockFtdcDisseminationField*)task->task_data;
		data["SequenceSeries"] = task_data->SequenceSeries;
		data["SequenceNo"] = task_data->SequenceNo;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTopic(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryStock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryStockField *task_data = (CStockFtdcRspQryStockField*)task->task_data;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["contractmultiplierunit"] = task_data->contractmultiplierunit;
		data["startdate"] = toUtf(task_data->startdate);
		data["enddate"] = toUtf(task_data->enddate);
		data["totallongposition"] = task_data->totallongposition;
		data["securityclosepx"] = task_data->securityclosepx;
		data["settlprice"] = task_data->settlprice;
		data["underlyingclosepx"] = task_data->underlyingclosepx;
		data["dailypriceuplimit"] = task_data->dailypriceuplimit;
		data["dailypricedownlimit"] = task_data->dailypricedownlimit;
		data["marginunit"] = task_data->marginunit;
		data["marginratioparam1"] = task_data->marginratioparam1;
		data["marginratioparam2"] = task_data->marginratioparam2;
		data["roundlot"] = task_data->roundlot;
		data["lmtordminfloor"] = task_data->lmtordminfloor;
		data["lmtordmaxfloor"] = task_data->lmtordmaxfloor;
		data["mktordminfloor"] = task_data->mktordminfloor;
		data["mktordmaxfloor"] = task_data->mktordmaxfloor;
		data["ticksize"] = task_data->ticksize;
		data["lastprice"] = task_data->lastprice;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryStock(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryOptions(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryOptionsField *task_data = (CStockFtdcRspQryOptionsField*)task->task_data;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["underlyingsecurityid"] = toUtf(task_data->underlyingsecurityid);
		data["optiontype"] = task_data->optiontype;
		data["callorput"] = task_data->callorput;
		data["contractmultiplierunit"] = task_data->contractmultiplierunit;
		data["exerciseprice"] = task_data->exerciseprice;
		data["startdate"] = toUtf(task_data->startdate);
		data["enddate"] = toUtf(task_data->enddate);
		data["exercisedate"] = toUtf(task_data->exercisedate);
		data["deliverydate"] = toUtf(task_data->deliverydate);
		data["expiredate"] = toUtf(task_data->expiredate);
		data["totallongposition"] = task_data->totallongposition;
		data["securityclosepx"] = task_data->securityclosepx;
		data["settlprice"] = task_data->settlprice;
		data["underlyingclosepx"] = task_data->underlyingclosepx;
		data["dailypriceuplimit"] = task_data->dailypriceuplimit;
		data["dailypricedownlimit"] = task_data->dailypricedownlimit;
		data["marginunit"] = task_data->marginunit;
		data["marginratioparam1"] = task_data->marginratioparam1;
		data["marginratioparam2"] = task_data->marginratioparam2;
		data["roundlot"] = task_data->roundlot;
		data["lmtordminfloor"] = task_data->lmtordminfloor;
		data["lmtordmaxfloor"] = task_data->lmtordmaxfloor;
		data["mktordminfloor"] = task_data->mktordminfloor;
		data["mktordmaxfloor"] = task_data->mktordmaxfloor;
		data["ticksize"] = task_data->ticksize;
		data["lastprice"] = task_data->lastprice;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOptions(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRtnOptionsOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsOrderField *task_data = (CStockFtdcOptionsOrderField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["TradeQty"] = task_data->TradeQty;
		data["CancelQty"] = task_data->CancelQty;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["PositionEffect"] = task_data->PositionEffect;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OwnerType"] = task_data->OwnerType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["OrdType"] = task_data->OrdType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OrdRejReason"] = task_data->OrdRejReason;
		delete task_data;
	}
	this->onRtnOptionsOrder(data);
};

void StockTdApi::processRtnStockOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockOrderField *task_data = (CStockFtdcStockOrderField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["OrdStatus"] = task_data->OrdStatus;
		data["Qty2"] = task_data->Qty2;
		data["TradeQty"] = task_data->TradeQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OwnerType"] = task_data->OwnerType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["OrdRejReason"] = task_data->OrdRejReason;
		delete task_data;
	}
	this->onRtnStockOrder(data);
};

void StockTdApi::processRtnQuoteOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcQuoteOrderField *task_data = (CStockFtdcQuoteOrderField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdStatus"] = task_data->OrdStatus;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OwnerType"] = task_data->OwnerType;
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		data["BidPx"] = task_data->BidPx;
		data["AskPx"] = task_data->AskPx;
		data["BidSize"] = task_data->BidSize;
		data["AskSize"] = task_data->AskSize;
		data["BidPositionEffect"] = task_data->BidPositionEffect;
		data["AskPositionEffect"] = task_data->AskPositionEffect;
		data["OrdRejReason"] = task_data->OrdRejReason;
		delete task_data;
	}
	this->onRtnQuoteOrder(data);
};

void StockTdApi::processRtnOptionsTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsTradeField *task_data = (CStockFtdcOptionsTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["ExecID"] = toUtf(task_data->ExecID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["LastPx"] = task_data->LastPx;
		data["LastQty"] = task_data->LastQty;
		data["LeavesQty"] = task_data->LeavesQty;
		data["Side"] = task_data->Side;
		data["PositionEffect"] = task_data->PositionEffect;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OrigTime"] = toUtf(task_data->OrigTime);
		data["ExecType"] = task_data->ExecType;
		data["OwnerType"] = task_data->OwnerType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["TotalValueTraded"] = task_data->TotalValueTraded;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	this->onRtnOptionsTrade(data);
};

void StockTdApi::processRtnStockTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockTradeField *task_data = (CStockFtdcStockTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["TradeVolume"] = task_data->TradeVolume;
		data["Side"] = task_data->Side;
		data["Cjjg"] = task_data->Cjjg;
		data["Cjje"] = task_data->Cjje;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		delete task_data;
	}
	this->onRtnStockTrade(data);
};

void StockTdApi::processRtnExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseRtnField *task_data = (CStockFtdcExerciseRtnField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		delete task_data;
	}
	this->onRtnExercise(data);
};

void StockTdApi::processRspQryRate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryRateField *task_data = (CStockFtdcRspQryRateField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Margin"] = task_data->Margin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryRate(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryClient(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspClientField *task_data = (CStockFtdcRspClientField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["Status"] = task_data->Status;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClient(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryClientMargin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryClientMarginField *task_data = (CStockFtdcRspQryClientMarginField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Margin"] = task_data->Margin;
		data["MarginRatio"] = task_data->MarginRatio;
		data["MinMarginRatio"] = task_data->MinMarginRatio;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClientMargin(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseRtnField *task_data = (CStockFtdcExerciseRtnField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryExercise(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRtnWithdrawDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcWithdrawDepositRtnField *task_data = (CStockFtdcWithdrawDepositRtnField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["deposit"] = task_data->deposit;
		data["withdraw"] = task_data->withdraw;
		delete task_data;
	}
	this->onRtnWithdrawDeposit(data);
};

void StockTdApi::processRspMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcMarginCombActionRspField *task_data = (CStockFtdcMarginCombActionRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["CombID"] = toUtf(task_data->CombID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspMarginCombAction(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRtnMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcMarginCombActionRtnField *task_data = (CStockFtdcMarginCombActionRtnField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["ExecID"] = toUtf(task_data->ExecID);
		data["CombID"] = toUtf(task_data->CombID);
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OrigTime"] = toUtf(task_data->OrigTime);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["LastQty"] = task_data->LastQty;
		data["commargin"] = task_data->commargin;
		delete task_data;
	}
	this->onRtnMarginCombAction(data);
};

void StockTdApi::processRspQrySseCombPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcCombPositionRspField *task_data = (CStockFtdcCombPositionRspField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["PosiQty"] = task_data->PosiQty;
		data["commargin"] = task_data->commargin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQrySseCombPosition(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspCombExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcCombExerciseRspField *task_data = (CStockFtdcCombExerciseRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["LegSecurityID1"] = toUtf(task_data->LegSecurityID1);
		data["LegOrderQty1"] = task_data->LegOrderQty1;
		data["LegSecurityID2"] = toUtf(task_data->LegSecurityID2);
		data["LegOrderQty2"] = task_data->LegOrderQty2;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspCombExercise(data, error, task->task_id, task->task_last);
};

