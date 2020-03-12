int FutureApi::reqUserLogin(const dict &req, int reqid)
{
	CFutureReqUserLoginField myreq = CFutureReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserPwd", myreq.UserPwd);
	getString(req, "UserType", myreq.UserType);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "ComputerName", myreq.ComputerName);
	getString(req, "SoftwareName", myreq.SoftwareName);
	getString(req, "SoftwareVersion", myreq.SoftwareVersion);
	getString(req, "AuthorCode", myreq.AuthorCode);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int FutureApi::reqUserLogout(const dict &req, int reqid)
{
	CFutureReqUserLogoutField myreq = CFutureReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

int FutureApi::reqSafeVerify(const dict &req, int reqid)
{
	CFutureReqSafeVerifyField myreq = CFutureReqSafeVerifyField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserPwd", myreq.UserPwd);
	getString(req, "Type", myreq.Type);
	getString(req, "Question", myreq.Question);
	getString(req, "Answer", myreq.Answer);
	getString(req, "MobileNumber", myreq.MobileNumber);
	getString(req, "VerifyCode", myreq.VerifyCode);
	getString(req, "SaveMac", myreq.SaveMac);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqSafeVerify(&myreq, reqid);
	return i;
};

int FutureApi::reqVerifyCode(const dict &req, int reqid)
{
	CFutureReqVerifyCodeField myreq = CFutureReqVerifyCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserPwd", myreq.UserPwd);
	getString(req, "Type", myreq.Type);
	getString(req, "Question", myreq.Question);
	getString(req, "Answer", myreq.Answer);
	getString(req, "MobileNumber", myreq.MobileNumber);
	getString(req, "VerifyCode", myreq.VerifyCode);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqVerifyCode(&myreq, reqid);
	return i;
};

int FutureApi::reqSetVerifyQA(const dict &req, int reqid)
{
	CFutureReqSetVerifyQAField myreq = CFutureReqSetVerifyQAField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserPwd", myreq.UserPwd);
	getString(req, "Type", myreq.Type);
	getString(req, "Question", myreq.Question);
	getString(req, "Answer", myreq.Answer);
	getString(req, "MobileNumber", myreq.MobileNumber);
	getString(req, "VerifyCode", myreq.VerifyCode);
	getString(req, "SaveMac", myreq.SaveMac);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqSetVerifyQA(&myreq, reqid);
	return i;
};

int FutureApi::reqGetQuestion(const dict &req, int reqid)
{
	CFutureReqGetQuestionField myreq = CFutureReqGetQuestionField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "Unused", &myreq.Unused);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqGetQuestion(&myreq, reqid);
	return i;
};

int FutureApi::reqOrderInsert(const dict &req, int reqid)
{
	CFutureReqOrderInsertField myreq = CFutureReqOrderInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserType", myreq.UserType);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "LocalNo", myreq.LocalNo);
	getString(req, "TradePwd", myreq.TradePwd);
	getString(req, "IsRiskOrder", myreq.IsRiskOrder);
	getString(req, "ExchangeCode", myreq.ExchangeCode);
	getString(req, "TreatyCode", myreq.TreatyCode);
	getString(req, "BuySale", myreq.BuySale);
	getString(req, "AddReduce", myreq.AddReduce);
	getString(req, "OrderNumber", myreq.OrderNumber);
	getString(req, "OrderPrice", myreq.OrderPrice);
	getString(req, "TradeType", myreq.TradeType);
	getString(req, "PriceType", myreq.PriceType);
	getString(req, "HtsType", myreq.HtsType);
	getString(req, "ForceID", myreq.ForceID);
	getString(req, "TriggerPrice", myreq.TriggerPrice);
	getString(req, "ValidDate", myreq.ValidDate);
	getString(req, "StrategyId", myreq.StrategyId);
	getString(req, "MaxShow", myreq.MaxShow);
	getString(req, "MinQty", myreq.MinQty);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqOrderInsert(&myreq, reqid);
	return i;
};

int FutureApi::reqOrderModify(const dict &req, int reqid)
{
	CFutureReqOrderModifyField myreq = CFutureReqOrderModifyField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SystemNo", myreq.SystemNo);
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserType", myreq.UserType);
	getString(req, "LocalNo", myreq.LocalNo);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "TradePwd", myreq.TradePwd);
	getString(req, "OrderNo", myreq.OrderNo);
	getString(req, "ExchangeCode", myreq.ExchangeCode);
	getString(req, "TreatyCode", myreq.TreatyCode);
	getString(req, "BuySale", myreq.BuySale);
	getString(req, "OrderNumber", myreq.OrderNumber);
	getString(req, "OrderPrice", myreq.OrderPrice);
	getString(req, "FilledNumber", myreq.FilledNumber);
	getString(req, "ModifyNumber", myreq.ModifyNumber);
	getString(req, "ModifyPrice", myreq.ModifyPrice);
	getString(req, "TradeType", myreq.TradeType);
	getString(req, "PriceType", myreq.PriceType);
	getString(req, "IsRiskOrder", myreq.IsRiskOrder);
	getString(req, "TriggerPrice", myreq.TriggerPrice);
	getString(req, "ModifyTriggerPrice", myreq.ModifyTriggerPrice);
	getString(req, "ValidDate", myreq.ValidDate);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqOrderModify(&myreq, reqid);
	return i;
};

