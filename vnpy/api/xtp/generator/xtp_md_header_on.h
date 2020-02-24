virtual void onDisconnected(int reqid) {};

virtual void onError(const dict &error) {};

virtual void onSubMarketData(const dict &data, const dict &error, bool last) {};

virtual void onUnSubMarketData(const dict &data, const dict &error, bool last) {};

virtual void onDepthMarketData(const dict &data, int reqid, int reqid, int reqid, int reqid, int reqid, int reqid) {};

virtual void onSubOrderBook(const dict &data, const dict &error, bool last) {};

virtual void onUnSubOrderBook(const dict &data, const dict &error, bool last) {};

virtual void onOrderBook(const dict &data) {};

virtual void onSubTickByTick(const dict &data, const dict &error, bool last) {};

virtual void onUnSubTickByTick(const dict &data, const dict &error, bool last) {};

virtual void onTickByTick(const dict &data) {};

virtual void onSubscribeAllMarketData(int data, const dict &error) {};

virtual void onUnSubscribeAllMarketData(int data, const dict &error) {};

virtual void onSubscribeAllOrderBook(int data, const dict &error) {};

virtual void onUnSubscribeAllOrderBook(int data, const dict &error) {};

virtual void onSubscribeAllTickByTick(int data, const dict &error) {};

virtual void onUnSubscribeAllTickByTick(int data, const dict &error) {};

virtual void onQueryAllTickers(const dict &data, const dict &error, bool last) {};

virtual void onQueryTickersPriceInfo(const dict &data, const dict &error, bool last) {};

virtual void onSubscribeAllOptionMarketData(int data, const dict &error) {};

virtual void onUnSubscribeAllOptionMarketData(int data, const dict &error) {};

virtual void onSubscribeAllOptionOrderBook(int data, const dict &error) {};

virtual void onUnSubscribeAllOptionOrderBook(int data, const dict &error) {};

virtual void onSubscribeAllOptionTickByTick(int data, const dict &error) {};

virtual void onUnSubscribeAllOptionTickByTick(int data, const dict &error) {};

