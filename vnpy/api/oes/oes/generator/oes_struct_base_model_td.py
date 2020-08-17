OesOrdReqT = {
    "__OES_ORD_BASE_INFO_PKT": "dict",
    "__OES_ORD_REQ_LATENCY_FIELDS": "dict",
}
OesOrdCancelReqT = {
    "__OES_ORD_CANCEL_BASE_INFO_PKT": "dict",
    "__OES_ORD_REQ_LATENCY_FIELDS": "dict",
}
OesOrdRejectT = {
    "__OES_ORD_BASE_INFO_PKT": "dict",
    "__OES_ORD_REQ_LATENCY_FIELDS": "dict",
    "origClSeqNo": "int32",
    "origClEnvId": "int8",
    "clEnvId": "int8",
    "clientId": "int16",
    "ordDate": "int32",
    "ordTime": "int32",
    "ordRejReason": "int32",
    "__filler": "int32",
}
OesOrdCnfmT = {
    "__OES_ORD_CNFM_BASE_INFO_PKT": "dict",
    "__OES_ORD_CNFM_EXT_INFO_PKT": "dict",
}
OesTrdBaseInfoT = {
    "__OES_TRD_BASE_INFO_PKT": "dict",
}
OesTrdCnfmT = {
    "__OES_TRD_CNFM_BASE_INFO_PKT": "dict",
    "__OES_TRD_CNFM_EXT_INFO_PKT": "dict",
}
OesLotWinningBaseInfoT = {
    "__OES_LOT_WINNING_BASE_INFO_PKT": "dict",
}
OesFundTrsfBaseInfoT = {
    "__OES_FUND_TRSF_BASE_INFO_PKT": "dict",
}
OesFundTrsfReqT = {
    "__OES_FUND_TRSF_BASE_INFO_PKT": "dict",
}
OesFundTrsfRejectT = {
    "__OES_FUND_TRSF_BASE_INFO_PKT": "dict",
    "ordDate": "int32",
    "ordTime": "int32",
    "clientId": "int16",
    "clEnvId": "int8",
    "__filler": "int8",
    "rejReason": "int32",
    "errorInfo": "string",
}
OesFundTrsfReportT = {
    "clSeqNo": "int32",
    "clientId": "int16",
    "clEnvId": "int8",
    "direct": "uint8",
    "cashAcctId": "string",
    "occurAmt": "int64",
}
OesIssueBaseInfoT = {
    "__OES_ISSUE_BASE_INFO_PKT": "dict",
}
OesPriceLimitT = {
    "upperLimitPrice": "int32",
    "ceilPrice": "int32",
}
OesStockBaseInfoT = {
    "__OES_STOCK_BASE_INFO_PKT": "dict",
}
OesEtfBaseInfoT = {
    "__OES_ETF_BASE_INFO_PKT": "dict",
}
OesEtfComponentBaseInfoT = {
    "__OES_ETF_COMPONENT_BASE_INFO_PKT": "dict",
}
OesCashAssetBaseInfoT = {
    "__OES_CASH_ASSET_BASE_INFO_PKT": "dict",
}
OesCashAssetReportT = {
    "__OES_CASH_ASSET_BASE_INFO_PKT": "dict",
    "__OES_CASH_ASSET_EXT_INFO_PKT": "dict",
}
OesCustBaseInfoT = {
    "__OES_CUST_BASE_INFO_PKT": "dict",
}
OesInvAcctBaseInfoT = {
    "__OES_INV_ACCT_BASE_INFO_PKT": "dict",
}
OesStkHoldingBaseInfoT = {
    "__OES_STK_HOLDING_BASE_INFO_PKT": "dict",
}
OesStkHoldingReportT = {
    "__OES_STK_HOLDING_BASE_INFO_PKT": "dict",
    "__OES_STK_HOLDING_EXT_INFO_PKT": "dict",
}
OesMarketStateInfoT = {
}
OesNotifyBaseInfoT = {
    "__OES_NOTIFY_BASE_INFO_PKT": "dict",
}
OesNotifyInfoReportT = {
    "__OES_NOTIFY_BASE_INFO_PKT": "dict",
}
OesOptionBaseInfoT = {
    "__OES_OPTION_BASE_INFO_PKT": "dict",
}
OesOptHoldingBaseInfoT = {
    "__OES_OPT_HOLDING_BASE_INFO_PKT": "dict",
}
OesOptHoldingReportT = {
    "__OES_OPT_HOLDING_BASE_INFO_PKT": "dict",
    "__OES_OPT_HOLDING_EXT_INFO_PKT": "dict",
}
OesOptUnderlyingHoldingBaseInfoT = {
    "__OES_OPT_UNDERLYING_HOLDING_BASE_PKT": "dict",
}
OesOptUnderlyingHoldingReportT = {
    "__OES_OPT_UNDERLYING_HOLDING_BASE_PKT": "dict",
}
OesOptionPositionLimitBaseInfoT = {
    "__OES_OPTION_POSITION_LIMIT_BASE_PKT": "dict",
}
OesOptionExerciseAssignBaseT = {
    "__OES_OPTION_EXERCISE_ASSIGN_BASE_PKT": "dict",
}
OesOptSettlementConfirmBaseInfoT = {
    "__OES_OPT_SETTLEMENT_CONFIRM_BASE_PKT": "dict",
}
OesOptSettlementConfirmReportT = {
    "__OES_OPT_SETTLEMENT_CONFIRM_BASE_PKT": "dict",
}
