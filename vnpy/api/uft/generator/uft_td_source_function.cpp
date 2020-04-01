int TdApi::reqAuthenticate(const dict &req, int reqid)
{
	CHSReqAuthenticateField myreq = CHSReqAuthenticateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountID", myreq.AccountID);
	getString(req, "Password", myreq.Password);
	getString(req, "AppID", myreq.AppID);
	getString(req, "AuthCode", myreq.AuthCode);
	int i = this->api->ReqAuthenticate(&myreq, reqid);
	return i;
};

int TdApi::reqUserLogin(const dict &req, int reqid)
{
	CHSReqUserLoginField myreq = CHSReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountID", myreq.AccountID);
	getString(req, "Password", myreq.Password);
	getChar(req, "UserApplicationType", &myreq.UserApplicationType);
	getString(req, "UserApplicationInfo", myreq.UserApplicationInfo);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int TdApi::reqUserPasswordUpdate(const dict &req, int reqid)
{
	CHSReqUserPasswordUpdateField myreq = CHSReqUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "PasswordType", &myreq.PasswordType);
	getString(req, "Password", myreq.Password);
	getString(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqUserPasswordUpdate(&myreq, reqid);
	return i;
};

int TdApi::reqOrderInsert(const dict &req, int reqid)
{
	CHSReqOrderInsertField myreq = CHSReqOrderInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "OrderRef", myreq.OrderRef);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeType", &myreq.HedgeType);
	getDouble(req, "OrderPrice", &myreq.OrderPrice);
	getDouble(req, "OrderVolume", &myreq.OrderVolume);
	getString(req, "OrderCommand", myreq.OrderCommand);
	getDouble(req, "MinVolume", &myreq.MinVolume);
	getDouble(req, "SpringPrice", &myreq.SpringPrice);
	getChar(req, "SwapOrderFlag", &myreq.SwapOrderFlag);
	int i = this->api->ReqOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqOrderAction(const dict &req, int reqid)
{
	CHSReqOrderActionField myreq = CHSReqOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "OrderRef", myreq.OrderRef);
	getString(req, "OrderActionRef", myreq.OrderActionRef);
	int i = this->api->ReqOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqExerciseOrderInsert(const dict &req, int reqid)
{
	CHSReqExerciseOrderInsertField myreq = CHSReqExerciseOrderInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExerciseRef", myreq.ExerciseRef);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getDouble(req, "OrderVolume", &myreq.OrderVolume);
	getChar(req, "ExerciseType", &myreq.ExerciseType);
	getChar(req, "HedgeType", &myreq.HedgeType);
	int i = this->api->ReqExerciseOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqExerciseOrderAction(const dict &req, int reqid)
{
	CHSReqExerciseOrderActionField myreq = CHSReqExerciseOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ExerciseOrderSysID", myreq.ExerciseOrderSysID);
	getString(req, "ExerciseRef", myreq.ExerciseRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "ExecOrderActionRef", myreq.ExecOrderActionRef);
	int i = this->api->ReqExerciseOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqLockInsert(const dict &req, int reqid)
{
	CHSReqLockInsertField myreq = CHSReqLockInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
	getChar(req, "LockType", &myreq.LockType);
	getDouble(req, "OrderVolume", &myreq.OrderVolume);
	int i = this->api->ReqLockInsert(&myreq, reqid);
	return i;
};

int TdApi::reqForQuoteInsert(const dict &req, int reqid)
{
	CHSReqForQuoteInsertField myreq = CHSReqForQuoteInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqForQuoteInsert(&myreq, reqid);
	return i;
};

int TdApi::reqCombActionInsert(const dict &req, int reqid)
{
	CHSReqCombActionInsertField myreq = CHSReqCombActionInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "CombStrategyID", myreq.CombStrategyID);
	getString(req, "CombPositionID", myreq.CombPositionID);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getDouble(req, "OrderVolume", &myreq.OrderVolume);
	getChar(req, "HedgeType", &myreq.HedgeType);
	getChar(req, "Direction", &myreq.Direction);
	int i = this->api->ReqCombActionInsert(&myreq, reqid);
	return i;
};

int TdApi::reqQueryMaxOrderVolume(const dict &req, int reqid)
{
	CHSReqQueryMaxOrderVolumeField myreq = CHSReqQueryMaxOrderVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "OrderCommand", myreq.OrderCommand);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeType", &myreq.HedgeType);
	getDouble(req, "OrderPrice", &myreq.OrderPrice);
	int i = this->api->ReqQueryMaxOrderVolume(&myreq, reqid);
	return i;
};

int TdApi::reqQueryLockVolume(const dict &req, int reqid)
{
	CHSReqQueryLockVolumeField myreq = CHSReqQueryLockVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
	getChar(req, "LockType", &myreq.LockType);
	int i = this->api->ReqQueryLockVolume(&myreq, reqid);
	return i;
};

int TdApi::reqQueryExerciseVolume(const dict &req, int reqid)
{
	CHSReqQueryExerciseVolumeField myreq = CHSReqQueryExerciseVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQueryExerciseVolume(&myreq, reqid);
	return i;
};

int TdApi::reqQryPosition(const dict &req, int reqid)
{
	CHSReqQryPositionField myreq = CHSReqQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryTradingAccount(const dict &req, int reqid)
{
	CHSReqQryTradingAccountField myreq = CHSReqQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->ReqQryTradingAccount(&myreq, reqid);
	return i;
};

int TdApi::reqQryOrder(const dict &req, int reqid)
{
	CHSReqQryOrderField myreq = CHSReqQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqQryOrder(&myreq, reqid);
	return i;
};

int TdApi::reqQryTrade(const dict &req, int reqid)
{
	CHSReqQryTradeField myreq = CHSReqQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryTrade(&myreq, reqid);
	return i;
};

int TdApi::reqQryExercise(const dict &req, int reqid)
{
	CHSReqQryExerciseField myreq = CHSReqQryExerciseField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ExerciseOrderSysID", myreq.ExerciseOrderSysID);
	int i = this->api->ReqQryExercise(&myreq, reqid);
	return i;
};

int TdApi::reqQryLock(const dict &req, int reqid)
{
	CHSReqQryLockField myreq = CHSReqQryLockField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
	getString(req, "LockOrderSysID", myreq.LockOrderSysID);
	int i = this->api->ReqQryLock(&myreq, reqid);
	return i;
};

int TdApi::reqQryCombAction(const dict &req, int reqid)
{
	CHSReqQryCombActionField myreq = CHSReqQryCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "CombOrderSysID", myreq.CombOrderSysID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryCombAction(&myreq, reqid);
	return i;
};

int TdApi::reqQryPositionCombineDetail(const dict &req, int reqid)
{
	CHSReqQryPositionCombineDetailField myreq = CHSReqQryPositionCombineDetailField();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->ReqQryPositionCombineDetail(&myreq, reqid);
	return i;
};

int TdApi::reqQryInstrument(const dict &req, int reqid)
{
	CHSReqQryInstrumentField myreq = CHSReqQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryInstrument(&myreq, reqid);
	return i;
};

int TdApi::reqQryCoveredShort(const dict &req, int reqid)
{
	CHSReqQryCoveredShortField myreq = CHSReqQryCoveredShortField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryCoveredShort(&myreq, reqid);
	return i;
};

int TdApi::reqQryExerciseAssign(const dict &req, int reqid)
{
	CHSReqQryExerciseAssignField myreq = CHSReqQryExerciseAssignField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "PositionType", &myreq.PositionType);
	int i = this->api->ReqQryExerciseAssign(&myreq, reqid);
	return i;
};

int TdApi::reqTransfer(const dict &req, int reqid)
{
	CHSReqTransferField myreq = CHSReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BankID", myreq.BankID);
	getChar(req, "TransferType", &myreq.TransferType);
	getDouble(req, "OccurBalance", &myreq.OccurBalance);
	getString(req, "FundPassword", myreq.FundPassword);
	getString(req, "BankPassword", myreq.BankPassword);
	getChar(req, "CurrencyID", &myreq.CurrencyID);
	getString(req, "TransferOccasion", myreq.TransferOccasion);
	int i = this->api->ReqTransfer(&myreq, reqid);
	return i;
};

int TdApi::reqQryTransfer(const dict &req, int reqid)
{
	CHSReqQryTransferField myreq = CHSReqQryTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BankID", myreq.BankID);
	getInt(req, "TransferSerialID", &myreq.TransferSerialID);
	int i = this->api->ReqQryTransfer(&myreq, reqid);
	return i;
};

int TdApi::reqQueryBankBalance(const dict &req, int reqid)
{
	CHSReqQueryBankBalanceField myreq = CHSReqQueryBankBalanceField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BankID", myreq.BankID);
	getString(req, "FundPassword", myreq.FundPassword);
	getString(req, "BankPassword", myreq.BankPassword);
	getChar(req, "CurrencyID", &myreq.CurrencyID);
	int i = this->api->ReqQueryBankBalance(&myreq, reqid);
	return i;
};

int TdApi::reqQueryBankAccount(const dict &req, int reqid)
{
	CHSReqQueryBankAccountField myreq = CHSReqQueryBankAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BankID", myreq.BankID);
	getChar(req, "CurrencyID", &myreq.CurrencyID);
	int i = this->api->ReqQueryBankAccount(&myreq, reqid);
	return i;
};

int TdApi::reqQueryBillContent(const dict &req, int reqid)
{
	CHSReqQueryBillContentField myreq = CHSReqQueryBillContentField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "BeginDate", &myreq.BeginDate);
	getInt(req, "EndDate", &myreq.EndDate);
	int i = this->api->ReqQueryBillContent(&myreq, reqid);
	return i;
};

