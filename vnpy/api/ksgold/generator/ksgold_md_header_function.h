void release();

bool init();

int join();

void registerFront(string pszFrontAddress);

void createGoldQutoApi(string pszFlowPath = " ");

int subscribeMarketData(string ppInstrumentID, int reqid);

int unSubscribeMarketData(string ppInstrumentID, int reqid);

int reqUserLogin(const dict &req, int reqid);

int reqUserLogout(const dict &req, int reqid);

