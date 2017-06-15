// vnqdpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnqdpmd.h"

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
	//手动修改
	Task task = Task();
	task.task_name = ONPACKAGESTART;
	task.task_id = nTopicID;
	task.additional_int = nSequenceNo;
	this->task_queue.push(task);
};

void MdApi::OnPackageEnd(int nTopicID, int nSequenceNo)
{
	//手动修改
	Task task = Task();
	task.task_name = ONPACKAGEEND;
	task.task_id = nTopicID;
	task.additional_int = nSequenceNo;
	this->task_queue.push(task);
};

void MdApi::OnMultiHeartbeat(char *CurrTime, char *MultiCastIP)
{
	//手动修改
	Task task = Task();
	task.task_name = ONMULTIHEARTBEAT;
	task.additional_str1 = *CurrTime;
	task.additional_str2 = *MultiCastIP;
	this->task_queue.push(task);
};

void MdApi::UdpMarketData(CQdpFtdcDepthMarketDataField *qmdata)
{
	//手动修改
	Task task = Task();
	task.task_name = UDPMARKETDATA;

	if (qmdata)
	{
		task.task_data = *qmdata;
	}
	else
	{
		CQdpFtdcDepthMarketDataField empty_data = CQdpFtdcDepthMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	this->task_queue.push(task);
};

void MdApi::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CQdpFtdcRspUserLoginField empty_data = CQdpFtdcRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pRspUserLogout)
	{
		task.task_data = *pRspUserLogout;
	}
	else
	{
		CQdpFtdcRspUserLogoutField empty_data = CQdpFtdcRspUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRtnQmdInstrumentStatu(CQdpFtdcQmdInstrumentStateField *pQmdInstrumentState)
{
	Task task = Task();
	task.task_name = ONRTNQMDINSTRUMENTSTATU;

	if (pQmdInstrumentState)
	{
		task.task_data = *pQmdInstrumentState;
	}
	else
	{
		CQdpFtdcQmdInstrumentStateField empty_data = CQdpFtdcQmdInstrumentStateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBETOPIC;

	if (pDissemination)
	{
		task.task_data = *pDissemination;
	}
	else
	{
		CQdpFtdcDisseminationField empty_data = CQdpFtdcDisseminationField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspQryTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTOPIC;

	if (pDissemination)
	{
		task.task_data = *pDissemination;
	}
	else
	{
		CQdpFtdcDisseminationField empty_data = CQdpFtdcDisseminationField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRtnDepthMarketData(CQdpFtdcDepthMarketDataField *pDepthMarketData)
{
	Task task = Task();
	task.task_name = ONRTNDEPTHMARKETDATA;

	if (pDepthMarketData)
	{
		task.task_data = *pDepthMarketData;
	}
	else
	{
		CQdpFtdcDepthMarketDataField empty_data = CQdpFtdcDepthMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		CQdpFtdcSpecificInstrumentField empty_data = CQdpFtdcSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBMARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		CQdpFtdcSpecificInstrumentField empty_data = CQdpFtdcSpecificInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspQryDepthMarketData(CQdpFtdcRspMarketDataField *pRspMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYDEPTHMARKETDATA;

	if (pRspMarketData)
	{
		task.task_data = *pRspMarketData;
	}
	else
	{
		CQdpFtdcRspMarketDataField empty_data = CQdpFtdcRspMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CQdpFtdcRspInfoField empty_error = CQdpFtdcRspInfoField();
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

			case ONPACKAGESTART:
			{
				this->processPackageStart(task);
				break;
			}

			case ONPACKAGEEND:
			{
				this->processPackageEnd(task);
				break;
			}

			//手动修改
			case ONMULTIHEARTBEAT:
			{
				this->processMultiHeartbeat(task);
				break;
			}

			//手动修改
			case UDPMARKETDATA:
			{
				this->processUdpMarketData(task);
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

			case ONRTNQMDINSTRUMENTSTATU:
			{
				this->processRtnQmdInstrumentStatu(task);
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

			case ONRSPQRYDEPTHMARKETDATA:
			{
				this->processRspQryDepthMarketData(task);
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

void MdApi::processPackageStart(Task task)
{
	//手动修改
	PyLock lock;
	this->onPackageStart(task.task_id, task.additional_int);
};

void MdApi::processPackageEnd(Task task)
{
	//手动修改
	PyLock lock;
	this->onPackageEnd(task.task_id, task.additional_int);
};

void MdApi::processMultiHeartbeat(Task task)
{
	//手动修改
	PyLock lock;
	this->onMultiHeartbeat(task.additional_str1, task.additional_str2);
};

void MdApi::processUdpMarketData(Task task)
{
	//手动修改
	PyLock lock;
	CQdpFtdcDepthMarketDataField task_data = any_cast<CQdpFtdcDepthMarketDataField>(task.task_data);
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
	data["ExchangeID"] = task_data.ExchangeID;
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

	this->udpMarketData(data);
};

void MdApi::processRspError(Task task)
{
	PyLock lock;
	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLoginField task_data = any_cast<CQdpFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["PrivateFlowSize"] = task_data.PrivateFlowSize;
	data["UserID"] = task_data.UserID;
	data["DataCenterID"] = task_data.DataCenterID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["BrokerID"] = task_data.BrokerID;
	data["MaxOrderLocalID"] = task_data.MaxOrderLocalID;
	data["TradingSystemName"] = task_data.TradingSystemName;
	data["FrontID"] = task_data.FrontID;
	data["LoginTime"] = task_data.LoginTime;
	data["UserFlowSize"] = task_data.UserFlowSize;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CQdpFtdcRspUserLogoutField task_data = any_cast<CQdpFtdcRspUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void MdApi::processRtnQmdInstrumentStatu(Task task)
{
	PyLock lock;
	CQdpFtdcQmdInstrumentStateField task_data = any_cast<CQdpFtdcQmdInstrumentStateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["ExchangeID"] = task_data.ExchangeID;

	this->onRtnQmdInstrumentStatu(data);
};

void MdApi::processRspSubscribeTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubscribeTopic(data, error, task.task_id, task.task_last);
};

void MdApi::processRspQryTopic(Task task)
{
	PyLock lock;
	CQdpFtdcDisseminationField task_data = any_cast<CQdpFtdcDisseminationField>(task.task_data);
	dict data;
	data["SequenceNo"] = task_data.SequenceNo;
	data["SequenceSeries"] = task_data.SequenceSeries;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTopic(data, error, task.task_id, task.task_last);
};

void MdApi::processRtnDepthMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcDepthMarketDataField task_data = any_cast<CQdpFtdcDepthMarketDataField>(task.task_data);
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
	data["ExchangeID"] = task_data.ExchangeID;
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
	CQdpFtdcSpecificInstrumentField task_data = any_cast<CQdpFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspUnSubMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcSpecificInstrumentField task_data = any_cast<CQdpFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubMarketData(data, error, task.task_id, task.task_last);
};

void MdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	CQdpFtdcRspMarketDataField task_data = any_cast<CQdpFtdcRspMarketDataField>(task.task_data);
	dict data;
	data["HighestPrice"] = task_data.HighestPrice;
	data["BidPrice1"] = task_data.BidPrice1;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["SettlementGroupID"] = task_data.SettlementGroupID;
	data["BidVolume1"] = task_data.BidVolume1;
	data["Volume"] = task_data.Volume;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
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

	CQdpFtdcRspInfoField task_error = any_cast<CQdpFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createFtdcMdApi(string pszFlowPath)
{
	this->api = CQdpFtdcMduserApi::CreateFtdcMduserApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

string MdApi::getVersion(int major, int minor)
{
	//手动修改
	string version = this->api->GetVersion(major, minor);
	return version;
};

void MdApi::release()
{
	this->api->Release();
};

void MdApi::setMultiCast(bool multicast)
{
	//手动修改
	this->api->SetMultiCast(multicast);
}

void MdApi::regTopicMultiAddr(string multiAddr)
{
	//手动修改
	this->api->RegTopicMultiAddr((char*) multiAddr.c_str());
}

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
}

void MdApi::subscribeMarketDataTopic(int topicID, int resumeType)
{
	this->api->SubscribeMarketDataTopic(topicID, (QDP_TE_RESUME_TYPE)resumeType);
}

int MdApi::subMarketData(string instrumentID)
{
	char* buffer = (char*) instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubMarketData(myreq, 1);
	return i;
};

int MdApi::unSubMarketData(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->UnSubMarketData(myreq, 1);
	return i;
};

void MdApi::setHeartbeatTimeout(int timeout)
{
	//手动修改
	this->api->SetHeartbeatTimeout(timeout);
}

void MdApi::shmMarketData(dict req, dict defdata)
{
	//手动修改
};

void MdApi::setUdpChannel(string udpid)
{
	//手动修改
	this->api->setudpchannel((char*)udpid.c_str());
}

int MdApi::reqUserLogin(dict req, int nRequestID)
{
	CQdpFtdcReqUserLoginField myreq = CQdpFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "MacAddress", myreq.MacAddress);
	getStr(req, "UserProductInfo", myreq.UserProductInfo);
	getStr(req, "UserID", myreq.UserID);
	getInt(req, "DataCenterID", &myreq.DataCenterID);
	getStr(req, "TradingDay", myreq.TradingDay);
	getStr(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getStr(req, "BrokerID", myreq.BrokerID);
	getStr(req, "ClientIPAddress", myreq.ClientIPAddress);
	getStr(req, "OneTimePassword", myreq.OneTimePassword);
	getStr(req, "ProtocolInfo", myreq.ProtocolInfo);
	getStr(req, "Password", myreq.Password);
	getStr(req, "IPAddress", myreq.IPAddress);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int MdApi::reqUserLogout(dict req, int nRequestID)
{
	CQdpFtdcReqUserLogoutField myreq = CQdpFtdcReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "UserID", myreq.UserID);
	getStr(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int MdApi::reqSubscribeTopic(dict req, int nRequestID)
{
	CQdpFtdcDisseminationField myreq = CQdpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqSubscribeTopic(&myreq, nRequestID);
	return i;
};

int MdApi::reqQryTopic(dict req, int nRequestID)
{
	CQdpFtdcDisseminationField myreq = CQdpFtdcDisseminationField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SequenceNo", &myreq.SequenceNo);
	getInt(req, "SequenceSeries", &myreq.SequenceSeries);
	int i = this->api->ReqQryTopic(&myreq, nRequestID);
	return i;
};

int MdApi::reqSubMarketData(dict req, int nRequestID)
{
	CQdpFtdcSpecificInstrumentField myreq = CQdpFtdcSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqSubMarketData(&myreq, nRequestID);
	return i;
};

int MdApi::reqUnSubMarketData(dict req, int nRequestID)
{
	CQdpFtdcSpecificInstrumentField myreq = CQdpFtdcSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqUnSubMarketData(&myreq, nRequestID);
	return i;
};

int MdApi::reqQryDepthMarketData(dict req, int nRequestID)
{
	CQdpFtdcQryMarketDataField myreq = CQdpFtdcQryMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "InstrumentID", myreq.InstrumentID);
	getStr(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryDepthMarketData(&myreq, nRequestID);
	return i;
};

void MdApi::activateMultiMarketData(string tradingDay)
{
	//手动修改
	this->api->ActiveMultiMarketData((char*)tradingDay.c_str());
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


	virtual void onPackageStart(int topicID, int sequenceNo)
	{
		//手动修改
		try
		{
			this->get_override("onPackageStart")(topicID, sequenceNo);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onPackageEnd(int topicID, int sequenceNo)
	{
		//手动修改
		try
		{
			this->get_override("onPackageEnd")(topicID, sequenceNo);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onMultiHeartbeat(string currTime, string multiCastIP)
	{
		//手动修改
		try
		{
			this->get_override("onMultiHeartbeat")(currTime, multiCastIP);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void udpMarketData(dict data)
	{
		//手动修改
		try
		{
			this->get_override("udpMarketData")(data);
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

	virtual void onRtnQmdInstrumentStatu(dict data)
	{
		try
		{
			this->get_override("onRtnQmdInstrumentStatu")(data);
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
};


BOOST_PYTHON_MODULE(vnqdpmd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<MdApiWrap, boost::noncopyable>("MdApi")
		.def("createFtdcMdApi", &MdApiWrap::createFtdcMdApi)
		.def("getVersion", &MdApiWrap::getVersion)
		.def("release", &MdApiWrap::release)
		.def("setMultiCast", &MdApiWrap::setMultiCast)
		.def("regTopicMultiAddr", &MdApiWrap::regTopicMultiAddr)
		.def("init", &MdApiWrap::init)
		.def("join", &MdApiWrap::join)
		.def("exit", &MdApiWrap::exit)
		.def("getTradingDay", &MdApiWrap::getTradingDay)
		.def("registerFront", &MdApiWrap::registerFront)
		.def("registerNameServer", &MdApiWrap::registerNameServer)
		.def("subscribeMarketDataTopic", &MdApiWrap::subscribeMarketDataTopic)
		.def("subMarketData", &MdApiWrap::subMarketData)
		.def("unSubMarketData", &MdApiWrap::unSubMarketData)
		.def("setHeartbeatTimeout", &MdApiWrap::setHeartbeatTimeout)
		.def("shmMarketData", &MdApiWrap::shmMarketData)
		.def("setUdpChannel", &MdApiWrap::setUdpChannel)
		.def("reqUserLogin", &MdApiWrap::reqUserLogin)
		.def("reqUserLogout", &MdApiWrap::reqUserLogout)
		.def("reqSubscribeTopic", &MdApiWrap::reqSubscribeTopic)
		.def("reqQryTopic", &MdApiWrap::reqQryTopic)
		.def("reqSubMarketData", &MdApiWrap::reqSubMarketData)
		.def("reqUnSubMarketData", &MdApiWrap::reqUnSubMarketData)
		.def("reqQryDepthMarketData", &MdApiWrap::reqQryDepthMarketData)
		.def("activateMultiMarketData", &MdApiWrap::activateMultiMarketData)

		.def("onFrontConnected", pure_virtual(&MdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&MdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&MdApiWrap::onHeartBeatWarning))
		.def("onPackageStart", pure_virtual(&MdApiWrap::onPackageStart))
		.def("onPackageEnd", pure_virtual(&MdApiWrap::onPackageEnd))
		.def("onMultiHeartbeat", pure_virtual(&MdApiWrap::onMultiHeartbeat))
		.def("udpMarketData", pure_virtual(&MdApiWrap::udpMarketData))
		.def("onRspError", pure_virtual(&MdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&MdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&MdApiWrap::onRspUserLogout))
		.def("onRtnQmdInstrumentStatu", pure_virtual(&MdApiWrap::onRtnQmdInstrumentStatu))
		.def("onRspSubscribeTopic", pure_virtual(&MdApiWrap::onRspSubscribeTopic))
		.def("onRspQryTopic", pure_virtual(&MdApiWrap::onRspQryTopic))
		.def("onRtnDepthMarketData", pure_virtual(&MdApiWrap::onRtnDepthMarketData))
		.def("onRspSubMarketData", pure_virtual(&MdApiWrap::onRspSubMarketData))
		.def("onRspUnSubMarketData", pure_virtual(&MdApiWrap::onRspUnSubMarketData))
		.def("onRspQryDepthMarketData", pure_virtual(&MdApiWrap::onRspQryDepthMarketData))
		;
};
