TapAPITradeUserInfo = {
    "SystemType": "dict",
    "UserNo": "string",
    "LoginIP": "string",
    "LoginProt": "unsigned int",
    "LoginType": "dict",
}

TapAPITradeLoginAuth = {
    "UserNo": "string",
    "UserType": "dict",
    "AuthCode": "string",
    "AppID": "string",
    "ISModifyPassword": "char",
    "Password": "string",
    "NewPassword": "string",
    "ISDDA": "char",
    "DDASerialNo": "string",
    "NoticeIgnoreFlag": "dict",
    "LoginInfo": "string",
}

TapAPITradeLoginRspInfo = {
    "UserNo": "string",
    "UserType": "dict",
    "UserName": "string",
    "QuoteTempPassword": "string",
    "ReservedInfo": "string",
    "LastLoginIP": "string",
    "LastLoginProt": "unsigned int",
    "LastLoginTime": "string",
    "LastLogoutTime": "string",
    "TradeDate": "string",
    "LastSettleTime": "string",
    "StartTime": "string",
    "InitTime": "string",
    "AuthType": "dict",
    "AuthDate": "string",
}

TapAPISubmitUserLoginInfo = {
    "UserNo": "string",
    "GatherInfo": "string",
    "ClientLoginIP": "string",
    "ClientLoginPort": "unsigned int",
    "ClientLoginDateTime": "string",
    "ClientAppID": "string",
    "AuthKeyVersion": "unsigned int",
}

TapAPISubmitUserLoginInfoRsp = {
    "UserNo": "string",
    "ErrorCode": "unsigned int",
    "ErrorText": "string",
}

TapAPIExchangeInfo = {
    "ExchangeNo": "string",
    "ExchangeName": "string",
}

TapAPICommodity = {
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
}

TapAPICommodityInfo = {
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "CommodityName": "string",
    "CommodityEngName": "string",
    "RelateExchangeNo": "string",
    "RelateCommodityType": "char",
    "RelateCommodityNo": "string",
    "RelateExchangeNo2": "string",
    "RelateCommodityType2": "char",
    "RelateCommodityNo2": "string",
    "TradeCurrency": "string",
    "ContractSize": "double",
    "OpenCloseMode": "dict",
    "StrikePriceTimes": "double",
    "CommodityTickSize": "double",
    "CommodityDenominator": "int",
    "CmbDirect": "dict",
    "OnlyCanCloseDays": "int",
    "DeliveryMode": "dict",
    "DeliveryDays": "int",
    "AddOneTime": "string",
    "CommodityTimeZone": "int",
    "IsAddOne": "dict",
}

TapAPIContract = {
    "Commodity": "dict",
    "ContractNo1": "string",
    "StrikePrice1": "string",
    "CallOrPutFlag1": "char",
    "ContractNo2": "string",
    "StrikePrice2": "string",
    "CallOrPutFlag2": "char",
}

TapAPITradeContractInfo = {
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo1": "string",
    "StrikePrice1": "string",
    "CallOrPutFlag1": "char",
    "ContractNo2": "string",
    "StrikePrice2": "string",
    "CallOrPutFlag2": "char",
    "ContractName": "string",
    "ContractExpDate": "string",
    "LastTradeDate": "string",
    "FirstNoticeDate": "string",
    "FutureContractNo": "string",
}

TapAPIChangePasswordReq = {
    "OldPassword": "string",
    "NewPassword": "string",
}

TapAPIUserRightInfo = {
    "UserNo": "string",
    "RightID": "dict",
}

TapAPIUserOrderFrequency = {
    "UserNo": "string",
    "UserOrderFrequency": "unsigned int",
}

TapAPIAccQryReq = {
    "AccountNo": "string",
}

TapAPIAccountInfo = {
    "AccountNo": "string",
    "AccountType": "dict",
    "AccountState": "dict",
    "AccountShortName": "string",
    "AccountIsDocHolder": "dict",
    "IsMarketMaker": "char",
    "AccountFamilyType": "dict",
}

