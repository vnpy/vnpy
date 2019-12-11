CUstpFtdcRspUserLoginField = {
    "TradingDay": "string",
    "BrokerID": "string",
    "UserID": "string",
    "LoginTime": "string",
    "ExchangeTime": "string",
    "MaxOrderLocalID": "string",
    "TradingSystemName": "string",
    "DataCenterID": "int",
    "PrivateFlowSize": "int",
    "UserFlowSize": "int",
    "ActionDay": "string",
    "FemasVersion": "string",
    "FemasLifeCycle": "int",
}

CUstpFtdcReqUserLogoutField = {
    "BrokerID": "string",
    "UserID": "string",
}

CUstpFtdcRspUserLogoutField = {
    "BrokerID": "string",
    "UserID": "string",
}

CUstpFtdcForceUserExitField = {
    "BrokerID": "string",
    "UserID": "string",
}

CUstpFtdcUserPasswordUpdateField = {
    "BrokerID": "string",
    "UserID": "string",
    "OldPassword": "string",
    "NewPassword": "string",
}

CUstpFtdcInputOrderField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "SeatNo": "int",
    "InstrumentID": "string",
    "UserOrderLocalID": "string",
    "OrderPriceType": "char",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "LimitPrice": "double",
    "Volume": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "UserCustom": "string",
    "BusinessLocalID": "int",
    "ActionDay": "string",
    "ArbiType": "char",
    "ClientID": "string",
}

CUstpFtdcOrderActionField = {
    "ExchangeID": "string",
    "OrderSysID": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "UserOrderActionLocalID": "string",
    "UserOrderLocalID": "string",
    "ActionFlag": "char",
    "LimitPrice": "double",
    "VolumeChange": "int",
    "BusinessLocalID": "int",
    "ClientID": "string",
}

CUstpFtdcMemDbField = {
    "MemTableName": "string",
}

CUstpFtdcRspInfoField = {
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CUstpFtdcQryOrderField = {
    "BrokerID": "string",
    "UserID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "OrderSysID": "string",
    "InstrumentID": "string",
    "OrderStatus": "char",
    "OrderType": "char",
    "ClientID": "string",
}

CUstpFtdcQryTradeField = {
    "BrokerID": "string",
    "UserID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "TradeID": "string",
    "InstrumentID": "string",
    "ClientID": "string",
}

CUstpFtdcQryInstrumentField = {
    "ExchangeID": "string",
    "ProductID": "string",
    "InstrumentID": "string",
}

CUstpFtdcRspInstrumentField = {
    "ExchangeID": "string",
    "ProductID": "string",
    "ProductName": "string",
    "InstrumentID": "string",
    "InstrumentName": "string",
    "DeliveryYear": "int",
    "DeliveryMonth": "int",
    "MaxLimitOrderVolume": "int",
    "MinLimitOrderVolume": "int",
    "MaxMarketOrderVolume": "int",
    "MinMarketOrderVolume": "int",
    "VolumeMultiple": "int",
    "PriceTick": "double",
    "Currency": "char",
    "LongPosLimit": "int",
    "ShortPosLimit": "int",
    "LowerLimitPrice": "double",
    "UpperLimitPrice": "double",
    "PreSettlementPrice": "double",
    "InstrumentStatus": "char",
    "CreateDate": "string",
    "OpenDate": "string",
    "ExpireDate": "string",
    "StartDelivDate": "string",
    "EndDelivDate": "string",
    "BasisPrice": "double",
    "IsTrading": "int",
    "UnderlyingInstrID": "string",
    "UnderlyingMultiple": "int",
    "PositionType": "char",
    "StrikePrice": "double",
    "OptionsType": "char",
    "CurrencyID": "string",
    "ArbiType": "char",
    "InstrumentID_1": "string",
    "Direction_1": "char",
    "Ratio_1": "double",
    "InstrumentID_2": "string",
    "Direction_2": "char",
    "Ratio_2": "double",
}

CUstpFtdcInstrumentStatusField = {
    "ExchangeID": "string",
    "ProductID": "string",
    "ProductName": "string",
    "InstrumentID": "string",
    "InstrumentName": "string",
    "DeliveryYear": "int",
    "DeliveryMonth": "int",
    "MaxLimitOrderVolume": "int",
    "MinLimitOrderVolume": "int",
    "MaxMarketOrderVolume": "int",
    "MinMarketOrderVolume": "int",
    "VolumeMultiple": "int",
    "PriceTick": "double",
    "Currency": "char",
    "LongPosLimit": "int",
    "ShortPosLimit": "int",
    "LowerLimitPrice": "double",
    "UpperLimitPrice": "double",
    "PreSettlementPrice": "double",
    "InstrumentStatus": "char",
    "CreateDate": "string",
    "OpenDate": "string",
    "ExpireDate": "string",
    "StartDelivDate": "string",
    "EndDelivDate": "string",
    "BasisPrice": "double",
    "IsTrading": "int",
    "UnderlyingInstrID": "string",
    "UnderlyingMultiple": "int",
    "PositionType": "char",
    "StrikePrice": "double",
    "OptionsType": "char",
    "CurrencyID": "string",
    "ArbiType": "char",
    "InstrumentID_1": "string",
    "Direction_1": "char",
    "Ratio_1": "double",
    "InstrumentID_2": "string",
    "Direction_2": "char",
    "Ratio_2": "double",
    "EnterDate": "string",
}

CUstpFtdcQryInvestorAccountField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
}

