// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnsecmd.h"


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
};

void getLong(dict d, string key, long *value)
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
};

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
};

void getString(dict d, string key, char *value)
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
};



///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnFrontConnected()
{
	Task *task = new Task();
	task->task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nReason)
{
	Task *task = new Task();
	task->task_name = ONFRONTDISCONNECTED;

	if (nReason)
	{
		task->task_id = nReason;
	}
	this->task_queue.push(task);
};

void MdApi::OnRtnNotice(DFITCSECRspNoticeField *pNotice)
{
	Task *task = new Task();
	task->task_name = ONRTNNOTICE;

	if (pNotice)
	{
		DFITCSECRspNoticeField *task_data = new DFITCSECRspNoticeField();
		*task_data = *pNotice;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspError(struct DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPERROR;

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspStockUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKUSERLOGIN;

	if (pRspUserLogin)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pRspUserLogin;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspStockUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKUSERLOGOUT;

	if (pRspUsrLogout)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pRspUsrLogout;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspSOPUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPUSERLOGIN;

	if (pRspUserLogin)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pRspUserLogin;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspSOPUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPUSERLOGOUT;

	if (pRspUsrLogout)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pRspUsrLogout;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspFASLUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLUSERLOGIN;

	if (pRspUserLogin)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pRspUserLogin;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspFASLUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLUSERLOGOUT;

	if (pRspUsrLogout)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pRspUsrLogout;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspStockSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspStockUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKUNSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspSOPSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspSOPUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPUNSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void MdApi::OnStockMarketData(struct DFITCStockDepthMarketDataField * pMarketDataField)
{
	Task *task = new Task();
	task->task_name = ONSTOCKMARKETDATA;

	if (pMarketDataField)
	{
		DFITCStockDepthMarketDataField *task_data = new DFITCStockDepthMarketDataField();
		*task_data = *pMarketDataField;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnSOPMarketData(struct DFITCSOPDepthMarketDataField * pMarketDataField)
{
	Task *task = new Task();
	task->task_name = ONSOPMARKETDATA;

	if (pMarketDataField)
	{
		DFITCSOPDepthMarketDataField *task_data = new DFITCSOPDepthMarketDataField();
		*task_data = *pMarketDataField;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspStockAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKAVAILABLEQUOT;

	if (pAvailableQuotInfo)
	{
		DFITCRspQuotQryField *task_data = new DFITCRspQuotQryField();
		*task_data = *pAvailableQuotInfo;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = flag;
	this->task_queue.push(task);
};

void MdApi::OnRspSopAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPAVAILABLEQUOT;

	if (pAvailableQuotInfo)
	{
		DFITCRspQuotQryField *task_data = new DFITCRspQuotQryField();
		*task_data = *pAvailableQuotInfo;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = flag;
	this->task_queue.push(task);
};

void MdApi::OnRspUserMDPasswordUpdate(struct DFITCSECRspMDPasswordUpdateField *pMDPasswordUpdate, struct DFITCSECRspInfoField * pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPUSERMDPASSWORDUPDATE;

	if (pMDPasswordUpdate)
	{
		DFITCSECRspMDPasswordUpdateField *task_data = new DFITCSECRspMDPasswordUpdateField();
		*task_data = *pMDPasswordUpdate;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void MdApi::processTask()
{
	while (1)
	{
		Task *task = this->task_queue.wait_and_pop();
		
		switch (task->task_name)
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

		case ONRTNNOTICE:
		{
			this->processRtnNotice(task);
			break;
		}

		case ONRSPERROR:
		{
			this->processRspError(task);
			break;
		}

		case ONRSPSTOCKUSERLOGIN:
		{
			this->processRspStockUserLogin(task);
			break;
		}

		case ONRSPSTOCKUSERLOGOUT:
		{
			this->processRspStockUserLogout(task);
			break;
		}

		case ONRSPSOPUSERLOGIN:
		{
			this->processRspSOPUserLogin(task);
			break;
		}

		case ONRSPSOPUSERLOGOUT:
		{
			this->processRspSOPUserLogout(task);
			break;
		}

		case ONRSPFASLUSERLOGIN:
		{
			this->processRspFASLUserLogin(task);
			break;
		}

		case ONRSPFASLUSERLOGOUT:
		{
			this->processRspFASLUserLogout(task);
			break;
		}

		case ONRSPSTOCKSUBMARKETDATA:
		{
			this->processRspStockSubMarketData(task);
			break;
		}

		case ONRSPSTOCKUNSUBMARKETDATA:
		{
			this->processRspStockUnSubMarketData(task);
			break;
		}

		case ONRSPSOPSUBMARKETDATA:
		{
			this->processRspSOPSubMarketData(task);
			break;
		}

		case ONRSPSOPUNSUBMARKETDATA:
		{
			this->processRspSOPUnSubMarketData(task);
			break;
		}

		case ONSTOCKMARKETDATA:
		{
			this->processStockMarketData(task);
			break;
		}

		case ONSOPMARKETDATA:
		{
			this->processSOPMarketData(task);
			break;
		}

		case ONRSPSTOCKAVAILABLEQUOT:
		{
			this->processRspStockAvailableQuot(task);
			break;
		}

		case ONRSPSOPAVAILABLEQUOT:
		{
			this->processRspSopAvailableQuot(task);
			break;
		}

		case ONRSPUSERMDPASSWORDUPDATE:
		{
			this->processRspUserMDPasswordUpdate(task);
			break;
		}

		};
	}
};

void MdApi::processFrontConnected(Task *task)
{
	PyLock lock;
	this->onFrontConnected();
	delete task;
};

void MdApi::processFrontDisconnected(Task *task)
{
	PyLock lock;
	this->onFrontDisconnected(task->task_id);
	delete task;
};

void MdApi::processRtnNotice(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspNoticeField *task_data = (DFITCSECRspNoticeField*)task->task_data;
		data["noticeMsg"] = task_data->noticeMsg;
		delete task->task_data;
	}

	this->onRtnNotice(data);
	delete task;
};

void MdApi::processRspError(Task *task)
{
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspError(error);
	delete task;
};

void MdApi::processRspStockUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogin(data, error);
	delete task;
};

void MdApi::processRspStockUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogout(data, error);
	delete task;
};

void MdApi::processRspSOPUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogin(data, error);
	delete task;
};

void MdApi::processRspSOPUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogout(data, error);
	delete task;
};

void MdApi::processRspFASLUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogin(data, error);
	delete task;
};

void MdApi::processRspFASLUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogout(data, error);
	delete task;
};

void MdApi::processRspStockSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockSubMarketData(data, error);
	delete task;
};

