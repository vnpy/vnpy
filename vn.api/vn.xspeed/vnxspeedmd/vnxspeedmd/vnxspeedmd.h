//说明部分

//系统
#include "stdafx.h"
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python封装
#include <boost/python/def.hpp>		//python封装
#include <boost/python/dict.hpp>	//python封装
#include <boost/python/object.hpp>	//python封装
#include <boost/python.hpp>			//python封装
#include <boost/thread.hpp>			//任务队列的线程功能
#include <boost/bind.hpp>			//任务队列的线程功能
#include <boost/any.hpp>			//任务队列的任务实现

//API
#include "DFITCMdApi.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;
using namespace DFITCXSPEEDMDAPI;

//常量
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERLOGOUT 4
#define ONRSPERROR 5
#define ONRSPSUBMARKETDATA 6
#define ONRSPUNSUBMARKETDATA 7
#define ONRSPSUBFORQUOTERSP 8
#define ONRSPUNSUBFORQUOTERSP 9
#define ONMARKETDATA 10
#define ONCUSTOMMARKETDATA 11
#define ONRTNFORQUOTERSP 12
#define ONRSPTRADINGDAY 13
#define EXIT 0


///-------------------------------------------------------------------------------------
///API中的部分组件
///-------------------------------------------------------------------------------------

//GIL全局锁简化获取用，
//用于帮助C++线程获得GIL锁，从而防止python崩溃
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//在某个函数方法中创建该对象时，获得GIL锁
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//在某个函数完成后销毁该对象时，解放GIL锁
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};


//任务结构体
struct Task
{
	int task_name;		//回调函数名称对应的常量
	any task_data;		//数据结构体
	any task_error;		//错误结构体
	int task_id;		//请求id
	bool task_last;		//是否为最后返回
};


///线程安全的队列
template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								//标准库队列
	mutable mutex the_mutex;							//boost互斥锁
	condition_variable the_condition_variable;			//boost条件变量

public:

	//存入新的任务
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);				//获取互斥锁
		the_queue.push(data);							//向队列中存入数据
		lock.unlock();									//释放锁
		the_condition_variable.notify_one();			//通知正在阻塞等待的线程
	}

	//检查队列是否为空
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	//取出
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						//当队列为空时
		{
			the_condition_variable.wait(lock);			//等待条件变量通知
		}

		Data popped_value = the_queue.front();			//获取队列中的最后一个任务
		the_queue.pop();								//删除该任务
		return popped_value;							//返回该任务
	}

};


//从字典中获取某个建值对应的整数，并赋值到请求结构体对象的值上
void getInt(dict d, string key, int* value);


//从字典中获取某个建值对应的浮点数，并赋值到请求结构体对象的值上
void getDouble(dict d, string key, double* value);


//从字典中获取某个建值对应的单字符，并赋值到请求结构体对象的值上
void getChar(dict d, string key, char* value);


