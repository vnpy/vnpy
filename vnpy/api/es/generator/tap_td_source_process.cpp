void TdApi::processConnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onConnect(task->task_string);
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
		data["AuthType"] = task_data->AuthType;
		data["AuthDate"] = toUtf(task_data->AuthDate);
		delete task_data;
	}
	this->onRspLogin(task->task_string, task->task_int, data);
};

void TdApi::processRtnContactInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPISecondInfo *task_data = (TapAPISecondInfo*)task->task_data;
		data["SendType"] = task_data->SendType;
		data["SendAccount"] = toUtf(task_data->SendAccount);
		delete task_data;
	}
	this->onRtnContactInfo(task->task_string, task->task_int, task->task_last, data);
};

void TdApi::processRspRequestVertificateCode(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIVertificateCode *task_data = (TapAPIVertificateCode*)task->task_data;
		data["SecondSerialID"] = toUtf(task_data->SecondSerialID);
		data["Effective"] = task_data->Effective;
		delete task_data;
	}
	this->onRspRequestVertificateCode(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnErrorMsg(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRtnErrorMsg(task->task_string, task->task_string);
};

void TdApi::processAPIReady(Task *task)
{
	gil_scoped_acquire acquire;
	this->onAPIReady(task->task_string);
};

void TdApi::processDisconnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(task->task_string, task->task_int);
};

void TdApi::processRspSubmitUserLoginInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPISubmitUserLoginInfoRsp *task_data = (TapAPISubmitUserLoginInfoRsp*)task->task_data;
		data["UserNo"] = toUtf(task_data->UserNo);
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		delete task_data;
	}
	this->onRspSubmitUserLoginInfo(task->task_string, task->task_id, data);
};

void TdApi::processRspChangePassword(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspChangePassword(task->task_string, task->task_id, task->task_int);
};

void TdApi::processRspSetReservedInfo(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSetReservedInfo(task->task_string, task->task_id, task->task_int, task->task_string);
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
		data["ContractName"] = toUtf(task_data->ContractName);
		data["ContractExpDate"] = toUtf(task_data->ContractExpDate);
		data["LastTradeDate"] = toUtf(task_data->LastTradeDate);
		data["FirstNoticeDate"] = toUtf(task_data->FirstNoticeDate);
		data["FutureContractNo"] = toUtf(task_data->FutureContractNo);
		delete task_data;
	}
	this->onRtnContract(task->task_string, data);
};

void TdApi::processRtnFund(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFundData *task_data = (TapAPIFundData*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ParentAccountNo"] = task_data->ParentAccountNo;
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
		data["ExchangeFee"] = task_data->ExchangeFee;
		data["AccountDeliveryFee"] = task_data->AccountDeliveryFee;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["CloseProfit"] = task_data->CloseProfit;
		data["DeliveryProfit"] = task_data->DeliveryProfit;
		data["UnExpProfit"] = task_data->UnExpProfit;
		data["ExpProfit"] = task_data->ExpProfit;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LmePositionProfit"] = task_data->LmePositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitialMargin"] = task_data->UpperInitialMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["Discount"] = task_data->Discount;
		data["Balance"] = task_data->Balance;
		data["Equity"] = task_data->Equity;
		data["Available"] = task_data->Available;
		data["CanDraw"] = task_data->CanDraw;
		data["MarketEquity"] = task_data->MarketEquity;
		data["AuthMoney"] = task_data->AuthMoney;
		data["OriginalCashInOut"] = task_data->OriginalCashInOut;
		data["FloatingPL"] = task_data->FloatingPL;
		data["FrozenRiskFundValue"] = task_data->FrozenRiskFundValue;
		data["ClosePL"] = task_data->ClosePL;
		data["NoCurrencyPledgeValue"] = task_data->NoCurrencyPledgeValue;
		data["PrePledgeValue"] = task_data->PrePledgeValue;
		data["PledgeIn"] = task_data->PledgeIn;
		data["PledgeOut"] = task_data->PledgeOut;
		data["PledgeValue"] = task_data->PledgeValue;
		data["BorrowValue"] = task_data->BorrowValue;
		data["SpecialAccountFrozenMargin"] = task_data->SpecialAccountFrozenMargin;
		data["SpecialAccountMargin"] = task_data->SpecialAccountMargin;
		data["SpecialAccountFrozenFee"] = task_data->SpecialAccountFrozenFee;
		data["SpecialAccountFee"] = task_data->SpecialAccountFee;
		data["SpecialFloatProfit"] = task_data->SpecialFloatProfit;
		data["SpecialCloseProfit"] = task_data->SpecialCloseProfit;
		data["SpecialFloatPL"] = task_data->SpecialFloatPL;
		data["SpecialClosePL"] = task_data->SpecialClosePL;
		data["RiskRate"] = task_data->RiskRate;
		delete task_data;
	}
	this->onRtnFund(task->task_string, data);
};