TapAPINewOrder = {
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "ContractNo2": "string",
    "StrikePrice2": "string",
    "CallOrPutFlag2": "char",
    "OrderType": "dict",
    "OrderSource": "dict",
    "TimeInForce": "dict",
    "ExpireTime": "string",
    "IsRiskOrder": "char",
    "OrderSide": "dict",
    "PositionEffect": "dict",
    "PositionEffect2": "dict",
    "InquiryNo": "string",
    "HedgeFlag": "dict",
    "HedgeFlag2": "dict",
    "OrderPrice": "double",
    "OrderPrice2": "double",
    "OrderQty": "unsigned int",
    "OrderQty2": "unsigned int",
    "OrderMinQty": "unsigned int",
    "MinClipSize": "unsigned int",
    "MaxClipSize": "unsigned int",
    "RefInt": "int",
    "RefDouble": "double",
    "RefString": "string",
    "TacticsType": "dict",
    "TriggerCondition": "dict",
    "TriggerPriceType": "dict",
    "StopPrice": "double",
    "AddOneIsValid": "char",
    "MarketLevel": "dict",
    "FutureAutoCloseFlag": "char",
    "UpperChannelNo": "string",
}

TapAPIOrderInfo = {
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "ContractNo2": "string",
    "StrikePrice2": "string",
    "CallOrPutFlag2": "char",
    "OrderType": "dict",
    "OrderSource": "dict",
    "TimeInForce": "dict",
    "ExpireTime": "string",
    "IsRiskOrder": "char",
    "OrderSide": "dict",
    "PositionEffect": "dict",
    "PositionEffect2": "dict",
    "InquiryNo": "string",
    "HedgeFlag": "dict",
    "HedgeFlag2": "dict",
    "OrderPrice": "double",
    "OrderPrice2": "double",
    "StopPrice": "double",
    "OrderQty": "unsigned int",
    "OrderQty2": "unsigned int",
    "OrderMinQty": "unsigned int",
    "MinClipSize": "unsigned int",
    "MaxClipSize": "unsigned int",
    "RefInt": "int",
    "RefDouble": "double",
    "RefString": "string",
    "TacticsType": "dict",
    "TriggerCondition": "dict",
    "TriggerPriceType": "dict",
    "AddOneIsValid": "char",
    "MarketLevel": "dict",
    "FutureAutoCloseFlag": "char",
    "OrderCanceledQty": "unsigned int",
    "LicenseNo": "string",
    "ParentAccountNo": "string",
    "ServerFlag": "char",
    "OrderNo": "string",
    "ClientOrderNo": "string",
    "OrderLocalNo": "string",
    "OrderSystemNo": "string",
    "OrderExchangeSystemNo": "string",
    "OrderParentNo": "dict",
    "OrderParentSystemNo": "dict",
    "TradeNo": "string",
    "UpperNo": "string",
    "UpperChannelNo": "string",
    "UpperSettleNo": "string",
    "UpperUserNo": "string",
    "OrderInsertUserNo": "string",
    "OrderInsertTime": "string",
    "OrderCommandUserNo": "string",
    "OrderUpdateUserNo": "string",
    "OrderUpdateTime": "string",
    "OrderState": "dict",
    "OrderMatchPrice": "double",
    "OrderMatchPrice2": "double",
    "OrderMatchQty": "unsigned int",
    "OrderMatchQty2": "unsigned int",
    "ErrorCode": "unsigned int",
    "ErrorText": "string",
    "IsBackInput": "char",
    "IsDeleted": "char",
    "IsAddOne": "char",
    "OrderStreamID": "unsigned int",
    "UpperStreamID": "dict",
    "ContractSize": "dict",
    "ContractSize2": "dict",
    "CommodityCurrencyGroup": "dict",
    "CommodityCurrency": "dict",
    "FeeMode": "dict",
    "FeeParam": "dict",
    "FeeCurrencyGroup": "dict",
    "FeeCurrency": "dict",
    "FeeMode2": "dict",
    "FeeParam2": "dict",
    "FeeCurrencyGroup2": "dict",
    "FeeCurrency2": "dict",
    "MarginMode": "dict",
    "MarginParam": "dict",
    "MarginMode2": "dict",
    "MarginParam2": "dict",
    "PreSettlePrice": "dict",
    "PreSettlePrice2": "dict",
    "OpenVol": "dict",
    "CoverVol": "dict",
    "OpenVol2": "dict",
    "CoverVol2": "dict",
    "FeeValue": "double",
    "MarginValue": "double",
    "OrderDeleteByDisConnFlag": "char",
}

