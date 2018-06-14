virtual void onFrontDisconnected(){};
{
	try
	{
		this->get_override("onFrontDisconnected")();
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRtnNotice(dict data){};
{
	try
	{
		this->get_override("onRtnNotice")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspError(dict error){};
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

virtual void onRspStockUserLogin(dict data, dict error){};
{
	try
	{
		this->get_override("onRspStockUserLogin")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockUserLogout(dict data, dict error){};
{
	try
	{
		this->get_override("onRspStockUserLogout")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPUserLogin(dict data, dict error){};
{
	try
	{
		this->get_override("onRspSOPUserLogin")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPUserLogout(dict data, dict error){};
{
	try
	{
		this->get_override("onRspSOPUserLogout")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLUserLogin(dict data, dict error){};
{
	try
	{
		this->get_override("onRspFASLUserLogin")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspFASLUserLogout(dict data, dict error){};
{
	try
	{
		this->get_override("onRspFASLUserLogout")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockSubMarketData(dict data, dict error){};
{
	try
	{
		this->get_override("onRspStockSubMarketData")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockUnSubMarketData(dict data, dict error){};
{
	try
	{
		this->get_override("onRspStockUnSubMarketData")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPSubMarketData(dict data, dict error){};
{
	try
	{
		this->get_override("onRspSOPSubMarketData")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSOPUnSubMarketData(dict data, dict error){};
{
	try
	{
		this->get_override("onRspSOPUnSubMarketData")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onStockMarketData(dict data){};
{
	try
	{
		this->get_override("onStockMarketData")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onSOPMarketData(dict data){};
{
	try
	{
		this->get_override("onSOPMarketData")(data);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspStockAvailableQuot(dict data, dict error, bool flag){};
{
	try
	{
		this->get_override("onRspStockAvailableQuot")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspSopAvailableQuot(dict data, dict error, bool flag){};
{
	try
	{
		this->get_override("onRspSopAvailableQuot")(data, error, flag);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspUserMDPasswordUpdate(dict data, dict error){};
{
	try
	{
		this->get_override("onRspUserMDPasswordUpdate")(data, error);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

