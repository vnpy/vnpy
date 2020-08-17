int TdApi::qryOrderProcess(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIOrderProcessQryReq myreq = TapAPIOrderProcessQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ServerFlag", &myreq.ServerFlag);
	getString(req, "OrderNo", myreq.OrderNo);
	int i = this->api->QryOrderProcess((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryDeepQuote(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIContract myreq = TapAPIContract();
	memset(&myreq, 0, sizeof(myreq));
	getDict(req, "Commodity", &myreq.Commodity);
	getString(req, "ContractNo1", myreq.ContractNo1);
	getString(req, "StrikePrice1", myreq.StrikePrice1);
	getChar(req, "CallOrPutFlag1", &myreq.CallOrPutFlag1);
	getString(req, "ContractNo2", myreq.ContractNo2);
	getString(req, "StrikePrice2", myreq.StrikePrice2);
	getChar(req, "CallOrPutFlag2", &myreq.CallOrPutFlag2);
	int i = this->api->QryDeepQuote((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryAccountRent(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIAccountRentQryReq myreq = TapAPIAccountRentQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "ContractNo", myreq.ContractNo);
	int i = this->api->QryAccountRent((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryAccountFeeRent(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIAccountFeeRentQryReq myreq = TapAPIAccountFeeRentQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	int i = this->api->QryAccountFeeRent((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryAccountMarginRent(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIAccountMarginRentQryReq myreq = TapAPIAccountMarginRentQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "ContractNo", myreq.ContractNo);
	int i = this->api->QryAccountMarginRent((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryAccountCashAdjust(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIAccountCashAdjustQryReq myreq = TapAPIAccountCashAdjustQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getUnsigned int(req, "SerialID", &myreq.SerialID);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	int i = this->api->QryAccountCashAdjust((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryBill(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIBillQryReq myreq = TapAPIBillQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserNo", myreq.UserNo);
	getDict(req, "BillType", &myreq.BillType);
	getString(req, "BillDate", myreq.BillDate);
	getDict(req, "BillFileType", &myreq.BillFileType);
	int i = this->api->QryBill((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryHisOrder(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIHisOrderQryReq myreq = TapAPIHisOrderQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	int i = this->api->QryHisOrder((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryHisOrderProcess(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIHisOrderProcessQryReq myreq = TapAPIHisOrderProcessQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "Date", myreq.Date);
	getString(req, "OrderNo", myreq.OrderNo);
	int i = this->api->QryHisOrderProcess((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryHisFill(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIHisFillQryReq myreq = TapAPIHisFillQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	getChar(req, "CountType", &myreq.CountType);
	int i = this->api->QryHisFill((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryHisPosition(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIHisPositionQryReq myreq = TapAPIHisPositionQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "Date", myreq.Date);
	getChar(req, "CountType", &myreq.CountType);
	int i = this->api->QryHisPosition((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryHisDelivery(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIHisDeliveryQryReq myreq = TapAPIHisDeliveryQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "AccountAttributeNo", myreq.AccountAttributeNo);
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	getChar(req, "CountType", &myreq.CountType);
	int i = this->api->QryHisDelivery((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryManageInfoForEStar(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIManageInfoQryReq myreq = TapAPIManageInfoQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BeginDate", myreq.BeginDate);
	getString(req, "EndDate", myreq.EndDate);
	int i = this->api->QryManageInfoForEStar((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qrySystemParameter(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPISystemParameterQryReq myreq = TapAPISystemParameterQryReq();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QrySystemParameter((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryTradeCenterFrontAddress(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPITradeCenterFrontAddressQryReq myreq = TapAPITradeCenterFrontAddressQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "FrontAddress", myreq.FrontAddress);
	getString(req, "FrontPort", myreq.FrontPort);
	getChar(req, "TradeCenter", &myreq.TradeCenter);
	getChar(req, "IsSSL", &myreq.IsSSL);
	int i = this->api->QryTradeCenterFrontAddress((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

int TdApi::qryTradeMessage(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPITradeMessageQryReq myreq = TapAPITradeMessageQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getUnsigned int(req, "SerialID", &myreq.SerialID);
	getDict(req, "TradeMsgQryType", &myreq.TradeMsgQryType);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "BeginSendDateTime", myreq.BeginSendDateTime);
	getString(req, "EndSendDateTime", myreq.EndSendDateTime);
	int i = this->api->QryTradeMessage((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
};

