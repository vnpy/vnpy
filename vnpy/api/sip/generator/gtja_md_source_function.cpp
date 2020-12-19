int32_t MdApi::initialize(string sjson)
{
	int i = this->api->Initialize(sjson.c_str());
	return i;
};

	int i = this->api->getCounterType();
	return i;
};

	int i = this->api->getCounterType();
	return i;
};

int32_t MdApi::subscribeDepthMarketData(int mk_type, string code)
{
	int i = this->api->SubscribeDepthMarketData(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeMarketData(int mk_type, string code)
{
	int i = this->api->SubscribeMarketData(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeIndexData(int mk_type, string code)
{
	int i = this->api->SubscribeIndexData(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeDepthMarketData(int mk_type, string code)
{
	int i = this->api->UnSubscribeDepthMarketData(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeMarketData(int mk_type, string code)
{
	int i = this->api->UnSubscribeMarketData(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeIndexData(int mk_type, string code)
{
	int i = this->api->UnSubscribeIndexData(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeOrderQueue(int mk_type, string code)
{
	int i = this->api->SubscribeOrderQueue(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeOrderQueue(int mk_type, string code)
{
	int i = this->api->UnSubscribeOrderQueue(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeStepTrade(int mk_type, string code)
{
	int i = this->api->SubscribeStepTrade(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeStepTrade(int mk_type, string code)
{
	int i = this->api->UnSubscribeStepTrade(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeStepOrder(int mk_type, string code)
{
	int i = this->api->SubscribeStepOrder(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeStepOrder(int mk_type, string code)
{
	int i = this->api->UnSubscribeStepOrder(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeBaseInfo(int mk_type, string code)
{
	int i = this->api->SubscribeBaseInfo(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeBaseInfo(int mk_type, string code)
{
	int i = this->api->UnSubscribeBaseInfo(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeKline(int mk_type, string code)
{
	int i = this->api->SubscribeKline(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeKline(int mk_type, string code)
{
	int i = this->api->UnSubscribeKline(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeFutures(int mk_type, string code)
{
	int i = this->api->SubscribeFutures(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeFutures(int mk_type, string code)
{
	int i = this->api->UnSubscribeFutures(mk_type, code.c_str());
	return i;
};

int32_t MdApi::subscribeEtfExt(int mk_type, string code)
{
	int i = this->api->SubscribeEtfExt(mk_type, code.c_str());
	return i;
};

int32_t MdApi::unSubscribeEtfExt(int mk_type, string code)
{
	int i = this->api->UnSubscribeEtfExt(mk_type, code.c_str());
	return i;
};

