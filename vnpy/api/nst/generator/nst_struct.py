tagExchange_Type = {
    "EXCHANGE_CFFEX": "int",
    "EXCHANGE_SHFE": "int",
    "EXCHANGE_DCE": "int",
    "EXCHANGE_SSEOPT": "int",
    "EXCHANGE_CZCE": "int",
    "EXCHANGE_SZSE": "int",
    "EXCHANGE_SSE": "int",
    "EXCHANGE_UNKNOWN": "int",
}

tagUftFtdcInputOrderField = {
    "OrderSysID": "string",
    "ParticipantID": "string",
    "ClientID": "string",
    "UserID": "string",
    "InstrumentID": "string",
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
    "OrderLocalID": "string",
    "IsAutoSuspend": "int",
    "BusinessUnit": "string",
}

tagUftQryInvestorPositionField = {
    "futu_code": "string",
    "entrust_bs": "char",
    "OldEnableAmount": "int32_t",
    "OldCurrentAmount": "int32_t",
    "TodayEnableAmount": "int32_t",
    "TodayCurrentAmount": "int32_t",
    "OldOpenBalance": "double",
    "TodayOpenBalance": "double",
    "HoldMargin": "double",
}

tagUftReqOrderInsertField = {
    "Order": "dict",
    "OrderRef": "dict",
    "MaginCheck": "dict",
}

tagUftAnsOrderInsertField = {
    "OrderRef": "dict",
    "OrderIndex": "dict",
    "ProcessTime": "dict",
    "TotalTime": "dict",
    "ExchangeTime": "dict",
    "SenderID": "dict",
    "LocalTimeDelay": "dict",
    "StockCode": "string",
    "Direction": "char",
    "EntrustType": "char",
    "Price": "dict",
    "Amount": "int32_t",
}

tagUftRspnOrderInsertField = {
    "OrderRef": "dict",
    "OrderIndex": "dict",
    "ProcessTime": "dict",
    "TotalTime": "dict",
    "ExchangeTime": "dict",
    "OrderSysID": "string",
    "OrderStatus": "char",
}

tagUftAnsOrderActionField = {
    "OrderRef": "dict",
    "OrderIndex": "dict",
    "OrderSysID": "string",
    "OrderLocalID": "string",
    "SenderID": "dict",
}

tagUftRspnOrderActionField = {
    "OrderSysID": "string",
    "OrderLocalID": "string",
    "OrderRef": "dict",
    "OrderIndex": "dict",
}

tagUftRtnnOrderField = {
    "OrderRef": "dict",
    "OrderIndex": "dict",
    "ProcessTime": "dict",
    "TotalTime": "dict",
    "ExchangeTime": "dict",
    "OrderSysID": "string",
    "VolumeTotal": "int",
    "OrderStatus": "char",
    "StockCode": "string",
    "EntrustType": "char",
    "Direction": "char",
    "Price": "dict",
    "Amount": "int32_t",
}

tagUftRtnnTradeField = {
    "BusinessPrice": "double",
    "BusinessTime": "int32_t",
    "BusinessAmount": "int32_t",
    "fare": "dict",
    "OrderRef": "dict",
    "OrderIndex": "dict",
    "BusinessId": "string",
    "OrderSysID": "dict",
    "session_id": "dict",
    "Direction": "char",
    "OffsetFlag": "char",
    "HedgeFlag": "char",
    "reserve": "string",
    "InstrumentID": "string",
    "StockCode": "string",
}

tagUftAnsQueryFundField = {
    "EnabledBalance": "double",
    "Deposit": "double",
    "BeginBalance": "double",
    "Margin": "double",
    "Profit": "double",
    "TotalFare": "dict",
    "CurrBalance": "dict",
    "floating_gain_loss": "dict",
    "FrozenBalance": "dict",
    "SenderID": "dict",
    "EnablePurQuota": "dict",
}

tagUftReqQueryOrderField = {
    "InstrumentID": "string",
    "BeginTime": "int32_t",
    "EndTime": "int32_t",
    "OrderSysID": "string",
    "OrderIndex": "dict",
    "EntrustSenderID": "dict",
    "OrderRef": "dict",
    "Position": "dict",
    "all_session_data": "dict",
}