void TdApi::processRtnOrder(Task *task)
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
		data["HedgeFlag2"] = task_data->HedgeFlag2;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderQty2"] = task_data->OrderQty2;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MarketLevel"] = task_data->MarketLevel;
		data["FutureAutoCloseFlag"] = task_data->FutureAutoCloseFlag;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ParentAccountNo"] = toUtf(task_data->ParentAccountNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentNo"] = task_data->OrderParentNo;
		data["OrderParentSystemNo"] = task_data->OrderParentSystemNo;
		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
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
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["ContractSize"] = task_data->ContractSize;
		data["ContractSize2"] = task_data->ContractSize2;
		data["CommodityCurrencyGroup"] = task_data->CommodityCurrencyGroup;
		data["CommodityCurrency"] = task_data->CommodityCurrency;
		data["FeeMode"] = task_data->FeeMode;
		data["FeeParam"] = task_data->FeeParam;
		data["FeeCurrencyGroup"] = task_data->FeeCurrencyGroup;
		data["FeeCurrency"] = task_data->FeeCurrency;
		data["FeeMode2"] = task_data->FeeMode2;
		data["FeeParam2"] = task_data->FeeParam2;
		data["FeeCurrencyGroup2"] = task_data->FeeCurrencyGroup2;
		data["FeeCurrency2"] = task_data->FeeCurrency2;
		data["MarginMode"] = task_data->MarginMode;
		data["MarginParam"] = task_data->MarginParam;
		data["MarginMode2"] = task_data->MarginMode2;
		data["MarginParam2"] = task_data->MarginParam2;
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["PreSettlePrice2"] = task_data->PreSettlePrice2;
		data["OpenVol"] = task_data->OpenVol;
		data["CoverVol"] = task_data->CoverVol;
		data["OpenVol2"] = task_data->OpenVol2;
		data["CoverVol2"] = task_data->CoverVol2;
		data["FeeValue"] = task_data->FeeValue;
		data["MarginValue"] = task_data->MarginValue;
		data["OrderDeleteByDisConnFlag"] = task_data->OrderDeleteByDisConnFlag;
		delete task_data;
	}
	this->onRtnOrder(task->task_string, task->task_id, data);
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
		data["HedgeFlag2"] = task_data->HedgeFlag2;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderQty2"] = task_data->OrderQty2;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MarketLevel"] = task_data->MarketLevel;
		data["FutureAutoCloseFlag"] = task_data->FutureAutoCloseFlag;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ParentAccountNo"] = toUtf(task_data->ParentAccountNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentNo"] = task_data->OrderParentNo;
		data["OrderParentSystemNo"] = task_data->OrderParentSystemNo;
		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
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
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["ContractSize"] = task_data->ContractSize;
		data["ContractSize2"] = task_data->ContractSize2;
		data["CommodityCurrencyGroup"] = task_data->CommodityCurrencyGroup;
		data["CommodityCurrency"] = task_data->CommodityCurrency;
		data["FeeMode"] = task_data->FeeMode;
		data["FeeParam"] = task_data->FeeParam;
		data["FeeCurrencyGroup"] = task_data->FeeCurrencyGroup;
		data["FeeCurrency"] = task_data->FeeCurrency;
		data["FeeMode2"] = task_data->FeeMode2;
		data["FeeParam2"] = task_data->FeeParam2;
		data["FeeCurrencyGroup2"] = task_data->FeeCurrencyGroup2;
		data["FeeCurrency2"] = task_data->FeeCurrency2;
		data["MarginMode"] = task_data->MarginMode;
		data["MarginParam"] = task_data->MarginParam;
		data["MarginMode2"] = task_data->MarginMode2;
		data["MarginParam2"] = task_data->MarginParam2;
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["PreSettlePrice2"] = task_data->PreSettlePrice2;
		data["OpenVol"] = task_data->OpenVol;
		data["CoverVol"] = task_data->CoverVol;
		data["OpenVol2"] = task_data->OpenVol2;
		data["CoverVol2"] = task_data->CoverVol2;
		data["FeeValue"] = task_data->FeeValue;
		data["MarginValue"] = task_data->MarginValue;
		data["OrderDeleteByDisConnFlag"] = task_data->OrderDeleteByDisConnFlag;
		delete task_data;
	}
	this->onRspQryOrderProcess(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnFill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFillInfo *task_data = (TapAPIFillInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ParentAccountNo"] = task_data->ParentAccountNo;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ExchangeNoRef"] = task_data->ExchangeNoRef;
		data["CommodityTypeRef"] = task_data->CommodityTypeRef;
		data["CommodityNoRef"] = task_data->CommodityNoRef;
		data["ContractNoRef"] = task_data->ContractNoRef;
		data["StrikePriceRef"] = task_data->StrikePriceRef;
		data["CallOrPutFlagRef"] = task_data->CallOrPutFlagRef;
		data["OrderExchangeNo"] = task_data->OrderExchangeNo;
		data["OrderCommodityType"] = task_data->OrderCommodityType;
		data["OrderCommodityNo"] = task_data->OrderCommodityNo;
		data["OrderType"] = task_data->OrderType;
		data["MatchSource"] = task_data->MatchSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffectRef"] = task_data->PositionEffectRef;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchDateTime"] = toUtf(task_data->MatchDateTime);
		data["UpperMatchDateTime"] = toUtf(task_data->UpperMatchDateTime);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchQty"] = task_data->MatchQty;
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["MatchStreamID"] = task_data->MatchStreamID;
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OpenCloseMode"] = task_data->OpenCloseMode;
		data["ContractSize"] = task_data->ContractSize;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["FeeMode"] = task_data->FeeMode;
		data["FeeParam"] = task_data->FeeParam;
		data["FeeCurrencyGroup"] = toUtf(task_data->FeeCurrencyGroup);
		data["FeeCurrency"] = toUtf(task_data->FeeCurrency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["FeeValue"] = task_data->FeeValue;
		data["IsManualFee"] = task_data->IsManualFee;
		data["Turnover"] = task_data->Turnover;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["OppoMatchNo"] = task_data->OppoMatchNo;
		data["CloseProfit"] = task_data->CloseProfit;
		data["UnExpProfit"] = task_data->UnExpProfit;
		data["UpperMatchPrice"] = task_data->UpperMatchPrice;
		data["QuotePrice"] = task_data->QuotePrice;
		data["ClosePL"] = task_data->ClosePL;
		delete task_data;
	}
	this->onRtnFill(task->task_string, data);
};

