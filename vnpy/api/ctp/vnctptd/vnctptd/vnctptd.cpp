#include "vnctptd.h"
#include <exception>

void getInt(dict d, string key, int *value)
{
	if (d.has_key(key))		
	{
		object o = d[key];	
		extract<int> x(o);	
		if (x.check())		
		{
			*value = x();	
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
///C++�Ļص����������ݱ��浽������
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

void TdApi::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERAUTHMETHOD;

	if (pRspUserAuthMethod)
	{
		task.task_data = *pRspUserAuthMethod;
	}
	else
	{
		CThostFtdcRspUserAuthMethodField empty_data = CThostFtdcRspUserAuthMethodField();
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

void TdApi::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPGENUSERCAPTCHA;

	if (pRspGenUserCaptcha)
	{
		task.task_data = *pRspGenUserCaptcha;
	}
	else
	{
		CThostFtdcRspGenUserCaptchaField empty_data = CThostFtdcRspGenUserCaptchaField();
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

void TdApi::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPGENUSERTEXT;

	if (pRspGenUserText)
	{
		task.task_data = *pRspGenUserText;
	}
	else
	{
		CThostFtdcRspGenUserTextField empty_data = CThostFtdcRspGenUserTextField();
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

void TdApi::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPBATCHORDERACTION;

	if (pInputBatchOrderAction)
	{
		task.task_data = *pInputBatchOrderAction;
	}
	else
	{
		CThostFtdcInputBatchOrderActionField empty_data = CThostFtdcInputBatchOrderActionField();
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

void TdApi::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPOPTIONSELFCLOSEINSERT;

	if (pInputOptionSelfClose)
	{
		task.task_data = *pInputOptionSelfClose;
	}
	else
	{
		CThostFtdcInputOptionSelfCloseField empty_data = CThostFtdcInputOptionSelfCloseField();
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

void TdApi::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPOPTIONSELFCLOSEACTION;

	if (pInputOptionSelfCloseAction)
	{
		task.task_data = *pInputOptionSelfCloseAction;
	}
	else
	{
		CThostFtdcInputOptionSelfCloseActionField empty_data = CThostFtdcInputOptionSelfCloseActionField();
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

void TdApi::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYMMINSTRUMENTCOMMISSIONRATE;

	if (pMMInstrumentCommissionRate)
	{
		task.task_data = *pMMInstrumentCommissionRate;
	}
	else
	{
		CThostFtdcMMInstrumentCommissionRateField empty_data = CThostFtdcMMInstrumentCommissionRateField();
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

void TdApi::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYMMOPTIONINSTRCOMMRATE;

	if (pMMOptionInstrCommRate)
	{
		task.task_data = *pMMOptionInstrCommRate;
	}
	else
	{
		CThostFtdcMMOptionInstrCommRateField empty_data = CThostFtdcMMOptionInstrCommRateField();
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

void TdApi::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTORDERCOMMRATE;

	if (pInstrumentOrderCommRate)
	{
		task.task_data = *pInstrumentOrderCommRate;
	}
	else
	{
		CThostFtdcInstrumentOrderCommRateField empty_data = CThostFtdcInstrumentOrderCommRateField();
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

void TdApi::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSECAGENTTRADINGACCOUNT;

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

void TdApi::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSECAGENTCHECKMODE;

	if (pSecAgentCheckMode)
	{
		task.task_data = *pSecAgentCheckMode;
	}
	else
	{
		CThostFtdcSecAgentCheckModeField empty_data = CThostFtdcSecAgentCheckModeField();
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

void TdApi::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSECAGENTTRADEINFO;

	if (pSecAgentTradeInfo)
	{
		task.task_data = *pSecAgentTradeInfo;
	}
	else
	{
		CThostFtdcSecAgentTradeInfoField empty_data = CThostFtdcSecAgentTradeInfoField();
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

void TdApi::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYOPTIONSELFCLOSE;

	if (pOptionSelfClose)
	{
		task.task_data = *pOptionSelfClose;
	}
	else
	{
		CThostFtdcOptionSelfCloseField empty_data = CThostFtdcOptionSelfCloseField();
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

void TdApi::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTUNIT;

	if (pInvestUnit)
	{
		task.task_data = *pInvestUnit;
	}
	else
	{
		CThostFtdcInvestUnitField empty_data = CThostFtdcInvestUnitField();
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

void TdApi::OnRtnBulletin(CThostFtdcBulletinField *pBulletin)
{
	Task task = Task();
	task.task_name = ONRTNBULLETIN;

	if (pBulletin)
	{
		task.task_data = *pBulletin;
	}
	else
	{
		CThostFtdcBulletinField empty_data = CThostFtdcBulletinField();
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

void TdApi::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNBATCHORDERACTION;

	if (pBatchOrderAction)
	{
		task.task_data = *pBatchOrderAction;
	}
	else
	{
		CThostFtdcBatchOrderActionField empty_data = CThostFtdcBatchOrderActionField();
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

void TdApi::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose)
{
	Task task = Task();
	task.task_name = ONRTNOPTIONSELFCLOSE;

	if (pOptionSelfClose)
	{
		task.task_data = *pOptionSelfClose;
	}
	else
	{
		CThostFtdcOptionSelfCloseField empty_data = CThostFtdcOptionSelfCloseField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNOPTIONSELFCLOSEINSERT;

	if (pInputOptionSelfClose)
	{
		task.task_data = *pInputOptionSelfClose;
	}
	else
	{
		CThostFtdcInputOptionSelfCloseField empty_data = CThostFtdcInputOptionSelfCloseField();
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

void TdApi::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNOPTIONSELFCLOSEACTION;

	if (pOptionSelfCloseAction)
	{
		task.task_data = *pOptionSelfCloseAction;
	}
	else
	{
		CThostFtdcOptionSelfCloseActionField empty_data = CThostFtdcOptionSelfCloseActionField();
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
///�����̴߳Ӷ�����ȡ�����ݣ�ת��Ϊpython����󣬽�������
///-------------------------------------------------------------------------------------

void TdApi::processTask()
{
	while (1)
	{
		Task task = this->task_queue.wait_and_pop();

		try
		{
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

			case ONRSPUSERAUTHMETHOD:
			{
				this->processRspUserAuthMethod(task);
				break;
			}

			case ONRSPGENUSERCAPTCHA:
			{
				this->processRspGenUserCaptcha(task);
				break;
			}

			case ONRSPGENUSERTEXT:
			{
				this->processRspGenUserText(task);
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

			case ONRSPBATCHORDERACTION:
			{
				this->processRspBatchOrderAction(task);
				break;
			}

			case ONRSPOPTIONSELFCLOSEINSERT:
			{
				this->processRspOptionSelfCloseInsert(task);
				break;
			}

			case ONRSPOPTIONSELFCLOSEACTION:
			{
				this->processRspOptionSelfCloseAction(task);
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

			case ONRSPQRYMMINSTRUMENTCOMMISSIONRATE:
			{
				this->processRspQryMMInstrumentCommissionRate(task);
				break;
			}

			case ONRSPQRYMMOPTIONINSTRCOMMRATE:
			{
				this->processRspQryMMOptionInstrCommRate(task);
				break;
			}

			case ONRSPQRYINSTRUMENTORDERCOMMRATE:
			{
				this->processRspQryInstrumentOrderCommRate(task);
				break;
			}

			case ONRSPQRYSECAGENTTRADINGACCOUNT:
			{
				this->processRspQrySecAgentTradingAccount(task);
				break;
			}

			case ONRSPQRYSECAGENTCHECKMODE:
			{
				this->processRspQrySecAgentCheckMode(task);
				break;
			}

			case ONRSPQRYSECAGENTTRADEINFO:
			{
				this->processRspQrySecAgentTradeInfo(task);
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

			case ONRSPQRYOPTIONSELFCLOSE:
			{
				this->processRspQryOptionSelfClose(task);
				break;
			}

			case ONRSPQRYINVESTUNIT:
			{
				this->processRspQryInvestUnit(task);
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

			case ONRTNBULLETIN:
			{
				this->processRtnBulletin(task);
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

			case ONERRRTNBATCHORDERACTION:
			{
				this->processErrRtnBatchOrderAction(task);
				break;
			}

			case ONRTNOPTIONSELFCLOSE:
			{
				this->processRtnOptionSelfClose(task);
				break;
			}

			case ONERRRTNOPTIONSELFCLOSEINSERT:
			{
				this->processErrRtnOptionSelfCloseInsert(task);
				break;
			}

			case ONERRRTNOPTIONSELFCLOSEACTION:
			{
				this->processErrRtnOptionSelfCloseAction(task);
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
		catch (std::exception & e)
		{
			cout << "TdApi processTask exception: " << e.what() << task.task_name << endl;
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

	cout << "begin processRspAuthenticate\n" << endl;

	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["AppID"] = boost::locale::conv::to_utf<char>(task_data.AppID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AppType"] = task_data.AppType;
	data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspAuthenticate(data, error, task.task_id, task.task_last);
	cout << "end processRspAuthenticate\n" << endl;
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CThostFtdcRspUserLoginField task_data = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CZCETime"] = boost::locale::conv::to_utf<char>(task_data.CZCETime, std::string("GB2312"));
    data["DCETime"] = boost::locale::conv::to_utf<char>(task_data.DCETime, std::string("GB2312"));
    data["FFEXTime"] = boost::locale::conv::to_utf<char>(task_data.FFEXTime, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["INETime"] = boost::locale::conv::to_utf<char>(task_data.INETime, std::string("GB2312"));
    data["LoginTime"] = boost::locale::conv::to_utf<char>(task_data.LoginTime, std::string("GB2312"));
    data["MaxOrderRef"] = boost::locale::conv::to_utf<char>(task_data.MaxOrderRef, std::string("GB2312"));
    data["SessionID"] = task_data.SessionID;
    data["SHFETime"] = boost::locale::conv::to_utf<char>(task_data.SHFETime, std::string("GB2312"));
    data["SystemName"] = boost::locale::conv::to_utf<char>(task_data.SystemName, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcUserPasswordUpdateField task_data = any_cast<CThostFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["OldPassword"] = boost::locale::conv::to_utf<char>(task_data.OldPassword, std::string("GB2312"));
	data["NewPassword"] = boost::locale::conv::to_utf<char>(task_data.NewPassword, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountPasswordUpdateField task_data = any_cast<CThostFtdcTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["NewPassword"] = boost::locale::conv::to_utf<char>(task_data.NewPassword, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["OldPassword"] = boost::locale::conv::to_utf<char>(task_data.OldPassword, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserAuthMethod(Task task)
{
	PyLock lock;
	CThostFtdcRspUserAuthMethodField task_data = any_cast<CThostFtdcRspUserAuthMethodField>(task.task_data);
	dict data;
	data["UsableAuthMethod"] = task_data.UsableAuthMethod;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserAuthMethod(data, error, task.task_id, task.task_last);
};

void TdApi::processRspGenUserCaptcha(Task task)
{
	PyLock lock;
	CThostFtdcRspGenUserCaptchaField task_data = any_cast<CThostFtdcRspGenUserCaptchaField>(task.task_data);
	dict data;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CaptchaInfoLen"] = task_data.CaptchaInfoLen;
	data["CaptchaInfo"] = boost::locale::conv::to_utf<char>(task_data.CaptchaInfo, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspGenUserCaptcha(data, error, task.task_id, task.task_last);
};

void TdApi::processRspGenUserText(Task task)
{
	PyLock lock;
	CThostFtdcRspGenUserTextField task_data = any_cast<CThostFtdcRspGenUserTextField>(task.task_data);
	dict data;
	data["UserTextSeq"] = task_data.UserTextSeq;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspGenUserText(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["TimeCondition"] = task_data.TimeCondition;
	data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
	data["StopPrice"] = task_data.StopPrice;
	data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
	data["UserForceClose"] = task_data.UserForceClose;
    data["ForceCloseReason"] = task_data.ForceCloseReason;
    data["VolumeCondition"] = task_data.VolumeCondition;
	data["LimitPrice"] = task_data.LimitPrice;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
	data["Direction"] = task_data.Direction;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
	data["MinVolume"] = task_data.MinVolume;



	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
    data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
    data["ContingentCondition"] = task_data.ContingentCondition;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForceCloseReason"] = task_data.ForceCloseReason;
    data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["IsAutoSuspend"] = task_data.IsAutoSuspend;
    data["IsSwapOrder"] = task_data.IsSwapOrder;
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["MinVolume"] = task_data.MinVolume;
    data["OrderPriceType"] = task_data.OrderPriceType;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["ParkedOrderID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["Status"] = task_data.Status;
    data["StopPrice"] = task_data.StopPrice;
    data["TimeCondition"] = task_data.TimeCondition;
    data["UserForceClose"] = task_data.UserForceClose;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserType"] = task_data.UserType;
    data["VolumeCondition"] = task_data.VolumeCondition;
    data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspParkedOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
	data["ActionFlag"] = task_data.ActionFlag;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OrderActionRef"] = task_data.OrderActionRef;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["ParkedOrderActionID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderActionID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["Status"] = task_data.Status;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserType"] = task_data.UserType;
    data["VolumeChange"] = task_data.VolumeChange;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderActionField task_data = any_cast<CThostFtdcInputOrderActionField>(task.task_data);
	dict data;
    data["ActionFlag"] = task_data.ActionFlag;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OrderActionRef"] = task_data.OrderActionRef;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VolumeChange"] = task_data.VolumeChange;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryMaxOrderVolume(Task task)
{
	PyLock lock;
	CThostFtdcQueryMaxOrderVolumeField task_data = any_cast<CThostFtdcQueryMaxOrderVolumeField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["MaxVolume"] = task_data.MaxVolume;
    data["OffsetFlag"] = task_data.OffsetFlag;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQueryMaxOrderVolume(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["SettlementID"] = task_data.SettlementID;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ConfirmDate"] = boost::locale::conv::to_utf<char>(task_data.ConfirmDate, std::string("GB2312"));
	data["ConfirmTime"] = boost::locale::conv::to_utf<char>(task_data.ConfirmTime, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspSettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderField task_data = any_cast<CThostFtdcRemoveParkedOrderField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["ParkedOrderID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspRemoveParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspRemoveParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcRemoveParkedOrderActionField task_data = any_cast<CThostFtdcRemoveParkedOrderActionField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["ParkedOrderActionID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderActionID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspRemoveParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActionType"] = task_data.ActionType;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CloseFlag"] = task_data.CloseFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OffsetFlag"] = task_data.OffsetFlag;
    data["PosiDirection"] = task_data.PosiDirection;
    data["RequestID"] = task_data.RequestID;
    data["ReservePositionFlag"] = task_data.ReservePositionFlag;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspExecOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderActionField task_data = any_cast<CThostFtdcInputExecOrderActionField>(task.task_data);
	dict data;
	data["ActionFlag"] = task_data.ActionFlag;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
    data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
    data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspExecOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForQuoteRef"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteRef, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspForQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
    data["AskHedgeFlag"] = task_data.AskHedgeFlag;
    data["AskOffsetFlag"] = task_data.AskOffsetFlag;
    data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
    data["AskPrice"] = task_data.AskPrice;
    data["AskVolume"] = task_data.AskVolume;
    data["BidHedgeFlag"] = task_data.BidHedgeFlag;
    data["BidOffsetFlag"] = task_data.BidOffsetFlag;
    data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
    data["BidPrice"] = task_data.BidPrice;
    data["BidVolume"] = task_data.BidVolume;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQuoteInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteActionField task_data = any_cast<CThostFtdcInputQuoteActionField>(task.task_data);
	dict data;
    data["ActionFlag"] = task_data.ActionFlag;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["QuoteActionRef"] = task_data.QuoteActionRef;
    data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
    data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQuoteAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspBatchOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputBatchOrderActionField task_data = any_cast<CThostFtdcInputBatchOrderActionField>(task.task_data);
	dict data;
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspBatchOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOptionSelfCloseInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOptionSelfCloseField task_data = any_cast<CThostFtdcInputOptionSelfCloseField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OptSelfCloseFlag"] = task_data.OptSelfCloseFlag;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["OptionSelfCloseRef"] = task_data.OptionSelfCloseRef;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspOptionSelfCloseInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOptionSelfCloseAction(Task task)
{
	PyLock lock;
	CThostFtdcInputOptionSelfCloseActionField task_data = any_cast<CThostFtdcInputOptionSelfCloseActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OptionSelfCloseSysID"] = task_data.OptionSelfCloseSysID;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["OptionSelfCloseActionRef"] = task_data.OptionSelfCloseActionRef;
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OptionSelfCloseRef"] = task_data.OptionSelfCloseRef;
	data["FrontID"] = task_data.FrontID;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspOptionSelfCloseAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
    data["CombDirection"] = task_data.CombDirection;
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspCombActionInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;

    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActiveTime"] = boost::locale::conv::to_utf<char>(task_data.ActiveTime, std::string("GB2312"));
    data["ActiveTraderID"] = boost::locale::conv::to_utf<char>(task_data.ActiveTraderID, std::string("GB2312"));
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
    data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
    data["ContingentCondition"] = task_data.ContingentCondition;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ForceCloseReason"] = task_data.ForceCloseReason;
    data["FrontID"] = task_data.FrontID;
    data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["IsAutoSuspend"] = task_data.IsAutoSuspend;
    data["IsSwapOrder"] = task_data.IsSwapOrder;
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["MinVolume"] = task_data.MinVolume;
    data["NotifySequence"] = task_data.NotifySequence;
    data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
    data["OrderPriceType"] = task_data.OrderPriceType;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSource"] = task_data.OrderSource;
    data["OrderStatus"] = task_data.OrderStatus;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["OrderType"] = task_data.OrderType;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["RelativeOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.RelativeOrderSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["StopPrice"] = task_data.StopPrice;
    data["SuspendTime"] = boost::locale::conv::to_utf<char>(task_data.SuspendTime, std::string("GB2312"));
    data["TimeCondition"] = task_data.TimeCondition;
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
    data["UserForceClose"] = task_data.UserForceClose;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["VolumeCondition"] = task_data.VolumeCondition;
    data["VolumeTotal"] = task_data.VolumeTotal;
    data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
    data["VolumeTraded"] = task_data.VolumeTraded;
    data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["OffsetFlag"] = task_data.OffsetFlag;
    data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["Price"] = task_data.Price;
    data["PriceSource"] = task_data.PriceSource;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SettlementID"] = task_data.SettlementID;
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradeSource"] = task_data.TradeSource;
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradeType"] = task_data.TradeType;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TradingRole"] = task_data.TradingRole;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionField task_data = any_cast<CThostFtdcInvestorPositionField>(task.task_data);
	dict data;
    data["AbandonFrozen"] = task_data.AbandonFrozen;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CashIn"] = task_data.CashIn;
    data["CloseAmount"] = task_data.CloseAmount;
    data["CloseProfit"] = task_data.CloseProfit;
    data["CloseProfitByDate"] = task_data.CloseProfitByDate;
    data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
    data["CloseVolume"] = task_data.CloseVolume;
    data["CombLongFrozen"] = task_data.CombLongFrozen;
    data["CombPosition"] = task_data.CombPosition;
    data["CombShortFrozen"] = task_data.CombShortFrozen;
    data["Commission"] = task_data.Commission;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeMargin"] = task_data.ExchangeMargin;
    data["FrozenCash"] = task_data.FrozenCash;
    data["FrozenCommission"] = task_data.FrozenCommission;
    data["FrozenMargin"] = task_data.FrozenMargin;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["LongFrozen"] = task_data.LongFrozen;
    data["LongFrozenAmount"] = task_data.LongFrozenAmount;
    data["MarginRateByMoney"] = task_data.MarginRateByMoney;
    data["MarginRateByVolume"] = task_data.MarginRateByVolume;
    data["OpenAmount"] = task_data.OpenAmount;
    data["OpenCost"] = task_data.OpenCost;
    data["OpenVolume"] = task_data.OpenVolume;
    data["PosiDirection"] = task_data.PosiDirection;
    data["Position"] = task_data.Position;
    data["PositionCost"] = task_data.PositionCost;
    data["PositionDate"] = task_data.PositionDate;
    data["PositionProfit"] = task_data.PositionProfit;
    data["PreMargin"] = task_data.PreMargin;
    data["PreSettlementPrice"] = task_data.PreSettlementPrice;
    data["SettlementID"] = task_data.SettlementID;
    data["SettlementPrice"] = task_data.SettlementPrice;
    data["ShortFrozen"] = task_data.ShortFrozen;
    data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
    data["StrikeFrozen"] = task_data.StrikeFrozen;
    data["StrikeFrozenAmount"] = task_data.StrikeFrozenAmount;
    data["TodayPosition"] = task_data.TodayPosition;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UseMargin"] = task_data.UseMargin;
    data["YdPosition"] = task_data.YdPosition;
    data["YdStrikeFrozen"] = task_data.YdStrikeFrozen;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountField task_data = any_cast<CThostFtdcTradingAccountField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["Available"] = task_data.Available;
    data["Balance"] = task_data.Balance;
    data["BizType"] = task_data.BizType;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CashIn"] = task_data.CashIn;
    data["CloseProfit"] = task_data.CloseProfit;
    data["Commission"] = task_data.Commission;
    data["Credit"] = task_data.Credit;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CurrMargin"] = task_data.CurrMargin;
    data["DeliveryMargin"] = task_data.DeliveryMargin;
    data["Deposit"] = task_data.Deposit;
    data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
    data["ExchangeMargin"] = task_data.ExchangeMargin;
    data["FrozenCash"] = task_data.FrozenCash;
    data["FrozenCommission"] = task_data.FrozenCommission;
    data["FrozenMargin"] = task_data.FrozenMargin;
    data["FrozenSwap"] = task_data.FrozenSwap;
    data["FundMortgageAvailable"] = task_data.FundMortgageAvailable;
    data["FundMortgageIn"] = task_data.FundMortgageIn;
    data["FundMortgageOut"] = task_data.FundMortgageOut;
    data["Interest"] = task_data.Interest;
    data["InterestBase"] = task_data.InterestBase;
    data["Mortgage"] = task_data.Mortgage;
    data["MortgageableFund"] = task_data.MortgageableFund;
    data["PositionProfit"] = task_data.PositionProfit;
    data["PreBalance"] = task_data.PreBalance;
    data["PreCredit"] = task_data.PreCredit;
    data["PreDeposit"] = task_data.PreDeposit;
    data["PreFundMortgageIn"] = task_data.PreFundMortgageIn;
    data["PreFundMortgageOut"] = task_data.PreFundMortgageOut;
    data["PreMargin"] = task_data.PreMargin;
    data["PreMortgage"] = task_data.PreMortgage;
    data["RemainSwap"] = task_data.RemainSwap;
    data["Reserve"] = task_data.Reserve;
    data["ReserveBalance"] = task_data.ReserveBalance;
    data["SettlementID"] = task_data.SettlementID;
    data["SpecProductCloseProfit"] = task_data.SpecProductCloseProfit;
    data["SpecProductCommission"] = task_data.SpecProductCommission;
    data["SpecProductExchangeMargin"] = task_data.SpecProductExchangeMargin;
    data["SpecProductFrozenCommission"] = task_data.SpecProductFrozenCommission;
    data["SpecProductFrozenMargin"] = task_data.SpecProductFrozenMargin;
    data["SpecProductMargin"] = task_data.SpecProductMargin;
    data["SpecProductPositionProfit"] = task_data.SpecProductPositionProfit;
    data["SpecProductPositionProfitByAlg"] = task_data.SpecProductPositionProfitByAlg;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["Withdraw"] = task_data.Withdraw;
    data["WithdrawQuota"] = task_data.WithdrawQuota;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CThostFtdcInvestorField task_data = any_cast<CThostFtdcInvestorField>(task.task_data);
	dict data;
    data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CommModelID"] = boost::locale::conv::to_utf<char>(task_data.CommModelID, std::string("GB2312"));
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["IdentifiedCardType"] = task_data.IdentifiedCardType;
    data["InvestorGroupID"] = boost::locale::conv::to_utf<char>(task_data.InvestorGroupID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestorName"] = boost::locale::conv::to_utf<char>(task_data.InvestorName, std::string("GB2312"));
    data["IsActive"] = task_data.IsActive;
    data["MarginModelID"] = boost::locale::conv::to_utf<char>(task_data.MarginModelID, std::string("GB2312"));
    data["Mobile"] = boost::locale::conv::to_utf<char>(task_data.Mobile, std::string("GB2312"));
    data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
    data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CThostFtdcTradingCodeField task_data = any_cast<CThostFtdcTradingCodeField>(task.task_data);
	dict data;
    data["BizType"] = task_data.BizType;
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ClientIDType"] = task_data.ClientIDType;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IsActive"] = task_data.IsActive;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentMarginRateField task_data = any_cast<CThostFtdcInstrumentMarginRateField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestorRange"] = task_data.InvestorRange;
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IsRelative"] = task_data.IsRelative;
    data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
    data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;
    data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
    data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInstrumentMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentCommissionRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentCommissionRateField task_data = any_cast<CThostFtdcInstrumentCommissionRateField>(task.task_data);
	dict data;
    data["BizType"] = task_data.BizType;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
    data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
    data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
    data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestorRange"] = task_data.InvestorRange;
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
    data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInstrumentCommissionRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CThostFtdcExchangeField task_data = any_cast<CThostFtdcExchangeField>(task.task_data);
	dict data;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ExchangeProperty"] = task_data.ExchangeProperty;
	data["ExchangeName"] = boost::locale::conv::to_utf<char>(task_data.ExchangeName, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProduct(Task task)
{
	PyLock lock;
	CThostFtdcProductField task_data = any_cast<CThostFtdcProductField>(task.task_data);
	dict data;
    data["CloseDealType"] = task_data.CloseDealType;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeProductID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeProductID, std::string("GB2312"));
    data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
    data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
    data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
    data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
    data["MortgageFundUseRange"] = task_data.MortgageFundUseRange;
    data["PositionDateType"] = task_data.PositionDateType;
    data["PositionType"] = task_data.PositionType;
    data["PriceTick"] = task_data.PriceTick;
    data["ProductClass"] = task_data.ProductClass;
    data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
    data["ProductName"] = boost::locale::conv::to_utf<char>(task_data.ProductName, std::string("GB2312"));
    data["TradeCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.TradeCurrencyID, std::string("GB2312"));
    data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
    data["VolumeMultiple"] = task_data.VolumeMultiple;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryProduct(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentField task_data = any_cast<CThostFtdcInstrumentField>(task.task_data);
	dict data;
    data["CombinationType"] = task_data.CombinationType;
    data["CreateDate"] = boost::locale::conv::to_utf<char>(task_data.CreateDate, std::string("GB2312"));
    data["DeliveryMonth"] = task_data.DeliveryMonth;
    data["DeliveryYear"] = task_data.DeliveryYear;
    data["EndDelivDate"] = boost::locale::conv::to_utf<char>(task_data.EndDelivDate, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ExpireDate"] = boost::locale::conv::to_utf<char>(task_data.ExpireDate, std::string("GB2312"));
    data["InstLifePhase"] = task_data.InstLifePhase;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InstrumentName"] = boost::locale::conv::to_utf<char>(task_data.InstrumentName, std::string("GB2312"));
    data["IsTrading"] = task_data.IsTrading;
    data["LongMarginRatio"] = task_data.LongMarginRatio;
    data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
    data["MaxMarginSideAlgorithm"] = task_data.MaxMarginSideAlgorithm;
    data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
    data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
    data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
    data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
    data["OptionsType"] = task_data.OptionsType;
    data["PositionDateType"] = task_data.PositionDateType;
    data["PositionType"] = task_data.PositionType;
    data["PriceTick"] = task_data.PriceTick;
    data["ProductClass"] = task_data.ProductClass;
    data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
    data["ShortMarginRatio"] = task_data.ShortMarginRatio;
    data["StartDelivDate"] = boost::locale::conv::to_utf<char>(task_data.StartDelivDate, std::string("GB2312"));
    data["StrikePrice"] = task_data.StrikePrice;
    data["UnderlyingInstrID"] = boost::locale::conv::to_utf<char>(task_data.UnderlyingInstrID, std::string("GB2312"));
    data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
    data["VolumeMultiple"] = task_data.VolumeMultiple;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
    data["ActionDay"] = boost::locale::conv::to_utf<char>(task_data.ActionDay, std::string("GB2312"));
    data["AskPrice1"] = task_data.AskPrice1;
    data["AskPrice2"] = task_data.AskPrice2;
    data["AskPrice3"] = task_data.AskPrice3;
    data["AskPrice4"] = task_data.AskPrice4;
    data["AskPrice5"] = task_data.AskPrice5;
    data["AskVolume1"] = task_data.AskVolume1;
    data["AskVolume2"] = task_data.AskVolume2;
    data["AskVolume3"] = task_data.AskVolume3;
    data["AskVolume4"] = task_data.AskVolume4;
    data["AskVolume5"] = task_data.AskVolume5;
    data["AveragePrice"] = task_data.AveragePrice;
    data["BidPrice1"] = task_data.BidPrice1;
    data["BidPrice2"] = task_data.BidPrice2;
    data["BidPrice3"] = task_data.BidPrice3;
    data["BidPrice4"] = task_data.BidPrice4;
    data["BidPrice5"] = task_data.BidPrice5;
    data["BidVolume1"] = task_data.BidVolume1;
    data["BidVolume2"] = task_data.BidVolume2;
    data["BidVolume3"] = task_data.BidVolume3;
    data["BidVolume4"] = task_data.BidVolume4;
    data["BidVolume5"] = task_data.BidVolume5;
    data["ClosePrice"] = task_data.ClosePrice;
    data["CurrDelta"] = task_data.CurrDelta;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["HighestPrice"] = task_data.HighestPrice;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["LastPrice"] = task_data.LastPrice;
    data["LowerLimitPrice"] = task_data.LowerLimitPrice;
    data["LowestPrice"] = task_data.LowestPrice;
    data["OpenInterest"] = task_data.OpenInterest;
    data["OpenPrice"] = task_data.OpenPrice;
    data["PreClosePrice"] = task_data.PreClosePrice;
    data["PreDelta"] = task_data.PreDelta;
    data["PreOpenInterest"] = task_data.PreOpenInterest;
    data["PreSettlementPrice"] = task_data.PreSettlementPrice;
    data["SettlementPrice"] = task_data.SettlementPrice;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["Turnover"] = task_data.Turnover;
    data["UpdateMillisec"] = task_data.UpdateMillisec;
    data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
    data["UpperLimitPrice"] = task_data.UpperLimitPrice;
    data["Volume"] = task_data.Volume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfo(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoField task_data = any_cast<CThostFtdcSettlementInfoField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["Content"] = boost::locale::conv::to_utf<char>(task_data.Content, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["SequenceNo"] = task_data.SequenceNo;
    data["SettlementID"] = task_data.SettlementID;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySettlementInfo(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferBank(Task task)
{
	PyLock lock;
	CThostFtdcTransferBankField task_data = any_cast<CThostFtdcTransferBankField>(task.task_data);
	dict data;
	data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
	data["BankBrchID"] = boost::locale::conv::to_utf<char>(task_data.BankBrchID, std::string("GB2312"));
	data["BankName"] = boost::locale::conv::to_utf<char>(task_data.BankName, std::string("GB2312"));
	data["IsActive"] = task_data.IsActive;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTransferBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionDetailField task_data = any_cast<CThostFtdcInvestorPositionDetailField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CloseAmount"] = task_data.CloseAmount;
    data["CloseProfitByDate"] = task_data.CloseProfitByDate;
    data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
    data["CloseVolume"] = task_data.CloseVolume;
    data["CombInstrumentID"] = boost::locale::conv::to_utf<char>(task_data.CombInstrumentID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchMargin"] = task_data.ExchMargin;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["LastSettlementPrice"] = task_data.LastSettlementPrice;
    data["Margin"] = task_data.Margin;
    data["MarginRateByMoney"] = task_data.MarginRateByMoney;
    data["MarginRateByVolume"] = task_data.MarginRateByVolume;
    data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
    data["OpenPrice"] = task_data.OpenPrice;
    data["PositionProfitByDate"] = task_data.PositionProfitByDate;
    data["PositionProfitByTrade"] = task_data.PositionProfitByTrade;
    data["SettlementID"] = task_data.SettlementID;
    data["SettlementPrice"] = task_data.SettlementPrice;
    data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
    data["TradeType"] = task_data.TradeType;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorPositionDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryNotice(Task task)
{
	PyLock lock;
	CThostFtdcNoticeField task_data = any_cast<CThostFtdcNoticeField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["Content"] = boost::locale::conv::to_utf<char>(task_data.Content, std::string("GB2312"));
    data["SequenceLabel"] = boost::locale::conv::to_utf<char>(task_data.SequenceLabel, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfoConfirm(Task task)
{
	PyLock lock;
	CThostFtdcSettlementInfoConfirmField task_data = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["SettlementID"] = task_data.SettlementID;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ConfirmDate"] = boost::locale::conv::to_utf<char>(task_data.ConfirmDate, std::string("GB2312"));
	data["ConfirmTime"] = boost::locale::conv::to_utf<char>(task_data.ConfirmTime, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionCombineDetail(Task task)
{
	PyLock lock;
	CThostFtdcInvestorPositionCombineDetailField task_data = any_cast<CThostFtdcInvestorPositionCombineDetailField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CombInstrumentID"] = boost::locale::conv::to_utf<char>(task_data.CombInstrumentID, std::string("GB2312"));
    data["ComTradeID"] = boost::locale::conv::to_utf<char>(task_data.ComTradeID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchMargin"] = task_data.ExchMargin;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["LegID"] = task_data.LegID;
    data["LegMultiple"] = task_data.LegMultiple;
    data["Margin"] = task_data.Margin;
    data["MarginRateByMoney"] = task_data.MarginRateByMoney;
    data["MarginRateByVolume"] = task_data.MarginRateByVolume;
    data["OpenDate"] = boost::locale::conv::to_utf<char>(task_data.OpenDate, std::string("GB2312"));
    data["SettlementID"] = task_data.SettlementID;
    data["TotalAmt"] = task_data.TotalAmt;
    data["TradeGroupID"] = task_data.TradeGroupID;
    data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorPositionCombineDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCFMMCTradingAccountKey(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountKeyField task_data = any_cast<CThostFtdcCFMMCTradingAccountKeyField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CurrentKey"] = boost::locale::conv::to_utf<char>(task_data.CurrentKey, std::string("GB2312"));
    data["KeyID"] = task_data.KeyID;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryCFMMCTradingAccountKey(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryEWarrantOffset(Task task)
{
	PyLock lock;
	CThostFtdcEWarrantOffsetField task_data = any_cast<CThostFtdcEWarrantOffsetField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryEWarrantOffset(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorProductGroupMargin(Task task)
{
	PyLock lock;
	CThostFtdcInvestorProductGroupMarginField task_data = any_cast<CThostFtdcInvestorProductGroupMarginField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CashIn"] = task_data.CashIn;
    data["CloseProfit"] = task_data.CloseProfit;
    data["Commission"] = task_data.Commission;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchMargin"] = task_data.ExchMargin;
    data["ExchOffsetAmount"] = task_data.ExchOffsetAmount;
    data["FrozenCash"] = task_data.FrozenCash;
    data["FrozenCommission"] = task_data.FrozenCommission;
    data["FrozenMargin"] = task_data.FrozenMargin;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["LongExchMargin"] = task_data.LongExchMargin;
    data["LongExchOffsetAmount"] = task_data.LongExchOffsetAmount;
    data["LongFrozenMargin"] = task_data.LongFrozenMargin;
    data["LongOffsetAmount"] = task_data.LongOffsetAmount;
    data["LongUseMargin"] = task_data.LongUseMargin;
    data["OffsetAmount"] = task_data.OffsetAmount;
    data["PositionProfit"] = task_data.PositionProfit;
    data["ProductGroupID"] = boost::locale::conv::to_utf<char>(task_data.ProductGroupID, std::string("GB2312"));
    data["SettlementID"] = task_data.SettlementID;
    data["ShortExchMargin"] = task_data.ShortExchMargin;
    data["ShortExchOffsetAmount"] = task_data.ShortExchOffsetAmount;
    data["ShortFrozenMargin"] = task_data.ShortFrozenMargin;
    data["ShortOffsetAmount"] = task_data.ShortOffsetAmount;
    data["ShortUseMargin"] = task_data.ShortUseMargin;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UseMargin"] = task_data.UseMargin;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestorProductGroupMargin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateField task_data = any_cast<CThostFtdcExchangeMarginRateField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
    data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;
    data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
    data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchangeMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeMarginRateAdjust(Task task)
{
	PyLock lock;
	CThostFtdcExchangeMarginRateAdjustField task_data = any_cast<CThostFtdcExchangeMarginRateAdjustField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchLongMarginRatioByMoney"] = task_data.ExchLongMarginRatioByMoney;
    data["ExchLongMarginRatioByVolume"] = task_data.ExchLongMarginRatioByVolume;
    data["ExchShortMarginRatioByMoney"] = task_data.ExchShortMarginRatioByMoney;
    data["ExchShortMarginRatioByVolume"] = task_data.ExchShortMarginRatioByVolume;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
    data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;
    data["NoLongMarginRatioByMoney"] = task_data.NoLongMarginRatioByMoney;
    data["NoLongMarginRatioByVolume"] = task_data.NoLongMarginRatioByVolume;
    data["NoShortMarginRatioByMoney"] = task_data.NoShortMarginRatioByMoney;
    data["NoShortMarginRatioByVolume"] = task_data.NoShortMarginRatioByVolume;
    data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
    data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchangeMarginRateAdjust(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchangeRate(Task task)
{
	PyLock lock;
	CThostFtdcExchangeRateField task_data = any_cast<CThostFtdcExchangeRateField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeRate"] = task_data.ExchangeRate;
    data["FromCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.FromCurrencyID, std::string("GB2312"));
    data["FromCurrencyUnit"] = task_data.FromCurrencyUnit;
    data["ToCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.ToCurrencyID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExchangeRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySecAgentACIDMap(Task task)
{
	PyLock lock;
	CThostFtdcSecAgentACIDMapField task_data = any_cast<CThostFtdcSecAgentACIDMapField>(task.task_data);
	dict data;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["BrokerSecAgentID"] = task_data.BrokerSecAgentID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySecAgentACIDMap(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductExchRate(Task task)
{
	PyLock lock;
	CThostFtdcProductExchRateField task_data = any_cast<CThostFtdcProductExchRateField>(task.task_data);
	dict data;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ExchangeRate"] = task_data.ExchangeRate;
	data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
	data["QuoteCurrencyID"] = boost::locale::conv::to_utf<char>(task_data.QuoteCurrencyID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryProductExchRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryProductGroup(Task task)
{
	PyLock lock;
	CThostFtdcProductGroupField task_data = any_cast<CThostFtdcProductGroupField>(task.task_data);
	dict data;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ProductID"] = boost::locale::conv::to_utf<char>(task_data.ProductID, std::string("GB2312"));
	data["ProductGroupID"] = boost::locale::conv::to_utf<char>(task_data.ProductGroupID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryProductGroup(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryMMInstrumentCommissionRate(Task task)
{
	PyLock lock;
	CThostFtdcMMInstrumentCommissionRateField task_data = any_cast<CThostFtdcMMInstrumentCommissionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorRange"] = task_data.InvestorRange;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryMMInstrumentCommissionRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryMMOptionInstrCommRate(Task task)
{
	PyLock lock;
	CThostFtdcMMOptionInstrCommRateField task_data = any_cast<CThostFtdcMMOptionInstrCommRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
	data["StrikeRatioByMoney"] = task_data.StrikeRatioByMoney;
	data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
	data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorRange"] = task_data.InvestorRange;
	data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
	data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;
	data["StrikeRatioByVolume"] = task_data.StrikeRatioByVolume;
	data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryMMOptionInstrCommRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentOrderCommRate(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentOrderCommRateField task_data = any_cast<CThostFtdcInstrumentOrderCommRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["OrderActionCommByVolume"] = task_data.OrderActionCommByVolume;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorRange"] = task_data.InvestorRange;
	data["OrderCommByVolume"] = task_data.OrderCommByVolume;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInstrumentOrderCommRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySecAgentTradingAccount(Task task)
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
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["Available"] = task_data.Available;
	data["FundMortgageAvailable"] = task_data.FundMortgageAvailable;
	data["FrozenSwap"] = task_data.FrozenSwap;
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
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["RemainSwap"] = task_data.RemainSwap;
	data["Balance"] = task_data.Balance;
	data["SpecProductMargin"] = task_data.SpecProductMargin;
	data["SpecProductPositionProfitByAlg"] = task_data.SpecProductPositionProfitByAlg;
	data["Reserve"] = task_data.Reserve;
	data["PreDeposit"] = task_data.PreDeposit;
	data["Credit"] = task_data.Credit;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
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
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySecAgentTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySecAgentCheckMode(Task task)
{
	PyLock lock;
	CThostFtdcSecAgentCheckModeField task_data = any_cast<CThostFtdcSecAgentCheckModeField>(task.task_data);
	dict data;
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerSecAgentID"] = task_data.BrokerSecAgentID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["CheckSelfAccount"] = task_data.CheckSelfAccount;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySecAgentCheckMode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySecAgentTradeInfo(Task task)
{
	PyLock lock;
	CThostFtdcSecAgentTradeInfoField task_data = any_cast<CThostFtdcSecAgentTradeInfoField>(task.task_data);
	dict data;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerSecAgentID"] = task_data.BrokerSecAgentID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["LongCustomerName"] = task_data.LongCustomerName;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQrySecAgentTradeInfo(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrTradeCost(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrTradeCostField task_data = any_cast<CThostFtdcOptionInstrTradeCostField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchFixedMargin"] = task_data.ExchFixedMargin;
    data["ExchMiniMargin"] = task_data.ExchMiniMargin;
    data["FixedMargin"] = task_data.FixedMargin;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["MiniMargin"] = task_data.MiniMargin;
    data["Royalty"] = task_data.Royalty;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryOptionInstrTradeCost(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionInstrCommRate(Task task)
{
	PyLock lock;
	CThostFtdcOptionInstrCommRateField task_data = any_cast<CThostFtdcOptionInstrCommRateField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CloseRatioByMoney"] = task_data.CloseRatioByMoney;
    data["CloseRatioByVolume"] = task_data.CloseRatioByVolume;
    data["CloseTodayRatioByMoney"] = task_data.CloseTodayRatioByMoney;
    data["CloseTodayRatioByVolume"] = task_data.CloseTodayRatioByVolume;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestorRange"] = task_data.InvestorRange;
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["OpenRatioByMoney"] = task_data.OpenRatioByMoney;
    data["OpenRatioByVolume"] = task_data.OpenRatioByVolume;
    data["StrikeRatioByMoney"] = task_data.StrikeRatioByMoney;
    data["StrikeRatioByVolume"] = task_data.StrikeRatioByVolume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryOptionInstrCommRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActionType"] = task_data.ActionType;
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CloseFlag"] = task_data.CloseFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ExecOrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderLocalID, std::string("GB2312"));
    data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
    data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
    data["ExecResult"] = task_data.ExecResult;
    data["FrontID"] = task_data.FrontID;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["NotifySequence"] = task_data.NotifySequence;
    data["OffsetFlag"] = task_data.OffsetFlag;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["PosiDirection"] = task_data.PosiDirection;
    data["RequestID"] = task_data.RequestID;
    data["ReservePositionFlag"] = task_data.ReservePositionFlag;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryExecOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryForQuote(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteField task_data = any_cast<CThostFtdcForQuoteField>(task.task_data);
	dict data;
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["BrokerForQutoSeq"] = task_data.BrokerForQutoSeq;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ForQuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteLocalID, std::string("GB2312"));
    data["ForQuoteRef"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteRef, std::string("GB2312"));
    data["ForQuoteStatus"] = task_data.ForQuoteStatus;
    data["FrontID"] = task_data.FrontID;
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["SessionID"] = task_data.SessionID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryForQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["AskHedgeFlag"] = task_data.AskHedgeFlag;
    data["AskOffsetFlag"] = task_data.AskOffsetFlag;
    data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
    data["AskOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.AskOrderSysID, std::string("GB2312"));
    data["AskPrice"] = task_data.AskPrice;
    data["AskVolume"] = task_data.AskVolume;
    data["BidHedgeFlag"] = task_data.BidHedgeFlag;
    data["BidOffsetFlag"] = task_data.BidOffsetFlag;
    data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
    data["BidOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.BidOrderSysID, std::string("GB2312"));
    data["BidPrice"] = task_data.BidPrice;
    data["BidVolume"] = task_data.BidVolume;
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["NotifySequence"] = task_data.NotifySequence;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["QuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.QuoteLocalID, std::string("GB2312"));
    data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
    data["QuoteStatus"] = task_data.QuoteStatus;
    data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryQuote(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOptionSelfClose(Task task)
{
	PyLock lock;
	CThostFtdcOptionSelfCloseField task_data = any_cast<CThostFtdcOptionSelfCloseField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerOptionSelfCloseSeq"] = task_data.BrokerOptionSelfCloseSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ExecResult"] = task_data.ExecResult;
    data["FrontID"] = task_data.FrontID;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InsertDate"] = task_data.InsertDate;
    data["InsertTime"] = task_data.InsertTime;
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["NotifySequence"] = task_data.NotifySequence;
    data["OptionSelfCloseLocalID"] = task_data.OptionSelfCloseLocalID;
    data["OptionSelfCloseRef"] = task_data.OptionSelfCloseRef;
    data["OptionSelfCloseSysID"] = task_data.OptionSelfCloseSysID;
    data["OptSelfCloseFlag"] = task_data.OptSelfCloseFlag;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryOptionSelfClose(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestUnit(Task task)
{
	PyLock lock;
	CThostFtdcInvestUnitField task_data = any_cast<CThostFtdcInvestUnitField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CommModelID"] = task_data.CommModelID;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["InvestorGroupID"] = task_data.InvestorGroupID;
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestorUnitName"] = task_data.InvestorUnitName;
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["MarginModelID"] = task_data.MarginModelID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryInvestUnit(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombInstrumentGuard(Task task)
{
	PyLock lock;
	CThostFtdcCombInstrumentGuardField task_data = any_cast<CThostFtdcCombInstrumentGuardField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["GuarantRatio"] = task_data.GuarantRatio;
	data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryCombInstrumentGuard(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
    data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
    data["ActionStatus"] = task_data.ActionStatus;
    data["BranchID"] = task_data.BranchID;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
    data["CombDirection"] = task_data.CombDirection;
    data["ComTradeID"] = task_data.ComTradeID;
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["NotifySequence"] = task_data.NotifySequence;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryCombAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	CThostFtdcTransferSerialField task_data = any_cast<CThostFtdcTransferSerialField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["AvailabilityFlag"] = task_data.AvailabilityFlag;
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankNewAccount"] = boost::locale::conv::to_utf<char>(task_data.BankNewAccount, std::string("GB2312"));
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FutureAccType"] = task_data.FutureAccType;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["OperatorCode"] = boost::locale::conv::to_utf<char>(task_data.OperatorCode, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["SessionID"] = task_data.SessionID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTransferSerial(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryAccountregister(Task task)
{
	PyLock lock;
	CThostFtdcAccountregisterField task_data = any_cast<CThostFtdcAccountregisterField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["LongCustomerName"] = task_data.LongCustomerName;
    data["OpenOrDestroy"] = task_data.OpenOrDestroy;
    data["OutDate"] = boost::locale::conv::to_utf<char>(task_data.OutDate, std::string("GB2312"));
    data["RegDate"] = boost::locale::conv::to_utf<char>(task_data.RegDate, std::string("GB2312"));
    data["TID"] = task_data.TID;
    data["TradeDay"] = boost::locale::conv::to_utf<char>(task_data.TradeDay, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryAccountregister(data, error, task.task_id, task.task_last);
};

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActiveTime"] = boost::locale::conv::to_utf<char>(task_data.ActiveTime, std::string("GB2312"));
    data["ActiveTraderID"] = boost::locale::conv::to_utf<char>(task_data.ActiveTraderID, std::string("GB2312"));
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
    data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
    data["ContingentCondition"] = task_data.ContingentCondition;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ForceCloseReason"] = task_data.ForceCloseReason;
    data["FrontID"] = task_data.FrontID;
    data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["IsAutoSuspend"] = task_data.IsAutoSuspend;
    data["IsSwapOrder"] = task_data.IsSwapOrder;
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["MinVolume"] = task_data.MinVolume;
    data["NotifySequence"] = task_data.NotifySequence;
    data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
    data["OrderPriceType"] = task_data.OrderPriceType;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSource"] = task_data.OrderSource;
    data["OrderStatus"] = task_data.OrderStatus;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["OrderType"] = task_data.OrderType;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["RelativeOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.RelativeOrderSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["StopPrice"] = task_data.StopPrice;
    data["SuspendTime"] = boost::locale::conv::to_utf<char>(task_data.SuspendTime, std::string("GB2312"));
    data["TimeCondition"] = task_data.TimeCondition;
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
    data["UserForceClose"] = task_data.UserForceClose;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["VolumeCondition"] = task_data.VolumeCondition;
    data["VolumeTotal"] = task_data.VolumeTotal;
    data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
    data["VolumeTraded"] = task_data.VolumeTraded;
    data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;


	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["OffsetFlag"] = task_data.OffsetFlag;
    data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["Price"] = task_data.Price;
    data["PriceSource"] = task_data.PriceSource;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SettlementID"] = task_data.SettlementID;
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeID"] = boost::locale::conv::to_utf<char>(task_data.TradeID, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradeSource"] = task_data.TradeSource;
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradeType"] = task_data.TradeType;
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TradingRole"] = task_data.TradingRole;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
    data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
    data["ContingentCondition"] = task_data.ContingentCondition;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForceCloseReason"] = task_data.ForceCloseReason;
    data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["IsAutoSuspend"] = task_data.IsAutoSuspend;
    data["IsSwapOrder"] = task_data.IsSwapOrder;
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["MinVolume"] = task_data.MinVolume;
    data["OrderPriceType"] = task_data.OrderPriceType;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["StopPrice"] = task_data.StopPrice;
    data["TimeCondition"] = task_data.TimeCondition;
    data["UserForceClose"] = task_data.UserForceClose;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VolumeCondition"] = task_data.VolumeCondition;
    data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcOrderActionField task_data = any_cast<CThostFtdcOrderActionField>(task.task_data);
	dict data;
    data["ActionDate"] = boost::locale::conv::to_utf<char>(task_data.ActionDate, std::string("GB2312"));
    data["ActionFlag"] = task_data.ActionFlag;
    data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
    data["ActionTime"] = boost::locale::conv::to_utf<char>(task_data.ActionTime, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OrderActionRef"] = task_data.OrderActionRef;
    data["OrderActionStatus"] = task_data.OrderActionStatus;
    data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VolumeChange"] = task_data.VolumeChange;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentStatusField task_data = any_cast<CThostFtdcInstrumentStatusField>(task.task_data);
	dict data;
    data["EnterReason"] = task_data.EnterReason;
    data["EnterTime"] = boost::locale::conv::to_utf<char>(task_data.EnterTime, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InstrumentStatus"] = task_data.InstrumentStatus;
    data["SettlementGroupID"] = boost::locale::conv::to_utf<char>(task_data.SettlementGroupID, std::string("GB2312"));
    data["TradingSegmentSN"] = task_data.TradingSegmentSN;


	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnBulletin(Task task)
{
	PyLock lock;
	CThostFtdcBulletinField task_data = any_cast<CThostFtdcBulletinField>(task.task_data);
	dict data;
	data["URLLink"] = task_data.URLLink;
	data["Content"] = task_data.Content;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["SequenceNo"] = task_data.SequenceNo;
	data["Abstract"] = task_data.Abstract;
	data["BulletinID"] = task_data.BulletinID;
	data["NewsUrgency"] = task_data.NewsUrgency;
	data["NewsType"] = task_data.NewsType;
	data["ComeFrom"] = task_data.ComeFrom;
	data["TradingDay"] = task_data.TradingDay;
	data["SendTime"] = task_data.SendTime;
	data["MarketID"] = task_data.MarketID;

	this->onRtnBulletin(data);
};

void TdApi::processRtnTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeInfoField task_data = any_cast<CThostFtdcTradingNoticeInfoField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["FieldContent"] = boost::locale::conv::to_utf<char>(task_data.FieldContent, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["SendTime"] = boost::locale::conv::to_utf<char>(task_data.SendTime, std::string("GB2312"));
    data["SequenceNo"] = task_data.SequenceNo;
    data["SequenceSeries"] = task_data.SequenceSeries;


	this->onRtnTradingNotice(data);
};

void TdApi::processRtnErrorConditionalOrder(Task task)
{
	PyLock lock;
	CThostFtdcErrorConditionalOrderField task_data = any_cast<CThostFtdcErrorConditionalOrderField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActiveTime"] = boost::locale::conv::to_utf<char>(task_data.ActiveTime, std::string("GB2312"));
    data["ActiveTraderID"] = boost::locale::conv::to_utf<char>(task_data.ActiveTraderID, std::string("GB2312"));
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
    data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
    data["ContingentCondition"] = task_data.ContingentCondition;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ForceCloseReason"] = task_data.ForceCloseReason;
    data["FrontID"] = task_data.FrontID;
    data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["IsAutoSuspend"] = task_data.IsAutoSuspend;
    data["IsSwapOrder"] = task_data.IsSwapOrder;
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["MinVolume"] = task_data.MinVolume;
    data["NotifySequence"] = task_data.NotifySequence;
    data["OrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.OrderLocalID, std::string("GB2312"));
    data["OrderPriceType"] = task_data.OrderPriceType;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSource"] = task_data.OrderSource;
    data["OrderStatus"] = task_data.OrderStatus;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["OrderType"] = task_data.OrderType;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["RelativeOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.RelativeOrderSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["StopPrice"] = task_data.StopPrice;
    data["SuspendTime"] = boost::locale::conv::to_utf<char>(task_data.SuspendTime, std::string("GB2312"));
    data["TimeCondition"] = task_data.TimeCondition;
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UpdateTime"] = boost::locale::conv::to_utf<char>(task_data.UpdateTime, std::string("GB2312"));
    data["UserForceClose"] = task_data.UserForceClose;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["VolumeCondition"] = task_data.VolumeCondition;
    data["VolumeTotal"] = task_data.VolumeTotal;
    data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
    data["VolumeTraded"] = task_data.VolumeTraded;
    data["ZCETotalTradedVolume"] = task_data.ZCETotalTradedVolume;


	this->onRtnErrorConditionalOrder(data);
};

void TdApi::processRtnExecOrder(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderField task_data = any_cast<CThostFtdcExecOrderField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActionType"] = task_data.ActionType;
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerExecOrderSeq"] = task_data.BrokerExecOrderSeq;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CloseFlag"] = task_data.CloseFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ExecOrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderLocalID, std::string("GB2312"));
    data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
    data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
    data["ExecResult"] = task_data.ExecResult;
    data["FrontID"] = task_data.FrontID;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["NotifySequence"] = task_data.NotifySequence;
    data["OffsetFlag"] = task_data.OffsetFlag;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["PosiDirection"] = task_data.PosiDirection;
    data["RequestID"] = task_data.RequestID;
    data["ReservePositionFlag"] = task_data.ReservePositionFlag;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	this->onRtnExecOrder(data);
};

void TdApi::processErrRtnExecOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputExecOrderField task_data = any_cast<CThostFtdcInputExecOrderField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActionType"] = task_data.ActionType;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CloseFlag"] = task_data.CloseFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OffsetFlag"] = task_data.OffsetFlag;
    data["PosiDirection"] = task_data.PosiDirection;
    data["RequestID"] = task_data.RequestID;
    data["ReservePositionFlag"] = task_data.ReservePositionFlag;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnExecOrderInsert(data, error);
};

void TdApi::processErrRtnExecOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcExecOrderActionField task_data = any_cast<CThostFtdcExecOrderActionField>(task.task_data);
	dict data;
    data["ActionDate"] = boost::locale::conv::to_utf<char>(task_data.ActionDate, std::string("GB2312"));
    data["ActionFlag"] = task_data.ActionFlag;
    data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
    data["ActionTime"] = boost::locale::conv::to_utf<char>(task_data.ActionTime, std::string("GB2312"));
    data["ActionType"] = task_data.ActionType;
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExecOrderActionRef"] = task_data.ExecOrderActionRef;
    data["ExecOrderLocalID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderLocalID, std::string("GB2312"));
    data["ExecOrderRef"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderRef, std::string("GB2312"));
    data["ExecOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.ExecOrderSysID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OrderActionStatus"] = task_data.OrderActionStatus;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnExecOrderAction(data, error);
};

void TdApi::processErrRtnForQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputForQuoteField task_data = any_cast<CThostFtdcInputForQuoteField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForQuoteRef"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteRef, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnForQuoteInsert(data, error);
};

void TdApi::processRtnQuote(Task task)
{
	PyLock lock;
	CThostFtdcQuoteField task_data = any_cast<CThostFtdcQuoteField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["ActiveUserID"] = boost::locale::conv::to_utf<char>(task_data.ActiveUserID, std::string("GB2312"));
    data["AskHedgeFlag"] = task_data.AskHedgeFlag;
    data["AskOffsetFlag"] = task_data.AskOffsetFlag;
    data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
    data["AskOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.AskOrderSysID, std::string("GB2312"));
    data["AskPrice"] = task_data.AskPrice;
    data["AskVolume"] = task_data.AskVolume;
    data["BidHedgeFlag"] = task_data.BidHedgeFlag;
    data["BidOffsetFlag"] = task_data.BidOffsetFlag;
    data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
    data["BidOrderSysID"] = boost::locale::conv::to_utf<char>(task_data.BidOrderSysID, std::string("GB2312"));
    data["BidPrice"] = task_data.BidPrice;
    data["BidVolume"] = task_data.BidVolume;
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerQuoteSeq"] = task_data.BrokerQuoteSeq;
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["CancelTime"] = boost::locale::conv::to_utf<char>(task_data.CancelTime, std::string("GB2312"));
    data["ClearingPartID"] = boost::locale::conv::to_utf<char>(task_data.ClearingPartID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InsertDate"] = boost::locale::conv::to_utf<char>(task_data.InsertDate, std::string("GB2312"));
    data["InsertTime"] = boost::locale::conv::to_utf<char>(task_data.InsertTime, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["NotifySequence"] = task_data.NotifySequence;
    data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["QuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.QuoteLocalID, std::string("GB2312"));
    data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
    data["QuoteStatus"] = task_data.QuoteStatus;
    data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));

	this->onRtnQuote(data);
};

void TdApi::processErrRtnQuoteInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputQuoteField task_data = any_cast<CThostFtdcInputQuoteField>(task.task_data);
	dict data;
	data["AskHedgeFlag"] = task_data.AskHedgeFlag;
    data["AskOffsetFlag"] = task_data.AskOffsetFlag;
    data["AskOrderRef"] = boost::locale::conv::to_utf<char>(task_data.AskOrderRef, std::string("GB2312"));
    data["AskPrice"] = task_data.AskPrice;
    data["AskVolume"] = task_data.AskVolume;
    data["BidHedgeFlag"] = task_data.BidHedgeFlag;
    data["BidOffsetFlag"] = task_data.BidOffsetFlag;
    data["BidOrderRef"] = boost::locale::conv::to_utf<char>(task_data.BidOrderRef, std::string("GB2312"));
    data["BidPrice"] = task_data.BidPrice;
    data["BidVolume"] = task_data.BidVolume;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnQuoteInsert(data, error);
};

void TdApi::processErrRtnQuoteAction(Task task)
{
	PyLock lock;
	CThostFtdcQuoteActionField task_data = any_cast<CThostFtdcQuoteActionField>(task.task_data);
	dict data;
    data["ActionDate"] = boost::locale::conv::to_utf<char>(task_data.ActionDate, std::string("GB2312"));
    data["ActionFlag"] = task_data.ActionFlag;
    data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
    data["ActionTime"] = boost::locale::conv::to_utf<char>(task_data.ActionTime, std::string("GB2312"));
    data["BranchID"] = boost::locale::conv::to_utf<char>(task_data.BranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OrderActionStatus"] = task_data.OrderActionStatus;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["QuoteActionRef"] = task_data.QuoteActionRef;
    data["QuoteLocalID"] = boost::locale::conv::to_utf<char>(task_data.QuoteLocalID, std::string("GB2312"));
    data["QuoteRef"] = boost::locale::conv::to_utf<char>(task_data.QuoteRef, std::string("GB2312"));
    data["QuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.QuoteSysID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnQuoteAction(data, error);
};

void TdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	CThostFtdcForQuoteRspField task_data = any_cast<CThostFtdcForQuoteRspField>(task.task_data);
	dict data;
	data["ActionDay"] = boost::locale::conv::to_utf<char>(task_data.ActionDay, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForQuoteSysID"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteSysID, std::string("GB2312"));
    data["ForQuoteTime"] = boost::locale::conv::to_utf<char>(task_data.ForQuoteTime, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));

	this->onRtnForQuoteRsp(data);
};

void TdApi::processRtnCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["KeyID"] = task_data.KeyID;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["Token"] = boost::locale::conv::to_utf<char>(task_data.Token, std::string("GB2312"));

	this->onRtnCFMMCTradingAccountToken(data);
};

void TdApi::processErrRtnBatchOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcBatchOrderActionField task_data = any_cast<CThostFtdcBatchOrderActionField>(task.task_data);
	dict data;
	data["ActionDate"] = task_data.ActionDate;
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["ActionTime"] = task_data.ActionTime;
	data["StatusMsg"] = task_data.StatusMsg;
	data["ParticipantID"] = task_data.ParticipantID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["InstallID"] = task_data.InstallID;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
	data["OrderActionStatus"] = task_data.OrderActionStatus;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnBatchOrderAction(data, error);
};

void TdApi::processRtnOptionSelfClose(Task task)
{
	PyLock lock;
	CThostFtdcOptionSelfCloseField task_data = any_cast<CThostFtdcOptionSelfCloseField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ExecResult"] = task_data.ExecResult;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["Volume"] = task_data.Volume;
	data["SessionID"] = task_data.SessionID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["OptionSelfCloseRef"] = task_data.OptionSelfCloseRef;
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["InstrumentID"] = task_data.InstrumentID;
	data["OptionSelfCloseSysID"] = task_data.OptionSelfCloseSysID;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InsertTime"] = task_data.InsertTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["OptSelfCloseFlag"] = task_data.OptSelfCloseFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["BrokerOptionSelfCloseSeq"] = task_data.BrokerOptionSelfCloseSeq;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["BranchID"] = task_data.BranchID;
	data["SequenceNo"] = task_data.SequenceNo;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["OptionSelfCloseLocalID"] = task_data.OptionSelfCloseLocalID;

	this->onRtnOptionSelfClose(data);
};

void TdApi::processErrRtnOptionSelfCloseInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOptionSelfCloseField task_data = any_cast<CThostFtdcInputOptionSelfCloseField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OptSelfCloseFlag"] = task_data.OptSelfCloseFlag;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["RequestID"] = task_data.RequestID;
	data["OptionSelfCloseRef"] = task_data.OptionSelfCloseRef;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
	data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnOptionSelfCloseInsert(data, error);
};

void TdApi::processErrRtnOptionSelfCloseAction(Task task)
{
	PyLock lock;
	CThostFtdcOptionSelfCloseActionField task_data = any_cast<CThostFtdcOptionSelfCloseActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
	data["OrderActionStatus"] = task_data.OrderActionStatus;
	data["StatusMsg"] = task_data.StatusMsg;
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
	data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OptionSelfCloseRef"] = task_data.OptionSelfCloseRef;
	data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
	data["InstrumentID"] = task_data.InstrumentID;
	data["OptionSelfCloseSysID"] = task_data.OptionSelfCloseSysID;
	data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
	data["OptionSelfCloseActionRef"] = task_data.OptionSelfCloseActionRef;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["ActionDate"] = task_data.ActionDate;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["OptionSelfCloseLocalID"] = task_data.OptionSelfCloseLocalID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnOptionSelfCloseAction(data, error);
};

void TdApi::processRtnCombAction(Task task)
{
	PyLock lock;
	CThostFtdcCombActionField task_data = any_cast<CThostFtdcCombActionField>(task.task_data);
	dict data;
    data["ActionLocalID"] = boost::locale::conv::to_utf<char>(task_data.ActionLocalID, std::string("GB2312"));
    data["ActionStatus"] = task_data.ActionStatus;
    data["BranchID"] = task_data.BranchID;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ClientID"] = boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
    data["CombDirection"] = task_data.CombDirection;
    data["ComTradeID"] = task_data.ComTradeID;
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ExchangeInstID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeInstID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["HedgeFlag"] = task_data.HedgeFlag;
    data["InstallID"] = task_data.InstallID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["NotifySequence"] = task_data.NotifySequence;
    data["ParticipantID"] = boost::locale::conv::to_utf<char>(task_data.ParticipantID, std::string("GB2312"));
    data["SequenceNo"] = task_data.SequenceNo;
    data["SessionID"] = task_data.SessionID;
    data["SettlementID"] = task_data.SettlementID;
    data["StatusMsg"] = boost::locale::conv::to_utf<char>(task_data.StatusMsg, std::string("GB2312"));
    data["TraderID"] = boost::locale::conv::to_utf<char>(task_data.TraderID, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserProductInfo"] = boost::locale::conv::to_utf<char>(task_data.UserProductInfo, std::string("GB2312"));
    data["Volume"] = task_data.Volume;


	this->onRtnCombAction(data);
};

void TdApi::processErrRtnCombActionInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputCombActionField task_data = any_cast<CThostFtdcInputCombActionField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CombActionRef"] = boost::locale::conv::to_utf<char>(task_data.CombActionRef, std::string("GB2312"));
    data["CombDirection"] = task_data.CombDirection;
    data["Direction"] = task_data.Direction;
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["HedgeFlag"] = task_data.HedgeFlag;
   data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["Volume"] = task_data.Volume;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnCombActionInsert(data, error);
};

void TdApi::processRspQryContractBank(Task task)
{
	PyLock lock;
	CThostFtdcContractBankField task_data = any_cast<CThostFtdcContractBankField>(task.task_data);
	dict data;
	data["BankBrchID"] = boost::locale::conv::to_utf<char>(task_data.BankBrchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankName"] = boost::locale::conv::to_utf<char>(task_data.BankName, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryContractBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrder(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderField task_data = any_cast<CThostFtdcParkedOrderField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BusinessUnit"] = boost::locale::conv::to_utf<char>(task_data.BusinessUnit, std::string("GB2312"));
    data["ClientID"] =  boost::locale::conv::to_utf<char>(task_data.ClientID, std::string("GB2312"));
    data["CombHedgeFlag"] = boost::locale::conv::to_utf<char>(task_data.CombHedgeFlag, std::string("GB2312"));
    data["CombOffsetFlag"] = boost::locale::conv::to_utf<char>(task_data.CombOffsetFlag, std::string("GB2312"));
    data["ContingentCondition"] = task_data.ContingentCondition;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["Direction"] = task_data.Direction;
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["ForceCloseReason"] = task_data.ForceCloseReason;
    data["GTDDate"] = boost::locale::conv::to_utf<char>(task_data.GTDDate, std::string("GB2312"));
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["IsAutoSuspend"] = task_data.IsAutoSuspend;
    data["IsSwapOrder"] = task_data.IsSwapOrder;
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["MinVolume"] = task_data.MinVolume;
    data["OrderPriceType"] = task_data.OrderPriceType;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["ParkedOrderID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["Status"] = task_data.Status;
    data["StopPrice"] = task_data.StopPrice;
    data["TimeCondition"] = task_data.TimeCondition;
    data["UserForceClose"] = task_data.UserForceClose;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserType"] = task_data.UserType;
    data["VolumeCondition"] = task_data.VolumeCondition;
    data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryParkedOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryParkedOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcParkedOrderActionField task_data = any_cast<CThostFtdcParkedOrderActionField>(task.task_data);
	dict data;
    data["ActionFlag"] = task_data.ActionFlag;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["FrontID"] = task_data.FrontID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["IPAddress"] = boost::locale::conv::to_utf<char>(task_data.IPAddress, std::string("GB2312"));
    data["LimitPrice"] = task_data.LimitPrice;
    data["MacAddress"] = boost::locale::conv::to_utf<char>(task_data.MacAddress, std::string("GB2312"));
    data["OrderActionRef"] = task_data.OrderActionRef;
    data["OrderRef"] = boost::locale::conv::to_utf<char>(task_data.OrderRef, std::string("GB2312"));
    data["OrderSysID"] = boost::locale::conv::to_utf<char>(task_data.OrderSysID, std::string("GB2312"));
    data["ParkedOrderActionID"] = boost::locale::conv::to_utf<char>(task_data.ParkedOrderActionID, std::string("GB2312"));
    data["RequestID"] = task_data.RequestID;
    data["SessionID"] = task_data.SessionID;
    data["Status"] = task_data.Status;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["UserType"] = task_data.UserType;
    data["VolumeChange"] = task_data.VolumeChange;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryParkedOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingNotice(Task task)
{
	PyLock lock;
	CThostFtdcTradingNoticeField task_data = any_cast<CThostFtdcTradingNoticeField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["FieldContent"] = boost::locale::conv::to_utf<char>(task_data.FieldContent, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["InvestorRange"] = task_data.InvestorRange;
    data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));
    data["SendTime"] = boost::locale::conv::to_utf<char>(task_data.SendTime, std::string("GB2312"));
    data["SequenceNo"] = task_data.SequenceNo;
    data["SequenceSeries"] = task_data.SequenceSeries;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryTradingNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingParams(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingParamsField task_data = any_cast<CThostFtdcBrokerTradingParamsField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["Algorithm"] = task_data.Algorithm;
    data["AvailIncludeCloseProfit"] = task_data.AvailIncludeCloseProfit;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
    data["MarginPriceType"] = task_data.MarginPriceType;
    data["OptionRoyaltyPriceType"] = task_data.OptionRoyaltyPriceType;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryBrokerTradingParams(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBrokerTradingAlgos(Task task)
{
	PyLock lock;
	CThostFtdcBrokerTradingAlgosField task_data = any_cast<CThostFtdcBrokerTradingAlgosField>(task.task_data);
	dict data;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["ExchangeID"] = boost::locale::conv::to_utf<char>(task_data.ExchangeID, std::string("GB2312"));
    data["FindMarginRateAlgoID"] = task_data.FindMarginRateAlgoID;
    data["HandlePositionAlgoID"] = task_data.HandlePositionAlgoID;
    data["HandleTradingAccountAlgoID"] = task_data.HandleTradingAccountAlgoID;
    data["InstrumentID"] = boost::locale::conv::to_utf<char>(task_data.InstrumentID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQryBrokerTradingAlgos(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryCFMMCTradingAccountToken(Task task)
{
	PyLock lock;
	CThostFtdcQueryCFMMCTradingAccountTokenField task_data = any_cast<CThostFtdcQueryCFMMCTradingAccountTokenField>(task.task_data);
	dict data;
	data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
	data["InvestorID"] = boost::locale::conv::to_utf<char>(task_data.InvestorID, std::string("GB2312"));
	data["InvestUnitID"] = boost::locale::conv::to_utf<char>(task_data.InvestUnitID, std::string("GB2312"));

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQueryCFMMCTradingAccountToken(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = task_data.LongCustomerName;
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnFromBankToFutureByBank(data);
};

void TdApi::processRtnFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnFromFutureToBankByBank(data);
};

void TdApi::processRtnRepealFromBankToFutureByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
     data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnRepealFromBankToFutureByBank(data);
};

void TdApi::processRtnRepealFromFutureToBankByBank(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnRepealFromFutureToBankByBank(data);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnFromBankToFutureByFuture(data);
};

void TdApi::processRtnFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspTransferField task_data = any_cast<CThostFtdcRspTransferField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnFromFutureToBankByFuture(data);
};

void TdApi::processRtnRepealFromBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
   data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;

	this->onRtnRepealFromBankToFutureByFutureManual(data);
};

void TdApi::processRtnRepealFromFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] =  boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnRepealFromFutureToBankByFutureManual(data);
};

void TdApi::processRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcNotifyQueryAccountField task_data = any_cast<CThostFtdcNotifyQueryAccountField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankFetchAmount"] = task_data.BankFetchAmount;
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BankUseAmount"] = task_data.BankUseAmount;
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnQueryBankBalanceByFuture(data);
};

void TdApi::processErrRtnBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = data["Message"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnBankToFutureByFuture(data, error);
};

void TdApi::processErrRtnFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
   data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnFutureToBankByFuture(data, error);
};

void TdApi::processErrRtnRepealBankToFutureByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] =  boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnRepealBankToFutureByFutureManual(data, error);
};

void TdApi::processErrRtnRepealFutureToBankByFutureManual(Task task)
{
	PyLock lock;
	CThostFtdcReqRepealField task_data = any_cast<CThostFtdcReqRepealField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
   data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnRepealFutureToBankByFutureManual(data, error);
};

void TdApi::processErrRtnQueryBankBalanceByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
   data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onErrRtnQueryBankBalanceByFuture(data, error);
};

void TdApi::processRtnRepealFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnRepealFromBankToFutureByFuture(data);
};

void TdApi::processRtnRepealFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcRspRepealField task_data = any_cast<CThostFtdcRspRepealField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankRepealFlag"] = task_data.BankRepealFlag;
    data["BankRepealSerial"] = boost::locale::conv::to_utf<char>(task_data.BankRepealSerial, std::string("GB2312"));
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["BrokerRepealFlag"] = task_data.BrokerRepealFlag;
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureRepealSerial"] = task_data.FutureRepealSerial;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateRepealSerial"] = task_data.PlateRepealSerial;
    data["PlateSerial"] = task_data.PlateSerial;
    data["RepealedTimes"] = task_data.RepealedTimes;
    data["RepealTimeInterval"] = task_data.RepealTimeInterval;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	this->onRtnRepealFromFutureToBankByFuture(data);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspFromBankToFutureByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqTransferField task_data = any_cast<CThostFtdcReqTransferField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerFee"] = task_data.BrokerFee;
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustFee"] = task_data.CustFee;
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FeePayFlag"] = task_data.FeePayFlag;
    data["FutureFetchAmount"] = task_data.FutureFetchAmount;
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["Message"] = boost::locale::conv::to_utf<char>(task_data.Message, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeAmount"] = task_data.TradeAmount;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["TransferStatus"] = task_data.TransferStatus;
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;


	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspFromFutureToBankByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryBankAccountMoneyByFuture(Task task)
{
	PyLock lock;
	CThostFtdcReqQueryAccountField task_data = any_cast<CThostFtdcReqQueryAccountField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["FutureSerial"] = task_data.FutureSerial;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["RequestID"] = task_data.RequestID;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["TID"] = task_data.TID;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorID"] = task_error.ErrorID;
	error["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_error.ErrorMsg, std::string("GB2312"));

	this->onRspQueryBankAccountMoneyByFuture(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOpenAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcOpenAccountField task_data = any_cast<CThostFtdcOpenAccountField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CashExchangeCode"] = task_data.CashExchangeCode;
    data["CountryCode"] = boost::locale::conv::to_utf<char>(task_data.CountryCode, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["EMail"] = boost::locale::conv::to_utf<char>(task_data.EMail, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["Fax"] = boost::locale::conv::to_utf<char>(task_data.Fax, std::string("GB2312"));
    data["Gender"] = task_data.Gender;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["MobilePhone"] = boost::locale::conv::to_utf<char>(task_data.MobilePhone, std::string("GB2312"));
    data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));
    data["TID"] = task_data.TID;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
    data["ZipCode"] = boost::locale::conv::to_utf<char>(task_data.ZipCode, std::string("GB2312"));


	this->onRtnOpenAccountByBank(data);
};

void TdApi::processRtnCancelAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcCancelAccountField task_data = any_cast<CThostFtdcCancelAccountField>(task.task_data);
	dict data;
	data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSecuAcc"] = boost::locale::conv::to_utf<char>(task_data.BankSecuAcc, std::string("GB2312"));
    data["BankSecuAccType"] = task_data.BankSecuAccType;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CashExchangeCode"] = task_data.CashExchangeCode;
    data["CountryCode"] = boost::locale::conv::to_utf<char>(task_data.CountryCode, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["DeviceID"] = boost::locale::conv::to_utf<char>(task_data.DeviceID, std::string("GB2312"));
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["EMail"] = boost::locale::conv::to_utf<char>(task_data.EMail, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["Fax"] = boost::locale::conv::to_utf<char>(task_data.Fax, std::string("GB2312"));
    data["Gender"] = task_data.Gender;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] = boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["MobilePhone"] = boost::locale::conv::to_utf<char>(task_data.MobilePhone, std::string("GB2312"));
    data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
    data["OperNo"] = boost::locale::conv::to_utf<char>(task_data.OperNo, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));
    data["TID"] = task_data.TID;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["UserID"] = boost::locale::conv::to_utf<char>(task_data.UserID, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
    data["ZipCode"] = boost::locale::conv::to_utf<char>(task_data.ZipCode, std::string("GB2312"));


	this->onRtnCancelAccountByBank(data);
};

void TdApi::processRtnChangeAccountByBank(Task task)
{
	PyLock lock;
	CThostFtdcChangeAccountField task_data = any_cast<CThostFtdcChangeAccountField>(task.task_data);
	dict data;
    data["AccountID"] = boost::locale::conv::to_utf<char>(task_data.AccountID, std::string("GB2312"));
    data["Address"] = boost::locale::conv::to_utf<char>(task_data.Address, std::string("GB2312"));
    data["BankAccount"] = boost::locale::conv::to_utf<char>(task_data.BankAccount, std::string("GB2312"));
    data["BankAccType"] = task_data.BankAccType;
    data["BankBranchID"] = boost::locale::conv::to_utf<char>(task_data.BankBranchID, std::string("GB2312"));
    data["BankID"] = boost::locale::conv::to_utf<char>(task_data.BankID, std::string("GB2312"));
    data["BankPassWord"] = boost::locale::conv::to_utf<char>(task_data.BankPassWord, std::string("GB2312"));
    data["BankPwdFlag"] = task_data.BankPwdFlag;
    data["BankSerial"] = boost::locale::conv::to_utf<char>(task_data.BankSerial, std::string("GB2312"));
    data["BrokerBranchID"] = boost::locale::conv::to_utf<char>(task_data.BrokerBranchID, std::string("GB2312"));
    data["BrokerID"] = boost::locale::conv::to_utf<char>(task_data.BrokerID, std::string("GB2312"));
    data["BrokerIDByBank"] = boost::locale::conv::to_utf<char>(task_data.BrokerIDByBank, std::string("GB2312"));
    data["CountryCode"] = boost::locale::conv::to_utf<char>(task_data.CountryCode, std::string("GB2312"));
    data["CurrencyID"] = boost::locale::conv::to_utf<char>(task_data.CurrencyID, std::string("GB2312"));
    data["CustomerName"] = boost::locale::conv::to_utf<char>(task_data.CustomerName, std::string("GB2312"));
    data["CustType"] = task_data.CustType;
    data["Digest"] = boost::locale::conv::to_utf<char>(task_data.Digest, std::string("GB2312"));
    data["EMail"] = boost::locale::conv::to_utf<char>(task_data.EMail, std::string("GB2312"));
    data["ErrorID"] = task_data.ErrorID;
    data["ErrorMsg"] = boost::locale::conv::to_utf<char>(task_data.ErrorMsg, std::string("GB2312"));
    data["Fax"] = boost::locale::conv::to_utf<char>(task_data.Fax, std::string("GB2312"));
    data["Gender"] = task_data.Gender;
    data["IdCardType"] = task_data.IdCardType;
    data["IdentifiedCardNo"] = boost::locale::conv::to_utf<char>(task_data.IdentifiedCardNo, std::string("GB2312"));
    data["InstallID"] = task_data.InstallID;
    data["LastFragment"] = task_data.LastFragment;
    data["LongCustomerName"] =  boost::locale::conv::to_utf<char>(task_data.LongCustomerName, std::string("GB2312"));
    data["MobilePhone"] = boost::locale::conv::to_utf<char>(task_data.MobilePhone, std::string("GB2312"));
    data["MoneyAccountStatus"] = task_data.MoneyAccountStatus;
    data["NewBankAccount"] = boost::locale::conv::to_utf<char>(task_data.NewBankAccount, std::string("GB2312"));
    data["NewBankPassWord"] = boost::locale::conv::to_utf<char>(task_data.NewBankPassWord, std::string("GB2312"));
    data["Password"] = boost::locale::conv::to_utf<char>(task_data.Password, std::string("GB2312"));
    data["PlateSerial"] = task_data.PlateSerial;
    data["SecuPwdFlag"] = task_data.SecuPwdFlag;
    data["SessionID"] = task_data.SessionID;
    data["Telephone"] = boost::locale::conv::to_utf<char>(task_data.Telephone, std::string("GB2312"));
    data["TID"] = task_data.TID;
    data["TradeCode"] = boost::locale::conv::to_utf<char>(task_data.TradeCode, std::string("GB2312"));
    data["TradeDate"] = boost::locale::conv::to_utf<char>(task_data.TradeDate, std::string("GB2312"));
    data["TradeTime"] = boost::locale::conv::to_utf<char>(task_data.TradeTime, std::string("GB2312"));
    data["TradingDay"] = boost::locale::conv::to_utf<char>(task_data.TradingDay, std::string("GB2312"));
    data["VerifyCertNoFlag"] = task_data.VerifyCertNoFlag;
    data["ZipCode"] = boost::locale::conv::to_utf<char>(task_data.ZipCode, std::string("GB2312"));

	this->onRtnChangeAccountByBank(data);
};

///-------------------------------------------------------------------------------------
///��������
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	
	this->api = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
	cout << "Api Version:" << this->api->GetApiVersion() << " ------" << endl;
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
	//�ú�����ԭ��API��û�У����ڰ�ȫ�˳�API�ã�ԭ����join�ƺ���̫�ȶ�
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
	printf("TdApi:registerFont\n");
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void TdApi::subscribePrivateTopic(int nType)
{
	//�ú���Ϊ�ֶ���д
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
	//�ú���Ϊ�ֶ���д
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
	printf("reqAuthenticate\n");
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "AuthCode", myreq.AuthCode);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AppID", myreq.AppID);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	int i = this->api->ReqAuthenticate(&myreq, nRequestID);
	return i;
};


int TdApi::reqUserLogin(dict req, int nRequestID)
{
	
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	printf("reqUserLogin\n");
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "LoginRemark", myreq.LoginRemark);
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

int TdApi::reqUserAuthMethod(dict req, int nRequestID)
{
	CThostFtdcReqUserAuthMethodField myreq = CThostFtdcReqUserAuthMethodField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserAuthMethod(&myreq, nRequestID);
	return i;
};

int TdApi::reqGenUserCaptcha(dict req, int nRequestID)
{
	CThostFtdcReqGenUserCaptchaField myreq = CThostFtdcReqGenUserCaptchaField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqGenUserCaptcha(&myreq, nRequestID);
	return i;
};

int TdApi::reqGenUserText(dict req, int nRequestID)
{
	CThostFtdcReqGenUserTextField myreq = CThostFtdcReqGenUserTextField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "UserID", myreq.UserID);
	int i = this->api->ReqGenUserText(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLoginWithCaptcha(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginWithCaptchaField myreq = CThostFtdcReqUserLoginWithCaptchaField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "Captcha", myreq.Captcha);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "LoginRemark", myreq.LoginRemark);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	int i = this->api->ReqUserLoginWithCaptcha(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLoginWithText(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginWithTextField myreq = CThostFtdcReqUserLoginWithTextField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "Text", myreq.Text);
	getStr(req, "LoginRemark", myreq.LoginRemark);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	int i = this->api->ReqUserLoginWithText(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLoginWithOTP(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginWithOTPField myreq = CThostFtdcReqUserLoginWithOTPField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getInt(req, "ClientIPPort", &myreq.ClientIPPort);
	getStr(req, "LoginRemark", myreq.LoginRemark);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	getStr(req, "OTPPassword", myreq.OTPPassword);
	int i = this->api->ReqUserLoginWithOTP(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "AccountID", myreq.AccountID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getStr(req, "ClientID", myreq.ClientID);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "IPAddress", myreq.IPAddress);
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
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "AccountID", myreq.AccountID);
	getChar(req, "Status", &myreq.Status);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getChar(req, "UserType", &myreq.UserType);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getStr(req, "ClientID", myreq.ClientID);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getStr(req, "IPAddress", myreq.IPAddress);
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
	getStr(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getStr(req, "ParkedOrderActionID", myreq.ParkedOrderActionID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getChar(req, "Status", &myreq.Status);
	getStr(req, "MacAddress", myreq.MacAddress);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "UserType", &myreq.UserType);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "IPAddress", myreq.IPAddress);
	getInt(req, "ErrorID", &myreq.ErrorID);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "OrderSysID", myreq.OrderSysID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ErrorMsg", myreq.ErrorMsg);
	getStr(req, "OrderRef", myreq.OrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "MacAddress", myreq.MacAddress);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQueryMaxOrderVolume(&myreq, nRequestID);
	return i;
};

int TdApi::reqSettlementInfoConfirm(dict req, int nRequestID)
{
	CThostFtdcSettlementInfoConfirmField myreq = CThostFtdcSettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SettlementID", &myreq.SettlementID);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ConfirmDate", myreq.ConfirmDate);
	getStr(req, "ConfirmTime", myreq.ConfirmTime);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqSettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqRemoveParkedOrder(dict req, int nRequestID)
{
	CThostFtdcRemoveParkedOrderField myreq = CThostFtdcRemoveParkedOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "PosiDirection", &myreq.PosiDirection);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ClientID", myreq.ClientID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionType", &myreq.ActionType);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "ReservePositionFlag", &myreq.ReservePositionFlag);
	getStr(req, "AccountID", myreq.AccountID);
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
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExecOrderRef", myreq.ExecOrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "ExecOrderActionRef", &myreq.ExecOrderActionRef);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
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
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqForQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteInsert(dict req, int nRequestID)
{
	CThostFtdcInputQuoteField myreq = CThostFtdcInputQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "AskHedgeFlag", &myreq.AskHedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "AskVolume", &myreq.AskVolume);
	getStr(req, "BidOrderRef", myreq.BidOrderRef);
	getChar(req, "BidHedgeFlag", &myreq.BidHedgeFlag);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "AskOffsetFlag", &myreq.AskOffsetFlag);
	getStr(req, "ClientID", myreq.ClientID);
	getChar(req, "BidOffsetFlag", &myreq.BidOffsetFlag);
	getDouble(req, "BidPrice", &myreq.BidPrice);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "BidVolume", &myreq.BidVolume);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getDouble(req, "AskPrice", &myreq.AskPrice);
	getStr(req, "AskOrderRef", myreq.AskOrderRef);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "ForQuoteSysID", myreq.ForQuoteSysID);
	int i = this->api->ReqQuoteInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQuoteAction(dict req, int nRequestID)
{
	CThostFtdcInputQuoteActionField myreq = CThostFtdcInputQuoteActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "QuoteActionRef", &myreq.QuoteActionRef);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ClientID", myreq.ClientID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "QuoteSysID", myreq.QuoteSysID);
	getStr(req, "QuoteRef", myreq.QuoteRef);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQuoteAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqBatchOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputBatchOrderActionField myreq = CThostFtdcInputBatchOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqBatchOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqOptionSelfCloseInsert(dict req, int nRequestID)
{
	CThostFtdcInputOptionSelfCloseField myreq = CThostFtdcInputOptionSelfCloseField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "OptSelfCloseFlag", &myreq.OptSelfCloseFlag);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ClientID", myreq.ClientID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getStr(req, "OptionSelfCloseRef", myreq.OptionSelfCloseRef);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqOptionSelfCloseInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOptionSelfCloseAction(dict req, int nRequestID)
{
	CThostFtdcInputOptionSelfCloseActionField myreq = CThostFtdcInputOptionSelfCloseActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "OptionSelfCloseSysID", myreq.OptionSelfCloseSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "OptionSelfCloseActionRef", &myreq.OptionSelfCloseActionRef);
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getStr(req, "OptionSelfCloseRef", myreq.OptionSelfCloseRef);
	getInt(req, "FrontID", &myreq.FrontID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqOptionSelfCloseAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqCombActionInsert(dict req, int nRequestID)
{
	CThostFtdcInputCombActionField myreq = CThostFtdcInputCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "MacAddress", myreq.MacAddress);
	getChar(req, "Direction", &myreq.Direction);
	getStr(req, "CombActionRef", myreq.CombActionRef);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "Volume", &myreq.Volume);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getStr(req, "IPAddress", myreq.IPAddress);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "AccountID", myreq.AccountID);
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
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ClientID", myreq.ClientID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getChar(req, "ClientIDType", &myreq.ClientIDType);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentMarginRateField myreq = CThostFtdcQryInstrumentMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "AccountID", myreq.AccountID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQrySettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionCombineDetail(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionCombineDetailField myreq = CThostFtdcQryInvestorPositionCombineDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryEWarrantOffset(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorProductGroupMargin(dict req, int nRequestID)
{
	CThostFtdcQryInvestorProductGroupMarginField myreq = CThostFtdcQryInvestorProductGroupMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "ProductGroupID", myreq.ProductGroupID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryInvestorProductGroupMargin(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchangeMarginRate(dict req, int nRequestID)
{
	CThostFtdcQryExchangeMarginRateField myreq = CThostFtdcQryExchangeMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getStr(req, "ExchangeID", myreq.ExchangeID);
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
	getStr(req, "ExchangeID", myreq.ExchangeID);
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

int TdApi::reqQryMMInstrumentCommissionRate(dict req, int nRequestID)
{
	CThostFtdcQryMMInstrumentCommissionRateField myreq = CThostFtdcQryMMInstrumentCommissionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryMMInstrumentCommissionRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryMMOptionInstrCommRate(dict req, int nRequestID)
{
	CThostFtdcQryMMOptionInstrCommRateField myreq = CThostFtdcQryMMOptionInstrCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryMMOptionInstrCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentOrderCommRate(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentOrderCommRateField myreq = CThostFtdcQryInstrumentOrderCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInstrumentOrderCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "CurrencyID", myreq.CurrencyID);
	getStr(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BizType", &myreq.BizType);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQrySecAgentTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentCheckMode(dict req, int nRequestID)
{
	CThostFtdcQrySecAgentCheckModeField myreq = CThostFtdcQrySecAgentCheckModeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQrySecAgentCheckMode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySecAgentTradeInfo(dict req, int nRequestID)
{
	CThostFtdcQrySecAgentTradeInfoField myreq = CThostFtdcQrySecAgentTradeInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "BrokerSecAgentID", myreq.BrokerSecAgentID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQrySecAgentTradeInfo(&myreq, nRequestID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryQuote(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOptionSelfClose(dict req, int nRequestID)
{
	CThostFtdcQryOptionSelfCloseField myreq = CThostFtdcQryOptionSelfCloseField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "OptionSelfCloseSysID", myreq.OptionSelfCloseSysID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	getStr(req, "InsertTimeStart", myreq.InsertTimeStart);
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOptionSelfClose(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestUnit(dict req, int nRequestID)
{
	CThostFtdcQryInvestUnitField myreq = CThostFtdcQryInvestUnitField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestUnit(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombInstrumentGuard(dict req, int nRequestID)
{
	CThostFtdcQryCombInstrumentGuardField myreq = CThostFtdcQryCombInstrumentGuardField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
	int i = this->api->ReqQryParkedOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingNotice(dict req, int nRequestID)
{
	CThostFtdcQryTradingNoticeField myreq = CThostFtdcQryTradingNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InvestorID", myreq.InvestorID);
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "AccountID", myreq.AccountID);
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
	getStr(req, "InvestUnitID", myreq.InvestUnitID);
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
	getStr(req, "LongCustomerName", myreq.LongCustomerName);
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
	getStr(req, "LongCustomerName", myreq.LongCustomerName);
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
	getStr(req, "LongCustomerName", myreq.LongCustomerName);
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
///Boost.Python��װ
///-------------------------------------------------------------------------------------

struct TdApiWrap : TdApi, wrapper < TdApi >
{
	virtual void onFrontConnected()
	{
		
		//����python�����е��ûص�������������ǰ����Ҫ�Ȼ�ȡȫ����GIL����ֹ����������
		PyLock lock;
		printf("TdApiWrap:onFrontConnected\n");

		//���µ�try...catch...����ʵ�ֲ�׽python�����д���Ĺ��ܣ���ֹC++ֱ�ӳ���ԭ��δ֪�ı���
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
			printf("TdApiWrap: OnRspAuthenticate\n");
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

	virtual void onRspUserAuthMethod(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspUserAuthMethod")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspGenUserCaptcha(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspGenUserCaptcha")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspGenUserText(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspGenUserText")(data, error, id, last);
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

	virtual void onRspBatchOrderAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspBatchOrderAction")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspOptionSelfCloseInsert(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspOptionSelfCloseInsert")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspOptionSelfCloseAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspOptionSelfCloseAction")(data, error, id, last);
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

	virtual void onRspQryMMInstrumentCommissionRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryMMInstrumentCommissionRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryMMOptionInstrCommRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryMMOptionInstrCommRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInstrumentOrderCommRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInstrumentOrderCommRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySecAgentTradingAccount(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySecAgentTradingAccount")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySecAgentCheckMode(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySecAgentCheckMode")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySecAgentTradeInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySecAgentTradeInfo")(data, error, id, last);
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

	virtual void onRspQryOptionSelfClose(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOptionSelfClose")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestUnit(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestUnit")(data, error, id, last);
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

	virtual void onRtnBulletin(dict data)
	{
		try
		{
			this->get_override("onRtnBulletin")(data);
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

	virtual void onErrRtnBatchOrderAction(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnBatchOrderAction")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnOptionSelfClose(dict data)
	{
		try
		{
			this->get_override("onRtnOptionSelfClose")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnOptionSelfCloseInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnOptionSelfCloseInsert")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnOptionSelfCloseAction(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnOptionSelfCloseAction")(data, error);
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
	PyEval_InitThreads();	//����ʱ���У���֤�ȴ���GIL

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
		.def("reqUserAuthMethod", &TdApiWrap::reqUserAuthMethod)
		.def("reqGenUserCaptcha", &TdApiWrap::reqGenUserCaptcha)
		.def("reqGenUserText", &TdApiWrap::reqGenUserText)
		.def("reqUserLoginWithCaptcha", &TdApiWrap::reqUserLoginWithCaptcha)
		.def("reqUserLoginWithText", &TdApiWrap::reqUserLoginWithText)
		.def("reqUserLoginWithOTP", &TdApiWrap::reqUserLoginWithOTP)
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
		.def("reqBatchOrderAction", &TdApiWrap::reqBatchOrderAction)
		.def("reqOptionSelfCloseInsert", &TdApiWrap::reqOptionSelfCloseInsert)
		.def("reqOptionSelfCloseAction", &TdApiWrap::reqOptionSelfCloseAction)
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
		.def("reqQryMMInstrumentCommissionRate", &TdApiWrap::reqQryMMInstrumentCommissionRate)
		.def("reqQryMMOptionInstrCommRate", &TdApiWrap::reqQryMMOptionInstrCommRate)
		.def("reqQryInstrumentOrderCommRate", &TdApiWrap::reqQryInstrumentOrderCommRate)
		.def("reqQrySecAgentTradingAccount", &TdApiWrap::reqQrySecAgentTradingAccount)
		.def("reqQrySecAgentCheckMode", &TdApiWrap::reqQrySecAgentCheckMode)
		.def("reqQrySecAgentTradeInfo", &TdApiWrap::reqQrySecAgentTradeInfo)
		.def("reqQryOptionInstrTradeCost", &TdApiWrap::reqQryOptionInstrTradeCost)
		.def("reqQryOptionInstrCommRate", &TdApiWrap::reqQryOptionInstrCommRate)
		.def("reqQryExecOrder", &TdApiWrap::reqQryExecOrder)
		.def("reqQryForQuote", &TdApiWrap::reqQryForQuote)
		.def("reqQryQuote", &TdApiWrap::reqQryQuote)
		.def("reqQryOptionSelfClose", &TdApiWrap::reqQryOptionSelfClose)
		.def("reqQryInvestUnit", &TdApiWrap::reqQryInvestUnit)
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
		.def("onRspUserAuthMethod", pure_virtual(&TdApiWrap::onRspUserAuthMethod))
		.def("onRspGenUserCaptcha", pure_virtual(&TdApiWrap::onRspGenUserCaptcha))
		.def("onRspGenUserText", pure_virtual(&TdApiWrap::onRspGenUserText))
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
		.def("onRspBatchOrderAction", pure_virtual(&TdApiWrap::onRspBatchOrderAction))
		.def("onRspOptionSelfCloseInsert", pure_virtual(&TdApiWrap::onRspOptionSelfCloseInsert))
		.def("onRspOptionSelfCloseAction", pure_virtual(&TdApiWrap::onRspOptionSelfCloseAction))
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
		.def("onRspQryMMInstrumentCommissionRate", pure_virtual(&TdApiWrap::onRspQryMMInstrumentCommissionRate))
		.def("onRspQryMMOptionInstrCommRate", pure_virtual(&TdApiWrap::onRspQryMMOptionInstrCommRate))
		.def("onRspQryInstrumentOrderCommRate", pure_virtual(&TdApiWrap::onRspQryInstrumentOrderCommRate))
		.def("onRspQrySecAgentTradingAccount", pure_virtual(&TdApiWrap::onRspQrySecAgentTradingAccount))
		.def("onRspQrySecAgentCheckMode", pure_virtual(&TdApiWrap::onRspQrySecAgentCheckMode))
		.def("onRspQrySecAgentTradeInfo", pure_virtual(&TdApiWrap::onRspQrySecAgentTradeInfo))
		.def("onRspQryOptionInstrTradeCost", pure_virtual(&TdApiWrap::onRspQryOptionInstrTradeCost))
		.def("onRspQryOptionInstrCommRate", pure_virtual(&TdApiWrap::onRspQryOptionInstrCommRate))
		.def("onRspQryExecOrder", pure_virtual(&TdApiWrap::onRspQryExecOrder))
		.def("onRspQryForQuote", pure_virtual(&TdApiWrap::onRspQryForQuote))
		.def("onRspQryQuote", pure_virtual(&TdApiWrap::onRspQryQuote))
		.def("onRspQryOptionSelfClose", pure_virtual(&TdApiWrap::onRspQryOptionSelfClose))
		.def("onRspQryInvestUnit", pure_virtual(&TdApiWrap::onRspQryInvestUnit))
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
		.def("onRtnBulletin", pure_virtual(&TdApiWrap::onRtnBulletin))
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
		.def("onErrRtnBatchOrderAction", pure_virtual(&TdApiWrap::onErrRtnBatchOrderAction))
		.def("onRtnOptionSelfClose", pure_virtual(&TdApiWrap::onRtnOptionSelfClose))
		.def("onErrRtnOptionSelfCloseInsert", pure_virtual(&TdApiWrap::onErrRtnOptionSelfCloseInsert))
		.def("onErrRtnOptionSelfCloseAction", pure_virtual(&TdApiWrap::onErrRtnOptionSelfCloseAction))
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
