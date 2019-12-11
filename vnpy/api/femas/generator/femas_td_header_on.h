virtual void onFrontConnected() {};

virtual void onQryFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onQryFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onPackageStart(int reqid, int reqid) {};

virtual void onPackageEnd(int reqid, int reqid) {};

virtual void onRspError(const dict &error, int reqid, bool last) {};

virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQuoteAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspForQuote(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspMarginCombAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspUserDeposit(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnFlowMessageCancel(const dict &data) {};

virtual void onRtnTrade(const dict &data) {};

virtual void onRtnOrder(const dict &data) {};

virtual void onErrRtnOrderInsert(const dict &data, const dict &error) {};

virtual void onErrRtnOrderAction(const dict &data, const dict &error) {};

virtual void onRtnInstrumentStatus(const dict &data) {};

virtual void onRtnInvestorAccountDeposit(const dict &data) {};

virtual void onRtnQuote(const dict &data) {};

virtual void onErrRtnQuoteInsert(const dict &data, const dict &error) {};

virtual void onErrRtnQuoteAction(const dict &data, const dict &error) {};

virtual void onRtnForQuote(const dict &data) {};

virtual void onRtnMarginCombinationLeg(const dict &data) {};

virtual void onRtnMarginCombAction(const dict &data) {};

virtual void onRtnUserDeposit(const dict &data) {};

virtual void onRspQueryUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryUserInvestor(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTradingCode(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorAccount(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryComplianceParam(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorFee(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorMargin(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorCombPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInvestorLegPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrumentGroup(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryClientMarginCombType(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspExecOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspExecOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnExecOrder(const dict &data) {};

virtual void onErrRtnExecOrderInsert(const dict &data, const dict &error) {};

virtual void onErrRtnExecOrderAction(const dict &data, const dict &error) {};

virtual void onRtnTransferMoney(const dict &data) {};

virtual void onRspQrySystemTime(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryMarginPrefParam(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspDSUserCertification(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspDSProxySubmitInfo(const dict &error, int reqid, bool last) {};

