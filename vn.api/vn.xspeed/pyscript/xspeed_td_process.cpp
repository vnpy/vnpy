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

void TdApi::processRspUserLogout(Task task)
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

void TdApi::processRspInsertOrder(Task task)
{
	PyLock lock;
	DFITCOrderRspDataRtnField task_data = any_cast<DFITCOrderRspDataRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["spdOrderID"] = task_data.spdOrderID;
	data["lRequestID"] = task_data.lRequestID;
	data["speculator"] = task_data.speculator;
	data["orderType"] = task_data.orderType;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;

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

	this->onRspInsertOrder(data, error);
};

void TdApi::processRspCancelOrder(Task task)
{
	PyLock lock;
	DFITCOrderRspDataRtnField task_data = any_cast<DFITCOrderRspDataRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["spdOrderID"] = task_data.spdOrderID;
	data["lRequestID"] = task_data.lRequestID;
	data["speculator"] = task_data.speculator;
	data["orderType"] = task_data.orderType;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;

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

	this->onRspCancelOrder(data, error);
};

void TdApi::processRtnErrorMsg(Task task)
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

	this->onRtnErrorMsg(error);
};

void TdApi::processRtnMatchedInfo(Task task)
{
	PyLock lock;
	DFITCMatchRtnField task_data = any_cast<DFITCMatchRtnField>(task.task_data);
	dict data;
	data["insertType"] = task_data.insertType;
	data["adjustmentInfo"] = task_data.adjustmentInfo;
	data["orderStatus"] = task_data.orderStatus;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["orderType"] = task_data.orderType;
	data["OrderSysID"] = task_data.OrderSysID;
	data["matchType"] = task_data.matchType;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["matchedTime"] = task_data.matchedTime;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["spdOrderID"] = task_data.spdOrderID;
	data["frozenCapita"] = task_data.frozenCapita;
	data["matchID"] = task_data.matchID;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["margin"] = task_data.margin;
	data["turnover"] = task_data.turnover;

	this->onRtnMatchedInfo(data);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	DFITCOrderRtnField task_data = any_cast<DFITCOrderRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["statusMsg"] = task_data.statusMsg;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["OrderSysID"] = task_data.OrderSysID;
	data["instrumentType"] = task_data.instrumentType;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["extSpdOrderID"] = task_data.extSpdOrderID;
	data["sessionID"] = task_data.sessionID;
	data["clientID"] = task_data.clientID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["orderProperty"] = task_data.orderProperty;
	data["speculator"] = task_data.speculator;
	data["reservedType2"] = task_data.reservedType2;
	data["orderType"] = task_data.orderType;
	data["spdOrderID"] = task_data.spdOrderID;
	data["orderStatus"] = task_data.orderStatus;

	this->onRtnOrder(data);
};

void TdApi::processRtnCancelOrder(Task task)
{
	PyLock lock;
	DFITCOrderCanceledRtnField task_data = any_cast<DFITCOrderCanceledRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["statusMsg"] = task_data.statusMsg;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["OrderSysID"] = task_data.OrderSysID;
	data["instrumentType"] = task_data.instrumentType;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["spdOrderID"] = task_data.spdOrderID;
	data["speculator"] = task_data.speculator;
	data["canceledTime"] = task_data.canceledTime;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;

	this->onRtnCancelOrder(data);
};

void TdApi::processRspQryOrderInfo(Task task)
{
	PyLock lock;
	DFITCOrderCommRtnField task_data = any_cast<DFITCOrderCommRtnField>(task.task_data);
	dict data;
	data["commTime"] = task_data.commTime;
	data["orderStatus"] = task_data.orderStatus;
	data["customCategory"] = task_data.customCategory;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["OrderSysID"] = task_data.OrderSysID;
	data["instrumentType"] = task_data.instrumentType;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;
	data["operStation"] = task_data.operStation;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["clientID"] = task_data.clientID;
	data["submitTime"] = task_data.submitTime;
	data["lRequestID"] = task_data.lRequestID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["margin"] = task_data.margin;
	data["openClose"] = task_data.openClose;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["sessionId"] = task_data.sessionId;
	data["reservedType2"] = task_data.reservedType2;
	data["orderType"] = task_data.orderType;
	data["spdOrderID"] = task_data.spdOrderID;
	data["insertType"] = task_data.insertType;

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

	this->onRspQryOrderInfo(data, error, task.task_last);
};

