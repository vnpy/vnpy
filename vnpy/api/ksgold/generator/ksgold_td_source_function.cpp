void TdApi::release()
{
	this->api->Release()
};

bool TdApi::init()
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);
	this->api->Init();
};

void TdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront(string pszFrontAddress)
};

void TdApi::subscribePrivateTopic(KS_TE_RESUME_TYPE reqid)
{
	this->api->SubscribePrivateTopic(KS_TE_RESUME_TYPE reqid)
};

void TdApi::subscribePublicTopic(KS_TE_RESUME_TYPE reqid)
{
	this->api->SubscribePublicTopic(KS_TE_RESUME_TYPE reqid)
};

void createGoldQutoApi(string pszFlowPath)
{
	this->api = CKSGoldQuotApi::CreateGoldQutoApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

int TdApi::join()
{
	int i =this->api->Join()
	return i;
};

int TdApi::reqUserLogin(const dict &req, int reqid)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountID", myreq.AccountID);
	getInt(req, "LoginType", &myreq.LoginType);
	getString(req, "Password", myreq.Password);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "UserProductionInfo", myreq.UserProductionInfo);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int TdApi::reqUserLogout(const dict &req, int reqid)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

int TdApi::reqQryInstrument(const dict &req, int reqid)
{
	CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "ContractID", myreq.ContractID);
	getString(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, reqid);
	return i;
};

int TdApi::reqQryVarietyCode(const dict &req, int reqid)
{
	CThostFtdcQryVarietyCodeField myreq = CThostFtdcQryVarietyCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "VarietyID", myreq.VarietyID);
	getString(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryVarietyCode(&myreq, reqid);
	return i;
};

int TdApi::reqOrderInsert(const dict &req, int reqid)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SeatID", myreq.SeatID);
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "TradeCode", myreq.TradeCode);
	getString(req, "InstID", myreq.InstID);
	getChar(req, "BuyOrSell", &myreq.BuyOrSell);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getInt(req, "Amount", &myreq.Amount);
	getDouble(req, "Price", &myreq.Price);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "CmdType", myreq.CmdType);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqOrderAction(const dict &req, int reqid)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "RequestID", &myreq.RequestID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorPosition(const dict &req, int reqid)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "InstID", myreq.InstID);
	int i = this->api->ReqQryInvestorPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryTradingAccount(const dict &req, int reqid)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingAccount(&myreq, reqid);
	return i;
};

int TdApi::reqQryTrade(const dict &req, int reqid)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "InstID", myreq.InstID);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	int i = this->api->ReqQryTrade(&myreq, reqid);
	return i;
};

int TdApi::reqQryOrder(const dict &req, int reqid)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	getString(req, "InstID", myreq.InstID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "CmdType", myreq.CmdType);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "OrderRef", myreq.OrderRef);
	int i = this->api->ReqQryOrder(&myreq, reqid);
	return i;
};

int TdApi::reqQryStorage(const dict &req, int reqid)
{
	CThostFtdcQryStorageField myreq = CThostFtdcQryStorageField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "VarietyID", myreq.VarietyID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryStorage(&myreq, reqid);
	return i;
};

int TdApi::reqQryCostMarginFeeRate(const dict &req, int reqid)
{
	CThostFtdcQryCostMarginFeeField myreq = CThostFtdcQryCostMarginFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "InstID", myreq.InstID);
	int i = this->api->ReqQryCostMarginFeeRate(&myreq, reqid);
	return i;
};

int TdApi::reqConditionOrderInsert(const dict &req, int reqid)
{
	CThostFtdcConditionOrderField myreq = CThostFtdcConditionOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "SeatID", myreq.SeatID);
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "TradeCode", myreq.TradeCode);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "InstID", myreq.InstID);
	getChar(req, "BuyOrSell", &myreq.BuyOrSell);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getInt(req, "Amount", &myreq.Amount);
	getChar(req, "OrderType", &myreq.OrderType);
	getChar(req, "MiddleFlag", &myreq.MiddleFlag);
	getChar(req, "PriceFlag", &myreq.PriceFlag);
	getDouble(req, "Price", &myreq.Price);
	getDouble(req, "TrigPrice", &myreq.TrigPrice);
	getInt(req, "ValidDay", &myreq.ValidDay);
	getInt(req, "VolumnCheck", &myreq.VolumnCheck);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "CmdType", myreq.CmdType);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqConditionOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqConditionOrderAction(const dict &req, int reqid)
{
	CThostFtdcConditionActionOrderField myreq = CThostFtdcConditionActionOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "ConditionOrderNo", myreq.ConditionOrderNo);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqConditionOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQryConditionOrder(const dict &req, int reqid)
{
	CThostFtdcConditionOrderQryField myreq = CThostFtdcConditionOrderQryField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "ConditionOrderNo", myreq.ConditionOrderNo);
	getChar(req, "Status", &myreq.Status);
	getString(req, "InstID", myreq.InstID);
	getString(req, "StartDate", myreq.StartDate);
	getString(req, "EndDate", myreq.EndDate);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "CmdType", myreq.CmdType);
	int i = this->api->ReqQryConditionOrder(&myreq, reqid);
	return i;
};

int TdApi::reqQryConditionOrderTrade(const dict &req, int reqid)
{
	CThostFtdcConditionOrderMatchField myreq = CThostFtdcConditionOrderMatchField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "InstID", myreq.InstID);
	getString(req, "ConditionOrderNo", myreq.ConditionOrderNo);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	int i = this->api->ReqQryConditionOrderTrade(&myreq, reqid);
	return i;
};