int TdApi::reqBillConfirm(const dict &req, int reqid)
{
	CHSReqBillConfirmField myreq = CHSReqBillConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->ReqBillConfirm(&myreq, reqid);
	return i;
};

int TdApi::reqQryMargin(const dict &req, int reqid)
{
	CHSReqQryMarginField myreq = CHSReqQryMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
	getChar(req, "HedgeType", &myreq.HedgeType);
	int i = this->api->ReqQryMargin(&myreq, reqid);
	return i;
};

int TdApi::reqQryCommission(const dict &req, int reqid)
{
	CHSReqQryCommissionField myreq = CHSReqQryCommissionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ProductType", &myreq.ProductType);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "UnderlyingInstrID", myreq.UnderlyingInstrID);
	int i = this->api->ReqQryCommission(&myreq, reqid);
	return i;
};

int TdApi::reqQryExchangeRate(const dict &req, int reqid)
{
	CHSReqQryExchangeRateField myreq = CHSReqQryExchangeRateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "FromCurrencyID", &myreq.FromCurrencyID);
	getChar(req, "ToCurrencyID", &myreq.ToCurrencyID);
	int i = this->api->ReqQryExchangeRate(&myreq, reqid);
	return i;
};

int TdApi::reqQryPositionDetail(const dict &req, int reqid)
{
	CHSReqQryPositionDetailField myreq = CHSReqQryPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryPositionDetail(&myreq, reqid);
	return i;
};

int TdApi::reqQrySysConfig(const dict &req, int reqid)
{
	CHSReqQrySysConfigField myreq = CHSReqQrySysConfigField();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->ReqQrySysConfig(&myreq, reqid);
	return i;
};

int TdApi::reqQryDepthMarketData(const dict &req, int reqid)
{
	CHSReqQryDepthMarketDataField myreq = CHSReqQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryDepthMarketData(&myreq, reqid);
	return i;
};

