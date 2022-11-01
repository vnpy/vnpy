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

case ONRSPSUBALLMARKETDATA:
{
	this->processRspSubAllMarketData(&task);
	break;
}

case ONRSPUNSUBALLMARKETDATA:
{
	this->processRspUnSubAllMarketData(&task);
	break;
}

case ONRSPSUBALLTICKBYTICK:
{
	this->processRspSubAllTickByTick(&task);
	break;
}

case ONRSPUNSUBALLTICKBYTICK:
{
	this->processRspUnSubAllTickByTick(&task);
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

case ONRSPSUBTICKBYTICK:
{
	this->processRspSubTickByTick(&task);
	break;
}

case ONRSPUNSUBTICKBYTICK:
{
	this->processRspUnSubTickByTick(&task);
	break;
}

case ONRTNDEPTHMARKETDATA:
{
	this->processRtnDepthMarketData(&task);
	break;
}

case ONRTNTICKBYTICK:
{
	this->processRtnTickByTick(&task);
	break;
}

case ONRTNORDERBOOK:
{
	this->processRtnOrderBook(&task);
	break;
}

case ONRSPSUBORDERBOOK:
{
	this->processRspSubOrderBook(&task);
	break;
}

case ONRSPUNSUBORDERBOOK:
{
	this->processRspUnSubOrderBook(&task);
	break;
}

