virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onRtnNotice(const dict &data) {};

virtual void onRspError(const dict &error) {};

virtual void onRspStockUserLogin(const dict &data, const dict &error) {};

virtual void onRspStockUserLogout(const dict &data, const dict &error) {};

virtual void onRspSOPUserLogin(const dict &data, const dict &error) {};

virtual void onRspSOPUserLogout(const dict &data, const dict &error) {};

virtual void onRspFASLUserLogin(const dict &data, const dict &error) {};

virtual void onRspFASLUserLogout(const dict &data, const dict &error) {};

virtual void onRspStockSubMarketData(const dict &data, const dict &error) {};

virtual void onRspStockUnSubMarketData(const dict &data, const dict &error) {};

virtual void onRspSOPSubMarketData(const dict &data, const dict &error) {};

virtual void onRspSOPUnSubMarketData(const dict &data, const dict &error) {};

virtual void onStockMarketData(const dict &data) {};

virtual void onSOPMarketData(const dict &data) {};

virtual void onRspStockAvailableQuot(const dict &data, const dict &error, bool last) {};

virtual void onRspSopAvailableQuot(const dict &data, const dict &error, bool last) {};

virtual void onRspUserMDPasswordUpdate(const dict &data, const dict &error) {};

