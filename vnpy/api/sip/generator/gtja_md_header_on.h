virtual void onLog(int level, string source, string slog) {};

virtual void onDisconnect(int chn) {};

virtual void onSubscribe(const dict &error) {};

virtual void onUnSubscribe(const dict &error) {};

virtual void onDepthMarketData(int mk_type, string code, const dict &data) {};

virtual void onMarketData(int mk_type, string code, const dict &data) {};

virtual void onIndexData(int mk_type, string code, const dict &data) {};

virtual void onOrderQueue(int mk_type, string code, const dict &data) {};

virtual void onSHTrade(string code, const dict &data) {};

virtual void onSZTrade(string code, const dict &data) {};

virtual void onSZOrder(string code, const dict &data) {};

virtual void onSHBaseInfo(string code, const dict &data) {};

virtual void onKline(int mk_type, string code, const dict &data) {};

virtual void onEtfExtData(int mk_type, string code, const dict &data) {};

