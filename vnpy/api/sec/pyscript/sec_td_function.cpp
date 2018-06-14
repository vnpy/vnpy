int TdApi::SubscribePrivateTopic(dict req)
{
	RESUME_TYPE myreq = RESUME_TYPE();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->SubscribePrivateTopic(&myreq);
	return i;
};

int TdApi::reqStockUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqStockUserLogin(&myreq);
	return i;
};

int TdApi::reqStockUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockUserLogout(&myreq);
	return i;
};

int TdApi::reqStockUserPasswordUpdate(dict req)
{
	DFITCSECReqPasswordUpdateField myreq = DFITCSECReqPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "oldPassword", myreq.oldPassword);
	getString(req, "newPassword", myreq.newPassword);
	getInt(req, "passwordType", &myreq.passwordType);
	int i = this->api->ReqStockUserPasswordUpdate(&myreq);
	return i;
};

int TdApi::reqStockEntrustOrder(dict req)
{
	DFITCStockReqEntrustOrderField myreq = DFITCStockReqEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getString(req, "eachSeatID", myreq.eachSeatID);
	getInt(req, "hkEntrustLimit", &myreq.hkEntrustLimit);
	getInt(req, "hkOrderType", &myreq.hkOrderType);
	int i = this->api->ReqStockEntrustOrder(&myreq);
	return i;
};

int TdApi::reqStockWithdrawOrder(dict req)
{
	DFITCSECReqWithdrawOrderField myreq = DFITCSECReqWithdrawOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	int i = this->api->ReqStockWithdrawOrder(&myreq);
	return i;
};

int TdApi::reqStockQryEntrustOrder(dict req)
{
	DFITCStockReqQryEntrustOrderField myreq = DFITCStockReqQryEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustQryFlag", &myreq.entrustQryFlag);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->ReqStockQryEntrustOrder(&myreq);
	return i;
};

int TdApi::reqStockQryRealTimeTrade(dict req)
{
	DFITCStockReqQryRealTimeTradeField myreq = DFITCStockReqQryRealTimeTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "queryFlag", &myreq.queryFlag);
	int i = this->api->ReqStockQryRealTimeTrade(&myreq);
	return i;
};

int TdApi::reqStockQrySerialTrade(dict req)
{
	DFITCStockReqQrySerialTradeField myreq = DFITCStockReqQrySerialTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "tradeQryFlag", &myreq.tradeQryFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->ReqStockQrySerialTrade(&myreq);
	return i;
};

int TdApi::reqStockQryPosition(dict req)
{
	DFITCStockReqQryPositionField myreq = DFITCStockReqQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "posiQryFlag", &myreq.posiQryFlag);
	int i = this->api->ReqStockQryPosition(&myreq);
	return i;
};

int TdApi::reqStockQryCapitalAccountInfo(dict req)
{
	DFITCStockReqQryCapitalAccountField myreq = DFITCStockReqQryCapitalAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "FundsQryFlag", &myreq.FundsQryFlag);
	int i = this->api->ReqStockQryCapitalAccountInfo(&myreq);
	return i;
};

int TdApi::reqStockQryAccountInfo(dict req)
{
	DFITCStockReqQryAccountField myreq = DFITCStockReqQryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockQryAccountInfo(&myreq);
	return i;
};

int TdApi::reqStockQryShareholderInfo(dict req)
{
	DFITCStockReqQryShareholderField myreq = DFITCStockReqQryShareholderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqStockQryShareholderInfo(&myreq);
	return i;
};

int TdApi::reqStockTransferFunds(dict req)
{
	DFITCStockReqTransferFundsField myreq = DFITCStockReqTransferFundsField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getInt(req, "fundsTransFlag", &myreq.fundsTransFlag);
	int i = this->api->ReqStockTransferFunds(&myreq);
	return i;
};

int TdApi::reqStockEntrustBatchOrder(dict req)
{
	DFITCStockReqEntrustBatchOrderField myreq = DFITCStockReqEntrustBatchOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustCount", &myreq.entrustCount);
	getString(req, "entrustDetail", myreq.entrustDetail);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	int i = this->api->ReqStockEntrustBatchOrder(&myreq);
	return i;
};

