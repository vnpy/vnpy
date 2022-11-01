// vnmonitor.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnmonitor.h"


MonitorApi::MonitorApi()
{
	if (!api)
	{
		api = this;
	}

	RegisterMonitorClientLoginFunc(&OnClientLogin);
	RegisterStartFunc(&OnStart);
	RegisterStopFunc(&OnStop);
	RegisterDisconnectedFunc(&OnDisconnected);
	RegisterSetParameterFunc(&OnMonitorClientSetParameter);
}

///-------------------------------------------------------------------------------------
///C++的回调函数
///-------------------------------------------------------------------------------------

int32_t OnClientLogin(const char* username, const char* password, const char* mac_add, const char* ip)
{   
	gil_scoped_acquire acquire;
	int i = api->onClientLogin(username, password, mac_add, ip);
	return i;
};

int32_t OnStart()
{   
	gil_scoped_acquire acquire;
	int i = api->onStart();
	return i;
};

int32_t OnStop()
{   
	gil_scoped_acquire acquire;
	int i = api->onStop();
	return i;
};

void OnDisconnected()
{   
	gil_scoped_acquire acquire;
	api->onDisconnected();
};

int32_t OnMonitorClientSetParameter(const char* key, const char* value)
{   
	gil_scoped_acquire acquire;
	int i = api->onMonitorClientSetParameter(key, value);
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
	return i;
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
			PYBIND11_OVERLOAD(int, MonitorApi, onClientLogin, username, password, mac_add, ip);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
			return -1;
		}
	};

	int onStart() override
	{
		try
		{
			PYBIND11_OVERLOAD(int, MonitorApi, onStart);
			return 0;
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
			return -1;
		}
	};

	int onStop() override
	{
		try
		{
			PYBIND11_OVERLOAD(int, MonitorApi, onStop);
			return 0;
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
			return -1;
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
			PYBIND11_OVERLOAD(int, MonitorApi, onMonitorClientSetParameter, key, value);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
			return -1;
		}
	};
};


PYBIND11_MODULE(vnmonitor, m)
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