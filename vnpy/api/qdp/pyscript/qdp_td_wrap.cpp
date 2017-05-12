virtual void onRspError(dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspError")(error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserLogin(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUserLogin")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserLogout(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUserLogout")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUserPasswordUpdate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspOrderInsert")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspOrderAction(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspFromBankToFutureByFuture")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspFromFutureToBankByFuture")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFlowMessageCancel(dict data)
{
	try
	{
		this->get_override("onRtnFlowMessageCancel")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnTrade(dict data)
{
	try
	{
		this->get_override("onRtnTrade")(data);
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

virtual void onErrRtnOrderInsert(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnOrderInsert")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnOrderAction(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnOrderAction")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnInstrumentStatus(dict data)
{
	try
	{
		this->get_override("onRtnInstrumentStatus")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnInvestorAccountDeposit(dict data)
{
	try
	{
		this->get_override("onRtnInvestorAccountDeposit")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnMessageNotify(dict data)
{
	try
	{
		this->get_override("onRtnMessageNotify")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnQueryBankBalanceByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnBankToFutureByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnBankToFutureByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnFutureToBankByFuture(dict data, dict error)
{
	try
	{
		this->get_override("onErrRtnFutureToBankByFuture")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnQueryBankBalanceByFuture(dict data)
{
	try
	{
		this->get_override("onRtnQueryBankBalanceByFuture")(data);
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

virtual void onRtnSGEDeferRate(dict data)
{
	try
	{
		this->get_override("onRtnSGEDeferRate")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryOrder(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryOrder")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTrade(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTrade")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryUserInvestor(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryUserInvestor")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorAccount(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorAccount")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInstrument")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchange(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExchange")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorPosition")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSubscribeTopic(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspSubscribeTopic")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTopic(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTopic")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorFee(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorFee")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorMargin(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorMargin")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchangeDiffTime(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExchangeDiffTime")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryContractBank(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryContractBank")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQueryBankAccountMoneyByFuture")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTransferSerial")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQrySGEDeferRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQrySGEDeferRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryMarketData(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryMarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

