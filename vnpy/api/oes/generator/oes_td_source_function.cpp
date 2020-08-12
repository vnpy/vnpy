int TdApi::queryOrder(const dict &req, int reqid)
{
	OesQryOrdFilterT myreq = OesQryOrdFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "isUnclosedOnly", &myreq.isUnclosedOnly);
	getInt8(req, "clEnvId", &myreq.clEnvId);
	getUint8(req, "securityType", &myreq.securityType);
	getUint8(req, "bsType", &myreq.bsType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "clOrdId", &myreq.clOrdId);
	getInt64(req, "clSeqNo", &myreq.clSeqNo);
	getInt32(req, "startTime", &myreq.startTime);
	getInt32(req, "endTime", &myreq.endTime);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryOrder(&myreq, reqid);
	return i;
};

int TdApi::queryTrade(const dict &req, int reqid)
{
	OesQryTrdFilterT myreq = OesQryTrdFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getUint8(req, "mktId", &myreq.mktId);
	getInt8(req, "clEnvId", &myreq.clEnvId);
	getUint8(req, "securityType", &myreq.securityType);
	getUint8(req, "bsType", &myreq.bsType);
	getUint32(req, "__filler", &myreq.__filler);
	getInt64(req, "clOrdId", &myreq.clOrdId);
	getInt64(req, "clSeqNo", &myreq.clSeqNo);
	getInt32(req, "startTime", &myreq.startTime);
	getInt32(req, "endTime", &myreq.endTime);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryTrade(&myreq, reqid);
	return i;
};

int TdApi::queryCashAsset(const dict &req, int reqid)
{
	OesQryCashAssetFilterT myreq = OesQryCashAssetFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "cashAcctId", myreq.cashAcctId);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryCashAsset(&myreq, reqid);
	return i;
};

int TdApi::queryStkHolding(const dict &req, int reqid)
{
	OesQryStkHoldingFilterT myreq = OesQryStkHoldingFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getString(req, "securityId", myreq.securityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "securityType", &myreq.securityType);
	getUint8(req, "productType", &myreq.productType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryStkHolding(&myreq, reqid);
	return i;
};

int TdApi::queryLotWinning(const dict &req, int reqid)
{
	OesQryLotWinningFilterT myreq = OesQryLotWinningFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "lotType", &myreq.lotType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt32(req, "startDate", &myreq.startDate);
	getInt32(req, "endDate", &myreq.endDate);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryLotWinning(&myreq, reqid);
	return i;
};

int TdApi::queryCustInfo(const dict &req, int reqid)
{
	OesQryCustFilterT myreq = OesQryCustFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryCustInfo(&myreq, reqid);
	return i;
};

int TdApi::queryInvAcct(const dict &req, int reqid)
{
	OesQryInvAcctFilterT myreq = OesQryInvAcctFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryInvAcct(&myreq, reqid);
	return i;
};

int TdApi::queryCommissionRate(const dict &req, int reqid)
{
	OesQryCommissionRateFilterT myreq = OesQryCommissionRateFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "securityType", &myreq.securityType);
	getUint8(req, "bsType", &myreq.bsType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryCommissionRate(&myreq, reqid);
	return i;
};

int TdApi::queryFundTransferSerial(const dict &req, int reqid)
{
	OesQryFundTransferSerialFilterT myreq = OesQryFundTransferSerialFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "cashAcctId", myreq.cashAcctId);
	getInt32(req, "clSeqNo", &myreq.clSeqNo);
	getInt8(req, "clEnvId", &myreq.clEnvId);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryFundTransferSerial(&myreq, reqid);
	return i;
};

int TdApi::queryIssue(const dict &req, int reqid)
{
	OesQryIssueFilterT myreq = OesQryIssueFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "securityId", myreq.securityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "productType", &myreq.productType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryIssue(&myreq, reqid);
	return i;
};

