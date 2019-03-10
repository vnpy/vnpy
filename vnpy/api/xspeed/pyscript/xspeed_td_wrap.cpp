virtual void onRspUserLogin(dict data, dict error)
{
	try
	{
		this->get_override("onRspUserLogin")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserLogout(dict data, dict error)
{
	try
	{
		this->get_override("onRspUserLogout")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspInsertOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspInsertOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspCancelOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspCancelOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnErrorMsg(dict data)
{
	try
	{
		this->get_override("onRtnErrorMsg")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnMatchedInfo(dict data)
{
	try
	{
		this->get_override("onRtnMatchedInfo")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnOrder(dict data)
{
	try
	{
		this->get_override("onRtnOrder")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnCancelOrder(dict data)
{
	try
	{
		this->get_override("onRtnCancelOrder")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryOrderInfo(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryOrderInfo")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryMatchInfo(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryMatchInfo")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryPosition(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryPosition")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspCustomerCapital(dict data, dict error)
{
	try
	{
		this->get_override("onRspCustomerCapital")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchangeInstrument(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryExchangeInstrument")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspArbitrageInstrument(dict data, dict error)
{
	try
	{
		this->get_override("onRspArbitrageInstrument")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQrySpecifyInstrument(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQrySpecifyInstrument")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryPositionDetail(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryPositionDetail")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnTradingNotice(dict data)
{
	try
	{
		this->get_override("onRtnTradingNotice")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspResetPassword(dict data, dict error)
{
	try
	{
		this->get_override("onRspResetPassword")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTradeCode(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryTradeCode")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspBillConfirm(dict data, dict error)
{
	try
	{
		this->get_override("onRspBillConfirm")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspEquityComputMode(dict data, dict error)
{
	try
	{
		this->get_override("onRspEquityComputMode")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryBill(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryBill")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspConfirmProductInfo(dict data, dict error)
{
	try
	{
		this->get_override("onRspConfirmProductInfo")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspTradingDay(dict data, dict error)
{
	try
	{
		this->get_override("onRspTradingDay")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQuoteInsert(dict data, dict error)
{
	try
	{
		this->get_override("onRspQuoteInsert")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnQuoteInsert(dict data)
{
	try
	{
		this->get_override("onRtnQuoteInsert")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQuoteCancel(dict data, dict error)
{
	try
	{
		this->get_override("onRspQuoteCancel")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnQuoteCancel(dict data)
{
	try
	{
		this->get_override("onRtnQuoteCancel")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnQuoteMatchedInfo(dict data)
{
	try
	{
		this->get_override("onRtnQuoteMatchedInfo")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspCancelAllOrder(dict data, dict error)
{
	try
	{
		this->get_override("onRspCancelAllOrder")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryQuoteNotice(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryQuoteNotice")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspForQuote(dict data, dict error)
{
	try
	{
		this->get_override("onRspForQuote")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnForQuote(dict data)
{
	try
	{
		this->get_override("onRtnForQuote")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryQuoteOrderInfo(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryQuoteOrderInfo")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryForQuote(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryForQuote")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTransferBank(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryTransferBank")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTransferSerial(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryTransferSerial")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFromBankToFutureByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onRspFromBankToFutureByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFromFutureToBankByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onRspFromFutureToBankByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFromBankToFutureByFuture(dict data)
{
	try
	{
		this->get_override("onRtnFromBankToFutureByFuture")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFromFutureToBankByFuture(dict data)
{
	try
	{
		this->get_override("onRtnFromFutureToBankByFuture")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnRepealFromFutureToBankByBank(dict data)
{
	try
	{
		this->get_override("onRtnRepealFromFutureToBankByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchangeStatus(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryExchangeStatus")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnExchangeStatus(dict data)
{
	try
	{
		this->get_override("onRtnExchangeStatus")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryDepthMarketData(dict data, dict error, bool last)
{
	try
	{
		this->get_override("onRspQryDepthMarketData")(data, error, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

