//˵������

//ϵͳ
#ifdef WIN32
#include "stdafx.h"
#endif
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	
#include <boost/python/def.hpp>		
#include <boost/python/dict.hpp>	
#include <boost/python/object.hpp>	
#include <boost/python.hpp>			
#include <boost/thread.hpp>			
#include <boost/bind.hpp>			
#include <boost/any.hpp>			
#include <boost/locale.hpp>
//API
#include "ThostFtdcMdApi.h"

using namespace std;
using namespace boost::python;
using namespace boost;


#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONHEARTBEATWARNING 3
#define ONRSPUSERLOGIN 4
#define ONRSPUSERLOGOUT 5
#define ONRSPERROR 6
#define ONRSPSUBMARKETDATA 7
#define ONRSPUNSUBMARKETDATA 8
#define ONRSPSUBFORQUOTERSP 9
#define ONRSPUNSUBFORQUOTERSP 10
#define ONRTNDEPTHMARKETDATA 11
#define ONRTNFORQUOTERSP 12

class PyLock
{
private:
	PyGILState_STATE gil_state;

public:

	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}


	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};


struct Task
{
	int task_name;		
	any task_data;		
	any task_error;		
	int task_id;		
	bool task_last;		
};

template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								
	mutable mutex the_mutex;							
	condition_variable the_condition_variable;			

public:

	
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);				
		the_queue.push(data);							
		lock.unlock();									
		the_condition_variable.notify_one();			
	}
		
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						
		{
			the_condition_variable.wait(lock);			
		}

		Data popped_value = the_queue.front();			
		the_queue.pop();								
		return popped_value;							
	}

};


void getInt(dict d, string key, int* value);


void getDouble(dict d, string key, double* value);


void getChar(dict d, string key, char* value);


void getStr(dict d, string key, char* value);


class MdApi : public CThostFtdcMdSpi
{
private:
	CThostFtdcMdApi* api;				
	thread *task_thread;				
	ConcurrentQueue<Task> task_queue;	

public:
	MdApi()
	{
		function0<void> f = boost::bind(&MdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~MdApi()
	{
	};

	virtual void OnFrontConnected();

	virtual void OnFrontDisconnected(int nReason);

	
	virtual void OnHeartBeatWarning(int nTimeLapse);

	
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	//-------------------------------------------------------------------------------------
	//task
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processHeartBeatWarning(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspError(Task task);

	void processRspSubMarketData(Task task);

	void processRspUnSubMarketData(Task task);

	void processRspSubForQuoteRsp(Task task);

	void processRspUnSubForQuoteRsp(Task task);

	void processRtnDepthMarketData(Task task);

	void processRtnForQuoteRsp(Task task);

	

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int i){};

	virtual void onHeartBeatWarning(int i){};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

	virtual void onRspError(dict error, int id, bool last) {};

	virtual void onRspSubMarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspUnSubMarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspSubForQuoteRsp(dict data, dict error, int id, bool last) {};

	virtual void onRspUnSubForQuoteRsp(dict data, dict error, int id, bool last) {};

	virtual void onRtnDepthMarketData(dict data) {};

	virtual void onRtnForQuoteRsp(dict data) {};

	//-------------------------------------------------------------------------------------
	//req:���������������ֵ�
	//-------------------------------------------------------------------------------------

	void createFtdcMdApi(string pszFlowPath = "");

	void release();

	void init();

	int join();

	int exit();

	string getTradingDay();

	void registerFront(string pszFrontAddress);

	int subscribeMarketData(string instrumentID);

	int unSubscribeMarketData(string instrumentID);

	int subscribeForQuoteRsp(string instrumentID);

	int unSubscribeForQuoteRsp(string instrumentID);

	int reqUserLogin(dict req, int nRequestID);

	int reqUserLogout(dict req, int nRequestID);
};
