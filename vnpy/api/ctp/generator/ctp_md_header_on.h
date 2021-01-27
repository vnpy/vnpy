virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspError(const dict &error, int reqid, bool last) {};

virtual void onRspSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUnSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspSubForQuoteRsp(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUnSubForQuoteRsp(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnDepthMarketData(const dict &data) {};

virtual void onRtnForQuoteRsp(const dict &data) {};