void TdApi::processRtnPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionInfo *task_data = (TapAPIPositionInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ParentAccountNo"] = task_data->ParentAccountNo;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ExchangeNoRef"] = task_data->ExchangeNoRef;
		data["CommodityTypeRef"] = task_data->CommodityTypeRef;
		data["CommodityNoRef"] = task_data->CommodityNoRef;
		data["ContractNoRef"] = task_data->ContractNoRef;
		data["StrikePriceRef"] = task_data->StrikePriceRef;
		data["CallOrPutFlagRef"] = task_data->CallOrPutFlagRef;
		data["OrderExchangeNo"] = task_data->OrderExchangeNo;
		data["OrderCommodityType"] = task_data->OrderCommodityType;
		data["OrderCommodityNo"] = task_data->OrderCommodityNo;
		data["OrderType"] = task_data->OrderType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = task_data->ExpireTime;
		data["MatchSide"] = task_data->MatchSide;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["PositionNo"] = toUtf(task_data->PositionNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchSource"] = task_data->MatchSource;
		data["MatchDate"] = task_data->MatchDate;
		data["MatchTime"] = task_data->MatchTime;
		data["UpperMatchTime"] = task_data->UpperMatchTime;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsAddOne"] = task_data->IsAddOne;
		data["MatchStreamID"] = task_data->MatchStreamID;
		data["PositionStreamId"] = task_data->PositionStreamId;
		data["OpenCloseMode"] = task_data->OpenCloseMode;
		data["ContractSize"] = task_data->ContractSize;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["SettlePrice"] = task_data->SettlePrice;
		data["Turnover"] = task_data->Turnover;
		data["AccountMarginMode"] = task_data->AccountMarginMode;
		data["AccountMarginParam"] = task_data->AccountMarginParam;
		data["UpperMarginMode"] = task_data->UpperMarginMode;
		data["UpperMarginParam"] = task_data->UpperMarginParam;
		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitialMargin"] = task_data->UpperInitialMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LMEPositionProfit"] = task_data->LMEPositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["MatchCmbNo"] = toUtf(task_data->MatchCmbNo);
		data["IsHistory"] = task_data->IsHistory;
		data["FloatingPL"] = task_data->FloatingPL;
		data["CalculatePrice"] = task_data->CalculatePrice;
		delete task_data;
	}
	this->onRtnPosition(task->task_string, data);
};

