// vnnhmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnnhmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------
void MdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;

	this->task_queue.push(task);
};

void MdApi::OnFrontDisConnected()
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;

	this->task_queue.push(task);
};

void MdApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;

	int *task_data = new int();
	*task_data = nTimeLapse;
	task.task_data = task_data;

	this->task_queue.push(task);
};

void MdApi::OnRspError(ERRORMSGINFO_t &pRspInfo, TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	ERRORMSGINFO_t *task_error = new ERRORMSGINFO_t();
	*task_error = pRspInfo;
	task.task_error = task_error;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRtnMarketData(STKMarketData_t &pData)
{
	Task task = Task();
	task.task_name = ONRTNMARKETDATA;

	STKMarketData_t *task_data = new STKMarketData_t();
	*task_data = pData;
	task.task_data = task_data;

	this->task_queue.push(task);
};

void MdApi::OnRspUtpLogin(const RspUtpLoginField_t& rsp, TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPUTPLOGIN;

	RspUtpLoginField_t *task_data = new RspUtpLoginField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspUtpLogout(const RspUtpLogoutField_t& rsp, TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPUTPLOGOUT;

	RspUtpLogoutField_t *task_data = new RspUtpLogoutField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspSubscribe(const RspSubscribeField_t& rsp, TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBE;

	RspSubscribeField_t *task_data = new RspSubscribeField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspUnSubscribe(const RspUnSubscribeField_t& rsp, TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBSCRIBE;

	RspUnSubscribeField_t *task_data = new RspUnSubscribeField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspQryExchange(const RspQryExchangeField_t& rsp, TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;

	RspQryExchangeField_t *task_data = new RspQryExchangeField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

	this->task_queue.push(task);
};

void MdApi::OnRspQryInstrument(const RspQryInstrumentField_t& rsp, TSequenceIDType nRequestID)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;

	RspQryInstrumentField_t *task_data = new RspQryInstrumentField_t();
	*task_data = rsp;
	task.task_data = task_data;

	task.task_id = nRequestID;

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
				this->processFrontDisConnected(&task);
				break;
			}

			case ONHEARTBEATWARNING:
			{
				this->processHeartBeatWarning(&task);
				break;
			}

			case ONRSPERROR:
			{
				this->processRspError(&task);
				break;
			}

			case ONRTNMARKETDATA:
			{
				this->processRtnMarketData(&task);
				break;
			}

			case ONRSPUTPLOGIN:
			{
				this->processRspUtpLogin(&task);
				break;
			}

			case ONRSPUTPLOGOUT:
			{
				this->processRspUtpLogout(&task);
				break;
			}

			case ONRSPSUBSCRIBE:
			{
				this->processRspSubscribe(&task);
				break;
			}

			case ONRSPUNSUBSCRIBE:
			{
				this->processRspUnSubscribe(&task);
				break;
			}

			case ONRSPQRYEXCHANGE:
			{
				this->processRspQryExchange(&task);
				break;
			}

			case ONRSPQRYINSTRUMENT:
			{
				this->processRspQryInstrument(&task);
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

void MdApi::processFrontDisConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisConnected();
};

void MdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_id);
};

void MdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		ERRORMSGINFO_t *task_data = (ERRORMSGINFO_t*)task->task_data;
		data["error_code"] = task_data->error_code;
		data["error_message"] = toUtf(task_data->error_message);
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		data["oms_server_id"] = task_data->oms_server_id;
		delete task_data;
	}
	this->onRspError(data, task->task_id);
};

