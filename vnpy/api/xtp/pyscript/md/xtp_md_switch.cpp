case ONDISCONNECTED:
{
    this->processDisconnected(task);
    break;
}

case ONERROR:
{
    this->processError(task);
    break;
}

case ONSUBMARKETDATA:
{
    this->processSubMarketData(task);
    break;
}

case ONUNSUBMARKETDATA:
{
    this->processUnSubMarketData(task);
    break;
}

case ONMARKETDATA:
{
    this->processMarketData(task);
    break;
}

case ONSUBORDERBOOK:
{
    this->processSubOrderBook(task);
    break;
}

case ONUNSUBORDERBOOK:
{
    this->processUnSubOrderBook(task);
    break;
}

case ONORDERBOOK:
{
    this->processOrderBook(task);
    break;
}

case ONQUERYALLTICKERS:
{
    this->processQueryAllTickers(task);
    break;
}