int TdApi::reqStockWithdrawBatchOrder(dict req)
{
	DFITCStockReqWithdrawBatchOrderField myreq = DFITCStockReqWithdrawBatchOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "orderRangeID", myreq.orderRangeID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	int i = this->api->ReqStockWithdrawBatchOrder(&myreq);
	return i;
};

int TdApi::reqStockCalcAbleEntrustQty(dict req)
{
	DFITCStockReqCalcAbleEntrustQtyField myreq = DFITCStockReqCalcAbleEntrustQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	int i = this->api->ReqStockCalcAbleEntrustQty(&myreq);
	return i;
};

int TdApi::reqStockCalcAblePurchaseETFQty(dict req)
{
	DFITCStockReqCalcAblePurchaseETFQtyField myreq = DFITCStockReqCalcAblePurchaseETFQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->ReqStockCalcAblePurchaseETFQty(&myreq);
	return i;
};

int TdApi::reqStockQryFreezeFundsDetail(dict req)
{
	DFITCStockReqQryFreezeFundsDetailField myreq = DFITCStockReqQryFreezeFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryFreezeFundsDetail(&myreq);
	return i;
};

int TdApi::reqStockQryFreezeStockDetail(dict req)
{
	DFITCStockReqQryFreezeStockDetailField myreq = DFITCStockReqQryFreezeStockDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getInt(req, "stockFreezeType", &myreq.stockFreezeType);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryFreezeStockDetail(&myreq);
	return i;
};

int TdApi::reqStockQryTransferFundsDetail(dict req)
{
	DFITCStockReqQryTransferFundsDetailField myreq = DFITCStockReqQryTransferFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryTransferFundsDetail(&myreq);
	return i;
};

int TdApi::reqStockQryTransferStockDetail(dict req)
{
	DFITCStockReqQryTransferStockDetailField myreq = DFITCStockReqQryTransferStockDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "stockFreezeType", &myreq.stockFreezeType);
	getString(req, "incQryIndex", myreq.incQryIndex);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryTransferStockDetail(&myreq);
	return i;
};

int TdApi::reqStockQryStockInfo(dict req)
{
	DFITCStockReqQryStockField myreq = DFITCStockReqQryStockField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->ReqStockQryStockInfo(&myreq);
	return i;
};

int TdApi::reqStockQryStockStaticInfo(dict req)
{
	DFITCStockReqQryStockStaticField myreq = DFITCStockReqQryStockStaticField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqStockQryStockStaticInfo(&myreq);
	return i;
};

int TdApi::reqStockQryTradeTime(dict req)
{
	DFITCStockReqQryTradeTimeField myreq = DFITCStockReqQryTradeTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockQryTradeTime(&myreq);
	return i;
};

int TdApi::reqSOPUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqSOPUserLogin(&myreq);
	return i;
};

int TdApi::reqSOPUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqSOPUserLogout(&myreq);
	return i;
};

