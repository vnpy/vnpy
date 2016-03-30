// TdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnsgittd.h"



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

void TdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(char *pErrMsg)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;

	if (pErrMsg)
	{
		task.task_data = *pErrMsg;
	}
	else
	{
		char empty_data = char();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CSgitFtdcRspUserLoginField *pRspUserLogin, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CSgitFtdcRspUserLoginField empty_data = CSgitFtdcRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(CSgitFtdcUserLogoutField *pUserLogout, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pUserLogout)
	{
		task.task_data = *pUserLogout;
	}
	else
	{
		CSgitFtdcUserLogoutField empty_data = CSgitFtdcUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspUserPasswordUpdate(CSgitFtdcUserPasswordUpdateField *pUserPasswordUpdate, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;

	if (pUserPasswordUpdate)
	{
		task.task_data = *pUserPasswordUpdate;
	}
	else
	{
		CSgitFtdcUserPasswordUpdateField empty_data = CSgitFtdcUserPasswordUpdateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CSgitFtdcInputOrderField *pInputOrder, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;

	if (pInputOrder)
	{
		task.task_data = *pInputOrder;
	}
	else
	{
		CSgitFtdcInputOrderField empty_data = CSgitFtdcInputOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CSgitFtdcInputOrderActionField *pInputOrderAction, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;

	if (pInputOrderAction)
	{
		task.task_data = *pInputOrderAction;
	}
	else
	{
		CSgitFtdcInputOrderActionField empty_data = CSgitFtdcInputOrderActionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CSgitFtdcOrderField *pOrder, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CSgitFtdcOrderField empty_data = CSgitFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingAccount(CSgitFtdcTradingAccountField *pTradingAccount, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGACCOUNT;

	if (pTradingAccount)
	{
		task.task_data = *pTradingAccount;
	}
	else
	{
		CSgitFtdcTradingAccountField empty_data = CSgitFtdcTradingAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestor(CSgitFtdcInvestorField *pInvestor, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTOR;

	if (pInvestor)
	{
		task.task_data = *pInvestor;
	}
	else
	{
		CSgitFtdcInvestorField empty_data = CSgitFtdcInvestorField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrument(CSgitFtdcInstrumentField *pInstrument, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;

	if (pInstrument)
	{
		task.task_data = *pInstrument;
	}
	else
	{
		CSgitFtdcInstrumentField empty_data = CSgitFtdcInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CSgitFtdcOrderField *pOrder, CSgitFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CSgitFtdcOrderField empty_data = CSgitFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CSgitFtdcTradeField *pTrade)
{
	Task task = Task();
	task.task_name = ONRTNTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CSgitFtdcTradeField empty_data = CSgitFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CSgitFtdcInstrumentStatusField *pInstrumentStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;

	if (pInstrumentStatus)
	{
		task.task_data = *pInstrumentStatus;
	}
	else
	{
		CSgitFtdcInstrumentStatusField empty_data = CSgitFtdcInstrumentStatusField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPositionDetail(CSgitFtdcInvestorPositionDetailField *pInvestorPositionDetail, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITIONDETAIL;

	if (pInvestorPositionDetail)
	{
		task.task_data = *pInvestorPositionDetail;
	}
	else
	{
		CSgitFtdcInvestorPositionDetailField empty_data = CSgitFtdcInvestorPositionDetailField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CSgitFtdcInvestorPositionField *pInvestorPosition, CSgitFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;

	if (pInvestorPosition)
	{
		task.task_data = *pInvestorPosition;
	}
	else
	{
		CSgitFtdcInvestorPositionField empty_data = CSgitFtdcInvestorPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSgitFtdcRspInfoField empty_error = CSgitFtdcRspInfoField();
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

		case ONRSPUSERPASSWORDUPDATE:
		{
			this->processRspUserPasswordUpdate(task);
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

		case ONRSPQRYINSTRUMENT:
		{
			this->processRspQryInstrument(task);
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

		case ONRTNINSTRUMENTSTATUS:
		{
			this->processRtnInstrumentStatus(task);
			break;
		}

		case ONRSPQRYINVESTORPOSITIONDETAIL:
		{
			this->processRspQryInvestorPositionDetail(task);
			break;
		}

		case ONRSPQRYINVESTORPOSITION:
		{
			this->processRspQryInvestorPosition(task);
			break;
		}

		};
	}
};

void TdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	string msg = any_cast<string>(task.task_data);
	this->onFrontDisconnected(msg);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CSgitFtdcRspUserLoginField task_data = any_cast<CSgitFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["SHFETime"] = task_data.SHFETime;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["FFEXTime"] = task_data.FFEXTime;
	data["BrokerID"] = task_data.BrokerID;
	data["DCETime"] = task_data.DCETime;
	data["LoginTime"] = task_data.LoginTime;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CSgitFtdcUserLogoutField task_data = any_cast<CSgitFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	PyLock lock;
	CSgitFtdcUserPasswordUpdateField task_data = any_cast<CSgitFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderInsert(Task task)
{
	PyLock lock;
	CSgitFtdcInputOrderField task_data = any_cast<CSgitFtdcInputOrderField>(task.task_data);
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

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	PyLock lock;
	CSgitFtdcInputOrderActionField task_data = any_cast<CSgitFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["OrderActionRef"] = task_data.OrderActionRef;
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

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CSgitFtdcOrderField task_data = any_cast<CSgitFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
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
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
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
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CSgitFtdcTradingAccountField task_data = any_cast<CSgitFtdcTradingAccountField>(task.task_data);
	dict data;
	data["Mortgage"] = task_data.Mortgage;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["Interest"] = task_data.Interest;
	data["CashIn"] = task_data.CashIn;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["PreCredit"] = task_data.PreCredit;
	data["PreMortgage"] = task_data.PreMortgage;
	data["InterestBase"] = task_data.InterestBase;
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
	data["PreDeposit"] = task_data.PreDeposit;
	data["Credit"] = task_data.Credit;
	data["PreBalance"] = task_data.PreBalance;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["CloseProfit"] = task_data.CloseProfit;
	data["Deposit"] = task_data.Deposit;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CSgitFtdcInvestorField task_data = any_cast<CSgitFtdcInvestorField>(task.task_data);
	dict data;
	data["CommModelID"] = task_data.CommModelID;
	data["InvestorName"] = task_data.InvestorName;
	data["Mobile"] = task_data.Mobile;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["Telephone"] = task_data.Telephone;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Address"] = task_data.Address;
	data["InvestorGroupID"] = task_data.InvestorGroupID;
	data["OpenDate"] = task_data.OpenDate;
	data["IsActive"] = task_data.IsActive;
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CSgitFtdcInstrumentField task_data = any_cast<CSgitFtdcInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["PositionDateType"] = task_data.PositionDateType;
	data["LongMarginRatio"] = task_data.LongMarginRatio;
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
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["PriceTick"] = task_data.PriceTick;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	CSgitFtdcOrderField task_data = any_cast<CSgitFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["TraderID"] = task_data.TraderID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
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
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["SettlementID"] = task_data.SettlementID;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
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
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRtnOrder(data, error);
};

void TdApi::processRtnTrade(Task task)
{
	PyLock lock;
	CSgitFtdcTradeField task_data = any_cast<CSgitFtdcTradeField>(task.task_data);
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
	data["SettlementID"] = task_data.SettlementID;
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

void TdApi::processRtnInstrumentStatus(Task task)
{
	PyLock lock;
	CSgitFtdcInstrumentStatusField task_data = any_cast<CSgitFtdcInstrumentStatusField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["EnterTime"] = task_data.EnterTime;
	data["SettlementGroupID"] = task_data.SettlementGroupID;
	data["TradingSegmentSN"] = task_data.TradingSegmentSN;
	data["EnterReason"] = task_data.EnterReason;
	data["InstrumentStatus"] = task_data.InstrumentStatus;
	data["ExchangeInstID"] = task_data.ExchangeInstID;

	this->onRtnInstrumentStatus(data);
};

void TdApi::processRspQryInvestorPositionDetail(Task task)
{
	PyLock lock;
	CSgitFtdcInvestorPositionDetailField task_data = any_cast<CSgitFtdcInvestorPositionDetailField>(task.task_data);
	dict data;
	data["PositionProfitByDate"] = task_data.PositionProfitByDate;
	data["ExchMargin"] = task_data.ExchMargin;
	data["TradeType"] = task_data.TradeType;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["Direction"] = task_data.Direction;
	data["CloseAmount"] = task_data.CloseAmount;
	data["OpenPrice"] = task_data.OpenPrice;
	data["Volume"] = task_data.Volume;
	data["LastSettlementPrice"] = task_data.LastSettlementPrice;
	data["CloseVolume"] = task_data.CloseVolume;
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
	data["CombInstrumentID"] = task_data.CombInstrumentID;
	data["OpenDate"] = task_data.OpenDate;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPositionDetail(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CSgitFtdcInvestorPositionField task_data = any_cast<CSgitFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["PositionProfit"] = task_data.PositionProfit;
	data["Commission"] = task_data.Commission;
	data["MarginRateByVolume"] = task_data.MarginRateByVolume;
	data["CombPosition"] = task_data.CombPosition;
	data["CashIn"] = task_data.CashIn;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["CombLongFrozen"] = task_data.CombLongFrozen;
	data["CloseAmount"] = task_data.CloseAmount;
	data["PosiDirection"] = task_data.PosiDirection;
	data["YdPosition"] = task_data.YdPosition;
	data["MarginRateByMoney"] = task_data.MarginRateByMoney;
	data["OpenVolume"] = task_data.OpenVolume;
	data["CloseVolume"] = task_data.CloseVolume;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["InstrumentID"] = task_data.InstrumentID;
	data["PositionDate"] = task_data.PositionDate;
	data["CloseProfitByTrade"] = task_data.CloseProfitByTrade;
	data["PreMargin"] = task_data.PreMargin;
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
	data["CombShortFrozen"] = task_data.CombShortFrozen;
	data["CloseProfitByDate"] = task_data.CloseProfitByDate;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LongFrozenAmount"] = task_data.LongFrozenAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["CloseProfit"] = task_data.CloseProfit;
	data["UseMargin"] = task_data.UseMargin;

	CSgitFtdcRspInfoField task_error = any_cast<CSgitFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	//该函数为手动编写
	this->api = CSgitFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void TdApi::release()
{
	//该函数为手动编写
	this->api->Release();
};

void TdApi::init(bool isLogged)
{
	//该函数为手动编写
	this->api->Init(isLogged);
};

int TdApi::exit()
{
	//该函数为手动编写
	this->api->Release();
	this->api = NULL;
	return 1;
};

int TdApi::join()
{
	int i = this->api->Join();
	return i;
}

string TdApi::getTradingDay()
{
	//该函数为手动编写
	string day = this->api->GetTradingDay();
	return day;
};

void TdApi::registerFront(string pszFrontAddress)
{
	//该函数为手动编写
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void TdApi::subscribePrivateTopic(int nType)
{
	//该函数为手动编写
	Sgit_TE_RESUME_TYPE type = Sgit_TE_RESUME_TYPE(nType);
	this->api->SubscribePrivateTopic(type);
};

void TdApi::subscribePublicTopic(int nType)
{
	//该函数为手动编写
	Sgit_TE_RESUME_TYPE type = Sgit_TE_RESUME_TYPE(nType);
	this->api->SubscribePublicTopic(type);
};

int TdApi::ready()
{
	//该函数为手动编写
	int i = this->api->Ready();
	return i;
}

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CSgitFtdcReqUserLoginField myreq = CSgitFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "UserProductInfo", myreq.UserProductInfo);
	getString(req, "UserID", myreq.UserID);
	getString(req, "TradingDay", myreq.TradingDay);
	getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "ClientIPAddress", myreq.ClientIPAddress);
	getString(req, "OneTimePassword", myreq.OneTimePassword);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	getString(req, "Password", myreq.Password);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CSgitFtdcUserLogoutField myreq = CSgitFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CSgitFtdcUserPasswordUpdateField myreq = CSgitFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserID", myreq.UserID);
	getString(req, "NewPassword", myreq.NewPassword);
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CSgitFtdcInputOrderField myreq = CSgitFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getString(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getString(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getString(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getString(req, "GTDDate", myreq.GTDDate);
	getString(req, "BusinessUnit", myreq.BusinessUnit);
	getString(req, "OrderRef", myreq.OrderRef);
	getString(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CSgitFtdcInputOrderActionField myreq = CSgitFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getString(req, "UserID", myreq.UserID);
	getDouble(req, "LimitPrice", &myreq.LimitPrice);
	getString(req, "OrderRef", myreq.OrderRef);
	getString(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getString(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getInt(req, "FrontID", &myreq.FrontID);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
{
	CSgitFtdcQryOrderField myreq = CSgitFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InsertTimeStart", myreq.InsertTimeStart);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	getString(req, "OrderSysID", myreq.OrderSysID);
	getString(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CSgitFtdcQryTradingAccountField myreq = CSgitFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CSgitFtdcQryInvestorField myreq = CSgitFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
{
	CSgitFtdcQryInstrumentField myreq = CSgitFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "ExchangeInstID", myreq.ExchangeInstID);
	getString(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(dict req, int nRequestID)
{
	CSgitFtdcQryInvestorPositionDetailField myreq = CSgitFtdcQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPositionDetail(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CSgitFtdcQryInvestorPositionField myreq = CSgitFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getString(req, "InvestorID", myreq.InvestorID);
	getString(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

/*
int TdApi::reqMBLQuot(dict req, int nRequestID)
{
	CSgitMBLQuotReq myreq = CSgitMBLQuotReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "StartContractID", myreq.StartContractID);
	getString(req, "EndContractID", myreq.EndContractID);
	getString(req, "BsFlag", &myreq.BsFlag);
	int i = this->api->ReqMBLQuot(nRequestID, &myreq);
	return i;
};
*/


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

	virtual void onFrontDisconnected(string msg)
	{
		try
		{
			this->get_override("onFrontDisconnected")(msg);
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

	virtual void onRtnOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRtnOrder")(data, error);
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
};


BOOST_PYTHON_MODULE(vnsgittd)
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
		.def("ready", &TdApiWrap::ready)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqUserPasswordUpdate", &TdApiWrap::reqUserPasswordUpdate)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqQryOrder", &TdApiWrap::reqQryOrder)
		.def("reqQryTradingAccount", &TdApiWrap::reqQryTradingAccount)
		.def("reqQryInvestor", &TdApiWrap::reqQryInvestor)
		.def("reqQryInstrument", &TdApiWrap::reqQryInstrument)
		.def("reqQryInvestorPositionDetail", &TdApiWrap::reqQryInvestorPositionDetail)
		.def("reqQryInvestorPosition", &TdApiWrap::reqQryInvestorPosition)
		//.def("reqMBLQuot", &TdApiWrap::reqMBLQuot)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspUserPasswordUpdate))
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onRspQryOrder", pure_virtual(&TdApiWrap::onRspQryOrder))
		.def("onRspQryTradingAccount", pure_virtual(&TdApiWrap::onRspQryTradingAccount))
		.def("onRspQryInvestor", pure_virtual(&TdApiWrap::onRspQryInvestor))
		.def("onRspQryInstrument", pure_virtual(&TdApiWrap::onRspQryInstrument))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onRtnInstrumentStatus", pure_virtual(&TdApiWrap::onRtnInstrumentStatus))
		.def("onRspQryInvestorPositionDetail", pure_virtual(&TdApiWrap::onRspQryInvestorPositionDetail))
		.def("onRspQryInvestorPosition", pure_virtual(&TdApiWrap::onRspQryInvestorPosition))
		;
};