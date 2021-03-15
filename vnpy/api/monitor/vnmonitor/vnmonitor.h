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


int32_t OnClientLogin(const char* username, const char* password, const char* mac_add, const char* ip);

int32_t OnStart();

int32_t OnStop();

void OnDisconnected();

int32_t OnMonitorClientSetParameter(const char* key, const char* value);


class MonitorApi
{
private:


public:
	MonitorApi();
	~MonitorApi() {};

	virtual int onClientLogin(string username, string password, string mac_add, string ip) { return 0; };

	virtual int onStart() { return 0; };

	virtual int onStop() { return 0; };

	virtual void onDisconnected() {};

	virtual int onMonitorClientSetParameter(string key, string value) { return 0; };

	int connectToMonitor(string ip, int port, string user, bool strategy_is_start) ;

	int sendMsg(int level, string topic, string log_text, int alarm_wav_index) ;

	dict getApiLastError() ;

};


MonitorApi *api = NULL;