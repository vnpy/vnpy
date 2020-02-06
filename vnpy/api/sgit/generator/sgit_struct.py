CThostFtdcDisseminationField = {
    "SequenceSeries": "int",
    "SequenceNo": "int",
}

CThostFtdcReqUserLoginField = {
    "TradingDay": "string",
    "BrokerID": "string",
    "UserID": "string",
    "Password": "string",
    "UserProductInfo": "string",
    "InterfaceProductInfo": "string",
    "ProtocolInfo": "string",
    "MacAddress": "string",
    "OneTimePassword": "string",
    "ClientIPAddress": "string",
    "AppID": "string",
    "AuthCode": "string",
}

CThostFtdcRspUserLoginField = {
    "TradingDay": "string",
    "LoginTime": "string",
    "BrokerID": "string",
    "UserID": "string",
    "SystemName": "string",
    "FrontID": "int",
    "SessionID": "int",
    "MaxOrderRef": "string",
    "SHFETime": "string",
    "DCETime": "string",
    "CZCETime": "string",
    "FFEXTime": "string",
    "INETime": "string",
}

CThostFtdcUserLogoutField = {
    "BrokerID": "string",
    "UserID": "string",
}

CThostFtdcForceUserLogoutField = {
    "BrokerID": "string",
    "UserID": "string",
}

CThostFtdcReqAuthenticateField = {
    "BrokerID": "string",
    "UserID": "string",
    "UserProductInfo": "string",
    "AuthCode": "string",
}

CThostFtdcRspAuthenticateField = {
    "BrokerID": "string",
    "UserID": "string",
    "UserProductInfo": "string",
}

CThostFtdcAuthenticationInfoField = {
    "BrokerID": "string",
    "UserID": "string",
    "UserProductInfo": "string",
    "AuthInfo": "string",
    "IsResult": "int",
}

CThostFtdcTransferHeaderField = {
    "Version": "string",
    "TradeCode": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "TradeSerial": "string",
    "FutureID": "string",
    "BankID": "string",
    "BankBrchID": "string",
    "OperNo": "string",
    "DeviceID": "string",
    "RecordNum": "string",
    "SessionID": "int",
    "RequestID": "int",
}

CThostFtdcTransferBankToFutureReqField = {
    "FutureAccount": "string",
    "FuturePwdFlag": "char",
    "FutureAccPwd": "string",
    "TradeAmt": "double",
    "CustFee": "double",
    "CurrencyCode": "string",
}

CThostFtdcTransferBankToFutureRspField = {
    "RetCode": "string",
    "RetInfo": "string",
    "FutureAccount": "string",
    "TradeAmt": "double",
    "CustFee": "double",
    "CurrencyCode": "string",
}

CThostFtdcTransferFutureToBankReqField = {
    "FutureAccount": "string",
    "FuturePwdFlag": "char",
    "FutureAccPwd": "string",
    "TradeAmt": "double",
    "CustFee": "double",
    "CurrencyCode": "string",
}

CThostFtdcTransferFutureToBankRspField = {
    "RetCode": "string",
    "RetInfo": "string",
    "FutureAccount": "string",
    "TradeAmt": "double",
    "CustFee": "double",
    "CurrencyCode": "string",
}

CThostFtdcTransferQryBankReqField = {
    "FutureAccount": "string",
    "FuturePwdFlag": "char",
    "FutureAccPwd": "string",
    "CurrencyCode": "string",
}

CThostFtdcTransferQryBankRspField = {
    "RetCode": "string",
    "RetInfo": "string",
    "FutureAccount": "string",
    "TradeAmt": "double",
    "UseAmt": "double",
    "FetchAmt": "double",
    "CurrencyCode": "string",
}

CThostFtdcTransferQryDetailReqField = {
    "FutureAccount": "string",
}

CThostFtdcTransferQryDetailRspField = {
    "TradeDate": "string",
    "TradeTime": "string",
    "TradeCode": "string",
    "FutureSerial": "int",
    "FutureID": "string",
    "FutureAccount": "string",
    "BankSerial": "int",
    "BankID": "string",
    "BankBrchID": "string",
    "BankAccount": "string",
    "CertCode": "string",
    "CurrencyCode": "string",
    "TxAmount": "double",
    "Flag": "char",
}

CThostFtdcRspInfoField = {
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcExchangeField = {
    "ExchangeID": "string",
    "ExchangeName": "string",
    "ExchangeProperty": "char",
}

CThostFtdcProductField = {
    "ProductID": "string",
    "ProductName": "string",
    "ExchangeID": "string",
    "ProductClass": "char",
    "VolumeMultiple": "int",
    "PriceTick": "double",
    "MaxMarketOrderVolume": "int",
    "MinMarketOrderVolume": "int",
    "MaxLimitOrderVolume": "int",
    "MinLimitOrderVolume": "int",
    "PositionType": "char",
    "PositionDateType": "char",
    "CloseDealType": "char",
    "TradeCurrencyID": "string",
    "MortgageFundUseRange": "char",
    "ExchangeProductID": "string",
    "UnderlyingMultiple": "double",
}

CThostFtdcInstrumentField = {
    "InstrumentID": "string",
    "ExchangeID": "string",
    "InstrumentName": "string",
    "ExchangeInstID": "string",
    "ProductID": "string",
    "ProductClass": "char",
    "DeliveryYear": "int",
    "DeliveryMonth": "int",
    "MaxMarketOrderVolume": "int",
    "MinMarketOrderVolume": "int",
    "MaxLimitOrderVolume": "int",
    "MinLimitOrderVolume": "int",
    "VolumeMultiple": "int",
    "PriceTick": "double",
    "CreateDate": "string",
    "OpenDate": "string",
    "ExpireDate": "string",
    "StartDelivDate": "string",
    "EndDelivDate": "string",
    "InstLifePhase": "char",
    "IsTrading": "int",
    "PositionType": "char",
    "PositionDateType": "char",
    "LongMarginRatio": "double",
    "ShortMarginRatio": "double",
    "MaxMarginSideAlgorithm": "char",
    "UnderlyingInstrID": "string",
    "StrikePrice": "double",
    "OptionsType": "char",
    "UnderlyingMultiple": "double",
    "CombinationType": "char",
}

CThostFtdcBrokerField = {
    "BrokerID": "string",
    "BrokerAbbr": "string",
    "BrokerName": "string",
    "IsActive": "int",
}

CThostFtdcTraderField = {
    "ExchangeID": "string",
    "TraderID": "string",
    "ParticipantID": "string",
    "Password": "string",
    "InstallCount": "int",
    "BrokerID": "string",
}

CThostFtdcInvestorField = {
    "InvestorID": "string",
    "BrokerID": "string",
    "InvestorGroupID": "string",
    "InvestorName": "string",
    "IdentifiedCardType": "char",
    "IdentifiedCardNo": "string",
    "IsActive": "int",
    "Telephone": "string",
    "Address": "string",
    "OpenDate": "string",
    "Mobile": "string",
    "CommModelID": "string",
    "MarginModelID": "string",
}

CThostFtdcTradingCodeField = {
    "InvestorID": "string",
    "BrokerID": "string",
    "ExchangeID": "string",
    "ClientID": "string",
    "IsActive": "int",
    "ClientIDType": "char",
}

CThostFtdcPartBrokerField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "IsActive": "int",
}

CThostFtdcSuperUserField = {
    "UserID": "string",
    "UserName": "string",
    "Password": "string",
    "IsActive": "int",
}

CThostFtdcSuperUserFunctionField = {
    "UserID": "string",
    "FunctionCode": "char",
}

CThostFtdcInvestorGroupField = {
    "BrokerID": "string",
    "InvestorGroupID": "string",
    "InvestorGroupName": "string",
}

CThostFtdcTradingAccountField = {
    "BrokerID": "string",
    "AccountID": "string",
    "PreMortgage": "double",
    "PreCredit": "double",
    "PreDeposit": "double",
    "PreBalance": "double",
    "PreMargin": "double",
    "InterestBase": "double",
    "Interest": "double",
    "Deposit": "double",
    "Withdraw": "double",
    "FrozenMargin": "double",
    "FrozenCash": "double",
    "FrozenCommission": "double",
    "CurrMargin": "double",
    "CashIn": "double",
    "Commission": "double",
    "CloseProfit": "double",
    "PositionProfit": "double",
    "Balance": "double",
    "Available": "double",
    "WithdrawQuota": "double",
    "Reserve": "double",
    "TradingDay": "string",
    "SettlementID": "int",
    "Credit": "double",
    "Mortgage": "double",
    "ExchangeMargin": "double",
    "DeliveryMargin": "double",
    "ExchangeDeliveryMargin": "double",
    "ReserveBalance": "double",
    "CurrencyID": "string",
    "PreFundMortgageIn": "double",
    "PreFundMortgageOut": "double",
    "FundMortgageIn": "double",
    "FundMortgageOut": "double",
    "FundMortgageAvailable": "double",
    "MortgageableFund": "double",
    "SpecProductMargin": "double",
    "SpecProductFrozenMargin": "double",
    "SpecProductCommission": "double",
    "SpecProductFrozenCommission": "double",
    "SpecProductPositionProfit": "double",
    "SpecProductCloseProfit": "double",
    "SpecProductPositionProfitByAlg": "double",
    "SpecProductExchangeMargin": "double",
}

