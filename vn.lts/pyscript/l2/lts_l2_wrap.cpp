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

virtual void onRspSubL2MarketData(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspSubL2MarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUnSubL2MarketData(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUnSubL2MarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSubL2Index(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspSubL2Index")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUnSubL2Index(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUnSubL2Index")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnL2MarketData(dict data)
{
	try
	{
		this->get_override("onRtnL2MarketData")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnL2Index(dict data)
{
	try
	{
		this->get_override("onRtnL2Index")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSubL2OrderAndTrade(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspSubL2OrderAndTrade")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUnSubL2OrderAndTrade(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUnSubL2OrderAndTrade")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnL2Order(dict data)
{
	try
	{
		this->get_override("onRtnL2Order")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnL2Trade(dict data)
{
	try
	{
		this->get_override("onRtnL2Trade")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

