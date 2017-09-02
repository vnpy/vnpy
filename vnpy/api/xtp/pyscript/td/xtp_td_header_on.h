virtual void onDisconnected() {};

virtual void onError(dict data) {};

virtual void onOrderEvent(dict data, dict error) {};

virtual void onTradeEvent(dict data) {};

virtual void onCancelOrderError(dict data, dict error) {};

virtual void onQueryOrder(dict data, dict error, int reqid, bool last) {};

virtual void onQueryTrade(dict data, dict error, int reqid, bool last) {};

virtual void onQueryPosition(dict data, dict error, int reqid, bool last) {};

virtual void onQueryAsset(dict data, dict error, int reqid, bool last) {};

