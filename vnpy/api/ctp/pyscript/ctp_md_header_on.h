


virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspError(dict error, int id, bool last) {};

virtual void onRspSubMarketData(dict data, dict error, int id, bool last) {};

virtual void onRspUnSubMarketData(dict data, dict error, int id, bool last) {};

virtual void onRspSubForQuoteRsp(dict data, dict error, int id, bool last) {};

virtual void onRspUnSubForQuoteRsp(dict data, dict error, int id, bool last) {};

virtual void onRtnDepthMarketData(dict data) {};

virtual void onRtnForQuoteRsp(dict data) {};