void TdApi::processRspQryMatchInfo(Task task)
{
	PyLock lock;
	DFITCMatchedRtnField task_data = any_cast<DFITCMatchedRtnField>(task.task_data);
	dict data;
	data["matchedMort"] = task_data.matchedMort;
	data["customCategory"] = task_data.customCategory;
	data["fee"] = task_data.fee;
	data["orderType"] = task_data.orderType;
	data["OrderSysID"] = task_data.OrderSysID;
	data["matchType"] = task_data.matchType;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["matchedTime"] = task_data.matchedTime;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["matchedID"] = task_data.matchedID;
	data["lRequestID"] = task_data.lRequestID;
	data["clientID"] = task_data.clientID;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["openClose"] = task_data.openClose;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["sessionId"] = task_data.sessionId;
	data["reservedType2"] = task_data.reservedType2;
	data["spdOrderID"] = task_data.spdOrderID;

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

	this->onRspQryMatchInfo(data, error, task.task_last);
};

void TdApi::processRspQryPosition(Task task)
{
	PyLock lock;
	DFITCPositionInfoRtnField task_data = any_cast<DFITCPositionInfoRtnField>(task.task_data);
	dict data;
	data["openAvgPrice"] = task_data.openAvgPrice;
	data["dPremium"] = task_data.dPremium;
	data["dMargin"] = task_data.dMargin;
	data["lastAvaiAmount"] = task_data.lastAvaiAmount;
	data["positionAmount"] = task_data.positionAmount;
	data["todayAmount"] = task_data.todayAmount;
	data["datePositionProfitLoss"] = task_data.datePositionProfitLoss;
	data["floatProfitLoss"] = task_data.floatProfitLoss;
	data["instrumentType"] = task_data.instrumentType;
	data["positionAvgPrice"] = task_data.positionAvgPrice;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["buySellType"] = task_data.buySellType;
	data["tradingAmount"] = task_data.tradingAmount;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["totalAvaiAmount"] = task_data.totalAvaiAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["todayAvaiAmount"] = task_data.todayAvaiAmount;
	data["yesterdayTradingAmount"] = task_data.yesterdayTradingAmount;
	data["speculator"] = task_data.speculator;
	data["dateCloseProfitLoss"] = task_data.dateCloseProfitLoss;
	data["accountID"] = task_data.accountID;
	data["lastAmount"] = task_data.lastAmount;

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

	this->onRspQryPosition(data, error, task.task_last);
};

void TdApi::processRspCustomerCapital(Task task)
{
	PyLock lock;
	DFITCCapitalInfoRtnField task_data = any_cast<DFITCCapitalInfoRtnField>(task.task_data);
	dict data;
	data["available"] = task_data.available;
	data["todayPremiumIncome"] = task_data.todayPremiumIncome;
	data["todayPremiumPay"] = task_data.todayPremiumPay;
	data["preEquity"] = task_data.preEquity;
	data["totFundOut"] = task_data.totFundOut;
	data["frozenMargin"] = task_data.frozenMargin;
	data["todayEquity"] = task_data.todayEquity;
	data["totFundIn"] = task_data.totFundIn;
	data["closeProfitLoss"] = task_data.closeProfitLoss;
	data["riskDegree"] = task_data.riskDegree;
	data["optMarketValue"] = task_data.optMarketValue;
	data["fee"] = task_data.fee;
	data["requestID"] = task_data.requestID;
	data["withdraw"] = task_data.withdraw;
	data["positionProfitLoss"] = task_data.positionProfitLoss;
	data["floatProfitLoss"] = task_data.floatProfitLoss;
	data["yesterdayPremium"] = task_data.yesterdayPremium;
	data["margin"] = task_data.margin;
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

	this->onRspCustomerCapital(data, error, task.task_last);
};

