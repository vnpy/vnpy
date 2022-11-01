CStockFtdcRspInfoField = {
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CStockFtdcOptionsInsertReqField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OwnerType": "int",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "PositionEffect": "char",
    "OrdType": "char",
    "TimeInForce": "char",
    "CoveredOrUncovered": "char",
    "PartyID": "string",
}

CStockFtdcOptionsInsertRspField = {
    "OrderID": "string",
    "ExecType": "char",
    "OrdStatus": "char",
    "SecurityID": "string",
    "ClOrdID": "int",
    "TransactTimeOnly": "string",
    "DiscretionPrice": "double",
    "LeavesQty": "int",
}

CStockFtdcOptionsCancelReqField = {
    "ClOrdID": "int",
    "OrigClOrdID": "int",
    "OrderID": "string",
}

CStockFtdcOptionsCancelRspField = {
    "OrderID": "string",
    "ExecType": "char",
    "OrdStatus": "char",
    "SecurityID": "string",
    "ClOrdID": "int",
    "OrigClOrdID": "int",
    "TransactTimeOnly": "string",
    "DiscretionPrice": "double",
    "LeavesQty": "int",
}

CStockFtdcQuoteInsertReqField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OwnerType": "int",
    "PartyID": "string",
    "QuoteReqID": "string",
    "BidPx": "double",
    "AskPx": "double",
    "BidSize": "int",
    "AskSize": "int",
    "BidPositionEffect": "char",
    "AskPositionEffect": "char",
}

CStockFtdcQuoteInsertRspField = {
    "OrderID": "string",
    "ExecType": "char",
    "OrdStatus": "char",
    "ClOrdID": "int",
    "SecurityID": "string",
    "OwnerType": "int",
    "PartyID": "string",
    "QuoteReqID": "string",
    "BidPx": "double",
    "AskPx": "double",
    "BidSize": "int",
    "AskSize": "int",
    "BidPositionEffect": "char",
    "AskPositionEffect": "char",
}

CStockFtdcQuoteCancelReqField = {
    "ClOrdID": "int",
    "OrigClOrdID": "int",
    "OrderID": "string",
}

CStockFtdcQuoteCancelRspField = {
    "OrderID": "string",
    "ExecType": "char",
    "OrdStatus": "char",
    "SecurityID": "string",
    "ClOrdID": "int",
    "OrigClOrdID": "int",
}

CStockFtdcExerciseReqField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OwnerType": "int",
    "OrderQty": "int",
    "PartyID": "string",
}

CStockFtdcExerciseRspField = {
    "OrderID": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
    "OwnerType": "int",
    "OrderQty": "int",
    "PartyID": "string",
}

CStockFtdcExerciseCancelReqField = {
    "OrigClOrdID": "int",
    "OrderID": "string",
}

CStockFtdcExerciseCancelRspField = {
    "OrigClOrdID": "int",
}

CStockFtdcForQuoteReqField = {
    "SecurityID": "string",
    "OwnerType": "int",
    "PartyID": "string",
    "ClOrdID": "int",
    "QuoteReqID": "string",
}

CStockFtdcForQuoteRspField = {
    "SecurityID": "string",
    "OwnerType": "int",
    "PartyID": "string",
    "ClOrdID": "int",
    "QuoteReqID": "string",
}

CStockFtdcExerciseRtnField = {
    "ClOrdID": "int",
    "OrderID": "string",
    "SecurityID": "string",
    "OwnerType": "int",
    "OrderQty": "int",
    "PartyID": "string",
    "TransactTimeOnly": "string",
}

CStockFtdcOptionsOrderField = {
    "OrderID": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
    "TradeQty": "int",
    "CancelQty": "int",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "DiscretionPrice": "double",
    "PositionEffect": "char",
    "CoveredOrUncovered": "char",
    "TransactTimeOnly": "string",
    "OwnerType": "int",
    "OrdStatus": "char",
    "OrdType": "char",
    "TimeInForce": "char",
    "PartyID": "string",
    "UserID": "string",
    "OrdRejReason": "int",
}

CStockFtdcOptionsTradeField = {
    "OrderID": "string",
    "ClOrdID": "int",
    "ExecID": "string",
    "SecurityID": "string",
    "LastPx": "double",
    "LastQty": "int",
    "LeavesQty": "int",
    "Side": "char",
    "PositionEffect": "char",
    "CoveredOrUncovered": "char",
    "TransactTimeOnly": "string",
    "OrigTime": "string",
    "ExecType": "char",
    "OwnerType": "int",
    "OrdStatus": "char",
    "TotalValueTraded": "double",
    "PartyID": "string",
}

CStockFtdcWithdrawDepositRtnField = {
    "AccountID": "string",
    "PartyID": "string",
    "deposit": "double",
    "withdraw": "double",
}

CStockFtdcStockInsertReqField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OrdType": "char",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "PartyID": "string",
    "OwnerType": "int",
    "TimeInForce": "char",
}

CStockFtdcStockInsertRspField = {
    "OrderID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
    "OrdType": "char",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "PartyID": "string",
    "Qty2": "int",
}

