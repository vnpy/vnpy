DFITCSECRspInfoField = {
    "requestID": "int",
    "sessionID": "int",
    "accountID": "string",
    "errorID": "int",
    "localOrderID": "int",
    "spdOrderID": "int",
    "errorMsg": "string",
}

DFITCSECRspNoticeField = {
    "noticeMsg": "string",
}

DFITCSECReqUserLoginField = {
    "requestID": "int",
    "accountID": "string",
    "password": "string",
    "compressflag": "int",
    "authenticCode": "string",
    "appID": "string",
    "collectInterType": "int",
}

DFITCSECRspUserLoginField = {
    "requestID": "int",
    "accountID": "string",
    "sessionID": "int",
    "frontID": "int",
    "localOrderID": "int",
    "loginTime": "string",
    "tradingDay": "int",
    "result": "int",
    "rtnMsg": "string",
}

DFITCSECReqUserLogoutField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCSECRspUserLogoutField = {
    "requestID": "int",
    "accountID": "string",
    "result": "int",
    "rtnMsg": "string",
}

DFITCSECReqPasswordUpdateField = {
    "requestID": "int",
    "accountID": "string",
    "oldPassword": "string",
    "newPassword": "string",
    "passwordType": "int",
}

DFITCSECRspPasswordUpdateField = {
    "requestID": "int",
    "accountID": "string",
    "passwordType": "int",
    "result": "int",
    "rtnMsg": "string",
}

DFITCSECReqMDPasswordUpdateField = {
    "requestID": "int",
    "accountID": "string",
    "oldPassword": "string",
    "newPassword": "string",
}

DFITCSECRspMDPasswordUpdateField = {
    "requestID": "int",
    "accountID": "string",
    "result": "int",
    "rtnMsg": "string",
}

DFITCSECReqWithdrawOrderField = {
    "requestID": "int",
    "accountID": "string",
    "spdOrderID": "int",
    "localOrderID": "int",
    "sessionID": "int",
}

DFITCSECRspWithdrawOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
    "entrustTime": "string",
    "cancelMsg": "string",
}

DFITCStockReqEntrustOrderField = {
    "requestID": "int",
    "localOrderID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "entrustPrice": "double",
    "entrustDirection": "int",
    "entrustQty": "int",
    "securityID": "string",
    "orderType": "int",
    "entrustBatchID": "int",
    "eachSeatID": "string",
    "hkEntrustLimit": "int",
    "hkOrderType": "int",
}

DFITCStockRspEntrustOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
    "entrustBatchID": "int",
    "entrustMsg": "string",
}

DFITCStockReqQryEntrustOrderField = {
    "requestID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "securityID": "string",
    "entrustBatchID": "int",
    "entrustQryFlag": "int",
    "withdrawFlag": "string",
    "incQryIndex": "string",
}

DFITCStockRspQryEntrustOrderField = {
    "requestID": "int",
    "offerShareholderID": "string",
    "currency": "string",
    "turnover": "double",
    "tradePrice": "double",
    "tradeTime": "string",
    "tradeQty": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "clearFunds": "double",
    "entrustType": "int",
    "spdOrderID": "int",
    "entrustPrice": "double",
    "entrustDirection": "int",
    "entrustQty": "int",
    "securityID": "string",
    "securityType": "string",
    "securityName": "string",
    "entrustTime": "string",
    "declareTime": "string",
    "declareResult": "int",
    "withdrawFlag": "string",
    "freezeFunds": "double",
    "accountID": "string",
    "noteMsg": "string",
    "withdrawQty": "int",
    "declareOrderID": "string",
    "orderType": "int",
    "entrustBatchID": "int",
    "freezeFundsSerialID": "int",
    "freezeStockSerialID": "int",
    "declareDate": "int",
    "declareSerialID": "int",
    "entrustDate": "int",
    "incQryIndex": "string",
    "ipAddr": "string",
    "macAddr": "string",
}

DFITCStockReqQryRealTimeTradeField = {
    "requestID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "securityID": "string",
    "entrustBatchID": "int",
    "entrustDirection": "int",
    "spdOrderID": "int",
    "queryFlag": "int",
}

DFITCStockRspQryRealTimeTradeField = {
    "requestID": "int",
    "accountID": "string",
    "spdOrderID": "int",
    "declareOrderID": "string",
    "exchangeID": "string",
    "shareholderID": "string",
    "entrustDirection": "int",
    "withdrawFlag": "string",
    "securityID": "string",
    "securityName": "string",
    "entrustQty": "int",
    "entrustPrice": "double",
    "withdrawQty": "int",
    "tradeQty": "int",
    "turnover": "double",
    "tradePrice": "double",
    "tradeTime": "string",
    "currency": "string",
    "clearFunds": "double",
    "entrustBatchID": "int",
    "orderType": "int",
}

DFITCStockReqQrySerialTradeField = {
    "requestID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "securityID": "string",
    "entrustBatchID": "int",
    "tradeQryFlag": "int",
    "incQryIndex": "string",
}

DFITCStockRspQrySerialTradeField = {
    "requestID": "int",
    "accountID": "string",
    "currency": "string",
    "tradeID": "string",
    "turnover": "double",
    "tradePrice": "double",
    "tradeQty": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "clearFunds": "double",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "securityID": "string",
    "securityType": "string",
    "securityName": "string",
    "withdrawFlag": "string",
    "commission": "double",
    "rtnSerialID": "int",
    "interestQuote": "double",
    "declareOrderID": "string",
    "incQryIndex": "string",
    "interest": "double",
    "tradeTime": "string",
}

DFITCStockReqQryPositionField = {
    "requestID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "securityID": "string",
    "posiQryFlag": "int",
}