void TdApi::processRspQryExchangeInstrument(Task task)
{
	PyLock lock;
	DFITCExchangeInstrumentRtnField task_data = any_cast<DFITCExchangeInstrumentRtnField>(task.task_data);
	dict data;
	data["optionType"] = task_data.optionType;
	data["underlying"] = task_data.underlying;
	data["instrumentType"] = task_data.instrumentType;
	data["minMargin"] = task_data.minMargin;
	data["tradeSize"] = task_data.tradeSize;
	data["lowerLimitPrice"] = task_data.lowerLimitPrice;
	data["VarietyName"] = task_data.VarietyName;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["contractMultiplier"] = task_data.contractMultiplier;
	data["orderTopLimit"] = task_data.orderTopLimit;
	data["mktOrderTopLimit"] = task_data.mktOrderTopLimit;
	data["settlementPrice"] = task_data.settlementPrice;
	data["exchangeRiskDegree"] = task_data.exchangeRiskDegree;
	data["strikePrice"] = task_data.strikePrice;
	data["preOpenInterest"] = task_data.preOpenInterest;
	data["lRequestID"] = task_data.lRequestID;
	data["upperLimitPrice"] = task_data.upperLimitPrice;
	data["instrumentMaturity"] = task_data.instrumentMaturity;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["instrumentPrefix"] = task_data.instrumentPrefix;
	data["preClosePrice"] = task_data.preClosePrice;
	data["instrumentExpiration"] = task_data.instrumentExpiration;
	data["minPriceFluctuation"] = task_data.minPriceFluctuation;

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

	this->onRspQryExchangeInstrument(data, error, task.task_last);
};

void TdApi::processRspArbitrageInstrument(Task task)
{
	PyLock lock;
	DFITCAbiInstrumentRtnField task_data = any_cast<DFITCAbiInstrumentRtnField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentName"] = task_data.instrumentName;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;

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

	this->onRspArbitrageInstrument(data, error, task.task_last);
};

void TdApi::processRspQrySpecifyInstrument(Task task)
{
	PyLock lock;
	DFITCInstrumentRtnField task_data = any_cast<DFITCInstrumentRtnField>(task.task_data);
	dict data;
	data["optExecRatioPerVol"] = task_data.optExecRatioPerVol;
	data["closeFeeVolRatio"] = task_data.closeFeeVolRatio;
	data["contractMultiplier"] = task_data.contractMultiplier;
	data["openFeeAmtRatio"] = task_data.openFeeAmtRatio;
	data["longMarginRatio"] = task_data.longMarginRatio;
	data["computeMode"] = task_data.computeMode;
	data["lowerLimitPrice"] = task_data.lowerLimitPrice;
	data["preClosePrice"] = task_data.preClosePrice;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["shortMarginRatio"] = task_data.shortMarginRatio;
	data["orderTopLimit"] = task_data.orderTopLimit;
	data["settlementPrice"] = task_data.settlementPrice;
	data["preOpenInterest"] = task_data.preOpenInterest;
	data["openFeeVolRatio"] = task_data.openFeeVolRatio;
	data["lRequestID"] = task_data.lRequestID;
	data["atMoneyNorm"] = task_data.atMoneyNorm;
	data["upperLimitPrice"] = task_data.upperLimitPrice;
	data["instrumentMaturity"] = task_data.instrumentMaturity;
	data["optExecRatio"] = task_data.optExecRatio;
	data["longMarginRatioByVolume"] = task_data.longMarginRatioByVolume;
	data["instrumentID"] = task_data.instrumentID;
	data["minimumPriceChange"] = task_data.minimumPriceChange;
	data["closeTodayFeeAmtRatio"] = task_data.closeTodayFeeAmtRatio;
	data["instrumentType"] = task_data.instrumentType;
	data["closeTodayFeeVolRatio"] = task_data.closeTodayFeeVolRatio;
	data["shortMarginRatioByVolume"] = task_data.shortMarginRatioByVolume;
	data["closeFeeAmtRatio"] = task_data.closeFeeAmtRatio;

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

	this->onRspQrySpecifyInstrument(data, error, task.task_last);
};

