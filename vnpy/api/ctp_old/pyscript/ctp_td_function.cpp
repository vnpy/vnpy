int TdApi::reqAuthenticate(dict req, int nRequestID)
{
	CThostFtdcReqAuthenticateField myreq = CThostFtdcReqAuthenticateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "AuthCode", myreq.AuthCode);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AppID", myreq.AppID);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	int i = this->api->ReqAuthenticate(&myreq, nRequestID);
	return i;
};

int TdApi::reqisterUserSystemInfo(dict req, int nRequestID)
{
	CThostFtdcUserSystemInfoField myreq = CThostFtdcUserSystemInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ClientAppID", myreq.ClientAppID);
	getStr(req, "ClientPublicIP", myreq.ClientPublicIP);
	getStr(req, "ClientLoginTime", myreq.ClientLoginTime);
	getStr(req, "ClientSystemInfo", myreq.ClientSystemInfo);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "ClientSystemInfoLen", &myreq.ClientSystemInfoLen);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->RegisterUserSystemInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqmitUserSystemInfo(dict req, int nRequestID)
{
	CThostFtdcUserSystemInfoField myreq = CThostFtdcUserSystemInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ClientAppID", myreq.ClientAppID);
	getStr(req, "ClientPublicIP", myreq.ClientPublicIP);
	getStr(req, "ClientLoginTime", myreq.ClientLoginTime);
	getStr(req, "ClientSystemInfo", myreq.ClientSystemInfo);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "ClientSystemInfoLen", &myreq.ClientSystemInfoLen);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->SubmitUserSystemInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "LoginRemark", myreq.LoginRemark);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CThostFtdcUserPasswordUpdateField myreq = CThostFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "NewPassword", myreq.NewPassword);
	getStr(req, "OldPassword", myreq.OldPassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqTradingAccountPasswordUpdate(dict req, int nRequestID)
{
	CThostFtdcTradingAccountPasswordUpdateField myreq = CThostFtdcTradingAccountPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "NewPassword", myreq.NewPassword);
	getStr(req, "OldPassword", myreq.OldPassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqTradingAccountPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserAuthMethod(dict req, int nRequestID)
{
	CThostFtdcReqUserAuthMethodField myreq = CThostFtdcReqUserAuthMethodField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserAuthMethod(&myreq, nRequestID);
	return i;
};

int TdApi::reqGenUserCaptcha(dict req, int nRequestID)
{
	CThostFtdcReqGenUserCaptchaField myreq = CThostFtdcReqGenUserCaptchaField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqGenUserCaptcha(&myreq, nRequestID);
	return i;
};

int TdApi::reqGenUserText(dict req, int nRequestID)
{
	CThostFtdcReqGenUserTextField myreq = CThostFtdcReqGenUserTextField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqGenUserText(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLoginWithCaptcha(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginWithCaptchaField myreq = CThostFtdcReqUserLoginWithCaptchaField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "Captcha", myreq.Captcha);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "LoginRemark", myreq.LoginRemark);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	int i = this->api->ReqUserLoginWithCaptcha(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLoginWithText(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginWithTextField myreq = CThostFtdcReqUserLoginWithTextField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "Text", myreq.Text);
	getStr(req, "LoginRemark", myreq.LoginRemark);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	int i = this->api->ReqUserLoginWithText(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLoginWithOTP(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginWithOTPField myreq = CThostFtdcReqUserLoginWithOTPField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "LoginRemark", myreq.LoginRemark);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	getStr(req, "OTPPassword", myreq.OTPPassword);
	int i = this->api->ReqUserLoginWithOTP(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getStr(req, "ClientID", myreq.ClientID);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "IPAddress", myreq.IPAddress);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getStr(req, "GTDDate", myreq.GTDDate);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqParkedOrderInsert(dict req, int nRequestID)
{
	CThostFtdcParkedOrderField myreq = CThostFtdcParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "AccountID", myreq.AccountID);
	getChar(req, "Status", &myreq.Status);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getChar(req, "UserType", &myreq.UserType);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getStr(req, "ClientID", myreq.ClientID);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "IPAddress", myreq.IPAddress);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getInt(req, "ErrorID", &myreq.ErrorID);
	getStr(req, "ParkedOrderID", myreq.ParkedOrderID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getStr(req, "GTDDate", myreq.GTDDate);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "ErrorMsg", myreq.ErrorMsg);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqParkedOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcParkedOrderActionField myreq = CThostFtdcParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "ParkedOrderActionID", myreq.ParkedOrderActionID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getChar(req, "Status", &myreq.Status);
	getStr(req, "MacAddress", myreq.MacAddress);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "UserType", &myreq.UserType);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "IPAddress", myreq.IPAddress);
	getInt(req, "ErrorID", &myreq.ErrorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ErrorMsg", myreq.ErrorMsg);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryMaxOrderVolume(dict req, int nRequestID)
{
	CThostFtdcQueryMaxOrderVolumeField myreq = CThostFtdcQueryMaxOrderVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "MaxVolume", &myreq.MaxVolume);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQueryMaxOrderVolume(&myreq, nRequestID);
	return i;
};

int TdApi::reqSettlementInfoConfirm(dict req, int nRequestID)
{
	CThostFtdcSettlementInfoConfirmField myreq = CThostFtdcSettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SettlementID", &myreq.SettlementID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ConfirmDate", myreq.ConfirmDate);
	getStr(req, "ConfirmTime", myreq.ConfirmTime);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqSettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqRemoveParkedOrder(dict req, int nRequestID)
{
	CThostFtdcRemoveParkedOrderField myreq = CThostFtdcRemoveParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ParkedOrderID", myreq.ParkedOrderID);
	int i = this->api->ReqRemoveParkedOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqRemoveParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcRemoveParkedOrderActionField myreq = CThostFtdcRemoveParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ParkedOrderActionID", myreq.ParkedOrderActionID);
	int i = this->api->ReqRemoveParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputExecOrderField myreq = CThostFtdcInputExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "CloseFlag", &myreq.CloseFlag);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "PosiDirection", &myreq.PosiDirection);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ClientID", myreq.ClientID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionType", &myreq.ActionType);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "ReservePositionFlag", &myreq.ReservePositionFlag);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqExecOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputExecOrderActionField myreq = CThostFtdcInputExecOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "ExecOrderActionRef", &myreq.ExecOrderActionRef);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqExecOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqForQuoteInsert(dict req, int nRequestID)
{
	CThostFtdcInputForQuoteField myreq = CThostFtdcInputForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ForQuoteRef", myreq.ForQuoteRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqForQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteInsert(dict req, int nRequestID)
{
	CThostFtdcInputQuoteField myreq = CThostFtdcInputQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "AskHedgeFlag", &myreq.AskHedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "AskVolume", &myreq.AskVolume);
	getStr(req, "BidOrderRef", myreq.BidOrderRef);
	getChar(req, "BidHedgeFlag", &myreq.BidHedgeFlag);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "AskOffsetFlag", &myreq.AskOffsetFlag);
	getStr(req, "ClientID", myreq.ClientID);
	getChar(req, "BidOffsetFlag", &myreq.BidOffsetFlag);
	getDouble(req, "BidPrice", &myreq.BidPrice);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "BidVolume", &myreq.BidVolume);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getDouble(req, "AskPrice", &myreq.AskPrice);
	getStr(req, "AskOrderRef", myreq.AskOrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "ForQuoteSysID", myreq.ForQuoteSysID);
	int i = this->api->ReqQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteAction(dict req, int nRequestID)
{
	CThostFtdcInputQuoteActionField myreq = CThostFtdcInputQuoteActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "QuoteActionRef", &myreq.QuoteActionRef);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ClientID", myreq.ClientID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "QuoteSysID", myreq.QuoteSysID);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQuoteAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqBatchOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputBatchOrderActionField myreq = CThostFtdcInputBatchOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqBatchOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqOptionSelfCloseInsert(dict req, int nRequestID)
{
	CThostFtdcInputOptionSelfCloseField myreq = CThostFtdcInputOptionSelfCloseField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "OptSelfCloseFlag", &myreq.OptSelfCloseFlag);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ClientID", myreq.ClientID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "OptionSelfCloseRef", myreq.OptionSelfCloseRef);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqOptionSelfCloseInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOptionSelfCloseAction(dict req, int nRequestID)
{
	CThostFtdcInputOptionSelfCloseActionField myreq = CThostFtdcInputOptionSelfCloseActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "OptionSelfCloseSysID", myreq.OptionSelfCloseSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "OptionSelfCloseActionRef", &myreq.OptionSelfCloseActionRef);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "OptionSelfCloseRef", myreq.OptionSelfCloseRef);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqOptionSelfCloseAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqCombActionInsert(dict req, int nRequestID)
{
	CThostFtdcInputCombActionField myreq = CThostFtdcInputCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "Direction", &myreq.Direction);
	getStr(req, "CombActionRef", myreq.CombActionRef);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqCombActionInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "TradeTimeStart", myreq.TradeTimeStart);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "TradeID", myreq.TradeID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "TradeTimeEnd", myreq.TradeTimeEnd);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BizType", &myreq.BizType);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CThostFtdcQryInvestorField myreq = CThostFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
{
	CThostFtdcQryTradingCodeField myreq = CThostFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ClientID", myreq.ClientID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getChar(req, "ClientIDType", &myreq.ClientIDType);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentMarginRateField myreq = CThostFtdcQryInstrumentMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryInstrumentMarginRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentCommissionRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentCommissionRateField myreq = CThostFtdcQryInstrumentCommissionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getChar(req, "ProductClass", &myreq.ProductClass);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryProduct(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ExchangeInstID", myreq.ExchangeInstID);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req, int nRequestID)
{
	CThostFtdcQryDepthMarketDataField myreq = CThostFtdcQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryDepthMarketData(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySettlementInfo(dict req, int nRequestID)
{
	CThostFtdcQrySettlementInfoField myreq = CThostFtdcQrySettlementInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "TradingDay", myreq.TradingDay);
	int i = this->api->ReqQrySettlementInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferBank(dict req, int nRequestID)
{
	CThostFtdcQryTransferBankField myreq = CThostFtdcQryTransferBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getStr(req, "BankID", myreq.BankID);
	int i = this->api->ReqQryTransferBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionDetailField myreq = CThostFtdcQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQrySettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionCombineDetail(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionCombineDetailField myreq = CThostFtdcQryInvestorPositionCombineDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "CombInstrumentID", myreq.CombInstrumentID);
	int i = this->api->ReqQryInvestorPositionCombineDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCFMMCTradingAccountKey(dict req, int nRequestID)
{
	CThostFtdcQryCFMMCTradingAccountKeyField myreq = CThostFtdcQryCFMMCTradingAccountKeyField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCFMMCTradingAccountKey(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryEWarrantOffset(dict req, int nRequestID)
{
	CThostFtdcQryEWarrantOffsetField myreq = CThostFtdcQryEWarrantOffsetField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryEWarrantOffset(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorProductGroupMargin(dict req, int nRequestID)
{
	CThostFtdcQryInvestorProductGroupMarginField myreq = CThostFtdcQryInvestorProductGroupMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ProductGroupID", myreq.ProductGroupID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryInvestorProductGroupMargin(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryExchangeMarginRateField myreq = CThostFtdcQryExchangeMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryExchangeMarginRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeMarginRateAdjust(dict req, int nRequestID)
{
	CThostFtdcQryExchangeMarginRateAdjustField myreq = CThostFtdcQryExchangeMarginRateAdjustField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "BrokerID", myreq.BrokerID);
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
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQrySecAgentACIDMap(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryProductExchRate(dict req, int nRequestID)
{
	CThostFtdcQryProductExchRateField myreq = CThostFtdcQryProductExchRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
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

int TdApi::reqQryMMInstrumentCommissionRate(dict req, int nRequestID)
{
	CThostFtdcQryMMInstrumentCommissionRateField myreq = CThostFtdcQryMMInstrumentCommissionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryMMInstrumentCommissionRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryMMOptionInstrCommRate(dict req, int nRequestID)
{
	CThostFtdcQryMMOptionInstrCommRateField myreq = CThostFtdcQryMMOptionInstrCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryMMOptionInstrCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentOrderCommRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentOrderCommRateField myreq = CThostFtdcQryInstrumentOrderCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInstrumentOrderCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BizType", &myreq.BizType);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQrySecAgentTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentCheckMode(dict req, int nRequestID)
{
	CThostFtdcQrySecAgentCheckModeField myreq = CThostFtdcQrySecAgentCheckModeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQrySecAgentCheckMode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentTradeInfo(dict req, int nRequestID)
{
	CThostFtdcQrySecAgentTradeInfoField myreq = CThostFtdcQrySecAgentTradeInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerSecAgentID", myreq.BrokerSecAgentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQrySecAgentTradeInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionInstrTradeCost(dict req, int nRequestID)
{
	CThostFtdcQryOptionInstrTradeCostField myreq = CThostFtdcQryOptionInstrTradeCostField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getDouble(req, "InputPrice", &myreq.InputPrice);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getDouble(req, "UnderlyingPrice", &myreq.UnderlyingPrice);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryOptionInstrTradeCost(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionInstrCommRate(dict req, int nRequestID)
{
	CThostFtdcQryOptionInstrCommRateField myreq = CThostFtdcQryOptionInstrCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryOptionInstrCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExecOrder(dict req, int nRequestID)
{
	CThostFtdcQryExecOrderField myreq = CThostFtdcQryExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryExecOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryForQuote(dict req, int nRequestID)
{
	CThostFtdcQryForQuoteField myreq = CThostFtdcQryForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryForQuote(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryQuote(dict req, int nRequestID)
{
	CThostFtdcQryQuoteField myreq = CThostFtdcQryQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "QuoteSysID", myreq.QuoteSysID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryQuote(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionSelfClose(dict req, int nRequestID)
{
	CThostFtdcQryOptionSelfCloseField myreq = CThostFtdcQryOptionSelfCloseField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "OptionSelfCloseSysID", myreq.OptionSelfCloseSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOptionSelfClose(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestUnit(dict req, int nRequestID)
{
	CThostFtdcQryInvestUnitField myreq = CThostFtdcQryInvestUnitField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestUnit(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombInstrumentGuard(dict req, int nRequestID)
{
	CThostFtdcQryCombInstrumentGuardField myreq = CThostFtdcQryCombInstrumentGuardField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCombInstrumentGuard(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombAction(dict req, int nRequestID)
{
	CThostFtdcQryCombActionField myreq = CThostFtdcQryCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryCombAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferSerial(dict req, int nRequestID)
{
	CThostFtdcQryTransferSerialField myreq = CThostFtdcQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryAccountregister(dict req, int nRequestID)
{
	CThostFtdcQryAccountregisterField myreq = CThostFtdcQryAccountregisterField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryAccountregister(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryContractBank(dict req, int nRequestID)
{
	CThostFtdcQryContractBankField myreq = CThostFtdcQryContractBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getStr(req, "BankID", myreq.BankID);
	int i = this->api->ReqQryContractBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryParkedOrder(dict req, int nRequestID)
{
	CThostFtdcQryParkedOrderField myreq = CThostFtdcQryParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryParkedOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcQryParkedOrderActionField myreq = CThostFtdcQryParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingNotice(dict req, int nRequestID)
{
	CThostFtdcQryTradingNoticeField myreq = CThostFtdcQryTradingNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingNotice(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBrokerTradingParams(dict req, int nRequestID)
{
	CThostFtdcQryBrokerTradingParamsField myreq = CThostFtdcQryBrokerTradingParamsField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryBrokerTradingParams(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBrokerTradingAlgos(dict req, int nRequestID)
{
	CThostFtdcQryBrokerTradingAlgosField myreq = CThostFtdcQryBrokerTradingAlgosField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryBrokerTradingAlgos(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryCFMMCTradingAccountToken(dict req, int nRequestID)
{
	CThostFtdcQueryCFMMCTradingAccountTokenField myreq = CThostFtdcQueryCFMMCTradingAccountTokenField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQueryCFMMCTradingAccountToken(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromBankToFutureByFuture(dict req, int nRequestID)
{
	CThostFtdcReqTransferField myreq = CThostFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "TradeCode", myreq.TradeCode);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "LongCustomerName", myreq.LongCustomerName);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Message", myreq.Message);
	getDouble(req, "CustFee", &myreq.CustFee);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromBankToFutureByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromFutureToBankByFuture(dict req, int nRequestID)
{
	CThostFtdcReqTransferField myreq = CThostFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "TradeCode", myreq.TradeCode);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "LongCustomerName", myreq.LongCustomerName);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Message", myreq.Message);
	getDouble(req, "CustFee", &myreq.CustFee);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromFutureToBankByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryBankAccountMoneyByFuture(dict req, int nRequestID)
{
	CThostFtdcReqQueryAccountField myreq = CThostFtdcReqQueryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "TradeCode", myreq.TradeCode);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "LongCustomerName", myreq.LongCustomerName);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getStr(req, "TradeDate", myreq.TradeDate);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqQueryBankAccountMoneyByFuture(&myreq, nRequestID);
	return i;
};

