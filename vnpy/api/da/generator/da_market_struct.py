CMarketRspInfoField = {
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CMarketReqUserLoginField = {
    "UserId": "string",
    "UserPwd": "string",
    "UserType": "string",
    "MacAddress": "string",
    "ComputerName": "string",
    "SoftwareName": "string",
    "SoftwareVersion": "string",
    "AuthorCode": "string",
    "ErrorDescription": "string",
}

CMarketRspUserLoginField = {
    "UserName": "string",
    "UserPwd": "string",
    "UserType": "string",
}

CMarketReqUserLogoutField = {
    "BrokerID": "string",
    "UserId": "string",
    "ErrorDescription": "string",
}

CMarketReqMarketDataField = {
    "MarketType": "char",
    "SubscMode": "char",
    "MarketCount": "int",
    "MarketTrcode[MAX_SUB_COUNT]": "string",
    "ErrorDescription": "string",
}

CMarketRspMarketDataField = {
    "ExchangeCode": "string",
    "TreatyCode": "string",
    "BuyPrice": "string",
    "BuyNumber": "string",
    "SalePrice": "string",
    "SaleNumber": "string",
    "CurrPrice": "string",
    "CurrNumber": "string",
    "High": "string",
    "Low": "string",
    "Open": "string",
    "IntradaySettlePrice": "string",
    "Close": "string",
    "Time": "string",
    "FilledNum": "string",
    "HoldNum": "string",
    "BuyPrice2": "string",
    "BuyPrice3": "string",
    "BuyPrice4": "string",
    "BuyPrice5": "string",
    "BuyNumber2": "string",
    "BuyNumber3": "string",
    "BuyNumber4": "string",
    "BuyNumber5": "string",
    "SalePrice2": "string",
    "SalePrice3": "string",
    "SalePrice4": "string",
    "SalePrice5": "string",
    "SaleNumber2": "string",
    "SaleNumber3": "string",
    "SaleNumber4": "string",
    "SaleNumber5": "string",
    "HideBuyPrice": "string",
    "HideBuyNumber": "string",
    "HideSalePrice": "string",
    "HideSaleNumber": "string",
    "LimitDownPrice": "string",
    "LimitUpPrice": "string",
    "TradeDay": "string",
    "BuyPrice6": "string",
    "BuyPrice7": "string",
    "BuyPrice8": "string",
    "BuyPrice9": "string",
    "BuyPrice10": "string",
    "BuyNumber6": "string",
    "BuyNumber7": "string",
    "BuyNumber8": "string",
    "BuyNumber9": "string",
    "BuyNumber10": "string",
    "SalePrice6": "string",
    "SalePrice7": "string",
    "SalePrice8": "string",
    "SalePrice9": "string",
    "SalePrice10": "string",
    "SaleNumber6": "string",
    "SaleNumber7": "string",
    "SaleNumber8": "string",
    "SaleNumber9": "string",
    "SaleNumber10": "string",
    "TradeFlag": "string",
    "DataTimestamp": "string",
    "DataSourceId": "string",
    "CanSellVol": "string",
    "QuoteType": "string",
    "AggressorSide": "string",
    "PreSettlementPrice": "string",
}

CMarketReqBrokerDataField = {
    "ContCode": "string",
    "ErrorDescription": "string",
}

CMarketRspBrokerDataField = {
    "BrokerData": "string",
}

CMarketRspTradeDateField = {
    "TradeDate": "string",
    "TradeProduct": "string",
}
