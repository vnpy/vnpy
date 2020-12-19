void onLog(int level, string source, string slog) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onLog, level, source, slog);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDisconnect(int chn) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDisconnect, chn);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribe(const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribe, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribe(const dict &error) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribe, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDepthMarketData(int mk_type, string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDepthMarketData, mk_type, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onMarketData(int mk_type, string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onMarketData, mk_type, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onIndexData(int mk_type, string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onIndexData, mk_type, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderQueue(int mk_type, string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onOrderQueue, mk_type, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSHTrade(string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSHTrade, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSZTrade(string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSZTrade, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSZOrder(string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSZOrder, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSHBaseInfo(string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSHBaseInfo, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onKline(int mk_type, string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onKline, mk_type, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onEtfExtData(int mk_type, string code, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onEtfExtData, mk_type, code, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