DFITCStockRspQryPositionField = {
    "requestID": "int",
    "accountID": "string",
    "currency": "string",
    "sellTurnover": "double",
    "sellTradeQty": "int",
    "sellEntrustQty": "int",
    "buyTurnover": "double",
    "buyTradeQty": "int",
    "buyEntrustQty": "int",
    "nonCirculateQty": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "openDate": "int",
    "ableSellQty": "int",
    "securityID": "string",
    "securityType": "string",
    "securityName": "string",
    "securityQty": "int",
    "position": "int",
    "unSettleQty": "int",
    "changeDate": "int",
    "ablePurchaseQty": "int",
    "ableRedemptionQty": "int",
    "freezeQty": "int",
    "offsetSQty": "int",
    "offsetBQty": "int",
    "purchaseTradeQty": "int",
    "redemptionTradeQty": "int",
    "tradeUnit": "int",
    "totalSellQty": "int",
    "totalBuyQty": "int",
    "rationedSharesQty": "int",
    "purchaseQty": "int",
    "dilutedFloatProfitLoss": "double",
    "dilutedBreakevenPrice": "double",
    "dilutedCost": "double",
    "avgPositionPrice": "double",
    "floatProfitLoss": "double",
    "dividend": "double",
    "totalFloatProfitLoss": "double",
    "sellAmount": "double",
    "buyAmount": "double",
    "buyAvgPrice": "double",
    "rationedSharesAmount": "double",
    "latestMarket": "double",
    "breakevenPrice": "double",
    "latestPrice": "double",
    "nonCirculateMarket": "double",
    "interestQuote": "double",
    "preClosePrice": "double",
}

DFITCStockReqQryCapitalAccountField = {
    "requestID": "int",
    "accountID": "string",
    "FundsQryFlag": "int",
}

DFITCStockRspQryCapitalAccountField = {
    "requestID": "int",
    "currency": "string",
    "availableFunds": "double",
    "t2AvailableFunds": "double",
    "anticipatedInterest": "double",
    "accountBalance": "double",
    "accountStatus": "int",
    "accountID": "string",
    "freezeFunds": "double",
    "t2FreezeFunds": "double",
    "branchID": "string",
    "totalFunds": "double",
    "totalMarket": "double",
}

DFITCStockReqQryAccountField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCStockRspQryAccountField = {
    "requestID": "int",
    "tel": "string",
    "accountID": "string",
    "accountName": "string",
    "accountIdentityID": "string",
    "accountIdentityType": "int",
    "branchID": "string",
    "mobile": "string",
    "entrustType": "int",
    "accountStatus": "int",
    "pwdSynFlag": "int",
}

DFITCStockReqQryShareholderField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
}

DFITCStockRspQryShareholderField = {
    "requestID": "int",
    "account": "string",
    "shareholderID": "string",
    "shareholderSpecProp": "int",
    "tradePermissions": "int",
    "exchangeID": "string",
    "shareholderStatus": "int",
    "mainAccountFlag": "int",
    "shareholderCtlProp": "int",
    "branchID": "string",
    "shareholderType": "int",
}

DFITCStockReqTransferFundsField = {
    "requestID": "int",
    "accountID": "string",
    "currency": "string",
    "summaryMsg": "string",
    "operateFunds": "double",
    "fundsTransFlag": "int",
}

DFITCStockRspTransferFundsField = {
    "requestID": "int",
    "accountID": "string",
    "serialID": "int",
    "accountBanlance": "double",
    "availableFunds": "double",
    "t2AvailableFunds": "double",
    "fundsTransFlag": "int",
}

DFITCStockReqEntrustBatchOrderField = {
    "requestID": "int",
    "localOrderID": "int",
    "accountID": "string",
    "entrustCount": "int",
    "entrustDetail": "string",
    "entrustBatchID": "int",
}

DFITCStockRspEntrustBatchOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "orderRangeID": "string",
    "entrustBatchID": "int",
    "sucEntrustCount": "int",
}

DFITCStockReqWithdrawBatchOrderField = {
    "requestID": "int",
    "accountID": "string",
    "orderRangeID": "string",
    "entrustBatchID": "int",
}

DFITCStockRspWithdrawBatchOrderField = {
    "requestID": "int",
    "accountID": "string",
    "result": "int",
}

DFITCStockReqCalcAbleEntrustQtyField = {
    "requestID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "entrustPrice": "double",
    "entrustDirection": "int",
    "securityID": "string",
    "orderType": "int",
}

DFITCStockRspCalcAbleEntrustQtyField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "ableEntrustQty": "int",
}

DFITCStockReqCalcAblePurchaseETFQtyField = {
    "requestID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "securityID": "string",
}

DFITCStockRspCalcAblePurchaseETFQtyField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "ablePurchaseETFQty": "int",
}

DFITCStockReqQryFreezeFundsDetailField = {
    "requestID": "int",
    "currency": "string",
    "fundsFreezeType": "int",
    "accountID": "string",
    "serialID": "int",
}

DFITCStockRspQryFreezeFundsDetailField = {
    "requestID": "int",
    "accountID": "string",
    "currency": "string",
    "fundsFreezeType": "int",
    "accountName": "string",
    "summaryMsg": "string",
    "serialID": "int",
    "operatorFunds": "double",
    "operatorTime": "string",
    "branchID": "string",
    "operatorDate": "int",
}

DFITCStockReqQryFreezeStockDetailField = {
    "requestID": "int",
    "stockFreezeType": "int",
    "exchangeID": "string",
    "accountID": "string",
    "securityID": "string",
    "serialID": "int",
}

DFITCStockRspQryFreezeStockDetailField = {
    "requestID": "int",
    "accountID": "string",
    "stockFreezeType": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "accountName": "string",
    "securityID": "string",
    "securityType": "string",
    "securityName": "string",
    "summaryMsg": "string",
    "serialID": "int",
    "operatorTime": "string",
    "branchID": "string",
    "operatorDate": "int",
    "operatorQty": "int",
}

DFITCStockReqQryTransferFundsDetailField = {
    "requestID": "int",
    "currency": "string",
    "fundsFreezeType": "int",
    "accountID": "string",
    "serialID": "int",
}

