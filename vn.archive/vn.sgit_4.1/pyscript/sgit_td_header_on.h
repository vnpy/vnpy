

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestor(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

virtual void onRtnOrder(dict data) {};

virtual void onRtnTrade(dict data) {};

virtual void onRtnInstrumentStatus(dict data) {};

virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

