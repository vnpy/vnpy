//说明部分
/*
由于CTP API中和资金转账相关的函数太多，
同时也已经有大量的客户端支持这些功能，
因此在这个Python封装中暂时选择只支持交易功能
*/


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
#include "GoldTradeApi.h"
#include "Constant.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;

//常量
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERLOGOUT 4
#define ONNTYMKTSTATUS 5
#define ONRSPQRYINSTRUMENT 6
#define ONRTNDEPTHMARKETDATA 7
#define ONRSPORDERINSERT 8
#define ONERRRTNORDERINSERT 9
#define ONRTNORDER 10
#define ONFORCELOGOUT 11
#define ONRSPORDERACTION 12
#define ONERRRTNORDERACTION 13
#define ONRTNTRADE 14
#define ONRSPQRYTRADINGACCOUNT 15
#define ONRSPQRYORDER 16
#define ONRSPQRYTRADE 17
#define ONRSPQRYINVESTORPOSITION 18
#define ONRSPQRYCLIENTSTORAGE 19
#define ONRSPSUBMARKETDATA 20


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


//从字典中获取某个建值对应的字符串，并赋值到请求结构体对象的值上
void getChar(dict d, string key, char* value);



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public CGoldTradeSpi
{
private:
	CGoldTradeApi* api;			//API对象
	thread *task_thread;				//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task> task_queue;	//任务队列

public:
	TdApi()
	{
		function0<void> f = boost::bind(&TdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~TdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

	//连接建立通知
	virtual void OnFrontConnected();

	//连接断开
	virtual void OnFrontDisconnected(int nReason);

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//市场状态通知
	virtual void OnNtyMktStatus(const CThostFtdcMarketStatusField *pfldMktStatus);

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	///报单录入请求响应(二级系统检查错误）
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入错误回报(交易所）
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

	///报单通知
	//virtual void OnRtnOrder(CThostFtdcOrderField *pOrder); //错误
	virtual void OnRtnOrder(CThostFtdcOrderRtnField *pOrder);

	//强退通知
	virtual void OnForceLogout(CThostFtdcUserLogoutField *pLogout);

	//撤单应答
	///报单操作请求响应(二级系统返回包含了错误编码和错误消息)
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单操作错误回报(交易所返回)
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//查询客户库存应答
	virtual void OnRspQryClientStorage(CThostFtdcStorageField *pStorage, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processNtyMktStatus(Task task);

	void processRspQryInstrument(Task task);

	void processRtnDepthMarketData(Task task);

	void processRspOrderInsert(Task task);

	void processErrRtnOrderInsert(Task task);

	void processRtnOrder(Task task);

	void processForceLogout(Task task);

	void processRspOrderAction(Task task);

	void processErrRtnOrderAction(Task task);

	void processRtnTrade(Task task);

	void processRspQryTradingAccount(Task task);

	void processRspQryOrder(Task task);

	void processRspQryTrade(Task task);

	void processRspQryInvestorPosition(Task task);

	void processRspQryClientStorage(Task task);

	void processRspSubMarketData(Task task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int i){};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

	virtual void onNtyMktStatus(dict data) {};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

	virtual void onRtnDepthMarketData(dict data) {};

	virtual void onForceLogout(dict data) {};

	virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onErrRtnOrderInsert(dict data, dict error) {};

	virtual void onRtnOrder(dict data) {};

	virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onErrRtnOrderAction(dict data, dict error) {};

	virtual void onRtnTrade(dict data) {};

	virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryClientStorage(dict data, dict error, int id, bool last) {};

	virtual void onRspSubMarketData(dict data, dict error, int id, bool last) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createGoldTraderApi();

	void release();

	int init(bool flag);

	void join();

	int exit();

	void registerFront(string pszFrontAddress);

	int reqUserLogin(dict req, int nRequestID);

	int reqUserLogout(dict req, int nRequestID);

	int reqUserReLogin();

	int subscribeMarketData(string instrumentID);

	int unSubscribeMarketData(string instrumentID);

	int reqQryInstrument(dict req, int nRequestID);

	int reqOrderInsert(dict req, int nRequestID);

	int reqOrderAction(dict req, int nRequestID);

	int reqQryInvestorPosition(dict req, int nRequestID);

	int reqQryTradingAccount(dict req, int nRequestID);

	int reqQryTrade(dict req, int nRequestID);

	int reqQryOrder(dict req, int nRequestID);

	int reqQryStorage(dict req, int nRequestID);
};

