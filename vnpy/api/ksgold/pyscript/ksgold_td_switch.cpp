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

case ONNTYMKTSTATUS:
{
	this->processNtyMktStatus(task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(task);
	break;
}

case ONRTNDEPTHMARKETDATA:
{
	this->processRtnDepthMarketData(task);
	break;
}

case ONRSPORDERINSERT:
{
	this->processRspOrderInsert(task);
	break;
}

case ONERRRTNORDERINSERT:
{
	this->processErrRtnOrderInsert(task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(task);
	break;
}

case ONFORCELOGOUT:
{
	this->processForceLogout(task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(task);
	break;
}

case ONERRRTNORDERACTION:
{
	this->processErrRtnOrderAction(task);
	break;
}

case ONRTNTRADE:
{
	this->processRtnTrade(task);
	break;
}

case ONRSPQRYTRADINGACCOUNT:
{
	this->processRspQryTradingAccount(task);
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

case ONRSPQRYCLIENTSTORAGE:
{
	this->processRspQryClientStorage(task);
	break;
}

case ONRSPSUBMARKETDATA:
{
	this->processRspSubMarketData(task);
	break;
}