tagUftAnsQueryOrderField = {
    "Order": "dict",
    "OrderRef": "dict",
    "MaginCheck": "char",
    "VolumeTotal": "int32_t",
    "OrderStatus": "char",
    "session_id": "dict",
    "reserve": "dict",
    "OrderTime": "int32_t",
    "SenderID": "dict",
    "ErrorID": "int32_t",
    "OrderIndex": "dict",
    "StockCode": "string",
    "Direction": "char",
    "EntrustType": "char",
    "CashMargin": "char",
    "TGWNo": "dict",
    "Price": "dict",
    "Amount": "dict",
    "OrderSysID": "string",
    "ClOrdID": "string",
}

tagUftReqQueryTradeField = {
    "InstrumentID": "string",
    "BeginTime": "int32_t",
    "EndTime": "int32_t",
    "OrderSysID": "string",
    "OrderIndex": "dict",
    "OrderRef": "dict",
    "Position": "dict",
    "all_session_data": "dict",
}

tagUftAnsQueryTradeField = {
    "BusinessPrice": "double",
    "BusinessTime": "int32_t",
    "BusinessAmount": "int32_t",
    "fare": "dict",
    "OrderRef": "dict",
    "OrderIndex": "dict",
    "BusinessId": "string",
    "OrderSysID": "string",
    "session_id": "dict",
    "Direction": "char",
    "OffsetFlag": "char",
    "StockCode": "string",
}

tagUftReqQueryPositionField = {
    "InstrumentID": "string",
}

tagUftAnsQueryPositionField = {
    "futu_code": "string",
    "entrust_bs": "char",
    "HedgeFlag": "char",
    "reserve": "string",
    "OldEnableAmount": "int32_t",
    "OldCurrentAmount": "int32_t",
    "TodayEnableAmount": "int32_t",
    "TodayCurrentAmount": "int32_t",
    "OldOpenBalance": "double",
    "TodayOpenBalance": "double",
    "HoldMargin": "double",
    "StockCode": "string",
    "EnableAmount": "dict",
    "CurrentAmount": "dict",
}

tagUftRspErrorField = {
    "ErrorNo": "int32_t",
    "OrderIndex": "dict",
    "OrderRef": "dict",
    "ErrorMsg": "string",
    "SendID": "dict",
}

tagUftRtnInstrumentStatusField = {
    "SettlementGroupID": "string",
    "InstrumentID": "string",
    "Status": "char",
    "TradingSegmentSN": "int",
    "EnterTime": "string",
    "EnterReason": "char",
    "PlatformID": "dict",
    "PlatformState": "dict",
}

tagUftRspTest = {
    "TimeDelay": "int32_t",
}

tagUftRspUserLoginField = {
    "MaxOrderRef": "uint64_t",
    "TradeDate": "int",
}

tagUftRspInfoField = {
    "ErrorID": "int",
    "ErrorMsg": "string",
}

E_EXCHANGE_TYPE = tagExchange_Type
CUftFtdcInputOrderField = tagUftFtdcInputOrderField
CUftQryInvestorPositionField = tagUftQryInvestorPositionField
CUftReqOrderInsertField = tagUftReqOrderInsertField
CUftAnsOrderInsertField = tagUftAnsOrderInsertField
CUftRspnOrderInsertField = tagUftRspnOrderInsertField
CUftAnsOrderActionField = tagUftAnsOrderActionField
CUftRspnOrderActionField = tagUftRspnOrderActionField
CUftRtnnOrderField = tagUftRtnnOrderField
CUftRtnnTradeField = tagUftRtnnTradeField
CUftAnsQueryFundField = tagUftAnsQueryFundField
QryInvestorPositionField = tagUftReqQueryOrderField
CUftAnsQueryOrderField = tagUftAnsQueryOrderField
CUftReqQueryTradeField = tagUftReqQueryTradeField
CUftAnsQueryTradeField = tagUftAnsQueryTradeField
CUftReqQueryPositionField = tagUftReqQueryPositionField
CUftAnsQueryPositionField = tagUftAnsQueryPositionField
CUftRspErrorField = tagUftRspErrorField
CUftRtnInstrumentStatusField = tagUftRtnInstrumentStatusField
CUftRspTest = tagUftRspTest
CUftRspUserLoginField = tagUftRspUserLoginField
CUftRspInfoField = tagUftRspInfoField
