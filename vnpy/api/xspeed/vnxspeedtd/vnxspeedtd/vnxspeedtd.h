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
#include "DFITCTraderApi.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;
using namespace DFITCXSPEEDAPI;

//常量
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERLOGOUT 4
#define ONRSPINSERTORDER 5
#define ONRSPCANCELORDER 6
#define ONRTNERRORMSG 7
#define ONRTNMATCHEDINFO 8
#define ONRTNORDER 9
#define ONRTNCANCELORDER 10
#define ONRSPQRYORDERINFO 11
#define ONRSPQRYMATCHINFO 12
#define ONRSPQRYPOSITION 13
#define ONRSPCUSTOMERCAPITAL 14
#define ONRSPQRYEXCHANGEINSTRUMENT 15
#define ONRSPARBITRAGEINSTRUMENT 16
#define ONRSPQRYSPECIFYINSTRUMENT 17
#define ONRSPQRYPOSITIONDETAIL 18
#define ONRTNTRADINGNOTICE 19
#define ONRSPRESETPASSWORD 20
#define ONRSPQRYTRADECODE 21
#define ONRSPBILLCONFIRM 22
#define ONRSPEQUITYCOMPUTMODE 23
#define ONRSPQRYBILL 24
#define ONRSPCONFIRMPRODUCTINFO 25
#define ONRSPTRADINGDAY 26
#define ONRSPQUOTEINSERT 27
#define ONRTNQUOTEINSERT 28
#define ONRSPQUOTECANCEL 29
#define ONRTNQUOTECANCEL 30
#define ONRTNQUOTEMATCHEDINFO 31
#define ONRSPCANCELALLORDER 32
#define ONRSPQRYQUOTENOTICE 33
#define ONRSPFORQUOTE 34
#define ONRTNFORQUOTE 35
#define ONRSPQRYQUOTEORDERINFO 36
#define ONRSPQRYFORQUOTE 37
#define ONRSPQRYTRANSFERBANK 38
#define ONRSPQRYTRANSFERSERIAL 39
#define ONRSPFROMBANKTOFUTUREBYFUTURE 40
#define ONRSPFROMFUTURETOBANKBYFUTURE 41
#define ONRTNFROMBANKTOFUTUREBYFUTURE 42
#define ONRTNFROMFUTURETOBANKBYFUTURE 43
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 44
#define ONRSPQRYEXCHANGESTATUS 45
#define ONRTNEXCHANGESTATUS 46
#define ONRSPQRYDEPTHMARKETDATA 47

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

//从字典中获取某个建值对应的长整数，并赋值到请求结构体对象的值上
void getLong(dict d, string key, long* value);

//从字典中获取某个建值对应的短整数，并赋值到请求结构体对象的值上
void getShort(dict d, string key, short* value);


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
class TdApi : public DFITCTraderSpi
{
private:
	DFITCTraderApi* api;			//API对象
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

	/* 网络连接正常响应:当客户端与交易后台需建立起通信连接时（还未登录前），客户端API会自动检测与前置机之间的连接，
	* 当网络可用，将自动建立连接，并调用该方法通知客户端， 客户端可以在实现该方法时，重新使用资金账号进行登录。
	*（该方法是在Api和前置机建立连接后被调用，该调用仅仅是说明tcp连接已经建立成功。用户需要自行登录才能进行后续的业务操作。
	*  登录失败则此方法不会被调用。）
	*/
	virtual void OnFrontConnected();

