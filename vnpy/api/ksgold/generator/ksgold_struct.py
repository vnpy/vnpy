KS_TE_RESUME_TYPE = {
    "KS_TERT_RESTART": "int",
    "KS_TERT_RESUME": "int",
    "KS_TERT_QUICK": "int",
}

CThostFtdcReqUserLoginField = {
    "AccountID": "string",
    "LoginType": "int",
    "Password": "string",
    "LoginIp": "string",
    "MacAddress": "string",
    "UserProductionInfo": "string",
    "ProtocolInfo": "string",
}

CThostFtdcRspUserLoginField = {
    "TradeDate": "string",
    "SessionID": "int",
    "ClientID": "string",
    "clientName": "string",
    "TradeCode": "string",
    "SeatNo": "string",
    "lastLoginIp": "string",
    "lastLoginDate": "string",
    "lastLoginTime": "string",
    "AccountID": "string",
    "LoginType": "int",
    "Password": "string",
    "MacAddress": "string",
    "LoginIp": "string",
    "UserProductionInfo": "string",
    "ProtocolInfo": "string",
    "SystemName": "string",
    "FrontID": "int",
    "MaxOrderRef": "string",
    "SgeTime": "string",
}

CThostFtdcUserLogoutField = {
    "LoginIp": "string",
    "MacAddress": "string",
    "ClientID": "string",
}

CThostFtdcQryClientSessionField = {
    "ClientID": "string",
}

CThostFtdcRspClientSessionField = {
    "ClientID": "string",
    "SessionID": "int",
    "IdDiffCode": "string",
    "CurLoginIp": "string",
    "CurMacAddress": "string",
    "Status": "string",
    "LoginTime": "string",
    "LoginDate": "string",
    "LogoutTime": "string",
    "LogoutDate": "string",
    "FailNumber": "int",
}

CThostFtdcRspVarietyCodeField = {
    "ExchangeID": "string",
    "VarietyShortName": "string",
    "VarietyFullName": "string",
    "VarietyCode": "string",
    "VarietyType": "string",
    "WeightUnit": "string",
    "Status": "char",
    "MinTakeVolumn": "double",
    "TakeUnit": "double",
    "Weight": "double",
    "ProductID": "string",
}

CThostFtdcInstrumentField = {
    "ExchangeID": "string",
    "InstID": "string",
    "LowerLimit": "double",
    "MarketID": "string",
    "MaxHand": "int",
    "MinHand": "int",
    "Name": "string",
    "OpenFlag": "char",
    "Tick": "double",
    "TradeState": "char",
    "Unit": "int",
    "UpperLimit": "double",
    "VarietyID": "string",
    "VarietyType": "char",
    "MarketType": "char",
    "ProductID": "string",
}

CThostFtdcQryTradingAccountField = {
    "ClientID": "string",
}

CThostFtdcQryHisCapitalField = {
    "ClientID": "string",
    "StartDate": "string",
    "EndDate": "string",
}

CThostFtdcQryCostMarginFeeField = {
    "ClientID": "string",
    "InstID": "string",
}

CThostFtdcRspHisCapitalField = {
    "TradeDate": "string",
    "AvailCap": "double",
    "Todayprofit": "double",
    "PosiMargin": "double",
    "PickUpMargin": "double",
    "StorageMargin": "double",
    "TradeFee": "double",
    "TodayInOut": "double",
    "EtfTransferFee": "double",
    "EtfTransferFeeFrzn": "double",
    "EtfCashBalance": "double",
    "EtfCashBalanceFrzn": "double",
}

CThostFtdcRspCostMarginFeeField = {
    "ClientID": "string",
    "InstID": "string",
    "BuyOpenHandFee": "double",
    "BuyOffsetHandFee": "double",
    "SellOpenHandFee": "double",
    "SellOffsetHandFee": "double",
    "BuyMarginFee": "double",
    "SellMarginFee": "double",
    "SeatBuyMarginFee": "double",
    "SeatSellMarginFee": "double",
}

