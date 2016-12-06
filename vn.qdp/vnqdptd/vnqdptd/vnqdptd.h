//说明部分
/*
由于CTP API中和资金转账相关的函数太多，
同时也已经有大量的客户端支持这些功能，
因此在这个Python封装中暂时选择只支持交易功能
*/


//系统
#ifdef WIN32
#include "stdafx.h"
#endif
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
#include "QdpFtdcTraderApi.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;

//常量
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONHEARTBEATWARNING 3
#define ONRSPAUTHENTICATE 4
#define ONRSPUSERLOGIN 5
#define ONRSPUSERLOGOUT 6
#define ONRSPUSERPASSWORDUPDATE 7
#define ONRSPTRADINGACCOUNTPASSWORDUPDATE 8
#define ONRSPORDERINSERT 9
#define ONRSPPARKEDORDERINSERT 10
#define ONRSPPARKEDORDERACTION 11
#define ONRSPORDERACTION 12
#define ONRSPQUERYMAXORDERVOLUME 13
#define ONRSPSETTLEMENTINFOCONFIRM 14
#define ONRSPREMOVEPARKEDORDER 15
#define ONRSPREMOVEPARKEDORDERACTION 16
#define ONRSPEXECORDERINSERT 17
#define ONRSPEXECORDERACTION 18
#define ONRSPFORQUOTEINSERT 19
#define ONRSPQUOTEINSERT 20
#define ONRSPQUOTEACTION 21
#define ONRSPLOCKINSERT 22
#define ONRSPCOMBACTIONINSERT 23
#define ONRSPQRYORDER 24
#define ONRSPQRYTRADE 25
#define ONRSPQRYINVESTORPOSITION 26
#define ONRSPQRYTRADINGACCOUNT 27
#define ONRSPQRYINVESTOR 28
#define ONRSPQRYTRADINGCODE 29
#define ONRSPQRYINSTRUMENTMARGINRATE 30
#define ONRSPQRYINSTRUMENTCOMMISSIONRATE 31
#define ONRSPQRYEXCHANGE 32
#define ONRSPQRYPRODUCT 33
#define ONRSPQRYINSTRUMENT 34
#define ONRSPQRYDEPTHMARKETDATA 35
#define ONRSPQRYSETTLEMENTINFO 36
#define ONRSPQRYTRANSFERBANK 37
#define ONRSPQRYINVESTORPOSITIONDETAIL 38
#define ONRSPQRYNOTICE 39
#define ONRSPQRYSETTLEMENTINFOCONFIRM 40
#define ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL 41
#define ONRSPQRYCFMMCTRADINGACCOUNTKEY 42
#define ONRSPQRYEWARRANTOFFSET 43
#define ONRSPQRYINVESTORPRODUCTGROUPMARGIN 44
#define ONRSPQRYEXCHANGEMARGINRATE 45
#define ONRSPQRYEXCHANGEMARGINRATEADJUST 46
#define ONRSPQRYEXCHANGERATE 47
#define ONRSPQRYSECAGENTACIDMAP 48
#define ONRSPQRYPRODUCTEXCHRATE 49
#define ONRSPQRYPRODUCTGROUP 50
#define ONRSPQRYOPTIONINSTRTRADECOST 51
#define ONRSPQRYOPTIONINSTRCOMMRATE 52
#define ONRSPQRYEXECORDER 53
#define ONRSPQRYFORQUOTE 54
#define ONRSPQRYQUOTE 55
#define ONRSPQRYLOCK 56
#define ONRSPQRYLOCKPOSITION 57
#define ONRSPQRYINVESTORLEVEL 58
#define ONRSPQRYEXECFREEZE 59
#define ONRSPQRYCOMBINSTRUMENTGUARD 60
#define ONRSPQRYCOMBACTION 61
#define ONRSPQRYTRANSFERSERIAL 62
#define ONRSPQRYACCOUNTREGISTER 63
#define ONRSPERROR 64
#define ONRTNORDER 65
#define ONRTNTRADE 66
#define ONERRRTNORDERINSERT 67
#define ONERRRTNORDERACTION 68
#define ONRTNINSTRUMENTSTATUS 69
#define ONRTNTRADINGNOTICE 70
#define ONRTNERRORCONDITIONALORDER 71
#define ONRTNEXECORDER 72
#define ONERRRTNEXECORDERINSERT 73
#define ONERRRTNEXECORDERACTION 74
#define ONERRRTNFORQUOTEINSERT 75
#define ONRTNQUOTE 76
#define ONERRRTNQUOTEINSERT 77
#define ONERRRTNQUOTEACTION 78
#define ONRTNFORQUOTERSP 79
#define ONRTNCFMMCTRADINGACCOUNTTOKEN 80
#define ONRTNLOCK 81
#define ONERRRTNLOCKINSERT 82
#define ONRTNCOMBACTION 83
#define ONERRRTNCOMBACTIONINSERT 84
#define ONRSPQRYCONTRACTBANK 85
#define ONRSPQRYPARKEDORDER 86
#define ONRSPQRYPARKEDORDERACTION 87
#define ONRSPQRYTRADINGNOTICE 88
#define ONRSPQRYBROKERTRADINGPARAMS 89
#define ONRSPQRYBROKERTRADINGALGOS 90
#define ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN 91
#define ONRTNFROMBANKTOFUTUREBYBANK 92
#define ONRTNFROMFUTURETOBANKBYBANK 93
#define ONRTNREPEALFROMBANKTOFUTUREBYBANK 94
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 95
#define ONRTNFROMBANKTOFUTUREBYFUTURE 96
#define ONRTNFROMFUTURETOBANKBYFUTURE 97
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL 98
#define ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL 99
#define ONRTNQUERYBANKBALANCEBYFUTURE 100
#define ONERRRTNBANKTOFUTUREBYFUTURE 101
#define ONERRRTNFUTURETOBANKBYFUTURE 102
#define ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL 103
#define ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL 104
#define ONERRRTNQUERYBANKBALANCEBYFUTURE 105
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTURE 106
#define ONRTNREPEALFROMFUTURETOBANKBYFUTURE 107
#define ONRSPFROMBANKTOFUTUREBYFUTURE 108
#define ONRSPFROMFUTURETOBANKBYFUTURE 109
#define ONRSPQUERYBANKACCOUNTMONEYBYFUTURE 110
#define ONRTNOPENACCOUNTBYBANK 111
#define ONRTNCANCELACCOUNTBYBANK 112
#define ONRTNCHANGEACCOUNTBYBANK 113
#define ONRSPQRYUSERINVESTOR 114



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


