case ONCONNECT:
{
	this->processConnect(&task);
	break;
}

case ONRSPLOGIN:
{
	this->processRspLogin(&task);
	break;
}

case ONRTNCONTACTINFO:
{
	this->processRtnContactInfo(&task);
	break;
}

case ONRSPREQUESTVERTIFICATECODE:
{
	this->processRspRequestVertificateCode(&task);
	break;
}

case ONEXPRIATIONDATE:
{
	this->processExpriationDate(&task);
	break;
}

case ONAPIREADY:
{
	this->processAPIReady(&task);
	break;
}

case ONDISCONNECT:
{
	this->processDisconnect(&task);
	break;
}

case ONRSPCHANGEPASSWORD:
{
	this->processRspChangePassword(&task);
	break;
}

case ONRSPAUTHPASSWORD:
{
	this->processRspAuthPassword(&task);
	break;
}

case ONRSPQRYTRADINGDATE:
{
	this->processRspQryTradingDate(&task);
	break;
}

case ONRSPSETRESERVEDINFO:
{
	this->processRspSetReservedInfo(&task);
	break;
}

case ONRSPQRYACCOUNT:
{
	this->processRspQryAccount(&task);
	break;
}

case ONRSPQRYFUND:
{
	this->processRspQryFund(&task);
	break;
}

case ONRTNFUND:
{
	this->processRtnFund(&task);
	break;
}

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(&task);
	break;
}

case ONRSPQRYCOMMODITY:
{
	this->processRspQryCommodity(&task);
	break;
}

case ONRSPQRYCONTRACT:
{
	this->processRspQryContract(&task);
	break;
}

case ONRTNCONTRACT:
{
	this->processRtnContract(&task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(&task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(&task);
	break;
}

case ONRSPQRYORDER:
{
	this->processRspQryOrder(&task);
	break;
}

case ONRSPQRYORDERPROCESS:
{
	this->processRspQryOrderProcess(&task);
	break;
}

case ONRSPQRYFILL:
{
	this->processRspQryFill(&task);
	break;
}

case ONRTNFILL:
{
	this->processRtnFill(&task);
	break;
}

case ONRSPQRYPOSITION:
{
	this->processRspQryPosition(&task);
	break;
}

case ONRTNPOSITION:
{
	this->processRtnPosition(&task);
	break;
}

case ONRSPQRYPOSITIONSUMMARY:
{
	this->processRspQryPositionSummary(&task);
	break;
}

case ONRTNPOSITIONSUMMARY:
{
	this->processRtnPositionSummary(&task);
	break;
}

case ONRTNPOSITIONPROFIT:
{
	this->processRtnPositionProfit(&task);
	break;
}

case ONRSPQRYCURRENCY:
{
	this->processRspQryCurrency(&task);
	break;
}

case ONRSPQRYTRADEMESSAGE:
{
	this->processRspQryTradeMessage(&task);
	break;
}

case ONRTNTRADEMESSAGE:
{
	this->processRtnTradeMessage(&task);
	break;
}

case ONRSPQRYHISORDER:
{
	this->processRspQryHisOrder(&task);
	break;
}

case ONRSPQRYHISORDERPROCESS:
{
	this->processRspQryHisOrderProcess(&task);
	break;
}

case ONRSPQRYHISMATCH:
{
	this->processRspQryHisMatch(&task);
	break;
}

case ONRSPQRYHISPOSITION:
{
	this->processRspQryHisPosition(&task);
	break;
}

case ONRSPQRYHISDELIVERY:
{
	this->processRspQryHisDelivery(&task);
	break;
}

case ONRSPQRYACCOUNTCASHADJUST:
{
	this->processRspQryAccountCashAdjust(&task);
	break;
}

case ONRSPQRYBILL:
{
	this->processRspQryBill(&task);
	break;
}

case ONRSPQRYACCOUNTFEERENT:
{
	this->processRspQryAccountFeeRent(&task);
	break;
}

case ONRSPQRYACCOUNTMARGINRENT:
{
	this->processRspQryAccountMarginRent(&task);
	break;
}

case ONRSPHKMARKETORDERINSERT:
{
	this->processRspHKMarketOrderInsert(&task);
	break;
}

case ONRSPHKMARKETORDERDELETE:
{
	this->processRspHKMarketOrderDelete(&task);
	break;
}

case ONHKMARKETQUOTENOTICE:
{
	this->processHKMarketQuoteNotice(&task);
	break;
}

case ONRSPORDERLOCALREMOVE:
{
	this->processRspOrderLocalRemove(&task);
	break;
}

case ONRSPORDERLOCALINPUT:
{
	this->processRspOrderLocalInput(&task);
	break;
}

case ONRSPORDERLOCALMODIFY:
{
	this->processRspOrderLocalModify(&task);
	break;
}

case ONRSPORDERLOCALTRANSFER:
{
	this->processRspOrderLocalTransfer(&task);
	break;
}

case ONRSPFILLLOCALINPUT:
{
	this->processRspFillLocalInput(&task);
	break;
}

case ONRSPFILLLOCALREMOVE:
{
	this->processRspFillLocalRemove(&task);
	break;
}

