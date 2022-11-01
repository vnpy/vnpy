virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int nReason) {};

virtual void onHeartBeatWarning(int nTimeLapse) {};

virtual void onRspError(const dict &error, int nRequestID, bool bIsLast) {};

virtual void onRspUserLogin(const dict &data, const dict &error, int nRequestID, bool bIsLast) {};

virtual void onRspUserLogout(const dict &data, const dict &error, int nRequestID, bool bIsLast) {};

virtual void onRspSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) {};

virtual void onRspUnSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) {};

virtual void onRspSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) {};

virtual void onRspUnSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) {};

virtual void onRspSubMarketData(string tickers, int count, int nRequestID, bool bIsSuccess) {};

virtual void onRspUnSubMarketData(string tickers, int count, int nRequestID, bool bIsSuccess) {};

virtual void onRspSubTickByTick(string tickers, int count, int nRequestID, bool bIsSuccess) {};

virtual void onRspUnSubTickByTick(string tickers, int count, int nRequestID, bool bIsSuccess) {};

virtual void onRtnDepthMarketData(const dict &data) {};

virtual void onRtnTickByTick(const dict &data) {};

virtual void onRtnOrderBook(const dict &data) {};

virtual void onRspSubOrderBook(string tickers, int count, int nRequestID, bool bIsSuccess) {};

virtual void onRspUnSubOrderBook(string tickers, int count, int nRequestID, bool bIsSuccess) {};