void MdApi::processRtnMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		STKMarketData_t *task_data = (STKMarketData_t*)task->task_data;
		data["trading_day"] = toUtf(task_data->trading_day);
		data["update_time"] = toUtf(task_data->update_time);
		data["update_millisec"] = task_data->update_millisec;
		data["update_sequence"] = task_data->update_sequence;
		data["instrument_id"] = toUtf(task_data->instrument_id);
		data["exchange_id"] = toUtf(task_data->exchange_id);
		data["exchange_inst_id"] = toUtf(task_data->exchange_inst_id);
		data["instrument_status"] = task_data->instrument_status;
		data["last_price"] = task_data->last_price;
		data["volume"] = task_data->volume;
		data["last_volume"] = task_data->last_volume;
		data["turnover"] = task_data->turnover;
		data["open_interest"] = task_data->open_interest;
		data["open_price"] = task_data->open_price;
		data["highest_price"] = task_data->highest_price;
		data["lowest_price"] = task_data->lowest_price;
		data["close_price"] = task_data->close_price;
		data["settlement_price"] = task_data->settlement_price;
		data["average_price"] = task_data->average_price;
		data["change_price"] = task_data->change_price;
		data["change_markup"] = task_data->change_markup;
		data["change_swing"] = task_data->change_swing;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["pre_settlement_price"] = task_data->pre_settlement_price;
		data["pre_close_price"] = task_data->pre_close_price;
		data["pre_open_interest"] = task_data->pre_open_interest;
		data["pre_delta"] = task_data->pre_delta;
		data["curr_delta"] = task_data->curr_delta;
		data["best_ask_price"] = task_data->best_ask_price;
		data["best_ask_volume"] = task_data->best_ask_volume;
		data["best_bid_price"] = task_data->best_bid_price;
		data["best_bid_volume"] = task_data->best_bid_volume;
		data["ask_price1"] = task_data->ask_price1;
		data["ask_volume1"] = task_data->ask_volume1;
		data["bid_price1"] = task_data->bid_price1;
		data["bid_volume1"] = task_data->bid_volume1;
		data["ask_price2"] = task_data->ask_price2;
		data["ask_volume2"] = task_data->ask_volume2;
		data["bid_price2"] = task_data->bid_price2;
		data["bid_volume2"] = task_data->bid_volume2;
		data["ask_price3"] = task_data->ask_price3;
		data["ask_volume3"] = task_data->ask_volume3;
		data["bid_price3"] = task_data->bid_price3;
		data["bid_volume3"] = task_data->bid_volume3;
		data["ask_price4"] = task_data->ask_price4;
		data["ask_volume4"] = task_data->ask_volume4;
		data["bid_price4"] = task_data->bid_price4;
		data["bid_volume4"] = task_data->bid_volume4;
		data["ask_price5"] = task_data->ask_price5;
		data["ask_volume5"] = task_data->ask_volume5;
		data["bid_price5"] = task_data->bid_price5;
		data["bid_volume5"] = task_data->bid_volume5;
		data["ask_price6"] = task_data->ask_price6;
		data["ask_volume6"] = task_data->ask_volume6;
		data["bid_price6"] = task_data->bid_price6;
		data["bid_volume6"] = task_data->bid_volume6;
		data["ask_price7"] = task_data->ask_price7;
		data["ask_volume7"] = task_data->ask_volume7;
		data["bid_price7"] = task_data->bid_price7;
		data["bid_volume7"] = task_data->bid_volume7;
		data["ask_price8"] = task_data->ask_price8;
		data["ask_volume8"] = task_data->ask_volume8;
		data["bid_price8"] = task_data->bid_price8;
		data["bid_volume8"] = task_data->bid_volume8;
		data["ask_price9"] = task_data->ask_price9;
		data["ask_volume9"] = task_data->ask_volume9;
		data["bid_price9"] = task_data->bid_price9;
		data["bid_volume9"] = task_data->bid_volume9;
		data["ask_price10"] = task_data->ask_price10;
		data["ask_volume10"] = task_data->ask_volume10;
		data["bid_price10"] = task_data->bid_price10;
		data["bid_volume10"] = task_data->bid_volume10;
		data["md_source"] = toUtf(task_data->md_source);
		delete task_data;
	}
	this->onRtnMarketData(data);
};

void MdApi::processRspUtpLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspUtpLoginField_t *task_data = (RspUtpLoginField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["session_public_key"] = toUtf(task_data->session_public_key);
		data["utp_checking_server_id"] = toUtf(task_data->utp_checking_server_id);
		data["utp_checking_server_time"] = task_data->utp_checking_server_time;
		data["last_login_ip_address"] = toUtf(task_data->last_login_ip_address);
		data["last_login_time"] = task_data->last_login_time;
		data["session_encrypted"] = task_data->session_encrypted;
		delete task_data;
	}
	this->onRspUtpLogin(data, task->task_id);
};

void MdApi::processRspUtpLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspUtpLogoutField_t *task_data = (RspUtpLogoutField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		delete task_data;
	}
	this->onRspUtpLogout(data, task->task_id);
};

