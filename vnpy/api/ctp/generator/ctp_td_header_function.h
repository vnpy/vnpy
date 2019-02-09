int reqAuthenticate(dict req, int reqid);

int reqUserLogin(dict req, int reqid);

int reqUserLogout(dict req, int reqid);

int reqUserPasswordUpdate(dict req, int reqid);

int reqTradingAccountPasswordUpdate(dict req, int reqid);

int reqUserAuthMethod(dict req, int reqid);

int reqGenUserCaptcha(dict req, int reqid);

int reqGenUserText(dict req, int reqid);

int reqUserLoginWithCaptcha(dict req, int reqid);

int reqUserLoginWithText(dict req, int reqid);

int reqUserLoginWithOTP(dict req, int reqid);

int reqOrderInsert(dict req, int reqid);

int reqParkedOrderInsert(dict req, int reqid);

int reqParkedOrderAction(dict req, int reqid);

int reqOrderAction(dict req, int reqid);

int reqQueryMaxOrderVolume(dict req, int reqid);

int reqSettlementInfoConfirm(dict req, int reqid);

int reqRemoveParkedOrder(dict req, int reqid);

int reqRemoveParkedOrderAction(dict req, int reqid);

int reqExecOrderInsert(dict req, int reqid);

int reqExecOrderAction(dict req, int reqid);

int reqForQuoteInsert(dict req, int reqid);

int reqQuoteInsert(dict req, int reqid);

int reqQuoteAction(dict req, int reqid);

int reqBatchOrderAction(dict req, int reqid);

int reqOptionSelfCloseInsert(dict req, int reqid);

int reqOptionSelfCloseAction(dict req, int reqid);

int reqCombActionInsert(dict req, int reqid);

int reqQryOrder(dict req, int reqid);

int reqQryTrade(dict req, int reqid);

int reqQryInvestorPosition(dict req, int reqid);

int reqQryTradingAccount(dict req, int reqid);

int reqQryInvestor(dict req, int reqid);

int reqQryTradingCode(dict req, int reqid);

int reqQryInstrumentMarginRate(dict req, int reqid);

int reqQryInstrumentCommissionRate(dict req, int reqid);

int reqQryExchange(dict req, int reqid);

int reqQryProduct(dict req, int reqid);

int reqQryInstrument(dict req, int reqid);

int reqQryDepthMarketData(dict req, int reqid);

int reqQrySettlementInfo(dict req, int reqid);

int reqQryTransferBank(dict req, int reqid);

int reqQryInvestorPositionDetail(dict req, int reqid);

int reqQryNotice(dict req, int reqid);

int reqQrySettlementInfoConfirm(dict req, int reqid);

int reqQryInvestorPositionCombineDetail(dict req, int reqid);

int reqQryCFMMCTradingAccountKey(dict req, int reqid);

int reqQryEWarrantOffset(dict req, int reqid);

int reqQryInvestorProductGroupMargin(dict req, int reqid);

int reqQryExchangeMarginRate(dict req, int reqid);

int reqQryExchangeMarginRateAdjust(dict req, int reqid);

int reqQryExchangeRate(dict req, int reqid);

int reqQrySecAgentACIDMap(dict req, int reqid);

int reqQryProductExchRate(dict req, int reqid);

int reqQryProductGroup(dict req, int reqid);

int reqQryMMInstrumentCommissionRate(dict req, int reqid);

int reqQryMMOptionInstrCommRate(dict req, int reqid);

int reqQryInstrumentOrderCommRate(dict req, int reqid);

int reqQrySecAgentTradingAccount(dict req, int reqid);

int reqQrySecAgentCheckMode(dict req, int reqid);

int reqQrySecAgentTradeInfo(dict req, int reqid);

int reqQryOptionInstrTradeCost(dict req, int reqid);

int reqQryOptionInstrCommRate(dict req, int reqid);

int reqQryExecOrder(dict req, int reqid);

int reqQryForQuote(dict req, int reqid);

int reqQryQuote(dict req, int reqid);

int reqQryOptionSelfClose(dict req, int reqid);

int reqQryInvestUnit(dict req, int reqid);

int reqQryCombInstrumentGuard(dict req, int reqid);

int reqQryCombAction(dict req, int reqid);

int reqQryTransferSerial(dict req, int reqid);

int reqQryAccountregister(dict req, int reqid);

int reqQryContractBank(dict req, int reqid);

int reqQryParkedOrder(dict req, int reqid);

int reqQryParkedOrderAction(dict req, int reqid);

int reqQryTradingNotice(dict req, int reqid);

int reqQryBrokerTradingParams(dict req, int reqid);

int reqQryBrokerTradingAlgos(dict req, int reqid);

int reqQueryCFMMCTradingAccountToken(dict req, int reqid);

int reqFromBankToFutureByFuture(dict req, int reqid);

int reqFromFutureToBankByFuture(dict req, int reqid);

int reqQueryBankAccountMoneyByFuture(dict req, int reqid);

