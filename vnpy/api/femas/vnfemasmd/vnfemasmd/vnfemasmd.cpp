// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnfemasmd.h"

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
};



///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void MdApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_id = nTimeLapse;
	this->task_queue.push(task);
};

void MdApi::OnPackageStart(int nTopicID, int nSequenceNo)
{
	//该函数忽略
};

void MdApi::OnPackageEnd(int nTopicID, int nSequenceNo)
{
	//该函数忽略
};

void MdApi::OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void MdApi::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	task.task_data = *pRspUserLogin;
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

void MdApi::OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;
	task.task_data = *pRspUserLogout;
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

void MdApi::OnRspSubscribeTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBETOPIC;
	task.task_data = *pDissemination;
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

void MdApi::OnRspQryTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTOPIC;
	task.task_data = *pDissemination;
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

void MdApi::OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField *pDepthMarketData)
{
	Task task = Task();
	task.task_name = ONRTNDEPTHMARKETDATA;
	task.task_data = *pDepthMarketData;
	this->task_queue.push(task);
};

void MdApi::OnRspSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBMARKETDATA;
	task.task_data = *pSpecificInstrument;
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

void MdApi::OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBMARKETDATA;
	task.task_data = *pSpecificInstrument;
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

void MdApi::processTask()
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

		case ONRTNDEPTHMARKETDATA:
		{
			this->processRtnDepthMarketData(task);
			break;
		}

		case ONRSPSUBMARKETDATA:
		{
			this->processRspSubMarketData(task);
			break;
		}

		case ONRSPUNSUBMARKETDATA:
		{
			this->processRspUnSubMarketData(task);
			break;
		}
		};
	}
};

void MdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void MdApi::processHeartBeatWarning(Task task)
{
	PyLock lock;
	this->onHeartBeatWarning(task.task_id);
};

void MdApi::processRspError(Task task)
{
	PyLock lock;
	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogin(Task task)
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

void MdApi::processRspUserLogout(Task task)
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

void MdApi::processRspSubscribeTopic(Task task)
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

void MdApi::processRspQryTopic(Task task)
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

void MdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CUstpFtdcDepthMarketDataField task_data = any_cast<CUstpFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["HighestPrice"] = task_data.HighestPrice;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidPrice1"] = task_data.BidPrice1;
	data["BidPrice3"] = task_data.BidPrice3;
	data["BidPrice2"] = task_data.BidPrice2;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["SettlementGroupID"] = task_data.SettlementGroupID;
	data["BidVolume2"] = task_data.BidVolume2;
	data["BidVolume1"] = task_data.BidVolume1;
	data["AskPrice2"] = task_data.AskPrice2;
	data["Volume"] = task_data.Volume;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["AskVolume5"] = task_data.AskVolume5;
	data["AskVolume4"] = task_data.AskVolume4;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["BidPrice4"] = task_data.BidPrice4;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["SettlementID"] = task_data.SettlementID;
	data["TradingDay"] = task_data.TradingDay;
	data["PreDelta"] = task_data.PreDelta;
	data["OpenInterest"] = task_data.OpenInterest;
	data["CurrDelta"] = task_data.CurrDelta;
	data["Turnover"] = task_data.Turnover;
	data["LastPrice"] = task_data.LastPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["OpenPrice"] = task_data.OpenPrice;
	data["LowestPrice"] = task_data.LowestPrice;

	this->onRtnDepthMarketData(data);
};

void MdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	CUstpFtdcSpecificInstrumentField task_data = any_cast<CUstpFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	CUstpFtdcSpecificInstrumentField task_data = any_cast<CUstpFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CUstpFtdcRspInfoField task_error = any_cast<CUstpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubMarketData(data, error, task.task_id, task.task_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createFtdcMdApi(string pszFlowPath)
{
	this->api = CUstpFtdcMduserApi::CreateFtdcMduserApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void MdApi::release()
{
	this->api->Release();
};

void MdApi::init()
{
	this->api->Init();
};

int MdApi::join()
{
	int i = this->api->Join();
	return i;
};

int MdApi::exit()
{
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string MdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

void MdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void MdApi::registerNameServer(string pszNsAddress)
{
	this->api->RegisterNameServer((char*)pszNsAddress.c_str());
};

int MdApi::registerCertificateFile(string pszCertFileName, string pszKeyFileName, string pszCaFileName, string pszKeyFilePassword)
{
	int i = this->api->RegisterCertificateFile(pszCertFileName.c_str(), pszKeyFileName.c_str(), pszCaFileName.c_str(), pszKeyFilePassword.c_str());
	return i;
}

void MdApi::subscribeMarketDataTopic(int topicID, int resumeType)
{
	switch (resumeType)
	{
		case 0:
		{
			this->api->SubscribeMarketDataTopic(topicID, USTP_TERT_RESTART);
			break;
		}

		case 1:
		{
			this->api->SubscribeMarketDataTopic(topicID, USTP_TERT_RESUME);
			break;
		}

		case 2:
		{
			this->api->SubscribeMarketDataTopic(topicID, USTP_TERT_QUICK);
			break;
		}
	}
}

int MdApi::subMarketData(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubMarketData(myreq, 1);
	return i;
}

int MdApi::unSubMarketData(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubMarketData(myreq, 1);
	return i;
}

void MdApi::setHeartbeatTimeout(int timeout)
{
	this->api->SetHeartbeatTimeout(timeout);
}


int MdApi::reqSubMarketData(dict req, int nRequestID)
{
	CUstpFtdcSpecificInstrumentField myreq = CUstpFtdcSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqSubMarketData(&myreq, nRequestID);
	return i;
};

int MdApi::reqUnSubMarketData(dict req, int nRequestID)
{
	CUstpFtdcSpecificInstrumentField myreq = CUstpFtdcSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqUnSubMarketData(&myreq, nRequestID);
	return i;
};

int MdApi::reqQryTopic(dict req, int nRequestID)
{
	CUstpFtdcDisseminationField myreq = CUstpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqQryTopic(&myreq, nRequestID);
	return i;
};

int MdApi::reqUserLogin(dict req, int nRequestID)
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

int MdApi::reqUserLogout(dict req, int nRequestID)
{
	CUstpFtdcReqUserLogoutField myreq = CUstpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int MdApi::reqSubscribeTopic(dict req, int nRequestID)
{
	CUstpFtdcDisseminationField myreq = CUstpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqSubscribeTopic(&myreq, nRequestID);
	return i;
};


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

	virtual void onFrontDisconnected(int i)
	{
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
		try
		{
			this->get_override("onHeartBeatWarning")(i);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspError(dict data, int id, bool last)
	{
		try
		{
			this->get_override("onRspError")(data, id, last);
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

	virtual void onRspSubMarketData(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspSubMarketData")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUnSubMarketData(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspUnSubMarketData")(data, error, id, last);
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

	virtual void onRtnDepthMarketData(dict data)
	{
		try
		{
			this->get_override("onRtnDepthMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnfemasmd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<MdApiWrap, boost::noncopyable>("MdApi")
		.def("createFtdcMdApi", &MdApiWrap::createFtdcMdApi)
		.def("release", &MdApiWrap::release)
		.def("init", &MdApiWrap::init)
		.def("join", &MdApiWrap::join)
		.def("exit", &MdApiWrap::exit)
		.def("getTradingDay", &MdApiWrap::getTradingDay)
		.def("registerFront", &MdApiWrap::registerFront)
		.def("registerNameServer", &MdApiWrap::registerNameServer)
		.def("registerCertificateFile", &MdApiWrap::registerCertificateFile)
		.def("subscribeMarketDataTopic", &MdApiWrap::subscribeMarketDataTopic)
		.def("subMarketData", &MdApiWrap::subMarketData)
		.def("unSubMarketData", &MdApiWrap::unSubMarketData)
		.def("setHeartbeatTimeout", &MdApiWrap::setHeartbeatTimeout)
		.def("reqSubMarketData", &MdApiWrap::reqSubMarketData)
		.def("reqUnSubMarketData", &MdApiWrap::reqUnSubMarketData)
		.def("reqUserLogin", &MdApiWrap::reqUserLogin)
		.def("reqUserLogout", &MdApiWrap::reqUserLogout)
		.def("reqQryTopic", &MdApiWrap::reqQryTopic)
		.def("reqSubscribeTopic", &MdApiWrap::reqSubscribeTopic)

		.def("onFrontConnected", pure_virtual(&MdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&MdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&MdApiWrap::onHeartBeatWarning))
		.def("onRspError", pure_virtual(&MdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&MdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&MdApiWrap::onRspUserLogout))

		.def("onRspSubMarketData", pure_virtual(&MdApiWrap::onRspSubMarketData))
		.def("onRspUnSubMarketData", pure_virtual(&MdApiWrap::onRspUnSubMarketData))
		.def("onRtnDepthMarketData", pure_virtual(&MdApiWrap::onRtnDepthMarketData))
		
		.def("onRspQryTopic", pure_virtual(&MdApiWrap::onRspQryTopic))
		.def("onRspSubscribeTopic", pure_virtual(&MdApiWrap::onRspSubscribeTopic))
		;
};