void MdApi::processRspSubscribe(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspSubscribeField_t *task_data = (RspSubscribeField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["routing_key"] = toUtf(task_data->routing_key[0]);
		delete task_data;
	}
	this->onRspSubscribe(data, task->task_id);
};

void MdApi::processRspUnSubscribe(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspUnSubscribeField_t *task_data = (RspUnSubscribeField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["routing_key"] = toUtf(task_data->routing_key[0]);
		delete task_data;
	}
	this->onRspUnSubscribe(data, task->task_id);
};

void MdApi::processRspQryExchange(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspQryExchangeField_t *task_data = (RspQryExchangeField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		data["oms_server_id"] = task_data->oms_server_id;
		data["exchange_id"] = toUtf(task_data->exchange_id);
		data["exchange_name"] = toUtf(task_data->exchange_name);
		data["exchange_status"] = task_data->exchange_status;
		delete task_data;
	}
	this->onRspQryExchange(data, task->task_id);
};

void MdApi::processRspQryInstrument(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspQryInstrumentField_t *task_data = (RspQryInstrumentField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		data["oms_server_id"] = task_data->oms_server_id;
		data["product_id"] = toUtf(task_data->product_id);
		data["product_name"] = toUtf(task_data->product_name);
		data["exchange_id"] = toUtf(task_data->exchange_id);
		data["product_class"] = task_data->product_class;
		data["instrument_id"] = toUtf(task_data->instrument_id);
		data["instrument_name"] = toUtf(task_data->instrument_name);
		data["instrument_class"] = task_data->instrument_class;
		data["instrument_status"] = task_data->instrument_status;
		data["delivery_year"] = task_data->delivery_year;
		data["delivery_month"] = task_data->delivery_month;
		data["volume_multiple"] = task_data->volume_multiple;
		data["price_tick"] = task_data->price_tick;
		data["price_tick_dividend"] = task_data->price_tick_dividend;
		data["max_marketorder_volume"] = task_data->max_marketorder_volume;
		data["min_marketorder_volume"] = task_data->min_marketorder_volume;
		data["max_limitorder_volume"] = task_data->max_limitorder_volume;
		data["min_limitorder_volume"] = task_data->min_limitorder_volume;
		data["create_date"] = toUtf(task_data->create_date);
		data["open_date"] = toUtf(task_data->open_date);
		data["expire_date"] = toUtf(task_data->expire_date);
		data["last_trading_date"] = toUtf(task_data->last_trading_date);
		data["start_delivery_date"] = toUtf(task_data->start_delivery_date);
		data["end_delivery_date"] = toUtf(task_data->end_delivery_date);
		data["first_notice_date"] = toUtf(task_data->first_notice_date);
		delete task_data;
	}
	this->onRspQryInstrument(data, task->task_id);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createMdApi()
{
	this->api = CNhMdApi::CreateMdApi();
	this->api->RegisterSpi(this);
};

void MdApi::release()
{
	this->api->Release();
};

void MdApi::init()
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);

	this->api->Init();
};

string MdApi::getVersion()
{
	int major;
	int minor;
	string version = this->api->GetVersion(major, minor);
	return version;
}

int MdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

void MdApi::registerFront(string address)
{
	this->api->RegisterFront((char*)address.c_str());
};

void MdApi::registerNameServer(string server)
{
	this->api->RegisterNameServer((char*)server.c_str());
};

int MdApi::reqUtpLogin(const dict &req, int reqid)
{
	ReqUtpLoginField_t myreq = ReqUtpLoginField_t();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "developer_code", myreq.developer_code);
	getString(req, "developer_license", myreq.developer_license);
	getString(req, "user_id", myreq.user_id);
	getString(req, "user_password", myreq.user_password);
	getString(req, "user_one_time_password", myreq.user_one_time_password);
	getString(req, "user_ca_info", myreq.user_ca_info);
	int i = this->api->ReqUtpLogin(myreq, reqid);
	return i;
};

int MdApi::reqUtpLogout(int reqid)
{
	int i = this->api->ReqUtpLogout(reqid);
	return i;
};

