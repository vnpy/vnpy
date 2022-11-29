//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnnst.h"
#include "pybind11/pybind11.h"
#include "nst/uft4_traderspi.h"


//常量
#define ONFRONTCONNECTED 0
#define ONRSPUSERLOGIN 1
#define ONANSORDERINSERT 2
#define ONRSPORDERINSERT 3
#define ONANSORDERACTION 4
#define ONRSPORDERACTION 5
#define ONORDERRTN 6
#define ONTRADERTN 7
#define ONRSPTRADINGACCOUNT 8
#define ONRSPERROR 9
#define ONRSPQRYORDER 10
#define ONRSPQRYTRADE 11
#define ONRSPQRYINVESTORPOSITION 12
#define ONRSPQRYCHANGEPWD 13
#define ONRSPLOGOUT 14
#define ONRTNINSTRUMENTSTATUS 15
#define ONRSPTEST 16
#define ONERRRTNORDERINSERT 17
#define ONERRRTNORDERACTION 18




///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public CUft4_TraderSpi
{
private:
	CUft4_TraderApi* api;                     //API对象
    thread task_thread;                    //工作线程指针（向python中推送数据）
    TaskQueue task_queue;                //任务队列
    bool active = false;                //工作状态

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

	virtual void OnFrontConnected();
	virtual void OnRspUserLogin(CUftRspUserLoginField* pRspUserLogin, CUftRspInfoField* pRspInfo);

	//柜台报单录入响应
	virtual void OnAnsOrderInsert(CUftAnsOrderInsertField *pOrderRsp, CUftRspErrorField* pError);

	//交易所报单录入响应
	virtual void OnRspOrderInsert(CUftRspnOrderInsertField *pOrderRsp, CUftRspErrorField* pError);

	//柜台报单操作请求响应
	virtual void OnAnsOrderAction(CUftAnsOrderActionField *pOrderAction, CUftRspErrorField* pError);

	//交易所报单操作请求响应
	virtual void OnRspOrderAction(CUftRspnOrderActionField *pOrderAction, CUftRspErrorField* pError);


	//报单回报
	virtual void OnOrderRtn(CUftRtnnOrderField* pOrder);

	//成交回报
	virtual void OnTradeRtn(CUftRtnnTradeField* pOrder);

	//查询资金回报
	virtual void OnRspTradingAccount(CUftAnsQueryFundField *pRspFund);

	virtual void OnRspError(CUftRspErrorField* pError);


	///请求查询报单响应
	virtual void OnRspQryOrder(CUftAnsQueryOrderField *pEntrust, bool bIsLast);

	///请求查询成交响应
	virtual void OnRspQryTrade(CUftAnsQueryTradeField *pTrade, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CUftAnsQueryPositionField *pInvestorPosition, bool bIsLast);


	///修改密码响应
	virtual void OnRspQryChangePwd();

	virtual void OnRspLogout(const char* szMsg);

	virtual void OnRtnInstrumentStatus(CUftRtnInstrumentStatusField *pInstStatus);

	virtual void OnRspTest(CUftRspTest *pTest);

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CUftRspErrorField* pError);

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CUftRspErrorField* pError);


    //-------------------------------------------------------------------------------------
    //task：任务
    //-------------------------------------------------------------------------------------
    void processTask();

	void processFrontConnected(Task *task);

	void processRspUserLogin(Task *task);

	void processAnsOrderInsert(Task *task);

	void processRspOrderInsert(Task *task);

	void processAnsOrderAction(Task *task);

	void processRspOrderAction(Task *task);

	void processOrderRtn(Task *task);

	void processTradeRtn(Task *task);

	void processRspTradingAccount(Task *task);

	void processRspError(Task *task);

	void processRspQryOrder(Task *task);

	void processRspQryTrade(Task *task);

	void processRspQryInvestorPosition(Task *task);

	void processRspQryChangePwd(Task *task);

	void processRspLogout(Task *task);

	void processRtnInstrumentStatus(Task *task);

	void processRspTest(Task *task);

	void processErrRtnOrderInsert(Task *task);

	void processErrRtnOrderAction(Task *task);



    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------    

	virtual void onFrontConnected() {};

	virtual void onRspUserLogin(const dict &data, const dict &error) {};

	virtual void onAnsOrderInsert(const dict &data, const dict &error) {};

	virtual void onRspOrderInsert(const dict &data, const dict &error) {};

	virtual void onAnsOrderAction(const dict &data, const dict &error) {};

	virtual void onRspOrderAction(const dict &data, const dict &error) {};

	virtual void onOrderRtn(const dict &data) {};

	virtual void onTradeRtn(const dict &data) {};

	virtual void onRspTradingAccount(const dict &data) {};

	virtual void onRspError(const dict &error) {};

	virtual void onRspQryOrder(const dict &data, bool last) {};

	virtual void onRspQryTrade(const dict &data, bool last) {};

	virtual void onRspQryInvestorPosition(const dict &data, bool last) {};

	virtual void onRspQryChangePwd() {};

	virtual void onRspLogout(string data) {};

	virtual void onRtnInstrumentStatus(const dict &data) {};

	virtual void onRspTest(const dict &data) {};

	virtual void onErrRtnOrderInsert(const dict &error) {};

	virtual void onErrRtnOrderAction(const dict &error) {};



    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------

	void newTradeApi(int nCnnMode);

	void tasksetCPU(int nBindingRspCpuId, int nBindingRtnCpuId);

    int init(string szAccount, string szPwd, int eExType);

    int join();

	int exit();

	void registerFront(string pszFrontAddress, uint16_t nPort, string pszLocalAddr, uint16_t nReqPort, uint16_t nRspPort, uint16_t nLocalNotifyPort);

	int reqUserLogin();

	int reqUserLogout();

	int reqOrderInsert(string szCode, char bs, char kp, double dbPrice, int nVolume, int64_t nOrderRef, char cOrderPriceType);

	int reqOrderAction(int nOrderIndex, int nOrderRef);

	int reqTradingAccount();

	int reqQryOrder(string szInstrumentID, int nStartTime, int nEndTime, string szOrderSysID, int nOrderRef, int nOrderIndex);

	int reqQryTrade(string szInstrumentID, int nStartTime, int nEndTime, string szOrderSysID, int nOrderIndex, int nOrderRef);

	int reqQryInvestorPosition(string szInstrumentID);

	int reqChangePwd(string szNewPwd, string szOldPwd);

	int reqQryTest();

	uint64_t getToken();

	int getReqPort();


};
