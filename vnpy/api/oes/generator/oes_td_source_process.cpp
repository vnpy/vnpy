void TdApi::processBusinessReject(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		OesRptMsgHeadT *task_error = (OesRptMsgHeadT*)task->task_error;
		delete task_error;
	}
	dict data;
	if (task->task_data)
	{
		OesOrdRejectT *task_data = (OesOrdRejectT*)task->task_data;
		data["clSeqNo"] = task_data->clSeqNo;
		data["mktId"] = task_data->mktId;
		data["ordType"] = task_data->ordType;
		data["bsType"] = task_data->bsType;
		data["__ORD_BASE_INFO_filler"] = task_data->__ORD_BASE_INFO_filler;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["ordQty"] = task_data->ordQty;
		data["ordPrice"] = task_data->ordPrice;
		data["origClOrdId"] = task_data->origClOrdId;
		data["__ordReqOrigSendTime"] = task_data->__ordReqOrigSendTime;
		data["origClSeqNo"] = task_data->origClSeqNo;
		data["origClEnvId"] = task_data->origClEnvId;
		data["clEnvId"] = task_data->clEnvId;
		data["clientId"] = task_data->clientId;
		data["ordDate"] = task_data->ordDate;
		data["ordTime"] = task_data->ordTime;
		data["ordRejReason"] = task_data->ordRejReason;
		data["__filler"] = task_data->__filler;
		delete task_data;
	}
	this->onBusinessReject(error, data);
};

void TdApi::processOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		OesRptMsgHeadT *task_error = (OesRptMsgHeadT*)task->task_error;
		delete task_error;
	}
	dict data;
	if (task->task_data)
	{
		OesOrdCnfmT *task_data = (OesOrdCnfmT*)task->task_data;
		data["clSeqNo"] = task_data->clSeqNo;
		data["mktId"] = task_data->mktId;
		data["ordType"] = task_data->ordType;
		data["bsType"] = task_data->bsType;
		data["__ORD_BASE_INFO_filler"] = task_data->__ORD_BASE_INFO_filler;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["ordQty"] = task_data->ordQty;
		data["ordPrice"] = task_data->ordPrice;
		data["origClOrdId"] = task_data->origClOrdId;
		data["__ordReqOrigSendTime"] = task_data->__ordReqOrigSendTime;
		data["clOrdId"] = task_data->clOrdId;
		data["clientId"] = task_data->clientId;
		data["clEnvId"] = task_data->clEnvId;
		data["origClEnvId"] = task_data->origClEnvId;
		data["origClSeqNo"] = task_data->origClSeqNo;
		data["ordDate"] = task_data->ordDate;
		data["ordTime"] = task_data->ordTime;
		data["ordCnfmTime"] = task_data->ordCnfmTime;
		data["ordStatus"] = task_data->ordStatus;
		data["ordCnfmSts"] = task_data->ordCnfmSts;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["__platformId"] = task_data->__platformId;
		data["__tgwGrpNo"] = task_data->__tgwGrpNo;
		data["__tgwPartitionNo"] = task_data->__tgwPartitionNo;
		data["productType"] = task_data->productType;
		data["exchOrdId"] = toUtf(task_data->exchOrdId);
		data["__declareFlag"] = task_data->__declareFlag;
		data["__repeatFlag"] = task_data->__repeatFlag;
		data["ownerType"] = task_data->ownerType;
		data["frzAmt"] = task_data->frzAmt;
		data["frzInterest"] = task_data->frzInterest;
		data["frzFee"] = task_data->frzFee;
		data["cumAmt"] = task_data->cumAmt;
		data["cumInterest"] = task_data->cumInterest;
		data["cumFee"] = task_data->cumFee;
		data["cumQty"] = task_data->cumQty;
		data["canceledQty"] = task_data->canceledQty;
		data["ordRejReason"] = task_data->ordRejReason;
		data["exchErrCode"] = task_data->exchErrCode;
		data["pbuId"] = task_data->pbuId;
		data["branchId"] = task_data->branchId;
		data["__rowNum"] = task_data->__rowNum;
		data["__recNum"] = task_data->__recNum;
		data["__ordReqOrigRecvTime"] = task_data->__ordReqOrigRecvTime;
		data["__ordReqCollectedTime"] = task_data->__ordReqCollectedTime;
		data["__ordReqActualDealTime"] = task_data->__ordReqActualDealTime;
		data["__ordReqProcessedTime"] = task_data->__ordReqProcessedTime;
		data["__ordCnfmOrigRecvTime"] = task_data->__ordCnfmOrigRecvTime;
		data["__ordCnfmCollectedTime"] = task_data->__ordCnfmCollectedTime;
		data["__ordCnfmActualDealTime"] = task_data->__ordCnfmActualDealTime;
		data["__ordCnfmProcessedTime"] = task_data->__ordCnfmProcessedTime;
		data["__ordDeclareTime"] = task_data->__ordDeclareTime;
		data["__ordDeclareDoneTime"] = task_data->__ordDeclareDoneTime;
		data["__pushingTime"] = task_data->__pushingTime;
		data["frzMargin"] = task_data->frzMargin;
		data["cumMargin"] = task_data->cumMargin;
		data["__ORD_CNFM_EXT_reserve"] = toUtf(task_data->__ORD_CNFM_EXT_reserve);
		delete task_data;
	}
	this->onOrderInsert(error, data);
};

