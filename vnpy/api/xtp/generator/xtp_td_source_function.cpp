int TdApi::queryOrderByXTPID(int order_xtp_id, int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryOrderByXTPID(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOrders(const dict &req, int session_id, int request_id)
{
	XTPQueryOrderReq myreq = XTPQueryOrderReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	myreq.begin_time = getIntValue(req, "begin_time");
	myreq.end_time = getIntValue(req, "end_time");
	int i = this->api->QueryOrders(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryTradesByXTPID(int order_xtp_id, int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryTradesByXTPID(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryTrades(const dict &req, int session_id, int request_id)
{
	XTPQueryTraderReq myreq = XTPQueryTraderReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	myreq.begin_time = getIntValue(req, "begin_time");
	myreq.end_time = getIntValue(req, "end_time");
	int i = this->api->QueryTrades(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryPosition(string ticker, int session_id, int request_id)
{
	char myreq = char();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryPosition(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryAsset(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryAsset(&myreq, request_id);
	return i;
};

int TdApi::queryStructuredFund(const dict &req, int session_id, int request_id)
{
	XTPQueryStructuredFundInfoReq myreq = XTPQueryStructuredFundInfoReq();
	memset(&myreq, 0, sizeof(myreq));
	myreq.exchange_id = (XTP_EXCHANGE_TYPE) getIntValue(req, "exchange_id");
	getString(req, "sf_ticker", myreq.sf_ticker);
	int i = this->api->QueryStructuredFund(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryFundTransfer(const dict &req, int session_id, int request_id)
{
	XTPQueryFundTransferLogReq myreq = XTPQueryFundTransferLogReq();
	memset(&myreq, 0, sizeof(myreq));
	myreq.serial_id = getIntValue(req, "serial_id");
	int i = this->api->QueryFundTransfer(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryETF(const dict &req, int session_id, int request_id)
{
	XTPQueryETFBaseReq myreq = XTPQueryETFBaseReq();
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (XTP_MARKET_TYPE) getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryETF(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryETFTickerBasket(const dict &req, int session_id, int request_id)
{
	XTPQueryETFComponentReq myreq = XTPQueryETFComponentReq();
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (XTP_MARKET_TYPE) getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryETFTickerBasket(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryIPOInfoList(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryIPOInfoList(&myreq, request_id);
	return i;
};

int TdApi::queryIPOQuotaInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryIPOQuotaInfo(&myreq, request_id);
	return i;
};

int TdApi::queryOptionAuctionInfo(const dict &req, int session_id, int request_id)
{
	XTPQueryOptionAuctionInfoReq myreq = XTPQueryOptionAuctionInfoReq();
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (XTP_MARKET_TYPE) getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryOptionAuctionInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditCashRepayInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditCashRepayInfo(&myreq, request_id);
	return i;
};

int TdApi::queryCreditFundInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditFundInfo(&myreq, request_id);
	return i;
};

int TdApi::queryCreditDebtInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditDebtInfo(&myreq, request_id);
	return i;
};

int TdApi::queryCreditTickerDebtInfo(const dict &req, int session_id, int request_id)
{
	XTPClientQueryCrdDebtStockReq myreq = XTPClientQueryCrdDebtStockReq();
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (XTP_MARKET_TYPE) getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerDebtInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditAssetDebtInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditAssetDebtInfo(&myreq, request_id);
	return i;
};

int TdApi::queryCreditTickerAssignInfo(const dict &req, int session_id, int request_id)
{
	XTPClientQueryCrdPositionStockReq myreq = XTPClientQueryCrdPositionStockReq();
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (XTP_MARKET_TYPE) getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerAssignInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditExcessStock(const dict &req, int session_id, int request_id)
{
	XTPClientQueryCrdSurplusStkReqInfo myreq = XTPClientQueryCrdSurplusStkReqInfo();
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (XTP_MARKET_TYPE) getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditExcessStock(&myreq, session_id, request_id);
	return i;
};

