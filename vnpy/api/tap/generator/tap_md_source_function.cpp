int MdApi::qryCommodity(unsigned int session)
{
	int i = this->api->QryCommodity(session);
	return i;
};

int MdApi::qryContract(unsigned int session, const dict &req)
{
	TapAPICommodity myreq = TapAPICommodity();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	int i = this->api->QryContract(session, &myreq);
	return i;
};

