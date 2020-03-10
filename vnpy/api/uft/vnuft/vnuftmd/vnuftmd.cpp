// vnuftmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnuftmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nResult)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nResult;
	this->task_queue.push(task);
};

void MdApi::OnRspDepthMarketDataSubscribe(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPDEPTHMARKETDATASUBSCRIBE;
	if (pRspInfo)
	{
		CHSRspInfoField *task_error = new CHSRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRspDepthMarketDataCancel(CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPDEPTHMARKETDATACANCEL;
	if (pRspInfo)
	{
		CHSRspInfoField *task_error = new CHSRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void MdApi::OnRtnDepthMarketData(CHSDepthMarketDataField *pDepthMarketData)
{
	Task task = Task();
	task.task_name = ONRTNDEPTHMARKETDATA;
	if (pDepthMarketData)
	{
		CHSDepthMarketDataField *task_data = new CHSDepthMarketDataField();
		*task_data = *pDepthMarketData;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};





///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void MdApi::processTask()
{
    try
    {
        while (this->active)
        {
            Task task = this->task_queue.pop();
            
            switch (task.task_name)
            {
			case ONFRONTCONNECTED:
			{
				this->processFrontConnected(&task);
				break;
			}

			case ONFRONTDISCONNECTED:
			{
				this->processFrontDisconnected(&task);
				break;
			}

			case ONRSPDEPTHMARKETDATASUBSCRIBE:
			{
				this->processRspDepthMarketDataSubscribe(&task);
				break;
			}

			case ONRSPDEPTHMARKETDATACANCEL:
			{
				this->processRspDepthMarketDataCancel(&task);
				break;
			}

			case ONRTNDEPTHMARKETDATA:
			{
				this->processRtnDepthMarketData(&task);
				break;
			}

            };
        }
    }
    catch (const TerminatedError&)
    {
    }
};

void MdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void MdApi::processRspDepthMarketDataSubscribe(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspDepthMarketDataSubscribe(error, task->task_id, task->task_last);
};

void MdApi::processRspDepthMarketDataCancel(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CHSRspInfoField *task_error = (CHSRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspDepthMarketDataCancel(error, task->task_id, task->task_last);
};

void MdApi::processRtnDepthMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CHSDepthMarketDataField *task_data = (CHSDepthMarketDataField*)task->task_data;
		data["TradingDay"] = task_data->TradingDay;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["LastPrice"] = task_data->LastPrice;
		data["PreSettlementPrice"] = task_data->PreSettlementPrice;
		data["PreClosePrice"] = task_data->PreClosePrice;
		data["OpenPrice"] = task_data->OpenPrice;
		data["HighestPrice"] = task_data->HighestPrice;
		data["LowestPrice"] = task_data->LowestPrice;
		data["TradeVolume"] = task_data->TradeVolume;
		data["TradeBalance"] = task_data->TradeBalance;
		data["OpenInterest"] = task_data->OpenInterest;
		data["ClosePrice"] = task_data->ClosePrice;
		data["SettlementPrice"] = task_data->SettlementPrice;
		data["UpperLimitPrice"] = task_data->UpperLimitPrice;
		data["LowerLimitPrice"] = task_data->LowerLimitPrice;
		data["PreDelta"] = task_data->PreDelta;
		data["CurrDelta"] = task_data->CurrDelta;
		data["UpdateTime"] = task_data->UpdateTime;
		data["BidPrice1"] = task_data->BidPrice1;
		data["BidVolume1"] = task_data->BidVolume1;
		data["AskPrice1"] = task_data->AskPrice1;
		data["AskVolume1"] = task_data->AskVolume1;
		data["BidPrice2"] = task_data->BidPrice2;
		data["BidVolume2"] = task_data->BidVolume2;
		data["AskPrice2"] = task_data->AskPrice2;
		data["AskVolume2"] = task_data->AskVolume2;
		data["BidPrice3"] = task_data->BidPrice3;
		data["BidVolume3"] = task_data->BidVolume3;
		data["AskPrice3"] = task_data->AskPrice3;
		data["AskVolume3"] = task_data->AskVolume3;
		data["BidPrice4"] = task_data->BidPrice4;
		data["BidVolume4"] = task_data->BidVolume4;
		data["AskPrice4"] = task_data->AskPrice4;
		data["AskVolume4"] = task_data->AskVolume4;
		data["BidPrice5"] = task_data->BidPrice5;
		data["BidVolume5"] = task_data->BidVolume5;
		data["AskPrice5"] = task_data->AskPrice5;
		data["AskVolume5"] = task_data->AskVolume5;
		data["AveragePrice"] = task_data->AveragePrice;
		data["PreOpenInterest"] = task_data->PreOpenInterest;
		data["InstrumentTradeStatus"] = task_data->InstrumentTradeStatus;
		data["OpenRestriction"] = toUtf(task_data->OpenRestriction);
		delete task_data;
	}
	this->onRtnDepthMarketData(data);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::newMdApi(string pszFlowPath)
{
	this->api = NewMdApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

int MdApi::init(string pszLicFile, string pszSafeLevel, string pszPwd, string pszSslFile, string pszSslPwd)
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);

	int i = this->api->Init((char*)pszLicFile.c_str(), (char*)pszSafeLevel.c_str(), (char*)pszPwd.c_str(), (char*)pszSslFile.c_str(), (char*)pszSslPwd.c_str());
	return i;
};

int MdApi::join()
{
	int i = this->api->Join();
	return i;
};

int MdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->ReleaseApi();
	this->api = NULL;
	return 1;
};

int MdApi::registerFront(string pszFrontAddress)
{
	int i = this->api->RegisterFront((char*)pszFrontAddress.c_str());
	return i;
};

int MdApi::registerFensServer(string pszFensAddress, string pszAccountID)
{
	int i = this->api->RegisterFensServer((char*)pszFensAddress.c_str(), (char*)pszAccountID.c_str());
	return i;
};

string MdApi::getApiErrorMsg(int nErrorCode)
{
	string error = this->api->GetApiErrorMsg(nErrorCode);
	return error;
};

int MdApi::reqDepthMarketDataSubscribe(const dict &req, int reqid)
{
	CHSReqDepthMarketDataField myreq = CHSReqDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);

	CHSReqDepthMarketDataField myreqs[1] = { myreq };
	int i = this->api->ReqDepthMarketDataSubscribe(myreqs, 1 ,reqid);
	return i;
};

int MdApi::reqDepthMarketDataCancel(const dict &req, int reqid)
{
	CHSReqDepthMarketDataField myreq = CHSReqDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "InstrumentID", myreq.InstrumentID);

	CHSReqDepthMarketDataField myreqs[1] = { myreq };
	int i = this->api->ReqDepthMarketDataCancel(myreqs, 1, reqid);
	return i;
};


///-------------------------------------------------------------------------------------
///Pybind11封装
///-------------------------------------------------------------------------------------

class PyMdApi: public MdApi
{
public:
	using MdApi::MdApi;

	void onFrontConnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onFrontConnected);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onFrontDisconnected(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onFrontDisconnected, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspDepthMarketDataSubscribe(const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspDepthMarketDataSubscribe, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspDepthMarketDataCancel(const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspDepthMarketDataCancel, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnDepthMarketData(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRtnDepthMarketData, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};


};


PYBIND11_MODULE(vnuftmd, m)
{
	class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
	mdapi
		.def(init<>())
		.def("newMdApi", &MdApi::newMdApi)
		.def("init", &MdApi::init)
		.def("join", &MdApi::join)
		.def("exit", &MdApi::exit)
		.def("registerFront", &MdApi::registerFront)
		.def("registerFensServer", &MdApi::registerFensServer)
		.def("reqDepthMarketDataSubscribe", &MdApi::reqDepthMarketDataSubscribe)
		.def("reqDepthMarketDataCancel", &MdApi::reqDepthMarketDataCancel)
		.def("getApiErrorMsg", &MdApi::getApiErrorMsg)
		.def("reqDepthMarketDataSubscribe", &MdApi::reqDepthMarketDataSubscribe)
		.def("reqDepthMarketDataCancel", &MdApi::reqDepthMarketDataCancel)

		.def("onFrontConnected", &MdApi::onFrontConnected)
		.def("onFrontDisconnected", &MdApi::onFrontDisconnected)
		.def("onRspDepthMarketDataSubscribe", &MdApi::onRspDepthMarketDataSubscribe)
		.def("onRspDepthMarketDataCancel", &MdApi::onRspDepthMarketDataCancel)
		.def("onRtnDepthMarketData", &MdApi::onRtnDepthMarketData)
		;

}
