void StockTdApi::OnFrontConnected() 
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void StockTdApi::OnFrontDisconnected(int nReason) 
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void StockTdApi::OnHeartBeatWarning(int nTimeLapse) 
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_id = nTimeLapse;
	this->task_queue.push(task);
};

void StockTdApi::OnPackageStart(int nTopicID, int nSequenceNo) 
{
	Task task = Task();
	task.task_name = ONPACKAGESTART;
	task.task_id = nTopicID;
	task.task_id = nSequenceNo;
	this->task_queue.push(task);
};

void StockTdApi::OnPackageEnd(int nTopicID, int nSequenceNo) 
{
	Task task = Task();
	task.task_name = ONPACKAGEEND;
	task.task_id = nTopicID;
	task.task_id = nSequenceNo;
	this->task_queue.push(task);
};

void StockTdApi::OnRspSubscribeTopic(CStockFtdcDisseminationField *pDissemination, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBETOPIC;
	if (pDissemination)
	{
		CStockFtdcDisseminationField *task_data = new CStockFtdcDisseminationField();
		*task_data = *pDissemination;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspUserLogin(CStockFtdcRspUserLoginField *pRspUserLogin, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	if (pRspUserLogin)
	{
		CStockFtdcRspUserLoginField *task_data = new CStockFtdcRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspUserLogout(CStockFtdcRspUserLogoutField *pRspUserLogout, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;
	if (pRspUserLogout)
	{
		CStockFtdcRspUserLogoutField *task_data = new CStockFtdcRspUserLogoutField();
		*task_data = *pRspUserLogout;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspUserPasswordUpdate(CStockFtdcUserPasswordUpdateField *pUserPasswordUpdate, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;
	if (pUserPasswordUpdate)
	{
		CStockFtdcUserPasswordUpdateField *task_data = new CStockFtdcUserPasswordUpdateField();
		*task_data = *pUserPasswordUpdate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspStockInsert(CStockFtdcStockInsertRspField *pStockInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKINSERT;
	if (pStockInsert)
	{
		CStockFtdcStockInsertRspField *task_data = new CStockFtdcStockInsertRspField();
		*task_data = *pStockInsert;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspStockCancel(CStockFtdcStockCancelRspField *pStockCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKCANCEL;
	if (pStockCancel)
	{
		CStockFtdcStockCancelRspField *task_data = new CStockFtdcStockCancelRspField();
		*task_data = *pStockCancel;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspOptionsInsert(CStockFtdcOptionsInsertRspField *pOptionsInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPOPTIONSINSERT;
	if (pOptionsInsert)
	{
		CStockFtdcOptionsInsertRspField *task_data = new CStockFtdcOptionsInsertRspField();
		*task_data = *pOptionsInsert;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspOptionsCancel(CStockFtdcOptionsCancelRspField *pOptionsCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPOPTIONSCANCEL;
	if (pOptionsCancel)
	{
		CStockFtdcOptionsCancelRspField *task_data = new CStockFtdcOptionsCancelRspField();
		*task_data = *pOptionsCancel;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQuoteInsert(CStockFtdcQuoteInsertRspField *pQuoteInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUOTEINSERT;
	if (pQuoteInsert)
	{
		CStockFtdcQuoteInsertRspField *task_data = new CStockFtdcQuoteInsertRspField();
		*task_data = *pQuoteInsert;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspForQuote(CStockFtdcForQuoteRspField *pForQuote, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPFORQUOTE;
	if (pForQuote)
	{
		CStockFtdcForQuoteRspField *task_data = new CStockFtdcForQuoteRspField();
		*task_data = *pForQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQuoteCancel(CStockFtdcQuoteCancelRspField *pQuoteCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQUOTECANCEL;
	if (pQuoteCancel)
	{
		CStockFtdcQuoteCancelRspField *task_data = new CStockFtdcQuoteCancelRspField();
		*task_data = *pQuoteCancel;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspStockLock(CStockFtdcStockLockRspField *pStockLock, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKLOCK;
	if (pStockLock)
	{
		CStockFtdcStockLockRspField *task_data = new CStockFtdcStockLockRspField();
		*task_data = *pStockLock;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspExercise(CStockFtdcExerciseRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPEXERCISE;
	if (pExercise)
	{
		CStockFtdcExerciseRspField *task_data = new CStockFtdcExerciseRspField();
		*task_data = *pExercise;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspExerciseCancel(CStockFtdcExerciseCancelRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPEXERCISECANCEL;
	if (pExercise)
	{
		CStockFtdcExerciseCancelRspField *task_data = new CStockFtdcExerciseCancelRspField();
		*task_data = *pExercise;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryPartAccount(CStockFtdcRspPartAccountField *pRspPartAccount, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYPARTACCOUNT;
	if (pRspPartAccount)
	{
		CStockFtdcRspPartAccountField *task_data = new CStockFtdcRspPartAccountField();
		*task_data = *pRspPartAccount;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryStockOrder(CStockFtdcRspQryStockOrderField *pOrder, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSTOCKORDER;
	if (pOrder)
	{
		CStockFtdcRspQryStockOrderField *task_data = new CStockFtdcRspQryStockOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryOptionsOrder(CStockFtdcRspQryOptionsOrderField *pOrder, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONSORDER;
	if (pOrder)
	{
		CStockFtdcRspQryOptionsOrderField *task_data = new CStockFtdcRspQryOptionsOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryQuoteOrder(CStockFtdcRspQryQuoteOrderField *pQuote, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYQUOTEORDER;
	if (pQuote)
	{
		CStockFtdcRspQryQuoteOrderField *task_data = new CStockFtdcRspQryQuoteOrderField();
		*task_data = *pQuote;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryStockTrade(CStockFtdcStockTradeField *pTrade, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSTOCKTRADE;
	if (pTrade)
	{
		CStockFtdcStockTradeField *task_data = new CStockFtdcStockTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryOptionsTrade(CStockFtdcOptionsTradeField *pTrade, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONSTRADE;
	if (pTrade)
	{
		CStockFtdcOptionsTradeField *task_data = new CStockFtdcOptionsTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryPosition(CStockFtdcRspPositionField *pPosition, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITION;
	if (pPosition)
	{
		CStockFtdcRspPositionField *task_data = new CStockFtdcRspPositionField();
		*task_data = *pPosition;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryTopic(CStockFtdcDisseminationField *pDissemination, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTOPIC;
	if (pDissemination)
	{
		CStockFtdcDisseminationField *task_data = new CStockFtdcDisseminationField();
		*task_data = *pDissemination;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryStock(CStockFtdcRspQryStockField *pStock, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSTOCK;
	if (pStock)
	{
		CStockFtdcRspQryStockField *task_data = new CStockFtdcRspQryStockField();
		*task_data = *pStock;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryOptions(CStockFtdcRspQryOptionsField *pOptions, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONS;
	if (pOptions)
	{
		CStockFtdcRspQryOptionsField *task_data = new CStockFtdcRspQryOptionsField();
		*task_data = *pOptions;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRtnOptionsOrder(CStockFtdcOptionsOrderField *pOrder) 
{
	Task task = Task();
	task.task_name = ONRTNOPTIONSORDER;
	if (pOrder)
	{
		CStockFtdcOptionsOrderField *task_data = new CStockFtdcOptionsOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRtnStockOrder(CStockFtdcStockOrderField *pOrder) 
{
	Task task = Task();
	task.task_name = ONRTNSTOCKORDER;
	if (pOrder)
	{
		CStockFtdcStockOrderField *task_data = new CStockFtdcStockOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRtnQuoteOrder(CStockFtdcQuoteOrderField *pQuote) 
{
	Task task = Task();
	task.task_name = ONRTNQUOTEORDER;
	if (pQuote)
	{
		CStockFtdcQuoteOrderField *task_data = new CStockFtdcQuoteOrderField();
		*task_data = *pQuote;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRtnOptionsTrade(CStockFtdcOptionsTradeField *pTrade) 
{
	Task task = Task();
	task.task_name = ONRTNOPTIONSTRADE;
	if (pTrade)
	{
		CStockFtdcOptionsTradeField *task_data = new CStockFtdcOptionsTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRtnStockTrade(CStockFtdcStockTradeField *pTrade) 
{
	Task task = Task();
	task.task_name = ONRTNSTOCKTRADE;
	if (pTrade)
	{
		CStockFtdcStockTradeField *task_data = new CStockFtdcStockTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRtnExercise(CStockFtdcExerciseRtnField *pExercise) 
{
	Task task = Task();
	task.task_name = ONRTNEXERCISE;
	if (pExercise)
	{
		CStockFtdcExerciseRtnField *task_data = new CStockFtdcExerciseRtnField();
		*task_data = *pExercise;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryRate(CStockFtdcRspQryRateField *pRate, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYRATE;
	if (pRate)
	{
		CStockFtdcRspQryRateField *task_data = new CStockFtdcRspQryRateField();
		*task_data = *pRate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryClient(CStockFtdcRspClientField *pRspClient, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCLIENT;
	if (pRspClient)
	{
		CStockFtdcRspClientField *task_data = new CStockFtdcRspClientField();
		*task_data = *pRspClient;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryClientMargin(CStockFtdcRspQryClientMarginField *pRspMargin, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYCLIENTMARGIN;
	if (pRspMargin)
	{
		CStockFtdcRspQryClientMarginField *task_data = new CStockFtdcRspQryClientMarginField();
		*task_data = *pRspMargin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspQryExercise(CStockFtdcExerciseRtnField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYEXERCISE;
	if (pExercise)
	{
		CStockFtdcExerciseRtnField *task_data = new CStockFtdcExerciseRtnField();
		*task_data = *pExercise;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRtnWithdrawDeposit(CStockFtdcWithdrawDepositRtnField *pWithdrawDeposit) 
{
	Task task = Task();
	task.task_name = ONRTNWITHDRAWDEPOSIT;
	if (pWithdrawDeposit)
	{
		CStockFtdcWithdrawDepositRtnField *task_data = new CStockFtdcWithdrawDepositRtnField();
		*task_data = *pWithdrawDeposit;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRspMarginCombAction(CStockFtdcMarginCombActionRspField *pMarginCombAction, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPMARGINCOMBACTION;
	if (pMarginCombAction)
	{
		CStockFtdcMarginCombActionRspField *task_data = new CStockFtdcMarginCombActionRspField();
		*task_data = *pMarginCombAction;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRtnMarginCombAction(CStockFtdcMarginCombActionRtnField *pMarginCombAction) 
{
	Task task = Task();
	task.task_name = ONRTNMARGINCOMBACTION;
	if (pMarginCombAction)
	{
		CStockFtdcMarginCombActionRtnField *task_data = new CStockFtdcMarginCombActionRtnField();
		*task_data = *pMarginCombAction;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void StockTdApi::OnRspQrySseCombPosition(CStockFtdcCombPositionRspField *pPosi, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYSSECOMBPOSITION;
	if (pPosi)
	{
		CStockFtdcCombPositionRspField *task_data = new CStockFtdcCombPositionRspField();
		*task_data = *pPosi;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void StockTdApi::OnRspCombExercise(CStockFtdcCombExerciseRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPCOMBEXERCISE;
	if (pExercise)
	{
		CStockFtdcCombExerciseRspField *task_data = new CStockFtdcCombExerciseRspField();
		*task_data = *pExercise;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CStockFtdcRspInfoField *task_error = new CStockFtdcRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

