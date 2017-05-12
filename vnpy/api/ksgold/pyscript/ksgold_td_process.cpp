void TdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CThostFtdcRspUserLoginField task_data = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["SeatNo"] = task_data.SeatNo;
	data["tradeDate"] = task_data.tradeDate;
	data["tradeCode"] = task_data.tradeCode;
	data["localOrderNo"] = task_data.localOrderNo;
	data["loginbatch"] = task_data.loginbatch;
	data["clientID"] = task_data.clientID;
	data["lastLoginDate"] = task_data.lastLoginDate;
	data["lastLoginTime"] = task_data.lastLoginTime;
	data["lastLoginIp"] = task_data.lastLoginIp;
	data["clientName"] = task_data.clientName;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["traderID"] = task_data.traderID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processNtyMktStatus(Task task)
{
	PyLock lock;
	this->onNtyMktStatus();
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentField task_data = any_cast<CThostFtdcInstrumentField>(task.task_data);
	dict data;
	data["exchangeID"] = task_data.exchangeID;
	data["tradeState"] = task_data.tradeState;
	data["name"] = task_data.name;
	data["lowerLimit"] = task_data.lowerLimit;
	data["openFlag"] = task_data.openFlag;
	data["instID"] = task_data.instID;
	data["marketType"] = task_data.marketType;
	data["marketID"] = task_data.marketID;
	data["varietyType"] = task_data.varietyType;
	data["maxHand"] = task_data.maxHand;
	data["minHand"] = task_data.minHand;
	data["tick"] = task_data.tick;
	data["varietyID"] = task_data.varietyID;
	data["unit"] = task_data.unit;
	data["upperLimit"] = task_data.upperLimit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["AskLot3"] = task_data.AskLot3;
	data["AskLot2"] = task_data.AskLot2;
	data["AskLot1"] = task_data.AskLot1;
	data["AskLot5"] = task_data.AskLot5;
	data["AskLot4"] = task_data.AskLot4;
	data["InstID"] = task_data.InstID;
	data["Bid5"] = task_data.Bid5;
	data["Bid4"] = task_data.Bid4;
	data["Bid3"] = task_data.Bid3;
	data["Bid2"] = task_data.Bid2;
	data["Bid1"] = task_data.Bid1;
	data["Low"] = task_data.Low;
	data["Ask1"] = task_data.Ask1;
	data["PreClose"] = task_data.PreClose;
	data["weight"] = task_data.weight;
	data["QuoteDate"] = task_data.QuoteDate;
	data["lowLimit"] = task_data.lowLimit;
	data["Volume"] = task_data.Volume;
	data["Average"] = task_data.Average;
	data["Ask5"] = task_data.Ask5;
	data["Ask4"] = task_data.Ask4;
	data["PreSettle"] = task_data.PreSettle;
	data["Last"] = task_data.Last;
	data["Name"] = task_data.Name;
	data["Ask3"] = task_data.Ask3;
	data["Ask2"] = task_data.Ask2;
	data["BidLot1"] = task_data.BidLot1;
	data["UpDown"] = task_data.UpDown;
	data["BidLot3"] = task_data.BidLot3;
	data["BidLot2"] = task_data.BidLot2;
	data["BidLot5"] = task_data.BidLot5;
	data["BidLot4"] = task_data.BidLot4;
	data["UpDownRate"] = task_data.UpDownRate;
	data["MarketName"] = task_data.MarketName;
	data["OpenInt"] = task_data.OpenInt;
	data["QuoteTime"] = task_data.QuoteTime;
	data["Turnover"] = task_data.Turnover;
	data["highLimit"] = task_data.highLimit;
	data["High"] = task_data.High;
	data["Settle"] = task_data.Settle;
	data["Close"] = task_data.Close;
	data["Open"] = task_data.Open;

	this->onRtnDepthMarketData(data);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["offsetFlag"] = task_data.offsetFlag;
	data["buyOrSell"] = task_data.buyOrSell;
	data["middleFlag"] = task_data.middleFlag;
	data["tradeCode"] = task_data.tradeCode;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["marketID"] = task_data.marketID;
	data["trigPrice"] = task_data.trigPrice;
	data["amount"] = task_data.amount;
	data["seatID"] = task_data.seatID;
	data["priceFlag"] = task_data.priceFlag;
	data["LocalOrderNo"] = task_data.LocalOrderNo;
	data["tradeWay"] = task_data.tradeWay;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["offsetFlag"] = task_data.offsetFlag;
	data["buyOrSell"] = task_data.buyOrSell;
	data["middleFlag"] = task_data.middleFlag;
	data["tradeCode"] = task_data.tradeCode;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["marketID"] = task_data.marketID;
	data["trigPrice"] = task_data.trigPrice;
	data["amount"] = task_data.amount;
	data["seatID"] = task_data.seatID;
	data["priceFlag"] = task_data.priceFlag;
	data["LocalOrderNo"] = task_data.LocalOrderNo;
	data["tradeWay"] = task_data.tradeWay;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderRtnField task_data = any_cast<CThostFtdcOrderRtnField>(task.task_data);
	dict data;
	data["status"] = task_data.status;
	data["orderNo"] = task_data.orderNo;
	data["localOrderNo"] = task_data.localOrderNo;
	data["cancelQty"] = task_data.cancelQty;

	this->onRtnOrder(data);
};