void TdApi::processRspQryPositionDetail(Task task)
{
	PyLock lock;
	DFITCPositionDetailRtnField task_data = any_cast<DFITCPositionDetailRtnField>(task.task_data);
	dict data;
	data["closeMatchVol"] = task_data.closeMatchVol;
	data["openPrice"] = task_data.openPrice;
	data["customCategory"] = task_data.customCategory;
	data["matchedDate"] = task_data.matchedDate;
	data["dMargin"] = task_data.dMargin;
	data["positionDateType"] = task_data.positionDateType;
	data["datePositionProfitLoss"] = task_data.datePositionProfitLoss;
	data["floatProfitLoss"] = task_data.floatProfitLoss;
	data["instrumentType"] = task_data.instrumentType;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["volume"] = task_data.volume;
	data["lRequestID"] = task_data.lRequestID;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["matchID"] = task_data.matchID;
	data["speculator"] = task_data.speculator;
	data["closeOrderVol"] = task_data.closeOrderVol;
	data["dateCloseProfitLoss"] = task_data.dateCloseProfitLoss;
	data["accountID"] = task_data.accountID;
	data["spdOrderID"] = task_data.spdOrderID;

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

	this->onRspQryPositionDetail(data, error, task.task_last);
};

void TdApi::processRtnTradingNotice(Task task)
{
	PyLock lock;
	DFITCTradingNoticeInfoField task_data = any_cast<DFITCTradingNoticeInfoField>(task.task_data);
	dict data;
	data["FieldContent"] = task_data.FieldContent;
	data["SendTime"] = task_data.SendTime;
	data["noticeType"] = task_data.noticeType;
	data["accountID"] = task_data.accountID;

	this->onRtnTradingNotice(data);
};

void TdApi::processRspResetPassword(Task task)
{
	PyLock lock;
	DFITCResetPwdRspField task_data = any_cast<DFITCResetPwdRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["execState"] = task_data.execState;
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

	this->onRspResetPassword(data, error);
};

void TdApi::processRspQryTradeCode(Task task)
{
	PyLock lock;
	DFITCQryTradeCodeRtnField task_data = any_cast<DFITCQryTradeCodeRtnField>(task.task_data);
	dict data;
	data["exchangeCode"] = task_data.exchangeCode;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["clientIDType"] = task_data.clientIDType;
	data["accountID"] = task_data.accountID;
	data["clientStatus"] = task_data.clientStatus;

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

	this->onRspQryTradeCode(data, error, task.task_last);
};

void TdApi::processRspBillConfirm(Task task)
{
	PyLock lock;
	DFITCBillConfirmRspField task_data = any_cast<DFITCBillConfirmRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["execState"] = task_data.execState;
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

	this->onRspBillConfirm(data, error);
};

void TdApi::processRspEquityComputMode(Task task)
{
	PyLock lock;
	DFITCEquityComputModeRtnField task_data = any_cast<DFITCEquityComputModeRtnField>(task.task_data);
	dict data;
	data["priceNote"] = task_data.priceNote;
	data["capConMode"] = task_data.capConMode;

	this->onRspEquityComputMode(data);
};

void TdApi::processRspQryBill(Task task)
{
	PyLock lock;
	DFITCQryBillRtnField task_data = any_cast<DFITCQryBillRtnField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["message"] = task_data.message;
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

	this->onRspQryBill(data, error, task.task_last);
};

void TdApi::processRspConfirmProductInfo(Task task)
{
	PyLock lock;
	DFITCProductRtnField task_data = any_cast<DFITCProductRtnField>(task.task_data);
	dict data;
	data["brokerInfoName"] = task_data.brokerInfoName;
	data["vendorID"] = task_data.vendorID;
	data["productOnlineCount"] = task_data.productOnlineCount;
	data["frontID"] = task_data.frontID;
	data["productID"] = task_data.productID;

	this->onRspConfirmProductInfo(data);
};

