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

case ONRSPSUBL2MARKETDATA:
{
	this->processRspSubL2MarketData(task);
	break;
}

case ONRSPUNSUBL2MARKETDATA:
{
	this->processRspUnSubL2MarketData(task);
	break;
}

case ONRSPSUBL2INDEX:
{
	this->processRspSubL2Index(task);
	break;
}

case ONRSPUNSUBL2INDEX:
{
	this->processRspUnSubL2Index(task);
	break;
}

case ONRTNL2MARKETDATA:
{
	this->processRtnL2MarketData(task);
	break;
}

case ONRTNL2INDEX:
{
	this->processRtnL2Index(task);
	break;
}

case ONRSPSUBL2ORDERANDTRADE:
{
	this->processRspSubL2OrderAndTrade(task);
	break;
}

case ONRSPUNSUBL2ORDERANDTRADE:
{
	this->processRspUnSubL2OrderAndTrade(task);
	break;
}

case ONRTNL2ORDER:
{
	this->processRtnL2Order(task);
	break;
}

case ONRTNL2TRADE:
{
	this->processRtnL2Trade(task);
	break;
}

case ONNTFCHECKORDERLIST:
{
	this->processNtfCheckOrderList(task);
	break;
}

