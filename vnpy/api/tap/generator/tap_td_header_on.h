virtual void onConnect() {};

virtual void onRspLogin(int error, const dict &data) {};

virtual void onRtnContactInfo(int error, char last, string ContactInfo) {};

virtual void onRspRequestVertificateCode(unsigned int session, int error, const dict &data) {};

virtual void onExpriationDate(string date, int days) {};

virtual void onAPIReady(int error) {};

virtual void onDisconnect(int reason) {};

virtual void onRspChangePassword(unsigned int session, int error) {};

virtual void onRspAuthPassword(unsigned int session, int error) {};

virtual void onRspQryTradingDate(unsigned int session, int error, const dict &data) {};

virtual void onRspSetReservedInfo(unsigned int session, int error, string info) {};

virtual void onRspQryAccount(unsigned int session, unsigned int session, char last, const dict &data) {};

virtual void onRspQryFund(unsigned int session, int error, char last, const dict &data) {};

virtual void onRtnFund(const dict &data) {};

virtual void onRspQryExchange(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryCommodity(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryContract(unsigned int session, int error, char last, const dict &data) {};

virtual void onRtnContract(const dict &data) {};

virtual void onRspOrderAction(unsigned int session, int error, const dict &data) {};

virtual void onRtnOrder(const dict &data) {};

virtual void onRspQryOrder(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryOrderProcess(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryFill(unsigned int session, int error, char last, const dict &data) {};

virtual void onRtnFill(const dict &data) {};

virtual void onRspQryPosition(unsigned int session, int error, char last, const dict &data) {};

virtual void onRtnPosition(const dict &data) {};

virtual void onRspQryPositionSummary(unsigned int session, int error, char last, const dict &data) {};

virtual void onRtnPositionSummary(const dict &data) {};

virtual void onRtnPositionProfit(const dict &data) {};

virtual void onRspQryCurrency(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryTradeMessage(unsigned int session, int error, char last, const dict &data) {};

virtual void onRtnTradeMessage(const dict &data) {};

virtual void onRspQryHisOrder(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryHisOrderProcess(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryHisMatch(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryHisPosition(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryHisDelivery(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryAccountCashAdjust(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryBill(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryAccountFeeRent(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspQryAccountMarginRent(unsigned int session, int error, char last, const dict &data) {};

virtual void onRspHKMarketOrderInsert(unsigned int session, int error, const dict &data) {};

virtual void onRspHKMarketOrderDelete(unsigned int session, int error, const dict &data) {};

virtual void onHKMarketQuoteNotice(const dict &data) {};

virtual void onRspOrderLocalRemove(unsigned int session, int error, const dict &data) {};

virtual void onRspOrderLocalInput(unsigned int session, int error, const dict &data) {};

virtual void onRspOrderLocalModify(unsigned int session, int error, const dict &data) {};

virtual void onRspOrderLocalTransfer(unsigned int session, int error, const dict &data) {};

virtual void onRspFillLocalInput(unsigned int session, int error, const dict &data) {};

virtual void onRspFillLocalRemove(unsigned int session, int error, const dict &data) {};