DFITCStockRspQryTransferFundsDetailField = {
    "requestID": "int",
    "accountID": "string",
    "currency": "string",
    "fundsFreezeType": "int",
    "accountName": "string",
    "summaryMsg": "string",
    "serialID": "int",
    "operatorFunds": "double",
    "operatorTime": "string",
    "branchID": "string",
    "operatorDate": "int",
}

DFITCStockReqQryTransferStockDetailField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "stockFreezeType": "int",
    "incQryIndex": "string",
    "serialID": "int",
}

DFITCStockRspQryTransferStockDetailField = {
    "requestID": "int",
    "accountID": "string",
    "accountName": "string",
    "branchID": "string",
    "operatorDate": "int",
    "exchangeID": "string",
    "stockFreezeType": "int",
    "securityID": "string",
    "serialID": "int",
    "shareholderID": "string",
    "summaryMsg": "string",
    "operatorTime": "string",
    "operatorQty": "int",
}

DFITCStockReqQryStockField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
}

DFITCStockRspQryStockField = {
    "requestID": "int",
    "accountID": "string",
    "stopFlag": "int",
    "latestPrice": "double",
    "preClosePrice": "double",
    "openPrice": "double",
    "tradeQty": "int",
    "turnover": "double",
    "priceHigher": "double",
    "priceLower": "double",
    "bidPrice1": "double",
    "bidQty1": "int",
    "askPrice1": "double",
    "askQty1": "int",
    "bidPrice2": "double",
    "bidQty2": "int",
    "askPrice2": "double",
    "askQty2": "int",
    "bidPrice3": "double",
    "bidQty3": "int",
    "askPrice3": "double",
    "askQty3": "int",
    "bidPrice4": "double",
    "bidQty4": "int",
    "askPrice4": "double",
    "askQty4": "int",
    "bidPrice5": "double",
    "bidQty5": "int",
    "askPrice5": "double",
    "askQty5": "int",
    "exchangeID": "string",
    "securityID": "string",
    "interestQuote": "double",
    "securityFaceValue": "double",
    "bidTradeFlag": "int",
    "tradeUnit": "int",
    "businessLimit": "int",
    "securityType": "string",
    "securityName": "string",
    "upperLimitPrice": "double",
    "lowerLimitPrice": "double",
    "currency": "string",
    "orderLimits": "string",
}

DFITCStockReqQryTradeTimeField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCStockRspQryTradeTimeField = {
    "requestID": "int",
    "accountID": "string",
    "sysTradingDay": "int",
    "sysTime": "string",
}

DFITCStockEntrustOrderRtnField = {
    "localOrderID": "int",
    "accountID": "string",
    "sessionID": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "currency": "string",
    "securityID": "string",
    "securityType": "string",
    "withdrawQty": "int",
    "withdrawFlag": "string",
    "freezeFunds": "double",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "declareResult": "int",
    "noteMsg": "string",
    "entrustQty": "int",
    "orderConfirmFlag": "int",
    "entrustTime": "string",
    "entrustPrice": "double",
    "orderType": "int",
}

DFITCStockTradeRtnField = {
    "localOrderID": "int",
    "accountID": "string",
    "sessionID": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "currency": "string",
    "securityID": "string",
    "securityType": "string",
    "withdrawFlag": "string",
    "tradeID": "string",
    "tradeTime": "string",
    "withdrawQty": "int",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "clearFunds": "double",
    "totalTradeQty": "int",
    "totalTurnover": "double",
    "tradeQty": "int",
    "tradePrice": "double",
    "turnover": "double",
    "entrustQty": "int",
    "declareResult": "int",
    "noteMsg": "string",
}

DFITCStockWithdrawOrderRtnField = {
    "localOrderID": "int",
    "accountID": "string",
    "sessionID": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "currency": "string",
    "securityID": "string",
    "securityType": "string",
    "withdrawQty": "int",
    "tradeQty": "int",
    "withdrawFlag": "string",
    "freezeFunds": "double",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "entrustQty": "int",
    "declareResult": "int",
    "noteMsg": "string",
}

DFITCSOPReqEntrustOrderField = {
    "requestID": "int",
    "localOrderID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "subAccountID": "string",
    "entrustQty": "int",
    "entrustPrice": "double",
    "entrustDirection": "int",
    "openCloseFlag": "int",
    "coveredFlag": "int",
    "orderType": "int",
    "orderExpiryDate": "int",
    "orderCategory": "int",
    "serialID": "int",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPRspEntrustOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
    "entrustTime": "string",
    "freezeFunds": "double",
}

DFITCSOPEntrustOrderRtnField = {
    "localOrderID": "int",
    "accountID": "string",
    "sessionID": "int",
    "branchID": "string",
    "shareholderID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "withdrawFlag": "string",
    "currency": "string",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "openCloseFlag": "int",
    "entrustPrice": "double",
    "entrustQty": "int",
    "entrustTime": "string",
    "coveredFlag": "int",
    "orderType": "int",
    "orderExpiryDate": "int",
    "orderCategory": "int",
    "declareResult": "int",
    "noteMsg": "string",
    "devID": "string",
    "devDecInfo": "string",
    "groupType": "int",
    "groupCode": "string",
    "securityOptionID1": "string",
    "securityOptionID2": "string",
    "securityOptionID3": "string",
    "securityOptionID4": "string",
}

DFITCSOPTradeRtnField = {
    "localOrderID": "int",
    "accountID": "string",
    "sessionID": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "withdrawFlag": "string",
    "currency": "string",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "openCloseFlag": "int",
    "coveredFlag": "int",
    "orderCategory": "int",
    "tradePrice": "double",
    "tradeQty": "int",
    "tradeID": "string",
    "rtnSerialID": "int",
    "declareOrderID": "string",
    "declareResult": "int",
    "noteMsg": "string",
    "devID": "string",
    "devDecInfo": "string",
    "tradeTime": "string",
    "groupCode": "string",
    "groupType": "int",
    "securityOptionID1": "string",
    "securityOptionID2": "string",
    "securityOptionID3": "string",
    "securityOptionID4": "string",
}

