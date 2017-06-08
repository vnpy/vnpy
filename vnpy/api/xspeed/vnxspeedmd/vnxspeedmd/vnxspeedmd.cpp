// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnxspeedmd.h"



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

void getShort(dict d, string key, short *value)
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
			*value = *buffer;
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

void MdApi::OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pRspUserLogin, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		DFITCUserLoginInfoRtnField empty_data = DFITCUserLoginInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pRspUsrLogout, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pRspUsrLogout)
	{
		task.task_data = *pRspUsrLogout;
	}
	else
	{
		DFITCUserLogoutInfoRtnField empty_data = DFITCUserLogoutInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspError(struct DFITCErrorRtnField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPSUBFORQUOTERSP;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBFORQUOTERSP;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		DFITCSpecificInstrumentField empty_data = DFITCSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnMarketData(struct DFITCDepthMarketDataField * pMarketDataField)
{
	Task task = Task();
	task.task_name = ONMARKETDATA;

	if (pMarketDataField)
	{
		task.task_data = *pMarketDataField;
	}
	else
	{
		DFITCDepthMarketDataField empty_data = DFITCDepthMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnCustomMarketData(struct DFITCCustomMarketDataField * pMarketDataField)
{
	Task task = Task();
	task.task_name = ONCUSTOMMARKETDATA;

	if (pMarketDataField)
	{
		task.task_data = *pMarketDataField;
	}
	else
	{
		DFITCCustomMarketDataField empty_data = DFITCCustomMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRtnForQuoteRsp(struct DFITCQuoteSubscribeRtnField * pForQuoteField)
{
	Task task = Task();
	task.task_name = ONRTNFORQUOTERSP;

	if (pForQuoteField)
	{
		task.task_data = *pForQuoteField;
	}
	else
	{
		DFITCQuoteSubscribeRtnField empty_data = DFITCQuoteSubscribeRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGDAY;

	if (pTradingDayRtnData)
	{
		task.task_data = *pTradingDayRtnData;
	}
	else
	{
		DFITCTradingDayRtnField empty_data = DFITCTradingDayRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
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

		case ONRSPERROR:
		{
			this->processRspError(task);
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

		case ONRSPSUBFORQUOTERSP:
		{
			this->processRspSubForQuoteRsp(task);
			break;
		}

		case ONRSPUNSUBFORQUOTERSP:
		{
			this->processRspUnSubForQuoteRsp(task);
			break;
		}

		case ONMARKETDATA:
		{
			this->processMarketData(task);
			break;
		}

		case ONCUSTOMMARKETDATA:
		{
			this->processCustomMarketData(task);
			break;
		}

		case ONRTNFORQUOTERSP:
		{
			this->processRtnForQuoteRsp(task);
			break;
		}

		case ONRSPTRADINGDAY:
		{
			this->processRspTradingDay(task);
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

void MdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	DFITCUserLoginInfoRtnField task_data = any_cast<DFITCUserLoginInfoRtnField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["initLocalOrderID"] = task_data.initLocalOrderID;
	data["SHFETime"] = task_data.SHFETime;
	data["errorMsg"] = task_data.errorMsg;
	data["INETime"] = task_data.INETime;
	data["lRequestID"] = task_data.lRequestID;
	data["loginResult"] = task_data.loginResult;
	data["sessionID"] = task_data.sessionID;
	data["nErrorID"] = task_data.nErrorID;
	data["CFFEXTime"] = task_data.CFFEXTime;
	data["DCEtime"] = task_data.DCEtime;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUserLogin(data, error);
};

void MdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	DFITCUserLogoutInfoRtnField task_data = any_cast<DFITCUserLogoutInfoRtnField>(task.task_data);
	dict data;
	data["logoutResult"] = task_data.logoutResult;
	data["lRequestID"] = task_data.lRequestID;
	data["nErrorID"] = task_data.nErrorID;
	data["errorMsg"] = task_data.errorMsg;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUserLogout(data, error);
};

void MdApi::processRspError(Task task)
{
	PyLock lock;
	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspError(error);
};

void MdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspSubMarketData(data, error);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUnSubMarketData(data, error);
};

void MdApi::processRspSubForQuoteRsp(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspSubForQuoteRsp(data, error);
};

void MdApi::processRspUnSubForQuoteRsp(Task task)
{
	PyLock lock;
	DFITCSpecificInstrumentField task_data = any_cast<DFITCSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentType"] = task_data.instrumentType;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUnSubForQuoteRsp(data, error);
};

void MdApi::processMarketData(Task task)
{
	PyLock lock;
	DFITCDepthMarketDataField task_data = any_cast<DFITCDepthMarketDataField>(task.task_data);
	dict data;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidPrice4"] = task_data.BidPrice4;
	data["BidPrice1"] = task_data.BidPrice1;
	data["openPrice"] = task_data.openPrice;
	data["BidPrice2"] = task_data.BidPrice2;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["AskPrice2"] = task_data.AskPrice2;
	data["AskPrice1"] = task_data.AskPrice1;
	data["closePrice"] = task_data.closePrice;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["AveragePrice"] = task_data.AveragePrice;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["BidVolume1"] = task_data.BidVolume1;
	data["Volume"] = task_data.Volume;
	data["tradingDay"] = task_data.tradingDay;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["lowerLimitPrice"] = task_data.lowerLimitPrice;
	data["AskVolume4"] = task_data.AskVolume4;
	data["preDelta"] = task_data.preDelta;
	data["AskVolume5"] = task_data.AskVolume5;
	data["openInterest"] = task_data.openInterest;
	data["currDelta"] = task_data.currDelta;
	data["preClosePrice"] = task_data.preClosePrice;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["lastPrice"] = task_data.lastPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["settlementPrice"] = task_data.settlementPrice;
	data["preOpenInterest"] = task_data.preOpenInterest;
	data["exchangeInstID"] = task_data.exchangeInstID;
	data["XSpeedTime"] = task_data.XSpeedTime;
	data["BidPrice3"] = task_data.BidPrice3;
	data["upperLimitPrice"] = task_data.upperLimitPrice;
	data["lowestPrice"] = task_data.lowestPrice;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["highestPrice"] = task_data.highestPrice;
	data["turnover"] = task_data.turnover;

	this->onMarketData(data);
};

void MdApi::processCustomMarketData(Task task)
{
	PyLock lock;
	DFITCCustomMarketDataField task_data = any_cast<DFITCCustomMarketDataField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["lastPrice"] = task_data.lastPrice;
	data["bidPrice1"] = task_data.bidPrice1;
	data["bidVolume1"] = task_data.bidVolume1;
	data["askVolume1"] = task_data.askVolume1;
	data["askPrice1"] = task_data.askPrice1;

	this->onCustomMarketData(data);
};

void MdApi::processRtnForQuoteRsp(Task task)
{
	PyLock lock;
	DFITCQuoteSubscribeRtnField task_data = any_cast<DFITCQuoteSubscribeRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["source"] = task_data.source;
	data["exchangeID"] = task_data.exchangeID;
	data["quoteID"] = task_data.quoteID;
	data["quoteTime"] = task_data.quoteTime;

	this->onRtnForQuoteRsp(data);
};

void MdApi::processRspTradingDay(Task task)
{
	PyLock lock;
	DFITCTradingDayRtnField task_data = any_cast<DFITCTradingDayRtnField>(task.task_data);
	dict data;
	data["date"] = task_data.date;
	data["lRequestID"] = task_data.lRequestID;

	this->onRspTradingDay(data);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createDFITCMdApi()
{
	this->api = DFITCMdApi::CreateDFITCMdApi();
};

void MdApi::release()
{
	this->api->Release();
};

void MdApi::init(string pszSvrAddr)
{
	this->api->Init((char*)pszSvrAddr.c_str(), this);
};

int MdApi::exit()
{
	this->api->Release();
	this->api = NULL;
	return 1;
};

int MdApi::subscribeMarketData(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeMarketData(myreq, 1, nRequestID);
	return i;
};

int MdApi::unSubscribeMarketData(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeMarketData(myreq, 1, nRequestID);
	return i;
};

int MdApi::subscribeForQuoteRsp(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeForQuoteRsp(myreq, 1, nRequestID);
	return i;
};

int MdApi::unSubscribeForQuoteRsp(string instrumentID, int nRequestID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeForQuoteRsp(myreq, 1, nRequestID);
	return i;
};

int MdApi::reqUserLogin(dict req)
{
	DFITCUserLoginField myreq = DFITCUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "passwd", myreq.passwd);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "companyID", &myreq.companyID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogin(&myreq);
	return i;
};

int MdApi::reqUserLogout(dict req)
{
	DFITCUserLogoutField myreq = DFITCUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "sessionID", &myreq.sessionID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogout(&myreq);
	return i;
};

int MdApi::reqTradingDay(dict req)
{
	DFITCTradingDayField myreq = DFITCTradingDayField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	int i = this->api->ReqTradingDay(&myreq);
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

	virtual void onRspUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspUserLogout")(data, error);
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

	virtual void onRspSubMarketData(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSubMarketData")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUnSubMarketData(dict data, dict error)
	{
		try
		{
			this->get_override("onRspUnSubMarketData")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSubForQuoteRsp(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSubForQuoteRsp")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUnSubForQuoteRsp(dict data, dict error)
	{
		try
		{
			this->get_override("onRspUnSubForQuoteRsp")(data, error);
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

	virtual void onMarketData(dict data)
	{
		try
		{
			this->get_override("onMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onCustomMarketData(dict data)
	{
		try
		{
			this->get_override("onCustomMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspTradingDay(dict data, dict error)
	{
		try
		{
			this->get_override("onRspTradingDay")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnxspeedmd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<MdApiWrap, boost::noncopyable>("MdApi")
		.def("createDFITCMdApi", &MdApiWrap::createDFITCMdApi)
		.def("release", &MdApiWrap::release)
		.def("init", &MdApiWrap::init)
		.def("exit", &MdApiWrap::exit)
		.def("subscribeMarketData", &MdApiWrap::subscribeMarketData)
		.def("unSubscribeMarketData", &MdApiWrap::unSubscribeMarketData)
		.def("subscribeForQuoteRsp", &MdApiWrap::subscribeForQuoteRsp)
		.def("unSubscribeForQuoteRsp", &MdApiWrap::unSubscribeForQuoteRsp)
		.def("reqUserLogin", &MdApiWrap::reqUserLogin)
		.def("reqUserLogout", &MdApiWrap::reqUserLogout)
		.def("reqTradingDay", &MdApiWrap::reqTradingDay)

		.def("onFrontConnected", pure_virtual(&MdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&MdApiWrap::onFrontDisconnected))
		.def("onRspUserLogin", pure_virtual(&MdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&MdApiWrap::onRspUserLogout))
		.def("onRspError", pure_virtual(&MdApiWrap::onRspError))
		.def("onRspSubMarketData", pure_virtual(&MdApiWrap::onRspSubMarketData))
		.def("onRspUnSubMarketData", pure_virtual(&MdApiWrap::onRspUnSubMarketData))
		.def("onRspSubForQuoteRsp", pure_virtual(&MdApiWrap::onRspSubForQuoteRsp))
		.def("onRspUnSubForQuoteRsp", pure_virtual(&MdApiWrap::onRspUnSubForQuoteRsp))
		.def("onMarketData", pure_virtual(&MdApiWrap::onMarketData))
		.def("onCustomMarketData", pure_virtual(&MdApiWrap::onCustomMarketData))
		.def("onRtnForQuoteRsp", pure_virtual(&MdApiWrap::onRtnForQuoteRsp))
		.def("onRspTradingDay", pure_virtual(&MdApiWrap::onRspTradingDay))
		;
};