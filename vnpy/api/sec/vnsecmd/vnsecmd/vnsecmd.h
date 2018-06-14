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

//API
#include "DFITCSECMdApi.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;

//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONRTNNOTICE 2
#define ONRSPERROR 3
#define ONRSPSTOCKUSERLOGIN 4
#define ONRSPSTOCKUSERLOGOUT 5
#define ONRSPSOPUSERLOGIN 6
#define ONRSPSOPUSERLOGOUT 7
#define ONRSPFASLUSERLOGIN 8
#define ONRSPFASLUSERLOGOUT 9
#define ONRSPSTOCKSUBMARKETDATA 10
#define ONRSPSTOCKUNSUBMARKETDATA 11
#define ONRSPSOPSUBMARKETDATA 12
#define ONRSPSOPUNSUBMARKETDATA 13
#define ONSTOCKMARKETDATA 14
#define ONSOPMARKETDATA 15
#define ONRSPSTOCKAVAILABLEQUOT 16
#define ONRSPSOPAVAILABLEQUOT 17
#define ONRSPUSERMDPASSWORDUPDATE 18


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
	int task_id;		//整数
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

//从字典中获取某个建值对应的整数，并赋值到请求结构体对象的值上
void getLong(dict d, string key, int* value);

//从字典中获取某个建值对应的浮点数，并赋值到请求结构体对象的值上
void getDouble(dict d, string key, double* value);

//从字典中获取某个建值对应的字符串，并赋值到请求结构体对象的值上
void getString(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public DFITCSECMdSpi
{
private:
	DFITCSECMdApi *api;					//API对象
	thread *task_thread;				//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task*> task_queue;	//任务队列

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
	* SEC-消息通知
	*/
	virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice);

	/**
	* ERR-错误应答
	* @param pRspInfo:若请求失败，返回错误信息地址
	*/
	virtual void OnRspError(struct DFITCSECRspInfoField *pRspInfo);

	/**
	* STOCK-登录响应
	* @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
	* @param pRspInfo::指针若非空，返回错误信息地址，表明登录请求失败
	*/
	virtual void OnRspStockUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-登出响应
	* @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
	*/
	virtual void OnRspStockUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-登录响应
	* @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
	*/
	virtual void OnRspSOPUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-登出响应
	* @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
	*/
	virtual void OnRspSOPUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* FASL-登录响应
	* @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
	*/
	virtual void OnRspFASLUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* FASL-登出响应
	* @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
	*/
	virtual void OnRspFASLUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-行情订阅响应
	* @param pSpecificInstrument:指针若非空,返回用户指定合约行情订阅响应结构地址,表明指定合约行情订阅成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情订阅失败
	*/
	virtual void OnRspStockSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-取消订阅行情响应
	* @param pSpecificInstrument:指针若非空,返回用户指定合约行情取消订阅响应结构地址,表明指定合约行情取消订阅成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	*/
	virtual void OnRspStockUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-行情订阅响应
	* @param pSpecificInstrument:指针若非空,返回用户指定合约行情订阅响应结构地址,表明指定合约行情订阅成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情订阅失败
	*/
	virtual void OnRspSOPSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-取消订阅行情响应
	* @param pSpecificInstrument:指针若非空,返回用户指定合约行情取消订阅响应结构地址,表明指定合约行情取消订阅成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	*/
	virtual void OnRspSOPUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-行情推送响应
	* @param pMarketDataField:指针若非空,返回行情推送响应结构地址
	*/
	virtual void OnStockMarketData(struct DFITCStockDepthMarketDataField * pMarketDataField);

	/**
	* SOP-行情推送响应
	* @param pMarketDataField:指针若非空,返回行情推送响应结构地址
	*/
	virtual void OnSOPMarketData(struct DFITCSOPDepthMarketDataField * pMarketDataField);

	/**
	* STOCK-可用行情响应
	* @param pAvailableQuotInfo:指针若非空,返回可用的行情信息
	* @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	* @param flag  为真是标示最后一条，为假时表示还有后续。
	*/
	virtual void OnRspStockAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag);

	/**
	* SOP-可用行情响应
	* @param pAvailableQuotInfo:指针若非空,返回可用的行情信息
	* @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	* @param flag  为真是标示最后一条，为假时表示还有后续。
	*/
	virtual void OnRspSopAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag);

	/**
	* 密码更新请求响应
	* @param pMDPasswordUpdate:指针若非空,返回用户行情密码响应信息结构地址,表明密码修改成功。
	* @param pRspInfo:指针若非空，返回错误信息地址，表明密码修改失败。
	*/
	virtual void OnRspUserMDPasswordUpdate(struct DFITCSECRspMDPasswordUpdateField *pMDPasswordUpdate, struct DFITCSECRspInfoField * pRspInfo);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processRtnNotice(Task *task);

	void processRspError(Task *task);

	void processRspStockUserLogin(Task *task);

	void processRspStockUserLogout(Task *task);

	void processRspSOPUserLogin(Task *task);

	void processRspSOPUserLogout(Task *task);

	void processRspFASLUserLogin(Task *task);

	void processRspFASLUserLogout(Task *task);

	void processRspStockSubMarketData(Task *task);

	void processRspStockUnSubMarketData(Task *task);

	void processRspSOPSubMarketData(Task *task);

	void processRspSOPUnSubMarketData(Task *task);

	void processStockMarketData(Task *task);

	void processSOPMarketData(Task *task);

	void processRspStockAvailableQuot(Task *task);

	void processRspSopAvailableQuot(Task *task);

	void processRspUserMDPasswordUpdate(Task *task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//flag：是否为最后返回
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int reason){};

	virtual void onRtnNotice(dict data){};

	virtual void onRspError(dict error){};

	virtual void onRspStockUserLogin(dict data, dict error){};

	virtual void onRspStockUserLogout(dict data, dict error){};

	virtual void onRspSOPUserLogin(dict data, dict error){};

	virtual void onRspSOPUserLogout(dict data, dict error){};

	virtual void onRspFASLUserLogin(dict data, dict error){};

	virtual void onRspFASLUserLogout(dict data, dict error){};

	virtual void onRspStockSubMarketData(dict data, dict error){};

	virtual void onRspStockUnSubMarketData(dict data, dict error){};

	virtual void onRspSOPSubMarketData(dict data, dict error){};

	virtual void onRspSOPUnSubMarketData(dict data, dict error){};

	virtual void onStockMarketData(dict data){};

	virtual void onSOPMarketData(dict data){};

	virtual void onRspStockAvailableQuot(dict data, dict error, bool flag){};

	virtual void onRspSopAvailableQuot(dict data, dict error, bool flag){};

	virtual void onRspUserMDPasswordUpdate(dict data, dict error){};


	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createDFITCMdApi(string logAddr);

	void init(string svrAddr);

	void release();

	int exit();

	int subscribeStockMarketData(string instrumentID, int nRequestID);

	int unSubscribeStockMarketData(string instrumentID, int nRequestID);

	int subscribeSOPMarketData(string instrumentID, int nRequestID);

	int unSubscribeSOPMarketData(string instrumentID, int nRequestID);

	int reqStockUserLogin(dict req);

	int reqStockUserLogout(dict req);

	int reqSOPUserLogin(dict req);

	int reqFASLUserLogin(dict req);

	int reqSOPUserLogout(dict req);

	int reqFASLUserLogout(dict req);

	int reqStockAvailableQuotQry(dict req);

	int reqSopAvailableQuotQry(dict req);

	int reqUserMDPasswordUpdate(dict req);
};
