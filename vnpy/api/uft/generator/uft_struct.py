CHSRspInfoField = {
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CHSReqAuthenticateField = {
    "AccountID": "string",
    "Password": "string",
    "AppID": "string",
    "AuthCode": "string",
}

CHSRspAuthenticateField = {
    "AccountID": "string",
    "AppID": "string",
    "AuthCode": "string",
}

CHSReqUserLoginField = {
    "AccountID": "string",
    "Password": "string",
    "UserApplicationType": "char",
    "UserApplicationInfo": "string",
    "MacAddress": "string",
    "IPAddress": "string",
}

CHSRspUserLoginField = {
    "BranchID": "int",
    "AccountID": "string",
    "UserName": "string",
    "TradingDay": "int",
    "PreTradingDay": "int",
    "BillConfirmFlag": "char",
    "SessionID": "int",
    "UserApplicationType": "char",
    "UserApplicationInfo": "string",
    "RiskLevel": "string",
    "LastMacAddress": "string",
    "LastIPAddress": "string",
    "LastLoginTime": "int",
    "CZCETime": "int",
    "DCETime": "int",
    "SHFETime": "int",
    "CFFEXTime": "int",
    "INETime": "int",
}

CHSReqUserPasswordUpdateField = {
    "PasswordType": "char",
    "Password": "string",
    "NewPassword": "string",
}

CHSRspUserPasswordUpdateField = {
}

CHSReqOrderInsertField = {
    "OrderRef": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeType": "char",
    "OrderPrice": "double",
    "OrderVolume": "double",
    "OrderCommand": "string",
    "MinVolume": "double",
    "SpringPrice": "double",
    "SwapOrderFlag": "char",
}

CHSRspOrderInsertField = {
    "AccountID": "string",
    "OrderSysID": "string",
    "BrokerOrderID": "string",
    "SessionID": "int",
    "OrderRef": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeType": "char",
    "OrderPrice": "double",
    "OrderVolume": "double",
    "OrderStatus": "char",
    "OrderCommand": "string",
    "InsertTime": "int",
    "MinVolume": "double",
    "SpringPrice": "double",
    "SwapOrderFlag": "char",
}

CHSReqOrderActionField = {
    "OrderSysID": "string",
    "ExchangeID": "string",
    "SessionID": "int",
    "OrderRef": "string",
    "OrderActionRef": "string",
}

CHSRspOrderActionField = {
    "AccountID": "string",
    "OrderSysID": "string",
    "ExchangeID": "string",
    "SessionID": "int",
    "OrderRef": "string",
    "OrderStatus": "char",
    "InsertTime": "int",
    "OrderActionRef": "string",
}

CHSReqExerciseOrderInsertField = {
    "ExerciseRef": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "OrderVolume": "double",
    "ExerciseType": "char",
    "HedgeType": "char",
}

CHSRspExerciseOrderInsertField = {
    "AccountID": "string",
    "SessionID": "int",
    "ExerciseOrderSysID": "string",
    "ExerciseRef": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "OrderVolume": "double",
    "ExerciseType": "char",
    "HedgeType": "char",
    "OrderStatus": "char",
    "InsertTime": "int",
}

CHSReqExerciseOrderActionField = {
    "ExchangeID": "string",
    "ExerciseOrderSysID": "string",
    "ExerciseRef": "string",
    "SessionID": "int",
    "ExecOrderActionRef": "string",
}

CHSRspExerciseOrderActionField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "ExerciseOrderSysID": "string",
    "ExerciseRef": "string",
    "SessionID": "int",
    "OrderStatus": "char",
    "ExecOrderActionRef": "string",
}

CHSReqLockInsertField = {
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "LockType": "char",
    "OrderVolume": "double",
}

CHSRspLockInsertField = {
    "AccountID": "string",
    "LockOrderSysID": "string",
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "LockType": "char",
    "OrderVolume": "double",
    "UnderlyingAccountID": "string",
    "OrderStatus": "char",
    "InsertTime": "int",
}

CHSReqForQuoteInsertField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSRspForQuoteInsertField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "OrderStatus": "char",
}

CHSReqCombActionInsertField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "CombStrategyID": "string",
    "CombPositionID": "string",
    "CombDirection": "char",
    "OrderVolume": "double",
    "HedgeType": "char",
    "Direction": "char",
}

CHSRspCombActionInsertField = {
    "AccountID": "string",
    "CombOrderSysID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "CombStrategyID": "string",
    "CombPositionID": "string",
    "CombDirection": "char",
    "OrderVolume": "double",
    "HedgeType": "char",
    "OrderStatus": "char",
    "InsertTime": "int",
    "Direction": "char",
}

