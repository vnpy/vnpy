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
#include "KSOTPTraderApi.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;
using namespace KingstarAPI;

//常量
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERLOGOUT 4
#define ONRSPUSERPASSWORDUPDATE 5
#define ONRSPTRADINGACCOUNTPASSWORDUPDATE 6
#define ONRSPORDERINSERT 7
#define ONRSPORDERACTION 8
#define ONRSPQRYORDER 9
#define ONRSPQRYTRADE 10
#define ONRSPQRYINVESTORPOSITION 11
#define ONRSPQRYTRADINGACCOUNT 12
#define ONRSPQRYINVESTOR 13
#define ONRSPQRYTRADINGCODE 14
#define ONRSPQRYEXCHANGE 15
#define ONRSPQRYINSTRUMENT 16
#define ONRSPQRYINVESTORPOSITIONDETAIL 17
#define ONRSPQRYTRADINGNOTICE 18
#define ONRSPEXECORDERINSERT 19
#define ONRSPLOCKINSERT 20
#define ONRSPEXECORDERACTION 21
#define ONRSPQRYEXECORDER 22
#define ONRSPQRYEXECORDERVOLUME 23
#define ONRSPQRYLOCK 24
#define ONRSPQRYLOCKPOSITION 25
#define ONRSPQRYUNDERLYINGSTOCKINFO 26
#define ONRSPQRYOTPINSCOMMRATE 27
#define ONRSPQRYINSTRUMENTMARGINRATE 28
#define ONRSPQRYOTPASSIGNMENT 29
#define ONRSPQRYDEPTHMARKETDATA 30
#define ONRSPFROMBANKTOSTOCKBYSTOCK 31
#define ONRTNFROMBANKTOSTOCKBYSTOCK 32
#define ONRSPFROMSTOCKTOBANKBYSTOCK 33
#define ONRTNFROMSTOCKTOBANKBYSTOCK 34
#define ONRTNQUERYBANKBALANCEBYSTOCK 35
#define ONRSPQRYCONTRACTBANK 36
#define ONRSPQUERYBANKACCOUNTMONEYBYSTOCK 37
#define ONRSPQRYTRANSFERSERIAL 38
#define ONRSPQRYSETTLEMENTINFOCONFIRM 39
#define ONRSPSETTLEMENTINFOCONFIRM 40
#define ONRSPQRYSETTLEMENTINFO 41
#define ONRSPQRYINVESTORTRADELEVEL 42
#define ONRSPQRYPURCHASELIMITAMT 43
#define ONRSPQRYPOSITIONLIMITVOL 44
#define ONRSPQRYHISTORYORDER 45
#define ONRSPQRYHISTORYTRADE 46
#define ONRSPQRYHISTORYASSIGNMENT 47
#define ONRSPQRYDELIVDETAIL 48
#define ONRSPAUTOEXECORDERACTION 49
#define ONRSPCOMBACTIONINSERT 50
#define ONRSPQRYINVESTORCOMBINEPOSITION 51
#define ONRSPQRYCOMBACTIONVOLUME 52
#define ONRSPFUNDOUTCREDITAPPLY 53
#define ONRSPQRYFUNDOUTCREDIT 54
#define ONRSPQRYFUNDOUTCREDITAPPLY 55
#define ONRSPERROR 56
#define ONRTNORDER 57
#define ONRTNTRADE 58
#define ONRTNEXECORDER 59
#define ONRTNLOCK 60
#define ONRTNINSTRUMENTSTATUS 61
#define ONRTNTRADINGNOTICE 62
#define ONRTNCOMBACTION 63


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
class TdApi : public CKSOTPTraderSpi
{
private:
	CKSOTPTraderApi* api;			//API对象
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

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用.
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用.
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	///        0x2004 服务器主动断开
	virtual void OnFrontDisconnected(int nReason);

