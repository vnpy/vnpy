void onFrontConnected() override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onFrontConnected);
};

void onFrontDisconnected(int reqid) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onFrontDisconnected, reqid);
};

void onHeartBeatWarning(int reqid) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onHeartBeatWarning, reqid);
};

void onRspAuthenticate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspAuthenticate, data, error, reqid, last);
};

void onRspUserLogin(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspUserLogin, data, error, reqid, last);
};

void onRspUserLogout(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspUserLogout, data, error, reqid, last);
};

void onRspUserPasswordUpdate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspUserPasswordUpdate, data, error, reqid, last);
};

void onRspTradingAccountPasswordUpdate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspTradingAccountPasswordUpdate, data, error, reqid, last);
};

void onRspUserAuthMethod(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspUserAuthMethod, data, error, reqid, last);
};

void onRspGenUserCaptcha(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspGenUserCaptcha, data, error, reqid, last);
};

void onRspGenUserText(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspGenUserText, data, error, reqid, last);
};

void onRspOrderInsert(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspOrderInsert, data, error, reqid, last);
};

void onRspParkedOrderInsert(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspParkedOrderInsert, data, error, reqid, last);
};

void onRspParkedOrderAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspParkedOrderAction, data, error, reqid, last);
};

void onRspOrderAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspOrderAction, data, error, reqid, last);
};

void onRspQueryMaxOrderVolume(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQueryMaxOrderVolume, data, error, reqid, last);
};

void onRspSettlementInfoConfirm(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspSettlementInfoConfirm, data, error, reqid, last);
};

void onRspRemoveParkedOrder(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspRemoveParkedOrder, data, error, reqid, last);
};

void onRspRemoveParkedOrderAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspRemoveParkedOrderAction, data, error, reqid, last);
};

void onRspExecOrderInsert(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspExecOrderInsert, data, error, reqid, last);
};

void onRspExecOrderAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspExecOrderAction, data, error, reqid, last);
};

void onRspForQuoteInsert(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspForQuoteInsert, data, error, reqid, last);
};

void onRspQuoteInsert(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQuoteInsert, data, error, reqid, last);
};

void onRspQuoteAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQuoteAction, data, error, reqid, last);
};

void onRspBatchOrderAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspBatchOrderAction, data, error, reqid, last);
};

void onRspOptionSelfCloseInsert(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspOptionSelfCloseInsert, data, error, reqid, last);
};

void onRspOptionSelfCloseAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspOptionSelfCloseAction, data, error, reqid, last);
};

void onRspCombActionInsert(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspCombActionInsert, data, error, reqid, last);
};

void onRspQryOrder(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryOrder, data, error, reqid, last);
};

void onRspQryTrade(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryTrade, data, error, reqid, last);
};

void onRspQryInvestorPosition(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInvestorPosition, data, error, reqid, last);
};

void onRspQryTradingAccount(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryTradingAccount, data, error, reqid, last);
};

void onRspQryInvestor(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInvestor, data, error, reqid, last);
};

void onRspQryTradingCode(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryTradingCode, data, error, reqid, last);
};

void onRspQryInstrumentMarginRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInstrumentMarginRate, data, error, reqid, last);
};

void onRspQryInstrumentCommissionRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInstrumentCommissionRate, data, error, reqid, last);
};

void onRspQryExchange(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryExchange, data, error, reqid, last);
};

void onRspQryProduct(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryProduct, data, error, reqid, last);
};

void onRspQryInstrument(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInstrument, data, error, reqid, last);
};

void onRspQryDepthMarketData(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryDepthMarketData, data, error, reqid, last);
};

void onRspQrySettlementInfo(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQrySettlementInfo, data, error, reqid, last);
};

void onRspQryTransferBank(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryTransferBank, data, error, reqid, last);
};

void onRspQryInvestorPositionDetail(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInvestorPositionDetail, data, error, reqid, last);
};

void onRspQryNotice(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryNotice, data, error, reqid, last);
};

void onRspQrySettlementInfoConfirm(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQrySettlementInfoConfirm, data, error, reqid, last);
};

void onRspQryInvestorPositionCombineDetail(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInvestorPositionCombineDetail, data, error, reqid, last);
};

void onRspQryCFMMCTradingAccountKey(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryCFMMCTradingAccountKey, data, error, reqid, last);
};

void onRspQryEWarrantOffset(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryEWarrantOffset, data, error, reqid, last);
};

void onRspQryInvestorProductGroupMargin(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInvestorProductGroupMargin, data, error, reqid, last);
};

void onRspQryExchangeMarginRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryExchangeMarginRate, data, error, reqid, last);
};

void onRspQryExchangeMarginRateAdjust(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryExchangeMarginRateAdjust, data, error, reqid, last);
};

void onRspQryExchangeRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryExchangeRate, data, error, reqid, last);
};

void onRspQrySecAgentACIDMap(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQrySecAgentACIDMap, data, error, reqid, last);
};

void onRspQryProductExchRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryProductExchRate, data, error, reqid, last);
};

void onRspQryProductGroup(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryProductGroup, data, error, reqid, last);
};

void onRspQryMMInstrumentCommissionRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryMMInstrumentCommissionRate, data, error, reqid, last);
};

void onRspQryMMOptionInstrCommRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryMMOptionInstrCommRate, data, error, reqid, last);
};

void onRspQryInstrumentOrderCommRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInstrumentOrderCommRate, data, error, reqid, last);
};

void onRspQrySecAgentTradingAccount(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQrySecAgentTradingAccount, data, error, reqid, last);
};

void onRspQrySecAgentCheckMode(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQrySecAgentCheckMode, data, error, reqid, last);
};

void onRspQrySecAgentTradeInfo(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQrySecAgentTradeInfo, data, error, reqid, last);
};