DFITCSOPWithdrawOrderRtnField = {
    "localOrderID": "int",
    "accountID": "string",
    "sessionID": "int",
    "shareholderID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "withdrawFlag": "string",
    "currency": "string",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "openCloseFlag": "int",
    "withdrawQty": "int",
    "tradeQty": "int",
    "declareResult": "int",
    "noteMsg": "string",
    "wdUnFreezeFunds": "double",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPReqQuoteEntrustOrderField = {
    "requestID": "int",
    "localOrderID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "entrustDirection": "int",
    "bidQty": "int",
    "bidPrice": "double",
    "bidOpenCloseFlag": "int",
    "bidCoveredFlag": "int",
    "askQty": "int",
    "askPrice": "double",
    "askOpenCloseFlag": "int",
    "askCoveredFlag": "int",
    "orderType": "int",
    "orderExpiryDate": "int",
    "orderCategory": "int",
    "quoteID": "int",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPRspQuoteEntrustOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
    "entrustTime": "string",
    "freezeFunds": "double",
}

DFITCSOPReqLockOUnLockStockField = {
    "requestID": "int",
    "localOrderID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "subAccountID": "string",
    "securityID": "string",
    "entrustQty": "int",
    "openCloseFlag": "int",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPRspLockOUnLockStockField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
    "entrustTime": "string",
    "freezeFunds": "double",
}

DFITCSOPReqQrySerialTradeField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "spdOrderID": "int",
    "incQryIndex": "string",
    "entrustDirection": "int",
    "entrustBatchID": "int",
    "tradeQryFlag": "int",
    "currency": "string",
    "rowIndex": "int",
    "rowCount": "int",
}

DFITCSOPRspQrySerialTradeField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "rtnSerialID": "int",
    "securityID": "string",
    "entrustDirection": "int",
    "withdrawFlag": "string",
    "declareOrderID": "string",
    "currency": "string",
    "tradeID": "string",
    "tradeTime": "string",
    "tradeQty": "int",
    "openCloseFlag": "int",
    "coveredFlag": "int",
    "spdOrderID": "int",
    "turnover": "double",
    "tradePrice": "double",
    "clearFunds": "double",
    "rotationTime": "string",
    "incQryIndex": "string",
    "shareholderID": "string",
    "capitalID": "string",
    "devID": "string",
    "devDecInfo": "string",
    "groupType": "int",
    "groupCode": "string",
    "securityOptionID1": "string",
    "securityOptionID2": "string",
    "securityOptionID3": "string",
    "securityOptionID4": "string",
}

DFITCSOPReqQryEntrustOrderField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityOptionID": "string",
    "withdrawFlag": "string",
    "exSerialID": "int",
    "entrustDirection": "int",
    "spdOrderID": "int",
    "entrustQryFlag": "int",
    "rowIndex": "int",
    "rowCount": "int",
}

DFITCSOPRspQryEntrustOrderField = {
    "requestID": "int",
    "accountID": "string",
    "spdOrderID": "int",
    "withdrawOrderID": "string",
    "declareOrderID": "string",
    "exchangeID": "string",
    "shareholderID": "string",
    "entrustDirection": "int",
    "withdrawFlag": "string",
    "securityOptionID": "string",
    "optType": "int",
    "openCloseFlag": "int",
    "coveredFlag": "int",
    "entrustQty": "int",
    "entrustPrice": "double",
    "entrustDate": "int",
    "entrustTime": "string",
    "offerShareholderID": "string",
    "declareDate": "int",
    "declareTime": "string",
    "declareSerialID": "int",
    "declareResult": "int",
    "noteMsg": "string",
    "withdrawQty": "int",
    "tradeQty": "int",
    "turnover": "double",
    "tradePrice": "double",
    "currency": "string",
    "freezeFunds": "double",
    "clearFunds": "double",
    "entrustType": "int",
    "macAddr": "string",
    "ipAddr": "string",
    "entrustBatchID": "int",
    "orderType": "int",
    "incQryIndex": "string",
    "capitalID": "string",
    "orderExpiryDate": "int",
    "devID": "string",
    "devDecInfo": "string",
    "groupType": "int",
    "groupCode": "string",
    "securityOptionID1": "string",
    "securityOptionID2": "string",
    "securityOptionID3": "string",
    "securityOptionID4": "string",
}

DFITCSOPReqQryPositionField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityOptionID": "string",
    "rowIndex": "int",
    "rowCount": "int",
}

DFITCSOPRspQryPositionField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "subAccountID": "string",
    "securityOptionID": "string",
    "contractID": "string",
    "contractName": "string",
    "entrustDirection": "int",
    "coveredFlag": "int",
    "executeDate": "int",
    "totalQty": "int",
    "availableQty": "int",
    "latestPrice": "double",
    "optionMarket": "double",
    "freezeQty": "int",
    "executeQty": "int",
    "openEntrustQty": "int",
    "openTradeQty": "int",
    "prePosition": "int",
    "closeEntrustQty": "int",
    "closeTradeQty": "int",
    "deposit": "double",
    "openDeposit": "double",
    "closeDeposit": "double",
    "exchangeDeposit": "double",
    "exchangeOpenDeposit": "double",
    "exchangeCloseDeposit": "double",
    "openAvgPrice": "double",
    "optType": "int",
    "contractObjectType": "int",
    "contractUnit": "int",
    "currency": "string",
    "totalTradeCost": "double",
    "tradeCost": "double",
    "realizeProfitLoss": "double",
    "profitLoss": "double",
    "adjustRemind": "int",
    "expireRemind": "int",
}

DFITCSOPReqQryCollateralPositionField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
}

DFITCSOPRspQryCollateralPositionField = {
    "requestID": "int",
    "exchangeID": "string",
    "accountID": "string",
    "securityID": "string",
    "securityName": "string",
    "availableQty": "int",
}

