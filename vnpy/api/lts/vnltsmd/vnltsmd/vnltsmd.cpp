// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#ifdef WIN32
#include "stdafx.h"
#endif
#include "vnltsmd.h"



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
        #ifdef WIN32
			strcpy_s(value, strlen(buffer) + 1, buffer);
        #else
			strncpy(value, buffer, strlen(buffer) + 1);
        #endif
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

void MdApi::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void MdApi::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;
	task.task_data = *pUserLogout;
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

void MdApi::OnRspSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRtnDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData)
{
	Task task = Task();
	task.task_name = ONRTNDEPTHMARKETDATA;
	task.task_data = *pDepthMarketData;
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

			case ONRTNDEPTHMARKETDATA:
			{
				this->processRtnDepthMarketData(task);
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
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogin(Task task)
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

void MdApi::processRspUserLogout(Task task)
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

void MdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CSecurityFtdcDepthMarketDataField task_data = any_cast<CSecurityFtdcDepthMarketDataField>(task.task_data);
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
	data["PreIOPV"] = task_data.PreIOPV;
	data["TradingDay"] = task_data.TradingDay;
	data["IOPV"] = task_data.IOPV;
	data["PreDelta"] = task_data.PreDelta;
	data["OpenInterest"] = task_data.OpenInterest;
	data["CurrDelta"] = task_data.CurrDelta;
	data["Turnover"] = task_data.Turnover;
	data["LastPrice"] = task_data.LastPrice;
	data["OpenRestriction"] = task_data.OpenRestriction;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["TradingPhase"] = task_data.TradingPhase;
	data["LowestPrice"] = task_data.LowestPrice;
	data["AuctionPrice"] = task_data.AuctionPrice;
	data["ActionDay"] = task_data.ActionDay;

	this->onRtnDepthMarketData(data);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createFtdcMdApi(string pszFlowPath)
{
	this->api = CSecurityFtdcMdApi::CreateFtdcMdApi(pszFlowPath.c_str());
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

int MdApi::subscribeMarketData(dict req)
{
	char instrumentID[256];
	char exchangeID[256];
	getChar(req, "InstrumentID", instrumentID);
	getChar(req, "ExchangeID", exchangeID);
	char* myreq[1] = { instrumentID };
	int i = this->api->SubscribeMarketData(myreq, 1, exchangeID);
	return i;
};

int MdApi::unSubscribeMarketData(dict req)
{
	char instrumentID[256];
	char exchangeID[256];
	getChar(req, "InstrumentID", instrumentID);
	getChar(req, "ExchangeID", exchangeID);
	char* myreq[1] = { instrumentID };
	int i = this->api->UnSubscribeMarketData(myreq, 1, exchangeID);
	return i;
};

int MdApi::reqUserLogin(dict req, int nRequestID)
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

int MdApi::reqUserLogout(dict req, int nRequestID)
{
	CSecurityFtdcUserLogoutField myreq = CSecurityFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
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


BOOST_PYTHON_MODULE(vnltsmd)
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
		.def("subscribeMarketData", &MdApiWrap::subscribeMarketData)
		.def("unSubscribeMarketData", &MdApiWrap::unSubscribeMarketData)
		.def("reqUserLogin", &MdApiWrap::reqUserLogin)
		.def("reqUserLogout", &MdApiWrap::reqUserLogout)

		.def("onFrontConnected", pure_virtual(&MdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&MdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&MdApiWrap::onHeartBeatWarning))
		.def("onRspError", pure_virtual(&MdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&MdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&MdApiWrap::onRspUserLogout))
		.def("onRspSubMarketData", pure_virtual(&MdApiWrap::onRspSubMarketData))
		.def("onRspUnSubMarketData", pure_virtual(&MdApiWrap::onRspUnSubMarketData))
		.def("onRtnDepthMarketData", pure_virtual(&MdApiWrap::onRtnDepthMarketData))
		;
};