TapAPIOrderActionRsp = {
    "ActionType": "dict",
    "OrderInfo": "dict",
}

TapAPIOrderModifyReq = {
    "ReqData": "dict",
    "ServerFlag": "char",
    "OrderNo": "string",
}

TapAPIOrderCancelReq = {
    "RefInt": "int",
    "RefString": "string",
    "ServerFlag": "char",
    "OrderNo": "string",
}

TapAPIOrderDeactivateReq = TapAPIOrderCancelReq
TapAPIOrderActivateReq = TapAPIOrderCancelReq
TapAPIOrderDeleteReq = TapAPIOrderCancelReq
TapAPIOrderQryReq = {
    "OrderQryType": "dict",
    "AccountNo": "string",
    "DataSeqID": "unsigned int",
}

TapAPIOrderProcessQryReq = {
    "ServerFlag": "char",
    "OrderNo": "string",
}

TapAPIFillQryReq = {
    "AccountNo": "string",
    "DataSeqID": "unsigned int",
}

TapAPIFillInfo = {
    "AccountNo": "string",
    "ParentAccountNo": "dict",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "ExchangeNoRef": "dict",
    "CommodityTypeRef": "dict",
    "CommodityNoRef": "dict",
    "ContractNoRef": "dict",
    "StrikePriceRef": "dict",
    "CallOrPutFlagRef": "dict",
    "OrderExchangeNo": "dict",
    "OrderCommodityType": "dict",
    "OrderCommodityNo": "dict",
    "OrderType": "dict",
    "MatchSource": "dict",
    "TimeInForce": "dict",
    "ExpireTime": "string",
    "IsRiskOrder": "char",
    "MatchSide": "dict",
    "PositionEffect": "dict",
    "PositionEffectRef": "dict",
    "HedgeFlag": "dict",
    "ServerFlag": "char",
    "OrderNo": "string",
    "OrderLocalNo": "string",
    "MatchNo": "string",
    "ExchangeMatchNo": "string",
    "MatchDateTime": "string",
    "UpperMatchDateTime": "string",
    "UpperNo": "string",
    "UpperChannelNo": "string",
    "UpperSettleNo": "string",
    "UpperUserNo": "string",
    "TradeNo": "string",
    "MatchPrice": "double",
    "MatchQty": "unsigned int",
    "IsBackInput": "char",
    "IsDeleted": "char",
    "IsAddOne": "char",
    "MatchStreamID": "unsigned int",
    "UpperStreamID": "dict",
    "OpenCloseMode": "dict",
    "ContractSize": "double",
    "CommodityCurrencyGroup": "string",
    "CommodityCurrency": "string",
    "FeeMode": "dict",
    "FeeParam": "dict",
    "FeeCurrencyGroup": "string",
    "FeeCurrency": "string",
    "PreSettlePrice": "double",
    "FeeValue": "double",
    "IsManualFee": "char",
    "Turnover": "dict",
    "PremiumIncome": "double",
    "PremiumPay": "double",
    "OppoMatchNo": "dict",
    "CloseProfit": "double",
    "UnExpProfit": "double",
    "UpperMatchPrice": "dict",
    "QuotePrice": "dict",
    "ClosePL": "double",
}

TapAPIPositionQryReq = {
    "AccountNo": "string",
    "DataSeqID": "unsigned int",
}

