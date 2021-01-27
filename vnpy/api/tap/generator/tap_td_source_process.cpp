void TdApi::processConnect(Task *task)
{
	this->onConnect();
};

void TdApi::processRspLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeLoginRspInfo *task_data = (TapAPITradeLoginRspInfo*)task->task_data;
		data["UserNo"] = toUtf(task_data->UserNo);
		data["UserType"] = task_data->UserType;
		data["UserName"] = toUtf(task_data->UserName);
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

void TdApi::processRtnContactInfo(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRtnContactInfo(task->task_int, task->task_last, task->task_string);
};

void TdApi::processRspRequestVertificateCode(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIRequestVertificateCodeRsp *task_data = (TapAPIRequestVertificateCodeRsp*)task->task_data;
		data["SecondSerialID"] = toUtf(task_data->SecondSerialID);
		data["Effective"] = task_data->Effective;
		delete task_data;
	}
	this->onRspRequestVertificateCode(task->task_id, task->task_int, data);
};

void TdApi::processExpriationDate(Task *task)
{
	gil_scoped_acquire acquire;
	this->onExpriationDate(task->task_string, task->task_int);
};

void TdApi::processAPIReady(Task *task)
{
	gil_scoped_acquire acquire;
	this->onAPIReady(task->task_int);
};

void TdApi::processDisconnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(task->task_int);
};

void TdApi::processRspChangePassword(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspChangePassword(task->task_id, task->task_int);
};

void TdApi::processRspAuthPassword(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspAuthPassword(task->task_id, task->task_int);
};

void TdApi::processRspQryTradingDate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradingCalendarQryRsp *task_data = (TapAPITradingCalendarQryRsp*)task->task_data;
		data["CurrTradeDate"] = toUtf(task_data->CurrTradeDate);
		data["LastSettlementDate"] = toUtf(task_data->LastSettlementDate);
		data["PromptDate"] = toUtf(task_data->PromptDate);
		data["LastPromptDate"] = toUtf(task_data->LastPromptDate);
		delete task_data;
	}
	this->onRspQryTradingDate(task->task_id, task->task_int, data);
};

void TdApi::processRspSetReservedInfo(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSetReservedInfo(task->task_id, task->task_int, task->task_string);
};

void TdApi::processRspQryAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountInfo *task_data = (TapAPIAccountInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["AccountType"] = task_data->AccountType;
		data["AccountState"] = task_data->AccountState;
		data["AccountTradeRight"] = task_data->AccountTradeRight;
		data["CommodityGroupNo"] = toUtf(task_data->CommodityGroupNo);
		data["AccountShortName"] = toUtf(task_data->AccountShortName);
		data["AccountEnShortName"] = toUtf(task_data->AccountEnShortName);
		delete task_data;
	}
	this->onRspQryAccount(task->task_id, task->task_id, task->task_last, data);
};

