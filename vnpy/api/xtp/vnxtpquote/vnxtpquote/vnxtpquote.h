//说明部分

//API
#include "xtp_quote_api.h"

//系统
#ifdef WIN32
	#include "stdafx.h"
#endif
#include <string>
#include <queue>
#include <vector>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python封装
#include <boost/python/def.hpp>		//python封装
#include <boost/python/dict.hpp>	//python封装
#include <boost/python/list.hpp>	//python封装
#include <boost/python/object.hpp>	//python封装
#include <boost/python.hpp>			//python封装
#include <boost/thread.hpp>			//任务队列的线程功能
#include <boost/bind.hpp>			//任务队列的线程功能


//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;


//常量
#define ONDISCONNECTED 1
#define ONERROR 2
#define ONSUBMARKETDATA 3
#define ONUNSUBMARKETDATA 4
#define ONDEPTHMARKETDATA 5
#define ONSUBORDERBOOK 6
#define ONUNSUBORDERBOOK 7
#define ONORDERBOOK 8
#define ONSUBTICKBYTICK 9
#define ONUNSUBTICKBYTICK 10
#define ONTICKBYTICK 11
#define ONSUBSCRIBEALLMARKETDATA 12
#define ONUNSUBSCRIBEALLMARKETDATA 13
#define ONSUBSCRIBEALLORDERBOOK 14
#define ONUNSUBSCRIBEALLORDERBOOK 15
#define ONSUBSCRIBEALLTICKBYTICK 16
#define ONUNSUBSCRIBEALLTICKBYTICK 17
#define ONQUERYALLTICKERS 18
#define ONQUERYTICKERSPRICEINFO 19


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
	void *task_data;	//数据结构体
	void *task_error;	//错误结构体
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

//从字典中获取某个建值对应的字符，并赋值到请求结构体对象的值上
void getChar(dict d, string key, char* value);

