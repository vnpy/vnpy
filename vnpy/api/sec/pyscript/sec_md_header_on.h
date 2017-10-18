virtual void onFrontDisconnected(){};

virtual void onRtnNotice(dict data){};

virtual void onRspError(dict error){};

virtual void onRspStockUserLogin(dict data, dict error){};

virtual void onRspStockUserLogout(dict data, dict error){};

virtual void onRspSOPUserLogin(dict data, dict error){};

virtual void onRspSOPUserLogout(dict data, dict error){};

virtual void onRspFASLUserLogin(dict data, dict error){};

virtual void onRspFASLUserLogout(dict data, dict error){};

virtual void onRspStockSubMarketData(dict data, dict error){};

virtual void onRspStockUnSubMarketData(dict data, dict error){};

virtual void onRspSOPSubMarketData(dict data, dict error){};

virtual void onRspSOPUnSubMarketData(dict data, dict error){};

virtual void onStockMarketData(dict data){};

virtual void onSOPMarketData(dict data){};

virtual void onRspStockAvailableQuot(dict data, dict error, bool flag){};

virtual void onRspSopAvailableQuot(dict data, dict error, bool flag){};

virtual void onRspUserMDPasswordUpdate(dict data, dict error){};