void TdApi::processOrderReport(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		OesRptMsgHeadT *task_error = (OesRptMsgHeadT*)task->task_error;
		delete task_error;
	}
	dict data;
	if (task->task_data)
	{
		OesOrdCnfmT *task_data = (OesOrdCnfmT*)task->task_data;
		data["clSeqNo"] = task_data->clSeqNo;
		data["mktId"] = task_data->mktId;
		data["ordType"] = task_data->ordType;
		data["bsType"] = task_data->bsType;
		data["__ORD_BASE_INFO_filler"] = task_data->__ORD_BASE_INFO_filler;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["ordQty"] = task_data->ordQty;
		data["ordPrice"] = task_data->ordPrice;
		data["origClOrdId"] = task_data->origClOrdId;
		data["__ordReqOrigSendTime"] = task_data->__ordReqOrigSendTime;
		data["clOrdId"] = task_data->clOrdId;
		data["clientId"] = task_data->clientId;
		data["clEnvId"] = task_data->clEnvId;
		data["origClEnvId"] = task_data->origClEnvId;
		data["origClSeqNo"] = task_data->origClSeqNo;
		data["ordDate"] = task_data->ordDate;
		data["ordTime"] = task_data->ordTime;
		data["ordCnfmTime"] = task_data->ordCnfmTime;
		data["ordStatus"] = task_data->ordStatus;
		data["ordCnfmSts"] = task_data->ordCnfmSts;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["__platformId"] = task_data->__platformId;
		data["__tgwGrpNo"] = task_data->__tgwGrpNo;
		data["__tgwPartitionNo"] = task_data->__tgwPartitionNo;
		data["productType"] = task_data->productType;
		data["exchOrdId"] = toUtf(task_data->exchOrdId);
		data["__declareFlag"] = task_data->__declareFlag;
		data["__repeatFlag"] = task_data->__repeatFlag;
		data["ownerType"] = task_data->ownerType;
		data["frzAmt"] = task_data->frzAmt;
		data["frzInterest"] = task_data->frzInterest;
		data["frzFee"] = task_data->frzFee;
		data["cumAmt"] = task_data->cumAmt;
		data["cumInterest"] = task_data->cumInterest;
		data["cumFee"] = task_data->cumFee;
		data["cumQty"] = task_data->cumQty;
		data["canceledQty"] = task_data->canceledQty;
		data["ordRejReason"] = task_data->ordRejReason;
		data["exchErrCode"] = task_data->exchErrCode;
		data["pbuId"] = task_data->pbuId;
		data["branchId"] = task_data->branchId;
		data["__rowNum"] = task_data->__rowNum;
		data["__recNum"] = task_data->__recNum;
		data["__ordReqOrigRecvTime"] = task_data->__ordReqOrigRecvTime;
		data["__ordReqCollectedTime"] = task_data->__ordReqCollectedTime;
		data["__ordReqActualDealTime"] = task_data->__ordReqActualDealTime;
		data["__ordReqProcessedTime"] = task_data->__ordReqProcessedTime;
		data["__ordCnfmOrigRecvTime"] = task_data->__ordCnfmOrigRecvTime;
		data["__ordCnfmCollectedTime"] = task_data->__ordCnfmCollectedTime;
		data["__ordCnfmActualDealTime"] = task_data->__ordCnfmActualDealTime;
		data["__ordCnfmProcessedTime"] = task_data->__ordCnfmProcessedTime;
		data["__ordDeclareTime"] = task_data->__ordDeclareTime;
		data["__ordDeclareDoneTime"] = task_data->__ordDeclareDoneTime;
		data["__pushingTime"] = task_data->__pushingTime;
		data["frzMargin"] = task_data->frzMargin;
		data["cumMargin"] = task_data->cumMargin;
		data["__ORD_CNFM_EXT_reserve"] = toUtf(task_data->__ORD_CNFM_EXT_reserve);
		delete task_data;
	}
	this->onOrderReport(error, data);
};

