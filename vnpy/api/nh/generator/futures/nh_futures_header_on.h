virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onRspAuthenticate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspTradingAccountPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspParkedOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryMaxOrderVolume(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspSettlementInfoConfirm(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspRemoveParkedOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspRemoveParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspExecOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspExecOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspForQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQuoteAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspBatchOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOptionSelfCloseInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOptionSelfCloseAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspCombActionInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestor(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTradingCode(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrumentMarginRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrumentCommissionRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryProduct(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryDepthMarketData(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQrySettlementInfo(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTransferBank(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorPositionDetail(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryNotice(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQrySettlementInfoConfirm(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorPositionCombineDetail(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCFMMCTradingAccountKey(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryEWarrantOffset(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorProductGroupMargin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExchangeMarginRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExchangeMarginRateAdjust(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExchangeRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQrySecAgentACIDMap(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryProductExchRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryProductGroup(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryMMInstrumentCommissionRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryMMOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrumentOrderCommRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQrySecAgentTradingAccount(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQrySecAgentCheckMode(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOptionInstrTradeCost(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExecOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryForQuote(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryQuote(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOptionSelfClose(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestUnit(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCombInstrumentGuard(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCombAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTransferSerial(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryAccountregister(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspForQuote(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspError(const dict &error, int reqid, bool last) {};

virtual void onRtnOrder(const dict &data) {};

virtual void onRtnTrade(const dict &data) {};

virtual void onErrRtnOrderInsert(const dict &data, const dict &error) {};

virtual void onErrRtnOrderAction(const dict &data, const dict &error) {};

virtual void onRtnInstrumentStatus(const dict &data) {};

virtual void onRtnBulletin(const dict &data) {};

virtual void onRtnTradingNotice(const dict &data) {};

virtual void onRtnErrorConditionalOrder(const dict &data) {};

virtual void onRtnExecOrder(const dict &data) {};

virtual void onErrRtnExecOrderInsert(const dict &data, const dict &error) {};

virtual void onErrRtnExecOrderAction(const dict &data, const dict &error) {};

virtual void onErrRtnForQuoteInsert(const dict &data, const dict &error) {};

virtual void onRtnQuote(const dict &data) {};

virtual void onErrRtnQuoteInsert(const dict &data, const dict &error) {};

virtual void onErrRtnQuoteAction(const dict &data, const dict &error) {};

virtual void onRtnForQuote(const dict &data) {};

virtual void onRtnCFMMCTradingAccountToken(const dict &data) {};

virtual void onErrRtnBatchOrderAction(const dict &data, const dict &error) {};

virtual void onRtnOptionSelfClose(const dict &data) {};

virtual void onErrRtnOptionSelfCloseInsert(const dict &data, const dict &error) {};

virtual void onErrRtnOptionSelfCloseAction(const dict &data, const dict &error) {};

virtual void onRtnCombAction(const dict &data) {};

virtual void onErrRtnCombActionInsert(const dict &data, const dict &error) {};

virtual void onRspQryContractBank(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryParkedOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTradingNotice(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryBrokerTradingParams(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryBrokerTradingAlgos(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryCFMMCTradingAccountToken(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnFromBankToFutureByBank(const dict &data) {};

virtual void onRtnFromFutureToBankByBank(const dict &data) {};

virtual void onRtnRepealFromBankToFutureByBank(const dict &data) {};

virtual void onRtnRepealFromFutureToBankByBank(const dict &data) {};

virtual void onRtnFromBankToFutureByFuture(const dict &data) {};

virtual void onRtnFromFutureToBankByFuture(const dict &data) {};

virtual void onRtnRepealFromBankToFutureByFutureManual(const dict &data) {};

virtual void onRtnRepealFromFutureToBankByFutureManual(const dict &data) {};

virtual void onRtnQueryBankBalanceByFuture(const dict &data) {};

virtual void onErrRtnBankToFutureByFuture(const dict &data, const dict &error) {};

virtual void onErrRtnFutureToBankByFuture(const dict &data, const dict &error) {};

virtual void onErrRtnRepealBankToFutureByFutureManual(const dict &data, const dict &error) {};

virtual void onErrRtnRepealFutureToBankByFutureManual(const dict &data, const dict &error) {};

virtual void onErrRtnQueryBankBalanceByFuture(const dict &data, const dict &error) {};

virtual void onRtnRepealFromBankToFutureByFuture(const dict &data) {};

virtual void onRtnRepealFromFutureToBankByFuture(const dict &data) {};

virtual void onRspFromBankToFutureByFuture(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspFromFutureToBankByFuture(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryBankAccountMoneyByFuture(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnOpenAccountByBank(const dict &data) {};

virtual void onRtnCancelAccountByBank(const dict &data) {};

virtual void onRtnChangeAccountByBank(const dict &data) {};

