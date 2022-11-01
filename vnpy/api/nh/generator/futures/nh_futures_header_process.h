void processFrontConnected(Task *task);

void processFrontDisconnected(Task *task);

void processHeartBeatWarning(Task *task);

void processRspAuthenticate(Task *task);

void processRspUserLogin(Task *task);

void processRspUserLogout(Task *task);

void processRspUserPasswordUpdate(Task *task);

void processRspTradingAccountPasswordUpdate(Task *task);

void processRspOrderInsert(Task *task);

void processRspParkedOrderInsert(Task *task);

void processRspParkedOrderAction(Task *task);

void processRspOrderAction(Task *task);

void processRspQueryMaxOrderVolume(Task *task);

void processRspSettlementInfoConfirm(Task *task);

void processRspRemoveParkedOrder(Task *task);

void processRspRemoveParkedOrderAction(Task *task);

void processRspExecOrderInsert(Task *task);

void processRspExecOrderAction(Task *task);

void processRspForQuoteInsert(Task *task);

void processRspQuoteInsert(Task *task);

void processRspQuoteAction(Task *task);

void processRspBatchOrderAction(Task *task);

void processRspOptionSelfCloseInsert(Task *task);

void processRspOptionSelfCloseAction(Task *task);

void processRspCombActionInsert(Task *task);

void processRspQryOrder(Task *task);

void processRspQryTrade(Task *task);

void processRspQryInvestorPosition(Task *task);

void processRspQryTradingAccount(Task *task);

void processRspQryInvestor(Task *task);

void processRspQryTradingCode(Task *task);

void processRspQryInstrumentMarginRate(Task *task);

void processRspQryInstrumentCommissionRate(Task *task);

void processRspQryExchange(Task *task);

void processRspQryProduct(Task *task);

void processRspQryInstrument(Task *task);

void processRspQryDepthMarketData(Task *task);

void processRspQrySettlementInfo(Task *task);

void processRspQryTransferBank(Task *task);

void processRspQryInvestorPositionDetail(Task *task);

void processRspQryNotice(Task *task);

void processRspQrySettlementInfoConfirm(Task *task);

void processRspQryInvestorPositionCombineDetail(Task *task);

void processRspQryCFMMCTradingAccountKey(Task *task);

void processRspQryEWarrantOffset(Task *task);

void processRspQryInvestorProductGroupMargin(Task *task);

void processRspQryExchangeMarginRate(Task *task);

void processRspQryExchangeMarginRateAdjust(Task *task);

void processRspQryExchangeRate(Task *task);

void processRspQrySecAgentACIDMap(Task *task);

void processRspQryProductExchRate(Task *task);

void processRspQryProductGroup(Task *task);

void processRspQryMMInstrumentCommissionRate(Task *task);

void processRspQryMMOptionInstrCommRate(Task *task);

void processRspQryInstrumentOrderCommRate(Task *task);

void processRspQrySecAgentTradingAccount(Task *task);

void processRspQrySecAgentCheckMode(Task *task);

void processRspQryOptionInstrTradeCost(Task *task);

void processRspQryOptionInstrCommRate(Task *task);

void processRspQryExecOrder(Task *task);

void processRspQryForQuote(Task *task);

void processRspQryQuote(Task *task);

void processRspQryOptionSelfClose(Task *task);

void processRspQryInvestUnit(Task *task);

void processRspQryCombInstrumentGuard(Task *task);

void processRspQryCombAction(Task *task);

void processRspQryTransferSerial(Task *task);

void processRspQryAccountregister(Task *task);

void processRspForQuote(Task *task);

void processRspError(Task *task);

void processRtnOrder(Task *task);

void processRtnTrade(Task *task);

void processErrRtnOrderInsert(Task *task);

void processErrRtnOrderAction(Task *task);

void processRtnInstrumentStatus(Task *task);

void processRtnBulletin(Task *task);

void processRtnTradingNotice(Task *task);

void processRtnErrorConditionalOrder(Task *task);

void processRtnExecOrder(Task *task);

void processErrRtnExecOrderInsert(Task *task);

void processErrRtnExecOrderAction(Task *task);

void processErrRtnForQuoteInsert(Task *task);

void processRtnQuote(Task *task);

void processErrRtnQuoteInsert(Task *task);

void processErrRtnQuoteAction(Task *task);

void processRtnForQuote(Task *task);

void processRtnCFMMCTradingAccountToken(Task *task);

void processErrRtnBatchOrderAction(Task *task);

void processRtnOptionSelfClose(Task *task);

void processErrRtnOptionSelfCloseInsert(Task *task);

void processErrRtnOptionSelfCloseAction(Task *task);

void processRtnCombAction(Task *task);

void processErrRtnCombActionInsert(Task *task);

void processRspQryContractBank(Task *task);

void processRspQryParkedOrder(Task *task);

void processRspQryParkedOrderAction(Task *task);

void processRspQryTradingNotice(Task *task);

void processRspQryBrokerTradingParams(Task *task);

void processRspQryBrokerTradingAlgos(Task *task);

void processRspQueryCFMMCTradingAccountToken(Task *task);

void processRtnFromBankToFutureByBank(Task *task);

void processRtnFromFutureToBankByBank(Task *task);

void processRtnRepealFromBankToFutureByBank(Task *task);

void processRtnRepealFromFutureToBankByBank(Task *task);

void processRtnFromBankToFutureByFuture(Task *task);

void processRtnFromFutureToBankByFuture(Task *task);

void processRtnRepealFromBankToFutureByFutureManual(Task *task);

void processRtnRepealFromFutureToBankByFutureManual(Task *task);

void processRtnQueryBankBalanceByFuture(Task *task);

void processErrRtnBankToFutureByFuture(Task *task);

void processErrRtnFutureToBankByFuture(Task *task);

void processErrRtnRepealBankToFutureByFutureManual(Task *task);

void processErrRtnRepealFutureToBankByFutureManual(Task *task);

void processErrRtnQueryBankBalanceByFuture(Task *task);

void processRtnRepealFromBankToFutureByFuture(Task *task);

void processRtnRepealFromFutureToBankByFuture(Task *task);

void processRspFromBankToFutureByFuture(Task *task);

void processRspFromFutureToBankByFuture(Task *task);

void processRspQueryBankAccountMoneyByFuture(Task *task);

void processRtnOpenAccountByBank(Task *task);

void processRtnCancelAccountByBank(Task *task);

void processRtnChangeAccountByBank(Task *task);

