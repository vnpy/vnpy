virtual void onDisconnected(int reqid) {};

virtual void onError(const dict &error) {};

virtual void onSubMarketData(const dict &data, const dict &error, bool last) {};

virtual void onUnSubMarketData(const dict &data, const dict &error, bool last) {};

virtual void onDepthMarketData(const dict &data) {};

virtual void onSubOrderBook(const dict &data, const dict &error, bool last) {};

virtual void onUnSubOrderBook(const dict &data, const dict &error, bool last) {};

virtual void onOrderBook() {};

virtual void onSubTickByTick(const dict &data, const dict &error, bool last) {};

virtual void onUnSubTickByTick(const dict &data, const dict &error, bool last) {};

virtual void onTickByTick() {};

virtual void onSubscribeAllMarketData(int extra, const dict &error) {};

virtual void onUnSubscribeAllMarketData(int extra, const dict &error) {};

virtual void onSubscribeAllOrderBook(int extra, const dict &error) {};

virtual void onUnSubscribeAllOrderBook(int extra, const dict &error) {};

virtual void onSubscribeAllTickByTick(int extra, const dict &error) {};

virtual void onUnSubscribeAllTickByTick(int extra, const dict &error) {};

virtual void onQueryAllTickers(const dict &data, const dict &error, bool last) {};

virtual void onQueryTickersPriceInfo(const dict &data, const dict &error, bool last) {};

virtual void onSubscribeAllOptionMarketData(int extra, const dict &error) {};

virtual void onUnSubscribeAllOptionMarketData(int extra, const dict &error) {};

virtual void onSubscribeAllOptionOrderBook(int extra, const dict &error) {};

virtual void onUnSubscribeAllOptionOrderBook(int extra, const dict &error) {};

virtual void onSubscribeAllOptionTickByTick(int extra, const dict &error) {};

virtual void onUnSubscribeAllOptionTickByTick(int extra, const dict &error) {};