void TdApi::processRspQryFund(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFundData *task_data = (TapAPIFundData*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["TradeRate"] = task_data->TradeRate;
		data["FutureAlg"] = task_data->FutureAlg;
		data["OptionAlg"] = task_data->OptionAlg;
		data["PreBalance"] = task_data->PreBalance;
		data["PreUnExpProfit"] = task_data->PreUnExpProfit;
		data["PreLMEPositionProfit"] = task_data->PreLMEPositionProfit;
		data["PreEquity"] = task_data->PreEquity;
		data["PreAvailable1"] = task_data->PreAvailable1;
		data["PreMarketEquity"] = task_data->PreMarketEquity;
		data["CashInValue"] = task_data->CashInValue;
		data["CashOutValue"] = task_data->CashOutValue;
		data["CashAdjustValue"] = task_data->CashAdjustValue;
		data["CashPledged"] = task_data->CashPledged;
		data["FrozenFee"] = task_data->FrozenFee;
		data["FrozenDeposit"] = task_data->FrozenDeposit;
		data["AccountFee"] = task_data->AccountFee;
		data["SwapInValue"] = task_data->SwapInValue;
		data["SwapOutValue"] = task_data->SwapOutValue;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["CloseProfit"] = task_data->CloseProfit;
		data["FrozenFund"] = task_data->FrozenFund;
		data["UnExpProfit"] = task_data->UnExpProfit;
		data["ExpProfit"] = task_data->ExpProfit;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LmePositionProfit"] = task_data->LmePositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["AccountIntialMargin"] = task_data->AccountIntialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitalMargin"] = task_data->UpperInitalMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["Discount"] = task_data->Discount;
		data["Balance"] = task_data->Balance;
		data["Equity"] = task_data->Equity;
		data["Available"] = task_data->Available;
		data["CanDraw"] = task_data->CanDraw;
		data["MarketEquity"] = task_data->MarketEquity;
		data["AuthMoney"] = task_data->AuthMoney;
		delete task_data;
	}
	this->onRspQryFund(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnFund(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFundData *task_data = (TapAPIFundData*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["TradeRate"] = task_data->TradeRate;
		data["FutureAlg"] = task_data->FutureAlg;
		data["OptionAlg"] = task_data->OptionAlg;
		data["PreBalance"] = task_data->PreBalance;
		data["PreUnExpProfit"] = task_data->PreUnExpProfit;
		data["PreLMEPositionProfit"] = task_data->PreLMEPositionProfit;
		data["PreEquity"] = task_data->PreEquity;
		data["PreAvailable1"] = task_data->PreAvailable1;
		data["PreMarketEquity"] = task_data->PreMarketEquity;
		data["CashInValue"] = task_data->CashInValue;
		data["CashOutValue"] = task_data->CashOutValue;
		data["CashAdjustValue"] = task_data->CashAdjustValue;
		data["CashPledged"] = task_data->CashPledged;
		data["FrozenFee"] = task_data->FrozenFee;
		data["FrozenDeposit"] = task_data->FrozenDeposit;
		data["AccountFee"] = task_data->AccountFee;
		data["SwapInValue"] = task_data->SwapInValue;
		data["SwapOutValue"] = task_data->SwapOutValue;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["CloseProfit"] = task_data->CloseProfit;
		data["FrozenFund"] = task_data->FrozenFund;
		data["UnExpProfit"] = task_data->UnExpProfit;
		data["ExpProfit"] = task_data->ExpProfit;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LmePositionProfit"] = task_data->LmePositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["AccountIntialMargin"] = task_data->AccountIntialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitalMargin"] = task_data->UpperInitalMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["Discount"] = task_data->Discount;
		data["Balance"] = task_data->Balance;
		data["Equity"] = task_data->Equity;
		data["Available"] = task_data->Available;
		data["CanDraw"] = task_data->CanDraw;
		data["MarketEquity"] = task_data->MarketEquity;
		data["AuthMoney"] = task_data->AuthMoney;
		delete task_data;
	}
	this->onRtnFund(data);
};