//从字典中获取某个建值对应的字符，并赋值到请求结构体对象的值上
void getChar(dict d, string key, char* value);


//从字典中获取某个建值对应的字符串，并赋值到请求结构体对象的值上
void getStr(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public CQdpFtdcTraderSpi
{
private:
	CQdpFtdcTraderApi* api;			//API对象
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

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///登录请求响应
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///登出请求响应
	virtual void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单录入请求响应
	virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单操作请求响应
	virtual void OnRspOrderAction(CQdpFtdcOrderActionField *pInputOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	///请求查询报单响应
	virtual void OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询成交响应
	virtual void OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询用户投资账户
	virtual void OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者响应
	virtual void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询交易所响应
	virtual void OnRspQryExchange(CQdpFtdcRspExchangeField *pExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询合约响应
	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询行情响应
	virtual void OnRspQryMarketData(CQdpFtdcMarketDataField *pDepthMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询转帐流水响应
	virtual void OnRspQryTransferSerial(CQdpFtdcTransferSerialField *pTransferSerial, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///错误应答
	virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单通知
	virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder) ;

	///成交通知
	virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade) ;

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo) ;

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo) ;

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus) ;

	///请求查询签约银行响应
	virtual void OnRspQryContractBank(CQdpFtdcContractBankField *pContractBank, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///银行发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByBank(CQdpFtdcRspTransferField *pRspTransfer) ;

	///银行发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByBank(CQdpFtdcRspTransferField *pRspTransfer) ;

	///期货发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByFuture(CQdpFtdcRspTransferField *pRspTransfer) ;

	///期货发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByFuture(CQdpFtdcRspTransferField *pRspTransfer) ;

	///期货发起查询银行余额通知
	virtual void OnRtnQueryBankBalanceByFuture(CQdpFtdcNotifyQueryAccountField *pNotifyQueryAccount) ;

	///期货发起银行资金转期货错误回报
	virtual void OnErrRtnBankToFutureByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo) ;

	///期货发起期货资金转银行错误回报
	virtual void OnErrRtnFutureToBankByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo) ;

	///期货发起查询银行余额错误回报
	virtual void OnErrRtnQueryBankBalanceByFuture(CQdpFtdcReqQueryAccountField *pReqQueryAccount, CQdpFtdcRspInfoField *pRspInfo) ;

	///期货发起银行资金转期货应答
	virtual void OnRspFromBankToFutureByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///期货发起期货资金转银行应答
	virtual void OnRspFromFutureToBankByFuture(CQdpFtdcReqTransferField *pReqTransfer, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///期货发起查询银行余额应答
	virtual void OnRspQueryBankAccountMoneyByFuture(CQdpFtdcReqQueryAccountField *pReqQueryAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;


	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processHeartBeatWarning(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspQryUserInvestor(Task task);

	void processRspQryContractBank(Task task);

	void processRspQryTransferSerial(Task task);

	void processRtnFromBankToFutureByBank(Task task);

	void processRtnFromFutureToBankByBank(Task task);

	void processRspUserPasswordUpdate(Task task);

	void processRspTradingAccountPasswordUpdate(Task task);

	void processRspOrderInsert(Task task);

	void processRspOrderAction(Task task);

	void processRspQryOrder(Task task);

	void processRspQryTrade(Task task);

	void processRspQryInvestorPosition(Task task);

	void processRspQryInvestorAccount(Task task);

	void processRspQryExchange(Task task);

	void processRspQryInstrument(Task task);

	void processRspQryMarketData(Task task);

	void processRspQryExecFreeze(Task task);

	void processRspQryCombAction(Task task);

	void processRspError(Task task);

	void processRtnOrder(Task task);

	void processRtnTrade(Task task);

	void processErrRtnOrderInsert(Task task);

	void processErrRtnOrderAction(Task task);

	void processRtnInstrumentStatus(Task task);

	void processRtnFromBankToFutureByFuture(Task task);

	void processRtnFromFutureToBankByFuture(Task task);

	void processRtnQueryBankBalanceByFuture(Task task);

	void processErrRtnBankToFutureByFuture(Task task);

	void processErrRtnFutureToBankByFuture(Task task);

	void processErrRtnQueryBankBalanceByFuture(Task task);

	void processRspFromBankToFutureByFuture(Task task);

	void processRspFromFutureToBankByFuture(Task task);

	void processRspQueryBankAccountMoneyByFuture(Task task);

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

	virtual void onRspAuthenticate(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

	virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

	virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last) {};

	virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQryUserInvestor(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last){};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorAccount(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestor(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

	virtual void onRspQryMarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspError(dict error, int id, bool last) {};

	virtual void onRtnOrder(dict data) {};

	virtual void onRtnTrade(dict data) {};

	virtual void onErrRtnOrderInsert(dict data, dict error) {};

	virtual void onErrRtnOrderAction(dict data, dict error) {};

	virtual void onRtnInstrumentStatus(dict data) {};

	virtual void onRspQryContractBank(dict data, dict error, int id, bool last) {};

	virtual void onRtnFromBankToFutureByBank(dict data) {};

	virtual void onRtnFromFutureToBankByBank(dict data) {};

	virtual void onRtnFromBankToFutureByFuture(dict data) {};

	virtual void onRtnFromFutureToBankByFuture(dict data) {};

	virtual void onRtnQueryBankBalanceByFuture(dict data) {};

	virtual void onErrRtnBankToFutureByFuture(dict data, dict error) {};

	virtual void onErrRtnFutureToBankByFuture(dict data, dict error) {};

	virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error) {};

	virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last) {};



	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createFtdcTraderApi(string pszFlowPath = "");

	void release();

	void init();

	int join();

	int exit();

	string getTradingDay();

	void registerFront(string pszFrontAddress);

	void subscribePrivateTopic(int nType);

	void subscribePublicTopic(int nType);

	int reqAuthenticate(dict req, int nRequestID);

	int reqUserLogin(dict req, int nRequestID);

	int reqUserLogout(dict req, int nRequestID);

	int reqQryUserInvestor(dict req, int nRequestID);

	int reqUserPasswordUpdate(dict req, int nRequestID);

	int reqTradingAccountPasswordUpdate(dict req, int nRequestID);

	int reqOrderInsert(dict req, int nRequestID);

	int reqParkedOrderInsert(dict req, int nRequestID);

	int reqParkedOrderAction(dict req, int nRequestID);

	int reqOrderAction(dict req, int nRequestID);

	int reqExecOrderInsert(dict req, int nRequestID);

	int reqExecOrderAction(dict req, int nRequestID);

	int reqForQuoteInsert(dict req, int nRequestID);

	int reqQuoteInsert(dict req, int nRequestID);

	int reqQuoteAction(dict req, int nRequestID);

	int reqLockInsert(dict req, int nRequestID);

	int reqCombActionInsert(dict req, int nRequestID);

	int reqQryOrder(dict req, int nRequestID);

	int reqQryTrade(dict req, int nRequestID);

	int reqQryInvestorPosition(dict req, int nRequestID);

	int reqQryInvestorAccount(dict req, int nRequestID);

	int reqQryTradingCode(dict req, int nRequestID);

	int reqQryInstrumentMarginRate(dict req, int nRequestID);

	int reqQryInstrumentCommissionRate(dict req, int nRequestID);

	int reqQryExchange(dict req, int nRequestID);

	int reqQryProduct(dict req, int nRequestID);

	int reqQryInstrument(dict req, int nRequestID);

	int reqQryMarketData(dict req, int nRequestID);

	int reqQryInvestorLevel(dict req, int nRequestID);

	int reqQryExecFreeze(dict req, int nRequestID);

	int reqQryCombInstrumentGuard(dict req, int nRequestID);

	int reqQryCombAction(dict req, int nRequestID);

	int reqQryContractBank(dict req, int nRequestID);

	int reqFromBankToFutureByFuture(dict req, int nRequestID);

	int reqFromFutureToBankByFuture(dict req, int nRequestID);

	int reqQueryBankAccountMoneyByFuture(dict req, int nRequestID);
};