CThostFtdcInvestorPositionField = {
    "InstrumentID": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "PosiDirection": "char",
    "HedgeFlag": "char",
    "PositionDate": "char",
    "YdPosition": "int",
    "Position": "int",
    "LongFrozen": "int",
    "ShortFrozen": "int",
    "LongFrozenAmount": "double",
    "ShortFrozenAmount": "double",
    "OpenVolume": "int",
    "CloseVolume": "int",
    "OpenAmount": "double",
    "CloseAmount": "double",
    "PositionCost": "double",
    "PreMargin": "double",
    "UseMargin": "double",
    "FrozenMargin": "double",
    "FrozenCash": "double",
    "FrozenCommission": "double",
    "CashIn": "double",
    "Commission": "double",
    "CloseProfit": "double",
    "PositionProfit": "double",
    "PreSettlementPrice": "double",
    "SettlementPrice": "double",
    "TradingDay": "string",
    "SettlementID": "int",
    "OpenCost": "double",
    "ExchangeMargin": "double",
    "CombPosition": "int",
    "CombLongFrozen": "int",
    "CombShortFrozen": "int",
    "CloseProfitByDate": "double",
    "CloseProfitByTrade": "double",
    "TodayPosition": "int",
    "MarginRateByMoney": "double",
    "MarginRateByVolume": "double",
    "StrikeFrozen": "int",
    "StrikeFrozenAmount": "double",
    "AbandonFrozen": "int",
    "PrePosition": "int",
}

CThostFtdcInstrumentMarginRateField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "LongMarginRatioByMoney": "double",
    "LongMarginRatioByVolume": "double",
    "ShortMarginRatioByMoney": "double",
    "ShortMarginRatioByVolume": "double",
    "IsRelative": "int",
}

CThostFtdcInstrumentCommissionRateField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "OpenRatioByMoney": "double",
    "OpenRatioByVolume": "double",
    "CloseRatioByMoney": "double",
    "CloseRatioByVolume": "double",
    "CloseTodayRatioByMoney": "double",
    "CloseTodayRatioByVolume": "double",
}

CThostFtdcDepthMarketDataField = {
    "TradingDay": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "ExchangeInstID": "string",
    "LastPrice": "double",
    "PreSettlementPrice": "double",
    "PreClosePrice": "double",
    "PreOpenInterest": "double",
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "Volume": "int",
    "Turnover": "double",
    "OpenInterest": "double",
    "ClosePrice": "double",
    "SettlementPrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "PreDelta": "double",
    "CurrDelta": "double",
    "UpdateTime": "string",
    "UpdateMillisec": "int",
    "BidPrice1": "double",
    "BidVolume1": "int",
    "AskPrice1": "double",
    "AskVolume1": "int",
    "BidPrice2": "double",
    "BidVolume2": "int",
    "AskPrice2": "double",
    "AskVolume2": "int",
    "BidPrice3": "double",
    "BidVolume3": "int",
    "AskPrice3": "double",
    "AskVolume3": "int",
    "BidPrice4": "double",
    "BidVolume4": "int",
    "AskPrice4": "double",
    "AskVolume4": "int",
    "BidPrice5": "double",
    "BidVolume5": "int",
    "AskPrice5": "double",
    "AskVolume5": "int",
    "AveragePrice": "double",
    "ActionDay": "string",
    "InstrumentNo": "int",
    "PacketNo": "int",
    "CenterChangeNo": "char",
    "": "double",
    "": "double",
    "": "int",
}

CThostFtdcInstrumentTradingRightField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "TradingRight": "char",
}

CThostFtdcBrokerUserField = {
    "BrokerID": "string",
    "UserID": "string",
    "UserName": "string",
    "UserType": "char",
    "IsActive": "int",
    "IsUsingOTP": "int",
}

CThostFtdcBrokerUserPasswordField = {
    "BrokerID": "string",
    "UserID": "string",
    "Password": "string",
}

CThostFtdcBrokerUserFunctionField = {
    "BrokerID": "string",
    "UserID": "string",
    "BrokerFunctionCode": "char",
}

CThostFtdcTraderOfferField = {
    "ExchangeID": "string",
    "TraderID": "string",
    "ParticipantID": "string",
    "Password": "string",
    "InstallID": "int",
    "OrderLocalID": "string",
    "TraderConnectStatus": "char",
    "ConnectRequestDate": "string",
    "ConnectRequestTime": "string",
    "LastReportDate": "string",
    "LastReportTime": "string",
    "ConnectDate": "string",
    "ConnectTime": "string",
    "StartDate": "string",
    "StartTime": "string",
    "TradingDay": "string",
    "BrokerID": "string",
    "MaxTradeID": "string",
    "MaxOrderMessageReference": "string",
}

CThostFtdcSettlementInfoField = {
    "TradingDay": "string",
    "SettlementID": "int",
    "BrokerID": "string",
    "InvestorID": "string",
    "SequenceNo": "int",
    "Content": "string",
}

CThostFtdcInstrumentMarginRateAdjustField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "LongMarginRatioByMoney": "double",
    "LongMarginRatioByVolume": "double",
    "ShortMarginRatioByMoney": "double",
    "ShortMarginRatioByVolume": "double",
    "IsRelative": "int",
}

CThostFtdcExchangeMarginRateField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
    "LongMarginRatioByMoney": "double",
    "LongMarginRatioByVolume": "double",
    "ShortMarginRatioByMoney": "double",
    "ShortMarginRatioByVolume": "double",
}

CThostFtdcExchangeMarginRateAdjustField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
    "LongMarginRatioByMoney": "double",
    "LongMarginRatioByVolume": "double",
    "ShortMarginRatioByMoney": "double",
    "ShortMarginRatioByVolume": "double",
    "ExchLongMarginRatioByMoney": "double",
    "ExchLongMarginRatioByVolume": "double",
    "ExchShortMarginRatioByMoney": "double",
    "ExchShortMarginRatioByVolume": "double",
    "NoLongMarginRatioByMoney": "double",
    "NoLongMarginRatioByVolume": "double",
    "NoShortMarginRatioByMoney": "double",
    "NoShortMarginRatioByVolume": "double",
}

CThostFtdcExchangeRateField = {
    "BrokerID": "string",
    "FromCurrencyID": "string",
    "FromCurrencyUnit": "double",
    "ToCurrencyID": "string",
    "ExchangeRate": "double",
}

CThostFtdcSettlementRefField = {
    "TradingDay": "string",
    "SettlementID": "int",
}

CThostFtdcCurrentTimeField = {
    "CurrDate": "string",
    "CurrTime": "string",
    "CurrMillisec": "int",
    "ActionDay": "string",
}

CThostFtdcCommPhaseField = {
    "TradingDay": "string",
    "CommPhaseNo": "int",
    "SystemID": "string",
}

CThostFtdcLoginInfoField = {
    "FrontID": "int",
    "SessionID": "int",
    "BrokerID": "string",
    "UserID": "string",
    "LoginDate": "string",
    "LoginTime": "string",
    "IPAddress": "string",
    "UserProductInfo": "string",
    "InterfaceProductInfo": "string",
    "ProtocolInfo": "string",
    "SystemName": "string",
    "Password": "string",
    "MaxOrderRef": "string",
    "SHFETime": "string",
    "DCETime": "string",
    "CZCETime": "string",
    "FFEXTime": "string",
    "MacAddress": "string",
    "OneTimePassword": "string",
    "INETime": "string",
}

CThostFtdcLogoutAllField = {
    "FrontID": "int",
    "SessionID": "int",
    "SystemName": "string",
}

CThostFtdcFrontStatusField = {
    "FrontID": "int",
    "LastReportDate": "string",
    "LastReportTime": "string",
    "IsActive": "int",
}

CThostFtdcUserPasswordUpdateField = {
    "BrokerID": "string",
    "UserID": "string",
    "OldPassword": "string",
    "NewPassword": "string",
}

CThostFtdcInputOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "OrderRef": "string",
    "UserID": "string",
    "OrderPriceType": "char",
    "Direction": "char",
    "CombOffsetFlag": "string",
    "CombHedgeFlag": "string",
    "LimitPrice": "double",
    "VolumeTotalOriginal": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "ContingentCondition": "char",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "RequestID": "int",
    "UserForceClose": "int",
    "IsSwapOrder": "int",
    "OrderSysID": "string",
    "ExchangeID": "string",
    "VolumeTotal": "int",
    "ClientID": "string",
}

CThostFtdcOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "OrderRef": "string",
    "UserID": "string",
    "OrderPriceType": "char",
    "Direction": "char",
    "CombOffsetFlag": "string",
    "CombHedgeFlag": "string",
    "LimitPrice": "double",
    "VolumeTotalOriginal": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "ContingentCondition": "char",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "RequestID": "int",
    "OrderLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderSubmitStatus": "char",
    "NotifySequence": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "OrderSysID": "string",
    "OrderSource": "char",
    "OrderStatus": "char",
    "OrderType": "char",
    "VolumeTraded": "int",
    "VolumeTotal": "int",
    "InsertDate": "string",
    "InsertTime": "string",
    "ActiveTime": "string",
    "SuspendTime": "string",
    "UpdateTime": "string",
    "CancelTime": "string",
    "ActiveTraderID": "string",
    "ClearingPartID": "string",
    "SequenceNo": "int",
    "FrontID": "int",
    "SessionID": "int",
    "UserProductInfo": "string",
    "StatusMsg": "string",
    "UserForceClose": "int",
    "ActiveUserID": "string",
    "BrokerOrderSeq": "int",
    "RelativeOrderSysID": "string",
    "ZCETotalTradedVolume": "int",
    "IsSwapOrder": "int",
}

