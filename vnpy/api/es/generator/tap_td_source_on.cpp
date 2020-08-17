void onConnect(string userNo) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onConnect, userNo);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspLogin(string userNo, int nErrorCode, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspLogin, userNo, nErrorCode, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnContactInfo(string userNo, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnContactInfo, userNo, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspRequestVertificateCode(string userNo, unsigned int nSessionID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspRequestVertificateCode, userNo, nSessionID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnErrorMsg(string userNo, string OnRtnErrorMsg) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnErrorMsg, userNo, ErrorMsg);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onAPIReady(string userNo) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onAPIReady, userNo);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDisconnect(string userNo, int nReasonCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onDisconnect, userNo, nReasonCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubmitUserLoginInfo(string userNo, unsigned int nSessionID, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSubmitUserLoginInfo, userNo, nSessionID, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspChangePassword(string userNo, unsigned int nSessionID, int nErrorCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspChangePassword, userNo, nSessionID, nErrorCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSetReservedInfo(string userNo, unsigned int nSessionID, int nErrorCode, string OnRspSetReservedInfo) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSetReservedInfo, userNo, nSessionID, nErrorCode, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnContract(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnContract, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFund(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnFund, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOrder(string userNo, unsigned int nRequestID, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, userNo, nRequestID, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrderProcess(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryOrderProcess, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFill(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnFill, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPosition(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPosition, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnClose(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnClose, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPositionProfit(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPositionProfit, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryDeepQuote(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryDeepQuote, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnExchangeStateInfo(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnExchangeStateInfo, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnReqQuoteNotice(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnReqQuoteNotice, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAccountRentInfo(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAccountRentInfo, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspTradeMessage(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspTradeMessage, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnTradeMessage(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnTradeMessage, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisOrder(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrder, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisOrderProcess(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrderProcess, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisFill(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisFill, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisPosition(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisPosition, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisDelivery(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisDelivery, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountCashAdjust(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountCashAdjust, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryBill(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryBill, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAccountFeeRent(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAccountFeeRent, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAccountMarginRent(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAccountMarginRent, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAddMobileDevice(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAddMobileDevice, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryManageInfoForEStar(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryManageInfoForEStar, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQrySystemParameter(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQrySystemParameter, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradeCenterFrontAddress(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTradeCenterFrontAddress, userNo, nRequestID, nErrorCode, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCommodityInfo(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnCommodityInfo, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnCurrencyInfo(string userNo, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnCurrencyInfo, userNo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

