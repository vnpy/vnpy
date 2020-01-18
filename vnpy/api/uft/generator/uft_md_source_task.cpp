void MdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nResult)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nResult;
	this->task_queue.push(task);
};

void MdApi::OnRspDepthMarketDataSubscribe(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPDEPTHMARKETDATASUBSCRIBE;
	if (pRspInfo)
	{
		CHSRspInfoField *task_error = new CHSRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspDepthMarketDataCancel(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPDEPTHMARKETDATACANCEL;
	if (pRspInfo)
	{
		CHSRspInfoField *task_error = new CHSRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRtnDepthMarketData(CHSDepthMarketDataField *pDepthMarketData) 
{
	Task task = Task();
	task.task_name = ONRTNDEPTHMARKETDATA;
	if (pDepthMarketData)
	{
		CHSDepthMarketDataField *task_data = new CHSDepthMarketDataField();
		*task_data = *pDepthMarketData;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

