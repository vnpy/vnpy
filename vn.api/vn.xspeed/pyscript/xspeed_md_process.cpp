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

void MdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	DFITCUserLoginInfoRtnField task_data = any_cast<DFITCUserLoginInfoRtnField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["initLocalOrderID"] = task_data.initLocalOrderID;
	data["SHFETime"] = task_data.SHFETime;
	data["errorMsg"] = task_data.errorMsg;
	data["INETime"] = task_data.INETime;
	data["lRequestID"] = task_data.lRequestID;
	data["loginResult"] = task_data.loginResult;
	data["sessionID"] = task_data.sessionID;
	data["nErrorID"] = task_data.nErrorID;
	data["CFFEXTime"] = task_data.CFFEXTime;
	data["DCEtime"] = task_data.DCEtime;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUserLogin(data, error);
};

void MdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	DFITCUserLogoutInfoRtnField task_data = any_cast<DFITCUserLogoutInfoRtnField>(task.task_data);
	dict data;
	data["logoutResult"] = task_data.logoutResult;
	data["lRequestID"] = task_data.lRequestID;
	data["nErrorID"] = task_data.nErrorID;
	data["errorMsg"] = task_data.errorMsg;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUserLogout(data, error);
};

void MdApi::processRspError(Task task)
{
	PyLock lock;
	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspError(error);
};

void MdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspSubMarketData(data, error);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUnSubMarketData(data, error);
};

void MdApi::processRspSubForQuoteRsp(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspSubForQuoteRsp(data, error);
};

void MdApi::processRspUnSubForQuoteRsp(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUnSubForQuoteRsp(data, error);
};

void MdApi::processMarketData(Task task)
{
	PyLock lock;
	DFITCDepthMarketDataField task_data = any_cast<DFITCDepthMarketDataField>(task.task_data);
	dict data;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidPrice4"] = task_data.BidPrice4;
	data["BidPrice1"] = task_data.BidPrice1;
	data["openPrice"] = task_data.openPrice;
	data["BidPrice2"] = task_data.BidPrice2;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["AskPrice2"] = task_data.AskPrice2;
	data["AskPrice1"] = task_data.AskPrice1;
	data["closePrice"] = task_data.closePrice;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["AveragePrice"] = task_data.AveragePrice;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["BidVolume1"] = task_data.BidVolume1;
	data["Volume"] = task_data.Volume;
	data["tradingDay"] = task_data.tradingDay;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["lowerLimitPrice"] = task_data.lowerLimitPrice;
	data["AskVolume4"] = task_data.AskVolume4;
	data["preDelta"] = task_data.preDelta;
	data["AskVolume5"] = task_data.AskVolume5;
	data["openInterest"] = task_data.openInterest;
	data["currDelta"] = task_data.currDelta;
	data["preClosePrice"] = task_data.preClosePrice;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["lastPrice"] = task_data.lastPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["settlementPrice"] = task_data.settlementPrice;
	data["preOpenInterest"] = task_data.preOpenInterest;
	data["exchangeInstID"] = task_data.exchangeInstID;
	data["XSpeedTime"] = task_data.XSpeedTime;
	data["BidPrice3"] = task_data.BidPrice3;
	data["upperLimitPrice"] = task_data.upperLimitPrice;
	data["lowestPrice"] = task_data.lowestPrice;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["highestPrice"] = task_data.highestPrice;
	data["turnover"] = task_data.turnover;

	this->onMarketData(data);
};

void MdApi::processCustomMarketData(Task task)
{
	PyLock lock;
	DFITCCustomMarketDataField task_data = any_cast<DFITCCustomMarketDataField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["lastPrice"] = task_data.lastPrice;
	data["bidPrice1"] = task_data.bidPrice1;
	data["bidVolume1"] = task_data.bidVolume1;
	data["askVolume1"] = task_data.askVolume1;
	data["askPrice1"] = task_data.askPrice1;

	this->onCustomMarketData(data);
};

void MdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	DFITCQuoteSubscribeRtnField task_data = any_cast<DFITCQuoteSubscribeRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["source"] = task_data.source;
	data["exchangeID"] = task_data.exchangeID;
	data["quoteID"] = task_data.quoteID;
	data["quoteTime"] = task_data.quoteTime;

	this->onRtnForQuoteRsp(data);
};

void MdApi::processRspTradingDay(Task task)
{
	PyLock lock;
	DFITCTradingDayRtnField task_data = any_cast<DFITCTradingDayRtnField>(task.task_data);
	dict data;
	data["date"] = task_data.date;
	data["lRequestID"] = task_data.lRequestID;

	this->onRspTradingDay(data);
};