int TdApi::reqQryClientSessionInfo(const dict &req, int reqid)
{
	CThostFtdcQryClientSessionField myreq = CThostFtdcQryClientSessionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryClientSessionInfo(&myreq, reqid);
	return i;
};

int TdApi::reqQryQuotation(const dict &req, int reqid)
{
	CThostFtdcQryQuotationField myreq = CThostFtdcQryQuotationField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "marketID", myreq.marketID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryQuotation(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(const dict &req, int reqid)
{
	CThostFtdcQryInvestorPositionDetailField myreq = CThostFtdcQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "QueryData", myreq.QueryData);
	int i = this->api->ReqQryInvestorPositionDetail(&myreq, reqid);
	return i;
};

int TdApi::reqModifyPassword(const dict &req, int reqid)
{
	CThostFtdcModifyPasswordField myreq = CThostFtdcModifyPasswordField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqModifyPassword(&myreq, reqid);
	return i;
};

int TdApi::reqQryHisCapital(const dict &req, int reqid)
{
	CThostFtdcQryHisCapitalField myreq = CThostFtdcQryHisCapitalField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "StartDate", myreq.StartDate);
	getString(req, "EndDate", myreq.EndDate);
	int i = this->api->ReqQryHisCapital(&myreq, reqid);
	return i;
};

int TdApi::reqETFSubScription(const dict &req, int reqid)
{
	CThostFtdcSubScriptionField myreq = CThostFtdcSubScriptionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "SeatNo", myreq.SeatNo);
	getString(req, "EtfCode", myreq.EtfCode);
	getString(req, "InstrumentID1", myreq.InstrumentID1);
	getDouble(req, "weight1", &myreq.weight1);
	getString(req, "InstrumentID2", myreq.InstrumentID2);
	getDouble(req, "weight2", &myreq.weight2);
	getString(req, "InstrumentID3", myreq.InstrumentID3);
	getDouble(req, "weight3", &myreq.weight3);
	getString(req, "InstrumentID4", myreq.InstrumentID4);
	getDouble(req, "weight4", &myreq.weight4);
	getString(req, "InstrumentID5", myreq.InstrumentID5);
	getDouble(req, "weight5", &myreq.weight5);
	getDouble(req, "Totalweight", &myreq.Totalweight);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFSubScription(&myreq, reqid);
	return i;
};

int TdApi::reqETFApplyForPurchase(const dict &req, int reqid)
{
	CThostFtdcApplyForPurchaseField myreq = CThostFtdcApplyForPurchaseField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "SeatNo", myreq.SeatNo);
	getString(req, "EtfCode", myreq.EtfCode);
	getString(req, "InstrumentID1", myreq.InstrumentID1);
	getDouble(req, "weight1", &myreq.weight1);
	getString(req, "InstrumentID2", myreq.InstrumentID2);
	getDouble(req, "weight2", &myreq.weight2);
	getString(req, "InstrumentID3", myreq.InstrumentID3);
	getDouble(req, "weight3", &myreq.weight3);
	getString(req, "InstrumentID4", myreq.InstrumentID4);
	getDouble(req, "weight4", &myreq.weight4);
	getString(req, "InstrumentID5", myreq.InstrumentID5);
	getDouble(req, "weight5", &myreq.weight5);
	getDouble(req, "Totalweight", &myreq.Totalweight);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFApplyForPurchase(&myreq, reqid);
	return i;
};

int TdApi::reqETFRedeem(const dict &req, int reqid)
{
	CThostFtdcRedeemField myreq = CThostFtdcRedeemField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "SeatNo", myreq.SeatNo);
	getString(req, "EtfCode", myreq.EtfCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFRedeem(&myreq, reqid);
	return i;
};

int TdApi::reqETFAccountBinding(const dict &req, int reqid)
{
	CThostFtdcETFBingingField myreq = CThostFtdcETFBingingField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "StockTradeCode", myreq.StockTradeCode);
	getString(req, "EtfCode", myreq.EtfCode);
	getChar(req, "EtfManagedUnit", &myreq.EtfManagedUnit);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFAccountBinding(&myreq, reqid);
	return i;
};

int TdApi::reqETFAccountUnbinding(const dict &req, int reqid)
{
	CThostFtdcETFUnBingingField myreq = CThostFtdcETFUnBingingField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "StockTradeCode", myreq.StockTradeCode);
	getString(req, "EtfCode", myreq.EtfCode);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFAccountUnbinding(&myreq, reqid);
	return i;
};

int TdApi::reqETFTradeDetail(const dict &req, int reqid)
{
	CThostFtdcQryETFTradeDetailField myreq = CThostFtdcQryETFTradeDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqETFTradeDetail(&myreq, reqid);
	return i;
};

int TdApi::reqETFPcfDetail(const dict &req, int reqid)
{
	CThostFtdcQryETFPcfDetailField myreq = CThostFtdcQryETFPcfDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "StartDate", myreq.StartDate);
	getString(req, "EndDate", myreq.EndDate);
	getString(req, "EtfCode", myreq.EtfCode);
	int i = this->api->ReqETFPcfDetail(&myreq, reqid);
	return i;
};

int TdApi::reqBOCMoneyIO(const dict &req, int reqid)
{
	CThostFtdcBOCMoneyIOField myreq = CThostFtdcBOCMoneyIOField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "TransFerType", myreq.TransFerType);
	getDouble(req, "TransFerAmount", &myreq.TransFerAmount);
	getString(req, "TradePassword", myreq.TradePassword);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqBOCMoneyIO(&myreq, reqid);
	return i;
};

