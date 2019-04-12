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

case ONHEARTBEATWARNING:
{
	this->processHeartBeatWarning(&task);
	break;
}

case ONPACKAGESTART:
{
	this->processPackageStart(&task);
	break;
}

case ONPACKAGEEND:
{
	this->processPackageEnd(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
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

case ONRTNDEPTHMARKETDATA:
{
	this->processRtnDepthMarketData(&task);
	break;
}

case ONRSPSUBMARKETDATA:
{
	this->processRspSubMarketData(&task);
	break;
}

case ONRSPUNSUBMARKETDATA:
{
	this->processRspUnSubMarketData(&task);
	break;
}

case ONRSPGETMARKETTOPIC:
{
	this->processRspGetMarketTopic(&task);
	break;
}

case ONRSPGETMARKETDATA:
{
	this->processRspGetMarketData(&task);
	break;
}