CStockFtdcStockCancelReqField = {
    "ClOrdID": "int",
    "OrigClOrdID": "int",
    "OrderID": "string",
}

CStockFtdcStockCancelRspField = {
    "OrderID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "PartyID": "string",
    "OrigClOrdId": "int",
    "Qty2": "int",
}

CStockFtdcStockLockReqField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OrderQty": "int",
    "Locked": "char",
    "PartyID": "string",
}

CStockFtdcStockLockRspField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OrderQty": "int",
    "PartyID": "string",
}

CStockFtdcStockOrderField = {
    "OrderID": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "OrdStatus": "char",
    "Qty2": "int",
    "TradeQty": "int",
    "PartyID": "string",
    "UserID": "string",
    "OwnerType": "int",
    "TimeInForce": "char",
    "OrdRejReason": "int",
}

CStockFtdcStockTradeField = {
    "OrderID": "string",
    "TradeID": "string",
    "PartyID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "TradeTime": "string",
    "TradeVolume": "int",
    "Side": "char",
    "Cjjg": "double",
    "Cjje": "double",
    "SecurityID": "string",
    "ClOrdID": "int",
}

CStockFtdcQuoteOrderField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OrdStatus": "char",
    "PartyID": "string",
    "UserID": "string",
    "OwnerType": "int",
    "QuoteReqID": "string",
    "BidPx": "double",
    "AskPx": "double",
    "BidSize": "int",
    "AskSize": "int",
    "BidPositionEffect": "char",
    "AskPositionEffect": "char",
    "OrdRejReason": "int",
}

CStockFtdcDisseminationField = {
    "SequenceSeries": "int",
    "SequenceNo": "int",
}

CStockFtdcReqUserLoginField = {
    "TradingDay": "string",
    "UserID": "string",
    "Password": "string",
    "UserProductInfo": "string",
    "InterfaceProductInfo": "string",
    "ProtocolInfo": "string",
    "DataCenterID": "int",
}

CStockFtdcRspUserLoginField = {
    "TradingDay": "string",
    "LoginTime": "string",
    "MaxClOrdID": "int",
    "UserID": "string",
    "TradingSystemName": "string",
    "DataCenterID": "int",
    "PrivateFlowSize": "int",
    "UserFlowSize": "int",
    "ActionDay": "string",
}

CStockFtdcReqUserLogoutField = {
    "UserID": "string",
}

CStockFtdcRspUserLogoutField = {
    "UserID": "string",
}

CStockFtdcUserPasswordUpdateField = {
    "UserID": "string",
    "OldPassword": "string",
    "NewPassword": "string",
}

CStockFtdcQryStockOrderField = {
    "PartyID": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
}

CStockFtdcRspQryStockOrderField = {
    "PartyID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
    "OrdType": "char",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "Qty2": "int",
    "OrdStatus": "char",
}

CStockFtdcQryOptionsOrderField = {
    "PartyID": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
}

CStockFtdcRspQryOptionsOrderField = {
    "PartyID": "string",
    "OrderID": "string",
    "ExecType": "char",
    "OrdStatus": "char",
    "SecurityID": "string",
    "ClOrdID": "int",
    "TransactTimeOnly": "string",
    "DiscretionPrice": "double",
    "LeavesQty": "int",
    "OwnerType": "int",
    "Price": "double",
    "OrderQty": "int",
    "Side": "char",
    "PositionEffect": "char",
    "OrdType": "char",
    "TimeInForce": "char",
    "CoveredOrUncovered": "char",
    "UserID": "string",
}

CStockFtdcQryQuoteOrderField = {
    "PartyID": "string",
    "ClOrdID": "int",
    "SecurityID": "string",
}

CStockFtdcRspQryQuoteOrderField = {
    "ClOrdID": "int",
    "SecurityID": "string",
    "OrdStatus": "char",
    "PartyID": "string",
    "UserID": "string",
    "OwnerType": "int",
    "QuoteReqID": "string",
    "BidPx": "double",
    "AskPx": "double",
    "BidSize": "int",
    "AskSize": "int",
    "BidPositionEffect": "char",
    "AskPositionEffect": "char",
}

CStockFtdcQryStockTradeField = {
    "PartyID": "string",
    "SecurityID": "string",
    "TradeID": "string",
}

CStockFtdcQryOptionsTradeField = {
    "PartyID": "string",
    "SecurityID": "string",
    "ExecID": "string",
}

CStockFtdcQryPositionField = {
    "PartyID": "string",
    "SecurityID": "string",
}

CStockFtdcRspPositionField = {
    "PartyID": "string",
    "SecurityID": "string",
    "Converd": "char",
    "Side": "char",
    "YdPosition": "int",
    "Position": "int",
    "TodayPosition": "int",
    "BuyTradeVolume": "int",
    "SellTradeVolume": "int",
    "PositionCost": "double",
    "YdPositionCost": "double",
    "UseMargin": "double",
}

CStockFtdcQryPartAccountField = {
    "PartyID": "string",
}