void TdApi::processRspQryExchange(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIExchangeInfo *task_data = (TapAPIExchangeInfo*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["ExchangeName"] = toUtf(task_data->ExchangeName);
		delete task_data;
	}
	this->onRspQryExchange(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryCommodity(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPICommodityInfo *task_data = (TapAPICommodityInfo*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["CommodityName"] = toUtf(task_data->CommodityName);
		data["CommodityEngName"] = toUtf(task_data->CommodityEngName);
		data["RelateExchangeNo"] = toUtf(task_data->RelateExchangeNo);
		data["RelateCommodityType"] = task_data->RelateCommodityType;
		data["RelateCommodityNo"] = toUtf(task_data->RelateCommodityNo);
		data["RelateExchangeNo2"] = toUtf(task_data->RelateExchangeNo2);
		data["RelateCommodityType2"] = task_data->RelateCommodityType2;
		data["RelateCommodityNo2"] = toUtf(task_data->RelateCommodityNo2);
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["TradeCurrency"] = toUtf(task_data->TradeCurrency);
		data["ContractSize"] = task_data->ContractSize;
		data["OpenCloseMode"] = task_data->OpenCloseMode;
		data["StrikePriceTimes"] = task_data->StrikePriceTimes;
		data["CommodityTickSize"] = task_data->CommodityTickSize;
		data["CommodityDenominator"] = task_data->CommodityDenominator;
		data["CmbDirect"] = task_data->CmbDirect;
		data["DeliveryMode"] = task_data->DeliveryMode;
		data["DeliveryDays"] = task_data->DeliveryDays;
		data["AddOneTime"] = toUtf(task_data->AddOneTime);
		data["CommodityTimeZone"] = task_data->CommodityTimeZone;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRspQryCommodity(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryContract(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeContractInfo *task_data = (TapAPITradeContractInfo*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo1"] = toUtf(task_data->ContractNo1);
		data["StrikePrice1"] = toUtf(task_data->StrikePrice1);
		data["CallOrPutFlag1"] = task_data->CallOrPutFlag1;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
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

void TdApi::processRtnContract(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeContractInfo *task_data = (TapAPITradeContractInfo*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo1"] = toUtf(task_data->ContractNo1);
		data["StrikePrice1"] = toUtf(task_data->StrikePrice1);
		data["CallOrPutFlag1"] = task_data->CallOrPutFlag1;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["ContractType"] = task_data->ContractType;
		data["QuoteUnderlyingContract"] = toUtf(task_data->QuoteUnderlyingContract);
		data["ContractName"] = toUtf(task_data->ContractName);
		data["ContractExpDate"] = toUtf(task_data->ContractExpDate);
		data["LastTradeDate"] = toUtf(task_data->LastTradeDate);
		data["FirstNoticeDate"] = toUtf(task_data->FirstNoticeDate);
		delete task_data;
	}
	this->onRtnContract(data);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderActionRsp *task_data = (TapAPIOrderActionRsp*)task->task_data;
		data["ActionType"] = task_data->ActionType;
		data["OrderInfo"] = task_data->OrderInfo;
		delete task_data;
	}
	this->onRspOrderAction(task->task_id, task->task_int, data);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderInfoNotice *task_data = (TapAPIOrderInfoNotice*)task->task_data;
		data["SessionID"] = task_data->SessionID;
		data["ErrorCode"] = task_data->ErrorCode;
		data["OrderInfo"] = task_data->OrderInfo;
		delete task_data;
	}
	this->onRtnOrder(data);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderInfo *task_data = (TapAPIOrderInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRspQryOrder(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryOrderProcess(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderInfo *task_data = (TapAPIOrderInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRspQryOrderProcess(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryFill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFillInfo *task_data = (TapAPIFillInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSource"] = task_data->MatchSource;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["UpperMatchNo"] = toUtf(task_data->UpperMatchNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchDateTime"] = toUtf(task_data->MatchDateTime);
		data["UpperMatchDateTime"] = toUtf(task_data->UpperMatchDateTime);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchQty"] = task_data->MatchQty;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["FeeCurrencyGroup"] = toUtf(task_data->FeeCurrencyGroup);
		data["FeeCurrency"] = toUtf(task_data->FeeCurrency);
		data["FeeValue"] = task_data->FeeValue;
		data["IsManualFee"] = task_data->IsManualFee;
		data["ClosePrositionPrice"] = task_data->ClosePrositionPrice;
		delete task_data;
	}
	this->onRspQryFill(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnFill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFillInfo *task_data = (TapAPIFillInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSource"] = task_data->MatchSource;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["UpperMatchNo"] = toUtf(task_data->UpperMatchNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchDateTime"] = toUtf(task_data->MatchDateTime);
		data["UpperMatchDateTime"] = toUtf(task_data->UpperMatchDateTime);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchQty"] = task_data->MatchQty;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["FeeCurrencyGroup"] = toUtf(task_data->FeeCurrencyGroup);
		data["FeeCurrency"] = toUtf(task_data->FeeCurrency);
		data["FeeValue"] = task_data->FeeValue;
		data["IsManualFee"] = task_data->IsManualFee;
		data["ClosePrositionPrice"] = task_data->ClosePrositionPrice;
		delete task_data;
	}
	this->onRtnFill(data);
};

void TdApi::processRspQryPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionInfo *task_data = (TapAPIPositionInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["PositionNo"] = toUtf(task_data->PositionNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["PositionStreamId"] = task_data->PositionStreamId;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["CalculatePrice"] = task_data->CalculatePrice;
		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitialMargin"] = task_data->UpperInitialMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LMEPositionProfit"] = task_data->LMEPositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["IsHistory"] = task_data->IsHistory;
		delete task_data;
	}
	this->onRspQryPosition(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionInfo *task_data = (TapAPIPositionInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["PositionNo"] = toUtf(task_data->PositionNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["PositionStreamId"] = task_data->PositionStreamId;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["CalculatePrice"] = task_data->CalculatePrice;
		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitialMargin"] = task_data->UpperInitialMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LMEPositionProfit"] = task_data->LMEPositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["IsHistory"] = task_data->IsHistory;
		delete task_data;
	}
	this->onRtnPosition(data);
};

void TdApi::processRspQryPositionSummary(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionSummary *task_data = (TapAPIPositionSummary*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["HisPositionQty"] = task_data->HisPositionQty;
		delete task_data;
	}
	this->onRspQryPositionSummary(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnPositionSummary(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionSummary *task_data = (TapAPIPositionSummary*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["HisPositionQty"] = task_data->HisPositionQty;
		delete task_data;
	}
	this->onRtnPositionSummary(data);
};

void TdApi::processRtnPositionProfit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionProfitNotice *task_data = (TapAPIPositionProfitNotice*)task->task_data;
		data["IsLast"] = task_data->IsLast;
		data["Data"] = task_data->Data;
		delete task_data;
	}
	this->onRtnPositionProfit(data);
};

void TdApi::processRspQryCurrency(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPICurrencyInfo *task_data = (TapAPICurrencyInfo*)task->task_data;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["TradeRate"] = task_data->TradeRate;
		data["TradeRate2"] = task_data->TradeRate2;
		data["FutureAlg"] = task_data->FutureAlg;
		data["OptionAlg"] = task_data->OptionAlg;
		delete task_data;
	}
	this->onRspQryCurrency(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryTradeMessage(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeMessage *task_data = (TapAPITradeMessage*)task->task_data;
		data["SerialID"] = task_data->SerialID;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["TMsgValidDateTime"] = toUtf(task_data->TMsgValidDateTime);
		data["TMsgTitle"] = toUtf(task_data->TMsgTitle);
		data["TMsgContent"] = toUtf(task_data->TMsgContent);
		data["TMsgType"] = task_data->TMsgType;
		data["TMsgLevel"] = task_data->TMsgLevel;
		data["IsSendBySMS"] = task_data->IsSendBySMS;
		data["IsSendByEMail"] = task_data->IsSendByEMail;
		data["Sender"] = toUtf(task_data->Sender);
		data["SendDateTime"] = toUtf(task_data->SendDateTime);
		delete task_data;
	}
	this->onRspQryTradeMessage(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnTradeMessage(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeMessage *task_data = (TapAPITradeMessage*)task->task_data;
		data["SerialID"] = task_data->SerialID;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["TMsgValidDateTime"] = toUtf(task_data->TMsgValidDateTime);
		data["TMsgTitle"] = toUtf(task_data->TMsgTitle);
		data["TMsgContent"] = toUtf(task_data->TMsgContent);
		data["TMsgType"] = task_data->TMsgType;
		data["TMsgLevel"] = task_data->TMsgLevel;
		data["IsSendBySMS"] = task_data->IsSendBySMS;
		data["IsSendByEMail"] = task_data->IsSendByEMail;
		data["Sender"] = toUtf(task_data->Sender);
		data["SendDateTime"] = toUtf(task_data->SendDateTime);
		delete task_data;
	}
	this->onRtnTradeMessage(data);
};

void TdApi::processRspQryHisOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisOrderQryRsp *task_data = (TapAPIHisOrderQryRsp*)task->task_data;
		data["Date"] = toUtf(task_data->Date);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		delete task_data;
	}
	this->onRspQryHisOrder(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisOrderProcess(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisOrderProcessQryRsp *task_data = (TapAPIHisOrderProcessQryRsp*)task->task_data;
		data["Date"] = toUtf(task_data->Date);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		delete task_data;
	}
	this->onRspQryHisOrderProcess(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisMatch(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisMatchQryRsp *task_data = (TapAPIHisMatchQryRsp*)task->task_data;
		data["SettleDate"] = toUtf(task_data->SettleDate);
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSource"] = task_data->MatchSource;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchQty"] = task_data->MatchQty;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["MatchStreamID"] = task_data->MatchStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["MatchCmbNo"] = toUtf(task_data->MatchCmbNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchUpperStreamID"] = task_data->MatchUpperStreamID;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["Turnover"] = task_data->Turnover;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["AccountFee"] = task_data->AccountFee;
		data["AccountFeeCurrencyGroup"] = toUtf(task_data->AccountFeeCurrencyGroup);
		data["AccountFeeCurrency"] = toUtf(task_data->AccountFeeCurrency);
		data["IsManualFee"] = task_data->IsManualFee;
		data["AccountOtherFee"] = task_data->AccountOtherFee;
		data["UpperFee"] = task_data->UpperFee;
		data["UpperFeeCurrencyGroup"] = toUtf(task_data->UpperFeeCurrencyGroup);
		data["UpperFeeCurrency"] = toUtf(task_data->UpperFeeCurrency);
		data["IsUpperManualFee"] = task_data->IsUpperManualFee;
		data["UpperOtherFee"] = task_data->UpperOtherFee;
		data["MatchDateTime"] = toUtf(task_data->MatchDateTime);
		data["UpperMatchDateTime"] = toUtf(task_data->UpperMatchDateTime);
		data["CloseProfit"] = task_data->CloseProfit;
		data["ClosePrice"] = task_data->ClosePrice;
		data["CloseQty"] = task_data->CloseQty;
		data["SettleGroupNo"] = toUtf(task_data->SettleGroupNo);
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		delete task_data;
	}
	this->onRspQryHisMatch(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisPositionQryRsp *task_data = (TapAPIHisPositionQryRsp*)task->task_data;
		data["SettleDate"] = toUtf(task_data->SettleDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["PositionNo"] = toUtf(task_data->PositionNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["CurrencyGroup"] = toUtf(task_data->CurrencyGroup);
		data["Currency"] = toUtf(task_data->Currency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["SettlePrice"] = task_data->SettlePrice;
		data["PositionDProfit"] = task_data->PositionDProfit;
		data["LMEPositionProfit"] = task_data->LMEPositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitialMargin"] = task_data->UpperInitialMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["SettleGroupNo"] = toUtf(task_data->SettleGroupNo);
		delete task_data;
	}
	this->onRspQryHisPosition(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisDelivery(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisDeliveryQryRsp *task_data = (TapAPIHisDeliveryQryRsp*)task->task_data;
		data["DeliveryDate"] = toUtf(task_data->DeliveryDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSource"] = task_data->MatchSource;
		data["OpenSide"] = task_data->OpenSide;
		data["OpenPrice"] = task_data->OpenPrice;
		data["DeliveryPrice"] = task_data->DeliveryPrice;
		data["DeliveryQty"] = task_data->DeliveryQty;
		data["FrozenQty"] = task_data->FrozenQty;
		data["OpenNo"] = toUtf(task_data->OpenNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["CommodityCurrencyGroupy"] = toUtf(task_data->CommodityCurrencyGroupy);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["DeliveryProfit"] = task_data->DeliveryProfit;
		data["AccountFrozenInitialMargin"] = task_data->AccountFrozenInitialMargin;
		data["AccountFrozenMaintenanceMargin"] = task_data->AccountFrozenMaintenanceMargin;
		data["UpperFrozenInitialMargin"] = task_data->UpperFrozenInitialMargin;
		data["UpperFrozenMaintenanceMargin"] = task_data->UpperFrozenMaintenanceMargin;
		data["AccountFeeCurrencyGroup"] = toUtf(task_data->AccountFeeCurrencyGroup);
		data["AccountFeeCurrency"] = toUtf(task_data->AccountFeeCurrency);
		data["AccountDeliveryFee"] = task_data->AccountDeliveryFee;
		data["UpperFeeCurrencyGroup"] = toUtf(task_data->UpperFeeCurrencyGroup);
		data["UpperFeeCurrency"] = toUtf(task_data->UpperFeeCurrency);
		data["UpperDeliveryFee"] = task_data->UpperDeliveryFee;
		data["DeliveryMode"] = task_data->DeliveryMode;
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		data["SettleGourpNo"] = toUtf(task_data->SettleGourpNo);
		delete task_data;
	}
	this->onRspQryHisDelivery(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryAccountCashAdjust(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountCashAdjustQryRsp *task_data = (TapAPIAccountCashAdjustQryRsp*)task->task_data;
		data["Date"] = toUtf(task_data->Date);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["CashAdjustType"] = task_data->CashAdjustType;
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["CashAdjustValue"] = task_data->CashAdjustValue;
		data["CashAdjustRemark"] = toUtf(task_data->CashAdjustRemark);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["AccountBank"] = toUtf(task_data->AccountBank);
		data["BankAccount"] = toUtf(task_data->BankAccount);
		data["AccountLWFlag"] = task_data->AccountLWFlag;
		data["CompanyBank"] = toUtf(task_data->CompanyBank);
		data["InternalBankAccount"] = toUtf(task_data->InternalBankAccount);
		data["CompanyLWFlag"] = task_data->CompanyLWFlag;
		delete task_data;
	}
	this->onRspQryAccountCashAdjust(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryBill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIBillQryRsp *task_data = (TapAPIBillQryRsp*)task->task_data;
		data["Reqdata"] = task_data->Reqdata;
		data["BillLen"] = task_data->BillLen;
		data["BillText"] = task_data->BillText;
		delete task_data;
	}
	this->onRspQryBill(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryAccountFeeRent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountFeeRentQryRsp *task_data = (TapAPIAccountFeeRentQryRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["MatchSource"] = task_data->MatchSource;
		data["CalculateMode"] = task_data->CalculateMode;
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["OpenCloseFee"] = task_data->OpenCloseFee;
		data["CloseTodayFee"] = task_data->CloseTodayFee;
		delete task_data;
	}
	this->onRspQryAccountFeeRent(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryAccountMarginRent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountMarginRentQryRsp *task_data = (TapAPIAccountMarginRentQryRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["CalculateMode"] = task_data->CalculateMode;
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["InitialMargin"] = task_data->InitialMargin;
		data["MaintenanceMargin"] = task_data->MaintenanceMargin;
		data["SellInitialMargin"] = task_data->SellInitialMargin;
		data["SellMaintenanceMargin"] = task_data->SellMaintenanceMargin;
		data["LockMargin"] = task_data->LockMargin;
		delete task_data;
	}
	this->onRspQryAccountMarginRent(task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspHKMarketOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderMarketInsertRsp *task_data = (TapAPIOrderMarketInsertRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["OrderType"] = task_data->OrderType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["OrderSource"] = task_data->OrderSource;
		data["BuyPositionEffect"] = task_data->BuyPositionEffect;
		data["SellPositionEffect"] = task_data->SellPositionEffect;
		data["OrderBuyPrice"] = task_data->OrderBuyPrice;
		data["OrderSellPrice"] = task_data->OrderSellPrice;
		data["OrderBuyQty"] = task_data->OrderBuyQty;
		data["OrderSellQty"] = task_data->OrderSellQty;
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderBuyNo"] = toUtf(task_data->OrderBuyNo);
		data["OrderSellNo"] = toUtf(task_data->OrderSellNo);
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["OrderMarketUserNo"] = toUtf(task_data->OrderMarketUserNo);
		data["OrderMarketTime"] = toUtf(task_data->OrderMarketTime);
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["ClientBuyOrderNo"] = toUtf(task_data->ClientBuyOrderNo);
		data["ClientSellOrderNo"] = toUtf(task_data->ClientSellOrderNo);
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		data["Remark"] = toUtf(task_data->Remark);
		delete task_data;
	}
	this->onRspHKMarketOrderInsert(task->task_id, task->task_int, data);
};

void TdApi::processRspHKMarketOrderDelete(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderMarketDeleteRsp *task_data = (TapAPIOrderMarketDeleteRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["OrderType"] = task_data->OrderType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["OrderSource"] = task_data->OrderSource;
		data["BuyPositionEffect"] = task_data->BuyPositionEffect;
		data["SellPositionEffect"] = task_data->SellPositionEffect;
		data["OrderBuyPrice"] = task_data->OrderBuyPrice;
		data["OrderSellPrice"] = task_data->OrderSellPrice;
		data["OrderBuyQty"] = task_data->OrderBuyQty;
		data["OrderSellQty"] = task_data->OrderSellQty;
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderBuyNo"] = toUtf(task_data->OrderBuyNo);
		data["OrderSellNo"] = toUtf(task_data->OrderSellNo);
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["OrderMarketUserNo"] = toUtf(task_data->OrderMarketUserNo);
		data["OrderMarketTime"] = toUtf(task_data->OrderMarketTime);
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["ClientBuyOrderNo"] = toUtf(task_data->ClientBuyOrderNo);
		data["ClientSellOrderNo"] = toUtf(task_data->ClientSellOrderNo);
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		data["Remark"] = toUtf(task_data->Remark);
		delete task_data;
	}
	this->onRspHKMarketOrderDelete(task->task_id, task->task_int, data);
};

void TdApi::processHKMarketQuoteNotice(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderQuoteMarketNotice *task_data = (TapAPIOrderQuoteMarketNotice*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["OrderSide"] = task_data->OrderSide;
		data["OrderQty"] = task_data->OrderQty;
		delete task_data;
	}
	this->onHKMarketQuoteNotice(data);
};

void TdApi::processRspOrderLocalRemove(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderLocalRemoveRsp *task_data = (TapAPIOrderLocalRemoveRsp*)task->task_data;
		data["req"] = task_data->req;
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		delete task_data;
	}
	this->onRspOrderLocalRemove(task->task_id, task->task_int, data);
};

void TdApi::processRspOrderLocalInput(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderLocalInputRsp *task_data = (TapAPIOrderLocalInputRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRspOrderLocalInput(task->task_id, task->task_int, data);
};

void TdApi::processRspOrderLocalModify(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderLocalModifyRsp *task_data = (TapAPIOrderLocalModifyRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRspOrderLocalModify(task->task_id, task->task_int, data);
};

void TdApi::processRspOrderLocalTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderLocalTransferRsp *task_data = (TapAPIOrderLocalTransferRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["ClientLocalIP"] = toUtf(task_data->ClientLocalIP);
		data["ClientMac"] = toUtf(task_data->ClientMac);
		data["ClientIP"] = toUtf(task_data->ClientIP);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRspOrderLocalTransfer(task->task_id, task->task_int, data);
};

void TdApi::processRspFillLocalInput(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFillLocalInputRsp *task_data = (TapAPIFillLocalInputRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchQty"] = task_data->MatchQty;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["UpperMatchNo"] = toUtf(task_data->UpperMatchNo);
		data["MatchDateTime"] = toUtf(task_data->MatchDateTime);
		data["UpperMatchDateTime"] = toUtf(task_data->UpperMatchDateTime);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["IsAddOne"] = task_data->IsAddOne;
		data["FeeCurrencyGroup"] = toUtf(task_data->FeeCurrencyGroup);
		data["FeeCurrency"] = toUtf(task_data->FeeCurrency);
		data["FeeValue"] = task_data->FeeValue;
		data["IsManualFee"] = task_data->IsManualFee;
		data["ClosePositionPrice"] = task_data->ClosePositionPrice;
		delete task_data;
	}
	this->onRspFillLocalInput(task->task_id, task->task_int, data);
};

void TdApi::processRspFillLocalRemove(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFillLocalRemoveRsp *task_data = (TapAPIFillLocalRemoveRsp*)task->task_data;
		data["ServerFlag"] = task_data->ServerFlag;
		data["MatchNo"] = toUtf(task_data->MatchNo);
		delete task_data;
	}
	this->onRspFillLocalRemove(task->task_id, task->task_int, data);
};