void TdApi::processForceLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["traderID"] = task_data.traderID;

	this->onForceLogout(data);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderActionField task_data = any_cast<CThostFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["status"] = task_data.status;
	data["localOrderNo"] = task_data.localOrderNo;
	data["marketID"] = task_data.marketID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcOrderActionField task_data = any_cast<CThostFtdcOrderActionField>(task.task_data);
	dict data;
	data["tradeWay"] = task_data.tradeWay;
	data["localOrderNo"] = task_data.localOrderNo;
	data["marketID"] = task_data.marketID;
	data["traderID"] = task_data.traderID;
	data["orderFlag"] = task_data.orderFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["offSetFlag"] = task_data.offSetFlag;
	data["buyOrSell"] = task_data.buyOrSell;
	data["order_flag"] = task_data.order_flag;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["trade_fee"] = task_data.trade_fee;
	data["weight"] = task_data.weight;
	data["marketID"] = task_data.marketID;
	data["volume"] = task_data.volume;
	data["matchTime"] = task_data.matchTime;
	data["amount"] = task_data.amount;
	data["matchNo"] = task_data.matchNo;
	data["orderNo"] = task_data.orderNo;
	data["tradeWay"] = task_data.tradeWay;
	data["forcebatchnum"] = task_data.forcebatchnum;
	data["localOrderNo"] = task_data.localOrderNo;
	data["matchDate"] = task_data.matchDate;
	data["forceoffset_flag"] = task_data.forceoffset_flag;

	this->onRtnTrade(data);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountField task_data = any_cast<CThostFtdcTradingAccountField>(task.task_data);
	dict data;
	data["available"] = task_data.available;
	data["buyPosiMargin"] = task_data.buyPosiMargin;
	data["totalFrozen"] = task_data.totalFrozen;
	data["spotSellFrozen"] = task_data.spotSellFrozen;
	data["middleMargin"] = task_data.middleMargin;
	data["posiMargin"] = task_data.posiMargin;
	data["storageMargin"] = task_data.storageMargin;
	data["availCap"] = task_data.availCap;
	data["todayOut"] = task_data.todayOut;
	data["pickUpMargin"] = task_data.pickUpMargin;
	data["totalFrozenFee"] = task_data.totalFrozenFee;
	data["lastFrozen"] = task_data.lastFrozen;
	data["todayIn"] = task_data.todayIn;
	data["orderFrozen"] = task_data.orderFrozen;
	data["totalFee"] = task_data.totalFee;
	data["sellPosiMargin"] = task_data.sellPosiMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["status"] = task_data.status;
	data["cancelTime"] = task_data.cancelTime;
	data["offsetFlag"] = task_data.offsetFlag;
	data["buyOrSell"] = task_data.buyOrSell;
	data["instID"] = task_data.instID;
	data["localOrderNo"] = task_data.localOrderNo;
	data["matchQty"] = task_data.matchQty;
	data["weight"] = task_data.weight;
	data["marketID"] = task_data.marketID;
	data["amount"] = task_data.amount;
	data["forceoffset_flag"] = task_data.forceoffset_flag;
	data["entrustTime"] = task_data.entrustTime;
	data["orderNo"] = task_data.orderNo;
	data["cancelQty"] = task_data.cancelQty;
	data["matchWeight"] = task_data.matchWeight;
	data["price"] = task_data.price;
	data["tradeWay"] = task_data.tradeWay;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["offSetFlag"] = task_data.offSetFlag;
	data["buyOrSell"] = task_data.buyOrSell;
	data["order_flag"] = task_data.order_flag;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["trade_fee"] = task_data.trade_fee;
	data["weight"] = task_data.weight;
	data["marketID"] = task_data.marketID;
	data["volume"] = task_data.volume;
	data["matchTime"] = task_data.matchTime;
	data["amount"] = task_data.amount;
	data["matchNo"] = task_data.matchNo;
	data["orderNo"] = task_data.orderNo;
	data["tradeWay"] = task_data.tradeWay;
	data["forcebatchnum"] = task_data.forcebatchnum;
	data["localOrderNo"] = task_data.localOrderNo;
	data["matchDate"] = task_data.matchDate;
	data["forceoffset_flag"] = task_data.forceoffset_flag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionField task_data = any_cast<CThostFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["shortPosiVol"] = task_data.shortPosiVol;
	data["longOpenAvgPrice"] = task_data.longOpenAvgPrice;
	data["lastLong"] = task_data.lastLong;
	data["longPosiVol"] = task_data.longPosiVol;
	data["todayOffsetLong"] = task_data.todayOffsetLong;
	data["shortPosiFrozen"] = task_data.shortPosiFrozen;
	data["instID"] = task_data.instID;
	data["lastShort"] = task_data.lastShort;
	data["todayOffsetShort"] = task_data.todayOffsetShort;
	data["longPosiAvgPrice"] = task_data.longPosiAvgPrice;
	data["longPosi"] = task_data.longPosi;
	data["todayLong"] = task_data.todayLong;
	data["todayShort"] = task_data.todayShort;
	data["shortPosi"] = task_data.shortPosi;
	data["shortOpenAvgPrice"] = task_data.shortOpenAvgPrice;
	data["longPosiFrozen"] = task_data.longPosiFrozen;
	data["shortPosiAvgPrice"] = task_data.shortPosiAvgPrice;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryClientStorage(Task task)
{
	PyLock lock;
	CThostFtdcStorageField task_data = any_cast<CThostFtdcStorageField>(task.task_data);
	dict data;
	data["todayLend"] = task_data.todayLend;
	data["todayBorrow"] = task_data.todayBorrow;
	data["frozenStorage"] = task_data.frozenStorage;
	data["storageCost"] = task_data.storageCost;
	data["varietyName"] = task_data.varietyName;
	data["customType"] = task_data.customType;
	data["lawFrozen"] = task_data.lawFrozen;
	data["impawnStorage"] = task_data.impawnStorage;
	data["todayBuy"] = task_data.todayBuy;
	data["varietyID"] = task_data.varietyID;
	data["pendStorage"] = task_data.pendStorage;
	data["availableStorage"] = task_data.availableStorage;
	data["totalStorage"] = task_data.totalStorage;
	data["impawnFrozen"] = task_data.impawnFrozen;
	data["todayRealDeposit"] = task_data.todayRealDeposit;
	data["todaySell"] = task_data.todaySell;
	data["bankFrozen"] = task_data.bankFrozen;
	data["todayDeposit"] = task_data.todayDeposit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryClientStorage(data, error);
};

void TdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};

