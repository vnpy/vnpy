    void MdApi::OnRspLogin(int errorCode, TapAPIQuotLoginRspInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPLOGIN;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIQuotLoginRspInfo *task_data = new TapAPIQuotLoginRspInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void MdApi::OnAPIReady()
{
	Task task = Task();
	task.task_name = ONAPIREADY;
	this->task_queue.push(task);
};

    void MdApi::OnDisconnect(int reasonCode)
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_int = reasonCode;
	this->task_queue.push(task);
};

    void MdApi::OnRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, TapAPIQuoteCommodityInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMMODITY;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIQuoteCommodityInfo *task_data = new TapAPIQuoteCommodityInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void MdApi::OnRspQryContract(unsigned int sessionID, int errorCode, char isLast, TapAPIQuoteContractInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIQuoteContractInfo *task_data = new TapAPIQuoteContractInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void MdApi::OnRspSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, TapAPIQuoteWhole *info)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBEQUOTE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIQuoteWhole *task_data = new TapAPIQuoteWhole();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void MdApi::OnRspUnSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, TapAPIContract *info)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBSCRIBEQUOTE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIContract *task_data = new TapAPIContract();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void MdApi::OnRtnQuote(TapAPIQuoteWhole *info)
{
	Task task = Task();
	task.task_name = ONRTNQUOTE;
	if (info)
	{
		TapAPIQuoteWhole *task_data = new TapAPIQuoteWhole();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

