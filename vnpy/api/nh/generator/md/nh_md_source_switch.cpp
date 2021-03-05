case ONFRONTCONNECTED:
{
	this->processFrontConnected(&task);
	break;
}

case ONFRONTDISCONNECTED:
{
	this->processFrontDisConnected(&task);
	break;
}

case ONHEARTBEATWARNING:
{
	this->processHeartBeatWarning(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
	break;
}

case ONRTNMARKETDATA:
{
	this->processRtnMarketData(&task);
	break;
}

case ONRSPUTPLOGIN:
{
	this->processRspUtpLogin(&task);
	break;
}

case ONRSPUTPLOGOUT:
{
	this->processRspUtpLogout(&task);
	break;
}

case ONRSPSUBSCRIBE:
{
	this->processRspSubscribe(&task);
	break;
}

case ONRSPUNSUBSCRIBE:
{
	this->processRspUnSubscribe(&task);
	break;
}

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(&task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(&task);
	break;
}

