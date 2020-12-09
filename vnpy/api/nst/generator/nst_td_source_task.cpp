void TdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CUftRspUserLoginField* pRspUserLogin, CUftRspInfoField* pRspInfo )
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	if (pRspUserLogin)
	{
		CUftRspUserLoginField *task_data = new CUftRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUftRspInfoField *task_error = new CUftRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnAnsOrderInsert(CUftAnsOrderInsertField *pOrderRsp, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONANSORDERINSERT;
	if (pOrderRsp)
	{
		CUftAnsOrderInsertField *task_data = new CUftAnsOrderInsertField();
		*task_data = *pOrderRsp;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CUftRspnOrderInsertField *pOrderRsp, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;
	if (pOrderRsp)
	{
		CUftRspnOrderInsertField *task_data = new CUftRspnOrderInsertField();
		*task_data = *pOrderRsp;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnAnsOrderAction(CUftAnsOrderActionField *pOrderAction, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONANSORDERACTION;
	if (pOrderAction)
	{
		CUftAnsOrderActionField *task_data = new CUftAnsOrderActionField();
		*task_data = *pOrderAction;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CUftRspnOrderActionField *pOrderAction, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	if (pOrderAction)
	{
		CUftRspnOrderActionField *task_data = new CUftRspnOrderActionField();
		*task_data = *pOrderAction;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnOrderRtn(CUftRtnnOrderField* pOrder)
{
	Task task = Task();
	task.task_name = ONORDERRTN;
	if (pOrder)
	{
		CUftRtnnOrderField *task_data = new CUftRtnnOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnTradeRtn(CUftRtnnTradeField* pOrder)
{
	Task task = Task();
	task.task_name = ONTRADERTN;
	if (pOrder)
	{
		CUftRtnnTradeField *task_data = new CUftRtnnTradeField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspTradingAccount(CUftAnsQueryFundField *pRspFund)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGACCOUNT;
	if (pRspFund)
	{
		CUftAnsQueryFundField *task_data = new CUftAnsQueryFundField();
		*task_data = *pRspFund;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspError(CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONRSPERROR;
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CUftAnsQueryOrderField *pEntrust, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	if (pEntrust)
	{
		CUftAnsQueryOrderField *task_data = new CUftAnsQueryOrderField();
		*task_data = *pEntrust;
		task.task_data = task_data;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CUftAnsQueryTradeField *pTrade, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;
	if (pTrade)
	{
		CUftAnsQueryTradeField *task_data = new CUftAnsQueryTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CUftAnsQueryPositionField *pInvestorPosition, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;
	if (pInvestorPosition)
	{
		CUftAnsQueryPositionField *task_data = new CUftAnsQueryPositionField();
		*task_data = *pInvestorPosition;
		task.task_data = task_data;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryChangePwd() 
{
	Task task = Task();
	task.task_name = ONRSPQRYCHANGEPWD;
	this->task_queue.push(task);
};

void TdApi::OnRspLogout(const char* szMsg) 
{
	Task task = Task();
	task.task_name = ONRSPLOGOUT;
	if (szMsg)
	{
		char *task_data = new char();
		*task_data = *szMsg;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CUftRtnInstrumentStatusField *pInstStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;
	if (pInstStatus)
	{
		CUftRtnInstrumentStatusField *task_data = new CUftRtnInstrumentStatusField();
		*task_data = *pInstStatus;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspTest(CUftRspTest *pTest)
{
	Task task = Task();
	task.task_name = ONRSPTEST;
	if (pTest)
	{
		CUftRspTest *task_data = new CUftRspTest();
		*task_data = *pTest;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CUftRspErrorField* pError) 
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CUftRspErrorField* pError) 
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

