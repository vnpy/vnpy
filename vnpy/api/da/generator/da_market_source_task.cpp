void MarketApi::OnFrontConnected() 
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void MarketApi::OnFrontDisconnected(int iReason) 
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(iReason);
};

void MarketApi::OnHeartBeatWarning(int iTimeLapse) 
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(iTimeLapse);
};

void MarketApi::OnRspRawData(const char* rawData) 
{
	gil_scoped_acquire acquire;
	this->onRspRawData(string(rawData));
};

void MarketApi::OnRspUserLogin(CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) 
{
	gil_scoped_acquire acquire;
	dict error;
	if (pRspInfo)
	{
		error["ErrorID"] = pRspInfo->ErrorID;
		error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
	}
	this->onRspUserLogin(error, iRequestID, bIsLast);
};

void MarketApi::OnRspTradeDate(CMarketRspTradeDateField *pRspTradeDate, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (pRspTradeDate)
	{
		data["TradeDate"] = toUtf(pRspTradeDate->TradeDate);
		data["TradeProduct"] = toUtf(pRspTradeDate->TradeProduct);
	}
	dict error;
	if (pRspInfo)
	{
		error["ErrorID"] = pRspInfo->ErrorID;
		error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
	}
	this->onRspTradeDate(data, error, iRequestID, bIsLast);
};

void MarketApi::OnRspBrokerData(CMarketRspBrokerDataField *pRspBrokerData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (pRspBrokerData)
	{
		data["BrokerData"] = toUtf(pRspBrokerData->BrokerData);
	}
	dict error;
	if (pRspInfo)
	{
		error["ErrorID"] = pRspInfo->ErrorID;
		error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
	}
	this->onRspBrokerData(data, error, iRequestID, bIsLast);
};

void MarketApi::OnRspMarketData(CMarketRspMarketDataField *pRspMarketData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (pRspMarketData)
	{
		data["ExchangeCode"] = toUtf(pRspMarketData->ExchangeCode);
		data["TreatyCode"] = toUtf(pRspMarketData->TreatyCode);
		data["BuyPrice"] = toUtf(pRspMarketData->BuyPrice);
		data["BuyNumber"] = toUtf(pRspMarketData->BuyNumber);
		data["SalePrice"] = toUtf(pRspMarketData->SalePrice);
		data["SaleNumber"] = toUtf(pRspMarketData->SaleNumber);
		data["CurrPrice"] = toUtf(pRspMarketData->CurrPrice);
		data["CurrNumber"] = toUtf(pRspMarketData->CurrNumber);
		data["High"] = toUtf(pRspMarketData->High);
		data["Low"] = toUtf(pRspMarketData->Low);
		data["Open"] = toUtf(pRspMarketData->Open);
		data["IntradaySettlePrice"] = toUtf(pRspMarketData->IntradaySettlePrice);
		data["Close"] = toUtf(pRspMarketData->Close);
		data["Time"] = toUtf(pRspMarketData->Time);
		data["FilledNum"] = toUtf(pRspMarketData->FilledNum);
		data["HoldNum"] = toUtf(pRspMarketData->HoldNum);
		data["BuyPrice2"] = toUtf(pRspMarketData->BuyPrice2);
		data["BuyPrice3"] = toUtf(pRspMarketData->BuyPrice3);
		data["BuyPrice4"] = toUtf(pRspMarketData->BuyPrice4);
		data["BuyPrice5"] = toUtf(pRspMarketData->BuyPrice5);
		data["BuyNumber2"] = toUtf(pRspMarketData->BuyNumber2);
		data["BuyNumber3"] = toUtf(pRspMarketData->BuyNumber3);
		data["BuyNumber4"] = toUtf(pRspMarketData->BuyNumber4);
		data["BuyNumber5"] = toUtf(pRspMarketData->BuyNumber5);
		data["SalePrice2"] = toUtf(pRspMarketData->SalePrice2);
		data["SalePrice3"] = toUtf(pRspMarketData->SalePrice3);
		data["SalePrice4"] = toUtf(pRspMarketData->SalePrice4);
		data["SalePrice5"] = toUtf(pRspMarketData->SalePrice5);
		data["SaleNumber2"] = toUtf(pRspMarketData->SaleNumber2);
		data["SaleNumber3"] = toUtf(pRspMarketData->SaleNumber3);
		data["SaleNumber4"] = toUtf(pRspMarketData->SaleNumber4);
		data["SaleNumber5"] = toUtf(pRspMarketData->SaleNumber5);
		data["HideBuyPrice"] = toUtf(pRspMarketData->HideBuyPrice);
		data["HideBuyNumber"] = toUtf(pRspMarketData->HideBuyNumber);
		data["HideSalePrice"] = toUtf(pRspMarketData->HideSalePrice);
		data["HideSaleNumber"] = toUtf(pRspMarketData->HideSaleNumber);
		data["LimitDownPrice"] = toUtf(pRspMarketData->LimitDownPrice);
		data["LimitUpPrice"] = toUtf(pRspMarketData->LimitUpPrice);
		data["TradeDay"] = toUtf(pRspMarketData->TradeDay);
		data["BuyPrice6"] = toUtf(pRspMarketData->BuyPrice6);
		data["BuyPrice7"] = toUtf(pRspMarketData->BuyPrice7);
		data["BuyPrice8"] = toUtf(pRspMarketData->BuyPrice8);
		data["BuyPrice9"] = toUtf(pRspMarketData->BuyPrice9);
		data["BuyPrice10"] = toUtf(pRspMarketData->BuyPrice10);
		data["BuyNumber6"] = toUtf(pRspMarketData->BuyNumber6);
		data["BuyNumber7"] = toUtf(pRspMarketData->BuyNumber7);
		data["BuyNumber8"] = toUtf(pRspMarketData->BuyNumber8);
		data["BuyNumber9"] = toUtf(pRspMarketData->BuyNumber9);
		data["BuyNumber10"] = toUtf(pRspMarketData->BuyNumber10);
		data["SalePrice6"] = toUtf(pRspMarketData->SalePrice6);
		data["SalePrice7"] = toUtf(pRspMarketData->SalePrice7);
		data["SalePrice8"] = toUtf(pRspMarketData->SalePrice8);
		data["SalePrice9"] = toUtf(pRspMarketData->SalePrice9);
		data["SalePrice10"] = toUtf(pRspMarketData->SalePrice10);
		data["SaleNumber6"] = toUtf(pRspMarketData->SaleNumber6);
		data["SaleNumber7"] = toUtf(pRspMarketData->SaleNumber7);
		data["SaleNumber8"] = toUtf(pRspMarketData->SaleNumber8);
		data["SaleNumber9"] = toUtf(pRspMarketData->SaleNumber9);
		data["SaleNumber10"] = toUtf(pRspMarketData->SaleNumber10);
		data["TradeFlag"] = toUtf(pRspMarketData->TradeFlag);
		data["DataTimestamp"] = toUtf(pRspMarketData->DataTimestamp);
		data["DataSourceId"] = toUtf(pRspMarketData->DataSourceId);
		data["CanSellVol"] = toUtf(pRspMarketData->CanSellVol);
		data["QuoteType"] = toUtf(pRspMarketData->QuoteType);
		data["AggressorSide"] = toUtf(pRspMarketData->AggressorSide);
		data["PreSettlementPrice"] = toUtf(pRspMarketData->PreSettlementPrice);
	}
	dict error;
	if (pRspInfo)
	{
		error["ErrorID"] = pRspInfo->ErrorID;
		error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
	}
	this->onRspMarketData(data, error, iRequestID, bIsLast);
};

