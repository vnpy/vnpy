virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onPackageStart(int reqid, int reqid) {};

virtual void onPackageEnd(int reqid, int reqid) {};

virtual void onRspError(const dict &data, int reqid, bool last) {};

virtual void onRspUserLogin(const dict &data, const dict &data, int reqid, bool last) {};

virtual void onRspUserLogout(const dict &data, const dict &data, int reqid, bool last) {};

virtual void onRtnDepthMarketData(const dict &data) {};

virtual void onRspSubMarketData(const dict &data, const dict &data, int reqid, bool last) {};

virtual void onRspUnSubMarketData(const dict &data, const dict &data, int reqid, bool last) {};

virtual void onRspGetMarketTopic(const dict &data, const dict &data, int reqid, bool last) {};

virtual void onRspGetMarketData(const dict &data, const dict &data, int reqid, bool last) {};