CThostFtdcExchangeOrderField = {
    "OrderPriceType": "char",
    "Direction": "char",
    "CombOffsetFlag": "string",
    "CombHedgeFlag": "string",
    "LimitPrice": "double",
    "VolumeTotalOriginal": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "ContingentCondition": "char",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "RequestID": "int",
    "OrderLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderSubmitStatus": "char",
    "NotifySequence": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "OrderSysID": "string",
    "OrderSource": "char",
    "OrderStatus": "char",
    "OrderType": "char",
    "VolumeTraded": "int",
    "VolumeTotal": "int",
    "InsertDate": "string",
    "InsertTime": "string",
    "ActiveTime": "string",
    "SuspendTime": "string",
    "UpdateTime": "string",
    "CancelTime": "string",
    "ActiveTraderID": "string",
    "ClearingPartID": "string",
    "SequenceNo": "int",
}

CThostFtdcExchangeOrderInsertErrorField = {
    "ExchangeID": "string",
    "ParticipantID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderLocalID": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcInputOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "OrderActionRef": "int",
    "OrderRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "ActionFlag": "char",
    "LimitPrice": "double",
    "VolumeChange": "int",
    "UserID": "string",
    "InstrumentID": "string",
    "ClientID": "string",
}

CThostFtdcOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "OrderActionRef": "int",
    "OrderRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "ActionFlag": "char",
    "LimitPrice": "double",
    "VolumeChange": "int",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderLocalID": "string",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
    "StatusMsg": "string",
    "InstrumentID": "string",
}

CThostFtdcExchangeOrderActionField = {
    "ExchangeID": "string",
    "OrderSysID": "string",
    "ActionFlag": "char",
    "LimitPrice": "double",
    "VolumeChange": "int",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderLocalID": "string",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
}

CThostFtdcExchangeOrderActionErrorField = {
    "ExchangeID": "string",
    "OrderSysID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderLocalID": "string",
    "ActionLocalID": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcExchangeTradeField = {
    "ExchangeID": "string",
    "TradeID": "string",
    "Direction": "char",
    "OrderSysID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "TradingRole": "char",
    "ExchangeInstID": "string",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "Price": "double",
    "Volume": "int",
    "TradeDate": "string",
    "TradeTime": "string",
    "TradeType": "char",
    "PriceSource": "char",
    "TraderID": "string",
    "OrderLocalID": "string",
    "ClearingPartID": "string",
    "BusinessUnit": "string",
    "SequenceNo": "int",
    "TradeSource": "char",
}

CThostFtdcTradeField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "OrderRef": "string",
    "UserID": "string",
    "ExchangeID": "string",
    "TradeID": "string",
    "Direction": "char",
    "OrderSysID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "TradingRole": "char",
    "ExchangeInstID": "string",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "Price": "double",
    "Volume": "int",
    "TradeDate": "string",
    "TradeTime": "string",
    "TradeType": "char",
    "PriceSource": "char",
    "TraderID": "string",
    "OrderLocalID": "string",
    "ClearingPartID": "string",
    "BusinessUnit": "string",
    "SequenceNo": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "BrokerOrderSeq": "int",
    "TradeSource": "char",
}

CThostFtdcUserSessionField = {
    "FrontID": "int",
    "SessionID": "int",
    "BrokerID": "string",
    "UserID": "string",
    "LoginDate": "string",
    "LoginTime": "string",
    "IPAddress": "string",
    "UserProductInfo": "string",
    "InterfaceProductInfo": "string",
    "ProtocolInfo": "string",
    "MacAddress": "string",
}

CThostFtdcQueryMaxOrderVolumeField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "MaxVolume": "int",
}

CThostFtdcSettlementInfoConfirmField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ConfirmDate": "string",
    "ConfirmTime": "string",
}

CThostFtdcSyncDepositField = {
    "DepositSeqNo": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "Deposit": "double",
    "IsForce": "int",
    "CurrencyID": "string",
}

CThostFtdcSyncFundMortgageField = {
    "MortgageSeqNo": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "FromCurrencyID": "string",
    "MortgageAmount": "double",
    "ToCurrencyID": "string",
}

CThostFtdcBrokerSyncField = {
    "BrokerID": "string",
}

CThostFtdcSyncingInvestorField = {
    "InvestorID": "string",
    "BrokerID": "string",
    "InvestorGroupID": "string",
    "InvestorName": "string",
    "IdentifiedCardType": "char",
    "IdentifiedCardNo": "string",
    "IsActive": "int",
    "Telephone": "string",
    "Address": "string",
    "OpenDate": "string",
    "Mobile": "string",
    "CommModelID": "string",
    "MarginModelID": "string",
}

CThostFtdcSyncingTradingCodeField = {
    "InvestorID": "string",
    "BrokerID": "string",
    "ExchangeID": "string",
    "ClientID": "string",
    "IsActive": "int",
    "ClientIDType": "char",
}

CThostFtdcSyncingInvestorGroupField = {
    "BrokerID": "string",
    "InvestorGroupID": "string",
    "InvestorGroupName": "string",
}

CThostFtdcSyncingTradingAccountField = {
    "BrokerID": "string",
    "AccountID": "string",
    "PreMortgage": "double",
    "PreCredit": "double",
    "PreDeposit": "double",
    "PreBalance": "double",
    "PreMargin": "double",
    "InterestBase": "double",
    "Interest": "double",
    "Deposit": "double",
    "Withdraw": "double",
    "FrozenMargin": "double",
    "FrozenCash": "double",
    "FrozenCommission": "double",
    "CurrMargin": "double",
    "CashIn": "double",
    "Commission": "double",
    "CloseProfit": "double",
    "PositionProfit": "double",
    "Balance": "double",
    "Available": "double",
    "WithdrawQuota": "double",
    "Reserve": "double",
    "TradingDay": "string",
    "SettlementID": "int",
    "Credit": "double",
    "Mortgage": "double",
    "ExchangeMargin": "double",
    "DeliveryMargin": "double",
    "ExchangeDeliveryMargin": "double",
    "ReserveBalance": "double",
    "CurrencyID": "string",
    "PreFundMortgageIn": "double",
    "PreFundMortgageOut": "double",
    "FundMortgageIn": "double",
    "FundMortgageOut": "double",
    "FundMortgageAvailable": "double",
    "MortgageableFund": "double",
    "SpecProductMargin": "double",
    "SpecProductFrozenMargin": "double",
    "SpecProductCommission": "double",
    "SpecProductFrozenCommission": "double",
    "SpecProductPositionProfit": "double",
    "SpecProductCloseProfit": "double",
    "SpecProductPositionProfitByAlg": "double",
    "SpecProductExchangeMargin": "double",
}

CThostFtdcSyncingInvestorPositionField = {
    "InstrumentID": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "PosiDirection": "char",
    "HedgeFlag": "char",
    "PositionDate": "char",
    "YdPosition": "int",
    "Position": "int",
    "LongFrozen": "int",
    "ShortFrozen": "int",
    "LongFrozenAmount": "double",
    "ShortFrozenAmount": "double",
    "OpenVolume": "int",
    "CloseVolume": "int",
    "OpenAmount": "double",
    "CloseAmount": "double",
    "PositionCost": "double",
    "PreMargin": "double",
    "UseMargin": "double",
    "FrozenMargin": "double",
    "FrozenCash": "double",
    "FrozenCommission": "double",
    "CashIn": "double",
    "Commission": "double",
    "CloseProfit": "double",
    "PositionProfit": "double",
    "PreSettlementPrice": "double",
    "SettlementPrice": "double",
    "TradingDay": "string",
    "SettlementID": "int",
    "OpenCost": "double",
    "ExchangeMargin": "double",
    "CombPosition": "int",
    "CombLongFrozen": "int",
    "CombShortFrozen": "int",
    "CloseProfitByDate": "double",
    "CloseProfitByTrade": "double",
    "TodayPosition": "int",
    "MarginRateByMoney": "double",
    "MarginRateByVolume": "double",
    "StrikeFrozen": "int",
    "StrikeFrozenAmount": "double",
    "AbandonFrozen": "int",
}

CThostFtdcSyncingInstrumentMarginRateField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "LongMarginRatioByMoney": "double",
    "LongMarginRatioByVolume": "double",
    "ShortMarginRatioByMoney": "double",
    "ShortMarginRatioByVolume": "double",
    "IsRelative": "int",
}

CThostFtdcSyncingInstrumentCommissionRateField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "OpenRatioByMoney": "double",
    "OpenRatioByVolume": "double",
    "CloseRatioByMoney": "double",
    "CloseRatioByVolume": "double",
    "CloseTodayRatioByMoney": "double",
    "CloseTodayRatioByVolume": "double",
}

CThostFtdcSyncingInstrumentTradingRightField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "TradingRight": "char",
}

CThostFtdcQryOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "InsertTimeStart": "string",
    "InsertTimeEnd": "string",
}

CThostFtdcQryTradeField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "TradeID": "string",
    "TradeTimeStart": "string",
    "TradeTimeEnd": "string",
}

CThostFtdcQryInvestorPositionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CThostFtdcQryTradingAccountField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "CurrencyID": "string",
}

CThostFtdcQryInvestorField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcQryTradingCodeField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "ClientID": "string",
    "ClientIDType": "char",
}

CThostFtdcQryInvestorGroupField = {
    "BrokerID": "string",
}

CThostFtdcQryInstrumentMarginRateField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
}

CThostFtdcQryInstrumentCommissionRateField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CThostFtdcQryInstrumentTradingRightField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CThostFtdcQryBrokerField = {
    "BrokerID": "string",
}

CThostFtdcQryTraderField = {
    "ExchangeID": "string",
    "ParticipantID": "string",
    "TraderID": "string",
}

CThostFtdcQrySuperUserFunctionField = {
    "UserID": "string",
}

CThostFtdcQryUserSessionField = {
    "FrontID": "int",
    "SessionID": "int",
    "BrokerID": "string",
    "UserID": "string",
}

CThostFtdcQryPartBrokerField = {
    "ExchangeID": "string",
    "BrokerID": "string",
    "ParticipantID": "string",
}

CThostFtdcQryFrontStatusField = {
    "FrontID": "int",
}

CThostFtdcQryExchangeOrderField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcQryOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
}

CThostFtdcQryExchangeOrderActionField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcQrySuperUserField = {
    "UserID": "string",
}

CThostFtdcQryExchangeField = {
    "ExchangeID": "string",
}

CThostFtdcQryProductField = {
    "ProductID": "string",
    "ProductClass": "char",
}

CThostFtdcQryInstrumentField = {
    "InstrumentID": "string",
    "ExchangeID": "string",
    "ExchangeInstID": "string",
    "ProductID": "string",
}

CThostFtdcQryDepthMarketDataField = {
    "InstrumentID": "string",
}

CThostFtdcQryBrokerUserField = {
    "BrokerID": "string",
    "UserID": "string",
}

CThostFtdcQryBrokerUserFunctionField = {
    "BrokerID": "string",
    "UserID": "string",
}

CThostFtdcQryTraderOfferField = {
    "ExchangeID": "string",
    "ParticipantID": "string",
    "TraderID": "string",
}

CThostFtdcQrySyncDepositField = {
    "BrokerID": "string",
    "DepositSeqNo": "string",
}

CThostFtdcQrySettlementInfoField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "TradingDay": "string",
}

CThostFtdcQryExchangeMarginRateField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
}

CThostFtdcQryExchangeMarginRateAdjustField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
}

CThostFtdcQryExchangeRateField = {
    "BrokerID": "string",
    "FromCurrencyID": "string",
    "ToCurrencyID": "string",
}

CThostFtdcQrySyncFundMortgageField = {
    "BrokerID": "string",
    "MortgageSeqNo": "string",
}

CThostFtdcQryHisOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "InsertTimeStart": "string",
    "InsertTimeEnd": "string",
    "TradingDay": "string",
    "SettlementID": "int",
}

CThostFtdcOptionInstrMiniMarginField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "MinMargin": "double",
    "ValueMethod": "char",
    "IsRelative": "int",
}

CThostFtdcOptionInstrMarginAdjustField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "SShortMarginRatioByMoney": "double",
    "SShortMarginRatioByVolume": "double",
    "HShortMarginRatioByMoney": "double",
    "HShortMarginRatioByVolume": "double",
    "AShortMarginRatioByMoney": "double",
    "AShortMarginRatioByVolume": "double",
    "IsRelative": "int",
}

CThostFtdcOptionInstrCommRateField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "OpenRatioByMoney": "double",
    "OpenRatioByVolume": "double",
    "CloseRatioByMoney": "double",
    "CloseRatioByVolume": "double",
    "CloseTodayRatioByMoney": "double",
    "CloseTodayRatioByVolume": "double",
    "StrikeRatioByMoney": "double",
    "StrikeRatioByVolume": "double",
}

CThostFtdcOptionInstrTradeCostField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
    "FixedMargin": "double",
    "MiniMargin": "double",
    "Royalty": "double",
    "ExchFixedMargin": "double",
    "ExchMiniMargin": "double",
}

CThostFtdcQryOptionInstrTradeCostField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
    "InputPrice": "double",
    "UnderlyingPrice": "double",
}

CThostFtdcQryOptionInstrCommRateField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CThostFtdcIndexPriceField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "ClosePrice": "double",
}

CThostFtdcInputExecOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExecOrderRef": "string",
    "UserID": "string",
    "Volume": "int",
    "RequestID": "int",
    "BusinessUnit": "string",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "ActionType": "char",
    "PosiDirection": "char",
    "ReservePositionFlag": "char",
    "CloseFlag": "char",
}

CThostFtdcInputExecOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExecOrderActionRef": "int",
    "ExecOrderRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "ExecOrderSysID": "string",
    "ActionFlag": "char",
    "UserID": "string",
    "InstrumentID": "string",
}

CThostFtdcExecOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExecOrderRef": "string",
    "UserID": "string",
    "Volume": "int",
    "RequestID": "int",
    "BusinessUnit": "string",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "ActionType": "char",
    "PosiDirection": "char",
    "ReservePositionFlag": "char",
    "CloseFlag": "char",
    "ExecOrderLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderSubmitStatus": "char",
    "NotifySequence": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "ExecOrderSysID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "CancelTime": "string",
    "ExecResult": "char",
    "ClearingPartID": "string",
    "SequenceNo": "int",
    "FrontID": "int",
    "SessionID": "int",
    "UserProductInfo": "string",
    "StatusMsg": "string",
    "ActiveUserID": "string",
    "BrokerExecOrderSeq": "int",
}

CThostFtdcExecOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExecOrderActionRef": "int",
    "ExecOrderRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "ExecOrderSysID": "string",
    "ActionFlag": "char",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "ExecOrderLocalID": "string",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
    "ActionType": "char",
    "StatusMsg": "string",
    "InstrumentID": "string",
}

CThostFtdcQryExecOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "ExecOrderSysID": "string",
    "InsertTimeStart": "string",
    "InsertTimeEnd": "string",
}

CThostFtdcExchangeExecOrderField = {
    "Volume": "int",
    "RequestID": "int",
    "BusinessUnit": "string",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "ActionType": "char",
    "PosiDirection": "char",
    "ReservePositionFlag": "char",
    "CloseFlag": "char",
    "ExecOrderLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderSubmitStatus": "char",
    "NotifySequence": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "ExecOrderSysID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "CancelTime": "string",
    "ExecResult": "char",
    "ClearingPartID": "string",
    "SequenceNo": "int",
}

CThostFtdcQryExchangeExecOrderField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcQryExecOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
}

CThostFtdcExchangeExecOrderActionField = {
    "ExchangeID": "string",
    "ExecOrderSysID": "string",
    "ActionFlag": "char",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "ExecOrderLocalID": "string",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
    "ActionType": "char",
}

CThostFtdcQryExchangeExecOrderActionField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcErrExecOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExecOrderRef": "string",
    "UserID": "string",
    "Volume": "int",
    "RequestID": "int",
    "BusinessUnit": "string",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "ActionType": "char",
    "PosiDirection": "char",
    "ReservePositionFlag": "char",
    "CloseFlag": "char",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcQryErrExecOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcErrExecOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExecOrderActionRef": "int",
    "ExecOrderRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "ExecOrderSysID": "string",
    "ActionFlag": "char",
    "UserID": "string",
    "InstrumentID": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcQryErrExecOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcOptionInstrTradingRightField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "Direction": "char",
    "TradingRight": "char",
}

CThostFtdcQryOptionInstrTradingRightField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "Direction": "char",
}

CThostFtdcInputForQuoteField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ForQuoteRef": "string",
    "UserID": "string",
}

CThostFtdcForQuoteField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ForQuoteRef": "string",
    "UserID": "string",
    "ForQuoteLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "InsertDate": "string",
    "InsertTime": "string",
    "ForQuoteStatus": "char",
    "FrontID": "int",
    "SessionID": "int",
    "StatusMsg": "string",
    "ActiveUserID": "string",
    "BrokerForQutoSeq": "int",
}

CThostFtdcQryForQuoteField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "InsertTimeStart": "string",
    "InsertTimeEnd": "string",
}

CThostFtdcExchangeForQuoteField = {
    "ForQuoteLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "InsertDate": "string",
    "InsertTime": "string",
    "ForQuoteStatus": "char",
}

CThostFtdcQryExchangeForQuoteField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcInputQuoteField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "QuoteRef": "string",
    "UserID": "string",
    "AskPrice": "double",
    "BidPrice": "double",
    "AskVolume": "int",
    "BidVolume": "int",
    "RequestID": "int",
    "BusinessUnit": "string",
    "AskOffsetFlag": "char",
    "BidOffsetFlag": "char",
    "AskHedgeFlag": "char",
    "BidHedgeFlag": "char",
    "AskOrderRef": "string",
    "BidOrderRef": "string",
    "ForQuoteSysID": "string",
}

CThostFtdcInputQuoteActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "QuoteActionRef": "int",
    "QuoteRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "QuoteSysID": "string",
    "ActionFlag": "char",
    "UserID": "string",
    "InstrumentID": "string",
}