TapAPIPositionInfo = {
    "AccountNo": "string",
    "ParentAccountNo": "dict",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "ExchangeNoRef": "dict",
    "CommodityTypeRef": "dict",
    "CommodityNoRef": "dict",
    "ContractNoRef": "dict",
    "StrikePriceRef": "dict",
    "CallOrPutFlagRef": "dict",
    "OrderExchangeNo": "dict",
    "OrderCommodityType": "dict",
    "OrderCommodityNo": "dict",
    "OrderType": "dict",
    "TimeInForce": "dict",
    "ExpireTime": "dict",
    "MatchSide": "dict",
    "HedgeFlag": "dict",
    "PositionNo": "string",
    "ServerFlag": "char",
    "OrderNo": "string",
    "MatchNo": "string",
    "ExchangeMatchNo": "string",
    "MatchSource": "dict",
    "MatchDate": "dict",
    "MatchTime": "dict",
    "UpperMatchTime": "dict",
    "UpperNo": "string",
    "UpperSettleNo": "string",
    "UpperUserNo": "string",
    "TradeNo": "string",
    "PositionPrice": "double",
    "PositionQty": "unsigned int",
    "IsBackInput": "char",
    "IsAddOne": "char",
    "MatchStreamID": "unsigned int",
    "PositionStreamId": "unsigned int",
    "OpenCloseMode": "dict",
    "ContractSize": "double",
    "CommodityCurrencyGroup": "string",
    "CommodityCurrency": "string",
    "PreSettlePrice": "double",
    "SettlePrice": "dict",
    "Turnover": "double",
    "AccountMarginMode": "dict",
    "AccountMarginParam": "double",
    "UpperMarginMode": "dict",
    "UpperMarginParam": "dict",
    "AccountInitialMargin": "double",
    "AccountMaintenanceMargin": "double",
    "UpperInitialMargin": "dict",
    "UpperMaintenanceMargin": "dict",
    "PositionProfit": "double",
    "LMEPositionProfit": "double",
    "OptionMarketValue": "double",
    "MatchCmbNo": "string",
    "IsHistory": "char",
    "FloatingPL": "double",
    "CalculatePrice": "double",
}

TapAPIPositionProfit = {
    "PositionNo": "string",
    "PositionStreamId": "unsigned int",
    "PositionProfit": "double",
    "LMEPositionProfit": "double",
    "OptionMarketValue": "double",
    "CalculatePrice": "double",
    "FloatingPL": "double",
}

TapAPIPositionProfitNotice = {
    "IsLast": "char",
    "Data": "dict",
}

TapAPICloseQryReq = {
    "AccountNo": "string",
    "DataSeqID": "unsigned int",
}

TapAPICloseInfo = {
    "AccountNo": "string",
    "ParentAccountNo": "dict",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "OpenOrderExchangeNo": "dict",
    "OpenOrderCommodityType": "dict",
    "OpenOrderCommodityNo": "dict",
    "CloseOrderExchangeNo": "dict",
    "CloseOrderCommodityType": "dict",
    "CloseOrderCommodityNo": "dict",
    "OpenMatchSource": "dict",
    "CloseMatchSource": "dict",
    "CloseSide": "dict",
    "CloseQty": "unsigned int",
    "OpenPrice": "double",
    "ClosePrice": "double",
    "OpenServerFlag": "char",
    "OpenOrderNo": "string",
    "OpenMatchNo": "string",
    "OpenExchangeMatchNo": "string",
    "OpenMatchDateTime": "string",
    "CloseServerFlag": "char",
    "CloseOrderNo": "string",
    "CloseMatchNo": "string",
    "CloseExchangeMatchNo": "string",
    "CloseMatchDateTime": "string",
    "CloseStreamId": "unsigned int",
    "OpenCloseMode": "dict",
    "ContractSize": "double",
    "CommodityCurrencyGroup": "dict",
    "CommodityCurrency": "dict",
    "PreSettlePrice": "double",
    "PremiumIncome": "dict",
    "PremiumPay": "dict",
    "CloseProfit": "double",
    "UnExpProfit": "double",
    "ClosePL": "double",
}

