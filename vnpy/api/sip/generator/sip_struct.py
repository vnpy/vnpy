t_SH_StockMarketDataL2 = {
    "nTime": "T_I32",
    "nStatus": "T_I32",
    "uPreClose": "T_U32",
    "uOpen": "T_U32",
    "uHigh": "T_U32",
    "uLow": "T_U32",
    "uMatch": "T_U32",
    "uAskPrice": "T_U32",
    "uAskVol": "T_U32",
    "uBidPrice": "T_U32",
    "uBidVol": "T_U32",
    "uNumTrades": "T_U32",
    "iVolume": "T_I64",
    "iTurnover": "T_I64",
    "iTotalBidVol": "T_I64",
    "iTotalAskVol": "T_I64",
    "uWeightedAvgBidPrice": "T_U32",
    "uWeightedAvgAskPrice": "T_U32",
    "nIOPV": "T_I32",
    "nYieldToMaturity": "T_I32",
    "uHighLimited": "T_U32",
    "uLowLimited": "T_U32",
    "sPrefix": "char",
    "nSyl1": "T_I32",
    "nSyl2": "T_I32",
    "nSD2": "T_I32",
    "sTradingPhraseCode": "char",
    "nPreIOPV": "T_I32",
}

Stock_MarketData = t_SH_StockMarketDataL2
T_SH_StockMarketDataL2 = t_SH_StockMarketDataL2
t_SH_StockMarketDataL1 = {
    "nTime": "T_I32",
    "nStatus": "T_I32",
    "uPreClose": "T_U32",
    "uOpen": "T_U32",
    "uHigh": "T_U32",
    "uLow": "T_U32",
    "uMatch": "T_U32",
    "uAskPrice": "T_U32",
    "uAskVol": "T_U32",
    "uBidPrice": "T_U32",
    "uBidVol": "T_U32",
    "uNumTrades": "T_U32",
    "iVolume": "T_I64",
    "iTurnover": "T_I64",
    "uHighLimited": "T_U32",
    "uLowLimited": "T_U32",
    "sTradingPhraseCode": "char",
    "nPreIOPV": "T_I32",
    "nIOPV": "T_I32",

}

StockMarketDataL1 = t_SH_StockMarketDataL1

t_SH_StockStepTrade = {
    "nTradeIndex": "T_I32",
    "nTradeChannel": "T_I32",
    "nTradeTime": "T_I32",
    "nTradePrice": "T_I32",
    "iTradeQty": "T_I64",
    "iTradeMoney": "T_I64",
    "iTradeBuyNo": "T_I64",
    "iTradeSellNo": "T_I64",
    "cTradeBSflag": "char",
    "sRes": "char",

}

t_OrderQueueHead = {
    "nItem": "T_I32",
}

Stock_OrderQueue_Head = t_OrderQueueHead
t_OrderQueueItem = {
    "nTime": "T_I32",
    "nSide": "T_I32",
    "nPrice": "T_I32",
    "nOrders": "T_I32",
    "nABItems": "T_I32",
    "nABVolume": "T_I32",
}

