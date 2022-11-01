virtual void onFrontConnected() {};

virtual void onRspUserLogin(const dict &data, const dict &error) {};

virtual void onAnsOrderInsert(const dict &data, const dict &error) {};

virtual void onRspOrderInsert(const dict &data, const dict &error) {};

virtual void onAnsOrderAction(const dict &data, const dict &error) {};

virtual void onRspOrderAction(const dict &data, const dict &error) {};

virtual void onOrderRtn(const dict &data) {};

virtual void onTradeRtn(const dict &data) {};

virtual void onRspTradingAccount(const dict &data) {};

virtual void onRspError(const dict &error) {};

virtual void onRspQryOrder(const dict &data, bool last) {};

virtual void onRspQryTrade(const dict &data, bool last) {};

virtual void onRspQryInvestorPosition(const dict &data, bool last) {};

virtual void onRspQryChangePwd() {};

virtual void onRspLogout(string data) {};

virtual void onRtnInstrumentStatus(const dict &data) {};

virtual void onRspTest(const dict &data) {};

virtual void onErrRtnOrderInsert(const dict &error) {};

virtual void onErrRtnOrderAction(const dict &error) {};

