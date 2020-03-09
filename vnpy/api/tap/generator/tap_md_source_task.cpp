void MdApi::TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info) = 0
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

void MdApi::TAP_CDECL OnAPIReady() = 0
{
	Task task = Task();
	task.task_name = ONAPIREADY;
	this->task_queue.push(task);
};

void MdApi::TAP_CDECL OnDisconnect(TAPIINT32 reasonCode) = 0
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_int = reasonCode;
	this->task_queue.push(task);
};

void MdApi::TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info) = 0
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

void MdApi::TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info) = 0
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

void MdApi::TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info) = 0
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

void MdApi::TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info) = 0
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

void MdApi::TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info) = 0
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