	/**
	* 网络连接不正常响应：当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	* @param  nReason:错误原因。
	*        0x1001 网络读失败
	*        0x1002 网络写失败
	*        0x2001 接收心跳超时
	*        0x2002 发送心跳失败
	*        0x2003 收到错误报文
	*/
	virtual void OnFrontDisconnected(int nReason);
	/**
	* 登陆请求响应:当用户发出登录请求后，前置机返回响应时此方法会被调用，通知用户登录是否成功。
	* @param pUserLoginInfoRtn:用户登录信息结构地址。
	* @param pErrorInfo:若登录失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pUserLoginInfoRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 登出请求响应:当用户发出退出请求后，前置机返回响应此方法会被调用，通知用户退出状态。
	* @param pUserLogoutInfoRtn:返回用户退出信息结构地址。
	* @param pErrorInfo:若登出失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 期货委托报单响应:当用户录入报单后，前置返回响应时该方法会被调用。
	* @param pOrderRtn:返回用户下单信息结构地址。
	* @param pErrorInfo:若报单失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 期货委托撤单响应:当用户撤单后，前置返回响应是该方法会被调用。
	* @param pOrderCanceledRtn:返回撤单响应信息结构地址。
	* @param pErrorInfo:若撤单失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspCancelOrder(struct DFITCOrderRspDataRtnField * pOrderCanceledRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 错误回报
	* @param pErrorInfo:错误信息的结构地址。
	*/
	virtual void OnRtnErrorMsg(struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 成交回报:当委托成功交易后次方法会被调用。
	* @param pRtnMatchData:指向成交回报的结构的指针。
	*/
	virtual void OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData);

