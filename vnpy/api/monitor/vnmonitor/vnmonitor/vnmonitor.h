#pragma once

#ifdef WIN32
#include "pch.h"
#endif

#include "pybind11/pybind11.h"
#include "xtp_monitor_guest_api.h"
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <codecvt>
#include <condition_variable>
#include <locale>

using namespace pybind11;
using namespace std;


class MonitorApi
{
private:
	MonitorApi()
	{
	    RegisterMonitorClientLoginFunc(&this->OnClientLogin);
		RegisterStartFunc(&this->OnStart);
		RegisterStopFunc(&this->OnStop);
		RegisterDisconnectedFunc(&this->OnDisconnected);
		RegisterSetParameterFunc(&this->OnMonitorClientSetParameter);
	}

	~MonitorApi()
	{

	}

public:

	//C++回调函数

	int32_t OnClientLogin(const char* username, const char* password, const char* mac_add, const char* ip);

	int32_t OnStart();

	int32_t OnStop();

	void OnDisconnected();

	int32_t OnMonitorClientSetParameter(const char* key, const char* value);

	//Python回调函数
	virtual int onClientLogin(string username, string password, string mac_add, string ip) {};

	virtual int onStart() {};

	virtual int onStop() {};

	virtual void onDisconnected() {};

	virtual int onMonitorClientSetParameter(string key, string value) {};

	//主动函数
	int connectToMonitor(string ip, int port, string user, bool strategy_is_start) ;

	int sendMsg(int level, string topic, string log_text, int alarm_wav_index) ;

	dict getApiLastError() ;

};