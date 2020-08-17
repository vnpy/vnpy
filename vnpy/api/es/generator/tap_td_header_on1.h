virtual void onConnect(string userNo) {};

virtual void onRspLogin(string userNo, int nErrorCode, const dict &data) {};

virtual void onRtnContactInfo(string userNo, int nErrorCode, char last, const dict &data) {};

virtual void onRspRequestVertificateCode(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRtnErrorMsg(string userNo, string userNo) {};

virtual void onAPIReady(string userNo) {};

virtual void onDisconnect(string userNo, int nReasonCode) {};

virtual void onRspSubmitUserLoginInfo(string userNo, unsigned int {name}, const dict &data) {};

virtual void onRspChangePassword(string userNo, unsigned int {name}, int nErrorCode) {};

virtual void onRspSetReservedInfo(string userNo, unsigned int {name}, int nErrorCode, string userNo) {};

virtual void onRtnContract(string userNo, const dict &data) {};

virtual void onRtnFund(string userNo, const dict &data) {};

virtual void onRtnOrder(string userNo, unsigned int {name}, const dict &data) {};

virtual void onRspQryOrderProcess(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRtnFill(string userNo, const dict &data) {};

virtual void onRtnPosition(string userNo, const dict &data) {};

virtual void onRtnClose(string userNo, const dict &data) {};

virtual void onRtnPositionProfit(string userNo, const dict &data) {};

virtual void onRspQryDeepQuote(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRtnExchangeStateInfo(string userNo, const dict &data) {};

virtual void onRtnReqQuoteNotice(string userNo, const dict &data) {};

virtual void onRspAccountRentInfo(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspTradeMessage(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRtnTradeMessage(string userNo, const dict &data) {};

virtual void onRspQryHisOrder(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryHisOrderProcess(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryHisFill(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryHisPosition(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryHisDelivery(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryAccountCashAdjust(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryBill(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspAccountFeeRent(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspAccountMarginRent(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspAddMobileDevice(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryManageInfoForEStar(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQrySystemParameter(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRspQryTradeCenterFrontAddress(string userNo, unsigned int {name}, int nErrorCode, char last, const dict &data) {};

virtual void onRtnCommodityInfo(string userNo, const dict &data) {};

virtual void onRtnCurrencyInfo(string userNo, const dict &data) {};