CHSReqQueryMaxOrderVolumeField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "OrderCommand": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeType": "char",
    "OrderPrice": "double",
}

CHSRspQueryMaxOrderVolumeField = {
    "AccountID": "string",
    "MaxOrderVolume": "double",
    "MaxOrderVolumeUnit": "double",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "OrderCommand": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeType": "char",
    "OrderPrice": "double",
}

CHSReqQueryLockVolumeField = {
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "LockType": "char",
}

CHSRspQueryLockVolumeField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "LockType": "char",
    "AvailablePositionVolume": "double",
}

CHSReqQueryExerciseVolumeField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSRspQueryExerciseVolumeField = {
    "AccountID": "string",
    "MaxOrderVolumeUnit": "double",
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSReqQryPositionField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSRspQryPositionField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "HedgeType": "char",
    "YdPositionVolume": "double",
    "PositionVolume": "double",
    "TodayPositionVolume": "double",
    "AvailablePositionVolume": "double",
    "TodayAvailablePositionVolume": "double",
    "PositionMargin": "double",
    "Premium": "double",
    "Commission": "double",
    "OpenFrozenVolume": "double",
    "CloseFrozenVolume": "double",
    "CombVolume": "double",
    "ExerciseFrozenVolume": "double",
    "FrozenMargin": "double",
    "ExerciseFrozenMargin": "double",
    "FrozenPremium": "double",
    "FrozenCommission": "double",
    "OpenVolume": "double",
    "CloseVolume": "double",
    "OpenBalance": "double",
    "CloseBalance": "double",
    "OpenCost": "double",
    "PositionCost": "double",
    "PositionProfit": "double",
    "CloseProfit": "double",
    "OptionsMarketValue": "double",
    "UnderlyingInstrID": "string",
}

CHSReqQryTradingAccountField = {
}

CHSRspQryTradingAccountField = {
    "AccountID": "string",
    "YdBalance": "double",
    "YdPositionMargin": "double",
    "YdFundEquity": "double",
    "FundEquity": "double",
    "OptionsMarketValue": "double",
    "Equity": "double",
    "AvailableBalance": "double",
    "WithdrawBalance": "double",
    "Margin": "double",
    "FrozenMargin": "double",
    "ExerciseFrozenMargin": "double",
    "RiskDegree": "double",
    "Premium": "double",
    "FrozenPremium": "double",
    "Commission": "double",
    "FrozenCommission": "double",
    "CloseProfit": "double",
    "PositionProfit": "double",
    "CloseProfitByDate": "double",
    "PositionProfitByDate": "double",
    "Deposit": "double",
    "Withdraw": "double",
    "FundMortgage": "double",
    "WarrantMortgage": "double",
    "FrozenBalance": "double",
    "UnFrozenBalance": "double",
    "CurrencyID": "char",
}

CHSReqQryOrderField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "OrderSysID": "string",
}

CHSOrderField = {
    "AccountID": "string",
    "OrderSysID": "string",
    "BrokerOrderID": "string",
    "SessionID": "int",
    "OrderRef": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeType": "char",
    "OrderPrice": "double",
    "OrderVolume": "double",
    "OrderStatus": "char",
    "TradeVolume": "double",
    "CancelVolume": "double",
    "TradePrice": "double",
    "TradingDay": "int",
    "InsertDate": "int",
    "InsertTime": "int",
    "ReportTime": "int",
    "OrderCommand": "string",
    "MinVolume": "double",
    "SpringPrice": "double",
    "SwapOrderFlag": "char",
    "ForceCloseReason": "char",
    "ErrorMsg": "string",
    "UnderlyingInstrID": "string",
    "OrderSource": "char",
}

CHSReqQryTradeField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSTradeField = {
    "AccountID": "string",
    "TradeID": "string",
    "OrderSysID": "string",
    "BrokerOrderID": "string",
    "SessionID": "int",
    "OrderRef": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeType": "char",
    "TradeVolume": "double",
    "TradePrice": "double",
    "TradingDay": "int",
    "TradeTime": "int",
    "UnderlyingInstrID": "string",
}

CHSReqQryExerciseField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "ExerciseOrderSysID": "string",
}

