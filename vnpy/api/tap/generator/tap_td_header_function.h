int qryTradingDate(unsigned int session);

int qryAccount(unsigned int session, const dict &data);

int qryFund(unsigned int session, const dict &data);

int qryExchange(unsigned int session);

int qryCommodity(unsigned int session);

int qryContract(unsigned int session, const dict &data);

int qryOrder(unsigned int session, const dict &data);

int qryOrderProcess(unsigned int session, const dict &data);

int qryFill(unsigned int session, const dict &data);

int qryPosition(unsigned int session, const dict &data);

int qryPositionSummary(unsigned int session, const dict &data);

int qryCurrency(unsigned int session);

int qryAccountCashAdjust(unsigned int session, const dict &data);

int qryTradeMessage(unsigned int session, const dict &data);

int qryBill(unsigned int session, const dict &data);

int qryHisOrder(unsigned int session, const dict &data);

int qryHisOrderProcess(unsigned int session, const dict &data);

int qryHisMatch(unsigned int session, const dict &data);

int qryHisPosition(unsigned int session, const dict &data);

int qryHisDelivery(unsigned int session, const dict &data);

int qryAccountFeeRent(unsigned int session, const dict &data);

int qryAccountMarginRent(unsigned int session, const dict &data);

