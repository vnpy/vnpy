virtual void onFrontConnected() {};

virtual void onFrontDisConnected() {};

virtual void onHeartBeatWarning(const dict &data) {};

virtual void onRspError(const dict &data, int reqid) {};

virtual void onRtnMarketData(const dict &data) {};

virtual void onRspUtpLogin(const dict &data, int reqid) {};

virtual void onRspUtpLogout(const dict &data, int reqid) {};

virtual void onRspSubscribe(const dict &data, int reqid) {};

virtual void onRspUnSubscribe(const dict &data, int reqid) {};

virtual void onRspQryExchange(const dict &data, int reqid) {};

virtual void onRspQryInstrument(const dict &data, int reqid) {};

