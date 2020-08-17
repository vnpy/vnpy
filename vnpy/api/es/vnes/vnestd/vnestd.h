#pragma once
#ifdef WIN32
#include "pch.h"
#endif

#include "vnes.h"
#include "pybind11/pybind11.h"
#include "es/EsTradeAPI.h"

using namespace pybind11;
using namespace EsTradeAPI;

//常量
#define ONCONNECT 0
#define ONRSPLOGIN 1
#define ONRTNCONTACTINFO 2
#define ONRSPREQUESTVERTIFICATECODE 3
#define ONRTNERRORMSG 4
#define ONAPIREADY 5
#define ONDISCONNECT 6
#define ONRSPSUBMITUSERLOGININFO 7
#define ONRSPCHANGEPASSWORD 8
#define ONRSPSETRESERVEDINFO 9
#define ONRTNCONTRACT 10
#define ONRTNFUND 11
#define ONRTNORDER 12
#define ONRSPQRYORDERPROCESS 13
#define ONRTNFILL 14
#define ONRTNPOSITION 15
#define ONRTNCLOSE 16
#define ONRTNPOSITIONPROFIT 17
#define ONRSPQRYDEEPQUOTE 18
#define ONRTNEXCHANGESTATEINFO 19
#define ONRTNREQQUOTENOTICE 20
#define ONRSPACCOUNTRENTINFO 21
#define ONRSPTRADEMESSAGE 22
#define ONRTNTRADEMESSAGE 23
#define ONRSPQRYHISORDER 24
#define ONRSPQRYHISORDERPROCESS 25
#define ONRSPQRYHISFILL 26
#define ONRSPQRYHISPOSITION 27
#define ONRSPQRYHISDELIVERY 28
#define ONRSPQRYACCOUNTCASHADJUST 29
#define ONRSPQRYBILL 30
#define ONRSPACCOUNTFEERENT 31
#define ONRSPACCOUNTMARGINRENT 32
#define ONRSPADDMOBILEDEVICE 33
#define ONRSPQRYMANAGEINFOFORESTAR 34
#define ONRSPQRYSYSTEMPARAMETER 35
#define ONRSPQRYTRADECENTERFRONTADDRESS 36
#define ONRTNCOMMODITYINFO 37
#define ONRTNCURRENCYINFO 38

///----------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///----------------------------------------------------------------------------------


//API的继承实现
class TdApi : public IEsTradeAPINotify
{
private:
	IEsTradeAPI* api;                   //API对象
	thread task_thread;                 //工作线程指针 (向python中推送数据)
	TaskQueue task_queue;               //任务队列
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



