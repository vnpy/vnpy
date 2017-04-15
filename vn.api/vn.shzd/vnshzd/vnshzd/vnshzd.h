//说明部分

//系统
#ifdef WIN32
#include "stdafx.h"
#endif
#include <string>
#include <queue>
#include <vector>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>		//python封装
#include <boost/python/def.hpp>			//python封装
#include <boost/python/dict.hpp>		//python封装
#include <boost/python/list.hpp>		//python封装
#include <boost/python/object.hpp>		//python封装
#include <boost/python.hpp>				//python封装
#include <boost/thread.hpp>				//任务队列的线程功能
#include <boost/bind.hpp>				//任务队列的线程功能
#include <boost/any.hpp>				//任务队列的任务实现
#include <boost/algorithm/string.hpp>	//字符串处理功能

//API
#include "ShZdTradeLib.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;

//常量
#define ONRECEIVETRADEINFO 1
#define ONRECEIVEMARKETINFO 2
#define ONRECEIVEERRORINFO 3


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
	int task_name;			//回调函数名称对应的常量
	void* task_data;		//数据结构指针
	string task_errmsg;		//错误字符串
	int task_errcode;		//错误代码
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


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class ShzdApi : public IShZdTradeOutLib
{
private:
	IShZdTradeInLib *api;				//API对象
	thread *task_thread;				//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task*> task_queue;	//任务队列

public:
	ShzdApi()
	{
		function0<void> f = boost::bind(&ShzdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~ShzdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

	virtual int OnReceiveTradeInfo(const CShZdMessage * re);

	virtual int OnReceiveMarketInfo(const CShZdMessage * re);
	
	virtual int OnReceiveErrorInfo(int errorCode, const char* re);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processTradeInfo(Task *task);

	void processMarketInfo(Task *task);

	void processErrorInfo(Task *task);


	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onReceiveTradeInfo(dict data){};

	virtual void onReceiveMarketInfo(dict data){};

	virtual void onReceiveErrorInfo(int errcode, string errmsg){};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void release();

	int initShZdServer();

	int registerFront(string address, int port);

	int registerMarket(string address, int port);

	int shzdSendInfoToTrade(dict data);

	int shzdSendInfoToMarket(dict data);

};
