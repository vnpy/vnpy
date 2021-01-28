virtual void onRspLogin(int error, const dict &data) {};

virtual void onAPIReady() {};

virtual void onDisconnect(int reason) {};

virtual void onRspQryCommodity(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryContract(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspSubscribeQuote(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspUnSubscribeQuote(unsigned int session, int error, char last, const dict &data) {};

virtual void onRtnQuote(const dict &data) {};

