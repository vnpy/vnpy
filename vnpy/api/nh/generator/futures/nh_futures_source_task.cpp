void FuturesTdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void FuturesTdApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void FuturesTdApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_id = nTimeLapse;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPAUTHENTICATE;
	if (pRspAuthenticateField)
	{
		CThostFtdcRspAuthenticateField *task_data = new CThostFtdcRspAuthenticateField();
		*task_data = *pRspAuthenticateField;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	if (pRspUserLogin)
	{
		CThostFtdcRspUserLoginField *task_data = new CThostFtdcRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;
	if (pUserLogout)
	{
		CThostFtdcUserLogoutField *task_data = new CThostFtdcUserLogoutField();
		*task_data = *pUserLogout;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;
	if (pUserPasswordUpdate)
	{
		CThostFtdcUserPasswordUpdateField *task_data = new CThostFtdcUserPasswordUpdateField();
		*task_data = *pUserPasswordUpdate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPTRADINGACCOUNTPASSWORDUPDATE;
	if (pTradingAccountPasswordUpdate)
	{
		CThostFtdcTradingAccountPasswordUpdateField *task_data = new CThostFtdcTradingAccountPasswordUpdateField();
		*task_data = *pTradingAccountPasswordUpdate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;
	if (pInputOrder)
	{
		CThostFtdcInputOrderField *task_data = new CThostFtdcInputOrderField();
		*task_data = *pInputOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPPARKEDORDERINSERT;
	if (pParkedOrder)
	{
		CThostFtdcParkedOrderField *task_data = new CThostFtdcParkedOrderField();
		*task_data = *pParkedOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPPARKEDORDERACTION;
	if (pParkedOrderAction)
	{
		CThostFtdcParkedOrderActionField *task_data = new CThostFtdcParkedOrderActionField();
		*task_data = *pParkedOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	if (pInputOrderAction)
	{
		CThostFtdcInputOrderActionField *task_data = new CThostFtdcInputOrderActionField();
		*task_data = *pInputOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUERYMAXORDERVOLUME;
	if (pQueryMaxOrderVolume)
	{
		CThostFtdcQueryMaxOrderVolumeField *task_data = new CThostFtdcQueryMaxOrderVolumeField();
		*task_data = *pQueryMaxOrderVolume;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPSETTLEMENTINFOCONFIRM;
	if (pSettlementInfoConfirm)
	{
		CThostFtdcSettlementInfoConfirmField *task_data = new CThostFtdcSettlementInfoConfirmField();
		*task_data = *pSettlementInfoConfirm;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPREMOVEPARKEDORDER;
	if (pRemoveParkedOrder)
	{
		CThostFtdcRemoveParkedOrderField *task_data = new CThostFtdcRemoveParkedOrderField();
		*task_data = *pRemoveParkedOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPREMOVEPARKEDORDERACTION;
	if (pRemoveParkedOrderAction)
	{
		CThostFtdcRemoveParkedOrderActionField *task_data = new CThostFtdcRemoveParkedOrderActionField();
		*task_data = *pRemoveParkedOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERINSERT;
	if (pInputExecOrder)
	{
		CThostFtdcInputExecOrderField *task_data = new CThostFtdcInputExecOrderField();
		*task_data = *pInputExecOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERACTION;
	if (pInputExecOrderAction)
	{
		CThostFtdcInputExecOrderActionField *task_data = new CThostFtdcInputExecOrderActionField();
		*task_data = *pInputExecOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPFORQUOTEINSERT;
	if (pInputForQuote)
	{
		CThostFtdcInputForQuoteField *task_data = new CThostFtdcInputForQuoteField();
		*task_data = *pInputForQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUOTEINSERT;
	if (pInputQuote)
	{
		CThostFtdcInputQuoteField *task_data = new CThostFtdcInputQuoteField();
		*task_data = *pInputQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUOTEACTION;
	if (pInputQuoteAction)
	{
		CThostFtdcInputQuoteActionField *task_data = new CThostFtdcInputQuoteActionField();
		*task_data = *pInputQuoteAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPBATCHORDERACTION;
	if (pInputBatchOrderAction)
	{
		CThostFtdcInputBatchOrderActionField *task_data = new CThostFtdcInputBatchOrderActionField();
		*task_data = *pInputBatchOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPOPTIONSELFCLOSEINSERT;
	if (pInputOptionSelfClose)
	{
		CThostFtdcInputOptionSelfCloseField *task_data = new CThostFtdcInputOptionSelfCloseField();
		*task_data = *pInputOptionSelfClose;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPOPTIONSELFCLOSEACTION;
	if (pInputOptionSelfCloseAction)
	{
		CThostFtdcInputOptionSelfCloseActionField *task_data = new CThostFtdcInputOptionSelfCloseActionField();
		*task_data = *pInputOptionSelfCloseAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPCOMBACTIONINSERT;
	if (pInputCombAction)
	{
		CThostFtdcInputCombActionField *task_data = new CThostFtdcInputCombActionField();
		*task_data = *pInputCombAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	if (pOrder)
	{
		CThostFtdcOrderField *task_data = new CThostFtdcOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;
	if (pTrade)
	{
		CThostFtdcTradeField *task_data = new CThostFtdcTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;
	if (pInvestorPosition)
	{
		CThostFtdcInvestorPositionField *task_data = new CThostFtdcInvestorPositionField();
		*task_data = *pInvestorPosition;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGACCOUNT;
	if (pTradingAccount)
	{
		CThostFtdcTradingAccountField *task_data = new CThostFtdcTradingAccountField();
		*task_data = *pTradingAccount;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTOR;
	if (pInvestor)
	{
		CThostFtdcInvestorField *task_data = new CThostFtdcInvestorField();
		*task_data = *pInvestor;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGCODE;
	if (pTradingCode)
	{
		CThostFtdcTradingCodeField *task_data = new CThostFtdcTradingCodeField();
		*task_data = *pTradingCode;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTMARGINRATE;
	if (pInstrumentMarginRate)
	{
		CThostFtdcInstrumentMarginRateField *task_data = new CThostFtdcInstrumentMarginRateField();
		*task_data = *pInstrumentMarginRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTCOMMISSIONRATE;
	if (pInstrumentCommissionRate)
	{
		CThostFtdcInstrumentCommissionRateField *task_data = new CThostFtdcInstrumentCommissionRateField();
		*task_data = *pInstrumentCommissionRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;
	if (pExchange)
	{
		CThostFtdcExchangeField *task_data = new CThostFtdcExchangeField();
		*task_data = *pExchange;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYPRODUCT;
	if (pProduct)
	{
		CThostFtdcProductField *task_data = new CThostFtdcProductField();
		*task_data = *pProduct;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;
	if (pInstrument)
	{
		CThostFtdcInstrumentField *task_data = new CThostFtdcInstrumentField();
		*task_data = *pInstrument;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYDEPTHMARKETDATA;
	if (pDepthMarketData)
	{
		CThostFtdcDepthMarketDataField *task_data = new CThostFtdcDepthMarketDataField();
		*task_data = *pDepthMarketData;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSETTLEMENTINFO;
	if (pSettlementInfo)
	{
		CThostFtdcSettlementInfoField *task_data = new CThostFtdcSettlementInfoField();
		*task_data = *pSettlementInfo;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERBANK;
	if (pTransferBank)
	{
		CThostFtdcTransferBankField *task_data = new CThostFtdcTransferBankField();
		*task_data = *pTransferBank;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITIONDETAIL;
	if (pInvestorPositionDetail)
	{
		CThostFtdcInvestorPositionDetailField *task_data = new CThostFtdcInvestorPositionDetailField();
		*task_data = *pInvestorPositionDetail;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYNOTICE;
	if (pNotice)
	{
		CThostFtdcNoticeField *task_data = new CThostFtdcNoticeField();
		*task_data = *pNotice;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSETTLEMENTINFOCONFIRM;
	if (pSettlementInfoConfirm)
	{
		CThostFtdcSettlementInfoConfirmField *task_data = new CThostFtdcSettlementInfoConfirmField();
		*task_data = *pSettlementInfoConfirm;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL;
	if (pInvestorPositionCombineDetail)
	{
		CThostFtdcInvestorPositionCombineDetailField *task_data = new CThostFtdcInvestorPositionCombineDetailField();
		*task_data = *pInvestorPositionCombineDetail;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCFMMCTRADINGACCOUNTKEY;
	if (pCFMMCTradingAccountKey)
	{
		CThostFtdcCFMMCTradingAccountKeyField *task_data = new CThostFtdcCFMMCTradingAccountKeyField();
		*task_data = *pCFMMCTradingAccountKey;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEWARRANTOFFSET;
	if (pEWarrantOffset)
	{
		CThostFtdcEWarrantOffsetField *task_data = new CThostFtdcEWarrantOffsetField();
		*task_data = *pEWarrantOffset;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPRODUCTGROUPMARGIN;
	if (pInvestorProductGroupMargin)
	{
		CThostFtdcInvestorProductGroupMarginField *task_data = new CThostFtdcInvestorProductGroupMarginField();
		*task_data = *pInvestorProductGroupMargin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGEMARGINRATE;
	if (pExchangeMarginRate)
	{
		CThostFtdcExchangeMarginRateField *task_data = new CThostFtdcExchangeMarginRateField();
		*task_data = *pExchangeMarginRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGEMARGINRATEADJUST;
	if (pExchangeMarginRateAdjust)
	{
		CThostFtdcExchangeMarginRateAdjustField *task_data = new CThostFtdcExchangeMarginRateAdjustField();
		*task_data = *pExchangeMarginRateAdjust;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGERATE;
	if (pExchangeRate)
	{
		CThostFtdcExchangeRateField *task_data = new CThostFtdcExchangeRateField();
		*task_data = *pExchangeRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSECAGENTACIDMAP;
	if (pSecAgentACIDMap)
	{
		CThostFtdcSecAgentACIDMapField *task_data = new CThostFtdcSecAgentACIDMapField();
		*task_data = *pSecAgentACIDMap;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYPRODUCTEXCHRATE;
	if (pProductExchRate)
	{
		CThostFtdcProductExchRateField *task_data = new CThostFtdcProductExchRateField();
		*task_data = *pProductExchRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYPRODUCTGROUP;
	if (pProductGroup)
	{
		CThostFtdcProductGroupField *task_data = new CThostFtdcProductGroupField();
		*task_data = *pProductGroup;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYMMINSTRUMENTCOMMISSIONRATE;
	if (pMMInstrumentCommissionRate)
	{
		CThostFtdcMMInstrumentCommissionRateField *task_data = new CThostFtdcMMInstrumentCommissionRateField();
		*task_data = *pMMInstrumentCommissionRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYMMOPTIONINSTRCOMMRATE;
	if (pMMOptionInstrCommRate)
	{
		CThostFtdcMMOptionInstrCommRateField *task_data = new CThostFtdcMMOptionInstrCommRateField();
		*task_data = *pMMOptionInstrCommRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTORDERCOMMRATE;
	if (pInstrumentOrderCommRate)
	{
		CThostFtdcInstrumentOrderCommRateField *task_data = new CThostFtdcInstrumentOrderCommRateField();
		*task_data = *pInstrumentOrderCommRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSECAGENTTRADINGACCOUNT;
	if (pTradingAccount)
	{
		CThostFtdcTradingAccountField *task_data = new CThostFtdcTradingAccountField();
		*task_data = *pTradingAccount;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSECAGENTCHECKMODE;
	if (pSecAgentCheckMode)
	{
		CThostFtdcSecAgentCheckModeField *task_data = new CThostFtdcSecAgentCheckModeField();
		*task_data = *pSecAgentCheckMode;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONINSTRTRADECOST;
	if (pOptionInstrTradeCost)
	{
		CThostFtdcOptionInstrTradeCostField *task_data = new CThostFtdcOptionInstrTradeCostField();
		*task_data = *pOptionInstrTradeCost;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONINSTRCOMMRATE;
	if (pOptionInstrCommRate)
	{
		CThostFtdcOptionInstrCommRateField *task_data = new CThostFtdcOptionInstrCommRateField();
		*task_data = *pOptionInstrCommRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEXECORDER;
	if (pExecOrder)
	{
		CThostFtdcExecOrderField *task_data = new CThostFtdcExecOrderField();
		*task_data = *pExecOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYFORQUOTE;
	if (pForQuote)
	{
		CThostFtdcForQuoteField *task_data = new CThostFtdcForQuoteField();
		*task_data = *pForQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYQUOTE;
	if (pQuote)
	{
		CThostFtdcQuoteField *task_data = new CThostFtdcQuoteField();
		*task_data = *pQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONSELFCLOSE;
	if (pOptionSelfClose)
	{
		CThostFtdcOptionSelfCloseField *task_data = new CThostFtdcOptionSelfCloseField();
		*task_data = *pOptionSelfClose;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTUNIT;
	if (pInvestUnit)
	{
		CThostFtdcInvestUnitField *task_data = new CThostFtdcInvestUnitField();
		*task_data = *pInvestUnit;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMBINSTRUMENTGUARD;
	if (pCombInstrumentGuard)
	{
		CThostFtdcCombInstrumentGuardField *task_data = new CThostFtdcCombInstrumentGuardField();
		*task_data = *pCombInstrumentGuard;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMBACTION;
	if (pCombAction)
	{
		CThostFtdcCombActionField *task_data = new CThostFtdcCombActionField();
		*task_data = *pCombAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERSERIAL;
	if (pTransferSerial)
	{
		CThostFtdcTransferSerialField *task_data = new CThostFtdcTransferSerialField();
		*task_data = *pTransferSerial;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTREGISTER;
	if (pAccountregister)
	{
		CThostFtdcAccountregisterField *task_data = new CThostFtdcAccountregisterField();
		*task_data = *pAccountregister;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspForQuote(CThostFtdcInputForQuoteField *pForQuoteRsp, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPFORQUOTE;
	if (pForQuoteRsp)
	{
		CThostFtdcInputForQuoteField *task_data = new CThostFtdcInputForQuoteField();
		*task_data = *pForQuoteRsp;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPERROR;
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnOrder(CThostFtdcOrderField *pOrder) 
{
	Task task = Task();
	task.task_name = ONRTNORDER;
	if (pOrder)
	{
		CThostFtdcOrderField *task_data = new CThostFtdcOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnTrade(CThostFtdcTradeField *pTrade) 
{
	Task task = Task();
	task.task_name = ONRTNTRADE;
	if (pTrade)
	{
		CThostFtdcTradeField *task_data = new CThostFtdcTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;
	if (pInputOrder)
	{
		CThostFtdcInputOrderField *task_data = new CThostFtdcInputOrderField();
		*task_data = *pInputOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;
	if (pOrderAction)
	{
		CThostFtdcOrderActionField *task_data = new CThostFtdcOrderActionField();
		*task_data = *pOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) 
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;
	if (pInstrumentStatus)
	{
		CThostFtdcInstrumentStatusField *task_data = new CThostFtdcInstrumentStatusField();
		*task_data = *pInstrumentStatus;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnBulletin(CThostFtdcBulletinField *pBulletin) 
{
	Task task = Task();
	task.task_name = ONRTNBULLETIN;
	if (pBulletin)
	{
		CThostFtdcBulletinField *task_data = new CThostFtdcBulletinField();
		*task_data = *pBulletin;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) 
{
	Task task = Task();
	task.task_name = ONRTNTRADINGNOTICE;
	if (pTradingNoticeInfo)
	{
		CThostFtdcTradingNoticeInfoField *task_data = new CThostFtdcTradingNoticeInfoField();
		*task_data = *pTradingNoticeInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) 
{
	Task task = Task();
	task.task_name = ONRTNERRORCONDITIONALORDER;
	if (pErrorConditionalOrder)
	{
		CThostFtdcErrorConditionalOrderField *task_data = new CThostFtdcErrorConditionalOrderField();
		*task_data = *pErrorConditionalOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) 
{
	Task task = Task();
	task.task_name = ONRTNEXECORDER;
	if (pExecOrder)
	{
		CThostFtdcExecOrderField *task_data = new CThostFtdcExecOrderField();
		*task_data = *pExecOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNEXECORDERINSERT;
	if (pInputExecOrder)
	{
		CThostFtdcInputExecOrderField *task_data = new CThostFtdcInputExecOrderField();
		*task_data = *pInputExecOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNEXECORDERACTION;
	if (pExecOrderAction)
	{
		CThostFtdcExecOrderActionField *task_data = new CThostFtdcExecOrderActionField();
		*task_data = *pExecOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNFORQUOTEINSERT;
	if (pInputForQuote)
	{
		CThostFtdcInputForQuoteField *task_data = new CThostFtdcInputForQuoteField();
		*task_data = *pInputForQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnQuote(CThostFtdcQuoteField *pQuote) 
{
	Task task = Task();
	task.task_name = ONRTNQUOTE;
	if (pQuote)
	{
		CThostFtdcQuoteField *task_data = new CThostFtdcQuoteField();
		*task_data = *pQuote;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNQUOTEINSERT;
	if (pInputQuote)
	{
		CThostFtdcInputQuoteField *task_data = new CThostFtdcInputQuoteField();
		*task_data = *pInputQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNQUOTEACTION;
	if (pQuoteAction)
	{
		CThostFtdcQuoteActionField *task_data = new CThostFtdcQuoteActionField();
		*task_data = *pQuoteAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnForQuote(CThostFtdcForQuoteRspField *pForQuoteRsp) 
{
	Task task = Task();
	task.task_name = ONRTNFORQUOTE;
	if (pForQuoteRsp)
	{
		CThostFtdcForQuoteRspField *task_data = new CThostFtdcForQuoteRspField();
		*task_data = *pForQuoteRsp;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) 
{
	Task task = Task();
	task.task_name = ONRTNCFMMCTRADINGACCOUNTTOKEN;
	if (pCFMMCTradingAccountToken)
	{
		CThostFtdcCFMMCTradingAccountTokenField *task_data = new CThostFtdcCFMMCTradingAccountTokenField();
		*task_data = *pCFMMCTradingAccountToken;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNBATCHORDERACTION;
	if (pBatchOrderAction)
	{
		CThostFtdcBatchOrderActionField *task_data = new CThostFtdcBatchOrderActionField();
		*task_data = *pBatchOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) 
{
	Task task = Task();
	task.task_name = ONRTNOPTIONSELFCLOSE;
	if (pOptionSelfClose)
	{
		CThostFtdcOptionSelfCloseField *task_data = new CThostFtdcOptionSelfCloseField();
		*task_data = *pOptionSelfClose;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNOPTIONSELFCLOSEINSERT;
	if (pInputOptionSelfClose)
	{
		CThostFtdcInputOptionSelfCloseField *task_data = new CThostFtdcInputOptionSelfCloseField();
		*task_data = *pInputOptionSelfClose;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNOPTIONSELFCLOSEACTION;
	if (pOptionSelfCloseAction)
	{
		CThostFtdcOptionSelfCloseActionField *task_data = new CThostFtdcOptionSelfCloseActionField();
		*task_data = *pOptionSelfCloseAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnCombAction(CThostFtdcCombActionField *pCombAction) 
{
	Task task = Task();
	task.task_name = ONRTNCOMBACTION;
	if (pCombAction)
	{
		CThostFtdcCombActionField *task_data = new CThostFtdcCombActionField();
		*task_data = *pCombAction;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNCOMBACTIONINSERT;
	if (pInputCombAction)
	{
		CThostFtdcInputCombActionField *task_data = new CThostFtdcInputCombActionField();
		*task_data = *pInputCombAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACTBANK;
	if (pContractBank)
	{
		CThostFtdcContractBankField *task_data = new CThostFtdcContractBankField();
		*task_data = *pContractBank;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYPARKEDORDER;
	if (pParkedOrder)
	{
		CThostFtdcParkedOrderField *task_data = new CThostFtdcParkedOrderField();
		*task_data = *pParkedOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYPARKEDORDERACTION;
	if (pParkedOrderAction)
	{
		CThostFtdcParkedOrderActionField *task_data = new CThostFtdcParkedOrderActionField();
		*task_data = *pParkedOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGNOTICE;
	if (pTradingNotice)
	{
		CThostFtdcTradingNoticeField *task_data = new CThostFtdcTradingNoticeField();
		*task_data = *pTradingNotice;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYBROKERTRADINGPARAMS;
	if (pBrokerTradingParams)
	{
		CThostFtdcBrokerTradingParamsField *task_data = new CThostFtdcBrokerTradingParamsField();
		*task_data = *pBrokerTradingParams;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYBROKERTRADINGALGOS;
	if (pBrokerTradingAlgos)
	{
		CThostFtdcBrokerTradingAlgosField *task_data = new CThostFtdcBrokerTradingAlgosField();
		*task_data = *pBrokerTradingAlgos;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN;
	if (pQueryCFMMCTradingAccountToken)
	{
		CThostFtdcQueryCFMMCTradingAccountTokenField *task_data = new CThostFtdcQueryCFMMCTradingAccountTokenField();
		*task_data = *pQueryCFMMCTradingAccountToken;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) 
{
	Task task = Task();
	task.task_name = ONRTNFROMBANKTOFUTUREBYBANK;
	if (pRspTransfer)
	{
		CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
		*task_data = *pRspTransfer;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) 
{
	Task task = Task();
	task.task_name = ONRTNFROMFUTURETOBANKBYBANK;
	if (pRspTransfer)
	{
		CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
		*task_data = *pRspTransfer;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) 
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYBANK;
	if (pRspRepeal)
	{
		CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
		*task_data = *pRspRepeal;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) 
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMFUTURETOBANKBYBANK;
	if (pRspRepeal)
	{
		CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
		*task_data = *pRspRepeal;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) 
{
	Task task = Task();
	task.task_name = ONRTNFROMBANKTOFUTUREBYFUTURE;
	if (pRspTransfer)
	{
		CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
		*task_data = *pRspTransfer;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) 
{
	Task task = Task();
	task.task_name = ONRTNFROMFUTURETOBANKBYFUTURE;
	if (pRspTransfer)
	{
		CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
		*task_data = *pRspTransfer;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) 
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL;
	if (pRspRepeal)
	{
		CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
		*task_data = *pRspRepeal;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) 
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL;
	if (pRspRepeal)
	{
		CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
		*task_data = *pRspRepeal;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) 
{
	Task task = Task();
	task.task_name = ONRTNQUERYBANKBALANCEBYFUTURE;
	if (pNotifyQueryAccount)
	{
		CThostFtdcNotifyQueryAccountField *task_data = new CThostFtdcNotifyQueryAccountField();
		*task_data = *pNotifyQueryAccount;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNBANKTOFUTUREBYFUTURE;
	if (pReqTransfer)
	{
		CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
		*task_data = *pReqTransfer;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNFUTURETOBANKBYFUTURE;
	if (pReqTransfer)
	{
		CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
		*task_data = *pReqTransfer;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL;
	if (pReqRepeal)
	{
		CThostFtdcReqRepealField *task_data = new CThostFtdcReqRepealField();
		*task_data = *pReqRepeal;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL;
	if (pReqRepeal)
	{
		CThostFtdcReqRepealField *task_data = new CThostFtdcReqRepealField();
		*task_data = *pReqRepeal;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNQUERYBANKBALANCEBYFUTURE;
	if (pReqQueryAccount)
	{
		CThostFtdcReqQueryAccountField *task_data = new CThostFtdcReqQueryAccountField();
		*task_data = *pReqQueryAccount;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) 
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYFUTURE;
	if (pRspRepeal)
	{
		CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
		*task_data = *pRspRepeal;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) 
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMFUTURETOBANKBYFUTURE;
	if (pRspRepeal)
	{
		CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
		*task_data = *pRspRepeal;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPFROMBANKTOFUTUREBYFUTURE;
	if (pReqTransfer)
	{
		CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
		*task_data = *pReqTransfer;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPFROMFUTURETOBANKBYFUTURE;
	if (pReqTransfer)
	{
		CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
		*task_data = *pReqTransfer;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUERYBANKACCOUNTMONEYBYFUTURE;
	if (pReqQueryAccount)
	{
		CThostFtdcReqQueryAccountField *task_data = new CThostFtdcReqQueryAccountField();
		*task_data = *pReqQueryAccount;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) 
{
	Task task = Task();
	task.task_name = ONRTNOPENACCOUNTBYBANK;
	if (pOpenAccount)
	{
		CThostFtdcOpenAccountField *task_data = new CThostFtdcOpenAccountField();
		*task_data = *pOpenAccount;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) 
{
	Task task = Task();
	task.task_name = ONRTNCANCELACCOUNTBYBANK;
	if (pCancelAccount)
	{
		CThostFtdcCancelAccountField *task_data = new CThostFtdcCancelAccountField();
		*task_data = *pCancelAccount;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void FuturesTdApi::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) 
{
	Task task = Task();
	task.task_name = ONRTNCHANGEACCOUNTBYBANK;
	if (pChangeAccount)
	{
		CThostFtdcChangeAccountField *task_data = new CThostFtdcChangeAccountField();
		*task_data = *pChangeAccount;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

