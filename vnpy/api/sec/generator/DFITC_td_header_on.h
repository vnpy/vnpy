virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onRtnNotice(const dict &data) {};

virtual void onRspError(const dict &error) {};

virtual void onRspStockUserLogin(const dict &data, const dict &error) {};

virtual void onRspStockUserLogout(const dict &data, const dict &error) {};

virtual void onRspStockUserPasswordUpdate(const dict &data, const dict &error) {};

virtual void onRspStockEntrustOrder(const dict &data, const dict &error) {};

virtual void onRspStockWithdrawOrder(const dict &data, const dict &error) {};

virtual void onRspStockQryEntrustOrder(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryRealTimeTrade(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQrySerialTrade(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryPosition(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryCapitalAccountInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryAccountInfo(const dict &data, const dict &error) {};

virtual void onRspStockQryShareholderInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspStockTransferFunds(const dict &data, const dict &error) {};

virtual void onRspStockEntrustBatchOrder(const dict &data, const dict &error) {};

virtual void onRspStockWithdrawBatchOrder(const dict &data, const dict &error) {};

virtual void onRspStockCalcAbleEntrustQty(const dict &data, const dict &error) {};

virtual void onRspStockCalcAblePurchaseETFQty(const dict &data, const dict &error) {};

virtual void onRspStockQryFreezeFundsDetail(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryFreezeStockDetail(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryTransferStockDetail(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryTransferFundsDetail(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryStockInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryStockStaticInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspStockQryTradeTime(const dict &data, const dict &error) {};

virtual void onStockEntrustOrderRtn(const dict &data) {};

virtual void onStockTradeRtn(const dict &data) {};

virtual void onStockWithdrawOrderRtn(const dict &data) {};

virtual void onRspSOPUserLogin(const dict &data, const dict &error) {};

virtual void onRspSOPUserLogout(const dict &data, const dict &error) {};

virtual void onRspSOPUserPasswordUpdate(const dict &data, const dict &error) {};

virtual void onRspSOPEntrustOrder(const dict &data, const dict &error) {};

virtual void onRspSOPQuoteEntrustOrder(const dict &data, const dict &error) {};

virtual void onRspSOPGroupSplit(const dict &data, const dict &error) {};

virtual void onRspSOPGroupExectueOrder(const dict &data, const dict &error) {};

virtual void onRspSOPQryGroupPosition(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPLockOUnLockStock(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPWithdrawOrder(const dict &data, const dict &error) {};

virtual void onRspSOPQryEntrustOrder(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQrySerialTrade(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryPosition(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryCollateralPosition(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryCapitalAccountInfo(const dict &data, const dict &error) {};

virtual void onRspSOPQryAccountInfo(const dict &data, const dict &error) {};

virtual void onRspSOPQryShareholderInfo(const dict &data, const dict &error) {};

virtual void onRspSOPCalcAbleEntrustQty(const dict &data, const dict &error) {};

virtual void onRspSOPQryAbleLockStock(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryContactInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPExectueOrder(const dict &data, const dict &error) {};

virtual void onRspSOPQryExecAssiInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryTradeTime(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryExchangeInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryCommission(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryDeposit(const dict &data, const dict &error, bool last) {};

virtual void onRspSOPQryContractObjectInfo(const dict &data, const dict &error, bool last) {};

virtual void onSOPEntrustOrderRtn(const dict &data) {};

virtual void onSOPTradeRtn(const dict &data) {};

virtual void onSOPWithdrawOrderRtn(const dict &data) {};

virtual void onRspFASLUserLogin(const dict &data, const dict &error) {};

virtual void onRspFASLUserLogout(const dict &data, const dict &error) {};

virtual void onRspFASLQryAbleFinInfo(const dict &data, const dict &error) {};

virtual void onRspFASLQryAbleSloInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLTransferCollateral(const dict &data, const dict &error) {};

virtual void onRspFASLDirectRepayment(const dict &data, const dict &error) {};

virtual void onRspFASLRepayStockTransfer(const dict &data, const dict &error) {};

virtual void onRspFASLEntrustCrdtOrder(const dict &data, const dict &error) {};

virtual void onRspFASLEntrustOrder(const dict &data, const dict &error) {};

virtual void onRspFASLCalcAbleEntrustCrdtQty(const dict &data, const dict &error) {};

virtual void onRspFASLQryCrdtFunds(const dict &data, const dict &error) {};

virtual void onRspFASLQryCrdtContract(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryCrdtConChangeInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLTransferFunds(const dict &data, const dict &error) {};

virtual void onRspFASLQryAccountInfo(const dict &data, const dict &error) {};

virtual void onRspFASLQryCapitalAccountInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryShareholderInfo(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryPosition(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryEntrustOrder(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQrySerialTrade(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryRealTimeTrade(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryFreezeFundsDetail(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryFreezeStockDetail(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryTransferFundsDetail(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLWithdrawOrder(const dict &data, const dict &error) {};

virtual void onRspFASLQrySystemTime(const dict &data, const dict &error) {};

virtual void onRspFASLQryTransferredContract(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLDesirableFundsOut(const dict &data, const dict &error) {};

virtual void onRspFASLQryGuaranteedContract(const dict &data, const dict &error, bool last) {};

virtual void onRspFASLQryUnderlyingContract(const dict &data, const dict &error, bool last) {};

virtual void onFASLEntrustOrderRtn(const dict &data) {};

virtual void onFASLTradeRtn(const dict &data) {};

virtual void onFASLWithdrawOrderRtn(const dict &data) {};

