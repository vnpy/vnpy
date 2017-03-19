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
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspAuthenticate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CThostFtdcRspUserLoginField task_data = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["FFEXTime"] = boost::locale::conv::to_utf<char>(task_data.FFEXTime, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CZCETime"] = boost::locale::conv::to_utf<char>(task_data.CZCETime, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["SHFETime"] = boost::locale::conv::to_utf<char>(task_data.SHFETime, std::string("GB2312"));
	data["INETime"] = boost::locale::conv::to_utf<char>(task_data.INETime, std::string("GB2312"));
	data["DCETime"] = boost::locale::conv::to_utf<char>(task_data.DCETime, std::string("GB2312"));
	data["LoginTime"] = boost::locale::conv::to_utf<char>(task_data.LoginTime, std::string("GB2312"));
	data["MaxOrderRef"] = boost::locale::conv::to_utf<char>(task_data.MaxOrderRef, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["SystemName"] = boost::locale::conv::to_utf<char>(task_data.SystemName, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcUserPasswordUpdateField task_data = any_cast<CThostFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["OldPassword"] = boost::locale::conv::to_utf<char>(task_data.OldPassword, std::string("GB2312"));
	data["NewPassword"] = boost::locale::conv::to_utf<char>(task_data.NewPassword, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountPasswordUpdateField task_data = any_cast<CThostFtdcTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["NewPassword"] = boost::locale::conv::to_utf<char>(task_data.NewPassword, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["OldPassword"] = boost::locale::conv::to_utf<char>(task_data.OldPassword, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["TimeCondition"] = task_data.TimeCondition;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserForceClose"] = task_data.UserForceClose;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["MinVolume"] = task_data.MinVolume;
	data["LimitPrice"] = task_data.LimitPrice;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
	data["TimeCondition"] = task_data.TimeCondition;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserType"] = task_data.UserType;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["ParkedOrderID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderID, std::string("GB2312"));
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["ErrorID"] = task_data.ErrorID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserForceClose"] = task_data.UserForceClose;
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["MinVolume"] = task_data.MinVolume;
	data["LimitPrice"] = task_data.LimitPrice;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["Status"] = task_data.Status;
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspParkedOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
	data["UserType"] = task_data.UserType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["LimitPrice"] = task_data.LimitPrice;
	data["ErrorID"] = task_data.ErrorID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["Status"] = task_data.Status;
	data["FrontID"] = task_data.FrontID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["ParkedOrderActionID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderActionID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderActionField task_data = any_cast<CThostFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["LimitPrice"] = task_data.LimitPrice;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryMaxOrderVolume(Task task)
{
	PyLock lock;
	CThostFtdcQueryMaxOrderVolumeField task_data = any_cast<CThostFtdcQueryMaxOrderVolumeField>(task.task_data);
	dict data;
	data["MaxVolume"] = task_data.MaxVolume;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQueryMaxOrderVolume(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmDate"] = boost::locale::conv::to_utf<char>(task_data.ConfirmDate, std::string("GB2312"));
	data["ConfirmTime"] = boost::locale::conv::to_utf<char>(task_data.ConfirmTime, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspSettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderField task_data = any_cast<CThostFtdcRemoveParkedOrderField>(task.task_data);
	dict data;
	data["ParkedOrderID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspRemoveParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderActionField task_data = any_cast<CThostFtdcRemoveParkedOrderActionField>(task.task_data);
	dict data;
	data["ParkedOrderActionID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderActionID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspRemoveParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ActionType"] = task_data.ActionType;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["Volume"] = task_data.Volume;
	data["CloseFlag"] = task_data.CloseFlag;
	data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
	data["PosiDirection"] = task_data.PosiDirection;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["HedgeFlag"] = task_data.HedgeFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspExecOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderActionField task_data = any_cast<CThostFtdcInputExecOrderActionField>(task.task_data);
	dict data;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
	data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspExecOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
	data["ForQuoteRef"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteRef, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspForQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
	data["BidPrice"] = task_data.BidPrice;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
	data["AskPrice"] = task_data.AskPrice;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["AskVolume"] = task_data.AskVolume;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BidVolume"] = task_data.BidVolume;
	data["RequestID"] = task_data.RequestID;
	data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteActionField task_data = any_cast<CThostFtdcInputQuoteActionField>(task.task_data);
	dict data;
	data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["QuoteActionRef"] = task_data.QuoteActionRef;
	data["FrontID"] = task_data.FrontID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQuoteAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspLockInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputLockField task_data = any_cast<CThostFtdcInputLockField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["LockRef"] = boost::locale::conv::to_utf<char>(task_data.LockRef, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["LockType"] = task_data.LockType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspLockInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["CombDirection"] = task_data.CombDirection;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspCombActionInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["RelativeOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.RelativeOrderSysID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActiveTraderID"] = boost::locale::conv::to_utf<char>(task_data.ActiveTraderID, std::string("GB2312"));
	data["ActiveTime"] = boost::locale::conv::to_utf<char>(task_data.ActiveTime, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["RequestID"] = task_data.RequestID;
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["OrderSource"] = task_data.OrderSource;
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["MinVolume"] = task_data.MinVolume;
	data["LimitPrice"] = task_data.LimitPrice;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["NotifySequence"] = task_data.NotifySequence;
	data["UserForceClose"] = task_data.UserForceClose;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;
	data["TimeCondition"] = task_data.TimeCondition;
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["OrderType"] = task_data.OrderType;
	data["SuspendTime"] = boost::locale::conv::to_utf<char>(task_data.SuspendTime, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["SettlementID"] = task_data.SettlementID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["OrderStatus"] = task_data.OrderStatus;
	data["InstallID"] = task_data.InstallID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["TradingRole"] = task_data.TradingRole;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["TradeType"] = task_data.TradeType;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["TradeSource"] = task_data.TradeSource;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
	data["PriceSource"] = task_data.PriceSource;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["Volume"] = task_data.Volume;
	data["Price"] = task_data.Price;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionField task_data = any_cast<CThostFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["ShortFrozen"] = task_data.ShortFrozen;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CashIn"] = task_data.CashIn;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["UseMargin"] = task_data.UseMargin;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["StrikeFrozen"] = task_data.StrikeFrozen;
	data["CombLongFrozen"] = task_data.CombLongFrozen;
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["TodayPosition"] = task_data.TodayPosition;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CombShortFrozen"] = task_data.CombShortFrozen;
	data["YdStrikeFrozen"] = task_data.YdStrikeFrozen;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["OpenVolume"] = task_data.OpenVolume;
	data["CloseVolume"] = task_data.CloseVolume;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["OpenCost"] = task_data.OpenCost;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["OpenAmount"] = task_data.OpenAmount;
	data["StrikeFrozenAmount"] = task_data.StrikeFrozenAmount;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["PositionCost"] = task_data.PositionCost;
	data["LongFrozenAmount"] = task_data.LongFrozenAmount;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["PreMargin"] = task_data.PreMargin;
	data["CloseProfit"] = task_data.CloseProfit;
	data["CloseAmount"] = task_data.CloseAmount;
	data["LongFrozen"] = task_data.LongFrozen;
	data["PosiDirection"] = task_data.PosiDirection;
	data["CombPosition"] = task_data.CombPosition;
	data["YdPosition"] = task_data.YdPosition;
	data["PositionDate"] = task_data.PositionDate;
	data["AbandonFrozen"] = task_data.AbandonFrozen;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["FrozenCash"] = task_data.FrozenCash;
	data["SettlementID"] = task_data.SettlementID;
	data["Position"] = task_data.Position;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountField task_data = any_cast<CThostFtdcTradingAccountField>(task.task_data);
	dict data;
	data["ReserveBalance"] = task_data.ReserveBalance;
	data["Reserve"] = task_data.Reserve;
	data["SpecProductCommission"] = task_data.SpecProductCommission;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CashIn"] = task_data.CashIn;
	data["FundMortgageOut"] = task_data.FundMortgageOut;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["SpecProductPositionProfitByAlg"] = task_data.SpecProductPositionProfitByAlg;
	data["Commission"] = task_data.Commission;
	data["SpecProductPositionProfit"] = task_data.SpecProductPositionProfit;
	data["Deposit"] = task_data.Deposit;
	data["DeliveryMargin"] = task_data.DeliveryMargin;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["Interest"] = task_data.Interest;
	data["PreDeposit"] = task_data.PreDeposit;
	data["Available"] = task_data.Available;
	data["SpecProductFrozenMargin"] = task_data.SpecProductFrozenMargin;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["SpecProductMargin"] = task_data.SpecProductMargin;
	data["PreFundMortgageOut"] = task_data.PreFundMortgageOut;
	data["InterestBase"] = task_data.InterestBase;
	data["SpecProductExchangeMargin"] = task_data.SpecProductExchangeMargin;
	data["PreBalance"] = task_data.PreBalance;
	data["Balance"] = task_data.Balance;
	data["MortgageableFund"] = task_data.MortgageableFund;
	data["Withdraw"] = task_data.Withdraw;
	data["SpecProductFrozenCommission"] = task_data.SpecProductFrozenCommission;
	data["PreMortgage"] = task_data.PreMortgage;
	data["SpecProductCloseProfit"] = task_data.SpecProductCloseProfit;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["FundMortgageAvailable"] = task_data.FundMortgageAvailable;
	data["BizType"] = task_data.BizType;
	data["PreCredit"] = task_data.PreCredit;
	data["FrozenCash"] = task_data.FrozenCash;
	data["SettlementID"] = task_data.SettlementID;
	data["CloseProfit"] = task_data.CloseProfit;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["Mortgage"] = task_data.Mortgage;
	data["Credit"] = task_data.Credit;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FundMortgageIn"] = task_data.FundMortgageIn;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["PreFundMortgageIn"] = task_data.PreFundMortgageIn;
	data["PositionProfit"] = task_data.PositionProfit;
	data["PreMargin"] = task_data.PreMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CThostFtdcInvestorField task_data = any_cast<CThostFtdcInvestorField>(task.task_data);
	dict data;
	data["MarginModelID"] = boost::locale::conv::to_utf<char>(task_data.MarginModelID, std::string("GB2312"));
	data["Mobile"] = boost::locale::conv::to_utf<char>(task_data.Mobile, std::string("GB2312"));
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
	data["IsActive"] = task_data.IsActive;
	data["InvestorName"] = boost::locale::conv::to_utf<char>(task_data.InvestorName, std::string("GB2312"));
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["InvestorGroupID"] = boost::locale::conv::to_utf<char>(task_data.InvestorGroupID, std::string("GB2312"));
	data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));
	data["CommModelID"] = boost::locale::conv::to_utf<char>(task_data.CommModelID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CThostFtdcTradingCodeField task_data = any_cast<CThostFtdcTradingCodeField>(task.task_data);
	dict data;
	data["BizType"] = task_data.BizType;
	data["IsActive"] = task_data.IsActive;
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["ClientIDType"] = task_data.ClientIDType;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentMarginRateField task_data = any_cast<CThostFtdcInstrumentMarginRateField>(task.task_data);
	dict data;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;
	data["InvestorRange"] = task_data.InvestorRange;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["IsRelative"] = task_data.IsRelative;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInstrumentMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentCommissionRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentCommissionRateField task_data = any_cast<CThostFtdcInstrumentCommissionRateField>(task.task_data);
	dict data;
	data["BizType"] = task_data.BizType;
	data["InvestorRange"] = task_data.InvestorRange;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInstrumentCommissionRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CThostFtdcExchangeField task_data = any_cast<CThostFtdcExchangeField>(task.task_data);
	dict data;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ExchangeProperty"] = task_data.ExchangeProperty;
	data["ExchangeName"] = boost::locale::conv::to_utf<char>(task_data.ExchangeName, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProduct(Task task)
{
	PyLock lock;
	CThostFtdcProductField task_data = any_cast<CThostFtdcProductField>(task.task_data);
	dict data;
	data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
	data["ProductClass"] = task_data.ProductClass;
	data["ProductName"] = boost::locale::conv::to_utf<char>(task_data.ProductName, std::string("GB2312"));
	data["TradeCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.TradeCurrencyID, std::string("GB2312"));
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["MortgageFundUseRange"] = task_data.MortgageFundUseRange;
	data["ExchangeProductID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeProductID, std::string("GB2312"));
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["PositionDateType"] = task_data.PositionDateType;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["PositionType"] = task_data.PositionType;
	data["PriceTick"] = task_data.PriceTick;
	data["CloseDealType"] = task_data.CloseDealType;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryProduct(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentField task_data = any_cast<CThostFtdcInstrumentField>(task.task_data);
	dict data;
	data["ShortMarginRatio"] = task_data.ShortMarginRatio;
	data["EndDelivDate"] = boost::locale::conv::to_utf<char>(task_data.EndDelivDate, std::string("GB2312"));
	data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
	data["PriceTick"] = task_data.PriceTick;
	data["PositionType"] = task_data.PositionType;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["MinSellVolume"] = task_data.MinSellVolume;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["InstrumentName"] = boost::locale::conv::to_utf<char>(task_data.InstrumentName, std::string("GB2312"));
	data["InstrumentCode"] = boost::locale::conv::to_utf<char>(task_data.InstrumentCode, std::string("GB2312"));
	data["IsTrading"] = task_data.IsTrading;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["LongMarginRatio"] = task_data.LongMarginRatio;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["OptionsType"] = task_data.OptionsType;
	data["CreateDate"] = boost::locale::conv::to_utf<char>(task_data.CreateDate, std::string("GB2312"));
	data["ProductClass"] = task_data.ProductClass;
	data["CombinationType"] = task_data.CombinationType;
	data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
	data["MinBuyVolume"] = task_data.MinBuyVolume;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["UnderlyingInstrID"] = boost::locale::conv::to_utf<char>(task_data.UnderlyingInstrID, std::string("GB2312"));
	data["PositionDateType"] = task_data.PositionDateType;
	data["ExpireDate"] = boost::locale::conv::to_utf<char>(task_data.ExpireDate, std::string("GB2312"));
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["MaxMarginSideAlgorithm"] = task_data.MaxMarginSideAlgorithm;
	data["StartDelivDate"] = boost::locale::conv::to_utf<char>(task_data.StartDelivDate, std::string("GB2312"));
	data["StrikePrice"] = task_data.StrikePrice;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["ActionDay"] = boost::locale::conv::to_utf<char>(task_data.ActionDay, std::string("GB2312"));
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["PreDelta"] = task_data.PreDelta;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["BidVolume1"] = task_data.BidVolume1;
	data["Turnover"] = task_data.Turnover;
	data["BidVolume4"] = task_data.BidVolume4;
	data["OpenPrice"] = task_data.OpenPrice;
	data["LastPrice"] = task_data.LastPrice;
	data["CurrDelta"] = task_data.CurrDelta;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["AskVolume4"] = task_data.AskVolume4;
	data["BidPrice2"] = task_data.BidPrice2;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["AskPrice2"] = task_data.AskPrice2;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["Volume"] = task_data.Volume;
	data["OpenInterest"] = task_data.OpenInterest;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["HighestPrice"] = task_data.HighestPrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
	data["LowestPrice"] = task_data.LowestPrice;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["BidPrice3"] = task_data.BidPrice3;
	data["AveragePrice"] = task_data.AveragePrice;
	data["BidPrice4"] = task_data.BidPrice4;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["BidVolume2"] = task_data.BidVolume2;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["AskVolume5"] = task_data.AskVolume5;
	data["AskVolume1"] = task_data.AskVolume1;
	data["AskPrice5"] = task_data.AskPrice5;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidPrice1"] = task_data.BidPrice1;
	data["BidPrice5"] = task_data.BidPrice5;
	data["AskPrice3"] = task_data.AskPrice3;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["ClosePrice"] = task_data.ClosePrice;
	data["BidVolume3"] = task_data.BidVolume3;
	data["AskPrice4"] = task_data.AskPrice4;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfo(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoField task_data = any_cast<CThostFtdcSettlementInfoField>(task.task_data);
	dict data;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["Content"] = boost::locale::conv::to_utf<char>(task_data.Content, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["SequenceNo"] = task_data.SequenceNo;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySettlementInfo(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferBank(Task task)
{
	PyLock lock;
	CThostFtdcTransferBankField task_data = any_cast<CThostFtdcTransferBankField>(task.task_data);
	dict data;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["BankBrchID"] = boost::locale::conv::to_utf<char>(task_data.BankBrchID, std::string("GB2312"));
	data["BankName"] = boost::locale::conv::to_utf<char>(task_data.BankName, std::string("GB2312"));
	data["IsActive"] = task_data.IsActive;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTransferBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionDetailField task_data = any_cast<CThostFtdcInvestorPositionDetailField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["PositionProfitByTrade"] = task_data.PositionProfitByTrade;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["OpenPrice"] = task_data.OpenPrice;
	data["PositionProfitByDate"] = task_data.PositionProfitByDate;
	data["CloseAmount"] = task_data.CloseAmount;
	data["Margin"] = task_data.Margin;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
	data["ExchMargin"] = task_data.ExchMargin;
	data["Volume"] = task_data.Volume;
	data["CloseVolume"] = task_data.CloseVolume;
	data["LastSettlementPrice"] = task_data.LastSettlementPrice;
	data["Direction"] = task_data.Direction;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["SettlementID"] = task_data.SettlementID;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["CombInstrumentID"] = boost::locale::conv::to_utf<char>(task_data.CombInstrumentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorPositionDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryNotice(Task task)
{
	PyLock lock;
	CThostFtdcNoticeField task_data = any_cast<CThostFtdcNoticeField>(task.task_data);
	dict data;
	data["SequenceLabel"] = boost::locale::conv::to_utf<char>(task_data.SequenceLabel, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["Content"] = boost::locale::conv::to_utf<char>(task_data.Content, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmDate"] = boost::locale::conv::to_utf<char>(task_data.ConfirmDate, std::string("GB2312"));
	data["ConfirmTime"] = boost::locale::conv::to_utf<char>(task_data.ConfirmTime, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionCombineDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionCombineDetailField task_data = any_cast<CThostFtdcInvestorPositionCombineDetailField>(task.task_data);
	dict data;
	data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
	data["ExchMargin"] = task_data.ExchMargin;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["TradeGroupID"] = task_data.TradeGroupID;
	data["ComTradeID"] = boost::locale::conv::to_utf<char>(task_data.ComTradeID, std::string("GB2312"));
	data["LegMultiple"] = task_data.LegMultiple;
	data["LegID"] = task_data.LegID;
	data["CombInstrumentID"] = boost::locale::conv::to_utf<char>(task_data.CombInstrumentID, std::string("GB2312"));
	data["Margin"] = task_data.Margin;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["TotalAmt"] = task_data.TotalAmt;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorPositionCombineDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCFMMCTradingAccountKey(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountKeyField task_data = any_cast<CThostFtdcCFMMCTradingAccountKeyField>(task.task_data);
	dict data;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["CurrentKey"] = boost::locale::conv::to_utf<char>(task_data.CurrentKey, std::string("GB2312"));
	data["KeyID"] = task_data.KeyID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryCFMMCTradingAccountKey(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryEWarrantOffset(Task task)
{
	PyLock lock;
	CThostFtdcEWarrantOffsetField task_data = any_cast<CThostFtdcEWarrantOffsetField>(task.task_data);
	dict data;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryEWarrantOffset(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorProductGroupMargin(Task task)
{
	PyLock lock;
	CThostFtdcInvestorProductGroupMarginField task_data = any_cast<CThostFtdcInvestorProductGroupMarginField>(task.task_data);
	dict data;
	data["ShortOffsetAmount"] = task_data.ShortOffsetAmount;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["LongOffsetAmount"] = task_data.LongOffsetAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["SettlementID"] = task_data.SettlementID;
	data["LongExchOffsetAmount"] = task_data.LongExchOffsetAmount;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CashIn"] = task_data.CashIn;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["ShortExchMargin"] = task_data.ShortExchMargin;
	data["CloseProfit"] = task_data.CloseProfit;
	data["UseMargin"] = task_data.UseMargin;
	data["OffsetAmount"] = task_data.OffsetAmount;
	data["ShortExchOffsetAmount"] = task_data.ShortExchOffsetAmount;
	data["LongUseMargin"] = task_data.LongUseMargin;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["ProductGroupID"] = boost::locale::conv::to_utf<char>(task_data.ProductGroupID, std::string("GB2312"));
	data["FrozenCash"] = task_data.FrozenCash;
	data["ExchMargin"] = task_data.ExchMargin;
	data["ShortUseMargin"] = task_data.ShortUseMargin;
	data["LongExchMargin"] = task_data.LongExchMargin;
	data["ExchOffsetAmount"] = task_data.ExchOffsetAmount;
	data["LongFrozenMargin"] = task_data.LongFrozenMargin;
	data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorProductGroupMargin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateField task_data = any_cast<CThostFtdcExchangeMarginRateField>(task.task_data);
	dict data;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchangeMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRateAdjust(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateAdjustField task_data = any_cast<CThostFtdcExchangeMarginRateAdjustField>(task.task_data);
	dict data;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;
	data["NoLongMarginRatioByMoney"] = task_data.NoLongMarginRatioByMoney;
	data["NoLongMarginRatioByVolume"] = task_data.NoLongMarginRatioByVolume;
	data["NoShortMarginRatioByMoney"] = task_data.NoShortMarginRatioByMoney;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["ExchLongMarginRatioByMoney"] = task_data.ExchLongMarginRatioByMoney;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ExchShortMarginRatioByVolume"] = task_data.ExchShortMarginRatioByVolume;
	data["ExchShortMarginRatioByMoney"] = task_data.ExchShortMarginRatioByMoney;
	data["NoShortMarginRatioByVolume"] = task_data.NoShortMarginRatioByVolume;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["ExchLongMarginRatioByVolume"] = task_data.ExchLongMarginRatioByVolume;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchangeMarginRateAdjust(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeRateField task_data = any_cast<CThostFtdcExchangeRateField>(task.task_data);
	dict data;
	data["FromCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.FromCurrencyID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FromCurrencyUnit"] = task_data.FromCurrencyUnit;
	data["ExchangeRate"] = task_data.ExchangeRate;
	data["ToCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.ToCurrencyID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchangeRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySecAgentACIDMap(Task task)
{
	PyLock lock;
	CThostFtdcSecAgentACIDMapField task_data = any_cast<CThostFtdcSecAgentACIDMapField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BrokerSecAgentID"] = boost::locale::conv::to_utf<char>(task_data.BrokerSecAgentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySecAgentACIDMap(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductExchRate(Task task)
{
	PyLock lock;
	CThostFtdcProductExchRateField task_data = any_cast<CThostFtdcProductExchRateField>(task.task_data);
	dict data;
	data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
	data["ExchangeRate"] = task_data.ExchangeRate;
	data["QuoteCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.QuoteCurrencyID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryProductExchRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductGroup(Task task)
{
	PyLock lock;
	CThostFtdcProductGroupField task_data = any_cast<CThostFtdcProductGroupField>(task.task_data);
	dict data;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
	data["ProductGroupID"] = boost::locale::conv::to_utf<char>(task_data.ProductGroupID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryProductGroup(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrTradeCost(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrTradeCostField task_data = any_cast<CThostFtdcOptionInstrTradeCostField>(task.task_data);
	dict data;
	data["Royalty"] = task_data.Royalty;
	data["ExchMiniMargin"] = task_data.ExchMiniMargin;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["MiniMargin"] = task_data.MiniMargin;
	data["ExchFixedMargin"] = task_data.ExchFixedMargin;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["FixedMargin"] = task_data.FixedMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryOptionInstrTradeCost(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrCommRate(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrCommRateField task_data = any_cast<CThostFtdcOptionInstrCommRateField>(task.task_data);
	dict data;
	data["InvestorRange"] = task_data.InvestorRange;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["StrikeRatioByMoney"] = task_data.StrikeRatioByMoney;
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["StrikeRatioByVolume"] = task_data.StrikeRatioByVolume;
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryOptionInstrCommRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["CloseFlag"] = task_data.CloseFlag;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["ExecOrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderLocalID, std::string("GB2312"));
	data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["ActionType"] = task_data.ActionType;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["Volume"] = task_data.Volume;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["ExecResult"] = task_data.ExecResult;
	data["InstallID"] = task_data.InstallID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExecOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryForQuote(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteField task_data = any_cast<CThostFtdcForQuoteField>(task.task_data);
	dict data;
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["BrokerForQutoSeq"] = task_data.BrokerForQutoSeq;
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["ForQuoteStatus"] = task_data.ForQuoteStatus;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["ForQuoteRef"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteRef, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["ForQuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteLocalID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryForQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
	data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["SettlementID"] = task_data.SettlementID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["AskOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.AskOrderSysID, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["BidPrice"] = task_data.BidPrice;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
	data["NotifySequence"] = task_data.NotifySequence;
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
	data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["QuoteStatus"] = task_data.QuoteStatus;
	data["AskVolume"] = task_data.AskVolume;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidVolume"] = task_data.BidVolume;
	data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
	data["AskPrice"] = task_data.AskPrice;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["BidOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.BidOrderSysID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["QuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.QuoteLocalID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryLock(Task task)
{
	PyLock lock;
	CThostFtdcLockField task_data = any_cast<CThostFtdcLockField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["LockStatus"] = task_data.LockStatus;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["LockRef"] = boost::locale::conv::to_utf<char>(task_data.LockRef, std::string("GB2312"));
	data["LockType"] = task_data.LockType;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["BrokerLockSeq"] = task_data.BrokerLockSeq;
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["LockSysID"] = boost::locale::conv::to_utf<char>(task_data.LockSysID, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["LockLocalID"] = boost::locale::conv::to_utf<char>(task_data.LockLocalID, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["Volume"] = task_data.Volume;
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["NotifySequence"] = task_data.NotifySequence;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryLock(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryLockPosition(Task task)
{
	PyLock lock;
	CThostFtdcLockPositionField task_data = any_cast<CThostFtdcLockPositionField>(task.task_data);
	dict data;
	data["FrozenVolume"] = task_data.FrozenVolume;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryLockPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorLevel(Task task)
{
	PyLock lock;
	CThostFtdcInvestorLevelField task_data = any_cast<CThostFtdcInvestorLevelField>(task.task_data);
	dict data;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["LevelType"] = task_data.LevelType;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorLevel(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecFreeze(Task task)
{
	PyLock lock;
	CThostFtdcExecFreezeField task_data = any_cast<CThostFtdcExecFreezeField>(task.task_data);
	dict data;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["Volume"] = task_data.Volume;
	data["PosiDirection"] = task_data.PosiDirection;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FrozenAmount"] = task_data.FrozenAmount;
	data["OptionsType"] = task_data.OptionsType;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExecFreeze(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombInstrumentGuard(Task task)
{
	PyLock lock;
	CThostFtdcCombInstrumentGuardField task_data = any_cast<CThostFtdcCombInstrumentGuardField>(task.task_data);
	dict data;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["GuarantRatio"] = task_data.GuarantRatio;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryCombInstrumentGuard(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["CombDirection"] = task_data.CombDirection;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["Volume"] = task_data.Volume;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["ActionStatus"] = task_data.ActionStatus;
	data["InstallID"] = task_data.InstallID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryCombAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	CThostFtdcTransferSerialField task_data = any_cast<CThostFtdcTransferSerialField>(task.task_data);
	dict data;
	data["BankNewAccount"] = boost::locale::conv::to_utf<char>(task_data.BankNewAccount, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["OperatorCode"] = boost::locale::conv::to_utf<char>(task_data.OperatorCode, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["AvailabilityFlag"] = task_data.AvailabilityFlag;
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["FutureAccType"] = task_data.FutureAccType;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTransferSerial(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryAccountregister(Task task)
{
	PyLock lock;
	CThostFtdcAccountregisterField task_data = any_cast<CThostFtdcAccountregisterField>(task.task_data);
	dict data;
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["TradeDay"] = boost::locale::conv::to_utf<char>(task_data.TradeDay, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["OutDate"] = boost::locale::conv::to_utf<char>(task_data.OutDate, std::string("GB2312"));
	data["OpenOrDestroy"] = task_data.OpenOrDestroy;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["RegDate"] = boost::locale::conv::to_utf<char>(task_data.RegDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryAccountregister(data, error, task.task_id, task.task_last);
};

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["RelativeOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.RelativeOrderSysID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActiveTraderID"] = boost::locale::conv::to_utf<char>(task_data.ActiveTraderID, std::string("GB2312"));
	data["ActiveTime"] = boost::locale::conv::to_utf<char>(task_data.ActiveTime, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["RequestID"] = task_data.RequestID;
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["OrderSource"] = task_data.OrderSource;
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["MinVolume"] = task_data.MinVolume;
	data["LimitPrice"] = task_data.LimitPrice;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["NotifySequence"] = task_data.NotifySequence;
	data["UserForceClose"] = task_data.UserForceClose;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;
	data["TimeCondition"] = task_data.TimeCondition;
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["OrderType"] = task_data.OrderType;
	data["SuspendTime"] = boost::locale::conv::to_utf<char>(task_data.SuspendTime, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["SettlementID"] = task_data.SettlementID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["OrderStatus"] = task_data.OrderStatus;
	data["InstallID"] = task_data.InstallID;

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["TradingRole"] = task_data.TradingRole;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["TradeType"] = task_data.TradeType;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["TradeSource"] = task_data.TradeSource;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
	data["PriceSource"] = task_data.PriceSource;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["Volume"] = task_data.Volume;
	data["Price"] = task_data.Price;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;

	this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["TimeCondition"] = task_data.TimeCondition;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserForceClose"] = task_data.UserForceClose;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["MinVolume"] = task_data.MinVolume;
	data["LimitPrice"] = task_data.LimitPrice;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcOrderActionField task_data = any_cast<CThostFtdcOrderActionField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
	data["ActionDate"] = boost::locale::conv::to_utf<char>(task_data.ActionDate, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["ActionTime"] = boost::locale::conv::to_utf<char>(task_data.ActionTime, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentStatusField task_data = any_cast<CThostFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["EnterTime"] = boost::locale::conv::to_utf<char>(task_data.EnterTime, std::string("GB2312"));
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["EnterReason"] = task_data.EnterReason;
	data["SettlementGroupID"] = boost::locale::conv::to_utf<char>(task_data.SettlementGroupID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["TradingSegmentSN"] = task_data.TradingSegmentSN;
	data["InstrumentStatus"] = task_data.InstrumentStatus;

	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeInfoField task_data = any_cast<CThostFtdcTradingNoticeInfoField>(task.task_data);
	dict data;
	data["FieldContent"] = boost::locale::conv::to_utf<char>(task_data.FieldContent, std::string("GB2312"));
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["SendTime"] = boost::locale::conv::to_utf<char>(task_data.SendTime, std::string("GB2312"));

	this->onRtnTradingNotice(data);
};

void TdApi::processRtnErrorConditionalOrder(Task task)
{
	PyLock lock;
	CThostFtdcErrorConditionalOrderField task_data = any_cast<CThostFtdcErrorConditionalOrderField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["RelativeOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.RelativeOrderSysID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["ErrorID"] = task_data.ErrorID;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActiveTraderID"] = boost::locale::conv::to_utf<char>(task_data.ActiveTraderID, std::string("GB2312"));
	data["ActiveTime"] = boost::locale::conv::to_utf<char>(task_data.ActiveTime, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["RequestID"] = task_data.RequestID;
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["OrderSource"] = task_data.OrderSource;
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["MinVolume"] = task_data.MinVolume;
	data["LimitPrice"] = task_data.LimitPrice;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["NotifySequence"] = task_data.NotifySequence;
	data["UserForceClose"] = task_data.UserForceClose;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;
	data["TimeCondition"] = task_data.TimeCondition;
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["OrderType"] = task_data.OrderType;
	data["SuspendTime"] = boost::locale::conv::to_utf<char>(task_data.SuspendTime, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["SettlementID"] = task_data.SettlementID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["OrderStatus"] = task_data.OrderStatus;
	data["InstallID"] = task_data.InstallID;

	this->onRtnErrorConditionalOrder(data);
};

void TdApi::processRtnExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["CloseFlag"] = task_data.CloseFlag;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["ExecOrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderLocalID, std::string("GB2312"));
	data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["ActionType"] = task_data.ActionType;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["Volume"] = task_data.Volume;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["ExecResult"] = task_data.ExecResult;
	data["InstallID"] = task_data.InstallID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	this->onRtnExecOrder(data);
};

void TdApi::processErrRtnExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ActionType"] = task_data.ActionType;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["Volume"] = task_data.Volume;
	data["CloseFlag"] = task_data.CloseFlag;
	data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
	data["PosiDirection"] = task_data.PosiDirection;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["HedgeFlag"] = task_data.HedgeFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnExecOrderInsert(data, error);
};

void TdApi::processErrRtnExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderActionField task_data = any_cast<CThostFtdcExecOrderActionField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ActionDate"] = boost::locale::conv::to_utf<char>(task_data.ActionDate, std::string("GB2312"));
	data["ActionFlag"] = task_data.ActionFlag;
	data["RequestID"] = task_data.RequestID;
	data["SessionID"] = task_data.SessionID;
	data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
	data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["ActionType"] = task_data.ActionType;
	data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["ExecOrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderLocalID, std::string("GB2312"));
	data["ActionTime"] = boost::locale::conv::to_utf<char>(task_data.ActionTime, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnExecOrderAction(data, error);
};

void TdApi::processErrRtnForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
	data["ForQuoteRef"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteRef, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnForQuoteInsert(data, error);
};

void TdApi::processRtnQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
	data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["SettlementID"] = task_data.SettlementID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["AskOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.AskOrderSysID, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["BidPrice"] = task_data.BidPrice;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
	data["NotifySequence"] = task_data.NotifySequence;
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
	data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["QuoteStatus"] = task_data.QuoteStatus;
	data["AskVolume"] = task_data.AskVolume;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidVolume"] = task_data.BidVolume;
	data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
	data["AskPrice"] = task_data.AskPrice;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["BidOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.BidOrderSysID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["QuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.QuoteLocalID, std::string("GB2312"));

	this->onRtnQuote(data);
};

void TdApi::processErrRtnQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
	data["BidPrice"] = task_data.BidPrice;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
	data["AskPrice"] = task_data.AskPrice;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["AskVolume"] = task_data.AskVolume;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BidVolume"] = task_data.BidVolume;
	data["RequestID"] = task_data.RequestID;
	data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnQuoteInsert(data, error);
};

void TdApi::processErrRtnQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcQuoteActionField task_data = any_cast<CThostFtdcQuoteActionField>(task.task_data);
	dict data;
	data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ActionDate"] = boost::locale::conv::to_utf<char>(task_data.ActionDate, std::string("GB2312"));
	data["ActionFlag"] = task_data.ActionFlag;
	data["RequestID"] = task_data.RequestID;
	data["SessionID"] = task_data.SessionID;
	data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["QuoteActionRef"] = task_data.QuoteActionRef;
	data["FrontID"] = task_data.FrontID;
	data["ActionTime"] = boost::locale::conv::to_utf<char>(task_data.ActionTime, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["QuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.QuoteLocalID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnQuoteAction(data, error);
};

void TdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteRspField task_data = any_cast<CThostFtdcForQuoteRspField>(task.task_data);
	dict data;
	data["ActionDay"] = boost::locale::conv::to_utf<char>(task_data.ActionDay, std::string("GB2312"));
	data["ForQuoteTime"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteTime, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));

	this->onRtnForQuoteRsp(data);
};

void TdApi::processRtnCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["Token"] = boost::locale::conv::to_utf<char>(task_data.Token, std::string("GB2312"));
	data["KeyID"] = task_data.KeyID;

	this->onRtnCFMMCTradingAccountToken(data);
};

void TdApi::processRtnLock(Task task)
{
	PyLock lock;
	CThostFtdcLockField task_data = any_cast<CThostFtdcLockField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
	data["LockStatus"] = task_data.LockStatus;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["LockRef"] = boost::locale::conv::to_utf<char>(task_data.LockRef, std::string("GB2312"));
	data["LockType"] = task_data.LockType;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["BrokerLockSeq"] = task_data.BrokerLockSeq;
	data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["LockSysID"] = boost::locale::conv::to_utf<char>(task_data.LockSysID, std::string("GB2312"));
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["FrontID"] = task_data.FrontID;
	data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["LockLocalID"] = boost::locale::conv::to_utf<char>(task_data.LockLocalID, std::string("GB2312"));
	data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["Volume"] = task_data.Volume;
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["NotifySequence"] = task_data.NotifySequence;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	this->onRtnLock(data);
};

void TdApi::processErrRtnLockInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputLockField task_data = any_cast<CThostFtdcInputLockField>(task.task_data);
	dict data;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["LockRef"] = boost::locale::conv::to_utf<char>(task_data.LockRef, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["LockType"] = task_data.LockType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnLockInsert(data, error);
};

void TdApi::processRtnCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["CombDirection"] = task_data.CombDirection;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["SettlementID"] = task_data.SettlementID;
	data["Volume"] = task_data.Volume;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
	data["ActionStatus"] = task_data.ActionStatus;
	data["InstallID"] = task_data.InstallID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	this->onRtnCombAction(data);
};

void TdApi::processErrRtnCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["CombDirection"] = task_data.CombDirection;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnCombActionInsert(data, error);
};

void TdApi::processRspQryContractBank(Task task)
{
	PyLock lock;
	CThostFtdcContractBankField task_data = any_cast<CThostFtdcContractBankField>(task.task_data);
	dict data;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["BankBrchID"] = boost::locale::conv::to_utf<char>(task_data.BankBrchID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["BankName"] = boost::locale::conv::to_utf<char>(task_data.BankName, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryContractBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
	data["TimeCondition"] = task_data.TimeCondition;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserType"] = task_data.UserType;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["ParkedOrderID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderID, std::string("GB2312"));
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["ErrorID"] = task_data.ErrorID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserForceClose"] = task_data.UserForceClose;
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["MinVolume"] = task_data.MinVolume;
	data["LimitPrice"] = task_data.LimitPrice;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["Status"] = task_data.Status;
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
	data["UserType"] = task_data.UserType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["LimitPrice"] = task_data.LimitPrice;
	data["ErrorID"] = task_data.ErrorID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["Status"] = task_data.Status;
	data["FrontID"] = task_data.FrontID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["ParkedOrderActionID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderActionID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeField task_data = any_cast<CThostFtdcTradingNoticeField>(task.task_data);
	dict data;
	data["FieldContent"] = boost::locale::conv::to_utf<char>(task_data.FieldContent, std::string("GB2312"));
	data["InvestorRange"] = task_data.InvestorRange;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["SendTime"] = boost::locale::conv::to_utf<char>(task_data.SendTime, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTradingNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingParams(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingParamsField task_data = any_cast<CThostFtdcBrokerTradingParamsField>(task.task_data);
	dict data;
	data["MarginPriceType"] = task_data.MarginPriceType;
	data["Algorithm"] = task_data.Algorithm;
	data["OptionRoyaltyPriceType"] = task_data.OptionRoyaltyPriceType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["AvailIncludeCloseProfit"] = task_data.AvailIncludeCloseProfit;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryBrokerTradingParams(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingAlgos(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingAlgosField task_data = any_cast<CThostFtdcBrokerTradingAlgosField>(task.task_data);
	dict data;
	data["HandlePositionAlgoID"] = task_data.HandlePositionAlgoID;
	data["HandleTradingAccountAlgoID"] = task_data.HandleTradingAccountAlgoID;
	data["FindMarginRateAlgoID"] = task_data.FindMarginRateAlgoID;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryBrokerTradingAlgos(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcQueryCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcQueryCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQueryCFMMCTradingAccountToken(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["InstallID"] = task_data.InstallID;

	this->onRtnFromBankToFutureByBank(data);
};

void TdApi::processRtnFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["InstallID"] = task_data.InstallID;

	this->onRtnFromFutureToBankByBank(data);
};

void TdApi::processRtnRepealFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	this->onRtnRepealFromBankToFutureByBank(data);
};

void TdApi::processRtnRepealFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	this->onRtnRepealFromFutureToBankByBank(data);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["InstallID"] = task_data.InstallID;

	this->onRtnFromBankToFutureByFuture(data);
};

void TdApi::processRtnFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["InstallID"] = task_data.InstallID;

	this->onRtnFromFutureToBankByFuture(data);
};

void TdApi::processRtnRepealFromBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	this->onRtnRepealFromBankToFutureByFutureManual(data);
};

void TdApi::processRtnRepealFromFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	this->onRtnRepealFromFutureToBankByFutureManual(data);
};

void TdApi::processRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcNotifyQueryAccountField task_data = any_cast<CThostFtdcNotifyQueryAccountField>(task.task_data);
	dict data;
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["BankUseAmount"] = task_data.BankUseAmount;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateSerial"] = task_data.PlateSerial;
	data["ErrorID"] = task_data.ErrorID;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["BankFetchAmount"] = task_data.BankFetchAmount;
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	this->onRtnQueryBankBalanceByFuture(data);
};

void TdApi::processErrRtnBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BrokerFee"] = task_data.BrokerFee;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["RequestID"] = task_data.RequestID;
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnBankToFutureByFuture(data, error);
};

void TdApi::processErrRtnFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BrokerFee"] = task_data.BrokerFee;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["RequestID"] = task_data.RequestID;
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnFutureToBankByFuture(data, error);
};

void TdApi::processErrRtnRepealBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnRepealBankToFutureByFutureManual(data, error);
};

void TdApi::processErrRtnRepealFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnRepealFutureToBankByFutureManual(data, error);
};

void TdApi::processErrRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnQueryBankBalanceByFuture(data, error);
};

void TdApi::processRtnRepealFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	this->onRtnRepealFromBankToFutureByFuture(data);
};

void TdApi::processRtnRepealFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerFee"] = task_data.BrokerFee;
	data["ErrorID"] = task_data.ErrorID;
	data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RequestID"] = task_data.RequestID;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["LastFragment"] = task_data.LastFragment;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;

	this->onRtnRepealFromFutureToBankByFuture(data);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BrokerFee"] = task_data.BrokerFee;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["RequestID"] = task_data.RequestID;
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspFromBankToFutureByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BrokerFee"] = task_data.BrokerFee;
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["TradeAmount"] = task_data.TradeAmount;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["RequestID"] = task_data.RequestID;
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["CustFee"] = task_data.CustFee;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspFromFutureToBankByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryBankAccountMoneyByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FutureSerial"] = task_data.FutureSerial;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQueryBankAccountMoneyByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOpenAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcOpenAccountField task_data = any_cast<CThostFtdcOpenAccountField>(task.task_data);
	dict data;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["EMail"] = boost::locale::conv::to_utf<char>(task_data.EMail, std::string("GB2312"));
	data["ZipCode"] = boost::locale::conv::to_utf<char>(task_data.ZipCode, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ErrorID"] = task_data.ErrorID;
	data["Fax"] = boost::locale::conv::to_utf<char>(task_data.Fax, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["MobilePhone"] = boost::locale::conv::to_utf<char>(task_data.MobilePhone, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["CountryCode"] = boost::locale::conv::to_utf<char>(task_data.CountryCode, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["Gender"] = task_data.Gender;
	data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
	data["CashExchangeCode"] = task_data.CashExchangeCode;
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["InstallID"] = task_data.InstallID;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;

	this->onRtnOpenAccountByBank(data);
};

void TdApi::processRtnCancelAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcCancelAccountField task_data = any_cast<CThostFtdcCancelAccountField>(task.task_data);
	dict data;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["PlateSerial"] = task_data.PlateSerial;
	data["EMail"] = boost::locale::conv::to_utf<char>(task_data.EMail, std::string("GB2312"));
	data["ZipCode"] = boost::locale::conv::to_utf<char>(task_data.ZipCode, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ErrorID"] = task_data.ErrorID;
	data["Fax"] = boost::locale::conv::to_utf<char>(task_data.Fax, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["MobilePhone"] = boost::locale::conv::to_utf<char>(task_data.MobilePhone, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
	data["CountryCode"] = boost::locale::conv::to_utf<char>(task_data.CountryCode, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["Gender"] = task_data.Gender;
	data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
	data["CashExchangeCode"] = task_data.CashExchangeCode;
	data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["InstallID"] = task_data.InstallID;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;

	this->onRtnCancelAccountByBank(data);
};

void TdApi::processRtnChangeAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcChangeAccountField task_data = any_cast<CThostFtdcChangeAccountField>(task.task_data);
	dict data;
	data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
	data["NewBankAccount"] = boost::locale::conv::to_utf<char>(task_data.NewBankAccount, std::string("GB2312"));
	data["CountryCode"] = boost::locale::conv::to_utf<char>(task_data.CountryCode, std::string("GB2312"));
	data["EMail"] = boost::locale::conv::to_utf<char>(task_data.EMail, std::string("GB2312"));
	data["LastFragment"] = task_data.LastFragment;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
	data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
	data["TID"] = task_data.TID;
	data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
	data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["Fax"] = boost::locale::conv::to_utf<char>(task_data.Fax, std::string("GB2312"));
	data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
	data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
	data["IdCardType"] = task_data.IdCardType;
	data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
	data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["BankAccType"] = task_data.BankAccType;
	data["MobilePhone"] = boost::locale::conv::to_utf<char>(task_data.MobilePhone, std::string("GB2312"));
	data["Gender"] = task_data.Gender;
	data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
	data["ErrorID"] = task_data.ErrorID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
	data["ZipCode"] = boost::locale::conv::to_utf<char>(task_data.ZipCode, std::string("GB2312"));
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["NewBankPassWord"] = boost::locale::conv::to_utf<char>(task_data.NewBankPassWord, std::string("GB2312"));
	data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));

	this->onRtnChangeAccountByBank(data);
};

