// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#ifdef WIN32
#include "stdafx.h"
#endif
#include "vnltstd.h"



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
        #ifdef WIN32
			strcpy_s(value, strlen(buffer) + 1, buffer);
        #else
			strncpy(value, buffer, strlen(buffer) + 1);
        #endif
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

void TdApi::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CSecurityFtdcRspUserLoginField empty_data = CSecurityFtdcRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pUserLogout)
	{
		task.task_data = *pUserLogout;
	}
	else
	{
		CSecurityFtdcUserLogoutField empty_data = CSecurityFtdcUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFetchAuthRandCode(CSecurityFtdcAuthRandCodeField *pAuthRandCode, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFETCHAUTHRANDCODE;

	if (pAuthRandCode)
	{
		task.task_data = *pAuthRandCode;
	}
	else
	{
		CSecurityFtdcAuthRandCodeField empty_data = CSecurityFtdcAuthRandCodeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CSecurityFtdcInputOrderField empty_data = CSecurityFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;

	if (pInputOrderAction)
	{
		task.task_data = *pInputOrderAction;
	}
	else
	{
		CSecurityFtdcInputOrderActionField empty_data = CSecurityFtdcInputOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserPasswordUpdate(CSecurityFtdcUserPasswordUpdateField *pUserPasswordUpdate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;

	if (pUserPasswordUpdate)
	{
		task.task_data = *pUserPasswordUpdate;
	}
	else
	{
		CSecurityFtdcUserPasswordUpdateField empty_data = CSecurityFtdcUserPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspTradingAccountPasswordUpdate(CSecurityFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGACCOUNTPASSWORDUPDATE;

	if (pTradingAccountPasswordUpdate)
	{
		task.task_data = *pTradingAccountPasswordUpdate;
	}
	else
	{
		CSecurityFtdcTradingAccountPasswordUpdateField empty_data = CSecurityFtdcTradingAccountPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CSecurityFtdcOrderField *pOrder)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CSecurityFtdcOrderField empty_data = CSecurityFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CSecurityFtdcTradeField *pTrade)
{
	Task task = Task();
	task.task_name = ONRTNTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CSecurityFtdcTradeField empty_data = CSecurityFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CSecurityFtdcInputOrderField empty_data = CSecurityFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CSecurityFtdcOrderActionField *pOrderAction, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;

	if (pOrderAction)
	{
		task.task_data = *pOrderAction;
	}
	else
	{
		CSecurityFtdcOrderActionField empty_data = CSecurityFtdcOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFundOutByLiber(CSecurityFtdcInputFundTransferField *pInputFundTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFUNDOUTBYLIBER;

	if (pInputFundTransfer)
	{
		task.task_data = *pInputFundTransfer;
	}
	else
	{
		CSecurityFtdcInputFundTransferField empty_data = CSecurityFtdcInputFundTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnFundOutByLiber(CSecurityFtdcFundTransferField *pFundTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFUNDOUTBYLIBER;

	if (pFundTransfer)
	{
		task.task_data = *pFundTransfer;
	}
	else
	{
		CSecurityFtdcFundTransferField empty_data = CSecurityFtdcFundTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnFundOutByLiber(CSecurityFtdcInputFundTransferField *pInputFundTransfer, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNFUNDOUTBYLIBER;

	if (pInputFundTransfer)
	{
		task.task_data = *pInputFundTransfer;
	}
	else
	{
		CSecurityFtdcInputFundTransferField empty_data = CSecurityFtdcInputFundTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFundInByBank(CSecurityFtdcFundTransferField *pFundTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFUNDINBYBANK;

	if (pFundTransfer)
	{
		task.task_data = *pFundTransfer;
	}
	else
	{
		CSecurityFtdcFundTransferField empty_data = CSecurityFtdcFundTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFundInterTransfer(CSecurityFtdcFundInterTransferField *pFundInterTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFUNDINTERTRANSFER;

	if (pFundInterTransfer)
	{
		task.task_data = *pFundInterTransfer;
	}
	else
	{
		CSecurityFtdcFundInterTransferField empty_data = CSecurityFtdcFundInterTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnFundInterTransferSerial(CSecurityFtdcFundInterTransferSerialField *pFundInterTransferSerial)
{
	Task task = Task();
	task.task_name = ONRTNFUNDINTERTRANSFERSERIAL;

	if (pFundInterTransferSerial)
	{
		task.task_data = *pFundInterTransferSerial;
	}
	else
	{
		CSecurityFtdcFundInterTransferSerialField empty_data = CSecurityFtdcFundInterTransferSerialField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnFundInterTransfer(CSecurityFtdcFundInterTransferField *pFundInterTransfer, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNFUNDINTERTRANSFER;

	if (pFundInterTransfer)
	{
		task.task_data = *pFundInterTransfer;
	}
	else
	{
		CSecurityFtdcFundInterTransferField empty_data = CSecurityFtdcFundInterTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
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

			case ONRSPFETCHAUTHRANDCODE:
			{
				this->processRspFetchAuthRandCode(task);
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

			case ONRSPFUNDOUTBYLIBER:
			{
				this->processRspFundOutByLiber(task);
				break;
			}

			case ONRTNFUNDOUTBYLIBER:
			{
				this->processRtnFundOutByLiber(task);
				break;
			}

			case ONERRRTNFUNDOUTBYLIBER:
			{
				this->processErrRtnFundOutByLiber(task);
				break;
			}

			case ONRTNFUNDINBYBANK:
			{
				this->processRtnFundInByBank(task);
				break;
			}

			case ONRSPFUNDINTERTRANSFER:
			{
				this->processRspFundInterTransfer(task);
				break;
			}

			case ONRTNFUNDINTERTRANSFERSERIAL:
			{
				this->processRtnFundInterTransferSerial(task);
				break;
			}

			case ONERRRTNFUNDINTERTRANSFER:
			{
				this->processErrRtnFundInterTransfer(task);
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
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CSecurityFtdcRspUserLoginField task_data = any_cast<CSecurityFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["BrokerID"] = task_data.BrokerID;
	data["LoginTime"] = task_data.LoginTime;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CSecurityFtdcUserLogoutField task_data = any_cast<CSecurityFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspFetchAuthRandCode(Task task)
{
	PyLock lock;
	CSecurityFtdcAuthRandCodeField task_data = any_cast<CSecurityFtdcAuthRandCodeField>(task.task_data);
	dict data;
	data["RandCode"] = task_data.RandCode;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFetchAuthRandCode(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CSecurityFtdcInputOrderField task_data = any_cast<CSecurityFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CSecurityFtdcInputOrderActionField task_data = any_cast<CSecurityFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["FrontID"] = task_data.FrontID;
	data["BranchPBU"] = task_data.BranchPBU;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CSecurityFtdcUserPasswordUpdateField task_data = any_cast<CSecurityFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	PyLock lock;
	CSecurityFtdcTradingAccountPasswordUpdateField task_data = any_cast<CSecurityFtdcTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CSecurityFtdcOrderField task_data = any_cast<CSecurityFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["AccountID"] = task_data.AccountID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
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
	data["IsETF"] = task_data.IsETF;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["InstrumentType"] = task_data.InstrumentType;
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
	data["BranchPBU"] = task_data.BranchPBU;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CSecurityFtdcTradeField task_data = any_cast<CSecurityFtdcTradeField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
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
	data["TradeIndex"] = task_data.TradeIndex;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["TradeSource"] = task_data.TradeSource;
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
	data["BranchPBU"] = task_data.BranchPBU;
	data["PriceSource"] = task_data.PriceSource;
	data["TradingRole"] = task_data.TradingRole;
	data["TradeAmount"] = task_data.TradeAmount;

	this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CSecurityFtdcInputOrderField task_data = any_cast<CSecurityFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
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

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CSecurityFtdcOrderActionField task_data = any_cast<CSecurityFtdcOrderActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["InvestorID"] = task_data.InvestorID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["ClientID"] = task_data.ClientID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["VolumeChange"] = task_data.VolumeChange;
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["BrokerID"] = task_data.BrokerID;
	data["InstrumentType"] = task_data.InstrumentType;
	data["ActionDate"] = task_data.ActionDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["BranchPBU"] = task_data.BranchPBU;
	data["OrderActionStatus"] = task_data.OrderActionStatus;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRspFundOutByLiber(Task task)
{
	PyLock lock;
	CSecurityFtdcInputFundTransferField task_data = any_cast<CSecurityFtdcInputFundTransferField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountType"] = task_data.AccountType;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFundOutByLiber(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFundOutByLiber(Task task)
{
	PyLock lock;
	CSecurityFtdcFundTransferField task_data = any_cast<CSecurityFtdcFundTransferField>(task.task_data);
	dict data;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["ErrorID"] = task_data.ErrorID;
	data["UserID"] = task_data.UserID;
	data["TransferSerial"] = task_data.TransferSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["LiberSerial"] = task_data.LiberSerial;
	data["BrokerID"] = task_data.BrokerID;
	data["FundDirection"] = task_data.FundDirection;
	data["TradeTime"] = task_data.TradeTime;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	this->onRtnFundOutByLiber(data);
};

void TdApi::processErrRtnFundOutByLiber(Task task)
{
	PyLock lock;
	CSecurityFtdcInputFundTransferField task_data = any_cast<CSecurityFtdcInputFundTransferField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountType"] = task_data.AccountType;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFundOutByLiber(data, error);
};

void TdApi::processRtnFundInByBank(Task task)
{
	PyLock lock;
	CSecurityFtdcFundTransferField task_data = any_cast<CSecurityFtdcFundTransferField>(task.task_data);
	dict data;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["ErrorID"] = task_data.ErrorID;
	data["UserID"] = task_data.UserID;
	data["TransferSerial"] = task_data.TransferSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["LiberSerial"] = task_data.LiberSerial;
	data["BrokerID"] = task_data.BrokerID;
	data["FundDirection"] = task_data.FundDirection;
	data["TradeTime"] = task_data.TradeTime;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	this->onRtnFundInByBank(data);
};

void TdApi::processRspFundInterTransfer(Task task)
{
	PyLock lock;
	CSecurityFtdcFundInterTransferField task_data = any_cast<CSecurityFtdcFundInterTransferField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFundInterTransfer(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFundInterTransferSerial(Task task)
{
	PyLock lock;
	CSecurityFtdcFundInterTransferSerialField task_data = any_cast<CSecurityFtdcFundInterTransferSerialField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["TransferTime"] = task_data.TransferTime;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ErrorID"] = task_data.ErrorID;
	data["AccountID"] = task_data.AccountID;

	this->onRtnFundInterTransferSerial(data);
};

void TdApi::processErrRtnFundInterTransfer(Task task)
{
	PyLock lock;
	CSecurityFtdcFundInterTransferField task_data = any_cast<CSecurityFtdcFundInterTransferField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFundInterTransfer(data, error);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	this->api = CSecurityFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
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
	SECURITY_TE_RESUME_TYPE type;

	switch (nType)
	{
		case 0:
		{
			type = SECURITY_TERT_RESTART;
			break;
		};

		case 1:
		{
			type = SECURITY_TERT_RESUME;
			break;
		};

		case 2:
		{
			type = SECURITY_TERT_QUICK;
			break;
		};
	}

	this->api->SubscribePrivateTopic(type);


};

void TdApi::subscribePublicTopic(int nType)
{
	//该函数为手动编写
	SECURITY_TE_RESUME_TYPE type;

	switch (nType)
	{
		case 0:
		{
			type = SECURITY_TERT_RESTART;
			break;
		};

		case 1:
		{
			type = SECURITY_TERT_RESUME;
			break;
		};

		case 2:
		{
			type = SECURITY_TERT_QUICK;
			break;
		};
	}

	this->api->SubscribePublicTopic(type);
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CSecurityFtdcReqUserLoginField myreq = CSecurityFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
	getChar(req, "RandCode", myreq.RandCode);
	getChar(req, "UserProductInfo", myreq.UserProductInfo);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "AuthCode", myreq.AuthCode);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientIPAddress", myreq.ClientIPAddress);
	getChar(req, "OneTimePassword", myreq.OneTimePassword);
	getChar(req, "ProtocolInfo", myreq.ProtocolInfo);
	getChar(req, "Password", myreq.Password);
	getChar(req, "HDSerialNumber", myreq.HDSerialNumber);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CSecurityFtdcUserLogoutField myreq = CSecurityFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqFetchAuthRandCode(dict req, int nRequestID)
{
	CSecurityFtdcAuthRandCodeField myreq = CSecurityFtdcAuthRandCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "RandCode", myreq.RandCode);
	int i = this->api->ReqFetchAuthRandCode(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CSecurityFtdcInputOrderField myreq = CSecurityFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	//getChar(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "LimitPrice", myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getChar(req, "GTDDate", myreq.GTDDate);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "Direction", &myreq.Direction);

	//处理CombOffsetFlag
	if (req.has_key("CombOffsetFlag"))
	{
		object o2 = req["CombOffsetFlag"];
		extract<string> x2(o2);
		if (x2.check())
		{
			string s2 = x2();
			const char *buffer2 = s2.c_str();
			myreq.CombOffsetFlag[0] = *buffer2;
		}
	}

	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CSecurityFtdcInputOrderActionField myreq = CSecurityFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OrderLocalID", myreq.OrderLocalID);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "FrontID", &myreq.FrontID);
	getChar(req, "BranchPBU", myreq.BranchPBU);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CSecurityFtdcUserPasswordUpdateField myreq = CSecurityFtdcUserPasswordUpdateField();
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
	CSecurityFtdcTradingAccountPasswordUpdateField myreq = CSecurityFtdcTradingAccountPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqTradingAccountPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqFundOutByLiber(dict req, int nRequestID)
{
	CSecurityFtdcInputFundTransferField myreq = CSecurityFtdcInputFundTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountType", &myreq.AccountType);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Digest", myreq.Digest);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqFundOutByLiber(&myreq, nRequestID);
	return i;
};

int TdApi::reqFundInterTransfer(dict req, int nRequestID)
{
	CSecurityFtdcFundInterTransferField myreq = CSecurityFtdcFundInterTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SerialID", &myreq.SerialID);
	getChar(req, "TransferType", &myreq.TransferType);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Password", myreq.Password);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqFundInterTransfer(&myreq, nRequestID);
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

	virtual void onRspFetchAuthRandCode(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFetchAuthRandCode")(data, error, id, last);
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

	virtual void onRspFundOutByLiber(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFundOutByLiber")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFundOutByLiber(dict data)
	{
		try
		{
			this->get_override("onRtnFundOutByLiber")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnFundOutByLiber(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnFundOutByLiber")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFundInByBank(dict data)
	{
		try
		{
			this->get_override("onRtnFundInByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFundInterTransfer(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFundInterTransfer")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFundInterTransferSerial(dict data)
	{
		try
		{
			this->get_override("onRtnFundInterTransferSerial")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onErrRtnFundInterTransfer(dict data, dict error)
	{
		try
		{
			this->get_override("onErrRtnFundInterTransfer")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnltstd)
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
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqFetchAuthRandCode", &TdApiWrap::reqFetchAuthRandCode)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqUserPasswordUpdate", &TdApiWrap::reqUserPasswordUpdate)
		.def("reqTradingAccountPasswordUpdate", &TdApiWrap::reqTradingAccountPasswordUpdate)
		.def("reqFundOutByLiber", &TdApiWrap::reqFundOutByLiber)
		.def("reqFundInterTransfer", &TdApiWrap::reqFundInterTransfer)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&TdApiWrap::onHeartBeatWarning))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspFetchAuthRandCode", pure_virtual(&TdApiWrap::onRspFetchAuthRandCode)) 
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onRspUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspUserPasswordUpdate))
		.def("onRspTradingAccountPasswordUpdate", pure_virtual(&TdApiWrap::onRspTradingAccountPasswordUpdate))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onErrRtnOrderInsert", pure_virtual(&TdApiWrap::onErrRtnOrderInsert))
		.def("onErrRtnOrderAction", pure_virtual(&TdApiWrap::onErrRtnOrderAction))
		.def("onRspFundOutByLiber", pure_virtual(&TdApiWrap::onRspFundOutByLiber))
		.def("onRtnFundOutByLiber", pure_virtual(&TdApiWrap::onRtnFundOutByLiber))
		.def("onErrRtnFundOutByLiber", pure_virtual(&TdApiWrap::onErrRtnFundOutByLiber))
		.def("onRtnFundInByBank", pure_virtual(&TdApiWrap::onRtnFundInByBank))
		.def("onRspFundInterTransfer", pure_virtual(&TdApiWrap::onRspFundInterTransfer))
		.def("onRtnFundInterTransferSerial", pure_virtual(&TdApiWrap::onRtnFundInterTransferSerial))
		.def("onErrRtnFundInterTransfer", pure_virtual(&TdApiWrap::onErrRtnFundInterTransfer))
		;
}
