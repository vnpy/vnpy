void TdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void TdApi::processHeartBeatWarning(Task task)
{
	PyLock lock;
	this->onHeartBeatWarning(task.task_id);
};

void TdApi::processRspAuthenticate(Task task)
{
	PyLock lock;
	CThostFtdcRspAuthenticateField task_data = any_cast<CThostFtdcRspAuthenticateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["UserProductInfo"] = task_data.UserProductInfo;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspAuthenticate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CThostFtdcRspUserLoginField task_data = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["SHFETime"] = task_data.SHFETime;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["INETime"] = task_data.INETime;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["FFEXTime"] = task_data.FFEXTime;
	data["BrokerID"] = task_data.BrokerID;
	data["DCETime"] = task_data.DCETime;
	data["LoginTime"] = task_data.LoginTime;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcUserPasswordUpdateField task_data = any_cast<CThostFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountPasswordUpdateField task_data = any_cast<CThostFtdcTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["CurrencyID"] = task_data.CurrencyID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderSysID"] = task_data.OrderSysID;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Status"] = task_data.Status;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["UserType"] = task_data.UserType;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["ErrorID"] = task_data.ErrorID;
	data["ParkedOrderID"] = task_data.ParkedOrderID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspParkedOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Status"] = task_data.Status;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserType"] = task_data.UserType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ParkedOrderActionID"] = task_data.ParkedOrderActionID;
	data["FrontID"] = task_data.FrontID;
	data["ErrorID"] = task_data.ErrorID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderActionField task_data = any_cast<CThostFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryMaxOrderVolume(Task task)
{
	PyLock lock;
	CThostFtdcQueryMaxOrderVolumeField task_data = any_cast<CThostFtdcQueryMaxOrderVolumeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxVolume"] = task_data.MaxVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryMaxOrderVolume(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmTime"] = task_data.ConfirmTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ConfirmDate"] = task_data.ConfirmDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderField task_data = any_cast<CThostFtdcRemoveParkedOrderField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParkedOrderID"] = task_data.ParkedOrderID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspRemoveParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderActionField task_data = any_cast<CThostFtdcRemoveParkedOrderActionField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParkedOrderActionID"] = task_data.ParkedOrderActionID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspRemoveParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["CloseFlag"] = task_data.CloseFlag;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionType"] = task_data.ActionType;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspExecOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderActionField task_data = any_cast<CThostFtdcInputExecOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["UserID"] = task_data.UserID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspExecOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["UserID"] = task_data.UserID;
	data["ForQuoteRef"] = task_data.ForQuoteRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspForQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["AskPrice"] = task_data.AskPrice;
	data["UserID"] = task_data.UserID;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidVolume"] = task_data.BidVolume;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["AskVolume"] = task_data.AskVolume;
	data["InvestorID"] = task_data.InvestorID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["BidPrice"] = task_data.BidPrice;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["BidOrderRef"] = task_data.BidOrderRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteActionField task_data = any_cast<CThostFtdcInputQuoteActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["QuoteActionRef"] = task_data.QuoteActionRef;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["FrontID"] = task_data.FrontID;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["QuoteRef"] = task_data.QuoteRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQuoteAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspBatchOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputBatchOrderActionField task_data = any_cast<CThostFtdcInputBatchOrderActionField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspBatchOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Direction"] = task_data.Direction;
	data["CombActionRef"] = task_data.CombActionRef;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombDirection"] = task_data.CombDirection;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspCombActionInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ParticipantID"] = task_data.ParticipantID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["ClientID"] = task_data.ClientID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TradeTime"] = task_data.TradeTime;
	data["Direction"] = task_data.Direction;
	data["ParticipantID"] = task_data.ParticipantID;
	data["Price"] = task_data.Price;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["TradeID"] = task_data.TradeID;
	data["TradeDate"] = task_data.TradeDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["TradeSource"] = task_data.TradeSource;
	data["PriceSource"] = task_data.PriceSource;
	data["TradingRole"] = task_data.TradingRole;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionField task_data = any_cast<CThostFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["StrikeFrozen"] = task_data.StrikeFrozen;
	data["CombPosition"] = task_data.CombPosition;
	data["CashIn"] = task_data.CashIn;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["CombLongFrozen"] = task_data.CombLongFrozen;
	data["CloseAmount"] = task_data.CloseAmount;
	data["PosiDirection"] = task_data.PosiDirection;
	data["YdPosition"] = task_data.YdPosition;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["AbandonFrozen"] = task_data.AbandonFrozen;
	data["OpenVolume"] = task_data.OpenVolume;
	data["CloseVolume"] = task_data.CloseVolume;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["InstrumentID"] = task_data.InstrumentID;
	data["PositionDate"] = task_data.PositionDate;
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["PreMargin"] = task_data.PreMargin;
	data["SettlementID"] = task_data.SettlementID;
	data["ShortFrozen"] = task_data.ShortFrozen;
	data["LongFrozen"] = task_data.LongFrozen;
	data["TodayPosition"] = task_data.TodayPosition;
	data["TradingDay"] = task_data.TradingDay;
	data["PositionCost"] = task_data.PositionCost;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["OpenAmount"] = task_data.OpenAmount;
	data["OpenCost"] = task_data.OpenCost;
	data["Position"] = task_data.Position;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["CombShortFrozen"] = task_data.CombShortFrozen;
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LongFrozenAmount"] = task_data.LongFrozenAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["StrikeFrozenAmount"] = task_data.StrikeFrozenAmount;
	data["CloseProfit"] = task_data.CloseProfit;
	data["UseMargin"] = task_data.UseMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountField task_data = any_cast<CThostFtdcTradingAccountField>(task.task_data);
	dict data;
	data["SpecProductFrozenCommission"] = task_data.SpecProductFrozenCommission;
	data["FundMortgageOut"] = task_data.FundMortgageOut;
	data["Mortgage"] = task_data.Mortgage;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["SpecProductCloseProfit"] = task_data.SpecProductCloseProfit;
	data["Interest"] = task_data.Interest;
	data["SpecProductCommission"] = task_data.SpecProductCommission;
	data["CashIn"] = task_data.CashIn;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["FundMortgageAvailable"] = task_data.FundMortgageAvailable;
	data["PreCredit"] = task_data.PreCredit;
	data["PreMortgage"] = task_data.PreMortgage;
	data["InterestBase"] = task_data.InterestBase;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["MortgageableFund"] = task_data.MortgageableFund;
	data["PreFundMortgageIn"] = task_data.PreFundMortgageIn;
	data["PreMargin"] = task_data.PreMargin;
	data["SettlementID"] = task_data.SettlementID;
	data["FundMortgageIn"] = task_data.FundMortgageIn;
	data["DeliveryMargin"] = task_data.DeliveryMargin;
	data["SpecProductFrozenMargin"] = task_data.SpecProductFrozenMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["Balance"] = task_data.Balance;
	data["SpecProductMargin"] = task_data.SpecProductMargin;
	data["SpecProductPositionProfitByAlg"] = task_data.SpecProductPositionProfitByAlg;
	data["Reserve"] = task_data.Reserve;
	data["PreDeposit"] = task_data.PreDeposit;
	data["Credit"] = task_data.Credit;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ReserveBalance"] = task_data.ReserveBalance;
	data["SpecProductPositionProfit"] = task_data.SpecProductPositionProfit;
	data["SpecProductExchangeMargin"] = task_data.SpecProductExchangeMargin;
	data["PreBalance"] = task_data.PreBalance;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["CloseProfit"] = task_data.CloseProfit;
	data["PreFundMortgageOut"] = task_data.PreFundMortgageOut;
	data["Deposit"] = task_data.Deposit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CThostFtdcInvestorField task_data = any_cast<CThostFtdcInvestorField>(task.task_data);
	dict data;
	data["CommModelID"] = task_data.CommModelID;
	data["InvestorName"] = task_data.InvestorName;
	data["Mobile"] = task_data.Mobile;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["Telephone"] = task_data.Telephone;
	data["MarginModelID"] = task_data.MarginModelID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Address"] = task_data.Address;
	data["InvestorGroupID"] = task_data.InvestorGroupID;
	data["OpenDate"] = task_data.OpenDate;
	data["IsActive"] = task_data.IsActive;
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CThostFtdcTradingCodeField task_data = any_cast<CThostFtdcTradingCodeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ClientIDType"] = task_data.ClientIDType;
	data["IsActive"] = task_data.IsActive;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentMarginRateField task_data = any_cast<CThostFtdcInstrumentMarginRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
	data["IsRelative"] = task_data.IsRelative;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentCommissionRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentCommissionRateField task_data = any_cast<CThostFtdcInstrumentCommissionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentCommissionRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CThostFtdcExchangeField task_data = any_cast<CThostFtdcExchangeField>(task.task_data);
	dict data;
	data["ExchangeProperty"] = task_data.ExchangeProperty;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProduct(Task task)
{
	PyLock lock;
	CThostFtdcProductField task_data = any_cast<CThostFtdcProductField>(task.task_data);
	dict data;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MortgageFundUseRange"] = task_data.MortgageFundUseRange;
	data["PositionDateType"] = task_data.PositionDateType;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["CloseDealType"] = task_data.CloseDealType;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["PriceTick"] = task_data.PriceTick;
	data["ProductName"] = task_data.ProductName;
	data["ExchangeProductID"] = task_data.ExchangeProductID;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["PositionType"] = task_data.PositionType;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["ProductClass"] = task_data.ProductClass;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["TradeCurrencyID"] = task_data.TradeCurrencyID;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryProduct(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentField task_data = any_cast<CThostFtdcInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["PositionDateType"] = task_data.PositionDateType;
	data["LongMarginRatio"] = task_data.LongMarginRatio;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortMarginRatio"] = task_data.ShortMarginRatio;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["MaxMarginSideAlgorithm"] = task_data.MaxMarginSideAlgorithm;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["CombinationType"] = task_data.CombinationType;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["OptionsType"] = task_data.OptionsType;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["PriceTick"] = task_data.PriceTick;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["UnderlyingInstrID"] = task_data.UnderlyingInstrID;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["HighestPrice"] = task_data.HighestPrice;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidPrice4"] = task_data.BidPrice4;
	data["BidPrice1"] = task_data.BidPrice1;
	data["BidPrice3"] = task_data.BidPrice3;
	data["BidPrice2"] = task_data.BidPrice2;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["OpenPrice"] = task_data.OpenPrice;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["AveragePrice"] = task_data.AveragePrice;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["AskPrice2"] = task_data.AskPrice2;
	data["Volume"] = task_data.Volume;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["AskVolume5"] = task_data.AskVolume5;
	data["AskVolume4"] = task_data.AskVolume4;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["BidVolume1"] = task_data.BidVolume1;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
	data["TradingDay"] = task_data.TradingDay;
	data["PreDelta"] = task_data.PreDelta;
	data["OpenInterest"] = task_data.OpenInterest;
	data["CurrDelta"] = task_data.CurrDelta;
	data["Turnover"] = task_data.Turnover;
	data["LastPrice"] = task_data.LastPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["LowestPrice"] = task_data.LowestPrice;
	data["ActionDay"] = task_data.ActionDay;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfo(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoField task_data = any_cast<CThostFtdcSettlementInfoField>(task.task_data);
	dict data;
	data["SettlementID"] = task_data.SettlementID;
	data["InvestorID"] = task_data.InvestorID;
	data["SequenceNo"] = task_data.SequenceNo;
	data["Content"] = task_data.Content;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySettlementInfo(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferBank(Task task)
{
	PyLock lock;
	CThostFtdcTransferBankField task_data = any_cast<CThostFtdcTransferBankField>(task.task_data);
	dict data;
	data["BankName"] = task_data.BankName;
	data["IsActive"] = task_data.IsActive;
	data["BankBrchID"] = task_data.BankBrchID;
	data["BankID"] = task_data.BankID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTransferBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionDetailField task_data = any_cast<CThostFtdcInvestorPositionDetailField>(task.task_data);
	dict data;
	data["PositionProfitByDate"] = task_data.PositionProfitByDate;
	data["ExchMargin"] = task_data.ExchMargin;
	data["TradeType"] = task_data.TradeType;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["Direction"] = task_data.Direction;
	data["CloseAmount"] = task_data.CloseAmount;
	data["OpenPrice"] = task_data.OpenPrice;
	data["Volume"] = task_data.Volume;
	data["LastSettlementPrice"] = task_data.LastSettlementPrice;
	data["CloseVolume"] = task_data.CloseVolume;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["SettlementID"] = task_data.SettlementID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["Margin"] = task_data.Margin;
	data["TradeID"] = task_data.TradeID;
	data["PositionProfitByTrade"] = task_data.PositionProfitByTrade;
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["CombInstrumentID"] = task_data.CombInstrumentID;
	data["OpenDate"] = task_data.OpenDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPositionDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryNotice(Task task)
{
	PyLock lock;
	CThostFtdcNoticeField task_data = any_cast<CThostFtdcNoticeField>(task.task_data);
	dict data;
	data["Content"] = task_data.Content;
	data["SequenceLabel"] = task_data.SequenceLabel;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmTime"] = task_data.ConfirmTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ConfirmDate"] = task_data.ConfirmDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionCombineDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionCombineDetailField task_data = any_cast<CThostFtdcInvestorPositionCombineDetailField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradeGroupID"] = task_data.TradeGroupID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["ComTradeID"] = task_data.ComTradeID;
	data["SettlementID"] = task_data.SettlementID;
	data["InvestorID"] = task_data.InvestorID;
	data["TotalAmt"] = task_data.TotalAmt;
	data["Margin"] = task_data.Margin;
	data["ExchMargin"] = task_data.ExchMargin;
	data["LegMultiple"] = task_data.LegMultiple;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TradeID"] = task_data.TradeID;
	data["LegID"] = task_data.LegID;
	data["TradingDay"] = task_data.TradingDay;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["Direction"] = task_data.Direction;
	data["BrokerID"] = task_data.BrokerID;
	data["CombInstrumentID"] = task_data.CombInstrumentID;
	data["OpenDate"] = task_data.OpenDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPositionCombineDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCFMMCTradingAccountKey(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountKeyField task_data = any_cast<CThostFtdcCFMMCTradingAccountKeyField>(task.task_data);
	dict data;
	data["KeyID"] = task_data.KeyID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CurrentKey"] = task_data.CurrentKey;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCFMMCTradingAccountKey(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryEWarrantOffset(Task task)
{
	PyLock lock;
	CThostFtdcEWarrantOffsetField task_data = any_cast<CThostFtdcEWarrantOffsetField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["InvestorID"] = task_data.InvestorID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["Volume"] = task_data.Volume;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryEWarrantOffset(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorProductGroupMargin(Task task)
{
	PyLock lock;
	CThostFtdcInvestorProductGroupMarginField task_data = any_cast<CThostFtdcInvestorProductGroupMarginField>(task.task_data);
	dict data;
	data["ExchMargin"] = task_data.ExchMargin;
	data["ShortExchOffsetAmount"] = task_data.ShortExchOffsetAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["LongOffsetAmount"] = task_data.LongOffsetAmount;
	data["CashIn"] = task_data.CashIn;
	data["ShortUseMargin"] = task_data.ShortUseMargin;
	data["ShortOffsetAmount"] = task_data.ShortOffsetAmount;
	data["SettlementID"] = task_data.SettlementID;
	data["LongExchOffsetAmount"] = task_data.LongExchOffsetAmount;
	data["LongUseMargin"] = task_data.LongUseMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["LongFrozenMargin"] = task_data.LongFrozenMargin;
	data["ShortExchMargin"] = task_data.ShortExchMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["ProductGroupID"] = task_data.ProductGroupID;
	data["ExchOffsetAmount"] = task_data.ExchOffsetAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["LongExchMargin"] = task_data.LongExchMargin;
	data["CloseProfit"] = task_data.CloseProfit;
	data["OffsetAmount"] = task_data.OffsetAmount;
	data["UseMargin"] = task_data.UseMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorProductGroupMargin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateField task_data = any_cast<CThostFtdcExchangeMarginRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["BrokerID"] = task_data.BrokerID;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRateAdjust(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateAdjustField task_data = any_cast<CThostFtdcExchangeMarginRateAdjustField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["ExchLongMarginRatioByMoney"] = task_data.ExchLongMarginRatioByMoney;
	data["ExchShortMarginRatioByMoney"] = task_data.ExchShortMarginRatioByMoney;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
	data["ExchShortMarginRatioByVolume"] = task_data.ExchShortMarginRatioByVolume;
	data["ExchLongMarginRatioByVolume"] = task_data.ExchLongMarginRatioByVolume;
	data["NoShortMarginRatioByMoney"] = task_data.NoShortMarginRatioByMoney;
	data["NoLongMarginRatioByMoney"] = task_data.NoLongMarginRatioByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["NoLongMarginRatioByVolume"] = task_data.NoLongMarginRatioByVolume;
	data["NoShortMarginRatioByVolume"] = task_data.NoShortMarginRatioByVolume;
	data["BrokerID"] = task_data.BrokerID;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeMarginRateAdjust(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeRateField task_data = any_cast<CThostFtdcExchangeRateField>(task.task_data);
	dict data;
	data["FromCurrencyID"] = task_data.FromCurrencyID;
	data["FromCurrencyUnit"] = task_data.FromCurrencyUnit;
	data["BrokerID"] = task_data.BrokerID;
	data["ExchangeRate"] = task_data.ExchangeRate;
	data["ToCurrencyID"] = task_data.ToCurrencyID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySecAgentACIDMap(Task task)
{
	PyLock lock;
	CThostFtdcSecAgentACIDMapField task_data = any_cast<CThostFtdcSecAgentACIDMapField>(task.task_data);
	dict data;
	data["CurrencyID"] = task_data.CurrencyID;
	data["UserID"] = task_data.UserID;
	data["BrokerSecAgentID"] = task_data.BrokerSecAgentID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySecAgentACIDMap(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductExchRate(Task task)
{
	PyLock lock;
	CThostFtdcProductExchRateField task_data = any_cast<CThostFtdcProductExchRateField>(task.task_data);
	dict data;
	data["QuoteCurrencyID"] = task_data.QuoteCurrencyID;
	data["ExchangeRate"] = task_data.ExchangeRate;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryProductExchRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductGroup(Task task)
{
	PyLock lock;
	CThostFtdcProductGroupField task_data = any_cast<CThostFtdcProductGroupField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ProductGroupID"] = task_data.ProductGroupID;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryProductGroup(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrTradeCost(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrTradeCostField task_data = any_cast<CThostFtdcOptionInstrTradeCostField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchMiniMargin"] = task_data.ExchMiniMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["Royalty"] = task_data.Royalty;
	data["BrokerID"] = task_data.BrokerID;
	data["MiniMargin"] = task_data.MiniMargin;
	data["ExchFixedMargin"] = task_data.ExchFixedMargin;
	data["FixedMargin"] = task_data.FixedMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOptionInstrTradeCost(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrCommRate(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrCommRateField task_data = any_cast<CThostFtdcOptionInstrCommRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["StrikeRatioByMoney"] = task_data.StrikeRatioByMoney;
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;
	data["StrikeRatioByVolume"] = task_data.StrikeRatioByVolume;
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOptionInstrCommRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["CloseFlag"] = task_data.CloseFlag;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ExecResult"] = task_data.ExecResult;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["Volume"] = task_data.Volume;
	data["InstallID"] = task_data.InstallID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["ClientID"] = task_data.ClientID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["SessionID"] = task_data.SessionID;
	data["ActionType"] = task_data.ActionType;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ExecOrderLocalID"] = task_data.ExecOrderLocalID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExecOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryForQuote(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteField task_data = any_cast<CThostFtdcForQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ForQuoteRef"] = task_data.ForQuoteRef;
	data["ExchangeID"] = task_data.ExchangeID;
	data["InstallID"] = task_data.InstallID;
	data["ForQuoteLocalID"] = task_data.ForQuoteLocalID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["InsertDate"] = task_data.InsertDate;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["SessionID"] = task_data.SessionID;
	data["ClientID"] = task_data.ClientID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ForQuoteStatus"] = task_data.ForQuoteStatus;
	data["FrontID"] = task_data.FrontID;
	data["BrokerForQutoSeq"] = task_data.BrokerForQutoSeq;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryForQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BidOrderSysID"] = task_data.BidOrderSysID;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["AskVolume"] = task_data.AskVolume;
	data["BidOrderRef"] = task_data.BidOrderRef;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["AskOrderSysID"] = task_data.AskOrderSysID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["ClientID"] = task_data.ClientID;
	data["SessionID"] = task_data.SessionID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BidPrice"] = task_data.BidPrice;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["InstrumentID"] = task_data.InstrumentID;
	data["QuoteStatus"] = task_data.QuoteStatus;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["QuoteLocalID"] = task_data.QuoteLocalID;
	data["BidVolume"] = task_data.BidVolume;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["CancelTime"] = task_data.CancelTime;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["AskPrice"] = task_data.AskPrice;
	data["SequenceNo"] = task_data.SequenceNo;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombInstrumentGuard(Task task)
{
	PyLock lock;
	CThostFtdcCombInstrumentGuardField task_data = any_cast<CThostFtdcCombInstrumentGuardField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["GuarantRatio"] = task_data.GuarantRatio;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCombInstrumentGuard(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ActionStatus"] = task_data.ActionStatus;
	data["CombDirection"] = task_data.CombDirection;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["SessionID"] = task_data.SessionID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["CombActionRef"] = task_data.CombActionRef;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCombAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	CThostFtdcTransferSerialField task_data = any_cast<CThostFtdcTransferSerialField>(task.task_data);
	dict data;
	data["BankNewAccount"] = task_data.BankNewAccount;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["TradeTime"] = task_data.TradeTime;
	data["OperatorCode"] = task_data.OperatorCode;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureAccType"] = task_data.FutureAccType;
	data["ErrorID"] = task_data.ErrorID;
	data["BankSerial"] = task_data.BankSerial;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["IdCardType"] = task_data.IdCardType;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AvailabilityFlag"] = task_data.AvailabilityFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTransferSerial(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryAccountregister(Task task)
{
	PyLock lock;
	CThostFtdcAccountregisterField task_data = any_cast<CThostFtdcAccountregisterField>(task.task_data);
	dict data;
	data["BankAccount"] = task_data.BankAccount;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = task_data.CustomerName;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["OutDate"] = task_data.OutDate;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankBranchID"] = task_data.BankBranchID;
	data["RegDate"] = task_data.RegDate;
	data["BrokerID"] = task_data.BrokerID;
	data["BankID"] = task_data.BankID;
	data["TID"] = task_data.TID;
	data["OpenOrDestroy"] = task_data.OpenOrDestroy;
	data["IdCardType"] = task_data.IdCardType;
	data["TradeDay"] = task_data.TradeDay;
	data["BankAccType"] = task_data.BankAccType;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryAccountregister(data, error, task.task_id, task.task_last);
};

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ParticipantID"] = task_data.ParticipantID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["ClientID"] = task_data.ClientID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TradeTime"] = task_data.TradeTime;
	data["Direction"] = task_data.Direction;
	data["ParticipantID"] = task_data.ParticipantID;
	data["Price"] = task_data.Price;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["TradeID"] = task_data.TradeID;
	data["TradeDate"] = task_data.TradeDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["TradeSource"] = task_data.TradeSource;
	data["PriceSource"] = task_data.PriceSource;
	data["TradingRole"] = task_data.TradingRole;

	this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderSysID"] = task_data.OrderSysID;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcOrderActionField task_data = any_cast<CThostFtdcOrderActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["InvestorID"] = task_data.InvestorID;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["VolumeChange"] = task_data.VolumeChange;
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["OrderSysID"] = task_data.OrderSysID;
	data["BrokerID"] = task_data.BrokerID;
	data["ClientID"] = task_data.ClientID;
	data["ActionDate"] = task_data.ActionDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentStatusField task_data = any_cast<CThostFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["EnterTime"] = task_data.EnterTime;
	data["SettlementGroupID"] = task_data.SettlementGroupID;
	data["TradingSegmentSN"] = task_data.TradingSegmentSN;
	data["EnterReason"] = task_data.EnterReason;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["ExchangeInstID"] = task_data.ExchangeInstID;

	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeInfoField task_data = any_cast<CThostFtdcTradingNoticeInfoField>(task.task_data);
	dict data;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["SequenceNo"] = task_data.SequenceNo;
	data["FieldContent"] = task_data.FieldContent;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["SendTime"] = task_data.SendTime;

	this->onRtnTradingNotice(data);
};

void TdApi::processRtnErrorConditionalOrder(Task task)
{
	PyLock lock;
	CThostFtdcErrorConditionalOrderField task_data = any_cast<CThostFtdcErrorConditionalOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ParticipantID"] = task_data.ParticipantID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["ClientID"] = task_data.ClientID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["ErrorID"] = task_data.ErrorID;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["OrderSource"] = task_data.OrderSource;
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	this->onRtnErrorConditionalOrder(data);
};

void TdApi::processRtnExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["CloseFlag"] = task_data.CloseFlag;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ExecResult"] = task_data.ExecResult;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["Volume"] = task_data.Volume;
	data["InstallID"] = task_data.InstallID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["ClientID"] = task_data.ClientID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["SessionID"] = task_data.SessionID;
	data["ActionType"] = task_data.ActionType;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ExecOrderLocalID"] = task_data.ExecOrderLocalID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
	data["FrontID"] = task_data.FrontID;

	this->onRtnExecOrder(data);
};

void TdApi::processErrRtnExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["CloseFlag"] = task_data.CloseFlag;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionType"] = task_data.ActionType;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnExecOrderInsert(data, error);
};

void TdApi::processErrRtnExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderActionField task_data = any_cast<CThostFtdcExecOrderActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["SessionID"] = task_data.SessionID;
	data["ActionType"] = task_data.ActionType;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["BrokerID"] = task_data.BrokerID;
	data["ExecOrderLocalID"] = task_data.ExecOrderLocalID;
	data["ActionDate"] = task_data.ActionDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnExecOrderAction(data, error);
};

void TdApi::processErrRtnForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["UserID"] = task_data.UserID;
	data["ForQuoteRef"] = task_data.ForQuoteRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnForQuoteInsert(data, error);
};

void TdApi::processRtnQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BidOrderSysID"] = task_data.BidOrderSysID;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["AskVolume"] = task_data.AskVolume;
	data["BidOrderRef"] = task_data.BidOrderRef;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["AskOrderSysID"] = task_data.AskOrderSysID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["ClientID"] = task_data.ClientID;
	data["SessionID"] = task_data.SessionID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BidPrice"] = task_data.BidPrice;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["InstrumentID"] = task_data.InstrumentID;
	data["QuoteStatus"] = task_data.QuoteStatus;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["QuoteLocalID"] = task_data.QuoteLocalID;
	data["BidVolume"] = task_data.BidVolume;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["CancelTime"] = task_data.CancelTime;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["AskPrice"] = task_data.AskPrice;
	data["SequenceNo"] = task_data.SequenceNo;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
	data["FrontID"] = task_data.FrontID;

	this->onRtnQuote(data);
};

void TdApi::processErrRtnQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["AskPrice"] = task_data.AskPrice;
	data["UserID"] = task_data.UserID;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidVolume"] = task_data.BidVolume;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["AskVolume"] = task_data.AskVolume;
	data["InvestorID"] = task_data.InvestorID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["BidPrice"] = task_data.BidPrice;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["BidOrderRef"] = task_data.BidOrderRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQuoteInsert(data, error);
};

void TdApi::processErrRtnQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcQuoteActionField task_data = any_cast<CThostFtdcQuoteActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["QuoteRef"] = task_data.QuoteRef;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["QuoteActionRef"] = task_data.QuoteActionRef;
	data["StatusMsg"] = task_data.StatusMsg;
	data["QuoteLocalID"] = task_data.QuoteLocalID;
	data["BrokerID"] = task_data.BrokerID;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["ActionDate"] = task_data.ActionDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQuoteAction(data, error);
};

void TdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteRspField task_data = any_cast<CThostFtdcForQuoteRspField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ActionDay"] = task_data.ActionDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["TradingDay"] = task_data.TradingDay;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["ForQuoteTime"] = task_data.ForQuoteTime;

	this->onRtnForQuoteRsp(data);
};

void TdApi::processRtnCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["Token"] = task_data.Token;
	data["KeyID"] = task_data.KeyID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["AccountID"] = task_data.AccountID;

	this->onRtnCFMMCTradingAccountToken(data);
};

void TdApi::processErrRtnBatchOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcBatchOrderActionField task_data = any_cast<CThostFtdcBatchOrderActionField>(task.task_data);
	dict data;
	data["ActionDate"] = task_data.ActionDate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionTime"] = task_data.ActionTime;
	data["StatusMsg"] = task_data.StatusMsg;
	data["ParticipantID"] = task_data.ParticipantID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["ClientID"] = task_data.ClientID;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["InstallID"] = task_data.InstallID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["OrderActionStatus"] = task_data.OrderActionStatus;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnBatchOrderAction(data, error);
};

void TdApi::processRtnCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ActionStatus"] = task_data.ActionStatus;
	data["CombDirection"] = task_data.CombDirection;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["SessionID"] = task_data.SessionID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["CombActionRef"] = task_data.CombActionRef;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["FrontID"] = task_data.FrontID;

	this->onRtnCombAction(data);
};

void TdApi::processErrRtnCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Direction"] = task_data.Direction;
	data["CombActionRef"] = task_data.CombActionRef;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombDirection"] = task_data.CombDirection;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnCombActionInsert(data, error);
};

void TdApi::processRspQryContractBank(Task task)
{
	PyLock lock;
	CThostFtdcContractBankField task_data = any_cast<CThostFtdcContractBankField>(task.task_data);
	dict data;
	data["BankName"] = task_data.BankName;
	data["BrokerID"] = task_data.BrokerID;
	data["BankBrchID"] = task_data.BankBrchID;
	data["BankID"] = task_data.BankID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryContractBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Status"] = task_data.Status;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["UserType"] = task_data.UserType;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["ErrorID"] = task_data.ErrorID;
	data["ParkedOrderID"] = task_data.ParkedOrderID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Status"] = task_data.Status;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserType"] = task_data.UserType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ParkedOrderActionID"] = task_data.ParkedOrderActionID;
	data["FrontID"] = task_data.FrontID;
	data["ErrorID"] = task_data.ErrorID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeField task_data = any_cast<CThostFtdcTradingNoticeField>(task.task_data);
	dict data;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["SequenceNo"] = task_data.SequenceNo;
	data["UserID"] = task_data.UserID;
	data["FieldContent"] = task_data.FieldContent;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["SendTime"] = task_data.SendTime;
	data["InvestorRange"] = task_data.InvestorRange;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingParams(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingParamsField task_data = any_cast<CThostFtdcBrokerTradingParamsField>(task.task_data);
	dict data;
	data["MarginPriceType"] = task_data.MarginPriceType;
	data["Algorithm"] = task_data.Algorithm;
	data["CurrencyID"] = task_data.CurrencyID;
	data["OptionRoyaltyPriceType"] = task_data.OptionRoyaltyPriceType;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AvailIncludeCloseProfit"] = task_data.AvailIncludeCloseProfit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBrokerTradingParams(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingAlgos(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingAlgosField task_data = any_cast<CThostFtdcBrokerTradingAlgosField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["HandlePositionAlgoID"] = task_data.HandlePositionAlgoID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FindMarginRateAlgoID"] = task_data.FindMarginRateAlgoID;
	data["BrokerID"] = task_data.BrokerID;
	data["HandleTradingAccountAlgoID"] = task_data.HandleTradingAccountAlgoID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBrokerTradingAlgos(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcQueryCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcQueryCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryCFMMCTradingAccountToken(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromBankToFutureByBank(data);
};

void TdApi::processRtnFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromFutureToBankByBank(data);
};

void TdApi::processRtnRepealFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromBankToFutureByBank(data);
};

void TdApi::processRtnRepealFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromFutureToBankByBank(data);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromBankToFutureByFuture(data);
};

