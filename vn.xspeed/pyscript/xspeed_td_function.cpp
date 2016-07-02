int TdApi::reqUserLogin(dict req)
{
	DFITCUserLoginField myreq = DFITCUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "passwd", myreq.passwd);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "companyID", &myreq.companyID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogin(&myreq);
	return i;
};

int TdApi::reqUserLogout(dict req)
{
	DFITCUserLogoutField myreq = DFITCUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "sessionID", &myreq.sessionID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogout(&myreq);
	return i;
};

int TdApi::reqInsertOrder(dict req)
{
	DFITCInsertOrderField myreq = DFITCInsertOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getInt(req, "openCloseType", &myreq.openCloseType);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getDouble(req, "insertPrice", &myreq.insertPrice);
	getChar(req, "orderProperty", myreq.orderProperty);
	getShort(req, "buySellType", &myreq.buySellType);
	getInt(req, "orderType", &myreq.orderType);
	getLong(req, "minMatchAmount", &myreq.minMatchAmount);
	getInt(req, "speculator", &myreq.speculator);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "reservedType2", &myreq.reservedType2);
	getInt(req, "insertType", &myreq.insertType);
	getLong(req, "orderAmount", &myreq.orderAmount);
	getDouble(req, "profitLossPrice", &myreq.profitLossPrice);
	getString(req, "customCategory", myreq.customCategory);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqInsertOrder(&myreq);
	return i;
};

int TdApi::reqCancelOrder(dict req)
{
	DFITCCancelOrderField myreq = DFITCCancelOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqCancelOrder(&myreq);
	return i;
};

int TdApi::reqQryPosition(dict req)
{
	DFITCPositionField myreq = DFITCPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryPosition(&myreq);
	return i;
};

int TdApi::reqQryCustomerCapital(dict req)
{
	DFITCCapitalField myreq = DFITCCapitalField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryCustomerCapital(&myreq);
	return i;
};

int TdApi::reqQryExchangeInstrument(dict req)
{
	DFITCExchangeInstrumentField myreq = DFITCExchangeInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "instrumentType", &myreq.instrumentType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryExchangeInstrument(&myreq);
	return i;
};

int TdApi::reqQryArbitrageInstrument(dict req)
{
	DFITCAbiInstrumentField myreq = DFITCAbiInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryArbitrageInstrument(&myreq);
	return i;
};

int TdApi::reqQryOrderInfo(dict req)
{
	DFITCOrderField myreq = DFITCOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "orderType", &myreq.orderType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "orderStatus", &myreq.orderStatus);
	getString(req, "customCategory", myreq.customCategory);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryOrderInfo(&myreq);
	return i;
};

int TdApi::reqQryMatchInfo(dict req)
{
	DFITCMatchField myreq = DFITCMatchField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getInt(req, "orderType", &myreq.orderType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "customCategory", myreq.customCategory);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryMatchInfo(&myreq);
	return i;
};

int TdApi::reqQrySpecifyInstrument(dict req)
{
	DFITCSpecificInstrumentField myreq = DFITCSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQrySpecifyInstrument(&myreq);
	return i;
};

int TdApi::reqQryPositionDetail(dict req)
{
	DFITCPositionDetailField myreq = DFITCPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryPositionDetail(&myreq);
	return i;
};

int TdApi::reqConfirmProductInfo(dict req)
{
	DFITCProductField myreq = DFITCProductField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "vendorID", myreq.vendorID);
	getString(req, "productID", myreq.productID);
	int i = this->api->ReqConfirmProductInfo(&myreq);
	return i;
};

int TdApi::reqResetPassword (dict req)
{
	DFITCResetPwdField myreq = DFITCResetPwdField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "oldpasswd", myreq.oldpasswd);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "newpasswd", myreq.newpasswd);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqResetPassword (&myreq);
	return i;
};

int TdApi::reqBillConfirm(dict req)
{
	DFITCBillConfirmField myreq = DFITCBillConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "date", myreq.date);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "confirmFlag", &myreq.confirmFlag);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqBillConfirm(&myreq);
	return i;
};

int TdApi::reqQryTradeCode(dict req)
{
	DFITCQryTradeCodeField myreq = DFITCQryTradeCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryTradeCode(&myreq);
	return i;
};