void MdApi::processRspStockUnSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUnSubMarketData(data, error);
	delete task;
};

void MdApi::processRspSOPSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPSubMarketData(data, error);
	delete task;
};

void MdApi::processRspSOPUnSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUnSubMarketData(data, error);
	delete task;
};

void MdApi::processStockMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockDepthMarketDataField *task_data = (DFITCStockDepthMarketDataField*)task->task_data;

		data["peRadio1"] = task_data->specificDataField.peRadio1;
		data["peRadio2"] = task_data->specificDataField.peRadio2;

		data["securityID"] = task_data->staticDataField.securityID;
		data["securityName"] = task_data->staticDataField.securityName;
		data["tradingDay"] = task_data->staticDataField.tradingDay;
		data["exchangeID"] = task_data->staticDataField.exchangeID;
		data["preClosePrice"] = task_data->staticDataField.preClosePrice;
		data["openPrice"] = task_data->staticDataField.openPrice;
		data["upperLimitPrice"] = task_data->staticDataField.upperLimitPrice;
		data["lowerLimitPrice"] = task_data->staticDataField.lowerLimitPrice;

		data["latestPrice"] = task_data->sharedDataField.latestPrice;
		data["turnover"] = task_data->sharedDataField.turnover;
		data["highestPrice"] = task_data->sharedDataField.highestPrice;
		data["lowestPrice"] = task_data->sharedDataField.lowestPrice;
		data["tradeQty"] = task_data->sharedDataField.tradeQty;
		data["updateTime"] = task_data->sharedDataField.updateTime;
		data["bidPrice1"] = task_data->sharedDataField.bidPrice1;
		data["bidQty1"] = task_data->sharedDataField.bidQty1;
		data["askPrice1"] = task_data->sharedDataField.askPrice1;
		data["askQty1"] = task_data->sharedDataField.askQty1;
		data["bidPrice2"] = task_data->sharedDataField.bidPrice2;
		data["bidQty2"] = task_data->sharedDataField.bidQty2;
		data["askPrice2"] = task_data->sharedDataField.askPrice2;
		data["askQty2"] = task_data->sharedDataField.askQty2;
		data["bidPrice3"] = task_data->sharedDataField.bidPrice3;
		data["bidQty3"] = task_data->sharedDataField.bidQty3;
		data["askPrice3"] = task_data->sharedDataField.askPrice3;
		data["askQty3"] = task_data->sharedDataField.askQty3;
		data["bidPrice4"] = task_data->sharedDataField.bidPrice4;
		data["bidQty4"] = task_data->sharedDataField.bidQty4;
		data["askPrice4"] = task_data->sharedDataField.askPrice4;
		data["askQty4"] = task_data->sharedDataField.askQty4;
		data["bidPrice5"] = task_data->sharedDataField.bidPrice5;
		data["bidQty5"] = task_data->sharedDataField.bidQty5;
		data["askPrice5"] = task_data->sharedDataField.askPrice5;
		data["askQty5"] = task_data->sharedDataField.askQty5;
		data["tradingPhaseCode"] = task_data->sharedDataField.tradingPhaseCode;

		delete task->task_data;
	}

	this->onStockMarketData(data);
	delete task;
};

