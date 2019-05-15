//系统
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vnfemas.h"
#include "pybind11/pybind11.h"
#include "femas/USTPFtdcTraderApi.h"


using namespace pybind11;

//常量
#define ONFRONTCONNECTED 0
#define ONQRYFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONQRYFRONTDISCONNECTED 3
#define ONHEARTBEATWARNING 4
#define ONPACKAGESTART 5
#define ONPACKAGEEND 6
#define ONRSPERROR 7
#define ONRSPUSERLOGIN 8
#define ONRSPUSERLOGOUT 9
#define ONRSPUSERPASSWORDUPDATE 10
#define ONRSPORDERINSERT 11
#define ONRSPORDERACTION 12
#define ONRSPQUOTEINSERT 13
#define ONRSPQUOTEACTION 14
#define ONRSPFORQUOTE 15
#define ONRSPMARGINCOMBACTION 16
#define ONRSPUSERDEPOSIT 17
#define ONRSPTRANSFERMONEY 18
#define ONRTNFLOWMESSAGECANCEL 19
#define ONRTNTRADE 20
#define ONRTNORDER 21
#define ONERRRTNORDERINSERT 22
#define ONERRRTNORDERACTION 23
#define ONRTNINSTRUMENTSTATUS 24
#define ONRTNINVESTORACCOUNTDEPOSIT 25
#define ONRTNQUOTE 26
#define ONERRRTNQUOTEINSERT 27
#define ONERRRTNQUOTEACTION 28
#define ONRTNFORQUOTE 29
#define ONRTNMARGINCOMBINATIONLEG 30
#define ONRTNMARGINCOMBACTION 31
#define ONRTNUSERDEPOSIT 32
#define ONRSPQUERYUSERLOGIN 33
#define ONRSPQRYORDER 34
#define ONRSPQRYTRADE 35
#define ONRSPQRYUSERINVESTOR 36
#define ONRSPQRYTRADINGCODE 37
#define ONRSPQRYINVESTORACCOUNT 38
#define ONRSPQRYINSTRUMENT 39
#define ONRSPQRYEXCHANGE 40
#define ONRSPQRYINVESTORPOSITION 41
#define ONRSPQRYCOMPLIANCEPARAM 42
#define ONRSPQRYINVESTORFEE 43
#define ONRSPQRYINVESTORMARGIN 44
#define ONRSPQRYINVESTORCOMBPOSITION 45
#define ONRSPQRYINVESTORLEGPOSITION 46
#define ONRSPQRYINSTRUMENTGROUP 47
#define ONRSPQRYCLIENTMARGINCOMBTYPE 48
#define ONRSPEXECORDERINSERT 49
#define ONRSPEXECORDERACTION 50
#define ONRTNEXECORDER 51
#define ONERRRTNEXECORDERINSERT 52
#define ONERRRTNEXECORDERACTION 53
#define ONRTNTRANSFERMONEY 54
#define ONRSPQRYSYSTEMTIME 55



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public CUstpFtdcTraderSpi
{
private:
	CUstpFtdcTraderApi* api;			//API对象
	thread task_thread;					//工作线程指针（向python中推送数据）
	TaskQueue task_queue;			    //任务队列
	bool active = false;				//工作状态

public:
	TdApi()
	{
	};

	~TdApi()
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
	virtual void OnQryFrontConnected();
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason) ;
	virtual void OnQryFrontDisconnected(int nReason);

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse) ;

	virtual void OnPackageStart(int nTopicID, int nSequenceNo);
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo);

	///错误应答
	virtual void OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///风控前置系统用户登录应答
	virtual void OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///用户退出应答
	virtual void OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单录入应答
	virtual void OnRspOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单操作应答
	virtual void OnRspOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报价录入应答
	virtual void OnRspQuoteInsert(CUstpFtdcInputQuoteField *pInputQuote, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报价操作应答
	virtual void OnRspQuoteAction(CUstpFtdcQuoteActionField *pQuoteAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///询价请求应答
	virtual void OnRspForQuote(CUstpFtdcReqForQuoteField *pReqForQuote, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///客户申请组合应答
	virtual void OnRspMarginCombAction(CUstpFtdcInputMarginCombActionField *pInputMarginCombAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///用户请求出入金应答
	virtual void OnRspUserDeposit(CUstpFtdcstpUserDepositField *pstpUserDeposit, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///用户主次席出入金应答
	virtual void OnRspTransferMoney(CUstpFtdcstpTransferMoneyField *pstpTransferMoney, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///数据流回退通知
	virtual void OnRtnFlowMessageCancel(CUstpFtdcFlowMessageCancelField *pFlowMessageCancel) ;

	///成交回报
	virtual void OnRtnTrade(CUstpFtdcTradeField *pTrade) ;

	///报单回报
	virtual void OnRtnOrder(CUstpFtdcOrderField *pOrder) ;

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo) ;

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo) ;

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus) ;

	///账户出入金回报
	virtual void OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes) ;

	///报价回报
	virtual void OnRtnQuote(CUstpFtdcRtnQuoteField *pRtnQuote) ;

	///报价录入错误回报
	virtual void OnErrRtnQuoteInsert(CUstpFtdcInputQuoteField *pInputQuote, CUstpFtdcRspInfoField *pRspInfo) ;

	///报价撤单错误回报
	virtual void OnErrRtnQuoteAction(CUstpFtdcQuoteActionField *pQuoteAction, CUstpFtdcRspInfoField *pRspInfo) ;

	///询价回报
	virtual void OnRtnForQuote(CUstpFtdcReqForQuoteField *pReqForQuote) ;

	///增加组合规则通知
	virtual void OnRtnMarginCombinationLeg(CUstpFtdcMarginCombinationLegField *pMarginCombinationLeg) ;

	///客户申请组合确认
	virtual void OnRtnMarginCombAction(CUstpFtdcInputMarginCombActionField *pInputMarginCombAction) ;

	///用户请求出入金
	virtual void OnRtnUserDeposit(CUstpFtdcstpUserDepositField *pstpUserDeposit) ;

	///查询前置系统用户登录应答
	virtual void OnRspQueryUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///报单查询应答
	virtual void OnRspQryOrder(CUstpFtdcOrderField *pOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///成交单查询应答
	virtual void OnRspQryTrade(CUstpFtdcTradeField *pTrade, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///可用投资者账户查询应答
	virtual void OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField *pRspUserInvestor, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///交易编码查询应答
	virtual void OnRspQryTradingCode(CUstpFtdcRspTradingCodeField *pRspTradingCode, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///投资者资金账户查询应答
	virtual void OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField *pRspInvestorAccount, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///合约查询应答
	virtual void OnRspQryInstrument(CUstpFtdcRspInstrumentField *pRspInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///交易所查询应答
	virtual void OnRspQryExchange(CUstpFtdcRspExchangeField *pRspExchange, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///投资者持仓查询应答
	virtual void OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField *pRspInvestorPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///合规参数查询应答
	virtual void OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField *pRspComplianceParam, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///投资者手续费率查询应答
	virtual void OnRspQryInvestorFee(CUstpFtdcInvestorFeeField *pInvestorFee, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///投资者保证金率查询应答
	virtual void OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField *pInvestorMargin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///交易编码组合持仓查询应答
	virtual void OnRspQryInvestorCombPosition(CUstpFtdcRspInvestorCombPositionField *pRspInvestorCombPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///交易编码单腿持仓查询应答
	virtual void OnRspQryInvestorLegPosition(CUstpFtdcRspInvestorLegPositionField *pRspInvestorLegPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///合约组信息查询应答
	virtual void OnRspQryInstrumentGroup(CUstpFtdcRspInstrumentGroupField *pRspInstrumentGroup, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///组合保证金类型查询应答
	virtual void OnRspQryClientMarginCombType(CUstpFtdcRspClientMarginCombTypeField *pRspClientMarginCombType, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///行权录入应答
	virtual void OnRspExecOrderInsert(CUstpFtdcInputExecOrderField *pInputExecOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///行权操作应答
	virtual void OnRspExecOrderAction(CUstpFtdcInputExecOrderActionField *pInputExecOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///行权通知
	virtual void OnRtnExecOrder(CUstpFtdcExecOrderField *pExecOrder) ;

	///行权录入错误回报
	virtual void OnErrRtnExecOrderInsert(CUstpFtdcInputExecOrderField *pInputExecOrder, CUstpFtdcRspInfoField *pRspInfo) ;

	///行权操作错误回报
	virtual void OnErrRtnExecOrderAction(CUstpFtdcInputExecOrderActionField *pInputExecOrderAction, CUstpFtdcRspInfoField *pRspInfo) ;

	///主次席资金同步通知
	virtual void OnRtnTransferMoney(CUstpFtdcSyncMoneyTransferField *pSyncMoneyTransfer) ;

	///系统时间查询应答
	virtual void OnRspQrySystemTime(CUstpFtdcRspQrySystemTimeField *pRspQrySystemTime, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;


	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processQryFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processQryFrontDisconnected(Task *task);

	void processHeartBeatWarning(Task *task);

	void processPackageStart(Task *task);

	void processPackageEnd(Task *task);

	void processRspError(Task *task);

	void processRspUserLogin(Task *task);

	void processRspUserLogout(Task *task);

	void processRspUserPasswordUpdate(Task *task);

	void processRspOrderInsert(Task *task);

	void processRspOrderAction(Task *task);

	void processRspQuoteInsert(Task *task);

	void processRspQuoteAction(Task *task);

	void processRspForQuote(Task *task);

	void processRspMarginCombAction(Task *task);

	void processRspUserDeposit(Task *task);

	void processRspTransferMoney(Task *task);

	void processRtnFlowMessageCancel(Task *task);

	void processRtnTrade(Task *task);

	void processRtnOrder(Task *task);

	void processErrRtnOrderInsert(Task *task);

	void processErrRtnOrderAction(Task *task);

	void processRtnInstrumentStatus(Task *task);

	void processRtnInvestorAccountDeposit(Task *task);

	void processRtnQuote(Task *task);

	void processErrRtnQuoteInsert(Task *task);

	void processErrRtnQuoteAction(Task *task);

	void processRtnForQuote(Task *task);

	void processRtnMarginCombinationLeg(Task *task);

	void processRtnMarginCombAction(Task *task);

	void processRtnUserDeposit(Task *task);

	void processRspQueryUserLogin(Task *task);

	void processRspQryOrder(Task *task);

	void processRspQryTrade(Task *task);

	void processRspQryUserInvestor(Task *task);

	void processRspQryTradingCode(Task *task);

	void processRspQryInvestorAccount(Task *task);

	void processRspQryInstrument(Task *task);

	void processRspQryExchange(Task *task);

	void processRspQryInvestorPosition(Task *task);

	void processRspQryComplianceParam(Task *task);

	void processRspQryInvestorFee(Task *task);

	void processRspQryInvestorMargin(Task *task);

	void processRspQryInvestorCombPosition(Task *task);

	void processRspQryInvestorLegPosition(Task *task);

	void processRspQryInstrumentGroup(Task *task);

	void processRspQryClientMarginCombType(Task *task);

	void processRspExecOrderInsert(Task *task);

	void processRspExecOrderAction(Task *task);

	void processRtnExecOrder(Task *task);

	void processErrRtnExecOrderInsert(Task *task);

	void processErrRtnExecOrderAction(Task *task);

	void processRtnTransferMoney(Task *task);

	void processRspQrySystemTime(Task *task);



	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------
	virtual void onFrontConnected() {};

	virtual void onQryFrontConnected() {};

	virtual void onFrontDisconnected(int reqid) {};

	virtual void onQryFrontDisconnected(int reqid) {};

	virtual void onHeartBeatWarning(int reqid) {};

	virtual void onPackageStart(int reqid) {};

	virtual void onPackageEnd(int reqid) {};

	virtual void onRspError(const dict &data, int reqid, bool last) {};

	virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQuoteAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspForQuote(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspMarginCombAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserDeposit(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspTransferMoney(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnFlowMessageCancel(const dict &data) {};

	virtual void onRtnTrade(const dict &data) {};

	virtual void onRtnOrder(const dict &data) {};

	virtual void onErrRtnOrderInsert(const dict &data, const dict &error) {};

	virtual void onErrRtnOrderAction(const dict &data, const dict &error) {};

	virtual void onRtnInstrumentStatus(const dict &data) {};

	virtual void onRtnInvestorAccountDeposit(const dict &data) {};

	virtual void onRtnQuote(const dict &data) {};

	virtual void onErrRtnQuoteInsert(const dict &data, const dict &error) {};

	virtual void onErrRtnQuoteAction(const dict &data, const dict &error) {};

	virtual void onRtnForQuote(const dict &data) {};

	virtual void onRtnMarginCombinationLeg(const dict &data) {};

	virtual void onRtnMarginCombAction(const dict &data) {};

	virtual void onRtnUserDeposit(const dict &data) {};

	virtual void onRspQueryUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryUserInvestor(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryTradingCode(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorAccount(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryComplianceParam(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorFee(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorMargin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorCombPosition(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorLegPosition(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInstrumentGroup(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryClientMarginCombType(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspExecOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspExecOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnExecOrder(const dict &data) {};

	virtual void onErrRtnExecOrderInsert(const dict &data, const dict &error) {};

	virtual void onErrRtnExecOrderAction(const dict &data, const dict &error) {};

	virtual void onRtnTransferMoney(const dict &data) {};

	virtual void onRspQrySystemTime(const dict &data, const dict &error, int reqid, bool last) {};



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

	void subscribeUserTopic(int nType);

	int reqUserLogin(const dict &req, int reqid);

	int reqUserLogout(const dict &req, int reqid);

	int reqUserPasswordUpdate(const dict &req, int reqid);

	int reqOrderInsert(const dict &req, int reqid);

	int reqOrderAction(const dict &req, int reqid);

	int reqQuoteInsert(const dict &req, int reqid);

	int reqQuoteAction(const dict &req, int reqid);

	int reqForQuote(const dict &req, int reqid);

	int reqMarginCombAction(const dict &req, int reqid);

	int reqUserDeposit(const dict &req, int reqid);

	int reqTransferMoney(const dict &req, int reqid);

	int reqQryOrder(const dict &req, int reqid);

	int reqQryTrade(const dict &req, int reqid);

	int reqQryUserInvestor(const dict &req, int reqid);

	int reqQryTradingCode(const dict &req, int reqid);

	int reqQryInvestorAccount(const dict &req, int reqid);

	int reqQryInstrument(const dict &req, int reqid);

	int reqQryExchange(const dict &req, int reqid);

	int reqQryInvestorPosition(const dict &req, int reqid);

	int reqQryComplianceParam(const dict &req, int reqid);

	int reqQryInvestorFee(const dict &req, int reqid);

	int reqQryInvestorMargin(const dict &req, int reqid);

	int reqQryInvestorCombPosition(const dict &req, int reqid);

	int reqQryInvestorLegPosition(const dict &req, int reqid);

	int reqQryInstrumentGroup(const dict &req, int reqid);

	int reqQryClientMarginCombType(const dict &req, int reqid);

	int reqExecOrderInsert(const dict &req, int reqid);

	int reqExecOrderAction(const dict &req, int reqid);

	int reqQrySystemTime(const dict &req, int reqid);
};
