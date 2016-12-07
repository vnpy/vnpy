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
	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLoginField task_data = any_cast<CQdpFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["PrivateFlowSize"] = task_data.PrivateFlowSize;
	data["UserID"] = task_data.UserID;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxOrderLocalID"] = task_data.MaxOrderLocalID;
	data["TradingSystemName"] = task_data.TradingSystemName;
	data["FrontID"] = task_data.FrontID;
	data["LoginTime"] = task_data.LoginTime;
	data["UserFlowSize"] = task_data.UserFlowSize;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLogoutField task_data = any_cast<CQdpFtdcRspUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CQdpFtdcUserPasswordUpdateField task_data = any_cast<CQdpFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CQdpFtdcInputOrderField task_data = any_cast<CQdpFtdcInputOrderField>(task.task_data);
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
	data["BusinessType"] = task_data.BusinessType;
	data["GTDDate"] = task_data.GTDDate;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CQdpFtdcOrderActionField task_data = any_cast<CQdpFtdcOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;
	data["FrontID"] = task_data.FrontID;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromBankToFutureByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromFutureToBankByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFlowMessageCancel(Task task)
{
	PyLock lock;
	CQdpFtdcFlowMessageCancelField task_data = any_cast<CQdpFtdcFlowMessageCancelField>(task.task_data);
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
	CQdpFtdcTradeField task_data = any_cast<CQdpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradeAmnt"] = task_data.TradeAmnt;
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
	data["RecNum"] = task_data.RecNum;
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CQdpFtdcOrderField task_data = any_cast<CQdpFtdcOrderField>(task.task_data);
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
	data["SessionID"] = task_data.SessionID;
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
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["BusinessType"] = task_data.BusinessType;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;
	data["OrderSource"] = task_data.OrderSource;

	this->onRtnOrder(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CQdpFtdcInputOrderField task_data = any_cast<CQdpFtdcInputOrderField>(task.task_data);
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
	data["BusinessType"] = task_data.BusinessType;
	data["GTDDate"] = task_data.GTDDate;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CQdpFtdcOrderActionField task_data = any_cast<CQdpFtdcOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;
	data["FrontID"] = task_data.FrontID;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CQdpFtdcInstrumentStatusField task_data = any_cast<CQdpFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
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
	CQdpFtdcInvestorAccountDepositResField task_data = any_cast<CQdpFtdcInvestorAccountDepositResField>(task.task_data);
	dict data;
	data["AmountDirection"] = task_data.AmountDirection;
	data["Available"] = task_data.Available;
	data["Balance"] = task_data.Balance;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountInsideSeqNo"] = task_data.AccountInsideSeqNo;
	data["AccountSeqNo"] = task_data.AccountSeqNo;
	data["AccountID"] = task_data.AccountID;

	this->onRtnInvestorAccountDeposit(data);
};

void TdApi::processRtnMessageNotify(Task task)
{
	PyLock lock;
	CQdpFtdcMessageNotifyInfoField task_data = any_cast<CQdpFtdcMessageNotifyInfoField>(task.task_data);
	dict data;
	data["WarnMsg"] = task_data.WarnMsg;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Nums"] = task_data.Nums;
	data["UserID"] = task_data.UserID;
	data["BusinessType"] = task_data.BusinessType;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	this->onRtnMessageNotify(data);
};

void TdApi::processErrRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqQueryAccountField task_data = any_cast<CQdpFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQueryBankBalanceByFuture(data, error);
};

void TdApi::processErrRtnBankToFutureByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnBankToFutureByFuture(data, error);
};

void TdApi::processErrRtnFutureToBankByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFutureToBankByFuture(data, error);
};

