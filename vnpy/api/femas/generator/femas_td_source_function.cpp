int TdApi::reqUserLogin(const dict &req, int reqid)
{
	CUstpFtdcReqUserLoginField myreq = CUstpFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "UserID", myreq.UserID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "Password", myreq.Password);
	getString(req, "UserProductInfo", myreq.UserProductInfo);
	getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	getString(req, "IPAddress", myreq.IPAddress);
	getString(req, "MacAddress", myreq.MacAddress);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	getInt(req, "UserProductFileSize", &myreq.UserProductFileSize);
	getChar(req, "Authenticate2Type", &myreq.Authenticate2Type);
	getString(req, "Authenticate2Password", myreq.Authenticate2Password);
	getString(req, "TerminalCode", myreq.TerminalCode);
	getString(req, "PasswordEncrypt", myreq.PasswordEncrypt);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int TdApi::reqUserLogout(const dict &req, int reqid)
{
	CUstpFtdcReqUserLogoutField myreq = CUstpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

int TdApi::reqUserPasswordUpdate(const dict &req, int reqid)
{
	CUstpFtdcUserPasswordUpdateField myreq = CUstpFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqUserPasswordUpdate(&myreq, reqid);
	return i;
};

int TdApi::reqOrderInsert(const dict &req, int reqid)
{
	CUstpFtdcInputOrderField myreq = CUstpFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getInt(req, "SeatNo", &myreq.SeatNo);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getString(req, "GTDDate", myreq.GTDDate);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "UserCustom", myreq.UserCustom);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getString(req, "ActionDay", myreq.ActionDay);
	getChar(req, "ArbiType", &myreq.ArbiType);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqOrderAction(const dict &req, int reqid)
{
	CUstpFtdcOrderActionField myreq = CUstpFtdcOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQuoteInsert(const dict &req, int reqid)
{
	CUstpFtdcInputQuoteField myreq = CUstpFtdcInputQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "QuoteSysID", myreq.QuoteSysID);
	getString(req, "UserQuoteLocalID", myreq.UserQuoteLocalID);
	getString(req, "QuoteLocalID", myreq.QuoteLocalID);
	getInt(req, "BidVolume", &myreq.BidVolume);
	getChar(req, "BidOffsetFlag", &myreq.BidOffsetFlag);
	getChar(req, "BidHedgeFlag", &myreq.BidHedgeFlag);
	getDouble(req, "BidPrice", &myreq.BidPrice);
	getInt(req, "AskVolume", &myreq.AskVolume);
	getChar(req, "AskOffsetFlag", &myreq.AskOffsetFlag);
	getChar(req, "AskHedgeFlag", &myreq.AskHedgeFlag);
	getDouble(req, "AskPrice", &myreq.AskPrice);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "UserCustom", myreq.UserCustom);
	getString(req, "BidUserOrderLocalID", myreq.BidUserOrderLocalID);
	getString(req, "AskUserOrderLocalID", myreq.AskUserOrderLocalID);
	getString(req, "BidOrderLocalID", myreq.BidOrderLocalID);
	getString(req, "AskOrderLocalID", myreq.AskOrderLocalID);
	getString(req, "ReqForQuoteID", myreq.ReqForQuoteID);
	getInt(req, "StandByTime", &myreq.StandByTime);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQuoteInsert(&myreq, reqid);
	return i;
};

int TdApi::reqQuoteAction(const dict &req, int reqid)
{
	CUstpFtdcQuoteActionField myreq = CUstpFtdcQuoteActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "QuoteSysID", myreq.QuoteSysID);
	getString(req, "UserQuoteLocalID", myreq.UserQuoteLocalID);
	getString(req, "UserQuoteActionLocalID", myreq.UserQuoteActionLocalID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "UserCustom", myreq.UserCustom);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQuoteAction(&myreq, reqid);
	return i;
};

int TdApi::reqForQuote(const dict &req, int reqid)
{
	CUstpFtdcReqForQuoteField myreq = CUstpFtdcReqForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ReqForQuoteID", myreq.ReqForQuoteID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "ReqForQuoteTime", myreq.ReqForQuoteTime);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqForQuote(&myreq, reqid);
	return i;
};

int TdApi::reqMarginCombAction(const dict &req, int reqid)
{
	CUstpFtdcInputMarginCombActionField myreq = CUstpFtdcInputMarginCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "UserActionLocalID", myreq.UserActionLocalID);
	getString(req, "CombInstrumentID", myreq.CombInstrumentID);
	getInt(req, "CombVolume", &myreq.CombVolume);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getString(req, "ActionLocalID", myreq.ActionLocalID);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getChar(req, "CombActionStatus", &myreq.CombActionStatus);
	int i = this->api->ReqMarginCombAction(&myreq, reqid);
	return i;
};

int TdApi::reqUserDeposit(const dict &req, int reqid)
{
	CUstpFtdcstpUserDepositField myreq = CUstpFtdcstpUserDepositField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getDouble(req, "Amount", &myreq.Amount);
	getChar(req, "AmountDirection", &myreq.AmountDirection);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	int i = this->api->ReqUserDeposit(&myreq, reqid);
	return i;
};

