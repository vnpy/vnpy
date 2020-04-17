int TdApi::qryTradingDate(unsigned int session)
{
	int i = this->api->QryTradingDate(session);
	return i;
};

int TdApi::qryAccount(unsigned int session, const dict &req)
{
	TapAPIAccQryReq myreq = TapAPIAccQryReq();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QryAccount(session, &myreq);
	return i;
};

int TdApi::qryFund(unsigned int session, const dict &req)
{
	TapAPIFundReq myreq = TapAPIFundReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	int i = this->api->QryFund(session, &myreq);
	return i;
};

int TdApi::qryExchange(unsigned int session)
{
	int i = this->api->QryExchange(session);
	return i;
};

int TdApi::qryCommodity(unsigned int session)
{
	int i = this->api->QryCommodity(session);
	return i;
};

int TdApi::qryContract(unsigned int session, const dict &req)
{
	TapAPICommodity myreq = TapAPICommodity();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	int i = this->api->QryContract(session, &myreq);
	return i;
};

int TdApi::qryOrder(unsigned int session, const dict &req)
{
	TapAPIOrderQryReq myreq = TapAPIOrderQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getChar(req, "OrderType", &myreq.OrderType);
	getChar(req, "OrderSource", &myreq.OrderSource);
	getChar(req, "TimeInForce", &myreq.TimeInForce);
	getString(req, "ExpireTime", myreq.ExpireTime);
	getChar(req, "IsRiskOrder", &myreq.IsRiskOrder);
	getChar(req, "ServerFlag", &myreq.ServerFlag);
	getString(req, "OrderNo", myreq.OrderNo);
	getChar(req, "IsBackInput", &myreq.IsBackInput);
	getChar(req, "IsDeleted", &myreq.IsDeleted);
	getChar(req, "IsAddOne", &myreq.IsAddOne);
	int i = this->api->QryOrder(session, &myreq);
	return i;
};

int TdApi::qryOrderProcess(unsigned int session, const dict &req)
{
	TapAPIOrderProcessQryReq myreq = TapAPIOrderProcessQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ServerFlag", &myreq.ServerFlag);
	getString(req, "OrderNo", myreq.OrderNo);
	int i = this->api->QryOrderProcess(session, &myreq);
	return i;
};

int TdApi::qryFill(unsigned int session, const dict &req)
{
	TapAPIFillQryReq myreq = TapAPIFillQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "ContractNo", myreq.ContractNo);
	getString(req, "StrikePrice", myreq.StrikePrice);
	getChar(req, "CallOrPutFlag", &myreq.CallOrPutFlag);
	getChar(req, "MatchSource", &myreq.MatchSource);
	getChar(req, "MatchSide", &myreq.MatchSide);
	getChar(req, "PositionEffect", &myreq.PositionEffect);
	getChar(req, "ServerFlag", &myreq.ServerFlag);
	getString(req, "OrderNo", myreq.OrderNo);
	getString(req, "UpperNo", myreq.UpperNo);
	getChar(req, "IsDeleted", &myreq.IsDeleted);
	getChar(req, "IsAddOne", &myreq.IsAddOne);
	int i = this->api->QryFill(session, &myreq);
	return i;
};

int TdApi::qryPosition(unsigned int session, const dict &req)
{
	TapAPIPositionQryReq myreq = TapAPIPositionQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	int i = this->api->QryPosition(session, &myreq);
	return i;
};

int TdApi::qryPositionSummary(unsigned int session, const dict &req)
{
	TapAPIPositionQryReq myreq = TapAPIPositionQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	int i = this->api->QryPositionSummary(session, &myreq);
	return i;
};

int TdApi::qryCurrency(unsigned int session)
{
	int i = this->api->QryCurrency(session);
	return i;
};

int TdApi::qryAccountCashAdjust(unsigned int session, const dict &req)
{
	TapAPIAccountCashAdjustQryReq myreq = TapAPIAccountCashAdjustQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getUnsigned int(req, "SerialID", &myreq.SerialID);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	int i = this->api->QryAccountCashAdjust(session, &myreq);
	return i;
};

int TdApi::qryTradeMessage(unsigned int session, const dict &req)
{
	TapAPITradeMessageReq myreq = TapAPITradeMessageReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BenginSendDateTime", myreq.BenginSendDateTime);
	getString(req, "EndSendDateTime", myreq.EndSendDateTime);
	int i = this->api->QryTradeMessage(session, &myreq);
	return i;
};

int TdApi::qryBill(unsigned int session, const dict &req)
{
	TapAPIBillQryReq myreq = TapAPIBillQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserNo", myreq.UserNo);
	getChar(req, "BillType", &myreq.BillType);
	getString(req, "BillDate", myreq.BillDate);
	getChar(req, "BillFileType", &myreq.BillFileType);
	int i = this->api->QryBill(session, &myreq);
	return i;
};

int TdApi::qryHisOrder(unsigned int session, const dict &req)
{
	TapAPIHisOrderQryReq myreq = TapAPIHisOrderQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	int i = this->api->QryHisOrder(session, &myreq);
	return i;
};

int TdApi::qryHisOrderProcess(unsigned int session, const dict &req)
{
	TapAPIHisOrderProcessQryReq myreq = TapAPIHisOrderProcessQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "Date", myreq.Date);
	getString(req, "OrderNo", myreq.OrderNo);
	int i = this->api->QryHisOrderProcess(session, &myreq);
	return i;
};

int TdApi::qryHisMatch(unsigned int session, const dict &req)
{
	TapAPIHisMatchQryReq myreq = TapAPIHisMatchQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	getChar(req, "CountType", &myreq.CountType);
	int i = this->api->QryHisMatch(session, &myreq);
	return i;
};

int TdApi::qryHisPosition(unsigned int session, const dict &req)
{
	TapAPIHisPositionQryReq myreq = TapAPIHisPositionQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getDict(req, "AccountAttributeNo", &myreq.AccountAttributeNo);
	getString(req, "Date", myreq.Date);
	getDict(req, "CountType", &myreq.CountType);
	getChar(req, "SettleFlag", &myreq.SettleFlag);
	int i = this->api->QryHisPosition(session, &myreq);
	return i;
};

int TdApi::qryHisDelivery(unsigned int session, const dict &req)
{
	TapAPIHisDeliveryQryReq myreq = TapAPIHisDeliveryQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	getChar(req, "CountType", &myreq.CountType);
	int i = this->api->QryHisDelivery(session, &myreq);
	return i;
};

int TdApi::qryAccountFeeRent(unsigned int session, const dict &req)
{
	TapAPIAccountFeeRentQryReq myreq = TapAPIAccountFeeRentQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	int i = this->api->QryAccountFeeRent(session, &myreq);
	return i;
};

int TdApi::qryAccountMarginRent(unsigned int session, const dict &req)
{
	TapAPIAccountMarginRentQryReq myreq = TapAPIAccountMarginRentQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "ContractNo", myreq.ContractNo);
	int i = this->api->QryAccountMarginRent(session, &myreq);
	return i;
};