void TdApi::processRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcNotifyQueryAccountField task_data = any_cast<CQdpFtdcNotifyQueryAccountField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;
	data["BankFetchAmount"] = task_data.BankFetchAmount;

	this->onRtnQueryBankBalanceByFuture(data);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcRspTransferField task_data = any_cast<CQdpFtdcRspTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["ErrorMsg"] = task_data.ErrorMsg;
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
	CQdpFtdcRspTransferField task_data = any_cast<CQdpFtdcRspTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromFutureToBankByFuture(data);
};

void TdApi::processRtnSGEDeferRate(Task task)
{
	PyLock lock;
	CQdpFtdcSGEDeferRateField task_data = any_cast<CQdpFtdcSGEDeferRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DeferRate"] = task_data.DeferRate;
	data["Direction"] = task_data.Direction;
	data["TradeDate"] = task_data.TradeDate;

	this->onRtnSGEDeferRate(data);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CQdpFtdcOrderField task_data = any_cast<CQdpFtdcOrderField>(task.task_data);
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
	data["SessionID"] = task_data.SessionID;
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
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["BusinessType"] = task_data.BusinessType;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;
	data["OrderSource"] = task_data.OrderSource;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CQdpFtdcTradeField task_data = any_cast<CQdpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradeAmnt"] = task_data.TradeAmnt;
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
	data["RecNum"] = task_data.RecNum;
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryUserInvestor(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserInvestorField task_data = any_cast<CQdpFtdcRspUserInvestorField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorID"] = task_data.InvestorID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryUserInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorAccount(Task task)
{
	PyLock lock;
	CQdpFtdcRspInvestorAccountField task_data = any_cast<CQdpFtdcRspInvestorAccountField>(task.task_data);
	dict data;
	data["Fee"] = task_data.Fee;
	data["Withdraw"] = task_data.Withdraw;
	data["Mortgage"] = task_data.Mortgage;
	data["ShortMargin"] = task_data.ShortMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
	data["PositionProfit"] = task_data.PositionProfit;
	data["FrozenFee"] = task_data.FrozenFee;
	data["OtherFee"] = task_data.OtherFee;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["Premium"] = task_data.Premium;
	data["Risk"] = task_data.Risk;
	data["Currency"] = task_data.Currency;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["PreAvailable"] = task_data.PreAvailable;
	data["BrokerID"] = task_data.BrokerID;
	data["Deposit"] = task_data.Deposit;
	data["LongFrozenMargin"] = task_data.LongFrozenMargin;
	data["Balance"] = task_data.Balance;
	data["Margin"] = task_data.Margin;
	data["DynamicRights"] = task_data.DynamicRights;
	data["PreBalance"] = task_data.PreBalance;
	data["InvestorID"] = task_data.InvestorID;
	data["LongMargin"] = task_data.LongMargin;
	data["CloseProfit"] = task_data.CloseProfit;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CQdpFtdcRspInstrumentField task_data = any_cast<CQdpFtdcRspInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
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

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CQdpFtdcRspExchangeField task_data = any_cast<CQdpFtdcRspExchangeField>(task.task_data);
	dict data;
	data["TradingDay"] = task_data.TradingDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CQdpFtdcRspInvestorPositionField task_data = any_cast<CQdpFtdcRspInvestorPositionField>(task.task_data);
	dict data;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Direction"] = task_data.Direction;
	data["ParticipantID"] = task_data.ParticipantID;
	data["FrozenClosing"] = task_data.FrozenClosing;
	data["InvestorID"] = task_data.InvestorID;
	data["LastTradeID"] = task_data.LastTradeID;
	data["YdPosition"] = task_data.YdPosition;
	data["ClientID"] = task_data.ClientID;
	data["FrozenPosition"] = task_data.FrozenPosition;
	data["LastOrderLocalID"] = task_data.LastOrderLocalID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["TodayPosition"] = task_data.TodayPosition;
	data["PositionCost"] = task_data.PositionCost;
	data["UsedMargin"] = task_data.UsedMargin;
	data["BrokerID"] = task_data.BrokerID;
	data["Position"] = task_data.Position;
	data["FrozenTodayClosing"] = task_data.FrozenTodayClosing;
	data["YdPositionCost"] = task_data.YdPositionCost;
	data["Currency"] = task_data.Currency;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSubscribeTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubscribeTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorFee(Task task)
{
	PyLock lock;
	CQdpFtdcInvestorFeeField task_data = any_cast<CQdpFtdcInvestorFeeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OTFeeRate"] = task_data.OTFeeRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OTFeeAmt"] = task_data.OTFeeAmt;
	data["OpenFeeAmt"] = task_data.OpenFeeAmt;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["OpenFeeRate"] = task_data.OpenFeeRate;
	data["OffsetFeeRate"] = task_data.OffsetFeeRate;
	data["OffsetFeeAmt"] = task_data.OffsetFeeAmt;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorFee(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorMargin(Task task)
{
	PyLock lock;
	CQdpFtdcInvestorMarginField task_data = any_cast<CQdpFtdcInvestorMarginField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["LongMarginRate"] = task_data.LongMarginRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["LongMarginAmt"] = task_data.LongMarginAmt;
	data["ShortMarginAmt"] = task_data.ShortMarginAmt;
	data["ShortMarginRate"] = task_data.ShortMarginRate;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorMargin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeDiffTime(Task task)
{
	PyLock lock;
	CQdpFtdcRspExchangeDiffTimeField task_data = any_cast<CQdpFtdcRspExchangeDiffTimeField>(task.task_data);
	dict data;
	data["ExchangeTime"] = task_data.ExchangeTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DiffSnd"] = task_data.DiffSnd;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeDiffTime(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryContractBank(Task task)
{
	PyLock lock;
	CQdpFtdcContractBankField task_data = any_cast<CQdpFtdcContractBankField>(task.task_data);
	dict data;
	data["Currency"] = task_data.Currency;
	data["BankName"] = task_data.BankName;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["BankBrchID"] = task_data.BankBrchID;
	data["BankID"] = task_data.BankID;
	data["AccountID"] = task_data.AccountID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryContractBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryBankAccountMoneyByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqQueryAccountField task_data = any_cast<CQdpFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
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
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryBankAccountMoneyByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	CQdpFtdcTransferSerialField task_data = any_cast<CQdpFtdcTransferSerialField>(task.task_data);
	dict data;
	data["BankNewAccount"] = task_data.BankNewAccount;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["BankBrchID"] = task_data.BankBrchID;
	data["OperatorCode"] = task_data.OperatorCode;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InvestorID"] = task_data.InvestorID;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["TradingTime"] = task_data.TradingTime;
	data["FutureAccType"] = task_data.FutureAccType;
	data["ErrorID"] = task_data.ErrorID;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["FutureSerial"] = task_data.FutureSerial;
	data["Currency"] = task_data.Currency;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AvailabilityFlag"] = task_data.AvailabilityFlag;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTransferSerial(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySGEDeferRate(Task task)
{
	PyLock lock;
	CQdpFtdcSGEDeferRateField task_data = any_cast<CQdpFtdcSGEDeferRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DeferRate"] = task_data.DeferRate;
	data["Direction"] = task_data.Direction;
	data["TradeDate"] = task_data.TradeDate;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySGEDeferRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcMarketDataField task_data = any_cast<CQdpFtdcMarketDataField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["LastPrice"] = task_data.LastPrice;
	data["HighestPrice"] = task_data.HighestPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["UpdateTime"] = task_data.UpdateTime;
	data["OpenPrice"] = task_data.OpenPrice;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["Volume"] = task_data.Volume;
	data["TradingDay"] = task_data.TradingDay;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["LowestPrice"] = task_data.LowestPrice;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["OpenInterest"] = task_data.OpenInterest;
	data["Turnover"] = task_data.Turnover;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryMarketData(data, error, task.task_id, task.task_last);
};

