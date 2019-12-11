void MdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void MdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_id);
};

void MdApi::processPackageStart(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageStart(task->task_id, task->task_id);
};

void MdApi::processPackageEnd(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageEnd(task->task_id, task->task_id);
};

void MdApi::processRspError(Task *task)
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

void MdApi::processRspUserLogin(Task *task)
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

void MdApi::processRspUserLogout(Task *task)
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

void MdApi::processRtnDepthMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcDepthMarketDataField *task_data = (CUstpFtdcDepthMarketDataField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["SettlementGroupID"] = toUtf(task_data->SettlementGroupID);
		data["SettlementID"] = task_data->SettlementID;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["PreClosePrice"] = task_data->PreClosePrice;
		data["PreOpenInterest"] = task_data->PreOpenInterest;
		data["PreDelta"] = task_data->PreDelta;
		data["OpenPrice"] = task_data->OpenPrice;
		data["HighestPrice"] = task_data->HighestPrice;
		data["LowestPrice"] = task_data->LowestPrice;
		data["ClosePrice"] = task_data->ClosePrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["SettlementPrice"] = task_data->SettlementPrice;
		data["CurrDelta"] = task_data->CurrDelta;
		data["LastPrice"] = task_data->LastPrice;
		data["Volume"] = task_data->Volume;
		data["Turnover"] = task_data->Turnover;
		data["OpenInterest"] = task_data->OpenInterest;
		data["BidPrice1"] = task_data->BidPrice1;
		data["BidVolume1"] = task_data->BidVolume1;
		data["AskPrice1"] = task_data->AskPrice1;
		data["AskVolume1"] = task_data->AskVolume1;
		data["BidPrice2"] = task_data->BidPrice2;
		data["BidVolume2"] = task_data->BidVolume2;
		data["BidPrice3"] = task_data->BidPrice3;
		data["BidVolume3"] = task_data->BidVolume3;
		data["AskPrice2"] = task_data->AskPrice2;
		data["AskVolume2"] = task_data->AskVolume2;
		data["AskPrice3"] = task_data->AskPrice3;
		data["AskVolume3"] = task_data->AskVolume3;
		data["BidPrice4"] = task_data->BidPrice4;
		data["BidVolume4"] = task_data->BidVolume4;
		data["BidPrice5"] = task_data->BidPrice5;
		data["BidVolume5"] = task_data->BidVolume5;
		data["AskPrice4"] = task_data->AskPrice4;
		data["AskVolume4"] = task_data->AskVolume4;
		data["AskPrice5"] = task_data->AskPrice5;
		data["AskVolume5"] = task_data->AskVolume5;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UpdateTime"] = toUtf(task_data->UpdateTime);
		data["UpdateMillisec"] = task_data->UpdateMillisec;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["HisHighestPrice"] = task_data->HisHighestPrice;
		data["HisLowestPrice"] = task_data->HisLowestPrice;
		data["LatestVolume"] = task_data->LatestVolume;
		data["InitVolume"] = task_data->InitVolume;
		data["ChangeVolume"] = task_data->ChangeVolume;
		data["BidImplyVolume"] = task_data->BidImplyVolume;
		data["AskImplyVolume"] = task_data->AskImplyVolume;
		data["AvgPrice"] = task_data->AvgPrice;
		data["ArbiType"] = task_data->ArbiType;
		data["InstrumentID_1"] = toUtf(task_data->InstrumentID_1);
		data["InstrumentID_2"] = toUtf(task_data->InstrumentID_2);
		data["InstrumentName"] = toUtf(task_data->InstrumentName);
		data["TotalBidVolume"] = task_data->TotalBidVolume;
		data["TotalAskVolume"] = task_data->TotalAskVolume;
		delete task->task_data;
	}
	this->onRtnDepthMarketData(data);
};

void MdApi::processRspSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcSpecificInstrumentField *task_data = (CUstpFtdcSpecificInstrumentField*)task->task_data;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
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
	this->onRspSubMarketData(data, error, task->task_id, task->task_last);
};

