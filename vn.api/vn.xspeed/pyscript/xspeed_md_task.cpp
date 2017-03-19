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
	task.task_id = nReason;
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pRspUserLogin, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		DFITCUserLoginInfoRtnField empty_data = DFITCUserLoginInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pRspUsrLogout, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pRspUsrLogout)
	{
		task.task_data = *pRspUsrLogout;
	}
	else
	{
		DFITCUserLogoutInfoRtnField empty_data = DFITCUserLogoutInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspError(struct DFITCErrorRtnField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo{}
;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPSUBFORQUOTERSP;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBFORQUOTERSP;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnMarketData(struct DFITCDepthMarketDataField * pMarketDataField)
{
	Task task = Task();
	task.task_name = ONMARKETDATA;

	if (pMarketDataField)
	{
		task.task_data = *pMarketDataField;
	}
	else
	{
		DFITCDepthMarketDataField empty_data = DFITCDepthMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnCustomMarketData(struct DFITCCustomMarketDataField * pMarketDataField)
{
	Task task = Task();
	task.task_name = ONCUSTOMMARKETDATA;

	if (pMarketDataField)
	{
		task.task_data = *pMarketDataField;
	}
	else
	{
		DFITCCustomMarketDataField empty_data = DFITCCustomMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRtnForQuoteRsp(struct DFITCQuoteSubscribeRtnField * pForQuoteField)
{
	Task task = Task();
	task.task_name = ONRTNFORQUOTERSP;

	if (pForQuoteField)
	{
		task.task_data = *pForQuoteField;
	}
	else
	{
		DFITCQuoteSubscribeRtnField empty_data = DFITCQuoteSubscribeRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGDAY;

	if (pTradingDayRtnData)
	{
		task.task_data = *pTradingDayRtnData;
	}
	else
	{
		DFITCTradingDayRtnField empty_data = DFITCTradingDayRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

