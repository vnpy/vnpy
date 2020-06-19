int reqUserLogin(const dict &req, int reqid);

int reqUserLogout(const dict &req, int reqid);

int unsubAllMarketData(int tickType,int exchangeID,int nRequestID);

int unsubAllTickByTick(int exchangeID,int nRequestID);

int unsubMarketData(string ppInstrumentID,int nCount,int nRequestID);

int unsubTickByTick(string ppInstrumentID,int nCount,int nRequestID);

int unsubAllOrderBook(int exchangeID,int nRequestID);

int unsubOrderBook(string ppInstrumentID,int nCount,int nRequestID);