void TdApi::processRspTradingDay(Task task)
{
	PyLock lock;
	DFITCTradingDayRtnField task_data = any_cast<DFITCTradingDayRtnField>(task.task_data);
	dict data;
	data["date"] = task_data.date;
	data["lRequestID"] = task_data.lRequestID;

	this->onRspTradingDay(data);
};

void TdApi::processRspQuoteInsert(Task task)
{
	PyLock lock;
	DFITCQuoteRspField task_data = any_cast<DFITCQuoteRspField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["orderTime"] = task_data.orderTime;
	data["fee"] = task_data.fee;
	data["localOrderID"] = task_data.localOrderID;
	data["margin"] = task_data.margin;
	data["sessionID"] = task_data.sessionID;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
	data["quoteID"] = task_data.quoteID;
	data["customCategory"] = task_data.customCategory;
	data["spdOrderID"] = task_data.spdOrderID;
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

	this->onRspQuoteInsert(data, error);
};

void TdApi::processRtnQuoteInsert(Task task)
{
	PyLock lock;
	DFITCQuoteRtnField task_data = any_cast<DFITCQuoteRtnField>(task.task_data);
	dict data;
	data["quoteID"] = task_data.quoteID;
	data["sOpenCloseType"] = task_data.sOpenCloseType;
	data["seatCode"] = task_data.seatCode;
	data["orderStatus"] = task_data.orderStatus;
	data["orderSysID"] = task_data.orderSysID;
	data["bOpenCloseType"] = task_data.bOpenCloseType;
	data["suspendTime"] = task_data.suspendTime;
	data["customCategory"] = task_data.customCategory;
	data["entrusTeller"] = task_data.entrusTeller;
	data["bInsertPrice"] = task_data.bInsertPrice;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["errorMsg"] = task_data.errorMsg;
	data["bOrderAmount"] = task_data.bOrderAmount;
	data["sInsertPrice"] = task_data.sInsertPrice;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["speculator"] = task_data.speculator;
	data["sOrderAmount"] = task_data.sOrderAmount;
	data["spdOrderID"] = task_data.spdOrderID;

	this->onRtnQuoteInsert(data);
};

void TdApi::processRspQuoteCancel(Task task)
{
	PyLock lock;
	DFITCQuoteRspField task_data = any_cast<DFITCQuoteRspField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["orderTime"] = task_data.orderTime;
	data["fee"] = task_data.fee;
	data["localOrderID"] = task_data.localOrderID;
	data["margin"] = task_data.margin;
	data["sessionID"] = task_data.sessionID;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
	data["quoteID"] = task_data.quoteID;
	data["customCategory"] = task_data.customCategory;
	data["spdOrderID"] = task_data.spdOrderID;
	data["accountID"] = task_data.accountID;

	this->onRspQuoteCancel(data);
};

void TdApi::processRtnQuoteCancel(Task task)
{
	PyLock lock;
	DFITCQuoteCanceledRtnField task_data = any_cast<DFITCQuoteCanceledRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["speculator"] = task_data.speculator;
	data["exchangeID"] = task_data.exchangeID;
	data["fee"] = task_data.fee;
	data["localOrderID"] = task_data.localOrderID;
	data["sOpenCloseType"] = task_data.sOpenCloseType;
	data["margin"] = task_data.margin;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["seatCode"] = task_data.seatCode;
	data["sessionID"] = task_data.sessionID;
	data["orderStatus"] = task_data.orderStatus;
	data["orderSysID"] = task_data.orderSysID;
	data["entrusTeller"] = task_data.entrusTeller;
	data["bOpenCloseType"] = task_data.bOpenCloseType;
	data["quoteID"] = task_data.quoteID;
	data["canceledTime"] = task_data.canceledTime;
	data["customCategory"] = task_data.customCategory;
	data["spdOrderID"] = task_data.spdOrderID;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;

	this->onRtnQuoteCancel(data);
};