void onRspQryOptionInstrTradeCost(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryOptionInstrTradeCost, data, error, reqid, last);
};

void onRspQryOptionInstrCommRate(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryOptionInstrCommRate, data, error, reqid, last);
};

void onRspQryExecOrder(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryExecOrder, data, error, reqid, last);
};

void onRspQryForQuote(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryForQuote, data, error, reqid, last);
};

void onRspQryQuote(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryQuote, data, error, reqid, last);
};

void onRspQryOptionSelfClose(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryOptionSelfClose, data, error, reqid, last);
};

void onRspQryInvestUnit(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryInvestUnit, data, error, reqid, last);
};

void onRspQryCombInstrumentGuard(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryCombInstrumentGuard, data, error, reqid, last);
};

void onRspQryCombAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryCombAction, data, error, reqid, last);
};

void onRspQryTransferSerial(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryTransferSerial, data, error, reqid, last);
};

void onRspQryAccountregister(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryAccountregister, data, error, reqid, last);
};

void onRspError(dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspError, error, reqid, last);
};

void onRtnOrder(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnOrder, data);
};

void onRtnTrade(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnTrade, data);
};

void onErrRtnOrderInsert(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnOrderInsert, data, error);
};

void onErrRtnOrderAction(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnOrderAction, data, error);
};

void onRtnInstrumentStatus(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnInstrumentStatus, data);
};

void onRtnBulletin(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnBulletin, data);
};

void onRtnTradingNotice(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnTradingNotice, data);
};

void onRtnErrorConditionalOrder(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnErrorConditionalOrder, data);
};

void onRtnExecOrder(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnExecOrder, data);
};

void onErrRtnExecOrderInsert(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnExecOrderInsert, data, error);
};

void onErrRtnExecOrderAction(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnExecOrderAction, data, error);
};

void onErrRtnForQuoteInsert(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnForQuoteInsert, data, error);
};

void onRtnQuote(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnQuote, data);
};

void onErrRtnQuoteInsert(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnQuoteInsert, data, error);
};

void onErrRtnQuoteAction(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnQuoteAction, data, error);
};

void onRtnForQuoteRsp(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnForQuoteRsp, data);
};

void onRtnCFMMCTradingAccountToken(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnCFMMCTradingAccountToken, data);
};

void onErrRtnBatchOrderAction(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnBatchOrderAction, data, error);
};

void onRtnOptionSelfClose(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnOptionSelfClose, data);
};

void onErrRtnOptionSelfCloseInsert(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnOptionSelfCloseInsert, data, error);
};

void onErrRtnOptionSelfCloseAction(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnOptionSelfCloseAction, data, error);
};

void onRtnCombAction(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnCombAction, data);
};

void onErrRtnCombActionInsert(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnCombActionInsert, data, error);
};

void onRspQryContractBank(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryContractBank, data, error, reqid, last);
};

void onRspQryParkedOrder(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryParkedOrder, data, error, reqid, last);
};

void onRspQryParkedOrderAction(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryParkedOrderAction, data, error, reqid, last);
};

void onRspQryTradingNotice(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryTradingNotice, data, error, reqid, last);
};

void onRspQryBrokerTradingParams(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryBrokerTradingParams, data, error, reqid, last);
};

void onRspQryBrokerTradingAlgos(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQryBrokerTradingAlgos, data, error, reqid, last);
};

void onRspQueryCFMMCTradingAccountToken(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQueryCFMMCTradingAccountToken, data, error, reqid, last);
};

void onRtnFromBankToFutureByBank(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnFromBankToFutureByBank, data);
};

void onRtnFromFutureToBankByBank(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnFromFutureToBankByBank, data);
};

void onRtnRepealFromBankToFutureByBank(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnRepealFromBankToFutureByBank, data);
};

void onRtnRepealFromFutureToBankByBank(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnRepealFromFutureToBankByBank, data);
};

void onRtnFromBankToFutureByFuture(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnFromBankToFutureByFuture, data);
};

void onRtnFromFutureToBankByFuture(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnFromFutureToBankByFuture, data);
};

void onRtnRepealFromBankToFutureByFutureManual(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnRepealFromBankToFutureByFutureManual, data);
};

void onRtnRepealFromFutureToBankByFutureManual(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnRepealFromFutureToBankByFutureManual, data);
};

void onRtnQueryBankBalanceByFuture(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnQueryBankBalanceByFuture, data);
};

void onErrRtnBankToFutureByFuture(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnBankToFutureByFuture, data, error);
};

void onErrRtnFutureToBankByFuture(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnFutureToBankByFuture, data, error);
};

void onErrRtnRepealBankToFutureByFutureManual(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnRepealBankToFutureByFutureManual, data, error);
};

void onErrRtnRepealFutureToBankByFutureManual(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnRepealFutureToBankByFutureManual, data, error);
};

void onErrRtnQueryBankBalanceByFuture(dict data, dict error) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onErrRtnQueryBankBalanceByFuture, data, error);
};

void onRtnRepealFromBankToFutureByFuture(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnRepealFromBankToFutureByFuture, data);
};

void onRtnRepealFromFutureToBankByFuture(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnRepealFromFutureToBankByFuture, data);
};

void onRspFromBankToFutureByFuture(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspFromBankToFutureByFuture, data, error, reqid, last);
};

void onRspFromFutureToBankByFuture(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspFromFutureToBankByFuture, data, error, reqid, last);
};

void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRspQueryBankAccountMoneyByFuture, data, error, reqid, last);
};

void onRtnOpenAccountByBank(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnOpenAccountByBank, data);
};

void onRtnCancelAccountByBank(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnCancelAccountByBank, data);
};

void onRtnChangeAccountByBank(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, TdApi, onRtnChangeAccountByBank, data);
};