void TdApi::processRtnClose(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPICloseInfo *task_data = (TapAPICloseInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ParentAccountNo"] = task_data->ParentAccountNo;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["OpenOrderExchangeNo"] = task_data->OpenOrderExchangeNo;
		data["OpenOrderCommodityType"] = task_data->OpenOrderCommodityType;
		data["OpenOrderCommodityNo"] = task_data->OpenOrderCommodityNo;
		data["CloseOrderExchangeNo"] = task_data->CloseOrderExchangeNo;
		data["CloseOrderCommodityType"] = task_data->CloseOrderCommodityType;
		data["CloseOrderCommodityNo"] = task_data->CloseOrderCommodityNo;
		data["OpenMatchSource"] = task_data->OpenMatchSource;
		data["CloseMatchSource"] = task_data->CloseMatchSource;
		data["CloseSide"] = task_data->CloseSide;
		data["CloseQty"] = task_data->CloseQty;
		data["OpenPrice"] = task_data->OpenPrice;
		data["ClosePrice"] = task_data->ClosePrice;
		data["OpenServerFlag"] = task_data->OpenServerFlag;
		data["OpenOrderNo"] = toUtf(task_data->OpenOrderNo);
		data["OpenMatchNo"] = toUtf(task_data->OpenMatchNo);
		data["OpenExchangeMatchNo"] = toUtf(task_data->OpenExchangeMatchNo);
		data["OpenMatchDateTime"] = toUtf(task_data->OpenMatchDateTime);
		data["CloseServerFlag"] = task_data->CloseServerFlag;
		data["CloseOrderNo"] = toUtf(task_data->CloseOrderNo);
		data["CloseMatchNo"] = toUtf(task_data->CloseMatchNo);
		data["CloseExchangeMatchNo"] = toUtf(task_data->CloseExchangeMatchNo);
		data["CloseMatchDateTime"] = toUtf(task_data->CloseMatchDateTime);
		data["CloseStreamId"] = task_data->CloseStreamId;
		data["OpenCloseMode"] = task_data->OpenCloseMode;
		data["ContractSize"] = task_data->ContractSize;
		data["CommodityCurrencyGroup"] = task_data->CommodityCurrencyGroup;
		data["CommodityCurrency"] = task_data->CommodityCurrency;
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["CloseProfit"] = task_data->CloseProfit;
		data["UnExpProfit"] = task_data->UnExpProfit;
		data["ClosePL"] = task_data->ClosePL;
		delete task_data;
	}
	this->onRtnClose(task->task_string, data);
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
	this->onRtnPositionProfit(task->task_string, data);
};

