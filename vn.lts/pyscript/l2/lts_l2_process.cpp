void L2MdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void L2MdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void L2MdApi::processHeartBeatWarning(Task task)
{
	PyLock lock;
	this->onHeartBeatWarning(task.task_id);
};

void L2MdApi::processRspError(Task task)
{
	PyLock lock;
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void L2MdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CSecurityFtdcUserLoginField task_data = any_cast<CSecurityFtdcUserLoginField>(task.task_data);
	dict data;
	data["TradingDay"] = task_data.TradingDay;
	data["Password"] = task_data.Password;
	data["BrokerID"] = task_data.BrokerID;
	data["DataLevel"] = task_data.DataLevel;
	data["UserID"] = task_data.UserID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CSecurityFtdcUserLogoutField task_data = any_cast<CSecurityFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspSubL2MarketData(Task task)
{
	PyLock lock;
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubL2MarketData(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspUnSubL2MarketData(Task task)
{
	PyLock lock;
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubL2MarketData(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspSubL2Index(Task task)
{
	PyLock lock;
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubL2Index(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspUnSubL2Index(Task task)
{
	PyLock lock;
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubL2Index(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRtnL2MarketData(Task task)
{
	PyLock lock;
	CSecurityFtdcL2MarketDataField task_data = any_cast<CSecurityFtdcL2MarketDataField>(task.task_data);
	dict data;
	data["BidCount8"] = task_data.BidCount8;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidPrice9"] = task_data.BidPrice9;
	data["BidPrice8"] = task_data.BidPrice8;
	data["OfferVolume8"] = task_data.OfferVolume8;
	data["OfferCount9"] = task_data.OfferCount9;
	data["BidPrice5"] = task_data.BidPrice5;
	data["LowPrice"] = task_data.LowPrice;
	data["BidPrice7"] = task_data.BidPrice7;
	data["AltWeightedAvgOfferPrice"] = task_data.AltWeightedAvgOfferPrice;
	data["BidPrice1"] = task_data.BidPrice1;
	data["OfferCount3"] = task_data.OfferCount3;
	data["TotalTradeVolume"] = task_data.TotalTradeVolume;
	data["BidPrice2"] = task_data.BidPrice2;
	data["BidVolume1"] = task_data.BidVolume1;
	data["OfferVolume3"] = task_data.OfferVolume3;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["OfferVolumeA"] = task_data.OfferVolumeA;
	data["BidCount3"] = task_data.BidCount3;
	data["BidCount2"] = task_data.BidCount2;
	data["BidCount1"] = task_data.BidCount1;
	data["BidPriceLevel"] = task_data.BidPriceLevel;
	data["BidCount7"] = task_data.BidCount7;
	data["BidCount6"] = task_data.BidCount6;
	data["BidCount5"] = task_data.BidCount5;
	data["BidCount4"] = task_data.BidCount4;
	data["BidVolume7"] = task_data.BidVolume7;
	data["BidVolume6"] = task_data.BidVolume6;
	data["TotalOfferVolume"] = task_data.TotalOfferVolume;
	data["TotalBidVolume"] = task_data.TotalBidVolume;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["OpenPrice"] = task_data.OpenPrice;
	data["OfferPriceA"] = task_data.OfferPriceA;
	data["OfferCount7"] = task_data.OfferCount7;
	data["OfferCount6"] = task_data.OfferCount6;
	data["TradeCount"] = task_data.TradeCount;
	data["BidPrice4"] = task_data.BidPrice4;
	data["WeightedAvgOfferPrice"] = task_data.WeightedAvgOfferPrice;
	data["OfferVolume6"] = task_data.OfferVolume6;
	data["HighPrice"] = task_data.HighPrice;
	data["OfferVolume9"] = task_data.OfferVolume9;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BidPrice6"] = task_data.BidPrice6;
	data["OfferPrice7"] = task_data.OfferPrice7;
	data["AltWeightedAvgBidPrice"] = task_data.AltWeightedAvgBidPrice;
	data["TimeStamp"] = task_data.TimeStamp;
	data["WeightedAvgBidPrice"] = task_data.WeightedAvgBidPrice;
	data["BidVolume9"] = task_data.BidVolume9;
	data["TotalTradeValue"] = task_data.TotalTradeValue;
	data["OfferCount4"] = task_data.OfferCount4;
	data["TradingDay"] = task_data.TradingDay;
	data["BidCountA"] = task_data.BidCountA;
	data["BidPrice3"] = task_data.BidPrice3;
	data["IOPV"] = task_data.IOPV;
	data["OfferCount1"] = task_data.OfferCount1;
	data["BidVolumeA"] = task_data.BidVolumeA;
	data["OfferPrice9"] = task_data.OfferPrice9;
	data["BidCount9"] = task_data.BidCount9;
	data["OfferPrice8"] = task_data.OfferPrice8;
	data["YieldToMaturity"] = task_data.YieldToMaturity;
	data["LastPrice"] = task_data.LastPrice;
	data["OfferCount8"] = task_data.OfferCount8;
	data["OfferPrice4"] = task_data.OfferPrice4;
	data["OfferPrice5"] = task_data.OfferPrice5;
	data["OfferPrice6"] = task_data.OfferPrice6;
	data["BidVolume8"] = task_data.BidVolume8;
	data["OfferCount5"] = task_data.OfferCount5;
	data["OfferPrice1"] = task_data.OfferPrice1;
	data["OfferPrice2"] = task_data.OfferPrice2;
	data["OfferPrice3"] = task_data.OfferPrice3;
	data["OfferVolume4"] = task_data.OfferVolume4;
	data["OfferVolume5"] = task_data.OfferVolume5;
	data["OfferPriceLevel"] = task_data.OfferPriceLevel;
	data["OfferVolume7"] = task_data.OfferVolume7;
	data["OfferVolume1"] = task_data.OfferVolume1;
	data["OfferVolume2"] = task_data.OfferVolume2;
	data["OfferCount2"] = task_data.OfferCount2;
	data["BidPriceA"] = task_data.BidPriceA;
	data["BidVolume5"] = task_data.BidVolume5;
	data["OfferCountA"] = task_data.OfferCountA;

	this->onRtnL2MarketData(data);
};

void L2MdApi::processRtnL2Index(Task task)
{
	PyLock lock;
	CSecurityFtdcL2IndexField task_data = any_cast<CSecurityFtdcL2IndexField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["HighIndex"] = task_data.HighIndex;
	data["TimeStamp"] = task_data.TimeStamp;
	data["CloseIndex"] = task_data.CloseIndex;
	data["PreCloseIndex"] = task_data.PreCloseIndex;
	data["LastIndex"] = task_data.LastIndex;
	data["TradingDay"] = task_data.TradingDay;
	data["OpenIndex"] = task_data.OpenIndex;
	data["TotalVolume"] = task_data.TotalVolume;
	data["LowIndex"] = task_data.LowIndex;
	data["TurnOver"] = task_data.TurnOver;

	this->onRtnL2Index(data);
};

void L2MdApi::processRspSubL2OrderAndTrade(Task task)
{
	PyLock lock;
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubL2OrderAndTrade(error, task.task_id, task.task_last);
};

void L2MdApi::processRspUnSubL2OrderAndTrade(Task task)
{
	PyLock lock;
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubL2OrderAndTrade(error, task.task_id, task.task_last);
};

void L2MdApi::processRtnL2Order(Task task)
{
	PyLock lock;
	CSecurityFtdcL2OrderField task_data = any_cast<CSecurityFtdcL2OrderField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OrderTime"] = task_data.OrderTime;
	data["OrderKind"] = task_data.OrderKind;
	data["Price"] = task_data.Price;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderGroupID"] = task_data.OrderGroupID;
	data["Volume"] = task_data.Volume;
	data["FunctionCode"] = task_data.FunctionCode;
	data["OrderIndex"] = task_data.OrderIndex;

	this->onRtnL2Order(data);
};

void L2MdApi::processRtnL2Trade(Task task)
{
	PyLock lock;
	CSecurityFtdcL2TradeField task_data = any_cast<CSecurityFtdcL2TradeField>(task.task_data);
	dict data;
	data["TradeGroupID"] = task_data.TradeGroupID;
	data["SellIndex"] = task_data.SellIndex;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderKind"] = task_data.OrderKind;
	data["TradeIndex"] = task_data.TradeIndex;
	data["Price"] = task_data.Price;
	data["InstrumentID"] = task_data.InstrumentID;
	data["BuyIndex"] = task_data.BuyIndex;
	data["Volume"] = task_data.Volume;
	data["FunctionCode"] = task_data.FunctionCode;
	data["TradeTime"] = task_data.TradeTime;

	this->onRtnL2Trade(data);
};

void L2MdApi::processNtfCheckOrderList(Task task)
{
	PyLock lock;
	this->onNtfCheckOrderList();
};

