void onRspLogin(int error, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspLogin, error, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onAPIReady() override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onAPIReady);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDisconnect(int reasonCode) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDisconnect, reasonCode);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryCommodity(unsigned int session, int error, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspQryCommodity, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspQryContract(unsigned int session, int error, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspQryContract, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspSubscribeQuote(unsigned int session, int error, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspSubscribeQuote, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRspUnSubscribeQuote(unsigned int session, int error, char last, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRspUnSubscribeQuote, session, error, last, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onRtnQuote(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onRtnQuote, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

