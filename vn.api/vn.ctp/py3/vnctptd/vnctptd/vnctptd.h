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
#include <boost/locale.hpp>			//字符集转换

//API
#include "ThostFtdcTraderApi.h"

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
class TdApi : public CThostFtdcTraderSpi
{
private:
	CThostFtdcTraderApi* api;			//API对象
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

	///客户端认证响应
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;


	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///资金账户口令更新请求响应
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///预埋单录入请求响应
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///预埋撤单录入请求响应
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单操作请求响应
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///查询最大报单数量响应
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///删除预埋单响应
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///删除预埋撤单响应
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///执行宣告录入请求响应
	virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///执行宣告操作请求响应
	virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///询价录入请求响应
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报价录入请求响应
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报价操作请求响应
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///锁定应答
	virtual void OnRspLockInsert(CThostFtdcInputLockField *pInputLock, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///申请组合录入请求响应
	virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询交易编码响应
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询合约保证金率响应
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询合约手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询交易所响应
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询产品响应
	virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者结算结果响应
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询转帐银行响应
	virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询客户通知响应
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询结算信息确认响应
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///查询保证金监管系统经纪公司资金账户密钥响应
	virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询仓单折抵信息响应
	virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者品种/跨品种保证金响应
	virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询交易所保证金率响应
	virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询交易所调整保证金率响应
	virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询汇率响应
	virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询二级代理操作员银期权限响应
	virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询产品报价汇率
	virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询产品组
	virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询期权交易成本响应
	virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询期权合约手续费响应
	virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询执行宣告响应
	virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询询价响应
	virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询报价响应
	virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询锁定应答
	virtual void OnRspQryLock(CThostFtdcLockField *pLock, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询锁定证券仓位应答
	virtual void OnRspQryLockPosition(CThostFtdcLockPositionField *pLockPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询投资者分级
	virtual void OnRspQryInvestorLevel(CThostFtdcInvestorLevelField *pInvestorLevel, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询E+1日行权冻结响应
	virtual void OnRspQryExecFreeze(CThostFtdcExecFreezeField *pExecFreeze, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询组合合约安全系数响应
	virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询申请组合响应
	virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询转帐流水响应
	virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询银期签约关系响应
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) ;

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) ;

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) ;

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) ;

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) ;

