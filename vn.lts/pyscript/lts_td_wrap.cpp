virtual void onRspError(dict error, int id, bool last)
{
	 PyLock lock;

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
	 PyLock lock;

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
	 PyLock lock;

	try
	{
		this->get_override("onRspUserLogout")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspOrderInsert(dict data, dict error, int id, bool last)
{
	 PyLock lock;

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
	 PyLock lock;

	try
	{
		this->get_override("onRspOrderAction")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspUserPasswordUpdate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspTradingAccountPasswordUpdate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExchange(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryExchange")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInstrument(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryInstrument")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestor(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryInvestor")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTradingCode(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryTradingCode")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryTradingAccount")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryDepthMarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryBondInterest(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryBondInterest")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryMarketRationInfo(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryMarketRationInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryInstrumentCommissionRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryETFInstrument(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryETFInstrument")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryETFBasket(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryETFBasket")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryOFInstrument(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryOFInstrument")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQrySFInstrument(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQrySFInstrument")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryOrder(dict data, dict error, int id, bool last)
{
	 PyLock lock;

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
	 PyLock lock;

	try
	{
		this->get_override("onRspQryTrade")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryInvestorPosition")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnOrder(dict data)
{
	 PyLock lock;

	try
	{
		this->get_override("onRtnOrder")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnTrade(dict data)
{
	 PyLock lock;

	try
	{
		this->get_override("onRtnTrade")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnOrderInsert(dict data, dict error)
{
	 PyLock lock;

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
	 PyLock lock;

	try
	{
		this->get_override("onErrRtnOrderAction")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFundOutByLiber(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspFundOutByLiber")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFundOutByLiber(dict data)
{
	 PyLock lock;

	try
	{
		this->get_override("onRtnFundOutByLiber")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnFundOutByLiber(dict data, dict error)
{
	 PyLock lock;

	try
	{
		this->get_override("onErrRtnFundOutByLiber")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFundInByBank(dict data)
{
	 PyLock lock;

	try
	{
		this->get_override("onRtnFundInByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryFundTransferSerial(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryFundTransferSerial")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFundInterTransfer(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspFundInterTransfer")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryFundInterTransferSerial(dict data, dict error, int id, bool last)
{
	 PyLock lock;

	try
	{
		this->get_override("onRspQryFundInterTransferSerial")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFundInterTransferSerial(dict data)
{
	 PyLock lock;

	try
	{
		this->get_override("onRtnFundInterTransferSerial")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onErrRtnFundInterTransfer(dict data, dict error)
{
	 PyLock lock;

	try
	{
		this->get_override("onErrRtnFundInterTransfer")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

