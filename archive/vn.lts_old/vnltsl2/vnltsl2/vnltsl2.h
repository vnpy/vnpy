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
#include "SecurityFtdcL2MDUserApi.h"
_USING_LTS_NS_

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;

//常量
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONHEARTBEATWARNING 3
#define ONRSPERROR 4
#define ONRSPUSERLOGIN 5
#define ONRSPUSERLOGOUT 6
#define ONRSPSUBL2MARKETDATA 7
#define ONRSPUNSUBL2MARKETDATA 8
#define ONRSPSUBL2INDEX 9
#define ONRSPUNSUBL2INDEX 10
#define ONRTNL2MARKETDATA 11
#define ONRTNL2INDEX 12
#define ONRSPSUBL2ORDERANDTRADE 13
#define ONRSPUNSUBL2ORDERANDTRADE 14
#define ONRTNL2ORDER 15
#define ONRTNL2TRADE 16
#define ONNTFCHECKORDERLIST 17



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
class L2MdApi : public CSecurityFtdcL2MDUserSpi
{
private:
	CSecurityFtdcL2MDUserApi* api;		//API对象
	thread *task_thread;				//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task> task_queue;	//任务队列

public:
	L2MdApi()
	{
		function0<void> f = boost::bind(&L2MdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~L2MdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///心跳超时警告
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///错误应答
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///登录请求响应
	virtual void OnRspUserLogin(CSecurityFtdcUserLoginField *pUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///登出请求响应
	virtual void OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///订阅Level2行情应答
	virtual void OnRspSubL2MarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///取消订阅Level2行情应答
	virtual void OnRspUnSubL2MarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///订阅Level2指数行情应答
	virtual void OnRspSubL2Index(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///取消订阅Level2指数行情应答
	virtual void OnRspUnSubL2Index(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///Level2行情通知
	virtual void OnRtnL2MarketData(CSecurityFtdcL2MarketDataField *pL2MarketData) ;

	///Level2指数行情通知
	virtual void OnRtnL2Index(CSecurityFtdcL2IndexField *pL2Index) ;

	///订阅逐笔委托及成交应答
	virtual void OnRspSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///取消订阅逐笔委托及成交应答
	virtual void OnRspUnSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///Level2委托通知
	virtual void OnRtnL2Order(CSecurityFtdcL2OrderField *pL2Order) ;

	///Level2成交通知
	virtual void OnRtnL2Trade(CSecurityFtdcL2TradeField *pL2Trade) ;

	///通知清理SSE买卖一队列中数量为0的报单
	virtual void OnNtfCheckOrderList(TSecurityFtdcInstrumentIDType InstrumentID, TSecurityFtdcFunctionCodeType FunctionCode) ;


	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processHeartBeatWarning(Task task);

	void processRspError(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspSubL2MarketData(Task task);

	void processRspUnSubL2MarketData(Task task);

	void processRspSubL2Index(Task task);

	void processRspUnSubL2Index(Task task);

	void processRtnL2MarketData(Task task);

	void processRtnL2Index(Task task);

	void processRspSubL2OrderAndTrade(Task task);

	void processRspUnSubL2OrderAndTrade(Task task);

	void processRtnL2Order(Task task);

	void processRtnL2Trade(Task task);

	void processNtfCheckOrderList(Task task);


	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int i){};

	virtual void onHeartBeatWarning(int i){};

	virtual void onRspError(dict error, int id, bool last) {};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

	virtual void onRspSubL2MarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspUnSubL2MarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspSubL2Index(dict data, dict error, int id, bool last) {};

	virtual void onRspUnSubL2Index(dict data, dict error, int id, bool last) {};

	virtual void onRtnL2MarketData(dict data) {};

	virtual void onRtnL2Index(dict data) {};

	virtual void onRspSubL2OrderAndTrade(dict error, int id, bool last) {};

	virtual void onRspUnSubL2OrderAndTrade(dict error, int id, bool last) {};

	virtual void onRtnL2Order(dict data) {};

	virtual void onRtnL2Trade(dict data) {};

	virtual void onNtfCheckOrderList(string instrumentID, string functionCode) {};


	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createFtdcL2MDUserApi(string pszFlowPath = "");

	void release();

	void init();

	int join();

	int exit();

	string getTradingDay();

	void registerFront(string pszFrontAddress);

	int subscribeL2MarketData(dict req);

	int unSubscribeL2MarketData(dict req);

	int subscribeL2Index(dict req);

	int unSubscribeL2Index(dict req);

	int subscribeL2OrderAndTrade();

	int unSubscribeL2OrderAndTrade();

	int reqUserLogin(dict req, int nRequestID);

	int reqUserLogout(dict req, int nRequestID);
};