CUstpFtdcRspInvestorAccountField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "AccountID": "string",
    "PreBalance": "double",
    "Deposit": "double",
    "Withdraw": "double",
    "FrozenMargin": "double",
    "FrozenFee": "double",
    "FrozenPremium": "double",
    "Fee": "double",
    "CloseProfit": "double",
    "PositionProfit": "double",
    "Available": "double",
    "LongFrozenMargin": "double",
    "ShortFrozenMargin": "double",
    "LongMargin": "double",
    "ShortMargin": "double",
    "ReleaseMargin": "double",
    "DynamicRights": "double",
    "TodayInOut": "double",
    "Margin": "double",
    "Premium": "double",
    "Risk": "double",
}

CUstpFtdcQryUserInvestorField = {
    "BrokerID": "string",
    "UserID": "string",
}

CUstpFtdcRspUserInvestorField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
}

CUstpFtdcQryTradingCodeField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "ClientID": "string",
}

CUstpFtdcRspTradingCodeField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "ClientID": "string",
    "ClientRight": "char",
    "ClientHedgeFlag": "char",
    "IsActive": "char",
}

CUstpFtdcQryExchangeField = {
    "ExchangeID": "string",
}

CUstpFtdcRspExchangeField = {
    "ExchangeID": "string",
    "ExchangeName": "string",
}

CUstpFtdcQryInvestorPositionField = {
    "BrokerID": "string",
    "UserID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CUstpFtdcRspInvestorPositionField = {
    "InvestorID": "string",
    "BrokerID": "string",
    "ExchangeID": "string",
    "ClientID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "HedgeFlag": "char",
    "UsedMargin": "double",
    "Position": "int",
    "PositionCost": "double",
    "YdPosition": "int",
    "YdPositionCost": "double",
    "FrozenMargin": "double",
    "FrozenPosition": "int",
    "FrozenClosing": "int",
    "YdFrozenClosing": "int",
    "FrozenPremium": "double",
    "LastTradeID": "string",
    "LastOrderLocalID": "string",
    "SpeculationPosition": "int",
    "ArbitragePosition": "int",
    "HedgePosition": "int",
    "SpecFrozenClosing": "int",
    "HedgeFrozenClosing": "int",
    "Currency": "string",
}

CUstpFtdcQryComplianceParamField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "ClientID": "string",
}