void MdApi::processSOPMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPDepthMarketDataField *task_data = (DFITCSOPDepthMarketDataField*)task->task_data;

		data["contractID"] = task_data->specificDataField.contractID;
		data["execPrice"] = task_data->specificDataField.execPrice;
		data["preSettlePrice"] = task_data->specificDataField.preSettlePrice;
		data["settlePrice"] = task_data->specificDataField.settlePrice;
		data["positionQty"] = task_data->specificDataField.positionQty;
		data["auctionPrice"] = task_data->specificDataField.auctionPrice;
		data["latestEnquiryTime"] = task_data->specificDataField.latestEnquiryTime;

		data["securityID"] = task_data->staticDataField.securityID;
		data["securityName"] = task_data->staticDataField.securityName;
		data["tradingDay"] = task_data->staticDataField.tradingDay;
		data["exchangeID"] = task_data->staticDataField.exchangeID;
		data["preClosePrice"] = task_data->staticDataField.preClosePrice;
		data["openPrice"] = task_data->staticDataField.openPrice;
		data["upperLimitPrice"] = task_data->staticDataField.upperLimitPrice;
		data["lowerLimitPrice"] = task_data->staticDataField.lowerLimitPrice;

		data["latestPrice"] = task_data->sharedDataField.latestPrice;
		data["turnover"] = task_data->sharedDataField.turnover;
		data["highestPrice"] = task_data->sharedDataField.highestPrice;
		data["lowestPrice"] = task_data->sharedDataField.lowestPrice;
		data["tradeQty"] = task_data->sharedDataField.tradeQty;
		data["updateTime"] = task_data->sharedDataField.updateTime;
		data["bidPrice1"] = task_data->sharedDataField.bidPrice1;
		data["bidQty1"] = task_data->sharedDataField.bidQty1;
		data["askPrice1"] = task_data->sharedDataField.askPrice1;
		data["askQty1"] = task_data->sharedDataField.askQty1;
		data["bidPrice2"] = task_data->sharedDataField.bidPrice2;
		data["bidQty2"] = task_data->sharedDataField.bidQty2;
		data["askPrice2"] = task_data->sharedDataField.askPrice2;
		data["askQty2"] = task_data->sharedDataField.askQty2;
		data["bidPrice3"] = task_data->sharedDataField.bidPrice3;
		data["bidQty3"] = task_data->sharedDataField.bidQty3;
		data["askPrice3"] = task_data->sharedDataField.askPrice3;
		data["askQty3"] = task_data->sharedDataField.askQty3;
		data["bidPrice4"] = task_data->sharedDataField.bidPrice4;
		data["bidQty4"] = task_data->sharedDataField.bidQty4;
		data["askPrice4"] = task_data->sharedDataField.askPrice4;
		data["askQty4"] = task_data->sharedDataField.askQty4;
		data["bidPrice5"] = task_data->sharedDataField.bidPrice5;
		data["bidQty5"] = task_data->sharedDataField.bidQty5;
		data["askPrice5"] = task_data->sharedDataField.askPrice5;
		data["askQty5"] = task_data->sharedDataField.askQty5;
		data["tradingPhaseCode"] = task_data->sharedDataField.tradingPhaseCode;


		delete task->task_data;
	}

	this->onSOPMarketData(data);
	delete task;
};

