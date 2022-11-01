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

case ONRSPUSERLOGIN:
{
	this->processRspUserLogin(&task);
	break;
}

case ONRSPUSERLOGOUT:
{
	this->processRspUserLogout(&task);
	break;
}

case ONNTYMKTSTATUS:
{
	this->processNtyMktStatus(&task);
	break;
}

case ONRTNINSTRUMENTSTATUS:
{
	this->processRtnInstrumentStatus(&task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(&task);
	break;
}

case ONRSPREQQRYVARIETYCODE:
{
	this->processRspReqQryVarietyCode(&task);
	break;
}

case ONRSPORDERINSERT:
{
	this->processRspOrderInsert(&task);
	break;
}

case ONRSPETFSUBSCRIPTIONORDERINSERT:
{
	this->processRspETFSubscriptionOrderInsert(&task);
	break;
}

case ONRSPETFPURCHASEORDERINSERT:
{
	this->processRspETFPurchaseOrderInsert(&task);
	break;
}

case ONRSPETFREDEEMINSERT:
{
	this->processRspETFRedeemInsert(&task);
	break;
}

case ONRSPETFACCOUNTBINDING:
{
	this->processRspETFAccountBinding(&task);
	break;
}

case ONRSPETFACCOUNTUNBINDING:
{
	this->processRspETFAccountUnbinding(&task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(&task);
	break;
}

case ONFORCELOGOUT:
{
	this->processForceLogout(&task);
	break;
}

case ONRTNETFACCOUNTBINDINGSTATUS:
{
	this->processRtnETFAccountBindingStatus(&task);
	break;
}

case ONRTNETFORDER:
{
	this->processRtnETFOrder(&task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
	break;
}

case ONRTNTRADE:
{
	this->processRtnTrade(&task);
	break;
}

case ONRSPQRYTRADINGACCOUNT:
{
	this->processRspQryTradingAccount(&task);
	break;
}

case ONRSPQRYHISCAPITAL:
{
	this->processRspQryHisCapital(&task);
	break;
}

case ONRSPQRYORDER:
{
	this->processRspQryOrder(&task);
	break;
}

case ONRSPQRYTRADE:
{
	this->processRspQryTrade(&task);
	break;
}

case ONRSPQRYINVESTORPOSITION:
{
	this->processRspQryInvestorPosition(&task);
	break;
}

case ONRSPQRYCLIENTSTORAGE:
{
	this->processRspQryClientStorage(&task);
	break;
}

case ONRSPQRYCOSTMARGINFEERATE:
{
	this->processRspQryCostMarginFeeRate(&task);
	break;
}

case ONRSPCONDITIONORDERINSERT:
{
	this->processRspConditionOrderInsert(&task);
	break;
}

case ONRSPCONDITIONORDERACTION:
{
	this->processRspConditionOrderAction(&task);
	break;
}

case ONRSPQRYCONDITIONORDER:
{
	this->processRspQryConditionOrder(&task);
	break;
}

case ONRSPQRYCONDITIONORDERTRADE:
{
	this->processRspQryConditionOrderTrade(&task);
	break;
}

case ONRSPQRYCLIENTSESSIONINFO:
{
	this->processRspQryClientSessionInfo(&task);
	break;
}

case ONRSPQRYQUOTATION:
{
	this->processRspQryQuotation(&task);
	break;
}

case ONRSPQRYINVESTORPOSITIONDETAIL:
{
	this->processRspQryInvestorPositionDetail(&task);
	break;
}

case ONRSPQRYETFRADEDETAIL:
{
	this->processRspQryETFradeDetail(&task);
	break;
}

case ONRSPQRYETFPCFDETAIL:
{
	this->processRspQryETFPcfDetail(&task);
	break;
}

case ONRSPMODIFYPASSWORD:
{
	this->processRspModifyPassword(&task);
	break;
}

case ONRSPB0CMONEYIO:
{
	this->processRspB0CMoneyIO(&task);
	break;
}

