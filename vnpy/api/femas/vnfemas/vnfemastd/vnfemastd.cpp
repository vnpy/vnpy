// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnfemastd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

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









///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void TdApi::processTask()
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

			case ONQRYFRONTCONNECTED:
			{
				this->processQryFrontConnected(&task);
				break;
			}

			case ONFRONTDISCONNECTED:
			{
				this->processFrontDisconnected(&task);
				break;
			}

			case ONQRYFRONTDISCONNECTED:
			{
				this->processQryFrontDisconnected(&task);
				break;
			}

			case ONHEARTBEATWARNING:
			{
				this->processHeartBeatWarning(&task);
				break;
			}

			case ONPACKAGESTART:
			{
				this->processPackageStart(&task);
				break;
			}

			case ONPACKAGEEND:
			{
				this->processPackageEnd(&task);
				break;
			}

			case ONRSPERROR:
			{
				this->processRspError(&task);
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

			case ONRSPORDERINSERT:
			{
				this->processRspOrderInsert(&task);
				break;
			}

			case ONRSPORDERACTION:
			{
				this->processRspOrderAction(&task);
				break;
			}

			case ONRSPQUOTEINSERT:
			{
				this->processRspQuoteInsert(&task);
				break;
			}

			case ONRSPQUOTEACTION:
			{
				this->processRspQuoteAction(&task);
				break;
			}

			case ONRSPFORQUOTE:
			{
				this->processRspForQuote(&task);
				break;
			}

			case ONRSPMARGINCOMBACTION:
			{
				this->processRspMarginCombAction(&task);
				break;
			}

			case ONRSPUSERDEPOSIT:
			{
				this->processRspUserDeposit(&task);
				break;
			}

			case ONRTNFLOWMESSAGECANCEL:
			{
				this->processRtnFlowMessageCancel(&task);
				break;
			}

			case ONRTNTRADE:
			{
				this->processRtnTrade(&task);
				break;
			}

			case ONRTNORDER:
			{
				this->processRtnOrder(&task);
				break;
			}

			case ONERRRTNORDERINSERT:
			{
				this->processErrRtnOrderInsert(&task);
				break;
			}

			case ONERRRTNORDERACTION:
			{
				this->processErrRtnOrderAction(&task);
				break;
			}

			case ONRTNINSTRUMENTSTATUS:
			{
				this->processRtnInstrumentStatus(&task);
				break;
			}

			case ONRTNINVESTORACCOUNTDEPOSIT:
			{
				this->processRtnInvestorAccountDeposit(&task);
				break;
			}

			case ONRTNQUOTE:
			{
				this->processRtnQuote(&task);
				break;
			}

			case ONERRRTNQUOTEINSERT:
			{
				this->processErrRtnQuoteInsert(&task);
				break;
			}

			case ONERRRTNQUOTEACTION:
			{
				this->processErrRtnQuoteAction(&task);
				break;
			}

			case ONRTNFORQUOTE:
			{
				this->processRtnForQuote(&task);
				break;
			}

			case ONRTNMARGINCOMBINATIONLEG:
			{
				this->processRtnMarginCombinationLeg(&task);
				break;
			}

			case ONRTNMARGINCOMBACTION:
			{
				this->processRtnMarginCombAction(&task);
				break;
			}

			case ONRTNUSERDEPOSIT:
			{
				this->processRtnUserDeposit(&task);
				break;
			}

			case ONRSPQUERYUSERLOGIN:
			{
				this->processRspQueryUserLogin(&task);
				break;
			}

			case ONRSPQRYORDER:
			{
				this->processRspQryOrder(&task);
				break;
			}

			case ONRSPQRYTRADE:
			{
				this->processRspQryTrade(&task);
				break;
			}

			case ONRSPQRYUSERINVESTOR:
			{
				this->processRspQryUserInvestor(&task);
				break;
			}

			case ONRSPQRYTRADINGCODE:
			{
				this->processRspQryTradingCode(&task);
				break;
			}

			case ONRSPQRYINVESTORACCOUNT:
			{
				this->processRspQryInvestorAccount(&task);
				break;
			}

			case ONRSPQRYINSTRUMENT:
			{
				this->processRspQryInstrument(&task);
				break;
			}

			case ONRSPQRYEXCHANGE:
			{
				this->processRspQryExchange(&task);
				break;
			}

			case ONRSPQRYINVESTORPOSITION:
			{
				this->processRspQryInvestorPosition(&task);
				break;
			}

			case ONRSPQRYCOMPLIANCEPARAM:
			{
				this->processRspQryComplianceParam(&task);
				break;
			}

			case ONRSPQRYINVESTORFEE:
			{
				this->processRspQryInvestorFee(&task);
				break;
			}

			case ONRSPQRYINVESTORMARGIN:
			{
				this->processRspQryInvestorMargin(&task);
				break;
			}

			case ONRSPQRYINVESTORCOMBPOSITION:
			{
				this->processRspQryInvestorCombPosition(&task);
				break;
			}

			case ONRSPQRYINVESTORLEGPOSITION:
			{
				this->processRspQryInvestorLegPosition(&task);
				break;
			}

			case ONRSPQRYINSTRUMENTGROUP:
			{
				this->processRspQryInstrumentGroup(&task);
				break;
			}

			case ONRSPQRYCLIENTMARGINCOMBTYPE:
			{
				this->processRspQryClientMarginCombType(&task);
				break;
			}

			case ONRSPEXECORDERINSERT:
			{
				this->processRspExecOrderInsert(&task);
				break;
			}

			case ONRSPEXECORDERACTION:
			{
				this->processRspExecOrderAction(&task);
				break;
			}

			case ONRTNEXECORDER:
			{
				this->processRtnExecOrder(&task);
				break;
			}

			case ONERRRTNEXECORDERINSERT:
			{
				this->processErrRtnExecOrderInsert(&task);
				break;
			}

			case ONERRRTNEXECORDERACTION:
			{
				this->processErrRtnExecOrderAction(&task);
				break;
			}

			case ONRTNTRANSFERMONEY:
			{
				this->processRtnTransferMoney(&task);
				break;
			}

			case ONRSPQRYSYSTEMTIME:
			{
				this->processRspQrySystemTime(&task);
				break;
			}

			case ONRSPQRYMARGINPREFPARAM:
			{
				this->processRspQryMarginPrefParam(&task);
				break;
			}

			case ONRSPDSUSERCERTIFICATION:
			{
				this->processRspDSUserCertification(&task);
				break;
			}

			case ONRSPDSPROXYSUBMITINFO:
			{
				this->processRspDSProxySubmitInfo(&task);
				break;
			}


			}
		}
	}
	catch (const TerminatedError&)
    {
    }
};

void TdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void TdApi::processQryFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onQryFrontConnected();
};

void TdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void TdApi::processQryFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onQryFrontDisconnected(task->task_id);
};

void TdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_id);
};

void TdApi::processPackageStart(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageStart(task->task_id);
};

void TdApi::processPackageEnd(Task *task)
{
	gil_scoped_acquire acquire;
	this->onPackageEnd(task->task_id);
};

void TdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspError(error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserLoginField *task_data = (CUstpFtdcRspUserLoginField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["ExchangeTime"] = toUtf(task_data->ExchangeTime);
		data["MaxOrderLocalID"] = toUtf(task_data->MaxOrderLocalID);
		data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
		data["DataCenterID"] = task_data->DataCenterID;
		data["PrivateFlowSize"] = task_data->PrivateFlowSize;
		data["UserFlowSize"] = task_data->UserFlowSize;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["FemasVersion"] = toUtf(task_data->FemasVersion);
		data["FemasLifeCycle"] = task_data->FemasLifeCycle;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserLogoutField *task_data = (CUstpFtdcRspUserLogoutField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserPasswordUpdate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcUserPasswordUpdateField *task_data = (CUstpFtdcUserPasswordUpdateField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OldPassword"] = toUtf(task_data->OldPassword);
		data["NewPassword"] = toUtf(task_data->NewPassword);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserPasswordUpdate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputOrderField *task_data = (CUstpFtdcInputOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderActionField *task_data = (CUstpFtdcOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQuoteInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputQuoteField *task_data = (CUstpFtdcInputQuoteField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["QuoteLocalID"] = toUtf(task_data->QuoteLocalID);
		data["BidVolume"] = task_data->BidVolume;
		data["BidOffsetFlag"] = task_data->BidOffsetFlag;
		data["BidHedgeFlag"] = task_data->BidHedgeFlag;
		data["BidPrice"] = task_data->BidPrice;
		data["AskVolume"] = task_data->AskVolume;
		data["AskOffsetFlag"] = task_data->AskOffsetFlag;
		data["AskHedgeFlag"] = task_data->AskHedgeFlag;
		data["AskPrice"] = task_data->AskPrice;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BidUserOrderLocalID"] = toUtf(task_data->BidUserOrderLocalID);
		data["AskUserOrderLocalID"] = toUtf(task_data->AskUserOrderLocalID);
		data["BidOrderLocalID"] = toUtf(task_data->BidOrderLocalID);
		data["AskOrderLocalID"] = toUtf(task_data->AskOrderLocalID);
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["StandByTime"] = task_data->StandByTime;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQuoteInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQuoteAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcQuoteActionField *task_data = (CUstpFtdcQuoteActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["UserQuoteActionLocalID"] = toUtf(task_data->UserQuoteActionLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["Direction"] = task_data->Direction;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQuoteAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspForQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcReqForQuoteField *task_data = (CUstpFtdcReqForQuoteField*)task->task_data;
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ReqForQuoteTime"] = toUtf(task_data->ReqForQuoteTime);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspForQuote(data, error, task->task_id, task->task_last);
};

void TdApi::processRspMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputMarginCombActionField *task_data = (CUstpFtdcInputMarginCombActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["UserActionLocalID"] = toUtf(task_data->UserActionLocalID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["CombVolume"] = task_data->CombVolume;
		data["CombDirection"] = task_data->CombDirection;
		data["ActionLocalID"] = toUtf(task_data->ActionLocalID);
		data["Direction"] = task_data->Direction;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["CombActionStatus"] = task_data->CombActionStatus;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspMarginCombAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcstpUserDepositField *task_data = (CUstpFtdcstpUserDepositField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["Amount"] = task_data->Amount;
		data["AmountDirection"] = task_data->AmountDirection;
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspUserDeposit(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnFlowMessageCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcFlowMessageCancelField *task_data = (CUstpFtdcFlowMessageCancelField*)task->task_data;
		data["SequenceSeries"] = task_data->SequenceSeries;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["DataCenterID"] = task_data->DataCenterID;
		data["StartSequenceNo"] = task_data->StartSequenceNo;
		data["EndSequenceNo"] = task_data->EndSequenceNo;
		delete task->task_data;
	}
	this->onRtnFlowMessageCancel(data);
};

void TdApi::processRtnTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcTradeField *task_data = (CUstpFtdcTradeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["TradePrice"] = task_data->TradePrice;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["ClearingPartID"] = toUtf(task_data->ClearingPartID);
		data["UsedFee"] = task_data->UsedFee;
		data["UsedMargin"] = task_data->UsedMargin;
		data["Premium"] = task_data->Premium;
		data["Position"] = task_data->Position;
		data["PositionCost"] = task_data->PositionCost;
		data["Available"] = task_data->Available;
		data["Margin"] = task_data->Margin;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ArbiInstrumentID"] = toUtf(task_data->ArbiInstrumentID);
		delete task->task_data;
	}
	this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderField *task_data = (CUstpFtdcOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderSource"] = task_data->OrderSource;
		data["OrderStatus"] = task_data->OrderStatus;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["CancelUserID"] = toUtf(task_data->CancelUserID);
		data["VolumeTraded"] = task_data->VolumeTraded;
		data["VolumeRemain"] = task_data->VolumeRemain;
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		delete task->task_data;
	}
	this->onRtnOrder(data);
};

void TdApi::processErrRtnOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputOrderField *task_data = (CUstpFtdcInputOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderActionField *task_data = (CUstpFtdcOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInstrumentStatusField *task_data = (CUstpFtdcInstrumentStatusField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["ProductName"] = toUtf(task_data->ProductName);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentName"] = toUtf(task_data->InstrumentName);
		data["DeliveryYear"] = task_data->DeliveryYear;
		data["DeliveryMonth"] = task_data->DeliveryMonth;
		data["MaxLimitOrderVolume"] = task_data->MaxLimitOrderVolume;
		data["MinLimitOrderVolume"] = task_data->MinLimitOrderVolume;
		data["MaxMarketOrderVolume"] = task_data->MaxMarketOrderVolume;
		data["MinMarketOrderVolume"] = task_data->MinMarketOrderVolume;
		data["VolumeMultiple"] = task_data->VolumeMultiple;
		data["PriceTick"] = task_data->PriceTick;
		data["Currency"] = task_data->Currency;
		data["LongPosLimit"] = task_data->LongPosLimit;
		data["ShortPosLimit"] = task_data->ShortPosLimit;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["InstrumentStatus"] = task_data->InstrumentStatus;
		data["CreateDate"] = toUtf(task_data->CreateDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["ExpireDate"] = toUtf(task_data->ExpireDate);
		data["StartDelivDate"] = toUtf(task_data->StartDelivDate);
		data["EndDelivDate"] = toUtf(task_data->EndDelivDate);
		data["BasisPrice"] = task_data->BasisPrice;
		data["IsTrading"] = task_data->IsTrading;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["UnderlyingMultiple"] = task_data->UnderlyingMultiple;
		data["PositionType"] = task_data->PositionType;
		data["StrikePrice"] = task_data->StrikePrice;
		data["OptionsType"] = task_data->OptionsType;
		data["CurrencyID"] = toUtf(task_data->CurrencyID);
		data["ArbiType"] = task_data->ArbiType;
		data["InstrumentID_1"] = toUtf(task_data->InstrumentID_1);
		data["Direction_1"] = task_data->Direction_1;
		data["Ratio_1"] = task_data->Ratio_1;
		data["InstrumentID_2"] = toUtf(task_data->InstrumentID_2);
		data["Direction_2"] = task_data->Direction_2;
		data["Ratio_2"] = task_data->Ratio_2;
		data["EnterDate"] = toUtf(task_data->EnterDate);
		delete task->task_data;
	}
	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnInvestorAccountDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInvestorAccountDepositResField *task_data = (CUstpFtdcInvestorAccountDepositResField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["AccountSeqNo"] = toUtf(task_data->AccountSeqNo);
		data["Amount"] = task_data->Amount;
		data["AmountDirection"] = task_data->AmountDirection;
		data["Available"] = task_data->Available;
		data["Balance"] = task_data->Balance;
		delete task->task_data;
	}
	this->onRtnInvestorAccountDeposit(data);
};

void TdApi::processRtnQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRtnQuoteField *task_data = (CUstpFtdcRtnQuoteField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["QuoteLocalID"] = toUtf(task_data->QuoteLocalID);
		data["BidVolume"] = task_data->BidVolume;
		data["BidOffsetFlag"] = task_data->BidOffsetFlag;
		data["BidHedgeFlag"] = task_data->BidHedgeFlag;
		data["BidPrice"] = task_data->BidPrice;
		data["AskVolume"] = task_data->AskVolume;
		data["AskOffsetFlag"] = task_data->AskOffsetFlag;
		data["AskHedgeFlag"] = task_data->AskHedgeFlag;
		data["AskPrice"] = task_data->AskPrice;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BidUserOrderLocalID"] = toUtf(task_data->BidUserOrderLocalID);
		data["AskUserOrderLocalID"] = toUtf(task_data->AskUserOrderLocalID);
		data["BidOrderLocalID"] = toUtf(task_data->BidOrderLocalID);
		data["AskOrderLocalID"] = toUtf(task_data->AskOrderLocalID);
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["StandByTime"] = task_data->StandByTime;
		data["BidOrderSysID"] = toUtf(task_data->BidOrderSysID);
		data["AskOrderSysID"] = toUtf(task_data->AskOrderSysID);
		data["QuoteStatus"] = task_data->QuoteStatus;
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	this->onRtnQuote(data);
};

void TdApi::processErrRtnQuoteInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputQuoteField *task_data = (CUstpFtdcInputQuoteField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["QuoteLocalID"] = toUtf(task_data->QuoteLocalID);
		data["BidVolume"] = task_data->BidVolume;
		data["BidOffsetFlag"] = task_data->BidOffsetFlag;
		data["BidHedgeFlag"] = task_data->BidHedgeFlag;
		data["BidPrice"] = task_data->BidPrice;
		data["AskVolume"] = task_data->AskVolume;
		data["AskOffsetFlag"] = task_data->AskOffsetFlag;
		data["AskHedgeFlag"] = task_data->AskHedgeFlag;
		data["AskPrice"] = task_data->AskPrice;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BidUserOrderLocalID"] = toUtf(task_data->BidUserOrderLocalID);
		data["AskUserOrderLocalID"] = toUtf(task_data->AskUserOrderLocalID);
		data["BidOrderLocalID"] = toUtf(task_data->BidOrderLocalID);
		data["AskOrderLocalID"] = toUtf(task_data->AskOrderLocalID);
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["StandByTime"] = task_data->StandByTime;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnQuoteInsert(data, error);
};

void TdApi::processErrRtnQuoteAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcQuoteActionField *task_data = (CUstpFtdcQuoteActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["QuoteSysID"] = toUtf(task_data->QuoteSysID);
		data["UserQuoteLocalID"] = toUtf(task_data->UserQuoteLocalID);
		data["UserQuoteActionLocalID"] = toUtf(task_data->UserQuoteActionLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["Direction"] = task_data->Direction;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnQuoteAction(data, error);
};

void TdApi::processRtnForQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcReqForQuoteField *task_data = (CUstpFtdcReqForQuoteField*)task->task_data;
		data["ReqForQuoteID"] = toUtf(task_data->ReqForQuoteID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ReqForQuoteTime"] = toUtf(task_data->ReqForQuoteTime);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task->task_data;
	}
	this->onRtnForQuote(data);
};

void TdApi::processRtnMarginCombinationLeg(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcMarginCombinationLegField *task_data = (CUstpFtdcMarginCombinationLegField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["LegID"] = task_data->LegID;
		data["LegInstrumentID"] = toUtf(task_data->LegInstrumentID);
		data["Direction"] = task_data->Direction;
		data["LegMultiple"] = task_data->LegMultiple;
		data["Priority"] = task_data->Priority;
		delete task->task_data;
	}
	this->onRtnMarginCombinationLeg(data);
};

void TdApi::processRtnMarginCombAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputMarginCombActionField *task_data = (CUstpFtdcInputMarginCombActionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["UserActionLocalID"] = toUtf(task_data->UserActionLocalID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["CombVolume"] = task_data->CombVolume;
		data["CombDirection"] = task_data->CombDirection;
		data["ActionLocalID"] = toUtf(task_data->ActionLocalID);
		data["Direction"] = task_data->Direction;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["CombActionStatus"] = task_data->CombActionStatus;
		delete task->task_data;
	}
	this->onRtnMarginCombAction(data);
};

void TdApi::processRtnUserDeposit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcstpUserDepositField *task_data = (CUstpFtdcstpUserDepositField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["Amount"] = task_data->Amount;
		data["AmountDirection"] = task_data->AmountDirection;
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		delete task->task_data;
	}
	this->onRtnUserDeposit(data);
};

void TdApi::processRspQueryUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserLoginField *task_data = (CUstpFtdcRspUserLoginField*)task->task_data;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["ExchangeTime"] = toUtf(task_data->ExchangeTime);
		data["MaxOrderLocalID"] = toUtf(task_data->MaxOrderLocalID);
		data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
		data["DataCenterID"] = task_data->DataCenterID;
		data["PrivateFlowSize"] = task_data->PrivateFlowSize;
		data["UserFlowSize"] = task_data->UserFlowSize;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["FemasVersion"] = toUtf(task_data->FemasVersion);
		data["FemasLifeCycle"] = task_data->FemasLifeCycle;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQueryUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcOrderField *task_data = (CUstpFtdcOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["SeatNo"] = task_data->SeatNo;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderPriceType"] = task_data->OrderPriceType;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["LimitPrice"] = task_data->LimitPrice;
		data["Volume"] = task_data->Volume;
		data["TimeCondition"] = task_data->TimeCondition;
		data["GTDDate"] = toUtf(task_data->GTDDate);
		data["VolumeCondition"] = task_data->VolumeCondition;
		data["MinVolume"] = task_data->MinVolume;
		data["StopPrice"] = task_data->StopPrice;
		data["ForceCloseReason"] = task_data->ForceCloseReason;
		data["IsAutoSuspend"] = task_data->IsAutoSuspend;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderSource"] = task_data->OrderSource;
		data["OrderStatus"] = task_data->OrderStatus;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["CancelUserID"] = toUtf(task_data->CancelUserID);
		data["VolumeTraded"] = task_data->VolumeTraded;
		data["VolumeRemain"] = task_data->VolumeRemain;
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcTradeField *task_data = (CUstpFtdcTradeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["UserID"] = toUtf(task_data->UserID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["TradeID"] = toUtf(task_data->TradeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["TradePrice"] = task_data->TradePrice;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradeTime"] = toUtf(task_data->TradeTime);
		data["ClearingPartID"] = toUtf(task_data->ClearingPartID);
		data["UsedFee"] = task_data->UsedFee;
		data["UsedMargin"] = task_data->UsedMargin;
		data["Premium"] = task_data->Premium;
		data["Position"] = task_data->Position;
		data["PositionCost"] = task_data->PositionCost;
		data["Available"] = task_data->Available;
		data["Margin"] = task_data->Margin;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["ArbiType"] = task_data->ArbiType;
		data["ArbiInstrumentID"] = toUtf(task_data->ArbiInstrumentID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryUserInvestor(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspUserInvestorField *task_data = (CUstpFtdcRspUserInvestorField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryUserInvestor(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTradingCode(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspTradingCodeField *task_data = (CUstpFtdcRspTradingCodeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ClientRight"] = task_data->ClientRight;
		data["ClientHedgeFlag"] = task_data->ClientHedgeFlag;
		data["IsActive"] = task_data->IsActive;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryTradingCode(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorAccountField *task_data = (CUstpFtdcRspInvestorAccountField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["PreBalance"] = task_data->PreBalance;
		data["Deposit"] = task_data->Deposit;
		data["Withdraw"] = task_data->Withdraw;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["FrozenFee"] = task_data->FrozenFee;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["Fee"] = task_data->Fee;
		data["CloseProfit"] = task_data->CloseProfit;
		data["PositionProfit"] = task_data->PositionProfit;
		data["Available"] = task_data->Available;
		data["LongFrozenMargin"] = task_data->LongFrozenMargin;
		data["ShortFrozenMargin"] = task_data->ShortFrozenMargin;
		data["LongMargin"] = task_data->LongMargin;
		data["ShortMargin"] = task_data->ShortMargin;
		data["ReleaseMargin"] = task_data->ReleaseMargin;
		data["DynamicRights"] = task_data->DynamicRights;
		data["TodayInOut"] = task_data->TodayInOut;
		data["Margin"] = task_data->Margin;
		data["Premium"] = task_data->Premium;
		data["Risk"] = task_data->Risk;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInstrument(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInstrumentField *task_data = (CUstpFtdcRspInstrumentField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["ProductName"] = toUtf(task_data->ProductName);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentName"] = toUtf(task_data->InstrumentName);
		data["DeliveryYear"] = task_data->DeliveryYear;
		data["DeliveryMonth"] = task_data->DeliveryMonth;
		data["MaxLimitOrderVolume"] = task_data->MaxLimitOrderVolume;
		data["MinLimitOrderVolume"] = task_data->MinLimitOrderVolume;
		data["MaxMarketOrderVolume"] = task_data->MaxMarketOrderVolume;
		data["MinMarketOrderVolume"] = task_data->MinMarketOrderVolume;
		data["VolumeMultiple"] = task_data->VolumeMultiple;
		data["PriceTick"] = task_data->PriceTick;
		data["Currency"] = task_data->Currency;
		data["LongPosLimit"] = task_data->LongPosLimit;
		data["ShortPosLimit"] = task_data->ShortPosLimit;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["InstrumentStatus"] = task_data->InstrumentStatus;
		data["CreateDate"] = toUtf(task_data->CreateDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["ExpireDate"] = toUtf(task_data->ExpireDate);
		data["StartDelivDate"] = toUtf(task_data->StartDelivDate);
		data["EndDelivDate"] = toUtf(task_data->EndDelivDate);
		data["BasisPrice"] = task_data->BasisPrice;
		data["IsTrading"] = task_data->IsTrading;
		data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
		data["UnderlyingMultiple"] = task_data->UnderlyingMultiple;
		data["PositionType"] = task_data->PositionType;
		data["StrikePrice"] = task_data->StrikePrice;
		data["OptionsType"] = task_data->OptionsType;
		data["CurrencyID"] = toUtf(task_data->CurrencyID);
		data["ArbiType"] = task_data->ArbiType;
		data["InstrumentID_1"] = toUtf(task_data->InstrumentID_1);
		data["Direction_1"] = task_data->Direction_1;
		data["Ratio_1"] = task_data->Ratio_1;
		data["InstrumentID_2"] = toUtf(task_data->InstrumentID_2);
		data["Direction_2"] = task_data->Direction_2;
		data["Ratio_2"] = task_data->Ratio_2;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInstrument(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryExchange(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspExchangeField *task_data = (CUstpFtdcRspExchangeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ExchangeName"] = toUtf(task_data->ExchangeName);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryExchange(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorPositionField *task_data = (CUstpFtdcRspInvestorPositionField*)task->task_data;
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Direction"] = task_data->Direction;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["UsedMargin"] = task_data->UsedMargin;
		data["Position"] = task_data->Position;
		data["PositionCost"] = task_data->PositionCost;
		data["YdPosition"] = task_data->YdPosition;
		data["YdPositionCost"] = task_data->YdPositionCost;
		data["FrozenMargin"] = task_data->FrozenMargin;
		data["FrozenPosition"] = task_data->FrozenPosition;
		data["FrozenClosing"] = task_data->FrozenClosing;
		data["YdFrozenClosing"] = task_data->YdFrozenClosing;
		data["FrozenPremium"] = task_data->FrozenPremium;
		data["LastTradeID"] = toUtf(task_data->LastTradeID);
		data["LastOrderLocalID"] = toUtf(task_data->LastOrderLocalID);
		data["SpeculationPosition"] = task_data->SpeculationPosition;
		data["ArbitragePosition"] = task_data->ArbitragePosition;
		data["HedgePosition"] = task_data->HedgePosition;
		data["SpecFrozenClosing"] = task_data->SpecFrozenClosing;
		data["HedgeFrozenClosing"] = task_data->HedgeFrozenClosing;
		data["Currency"] = toUtf(task_data->Currency);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryComplianceParam(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspComplianceParamField *task_data = (CUstpFtdcRspComplianceParamField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["DailyMaxOrder"] = task_data->DailyMaxOrder;
		data["DailyMaxOrderAction"] = task_data->DailyMaxOrderAction;
		data["DailyMaxErrorOrder"] = task_data->DailyMaxErrorOrder;
		data["DailyMaxOrderVolume"] = task_data->DailyMaxOrderVolume;
		data["DailyMaxOrderActionVolume"] = task_data->DailyMaxOrderActionVolume;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryComplianceParam(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorFee(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInvestorFeeField *task_data = (CUstpFtdcInvestorFeeField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["OpenFeeRate"] = task_data->OpenFeeRate;
		data["OpenFeeAmt"] = task_data->OpenFeeAmt;
		data["OffsetFeeRate"] = task_data->OffsetFeeRate;
		data["OffsetFeeAmt"] = task_data->OffsetFeeAmt;
		data["OTFeeRate"] = task_data->OTFeeRate;
		data["OTFeeAmt"] = task_data->OTFeeAmt;
		data["ExecFeeRate"] = task_data->ExecFeeRate;
		data["ExecFeeAmt"] = task_data->ExecFeeAmt;
		data["PerOrderAmt"] = task_data->PerOrderAmt;
		data["PerCancelAmt"] = task_data->PerCancelAmt;
		data["HedgeFlag"] = task_data->HedgeFlag;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorFee(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorMargin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInvestorMarginField *task_data = (CUstpFtdcInvestorMarginField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["ProductID"] = toUtf(task_data->ProductID);
		data["LongMarginRate"] = task_data->LongMarginRate;
		data["LongMarginAmt"] = task_data->LongMarginAmt;
		data["ShortMarginRate"] = task_data->ShortMarginRate;
		data["ShortMarginAmt"] = task_data->ShortMarginAmt;
		data["HedgeFlag"] = task_data->HedgeFlag;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorMargin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorCombPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorCombPositionField *task_data = (CUstpFtdcRspInvestorCombPositionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["Direction"] = task_data->Direction;
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["Leg1InstrumentID"] = toUtf(task_data->Leg1InstrumentID);
		data["Leg2InstrumentID"] = toUtf(task_data->Leg2InstrumentID);
		data["CombPosition"] = task_data->CombPosition;
		data["CombFrozenPosition"] = task_data->CombFrozenPosition;
		data["CombFreeMargin"] = task_data->CombFreeMargin;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorCombPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorLegPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInvestorLegPositionField *task_data = (CUstpFtdcRspInvestorLegPositionField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["LongPosition"] = task_data->LongPosition;
		data["ShortPosition"] = task_data->ShortPosition;
		data["LongMargin"] = task_data->LongMargin;
		data["ShortMargin"] = task_data->ShortMargin;
		data["LongFrozenPosition"] = task_data->LongFrozenPosition;
		data["ShortFrozenPosition"] = task_data->ShortFrozenPosition;
		data["LongFrozenMargin"] = task_data->LongFrozenMargin;
		data["ShortFrozenMargin"] = task_data->ShortFrozenMargin;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInvestorLegPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInstrumentGroup(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspInstrumentGroupField *task_data = (CUstpFtdcRspInstrumentGroupField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentGroupID"] = toUtf(task_data->InstrumentGroupID);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryInstrumentGroup(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryClientMarginCombType(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspClientMarginCombTypeField *task_data = (CUstpFtdcRspClientMarginCombTypeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstrumentGroupID"] = toUtf(task_data->InstrumentGroupID);
		data["MarginCombType"] = task_data->MarginCombType;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryClientMarginCombType(data, error, task->task_id, task->task_last);
};

void TdApi::processRspExecOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderField *task_data = (CUstpFtdcInputExecOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Volume"] = task_data->Volume;
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspExecOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspExecOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderActionField *task_data = (CUstpFtdcInputExecOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["OrderType"] = task_data->OrderType;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspExecOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnExecOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcExecOrderField *task_data = (CUstpFtdcExecOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Volume"] = task_data->Volume;
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		data["TradingDay"] = toUtf(task_data->TradingDay);
		data["ParticipantID"] = toUtf(task_data->ParticipantID);
		data["OrderUserID"] = toUtf(task_data->OrderUserID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SeatID"] = toUtf(task_data->SeatID);
		data["InsertTime"] = toUtf(task_data->InsertTime);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderSource"] = task_data->OrderSource;
		data["OrderStatus"] = task_data->OrderStatus;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["CancelUserID"] = toUtf(task_data->CancelUserID);
		delete task->task_data;
	}
	this->onRtnExecOrder(data);
};

void TdApi::processErrRtnExecOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderField *task_data = (CUstpFtdcInputExecOrderField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["OrderType"] = task_data->OrderType;
		data["DeliveryFlag"] = task_data->DeliveryFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Volume"] = task_data->Volume;
		data["UserCustom"] = toUtf(task_data->UserCustom);
		data["ActionDay"] = toUtf(task_data->ActionDay);
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnExecOrderInsert(data, error);
};

void TdApi::processErrRtnExecOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcInputExecOrderActionField *task_data = (CUstpFtdcInputExecOrderActionField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["InvestorID"] = toUtf(task_data->InvestorID);
		data["UserID"] = toUtf(task_data->UserID);
		data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
		data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
		data["ActionFlag"] = task_data->ActionFlag;
		data["VolumeChange"] = task_data->VolumeChange;
		data["BusinessLocalID"] = task_data->BusinessLocalID;
		data["OrderType"] = task_data->OrderType;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onErrRtnExecOrderAction(data, error);
};

void TdApi::processRtnTransferMoney(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcSyncMoneyTransferField *task_data = (CUstpFtdcSyncMoneyTransferField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["BankID"] = toUtf(task_data->BankID);
		data["BankAccount"] = toUtf(task_data->BankAccount);
		data["Currency"] = toUtf(task_data->Currency);
		data["Amount"] = task_data->Amount;
		data["SyncTransMoneyEvent"] = task_data->SyncTransMoneyEvent;
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["TradeSource"] = task_data->TradeSource;
		data["TransSerialNo"] = toUtf(task_data->TransSerialNo);
		data["SerialNo"] = toUtf(task_data->SerialNo);
		data["UserID"] = toUtf(task_data->UserID);
		data["CommandDate"] = toUtf(task_data->CommandDate);
		data["CommandTime"] = toUtf(task_data->CommandTime);
		delete task->task_data;
	}
	this->onRtnTransferMoney(data);
};

void TdApi::processRspQrySystemTime(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspQrySystemTimeField *task_data = (CUstpFtdcRspQrySystemTimeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["SystemTime"] = toUtf(task_data->SystemTime);
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQrySystemTime(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryMarginPrefParam(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcRspQryMarginPrefParamField *task_data = (CUstpFtdcRspQryMarginPrefParamField*)task->task_data;
		data["BrokerID"] = toUtf(task_data->BrokerID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["CombInstrumentID"] = toUtf(task_data->CombInstrumentID);
		data["CombInstrumentName"] = toUtf(task_data->CombInstrumentName);
		data["CombType"] = task_data->CombType;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["Leg1InstrumentID"] = toUtf(task_data->Leg1InstrumentID);
		data["Leg1ProductID"] = toUtf(task_data->Leg1ProductID);
		data["Leg1Direction"] = task_data->Leg1Direction;
		data["Leg1HedgeFlag"] = task_data->Leg1HedgeFlag;
		data["Leg1SettlementPrice"] = task_data->Leg1SettlementPrice;
		data["Leg2InstrumentID"] = toUtf(task_data->Leg2InstrumentID);
		data["Leg2ProductID"] = toUtf(task_data->Leg2ProductID);
		data["Leg2Direction"] = task_data->Leg2Direction;
		data["Leg2HedgeFlag"] = task_data->Leg2HedgeFlag;
		data["Leg2SettlementPrice"] = task_data->Leg2SettlementPrice;
		data["Priority"] = task_data->Priority;
		data["TradeEna"] = task_data->TradeEna;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspQryMarginPrefParam(data, error, task->task_id, task->task_last);
};

void TdApi::processRspDSUserCertification(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUstpFtdcDSUserCertRspDataField *task_data = (CUstpFtdcDSUserCertRspDataField*)task->task_data;
		data["AppID"] = toUtf(task_data->AppID);
		data["AppIDType"] = task_data->AppIDType;
		data["UserCertRspData"] = toUtf(task_data->UserCertRspData);
		data["TotalNum"] = task_data->TotalNum;
		data["CurrentNum"] = task_data->CurrentNum;
		delete task->task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspDSUserCertification(data, error, task->task_id, task->task_last);
};

void TdApi::processRspDSProxySubmitInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUstpFtdcRspInfoField *task_error = (CUstpFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task->task_error;
	}
	this->onRspDSProxySubmitInfo(error, task->task_id, task->task_last);
};








///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	this->api = CUstpFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void TdApi::release()
{
	this->api->Release();
};

void TdApi::init()
{
	this->active = true;
	this->task_thread = thread(&TdApi::processTask, this);

	this->api->Init();
};

int TdApi::join()
{
	int i = this->api->Join();
	return i;
};

int TdApi::exit()
{
	this->active = false;
    this->task_queue.terminate();
    this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string TdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

void TdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void TdApi::subscribePrivateTopic(int nType)
{
	this->api->SubscribePrivateTopic((USTP_TE_RESUME_TYPE)nType);
};

void TdApi::subscribeUserTopic(int nType)
{
	this->api->SubscribeUserTopic((USTP_TE_RESUME_TYPE)nType);
};

void TdApi::subscribePublicTopic(int nType)
{
	this->api->SubscribePublicTopic((USTP_TE_RESUME_TYPE)nType);
};

int TdApi::reqUserLogin(const dict &req, int reqid)
{
	CUstpFtdcReqUserLoginField myreq = CUstpFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "UserID", myreq.UserID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "Password", myreq.Password);
	getString(req, "UserProductInfo", myreq.UserProductInfo);
	getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	getString(req, "IPAddress", myreq.IPAddress);
	getString(req, "MacAddress", myreq.MacAddress);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	getInt(req, "UserProductFileSize", &myreq.UserProductFileSize);
	getChar(req, "Authenticate2Type", &myreq.Authenticate2Type);
	getString(req, "Authenticate2Password", myreq.Authenticate2Password);
	getString(req, "TerminalCode", myreq.TerminalCode);
	getString(req, "PasswordEncrypt", myreq.PasswordEncrypt);
	int i = this->api->ReqUserLogin(&myreq, reqid);
	return i;
};

int TdApi::reqUserLogout(const dict &req, int reqid)
{
	CUstpFtdcReqUserLogoutField myreq = CUstpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

int TdApi::reqUserPasswordUpdate(const dict &req, int reqid)
{
	CUstpFtdcUserPasswordUpdateField myreq = CUstpFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqUserPasswordUpdate(&myreq, reqid);
	return i;
};

int TdApi::reqOrderInsert(const dict &req, int reqid)
{
	CUstpFtdcInputOrderField myreq = CUstpFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getInt(req, "SeatNo", &myreq.SeatNo);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getString(req, "GTDDate", myreq.GTDDate);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "UserCustom", myreq.UserCustom);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getString(req, "ActionDay", myreq.ActionDay);
	getChar(req, "ArbiType", &myreq.ArbiType);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqOrderAction(const dict &req, int reqid)
{
	CUstpFtdcOrderActionField myreq = CUstpFtdcOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQuoteInsert(const dict &req, int reqid)
{
	CUstpFtdcInputQuoteField myreq = CUstpFtdcInputQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "QuoteSysID", myreq.QuoteSysID);
	getString(req, "UserQuoteLocalID", myreq.UserQuoteLocalID);
	getString(req, "QuoteLocalID", myreq.QuoteLocalID);
	getInt(req, "BidVolume", &myreq.BidVolume);
	getChar(req, "BidOffsetFlag", &myreq.BidOffsetFlag);
	getChar(req, "BidHedgeFlag", &myreq.BidHedgeFlag);
	getDouble(req, "BidPrice", &myreq.BidPrice);
	getInt(req, "AskVolume", &myreq.AskVolume);
	getChar(req, "AskOffsetFlag", &myreq.AskOffsetFlag);
	getChar(req, "AskHedgeFlag", &myreq.AskHedgeFlag);
	getDouble(req, "AskPrice", &myreq.AskPrice);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "UserCustom", myreq.UserCustom);
	getString(req, "BidUserOrderLocalID", myreq.BidUserOrderLocalID);
	getString(req, "AskUserOrderLocalID", myreq.AskUserOrderLocalID);
	getString(req, "BidOrderLocalID", myreq.BidOrderLocalID);
	getString(req, "AskOrderLocalID", myreq.AskOrderLocalID);
	getString(req, "ReqForQuoteID", myreq.ReqForQuoteID);
	getInt(req, "StandByTime", &myreq.StandByTime);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQuoteInsert(&myreq, reqid);
	return i;
};

int TdApi::reqQuoteAction(const dict &req, int reqid)
{
	CUstpFtdcQuoteActionField myreq = CUstpFtdcQuoteActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "QuoteSysID", myreq.QuoteSysID);
	getString(req, "UserQuoteLocalID", myreq.UserQuoteLocalID);
	getString(req, "UserQuoteActionLocalID", myreq.UserQuoteActionLocalID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "UserCustom", myreq.UserCustom);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQuoteAction(&myreq, reqid);
	return i;
};

int TdApi::reqForQuote(const dict &req, int reqid)
{
	CUstpFtdcReqForQuoteField myreq = CUstpFtdcReqForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ReqForQuoteID", myreq.ReqForQuoteID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "ReqForQuoteTime", myreq.ReqForQuoteTime);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqForQuote(&myreq, reqid);
	return i;
};

int TdApi::reqMarginCombAction(const dict &req, int reqid)
{
	CUstpFtdcInputMarginCombActionField myreq = CUstpFtdcInputMarginCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "UserActionLocalID", myreq.UserActionLocalID);
	getString(req, "CombInstrumentID", myreq.CombInstrumentID);
	getInt(req, "CombVolume", &myreq.CombVolume);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getString(req, "ActionLocalID", myreq.ActionLocalID);
	getChar(req, "Direction", &myreq.Direction);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getChar(req, "CombActionStatus", &myreq.CombActionStatus);
	int i = this->api->ReqMarginCombAction(&myreq, reqid);
	return i;
};

int TdApi::reqUserDeposit(const dict &req, int reqid)
{
	CUstpFtdcstpUserDepositField myreq = CUstpFtdcstpUserDepositField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getDouble(req, "Amount", &myreq.Amount);
	getChar(req, "AmountDirection", &myreq.AmountDirection);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	int i = this->api->ReqUserDeposit(&myreq, reqid);
	return i;
};

int TdApi::reqQryOrder(const dict &req, int reqid)
{
	CUstpFtdcQryOrderField myreq = CUstpFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "OrderStatus", &myreq.OrderStatus);
	getChar(req, "OrderType", &myreq.OrderType);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryOrder(&myreq, reqid);
	return i;
};

int TdApi::reqQryTrade(const dict &req, int reqid)
{
	CUstpFtdcQryTradeField myreq = CUstpFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "TradeID", myreq.TradeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTrade(&myreq, reqid);
	return i;
};

int TdApi::reqQryUserInvestor(const dict &req, int reqid)
{
	CUstpFtdcQryUserInvestorField myreq = CUstpFtdcQryUserInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	int i = this->api->ReqQryUserInvestor(&myreq, reqid);
	return i;
};

int TdApi::reqQryTradingCode(const dict &req, int reqid)
{
	CUstpFtdcQryTradingCodeField myreq = CUstpFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingCode(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorAccount(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorAccountField myreq = CUstpFtdcQryInvestorAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorAccount(&myreq, reqid);
	return i;
};

int TdApi::reqQryInstrument(const dict &req, int reqid)
{
	CUstpFtdcQryInstrumentField myreq = CUstpFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ProductID", myreq.ProductID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryInstrument(&myreq, reqid);
	return i;
};

int TdApi::reqQryExchange(const dict &req, int reqid)
{
	CUstpFtdcQryExchangeField myreq = CUstpFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorPosition(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorPositionField myreq = CUstpFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryInvestorPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryComplianceParam(const dict &req, int reqid)
{
	CUstpFtdcQryComplianceParamField myreq = CUstpFtdcQryComplianceParamField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryComplianceParam(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorFee(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorFeeField myreq = CUstpFtdcQryInvestorFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorFee(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorMargin(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorMarginField myreq = CUstpFtdcQryInvestorMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorMargin(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorCombPosition(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorCombPositionField myreq = CUstpFtdcQryInvestorCombPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "CombInstrumentID", myreq.CombInstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorCombPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorLegPosition(const dict &req, int reqid)
{
	CUstpFtdcQryInvestorLegPositionField myreq = CUstpFtdcQryInvestorLegPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "LegInstrumentID", myreq.LegInstrumentID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryInvestorLegPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryInstrumentGroup(const dict &req, int reqid)
{
	CUstpFtdcQryUstpInstrumentGroupField myreq = CUstpFtdcQryUstpInstrumentGroupField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryInstrumentGroup(&myreq, reqid);
	return i;
};

int TdApi::reqQryClientMarginCombType(const dict &req, int reqid)
{
	CUstpFtdcQryClientMarginCombTypeField myreq = CUstpFtdcQryClientMarginCombTypeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "InstrumentGroupID", myreq.InstrumentGroupID);
	int i = this->api->ReqQryClientMarginCombType(&myreq, reqid);
	return i;
};

int TdApi::reqExecOrderInsert(const dict &req, int reqid)
{
	CUstpFtdcInputExecOrderField myreq = CUstpFtdcInputExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "OrderType", &myreq.OrderType);
	getChar(req, "DeliveryFlag", &myreq.DeliveryFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getInt(req, "Volume", &myreq.Volume);
	getString(req, "UserCustom", myreq.UserCustom);
	getString(req, "ActionDay", myreq.ActionDay);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	int i = this->api->ReqExecOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqExecOrderAction(const dict &req, int reqid)
{
	CUstpFtdcInputExecOrderActionField myreq = CUstpFtdcInputExecOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "UserID", myreq.UserID);
	getString(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getInt(req, "BusinessLocalID", &myreq.BusinessLocalID);
	getChar(req, "OrderType", &myreq.OrderType);
	int i = this->api->ReqExecOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQrySystemTime(const dict &req, int reqid)
{
	CUstpFtdcReqQrySystemTimeField myreq = CUstpFtdcReqQrySystemTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQrySystemTime(&myreq, reqid);
	return i;
};

int TdApi::reqQryMarginPrefParam(const dict &req, int reqid)
{
	CUstpFtdcReqQryMarginPrefParamField myreq = CUstpFtdcReqQryMarginPrefParamField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "CombInstrumentID", myreq.CombInstrumentID);
	getString(req, "CombInstrumentName", myreq.CombInstrumentName);
	int i = this->api->ReqQryMarginPrefParam(&myreq, reqid);
	return i;
};

int TdApi::reqDSUserCertification(const dict &req, int reqid)
{
	CUstpFtdcDSUserInfoField myreq = CUstpFtdcDSUserInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AppID", myreq.AppID);
	getString(req, "AuthCode", myreq.AuthCode);
	getChar(req, "EncryptType", &myreq.EncryptType);
	int i = this->api->ReqDSUserCertification(&myreq, reqid);
	return i;
};

int TdApi::reqDSProxySubmitInfo(const dict &req, int reqid)
{
	CUstpFtdcDSProxySubmitDataField myreq = CUstpFtdcDSProxySubmitDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AppID", myreq.AppID);
	getString(req, "TerminalPubNetIP", myreq.TerminalPubNetIP);
	getString(req, "TerminalPubNetPort", myreq.TerminalPubNetPort);
	getString(req, "TerminalLoginTime", myreq.TerminalLoginTime);
	getChar(req, "ExceptionFlag", &myreq.ExceptionFlag);
	getString(req, "RelayID", myreq.RelayID);
	getString(req, "TerminalSystemData", myreq.TerminalSystemData);
	int i = this->api->ReqDSProxySubmitInfo(&myreq, reqid);
	return i;
};




///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
	using TdApi::TdApi;

	void onFrontConnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onFrontConnected);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQryFrontConnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQryFrontConnected);
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
			PYBIND11_OVERLOAD(void, TdApi, onFrontDisconnected, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQryFrontDisconnected(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQryFrontDisconnected, reqid);
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
			PYBIND11_OVERLOAD(void, TdApi, onHeartBeatWarning, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onPackageStart(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onPackageStart, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onPackageEnd(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onPackageEnd, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspError(const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspError, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspUserLogin, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspUserLogout, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspUserPasswordUpdate, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspOrderInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspQuoteInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQuoteAction(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQuoteAction, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspForQuote, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspMarginCombAction, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUserDeposit(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspUserDeposit, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnFlowMessageCancel(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnFlowMessageCancel, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnTrade(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnTrade, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnOrder(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnOrderInsert(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderInsert, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnOrderAction(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderAction, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnInstrumentStatus(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnInstrumentStatus, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnInvestorAccountDeposit(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnInvestorAccountDeposit, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnQuote(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnQuote, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnQuoteInsert(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnQuoteInsert, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnQuoteAction(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnQuoteAction, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnForQuote(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnForQuote, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnMarginCombinationLeg(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnMarginCombinationLeg, data);
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
			PYBIND11_OVERLOAD(void, TdApi, onRtnMarginCombAction, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnUserDeposit(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnUserDeposit, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQueryUserLogin(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQueryUserLogin, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryTrade, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryUserInvestor(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryUserInvestor, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryTradingCode(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryTradingCode, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorAccount(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorAccount, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInstrument, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryExchange, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorPosition, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryComplianceParam(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryComplianceParam, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorFee(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorFee, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorMargin(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorMargin, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorCombPosition(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorCombPosition, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorLegPosition(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorLegPosition, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInstrumentGroup(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInstrumentGroup, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryClientMarginCombType(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryClientMarginCombType, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspExecOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspExecOrderInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspExecOrderAction(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspExecOrderAction, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnExecOrder(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnExecOrder, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnExecOrderInsert(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnExecOrderInsert, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnExecOrderAction(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnExecOrderAction, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnTransferMoney(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnTransferMoney, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQrySystemTime(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQrySystemTime, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryMarginPrefParam(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryMarginPrefParam, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspDSUserCertification(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspDSUserCertification, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspDSProxySubmitInfo(const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspDSProxySubmitInfo, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};





};


PYBIND11_MODULE(vnfemastd, m)
{
	class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
	TdApi
		.def(init<>())
		.def("createFtdcTraderApi", &TdApi::createFtdcTraderApi)
		.def("release", &TdApi::release)
		.def("init", &TdApi::init)
		.def("join", &TdApi::join)
		.def("exit", &TdApi::exit)
		.def("getTradingDay", &TdApi::getTradingDay)
		.def("registerFront", &TdApi::registerFront)
		.def("subscribePrivateTopic", &TdApi::subscribePrivateTopic)
		.def("subscribePublicTopic", &TdApi::subscribePublicTopic)
		.def("subscribeUserTopic", &TdApi::subscribeUserTopic)
		.def("reqUserLogin", &TdApi::reqUserLogin)
		.def("reqUserLogout", &TdApi::reqUserLogout)
		.def("reqUserPasswordUpdate", &TdApi::reqUserPasswordUpdate)
		.def("reqOrderInsert", &TdApi::reqOrderInsert)
		.def("reqOrderAction", &TdApi::reqOrderAction)
		.def("reqQuoteInsert", &TdApi::reqQuoteInsert)
		.def("reqQuoteAction", &TdApi::reqQuoteAction)
		.def("reqForQuote", &TdApi::reqForQuote)
		.def("reqMarginCombAction", &TdApi::reqMarginCombAction)
		.def("reqUserDeposit", &TdApi::reqUserDeposit)
		.def("reqQryOrder", &TdApi::reqQryOrder)
		.def("reqQryTrade", &TdApi::reqQryTrade)
		.def("reqQryUserInvestor", &TdApi::reqQryUserInvestor)
		.def("reqQryTradingCode", &TdApi::reqQryTradingCode)
		.def("reqQryInvestorAccount", &TdApi::reqQryInvestorAccount)
		.def("reqQryInstrument", &TdApi::reqQryInstrument)
		.def("reqQryExchange", &TdApi::reqQryExchange)
		.def("reqQryInvestorPosition", &TdApi::reqQryInvestorPosition)
		.def("reqQryComplianceParam", &TdApi::reqQryComplianceParam)
		.def("reqQryInvestorFee", &TdApi::reqQryInvestorFee)
		.def("reqQryInvestorMargin", &TdApi::reqQryInvestorMargin)
		.def("reqQryInvestorCombPosition", &TdApi::reqQryInvestorCombPosition)
		.def("reqQryInvestorLegPosition", &TdApi::reqQryInvestorLegPosition)
		.def("reqQryInstrumentGroup", &TdApi::reqQryInstrumentGroup)
		.def("reqQryClientMarginCombType", &TdApi::reqQryClientMarginCombType)
		.def("reqExecOrderInsert", &TdApi::reqExecOrderInsert)
		.def("reqExecOrderAction", &TdApi::reqExecOrderAction)
		.def("reqQrySystemTime", &TdApi::reqQrySystemTime)
		.def("reqQryMarginPrefParam", &TdApi::reqQryMarginPrefParam)
		.def("reqDSUserCertification", &TdApi::reqDSUserCertification)
		.def("reqDSProxySubmitInfo", &TdApi::reqDSProxySubmitInfo)

		.def("onFrontConnected", &TdApi::onFrontConnected)
		.def("onQryFrontConnected", &TdApi::onQryFrontConnected)
		.def("onFrontDisconnected", &TdApi::onFrontDisconnected)
		.def("onQryFrontDisconnected", &TdApi::onQryFrontDisconnected)
		.def("onHeartBeatWarning", &TdApi::onHeartBeatWarning)
		.def("onPackageStart", &TdApi::onPackageStart)
		.def("onPackageEnd", &TdApi::onPackageEnd)
		.def("onRspError", &TdApi::onRspError)
		.def("onRspUserLogin", &TdApi::onRspUserLogin)
		.def("onRspUserLogout", &TdApi::onRspUserLogout)
		.def("onRspUserPasswordUpdate", &TdApi::onRspUserPasswordUpdate)
		.def("onRspOrderInsert", &TdApi::onRspOrderInsert)
		.def("onRspOrderAction", &TdApi::onRspOrderAction)
		.def("onRspQuoteInsert", &TdApi::onRspQuoteInsert)
		.def("onRspQuoteAction", &TdApi::onRspQuoteAction)
		.def("onRspForQuote", &TdApi::onRspForQuote)
		.def("onRspMarginCombAction", &TdApi::onRspMarginCombAction)
		.def("onRspUserDeposit", &TdApi::onRspUserDeposit)
		.def("onRtnFlowMessageCancel", &TdApi::onRtnFlowMessageCancel)
		.def("onRtnTrade", &TdApi::onRtnTrade)
		.def("onRtnOrder", &TdApi::onRtnOrder)
		.def("onErrRtnOrderInsert", &TdApi::onErrRtnOrderInsert)
		.def("onErrRtnOrderAction", &TdApi::onErrRtnOrderAction)
		.def("onRtnInstrumentStatus", &TdApi::onRtnInstrumentStatus)
		.def("onRtnInvestorAccountDeposit", &TdApi::onRtnInvestorAccountDeposit)
		.def("onRtnQuote", &TdApi::onRtnQuote)
		.def("onErrRtnQuoteInsert", &TdApi::onErrRtnQuoteInsert)
		.def("onErrRtnQuoteAction", &TdApi::onErrRtnQuoteAction)
		.def("onRtnForQuote", &TdApi::onRtnForQuote)
		.def("onRtnMarginCombinationLeg", &TdApi::onRtnMarginCombinationLeg)
		.def("onRtnMarginCombAction", &TdApi::onRtnMarginCombAction)
		.def("onRtnUserDeposit", &TdApi::onRtnUserDeposit)
		.def("onRspQueryUserLogin", &TdApi::onRspQueryUserLogin)
		.def("onRspQryOrder", &TdApi::onRspQryOrder)
		.def("onRspQryTrade", &TdApi::onRspQryTrade)
		.def("onRspQryUserInvestor", &TdApi::onRspQryUserInvestor)
		.def("onRspQryTradingCode", &TdApi::onRspQryTradingCode)
		.def("onRspQryInvestorAccount", &TdApi::onRspQryInvestorAccount)
		.def("onRspQryInstrument", &TdApi::onRspQryInstrument)
		.def("onRspQryExchange", &TdApi::onRspQryExchange)
		.def("onRspQryInvestorPosition", &TdApi::onRspQryInvestorPosition)
		.def("onRspQryComplianceParam", &TdApi::onRspQryComplianceParam)
		.def("onRspQryInvestorFee", &TdApi::onRspQryInvestorFee)
		.def("onRspQryInvestorMargin", &TdApi::onRspQryInvestorMargin)
		.def("onRspQryInvestorCombPosition", &TdApi::onRspQryInvestorCombPosition)
		.def("onRspQryInvestorLegPosition", &TdApi::onRspQryInvestorLegPosition)
		.def("onRspQryInstrumentGroup", &TdApi::onRspQryInstrumentGroup)
		.def("onRspQryClientMarginCombType", &TdApi::onRspQryClientMarginCombType)
		.def("onRspExecOrderInsert", &TdApi::onRspExecOrderInsert)
		.def("onRspExecOrderAction", &TdApi::onRspExecOrderAction)
		.def("onRtnExecOrder", &TdApi::onRtnExecOrder)
		.def("onErrRtnExecOrderInsert", &TdApi::onErrRtnExecOrderInsert)
		.def("onErrRtnExecOrderAction", &TdApi::onErrRtnExecOrderAction)
		.def("onRtnTransferMoney", &TdApi::onRtnTransferMoney)
		.def("onRspQrySystemTime", &TdApi::onRspQrySystemTime)
		.def("onRspQryMarginPrefParam", &TdApi::onRspQryMarginPrefParam)
		.def("onRspDSUserCertification", &TdApi::onRspDSUserCertification)
		.def("onRspDSProxySubmitInfo", &TdApi::onRspDSProxySubmitInfo)
		;


}