void MdApi::processRspStockAvailableQuot(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockAvailableQuot(data, error, task->task_last);
	delete task;
};

void MdApi::processRspSopAvailableQuot(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSopAvailableQuot(data, error, task->task_last);
	delete task;
};

void MdApi::processRspUserMDPasswordUpdate(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspMDPasswordUpdateField *task_data = (DFITCSECRspMDPasswordUpdateField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspUserMDPasswordUpdate(data, error);
	delete task;
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createDFITCMdApi(string logAddr)
{
	this->api = DFITCSECMdApi::CreateDFITCMdApi(logAddr.c_str());
};

void MdApi::init(string pszSvrAddr)
{
	this->api->Init(pszSvrAddr.c_str(), this);
};

void MdApi::release()
{
	this->api->Release();
};

int MdApi::exit()
{
	this->api->Release();
	this->api = NULL;
	return 1;
};

int MdApi::subscribeStockMarketData(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeStockMarketData(myreq, 1, nRequestID);
	return i;
};

int MdApi::unSubscribeStockMarketData(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeStockMarketData(myreq, 1, nRequestID);
	return i;
};

int MdApi::subscribeSOPMarketData(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeSOPMarketData(myreq, 1, nRequestID);
	return i;
};

int MdApi::unSubscribeSOPMarketData(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeSOPMarketData(myreq, 1, nRequestID);
	return i;
};

int MdApi::reqStockUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqStockUserLogin(&myreq);
	return i;
};

int MdApi::reqStockUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockUserLogout(&myreq);
	return i;
};

int MdApi::reqSOPUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqSOPUserLogin(&myreq);
	return i;
};

int MdApi::reqFASLUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqFASLUserLogin(&myreq);
	return i;
};

int MdApi::reqSOPUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqSOPUserLogout(&myreq);
	return i;
};

int MdApi::reqFASLUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLUserLogout(&myreq);
	return i;
};

int MdApi::reqUserMDPasswordUpdate(dict req)
{
	DFITCSECReqMDPasswordUpdateField myreq = DFITCSECReqMDPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "oldPassword", myreq.oldPassword);
	getString(req, "newPassword", myreq.newPassword);
	int i = this->api->ReqUserMDPasswordUpdate(&myreq);
	return i;
};

int MdApi::reqStockAvailableQuotQry(dict req)
{
	DFITCReqQuotQryField myreq = DFITCReqQuotQryField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqStockAvailableQuotQry(&myreq);
	return i;
}

int MdApi::reqSopAvailableQuotQry(dict req)
{
	DFITCReqQuotQryField myreq = DFITCReqQuotQryField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqSopAvailableQuotQry(&myreq);
	return i;
}



