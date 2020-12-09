//系统
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vnnh.h"
#include "pybind11/pybind11.h"
#include "nh/stock/NhStockTraderApi.h"


using namespace pybind11;
using namespace nhtd;


//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONPACKAGESTART 3
#define ONPACKAGEEND 4
#define ONRSPSUBSCRIBETOPIC 5
#define ONRSPUSERLOGIN 6
#define ONRSPUSERLOGOUT 7
#define ONRSPUSERPASSWORDUPDATE 8
#define ONRSPSTOCKINSERT 9
#define ONRSPSTOCKCANCEL 10
#define ONRSPOPTIONSINSERT 11
#define ONRSPOPTIONSCANCEL 12
#define ONRSPQUOTEINSERT 13
#define ONRSPFORQUOTE 14
#define ONRSPQUOTECANCEL 15
#define ONRSPSTOCKLOCK 16
#define ONRSPEXERCISE 17
#define ONRSPEXERCISECANCEL 18
#define ONRSPQRYPARTACCOUNT 19
#define ONRSPQRYSTOCKORDER 20
#define ONRSPQRYOPTIONSORDER 21
#define ONRSPQRYQUOTEORDER 22
#define ONRSPQRYSTOCKTRADE 23
#define ONRSPQRYOPTIONSTRADE 24
#define ONRSPQRYPOSITION 25
#define ONRSPQRYTOPIC 26
#define ONRSPQRYSTOCK 27
#define ONRSPQRYOPTIONS 28
#define ONRTNOPTIONSORDER 29
#define ONRTNSTOCKORDER 30
#define ONRTNQUOTEORDER 31
#define ONRTNOPTIONSTRADE 32
#define ONRTNSTOCKTRADE 33
#define ONRTNEXERCISE 34
#define ONRSPQRYRATE 35
#define ONRSPQRYCLIENT 36
#define ONRSPQRYCLIENTMARGIN 37
#define ONRSPQRYEXERCISE 38
#define ONRTNWITHDRAWDEPOSIT 39
#define ONRSPMARGINCOMBACTION 40
#define ONRTNMARGINCOMBACTION 41
#define ONRSPQRYSSECOMBPOSITION 42
#define ONRSPCOMBEXERCISE 43


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class StockTdApi : public CNhStockTraderSpi
{
private:
	CNhStockTraderApi* api;				//API对象
	thread task_thread;					//工作线程指针（向python中推送数据）
	TaskQueue task_queue;			    //任务队列
	bool active = false;				//工作状态

public:
	StockTdApi()
	{
	};

	~StockTdApi()
	{
		if (this->active)
		{
			this->exit();
		}
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

	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo);

	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo);

	///订阅主题应答
	virtual void OnRspSubscribeTopic(CStockFtdcDisseminationField *pDissemination, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户登录应答
	virtual void OnRspUserLogin(CStockFtdcRspUserLoginField *pRspUserLogin, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户退出应答
	virtual void OnRspUserLogout(CStockFtdcRspUserLogoutField *pRspUserLogout, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CStockFtdcUserPasswordUpdateField *pUserPasswordUpdate, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///股票报单应答
	virtual void OnRspStockInsert(CStockFtdcStockInsertRspField *pStockInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///股票撤单应答
	virtual void OnRspStockCancel(CStockFtdcStockCancelRspField *pStockCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期权报单应答
	virtual void OnRspOptionsInsert(CStockFtdcOptionsInsertRspField *pOptionsInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期权撤单应答
	virtual void OnRspOptionsCancel(CStockFtdcOptionsCancelRspField *pOptionsCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期权报价应答
	virtual void OnRspQuoteInsert(CStockFtdcQuoteInsertRspField *pQuoteInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期权撤销报价应答
	virtual void OnRspForQuote(CStockFtdcForQuoteRspField *pForQuote, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///询价应答
	virtual void OnRspQuoteCancel(CStockFtdcQuoteCancelRspField *pQuoteCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///证券锁定应答
	virtual void OnRspStockLock(CStockFtdcStockLockRspField *pStockLock, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///行权应答
	virtual void OnRspExercise(CStockFtdcExerciseRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///撤销行权应答
	virtual void OnRspExerciseCancel(CStockFtdcExerciseCancelRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///会员资金查询应答
	virtual void OnRspQryPartAccount(CStockFtdcRspPartAccountField *pRspPartAccount, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///股票报单查询应答
	virtual void OnRspQryStockOrder(CStockFtdcRspQryStockOrderField *pOrder, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期权报单查询应答
	virtual void OnRspQryOptionsOrder(CStockFtdcRspQryOptionsOrderField *pOrder, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报价查询应答
	virtual void OnRspQryQuoteOrder(CStockFtdcRspQryQuoteOrderField *pQuote, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///股票成交查询应答
	virtual void OnRspQryStockTrade(CStockFtdcStockTradeField *pTrade, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期权成交查询应答
	virtual void OnRspQryOptionsTrade(CStockFtdcOptionsTradeField *pTrade, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///持仓查询应答
	virtual void OnRspQryPosition(CStockFtdcRspPositionField *pPosition, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///主题查询应答
	virtual void OnRspQryTopic(CStockFtdcDisseminationField *pDissemination, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//股票查询应答
	virtual void OnRspQryStock(CStockFtdcRspQryStockField *pStock, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//期权查询应答
	virtual void OnRspQryOptions(CStockFtdcRspQryOptionsField *pOptions, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期权委托回报
	virtual void OnRtnOptionsOrder(CStockFtdcOptionsOrderField *pOrder);

	///股票委托回报
	virtual void OnRtnStockOrder(CStockFtdcStockOrderField *pOrder);

	///报价回报
	virtual void OnRtnQuoteOrder(CStockFtdcQuoteOrderField *pQuote);

	///期权成交回报
	virtual void OnRtnOptionsTrade(CStockFtdcOptionsTradeField *pTrade);

	///股票成交回报
	virtual void OnRtnStockTrade(CStockFtdcStockTradeField *pTrade);

	///行权回报
	virtual void OnRtnExercise(CStockFtdcExerciseRtnField *pExercise);

	///查询费率信息应答
	virtual void OnRspQryRate(CStockFtdcRspQryRateField *pRate, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///会员客户查询应答
	virtual void OnRspQryClient(CStockFtdcRspClientField *pRspClient, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///客户保证金查询应答
	virtual void OnRspQryClientMargin(CStockFtdcRspQryClientMarginField *pRspMargin, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询行权应答
	virtual void OnRspQryExercise(CStockFtdcExerciseRtnField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///出入金通知
	virtual void OnRtnWithdrawDeposit(CStockFtdcWithdrawDepositRtnField *pWithdrawDeposit);

	///客户申请组合请求
	virtual void OnRspMarginCombAction(CStockFtdcMarginCombActionRspField *pMarginCombAction, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///客户申请组合通知
	virtual void OnRtnMarginCombAction(CStockFtdcMarginCombActionRtnField *pMarginCombAction);

	///上期所组合持仓查询应答
	virtual void OnRspQrySseCombPosition(CStockFtdcCombPositionRspField *pPosi, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///组合行权应答
	virtual void OnRspCombExercise(CStockFtdcCombExerciseRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processHeartBeatWarning(Task *task);

	void processRspSubscribeTopic(Task *task);

	void processRspUserLogin(Task *task);

	void processRspUserLogout(Task *task);

	void processRspUserPasswordUpdate(Task *task);

	void processRspStockInsert(Task *task);

	void processRspStockCancel(Task *task);

	void processRspOptionsInsert(Task *task);

	void processRspOptionsCancel(Task *task);

	void processRspQuoteInsert(Task *task);

	void processRspForQuote(Task *task);

	void processRspQuoteCancel(Task *task);

	void processRspStockLock(Task *task);

	void processRspExercise(Task *task);

	void processRspExerciseCancel(Task *task);

	void processRspQryPartAccount(Task *task);

	void processRspQryStockOrder(Task *task);

	void processRspQryOptionsOrder(Task *task);

	void processRspQryQuoteOrder(Task *task);

	void processRspQryStockTrade(Task *task);

	void processRspQryOptionsTrade(Task *task);

	void processRspQryPosition(Task *task);

	void processRspQryTopic(Task *task);

	void processRspQryStock(Task *task);

	void processRspQryOptions(Task *task);

	void processRtnOptionsOrder(Task *task);

	void processRtnStockOrder(Task *task);

	void processRtnQuoteOrder(Task *task);

	void processRtnOptionsTrade(Task *task);

	void processRtnStockTrade(Task *task);

	void processRtnExercise(Task *task);

	void processRspQryRate(Task *task);

	void processRspQryClient(Task *task);

	void processRspQryClientMargin(Task *task);

	void processRspQryExercise(Task *task);

	void processRtnWithdrawDeposit(Task *task);

	void processRspMarginCombAction(Task *task);

	void processRtnMarginCombAction(Task *task);

	void processRspQrySseCombPosition(Task *task);

	void processRspCombExercise(Task *task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected() {};

	virtual void onFrontDisconnected(int reqid) {};

	virtual void onHeartBeatWarning(int reqid) {};

	virtual void onRspSubscribeTopic(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspStockInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspStockCancel(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspOptionsInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspOptionsCancel(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspForQuote(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQuoteCancel(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspStockLock(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspExercise(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspExerciseCancel(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryPartAccount(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryStockOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryOptionsOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryQuoteOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryStockTrade(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryOptionsTrade(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryTopic(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryStock(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryOptions(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnOptionsOrder(const dict &data) {};

	virtual void onRtnStockOrder(const dict &data) {};

	virtual void onRtnQuoteOrder(const dict &data) {};

	virtual void onRtnOptionsTrade(const dict &data) {};

	virtual void onRtnStockTrade(const dict &data) {};

	virtual void onRtnExercise(const dict &data) {};

	virtual void onRspQryRate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryClient(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryClientMargin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryExercise(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnWithdrawDeposit(const dict &data) {};

	virtual void onRspMarginCombAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnMarginCombAction(const dict &data) {};

	virtual void onRspQrySseCombPosition(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspCombExercise(const dict &data, const dict &error, int reqid, bool last) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createStockTdApi(string flowPath);

	string getVersion();

	void release();

	void init(string localIp, string netWorkCard);

	int exit();

	string getTradingDay();

	void registerFront(string address);

	void subscribePrivateTopic(int type);

	void subscribePublicTopic(int type);

	void subscribeUserTopic(int type);

	int reqSubscribeTopic(const dict &req, int reqid);

	int reqUserLogin(const dict &req, int reqid);

	int reqUserLogout(const dict &req, int reqid);

	int reqUserPasswordUpdate(const dict &req, int reqid);

	int reqStockInsert(const dict &req, int reqid);

	int reqStockCancel(const dict &req, int reqid);

	int reqStockLock(const dict &req, int reqid);

	int reqOptionsInsert(const dict &req, int reqid);

	int reqOptionsCancel(const dict &req, int reqid);

	int reqQuoteInsert(const dict &req, int reqid);

	int reqQuoteCancel(const dict &req, int reqid);

	int reqForQuote(const dict &req, int reqid);

	int reqExercise(const dict &req, int reqid);

	int reqExerciseCancel(const dict &req, int reqid);

	int reqQryPartAccount(const dict &req, int reqid);

	int reqQryStockOrder(const dict &req, int reqid);

	int reqQryOptionsOrder(const dict &req, int reqid);

	int reqQryQuoteOrder(const dict &req, int reqid);

	int reqQryStockTrade(const dict &req, int reqid);

	int reqQryOptionsTrade(const dict &req, int reqid);

	int reqQryPosition(const dict &req, int reqid);

	int reqQryTopic(const dict &req, int reqid);

	int reqQryStock(const dict &req, int reqid);

	int reqQryOptions(const dict &req, int reqid);

	int reqQryRate(const dict &req, int reqid);

	int reqQryClient(int reqid);

	int reqQryClientMargin(const dict &req, int reqid);

	int reqQryExercise(const dict &req, int reqid);

	int reqMarginCombAction(const dict &req, int reqid);

	int reqQrySseCombPosition(const dict &req, int reqid);

	int reqCombExercise(const dict &req, int reqid);
};