void TdApi::processRtnFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromFutureToBankByFuture(data);
};

void TdApi::processRtnRepealFromBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromBankToFutureByFutureManual(data);
};

void TdApi::processRtnRepealFromFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromFutureToBankByFutureManual(data);
};

void TdApi::processRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcNotifyQueryAccountField task_data = any_cast<CThostFtdcNotifyQueryAccountField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["BankUseAmount"] = task_data.BankUseAmount;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;
	data["BankFetchAmount"] = task_data.BankFetchAmount;

	this->onRtnQueryBankBalanceByFuture(data);
};

void TdApi::processErrRtnBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnBankToFutureByFuture(data, error);
};

void TdApi::processErrRtnFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFutureToBankByFuture(data, error);
};

void TdApi::processErrRtnRepealBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnRepealBankToFutureByFutureManual(data, error);
};

void TdApi::processErrRtnRepealFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnRepealFutureToBankByFutureManual(data, error);
};

void TdApi::processErrRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQueryBankBalanceByFuture(data, error);
};

void TdApi::processRtnRepealFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromBankToFutureByFuture(data);
};

void TdApi::processRtnRepealFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromFutureToBankByFuture(data);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromBankToFutureByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromFutureToBankByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryBankAccountMoneyByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryBankAccountMoneyByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOpenAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcOpenAccountField task_data = any_cast<CThostFtdcOpenAccountField>(task.task_data);
	dict data;
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["Telephone"] = task_data.Telephone;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["Fax"] = task_data.Fax;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["CountryCode"] = task_data.CountryCode;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["Address"] = task_data.Address;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["CustType"] = task_data.CustType;
	data["Gender"] = task_data.Gender;
	data["BankID"] = task_data.BankID;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["CashExchangeCode"] = task_data.CashExchangeCode;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["MobilePhone"] = task_data.MobilePhone;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["ZipCode"] = task_data.ZipCode;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["TradeTime"] = task_data.TradeTime;
	data["EMail"] = task_data.EMail;
	data["Digest"] = task_data.Digest;
	data["DeviceID"] = task_data.DeviceID;

	this->onRtnOpenAccountByBank(data);
};