CThostFtdcQuoteField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "QuoteRef": "string",
    "UserID": "string",
    "AskPrice": "double",
    "BidPrice": "double",
    "AskVolume": "int",
    "BidVolume": "int",
    "RequestID": "int",
    "BusinessUnit": "string",
    "AskOffsetFlag": "char",
    "BidOffsetFlag": "char",
    "AskHedgeFlag": "char",
    "BidHedgeFlag": "char",
    "QuoteLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "NotifySequence": "int",
    "OrderSubmitStatus": "char",
    "TradingDay": "string",
    "SettlementID": "int",
    "QuoteSysID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "CancelTime": "string",
    "QuoteStatus": "char",
    "ClearingPartID": "string",
    "SequenceNo": "int",
    "AskOrderSysID": "string",
    "BidOrderSysID": "string",
    "FrontID": "int",
    "SessionID": "int",
    "UserProductInfo": "string",
    "StatusMsg": "string",
    "ActiveUserID": "string",
    "BrokerQuoteSeq": "int",
    "AskOrderRef": "string",
    "BidOrderRef": "string",
    "ForQuoteSysID": "string",
}

CThostFtdcQuoteActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "QuoteActionRef": "int",
    "QuoteRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "QuoteSysID": "string",
    "ActionFlag": "char",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "QuoteLocalID": "string",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
    "StatusMsg": "string",
    "InstrumentID": "string",
}

CThostFtdcQryQuoteField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "QuoteSysID": "string",
    "InsertTimeStart": "string",
    "InsertTimeEnd": "string",
}

CThostFtdcExchangeQuoteField = {
    "AskPrice": "double",
    "BidPrice": "double",
    "AskVolume": "int",
    "BidVolume": "int",
    "RequestID": "int",
    "BusinessUnit": "string",
    "AskOffsetFlag": "char",
    "BidOffsetFlag": "char",
    "AskHedgeFlag": "char",
    "BidHedgeFlag": "char",
    "QuoteLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "NotifySequence": "int",
    "OrderSubmitStatus": "char",
    "TradingDay": "string",
    "SettlementID": "int",
    "QuoteSysID": "string",
    "InsertDate": "string",
    "InsertTime": "string",
    "CancelTime": "string",
    "QuoteStatus": "char",
    "ClearingPartID": "string",
    "SequenceNo": "int",
    "AskOrderSysID": "string",
    "BidOrderSysID": "string",
    "ForQuoteSysID": "string",
}

CThostFtdcQryExchangeQuoteField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcQryQuoteActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
}

CThostFtdcExchangeQuoteActionField = {
    "ExchangeID": "string",
    "QuoteSysID": "string",
    "ActionFlag": "char",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "QuoteLocalID": "string",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
}

CThostFtdcQryExchangeQuoteActionField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcOptionInstrDeltaField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "Delta": "double",
}

CThostFtdcForQuoteRspField = {
    "TradingDay": "string",
    "InstrumentID": "string",
    "ForQuoteSysID": "string",
    "ForQuoteTime": "string",
    "ActionDay": "string",
    "ExchangeID": "string",
}

CThostFtdcStrikeOffsetField = {
    "InstrumentID": "string",
    "InvestorRange": "char",
    "BrokerID": "string",
    "InvestorID": "string",
    "Offset": "double",
}

CThostFtdcQryStrikeOffsetField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CThostFtdcInputBatchOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "OrderActionRef": "int",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "UserID": "string",
}

CThostFtdcBatchOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "OrderActionRef": "int",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
    "StatusMsg": "string",
}

CThostFtdcExchangeBatchOrderActionField = {
    "ExchangeID": "string",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
}

CThostFtdcQryBatchOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
}

CThostFtdcCombInstrumentGuardField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "GuarantRatio": "double",
}

CThostFtdcQryCombInstrumentGuardField = {
    "BrokerID": "string",
    "InstrumentID": "string",
}

CThostFtdcInputCombActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "CombActionRef": "string",
    "UserID": "string",
    "Direction": "char",
    "Volume": "int",
    "CombDirection": "char",
    "HedgeFlag": "char",
}

CThostFtdcCombActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "CombActionRef": "string",
    "UserID": "string",
    "Direction": "char",
    "Volume": "int",
    "CombDirection": "char",
    "HedgeFlag": "char",
    "ActionLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "ActionStatus": "char",
    "NotifySequence": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "SequenceNo": "int",
    "FrontID": "int",
    "SessionID": "int",
    "UserProductInfo": "string",
    "StatusMsg": "string",
}

CThostFtdcQryCombActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
}

CThostFtdcExchangeCombActionField = {
    "Direction": "char",
    "Volume": "int",
    "CombDirection": "char",
    "HedgeFlag": "char",
    "ActionLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "ActionStatus": "char",
    "NotifySequence": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "SequenceNo": "int",
}

CThostFtdcQryExchangeCombActionField = {
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "ExchangeID": "string",
    "TraderID": "string",
}

CThostFtdcProductExchRateField = {
    "ProductID": "string",
    "QuoteCurrencyID": "string",
    "ExchangeRate": "double",
}

CThostFtdcQryProductExchRateField = {
    "ProductID": "string",
}

CThostFtdcQryForQuoteParamField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
}

CThostFtdcForQuoteParamField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "LastPrice": "double",
    "PriceInterval": "double",
}

CThostFtdcMarketDataField = {
    "TradingDay": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
    "ExchangeInstID": "string",
    "LastPrice": "double",
    "PreSettlementPrice": "double",
    "PreClosePrice": "double",
    "PreOpenInterest": "double",
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "Volume": "int",
    "Turnover": "double",
    "OpenInterest": "double",
    "ClosePrice": "double",
    "SettlementPrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "PreDelta": "double",
    "CurrDelta": "double",
    "UpdateTime": "string",
    "UpdateMillisec": "int",
    "ActionDay": "string",
}

CThostFtdcMarketDataBaseField = {
    "TradingDay": "string",
    "PreSettlementPrice": "double",
    "PreClosePrice": "double",
    "PreOpenInterest": "double",
    "PreDelta": "double",
}

CThostFtdcMarketDataStaticField = {
    "OpenPrice": "double",
    "HighestPrice": "double",
    "LowestPrice": "double",
    "ClosePrice": "double",
    "UpperLimitPrice": "double",
    "LowerLimitPrice": "double",
    "SettlementPrice": "double",
    "CurrDelta": "double",
}

CThostFtdcMarketDataLastMatchField = {
    "LastPrice": "double",
    "Volume": "int",
    "Turnover": "double",
    "OpenInterest": "double",
}

CThostFtdcMarketDataBestPriceField = {
    "BidPrice1": "double",
    "BidVolume1": "int",
    "AskPrice1": "double",
    "AskVolume1": "int",
}

CThostFtdcMarketDataBid23Field = {
    "BidPrice2": "double",
    "BidVolume2": "int",
    "BidPrice3": "double",
    "BidVolume3": "int",
}

CThostFtdcMarketDataAsk23Field = {
    "AskPrice2": "double",
    "AskVolume2": "int",
    "AskPrice3": "double",
    "AskVolume3": "int",
}

CThostFtdcMarketDataBid45Field = {
    "BidPrice4": "double",
    "BidVolume4": "int",
    "BidPrice5": "double",
    "BidVolume5": "int",
}

CThostFtdcMarketDataAsk45Field = {
    "AskPrice4": "double",
    "AskVolume4": "int",
    "AskPrice5": "double",
    "AskVolume5": "int",
}

CThostFtdcMarketDataUpdateTimeField = {
    "InstrumentID": "string",
    "UpdateTime": "string",
    "UpdateMillisec": "int",
    "ActionDay": "string",
}

CThostFtdcMarketDataExchangeField = {
    "ExchangeID": "string",
}

CThostFtdcSpecificInstrumentField = {
    "InstrumentID": "string",
}

CThostFtdcInstrumentStatusField = {
    "ExchangeID": "string",
    "ExchangeInstID": "string",
    "SettlementGroupID": "string",
    "InstrumentID": "string",
    "InstrumentStatus": "char",
    "TradingSegmentSN": "int",
    "EnterTime": "string",
    "EnterReason": "char",
}

CThostFtdcQryInstrumentStatusField = {
    "ExchangeID": "string",
    "ExchangeInstID": "string",
}

CThostFtdcInvestorAccountField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "AccountID": "string",
    "CurrencyID": "string",
}

CThostFtdcPositionProfitAlgorithmField = {
    "BrokerID": "string",
    "AccountID": "string",
    "Algorithm": "char",
    "Memo": "string",
    "CurrencyID": "string",
}

CThostFtdcDiscountField = {
    "BrokerID": "string",
    "InvestorRange": "char",
    "InvestorID": "string",
    "Discount": "double",
}

CThostFtdcQryTransferBankField = {
    "BankID": "string",
    "BankBrchID": "string",
}

CThostFtdcTransferBankField = {
    "BankID": "string",
    "BankBrchID": "string",
    "BankName": "string",
    "IsActive": "int",
}

CThostFtdcQryInvestorPositionDetailField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CThostFtdcInvestorPositionDetailField = {
    "InstrumentID": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "HedgeFlag": "char",
    "Direction": "char",
    "OpenDate": "string",
    "TradeID": "string",
    "Volume": "int",
    "OpenPrice": "double",
    "TradingDay": "string",
    "SettlementID": "int",
    "TradeType": "char",
    "CombInstrumentID": "string",
    "ExchangeID": "string",
    "CloseProfitByDate": "double",
    "CloseProfitByTrade": "double",
    "PositionProfitByDate": "double",
    "PositionProfitByTrade": "double",
    "Margin": "double",
    "ExchMargin": "double",
    "MarginRateByMoney": "double",
    "MarginRateByVolume": "double",
    "LastSettlementPrice": "double",
    "SettlementPrice": "double",
    "CloseVolume": "int",
    "CloseAmount": "double",
}

