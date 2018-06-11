virtual void onFrontDisconnected(){};

virtual void onRtnNotice(dict data){};

virtual void onRspError(dict error){};

virtual void onRspStockUserLogin(dict data, dict error){};

virtual void onRspStockUserLogout(dict data, dict error){};

virtual void onRspStockUserPasswordUpdate(dict data, dict error){};

virtual void onRspStockEntrustOrder(dict data, dict error){};

virtual void onRspStockWithdrawOrder(dict data, dict error){};

virtual void onRspStockQryEntrustOrder(dict data, dict error, bool flag){};

virtual void onRspStockQryRealTimeTrade(dict data, dict error, bool flag){};

virtual void onRspStockQrySerialTrade(dict data, dict error, bool flag){};

virtual void onRspStockQryPosition(dict data, dict error, bool flag){};

virtual void onRspStockQryCapitalAccountInfo(dict data, dict error, bool flag){};

virtual void onRspStockQryAccountInfo(dict data, dict error){};

virtual void onRspStockQryShareholderInfo(dict data, dict error, bool flag){};

virtual void onRspStockTransferFunds(dict data, dict error){};

virtual void onRspStockEntrustBatchOrder(dict data, dict error){};

virtual void onRspStockWithdrawBatchOrder(dict data, dict error){};

virtual void onRspStockCalcAbleEntrustQty(dict data, dict error){};

virtual void onRspStockCalcAblePurchaseETFQty(dict data, dict error){};

virtual void onRspStockQryFreezeFundsDetail(dict data, dict error, bool flag){};

virtual void onRspStockQryFreezeStockDetail(dict data, dict error, bool flag){};

virtual void onRspStockQryTransferStockDetail(dict data, dict error, bool flag){};

virtual void onRspStockQryTransferFundsDetail(dict data, dict error, bool flag){};

virtual void onRspStockQryStockInfo(dict data, dict error, bool flag){};

virtual void onRspStockQryStockStaticInfo(dict data, dict error, bool flag){};

virtual void onRspStockQryTradeTime(dict data, dict error){};

virtual void onStockEntrustOrderRtn(dict data){};

virtual void onStockTradeRtn(dict data){};

virtual void onStockWithdrawOrderRtn(dict data){};

virtual void onRspSOPUserLogin(dict data, dict error){};

virtual void onRspSOPUserLogout(dict data, dict error){};

virtual void onRspSOPUserPasswordUpdate(dict data, dict error){};

virtual void onRspSOPEntrustOrder(dict data, dict error){};

virtual void onRspSOPGroupSplit(dict data, dict error){};

virtual void onRspSOPQryGroupPosition(dict data, dict error, bool flag){};

virtual void onRspSOPLockOUnLockStock(dict data, dict error, bool flag){};

virtual void onRspSOPWithdrawOrder(dict data, dict error){};

virtual void onRspSOPQryEntrustOrder(dict data, dict error, bool flag){};

virtual void onRspSOPQrySerialTrade(dict data, dict error, bool flag){};

virtual void onRspSOPQryPosition(dict data, dict error, bool flag){};

virtual void onRspSOPQryCollateralPosition(dict data, dict error, bool flag){};

virtual void onRspSOPQryCapitalAccountInfo(dict data, dict error){};

virtual void onRspSOPQryAccountInfo(dict data, dict error){};

virtual void onRspSOPQryShareholderInfo(dict data, dict error){};

virtual void onRspSOPCalcAbleEntrustQty(dict data, dict error){};

virtual void onRspSOPQryAbleLockStock(dict data, dict error, bool flag){};

virtual void onRspSOPQryContactInfo(dict data, dict error, bool flag){};

virtual void onRspSOPExectueOrder(dict data, dict error){};

virtual void onRspSOPQryExecAssiInfo(dict data, dict error, bool flag){};

virtual void onRspSOPQryTradeTime(dict data, dict error, bool flag){};

virtual void onRspSOPQryExchangeInfo(dict data, dict error, bool flag){};

virtual void onRspSOPQryCommission(dict data, dict error, bool flag){};

virtual void onRspSOPQryDeposit(dict data, dict error, bool flag){};

virtual void onRspSOPQryContractObjectInfo(dict data, dict error, bool flag){};

virtual void onSOPEntrustOrderRtn(dict data){};

virtual void onSOPTradeRtn(dict data){};

virtual void onSOPWithdrawOrderRtn(dict data){};

virtual void onRspFASLUserLogin(dict data, dict error){};

virtual void onRspFASLUserLogout(dict data, dict error){};

virtual void onRspFASLQryAbleFinInfo(dict data, dict error){};

virtual void onRspFASLQryAbleSloInfo(dict data, dict error, bool flag){};

virtual void onRspFASLTransferCollateral(dict data, dict error){};

virtual void onRspFASLDirectRepayment(dict data, dict error){};

virtual void onRspFASLRepayStockTransfer(dict data, dict error){};

virtual void onRspFASLEntrustCrdtOrder(dict data, dict error){};

virtual void onRspFASLEntrustOrder(dict data, dict error){};

virtual void onRspFASLCalcAbleEntrustCrdtQty(dict data, dict error){};

virtual void onRspFASLQryCrdtFunds(dict data, dict error){};

virtual void onRspFASLQryCrdtContract(dict data, dict error, bool flag){};

virtual void onRspFASLQryCrdtConChangeInfo(dict data, dict error, bool flag){};

virtual void onRspFASLTransferFunds(dict data, dict error){};

virtual void onRspFASLQryAccountInfo(dict data, dict error){};

virtual void onRspFASLQryCapitalAccountInfo(dict data, dict error, bool flag){};

virtual void onRspFASLQryShareholderInfo(dict data, dict error, bool flag){};

virtual void onRspFASLQryPosition(dict data, dict error, bool flag){};

virtual void onRspFASLQryEntrustOrder(dict data, dict error, bool flag){};

virtual void onRspFASLQrySerialTrade(dict data, dict error, bool flag){};

virtual void onRspFASLQryRealTimeTrade(dict data, dict error, bool flag){};

virtual void onRspFASLQryFreezeFundsDetail(dict data, dict error, bool flag){};

virtual void onRspFASLQryFreezeStockDetail(dict data, dict error, bool flag){};

virtual void onRspFASLQryTransferFundsDetail(dict data, dict error, bool flag){};

virtual void onRspFASLWithdrawOrder(dict data, dict error){};

virtual void onRspFASLQrySystemTime(dict data, dict error){};

virtual void onRspFASLQryTransferredContract(dict data, dict error, bool flag){};

virtual void onRspFASLDesirableFundsOut(dict data, dict error){};

virtual void onRspFASLQryGuaranteedContract(dict data, dict error, bool flag){};

virtual void onRspFASLQryUnderlyingContract(dict data, dict error, bool flag){};

virtual void onFASLEntrustOrderRtn(dict data){};

virtual void onFASLTradeRtn(dict data){};

virtual void onFASLWithdrawOrderRtn(dict data){};

