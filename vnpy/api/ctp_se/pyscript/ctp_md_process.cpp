void MdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void MdApi::processHeartBeatWarning(Task task)
{
	PyLock lock;
	this->onHeartBeatWarning(task.task_id);
};

void MdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CThostFtdcRspUserLoginField task_data = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["SystemName"] = task_data.SystemName;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["LoginTime"] = task_data.LoginTime;
	data["SHFETime"] = task_data.SHFETime;
	data["INETime"] = task_data.INETime;
	data["BrokerID"] = task_data.BrokerID;
	data["UserID"] = task_data.UserID;
	data["DCETime"] = task_data.DCETime;
	data["FrontID"] = task_data.FrontID;
	data["FFEXTime"] = task_data.FFEXTime;
	data["MaxOrderRef"] = task_data.MaxOrderRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = task_error.ErrorMsg;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = task_error.ErrorMsg;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void MdApi::processRspError(Task task)
{
	PyLock lock;
	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = task_error.ErrorMsg;

	this->onRspError(error, task.task_id, task.task_last);
};

void MdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = task_error.ErrorMsg;

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = task_error.ErrorMsg;

	this->onRspUnSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspSubForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = task_error.ErrorMsg;

	this->onRspSubForQuoteRsp(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = task_error.ErrorMsg;

	this->onRspUnSubForQuoteRsp(data, error, task.task_id, task.task_last);
};

void MdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["LowestPrice"] = task_data.LowestPrice;
	data["BidPrice3"] = task_data.BidPrice3;
	data["Volume"] = task_data.Volume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["TradingDay"] = task_data.TradingDay;
	data["AveragePrice"] = task_data.AveragePrice;
	data["OpenInterest"] = task_data.OpenInterest;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["BidVolume4"] = task_data.BidVolume4;
	data["Turnover"] = task_data.Turnover;
	data["AskPrice2"] = task_data.AskPrice2;
	data["AskVolume5"] = task_data.AskVolume5;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["BidVolume2"] = task_data.BidVolume2;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidPrice1"] = task_data.BidPrice1;
	data["AskVolume1"] = task_data.AskVolume1;
	data["OpenPrice"] = task_data.OpenPrice;
	data["AskVolume2"] = task_data.AskVolume2;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ActionDay"] = task_data.ActionDay;
	data["HighestPrice"] = task_data.HighestPrice;
	data["UpdateTime"] = task_data.UpdateTime;
	data["LastPrice"] = task_data.LastPrice;
	data["AskPrice3"] = task_data.AskPrice3;
	data["BidPrice4"] = task_data.BidPrice4;
	data["ClosePrice"] = task_data.ClosePrice;
	data["PreDelta"] = task_data.PreDelta;
	data["BidPrice2"] = task_data.BidPrice2;
	data["AskVolume3"] = task_data.AskVolume3;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["BidVolume1"] = task_data.BidVolume1;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["BidVolume3"] = task_data.BidVolume3;
	data["AskPrice1"] = task_data.AskPrice1;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["AskVolume4"] = task_data.AskVolume4;
	data["CurrDelta"] = task_data.CurrDelta;
	data["AskPrice4"] = task_data.AskPrice4;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["AskPrice5"] = task_data.AskPrice5;

	this->onRtnDepthMarketData(data);
};

void MdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteRspField task_data = any_cast<CThostFtdcForQuoteRspField>(task.task_data);
	dict data;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ForQuoteTime"] = task_data.ForQuoteTime;
	data["ActionDay"] = task_data.ActionDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["TradingDay"] = task_data.TradingDay;

	this->onRtnForQuoteRsp(data);
};