CHSExerciseField = {
    "AccountID": "string",
    "ExerciseOrderSysID": "string",
    "SessionID": "int",
    "ExerciseRef": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "HedgeType": "char",
    "ExerciseType": "char",
    "OrderVolume": "double",
    "OrderStatus": "char",
    "InsertDate": "int",
    "InsertTime": "int",
    "ErrorMsg": "string",
    "UnderlyingInstrID": "string",
    "OrderSource": "char",
    "CloseFlag": "char",
    "OffsetFlag": "char",
}

CHSReqQryLockField = {
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "LockOrderSysID": "string",
}

CHSLockField = {
    "AccountID": "string",
    "LockOrderSysID": "string",
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "LockType": "char",
    "OrderVolume": "double",
    "OrderStatus": "char",
    "TradingDay": "int",
    "InsertTime": "int",
    "ErrorMsg": "string",
    "OrderSource": "char",
}

CHSReqQryCombActionField = {
    "CombOrderSysID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSCombActionField = {
    "AccountID": "string",
    "CombOrderSysID": "string",
    "CombPositionID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "CombStrategyID": "string",
    "Direction": "char",
    "CombDirection": "char",
    "HedgeType": "char",
    "OrderVolume": "double",
    "OrderStatus": "char",
    "TradingDay": "int",
    "InsertDate": "int",
    "InsertTime": "int",
    "ErrorMsg": "string",
    "OrderSource": "char",
}

CHSReqQryPositionCombineDetailField = {
}

CHSRspQryPositionCombineDetailField = {
    "AccountID": "string",
    "CombPositionID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "CombStrategyID": "string",
    "HedgeType": "char",
    "Direction": "char",
    "YdPositionVolume": "double",
    "AvailablePositionVolume": "double",
    "TotalCombVolume": "double",
    "TotalSplitVolume": "double",
    "PositionMargin": "double",
    "OpenDate": "int",
}

CHSReqQryInstrumentField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSRspQryInstrumentField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "InstrumentName": "string",
    "InstrumentEngName": "string",
    "ProductID": "string",
    "ProductType": "char",
    "MaxMarketOrderVolume": "double",
    "MinMarketOrderVolume": "double",
    "MaxLimitOrderVolume": "double",
    "MinLimitOrderVolume": "double",
    "VolumeMultiple": "double",
    "PriceTick": "double",
    "UnderlyingInstrID": "string",
    "ExercisePrice": "double",
    "OptionsType": "char",
    "TradingFlag": "char",
    "MarketDate": "int",
    "ExpireDate": "int",
    "BeginExerciseDate": "int",
    "EndExerciseDate": "int",
    "BeginDeliveryDate": "int",
    "EndDeliveryDate": "int",
    "CurrencyID": "char",
    "CombType": "char",
}

CHSReqQryCoveredShortField = {
    "ExchangeID": "string",
}

CHSRspQryCoveredShortField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "CoveredLockVolume": "double",
    "CoveredShortVolume": "double",
    "CoveredEstimateShortVolume": "double",
    "MsgContent": "string",
}

CHSReqQryExerciseAssignField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "PositionType": "char",
}

CHSRspQryExerciseAssignField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "UnderlyingInstrID": "string",
    "InstrumentID": "string",
    "PositionType": "char",
    "OptionsType": "char",
    "ExercisePrice": "double",
    "ExerciseVolume": "double",
    "DeliveryVolume": "double",
    "ExerciseFrozenBalance": "double",
    "SettlementBalance": "double",
}

CHSReqTransferField = {
    "BankID": "string",
    "TransferType": "char",
    "OccurBalance": "double",
    "FundPassword": "string",
    "BankPassword": "string",
    "CurrencyID": "char",
    "TransferOccasion": "string",
}

CHSRspTransferField = {
    "TransferSerialID": "int",
    "BankID": "string",
    "TransferType": "char",
    "OccurBalance": "double",
    "CurrencyID": "char",
    "TransferOccasion": "string",
}

CHSReqQryTransferField = {
    "BankID": "string",
    "TransferSerialID": "int",
}

CHSRspQryTransferField = {
    "TransferSerialID": "int",
    "BankID": "string",
    "BankName": "string",
    "BusinessName": "string",
    "OccurBalance": "double",
    "PostBalance": "double",
    "TransferTime": "int",
    "TransferStatus": "char",
    "TransferSource": "char",
    "Remarks": "string",
    "CurrencyID": "char",
    "OrderSourceDate": "int",
    "TradingDay": "int",
    "TransferOccasion": "string",
}

CHSReqQueryBankBalanceField = {
    "BankID": "string",
    "FundPassword": "string",
    "BankPassword": "string",
    "CurrencyID": "char",
}