//从字典中获取某个建值对应的字符串，并赋值到请求结构体对象的值上
void getStr(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class QuoteApi : public XTP::API::QuoteSpi
{
private:
	XTP::API::QuoteApi* api;			//API对象
	thread *task_thread;				//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task*> task_queue;	//任务队列

public:
	QuoteApi()
	{
		function0<void> f = boost::bind(&QuoteApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~QuoteApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

	///当客户端与行情后台通信连接断开时，该方法被调用。
	///@param reason 错误原因，请与错误代码表对应
	///@remark api不会自动重连，当断线发生时，请用户自行选择后续操作。可以在此函数中调用Login重新登录。注意用户重新登录后，需要重新订阅行情
	virtual void OnDisconnected(int reason);


	///错误应答
	///@param error_info 当服务器响应发生错误时的具体的错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@remark 此函数只有在服务器发生错误时才会调用，一般无需用户处理
	virtual void OnError(XTPRI *error_info);

	///订阅行情应答
	///@param ticker 详细的合约订阅情况
	///@param error_info 订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@remark 每条订阅的合约均对应一条订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last);

	///退订行情应答
	///@param ticker 详细的合约取消订阅情况
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@remark 每条取消订阅的合约均对应一条取消订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last);

	///深度行情通知，包含买一卖一队列
	///@param market_data 行情数据
	///@param bid1_qty 买一队列数据
	///@param bid1_count 买一队列的有效委托笔数
	///@param max_bid1_count 买一队列总委托笔数
	///@param ask1_qty 卖一队列数据
	///@param ask1_count 卖一队列的有效委托笔数
	///@param max_ask1_count 卖一队列总委托笔数
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count);

	///订阅行情订单簿应答
	///@param ticker 详细的合约订阅情况
	///@param error_info 订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@remark 每条订阅的合约均对应一条订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last);

	///退订行情订单簿应答
	///@param ticker 详细的合约取消订阅情况
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@remark 每条取消订阅的合约均对应一条取消订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last);

	///行情订单簿通知
	///@param order_book 行情订单簿数据，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnOrderBook(XTPOB *order_book);

	///订阅逐笔行情应答
	///@param ticker 详细的合约订阅情况
	///@param error_info 订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@remark 每条订阅的合约均对应一条订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last);

	///退订逐笔行情应答
	///@param ticker 详细的合约取消订阅情况
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@remark 每条取消订阅的合约均对应一条取消订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last);

	///逐笔行情通知
	///@param tbt_data 逐笔行情数据，包括逐笔委托和逐笔成交，此为共用结构体，需要根据type来区分是逐笔委托还是逐笔成交，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnTickByTick(XTPTBT *tbt_data);

	///订阅全市场的行情应答
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@remark 需要快速返回
	virtual void OnSubscribeAllMarketData(XTPRI *error_info);

	///退订全市场的行情应答
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@remark 需要快速返回
	virtual void OnUnSubscribeAllMarketData(XTPRI *error_info);

	///订阅全市场的行情订单簿应答
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@remark 需要快速返回
	virtual void OnSubscribeAllOrderBook(XTPRI *error_info);

	///退订全市场的行情订单簿应答
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@remark 需要快速返回
	virtual void OnUnSubscribeAllOrderBook(XTPRI *error_info);

	///订阅全市场的逐笔行情应答
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@remark 需要快速返回
	virtual void OnSubscribeAllTickByTick(XTPRI *error_info);

	///退订全市场的逐笔行情应答
	///@param error_info 取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@remark 需要快速返回
	virtual void OnUnSubscribeAllTickByTick(XTPRI *error_info);


	///查询可交易合约的应答
	///@param ticker_info 可交易合约信息
	///@param error_info 查询可交易合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次查询可交易合约的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	virtual void OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last);

	///查询合约的最新价格信息应答
	///@param ticker_info 合约的最新价格信息
	///@param error_info 查询合约的最新价格信息时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param is_last 是否此次查询的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	virtual void OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processDisconnected(Task *task);

	void processError(Task *task);

	void processSubMarketData(Task *task);

	void processUnSubMarketData(Task *task);

	void processDepthMarketData(Task *task);

	void processSubOrderBook(Task *task);

	void processUnSubOrderBook(Task *task);

	void processOrderBook(Task *task);

	void processSubTickByTick(Task *task);

	void processUnSubTickByTick(Task *task);

	void processTickByTick(Task *task);

	void processSubscribeAllMarketData(Task *task);

	void processUnSubscribeAllMarketData(Task *task);

	void processSubscribeAllOrderBook(Task *task);

	void processUnSubscribeAllOrderBook(Task *task);

	void processSubscribeAllTickByTick(Task *task);

	void processUnSubscribeAllTickByTick(Task *task);

	void processQueryAllTickers(Task *task);

	void processQueryTickersPriceInfo(Task *task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onDisconnected(int reason) {};

	virtual void onError(dict data) {};

	virtual void onSubMarketData(dict data, dict error, bool last) {};

	virtual void onUnSubMarketData(dict data, dict error, bool last) {};

	virtual void onDepthMarketData(dict data) {};

	virtual void onSubOrderBook(dict data, dict error, bool last) {};

	virtual void onUnSubOrderBook(dict data, dict error, bool last) {};

	virtual void onOrderBook(dict data) {};

	virtual void onSubTickByTick(dict data, dict error, bool last) {};

	virtual void onUnSubTickByTick(dict data, dict error, bool last) {};

	virtual void onTickByTick(dict data) {};

	virtual void onSubscribeAllMarketData(dict error) {};

	virtual void onUnSubscribeAllMarketData(dict error) {};

	virtual void onSubscribeAllOrderBook(dict error) {};

	virtual void onUnSubscribeAllOrderBook(dict error) {};

	virtual void onSubscribeAllTickByTick(dict error) {};

	virtual void onUnSubscribeAllTickByTick(dict error) {};

	virtual void onQueryAllTickers(dict data, dict error, bool last) {};

	virtual void onQueryTickersPriceInfo(dict data, dict error, bool last) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createQuoteApi(int clientid, string path);

	void release();

	int exit();

	string getTradingDay();

	string getApiVersion();

	dict getApiLastError();

	void setUDPBufferSize(int size);

	void setHeartBeatInterval(int interval);

	int subscribeMarketData(string ticker, int exchange);

	int unSubscribeMarketData(string ticker, int exchange);

	int subscribeOrderBook(string ticker, int exchange);

	int unSubscribeOrderBook(string ticker, int exchange);

	int subscribeTickByTick(string ticker, int exchange);

	int unSubscribeTickByTick(string ticker, int exchange);

	void subscribeAllMarketData();

	void unSubscribeAllMarketData();

	void subscribeAllOrderBook();

	void unSubscribeAllOrderBook();

	void subscribeAllTickByTick();

	void unSubscribeAllTickByTick();

	int login(string ip, int port, string user, string password, int socktype);

	int logout();

	int queryAllTickers(int exchange);

	int queryTickersPriceInfo(string ticker, int exchange);

	int queryAllTickersPriceInfo();
};
