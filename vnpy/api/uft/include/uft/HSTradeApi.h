/**
* @author 寿贺飞
* @company 恒生电子股份有限公司
* @file HSTradeApi.h
* @brief 定义了交易接口
* @date    20170927
*/
#ifndef _HS_TRADE_API_H_
#define _HS_TRADE_API_H_

#include "HSStruct.h"

#ifdef WIN32
    #define TRADE_API_EXPORT
#else
    #ifdef HSTRADEAPI_EXPORTS
        #define TRADE_API_EXPORT __attribute__((visibility("default"))) 
    #else
        #define TRADE_API_EXPORT
    #endif
#endif

/// 回调虚类
class CHSTradeSpi
{
public:
    /// Description: 当客户端与交易后台开始建立通信连接，连接成功后此方法被回调。
    virtual void OnFrontConnected(){};

    /// Description:当客户端与交易后台通信连接异常时，该方法被调用。
    /// Others     :通过GetApiErrorMsg(nResult)获取详细错误信息。
    virtual void OnFrontDisconnected(int nResult){};

    /// Description:客户认证
    virtual void OnRspAuthenticate(CHSRspAuthenticateField *pRspAuthenticate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:客户登录
    virtual void OnRspUserLogin(CHSRspUserLoginField *pRspUserLogin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:密码更改
    virtual void OnRspUserPasswordUpdate(CHSRspUserPasswordUpdateField *pRspUserPasswordUpdate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:报单录入
    /// Others     :报单错误此方法被回调，pRspOrderInsert保存了请求时出错的结构体数据。
    virtual void OnRspErrorOrderInsert(CHSRspOrderInsertField *pRspOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:撤单
    virtual void OnRspOrderAction(CHSRspOrderActionField *pRspOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:行权录入
    /// Others     :行权录入错误此方法被回调，pRspExerciseOrderInsert保存了请求时出错的结构体数据。
    virtual void OnRspErrorExerciseOrderInsert(CHSRspExerciseOrderInsertField *pRspExerciseOrderInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:行权撤单
    virtual void OnRspExerciseOrderAction(CHSRspExerciseOrderActionField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:锁定录入
    /// Others     :锁定错误此方法被回调，pRspExerciseOrderAction保存了请求时出错的结构体数据。
    virtual void OnRspErrorLockInsert(CHSRspLockInsertField *pRspExerciseOrderAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:询价录入
    virtual void OnRspForQuoteInsert(CHSRspForQuoteInsertField *pRspForQuoteInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:申请组合录入
    virtual void OnRspErrorCombActionInsert(CHSRspCombActionInsertField *pRspCombActionInsert, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:最大报单数量获取
    virtual void OnRspQueryMaxOrderVolume(CHSRspQueryMaxOrderVolumeField *pRspQueryMaxOrderVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:可锁定数量获取
    virtual void OnRspQueryLockVolume(CHSRspQueryLockVolumeField *pRspQueryLockVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:可行权数量获取
    virtual void OnRspQueryExerciseVolume(CHSRspQueryExerciseVolumeField *pRspQueryExerciseVolume, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:持仓查询
    virtual void OnRspQryPosition(CHSRspQryPositionField *pRspQryPosition, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:资金账户查询
    virtual void OnRspQryTradingAccount(CHSRspQryTradingAccountField *pRspQryTradingAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:报单查询
    virtual void OnRspQryOrder(CHSOrderField *pRspQryOrder, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:成交查询
    virtual void OnRspQryTrade(CHSTradeField *pRspQryTrade, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:行权查询
    virtual void OnRspQryExercise(CHSExerciseField *pRspQryExercise, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:锁定查询
    virtual void OnRspQryLock(CHSLockField *pRspQryLock, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:申请组合查询
    virtual void OnRspQryCombAction(CHSCombActionField *pRspQryCombAction, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:组合持仓明细查询
    virtual void OnRspQryPositionCombineDetail(CHSRspQryPositionCombineDetailField *pRspQryPositionCombineDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:合约信息查询
    virtual void OnRspQryInstrument(CHSRspQryInstrumentField *pRspQryInstrument, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:备兑缺口查询
    virtual void OnRspQryCoveredShort(CHSRspQryCoveredShortField *pRspQryCoveredShort, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:行权指派查询
    virtual void OnRspQryExerciseAssign(CHSRspQryExerciseAssignField *pRspQryExerciseAssign, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:银行转账
    virtual void OnRspTransfer(CHSRspTransferField *pRspTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:银行转账查询
    virtual void OnRspQryTransfer(CHSRspQryTransferField *pRspQryTransfer, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:银行余额查询
    virtual void OnRspQueryBankBalance(CHSRspQueryBankBalanceField *pRspQueryBankBalance, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:银行账户查询
    virtual void OnRspQueryBankAccount(CHSRspQueryBankAccountField *pRspQueryBankAccount, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:客户账单查询
    virtual void OnRspQueryBillContent(CHSRspQueryBillContentField *pRspQueryBillContent, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:客户账单确认
    virtual void OnRspBillConfirm(CHSRspBillConfirmField *pRspBillConfirm, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:保证金查询
    virtual void OnRspQryMargin(CHSRspQryMarginField *pRspQryMargin, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:手续费查询
    virtual void OnRspQryCommission(CHSRspQryCommissionField *pRspQryCommission, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:持仓明细查询
    virtual void OnRspQryPositionDetail(CHSRspQryPositionDetailField *pRspQryPositionDetail, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    // Description:汇率查询
    virtual void OnRspQryExchangeRate(CHSRspQryExchangeRateField *pRspQryExchangeRate, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:经纪公司配置参数查询
    virtual void OnRspQrySysConfig(CHSRspQrySysConfigField *pRspQrySysConfig, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description:行情查询
    virtual void OnRspQryDepthMarketData(CHSDepthMarketDataField *pRspQryDepthMarketData, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

    /// Description: 主推-成交回报
    virtual void OnRtnTrade(CHSTradeField *pRtnTrade) {};

    /// Description: 主推-报单回报
    virtual void OnRtnOrder(CHSOrderField *pRtnOrder) {};

    /// Description: 主推-行权
    virtual void OnRtnExercise(CHSExerciseField *pRtnExercise) {};

    /// Description: 主推-申请组合
    virtual void OnRtnCombAction(CHSCombActionField *pRtnCombAction) {};

    /// Description: 主推-锁定
    virtual void OnRtnLock(CHSLockField *pRtnLock) {};
};

///交易
class  CHSTradeApi
{
public:
    /// Description: 删除接口对象本身
    virtual void ReleaseApi() = 0;

    /// Description: 初始化连接
    ///              pszLicFile            通讯证书
    ///              pszSafeLevel          安全级别
    ///              pszPwd                通讯密码
    ///              pszSslFile            SSL证书
    ///              pszSslPwd             SSL密码
    virtual int Init(const char *pszLicFile, const char *pszSafeLevel = "", const char *pszPwd = "", const char *pszSslFile = "", const char *pszSslPwd = "") = 0;

    /// Description: API和交易柜台建立连接，连接建立成功后，主线程会等待用户操作子线程退出
    /// Return     : int 0表示连接建立成功，否则表示失败，通过调用GetApiErrorMsg可以获取详细错误信息
    virtual int Join() = 0;

    /// Description: 注册订阅模式（暂未支持）
    /// Input      : 订阅方式
    ///                 HS_TERT_RESTART://从本交易日开始重传
    ///                 HS_TERT_RESUME: //从上次收到的续传
    ///                 HS_TERT_QUICK:  //从登录后最新的开始传
    virtual int RegisterSubModel(const char *pszSubModel) = 0;

    /// Description: 注册前置机网络地址
    /// Input      : pszFrontAddress           前置机网络地址 如：”tcp://127.0.0.1:17001”
    /// Return     : int 0表示设置成功，否则表示失败，通过调用GetApiErrorMsg可以获取详细错误信息
    virtual int RegisterFront(const char *pszFrontAddress) = 0;

    /// Description: 注册Fens网络地址
    /// Input      : pszFensAddress            Fens网络地址
    /// Input      : pszAccountID              账号
    /// Return     : int 0表示设置成功，否则表示失败，通过调用GetApiErrorMsg可以获取详细错误信息
    virtual int RegisterFensServer(const char *pszFensAddress, const char *pszAccountID) = 0;

    /// Description: 注册回调接口
    /// Input      : pSpi            派生自回调接口类的实例     
    virtual void RegisterSpi(CHSTradeSpi *pSpi) = 0;

    /// Description: 获得错误详细信息
    virtual const char* GetApiErrorMsg(int nErrorCode) = 0;

    /// Description: 获取当前交易日期
    virtual int GetTradingDate() = 0;

    /// Description: 接入认证 
    virtual int ReqAuthenticate(CHSReqAuthenticateField *pReqAuthenticate,int nRequestID) = 0;

    /// Description:客户登录
    virtual int  ReqUserLogin(CHSReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

    /// Description:密码更改
    virtual int  ReqUserPasswordUpdate(CHSReqUserPasswordUpdateField *pReqUserPasswordUpdate, int nRequestID) = 0;

    /// Description:报单录入
    virtual int  ReqOrderInsert(CHSReqOrderInsertField *pReqOrderInsert, int nRequestID) = 0;

    /// Description:撤单
    virtual int  ReqOrderAction(CHSReqOrderActionField *pReqOrderAction, int nRequestID) = 0;

    /// Description:行权录入
    virtual int  ReqExerciseOrderInsert(CHSReqExerciseOrderInsertField *pReqExerciseOrderInsert, int nRequestID) = 0;

    /// Description:行权撤单
    virtual int  ReqExerciseOrderAction(CHSReqExerciseOrderActionField *pReqExerciseOrderAction, int nRequestID) = 0;

    /// Description:锁定录入
    virtual int  ReqLockInsert(CHSReqLockInsertField *pReqLockInsert, int nRequestID) = 0;

    /// Description:询价录入
    virtual int  ReqForQuoteInsert(CHSReqForQuoteInsertField *pReqForQuoteInsert, int nRequestID) = 0;

    /// Description:申请组合录入
    virtual int  ReqCombActionInsert(CHSReqCombActionInsertField *pReqCombActionInsert, int nRequestID) = 0;

    /// Description:最大报单数量获取
    virtual int  ReqQueryMaxOrderVolume(CHSReqQueryMaxOrderVolumeField *pReqQueryMaxOrderVolume, int nRequestID) = 0;

    /// Description:可锁定数量获取
    virtual int  ReqQueryLockVolume(CHSReqQueryLockVolumeField *pReqQueryLockVolume, int nRequestID) = 0;

    /// Description:可行权数量获取
    virtual int  ReqQueryExerciseVolume(CHSReqQueryExerciseVolumeField *pReqQueryExerciseVolume, int nRequestID) = 0;

    /// Description:持仓汇总查询
    virtual int  ReqQryPosition(CHSReqQryPositionField *pReqQryPosition, int nRequestID) = 0;

    /// Description:资金账户查询
    virtual int  ReqQryTradingAccount(CHSReqQryTradingAccountField *pReqQryTradingAccount, int nRequestID) = 0;

    /// Description:报单查询
    virtual int  ReqQryOrder(CHSReqQryOrderField *pReqQryOrder, int nRequestID) = 0;

    /// Description:成交查询
    virtual int  ReqQryTrade(CHSReqQryTradeField *pReqQryTrade, int nRequestID) = 0;

    /// Description:行权查询
    virtual int  ReqQryExercise(CHSReqQryExerciseField *pReqQryExercise, int nRequestID) = 0;

    /// Description:锁定查询
    virtual int  ReqQryLock(CHSReqQryLockField *pReqQryLock, int nRequestID) = 0;

    /// Description:申请组合查询
    virtual int  ReqQryCombAction(CHSReqQryCombActionField *pReqQryCombAction, int nRequestID) = 0;

    /// Description:组合持仓明细查询
    virtual int  ReqQryPositionCombineDetail(CHSReqQryPositionCombineDetailField *pReqQryPositionCombineDetail, int nRequestID) = 0;

    /// Description:合约信息查询
    virtual int  ReqQryInstrument(CHSReqQryInstrumentField *pReqQryInstrument, int nRequestID) = 0;

    /// Description:备兑缺口查询
    virtual int  ReqQryCoveredShort(CHSReqQryCoveredShortField *pReqQryCoveredShort, int nRequestID) = 0;

    /// Description:行权指派查询
    virtual int  ReqQryExerciseAssign(CHSReqQryExerciseAssignField *pReqQryExerciseAssign, int nRequestID) = 0;

    /// Description:银行转账
    virtual int  ReqTransfer(CHSReqTransferField *pReqTransfer, int nRequestID) = 0;

    /// Description:银行转账查询
    virtual int  ReqQryTransfer(CHSReqQryTransferField *pReqQryTransfer, int nRequestID) = 0;

    /// Description:银行余额查询
    virtual int  ReqQueryBankBalance(CHSReqQueryBankBalanceField *pReqQueryBankBalance, int nRequestID) = 0;

    /// Description:银行账户查询
    virtual int  ReqQueryBankAccount(CHSReqQueryBankAccountField *pReqQueryBankAccount, int nRequestID) = 0;

    /// Description:客户账单查询
    virtual int  ReqQueryBillContent(CHSReqQueryBillContentField *pReqQueryBillContent, int nRequestID) = 0;

    /// Description:客户账单确认
    virtual int  ReqBillConfirm(CHSReqBillConfirmField *pReqBillConfirm, int nRequestID) = 0;

    /// Description:保证金查询
    virtual int  ReqQryMargin(CHSReqQryMarginField *pReqQryMargin, int nRequestID) = 0;

    /// Description:手续费查询
    virtual int  ReqQryCommission(CHSReqQryCommissionField *pReqQryCommission, int nRequestID) = 0;

    /// Description:汇率查询
    virtual int  ReqQryExchangeRate(CHSReqQryExchangeRateField *pReqQryExchangeRate, int nRequestID) = 0;

    /// Description:持仓明细查询
    virtual int  ReqQryPositionDetail(CHSReqQryPositionDetailField *pReqQryPositionDetail, int nRequestID) = 0;

    /// Description:经纪公司配置参数查询
    virtual int  ReqQrySysConfig(CHSReqQrySysConfigField *pReqQrySysConfig, int nRequestID) = 0;

    /// Description:行情查询
    virtual int  ReqQryDepthMarketData(CHSReqQryDepthMarketDataField *pReqQryDepthMarketData, int nRequestID) = 0;
protected:
    ~CHSTradeApi(){};
};

#ifdef __cplusplus
extern "C"
{
#endif
    /// Description: 获取API版本号
    TRADE_API_EXPORT const char*  GetTradeApiVersion();

    /// Description: 创建交易接口    
    /// Input      : pszFlowPath    日志路径   
    TRADE_API_EXPORT CHSTradeApi* NewTradeApi(const char *pszFlowPath);

#ifdef __cplusplus
}
#endif
#endif


