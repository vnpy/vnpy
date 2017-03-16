virtual void onRspAuthenticate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspAuthenticate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserLogin(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUserLogin")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserLogout(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUserLogout")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUserPasswordUpdate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspTradingAccountPasswordUpdate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspOrderInsert")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspParkedOrderInsert(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspParkedOrderInsert")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspParkedOrderAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspParkedOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspOrderAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQueryMaxOrderVolume(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQueryMaxOrderVolume")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSettlementInfoConfirm(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspSettlementInfoConfirm")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspRemoveParkedOrder(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspRemoveParkedOrder")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspRemoveParkedOrderAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspRemoveParkedOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspExecOrderInsert(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspExecOrderInsert")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspExecOrderAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspExecOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspForQuoteInsert(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspForQuoteInsert")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQuoteInsert(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQuoteInsert")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQuoteAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQuoteAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspBatchOrderAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspBatchOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspCombActionInsert(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspCombActionInsert")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryOrder(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryOrder")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTrade(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTrade")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorPosition")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTradingAccount")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestor(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestor")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTradingCode(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTradingCode")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInstrumentMarginRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInstrumentMarginRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInstrumentCommissionRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchange(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExchange")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryProduct(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryProduct")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInstrument")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryDepthMarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQrySettlementInfo(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQrySettlementInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTransferBank(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTransferBank")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorPositionDetail")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryNotice(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryNotice")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQrySettlementInfoConfirm(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQrySettlementInfoConfirm")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorPositionCombineDetail(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorPositionCombineDetail")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryCFMMCTradingAccountKey(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryCFMMCTradingAccountKey")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryEWarrantOffset(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryEWarrantOffset")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorProductGroupMargin(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorProductGroupMargin")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchangeMarginRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExchangeMarginRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchangeMarginRateAdjust(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExchangeMarginRateAdjust")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchangeRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExchangeRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQrySecAgentACIDMap(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQrySecAgentACIDMap")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryProductExchRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryProductExchRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryProductGroup(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryProductGroup")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryOptionInstrTradeCost(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryOptionInstrTradeCost")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryOptionInstrCommRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryOptionInstrCommRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExecOrder(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExecOrder")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryForQuote(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryForQuote")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryQuote(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryQuote")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryCombInstrumentGuard(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryCombInstrumentGuard")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryCombAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryCombAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTransferSerial")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryAccountregister(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryAccountregister")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspError(dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspError")(error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnOrder(dict data)
{
	try
	{
		this->get_override("onRtnOrder")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnTrade(dict data)
{
	try
	{
		this->get_override("onRtnTrade")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnOrderInsert(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnOrderInsert")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnOrderAction(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnOrderAction")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnInstrumentStatus(dict data)
{
	try
	{
		this->get_override("onRtnInstrumentStatus")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnTradingNotice(dict data)
{
	try
	{
		this->get_override("onRtnTradingNotice")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnErrorConditionalOrder(dict data)
{
	try
	{
		this->get_override("onRtnErrorConditionalOrder")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnExecOrder(dict data)
{
	try
	{
		this->get_override("onRtnExecOrder")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnExecOrderInsert(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnExecOrderInsert")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnExecOrderAction(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnExecOrderAction")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnForQuoteInsert(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnForQuoteInsert")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnQuote(dict data)
{
	try
	{
		this->get_override("onRtnQuote")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnQuoteInsert(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnQuoteInsert")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnQuoteAction(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnQuoteAction")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnForQuoteRsp(dict data)
{
	try
	{
		this->get_override("onRtnForQuoteRsp")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnCFMMCTradingAccountToken(dict data)
{
	try
	{
		this->get_override("onRtnCFMMCTradingAccountToken")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnBatchOrderAction(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnBatchOrderAction")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnCombAction(dict data)
{
	try
	{
		this->get_override("onRtnCombAction")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnCombActionInsert(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnCombActionInsert")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryContractBank(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryContractBank")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryParkedOrder(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryParkedOrder")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryParkedOrderAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryParkedOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTradingNotice(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTradingNotice")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryBrokerTradingParams(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryBrokerTradingParams")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryBrokerTradingAlgos(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryBrokerTradingAlgos")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQueryCFMMCTradingAccountToken(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQueryCFMMCTradingAccountToken")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFromBankToFutureByBank(dict data)
{
	try
	{
		this->get_override("onRtnFromBankToFutureByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFromFutureToBankByBank(dict data)
{
	try
	{
		this->get_override("onRtnFromFutureToBankByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnRepealFromBankToFutureByBank(dict data)
{
	try
	{
		this->get_override("onRtnRepealFromBankToFutureByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnRepealFromFutureToBankByBank(dict data)
{
	try
	{
		this->get_override("onRtnRepealFromFutureToBankByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFromBankToFutureByFuture(dict data)
{
	try
	{
		this->get_override("onRtnFromBankToFutureByFuture")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFromFutureToBankByFuture(dict data)
{
	try
	{
		this->get_override("onRtnFromFutureToBankByFuture")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnRepealFromBankToFutureByFutureManual(dict data)
{
	try
	{
		this->get_override("onRtnRepealFromBankToFutureByFutureManual")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnRepealFromFutureToBankByFutureManual(dict data)
{
	try
	{
		this->get_override("onRtnRepealFromFutureToBankByFutureManual")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnQueryBankBalanceByFuture(dict data)
{
	try
	{
		this->get_override("onRtnQueryBankBalanceByFuture")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnBankToFutureByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnBankToFutureByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnFutureToBankByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnFutureToBankByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnRepealBankToFutureByFutureManual(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnRepealBankToFutureByFutureManual")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnRepealFutureToBankByFutureManual(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnRepealFutureToBankByFutureManual")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnQueryBankBalanceByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnRepealFromBankToFutureByFuture(dict data)
{
	try
	{
		this->get_override("onRtnRepealFromBankToFutureByFuture")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnRepealFromFutureToBankByFuture(dict data)
{
	try
	{
		this->get_override("onRtnRepealFromFutureToBankByFuture")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspFromBankToFutureByFuture")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspFromFutureToBankByFuture")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQueryBankAccountMoneyByFuture")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnOpenAccountByBank(dict data)
{
	try
	{
		this->get_override("onRtnOpenAccountByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnCancelAccountByBank(dict data)
{
	try
	{
		this->get_override("onRtnCancelAccountByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnChangeAccountByBank(dict data)
{
	try
	{
		this->get_override("onRtnChangeAccountByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

