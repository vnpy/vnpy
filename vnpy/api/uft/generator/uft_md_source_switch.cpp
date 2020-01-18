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

case ONRSPDEPTHMARKETDATASUBSCRIBE:
{
	this->processRspDepthMarketDataSubscribe(&task);
	break;
}

case ONRSPDEPTHMARKETDATACANCEL:
{
	this->processRspDepthMarketDataCancel(&task);
	break;
}

case ONRTNDEPTHMARKETDATA:
{
	this->processRtnDepthMarketData(&task);
	break;
}