int TdApi::reqQryOrder(const dict &req, int reqid)
{
	CUstpFtdcQryOrderField myreq = CUstpFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "OrderStatus", &myreq.OrderStatus);
	getChar(req, "OrderType", &myreq.OrderType);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryOrder(&myreq, reqid);
	return i;
};

int TdApi::reqQryTrade(const dict &req, int reqid)
{
	CUstpFtdcQryTradeField myreq = CUstpFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "TradeID", myreq.TradeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTrade(&myreq, reqid);
	return i;
};

int TdApi::reqQryUserInvestor(const dict &req, int reqid)
{
	CUstpFtdcQryUserInvestorField myreq = CUstpFtdcQryUserInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	int i = this->api->ReqQryUserInvestor(&myreq, reqid);
	return i;
};

int TdApi::reqQryTradingCode(const dict &req, int reqid)
{
	CUstpFtdcQryTradingCodeField myreq = CUstpFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingCode(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorAccount(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorAccountField myreq = CUstpFtdcQryInvestorAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorAccount(&myreq, reqid);
	return i;
};

int TdApi::reqQryInstrument(const dict &req, int reqid)
{
	CUstpFtdcQryInstrumentField myreq = CUstpFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ProductID", myreq.ProductID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryInstrument(&myreq, reqid);
	return i;
};

int TdApi::reqQryExchange(const dict &req, int reqid)
{
	CUstpFtdcQryExchangeField myreq = CUstpFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorPosition(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorPositionField myreq = CUstpFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryInvestorPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryComplianceParam(const dict &req, int reqid)
{
	CUstpFtdcQryComplianceParamField myreq = CUstpFtdcQryComplianceParamField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryComplianceParam(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorFee(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorFeeField myreq = CUstpFtdcQryInvestorFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorFee(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorMargin(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorMarginField myreq = CUstpFtdcQryInvestorMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorMargin(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorCombPosition(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorCombPositionField myreq = CUstpFtdcQryInvestorCombPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "CombInstrumentID", myreq.CombInstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorCombPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorLegPosition(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorLegPositionField myreq = CUstpFtdcQryInvestorLegPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "LegInstrumentID", myreq.LegInstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorLegPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryInstrumentGroup(const dict &req, int reqid)
{
	CUstpFtdcQryUstpInstrumentGroupField myreq = CUstpFtdcQryUstpInstrumentGroupField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryInstrumentGroup(&myreq, reqid);
	return i;
};

int TdApi::reqQryClientMarginCombType(const dict &req, int reqid)
{
	CUstpFtdcQryClientMarginCombTypeField myreq = CUstpFtdcQryClientMarginCombTypeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "InstrumentGroupID", myreq.InstrumentGroupID);
	int i = this->api->ReqQryClientMarginCombType(&myreq, reqid);
	return i;
};

int TdApi::reqExecOrderInsert(const dict &req, int reqid)
{
	CUstpFtdcInputExecOrderField myreq = CUstpFtdcInputExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "OrderType", &myreq.OrderType);
	getChar(req, "DeliveryFlag", &myreq.DeliveryFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getInt(req, "Volume", &myreq.Volume);
	getString(req, "UserCustom", myreq.UserCustom);
	getString(req, "ActionDay", myreq.ActionDay);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	int i = this->api->ReqExecOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqExecOrderAction(const dict &req, int reqid)
{
	CUstpFtdcInputExecOrderActionField myreq = CUstpFtdcInputExecOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getChar(req, "OrderType", &myreq.OrderType);
	int i = this->api->ReqExecOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQrySystemTime(const dict &req, int reqid)
{
	CUstpFtdcReqQrySystemTimeField myreq = CUstpFtdcReqQrySystemTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQrySystemTime(&myreq, reqid);
	return i;
};

int TdApi::reqQryMarginPrefParam(const dict &req, int reqid)
{
	CUstpFtdcReqQryMarginPrefParamField myreq = CUstpFtdcReqQryMarginPrefParamField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "CombInstrumentID", myreq.CombInstrumentID);
	getString(req, "CombInstrumentName", myreq.CombInstrumentName);
	int i = this->api->ReqQryMarginPrefParam(&myreq, reqid);
	return i;
};

int TdApi::reqDSUserCertification(const dict &req, int reqid)
{
	CUstpFtdcDSUserInfoField myreq = CUstpFtdcDSUserInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AppID", myreq.AppID);
	getString(req, "AuthCode", myreq.AuthCode);
	getChar(req, "EncryptType", &myreq.EncryptType);
	int i = this->api->ReqDSUserCertification(&myreq, reqid);
	return i;
};

int TdApi::reqDSProxySubmitInfo(const dict &req, int reqid)
{
	CUstpFtdcDSProxySubmitDataField myreq = CUstpFtdcDSProxySubmitDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AppID", myreq.AppID);
	getString(req, "TerminalPubNetIP", myreq.TerminalPubNetIP);
	getString(req, "TerminalPubNetPort", myreq.TerminalPubNetPort);
	getString(req, "TerminalLoginTime", myreq.TerminalLoginTime);
	getChar(req, "ExceptionFlag", &myreq.ExceptionFlag);
	getString(req, "RelayID", myreq.RelayID);
	getString(req, "TerminalSystemData", myreq.TerminalSystemData);
	int i = this->api->ReqDSProxySubmitInfo(&myreq, reqid);
	return i;
};

