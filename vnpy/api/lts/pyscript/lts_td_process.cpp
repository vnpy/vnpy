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

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CSecurityFtdcRspUserLoginField task_data = any_cast<CSecurityFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["BrokerID"] = task_data.BrokerID;
	data["LoginTime"] = task_data.LoginTime;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CSecurityFtdcUserLogoutField task_data = any_cast<CSecurityFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFetchAuthRandCode(Task task)
{
	PyLock lock;
	CSecurityFtdcAuthRandCodeField task_data = any_cast<CSecurityFtdcAuthRandCodeField>(task.task_data);
	dict data;
	data["RandCode"] = task_data.RandCode;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFetchAuthRandCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CSecurityFtdcInputOrderField task_data = any_cast<CSecurityFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CSecurityFtdcInputOrderActionField task_data = any_cast<CSecurityFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["FrontID"] = task_data.FrontID;
	data["BranchPBU"] = task_data.BranchPBU;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CSecurityFtdcUserPasswordUpdateField task_data = any_cast<CSecurityFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	PyLock lock;
	CSecurityFtdcTradingAccountPasswordUpdateField task_data = any_cast<CSecurityFtdcTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CSecurityFtdcOrderField task_data = any_cast<CSecurityFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["AccountID"] = task_data.AccountID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
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
	data["IsETF"] = task_data.IsETF;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["InstrumentType"] = task_data.InstrumentType;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;
	data["BranchPBU"] = task_data.BranchPBU;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CSecurityFtdcTradeField task_data = any_cast<CSecurityFtdcTradeField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
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
	data["UserID"] = task_data.UserID;
	data["TradeIndex"] = task_data.TradeIndex;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["TradeSource"] = task_data.TradeSource;
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
	data["BranchPBU"] = task_data.BranchPBU;
	data["PriceSource"] = task_data.PriceSource;
	data["TradingRole"] = task_data.TradingRole;
	data["TradeAmount"] = task_data.TradeAmount;

	this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CSecurityFtdcInputOrderField task_data = any_cast<CSecurityFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CSecurityFtdcOrderActionField task_data = any_cast<CSecurityFtdcOrderActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["InvestorID"] = task_data.InvestorID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["ClientID"] = task_data.ClientID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["VolumeChange"] = task_data.VolumeChange;
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["BrokerID"] = task_data.BrokerID;
	data["InstrumentType"] = task_data.InstrumentType;
	data["ActionDate"] = task_data.ActionDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["BranchPBU"] = task_data.BranchPBU;
	data["OrderActionStatus"] = task_data.OrderActionStatus;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRspFundOutByLiber(Task task)
{
	PyLock lock;
	CSecurityFtdcInputFundTransferField task_data = any_cast<CSecurityFtdcInputFundTransferField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountType"] = task_data.AccountType;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFundOutByLiber(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFundOutByLiber(Task task)
{
	PyLock lock;
	CSecurityFtdcFundTransferField task_data = any_cast<CSecurityFtdcFundTransferField>(task.task_data);
	dict data;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["ErrorID"] = task_data.ErrorID;
	data["UserID"] = task_data.UserID;
	data["TransferSerial"] = task_data.TransferSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["LiberSerial"] = task_data.LiberSerial;
	data["BrokerID"] = task_data.BrokerID;
	data["FundDirection"] = task_data.FundDirection;
	data["TradeTime"] = task_data.TradeTime;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	this->onRtnFundOutByLiber(data);
};

void TdApi::processErrRtnFundOutByLiber(Task task)
{
	PyLock lock;
	CSecurityFtdcInputFundTransferField task_data = any_cast<CSecurityFtdcInputFundTransferField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountType"] = task_data.AccountType;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFundOutByLiber(data, error);
};

void TdApi::processRtnFundInByBank(Task task)
{
	PyLock lock;
	CSecurityFtdcFundTransferField task_data = any_cast<CSecurityFtdcFundTransferField>(task.task_data);
	dict data;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["ErrorID"] = task_data.ErrorID;
	data["UserID"] = task_data.UserID;
	data["TransferSerial"] = task_data.TransferSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["LiberSerial"] = task_data.LiberSerial;
	data["BrokerID"] = task_data.BrokerID;
	data["FundDirection"] = task_data.FundDirection;
	data["TradeTime"] = task_data.TradeTime;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	this->onRtnFundInByBank(data);
};

void TdApi::processRspFundInterTransfer(Task task)
{
	PyLock lock;
	CSecurityFtdcFundInterTransferField task_data = any_cast<CSecurityFtdcFundInterTransferField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFundInterTransfer(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFundInterTransferSerial(Task task)
{
	PyLock lock;
	CSecurityFtdcFundInterTransferSerialField task_data = any_cast<CSecurityFtdcFundInterTransferSerialField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["TransferTime"] = task_data.TransferTime;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ErrorID"] = task_data.ErrorID;
	data["AccountID"] = task_data.AccountID;

	this->onRtnFundInterTransferSerial(data);
};

void TdApi::processErrRtnFundInterTransfer(Task task)
{
	PyLock lock;
	CSecurityFtdcFundInterTransferField task_data = any_cast<CSecurityFtdcFundInterTransferField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFundInterTransfer(data, error);
};