DFITCSOPReqQryCapitalAccountField = {
    "requestID": "int",
    "accountID": "string",
    "currency": "string",
    "FundsQryFlag": "int",
}

DFITCSOPRspQryCapitalAccountField = {
    "requestID": "int",
    "accountID": "string",
    "branchID": "string",
    "currency": "string",
    "accountBanlance": "double",
    "availableFunds": "double",
    "freezeFunds": "double",
    "anticipatedInterest": "double",
    "usedDeposit": "double",
    "accountStatus": "int",
    "totalFunds": "double",
    "totalMarket": "double",
    "cashAssets": "double",
    "execGuaranteeRatio": "double",
    "buyLimits": "double",
}

DFITCSOPReqQryAccountField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCSOPRspQryAccountField = {
    "requestID": "int",
    "accountID": "string",
    "accountName": "string",
    "accountFullName": "string",
    "branchID": "string",
    "identityType": "int",
    "accountIdentityID": "string",
    "tel": "string",
    "mobile": "string",
    "accountType": "int",
    "accountProp": "int",
    "tradePermissions": "int",
    "entrustType": "int",
    "accountStatus": "int",
    "pwdSynFlag": "int",
    "accountNodeID": "int",
}

DFITCSOPReqCalcAbleEntrustQtyField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "subAccountID": "string",
    "securityOptionID": "string",
    "entrustDirection": "int",
    "openCloseFlag": "int",
    "coveredFlag": "int",
    "entrustPrice": "double",
    "checkUpLimit": "int",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPRspCalcAbleEntrustQtyField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityOptionID": "string",
    "entrustQty": "int",
}

DFITCSOPReqQryShareholderField = {
    "accountID": "string",
    "requestID": "int",
    "exchangeID": "string",
}

DFITCSOPRspQryShareholderField = {
    "requestID": "int",
    "accountID": "string",
    "branchID": "string",
    "currency": "string",
    "shareholderID": "string",
    "tradePermissions": "int",
    "shareholderSpecProp": "int",
    "shareholderCtlProp": "int",
    "shareholderStatus": "int",
    "mainAccountFlag": "int",
    "exchangeID": "string",
}

DFITCSOPReqQryAbleLockStockField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
}

DFITCSOPRspQryAbleLockStockField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "securityName": "string",
    "securityQty": "int",
    "position": "int",
    "avgPositionPrice": "double",
    "dilutedCost": "double",
    "breakevenPrice": "double",
    "dilutedBreakevenPrice": "double",
    "ableSellQty": "int",
    "latestMarket": "double",
    "latestPrice": "double",
    "floatProfitLoss": "double",
    "dilutedFloatProfitLoss": "double",
    "tradeUnit": "int",
    "openBuyQty": "int",
    "openSellQty": "int",
    "buyUnSettleQty": "int",
    "sellUnSettleQty": "int",
    "openEntrustSellQty": "int",
    "ableLockQty": "int",
}

DFITCSOPReqQryExecAssiInfoField = {
    "requestID": "int",
    "accountID": "string",
    "securityOptionID": "string",
    "tradeDate": "int",
}

DFITCSOPRspQryExecAssiInfoField = {
    "requestID": "int",
    "accountID": "string",
    "tradeDate": "int",
    "branchID": "string",
    "shareholderID": "string",
    "subAccountID": "string",
    "exchangeID": "string",
    "currency": "string",
    "optType": "int",
    "contractObjectType": "int",
    "coveredFlag": "int",
    "securityOptionID": "string",
    "entrustDirection": "int",
    "securityID": "string",
    "seatID": "string",
    "execPrice": "double",
    "execQty": "int",
    "tradeQty": "int",
    "clearFunds": "double",
    "settleFunds": "double",
    "commission": "double",
    "stampTax": "double",
    "transferFee": "double",
    "fee3": "double",
    "fee4": "double",
    "summaryMsg": "string",
}

DFITCSOPReqQryContactField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityOptionID": "string",
    "securityID": "string",
    "contractObjectType": "int",
    "optType": "int",
    "rowIndex": "string",
    "rowCount": "int",
}

DFITCSOPRspQryContactField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityOptionID": "string",
    "contractID": "string",
    "contractName": "string",
    "securityID": "string",
    "contractObjectType": "int",
    "execType": "int",
    "deliType": "int",
    "optType": "int",
    "contactUnit": "int",
    "latestPrice": "double",
    "beginTradingDay": "int",
    "endTradingDay": "int",
    "execDate": "int",
    "endDate": "int",
    "positionUpLimit": "int",
    "priceUpLimit": "double",
    "priceDownLimit": "double",
    "priceHigher": "double",
    "priceLower": "double",
    "entrustUpLimit": "int",
    "entrustDownLimit": "int",
    "entrustUpLimitMarketPri": "int",
    "entrustDownLimitMarketPri": "int",
    "openLimit": "int",
    "stockTradeFlag": "int",
    "depositUnit": "double",
    "depositRatioC": "double",
    "depositRatioE": "double",
    "preClosePrice": "double",
    "closePrice": "double",
    "preSettlePrice": "double",
    "openPrice": "double",
    "tradeQty": "int",
    "turnover": "double",
    "settlePrice": "double",
    "endCashSettlePrice": "double",
    "handQty": "int",
    "unClosePositionQty": "int",
    "approachExpireFlag": "int",
    "tempAdjustFlag": "int",
    "stockListFlag": "string",
    "execPrice": "double",
    "bidPrice1": "double",
    "bidQty1": "int",
    "bidPrice2": "double",
    "bidQty2": "int",
    "bidPrice3": "double",
    "bidQty3": "int",
    "bidPrice4": "double",
    "bidQty4": "int",
    "bidPrice5": "double",
    "bidQty5": "int",
    "askPrice1": "double",
    "askQty1": "int",
    "askPrice2": "double",
    "askQty2": "int",
    "askPrice3": "double",
    "askQty3": "int",
    "askPrice4": "double",
    "askQty4": "int",
    "askPrice5": "double",
    "askQty5": "int",
    "optionIndex": "string",
    "miniPriceChange": "double",
}

