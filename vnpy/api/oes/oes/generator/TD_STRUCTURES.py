OesCashAssetBaseInfoT : {'cashAcctId': 'string', 'custId': 'string', 'currType': 'uint8', 'cashType': 'uint8', 'cashAcctStatus': 'uint8', 'isFundTrsfDisabled': 'uint8', '__CASH_ASSET_BASE_filler': 'uint8', 'beginningBal': 'int64', 'beginningAvailableBal': 'int64', 'beginningDrawableBal': 'int64', 'disableBal': 'int64', 'reversalAmt': 'int64', 'manualFrzAmt': 'int64', 'totalDepositAmt': 'int64', 'totalWithdrawAmt': 'int64', 'withdrawFrzAmt': 'int64', 'totalSellAmt': 'int64', 'totalBuyAmt': 'int64', 'buyFrzAmt': 'int64','totalFeeAmt': 'int64', 'feeFrzAmt': 'int64', 'marginAmt': 'int64', 'marginFrzAmt': 'int64'}
OesCashAssetReportT : {'cashAcctId': 'string', 'custId': 'string', 'currType': 'uint8', 'cashType': 'uint8', 'cashAcctStatus': 'uint8', 'isFundTrsfDisabled': 'uint8', '__CASH_ASSET_BASE_filler': 'uint8', 'beginningBal': 'int64', 'beginningAvailableBal': 'int64', 'beginningDrawableBal': 'int64', 'disableBal': 'int64', 'reversalAmt': 'int64', 'manualFrzAmt': 'int64', 'totalDepositAmt': 'int64', 'totalWithdrawAmt': 'int64', 'withdrawFrzAmt': 'int64', 'totalSellAmt': 'int64', 'totalBuyAmt': 'int64', 'buyFrzAmt': 'int64', 'totalFeeAmt': 'int64', 'feeFrzAmt': 'int64', 'marginAmt': 'int64', 'marginFrzAmt': 'int64', 'currentTotalBal': 'int64', 'currentAvailableBal': 'int64', 'currentDrawableBal': 'int64', '{': 'struct', 'initialMargin': 'int64', 'totalExerciseFrzAmt': 'int64', 'pendingSupplMargin': 'int64', 'sseAvailablePurchaseLimit': 'int64', 'szseAvailablePurchaseLimit': 'int64', 'totalMarketMargin': 'int64', 'totalNetMargin': 'int64', 'optionExt': '}', '__CASH_ASSET_EXT_reserve': 'string'}
OesCustBaseInfoT : {'custId': 'string', 'custType': 'uint8', 'status': 'uint8', 'riskLevel': 'uint8', 'originRiskLevel': 'uint8', 'institutionFlag': 'uint8', 'investorClass':'uint8', 'optSettlementCnfmFlag': 'uint8', '__CUST_BASE_filler1': 'uint8', 'branchId': 'int32', '__CUST_BASE_filler2': 'uint32'}
OesEtfBaseInfoT : {'fundId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'isPublishIOPV': 'uint8', 'isCreationAble': 'uint8', 'isRedemptionAble': 'uint8', 'isDisabled': 'uint8', '__ETF_BASE_filler': 'uint8', 'componentCnt': 'int32', 'creRdmUnit': 'int32', 'maxCashRatio': 'int32', 'nav': 'int32', 'navPerCU': 'int64', 'dividendPerCU': 'int64', 'tradingDay': 'int32', 'preTradingDay': 'int32', 'estiCashCmpoent': 'int64', 'cashCmpoent': 'int64', 'creationLimit': 'int64', 'redemLimit': 'int64', 'netCreationLimit': 'int64', 'netRedemLimit': 'int64'}
OesEtfComponentBaseInfoT : {'fundId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'subFlag': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'prevClose': 'int32', 'qty': 'int32', 'premiumRate': 'int32', 'creationSubCash': 'int64', 'redemptionCashSub': 'int64'}
OesFundTrsfBaseInfoT : {'clSeqNo': 'int32', 'direct': 'uint8', 'isAllotOnly': 'uint8', '__FUND_TRSF_BASE_filler': 'uint8', 'cashAcctId': 'string', 'trdPasswd': 'string', 'trsfPasswd': 'string', 'occurAmt': 'int64'}
OesFundTrsfRejectT : {'clSeqNo': 'int32', 'direct': 'uint8', 'isAllotOnly': 'uint8', '__FUND_TRSF_BASE_filler': 'uint8', 'cashAcctId': 'string', 'trdPasswd': 'string', 'trsfPasswd': 'string', 'occurAmt': 'int64', 'ordDate': 'int32', 'ordTime': 'int32', 'clientId': 'int16', 'clEnvId': 'int8', '__filler': 'int8', 'rejReason': 'int32', 'errorInfo': 'string'}
OesFundTrsfReportT : {'clSeqNo': 'int32', 'clientId': 'int16', 'clEnvId': 'int8', 'direct': 'uint8', 'cashAcctId': 'string', 'occurAmt': 'int64'}
OesFundTrsfReqT : {'clSeqNo': 'int32', 'direct': 'uint8', 'isAllotOnly': 'uint8', '__FUND_TRSF_BASE_filler': 'uint8', 'cashAcctId': 'string', 'trdPasswd': 'string', 'trsfPasswd': 'string', 'occurAmt': 'int64'}
OesInvAcctBaseInfoT : {'invAcctId': 'string', 'mktId': 'uint8', 'acctType': 'uint8', 'status': 'uint8', 'ownerType': 'uint8', 'optInvLevel': 'uint8', 'isTradeDisabled': 'uint8', '__INV_ACCT_BASE_filler': 'uint8', 'limits': 'uint64', 'permissions': 'uint64', 'pbuId': 'int32', 'stkPositionLimitRatio': 'int32', 'subscriptionQuota': 'int32', 'kcSubscriptionQuota': 'int32', '__INV_ACCT_BASE_reserve': 'string'}
OesIssueBaseInfoT : {'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'isCancelAble': 'uint8', 'isReApplyAble': 'uint8', 'productType': 'uint8', 'suspFlag': 'uint8', 'issueType': 'uint8', 'securityName': 'string', 'underlyingSecurityId': 'string', 'startDate': 'int32', 'endDate': 'int32', 'issueQty': 'int64', 'qtyUnit': 'int32', 'ordMaxQty': 'int32', 'ordMinQty': 'int32', 'issuePrice': 'int32', 'upperLimitPrice': 'int32', 'ceilPrice': 'int32', 'lowerLimitPrice': 'int32', 'floorPrice': 'int32'}
OesLotWinningBaseInfoT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'lotType': 'uint8', 'rejReason': 'uint8', '__LOT_WINNING_BASE_INFO_filler': 'int8','lotDate': 'int32', 'securityName': 'string', 'assignNum': 'int64', 'lotQty': 'int32', 'lotPrice': 'int32', 'lotAmt': 'int64'}
OesNotifyBaseInfoT : {'notifySeqNo': 'int32', 'notifySource': 'uint8', 'notifyType': 'uint8', 'notifyLevel': 'uint8', 'notifyScope': 'uint8', 'tranTime': 'int32', '__NOTIFY_INFO_filler': 'int32', 'custId': 'string', 'content': 'string'}
OesNotifyInfoReportT : {'notifySeqNo': 'int32', 'notifySource': 'uint8', 'notifyType': 'uint8', 'notifyLevel': 'uint8', 'notifyScope': 'uint8', 'tranTime': 'int32', '__NOTIFY_INFO_filler': 'int32', 'custId': 'string', 'content': 'string'}
OesOptHoldingBaseInfoT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'positionType': 'uint8', 'productType': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'contractType': 'uint8', 'hedgeFlag': 'uint8', '__HOLD_BASE_filler': 'uint8', 'originalQty': 'int64', 'originalAvlQty': 'int64', 'originalCostAmt': 'int64','originalCarryingAmt': 'int64', 'totalOpenQty': 'int64', 'uncomeQty': 'int64', 'totalCloseQty': 'int64', 'closeFrzQty': 'int64', 'manualFrzQty': 'int64', 'totalInPremium': 'int64', 'totalOutPremium': 'int64', 'totalOpenFee': 'int64', 'totalCloseFee': 'int64', 'exerciseFrzQty': 'int64', 'positionMargin': 'int64', '__OPT_HOLDING_BASE_reserve': 'string'}
OesOptHoldingReportT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'positionType': 'uint8', 'productType': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'contractType': 'uint8', 'hedgeFlag': 'uint8', '__HOLD_BASE_filler': 'uint8', 'originalQty': 'int64', 'originalAvlQty': 'int64', 'originalCostAmt': 'int64', 'originalCarryingAmt': 'int64', 'totalOpenQty': 'int64', 'uncomeQty': 'int64', 'totalCloseQty': 'int64', 'closeFrzQty': 'int64', 'manualFrzQty': 'int64', 'totalInPremium': 'int64', 'totalOutPremium': 'int64', 'totalOpenFee': 'int64', 'totalCloseFee': 'int64', 'exerciseFrzQty': 'int64', 'positionMargin': 'int64', '__OPT_HOLDING_BASE_reserve': 'string', 'closeAvlQty': 'int64', 'exerciseAvlQty': 'int64', 'sumQty': 'int64', 'costPrice': 'int64', 'carryingAvgPrice': 'int64', 'coveredAvlUnderlyingQty': 'int64', 'availableLongPositionLimit': 'int32', 'availableTotalPositionLimit': 'int32', 'availableDailyBuyOpenLimit': 'int32', '__OPT_HOLDING_EXT_filler2': 'int32', '__OPT_HOLDING_EXT_reserve': 'string'}
OesOptSettlementConfirmBaseInfoT : {'custId': 'string', 'clientId': 'int16', 'clEnvId': 'int8', '__filler2': 'int8', 'transDate': 'int32', 'transTime': 'int32', 'rejReason': 'int32', '__OPT_SETTLEMENT_CONFIRM_BASE_reserve': 'string'}
OesOptSettlementConfirmReportT : {'custId': 'string', 'clientId': 'int16', 'clEnvId': 'int8', '__filler2': 'int8', 'transDate': 'int32', 'transTime': 'int32', 'rejReason': 'int32', '__OPT_SETTLEMENT_CONFIRM_BASE_reserve': 'string'}
OesOptUnderlyingHoldingBaseInfoT : {'invAcctId': 'string', 'underlyingSecurityId': 'string', 'mktId': 'uint8', 'underlyingMktId': 'uint8', 'underlyingSecurityType': 'uint8', 'underlyingSubSecurityType': 'uint8', '__OPT_UNDERLYING_HOLD_BASE_filler': 'uint8', 'originalHld': 'int64', 'originalAvlHld': 'int64', 'originalCoveredQty': 'int64', 'initialCoveredQty': 'int64', 'coveredQty': 'int64', 'coveredGapQty': 'int64', 'coveredAvlQty': 'int64', 'lockAvlQty': 'int64', 'sumHld': 'int64', 'maxReduceQuota': 'int64'}
OesOptUnderlyingHoldingReportT : {'invAcctId': 'string', 'underlyingSecurityId': 'string', 'mktId': 'uint8', 'underlyingMktId': 'uint8', 'underlyingSecurityType': 'uint8', 'underlyingSubSecurityType': 'uint8', '__OPT_UNDERLYING_HOLD_BASE_filler': 'uint8', 'originalHld': 'int64', 'originalAvlHld': 'int64', 'originalCoveredQty': 'int64', 'initialCoveredQty': 'int64', 'coveredQty': 'int64', 'coveredGapQty': 'int64', 'coveredAvlQty': 'int64', 'lockAvlQty': 'int64', 'sumHld': 'int64', 'maxReduceQuota': 'int64'}
OesOptionBaseInfoT : {'securityId': 'string', 'mktId': 'uint8', 'productType': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'contractType': 'uint8', 'exerciseType': 'uint8', 'deliveryType': 'uint8', 'isDayTrading': 'uint8', 'limitOpenFlag': 'uint8', 'suspFlag': 'uint8', 'temporarySuspFlag': 'uint8', '__OPTION_BASE_filler1': 'uint8', 'contractUnit': 'int32', 'exercisePrice': 'int32', 'deliveryDate': 'int32', 'deliveryMonth': 'int32', 'listDate': 'int32', 'lastTradeDay': 'int32', 'exerciseBeginDate': 'int32', 'exerciseEndDate': 'int32', 'contractPosition': 'int64', 'prevClosePrice': 'int32', 'prevSettlPrice': 'int32', 'underlyingClosePrice': 'int32', 'priceTick': 'int32', 'upperLimitPrice': 'int32', 'lowerLimitPrice': 'int32', 'buyQtyUnit': 'int32', 'lmtBuyMaxQty': 'int32', 'lmtBuyMinQty': 'int32', 'mktBuyMaxQty': 'int32', 'mktBuyMinQty': 'int32',
'sellQtyUnit': 'int32', 'lmtSellMaxQty': 'int32', 'lmtSellMinQty': 'int32', 'mktSellMaxQty': 'int32', 'mktSellMinQty': 'int32', 'sellMargin': 'int64', 'originalSellMargin': 'int64', 'marginRatioParam1': 'int32', 'marginRatioParam2': 'int32', 'increasedMarginRatio': 'int32', 'expireDays': 'int32', 'contractId': 'string', 'securityName': 'string', 'securityStatusFlag': 'string', 'underlyingSecurityId': 'string', 'underlyingMktId': 'uint8', 'underlyingSecurityType': 'uint8', '__OPTION_BASE_filler3': 'uint8', '__OPTION_BASE_reserve': 'string'}
OesOptionExerciseAssignBaseT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'positionType': 'uint8', 'productType': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'contractType': 'uint8', 'deliveryType': 'uint8', '__OPTION_EXERCISE_ASSIGN_filler1': 'uint8', 'exercisePrice': 'int32', 'exerciseQty': 'int32', 'deliveryQty': 'int64', 'exerciseBeginDate': 'int32', 'exerciseEndDate': 'int32', 'clearingDate': 'int32', 'deliveryDate': 'int32', 'clearingAmt': 'int64', 'clearingFee': 'int64', 'settlementAmt': 'int64', 'underlyingSecurityId': 'string', 'underlyingMktId': 'uint8', 'underlyingSecurityType': 'uint8', '__OPTION_EXERCISE_ASSIGN_filler3': 'uint8', 'securityName': 'string', '__OPTION_EXERCISE_ASSIGN_reserve': 'string'}
OesOptionPositionLimitBaseInfoT : {'invAcctId': 'string', 'underlyingSecurityId': 'string', 'mktId': 'uint8', 'underlyingMktId': 'uint8', 'underlyingSecurityType': 'uint8', 'underlyingSubSecurityType': 'uint8', '__POSITION_LIMIT_BASE_filler1': 'uint8', 'longPositionLimit': 'int32', 'totalPositionLimit': 'int32', 'dailyBuyOpenLimit': 'int32', '__POSITION_LIMIT_BASE_filler2': 'int32', 'originalLongQty': 'int32', 'totalBuyOpenQty': 'int32', 'uncomeBuyOpenQty': 'int32', 'totalSellCloseQty': 'int32', 'originalShortQty': 'int32', 'totalSellOpenQty': 'int32', 'uncomeSellOpenQty': 'int32', 'totalBuyCloseQty': 'int32', 'originalCoveredQty': 'int32', 'totalCoveredOpenQty': 'int32', 'uncomeCoveredOpenQty': 'int32', 'totalCoveredCloseQty': 'int32'}
OesOrdCancelReqT : {'clSeqNo': 'int32', 'mktId': 'uint8', '__ORD_CANCEL_BASE_INFO_filler1': 'uint8', 'invAcctId': 'string', 'securityId': 'string', 'origClSeqNo': 'int32', 'origClEnvId': 'int8', '__ORD_CANCEL_BASE_INFO_filler2': 'uint8', 'origClOrdId': 'int64', '__ordReqOrigSendTime': 'STimeval32T'}
OesOrdCnfmT : {'clSeqNo': 'int32', 'mktId': 'uint8', 'ordType': 'uint8', 'bsType': 'uint8', '__ORD_BASE_INFO_filler': 'uint8', 'invAcctId': 'string', 'securityId': 'string', 'ordQty': 'int32', 'ordPrice': 'int32', 'origClOrdId': 'int64', '__ordReqOrigSendTime': 'STimeval32T', 'clOrdId': 'int64', 'clientId': 'int16', 'clEnvId': 'int8', 'origClEnvId': 'int8', 'origClSeqNo': 'int32', 'ordDate': 'int32', 'ordTime': 'int32', 'ordCnfmTime': 'int32', 'ordStatus': 'uint8', 'ordCnfmSts': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', '__platformId': 'uint8', '__tgwGrpNo': 'uint8', '__tgwPartitionNo': 'uint8', 'productType': 'uint8', 'exchOrdId': 'string', '__declareFlag': 'uint8', '__repeatFlag': 'uint8', 'ownerType': 'uint8', 'frzAmt': 'int64', 'frzInterest': 'int64', 'frzFee': 'int64', 'cumAmt': 'int64', 'cumInterest': 'int64', 'cumFee': 'int64', 'cumQty': 'int32', 'canceledQty': 'int32', 'ordRejReason': 'int32', 'exchErrCode': 'int32', 'pbuId': 'int32', 'branchId': 'int32', '__rowNum': 'int32', '__recNum': 'uint32', '__ordReqOrigRecvTime': 'STimeval32T', '__ordReqCollectedTime': 'STimeval32T', '__ordReqActualDealTime': 'STimeval32T', '__ordReqProcessedTime': 'STimeval32T', '__ordCnfmOrigRecvTime': 'STimeval32T', '__ordCnfmCollectedTime': 'STimeval32T', '__ordCnfmActualDealTime': 'STimeval32T', '__ordCnfmProcessedTime': 'STimeval32T', '__ordDeclareTime': 'STimeval32T',
'__ordDeclareDoneTime': 'STimeval32T', '__pushingTime': 'STimeval32T', 'frzMargin': 'int64', 'cumMargin': 'int64', '__ORD_CNFM_EXT_reserve': 'string'}
OesOrdRejectT : {'clSeqNo': 'int32', 'mktId': 'uint8', 'ordType': 'uint8', 'bsType': 'uint8', '__ORD_BASE_INFO_filler': 'uint8', 'invAcctId': 'string', 'securityId': 'string', 'ordQty': 'int32', 'ordPrice': 'int32', 'origClOrdId': 'int64', '__ordReqOrigSendTime': 'STimeval32T', 'origClSeqNo': 'int32', 'origClEnvId': 'int8', 'clEnvId': 'int8', 'clientId': 'int16', 'ordDate': 'int32', 'ordTime': 'int32', 'ordRejReason': 'int32', '__filler': 'int32'}
OesOrdReqT : {'clSeqNo': 'int32', 'mktId': 'uint8', 'ordType': 'uint8', 'bsType': 'uint8', '__ORD_BASE_INFO_filler': 'uint8', 'invAcctId': 'string', 'securityId': 'string', 'ordQty': 'int32', 'ordPrice': 'int32', 'origClOrdId': 'int64', '__ordReqOrigSendTime': 'STimeval32T'}
OesPriceLimitT : {'upperLimitPrice': 'int32', 'ceilPrice': 'int32'}
OesStkHoldingBaseInfoT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'productType': 'uint8', '__HOLD_BASE_filler': 'uint8', 'originalHld': 'int64', 'originalCostAmt': 'int64', 'totalBuyHld': 'int64', 'totalSellHld': 'int64', 'sellFrzHld': 'int64', 'manualFrzHld': 'int64', 'totalBuyAmt': 'int64', 'totalSellAmt': 'int64', 'totalBuyFee': 'int64', 'totalSellFee': 'int64', 'totalTrsfInHld': 'int64', 'totalTrsfOutHld': 'int64', 'trsfOutFrzHld': 'int64', 'originalLockHld': 'int64', 'totalLockHld': 'int64', 'totalUnlockHld': 'int64', 'originalAvlHld': 'int64', 'maxReduceQuota': 'int64'}
OesStkHoldingReportT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'productType': 'uint8', '__HOLD_BASE_filler': 'uint8', 'originalHld': 'int64', 'originalCostAmt': 'int64', 'totalBuyHld': 'int64', 'totalSellHld': 'int64', 'sellFrzHld': 'int64', 'manualFrzHld': 'int64', 'totalBuyAmt': 'int64', 'totalSellAmt': 'int64', 'totalBuyFee': 'int64', 'totalSellFee': 'int64', 'totalTrsfInHld': 'int64', 'totalTrsfOutHld': 'int64', 'trsfOutFrzHld': 'int64',
'originalLockHld': 'int64', 'totalLockHld': 'int64', 'totalUnlockHld': 'int64', 'originalAvlHld': 'int64', 'maxReduceQuota': 'int64', 'sellAvlHld': 'int64', 'trsfOutAvlHld': 'int64', 'lockAvlHld': 'int64', '__filler': 'int64', 'sumHld': 'int64', 'costPrice': 'int64'}
OesStockBaseInfoT : {'securityId': 'string', 'mktId': 'uint8', 'productType': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'securityLevel': 'uint8', 'securityRiskLevel': 'uint8', 'currType': 'uint8', 'qualificationClass': 'uint8', 'isDayTrading': 'uint8', 'suspFlag': 'uint8', 'temporarySuspFlag': 'uint8', '__STOCK_BASE_filler': 'uint8', 'buyQtyUnit': 'int32', 'lmtBuyMaxQty': 'int32', 'buyOrdMaxQty': 'int32', 'lmtBuyMinQty': 'int32', 'buyOrdMinQty': 'int32', 'mktBuyMaxQty': 'int32', 'mktBuyMinQty': 'int32', 'sellQtyUnit': 'int32', 'lmtSellMaxQty': 'int32', 'sellOrdMaxQty': 'int32', 'lmtSellMinQty': 'int32', 'sellOrdMinQty': 'int32', 'mktSellMaxQty': 'int32', 'mktSellMinQty':
'int32', 'priceTick': 'int32', 'priceUnit': 'int32', 'prevClose': 'int32', 'parPrice': 'int64', 'bondInterest': 'int64', 'repoExpirationDays': 'int32', 'cashHoldDays': 'int32', 'priceLimit': 'OesPriceLimitT', 'securityName': 'string', 'fundId': 'string', 'outstandingShare': 'int64', 'publicFloatShare': 'int64', '__STOCK_BASE_reserve': 'string'}
OesTrdBaseInfoT : {'exchTrdNum': 'int64', 'mktId': 'uint8', 'trdSide': 'uint8', '__platformId': 'uint8', '__trdCnfmType': 'uint8', '__etfTrdCnfmSeq': 'uint32', 'invAcctId': 'string', 'securityId': 'string', 'trdDate': 'int32', 'trdTime': 'int32', 'trdQty': 'int32', 'trdPrice': 'int32', 'trdAmt': 'int64', 'clOrdId': 'int64', 'cumQty': 'int32', '__rowNum': 'int32', '__tgwGrpNo': 'uint8', '__isTrsfInCashAvailable': 'uint8', '__tgwPartitionNo': 'uint8', 'productType': 'uint8', 'origOrdQty': 'int32', 'pbuId': 'int32', 'branchId': 'int32'}
OesTrdCnfmT : {'exchTrdNum': 'int64', 'mktId': 'uint8', 'trdSide': 'uint8', '__platformId': 'uint8', '__trdCnfmType': 'uint8', '__etfTrdCnfmSeq': 'uint32', 'invAcctId': 'string', 'securityId': 'string', 'trdDate': 'int32', 'trdTime': 'int32', 'trdQty': 'int32', 'trdPrice': 'int32', 'trdAmt': 'int64', 'clOrdId': 'int64', 'cumQty': 'int32', '__rowNum': 'int32', '__tgwGrpNo': 'uint8', '__isTrsfInCashAvailable': 'uint8', '__tgwPartitionNo': 'uint8', 'productType': 'uint8', 'origOrdQty': 'int32', 'pbuId': 'int32', 'branchId': 'int32', 'clSeqNo': 'int32', 'clientId': 'int16', 'clEnvId': 'int8', 'subSecurityType': 'uint8', 'ordStatus': 'uint8', 'ordType': 'uint8', 'ordBuySellType': 'uint8', 'securityType': 'uint8', 'origOrdPrice': 'int32', 'cumAmt': 'int64', 'cumInterest': 'int64', 'cumFee': 'int64', '__trdCnfmOrigRecvTime': 'STimeval32T', '__trdCnfmCollectedTime': 'STimeval32T', '__trdCnfmActualDealTime': 'STimeval32T', '__trdCnfmProcessedTime': 'STimeval32T', '__pushingTime': 'STimeval32T', 'trdInterest': 'int64', 'trdFee': 'int64', 'trdMargin': 'int64', 'cumMargin': 'int64', '__TRD_CNFM_EXT_reserve': 'string'}
OesBatchOrdersHeadT : {'itemCount': 'int32', '__filler': 'int32'}
OesBatchOrdersReqT : {'batchHead': 'dict', 'items': 'dict'}
OesChangePasswordReqT : {'encryptMethod': 'int32', '__filler': 'int32', 'username': 'string'}
OesChangePasswordRspT : {'encryptMethod': 'int32', '__filler': 'int32', 'username': 'string'}
OesOptSettlementConfirmReqT : {'custId': 'string'}
OesReportSynchronizationReqT : {'lastRptSeqNum': 'int64', 'subscribeEnvId': 'int8', '__filler': 'uint8', 'subscribeRptTypes': 'int32'}
OesReportSynchronizationRspT : {'lastRptSeqNum': 'int64', 'subscribeEnvId': 'int8', '__filler': 'uint8', 'subscribeRptTypes': 'int32'}
OesRptMsgHeadT : {}
OesRptMsgT : {}
OesTestRequestReqT : {'testReqId': 'string', 'sendTime': 'string', '__filler': 'string'}
OesTestRequestRspT : {'testReqId': 'string', 'origSendTime': 'string', '__filler1': 'string', 'respTime': 'string', '__filler2': 'string', '__recvTime': 'STimeval32T', '__collectedTime': 'STimeval32T', '__pushingTime': 'STimeval32T'}
OesBrokerParamsInfoT : {'brokerName': 'string', 'brokerPhone': 'string', 'brokerWebsite': 'string', 'apiVersion': 'string', 'apiMinVersion': 'string', 'clientVersion': 'string', 'changePwdLimitTime': 'int32', 'minClientPasswordLen': 'int32', 'clientPasswordStrength': 'int32', 'businessScope': 'uint32', '__reserve': 'string'}
OesCashAcctOverviewT : {'cashAcctId': 'string', 'custId': 'string', 'bankId': 'string'}
OesCashAssetItemT : {'cashAcctId': 'string', 'custId': 'string', 'currType': 'uint8', 'cashType': 'uint8', 'cashAcctStatus': 'uint8', 'isFundTrsfDisabled': 'uint8', '__CASH_ASSET_BASE_filler': 'uint8', 'beginningBal': 'int64', 'beginningAvailableBal': 'int64', 'beginningDrawableBal': 'int64', 'disableBal': 'int64', 'reversalAmt': 'int64', 'manualFrzAmt': 'int64', 'totalDepositAmt': 'int64', 'totalWithdrawAmt': 'int64', 'withdrawFrzAmt': 'int64', 'totalSellAmt': 'int64', 'totalBuyAmt': 'int64', 'buyFrzAmt': 'int64', 'totalFeeAmt': 'int64', 'feeFrzAmt': 'int64', 'marginAmt': 'int64', 'marginFrzAmt': 'int64', 'currentTotalBal': 'int64', 'currentAvailableBal': 'int64', 'currentDrawableBal': 'int64', '{': 'struct', 'initialMargin': 'int64', 'totalExerciseFrzAmt': 'int64', 'pendingSupplMargin': 'int64', 'sseAvailablePurchaseLimit': 'int64', 'szseAvailablePurchaseLimit': 'int64', 'totalMarketMargin': 'int64', 'totalNetMargin': 'int64', 'optionExt': '}', '__CASH_ASSET_EXT_reserve': 'string'}
OesClientOverviewT : {'clientName': 'string', 'clientMemo': 'string', 'custItems': 'OesCustOverviewT'}
OesCommissionRateItemT : {'custId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'bsType': 'uint8', 'feeType': 'uint8', 'currType': 'uint8', 'calcFeeMode': 'uint8', '__filler': 'uint8', 'feeRate': 'int64', 'minFee': 'int32', 'maxFee': 'int32'}
OesCounterCashItemT : {'cashAcctId': 'string', 'custId': 'string', 'custName': 'string', 'bankId': 'string'}
OesCustOverviewT : {'custId': 'string', 'custType': 'uint8', 'status': 'uint8', 'riskLevel': 'uint8', 'originRiskLevel': 'uint8', 'institutionFlag': 'uint8', 'investorClass':
'uint8', 'optSettlementCnfmFlag': 'uint8', '__CUST_BASE_filler1': 'uint8', 'branchId': 'int32', '__CUST_BASE_filler2': 'uint32', 'custName': 'string'}
OesEtfComponentItemT : {'securityId': 'string', 'mktId': 'uint8', 'subFlag': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'prevClose': 'int32', 'qty': 'int32', 'premiumRate': 'int32', 'creationSubCash': 'int64', 'redemptionCashSub': 'int64', 'fundId': 'string'}
OesInvAcctItemT : {'invAcctId': 'string', 'mktId': 'uint8', 'acctType': 'uint8', 'status': 'uint8', 'ownerType': 'uint8', 'optInvLevel': 'uint8', 'isTradeDisabled': 'uint8', '__INV_ACCT_BASE_filler': 'uint8', 'limits': 'uint64', 'permissions': 'uint64', 'pbuId': 'int32', 'stkPositionLimitRatio': 'int32', 'subscriptionQuota': 'int32', 'kcSubscriptionQuota': 'int32', '__INV_ACCT_BASE_reserve': 'string', 'custId': 'string'}
OesInvAcctOverviewT : {'invAcctId': 'string', 'mktId': 'uint8', 'acctType': 'uint8', 'status': 'uint8', 'ownerType': 'uint8', 'optInvLevel': 'uint8', 'isTradeDisabled': 'uint8', '__INV_ACCT_BASE_filler': 'uint8', 'limits': 'uint64', 'permissions': 'uint64', 'pbuId': 'int32', 'subscriptionQuota': 'int32', 'custId': 'string'}
OesOptHoldingItemT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'positionType': 'uint8', 'productType': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'contractType': 'uint8', 'hedgeFlag': 'uint8', '__HOLD_BASE_filler': 'uint8', 'originalQty': 'int64', 'originalAvlQty': 'int64', 'originalCostAmt': 'int64', 'originalCarryingAmt': 'int64', 'totalOpenQty': 'int64', 'uncomeQty': 'int64', 'totalCloseQty': 'int64', 'closeFrzQty': 'int64', 'manualFrzQty': 'int64', 'totalInPremium': 'int64', 'totalOutPremium': 'int64', 'totalOpenFee': 'int64', 'totalCloseFee': 'int64', 'exerciseFrzQty': 'int64', 'positionMargin': 'int64', '__OPT_HOLDING_BASE_reserve': 'string',
'closeAvlQty': 'int64', 'exerciseAvlQty': 'int64', 'sumQty': 'int64', 'costPrice': 'int64', 'carryingAvgPrice': 'int64', 'coveredAvlUnderlyingQty': 'int64', 'availableLongPositionLimit': 'int32', 'availableTotalPositionLimit': 'int32', 'availableDailyBuyOpenLimit': 'int32', '__OPT_HOLDING_EXT_filler2': 'int32', '__OPT_HOLDING_EXT_reserve': 'string', 'contractId': 'string', 'contractSymbol': 'string', 'prevSettlPrice': 'int64'}
OesOptPositionLimitItemT : {'invAcctId': 'string', 'underlyingSecurityId': 'string', 'mktId': 'uint8', 'underlyingMktId': 'uint8', 'underlyingSecurityType': 'uint8', 'underlyingSubSecurityType': 'uint8', '__filler1': 'uint8', 'longPositionLimit': 'int32', 'totalPositionLimit': 'int32', 'dailyBuyOpenLimit': 'int32', '__filler2': 'int32', 'originalLongQty': 'int32', 'originalShortQty': 'int32', 'originalCoveredQty': 'int32', 'availableLongPositionLimit': 'int32', 'availableTotalPositionLimit': 'int32', 'availableDailyBuyOpenLimit': 'int32', '__reserve': 'string'}
OesOptPurchaseLimitItemT : {'custId': 'string', 'cashAcctId': 'string', 'invAcctId': 'string', 'mktId': 'uint8', 'custType': 'uint8', '__filler': 'uint8', 'purchaseLimit': 'int64', 'originalUsedPurchaseAmt': 'int64', 'totalOpenPurchaseAmt': 'int64', 'frzPurchaseAmt': 'int64', 'totalClosePurchaseAmt': 'int64', 'availablePurchaseLimit': 'int64'}
OesQryBrokerParamsInfoRspT : {'brokerParams': 'OesBrokerParamsInfoT'}
OesQryCashAssetFilterT : {'custId': 'string', 'cashAcctId': 'string', 'userInfo': 'int64'}
OesQryCashAssetReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryCashAssetFilterT'}
OesQryCashAssetRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesCashAssetItemT'}
OesQryCommissionRateFilterT : {'custId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'bsType': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryCommissionRateReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryCommissionRateFilterT'}
OesQryCommissionRateRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesCommissionRateItemT'}
OesQryCounterCashReqT : {'cashAcctId': 'string'}
OesQryCounterCashRspT : {'counterCashItem': 'OesCounterCashItemT'}
OesQryCursorT : {'seqNo': 'int32', 'isEnd': 'int8', '__filler': 'int8', 'userInfo': 'int64'}
OesQryCustFilterT : {'custId': 'string', 'userInfo': 'int64'}
OesQryCustReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryCustFilterT'}
OesQryCustRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesCustItemT'}
OesQryEtfComponentFilterT : {'fundId': 'string', 'userInfo': 'int64'}
OesQryEtfComponentReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryEtfComponentFilterT'}
OesQryEtfComponentRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesEtfComponentItemT'}
OesQryEtfFilterT : {'fundId': 'string', 'mktId': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryEtfReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryEtfFilterT'}
OesQryEtfRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesEtfItemT'}
OesQryFundTransferSerialFilterT : {'custId': 'string', 'cashAcctId': 'string', 'clSeqNo': 'int32', 'clEnvId': 'int8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryFundTransferSerialReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryFundTransferSerialFilterT'}
OesQryFundTransferSerialRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesFundTransferSerialItemT'}
OesQryInvAcctFilterT : {'custId': 'string', 'invAcctId': 'string', 'mktId': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryInvAcctReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryInvAcctFilterT'}
OesQryInvAcctRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesInvAcctItemT'}
OesQryIssueFilterT : {'securityId': 'string', 'mktId': 'uint8', 'productType': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryIssueReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryIssueFilterT'}
OesQryIssueRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesIssueItemT'}
OesQryLotWinningFilterT : {'custId': 'string', 'invAcctId': 'string', 'mktId': 'uint8', 'lotType': 'uint8', '__filler': 'uint8', 'startDate': 'int32', 'endDate': 'int32', 'userInfo': 'int64'}
OesQryLotWinningReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryLotWinningFilterT'}
OesQryLotWinningRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesLotWinningItemT'}
OesQryMarketStateFilterT : {'exchId': 'uint8', 'platformId': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryMarketStateReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryMarketStateFilterT'}
OesQryMarketStateRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesMarketStateItemT'}
OesQryNotifyInfoFilterT : {'custId': 'string', 'notifyLevel': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryNotifyInfoReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryNotifyInfoFilterT'}
OesQryNotifyInfoRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesNotifyInfoItemT'}
OesQryOptExerciseAssignFilterT : {'custId': 'string', 'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'positionType': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryOptExerciseAssignReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryOptExerciseAssignFilterT'}
OesQryOptExerciseAssignRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesOptExerciseAssignItemT'}
OesQryOptHoldingFilterT : {'custId': 'string', 'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'positionType': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryOptHoldingReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryOptHoldingFilterT'}
OesQryOptHoldingRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesOptHoldingItemT'}
OesQryOptPositionLimitFilterT : {'custId': 'string', 'invAcctId': 'string', 'underlyingSecurityId': 'string', 'mktId': 'uint8', 'underlyingSecurityType': 'uint8', '__filler':'uint8', 'userInfo': 'int64'}
OesQryOptPositionLimitReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryOptPositionLimitFilterT'}
OesQryOptPositionLimitRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesOptPositionLimitItemT'}
OesQryOptPurchaseLimitFilterT : {'custId': 'string', 'invAcctId': 'string', 'mktId': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryOptPurchaseLimitReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryOptPurchaseLimitFilterT'}
OesQryOptPurchaseLimitRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesOptPurchaseLimitItemT'}
OesQryOptUnderlyingHoldingFilterT : {'custId': 'string', 'invAcctId': 'string', 'underlyingSecurityId': 'string', 'mktId': 'uint8', 'underlyingSecurityType': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryOptUnderlyingHoldingReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryOptUnderlyingHoldingFilterT'}
OesQryOptUnderlyingHoldingRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesOptUnderlyingHoldingItemT'}
OesQryOptionFilterT : {'securityId': 'string', 'mktId': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryOptionReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryOptionFilterT'}
OesQryOptionRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesOptionItemT'}
OesQryOrdFilterT : {'custId': 'string', 'invAcctId': 'string', 'mktId': 'uint8', 'isUnclosedOnly': 'uint8', 'clEnvId': 'int8', 'securityType': 'uint8', 'bsType': 'uint8', '__filler': 'uint8', 'clOrdId': 'int64', 'clSeqNo': 'int64', 'startTime': 'int32', 'endTime': 'int32', 'userInfo': 'int64'}
OesQryOrdReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryOrdFilterT'}
OesQryOrdRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesOrdItemT'}
OesQryReqHeadT : {'maxPageSize': 'int32', 'lastPosition': 'int32'}
OesQryRspHeadT : {'itemCount': 'int32', 'lastPosition': 'int32', 'isEnd': 'int8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryStkHoldingFilterT : {'custId': 'string', 'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'productType': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryStkHoldingReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryStkHoldingFilterT'}
OesQryStkHoldingRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesStkHoldingItemT'}
OesQryStockFilterT : {'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', '__filler': 'uint8', 'userInfo': 'int64'}
OesQryStockReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryStockFilterT'}
OesQryStockRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesStockItemT'}
OesQryTradingDayRspT : {'tradingDay': 'int32', '__filler': 'int32'}
OesQryTrdFilterT : {'custId': 'string', 'invAcctId': 'string', 'mktId': 'uint8', 'clEnvId': 'int8', 'securityType': 'uint8', 'bsType': 'uint8', '__filler': 'uint32', 'clOrdId': 'int64', 'clSeqNo': 'int64', 'startTime': 'int32', 'endTime': 'int32', 'userInfo': 'int64'}
OesQryTrdReqT : {'reqHead': 'OesQryReqHeadT', 'qryFilter': 'OesQryTrdFilterT'}
OesQryTrdRspT : {'rspHead': 'OesQryRspHeadT', 'qryItems': 'OesTrdItemT'}
OesStkHoldingItemT : {'invAcctId': 'string', 'securityId': 'string', 'mktId': 'uint8', 'securityType': 'uint8', 'subSecurityType': 'uint8', 'productType': 'uint8', '__HOLD_BASE_filler': 'uint8', 'originalHld': 'int64', 'originalCostAmt': 'int64', 'totalBuyHld': 'int64', 'totalSellHld': 'int64', 'sellFrzHld': 'int64', 'manualFrzHld': 'int64', 'totalBuyAmt': 'int64', 'totalSellAmt': 'int64', 'totalBuyFee': 'int64', 'totalSellFee': 'int64', 'totalTrsfInHld': 'int64', 'totalTrsfOutHld': 'int64', 'trsfOutFrzHld': 'int64', 'originalLockHld': 'int64', 'totalLockHld': 'int64', 'totalUnlockHld': 'int64', 'originalAvlHld': 'int64', 'maxReduceQuota': 'int64', 'sellAvlHld': 'int64', 'trsfOutAvlHld': 'int64', 'lockAvlHld': 'int64', '__filler': 'int64', 'sumHld': 'int64', 'costPrice': 'int64'}











 'QueryOrder': {'pQryFilter': 'OesQryOrdFilterT', 'requestId': 'int32'},
 'QueryTrade': {'pQryFilter': 'OesQryTrdFilterT', 'requestId': 'int32'},
 'QueryCashAsset': {'pQryFilter': 'OesQryCashAssetFilterT', 'requestId': 'int32'},
 'QueryStkHolding': {'pQryFilter': 'OesQryStkHoldingFilterT', 'requestId': 'int32'},
 'QueryLotWinning': {'pQryFilter': 'OesQryLotWinningFilterT', 'requestId': 'int32'},
 'QueryCustInfo': {'pQryFilter': 'OesQryCustFilterT', 'requestId': 'int32'},
 'QueryInvAcct': {'pQryFilter': 'OesQryInvAcctFilterT', 'requestId': 'int32'},
 'QueryCommissionRate': {'pQryFilter': 'OesQryCommissionRateFilterT', 'requestId': 'int32'},
 'QueryFundTransferSerial': {'pQryFilter': 'OesQryFundTransferSerialFilterT', 'requestId': 'int32'},
 'QueryIssue': {'pQryFilter': 'OesQryIssueFilterT', 'requestId': 'int32'},
 'QueryStock': {'pQryFilter': 'OesQryStockFilterT', 'requestId': 'int32'},
 'QueryEtf': {'pQryFilter': 'OesQryEtfFilterT', 'requestId': 'int32'},
 'QueryEtfComponent': {'pQryFilter': 'OesQryEtfComponentFilterT', 'requestId': 'int32'},
 'QueryMarketState': {'pQryFilter': 'OesQryMarketStateFilterT', 'requestId': 'int32'},
 'QueryCounterCash': {'pCashAcctId': 'char', 'pCounterCashItem': 'OesCounterCashItemT', 'requestId': 'int32'},
 'QueryOption': {'pQryFilter': 'OesQryOptionFilterT', 'requestId': 'int32'},
 'QueryOptHolding': {'pQryFilter': 'OesQryOptHoldingFilterT', 'requestId': 'int32'},
 'QueryOptUnderlyingHolding': {'pQryFilter': 'OesQryOptUnderlyingHoldingFilterT', 'requestId': 'int32'},
 'QueryOptPositionLimit': {'pQryFilter': 'OesQryOptPositionLimitFilterT', 'requestId': 'int32'},
 'QueryOptPurchaseLimit': {'pQryFilter': 'OesQryOptPurchaseLimitFilterT', 'requestId': 'int32'},
 'QueryOptExerciseAssign': {'pQryFilter': 'OesQryOptExerciseAssignFilterT', 'requestId': 'int32'},
 'QueryOptSettlementStatement': {'pCustId': 'char', 'pSettleBuf': 'char', 'bufSize': 'int32', 'requestId': 'int32'},
 'QueryNotifyInfo': {'pQryFilter': 'OesQryNotifyInfoFilterT', 'requestId': 'int32'}




 'OnBusinessReject': {'pRptMsgHead': 'OesRptMsgHeadT', 'pOrderReject': 'OesOrdRejectT'},
 'OnOrderInsert': {'pRptMsgHead': 'OesRptMsgHeadT', 'pOrderInsert': 'OesOrdCnfmT'},
 'OnOrderReport': {'pRptMsgHead': 'OesRptMsgHeadT', 'pOrderReport': 'OesOrdCnfmT'},
 'OnTradeReport': {'pRptMsgHead': 'OesRptMsgHeadT', 'pTradeReport': 'OesTrdCnfmT'},
 'OnCashAssetVariation': {'pCashAssetRpt': 'OesCashAssetReportT'},
 'OnStockHoldingVariation': {'pStkHoldingRpt': 'OesStkHoldingReportT'},
 'OnOptionHoldingVariation': {'pOptHoldingRpt': 'OesOptHoldingReportT'},
 'OnOptionUnderlyingHoldingVariation': {'pUnderlyingHoldingRpt': 'OesOptUnderlyingHoldingReportT'},
 'OnSettlementConfirmedRpt': {'pRptMsgHead': 'OesRptMsgHeadT', 'pCnfmSettlementRpt': 'OesOptSettlementConfirmReportT'},
 'OnFundTrsfReject': {'pRptMsgHead': 'OesRptMsgHeadT', 'pFundTrsfReject': 'OesFundTrsfRejectT'},
 'OnFundTrsfReport': {'pRptMsgHead': 'OesRptMsgHeadT', 'pFundTrsfReport': 'OesFundTrsfReportT'},
 'OnMarketState': {'pMarketStateItem': 'OesMarketStateItemT'},
 'OnNotifyReport': {'pNotifyInfoRpt': 'OesNotifyInfoReportT'},
 'OnReportSynchronizationRsp': {'pReportSynchronization': 'OesReportSynchronizationRspT'},
 'OnQueryOrder': {'pOrder': 'OesOrdItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryTrade': {'pTrade': 'OesTrdItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryCashAsset': {'pCashAsset': 'OesCashAssetItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryStkHolding': {'pStkHolding': 'OesStkHoldingItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryLotWinning': {'pLotWinning': 'OesLotWinningItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryCustInfo': {'pCust': 'OesCustItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryInvAcct': {'pInvAcct': 'OesInvAcctItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryCommissionRate': {'pCommissionRate': 'OesCommissionRateItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryFundTransferSerial': {'pFundTrsf': 'OesFundTransferSerialItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryIssue': {'pIssue': 'OesIssueItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryStock': {'pStock': 'OesStockItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryEtf':{'pEtf': 'OesEtfItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryEtfComponent': {'pEtfComponent': 'OesEtfComponentItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryMarketState': {'pMarketState': 'OesMarketStateItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryOption': {'pOption': 'OesOptionItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryOptHolding': {'pOptHolding': 'OesOptHoldingItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryOptUnderlyingHolding': {'pUnderlyingHld': 'OesOptUnderlyingHoldingItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryOptPositionLimit': {'pPositionLimit': 'OesOptPositionLimitItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryOptPurchaseLimit': {'pPurchaseLimit': 'OesOptPurchaseLimitItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryOptExerciseAssign': {'pExerciseAssign': 'OesOptExerciseAssignItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'},
 'OnQueryNotifyInfo': {'pNotifyInfo': 'OesNotifyInfoItemT', 'pCursor': 'OesQryCursorT', 'requestId': 'int32'}