	///交易通知
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) ;

	///提示条件单校验错误
	virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) ;

	///执行宣告通知
	virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) ;

	///执行宣告录入错误回报
	virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) ;

	///执行宣告操作错误回报
	virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) ;

	///询价录入错误回报
	virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) ;

	///报价通知
	virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote) ;

	///报价录入错误回报
	virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) ;

	///报价操作错误回报
	virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) ;

	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) ;

	///保证金监控中心用户令牌
	virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) ;

	///锁定通知
	virtual void OnRtnLock(CThostFtdcLockField *pLock) ;

	///锁定错误通知
	virtual void OnErrRtnLockInsert(CThostFtdcInputLockField *pInputLock, CThostFtdcRspInfoField *pRspInfo) ;

	///申请组合通知
	virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction) ;

	///申请组合录入错误回报
	virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) ;

	///请求查询签约银行响应
	virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询预埋单响应
	virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询预埋撤单响应
	virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询交易通知响应
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询经纪公司交易参数响应
	virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询经纪公司交易算法响应
	virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///请求查询监控中心用户令牌
	virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///银行发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) ;

	///银行发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) ;

	///银行发起冲正银行转期货通知
	virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) ;

	///银行发起冲正期货转银行通知
	virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) ;

	///期货发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) ;

	///期货发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) ;

	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) ;

	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) ;

	///期货发起查询银行余额通知
	virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) ;

	///期货发起银行资金转期货错误回报
	virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) ;

	///期货发起期货资金转银行错误回报
	virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) ;

	///系统运行时期货端手工发起冲正银行转期货错误回报
	virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) ;

	///系统运行时期货端手工发起冲正期货转银行错误回报
	virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) ;

	///期货发起查询银行余额错误回报
	virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) ;

	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) ;

	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) ;

	///期货发起银行资金转期货应答
	virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///期货发起期货资金转银行应答
	virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///期货发起查询银行余额应答
	virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///银行发起银期开户通知
	virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) ;

	///银行发起银期销户通知
	virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) ;

	///银行发起变更银行账号通知
	virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) ;

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processHeartBeatWarning(Task task);

	void processRspAuthenticate(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspUserPasswordUpdate(Task task);

	void processRspTradingAccountPasswordUpdate(Task task);

	void processRspOrderInsert(Task task);

	void processRspParkedOrderInsert(Task task);

	void processRspParkedOrderAction(Task task);

	void processRspOrderAction(Task task);

	void processRspQueryMaxOrderVolume(Task task);

	void processRspSettlementInfoConfirm(Task task);

	void processRspRemoveParkedOrder(Task task);

	void processRspRemoveParkedOrderAction(Task task);

	void processRspExecOrderInsert(Task task);

	void processRspExecOrderAction(Task task);

	void processRspForQuoteInsert(Task task);

	void processRspQuoteInsert(Task task);

	void processRspQuoteAction(Task task);

	void processRspLockInsert(Task task);

	void processRspCombActionInsert(Task task);

	void processRspQryOrder(Task task);

	void processRspQryTrade(Task task);

	void processRspQryInvestorPosition(Task task);

	void processRspQryTradingAccount(Task task);

	void processRspQryInvestor(Task task);

	void processRspQryTradingCode(Task task);

	void processRspQryInstrumentMarginRate(Task task);

	void processRspQryInstrumentCommissionRate(Task task);

	void processRspQryExchange(Task task);

	void processRspQryProduct(Task task);

	void processRspQryInstrument(Task task);

	void processRspQryDepthMarketData(Task task);

	void processRspQrySettlementInfo(Task task);

	void processRspQryTransferBank(Task task);

	void processRspQryInvestorPositionDetail(Task task);

	void processRspQryNotice(Task task);

	void processRspQrySettlementInfoConfirm(Task task);

	void processRspQryInvestorPositionCombineDetail(Task task);

	void processRspQryCFMMCTradingAccountKey(Task task);

	void processRspQryEWarrantOffset(Task task);

	void processRspQryInvestorProductGroupMargin(Task task);

	void processRspQryExchangeMarginRate(Task task);

	void processRspQryExchangeMarginRateAdjust(Task task);

	void processRspQryExchangeRate(Task task);

	void processRspQrySecAgentACIDMap(Task task);

	void processRspQryProductExchRate(Task task);

	void processRspQryProductGroup(Task task);

	void processRspQryOptionInstrTradeCost(Task task);

	void processRspQryOptionInstrCommRate(Task task);

	void processRspQryExecOrder(Task task);

	void processRspQryForQuote(Task task);

	void processRspQryQuote(Task task);

	void processRspQryLock(Task task);

	void processRspQryLockPosition(Task task);

	void processRspQryInvestorLevel(Task task);

	void processRspQryExecFreeze(Task task);

	void processRspQryCombInstrumentGuard(Task task);

	void processRspQryCombAction(Task task);

	void processRspQryTransferSerial(Task task);

	void processRspQryAccountregister(Task task);

	void processRspError(Task task);

	void processRtnOrder(Task task);

	void processRtnTrade(Task task);

	void processErrRtnOrderInsert(Task task);

	void processErrRtnOrderAction(Task task);

	void processRtnInstrumentStatus(Task task);

	void processRtnTradingNotice(Task task);

	void processRtnErrorConditionalOrder(Task task);

	void processRtnExecOrder(Task task);

	void processErrRtnExecOrderInsert(Task task);

	void processErrRtnExecOrderAction(Task task);

	void processErrRtnForQuoteInsert(Task task);

	void processRtnQuote(Task task);

	void processErrRtnQuoteInsert(Task task);

	void processErrRtnQuoteAction(Task task);

	void processRtnForQuoteRsp(Task task);

	void processRtnCFMMCTradingAccountToken(Task task);

	void processRtnLock(Task task);

	void processErrRtnLockInsert(Task task);

	void processRtnCombAction(Task task);

	void processErrRtnCombActionInsert(Task task);

	void processRspQryContractBank(Task task);

	void processRspQryParkedOrder(Task task);

	void processRspQryParkedOrderAction(Task task);

	void processRspQryTradingNotice(Task task);

	void processRspQryBrokerTradingParams(Task task);

	void processRspQryBrokerTradingAlgos(Task task);

	void processRspQueryCFMMCTradingAccountToken(Task task);

	void processRtnFromBankToFutureByBank(Task task);

	void processRtnFromFutureToBankByBank(Task task);

	void processRtnRepealFromBankToFutureByBank(Task task);

	void processRtnRepealFromFutureToBankByBank(Task task);

	void processRtnFromBankToFutureByFuture(Task task);

	void processRtnFromFutureToBankByFuture(Task task);

	void processRtnRepealFromBankToFutureByFutureManual(Task task);

	void processRtnRepealFromFutureToBankByFutureManual(Task task);

	void processRtnQueryBankBalanceByFuture(Task task);

	void processErrRtnBankToFutureByFuture(Task task);

	void processErrRtnFutureToBankByFuture(Task task);

	void processErrRtnRepealBankToFutureByFutureManual(Task task);

	void processErrRtnRepealFutureToBankByFutureManual(Task task);

	void processErrRtnQueryBankBalanceByFuture(Task task);

	void processRtnRepealFromBankToFutureByFuture(Task task);

	void processRtnRepealFromFutureToBankByFuture(Task task);

	void processRspFromBankToFutureByFuture(Task task);

	void processRspFromFutureToBankByFuture(Task task);

	void processRspQueryBankAccountMoneyByFuture(Task task);

	void processRtnOpenAccountByBank(Task task);

	void processRtnCancelAccountByBank(Task task);

	void processRtnChangeAccountByBank(Task task);

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

	virtual void onRspParkedOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspParkedOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQueryMaxOrderVolume(dict data, dict error, int id, bool last) {};

	virtual void onRspSettlementInfoConfirm(dict data, dict error, int id, bool last) {};

	virtual void onRspRemoveParkedOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspRemoveParkedOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspExecOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspExecOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspForQuoteInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspQuoteInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspQuoteAction(dict data, dict error, int id, bool last) {};

	virtual void onRspLockInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspCombActionInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestor(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingCode(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrumentMarginRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

	virtual void onRspQryProduct(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

	virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySettlementInfo(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTransferBank(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last) {};

	virtual void onRspQryNotice(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySettlementInfoConfirm(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPositionCombineDetail(dict data, dict error, int id, bool last) {};

	virtual void onRspQryCFMMCTradingAccountKey(dict data, dict error, int id, bool last) {};

	virtual void onRspQryEWarrantOffset(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorProductGroupMargin(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchangeMarginRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchangeMarginRateAdjust(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchangeRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySecAgentACIDMap(dict data, dict error, int id, bool last) {};

	virtual void onRspQryProductExchRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryProductGroup(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOptionInstrTradeCost(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOptionInstrCommRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExecOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryForQuote(dict data, dict error, int id, bool last) {};

	virtual void onRspQryQuote(dict data, dict error, int id, bool last) {};

	virtual void onRspQryLock(dict data, dict error, int id, bool last) {};

	virtual void onRspQryLockPosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorLevel(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExecFreeze(dict data, dict error, int id, bool last) {};

	virtual void onRspQryCombInstrumentGuard(dict data, dict error, int id, bool last) {};

	virtual void onRspQryCombAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last) {};

	virtual void onRspQryAccountregister(dict data, dict error, int id, bool last) {};

	virtual void onRspError(dict error, int id, bool last) {};

	virtual void onRtnOrder(dict data) {};

	virtual void onRtnTrade(dict data) {};

	virtual void onErrRtnOrderInsert(dict data, dict error) {};

	virtual void onErrRtnOrderAction(dict data, dict error) {};

	virtual void onRtnInstrumentStatus(dict data) {};

	virtual void onRtnTradingNotice(dict data) {};

	virtual void onRtnErrorConditionalOrder(dict data) {};

	virtual void onRtnExecOrder(dict data) {};

	virtual void onErrRtnExecOrderInsert(dict data, dict error) {};

	virtual void onErrRtnExecOrderAction(dict data, dict error) {};

	virtual void onErrRtnForQuoteInsert(dict data, dict error) {};

	virtual void onRtnQuote(dict data) {};

	virtual void onErrRtnQuoteInsert(dict data, dict error) {};

	virtual void onErrRtnQuoteAction(dict data, dict error) {};

	virtual void onRtnForQuoteRsp(dict data) {};

	virtual void onRtnCFMMCTradingAccountToken(dict data) {};

	virtual void onRtnLock(dict data) {};

	virtual void onErrRtnLockInsert(dict data, dict error) {};

	virtual void onRtnCombAction(dict data) {};

	virtual void onErrRtnCombActionInsert(dict data, dict error) {};

	virtual void onRspQryContractBank(dict data, dict error, int id, bool last) {};

	virtual void onRspQryParkedOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryParkedOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingNotice(dict data, dict error, int id, bool last) {};

	virtual void onRspQryBrokerTradingParams(dict data, dict error, int id, bool last) {};

	virtual void onRspQryBrokerTradingAlgos(dict data, dict error, int id, bool last) {};

	virtual void onRspQueryCFMMCTradingAccountToken(dict data, dict error, int id, bool last) {};

	virtual void onRtnFromBankToFutureByBank(dict data) {};

	virtual void onRtnFromFutureToBankByBank(dict data) {};

	virtual void onRtnRepealFromBankToFutureByBank(dict data) {};

	virtual void onRtnRepealFromFutureToBankByBank(dict data) {};

	virtual void onRtnFromBankToFutureByFuture(dict data) {};

	virtual void onRtnFromFutureToBankByFuture(dict data) {};

	virtual void onRtnRepealFromBankToFutureByFutureManual(dict data) {};

	virtual void onRtnRepealFromFutureToBankByFutureManual(dict data) {};

	virtual void onRtnQueryBankBalanceByFuture(dict data) {};

	virtual void onErrRtnBankToFutureByFuture(dict data, dict error) {};

	virtual void onErrRtnFutureToBankByFuture(dict data, dict error) {};

	virtual void onErrRtnRepealBankToFutureByFutureManual(dict data, dict error) {};

	virtual void onErrRtnRepealFutureToBankByFutureManual(dict data, dict error) {};

	virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error) {};

	virtual void onRtnRepealFromBankToFutureByFuture(dict data) {};

	virtual void onRtnRepealFromFutureToBankByFuture(dict data) {};

	virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRtnOpenAccountByBank(dict data) {};

	virtual void onRtnCancelAccountByBank(dict data) {};

	virtual void onRtnChangeAccountByBank(dict data) {};


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

	int reqUserPasswordUpdate(dict req, int nRequestID);

	int reqTradingAccountPasswordUpdate(dict req, int nRequestID);

	int reqOrderInsert(dict req, int nRequestID);

	int reqParkedOrderInsert(dict req, int nRequestID);

	int reqParkedOrderAction(dict req, int nRequestID);

	int reqOrderAction(dict req, int nRequestID);

	int reqQueryMaxOrderVolume(dict req, int nRequestID);

	int reqSettlementInfoConfirm(dict req, int nRequestID);

	int reqRemoveParkedOrder(dict req, int nRequestID);

	int reqRemoveParkedOrderAction(dict req, int nRequestID);

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

	int reqQryTradingAccount(dict req, int nRequestID);

	int reqQryInvestor(dict req, int nRequestID);

	int reqQryTradingCode(dict req, int nRequestID);

	int reqQryInstrumentMarginRate(dict req, int nRequestID);

	int reqQryInstrumentCommissionRate(dict req, int nRequestID);

	int reqQryExchange(dict req, int nRequestID);

	int reqQryProduct(dict req, int nRequestID);

	int reqQryInstrument(dict req, int nRequestID);

	int reqQryDepthMarketData(dict req, int nRequestID);

	int reqQrySettlementInfo(dict req, int nRequestID);

	int reqQryTransferBank(dict req, int nRequestID);

	int reqQryInvestorPositionDetail(dict req, int nRequestID);

	int reqQryNotice(dict req, int nRequestID);

	int reqQrySettlementInfoConfirm(dict req, int nRequestID);

	int reqQryInvestorPositionCombineDetail(dict req, int nRequestID);

	int reqQryCFMMCTradingAccountKey(dict req, int nRequestID);

	int reqQryEWarrantOffset(dict req, int nRequestID);

	int reqQryInvestorProductGroupMargin(dict req, int nRequestID);

	int reqQryExchangeMarginRate(dict req, int nRequestID);

	int reqQryExchangeMarginRateAdjust(dict req, int nRequestID);

	int reqQryExchangeRate(dict req, int nRequestID);

	int reqQrySecAgentACIDMap(dict req, int nRequestID);

	int reqQryProductExchRate(dict req, int nRequestID);

	int reqQryProductGroup(dict req, int nRequestID);

	int reqQryOptionInstrTradeCost(dict req, int nRequestID);

	int reqQryOptionInstrCommRate(dict req, int nRequestID);

	int reqQryExecOrder(dict req, int nRequestID);

	int reqQryForQuote(dict req, int nRequestID);

	int reqQryQuote(dict req, int nRequestID);

	int reqQryLock(dict req, int nRequestID);

	int reqQryLockPosition(dict req, int nRequestID);

	int reqQryInvestorLevel(dict req, int nRequestID);

	int reqQryExecFreeze(dict req, int nRequestID);

	int reqQryCombInstrumentGuard(dict req, int nRequestID);

	int reqQryCombAction(dict req, int nRequestID);

	int reqQryTransferSerial(dict req, int nRequestID);

	int reqQryAccountregister(dict req, int nRequestID);

	int reqQryContractBank(dict req, int nRequestID);

	int reqQryParkedOrder(dict req, int nRequestID);

	int reqQryParkedOrderAction(dict req, int nRequestID);

	int reqQryTradingNotice(dict req, int nRequestID);

	int reqQryBrokerTradingParams(dict req, int nRequestID);

	int reqQryBrokerTradingAlgos(dict req, int nRequestID);

	int reqQueryCFMMCTradingAccountToken(dict req, int nRequestID);

	int reqFromBankToFutureByFuture(dict req, int nRequestID);

	int reqFromFutureToBankByFuture(dict req, int nRequestID);

	int reqQueryBankAccountMoneyByFuture(dict req, int nRequestID);
};