TapAPIFundReq = {
    "AccountNo": "string",
    "DataSeqID": "unsigned int",
}

TapAPIFundData = {
    "AccountNo": "string",
    "ParentAccountNo": "dict",
    "CurrencyGroupNo": "string",
    "CurrencyNo": "string",
    "TradeRate": "double",
    "FutureAlg": "dict",
    "OptionAlg": "dict",
    "PreBalance": "double",
    "PreUnExpProfit": "double",
    "PreLMEPositionProfit": "double",
    "PreEquity": "double",
    "PreAvailable1": "double",
    "PreMarketEquity": "double",
    "CashInValue": "double",
    "CashOutValue": "double",
    "CashAdjustValue": "double",
    "CashPledged": "double",
    "FrozenFee": "double",
    "FrozenDeposit": "double",
    "AccountFee": "double",
    "ExchangeFee": "double",
    "AccountDeliveryFee": "double",
    "PremiumIncome": "double",
    "PremiumPay": "double",
    "CloseProfit": "double",
    "DeliveryProfit": "double",
    "UnExpProfit": "double",
    "ExpProfit": "double",
    "PositionProfit": "double",
    "LmePositionProfit": "double",
    "OptionMarketValue": "double",
    "AccountInitialMargin": "double",
    "AccountMaintenanceMargin": "double",
    "UpperInitialMargin": "double",
    "UpperMaintenanceMargin": "double",
    "Discount": "double",
    "Balance": "double",
    "Equity": "double",
    "Available": "double",
    "CanDraw": "double",
    "MarketEquity": "double",
    "AuthMoney": "double",
    "OriginalCashInOut": "double",
    "FloatingPL": "double",
    "FrozenRiskFundValue": "double",
    "ClosePL": "double",
    "NoCurrencyPledgeValue": "double",
    "PrePledgeValue": "double",
    "PledgeIn": "double",
    "PledgeOut": "double",
    "PledgeValue": "double",
    "BorrowValue": "double",
    "SpecialAccountFrozenMargin": "double",
    "SpecialAccountMargin": "double",
    "SpecialAccountFrozenFee": "double",
    "SpecialAccountFee": "double",
    "SpecialFloatProfit": "double",
    "SpecialCloseProfit": "double",
    "SpecialFloatPL": "double",
    "SpecialClosePL": "double",
    "RiskRate": "double",
}

TapAPIReqQuoteNotice = {
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "InquiryNo": "string",
    "UpdateTime": "string",
}

TapAPIDeepQuoteInfo = {
    "Side": "dict",
    "Price": "double",
    "Qty": "unsigned int",
}

TapAPIDeepQuoteQryRsp = {
    "Contract": "dict",
    "DeepQuote": "dict",
}

TapAPIExchangeStateInfoQryReq = {
}

TapAPIExchangeStateInfo = {
    "UpperChannelNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ExchangeTime": "string",
    "TradingState": "dict",
}

TapAPIExchangeStateInfoNotice = {
    "IsLast": "char",
    "ExchangeStateInfo": "dict",
}

TapAPIUpperChannelQryReq = {
}

TapAPIUpperChannelInfo = {
    "UpperChannelNo": "string",
    "UpperChannelName": "string",
    "UpperNo": "string",
    "UpperUserNo": "string",
}

TapAPIAccountRentQryReq = {
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
}