Stock_OrderQueue = t_OrderQueueItem
T_OrderQueueItem = t_OrderQueueItem
t_SH_StockOrderQueue = {
    "tHead": "T_OrderQueueHead",
    "tItem": "T_OrderQueueItem",

}
StockOrderQueue = t_SH_StockOrderQueue
T_SH_StockOrderQueue = t_SH_StockOrderQueue
t_SH_StockIndex = {
    "nTime": "T_I32",
    "nOpenIndex": "T_I32",
    "nHighIndex": "T_I32",
    "nLowIndex": "T_I32",
    "nLastIndex": "T_I32",
    "iTotalVolume": "T_I64",
    "iTurnover": "T_I64",
    "nPreCloseIndex": "T_I32",
}
Stock_IndexData = t_SH_StockIndex
T_SH_StockIndex = t_SH_StockIndex
t_SH_Kline = {
    "uDay": "T_U32",
    "nTime": "T_I32",
    "nPreClose": "T_I32",
    "nValOpen": "T_I32",
    "nValHigh": "T_I32",
    "nValLow": "T_I32",
    "nValClose": "T_I32",
    "i64Volume": "T_I64",
    "i64ValTotal": "T_I64",
    "i64TotalVol": "T_I64",
    "i64TotalTurnOver": "T_I64",
    "nTurover": "T_I32",
    "nValIncrease": "T_I32",
}
T_Kline = t_SH_Kline
T_SH_Kline = t_SH_Kline
t_CPXX = {
    "szStkCode": "char",
    "szISIN": "char",
    "uUpdateTime": "T_U32",
    "szStkNameZN": "char",
    "szStkNameEn": "char",
    "szUnderlyingCode": "char",
    "szMktClass": "char",
    "szStkClass": "char",
    "szStkSubClass": "char",
    "szCurrency": "char",
    "i64FaceValue": "T_I64",
    "i64MatchQty": "T_I64",
    "szLastDate": "char",
    "uListingData": "T_U32",
    "uProductSETId": "T_U32",
    "i64BuyNumUnit": "T_I64",
    "i64SellNumUnit": "T_I64",
    "i64DecalaredLowestNum": "T_I64",
    "i64DecalaredHightestNum": "T_I64",
    "i64PreClosePrice": "T_I64",
    "i64PriceLevel": "T_I64",
    "cPriceLimitsType": "char",
    "i64UpLimitsPrice": "T_I64",
    "i64LowerLimitPrice": "T_I64",
    "i64DividendRatio": "T_I64",
    "i64DividendAmount": "T_I64",
    "cFinaSubjectFlag": "char",
    "cMarginSubjectFlag": "char",
    "szProdStatusFlag": "char",
    "i64MPDecalaredLowestNum": "T_I64",
    "i64MPDecalaredHightestNum": "T_I64",
    "szStkNameZNLong": "char",
    "szNote": "char",
}
T_CPXX = t_CPXX
T_SH_BaseInfo = t_CPXX
t_SH_ETFExtends = {
    "nTime": "T_I32",
    "nIOPV": "T_I32",
    "nEtfBuyNum": "T_I32",
    "i64EtfBuyAmount": "T_I64",
    "i64EtfBuyMoney": "T_I64",
    "nEtfSellNum": "T_I32",
    "i64EtfSellAmount": "T_I64",
    "i64EtfSellMoney": "T_I64",
    "nWithDrawBuyNum": "T_I32",
    "i64WithDrawBuyAmount": "T_I64",
    "i64WithDrawBuyMoney": "T_I64",
    "nWithDrawSellNum": "T_I32",
    "i64WithDrawSellAmount": "T_I64",
    "i64WithDrawSellMoney": "T_I64",
}

T_ETFEXTENDS = t_SH_ETFExtends
T_SH_ETFEXTENDS = t_SH_ETFExtends

t_SZ_StockMarketDataL2 = {
    "nTime": "T_I32",
    "nStatus": "T_I32",
    "uPreClose": "T_U32",
    "uOpen": "T_U32",
    "uHigh": "T_U32",
    "uLow": "T_U32",
    "uMatch": "T_U32",
    "uAskPrice": "T_U32",
    "uAskVol": "T_U32",
    "uBidPrice": "T_U32",
    "uBidVol": "T_U32",
    "uNumTrades": "T_U32",
    "iVolume": "T_I64",
    "iTurnover": "T_I64",
    "iTotalBidVol": "T_I64",
    "iTotalAskVol": "T_I64",
    "uWeightedAvgBidPrice": "T_U32",
    "uWeightedAvgAskPrice": "T_U32",
    "nIOPV": "T_I32",
    "nYieldToMaturity": "T_I32",
    "uHighLimited": "T_U32",
    "uLowLimited": "T_U32",
    "sPrefix": "char",
    "nSyl1": "T_I32",
    "nSyl2": "T_I32",
    "nSD2": "T_I32",
    "sTradingPhraseCode": "char",
    "nPreIOPV": "T_I32",
}


t_SZ_StockMarketDataL1 = {
    "nTime": "T_I32",
    "nStatus": "T_I32",
    "uPreClose": "T_U32",
    "uOpen": "T_U32",
    "uHigh": "T_U32",
    "uLow": "T_U32",
    "uMatch": "T_U32",
    "uAskPrice": "T_U32",
    "uAskVol": "T_U32",
    "uBidPrice": "T_U32",
    "uBidVol": "T_U32",
    "uNumTrades": "T_U32",
    "iVolume": "T_I64",
    "iTurnover": "T_I64",
    "uHighLimited": "T_U32",
    "uLowLimited": "T_U32",
    "sTradingPhraseCode": "char",
    "nPreIOPV": "T_I32",
    "nIOPV": "T_I32",
}