void MdApi::processRspUnSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcSpecificInstrumentField *task_data = (CUstpFtdcSpecificInstrumentField*)task->task_data;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
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
	this->onRspUnSubMarketData(data, error, task->task_id, task->task_last);
};

void MdApi::processRspGetMarketTopic(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspMarketTopicField *task_data = (CUstpFtdcRspMarketTopicField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["TopicID"] = task_data->TopicID;
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
	this->onRspGetMarketTopic(data, error, task->task_id, task->task_last);
};

void MdApi::processRspGetMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspDepthMarketDataField *task_data = (CUstpFtdcRspDepthMarketDataField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["SettlementGroupID"] = toUtf(task_data->SettlementGroupID);
		data["SettlementID"] = task_data->SettlementID;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["PreClosePrice"] = task_data->PreClosePrice;
		data["PreOpenInterest"] = task_data->PreOpenInterest;
		data["PreDelta"] = task_data->PreDelta;
		data["OpenPrice"] = task_data->OpenPrice;
		data["HighestPrice"] = task_data->HighestPrice;
		data["LowestPrice"] = task_data->LowestPrice;
		data["ClosePrice"] = task_data->ClosePrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["SettlementPrice"] = task_data->SettlementPrice;
		data["CurrDelta"] = task_data->CurrDelta;
		data["LastPrice"] = task_data->LastPrice;
		data["Volume"] = task_data->Volume;
		data["Turnover"] = task_data->Turnover;
		data["OpenInterest"] = task_data->OpenInterest;
		data["BidPrice1"] = task_data->BidPrice1;
		data["BidVolume1"] = task_data->BidVolume1;
		data["AskPrice1"] = task_data->AskPrice1;
		data["AskVolume1"] = task_data->AskVolume1;
		data["BidPrice2"] = task_data->BidPrice2;
		data["BidVolume2"] = task_data->BidVolume2;
		data["BidPrice3"] = task_data->BidPrice3;
		data["BidVolume3"] = task_data->BidVolume3;
		data["AskPrice2"] = task_data->AskPrice2;
		data["AskVolume2"] = task_data->AskVolume2;
		data["AskPrice3"] = task_data->AskPrice3;
		data["AskVolume3"] = task_data->AskVolume3;
		data["BidPrice4"] = task_data->BidPrice4;
		data["BidVolume4"] = task_data->BidVolume4;
		data["BidPrice5"] = task_data->BidPrice5;
		data["BidVolume5"] = task_data->BidVolume5;
		data["AskPrice4"] = task_data->AskPrice4;
		data["AskVolume4"] = task_data->AskVolume4;
		data["AskPrice5"] = task_data->AskPrice5;
		data["AskVolume5"] = task_data->AskVolume5;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UpdateTime"] = toUtf(task_data->UpdateTime);
		data["UpdateMillisec"] = task_data->UpdateMillisec;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["HisHighestPrice"] = task_data->HisHighestPrice;
		data["HisLowestPrice"] = task_data->HisLowestPrice;
		data["LatestVolume"] = task_data->LatestVolume;
		data["InitVolume"] = task_data->InitVolume;
		data["ChangeVolume"] = task_data->ChangeVolume;
		data["BidImplyVolume"] = task_data->BidImplyVolume;
		data["AskImplyVolume"] = task_data->AskImplyVolume;
		data["AvgPrice"] = task_data->AvgPrice;
		data["ArbiType"] = task_data->ArbiType;
		data["InstrumentID_1"] = toUtf(task_data->InstrumentID_1);
		data["InstrumentID_2"] = toUtf(task_data->InstrumentID_2);
		data["InstrumentName"] = toUtf(task_data->InstrumentName);
		data["TotalBidVolume"] = task_data->TotalBidVolume;
		data["TotalAskVolume"] = task_data->TotalAskVolume;
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
	this->onRspGetMarketData(data, error, task->task_id, task->task_last);
};