CThostFtdcTradingAccountField = {
    "ClientID": "string",
    "AvailCap": "double",
    "Available": "double",
    "PosiMargin": "double",
    "BuyPosiMargin": "double",
    "SellPosiMargin": "double",
    "StorageMargin": "double",
    "TotalFee": "double",
    "TotalFrozen": "double",
    "OrderFrozen": "double",
    "SpotSellFrozen": "double",
    "TodayIn": "double",
    "TodayOut": "double",
    "LastFrozen": "double",
    "TotalFrozenFee": "double",
    "PickUpMargin": "double",
    "MiddleMargin": "double",
}

CThostFtdcRspInfoField = {
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcDepthMarketDataField = {
    "InstID": "string",
    "Name": "string",
    "MarketName": "string",
    "PreSettle": "double",
    "PreClose": "double",
    "Open": "double",
    "High": "double",
    "Low": "double",
    "Last": "double",
    "Close": "double",
    "Bid1": "double",
    "BidLot1": "int",
    "Ask1": "double",
    "AskLot1": "int",
    "Bid2": "double",
    "BidLot2": "int",
    "Ask2": "double",
    "AskLot2": "int",
    "Bid3": "double",
    "BidLot3": "int",
    "Ask3": "double",
    "AskLot3": "int",
    "Bid4": "double",
    "BidLot4": "int",
    "Ask4": "double",
    "AskLot4": "int",
    "Bid5": "double",
    "BidLot5": "int",
    "Ask5": "double",
    "AskLot5": "int",
    "Bid6": "double",
    "BidLot6": "int",
    "Ask6": "double",
    "AskLot6": "int",
    "Bid7": "double",
    "BidLot7": "int",
    "Ask7": "double",
    "AskLot7": "int",
    "Bid8": "double",
    "BidLot8": "int",
    "Ask8": "double",
    "AskLot8": "int",
    "Bid9": "double",
    "BidLot9": "int",
    "Ask9": "double",
    "AskLot9": "int",
    "Bid10": "double",
    "BidLot10": "int",
    "Ask10": "double",
    "AskLot10": "int",
    "Volume": "int",
    "OpenInt": "int",
    "UpDown": "double",
    "Turnover": "double",
    "Settle": "double",
    "Average": "double",
    "QuoteDate": "string",
    "QuoteTime": "string",
    "weight": "double",
    "highLimit": "double",
    "lowLimit": "double",
    "UpDownRate": "double",
}

CThostFtdcInputOrderField = {
    "SeatID": "string",
    "ClientID": "string",
    "TradeCode": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffsetFlag": "char",
    "Amount": "int",
    "Price": "double",
    "MarketID": "string",
    "OrderRef": "string",
    "SessionID": "int",
    "HedgeFlag": "char",
    "CmdType": "string",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcConditionOrderField = {
    "ExchangeID": "string",
    "SeatID": "string",
    "ClientID": "string",
    "TradeCode": "string",
    "MarketID": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffsetFlag": "char",
    "Amount": "int",
    "OrderType": "char",
    "MiddleFlag": "char",
    "PriceFlag": "char",
    "Price": "double",
    "TrigPrice": "double",
    "ValidDay": "int",
    "VolumnCheck": "int",
    "OrderRef": "string",
    "SessionID": "int",
    "CmdType": "string",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcRspConditionOrderField = {
    "SeatID": "string",
    "ClientID": "string",
    "TradeCode": "string",
    "ExchangeID": "string",
    "ConditionOrderNo": "string",
    "EntrustDate": "string",
    "TradeDate": "string",
    "EntrustTime": "string",
    "Status": "char",
    "MarketID": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffsetFlag": "char",
    "Amount": "int",
    "OrderType": "char",
    "MiddleFlag": "char",
    "PriceFlag": "char",
    "Price": "double",
    "TrigPrice": "double",
    "ValidDay": "int",
    "VolumnCheck": "int",
    "OrderRef": "string",
    "SessionID": "int",
    "CmdType": "string",
}

CThostFtdcRspInputOrderField = {
    "LocalOrderNo": "string",
    "Status": "char",
    "SeatID": "string",
    "ClientID": "string",
    "TradeCode": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffsetFlag": "char",
    "Amount": "int",
    "Price": "double",
    "MarketID": "string",
    "OrderRef": "string",
    "SessionID": "int",
    "RequestID": "int",
    "HedgeFlag": "char",
    "CmdType": "string",
}

CThostFtdcConditionActionOrderField = {
    "ClientID": "string",
    "ConditionOrderNo": "string",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcRspConditionActionOrderField = {
    "ClientID": "string",
    "ConditionOrderNo": "string",
}

CThostFtdcConditionOrderQryField = {
    "ClientID": "string",
    "ConditionOrderNo": "string",
    "Status": "char",
    "InstID": "string",
    "StartDate": "string",
    "EndDate": "string",
    "OrderRef": "string",
    "SessionID": "int",
    "CmdType": "string",
}

CThostFtdcRspConditionOrderQryField = {
    "ClientID": "string",
    "StartDate": "string",
    "EndDate": "string",
    "ConditionOrderNo": "string",
    "LocalOrderNo": "string",
    "OrderType": "char",
    "EntrustTypeName": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffSetFlag": "char",
    "Status": "char",
    "Amount": "int",
    "Price": "double",
    "TriggerPrice": "double",
    "EntrustTime": "string",
    "TriggerTime": "string",
    "ReasonDesc": "string",
    "EntrustDate": "string",
    "ExpireDate": "string",
    "TriggerDate": "string",
    "OrderRef": "string",
    "SessionID": "int",
    "CmdType": "string",
}

CThostFtdcConditionOrderMatchField = {
    "ClientID": "string",
    "InstID": "string",
    "ConditionOrderNo": "string",
    "LocalOrderNo": "string",
}

CThostFtdcRspConditionOrderMatchField = {
    "ClientID": "string",
    "MatchNo": "string",
    "ConditionOrderNo": "string",
    "LocalOrderNo": "string",
    "EntrustType": "char",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffSetFlag": "char",
    "Amount": "int",
    "Price": "double",
    "MatchVolumn": "int",
    "MatchPrice": "double",
    "MatchTime": "string",
}

CThostFtdcOrderRtnField = {
    "orderNo": "string",
    "localOrderNo": "string",
    "status": "char",
    "cancelQty": "int",
}

CThostFtdcInputOrderActionField = {
    "ClientID": "string",
    "LocalOrderNo": "string",
    "MarketID": "string",
    "OrderRef": "string",
    "SessionID": "int",
    "RequestID": "int",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcRspInputOrderActionField = {
    "ClientID": "string",
    "localOrderNo": "string",
    "Status": "char",
    "marketID": "string",
    "OrderRef": "string",
    "SessionID": "int",
    "RequestID": "int",
}

CThostFtdcOrderActionField = {
    "localOrderNo": "string",
    "orderFlag": "char",
    "marketID": "string",
    "traderID": "string",
    "OrderRef": "string",
    "SessionID": "int",
    "tradeWay": "char",
}

CThostFtdcTradeField = {
    "ClientID": "string",
    "OrderNo": "string",
    "MatchNo": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffSetFlag": "char",
    "Price": "double",
    "Volume": "int",
    "Amount": "double",
    "Order_flag": "char",
    "MatchDate": "string",
    "MatchTime": "string",
    "LocalOrderNo": "string",
    "MarketID": "string",
    "Trade_fee": "double",
    "Forceoffset_flag": "char",
    "Forcebatchnum": "int",
    "TradeWay": "char",
    "HedgeFlag": "char",
    "SessionID": "int",
    "OrderRef": "string",
}

CThostFtdcQryInstrumentField = {
    "ClientID": "string",
    "ContractID": "string",
    "ProductID": "string",
}

CThostFtdcQryVarietyCodeField = {
    "ClientID": "string",
    "VarietyID": "string",
    "ProductID": "string",
}

CThostFtdcQryTradeField = {
    "ClientID": "string",
    "MarketID": "string",
    "InstID": "string",
    "LocalOrderNo": "string",
}

CThostFtdcQryOrderField = {
    "ClientID": "string",
    "MarketID": "string",
    "LocalOrderNo": "string",
    "InstID": "string",
    "HedgeFlag": "char",
    "CmdType": "string",
    "SessionID": "int",
    "OrderRef": "string",
}

CThostFtdcOrderField = {
    "ClientID": "string",
    "OrderNo": "string",
    "LocalOrderNo": "string",
    "MarketID": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "OffsetFlag": "char",
    "Amount": "int",
    "Price": "double",
    "MatchQty": "int",
    "Status": "char",
    "EntrustTime": "string",
    "Forceoffset_flag": "char",
    "CancelQty": "int",
    "CancelTime": "string",
    "TradeWay": "char",
    "HedgeFlag": "char",
    "SessionID": "int",
    "OrderRef": "string",
    "CmdType": "string",
    "RequestID": "int",
}

CThostFtdcQryInvestorPositionField = {
    "ClientID": "string",
    "MarketID": "string",
    "InstID": "string",
}

CThostFtdcQryInvestorPositionDetailField = {
    "ClientID": "string",
    "QueryData": "string",
}

CThostFtdcInvestorPositionField = {
    "ClientID": "string",
    "InstID": "string",
    "MarketID": "string",
    "LongPosi": "int",
    "LongPosiAvgPrice": "double",
    "ShortPosi": "int",
    "ShortPosiAvgPrice": "double",
    "LongOpenAvgPrice": "double",
    "ShortOpenAvgPrice": "double",
    "LongPosiFrozen": "int",
    "ShortPosiFrozen": "int",
    "LongPosiVol": "int",
    "ShortPosiVol": "int",
    "TodayLong": "int",
    "TodayShort": "int",
    "TodayOffsetShort": "int",
    "TodayOffsetLong": "int",
    "LastLong": "int",
    "LastShort": "int",
}

CThostFtdcInvestorPositionDetailField = {
    "ClientID": "string",
    "ClientShortName": "string",
    "Data": "string",
    "InstID": "string",
    "BuyOrSell": "char",
    "Volumn": "int",
    "Settle": "double",
    "OpenFlagData": "string",
    "MatchNo": "string",
}

CThostFtdcQryStorageField = {
    "VarietyID": "string",
    "ClientID": "string",
}

CThostFtdcSubScriptionField = {
    "ClientID": "string",
    "SeatNo": "string",
    "EtfCode": "string",
    "InstrumentID1": "string",
    "weight1": "double",
    "InstrumentID2": "string",
    "weight2": "double",
    "InstrumentID3": "string",
    "weight3": "double",
    "InstrumentID4": "string",
    "weight4": "double",
    "InstrumentID5": "string",
    "weight5": "double",
    "Totalweight": "double",
    "SessionID": "int",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcApplyForPurchaseField = {
    "ClientID": "string",
    "SeatNo": "string",
    "EtfCode": "string",
    "InstrumentID1": "string",
    "weight1": "double",
    "InstrumentID2": "string",
    "weight2": "double",
    "InstrumentID3": "string",
    "weight3": "double",
    "InstrumentID4": "string",
    "weight4": "double",
    "InstrumentID5": "string",
    "weight5": "double",
    "Totalweight": "double",
    "SessionID": "int",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcRedeemField = {
    "ClientID": "string",
    "SeatNo": "string",
    "EtfCode": "string",
    "SessionID": "int",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcETFBingingField = {
    "ClientID": "string",
    "StockTradeCode": "string",
    "EtfCode": "string",
    "EtfManagedUnit": "char",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcETFUnBingingField = {
    "ClientID": "string",
    "StockTradeCode": "string",
    "EtfCode": "string",
    "LoginIp": "string",
    "MacAddress": "string",
}

CThostFtdcETFBindingStatusField = {
    "ClientID": "string",
    "StockTradeCode": "string",
    "EtfCode": "string",
    "BindingStatus": "string",
    "BindingDate": "string",
    "BindingLocalOrderNo": "string",
    "BindingEtfrevsn": "string",
    "UnBindingDate": "string",
    "UnBindingLocalOrderNo": "string",
    "UnBindingEtfrevsn": "string",
}

CThostFtdcQryETFTradeDetailField = {
    "ClientID": "string",
}

CThostFtdcQryETFPcfDetailField = {
    "StartDate": "string",
    "EndDate": "string",
    "EtfCode": "string",
}

CThostFtdcETFPcfDetailField = {
    "TradeDate": "string",
    "EtfCode": "string",
    "InstrumentID1": "string",
    "TMoneydiff1": "double",
    "TPreMoneydiff1": "double",
    "InstrumentID2": "string",
    "TMoneydiff2": "double",
    "TPreMoneydiff2": "double",
    "InstrumentID3": "string",
    "TMoneydiff3": "double",
    "TPreMoneydiff3": "double",
    "InstrumentID4": "string",
    "TMoneydiff4": "double",
    "TPreMoneydiff4": "double",
    "InstrumentID5": "string",
    "TMoneydiff5": "double",
    "TPreMoneydiff5": "double",
    "minTradeWeight": "double",
    "TodayPurchaseMaxLimit": "double",
    "TodayRedeemMaxLimit": "double",
    "TodayAllow": "char",
    "PreETFWeight": "double",
}

CThostFtdcETFTradeDetailField = {
    "ClientID": "string",
    "OrderNo": "string",
    "LocalOrderNo": "string",
    "RequestDate": "string",
    "RequestTime": "string",
    "EtfCode": "string",
    "InstrumentID1": "string",
    "weight1": "double",
    "InstrumentID2": "string",
    "weight2": "double",
    "InstrumentID3": "string",
    "weight3": "double",
    "InstrumentID4": "string",
    "weight4": "double",
    "InstrumentID5": "string",
    "weight5": "double",
    "Totalweight": "double",
    "fundunit": "double",
    "confirmDate": "string",
    "tradestatus": "string",
    "ErrorMsg": "string",
    "RequestID": "int",
}

CThostFtdcStorageField = {
    "ClientID": "string",
    "VarietyID": "string",
    "totalStorage": "double",
    "availableStorage": "double",
    "frozenStorage": "double",
    "pendStorage": "double",
    "todayBuy": "double",
    "todaySell": "double",
    "todayDeposit": "double",
    "todayDraw": "double",
    "todayBorrow": "double",
    "todayLend": "double",
    "impawnStorage": "double",
    "lawFrozen": "double",
    "bankFrozen": "double",
    "customType": "char",
    "storageCost": "double",
    "impawnFrozen": "double",
    "transFrozen": "double",
}

CThostFtdcMarketStatusField = {
    "MktStatus": "string",
    "marketID": "string",
    "ExchCode": "string",
}

CThostFtdcInstrumentStatusField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "InstrumentStatus": "char",
}

CThostFtdcSpecificInstrumentField = {
    "InstrumentID": "string",
}

CThostFtdcQryQuotationField = {
    "marketID": "string",
    "InstrumentID": "string",
}

CThostFtdcModifyPasswordField = {
    "OldPassword": "string",
    "NewPassword": "string",
}

CThostFtdcModifyPasswordRsqField = {
    "ClientID": "string",
}

CThostFtdcBOCMoneyIOField = {
    "TransFerType": "string",
    "TransFerAmount": "double",
    "TradePassword": "string",
    "ClientID": "string",
}

CThostFtdcBOCMoneyIORspField = {
    "ClientID": "string",
}
