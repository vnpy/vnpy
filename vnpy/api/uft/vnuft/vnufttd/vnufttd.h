//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnuft.h"
#include "pybind11/pybind11.h"
#include "uft/HSTradeApi.h"


using namespace pybind11;

//常量
#define ONFRONTCONNECTED 0
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONRSPAUTHENTICATE 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERPASSWORDUPDATE 4
#define ONRSPERRORORDERINSERT 5
#define ONRSPORDERACTION 6
#define ONRSPERROREXERCISEORDERINSERT 7
#define ONRSPEXERCISEORDERACTION 8
#define ONRSPERRORLOCKINSERT 9
#define ONRSPFORQUOTEINSERT 10
#define ONRSPERRORCOMBACTIONINSERT 11
#define ONRSPQUERYMAXORDERVOLUME 12
#define ONRSPQUERYLOCKVOLUME 13
#define ONRSPQUERYEXERCISEVOLUME 14
#define ONRSPQRYPOSITION 15
#define ONRSPQRYTRADINGACCOUNT 16
#define ONRSPQRYORDER 17
#define ONRSPQRYTRADE 18
#define ONRSPQRYEXERCISE 19
#define ONRSPQRYLOCK 20
#define ONRSPQRYCOMBACTION 21
#define ONRSPQRYPOSITIONCOMBINEDETAIL 22
#define ONRSPQRYINSTRUMENT 23
#define ONRSPQRYCOVEREDSHORT 24
#define ONRSPQRYEXERCISEASSIGN 25
#define ONRSPTRANSFER 26
#define ONRSPQRYTRANSFER 27
#define ONRSPQUERYBANKBALANCE 28
#define ONRSPQUERYBANKACCOUNT 29
#define ONRSPQUERYBILLCONTENT 30
#define ONRSPBILLCONFIRM 31
#define ONRSPQRYMARGIN 32
#define ONRSPQRYCOMMISSION 33
#define ONRSPQRYPOSITIONDETAIL 34
#define ONRSPQRYEXCHANGERATE 35
#define ONRSPQRYSYSCONFIG 36
#define ONRSPQRYDEPTHMARKETDATA 37
#define ONRTNTRADE 38
#define ONRTNORDER 39
#define ONRTNEXERCISE 40
#define ONRTNCOMBACTION 41
#define ONRTNLOCK 42



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public CHSTradeSpi
{
private:
	CHSTradeApi* api;                     //API对象
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

	/// Description: 当客户端与交易后台开始建立通信连接，连接成功后此方法被回调。
	virtual void OnFrontConnected();

	/// Description:当客户端与交易后台通信连接异常时，该方法被调用。
	/// Others     :通过GetApiErrorMsg(nResult)获取详细错误信息。
	virtual void OnFrontDisconnected(int nResult);

	/// Description:客户认证
	virtual void OnRspAuthenticate(CHSRspAuthenticateField *pRspAuthenticate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:客户登录
	virtual void OnRspUserLogin(CHSRspUserLoginField *pRspUserLogin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:密码更改
	virtual void OnRspUserPasswordUpdate(CHSRspUserPasswordUpdateField *pRspUserPasswordUpdate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:报单录入
	/// Others     :报单错误此方法被回调，pRspOrderInsert保存了请求时出错的结构体数据。
	virtual void OnRspErrorOrderInsert(CHSRspOrderInsertField *pRspOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:撤单
	virtual void OnRspOrderAction(CHSRspOrderActionField *pRspOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:行权录入
	/// Others     :行权录入错误此方法被回调，pRspExerciseOrderInsert保存了请求时出错的结构体数据。
	virtual void OnRspErrorExerciseOrderInsert(CHSRspExerciseOrderInsertField *pRspExerciseOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:行权撤单
	virtual void OnRspExerciseOrderAction(CHSRspExerciseOrderActionField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:锁定录入
	/// Others     :锁定错误此方法被回调，pRspExerciseOrderAction保存了请求时出错的结构体数据。
	virtual void OnRspErrorLockInsert(CHSRspLockInsertField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:询价录入
	virtual void OnRspForQuoteInsert(CHSRspForQuoteInsertField *pRspForQuoteInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:申请组合录入
	virtual void OnRspErrorCombActionInsert(CHSRspCombActionInsertField *pRspCombActionInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:最大报单数量获取
	virtual void OnRspQueryMaxOrderVolume(CHSRspQueryMaxOrderVolumeField *pRspQueryMaxOrderVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:可锁定数量获取
	virtual void OnRspQueryLockVolume(CHSRspQueryLockVolumeField *pRspQueryLockVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:可行权数量获取
	virtual void OnRspQueryExerciseVolume(CHSRspQueryExerciseVolumeField *pRspQueryExerciseVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:持仓查询
	virtual void OnRspQryPosition(CHSRspQryPositionField *pRspQryPosition, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:资金账户查询
	virtual void OnRspQryTradingAccount(CHSRspQryTradingAccountField *pRspQryTradingAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:报单查询
	virtual void OnRspQryOrder(CHSOrderField *pRspQryOrder, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:成交查询
	virtual void OnRspQryTrade(CHSTradeField *pRspQryTrade, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:行权查询
	virtual void OnRspQryExercise(CHSExerciseField *pRspQryExercise, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:锁定查询
	virtual void OnRspQryLock(CHSLockField *pRspQryLock, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:申请组合查询
	virtual void OnRspQryCombAction(CHSCombActionField *pRspQryCombAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:组合持仓明细查询
	virtual void OnRspQryPositionCombineDetail(CHSRspQryPositionCombineDetailField *pRspQryPositionCombineDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:合约信息查询
	virtual void OnRspQryInstrument(CHSRspQryInstrumentField *pRspQryInstrument, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:备兑缺口查询
	virtual void OnRspQryCoveredShort(CHSRspQryCoveredShortField *pRspQryCoveredShort, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:行权指派查询
	virtual void OnRspQryExerciseAssign(CHSRspQryExerciseAssignField *pRspQryExerciseAssign, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:银行转账
	virtual void OnRspTransfer(CHSRspTransferField *pRspTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:银行转账查询
	virtual void OnRspQryTransfer(CHSRspQryTransferField *pRspQryTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:银行余额查询
	virtual void OnRspQueryBankBalance(CHSRspQueryBankBalanceField *pRspQueryBankBalance, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:银行账户查询
	virtual void OnRspQueryBankAccount(CHSRspQueryBankAccountField *pRspQueryBankAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:客户账单查询
	virtual void OnRspQueryBillContent(CHSRspQueryBillContentField *pRspQueryBillContent, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:客户账单确认
	virtual void OnRspBillConfirm(CHSRspBillConfirmField *pRspBillConfirm, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:保证金查询
	virtual void OnRspQryMargin(CHSRspQryMarginField *pRspQryMargin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:手续费查询
	virtual void OnRspQryCommission(CHSRspQryCommissionField *pRspQryCommission, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:持仓明细查询
	virtual void OnRspQryPositionDetail(CHSRspQryPositionDetailField *pRspQryPositionDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	// Description:汇率查询
	virtual void OnRspQryExchangeRate(CHSRspQryExchangeRateField *pRspQryExchangeRate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:经纪公司配置参数查询
	virtual void OnRspQrySysConfig(CHSRspQrySysConfigField *pRspQrySysConfig, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description:行情查询
	virtual void OnRspQryDepthMarketData(CHSDepthMarketDataField *pRspQryDepthMarketData, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	/// Description: 主推-成交回报
	virtual void OnRtnTrade(CHSTradeField *pRtnTrade);

	/// Description: 主推-报单回报
	virtual void OnRtnOrder(CHSOrderField *pRtnOrder);

	/// Description: 主推-行权
	virtual void OnRtnExercise(CHSExerciseField *pRtnExercise);

	/// Description: 主推-申请组合
	virtual void OnRtnCombAction(CHSCombActionField *pRtnCombAction);

	/// Description: 主推-锁定
	virtual void OnRtnLock(CHSLockField *pRtnLock);

    //-------------------------------------------------------------------------------------
    //task：任务
    //-------------------------------------------------------------------------------------
    void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processRspAuthenticate(Task *task);

	void processRspUserLogin(Task *task);

	void processRspUserPasswordUpdate(Task *task);

	void processRspErrorOrderInsert(Task *task);

	void processRspOrderAction(Task *task);

	void processRspErrorExerciseOrderInsert(Task *task);

	void processRspExerciseOrderAction(Task *task);

	void processRspErrorLockInsert(Task *task);

	void processRspForQuoteInsert(Task *task);

	void processRspErrorCombActionInsert(Task *task);

	void processRspQueryMaxOrderVolume(Task *task);

	void processRspQueryLockVolume(Task *task);

	void processRspQueryExerciseVolume(Task *task);

	void processRspQryPosition(Task *task);

	void processRspQryTradingAccount(Task *task);

	void processRspQryOrder(Task *task);

	void processRspQryTrade(Task *task);

	void processRspQryExercise(Task *task);

	void processRspQryLock(Task *task);

	void processRspQryCombAction(Task *task);

	void processRspQryPositionCombineDetail(Task *task);

	void processRspQryInstrument(Task *task);

	void processRspQryCoveredShort(Task *task);

	void processRspQryExerciseAssign(Task *task);

	void processRspTransfer(Task *task);

	void processRspQryTransfer(Task *task);

	void processRspQueryBankBalance(Task *task);

	void processRspQueryBankAccount(Task *task);

	void processRspQueryBillContent(Task *task);

	void processRspBillConfirm(Task *task);

	void processRspQryMargin(Task *task);

	void processRspQryCommission(Task *task);

	void processRspQryPositionDetail(Task *task);

	void processRspQryExchangeRate(Task *task);

	void processRspQrySysConfig(Task *task);

	void processRspQryDepthMarketData(Task *task);

	void processRtnTrade(Task *task);

	void processRtnOrder(Task *task);

	void processRtnExercise(Task *task);

	void processRtnCombAction(Task *task);

	void processRtnLock(Task *task);



    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------
    

	virtual void onFrontConnected() {};

	virtual void onFrontDisconnected(int reqid) {};

	virtual void onRspAuthenticate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspErrorOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspErrorExerciseOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspExerciseOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspErrorLockInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspForQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspErrorCombActionInsert(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQueryMaxOrderVolume(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQueryLockVolume(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQueryExerciseVolume(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryExercise(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryLock(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryCombAction(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryPositionCombineDetail(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryCoveredShort(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryExerciseAssign(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspTransfer(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryTransfer(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQueryBankBalance(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQueryBankAccount(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQueryBillContent(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspBillConfirm(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryMargin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryCommission(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryPositionDetail(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryExchangeRate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQrySysConfig(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryDepthMarketData(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnTrade(const dict &data) {};

	virtual void onRtnOrder(const dict &data) {};

	virtual void onRtnExercise(const dict &data) {};

	virtual void onRtnCombAction(const dict &data) {};

	virtual void onRtnLock(const dict &data) {};



    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------



    void releaseApi(); //

    int init(string pszLicFile, string pszSafeLevel, string pszPwd, string pszSslFile, string pszSslPwd);

    int join(); //

	int exit(); //

	int rgisterSubModel(string pszSubModel); //

	int registerFront(string pszFrontAddress); //

	int registerFensServer(string pszFensAddress, string pszAccountID);//

	///void registerSpi(CHSTradeSpi pSpi);

	string getApiErrorMsg(int nErrorCode); //

	int getTradingDate(); //

	int reqAuthenticate(const dict &req, int reqid);

	int reqUserLogin(const dict &req, int reqid);

	int reqUserPasswordUpdate(const dict &req, int reqid);

	int reqOrderInsert(const dict &req, int reqid);

	int reqOrderAction(const dict &req, int reqid);

	int reqExerciseOrderInsert(const dict &req, int reqid);

	int reqExerciseOrderAction(const dict &req, int reqid);

	int reqLockInsert(const dict &req, int reqid);

	int reqForQuoteInsert(const dict &req, int reqid);

	int reqCombActionInsert(const dict &req, int reqid);

	int reqQueryMaxOrderVolume(const dict &req, int reqid);

	int reqQueryLockVolume(const dict &req, int reqid);

	int reqQueryExerciseVolume(const dict &req, int reqid);

	int reqQryPosition(const dict &req, int reqid);

	int reqQryTradingAccount(const dict &req, int reqid);

	int reqQryOrder(const dict &req, int reqid);

	int reqQryTrade(const dict &req, int reqid);

	int reqQryExercise(const dict &req, int reqid);

	int reqQryLock(const dict &req, int reqid);

	int reqQryCombAction(const dict &req, int reqid);

	int reqQryPositionCombineDetail(const dict &req, int reqid);

	int reqQryInstrument(const dict &req, int reqid);

	int reqQryCoveredShort(const dict &req, int reqid);

	int reqQryExerciseAssign(const dict &req, int reqid);

	int reqTransfer(const dict &req, int reqid);

	int reqQryTransfer(const dict &req, int reqid);

	int reqQueryBankBalance(const dict &req, int reqid);

	int reqQueryBankAccount(const dict &req, int reqid);

	int reqQueryBillContent(const dict &req, int reqid);

	int reqBillConfirm(const dict &req, int reqid);

	int reqQryMargin(const dict &req, int reqid);

	int reqQryCommission(const dict &req, int reqid);

	int reqQryExchangeRate(const dict &req, int reqid);

	int reqQryPositionDetail(const dict &req, int reqid);

	int reqQrySysConfig(const dict &req, int reqid);

	int reqQryDepthMarketData(const dict &req, int reqid);


};
