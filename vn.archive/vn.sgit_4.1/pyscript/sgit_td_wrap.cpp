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

virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryTradingAccount")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInvestor(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestor")(data, error, id, last);
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

virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInvestorPositionDetail")(data, error, id, last);
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

