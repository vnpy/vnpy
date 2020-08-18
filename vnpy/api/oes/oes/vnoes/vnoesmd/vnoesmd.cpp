// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnoesmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------
int32 MdApi::OnConnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo, MdsApiSubscribeInfoT *pSubscribeInfo)
{
	Task task = Task();
	task.task_name = ONCONNECTED;
	task.task_int = channelType;

	if (pSessionInfo)
	{
		MdsApiSessionInfoT *task_data = new MdsApiSessionInfoT();
		*task_data = *pSessionInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);

	return EAGAIN;

};

int32 MdApi::OnDisconnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo)
{
	Task task = Task();
	task.task_name = ONDISCONNECTED;
	task.task_int = channelType;

	if (pSessionInfo)
	{
		MdsApiSessionInfoT *task_data = new MdsApiSessionInfoT();
		*task_data = *pSessionInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);

	return EAGAIN;
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
			case ONCONNECTED:
			{
				this->processConnected(&task);
				break;
			}

			case ONDISCONNECTED:
			{
				this->processDisconnected(&task);
				break;
			}


			};
		}
	}
	catch (const TerminatedError&)
	{
	}
};

int32 MdApi::processConnected(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		MdsApiSessionInfoT *task_data = (MdsApiSessionInfoT*)task->task_data;
		data["remoteHostNum"] = task_data->remoteHostNum;
		delete task_data;
	}
	this->onConnected(task->task_int, data);
};

int32 MdApi::processDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		MdsApiSessionInfoT *task_data = (MdsApiSessionInfoT*)task->task_data;
		data["remoteHostNum"] = task_data->remoteHostNum;
		delete task_data;
	}
	this->onDisconnected(task->task_int, data);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------
void MdApi::createMdApi()
{
	this->api = new MdsClientApi();
	this->api->RegisterSpi(this);
}


bool MdApi::loadCfg(string pCfgFile)
{
	bool i = this->api->LoadCfg((char*)pCfgFile.c_str());
	return i;
}


bool MdApi::setCustomizedIp(string pIpStr)
{
	bool i = this->api->SetCustomizedIp((char*)pIpStr.c_str());
	return i;
}

bool MdApi::setCustomizedMac(string pMacStr)
{
	bool  i = this->api->SetCustomizedMac((char*)pMacStr.c_str());
	return i;
}

bool MdApi::setCustomizedDriverId(string pDriverStr)
{
	bool  i = this->api->SetCustomizedDriverId((char*)pDriverStr.c_str());
	return i;
}

void MdApi::setThreadUsername(string pUsername)
{
	this->api->SetThreadUsername((char*)pUsername.c_str());
}


void MdApi::setThreadPassword(string pPassword)
{
	this->api->SetThreadPassword((char*)pPassword.c_str());
}


bool MdApi::init()
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);
	int32 LastClSeqNo;
	bool i = this->api->Start(&LastClSeqNo, 0);
	return i;
}

int MdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->Stop();
	this->api = NULL;
	return 1;
};


bool MdApi::subscribeMarketData(const dict &req1, const dict &req2)
{
	MdsMktDataRequestReqT myreq1 = MdsMktDataRequestReqT();
	memset(&myreq1, 0, sizeof(myreq1));
	getUint8(req1, "subMode", &myreq1.subMode);
	getUint8(req1, "tickType", &myreq1.tickType);
	getInt8(req1, "sseStockFlag", &myreq1.sseStockFlag);
	getInt8(req1, "sseIndexFlag", &myreq1.sseIndexFlag);
	getInt8(req1, "sseOptionFlag", &myreq1.sseOptionFlag);
	getInt8(req1, "szseStockFlag", &myreq1.szseStockFlag);
	getInt8(req1, "szseIndexFlag", &myreq1.szseIndexFlag);
	getInt8(req1, "szseOptionFlag", &myreq1.szseOptionFlag);
	getUint8(req1, "isRequireInitialMktData", &myreq1.isRequireInitialMktData);
	getUint8(req1, "__channelNos", &myreq1.__channelNos);
	getUint8(req1, "tickExpireType", &myreq1.tickExpireType);
	getUint8(req1, "tickRebuildFlag", &myreq1.tickRebuildFlag);
	getInt32(req1, "dataTypes", &myreq1.dataTypes);
	getInt32(req1, "beginTime", &myreq1.beginTime);
	getInt32(req1, "subSecurityCnt", &myreq1.subSecurityCnt);


	MdsMktDataRequestEntryT myreq2 = MdsMktDataRequestEntryT();
	memset(&myreq2, 0, sizeof(myreq2));
	getUint8(req2, "exchId", &myreq2.exchId);
	getUint8(req2, "mdProductType", &myreq2.mdProductType);
	getInt32(req2, "instrId", &myreq2.instrId);

	bool i = this->api->SubscribeMarketData(&myreq1, &myreq2);
	return i;

}


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMdApi : public MdApi
{
public:
	using MdApi::MdApi;

	void onConnected(int channelType, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onConnected, channelType, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onDisconnected(int channelType, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDisconnected, channelType, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};



};


PYBIND11_MODULE(vnoesmd, m)
{
	class_<MdApi, PyMdApi> MdApi(m, "MdApi", module_local());
	MdApi
		.def(init<>())
		.def("createMdApi", &MdApi::createMdApi)
		.def("loadCfg", &MdApi::loadCfg)
		.def("setCustomizedIp", &MdApi::setCustomizedIp)
		.def("setCustomizedMac", &MdApi::setCustomizedMac)
		.def("setCustomizedDriverId", &MdApi::setCustomizedDriverId)
		.def("setThreadUsername", &MdApi::setThreadUsername)
		.def("setThreadPassword", &MdApi::setThreadPassword)
		.def("init", &MdApi::init)
		.def("exit", &MdApi::exit)

		.def("onConnected", &MdApi::onConnected)
		.def("onDisconnected", &MdApi::onDisconnected)
		;

}
