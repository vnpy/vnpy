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

case ONRSPERROR:
{
	this->processRspError(task);
	break;
}

case ONRSPSUBMARKETDATA:
{
	this->processRspSubMarketData(task);
	break;
}

case ONRSPUNSUBMARKETDATA:
{
	this->processRspUnSubMarketData(task);
	break;
}

case ONRSPSUBFORQUOTERSP:
{
	this->processRspSubForQuoteRsp(task);
	break;
}

case ONRSPUNSUBFORQUOTERSP:
{
	this->processRspUnSubForQuoteRsp(task);
	break;
}

case ONMARKETDATA:
{
	this->processMarketData(task);
	break;
}

case ONCUSTOMMARKETDATA:
{
	this->processCustomMarketData(task);
	break;
}

case ONRTNFORQUOTERSP:
{
	this->processRtnForQuoteRsp(task);
	break;
}

case ONRSPTRADINGDAY:
{
	this->processRspTradingDay(task);
	break;
}