void TdApi::processTradeReport(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		OesRptMsgHeadT *task_error = (OesRptMsgHeadT*)task->task_error;
		delete task_error;
	}
	dict data;
	if (task->task_data)
	{
		OesTrdCnfmT *task_data = (OesTrdCnfmT*)task->task_data;
		data["exchTrdNum"] = task_data->exchTrdNum;
		data["mktId"] = task_data->mktId;
		data["trdSide"] = task_data->trdSide;
		data["__platformId"] = task_data->__platformId;
		data["__trdCnfmType"] = task_data->__trdCnfmType;
		data["__etfTrdCnfmSeq"] = task_data->__etfTrdCnfmSeq;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["trdDate"] = task_data->trdDate;
		data["trdTime"] = task_data->trdTime;
		data["trdQty"] = task_data->trdQty;
		data["trdPrice"] = task_data->trdPrice;
		data["trdAmt"] = task_data->trdAmt;
		data["clOrdId"] = task_data->clOrdId;
		data["cumQty"] = task_data->cumQty;
		data["__rowNum"] = task_data->__rowNum;
		data["__tgwGrpNo"] = task_data->__tgwGrpNo;
		data["__isTrsfInCashAvailable"] = task_data->__isTrsfInCashAvailable;
		data["__tgwPartitionNo"] = task_data->__tgwPartitionNo;
		data["productType"] = task_data->productType;
		data["origOrdQty"] = task_data->origOrdQty;
		data["pbuId"] = task_data->pbuId;
		data["branchId"] = task_data->branchId;
		data["clSeqNo"] = task_data->clSeqNo;
		data["clientId"] = task_data->clientId;
		data["clEnvId"] = task_data->clEnvId;
		data["subSecurityType"] = task_data->subSecurityType;
		data["ordStatus"] = task_data->ordStatus;
		data["ordType"] = task_data->ordType;
		data["ordBuySellType"] = task_data->ordBuySellType;
		data["securityType"] = task_data->securityType;
		data["origOrdPrice"] = task_data->origOrdPrice;
		data["cumAmt"] = task_data->cumAmt;
		data["cumInterest"] = task_data->cumInterest;
		data["cumFee"] = task_data->cumFee;
		data["__trdCnfmOrigRecvTime"] = task_data->__trdCnfmOrigRecvTime;
		data["__trdCnfmCollectedTime"] = task_data->__trdCnfmCollectedTime;
		data["__trdCnfmActualDealTime"] = task_data->__trdCnfmActualDealTime;
		data["__trdCnfmProcessedTime"] = task_data->__trdCnfmProcessedTime;
		data["__pushingTime"] = task_data->__pushingTime;
		data["trdInterest"] = task_data->trdInterest;
		data["trdFee"] = task_data->trdFee;
		data["trdMargin"] = task_data->trdMargin;
		data["cumMargin"] = task_data->cumMargin;
		data["__TRD_CNFM_EXT_reserve"] = toUtf(task_data->__TRD_CNFM_EXT_reserve);
		delete task_data;
	}
	this->onTradeReport(error, data);
};

void TdApi::processCashAssetVariation(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesCashAssetReportT *task_data = (OesCashAssetReportT*)task->task_data;
		data["cashAcctId"] = toUtf(task_data->cashAcctId);
		data["custId"] = toUtf(task_data->custId);
		data["currType"] = task_data->currType;
		data["cashType"] = task_data->cashType;
		data["cashAcctStatus"] = task_data->cashAcctStatus;
		data["isFundTrsfDisabled"] = task_data->isFundTrsfDisabled;
		data["__CASH_ASSET_BASE_filler"] = task_data->__CASH_ASSET_BASE_filler;
		data["beginningBal"] = task_data->beginningBal;
		data["beginningAvailableBal"] = task_data->beginningAvailableBal;
		data["beginningDrawableBal"] = task_data->beginningDrawableBal;
		data["disableBal"] = task_data->disableBal;
		data["reversalAmt"] = task_data->reversalAmt;
		data["manualFrzAmt"] = task_data->manualFrzAmt;
		data["totalDepositAmt"] = task_data->totalDepositAmt;
		data["totalWithdrawAmt"] = task_data->totalWithdrawAmt;
		data["withdrawFrzAmt"] = task_data->withdrawFrzAmt;
		data["totalSellAmt"] = task_data->totalSellAmt;
		data["totalBuyAmt"] = task_data->totalBuyAmt;
		data["buyFrzAmt"] = task_data->buyFrzAmt;
		data["totalFeeAmt"] = task_data->totalFeeAmt;
		data["feeFrzAmt"] = task_data->feeFrzAmt;
		data["marginAmt"] = task_data->marginAmt;
		data["marginFrzAmt"] = task_data->marginFrzAmt;
		data["currentTotalBal"] = task_data->currentTotalBal;
		data["currentAvailableBal"] = task_data->currentAvailableBal;
		data["currentDrawableBal"] = task_data->currentDrawableBal;
		data["{"] = task_data->{;
		data["initialMargin"] = task_data->initialMargin;
		data["totalExerciseFrzAmt"] = task_data->totalExerciseFrzAmt;
		data["pendingSupplMargin"] = task_data->pendingSupplMargin;
		data["sseAvailablePurchaseLimit"] = task_data->sseAvailablePurchaseLimit;
		data["szseAvailablePurchaseLimit"] = task_data->szseAvailablePurchaseLimit;
		data["totalMarketMargin"] = task_data->totalMarketMargin;
		data["totalNetMargin"] = task_data->totalNetMargin;
		data["optionExt"] = task_data->optionExt;
		data["__CASH_ASSET_EXT_reserve"] = toUtf(task_data->__CASH_ASSET_EXT_reserve);
		delete task_data;
	}
	this->onCashAssetVariation(data);
};

