




virtual void onRspError(dict error, int id, bool last) {};

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last) {};

virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last) {};

virtual void onRtnFlowMessageCancel(dict data) {};

virtual void onRtnTrade(dict data) {};

virtual void onRtnOrder(dict data) {};

virtual void onErrRtnOrderInsert(dict data, dict error) {};

virtual void onErrRtnOrderAction(dict data, dict error) {};

virtual void onRtnInstrumentStatus(dict data) {};

virtual void onRtnInvestorAccountDeposit(dict data) {};

virtual void onRtnMessageNotify(dict data) {};

virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error) {};

virtual void onErrRtnBankToFutureByFuture(dict data, dict error) {};

virtual void onErrRtnFutureToBankByFuture(dict data, dict error) {};

virtual void onRtnQueryBankBalanceByFuture(dict data) {};

virtual void onRtnFromBankToFutureByFuture(dict data) {};

virtual void onRtnFromFutureToBankByFuture(dict data) {};

virtual void onRtnSGEDeferRate(dict data) {};

virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

virtual void onRspQryUserInvestor(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorAccount(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

virtual void onRspSubscribeTopic(dict data, dict error, int id, bool last) {};

virtual void onRspQryTopic(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorFee(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorMargin(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchangeDiffTime(dict data, dict error, int id, bool last) {};

virtual void onRspQryContractBank(dict data, dict error, int id, bool last) {};

virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last) {};

virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last) {};

virtual void onRspQrySGEDeferRate(dict data, dict error, int id, bool last) {};

virtual void onRspQryMarketData(dict data, dict error, int id, bool last) {};

