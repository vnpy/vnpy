case ONFRONTCONNECTED:
{
	this->processFrontConnected(&task);
	break;
}

case ONFRONTDISCONNECTED:
{
	this->processFrontDisconnected(&task);
	break;
}

case ONRTNNOTICE:
{
	this->processRtnNotice(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
	break;
}

case ONRSPSTOCKUSERLOGIN:
{
	this->processRspStockUserLogin(&task);
	break;
}

case ONRSPSTOCKUSERLOGOUT:
{
	this->processRspStockUserLogout(&task);
	break;
}

case ONRSPSTOCKUSERPASSWORDUPDATE:
{
	this->processRspStockUserPasswordUpdate(&task);
	break;
}

case ONRSPSTOCKENTRUSTORDER:
{
	this->processRspStockEntrustOrder(&task);
	break;
}

case ONRSPSTOCKWITHDRAWORDER:
{
	this->processRspStockWithdrawOrder(&task);
	break;
}

case ONRSPSTOCKQRYENTRUSTORDER:
{
	this->processRspStockQryEntrustOrder(&task);
	break;
}

case ONRSPSTOCKQRYREALTIMETRADE:
{
	this->processRspStockQryRealTimeTrade(&task);
	break;
}

case ONRSPSTOCKQRYSERIALTRADE:
{
	this->processRspStockQrySerialTrade(&task);
	break;
}

case ONRSPSTOCKQRYPOSITION:
{
	this->processRspStockQryPosition(&task);
	break;
}

case ONRSPSTOCKQRYCAPITALACCOUNTINFO:
{
	this->processRspStockQryCapitalAccountInfo(&task);
	break;
}

case ONRSPSTOCKQRYACCOUNTINFO:
{
	this->processRspStockQryAccountInfo(&task);
	break;
}

case ONRSPSTOCKQRYSHAREHOLDERINFO:
{
	this->processRspStockQryShareholderInfo(&task);
	break;
}

case ONRSPSTOCKTRANSFERFUNDS:
{
	this->processRspStockTransferFunds(&task);
	break;
}

case ONRSPSTOCKENTRUSTBATCHORDER:
{
	this->processRspStockEntrustBatchOrder(&task);
	break;
}

case ONRSPSTOCKWITHDRAWBATCHORDER:
{
	this->processRspStockWithdrawBatchOrder(&task);
	break;
}

case ONRSPSTOCKCALCABLEENTRUSTQTY:
{
	this->processRspStockCalcAbleEntrustQty(&task);
	break;
}

case ONRSPSTOCKCALCABLEPURCHASEETFQTY:
{
	this->processRspStockCalcAblePurchaseETFQty(&task);
	break;
}

case ONRSPSTOCKQRYFREEZEFUNDSDETAIL:
{
	this->processRspStockQryFreezeFundsDetail(&task);
	break;
}

case ONRSPSTOCKQRYFREEZESTOCKDETAIL:
{
	this->processRspStockQryFreezeStockDetail(&task);
	break;
}

case ONRSPSTOCKQRYTRANSFERSTOCKDETAIL:
{
	this->processRspStockQryTransferStockDetail(&task);
	break;
}

case ONRSPSTOCKQRYTRANSFERFUNDSDETAIL:
{
	this->processRspStockQryTransferFundsDetail(&task);
	break;
}

case ONRSPSTOCKQRYSTOCKINFO:
{
	this->processRspStockQryStockInfo(&task);
	break;
}

case ONRSPSTOCKQRYSTOCKSTATICINFO:
{
	this->processRspStockQryStockStaticInfo(&task);
	break;
}

case ONRSPSTOCKQRYTRADETIME:
{
	this->processRspStockQryTradeTime(&task);
	break;
}

case ONSTOCKENTRUSTORDERRTN:
{
	this->processStockEntrustOrderRtn(&task);
	break;
}

case ONSTOCKTRADERTN:
{
	this->processStockTradeRtn(&task);
	break;
}

case ONSTOCKWITHDRAWORDERRTN:
{
	this->processStockWithdrawOrderRtn(&task);
	break;
}

case ONRSPSOPUSERLOGIN:
{
	this->processRspSOPUserLogin(&task);
	break;
}

case ONRSPSOPUSERLOGOUT:
{
	this->processRspSOPUserLogout(&task);
	break;
}

case ONRSPSOPUSERPASSWORDUPDATE:
{
	this->processRspSOPUserPasswordUpdate(&task);
	break;
}

case ONRSPSOPENTRUSTORDER:
{
	this->processRspSOPEntrustOrder(&task);
	break;
}

case ONRSPSOPQUOTEENTRUSTORDER:
{
	this->processRspSOPQuoteEntrustOrder(&task);
	break;
}

case ONRSPSOPGROUPSPLIT:
{
	this->processRspSOPGroupSplit(&task);
	break;
}

case ONRSPSOPGROUPEXECTUEORDER:
{
	this->processRspSOPGroupExectueOrder(&task);
	break;
}

case ONRSPSOPQRYGROUPPOSITION:
{
	this->processRspSOPQryGroupPosition(&task);
	break;
}

case ONRSPSOPLOCKOUNLOCKSTOCK:
{
	this->processRspSOPLockOUnLockStock(&task);
	break;
}

case ONRSPSOPWITHDRAWORDER:
{
	this->processRspSOPWithdrawOrder(&task);
	break;
}

case ONRSPSOPQRYENTRUSTORDER:
{
	this->processRspSOPQryEntrustOrder(&task);
	break;
}

case ONRSPSOPQRYSERIALTRADE:
{
	this->processRspSOPQrySerialTrade(&task);
	break;
}

case ONRSPSOPQRYPOSITION:
{
	this->processRspSOPQryPosition(&task);
	break;
}

case ONRSPSOPQRYCOLLATERALPOSITION:
{
	this->processRspSOPQryCollateralPosition(&task);
	break;
}

case ONRSPSOPQRYCAPITALACCOUNTINFO:
{
	this->processRspSOPQryCapitalAccountInfo(&task);
	break;
}

case ONRSPSOPQRYACCOUNTINFO:
{
	this->processRspSOPQryAccountInfo(&task);
	break;
}

case ONRSPSOPQRYSHAREHOLDERINFO:
{
	this->processRspSOPQryShareholderInfo(&task);
	break;
}

case ONRSPSOPCALCABLEENTRUSTQTY:
{
	this->processRspSOPCalcAbleEntrustQty(&task);
	break;
}

case ONRSPSOPQRYABLELOCKSTOCK:
{
	this->processRspSOPQryAbleLockStock(&task);
	break;
}

case ONRSPSOPQRYCONTACTINFO:
{
	this->processRspSOPQryContactInfo(&task);
	break;
}

case ONRSPSOPEXECTUEORDER:
{
	this->processRspSOPExectueOrder(&task);
	break;
}

case ONRSPSOPQRYEXECASSIINFO:
{
	this->processRspSOPQryExecAssiInfo(&task);
	break;
}

case ONRSPSOPQRYTRADETIME:
{
	this->processRspSOPQryTradeTime(&task);
	break;
}

case ONRSPSOPQRYEXCHANGEINFO:
{
	this->processRspSOPQryExchangeInfo(&task);
	break;
}

case ONRSPSOPQRYCOMMISSION:
{
	this->processRspSOPQryCommission(&task);
	break;
}

case ONRSPSOPQRYDEPOSIT:
{
	this->processRspSOPQryDeposit(&task);
	break;
}

case ONRSPSOPQRYCONTRACTOBJECTINFO:
{
	this->processRspSOPQryContractObjectInfo(&task);
	break;
}

case ONSOPENTRUSTORDERRTN:
{
	this->processSOPEntrustOrderRtn(&task);
	break;
}

case ONSOPTRADERTN:
{
	this->processSOPTradeRtn(&task);
	break;
}

case ONSOPWITHDRAWORDERRTN:
{
	this->processSOPWithdrawOrderRtn(&task);
	break;
}

case ONRSPFASLUSERLOGIN:
{
	this->processRspFASLUserLogin(&task);
	break;
}

case ONRSPFASLUSERLOGOUT:
{
	this->processRspFASLUserLogout(&task);
	break;
}

case ONRSPFASLQRYABLEFININFO:
{
	this->processRspFASLQryAbleFinInfo(&task);
	break;
}

case ONRSPFASLQRYABLESLOINFO:
{
	this->processRspFASLQryAbleSloInfo(&task);
	break;
}

case ONRSPFASLTRANSFERCOLLATERAL:
{
	this->processRspFASLTransferCollateral(&task);
	break;
}

case ONRSPFASLDIRECTREPAYMENT:
{
	this->processRspFASLDirectRepayment(&task);
	break;
}

case ONRSPFASLREPAYSTOCKTRANSFER:
{
	this->processRspFASLRepayStockTransfer(&task);
	break;
}

case ONRSPFASLENTRUSTCRDTORDER:
{
	this->processRspFASLEntrustCrdtOrder(&task);
	break;
}

case ONRSPFASLENTRUSTORDER:
{
	this->processRspFASLEntrustOrder(&task);
	break;
}

case ONRSPFASLCALCABLEENTRUSTCRDTQTY:
{
	this->processRspFASLCalcAbleEntrustCrdtQty(&task);
	break;
}

case ONRSPFASLQRYCRDTFUNDS:
{
	this->processRspFASLQryCrdtFunds(&task);
	break;
}

case ONRSPFASLQRYCRDTCONTRACT:
{
	this->processRspFASLQryCrdtContract(&task);
	break;
}

case ONRSPFASLQRYCRDTCONCHANGEINFO:
{
	this->processRspFASLQryCrdtConChangeInfo(&task);
	break;
}

case ONRSPFASLTRANSFERFUNDS:
{
	this->processRspFASLTransferFunds(&task);
	break;
}

case ONRSPFASLQRYACCOUNTINFO:
{
	this->processRspFASLQryAccountInfo(&task);
	break;
}

case ONRSPFASLQRYCAPITALACCOUNTINFO:
{
	this->processRspFASLQryCapitalAccountInfo(&task);
	break;
}

case ONRSPFASLQRYSHAREHOLDERINFO:
{
	this->processRspFASLQryShareholderInfo(&task);
	break;
}

case ONRSPFASLQRYPOSITION:
{
	this->processRspFASLQryPosition(&task);
	break;
}

case ONRSPFASLQRYENTRUSTORDER:
{
	this->processRspFASLQryEntrustOrder(&task);
	break;
}

case ONRSPFASLQRYSERIALTRADE:
{
	this->processRspFASLQrySerialTrade(&task);
	break;
}

case ONRSPFASLQRYREALTIMETRADE:
{
	this->processRspFASLQryRealTimeTrade(&task);
	break;
}

case ONRSPFASLQRYFREEZEFUNDSDETAIL:
{
	this->processRspFASLQryFreezeFundsDetail(&task);
	break;
}

case ONRSPFASLQRYFREEZESTOCKDETAIL:
{
	this->processRspFASLQryFreezeStockDetail(&task);
	break;
}

case ONRSPFASLQRYTRANSFERFUNDSDETAIL:
{
	this->processRspFASLQryTransferFundsDetail(&task);
	break;
}

case ONRSPFASLWITHDRAWORDER:
{
	this->processRspFASLWithdrawOrder(&task);
	break;
}

case ONRSPFASLQRYSYSTEMTIME:
{
	this->processRspFASLQrySystemTime(&task);
	break;
}

case ONRSPFASLQRYTRANSFERREDCONTRACT:
{
	this->processRspFASLQryTransferredContract(&task);
	break;
}

case ONRSPFASLDESIRABLEFUNDSOUT:
{
	this->processRspFASLDesirableFundsOut(&task);
	break;
}

case ONRSPFASLQRYGUARANTEEDCONTRACT:
{
	this->processRspFASLQryGuaranteedContract(&task);
	break;
}

case ONRSPFASLQRYUNDERLYINGCONTRACT:
{
	this->processRspFASLQryUnderlyingContract(&task);
	break;
}

case ONFASLENTRUSTORDERRTN:
{
	this->processFASLEntrustOrderRtn(&task);
	break;
}

case ONFASLTRADERTN:
{
	this->processFASLTradeRtn(&task);
	break;
}

case ONFASLWITHDRAWORDERRTN:
{
	this->processFASLWithdrawOrderRtn(&task);
	break;
}

