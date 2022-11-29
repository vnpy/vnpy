// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnnhstock.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

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
};

void StockTdApi::OnPackageEnd(int nTopicID, int nSequenceNo) 
{
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


///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void StockTdApi::processTask()
{
	try
	{
		while (this->active)
		{
			Task task = this->task_queue.pop();
			switch (task.task_name)
			{
			case ONFRONTCONNECTED:
			{
				this->processFrontConnected(&task);
				break;
			}

			case ONFRONTDISCONNECTED:
			{
				this->processFrontDisconnected(&task);
				break;
			}

			case ONHEARTBEATWARNING:
			{
				this->processHeartBeatWarning(&task);
				break;
			}


			case ONRSPSUBSCRIBETOPIC:
			{
				this->processRspSubscribeTopic(&task);
				break;
			}

			case ONRSPUSERLOGIN:
			{
				this->processRspUserLogin(&task);
				break;
			}

			case ONRSPUSERLOGOUT:
			{
				this->processRspUserLogout(&task);
				break;
			}

			case ONRSPUSERPASSWORDUPDATE:
			{
				this->processRspUserPasswordUpdate(&task);
				break;
			}

			case ONRSPSTOCKINSERT:
			{
				this->processRspStockInsert(&task);
				break;
			}

			case ONRSPSTOCKCANCEL:
			{
				this->processRspStockCancel(&task);
				break;
			}

			case ONRSPOPTIONSINSERT:
			{
				this->processRspOptionsInsert(&task);
				break;
			}

			case ONRSPOPTIONSCANCEL:
			{
				this->processRspOptionsCancel(&task);
				break;
			}

			case ONRSPQUOTEINSERT:
			{
				this->processRspQuoteInsert(&task);
				break;
			}

			case ONRSPFORQUOTE:
			{
				this->processRspForQuote(&task);
				break;
			}

			case ONRSPQUOTECANCEL:
			{
				this->processRspQuoteCancel(&task);
				break;
			}

			case ONRSPSTOCKLOCK:
			{
				this->processRspStockLock(&task);
				break;
			}

			case ONRSPEXERCISE:
			{
				this->processRspExercise(&task);
				break;
			}

			case ONRSPEXERCISECANCEL:
			{
				this->processRspExerciseCancel(&task);
				break;
			}

			case ONRSPQRYPARTACCOUNT:
			{
				this->processRspQryPartAccount(&task);
				break;
			}

			case ONRSPQRYSTOCKORDER:
			{
				this->processRspQryStockOrder(&task);
				break;
			}

			case ONRSPQRYOPTIONSORDER:
			{
				this->processRspQryOptionsOrder(&task);
				break;
			}

			case ONRSPQRYQUOTEORDER:
			{
				this->processRspQryQuoteOrder(&task);
				break;
			}

			case ONRSPQRYSTOCKTRADE:
			{
				this->processRspQryStockTrade(&task);
				break;
			}

			case ONRSPQRYOPTIONSTRADE:
			{
				this->processRspQryOptionsTrade(&task);
				break;
			}

			case ONRSPQRYPOSITION:
			{
				this->processRspQryPosition(&task);
				break;
			}

			case ONRSPQRYTOPIC:
			{
				this->processRspQryTopic(&task);
				break;
			}

			case ONRSPQRYSTOCK:
			{
				this->processRspQryStock(&task);
				break;
			}

			case ONRSPQRYOPTIONS:
			{
				this->processRspQryOptions(&task);
				break;
			}

			case ONRTNOPTIONSORDER:
			{
				this->processRtnOptionsOrder(&task);
				break;
			}

			case ONRTNSTOCKORDER:
			{
				this->processRtnStockOrder(&task);
				break;
			}

			case ONRTNQUOTEORDER:
			{
				this->processRtnQuoteOrder(&task);
				break;
			}

			case ONRTNOPTIONSTRADE:
			{
				this->processRtnOptionsTrade(&task);
				break;
			}

			case ONRTNSTOCKTRADE:
			{
				this->processRtnStockTrade(&task);
				break;
			}

			case ONRTNEXERCISE:
			{
				this->processRtnExercise(&task);
				break;
			}

			case ONRSPQRYRATE:
			{
				this->processRspQryRate(&task);
				break;
			}

			case ONRSPQRYCLIENT:
			{
				this->processRspQryClient(&task);
				break;
			}

			case ONRSPQRYCLIENTMARGIN:
			{
				this->processRspQryClientMargin(&task);
				break;
			}

			case ONRSPQRYEXERCISE:
			{
				this->processRspQryExercise(&task);
				break;
			}

			case ONRTNWITHDRAWDEPOSIT:
			{
				this->processRtnWithdrawDeposit(&task);
				break;
			}

			case ONRSPMARGINCOMBACTION:
			{
				this->processRspMarginCombAction(&task);
				break;
			}

			case ONRTNMARGINCOMBACTION:
			{
				this->processRtnMarginCombAction(&task);
				break;
			}

			case ONRSPQRYSSECOMBPOSITION:
			{
				this->processRspQrySseCombPosition(&task);
				break;
			}

			case ONRSPCOMBEXERCISE:
			{
				this->processRspCombExercise(&task);
				break;
			}
			};
		}
	}
	catch (const TerminatedError&)
	{
	}
};

void StockTdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void StockTdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void StockTdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_id);
};