int MdApi::reqSubscribe(string symbol, int reqid)
{
	char* buffer = (char*)symbol.c_str();

	ReqSubscribeField_t myreq = ReqSubscribeField_t();
	memset(&myreq, 0, sizeof(myreq));
	strcpy(myreq.routing_key[0], symbol.c_str());
	
	int i = this->api->ReqSubscribe(myreq, reqid);
	return i;
};

int MdApi::reqUnSubscribe(string symbol, int reqid)
{
	char* buffer = (char*)symbol.c_str();

	ReqUnSubscribeField_t myreq = ReqUnSubscribeField_t();
	memset(&myreq, 0, sizeof(myreq));
	strcpy(myreq.routing_key[0], symbol.c_str());

	int i = this->api->ReqUnSubscribe(myreq, reqid);
	return i;
};

int MdApi::reqAuthUserPasswor(const dict &req, int reqid)
{
	ReqAuthUserPassworField_t myreq = ReqAuthUserPassworField_t();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "user_id", myreq.user_id);
	getString(req, "password", myreq.password);
	getInt(req, "save_int", &myreq.save_int);
	getDouble(req, "save_double", &myreq.save_double);
	getString(req, "save_string", myreq.save_string);
	int i = this->api->ReqAuthUserPasswor(myreq, reqid);
	return i;
};

int MdApi::reqQryExchange(const dict &req, int reqid)
{
	ReqQryExchangeField_t myreq = ReqQryExchangeField_t();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "oms_server_id", &myreq.oms_server_id);
	int i = this->api->ReqQryExchange(myreq, reqid);
	return i;
};

int MdApi::reqQryInstrument(const dict &req, int reqid)
{
	ReqQryInstrumentField_t myreq = ReqQryInstrumentField_t();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "oms_server_id", &myreq.oms_server_id);
	getString(req, "exchange_id", myreq.exchange_id);
	getString(req, "product_id", myreq.product_id);
	getString(req, "instrument_id", myreq.instrument_id);
	getChar(req, "product_class", &myreq.product_class);
	int i = this->api->ReqQryInstrument(myreq, reqid);
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMdApi : public MdApi
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

	void onFrontDisConnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onFrontDisConnected);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onHeartBeatWarning(int timeLapse) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onHeartBeatWarning, timeLapse);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspError(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspError, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnMarketData(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRtnMarketData, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUtpLogin(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspUtpLogin, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUtpLogout(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspUtpLogout, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspSubscribe(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspSubscribe, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUnSubscribe(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspUnSubscribe, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryExchange(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspQryExchange, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInstrument(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspQryInstrument, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vnnhmd, m)
{
	class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
	mdapi
		.def(init<>())
		.def("createMdApi", &MdApi::createMdApi)
		.def("release", &MdApi::release)
		.def("init", &MdApi::init)
		.def("getVersion", &MdApi::getVersion)
		.def("registerFront", &MdApi::registerFront)
		.def("registerNameServer", &MdApi::registerNameServer)
		.def("exit", &MdApi::exit)
		.def("reqUtpLogin", &MdApi::reqUtpLogin)
		.def("reqUtpLogout", &MdApi::reqUtpLogout)
		.def("reqSubscribe", &MdApi::reqSubscribe)
		.def("reqUnSubscribe", &MdApi::reqUnSubscribe)
		.def("reqAuthUserPasswor", &MdApi::reqAuthUserPasswor)
		.def("reqQryExchange", &MdApi::reqQryExchange)
		.def("reqQryInstrument", &MdApi::reqQryInstrument)

		.def("onFrontConnected", &MdApi::onFrontConnected)
		.def("onFrontDisConnected", &MdApi::onFrontDisConnected)
		.def("onHeartBeatWarning", &MdApi::onHeartBeatWarning)
		.def("onRspError", &MdApi::onRspError)
		.def("onRtnMarketData", &MdApi::onRtnMarketData)
		.def("onRspUtpLogin", &MdApi::onRspUtpLogin)
		.def("onRspUtpLogout", &MdApi::onRspUtpLogout)
		.def("onRspSubscribe", &MdApi::onRspSubscribe)
		.def("onRspUnSubscribe", &MdApi::onRspUnSubscribe)
		.def("onRspQryExchange", &MdApi::onRspQryExchange)
		.def("onRspQryInstrument", &MdApi::onRspQryInstrument)
		;
}
