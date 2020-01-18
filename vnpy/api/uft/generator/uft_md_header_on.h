virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onRspDepthMarketDataSubscribe(const dict &error, int reqid, bool last) {};

virtual void onRspDepthMarketDataCancel(const dict &error, int reqid, bool last) {};

virtual void onRtnDepthMarketData(const dict &data) {};