	//------------------------------------------------------------------------------------
	//API回调函数
	//------------------------------------------------------------------------------------
	virtual void ES_CDECL OnConnect(const TAPISTR_20 UserNo);
	virtual void ES_CDECL OnRspLogin(const TAPISTR_20 UserNo, TAPIINT32 nErrorCode, const TapAPITradeLoginRspInfo *pLoginRspInfo);
	virtual void ES_CDECL OnRtnContactInfo(const TAPISTR_20 UserNo, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPISecondInfo* pInfo);   //北斗星专用
	virtual void ES_CDECL OnRspRequestVertificateCode(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIVertificateCode *pInfo);    //北斗星专用 nSessionID
	virtual void ES_CDECL OnRtnErrorMsg(const TAPISTR_20 UserNo, const TAPISTR_500 ErrorMsg);	
	virtual void ES_CDECL OnAPIReady(const TAPISTR_20 UserNo);//
	virtual void ES_CDECL OnDisconnect(const TAPISTR_20 UserNo, TAPIINT32 nReasonCode);
	virtual void ES_CDECL OnRspSubmitUserLoginInfo(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, const TapAPISubmitUserLoginInfoRsp *pRspInfo);   //nSessionID
	virtual void ES_CDECL OnRspChangePassword(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode);    //nSessionID
	virtual void ES_CDECL OnRspSetReservedInfo(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode, const TAPISTR_50 info);    //nSessionID
	virtual void ES_CDECL OnRtnContract(const TAPISTR_20 UserNo, const TapAPITradeContractInfo *pRtnInfo);
	virtual void ES_CDECL OnRtnFund(const TAPISTR_20 UserNo, const TapAPIFundData *pRtnInfo);
	virtual void ES_CDECL OnRtnOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderInfo *pRtnInfo);
	virtual void ES_CDECL OnRspQryOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *pRspInfo);
	virtual void ES_CDECL OnRtnFill(const TAPISTR_20 UserNo, const TapAPIFillInfo *pRtnInfo);
	virtual void ES_CDECL OnRtnPosition(const TAPISTR_20 UserNo, const TapAPIPositionInfo *pRtnInfo);
	virtual void ES_CDECL OnRtnClose(const TAPISTR_20 UserNo, const TapAPICloseInfo *pRtnInfo);
	virtual void ES_CDECL OnRtnPositionProfit(const TAPISTR_20 UserNo, const TapAPIPositionProfitNotice *pRtnInfo);
	virtual void ES_CDECL OnRspQryDeepQuote(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *pRspInfo);
	virtual void ES_CDECL OnRtnExchangeStateInfo(const TAPISTR_20 UserNo, const TapAPIExchangeStateInfoNotice *pRtnInfo);
	virtual void ES_CDECL OnRtnReqQuoteNotice(const TAPISTR_20 UserNo, const TapAPIReqQuoteNotice *pRtnInfo);
	virtual void ES_CDECL OnRspAccountRentInfo(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo *pRspInfo);
	virtual void ES_CDECL OnRspTradeMessage(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPITradeMessage *pRspInfo);
	virtual void ES_CDECL OnRtnTradeMessage(const TAPISTR_20 UserNo, const TapAPITradeMessage *pRtnInfo);
	virtual void ES_CDECL OnRspQryHisOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisOrderQryRsp *pInfo);
	virtual void ES_CDECL OnRspQryHisOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisOrderProcessQryRsp *pInfo);
	virtual void ES_CDECL OnRspQryHisFill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisFillQryRsp *pInfo);
	virtual void ES_CDECL OnRspQryHisPosition(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisPositionQryRsp *pInfo);
	virtual void ES_CDECL OnRspQryHisDelivery(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisDeliveryQryRsp *pInfo);
	virtual void ES_CDECL OnRspQryAccountCashAdjust(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountCashAdjustQryRsp *pInfo);
	virtual void ES_CDECL OnRspQryBill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIBillQryRsp *pInfo);
	virtual void ES_CDECL OnRspAccountFeeRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountFeeRentQryRsp *pInfo);
	virtual void ES_CDECL OnRspAccountMarginRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountMarginRentQryRsp *pInfo);
	virtual void ES_CDECL OnRspAddMobileDevice(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIMobileDeviceAddRsp *pInfo);
	virtual void ES_CDECL OnRspQryManageInfoForEStar(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIManageInfo *pInfo);
	virtual void ES_CDECL OnRspQrySystemParameter(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPISystemParameterInfo *pInfo);
	virtual void ES_CDECL OnRspQryTradeCenterFrontAddress(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPITradeCenterFrontAddressInfo *pInfo);
	virtual void ES_CDECL OnRtnCommodityInfo(const TAPISTR_20 UserNo, const TapAPICommodityInfo *pInfo);
	virtual void ES_CDECL OnRtnCurrencyInfo(const TAPISTR_20 UserNo, const TapAPICurrencyInfo *pInfo);


	//---------------------------------------------------------------------------------
	//task: 任务
	//---------------------------------------------------------------------------------
	void processTask();

	void processConnect(Task *task);

	void processRspLogin(Task *task);

	void processRtnContactInfo(Task *task);    //北斗星专用

	void processRspRequestVertificateCode(Task *task);    //北斗星专用

	void processRtnErrorMsg(Task *task);

	void processAPIReady(Task *task);

	void processDisconnect(Task *task);

	void processRspSubmitUserLoginInfo(Task *task);	

	void processRspChangePassword(Task *task);

	void processRspSetReservedInfo(Task *task);

	void processRtnContract(Task *task);

	void processRtnFund(Task *task);

	void processRtnOrder(Task *task);

	void processRspQryOrderProcess(Task *task);

	void processRtnFill(Task *task);

	void processRtnPosition(Task *task);

	void processRtnClose(Task *task);

	void processRtnPositionProfit(Task *task);
	
	void processRspQryDeepQuote(Task *task);
	

	void processRtnExchangeStateInfo(Task *task);

	
	void processRtnReqQuoteNotice(Task *task);

	void processRspAccountRentInfo(Task *task);

	void processRspTradeMessage(Task *task);

	void processRtnTradeMessage(Task *task);
	

	void processRspQryHisOrder(Task *task);    //北斗星专用

	void processRspQryHisOrderProcess(Task *task);    //北斗星专用   

	void processRspQryHisFill(Task *task);    //北斗星专用

	void processRspQryHisPosition(Task *task);    //北斗星专用

	void processRspQryHisDelivery(Task *task);    //北斗星专用

	void processRspQryAccountCashAdjust(Task *task);    //北斗星专用

	void processRspQryBill(Task *task);    //北斗星专用

	void processRspAccountFeeRent(Task *task);    //北斗星专用

	void processRspAccountMarginRent(Task *task);    //北斗星专用

	void processRspAddMobileDevice(Task *task);    //北斗星专用

	void processRspQryManageInfoForEStar(Task *task);    //北斗星专用

	void processRspQrySystemParameter(Task *task);    //北斗星专用

	void processRspQryTradeCenterFrontAddress(Task *task);    //北斗星专用

	void processRtnCommodityInfo(Task *task);    //北斗星专用

	void processRtnCurrencyInfo(Task *task);    //北斗星专用


	

	//---------------------------------------------------------------------------------
	//data: 回调函数的数据字典
	//error;回调函数的错误字典
	//id: 请求id
	//last: 是否为最后返回
	//i: 整数
	//---------------------------------------------------------------------------------

	virtual void onConnect(string userNo) {};

	virtual void onRspLogin(string userNo, int nErrorCode, const dict &data) {};

	virtual void onRtnContactInfo(string userNo, int error, char last, const dict &data) {};   //北斗

	virtual void onRspRequestVertificateCode(string userNo, unsigned int nSessionID, int error, char last, const dict &data) {};   //北斗//nSessionID

	virtual void onRtnErrorMsg(string userNo, string ErrorMsg) {};

	virtual void onAPIReady(string userNo) {};

	virtual void onDisconnect(string userNo, int nReasonCode) {};

	virtual void onRspSubmitUserLoginInfo(string userNo, unsigned int nSessionID, const dict &data) {};  // 中继用户提交用户登录信息。(启明星专用)//nSessionID
	
	virtual void onRspChangePassword(string userNo, unsigned int nSessionID, int nErrorCode) {};   //nSessionID

	virtual void onRspSetReservedInfo(string userNo, unsigned int nSessionID, int nErrorCode, string info) {};    //nSessionID

	virtual void onRtnContract(string userNo, const dict &data) {};

	virtual void onRtnFund(string userNo, const dict &data) {};

	virtual void onRtnOrder(string userNo, unsigned int nRequestID, const dict &data) {};

	virtual void onRspQryOrderProcess(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRtnFill(string userNo, const dict &data) {};

	virtual void onRtnPosition(string userNo, const dict &data) {};

	virtual void onRtnClose(string userNo, const dict &data) {};

	virtual void onRtnPositionProfit(string userNo, const dict &data) {};

	virtual void onRspQryDeepQuote(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};
	
	virtual void onRtnExchangeStateInfo(string userNo, const dict &data) {};    //bad

	virtual void onRtnReqQuoteNotice(string userNo, const dict &data) {};

	virtual void onRspAccountRentInfo(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspTradeMessage(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRtnTradeMessage(string userNo, const dict &data) {};

	virtual void onRspQryHisOrder(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryHisOrderProcess(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryHisFill(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryHisPosition(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryHisDelivery(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryAccountCashAdjust(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryBill(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspAccountFeeRent(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspAccountMarginRent(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspAddMobileDevice(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryManageInfoForEStar(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQrySystemParameter(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRspQryTradeCenterFrontAddress(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) {};

	virtual void onRtnCommodityInfo(string userNo, const dict &data) {};

	virtual void onRtnCurrencyInfo(string userNo, const dict &data) {};

	

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createEsTradeAPI();   //原生函数有一个返回值nResult
	void release();
	void init();
	int exit();

	string getEsTradeAPIVersion();//
	
	//int SetAPINotify(IEsTradeAPINotify *pApiNotify);
	int setEsTradeAPIDataPath(string path);
	int setEsTradeAPILogLevel(string level);
	int setUserInfo(const dict &req);
	int startUser(string userNo, const dict &req);
	int stopUser(string userNo);

	int getAccount(string userNo); //, TAPIUINT32 nDataSeqID, TapAPIAccountInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	int getExchange(string userNo);// , TAPIUINT32 nDataSeqID, TapAPIExchangeInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	
	int getCommodity(string userNo);// , TAPIUINT32 nDataSeqID, TapAPICommodityInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	int getContract(string userNo);
	int getFund(string userNo);
	int getOrder(string userNo);
	int getFill(string userNo);
	int getPosition(string userNo);// const TapAPIPositionQryReq *pReqInfo, TapAPIPositionInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	int getClose(string userNo);



	int qryOrderProcess(string userNo, unsigned int nRequestID, const dict &req);
	int qryDeepQuote(string userNo, unsigned int nRequestID, const dict &req);
	

	pybind11::tuple insertOrder(string userNo, unsigned int nRequestID, const dict &req);
	int cancelOrder(string userNo, unsigned int nRequestID, const dict &req);
	

	//int submitUserLoginInfo(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPISubmitUserLoginInfo *pUserLoginInfo);    //启明星中继用户专用
	
	int changePassword(string userNo, unsigned int nRequestID, const dict &req);
	int haveCertainRight(string userNo, int nRightID);
	int setReservedInfo(string userNo, unsigned int nRequestID, string info);
	//int getAccount(string userNo, TAPIUINT32 nDataSeqID, TapAPIAccountInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int getExchange(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPIExchangeInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int GetCommodity(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPICommodityInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int GetContract(const TAPISTR_20 UserNo, const TapAPICommodity *pReqInfo, TAPIUINT32 nDataSeqID, TapAPITradeContractInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int InsertOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPINewOrder *pOrder);
	//int CancelOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderCancelReq *pOrder);
	
	int activateOrder(string userNo, unsigned int nRequestID, const dict &req);

	//int GetFund(const TAPISTR_20 UserNo, const TapAPIFundReq *pReqInfo, TapAPIFundData *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int GetOrder(const TAPISTR_20 UserNo, const TapAPIOrderQryReq *pReqInfo, TapAPIOrderInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);

	//int qryOrderProcess(string userNo, unsigned int request, const dict &req);
	//int GetFill(const TAPISTR_20 UserNo, const TapAPIFillQryReq *pReqInfo, TapAPIFillInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int GetPosition(const TAPISTR_20 UserNo, const TapAPIPositionQryReq *pReqInfo, TapAPIPositionInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int GetClose(const TAPISTR_20 UserNo, const TapAPICloseQryReq *pReqInfo, TapAPICloseInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast);
	//int qryDeepQuote(string userNo, unsigned int nRequestID, const dict &req);
	int getExchangeStateInfo(string userNo, unsigned int nDataSeqID, unsigned int nOutLen, char flag);
	int getUpperChannel(string userNo, unsigned int nDataSeqID,  unsigned int nOutLen, char flag);
	int getCurrency(string userNo, unsigned int nDataSeqID,  unsigned int nOutLen, char flag);

	int qryAccountRent(string userNo, unsigned int nRequestID, const dict &req);
	/*
	/*------------//以下北斗星专用
	int requestVertificateCode(string userNo, unsigned int nSessionID, const dict &req);    //北斗星专用 //nSessionID
	int setVertificateCode(string userNo, unsigned int nSessionID, string VertificateCode);    //北斗星专用 //nSessionID

	int modifyOrder(string userNo, unsigned int nRequestID, const dict &data);    //北斗星专用

	//qry
	int qryAccountRent(string userNo, unsigned int nRequestID, const dict &data);

    int qryAccountFeeRent(string userNo, unsigned int nRequestID, const dict &data);

    int qryAccountMarginRent(string userNo, unsigned int nRequestID, const dict &data);

    int qryAccountCashAdjust(string userNo, unsigned int nRequestID, const dict &data);

    int qryBill(string userNo, unsigned int nRequestID, const dict &data);

    int qryHisOrder(string userNo, unsigned int nRequestID, const dict &data);

    int qryHisOrderProcess(string userNo, unsigned int nRequestID, const dict &data);

    int qryHisFill(string userNo, unsigned int nRequestID, const dict &data);

    int qryHisPosition(string userNo, unsigned int nRequestID, const dict &data);

    int qryHisDelivery(string userNo, unsigned int nRequestID, const dict &data);

    int qryManageInfoForEStar(string userNo, unsigned int nRequestID, const dict &data);

    int qrySystemParameter(string userNo, unsigned int nRequestID, const dict &data);

    int qryTradeCenterFrontAddress(string userNo, unsigned int nRequestID, const dict &data);

    int qryTradeMessage(string userNo, unsigned int nRequestID, const dict &data);    
	*/

};