void TdApi::processRtnQuoteMatchedInfo(Task task)
{
	PyLock lock;
	DFITCQuoteMatchRtnField task_data = any_cast<DFITCQuoteMatchRtnField>(task.task_data);
	dict data;
	data["quoteID"] = task_data.quoteID;
	data["seatCode"] = task_data.seatCode;
	data["closeTodayPrice"] = task_data.closeTodayPrice;
	data["adjustmentInfo"] = task_data.adjustmentInfo;
	data["orderStatus"] = task_data.orderStatus;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["largeMarginDirect"] = task_data.largeMarginDirect;
	data["OrderSysID"] = task_data.OrderSysID;
	data["entrusTeller"] = task_data.entrusTeller;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["matchedTime"] = task_data.matchedTime;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["closeTodayAmount"] = task_data.closeTodayAmount;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["spdOrderID"] = task_data.spdOrderID;
	data["frozenCapita"] = task_data.frozenCapita;
	data["matchID"] = task_data.matchID;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["dateCloseProfitLoss"] = task_data.dateCloseProfitLoss;
	data["closePrice"] = task_data.closePrice;
	data["margin"] = task_data.margin;
	data["turnover"] = task_data.turnover;

	this->onRtnQuoteMatchedInfo(data);
};

void TdApi::processRspCancelAllOrder(Task task)
{
	PyLock lock;
	DFITCCancelAllOrderRspField task_data = any_cast<DFITCCancelAllOrderRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
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

	this->onRspCancelAllOrder(data, error);
};

void TdApi::processRspQryQuoteNotice(Task task)
{
	PyLock lock;
	DFITCQryQuoteNoticeRtnField task_data = any_cast<DFITCQryQuoteNoticeRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["quoteID"] = task_data.quoteID;
	data["source"] = task_data.source;
	data["lRequestID"] = task_data.lRequestID;
	data["quoteTime"] = task_data.quoteTime;

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

	this->onRspQryQuoteNotice(data, error, task.task_last);
};

void TdApi::processRspForQuote(Task task)
{
	PyLock lock;
	DFITCForQuoteRspField task_data = any_cast<DFITCForQuoteRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["commTime"] = task_data.commTime;
	data["spdOrderID"] = task_data.spdOrderID;

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

	this->onRspForQuote(data, error);
};

void TdApi::processRtnForQuote(Task task)
{
	PyLock lock;
	DFITCForQuoteRtnField task_data = any_cast<DFITCForQuoteRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["sessionID"] = task_data.sessionID;
	data["orderStatus"] = task_data.orderStatus;
	data["spdOrderID"] = task_data.spdOrderID;
	data["accountID"] = task_data.accountID;

	this->onRtnForQuote(data);
};

void TdApi::processRspQryQuoteOrderInfo(Task task)
{
	PyLock lock;
	DFITCQuoteOrderRtnField task_data = any_cast<DFITCQuoteOrderRtnField>(task.task_data);
	dict data;
	data["quoteID"] = task_data.quoteID;
	data["sOpenCloseType"] = task_data.sOpenCloseType;
	data["commTime"] = task_data.commTime;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;
	data["bOpenCloseType"] = task_data.bOpenCloseType;
	data["customCategory"] = task_data.customCategory;
	data["fee"] = task_data.fee;
	data["bMatchedPrice"] = task_data.bMatchedPrice;
	data["sMatchedPrice"] = task_data.sMatchedPrice;
	data["sInsertPrice"] = task_data.sInsertPrice;
	data["bInsertPrice"] = task_data.bInsertPrice;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["bOrderAmount"] = task_data.bOrderAmount;
	data["operStation"] = task_data.operStation;
	data["submitTime"] = task_data.submitTime;
	data["lRequestID"] = task_data.lRequestID;
	data["bMatchedAmount"] = task_data.bMatchedAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["sCancelAmount"] = task_data.sCancelAmount;
	data["sessionID"] = task_data.sessionID;
	data["sMatchedAmount"] = task_data.sMatchedAmount;
	data["sOrderAmount"] = task_data.sOrderAmount;
	data["spdOrderID"] = task_data.spdOrderID;
	data["bCancelAmount"] = task_data.bCancelAmount;

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

	this->onRspQryQuoteOrderInfo(data, error, task.task_last);
};