t_SZ_StepTrade = {
    "usChannelNo": "T_U16",
    "i64ApplSeqNum": "T_I64",
    "sMDStreamID": "char",
    "i64BidApplSeqNum": "T_I64",
    "i64OfferApplSeqNum": "T_I64",
    "sSecurityID": "char",
    "sSecurityIDSource": "char",
    "i64LastPx": "T_I64",
    "i64LastQty": "T_I64",
    "cExecType": "char",
    "i64TransactTime": "T_I64",
    "sExtendFields": "char",
}
T_SZ_STEPTRADE = t_SZ_StepTrade


t_SZ_300191ExtendFields = {
}

t_SZ_300591ExtendFields = {
}

t_SZ_300791ExtendFields = {
}

t_SZ_StepOrder = {
    "usChannelNo": "T_U16",
    "i64ApplSeqNum": "T_I64",
    "sMDStreamID": "char",
    "sSecurityID": "char",
    "sSecurityIDSource": "char",
    "i64Price": "T_I64",
    "i64OrderQty": "T_I64",
    "cSide": "char",
    "i64TransactTime": "T_I64",
    "sExtendFields": "char",
}
T_SZ_STEPORDER = t_SZ_StepOrder

t_SZ_300192ExtendFields = {
    "cOrdType": "char",
}

t_SZ_300592ExtendFields = {
    "sConfirmID": "char",
    "sContactor": "char",
    "sContactInfo": "char",

}

t_SZ_300792ExtendFields = {
    "usExpirationDays": "T_U16",
    "ucExpirationType": "T_U8",
}


t_OrderQueueHead = {
    "nItem": "T_I32",
}

t_OrderQueueItem = {
    "nTime": "T_I32",
    "nSide": "T_I32",
    "nPrice": "T_I32",
    "nOrders": "T_I32",
    "nABItems": "T_I32",
    "nABVolume": "T_I32",
}


t_SZ_StockOrderQueue = {
    "tHead": "T_OrderQueueHead",
    "tItem": "T_OrderQueueItem",
}

t_SZ_StockIndex = {
    "nTime": "T_I32",
    "nOpenIndex": "T_I32",
    "nHighIndex": "T_I32",
    "nLowIndex": "T_I32",
    "nLastIndex": "T_I32",
    "iTotalVolume": "T_I64",
    "iTurnover": "T_I64",
    "nPreCloseIndex": "T_I32",
}

t_SZ_Kline = {
    "uDay": "T_U32",
    "nTime": "T_I32",
    "nPreClose": "T_I32",
    "nValOpen": "T_I32",
    "nValHigh": "T_I32",
    "nValLow": "T_I32",
    "nValClose": "T_I32",
    "i64Volume": "T_I64",
    "i64ValTotal": "T_I64",
    "i64TotalVol": "T_I64",
    "i64TotalTurnOver": "T_I64",
    "nTurover": "T_I32",
    "nValIncrease": "T_I32",
}


t_SZ_StockMarketDataLF = {
    "nTime": "T_I32",
    "uPreClose": "T_U32",
    "uOpen": "T_U32",
    "uHigh": "T_U32",
    "uLow": "T_U32",
    "uMatch": "T_U32",
    "uAskPrice": "T_U32",
    "uAskVol": "T_U32",
    "uBidPrice": "T_U32",
    "uBidVol": "T_U32",
    "uNumTrades": "T_U32",
    "iVolume": "T_I64",
    "iTurnover": "T_I64",
    "iTotalBidVol": "T_I64",
    "iTotalAskVol": "T_I64",
    "uWeightedAvgBidPrice": "T_U32",
    "uWeightedAvgAskPrice": "T_U32",
    "nIOPV": "T_I32",
    "nYieldToMaturity": "T_I32",
    "uHighLimited": "T_U32",
    "uLowLimited": "T_U32",
    "sPrefix": "char",
    "nSyl1": "T_I32",
    "nSyl2": "T_I32",
    "nSD2": "T_I32",
    "sTradingPhraseCode": "char",
    "nPreIOPV": "T_I32",
}

t_TickByTickData = {
    "cType": "char",
    "entrust": "T_SZ_STEPORDER",
    "trade": "T_SZ_STEPTRADE",
}
T_SZ_TickByTickData = t_TickByTickData

ErrMsg = {
    "channel": "int",
    "errcode": "int",
    "errstr": "char",
    "mktype": "MKtype",
    "datatype": "DATAtype",
    "usize": "unsigned int",
    "codes": "char",
}