int TdApi::reqQryBill(dict req)
{
	DFITCQryBillField myreq = DFITCQryBillField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "date", myreq.date);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryBill(&myreq);
	return i;
};

int TdApi::reqTradingDay(dict req)
{
	DFITCTradingDayField myreq = DFITCTradingDayField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	int i = this->api->ReqTradingDay(&myreq);
	return i;
};

int TdApi::reqQryQuoteNotice(dict req)
{
	DFITCQryQuoteNoticeField myreq = DFITCQryQuoteNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryQuoteNotice(&myreq);
	return i;
};

int TdApi::reqQuoteInsert(dict req)
{
	DFITCQuoteInsertField myreq = DFITCQuoteInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getInt(req, "stayTime", &myreq.stayTime);
	getInt(req, "sSpeculator", &myreq.sSpeculator);
	getString(req, "quoteID", myreq.quoteID);
	getInt(req, "sOpenCloseType", &myreq.sOpenCloseType);
	getLong(req, "bOrderAmount", &myreq.bOrderAmount);
	getDouble(req, "sInsertPrice", &myreq.sInsertPrice);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "insertType", &myreq.insertType);
	getLong(req, "sOrderAmount", &myreq.sOrderAmount);
	getInt(req, "bOpenCloseType", &myreq.bOpenCloseType);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "bSpeculator", &myreq.bSpeculator);
	getString(req, "customCategory", myreq.customCategory);
	getDouble(req, "bInsertPrice", &myreq.bInsertPrice);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQuoteInsert(&myreq);
	return i;
};

int TdApi::reqQuoteCancel(dict req)
{
	DFITCCancelOrderField myreq = DFITCCancelOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQuoteCancel(&myreq);
	return i;
};

int TdApi::reqCancelAllOrder(dict req)
{
	DFITCCancelAllOrderField myreq = DFITCCancelAllOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqCancelAllOrder(&myreq);
	return i;
};

int TdApi::reqForQuote(dict req)
{
	DFITCForQuoteField myreq = DFITCForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqForQuote(&myreq);
	return i;
};

int TdApi::reqQryForQuote(dict req)
{
	DFITCQryForQuoteField myreq = DFITCQryForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryForQuote(&myreq);
	return i;
};

int TdApi::reqQryQuoteOrderInfo(dict req)
{
	DFITCQuoteOrderField myreq = DFITCQuoteOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getString(req, "exchangeID", myreq.exchangeID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "orderStatus", &myreq.orderStatus);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryQuoteOrderInfo(&myreq);
	return i;
};

int TdApi::reqQryTransferBank(dict req)
{
	DFITCQryTransferBankField myreq = DFITCQryTransferBankField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryTransferBank(&myreq);
	return i;
};

int TdApi::reqQryTransferSerial(dict req)
{
	DFITCQryTransferSerialField myreq = DFITCQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "bankAccount", myreq.bankAccount);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryTransferSerial(&myreq);
	return i;
};

int TdApi::reqFromBankToFutureByFuture(dict req)
{
	DFITCReqTransferField myreq = DFITCReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "bankAccount", myreq.bankAccount);
	getString(req, "bankPassword", myreq.bankPassword);
	getString(req, "currency", myreq.currency);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "password", myreq.password);
	getDouble(req, "tradeAmount", &myreq.tradeAmount);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFromBankToFutureByFuture(&myreq);
	return i;
};

int TdApi::reqFromFutureToBankByFuture(dict req)
{
	DFITCReqTransferField myreq = DFITCReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "bankAccount", myreq.bankAccount);
	getString(req, "bankPassword", myreq.bankPassword);
	getString(req, "currency", myreq.currency);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "password", myreq.password);
	getDouble(req, "tradeAmount", &myreq.tradeAmount);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFromFutureToBankByFuture(&myreq);
	return i;
};

int TdApi::reqQryExchangeStatus(dict req)
{
	DFITCQryExchangeStatusField myreq = DFITCQryExchangeStatusField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqQryExchangeStatus(&myreq);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req)
{
	DFITCQryDepthMarketDataField myreq = DFITCQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqQryDepthMarketData(&myreq);
	return i;
};

