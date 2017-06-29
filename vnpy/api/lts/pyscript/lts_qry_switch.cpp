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

case ONHEARTBEATWARNING:
{
	this->processHeartBeatWarning(task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(task);
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

case ONRSPFETCHAUTHRANDCODE:
{
	this->processRspFetchAuthRandCode(task);
	break;
}

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(task);
	break;
}

case ONRSPQRYINVESTOR:
{
	this->processRspQryInvestor(task);
	break;
}

case ONRSPQRYTRADINGCODE:
{
	this->processRspQryTradingCode(task);
	break;
}

case ONRSPQRYTRADINGACCOUNT:
{
	this->processRspQryTradingAccount(task);
	break;
}

case ONRSPQRYBONDINTEREST:
{
	this->processRspQryBondInterest(task);
	break;
}

case ONRSPQRYMARKETRATIONINFO:
{
	this->processRspQryMarketRationInfo(task);
	break;
}

case ONRSPQRYINSTRUMENTCOMMISSIONRATE:
{
	this->processRspQryInstrumentCommissionRate(task);
	break;
}

case ONRSPQRYETFINSTRUMENT:
{
	this->processRspQryETFInstrument(task);
	break;
}

case ONRSPQRYETFBASKET:
{
	this->processRspQryETFBasket(task);
	break;
}

case ONRSPQRYOFINSTRUMENT:
{
	this->processRspQryOFInstrument(task);
	break;
}

case ONRSPQRYSFINSTRUMENT:
{
	this->processRspQrySFInstrument(task);
	break;
}

case ONRSPQRYINSTRUMENTUNITMARGIN:
{
	this->processRspQryInstrumentUnitMargin(task);
	break;
}

case ONRSPQRYPREDELIVINFO:
{
	this->processRspQryPreDelivInfo(task);
	break;
}

case ONRSPQRYCREDITSTOCKASSIGNINFO:
{
	this->processRspQryCreditStockAssignInfo(task);
	break;
}

case ONRSPQRYCREDITCASHASSIGNINFO:
{
	this->processRspQryCreditCashAssignInfo(task);
	break;
}

case ONRSPQRYCONVERSIONRATE:
{
	this->processRspQryConversionRate(task);
	break;
}

case ONRSPQRYHISCREDITDEBTINFO:
{
	this->processRspQryHisCreditDebtInfo(task);
	break;
}

case ONRSPQRYMARKETDATASTATICINFO:
{
	this->processRspQryMarketDataStaticInfo(task);
	break;
}

case ONRSPQRYEXPIREREPURCHINFO:
{
	this->processRspQryExpireRepurchInfo(task);
	break;
}

case ONRSPQRYBONDPLEDGERATE:
{
	this->processRspQryBondPledgeRate(task);
	break;
}

case ONRSPQRYPLEDGEBOND:
{
	this->processRspQryPledgeBond(task);
	break;
}

case ONRSPQRYORDER:
{
	this->processRspQryOrder(task);
	break;
}

case ONRSPQRYTRADE:
{
	this->processRspQryTrade(task);
	break;
}

case ONRSPQRYINVESTORPOSITION:
{
	this->processRspQryInvestorPosition(task);
	break;
}

case ONRSPQRYFUNDTRANSFERSERIAL:
{
	this->processRspQryFundTransferSerial(task);
	break;
}

case ONRSPQRYFUNDINTERTRANSFERSERIAL:
{
	this->processRspQryFundInterTransferSerial(task);
	break;
}