CHSRspQueryBankBalanceField = {
    "TransferSerialID": "int",
}

CHSReqQueryBankAccountField = {
    "BankID": "string",
    "CurrencyID": "char",
}

CHSRspQueryBankAccountField = {
    "BankID": "string",
    "BankName": "string",
    "BankAccountID": "string",
    "CurrencyID": "char",
}

CHSReqQueryBillContentField = {
    "BeginDate": "int",
    "EndDate": "int",
}

CHSRspQueryBillContentField = {
    "BillContent": "string",
}

CHSReqBillConfirmField = {
}

CHSRspBillConfirmField = {
    "AccountID": "string",
    "BillConfirmStatus": "char",
    "ConfirmDate": "int",
    "ConfirmTime": "int",
}

CHSReqQryMarginField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
    "UnderlyingInstrID": "string",
    "HedgeType": "char",
}

CHSRspQryMarginField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "UnderlyingInstrID": "string",
    "HedgeType": "char",
    "LongMarginRatio": "double",
    "LongMargin": "double",
    "ShortMarginRatio": "double",
    "ShortMargin": "double",
}

CHSReqQryCommissionField = {
    "ExchangeID": "string",
    "ProductType": "char",
    "InstrumentID": "string",
    "UnderlyingInstrID": "string",
}

CHSRspQryCommissionField = {
    "AccountID": "string",
    "ExchangeID": "string",
    "ProductType": "char",
    "InstrumentID": "string",
    "UnderlyingInstrID": "string",
    "LongOpenCommissionRatio": "double",
    "LongOpenCommission": "double",
    "LongCloseCommissionRatio": "double",
    "LongCloseCommission": "double",
    "LongCloseTodayCommissionRatio": "double",
    "LongCloseTodayCommission": "double",
    "ShortOpenCommissionRatio": "double",
    "ShortOpenCommission": "double",
    "ShortCloseCommissionRatio": "double",
    "ShortCloseCommission": "double",
    "ShortCloseTodayCommissionRatio": "double",
    "ShortCloseTodayCommission": "double",
    "ExerciseCommissionRatio": "double",
    "ExerciseCommission": "double",
    "TradeValueRatio": "double",
    "StockValue": "double",
}

CHSReqQryExchangeRateField = {
    "FromCurrencyID": "char",
    "ToCurrencyID": "char",
}

CHSRspQryExchangeRateField = {
    "FromCurrencyID": "char",
    "ToCurrencyID": "char",
    "ExchangeRate": "double",
    "FromCurrencyUnit": "double",
}

CHSReqQryPositionDetailField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSRspQryPositionDetailField = {
    "AccountID": "string",
    "TradeID": "string",
    "OpenDate": "int",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "HedgeType": "char",
    "TradeVolume": "double",
    "PositionPrice": "double",
    "TodayCloseVolume": "double",
    "ArbitragePositionID": "string",
    "LegID": "double",
    "TradeType": "char",
    "PositionMargin": "double",
    "CombInstrumentID": "string",
}

CHSReqQrySysConfigField = {
}

CHSRspQrySysConfigField = {
    "ConfigNo": "double",
    "ConfigValue": "string",
}

CHSReqDepthMarketDataField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSReqQryDepthMarketDataField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CHSDepthMarketDataField = {
    "TradingDay": "int",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "LastPrice": "double",
    "PreSettlementPrice": "double",
    "PreClosePrice": "double",
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "TradeVolume": "double",
    "TradeBalance": "double",
    "OpenInterest": "double",
    "ClosePrice": "double",
    "SettlementPrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "PreDelta": "double",
    "CurrDelta": "double",
    "UpdateTime": "int",
    "BidPrice1": "double",
    "BidVolume1": "double",
    "AskPrice1": "double",
    "AskVolume1": "double",
    "BidPrice2": "double",
    "BidVolume2": "double",
    "AskPrice2": "double",
    "AskVolume2": "double",
    "BidPrice3": "double",
    "BidVolume3": "double",
    "AskPrice3": "double",
    "AskVolume3": "double",
    "BidPrice4": "double",
    "BidVolume4": "double",
    "AskPrice4": "double",
    "AskVolume4": "double",
    "BidPrice5": "double",
    "BidVolume5": "double",
    "AskPrice5": "double",
    "AskVolume5": "double",
    "AveragePrice": "double",
    "PreOpenInterest": "double",
    "InstrumentTradeStatus": "char",
    "OpenRestriction": "string",
}
