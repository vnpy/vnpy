    void TdApi::OnBusinessReject(const OesRptMsgHeadT *pRptMsgHead, const OesOrdRejectT *pOrderReject)
{
	Task task = Task();
	task.task_name = ONBUSINESSREJECT;
	if (pRptMsgHead)
	{
		OesRptMsgHeadT *task_error = new OesRptMsgHeadT();
		*task_error = *pRptMsgHead;
		task.task_error = task_error;
	}
	if (pOrderReject)
	{
		OesOrdRejectT *task_data = new OesOrdRejectT();
		*task_data = *pOrderReject;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnOrderInsert(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderInsert)
{
	Task task = Task();
	task.task_name = ONORDERINSERT;
	if (pRptMsgHead)
	{
		OesRptMsgHeadT *task_error = new OesRptMsgHeadT();
		*task_error = *pRptMsgHead;
		task.task_error = task_error;
	}
	if (pOrderInsert)
	{
		OesOrdCnfmT *task_data = new OesOrdCnfmT();
		*task_data = *pOrderInsert;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnOrderReport(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderReport)
{
	Task task = Task();
	task.task_name = ONORDERREPORT;
	if (pRptMsgHead)
	{
		OesRptMsgHeadT *task_error = new OesRptMsgHeadT();
		*task_error = *pRptMsgHead;
		task.task_error = task_error;
	}
	if (pOrderReport)
	{
		OesOrdCnfmT *task_data = new OesOrdCnfmT();
		*task_data = *pOrderReport;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnTradeReport(const OesRptMsgHeadT *pRptMsgHead, const OesTrdCnfmT *pTradeReport)
{
	Task task = Task();
	task.task_name = ONTRADEREPORT;
	if (pRptMsgHead)
	{
		OesRptMsgHeadT *task_error = new OesRptMsgHeadT();
		*task_error = *pRptMsgHead;
		task.task_error = task_error;
	}
	if (pTradeReport)
	{
		OesTrdCnfmT *task_data = new OesTrdCnfmT();
		*task_data = *pTradeReport;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnCashAssetVariation(const OesCashAssetReportT *pCashAssetRpt)
{
	Task task = Task();
	task.task_name = ONCASHASSETVARIATION;
	if (pCashAssetRpt)
	{
		OesCashAssetReportT *task_data = new OesCashAssetReportT();
		*task_data = *pCashAssetRpt;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnStockHoldingVariation(const OesStkHoldingReportT *pStkHoldingRpt)
{
	Task task = Task();
	task.task_name = ONSTOCKHOLDINGVARIATION;
	if (pStkHoldingRpt)
	{
		OesStkHoldingReportT *task_data = new OesStkHoldingReportT();
		*task_data = *pStkHoldingRpt;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnOptionHoldingVariation(const OesOptHoldingReportT *pOptHoldingRpt)
{
	Task task = Task();
	task.task_name = ONOPTIONHOLDINGVARIATION;
	if (pOptHoldingRpt)
	{
		OesOptHoldingReportT *task_data = new OesOptHoldingReportT();
		*task_data = *pOptHoldingRpt;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnOptionUnderlyingHoldingVariation(const OesOptUnderlyingHoldingReportT *pUnderlyingHoldingRpt)
{
	Task task = Task();
	task.task_name = ONOPTIONUNDERLYINGHOLDINGVARIATION;
	if (pUnderlyingHoldingRpt)
	{
		OesOptUnderlyingHoldingReportT *task_data = new OesOptUnderlyingHoldingReportT();
		*task_data = *pUnderlyingHoldingRpt;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnSettlementConfirmedRpt(const OesRptMsgHeadT *pRptMsgHead, const OesOptSettlementConfirmReportT *pCnfmSettlementRpt)
{
	Task task = Task();
	task.task_name = ONSETTLEMENTCONFIRMEDRPT;
	if (pRptMsgHead)
	{
		OesRptMsgHeadT *task_error = new OesRptMsgHeadT();
		*task_error = *pRptMsgHead;
		task.task_error = task_error;
	}
	if (pCnfmSettlementRpt)
	{
		OesOptSettlementConfirmReportT *task_data = new OesOptSettlementConfirmReportT();
		*task_data = *pCnfmSettlementRpt;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnFundTrsfReject(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfRejectT *pFundTrsfReject)
{
	Task task = Task();
	task.task_name = ONFUNDTRSFREJECT;
	if (pRptMsgHead)
	{
		OesRptMsgHeadT *task_error = new OesRptMsgHeadT();
		*task_error = *pRptMsgHead;
		task.task_error = task_error;
	}
	if (pFundTrsfReject)
	{
		OesFundTrsfRejectT *task_data = new OesFundTrsfRejectT();
		*task_data = *pFundTrsfReject;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnFundTrsfReport(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfReportT *pFundTrsfReport)
{
	Task task = Task();
	task.task_name = ONFUNDTRSFREPORT;
	if (pRptMsgHead)
	{
		OesRptMsgHeadT *task_error = new OesRptMsgHeadT();
		*task_error = *pRptMsgHead;
		task.task_error = task_error;
	}
	if (pFundTrsfReport)
	{
		OesFundTrsfReportT *task_data = new OesFundTrsfReportT();
		*task_data = *pFundTrsfReport;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnMarketState(const OesMarketStateItemT *pMarketStateItem)
{
	Task task = Task();
	task.task_name = ONMARKETSTATE;
	if (pMarketStateItem)
	{
		OesMarketStateItemT *task_data = new OesMarketStateItemT();
		*task_data = *pMarketStateItem;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnNotifyReport(const OesNotifyInfoReportT *pNotifyInfoRpt)
{
	Task task = Task();
	task.task_name = ONNOTIFYREPORT;
	if (pNotifyInfoRpt)
	{
		OesNotifyInfoReportT *task_data = new OesNotifyInfoReportT();
		*task_data = *pNotifyInfoRpt;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnReportSynchronizationRsp(const OesReportSynchronizationRspT *pReportSynchronization)
{
	Task task = Task();
	task.task_name = ONREPORTSYNCHRONIZATIONRSP;
	if (pReportSynchronization)
	{
		OesReportSynchronizationRspT *task_data = new OesReportSynchronizationRspT();
		*task_data = *pReportSynchronization;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnQueryOrder(const OesOrdItemT *pOrder, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYORDER;
	if (pOrder)
	{
		OesOrdItemT *task_data = new OesOrdItemT();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryTrade(const OesTrdItemT *pTrade, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYTRADE;
	if (pTrade)
	{
		OesTrdItemT *task_data = new OesTrdItemT();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryCashAsset(const OesCashAssetItemT *pCashAsset, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYCASHASSET;
	if (pCashAsset)
	{
		OesCashAssetItemT *task_data = new OesCashAssetItemT();
		*task_data = *pCashAsset;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryStkHolding(const OesStkHoldingItemT *pStkHolding, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYSTKHOLDING;
	if (pStkHolding)
	{
		OesStkHoldingItemT *task_data = new OesStkHoldingItemT();
		*task_data = *pStkHolding;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryLotWinning(const OesLotWinningItemT *pLotWinning, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYLOTWINNING;
	if (pLotWinning)
	{
		OesLotWinningItemT *task_data = new OesLotWinningItemT();
		*task_data = *pLotWinning;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryCustInfo(const OesCustItemT *pCust, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYCUSTINFO;
	if (pCust)
	{
		OesCustItemT *task_data = new OesCustItemT();
		*task_data = *pCust;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryInvAcct(const OesInvAcctItemT *pInvAcct, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYINVACCT;
	if (pInvAcct)
	{
		OesInvAcctItemT *task_data = new OesInvAcctItemT();
		*task_data = *pInvAcct;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryCommissionRate(const OesCommissionRateItemT *pCommissionRate, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYCOMMISSIONRATE;
	if (pCommissionRate)
	{
		OesCommissionRateItemT *task_data = new OesCommissionRateItemT();
		*task_data = *pCommissionRate;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryFundTransferSerial(const OesFundTransferSerialItemT *pFundTrsf, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYFUNDTRANSFERSERIAL;
	if (pFundTrsf)
	{
		OesFundTransferSerialItemT *task_data = new OesFundTransferSerialItemT();
		*task_data = *pFundTrsf;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryIssue(const OesIssueItemT *pIssue, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYISSUE;
	if (pIssue)
	{
		OesIssueItemT *task_data = new OesIssueItemT();
		*task_data = *pIssue;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryStock(const OesStockItemT *pStock, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYSTOCK;
	if (pStock)
	{
		OesStockItemT *task_data = new OesStockItemT();
		*task_data = *pStock;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryEtf(const OesEtfItemT *pEtf, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYETF;
	if (pEtf)
	{
		OesEtfItemT *task_data = new OesEtfItemT();
		*task_data = *pEtf;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryEtfComponent(const OesEtfComponentItemT *pEtfComponent, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYETFCOMPONENT;
	if (pEtfComponent)
	{
		OesEtfComponentItemT *task_data = new OesEtfComponentItemT();
		*task_data = *pEtfComponent;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryMarketState(const OesMarketStateItemT *pMarketState, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYMARKETSTATE;
	if (pMarketState)
	{
		OesMarketStateItemT *task_data = new OesMarketStateItemT();
		*task_data = *pMarketState;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryOption(const OesOptionItemT *pOption, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYOPTION;
	if (pOption)
	{
		OesOptionItemT *task_data = new OesOptionItemT();
		*task_data = *pOption;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryOptHolding(const OesOptHoldingItemT *pOptHolding, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYOPTHOLDING;
	if (pOptHolding)
	{
		OesOptHoldingItemT *task_data = new OesOptHoldingItemT();
		*task_data = *pOptHolding;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryOptUnderlyingHolding(const OesOptUnderlyingHoldingItemT *pUnderlyingHld, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYOPTUNDERLYINGHOLDING;
	if (pUnderlyingHld)
	{
		OesOptUnderlyingHoldingItemT *task_data = new OesOptUnderlyingHoldingItemT();
		*task_data = *pUnderlyingHld;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryOptPositionLimit(const OesOptPositionLimitItemT *pPositionLimit, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYOPTPOSITIONLIMIT;
	if (pPositionLimit)
	{
		OesOptPositionLimitItemT *task_data = new OesOptPositionLimitItemT();
		*task_data = *pPositionLimit;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryOptPurchaseLimit(const OesOptPurchaseLimitItemT *pPurchaseLimit, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYOPTPURCHASELIMIT;
	if (pPurchaseLimit)
	{
		OesOptPurchaseLimitItemT *task_data = new OesOptPurchaseLimitItemT();
		*task_data = *pPurchaseLimit;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryOptExerciseAssign(const OesOptExerciseAssignItemT *pExerciseAssign, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYOPTEXERCISEASSIGN;
	if (pExerciseAssign)
	{
		OesOptExerciseAssignItemT *task_data = new OesOptExerciseAssignItemT();
		*task_data = *pExerciseAssign;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

    void TdApi::OnQueryNotifyInfo(const OesNotifyInfoItemT *pNotifyInfo, const OesQryCursorT *pCursor, int32 requestId)
{
	Task task = Task();
	task.task_name = ONQUERYNOTIFYINFO;
	if (pNotifyInfo)
	{
		OesNotifyInfoItemT *task_data = new OesNotifyInfoItemT();
		*task_data = *pNotifyInfo;
		task.task_data = task_data;
	}
	if (pCursor)
	{
		OesQryCursorT *task_error = new OesQryCursorT();
		*task_error = *pCursor;
		task.task_error = task_error;
	}
	task.task_id = requestId;
	this->task_queue.push(task);
};

