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

virtual void onRspError(dict error)
{
	try
	{
		this->get_override("onRspError")(error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSubMarketData(dict data, dict error)
{
	try
	{
		this->get_override("onRspSubMarketData")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUnSubMarketData(dict data, dict error)
{
	try
	{
		this->get_override("onRspUnSubMarketData")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSubForQuoteRsp(dict data, dict error)
{
	try
	{
		this->get_override("onRspSubForQuoteRsp")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUnSubForQuoteRsp(dict data, dict error)
{
	try
	{
		this->get_override("onRspUnSubForQuoteRsp")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnForQuoteRsp(dict data)
{
	try
	{
		this->get_override("onRtnForQuoteRsp")(data);
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

