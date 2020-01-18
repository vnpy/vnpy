virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onRspAuthenticate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspErrorOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspErrorExerciseOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspExerciseOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspErrorLockInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspForQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspErrorCombActionInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryMaxOrderVolume(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryLockVolume(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryExerciseVolume(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExercise(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryLock(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCombAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryPositionCombineDetail(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCoveredShort(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExerciseAssign(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspTransfer(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTransfer(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryBankBalance(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryBankAccount(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQueryBillContent(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspBillConfirm(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryMargin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCommission(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryPositionDetail(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExchangeRate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQrySysConfig(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryDepthMarketData(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnTrade(const dict &data) {};

virtual void onRtnOrder(const dict &data) {};

virtual void onRtnExercise(const dict &data) {};

virtual void onRtnCombAction(const dict &data) {};

virtual void onRtnLock(const dict &data) {};

