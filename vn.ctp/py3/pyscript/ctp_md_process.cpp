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
	data["SessionID"] = task_data.SessionID;
	data["MaxOrderRef"] = boost::locale::conv::to_utf<char>(task_data.MaxOrderRef, std::string("GB2312"));
	data["LoginTime"] = boost::locale::conv::to_utf<char>(task_data.LoginTime, std::string("GB2312"));
	data["FFEXTime"] = boost::locale::conv::to_utf<char>(task_data.FFEXTime, std::string("GB2312"));
	data["SystemName"] = boost::locale::conv::to_utf<char>(task_data.SystemName, std::string("GB2312"));
	data["CZCETime"] = boost::locale::conv::to_utf<char>(task_data.CZCETime, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["DCETime"] = boost::locale::conv::to_utf<char>(task_data.DCETime, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["INETime"] = boost::locale::conv::to_utf<char>(task_data.INETime, std::string("GB2312"));
	data["SHFETime"] = boost::locale::conv::to_utf<char>(task_data.SHFETime, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void MdApi::processRspError(Task task)
{
	PyLock lock;
	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspError(error, task.task_id, task.task_last);
};

void MdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUnSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspSubForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspSubForQuoteRsp(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUnSubForQuoteRsp(data, error, task.task_id, task.task_last);
};

void MdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["AskPrice5"] = task_data.AskPrice5;
	data["CurrDelta"] = task_data.CurrDelta;
	data["AskPrice2"] = task_data.AskPrice2;
	data["BidPrice4"] = task_data.BidPrice4;
	data["AveragePrice"] = task_data.AveragePrice;
	data["AskVolume4"] = task_data.AskVolume4;
	data["BidPrice1"] = task_data.BidPrice1;
	data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
	data["AskPrice4"] = task_data.AskPrice4;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["LastPrice"] = task_data.LastPrice;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["BidPrice2"] = task_data.BidPrice2;
	data["BidPrice3"] = task_data.BidPrice3;
	data["HighestPrice"] = task_data.HighestPrice;
	data["AskPrice3"] = task_data.AskPrice3;
	data["BidVolume5"] = task_data.BidVolume5;
	data["ActionDay"] = boost::locale::conv::to_utf<char>(task_data.ActionDay, std::string("GB2312"));
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["BidVolume4"] = task_data.BidVolume4;
	data["AskVolume2"] = task_data.AskVolume2;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["AskVolume3"] = task_data.AskVolume3;
	data["Volume"] = task_data.Volume;
	data["Turnover"] = task_data.Turnover;
	data["BidPrice5"] = task_data.BidPrice5;
	data["AskVolume5"] = task_data.AskVolume5;
	data["OpenPrice"] = task_data.OpenPrice;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["OpenInterest"] = task_data.OpenInterest;
	data["ClosePrice"] = task_data.ClosePrice;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["BidVolume1"] = task_data.BidVolume1;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["AskVolume1"] = task_data.AskVolume1;
	data["AskPrice1"] = task_data.AskPrice1;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LowestPrice"] = task_data.LowestPrice;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["PreDelta"] = task_data.PreDelta;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));

	this->onRtnDepthMarketData(data);
};

void MdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteRspField task_data = any_cast<CThostFtdcForQuoteRspField>(task.task_data);
	dict data;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
	data["ForQuoteTime"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteTime, std::string("GB2312"));
	data["ActionDay"] = boost::locale::conv::to_utf<char>(task_data.ActionDay, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));

	this->onRtnForQuoteRsp(data);
};

