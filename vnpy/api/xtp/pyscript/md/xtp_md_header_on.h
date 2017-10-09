virtual void onDisconnected() {};

virtual void onError(dict data) {};

virtual void onSubMarketData(dict data, dict error, bool last) {};

virtual void onUnSubMarketData(dict data, dict error, bool last) {};

virtual void onMarketData(dict data) {};

virtual void onSubOrderBook(dict data, dict error, bool last) {};

virtual void onUnSubOrderBook(dict data, dict error, bool last) {};

virtual void onOrderBook(dict data) {};

virtual void onQueryAllTickers(dict data, dict error, bool last) {};

