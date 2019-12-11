void TdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnQryFrontConnected()
{
	Task task = Task();
	task.task_name = ONQRYFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void TdApi::OnQryFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONQRYFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void TdApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_id = nTimeLapse;
	this->task_queue.push(task);
};

void TdApi::OnPackageStart(int nTopicID, int nSequenceNo)
{
	Task task = Task();
	task.task_name = ONPACKAGESTART;
	task.task_id = nTopicID;
	task.task_id = nSequenceNo;
	this->task_queue.push(task);
};

void TdApi::OnPackageEnd(int nTopicID, int nSequenceNo)
{
	Task task = Task();
	task.task_name = ONPACKAGEEND;
	task.task_id = nTopicID;
	task.task_id = nSequenceNo;
	this->task_queue.push(task);
};

void TdApi::OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPERROR;
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	if (pRspUserLogin)
	{
		CUstpFtdcRspUserLoginField *task_data = new CUstpFtdcRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;
	if (pRspUserLogout)
	{
		CUstpFtdcRspUserLogoutField *task_data = new CUstpFtdcRspUserLogoutField();
		*task_data = *pRspUserLogout;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;
	if (pUserPasswordUpdate)
	{
		CUstpFtdcUserPasswordUpdateField *task_data = new CUstpFtdcUserPasswordUpdateField();
		*task_data = *pUserPasswordUpdate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;
	if (pInputOrder)
	{
		CUstpFtdcInputOrderField *task_data = new CUstpFtdcInputOrderField();
		*task_data = *pInputOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	if (pOrderAction)
	{
		CUstpFtdcOrderActionField *task_data = new CUstpFtdcOrderActionField();
		*task_data = *pOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQuoteInsert(CUstpFtdcInputQuoteField *pInputQuote, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUOTEINSERT;
	if (pInputQuote)
	{
		CUstpFtdcInputQuoteField *task_data = new CUstpFtdcInputQuoteField();
		*task_data = *pInputQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQuoteAction(CUstpFtdcQuoteActionField *pQuoteAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUOTEACTION;
	if (pQuoteAction)
	{
		CUstpFtdcQuoteActionField *task_data = new CUstpFtdcQuoteActionField();
		*task_data = *pQuoteAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspForQuote(CUstpFtdcReqForQuoteField *pReqForQuote, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPFORQUOTE;
	if (pReqForQuote)
	{
		CUstpFtdcReqForQuoteField *task_data = new CUstpFtdcReqForQuoteField();
		*task_data = *pReqForQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspMarginCombAction(CUstpFtdcInputMarginCombActionField *pInputMarginCombAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPMARGINCOMBACTION;
	if (pInputMarginCombAction)
	{
		CUstpFtdcInputMarginCombActionField *task_data = new CUstpFtdcInputMarginCombActionField();
		*task_data = *pInputMarginCombAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserDeposit(CUstpFtdcstpUserDepositField *pstpUserDeposit, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERDEPOSIT;
	if (pstpUserDeposit)
	{
		CUstpFtdcstpUserDepositField *task_data = new CUstpFtdcstpUserDepositField();
		*task_data = *pstpUserDeposit;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnFlowMessageCancel(CUstpFtdcFlowMessageCancelField *pFlowMessageCancel) 
{
	Task task = Task();
	task.task_name = ONRTNFLOWMESSAGECANCEL;
	if (pFlowMessageCancel)
	{
		CUstpFtdcFlowMessageCancelField *task_data = new CUstpFtdcFlowMessageCancelField();
		*task_data = *pFlowMessageCancel;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CUstpFtdcTradeField *pTrade) 
{
	Task task = Task();
	task.task_name = ONRTNTRADE;
	if (pTrade)
	{
		CUstpFtdcTradeField *task_data = new CUstpFtdcTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CUstpFtdcOrderField *pOrder) 
{
	Task task = Task();
	task.task_name = ONRTNORDER;
	if (pOrder)
	{
		CUstpFtdcOrderField *task_data = new CUstpFtdcOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;
	if (pInputOrder)
	{
		CUstpFtdcInputOrderField *task_data = new CUstpFtdcInputOrderField();
		*task_data = *pInputOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;
	if (pOrderAction)
	{
		CUstpFtdcOrderActionField *task_data = new CUstpFtdcOrderActionField();
		*task_data = *pOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus) 
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;
	if (pInstrumentStatus)
	{
		CUstpFtdcInstrumentStatusField *task_data = new CUstpFtdcInstrumentStatusField();
		*task_data = *pInstrumentStatus;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes) 
{
	Task task = Task();
	task.task_name = ONRTNINVESTORACCOUNTDEPOSIT;
	if (pInvestorAccountDepositRes)
	{
		CUstpFtdcInvestorAccountDepositResField *task_data = new CUstpFtdcInvestorAccountDepositResField();
		*task_data = *pInvestorAccountDepositRes;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQuote(CUstpFtdcRtnQuoteField *pRtnQuote) 
{
	Task task = Task();
	task.task_name = ONRTNQUOTE;
	if (pRtnQuote)
	{
		CUstpFtdcRtnQuoteField *task_data = new CUstpFtdcRtnQuoteField();
		*task_data = *pRtnQuote;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnQuoteInsert(CUstpFtdcInputQuoteField *pInputQuote, CUstpFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNQUOTEINSERT;
	if (pInputQuote)
	{
		CUstpFtdcInputQuoteField *task_data = new CUstpFtdcInputQuoteField();
		*task_data = *pInputQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnQuoteAction(CUstpFtdcQuoteActionField *pQuoteAction, CUstpFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNQUOTEACTION;
	if (pQuoteAction)
	{
		CUstpFtdcQuoteActionField *task_data = new CUstpFtdcQuoteActionField();
		*task_data = *pQuoteAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnForQuote(CUstpFtdcReqForQuoteField *pReqForQuote) 
{
	Task task = Task();
	task.task_name = ONRTNFORQUOTE;
	if (pReqForQuote)
	{
		CUstpFtdcReqForQuoteField *task_data = new CUstpFtdcReqForQuoteField();
		*task_data = *pReqForQuote;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnMarginCombinationLeg(CUstpFtdcMarginCombinationLegField *pMarginCombinationLeg) 
{
	Task task = Task();
	task.task_name = ONRTNMARGINCOMBINATIONLEG;
	if (pMarginCombinationLeg)
	{
		CUstpFtdcMarginCombinationLegField *task_data = new CUstpFtdcMarginCombinationLegField();
		*task_data = *pMarginCombinationLeg;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnMarginCombAction(CUstpFtdcInputMarginCombActionField *pInputMarginCombAction) 
{
	Task task = Task();
	task.task_name = ONRTNMARGINCOMBACTION;
	if (pInputMarginCombAction)
	{
		CUstpFtdcInputMarginCombActionField *task_data = new CUstpFtdcInputMarginCombActionField();
		*task_data = *pInputMarginCombAction;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnUserDeposit(CUstpFtdcstpUserDepositField *pstpUserDeposit) 
{
	Task task = Task();
	task.task_name = ONRTNUSERDEPOSIT;
	if (pstpUserDeposit)
	{
		CUstpFtdcstpUserDepositField *task_data = new CUstpFtdcstpUserDepositField();
		*task_data = *pstpUserDeposit;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQueryUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUERYUSERLOGIN;
	if (pRspUserLogin)
	{
		CUstpFtdcRspUserLoginField *task_data = new CUstpFtdcRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CUstpFtdcOrderField *pOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	if (pOrder)
	{
		CUstpFtdcOrderField *task_data = new CUstpFtdcOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CUstpFtdcTradeField *pTrade, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;
	if (pTrade)
	{
		CUstpFtdcTradeField *task_data = new CUstpFtdcTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField *pRspUserInvestor, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYUSERINVESTOR;
	if (pRspUserInvestor)
	{
		CUstpFtdcRspUserInvestorField *task_data = new CUstpFtdcRspUserInvestorField();
		*task_data = *pRspUserInvestor;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingCode(CUstpFtdcRspTradingCodeField *pRspTradingCode, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGCODE;
	if (pRspTradingCode)
	{
		CUstpFtdcRspTradingCodeField *task_data = new CUstpFtdcRspTradingCodeField();
		*task_data = *pRspTradingCode;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField *pRspInvestorAccount, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORACCOUNT;
	if (pRspInvestorAccount)
	{
		CUstpFtdcRspInvestorAccountField *task_data = new CUstpFtdcRspInvestorAccountField();
		*task_data = *pRspInvestorAccount;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrument(CUstpFtdcRspInstrumentField *pRspInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;
	if (pRspInstrument)
	{
		CUstpFtdcRspInstrumentField *task_data = new CUstpFtdcRspInstrumentField();
		*task_data = *pRspInstrument;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchange(CUstpFtdcRspExchangeField *pRspExchange, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;
	if (pRspExchange)
	{
		CUstpFtdcRspExchangeField *task_data = new CUstpFtdcRspExchangeField();
		*task_data = *pRspExchange;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField *pRspInvestorPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;
	if (pRspInvestorPosition)
	{
		CUstpFtdcRspInvestorPositionField *task_data = new CUstpFtdcRspInvestorPositionField();
		*task_data = *pRspInvestorPosition;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField *pRspComplianceParam, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMPLIANCEPARAM;
	if (pRspComplianceParam)
	{
		CUstpFtdcRspComplianceParamField *task_data = new CUstpFtdcRspComplianceParamField();
		*task_data = *pRspComplianceParam;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorFee(CUstpFtdcInvestorFeeField *pInvestorFee, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORFEE;
	if (pInvestorFee)
	{
		CUstpFtdcInvestorFeeField *task_data = new CUstpFtdcInvestorFeeField();
		*task_data = *pInvestorFee;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField *pInvestorMargin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORMARGIN;
	if (pInvestorMargin)
	{
		CUstpFtdcInvestorMarginField *task_data = new CUstpFtdcInvestorMarginField();
		*task_data = *pInvestorMargin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorCombPosition(CUstpFtdcRspInvestorCombPositionField *pRspInvestorCombPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORCOMBPOSITION;
	if (pRspInvestorCombPosition)
	{
		CUstpFtdcRspInvestorCombPositionField *task_data = new CUstpFtdcRspInvestorCombPositionField();
		*task_data = *pRspInvestorCombPosition;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorLegPosition(CUstpFtdcRspInvestorLegPositionField *pRspInvestorLegPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORLEGPOSITION;
	if (pRspInvestorLegPosition)
	{
		CUstpFtdcRspInvestorLegPositionField *task_data = new CUstpFtdcRspInvestorLegPositionField();
		*task_data = *pRspInvestorLegPosition;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrumentGroup(CUstpFtdcRspInstrumentGroupField *pRspInstrumentGroup, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTGROUP;
	if (pRspInstrumentGroup)
	{
		CUstpFtdcRspInstrumentGroupField *task_data = new CUstpFtdcRspInstrumentGroupField();
		*task_data = *pRspInstrumentGroup;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryClientMarginCombType(CUstpFtdcRspClientMarginCombTypeField *pRspClientMarginCombType, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCLIENTMARGINCOMBTYPE;
	if (pRspClientMarginCombType)
	{
		CUstpFtdcRspClientMarginCombTypeField *task_data = new CUstpFtdcRspClientMarginCombTypeField();
		*task_data = *pRspClientMarginCombType;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspExecOrderInsert(CUstpFtdcInputExecOrderField *pInputExecOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERINSERT;
	if (pInputExecOrder)
	{
		CUstpFtdcInputExecOrderField *task_data = new CUstpFtdcInputExecOrderField();
		*task_data = *pInputExecOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspExecOrderAction(CUstpFtdcInputExecOrderActionField *pInputExecOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERACTION;
	if (pInputExecOrderAction)
	{
		CUstpFtdcInputExecOrderActionField *task_data = new CUstpFtdcInputExecOrderActionField();
		*task_data = *pInputExecOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnExecOrder(CUstpFtdcExecOrderField *pExecOrder) 
{
	Task task = Task();
	task.task_name = ONRTNEXECORDER;
	if (pExecOrder)
	{
		CUstpFtdcExecOrderField *task_data = new CUstpFtdcExecOrderField();
		*task_data = *pExecOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnExecOrderInsert(CUstpFtdcInputExecOrderField *pInputExecOrder, CUstpFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNEXECORDERINSERT;
	if (pInputExecOrder)
	{
		CUstpFtdcInputExecOrderField *task_data = new CUstpFtdcInputExecOrderField();
		*task_data = *pInputExecOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnExecOrderAction(CUstpFtdcInputExecOrderActionField *pInputExecOrderAction, CUstpFtdcRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONERRRTNEXECORDERACTION;
	if (pInputExecOrderAction)
	{
		CUstpFtdcInputExecOrderActionField *task_data = new CUstpFtdcInputExecOrderActionField();
		*task_data = *pInputExecOrderAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTransferMoney(CUstpFtdcSyncMoneyTransferField *pSyncMoneyTransfer) 
{
	Task task = Task();
	task.task_name = ONRTNTRANSFERMONEY;
	if (pSyncMoneyTransfer)
	{
		CUstpFtdcSyncMoneyTransferField *task_data = new CUstpFtdcSyncMoneyTransferField();
		*task_data = *pSyncMoneyTransfer;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQrySystemTime(CUstpFtdcRspQrySystemTimeField *pRspQrySystemTime, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSYSTEMTIME;
	if (pRspQrySystemTime)
	{
		CUstpFtdcRspQrySystemTimeField *task_data = new CUstpFtdcRspQrySystemTimeField();
		*task_data = *pRspQrySystemTime;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryMarginPrefParam(CUstpFtdcRspQryMarginPrefParamField *pRspQryMarginPrefParam, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYMARGINPREFPARAM;
	if (pRspQryMarginPrefParam)
	{
		CUstpFtdcRspQryMarginPrefParamField *task_data = new CUstpFtdcRspQryMarginPrefParamField();
		*task_data = *pRspQryMarginPrefParam;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspDSUserCertification(CUstpFtdcDSUserCertRspDataField *pDSUserCertRspData, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPDSUSERCERTIFICATION;
	if (pDSUserCertRspData)
	{
		CUstpFtdcDSUserCertRspDataField *task_data = new CUstpFtdcDSUserCertRspDataField();
		*task_data = *pDSUserCertRspData;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspDSProxySubmitInfo(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPDSPROXYSUBMITINFO;
	if (pRspInfo)
	{
		CUstpFtdcRspInfoField *task_error = new CUstpFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