int FutureApi::reqOrderCancel(const dict &req, int reqid)
{
	CFutureReqOrderCancelField myreq = CFutureReqOrderCancelField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserType", myreq.UserType);
	getString(req, "LocalNo", myreq.LocalNo);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "TradePwd", myreq.TradePwd);
	getString(req, "IsSimulation", myreq.IsSimulation);
	getString(req, "SystemNo", myreq.SystemNo);
	getString(req, "OrderNo", myreq.OrderNo);
	getString(req, "ExchangeCode", myreq.ExchangeCode);
	getString(req, "TreatyCode", myreq.TreatyCode);
	getString(req, "BuySale", myreq.BuySale);
	getString(req, "OrderNumber", myreq.OrderNumber);
	getString(req, "OrderPrice", myreq.OrderPrice);
	getString(req, "FilledNumber", myreq.FilledNumber);
	getString(req, "TradeType", myreq.TradeType);
	getString(req, "PriceType", myreq.PriceType);
	getString(req, "HtsType", myreq.HtsType);
	getString(req, "IsRiskOrder", myreq.IsRiskOrder);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqOrderCancel(&myreq, reqid);
	return i;
};

int FutureApi::reqPasswordUpdate(const dict &req, int reqid)
{
	CFutureReqPasswordUpdateField myreq = CFutureReqPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "NewPassword", myreq.NewPassword);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqPasswordUpdate(&myreq, reqid);
	return i;
};

int FutureApi::reqQryOrder(const dict &req, int reqid)
{
	CFutureQryOrderField myreq = CFutureQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserType", myreq.UserType);
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "TradePwd", myreq.TradePwd);
	getString(req, "IsSimulation", myreq.IsSimulation);
	getString(req, "OrderNo", myreq.OrderNo);
	getString(req, "OrderDateTime", myreq.OrderDateTime);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryOrder(&myreq, reqid);
	return i;
};

int FutureApi::reqQryTrade(const dict &req, int reqid)
{
	CFutureQryTradeField myreq = CFutureQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryTrade(&myreq, reqid);
	return i;
};

int FutureApi::reqQryCapital(const dict &req, int reqid)
{
	CFutureQryCapitalField myreq = CFutureQryCapitalField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "Unused", &myreq.Unused);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryCapital(&myreq, reqid);
	return i;
};

int FutureApi::reqQryVersion(const dict &req, int reqid)
{
	CFutureQryVersionField myreq = CFutureQryVersionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.UserId);
	getString(req, "UserPwd", myreq.UserPwd);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryVersion(&myreq, reqid);
	return i;
};

int FutureApi::reqQryCurrency(const dict &req, int reqid)
{
	CFutureQryCurrencyField myreq = CFutureQryCurrencyField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "Unused", &myreq.Unused);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryCurrency(&myreq, reqid);
	return i;
};

int FutureApi::reqQryExchange(const dict &req, int reqid)
{
	CFutureQryExchangeField myreq = CFutureQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ProductGroupID", myreq.ProductGroupID);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryExchange(&myreq, reqid);
	return i;
};

int FutureApi::reqQryPosition(const dict &req, int reqid)
{
	CFutureQryPositionField myreq = CFutureQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryPosition(&myreq, reqid);
	return i;
};

int FutureApi::reqQryStrategy(const dict &req, int reqid)
{
	CFutureQryStrategyField myreq = CFutureQryStrategyField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryStrategy(&myreq, reqid);
	return i;
};

int FutureApi::reqQryCommodity(const dict &req, int reqid)
{
	CFutureQryCommodityField myreq = CFutureQryCommodityField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UpdateDate", myreq.UpdateDate);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryCommodity(&myreq, reqid);
	return i;
};

int FutureApi::reqQryInstrument(const dict &req, int reqid)
{
	CFutureQryInstrumentField myreq = CFutureQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "PageIndex", &myreq.PageIndex);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "CommodityType", myreq.CommodityType);
	getString(req, "ContractNo", myreq.ContractNo);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryInstrument(&myreq, reqid);
	return i;
};

int FutureApi::reqQryExchangeTime(const dict &req, int reqid)
{
	CFutureQryExchangeTimeField myreq = CFutureQryExchangeTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "Unused", &myreq.Unused);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryExchangeTime(&myreq, reqid);
	return i;
};

int FutureApi::reqQryCommodityTime(const dict &req, int reqid)
{
	CFutureQryCommodityTimeField myreq = CFutureQryCommodityTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryCommodityTime(&myreq, reqid);
	return i;
};

int FutureApi::reqQryTotalPosition(const dict &req, int reqid)
{
	CFutureQryTotalPositionField myreq = CFutureQryTotalPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryTotalPosition(&myreq, reqid);
	return i;
};

int FutureApi::reqQryStrategyDetail(const dict &req, int reqid)
{
	CFutureQryStrategyDetailField myreq = CFutureQryStrategyDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "StartegyCommodityNo", myreq.StartegyCommodityNo);
	getString(req, "ErrorDescription", myreq.ErrorDescription);
	int i = this->api->ReqQryStrategyDetail(&myreq, reqid);
	return i;
};