CThostFtdcTradingAccountPasswordField = {
    "BrokerID": "string",
    "AccountID": "string",
    "Password": "string",
    "CurrencyID": "string",
}

CThostFtdcMDTraderOfferField = {
    "ExchangeID": "string",
    "TraderID": "string",
    "ParticipantID": "string",
    "Password": "string",
    "InstallID": "int",
    "OrderLocalID": "string",
    "TraderConnectStatus": "char",
    "ConnectRequestDate": "string",
    "ConnectRequestTime": "string",
    "LastReportDate": "string",
    "LastReportTime": "string",
    "ConnectDate": "string",
    "ConnectTime": "string",
    "StartDate": "string",
    "StartTime": "string",
    "TradingDay": "string",
    "BrokerID": "string",
    "MaxTradeID": "string",
    "MaxOrderMessageReference": "string",
}

CThostFtdcQryMDTraderOfferField = {
    "ExchangeID": "string",
    "ParticipantID": "string",
    "TraderID": "string",
}

CThostFtdcQryNoticeField = {
    "BrokerID": "string",
}

CThostFtdcNoticeField = {
    "BrokerID": "string",
    "Content": "string",
    "SequenceLabel": "string",
}

CThostFtdcUserRightField = {
    "BrokerID": "string",
    "UserID": "string",
    "UserRightType": "char",
    "IsForbidden": "int",
}

CThostFtdcQrySettlementInfoConfirmField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcLoadSettlementInfoField = {
    "BrokerID": "string",
}

CThostFtdcBrokerWithdrawAlgorithmField = {
    "BrokerID": "string",
    "WithdrawAlgorithm": "char",
    "UsingRatio": "double",
    "IncludeCloseProfit": "char",
    "AllWithoutTrade": "char",
    "AvailIncludeCloseProfit": "char",
    "IsBrokerUserEvent": "int",
    "CurrencyID": "string",
    "FundMortgageRatio": "double",
    "BalanceAlgorithm": "char",
}

CThostFtdcTradingAccountPasswordUpdateV1Field = {
    "BrokerID": "string",
    "InvestorID": "string",
    "OldPassword": "string",
    "NewPassword": "string",
}

CThostFtdcTradingAccountPasswordUpdateField = {
    "BrokerID": "string",
    "AccountID": "string",
    "OldPassword": "string",
    "NewPassword": "string",
    "CurrencyID": "string",
}

CThostFtdcQryCombinationLegField = {
    "CombInstrumentID": "string",
    "LegID": "int",
    "LegInstrumentID": "string",
}

CThostFtdcQrySyncStatusField = {
    "TradingDay": "string",
}

CThostFtdcCombinationLegField = {
    "CombInstrumentID": "string",
    "LegID": "int",
    "LegInstrumentID": "string",
    "Direction": "char",
    "LegMultiple": "int",
    "ImplyLevel": "int",
}

CThostFtdcSyncStatusField = {
    "TradingDay": "string",
    "DataSyncStatus": "char",
}

CThostFtdcQryLinkManField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcLinkManField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "PersonType": "char",
    "IdentifiedCardType": "char",
    "IdentifiedCardNo": "string",
    "PersonName": "string",
    "Telephone": "string",
    "Address": "string",
    "ZipCode": "string",
    "Priority": "int",
    "UOAZipCode": "string",
    "PersonFullName": "string",
}

CThostFtdcQryBrokerUserEventField = {
    "BrokerID": "string",
    "UserID": "string",
    "UserEventType": "char",
}

CThostFtdcBrokerUserEventField = {
    "BrokerID": "string",
    "UserID": "string",
    "UserEventType": "char",
    "EventSequenceNo": "int",
    "EventDate": "string",
    "EventTime": "string",
    "UserEventInfo": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
}

CThostFtdcQryContractBankField = {
    "BrokerID": "string",
    "BankID": "string",
    "BankBrchID": "string",
}

CThostFtdcContractBankField = {
    "BrokerID": "string",
    "BankID": "string",
    "BankBrchID": "string",
    "BankName": "string",
}

CThostFtdcInvestorPositionCombineDetailField = {
    "TradingDay": "string",
    "OpenDate": "string",
    "ExchangeID": "string",
    "SettlementID": "int",
    "BrokerID": "string",
    "InvestorID": "string",
    "ComTradeID": "string",
    "TradeID": "string",
    "InstrumentID": "string",
    "HedgeFlag": "char",
    "Direction": "char",
    "TotalAmt": "int",
    "Margin": "double",
    "ExchMargin": "double",
    "MarginRateByMoney": "double",
    "MarginRateByVolume": "double",
    "LegID": "int",
    "LegMultiple": "int",
    "CombInstrumentID": "string",
    "TradeGroupID": "int",
}

CThostFtdcParkedOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "OrderRef": "string",
    "UserID": "string",
    "OrderPriceType": "char",
    "Direction": "char",
    "CombOffsetFlag": "string",
    "CombHedgeFlag": "string",
    "LimitPrice": "double",
    "VolumeTotalOriginal": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "ContingentCondition": "char",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "RequestID": "int",
    "UserForceClose": "int",
    "ExchangeID": "string",
    "ParkedOrderID": "string",
    "UserType": "char",
    "Status": "char",
    "ErrorID": "int",
    "ErrorMsg": "string",
    "IsSwapOrder": "int",
}

CThostFtdcParkedOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "OrderActionRef": "int",
    "OrderRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "ActionFlag": "char",
    "LimitPrice": "double",
    "VolumeChange": "int",
    "UserID": "string",
    "InstrumentID": "string",
    "ParkedOrderActionID": "string",
    "UserType": "char",
    "Status": "char",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcQryParkedOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
}

CThostFtdcQryParkedOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "ExchangeID": "string",
}

CThostFtdcRemoveParkedOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ParkedOrderID": "string",
}

CThostFtdcRemoveParkedOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ParkedOrderActionID": "string",
}

CThostFtdcInvestorWithdrawAlgorithmField = {
    "BrokerID": "string",
    "InvestorRange": "char",
    "InvestorID": "string",
    "UsingRatio": "double",
    "CurrencyID": "string",
    "FundMortgageRatio": "double",
}

CThostFtdcQryInvestorPositionCombineDetailField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "CombInstrumentID": "string",
}

CThostFtdcMarketDataAveragePriceField = {
    "AveragePrice": "double",
}

CThostFtdcVerifyInvestorPasswordField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "Password": "string",
}

CThostFtdcUserIPField = {
    "BrokerID": "string",
    "UserID": "string",
    "IPAddress": "string",
    "IPMask": "string",
    "MacAddress": "string",
}

CThostFtdcTradingNoticeInfoField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "SendTime": "string",
    "FieldContent": "string",
    "SequenceSeries": "int",
    "SequenceNo": "int",
}

CThostFtdcTradingNoticeField = {
    "BrokerID": "string",
    "InvestorRange": "char",
    "InvestorID": "string",
    "SequenceSeries": "int",
    "UserID": "string",
    "SendTime": "string",
    "SequenceNo": "int",
    "FieldContent": "string",
}

CThostFtdcQryTradingNoticeField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcQryErrOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcErrOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "OrderRef": "string",
    "UserID": "string",
    "OrderPriceType": "char",
    "Direction": "char",
    "CombOffsetFlag": "string",
    "CombHedgeFlag": "string",
    "LimitPrice": "double",
    "VolumeTotalOriginal": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "ContingentCondition": "char",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "RequestID": "int",
    "UserForceClose": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
    "IsSwapOrder": "int",
}

CThostFtdcErrorConditionalOrderField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "OrderRef": "string",
    "UserID": "string",
    "OrderPriceType": "char",
    "Direction": "char",
    "CombOffsetFlag": "string",
    "CombHedgeFlag": "string",
    "LimitPrice": "double",
    "VolumeTotalOriginal": "int",
    "TimeCondition": "char",
    "GTDDate": "string",
    "VolumeCondition": "char",
    "MinVolume": "int",
    "ContingentCondition": "char",
    "StopPrice": "double",
    "ForceCloseReason": "char",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
    "RequestID": "int",
    "OrderLocalID": "string",
    "ExchangeID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "ExchangeInstID": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderSubmitStatus": "char",
    "NotifySequence": "int",
    "TradingDay": "string",
    "SettlementID": "int",
    "OrderSysID": "string",
    "OrderSource": "char",
    "OrderStatus": "char",
    "OrderType": "char",
    "VolumeTraded": "int",
    "VolumeTotal": "int",
    "InsertDate": "string",
    "InsertTime": "string",
    "ActiveTime": "string",
    "SuspendTime": "string",
    "UpdateTime": "string",
    "CancelTime": "string",
    "ActiveTraderID": "string",
    "ClearingPartID": "string",
    "SequenceNo": "int",
    "FrontID": "int",
    "SessionID": "int",
    "UserProductInfo": "string",
    "StatusMsg": "string",
    "UserForceClose": "int",
    "ActiveUserID": "string",
    "BrokerOrderSeq": "int",
    "RelativeOrderSysID": "string",
    "ZCETotalTradedVolume": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
    "IsSwapOrder": "int",
}

CThostFtdcQryErrOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcErrOrderActionField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "OrderActionRef": "int",
    "OrderRef": "string",
    "RequestID": "int",
    "FrontID": "int",
    "SessionID": "int",
    "ExchangeID": "string",
    "OrderSysID": "string",
    "ActionFlag": "char",
    "LimitPrice": "double",
    "VolumeChange": "int",
    "ActionDate": "string",
    "ActionTime": "string",
    "TraderID": "string",
    "InstallID": "int",
    "OrderLocalID": "string",
    "ActionLocalID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "BusinessUnit": "string",
    "OrderActionStatus": "char",
    "UserID": "string",
    "StatusMsg": "string",
    "InstrumentID": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcQryExchangeSequenceField = {
    "ExchangeID": "string",
}

CThostFtdcExchangeSequenceField = {
    "ExchangeID": "string",
    "SequenceNo": "int",
    "MarketStatus": "char",
}

CThostFtdcQueryMaxOrderVolumeWithPriceField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "MaxVolume": "int",
    "Price": "double",
}

CThostFtdcQryBrokerTradingParamsField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "CurrencyID": "string",
}

CThostFtdcBrokerTradingParamsField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "MarginPriceType": "char",
    "Algorithm": "char",
    "AvailIncludeCloseProfit": "char",
    "CurrencyID": "string",
    "OptionRoyaltyPriceType": "char",
}

CThostFtdcQryBrokerTradingAlgosField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CThostFtdcBrokerTradingAlgosField = {
    "BrokerID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "HandlePositionAlgoID": "char",
    "FindMarginRateAlgoID": "char",
    "HandleTradingAccountAlgoID": "char",
}

CThostFtdcQueryBrokerDepositField = {
    "BrokerID": "string",
    "ExchangeID": "string",
}

CThostFtdcBrokerDepositField = {
    "TradingDay": "string",
    "BrokerID": "string",
    "ParticipantID": "string",
    "ExchangeID": "string",
    "PreBalance": "double",
    "CurrMargin": "double",
    "CloseProfit": "double",
    "Balance": "double",
    "Deposit": "double",
    "Withdraw": "double",
    "Available": "double",
    "Reserve": "double",
    "FrozenMargin": "double",
}

CThostFtdcQryCFMMCBrokerKeyField = {
    "BrokerID": "string",
}

CThostFtdcCFMMCBrokerKeyField = {
    "BrokerID": "string",
    "ParticipantID": "string",
    "CreateDate": "string",
    "CreateTime": "string",
    "KeyID": "int",
    "CurrentKey": "string",
    "KeyKind": "char",
}

CThostFtdcCFMMCTradingAccountKeyField = {
    "BrokerID": "string",
    "ParticipantID": "string",
    "AccountID": "string",
    "KeyID": "int",
    "CurrentKey": "string",
}

CThostFtdcQryCFMMCTradingAccountKeyField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcBrokerUserOTPParamField = {
    "BrokerID": "string",
    "UserID": "string",
    "OTPVendorsID": "string",
    "SerialNumber": "string",
    "AuthKey": "string",
    "LastDrift": "int",
    "LastSuccess": "int",
    "OTPType": "char",
}

CThostFtdcManualSyncBrokerUserOTPField = {
    "BrokerID": "string",
    "UserID": "string",
    "OTPType": "char",
    "FirstOTP": "string",
    "SecondOTP": "string",
}

CThostFtdcCommRateModelField = {
    "BrokerID": "string",
    "CommModelID": "string",
    "CommModelName": "string",
}

CThostFtdcQryCommRateModelField = {
    "BrokerID": "string",
    "CommModelID": "string",
}

CThostFtdcMarginModelField = {
    "BrokerID": "string",
    "MarginModelID": "string",
    "MarginModelName": "string",
}

CThostFtdcQryMarginModelField = {
    "BrokerID": "string",
    "MarginModelID": "string",
}

CThostFtdcEWarrantOffsetField = {
    "TradingDay": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
    "Direction": "char",
    "HedgeFlag": "char",
    "Volume": "int",
}

CThostFtdcQryEWarrantOffsetField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ExchangeID": "string",
    "InstrumentID": "string",
}

CThostFtdcQryInvestorProductGroupMarginField = {
    "BrokerID": "string",
    "InvestorID": "string",
    "ProductGroupID": "string",
    "HedgeFlag": "char",
}

CThostFtdcInvestorProductGroupMarginField = {
    "ProductGroupID": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "TradingDay": "string",
    "SettlementID": "int",
    "FrozenMargin": "double",
    "LongFrozenMargin": "double",
    "ShortFrozenMargin": "double",
    "UseMargin": "double",
    "LongUseMargin": "double",
    "ShortUseMargin": "double",
    "ExchMargin": "double",
    "LongExchMargin": "double",
    "ShortExchMargin": "double",
    "CloseProfit": "double",
    "FrozenCommission": "double",
    "Commission": "double",
    "FrozenCash": "double",
    "CashIn": "double",
    "PositionProfit": "double",
    "OffsetAmount": "double",
    "LongOffsetAmount": "double",
    "ShortOffsetAmount": "double",
    "ExchOffsetAmount": "double",
    "LongExchOffsetAmount": "double",
    "ShortExchOffsetAmount": "double",
    "HedgeFlag": "char",
}

CThostFtdcQueryCFMMCTradingAccountTokenField = {
    "BrokerID": "string",
    "InvestorID": "string",
}

CThostFtdcCFMMCTradingAccountTokenField = {
    "BrokerID": "string",
    "ParticipantID": "string",
    "AccountID": "string",
    "KeyID": "int",
    "Token": "string",
}

CThostFtdcQryProductGroupField = {
    "ProductID": "string",
    "ExchangeID": "string",
}

CThostFtdcProductGroupField = {
    "ProductID": "string",
    "ExchangeID": "string",
    "ProductGroupID": "string",
}

CThostFtdcReqOpenAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "Gender": "char",
    "CountryCode": "string",
    "CustType": "char",
    "Address": "string",
    "ZipCode": "string",
    "Telephone": "string",
    "MobilePhone": "string",
    "Fax": "string",
    "EMail": "string",
    "MoneyAccountStatus": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "CashExchangeCode": "char",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "TID": "int",
    "UserID": "string",
}

CThostFtdcReqCancelAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "Gender": "char",
    "CountryCode": "string",
    "CustType": "char",
    "Address": "string",
    "ZipCode": "string",
    "Telephone": "string",
    "MobilePhone": "string",
    "Fax": "string",
    "EMail": "string",
    "MoneyAccountStatus": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "CashExchangeCode": "char",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "TID": "int",
    "UserID": "string",
}

CThostFtdcReqChangeAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "Gender": "char",
    "CountryCode": "string",
    "CustType": "char",
    "Address": "string",
    "ZipCode": "string",
    "Telephone": "string",
    "MobilePhone": "string",
    "Fax": "string",
    "EMail": "string",
    "MoneyAccountStatus": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "NewBankAccount": "string",
    "NewBankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "BankAccType": "char",
    "InstallID": "int",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "BrokerIDByBank": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "TID": "int",
    "Digest": "string",
}

CThostFtdcReqTransferField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "FutureSerial": "int",
    "UserID": "string",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "TradeAmount": "double",
    "FutureFetchAmount": "double",
    "FeePayFlag": "char",
    "CustFee": "double",
    "BrokerFee": "double",
    "Message": "string",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "TransferStatus": "char",
}

CThostFtdcRspTransferField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "FutureSerial": "int",
    "UserID": "string",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "TradeAmount": "double",
    "FutureFetchAmount": "double",
    "FeePayFlag": "char",
    "CustFee": "double",
    "BrokerFee": "double",
    "Message": "string",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "TransferStatus": "char",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcReqRepealField = {
    "RepealTimeInterval": "int",
    "RepealedTimes": "int",
    "BankRepealFlag": "char",
    "BrokerRepealFlag": "char",
    "PlateRepealSerial": "int",
    "BankRepealSerial": "string",
    "FutureRepealSerial": "int",
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "FutureSerial": "int",
    "UserID": "string",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "TradeAmount": "double",
    "FutureFetchAmount": "double",
    "FeePayFlag": "char",
    "CustFee": "double",
    "BrokerFee": "double",
    "Message": "string",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "TransferStatus": "char",
}

CThostFtdcRspRepealField = {
    "RepealTimeInterval": "int",
    "RepealedTimes": "int",
    "BankRepealFlag": "char",
    "BrokerRepealFlag": "char",
    "PlateRepealSerial": "int",
    "BankRepealSerial": "string",
    "FutureRepealSerial": "int",
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "FutureSerial": "int",
    "UserID": "string",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "TradeAmount": "double",
    "FutureFetchAmount": "double",
    "FeePayFlag": "char",
    "CustFee": "double",
    "BrokerFee": "double",
    "Message": "string",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "TransferStatus": "char",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcReqQueryAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "FutureSerial": "int",
    "InstallID": "int",
    "UserID": "string",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
}

CThostFtdcRspQueryAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "FutureSerial": "int",
    "InstallID": "int",
    "UserID": "string",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "BankUseAmount": "double",
    "BankFetchAmount": "double",
}

