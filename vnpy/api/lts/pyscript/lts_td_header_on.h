


virtual void onRspError(dict error, int id, bool last) {};

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspFetchAuthRandCode(dict data, dict error, int id, bool last) {};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRtnOrder(dict data) {};

virtual void onRtnTrade(dict data) {};

virtual void onErrRtnOrderInsert(dict data, dict error) {};

virtual void onErrRtnOrderAction(dict data, dict error) {};

virtual void onRspFundOutByLiber(dict data, dict error, int id, bool last) {};

virtual void onRtnFundOutByLiber(dict data) {};

virtual void onErrRtnFundOutByLiber(dict data, dict error) {};

virtual void onRtnFundInByBank(dict data) {};

virtual void onRspFundInterTransfer(dict data, dict error, int id, bool last) {};

virtual void onRtnFundInterTransferSerial(dict data) {};

virtual void onErrRtnFundInterTransfer(dict data, dict error) {};

