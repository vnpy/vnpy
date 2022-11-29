void MdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_extra);
};

void MdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_extra);
};

void MdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CIStoneRspInfo *task_error = (CIStoneRspInfo*)task->task_error;
		error["Tid"] = task_error->Tid;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = task_error->ErrorMsg;
		delete task_error;
	}
	this->onRspError(error, task->task_id, task->task_result);
};

void MdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CIStoneRspUserLogin *task_data = (CIStoneRspUserLogin*)task->task_data;
		data["TradingDay"] = task_data->TradingDay;
		data["UserID"] = task_data->UserID;
		data["MaxUserOrderLocalID"] = task_data->MaxUserOrderLocalID;
		data["LoginTime"] = task_data->LoginTime;
		data["userType"] = task_data->userType;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CIStoneRspInfo *task_error = (CIStoneRspInfo*)task->task_error;
		error["Tid"] = task_error->Tid;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = task_error->ErrorMsg;
		delete task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_result);
};

void MdApi::processRspUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CIStoneRspUserLogout *task_data = (CIStoneRspUserLogout*)task->task_data;
		data["UserID"] = task_data->UserID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CIStoneRspInfo *task_error = (CIStoneRspInfo*)task->task_error;
		error["Tid"] = task_error->Tid;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = task_error->ErrorMsg;
		delete task_error;
	}
	this->onRspUserLogout(data, error, task->task_id, task->task_result);
};

void MdApi::processRspSubAllMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSubAllMarketData(task->task_tick, task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspUnSubAllMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspUnSubAllMarketData(task->task_tick, task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspSubAllTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSubAllTickByTick(task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspUnSubAllTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspUnSubAllTickByTick(task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSubMarketData(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspUnSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspUnSubMarketData(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspSubTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSubTickByTick(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspUnSubTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspUnSubTickByTick(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRtnDepthMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CIStoneDepthMarketData *task_data = (CIStoneDepthMarketData*)task->task_data;
		data["ExchangeID"] = task_data->ExchangeID;
		data["TickerType"] = task_data->TickerType;
		data["Ticker"] = task_data->Ticker;
		data["LastPrice"] = task_data->LastPrice;
		data["PreClosePrice"] = task_data->PreClosePrice;
		data["OpenPrice"] = task_data->OpenPrice;
		data["HighestPrice"] = task_data->HighestPrice;
		data["LowestPrice"] = task_data->LowestPrice;
		data["ClosePrice"] = task_data->ClosePrice;
		data["PreOpenInterest"] = task_data->PreOpenInterest;
		data["OpenInterest"] = task_data->OpenInterest;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["SettlementPrice"] = task_data->SettlementPrice;
		data["PreDelta"] = task_data->PreDelta;
		data["CurrDelta"] = task_data->CurrDelta;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["DateTime"] = task_data->DateTime;
		data["Qty"] = task_data->Qty;
		data["Turnover"] = task_data->Turnover;
		data["AvgPrice"] = task_data->AvgPrice;
		data["Bid"] = task_data->Bid;
		data["Ask"] = task_data->Ask;
		data["BidQty"] = task_data->BidQty;
		data["AskQty"] = task_data->AskQty;
		data["TradesCount"] = task_data->TradesCount;
		data["TickerStatus"] = task_data->TickerStatus;
		data["tickBid1"] = task_data->tickBid1;
		data["DataType"] = task_data->DataType;
		data["Stk"] = task_data->Stk;
		data["Opt"] = task_data->Opt;
		data["R4"] = task_data->R4;
		delete task_data;
	}
	this->onRtnDepthMarketData(data);
};

void MdApi::processRtnTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CIStoneTickByTick *task_data = (CIStoneTickByTick*)task->task_data;
		data["ExchangeID"] = task_data->ExchangeID;
		data["Ticker"] = task_data->Ticker;
		data["Seq"] = task_data->Seq;
		data["DataTime"] = task_data->DataTime;
		data["Type"] = task_data->Type;
		data["Entrust"] = task_data->Entrust;
		data["Trade"] = task_data->Trade;
		delete task_data;
	}
	this->onRtnTickByTick(data);
};

void MdApi::processRtnOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CIStoneOrderBook *task_data = (CIStoneOrderBook*)task->task_data;
		data["ExchangeID"] = task_data->ExchangeID;
		data["Ticker"] = task_data->Ticker;
		data["LastPrice"] = task_data->LastPrice;
		data["Qty"] = task_data->Qty;
		data["Turnover"] = task_data->Turnover;
		data["TradesCount"] = task_data->TradesCount;
		data["Bid"] = task_data->Bid;
		data["Ask"] = task_data->Ask;
		data["BidQty"] = task_data->BidQty;
		data["AskQty"] = task_data->AskQty;
		data["DataTime"] = task_data->DataTime;
		data["bidSeq"] = task_data->bidSeq;
		data["askSeq"] = task_data->askSeq;
		delete task_data;
	}
	this->onRtnOrderBook(data);
};

void MdApi::processRspSubOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSubOrderBook(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspUnSubOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspUnSubOrderBook(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

