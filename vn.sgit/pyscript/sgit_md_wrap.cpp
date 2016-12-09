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

virtual void onRspUnSubMarketData(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUnSubMarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSubForQuoteRsp(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspSubForQuoteRsp")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUnSubForQuoteRsp(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspUnSubForQuoteRsp")(data, error, id, last);
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

virtual void onRtnDeferDeliveryQuot(dict data)
{
	try
	{
		this->get_override("onRtnDeferDeliveryQuot")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