void TdApi::processStockHoldingVariation(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesStkHoldingReportT *task_data = (OesStkHoldingReportT*)task->task_data;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["mktId"] = task_data->mktId;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["productType"] = task_data->productType;
		data["__HOLD_BASE_filler"] = task_data->__HOLD_BASE_filler;
		data["originalHld"] = task_data->originalHld;
		data["originalCostAmt"] = task_data->originalCostAmt;
		data["totalBuyHld"] = task_data->totalBuyHld;
		data["totalSellHld"] = task_data->totalSellHld;
		data["sellFrzHld"] = task_data->sellFrzHld;
		data["manualFrzHld"] = task_data->manualFrzHld;
		data["totalBuyAmt"] = task_data->totalBuyAmt;
		data["totalSellAmt"] = task_data->totalSellAmt;
		data["totalBuyFee"] = task_data->totalBuyFee;
		data["totalSellFee"] = task_data->totalSellFee;
		data["totalTrsfInHld"] = task_data->totalTrsfInHld;
		data["totalTrsfOutHld"] = task_data->totalTrsfOutHld;
		data["trsfOutFrzHld"] = task_data->trsfOutFrzHld;
		data["originalLockHld"] = task_data->originalLockHld;
		data["totalLockHld"] = task_data->totalLockHld;
		data["totalUnlockHld"] = task_data->totalUnlockHld;
		data["originalAvlHld"] = task_data->originalAvlHld;
		data["maxReduceQuota"] = task_data->maxReduceQuota;
		data["sellAvlHld"] = task_data->sellAvlHld;
		data["trsfOutAvlHld"] = task_data->trsfOutAvlHld;
		data["lockAvlHld"] = task_data->lockAvlHld;
		data["__filler"] = task_data->__filler;
		data["sumHld"] = task_data->sumHld;
		data["costPrice"] = task_data->costPrice;
		delete task_data;
	}
	this->onStockHoldingVariation(data);
};

void TdApi::processOptionHoldingVariation(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptHoldingReportT *task_data = (OesOptHoldingReportT*)task->task_data;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["mktId"] = task_data->mktId;
		data["positionType"] = task_data->positionType;
		data["productType"] = task_data->productType;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["contractType"] = task_data->contractType;
		data["hedgeFlag"] = task_data->hedgeFlag;
		data["__HOLD_BASE_filler"] = task_data->__HOLD_BASE_filler;
		data["originalQty"] = task_data->originalQty;
		data["originalAvlQty"] = task_data->originalAvlQty;
		data["originalCostAmt"] = task_data->originalCostAmt;
		data["originalCarryingAmt"] = task_data->originalCarryingAmt;
		data["totalOpenQty"] = task_data->totalOpenQty;
		data["uncomeQty"] = task_data->uncomeQty;
		data["totalCloseQty"] = task_data->totalCloseQty;
		data["closeFrzQty"] = task_data->closeFrzQty;
		data["manualFrzQty"] = task_data->manualFrzQty;
		data["totalInPremium"] = task_data->totalInPremium;
		data["totalOutPremium"] = task_data->totalOutPremium;
		data["totalOpenFee"] = task_data->totalOpenFee;
		data["totalCloseFee"] = task_data->totalCloseFee;
		data["exerciseFrzQty"] = task_data->exerciseFrzQty;
		data["positionMargin"] = task_data->positionMargin;
		data["__OPT_HOLDING_BASE_reserve"] = toUtf(task_data->__OPT_HOLDING_BASE_reserve);
		data["closeAvlQty"] = task_data->closeAvlQty;
		data["exerciseAvlQty"] = task_data->exerciseAvlQty;
		data["sumQty"] = task_data->sumQty;
		data["costPrice"] = task_data->costPrice;
		data["carryingAvgPrice"] = task_data->carryingAvgPrice;
		data["coveredAvlUnderlyingQty"] = task_data->coveredAvlUnderlyingQty;
		data["availableLongPositionLimit"] = task_data->availableLongPositionLimit;
		data["availableTotalPositionLimit"] = task_data->availableTotalPositionLimit;
		data["availableDailyBuyOpenLimit"] = task_data->availableDailyBuyOpenLimit;
		data["__OPT_HOLDING_EXT_filler2"] = task_data->__OPT_HOLDING_EXT_filler2;
		data["__OPT_HOLDING_EXT_reserve"] = toUtf(task_data->__OPT_HOLDING_EXT_reserve);
		delete task_data;
	}
	this->onOptionHoldingVariation(data);
};

void TdApi::processOptionUnderlyingHoldingVariation(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptUnderlyingHoldingReportT *task_data = (OesOptUnderlyingHoldingReportT*)task->task_data;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["underlyingSecurityId"] = toUtf(task_data->underlyingSecurityId);
		data["mktId"] = task_data->mktId;
		data["underlyingMktId"] = task_data->underlyingMktId;
		data["underlyingSecurityType"] = task_data->underlyingSecurityType;
		data["underlyingSubSecurityType"] = task_data->underlyingSubSecurityType;
		data["__OPT_UNDERLYING_HOLD_BASE_filler"] = task_data->__OPT_UNDERLYING_HOLD_BASE_filler;
		data["originalHld"] = task_data->originalHld;
		data["originalAvlHld"] = task_data->originalAvlHld;
		data["originalCoveredQty"] = task_data->originalCoveredQty;
		data["initialCoveredQty"] = task_data->initialCoveredQty;
		data["coveredQty"] = task_data->coveredQty;
		data["coveredGapQty"] = task_data->coveredGapQty;
		data["coveredAvlQty"] = task_data->coveredAvlQty;
		data["lockAvlQty"] = task_data->lockAvlQty;
		data["sumHld"] = task_data->sumHld;
		data["maxReduceQuota"] = task_data->maxReduceQuota;
		delete task_data;
	}
	this->onOptionUnderlyingHoldingVariation(data);
};