CUstpFtdcRspComplianceParamField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "ClientID": "string",
    "DailyMaxOrder": "int",
    "DailyMaxOrderAction": "int",
    "DailyMaxErrorOrder": "int",
    "DailyMaxOrderVolume": "int",
    "DailyMaxOrderActionVolume": "int",
}

CUstpFtdcQryUserField = {
    "StartUserID": "string",
    "EndUserID": "string",
}

CUstpFtdcUserField = {
    "BrokerID": "string",
    "UserID": "string",
    "Password": "string",
    "IsActive": "char",
    "UserName": "string",
    "UserType": "char",
    "Department": "string",
    "GrantFuncSet": "char",
    "SetUserID": "string",
    "CommandDate": "string",
    "CommandTime": "string",
}

CUstpFtdcQryInvestorFeeField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "ClientID": "string",
}

CUstpFtdcInvestorFeeField = {
    "BrokerID": "string",
    "ClientID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "ProductID": "string",
    "OpenFeeRate": "double",
    "OpenFeeAmt": "double",
    "OffsetFeeRate": "double",
    "OffsetFeeAmt": "double",
    "OTFeeRate": "double",
    "OTFeeAmt": "double",
    "ExecFeeRate": "double",
    "ExecFeeAmt": "double",
    "PerOrderAmt": "double",
    "PerCancelAmt": "double",
    "HedgeFlag": "char",
}

CUstpFtdcQryInvestorMarginField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "ClientID": "string",
}

CUstpFtdcInvestorMarginField = {
    "BrokerID": "string",
    "ClientID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "ProductID": "string",
    "LongMarginRate": "double",
    "LongMarginAmt": "double",
    "ShortMarginRate": "double",
    "ShortMarginAmt": "double",
    "HedgeFlag": "char",
}

CUstpFtdcReqUserLoginField = {
    "TradingDay": "string",
    "UserID": "string",
    "BrokerID": "string",
    "Password": "string",
    "UserProductInfo": "string",
    "InterfaceProductInfo": "string",
    "ProtocolInfo": "string",
    "IPAddress": "string",
    "MacAddress": "string",
    "DataCenterID": "int",
    "UserProductFileSize": "int",
    "Authenticate2Type": "char",
    "Authenticate2Password": "string",
    "TerminalCode": "string",
    "PasswordEncrypt": "string",
}

CUstpFtdcstpUserDepositField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "Amount": "double",
    "AmountDirection": "char",
    "UserOrderLocalID": "string",
}

CUstpFtdcstpTransferMoneyField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "Amount": "double",
    "AmountDirection": "char",
    "UserOrderLocalID": "string",
    "BankID": "string",
    "BankPasswd": "string",
    "AccountPasswd": "string",
    "Currency": "string",
    "SerialNo": "string",
}

CUstpFtdcTradeField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "TradingDay": "string",
    "ParticipantID": "string",
    "SeatID": "string",
    "InvestorID": "string",
    "ClientID": "string",
    "UserID": "string",
    "OrderUserID": "string",
    "TradeID": "string",
    "OrderSysID": "string",
    "UserOrderLocalID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "TradePrice": "double",
    "TradeVolume": "int",
    "TradeTime": "string",
    "ClearingPartID": "string",
    "UsedFee": "double",
    "UsedMargin": "double",
    "Premium": "double",
    "Position": "int",
    "PositionCost": "double",
    "Available": "double",
    "Margin": "double",
    "FrozenMargin": "double",
    "BusinessLocalID": "int",
    "ActionDay": "string",
    "ArbiType": "char",
    "ArbiInstrumentID": "string",
}