DFITCSOPReqQryContractObjectField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "securityObjectType": "int",
}

DFITCSOPRspQryContractObjectField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityName": "string",
    "securityID": "string",
    "contractObjectType": "int",
    "contractObjectStatus": "int",
}

DFITCSOPReqExectueOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "exchangeID": "string",
    "securityOptionID": "string",
    "subAccountID": "string",
    "entrustQty": "int",
    "entrustDirection": "int",
    "openCloseFlag": "int",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPRspExectueOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
    "entrustTime": "string",
    "freezeFunds": "double",
}

DFITCSOPReqQryTradeTimeField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCSOPRspQryTradeTimeField = {
    "requestID": "int",
    "accountID": "string",
    "sysTradingDay": "int",
    "sysTime": "string",
}

DFITCSOPReqQryExchangeInfoField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
}

DFITCSOPRspQryExchangeInfoField = {
    "requestID": "int",
    "exchangeID": "string",
    "exchangeName": "string",
    "callauctionBegining": "string",
    "callauctionEnding": "string",
    "morningOpening": "string",
    "morningClosing": "string",
    "afternoonOpening": "string",
    "afternoonClosing": "string",
    "execOpening": "string",
    "execClosing": "string",
    "nightTradeFlag": "int",
    "nightOpening": "string",
    "nightClosing": "string",
    "stockTradeStatus": "int",
    "currency": "string",
    "tradingDayFlag": "int",
}

DFITCSOPReqQryCommissionField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "refType": "int",
    "contractObjectType": "int",
    "securityID": "string",
    "openCloseFlag": "int",
    "level": "int",
    "entrustDirection": "int",
}

DFITCSOPRspQryCommissionField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "refType": "int",
    "contractObjectType": "int",
    "securityID": "string",
    "openCloseFlag": "int",
    "entrustDirection": "int",
    "level": "int",
    "costRatio1": "double",
    "unitCost1": "double",
    "costUpLimit1": "double",
    "costDonwLimit1": "double",
    "costRatio2": "double",
    "unitCost2": "double",
    "costUpLimit2": "double",
    "costDonwLimit2": "double",
    "costRatio3": "double",
    "unitCost3": "double",
    "costRatio4": "double",
    "unitCost4": "double",
}

DFITCSOPReqQryDepositField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "refType": "int",
    "securityObjectType": "int",
    "securityID": "string",
    "level": "int",
}

DFITCSOPRspQryDepositField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "refType": "int",
    "securityObjectType": "int",
    "securityID": "string",
    "depositRateC": "double",
    "depositRateE": "double",
    "depositUnit": "double",
    "calcType": "int",
    "level": "int",
}

DFITCFASLReqAbleFinInfoField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCFASLRspAbleFinInfoField = {
    "requestID": "int",
    "accountID": "string",
    "accountBanlance": "double",
    "ableFinFunds": "double",
    "turnover": "double",
    "entrustFreezeFunds": "double",
}

DFITCReqQuotQryField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
}

DFITCRspQuotQryField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "securityName": "string",
}

DFITCFASLReqAbleSloInfoField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCFASLRspAbleSloInfoField = {
    "requestID": "int",
    "accountID": "string",
    "securityID": "string",
    "exchangeID": "string",
    "ableSloQty": "int",
    "securityName": "string",
    "entrustQty": "int",
    "tradeQty": "int",
    "status": "int",
    "sloDepositRatio": "double",
}

DFITCFASLReqTransferCollateralField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "entrustDirection": "int",
    "exchangeID": "string",
    "securityID": "string",
    "transferQty": "int",
}

DFITCFASLRspTransferCollateralField = {
    "requestID": "int",
    "accountID": "string",
    "spdOrderID": "int",
    "localOrderID": "int",
}

DFITCFASLReqDirectRepaymentField = {
    "requestID": "int",
    "accountID": "string",
    "contractNO": "string",
    "repayFunds": "double",
}

DFITCFASLRspDirectRepaymentField = {
    "requestID": "int",
    "accountID": "string",
    "realRepayFunds": "double",
}

DFITCFASLReqRepayStockTransferField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "exchangeID": "string",
    "repayQty": "int",
    "securityID": "string",
    "contractNO": "string",
}

DFITCFASLRspRepayStockTransferField = {
    "requestID": "int",
    "accountID": "string",
    "spdOrderID": "int",
    "localOrderID": "int",
}

DFITCFASLReqEntrustCrdtOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "entrustDirection": "int",
    "exchangeID": "string",
    "contractNO": "string",
    "securityID": "string",
    "orderType": "int",
    "entrustQty": "int",
    "entrustPrice": "double",
}

DFITCFASLRspEntrustCrdtOrderField = {
    "requestID": "int",
    "accountID": "string",
    "spdOrderID": "int",
    "localOrderID": "int",
}

DFITCFASLReqWithdrawOrderField = {
    "requestID": "int",
    "accountID": "string",
    "spdOrderID": "int",
    "localOrderID": "int",
    "sessionID": "int",
}

DFITCFASLRspWithdrawOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
}

DFITCFASLReqEntrustOrderField = {
    "requestID": "int",
    "localOrderID": "int",
    "accountID": "string",
    "entrustDirection": "int",
    "exchangeID": "string",
    "securityID": "string",
    "orderType": "int",
    "entrustQty": "int",
    "entrustPrice": "double",
    "positionSource": "int",
}

DFITCFASLRspEntrustOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
}

DFITCFASLReqCalcAbleEntrustCrdtQtyField = {
    "requestID": "int",
    "accountID": "string",
    "entrustDirection": "int",
    "exchangeID": "string",
    "contractNO": "string",
    "securityID": "string",
    "orderType": "int",
    "entrustPrice": "double",
    "positionSource": "int",
}

