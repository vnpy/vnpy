// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnksotptd.h"



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

void TdApi::OnRspError(CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CKSOTPRspUserLoginField empty_data = CKSOTPRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(CKSOTPUserLogoutField *pUserLogout, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pUserLogout)
	{
		task.task_data = *pUserLogout;
	}
	else
	{
		CKSOTPUserLogoutField empty_data = CKSOTPUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserPasswordUpdate(CKSOTPUserPasswordUpdateField *pUserPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;

	if (pUserPasswordUpdate)
	{
		task.task_data = *pUserPasswordUpdate;
	}
	else
	{
		CKSOTPUserPasswordUpdateField empty_data = CKSOTPUserPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspTradingAccountPasswordUpdate(CKSOTPTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGACCOUNTPASSWORDUPDATE;

	if (pTradingAccountPasswordUpdate)
	{
		task.task_data = *pTradingAccountPasswordUpdate;
	}
	else
	{
		CKSOTPTradingAccountPasswordUpdateField empty_data = CKSOTPTradingAccountPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CKSOTPInputOrderField *pInputOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CKSOTPInputOrderField empty_data = CKSOTPInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CKSOTPInputOrderActionField *pInputOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;

	if (pInputOrderAction)
	{
		task.task_data = *pInputOrderAction;
	}
	else
	{
		CKSOTPInputOrderActionField empty_data = CKSOTPInputOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CKSOTPOrderField *pOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CKSOTPOrderField empty_data = CKSOTPOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CKSOTPTradeField *pTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CKSOTPTradeField empty_data = CKSOTPTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CKSOTPInvestorPositionField *pInvestorPosition, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;

	if (pInvestorPosition)
	{
		task.task_data = *pInvestorPosition;
	}
	else
	{
		CKSOTPInvestorPositionField empty_data = CKSOTPInvestorPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingAccount(CKSOTPTradingAccountField *pTradingAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGACCOUNT;

	if (pTradingAccount)
	{
		task.task_data = *pTradingAccount;
	}
	else
	{
		CKSOTPTradingAccountField empty_data = CKSOTPTradingAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestor(CKSOTPInvestorField *pInvestor, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTOR;

	if (pInvestor)
	{
		task.task_data = *pInvestor;
	}
	else
	{
		CKSOTPInvestorField empty_data = CKSOTPInvestorField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingCode(CKSOTPTradingCodeField *pTradingCode, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGCODE;

	if (pTradingCode)
	{
		task.task_data = *pTradingCode;
	}
	else
	{
		CKSOTPTradingCodeField empty_data = CKSOTPTradingCodeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchange(CKSOTPExchangeField *pExchange, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;

	if (pExchange)
	{
		task.task_data = *pExchange;
	}
	else
	{
		CKSOTPExchangeField empty_data = CKSOTPExchangeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrument(CKSOTPInstrumentField *pInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;

	if (pInstrument)
	{
		task.task_data = *pInstrument;
	}
	else
	{
		CKSOTPInstrumentField empty_data = CKSOTPInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPositionDetail(CKSOTPInvestorPositionDetailField *pInvestorPositionDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITIONDETAIL;

	if (pInvestorPositionDetail)
	{
		task.task_data = *pInvestorPositionDetail;
	}
	else
	{
		CKSOTPInvestorPositionDetailField empty_data = CKSOTPInvestorPositionDetailField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingNotice(CKSOTPTradingNoticeField *pTradingNotice, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGNOTICE;

	if (pTradingNotice)
	{
		task.task_data = *pTradingNotice;
	}
	else
	{
		CKSOTPTradingNoticeField empty_data = CKSOTPTradingNoticeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspExecOrderInsert(CKSOTPInputExecOrderField *pInputExecOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERINSERT;

	if (pInputExecOrder)
	{
		task.task_data = *pInputExecOrder;
	}
	else
	{
		CKSOTPInputExecOrderField empty_data = CKSOTPInputExecOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspLockInsert(CKSOTPInputLockField *pInputLock, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPLOCKINSERT;

	if (pInputLock)
	{
		task.task_data = *pInputLock;
	}
	else
	{
		CKSOTPInputLockField empty_data = CKSOTPInputLockField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspExecOrderAction(CKSOTPInputExecOrderActionField *pInputExecOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPEXECORDERACTION;

	if (pInputExecOrderAction)
	{
		task.task_data = *pInputExecOrderAction;
	}
	else
	{
		CKSOTPInputExecOrderActionField empty_data = CKSOTPInputExecOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExecOrder(CKSOTPExecOrderField *pExecOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXECORDER;

	if (pExecOrder)
	{
		task.task_data = *pExecOrder;
	}
	else
	{
		CKSOTPExecOrderField empty_data = CKSOTPExecOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExecOrderVolume(CKSOTPExecOrderVolumeField *pExecOrderVolume, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXECORDERVOLUME;

	if (pExecOrderVolume)
	{
		task.task_data = *pExecOrderVolume;
	}
	else
	{
		CKSOTPExecOrderVolumeField empty_data = CKSOTPExecOrderVolumeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryLock(CKSOTPLockField *pLock, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYLOCK;

	if (pLock)
	{
		task.task_data = *pLock;
	}
	else
	{
		CKSOTPLockField empty_data = CKSOTPLockField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryLockPosition(CKSOTPLockPositionField *pLockPosition, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYLOCKPOSITION;

	if (pLockPosition)
	{
		task.task_data = *pLockPosition;
	}
	else
	{
		CKSOTPLockPositionField empty_data = CKSOTPLockPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryUnderlyingStockInfo(CKSOTPUnderlyingStockInfoField *pUnderlyingStockInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYUNDERLYINGSTOCKINFO;

	if (pUnderlyingStockInfo)
	{
		task.task_data = *pUnderlyingStockInfo;
	}
	else
	{
		CKSOTPUnderlyingStockInfoField empty_data = CKSOTPUnderlyingStockInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOTPInsCommRate(CKSOTPOTPInsCommRateField *pOTPInsCommRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYOTPINSCOMMRATE;

	if (pOTPInsCommRate)
	{
		task.task_data = *pOTPInsCommRate;
	}
	else
	{
		CKSOTPOTPInsCommRateField empty_data = CKSOTPOTPInsCommRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrumentMarginRate(CKSOTPInstrumentMarginRateField *pInstrumentMarginRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTMARGINRATE;

	if (pInstrumentMarginRate)
	{
		task.task_data = *pInstrumentMarginRate;
	}
	else
	{
		CKSOTPInstrumentMarginRateField empty_data = CKSOTPInstrumentMarginRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOTPAssignment(CKSOTPOTPAssignmentField *pOTPAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYOTPASSIGNMENT;

	if (pOTPAssignment)
	{
		task.task_data = *pOTPAssignment;
	}
	else
	{
		CKSOTPOTPAssignmentField empty_data = CKSOTPOTPAssignmentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryDepthMarketData(CKSOTPDepthMarketDataField *pDepthMarketData, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYDEPTHMARKETDATA;

	if (pDepthMarketData)
	{
		task.task_data = *pDepthMarketData;
	}
	else
	{
		CKSOTPDepthMarketDataField empty_data = CKSOTPDepthMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFromBankToStockByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFROMBANKTOSTOCKBYSTOCK;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CKSOTPReqTransferField empty_data = CKSOTPReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnFromBankToStockByStock(CKSOTPRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMBANKTOSTOCKBYSTOCK;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CKSOTPRspTransferField empty_data = CKSOTPRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFromStockToBankByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFROMSTOCKTOBANKBYSTOCK;

	if (pReqTransfer)
	{
		task.task_data = *pReqTransfer;
	}
	else
	{
		CKSOTPReqTransferField empty_data = CKSOTPReqTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnFromStockToBankByStock(CKSOTPRspTransferField *pRspTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFROMSTOCKTOBANKBYSTOCK;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		CKSOTPRspTransferField empty_data = CKSOTPRspTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQueryBankBalanceByStock(CKSOTPNotifyQueryAccountField *pNotifyQueryAccount)
{
	Task task = Task();
	task.task_name = ONRTNQUERYBANKBALANCEBYSTOCK;

	if (pNotifyQueryAccount)
	{
		task.task_data = *pNotifyQueryAccount;
	}
	else
	{
		CKSOTPNotifyQueryAccountField empty_data = CKSOTPNotifyQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryContractBank(CKSOTPContractBankField *pContractBank, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACTBANK;

	if (pContractBank)
	{
		task.task_data = *pContractBank;
	}
	else
	{
		CKSOTPContractBankField empty_data = CKSOTPContractBankField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQueryBankAccountMoneyByStock(CKSOTPReqQueryAccountField *pReqQueryAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQUERYBANKACCOUNTMONEYBYSTOCK;

	if (pReqQueryAccount)
	{
		task.task_data = *pReqQueryAccount;
	}
	else
	{
		CKSOTPReqQueryAccountField empty_data = CKSOTPReqQueryAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTransferSerial(CKSOTPTransferSerialField *pTransferSerial, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERSERIAL;

	if (pTransferSerial)
	{
		task.task_data = *pTransferSerial;
	}
	else
	{
		CKSOTPTransferSerialField empty_data = CKSOTPTransferSerialField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQrySettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSETTLEMENTINFOCONFIRM;

	if (pSettlementInfoConfirm)
	{
		task.task_data = *pSettlementInfoConfirm;
	}
	else
	{
		CKSOTPSettlementInfoConfirmField empty_data = CKSOTPSettlementInfoConfirmField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSETTLEMENTINFOCONFIRM;

	if (pSettlementInfoConfirm)
	{
		task.task_data = *pSettlementInfoConfirm;
	}
	else
	{
		CKSOTPSettlementInfoConfirmField empty_data = CKSOTPSettlementInfoConfirmField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQrySettlementInfo(CKSOTPSettlementInfoField *pSettlementInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSETTLEMENTINFO;

	if (pSettlementInfo)
	{
		task.task_data = *pSettlementInfo;
	}
	else
	{
		CKSOTPSettlementInfoField empty_data = CKSOTPSettlementInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorTradeLevel(CKSOTPInvestorTradeLevelField *pInvestorTradeLevel, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORTRADELEVEL;

	if (pInvestorTradeLevel)
	{
		task.task_data = *pInvestorTradeLevel;
	}
	else
	{
		CKSOTPInvestorTradeLevelField empty_data = CKSOTPInvestorTradeLevelField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryPurchaseLimitAmt(CKSOTPPurchaseLimitAmtField *pPurchaseLimitAmt, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPURCHASELIMITAMT;

	if (pPurchaseLimitAmt)
	{
		task.task_data = *pPurchaseLimitAmt;
	}
	else
	{
		CKSOTPPurchaseLimitAmtField empty_data = CKSOTPPurchaseLimitAmtField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryPositionLimitVol(CKSOTPPositionLimitVolField *pPositionLimitVol, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITIONLIMITVOL;

	if (pPositionLimitVol)
	{
		task.task_data = *pPositionLimitVol;
	}
	else
	{
		CKSOTPPositionLimitVolField empty_data = CKSOTPPositionLimitVolField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryHistoryOrder(CKSOTPHistoryOrderField *pHistoryOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISTORYORDER;

	if (pHistoryOrder)
	{
		task.task_data = *pHistoryOrder;
	}
	else
	{
		CKSOTPHistoryOrderField empty_data = CKSOTPHistoryOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryHistoryTrade(CKSOTPHistoryTradeField *pHistoryTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISTORYTRADE;

	if (pHistoryTrade)
	{
		task.task_data = *pHistoryTrade;
	}
	else
	{
		CKSOTPHistoryTradeField empty_data = CKSOTPHistoryTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryHistoryAssignment(CKSOTPHistoryAssignmentField *pHistoryAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISTORYASSIGNMENT;

	if (pHistoryAssignment)
	{
		task.task_data = *pHistoryAssignment;
	}
	else
	{
		CKSOTPHistoryAssignmentField empty_data = CKSOTPHistoryAssignmentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryDelivDetail(CKSOTPDelivDetailField *pDelivDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYDELIVDETAIL;

	if (pDelivDetail)
	{
		task.task_data = *pDelivDetail;
	}
	else
	{
		CKSOTPDelivDetailField empty_data = CKSOTPDelivDetailField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspAutoExecOrderAction(CKSOTPAutoExecOrderActionField *pAutoExecOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPAUTOEXECORDERACTION;

	if (pAutoExecOrderAction)
	{
		task.task_data = *pAutoExecOrderAction;
	}
	else
	{
		CKSOTPAutoExecOrderActionField empty_data = CKSOTPAutoExecOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspCombActionInsert(CKSOTPInputCombActionField *pInputCombAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPCOMBACTIONINSERT;

	if (pInputCombAction)
	{
		task.task_data = *pInputCombAction;
	}
	else
	{
		CKSOTPInputCombActionField empty_data = CKSOTPInputCombActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorCombinePosition(CKSOTPInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORCOMBINEPOSITION;

	if (pInvestorPositionCombineDetail)
	{
		task.task_data = *pInvestorPositionCombineDetail;
	}
	else
	{
		CKSOTPInvestorPositionCombineDetailField empty_data = CKSOTPInvestorPositionCombineDetailField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryCombActionVolume(CKSOTPCombActionVolumeField *pCombActionVolume, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMBACTIONVOLUME;

	if (pCombActionVolume)
	{
		task.task_data = *pCombActionVolume;
	}
	else
	{
		CKSOTPCombActionVolumeField empty_data = CKSOTPCombActionVolumeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFundOutCreditApply(CKSOTPInputFundOutCreditApplyField *pFundOutCreditApply, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFUNDOUTCREDITAPPLY;

	if (pFundOutCreditApply)
	{
		task.task_data = *pFundOutCreditApply;
	}
	else
	{
		CKSOTPInputFundOutCreditApplyField empty_data = CKSOTPInputFundOutCreditApplyField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryFundOutCredit(CKSOTPRspQryFundOutCreditField *pRspQryFundOutCredit, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUNDOUTCREDIT;

	if (pRspQryFundOutCredit)
	{
		task.task_data = *pRspQryFundOutCredit;
	}
	else
	{
		CKSOTPRspQryFundOutCreditField empty_data = CKSOTPRspQryFundOutCreditField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryFundOutCreditApply(CKSOTPRspQryFundOutCreditApplyField *pRspQryFundOutCreditApply, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUNDOUTCREDITAPPLY;

	if (pRspQryFundOutCreditApply)
	{
		task.task_data = *pRspQryFundOutCreditApply;
	}
	else
	{
		CKSOTPRspQryFundOutCreditApplyField empty_data = CKSOTPRspQryFundOutCreditApplyField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CKSOTPRspInfoField empty_error = CKSOTPRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CKSOTPOrderField *pOrder)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CKSOTPOrderField empty_data = CKSOTPOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CKSOTPTradeField *pTrade)
{
	Task task = Task();
	task.task_name = ONRTNTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CKSOTPTradeField empty_data = CKSOTPTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnExecOrder(CKSOTPExecOrderField *pExecOrder)
{
	Task task = Task();
	task.task_name = ONRTNEXECORDER;

	if (pExecOrder)
	{
		task.task_data = *pExecOrder;
	}
	else
	{
		CKSOTPExecOrderField empty_data = CKSOTPExecOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnLock(CKSOTPLockField *pLock)
{
	Task task = Task();
	task.task_name = ONRTNLOCK;

	if (pLock)
	{
		task.task_data = *pLock;
	}
	else
	{
		CKSOTPLockField empty_data = CKSOTPLockField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CKSOTPInstrumentStatusField *pInstrumentStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;

	if (pInstrumentStatus)
	{
		task.task_data = *pInstrumentStatus;
	}
	else
	{
		CKSOTPInstrumentStatusField empty_data = CKSOTPInstrumentStatusField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTradingNotice(CKSOTPTradingNoticeInfoField *pTradingNoticeInfo)
{
	Task task = Task();
	task.task_name = ONRTNTRADINGNOTICE;

	if (pTradingNoticeInfo)
	{
		task.task_data = *pTradingNoticeInfo;
	}
	else
	{
		CKSOTPTradingNoticeInfoField empty_data = CKSOTPTradingNoticeInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnCombAction(CKSOTPCombActionField *pCombAction)
{
	Task task = Task();
	task.task_name = ONRTNCOMBACTION;

	if (pCombAction)
	{
		task.task_data = *pCombAction;
	}
	else
	{
		CKSOTPCombActionField empty_data = CKSOTPCombActionField();
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

		case ONRSPORDERACTION:
		{
			this->processRspOrderAction(task);
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

		case ONRSPQRYEXCHANGE:
		{
			this->processRspQryExchange(task);
			break;
		}

		case ONRSPQRYINSTRUMENT:
		{
			this->processRspQryInstrument(task);
			break;
		}

		case ONRSPQRYINVESTORPOSITIONDETAIL:
		{
			this->processRspQryInvestorPositionDetail(task);
			break;
		}

		case ONRSPQRYTRADINGNOTICE:
		{
			this->processRspQryTradingNotice(task);
			break;
		}

		case ONRSPEXECORDERINSERT:
		{
			this->processRspExecOrderInsert(task);
			break;
		}

		case ONRSPLOCKINSERT:
		{
			this->processRspLockInsert(task);
			break;
		}

		case ONRSPEXECORDERACTION:
		{
			this->processRspExecOrderAction(task);
			break;
		}

		case ONRSPQRYEXECORDER:
		{
			this->processRspQryExecOrder(task);
			break;
		}

		case ONRSPQRYEXECORDERVOLUME:
		{
			this->processRspQryExecOrderVolume(task);
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

		case ONRSPQRYUNDERLYINGSTOCKINFO:
		{
			this->processRspQryUnderlyingStockInfo(task);
			break;
		}

		case ONRSPQRYOTPINSCOMMRATE:
		{
			this->processRspQryOTPInsCommRate(task);
			break;
		}

		case ONRSPQRYINSTRUMENTMARGINRATE:
		{
			this->processRspQryInstrumentMarginRate(task);
			break;
		}

		case ONRSPQRYOTPASSIGNMENT:
		{
			this->processRspQryOTPAssignment(task);
			break;
		}

		case ONRSPQRYDEPTHMARKETDATA:
		{
			this->processRspQryDepthMarketData(task);
			break;
		}

		case ONRSPFROMBANKTOSTOCKBYSTOCK:
		{
			this->processRspFromBankToStockByStock(task);
			break;
		}

		case ONRTNFROMBANKTOSTOCKBYSTOCK:
		{
			this->processRtnFromBankToStockByStock(task);
			break;
		}

		case ONRSPFROMSTOCKTOBANKBYSTOCK:
		{
			this->processRspFromStockToBankByStock(task);
			break;
		}

		case ONRTNFROMSTOCKTOBANKBYSTOCK:
		{
			this->processRtnFromStockToBankByStock(task);
			break;
		}

		case ONRTNQUERYBANKBALANCEBYSTOCK:
		{
			this->processRtnQueryBankBalanceByStock(task);
			break;
		}

		case ONRSPQRYCONTRACTBANK:
		{
			this->processRspQryContractBank(task);
			break;
		}

		case ONRSPQUERYBANKACCOUNTMONEYBYSTOCK:
		{
			this->processRspQueryBankAccountMoneyByStock(task);
			break;
		}

		case ONRSPQRYTRANSFERSERIAL:
		{
			this->processRspQryTransferSerial(task);
			break;
		}

		case ONRSPQRYSETTLEMENTINFOCONFIRM:
		{
			this->processRspQrySettlementInfoConfirm(task);
			break;
		}

		case ONRSPSETTLEMENTINFOCONFIRM:
		{
			this->processRspSettlementInfoConfirm(task);
			break;
		}

		case ONRSPQRYSETTLEMENTINFO:
		{
			this->processRspQrySettlementInfo(task);
			break;
		}

		case ONRSPQRYINVESTORTRADELEVEL:
		{
			this->processRspQryInvestorTradeLevel(task);
			break;
		}

		case ONRSPQRYPURCHASELIMITAMT:
		{
			this->processRspQryPurchaseLimitAmt(task);
			break;
		}

		case ONRSPQRYPOSITIONLIMITVOL:
		{
			this->processRspQryPositionLimitVol(task);
			break;
		}

		case ONRSPQRYHISTORYORDER:
		{
			this->processRspQryHistoryOrder(task);
			break;
		}

		case ONRSPQRYHISTORYTRADE:
		{
			this->processRspQryHistoryTrade(task);
			break;
		}

		case ONRSPQRYHISTORYASSIGNMENT:
		{
			this->processRspQryHistoryAssignment(task);
			break;
		}

		case ONRSPQRYDELIVDETAIL:
		{
			this->processRspQryDelivDetail(task);
			break;
		}

		case ONRSPAUTOEXECORDERACTION:
		{
			this->processRspAutoExecOrderAction(task);
			break;
		}

		case ONRSPCOMBACTIONINSERT:
		{
			this->processRspCombActionInsert(task);
			break;
		}

		case ONRSPQRYINVESTORCOMBINEPOSITION:
		{
			this->processRspQryInvestorCombinePosition(task);
			break;
		}

		case ONRSPQRYCOMBACTIONVOLUME:
		{
			this->processRspQryCombActionVolume(task);
			break;
		}

		case ONRSPFUNDOUTCREDITAPPLY:
		{
			this->processRspFundOutCreditApply(task);
			break;
		}

		case ONRSPQRYFUNDOUTCREDIT:
		{
			this->processRspQryFundOutCredit(task);
			break;
		}

		case ONRSPQRYFUNDOUTCREDITAPPLY:
		{
			this->processRspQryFundOutCreditApply(task);
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

		case ONRTNEXECORDER:
		{
			this->processRtnExecOrder(task);
			break;
		}

		case ONRTNLOCK:
		{
			this->processRtnLock(task);
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

		case ONRTNCOMBACTION:
		{
			this->processRtnCombAction(task);
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

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CKSOTPRspUserLoginField task_data = any_cast<CKSOTPRspUserLoginField>(task.task_data);
	dict data;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["BrokerID"] = task_data.BrokerID;
	data["LoginTime"] = task_data.LoginTime;
	data["SSETime"] = task_data.SSETime;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CKSOTPUserLogoutField task_data = any_cast<CKSOTPUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CKSOTPUserPasswordUpdateField task_data = any_cast<CKSOTPUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	PyLock lock;
	CKSOTPTradingAccountPasswordUpdateField task_data = any_cast<CKSOTPTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CKSOTPInputOrderField task_data = any_cast<CKSOTPInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["IsSwapOrder"] = task_data.IsSwapOrder;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CKSOTPInputOrderActionField task_data = any_cast<CKSOTPInputOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CKSOTPOrderField task_data = any_cast<CKSOTPOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["OrderType"] = task_data.OrderType;
	data["Direction"] = task_data.Direction;
	data["ActiveTime"] = task_data.ActiveTime;
	data["OffsetFlag"] = task_data.OffsetFlag;
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
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CKSOTPTradeField task_data = any_cast<CKSOTPTradeField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CKSOTPInvestorPositionField task_data = any_cast<CKSOTPInvestorPositionField>(task.task_data);
	dict data;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["CashIn"] = task_data.CashIn;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["CloseAmount"] = task_data.CloseAmount;
	data["PosiDirection"] = task_data.PosiDirection;
	data["YdPosition"] = task_data.YdPosition;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["OpenVolume"] = task_data.OpenVolume;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["InstrumentID"] = task_data.InstrumentID;
	data["PositionDate"] = task_data.PositionDate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["StrikeFrozen"] = task_data.StrikeFrozen;
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
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LongFrozenAmount"] = task_data.LongFrozenAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["StrikeFrozenAmount"] = task_data.StrikeFrozenAmount;
	data["CloseProfit"] = task_data.CloseProfit;
	data["UseMargin"] = task_data.UseMargin;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CKSOTPTradingAccountField task_data = any_cast<CKSOTPTradingAccountField>(task.task_data);
	dict data;
	data["Mortgage"] = task_data.Mortgage;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["CashIn"] = task_data.CashIn;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["PreMargin"] = task_data.PreMargin;
	data["SettlementID"] = task_data.SettlementID;
	data["DeliveryMargin"] = task_data.DeliveryMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["Balance"] = task_data.Balance;
	data["Reserve"] = task_data.Reserve;
	data["Credit"] = task_data.Credit;
	data["PreBalance"] = task_data.PreBalance;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["CloseProfit"] = task_data.CloseProfit;
	data["Deposit"] = task_data.Deposit;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CKSOTPInvestorField task_data = any_cast<CKSOTPInvestorField>(task.task_data);
	dict data;
	data["InvestorName"] = task_data.InvestorName;
	data["Mobile"] = task_data.Mobile;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["Telephone"] = task_data.Telephone;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Address"] = task_data.Address;
	data["OpenDate"] = task_data.OpenDate;
	data["IsActive"] = task_data.IsActive;
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CKSOTPTradingCodeField task_data = any_cast<CKSOTPTradingCodeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ClientIDType"] = task_data.ClientIDType;
	data["IsActive"] = task_data.IsActive;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CKSOTPExchangeField task_data = any_cast<CKSOTPExchangeField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CKSOTPInstrumentField task_data = any_cast<CKSOTPInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["PositionDateType"] = task_data.PositionDateType;
	data["LongMarginRatio"] = task_data.LongMarginRatio;
	data["StrikePrice"] = task_data.StrikePrice;
	data["UnderlyingMultiple"] = task_data.UnderlyingMultiple;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ShortMarginRatio"] = task_data.ShortMarginRatio;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["DeliveryYear"] = task_data.DeliveryYear;
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
	data["PriceTick"] = task_data.PriceTick;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["UnderlyingInstrID"] = task_data.UnderlyingInstrID;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPositionDetail(Task task)
{
	PyLock lock;
	CKSOTPInvestorPositionDetailField task_data = any_cast<CKSOTPInvestorPositionDetailField>(task.task_data);
	dict data;
	data["PositionProfitByDate"] = task_data.PositionProfitByDate;
	data["ExchMargin"] = task_data.ExchMargin;
	data["TradeType"] = task_data.TradeType;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["Direction"] = task_data.Direction;
	data["OpenPrice"] = task_data.OpenPrice;
	data["Volume"] = task_data.Volume;
	data["LastSettlementPrice"] = task_data.LastSettlementPrice;
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
	data["OpenDate"] = task_data.OpenDate;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPositionDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingNotice(Task task)
{
	PyLock lock;
	CKSOTPTradingNoticeField task_data = any_cast<CKSOTPTradingNoticeField>(task.task_data);
	dict data;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["SequenceNo"] = task_data.SequenceNo;
	data["UserID"] = task_data.UserID;
	data["FieldContent"] = task_data.FieldContent;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["SendTime"] = task_data.SendTime;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingNotice(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderInsert(Task task)
{
	PyLock lock;
	CKSOTPInputExecOrderField task_data = any_cast<CKSOTPInputExecOrderField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspExecOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspLockInsert(Task task)
{
	PyLock lock;
	CKSOTPInputLockField task_data = any_cast<CKSOTPInputLockField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspLockInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspExecOrderAction(Task task)
{
	PyLock lock;
	CKSOTPInputExecOrderActionField task_data = any_cast<CKSOTPInputExecOrderActionField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspExecOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecOrder(Task task)
{
	PyLock lock;
	CKSOTPExecOrderField task_data = any_cast<CKSOTPExecOrderField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExecOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExecOrderVolume(Task task)
{
	PyLock lock;
	CKSOTPExecOrderVolumeField task_data = any_cast<CKSOTPExecOrderVolumeField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["Direction"] = task_data.Direction;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ActionVolume"] = task_data.ActionVolume;
	data["ActionedVolume"] = task_data.ActionedVolume;
	data["ExecedVolume"] = task_data.ExecedVolume;
	data["ExecVolume"] = task_data.ExecVolume;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExecOrderVolume(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryLock(Task task)
{
	PyLock lock;
	CKSOTPLockField task_data = any_cast<CKSOTPLockField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryLock(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryLockPosition(Task task)
{
	PyLock lock;
	CKSOTPLockPositionField task_data = any_cast<CKSOTPLockPositionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenVolume"] = task_data.FrozenVolume;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryLockPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryUnderlyingStockInfo(Task task)
{
	PyLock lock;
	CKSOTPUnderlyingStockInfoField task_data = any_cast<CKSOTPUnderlyingStockInfoField>(task.task_data);
	dict data;
	data["GuarantRatio"] = task_data.GuarantRatio;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BrokerID"] = task_data.BrokerID;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryUnderlyingStockInfo(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOTPInsCommRate(Task task)
{
	PyLock lock;
	CKSOTPOTPInsCommRateField task_data = any_cast<CKSOTPOTPInsCommRateField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOTPInsCommRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrumentMarginRate(Task task)
{
	PyLock lock;
	CKSOTPInstrumentMarginRateField task_data = any_cast<CKSOTPInstrumentMarginRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ShortMarginRatioByMoney"] = task_data.ShortMarginRatioByMoney;
	data["ExchangeID"] = task_data.ExchangeID;
	data["LongMarginRatioByMoney"] = task_data.LongMarginRatioByMoney;
	data["IsRelative"] = task_data.IsRelative;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["ShortMarginRatioByVolume"] = task_data.ShortMarginRatioByVolume;
	data["LongMarginRatioByVolume"] = task_data.LongMarginRatioByVolume;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentMarginRate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOTPAssignment(Task task)
{
	PyLock lock;
	CKSOTPOTPAssignmentField task_data = any_cast<CKSOTPOTPAssignmentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["InstrumentName"] = task_data.InstrumentName;
	data["Direction"] = task_data.Direction;
	data["AssProVol"] = task_data.AssProVol;
	data["OptionsType"] = task_data.OptionsType;
	data["YdPosition"] = task_data.YdPosition;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["ExchangeID"] = task_data.ExchangeID;
	data["AssInsVo"] = task_data.AssInsVo;
	data["InvestorID"] = task_data.InvestorID;
	data["FeePay"] = task_data.FeePay;
	data["BrokerID"] = task_data.BrokerID;
	data["StockID"] = task_data.StockID;
	data["DeliveryDay"] = task_data.DeliveryDay;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOTPAssignment(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	CKSOTPDepthMarketDataField task_data = any_cast<CKSOTPDepthMarketDataField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFromBankToStockByStock(Task task)
{
	PyLock lock;
	CKSOTPReqTransferField task_data = any_cast<CKSOTPReqTransferField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromBankToStockByStock(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFromBankToStockByStock(Task task)
{
	PyLock lock;
	CKSOTPRspTransferField task_data = any_cast<CKSOTPRspTransferField>(task.task_data);
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

	this->onRtnFromBankToStockByStock(data);
};

void TdApi::processRspFromStockToBankByStock(Task task)
{
	PyLock lock;
	CKSOTPReqTransferField task_data = any_cast<CKSOTPReqTransferField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFromStockToBankByStock(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFromStockToBankByStock(Task task)
{
	PyLock lock;
	CKSOTPRspTransferField task_data = any_cast<CKSOTPRspTransferField>(task.task_data);
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

	this->onRtnFromStockToBankByStock(data);
};

void TdApi::processRtnQueryBankBalanceByStock(Task task)
{
	PyLock lock;
	CKSOTPNotifyQueryAccountField task_data = any_cast<CKSOTPNotifyQueryAccountField>(task.task_data);
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

	this->onRtnQueryBankBalanceByStock(data);
};

void TdApi::processRspQryContractBank(Task task)
{
	PyLock lock;
	CKSOTPContractBankField task_data = any_cast<CKSOTPContractBankField>(task.task_data);
	dict data;
	data["BankName"] = task_data.BankName;
	data["BrokerID"] = task_data.BrokerID;
	data["BankBrchID"] = task_data.BankBrchID;
	data["BankID"] = task_data.BankID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryContractBank(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQueryBankAccountMoneyByStock(Task task)
{
	PyLock lock;
	CKSOTPReqQueryAccountField task_data = any_cast<CKSOTPReqQueryAccountField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQueryBankAccountMoneyByStock(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	CKSOTPTransferSerialField task_data = any_cast<CKSOTPTransferSerialField>(task.task_data);
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

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTransferSerial(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfoConfirm(Task task)
{
	PyLock lock;
	CKSOTPSettlementInfoConfirmField task_data = any_cast<CKSOTPSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmTime"] = task_data.ConfirmTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ConfirmDate"] = task_data.ConfirmDate;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSettlementInfoConfirm(Task task)
{
	PyLock lock;
	CKSOTPSettlementInfoConfirmField task_data = any_cast<CKSOTPSettlementInfoConfirmField>(task.task_data);
	dict data;
	data["ConfirmTime"] = task_data.ConfirmTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ConfirmDate"] = task_data.ConfirmDate;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSettlementInfoConfirm(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySettlementInfo(Task task)
{
	PyLock lock;
	CKSOTPSettlementInfoField task_data = any_cast<CKSOTPSettlementInfoField>(task.task_data);
	dict data;
	data["SettlementID"] = task_data.SettlementID;
	data["InvestorID"] = task_data.InvestorID;
	data["SequenceNo"] = task_data.SequenceNo;
	data["Content"] = task_data.Content;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySettlementInfo(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorTradeLevel(Task task)
{
	PyLock lock;
	CKSOTPInvestorTradeLevelField task_data = any_cast<CKSOTPInvestorTradeLevelField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BrokerID"] = task_data.BrokerID;
	data["TradeLevel"] = task_data.TradeLevel;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorTradeLevel(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryPurchaseLimitAmt(Task task)
{
	PyLock lock;
	CKSOTPPurchaseLimitAmtField task_data = any_cast<CKSOTPPurchaseLimitAmtField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["PurLimitAmt"] = task_data.PurLimitAmt;
	data["BrokerID"] = task_data.BrokerID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryPurchaseLimitAmt(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryPositionLimitVol(Task task)
{
	PyLock lock;
	CKSOTPPositionLimitVolField task_data = any_cast<CKSOTPPositionLimitVolField>(task.task_data);
	dict data;
	data["ProtectFlag"] = task_data.ProtectFlag;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OptionsType"] = task_data.OptionsType;
	data["PosiLimitVol"] = task_data.PosiLimitVol;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ControlRange"] = task_data.ControlRange;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryPositionLimitVol(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryHistoryOrder(Task task)
{
	PyLock lock;
	CKSOTPHistoryOrderField task_data = any_cast<CKSOTPHistoryOrderField>(task.task_data);
	dict data;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["ProductClass"] = task_data.ProductClass;
	data["ProductName"] = task_data.ProductName;
	data["Direction"] = task_data.Direction;
	data["CustomerName"] = task_data.CustomerName;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["SessionID"] = task_data.SessionID;
	data["OrderStatus"] = task_data.OrderStatus;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FunctionName"] = task_data.FunctionName;
	data["OrderPrice"] = task_data.OrderPrice;
	data["TradePrice"] = task_data.TradePrice;
	data["OrderSource"] = task_data.OrderSource;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["OrderTime"] = task_data.OrderTime;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["CurrencyID"] = task_data.CurrencyID;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["FrozenAmount"] = task_data.FrozenAmount;
	data["OrderRef"] = task_data.OrderRef;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["RequestID"] = task_data.RequestID;
	data["BrokerID"] = task_data.BrokerID;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryHistoryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryHistoryTrade(Task task)
{
	PyLock lock;
	CKSOTPHistoryTradeField task_data = any_cast<CKSOTPHistoryTradeField>(task.task_data);
	dict data;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Commission"] = task_data.Commission;
	data["TradeTime"] = task_data.TradeTime;
	data["CustomerName"] = task_data.CustomerName;
	data["Memo"] = task_data.Memo;
	data["ClientID"] = task_data.ClientID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["TradePrice;"] = task_data.TradePrice;;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FunctionName"] = task_data.FunctionName;
	data["OptionsType"] = task_data.OptionsType;
	data["BrokerID"] = task_data.BrokerID;
	data["RoyaltyAmount"] = task_data.RoyaltyAmount;
	data["TraderOfferTime"] = task_data.TraderOfferTime;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["TradeID"] = task_data.TradeID;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["TradeDate"] = task_data.TradeDate;
	data["CurrencyID"] = task_data.CurrencyID;
	data["ProductName"] = task_data.ProductName;
	data["InvestorID"] = task_data.InvestorID;
	data["ObligationVolume"] = task_data.ObligationVolume;
	data["RoyaltyVolume"] = task_data.RoyaltyVolume;
	data["ObligationAmount"] = task_data.ObligationAmount;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryHistoryTrade(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryHistoryAssignment(Task task)
{
	PyLock lock;
	CKSOTPHistoryAssignmentField task_data = any_cast<CKSOTPHistoryAssignmentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OptionsType"] = task_data.OptionsType;
	data["DelivDate"] = task_data.DelivDate;
	data["TradingDay"] = task_data.TradingDay;
	data["PosiDirection"] = task_data.PosiDirection;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["StrikePrice"] = task_data.StrikePrice;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["StockInstr"] = task_data.StockInstr;
	data["IOVol"] = task_data.IOVol;
	data["IOAmt"] = task_data.IOAmt;
	data["ExecVol"] = task_data.ExecVol;
	data["ProductID"] = task_data.ProductID;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryHistoryAssignment(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryDelivDetail(Task task)
{
	PyLock lock;
	CKSOTPDelivDetailField task_data = any_cast<CKSOTPDelivDetailField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FunctionName"] = task_data.FunctionName;
	data["SettlementAmt"] = task_data.SettlementAmt;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["StockInstr"] = task_data.StockInstr;
	data["IOVolInFact"] = task_data.IOVolInFact;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["IOVol"] = task_data.IOVol;
	data["DelivDate"] = task_data.DelivDate;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryDelivDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspAutoExecOrderAction(Task task)
{
	PyLock lock;
	CKSOTPAutoExecOrderActionField task_data = any_cast<CKSOTPAutoExecOrderActionField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["RangeVol"] = task_data.RangeVol;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspAutoExecOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspCombActionInsert(Task task)
{
	PyLock lock;
	CKSOTPInputCombActionField task_data = any_cast<CKSOTPInputCombActionField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CombDirection"] = task_data.CombDirection;
	data["CombActionRef"] = task_data.CombActionRef;
	data["ComTradeID"] = task_data.ComTradeID;
	data[" CombActionFlag"] = task_data.CombActionFlag;
	data["UserID"] = task_data.UserID;
	data["Direction1"] = task_data.Direction1;
	data["Direction3"] = task_data.Direction3;
	data["InstrumentID4"] = task_data.InstrumentID4;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InstrumentID1"] = task_data.InstrumentID1;
	data["Direction2"] = task_data.Direction2;
	data["StrategyID"] = task_data.StrategyID;
	data["InstrumentID2"] = task_data.InstrumentID2;
	data["InstrumentID3"] = task_data.InstrumentID3;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction4"] = task_data.Direction4;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspCombActionInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorCombinePosition(Task task)
{
	PyLock lock;
	CKSOTPInvestorPositionCombineDetailField task_data = any_cast<CKSOTPInvestorPositionCombineDetailField>(task.task_data);
	dict data;
	data["ExchangeID"] = task_data.ExchangeID;
	data["CombActionVolume"] = task_data.CombActionVolume;
	data["Direction3"] = task_data.Direction3;
	data["ComTradeID"] = task_data.ComTradeID;
	data["TotalAmt"] = task_data.TotalAmt;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["Direction1"] = task_data.Direction1;
	data["ClientID"] = task_data.ClientID;
	data["InstrumentID4"] = task_data.InstrumentID4;
	data["CombDirection"] = task_data.CombDirection;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InstrumentID1"] = task_data.InstrumentID1;
	data["Direction2"] = task_data.Direction2;
	data["StrategyID"] = task_data.StrategyID;
	data["InstrumentID2"] = task_data.InstrumentID2;
	data["Margin"] = task_data.Margin;
	data["InstrumentID3"] = task_data.InstrumentID3;
	data["Direction4"] = task_data.Direction4;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorCombinePosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryCombActionVolume(Task task)
{
	PyLock lock;
	CKSOTPCombActionVolumeField task_data = any_cast<CKSOTPCombActionVolumeField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxActionVolume"] = task_data.MaxActionVolume;
	data["MaxCombVolume"] = task_data.MaxCombVolume;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCombActionVolume(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFundOutCreditApply(Task task)
{
	PyLock lock;
	CKSOTPInputFundOutCreditApplyField task_data = any_cast<CKSOTPInputFundOutCreditApplyField>(task.task_data);
	dict data;
	data["CreditApplyFlag"] = task_data.CreditApplyFlag;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["FundOutCredit"] = task_data.FundOutCredit;
	data["CreditSerial"] = task_data.CreditSerial;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFundOutCreditApply(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryFundOutCredit(Task task)
{
	PyLock lock;
	CKSOTPRspQryFundOutCreditField task_data = any_cast<CKSOTPRspQryFundOutCreditField>(task.task_data);
	dict data;
	data["FundOutCredit"] = task_data.FundOutCredit;
	data["FundOutedCredit"] = task_data.FundOutedCredit;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["UpdateDate"] = task_data.UpdateDate;
	data["SetTime"] = task_data.SetTime;
	data["SetDate"] = task_data.SetDate;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryFundOutCredit(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryFundOutCreditApply(Task task)
{
	PyLock lock;
	CKSOTPRspQryFundOutCreditApplyField task_data = any_cast<CKSOTPRspQryFundOutCreditApplyField>(task.task_data);
	dict data;
	data["DealStatus"] = task_data.DealStatus;
	data["FundOutCredit"] = task_data.FundOutCredit;
	data["ApplyTime"] = task_data.ApplyTime;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ConfirmDate"] = task_data.ConfirmDate;
	data["ConfirmTime"] = task_data.ConfirmTime;
	data["ApplyDate"] = task_data.ApplyDate;
	data["CreditSerial"] = task_data.CreditSerial;

	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryFundOutCreditApply(data, error, task.task_id, task.task_last);
};

void TdApi::processRspError(Task task)
{
	PyLock lock;
	CKSOTPRspInfoField task_error = any_cast<CKSOTPRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CKSOTPOrderField task_data = any_cast<CKSOTPOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["TraderID"] = task_data.TraderID;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["OrderType"] = task_data.OrderType;
	data["Direction"] = task_data.Direction;
	data["ActiveTime"] = task_data.ActiveTime;
	data["OffsetFlag"] = task_data.OffsetFlag;
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
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["UserID"] = task_data.UserID;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CKSOTPTradeField task_data = any_cast<CKSOTPTradeField>(task.task_data);
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

void TdApi::processRtnExecOrder(Task task)
{
	PyLock lock;
	CKSOTPExecOrderField task_data = any_cast<CKSOTPExecOrderField>(task.task_data);
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

void TdApi::processRtnLock(Task task)
{
	PyLock lock;
	CKSOTPLockField task_data = any_cast<CKSOTPLockField>(task.task_data);
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

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CKSOTPInstrumentStatusField task_data = any_cast<CKSOTPInstrumentStatusField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["EnterTime"] = task_data.EnterTime;
	data["TradingSegmentSN"] = task_data.TradingSegmentSN;
	data["EnterReason"] = task_data.EnterReason;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["ExchangeInstID"] = task_data.ExchangeInstID;

	this->onRtnInstrumentStatus(data);
};

void TdApi::processRtnTradingNotice(Task task)
{
	PyLock lock;
	CKSOTPTradingNoticeInfoField task_data = any_cast<CKSOTPTradingNoticeInfoField>(task.task_data);
	dict data;
	data["SequenceSeries"] = task_data.SequenceSeries;
	data["SequenceNo"] = task_data.SequenceNo;
	data["FieldContent"] = task_data.FieldContent;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["SendTime"] = task_data.SendTime;

	this->onRtnTradingNotice(data);
};

void TdApi::processRtnCombAction(Task task)
{
	PyLock lock;
	CKSOTPCombActionField task_data = any_cast<CKSOTPCombActionField>(task.task_data);
	dict data;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ComTradeID"] = task_data.ComTradeID;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["OrderSource"] = task_data.OrderSource;
	data["TraderID"] = task_data.TraderID;
	data[" CombActionFlag"] = task_data.CombActionFlag;
	data["ActionStatus"] = task_data.ActionStatus;
	data["StrategyID"] = task_data.StrategyID;
	data["CombDirection"] = task_data.CombDirection;
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
	data["FrontID"] = task_data.FrontID;
	data["InstrumentID1"] = task_data.InstrumentID1;
	data["InstrumentID3"] = task_data.InstrumentID3;
	data["InstrumentID2"] = task_data.InstrumentID2;
	data["InstrumentID4"] = task_data.InstrumentID4;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["CombActionRef"] = task_data.CombActionRef;
	data["SequenceNo"] = task_data.SequenceNo;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["Direction3"] = task_data.Direction3;
	data["Direction2"] = task_data.Direction2;
	data["Direction1"] = task_data.Direction1;
	data["Direction4"] = task_data.Direction4;

	this->onRtnCombAction(data);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createOTPTraderApi(string pszFlowPath)
{
	this->api = CKSOTPTraderApi::CreateOTPTraderApi(pszFlowPath.c_str());
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
	KSOTP_TE_RESUME_TYPE type;

	switch (nType)
	{
	case 0:
	{
		type = KSOTP_TERT_RESTART;
		break;
	};

	case 1:
	{
		type = KSOTP_TERT_RESUME;
		break;
	};

	case 2:
	{
		type = KSOTP_TERT_QUICK;
		break;
	};
	}

	this->api->SubscribePrivateTopic(type);


};

void TdApi::subscribePublicTopic(int nType)
{
	//该函数为手动编写
	KSOTP_TE_RESUME_TYPE type;

	switch (nType)
	{
	case 0:
	{
		type = KSOTP_TERT_RESTART;
		break;
	};

	case 1:
	{
		type = KSOTP_TERT_RESUME;
		break;
	};

	case 2:
	{
		type = KSOTP_TERT_QUICK;
		break;
	};
	}

	this->api->SubscribePublicTopic(type);
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CKSOTPReqUserLoginField myreq = CKSOTPReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
	getChar(req, "UserProductInfo", myreq.UserProductInfo);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientIPAddress", myreq.ClientIPAddress);
	getChar(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CKSOTPUserLogoutField myreq = CKSOTPUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CKSOTPUserPasswordUpdateField myreq = CKSOTPUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqTradingAccountPasswordUpdate(dict req, int nRequestID)
{
	CKSOTPTradingAccountPasswordUpdateField myreq = CKSOTPTradingAccountPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqTradingAccountPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CKSOTPInputOrderField myreq = CKSOTPInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getInt(req, "IsSwapOrder", &myreq.IsSwapOrder);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "GTDDate", myreq.GTDDate);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);

	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CKSOTPInputOrderActionField myreq = CKSOTPInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CKSOTPQryOrderField myreq = CKSOTPQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CKSOTPQryTradeField myreq = CKSOTPQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "TradeTimeEnd", myreq.TradeTimeEnd);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "TradeTimeStart", myreq.TradeTimeStart);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CKSOTPQryInvestorPositionField myreq = CKSOTPQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CKSOTPQryTradingAccountField myreq = CKSOTPQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CKSOTPQryInvestorField myreq = CKSOTPQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
{
	CKSOTPQryTradingCodeField myreq = CKSOTPQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CKSOTPQryExchangeField myreq = CKSOTPQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CKSOTPQryInstrumentField myreq = CKSOTPQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(dict req, int nRequestID)
{
	CKSOTPQryInvestorPositionDetailField myreq = CKSOTPQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPositionDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingNotice(dict req, int nRequestID)
{
	CKSOTPQryTradingNoticeField myreq = CKSOTPQryTradingNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingNotice(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderInsert(dict req, int nRequestID)
{
	CKSOTPInputExecOrderField myreq = CKSOTPInputExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExecOrderRef", myreq.ExecOrderRef);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "CloseFlag", &myreq.CloseFlag);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "PosiDirection", &myreq.PosiDirection);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getChar(req, "UserID", myreq.UserID);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionType", &myreq.ActionType);
	getChar(req, "ReservePositionFlag", &myreq.ReservePositionFlag);
	int i = this->api->ReqExecOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqExecOrderAction(dict req, int nRequestID)
{
	CKSOTPInputExecOrderActionField myreq = CKSOTPInputExecOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "ExecOrderRef", myreq.ExecOrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "ExecOrderActionRef", &myreq.ExecOrderActionRef);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqExecOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqLockInsert(dict req, int nRequestID)
{
	CKSOTPInputLockField myreq = CKSOTPInputLockField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "LockRef", myreq.LockRef);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "LockType", &myreq.LockType);
	int i = this->api->ReqLockInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExecOrder(dict req, int nRequestID)
{
	CKSOTPQryExecOrderField myreq = CKSOTPQryExecOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ExecOrderSysID", myreq.ExecOrderSysID);
	int i = this->api->ReqQryExecOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExecOrderVolume(dict req, int nRequestID)
{
	CKSOTPQryExecOrderVolumeField myreq = CKSOTPQryExecOrderVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryExecOrderVolume(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryLock(dict req, int nRequestID)
{
	CKSOTPQryLockField myreq = CKSOTPQryLockField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "LockSysID", myreq.LockSysID);
	int i = this->api->ReqQryLock(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryLockPosition(dict req, int nRequestID)
{
	CKSOTPQryLockPositionField myreq = CKSOTPQryLockPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryLockPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryUnderlyingStockInfo(dict req, int nRequestID)
{
	CKSOTPQryUnderlyingStockInfoField myreq = CKSOTPQryUnderlyingStockInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryUnderlyingStockInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOTPInsCommRate(dict req, int nRequestID)
{
	CKSOTPQryOTPInsCommRateField myreq = CKSOTPQryOTPInsCommRateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryOTPInsCommRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentMarginRate(dict req, int nRequestID)
{
	CKSOTPQryInstrumentMarginRateField myreq = CKSOTPQryInstrumentMarginRateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	int i = this->api->ReqQryInstrumentMarginRate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOTPAssignment(dict req, int nRequestID)
{
	CKSOTPQryOTPAssignmentField myreq = CKSOTPQryOTPAssignmentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "Direction", &myreq.Direction);
	int i = this->api->ReqQryOTPAssignment(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req, int nRequestID)
{
	CKSOTPQryDepthMarketDataField myreq = CKSOTPQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryDepthMarketData(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromBankToStockByStock(dict req, int nRequestID)
{
	CKSOTPReqTransferField myreq = CKSOTPReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BrokerBranchID", myreq.BrokerBranchID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BankPassWord", myreq.BankPassWord);
	getChar(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getChar(req, "AccountID", myreq.AccountID);
	getChar(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getChar(req, "CustomerName", myreq.CustomerName);
	getChar(req, "TradeCode", myreq.TradeCode);
	getChar(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "BankID", myreq.BankID);
	getChar(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getChar(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getChar(req, "BankSerial", myreq.BankSerial);
	getChar(req, "OperNo", myreq.OperNo);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "BankSecuAcc", myreq.BankSecuAcc);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "TradeDate", myreq.TradeDate);
	getChar(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getChar(req, "Message", myreq.Message);
	getChar(req, "Message", myreq.Message);
	getChar(req, "Message", myreq.Message);
	getChar(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromBankToStockByStock(&myreq, nRequestID);
	return i;
};

int TdApi::reqFromStockToBankByStock(dict req, int nRequestID)
{
	CKSOTPReqTransferField myreq = CKSOTPReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BrokerBranchID", myreq.BrokerBranchID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BankPassWord", myreq.BankPassWord);
	getChar(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getChar(req, "AccountID", myreq.AccountID);
	getChar(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getChar(req, "CustomerName", myreq.CustomerName);
	getChar(req, "TradeCode", myreq.TradeCode);
	getChar(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "BankID", myreq.BankID);
	getChar(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getChar(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "FeePayFlag", &myreq.FeePayFlag);
	getChar(req, "BankSerial", myreq.BankSerial);
	getChar(req, "OperNo", myreq.OperNo);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "BankSecuAcc", myreq.BankSecuAcc);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "DeviceID", myreq.DeviceID);
	getChar(req, "TransferStatus", &myreq.TransferStatus);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "TradeDate", myreq.TradeDate);
	getChar(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getChar(req, "Message", myreq.Message);
	getChar(req, "Message", myreq.Message);
	getChar(req, "Message", myreq.Message);
	getChar(req, "Digest", myreq.Digest);
	int i = this->api->ReqFromStockToBankByStock(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryContractBank(dict req, int nRequestID)
{
	CKSOTPQryContractBankField myreq = CKSOTPQryContractBankField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "BankBrchID", myreq.BankBrchID);
	getChar(req, "BankID", myreq.BankID);
	int i = this->api->ReqQryContractBank(&myreq, nRequestID);
	return i;
};

int TdApi::reqQueryBankAccountMoneyByStock(dict req, int nRequestID)
{
	CKSOTPReqQueryAccountField myreq = CKSOTPReqQueryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BrokerBranchID", myreq.BrokerBranchID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BankPassWord", myreq.BankPassWord);
	getChar(req, "TradeTime", myreq.TradeTime);
	getChar(req, "VerifyCertNoFlag", &myreq.VerifyCertNoFlag);
	getInt(req, "TID", &myreq.TID);
	getChar(req, "AccountID", myreq.AccountID);
	getChar(req, "BankAccount", myreq.BankAccount);
	getInt(req, "InstallID", &myreq.InstallID);
	getChar(req, "CustomerName", myreq.CustomerName);
	getChar(req, "TradeCode", myreq.TradeCode);
	getChar(req, "BankBranchID", myreq.BankBranchID);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "BankID", myreq.BankID);
	getChar(req, "Password", myreq.Password);
	getChar(req, "BankPwdFlag", &myreq.BankPwdFlag);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "CustType", &myreq.CustType);
	getChar(req, "IdentifiedCardNo", myreq.IdentifiedCardNo);
	getChar(req, "BankSerial", myreq.BankSerial);
	getChar(req, "OperNo", myreq.OperNo);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "BankSecuAcc", myreq.BankSecuAcc);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "DeviceID", myreq.DeviceID);
	getChar(req, "IdCardType", &myreq.IdCardType);
	getInt(req, "PlateSerial", &myreq.PlateSerial);
	getChar(req, "TradeDate", myreq.TradeDate);
	getChar(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankAccType", &myreq.BankAccType);
	getChar(req, "LastFragment", &myreq.LastFragment);
	getInt(req, "FutureSerial", &myreq.FutureSerial);
	getChar(req, "BankSecuAccType", &myreq.BankSecuAccType);
	getChar(req, "BrokerIDByBank", myreq.BrokerIDByBank);
	getChar(req, "SecuPwdFlag", &myreq.SecuPwdFlag);
	getChar(req, "Digest", myreq.Digest);
	int i = this->api->ReqQueryBankAccountMoneyByStock(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTransferSerial(dict req, int nRequestID)
{
	CKSOTPQryTransferSerialField myreq = CKSOTPQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "CurrencyID", myreq.CurrencyID);
	getChar(req, "BankID", myreq.BankID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySettlementInfoConfirm(dict req, int nRequestID)
{
	CKSOTPQrySettlementInfoConfirmField myreq = CKSOTPQrySettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQrySettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqSettlementInfoConfirm(dict req, int nRequestID)
{
	CKSOTPSettlementInfoConfirmField myreq = CKSOTPSettlementInfoConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ConfirmTime", myreq.ConfirmTime);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ConfirmDate", myreq.ConfirmDate);
	int i = this->api->ReqSettlementInfoConfirm(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySettlementInfo(dict req, int nRequestID)
{
	CKSOTPQrySettlementInfoField myreq = CKSOTPQrySettlementInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "TradingDay", myreq.TradingDay);
	int i = this->api->ReqQrySettlementInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorTradeLevel(dict req, int nRequestID)
{
	CKSOTPQryInvestorTradeLevelField myreq = CKSOTPQryInvestorTradeLevelField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInvestorTradeLevel(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryPurchaseLimitAmt(dict req, int nRequestID)
{
	CKSOTPQryPurchaseLimitAmtField myreq = CKSOTPQryPurchaseLimitAmtField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryPurchaseLimitAmt(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryPositionLimitVol(dict req, int nRequestID)
{
	CKSOTPQryPositionLimitVolField myreq = CKSOTPQryPositionLimitVolField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ProtectFlag", &myreq.ProtectFlag);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OptionsType", &myreq.OptionsType);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ControlRange", &myreq.ControlRange);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryPositionLimitVol(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryHistoryOrder(dict req, int nRequestID)
{
	CKSOTPQryHistoryOrderField myreq = CKSOTPQryHistoryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "OrderLocalID", myreq.OrderLocalID);
	getChar(req, "OrderDataStart", myreq.OrderDataStart);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "OrderDataEnd", myreq.OrderDataEnd);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryHistoryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryHistoryTrade(dict req, int nRequestID)
{
	CKSOTPQryHistoryTradeField myreq = CKSOTPQryHistoryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "TradeDataEnd", myreq.TradeDataEnd);
	getChar(req, "TradeDataStart", myreq.TradeDataStart);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryHistoryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryHistoryAssignment(dict req, int nRequestID)
{
	CKSOTPQryHistoryAssignmentField myreq = CKSOTPQryHistoryAssignmentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OptionsType", &myreq.OptionsType);
	getChar(req, "PosiDirection", &myreq.PosiDirection);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "DeliveryMonth", myreq.DeliveryMonth);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryHistoryAssignment(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryDelivDetail(dict req, int nRequestID)
{
	CKSOTPQryDelivDetailField myreq = CKSOTPQryDelivDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "DelivMode", &myreq.DelivMode);
	getChar(req, "ProductID", myreq.ProductID);
	getChar(req, "DeliveryMonth", myreq.DeliveryMonth);
	int i = this->api->ReqQryDelivDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqAutoExecOrderAction(dict req, int nRequestID)
{
	CKSOTPAutoExecOrderActionField myreq = CKSOTPAutoExecOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RangeVol", &myreq.RangeVol);
	int i = this->api->ReqAutoExecOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqCombActionInsert(dict req, int nRequestID)
{
	CKSOTPInputCombActionField myreq = CKSOTPInputCombActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getChar(req, "CombActionRef", myreq.CombActionRef);
	getChar(req, "ComTradeID", myreq.ComTradeID);
	getChar(req, " CombActionFlag", &myreq.CombActionFlag);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "Direction1", &myreq.Direction1);
	getChar(req, "Direction3", &myreq.Direction3);
	getChar(req, "InstrumentID4", myreq.InstrumentID4);
	getInt(req, "Volume", &myreq.Volume);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InstrumentID1", myreq.InstrumentID1);
	getChar(req, "Direction2", &myreq.Direction2);
	getChar(req, "StrategyID", myreq.StrategyID);
	getChar(req, "InstrumentID2", myreq.InstrumentID2);
	getChar(req, "InstrumentID3", myreq.InstrumentID3);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getChar(req, "Direction4", &myreq.Direction4);
	int i = this->api->ReqCombActionInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorCombinePosition(dict req, int nRequestID)
{
	CKSOTPQryInvestorPositionCombineDetailField myreq = CKSOTPQryInvestorPositionCombineDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ComTradeID", myreq.ComTradeID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInvestorCombinePosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryCombActionVolume(dict req, int nRequestID)
{
	CKSOTPQryCombActionVolumeField myreq = CKSOTPQryCombActionVolumeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "CombDirection", &myreq.CombDirection);
	getChar(req, "Direction3", &myreq.Direction3);
	getChar(req, "ComTradeID", myreq.ComTradeID);
	getChar(req, " CombActionFlag", &myreq.CombActionFlag);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getChar(req, "Direction1", &myreq.Direction1);
	getChar(req, "InstrumentID4", myreq.InstrumentID4);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "InstrumentID1", myreq.InstrumentID1);
	getChar(req, "Direction2", &myreq.Direction2);
	getChar(req, "StrategyID", myreq.StrategyID);
	getChar(req, "InstrumentID2", myreq.InstrumentID2);
	getChar(req, "InstrumentID3", myreq.InstrumentID3);
	getChar(req, "Direction4", &myreq.Direction4);
	int i = this->api->ReqQryCombActionVolume(&myreq, nRequestID);
	return i;
};

int TdApi::reqFundOutCreditApply(dict req, int nRequestID)
{
	CKSOTPInputFundOutCreditApplyField myreq = CKSOTPInputFundOutCreditApplyField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "CreditApplyFlag", &myreq.CreditApplyFlag);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "CreditSerial", &myreq.CreditSerial);
	int i = this->api->ReqFundOutCreditApply(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryFundOutCredit(dict req, int nRequestID)
{
	CKSOTPQryFundOutCreditField myreq = CKSOTPQryFundOutCreditField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryFundOutCredit(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryFundOutCreditApply(dict req, int nRequestID)
{
	CKSOTPQryFundOutCreditApplyField myreq = CKSOTPQryFundOutCreditApplyField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "QryCreditEnd", myreq.QryCreditEnd);
	getChar(req, "DealStatus", &myreq.DealStatus);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "QryCreditStart", myreq.QryCreditStart);
	int i = this->api->ReqQryFundOutCreditApply(&myreq, nRequestID);
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

	virtual void onRspQryExecOrderVolume(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExecOrderVolume")(data, error, id, last);
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

	virtual void onRspQryUnderlyingStockInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryUnderlyingStockInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryOTPInsCommRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOTPInsCommRate")(data, error, id, last);
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

	virtual void onRspQryOTPAssignment(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOTPAssignment")(data, error, id, last);
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

	virtual void onRspFromBankToStockByStock(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFromBankToStockByStock")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromBankToStockByStock(dict data)
	{
		try
		{
			this->get_override("onRtnFromBankToStockByStock")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFromStockToBankByStock(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFromStockToBankByStock")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromStockToBankByStock(dict data)
	{
		try
		{
			this->get_override("onRtnFromStockToBankByStock")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnQueryBankBalanceByStock(dict data)
	{
		try
		{
			this->get_override("onRtnQueryBankBalanceByStock")(data);
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

	virtual void onRspQueryBankAccountMoneyByStock(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQueryBankAccountMoneyByStock")(data, error, id, last);
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

	virtual void onRspQryInvestorTradeLevel(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorTradeLevel")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryPurchaseLimitAmt(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryPurchaseLimitAmt")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryPositionLimitVol(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryPositionLimitVol")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryHistoryOrder(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryHistoryOrder")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryHistoryTrade(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryHistoryTrade")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryHistoryAssignment(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryHistoryAssignment")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryDelivDetail(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryDelivDetail")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspAutoExecOrderAction(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspAutoExecOrderAction")(data, error, id, last);
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

	virtual void onRspQryInvestorCombinePosition(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorCombinePosition")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryCombActionVolume(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryCombActionVolume")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFundOutCreditApply(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFundOutCreditApply")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryFundOutCredit(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryFundOutCredit")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryFundOutCreditApply(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryFundOutCreditApply")(data, error, id, last);
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
};


BOOST_PYTHON_MODULE(vnksotptd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("createOTPTraderApi", &TdApiWrap::createOTPTraderApi)
		.def("release", &TdApiWrap::release)
		.def("init", &TdApiWrap::init)
		.def("exit", &TdApiWrap::exit)
		.def("getTradingDay", &TdApiWrap::getTradingDay)
		.def("registerFront", &TdApiWrap::registerFront)
		.def("subscribePrivateTopic", &TdApiWrap::subscribePrivateTopic)
		.def("subscribePublicTopic", &TdApiWrap::subscribePublicTopic)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqUserPasswordUpdate", &TdApiWrap::reqUserPasswordUpdate)
		.def("reqTradingAccountPasswordUpdate", &TdApiWrap::reqTradingAccountPasswordUpdate)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqQryOrder", &TdApiWrap::reqQryOrder)
		.def("reqQryTrade", &TdApiWrap::reqQryTrade)
		.def("reqQryInvestorPosition", &TdApiWrap::reqQryInvestorPosition)
		.def("reqQryTradingAccount", &TdApiWrap::reqQryTradingAccount)
		.def("reqQryInvestor", &TdApiWrap::reqQryInvestor)
		.def("reqQryTradingCode", &TdApiWrap::reqQryTradingCode)
		.def("reqQryExchange", &TdApiWrap::reqQryExchange)
		.def("reqQryInstrument", &TdApiWrap::reqQryInstrument)
		.def("reqQryInvestorPositionDetail", &TdApiWrap::reqQryInvestorPositionDetail)
		.def("reqQryTradingNotice", &TdApiWrap::reqQryTradingNotice)
		.def("reqExecOrderInsert", &TdApiWrap::reqExecOrderInsert)
		.def("reqExecOrderAction", &TdApiWrap::reqExecOrderAction)
		.def("reqLockInsert", &TdApiWrap::reqLockInsert)
		.def("reqQryExecOrder", &TdApiWrap::reqQryExecOrder)
		.def("reqQryExecOrderVolume", &TdApiWrap::reqQryExecOrderVolume)
		.def("reqQryLock", &TdApiWrap::reqQryLock)
		.def("reqQryLockPosition", &TdApiWrap::reqQryLockPosition)
		.def("reqQryUnderlyingStockInfo", &TdApiWrap::reqQryUnderlyingStockInfo)
		.def("reqQryOTPInsCommRate", &TdApiWrap::reqQryOTPInsCommRate)
		.def("reqQryInstrumentMarginRate", &TdApiWrap::reqQryInstrumentMarginRate)
		.def("reqQryOTPAssignment", &TdApiWrap::reqQryOTPAssignment)
		.def("reqQryDepthMarketData", &TdApiWrap::reqQryDepthMarketData)
		.def("reqFromBankToStockByStock", &TdApiWrap::reqFromBankToStockByStock)
		.def("reqFromStockToBankByStock", &TdApiWrap::reqFromStockToBankByStock)
		.def("reqQryContractBank", &TdApiWrap::reqQryContractBank)
		.def("reqQueryBankAccountMoneyByStock", &TdApiWrap::reqQueryBankAccountMoneyByStock)
		.def("reqQryTransferSerial", &TdApiWrap::reqQryTransferSerial)
		.def("reqQrySettlementInfoConfirm", &TdApiWrap::reqQrySettlementInfoConfirm)
		.def("reqSettlementInfoConfirm", &TdApiWrap::reqSettlementInfoConfirm)
		.def("reqQrySettlementInfo", &TdApiWrap::reqQrySettlementInfo)
		.def("reqQryInvestorTradeLevel", &TdApiWrap::reqQryInvestorTradeLevel)
		.def("reqQryPurchaseLimitAmt", &TdApiWrap::reqQryPurchaseLimitAmt)
		.def("reqQryPositionLimitVol", &TdApiWrap::reqQryPositionLimitVol)
		.def("reqQryHistoryOrder", &TdApiWrap::reqQryHistoryOrder)
		.def("reqQryHistoryTrade", &TdApiWrap::reqQryHistoryTrade)
		.def("reqQryHistoryAssignment", &TdApiWrap::reqQryHistoryAssignment)
		.def("reqQryDelivDetail", &TdApiWrap::reqQryDelivDetail)
		.def("reqAutoExecOrderAction", &TdApiWrap::reqAutoExecOrderAction)
		.def("reqCombActionInsert", &TdApiWrap::reqCombActionInsert)
		.def("reqQryInvestorCombinePosition", &TdApiWrap::reqQryInvestorCombinePosition)
		.def("reqQryCombActionVolume", &TdApiWrap::reqQryCombActionVolume)
		.def("reqFundOutCreditApply", &TdApiWrap::reqFundOutCreditApply)
		.def("reqQryFundOutCredit", &TdApiWrap::reqQryFundOutCredit)
		.def("reqQryFundOutCreditApply", &TdApiWrap::reqQryFundOutCreditApply)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspUserPasswordUpdate))
		.def("onRspTradingAccountPasswordUpdate", pure_virtual(&TdApiWrap::onRspTradingAccountPasswordUpdate))
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onRspQryOrder", pure_virtual(&TdApiWrap::onRspQryOrder))
		.def("onRspQryTrade", pure_virtual(&TdApiWrap::onRspQryTrade))
		.def("onRspQryInvestorPosition", pure_virtual(&TdApiWrap::onRspQryInvestorPosition))
		.def("onRspQryTradingAccount", pure_virtual(&TdApiWrap::onRspQryTradingAccount))
		.def("onRspQryInvestor", pure_virtual(&TdApiWrap::onRspQryInvestor))
		.def("onRspQryTradingCode", pure_virtual(&TdApiWrap::onRspQryTradingCode))
		.def("onRspQryExchange", pure_virtual(&TdApiWrap::onRspQryExchange))
		.def("onRspQryInstrument", pure_virtual(&TdApiWrap::onRspQryInstrument))
		.def("onRspQryInvestorPositionDetail", pure_virtual(&TdApiWrap::onRspQryInvestorPositionDetail))
		.def("onRspQryTradingNotice", pure_virtual(&TdApiWrap::onRspQryTradingNotice))
		.def("onRspExecOrderInsert", pure_virtual(&TdApiWrap::onRspExecOrderInsert))
		.def("onRspLockInsert", pure_virtual(&TdApiWrap::onRspLockInsert))
		.def("onRspExecOrderAction", pure_virtual(&TdApiWrap::onRspExecOrderAction))
		.def("onRspQryExecOrder", pure_virtual(&TdApiWrap::onRspQryExecOrder))
		.def("onRspQryExecOrderVolume", pure_virtual(&TdApiWrap::onRspQryExecOrderVolume))
		.def("onRspQryLock", pure_virtual(&TdApiWrap::onRspQryLock))
		.def("onRspQryLockPosition", pure_virtual(&TdApiWrap::onRspQryLockPosition))
		.def("onRspQryUnderlyingStockInfo", pure_virtual(&TdApiWrap::onRspQryUnderlyingStockInfo))
		.def("onRspQryOTPInsCommRate", pure_virtual(&TdApiWrap::onRspQryOTPInsCommRate))
		.def("onRspQryInstrumentMarginRate", pure_virtual(&TdApiWrap::onRspQryInstrumentMarginRate))
		.def("onRspQryOTPAssignment", pure_virtual(&TdApiWrap::onRspQryOTPAssignment))
		.def("onRspQryDepthMarketData", pure_virtual(&TdApiWrap::onRspQryDepthMarketData))
		.def("onRspFromBankToStockByStock", pure_virtual(&TdApiWrap::onRspFromBankToStockByStock))
		.def("onRtnFromBankToStockByStock", pure_virtual(&TdApiWrap::onRtnFromBankToStockByStock))
		.def("onRspFromStockToBankByStock", pure_virtual(&TdApiWrap::onRspFromStockToBankByStock))
		.def("onRtnFromStockToBankByStock", pure_virtual(&TdApiWrap::onRtnFromStockToBankByStock))
		.def("onRtnQueryBankBalanceByStock", pure_virtual(&TdApiWrap::onRtnQueryBankBalanceByStock))
		.def("onRspQryContractBank", pure_virtual(&TdApiWrap::onRspQryContractBank))
		.def("onRspQueryBankAccountMoneyByStock", pure_virtual(&TdApiWrap::onRspQueryBankAccountMoneyByStock))
		.def("onRspQryTransferSerial", pure_virtual(&TdApiWrap::onRspQryTransferSerial))
		.def("onRspQrySettlementInfoConfirm", pure_virtual(&TdApiWrap::onRspQrySettlementInfoConfirm))
		.def("onRspSettlementInfoConfirm", pure_virtual(&TdApiWrap::onRspSettlementInfoConfirm))
		.def("onRspQrySettlementInfo", pure_virtual(&TdApiWrap::onRspQrySettlementInfo))
		.def("onRspQryInvestorTradeLevel", pure_virtual(&TdApiWrap::onRspQryInvestorTradeLevel))
		.def("onRspQryPurchaseLimitAmt", pure_virtual(&TdApiWrap::onRspQryPurchaseLimitAmt))
		.def("onRspQryPositionLimitVol", pure_virtual(&TdApiWrap::onRspQryPositionLimitVol))
		.def("onRspQryHistoryOrder", pure_virtual(&TdApiWrap::onRspQryHistoryOrder))
		.def("onRspQryHistoryTrade", pure_virtual(&TdApiWrap::onRspQryHistoryTrade))
		.def("onRspQryHistoryAssignment", pure_virtual(&TdApiWrap::onRspQryHistoryAssignment))
		.def("onRspQryDelivDetail", pure_virtual(&TdApiWrap::onRspQryDelivDetail))
		.def("onRspAutoExecOrderAction", pure_virtual(&TdApiWrap::onRspAutoExecOrderAction))
		.def("onRspCombActionInsert", pure_virtual(&TdApiWrap::onRspCombActionInsert))
		.def("onRspQryInvestorCombinePosition", pure_virtual(&TdApiWrap::onRspQryInvestorCombinePosition))
		.def("onRspQryCombActionVolume", pure_virtual(&TdApiWrap::onRspQryCombActionVolume))
		.def("onRspFundOutCreditApply", pure_virtual(&TdApiWrap::onRspFundOutCreditApply))
		.def("onRspQryFundOutCredit", pure_virtual(&TdApiWrap::onRspQryFundOutCredit))
		.def("onRspQryFundOutCreditApply", pure_virtual(&TdApiWrap::onRspQryFundOutCreditApply))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onRtnExecOrder", pure_virtual(&TdApiWrap::onRtnExecOrder))
		.def("onRtnLock", pure_virtual(&TdApiWrap::onRtnLock))
		.def("onRtnInstrumentStatus", pure_virtual(&TdApiWrap::onRtnInstrumentStatus))
		.def("onRtnTradingNotice", pure_virtual(&TdApiWrap::onRtnTradingNotice))
		.def("onRtnCombAction", pure_virtual(&TdApiWrap::onRtnCombAction))
		;
}
