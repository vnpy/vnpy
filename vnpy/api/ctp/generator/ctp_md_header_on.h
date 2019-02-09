virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onRspUserLogin(dict data, dict error, int reqid, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int reqid, bool last) {};

virtual void onRspError(dict error, int reqid, bool last) {};

virtual void onRspSubMarketData(dict data, dict error, int reqid, bool last) {};

virtual void onRspUnSubMarketData(dict data, dict error, int reqid, bool last) {};

virtual void onRspSubForQuoteRsp(dict data, dict error, int reqid, bool last) {};

virtual void onRspUnSubForQuoteRsp(dict data, dict error, int reqid, bool last) {};

virtual void onRtnDepthMarketData(dict data) {};

virtual void onRtnForQuoteRsp(dict data) {};