TapAPIAccountRentInfo = {
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "MatchSource": "dict",
    "CurrencyNo": "string",
    "FeeMode": "dict",
    "OpenTurnover": "double",
    "ClosedTurnover": "double",
    "CloseNewTurnover": "double",
    "OpenVolume": "double",
    "ClosedVolume": "double",
    "CloseNewVolume": "double",
    "MarginMode": "dict",
    "BuyTInitMargin": "double",
    "SellTInitMargin": "double",
    "BuyBInitMargin": "double",
    "SellBInitMargin": "double",
    "BuyLInitMargin": "double",
    "SellLInitMargin": "double",
    "BuyMInitMargin": "double",
    "SellMInitMargin": "double",
    "BuyTMaintMargin": "double",
    "SellTMaintMargin": "double",
    "BuyBMaintMargin": "double",
    "SellBMaintMargin": "double",
    "BuyLMaintMargin": "double",
    "SellLMaintMargin": "double",
    "BuyMMaintMargin": "double",
    "SellMMaintMargin": "double",
}

TapAPICurrencyInfo = {
    "CurrencyNo": "string",
    "CurrencyGroupNo": "string",
    "TradeRate": "double",
    "TradeRate2": "double",
    "FutureAlg": "dict",
    "OptionAlg": "dict",
}

TapAPITradeMessageQryReq = {
    "SerialID": "unsigned int",
    "TradeMsgQryType": "dict",
    "AccountNo": "string",
    "BeginSendDateTime": "string",
    "EndSendDateTime": "string",
}

TapAPITradeMessage = {
    "SerialID": "unsigned int",
    "AccountNo": "string",
    "TMsgValidDateTime": "string",
    "TMsgTitle": "string",
    "TMsgContent": "string",
    "TMsgType": "dict",
    "TMsgLevel": "dict",
    "IsSendBySMS": "char",
    "IsSendByEMail": "char",
    "Sender": "string",
    "SendDateTime": "string",
}

TapAPIAccountCashAdjustQryReq = {
    "SerialID": "unsigned int",
    "AccountNo": "string",
    "AccountAttributeNo": "string",
    "BeginDate": "string",
    "EndDate": "string",
}

TapAPIAccountCashAdjustQryRsp = {
    "Date": "string",
    "AccountNo": "string",
    "CashAdjustType": "dict",
    "CurrencyGroupNo": "string",
    "CurrencyNo": "string",
    "CashAdjustValue": "double",
    "CashAdjustRemark": "string",
    "OperateTime": "string",
    "OperatorNo": "string",
    "AccountBank": "string",
    "BankAccount": "string",
    "AccountLWFlag": "dict",
    "CompanyBank": "string",
    "InternalBankAccount": "string",
    "CompanyLWFlag": "dict",
}

TapAPIBillQryReq = {
    "UserNo": "string",
    "BillType": "dict",
    "BillDate": "string",
    "BillFileType": "dict",
}

TapAPIBillQryRsp = {
    "Reqdata": "dict",
    "BillLen": "int",
    "BillText": "char",
}

TapAPIHisOrderQryReq = {
    "AccountNo": "string",
    "AccountAttributeNo": "string",
    "BeginDate": "string",
    "EndDate": "string",
}

TapAPIHisOrderQryRsp = {
    "Date": "string",
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "ContractNo2": "string",
    "StrikePrice2": "string",
    "CallOrPutFlag2": "char",
    "OrderType": "dict",
    "OrderSource": "dict",
    "TimeInForce": "dict",
    "ExpireTime": "string",
    "IsRiskOrder": "char",
    "OrderSide": "dict",
    "PositionEffect": "dict",
    "PositionEffect2": "dict",
    "InquiryNo": "string",
    "HedgeFlag": "dict",
    "OrderPrice": "double",
    "OrderPrice2": "double",
    "StopPrice": "double",
    "OrderQty": "unsigned int",
    "OrderMinQty": "unsigned int",
    "OrderCanceledQty": "unsigned int",
    "RefInt": "int",
    "RefDouble": "double",
    "RefString": "string",
    "ServerFlag": "char",
    "OrderNo": "string",
    "OrderStreamID": "unsigned int",
    "UpperNo": "string",
    "UpperChannelNo": "string",
    "OrderLocalNo": "string",
    "UpperStreamID": "unsigned int",
    "OrderSystemNo": "string",
    "OrderExchangeSystemNo": "string",
    "OrderParentSystemNo": "string",
    "OrderInsertUserNo": "string",
    "OrderInsertTime": "string",
    "OrderCommandUserNo": "string",
    "OrderUpdateUserNo": "string",
    "OrderUpdateTime": "string",
    "OrderState": "dict",
    "OrderMatchPrice": "double",
    "OrderMatchPrice2": "double",
    "OrderMatchQty": "unsigned int",
    "OrderMatchQty2": "unsigned int",
    "ErrorCode": "unsigned int",
    "ErrorText": "string",
    "IsBackInput": "char",
    "IsDeleted": "char",
    "IsAddOne": "char",
    "AddOneIsValid": "char",
    "MinClipSize": "unsigned int",
    "MaxClipSize": "unsigned int",
    "LicenseNo": "string",
    "TacticsType": "dict",
    "TriggerCondition": "dict",
    "TriggerPriceType": "dict",
}

