//系统
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vnksgold.h"
#include "pybind11/pybind11.h"
#include "ksgold/KSGoldTraderApi.h"


using namespace pybind11;
using namespace KSGoldTradeAPI;


//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONRSPUSERLOGIN 2
#define ONRSPUSERLOGOUT 3
#define ONNTYMKTSTATUS 4
#define ONRTNINSTRUMENTSTATUS 5
#define ONRSPQRYINSTRUMENT 6
#define ONRSPREQQRYVARIETYCODE 7
#define ONRSPORDERINSERT 8
#define ONRSPETFSUBSCRIPTIONORDERINSERT 9
#define ONRSPETFPURCHASEORDERINSERT 10
#define ONRSPETFREDEEMINSERT 11
#define ONRSPETFACCOUNTBINDING 12
#define ONRSPETFACCOUNTUNBINDING 13
#define ONRTNORDER 14
#define ONFORCELOGOUT 15
#define ONRTNETFACCOUNTBINDINGSTATUS 16
#define ONRTNETFORDER 17
#define ONRSPORDERACTION 18
#define ONRSPERROR 19
#define ONRTNTRADE 20
#define ONRSPQRYTRADINGACCOUNT 21
#define ONRSPQRYHISCAPITAL 22
#define ONRSPQRYORDER 23
#define ONRSPQRYTRADE 24
#define ONRSPQRYINVESTORPOSITION 25
#define ONRSPQRYCLIENTSTORAGE 26
#define ONRSPQRYCOSTMARGINFEERATE 27
#define ONRSPCONDITIONORDERINSERT 28
#define ONRSPCONDITIONORDERACTION 29
#define ONRSPQRYCONDITIONORDER 30
#define ONRSPQRYCONDITIONORDERTRADE 31
#define ONRSPQRYCLIENTSESSIONINFO 32
#define ONRSPQRYQUOTATION 33
#define ONRSPQRYINVESTORPOSITIONDETAIL 34
#define ONRSPQRYETFRADEDETAIL 35
#define ONRSPQRYETFPCFDETAIL 36
#define ONRSPMODIFYPASSWORD 37
#define ONRSPB0CMONEYIO 38



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public CKSGoldTraderSpi
{
private:
	CKSGoldTraderApi* api;                     //API对象
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

	///当客户端与交易后台建立起通信连接时，该方法被调用。
	///出现断线重连时，也会调用此方法
	///@param nResult 返回结果
	///        0x1001 建立连接
	///        0x1002 断线重连成功
	virtual void OnFrontConnected(int nResult);

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//市场状态通知
	virtual void OnNtyMktStatus(CThostFtdcMarketStatusField *pfldMktStatus);

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//请求查询交割品种响应
	virtual void OnRspReqQryVarietyCode(CThostFtdcRspVarietyCodeField *pVarietyCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcRspInputOrderField *pRspInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ETF认购请求响应
	virtual void OnRspETFSubscriptionOrderInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ETF申购请求响应
	virtual void OnRspETFPurchaseOrderInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ETF赎回请求响应
	virtual void OnRspETFRedeemInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ETF账户绑定请求响应
	virtual void OnRspETFAccountBinding(CThostFtdcETFBindingStatusField *pETFAccountBinding, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ETF账户解绑定请求响应
	virtual void OnRspETFAccountUnbinding(CThostFtdcETFBindingStatusField *pETFAccountUnbinding, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///强退通知
	virtual void OnForceLogout(CThostFtdcUserLogoutField *pLogout);

	//ETF账户绑定解绑定状态通知
	virtual void OnRtnETFAccountBindingStatus(CThostFtdcETFBindingStatusField * pETFBindgingStatus);

	//ETF认申赎报单状态通知
	virtual void OnRtnETFOrder(CThostFtdcETFTradeDetailField *pEtfTradeDetail);

	///撤单应答
	virtual void OnRspOrderAction(CThostFtdcRspInputOrderActionField *pRspInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求历史资金查询
	virtual void OnRspQryHisCapital(CThostFtdcRspHisCapitalField *pHisCapital, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询客户库存响应
	virtual void OnRspQryClientStorage(CThostFtdcStorageField *pStorage, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///费率\保证金率查询响应
	virtual void OnRspQryCostMarginFeeRate(CThostFtdcRspCostMarginFeeField *pCostMarginFee, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///条件单委托响应
	virtual void OnRspConditionOrderInsert(CThostFtdcRspConditionOrderField *pConditionOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///条件单撤单响应
	virtual void OnRspConditionOrderAction(CThostFtdcRspConditionActionOrderField *pConditionActionOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///条件单委托查询响应
	virtual void OnRspQryConditionOrder(CThostFtdcRspConditionOrderQryField *pConditionOrderQry, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///条件单成交查询响应
	virtual void OnRspQryConditionOrderTrade(CThostFtdcRspConditionOrderMatchField *pConditionOrderMatch, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///客户会话信息通用查询响应
	virtual void OnRspQryClientSessionInfo(CThostFtdcRspClientSessionField *pClientSessionField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询行情信息响应
	virtual void OnRspQryQuotation(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ETF认申赎交易查询响应
	virtual void OnRspQryETFradeDetail(CThostFtdcETFTradeDetailField *pQryETFTradeDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ETF认申赎清单查询
	virtual void OnRspQryETFPcfDetail(CThostFtdcETFPcfDetailField *pQryETFpcfDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///修改密码响应
	virtual void OnRspModifyPassword(CThostFtdcModifyPasswordRsqField *pRsqModifyPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///中行出入金响应
	virtual void OnRspB0CMoneyIO(CThostFtdcBOCMoneyIORspField *pRspBOCMoneyIO, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);



    //-------------------------------------------------------------------------------------
    //task：任务
    //-------------------------------------------------------------------------------------
    void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processRspUserLogin(Task *task);

	void processRspUserLogout(Task *task);

	void processNtyMktStatus(Task *task);

	void processRtnInstrumentStatus(Task *task);

	void processRspQryInstrument(Task *task);

	void processRspReqQryVarietyCode(Task *task);

	void processRspOrderInsert(Task *task);

	void processRspETFSubscriptionOrderInsert(Task *task);

	void processRspETFPurchaseOrderInsert(Task *task);

	void processRspETFRedeemInsert(Task *task);

	void processRspETFAccountBinding(Task *task);

	void processRspETFAccountUnbinding(Task *task);

	void processRtnOrder(Task *task);

	void processForceLogout(Task *task);

	void processRtnETFAccountBindingStatus(Task *task);

	void processRtnETFOrder(Task *task);

	void processRspOrderAction(Task *task);

	void processRspError(Task *task);

	void processRtnTrade(Task *task);

	void processRspQryTradingAccount(Task *task);

	void processRspQryHisCapital(Task *task);

	void processRspQryOrder(Task *task);

	void processRspQryTrade(Task *task);

	void processRspQryInvestorPosition(Task *task);

	void processRspQryClientStorage(Task *task);

	void processRspQryCostMarginFeeRate(Task *task);

	void processRspConditionOrderInsert(Task *task);

	void processRspConditionOrderAction(Task *task);

	void processRspQryConditionOrder(Task *task);

	void processRspQryConditionOrderTrade(Task *task);

	void processRspQryClientSessionInfo(Task *task);

	void processRspQryQuotation(Task *task);

	void processRspQryInvestorPositionDetail(Task *task);

	void processRspQryETFradeDetail(Task *task);

	void processRspQryETFPcfDetail(Task *task);

	void processRspModifyPassword(Task *task);

	void processRspB0CMoneyIO(Task *task);



    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------    

	virtual void onFrontConnected(int nResult) {};

	virtual void onFrontDisconnected(int nReason) {};

	virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onNtyMktStatus(const dict &data) {};

	virtual void onRtnInstrumentStatus(const dict &data) {};

	virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspReqQryVarietyCode(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspETFSubscriptionOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspETFPurchaseOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspETFRedeemInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspETFAccountBinding(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspETFAccountUnbinding(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnOrder(const dict &data) {};

	virtual void onForceLogout(const dict &data) {};

	virtual void onRtnETFAccountBindingStatus(const dict &data) {};

	virtual void onRtnETFOrder(const dict &data) {};

	virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspError(const dict &error, int reqid, bool last) {};

	virtual void onRtnTrade(const dict &data) {};

	virtual void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryHisCapital(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryClientStorage(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryCostMarginFeeRate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspConditionOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspConditionOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryConditionOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryConditionOrderTrade(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryClientSessionInfo(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryQuotation(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInvestorPositionDetail(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryETFradeDetail(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryETFPcfDetail(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspModifyPassword(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspB0CMoneyIO(const dict &data, const dict &error, int reqid, bool last) {};


    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------
	void createGoldTraderApi(string pszFlowPath = " ");

	int exit();

	void release();

	bool init();

	void registerFront(string pszFrontAddress);

	void subscribePrivateTopic(int nResumeType);

	void subscribePublicTopic(int nResumeType);


	int join();

	int reqUserLogin(const dict &req, int reqid);

	int reqUserLogout(const dict &req, int reqid);

	int reqQryInstrument(const dict &req, int reqid);

	int reqQryVarietyCode(const dict &req, int reqid);

	int reqOrderInsert(const dict &req, int reqid);

	int reqOrderAction(const dict &req, int reqid);

	int reqQryInvestorPosition(const dict &req, int reqid);

	int reqQryTradingAccount(const dict &req, int reqid);

	int reqQryTrade(const dict &req, int reqid);

	int reqQryOrder(const dict &req, int reqid);

	int reqQryStorage(const dict &req, int reqid);

	int reqQryCostMarginFeeRate(const dict &req, int reqid);

	int reqConditionOrderInsert(const dict &req, int reqid);

	int reqConditionOrderAction(const dict &req, int reqid);

	int reqQryConditionOrder(const dict &req, int reqid);

	int reqQryConditionOrderTrade(const dict &req, int reqid);

	int reqQryClientSessionInfo(const dict &req, int reqid);

	int reqQryQuotation(const dict &req, int reqid);

	int reqQryInvestorPositionDetail(const dict &req, int reqid);

	int reqModifyPassword(const dict &req, int reqid);

	int reqQryHisCapital(const dict &req, int reqid);

	int reqETFSubScription(const dict &req, int reqid);

	int reqETFApplyForPurchase(const dict &req, int reqid);

	int reqETFRedeem(const dict &req, int reqid);

	int reqETFAccountBinding(const dict &req, int reqid);

	int reqETFAccountUnbinding(const dict &req, int reqid);

	int reqETFTradeDetail(const dict &req, int reqid);

	int reqETFPcfDetail(const dict &req, int reqid);

	int reqBOCMoneyIO(const dict &req, int reqid);


};
