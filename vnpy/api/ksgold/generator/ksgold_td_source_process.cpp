void TdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected(task->task_id);
};

void TdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void TdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspUserLoginField *task_data = (CThostFtdcRspUserLoginField*)task->task_data;
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["SessionID"] = task_data->SessionID;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["clientName"] = toUtf(task_data->clientName);
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["SeatNo"] = toUtf(task_data->SeatNo);
		data["lastLoginIp"] = toUtf(task_data->lastLoginIp);
		data["lastLoginDate"] = toUtf(task_data->lastLoginDate);
		data["lastLoginTime"] = toUtf(task_data->lastLoginTime);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["LoginType"] = task_data->LoginType;
		data["Password"] = toUtf(task_data->Password);
		data["MacAddress"] = toUtf(task_data->MacAddress);
		data["LoginIp"] = toUtf(task_data->LoginIp);
		data["UserProductionInfo"] = toUtf(task_data->UserProductionInfo);
		data["ProtocolInfo"] = toUtf(task_data->ProtocolInfo);
		data["SystemName"] = toUtf(task_data->SystemName);
		data["FrontID"] = task_data->FrontID;
		data["MaxOrderRef"] = toUtf(task_data->MaxOrderRef);
		data["SgeTime"] = toUtf(task_data->SgeTime);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcUserLogoutField *task_data = (CThostFtdcUserLogoutField*)task->task_data;
		data["LoginIp"] = toUtf(task_data->LoginIp);
		data["MacAddress"] = toUtf(task_data->MacAddress);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void TdApi::processNtyMktStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcMarketStatusField *task_data = (CThostFtdcMarketStatusField*)task->task_data;
		data["MktStatus"] = toUtf(task_data->MktStatus);
		data["marketID"] = toUtf(task_data->marketID);
		data["ExchCode"] = toUtf(task_data->ExchCode);
		delete task_data;
	}
	this->onNtyMktStatus(data);
};

void TdApi::processRtnInstrumentStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInstrumentStatusField *task_data = (CThostFtdcInstrumentStatusField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentStatus"] = task_data->InstrumentStatus;
		delete task_data;
	}
	this->onRtnInstrumentStatus(data);
};