TapAPIHisFillQryReq = {
    "AccountNo": "string",
    "AccountAttributeNo": "string",
    "BeginDate": "string",
    "EndDate": "string",
    "CountType": "char",
}

TapAPIHisFillQryRsp = {
    "SettleDate": "string",
    "TradeDate": "string",
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "MatchSource": "dict",
    "MatchSide": "dict",
    "PositionEffect": "dict",
    "HedgeFlag": "dict",
    "MatchPrice": "double",
    "MatchQty": "unsigned int",
    "OrderNo": "string",
    "MatchNo": "string",
    "MatchStreamID": "unsigned int",
    "UpperNo": "string",
    "MatchCmbNo": "string",
    "ExchangeMatchNo": "string",
    "MatchUpperStreamID": "unsigned int",
    "CommodityCurrencyGroup": "string",
    "CommodityCurrency": "string",
    "Turnover": "double",
    "PremiumIncome": "double",
    "PremiumPay": "double",
    "AccountFee": "double",
    "AccountFeeCurrencyGroup": "string",
    "AccountFeeCurrency": "string",
    "IsManualFee": "char",
    "AccountOtherFee": "double",
    "UpperFee": "double",
    "UpperFeeCurrencyGroup": "string",
    "UpperFeeCurrency": "string",
    "IsUpperManualFee": "char",
    "UpperOtherFee": "double",
    "MatchDateTime": "string",
    "UpperMatchDateTime": "string",
    "CloseProfit": "double",
    "ClosePrice": "double",
    "CloseQty": "unsigned int",
    "SettleGroupNo": "string",
    "OperatorNo": "string",
    "OperateTime": "string",
}

TapAPIHisOrderProcessQryReq = {
    "Date": "string",
    "OrderNo": "string",
}

TapAPIHisOrderProcessQryRsp = TapAPIHisOrderQryRsp
TapAPIHisPositionQryReq = {
    "AccountNo": "string",
    "AccountAttributeNo": "string",
    "Date": "string",
    "CountType": "char",
}

TapAPIHisPositionQryRsp = {
    "SettleDate": "string",
    "OpenDate": "string",
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "MatchSide": "dict",
    "HedgeFlag": "dict",
    "PositionPrice": "double",
    "PositionQty": "unsigned int",
    "OrderNo": "string",
    "PositionNo": "string",
    "UpperNo": "string",
    "CurrencyGroup": "string",
    "Currency": "string",
    "PreSettlePrice": "double",
    "SettlePrice": "double",
    "PositionDProfit": "double",
    "LMEPositionProfit": "double",
    "OptionMarketValue": "double",
    "AccountInitialMargin": "double",
    "AccountMaintenanceMargin": "double",
    "UpperInitialMargin": "double",
    "UpperMaintenanceMargin": "double",
    "SettleGroupNo": "string",
}

TapAPIHisDeliveryQryReq = {
    "AccountNo": "string",
    "AccountAttributeNo": "string",
    "BeginDate": "string",
    "EndDate": "string",
    "CountType": "char",
}

