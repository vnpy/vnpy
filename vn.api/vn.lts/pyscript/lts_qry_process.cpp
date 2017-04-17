void QryApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void QryApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void QryApi::processHeartBeatWarning(Task task)
{
	PyLock lock;
	this->onHeartBeatWarning(task.task_id);
};

void QryApi::processRspError(Task task)
{
	PyLock lock;
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void QryApi::processRspUserLogin(Task task)
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

void QryApi::processRspUserLogout(Task task)
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

void QryApi::processRspFetchAuthRandCode(Task task)
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

void QryApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CSecurityFtdcExchangeField task_data = any_cast<CSecurityFtdcExchangeField>(task.task_data);
	dict data;
	data["ExchangeProperty"] = task_data.ExchangeProperty;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcInstrumentField task_data = any_cast<CSecurityFtdcInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["UnitMargin"] = task_data.UnitMargin;
	data["OrderCanBeWithdraw"] = task_data.OrderCanBeWithdraw;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["MinSellVolume"] = task_data.MinSellVolume;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ExecPrice"] = task_data.ExecPrice;
	data["RightModelID"] = task_data.RightModelID;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["OptionsMarginParam2"] = task_data.OptionsMarginParam2;
	data["OptionsMarginParam1"] = task_data.OptionsMarginParam1;
	data["PosTradeType"] = task_data.PosTradeType;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["InstrumentType"] = task_data.InstrumentType;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["MinBuyVolume"] = task_data.MinBuyVolume;
	data["PriceTick"] = task_data.PriceTick;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["MarketID"] = task_data.MarketID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CSecurityFtdcInvestorField task_data = any_cast<CSecurityFtdcInvestorField>(task.task_data);
	dict data;
	data["SZBranchID"] = task_data.SZBranchID;
	data["InvestorName"] = task_data.InvestorName;
	data["SHBranchID"] = task_data.SHBranchID;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorGroupID"] = task_data.InvestorGroupID;
	data["SettleSystemType"] = task_data.SettleSystemType;
	data["InvestorLevel"] = task_data.InvestorLevel;
	data["IsActive"] = task_data.IsActive;
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CSecurityFtdcTradingCodeField task_data = any_cast<CSecurityFtdcTradingCodeField>(task.task_data);
	dict data;
	data["PBU"] = task_data.PBU;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientType"] = task_data.ClientType;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["IsActive"] = task_data.IsActive;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CSecurityFtdcTradingAccountField task_data = any_cast<CSecurityFtdcTradingAccountField>(task.task_data);
	dict data;
	data["MarginTradeAmount"] = task_data.MarginTradeAmount;
	data["FrozenTransferFee"] = task_data.FrozenTransferFee;
	data["SSEOptionsBuyFrozenAmount"] = task_data.SSEOptionsBuyFrozenAmount;
	data["Mortgage"] = task_data.Mortgage;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["TransferFee"] = task_data.TransferFee;
	data["Commission"] = task_data.Commission;
	data["Interest"] = task_data.Interest;
	data["ShortSellProfit"] = task_data.ShortSellProfit;
	data["FrozenExecCash"] = task_data.FrozenExecCash;
	data["CashIn"] = task_data.CashIn;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["PreCredit"] = task_data.PreCredit;
	data["PreMortgage"] = task_data.PreMortgage;
	data["CreditRatio"] = task_data.CreditRatio;
	data["CreditAmount"] = task_data.CreditAmount;
	data["InterestBase"] = task_data.InterestBase;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["ConversionAmount"] = task_data.ConversionAmount;
	data["SSStockValue"] = task_data.SSStockValue;
	data["ShortSellAmount"] = task_data.ShortSellAmount;
	data["PreMargin"] = task_data.PreMargin;
	data["CurrencyCode"] = task_data.CurrencyCode;
	data["DeliveryMargin"] = task_data.DeliveryMargin;
	data["BondRepurchaseAmount"] = task_data.BondRepurchaseAmount;
	data["SettleMargin"] = task_data.SettleMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["ReverseRepurchaseAmount"] = task_data.ReverseRepurchaseAmount;
	data["StampTax"] = task_data.StampTax;
	data["SSEOptionsBuyAmount"] = task_data.SSEOptionsBuyAmount;
	data["Balance"] = task_data.Balance;
	data["FrozenStampTax"] = task_data.FrozenStampTax;
	data["Reserve"] = task_data.Reserve;
	data["PreDeposit"] = task_data.PreDeposit;
	data["MarginTradeProfit"] = task_data.MarginTradeProfit;
	data["Credit"] = task_data.Credit;
	data["PreBalance"] = task_data.PreBalance;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["AccountType"] = task_data.AccountType;
	data["StockValue"] = task_data.StockValue;
	data["Deposit"] = task_data.Deposit;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryBondInterest(Task task)
{
	PyLock lock;
	CSecurityFtdcBondInterestField task_data = any_cast<CSecurityFtdcBondInterestField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradingDay"] = task_data.TradingDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Interest"] = task_data.Interest;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBondInterest(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryMarketRationInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcMarketRationInfoField task_data = any_cast<CSecurityFtdcMarketRationInfoField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BrokerID"] = task_data.BrokerID;
	data["RationVolume"] = task_data.RationVolume;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryMarketRationInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInstrumentCommissionRate(Task task)
{
	PyLock lock;
	CSecurityFtdcInstrumentCommissionRateField task_data = any_cast<CSecurityFtdcInstrumentCommissionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinTransferFee"] = task_data.MinTransferFee;
	data["TradeFeeByMoney"] = task_data.TradeFeeByMoney;
	data["Direction"] = task_data.Direction;
	data["MinTradeFee"] = task_data.MinTradeFee;
	data["StampTaxRateByMoney"] = task_data.StampTaxRateByMoney;
	data["InvestorID"] = task_data.InvestorID;
	data["MarginByMoney"] = task_data.MarginByMoney;
	data["StampTaxRateByVolume"] = task_data.StampTaxRateByVolume;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["TransferFeeRateByVolume"] = task_data.TransferFeeRateByVolume;
	data["TransferFeeRateByMoney"] = task_data.TransferFeeRateByMoney;
	data["TradeFeeByVolume"] = task_data.TradeFeeByVolume;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentCommissionRate(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryETFInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcETFInstrumentField task_data = any_cast<CSecurityFtdcETFInstrumentField>(task.task_data);
	dict data;
	data["ETFInstrumentID"] = task_data.ETFInstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ETFPurRedInstrumentID"] = task_data.ETFPurRedInstrumentID;
	data["ETFNetValue"] = task_data.ETFNetValue;
	data["FundClass"] = task_data.FundClass;
	data["EstimateCashComponent"] = task_data.EstimateCashComponent;
	data["CreationRedemptionUnit"] = task_data.CreationRedemptionUnit;
	data["Maxcashratio"] = task_data.Maxcashratio;
	data["Creationredemption"] = task_data.Creationredemption;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryETFInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryETFBasket(Task task)
{
	PyLock lock;
	CSecurityFtdcETFBasketField task_data = any_cast<CSecurityFtdcETFBasketField>(task.task_data);
	dict data;
	data["ETFInstrumentID"] = task_data.ETFInstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Premium"] = task_data.Premium;
	data["StockInstrumentName"] = task_data.StockInstrumentName;
	data["CurrenceReplaceStatus"] = task_data.CurrenceReplaceStatus;
	data["Volume"] = task_data.Volume;
	data["Amount"] = task_data.Amount;
	data["StockInstrumentID"] = task_data.StockInstrumentID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryETFBasket(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryOFInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcOFInstrumentField task_data = any_cast<CSecurityFtdcOFInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["NetPrice"] = task_data.NetPrice;
	data["FundClass"] = task_data.FundClass;
	data["Creationredemption"] = task_data.Creationredemption;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOFInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQrySFInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcSFInstrumentField task_data = any_cast<CSecurityFtdcSFInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["NetPrice"] = task_data.NetPrice;
	data["MinMergeVolume"] = task_data.MinMergeVolume;
	data["SFInstrumentID"] = task_data.SFInstrumentID;
	data["MinSplitVolume"] = task_data.MinSplitVolume;
	data["VolumeRatio"] = task_data.VolumeRatio;
	data["SplitMergeStatus"] = task_data.SplitMergeStatus;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySFInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInstrumentUnitMargin(Task task)
{
	PyLock lock;
	CSecurityFtdcInstrumentUnitMarginField task_data = any_cast<CSecurityFtdcInstrumentUnitMarginField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BrokerID"] = task_data.BrokerID;
	data["UnitMargin"] = task_data.UnitMargin;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentUnitMargin(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryPreDelivInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcPreDelivInfoField task_data = any_cast<CSecurityFtdcPreDelivInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DelivVolume"] = task_data.DelivVolume;
	data["DelivAmount"] = task_data.DelivAmount;
	data["DelivType"] = task_data.DelivType;
	data["Direction"] = task_data.Direction;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ExecVolume"] = task_data.ExecVolume;
	data["UnderlyingInstrumentID"] = task_data.UnderlyingInstrumentID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryPreDelivInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryCreditStockAssignInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcCreditStockAssignInfoField task_data = any_cast<CSecurityFtdcCreditStockAssignInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenVolume"] = task_data.FrozenVolume;
	data["InvestorID"] = task_data.InvestorID;
	data["LeftVolume"] = task_data.LeftVolume;
	data["BrokerID"] = task_data.BrokerID;
	data["YDVolume"] = task_data.YDVolume;
	data["LimitVolume"] = task_data.LimitVolume;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCreditStockAssignInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryCreditCashAssignInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcCreditCashAssignInfoField task_data = any_cast<CSecurityFtdcCreditCashAssignInfoField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["YDAmount"] = task_data.YDAmount;
	data["BrokerID"] = task_data.BrokerID;
	data["LimitAmount"] = task_data.LimitAmount;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCreditCashAssignInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryConversionRate(Task task)
{
	PyLock lock;
	CSecurityFtdcConversionRateField task_data = any_cast<CSecurityFtdcConversionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ConversionRate"] = task_data.ConversionRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["IsTradingForShort"] = task_data.IsTradingForShort;
	data["IsTradingForMargin"] = task_data.IsTradingForMargin;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryConversionRate(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryHisCreditDebtInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcHisCreditDebtInfoField task_data = any_cast<CSecurityFtdcHisCreditDebtInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Direction"] = task_data.Direction;
	data["OpenPrice"] = task_data.OpenPrice;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["OpenDate"] = task_data.OpenDate;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryHisCreditDebtInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryMarketDataStaticInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcMarketDataStaticInfoField task_data = any_cast<CSecurityFtdcMarketDataStaticInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["PreIOPV"] = task_data.PreIOPV;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["IsNotTrade"] = task_data.IsNotTrade;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryMarketDataStaticInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryExpireRepurchInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcExpireRepurchInfoField task_data = any_cast<CSecurityFtdcExpireRepurchInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExpireType"] = task_data.ExpireType;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["Interest"] = task_data.Interest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExpireRepurchInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryBondPledgeRate(Task task)
{
	PyLock lock;
	CSecurityFtdcBondPledgeRateField task_data = any_cast<CSecurityFtdcBondPledgeRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Ratio"] = task_data.Ratio;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBondPledgeRate(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryPledgeBond(Task task)
{
	PyLock lock;
	CSecurityFtdcPledgeBondField task_data = any_cast<CSecurityFtdcPledgeBondField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["PledgeID"] = task_data.PledgeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryPledgeBond(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryOrder(Task task)
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryTrade(Task task)
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CSecurityFtdcInvestorPositionField task_data = any_cast<CSecurityFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["LockPosition"] = task_data.LockPosition;
	data["MarginTradeAmount"] = task_data.MarginTradeAmount;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["ShortSellAmount"] = task_data.ShortSellAmount;
	data["TodaySSPosition"] = task_data.TodaySSPosition;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TransferFee"] = task_data.TransferFee;
	data["Commission"] = task_data.Commission;
	data["ShortSellVolume"] = task_data.ShortSellVolume;
	data["CoverFrozenPosition"] = task_data.CoverFrozenPosition;
	data["TodayPurRedVolume"] = task_data.TodayPurRedVolume;
	data["PurRedShortFrozen"] = task_data.PurRedShortFrozen;
	data["CashIn"] = task_data.CashIn;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["ShortSellFrozenAmount"] = task_data.ShortSellFrozenAmount;
	data["CloseAmount"] = task_data.CloseAmount;
	data["PosiDirection"] = task_data.PosiDirection;
	data["LockFrozenPosition"] = task_data.LockFrozenPosition;
	data["RepurchasePosition"] = task_data.RepurchasePosition;
	data["MarginTradeVolume"] = task_data.MarginTradeVolume;
	data["YdPosition"] = task_data.YdPosition;
	data["MarginTradeFrozenVolume"] = task_data.MarginTradeFrozenVolume;
	data["ConversionRate"] = task_data.ConversionRate;
	data["YDCoverPosition"] = task_data.YDCoverPosition;
	data["ShortSellFrozenVolume"] = task_data.ShortSellFrozenVolume;
	data["OpenVolume"] = task_data.OpenVolume;
	data["TodayMTPosition"] = task_data.TodayMTPosition;
	data["CoverPosition"] = task_data.CoverPosition;
	data["CloseVolume"] = task_data.CloseVolume;
	data["AccountID"] = task_data.AccountID;
	data["ConversionAmount"] = task_data.ConversionAmount;
	data["ShortSellConversionProfit"] = task_data.ShortSellConversionProfit;
	data["InstrumentID"] = task_data.InstrumentID;
	data["PositionDate"] = task_data.PositionDate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MarginTradeFrozenAmount"] = task_data.MarginTradeFrozenAmount;
	data["ShortFrozen"] = task_data.ShortFrozen;
	data["LongFrozen"] = task_data.LongFrozen;
	data["TodayPosition"] = task_data.TodayPosition;
	data["TradingDay"] = task_data.TradingDay;
	data["PositionCost"] = task_data.PositionCost;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["OpenAmount"] = task_data.OpenAmount;
	data["OpenCost"] = task_data.OpenCost;
	data["StampTax"] = task_data.StampTax;
	data["Position"] = task_data.Position;
	data["ExecFrozenPosition"] = task_data.ExecFrozenPosition;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["PledgeInPosition"] = task_data.PledgeInPosition;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LongFrozenAmount"] = task_data.LongFrozenAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["UnlockFrozenPosition"] = task_data.UnlockFrozenPosition;
	data["YdOpenCost"] = task_data.YdOpenCost;
	data["MarginTradeConversionProfit"] = task_data.MarginTradeConversionProfit;
	data["SSStockValue"] = task_data.SSStockValue;
	data["StockValue"] = task_data.StockValue;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryFundTransferSerial(Task task)
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryFundTransferSerial(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryFundInterTransferSerial(Task task)
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryFundInterTransferSerial(data, error, task.task_id, task.task_last);
};