CStockFtdcRspPartAccountField = {
    "PartyID": "string",
    "TradingDay": "string",
    "PreBalance": "double",
    "Balance": "double",
    "Available": "double",
    "CurrMargin": "double",
    "FrozenMargin": "double",
    "CombMargin": "double",
    "Premium": "double",
    "FrozenPremium": "double",
    "Commi": "double",
    "FrozenCommi": "double",
    "CloseProfit": "double",
    "PosiProfit": "double",
    "Deposit": "double",
    "Withdraw": "double",
    "BaseReserve": "double",
    "SaveDouble1": "double",
    "SaveDouble2": "double",
    "SaveDouble3": "double",
}

CStockFtdcQryStockField = {
    "SecurityID": "string",
}

CStockFtdcRspQryStockField = {
    "SecurityID": "string",
    "contractmultiplierunit": "int",
    "startdate": "string",
    "enddate": "string",
    "totallongposition": "int",
    "securityclosepx": "double",
    "settlprice": "double",
    "underlyingclosepx": "double",
    "dailypriceuplimit": "double",
    "dailypricedownlimit": "double",
    "marginunit": "double",
    "marginratioparam1": "double",
    "marginratioparam2": "double",
    "roundlot": "int",
    "lmtordminfloor": "int",
    "lmtordmaxfloor": "int",
    "mktordminfloor": "int",
    "mktordmaxfloor": "int",
    "ticksize": "double",
    "lastprice": "double",
}

CStockFtdcQryOptionsField = {
    "SecurityID": "string",
}

CStockFtdcRspQryOptionsField = {
    "SecurityID": "string",
    "underlyingsecurityid": "string",
    "optiontype": "char",
    "callorput": "char",
    "contractmultiplierunit": "int",
    "exerciseprice": "double",
    "startdate": "string",
    "enddate": "string",
    "exercisedate": "string",
    "deliverydate": "string",
    "expiredate": "string",
    "totallongposition": "int",
    "securityclosepx": "double",
    "settlprice": "double",
    "underlyingclosepx": "double",
    "dailypriceuplimit": "double",
    "dailypricedownlimit": "double",
    "marginunit": "double",
    "marginratioparam1": "double",
    "marginratioparam2": "double",
    "roundlot": "int",
    "lmtordminfloor": "int",
    "lmtordmaxfloor": "int",
    "mktordminfloor": "int",
    "mktordmaxfloor": "int",
    "ticksize": "double",
    "lastprice": "double",
}

CStockFtdcQryRateField = {
    "PartyID": "string",
    "SecurityID": "string",
}

Commi_Info = {
    "bymoney": "double",
    "byvolume": "double",
    "maxcommi": "double",
    "mincommi": "double",
}

CStockFtdcRspQryRateField = {
    "PartyID": "string",
    "SecurityID": "string",
    "Margin": "double",
}

CStockFtdcQryClientMarginField = {
    "PartyID": "string",
    "SecurityID": "string",
}

CStockFtdcRspQryClientMarginField = {
    "PartyID": "string",
    "SecurityID": "string",
    "Margin": "double",
    "MarginRatio": "double",
    "MinMarginRatio": "double",
}

CStockFtdcRspClientField = {
    "PartyID": "string",
    "Status": "char",
}

CStockFtdcQryExerciseField = {
    "PartyID": "string",
}

OmlItem = {
    "LegSecurityID": "string",
    "CoveredOrUncovered": "char",
    "LegOrderQty": "int",
}

CStockFtdcMarginCombActionField = {
    "ClOrdID": "int",
    "CombID": "string",
    "OwnerType": "int",
    "OrderQty": "int",
    "PartyID": "string",
}

CStockFtdcMarginCombActionRspField = {
    "OrderID": "string",
    "ClOrdID": "int",
    "CombID": "string",
    "OwnerType": "int",
    "OrderQty": "int",
    "PartyID": "string",
}

CStockFtdcMarginCombActionRtnField = {
    "ClOrdID": "int",
    "ExecID": "string",
    "CombID": "string",
    "TransactTimeOnly": "string",
    "OrigTime": "string",
    "PartyID": "string",
    "LastQty": "int",
    "commargin": "double",
}

CStockFtdcCombPositionField = {
    "PartyID": "string",
}

CStockFtdcCombPositionRspField = {
    "PartyID": "string",
    "PosiQty": "int",
    "commargin": "double",
}

CStockFtdcCombExerciseReqField = {
    "ClOrdID": "int",
    "OwnerType": "int",
    "OrderQty": "int",
    "PartyID": "string",
    "LegSecurityID1": "string",
    "LegOrderQty1": "int",
    "LegSecurityID2": "string",
    "LegOrderQty2": "int",
}

CStockFtdcCombExerciseRspField = {
    "OrderID": "string",
    "ClOrdID": "int",
    "OwnerType": "int",
    "OrderQty": "int",
    "PartyID": "string",
    "LegSecurityID1": "string",
    "LegOrderQty1": "int",
    "LegSecurityID2": "string",
    "LegOrderQty2": "int",
}