int TdApi::queryStock(const dict &req, int reqid)
{
	OesQryStockFilterT myreq = OesQryStockFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "securityId", myreq.securityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "securityType", &myreq.securityType);
	getUint8(req, "subSecurityType", &myreq.subSecurityType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryStock(&myreq, reqid);
	return i;
};

int TdApi::queryEtf(const dict &req, int reqid)
{
	OesQryEtfFilterT myreq = OesQryEtfFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "fundId", myreq.fundId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryEtf(&myreq, reqid);
	return i;
};

int TdApi::queryEtfComponent(const dict &req, int reqid)
{
	OesQryEtfComponentFilterT myreq = OesQryEtfComponentFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "fundId", myreq.fundId);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryEtfComponent(&myreq, reqid);
	return i;
};

int TdApi::queryMarketState(const dict &req, int reqid)
{
	OesQryMarketStateFilterT myreq = OesQryMarketStateFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getUint8(req, "exchId", &myreq.exchId);
	getUint8(req, "platformId", &myreq.platformId);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryMarketState(&myreq, reqid);
	return i;
};

int TdApi::queryCounterCash(const dict &req, int reqid)
{
	char myreq = char();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "char", myreq.char);
	int i = this->api->QueryCounterCash(&myreq, reqid);
	return i;
};

int TdApi::queryOption(const dict &req, int reqid)
{
	OesQryOptionFilterT myreq = OesQryOptionFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "securityId", myreq.securityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryOption(&myreq, reqid);
	return i;
};

int TdApi::queryOptHolding(const dict &req, int reqid)
{
	OesQryOptHoldingFilterT myreq = OesQryOptHoldingFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getString(req, "securityId", myreq.securityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "positionType", &myreq.positionType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryOptHolding(&myreq, reqid);
	return i;
};

int TdApi::queryOptUnderlyingHolding(const dict &req, int reqid)
{
	OesQryOptUnderlyingHoldingFilterT myreq = OesQryOptUnderlyingHoldingFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getString(req, "underlyingSecurityId", myreq.underlyingSecurityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "underlyingSecurityType", &myreq.underlyingSecurityType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryOptUnderlyingHolding(&myreq, reqid);
	return i;
};

int TdApi::queryOptPositionLimit(const dict &req, int reqid)
{
	OesQryOptPositionLimitFilterT myreq = OesQryOptPositionLimitFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getString(req, "underlyingSecurityId", myreq.underlyingSecurityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "underlyingSecurityType", &myreq.underlyingSecurityType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryOptPositionLimit(&myreq, reqid);
	return i;
};

int TdApi::queryOptPurchaseLimit(const dict &req, int reqid)
{
	OesQryOptPurchaseLimitFilterT myreq = OesQryOptPurchaseLimitFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryOptPurchaseLimit(&myreq, reqid);
	return i;
};

int TdApi::queryOptExerciseAssign(const dict &req, int reqid)
{
	OesQryOptExerciseAssignFilterT myreq = OesQryOptExerciseAssignFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getString(req, "invAcctId", myreq.invAcctId);
	getString(req, "securityId", myreq.securityId);
	getUint8(req, "mktId", &myreq.mktId);
	getUint8(req, "positionType", &myreq.positionType);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryOptExerciseAssign(&myreq, reqid);
	return i;
};

int TdApi::queryOptSettlementStatement(const dict &req, int reqid)
{
	char myreq = char();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "char", myreq.char);
	int i = this->api->QueryOptSettlementStatement(&myreq, reqid);
	return i;
};

int TdApi::queryNotifyInfo(const dict &req, int reqid)
{
	OesQryNotifyInfoFilterT myreq = OesQryNotifyInfoFilterT();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "custId", myreq.custId);
	getUint8(req, "notifyLevel", &myreq.notifyLevel);
	getUint8(req, "__filler", &myreq.__filler);
	getInt64(req, "userInfo", &myreq.userInfo);
	int i = this->api->QueryNotifyInfo(&myreq, reqid);
	return i;
};

