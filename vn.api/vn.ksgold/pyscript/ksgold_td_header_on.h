

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};


virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

virtual void onRtnDepthMarketData(dict data) {};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onErrRtnOrderInsert(dict data, dict error) {};

virtual void onRtnOrder(dict data) {};


virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

virtual void onErrRtnOrderAction(dict data, dict error) {};

virtual void onRtnTrade(dict data) {};

virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

virtual void onRspQryClientStorage(dict data, dict error, int id, bool last) {};

virtual void onRspSubMarketData(dict data, dict error, int id, bool last) {};