TapAPIHisDeliveryQryRsp = {
    "DeliveryDate": "string",
    "OpenDate": "string",
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "MatchSource": "dict",
    "OpenSide": "dict",
    "OpenPrice": "double",
    "DeliveryPrice": "double",
    "DeliveryQty": "unsigned int",
    "FrozenQty": "unsigned int",
    "OpenNo": "string",
    "UpperNo": "string",
    "CommodityCurrencyGroupy": "string",
    "CommodityCurrency": "string",
    "PreSettlePrice": "double",
    "DeliveryProfit": "double",
    "AccountFrozenInitialMargin": "double",
    "AccountFrozenMaintenanceMargin": "double",
    "UpperFrozenInitialMargin": "double",
    "UpperFrozenMaintenanceMargin": "double",
    "AccountFeeCurrencyGroup": "string",
    "AccountFeeCurrency": "string",
    "AccountDeliveryFee": "double",
    "UpperFeeCurrencyGroup": "string",
    "UpperFeeCurrency": "string",
    "UpperDeliveryFee": "double",
    "DeliveryMode": "dict",
    "OperatorNo": "string",
    "OperateTime": "string",
    "SettleGourpNo": "string",
}

TapAPIAccountFeeRentQryReq = {
    "AccountNo": "string",
}

TapAPIAccountFeeRentQryRsp = {
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "MatchSource": "dict",
    "CalculateMode": "dict",
    "CurrencyGroupNo": "string",
    "CurrencyNo": "string",
    "OpenCloseFee": "double",
    "CloseTodayFee": "double",
}

TapAPIAccountMarginRentQryReq = {
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
}

TapAPIAccountMarginRentQryRsp = {
    "AccountNo": "string",
    "ExchangeNo": "string",
    "CommodityType": "char",
    "CommodityNo": "string",
    "ContractNo": "string",
    "StrikePrice": "string",
    "CallOrPutFlag": "char",
    "CalculateMode": "dict",
    "CurrencyGroupNo": "string",
    "CurrencyNo": "string",
    "InitialMargin": "double",
    "MaintenanceMargin": "double",
    "SellInitialMargin": "double",
    "SellMaintenanceMargin": "double",
    "LockMargin": "double",
}

TapAPISecondInfo = {
    "SendType": "dict",
    "SendAccount": "string",
}

TapAPIVertificateCode = {
    "SecondSerialID": "string",
    "Effective": "int",
}

TapAPIMobileDeviceAddReq = {
    "UserNo": "string",
    "AppKey": "string",
    "AppID": "string",
    "MasterSecret": "string",
    "Cid": "string",
    "CompanyNo": "string",
    "CompanyAddressNo": "string",
    "DeviceType": "dict",
}

TapAPIMobileDeviceAddRsp = TapAPIMobileDeviceAddReq
TapAPIManageInfoQryReq = {
    "BeginDate": "string",
    "EndDate": "string",
}

TapAPIManageInfo = {
    "MsgID": "unsigned int",
    "SendFrom": "string",
    "SendManageType": "char",
    "AccountNo": "string",
    "SendAccount": "string",
    "Title": "string",
    "Content": "string",
    "Attachment": "string",
    "SendStatus": "char",
    "Remark": "string",
    "GUID": "string",
    "OperatorNo": "string",
    "OperateTime": "string",
}

TapAPISystemParameterQryReq = {
}

TapAPISystemParameterInfo = {
    "ItemNo": "string",
    "ExchangeNo": "string",
    "CommodityNo": "string",
    "CommodityType": "char",
    "ItemValue": "int",
    "ItemValueStr": "string",
    "ItemValueDouble": "double",
}

TapAPITradeCenterFrontAddressQryReq = {
    "FrontAddress": "string",
    "FrontPort": "string",
    "TradeCenter": "char",
    "IsSSL": "char",
}

TapAPITradeCenterFrontAddressInfo = {
    "FrontName": "string",
    "FrontAddress": "string",
    "FrontPort": "string",
    "TradeCenter": "char",
    "IsEnable": "char",
    "IsSSL": "char",
}


