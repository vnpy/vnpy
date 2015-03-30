// vnltsl2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnltsl2.h"



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

void L2MdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void L2MdApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void L2MdApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_id = nTimeLapse;
	this->task_queue.push(task);
};

void L2MdApi::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void L2MdApi::OnRspUserLogin(CSecurityFtdcUserLoginField *pUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pUserLogin)
	{
		task.task_data = *pUserLogin;
	}
	else
	{
		CSecurityFtdcUserLoginField empty_data = CSecurityFtdcUserLoginField();
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

void L2MdApi::OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void L2MdApi::OnRspSubL2MarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBL2MARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		CSecurityFtdcSpecificInstrumentField empty_data = CSecurityFtdcSpecificInstrumentField();
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

void L2MdApi::OnRspUnSubL2MarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBL2MARKETDATA;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		CSecurityFtdcSpecificInstrumentField empty_data = CSecurityFtdcSpecificInstrumentField();
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

void L2MdApi::OnRspSubL2Index(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBL2INDEX;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		CSecurityFtdcSpecificInstrumentField empty_data = CSecurityFtdcSpecificInstrumentField();
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

void L2MdApi::OnRspUnSubL2Index(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBL2INDEX;

	if (pSpecificInstrument)
	{
		task.task_data = *pSpecificInstrument;
	}
	else
	{
		CSecurityFtdcSpecificInstrumentField empty_data = CSecurityFtdcSpecificInstrumentField();
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

void L2MdApi::OnRtnL2MarketData(CSecurityFtdcL2MarketDataField *pL2MarketData)
{
	Task task = Task();
	task.task_name = ONRTNL2MARKETDATA;

	if (pL2MarketData)
	{
		task.task_data = *pL2MarketData;
	}
	else
	{
		CSecurityFtdcL2MarketDataField empty_data = CSecurityFtdcL2MarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void L2MdApi::OnRtnL2Index(CSecurityFtdcL2IndexField *pL2Index)
{
	Task task = Task();
	task.task_name = ONRTNL2INDEX;

	if (pL2Index)
	{
		task.task_data = *pL2Index;
	}
	else
	{
		CSecurityFtdcL2IndexField empty_data = CSecurityFtdcL2IndexField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void L2MdApi::OnRspSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPSUBL2ORDERANDTRADE;

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

void L2MdApi::OnRspUnSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBL2ORDERANDTRADE;

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

void L2MdApi::OnRtnL2Order(CSecurityFtdcL2OrderField *pL2Order)
{
	Task task = Task();
	task.task_name = ONRTNL2ORDER;

	if (pL2Order)
	{
		task.task_data = *pL2Order;
	}
	else
	{
		CSecurityFtdcL2OrderField empty_data = CSecurityFtdcL2OrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void L2MdApi::OnRtnL2Trade(CSecurityFtdcL2TradeField *pL2Trade)
{
	Task task = Task();
	task.task_name = ONRTNL2TRADE;

	if (pL2Trade)
	{
		task.task_data = *pL2Trade;
	}
	else
	{
		CSecurityFtdcL2TradeField empty_data = CSecurityFtdcL2TradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void L2MdApi::OnNtfCheckOrderList(TSecurityFtdcInstrumentIDType InstrumentID, TSecurityFtdcFunctionCodeType FunctionCode)
{
	//该函数为手动实现
	Task task = Task();
	task.task_name = ONNTFCHECKORDERLIST;

	//先转换为string类型
	string instrumentID = InstrumentID;
	string functionCode = FunctionCode;

	task.task_data = instrumentID;
	task.task_error = functionCode;

	this->task_queue.push(task);
};


///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void L2MdApi::processTask()
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

			case ONRSPSUBL2MARKETDATA:
			{
				this->processRspSubL2MarketData(task);
				break;
			}

			case ONRSPUNSUBL2MARKETDATA:
			{
				this->processRspUnSubL2MarketData(task);
				break;
			}

			case ONRSPSUBL2INDEX:
			{
				this->processRspSubL2Index(task);
				break;
			}

			case ONRSPUNSUBL2INDEX:
			{
				this->processRspUnSubL2Index(task);
				break;
			}

			case ONRTNL2MARKETDATA:
			{
				this->processRtnL2MarketData(task);
				break;
			}

			case ONRTNL2INDEX:
			{
				this->processRtnL2Index(task);
				break;
			}

			case ONRSPSUBL2ORDERANDTRADE:
			{
				this->processRspSubL2OrderAndTrade(task);
				break;
			}

			case ONRSPUNSUBL2ORDERANDTRADE:
			{
				this->processRspUnSubL2OrderAndTrade(task);
				break;
			}

			case ONRTNL2ORDER:
			{
				this->processRtnL2Order(task);
				break;
			}

			case ONRTNL2TRADE:
			{
				this->processRtnL2Trade(task);
				break;
			}

			case ONNTFCHECKORDERLIST:
			{
				this->processNtfCheckOrderList(task);
				break;
			}
		}
	}
};

void L2MdApi::processFrontConnected(Task task)
{
	this->onFrontConnected();
};

void L2MdApi::processFrontDisconnected(Task task)
{
	this->onFrontDisconnected(task.task_id);
};

void L2MdApi::processHeartBeatWarning(Task task)
{
	this->onHeartBeatWarning(task.task_id);
};

void L2MdApi::processRspError(Task task)
{
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void L2MdApi::processRspUserLogin(Task task)
{
	CSecurityFtdcUserLoginField task_data = any_cast<CSecurityFtdcUserLoginField>(task.task_data);
	dict data;
	data["TradingDay"] = task_data.TradingDay;
	data["Password"] = task_data.Password;
	data["BrokerID"] = task_data.BrokerID;
	data["DataLevel"] = task_data.DataLevel;
	data["UserID"] = task_data.UserID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspUserLogout(Task task)
{
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

void L2MdApi::processRspSubL2MarketData(Task task)
{
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubL2MarketData(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspUnSubL2MarketData(Task task)
{
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubL2MarketData(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspSubL2Index(Task task)
{
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubL2Index(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRspUnSubL2Index(Task task)
{
	CSecurityFtdcSpecificInstrumentField task_data = any_cast<CSecurityFtdcSpecificInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubL2Index(data, error, task.task_id, task.task_last);
};

void L2MdApi::processRtnL2MarketData(Task task)
{
	CSecurityFtdcL2MarketDataField task_data = any_cast<CSecurityFtdcL2MarketDataField>(task.task_data);
	dict data;
	data["BidCount8"] = task_data.BidCount8;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidPrice9"] = task_data.BidPrice9;
	data["BidPrice8"] = task_data.BidPrice8;
	data["OfferVolume8"] = task_data.OfferVolume8;
	data["OfferCount9"] = task_data.OfferCount9;
	data["BidPrice5"] = task_data.BidPrice5;
	data["LowPrice"] = task_data.LowPrice;
	data["BidPrice7"] = task_data.BidPrice7;
	data["AltWeightedAvgOfferPrice"] = task_data.AltWeightedAvgOfferPrice;
	data["BidPrice1"] = task_data.BidPrice1;
	data["OfferCount3"] = task_data.OfferCount3;
	data["TotalTradeVolume"] = task_data.TotalTradeVolume;
	data["BidPrice2"] = task_data.BidPrice2;
	data["BidVolume1"] = task_data.BidVolume1;
	data["OfferVolume3"] = task_data.OfferVolume3;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["OfferVolumeA"] = task_data.OfferVolumeA;
	data["BidCount3"] = task_data.BidCount3;
	data["BidCount2"] = task_data.BidCount2;
	data["BidCount1"] = task_data.BidCount1;
	data["BidPriceLevel"] = task_data.BidPriceLevel;
	data["BidCount7"] = task_data.BidCount7;
	data["BidCount6"] = task_data.BidCount6;
	data["BidCount5"] = task_data.BidCount5;
	data["BidCount4"] = task_data.BidCount4;
	data["BidVolume7"] = task_data.BidVolume7;
	data["BidVolume6"] = task_data.BidVolume6;
	data["TotalOfferVolume"] = task_data.TotalOfferVolume;
	data["TotalBidVolume"] = task_data.TotalBidVolume;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["OpenPrice"] = task_data.OpenPrice;
	data["OfferPriceA"] = task_data.OfferPriceA;
	data["OfferCount7"] = task_data.OfferCount7;
	data["OfferCount6"] = task_data.OfferCount6;
	data["TradeCount"] = task_data.TradeCount;
	data["BidPrice4"] = task_data.BidPrice4;
	data["WeightedAvgOfferPrice"] = task_data.WeightedAvgOfferPrice;
	data["OfferVolume6"] = task_data.OfferVolume6;
	data["HighPrice"] = task_data.HighPrice;
	data["OfferVolume9"] = task_data.OfferVolume9;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BidPrice6"] = task_data.BidPrice6;
	data["OfferPrice7"] = task_data.OfferPrice7;
	data["AltWeightedAvgBidPrice"] = task_data.AltWeightedAvgBidPrice;
	data["TimeStamp"] = task_data.TimeStamp;
	data["WeightedAvgBidPrice"] = task_data.WeightedAvgBidPrice;
	data["BidVolume9"] = task_data.BidVolume9;
	data["TotalTradeValue"] = task_data.TotalTradeValue;
	data["OfferCount4"] = task_data.OfferCount4;
	data["TradingDay"] = task_data.TradingDay;
	data["BidCountA"] = task_data.BidCountA;
	data["BidPrice3"] = task_data.BidPrice3;
	data["IOPV"] = task_data.IOPV;
	data["OfferCount1"] = task_data.OfferCount1;
	data["BidVolumeA"] = task_data.BidVolumeA;
	data["OfferPrice9"] = task_data.OfferPrice9;
	data["BidCount9"] = task_data.BidCount9;
	data["OfferPrice8"] = task_data.OfferPrice8;
	data["YieldToMaturity"] = task_data.YieldToMaturity;
	data["LastPrice"] = task_data.LastPrice;
	data["OfferCount8"] = task_data.OfferCount8;
	data["OfferPrice4"] = task_data.OfferPrice4;
	data["OfferPrice5"] = task_data.OfferPrice5;
	data["OfferPrice6"] = task_data.OfferPrice6;
	data["BidVolume8"] = task_data.BidVolume8;
	data["OfferCount5"] = task_data.OfferCount5;
	data["OfferPrice1"] = task_data.OfferPrice1;
	data["OfferPrice2"] = task_data.OfferPrice2;
	data["OfferPrice3"] = task_data.OfferPrice3;
	data["OfferVolume4"] = task_data.OfferVolume4;
	data["OfferVolume5"] = task_data.OfferVolume5;
	data["OfferPriceLevel"] = task_data.OfferPriceLevel;
	data["OfferVolume7"] = task_data.OfferVolume7;
	data["OfferVolume1"] = task_data.OfferVolume1;
	data["OfferVolume2"] = task_data.OfferVolume2;
	data["OfferCount2"] = task_data.OfferCount2;
	data["BidPriceA"] = task_data.BidPriceA;
	data["BidVolume5"] = task_data.BidVolume5;
	data["OfferCountA"] = task_data.OfferCountA;

	this->onRtnL2MarketData(data);
};

void L2MdApi::processRtnL2Index(Task task)
{
	CSecurityFtdcL2IndexField task_data = any_cast<CSecurityFtdcL2IndexField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["HighIndex"] = task_data.HighIndex;
	data["TimeStamp"] = task_data.TimeStamp;
	data["CloseIndex"] = task_data.CloseIndex;
	data["PreCloseIndex"] = task_data.PreCloseIndex;
	data["LastIndex"] = task_data.LastIndex;
	data["TradingDay"] = task_data.TradingDay;
	data["OpenIndex"] = task_data.OpenIndex;
	data["TotalVolume"] = task_data.TotalVolume;
	data["LowIndex"] = task_data.LowIndex;
	data["TurnOver"] = task_data.TurnOver;

	this->onRtnL2Index(data);
};

void L2MdApi::processRspSubL2OrderAndTrade(Task task)
{
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspSubL2OrderAndTrade(error, task.task_id, task.task_last);
};

void L2MdApi::processRspUnSubL2OrderAndTrade(Task task)
{
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUnSubL2OrderAndTrade(error, task.task_id, task.task_last);
};

void L2MdApi::processRtnL2Order(Task task)
{
	CSecurityFtdcL2OrderField task_data = any_cast<CSecurityFtdcL2OrderField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["OrderTime"] = task_data.OrderTime;
	data["OrderKind"] = task_data.OrderKind;
	data["Price"] = task_data.Price;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderGroupID"] = task_data.OrderGroupID;
	data["Volume"] = task_data.Volume;
	data["FunctionCode"] = task_data.FunctionCode;
	data["OrderIndex"] = task_data.OrderIndex;

	this->onRtnL2Order(data);
};

void L2MdApi::processRtnL2Trade(Task task)
{
	CSecurityFtdcL2TradeField task_data = any_cast<CSecurityFtdcL2TradeField>(task.task_data);
	dict data;
	data["TradeGroupID"] = task_data.TradeGroupID;
	data["SellIndex"] = task_data.SellIndex;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderKind"] = task_data.OrderKind;
	data["TradeIndex"] = task_data.TradeIndex;
	data["Price"] = task_data.Price;
	data["InstrumentID"] = task_data.InstrumentID;
	data["BuyIndex"] = task_data.BuyIndex;
	data["Volume"] = task_data.Volume;
	data["FunctionCode"] = task_data.FunctionCode;
	data["TradeTime"] = task_data.TradeTime;

	this->onRtnL2Trade(data);
};

void L2MdApi::processNtfCheckOrderList(Task task)
{
	//该函数为手动实现
	string instrumentID = any_cast<string>(task.task_data);
	string functionCode = any_cast<string>(task.task_data);

	this->onNtfCheckOrderList(instrumentID, functionCode);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void L2MdApi::createFtdcL2MDUserApi(string pszFlowPath)
{
	this->api = CSecurityFtdcL2MDUserApi::CreateFtdcL2MDUserApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void L2MdApi::release()
{
	this->api->Release();
};

void L2MdApi::init()
{
	this->api->Init();
};

int L2MdApi::join()
{
	int i = this->api->Join();
	return i;
};

int L2MdApi::exit()
{
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string L2MdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

void L2MdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

int L2MdApi::reqUserLogin(dict req, int nRequestID)
{
	CSecurityFtdcUserLoginField myreq = CSecurityFtdcUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "Password", myreq.Password);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "DataLevel", &myreq.DataLevel);
	getChar(req, "UserID", myreq.UserID);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);

	return i;
};

int L2MdApi::reqUserLogout(dict req, int nRequestID)
{
	CSecurityFtdcUserLogoutField myreq = CSecurityFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int L2MdApi::subscribeL2MarketData(dict req)
{
	char instrumentID[256];
	char exchangeID[256];
	getChar(req, "InstrumentID", instrumentID);
	getChar(req, "ExchangeID", exchangeID);
	char* myreq[1] = { instrumentID };
	int i = this->api->SubscribeL2MarketData(myreq, 1, exchangeID);
	return i;
};

int L2MdApi::unSubscribeL2MarketData(dict req)
{
	char instrumentID[256];
	char exchangeID[256];
	getChar(req, "InstrumentID", instrumentID);
	getChar(req, "ExchangeID", exchangeID);
	char* myreq[1] = { instrumentID };
	int i = this->api->UnSubscribeL2MarketData(myreq, 1, exchangeID);
	return i;
};

int L2MdApi::subscribeL2Index(dict req)
{
	char instrumentID[256];
	char exchangeID[256];
	getChar(req, "InstrumentID", instrumentID);
	getChar(req, "ExchangeID", exchangeID);
	char* myreq[1] = { instrumentID };
	int i = this->api->SubscribeL2Index(myreq, 1, exchangeID);
	return i;
};

int L2MdApi::unSubscribeL2Index(dict req)
{
	char instrumentID[256];
	char exchangeID[256];
	getChar(req, "InstrumentID", instrumentID);
	getChar(req, "ExchangeID", exchangeID);
	char* myreq[1] = { instrumentID };
	int i = this->api->UnSubscribeL2Index(myreq, 1, exchangeID);
	return i;
};

int L2MdApi::subscribeL2OrderAndTrade()
{
	int i = this->api->SubscribeL2OrderAndTrade();
	return i;
};

int L2MdApi::unSubscribeL2OrderAndTrade()
{
	int i = this->api->UnSubscribeL2OrderAndTrade();
	return i;
};




///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct L2MdApiWrap : L2MdApi, wrapper < L2MdApi >
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
		PyLock lock;

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
		PyLock lock;

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
		PyLock lock;

		try
		{
			this->get_override("onRspUserLogout")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSubL2MarketData(dict data, dict error, int id, bool last)
	{
		PyLock lock;

		try
		{
			this->get_override("onRspSubL2MarketData")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUnSubL2MarketData(dict data, dict error, int id, bool last)
	{
		PyLock lock;

		try
		{
			this->get_override("onRspUnSubL2MarketData")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSubL2Index(dict data, dict error, int id, bool last)
	{
		PyLock lock;

		try
		{
			this->get_override("onRspSubL2Index")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUnSubL2Index(dict data, dict error, int id, bool last)
	{
		PyLock lock;

		try
		{
			this->get_override("onRspUnSubL2Index")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnL2MarketData(dict data)
	{
		PyLock lock;

		try
		{
			this->get_override("onRtnL2MarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnL2Index(dict data)
	{
		PyLock lock;

		try
		{
			this->get_override("onRtnL2Index")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSubL2OrderAndTrade(dict error, int id, bool last)
	{
		PyLock lock;

		try
		{
			this->get_override("onRspSubL2OrderAndTrade")(error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUnSubL2OrderAndTrade(dict error, int id, bool last)
	{
		PyLock lock;

		try
		{
			this->get_override("onRspUnSubL2OrderAndTrade")(error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnL2Order(dict data)
	{
		PyLock lock;

		try
		{
			this->get_override("onRtnL2Order")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnL2Trade(dict data)
	{
		PyLock lock;

		try
		{
			this->get_override("onRtnL2Trade")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onNtfCheckOrderList(string instrumentID, string functionCode)
	{
		PyLock lock;

		try
		{
			this->get_override("onNtfCheckOrderList")(instrumentID, functionCode);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnltsl2)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<L2MdApiWrap, boost::noncopyable>("L2MdApi")
		.def("createFtdcL2MDUserApi", &L2MdApiWrap::createFtdcL2MDUserApi)
		.def("release", &L2MdApiWrap::release)
		.def("init", &L2MdApiWrap::init)
		.def("join", &L2MdApiWrap::join)
		.def("exit", &L2MdApiWrap::exit)
		.def("getTradingDay", &L2MdApiWrap::getTradingDay)
		.def("registerFront", &L2MdApiWrap::registerFront)
		.def("subscribeL2MarketData", &L2MdApiWrap::subscribeL2MarketData)
		.def("unSubscribeL2MarketData", &L2MdApiWrap::unSubscribeL2MarketData)
		.def("subscribeL2Index", &L2MdApiWrap::subscribeL2Index)
		.def("unSubscribeL2Index", &L2MdApiWrap::unSubscribeL2Index)
		.def("subscribeL2OrderAndTrade", &L2MdApiWrap::subscribeL2OrderAndTrade)
		.def("unSubscribeL2OrderAndTrade", &L2MdApiWrap::unSubscribeL2OrderAndTrade)
		.def("reqUserLogin", &L2MdApiWrap::reqUserLogin)
		.def("reqUserLogout", &L2MdApiWrap::reqUserLogout)

		.def("onFrontConnected", pure_virtual(&L2MdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&L2MdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&L2MdApiWrap::onHeartBeatWarning))
		.def("onRspError", pure_virtual(&L2MdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&L2MdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&L2MdApiWrap::onRspUserLogout))
		.def("onRspSubL2MarketData", pure_virtual(&L2MdApiWrap::onRspSubL2MarketData))
		.def("onRspUnSubL2MarketData", pure_virtual(&L2MdApiWrap::onRspUnSubL2MarketData))
		.def("onRspSubL2Index", pure_virtual(&L2MdApiWrap::onRspSubL2Index))
		.def("onRspUnSubL2Index", pure_virtual(&L2MdApiWrap::onRspUnSubL2Index))
		.def("onRtnL2MarketData", pure_virtual(&L2MdApiWrap::onRtnL2MarketData))
		.def("onRtnL2Index", pure_virtual(&L2MdApiWrap::onRtnL2Index))
		.def("onRspSubL2OrderAndTrade", pure_virtual(&L2MdApiWrap::onRspSubL2OrderAndTrade))
		.def("onRspUnSubL2OrderAndTrade", pure_virtual(&L2MdApiWrap::onRspUnSubL2OrderAndTrade))
		.def("onRtnL2Order", pure_virtual(&L2MdApiWrap::onRtnL2Order))
		.def("onRtnL2Trade", pure_virtual(&L2MdApiWrap::onRtnL2Trade))
		.def("onNtfCheckOrderList", pure_virtual(&L2MdApiWrap::onNtfCheckOrderList))
		;
};