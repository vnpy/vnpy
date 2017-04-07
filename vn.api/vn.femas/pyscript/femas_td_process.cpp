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

void TdApi::processPackageStart(Task task)
{
	PyLock lock;
	this->onPackageStart(task.task_id, task.task_id);
};

void TdApi::processPackageEnd(Task task)
{
	PyLock lock;
	this->onPackageEnd(task.task_id, task.task_id);
};

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CUstpFtdcRspUserLoginField task_data = any_cast<CUstpFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["PrivateFlowSize"] = task_data.PrivateFlowSize;
	data["UserID"] = task_data.UserID;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxOrderLocalID"] = task_data.MaxOrderLocalID;
	data["TradingSystemName"] = task_data.TradingSystemName;
	data["LoginTime"] = task_data.LoginTime;
	data["UserFlowSize"] = task_data.UserFlowSize;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CUstpFtdcRspUserLogoutField task_data = any_cast<CUstpFtdcRspUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CUstpFtdcUserPasswordUpdateField task_data = any_cast<CUstpFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CUstpFtdcInputOrderField task_data = any_cast<CUstpFtdcInputOrderField>(task.task_data);
	dict data;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CUstpFtdcOrderActionField task_data = any_cast<CUstpFtdcOrderActionField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFlowMessageCancel(Task task)
{
	PyLock lock;
	CUstpFtdcFlowMessageCancelField task_data = any_cast<CUstpFtdcFlowMessageCancelField>(task.task_data);
	dict data;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["StartSequenceNo"] = task_data.StartSequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["EndSequenceNo"] = task_data.EndSequenceNo;

	this->onRtnFlowMessageCancel(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CUstpFtdcTradeField task_data = any_cast<CUstpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["TradeID"] = task_data.TradeID;
	data["InvestorID"] = task_data.InvestorID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["Direction"] = task_data.Direction;
	data["ClientID"] = task_data.ClientID;
	data["TradePrice"] = task_data.TradePrice;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CUstpFtdcOrderField task_data = any_cast<CUstpFtdcOrderField>(task.task_data);
	dict data;
	data["VolumeRemain"] = task_data.VolumeRemain;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["SeatID"] = task_data.SeatID;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["CancelUserID"] = task_data.CancelUserID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["OrderSource"] = task_data.OrderSource;

	this->onRtnOrder(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CUstpFtdcInputOrderField task_data = any_cast<CUstpFtdcInputOrderField>(task.task_data);
	dict data;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CUstpFtdcOrderActionField task_data = any_cast<CUstpFtdcOrderActionField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CUstpFtdcInstrumentStatusField task_data = any_cast<CUstpFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortPosLimit"] = task_data.ShortPosLimit;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["OptionsType"] = task_data.OptionsType;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["BasisPrice"] = task_data.BasisPrice;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["PriceTick"] = task_data.PriceTick;
	data["ProductName"] = task_data.ProductName;
	data["Currency"] = task_data.Currency;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["UnderlyingInstrID"] = task_data.UnderlyingInstrID;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnInvestorAccountDeposit(Task task)
{
	PyLock lock;
	CUstpFtdcInvestorAccountDepositResField task_data = any_cast<CUstpFtdcInvestorAccountDepositResField>(task.task_data);
	dict data;
	data["AmountDirection"] = task_data.AmountDirection;
	data["Available"] = task_data.Available;
	data["Balance"] = task_data.Balance;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountSeqNo"] = task_data.AccountSeqNo;
	data["AccountID"] = task_data.AccountID;

	this->onRtnInvestorAccountDeposit(data);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CUstpFtdcOrderField task_data = any_cast<CUstpFtdcOrderField>(task.task_data);
	dict data;
	data["VolumeRemain"] = task_data.VolumeRemain;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["SeatID"] = task_data.SeatID;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["CancelUserID"] = task_data.CancelUserID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["OrderSource"] = task_data.OrderSource;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CUstpFtdcTradeField task_data = any_cast<CUstpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["TradeID"] = task_data.TradeID;
	data["InvestorID"] = task_data.InvestorID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["Direction"] = task_data.Direction;
	data["ClientID"] = task_data.ClientID;
	data["TradePrice"] = task_data.TradePrice;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryUserInvestor(Task task)
{
	PyLock lock;
	CUstpFtdcRspUserInvestorField task_data = any_cast<CUstpFtdcRspUserInvestorField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorID"] = task_data.InvestorID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryUserInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CUstpFtdcRspTradingCodeField task_data = any_cast<CUstpFtdcRspTradingCodeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientRight"] = task_data.ClientRight;
	data["BrokerID"] = task_data.BrokerID;
	data["IsActive"] = task_data.IsActive;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorAccount(Task task)
{
	PyLock lock;
	CUstpFtdcRspInvestorAccountField task_data = any_cast<CUstpFtdcRspInvestorAccountField>(task.task_data);
	dict data;
	data["Fee"] = task_data.Fee;
	data["Withdraw"] = task_data.Withdraw;
	data["ShortMargin"] = task_data.ShortMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
	data["PositionProfit"] = task_data.PositionProfit;
	data["FrozenFee"] = task_data.FrozenFee;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["Premium"] = task_data.Premium;
	data["Risk"] = task_data.Risk;
	data["TodayInOut"] = task_data.TodayInOut;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["BrokerID"] = task_data.BrokerID;
	data["Deposit"] = task_data.Deposit;
	data["LongFrozenMargin"] = task_data.LongFrozenMargin;
	data["Margin"] = task_data.Margin;
	data["DynamicRights"] = task_data.DynamicRights;
	data["ReleaseMargin"] = task_data.ReleaseMargin;
	data["PreBalance"] = task_data.PreBalance;
	data["InvestorID"] = task_data.InvestorID;
	data["LongMargin"] = task_data.LongMargin;
	data["CloseProfit"] = task_data.CloseProfit;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CUstpFtdcRspInstrumentField task_data = any_cast<CUstpFtdcRspInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortPosLimit"] = task_data.ShortPosLimit;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["OptionsType"] = task_data.OptionsType;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["BasisPrice"] = task_data.BasisPrice;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["PriceTick"] = task_data.PriceTick;
	data["ProductName"] = task_data.ProductName;
	data["Currency"] = task_data.Currency;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["UnderlyingInstrID"] = task_data.UnderlyingInstrID;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CUstpFtdcRspExchangeField task_data = any_cast<CUstpFtdcRspExchangeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CUstpFtdcRspInvestorPositionField task_data = any_cast<CUstpFtdcRspInvestorPositionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["FrozenClosing"] = task_data.FrozenClosing;
	data["Currency"] = task_data.Currency;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["YdPosition"] = task_data.YdPosition;
	data["LastTradeID"] = task_data.LastTradeID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["ClientID"] = task_data.ClientID;
	data["YdPositionCost"] = task_data.YdPositionCost;
	data["InvestorID"] = task_data.InvestorID;
	data["PositionCost"] = task_data.PositionCost;
	data["UsedMargin"] = task_data.UsedMargin;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenPosition"] = task_data.FrozenPosition;
	data["Position"] = task_data.Position;
	data["LastOrderLocalID"] = task_data.LastOrderLocalID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSubscribeTopic(Task task)
{
	PyLock lock;
	CUstpFtdcDisseminationField task_data = any_cast<CUstpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubscribeTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryComplianceParam(Task task)
{
	PyLock lock;
	CUstpFtdcRspComplianceParamField task_data = any_cast<CUstpFtdcRspComplianceParamField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DailyMaxOrderActionVolume"] = task_data.DailyMaxOrderActionVolume;
	data["DailyMaxOrderVolume"] = task_data.DailyMaxOrderVolume;
	data["ClientID"] = task_data.ClientID;
	data["DailyMaxOrder"] = task_data.DailyMaxOrder;
	data["InvestorID"] = task_data.InvestorID;
	data["DailyMaxErrorOrder"] = task_data.DailyMaxErrorOrder;
	data["BrokerID"] = task_data.BrokerID;
	data["DailyMaxOrderAction"] = task_data.DailyMaxOrderAction;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryComplianceParam(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTopic(Task task)
{
	PyLock lock;
	CUstpFtdcDisseminationField task_data = any_cast<CUstpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorFee(Task task)
{
	PyLock lock;
	CUstpFtdcInvestorFeeField task_data = any_cast<CUstpFtdcInvestorFeeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OTFeeRate"] = task_data.OTFeeRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OTFeeAmt"] = task_data.OTFeeAmt;
	data["OpenFeeAmt"] = task_data.OpenFeeAmt;
	data["ClientID"] = task_data.ClientID;
	data["BrokerID"] = task_data.BrokerID;
	data["OpenFeeRate"] = task_data.OpenFeeRate;
	data["OffsetFeeAmt"] = task_data.OffsetFeeAmt;
	data["OffsetFeeRate"] = task_data.OffsetFeeRate;
	data["ProductID"] = task_data.ProductID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorFee(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorMargin(Task task)
{
	PyLock lock;
	CUstpFtdcInvestorMarginField task_data = any_cast<CUstpFtdcInvestorMarginField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["LongMarginRate"] = task_data.LongMarginRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientID"] = task_data.ClientID;
	data["BrokerID"] = task_data.BrokerID;
	data["LongMarginAmt"] = task_data.LongMarginAmt;
	data["ShortMarginAmt"] = task_data.ShortMarginAmt;
	data["ShortMarginRate"] = task_data.ShortMarginRate;
	data["ProductID"] = task_data.ProductID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorMargin(data, error, task.task_id, task.task_last);
};

