//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnoes.h"
#include "pybind11/pybind11.h"
#include "oes/oes_api/samples/cpp_sample/oes_client_sample.h"


using namespace pybind11;
using namespace Quant360;

//常量
#define ONBUSINESSREJECT 0
#define ONORDERINSERT 1
#define ONORDERREPORT 2
#define ONTRADEREPORT 3
#define ONCASHASSETVARIATION 4
#define ONSTOCKHOLDINGVARIATION 5
#define ONOPTIONHOLDINGVARIATION 6
#define ONOPTIONUNDERLYINGHOLDINGVARIATION 7
#define ONSETTLEMENTCONFIRMEDRPT 8
#define ONFUNDTRSFREJECT 9
#define ONFUNDTRSFREPORT 10
#define ONMARKETSTATE 11
#define ONNOTIFYREPORT 12
#define ONREPORTSYNCHRONIZATIONRSP 13
#define ONQUERYORDER 14
#define ONQUERYTRADE 15
#define ONQUERYCASHASSET 16
#define ONQUERYSTKHOLDING 17
#define ONQUERYLOTWINNING 18
#define ONQUERYCUSTINFO 19
#define ONQUERYINVACCT 20
#define ONQUERYCOMMISSIONRATE 21
#define ONQUERYFUNDTRANSFERSERIAL 22
#define ONQUERYISSUE 23
#define ONQUERYSTOCK 24
#define ONQUERYETF 25
#define ONQUERYETFCOMPONENT 26
#define ONQUERYMARKETSTATE 27
#define ONQUERYOPTION 28
#define ONQUERYOPTHOLDING 29
#define ONQUERYOPTUNDERLYINGHOLDING 30
#define ONQUERYOPTPOSITIONLIMIT 31
#define ONQUERYOPTPURCHASELIMIT 32
#define ONQUERYOPTEXERCISEASSIGN 33
#define ONQUERYNOTIFYINFO 34 
#define ONCONNECTED 35
#define ONDISCONNECTED 36
///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public OesClientSpi
{
private:
	OesClientApi* api;            //API对象
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




	/* 连接或重新连接完成后的回调函数 */
	virtual int32       OnConnected(eOesApiChannelTypeT channelType, OesApiSessionInfoT *pSessionInfo, OesApiSubscribeInfoT *pSubscribeInfo = NULL);
	/* 连接断开后的回调函数 */
	virtual int32       OnDisconnected(eOesApiChannelTypeT channelType, OesApiSessionInfoT *pSessionInfo);

	/* 委托拒绝回报 */
	virtual void        OnBusinessReject(const OesRptMsgHeadT *pRptMsgHead, const OesOrdRejectT *pOrderReject);
	/* 委托已收回报 */
	virtual void        OnOrderInsert(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderInsert);
	/* 委托确认回报 */
	virtual void        OnOrderReport(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderReport);
	/* 成交确认回报 */
	virtual void        OnTradeReport(const OesRptMsgHeadT *pRptMsgHead, const OesTrdCnfmT *pTradeReport);
	/* 资金变动通知 */
	virtual void        OnCashAssetVariation(const OesCashAssetReportT *pCashAssetRpt);
	/* 股票持仓变动通知 */
	virtual void        OnStockHoldingVariation(const OesStkHoldingReportT *pStkHoldingRpt);
	/* 期权持仓变动通知 (适用于期权业务) */
	virtual void        OnOptionHoldingVariation(const OesOptHoldingReportT *pOptHoldingRpt);
	/* 期权标的持仓变动通知 (适用于期权业务) */
	virtual void        OnOptionUnderlyingHoldingVariation(const OesOptUnderlyingHoldingReportT *pUnderlyingHoldingRpt);
	/* 期权结算单确认回报 (适用于期权业务) */
	virtual void        OnSettlementConfirmedRpt(const OesRptMsgHeadT *pRptMsgHead, const OesOptSettlementConfirmReportT *pCnfmSettlementRpt);
	/* 出入金委托拒绝回报 */
	virtual void        OnFundTrsfReject(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfRejectT *pFundTrsfReject);
	/* 出入金委托执行回报 */
	virtual void        OnFundTrsfReport(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfReportT *pFundTrsfReport);
	/* 市场状态信息通知 */
	virtual void        OnMarketState(const OesMarketStateItemT *pMarketStateItem);
	/* 通知消息回报 */
	virtual void        OnNotifyReport(const OesNotifyInfoReportT *pNotifyInfoRpt);
	/* 回报同步请求的响应 */
	virtual void        OnReportSynchronizationRsp(const OesReportSynchronizationRspT *pReportSynchronization);

	/* 查询委托信息回调 */
	virtual void        OnQueryOrder(const OesOrdItemT *pOrder, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询成交信息回调 */
	virtual void        OnQueryTrade(const OesTrdItemT *pTrade, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询资金信息回调 */
	virtual void        OnQueryCashAsset(const OesCashAssetItemT *pCashAsset, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询股票持仓信息回调 */
	virtual void        OnQueryStkHolding(const OesStkHoldingItemT *pStkHolding, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询配号、中签信息回调 */
	virtual void        OnQueryLotWinning(const OesLotWinningItemT *pLotWinning, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询客户信息回调 */
	virtual void        OnQueryCustInfo(const OesCustItemT *pCust, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询股东账户信息回调 */
	virtual void        OnQueryInvAcct(const OesInvAcctItemT *pInvAcct, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询佣金信息回调 */
	virtual void        OnQueryCommissionRate(const OesCommissionRateItemT *pCommissionRate, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询出入金流水信息回调 */
	virtual void        OnQueryFundTransferSerial(const OesFundTransferSerialItemT *pFundTrsf, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询证券发行信息回调 */
	virtual void        OnQueryIssue(const OesIssueItemT *pIssue, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询证券信息回调 */
	virtual void        OnQueryStock(const OesStockItemT *pStock, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询ETF产品信息回调 */
	virtual void        OnQueryEtf(const OesEtfItemT *pEtf, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询ETF成分股信息回调 */
	virtual void        OnQueryEtfComponent(const OesEtfComponentItemT *pEtfComponent, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询市场状态信息回调 */
	virtual void        OnQueryMarketState(const OesMarketStateItemT *pMarketState, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询期权产品信息回调 (适用于期权业务) */
	virtual void        OnQueryOption(const OesOptionItemT *pOption, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询期权持仓信息回调 (适用于期权业务) */
	virtual void        OnQueryOptHolding(const OesOptHoldingItemT *pOptHolding, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询期权标的持仓信息回调 (适用于期权业务) */
	virtual void        OnQueryOptUnderlyingHolding(const OesOptUnderlyingHoldingItemT *pUnderlyingHld, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询期权限仓额度信息回调 (适用于期权业务) */
	virtual void        OnQueryOptPositionLimit(const OesOptPositionLimitItemT *pPositionLimit, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询期权限购额度信息回调 (适用于期权业务) */
	virtual void        OnQueryOptPurchaseLimit(const OesOptPurchaseLimitItemT *pPurchaseLimit, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询期权行权指派信息回调 (适用于期权业务) */
	virtual void        OnQueryOptExerciseAssign(const OesOptExerciseAssignItemT *pExerciseAssign, const OesQryCursorT *pCursor, int32 requestId);
	/* 查询通知消息回调 */
	virtual void        OnQueryNotifyInfo(const OesNotifyInfoItemT *pNotifyInfo, const OesQryCursorT *pCursor, int32 requestId);



    //-------------------------------------------------------------------------------------
    //task：任务
    //-------------------------------------------------------------------------------------
    void processTask();

	int32 processConnected(Task *task);

	int32 processDisconnected(Task *task);

	void processBusinessReject(Task *task);

	void processOrderInsert(Task *task);

	void processOrderReport(Task *task);

	void processTradeReport(Task *task);

	void processCashAssetVariation(Task *task);

	void processStockHoldingVariation(Task *task);

	void processOptionHoldingVariation(Task *task);

	void processOptionUnderlyingHoldingVariation(Task *task);

	void processSettlementConfirmedRpt(Task *task);

	void processFundTrsfReject(Task *task);

	void processFundTrsfReport(Task *task);

	void processMarketState(Task *task);

	void processNotifyReport(Task *task);

	void processReportSynchronizationRsp(Task *task);

	void processQueryOrder(Task *task);

	void processQueryTrade(Task *task);

	void processQueryCashAsset(Task *task);

	void processQueryStkHolding(Task *task);

	void processQueryLotWinning(Task *task);

	void processQueryCustInfo(Task *task);

	void processQueryInvAcct(Task *task);

	void processQueryCommissionRate(Task *task);

	void processQueryFundTransferSerial(Task *task);

	void processQueryIssue(Task *task);

	void processQueryStock(Task *task);

	void processQueryEtf(Task *task);

	void processQueryEtfComponent(Task *task);

	void processQueryMarketState(Task *task);

	void processQueryOption(Task *task);

	void processQueryOptHolding(Task *task);

	void processQueryOptUnderlyingHolding(Task *task);

	void processQueryOptPositionLimit(Task *task);

	void processQueryOptPurchaseLimit(Task *task);

	void processQueryOptExerciseAssign(Task *task);

	void processQueryNotifyInfo(Task *task);



    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------
    

	virtual void onConnected(int channelType, const dict &data) {};

	virtual void onDisconnected(int channelType, const dict &data) {};

	virtual void onBusinessReject(const dict &error, const dict &data) {};

	virtual void onOrderInsert(const dict &error, const dict &data) {};

	virtual void onOrderReport(const dict &error, const dict &data) {};

	virtual void onTradeReport(const dict &error, const dict &data) {};

	virtual void onCashAssetVariation(const dict &data) {};

	virtual void onStockHoldingVariation(const dict &data) {};

	virtual void onOptionHoldingVariation(const dict &data) {};

	virtual void onOptionUnderlyingHoldingVariation(const dict &data) {};

	virtual void onSettlementConfirmedRpt(const dict &error, const dict &data) {};

	virtual void onFundTrsfReject(const dict &error, const dict &data) {};

	virtual void onFundTrsfReport(const dict &error, const dict &data) {};

	virtual void onMarketState(const dict &data) {};

	virtual void onNotifyReport(const dict &data) {};

	virtual void onReportSynchronizationRsp(const dict &data) {};

	virtual void onQueryOrder(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryTrade(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryCashAsset(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryStkHolding(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryLotWinning(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryCustInfo(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryInvAcct(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryCommissionRate(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryFundTransferSerial(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryIssue(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryStock(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryEtf(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryEtfComponent(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryMarketState(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOption(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptHolding(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptUnderlyingHolding(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptPositionLimit(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptPurchaseLimit(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptExerciseAssign(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryNotifyInfo(const dict &data, const dict &error, int reqid) {};



    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------

	bool loadCfg(string pCfgFile);

	bool setCustomizedIpAndMac(string pIpStr, string pMacStr);

	bool setCustomizedIp(string pIpStr);

	bool setCustomizedMac(string pMacStr);

	bool setCustomizedDriverId(string pDriverStr);

	void setThreadUsername(string pUsername);

	void setThreadPassword(string pPassword);

	void setThreadEnvId(int clEnvId);

	void setThreadSubscribeEnvId(int subscribeEnvId);

	void init();

    int exit();

	int sendOrder(const dict &req);

	int sendCancelOrder(const dict &req);

	int sendOptSettlementConfirm(const dict &req);

	int getTradingDay();

	int getClientOverview(const dict &req);

	int queryOrder(const dict &req, int reqid);

	int queryTrade(const dict &req, int reqid);

	int queryCashAsset(const dict &req, int reqid);

	int queryStkHolding(const dict &req, int reqid);

	int queryLotWinning(const dict &req, int reqid);

	int queryCustInfo(const dict &req, int reqid);

	int queryInvAcct(const dict &req, int reqid);

	int queryCommissionRate(const dict &req, int reqid);

	int queryFundTransferSerial(const dict &req, int reqid);

	int queryIssue(const dict &req, int reqid);

	int queryStock(const dict &req, int reqid);

	int queryEtf(const dict &req, int reqid);

	int queryEtfComponent(const dict &req, int reqid);

	int queryMarketState(const dict &req, int reqid);

	int queryCounterCash(string pCashAcctId, const dict &req, int reqid);

	int queryOption(const dict &req, int reqid);

	int queryOptHolding(const dict &req, int reqid);

	int queryOptUnderlyingHolding(const dict &req, int reqid);

	int queryOptPositionLimit(const dict &req, int reqid);

	int queryOptPurchaseLimit(const dict &req, int reqid);

	int queryOptExerciseAssign(const dict &req, int reqid);

	int queryOptSettlementStatement(string pCustId, string pSettleBuf, int bufSize, int reqid);

	int queryNotifyInfo(const dict &req, int reqid);


};
