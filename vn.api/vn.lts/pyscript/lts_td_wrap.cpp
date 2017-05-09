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

virtual void onRspFetchAuthRandCode(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspFetchAuthRandCode")(data, error, id, last);
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

virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspTradingAccountPasswordUpdate")(data, error, id, last);
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

virtual void onRspFundOutByLiber(dict data, dict error, int id, bool last)
{
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
	try
	{
		this->get_override("onRtnFundInByBank")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFundInterTransfer(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspFundInterTransfer")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnFundInterTransferSerial(dict data)
{
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
	try
	{
		this->get_override("onErrRtnFundInterTransfer")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

