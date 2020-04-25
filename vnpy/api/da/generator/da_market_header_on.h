virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onRspRawData(const dict &data) {};

virtual void onRspUserLogin(const dict &error, int reqid, bool last) {};

virtual void onRspTradeDate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspBrokerData(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspMarketData(const dict &data, const dict &error, int reqid, bool last) {};