	/**
	* 委托回报:下单委托成功后，此方法会被调用。
	* @param pRtnOrderData:指向委托回报地址的指针。
	*/
	virtual void OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData);

	/**
	* 撤单回报:当撤单成功后该方法会被调用。
	* @param pCancelOrderData:指向撤单回报结构的地址，该结构体包含被撤单合约的相关信息。
	*/
	virtual void OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData);

	/**
	* 查询当日委托响应:当用户发出委托查询后，该方法会被调用。
	* @param pRtnOrderData:指向委托回报结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 查询当日成交响应:当用户发出成交查询后该方法会被调用。
	* @param pRtnMatchData:指向成交回报结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 持仓查询响应:当用户发出持仓查询指令后，前置返回响应时该方法会被调用。
	* @param pPositionInfoRtn:返回持仓信息结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 客户资金查询响应:当用户发出资金查询指令后，前置返回响应时该方法会被调用。
	* @param pCapitalInfoRtn:返回资金信息结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 交易所合约查询响应:当用户发出合约查询指令后，前置返回响应时该方法会被调用。
	* @param pInstrumentData:返回合约信息结构的地址。
	* @param pErrorInfo:错误信息结构，如果查询发生错误，则返回错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 套利合约查询响应:当用户发出套利合约查询指令后，前置返回响应时该方法会被调用。
	* @param pAbiInstrumentData:返回套利合约信息结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 查询指定合约响应:当用户发出指定合约查询指令后，前置返回响应时该方法会被调用。
	* @param pInstrument:返回指定合约信息结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 查询持仓明细响应:当用户发出查询持仓明细后，前置返回响应时该方法会被调用。
	* @param pPositionDetailRtn:返回持仓明细结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 交易通知响应:用于接收XSPEED柜台手动发送通知，即支持指定客户，也支持系统广播。
	* @param pTradingNoticeInfo: 返回用户事件通知结构的地址。
	*/
	virtual void OnRtnTradingNotice(struct DFITCTradingNoticeInfoField * pTradingNoticeInfo);

	/**
	* 密码修改响应:用于修改资金账户登录密码。
	* @param pResetPassword: 返回密码修改结构的地址。
	* @param pErrorInfo:若修改密码失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 交易编码查询响应:返回交易编码信息
	* @param pTradeCode: 返回交易编码查询结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 账单确认响应:用于接收客户账单确认状态。
	* @param pBillConfirm: 返回账单确认结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 查询客户权益计算方式响应:返回客户权益计算的方式
	* @param pEquityComputMode: 返回客户权益计算方式结构的地址。
	*/
	virtual void OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode);

	/**
	* 客户结算账单查询响应:返回账单信息
	* @param pQryBill: 返回客户结算账单查询结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryBill(struct DFITCQryBillRtnField *pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 厂商ID确认响应:用于接收厂商信息。
	* @param pProductRtnData: 返回厂商ID确认响应结构的地址。
	*/
	virtual void OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData);


	/**
	* 交易日确认响应:用于接收交易日信息。
	* @param DFITCTradingDayRtnField: 返回交易日请求确认响应结构的地址。
	*/
	virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData);

	/**
	* 做市商报单响应
	* @param pRspQuoteData:指向做市商报单响应地址的指针。
	* @param pErrorInfo:若报价失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspQuoteInsert(struct DFITCQuoteRspField * pRspQuoteData, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* 做市商报单回报
	* @param pRtnQuoteData:指向做市商报单回报地址的指针。
	*/
	virtual void OnRtnQuoteInsert(struct DFITCQuoteRtnField * pRtnQuoteData);

	/**
	* 做市商撤单响应
	* @param pRspQuoteCanceledData:指向做市商撤单响应地址的指针。
	* @param pErrorInfo:若撤单失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspQuoteCancel(struct DFITCQuoteRspField * pRspQuoteCanceledData, struct DFITCErrorRtnField * pErrorInfo)  ;

	/**
	* 做市商撤单回报
	* @param pRtnQuoteCanceledData:指向做市商撤单回报地址的指针。
	*/
	virtual void OnRtnQuoteCancel(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData) ;

	/**
	* 做市商成交回报
	* @param pRtnQuoteMatchedData:指向做市商成交回报地址的指针。
	*/
	virtual void OnRtnQuoteMatchedInfo(struct DFITCQuoteMatchRtnField * pRtnQuoteMatchedData) ;

	/**
	* 批量撤单响应
	* @param pRspStripCancelOrderData:指向批量撤单响应地址的指针。
	* @param pErrorInfo:若批量撤单失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspCancelAllOrder(struct DFITCCancelAllOrderRspField *pRspCancelAllOrderData, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 询价通知查询响应
	* @param pRtnQryQuoteNoticeData:查询询价通知回报结构地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryQuoteNotice(struct DFITCQryQuoteNoticeRtnField * pRtnQryQuoteNoticeData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 询价响应
	* @param pRspForQuoteData:询价请求响应结构地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspForQuote(struct DFITCForQuoteRspField * pRspForQuoteData, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* 询价回报
	* @param pRtnForQuoteData:询价回报结构地址。
	*/
	virtual void OnRtnForQuote(struct DFITCForQuoteRtnField * pRtnForQuoteData);

	/**
	* 查询当日报价委托响应
	* @param pRtnQuoteOrderData:指向报价查询回报结构的地址。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryQuoteOrderInfo(struct DFITCQuoteOrderRtnField * pRtnQuoteOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 询价委托查询响应
	* @param pRtnQryForQuoteData:指向询价委托查询响应地址的指针。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryForQuote(struct DFITCQryForQuoteRtnField * pRtnQryForQuoteData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* 查询转帐银行响应
	* @param pTransferBank:指向查询转帐银行回报地址的指针。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryTransferBank(struct DFITCTransferBankRspField * pTransferBank, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) ;

	/**
	* 查询转帐流水响应
	* @param pTransferSerial:指向查询转帐流水回报地址的指针。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryTransferSerial(struct DFITCTransferSerialRspField * pTransferSerial, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) ;

	/**
	* 期货发起银行资金转期货应答
	* @param pRspTransfer:指向期货发起银行资金转期货应答地址的指针。
	* @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspFromBankToFutureByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* 期货发起期货资金转银行应答
	* @param pRspTransfer:指向期货发起期货资金转银行应答地址的指针。
	* @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRspFromFutureToBankByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* 期货发起银行资金转期货通知
	* @param pRtnTransfer:指向期货发起银行资金转期货通知地址的指针。
	* @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRtnFromBankToFutureByFuture(DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* 期货发起期货资金转银行通知
	* @param pRtnTransfer:指向期货发起期货资金转银行通知地址的指针。
	* @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
	*/
	virtual void OnRtnFromFutureToBankByFuture(DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* 银行发起冲正期货转银行通知
	* @param pRspRepeal:指向期货发起期货资金转银行冲正通知地址的指针。
	*/
	virtual void OnRtnRepealFromFutureToBankByBank(DFITCRepealRtnField * pRspRepeal) ;

	/**
	* 交易所状态查询响应
	* @param pRspExchangeStatusData:指向交易所状态查询响应地址的指针。
	*/
	virtual void OnRspQryExchangeStatus(struct DFITCExchangeStatusRspField * pRspExchangeStatusData);

	/**
	* 交易所状态通知
	* @param pRtnExchangeStatusData:指向交易所状态通知地址的指针。
	*/
	virtual void OnRtnExchangeStatus(struct DFITCExchangeStatusRtnField * pRtnExchangeStatusData);

	/**
	* 行情查询响应
	* @param pDepthMarketData:指向行情查询响应地址的指针。
	* @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
	* @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
	*/
	virtual void OnRspQryDepthMarketData(struct DFITCDepthMarketDataField * pDepthMarketData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspInsertOrder(Task task);

	void processRspCancelOrder(Task task);

	void processRtnErrorMsg(Task task);

	void processRtnMatchedInfo(Task task);

	void processRtnOrder(Task task);

	void processRtnCancelOrder(Task task);

	void processRspQryOrderInfo(Task task);

	void processRspQryMatchInfo(Task task);

	void processRspQryPosition(Task task);

	void processRspCustomerCapital(Task task);

	void processRspQryExchangeInstrument(Task task);

	void processRspArbitrageInstrument(Task task);

	void processRspQrySpecifyInstrument(Task task);

	void processRspQryPositionDetail(Task task);

	void processRtnTradingNotice(Task task);

	void processRspResetPassword(Task task);

	void processnRspQryTradeCode(Task task);

	void processRspBillConfirm(Task task);

	void processnRspEquityComputMode(Task task);

	void processRspQryBill(Task task);

	void processRspConfirmProductInfo(Task task);

	void processRspTradingDay(Task task);

	void processRspQuoteInsert(Task task);

	void processRtnQuoteInsert(Task task);

	void processRspQuoteCancel(Task task);

	void processRtnQuoteCancel(Task task);

	void processRtnQuoteMatchedInfo(Task task);

	void processRspCancelAllOrder(Task task);

	void processRspQryQuoteNotice(Task task);

	void processRspForQuote(Task task);

	void processRtnForQuote(Task task);

	void processRspQryQuoteOrderInfo(Task task);

	void processRspQryForQuote(Task task);

	void processRspQryTransferBank(Task task);

	void processRspQryTransferSerial(Task task);

	void processRspFromBankToFutureByFuture(Task task);

	void processRspFromFutureToBankByFuture(Task task);

	void processRtnFromBankToFutureByFuture(Task task);

	void processRtnFromFutureToBankByFuture(Task task);

	void processRtnRepealFromFutureToBankByBank(Task task);

	void processRspQryExchangeStatus(Task task);

	void processRtnExchangeStatus(Task task);

	void processRspQryDepthMarketData(Task task);

	void processRspQryTradeCode(Task task);

	void processRspEquityComputMode(Task task);

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

	virtual void onRspInsertOrder(dict data, dict error) {};

	virtual void onRspCancelOrder(dict data, dict error) {};

	virtual void onRtnErrorMsg(dict data) {};

	virtual void onRtnMatchedInfo(dict data) {};

	virtual void onRtnOrder(dict data) {};

	virtual void onRtnCancelOrder(dict data) {};

	virtual void onRspQryOrderInfo(dict data, dict error, bool last) {};

	virtual void onRspQryMatchInfo(dict data, dict error, bool last) {};

	virtual void onRspQryPosition(dict data, dict error, bool last) {};

	virtual void onRspCustomerCapital(dict data, dict error, bool last) {};

	virtual void onRspQryExchangeInstrument(dict data, dict error, bool last) {};

	virtual void onRspArbitrageInstrument(dict data, dict error, bool last) {};

	virtual void onRspQrySpecifyInstrument(dict data, dict error, bool last) {};

	virtual void onRspQryPositionDetail(dict data, dict error, bool last) {};

	virtual void onRtnTradingNotice(dict data) {};

	virtual void onRspResetPassword(dict data, dict error) {};

	virtual void onnRspQryTradeCode(dict data, dict error, bool last) {};

	virtual void onRspBillConfirm(dict data, dict error) {};

	virtual void onnRspEquityComputMode(dict data, dict error) {};

	virtual void onRspQryBill(dict data, dict error, bool last) {};

	virtual void onRspConfirmProductInfo(dict data, dict error) {};

	virtual void onRspTradingDay(dict data, dict error) {};

	virtual void onRspQuoteInsert(dict data, dict error) {};

	virtual void onRtnQuoteInsert(dict data) {};

	virtual void onRspQuoteCancel(dict data, dict error) {};

	virtual void onRtnQuoteCancel(dict data) {};

	virtual void onRtnQuoteMatchedInfo(dict data) {};

	virtual void onRspCancelAllOrder(dict data, dict error) {};

	virtual void onRspQryQuoteNotice(dict data, dict error, bool last) {};

	virtual void onRspForQuote(dict data, dict error) {};

	virtual void onRtnForQuote(dict data) {};

	virtual void onRspQryQuoteOrderInfo(dict data, dict error, bool last) {};

	virtual void onRspQryForQuote(dict data, dict error, bool last) {};

	virtual void onRspQryTransferBank(dict data, dict error, bool last) {};

	virtual void onRspQryTransferSerial(dict data, dict error, bool last) {};

	virtual void onRspFromBankToFutureByFuture(dict data, dict error) {};

	virtual void onRspFromFutureToBankByFuture(dict data, dict error) {};

	virtual void onRtnFromBankToFutureByFuture(dict data, dict error) {};

	virtual void onRtnFromFutureToBankByFuture(dict data, dict error) {};

	virtual void onRtnRepealFromFutureToBankByBank(dict data) {};

	virtual void onRspQryExchangeStatus(dict data, dict error, bool last) {};

	virtual void onRtnExchangeStatus(dict data) {};

	virtual void onRspQryDepthMarketData(dict data, dict error, bool last) {};

	virtual void onRspQryTradeCode(dict data, dict error, bool last) {};

	virtual void onRspEquityComputMode(dict data) {};


	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createDFITCTraderApi();

	void release();

	void init(string pszSvrAddr);

	int exit();

	int reqUserLogin(dict req);

	int reqUserLogout(dict req);

	int reqInsertOrder(dict req);

	int reqCancelOrder(dict req);

	int reqQryPosition(dict req);

	int reqQryCustomerCapital(dict req);

	int reqQryExchangeInstrument(dict req);

	int reqQryArbitrageInstrument(dict req);

	int reqQryOrderInfo(dict req);

	int reqQryMatchInfo(dict req);

	int reqQrySpecifyInstrument(dict req);

	int reqQryPositionDetail(dict req);

	int reqConfirmProductInfo(dict req);

	int reqResetPassword(dict req);

	int reqBillConfirm(dict req);

	int reqQryTradeCode(dict req);

	int reqEquityComputMode();

	int reqQryBill(dict req);

	int reqTradingDay(dict req);

	int reqQryQuoteNotice(dict req);

	int reqQuoteInsert(dict req);

	int reqQuoteCancel(dict req);

	int reqCancelAllOrder(dict req);

	int reqForQuote(dict req);

	int reqQryForQuote(dict req);

	int reqQryQuoteOrderInfo(dict req);

	int reqQryTransferBank(dict req);

	int reqQryTransferSerial(dict req);

	int reqFromBankToFutureByFuture(dict req);

	int reqFromFutureToBankByFuture(dict req);

	int reqQryExchangeStatus(dict req);

	int reqQryDepthMarketData(dict req);
};
