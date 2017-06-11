// vnctptd.cpp : 定义 DLL 应用程序的导出函数。

#include "stdafx.h"
#include "vnksgoldtd.h"


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


void getUnsignedChar(dict d, string key, unsigned char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			*value = (unsigned char)*buffer;
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

void TdApi::OnNtyMktStatus(const CThostFtdcMarketStatusField *pfldMktStatus)
{
	Task task = Task();
	task.task_name = ONNTYMKTSTATUS;

	if (pfldMktStatus)
	{
		task.task_data = *pfldMktStatus;
	}
	else
	{
		CThostFtdcMarketStatusField empty_data = CThostFtdcMarketStatusField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
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

void TdApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	Task task = Task();
	task.task_name = ONRTNDEPTHMARKETDATA;

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

void TdApi::OnRtnOrder(CThostFtdcOrderRtnField *pOrder)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CThostFtdcOrderRtnField empty_data = CThostFtdcOrderRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnForceLogout(CThostFtdcUserLogoutField *pLogout)
{
	Task task = Task();
	task.task_name = ONFORCELOGOUT;

	if (pLogout)
	{
		task.task_data = *pLogout;
	}
	else
	{
		CThostFtdcUserLogoutField empty_data = CThostFtdcUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
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

void TdApi::OnRspQryClientStorage(CThostFtdcStorageField *pStorage, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCLIENTSTORAGE;

	if (pStorage)
	{
		task.task_data = *pStorage;
	}
	else
	{
		CThostFtdcStorageField empty_data = CThostFtdcStorageField();
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

void TdApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		CThostFtdcSpecificInstrumentField empty_data = CThostFtdcSpecificInstrumentField();
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

		case ONNTYMKTSTATUS:
		{
			this->processNtyMktStatus(task);
			break;
		}

		case ONRSPQRYINSTRUMENT:
		{
			this->processRspQryInstrument(task);
			break;
		}

		case ONRTNDEPTHMARKETDATA:
		{
			this->processRtnDepthMarketData(task);
			break;
		}

		case ONRSPORDERINSERT:
		{
			this->processRspOrderInsert(task);
			break;
		}

		case ONERRRTNORDERINSERT:
		{
			this->processErrRtnOrderInsert(task);
			break;
		}

		case ONRTNORDER:
		{
			this->processRtnOrder(task);
			break;
		}

		case ONFORCELOGOUT:
		{
			this->processForceLogout(task);
			break;
		}

		case ONRSPORDERACTION:
		{
			this->processRspOrderAction(task);
			break;
		}

		case ONERRRTNORDERACTION:
		{
			this->processErrRtnOrderAction(task);
			break;
		}

		case ONRTNTRADE:
		{
			this->processRtnTrade(task);
			break;
		}

		case ONRSPQRYTRADINGACCOUNT:
		{
			this->processRspQryTradingAccount(task);
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

		case ONRSPQRYCLIENTSTORAGE:
		{
			this->processRspQryClientStorage(task);
			break;
		}

		case ONRSPSUBMARKETDATA:
		{
			this->processRspSubMarketData(task);
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
	CThostFtdcRspUserLoginField task_data = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["SeatNo"] = task_data.SeatNo;
	data["tradeDate"] = task_data.tradeDate;
	data["tradeCode"] = task_data.tradeCode;
	data["localOrderNo"] = task_data.localOrderNo;
	data["loginbatch"] = task_data.loginbatch;
	data["clientID"] = task_data.clientID;
	data["lastLoginDate"] = task_data.lastLoginDate;
	data["lastLoginTime"] = task_data.lastLoginTime;
	data["lastLoginIp"] = task_data.lastLoginIp;
	data["clientName"] = task_data.clientName;

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
	data["traderID"] = task_data.traderID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processNtyMktStatus(Task task)
{
	PyLock lock;
	CThostFtdcMarketStatusField task_data = any_cast<CThostFtdcMarketStatusField>(task.task_data);
	dict data;
	data["mktStatus"] = task_data.MktStatus;
	data["marketID"] = task_data.marketID;

	this->onNtyMktStatus(data);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CThostFtdcInstrumentField task_data = any_cast<CThostFtdcInstrumentField>(task.task_data);
	dict data;
	data["exchangeID"] = task_data.exchangeID;
	data["tradeState"] = task_data.tradeState;
	data["name"] = task_data.name;
	data["lowerLimit"] = task_data.lowerLimit;
	data["openFlag"] = task_data.openFlag;
	data["instID"] = task_data.instID;
	data["marketType"] = task_data.marketType;
	data["marketID"] = task_data.marketID;
	data["varietyType"] = task_data.varietyType;
	data["maxHand"] = task_data.maxHand;
	data["minHand"] = task_data.minHand;
	data["tick"] = task_data.tick;
	data["varietyID"] = task_data.varietyID;
	data["unit"] = task_data.unit;
	data["upperLimit"] = task_data.upperLimit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CThostFtdcDepthMarketDataField task_data = any_cast<CThostFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["AskLot3"] = task_data.AskLot3;
	data["AskLot2"] = task_data.AskLot2;
	data["AskLot1"] = task_data.AskLot1;
	data["AskLot5"] = task_data.AskLot5;
	data["AskLot4"] = task_data.AskLot4;
	data["InstID"] = task_data.InstID;
	data["Bid5"] = task_data.Bid5;
	data["Bid4"] = task_data.Bid4;
	data["Bid3"] = task_data.Bid3;
	data["Bid2"] = task_data.Bid2;
	data["Bid1"] = task_data.Bid1;
	data["Low"] = task_data.Low;
	data["Ask1"] = task_data.Ask1;
	data["PreClose"] = task_data.PreClose;
	data["weight"] = task_data.weight;
	data["QuoteDate"] = task_data.QuoteDate;
	data["lowLimit"] = task_data.lowLimit;
	data["Volume"] = task_data.Volume;
	data["Average"] = task_data.Average;
	data["Ask5"] = task_data.Ask5;
	data["Ask4"] = task_data.Ask4;
	data["PreSettle"] = task_data.PreSettle;
	data["Last"] = task_data.Last;
	data["Name"] = task_data.Name;
	data["Ask3"] = task_data.Ask3;
	data["Ask2"] = task_data.Ask2;
	data["BidLot1"] = task_data.BidLot1;
	data["UpDown"] = task_data.UpDown;
	data["BidLot3"] = task_data.BidLot3;
	data["BidLot2"] = task_data.BidLot2;
	data["BidLot5"] = task_data.BidLot5;
	data["BidLot4"] = task_data.BidLot4;
	data["UpDownRate"] = task_data.UpDownRate;
	data["MarketName"] = task_data.MarketName;
	data["OpenInt"] = task_data.OpenInt;
	data["QuoteTime"] = task_data.QuoteTime;
	data["Turnover"] = task_data.Turnover;
	data["highLimit"] = task_data.highLimit;
	data["High"] = task_data.High;
	data["Settle"] = task_data.Settle;
	data["Close"] = task_data.Close;
	data["Open"] = task_data.Open;

	this->onRtnDepthMarketData(data);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;

	data["offsetFlag"] = (char) task_data.offsetFlag;
	data["buyOrSell"] = (char) task_data.buyOrSell;
	data["middleFlag"] = task_data.middleFlag;
	data["tradeCode"] = task_data.tradeCode;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["marketID"] = task_data.marketID;
	data["trigPrice"] = task_data.trigPrice;
	data["amount"] = task_data.amount;
	data["seatID"] = task_data.seatID;
	data["priceFlag"] = task_data.priceFlag;
	data["LocalOrderNo"] = task_data.LocalOrderNo;
	data["tradeWay"] = task_data.tradeWay;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderField task_data = any_cast<CThostFtdcInputOrderField>(task.task_data);
	dict data;
	data["offsetFlag"] = task_data.offsetFlag;
	data["buyOrSell"] = task_data.buyOrSell;
	data["middleFlag"] = task_data.middleFlag;
	data["tradeCode"] = task_data.tradeCode;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["marketID"] = task_data.marketID;
	data["trigPrice"] = task_data.trigPrice;
	data["amount"] = task_data.amount;
	data["seatID"] = task_data.seatID;
	data["priceFlag"] = task_data.priceFlag;
	data["LocalOrderNo"] = task_data.LocalOrderNo;
	data["tradeWay"] = task_data.tradeWay;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderRtnField task_data = any_cast<CThostFtdcOrderRtnField>(task.task_data);
	dict data;
	data["status"] = (char) task_data.status;
	data["orderNo"] = task_data.orderNo;
	data["localOrderNo"] = task_data.localOrderNo;
	data["cancelQty"] = task_data.cancelQty;

	this->onRtnOrder(data);
};

void TdApi::processForceLogout(Task task)
{
	PyLock lock;
	CThostFtdcUserLogoutField task_data = any_cast<CThostFtdcUserLogoutField>(task.task_data);
	dict data;
	data["traderID"] = task_data.traderID;

	this->onForceLogout(data);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcInputOrderActionField task_data = any_cast<CThostFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["status"] = task_data.status;
	data["localOrderNo"] = task_data.localOrderNo;
	data["marketID"] = task_data.marketID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	PyLock lock;
	CThostFtdcOrderActionField task_data = any_cast<CThostFtdcOrderActionField>(task.task_data);
	dict data;
	data["tradeWay"] = task_data.tradeWay;
	data["localOrderNo"] = task_data.localOrderNo;
	data["marketID"] = task_data.marketID;
	data["traderID"] = task_data.traderID;
	data["orderFlag"] = task_data.orderFlag;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CThostFtdcTradeField task_data = any_cast<CThostFtdcTradeField>(task.task_data);
	dict data;
	data["offSetFlag"] = (char) task_data.offSetFlag;
	data["buyOrSell"] = (char) task_data.buyOrSell;
	data["order_flag"] = task_data.order_flag;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["trade_fee"] = task_data.trade_fee;
	data["weight"] = task_data.weight;
	data["marketID"] = task_data.marketID;
	data["volume"] = task_data.volume;
	data["matchTime"] = task_data.matchTime;
	data["amount"] = task_data.amount;
	data["matchNo"] = task_data.matchNo;
	data["orderNo"] = task_data.orderNo;
	data["tradeWay"] = task_data.tradeWay;
	data["forcebatchnum"] = task_data.forcebatchnum;
	data["localOrderNo"] = task_data.localOrderNo;
	data["matchDate"] = task_data.matchDate;
	data["forceoffset_flag"] = task_data.forceoffset_flag; 

	this->onRtnTrade(data);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CThostFtdcTradingAccountField task_data = any_cast<CThostFtdcTradingAccountField>(task.task_data);
	dict data;
	data["available"] = task_data.available;
	data["buyPosiMargin"] = task_data.buyPosiMargin;
	data["totalFrozen"] = task_data.totalFrozen;
	data["spotSellFrozen"] = task_data.spotSellFrozen;
	data["middleMargin"] = task_data.middleMargin;
	data["posiMargin"] = task_data.posiMargin;
	data["storageMargin"] = task_data.storageMargin;
	data["availCap"] = task_data.availCap;
	data["todayOut"] = task_data.todayOut;
	data["pickUpMargin"] = task_data.pickUpMargin;
	data["totalFrozenFee"] = task_data.totalFrozenFee;
	data["lastFrozen"] = task_data.lastFrozen;
	data["todayIn"] = task_data.todayIn;
	data["orderFrozen"] = task_data.orderFrozen;
	data["totalFee"] = task_data.totalFee;
	data["sellPosiMargin"] = task_data.sellPosiMargin;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CThostFtdcOrderField task_data = any_cast<CThostFtdcOrderField>(task.task_data);
	dict data;
	data["status"] = (char) task_data.status;
	data["cancelTime"] = task_data.cancelTime;
	data["offsetFlag"] = (char) task_data.offsetFlag;
	data["buyOrSell"] = (char) task_data.buyOrSell;
	data["instID"] = task_data.instID;
	data["localOrderNo"] = task_data.localOrderNo;
	data["matchQty"] = task_data.matchQty;
	data["weight"] = task_data.weight;
	data["marketID"] = task_data.marketID;
	data["amount"] = task_data.amount;
	data["forceoffset_flag"] = (char) task_data.forceoffset_flag;
	data["entrustTime"] = task_data.entrustTime;
	data["orderNo"] = task_data.orderNo;
	data["cancelQty"] = task_data.cancelQty;
	data["matchWeight"] = task_data.matchWeight;
	data["price"] = task_data.price;
	data["tradeWay"] = (char) task_data.tradeWay;

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
	data["offSetFlag"] = (char) task_data.offSetFlag;
	data["buyOrSell"] = (char) task_data.buyOrSell;
	data["order_flag"] = task_data.order_flag;
	data["instID"] = task_data.instID;
	data["price"] = task_data.price;
	data["trade_fee"] = task_data.trade_fee;
	data["weight"] = task_data.weight;
	data["marketID"] = task_data.marketID;
	data["volume"] = task_data.volume;
	data["matchTime"] = task_data.matchTime;
	data["amount"] = task_data.amount;
	data["matchNo"] = task_data.matchNo;
	data["orderNo"] = task_data.orderNo;
	data["tradeWay"] = task_data.tradeWay;
	data["forcebatchnum"] = task_data.forcebatchnum;
	data["localOrderNo"] = task_data.localOrderNo;
	data["matchDate"] = task_data.matchDate;
	data["forceoffset_flag"] = (char) task_data.forceoffset_flag;

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
	data["shortPosiVol"] = task_data.shortPosiVol;
	data["longOpenAvgPrice"] = task_data.longOpenAvgPrice;
	data["lastLong"] = task_data.lastLong;
	data["longPosiVol"] = task_data.longPosiVol;
	data["todayOffsetLong"] = task_data.todayOffsetLong;
	data["shortPosiFrozen"] = task_data.shortPosiFrozen;
	data["instID"] = task_data.instID;
	data["lastShort"] = task_data.lastShort;
	data["todayOffsetShort"] = task_data.todayOffsetShort;
	data["longPosiAvgPrice"] = task_data.longPosiAvgPrice;
	data["longPosi"] = task_data.longPosi;
	data["todayLong"] = task_data.todayLong;
	data["todayShort"] = task_data.todayShort;
	data["shortPosi"] = task_data.shortPosi;
	data["shortOpenAvgPrice"] = task_data.shortOpenAvgPrice;
	data["longPosiFrozen"] = task_data.longPosiFrozen;
	data["shortPosiAvgPrice"] = task_data.shortPosiAvgPrice;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryClientStorage(Task task)
{
	PyLock lock;
	CThostFtdcStorageField task_data = any_cast<CThostFtdcStorageField>(task.task_data);
	dict data;
	data["todayLend"] = task_data.todayLend;
	data["todayBorrow"] = task_data.todayBorrow;
	data["frozenStorage"] = task_data.frozenStorage;
	data["storageCost"] = task_data.storageCost;
	data["varietyName"] = task_data.varietyName;
	data["customType"] = task_data.customType;
	data["lawFrozen"] = task_data.lawFrozen;
	data["impawnStorage"] = task_data.impawnStorage;
	data["todayBuy"] = task_data.todayBuy;
	data["varietyID"] = task_data.varietyID;
	data["pendStorage"] = task_data.pendStorage;
	data["availableStorage"] = task_data.availableStorage;
	data["totalStorage"] = task_data.totalStorage;
	data["impawnFrozen"] = task_data.impawnFrozen;
	data["todayRealDeposit"] = task_data.todayRealDeposit;
	data["todaySell"] = task_data.todaySell;
	data["bankFrozen"] = task_data.bankFrozen;
	data["todayDeposit"] = task_data.todayDeposit;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryClientStorage(data, error, task.task_id, task.task_last);
};

void TdApi::processRspSubMarketData(Task task)
{
	PyLock lock;
	CThostFtdcSpecificInstrumentField task_data = any_cast<CThostFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CThostFtdcRspInfoField task_error = any_cast<CThostFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createGoldTraderApi()
{
	this->api = CGoldTradeApi::CreateGoldTradeApi();
	this->api->RegisterSpi(this);
};

void TdApi::release()
{
	this->api->Release();
};

int TdApi::init(bool flag)
{
	int i = this->api->Init(flag);
	return i;
};

void TdApi::join()
{
	this->api->Join();
};

int TdApi::exit()
{
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

void TdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

int TdApi::subscribeMarketData(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeMarketData(myreq, 1);
	return i;
};

int TdApi::unSubscribeMarketData(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->UnSubscribeMarketData(myreq, 1);
	return i;
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "password", myreq.password);
	getChar(req, "tradeDate", myreq.tradeDate);
	getChar(req, "memberID", myreq.memberID);
	getInt(req, "loginType", &myreq.loginType);
	getChar(req, "accountID", myreq.accountID);

	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "traderID", myreq.traderID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserReLogin()
{
	int i = this->api->ReqUserReLogin();
	return i;
}

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ProductID", myreq.ProductID);
	getChar(req, "ContractID", myreq.ContractID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));

	getChar(req, "tradeCode", myreq.tradeCode);
	getChar(req, "instID", myreq.instID);
	getChar(req, "marketID", myreq.marketID);
	getInt(req, "amount", &myreq.amount);
	getChar(req, "seatID", myreq.seatID);
	getUnsignedChar(req, "priceFlag", &myreq.priceFlag);
	getChar(req, "LocalOrderNo", myreq.LocalOrderNo);
	getUnsignedChar(req, "tradeWay", &myreq.tradeWay);
	getUnsignedChar(req, "middleFlag", &myreq.middleFlag);
	getDouble(req, "price", &myreq.price);

	//以下代码为手写

	if (req.has_key("offsetFlag"))
	{
		object o = req["offsetFlag"];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *offsetBuffer = s.c_str();
			
			if (*offsetBuffer == '0')
			{
				myreq.offsetFlag = '0';
			}
			else if (*offsetBuffer == '1')
			{
				myreq.offsetFlag = '1';
			}
		}
	}

	if (req.has_key("buyOrSell"))
	{
		object o2 = req["buyOrSell"];
		extract<string> x2(o2);
		if (x2.check())
		{
			string s2 = x2();
			const char *bsBuffer = s2.c_str();

			if (*bsBuffer == '0')
			{
				myreq.buyOrSell = '0';
			}
			else if (*bsBuffer == '1')
			{
				myreq.buyOrSell = '1';
			}
		}
	}

	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getUnsignedChar(req, "status", &myreq.status);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "instID", myreq.instID);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "remian", myreq.remian);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTrade(dict req, int nRequestID)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "instID", myreq.instID);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "matchNo", myreq.matchNo);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "instID", myreq.instID);
	getChar(req, "localOrderNo", myreq.localOrderNo);
	getChar(req, "marketID", myreq.marketID);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryStorage(dict req, int nRequestID)
{
	CThostFtdcQryStorageField myreq = CThostFtdcQryStorageField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "varietyID", myreq.varietyID);
	int i = this->api->ReqQryStorage(&myreq, nRequestID);
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct TdApiWrap : TdApi, wrapper < TdApi >
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

	virtual void onRspQryClientStorage(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryClientStorage")(data, error, id, last);
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

};

BOOST_PYTHON_MODULE(vnksgoldtd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("createGoldTraderApi", &TdApiWrap::createGoldTraderApi)
		.def("release", &TdApiWrap::release)
		.def("init", &TdApiWrap::init)
		.def("join", &TdApiWrap::join)
		.def("exit", &TdApiWrap::exit)
		.def("registerFront", &TdApiWrap::registerFront)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("subscribeMarketData", &TdApiWrap::subscribeMarketData)
		.def("unSubscribeMarketData", &TdApiWrap::unSubscribeMarketData)
		.def("reqUserReLogin", &TdApiWrap::reqUserReLogin)
		.def("reqQryInstrument", &TdApiWrap::reqQryInstrument)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqQryInvestorPosition", &TdApiWrap::reqQryInvestorPosition)
		.def("reqQryTradingAccount", &TdApiWrap::reqQryTradingAccount)
		.def("reqQryTrade", &TdApiWrap::reqQryTrade)
		.def("reqQryOrder", &TdApiWrap::reqQryOrder)
		.def("reqQryStorage", &TdApiWrap::reqQryStorage)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onNtyMktStatus", pure_virtual(&TdApiWrap::onNtyMktStatus))
		.def("onRspQryInstrument", pure_virtual(&TdApiWrap::onRspQryInstrument))
		.def("onRtnDepthMarketData", pure_virtual(&TdApiWrap::onRtnDepthMarketData))
		.def("onForceLogout", pure_virtual(&TdApiWrap::onForceLogout))
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onErrRtnOrderInsert", pure_virtual(&TdApiWrap::onErrRtnOrderInsert))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onErrRtnOrderAction", pure_virtual(&TdApiWrap::onErrRtnOrderAction))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onRspQryTradingAccount", pure_virtual(&TdApiWrap::onRspQryTradingAccount))
		.def("onRspQryOrder", pure_virtual(&TdApiWrap::onRspQryOrder))
		.def("onRspQryTrade", pure_virtual(&TdApiWrap::onRspQryTrade))
		.def("onRspQryInvestorPosition", pure_virtual(&TdApiWrap::onRspQryInvestorPosition))
		.def("onRspQryClientStorage", pure_virtual(&TdApiWrap::onRspQryClientStorage))
		.def("onRspSubMarketData", pure_virtual(&TdApiWrap::onRspSubMarketData))
		;
}