void TdApi::processRtnCancelAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcCancelAccountField task_data = any_cast<CThostFtdcCancelAccountField>(task.task_data);
	dict data;
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["Telephone"] = task_data.Telephone;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["Fax"] = task_data.Fax;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["CountryCode"] = task_data.CountryCode;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["Address"] = task_data.Address;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["CustType"] = task_data.CustType;
	data["Gender"] = task_data.Gender;
	data["BankID"] = task_data.BankID;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["CashExchangeCode"] = task_data.CashExchangeCode;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["MobilePhone"] = task_data.MobilePhone;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["ZipCode"] = task_data.ZipCode;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["TradeTime"] = task_data.TradeTime;
	data["EMail"] = task_data.EMail;
	data["Digest"] = task_data.Digest;
	data["DeviceID"] = task_data.DeviceID;

	this->onRtnCancelAccountByBank(data);
};

void TdApi::processRtnChangeAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcChangeAccountField task_data = any_cast<CThostFtdcChangeAccountField>(task.task_data);
	dict data;
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["NewBankPassWord"] = task_data.NewBankPassWord;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["Telephone"] = task_data.Telephone;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["Fax"] = task_data.Fax;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["CountryCode"] = task_data.CountryCode;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["NewBankAccount"] = task_data.NewBankAccount;
	data["Address"] = task_data.Address;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["CustType"] = task_data.CustType;
	data["Gender"] = task_data.Gender;
	data["BankID"] = task_data.BankID;
	data["BankSerial"] = task_data.BankSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["MobilePhone"] = task_data.MobilePhone;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["ZipCode"] = task_data.ZipCode;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["TradeTime"] = task_data.TradeTime;
	data["EMail"] = task_data.EMail;
	data["Digest"] = task_data.Digest;

	this->onRtnChangeAccountByBank(data);
};