void TdApi::processSettlementConfirmedRpt(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		OesRptMsgHeadT *task_error = (OesRptMsgHeadT*)task->task_error;
		delete task_error;
	}
	dict data;
	if (task->task_data)
	{
		OesOptSettlementConfirmReportT *task_data = (OesOptSettlementConfirmReportT*)task->task_data;
		data["custId"] = toUtf(task_data->custId);
		data["clientId"] = task_data->clientId;
		data["clEnvId"] = task_data->clEnvId;
		data["__filler2"] = task_data->__filler2;
		data["transDate"] = task_data->transDate;
		data["transTime"] = task_data->transTime;
		data["rejReason"] = task_data->rejReason;
		data["__OPT_SETTLEMENT_CONFIRM_BASE_reserve"] = toUtf(task_data->__OPT_SETTLEMENT_CONFIRM_BASE_reserve);
		delete task_data;
	}
	this->onSettlementConfirmedRpt(error, data);
};

void TdApi::processFundTrsfReject(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		OesRptMsgHeadT *task_error = (OesRptMsgHeadT*)task->task_error;
		delete task_error;
	}
	dict data;
	if (task->task_data)
	{
		OesFundTrsfRejectT *task_data = (OesFundTrsfRejectT*)task->task_data;
		data["clSeqNo"] = task_data->clSeqNo;
		data["direct"] = task_data->direct;
		data["isAllotOnly"] = task_data->isAllotOnly;
		data["__FUND_TRSF_BASE_filler"] = task_data->__FUND_TRSF_BASE_filler;
		data["cashAcctId"] = toUtf(task_data->cashAcctId);
		data["trdPasswd"] = toUtf(task_data->trdPasswd);
		data["trsfPasswd"] = toUtf(task_data->trsfPasswd);
		data["occurAmt"] = task_data->occurAmt;
		data["ordDate"] = task_data->ordDate;
		data["ordTime"] = task_data->ordTime;
		data["clientId"] = task_data->clientId;
		data["clEnvId"] = task_data->clEnvId;
		data["__filler"] = task_data->__filler;
		data["rejReason"] = task_data->rejReason;
		data["errorInfo"] = toUtf(task_data->errorInfo);
		delete task_data;
	}
	this->onFundTrsfReject(error, data);
};

void TdApi::processFundTrsfReport(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		OesRptMsgHeadT *task_error = (OesRptMsgHeadT*)task->task_error;
		delete task_error;
	}
	dict data;
	if (task->task_data)
	{
		OesFundTrsfReportT *task_data = (OesFundTrsfReportT*)task->task_data;
		data["clSeqNo"] = task_data->clSeqNo;
		data["clientId"] = task_data->clientId;
		data["clEnvId"] = task_data->clEnvId;
		data["direct"] = task_data->direct;
		data["cashAcctId"] = toUtf(task_data->cashAcctId);
		data["occurAmt"] = task_data->occurAmt;
		delete task_data;
	}
	this->onFundTrsfReport(error, data);
};

void TdApi::processMarketState(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesMarketStateItemT *task_data = (OesMarketStateItemT*)task->task_data;
		data["pMarketStateItem"] = toUtf(task_data->pMarketStateItem);
		delete task_data;
	}
	this->onMarketState(data);
};

void TdApi::processNotifyReport(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesNotifyInfoReportT *task_data = (OesNotifyInfoReportT*)task->task_data;
		data["notifySeqNo"] = task_data->notifySeqNo;
		data["notifySource"] = task_data->notifySource;
		data["notifyType"] = task_data->notifyType;
		data["notifyLevel"] = task_data->notifyLevel;
		data["notifyScope"] = task_data->notifyScope;
		data["tranTime"] = task_data->tranTime;
		data["__NOTIFY_INFO_filler"] = task_data->__NOTIFY_INFO_filler;
		data["custId"] = toUtf(task_data->custId);
		data["content"] = toUtf(task_data->content);
		delete task_data;
	}
	this->onNotifyReport(data);
};

void TdApi::processReportSynchronizationRsp(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesReportSynchronizationRspT *task_data = (OesReportSynchronizationRspT*)task->task_data;
		data["lastRptSeqNum"] = task_data->lastRptSeqNum;
		data["subscribeEnvId"] = task_data->subscribeEnvId;
		data["__filler"] = task_data->__filler;
		data["subscribeRptTypes"] = task_data->subscribeRptTypes;
		delete task_data;
	}
	this->onReportSynchronizationRsp(data);
};

void TdApi::processQueryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOrdItemT *task_data = (OesOrdItemT*)task->task_data;
		data["pOrder"] = toUtf(task_data->pOrder);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryOrder(data, error, task->task_id);
};

void TdApi::processQueryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesTrdItemT *task_data = (OesTrdItemT*)task->task_data;
		data["pTrade"] = toUtf(task_data->pTrade);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryTrade(data, error, task->task_id);
};

