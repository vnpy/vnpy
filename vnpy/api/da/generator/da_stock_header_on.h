virtual void onFrontConnected() {};

virtual void onFrontDisconnected(int reqid) {};

virtual void onHeartBeatWarning(int reqid) {};

virtual void onRspNeedVerify(bool last, bool last) {};

virtual void onRspUserLogin(const dict &error, int reqid, bool last) {};

virtual void onRspUserLogout(const dict &error, int reqid, bool last) {};

virtual void onRspVerifyCode(const dict &error, int reqid, bool last) {};

virtual void onRspSafeVerify(const dict &error, int reqid, bool last) {};

virtual void onRspSetVerifyQA(const dict &error, int reqid, bool last) {};

virtual void onRspAccount(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQuestion(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderModify(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspOrderCancel(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnTrade(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnCapital(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRtnPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTick(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCapital(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryVersion(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryCurrency(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) {};

virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

