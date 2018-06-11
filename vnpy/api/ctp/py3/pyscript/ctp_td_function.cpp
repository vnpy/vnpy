int TdApi::reqAuthenticate(dict req, int nRequestID)
{
	CThostFtdcReqAuthenticateField myreq = CThostFtdcReqAuthenticateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "AuthCode", myreq.AuthCode);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqAuthenticate(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CThostFtdcUserPasswordUpdateField myreq = CThostFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "OldPassword", myreq.OldPassword);
	getStr(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqTradingAccountPasswordUpdate(dict req, int nRequestID)
{
	CThostFtdcTradingAccountPasswordUpdateField myreq = CThostFtdcTradingAccountPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "NewPassword", myreq.NewPassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "OldPassword", myreq.OldPassword);
	int i = this->api->ReqTradingAccountPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "UserID", myreq.UserID);
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getStr(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "GTDDate", myreq.GTDDate);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "OrderRef", myreq.OrderRef);
	getChar(req, "Direction", &myreq.Direction);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqParkedOrderInsert(dict req, int nRequestID)
{
	CThostFtdcParkedOrderField myreq = CThostFtdcParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "UserType", &myreq.UserType);
	getStr(req, "UserID", myreq.UserID);
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getStr(req, "ParkedOrderID", myreq.ParkedOrderID);
	getStr(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "GTDDate", myreq.GTDDate);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getInt(req, "ErrorID", &myreq.ErrorID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getStr(req, "ErrorMsg", myreq.ErrorMsg);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "Status", &myreq.Status);
	getStr(req, "OrderRef", myreq.OrderRef);
	getChar(req, "Direction", &myreq.Direction);
	int i = this->api->ReqParkedOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcParkedOrderActionField myreq = CThostFtdcParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserType", &myreq.UserType);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "ErrorID", &myreq.ErrorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "UserID", myreq.UserID);
	getChar(req, "Status", &myreq.Status);
	getInt(req, "FrontID", &myreq.FrontID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "ParkedOrderActionID", myreq.ParkedOrderActionID);
	getStr(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "ErrorMsg", myreq.ErrorMsg);
	int i = this->api->ReqParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "FrontID", &myreq.FrontID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryMaxOrderVolume(dict req, int nRequestID)
{
	CThostFtdcQueryMaxOrderVolumeField myreq = CThostFtdcQueryMaxOrderVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "MaxVolume", &myreq.MaxVolume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getChar(req, "Direction", &myreq.Direction);
	int i = this->api->ReqQueryMaxOrderVolume(&myreq, nRequestID);
	return i;
};

