

virtual void onRspUserLogin(dict data, dict error) {};

virtual void onRspUserLogout(dict data, dict error) {};

virtual void onRspInsertOrder(dict data, dict error) {};

virtual void onRspCancelOrder(dict data, dict error) {};

virtual void onRtnErrorMsg(dict data) {};

virtual void onRtnMatchedInfo(dict data) {};

virtual void onRtnOrder(dict data) {};

virtual void onRtnCancelOrder(dict data) {};

virtual void onRspQryOrderInfo(dict data, dict error, bool last) {};

virtual void onRspQryMatchInfo(dict data, dict error, bool last) {};

virtual void onRspQryPosition(dict data, dict error, bool last) {};

virtual void onRspCustomerCapital(dict data, dict error) {};

virtual void onRspQryExchangeInstrument(dict data, dict error, bool last) {};

virtual void onRspArbitrageInstrument(dict data, dict error) {};

virtual void onRspQrySpecifyInstrument(dict data, dict error, bool last) {};

virtual void onRspQryPositionDetail(dict data, dict error, bool last) {};

virtual void onRtnTradingNotice(dict data) {};

virtual void onRspResetPassword(dict data, dict error) {};

virtual void onRspQryTradeCode(dict data, dict error, bool last) {};

virtual void onRspBillConfirm(dict data, dict error) {};

virtual void onRspEquityComputMode(dict data, dict error) {};

virtual void onRspQryBill(dict data, dict error, bool last) {};

virtual void onRspConfirmProductInfo(dict data, dict error) {};

virtual void onRspTradingDay(dict data, dict error) {};

virtual void onRspQuoteInsert(dict data, dict error) {};

virtual void onRtnQuoteInsert(dict data) {};

virtual void onRspQuoteCancel(dict data, dict error) {};

virtual void onRtnQuoteCancel(dict data) {};

virtual void onRtnQuoteMatchedInfo(dict data) {};

virtual void onRspCancelAllOrder(dict data, dict error) {};

virtual void onRspQryQuoteNotice(dict data, dict error, bool last) {};

virtual void onRspForQuote(dict data, dict error) {};

virtual void onRtnForQuote(dict data) {};

virtual void onRspQryQuoteOrderInfo(dict data, dict error, bool last) {};

virtual void onRspQryForQuote(dict data, dict error, bool last) {};

virtual void onRspQryTransferBank(dict data, dict error, bool last) {};

virtual void onRspQryTransferSerial(dict data, dict error, bool last) {};

virtual void onRspFromBankToFutureByFuture(dict data, dict error) {};

virtual void onRspFromFutureToBankByFuture(dict data, dict error) {};

virtual void onRtnFromBankToFutureByFuture(dict data) {};

virtual void onRtnFromFutureToBankByFuture(dict data) {};

virtual void onRtnRepealFromFutureToBankByBank(dict data) {};

virtual void onRspQryExchangeStatus(dict data, dict error, bool last) {};

virtual void onRtnExchangeStatus(dict data) {};

virtual void onRspQryDepthMarketData(dict data, dict error, bool last) {};

