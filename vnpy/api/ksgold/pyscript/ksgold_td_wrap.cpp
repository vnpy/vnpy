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

virtual void onRtnDepthMarketData(dict data)
{
	try
	{
		this->get_override("onRtnDepthMarketData")(data);
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

virtual void onRspQryClientStorage(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryClientStorage")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSubMarketData(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspSubMarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

