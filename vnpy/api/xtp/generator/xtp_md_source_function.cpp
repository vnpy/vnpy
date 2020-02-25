int MdApi::queryAllTickers(int exchange_id)
{
	XTP_EXCHANGE_TYPE myreq = XTP_EXCHANGE_TYPE();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryAllTickers(&myreq, (XTP_EXCHANGE_TYPE) exchange_id);
	return i;
};

int MdApi::queryTickersPriceInfo(string ticker, int count, int exchange_id)
{
	char myreq = char();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryTickersPriceInfo(&myreq, reqid);
	return i;
};

int MdApi::queryAllTickersPriceInfo()
{
	char myreq = char();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryAllTickersPriceInfo(&myreq, reqid);
	return i;
};

