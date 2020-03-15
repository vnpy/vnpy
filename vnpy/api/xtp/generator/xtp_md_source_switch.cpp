case ONDISCONNECTED:
{
	this->processDisconnected(&task);
	break;
}

case ONERROR:
{
	this->processError(&task);
	break;
}

case ONSUBMARKETDATA:
{
	this->processSubMarketData(&task);
	break;
}

case ONUNSUBMARKETDATA:
{
	this->processUnSubMarketData(&task);
	break;
}

case ONDEPTHMARKETDATA:
{
	this->processDepthMarketData(&task);
	break;
}

case ONSUBORDERBOOK:
{
	this->processSubOrderBook(&task);
	break;
}

case ONUNSUBORDERBOOK:
{
	this->processUnSubOrderBook(&task);
	break;
}

case ONORDERBOOK:
{
	this->processOrderBook(&task);
	break;
}

case ONSUBTICKBYTICK:
{
	this->processSubTickByTick(&task);
	break;
}

case ONUNSUBTICKBYTICK:
{
	this->processUnSubTickByTick(&task);
	break;
}

case ONTICKBYTICK:
{
	this->processTickByTick(&task);
	break;
}

case ONSUBSCRIBEALLMARKETDATA:
{
	this->processSubscribeAllMarketData(&task);
	break;
}

case ONUNSUBSCRIBEALLMARKETDATA:
{
	this->processUnSubscribeAllMarketData(&task);
	break;
}

case ONSUBSCRIBEALLORDERBOOK:
{
	this->processSubscribeAllOrderBook(&task);
	break;
}

case ONUNSUBSCRIBEALLORDERBOOK:
{
	this->processUnSubscribeAllOrderBook(&task);
	break;
}

case ONSUBSCRIBEALLTICKBYTICK:
{
	this->processSubscribeAllTickByTick(&task);
	break;
}

case ONUNSUBSCRIBEALLTICKBYTICK:
{
	this->processUnSubscribeAllTickByTick(&task);
	break;
}

case ONQUERYALLTICKERS:
{
	this->processQueryAllTickers(&task);
	break;
}

case ONQUERYTICKERSPRICEINFO:
{
	this->processQueryTickersPriceInfo(&task);
	break;
}

case ONSUBSCRIBEALLOPTIONMARKETDATA:
{
	this->processSubscribeAllOptionMarketData(&task);
	break;
}

case ONUNSUBSCRIBEALLOPTIONMARKETDATA:
{
	this->processUnSubscribeAllOptionMarketData(&task);
	break;
}

case ONSUBSCRIBEALLOPTIONORDERBOOK:
{
	this->processSubscribeAllOptionOrderBook(&task);
	break;
}

case ONUNSUBSCRIBEALLOPTIONORDERBOOK:
{
	this->processUnSubscribeAllOptionOrderBook(&task);
	break;
}

case ONSUBSCRIBEALLOPTIONTICKBYTICK:
{
	this->processSubscribeAllOptionTickByTick(&task);
	break;
}

case ONUNSUBSCRIBEALLOPTIONTICKBYTICK:
{
	this->processUnSubscribeAllOptionTickByTick(&task);
	break;
}