	///登录请求响应
	virtual void OnRspUserLogin(CKSOTPRspUserLoginField *pRspUserLogin, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CKSOTPUserLogoutField *pUserLogout, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CKSOTPUserPasswordUpdateField *pUserPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///资金账户口令更新请求响应
	virtual void OnRspTradingAccountPasswordUpdate(CKSOTPTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入请求响应
	virtual void OnRspOrderInsert(CKSOTPInputOrderField *pInputOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单操作请求响应
	virtual void OnRspOrderAction(CKSOTPInputOrderActionField *pInputOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询报单响应
	virtual void OnRspQryOrder(CKSOTPOrderField *pOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询成交响应
	virtual void OnRspQryTrade(CKSOTPTradeField *pTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CKSOTPInvestorPositionField *pInvestorPosition, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CKSOTPTradingAccountField *pTradingAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CKSOTPInvestorField *pInvestor, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询合约账号响应
	virtual void OnRspQryTradingCode(CKSOTPTradingCodeField *pTradingCode, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询交易所响应
	virtual void OnRspQryExchange(CKSOTPExchangeField *pExchange, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询合约响应
	virtual void OnRspQryInstrument(CKSOTPInstrumentField *pInstrument, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CKSOTPInvestorPositionDetailField *pInvestorPositionDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询交易通知响应
	virtual void OnRspQryTradingNotice(CKSOTPTradingNoticeField *pTradingNotice, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///执行宣告录入请求响应
	virtual void OnRspExecOrderInsert(CKSOTPInputExecOrderField *pInputExecOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///锁定应答
	virtual void OnRspLockInsert(CKSOTPInputLockField *pInputLock, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///执行宣告操作请求响应
	virtual void OnRspExecOrderAction(CKSOTPInputExecOrderActionField *pInputExecOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询执行宣告响应
	virtual void OnRspQryExecOrder(CKSOTPExecOrderField *pExecOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询宣告数量请求响应
	virtual void OnRspQryExecOrderVolume(CKSOTPExecOrderVolumeField *pExecOrderVolume, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询锁定应答
	virtual void OnRspQryLock(CKSOTPLockField *pLock, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询锁定证券仓位应答
	virtual void OnRspQryLockPosition(CKSOTPLockPositionField *pLockPosition, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询标的券信息响应
	virtual void OnRspQryUnderlyingStockInfo(CKSOTPUnderlyingStockInfoField *pUnderlyingStockInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询个股期权手续费率请求响应
	virtual void OnRspQryOTPInsCommRate(CKSOTPOTPInsCommRateField *pOTPInsCommRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询个股期权合约保证金率请求响应
	virtual void OnRspQryInstrumentMarginRate(CKSOTPInstrumentMarginRateField *pInstrumentMarginRate, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询个股行权指派信息请求响应
	virtual void OnRspQryOTPAssignment(CKSOTPOTPAssignmentField *pOTPAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CKSOTPDepthMarketDataField *pDepthMarketData, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///发起银行资金转证券应答
	virtual void OnRspFromBankToStockByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///证券发起银行资金转证券通知
	virtual void OnRtnFromBankToStockByStock(CKSOTPRspTransferField *pRspTransfer);

	///证券发起证券资金转银行应答
	virtual void OnRspFromStockToBankByStock(CKSOTPReqTransferField *pReqTransfer, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///证券发起证券资金转银行通知
	virtual void OnRtnFromStockToBankByStock(CKSOTPRspTransferField *pRspTransfer);

	///证券发起查询银行余额通知
	virtual void OnRtnQueryBankBalanceByStock(CKSOTPNotifyQueryAccountField *pNotifyQueryAccount);

	///请求查询签约银行响应
	virtual void OnRspQryContractBank(CKSOTPContractBankField *pContractBank, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///证券发起查询银行余额应答
	virtual void OnRspQueryBankAccountMoneyByStock(CKSOTPReqQueryAccountField *pReqQueryAccount, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询转帐流水响应
	virtual void OnRspQryTransferSerial(CKSOTPTransferSerialField *pTransferSerial, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询结算信息确认响应
	virtual void OnRspQrySettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CKSOTPSettlementInfoConfirmField *pSettlementInfoConfirm, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者结算结果响应
	virtual void OnRspQrySettlementInfo(CKSOTPSettlementInfoField *pSettlementInfo, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询客户交易级别响应
	virtual void OnRspQryInvestorTradeLevel(CKSOTPInvestorTradeLevelField *pInvestorTradeLevel, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询个股限购额度响应
	virtual void OnRspQryPurchaseLimitAmt(CKSOTPPurchaseLimitAmtField *pPurchaseLimitAmt, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询个股限仓额度响应
	virtual void OnRspQryPositionLimitVol(CKSOTPPositionLimitVolField *pPositionLimitVol, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询历史报单响应
	virtual void OnRspQryHistoryOrder(CKSOTPHistoryOrderField *pHistoryOrder, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询历史成交响应
	virtual void OnRspQryHistoryTrade(CKSOTPHistoryTradeField *pHistoryTrade, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询历史行权指派明细响应
	virtual void OnRspQryHistoryAssignment(CKSOTPHistoryAssignmentField *pHistoryAssignment, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询行权交割明细响应
	virtual void OnRspQryDelivDetail(CKSOTPDelivDetailField *pDelivDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///自动行权执行操作响应
	virtual void OnRspAutoExecOrderAction(CKSOTPAutoExecOrderActionField *pAutoExecOrderAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///申请组合录入请求响应
	virtual void OnRspCombActionInsert(CKSOTPInputCombActionField *pInputCombAction, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询个股组合持仓明细应答
	virtual void OnRspQryInvestorCombinePosition(CKSOTPInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///个股可组合可拆分手数请求响应
	virtual void OnRspQryCombActionVolume(CKSOTPCombActionVolumeField *pCombActionVolume, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///客户每日出金额度申请响应
	virtual void OnRspFundOutCreditApply(CKSOTPInputFundOutCreditApplyField *pFundOutCreditApply, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///客户每日出金额度查询响应
	virtual void OnRspQryFundOutCredit(CKSOTPRspQryFundOutCreditField *pRspQryFundOutCredit, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///客户每日出金额度申请查询响应
	virtual void OnRspQryFundOutCreditApply(CKSOTPRspQryFundOutCreditApplyField *pRspQryFundOutCreditApply, CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CKSOTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单通知
	virtual void OnRtnOrder(CKSOTPOrderField *pOrder);

	///成交通知
	virtual void OnRtnTrade(CKSOTPTradeField *pTrade);

	///执行宣告通知
	virtual void OnRtnExecOrder(CKSOTPExecOrderField *pExecOrder);

	///锁定通知
	virtual void OnRtnLock(CKSOTPLockField *pLock);

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CKSOTPInstrumentStatusField *pInstrumentStatus);

	///交易通知
	virtual void OnRtnTradingNotice(CKSOTPTradingNoticeInfoField *pTradingNoticeInfo);

	///个股组合拆分委托通知
	virtual void OnRtnCombAction(CKSOTPCombActionField *pCombAction);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspUserPasswordUpdate(Task task);

	void processRspTradingAccountPasswordUpdate(Task task);

	void processRspOrderInsert(Task task);

	void processRspOrderAction(Task task);

	void processRspQryOrder(Task task);

	void processRspQryTrade(Task task);

	void processRspQryInvestorPosition(Task task);

	void processRspQryTradingAccount(Task task);

	void processRspQryInvestor(Task task);

	void processRspQryTradingCode(Task task);

	void processRspQryExchange(Task task);

	void processRspQryInstrument(Task task);

	void processRspQryInvestorPositionDetail(Task task);

	void processRspQryTradingNotice(Task task);

	void processRspExecOrderInsert(Task task);

	void processRspLockInsert(Task task);

	void processRspExecOrderAction(Task task);

	void processRspQryExecOrder(Task task);

	void processRspQryExecOrderVolume(Task task);

	void processRspQryLock(Task task);

	void processRspQryLockPosition(Task task);

	void processRspQryUnderlyingStockInfo(Task task);

	void processRspQryOTPInsCommRate(Task task);

	void processRspQryInstrumentMarginRate(Task task);

	void processRspQryOTPAssignment(Task task);

	void processRspQryDepthMarketData(Task task);

	void processRspFromBankToStockByStock(Task task);

	void processRtnFromBankToStockByStock(Task task);

	void processRspFromStockToBankByStock(Task task);

	void processRtnFromStockToBankByStock(Task task);

	void processRtnQueryBankBalanceByStock(Task task);

	void processRspQryContractBank(Task task);

	void processRspQueryBankAccountMoneyByStock(Task task);

	void processRspQryTransferSerial(Task task);

	void processRspQrySettlementInfoConfirm(Task task);

	void processRspSettlementInfoConfirm(Task task);

	void processRspQrySettlementInfo(Task task);

	void processRspQryInvestorTradeLevel(Task task);

	void processRspQryPurchaseLimitAmt(Task task);

	void processRspQryPositionLimitVol(Task task);

	void processRspQryHistoryOrder(Task task);

	void processRspQryHistoryTrade(Task task);

	void processRspQryHistoryAssignment(Task task);

	void processRspQryDelivDetail(Task task);

	void processRspAutoExecOrderAction(Task task);

	void processRspCombActionInsert(Task task);

	void processRspQryInvestorCombinePosition(Task task);

	void processRspQryCombActionVolume(Task task);

	void processRspFundOutCreditApply(Task task);

	void processRspQryFundOutCredit(Task task);

	void processRspQryFundOutCreditApply(Task task);

	void processRspError(Task task);

	void processRtnOrder(Task task);

	void processRtnTrade(Task task);

	void processRtnExecOrder(Task task);

	void processRtnLock(Task task);

	void processRtnInstrumentStatus(Task task);

	void processRtnTradingNotice(Task task);

	void processRtnCombAction(Task task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int i){};

	virtual void onRspError(dict error, int id, bool last) {};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

	virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

	virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last) {};

	virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestor(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingCode(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingNotice(dict data, dict error, int id, bool last) {};

	virtual void onRspExecOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspLockInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspExecOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExecOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExecOrderVolume(dict data, dict error, int id, bool last) {};

	virtual void onRspQryLock(dict data, dict error, int id, bool last) {};

	virtual void onRspQryLockPosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryUnderlyingStockInfo(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOTPInsCommRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrumentMarginRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOTPAssignment(dict data, dict error, int id, bool last) {};

	virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspFromBankToStockByStock(dict data, dict error, int id, bool last) {};

	virtual void onRtnFromBankToStockByStock(dict data) {};

	virtual void onRspFromStockToBankByStock(dict data, dict error, int id, bool last) {};

	virtual void onRtnFromStockToBankByStock(dict data) {};

	virtual void onRtnQueryBankBalanceByStock(dict data) {};

	virtual void onRspQryContractBank(dict data, dict error, int id, bool last) {};

	virtual void onRspQueryBankAccountMoneyByStock(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySettlementInfoConfirm(dict data, dict error, int id, bool last) {};

	virtual void onRspSettlementInfoConfirm(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySettlementInfo(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorTradeLevel(dict data, dict error, int id, bool last) {};

	virtual void onRspQryPurchaseLimitAmt(dict data, dict error, int id, bool last) {};

	virtual void onRspQryPositionLimitVol(dict data, dict error, int id, bool last) {};

	virtual void onRspQryHistoryOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryHistoryTrade(dict data, dict error, int id, bool last) {};

	virtual void onRspQryHistoryAssignment(dict data, dict error, int id, bool last) {};

	virtual void onRspQryDelivDetail(dict data, dict error, int id, bool last) {};

	virtual void onRspAutoExecOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspCombActionInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorCombinePosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryCombActionVolume(dict data, dict error, int id, bool last) {};

	virtual void onRspFundOutCreditApply(dict data, dict error, int id, bool last) {};

	virtual void onRspQryFundOutCredit(dict data, dict error, int id, bool last) {};

	virtual void onRspQryFundOutCreditApply(dict data, dict error, int id, bool last) {};

	virtual void onRtnOrder(dict data) {};

	virtual void onRtnTrade(dict data) {};

	virtual void onRtnExecOrder(dict data) {};

	virtual void onRtnLock(dict data) {};

	virtual void onRtnInstrumentStatus(dict data) {};

	virtual void onRtnTradingNotice(dict data) {};

	virtual void onRtnCombAction(dict data) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createOTPTraderApi(string pszFlowPath = "");

	void release();

	void init();

	int exit();

	string getTradingDay();

	void registerFront(string pszFrontAddress);

	void subscribePrivateTopic(int nType);

	void subscribePublicTopic(int nType);

	int reqUserLogin(dict req, int nRequestID);

	int reqUserLogout(dict req, int nRequestID);

	int reqUserPasswordUpdate(dict req, int nRequestID);

	int reqTradingAccountPasswordUpdate(dict req, int nRequestID);

	int reqOrderInsert(dict req, int nRequestID);

	int reqOrderAction(dict req, int nRequestID);

	int reqQryOrder(dict req, int nRequestID);

	int reqQryTrade(dict req, int nRequestID);

	int reqQryInvestorPosition(dict req, int nRequestID);

	int reqQryTradingAccount(dict req, int nRequestID);

	int reqQryInvestor(dict req, int nRequestID);

	int reqQryTradingCode(dict req, int nRequestID);

	int reqQryExchange(dict req, int nRequestID);

	int reqQryInstrument(dict req, int nRequestID);

	int reqQryInvestorPositionDetail(dict req, int nRequestID);

	int reqQryTradingNotice(dict req, int nRequestID);

	int reqExecOrderInsert(dict req, int nRequestID);

	int reqExecOrderAction(dict req, int nRequestID);

	int reqLockInsert(dict req, int nRequestID);

	int reqQryExecOrder(dict req, int nRequestID);

	int reqQryExecOrderVolume(dict req, int nRequestID);

	int reqQryLock(dict req, int nRequestID);

	int reqQryLockPosition(dict req, int nRequestID);

	int reqQryUnderlyingStockInfo(dict req, int nRequestID);

	int reqQryOTPInsCommRate(dict req, int nRequestID);

	int reqQryInstrumentMarginRate(dict req, int nRequestID);

	int reqQryOTPAssignment(dict req, int nRequestID);

	int reqQryDepthMarketData(dict req, int nRequestID);

	int reqFromBankToStockByStock(dict req, int nRequestID);

	int reqFromStockToBankByStock(dict req, int nRequestID);

	int reqQryContractBank(dict req, int nRequestID);

	int reqQueryBankAccountMoneyByStock(dict req, int nRequestID);

	int reqQryTransferSerial(dict req, int nRequestID);

	int reqQrySettlementInfoConfirm(dict req, int nRequestID);

	int reqSettlementInfoConfirm(dict req, int nRequestID);

	int reqQrySettlementInfo(dict req, int nRequestID);

	int reqQryInvestorTradeLevel(dict req, int nRequestID);

	int reqQryPurchaseLimitAmt(dict req, int nRequestID);

	int reqQryPositionLimitVol(dict req, int nRequestID);

	int reqQryHistoryOrder(dict req, int nRequestID);

	int reqQryHistoryTrade(dict req, int nRequestID);

	int reqQryHistoryAssignment(dict req, int nRequestID);

	int reqQryDelivDetail(dict req, int nRequestID);

	int reqAutoExecOrderAction(dict req, int nRequestID);

	int reqCombActionInsert(dict req, int nRequestID);

	int reqQryInvestorCombinePosition(dict req, int nRequestID);

	int reqQryCombActionVolume(dict req, int nRequestID);

	int reqFundOutCreditApply(dict req, int nRequestID);

	int reqQryFundOutCredit(dict req, int nRequestID);

	int reqQryFundOutCreditApply(dict req, int nRequestID);
};