void TdApi::processQueryCashAsset(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesCashAssetItemT *task_data = (OesCashAssetItemT*)task->task_data;
		data["cashAcctId"] = toUtf(task_data->cashAcctId);
		data["custId"] = toUtf(task_data->custId);
		data["currType"] = task_data->currType;
		data["cashType"] = task_data->cashType;
		data["cashAcctStatus"] = task_data->cashAcctStatus;
		data["isFundTrsfDisabled"] = task_data->isFundTrsfDisabled;
		data["__CASH_ASSET_BASE_filler"] = task_data->__CASH_ASSET_BASE_filler;
		data["beginningBal"] = task_data->beginningBal;
		data["beginningAvailableBal"] = task_data->beginningAvailableBal;
		data["beginningDrawableBal"] = task_data->beginningDrawableBal;
		data["disableBal"] = task_data->disableBal;
		data["reversalAmt"] = task_data->reversalAmt;
		data["manualFrzAmt"] = task_data->manualFrzAmt;
		data["totalDepositAmt"] = task_data->totalDepositAmt;
		data["totalWithdrawAmt"] = task_data->totalWithdrawAmt;
		data["withdrawFrzAmt"] = task_data->withdrawFrzAmt;
		data["totalSellAmt"] = task_data->totalSellAmt;
		data["totalBuyAmt"] = task_data->totalBuyAmt;
		data["buyFrzAmt"] = task_data->buyFrzAmt;
		data["totalFeeAmt"] = task_data->totalFeeAmt;
		data["feeFrzAmt"] = task_data->feeFrzAmt;
		data["marginAmt"] = task_data->marginAmt;
		data["marginFrzAmt"] = task_data->marginFrzAmt;
		data["currentTotalBal"] = task_data->currentTotalBal;
		data["currentAvailableBal"] = task_data->currentAvailableBal;
		data["currentDrawableBal"] = task_data->currentDrawableBal;
		data["{"] = task_data->{;
		data["initialMargin"] = task_data->initialMargin;
		data["totalExerciseFrzAmt"] = task_data->totalExerciseFrzAmt;
		data["pendingSupplMargin"] = task_data->pendingSupplMargin;
		data["sseAvailablePurchaseLimit"] = task_data->sseAvailablePurchaseLimit;
		data["szseAvailablePurchaseLimit"] = task_data->szseAvailablePurchaseLimit;
		data["totalMarketMargin"] = task_data->totalMarketMargin;
		data["totalNetMargin"] = task_data->totalNetMargin;
		data["optionExt"] = task_data->optionExt;
		data["__CASH_ASSET_EXT_reserve"] = toUtf(task_data->__CASH_ASSET_EXT_reserve);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryCashAsset(data, error, task->task_id);
};

void TdApi::processQueryStkHolding(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesStkHoldingItemT *task_data = (OesStkHoldingItemT*)task->task_data;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["mktId"] = task_data->mktId;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["productType"] = task_data->productType;
		data["__HOLD_BASE_filler"] = task_data->__HOLD_BASE_filler;
		data["originalHld"] = task_data->originalHld;
		data["originalCostAmt"] = task_data->originalCostAmt;
		data["totalBuyHld"] = task_data->totalBuyHld;
		data["totalSellHld"] = task_data->totalSellHld;
		data["sellFrzHld"] = task_data->sellFrzHld;
		data["manualFrzHld"] = task_data->manualFrzHld;
		data["totalBuyAmt"] = task_data->totalBuyAmt;
		data["totalSellAmt"] = task_data->totalSellAmt;
		data["totalBuyFee"] = task_data->totalBuyFee;
		data["totalSellFee"] = task_data->totalSellFee;
		data["totalTrsfInHld"] = task_data->totalTrsfInHld;
		data["totalTrsfOutHld"] = task_data->totalTrsfOutHld;
		data["trsfOutFrzHld"] = task_data->trsfOutFrzHld;
		data["originalLockHld"] = task_data->originalLockHld;
		data["totalLockHld"] = task_data->totalLockHld;
		data["totalUnlockHld"] = task_data->totalUnlockHld;
		data["originalAvlHld"] = task_data->originalAvlHld;
		data["maxReduceQuota"] = task_data->maxReduceQuota;
		data["sellAvlHld"] = task_data->sellAvlHld;
		data["trsfOutAvlHld"] = task_data->trsfOutAvlHld;
		data["lockAvlHld"] = task_data->lockAvlHld;
		data["__filler"] = task_data->__filler;
		data["sumHld"] = task_data->sumHld;
		data["costPrice"] = task_data->costPrice;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryStkHolding(data, error, task->task_id);
};

void TdApi::processQueryLotWinning(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesLotWinningItemT *task_data = (OesLotWinningItemT*)task->task_data;
		data["pLotWinning"] = toUtf(task_data->pLotWinning);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryLotWinning(data, error, task->task_id);
};

void TdApi::processQueryCustInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesCustItemT *task_data = (OesCustItemT*)task->task_data;
		data["pCust"] = toUtf(task_data->pCust);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryCustInfo(data, error, task->task_id);
};

