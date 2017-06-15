


virtual void onRspError(dict error, int id, bool last) {};

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspSubL2MarketData(dict data, dict error, int id, bool last) {};

virtual void onRspUnSubL2MarketData(dict data, dict error, int id, bool last) {};

virtual void onRspSubL2Index(dict data, dict error, int id, bool last) {};

virtual void onRspUnSubL2Index(dict data, dict error, int id, bool last) {};

virtual void onRtnL2MarketData(dict data) {};

virtual void onRtnL2Index(dict data) {};

virtual void onRspSubL2OrderAndTrade(dict data, dict error, int id, bool last) {};

virtual void onRspUnSubL2OrderAndTrade(dict data, dict error, int id, bool last) {};

virtual void onRtnL2Order(dict data) {};

virtual void onRtnL2Trade(dict data) {};


