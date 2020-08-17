case ONCONNECTED:
{
	this->processConnected(&task);
	break;
}

case ONDISCONNECTED:
{
	this->processDisconnected(&task);
	break;
}

case ONBUSINESSREJECT:
{
	this->processBusinessReject(&task);
	break;
}

case ONORDERINSERT:
{
	this->processOrderInsert(&task);
	break;
}

case ONORDERREPORT:
{
	this->processOrderReport(&task);
	break;
}

case ONTRADEREPORT:
{
	this->processTradeReport(&task);
	break;
}

case ONCASHASSETVARIATION:
{
	this->processCashAssetVariation(&task);
	break;
}

case ONSTOCKHOLDINGVARIATION:
{
	this->processStockHoldingVariation(&task);
	break;
}

case ONOPTIONHOLDINGVARIATION:
{
	this->processOptionHoldingVariation(&task);
	break;
}

case ONOPTIONUNDERLYINGHOLDINGVARIATION:
{
	this->processOptionUnderlyingHoldingVariation(&task);
	break;
}

case ONSETTLEMENTCONFIRMEDRPT:
{
	this->processSettlementConfirmedRpt(&task);
	break;
}

case ONFUNDTRSFREJECT:
{
	this->processFundTrsfReject(&task);
	break;
}

case ONFUNDTRSFREPORT:
{
	this->processFundTrsfReport(&task);
	break;
}

case ONMARKETSTATE:
{
	this->processMarketState(&task);
	break;
}

case ONNOTIFYREPORT:
{
	this->processNotifyReport(&task);
	break;
}

case ONREPORTSYNCHRONIZATIONRSP:
{
	this->processReportSynchronizationRsp(&task);
	break;
}

case ONQUERYORDER:
{
	this->processQueryOrder(&task);
	break;
}

case ONQUERYTRADE:
{
	this->processQueryTrade(&task);
	break;
}

case ONQUERYCASHASSET:
{
	this->processQueryCashAsset(&task);
	break;
}

case ONQUERYSTKHOLDING:
{
	this->processQueryStkHolding(&task);
	break;
}

case ONQUERYLOTWINNING:
{
	this->processQueryLotWinning(&task);
	break;
}

case ONQUERYCUSTINFO:
{
	this->processQueryCustInfo(&task);
	break;
}

case ONQUERYINVACCT:
{
	this->processQueryInvAcct(&task);
	break;
}

case ONQUERYCOMMISSIONRATE:
{
	this->processQueryCommissionRate(&task);
	break;
}

case ONQUERYFUNDTRANSFERSERIAL:
{
	this->processQueryFundTransferSerial(&task);
	break;
}

case ONQUERYISSUE:
{
	this->processQueryIssue(&task);
	break;
}

case ONQUERYSTOCK:
{
	this->processQueryStock(&task);
	break;
}

case ONQUERYETF:
{
	this->processQueryEtf(&task);
	break;
}

case ONQUERYETFCOMPONENT:
{
	this->processQueryEtfComponent(&task);
	break;
}

case ONQUERYMARKETSTATE:
{
	this->processQueryMarketState(&task);
	break;
}

case ONQUERYOPTION:
{
	this->processQueryOption(&task);
	break;
}

case ONQUERYOPTHOLDING:
{
	this->processQueryOptHolding(&task);
	break;
}

case ONQUERYOPTUNDERLYINGHOLDING:
{
	this->processQueryOptUnderlyingHolding(&task);
	break;
}

case ONQUERYOPTPOSITIONLIMIT:
{
	this->processQueryOptPositionLimit(&task);
	break;
}

case ONQUERYOPTPURCHASELIMIT:
{
	this->processQueryOptPurchaseLimit(&task);
	break;
}

case ONQUERYOPTEXERCISEASSIGN:
{
	this->processQueryOptExerciseAssign(&task);
	break;
}

case ONQUERYNOTIFYINFO:
{
	this->processQueryNotifyInfo(&task);
	break;
}

