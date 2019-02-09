void onFrontConnected() override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onFrontConnected);
};

void onFrontDisconnected(int reqid) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onFrontDisconnected, reqid);
};

void onHeartBeatWarning(int reqid) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onHeartBeatWarning, reqid);
};

void onRspUserLogin(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRspUserLogin, data, error, reqid, last);
};

void onRspUserLogout(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRspUserLogout, data, error, reqid, last);
};

void onRspError(dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRspError, error, reqid, last);
};

void onRspSubMarketData(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRspSubMarketData, data, error, reqid, last);
};

void onRspUnSubMarketData(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRspUnSubMarketData, data, error, reqid, last);
};

void onRspSubForQuoteRsp(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRspSubForQuoteRsp, data, error, reqid, last);
};

void onRspUnSubForQuoteRsp(dict data, dict error, int reqid, bool last) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRspUnSubForQuoteRsp, data, error, reqid, last);
};

void onRtnDepthMarketData(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRtnDepthMarketData, data);
};

void onRtnForQuoteRsp(dict data) override
{
	PYBIND11_OVERLOAD_PURE(void, MdApi, onRtnForQuoteRsp, data);
};

