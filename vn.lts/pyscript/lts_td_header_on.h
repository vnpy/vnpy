


virtual void onRspError(dict error, int id, bool last) {};

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestor(dict data, dict error, int id, bool last) {};

virtual void onRspQryTradingCode(dict data, dict error, int id, bool last) {};

virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last) {};

virtual void onRspQryBondInterest(dict data, dict error, int id, bool last) {};

virtual void onRspQryMarketRationInfo(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last) {};

virtual void onRspQryETFInstrument(dict data, dict error, int id, bool last) {};

virtual void onRspQryETFBasket(dict data, dict error, int id, bool last) {};

virtual void onRspQryOFInstrument(dict data, dict error, int id, bool last) {};

virtual void onRspQrySFInstrument(dict data, dict error, int id, bool last) {};

virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

virtual void onRtnOrder(dict data) {};

virtual void onRtnTrade(dict data) {};

virtual void onErrRtnOrderInsert(dict data, dict error) {};

virtual void onErrRtnOrderAction(dict data, dict error) {};

virtual void onRspFundOutByLiber(dict data, dict error, int id, bool last) {};

virtual void onRtnFundOutByLiber(dict data) {};

virtual void onErrRtnFundOutByLiber(dict data, dict error) {};

virtual void onRtnFundInByBank(dict data) {};

virtual void onRspQryFundTransferSerial(dict data, dict error, int id, bool last) {};

virtual void onRspFundInterTransfer(dict data, dict error, int id, bool last) {};

virtual void onRspQryFundInterTransferSerial(dict data, dict error, int id, bool last) {};

virtual void onRtnFundInterTransferSerial(dict data) {};

virtual void onErrRtnFundInterTransfer(dict data, dict error) {};