//从字典中获取某个建值对应的字符串，并赋值到请求结构体对象的值上
void getString(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public DFITCMdSpi
{
private:
	DFITCMdApi* api;			//API对象
	thread *task_thread;				//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task> task_queue;	//任务队列

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

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

		/**
		* 网络连接正常响应
		*/
		virtual void OnFrontConnected();

		/**
		* 网络连接不正常响应
		*/
		virtual void OnFrontDisconnected(int nReason);

		/**
		* 登陆请求响应:当用户发出登录请求后，前置机返回响应时此方法会被调用，通知用户登录是否成功。
		* @param pRspUserLogin:用户登录信息结构地址。
		* @param pRspInfo:若请求失败，返回错误信息地址，该结构含有错误信息。
		*/
		virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pRspUserLogin, struct DFITCErrorRtnField * pRspInfo);

		/**
		* 登出请求响应:当用户发出退出请求后，前置机返回响应此方法会被调用，通知用户退出状态。
		* @param pRspUsrLogout:返回用户退出信息结构地址。
		* @param pRspInfo:若请求失败，返回错误信息地址。
		*/
		virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pRspUsrLogout, struct DFITCErrorRtnField * pRspInfo);

		/**
		* 错误应答
		* @param pRspInfo:错误信息地址。
		*/
		virtual void OnRspError(struct DFITCErrorRtnField *pRspInfo);

		/**
		* 行情订阅应答:当用户发出行情订阅该方法会被调用。
		* @param pSpecificInstrument:指向合约响应结构，该结构包含合约的相关信息。
		* @param pRspInfo:错误信息，如果发生错误，该结构含有错误信息。
		*/
		virtual void OnRspSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* 取消订阅行情应答:当用户发出退订请求后该方法会被调用。
		* @param pSpecificInstrument:指向合约响应结构，该结构包含合约的相关信息。
		* @param pRspInfo:错误信息，如果发生错误，该结构含有错误信息。
		*/
		virtual void OnRspUnSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* 订阅询价应答
		* @param pSpecificInstrument:指向合约响应结构，该结构包含合约的相关信息。
		* @param pRspInfo:错误信息，如果发生错误，该结构含有错误信息。
		*/
		virtual void OnRspSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* 取消订阅询价应答
		* @param pSpecificInstrument:指向合约响应结构，该结构包含合约的相关信息。
		* @param pRspInfo:错误信息，如果发生错误，该结构含有错误信息。
		*/
		virtual void OnRspUnSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* 行情消息应答:如果订阅行情成功且有行情返回时，该方法会被调用。
		* @param pMarketDataField:指向行情信息结构的指针，结构体中包含具体的行情信息。
		*/
		virtual void OnMarketData(struct DFITCDepthMarketDataField * pMarketDataField);

		/**
		* 自定义组合行情消息应答:如果订阅行情成功且有行情返回时，该方法会被调用。
		* @param pMarketDataField:指向行情信息结构的指针，结构体中包含具体的行情信息。
		*/
		virtual void OnCustomMarketData(struct DFITCCustomMarketDataField * pMarketDataField);

		/**
		* 询价通知
		* @param pForQuoteField:指向询价信息结构的指针，结构体中包含具体的询价信息。
		*/
		virtual void OnRtnForQuoteRsp(struct DFITCQuoteSubscribeRtnField * pForQuoteField);

		/**
		* 交易日确认响应:用于接收交易日信息。
		* @param pTradingDayRtnData: 返回交易日请求确认响应结构的地址。
		*/
		virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData);


	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspError(Task task);

	void processRspSubMarketData(Task task);

	void processRspUnSubMarketData(Task task);

	void processRspSubForQuoteRsp(Task task);

	void processRspUnSubForQuoteRsp(Task task);

	void processMarketData(Task task);

	void processCustomMarketData(Task task);

	void processRtnForQuoteRsp(Task task);

	void processRspTradingDay(Task task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int i){};

	virtual void onRspUserLogin(dict data, dict error) {};

	virtual void onRspUserLogout(dict data, dict error) {};

	virtual void onRspError(dict error) {};

	virtual void onRspSubMarketData(dict data, dict error) {};

	virtual void onRspUnSubMarketData(dict data, dict error) {};

	virtual void onRspSubForQuoteRsp(dict data, dict error) {};

	virtual void onRspUnSubForQuoteRsp(dict data, dict error) {};

	virtual void onMarketData(dict data) {};

	virtual void onCustomMarketData(dict data) {};

	virtual void onRtnForQuoteRsp(dict data) {};

	virtual void onRspTradingDay(dict data) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createDFITCMdApi();

	void release();

	void init(string pszSvrAddr);

	int exit();
	
	int subscribeMarketData(string instrumentID, int nRequestID);

	int unSubscribeMarketData(string instrumentID, int nRequestID);

	int subscribeForQuoteRsp(string instrumentID, int nRequestID);

	int unSubscribeForQuoteRsp(string instrumentID, int nRequestID);

	int reqUserLogin(dict req);

	int reqUserLogout(dict req);

	int reqTradingDay(dict req);
};
