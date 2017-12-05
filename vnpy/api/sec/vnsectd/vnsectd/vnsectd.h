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
#include "DFITCSECTraderApi.h"

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
#define ONRSPSTOCKUSERPASSWORDUPDATE 6
#define ONRSPSTOCKENTRUSTORDER 7
#define ONRSPSTOCKWITHDRAWORDER 8
#define ONRSPSTOCKQRYENTRUSTORDER 9
#define ONRSPSTOCKQRYREALTIMETRADE 10
#define ONRSPSTOCKQRYSERIALTRADE 11
#define ONRSPSTOCKQRYPOSITION 12
#define ONRSPSTOCKQRYCAPITALACCOUNTINFO 13
#define ONRSPSTOCKQRYACCOUNTINFO 14
#define ONRSPSTOCKQRYSHAREHOLDERINFO 15
#define ONRSPSTOCKTRANSFERFUNDS 16
#define ONRSPSTOCKENTRUSTBATCHORDER 17
#define ONRSPSTOCKWITHDRAWBATCHORDER 18
#define ONRSPSTOCKCALCABLEENTRUSTQTY 19
#define ONRSPSTOCKCALCABLEPURCHASEETFQTY 20
#define ONRSPSTOCKQRYFREEZEFUNDSDETAIL 21
#define ONRSPSTOCKQRYFREEZESTOCKDETAIL 22
#define ONRSPSTOCKQRYTRANSFERSTOCKDETAIL 23
#define ONRSPSTOCKQRYTRANSFERFUNDSDETAIL 24
#define ONRSPSTOCKQRYSTOCKINFO 25
#define ONRSPSTOCKQRYSTOCKSTATICINFO 26
#define ONRSPSTOCKQRYTRADETIME 27
#define ONSTOCKENTRUSTORDERRTN 28
#define ONSTOCKTRADERTN 29
#define ONSTOCKWITHDRAWORDERRTN 30
#define ONRSPSOPUSERLOGIN 31
#define ONRSPSOPUSERLOGOUT 32
#define ONRSPSOPUSERPASSWORDUPDATE 33
#define ONRSPSOPENTRUSTORDER 34
#define ONRSPSOPGROUPSPLIT 35
#define ONRSPSOPQRYGROUPPOSITION 36
#define ONRSPSOPLOCKOUNLOCKSTOCK 37
#define ONRSPSOPWITHDRAWORDER 38
#define ONRSPSOPQRYENTRUSTORDER 39
#define ONRSPSOPQRYSERIALTRADE 40
#define ONRSPSOPQRYPOSITION 41
#define ONRSPSOPQRYCOLLATERALPOSITION 42
#define ONRSPSOPQRYCAPITALACCOUNTINFO 43
#define ONRSPSOPQRYACCOUNTINFO 44
#define ONRSPSOPQRYSHAREHOLDERINFO 45
#define ONRSPSOPCALCABLEENTRUSTQTY 46
#define ONRSPSOPQRYABLELOCKSTOCK 47
#define ONRSPSOPQRYCONTACTINFO 48
#define ONRSPSOPEXECTUEORDER 49
#define ONRSPSOPQRYEXECASSIINFO 50
#define ONRSPSOPQRYTRADETIME 51
#define ONRSPSOPQRYEXCHANGEINFO 52
#define ONRSPSOPQRYCOMMISSION 53
#define ONRSPSOPQRYDEPOSIT 54
#define ONRSPSOPQRYCONTRACTOBJECTINFO 55
#define ONSOPENTRUSTORDERRTN 56
#define ONSOPTRADERTN 57
#define ONSOPWITHDRAWORDERRTN 58
#define ONRSPFASLUSERLOGIN 59
#define ONRSPFASLUSERLOGOUT 60
#define ONRSPFASLQRYABLEFININFO 61
#define ONRSPFASLQRYABLESLOINFO 62
#define ONRSPFASLTRANSFERCOLLATERAL 63
#define ONRSPFASLDIRECTREPAYMENT 64
#define ONRSPFASLREPAYSTOCKTRANSFER 65
#define ONRSPFASLENTRUSTCRDTORDER 66
#define ONRSPFASLENTRUSTORDER 67
#define ONRSPFASLCALCABLEENTRUSTCRDTQTY 68
#define ONRSPFASLQRYCRDTFUNDS 69
#define ONRSPFASLQRYCRDTCONTRACT 70
#define ONRSPFASLQRYCRDTCONCHANGEINFO 71
#define ONRSPFASLTRANSFERFUNDS 72
#define ONRSPFASLQRYACCOUNTINFO 73
#define ONRSPFASLQRYCAPITALACCOUNTINFO 74
#define ONRSPFASLQRYSHAREHOLDERINFO 75
#define ONRSPFASLQRYPOSITION 76
#define ONRSPFASLQRYENTRUSTORDER 77
#define ONRSPFASLQRYSERIALTRADE 78
#define ONRSPFASLQRYREALTIMETRADE 79
#define ONRSPFASLQRYFREEZEFUNDSDETAIL 80
#define ONRSPFASLQRYFREEZESTOCKDETAIL 81
#define ONRSPFASLQRYTRANSFERFUNDSDETAIL 82
#define ONRSPFASLWITHDRAWORDER 83
#define ONRSPFASLQRYSYSTEMTIME 84
#define ONRSPFASLQRYTRANSFERREDCONTRACT 85
#define ONRSPFASLDESIRABLEFUNDSOUT 86
#define ONRSPFASLQRYGUARANTEEDCONTRACT 87
#define ONRSPFASLQRYUNDERLYINGCONTRACT 88
#define ONFASLENTRUSTORDERRTN 89
#define ONFASLTRADERTN 90
#define ONFASLWITHDRAWORDERRTN 91



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
class TdApi : public DFITCSECTraderSpi
{
private:
	DFITCSECTraderApi *api;				//API对象
	thread *task_thread;				//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task*> task_queue;	//任务队列

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
	/**
	* SEC-网络连接正常响应
	*/
	virtual void OnFrontConnected();
	/**
	* SEC-网络连接不正常响应
	*/
	virtual void OnFrontDisconnected(int nReason) ;
	/**
	* SEC-消息通知
	*/
	virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice) ;
	/**
	* ERR-错误应答
	* @param pRspInfo:指针若非空，返回错误信息结构地址
	*/
	virtual void OnRspError(DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-登录响应
	* @param pData:指针若非空,返回用户登录响应信息结构体的地址,表明登录请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明登录请求失败
	*/
	virtual void OnRspStockUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-登出响应
	* @param pData:指针若非空,返回用户登出响应信息结构体的地址,表明登出请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明登出请求失败
	*/
	virtual void OnRspStockUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-密码更新响应
	* @param pData:指针若非空,返回用户密码更新响应信息结构体的地址,表明密码更新请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明密码更新请求失败
	*/
	virtual void OnRspStockUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-委托报单响应
	* @param pData:指针若非空,返回用户委托报单响应信息结构体的地址,表明报单请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托报单请求失败
	*/
	virtual void OnRspStockEntrustOrder(DFITCStockRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-委托撤单响应
	* @param pData:指针若非空,返回用户委托撤单响应信息结构体的地址,表明撤单请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托撤单请求失败
	*/
	virtual void OnRspStockWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-委托查询响应
	* @param pData:指针若非空,返回用户委托查询响应信息结构体的地址,表明查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryEntrustOrder(DFITCStockRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-实时成交查询响应
	* @param pData:指针若非空,返回用户实时成交查询响应信息结构体的地址,表明实时成交查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明实时成交查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-分笔成交查询响应
	* @param pData:指针若非空,返回用户分笔成交查询响应信息结构体的地址,表明分笔成交查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明分笔成交查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQrySerialTrade(DFITCStockRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-持仓查询响应
	* @param pData:指针若非空,返回用户持仓查询响应信息结构体的地址,表明持仓查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明持仓查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-资金账号查询响应
	* @param pData:指针若非空,返回用户资金账号查询响应信息结构体的地址,表明资金账号查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明资金账号查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-交易账号查询响应
	* @param pData:指针若非空,返回用户交易账号查询响应信息结构体的地址,表明交易账号查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明交易账号查询请求失败
	*/
	virtual void OnRspStockQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-股东号查询响应
	* @param pData:指针若非空,返回用户股东号查询响应信息结构体的地址,表明股东号查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明股东号查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-资金调拨响应
	* @param pData:指针若非空,返回用户资金调拨响应信息结构体的地址,表明股资金调拨请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明资金调拨请求失败
	*/
	virtual void OnRspStockTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-批量委托响应
	* @param pData:指针若非空,返回用户批量委托响应信息结构体的地址,表明批量委托请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明批量委托请求失败
	*/
	virtual void OnRspStockEntrustBatchOrder(DFITCStockRspEntrustBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-批量撤单响应
	* @param pData:指针若非空,返回用户批量撤单响应信息结构体的地址,表明批量撤单请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明批量撤单请求失败
	*/
	virtual void OnRspStockWithdrawBatchOrder(DFITCStockRspWithdrawBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-计算可委托数量响应
	* @param pData:指针若非空,返回用户计算可委托数量响应信息结构体的地址,表明计算可委托数量请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明计算可委托数量请求失败
	*/
	virtual void OnRspStockCalcAbleEntrustQty(DFITCStockRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-计算申购ETF数量响应
	* @param pData:指针若非空,返回用户计算申购ETF数量响应信息结构体的地址,表明计算申购ETF数量请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明计算申购ETF数量请求失败
	*/
	virtual void OnRspStockCalcAblePurchaseETFQty(DFITCStockRspCalcAblePurchaseETFQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-冻结资金明细查询响应
	* @param pData:指针若非空,返回用户冻结资金明细查询响应信息结构体的地址,表明冻结资金明细查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明冻结资金明细查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-冻结证券明细查询响应
	* @param pData:指针若非空,返回用户冻结证券明细查询响应信息结构体的地址,表明冻结证券明细查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明冻结证券明细查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-调拨证券明细查询响应
	* @param pData:指针若非空,返回用户调拨证券明细查询响应信息结构体的地址,表明调拨证券明细查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明调拨证券明细查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryTransferStockDetail(DFITCStockRspQryTransferStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-调拨资金明细查询响应
	* @param pData:指针若非空,返回用户调拨资金明细查询响应信息结构体的地址,表明调拨资金明细查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明调拨资金明细查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-证券信息查询响应
	* @param pData:指针若非空,返回用户证券信息查询响应信息结构体的地址,表明证券信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明证券信息查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryStockInfo(DFITCStockRspQryStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-证券静态信息查询响应
	* @param pData:指针若非空,返回用户证券静态信息查询响应信息结构体的地址,表明证券静态信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明证券静态信息查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspStockQryStockStaticInfo(DFITCStockRspQryStockStaticField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-交易时间查询响应
	* @param pData:指针若非空,返回用户交易时间查询响应信息结构体的地址,表明交易时间查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明交易时间查询请求失败
	*/
	virtual void OnRspStockQryTradeTime(DFITCStockRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-委托回报响应
	* @param pData:返回委托回报结构体的地址
	*/
	virtual void OnStockEntrustOrderRtn(DFITCStockEntrustOrderRtnField * pData);
	/**
	* STOCK-成交回报响应
	* @param pData:返回成交回报结构体的地址
	*/
	virtual void OnStockTradeRtn(DFITCStockTradeRtnField * pData);
	/**
	* STOCK-撤单回报响应
	* @param pData:返回撤单回报结构体的地址
	*/
	virtual void OnStockWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField * pData);

	/**
	* SOP-登录响应
	* @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
	*/
	virtual void OnRspSOPUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-登出响应
	* @param pData:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
	*/
	virtual void OnRspSOPUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-用户口令更新响应
	* @param pData:指针若非空,返回用户口令更新响应信息结构地址,表明用户口令更新请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明用户口令更新请求失败
	*/
	virtual void OnRspSOPUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-报单响应
	* @param pData:指针若非空,返回用户报单响应信息结构地址,表明报单请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明报单请求失败
	*/
	virtual void OnRspSOPEntrustOrder(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-组合拆分委托响应
	* @param pData:指针若非空,返回用户响应信息结构地址,表明组合拆分委托请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明组合拆分委托请求失败
	*/
	virtual void OnRspSOPGroupSplit(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-查询客户组合持仓明细响应
	* @param pData:指针若非空,返回用户查询客户组合持仓明细响应结构地址,表明查询客户组合持仓明细请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明查询客户组合持仓明细请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryGroupPosition(DFITCSOPRspQryGroupPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-证券锁定解锁响应
	* @param pData:指针若非空,返回用户证券锁定解锁响应信息结构地址,表明证券锁定解锁请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明证券锁定解锁请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPLockOUnLockStock(DFITCSOPRspLockOUnLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-撤单响应
	* @param pData:指针若非空,返回用户撤单响应信息结构地址,表明撤单请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明撤单请求失败
	*/
	virtual void OnRspSOPWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-委托查询响应
	* @param pData:指针若非空,返回用户委托查询响应信息结构地址,表明委托查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明委托查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryEntrustOrder(DFITCSOPRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-分笔成交查询响应
	* @param pData:指针若非空,返回用户分笔成交查询响应信息结构地址,表明分笔成交查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明分笔成交查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQrySerialTrade(DFITCSOPRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-持仓查询响应
	* @param pData:指针若非空,返回用户持仓查询响应信息结构地址,表明持仓查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明持仓查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryPosition(DFITCSOPRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-客户担保持仓查询响应
	* @param pData:指针若非空,返回用户客户担保持仓查询响应信息结构地址,表明客户担保持仓查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户担保持仓查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryCollateralPosition(DFITCSOPRspQryCollateralPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-客户资金查询响应
	* @param pData:指针若非空,返回用户客户资金查询响应信息结构地址,表明客户客户资金查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户资金查询请求失败
	*/
	virtual void OnRspSOPQryCapitalAccountInfo(DFITCSOPRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-客户信息查询响应
	* @param pData:指针若非空,返回用户客户信息查询响应信息结构地址,表明客户客户信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户信息查询请求失败
	*/
	virtual void OnRspSOPQryAccountInfo(DFITCSOPRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-股东信息查询响应
	* @param pData:指针若非空,返回用户股东信息查询响应信息结构地址,表明客户股东信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户股东信息查询请求失败
	*/
	virtual void OnRspSOPQryShareholderInfo(DFITCSOPRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-可委托数量查询响应
	* @param pData:指针若非空,返回用户可委托数量查询响应信息结构地址,表明客户可委托数量查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户可委托数量查询请求失败
	*/
	virtual void OnRspSOPCalcAbleEntrustQty(DFITCSOPRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-客户可锁定证券查询响应
	* @param pData:指针若非空,返回用户客户可锁定证券查询响应信息结构地址,表明客户客户可锁定证券查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可锁定证券查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryAbleLockStock(DFITCSOPRspQryAbleLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-期权合约代码查询响应
	* @param pData:指针若非空,返回用户期权合约代码查询响应信息结构地址,表明客户期权合约代码查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户期权合约代码查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryContactInfo(DFITCSOPRspQryContactField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-执行委托响应
	* @param pData:指针若非空,返回用户执行委托响应信息结构地址,表明客户执行委托请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户执行委托请求失败
	*/
	virtual void OnRspSOPExectueOrder(DFITCSOPRspExectueOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-客户行权指派信息查询响应
	* @param pData:指针若非空,返回用户客户行权指派信息查询响应信息结构地址,表明客户客户行权指派信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户行权指派信息查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryExecAssiInfo(DFITCSOPRspQryExecAssiInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-查询交易时间响应
	* @param pData:指针若非空,返回用户查询交易时间响应信息结构地址,表明客户查询交易时间请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询交易时间请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryTradeTime(DFITCSOPRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-获取所有交易所参数响应
	* @param pData:指针若非空,返回用户获取所有交易所参数响应信息结构地址,表明客户获取所有交易所参数请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户获取所有交易所参数请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryExchangeInfo(DFITCSOPRspQryExchangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-查询手续费参数响应
	* @param pData:指针若非空,返回用户查询手续费参数响应信息结构地址,表明客户查询手续费参数请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询手续费参数请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryCommission(DFITCSOPRspQryCommissionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-查询保证金率参数响应
	* @param pData:指针若非空,返回用户查询保证金率参数响应信息结构地址,表明客户查询保证金率参数请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询保证金率参数请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryDeposit(DFITCSOPRspQryDepositField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-期权标的信息查询响应
	* @param pData:指针若非空,返回用户期权标的信息查询响应信息结构地址,表明客户期权标的信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户期权标的信息查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspSOPQryContractObjectInfo(DFITCSOPRspQryContractObjectField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-委托回报响应
	* @param pData:返回委托回报结构体的地址
	*/
	virtual void OnSOPEntrustOrderRtn(DFITCSOPEntrustOrderRtnField * pData);
	/**
	* SOP-成交回报响应
	* @param pData:返回成交回报结构体的地址
	*/
	virtual void OnSOPTradeRtn(DFITCSOPTradeRtnField * pData);
	/**
	* SOP-撤单回报响应
	* @param pData:返回撤单回报结构体的地址
	*/
	virtual void OnSOPWithdrawOrderRtn(DFITCSOPWithdrawOrderRtnField * pData);

	/**
	* FASL-登录响应
	* @param pData:指针若非空,返回用户融资融券登录响应信息结构地址,表明客户融资融券登录请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券登录请求失败
	*/
	virtual void OnRspFASLUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-登出响应
	* @param pData:指针若非空,返回用户融资融券登出响应信息结构地址,表明客户融资融券登出请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券登出请求失败
	*/
	virtual void OnRspFASLUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-客户可融资信息响应
	* @param pData:指针若非空,返回用户客户可融资信息响应信息结构地址,表明客户客户可融资信息请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可融资信息请求失败
	*/
	virtual void OnRspFASLQryAbleFinInfo(DFITCFASLRspAbleFinInfoField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-客户可融券信息响应
	* @param pData:指针若非空,返回用户客户可融券信息响应信息结构地址,表明客户客户可融券信息请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可融券信息请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryAbleSloInfo(DFITCFASLRspAbleSloInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-担保物划转响应
	* @param pData:指针若非空,返回用户担保物划转响应信息结构地址,表明客户担保物划转请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户担保物划转请求失败
	*/
	virtual void OnRspFASLTransferCollateral(DFITCFASLRspTransferCollateralField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-直接还款响应
	* @param pData:指针若非空,返回用户直接还款响应信息结构地址,表明客户直接还款请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户直接还款请求失败
	*/
	virtual void OnRspFASLDirectRepayment(DFITCFASLRspDirectRepaymentField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-还券划转响应
	* @param pData:指针若非空,返回用户还券划转响应信息结构地址,表明客户还券划转请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户还券划转请求失败
	*/
	virtual void OnRspFASLRepayStockTransfer(DFITCFASLRspRepayStockTransferField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-信用交易响应
	* @param pData:指针若非空,返回用户信用交易响应信息结构地址,表明客户信用交易请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用交易请求失败
	*/
	virtual void OnRspFASLEntrustCrdtOrder(DFITCFASLRspEntrustCrdtOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-融资融券交易响应
	* @param pData:指针若非空,返回用户融资融券交易响应信息结构地址,表明客户融资融券交易请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券交易请求失败
	*/
	virtual void OnRspFASLEntrustOrder(DFITCFASLRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-信用可委托数量查询响应
	* @param pData:指针若非空,返回用户信用可委托数量查询响应信息结构地址,表明客户信用可委托数量查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用可委托数量查询请求失败
	*/
	virtual void OnRspFASLCalcAbleEntrustCrdtQty(DFITCFASLRspCalcAbleEntrustCrdtQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-查询信用资金响应
	* @param pData:指针若非空,返回用户查询信用资金响应信息结构地址,表明客户查询信用资金请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询信用资金请求失败
	*/
	virtual void OnRspFASLQryCrdtFunds(DFITCFASLRspQryCrdtFundsField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-信用合约信息响应
	* @param pData:指针若非空,返回用户信用合约信息响应信息结构地址,表明客户信用合约信息请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用合约信息请求失败
	*/
	virtual void OnRspFASLQryCrdtContract(DFITCFASLRspQryCrdtContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLat) ;
	/**
	* FASL-信用合约变动信息查询响应
	* @param pData:指针若非空,返回用户信用合约变动信息查询响应信息结构地址,表明客户信用合约变动信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用合约变动信息查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryCrdtConChangeInfo(DFITCFASLRspQryCrdtConChangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-资金调转响应
	* @param pData:指针若非空,返回用户资金调转响应信息结构地址,表明客户资金调转请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金调转请求失败
	*/
	virtual void OnRspFASLTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-客户信息查询响应
	* @param pData:指针若非空,返回用户客户信息查询响应信息结构地址,表明客户客户信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户信息查询请求失败
	*/
	virtual void OnRspFASLQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-客户资金查询响应
	* @param pData:指针若非空,返回用户客户资金查询响应信息结构地址,表明客户客户资金查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户资金查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-股东信息查询响应
	* @param pData:指针若非空,返回用户股东信息查询响应信息结构地址,表明客户股东信息查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户股东信息查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-持仓查询响应
	* @param pData:指针若非空,返回用户持仓查询响应信息结构地址,表明客户持仓查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户持仓查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-委托查询响应
	* @param pData:指针若非空,返回用户委托查询响应信息结构地址,表明客户委托查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户委托查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryEntrustOrder(DFITCStockRspQryEntrustOrderField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-分笔成交查询响应
	* @param pData:指针若非空,返回用户分笔成交查询响应信息结构地址,表明客户分笔成交查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户分笔成交查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQrySerialTrade(DFITCStockRspQrySerialTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-实时成交查询响应
	* @param pData:指针若非空,返回用户实时成交查询响应信息结构地址,表明客户实时成交查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户实时成交查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-资金冻结明细查询响应
	* @param pData:指针若非空,返回用户资金冻结明细查询响应信息结构地址,表明客户资金冻结明细查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金冻结明细查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-证券冻结明细查询响应
	* @param pData:指针若非空,返回用户证券冻结明细查询响应信息结构地址,表明客户证券冻结明细查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户证券冻结明细查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-资金调拨明细查询响应
	* @param pData:指针若非空,返回用户资金调拨明细查询响应信息结构地址,表明客户资金调拨明细查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金调拨明细查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-撤单响应
	* @param pData:指针若非空,返回用户撤单响应信息结构地址,表明撤单请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明撤单请求失败
	*/
	virtual void OnRspFASLWithdrawOrder(DFITCFASLRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-当前系统时间查询请求响应
	* @param pData:指针若非空,返回用户系统时间查询响应信息结构地址,表明系统时间查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明系统时间查询请求失败
	*/
	virtual void OnRspFASLQrySystemTime(DFITCFASLRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-可转入担保证券查询请求响应
	* @param pData:指针若非空,返回可转入担保证券查询响应信息结构地址,表明可转入担保证券查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明可转入担保证券查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryTransferredContract(DFITCFASLRspQryTransferredContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-客户可取资金调出请求响应
	* @param pData:指针若非空,返回客户可取资金调出响应信息结构地址,表明客户可取资金调出请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明客户可取资金调出请求失败
	*/
	virtual void OnRspFASLDesirableFundsOut(DFITCFASLRspDesirableFundsOutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-担保证券查询请求响应
	* @param pData:指针若非空,返回担保证券查询响应信息结构地址,表明担保证券查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明担保证券查询请求失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryGuaranteedContract(DFITCFASLRspQryGuaranteedContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-标的证券查询请求响应
	* @param pData:指针若非空,返回标的证券查询响应信息结构地址,表明标的证券查询请求成功
	* @param pRspInfo:指针若非空，返回错误信息地址，表明标的证券查询失败
	* @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
	*/
	virtual void OnRspFASLQryUnderlyingContract(DFITCFASLRspQryUnderlyingContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-委托回报响应
	* @param pData:返回委托回报结构体的地址
	*/
	virtual void OnFASLEntrustOrderRtn(DFITCStockEntrustOrderRtnField *pData);
	/**
	* FASL-成交回报响应
	* @param pData:返回成交回报结构体的地址
	*/
	virtual void OnFASLTradeRtn(DFITCStockTradeRtnField *pData);
	/**
	* FASL-撤单回报响应
	* @param pData:返回撤单回报结构体的地址
	*/
	virtual void OnFASLWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField *pData);

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

	void processRspStockUserPasswordUpdate(Task *task);

	void processRspStockEntrustOrder(Task *task);

	void processRspStockWithdrawOrder(Task *task);

	void processRspStockQryEntrustOrder(Task *task);

	void processRspStockQryRealTimeTrade(Task *task);

	void processRspStockQrySerialTrade(Task *task);

	void processRspStockQryPosition(Task *task);

	void processRspStockQryCapitalAccountInfo(Task *task);

	void processRspStockQryAccountInfo(Task *task);

	void processRspStockQryShareholderInfo(Task *task);

	void processRspStockTransferFunds(Task *task);

	void processRspStockEntrustBatchOrder(Task *task);

	void processRspStockWithdrawBatchOrder(Task *task);

	void processRspStockCalcAbleEntrustQty(Task *task);

	void processRspStockCalcAblePurchaseETFQty(Task *task);

	void processRspStockQryFreezeFundsDetail(Task *task);

	void processRspStockQryFreezeStockDetail(Task *task);

	void processRspStockQryTransferStockDetail(Task *task);

	void processRspStockQryTransferFundsDetail(Task *task);

	void processRspStockQryStockInfo(Task *task);

	void processRspStockQryStockStaticInfo(Task *task);

	void processRspStockQryTradeTime(Task *task);

	void processStockEntrustOrderRtn(Task *task);

	void processStockTradeRtn(Task *task);

	void processStockWithdrawOrderRtn(Task *task);

	void processRspSOPUserLogin(Task *task);

	void processRspSOPUserLogout(Task *task);

	void processRspSOPUserPasswordUpdate(Task *task);

	void processRspSOPEntrustOrder(Task *task);

	void processRspSOPGroupSplit(Task *task);

	void processRspSOPQryGroupPosition(Task *task);

	void processRspSOPLockOUnLockStock(Task *task);

	void processRspSOPWithdrawOrder(Task *task);

	void processRspSOPQryEntrustOrder(Task *task);

	void processRspSOPQrySerialTrade(Task *task);

	void processRspSOPQryPosition(Task *task);

	void processRspSOPQryCollateralPosition(Task *task);

	void processRspSOPQryCapitalAccountInfo(Task *task);

	void processRspSOPQryAccountInfo(Task *task);

	void processRspSOPQryShareholderInfo(Task *task);

	void processRspSOPCalcAbleEntrustQty(Task *task);

	void processRspSOPQryAbleLockStock(Task *task);

	void processRspSOPQryContactInfo(Task *task);

	void processRspSOPExectueOrder(Task *task);

	void processRspSOPQryExecAssiInfo(Task *task);

	void processRspSOPQryTradeTime(Task *task);

	void processRspSOPQryExchangeInfo(Task *task);

	void processRspSOPQryCommission(Task *task);

	void processRspSOPQryDeposit(Task *task);

	void processRspSOPQryContractObjectInfo(Task *task);

	void processSOPEntrustOrderRtn(Task *task);

	void processSOPTradeRtn(Task *task);

	void processSOPWithdrawOrderRtn(Task *task);

	void processRspFASLUserLogin(Task *task);

	void processRspFASLUserLogout(Task *task);

	void processRspFASLQryAbleFinInfo(Task *task);

	void processRspFASLQryAbleSloInfo(Task *task);

	void processRspFASLTransferCollateral(Task *task);

	void processRspFASLDirectRepayment(Task *task);

	void processRspFASLRepayStockTransfer(Task *task);

	void processRspFASLEntrustCrdtOrder(Task *task);

	void processRspFASLEntrustOrder(Task *task);

	void processRspFASLCalcAbleEntrustCrdtQty(Task *task);

	void processRspFASLQryCrdtFunds(Task *task);

	void processRspFASLQryCrdtContract(Task *task);

	void processRspFASLQryCrdtConChangeInfo(Task *task);

	void processRspFASLTransferFunds(Task *task);

	void processRspFASLQryAccountInfo(Task *task);

	void processRspFASLQryCapitalAccountInfo(Task *task);

	void processRspFASLQryShareholderInfo(Task *task);

	void processRspFASLQryPosition(Task *task);

	void processRspFASLQryEntrustOrder(Task *task);

	void processRspFASLQrySerialTrade(Task *task);

	void processRspFASLQryRealTimeTrade(Task *task);

	void processRspFASLQryFreezeFundsDetail(Task *task);

	void processRspFASLQryFreezeStockDetail(Task *task);

	void processRspFASLQryTransferFundsDetail(Task *task);

	void processRspFASLWithdrawOrder(Task *task);

	void processRspFASLQrySystemTime(Task *task);

	void processRspFASLQryTransferredContract(Task *task);

	void processRspFASLDesirableFundsOut(Task *task);

	void processRspFASLQryGuaranteedContract(Task *task);

	void processRspFASLQryUnderlyingContract(Task *task);

	void processFASLEntrustOrderRtn(Task *task);

	void processFASLTradeRtn(Task *task);

	void processFASLWithdrawOrderRtn(Task *task);

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

	virtual void onRspStockUserPasswordUpdate(dict data, dict error){};

	virtual void onRspStockEntrustOrder(dict data, dict error){};

	virtual void onRspStockWithdrawOrder(dict data, dict error){};

	virtual void onRspStockQryEntrustOrder(dict data, dict error, bool flag){};

	virtual void onRspStockQryRealTimeTrade(dict data, dict error, bool flag){};

	virtual void onRspStockQrySerialTrade(dict data, dict error, bool flag){};

	virtual void onRspStockQryPosition(dict data, dict error, bool flag){};

	virtual void onRspStockQryCapitalAccountInfo(dict data, dict error, bool flag){};

	virtual void onRspStockQryAccountInfo(dict data, dict error){};

	virtual void onRspStockQryShareholderInfo(dict data, dict error, bool flag){};

	virtual void onRspStockTransferFunds(dict data, dict error){};

	virtual void onRspStockEntrustBatchOrder(dict data, dict error){};

	virtual void onRspStockWithdrawBatchOrder(dict data, dict error){};

	virtual void onRspStockCalcAbleEntrustQty(dict data, dict error){};

	virtual void onRspStockCalcAblePurchaseETFQty(dict data, dict error){};

	virtual void onRspStockQryFreezeFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryFreezeStockDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryTransferStockDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryTransferFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryStockInfo(dict data, dict error, bool flag){};

	virtual void onRspStockQryStockStaticInfo(dict data, dict error, bool flag){};

	virtual void onRspStockQryTradeTime(dict data, dict error){};

	virtual void onStockEntrustOrderRtn(dict data){};

	virtual void onStockTradeRtn(dict data){};

	virtual void onStockWithdrawOrderRtn(dict data){};

	virtual void onRspSOPUserLogin(dict data, dict error){};

	virtual void onRspSOPUserLogout(dict data, dict error){};

	virtual void onRspSOPUserPasswordUpdate(dict data, dict error){};

	virtual void onRspSOPEntrustOrder(dict data, dict error){};

	virtual void onRspSOPGroupSplit(dict data, dict error){};

	virtual void onRspSOPQryGroupPosition(dict data, dict error, bool flag){};

	virtual void onRspSOPLockOUnLockStock(dict data, dict error, bool flag){};

	virtual void onRspSOPWithdrawOrder(dict data, dict error){};

	virtual void onRspSOPQryEntrustOrder(dict data, dict error, bool flag){};

	virtual void onRspSOPQrySerialTrade(dict data, dict error, bool flag){};

	virtual void onRspSOPQryPosition(dict data, dict error, bool flag){};

	virtual void onRspSOPQryCollateralPosition(dict data, dict error, bool flag){};

	virtual void onRspSOPQryCapitalAccountInfo(dict data, dict error){};

	virtual void onRspSOPQryAccountInfo(dict data, dict error){};

	virtual void onRspSOPQryShareholderInfo(dict data, dict error){};

	virtual void onRspSOPCalcAbleEntrustQty(dict data, dict error){};

	virtual void onRspSOPQryAbleLockStock(dict data, dict error, bool flag){};

	virtual void onRspSOPQryContactInfo(dict data, dict error, bool flag){};

	virtual void onRspSOPExectueOrder(dict data, dict error){};

	virtual void onRspSOPQryExecAssiInfo(dict data, dict error, bool flag){};

	virtual void onRspSOPQryTradeTime(dict data, dict error, bool flag){};

	virtual void onRspSOPQryExchangeInfo(dict data, dict error, bool flag){};

	virtual void onRspSOPQryCommission(dict data, dict error, bool flag){};

	virtual void onRspSOPQryDeposit(dict data, dict error, bool flag){};

	virtual void onRspSOPQryContractObjectInfo(dict data, dict error, bool flag){};

	virtual void onSOPEntrustOrderRtn(dict data){};

	virtual void onSOPTradeRtn(dict data){};

	virtual void onSOPWithdrawOrderRtn(dict data){};

	virtual void onRspFASLUserLogin(dict data, dict error){};

	virtual void onRspFASLUserLogout(dict data, dict error){};

	virtual void onRspFASLQryAbleFinInfo(dict data, dict error){};

	virtual void onRspFASLQryAbleSloInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLTransferCollateral(dict data, dict error){};

	virtual void onRspFASLDirectRepayment(dict data, dict error){};

	virtual void onRspFASLRepayStockTransfer(dict data, dict error){};

	virtual void onRspFASLEntrustCrdtOrder(dict data, dict error){};

	virtual void onRspFASLEntrustOrder(dict data, dict error){};

	virtual void onRspFASLCalcAbleEntrustCrdtQty(dict data, dict error){};

	virtual void onRspFASLQryCrdtFunds(dict data, dict error){};

	virtual void onRspFASLQryCrdtContract(dict data, dict error, bool flag){};

	virtual void onRspFASLQryCrdtConChangeInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLTransferFunds(dict data, dict error){};

	virtual void onRspFASLQryAccountInfo(dict data, dict error){};

	virtual void onRspFASLQryCapitalAccountInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLQryShareholderInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLQryPosition(dict data, dict error, bool flag){};

	virtual void onRspFASLQryEntrustOrder(dict data, dict error, bool flag){};

	virtual void onRspFASLQrySerialTrade(dict data, dict error, bool flag){};

	virtual void onRspFASLQryRealTimeTrade(dict data, dict error, bool flag){};

	virtual void onRspFASLQryFreezeFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspFASLQryFreezeStockDetail(dict data, dict error, bool flag){};

	virtual void onRspFASLQryTransferFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspFASLWithdrawOrder(dict data, dict error){};

	virtual void onRspFASLQrySystemTime(dict data, dict error){};

	virtual void onRspFASLQryTransferredContract(dict data, dict error, bool flag){};

	virtual void onRspFASLDesirableFundsOut(dict data, dict error){};

	virtual void onRspFASLQryGuaranteedContract(dict data, dict error, bool flag){};

	virtual void onRspFASLQryUnderlyingContract(dict data, dict error, bool flag){};

	virtual void onFASLEntrustOrderRtn(dict data){};

	virtual void onFASLTradeRtn(dict data){};

	virtual void onFASLWithdrawOrderRtn(dict data){};


	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createDFITCSECTraderApi(string logAddr);

	void init(string svrAddr);

	void release();

	int exit();

	int subscribePrivateTopic(int type);

	int reqStockUserLogin(dict req);

	int reqStockUserLogout(dict req);

	int reqStockUserPasswordUpdate(dict req);

	int reqStockEntrustOrder(dict req);

	int reqStockWithdrawOrder(dict req);

	int reqStockQryEntrustOrder(dict req);

	int reqStockQryRealTimeTrade(dict req);

	int reqStockQrySerialTrade(dict req);

	int reqStockQryPosition(dict req);

	int reqStockQryCapitalAccountInfo(dict req);

	int reqStockQryAccountInfo(dict req);

	int reqStockQryShareholderInfo(dict req);

	int reqStockTransferFunds(dict req);

	int reqStockEntrustBatchOrder(dict req);

	int reqStockWithdrawBatchOrder(dict req);

	int reqStockCalcAbleEntrustQty(dict req);

	int reqStockCalcAblePurchaseETFQty(dict req);

	int reqStockQryFreezeFundsDetail(dict req);

	int reqStockQryFreezeStockDetail(dict req);

	int reqStockQryTransferFundsDetail(dict req);

	int reqStockQryTransferStockDetail(dict req);

	int reqStockQryStockInfo(dict req);

	int reqStockQryStockStaticInfo(dict req);

	int reqStockQryTradeTime(dict req);

	int reqSOPUserLogin(dict req);

	int reqSOPUserLogout(dict req);

	int reqSOPUserPasswordUpdate(dict req);

	int reqSOPEntrustOrder(dict req);

	int reqSOPGroupSplit(dict req);

	int reqSOPQryGroupPosition(dict req);

	int reqSOPLockOUnLockStock(dict req);

	int reqSOPWithdrawOrder(dict req);

	int reqSOPQryEntrustOrder(dict req);

	int reqSOPQrySerialTrade(dict req);

	int reqSOPQryPosition(dict req);

	int reqSOPQryCollateralPosition(dict req);

	int reqSOPQryCapitalAccountInfo(dict req);

	int reqSOPQryAccountInfo(dict req);

	int reqSOPQryShareholderInfo(dict req);

	int reqSOPCalcAbleEntrustQty(dict req);

	int reqSOPQryAbleLockStock(dict req);

	int reqSOPQryContactInfo(dict req);

	int reqSOPExectueOrder(dict req);

	int reqSOPQryExecAssiInfo(dict req);

	int reqSOPQryTradeTime(dict req);

	int reqSOPQryExchangeInfo(dict req);

	int reqSOPQryCommission(dict req);

	int reqSOPQryDeposit(dict req);

	int reqSOPQryContractObjectInfo(dict req);

	int reqFASLUserLogin(dict req);

	int reqFASLUserLogout(dict req);

	int reqFASLQryAbleFinInfo(dict req);

	int reqFASLQryAbleSloInfo(dict req);

	int reqFASLTransferCollateral(dict req);

	int reqFASLDirectRepayment(dict req);

	int reqFASLRepayStockTransfer(dict req);

	int reqFASLEntrustCrdtOrder(dict req);

	int reqFASLEntrsuctOrder(dict req);

	int reqFASLWithdrawOrder(dict req);

	int reqFASLCalcAbleEntrustCrdtQty(dict req);

	int reqFASLQryCrdtFunds(dict req);

	int reqFASLQryCrdtContract(dict req);

	int reqFASLQryCrdtConChangeInfo(dict req);

	int reqFASLTransferFunds(dict req);

	int reqFASLQryAccountInfo(dict req);

	int reqFASLQryCapitalAccountInfo(dict req);

	int reqFASLQryShareholderInfo(dict req);

	int reqFASLQryPosition(dict req);

	int reqFASLQryEntrustOrder(dict req);

	int reqFASLQrySerialTrade(dict req);

	int reqFASLQryRealTimeTrade(dict req);

	int reqFASLQryFreezeFundsDetail(dict req);

	int reqFASLQryFreezeStockDetail(dict req);

	int reqFASLQryTransferFundsDetail(dict req);

	int reqFASLQrySystemTime(dict req);

	int reqFASLQryTransferredContract(dict req);

	int reqFASLDesirableFundsOut(dict req);

	int reqFASLQryGuaranteedContract(dict req);

	int reqFASLQryUnderlyingContract(dict req);
};