void TdApi::processQueryInvAcct(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesInvAcctItemT *task_data = (OesInvAcctItemT*)task->task_data;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["mktId"] = task_data->mktId;
		data["acctType"] = task_data->acctType;
		data["status"] = task_data->status;
		data["ownerType"] = task_data->ownerType;
		data["optInvLevel"] = task_data->optInvLevel;
		data["isTradeDisabled"] = task_data->isTradeDisabled;
		data["__INV_ACCT_BASE_filler"] = task_data->__INV_ACCT_BASE_filler;
		data["limits"] = task_data->limits;
		data["permissions"] = task_data->permissions;
		data["pbuId"] = task_data->pbuId;
		data["stkPositionLimitRatio"] = task_data->stkPositionLimitRatio;
		data["subscriptionQuota"] = task_data->subscriptionQuota;
		data["kcSubscriptionQuota"] = task_data->kcSubscriptionQuota;
		data["__INV_ACCT_BASE_reserve"] = toUtf(task_data->__INV_ACCT_BASE_reserve);
		data["custId"] = toUtf(task_data->custId);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryInvAcct(data, error, task->task_id);
};

void TdApi::processQueryCommissionRate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesCommissionRateItemT *task_data = (OesCommissionRateItemT*)task->task_data;
		data["custId"] = toUtf(task_data->custId);
		data["securityId"] = toUtf(task_data->securityId);
		data["mktId"] = task_data->mktId;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["bsType"] = task_data->bsType;
		data["feeType"] = task_data->feeType;
		data["currType"] = task_data->currType;
		data["calcFeeMode"] = task_data->calcFeeMode;
		data["__filler"] = task_data->__filler;
		data["feeRate"] = task_data->feeRate;
		data["minFee"] = task_data->minFee;
		data["maxFee"] = task_data->maxFee;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryCommissionRate(data, error, task->task_id);
};

void TdApi::processQueryFundTransferSerial(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesFundTransferSerialItemT *task_data = (OesFundTransferSerialItemT*)task->task_data;
		data["pFundTrsf"] = toUtf(task_data->pFundTrsf);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryFundTransferSerial(data, error, task->task_id);
};

void TdApi::processQueryIssue(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesIssueItemT *task_data = (OesIssueItemT*)task->task_data;
		data["pIssue"] = toUtf(task_data->pIssue);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryIssue(data, error, task->task_id);
};

void TdApi::processQueryStock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesStockItemT *task_data = (OesStockItemT*)task->task_data;
		data["pStock"] = toUtf(task_data->pStock);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryStock(data, error, task->task_id);
};

void TdApi::processQueryEtf(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesEtfItemT *task_data = (OesEtfItemT*)task->task_data;
		data["pEtf"] = toUtf(task_data->pEtf);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryEtf(data, error, task->task_id);
};

void TdApi::processQueryEtfComponent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesEtfComponentItemT *task_data = (OesEtfComponentItemT*)task->task_data;
		data["securityId"] = toUtf(task_data->securityId);
		data["mktId"] = task_data->mktId;
		data["subFlag"] = task_data->subFlag;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["prevClose"] = task_data->prevClose;
		data["qty"] = task_data->qty;
		data["premiumRate"] = task_data->premiumRate;
		data["creationSubCash"] = task_data->creationSubCash;
		data["redemptionCashSub"] = task_data->redemptionCashSub;
		data["fundId"] = toUtf(task_data->fundId);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryEtfComponent(data, error, task->task_id);
};

void TdApi::processQueryMarketState(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesMarketStateItemT *task_data = (OesMarketStateItemT*)task->task_data;
		data["pMarketState"] = toUtf(task_data->pMarketState);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryMarketState(data, error, task->task_id);
};

void TdApi::processQueryOption(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptionItemT *task_data = (OesOptionItemT*)task->task_data;
		data["pOption"] = toUtf(task_data->pOption);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryOption(data, error, task->task_id);
};

