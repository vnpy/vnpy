int MdApi::reqDepthMarketDataSubscribe(const dict &req, int reqid)
{
	CHSReqDepthMarketDataField myreq = CHSReqDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqDepthMarketDataSubscribe(&myreq, reqid);
	return i;
};

int MdApi::reqDepthMarketDataCancel(const dict &req, int reqid)
{
	CHSReqDepthMarketDataField myreq = CHSReqDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqDepthMarketDataCancel(&myreq, reqid);
	return i;
};