void TdApi::processRspQryInstrument(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInstrumentField *task_data = (CThostFtdcInstrumentField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstID"] = toUtf(task_data->InstID);
		data["LowerLimit"] = task_data->LowerLimit;
		data["MarketID"] = toUtf(task_data->MarketID);
		data["MaxHand"] = task_data->MaxHand;
		data["MinHand"] = task_data->MinHand;
		data["Name"] = toUtf(task_data->Name);
		data["OpenFlag"] = task_data->OpenFlag;
		data["Tick"] = task_data->Tick;
		data["TradeState"] = task_data->TradeState;
		data["Unit"] = task_data->Unit;
		data["UpperLimit"] = task_data->UpperLimit;
		data["VarietyID"] = toUtf(task_data->VarietyID);
		data["VarietyType"] = task_data->VarietyType;
		data["MarketType"] = task_data->MarketType;
		data["ProductID"] = toUtf(task_data->ProductID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryInstrument(data, error, task->task_id, task->task_last);
};

void TdApi::processRspReqQryVarietyCode(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspVarietyCodeField *task_data = (CThostFtdcRspVarietyCodeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["VarietyShortName"] = toUtf(task_data->VarietyShortName);
		data["VarietyFullName"] = toUtf(task_data->VarietyFullName);
		data["VarietyCode"] = toUtf(task_data->VarietyCode);
		data["VarietyType"] = toUtf(task_data->VarietyType);
		data["WeightUnit"] = toUtf(task_data->WeightUnit);
		data["Status"] = task_data->Status;
		data["MinTakeVolumn"] = task_data->MinTakeVolumn;
		data["TakeUnit"] = task_data->TakeUnit;
		data["Weight"] = task_data->Weight;
		data["ProductID"] = toUtf(task_data->ProductID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspReqQryVarietyCode(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspInputOrderField *task_data = (CThostFtdcRspInputOrderField*)task->task_data;
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["Status"] = task_data->Status;
		data["SeatID"] = toUtf(task_data->SeatID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MarketID"] = toUtf(task_data->MarketID);
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["RequestID"] = task_data->RequestID;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["CmdType"] = toUtf(task_data->CmdType);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFSubscriptionOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFSubscriptionOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFPurchaseOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFPurchaseOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFRedeemInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFRedeemInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFAccountBinding(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFBindingStatusField *task_data = (CThostFtdcETFBindingStatusField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StockTradeCode"] = toUtf(task_data->StockTradeCode);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["BindingStatus"] = toUtf(task_data->BindingStatus);
		data["BindingDate"] = toUtf(task_data->BindingDate);
		data["BindingLocalOrderNo"] = toUtf(task_data->BindingLocalOrderNo);
		data["BindingEtfrevsn"] = toUtf(task_data->BindingEtfrevsn);
		data["UnBindingDate"] = toUtf(task_data->UnBindingDate);
		data["UnBindingLocalOrderNo"] = toUtf(task_data->UnBindingLocalOrderNo);
		data["UnBindingEtfrevsn"] = toUtf(task_data->UnBindingEtfrevsn);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFAccountBinding(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFAccountUnbinding(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFBindingStatusField *task_data = (CThostFtdcETFBindingStatusField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StockTradeCode"] = toUtf(task_data->StockTradeCode);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["BindingStatus"] = toUtf(task_data->BindingStatus);
		data["BindingDate"] = toUtf(task_data->BindingDate);
		data["BindingLocalOrderNo"] = toUtf(task_data->BindingLocalOrderNo);
		data["BindingEtfrevsn"] = toUtf(task_data->BindingEtfrevsn);
		data["UnBindingDate"] = toUtf(task_data->UnBindingDate);
		data["UnBindingLocalOrderNo"] = toUtf(task_data->UnBindingLocalOrderNo);
		data["UnBindingEtfrevsn"] = toUtf(task_data->UnBindingEtfrevsn);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFAccountUnbinding(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcOrderField *task_data = (CThostFtdcOrderField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MatchQty"] = task_data->MatchQty;
		data["Status"] = task_data->Status;
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["CancelQty"] = task_data->CancelQty;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["CmdType"] = toUtf(task_data->CmdType);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	this->onRtnOrder(data);
};

void TdApi::processForceLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcUserLogoutField *task_data = (CThostFtdcUserLogoutField*)task->task_data;
		data["LoginIp"] = toUtf(task_data->LoginIp);
		data["MacAddress"] = toUtf(task_data->MacAddress);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	this->onForceLogout(data);
};

void TdApi::processRtnETFAccountBindingStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFBindingStatusField *task_data = (CThostFtdcETFBindingStatusField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StockTradeCode"] = toUtf(task_data->StockTradeCode);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["BindingStatus"] = toUtf(task_data->BindingStatus);
		data["BindingDate"] = toUtf(task_data->BindingDate);
		data["BindingLocalOrderNo"] = toUtf(task_data->BindingLocalOrderNo);
		data["BindingEtfrevsn"] = toUtf(task_data->BindingEtfrevsn);
		data["UnBindingDate"] = toUtf(task_data->UnBindingDate);
		data["UnBindingLocalOrderNo"] = toUtf(task_data->UnBindingLocalOrderNo);
		data["UnBindingEtfrevsn"] = toUtf(task_data->UnBindingEtfrevsn);
		delete task_data;
	}
	this->onRtnETFAccountBindingStatus(data);
};

void TdApi::processRtnETFOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	this->onRtnETFOrder(data);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspInputOrderActionField *task_data = (CThostFtdcRspInputOrderActionField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["localOrderNo"] = toUtf(task_data->localOrderNo);
		data["Status"] = task_data->Status;
		data["marketID"] = toUtf(task_data->marketID);
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspError(error, task->task_id, task->task_last);
};

void TdApi::processRtnTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcTradeField *task_data = (CThostFtdcTradeField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Price"] = task_data->Price;
		data["Volume"] = task_data->Volume;
		data["Amount"] = task_data->Amount;
		data["Order_flag"] = task_data->Order_flag;
		data["MatchDate"] = toUtf(task_data->MatchDate);
		data["MatchTime"] = toUtf(task_data->MatchTime);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["Trade_fee"] = task_data->Trade_fee;
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["Forcebatchnum"] = task_data->Forcebatchnum;
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		delete task_data;
	}
	this->onRtnTrade(data);
};

void TdApi::processRspQryTradingAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcTradingAccountField *task_data = (CThostFtdcTradingAccountField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["AvailCap"] = task_data->AvailCap;
		data["Available"] = task_data->Available;
		data["PosiMargin"] = task_data->PosiMargin;
		data["BuyPosiMargin"] = task_data->BuyPosiMargin;
		data["SellPosiMargin"] = task_data->SellPosiMargin;
		data["StorageMargin"] = task_data->StorageMargin;
		data["TotalFee"] = task_data->TotalFee;
		data["TotalFrozen"] = task_data->TotalFrozen;
		data["OrderFrozen"] = task_data->OrderFrozen;
		data["SpotSellFrozen"] = task_data->SpotSellFrozen;
		data["TodayIn"] = task_data->TodayIn;
		data["TodayOut"] = task_data->TodayOut;
		data["LastFrozen"] = task_data->LastFrozen;
		data["TotalFrozenFee"] = task_data->TotalFrozenFee;
		data["PickUpMargin"] = task_data->PickUpMargin;
		data["MiddleMargin"] = task_data->MiddleMargin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTradingAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryHisCapital(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspHisCapitalField *task_data = (CThostFtdcRspHisCapitalField*)task->task_data;
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["AvailCap"] = task_data->AvailCap;
		data["Todayprofit"] = task_data->Todayprofit;
		data["PosiMargin"] = task_data->PosiMargin;
		data["PickUpMargin"] = task_data->PickUpMargin;
		data["StorageMargin"] = task_data->StorageMargin;
		data["TradeFee"] = task_data->TradeFee;
		data["TodayInOut"] = task_data->TodayInOut;
		data["EtfTransferFee"] = task_data->EtfTransferFee;
		data["EtfTransferFeeFrzn"] = task_data->EtfTransferFeeFrzn;
		data["EtfCashBalance"] = task_data->EtfCashBalance;
		data["EtfCashBalanceFrzn"] = task_data->EtfCashBalanceFrzn;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryHisCapital(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcOrderField *task_data = (CThostFtdcOrderField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MatchQty"] = task_data->MatchQty;
		data["Status"] = task_data->Status;
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["CancelQty"] = task_data->CancelQty;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["CmdType"] = toUtf(task_data->CmdType);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
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
		CThostFtdcTradeField *task_data = (CThostFtdcTradeField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Price"] = task_data->Price;
		data["Volume"] = task_data->Volume;
		data["Amount"] = task_data->Amount;
		data["Order_flag"] = task_data->Order_flag;
		data["MatchDate"] = toUtf(task_data->MatchDate);
		data["MatchTime"] = toUtf(task_data->MatchTime);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["Trade_fee"] = task_data->Trade_fee;
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["Forcebatchnum"] = task_data->Forcebatchnum;
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInvestorPositionField *task_data = (CThostFtdcInvestorPositionField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstID"] = toUtf(task_data->InstID);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["LongPosi"] = task_data->LongPosi;
		data["LongPosiAvgPrice"] = task_data->LongPosiAvgPrice;
		data["ShortPosi"] = task_data->ShortPosi;
		data["ShortPosiAvgPrice"] = task_data->ShortPosiAvgPrice;
		data["LongOpenAvgPrice"] = task_data->LongOpenAvgPrice;
		data["ShortOpenAvgPrice"] = task_data->ShortOpenAvgPrice;
		data["LongPosiFrozen"] = task_data->LongPosiFrozen;
		data["ShortPosiFrozen"] = task_data->ShortPosiFrozen;
		data["LongPosiVol"] = task_data->LongPosiVol;
		data["ShortPosiVol"] = task_data->ShortPosiVol;
		data["TodayLong"] = task_data->TodayLong;
		data["TodayShort"] = task_data->TodayShort;
		data["TodayOffsetShort"] = task_data->TodayOffsetShort;
		data["TodayOffsetLong"] = task_data->TodayOffsetLong;
		data["LastLong"] = task_data->LastLong;
		data["LastShort"] = task_data->LastShort;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryInvestorPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryClientStorage(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcStorageField *task_data = (CThostFtdcStorageField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["VarietyID"] = toUtf(task_data->VarietyID);
		data["totalStorage"] = task_data->totalStorage;
		data["availableStorage"] = task_data->availableStorage;
		data["frozenStorage"] = task_data->frozenStorage;
		data["pendStorage"] = task_data->pendStorage;
		data["todayBuy"] = task_data->todayBuy;
		data["todaySell"] = task_data->todaySell;
		data["todayDeposit"] = task_data->todayDeposit;
		data["todayDraw"] = task_data->todayDraw;
		data["todayBorrow"] = task_data->todayBorrow;
		data["todayLend"] = task_data->todayLend;
		data["impawnStorage"] = task_data->impawnStorage;
		data["lawFrozen"] = task_data->lawFrozen;
		data["bankFrozen"] = task_data->bankFrozen;
		data["customType"] = task_data->customType;
		data["storageCost"] = task_data->storageCost;
		data["impawnFrozen"] = task_data->impawnFrozen;
		data["transFrozen"] = task_data->transFrozen;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClientStorage(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCostMarginFeeRate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspCostMarginFeeField *task_data = (CThostFtdcRspCostMarginFeeField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOpenHandFee"] = task_data->BuyOpenHandFee;
		data["BuyOffsetHandFee"] = task_data->BuyOffsetHandFee;
		data["SellOpenHandFee"] = task_data->SellOpenHandFee;
		data["SellOffsetHandFee"] = task_data->SellOffsetHandFee;
		data["BuyMarginFee"] = task_data->BuyMarginFee;
		data["SellMarginFee"] = task_data->SellMarginFee;
		data["SeatBuyMarginFee"] = task_data->SeatBuyMarginFee;
		data["SeatSellMarginFee"] = task_data->SeatSellMarginFee;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryCostMarginFeeRate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspConditionOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionOrderField *task_data = (CThostFtdcRspConditionOrderField*)task->task_data;
		data["SeatID"] = toUtf(task_data->SeatID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		data["EntrustDate"] = toUtf(task_data->EntrustDate);
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["Status"] = task_data->Status;
		data["MarketID"] = toUtf(task_data->MarketID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["OrderType"] = task_data->OrderType;
		data["MiddleFlag"] = task_data->MiddleFlag;
		data["PriceFlag"] = task_data->PriceFlag;
		data["Price"] = task_data->Price;
		data["TrigPrice"] = task_data->TrigPrice;
		data["ValidDay"] = task_data->ValidDay;
		data["VolumnCheck"] = task_data->VolumnCheck;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["CmdType"] = toUtf(task_data->CmdType);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspConditionOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspConditionOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionActionOrderField *task_data = (CThostFtdcRspConditionActionOrderField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspConditionOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryConditionOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionOrderQryField *task_data = (CThostFtdcRspConditionOrderQryField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StartDate"] = toUtf(task_data->StartDate);
		data["EndDate"] = toUtf(task_data->EndDate);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["OrderType"] = task_data->OrderType;
		data["EntrustTypeName"] = toUtf(task_data->EntrustTypeName);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Status"] = task_data->Status;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["TriggerPrice"] = task_data->TriggerPrice;
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["TriggerTime"] = toUtf(task_data->TriggerTime);
		data["ReasonDesc"] = toUtf(task_data->ReasonDesc);
		data["EntrustDate"] = toUtf(task_data->EntrustDate);
		data["ExpireDate"] = toUtf(task_data->ExpireDate);
		data["TriggerDate"] = toUtf(task_data->TriggerDate);
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["CmdType"] = toUtf(task_data->CmdType);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryConditionOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryConditionOrderTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionOrderMatchField *task_data = (CThostFtdcRspConditionOrderMatchField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["EntrustType"] = task_data->EntrustType;
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MatchVolumn"] = task_data->MatchVolumn;
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchTime"] = toUtf(task_data->MatchTime);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryConditionOrderTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryClientSessionInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspClientSessionField *task_data = (CThostFtdcRspClientSessionField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SessionID"] = task_data->SessionID;
		data["IdDiffCode"] = toUtf(task_data->IdDiffCode);
		data["CurLoginIp"] = toUtf(task_data->CurLoginIp);
		data["CurMacAddress"] = toUtf(task_data->CurMacAddress);
		data["Status"] = toUtf(task_data->Status);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["LoginDate"] = toUtf(task_data->LoginDate);
		data["LogoutTime"] = toUtf(task_data->LogoutTime);
		data["LogoutDate"] = toUtf(task_data->LogoutDate);
		data["FailNumber"] = task_data->FailNumber;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClientSessionInfo(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryQuotation(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcDepthMarketDataField *task_data = (CThostFtdcDepthMarketDataField*)task->task_data;
		data["InstID"] = toUtf(task_data->InstID);
		data["Name"] = toUtf(task_data->Name);
		data["MarketName"] = toUtf(task_data->MarketName);
		data["PreSettle"] = task_data->PreSettle;
		data["PreClose"] = task_data->PreClose;
		data["Open"] = task_data->Open;
		data["High"] = task_data->High;
		data["Low"] = task_data->Low;
		data["Last"] = task_data->Last;
		data["Close"] = task_data->Close;
		data["Bid1"] = task_data->Bid1;
		data["BidLot1"] = task_data->BidLot1;
		data["Ask1"] = task_data->Ask1;
		data["AskLot1"] = task_data->AskLot1;
		data["Bid2"] = task_data->Bid2;
		data["BidLot2"] = task_data->BidLot2;
		data["Ask2"] = task_data->Ask2;
		data["AskLot2"] = task_data->AskLot2;
		data["Bid3"] = task_data->Bid3;
		data["BidLot3"] = task_data->BidLot3;
		data["Ask3"] = task_data->Ask3;
		data["AskLot3"] = task_data->AskLot3;
		data["Bid4"] = task_data->Bid4;
		data["BidLot4"] = task_data->BidLot4;
		data["Ask4"] = task_data->Ask4;
		data["AskLot4"] = task_data->AskLot4;
		data["Bid5"] = task_data->Bid5;
		data["BidLot5"] = task_data->BidLot5;
		data["Ask5"] = task_data->Ask5;
		data["AskLot5"] = task_data->AskLot5;
		data["Bid6"] = task_data->Bid6;
		data["BidLot6"] = task_data->BidLot6;
		data["Ask6"] = task_data->Ask6;
		data["AskLot6"] = task_data->AskLot6;
		data["Bid7"] = task_data->Bid7;
		data["BidLot7"] = task_data->BidLot7;
		data["Ask7"] = task_data->Ask7;
		data["AskLot7"] = task_data->AskLot7;
		data["Bid8"] = task_data->Bid8;
		data["BidLot8"] = task_data->BidLot8;
		data["Ask8"] = task_data->Ask8;
		data["AskLot8"] = task_data->AskLot8;
		data["Bid9"] = task_data->Bid9;
		data["BidLot9"] = task_data->BidLot9;
		data["Ask9"] = task_data->Ask9;
		data["AskLot9"] = task_data->AskLot9;
		data["Bid10"] = task_data->Bid10;
		data["BidLot10"] = task_data->BidLot10;
		data["Ask10"] = task_data->Ask10;
		data["AskLot10"] = task_data->AskLot10;
		data["Volume"] = task_data->Volume;
		data["OpenInt"] = task_data->OpenInt;
		data["UpDown"] = task_data->UpDown;
		data["Turnover"] = task_data->Turnover;
		data["Settle"] = task_data->Settle;
		data["Average"] = task_data->Average;
		data["QuoteDate"] = toUtf(task_data->QuoteDate);
		data["QuoteTime"] = toUtf(task_data->QuoteTime);
		data["weight"] = task_data->weight;
		data["highLimit"] = task_data->highLimit;
		data["lowLimit"] = task_data->lowLimit;
		data["UpDownRate"] = task_data->UpDownRate;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryQuotation(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorPositionDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInvestorPositionDetailField *task_data = (CThostFtdcInvestorPositionDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ClientShortName"] = toUtf(task_data->ClientShortName);
		data["Data"] = toUtf(task_data->Data);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["Volumn"] = task_data->Volumn;
		data["Settle"] = task_data->Settle;
		data["OpenFlagData"] = toUtf(task_data->OpenFlagData);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryInvestorPositionDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryETFradeDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryETFradeDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryETFPcfDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFPcfDetailField *task_data = (CThostFtdcETFPcfDetailField*)task->task_data;
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["TMoneydiff1"] = task_data->TMoneydiff1;
		data["TPreMoneydiff1"] = task_data->TPreMoneydiff1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["TMoneydiff2"] = task_data->TMoneydiff2;
		data["TPreMoneydiff2"] = task_data->TPreMoneydiff2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["TMoneydiff3"] = task_data->TMoneydiff3;
		data["TPreMoneydiff3"] = task_data->TPreMoneydiff3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["TMoneydiff4"] = task_data->TMoneydiff4;
		data["TPreMoneydiff4"] = task_data->TPreMoneydiff4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["TMoneydiff5"] = task_data->TMoneydiff5;
		data["TPreMoneydiff5"] = task_data->TPreMoneydiff5;
		data["minTradeWeight"] = task_data->minTradeWeight;
		data["TodayPurchaseMaxLimit"] = task_data->TodayPurchaseMaxLimit;
		data["TodayRedeemMaxLimit"] = task_data->TodayRedeemMaxLimit;
		data["TodayAllow"] = task_data->TodayAllow;
		data["PreETFWeight"] = task_data->PreETFWeight;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryETFPcfDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspModifyPassword(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcModifyPasswordRsqField *task_data = (CThostFtdcModifyPasswordRsqField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspModifyPassword(data, error, task->task_id, task->task_last);
};

void TdApi::processRspB0CMoneyIO(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcBOCMoneyIORspField *task_data = (CThostFtdcBOCMoneyIORspField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspB0CMoneyIO(data, error, task->task_id, task->task_last);
};

