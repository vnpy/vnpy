CIStoneReqUserLogin = {
    "TradingDay": "string",
    "UserID": "string",
    "Password": "string",
    "UserProductInfo": "string",
    "IPAddress": "string",
    "MacAddress": "string",
}

CIStoneRspUserLogin = {
    "TradingDay": "string",
    "UserID": "string",
    "MaxUserOrderLocalID": "int",
    "LoginTime": "string",
    "userType": "enum",
}

CIStoneReqUserLogout = {
    "UserID": "string",
}

CIStoneRspUserLogout = {
    "UserID": "string",
}

CIStoneSubParams = {
    "TickType": "int",
    "ExchangeType": "int",
}

CIStoneRspSubTickByTick = {
    "SubAllFlag": "int16_t",
    "ExchangeID": "enum",
    "Ticker": "string",
}

CIStoneRspUnSubTickByTick = {
    "UnSubAllFlag": "int16_t",
    "ExchangeID": "enum",
    "Ticker": "string",
}

CIStoneRspInfo = {
    "Tid": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

ISTONE_MARKETDATA_TYPE = {
    "ISTONE_MARKETDATA_ACTUAL": "int",
    "ISTONE_MARKETDATA_OPTION": "int",
}

CIStoneQryMarketData = {
    "ExchangeID": "enum",
    "Ticker": "string",
}

CIStoneSpecificTicker = {
    "ExchangeID": "enum",
    "Ticker": "string",
}

CIStoneMarketDataStockExData = {
    "TotalBidQty": "int64_t",
    "TotalAskQty": "int64_t",
    "MaBidPrice": "double",
    "MaAskPrice": "double",
    "MaBondBidPrice": "double",
    "MaBondAskPrice": "double",
    "YieldToMaturity": "double",
    "Iopv": "double",
    "EtfBuyCount": "int32_t",
    "EtfSellCount": "int32_t",
    "EtfBuyQty": "double",
    "EtfBuyMoney": "double",
    "EtfSellQty": "double",
    "EtfSellMoney": "double",
    "TotalWarrantExecQty": "double",
    "WarrantLowerPrice": "double",
    "WarrantUpperPrice": "double",
    "CancelBuyCount": "int32_t",
    "CancelSellCount": "int32_t",
    "CancelBuyQty": "double",
    "CancelSellQty": "double",
    "CancelBuyMoney": "double",
    "CancelSellMoney": "double",
    "TotalBuyCount": "int64_t",
    "TotalSellCount": "int64_t",
    "DurationAfterBuy": "int32_t",
    "DurationAfterSell": "int32_t",
    "NumBidOrders": "int32_t",
    "NumAskOrders": "int32_t",
    "PreIopv": "double",
    "R1": "int64_t",
    "R2": "int64_t",
}

CIStoneMarketDataOptionExData = {
    "AuctionPrice": "double",
    "AuctionQty": "int64_t",
    "LastEnquiryTime": "int64_t",
}

CIStoneTickerBid1 = {
    "Bid1NumOfOrders": "uint32_t",
    "Bid1NoOrders": "uint8_t",
    "Bid1Orders": "string",
    "Ask1NumOfOrders": "uint32_t",
    "Ask1NoOrders": "uint8_t",
    "Ask1Orders": "string",
}

CIStoneDepthMarketData = {
    "ExchangeID": "enum",
    "TickerType": "enum",
    "Ticker": "string",
    "LastPrice": "double",
    "PreClosePrice": "double",
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "ClosePrice": "double",
    "PreOpenInterest": "int64_t",
    "OpenInterest": "int64_t",
    "PreSettlementPrice": "double",
    "SettlementPrice": "double",
    "PreDelta": "double",
    "CurrDelta": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "DateTime": "int64_t",
    "Qty": "int64_t",
    "Turnover": "double",
    "AvgPrice": "double",
    "Bid": "string",
    "Ask": "string",
    "BidQty": "string",
    "AskQty": "string",
    "TradesCount": "int64_t",
    "TickerStatus": "string",
    "tickBid1": "dict",
    "DataType": "dict",
    "Stk": "dict",
    "Opt": "dict",
    "R4": "int32_t",
}

CIStoneQuoteStaticInfo = {
    "ExchangeID": "enum",
    "Ticker": "string",
    "TickerName": "string",
    "TickerType": "enum",
    "PreClosePrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "PriceTick": "double",
    "BuyQtyUnit": "int32_t",
    "SellQtyUnit": "int32_t",
}

CIStoneOrderBook = {
    "ExchangeID": "enum",
    "Ticker": "string",
    "LastPrice": "double",
    "Qty": "int64_t",
    "Turnover": "double",
    "TradesCount": "int64_t",
    "Bid": "string",
    "Ask": "string",
    "BidQty": "string",
    "AskQty": "string",
    "DataTime": "int64_t",
    "bidSeq": "string",
    "askSeq": "string",
}

CIStoneTickByTickEntrust = {
    "ChannalNo": "int32_t",
    "Seq": "int64_t",
    "Price": "double",
    "Qty": "int64_t",
    "Side": "char",
    "OrdType": "char",
}

CIStoneTickByTickTrade = {
    "ChannalNo": "int32_t",
    "Seq": "int64_t",
    "Price": "double",
    "Qty": "int64_t",
    "Money": "double",
    "BidNo": "int64_t",
    "AskNo": "int64_t",
    "TradeFlag": "char",
}

CIStoneTickByTick = {
    "ExchangeID": "enum",
    "Ticker": "string",
    "Seq": "int64_t",
    "DataTime": "int64_t",
    "Type": "enum",
    "Entrust": "dict",
    "Trade": "dict",
}

CIStoneTickerPriceInfo = {
    "ExchangeID": "enum",
    "Ticker": "string",
    "LastPrice": "double",
}
