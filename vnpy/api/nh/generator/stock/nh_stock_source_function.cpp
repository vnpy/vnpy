int StockTdApi::reqSubscribeTopic(const dict &req, int reqid)
{
	CStockFtdcDisseminationField myreq = CStockFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	int i = this->api->ReqSubscribeTopic(&myreq, reqid);
	return i;
};

int StockTdApi::reqUserLogin(const dict &req, int reqid)
{
	CStockFtdcReqUserLoginField myreq = CStockFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "UserID", myreq.UserID);
	getString(req, "Password", myreq.Password);
	getString(req, "UserProductInfo", myreq.UserProductInfo);
	getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int StockTdApi::reqUserLogout(const dict &req, int reqid)
{
	CStockFtdcReqUserLogoutField myreq = CStockFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

int StockTdApi::reqUserPasswordUpdate(const dict &req, int reqid)
{
	CStockFtdcUserPasswordUpdateField myreq = CStockFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqUserPasswordUpdate(&myreq, reqid);
	return i;
};

int StockTdApi::reqStockInsert(const dict &req, int reqid)
{
	CStockFtdcStockInsertReqField myreq = CStockFtdcStockInsertReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getChar(req, "OrdType", &myreq.OrdType);
	getDouble(req, "Price", &myreq.Price);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getChar(req, "Side", &myreq.Side);
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getChar(req, "TimeInForce", &myreq.TimeInForce);
	int i = this->api->ReqStockInsert(&myreq, reqid);
	return i;
};

int StockTdApi::reqStockCancel(const dict &req, int reqid)
{
	CStockFtdcStockCancelReqField myreq = CStockFtdcStockCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqStockCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqStockLock(const dict &req, int reqid)
{
	CStockFtdcStockLockReqField myreq = CStockFtdcStockLockReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getChar(req, "Locked", &myreq.Locked);
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqStockLock(&myreq, reqid);
	return i;
};

int StockTdApi::reqOptionsInsert(const dict &req, int reqid)
{
	CStockFtdcOptionsInsertReqField myreq = CStockFtdcOptionsInsertReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getDouble(req, "Price", &myreq.Price);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getChar(req, "Side", &myreq.Side);
	getChar(req, "PositionEffect", &myreq.PositionEffect);
	getChar(req, "OrdType", &myreq.OrdType);
	getChar(req, "TimeInForce", &myreq.TimeInForce);
	getChar(req, "CoveredOrUncovered", &myreq.CoveredOrUncovered);
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqOptionsInsert(&myreq, reqid);
	return i;
};

int StockTdApi::reqOptionsCancel(const dict &req, int reqid)
{
	CStockFtdcOptionsCancelReqField myreq = CStockFtdcOptionsCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqOptionsCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqQuoteInsert(const dict &req, int reqid)
{
	CStockFtdcQuoteInsertReqField myreq = CStockFtdcQuoteInsertReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "QuoteReqID", myreq.QuoteReqID);
	getDouble(req, "BidPx", &myreq.BidPx);
	getDouble(req, "AskPx", &myreq.AskPx);
	getInt(req, "BidSize", &myreq.BidSize);
	getInt(req, "AskSize", &myreq.AskSize);
	getChar(req, "BidPositionEffect", &myreq.BidPositionEffect);
	getChar(req, "AskPositionEffect", &myreq.AskPositionEffect);
	int i = this->api->ReqQuoteInsert(&myreq, reqid);
	return i;
};

int StockTdApi::reqQuoteCancel(const dict &req, int reqid)
{
	CStockFtdcQuoteCancelReqField myreq = CStockFtdcQuoteCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqQuoteCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqForQuote(const dict &req, int reqid)
{
	CStockFtdcForQuoteReqField myreq = CStockFtdcForQuoteReqField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "QuoteReqID", myreq.QuoteReqID);
	int i = this->api->ReqForQuote(&myreq, reqid);
	return i;
};

int StockTdApi::reqExercise(const dict &req, int reqid)
{
	CStockFtdcExerciseReqField myreq = CStockFtdcExerciseReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqExercise(&myreq, reqid);
	return i;
};

int StockTdApi::reqExerciseCancel(const dict &req, int reqid)
{
	CStockFtdcExerciseCancelReqField myreq = CStockFtdcExerciseCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqExerciseCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryPartAccount(const dict &req, int reqid)
{
	CStockFtdcQryPartAccountField myreq = CStockFtdcQryPartAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqQryPartAccount(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryStockOrder(const dict &req, int reqid)
{
	CStockFtdcQryStockOrderField myreq = CStockFtdcQryStockOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryStockOrder(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryOptionsOrder(const dict &req, int reqid)
{
	CStockFtdcQryOptionsOrderField myreq = CStockFtdcQryOptionsOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryOptionsOrder(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryQuoteOrder(const dict &req, int reqid)
{
	CStockFtdcQryQuoteOrderField myreq = CStockFtdcQryQuoteOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryQuoteOrder(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryStockTrade(const dict &req, int reqid)
{
	CStockFtdcQryStockTradeField myreq = CStockFtdcQryStockTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	getString(req, "TradeID", myreq.TradeID);
	int i = this->api->ReqQryStockTrade(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryOptionsTrade(const dict &req, int reqid)
{
	CStockFtdcQryOptionsTradeField myreq = CStockFtdcQryOptionsTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	getString(req, "ExecID", myreq.ExecID);
	int i = this->api->ReqQryOptionsTrade(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryPosition(const dict &req, int reqid)
{
	CStockFtdcQryPositionField myreq = CStockFtdcQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryPosition(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryTopic(const dict &req, int reqid)
{
	CStockFtdcDisseminationField myreq = CStockFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	int i = this->api->ReqQryTopic(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryStock(const dict &req, int reqid)
{
	CStockFtdcQryStockField myreq = CStockFtdcQryStockField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryStock(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryOptions(const dict &req, int reqid)
{
	CStockFtdcQryOptionsField myreq = CStockFtdcQryOptionsField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryOptions(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryRate(const dict &req, int reqid)
{
	CStockFtdcQryRateField myreq = CStockFtdcQryRateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryRate(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryClientMargin(const dict &req, int reqid)
{
	CStockFtdcQryClientMarginField myreq = CStockFtdcQryClientMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryClientMargin(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryExercise(const dict &req, int reqid)
{
	CStockFtdcQryExerciseField myreq = CStockFtdcQryExerciseField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqQryExercise(&myreq, reqid);
	return i;
};

int StockTdApi::reqMarginCombAction(const dict &req, int reqid)
{
	CStockFtdcMarginCombActionField myreq = CStockFtdcMarginCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "CombID", myreq.CombID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqMarginCombAction(&myreq, reqid);
	return i;
};

int StockTdApi::reqQrySseCombPosition(const dict &req, int reqid)
{
	CStockFtdcCombPositionField myreq = CStockFtdcCombPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqQrySseCombPosition(&myreq, reqid);
	return i;
};

int StockTdApi::reqCombExercise(const dict &req, int reqid)
{
	CStockFtdcCombExerciseReqField myreq = CStockFtdcCombExerciseReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "LegSecurityID1", myreq.LegSecurityID1);
	getInt(req, "LegOrderQty1", &myreq.LegOrderQty1);
	getString(req, "LegSecurityID2", myreq.LegSecurityID2);
	getInt(req, "LegOrderQty2", &myreq.LegOrderQty2);
	int i = this->api->ReqCombExercise(&myreq, reqid);
	return i;
};

