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

virtual void onRspQryTradingCode(dict data, dict error, int id, bool last)
{
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
	try
	{
		this->get_override("onRspQryTradingAccount")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryBondInterest(dict data, dict error, int id, bool last)
{
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
	try
	{
		this->get_override("onRspQrySFInstrument")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryInstrumentUnitMargin(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryInstrumentUnitMargin")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryPreDelivInfo(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryPreDelivInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryCreditStockAssignInfo(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryCreditStockAssignInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryCreditCashAssignInfo(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryCreditCashAssignInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryConversionRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryConversionRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryHisCreditDebtInfo(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryHisCreditDebtInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryMarketDataStaticInfo(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryMarketDataStaticInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryExpireRepurchInfo(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryExpireRepurchInfo")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryBondPledgeRate(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryBondPledgeRate")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryPledgeBond(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryPledgeBond")(data, error, id, last);
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

virtual void onRspQryFundTransferSerial(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryFundTransferSerial")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

virtual void onRspQryFundInterTransferSerial(dict data, dict error, int id, bool last)
{
	try
	{
		this->get_override("onRspQryFundInterTransferSerial")(data, error, id, last);
	}
	catch (error_already_set const &)
	{
		PyErr_Print();
	}
};

