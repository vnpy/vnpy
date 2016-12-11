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

void MdApi::processPackageStart(Task task)
{
	PyLock lock;
	this->onPackageStart(task.task_id, task.task_id);
};

void MdApi::processPackageEnd(Task task)
{
	PyLock lock;
	this->onPackageEnd(task.task_id, task.task_id);
};

void MdApi::processRspError(Task task)
{
	PyLock lock;
	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLoginField task_data = any_cast<CQdpFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["PrivateFlowSize"] = task_data.PrivateFlowSize;
	data["UserID"] = task_data.UserID;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxOrderLocalID"] = task_data.MaxOrderLocalID;
	data["TradingSystemName"] = task_data.TradingSystemName;
	data["FrontID"] = task_data.FrontID;
	data["LoginTime"] = task_data.LoginTime;
	data["UserFlowSize"] = task_data.UserFlowSize;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLogoutField task_data = any_cast<CQdpFtdcRspUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void MdApi::processRtnQmdInstrumentStatu(Task task)
{
	PyLock lock;
	CQdpFtdcQmdInstrumentStateField task_data = any_cast<CQdpFtdcQmdInstrumentStateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["ExchangeID"] = task_data.ExchangeID;

	this->onRtnQmdInstrumentStatu(data);
};

void MdApi::processRspSubscribeTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubscribeTopic(data, error, task.task_id, task.task_last);
};

void MdApi::processRspQryTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTopic(data, error, task.task_id, task.task_last);
};

void MdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcDepthMarketDataField task_data = any_cast<CQdpFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["HighestPrice"] = task_data.HighestPrice;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidPrice1"] = task_data.BidPrice1;
	data["BidPrice3"] = task_data.BidPrice3;
	data["BidPrice2"] = task_data.BidPrice2;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["SettlementGroupID"] = task_data.SettlementGroupID;
	data["BidVolume2"] = task_data.BidVolume2;
	data["BidVolume1"] = task_data.BidVolume1;
	data["AskPrice2"] = task_data.AskPrice2;
	data["Volume"] = task_data.Volume;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["AskVolume5"] = task_data.AskVolume5;
	data["AskVolume4"] = task_data.AskVolume4;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["BidPrice4"] = task_data.BidPrice4;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
	data["SettlementID"] = task_data.SettlementID;
	data["TradingDay"] = task_data.TradingDay;
	data["PreDelta"] = task_data.PreDelta;
	data["OpenInterest"] = task_data.OpenInterest;
	data["CurrDelta"] = task_data.CurrDelta;
	data["Turnover"] = task_data.Turnover;
	data["LastPrice"] = task_data.LastPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["OpenPrice"] = task_data.OpenPrice;
	data["LowestPrice"] = task_data.LowestPrice;

	this->onRtnDepthMarketData(data);
};

void MdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcSpecificInstrumentField task_data = any_cast<CQdpFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcSpecificInstrumentField task_data = any_cast<CQdpFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcRspMarketDataField task_data = any_cast<CQdpFtdcRspMarketDataField>(task.task_data);
	dict data;
	data["HighestPrice"] = task_data.HighestPrice;
	data["BidPrice1"] = task_data.BidPrice1;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["SettlementGroupID"] = task_data.SettlementGroupID;
	data["BidVolume1"] = task_data.BidVolume1;
	data["Volume"] = task_data.Volume;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
	data["SettlementID"] = task_data.SettlementID;
	data["TradingDay"] = task_data.TradingDay;
	data["PreDelta"] = task_data.PreDelta;
	data["OpenInterest"] = task_data.OpenInterest;
	data["CurrDelta"] = task_data.CurrDelta;
	data["Turnover"] = task_data.Turnover;
	data["LastPrice"] = task_data.LastPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["OpenPrice"] = task_data.OpenPrice;
	data["LowestPrice"] = task_data.LowestPrice;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};

