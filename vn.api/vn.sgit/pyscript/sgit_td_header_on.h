


virtual void onRspAuthenticate(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspParkedOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspParkedOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspQueryMaxOrderVolume(dict data, dict error, int id, bool last) {};

virtual void onRspSettlementInfoConfirm(dict data, dict error, int id, bool last) {};

virtual void onRspRemoveParkedOrder(dict data, dict error, int id, bool last) {};

virtual void onRspRemoveParkedOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspExecOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspExecOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspForQuoteInsert(dict data, dict error, int id, bool last) {};

virtual void onRspQuoteInsert(dict data, dict error, int id, bool last) {};

virtual void onRspQuoteAction(dict data, dict error, int id, bool last) {};

virtual void onRspBatchOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspCombActionInsert(dict data, dict error, int id, bool last) {};

virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestor(dict data, dict error, int id, bool last) {};

virtual void onRspQryTradingCode(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrumentMarginRate(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

virtual void onRspQryProduct(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last) {};

virtual void onRspQrySettlementInfo(dict data, dict error, int id, bool last) {};

virtual void onRspQryTransferBank(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last) {};

virtual void onRspQryNotice(dict data, dict error, int id, bool last) {};

virtual void onRspQrySettlementInfoConfirm(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPositionCombineDetail(dict data, dict error, int id, bool last) {};

virtual void onRspQryCFMMCTradingAccountKey(dict data, dict error, int id, bool last) {};

virtual void onRspQryEWarrantOffset(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorProductGroupMargin(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchangeMarginRate(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchangeMarginRateAdjust(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchangeRate(dict data, dict error, int id, bool last) {};

virtual void onRspQrySecAgentACIDMap(dict data, dict error, int id, bool last) {};

virtual void onRspQryProductExchRate(dict data, dict error, int id, bool last) {};

virtual void onRspQryProductGroup(dict data, dict error, int id, bool last) {};

virtual void onRspQryOptionInstrTradeCost(dict data, dict error, int id, bool last) {};

virtual void onRspQryOptionInstrCommRate(dict data, dict error, int id, bool last) {};

virtual void onRspQryExecOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryForQuote(dict data, dict error, int id, bool last) {};

virtual void onRspQryQuote(dict data, dict error, int id, bool last) {};

virtual void onRspQryCombInstrumentGuard(dict data, dict error, int id, bool last) {};

virtual void onRspQryCombAction(dict data, dict error, int id, bool last) {};

virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last) {};

virtual void onRspQryAccountregister(dict data, dict error, int id, bool last) {};

virtual void onRspError(dict error, int id, bool last) {};

virtual void onRtnOrder(dict data) {};

virtual void onRtnTrade(dict data) {};

virtual void onErrRtnOrderInsert(dict data, dict error) {};

virtual void onErrRtnOrderAction(dict data, dict error) {};

virtual void onRtnInstrumentStatus(dict data) {};

virtual void onRtnTradingNotice(dict data) {};

virtual void onRtnErrorConditionalOrder(dict data) {};

virtual void onRtnExecOrder(dict data) {};

virtual void onErrRtnExecOrderInsert(dict data, dict error) {};

virtual void onErrRtnExecOrderAction(dict data, dict error) {};

virtual void onErrRtnForQuoteInsert(dict data, dict error) {};

virtual void onRtnQuote(dict data) {};

virtual void onErrRtnQuoteInsert(dict data, dict error) {};

virtual void onErrRtnQuoteAction(dict data, dict error) {};

virtual void onRtnForQuoteRsp(dict data) {};

virtual void onRtnCFMMCTradingAccountToken(dict data) {};

virtual void onErrRtnBatchOrderAction(dict data, dict error) {};

virtual void onRtnCombAction(dict data) {};

virtual void onErrRtnCombActionInsert(dict data, dict error) {};

virtual void onRspQryContractBank(dict data, dict error, int id, bool last) {};

virtual void onRspQryParkedOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryParkedOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspQryTradingNotice(dict data, dict error, int id, bool last) {};

virtual void onRspQryBrokerTradingParams(dict data, dict error, int id, bool last) {};

virtual void onRspQryBrokerTradingAlgos(dict data, dict error, int id, bool last) {};

virtual void onRspQueryCFMMCTradingAccountToken(dict data, dict error, int id, bool last) {};

virtual void onRtnFromBankToFutureByBank(dict data) {};

virtual void onRtnFromFutureToBankByBank(dict data) {};

virtual void onRtnRepealFromBankToFutureByBank(dict data) {};

virtual void onRtnRepealFromFutureToBankByBank(dict data) {};

virtual void onRtnFromBankToFutureByFuture(dict data) {};

virtual void onRtnFromFutureToBankByFuture(dict data) {};

virtual void onRtnRepealFromBankToFutureByFutureManual(dict data) {};

virtual void onRtnRepealFromFutureToBankByFutureManual(dict data) {};

virtual void onRtnQueryBankBalanceByFuture(dict data) {};

virtual void onErrRtnBankToFutureByFuture(dict data, dict error) {};

virtual void onErrRtnFutureToBankByFuture(dict data, dict error) {};

virtual void onErrRtnRepealBankToFutureByFutureManual(dict data, dict error) {};

virtual void onErrRtnRepealFutureToBankByFutureManual(dict data, dict error) {};

virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error) {};

virtual void onRtnRepealFromBankToFutureByFuture(dict data) {};

virtual void onRtnRepealFromFutureToBankByFuture(dict data) {};

virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last) {};

virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last) {};

virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last) {};

virtual void onRtnOpenAccountByBank(dict data) {};

virtual void onRtnCancelAccountByBank(dict data) {};

virtual void onRtnChangeAccountByBank(dict data) {};