DFITCFASLRspCalcAbleEntrustCrdtQtyField = {
    "requestID": "int",
    "accountID": "string",
    "totalRepayQty": "int",
    "entrustQty": "int",
}

DFITCFASLReqQryCrdtFundsField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCFASLRspQryCrdtFundsField = {
    "requestID": "int",
    "accountID": "string",
    "availableDeposit": "double",
    "maintGuaranteeRatio": "double",
    "antiMaintGuaranteeRatio": "double",
    "accountBanlance": "double",
    "availableFunds": "double",
    "clearFunds": "double",
    "stockMarket": "double",
    "guaranteeStockSubMarket": "double",
    "guaranteeStockMarket": "double",
    "tradeFinLiabilities": "double",
    "tradeSloLiabilities": "double",
    "orderFinLiabilities": "double",
    "orderSloLiabilities": "double",
    "sloOrderRepay": "double",
    "fundsBalance": "double",
    "closeFunds": "double",
    "activeCloseFunds": "double",
    "ableWithdrawalAssetsStand": "double",
    "withdrawalFunds": "double",
    "totalAssets": "double",
    "unTransferStockMarket": "double",
    "totalLiabilities": "double",
    "netAssets": "double",
    "sellRepayFunds": "double",
    "anticipatedInterest": "double",
    "finProfitLoss": "double",
    "sloProfitLoss": "double",
    "sloFunds": "double",
    "finCost": "double",
    "sloCost": "double",
    "finCurMarket": "double",
    "finUsedDeposit": "double",
    "sloUsedDeposit": "double",
    "finAntiInterest": "double",
    "sloAntiInterest": "double",
    "shGuaranteeStockMarket": "double",
    "szGuaranteeStockMarket": "double",
    "finFloatProfit": "double",
    "finFloatLoss": "double",
    "sloFloatProfit": "double",
    "sloFloatLoss": "double",
    "finRatio": "double",
    "sloRatio": "double",
    "contractEndDate": "int",
    "finUsedLimits": "double",
    "sloUsedLimits": "double",
    "finCreditLimits": "double",
    "sloCreditLimits": "double",
    "ableBuyCollateralFunds": "double",
    "ableRepayFunds": "double",
    "sloAvailableFunds": "double",
    "cashAssets": "double",
    "totalStockMarket": "double",
    "finContractFunds": "double",
    "contractObjectMarket": "double",
    "otherCharges": "double",
    "sloCurMarket": "double",
}

DFITCFASLReqQryCrdtContractField = {
    "requestID": "int",
    "accountID": "string",
    "openBeginDate": "int",
    "openEndDate": "int",
    "crdtConQryFlag": "int",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "exchangeID": "string",
    "contractNO": "string",
    "securityID": "string",
    "conSerialID": "int",
}

DFITCFASLRspQryCrdtContractField = {
    "requestID": "int",
    "accountID": "string",
    "conSerialNO": "int",
    "contractNO": "string",
    "operatorDate": "int",
    "endDate": "int",
    "spdOrderID": "int",
    "entrustDirection": "int",
    "exchangeID": "string",
    "securityID": "string",
    "securityName": "string",
    "currency": "string",
    "finQty": "int",
    "finFunds": "double",
    "sloQty": "int",
    "sloFunds": "double",
    "finEntrustQty": "int",
    "finEntrustFunds": "double",
    "sloEntrustQty": "int",
    "sloEntrustFunds": "double",
    "finTradeQty": "int",
    "finTradeFunds": "double",
    "sloTradeQty": "int",
    "sloTradeFunds": "double",
    "debtPrincipal": "double",
    "repayFunds": "double",
    "debtQty": "int",
    "repayQty": "int",
    "sellStockRepayFunds": "double",
    "buyStockForRepayEntrustQty": "int",
    "buyStockForRepayTradeQty": "int",
    "finCost": "double",
    "sloCost": "double",
    "totalInterest": "double",
    "repaidInterest": "double",
    "crdtConStatus": "int",
    "leftInterest": "double",
    "sloLeftFunds": "double",
    "buyStockFreezeFunds": "double",
    "buyStockClearFunds": "double",
    "sloLeftAvaiFunds": "double",
    "debtQtyEntrustMarket": "double",
    "debtQtyTradeMarket": "double",
    "debtFundsMarket": "double",
    "finProfitLoss": "double",
    "sloProfitLoss": "double",
    "entrustQty": "int",
    "conOpenQty": "int",
    "conOpenFunds": "double",
    "conOpenCost": "double",
    "conInitQty": "int",
    "conInitFunds": "double",
    "conInitCost": "double",
    "unRepayConFunds": "double",
    "unRepayConQty": "int",
    "unRepayConCost": "double",
    "positionNO": "int",
}

DFITCFASLReqQryCrdtConChangeInfoField = {
    "requestID": "int",
    "accountID": "string",
    "withdrawFlag": "string",
    "entrustDirection": "int",
    "exchangeID": "string",
    "securityID": "string",
    "conSerialNO": "int",
}

DFITCFASLRspQryCrdtConChangeInfoField = {
    "requestID": "int",
    "accountID": "string",
    "serialNO": "int",
    "conChangeNO": "string",
    "withdrawFlag": "string",
    "securityID": "string",
    "entrustDirection": "int",
    "operatorFunds": "double",
    "operatorTime": "string",
    "operatorQty": "int",
    "operatorDate": "int",
    "clearFlag": "int",
    "commission": "double",
    "operatorFunds2": "double",
    "postFunds": "double",
    "postQty": "int",
    "exchangeID": "string",
    "operatorCost": "double",
    "postCost": "double",
    "operatorInterest": "double",
    "postInterest": "double",
    "changeNote": "string",
    "shareholderID": "string",
}

DFITCFASLReqQryTradeTimeField = {
    "requestID": "int",
    "accountID": "string",
    "flag": "int",
}

