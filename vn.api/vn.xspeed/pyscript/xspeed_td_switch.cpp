case ONFRONTCONNECTED:
{
	this->processFrontConnected(task);
	break;
}

case ONFRONTDISCONNECTED:
{
	this->processFrontDisconnected(task);
	break;
}

case ONRSPUSERLOGIN:
{
	this->processRspUserLogin(task);
	break;
}

case ONRSPUSERLOGOUT:
{
	this->processRspUserLogout(task);
	break;
}

case ONRSPINSERTORDER:
{
	this->processRspInsertOrder(task);
	break;
}

case ONRSPCANCELORDER:
{
	this->processRspCancelOrder(task);
	break;
}

case ONRTNERRORMSG:
{
	this->processRtnErrorMsg(task);
	break;
}

case ONRTNMATCHEDINFO:
{
	this->processRtnMatchedInfo(task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(task);
	break;
}

case ONRTNCANCELORDER:
{
	this->processRtnCancelOrder(task);
	break;
}

case ONRSPQRYORDERINFO:
{
	this->processRspQryOrderInfo(task);
	break;
}

case ONRSPQRYMATCHINFO:
{
	this->processRspQryMatchInfo(task);
	break;
}

case ONRSPQRYPOSITION:
{
	this->processRspQryPosition(task);
	break;
}

case ONRSPCUSTOMERCAPITAL:
{
	this->processRspCustomerCapital(task);
	break;
}

case ONRSPQRYEXCHANGEINSTRUMENT:
{
	this->processRspQryExchangeInstrument(task);
	break;
}

case ONRSPARBITRAGEINSTRUMENT:
{
	this->processRspArbitrageInstrument(task);
	break;
}

case ONRSPQRYSPECIFYINSTRUMENT:
{
	this->processRspQrySpecifyInstrument(task);
	break;
}

case ONRSPQRYPOSITIONDETAIL:
{
	this->processRspQryPositionDetail(task);
	break;
}

case ONRTNTRADINGNOTICE:
{
	this->processRtnTradingNotice(task);
	break;
}

case ONRSPRESETPASSWORD:
{
	this->processRspResetPassword(task);
	break;
}

case ONRSPQRYTRADECODE:
{
	this->processRspQryTradeCode(task);
	break;
}

case ONRSPBILLCONFIRM:
{
	this->processRspBillConfirm(task);
	break;
}

case ONRSPEQUITYCOMPUTMODE:
{
	this->processRspEquityComputMode(task);
	break;
}

case ONRSPQRYBILL:
{
	this->processRspQryBill(task);
	break;
}

case ONRSPCONFIRMPRODUCTINFO:
{
	this->processRspConfirmProductInfo(task);
	break;
}

case ONRSPTRADINGDAY:
{
	this->processRspTradingDay(task);
	break;
}

case ONRSPQUOTEINSERT:
{
	this->processRspQuoteInsert(task);
	break;
}

case ONRTNQUOTEINSERT:
{
	this->processRtnQuoteInsert(task);
	break;
}

case ONRSPQUOTECANCEL:
{
	this->processRspQuoteCancel(task);
	break;
}

case ONRTNQUOTECANCEL:
{
	this->processRtnQuoteCancel(task);
	break;
}

case ONRTNQUOTEMATCHEDINFO:
{
	this->processRtnQuoteMatchedInfo(task);
	break;
}

case ONRSPCANCELALLORDER:
{
	this->processRspCancelAllOrder(task);
	break;
}

case ONRSPQRYQUOTENOTICE:
{
	this->processRspQryQuoteNotice(task);
	break;
}

case ONRSPFORQUOTE:
{
	this->processRspForQuote(task);
	break;
}

case ONRTNFORQUOTE:
{
	this->processRtnForQuote(task);
	break;
}

case ONRSPQRYQUOTEORDERINFO:
{
	this->processRspQryQuoteOrderInfo(task);
	break;
}

case ONRSPQRYFORQUOTE:
{
	this->processRspQryForQuote(task);
	break;
}

case ONRSPQRYTRANSFERBANK:
{
	this->processRspQryTransferBank(task);
	break;
}

case ONRSPQRYTRANSFERSERIAL:
{
	this->processRspQryTransferSerial(task);
	break;
}

case ONRSPFROMBANKTOFUTUREBYFUTURE:
{
	this->processRspFromBankToFutureByFuture(task);
	break;
}

case ONRSPFROMFUTURETOBANKBYFUTURE:
{
	this->processRspFromFutureToBankByFuture(task);
	break;
}

case ONRTNFROMBANKTOFUTUREBYFUTURE:
{
	this->processRtnFromBankToFutureByFuture(task);
	break;
}

case ONRTNFROMFUTURETOBANKBYFUTURE:
{
	this->processRtnFromFutureToBankByFuture(task);
	break;
}

case ONRTNREPEALFROMFUTURETOBANKBYBANK:
{
	this->processRtnRepealFromFutureToBankByBank(task);
	break;
}

case ONRSPQRYEXCHANGESTATUS:
{
	this->processRspQryExchangeStatus(task);
	break;
}

case ONRTNEXCHANGESTATUS:
{
	this->processRtnExchangeStatus(task);
	break;
}

case ONRSPQRYDEPTHMARKETDATA:
{
	this->processRspQryDepthMarketData(task);
	break;
}

