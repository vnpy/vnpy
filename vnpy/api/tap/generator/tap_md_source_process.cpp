void MdApi::processRspLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuotLoginRspInfo *task_data = (TapAPIQuotLoginRspInfo*)task->task_data;
		data["UserNo"] = toUtf(task_data->UserNo);
		data["UserType"] = task_data->UserType;
		data["UserName"] = toUtf(task_data->UserName);
		data["QuoteTempPassword"] = toUtf(task_data->QuoteTempPassword);
		data["ReservedInfo"] = toUtf(task_data->ReservedInfo);
		data["LastLoginIP"] = toUtf(task_data->LastLoginIP);
		data["LastLoginProt"] = task_data->LastLoginProt;
		data["LastLoginTime"] = toUtf(task_data->LastLoginTime);
		data["LastLogoutTime"] = toUtf(task_data->LastLogoutTime);
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["LastSettleTime"] = toUtf(task_data->LastSettleTime);
		data["StartTime"] = toUtf(task_data->StartTime);
		data["InitTime"] = toUtf(task_data->InitTime);
		delete task_data;
	}
	this->onRspLogin(task->task_int, data);
};

void MdApi::processAPIReady(Task *task)
{
	this->onAPIReady();
};

void MdApi::processDisconnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(task->task_int);
};

