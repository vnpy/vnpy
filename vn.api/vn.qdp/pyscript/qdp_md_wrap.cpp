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

virtual void onRtnQmdInstrumentStatu(dict data)
{
	try
	{
		this->get_override("onRtnQmdInstrumentStatu")(data);
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

virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryDepthMarketData")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