///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct MdApiWrap : MdApi, wrapper < MdApi >
{
	virtual void onFrontConnected()
	{
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

	virtual void onFrontDisconnected(int reason)
	{
		try
		{
			this->get_override("onFrontDisconnected")(reason);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnNotice(dict data)
	{
		try
		{
			this->get_override("onRtnNotice")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspError(dict error)
	{
		try
		{
			this->get_override("onRspError")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockUserLogout")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPUserLogout")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLUserLogout")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockSubMarketData(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockSubMarketData")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockUnSubMarketData(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockUnSubMarketData")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPSubMarketData(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPSubMarketData")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPUnSubMarketData(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPUnSubMarketData")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onStockMarketData(dict data)
	{
		try
		{
			this->get_override("onStockMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onSOPMarketData(dict data)
	{
		try
		{
			this->get_override("onSOPMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockAvailableQuot(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockAvailableQuot")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSopAvailableQuot(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSopAvailableQuot")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserMDPasswordUpdate(dict data, dict error)
	{
		try
		{
			this->get_override("onRspUserMDPasswordUpdate")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnsecmd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<MdApiWrap, boost::noncopyable>("MdApi")
		.def("createDFITCMdApi", &MdApiWrap::createDFITCMdApi)
		.def("init", &MdApiWrap::init)
		.def("release", &MdApiWrap::release)
		.def("exit", &MdApiWrap::exit)
		.def("subscribeStockMarketData", &MdApiWrap::subscribeStockMarketData)
		.def("unSubscribeStockMarketData", &MdApiWrap::unSubscribeStockMarketData)
		.def("subscribeSOPMarketData", &MdApiWrap::subscribeSOPMarketData)
		.def("unSubscribeSOPMarketData", &MdApiWrap::unSubscribeSOPMarketData)
		.def("reqStockUserLogin", &MdApiWrap::reqStockUserLogin)
		.def("reqStockUserLogout", &MdApiWrap::reqStockUserLogout)
		.def("reqSOPUserLogin", &MdApiWrap::reqSOPUserLogin)
		.def("reqFASLUserLogin", &MdApiWrap::reqFASLUserLogin)
		.def("reqSOPUserLogout", &MdApiWrap::reqSOPUserLogout)
		.def("reqFASLUserLogout", &MdApiWrap::reqFASLUserLogout)
		.def("reqStockAvailableQuotQry", &MdApiWrap::reqStockAvailableQuotQry)
		.def("reqSopAvailableQuotQry", &MdApiWrap::reqSopAvailableQuotQry)
		.def("reqUserMDPasswordUpdate", &MdApiWrap::reqUserMDPasswordUpdate)

		.def("onFrontConnected", pure_virtual(&MdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&MdApiWrap::onFrontDisconnected))
		.def("onRtnNotice", pure_virtual(&MdApiWrap::onRtnNotice))
		.def("onRspError", pure_virtual(&MdApiWrap::onRspError))
		.def("onRspStockUserLogin", pure_virtual(&MdApiWrap::onRspStockUserLogin))
		.def("onRspStockUserLogout", pure_virtual(&MdApiWrap::onRspStockUserLogout))
		.def("onRspSOPUserLogin", pure_virtual(&MdApiWrap::onRspSOPUserLogin))
		.def("onRspSOPUserLogout", pure_virtual(&MdApiWrap::onRspSOPUserLogout))
		.def("onRspFASLUserLogin", pure_virtual(&MdApiWrap::onRspFASLUserLogin))
		.def("onRspFASLUserLogout", pure_virtual(&MdApiWrap::onRspFASLUserLogout))
		.def("onRspStockSubMarketData", pure_virtual(&MdApiWrap::onRspStockSubMarketData))
		.def("onRspStockUnSubMarketData", pure_virtual(&MdApiWrap::onRspStockUnSubMarketData))
		.def("onRspSOPSubMarketData", pure_virtual(&MdApiWrap::onRspSOPSubMarketData))
		.def("onRspSOPUnSubMarketData", pure_virtual(&MdApiWrap::onRspSOPUnSubMarketData))
		.def("onStockMarketData", pure_virtual(&MdApiWrap::onStockMarketData))
		.def("onSOPMarketData", pure_virtual(&MdApiWrap::onSOPMarketData))
		.def("onRspStockAvailableQuot", pure_virtual(&MdApiWrap::onRspStockAvailableQuot))
		.def("onRspSopAvailableQuot", pure_virtual(&MdApiWrap::onRspSopAvailableQuot))
		.def("onRspUserMDPasswordUpdate", pure_virtual(&MdApiWrap::onRspUserMDPasswordUpdate))
		;
};