void MdApi::processRspQryCommodity(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteCommodityInfo *task_data = (TapAPIQuoteCommodityInfo*)task->task_data;
		data["Commodity"] = task_data->Commodity;
		data["CommodityName"] = toUtf(task_data->CommodityName);
		data["CommodityEngName"] = toUtf(task_data->CommodityEngName);
		data["ContractSize"] = task_data->ContractSize;
		data["CommodityTickSize"] = task_data->CommodityTickSize;
		data["CommodityDenominator"] = task_data->CommodityDenominator;
		data["CmbDirect"] = task_data->CmbDirect;
		data["CommodityContractLen"] = task_data->CommodityContractLen;
		data["IsDST"] = task_data->IsDST;
		data["RelateCommodity1"] = task_data->RelateCommodity1;
		data["RelateCommodity2"] = task_data->RelateCommodity2;
		delete task_data;
	}
	this->onRspQryCommodity(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRspQryContract(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteContractInfo *task_data = (TapAPIQuoteContractInfo*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["ContractType"] = task_data->ContractType;
		data["QuoteUnderlyingContract"] = toUtf(task_data->QuoteUnderlyingContract);
		data["ContractName"] = toUtf(task_data->ContractName);
		data["ContractExpDate"] = toUtf(task_data->ContractExpDate);
		data["LastTradeDate"] = toUtf(task_data->LastTradeDate);
		data["FirstNoticeDate"] = toUtf(task_data->FirstNoticeDate);
		delete task_data;
	}
	this->onRspQryContract(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRspSubscribeQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteWhole *task_data = (TapAPIQuoteWhole*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["TradingState"] = task_data->TradingState;
		data["DateTimeStamp"] = toUtf(task_data->DateTimeStamp);
		data["QPreClosingPrice"] = task_data->QPreClosingPrice;
		data["QPreSettlePrice"] = task_data->QPreSettlePrice;
		data["QPrePositionQty"] = task_data->QPrePositionQty;
		data["QOpeningPrice"] = task_data->QOpeningPrice;
		data["QLastPrice"] = task_data->QLastPrice;
		data["QHighPrice"] = task_data->QHighPrice;
		data["QLowPrice"] = task_data->QLowPrice;
		data["QHisHighPrice"] = task_data->QHisHighPrice;
		data["QHisLowPrice"] = task_data->QHisLowPrice;
		data["QLimitUpPrice"] = task_data->QLimitUpPrice;
		data["QLimitDownPrice"] = task_data->QLimitDownPrice;
		data["QTotalQty"] = task_data->QTotalQty;
		data["QTotalTurnover"] = task_data->QTotalTurnover;
		data["QPositionQty"] = task_data->QPositionQty;
		data["QAveragePrice"] = task_data->QAveragePrice;
		data["QClosingPrice"] = task_data->QClosingPrice;
		data["QSettlePrice"] = task_data->QSettlePrice;
		data["QLastQty"] = task_data->QLastQty;
		data["QBidPrice"] = task_data->QBidPrice;
		data["QBidQty"] = task_data->QBidQty;
		data["QAskPrice"] = task_data->QAskPrice;
		data["QAskQty"] = task_data->QAskQty;
		data["QImpliedBidPrice"] = task_data->QImpliedBidPrice;
		data["QImpliedBidQty"] = task_data->QImpliedBidQty;
		data["QImpliedAskPrice"] = task_data->QImpliedAskPrice;
		data["QImpliedAskQty"] = task_data->QImpliedAskQty;
		data["QPreDelta"] = task_data->QPreDelta;
		data["QCurrDelta"] = task_data->QCurrDelta;
		data["QInsideQty"] = task_data->QInsideQty;
		data["QOutsideQty"] = task_data->QOutsideQty;
		data["QTurnoverRate"] = task_data->QTurnoverRate;
		data["Q5DAvgQty"] = task_data->Q5DAvgQty;
		data["QPERatio"] = task_data->QPERatio;
		data["QTotalValue"] = task_data->QTotalValue;
		data["QNegotiableValue"] = task_data->QNegotiableValue;
		data["QPositionTrend"] = task_data->QPositionTrend;
		data["QChangeSpeed"] = task_data->QChangeSpeed;
		data["QChangeRate"] = task_data->QChangeRate;
		data["QChangeValue"] = task_data->QChangeValue;
		data["QSwing"] = task_data->QSwing;
		data["QTotalBidQty"] = task_data->QTotalBidQty;
		data["QTotalAskQty"] = task_data->QTotalAskQty;
		data["UnderlyContract"] = task_data->UnderlyContract;
		delete task_data;
	}
	this->onRspSubscribeQuote(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRspUnSubscribeQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIContract *task_data = (TapAPIContract*)task->task_data;
		data["Commodity"] = task_data->Commodity;
		data["ContractNo1"] = toUtf(task_data->ContractNo1);
		data["StrikePrice1"] = toUtf(task_data->StrikePrice1);
		data["CallOrPutFlag1"] = task_data->CallOrPutFlag1;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		delete task_data;
	}
	this->onRspUnSubscribeQuote(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRtnQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteWhole *task_data = (TapAPIQuoteWhole*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["TradingState"] = task_data->TradingState;
		data["DateTimeStamp"] = toUtf(task_data->DateTimeStamp);
		data["QPreClosingPrice"] = task_data->QPreClosingPrice;
		data["QPreSettlePrice"] = task_data->QPreSettlePrice;
		data["QPrePositionQty"] = task_data->QPrePositionQty;
		data["QOpeningPrice"] = task_data->QOpeningPrice;
		data["QLastPrice"] = task_data->QLastPrice;
		data["QHighPrice"] = task_data->QHighPrice;
		data["QLowPrice"] = task_data->QLowPrice;
		data["QHisHighPrice"] = task_data->QHisHighPrice;
		data["QHisLowPrice"] = task_data->QHisLowPrice;
		data["QLimitUpPrice"] = task_data->QLimitUpPrice;
		data["QLimitDownPrice"] = task_data->QLimitDownPrice;
		data["QTotalQty"] = task_data->QTotalQty;
		data["QTotalTurnover"] = task_data->QTotalTurnover;
		data["QPositionQty"] = task_data->QPositionQty;
		data["QAveragePrice"] = task_data->QAveragePrice;
		data["QClosingPrice"] = task_data->QClosingPrice;
		data["QSettlePrice"] = task_data->QSettlePrice;
		data["QLastQty"] = task_data->QLastQty;
		data["QBidPrice"] = task_data->QBidPrice;
		data["QBidQty"] = task_data->QBidQty;
		data["QAskPrice"] = task_data->QAskPrice;
		data["QAskQty"] = task_data->QAskQty;
		data["QImpliedBidPrice"] = task_data->QImpliedBidPrice;
		data["QImpliedBidQty"] = task_data->QImpliedBidQty;
		data["QImpliedAskPrice"] = task_data->QImpliedAskPrice;
		data["QImpliedAskQty"] = task_data->QImpliedAskQty;
		data["QPreDelta"] = task_data->QPreDelta;
		data["QCurrDelta"] = task_data->QCurrDelta;
		data["QInsideQty"] = task_data->QInsideQty;
		data["QOutsideQty"] = task_data->QOutsideQty;
		data["QTurnoverRate"] = task_data->QTurnoverRate;
		data["Q5DAvgQty"] = task_data->Q5DAvgQty;
		data["QPERatio"] = task_data->QPERatio;
		data["QTotalValue"] = task_data->QTotalValue;
		data["QNegotiableValue"] = task_data->QNegotiableValue;
		data["QPositionTrend"] = task_data->QPositionTrend;
		data["QChangeSpeed"] = task_data->QChangeSpeed;
		data["QChangeRate"] = task_data->QChangeRate;
		data["QChangeValue"] = task_data->QChangeValue;
		data["QSwing"] = task_data->QSwing;
		data["QTotalBidQty"] = task_data->QTotalBidQty;
		data["QTotalAskQty"] = task_data->QTotalAskQty;
		data["UnderlyContract"] = task_data->UnderlyContract;
		delete task_data;
	}
	this->onRtnQuote(data);
};

