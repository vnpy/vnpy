// vnqdptd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnqdptd.h"


///-------------------------------------------------------------------------------------
///从Python对象到C++类型转换用的函数
///-------------------------------------------------------------------------------------

void getInt(dict d, string key, int *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
}

void getDouble(dict d, string key, double *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<double> x(o);
		if (x.check())
		{
			*value = x();
		}
	}
}

void getStr(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
#ifdef _MSC_VER //WIN32
			strcpy_s(value, strlen(buffer) + 1, buffer);
#elif __GNUC__
			strncpy(value, buffer, strlen(buffer) + 1);
#endif
		}
	}
}

void getChar(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			*value = *buffer;
		}
	}
}


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void TdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
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
	task.additional_int = nSequenceNo;
	this->task_queue.push(task);
};

void TdApi::OnPackageEnd(int nTopicID, int nSequenceNo)
{
	Task task = Task();
	task.task_name = ONPACKAGEEND;
	task.task_id = nTopicID;
	task.additional_int = nSequenceNo;
	this->task_queue.push(task);
};

void TdApi::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CQdpFtdcRspUserLoginField empty_data = CQdpFtdcRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pRspUserLogout)
	{
		task.task_data = *pRspUserLogout;
	}
	else
	{
		CQdpFtdcRspUserLogoutField empty_data = CQdpFtdcRspUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;

	if (pUserPasswordUpdate)
	{
		task.task_data = *pUserPasswordUpdate;
	}
	else
	{
		CQdpFtdcUserPasswordUpdateField empty_data = CQdpFtdcUserPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CQdpFtdcInputOrderField empty_data = CQdpFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;

	if (pOrderAction)
	{
		task.task_data = *pOrderAction;
	}
	else
	{
		CQdpFtdcOrderActionField empty_data = CQdpFtdcOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFromBankToFutureByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFROMBANKTOFUTUREBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CQdpFtdcReqTransferField empty_data = CQdpFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFromFutureToBankByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFROMFUTURETOBANKBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CQdpFtdcReqTransferField empty_data = CQdpFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel)
{
	Task task = Task();
	task.task_name = ONRTNFLOWMESSAGECANCEL;

	if (pFlowMessageCancel)
	{
		task.task_data = *pFlowMessageCancel;
	}
	else
	{
		CQdpFtdcFlowMessageCancelField empty_data = CQdpFtdcFlowMessageCancelField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CQdpFtdcTradeField *pTrade)
{
	Task task = Task();
	task.task_name = ONRTNTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CQdpFtdcTradeField empty_data = CQdpFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CQdpFtdcOrderField *pOrder)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CQdpFtdcOrderField empty_data = CQdpFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CQdpFtdcInputOrderField empty_data = CQdpFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;

	if (pOrderAction)
	{
		task.task_data = *pOrderAction;
	}
	else
	{
		CQdpFtdcOrderActionField empty_data = CQdpFtdcOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;

	if (pInstrumentStatus)
	{
		task.task_data = *pInstrumentStatus;
	}
	else
	{
		CQdpFtdcInstrumentStatusField empty_data = CQdpFtdcInstrumentStatusField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes)
{
	Task task = Task();
	task.task_name = ONRTNINVESTORACCOUNTDEPOSIT;

	if (pInvestorAccountDepositRes)
	{
		task.task_data = *pInvestorAccountDepositRes;
	}
	else
	{
		CQdpFtdcInvestorAccountDepositResField empty_data = CQdpFtdcInvestorAccountDepositResField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo)
{
	Task task = Task();
	task.task_name = ONRTNMESSAGENOTIFY;

	if (pMessageNotifyInfo)
	{
		task.task_data = *pMessageNotifyInfo;
	}
	else
	{
		CQdpFtdcMessageNotifyInfoField empty_data = CQdpFtdcMessageNotifyInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnQueryBankBalanceByFuture(CQdpFtdcReqQueryAccountField *pReqQueryAccount, CQdpFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNQUERYBANKBALANCEBYFUTURE;

	if (pReqQueryAccount)
	{
		task.task_data = *pReqQueryAccount;
	}
	else
	{
		CQdpFtdcReqQueryAccountField empty_data = CQdpFtdcReqQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnBankToFutureByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNBANKTOFUTUREBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CQdpFtdcReqTransferField empty_data = CQdpFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnFutureToBankByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNFUTURETOBANKBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CQdpFtdcReqTransferField empty_data = CQdpFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQueryBankBalanceByFuture(CQdpFtdcNotifyQueryAccountField *pNotifyQueryAccount)
{
	Task task = Task();
	task.task_name = ONRTNQUERYBANKBALANCEBYFUTURE;

	if (pNotifyQueryAccount)
	{
		task.task_data = *pNotifyQueryAccount;
	}
	else
	{
		CQdpFtdcNotifyQueryAccountField empty_data = CQdpFtdcNotifyQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFromBankToFutureByFuture(CQdpFtdcRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMBANKTOFUTUREBYFUTURE;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CQdpFtdcRspTransferField empty_data = CQdpFtdcRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFromFutureToBankByFuture(CQdpFtdcRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMFUTURETOBANKBYFUTURE;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CQdpFtdcRspTransferField empty_data = CQdpFtdcRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnSGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate)
{
	Task task = Task();
	task.task_name = ONRTNSGEDEFERRATE;

	if (pSGEDeferRate)
	{
		task.task_data = *pSGEDeferRate;
	}
	else
	{
		CQdpFtdcSGEDeferRateField empty_data = CQdpFtdcSGEDeferRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CQdpFtdcOrderField empty_data = CQdpFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CQdpFtdcTradeField empty_data = CQdpFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYUSERINVESTOR;

	if (pRspUserInvestor)
	{
		task.task_data = *pRspUserInvestor;
	}
	else
	{
		CQdpFtdcRspUserInvestorField empty_data = CQdpFtdcRspUserInvestorField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORACCOUNT;

	if (pRspInvestorAccount)
	{
		task.task_data = *pRspInvestorAccount;
	}
	else
	{
		CQdpFtdcRspInvestorAccountField empty_data = CQdpFtdcRspInvestorAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;

	if (pRspInstrument)
	{
		task.task_data = *pRspInstrument;
	}
	else
	{
		CQdpFtdcRspInstrumentField empty_data = CQdpFtdcRspInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;

	if (pRspExchange)
	{
		task.task_data = *pRspExchange;
	}
	else
	{
		CQdpFtdcRspExchangeField empty_data = CQdpFtdcRspExchangeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;

	if (pRspInvestorPosition)
	{
		task.task_data = *pRspInvestorPosition;
	}
	else
	{
		CQdpFtdcRspInvestorPositionField empty_data = CQdpFtdcRspInvestorPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBETOPIC;

	if (pDissemination)
	{
		task.task_data = *pDissemination;
	}
	else
	{
		CQdpFtdcDisseminationField empty_data = CQdpFtdcDisseminationField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTOPIC;

	if (pDissemination)
	{
		task.task_data = *pDissemination;
	}
	else
	{
		CQdpFtdcDisseminationField empty_data = CQdpFtdcDisseminationField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORFEE;

	if (pInvestorFee)
	{
		task.task_data = *pInvestorFee;
	}
	else
	{
		CQdpFtdcInvestorFeeField empty_data = CQdpFtdcInvestorFeeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORMARGIN;

	if (pInvestorMargin)
	{
		task.task_data = *pInvestorMargin;
	}
	else
	{
		CQdpFtdcInvestorMarginField empty_data = CQdpFtdcInvestorMarginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeDiffTime(CQdpFtdcRspExchangeDiffTimeField *pRspExchangeDiffTime, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGEDIFFTIME;

	if (pRspExchangeDiffTime)
	{
		task.task_data = *pRspExchangeDiffTime;
	}
	else
	{
		CQdpFtdcRspExchangeDiffTimeField empty_data = CQdpFtdcRspExchangeDiffTimeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryContractBank(CQdpFtdcContractBankField *pContractBank, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACTBANK;

	if (pContractBank)
	{
		task.task_data = *pContractBank;
	}
	else
	{
		CQdpFtdcContractBankField empty_data = CQdpFtdcContractBankField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQueryBankAccountMoneyByFuture(CQdpFtdcReqQueryAccountField *pReqQueryAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQUERYBANKACCOUNTMONEYBYFUTURE;

	if (pReqQueryAccount)
	{
		task.task_data = *pReqQueryAccount;
	}
	else
	{
		CQdpFtdcReqQueryAccountField empty_data = CQdpFtdcReqQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTransferSerial(CQdpFtdcTransferSerialField *pTransferSerial, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERSERIAL;

	if (pTransferSerial)
	{
		task.task_data = *pTransferSerial;
	}
	else
	{
		CQdpFtdcTransferSerialField empty_data = CQdpFtdcTransferSerialField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQrySGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSGEDEFERRATE;

	if (pSGEDeferRate)
	{
		task.task_data = *pSGEDeferRate;
	}
	else
	{
		CQdpFtdcSGEDeferRateField empty_data = CQdpFtdcSGEDeferRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryMarketData(CQdpFtdcMarketDataField *pMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYMARKETDATA;

	if (pMarketData)
	{
		task.task_data = *pMarketData;
	}
	else
	{
		CQdpFtdcMarketDataField empty_data = CQdpFtdcMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
	while (1)
	{
		Task task = this->task_queue.wait_and_pop();

		switch (task.task_name)
		{
		case ONFRONTCONNECTED:
		{
			this->processFrontConnected(task);
			break;
		}

		case ONFRONTDISCONNECTED:
		{
			this->processFrontDisconnected(task);
			break;
		}

		case ONHEARTBEATWARNING:
		{
			this->processHeartBeatWarning(task);
			break;
		}

		case ONPACKAGESTART:
		{
			this->processPackageStart(task);
			break;
		}

		case ONPACKAGEEND:
		{
			this->processPackageEnd(task);
			break;
		}

		case ONRSPERROR:
		{
			this->processRspError(task);
			break;
		}

		case ONRSPUSERLOGIN:
		{
			this->processRspUserLogin(task);
			break;
		}

		case ONRSPUSERLOGOUT:
		{
			this->processRspUserLogout(task);
			break;
		}

		case ONRSPUSERPASSWORDUPDATE:
		{
			this->processRspUserPasswordUpdate(task);
			break;
		}

		case ONRSPORDERINSERT:
		{
			this->processRspOrderInsert(task);
			break;
		}

		case ONRSPORDERACTION:
		{
			this->processRspOrderAction(task);
			break;
		}

		case ONRSPFROMBANKTOFUTUREBYFUTURE:
		{
			this->processRspFromBankToFutureByFuture(task);
			break;
		}

		case ONRSPFROMFUTURETOBANKBYFUTURE:
		{
			this->processRspFromFutureToBankByFuture(task);
			break;
		}

		case ONRTNFLOWMESSAGECANCEL:
		{
			this->processRtnFlowMessageCancel(task);
			break;
		}

		case ONRTNTRADE:
		{
			this->processRtnTrade(task);
			break;
		}

		case ONRTNORDER:
		{
			this->processRtnOrder(task);
			break;
		}

		case ONERRRTNORDERINSERT:
		{
			this->processErrRtnOrderInsert(task);
			break;
		}

		case ONERRRTNORDERACTION:
		{
			this->processErrRtnOrderAction(task);
			break;
		}

		case ONRTNINSTRUMENTSTATUS:
		{
			this->processRtnInstrumentStatus(task);
			break;
		}

		case ONRTNINVESTORACCOUNTDEPOSIT:
		{
			this->processRtnInvestorAccountDeposit(task);
			break;
		}

		case ONRTNMESSAGENOTIFY:
		{
			this->processRtnMessageNotify(task);
			break;
		}

		case ONERRRTNQUERYBANKBALANCEBYFUTURE:
		{
			this->processErrRtnQueryBankBalanceByFuture(task);
			break;
		}

		case ONERRRTNBANKTOFUTUREBYFUTURE:
		{
			this->processErrRtnBankToFutureByFuture(task);
			break;
		}

		case ONERRRTNFUTURETOBANKBYFUTURE:
		{
			this->processErrRtnFutureToBankByFuture(task);
			break;
		}

		case ONRTNQUERYBANKBALANCEBYFUTURE:
		{
			this->processRtnQueryBankBalanceByFuture(task);
			break;
		}

		case ONRTNFROMBANKTOFUTUREBYFUTURE:
		{
			this->processRtnFromBankToFutureByFuture(task);
			break;
		}

		case ONRTNFROMFUTURETOBANKBYFUTURE:
		{
			this->processRtnFromFutureToBankByFuture(task);
			break;
		}

		case ONRTNSGEDEFERRATE:
		{
			this->processRtnSGEDeferRate(task);
			break;
		}

		case ONRSPQRYORDER:
		{
			this->processRspQryOrder(task);
			break;
		}

		case ONRSPQRYTRADE:
		{
			this->processRspQryTrade(task);
			break;
		}

		case ONRSPQRYUSERINVESTOR:
		{
			this->processRspQryUserInvestor(task);
			break;
		}

		case ONRSPQRYINVESTORACCOUNT:
		{
			this->processRspQryInvestorAccount(task);
			break;
		}

		case ONRSPQRYINSTRUMENT:
		{
			this->processRspQryInstrument(task);
			break;
		}

		case ONRSPQRYEXCHANGE:
		{
			this->processRspQryExchange(task);
			break;
		}

		case ONRSPQRYINVESTORPOSITION:
		{
			this->processRspQryInvestorPosition(task);
			break;
		}

		case ONRSPSUBSCRIBETOPIC:
		{
			this->processRspSubscribeTopic(task);
			break;
		}

		case ONRSPQRYTOPIC:
		{
			this->processRspQryTopic(task);
			break;
		}

		case ONRSPQRYINVESTORFEE:
		{
			this->processRspQryInvestorFee(task);
			break;
		}

		case ONRSPQRYINVESTORMARGIN:
		{
			this->processRspQryInvestorMargin(task);
			break;
		}

		case ONRSPQRYEXCHANGEDIFFTIME:
		{
			this->processRspQryExchangeDiffTime(task);
			break;
		}

		case ONRSPQRYCONTRACTBANK:
		{
			this->processRspQryContractBank(task);
			break;
		}

		case ONRSPQUERYBANKACCOUNTMONEYBYFUTURE:
		{
			this->processRspQueryBankAccountMoneyByFuture(task);
			break;
		}

		case ONRSPQRYTRANSFERSERIAL:
		{
			this->processRspQryTransferSerial(task);
			break;
		}

		case ONRSPQRYSGEDEFERRATE:
		{
			this->processRspQrySGEDeferRate(task);
			break;
		}

		case ONRSPQRYMARKETDATA:
		{
			this->processRspQryMarketData(task);
			break;
		}
		}
	}
}

void TdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void TdApi::processHeartBeatWarning(Task task)
{
	PyLock lock;
	this->onHeartBeatWarning(task.task_id);
};

void TdApi::processPackageStart(Task task)
{
	PyLock lock;
	this->onPackageStart(task.task_id, task.additional_int);
};

void TdApi::processPackageEnd(Task task)
{
	PyLock lock;
	this->onPackageEnd(task.task_id, task.additional_int);
};

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLoginField task_data = any_cast<CQdpFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["PrivateFlowSize"] = task_data.PrivateFlowSize;
	data["UserID"] = task_data.UserID;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxOrderLocalID"] = task_data.MaxOrderLocalID;
	data["TradingSystemName"] = task_data.TradingSystemName;
	data["FrontID"] = task_data.FrontID;
	data["LoginTime"] = task_data.LoginTime;
	data["UserFlowSize"] = task_data.UserFlowSize;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLogoutField task_data = any_cast<CQdpFtdcRspUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CQdpFtdcUserPasswordUpdateField task_data = any_cast<CQdpFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CQdpFtdcInputOrderField task_data = any_cast<CQdpFtdcInputOrderField>(task.task_data);
	dict data;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["BusinessType"] = task_data.BusinessType;
	data["GTDDate"] = task_data.GTDDate;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CQdpFtdcOrderActionField task_data = any_cast<CQdpFtdcOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;
	data["FrontID"] = task_data.FrontID;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromBankToFutureByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromFutureToBankByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFlowMessageCancel(Task task)
{
	PyLock lock;
	CQdpFtdcFlowMessageCancelField task_data = any_cast<CQdpFtdcFlowMessageCancelField>(task.task_data);
	dict data;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["StartSequenceNo"] = task_data.StartSequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["EndSequenceNo"] = task_data.EndSequenceNo;

	this->onRtnFlowMessageCancel(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CQdpFtdcTradeField task_data = any_cast<CQdpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradeAmnt"] = task_data.TradeAmnt;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["TradeID"] = task_data.TradeID;
	data["InvestorID"] = task_data.InvestorID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["Direction"] = task_data.Direction;
	data["ClientID"] = task_data.ClientID;
	data["TradePrice"] = task_data.TradePrice;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["RecNum"] = task_data.RecNum;
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CQdpFtdcOrderField task_data = any_cast<CQdpFtdcOrderField>(task.task_data);
	dict data;
	data["VolumeRemain"] = task_data.VolumeRemain;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["SeatID"] = task_data.SeatID;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["CancelUserID"] = task_data.CancelUserID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["BusinessType"] = task_data.BusinessType;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;
	data["OrderSource"] = task_data.OrderSource;

	this->onRtnOrder(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CQdpFtdcInputOrderField task_data = any_cast<CQdpFtdcInputOrderField>(task.task_data);
	dict data;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["BusinessType"] = task_data.BusinessType;
	data["GTDDate"] = task_data.GTDDate;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CQdpFtdcOrderActionField task_data = any_cast<CQdpFtdcOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;
	data["FrontID"] = task_data.FrontID;
	data["RecNum"] = task_data.RecNum;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CQdpFtdcInstrumentStatusField task_data = any_cast<CQdpFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortPosLimit"] = task_data.ShortPosLimit;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["OptionsType"] = task_data.OptionsType;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["BasisPrice"] = task_data.BasisPrice;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["PriceTick"] = task_data.PriceTick;
	data["ProductName"] = task_data.ProductName;
	data["Currency"] = task_data.Currency;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["UnderlyingInstrID"] = task_data.UnderlyingInstrID;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnInvestorAccountDeposit(Task task)
{
	PyLock lock;
	CQdpFtdcInvestorAccountDepositResField task_data = any_cast<CQdpFtdcInvestorAccountDepositResField>(task.task_data);
	dict data;
	data["AmountDirection"] = task_data.AmountDirection;
	data["Available"] = task_data.Available;
	data["Balance"] = task_data.Balance;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountInsideSeqNo"] = task_data.AccountInsideSeqNo;
	data["AccountSeqNo"] = task_data.AccountSeqNo;
	data["AccountID"] = task_data.AccountID;

	this->onRtnInvestorAccountDeposit(data);
};

void TdApi::processRtnMessageNotify(Task task)
{
	PyLock lock;
	CQdpFtdcMessageNotifyInfoField task_data = any_cast<CQdpFtdcMessageNotifyInfoField>(task.task_data);
	dict data;
	data["WarnMsg"] = task_data.WarnMsg;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Nums"] = task_data.Nums;
	data["UserID"] = task_data.UserID;
	data["BusinessType"] = task_data.BusinessType;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	this->onRtnMessageNotify(data);
};

void TdApi::processErrRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqQueryAccountField task_data = any_cast<CQdpFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQueryBankBalanceByFuture(data, error);
};

void TdApi::processErrRtnBankToFutureByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnBankToFutureByFuture(data, error);
};

void TdApi::processErrRtnFutureToBankByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqTransferField task_data = any_cast<CQdpFtdcReqTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFutureToBankByFuture(data, error);
};

void TdApi::processRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcNotifyQueryAccountField task_data = any_cast<CQdpFtdcNotifyQueryAccountField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["BankUseAmount"] = task_data.BankUseAmount;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;
	data["BankFetchAmount"] = task_data.BankFetchAmount;

	this->onRtnQueryBankBalanceByFuture(data);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcRspTransferField task_data = any_cast<CQdpFtdcRspTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromBankToFutureByFuture(data);
};

void TdApi::processRtnFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcRspTransferField task_data = any_cast<CQdpFtdcRspTransferField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["TradingTime"] = task_data.TradingTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromFutureToBankByFuture(data);
};

void TdApi::processRtnSGEDeferRate(Task task)
{
	PyLock lock;
	CQdpFtdcSGEDeferRateField task_data = any_cast<CQdpFtdcSGEDeferRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DeferRate"] = task_data.DeferRate;
	data["Direction"] = task_data.Direction;
	data["TradeDate"] = task_data.TradeDate;

	this->onRtnSGEDeferRate(data);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CQdpFtdcOrderField task_data = any_cast<CQdpFtdcOrderField>(task.task_data);
	dict data;
	data["VolumeRemain"] = task_data.VolumeRemain;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["SeatID"] = task_data.SeatID;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["CancelUserID"] = task_data.CancelUserID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["BusinessType"] = task_data.BusinessType;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RecNum"] = task_data.RecNum;
	data["OrderSource"] = task_data.OrderSource;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CQdpFtdcTradeField task_data = any_cast<CQdpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradeAmnt"] = task_data.TradeAmnt;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["TradeID"] = task_data.TradeID;
	data["InvestorID"] = task_data.InvestorID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["Direction"] = task_data.Direction;
	data["ClientID"] = task_data.ClientID;
	data["TradePrice"] = task_data.TradePrice;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["RecNum"] = task_data.RecNum;
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryUserInvestor(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserInvestorField task_data = any_cast<CQdpFtdcRspUserInvestorField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorID"] = task_data.InvestorID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryUserInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorAccount(Task task)
{
	PyLock lock;
	CQdpFtdcRspInvestorAccountField task_data = any_cast<CQdpFtdcRspInvestorAccountField>(task.task_data);
	dict data;
	data["Fee"] = task_data.Fee;
	data["Withdraw"] = task_data.Withdraw;
	data["Mortgage"] = task_data.Mortgage;
	data["ShortMargin"] = task_data.ShortMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
	data["PositionProfit"] = task_data.PositionProfit;
	data["FrozenFee"] = task_data.FrozenFee;
	data["OtherFee"] = task_data.OtherFee;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["Premium"] = task_data.Premium;
	data["Risk"] = task_data.Risk;
	data["Currency"] = task_data.Currency;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["PreAvailable"] = task_data.PreAvailable;
	data["BrokerID"] = task_data.BrokerID;
	data["Deposit"] = task_data.Deposit;
	data["LongFrozenMargin"] = task_data.LongFrozenMargin;
	data["Balance"] = task_data.Balance;
	data["Margin"] = task_data.Margin;
	data["DynamicRights"] = task_data.DynamicRights;
	data["PreBalance"] = task_data.PreBalance;
	data["InvestorID"] = task_data.InvestorID;
	data["LongMargin"] = task_data.LongMargin;
	data["CloseProfit"] = task_data.CloseProfit;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CQdpFtdcRspInstrumentField task_data = any_cast<CQdpFtdcRspInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortPosLimit"] = task_data.ShortPosLimit;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["OptionsType"] = task_data.OptionsType;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["BasisPrice"] = task_data.BasisPrice;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["PriceTick"] = task_data.PriceTick;
	data["ProductName"] = task_data.ProductName;
	data["Currency"] = task_data.Currency;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["UnderlyingInstrID"] = task_data.UnderlyingInstrID;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CQdpFtdcRspExchangeField task_data = any_cast<CQdpFtdcRspExchangeField>(task.task_data);
	dict data;
	data["TradingDay"] = task_data.TradingDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CQdpFtdcRspInvestorPositionField task_data = any_cast<CQdpFtdcRspInvestorPositionField>(task.task_data);
	dict data;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Direction"] = task_data.Direction;
	data["ParticipantID"] = task_data.ParticipantID;
	data["FrozenClosing"] = task_data.FrozenClosing;
	data["InvestorID"] = task_data.InvestorID;
	data["LastTradeID"] = task_data.LastTradeID;
	data["YdPosition"] = task_data.YdPosition;
	data["ClientID"] = task_data.ClientID;
	data["FrozenPosition"] = task_data.FrozenPosition;
	data["LastOrderLocalID"] = task_data.LastOrderLocalID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["TodayPosition"] = task_data.TodayPosition;
	data["PositionCost"] = task_data.PositionCost;
	data["UsedMargin"] = task_data.UsedMargin;
	data["BrokerID"] = task_data.BrokerID;
	data["Position"] = task_data.Position;
	data["FrozenTodayClosing"] = task_data.FrozenTodayClosing;
	data["YdPositionCost"] = task_data.YdPositionCost;
	data["Currency"] = task_data.Currency;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSubscribeTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubscribeTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorFee(Task task)
{
	PyLock lock;
	CQdpFtdcInvestorFeeField task_data = any_cast<CQdpFtdcInvestorFeeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OTFeeRate"] = task_data.OTFeeRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OTFeeAmt"] = task_data.OTFeeAmt;
	data["OpenFeeAmt"] = task_data.OpenFeeAmt;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["OpenFeeRate"] = task_data.OpenFeeRate;
	data["OffsetFeeRate"] = task_data.OffsetFeeRate;
	data["OffsetFeeAmt"] = task_data.OffsetFeeAmt;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorFee(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorMargin(Task task)
{
	PyLock lock;
	CQdpFtdcInvestorMarginField task_data = any_cast<CQdpFtdcInvestorMarginField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["LongMarginRate"] = task_data.LongMarginRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["LongMarginAmt"] = task_data.LongMarginAmt;
	data["ShortMarginAmt"] = task_data.ShortMarginAmt;
	data["ShortMarginRate"] = task_data.ShortMarginRate;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorMargin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeDiffTime(Task task)
{
	PyLock lock;
	CQdpFtdcRspExchangeDiffTimeField task_data = any_cast<CQdpFtdcRspExchangeDiffTimeField>(task.task_data);
	dict data;
	data["ExchangeTime"] = task_data.ExchangeTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DiffSnd"] = task_data.DiffSnd;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeDiffTime(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryContractBank(Task task)
{
	PyLock lock;
	CQdpFtdcContractBankField task_data = any_cast<CQdpFtdcContractBankField>(task.task_data);
	dict data;
	data["Currency"] = task_data.Currency;
	data["BankName"] = task_data.BankName;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["BankBrchID"] = task_data.BankBrchID;
	data["BankID"] = task_data.BankID;
	data["AccountID"] = task_data.AccountID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryContractBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryBankAccountMoneyByFuture(Task task)
{
	PyLock lock;
	CQdpFtdcReqQueryAccountField task_data = any_cast<CQdpFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["BankBrchID"] = task_data.BankBrchID;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["Currency"] = task_data.Currency;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["BankCodingForFuture"] = task_data.BankCodingForFuture;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryBankAccountMoneyByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	CQdpFtdcTransferSerialField task_data = any_cast<CQdpFtdcTransferSerialField>(task.task_data);
	dict data;
	data["BankNewAccount"] = task_data.BankNewAccount;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["BankBrchID"] = task_data.BankBrchID;
	data["OperatorCode"] = task_data.OperatorCode;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InvestorID"] = task_data.InvestorID;
	data["TradeCode"] = task_data.TradeCode;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["TradingTime"] = task_data.TradingTime;
	data["FutureAccType"] = task_data.FutureAccType;
	data["ErrorID"] = task_data.ErrorID;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankSerial"] = task_data.BankSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["IdCardType"] = task_data.IdCardType;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradeDate"] = task_data.TradeDate;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["FutureSerial"] = task_data.FutureSerial;
	data["Currency"] = task_data.Currency;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AvailabilityFlag"] = task_data.AvailabilityFlag;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTransferSerial(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySGEDeferRate(Task task)
{
	PyLock lock;
	CQdpFtdcSGEDeferRateField task_data = any_cast<CQdpFtdcSGEDeferRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DeferRate"] = task_data.DeferRate;
	data["Direction"] = task_data.Direction;
	data["TradeDate"] = task_data.TradeDate;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySGEDeferRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcMarketDataField task_data = any_cast<CQdpFtdcMarketDataField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["LastPrice"] = task_data.LastPrice;
	data["HighestPrice"] = task_data.HighestPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["UpdateTime"] = task_data.UpdateTime;
	data["OpenPrice"] = task_data.OpenPrice;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["Volume"] = task_data.Volume;
	data["TradingDay"] = task_data.TradingDay;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["LowestPrice"] = task_data.LowestPrice;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["OpenInterest"] = task_data.OpenInterest;
	data["Turnover"] = task_data.Turnover;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryMarketData(data, error, task.task_id, task.task_last);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	this->api = CQdpFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

string TdApi::getVersion(int major, int minor)
{
	string version = this->api->GetVersion(major, minor);
	return version;
}

void TdApi::release()
{
	this->api->Release();
};

void TdApi::init()
{
	this->api->Init();
};

int TdApi::join()
{
	int i = this->api->Join();
	return i;
};

int TdApi::exit()
{
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
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

void TdApi::registerNameServer(string pszNsAddress)
{
	this->api->RegisterNameServer((char*)pszNsAddress.c_str());
};

void TdApi::subscribePrivateTopic(int nType)
{
	this->api->SubscribePrivateTopic((QDP_TE_RESUME_TYPE)nType);
};

void TdApi::subscribePublicTopic(int nType)
{
	this->api->SubscribePublicTopic((QDP_TE_RESUME_TYPE)nType);
};

void TdApi::setHeartbeatTimeout(int timeout)
{
	this->api->SetHeartbeatTimeout(timeout);
};

int TdApi::openRequestLog(string fileName)
{
	return this->api->OpenRequestLog((char*)fileName.c_str());
};

int TdApi::openResponseLog(string fileName)
{
	return this->api->OpenResponseLog((char*)fileName.c_str());
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CQdpFtdcReqUserLoginField myreq = CQdpFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CQdpFtdcReqUserLogoutField myreq = CQdpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CQdpFtdcUserPasswordUpdateField myreq = CQdpFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "NewPassword", myreq.NewPassword);
	getStr(req, "OldPassword", myreq.OldPassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CQdpFtdcInputOrderField myreq = CQdpFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getStr(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "BusinessType", &myreq.BusinessType);
	getStr(req, "GTDDate", myreq.GTDDate);
	getStr(req, "BranchID", myreq.BranchID);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "UserCustom", myreq.UserCustom);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RecNum", &myreq.RecNum);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CQdpFtdcOrderActionField myreq = CQdpFtdcOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getStr(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "FrontID", &myreq.FrontID);
	getInt(req, "RecNum", &myreq.RecNum);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromBankToFutureByFuture(dict req, int nRequestID)
{
	CQdpFtdcReqTransferField myreq = CQdpFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "VerifyCertNoFlag", myreq.VerifyCertNoFlag);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "TradeCode", myreq.TradeCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "CustType", myreq.CustType);
	getStr(req, "BankCodingForFuture", myreq.BankCodingForFuture);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getStr(req, "IdCardType", myreq.IdCardType);
	getStr(req, "Password", myreq.Password);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getStr(req, "TradingTime", myreq.TradingTime);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Message", myreq.Message);
	getDouble(req, "CustFee", &myreq.CustFee);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromBankToFutureByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromFutureToBankByFuture(dict req, int nRequestID)
{
	CQdpFtdcReqTransferField myreq = CQdpFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "VerifyCertNoFlag", myreq.VerifyCertNoFlag);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "TradeCode", myreq.TradeCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "CustType", myreq.CustType);
	getStr(req, "BankCodingForFuture", myreq.BankCodingForFuture);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getStr(req, "IdCardType", myreq.IdCardType);
	getStr(req, "Password", myreq.Password);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getStr(req, "TradingTime", myreq.TradingTime);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Message", myreq.Message);
	getDouble(req, "CustFee", &myreq.CustFee);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromFutureToBankByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CQdpFtdcQryOrderField myreq = CQdpFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CQdpFtdcQryTradeField myreq = CQdpFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "TradeID", myreq.TradeID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryUserInvestor(dict req, int nRequestID)
{
	CQdpFtdcQryUserInvestorField myreq = CQdpFtdcQryUserInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryUserInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorAccount(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorAccountField myreq = CQdpFtdcQryInvestorAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CQdpFtdcQryInstrumentField myreq = CQdpFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CQdpFtdcQryExchangeField myreq = CQdpFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorPositionField myreq = CQdpFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqSubscribeTopic(dict req, int nRequestID)
{
	CQdpFtdcDisseminationField myreq = CQdpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqSubscribeTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTopic(dict req, int nRequestID)
{
	CQdpFtdcDisseminationField myreq = CQdpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqQryTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorFee(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorFeeField myreq = CQdpFtdcQryInvestorFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorFee(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorMargin(dict req, int nRequestID)
{
	CQdpFtdcQryInvestorMarginField myreq = CQdpFtdcQryInvestorMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorMargin(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeDiffTime(dict req, int nRequestID)
{
	CQdpFtdcQryExchangeDiffTimeField myreq = CQdpFtdcQryExchangeDiffTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchangeDiffTime(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryContractBank(dict req, int nRequestID)
{
	CQdpFtdcQryContractBankField myreq = CQdpFtdcQryContractBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getStr(req, "BankID", myreq.BankID);
	int i = this->api->ReqQryContractBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryBankAccountMoneyByFuture(dict req, int nRequestID)
{
	CQdpFtdcReqQueryAccountField myreq = CQdpFtdcReqQueryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "VerifyCertNoFlag", myreq.VerifyCertNoFlag);
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "TradeCode", myreq.TradeCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "CustType", myreq.CustType);
	getStr(req, "BankCodingForFuture", myreq.BankCodingForFuture);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getStr(req, "IdCardType", myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getStr(req, "TradeDate", myreq.TradeDate);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqQueryBankAccountMoneyByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferSerial(dict req, int nRequestID)
{
	CQdpFtdcQryTransferSerialField myreq = CQdpFtdcQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "Currency", myreq.Currency);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySGEDeferRate(dict req, int nRequestID)
{
	CQdpFtdcQrySGEDeferRateField myreq = CQdpFtdcQrySGEDeferRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQrySGEDeferRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryMarketData(dict req, int nRequestID)
{
	CQdpFtdcQryMarketDataField myreq = CQdpFtdcQryMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryMarketData(&myreq, nRequestID);
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct TdApiWrap : TdApi, wrapper < TdApi >
{
	virtual void onFrontConnected()
	{
		//在向python环境中调用回调函数推送数据前，需要先获取全局锁GIL，防止解释器崩溃
		PyLock lock;

		//以下的try...catch...可以实现捕捉python环境中错误的功能，防止C++直接出现原因未知的崩溃
		try
		{
			this->get_override("onFrontConnected")();
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFrontDisconnected(int i)
	{
		PyLock lock;

		try
		{
			this->get_override("onFrontDisconnected")(i);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onHeartBeatWarning(int i)
	{
		PyLock lock;

		try
		{
			this->get_override("onHeartBeatWarning")(i);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onPackageStart(int topicID, int sequenceNo)
	{
		PyLock lock;

		try
		{
			this->get_override("onPackageStart")(topicID, sequenceNo);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onPackageEnd(int topicID, int sequenceNo)
	{
		PyLock lock;

		try
		{
			this->get_override("onPackageEnd")(topicID, sequenceNo);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspError(dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspError")(error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspUserLogin")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspUserLogout")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspUserPasswordUpdate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspOrderInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspOrderInsert")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspOrderAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspOrderAction")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFromBankToFutureByFuture")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFromFutureToBankByFuture")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFlowMessageCancel(dict data)
	{
		try
		{
			this->get_override("onRtnFlowMessageCancel")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnTrade(dict data)
	{
		try
		{
			this->get_override("onRtnTrade")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnOrder(dict data)
	{
		try
		{
			this->get_override("onRtnOrder")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnOrderInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnOrderInsert")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnOrderAction(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnOrderAction")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnInstrumentStatus(dict data)
	{
		try
		{
			this->get_override("onRtnInstrumentStatus")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnInvestorAccountDeposit(dict data)
	{
		try
		{
			this->get_override("onRtnInvestorAccountDeposit")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnMessageNotify(dict data)
	{
		try
		{
			this->get_override("onRtnMessageNotify")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnQueryBankBalanceByFuture")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnBankToFutureByFuture(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnBankToFutureByFuture")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnFutureToBankByFuture(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnFutureToBankByFuture")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnQueryBankBalanceByFuture(dict data)
	{
		try
		{
			this->get_override("onRtnQueryBankBalanceByFuture")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromBankToFutureByFuture(dict data)
	{
		try
		{
			this->get_override("onRtnFromBankToFutureByFuture")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromFutureToBankByFuture(dict data)
	{
		try
		{
			this->get_override("onRtnFromFutureToBankByFuture")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnSGEDeferRate(dict data)
	{
		try
		{
			this->get_override("onRtnSGEDeferRate")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOrder")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTrade")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryUserInvestor(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryUserInvestor")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorAccount(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorAccount")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInstrument")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchange(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExchange")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorPosition")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSubscribeTopic(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspSubscribeTopic")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTopic(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTopic")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorFee(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorFee")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorMargin(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorMargin")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchangeDiffTime(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExchangeDiffTime")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryContractBank(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryContractBank")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQueryBankAccountMoneyByFuture")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTransferSerial")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySGEDeferRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySGEDeferRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryMarketData(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryMarketData")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnqdptd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("createFtdcTraderApi", &TdApiWrap::createFtdcTraderApi)
		.def("getVersion", &TdApiWrap::getVersion)
		.def("release", &TdApiWrap::release)
		.def("init", &TdApiWrap::init)
		.def("join", &TdApiWrap::join)
		.def("exit", &TdApiWrap::exit)
		.def("getTradingDay", &TdApiWrap::getTradingDay)
		.def("registerFront", &TdApiWrap::registerFront)
		.def("registerNameServer", &TdApiWrap::registerNameServer)
		.def("subscribePrivateTopic", &TdApiWrap::subscribePrivateTopic)
		.def("subscribePublicTopic", &TdApiWrap::subscribePublicTopic)
		.def("setHeartbeatTimeout", &TdApiWrap::setHeartbeatTimeout)
		.def("openRequestLog", &TdApiWrap::openRequestLog)
		.def("openResponseLog", &TdApiWrap::openResponseLog)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqUserPasswordUpdate", &TdApiWrap::reqUserPasswordUpdate)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqFromBankToFutureByFuture", &TdApiWrap::reqFromBankToFutureByFuture)
		.def("reqFromFutureToBankByFuture", &TdApiWrap::reqFromFutureToBankByFuture)
		.def("reqQryOrder", &TdApiWrap::reqQryOrder)
		.def("reqQryTrade", &TdApiWrap::reqQryTrade)
		.def("reqQryUserInvestor", &TdApiWrap::reqQryUserInvestor)
		.def("reqQryInvestorAccount", &TdApiWrap::reqQryInvestorAccount)
		.def("reqQryInstrument", &TdApiWrap::reqQryInstrument)
		.def("reqQryExchange", &TdApiWrap::reqQryExchange)
		.def("reqQryInvestorPosition", &TdApiWrap::reqQryInvestorPosition)
		.def("reqSubscribeTopic", &TdApiWrap::reqSubscribeTopic)
		.def("reqQryTopic", &TdApiWrap::reqQryTopic)
		.def("reqQryInvestorFee", &TdApiWrap::reqQryInvestorFee)
		.def("reqQryInvestorMargin", &TdApiWrap::reqQryInvestorMargin)
		.def("reqQryExchangeDiffTime", &TdApiWrap::reqQryExchangeDiffTime)
		.def("reqQryContractBank", &TdApiWrap::reqQryContractBank)
		.def("reqQueryBankAccountMoneyByFuture", &TdApiWrap::reqQueryBankAccountMoneyByFuture)
		.def("reqQryTransferSerial", &TdApiWrap::reqQryTransferSerial)
		.def("reqQrySGEDeferRate", &TdApiWrap::reqQrySGEDeferRate)
		.def("reqQryMarketData", &TdApiWrap::reqQryMarketData)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&TdApiWrap::onHeartBeatWarning))
		.def("onPackageStart", pure_virtual(&TdApiWrap::onPackageStart))
		.def("onPackageEnd", pure_virtual(&TdApiWrap::onPackageEnd))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspUserPasswordUpdate))
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onRspFromBankToFutureByFuture", pure_virtual(&TdApiWrap::onRspFromBankToFutureByFuture))
		.def("onRspFromFutureToBankByFuture", pure_virtual(&TdApiWrap::onRspFromFutureToBankByFuture))
		.def("onRtnFlowMessageCancel", pure_virtual(&TdApiWrap::onRtnFlowMessageCancel))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onErrRtnOrderInsert", pure_virtual(&TdApiWrap::onErrRtnOrderInsert))
		.def("onErrRtnOrderAction", pure_virtual(&TdApiWrap::onErrRtnOrderAction))
		.def("onRtnInstrumentStatus", pure_virtual(&TdApiWrap::onRtnInstrumentStatus))
		.def("onRtnInvestorAccountDeposit", pure_virtual(&TdApiWrap::onRtnInvestorAccountDeposit))
		.def("onRtnMessageNotify", pure_virtual(&TdApiWrap::onRtnMessageNotify))
		.def("onErrRtnQueryBankBalanceByFuture", pure_virtual(&TdApiWrap::onErrRtnQueryBankBalanceByFuture))
		.def("onErrRtnBankToFutureByFuture", pure_virtual(&TdApiWrap::onErrRtnBankToFutureByFuture))
		.def("onErrRtnFutureToBankByFuture", pure_virtual(&TdApiWrap::onErrRtnFutureToBankByFuture))
		.def("onRtnQueryBankBalanceByFuture", pure_virtual(&TdApiWrap::onRtnQueryBankBalanceByFuture))
		.def("onRtnFromBankToFutureByFuture", pure_virtual(&TdApiWrap::onRtnFromBankToFutureByFuture))
		.def("onRtnFromFutureToBankByFuture", pure_virtual(&TdApiWrap::onRtnFromFutureToBankByFuture))
		.def("onRtnSGEDeferRate", pure_virtual(&TdApiWrap::onRtnSGEDeferRate))
		.def("onRspQryOrder", pure_virtual(&TdApiWrap::onRspQryOrder))
		.def("onRspQryTrade", pure_virtual(&TdApiWrap::onRspQryTrade))
		.def("onRspQryUserInvestor", pure_virtual(&TdApiWrap::onRspQryUserInvestor))
		.def("onRspQryInvestorAccount", pure_virtual(&TdApiWrap::onRspQryInvestorAccount))
		.def("onRspQryInstrument", pure_virtual(&TdApiWrap::onRspQryInstrument))
		.def("onRspQryExchange", pure_virtual(&TdApiWrap::onRspQryExchange))
		.def("onRspQryInvestorPosition", pure_virtual(&TdApiWrap::onRspQryInvestorPosition))
		.def("onRspSubscribeTopic", pure_virtual(&TdApiWrap::onRspSubscribeTopic))
		.def("onRspQryTopic", pure_virtual(&TdApiWrap::onRspQryTopic))
		.def("onRspQryInvestorFee", pure_virtual(&TdApiWrap::onRspQryInvestorFee))
		.def("onRspQryInvestorMargin", pure_virtual(&TdApiWrap::onRspQryInvestorMargin))
		.def("onRspQryExchangeDiffTime", pure_virtual(&TdApiWrap::onRspQryExchangeDiffTime))
		.def("onRspQryContractBank", pure_virtual(&TdApiWrap::onRspQryContractBank))
		.def("onRspQueryBankAccountMoneyByFuture", pure_virtual(&TdApiWrap::onRspQueryBankAccountMoneyByFuture))
		.def("onRspQryTransferSerial", pure_virtual(&TdApiWrap::onRspQryTransferSerial))
		.def("onRspQrySGEDeferRate", pure_virtual(&TdApiWrap::onRspQrySGEDeferRate))
		.def("onRspQryMarketData", pure_virtual(&TdApiWrap::onRspQryMarketData))
		;
}
