virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onPackageStart(int reqid, int reqid) {};

virtual void onPackageEnd(int reqid, int reqid) {};

virtual void onRspSubscribeTopic(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspStockInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspStockCancel(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOptionsInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOptionsCancel(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspForQuote(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQuoteCancel(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspStockLock(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspExercise(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspExerciseCancel(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryPartAccount(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryStockOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOptionsOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryQuoteOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryStockTrade(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOptionsTrade(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTopic(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryStock(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOptions(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnOptionsOrder(const dict &data) {};

virtual void onRtnStockOrder(const dict &data) {};

virtual void onRtnQuoteOrder(const dict &data) {};

virtual void onRtnOptionsTrade(const dict &data) {};

virtual void onRtnStockTrade(const dict &data) {};

virtual void onRtnExercise(const dict &data) {};

virtual void onRspQryRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryClient(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryClientMargin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExercise(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnWithdrawDeposit(const dict &data) {};

virtual void onRspMarginCombAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnMarginCombAction(const dict &data) {};

virtual void onRspQrySseCombPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspCombExercise(const dict &data, const dict &error, int reqid, bool last) {};

