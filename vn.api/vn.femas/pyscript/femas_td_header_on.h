




virtual void onRspError(dict error, int id, bool last) {};

virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

virtual void onRtnFlowMessageCancel(dict data) {};

virtual void onRtnTrade(dict data) {};

virtual void onRtnOrder(dict data) {};

virtual void onErrRtnOrderInsert(dict data, dict error) {};

virtual void onErrRtnOrderAction(dict data, dict error) {};

virtual void onRtnInstrumentStatus(dict data) {};

virtual void onRtnInvestorAccountDeposit(dict data) {};

virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

virtual void onRspQryUserInvestor(dict data, dict error, int id, bool last) {};

virtual void onRspQryTradingCode(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorAccount(dict data, dict error, int id, bool last) {};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

virtual void onRspSubscribeTopic(dict data, dict error, int id, bool last) {};

virtual void onRspQryComplianceParam(dict data, dict error, int id, bool last) {};

virtual void onRspQryTopic(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorFee(dict data, dict error, int id, bool last) {};

virtual void onRspQryInvestorMargin(dict data, dict error, int id, bool last) {};

