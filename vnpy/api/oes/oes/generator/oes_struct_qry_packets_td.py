OesQryCursorT = {
    "seqNo": "int32",
    "isEnd": "int8",
    "__filler": "int8",
    "userInfo": "int64",
}
OesQryReqHeadT = {
    "maxPageSize": "int32",
    "lastPosition": "int32",
}
OesQryRspHeadT = {
    "itemCount": "int32",
    "lastPosition": "int32",
    "isEnd": "int8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryOrdFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "mktId": "uint8",
    "isUnclosedOnly": "uint8",
    "clEnvId": "int8",
    "securityType": "uint8",
    "bsType": "uint8",
    "__filler": "uint8",
    "clOrdId": "int64",
    "clSeqNo": "int64",
    "startTime": "int32",
    "endTime": "int32",
    "userInfo": "int64",
}
OesQryOrdReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryOrdFilterT",
}
OesQryOrdRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesOrdItemT",
}
OesQryTrdFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "mktId": "uint8",
    "clEnvId": "int8",
    "securityType": "uint8",
    "bsType": "uint8",
    "__filler": "uint32",
    "clOrdId": "int64",
    "clSeqNo": "int64",
    "startTime": "int32",
    "endTime": "int32",
    "userInfo": "int64",
}
OesQryTrdReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryTrdFilterT",
}
OesQryTrdRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesTrdItemT",
}
OesQryCashAssetFilterT = {
    "custId": "string",
    "cashAcctId": "string",
    "userInfo": "int64",
}
OesCashAssetItemT = {
    "__OES_CASH_ASSET_BASE_INFO_PKT": "dict",
    "__OES_CASH_ASSET_EXT_INFO_PKT": "dict",
}
OesQryCashAssetReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryCashAssetFilterT",
}
OesQryCashAssetRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesCashAssetItemT",
}
OesCounterCashItemT = {
    "cashAcctId": "string",
    "custId": "string",
    "custName": "string",
    "bankId": "string",
}
OesQryCounterCashReqT = {
    "cashAcctId": "string",
}
OesQryCounterCashRspT = {
    "counterCashItem": "OesCounterCashItemT",
}
OesQryStkHoldingFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "securityId": "string",
    "mktId": "uint8",
    "securityType": "uint8",
    "productType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesStkHoldingItemT = {
    "__OES_STK_HOLDING_BASE_INFO_PKT": "dict",
    "__OES_STK_HOLDING_EXT_INFO_PKT": "dict",
}
OesQryStkHoldingReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryStkHoldingFilterT",
}
OesQryStkHoldingRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesStkHoldingItemT",
}
OesQryOptHoldingFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "securityId": "string",
    "mktId": "uint8",
    "positionType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesOptHoldingItemT = {
    "__OES_OPT_HOLDING_BASE_INFO_PKT": "dict",
    "__OES_OPT_HOLDING_EXT_INFO_PKT": "dict",
    "contractId": "string",
    "contractSymbol": "string",
    "prevSettlPrice": "int64",
}
OesQryOptHoldingReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryOptHoldingFilterT",
}
OesQryOptHoldingRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesOptHoldingItemT",
}
OesQryCustFilterT = {
    "custId": "string",
    "userInfo": "int64",
}
OesQryCustReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryCustFilterT",
}
OesQryCustRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesCustItemT",
}
OesQryInvAcctFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "mktId": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesInvAcctItemT = {
    "__OES_INV_ACCT_BASE_INFO_PKT": "dict",
    "custId": "string",
}
OesQryInvAcctReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryInvAcctFilterT",
}
OesQryInvAcctRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesInvAcctItemT",
}
OesInvAcctOverviewT = {
    "invAcctId": "string",
    "mktId": "uint8",
    "acctType": "uint8",
    "status": "uint8",
    "ownerType": "uint8",
    "optInvLevel": "uint8",
    "isTradeDisabled": "uint8",
    "__INV_ACCT_BASE_filler": "uint8",
    "limits": "uint64",
    "permissions": "uint64",
    "pbuId": "int32",
    "subscriptionQuota": "int32",
    "custId": "string",
}
OesCashAcctOverviewT = {
    "cashAcctId": "string",
    "custId": "string",
    "bankId": "string",
}
OesCustOverviewT = {
    "__OES_CUST_BASE_INFO_PKT": "dict",
    "custName": "string",
}
OesClientOverviewT = {
    "clientName": "string",
    "clientMemo": "string",
    "custItems": "OesCustOverviewT",
}
OesQryCommissionRateFilterT = {
    "custId": "string",
    "mktId": "uint8",
    "securityType": "uint8",
    "bsType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesCommissionRateItemT = {
    "custId": "string",
    "securityId": "string",
    "mktId": "uint8",
    "securityType": "uint8",
    "subSecurityType": "uint8",
    "bsType": "uint8",
    "feeType": "uint8",
    "currType": "uint8",
    "calcFeeMode": "uint8",
    "__filler": "uint8",
    "feeRate": "int64",
    "minFee": "int32",
    "maxFee": "int32",
}
OesQryCommissionRateReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryCommissionRateFilterT",
}
OesQryCommissionRateRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesCommissionRateItemT",
}
OesQryFundTransferSerialFilterT = {
    "custId": "string",
    "cashAcctId": "string",
    "clSeqNo": "int32",
    "clEnvId": "int8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryFundTransferSerialReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryFundTransferSerialFilterT",
}
OesQryFundTransferSerialRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesFundTransferSerialItemT",
}
OesQryLotWinningFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "mktId": "uint8",
    "lotType": "uint8",
    "__filler": "uint8",
    "startDate": "int32",
    "endDate": "int32",
    "userInfo": "int64",
}
OesQryLotWinningReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryLotWinningFilterT",
}
OesQryLotWinningRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesLotWinningItemT",
}
OesQryIssueFilterT = {
    "securityId": "string",
    "mktId": "uint8",
    "productType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryIssueReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryIssueFilterT",
}
OesQryIssueRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesIssueItemT",
}
OesQryStockFilterT = {
    "securityId": "string",
    "mktId": "uint8",
    "securityType": "uint8",
    "subSecurityType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryStockReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryStockFilterT",
}
OesQryStockRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesStockItemT",
}
OesQryEtfFilterT = {
    "fundId": "string",
    "mktId": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryEtfReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryEtfFilterT",
}
OesQryEtfRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesEtfItemT",
}
OesQryEtfComponentFilterT = {
    "fundId": "string",
    "userInfo": "int64",
}
OesEtfComponentItemT = {
    "securityId": "string",
    "mktId": "uint8",
    "subFlag": "uint8",
    "securityType": "uint8",
    "subSecurityType": "uint8",
    "prevClose": "int32",
    "qty": "int32",
    "premiumRate": "int32",
    "creationSubCash": "int64",
    "redemptionCashSub": "int64",
    "fundId": "string",
}
OesQryEtfComponentReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryEtfComponentFilterT",
}
OesQryEtfComponentRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesEtfComponentItemT",
}
OesQryOptionFilterT = {
    "securityId": "string",
    "mktId": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryOptionReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryOptionFilterT",
}
OesQryOptionRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesOptionItemT",
}
OesQryOptUnderlyingHoldingFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "underlyingSecurityId": "string",
    "mktId": "uint8",
    "underlyingSecurityType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryOptUnderlyingHoldingReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryOptUnderlyingHoldingFilterT",
}
OesQryOptUnderlyingHoldingRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesOptUnderlyingHoldingItemT",
}
OesQryOptPositionLimitFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "underlyingSecurityId": "string",
    "mktId": "uint8",
    "underlyingSecurityType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesOptPositionLimitItemT = {
    "invAcctId": "string",
    "underlyingSecurityId": "string",
    "mktId": "uint8",
    "underlyingMktId": "uint8",
    "underlyingSecurityType": "uint8",
    "underlyingSubSecurityType": "uint8",
    "__filler1": "uint8",
    "longPositionLimit": "int32",
    "totalPositionLimit": "int32",
    "dailyBuyOpenLimit": "int32",
    "__filler2": "int32",
    "originalLongQty": "int32",
    "originalShortQty": "int32",
    "originalCoveredQty": "int32",
    "availableLongPositionLimit": "int32",
    "availableTotalPositionLimit": "int32",
    "availableDailyBuyOpenLimit": "int32",
    "__reserve": "string",
}
OesQryOptPositionLimitReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryOptPositionLimitFilterT",
}
OesQryOptPositionLimitRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesOptPositionLimitItemT",
}
OesQryOptPurchaseLimitFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "mktId": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesOptPurchaseLimitItemT = {
    "custId": "string",
    "cashAcctId": "string",
    "invAcctId": "string",
    "mktId": "uint8",
    "custType": "uint8",
    "__filler": "uint8",
    "purchaseLimit": "int64",
    "originalUsedPurchaseAmt": "int64",
    "totalOpenPurchaseAmt": "int64",
    "frzPurchaseAmt": "int64",
    "totalClosePurchaseAmt": "int64",
    "availablePurchaseLimit": "int64",
}
OesQryOptPurchaseLimitReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryOptPurchaseLimitFilterT",
}
OesQryOptPurchaseLimitRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesOptPurchaseLimitItemT",
}
OesQryOptExerciseAssignFilterT = {
    "custId": "string",
    "invAcctId": "string",
    "securityId": "string",
    "mktId": "uint8",
    "positionType": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryOptExerciseAssignReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryOptExerciseAssignFilterT",
}
OesQryOptExerciseAssignRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesOptExerciseAssignItemT",
}
OesQryTradingDayRspT = {
    "tradingDay": "int32",
    "__filler": "int32",
}
OesQryMarketStateFilterT = {
    "exchId": "uint8",
    "platformId": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryMarketStateReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryMarketStateFilterT",
}
OesQryMarketStateRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesMarketStateItemT",
}
OesQryNotifyInfoFilterT = {
    "custId": "string",
    "notifyLevel": "uint8",
    "__filler": "uint8",
    "userInfo": "int64",
}
OesQryNotifyInfoReqT = {
    "reqHead": "OesQryReqHeadT",
    "qryFilter": "OesQryNotifyInfoFilterT",
}
OesBrokerParamsInfoT = {
    "brokerName": "string",
    "brokerPhone": "string",
    "brokerWebsite": "string",
    "apiVersion": "string",
    "apiMinVersion": "string",
    "clientVersion": "string",
    "changePwdLimitTime": "int32",
    "minClientPasswordLen": "int32",
    "clientPasswordStrength": "int32",
    "businessScope": "uint32",
    "__reserve": "string",
}
OesQryBrokerParamsInfoRspT = {
    "brokerParams": "OesBrokerParamsInfoT",
}
OesQryNotifyInfoRspT = {
    "rspHead": "OesQryRspHeadT",
    "qryItems": "OesNotifyInfoItemT",
}