int TdApi::reqSettlementInfoConfirm(dict req, int nRequestID)
{
	CThostFtdcSettlementInfoConfirmField myreq = CThostFtdcSettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ConfirmDate", myreq.ConfirmDate);
	getStr(req, "ConfirmTime", myreq.ConfirmTime);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqSettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqRemoveParkedOrder(dict req, int nRequestID)
{
	CThostFtdcRemoveParkedOrderField myreq = CThostFtdcRemoveParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ParkedOrderID", myreq.ParkedOrderID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqRemoveParkedOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqRemoveParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcRemoveParkedOrderActionField myreq = CThostFtdcRemoveParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ParkedOrderActionID", myreq.ParkedOrderActionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqRemoveParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputExecOrderField myreq = CThostFtdcInputExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ActionType", &myreq.ActionType);
	getChar(req, "ReservePositionFlag", &myreq.ReservePositionFlag);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "CloseFlag", &myreq.CloseFlag);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getChar(req, "PosiDirection", &myreq.PosiDirection);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	int i = this->api->ReqExecOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputExecOrderActionField myreq = CThostFtdcInputExecOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "ExecOrderActionRef", &myreq.ExecOrderActionRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "SessionID", &myreq.SessionID);
	int i = this->api->ReqExecOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqForQuoteInsert(dict req, int nRequestID)
{
	CThostFtdcInputForQuoteField myreq = CThostFtdcInputForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ForQuoteRef", myreq.ForQuoteRef);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqForQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteInsert(dict req, int nRequestID)
{
	CThostFtdcInputQuoteField myreq = CThostFtdcInputQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getDouble(req, "BidPrice", &myreq.BidPrice);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	getChar(req, "AskHedgeFlag", &myreq.AskHedgeFlag);
	getStr(req, "AskOrderRef", myreq.AskOrderRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AskOffsetFlag", &myreq.AskOffsetFlag);
	getChar(req, "BidOffsetFlag", &myreq.BidOffsetFlag);
	getStr(req, "BidOrderRef", myreq.BidOrderRef);
	getDouble(req, "AskPrice", &myreq.AskPrice);
	getChar(req, "BidHedgeFlag", &myreq.BidHedgeFlag);
	getInt(req, "AskVolume", &myreq.AskVolume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "BidVolume", &myreq.BidVolume);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "ForQuoteSysID", myreq.ForQuoteSysID);
	int i = this->api->ReqQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteAction(dict req, int nRequestID)
{
	CThostFtdcInputQuoteActionField myreq = CThostFtdcInputQuoteActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "QuoteSysID", myreq.QuoteSysID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "QuoteActionRef", &myreq.QuoteActionRef);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "SessionID", &myreq.SessionID);
	int i = this->api->ReqQuoteAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqLockInsert(dict req, int nRequestID)
{
	CThostFtdcInputLockField myreq = CThostFtdcInputLockField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "LockRef", myreq.LockRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "LockType", &myreq.LockType);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getInt(req, "Volume", &myreq.Volume);
	int i = this->api->ReqLockInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqCombActionInsert(dict req, int nRequestID)
{
	CThostFtdcInputCombActionField myreq = CThostFtdcInputCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "CombActionRef", myreq.CombActionRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "Volume", &myreq.Volume);
	int i = this->api->ReqCombActionInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "TradeID", myreq.TradeID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "TradeTimeEnd", myreq.TradeTimeEnd);
	getStr(req, "TradeTimeStart", myreq.TradeTimeStart);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BizType", &myreq.BizType);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CThostFtdcQryInvestorField myreq = CThostFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
{
	CThostFtdcQryTradingCodeField myreq = CThostFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ClientIDType", &myreq.ClientIDType);
	getStr(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentMarginRateField myreq = CThostFtdcQryInstrumentMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	int i = this->api->ReqQryInstrumentMarginRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentCommissionRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentCommissionRateField myreq = CThostFtdcQryInstrumentCommissionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInstrumentCommissionRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CThostFtdcQryExchangeField myreq = CThostFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryProduct(dict req, int nRequestID)
{
	CThostFtdcQryProductField myreq = CThostFtdcQryProductField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ProductID", myreq.ProductID);
	getChar(req, "ProductClass", &myreq.ProductClass);
	int i = this->api->ReqQryProduct(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ProductID", myreq.ProductID);
	getStr(req, "ExchangeInstID", myreq.ExchangeInstID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req, int nRequestID)
{
	CThostFtdcQryDepthMarketDataField myreq = CThostFtdcQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryDepthMarketData(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySettlementInfo(dict req, int nRequestID)
{
	CThostFtdcQrySettlementInfoField myreq = CThostFtdcQrySettlementInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "TradingDay", myreq.TradingDay);
	int i = this->api->ReqQrySettlementInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferBank(dict req, int nRequestID)
{
	CThostFtdcQryTransferBankField myreq = CThostFtdcQryTransferBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	int i = this->api->ReqQryTransferBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionDetailField myreq = CThostFtdcQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorPositionDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryNotice(dict req, int nRequestID)
{
	CThostFtdcQryNoticeField myreq = CThostFtdcQryNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryNotice(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySettlementInfoConfirm(dict req, int nRequestID)
{
	CThostFtdcQrySettlementInfoConfirmField myreq = CThostFtdcQrySettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQrySettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionCombineDetail(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionCombineDetailField myreq = CThostFtdcQryInvestorPositionCombineDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "CombInstrumentID", myreq.CombInstrumentID);
	int i = this->api->ReqQryInvestorPositionCombineDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCFMMCTradingAccountKey(dict req, int nRequestID)
{
	CThostFtdcQryCFMMCTradingAccountKeyField myreq = CThostFtdcQryCFMMCTradingAccountKeyField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryCFMMCTradingAccountKey(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryEWarrantOffset(dict req, int nRequestID)
{
	CThostFtdcQryEWarrantOffsetField myreq = CThostFtdcQryEWarrantOffsetField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryEWarrantOffset(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorProductGroupMargin(dict req, int nRequestID)
{
	CThostFtdcQryInvestorProductGroupMarginField myreq = CThostFtdcQryInvestorProductGroupMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "ProductGroupID", myreq.ProductGroupID);
	int i = this->api->ReqQryInvestorProductGroupMargin(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryExchangeMarginRateField myreq = CThostFtdcQryExchangeMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	int i = this->api->ReqQryExchangeMarginRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeMarginRateAdjust(dict req, int nRequestID)
{
	CThostFtdcQryExchangeMarginRateAdjustField myreq = CThostFtdcQryExchangeMarginRateAdjustField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	int i = this->api->ReqQryExchangeMarginRateAdjust(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeRate(dict req, int nRequestID)
{
	CThostFtdcQryExchangeRateField myreq = CThostFtdcQryExchangeRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "FromCurrencyID", myreq.FromCurrencyID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ToCurrencyID", myreq.ToCurrencyID);
	int i = this->api->ReqQryExchangeRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentACIDMap(dict req, int nRequestID)
{
	CThostFtdcQrySecAgentACIDMapField myreq = CThostFtdcQrySecAgentACIDMapField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	int i = this->api->ReqQrySecAgentACIDMap(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryProductExchRate(dict req, int nRequestID)
{
	CThostFtdcQryProductExchRateField myreq = CThostFtdcQryProductExchRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryProductExchRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryProductGroup(dict req, int nRequestID)
{
	CThostFtdcQryProductGroupField myreq = CThostFtdcQryProductGroupField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryProductGroup(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionInstrTradeCost(dict req, int nRequestID)
{
	CThostFtdcQryOptionInstrTradeCostField myreq = CThostFtdcQryOptionInstrTradeCostField();
	memset(&myreq, 0, sizeof(myreq));
	getDouble(req, "InputPrice", &myreq.InputPrice);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getDouble(req, "UnderlyingPrice", &myreq.UnderlyingPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	int i = this->api->ReqQryOptionInstrTradeCost(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionInstrCommRate(dict req, int nRequestID)
{
	CThostFtdcQryOptionInstrCommRateField myreq = CThostFtdcQryOptionInstrCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryOptionInstrCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExecOrder(dict req, int nRequestID)
{
	CThostFtdcQryExecOrderField myreq = CThostFtdcQryExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	int i = this->api->ReqQryExecOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryForQuote(dict req, int nRequestID)
{
	CThostFtdcQryForQuoteField myreq = CThostFtdcQryForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	int i = this->api->ReqQryForQuote(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryQuote(dict req, int nRequestID)
{
	CThostFtdcQryQuoteField myreq = CThostFtdcQryQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "QuoteSysID", myreq.QuoteSysID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	int i = this->api->ReqQryQuote(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryLock(dict req, int nRequestID)
{
	CThostFtdcQryLockField myreq = CThostFtdcQryLockField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "LockSysID", myreq.LockSysID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	int i = this->api->ReqQryLock(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryLockPosition(dict req, int nRequestID)
{
	CThostFtdcQryLockPositionField myreq = CThostFtdcQryLockPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryLockPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorLevel(dict req, int nRequestID)
{
	CThostFtdcQryInvestorLevelField myreq = CThostFtdcQryInvestorLevelField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorLevel(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExecFreeze(dict req, int nRequestID)
{
	CThostFtdcQryExecFreezeField myreq = CThostFtdcQryExecFreezeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryExecFreeze(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombInstrumentGuard(dict req, int nRequestID)
{
	CThostFtdcQryCombInstrumentGuardField myreq = CThostFtdcQryCombInstrumentGuardField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCombInstrumentGuard(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombAction(dict req, int nRequestID)
{
	CThostFtdcQryCombActionField myreq = CThostFtdcQryCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryCombAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferSerial(dict req, int nRequestID)
{
	CThostFtdcQryTransferSerialField myreq = CThostFtdcQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	int i = this->api->ReqQryTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryAccountregister(dict req, int nRequestID)
{
	CThostFtdcQryAccountregisterField myreq = CThostFtdcQryAccountregisterField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	int i = this->api->ReqQryAccountregister(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryContractBank(dict req, int nRequestID)
{
	CThostFtdcQryContractBankField myreq = CThostFtdcQryContractBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryContractBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryParkedOrder(dict req, int nRequestID)
{
	CThostFtdcQryParkedOrderField myreq = CThostFtdcQryParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryParkedOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcQryParkedOrderActionField myreq = CThostFtdcQryParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingNotice(dict req, int nRequestID)
{
	CThostFtdcQryTradingNoticeField myreq = CThostFtdcQryTradingNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryTradingNotice(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBrokerTradingParams(dict req, int nRequestID)
{
	CThostFtdcQryBrokerTradingParamsField myreq = CThostFtdcQryBrokerTradingParamsField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	int i = this->api->ReqQryBrokerTradingParams(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBrokerTradingAlgos(dict req, int nRequestID)
{
	CThostFtdcQryBrokerTradingAlgosField myreq = CThostFtdcQryBrokerTradingAlgosField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryBrokerTradingAlgos(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryCFMMCTradingAccountToken(dict req, int nRequestID)
{
	CThostFtdcQueryCFMMCTradingAccountTokenField myreq = CThostFtdcQueryCFMMCTradingAccountTokenField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQueryCFMMCTradingAccountToken(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromBankToFutureByFuture(dict req, int nRequestID)
{
	CThostFtdcReqTransferField myreq = CThostFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "Message", myreq.Message);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "AccountID", myreq.AccountID);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getStr(req, "OperNo", myreq.OperNo);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getStr(req, "Password", myreq.Password);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Digest", myreq.Digest);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "TradeCode", myreq.TradeCode);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getDouble(req, "CustFee", &myreq.CustFee);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "TradeTime", myreq.TradeTime);
	getStr(req, "TradeDate", myreq.TradeDate);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getStr(req, "BankAccount", myreq.BankAccount);
	int i = this->api->ReqFromBankToFutureByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromFutureToBankByFuture(dict req, int nRequestID)
{
	CThostFtdcReqTransferField myreq = CThostFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "Message", myreq.Message);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "AccountID", myreq.AccountID);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getStr(req, "OperNo", myreq.OperNo);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getStr(req, "Password", myreq.Password);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Digest", myreq.Digest);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "TradeCode", myreq.TradeCode);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getDouble(req, "CustFee", &myreq.CustFee);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "TradeTime", myreq.TradeTime);
	getStr(req, "TradeDate", myreq.TradeDate);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getStr(req, "BankAccount", myreq.BankAccount);
	int i = this->api->ReqFromFutureToBankByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryBankAccountMoneyByFuture(dict req, int nRequestID)
{
	CThostFtdcReqQueryAccountField myreq = CThostFtdcReqQueryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "AccountID", myreq.AccountID);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getStr(req, "OperNo", myreq.OperNo);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getStr(req, "Password", myreq.Password);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Digest", myreq.Digest);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "TradeCode", myreq.TradeCode);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "DeviceID", myreq.DeviceID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "TradeTime", myreq.TradeTime);
	getStr(req, "TradeDate", myreq.TradeDate);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "BankAccount", myreq.BankAccount);
	int i = this->api->ReqQueryBankAccountMoneyByFuture(&myreq, nRequestID);
	return i;
};