CUstpFtdcOrderField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "SeatNo": "int",
    "InstrumentID": "string",
    "UserOrderLocalID": "string",
    "OrderPriceType": "char",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "LimitPrice": "double",
    "Volume": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "UserCustom": "string",
    "BusinessLocalID": "int",
    "ActionDay": "string",
    "ArbiType": "char",
    "TradingDay": "string",
    "ParticipantID": "string",
    "OrderUserID": "string",
    "ClientID": "string",
    "SeatID": "string",
    "InsertTime": "string",
    "OrderLocalID": "string",
    "OrderSource": "char",
    "OrderStatus": "char",
    "CancelTime": "string",
    "CancelUserID": "string",
    "VolumeTraded": "int",
    "VolumeRemain": "int",
    "OrderType": "char",
    "DeliveryFlag": "char",
}

CUstpFtdcFlowMessageCancelField = {
    "SequenceSeries": "int",
    "TradingDay": "string",
    "DataCenterID": "int",
    "StartSequenceNo": "int",
    "EndSequenceNo": "int",
}

CUstpFtdcDisseminationField = {
    "SequenceSeries": "int",
    "SequenceNo": "int",
}

CUstpFtdcInvestorAccountDepositResField = {
    "BrokerID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "AccountID": "string",
    "AccountSeqNo": "string",
    "Amount": "double",
    "AmountDirection": "char",
    "Available": "double",
    "Balance": "double",
}

CUstpFtdcInputQuoteField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "QuoteSysID": "string",
    "UserQuoteLocalID": "string",
    "QuoteLocalID": "string",
    "BidVolume": "int",
    "BidOffsetFlag": "char",
    "BidHedgeFlag": "char",
    "BidPrice": "double",
    "AskVolume": "int",
    "AskOffsetFlag": "char",
    "AskHedgeFlag": "char",
    "AskPrice": "double",
    "BusinessUnit": "string",
    "UserCustom": "string",
    "BidUserOrderLocalID": "string",
    "AskUserOrderLocalID": "string",
    "BidOrderLocalID": "string",
    "AskOrderLocalID": "string",
    "ReqForQuoteID": "string",
    "StandByTime": "int",
    "ClientID": "string",
}

CUstpFtdcRtnQuoteField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "QuoteSysID": "string",
    "UserQuoteLocalID": "string",
    "QuoteLocalID": "string",
    "BidVolume": "int",
    "BidOffsetFlag": "char",
    "BidHedgeFlag": "char",
    "BidPrice": "double",
    "AskVolume": "int",
    "AskOffsetFlag": "char",
    "AskHedgeFlag": "char",
    "AskPrice": "double",
    "BusinessUnit": "string",
    "UserCustom": "string",
    "BidUserOrderLocalID": "string",
    "AskUserOrderLocalID": "string",
    "BidOrderLocalID": "string",
    "AskOrderLocalID": "string",
    "ReqForQuoteID": "string",
    "StandByTime": "int",
    "BidOrderSysID": "string",
    "AskOrderSysID": "string",
    "QuoteStatus": "char",
    "InsertTime": "string",
    "CancelTime": "string",
    "TradeTime": "string",
    "ClientID": "string",
}

CUstpFtdcQuoteActionField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "QuoteSysID": "string",
    "UserQuoteLocalID": "string",
    "UserQuoteActionLocalID": "string",
    "ActionFlag": "char",
    "BusinessUnit": "string",
    "UserCustom": "string",
    "Direction": "char",
    "ClientID": "string",
}

CUstpFtdcReqForQuoteField = {
    "ReqForQuoteID": "string",
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "TradingDay": "string",
    "ReqForQuoteTime": "string",
    "ClientID": "string",
}

CUstpFtdcSyncMoneyTransferField = {
    "BrokerID": "string",
    "AccountID": "string",
    "BankID": "string",
    "BankAccount": "string",
    "Currency": "string",
    "Amount": "double",
    "SyncTransMoneyEvent": "char",
    "TradeCode": "string",
    "TradeSource": "char",
    "TransSerialNo": "string",
    "SerialNo": "string",
    "UserID": "string",
    "CommandDate": "string",
    "CommandTime": "string",
}

CUstpFtdcMarketDataBaseField = {
    "TradingDay": "string",
    "SettlementGroupID": "string",
    "SettlementID": "int",
    "PreSettlementPrice": "double",
    "PreClosePrice": "double",
    "PreOpenInterest": "double",
    "PreDelta": "double",
}

