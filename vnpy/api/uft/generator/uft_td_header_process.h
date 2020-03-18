void processFrontConnected(Task *task);

void processFrontDisconnected(Task *task);

void processRspAuthenticate(Task *task);

void processRspUserLogin(Task *task);

void processRspUserPasswordUpdate(Task *task);

void processRspErrorOrderInsert(Task *task);

void processRspOrderAction(Task *task);

void processRspErrorExerciseOrderInsert(Task *task);

void processRspExerciseOrderAction(Task *task);

void processRspErrorLockInsert(Task *task);

void processRspForQuoteInsert(Task *task);

void processRspErrorCombActionInsert(Task *task);

void processRspQueryMaxOrderVolume(Task *task);

void processRspQueryLockVolume(Task *task);

void processRspQueryExerciseVolume(Task *task);

void processRspQryPosition(Task *task);

void processRspQryTradingAccount(Task *task);

void processRspQryOrder(Task *task);

void processRspQryTrade(Task *task);

void processRspQryExercise(Task *task);

void processRspQryLock(Task *task);

void processRspQryCombAction(Task *task);

void processRspQryPositionCombineDetail(Task *task);

void processRspQryInstrument(Task *task);

void processRspQryCoveredShort(Task *task);

void processRspQryExerciseAssign(Task *task);

void processRspTransfer(Task *task);

void processRspQryTransfer(Task *task);

void processRspQueryBankBalance(Task *task);

void processRspQueryBankAccount(Task *task);

void processRspQueryBillContent(Task *task);

void processRspBillConfirm(Task *task);

void processRspQryMargin(Task *task);

void processRspQryCommission(Task *task);

void processRspQryPositionDetail(Task *task);

void processRspQryExchangeRate(Task *task);

void processRspQrySysConfig(Task *task);

void processRspQryDepthMarketData(Task *task);

void processRtnTrade(Task *task);

void processRtnOrder(Task *task);

void processRtnExercise(Task *task);

void processRtnCombAction(Task *task);

void processRtnLock(Task *task);

