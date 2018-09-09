




virtual void onRspError(dict error, int id, bool last) {};

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRtnQmdInstrumentStatu(dict data) {};

virtual void onRspSubscribeTopic(dict data, dict error, int id, bool last) {};

virtual void onRspQryTopic(dict data, dict error, int id, bool last) {};

virtual void onRtnDepthMarketData(dict data) {};

virtual void onRspSubMarketData(dict data, dict error, int id, bool last) {};

virtual void onRspUnSubMarketData(dict data, dict error, int id, bool last) {};

virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last) {};

