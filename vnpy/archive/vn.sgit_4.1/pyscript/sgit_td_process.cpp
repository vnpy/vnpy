void TdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected();
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CSgitFtdcRspUserLoginField task_data = any_cast<CSgitFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["SHFETime"] = task_data.SHFETime;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["FFEXTime"] = task_data.FFEXTime;
	data["BrokerID"] = task_data.BrokerID;
	data["DCETime"] = task_data.DCETime;
	data["LoginTime"] = task_data.LoginTime;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CSgitFtdcUserLogoutField task_data = any_cast<CSgitFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CSgitFtdcUserPasswordUpdateField task_data = any_cast<CSgitFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CSgitFtdcInputOrderField task_data = any_cast<CSgitFtdcInputOrderField>(task.task_data);
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

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CSgitFtdcInputOrderActionField task_data = any_cast<CSgitFtdcInputOrderActionField>(task.task_data);
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

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CSgitFtdcOrderField task_data = any_cast<CSgitFtdcOrderField>(task.task_data);
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
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CSgitFtdcTradingAccountField task_data = any_cast<CSgitFtdcTradingAccountField>(task.task_data);
	dict data;
	data["Mortgage"] = task_data.Mortgage;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["Interest"] = task_data.Interest;
	data["CashIn"] = task_data.CashIn;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["PreCredit"] = task_data.PreCredit;
	data["PreMortgage"] = task_data.PreMortgage;
	data["InterestBase"] = task_data.InterestBase;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["PreMargin"] = task_data.PreMargin;
	data["SettlementID"] = task_data.SettlementID;
	data["DeliveryMargin"] = task_data.DeliveryMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["Balance"] = task_data.Balance;
	data["Reserve"] = task_data.Reserve;
	data["PreDeposit"] = task_data.PreDeposit;
	data["Credit"] = task_data.Credit;
	data["PreBalance"] = task_data.PreBalance;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["CloseProfit"] = task_data.CloseProfit;
	data["Deposit"] = task_data.Deposit;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CSgitFtdcInvestorField task_data = any_cast<CSgitFtdcInvestorField>(task.task_data);
	dict data;
	data["CommModelID"] = task_data.CommModelID;
	data["InvestorName"] = task_data.InvestorName;
	data["Mobile"] = task_data.Mobile;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["Telephone"] = task_data.Telephone;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Address"] = task_data.Address;
	data["InvestorGroupID"] = task_data.InvestorGroupID;
	data["OpenDate"] = task_data.OpenDate;
	data["IsActive"] = task_data.IsActive;
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CSgitFtdcInstrumentField task_data = any_cast<CSgitFtdcInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["PositionDateType"] = task_data.PositionDateType;
	data["LongMarginRatio"] = task_data.LongMarginRatio;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortMarginRatio"] = task_data.ShortMarginRatio;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["PriceTick"] = task_data.PriceTick;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CSgitFtdcOrderField task_data = any_cast<CSgitFtdcOrderField>(task.task_data);
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
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CSgitFtdcTradeField task_data = any_cast<CSgitFtdcTradeField>(task.task_data);
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

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CSgitFtdcInstrumentStatusField task_data = any_cast<CSgitFtdcInstrumentStatusField>(task.task_data);
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

void TdApi::processRspQryInvestorPositionDetail(Task task)
{
	PyLock lock;
	CSgitFtdcInvestorPositionDetailField task_data = any_cast<CSgitFtdcInvestorPositionDetailField>(task.task_data);
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

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPositionDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CSgitFtdcInvestorPositionField task_data = any_cast<CSgitFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["CombPosition"] = task_data.CombPosition;
	data["CashIn"] = task_data.CashIn;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["CombLongFrozen"] = task_data.CombLongFrozen;
	data["CloseAmount"] = task_data.CloseAmount;
	data["PosiDirection"] = task_data.PosiDirection;
	data["YdPosition"] = task_data.YdPosition;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
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
	data["CloseProfit"] = task_data.CloseProfit;
	data["UseMargin"] = task_data.UseMargin;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