CUstpFtdcMarketDataStaticField = {
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "ClosePrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "SettlementPrice": "double",
    "CurrDelta": "double",
}

CUstpFtdcMarketDataLastMatchField = {
    "LastPrice": "double",
    "Volume": "int",
    "Turnover": "double",
    "OpenInterest": "double",
}

CUstpFtdcMarketDataBestPriceField = {
    "BidPrice1": "double",
    "BidVolume1": "int",
    "AskPrice1": "double",
    "AskVolume1": "int",
}

CUstpFtdcMarketDataBid23Field = {
    "BidPrice2": "double",
    "BidVolume2": "int",
    "BidPrice3": "double",
    "BidVolume3": "int",
}

CUstpFtdcMarketDataAsk23Field = {
    "AskPrice2": "double",
    "AskVolume2": "int",
    "AskPrice3": "double",
    "AskVolume3": "int",
}

CUstpFtdcMarketDataBid45Field = {
    "BidPrice4": "double",
    "BidVolume4": "int",
    "BidPrice5": "double",
    "BidVolume5": "int",
}

CUstpFtdcMarketDataAsk45Field = {
    "AskPrice4": "double",
    "AskVolume4": "int",
    "AskPrice5": "double",
    "AskVolume5": "int",
}

CUstpFtdcMarketDataUpdateTimeField = {
    "InstrumentID": "string",
    "UpdateTime": "string",
    "UpdateMillisec": "int",
    "ActionDay": "string",
}

CUstpFtdcDepthMarketDataField = {
    "TradingDay": "string",
    "SettlementGroupID": "string",
    "SettlementID": "int",
    "PreSettlementPrice": "double",
    "PreClosePrice": "double",
    "PreOpenInterest": "double",
    "PreDelta": "double",
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "ClosePrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "SettlementPrice": "double",
    "CurrDelta": "double",
    "LastPrice": "double",
    "Volume": "int",
    "Turnover": "double",
    "OpenInterest": "double",
    "BidPrice1": "double",
    "BidVolume1": "int",
    "AskPrice1": "double",
    "AskVolume1": "int",
    "BidPrice2": "double",
    "BidVolume2": "int",
    "BidPrice3": "double",
    "BidVolume3": "int",
    "AskPrice2": "double",
    "AskVolume2": "int",
    "AskPrice3": "double",
    "AskVolume3": "int",
    "BidPrice4": "double",
    "BidVolume4": "int",
    "BidPrice5": "double",
    "BidVolume5": "int",
    "AskPrice4": "double",
    "AskVolume4": "int",
    "AskPrice5": "double",
    "AskVolume5": "int",
    "InstrumentID": "string",
    "UpdateTime": "string",
    "UpdateMillisec": "int",
    "ActionDay": "string",
    "HisHighestPrice": "double",
    "HisLowestPrice": "double",
    "LatestVolume": "int",
    "InitVolume": "int",
    "ChangeVolume": "int",
    "BidImplyVolume": "int",
    "AskImplyVolume": "int",
    "AvgPrice": "double",
    "ArbiType": "char",
    "InstrumentID_1": "string",
    "InstrumentID_2": "string",
    "InstrumentName": "string",
    "TotalBidVolume": "int",
    "TotalAskVolume": "int",
}

CUstpFtdcSpecificInstrumentField = {
    "InstrumentID": "string",
}

CUstpFtdcMultiChannelHeartBeatField = {
    "UstpMultiChannelHeartBeatTimeOut": "int",
}

CUstpFtdcReqMarketTopicField = {
    "ExchangeID": "string",
}

CUstpFtdcRspMarketTopicField = {
    "ExchangeID": "string",
    "TopicID": "int",
}

