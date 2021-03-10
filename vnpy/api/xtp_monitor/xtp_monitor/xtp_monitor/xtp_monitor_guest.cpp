// xtp_monitor_guest.cpp : 定义 DLL 应用程序的导出函数。
//

#include "xtp_monitor_guest.h"



///-------------------------------------------------------------------------------------
///C++的回调函数
///-------------------------------------------------------------------------------------

int32_t MonitorApi::OnClientLogin(const char* username, const char* password, const char* mac_add, const char* ip)
{
	int i = this->onClientLogin(username, password, mac_add, ip);
	return i;
};

int32_t MonitorApi::OnStart()
{
	int i = this->onStart();
	return i;
};

int32_t MonitorApi::OnStop()
{
	int i = this->onStop();
	return i;
};

void MonitorApi::OnDisconnected()
{
	this->onDisconnected();
};

int32_t MonitorApi::OnMonitorClientSetParameter(const char* key, const char* value)
{
	int i = this->onMonitorClientSetParameter(key, value);
	return i;
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

int MonitorApi::connectToMonitor(string ip, int port, string user, bool strategy_is_start)
{
	int i = ConnectToMonitor(ip.c_str(), port, user.c_str(), strategy_is_start);
	return i;
};

int MonitorApi::sendMsg(int level, string topic, string log_text, int alarm_wav_index)
{
	int i = SendMsg(level, topic.c_str(), log_text.c_str(), alarm_wav_index);
};

dict MonitorApi::getApiLastError()
{
	XTPHRI last_error = { 0 };
	GetApiLastError(&last_error);

	dict error;
	error["error_id"] = last_error.error_id;
	error["error_msg"] = last_error.error_msg;
	return error;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMonitorApi : public MonitorApi
{
public:
	using MonitorApi::MonitorApi;

	int onClientLogin(string username, string password, string mac_add, string ip) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MonitorApi, onClientLogin, username, password, mac_add, ip);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	int onStart() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MonitorApi, onStart);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	int onStop() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MonitorApi, onStop);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onDisconnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MonitorApi, onDisconnected);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	int onMonitorClientSetParameter(string key, string value) override
	{
		try
		{
			PYBIND11_OVERLOAD(int, MonitorApi, onMonitorClientSetParameter);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};




};


PYBIND11_MODULE(xtp_monitor_guest, m)
{
	class_<MonitorApi, PyMonitorApi> MonitorApi(m, "MonitorApi", module_local());
	MonitorApi
		.def(init<>())
		.def("connectToMonitor", &MonitorApi::connectToMonitor)
		.def("sendMsg", &MonitorApi::sendMsg)
		.def("getApiLastError", &MonitorApi::getApiLastError)
		.def("onClientLogin", &MonitorApi::onClientLogin)
		.def("onStart", &MonitorApi::onStart)
		.def("onStop", &MonitorApi::onStop)
		.def("onDisconnected", &MonitorApi::onDisconnected)
		.def("onMonitorClientSetParameter", &MonitorApi::onMonitorClientSetParameter)
		;


}