void TdApi::processQueryOptHolding(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptHoldingItemT *task_data = (OesOptHoldingItemT*)task->task_data;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["securityId"] = toUtf(task_data->securityId);
		data["mktId"] = task_data->mktId;
		data["positionType"] = task_data->positionType;
		data["productType"] = task_data->productType;
		data["securityType"] = task_data->securityType;
		data["subSecurityType"] = task_data->subSecurityType;
		data["contractType"] = task_data->contractType;
		data["hedgeFlag"] = task_data->hedgeFlag;
		data["__HOLD_BASE_filler"] = task_data->__HOLD_BASE_filler;
		data["originalQty"] = task_data->originalQty;
		data["originalAvlQty"] = task_data->originalAvlQty;
		data["originalCostAmt"] = task_data->originalCostAmt;
		data["originalCarryingAmt"] = task_data->originalCarryingAmt;
		data["totalOpenQty"] = task_data->totalOpenQty;
		data["uncomeQty"] = task_data->uncomeQty;
		data["totalCloseQty"] = task_data->totalCloseQty;
		data["closeFrzQty"] = task_data->closeFrzQty;
		data["manualFrzQty"] = task_data->manualFrzQty;
		data["totalInPremium"] = task_data->totalInPremium;
		data["totalOutPremium"] = task_data->totalOutPremium;
		data["totalOpenFee"] = task_data->totalOpenFee;
		data["totalCloseFee"] = task_data->totalCloseFee;
		data["exerciseFrzQty"] = task_data->exerciseFrzQty;
		data["positionMargin"] = task_data->positionMargin;
		data["__OPT_HOLDING_BASE_reserve"] = toUtf(task_data->__OPT_HOLDING_BASE_reserve);
		data["closeAvlQty"] = task_data->closeAvlQty;
		data["exerciseAvlQty"] = task_data->exerciseAvlQty;
		data["sumQty"] = task_data->sumQty;
		data["costPrice"] = task_data->costPrice;
		data["carryingAvgPrice"] = task_data->carryingAvgPrice;
		data["coveredAvlUnderlyingQty"] = task_data->coveredAvlUnderlyingQty;
		data["availableLongPositionLimit"] = task_data->availableLongPositionLimit;
		data["availableTotalPositionLimit"] = task_data->availableTotalPositionLimit;
		data["availableDailyBuyOpenLimit"] = task_data->availableDailyBuyOpenLimit;
		data["__OPT_HOLDING_EXT_filler2"] = task_data->__OPT_HOLDING_EXT_filler2;
		data["__OPT_HOLDING_EXT_reserve"] = toUtf(task_data->__OPT_HOLDING_EXT_reserve);
		data["contractId"] = toUtf(task_data->contractId);
		data["contractSymbol"] = toUtf(task_data->contractSymbol);
		data["prevSettlPrice"] = task_data->prevSettlPrice;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryOptHolding(data, error, task->task_id);
};

void TdApi::processQueryOptUnderlyingHolding(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptUnderlyingHoldingItemT *task_data = (OesOptUnderlyingHoldingItemT*)task->task_data;
		data["pUnderlyingHld"] = toUtf(task_data->pUnderlyingHld);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryOptUnderlyingHolding(data, error, task->task_id);
};

void TdApi::processQueryOptPositionLimit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptPositionLimitItemT *task_data = (OesOptPositionLimitItemT*)task->task_data;
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["underlyingSecurityId"] = toUtf(task_data->underlyingSecurityId);
		data["mktId"] = task_data->mktId;
		data["underlyingMktId"] = task_data->underlyingMktId;
		data["underlyingSecurityType"] = task_data->underlyingSecurityType;
		data["underlyingSubSecurityType"] = task_data->underlyingSubSecurityType;
		data["__filler1"] = task_data->__filler1;
		data["longPositionLimit"] = task_data->longPositionLimit;
		data["totalPositionLimit"] = task_data->totalPositionLimit;
		data["dailyBuyOpenLimit"] = task_data->dailyBuyOpenLimit;
		data["__filler2"] = task_data->__filler2;
		data["originalLongQty"] = task_data->originalLongQty;
		data["originalShortQty"] = task_data->originalShortQty;
		data["originalCoveredQty"] = task_data->originalCoveredQty;
		data["availableLongPositionLimit"] = task_data->availableLongPositionLimit;
		data["availableTotalPositionLimit"] = task_data->availableTotalPositionLimit;
		data["availableDailyBuyOpenLimit"] = task_data->availableDailyBuyOpenLimit;
		data["__reserve"] = toUtf(task_data->__reserve);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryOptPositionLimit(data, error, task->task_id);
};

void TdApi::processQueryOptPurchaseLimit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptPurchaseLimitItemT *task_data = (OesOptPurchaseLimitItemT*)task->task_data;
		data["custId"] = toUtf(task_data->custId);
		data["cashAcctId"] = toUtf(task_data->cashAcctId);
		data["invAcctId"] = toUtf(task_data->invAcctId);
		data["mktId"] = task_data->mktId;
		data["custType"] = task_data->custType;
		data["__filler"] = task_data->__filler;
		data["purchaseLimit"] = task_data->purchaseLimit;
		data["originalUsedPurchaseAmt"] = task_data->originalUsedPurchaseAmt;
		data["totalOpenPurchaseAmt"] = task_data->totalOpenPurchaseAmt;
		data["frzPurchaseAmt"] = task_data->frzPurchaseAmt;
		data["totalClosePurchaseAmt"] = task_data->totalClosePurchaseAmt;
		data["availablePurchaseLimit"] = task_data->availablePurchaseLimit;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryOptPurchaseLimit(data, error, task->task_id);
};

void TdApi::processQueryOptExerciseAssign(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesOptExerciseAssignItemT *task_data = (OesOptExerciseAssignItemT*)task->task_data;
		data["pExerciseAssign"] = toUtf(task_data->pExerciseAssign);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryOptExerciseAssign(data, error, task->task_id);
};

void TdApi::processQueryNotifyInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		OesNotifyInfoItemT *task_data = (OesNotifyInfoItemT*)task->task_data;
		data["pNotifyInfo"] = toUtf(task_data->pNotifyInfo);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		OesQryCursorT *task_error = (OesQryCursorT*)task->task_error;
		error["seqNo"] = task_error->seqNo;
		error["isEnd"] = task_error->isEnd;
		error["__filler"] = task_error->__filler;
		error["userInfo"] = task_error->userInfo;
		delete task_error;
	}
	this->onQueryNotifyInfo(data, error, task->task_id);
};