CThostFtdcFutureSignIOField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Digest": "string",
    "CurrencyID": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
}

CThostFtdcRspFutureSignInField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Digest": "string",
    "CurrencyID": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
    "PinKey": "string",
    "MacKey": "string",
}

CThostFtdcReqFutureSignOutField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Digest": "string",
    "CurrencyID": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
}

CThostFtdcRspFutureSignOutField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Digest": "string",
    "CurrencyID": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcReqQueryTradeResultBySerialField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "Reference": "int",
    "RefrenceIssureType": "char",
    "RefrenceIssure": "string",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "CurrencyID": "string",
    "TradeAmount": "double",
    "Digest": "string",
}

CThostFtdcRspQueryTradeResultBySerialField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
    "Reference": "int",
    "RefrenceIssureType": "char",
    "RefrenceIssure": "string",
    "OriginReturnCode": "string",
    "OriginDescrInfoForReturnCode": "string",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "CurrencyID": "string",
    "TradeAmount": "double",
    "Digest": "string",
}

CThostFtdcReqDayEndFileReadyField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "FileBusinessCode": "char",
    "Digest": "string",
}

CThostFtdcReturnResultField = {
    "ReturnCode": "string",
    "DescrInfoForReturnCode": "string",
}

CThostFtdcVerifyFuturePasswordField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "AccountID": "string",
    "Password": "string",
    "BankAccount": "string",
    "BankPassWord": "string",
    "InstallID": "int",
    "TID": "int",
    "CurrencyID": "string",
}

CThostFtdcVerifyCustInfoField = {
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
}

CThostFtdcVerifyFuturePasswordAndCustInfoField = {
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "AccountID": "string",
    "Password": "string",
    "CurrencyID": "string",
}

CThostFtdcDepositResultInformField = {
    "DepositSeqNo": "string",
    "BrokerID": "string",
    "InvestorID": "string",
    "Deposit": "double",
    "RequestID": "int",
    "ReturnCode": "string",
    "DescrInfoForReturnCode": "string",
}

CThostFtdcReqSyncKeyField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Message": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
}

CThostFtdcRspSyncKeyField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Message": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcNotifyQueryAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustType": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "FutureSerial": "int",
    "InstallID": "int",
    "UserID": "string",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "BankUseAmount": "double",
    "BankFetchAmount": "double",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcTransferSerialField = {
    "PlateSerial": "int",
    "TradeDate": "string",
    "TradingDay": "string",
    "TradeTime": "string",
    "TradeCode": "string",
    "SessionID": "int",
    "BankID": "string",
    "BankBranchID": "string",
    "BankAccType": "char",
    "BankAccount": "string",
    "BankSerial": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "FutureAccType": "char",
    "AccountID": "string",
    "InvestorID": "string",
    "FutureSerial": "int",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CurrencyID": "string",
    "TradeAmount": "double",
    "CustFee": "double",
    "BrokerFee": "double",
    "AvailabilityFlag": "char",
    "OperatorCode": "string",
    "BankNewAccount": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcQryTransferSerialField = {
    "BrokerID": "string",
    "AccountID": "string",
    "BankID": "string",
    "CurrencyID": "string",
}

CThostFtdcNotifyFutureSignInField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Digest": "string",
    "CurrencyID": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
    "PinKey": "string",
    "MacKey": "string",
}

CThostFtdcNotifyFutureSignOutField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Digest": "string",
    "CurrencyID": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcNotifySyncKeyField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "InstallID": "int",
    "UserID": "string",
    "Message": "string",
    "DeviceID": "string",
    "BrokerIDByBank": "string",
    "OperNo": "string",
    "RequestID": "int",
    "TID": "int",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcQryAccountregisterField = {
    "BrokerID": "string",
    "AccountID": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "CurrencyID": "string",
}

CThostFtdcAccountregisterField = {
    "TradeDay": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BankAccount": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "AccountID": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "CustomerName": "string",
    "CurrencyID": "string",
    "OpenOrDestroy": "char",
    "RegDate": "string",
    "OutDate": "string",
    "TID": "int",
    "CustType": "char",
    "BankAccType": "char",
}

CThostFtdcOpenAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "Gender": "char",
    "CountryCode": "string",
    "CustType": "char",
    "Address": "string",
    "ZipCode": "string",
    "Telephone": "string",
    "MobilePhone": "string",
    "Fax": "string",
    "EMail": "string",
    "MoneyAccountStatus": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "CashExchangeCode": "char",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "TID": "int",
    "UserID": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcCancelAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "Gender": "char",
    "CountryCode": "string",
    "CustType": "char",
    "Address": "string",
    "ZipCode": "string",
    "Telephone": "string",
    "MobilePhone": "string",
    "Fax": "string",
    "EMail": "string",
    "MoneyAccountStatus": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "InstallID": "int",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "CashExchangeCode": "char",
    "Digest": "string",
    "BankAccType": "char",
    "DeviceID": "string",
    "BankSecuAccType": "char",
    "BrokerIDByBank": "string",
    "BankSecuAcc": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "OperNo": "string",
    "TID": "int",
    "UserID": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcChangeAccountField = {
    "TradeCode": "string",
    "BankID": "string",
    "BankBranchID": "string",
    "BrokerID": "string",
    "BrokerBranchID": "string",
    "TradeDate": "string",
    "TradeTime": "string",
    "BankSerial": "string",
    "TradingDay": "string",
    "PlateSerial": "int",
    "LastFragment": "char",
    "SessionID": "int",
    "CustomerName": "string",
    "IdCardType": "char",
    "IdentifiedCardNo": "string",
    "Gender": "char",
    "CountryCode": "string",
    "CustType": "char",
    "Address": "string",
    "ZipCode": "string",
    "Telephone": "string",
    "MobilePhone": "string",
    "Fax": "string",
    "EMail": "string",
    "MoneyAccountStatus": "char",
    "BankAccount": "string",
    "BankPassWord": "string",
    "NewBankAccount": "string",
    "NewBankPassWord": "string",
    "AccountID": "string",
    "Password": "string",
    "BankAccType": "char",
    "InstallID": "int",
    "VerifyCertNoFlag": "char",
    "CurrencyID": "string",
    "BrokerIDByBank": "string",
    "BankPwdFlag": "char",
    "SecuPwdFlag": "char",
    "TID": "int",
    "Digest": "string",
    "ErrorID": "int",
    "ErrorMsg": "string",
}

CThostFtdcSecAgentACIDMapField = {
    "BrokerID": "string",
    "UserID": "string",
    "AccountID": "string",
    "CurrencyID": "string",
    "BrokerSecAgentID": "string",
}

CThostFtdcQrySecAgentACIDMapField = {
    "BrokerID": "string",
    "UserID": "string",
    "AccountID": "string",
    "CurrencyID": "string",
}

CThostFtdcUserRightsAssignField = {
    "BrokerID": "string",
    "UserID": "string",
    "DRIdentityID": "int",
}

CThostFtdcBrokerUserRightAssignField = {
    "BrokerID": "string",
    "DRIdentityID": "int",
    "Tradeable": "int",
}

CThostFtdcDRTransferField = {
    "OrigDRIdentityID": "int",
    "DestDRIdentityID": "int",
    "OrigBrokerID": "string",
    "DestBrokerID": "string",
}

CThostFtdcFensUserInfoField = {
    "BrokerID": "string",
    "UserID": "string",
    "LoginMode": "char",
}

CThostFtdcCurrTransferIdentityField = {
    "IdentityID": "int",
}

CThostFtdcLoginForbiddenUserField = {
    "BrokerID": "string",
    "UserID": "string",
    "IPAddress": "string",
}

CThostFtdcQryLoginForbiddenUserField = {
    "BrokerID": "string",
    "UserID": "string",
}

CThostFtdcMulticastGroupInfoField = {
    "GroupIP": "string",
    "GroupPort": "int",
    "SourceIP": "string",
}

CThostFtdcTradingAccountReserveField = {
    "BrokerID": "string",
    "AccountID": "string",
    "Reserve": "double",
    "CurrencyID": "string",
}

CThostMBLQuotReq = {
    "StartInstrumentID": "string",
    "EndInstrumentID": "string",
    "Direction": "char",
}

CThostMBLQuotData = {
    "InstrumentID": "string",
    "Direction": "char",
    "Price": "double",
    "Volume": "int",
}

CThostSubQuotField = {
    "InstrumentID": "string",
}

CThostDeferDeliveryQuot = {
}

CThostDeferFeeRateField = {
}

CThostDeferMidAppTradeField = {
    "BrokerID": "string",
    "ClientID": "string",
    "InvestorID": "string",
    "InstrumentID": "string",
    "OrderRef": "string",
    "UserID": "string",
    "ExchangeID": "string",
    "TradeID": "string",
    "Direction": "char",
    "OrderSysID": "string",
    "Price": "double",
    "Volume": "int",
    "TradeDate": "string",
    "TradeTime": "string",
    "TraderID": "string",
    "OrderLocalID": "string",
    "MiddleFlag": "int",
}

CThostFtdcPositionNettingField = {
    "BrokerID": "string",
    "InstrumentID": "string",
    "InvestorID": "string",
    "Direction": "char",
    "HedgeFlag": "char",
    "PositionNetting": "int",
    "Price": "double",
    "MarginNetting": "double",
}

}