CUstpFtdcInputMarginCombActionField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "UserID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "UserActionLocalID": "string",
    "CombInstrumentID": "string",
    "CombVolume": "int",
    "CombDirection": "char",
    "ActionLocalID": "string",
    "Direction": "char",
    "OrderSysID": "string",
    "CombActionStatus": "char",
}

CUstpFtdcQryInvestorCombPositionField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "CombInstrumentID": "string",
    "ClientID": "string",
}

CUstpFtdcRspInvestorCombPositionField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "Direction": "char",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "ClientID": "string",
    "CombInstrumentID": "string",
    "Leg1InstrumentID": "string",
    "Leg2InstrumentID": "string",
    "CombPosition": "int",
    "CombFrozenPosition": "int",
    "CombFreeMargin": "double",
}

CUstpFtdcMarginCombinationLegField = {
    "ExchangeID": "string",
    "CombInstrumentID": "string",
    "LegID": "int",
    "LegInstrumentID": "string",
    "Direction": "char",
    "LegMultiple": "int",
    "Priority": "int",
}

CUstpFtdcQryInvestorLegPositionField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "LegInstrumentID": "string",
    "ClientID": "string",
}

CUstpFtdcRspInvestorLegPositionField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "ClientID": "string",
    "InstrumentID": "string",
    "LongPosition": "int",
    "ShortPosition": "int",
    "LongMargin": "double",
    "ShortMargin": "double",
    "LongFrozenPosition": "int",
    "ShortFrozenPosition": "int",
    "LongFrozenMargin": "double",
    "ShortFrozenMargin": "double",
}

CUstpFtdcQryUstpInstrumentGroupField = {
    "ExchangeID": "string",
    "BrokerID": "string",
    "InstrumentID": "string",
}

CUstpFtdcRspInstrumentGroupField = {
    "ExchangeID": "string",
    "BrokerID": "string",
    "InstrumentID": "string",
    "InstrumentGroupID": "string",
}

CUstpFtdcQryClientMarginCombTypeField = {
    "ExchangeID": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "InstrumentGroupID": "string",
}

CUstpFtdcRspClientMarginCombTypeField = {
    "ExchangeID": "string",
    "BrokerID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "InstrumentGroupID": "string",
    "MarginCombType": "char",
}

CUstpFtdcReqQrySystemTimeField = {
    "ExchangeID": "string",
}

CUstpFtdcRspQrySystemTimeField = {
    "ExchangeID": "string",
    "SystemTime": "string",
}

CUstpFtdcInputExecOrderField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "InstrumentID": "string",
    "UserOrderLocalID": "string",
    "OrderType": "char",
    "DeliveryFlag": "char",
    "HedgeFlag": "char",
    "Volume": "int",
    "UserCustom": "string",
    "ActionDay": "string",
    "BusinessLocalID": "int",
    "BusinessUnit": "string",
}

CUstpFtdcInputExecOrderActionField = {
    "ExchangeID": "string",
    "OrderSysID": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "UserOrderActionLocalID": "string",
    "UserOrderLocalID": "string",
    "ActionFlag": "char",
    "VolumeChange": "int",
    "BusinessLocalID": "int",
    "OrderType": "char",
}

CUstpFtdcExecOrderField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "InvestorID": "string",
    "UserID": "string",
    "InstrumentID": "string",
    "UserOrderLocalID": "string",
    "OrderType": "char",
    "DeliveryFlag": "char",
    "HedgeFlag": "char",
    "Volume": "int",
    "UserCustom": "string",
    "ActionDay": "string",
    "BusinessLocalID": "int",
    "BusinessUnit": "string",
    "TradingDay": "string",
    "ParticipantID": "string",
    "OrderUserID": "string",
    "ClientID": "string",
    "SeatID": "string",
    "InsertTime": "string",
    "OrderLocalID": "string",
    "OrderSource": "char",
    "OrderStatus": "char",
    "CancelTime": "string",
    "CancelUserID": "string",
}