void StockTdApi::processRspSubscribeTopic(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcDisseminationField *task_data = (CStockFtdcDisseminationField*)task->task_data;
		data["SequenceSeries"] = task_data->SequenceSeries;
		data["SequenceNo"] = task_data->SequenceNo;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspSubscribeTopic(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspUserLoginField *task_data = (CStockFtdcRspUserLoginField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["MaxClOrdID"] = task_data->MaxClOrdID;
		data["UserID"] = toUtf(task_data->UserID);
		data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
		data["DataCenterID"] = task_data->DataCenterID;
		data["PrivateFlowSize"] = task_data->PrivateFlowSize;
		data["UserFlowSize"] = task_data->UserFlowSize;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspUserLogoutField *task_data = (CStockFtdcRspUserLogoutField*)task->task_data;
		data["UserID"] = toUtf(task_data->UserID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspUserPasswordUpdate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcUserPasswordUpdateField *task_data = (CStockFtdcUserPasswordUpdateField*)task->task_data;
		data["UserID"] = toUtf(task_data->UserID);
		data["OldPassword"] = toUtf(task_data->OldPassword);
		data["NewPassword"] = toUtf(task_data->NewPassword);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserPasswordUpdate(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspStockInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockInsertRspField *task_data = (CStockFtdcStockInsertRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdType"] = task_data->OrdType;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["Qty2"] = task_data->Qty2;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspStockInsert(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspStockCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockCancelRspField *task_data = (CStockFtdcStockCancelRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["OrigClOrdId"] = task_data->OrigClOrdId;
		data["Qty2"] = task_data->Qty2;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspStockCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspOptionsInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsInsertRspField *task_data = (CStockFtdcOptionsInsertRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["LeavesQty"] = task_data->LeavesQty;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOptionsInsert(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspOptionsCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsCancelRspField *task_data = (CStockFtdcOptionsCancelRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrigClOrdID"] = task_data->OrigClOrdID;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["LeavesQty"] = task_data->LeavesQty;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOptionsCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQuoteInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcQuoteInsertRspField *task_data = (CStockFtdcQuoteInsertRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		data["BidPx"] = task_data->BidPx;
		data["AskPx"] = task_data->AskPx;
		data["BidSize"] = task_data->BidSize;
		data["AskSize"] = task_data->AskSize;
		data["BidPositionEffect"] = task_data->BidPositionEffect;
		data["AskPositionEffect"] = task_data->AskPositionEffect;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQuoteInsert(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspForQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcForQuoteRspField *task_data = (CStockFtdcForQuoteRspField*)task->task_data;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspForQuote(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQuoteCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcQuoteCancelRspField *task_data = (CStockFtdcQuoteCancelRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrigClOrdID"] = task_data->OrigClOrdID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQuoteCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspStockLock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockLockRspField *task_data = (CStockFtdcStockLockRspField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspStockLock(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseRspField *task_data = (CStockFtdcExerciseRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspExercise(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspExerciseCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseCancelRspField *task_data = (CStockFtdcExerciseCancelRspField*)task->task_data;
		data["OrigClOrdID"] = task_data->OrigClOrdID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspExerciseCancel(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryPartAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspPartAccountField *task_data = (CStockFtdcRspPartAccountField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["PreBalance"] = task_data->PreBalance;
		data["Balance"] = task_data->Balance;
		data["Available"] = task_data->Available;
		data["CurrMargin"] = task_data->CurrMargin;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["CombMargin"] = task_data->CombMargin;
		data["Premium"] = task_data->Premium;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["Commi"] = task_data->Commi;
		data["FrozenCommi"] = task_data->FrozenCommi;
		data["CloseProfit"] = task_data->CloseProfit;
		data["PosiProfit"] = task_data->PosiProfit;
		data["Deposit"] = task_data->Deposit;
		data["Withdraw"] = task_data->Withdraw;
		data["BaseReserve"] = task_data->BaseReserve;
		data["SaveDouble1"] = task_data->SaveDouble1;
		data["SaveDouble2"] = task_data->SaveDouble2;
		data["SaveDouble3"] = task_data->SaveDouble3;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryPartAccount(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryStockOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryStockOrderField *task_data = (CStockFtdcRspQryStockOrderField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdType"] = task_data->OrdType;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["Qty2"] = task_data->Qty2;
		data["OrdStatus"] = task_data->OrdStatus;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryStockOrder(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryOptionsOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryOptionsOrderField *task_data = (CStockFtdcRspQryOptionsOrderField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ExecType"] = task_data->ExecType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["LeavesQty"] = task_data->LeavesQty;
		data["OwnerType"] = task_data->OwnerType;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["PositionEffect"] = task_data->PositionEffect;
		data["OrdType"] = task_data->OrdType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["UserID"] = toUtf(task_data->UserID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOptionsOrder(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryQuoteOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryQuoteOrderField *task_data = (CStockFtdcRspQryQuoteOrderField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdStatus"] = task_data->OrdStatus;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OwnerType"] = task_data->OwnerType;
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		data["BidPx"] = task_data->BidPx;
		data["AskPx"] = task_data->AskPx;
		data["BidSize"] = task_data->BidSize;
		data["AskSize"] = task_data->AskSize;
		data["BidPositionEffect"] = task_data->BidPositionEffect;
		data["AskPositionEffect"] = task_data->AskPositionEffect;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryQuoteOrder(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryStockTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockTradeField *task_data = (CStockFtdcStockTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["TradeVolume"] = task_data->TradeVolume;
		data["Side"] = task_data->Side;
		data["Cjjg"] = task_data->Cjjg;
		data["Cjje"] = task_data->Cjje;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryStockTrade(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryOptionsTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsTradeField *task_data = (CStockFtdcOptionsTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["ExecID"] = toUtf(task_data->ExecID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["LastPx"] = task_data->LastPx;
		data["LastQty"] = task_data->LastQty;
		data["LeavesQty"] = task_data->LeavesQty;
		data["Side"] = task_data->Side;
		data["PositionEffect"] = task_data->PositionEffect;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OrigTime"] = toUtf(task_data->OrigTime);
		data["ExecType"] = task_data->ExecType;
		data["OwnerType"] = task_data->OwnerType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["TotalValueTraded"] = task_data->TotalValueTraded;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOptionsTrade(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspPositionField *task_data = (CStockFtdcRspPositionField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Converd"] = task_data->Converd;
		data["Side"] = task_data->Side;
		data["YdPosition"] = task_data->YdPosition;
		data["Position"] = task_data->Position;
		data["TodayPosition"] = task_data->TodayPosition;
		data["BuyTradeVolume"] = task_data->BuyTradeVolume;
		data["SellTradeVolume"] = task_data->SellTradeVolume;
		data["PositionCost"] = task_data->PositionCost;
		data["YdPositionCost"] = task_data->YdPositionCost;
		data["UseMargin"] = task_data->UseMargin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryPosition(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryTopic(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcDisseminationField *task_data = (CStockFtdcDisseminationField*)task->task_data;
		data["SequenceSeries"] = task_data->SequenceSeries;
		data["SequenceNo"] = task_data->SequenceNo;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTopic(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryStock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryStockField *task_data = (CStockFtdcRspQryStockField*)task->task_data;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["contractmultiplierunit"] = task_data->contractmultiplierunit;
		data["startdate"] = toUtf(task_data->startdate);
		data["enddate"] = toUtf(task_data->enddate);
		data["totallongposition"] = task_data->totallongposition;
		data["securityclosepx"] = task_data->securityclosepx;
		data["settlprice"] = task_data->settlprice;
		data["underlyingclosepx"] = task_data->underlyingclosepx;
		data["dailypriceuplimit"] = task_data->dailypriceuplimit;
		data["dailypricedownlimit"] = task_data->dailypricedownlimit;
		data["marginunit"] = task_data->marginunit;
		data["marginratioparam1"] = task_data->marginratioparam1;
		data["marginratioparam2"] = task_data->marginratioparam2;
		data["roundlot"] = task_data->roundlot;
		data["lmtordminfloor"] = task_data->lmtordminfloor;
		data["lmtordmaxfloor"] = task_data->lmtordmaxfloor;
		data["mktordminfloor"] = task_data->mktordminfloor;
		data["mktordmaxfloor"] = task_data->mktordmaxfloor;
		data["ticksize"] = task_data->ticksize;
		data["lastprice"] = task_data->lastprice;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryStock(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryOptions(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryOptionsField *task_data = (CStockFtdcRspQryOptionsField*)task->task_data;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["contractid"] = toUtf(task_data->contractid);
		data["contractsymbol"] = toUtf(task_data->contractsymbol);
		data["underlyingsecurityid"] = toUtf(task_data->underlyingsecurityid);
		data["optiontype"] = task_data->optiontype;
		data["callorput"] = task_data->callorput;
		data["contractmultiplierunit"] = task_data->contractmultiplierunit;
		data["exerciseprice"] = task_data->exerciseprice;
		data["startdate"] = toUtf(task_data->startdate);
		data["enddate"] = toUtf(task_data->enddate);
		data["exercisedate"] = toUtf(task_data->exercisedate);
		data["deliverydate"] = toUtf(task_data->deliverydate);
		data["expiredate"] = toUtf(task_data->expiredate);
		data["totallongposition"] = task_data->totallongposition;
		data["securityclosepx"] = task_data->securityclosepx;
		data["settlprice"] = task_data->settlprice;
		data["underlyingclosepx"] = task_data->underlyingclosepx;
		data["dailypriceuplimit"] = task_data->dailypriceuplimit;
		data["dailypricedownlimit"] = task_data->dailypricedownlimit;
		data["marginunit"] = task_data->marginunit;
		data["marginratioparam1"] = task_data->marginratioparam1;
		data["marginratioparam2"] = task_data->marginratioparam2;
		data["roundlot"] = task_data->roundlot;
		data["lmtordminfloor"] = task_data->lmtordminfloor;
		data["lmtordmaxfloor"] = task_data->lmtordmaxfloor;
		data["mktordminfloor"] = task_data->mktordminfloor;
		data["mktordmaxfloor"] = task_data->mktordmaxfloor;
		data["ticksize"] = task_data->ticksize;
		data["lastprice"] = task_data->lastprice;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOptions(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRtnOptionsOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsOrderField *task_data = (CStockFtdcOptionsOrderField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["TradeQty"] = task_data->TradeQty;
		data["CancelQty"] = task_data->CancelQty;
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["DiscretionPrice"] = task_data->DiscretionPrice;
		data["PositionEffect"] = task_data->PositionEffect;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OwnerType"] = task_data->OwnerType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["OrdType"] = task_data->OrdType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OrdRejReason"] = task_data->OrdRejReason;
		delete task_data;
	}
	this->onRtnOptionsOrder(data);
};

void StockTdApi::processRtnStockOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockOrderField *task_data = (CStockFtdcStockOrderField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Price"] = task_data->Price;
		data["OrderQty"] = task_data->OrderQty;
		data["Side"] = task_data->Side;
		data["OrdStatus"] = task_data->OrdStatus;
		data["Qty2"] = task_data->Qty2;
		data["TradeQty"] = task_data->TradeQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OwnerType"] = task_data->OwnerType;
		data["TimeInForce"] = task_data->TimeInForce;
		data["OrdRejReason"] = task_data->OrdRejReason;
		delete task_data;
	}
	this->onRtnStockOrder(data);
};

void StockTdApi::processRtnQuoteOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcQuoteOrderField *task_data = (CStockFtdcQuoteOrderField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OrdStatus"] = task_data->OrdStatus;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OwnerType"] = task_data->OwnerType;
		data["QuoteReqID"] = toUtf(task_data->QuoteReqID);
		data["BidPx"] = task_data->BidPx;
		data["AskPx"] = task_data->AskPx;
		data["BidSize"] = task_data->BidSize;
		data["AskSize"] = task_data->AskSize;
		data["BidPositionEffect"] = task_data->BidPositionEffect;
		data["AskPositionEffect"] = task_data->AskPositionEffect;
		data["OrdRejReason"] = task_data->OrdRejReason;
		delete task_data;
	}
	this->onRtnQuoteOrder(data);
};

void StockTdApi::processRtnOptionsTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcOptionsTradeField *task_data = (CStockFtdcOptionsTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["ExecID"] = toUtf(task_data->ExecID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["LastPx"] = task_data->LastPx;
		data["LastQty"] = task_data->LastQty;
		data["LeavesQty"] = task_data->LeavesQty;
		data["Side"] = task_data->Side;
		data["PositionEffect"] = task_data->PositionEffect;
		data["CoveredOrUncovered"] = task_data->CoveredOrUncovered;
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OrigTime"] = toUtf(task_data->OrigTime);
		data["ExecType"] = task_data->ExecType;
		data["OwnerType"] = task_data->OwnerType;
		data["OrdStatus"] = task_data->OrdStatus;
		data["TotalValueTraded"] = task_data->TotalValueTraded;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	this->onRtnOptionsTrade(data);
};

void StockTdApi::processRtnStockTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcStockTradeField *task_data = (CStockFtdcStockTradeField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["InsertDate"] = toUtf(task_data->InsertDate);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["TradeVolume"] = task_data->TradeVolume;
		data["Side"] = task_data->Side;
		data["Cjjg"] = task_data->Cjjg;
		data["Cjje"] = task_data->Cjje;
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["ClOrdID"] = task_data->ClOrdID;
		delete task_data;
	}
	this->onRtnStockTrade(data);
};

void StockTdApi::processRtnExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseRtnField *task_data = (CStockFtdcExerciseRtnField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		delete task_data;
	}
	this->onRtnExercise(data);
};

void StockTdApi::processRspQryRate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryRateField *task_data = (CStockFtdcRspQryRateField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Margin"] = task_data->Margin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryRate(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryClient(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspClientField *task_data = (CStockFtdcRspClientField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["Status"] = task_data->Status;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClient(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryClientMargin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcRspQryClientMarginField *task_data = (CStockFtdcRspQryClientMarginField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["Margin"] = task_data->Margin;
		data["MarginRatio"] = task_data->MarginRatio;
		data["MinMarginRatio"] = task_data->MinMarginRatio;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClientMargin(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspQryExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcExerciseRtnField *task_data = (CStockFtdcExerciseRtnField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["SecurityID"] = toUtf(task_data->SecurityID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryExercise(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRtnWithdrawDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcWithdrawDepositRtnField *task_data = (CStockFtdcWithdrawDepositRtnField*)task->task_data;
		data["AccountID"] = toUtf(task_data->AccountID);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["deposit"] = task_data->deposit;
		data["withdraw"] = task_data->withdraw;
		delete task_data;
	}
	this->onRtnWithdrawDeposit(data);
};

void StockTdApi::processRspMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcMarginCombActionRspField *task_data = (CStockFtdcMarginCombActionRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["CombID"] = toUtf(task_data->CombID);
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspMarginCombAction(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRtnMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcMarginCombActionRtnField *task_data = (CStockFtdcMarginCombActionRtnField*)task->task_data;
		data["ClOrdID"] = task_data->ClOrdID;
		data["ExecID"] = toUtf(task_data->ExecID);
		data["CombID"] = toUtf(task_data->CombID);
		data["TransactTimeOnly"] = toUtf(task_data->TransactTimeOnly);
		data["OrigTime"] = toUtf(task_data->OrigTime);
		data["PartyID"] = toUtf(task_data->PartyID);
		data["LastQty"] = task_data->LastQty;
		data["commargin"] = task_data->commargin;
		delete task_data;
	}
	this->onRtnMarginCombAction(data);
};

void StockTdApi::processRspQrySseCombPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcCombPositionRspField *task_data = (CStockFtdcCombPositionRspField*)task->task_data;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["PosiQty"] = task_data->PosiQty;
		data["commargin"] = task_data->commargin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQrySseCombPosition(data, error, task->task_id, task->task_last);
};

void StockTdApi::processRspCombExercise(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CStockFtdcCombExerciseRspField *task_data = (CStockFtdcCombExerciseRspField*)task->task_data;
		data["OrderID"] = toUtf(task_data->OrderID);
		data["ClOrdID"] = task_data->ClOrdID;
		data["OwnerType"] = task_data->OwnerType;
		data["OrderQty"] = task_data->OrderQty;
		data["PartyID"] = toUtf(task_data->PartyID);
		data["LegSecurityID1"] = toUtf(task_data->LegSecurityID1);
		data["LegOrderQty1"] = task_data->LegOrderQty1;
		data["LegSecurityID2"] = toUtf(task_data->LegSecurityID2);
		data["LegOrderQty2"] = task_data->LegOrderQty2;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CStockFtdcRspInfoField *task_error = (CStockFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspCombExercise(data, error, task->task_id, task->task_last);
};

///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void StockTdApi::createStockTdApi(string flowPath)
{
	this->api = CNhStockTraderApi::CreateFtdcTraderApi(flowPath.c_str());
	this->api->RegisterSpi(this);
};

string StockTdApi::getVersion()
{
	int major, minor;
	return this->api->GetVersion(major, minor);
}

void StockTdApi::release()
{
	this->api->Release();
};

void StockTdApi::init(string localIp, string netWorkCard)
{
	this->active = true;
	this->task_thread = thread(&StockTdApi::processTask, this);

	this->api->Init(localIp.c_str(), netWorkCard.c_str());
};

int StockTdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string StockTdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

void StockTdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void StockTdApi::subscribePrivateTopic(int nType)
{
	this->api->SubscribePrivateTopic((SZSE_TE_RESUME_TYPE)nType);
};

void StockTdApi::subscribePublicTopic(int nType)
{
	this->api->SubscribePublicTopic((SZSE_TE_RESUME_TYPE)nType);
};

void StockTdApi::subscribeUserTopic(int nType)
{
	this->api->SubscribeUserTopic((SZSE_TE_RESUME_TYPE)nType);
};

int StockTdApi::reqSubscribeTopic(const dict &req, int reqid)
{
	CStockFtdcDisseminationField myreq = CStockFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	int i = this->api->ReqSubscribeTopic(&myreq, reqid);
	return i;
};

int StockTdApi::reqUserLogin(const dict &req, int reqid)
{
	CStockFtdcReqUserLoginField myreq = CStockFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "UserID", myreq.UserID);
	getString(req, "Password", myreq.Password);
	getString(req, "UserProductInfo", myreq.UserProductInfo);
	getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int StockTdApi::reqUserLogout(const dict &req, int reqid)
{
	CStockFtdcReqUserLogoutField myreq = CStockFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

int StockTdApi::reqUserPasswordUpdate(const dict &req, int reqid)
{
	CStockFtdcUserPasswordUpdateField myreq = CStockFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqUserPasswordUpdate(&myreq, reqid);
	return i;
};

int StockTdApi::reqStockInsert(const dict &req, int reqid)
{
	CStockFtdcStockInsertReqField myreq = CStockFtdcStockInsertReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getChar(req, "OrdType", &myreq.OrdType);
	getDouble(req, "Price", &myreq.Price);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getChar(req, "Side", &myreq.Side);
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getChar(req, "TimeInForce", &myreq.TimeInForce);
	int i = this->api->ReqStockInsert(&myreq, reqid);
	return i;
};

int StockTdApi::reqStockCancel(const dict &req, int reqid)
{
	CStockFtdcStockCancelReqField myreq = CStockFtdcStockCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqStockCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqStockLock(const dict &req, int reqid)
{
	CStockFtdcStockLockReqField myreq = CStockFtdcStockLockReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getChar(req, "Locked", &myreq.Locked);
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqStockLock(&myreq, reqid);
	return i;
};

int StockTdApi::reqOptionsInsert(const dict &req, int reqid)
{
	CStockFtdcOptionsInsertReqField myreq = CStockFtdcOptionsInsertReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getDouble(req, "Price", &myreq.Price);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getChar(req, "Side", &myreq.Side);
	getChar(req, "PositionEffect", &myreq.PositionEffect);
	getChar(req, "OrdType", &myreq.OrdType);
	getChar(req, "TimeInForce", &myreq.TimeInForce);
	getString(req, "PartyID", myreq.PartyID);

	int buf;
	getInt(req, "CoveredOrUncovered", &buf);
	myreq.CoveredOrUncovered = buf;

	int i = this->api->ReqOptionsInsert(&myreq, reqid);
	return i;
};

int StockTdApi::reqOptionsCancel(const dict &req, int reqid)
{
	CStockFtdcOptionsCancelReqField myreq = CStockFtdcOptionsCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqOptionsCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqQuoteInsert(const dict &req, int reqid)
{
	CStockFtdcQuoteInsertReqField myreq = CStockFtdcQuoteInsertReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "QuoteReqID", myreq.QuoteReqID);
	getDouble(req, "BidPx", &myreq.BidPx);
	getDouble(req, "AskPx", &myreq.AskPx);
	getInt(req, "BidSize", &myreq.BidSize);
	getInt(req, "AskSize", &myreq.AskSize);
	getChar(req, "BidPositionEffect", &myreq.BidPositionEffect);
	getChar(req, "AskPositionEffect", &myreq.AskPositionEffect);
	int i = this->api->ReqQuoteInsert(&myreq, reqid);
	return i;
};

int StockTdApi::reqQuoteCancel(const dict &req, int reqid)
{
	CStockFtdcQuoteCancelReqField myreq = CStockFtdcQuoteCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqQuoteCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqForQuote(const dict &req, int reqid)
{
	CStockFtdcForQuoteReqField myreq = CStockFtdcForQuoteReqField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "QuoteReqID", myreq.QuoteReqID);
	int i = this->api->ReqForQuote(&myreq, reqid);
	return i;
};

int StockTdApi::reqExercise(const dict &req, int reqid)
{
	CStockFtdcExerciseReqField myreq = CStockFtdcExerciseReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqExercise(&myreq, reqid);
	return i;
};

int StockTdApi::reqExerciseCancel(const dict &req, int reqid)
{
	CStockFtdcExerciseCancelReqField myreq = CStockFtdcExerciseCancelReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "OrigClOrdID", &myreq.OrigClOrdID);
	getString(req, "OrderID", myreq.OrderID);
	int i = this->api->ReqExerciseCancel(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryPartAccount(const dict &req, int reqid)
{
	CStockFtdcQryPartAccountField myreq = CStockFtdcQryPartAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqQryPartAccount(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryStockOrder(const dict &req, int reqid)
{
	CStockFtdcQryStockOrderField myreq = CStockFtdcQryStockOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryStockOrder(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryOptionsOrder(const dict &req, int reqid)
{
	CStockFtdcQryOptionsOrderField myreq = CStockFtdcQryOptionsOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryOptionsOrder(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryQuoteOrder(const dict &req, int reqid)
{
	CStockFtdcQryQuoteOrderField myreq = CStockFtdcQryQuoteOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryQuoteOrder(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryStockTrade(const dict &req, int reqid)
{
	CStockFtdcQryStockTradeField myreq = CStockFtdcQryStockTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	getString(req, "TradeID", myreq.TradeID);
	int i = this->api->ReqQryStockTrade(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryOptionsTrade(const dict &req, int reqid)
{
	CStockFtdcQryOptionsTradeField myreq = CStockFtdcQryOptionsTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	getString(req, "ExecID", myreq.ExecID);
	int i = this->api->ReqQryOptionsTrade(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryPosition(const dict &req, int reqid)
{
	CStockFtdcQryPositionField myreq = CStockFtdcQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryPosition(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryTopic(const dict &req, int reqid)
{
	CStockFtdcDisseminationField myreq = CStockFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	int i = this->api->ReqQryTopic(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryStock(const dict &req, int reqid)
{
	CStockFtdcQryStockField myreq = CStockFtdcQryStockField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryStock(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryOptions(const dict &req, int reqid)
{
	CStockFtdcQryOptionsField myreq = CStockFtdcQryOptionsField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryOptions(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryRate(const dict &req, int reqid)
{
	CStockFtdcQryRateField myreq = CStockFtdcQryRateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryRate(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryClient(int reqid)
{
	int i = this->api->ReqQryClient(reqid);
	return i;
};


int StockTdApi::reqQryClientMargin(const dict &req, int reqid)
{
	CStockFtdcQryClientMarginField myreq = CStockFtdcQryClientMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "SecurityID", myreq.SecurityID);
	int i = this->api->ReqQryClientMargin(&myreq, reqid);
	return i;
};

int StockTdApi::reqQryExercise(const dict &req, int reqid)
{
	CStockFtdcQryExerciseField myreq = CStockFtdcQryExerciseField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqQryExercise(&myreq, reqid);
	return i;
};

int StockTdApi::reqMarginCombAction(const dict &req, int reqid)
{
	CStockFtdcMarginCombActionField myreq = CStockFtdcMarginCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getString(req, "CombID", myreq.CombID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqMarginCombAction(&myreq, reqid);
	return i;
};

int StockTdApi::reqQrySseCombPosition(const dict &req, int reqid)
{
	CStockFtdcCombPositionField myreq = CStockFtdcCombPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "PartyID", myreq.PartyID);
	int i = this->api->ReqQrySseCombPosition(&myreq, reqid);
	return i;
};

int StockTdApi::reqCombExercise(const dict &req, int reqid)
{
	CStockFtdcCombExerciseReqField myreq = CStockFtdcCombExerciseReqField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "ClOrdID", &myreq.ClOrdID);
	getInt(req, "OwnerType", &myreq.OwnerType);
	getInt(req, "OrderQty", &myreq.OrderQty);
	getString(req, "PartyID", myreq.PartyID);
	getString(req, "LegSecurityID1", myreq.LegSecurityID1);
	getInt(req, "LegOrderQty1", &myreq.LegOrderQty1);
	getString(req, "LegSecurityID2", myreq.LegSecurityID2);
	getInt(req, "LegOrderQty2", &myreq.LegOrderQty2);
	int i = this->api->ReqCombExercise(&myreq, reqid);
	return i;
};

///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyStockTdApi : public StockTdApi
{
public:
	using StockTdApi::StockTdApi;

	void onFrontConnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onFrontConnected);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onFrontDisconnected(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onFrontDisconnected, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onHeartBeatWarning(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onHeartBeatWarning, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspSubscribeTopic(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspSubscribeTopic, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspUserLogin, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspUserLogout, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspUserPasswordUpdate, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspStockInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspStockInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspStockCancel(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspStockCancel, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspOptionsInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspOptionsInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspOptionsCancel(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspOptionsCancel, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQuoteInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspForQuote(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspForQuote, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQuoteCancel(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQuoteCancel, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspStockLock(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspStockLock, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspExercise(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspExercise, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspExerciseCancel(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspExerciseCancel, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryPartAccount(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryPartAccount, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryStockOrder(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryStockOrder, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryOptionsOrder(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryOptionsOrder, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryQuoteOrder(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryQuoteOrder, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryStockTrade(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryStockTrade, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryOptionsTrade(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryOptionsTrade, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryPosition, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryTopic(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryTopic, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryStock(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryStock, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryOptions(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryOptions, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnOptionsOrder(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnOptionsOrder, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnStockOrder(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnStockOrder, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnQuoteOrder(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnQuoteOrder, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnOptionsTrade(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnOptionsTrade, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnStockTrade(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnStockTrade, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnExercise(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnExercise, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryRate(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryRate, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryClient(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryClient, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryClientMargin(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryClientMargin, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryExercise(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQryExercise, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnWithdrawDeposit(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnWithdrawDeposit, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspMarginCombAction(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspMarginCombAction, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnMarginCombAction(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRtnMarginCombAction, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQrySseCombPosition(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspQrySseCombPosition, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspCombExercise(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, StockTdApi, onRspCombExercise, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vnnhstock, m)
{
	class_<StockTdApi, PyStockTdApi> StockTdApi(m, "StockTdApi", module_local());
	StockTdApi
		.def(init<>())
		.def("createStockTdApi", &StockTdApi::createStockTdApi)
		.def("getVersion", &StockTdApi::getVersion)
		.def("release", &StockTdApi::release)
		.def("init", &StockTdApi::init)
		.def("exit", &StockTdApi::exit)
		.def("getTradingDay", &StockTdApi::getTradingDay)
		.def("registerFront", &StockTdApi::registerFront)
		.def("subscribePrivateTopic", &StockTdApi::subscribePrivateTopic)
		.def("subscribePublicTopic", &StockTdApi::subscribePublicTopic)
		.def("subscribeUserTopic", &StockTdApi::subscribeUserTopic)
		.def("reqSubscribeTopic", &StockTdApi::reqSubscribeTopic)
		.def("reqUserLogin", &StockTdApi::reqUserLogin)
		.def("reqUserLogout", &StockTdApi::reqUserLogout)
		.def("reqUserPasswordUpdate", &StockTdApi::reqUserPasswordUpdate)
		.def("reqStockInsert", &StockTdApi::reqStockInsert)
		.def("reqStockCancel", &StockTdApi::reqStockCancel)
		.def("reqStockLock", &StockTdApi::reqStockLock)
		.def("reqOptionsInsert", &StockTdApi::reqOptionsInsert)
		.def("reqOptionsCancel", &StockTdApi::reqOptionsCancel)
		.def("reqQuoteInsert", &StockTdApi::reqQuoteInsert)
		.def("reqQuoteCancel", &StockTdApi::reqQuoteCancel)
		.def("reqForQuote", &StockTdApi::reqForQuote)
		.def("reqExercise", &StockTdApi::reqExercise)
		.def("reqExerciseCancel", &StockTdApi::reqExerciseCancel)
		.def("reqQryPartAccount", &StockTdApi::reqQryPartAccount)
		.def("reqQryStockOrder", &StockTdApi::reqQryStockOrder)
		.def("reqQryOptionsOrder", &StockTdApi::reqQryOptionsOrder)
		.def("reqQryQuoteOrder", &StockTdApi::reqQryQuoteOrder)
		.def("reqQryStockTrade", &StockTdApi::reqQryStockTrade)
		.def("reqQryOptionsTrade", &StockTdApi::reqQryOptionsTrade)
		.def("reqQryPosition", &StockTdApi::reqQryPosition)
		.def("reqQryTopic", &StockTdApi::reqQryTopic)
		.def("reqQryStock", &StockTdApi::reqQryStock)
		.def("reqQryOptions", &StockTdApi::reqQryOptions)
		.def("reqQryRate", &StockTdApi::reqQryRate)
		.def("reqQryClient", &StockTdApi::reqQryClient)
		.def("reqQryClientMargin", &StockTdApi::reqQryClientMargin)
		.def("reqQryExercise", &StockTdApi::reqQryExercise)
		.def("reqMarginCombAction", &StockTdApi::reqMarginCombAction)
		.def("reqQrySseCombPosition", &StockTdApi::reqQrySseCombPosition)
		.def("reqCombExercise", &StockTdApi::reqCombExercise)

		.def("onFrontConnected", &StockTdApi::onFrontConnected)
		.def("onFrontDisconnected", &StockTdApi::onFrontDisconnected)
		.def("onHeartBeatWarning", &StockTdApi::onHeartBeatWarning)
		.def("onRspSubscribeTopic", &StockTdApi::onRspSubscribeTopic)
		.def("onRspUserLogin", &StockTdApi::onRspUserLogin)
		.def("onRspUserLogout", &StockTdApi::onRspUserLogout)
		.def("onRspUserPasswordUpdate", &StockTdApi::onRspUserPasswordUpdate)
		.def("onRspStockInsert", &StockTdApi::onRspStockInsert)
		.def("onRspStockCancel", &StockTdApi::onRspStockCancel)
		.def("onRspOptionsInsert", &StockTdApi::onRspOptionsInsert)
		.def("onRspOptionsCancel", &StockTdApi::onRspOptionsCancel)
		.def("onRspQuoteInsert", &StockTdApi::onRspQuoteInsert)
		.def("onRspForQuote", &StockTdApi::onRspForQuote)
		.def("onRspQuoteCancel", &StockTdApi::onRspQuoteCancel)
		.def("onRspStockLock", &StockTdApi::onRspStockLock)
		.def("onRspExercise", &StockTdApi::onRspExercise)
		.def("onRspExerciseCancel", &StockTdApi::onRspExerciseCancel)
		.def("onRspQryPartAccount", &StockTdApi::onRspQryPartAccount)
		.def("onRspQryStockOrder", &StockTdApi::onRspQryStockOrder)
		.def("onRspQryOptionsOrder", &StockTdApi::onRspQryOptionsOrder)
		.def("onRspQryQuoteOrder", &StockTdApi::onRspQryQuoteOrder)
		.def("onRspQryStockTrade", &StockTdApi::onRspQryStockTrade)
		.def("onRspQryOptionsTrade", &StockTdApi::onRspQryOptionsTrade)
		.def("onRspQryPosition", &StockTdApi::onRspQryPosition)
		.def("onRspQryTopic", &StockTdApi::onRspQryTopic)
		.def("onRspQryStock", &StockTdApi::onRspQryStock)
		.def("onRspQryOptions", &StockTdApi::onRspQryOptions)
		.def("onRtnOptionsOrder", &StockTdApi::onRtnOptionsOrder)
		.def("onRtnStockOrder", &StockTdApi::onRtnStockOrder)
		.def("onRtnQuoteOrder", &StockTdApi::onRtnQuoteOrder)
		.def("onRtnOptionsTrade", &StockTdApi::onRtnOptionsTrade)
		.def("onRtnStockTrade", &StockTdApi::onRtnStockTrade)
		.def("onRtnExercise", &StockTdApi::onRtnExercise)
		.def("onRspQryRate", &StockTdApi::onRspQryRate)
		.def("onRspQryClient", &StockTdApi::onRspQryClient)
		.def("onRspQryClientMargin", &StockTdApi::onRspQryClientMargin)
		.def("onRspQryExercise", &StockTdApi::onRspQryExercise)
		.def("onRtnWithdrawDeposit", &StockTdApi::onRtnWithdrawDeposit)
		.def("onRspMarginCombAction", &StockTdApi::onRspMarginCombAction)
		.def("onRtnMarginCombAction", &StockTdApi::onRtnMarginCombAction)
		.def("onRspQrySseCombPosition", &StockTdApi::onRspQrySseCombPosition)
		.def("onRspCombExercise", &StockTdApi::onRspCombExercise)
		;
}