void TdApi::processRspQryForQuote(Task task)
{
	PyLock lock;
	DFITCQryForQuoteRtnField task_data = any_cast<DFITCQryForQuoteRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
	data["spdOrderID"] = task_data.spdOrderID;
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

	this->onRspQryForQuote(data, error, task.task_last);
};

void TdApi::processRspQryTransferBank(Task task)
{
	PyLock lock;
	DFITCTransferBankRspField task_data = any_cast<DFITCTransferBankRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["registDate"] = task_data.registDate;
	data["currency"] = task_data.currency;
	data["lRequestID"] = task_data.lRequestID;
	data["bankID"] = task_data.bankID;
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

	this->onRspQryTransferBank(data, error, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	DFITCTransferSerialRspField task_data = any_cast<DFITCTransferSerialRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["curFutAccountFund"] = task_data.curFutAccountFund;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["procResult"] = task_data.procResult;
	data["currency"] = task_data.currency;
	data["lRequestID"] = task_data.lRequestID;
	data["applyNum"] = task_data.applyNum;
	data["dealTransferTime"] = task_data.dealTransferTime;
	data["bankID"] = task_data.bankID;
	data["reqTransferTime"] = task_data.reqTransferTime;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
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

	this->onRspQryTransferSerial(data, error, task.task_last);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRspField task_data = any_cast<DFITCTransferRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["applyNumber"] = task_data.applyNumber;
	data["lRequestID"] = task_data.lRequestID;
	data["bankID"] = task_data.bankID;
	data["tradeAmount"] = task_data.tradeAmount;
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

	this->onRspFromBankToFutureByFuture(data, error);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRspField task_data = any_cast<DFITCTransferRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["applyNumber"] = task_data.applyNumber;
	data["lRequestID"] = task_data.lRequestID;
	data["bankID"] = task_data.bankID;
	data["tradeAmount"] = task_data.tradeAmount;
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

	this->onRspFromFutureToBankByFuture(data, error);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRtnField task_data = any_cast<DFITCTransferRtnField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["applyNumber"] = task_data.applyNumber;
	data["sessionID"] = task_data.sessionID;
	data["bankID"] = task_data.bankID;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
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

	this->onRtnFromBankToFutureByFuture(data, error);
};

void TdApi::processRtnFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRtnField task_data = any_cast<DFITCTransferRtnField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["applyNumber"] = task_data.applyNumber;
	data["sessionID"] = task_data.sessionID;
	data["bankID"] = task_data.bankID;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
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

	this->onRtnFromFutureToBankByFuture(data, error);
};

void TdApi::processRtnRepealFromFutureToBankByBank(Task task)
{
	PyLock lock;
	DFITCRepealRtnField task_data = any_cast<DFITCRepealRtnField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["repealSerial"] = task_data.repealSerial;
	data["bankID"] = task_data.bankID;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
	data["accountID"] = task_data.accountID;

	this->onRtnRepealFromFutureToBankByBank(data);
};

void TdApi::processRspQryExchangeStatus(Task task)
{
	PyLock lock;
	DFITCExchangeStatusRspField task_data = any_cast<DFITCExchangeStatusRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeStatus"] = task_data.exchangeStatus;
	data["exchangeID"] = task_data.exchangeID;

	this->onRspQryExchangeStatus(data);
};

void TdApi::processRtnExchangeStatus(Task task)
{
	PyLock lock;
	DFITCExchangeStatusRtnField task_data = any_cast<DFITCExchangeStatusRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["exchangeStatus"] = task_data.exchangeStatus;

	this->onRtnExchangeStatus(data);
};

void TdApi::processRspQryDepthMarketData(Task task)
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

	this->onRspQryDepthMarketData(data, error, task.task_last);
};

