void MdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected(task->task_id);
};

void MdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void MdApi::processRspUserLogin(Task *task)
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

void MdApi::processRspUserLogout(Task *task)
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

void MdApi::processRspError(Task *task)
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

void MdApi::processRspSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcSpecificInstrumentField *task_data = (CThostFtdcSpecificInstrumentField*)task->task_data;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
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
	this->onRspSubMarketData(data, error, task->task_id, task->task_last);
};

void MdApi::processRspUnSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcSpecificInstrumentField *task_data = (CThostFtdcSpecificInstrumentField*)task->task_data;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
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
	this->onRspUnSubMarketData(data, error, task->task_id, task->task_last);
};

void MdApi::processRtnDepthMarketData(Task *task)
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
	this->onRtnDepthMarketData(data);
};

