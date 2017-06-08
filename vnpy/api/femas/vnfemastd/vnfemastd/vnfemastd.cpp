// vnctptd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnfemastd.h"


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
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
			strcpy_s(value, strlen(buffer) + 1, buffer);
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
	//该函数忽略
};

void TdApi::OnPackageEnd(int nTopicID, int nSequenceNo)
{
	//该函数忽略
};

void TdApi::OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CUstpFtdcRspUserLoginField empty_data = CUstpFtdcRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspUserLogout;
	}
	else
	{
		CUstpFtdcRspUserLogoutField empty_data = CUstpFtdcRspUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pUserPasswordUpdate;
	}
	else
	{
		CUstpFtdcUserPasswordUpdateField empty_data = CUstpFtdcUserPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pInputOrder;
	}
	else
	{
		CUstpFtdcInputOrderField empty_data = CUstpFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pOrderAction;
	}
	else
	{
		CUstpFtdcOrderActionField empty_data = CUstpFtdcOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pFlowMessageCancel;
	}
	else
	{
		CUstpFtdcFlowMessageCancelField empty_data = CUstpFtdcFlowMessageCancelField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CUstpFtdcTradeField *pTrade)
{
	Task task = Task();
	task.task_name = ONRTNTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CUstpFtdcTradeField empty_data = CUstpFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CUstpFtdcOrderField *pOrder)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CUstpFtdcOrderField empty_data = CUstpFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CUstpFtdcInputOrderField empty_data = CUstpFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;

	if (pOrderAction)
	{
		task.task_data = *pOrderAction;
	}
	else
	{
		CUstpFtdcOrderActionField empty_data = CUstpFtdcOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;

	if (pInstrumentStatus)
	{
		task.task_data = *pInstrumentStatus;
	}
	else
	{
		CUstpFtdcInstrumentStatusField empty_data = CUstpFtdcInstrumentStatusField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes)
{
	Task task = Task();
	task.task_name = ONRTNINVESTORACCOUNTDEPOSIT;

	if (pInvestorAccountDepositRes)
	{
		task.task_data = *pInvestorAccountDepositRes;
	}
	else
	{
		CUstpFtdcInvestorAccountDepositResField empty_data = CUstpFtdcInvestorAccountDepositResField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CUstpFtdcOrderField *pOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CUstpFtdcOrderField empty_data = CUstpFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pTrade;
	}
	else
	{
		CUstpFtdcTradeField empty_data = CUstpFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspUserInvestor;
	}
	else
	{
		CUstpFtdcRspUserInvestorField empty_data = CUstpFtdcRspUserInvestorField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspTradingCode;
	}
	else
	{
		CUstpFtdcRspTradingCodeField empty_data = CUstpFtdcRspTradingCodeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspInvestorAccount;
	}
	else
	{
		CUstpFtdcRspInvestorAccountField empty_data = CUstpFtdcRspInvestorAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspInstrument;
	}
	else
	{
		CUstpFtdcRspInstrumentField empty_data = CUstpFtdcRspInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspExchange;
	}
	else
	{
		CUstpFtdcRspExchangeField empty_data = CUstpFtdcRspExchangeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspInvestorPosition;
	}
	else
	{
		CUstpFtdcRspInvestorPositionField empty_data = CUstpFtdcRspInvestorPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSubscribeTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBETOPIC;

	if (pDissemination)
	{
		task.task_data = *pDissemination;
	}
	else
	{
		CUstpFtdcDisseminationField empty_data = CUstpFtdcDisseminationField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pRspComplianceParam;
	}
	else
	{
		CUstpFtdcRspComplianceParamField empty_data = CUstpFtdcRspComplianceParamField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTOPIC;

	if (pDissemination)
	{
		task.task_data = *pDissemination;
	}
	else
	{
		CUstpFtdcDisseminationField empty_data = CUstpFtdcDisseminationField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pInvestorFee;
	}
	else
	{
		CUstpFtdcInvestorFeeField empty_data = CUstpFtdcInvestorFeeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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
		task.task_data = *pInvestorMargin;
	}
	else
	{
		CUstpFtdcInvestorMarginField empty_data = CUstpFtdcInvestorMarginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CUstpFtdcRspInfoField empty_error = CUstpFtdcRspInfoField();
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

			case ONRSPQRYTRADINGCODE:
			{
				this->processRspQryTradingCode(task);
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

			case ONRSPQRYCOMPLIANCEPARAM:
			{
				this->processRspQryComplianceParam(task);
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

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CUstpFtdcRspUserLoginField task_data = any_cast<CUstpFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["PrivateFlowSize"] = task_data.PrivateFlowSize;
	data["UserID"] = task_data.UserID;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxOrderLocalID"] = task_data.MaxOrderLocalID;
	data["TradingSystemName"] = task_data.TradingSystemName;
	data["LoginTime"] = task_data.LoginTime;
	data["UserFlowSize"] = task_data.UserFlowSize;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CUstpFtdcRspUserLogoutField task_data = any_cast<CUstpFtdcRspUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CUstpFtdcUserPasswordUpdateField task_data = any_cast<CUstpFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CUstpFtdcInputOrderField task_data = any_cast<CUstpFtdcInputOrderField>(task.task_data);
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
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CUstpFtdcOrderActionField task_data = any_cast<CUstpFtdcOrderActionField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFlowMessageCancel(Task task)
{
	PyLock lock;
	CUstpFtdcFlowMessageCancelField task_data = any_cast<CUstpFtdcFlowMessageCancelField>(task.task_data);
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
	CUstpFtdcTradeField task_data = any_cast<CUstpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
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
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	this->onRtnTrade(data);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CUstpFtdcOrderField task_data = any_cast<CUstpFtdcOrderField>(task.task_data);
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
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["OrderSource"] = task_data.OrderSource;

	this->onRtnOrder(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CUstpFtdcInputOrderField task_data = any_cast<CUstpFtdcInputOrderField>(task.task_data);
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
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CUstpFtdcOrderActionField task_data = any_cast<CUstpFtdcOrderActionField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["UserOrderActionLocalID"] = task_data.UserOrderActionLocalID;
	data["UserOrderLocalID"] = task_data.UserOrderLocalID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["OrderSysID"] = task_data.OrderSysID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CUstpFtdcInstrumentStatusField task_data = any_cast<CUstpFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
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
	CUstpFtdcInvestorAccountDepositResField task_data = any_cast<CUstpFtdcInvestorAccountDepositResField>(task.task_data);
	dict data;
	data["AmountDirection"] = task_data.AmountDirection;
	data["Available"] = task_data.Available;
	data["Balance"] = task_data.Balance;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountSeqNo"] = task_data.AccountSeqNo;
	data["AccountID"] = task_data.AccountID;

	this->onRtnInvestorAccountDeposit(data);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CUstpFtdcOrderField task_data = any_cast<CUstpFtdcOrderField>(task.task_data);
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
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserCustom"] = task_data.UserCustom;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["OrderSource"] = task_data.OrderSource;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CUstpFtdcTradeField task_data = any_cast<CUstpFtdcTradeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
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
	data["TradeTime"] = task_data.TradeTime;
	data["SeatID"] = task_data.SeatID;
	data["TradeVolume"] = task_data.TradeVolume;
	data["OffsetFlag"] = task_data.OffsetFlag;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryUserInvestor(Task task)
{
	PyLock lock;
	CUstpFtdcRspUserInvestorField task_data = any_cast<CUstpFtdcRspUserInvestorField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorID"] = task_data.InvestorID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryUserInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CUstpFtdcRspTradingCodeField task_data = any_cast<CUstpFtdcRspTradingCodeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientRight"] = task_data.ClientRight;
	data["BrokerID"] = task_data.BrokerID;
	data["IsActive"] = task_data.IsActive;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorAccount(Task task)
{
	PyLock lock;
	CUstpFtdcRspInvestorAccountField task_data = any_cast<CUstpFtdcRspInvestorAccountField>(task.task_data);
	dict data;
	data["Fee"] = task_data.Fee;
	data["Withdraw"] = task_data.Withdraw;
	data["ShortMargin"] = task_data.ShortMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
	data["PositionProfit"] = task_data.PositionProfit;
	data["FrozenFee"] = task_data.FrozenFee;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["Premium"] = task_data.Premium;
	data["Risk"] = task_data.Risk;
	data["TodayInOut"] = task_data.TodayInOut;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["BrokerID"] = task_data.BrokerID;
	data["Deposit"] = task_data.Deposit;
	data["LongFrozenMargin"] = task_data.LongFrozenMargin;
	data["Margin"] = task_data.Margin;
	data["DynamicRights"] = task_data.DynamicRights;
	data["ReleaseMargin"] = task_data.ReleaseMargin;
	data["PreBalance"] = task_data.PreBalance;
	data["InvestorID"] = task_data.InvestorID;
	data["LongMargin"] = task_data.LongMargin;
	data["CloseProfit"] = task_data.CloseProfit;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CUstpFtdcRspInstrumentField task_data = any_cast<CUstpFtdcRspInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["LongPosLimit"] = task_data.LongPosLimit;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PositionType"] = task_data.PositionType;
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

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CUstpFtdcRspExchangeField task_data = any_cast<CUstpFtdcRspExchangeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CUstpFtdcRspInvestorPositionField task_data = any_cast<CUstpFtdcRspInvestorPositionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenPremium"] = task_data.FrozenPremium;
	data["FrozenClosing"] = task_data.FrozenClosing;
	data["Currency"] = task_data.Currency;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["YdPosition"] = task_data.YdPosition;
	data["LastTradeID"] = task_data.LastTradeID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["ClientID"] = task_data.ClientID;
	data["YdPositionCost"] = task_data.YdPositionCost;
	data["InvestorID"] = task_data.InvestorID;
	data["PositionCost"] = task_data.PositionCost;
	data["UsedMargin"] = task_data.UsedMargin;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenPosition"] = task_data.FrozenPosition;
	data["Position"] = task_data.Position;
	data["LastOrderLocalID"] = task_data.LastOrderLocalID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSubscribeTopic(Task task)
{
	PyLock lock;
	CUstpFtdcDisseminationField task_data = any_cast<CUstpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubscribeTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryComplianceParam(Task task)
{
	PyLock lock;
	CUstpFtdcRspComplianceParamField task_data = any_cast<CUstpFtdcRspComplianceParamField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DailyMaxOrderActionVolume"] = task_data.DailyMaxOrderActionVolume;
	data["DailyMaxOrderVolume"] = task_data.DailyMaxOrderVolume;
	data["ClientID"] = task_data.ClientID;
	data["DailyMaxOrder"] = task_data.DailyMaxOrder;
	data["InvestorID"] = task_data.InvestorID;
	data["DailyMaxErrorOrder"] = task_data.DailyMaxErrorOrder;
	data["BrokerID"] = task_data.BrokerID;
	data["DailyMaxOrderAction"] = task_data.DailyMaxOrderAction;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryComplianceParam(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTopic(Task task)
{
	PyLock lock;
	CUstpFtdcDisseminationField task_data = any_cast<CUstpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTopic(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorFee(Task task)
{
	PyLock lock;
	CUstpFtdcInvestorFeeField task_data = any_cast<CUstpFtdcInvestorFeeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OTFeeRate"] = task_data.OTFeeRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OTFeeAmt"] = task_data.OTFeeAmt;
	data["OpenFeeAmt"] = task_data.OpenFeeAmt;
	data["ClientID"] = task_data.ClientID;
	data["BrokerID"] = task_data.BrokerID;
	data["OpenFeeRate"] = task_data.OpenFeeRate;
	data["OffsetFeeAmt"] = task_data.OffsetFeeAmt;
	data["OffsetFeeRate"] = task_data.OffsetFeeRate;
	data["ProductID"] = task_data.ProductID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorFee(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorMargin(Task task)
{
	PyLock lock;
	CUstpFtdcInvestorMarginField task_data = any_cast<CUstpFtdcInvestorMarginField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["LongMarginRate"] = task_data.LongMarginRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientID"] = task_data.ClientID;
	data["BrokerID"] = task_data.BrokerID;
	data["LongMarginAmt"] = task_data.LongMarginAmt;
	data["ShortMarginAmt"] = task_data.ShortMarginAmt;
	data["ShortMarginRate"] = task_data.ShortMarginRate;
	data["ProductID"] = task_data.ProductID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorMargin(data, error, task.task_id, task.task_last);
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

int TdApi::registerCertificateFile(string pszCertFileName, string pszKeyFileName, string pszCaFileName, string pszKeyFilePassword)
{
	int i = this->api->RegisterCertificateFile(pszCertFileName.c_str(), pszKeyFileName.c_str(), pszCaFileName.c_str(), pszKeyFilePassword.c_str());
	return i;
}

void TdApi::subscribePrivateTopic(int nType)
{
	//该函数为手动编写
	USTP_TE_RESUME_TYPE type;

	switch (nType)
	{
	case 0:
	{
		type = USTP_TERT_RESTART;
		break;
	};

	case 1:
	{
		type = USTP_TERT_RESUME;
		break;
	};

	case 2:
	{
		type = USTP_TERT_QUICK;
		break;
	};
	}

	this->api->SubscribePrivateTopic(type);
};

void TdApi::subscribePublicTopic(int nType)
{
	//该函数为手动编写
	USTP_TE_RESUME_TYPE type;

	switch (nType)
	{
	case 0:
	{
		type = USTP_TERT_RESTART;
		break;
	};

	case 1:
	{
		type = USTP_TERT_RESUME;
		break;
	};

	case 2:
	{
		type = USTP_TERT_QUICK;
		break;
	};
	}

	this->api->SubscribePublicTopic(type);
};

void TdApi::subscribeUserTopic(int nType)
{
	//该函数为手动编写
	USTP_TE_RESUME_TYPE type;

	switch (nType)
	{
	case 0:
	{
		type = USTP_TERT_RESTART;
		break;
	};

	case 1:
	{
		type = USTP_TERT_RESUME;
		break;
	};

	case 2:
	{
		type = USTP_TERT_QUICK;
		break;
	};
	}

	this->api->SubscribeUserTopic(type);
};

void TdApi::setHeartbeatTimeout(int timeout)
{
	//该函数为手动编写
	this->api->SetHeartbeatTimeout(timeout);
}

int TdApi::openRequestLog(string pszReqLogFileName)
{
	//该函数为手动编写
	int i = this->api->OpenRequestLog(pszReqLogFileName.c_str());
	return i;
}

int TdApi::openResponseLog(string pszReqLogFileName)
{
	//该函数为手动编写
	int i = this->api->OpenResponseLog(pszReqLogFileName.c_str());
	return i;
}

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CUstpFtdcReqUserLoginField myreq = CUstpFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
	getChar(req, "UserProductInfo", myreq.UserProductInfo);
	getChar(req, "UserID", myreq.UserID);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ProtocolInfo", myreq.ProtocolInfo);
	getChar(req, "Password", myreq.Password);
	getChar(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CUstpFtdcReqUserLogoutField myreq = CUstpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CUstpFtdcUserPasswordUpdateField myreq = CUstpFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CUstpFtdcInputOrderField myreq = CUstpFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getChar(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "GTDDate", myreq.GTDDate);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "UserCustom", myreq.UserCustom);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);

	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "Direction", &myreq.Direction);
	
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);

	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CUstpFtdcOrderActionField myreq = CUstpFtdcOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getChar(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
	getChar(req, "UserOrderLocalID", myreq.UserOrderLocalID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CUstpFtdcQryOrderField myreq = CUstpFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CUstpFtdcQryTradeField myreq = CUstpFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "TradeID", myreq.TradeID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryUserInvestor(dict req, int nRequestID)
{
	CUstpFtdcQryUserInvestorField myreq = CUstpFtdcQryUserInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryUserInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
{
	CUstpFtdcQryTradingCodeField myreq = CUstpFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorAccount(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorAccountField myreq = CUstpFtdcQryInvestorAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CUstpFtdcQryInstrumentField myreq = CUstpFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CUstpFtdcQryExchangeField myreq = CUstpFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorPositionField myreq = CUstpFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqSubscribeTopic(dict req, int nRequestID)
{
	CUstpFtdcDisseminationField myreq = CUstpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqSubscribeTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryComplianceParam(dict req, int nRequestID)
{
	CUstpFtdcQryComplianceParamField myreq = CUstpFtdcQryComplianceParamField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryComplianceParam(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTopic(dict req, int nRequestID)
{
	CUstpFtdcDisseminationField myreq = CUstpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqQryTopic(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorFee(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorFeeField myreq = CUstpFtdcQryInvestorFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorFee(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorMargin(dict req, int nRequestID)
{
	CUstpFtdcQryInvestorMarginField myreq = CUstpFtdcQryInvestorMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InvestorID", myreq.InvestorID);
	int i = this->api->ReqQryInvestorMargin(&myreq, nRequestID);
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

	virtual void onRspQryTradingCode(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTradingCode")(data, error, id, last);
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

	virtual void onRspQryComplianceParam(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryComplianceParam")(data, error, id, last);
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

};

BOOST_PYTHON_MODULE(vnfemastd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("createFtdcTraderApi", &TdApiWrap::createFtdcTraderApi)
		.def("release", &TdApiWrap::release)
		.def("init", &TdApiWrap::init)
		.def("join", &TdApiWrap::join)
		.def("exit", &TdApiWrap::exit)
		.def("getTradingDay", &TdApiWrap::getTradingDay)
		.def("registerFront", &TdApiWrap::registerFront)
		.def("registerNameServer", &TdApiWrap::registerNameServer)
		.def("registerCertificateFile", &TdApiWrap::registerCertificateFile)
		.def("subscribePrivateTopic", &TdApiWrap::subscribePrivateTopic)
		.def("subscribePublicTopic", &TdApiWrap::subscribePublicTopic)
		.def("subscribeUserTopic", &TdApiWrap::subscribeUserTopic)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqUserPasswordUpdate", &TdApiWrap::reqUserPasswordUpdate)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqQryOrder", &TdApiWrap::reqQryOrder)
		.def("reqQryTrade", &TdApiWrap::reqQryTrade)
		.def("reqQryUserInvestor", &TdApiWrap::reqQryUserInvestor)
		.def("reqQryTradingCode", &TdApiWrap::reqQryTradingCode)
		.def("reqQryInvestorAccount", &TdApiWrap::reqQryInvestorAccount)
		.def("reqQryInstrument", &TdApiWrap::reqQryInstrument)
		.def("reqQryExchange", &TdApiWrap::reqQryExchange)
		.def("reqQryInvestorPosition", &TdApiWrap::reqQryInvestorPosition)
		.def("reqSubscribeTopic", &TdApiWrap::reqSubscribeTopic)
		.def("reqQryComplianceParam", &TdApiWrap::reqQryComplianceParam)
		.def("reqQryTopic", &TdApiWrap::reqQryTopic)
		.def("reqQryInvestorFee", &TdApiWrap::reqQryInvestorFee)
		.def("reqQryInvestorMargin", &TdApiWrap::reqQryInvestorMargin)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&TdApiWrap::onHeartBeatWarning))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspUserPasswordUpdate))
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onRtnFlowMessageCancel", pure_virtual(&TdApiWrap::onRtnFlowMessageCancel))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onErrRtnOrderInsert", pure_virtual(&TdApiWrap::onErrRtnOrderInsert))
		.def("onErrRtnOrderAction", pure_virtual(&TdApiWrap::onErrRtnOrderAction))
		.def("onRtnInstrumentStatus", pure_virtual(&TdApiWrap::onRtnInstrumentStatus))
		.def("onRtnInvestorAccountDeposit", pure_virtual(&TdApiWrap::onRtnInvestorAccountDeposit))
		.def("onRspQryOrder", pure_virtual(&TdApiWrap::onRspQryOrder))
		.def("onRspQryTrade", pure_virtual(&TdApiWrap::onRspQryTrade))
		.def("onRspQryUserInvestor", pure_virtual(&TdApiWrap::onRspQryUserInvestor))
		.def("onRspQryTradingCode", pure_virtual(&TdApiWrap::onRspQryTradingCode))
		.def("onRspQryInvestorAccount", pure_virtual(&TdApiWrap::onRspQryInvestorAccount))
		.def("onRspQryInstrument", pure_virtual(&TdApiWrap::onRspQryInstrument))
		.def("onRspQryExchange", pure_virtual(&TdApiWrap::onRspQryExchange))
		.def("onRspQryInvestorPosition", pure_virtual(&TdApiWrap::onRspQryInvestorPosition))
		.def("onRspSubscribeTopic", pure_virtual(&TdApiWrap::onRspSubscribeTopic))
		.def("onRspQryComplianceParam", pure_virtual(&TdApiWrap::onRspQryComplianceParam))
		.def("onRspQryTopic", pure_virtual(&TdApiWrap::onRspQryTopic))
		.def("onRspQryInvestorFee", pure_virtual(&TdApiWrap::onRspQryInvestorFee))
		.def("onRspQryInvestorMargin", pure_virtual(&TdApiWrap::onRspQryInvestorMargin))
		;
}