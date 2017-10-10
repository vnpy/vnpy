int TraderApi::insertOrder(dict req, int reqid)
{
    XTPOrderInsertInfo myreq = XTPOrderInsertInfo();
    memset(&myreq, 0, sizeof(myreq));
    getEnum(req, "business_type", &myreq.business_type);
    getDouble(req, "stop_price", &myreq.stop_price);
    getDouble(req, "stop_price", &myreq.stop_price);
    getEnum(req, "price_type", &myreq.price_type);
    getDouble(req, "price", &myreq.price);
    getDouble(req, "price", &myreq.price);
    getString(req, "ticker", myreq.ticker);
    getEnum(req, "side", &myreq.side);
    getEnum(req, "market", &myreq.market);
    getEnum(req, "market", &myreq.market);
    int i = this->api->InsertOrder(&myreq, reqid);
    return i;
};

int TraderApi::queryOrders(dict req, int reqid)
{
    XTPQueryOrderReq myreq = XTPQueryOrderReq();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ticker", myreq.ticker);
    getString(req, "ticker", myreq.ticker);
    getString(req, "ticker", myreq.ticker);
    int i = this->api->QueryOrders(&myreq, reqid);
    return i;
};

int TraderApi::queryTrades(dict req, int reqid)
{
    XTPQueryTraderReq myreq = XTPQueryTraderReq();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ticker", myreq.ticker);
    getString(req, "ticker", myreq.ticker);
    getString(req, "ticker", myreq.ticker);
    int i = this->api->QueryTrades(&myreq, reqid);
    return i;
};