CUstpFtdcReqQryMarketDataField = {
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CUstpFtdcRspDepthMarketDataField = {
    "TradingDay": "string",
    "SettlementGroupID": "string",
    "SettlementID": "int",
    "PreSettlementPrice": "double",
    "PreClosePrice": "double",
    "PreOpenInterest": "double",
    "PreDelta": "double",
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "ClosePrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "SettlementPrice": "double",
    "CurrDelta": "double",
    "LastPrice": "double",
    "Volume": "int",
    "Turnover": "double",
    "OpenInterest": "double",
    "BidPrice1": "double",
    "BidVolume1": "int",
    "AskPrice1": "double",
    "AskVolume1": "int",
    "BidPrice2": "double",
    "BidVolume2": "int",
    "BidPrice3": "double",
    "BidVolume3": "int",
    "AskPrice2": "double",
    "AskVolume2": "int",
    "AskPrice3": "double",
    "AskVolume3": "int",
    "BidPrice4": "double",
    "BidVolume4": "int",
    "BidPrice5": "double",
    "BidVolume5": "int",
    "AskPrice4": "double",
    "AskVolume4": "int",
    "AskPrice5": "double",
    "AskVolume5": "int",
    "InstrumentID": "string",
    "UpdateTime": "string",
    "UpdateMillisec": "int",
    "ActionDay": "string",
    "HisHighestPrice": "double",
    "HisLowestPrice": "double",
    "LatestVolume": "int",
    "InitVolume": "int",
    "ChangeVolume": "int",
    "BidImplyVolume": "int",
    "AskImplyVolume": "int",
    "AvgPrice": "double",
    "ArbiType": "char",
    "InstrumentID_1": "string",
    "InstrumentID_2": "string",
    "InstrumentName": "string",
    "TotalBidVolume": "int",
    "TotalAskVolume": "int",
}

CUstpFtdcDSUserInfoField = {
    "AppID": "string",
    "AuthCode": "string",
    "EncryptType": "char",
}

CUstpFtdcDSUserCertReqDataField = {
    "AppID": "string",
    "UserCertReqData": "string",
    "TotalNum": "int",
    "CurrentNum": "int",
}

CUstpFtdcDSUserCertRspDataField = {
    "AppID": "string",
    "AppIDType": "char",
    "UserCertRspData": "string",
    "TotalNum": "int",
    "CurrentNum": "int",
}

CUstpFtdcDSLocalSystemDataField = {
    "AppID": "string",
    "ExceptionFlag": "char",
    "LocalSystemData": "string",
}

CUstpFtdcDSProxyCheckUserInfoField = {
    "AppID": "string",
    "AuthCode": "string",
    "EncryptType": "char",
}

CUstpFtdcDSProxyUserCertInField = {
    "UserCertReqInfo": "string",
}

CUstpFtdcDSProxyUserCertOutField = {
    "UserCertRspInfo": "string",
    "UserCertRspInfoLen": "int",
}

CUstpFtdcDSProxySubmitDataField = {
    "AppID": "string",
    "TerminalPubNetIP": "string",
    "TerminalPubNetPort": "string",
    "TerminalLoginTime": "string",
    "ExceptionFlag": "char",
    "RelayID": "string",
    "TerminalSystemData": "string",
}

CUstpFtdcReqQryMarginPrefParamField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "CombInstrumentID": "string",
    "CombInstrumentName": "string",
}

CUstpFtdcRspQryMarginPrefParamField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "CombInstrumentID": "string",
    "CombInstrumentName": "string",
    "CombType": "char",
    "HedgeFlag": "char",
    "Leg1InstrumentID": "string",
    "Leg1ProductID": "string",
    "Leg1Direction": "char",
    "Leg1HedgeFlag": "char",
    "Leg1SettlementPrice": "double",
    "Leg2InstrumentID": "string",
    "Leg2ProductID": "string",
    "Leg2Direction": "char",
    "Leg2HedgeFlag": "char",
    "Leg2SettlementPrice": "double",
    "Priority": "int",
    "TradeEna": "char",
}