int TdApi::reqSOPUserPasswordUpdate(dict req)
{
	DFITCSECReqPasswordUpdateField myreq = DFITCSECReqPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "oldPassword", myreq.oldPassword);
	getString(req, "newPassword", myreq.newPassword);
	getInt(req, "passwordType", &myreq.passwordType);
	int i = this->api->ReqSOPUserPasswordUpdate(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPEntrustOrder(dict req)
{
	DFITCSOPReqEntrustOrderField myreq = DFITCSOPReqEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getString(req, "subAccountID", myreq.subAccountID);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "coveredFlag", &myreq.coveredFlag);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "orderExpiryDate", &myreq.orderExpiryDate);
	getInt(req, "orderCategory", &myreq.orderCategory);
	getInt(req, "serialID", &myreq.serialID);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->    virtual int ReqSOPEntrustOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPGroupSplit(dict req)
{
	DFITCSOPReqGroupSplitField myreq = DFITCSOPReqGroupSplitField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "subAccountID", myreq.subAccountID);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "groupType", &myreq.groupType);
	getString(req, "groupCode", myreq.groupCode);
	getString(req, "securityOptionID1", myreq.securityOptionID1);
	getString(req, "securityOptionID2", myreq.securityOptionID2);
	getString(req, "securityOptionID3", myreq.securityOptionID3);
	getString(req, "securityOptionID4", myreq.securityOptionID4);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->    virtual int ReqSOPGroupSplit(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryGroupPosition(dict req)
{
	DFITCSOPReqQryGroupPositionField myreq = DFITCSOPReqQryGroupPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqSOPQryGroupPosition(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPLockOUnLockStock(dict req)
{
	DFITCSOPReqLockOUnLockStockField myreq = DFITCSOPReqLockOUnLockStockField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "subAccountID", myreq.subAccountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->    virtual int ReqSOPLockOUnLockStock(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPWithdrawOrder(dict req)
{
	DFITCSECReqWithdrawOrderField myreq = DFITCSECReqWithdrawOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	int i = this->api->    virtual int ReqSOPWithdrawOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryEntrustOrder(dict req)
{
	DFITCSOPReqQryEntrustOrderField myreq = DFITCSOPReqQryEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getInt(req, "exSerialID", &myreq.exSerialID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustQryFlag", &myreq.entrustQryFlag);
	getInt(req, "rowIndex", &myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->    virtual int ReqSOPQryEntrustOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQrySerialTrade(dict req)
{
	DFITCSOPReqQrySerialTradeField myreq = DFITCSOPReqQrySerialTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "incQryIndex", myreq.incQryIndex);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "tradeQryFlag", &myreq.tradeQryFlag);
	getString(req, "currency", myreq.currency);
	getInt(req, "rowIndex", &myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->    virtual int ReqSOPQrySerialTrade(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryPosition(dict req)
{
	DFITCSOPReqQryPositionField myreq = DFITCSOPReqQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getInt(req, "rowIndex", &myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->    virtual int ReqSOPQryPosition(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryCollateralPosition(dict req)
{
	DFITCSOPReqQryCollateralPositionField myreq = DFITCSOPReqQryCollateralPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->    virtual int ReqSOPQryCollateralPosition(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryCapitalAccountInfo(dict req)
{
	DFITCSOPReqQryCapitalAccountField myreq = DFITCSOPReqQryCapitalAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getInt(req, "FundsQryFlag", &myreq.FundsQryFlag);
	int i = this->api->    virtual int ReqSOPQryCapitalAccountInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryAccountInfo(dict req)
{
	DFITCSOPReqQryAccountField myreq = DFITCSOPReqQryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqSOPQryAccountInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryShareholderInfo(dict req)
{
	DFITCSOPReqQryShareholderField myreq = DFITCSOPReqQryShareholderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "accountID", myreq.accountID);
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->    virtual int ReqSOPQryShareholderInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPCalcAbleEntrustQty(dict req)
{
	DFITCSOPReqCalcAbleEntrustQtyField myreq = DFITCSOPReqCalcAbleEntrustQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "subAccountID", myreq.subAccountID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "coveredFlag", &myreq.coveredFlag);
	getInt(req, "coveredFlag", &myreq.coveredFlag);
	getInt(req, "checkUpLimit", &myreq.checkUpLimit);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->    virtual int ReqSOPCalcAbleEntrustQty(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryAbleLockStock(dict req)
{
	DFITCSOPReqQryAbleLockStockField myreq = DFITCSOPReqQryAbleLockStockField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->    virtual int ReqSOPQryAbleLockStock(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryContactInfo(dict req)
{
	DFITCSOPReqQryContactField myreq = DFITCSOPReqQryContactField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "contractObjectType", &myreq.contractObjectType);
	getInt(req, "optType", &myreq.optType);
	getString(req, "rowIndex", myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->    virtual int ReqSOPQryContactInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPExectueOrder(dict req)
{
	DFITCSOPReqExectueOrderField myreq = DFITCSOPReqExectueOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "subAccountID", myreq.subAccountID);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->    virtual int ReqSOPExectueOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryExecAssiInfo(dict req)
{
	DFITCSOPReqQryExecAssiInfoField myreq = DFITCSOPReqQryExecAssiInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getInt(req, "tradeDate", &myreq.tradeDate);
	int i = this->api->    virtual int ReqSOPQryExecAssiInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryTradeTime(dict req)
{
	DFITCSOPReqQryTradeTimeField myreq = DFITCSOPReqQryTradeTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqSOPQryTradeTime(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryExchangeInfo(dict req)
{
	DFITCSOPReqQryExchangeInfoField myreq = DFITCSOPReqQryExchangeInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->    virtual int ReqSOPQryExchangeInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryCommission(dict req)
{
	DFITCSOPReqQryCommissionField myreq = DFITCSOPReqQryCommissionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "refType", &myreq.refType);
	getInt(req, "contractObjectType", &myreq.contractObjectType);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "level", &myreq.level);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	int i = this->api->    virtual int ReqSOPQryCommission(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryDeposit(dict req)
{
	DFITCSOPReqQryDepositField myreq = DFITCSOPReqQryDepositField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "refType", &myreq.refType);
	getInt(req, "securityObjectType", &myreq.securityObjectType);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "level", &myreq.level);
	int i = this->api->    virtual int ReqSOPQryDeposit(&myreq);
	return i;
};

int TdApi::    virtual int reqSOPQryContractObjectInfo(dict req)
{
	DFITCSOPReqQryContractObjectField myreq = DFITCSOPReqQryContractObjectField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "securityObjectType", &myreq.securityObjectType);
	int i = this->api->    virtual int ReqSOPQryContractObjectInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->    virtual int ReqFASLUserLogin(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqFASLUserLogout(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryAbleFinInfo(dict req)
{
	DFITCFASLReqAbleFinInfoField myreq = DFITCFASLReqAbleFinInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqFASLQryAbleFinInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryAbleSloInfo(dict req)
{
	DFITCFASLReqAbleSloInfoField myreq = DFITCFASLReqAbleSloInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqFASLQryAbleSloInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLTransferCollateral(dict req)
{
	DFITCFASLReqTransferCollateralField myreq = DFITCFASLReqTransferCollateralField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "transferQty", &myreq.transferQty);
	int i = this->api->    virtual int ReqFASLTransferCollateral(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLDirectRepayment(dict req)
{
	DFITCFASLReqDirectRepaymentField myreq = DFITCFASLReqDirectRepaymentField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "contractNO", myreq.contractNO);
	int i = this->api->    virtual int ReqFASLDirectRepayment(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLRepayStockTransfer(dict req)
{
	DFITCFASLReqRepayStockTransferField myreq = DFITCFASLReqRepayStockTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "repayQty", &myreq.repayQty);
	getString(req, "securityID", myreq.securityID);
	getString(req, "contractNO", myreq.contractNO);
	int i = this->api->    virtual int ReqFASLRepayStockTransfer(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLEntrustCrdtOrder(dict req)
{
	DFITCFASLReqEntrustCrdtOrderField myreq = DFITCFASLReqEntrustCrdtOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustQty", &myreq.entrustQty);
	int i = this->api->    virtual int ReqFASLEntrustCrdtOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLEntrsuctOrder(dict req)
{
	DFITCFASLReqEntrustOrderField myreq = DFITCFASLReqEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "positionSource", &myreq.positionSource);
	int i = this->api->    virtual int ReqFASLEntrsuctOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLWithdrawOrder(dict req)
{
	DFITCFASLReqWithdrawOrderField myreq = DFITCFASLReqWithdrawOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	int i = this->api->    virtual int ReqFASLWithdrawOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLCalcAbleEntrustCrdtQty(dict req)
{
	DFITCFASLReqCalcAbleEntrustCrdtQtyField myreq = DFITCFASLReqCalcAbleEntrustCrdtQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "positionSource", &myreq.positionSource);
	int i = this->api->    virtual int ReqFASLCalcAbleEntrustCrdtQty(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryCrdtFunds(dict req)
{
	DFITCFASLReqQryCrdtFundsField myreq = DFITCFASLReqQryCrdtFundsField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqFASLQryCrdtFunds(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryCrdtContract(dict req)
{
	DFITCFASLReqQryCrdtContractField myreq = DFITCFASLReqQryCrdtContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "openBeginDate", &myreq.openBeginDate);
	getInt(req, "openEndDate", &myreq.openEndDate);
	getInt(req, "crdtConQryFlag", &myreq.crdtConQryFlag);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "conSerialID", &myreq.conSerialID);
	int i = this->api->    virtual int ReqFASLQryCrdtContract(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryCrdtConChangeInfo(dict req)
{
	DFITCFASLReqQryCrdtConChangeInfoField myreq = DFITCFASLReqQryCrdtConChangeInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "conSerialNO", &myreq.conSerialNO);
	int i = this->api->    virtual int ReqFASLQryCrdtConChangeInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLTransferFunds(dict req)
{
	DFITCStockReqTransferFundsField myreq = DFITCStockReqTransferFundsField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getInt(req, "fundsTransFlag", &myreq.fundsTransFlag);
	int i = this->api->    virtual int ReqFASLTransferFunds(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryAccountInfo(dict req)
{
	DFITCStockReqQryAccountField myreq = DFITCStockReqQryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->    virtual int ReqFASLQryAccountInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryCapitalAccountInfo(dict req)
{
	DFITCStockReqQryCapitalAccountField myreq = DFITCStockReqQryCapitalAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "FundsQryFlag", &myreq.FundsQryFlag);
	int i = this->api->    virtual int ReqFASLQryCapitalAccountInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryShareholderInfo(dict req)
{
	DFITCStockReqQryShareholderField myreq = DFITCStockReqQryShareholderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->    virtual int ReqFASLQryShareholderInfo(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryPosition(dict req)
{
	DFITCStockReqQryPositionField myreq = DFITCStockReqQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "posiQryFlag", &myreq.posiQryFlag);
	int i = this->api->    virtual int ReqFASLQryPosition(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryEntrustOrder(dict req)
{
	DFITCStockReqQryEntrustOrderField myreq = DFITCStockReqQryEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustQryFlag", &myreq.entrustQryFlag);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->    virtual int ReqFASLQryEntrustOrder(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQrySerialTrade(dict req)
{
	DFITCStockReqQrySerialTradeField myreq = DFITCStockReqQrySerialTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "tradeQryFlag", &myreq.tradeQryFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->    virtual int ReqFASLQrySerialTrade(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryRealTimeTrade(dict req)
{
	DFITCStockReqQryRealTimeTradeField myreq = DFITCStockReqQryRealTimeTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "queryFlag", &myreq.queryFlag);
	int i = this->api->    virtual int ReqFASLQryRealTimeTrade(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryFreezeFundsDetail(dict req)
{
	DFITCStockReqQryFreezeFundsDetailField myreq = DFITCStockReqQryFreezeFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->    virtual int ReqFASLQryFreezeFundsDetail(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryFreezeStockDetail(dict req)
{
	DFITCStockReqQryFreezeStockDetailField myreq = DFITCStockReqQryFreezeStockDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getInt(req, "stockFreezeType", &myreq.stockFreezeType);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->    virtual int ReqFASLQryFreezeStockDetail(&myreq);
	return i;
};

int TdApi::    virtual int reqFASLQryTransferFundsDetail(dict req)
{
	DFITCStockReqQryTransferFundsDetailField myreq = DFITCStockReqQryTransferFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->    virtual int ReqFASLQryTransferFundsDetail(&myreq);
	return i;
};

int TdApi::reqFASLQrySystemTime(dict req)
{
	DFITCFASLReqQryTradeTimeField myreq = DFITCFASLReqQryTradeTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "flag", &myreq.flag);
	int i = this->api->ReqFASLQrySystemTime(&myreq);
	return i;
};

int TdApi::reqFASLQryTransferredContract(dict req)
{
	DFITCFASLReqQryTransferredContractField myreq = DFITCFASLReqQryTransferredContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqFASLQryTransferredContract(&myreq);
	return i;
};

int TdApi::reqFASLDesirableFundsOut(dict req)
{
	DFITCFASLReqDesirableFundsOutField myreq = DFITCFASLReqDesirableFundsOutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getString(req, "currency", myreq.currency);
	getString(req, "summaryMsg", myreq.summaryMsg);
	int i = this->api->ReqFASLDesirableFundsOut(&myreq);
	return i;
};

int TdApi::reqFASLQryGuaranteedContract(dict req)
{
	DFITCFASLReqQryGuaranteedContractField myreq = DFITCFASLReqQryGuaranteedContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryGuaranteedContract(&myreq);
	return i;
};

int TdApi::reqFASLQryUnderlyingContract(dict req)
{
	DFITCFASLReqQryUnderlyingContractField myreq = DFITCFASLReqQryUnderlyingContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryUnderlyingContract(&myreq);
	return i;
};

