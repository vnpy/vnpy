void release();

bool init();

void registerFront(string pszFrontAddress);

void subscribePrivateTopic(KS_TE_RESUME_TYPE reqid);

void subscribePublicTopic(KS_TE_RESUME_TYPE reqid);

void createGoldQutoApi(string pszFlowPath = " ");

int join();

int reqUserLogin(const dict &req, int reqid);

int reqUserLogout(const dict &req, int reqid);

int reqQryInstrument(const dict &req, int reqid);

int reqQryVarietyCode(const dict &req, int reqid);

int reqOrderInsert(const dict &req, int reqid);

int reqOrderAction(const dict &req, int reqid);

int reqQryInvestorPosition(const dict &req, int reqid);

int reqQryTradingAccount(const dict &req, int reqid);

int reqQryTrade(const dict &req, int reqid);

int reqQryOrder(const dict &req, int reqid);

int reqQryStorage(const dict &req, int reqid);

int reqQryCostMarginFeeRate(const dict &req, int reqid);

int reqConditionOrderInsert(const dict &req, int reqid);

int reqConditionOrderAction(const dict &req, int reqid);

int reqQryConditionOrder(const dict &req, int reqid);

int reqQryConditionOrderTrade(const dict &req, int reqid);

int reqQryClientSessionInfo(const dict &req, int reqid);

int reqQryQuotation(const dict &req, int reqid);

int reqQryInvestorPositionDetail(const dict &req, int reqid);

int reqModifyPassword(const dict &req, int reqid);

int reqQryHisCapital(const dict &req, int reqid);

int reqETFSubScription(const dict &req, int reqid);

int reqETFApplyForPurchase(const dict &req, int reqid);

int reqETFRedeem(const dict &req, int reqid);

int reqETFAccountBinding(const dict &req, int reqid);

int reqETFAccountUnbinding(const dict &req, int reqid);

int reqETFTradeDetail(const dict &req, int reqid);

int reqETFPcfDetail(const dict &req, int reqid);

int reqBOCMoneyIO(const dict &req, int reqid);

