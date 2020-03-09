void onConnect() override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onConnect);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspLogin(int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspLogin, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnContactInfo(int error, bool last, string ContactInfo) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnContactInfo, error, last, ContactInfo);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspRequestVertificateCode(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspRequestVertificateCode, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onExpriationDate(string date, int days) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onExpriationDate, date, days);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onAPIReady(int error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onAPIReady, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDisconnect(int reasonCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onDisconnect, reasonCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspChangePassword(int session, int error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspChangePassword, session, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspAuthPassword(int session, int error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspAuthPassword, session, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradingDate(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTradingDate, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSetReservedInfo(int session, int error, string info) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspSetReservedInfo, session, error, info);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccount(int session, int session, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccount, session, session, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryFund(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryFund, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFund(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnFund, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryExchange(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryExchange, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCommodity(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCommodity, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryContract(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryContract, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnContract(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnContract, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderAction(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnOrder(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrder(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryOrderProcess(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryOrderProcess, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryFill(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryFill, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnFill(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnFill, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPosition(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryPosition, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPosition(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPosition, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryPositionSummary(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryPositionSummary, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPositionSummary(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPositionSummary, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnPositionProfit(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnPositionProfit, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCurrency(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryCurrency, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryTradeMessage(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryTradeMessage, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnTradeMessage(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRtnTradeMessage, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisOrder(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrder, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisOrderProcess(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrderProcess, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisMatch(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisMatch, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisPosition(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisPosition, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryHisDelivery(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryHisDelivery, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountCashAdjust(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountCashAdjust, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryBill(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryBill, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountFeeRent(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountFeeRent, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryAccountMarginRent(int session, int error, bool last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountMarginRent, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspHKMarketOrderInsert(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspHKMarketOrderInsert, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspHKMarketOrderDelete(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspHKMarketOrderDelete, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onHKMarketQuoteNotice(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onHKMarketQuoteNotice, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalRemove(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalRemove, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalInput(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalInput, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalModify(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalModify, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspOrderLocalTransfer(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspOrderLocalTransfer, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFillLocalInput(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFillLocalInput, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspFillLocalRemove(int session, int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onRspFillLocalRemove, session, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