DFITCFASLRspQryTradeTimeField = {
    "requestID": "int",
    "accountID": "string",
    "sysTradingDay": "int",
    "sysTime": "string",
    "sysWeek": "int",
    "sysMillisecond": "int",
}

DFITCFASLReqQryTransferredContractField = {
    "requestID": "int",
    "accountID": "string",
    "securityID": "string",
    "exchangeID": "string",
}

DFITCFASLRspQryTransferredContractField = {
    "requestID": "int",
    "accountID": "string",
    "capitalID": "string",
    "securityID": "string",
    "exchangeID": "string",
    "ableSellQty": "int",
}

DFITCFASLReqDesirableFundsOutField = {
    "requestID": "int",
    "accountID": "string",
    "currency": "string",
    "operateFunds": "double",
    "summaryMsg": "string",
}

DFITCFASLRspDesirableFundsOutField = {
    "requestID": "int",
    "accountID": "string",
    "serialID": "int",
    "accountBanlance": "double",
}

DFITCFASLReqQryGuaranteedContractField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCFASLRspQryGuaranteedContractField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "securityName": "string",
    "exchangRate": "double",
    "status": "int",
    "accountType": "int",
}

DFITCFASLReqQryUnderlyingContractField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCFASLRspQryUnderlyingContractField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "securityID": "string",
    "securityName": "string",
    "financeDepositRatio": "double",
    "securityDepositRatio": "double",
    "status": "int",
    "accountType": "int",
}

DFITCSECSpecificInstrumentField = {
    "requestID": "int",
    "securityID": "string",
    "exchangeID": "string",
}

DFITCSOPSpecificDataField = {
    "contractID": "string",
    "execPrice": "double",
    "preSettlePrice": "double",
    "settlePrice": "double",
    "positionQty": "int",
    "auctionPrice": "double",
    "latestEnquiryTime": "string",
}

DFITCStockSpecificDataField = {
    "peRadio1": "double",
    "peRadio2": "double",
}

DFITCStaticDataField = {
    "securityID": "string",
    "securityName": "string",
    "tradingDay": "int",
    "exchangeID": "string",
    "preClosePrice": "double",
    "openPrice": "double",
    "upperLimitPrice": "double",
    "lowerLimitPrice": "double",
}

DFITCSharedDataField = {
    "latestPrice": "double",
    "turnover": "double",
    "highestPrice": "double",
    "lowestPrice": "double",
    "tradeQty": "int",
    "updateTime": "string",
    "bidPrice1": "double",
    "bidQty1": "int",
    "askPrice1": "double",
    "askQty1": "int",
    "bidPrice2": "double",
    "bidQty2": "int",
    "askPrice2": "double",
    "askQty2": "int",
    "bidPrice3": "double",
    "bidQty3": "int",
    "askPrice3": "double",
    "askQty3": "int",
    "bidPrice4": "double",
    "bidQty4": "int",
    "askPrice4": "double",
    "askQty4": "int",
    "bidPrice5": "double",
    "bidQty5": "int",
    "askPrice5": "double",
    "askQty5": "int",
    "tradingPhaseCode": "string",
}

DFITCSOPDepthMarketDataField = {
    "specificDataField": "dict",
    "staticDataField": "dict",
    "sharedDataField": "dict",
}

DFITCStockDepthMarketDataField = {
    "specificDataField": "dict",
    "staticDataField": "dict",
    "sharedDataField": "dict",
}

DFITCStockReqQryStockStaticField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
}

DFITCStockRspQryStockStaticField = {
    "requestID": "int",
    "accountID": "string",
    "stopFlag": "int",
    "preClosePrice": "double",
    "openPrice": "double",
    "exchangeID": "string",
    "securityID": "string",
    "interestQuote": "double",
    "securityFaceValue": "double",
    "bidTradeFlag": "int",
    "tradeUnit": "int",
    "businessLimit": "int",
    "securityType": "string",
    "securityName": "string",
    "upperLimitPrice": "double",
    "lowerLimitPrice": "double",
    "currency": "string",
    "orderLimits": "string",
}

DFITCSOPReqGroupSplitField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "exchangeID": "string",
    "securityOptionID": "string",
    "subAccountID": "string",
    "openCloseFlag": "int",
    "groupType": "int",
    "groupCode": "string",
    "securityOptionID1": "string",
    "securityOptionID2": "string",
    "securityOptionID3": "string",
    "securityOptionID4": "string",
    "entrustQty": "int",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPReqGroupExectueOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "exchangeID": "string",
    "securityOptionID1": "string",
    "securityOptionID2": "string",
    "subAccountID": "string",
    "entrustQty": "int",
    "entrustDirection": "int",
    "openCloseFlag": "int",
    "orderCategory": "int",
    "devID": "string",
    "devDecInfo": "string",
}

DFITCSOPRspGroupExectueOrderField = {
    "requestID": "int",
    "accountID": "string",
    "localOrderID": "int",
    "spdOrderID": "int",
    "entrustTime": "string",
    "freezeFunds": "double",
}

DFITCSOPReqQryGroupPositionField = {
    "requestID": "int",
    "accountID": "string",
}

DFITCSOPRspQryGroupPositionField = {
    "requestID": "int",
    "accountID": "string",
    "exchangeID": "string",
    "shareholderID": "string",
    "subAccountID": "string",
    "currency": "string",
    "capitalID": "string",
    "groupType": "int",
    "groupCode": "string",
    "groupQty": "int",
    "enableSplitQty": "int",
    "splitEntrustQty": "int",
    "splitTradeQty": "int",
    "groupDeposit": "double",
    "securityOptionID1": "string",
    "securityOptionID2": "string",
    "securityOptionID3": "string",
    "securityOptionID4": "string",
}

DFITCTerminalInfoField = {
    "systemInfo": "string",
    "secretkeyVer": "string",
    "appID": "string",
    "exceptionFlag": "int",
    "clientPublicIP": "string",
    "clientPublicPort": "int",
    "clientLoginTime": "string",
    "systemInfo_integrity": "string",
}

