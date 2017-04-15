// vnctptd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnctptd.h"


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

void TdApi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPAUTHENTICATE;

	if (pRspAuthenticateField)
	{
		task.task_data = *pRspAuthenticateField;
	}
	else
	{
		CThostFtdcRspAuthenticateField empty_data = CThostFtdcRspAuthenticateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CThostFtdcRspUserLoginField empty_data = CThostFtdcRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pUserLogout)
	{
		task.task_data = *pUserLogout;
	}
	else
	{
		CThostFtdcUserLogoutField empty_data = CThostFtdcUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;

	if (pUserPasswordUpdate)
	{
		task.task_data = *pUserPasswordUpdate;
	}
	else
	{
		CThostFtdcUserPasswordUpdateField empty_data = CThostFtdcUserPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGACCOUNTPASSWORDUPDATE;

	if (pTradingAccountPasswordUpdate)
	{
		task.task_data = *pTradingAccountPasswordUpdate;
	}
	else
	{
		CThostFtdcTradingAccountPasswordUpdateField empty_data = CThostFtdcTradingAccountPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CThostFtdcInputOrderField empty_data = CThostFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPPARKEDORDERINSERT;

	if (pParkedOrder)
	{
		task.task_data = *pParkedOrder;
	}
	else
	{
		CThostFtdcParkedOrderField empty_data = CThostFtdcParkedOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPPARKEDORDERACTION;

	if (pParkedOrderAction)
	{
		task.task_data = *pParkedOrderAction;
	}
	else
	{
		CThostFtdcParkedOrderActionField empty_data = CThostFtdcParkedOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;

	if (pInputOrderAction)
	{
		task.task_data = *pInputOrderAction;
	}
	else
	{
		CThostFtdcInputOrderActionField empty_data = CThostFtdcInputOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQUERYMAXORDERVOLUME;

	if (pQueryMaxOrderVolume)
	{
		task.task_data = *pQueryMaxOrderVolume;
	}
	else
	{
		CThostFtdcQueryMaxOrderVolumeField empty_data = CThostFtdcQueryMaxOrderVolumeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSETTLEMENTINFOCONFIRM;

	if (pSettlementInfoConfirm)
	{
		task.task_data = *pSettlementInfoConfirm;
	}
	else
	{
		CThostFtdcSettlementInfoConfirmField empty_data = CThostFtdcSettlementInfoConfirmField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPREMOVEPARKEDORDER;

	if (pRemoveParkedOrder)
	{
		task.task_data = *pRemoveParkedOrder;
	}
	else
	{
		CThostFtdcRemoveParkedOrderField empty_data = CThostFtdcRemoveParkedOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPREMOVEPARKEDORDERACTION;

	if (pRemoveParkedOrderAction)
	{
		task.task_data = *pRemoveParkedOrderAction;
	}
	else
	{
		CThostFtdcRemoveParkedOrderActionField empty_data = CThostFtdcRemoveParkedOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERINSERT;

	if (pInputExecOrder)
	{
		task.task_data = *pInputExecOrder;
	}
	else
	{
		CThostFtdcInputExecOrderField empty_data = CThostFtdcInputExecOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERACTION;

	if (pInputExecOrderAction)
	{
		task.task_data = *pInputExecOrderAction;
	}
	else
	{
		CThostFtdcInputExecOrderActionField empty_data = CThostFtdcInputExecOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFORQUOTEINSERT;

	if (pInputForQuote)
	{
		task.task_data = *pInputForQuote;
	}
	else
	{
		CThostFtdcInputForQuoteField empty_data = CThostFtdcInputForQuoteField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQUOTEINSERT;

	if (pInputQuote)
	{
		task.task_data = *pInputQuote;
	}
	else
	{
		CThostFtdcInputQuoteField empty_data = CThostFtdcInputQuoteField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQUOTEACTION;

	if (pInputQuoteAction)
	{
		task.task_data = *pInputQuoteAction;
	}
	else
	{
		CThostFtdcInputQuoteActionField empty_data = CThostFtdcInputQuoteActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspLockInsert(CThostFtdcInputLockField *pInputLock, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPLOCKINSERT;

	if (pInputLock)
	{
		task.task_data = *pInputLock;
	}
	else
	{
		CThostFtdcInputLockField empty_data = CThostFtdcInputLockField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPCOMBACTIONINSERT;

	if (pInputCombAction)
	{
		task.task_data = *pInputCombAction;
	}
	else
	{
		CThostFtdcInputCombActionField empty_data = CThostFtdcInputCombActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CThostFtdcOrderField empty_data = CThostFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CThostFtdcTradeField empty_data = CThostFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;

	if (pInvestorPosition)
	{
		task.task_data = *pInvestorPosition;
	}
	else
	{
		CThostFtdcInvestorPositionField empty_data = CThostFtdcInvestorPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGACCOUNT;

	if (pTradingAccount)
	{
		task.task_data = *pTradingAccount;
	}
	else
	{
		CThostFtdcTradingAccountField empty_data = CThostFtdcTradingAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTOR;

	if (pInvestor)
	{
		task.task_data = *pInvestor;
	}
	else
	{
		CThostFtdcInvestorField empty_data = CThostFtdcInvestorField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGCODE;

	if (pTradingCode)
	{
		task.task_data = *pTradingCode;
	}
	else
	{
		CThostFtdcTradingCodeField empty_data = CThostFtdcTradingCodeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTMARGINRATE;

	if (pInstrumentMarginRate)
	{
		task.task_data = *pInstrumentMarginRate;
	}
	else
	{
		CThostFtdcInstrumentMarginRateField empty_data = CThostFtdcInstrumentMarginRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTCOMMISSIONRATE;

	if (pInstrumentCommissionRate)
	{
		task.task_data = *pInstrumentCommissionRate;
	}
	else
	{
		CThostFtdcInstrumentCommissionRateField empty_data = CThostFtdcInstrumentCommissionRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;

	if (pExchange)
	{
		task.task_data = *pExchange;
	}
	else
	{
		CThostFtdcExchangeField empty_data = CThostFtdcExchangeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPRODUCT;

	if (pProduct)
	{
		task.task_data = *pProduct;
	}
	else
	{
		CThostFtdcProductField empty_data = CThostFtdcProductField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;

	if (pInstrument)
	{
		task.task_data = *pInstrument;
	}
	else
	{
		CThostFtdcInstrumentField empty_data = CThostFtdcInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYDEPTHMARKETDATA;

	if (pDepthMarketData)
	{
		task.task_data = *pDepthMarketData;
	}
	else
	{
		CThostFtdcDepthMarketDataField empty_data = CThostFtdcDepthMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSETTLEMENTINFO;

	if (pSettlementInfo)
	{
		task.task_data = *pSettlementInfo;
	}
	else
	{
		CThostFtdcSettlementInfoField empty_data = CThostFtdcSettlementInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERBANK;

	if (pTransferBank)
	{
		task.task_data = *pTransferBank;
	}
	else
	{
		CThostFtdcTransferBankField empty_data = CThostFtdcTransferBankField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITIONDETAIL;

	if (pInvestorPositionDetail)
	{
		task.task_data = *pInvestorPositionDetail;
	}
	else
	{
		CThostFtdcInvestorPositionDetailField empty_data = CThostFtdcInvestorPositionDetailField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYNOTICE;

	if (pNotice)
	{
		task.task_data = *pNotice;
	}
	else
	{
		CThostFtdcNoticeField empty_data = CThostFtdcNoticeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSETTLEMENTINFOCONFIRM;

	if (pSettlementInfoConfirm)
	{
		task.task_data = *pSettlementInfoConfirm;
	}
	else
	{
		CThostFtdcSettlementInfoConfirmField empty_data = CThostFtdcSettlementInfoConfirmField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL;

	if (pInvestorPositionCombineDetail)
	{
		task.task_data = *pInvestorPositionCombineDetail;
	}
	else
	{
		CThostFtdcInvestorPositionCombineDetailField empty_data = CThostFtdcInvestorPositionCombineDetailField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCFMMCTRADINGACCOUNTKEY;

	if (pCFMMCTradingAccountKey)
	{
		task.task_data = *pCFMMCTradingAccountKey;
	}
	else
	{
		CThostFtdcCFMMCTradingAccountKeyField empty_data = CThostFtdcCFMMCTradingAccountKeyField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEWARRANTOFFSET;

	if (pEWarrantOffset)
	{
		task.task_data = *pEWarrantOffset;
	}
	else
	{
		CThostFtdcEWarrantOffsetField empty_data = CThostFtdcEWarrantOffsetField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPRODUCTGROUPMARGIN;

	if (pInvestorProductGroupMargin)
	{
		task.task_data = *pInvestorProductGroupMargin;
	}
	else
	{
		CThostFtdcInvestorProductGroupMarginField empty_data = CThostFtdcInvestorProductGroupMarginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGEMARGINRATE;

	if (pExchangeMarginRate)
	{
		task.task_data = *pExchangeMarginRate;
	}
	else
	{
		CThostFtdcExchangeMarginRateField empty_data = CThostFtdcExchangeMarginRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGEMARGINRATEADJUST;

	if (pExchangeMarginRateAdjust)
	{
		task.task_data = *pExchangeMarginRateAdjust;
	}
	else
	{
		CThostFtdcExchangeMarginRateAdjustField empty_data = CThostFtdcExchangeMarginRateAdjustField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGERATE;

	if (pExchangeRate)
	{
		task.task_data = *pExchangeRate;
	}
	else
	{
		CThostFtdcExchangeRateField empty_data = CThostFtdcExchangeRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSECAGENTACIDMAP;

	if (pSecAgentACIDMap)
	{
		task.task_data = *pSecAgentACIDMap;
	}
	else
	{
		CThostFtdcSecAgentACIDMapField empty_data = CThostFtdcSecAgentACIDMapField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPRODUCTEXCHRATE;

	if (pProductExchRate)
	{
		task.task_data = *pProductExchRate;
	}
	else
	{
		CThostFtdcProductExchRateField empty_data = CThostFtdcProductExchRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPRODUCTGROUP;

	if (pProductGroup)
	{
		task.task_data = *pProductGroup;
	}
	else
	{
		CThostFtdcProductGroupField empty_data = CThostFtdcProductGroupField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONINSTRTRADECOST;

	if (pOptionInstrTradeCost)
	{
		task.task_data = *pOptionInstrTradeCost;
	}
	else
	{
		CThostFtdcOptionInstrTradeCostField empty_data = CThostFtdcOptionInstrTradeCostField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONINSTRCOMMRATE;

	if (pOptionInstrCommRate)
	{
		task.task_data = *pOptionInstrCommRate;
	}
	else
	{
		CThostFtdcOptionInstrCommRateField empty_data = CThostFtdcOptionInstrCommRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXECORDER;

	if (pExecOrder)
	{
		task.task_data = *pExecOrder;
	}
	else
	{
		CThostFtdcExecOrderField empty_data = CThostFtdcExecOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFORQUOTE;

	if (pForQuote)
	{
		task.task_data = *pForQuote;
	}
	else
	{
		CThostFtdcForQuoteField empty_data = CThostFtdcForQuoteField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYQUOTE;

	if (pQuote)
	{
		task.task_data = *pQuote;
	}
	else
	{
		CThostFtdcQuoteField empty_data = CThostFtdcQuoteField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryLock(CThostFtdcLockField *pLock, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYLOCK;

	if (pLock)
	{
		task.task_data = *pLock;
	}
	else
	{
		CThostFtdcLockField empty_data = CThostFtdcLockField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryLockPosition(CThostFtdcLockPositionField *pLockPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYLOCKPOSITION;

	if (pLockPosition)
	{
		task.task_data = *pLockPosition;
	}
	else
	{
		CThostFtdcLockPositionField empty_data = CThostFtdcLockPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorLevel(CThostFtdcInvestorLevelField *pInvestorLevel, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORLEVEL;

	if (pInvestorLevel)
	{
		task.task_data = *pInvestorLevel;
	}
	else
	{
		CThostFtdcInvestorLevelField empty_data = CThostFtdcInvestorLevelField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExecFreeze(CThostFtdcExecFreezeField *pExecFreeze, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXECFREEZE;

	if (pExecFreeze)
	{
		task.task_data = *pExecFreeze;
	}
	else
	{
		CThostFtdcExecFreezeField empty_data = CThostFtdcExecFreezeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMBINSTRUMENTGUARD;

	if (pCombInstrumentGuard)
	{
		task.task_data = *pCombInstrumentGuard;
	}
	else
	{
		CThostFtdcCombInstrumentGuardField empty_data = CThostFtdcCombInstrumentGuardField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMBACTION;

	if (pCombAction)
	{
		task.task_data = *pCombAction;
	}
	else
	{
		CThostFtdcCombActionField empty_data = CThostFtdcCombActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERSERIAL;

	if (pTransferSerial)
	{
		task.task_data = *pTransferSerial;
	}
	else
	{
		CThostFtdcTransferSerialField empty_data = CThostFtdcTransferSerialField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTREGISTER;

	if (pAccountregister)
	{
		task.task_data = *pAccountregister;
	}
	else
	{
		CThostFtdcAccountregisterField empty_data = CThostFtdcAccountregisterField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CThostFtdcOrderField empty_data = CThostFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	Task task = Task();
	task.task_name = ONRTNTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CThostFtdcTradeField empty_data = CThostFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CThostFtdcInputOrderField empty_data = CThostFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;

	if (pOrderAction)
	{
		task.task_data = *pOrderAction;
	}
	else
	{
		CThostFtdcOrderActionField empty_data = CThostFtdcOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;

	if (pInstrumentStatus)
	{
		task.task_data = *pInstrumentStatus;
	}
	else
	{
		CThostFtdcInstrumentStatusField empty_data = CThostFtdcInstrumentStatusField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
	Task task = Task();
	task.task_name = ONRTNTRADINGNOTICE;

	if (pTradingNoticeInfo)
	{
		task.task_data = *pTradingNoticeInfo;
	}
	else
	{
		CThostFtdcTradingNoticeInfoField empty_data = CThostFtdcTradingNoticeInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)
{
	Task task = Task();
	task.task_name = ONRTNERRORCONDITIONALORDER;

	if (pErrorConditionalOrder)
	{
		task.task_data = *pErrorConditionalOrder;
	}
	else
	{
		CThostFtdcErrorConditionalOrderField empty_data = CThostFtdcErrorConditionalOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
	Task task = Task();
	task.task_name = ONRTNEXECORDER;

	if (pExecOrder)
	{
		task.task_data = *pExecOrder;
	}
	else
	{
		CThostFtdcExecOrderField empty_data = CThostFtdcExecOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNEXECORDERINSERT;

	if (pInputExecOrder)
	{
		task.task_data = *pInputExecOrder;
	}
	else
	{
		CThostFtdcInputExecOrderField empty_data = CThostFtdcInputExecOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNEXECORDERACTION;

	if (pExecOrderAction)
	{
		task.task_data = *pExecOrderAction;
	}
	else
	{
		CThostFtdcExecOrderActionField empty_data = CThostFtdcExecOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNFORQUOTEINSERT;

	if (pInputForQuote)
	{
		task.task_data = *pInputForQuote;
	}
	else
	{
		CThostFtdcInputForQuoteField empty_data = CThostFtdcInputForQuoteField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
	Task task = Task();
	task.task_name = ONRTNQUOTE;

	if (pQuote)
	{
		task.task_data = *pQuote;
	}
	else
	{
		CThostFtdcQuoteField empty_data = CThostFtdcQuoteField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNQUOTEINSERT;

	if (pInputQuote)
	{
		task.task_data = *pInputQuote;
	}
	else
	{
		CThostFtdcInputQuoteField empty_data = CThostFtdcInputQuoteField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNQUOTEACTION;

	if (pQuoteAction)
	{
		task.task_data = *pQuoteAction;
	}
	else
	{
		CThostFtdcQuoteActionField empty_data = CThostFtdcQuoteActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	Task task = Task();
	task.task_name = ONRTNFORQUOTERSP;

	if (pForQuoteRsp)
	{
		task.task_data = *pForQuoteRsp;
	}
	else
	{
		CThostFtdcForQuoteRspField empty_data = CThostFtdcForQuoteRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken)
{
	Task task = Task();
	task.task_name = ONRTNCFMMCTRADINGACCOUNTTOKEN;

	if (pCFMMCTradingAccountToken)
	{
		task.task_data = *pCFMMCTradingAccountToken;
	}
	else
	{
		CThostFtdcCFMMCTradingAccountTokenField empty_data = CThostFtdcCFMMCTradingAccountTokenField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnLock(CThostFtdcLockField *pLock)
{
	Task task = Task();
	task.task_name = ONRTNLOCK;

	if (pLock)
	{
		task.task_data = *pLock;
	}
	else
	{
		CThostFtdcLockField empty_data = CThostFtdcLockField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnLockInsert(CThostFtdcInputLockField *pInputLock, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNLOCKINSERT;

	if (pInputLock)
	{
		task.task_data = *pInputLock;
	}
	else
	{
		CThostFtdcInputLockField empty_data = CThostFtdcInputLockField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnCombAction(CThostFtdcCombActionField *pCombAction)
{
	Task task = Task();
	task.task_name = ONRTNCOMBACTION;

	if (pCombAction)
	{
		task.task_data = *pCombAction;
	}
	else
	{
		CThostFtdcCombActionField empty_data = CThostFtdcCombActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNCOMBACTIONINSERT;

	if (pInputCombAction)
	{
		task.task_data = *pInputCombAction;
	}
	else
	{
		CThostFtdcInputCombActionField empty_data = CThostFtdcInputCombActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACTBANK;

	if (pContractBank)
	{
		task.task_data = *pContractBank;
	}
	else
	{
		CThostFtdcContractBankField empty_data = CThostFtdcContractBankField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPARKEDORDER;

	if (pParkedOrder)
	{
		task.task_data = *pParkedOrder;
	}
	else
	{
		CThostFtdcParkedOrderField empty_data = CThostFtdcParkedOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPARKEDORDERACTION;

	if (pParkedOrderAction)
	{
		task.task_data = *pParkedOrderAction;
	}
	else
	{
		CThostFtdcParkedOrderActionField empty_data = CThostFtdcParkedOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGNOTICE;

	if (pTradingNotice)
	{
		task.task_data = *pTradingNotice;
	}
	else
	{
		CThostFtdcTradingNoticeField empty_data = CThostFtdcTradingNoticeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYBROKERTRADINGPARAMS;

	if (pBrokerTradingParams)
	{
		task.task_data = *pBrokerTradingParams;
	}
	else
	{
		CThostFtdcBrokerTradingParamsField empty_data = CThostFtdcBrokerTradingParamsField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYBROKERTRADINGALGOS;

	if (pBrokerTradingAlgos)
	{
		task.task_data = *pBrokerTradingAlgos;
	}
	else
	{
		CThostFtdcBrokerTradingAlgosField empty_data = CThostFtdcBrokerTradingAlgosField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN;

	if (pQueryCFMMCTradingAccountToken)
	{
		task.task_data = *pQueryCFMMCTradingAccountToken;
	}
	else
	{
		CThostFtdcQueryCFMMCTradingAccountTokenField empty_data = CThostFtdcQueryCFMMCTradingAccountTokenField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMBANKTOFUTUREBYBANK;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CThostFtdcRspTransferField empty_data = CThostFtdcRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMFUTURETOBANKBYBANK;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CThostFtdcRspTransferField empty_data = CThostFtdcRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal)
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYBANK;

	if (pRspRepeal)
	{
		task.task_data = *pRspRepeal;
	}
	else
	{
		CThostFtdcRspRepealField empty_data = CThostFtdcRspRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal)
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMFUTURETOBANKBYBANK;

	if (pRspRepeal)
	{
		task.task_data = *pRspRepeal;
	}
	else
	{
		CThostFtdcRspRepealField empty_data = CThostFtdcRspRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMBANKTOFUTUREBYFUTURE;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CThostFtdcRspTransferField empty_data = CThostFtdcRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMFUTURETOBANKBYFUTURE;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CThostFtdcRspTransferField empty_data = CThostFtdcRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL;

	if (pRspRepeal)
	{
		task.task_data = *pRspRepeal;
	}
	else
	{
		CThostFtdcRspRepealField empty_data = CThostFtdcRspRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL;

	if (pRspRepeal)
	{
		task.task_data = *pRspRepeal;
	}
	else
	{
		CThostFtdcRspRepealField empty_data = CThostFtdcRspRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)
{
	Task task = Task();
	task.task_name = ONRTNQUERYBANKBALANCEBYFUTURE;

	if (pNotifyQueryAccount)
	{
		task.task_data = *pNotifyQueryAccount;
	}
	else
	{
		CThostFtdcNotifyQueryAccountField empty_data = CThostFtdcNotifyQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNBANKTOFUTUREBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CThostFtdcReqTransferField empty_data = CThostFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNFUTURETOBANKBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CThostFtdcReqTransferField empty_data = CThostFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL;

	if (pReqRepeal)
	{
		task.task_data = *pReqRepeal;
	}
	else
	{
		CThostFtdcReqRepealField empty_data = CThostFtdcReqRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL;

	if (pReqRepeal)
	{
		task.task_data = *pReqRepeal;
	}
	else
	{
		CThostFtdcReqRepealField empty_data = CThostFtdcReqRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNQUERYBANKBALANCEBYFUTURE;

	if (pReqQueryAccount)
	{
		task.task_data = *pReqQueryAccount;
	}
	else
	{
		CThostFtdcReqQueryAccountField empty_data = CThostFtdcReqQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYFUTURE;

	if (pRspRepeal)
	{
		task.task_data = *pRspRepeal;
	}
	else
	{
		CThostFtdcRspRepealField empty_data = CThostFtdcRspRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMFUTURETOBANKBYFUTURE;

	if (pRspRepeal)
	{
		task.task_data = *pRspRepeal;
	}
	else
	{
		CThostFtdcRspRepealField empty_data = CThostFtdcRspRepealField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFROMBANKTOFUTUREBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CThostFtdcReqTransferField empty_data = CThostFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFROMFUTURETOBANKBYFUTURE;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CThostFtdcReqTransferField empty_data = CThostFtdcReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQUERYBANKACCOUNTMONEYBYFUTURE;

	if (pReqQueryAccount)
	{
		task.task_data = *pReqQueryAccount;
	}
	else
	{
		CThostFtdcReqQueryAccountField empty_data = CThostFtdcReqQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount)
{
	Task task = Task();
	task.task_name = ONRTNOPENACCOUNTBYBANK;

	if (pOpenAccount)
	{
		task.task_data = *pOpenAccount;
	}
	else
	{
		CThostFtdcOpenAccountField empty_data = CThostFtdcOpenAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount)
{
	Task task = Task();
	task.task_name = ONRTNCANCELACCOUNTBYBANK;

	if (pCancelAccount)
	{
		task.task_data = *pCancelAccount;
	}
	else
	{
		CThostFtdcCancelAccountField empty_data = CThostFtdcCancelAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount)
{
	Task task = Task();
	task.task_name = ONRTNCHANGEACCOUNTBYBANK;

	if (pChangeAccount)
	{
		task.task_data = *pChangeAccount;
	}
	else
	{
		CThostFtdcChangeAccountField empty_data = CThostFtdcChangeAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
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

		case ONRSPAUTHENTICATE:
		{
			this->processRspAuthenticate(task);
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

		case ONRSPTRADINGACCOUNTPASSWORDUPDATE:
		{
			this->processRspTradingAccountPasswordUpdate(task);
			break;
		}

		case ONRSPORDERINSERT:
		{
			this->processRspOrderInsert(task);
			break;
		}

		case ONRSPPARKEDORDERINSERT:
		{
			this->processRspParkedOrderInsert(task);
			break;
		}

		case ONRSPPARKEDORDERACTION:
		{
			this->processRspParkedOrderAction(task);
			break;
		}

		case ONRSPORDERACTION:
		{
			this->processRspOrderAction(task);
			break;
		}

		case ONRSPQUERYMAXORDERVOLUME:
		{
			this->processRspQueryMaxOrderVolume(task);
			break;
		}

		case ONRSPSETTLEMENTINFOCONFIRM:
		{
			this->processRspSettlementInfoConfirm(task);
			break;
		}

		case ONRSPREMOVEPARKEDORDER:
		{
			this->processRspRemoveParkedOrder(task);
			break;
		}

		case ONRSPREMOVEPARKEDORDERACTION:
		{
			this->processRspRemoveParkedOrderAction(task);
			break;
		}

		case ONRSPEXECORDERINSERT:
		{
			this->processRspExecOrderInsert(task);
			break;
		}

		case ONRSPEXECORDERACTION:
		{
			this->processRspExecOrderAction(task);
			break;
		}

		case ONRSPFORQUOTEINSERT:
		{
			this->processRspForQuoteInsert(task);
			break;
		}

		case ONRSPQUOTEINSERT:
		{
			this->processRspQuoteInsert(task);
			break;
		}

		case ONRSPQUOTEACTION:
		{
			this->processRspQuoteAction(task);
			break;
		}

		case ONRSPLOCKINSERT:
		{
			this->processRspLockInsert(task);
			break;
		}

		case ONRSPCOMBACTIONINSERT:
		{
			this->processRspCombActionInsert(task);
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

		case ONRSPQRYINVESTORPOSITION:
		{
			this->processRspQryInvestorPosition(task);
			break;
		}

		case ONRSPQRYTRADINGACCOUNT:
		{
			this->processRspQryTradingAccount(task);
			break;
		}

		case ONRSPQRYINVESTOR:
		{
			this->processRspQryInvestor(task);
			break;
		}

		case ONRSPQRYTRADINGCODE:
		{
			this->processRspQryTradingCode(task);
			break;
		}

		case ONRSPQRYINSTRUMENTMARGINRATE:
		{
			this->processRspQryInstrumentMarginRate(task);
			break;
		}

		case ONRSPQRYINSTRUMENTCOMMISSIONRATE:
		{
			this->processRspQryInstrumentCommissionRate(task);
			break;
		}

		case ONRSPQRYEXCHANGE:
		{
			this->processRspQryExchange(task);
			break;
		}

		case ONRSPQRYPRODUCT:
		{
			this->processRspQryProduct(task);
			break;
		}

		case ONRSPQRYINSTRUMENT:
		{
			this->processRspQryInstrument(task);
			break;
		}

		case ONRSPQRYDEPTHMARKETDATA:
		{
			this->processRspQryDepthMarketData(task);
			break;
		}

		case ONRSPQRYSETTLEMENTINFO:
		{
			this->processRspQrySettlementInfo(task);
			break;
		}

		case ONRSPQRYTRANSFERBANK:
		{
			this->processRspQryTransferBank(task);
			break;
		}

		case ONRSPQRYINVESTORPOSITIONDETAIL:
		{
			this->processRspQryInvestorPositionDetail(task);
			break;
		}

		case ONRSPQRYNOTICE:
		{
			this->processRspQryNotice(task);
			break;
		}

		case ONRSPQRYSETTLEMENTINFOCONFIRM:
		{
			this->processRspQrySettlementInfoConfirm(task);
			break;
		}

		case ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL:
		{
			this->processRspQryInvestorPositionCombineDetail(task);
			break;
		}

		case ONRSPQRYCFMMCTRADINGACCOUNTKEY:
		{
			this->processRspQryCFMMCTradingAccountKey(task);
			break;
		}

		case ONRSPQRYEWARRANTOFFSET:
		{
			this->processRspQryEWarrantOffset(task);
			break;
		}

		case ONRSPQRYINVESTORPRODUCTGROUPMARGIN:
		{
			this->processRspQryInvestorProductGroupMargin(task);
			break;
		}

		case ONRSPQRYEXCHANGEMARGINRATE:
		{
			this->processRspQryExchangeMarginRate(task);
			break;
		}

		case ONRSPQRYEXCHANGEMARGINRATEADJUST:
		{
			this->processRspQryExchangeMarginRateAdjust(task);
			break;
		}

		case ONRSPQRYEXCHANGERATE:
		{
			this->processRspQryExchangeRate(task);
			break;
		}

		case ONRSPQRYSECAGENTACIDMAP:
		{
			this->processRspQrySecAgentACIDMap(task);
			break;
		}

		case ONRSPQRYPRODUCTEXCHRATE:
		{
			this->processRspQryProductExchRate(task);
			break;
		}

		case ONRSPQRYPRODUCTGROUP:
		{
			this->processRspQryProductGroup(task);
			break;
		}

		case ONRSPQRYOPTIONINSTRTRADECOST:
		{
			this->processRspQryOptionInstrTradeCost(task);
			break;
		}

		case ONRSPQRYOPTIONINSTRCOMMRATE:
		{
			this->processRspQryOptionInstrCommRate(task);
			break;
		}

		case ONRSPQRYEXECORDER:
		{
			this->processRspQryExecOrder(task);
			break;
		}

		case ONRSPQRYFORQUOTE:
		{
			this->processRspQryForQuote(task);
			break;
		}

		case ONRSPQRYQUOTE:
		{
			this->processRspQryQuote(task);
			break;
		}

		case ONRSPQRYLOCK:
		{
			this->processRspQryLock(task);
			break;
		}

		case ONRSPQRYLOCKPOSITION:
		{
			this->processRspQryLockPosition(task);
			break;
		}

		case ONRSPQRYINVESTORLEVEL:
		{
			this->processRspQryInvestorLevel(task);
			break;
		}

		case ONRSPQRYEXECFREEZE:
		{
			this->processRspQryExecFreeze(task);
			break;
		}

		case ONRSPQRYCOMBINSTRUMENTGUARD:
		{
			this->processRspQryCombInstrumentGuard(task);
			break;
		}

		case ONRSPQRYCOMBACTION:
		{
			this->processRspQryCombAction(task);
			break;
		}

		case ONRSPQRYTRANSFERSERIAL:
		{
			this->processRspQryTransferSerial(task);
			break;
		}

		case ONRSPQRYACCOUNTREGISTER:
		{
			this->processRspQryAccountregister(task);
			break;
		}

		case ONRSPERROR:
		{
			this->processRspError(task);
			break;
		}

		case ONRTNORDER:
		{
			this->processRtnOrder(task);
			break;
		}

		case ONRTNTRADE:
		{
			this->processRtnTrade(task);
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

		case ONRTNTRADINGNOTICE:
		{
			this->processRtnTradingNotice(task);
			break;
		}

		case ONRTNERRORCONDITIONALORDER:
		{
			this->processRtnErrorConditionalOrder(task);
			break;
		}

		case ONRTNEXECORDER:
		{
			this->processRtnExecOrder(task);
			break;
		}

		case ONERRRTNEXECORDERINSERT:
		{
			this->processErrRtnExecOrderInsert(task);
			break;
		}

		case ONERRRTNEXECORDERACTION:
		{
			this->processErrRtnExecOrderAction(task);
			break;
		}

		case ONERRRTNFORQUOTEINSERT:
		{
			this->processErrRtnForQuoteInsert(task);
			break;
		}

		case ONRTNQUOTE:
		{
			this->processRtnQuote(task);
			break;
		}

		case ONERRRTNQUOTEINSERT:
		{
			this->processErrRtnQuoteInsert(task);
			break;
		}

		case ONERRRTNQUOTEACTION:
		{
			this->processErrRtnQuoteAction(task);
			break;
		}

		case ONRTNFORQUOTERSP:
		{
			this->processRtnForQuoteRsp(task);
			break;
		}

		case ONRTNCFMMCTRADINGACCOUNTTOKEN:
		{
			this->processRtnCFMMCTradingAccountToken(task);
			break;
		}

		case ONRTNLOCK:
		{
			this->processRtnLock(task);
			break;
		}

		case ONERRRTNLOCKINSERT:
		{
			this->processErrRtnLockInsert(task);
			break;
		}

		case ONRTNCOMBACTION:
		{
			this->processRtnCombAction(task);
			break;
		}

		case ONERRRTNCOMBACTIONINSERT:
		{
			this->processErrRtnCombActionInsert(task);
			break;
		}

		case ONRSPQRYCONTRACTBANK:
		{
			this->processRspQryContractBank(task);
			break;
		}

		case ONRSPQRYPARKEDORDER:
		{
			this->processRspQryParkedOrder(task);
			break;
		}

		case ONRSPQRYPARKEDORDERACTION:
		{
			this->processRspQryParkedOrderAction(task);
			break;
		}

		case ONRSPQRYTRADINGNOTICE:
		{
			this->processRspQryTradingNotice(task);
			break;
		}

		case ONRSPQRYBROKERTRADINGPARAMS:
		{
			this->processRspQryBrokerTradingParams(task);
			break;
		}

		case ONRSPQRYBROKERTRADINGALGOS:
		{
			this->processRspQryBrokerTradingAlgos(task);
			break;
		}

		case ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN:
		{
			this->processRspQueryCFMMCTradingAccountToken(task);
			break;
		}

		case ONRTNFROMBANKTOFUTUREBYBANK:
		{
			this->processRtnFromBankToFutureByBank(task);
			break;
		}

		case ONRTNFROMFUTURETOBANKBYBANK:
		{
			this->processRtnFromFutureToBankByBank(task);
			break;
		}

		case ONRTNREPEALFROMBANKTOFUTUREBYBANK:
		{
			this->processRtnRepealFromBankToFutureByBank(task);
			break;
		}

		case ONRTNREPEALFROMFUTURETOBANKBYBANK:
		{
			this->processRtnRepealFromFutureToBankByBank(task);
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

		case ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL:
		{
			this->processRtnRepealFromBankToFutureByFutureManual(task);
			break;
		}

		case ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL:
		{
			this->processRtnRepealFromFutureToBankByFutureManual(task);
			break;
		}

		case ONRTNQUERYBANKBALANCEBYFUTURE:
		{
			this->processRtnQueryBankBalanceByFuture(task);
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

		case ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL:
		{
			this->processErrRtnRepealBankToFutureByFutureManual(task);
			break;
		}

		case ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL:
		{
			this->processErrRtnRepealFutureToBankByFutureManual(task);
			break;
		}

		case ONERRRTNQUERYBANKBALANCEBYFUTURE:
		{
			this->processErrRtnQueryBankBalanceByFuture(task);
			break;
		}

		case ONRTNREPEALFROMBANKTOFUTUREBYFUTURE:
		{
			this->processRtnRepealFromBankToFutureByFuture(task);
			break;
		}

		case ONRTNREPEALFROMFUTURETOBANKBYFUTURE:
		{
			this->processRtnRepealFromFutureToBankByFuture(task);
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

		case ONRSPQUERYBANKACCOUNTMONEYBYFUTURE:
		{
			this->processRspQueryBankAccountMoneyByFuture(task);
			break;
		}

		case ONRTNOPENACCOUNTBYBANK:
		{
			this->processRtnOpenAccountByBank(task);
			break;
		}

		case ONRTNCANCELACCOUNTBYBANK:
		{
			this->processRtnCancelAccountByBank(task);
			break;
		}

		case ONRTNCHANGEACCOUNTBYBANK:
		{
			this->processRtnChangeAccountByBank(task);
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

void TdApi::processRspAuthenticate(Task task)
{
	PyLock lock;
	CThostFtdcRspAuthenticateField task_data = any_cast<CThostFtdcRspAuthenticateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["UserProductInfo"] = task_data.UserProductInfo;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspAuthenticate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CThostFtdcRspUserLoginField task_data = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["SHFETime"] = task_data.SHFETime;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["INETime"] = task_data.INETime;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["FFEXTime"] = task_data.FFEXTime;
	data["BrokerID"] = task_data.BrokerID;
	data["DCETime"] = task_data.DCETime;
	data["LoginTime"] = task_data.LoginTime;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcUserPasswordUpdateField task_data = any_cast<CThostFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountPasswordUpdateField task_data = any_cast<CThostFtdcTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["CurrencyID"] = task_data.CurrencyID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Status"] = task_data.Status;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["UserType"] = task_data.UserType;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["ErrorID"] = task_data.ErrorID;
	data["ParkedOrderID"] = task_data.ParkedOrderID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspParkedOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Status"] = task_data.Status;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserType"] = task_data.UserType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ParkedOrderActionID"] = task_data.ParkedOrderActionID;
	data["FrontID"] = task_data.FrontID;
	data["ErrorID"] = task_data.ErrorID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderActionField task_data = any_cast<CThostFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryMaxOrderVolume(Task task)
{
	PyLock lock;
	CThostFtdcQueryMaxOrderVolumeField task_data = any_cast<CThostFtdcQueryMaxOrderVolumeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Direction"] = task_data.Direction;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ExchangeID"] = task_data.ExchangeID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxVolume"] = task_data.MaxVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryMaxOrderVolume(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmTime"] = task_data.ConfirmTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ConfirmDate"] = task_data.ConfirmDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderField task_data = any_cast<CThostFtdcRemoveParkedOrderField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParkedOrderID"] = task_data.ParkedOrderID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspRemoveParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderActionField task_data = any_cast<CThostFtdcRemoveParkedOrderActionField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParkedOrderActionID"] = task_data.ParkedOrderActionID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspRemoveParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CloseFlag"] = task_data.CloseFlag;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionType"] = task_data.ActionType;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspExecOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderActionField task_data = any_cast<CThostFtdcInputExecOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["UserID"] = task_data.UserID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspExecOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ForQuoteRef"] = task_data.ForQuoteRef;
	data["ExchangeID"] = task_data.ExchangeID;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspForQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["AskPrice"] = task_data.AskPrice;
	data["UserID"] = task_data.UserID;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidVolume"] = task_data.BidVolume;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["AskVolume"] = task_data.AskVolume;
	data["InvestorID"] = task_data.InvestorID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["BidPrice"] = task_data.BidPrice;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["BidOrderRef"] = task_data.BidOrderRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteActionField task_data = any_cast<CThostFtdcInputQuoteActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["QuoteActionRef"] = task_data.QuoteActionRef;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["FrontID"] = task_data.FrontID;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["QuoteRef"] = task_data.QuoteRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQuoteAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspLockInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputLockField task_data = any_cast<CThostFtdcInputLockField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserID"] = task_data.UserID;
	data["LockRef"] = task_data.LockRef;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["LockType"] = task_data.LockType;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspLockInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Direction"] = task_data.Direction;
	data["CombActionRef"] = task_data.CombActionRef;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombDirection"] = task_data.CombDirection;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspCombActionInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ParticipantID"] = task_data.ParticipantID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["ClientID"] = task_data.ClientID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TradeTime"] = task_data.TradeTime;
	data["Direction"] = task_data.Direction;
	data["ParticipantID"] = task_data.ParticipantID;
	data["Price"] = task_data.Price;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["TradeID"] = task_data.TradeID;
	data["TradeDate"] = task_data.TradeDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["TradeSource"] = task_data.TradeSource;
	data["PriceSource"] = task_data.PriceSource;
	data["TradingRole"] = task_data.TradingRole;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionField task_data = any_cast<CThostFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["StrikeFrozen"] = task_data.StrikeFrozen;
	data["CombPosition"] = task_data.CombPosition;
	data["CashIn"] = task_data.CashIn;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["CombLongFrozen"] = task_data.CombLongFrozen;
	data["CloseAmount"] = task_data.CloseAmount;
	data["PosiDirection"] = task_data.PosiDirection;
	data["YdPosition"] = task_data.YdPosition;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["AbandonFrozen"] = task_data.AbandonFrozen;
	data["OpenVolume"] = task_data.OpenVolume;
	data["CloseVolume"] = task_data.CloseVolume;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["YdStrikeFrozen"] = task_data.YdStrikeFrozen;
	data["InstrumentID"] = task_data.InstrumentID;
	data["PositionDate"] = task_data.PositionDate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["PreMargin"] = task_data.PreMargin;
	data["SettlementID"] = task_data.SettlementID;
	data["ShortFrozen"] = task_data.ShortFrozen;
	data["LongFrozen"] = task_data.LongFrozen;
	data["TodayPosition"] = task_data.TodayPosition;
	data["TradingDay"] = task_data.TradingDay;
	data["PositionCost"] = task_data.PositionCost;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["OpenAmount"] = task_data.OpenAmount;
	data["OpenCost"] = task_data.OpenCost;
	data["Position"] = task_data.Position;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["CombShortFrozen"] = task_data.CombShortFrozen;
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LongFrozenAmount"] = task_data.LongFrozenAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["StrikeFrozenAmount"] = task_data.StrikeFrozenAmount;
	data["CloseProfit"] = task_data.CloseProfit;
	data["UseMargin"] = task_data.UseMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountField task_data = any_cast<CThostFtdcTradingAccountField>(task.task_data);
	dict data;
	data["SpecProductFrozenCommission"] = task_data.SpecProductFrozenCommission;
	data["FundMortgageOut"] = task_data.FundMortgageOut;
	data["Mortgage"] = task_data.Mortgage;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["SpecProductCloseProfit"] = task_data.SpecProductCloseProfit;
	data["Interest"] = task_data.Interest;
	data["SpecProductCommission"] = task_data.SpecProductCommission;
	data["CashIn"] = task_data.CashIn;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["FundMortgageAvailable"] = task_data.FundMortgageAvailable;
	data["PreCredit"] = task_data.PreCredit;
	data["PreMortgage"] = task_data.PreMortgage;
	data["InterestBase"] = task_data.InterestBase;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["MortgageableFund"] = task_data.MortgageableFund;
	data["PreFundMortgageIn"] = task_data.PreFundMortgageIn;
	data["PreMargin"] = task_data.PreMargin;
	data["SettlementID"] = task_data.SettlementID;
	data["BizType"] = task_data.BizType;
	data["FundMortgageIn"] = task_data.FundMortgageIn;
	data["DeliveryMargin"] = task_data.DeliveryMargin;
	data["SpecProductFrozenMargin"] = task_data.SpecProductFrozenMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["Balance"] = task_data.Balance;
	data["SpecProductMargin"] = task_data.SpecProductMargin;
	data["SpecProductPositionProfitByAlg"] = task_data.SpecProductPositionProfitByAlg;
	data["Reserve"] = task_data.Reserve;
	data["PreDeposit"] = task_data.PreDeposit;
	data["Credit"] = task_data.Credit;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ReserveBalance"] = task_data.ReserveBalance;
	data["SpecProductPositionProfit"] = task_data.SpecProductPositionProfit;
	data["SpecProductExchangeMargin"] = task_data.SpecProductExchangeMargin;
	data["PreBalance"] = task_data.PreBalance;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["CloseProfit"] = task_data.CloseProfit;
	data["PreFundMortgageOut"] = task_data.PreFundMortgageOut;
	data["Deposit"] = task_data.Deposit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CThostFtdcInvestorField task_data = any_cast<CThostFtdcInvestorField>(task.task_data);
	dict data;
	data["CommModelID"] = task_data.CommModelID;
	data["InvestorName"] = task_data.InvestorName;
	data["Mobile"] = task_data.Mobile;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["Telephone"] = task_data.Telephone;
	data["MarginModelID"] = task_data.MarginModelID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Address"] = task_data.Address;
	data["InvestorGroupID"] = task_data.InvestorGroupID;
	data["OpenDate"] = task_data.OpenDate;
	data["IsActive"] = task_data.IsActive;
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CThostFtdcTradingCodeField task_data = any_cast<CThostFtdcTradingCodeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BranchID"] = task_data.BranchID;
	data["BizType"] = task_data.BizType;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ClientIDType"] = task_data.ClientIDType;
	data["IsActive"] = task_data.IsActive;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentMarginRateField task_data = any_cast<CThostFtdcInstrumentMarginRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
	data["IsRelative"] = task_data.IsRelative;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentCommissionRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentCommissionRateField task_data = any_cast<CThostFtdcInstrumentCommissionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["BizType"] = task_data.BizType;
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["ExchangeID"] = task_data.ExchangeID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentCommissionRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CThostFtdcExchangeField task_data = any_cast<CThostFtdcExchangeField>(task.task_data);
	dict data;
	data["ExchangeProperty"] = task_data.ExchangeProperty;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProduct(Task task)
{
	PyLock lock;
	CThostFtdcProductField task_data = any_cast<CThostFtdcProductField>(task.task_data);
	dict data;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MortgageFundUseRange"] = task_data.MortgageFundUseRange;
	data["PositionDateType"] = task_data.PositionDateType;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["CloseDealType"] = task_data.CloseDealType;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["PriceTick"] = task_data.PriceTick;
	data["ProductName"] = task_data.ProductName;
	data["ExchangeProductID"] = task_data.ExchangeProductID;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["PositionType"] = task_data.PositionType;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["ProductClass"] = task_data.ProductClass;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["TradeCurrencyID"] = task_data.TradeCurrencyID;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryProduct(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentField task_data = any_cast<CThostFtdcInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["PositionDateType"] = task_data.PositionDateType;
	data["LongMarginRatio"] = task_data.LongMarginRatio;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["MinSellVolume"] = task_data.MinSellVolume;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortMarginRatio"] = task_data.ShortMarginRatio;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["MaxMarginSideAlgorithm"] = task_data.MaxMarginSideAlgorithm;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["CombinationType"] = task_data.CombinationType;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["OptionsType"] = task_data.OptionsType;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["InstrumentCode"] = task_data.InstrumentCode;
	data["MinBuyVolume"] = task_data.MinBuyVolume;
	data["PriceTick"] = task_data.PriceTick;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["UnderlyingInstrID"] = task_data.UnderlyingInstrID;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["HighestPrice"] = task_data.HighestPrice;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidPrice4"] = task_data.BidPrice4;
	data["BidPrice1"] = task_data.BidPrice1;
	data["BidPrice3"] = task_data.BidPrice3;
	data["BidPrice2"] = task_data.BidPrice2;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["OpenPrice"] = task_data.OpenPrice;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["AveragePrice"] = task_data.AveragePrice;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["AskPrice2"] = task_data.AskPrice2;
	data["Volume"] = task_data.Volume;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["AskVolume5"] = task_data.AskVolume5;
	data["AskVolume4"] = task_data.AskVolume4;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["BidVolume1"] = task_data.BidVolume1;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
	data["TradingDay"] = task_data.TradingDay;
	data["PreDelta"] = task_data.PreDelta;
	data["OpenInterest"] = task_data.OpenInterest;
	data["CurrDelta"] = task_data.CurrDelta;
	data["Turnover"] = task_data.Turnover;
	data["LastPrice"] = task_data.LastPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["LowestPrice"] = task_data.LowestPrice;
	data["ActionDay"] = task_data.ActionDay;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfo(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoField task_data = any_cast<CThostFtdcSettlementInfoField>(task.task_data);
	dict data;
	data["SettlementID"] = task_data.SettlementID;
	data["InvestorID"] = task_data.InvestorID;
	data["SequenceNo"] = task_data.SequenceNo;
	data["Content"] = task_data.Content;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySettlementInfo(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferBank(Task task)
{
	PyLock lock;
	CThostFtdcTransferBankField task_data = any_cast<CThostFtdcTransferBankField>(task.task_data);
	dict data;
	data["BankName"] = task_data.BankName;
	data["IsActive"] = task_data.IsActive;
	data["BankBrchID"] = task_data.BankBrchID;
	data["BankID"] = task_data.BankID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTransferBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionDetailField task_data = any_cast<CThostFtdcInvestorPositionDetailField>(task.task_data);
	dict data;
	data["PositionProfitByDate"] = task_data.PositionProfitByDate;
	data["ExchMargin"] = task_data.ExchMargin;
	data["TradeType"] = task_data.TradeType;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["Direction"] = task_data.Direction;
	data["CloseAmount"] = task_data.CloseAmount;
	data["OpenPrice"] = task_data.OpenPrice;
	data["Volume"] = task_data.Volume;
	data["LastSettlementPrice"] = task_data.LastSettlementPrice;
	data["CloseVolume"] = task_data.CloseVolume;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["SettlementID"] = task_data.SettlementID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["Margin"] = task_data.Margin;
	data["TradeID"] = task_data.TradeID;
	data["PositionProfitByTrade"] = task_data.PositionProfitByTrade;
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["InvestorID"] = task_data.InvestorID;
	data["CombInstrumentID"] = task_data.CombInstrumentID;
	data["OpenDate"] = task_data.OpenDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPositionDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryNotice(Task task)
{
	PyLock lock;
	CThostFtdcNoticeField task_data = any_cast<CThostFtdcNoticeField>(task.task_data);
	dict data;
	data["Content"] = task_data.Content;
	data["SequenceLabel"] = task_data.SequenceLabel;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmTime"] = task_data.ConfirmTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ConfirmDate"] = task_data.ConfirmDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionCombineDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionCombineDetailField task_data = any_cast<CThostFtdcInvestorPositionCombineDetailField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradeGroupID"] = task_data.TradeGroupID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["ComTradeID"] = task_data.ComTradeID;
	data["SettlementID"] = task_data.SettlementID;
	data["InvestorID"] = task_data.InvestorID;
	data["TotalAmt"] = task_data.TotalAmt;
	data["Margin"] = task_data.Margin;
	data["ExchMargin"] = task_data.ExchMargin;
	data["LegMultiple"] = task_data.LegMultiple;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TradeID"] = task_data.TradeID;
	data["LegID"] = task_data.LegID;
	data["TradingDay"] = task_data.TradingDay;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["Direction"] = task_data.Direction;
	data["BrokerID"] = task_data.BrokerID;
	data["CombInstrumentID"] = task_data.CombInstrumentID;
	data["OpenDate"] = task_data.OpenDate;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPositionCombineDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCFMMCTradingAccountKey(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountKeyField task_data = any_cast<CThostFtdcCFMMCTradingAccountKeyField>(task.task_data);
	dict data;
	data["KeyID"] = task_data.KeyID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CurrentKey"] = task_data.CurrentKey;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCFMMCTradingAccountKey(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryEWarrantOffset(Task task)
{
	PyLock lock;
	CThostFtdcEWarrantOffsetField task_data = any_cast<CThostFtdcEWarrantOffsetField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["InvestorID"] = task_data.InvestorID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction"] = task_data.Direction;
	data["Volume"] = task_data.Volume;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryEWarrantOffset(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorProductGroupMargin(Task task)
{
	PyLock lock;
	CThostFtdcInvestorProductGroupMarginField task_data = any_cast<CThostFtdcInvestorProductGroupMarginField>(task.task_data);
	dict data;
	data["ExchMargin"] = task_data.ExchMargin;
	data["ShortExchOffsetAmount"] = task_data.ShortExchOffsetAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["LongOffsetAmount"] = task_data.LongOffsetAmount;
	data["CashIn"] = task_data.CashIn;
	data["ShortUseMargin"] = task_data.ShortUseMargin;
	data["ShortOffsetAmount"] = task_data.ShortOffsetAmount;
	data["SettlementID"] = task_data.SettlementID;
	data["LongExchOffsetAmount"] = task_data.LongExchOffsetAmount;
	data["LongUseMargin"] = task_data.LongUseMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["LongFrozenMargin"] = task_data.LongFrozenMargin;
	data["ShortExchMargin"] = task_data.ShortExchMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["ProductGroupID"] = task_data.ProductGroupID;
	data["ExchOffsetAmount"] = task_data.ExchOffsetAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["LongExchMargin"] = task_data.LongExchMargin;
	data["CloseProfit"] = task_data.CloseProfit;
	data["OffsetAmount"] = task_data.OffsetAmount;
	data["UseMargin"] = task_data.UseMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorProductGroupMargin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateField task_data = any_cast<CThostFtdcExchangeMarginRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["BrokerID"] = task_data.BrokerID;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRateAdjust(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateAdjustField task_data = any_cast<CThostFtdcExchangeMarginRateAdjustField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["ExchLongMarginRatioByMoney"] = task_data.ExchLongMarginRatioByMoney;
	data["ExchShortMarginRatioByMoney"] = task_data.ExchShortMarginRatioByMoney;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
	data["ExchShortMarginRatioByVolume"] = task_data.ExchShortMarginRatioByVolume;
	data["ExchLongMarginRatioByVolume"] = task_data.ExchLongMarginRatioByVolume;
	data["NoShortMarginRatioByMoney"] = task_data.NoShortMarginRatioByMoney;
	data["NoLongMarginRatioByMoney"] = task_data.NoLongMarginRatioByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["NoLongMarginRatioByVolume"] = task_data.NoLongMarginRatioByVolume;
	data["NoShortMarginRatioByVolume"] = task_data.NoShortMarginRatioByVolume;
	data["BrokerID"] = task_data.BrokerID;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeMarginRateAdjust(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeRateField task_data = any_cast<CThostFtdcExchangeRateField>(task.task_data);
	dict data;
	data["FromCurrencyID"] = task_data.FromCurrencyID;
	data["FromCurrencyUnit"] = task_data.FromCurrencyUnit;
	data["BrokerID"] = task_data.BrokerID;
	data["ExchangeRate"] = task_data.ExchangeRate;
	data["ToCurrencyID"] = task_data.ToCurrencyID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchangeRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySecAgentACIDMap(Task task)
{
	PyLock lock;
	CThostFtdcSecAgentACIDMapField task_data = any_cast<CThostFtdcSecAgentACIDMapField>(task.task_data);
	dict data;
	data["CurrencyID"] = task_data.CurrencyID;
	data["UserID"] = task_data.UserID;
	data["BrokerSecAgentID"] = task_data.BrokerSecAgentID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySecAgentACIDMap(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductExchRate(Task task)
{
	PyLock lock;
	CThostFtdcProductExchRateField task_data = any_cast<CThostFtdcProductExchRateField>(task.task_data);
	dict data;
	data["QuoteCurrencyID"] = task_data.QuoteCurrencyID;
	data["ExchangeRate"] = task_data.ExchangeRate;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryProductExchRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductGroup(Task task)
{
	PyLock lock;
	CThostFtdcProductGroupField task_data = any_cast<CThostFtdcProductGroupField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ProductGroupID"] = task_data.ProductGroupID;
	data["ProductID"] = task_data.ProductID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryProductGroup(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrTradeCost(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrTradeCostField task_data = any_cast<CThostFtdcOptionInstrTradeCostField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchMiniMargin"] = task_data.ExchMiniMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["Royalty"] = task_data.Royalty;
	data["BrokerID"] = task_data.BrokerID;
	data["MiniMargin"] = task_data.MiniMargin;
	data["ExchFixedMargin"] = task_data.ExchFixedMargin;
	data["FixedMargin"] = task_data.FixedMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOptionInstrTradeCost(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrCommRate(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrCommRateField task_data = any_cast<CThostFtdcOptionInstrCommRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["StrikeRatioByMoney"] = task_data.StrikeRatioByMoney;
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["ExchangeID"] = task_data.ExchangeID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;
	data["StrikeRatioByVolume"] = task_data.StrikeRatioByVolume;
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOptionInstrCommRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["CloseFlag"] = task_data.CloseFlag;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ExecResult"] = task_data.ExecResult;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["Volume"] = task_data.Volume;
	data["InstallID"] = task_data.InstallID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["ClientID"] = task_data.ClientID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["SessionID"] = task_data.SessionID;
	data["ActionType"] = task_data.ActionType;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ExecOrderLocalID"] = task_data.ExecOrderLocalID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExecOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryForQuote(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteField task_data = any_cast<CThostFtdcForQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ForQuoteRef"] = task_data.ForQuoteRef;
	data["ExchangeID"] = task_data.ExchangeID;
	data["InstallID"] = task_data.InstallID;
	data["ForQuoteLocalID"] = task_data.ForQuoteLocalID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["InsertDate"] = task_data.InsertDate;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["SessionID"] = task_data.SessionID;
	data["ClientID"] = task_data.ClientID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ForQuoteStatus"] = task_data.ForQuoteStatus;
	data["FrontID"] = task_data.FrontID;
	data["BrokerForQutoSeq"] = task_data.BrokerForQutoSeq;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryForQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BidOrderSysID"] = task_data.BidOrderSysID;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["AskVolume"] = task_data.AskVolume;
	data["BidOrderRef"] = task_data.BidOrderRef;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["AskOrderSysID"] = task_data.AskOrderSysID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["ClientID"] = task_data.ClientID;
	data["SessionID"] = task_data.SessionID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BidPrice"] = task_data.BidPrice;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["InstrumentID"] = task_data.InstrumentID;
	data["QuoteStatus"] = task_data.QuoteStatus;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["QuoteLocalID"] = task_data.QuoteLocalID;
	data["BidVolume"] = task_data.BidVolume;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["CancelTime"] = task_data.CancelTime;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["AskPrice"] = task_data.AskPrice;
	data["SequenceNo"] = task_data.SequenceNo;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryLock(Task task)
{
	PyLock lock;
	CThostFtdcLockField task_data = any_cast<CThostFtdcLockField>(task.task_data);
	dict data;
	data["LockStatus"] = task_data.LockStatus;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LockLocalID"] = task_data.LockLocalID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["SessionID"] = task_data.SessionID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CancelTime"] = task_data.CancelTime;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["BrokerLockSeq"] = task_data.BrokerLockSeq;
	data["SequenceNo"] = task_data.SequenceNo;
	data["LockRef"] = task_data.LockRef;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["LockSysID"] = task_data.LockSysID;
	data["LockType"] = task_data.LockType;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryLock(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryLockPosition(Task task)
{
	PyLock lock;
	CThostFtdcLockPositionField task_data = any_cast<CThostFtdcLockPositionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenVolume"] = task_data.FrozenVolume;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryLockPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorLevel(Task task)
{
	PyLock lock;
	CThostFtdcInvestorLevelField task_data = any_cast<CThostFtdcInvestorLevelField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["LevelType"] = task_data.LevelType;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorLevel(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecFreeze(Task task)
{
	PyLock lock;
	CThostFtdcExecFreezeField task_data = any_cast<CThostFtdcExecFreezeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OptionsType"] = task_data.OptionsType;
	data["PosiDirection"] = task_data.PosiDirection;
	data["FrozenAmount"] = task_data.FrozenAmount;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExecFreeze(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombInstrumentGuard(Task task)
{
	PyLock lock;
	CThostFtdcCombInstrumentGuardField task_data = any_cast<CThostFtdcCombInstrumentGuardField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["GuarantRatio"] = task_data.GuarantRatio;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCombInstrumentGuard(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ActionStatus"] = task_data.ActionStatus;
	data["CombDirection"] = task_data.CombDirection;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["SessionID"] = task_data.SessionID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["CombActionRef"] = task_data.CombActionRef;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCombAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	CThostFtdcTransferSerialField task_data = any_cast<CThostFtdcTransferSerialField>(task.task_data);
	dict data;
	data["BankNewAccount"] = task_data.BankNewAccount;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["TradeTime"] = task_data.TradeTime;
	data["OperatorCode"] = task_data.OperatorCode;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureAccType"] = task_data.FutureAccType;
	data["ErrorID"] = task_data.ErrorID;
	data["BankSerial"] = task_data.BankSerial;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["IdCardType"] = task_data.IdCardType;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["FutureSerial"] = task_data.FutureSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AvailabilityFlag"] = task_data.AvailabilityFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTransferSerial(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryAccountregister(Task task)
{
	PyLock lock;
	CThostFtdcAccountregisterField task_data = any_cast<CThostFtdcAccountregisterField>(task.task_data);
	dict data;
	data["BankAccount"] = task_data.BankAccount;
	data["CustType"] = task_data.CustType;
	data["CustomerName"] = task_data.CustomerName;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["OutDate"] = task_data.OutDate;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["BankBranchID"] = task_data.BankBranchID;
	data["RegDate"] = task_data.RegDate;
	data["BrokerID"] = task_data.BrokerID;
	data["BankID"] = task_data.BankID;
	data["TID"] = task_data.TID;
	data["OpenOrDestroy"] = task_data.OpenOrDestroy;
	data["IdCardType"] = task_data.IdCardType;
	data["TradeDay"] = task_data.TradeDay;
	data["BankAccType"] = task_data.BankAccType;
	data["AccountID"] = task_data.AccountID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryAccountregister(data, error, task.task_id, task.task_last);
};

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ParticipantID"] = task_data.ParticipantID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["ClientID"] = task_data.ClientID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TradeTime"] = task_data.TradeTime;
	data["Direction"] = task_data.Direction;
	data["ParticipantID"] = task_data.ParticipantID;
	data["Price"] = task_data.Price;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["TradeID"] = task_data.TradeID;
	data["TradeDate"] = task_data.TradeDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["TradeSource"] = task_data.TradeSource;
	data["PriceSource"] = task_data.PriceSource;
	data["TradingRole"] = task_data.TradingRole;

	this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcOrderActionField task_data = any_cast<CThostFtdcOrderActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["InvestorID"] = task_data.InvestorID;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["VolumeChange"] = task_data.VolumeChange;
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["OrderSysID"] = task_data.OrderSysID;
	data["BrokerID"] = task_data.BrokerID;
	data["ClientID"] = task_data.ClientID;
	data["ActionDate"] = task_data.ActionDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentStatusField task_data = any_cast<CThostFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["EnterTime"] = task_data.EnterTime;
	data["SettlementGroupID"] = task_data.SettlementGroupID;
	data["TradingSegmentSN"] = task_data.TradingSegmentSN;
	data["EnterReason"] = task_data.EnterReason;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["ExchangeInstID"] = task_data.ExchangeInstID;

	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeInfoField task_data = any_cast<CThostFtdcTradingNoticeInfoField>(task.task_data);
	dict data;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["SequenceNo"] = task_data.SequenceNo;
	data["FieldContent"] = task_data.FieldContent;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["SendTime"] = task_data.SendTime;

	this->onRtnTradingNotice(data);
};

void TdApi::processRtnErrorConditionalOrder(Task task)
{
	PyLock lock;
	CThostFtdcErrorConditionalOrderField task_data = any_cast<CThostFtdcErrorConditionalOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["ParticipantID"] = task_data.ParticipantID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["ClientID"] = task_data.ClientID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["ErrorID"] = task_data.ErrorID;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["OrderSource"] = task_data.OrderSource;
	data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	this->onRtnErrorConditionalOrder(data);
};

void TdApi::processRtnExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["CloseFlag"] = task_data.CloseFlag;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ExecResult"] = task_data.ExecResult;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;
	data["Volume"] = task_data.Volume;
	data["InstallID"] = task_data.InstallID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["ClientID"] = task_data.ClientID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["SessionID"] = task_data.SessionID;
	data["ActionType"] = task_data.ActionType;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ExecOrderLocalID"] = task_data.ExecOrderLocalID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
	data["FrontID"] = task_data.FrontID;

	this->onRtnExecOrder(data);
};

void TdApi::processErrRtnExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CloseFlag"] = task_data.CloseFlag;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["PosiDirection"] = task_data.PosiDirection;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionType"] = task_data.ActionType;
	data["ReservePositionFlag"] = task_data.ReservePositionFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnExecOrderInsert(data, error);
};

void TdApi::processErrRtnExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderActionField task_data = any_cast<CThostFtdcExecOrderActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["ExecOrderRef"] = task_data.ExecOrderRef;
	data["SessionID"] = task_data.SessionID;
	data["ActionType"] = task_data.ActionType;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExecOrderSysID"] = task_data.ExecOrderSysID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["BrokerID"] = task_data.BrokerID;
	data["ExecOrderLocalID"] = task_data.ExecOrderLocalID;
	data["ActionDate"] = task_data.ActionDate;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnExecOrderAction(data, error);
};

void TdApi::processErrRtnForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ForQuoteRef"] = task_data.ForQuoteRef;
	data["ExchangeID"] = task_data.ExchangeID;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnForQuoteInsert(data, error);
};

void TdApi::processRtnQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BidOrderSysID"] = task_data.BidOrderSysID;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["AskVolume"] = task_data.AskVolume;
	data["BidOrderRef"] = task_data.BidOrderRef;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["AskOrderSysID"] = task_data.AskOrderSysID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["ClientID"] = task_data.ClientID;
	data["SessionID"] = task_data.SessionID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BidPrice"] = task_data.BidPrice;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["InstrumentID"] = task_data.InstrumentID;
	data["QuoteStatus"] = task_data.QuoteStatus;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["QuoteLocalID"] = task_data.QuoteLocalID;
	data["BidVolume"] = task_data.BidVolume;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["CancelTime"] = task_data.CancelTime;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["AskPrice"] = task_data.AskPrice;
	data["SequenceNo"] = task_data.SequenceNo;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
	data["FrontID"] = task_data.FrontID;

	this->onRtnQuote(data);
};

void TdApi::processErrRtnQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["AskPrice"] = task_data.AskPrice;
	data["UserID"] = task_data.UserID;
	data["AskOffsetFlag"] = task_data.AskOffsetFlag;
	data["BidVolume"] = task_data.BidVolume;
	data["AskOrderRef"] = task_data.AskOrderRef;
	data["AskVolume"] = task_data.AskVolume;
	data["InvestorID"] = task_data.InvestorID;
	data["BidOffsetFlag"] = task_data.BidOffsetFlag;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["BidPrice"] = task_data.BidPrice;
	data["BidHedgeFlag"] = task_data.BidHedgeFlag;
	data["QuoteRef"] = task_data.QuoteRef;
	data["BidOrderRef"] = task_data.BidOrderRef;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQuoteInsert(data, error);
};

void TdApi::processErrRtnQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcQuoteActionField task_data = any_cast<CThostFtdcQuoteActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["QuoteRef"] = task_data.QuoteRef;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["QuoteActionRef"] = task_data.QuoteActionRef;
	data["StatusMsg"] = task_data.StatusMsg;
	data["QuoteLocalID"] = task_data.QuoteLocalID;
	data["BrokerID"] = task_data.BrokerID;
	data["QuoteSysID"] = task_data.QuoteSysID;
	data["ActionDate"] = task_data.ActionDate;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQuoteAction(data, error);
};

void TdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteRspField task_data = any_cast<CThostFtdcForQuoteRspField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ActionDay"] = task_data.ActionDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["TradingDay"] = task_data.TradingDay;
	data["ForQuoteSysID"] = task_data.ForQuoteSysID;
	data["ForQuoteTime"] = task_data.ForQuoteTime;

	this->onRtnForQuoteRsp(data);
};

void TdApi::processRtnCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["Token"] = task_data.Token;
	data["KeyID"] = task_data.KeyID;
	data["BrokerID"] = task_data.BrokerID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["AccountID"] = task_data.AccountID;

	this->onRtnCFMMCTradingAccountToken(data);
};

void TdApi::processRtnLock(Task task)
{
	PyLock lock;
	CThostFtdcLockField task_data = any_cast<CThostFtdcLockField>(task.task_data);
	dict data;
	data["LockStatus"] = task_data.LockStatus;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LockLocalID"] = task_data.LockLocalID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["SessionID"] = task_data.SessionID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CancelTime"] = task_data.CancelTime;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["BrokerLockSeq"] = task_data.BrokerLockSeq;
	data["SequenceNo"] = task_data.SequenceNo;
	data["LockRef"] = task_data.LockRef;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["LockSysID"] = task_data.LockSysID;
	data["LockType"] = task_data.LockType;

	this->onRtnLock(data);
};

void TdApi::processErrRtnLockInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputLockField task_data = any_cast<CThostFtdcInputLockField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["UserID"] = task_data.UserID;
	data["LockRef"] = task_data.LockRef;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["LockType"] = task_data.LockType;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnLockInsert(data, error);
};

void TdApi::processRtnCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ActionStatus"] = task_data.ActionStatus;
	data["CombDirection"] = task_data.CombDirection;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = task_data.InvestorID;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["SessionID"] = task_data.SessionID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["CombActionRef"] = task_data.CombActionRef;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["FrontID"] = task_data.FrontID;

	this->onRtnCombAction(data);
};

void TdApi::processErrRtnCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Direction"] = task_data.Direction;
	data["CombActionRef"] = task_data.CombActionRef;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = task_data.UserID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombDirection"] = task_data.CombDirection;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnCombActionInsert(data, error);
};

void TdApi::processRspQryContractBank(Task task)
{
	PyLock lock;
	CThostFtdcContractBankField task_data = any_cast<CThostFtdcContractBankField>(task.task_data);
	dict data;
	data["BankName"] = task_data.BankName;
	data["BrokerID"] = task_data.BrokerID;
	data["BankBrchID"] = task_data.BankBrchID;
	data["BankID"] = task_data.BankID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryContractBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Status"] = task_data.Status;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["UserType"] = task_data.UserType;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["ErrorID"] = task_data.ErrorID;
	data["ParkedOrderID"] = task_data.ParkedOrderID;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Status"] = task_data.Status;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserType"] = task_data.UserType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ParkedOrderActionID"] = task_data.ParkedOrderActionID;
	data["FrontID"] = task_data.FrontID;
	data["ErrorID"] = task_data.ErrorID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeField task_data = any_cast<CThostFtdcTradingNoticeField>(task.task_data);
	dict data;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["SequenceNo"] = task_data.SequenceNo;
	data["UserID"] = task_data.UserID;
	data["FieldContent"] = task_data.FieldContent;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["SendTime"] = task_data.SendTime;
	data["InvestorRange"] = task_data.InvestorRange;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingParams(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingParamsField task_data = any_cast<CThostFtdcBrokerTradingParamsField>(task.task_data);
	dict data;
	data["MarginPriceType"] = task_data.MarginPriceType;
	data["Algorithm"] = task_data.Algorithm;
	data["CurrencyID"] = task_data.CurrencyID;
	data["OptionRoyaltyPriceType"] = task_data.OptionRoyaltyPriceType;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AvailIncludeCloseProfit"] = task_data.AvailIncludeCloseProfit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBrokerTradingParams(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingAlgos(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingAlgosField task_data = any_cast<CThostFtdcBrokerTradingAlgosField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["HandlePositionAlgoID"] = task_data.HandlePositionAlgoID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FindMarginRateAlgoID"] = task_data.FindMarginRateAlgoID;
	data["BrokerID"] = task_data.BrokerID;
	data["HandleTradingAccountAlgoID"] = task_data.HandleTradingAccountAlgoID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBrokerTradingAlgos(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcQueryCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcQueryCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryCFMMCTradingAccountToken(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromBankToFutureByBank(data);
};

void TdApi::processRtnFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromFutureToBankByBank(data);
};

void TdApi::processRtnRepealFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromBankToFutureByBank(data);
};

void TdApi::processRtnRepealFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromFutureToBankByBank(data);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
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
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnFromFutureToBankByFuture(data);
};

void TdApi::processRtnRepealFromBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromBankToFutureByFutureManual(data);
};

void TdApi::processRtnRepealFromFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromFutureToBankByFutureManual(data);
};

void TdApi::processRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcNotifyQueryAccountField task_data = any_cast<CThostFtdcNotifyQueryAccountField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;
	data["BankFetchAmount"] = task_data.BankFetchAmount;

	this->onRtnQueryBankBalanceByFuture(data);
};

void TdApi::processErrRtnBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnBankToFutureByFuture(data, error);
};

void TdApi::processErrRtnFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFutureToBankByFuture(data, error);
};

void TdApi::processErrRtnRepealBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnRepealBankToFutureByFutureManual(data, error);
};

void TdApi::processErrRtnRepealFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnRepealFutureToBankByFutureManual(data, error);
};

void TdApi::processErrRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["CurrencyID"] = task_data.CurrencyID;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnQueryBankBalanceByFuture(data, error);
};

void TdApi::processRtnRepealFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromBankToFutureByFuture(data);
};

void TdApi::processRtnRepealFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["BankRepealFlag"] = task_data.BankRepealFlag;
	data["RepealedTimes"] = task_data.RepealedTimes;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["FutureRepealSerial"] = task_data.FutureRepealSerial;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["FeePayFlag"] = task_data.FeePayFlag;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["DeviceID"] = task_data.DeviceID;
	data["TransferStatus"] = task_data.TransferStatus;
	data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankRepealSerial"] = task_data.BankRepealSerial;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["RepealTimeInterval"] = task_data.RepealTimeInterval;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["PlateRepealSerial"] = task_data.PlateRepealSerial;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	this->onRtnRepealFromFutureToBankByFuture(data);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromBankToFutureByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["PlateSerial"] = task_data.PlateSerial;
	data["FutureFetchAmount"] = task_data.FutureFetchAmount;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["BrokerFee"] = task_data.BrokerFee;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Message"] = task_data.Message;
	data["CustFee"] = task_data.CustFee;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromFutureToBankByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryBankAccountMoneyByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["TradeTime"] = task_data.TradeTime;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["InstallID"] = task_data.InstallID;
	data["CustomerName"] = task_data.CustomerName;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["BankID"] = task_data.BankID;
	data["Password"] = task_data.Password;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["RequestID"] = task_data.RequestID;
	data["CustType"] = task_data.CustType;
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
	data["CurrencyID"] = task_data.CurrencyID;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["FutureSerial"] = task_data.FutureSerial;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["Digest"] = task_data.Digest;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryBankAccountMoneyByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOpenAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcOpenAccountField task_data = any_cast<CThostFtdcOpenAccountField>(task.task_data);
	dict data;
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["Telephone"] = task_data.Telephone;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["Fax"] = task_data.Fax;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["CountryCode"] = task_data.CountryCode;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["Address"] = task_data.Address;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["CustType"] = task_data.CustType;
	data["Gender"] = task_data.Gender;
	data["BankID"] = task_data.BankID;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["CashExchangeCode"] = task_data.CashExchangeCode;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["MobilePhone"] = task_data.MobilePhone;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["ZipCode"] = task_data.ZipCode;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["TradeTime"] = task_data.TradeTime;
	data["EMail"] = task_data.EMail;
	data["Digest"] = task_data.Digest;
	data["DeviceID"] = task_data.DeviceID;

	this->onRtnOpenAccountByBank(data);
};

void TdApi::processRtnCancelAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcCancelAccountField task_data = any_cast<CThostFtdcCancelAccountField>(task.task_data);
	dict data;
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["UserID"] = task_data.UserID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["Telephone"] = task_data.Telephone;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["Fax"] = task_data.Fax;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["CountryCode"] = task_data.CountryCode;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["Address"] = task_data.Address;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["CustType"] = task_data.CustType;
	data["Gender"] = task_data.Gender;
	data["BankID"] = task_data.BankID;
	data["BankSerial"] = task_data.BankSerial;
	data["OperNo"] = task_data.OperNo;
	data["TradingDay"] = task_data.TradingDay;
	data["BankSecuAcc"] = task_data.BankSecuAcc;
	data["BrokerID"] = task_data.BrokerID;
	data["CashExchangeCode"] = task_data.CashExchangeCode;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["MobilePhone"] = task_data.MobilePhone;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["ZipCode"] = task_data.ZipCode;
	data["BankSecuAccType"] = task_data.BankSecuAccType;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["TradeTime"] = task_data.TradeTime;
	data["EMail"] = task_data.EMail;
	data["Digest"] = task_data.Digest;
	data["DeviceID"] = task_data.DeviceID;

	this->onRtnCancelAccountByBank(data);
};

void TdApi::processRtnChangeAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcChangeAccountField task_data = any_cast<CThostFtdcChangeAccountField>(task.task_data);
	dict data;
	data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
	data["NewBankPassWord"] = task_data.NewBankPassWord;
	data["BrokerBranchID"] = task_data.BrokerBranchID;
	data["BankPassWord"] = task_data.BankPassWord;
	data["Telephone"] = task_data.Telephone;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
	data["TID"] = task_data.TID;
	data["AccountID"] = task_data.AccountID;
	data["BankAccount"] = task_data.BankAccount;
	data["Fax"] = task_data.Fax;
	data["InstallID"] = task_data.InstallID;
	data["SecuPwdFlag"] = task_data.SecuPwdFlag;
	data["CustomerName"] = task_data.CustomerName;
	data["CountryCode"] = task_data.CountryCode;
	data["TradeCode"] = task_data.TradeCode;
	data["BankBranchID"] = task_data.BankBranchID;
	data["SessionID"] = task_data.SessionID;
	data["NewBankAccount"] = task_data.NewBankAccount;
	data["Address"] = task_data.Address;
	data["PlateSerial"] = task_data.PlateSerial;
	data["BankPwdFlag"] = task_data.BankPwdFlag;
	data["ErrorID"] = task_data.ErrorID;
	data["CustType"] = task_data.CustType;
	data["Gender"] = task_data.Gender;
	data["BankID"] = task_data.BankID;
	data["BankSerial"] = task_data.BankSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["IdCardType"] = task_data.IdCardType;
	data["Password"] = task_data.Password;
	data["MobilePhone"] = task_data.MobilePhone;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["BankAccType"] = task_data.BankAccType;
	data["LastFragment"] = task_data.LastFragment;
	data["ZipCode"] = task_data.ZipCode;
	data["BrokerIDByBank"] = task_data.BrokerIDByBank;
	data["TradeTime"] = task_data.TradeTime;
	data["EMail"] = task_data.EMail;
	data["Digest"] = task_data.Digest;

	this->onRtnChangeAccountByBank(data);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	this->api = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
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

void TdApi::subscribePrivateTopic(int nType)
{
	//该函数为手动编写
	THOST_TE_RESUME_TYPE type;

	switch (nType)
	{
	case 0:
	{
		type = THOST_TERT_RESTART;
		break;
	};

	case 1:
	{
		type = THOST_TERT_RESUME;
		break;
	};

	case 2:
	{
		type = THOST_TERT_QUICK;
		break;
	};
	}

	this->api->SubscribePrivateTopic(type);
};

void TdApi::subscribePublicTopic(int nType)
{
	//该函数为手动编写
	THOST_TE_RESUME_TYPE type;

	switch (nType)
	{
	case 0:
	{
		type = THOST_TERT_RESTART;
		break;
	};

	case 1:
	{
		type = THOST_TERT_RESUME;
		break;
	};

	case 2:
	{
		type = THOST_TERT_QUICK;
		break;
	};
	}

	this->api->SubscribePublicTopic(type);
};

int TdApi::reqAuthenticate(dict req, int nRequestID)
{
	CThostFtdcReqAuthenticateField myreq = CThostFtdcReqAuthenticateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "AuthCode", myreq.AuthCode);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	int i = this->api->ReqAuthenticate(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CThostFtdcUserPasswordUpdateField myreq = CThostFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "NewPassword", myreq.NewPassword);
	getStr(req, "OldPassword", myreq.OldPassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqTradingAccountPasswordUpdate(dict req, int nRequestID)
{
	CThostFtdcTradingAccountPasswordUpdateField myreq = CThostFtdcTradingAccountPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "NewPassword", myreq.NewPassword);
	getStr(req, "OldPassword", myreq.OldPassword);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqTradingAccountPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getStr(req, "GTDDate", myreq.GTDDate);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqParkedOrderInsert(dict req, int nRequestID)
{
	CThostFtdcParkedOrderField myreq = CThostFtdcParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getChar(req, "Status", &myreq.Status);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getChar(req, "UserType", &myreq.UserType);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getInt(req, "ErrorID", &myreq.ErrorID);
	getStr(req, "ParkedOrderID", myreq.ParkedOrderID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getStr(req, "GTDDate", myreq.GTDDate);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "ErrorMsg", myreq.ErrorMsg);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqParkedOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcParkedOrderActionField myreq = CThostFtdcParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Status", &myreq.Status);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getChar(req, "UserType", &myreq.UserType);
	getStr(req, "ErrorMsg", myreq.ErrorMsg);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getStr(req, "ParkedOrderActionID", myreq.ParkedOrderActionID);
	getInt(req, "FrontID", &myreq.FrontID);
	getInt(req, "ErrorID", &myreq.ErrorID);
	int i = this->api->ReqParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryMaxOrderVolume(dict req, int nRequestID)
{
	CThostFtdcQueryMaxOrderVolumeField myreq = CThostFtdcQueryMaxOrderVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "MaxVolume", &myreq.MaxVolume);
	int i = this->api->ReqQueryMaxOrderVolume(&myreq, nRequestID);
	return i;
};

int TdApi::reqSettlementInfoConfirm(dict req, int nRequestID)
{
	CThostFtdcSettlementInfoConfirmField myreq = CThostFtdcSettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ConfirmTime", myreq.ConfirmTime);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ConfirmDate", myreq.ConfirmDate);
	int i = this->api->ReqSettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqRemoveParkedOrder(dict req, int nRequestID)
{
	CThostFtdcRemoveParkedOrderField myreq = CThostFtdcRemoveParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ParkedOrderID", myreq.ParkedOrderID);
	int i = this->api->ReqRemoveParkedOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqRemoveParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcRemoveParkedOrderActionField myreq = CThostFtdcRemoveParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ParkedOrderActionID", myreq.ParkedOrderActionID);
	int i = this->api->ReqRemoveParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputExecOrderField myreq = CThostFtdcInputExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "CloseFlag", &myreq.CloseFlag);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "PosiDirection", &myreq.PosiDirection);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionType", &myreq.ActionType);
	getChar(req, "ReservePositionFlag", &myreq.ReservePositionFlag);
	int i = this->api->ReqExecOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputExecOrderActionField myreq = CThostFtdcInputExecOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "ExecOrderActionRef", &myreq.ExecOrderActionRef);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqExecOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqForQuoteInsert(dict req, int nRequestID)
{
	CThostFtdcInputForQuoteField myreq = CThostFtdcInputForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ForQuoteRef", myreq.ForQuoteRef);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqForQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteInsert(dict req, int nRequestID)
{
	CThostFtdcInputQuoteField myreq = CThostFtdcInputQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "AskHedgeFlag", &myreq.AskHedgeFlag);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getDouble(req, "AskPrice", &myreq.AskPrice);
	getStr(req, "UserID", myreq.UserID);
	getChar(req, "AskOffsetFlag", &myreq.AskOffsetFlag);
	getInt(req, "BidVolume", &myreq.BidVolume);
	getStr(req, "AskOrderRef", myreq.AskOrderRef);
	getInt(req, "AskVolume", &myreq.AskVolume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BidOffsetFlag", &myreq.BidOffsetFlag);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "ForQuoteSysID", myreq.ForQuoteSysID);
	getDouble(req, "BidPrice", &myreq.BidPrice);
	getChar(req, "BidHedgeFlag", &myreq.BidHedgeFlag);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	getStr(req, "BidOrderRef", myreq.BidOrderRef);
	int i = this->api->ReqQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteAction(dict req, int nRequestID)
{
	CThostFtdcInputQuoteActionField myreq = CThostFtdcInputQuoteActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "QuoteActionRef", &myreq.QuoteActionRef);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "QuoteSysID", myreq.QuoteSysID);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	int i = this->api->ReqQuoteAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqLockInsert(dict req, int nRequestID)
{
	CThostFtdcInputLockField myreq = CThostFtdcInputLockField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "LockRef", myreq.LockRef);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "LockType", &myreq.LockType);
	int i = this->api->ReqLockInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqCombActionInsert(dict req, int nRequestID)
{
	CThostFtdcInputCombActionField myreq = CThostFtdcInputCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "Direction", &myreq.Direction);
	getStr(req, "CombActionRef", myreq.CombActionRef);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "CombDirection", &myreq.CombDirection);
	int i = this->api->ReqCombActionInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "TradeTimeStart", myreq.TradeTimeStart);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "TradeID", myreq.TradeID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "TradeTimeEnd", myreq.TradeTimeEnd);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BizType", &myreq.BizType);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CThostFtdcQryInvestorField myreq = CThostFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
{
	CThostFtdcQryTradingCodeField myreq = CThostFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientIDType", &myreq.ClientIDType);
	getStr(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentMarginRateField myreq = CThostFtdcQryInstrumentMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	int i = this->api->ReqQryInstrumentMarginRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentCommissionRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentCommissionRateField myreq = CThostFtdcQryInstrumentCommissionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInstrumentCommissionRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CThostFtdcQryExchangeField myreq = CThostFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryProduct(dict req, int nRequestID)
{
	CThostFtdcQryProductField myreq = CThostFtdcQryProductField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ProductClass", &myreq.ProductClass);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryProduct(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ExchangeInstID", myreq.ExchangeInstID);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req, int nRequestID)
{
	CThostFtdcQryDepthMarketDataField myreq = CThostFtdcQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryDepthMarketData(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySettlementInfo(dict req, int nRequestID)
{
	CThostFtdcQrySettlementInfoField myreq = CThostFtdcQrySettlementInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "TradingDay", myreq.TradingDay);
	int i = this->api->ReqQrySettlementInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferBank(dict req, int nRequestID)
{
	CThostFtdcQryTransferBankField myreq = CThostFtdcQryTransferBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getStr(req, "BankID", myreq.BankID);
	int i = this->api->ReqQryTransferBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionDetailField myreq = CThostFtdcQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPositionDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryNotice(dict req, int nRequestID)
{
	CThostFtdcQryNoticeField myreq = CThostFtdcQryNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryNotice(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySettlementInfoConfirm(dict req, int nRequestID)
{
	CThostFtdcQrySettlementInfoConfirmField myreq = CThostFtdcQrySettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQrySettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionCombineDetail(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionCombineDetailField myreq = CThostFtdcQryInvestorPositionCombineDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "CombInstrumentID", myreq.CombInstrumentID);
	int i = this->api->ReqQryInvestorPositionCombineDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCFMMCTradingAccountKey(dict req, int nRequestID)
{
	CThostFtdcQryCFMMCTradingAccountKeyField myreq = CThostFtdcQryCFMMCTradingAccountKeyField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCFMMCTradingAccountKey(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryEWarrantOffset(dict req, int nRequestID)
{
	CThostFtdcQryEWarrantOffsetField myreq = CThostFtdcQryEWarrantOffsetField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryEWarrantOffset(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorProductGroupMargin(dict req, int nRequestID)
{
	CThostFtdcQryInvestorProductGroupMarginField myreq = CThostFtdcQryInvestorProductGroupMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "ProductGroupID", myreq.ProductGroupID);
	int i = this->api->ReqQryInvestorProductGroupMargin(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryExchangeMarginRateField myreq = CThostFtdcQryExchangeMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryExchangeMarginRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeMarginRateAdjust(dict req, int nRequestID)
{
	CThostFtdcQryExchangeMarginRateAdjustField myreq = CThostFtdcQryExchangeMarginRateAdjustField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryExchangeMarginRateAdjust(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeRate(dict req, int nRequestID)
{
	CThostFtdcQryExchangeRateField myreq = CThostFtdcQryExchangeRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "FromCurrencyID", myreq.FromCurrencyID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ToCurrencyID", myreq.ToCurrencyID);
	int i = this->api->ReqQryExchangeRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentACIDMap(dict req, int nRequestID)
{
	CThostFtdcQrySecAgentACIDMapField myreq = CThostFtdcQrySecAgentACIDMapField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQrySecAgentACIDMap(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryProductExchRate(dict req, int nRequestID)
{
	CThostFtdcQryProductExchRateField myreq = CThostFtdcQryProductExchRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryProductExchRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryProductGroup(dict req, int nRequestID)
{
	CThostFtdcQryProductGroupField myreq = CThostFtdcQryProductGroupField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryProductGroup(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionInstrTradeCost(dict req, int nRequestID)
{
	CThostFtdcQryOptionInstrTradeCostField myreq = CThostFtdcQryOptionInstrTradeCostField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getDouble(req, "InputPrice", &myreq.InputPrice);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getDouble(req, "UnderlyingPrice", &myreq.UnderlyingPrice);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryOptionInstrTradeCost(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionInstrCommRate(dict req, int nRequestID)
{
	CThostFtdcQryOptionInstrCommRateField myreq = CThostFtdcQryOptionInstrCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryOptionInstrCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExecOrder(dict req, int nRequestID)
{
	CThostFtdcQryExecOrderField myreq = CThostFtdcQryExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryExecOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryForQuote(dict req, int nRequestID)
{
	CThostFtdcQryForQuoteField myreq = CThostFtdcQryForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryForQuote(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryQuote(dict req, int nRequestID)
{
	CThostFtdcQryQuoteField myreq = CThostFtdcQryQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "QuoteSysID", myreq.QuoteSysID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryQuote(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryLock(dict req, int nRequestID)
{
	CThostFtdcQryLockField myreq = CThostFtdcQryLockField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "LockSysID", myreq.LockSysID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryLock(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryLockPosition(dict req, int nRequestID)
{
	CThostFtdcQryLockPositionField myreq = CThostFtdcQryLockPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryLockPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorLevel(dict req, int nRequestID)
{
	CThostFtdcQryInvestorLevelField myreq = CThostFtdcQryInvestorLevelField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorLevel(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExecFreeze(dict req, int nRequestID)
{
	CThostFtdcQryExecFreezeField myreq = CThostFtdcQryExecFreezeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryExecFreeze(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombInstrumentGuard(dict req, int nRequestID)
{
	CThostFtdcQryCombInstrumentGuardField myreq = CThostFtdcQryCombInstrumentGuardField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCombInstrumentGuard(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombAction(dict req, int nRequestID)
{
	CThostFtdcQryCombActionField myreq = CThostFtdcQryCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCombAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferSerial(dict req, int nRequestID)
{
	CThostFtdcQryTransferSerialField myreq = CThostFtdcQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryAccountregister(dict req, int nRequestID)
{
	CThostFtdcQryAccountregisterField myreq = CThostFtdcQryAccountregisterField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryAccountregister(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryContractBank(dict req, int nRequestID)
{
	CThostFtdcQryContractBankField myreq = CThostFtdcQryContractBankField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BankBrchID", myreq.BankBrchID);
	getStr(req, "BankID", myreq.BankID);
	int i = this->api->ReqQryContractBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryParkedOrder(dict req, int nRequestID)
{
	CThostFtdcQryParkedOrderField myreq = CThostFtdcQryParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryParkedOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryParkedOrderAction(dict req, int nRequestID)
{
	CThostFtdcQryParkedOrderActionField myreq = CThostFtdcQryParkedOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingNotice(dict req, int nRequestID)
{
	CThostFtdcQryTradingNoticeField myreq = CThostFtdcQryTradingNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingNotice(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBrokerTradingParams(dict req, int nRequestID)
{
	CThostFtdcQryBrokerTradingParamsField myreq = CThostFtdcQryBrokerTradingParamsField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryBrokerTradingParams(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBrokerTradingAlgos(dict req, int nRequestID)
{
	CThostFtdcQryBrokerTradingAlgosField myreq = CThostFtdcQryBrokerTradingAlgosField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryBrokerTradingAlgos(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryCFMMCTradingAccountToken(dict req, int nRequestID)
{
	CThostFtdcQueryCFMMCTradingAccountTokenField myreq = CThostFtdcQueryCFMMCTradingAccountTokenField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQueryCFMMCTradingAccountToken(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromBankToFutureByFuture(dict req, int nRequestID)
{
	CThostFtdcReqTransferField myreq = CThostFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "TradeCode", myreq.TradeCode);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
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
	CThostFtdcReqTransferField myreq = CThostFtdcReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "TradeCode", myreq.TradeCode);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getDouble(req, "FutureFetchAmount", &myreq.FutureFetchAmount);
	getStr(req, "TradeDate", myreq.TradeDate);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getDouble(req, "BrokerFee", &myreq.BrokerFee);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Message", myreq.Message);
	getDouble(req, "CustFee", &myreq.CustFee);
	getDouble(req, "TradeAmount", &myreq.TradeAmount);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromFutureToBankByFuture(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryBankAccountMoneyByFuture(dict req, int nRequestID)
{
	CThostFtdcReqQueryAccountField myreq = CThostFtdcReqQueryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerBranchID", myreq.BrokerBranchID);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BankPassWord", myreq.BankPassWord);
	getStr(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getStr(req, "CustomerName", myreq.CustomerName);
	getStr(req, "TradeCode", myreq.TradeCode);
	getStr(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BankID", myreq.BankID);
	getStr(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getStr(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getStr(req, "BankSerial", myreq.BankSerial);
	getStr(req, "OperNo", myreq.OperNo);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BankSecuAcc", myreq.BankSecuAcc);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "DeviceID", myreq.DeviceID);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getStr(req, "TradeDate", myreq.TradeDate);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getStr(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getStr(req, "Digest", myreq.Digest);
	int i = this->api->ReqQueryBankAccountMoneyByFuture(&myreq, nRequestID);
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

	virtual void onRspAuthenticate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspAuthenticate")(data, error, id, last);
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

	virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspTradingAccountPasswordUpdate")(data, error, id, last);
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

	virtual void onRspParkedOrderInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspParkedOrderInsert")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspParkedOrderAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspParkedOrderAction")(data, error, id, last);
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

	virtual void onRspQueryMaxOrderVolume(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQueryMaxOrderVolume")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSettlementInfoConfirm(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspSettlementInfoConfirm")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspRemoveParkedOrder(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspRemoveParkedOrder")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspRemoveParkedOrderAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspRemoveParkedOrderAction")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspExecOrderInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspExecOrderInsert")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspExecOrderAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspExecOrderAction")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspForQuoteInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspForQuoteInsert")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQuoteInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQuoteInsert")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQuoteAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQuoteAction")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspLockInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspLockInsert")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspCombActionInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspCombActionInsert")(data, error, id, last);
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

	virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTradingAccount")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestor(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestor")(data, error, id, last);
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

	virtual void onRspQryInstrumentMarginRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInstrumentMarginRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInstrumentCommissionRate")(data, error, id, last);
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

	virtual void onRspQryProduct(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryProduct")(data, error, id, last);
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

	virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryDepthMarketData")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySettlementInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySettlementInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTransferBank(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTransferBank")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorPositionDetail")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryNotice(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryNotice")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySettlementInfoConfirm(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySettlementInfoConfirm")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorPositionCombineDetail(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorPositionCombineDetail")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryCFMMCTradingAccountKey(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryCFMMCTradingAccountKey")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryEWarrantOffset(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryEWarrantOffset")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorProductGroupMargin(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorProductGroupMargin")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchangeMarginRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExchangeMarginRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchangeMarginRateAdjust(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExchangeMarginRateAdjust")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchangeRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExchangeRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySecAgentACIDMap(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySecAgentACIDMap")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryProductExchRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryProductExchRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryProductGroup(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryProductGroup")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryOptionInstrTradeCost(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOptionInstrTradeCost")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryOptionInstrCommRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOptionInstrCommRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExecOrder(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExecOrder")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryForQuote(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryForQuote")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryQuote(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryQuote")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryLock(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryLock")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryLockPosition(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryLockPosition")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorLevel(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorLevel")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExecFreeze(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExecFreeze")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryCombInstrumentGuard(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryCombInstrumentGuard")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryCombAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryCombAction")(data, error, id, last);
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

	virtual void onRspQryAccountregister(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryAccountregister")(data, error, id, last);
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

	virtual void onRtnTradingNotice(dict data)
	{
		try
		{
			this->get_override("onRtnTradingNotice")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnErrorConditionalOrder(dict data)
	{
		try
		{
			this->get_override("onRtnErrorConditionalOrder")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnExecOrder(dict data)
	{
		try
		{
			this->get_override("onRtnExecOrder")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnExecOrderInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnExecOrderInsert")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnExecOrderAction(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnExecOrderAction")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnForQuoteInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnForQuoteInsert")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnQuote(dict data)
	{
		try
		{
			this->get_override("onRtnQuote")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnQuoteInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnQuoteInsert")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnQuoteAction(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnQuoteAction")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnForQuoteRsp(dict data)
	{
		try
		{
			this->get_override("onRtnForQuoteRsp")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnCFMMCTradingAccountToken(dict data)
	{
		try
		{
			this->get_override("onRtnCFMMCTradingAccountToken")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnLock(dict data)
	{
		try
		{
			this->get_override("onRtnLock")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnLockInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnLockInsert")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnCombAction(dict data)
	{
		try
		{
			this->get_override("onRtnCombAction")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnCombActionInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnCombActionInsert")(data, error);
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

	virtual void onRspQryParkedOrder(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryParkedOrder")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryParkedOrderAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryParkedOrderAction")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTradingNotice(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTradingNotice")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryBrokerTradingParams(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryBrokerTradingParams")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryBrokerTradingAlgos(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryBrokerTradingAlgos")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQueryCFMMCTradingAccountToken(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQueryCFMMCTradingAccountToken")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromBankToFutureByBank(dict data)
	{
		try
		{
			this->get_override("onRtnFromBankToFutureByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromFutureToBankByBank(dict data)
	{
		try
		{
			this->get_override("onRtnFromFutureToBankByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnRepealFromBankToFutureByBank(dict data)
	{
		try
		{
			this->get_override("onRtnRepealFromBankToFutureByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnRepealFromFutureToBankByBank(dict data)
	{
		try
		{
			this->get_override("onRtnRepealFromFutureToBankByBank")(data);
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

	virtual void onRtnRepealFromBankToFutureByFutureManual(dict data)
	{
		try
		{
			this->get_override("onRtnRepealFromBankToFutureByFutureManual")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnRepealFromFutureToBankByFutureManual(dict data)
	{
		try
		{
			this->get_override("onRtnRepealFromFutureToBankByFutureManual")(data);
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

	virtual void onErrRtnRepealBankToFutureByFutureManual(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnRepealBankToFutureByFutureManual")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnRepealFutureToBankByFutureManual(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnRepealFutureToBankByFutureManual")(data, error);
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

	virtual void onRtnRepealFromBankToFutureByFuture(dict data)
	{
		try
		{
			this->get_override("onRtnRepealFromBankToFutureByFuture")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnRepealFromFutureToBankByFuture(dict data)
	{
		try
		{
			this->get_override("onRtnRepealFromFutureToBankByFuture")(data);
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

	virtual void onRtnOpenAccountByBank(dict data)
	{
		try
		{
			this->get_override("onRtnOpenAccountByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnCancelAccountByBank(dict data)
	{
		try
		{
			this->get_override("onRtnCancelAccountByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnChangeAccountByBank(dict data)
	{
		try
		{
			this->get_override("onRtnChangeAccountByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

};

BOOST_PYTHON_MODULE(vnctptd)
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
		.def("subscribePrivateTopic", &TdApiWrap::subscribePrivateTopic)
		.def("subscribePublicTopic", &TdApiWrap::subscribePublicTopic)
		.def("reqAuthenticate", &TdApiWrap::reqAuthenticate)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqUserPasswordUpdate", &TdApiWrap::reqUserPasswordUpdate)
		.def("reqTradingAccountPasswordUpdate", &TdApiWrap::reqTradingAccountPasswordUpdate)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqParkedOrderInsert", &TdApiWrap::reqParkedOrderInsert)
		.def("reqParkedOrderAction", &TdApiWrap::reqParkedOrderAction)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqQueryMaxOrderVolume", &TdApiWrap::reqQueryMaxOrderVolume)
		.def("reqSettlementInfoConfirm", &TdApiWrap::reqSettlementInfoConfirm)
		.def("reqRemoveParkedOrder", &TdApiWrap::reqRemoveParkedOrder)
		.def("reqRemoveParkedOrderAction", &TdApiWrap::reqRemoveParkedOrderAction)
		.def("reqExecOrderInsert", &TdApiWrap::reqExecOrderInsert)
		.def("reqExecOrderAction", &TdApiWrap::reqExecOrderAction)
		.def("reqForQuoteInsert", &TdApiWrap::reqForQuoteInsert)
		.def("reqQuoteInsert", &TdApiWrap::reqQuoteInsert)
		.def("reqQuoteAction", &TdApiWrap::reqQuoteAction)
		.def("reqLockInsert", &TdApiWrap::reqLockInsert)
		.def("reqCombActionInsert", &TdApiWrap::reqCombActionInsert)
		.def("reqQryOrder", &TdApiWrap::reqQryOrder)
		.def("reqQryTrade", &TdApiWrap::reqQryTrade)
		.def("reqQryInvestorPosition", &TdApiWrap::reqQryInvestorPosition)
		.def("reqQryTradingAccount", &TdApiWrap::reqQryTradingAccount)
		.def("reqQryInvestor", &TdApiWrap::reqQryInvestor)
		.def("reqQryTradingCode", &TdApiWrap::reqQryTradingCode)
		.def("reqQryInstrumentMarginRate", &TdApiWrap::reqQryInstrumentMarginRate)
		.def("reqQryInstrumentCommissionRate", &TdApiWrap::reqQryInstrumentCommissionRate)
		.def("reqQryExchange", &TdApiWrap::reqQryExchange)
		.def("reqQryProduct", &TdApiWrap::reqQryProduct)
		.def("reqQryInstrument", &TdApiWrap::reqQryInstrument)
		.def("reqQryDepthMarketData", &TdApiWrap::reqQryDepthMarketData)
		.def("reqQrySettlementInfo", &TdApiWrap::reqQrySettlementInfo)
		.def("reqQryTransferBank", &TdApiWrap::reqQryTransferBank)
		.def("reqQryInvestorPositionDetail", &TdApiWrap::reqQryInvestorPositionDetail)
		.def("reqQryNotice", &TdApiWrap::reqQryNotice)
		.def("reqQrySettlementInfoConfirm", &TdApiWrap::reqQrySettlementInfoConfirm)
		.def("reqQryInvestorPositionCombineDetail", &TdApiWrap::reqQryInvestorPositionCombineDetail)
		.def("reqQryCFMMCTradingAccountKey", &TdApiWrap::reqQryCFMMCTradingAccountKey)
		.def("reqQryEWarrantOffset", &TdApiWrap::reqQryEWarrantOffset)
		.def("reqQryInvestorProductGroupMargin", &TdApiWrap::reqQryInvestorProductGroupMargin)
		.def("reqQryExchangeMarginRate", &TdApiWrap::reqQryExchangeMarginRate)
		.def("reqQryExchangeMarginRateAdjust", &TdApiWrap::reqQryExchangeMarginRateAdjust)
		.def("reqQryExchangeRate", &TdApiWrap::reqQryExchangeRate)
		.def("reqQrySecAgentACIDMap", &TdApiWrap::reqQrySecAgentACIDMap)
		.def("reqQryProductExchRate", &TdApiWrap::reqQryProductExchRate)
		.def("reqQryProductGroup", &TdApiWrap::reqQryProductGroup)
		.def("reqQryOptionInstrTradeCost", &TdApiWrap::reqQryOptionInstrTradeCost)
		.def("reqQryOptionInstrCommRate", &TdApiWrap::reqQryOptionInstrCommRate)
		.def("reqQryExecOrder", &TdApiWrap::reqQryExecOrder)
		.def("reqQryForQuote", &TdApiWrap::reqQryForQuote)
		.def("reqQryQuote", &TdApiWrap::reqQryQuote)
		.def("reqQryLock", &TdApiWrap::reqQryLock)
		.def("reqQryLockPosition", &TdApiWrap::reqQryLockPosition)
		.def("reqQryInvestorLevel", &TdApiWrap::reqQryInvestorLevel)
		.def("reqQryExecFreeze", &TdApiWrap::reqQryExecFreeze)
		.def("reqQryCombInstrumentGuard", &TdApiWrap::reqQryCombInstrumentGuard)
		.def("reqQryCombAction", &TdApiWrap::reqQryCombAction)
		.def("reqQryTransferSerial", &TdApiWrap::reqQryTransferSerial)
		.def("reqQryAccountregister", &TdApiWrap::reqQryAccountregister)
		.def("reqQryContractBank", &TdApiWrap::reqQryContractBank)
		.def("reqQryParkedOrder", &TdApiWrap::reqQryParkedOrder)
		.def("reqQryParkedOrderAction", &TdApiWrap::reqQryParkedOrderAction)
		.def("reqQryTradingNotice", &TdApiWrap::reqQryTradingNotice)
		.def("reqQryBrokerTradingParams", &TdApiWrap::reqQryBrokerTradingParams)
		.def("reqQryBrokerTradingAlgos", &TdApiWrap::reqQryBrokerTradingAlgos)
		.def("reqQueryCFMMCTradingAccountToken", &TdApiWrap::reqQueryCFMMCTradingAccountToken)
		.def("reqFromBankToFutureByFuture", &TdApiWrap::reqFromBankToFutureByFuture)
		.def("reqFromFutureToBankByFuture", &TdApiWrap::reqFromFutureToBankByFuture)
		.def("reqQueryBankAccountMoneyByFuture", &TdApiWrap::reqQueryBankAccountMoneyByFuture)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&TdApiWrap::onHeartBeatWarning))
		.def("onRspAuthenticate", pure_virtual(&TdApiWrap::onRspAuthenticate))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspUserPasswordUpdate))
		.def("onRspTradingAccountPasswordUpdate", pure_virtual(&TdApiWrap::onRspTradingAccountPasswordUpdate))
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onRspParkedOrderInsert", pure_virtual(&TdApiWrap::onRspParkedOrderInsert))
		.def("onRspParkedOrderAction", pure_virtual(&TdApiWrap::onRspParkedOrderAction))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onRspQueryMaxOrderVolume", pure_virtual(&TdApiWrap::onRspQueryMaxOrderVolume))
		.def("onRspSettlementInfoConfirm", pure_virtual(&TdApiWrap::onRspSettlementInfoConfirm))
		.def("onRspRemoveParkedOrder", pure_virtual(&TdApiWrap::onRspRemoveParkedOrder))
		.def("onRspRemoveParkedOrderAction", pure_virtual(&TdApiWrap::onRspRemoveParkedOrderAction))
		.def("onRspExecOrderInsert", pure_virtual(&TdApiWrap::onRspExecOrderInsert))
		.def("onRspExecOrderAction", pure_virtual(&TdApiWrap::onRspExecOrderAction))
		.def("onRspForQuoteInsert", pure_virtual(&TdApiWrap::onRspForQuoteInsert))
		.def("onRspQuoteInsert", pure_virtual(&TdApiWrap::onRspQuoteInsert))
		.def("onRspQuoteAction", pure_virtual(&TdApiWrap::onRspQuoteAction))
		.def("onRspLockInsert", pure_virtual(&TdApiWrap::onRspLockInsert))
		.def("onRspCombActionInsert", pure_virtual(&TdApiWrap::onRspCombActionInsert))
		.def("onRspQryOrder", pure_virtual(&TdApiWrap::onRspQryOrder))
		.def("onRspQryTrade", pure_virtual(&TdApiWrap::onRspQryTrade))
		.def("onRspQryInvestorPosition", pure_virtual(&TdApiWrap::onRspQryInvestorPosition))
		.def("onRspQryTradingAccount", pure_virtual(&TdApiWrap::onRspQryTradingAccount))
		.def("onRspQryInvestor", pure_virtual(&TdApiWrap::onRspQryInvestor))
		.def("onRspQryTradingCode", pure_virtual(&TdApiWrap::onRspQryTradingCode))
		.def("onRspQryInstrumentMarginRate", pure_virtual(&TdApiWrap::onRspQryInstrumentMarginRate))
		.def("onRspQryInstrumentCommissionRate", pure_virtual(&TdApiWrap::onRspQryInstrumentCommissionRate))
		.def("onRspQryExchange", pure_virtual(&TdApiWrap::onRspQryExchange))
		.def("onRspQryProduct", pure_virtual(&TdApiWrap::onRspQryProduct))
		.def("onRspQryInstrument", pure_virtual(&TdApiWrap::onRspQryInstrument))
		.def("onRspQryDepthMarketData", pure_virtual(&TdApiWrap::onRspQryDepthMarketData))
		.def("onRspQrySettlementInfo", pure_virtual(&TdApiWrap::onRspQrySettlementInfo))
		.def("onRspQryTransferBank", pure_virtual(&TdApiWrap::onRspQryTransferBank))
		.def("onRspQryInvestorPositionDetail", pure_virtual(&TdApiWrap::onRspQryInvestorPositionDetail))
		.def("onRspQryNotice", pure_virtual(&TdApiWrap::onRspQryNotice))
		.def("onRspQrySettlementInfoConfirm", pure_virtual(&TdApiWrap::onRspQrySettlementInfoConfirm))
		.def("onRspQryInvestorPositionCombineDetail", pure_virtual(&TdApiWrap::onRspQryInvestorPositionCombineDetail))
		.def("onRspQryCFMMCTradingAccountKey", pure_virtual(&TdApiWrap::onRspQryCFMMCTradingAccountKey))
		.def("onRspQryEWarrantOffset", pure_virtual(&TdApiWrap::onRspQryEWarrantOffset))
		.def("onRspQryInvestorProductGroupMargin", pure_virtual(&TdApiWrap::onRspQryInvestorProductGroupMargin))
		.def("onRspQryExchangeMarginRate", pure_virtual(&TdApiWrap::onRspQryExchangeMarginRate))
		.def("onRspQryExchangeMarginRateAdjust", pure_virtual(&TdApiWrap::onRspQryExchangeMarginRateAdjust))
		.def("onRspQryExchangeRate", pure_virtual(&TdApiWrap::onRspQryExchangeRate))
		.def("onRspQrySecAgentACIDMap", pure_virtual(&TdApiWrap::onRspQrySecAgentACIDMap))
		.def("onRspQryProductExchRate", pure_virtual(&TdApiWrap::onRspQryProductExchRate))
		.def("onRspQryProductGroup", pure_virtual(&TdApiWrap::onRspQryProductGroup))
		.def("onRspQryOptionInstrTradeCost", pure_virtual(&TdApiWrap::onRspQryOptionInstrTradeCost))
		.def("onRspQryOptionInstrCommRate", pure_virtual(&TdApiWrap::onRspQryOptionInstrCommRate))
		.def("onRspQryExecOrder", pure_virtual(&TdApiWrap::onRspQryExecOrder))
		.def("onRspQryForQuote", pure_virtual(&TdApiWrap::onRspQryForQuote))
		.def("onRspQryQuote", pure_virtual(&TdApiWrap::onRspQryQuote))
		.def("onRspQryLock", pure_virtual(&TdApiWrap::onRspQryLock))
		.def("onRspQryLockPosition", pure_virtual(&TdApiWrap::onRspQryLockPosition))
		.def("onRspQryInvestorLevel", pure_virtual(&TdApiWrap::onRspQryInvestorLevel))
		.def("onRspQryExecFreeze", pure_virtual(&TdApiWrap::onRspQryExecFreeze))
		.def("onRspQryCombInstrumentGuard", pure_virtual(&TdApiWrap::onRspQryCombInstrumentGuard))
		.def("onRspQryCombAction", pure_virtual(&TdApiWrap::onRspQryCombAction))
		.def("onRspQryTransferSerial", pure_virtual(&TdApiWrap::onRspQryTransferSerial))
		.def("onRspQryAccountregister", pure_virtual(&TdApiWrap::onRspQryAccountregister))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onErrRtnOrderInsert", pure_virtual(&TdApiWrap::onErrRtnOrderInsert))
		.def("onErrRtnOrderAction", pure_virtual(&TdApiWrap::onErrRtnOrderAction))
		.def("onRtnInstrumentStatus", pure_virtual(&TdApiWrap::onRtnInstrumentStatus))
		.def("onRtnTradingNotice", pure_virtual(&TdApiWrap::onRtnTradingNotice))
		.def("onRtnErrorConditionalOrder", pure_virtual(&TdApiWrap::onRtnErrorConditionalOrder))
		.def("onRtnExecOrder", pure_virtual(&TdApiWrap::onRtnExecOrder))
		.def("onErrRtnExecOrderInsert", pure_virtual(&TdApiWrap::onErrRtnExecOrderInsert))
		.def("onErrRtnExecOrderAction", pure_virtual(&TdApiWrap::onErrRtnExecOrderAction))
		.def("onErrRtnForQuoteInsert", pure_virtual(&TdApiWrap::onErrRtnForQuoteInsert))
		.def("onRtnQuote", pure_virtual(&TdApiWrap::onRtnQuote))
		.def("onErrRtnQuoteInsert", pure_virtual(&TdApiWrap::onErrRtnQuoteInsert))
		.def("onErrRtnQuoteAction", pure_virtual(&TdApiWrap::onErrRtnQuoteAction))
		.def("onRtnForQuoteRsp", pure_virtual(&TdApiWrap::onRtnForQuoteRsp))
		.def("onRtnCFMMCTradingAccountToken", pure_virtual(&TdApiWrap::onRtnCFMMCTradingAccountToken))
		.def("onRtnLock", pure_virtual(&TdApiWrap::onRtnLock))
		.def("onErrRtnLockInsert", pure_virtual(&TdApiWrap::onErrRtnLockInsert))
		.def("onRtnCombAction", pure_virtual(&TdApiWrap::onRtnCombAction))
		.def("onErrRtnCombActionInsert", pure_virtual(&TdApiWrap::onErrRtnCombActionInsert))
		.def("onRspQryContractBank", pure_virtual(&TdApiWrap::onRspQryContractBank))
		.def("onRspQryParkedOrder", pure_virtual(&TdApiWrap::onRspQryParkedOrder))
		.def("onRspQryParkedOrderAction", pure_virtual(&TdApiWrap::onRspQryParkedOrderAction))
		.def("onRspQryTradingNotice", pure_virtual(&TdApiWrap::onRspQryTradingNotice))
		.def("onRspQryBrokerTradingParams", pure_virtual(&TdApiWrap::onRspQryBrokerTradingParams))
		.def("onRspQryBrokerTradingAlgos", pure_virtual(&TdApiWrap::onRspQryBrokerTradingAlgos))
		.def("onRspQueryCFMMCTradingAccountToken", pure_virtual(&TdApiWrap::onRspQueryCFMMCTradingAccountToken))
		.def("onRtnFromBankToFutureByBank", pure_virtual(&TdApiWrap::onRtnFromBankToFutureByBank))
		.def("onRtnFromFutureToBankByBank", pure_virtual(&TdApiWrap::onRtnFromFutureToBankByBank))
		.def("onRtnRepealFromBankToFutureByBank", pure_virtual(&TdApiWrap::onRtnRepealFromBankToFutureByBank))
		.def("onRtnRepealFromFutureToBankByBank", pure_virtual(&TdApiWrap::onRtnRepealFromFutureToBankByBank))
		.def("onRtnFromBankToFutureByFuture", pure_virtual(&TdApiWrap::onRtnFromBankToFutureByFuture))
		.def("onRtnFromFutureToBankByFuture", pure_virtual(&TdApiWrap::onRtnFromFutureToBankByFuture))
		.def("onRtnRepealFromBankToFutureByFutureManual", pure_virtual(&TdApiWrap::onRtnRepealFromBankToFutureByFutureManual))
		.def("onRtnRepealFromFutureToBankByFutureManual", pure_virtual(&TdApiWrap::onRtnRepealFromFutureToBankByFutureManual))
		.def("onRtnQueryBankBalanceByFuture", pure_virtual(&TdApiWrap::onRtnQueryBankBalanceByFuture))
		.def("onErrRtnBankToFutureByFuture", pure_virtual(&TdApiWrap::onErrRtnBankToFutureByFuture))
		.def("onErrRtnFutureToBankByFuture", pure_virtual(&TdApiWrap::onErrRtnFutureToBankByFuture))
		.def("onErrRtnRepealBankToFutureByFutureManual", pure_virtual(&TdApiWrap::onErrRtnRepealBankToFutureByFutureManual))
		.def("onErrRtnRepealFutureToBankByFutureManual", pure_virtual(&TdApiWrap::onErrRtnRepealFutureToBankByFutureManual))
		.def("onErrRtnQueryBankBalanceByFuture", pure_virtual(&TdApiWrap::onErrRtnQueryBankBalanceByFuture))
		.def("onRtnRepealFromBankToFutureByFuture", pure_virtual(&TdApiWrap::onRtnRepealFromBankToFutureByFuture))
		.def("onRtnRepealFromFutureToBankByFuture", pure_virtual(&TdApiWrap::onRtnRepealFromFutureToBankByFuture))
		.def("onRspFromBankToFutureByFuture", pure_virtual(&TdApiWrap::onRspFromBankToFutureByFuture))
		.def("onRspFromFutureToBankByFuture", pure_virtual(&TdApiWrap::onRspFromFutureToBankByFuture))
		.def("onRspQueryBankAccountMoneyByFuture", pure_virtual(&TdApiWrap::onRspQueryBankAccountMoneyByFuture))
		.def("onRtnOpenAccountByBank", pure_virtual(&TdApiWrap::onRtnOpenAccountByBank))
		.def("onRtnCancelAccountByBank", pure_virtual(&TdApiWrap::onRtnCancelAccountByBank))
		.def("onRtnChangeAccountByBank", pure_virtual(&TdApiWrap::onRtnChangeAccountByBank))
		;
}
