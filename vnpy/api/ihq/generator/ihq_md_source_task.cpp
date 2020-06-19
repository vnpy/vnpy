void MdApi::OnFrontConnected() 
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nReason) 
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_extra = nReason;
	this->task_queue.push(task);
};

void MdApi::OnHeartBeatWarning(int nTimeLapse) 
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_extra = nTimeLapse;
	this->task_queue.push(task);
};

void MdApi::OnRspError(CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPERROR;
	if (pRspInfo)
	{
		CIStoneRspInfo *task_error = new CIStoneRspInfo();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_result = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogin(CIStoneRspUserLogin* pRspUserLogin, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	if (pRspUserLogin)
	{
		CIStoneRspUserLogin *task_data = new CIStoneRspUserLogin();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CIStoneRspInfo *task_error = new CIStoneRspInfo();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_result = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(CIStoneRspUserLogout* pRspUserLogout, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;
	if (pRspUserLogout)
	{
		CIStoneRspUserLogout *task_data = new CIStoneRspUserLogout();
		*task_data = *pRspUserLogout;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CIStoneRspInfo *task_error = new CIStoneRspInfo();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_result = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPSUBALLMARKETDATA;
	task.task_tick = tickType;
	task.task_exchange = exchangeID;
	task.task_id = nRequestID;
	task.task_result = isSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPUNSUBALLMARKETDATA;
	task.task_tick = tickType;
	task.task_exchange = exchangeID;
	task.task_id = nRequestID;
	task.task_result = isSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPSUBALLTICKBYTICK;
	task.task_exchange = exchangeID;
	task.task_id = nRequestID;
	task.task_result = isSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPUNSUBALLTICKBYTICK;
	task.task_exchange = exchangeID;
	task.task_id = nRequestID;
	task.task_result = isSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPSUBMARKETDATA;
	task.task_tickers = (char*) tickers;
	task.task_count = count;
	task.task_id = nRequestID;
	task.task_result = bIsSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPUNSUBMARKETDATA;
	task.task_tickers = (char*) tickers;
	task.task_count = count;
	task.task_id = nRequestID;
	task.task_result = bIsSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPSUBTICKBYTICK;
	task.task_tickers = (char*) tickers;
	task.task_count = count;
	task.task_id = nRequestID;
	task.task_result = bIsSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPUNSUBTICKBYTICK;
	task.task_tickers = (char*) tickers;
	task.task_count = count;
	task.task_id = nRequestID;
	task.task_result = bIsSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRtnDepthMarketData(CIStoneDepthMarketData* data) 
{
	Task task = Task();
	task.task_name = ONRTNDEPTHMARKETDATA;
	if (data)
	{
		CIStoneDepthMarketData *task_data = new CIStoneDepthMarketData();
		*task_data = *data;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRtnTickByTick(CIStoneTickByTick* data) 
{
	Task task = Task();
	task.task_name = ONRTNTICKBYTICK;
	if (data)
	{
		CIStoneTickByTick *task_data = new CIStoneTickByTick();
		*task_data = *data;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRtnOrderBook(CIStoneOrderBook* data) 
{
	Task task = Task();
	task.task_name = ONRTNORDERBOOK;
	if (data)
	{
		CIStoneOrderBook *task_data = new CIStoneOrderBook();
		*task_data = *data;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPSUBORDERBOOK;
	task.task_tickers = (char*) tickers;
	task.task_count = count;
	task.task_id = nRequestID;
	task.task_result = bIsSuccess;
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess) 
{
	Task task = Task();
	task.task_name = ONRSPUNSUBORDERBOOK;
	task.task_tickers = (char*) tickers;
	task.task_count = count;
	task.task_id = nRequestID;
	task.task_result = bIsSuccess;
	this->task_queue.push(task);
};

