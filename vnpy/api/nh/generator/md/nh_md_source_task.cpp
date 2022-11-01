void MdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;

	this->task_queue.push(task);
};

void MdApi::OnFrontDisConnected()
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;

	this->task_queue.push(task);
};

void MdApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;

	int *task_data = new int();
	*task_data = nTimeLapse;
	task.task_data = task_data;

	this->task_queue.push(task);
};

void MdApi::OnRspError(ERRORMSGINFO_t &pRspInfo,TSequenceIDType nRequestID) 
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	ERRORMSGINFO_t *task_error = new ERRORMSGINFO_t();
	*task_error = pRspInfo;
	task.task_error = task_error;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRtnMarketData(STKMarketData_t &pData) 
{
	Task task = Task();
	task.task_name = ONRTNMARKETDATA;

	STKMarketData_t *task_data = new STKMarketData_t();
	*task_data = pData;
	task.task_data = task_data;

	this->task_queue.push(task);
};

void MdApi::OnRspUtpLogin(const RspUtpLoginField_t& rsp,TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPUTPLOGIN;

	RspUtpLoginField_t *task_data = new RspUtpLoginField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspUtpLogout(const RspUtpLogoutField_t& rsp,TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPUTPLOGOUT;

	RspUtpLogoutField_t *task_data = new RspUtpLogoutField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspSubscribe(const RspSubscribeField_t& rsp,TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBE;

	RspSubscribeField_t *task_data = new RspSubscribeField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspUnSubscribe(const RspUnSubscribeField_t& rsp,TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBSCRIBE;

	RspUnSubscribeField_t *task_data = new RspUnSubscribeField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspQryExchange(const RspQryExchangeField_t& rsp,TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;

	RspQryExchangeField_t *task_data = new RspQryExchangeField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspQryInstrument(const RspQryInstrumentField_t& rsp,TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;

	RspQryInstrumentField_t *task_data = new RspQryInstrumentField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

