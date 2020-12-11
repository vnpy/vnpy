int initialize(string sjson);

int login();

int stop();

int subscribeDepthMarketData(int mk_type, string code);

int subscribeMarketData(int mk_type, string code);

int subscribeIndexData(int mk_type, string code);

int unSubscribeDepthMarketData(int mk_type, string code);

int unSubscribeMarketData(int mk_type, string code);

int unSubscribeIndexData(int mk_type, string code);

int subscribeOrderQueue(int mk_type, string code);

int unSubscribeOrderQueue(int mk_type, string code);

int subscribeStepTrade(int mk_type, string code);

int unSubscribeStepTrade(int mk_type, string code);

int subscribeStepOrder(int mk_type, string code);

int unSubscribeStepOrder(int mk_type, string code);

int subscribeBaseInfo(int mk_type, string code);

int unSubscribeBaseInfo(int mk_type, string code);

int subscribeKline(int mk_type, string code);

int unSubscribeKline(int mk_type, string code);

int subscribeFutures(int mk_type, string code);

int unSubscribeFutures(int mk_type, string code);

int subscribeEtfExt(int mk_type, string code);

int unSubscribeEtfExt(int mk_type, string code);