void TdApi::processRspQryDeepQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIDeepQuoteQryRsp *task_data = (TapAPIDeepQuoteQryRsp*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["DeepQuote"] = task_data->DeepQuote;
		delete task_data;
	}
	this->onRspQryDeepQuote(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnExchangeStateInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIExchangeStateInfoNotice *task_data = (TapAPIExchangeStateInfoNotice*)task->task_data;
		data["IsLast"] = task_data->IsLast;
		data["ExchangeStateInfo"] = task_data->ExchangeStateInfo;
		delete task_data;
	}
	this->onRtnExchangeStateInfo(task->task_string, data);
};

void TdApi::processRtnReqQuoteNotice(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIReqQuoteNotice *task_data = (TapAPIReqQuoteNotice*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["UpdateTime"] = toUtf(task_data->UpdateTime);
		delete task_data;
	}
	this->onRtnReqQuoteNotice(task->task_string, data);
};

void TdApi::processRspAccountRentInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountRentInfo *task_data = (TapAPIAccountRentInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["MatchSource"] = task_data->MatchSource;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["FeeMode"] = task_data->FeeMode;
		data["OpenTurnover"] = task_data->OpenTurnover;
		data["ClosedTurnover"] = task_data->ClosedTurnover;
		data["CloseNewTurnover"] = task_data->CloseNewTurnover;
		data["OpenVolume"] = task_data->OpenVolume;
		data["ClosedVolume"] = task_data->ClosedVolume;
		data["CloseNewVolume"] = task_data->CloseNewVolume;
		data["MarginMode"] = task_data->MarginMode;
		data["BuyTInitMargin"] = task_data->BuyTInitMargin;
		data["SellTInitMargin"] = task_data->SellTInitMargin;
		data["BuyBInitMargin"] = task_data->BuyBInitMargin;
		data["SellBInitMargin"] = task_data->SellBInitMargin;
		data["BuyLInitMargin"] = task_data->BuyLInitMargin;
		data["SellLInitMargin"] = task_data->SellLInitMargin;
		data["BuyMInitMargin"] = task_data->BuyMInitMargin;
		data["SellMInitMargin"] = task_data->SellMInitMargin;
		data["BuyTMaintMargin"] = task_data->BuyTMaintMargin;
		data["SellTMaintMargin"] = task_data->SellTMaintMargin;
		data["BuyBMaintMargin"] = task_data->BuyBMaintMargin;
		data["SellBMaintMargin"] = task_data->SellBMaintMargin;
		data["BuyLMaintMargin"] = task_data->BuyLMaintMargin;
		data["SellLMaintMargin"] = task_data->SellLMaintMargin;
		data["BuyMMaintMargin"] = task_data->BuyMMaintMargin;
		data["SellMMaintMargin"] = task_data->SellMMaintMargin;
		delete task_data;
	}
	this->onRspAccountRentInfo(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspTradeMessage(Task *task)
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
	this->onRspTradeMessage(task->task_string, task->task_id, task->task_int, task->task_last, data);
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
	this->onRtnTradeMessage(task->task_string, data);
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
	this->onRspQryHisOrder(task->task_string, task->task_id, task->task_int, task->task_last, data);
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
	this->onRspQryHisOrderProcess(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisFill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisFillQryRsp *task_data = (TapAPIHisFillQryRsp*)task->task_data;
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
	this->onRspQryHisFill(task->task_string, task->task_id, task->task_int, task->task_last, data);
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
	this->onRspQryHisPosition(task->task_string, task->task_id, task->task_int, task->task_last, data);
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
	this->onRspQryHisDelivery(task->task_string, task->task_id, task->task_int, task->task_last, data);
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
	this->onRspQryAccountCashAdjust(task->task_string, task->task_id, task->task_int, task->task_last, data);
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
	this->onRspQryBill(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspAccountFeeRent(Task *task)
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
	this->onRspAccountFeeRent(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspAccountMarginRent(Task *task)
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
	this->onRspAccountMarginRent(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspAddMobileDevice(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIMobileDeviceAddRsp *task_data = (TapAPIMobileDeviceAddRsp*)task->task_data;
		data["UserNo"] = toUtf(task_data->UserNo);
		data["AppKey"] = toUtf(task_data->AppKey);
		data["AppID"] = toUtf(task_data->AppID);
		data["MasterSecret"] = toUtf(task_data->MasterSecret);
		data["Cid"] = toUtf(task_data->Cid);
		data["CompanyNo"] = toUtf(task_data->CompanyNo);
		data["CompanyAddressNo"] = toUtf(task_data->CompanyAddressNo);
		data["DeviceType"] = task_data->DeviceType;
		delete task_data;
	}
	this->onRspAddMobileDevice(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryManageInfoForEStar(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIManageInfo *task_data = (TapAPIManageInfo*)task->task_data;
		data["MsgID"] = task_data->MsgID;
		data["SendFrom"] = toUtf(task_data->SendFrom);
		data["SendManageType"] = task_data->SendManageType;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["SendAccount"] = toUtf(task_data->SendAccount);
		data["Title"] = toUtf(task_data->Title);
		data["Content"] = toUtf(task_data->Content);
		data["Attachment"] = toUtf(task_data->Attachment);
		data["SendStatus"] = task_data->SendStatus;
		data["Remark"] = toUtf(task_data->Remark);
		data["GUID"] = toUtf(task_data->GUID);
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		delete task_data;
	}
	this->onRspQryManageInfoForEStar(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQrySystemParameter(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPISystemParameterInfo *task_data = (TapAPISystemParameterInfo*)task->task_data;
		data["ItemNo"] = toUtf(task_data->ItemNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["CommodityType"] = task_data->CommodityType;
		data["ItemValue"] = task_data->ItemValue;
		data["ItemValueStr"] = toUtf(task_data->ItemValueStr);
		data["ItemValueDouble"] = task_data->ItemValueDouble;
		delete task_data;
	}
	this->onRspQrySystemParameter(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryTradeCenterFrontAddress(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeCenterFrontAddressInfo *task_data = (TapAPITradeCenterFrontAddressInfo*)task->task_data;
		data["FrontName"] = toUtf(task_data->FrontName);
		data["FrontAddress"] = toUtf(task_data->FrontAddress);
		data["FrontPort"] = toUtf(task_data->FrontPort);
		data["TradeCenter"] = task_data->TradeCenter;
		data["IsEnable"] = task_data->IsEnable;
		data["IsSSL"] = task_data->IsSSL;
		delete task_data;
	}
	this->onRspQryTradeCenterFrontAddress(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnCommodityInfo(Task *task)
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
		data["TradeCurrency"] = toUtf(task_data->TradeCurrency);
		data["ContractSize"] = task_data->ContractSize;
		data["OpenCloseMode"] = task_data->OpenCloseMode;
		data["StrikePriceTimes"] = task_data->StrikePriceTimes;
		data["CommodityTickSize"] = task_data->CommodityTickSize;
		data["CommodityDenominator"] = task_data->CommodityDenominator;
		data["CmbDirect"] = task_data->CmbDirect;
		data["OnlyCanCloseDays"] = task_data->OnlyCanCloseDays;
		data["DeliveryMode"] = task_data->DeliveryMode;
		data["DeliveryDays"] = task_data->DeliveryDays;
		data["AddOneTime"] = toUtf(task_data->AddOneTime);
		data["CommodityTimeZone"] = task_data->CommodityTimeZone;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRtnCommodityInfo(task->task_string, data);
};

void TdApi::processRtnCurrencyInfo(Task *task)
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
	this->onRtnCurrencyInfo(task->task_string, data);
};

