/**
 * 版权所有(C)2012-2016, 大连飞创信息技术有限公司
 * 文件名称：DFITCSECTraderApi.h
 * 文件说明：定义接口所需的数据接口
 * 当前版本：1.6.88
 * 作者：XSpeed证券项目组
 * 发布日期：2019年11月
 */
#ifndef DFITCSECTRADERAPI_H_
#define DFITCSECTRADERAPI_H_

#include "DFITCSECApiStruct.h"

#ifdef WIN32
#ifndef AFX_EXT_CLASS
#define AFX_EXT_CLASS       _declspec(dllexport)
#endif

#ifdef DFITCSECAPI_EXPORTS
#define DFITCSEC_TRADER_API __declspec(dllexport)
#else 
#define DFITCSEC_TRADER_API __declspec(dllimport)
#endif
#else 
#define DFITCSEC_TRADER_API 
#endif

class DFITCSECTraderSpi
{
public:
    /**
     * SEC-网络连接正常响应
     */
    virtual void OnFrontConnected(){};
    /**
     * SEC-网络连接不正常响应
     */
    virtual void OnFrontDisconnected(int nReason) {};
    /**
     * SEC-消息通知
     */
    virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice) {};
    /**
    * ERR-错误应答
    * @param pRspInfo:指针若非空，返回错误信息结构地址
    */
    virtual void OnRspError(DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-登录响应
    * @param pData:指针若非空,返回用户登录响应信息结构体的地址,表明登录请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明登录请求失败
    */
    virtual void OnRspStockUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-登出响应
    * @param pData:指针若非空,返回用户登出响应信息结构体的地址,表明登出请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明登出请求失败
    */
    virtual void OnRspStockUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-密码更新响应
    * @param pData:指针若非空,返回用户密码更新响应信息结构体的地址,表明密码更新请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明密码更新请求失败
    */
    virtual void OnRspStockUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-委托报单响应
    * @param pData:指针若非空,返回用户委托报单响应信息结构体的地址,表明报单请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托报单请求失败
    */
    virtual void OnRspStockEntrustOrder(DFITCStockRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-委托撤单响应
    * @param pData:指针若非空,返回用户委托撤单响应信息结构体的地址,表明撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托撤单请求失败
    */
    virtual void OnRspStockWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-委托查询响应
    * @param pData:指针若非空,返回用户委托查询响应信息结构体的地址,表明查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryEntrustOrder(DFITCStockRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-实时成交查询响应
    * @param pData:指针若非空,返回用户实时成交查询响应信息结构体的地址,表明实时成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明实时成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-分笔成交查询响应
    * @param pData:指针若非空,返回用户分笔成交查询响应信息结构体的地址,表明分笔成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明分笔成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQrySerialTrade(DFITCStockRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-持仓查询响应
    * @param pData:指针若非空,返回用户持仓查询响应信息结构体的地址,表明持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-资金账号查询响应
    * @param pData:指针若非空,返回用户资金账号查询响应信息结构体的地址,表明资金账号查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明资金账号查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-交易账号查询响应
    * @param pData:指针若非空,返回用户交易账号查询响应信息结构体的地址,表明交易账号查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明交易账号查询请求失败
    */
    virtual void OnRspStockQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) {}; 
    /**
    * STOCK-股东号查询响应
    * @param pData:指针若非空,返回用户股东号查询响应信息结构体的地址,表明股东号查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明股东号查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {}; 
    /**
    * STOCK-资金调拨响应
    * @param pData:指针若非空,返回用户资金调拨响应信息结构体的地址,表明股资金调拨请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明资金调拨请求失败
    */
    virtual void OnRspStockTransferFunds(DFITCStockRspTransferFundsField *pData,DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-批量委托响应
    * @param pData:指针若非空,返回用户批量委托响应信息结构体的地址,表明批量委托请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明批量委托请求失败
    */
    virtual void OnRspStockEntrustBatchOrder(DFITCStockRspEntrustBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-批量撤单响应
    * @param pData:指针若非空,返回用户批量撤单响应信息结构体的地址,表明批量撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明批量撤单请求失败
    */
    virtual void OnRspStockWithdrawBatchOrder(DFITCStockRspWithdrawBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-计算可委托数量响应
    * @param pData:指针若非空,返回用户计算可委托数量响应信息结构体的地址,表明计算可委托数量请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明计算可委托数量请求失败
    */
    virtual void OnRspStockCalcAbleEntrustQty(DFITCStockRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo) {}; 
    /**
    * STOCK-计算申购ETF数量响应
    * @param pData:指针若非空,返回用户计算申购ETF数量响应信息结构体的地址,表明计算申购ETF数量请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明计算申购ETF数量请求失败
    */
    virtual void OnRspStockCalcAblePurchaseETFQty(DFITCStockRspCalcAblePurchaseETFQtyField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-冻结资金明细查询响应
    * @param pData:指针若非空,返回用户冻结资金明细查询响应信息结构体的地址,表明冻结资金明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明冻结资金明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {}; 
    /**
    * STOCK-冻结证券明细查询响应
    * @param pData:指针若非空,返回用户冻结证券明细查询响应信息结构体的地址,表明冻结证券明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明冻结证券明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-调拨证券明细查询响应
    * @param pData:指针若非空,返回用户调拨证券明细查询响应信息结构体的地址,表明调拨证券明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明调拨证券明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryTransferStockDetail(DFITCStockRspQryTransferStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-调拨资金明细查询响应
    * @param pData:指针若非空,返回用户调拨资金明细查询响应信息结构体的地址,表明调拨资金明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明调拨资金明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-证券信息查询响应
    * @param pData:指针若非空,返回用户证券信息查询响应信息结构体的地址,表明证券信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明证券信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryStockInfo(DFITCStockRspQryStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-证券静态信息查询响应
    * @param pData:指针若非空,返回用户证券静态信息查询响应信息结构体的地址,表明证券静态信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明证券静态信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryStockStaticInfo(DFITCStockRspQryStockStaticField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * STOCK-交易时间查询响应
    * @param pData:指针若非空,返回用户交易时间查询响应信息结构体的地址,表明交易时间查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明交易时间查询请求失败
    */
    virtual void OnRspStockQryTradeTime(DFITCStockRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * STOCK-委托回报响应
    * @param pData:返回委托回报结构体的地址
    */
    virtual void OnStockEntrustOrderRtn(DFITCStockEntrustOrderRtnField * pData){};
    /**
    * STOCK-成交回报响应
    * @param pData:返回成交回报结构体的地址
    */
    virtual void OnStockTradeRtn(DFITCStockTradeRtnField * pData){};
    /**
    * STOCK-撤单回报响应
    * @param pData:返回撤单回报结构体的地址
    */
    virtual void OnStockWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField * pData){};
    
    /**
    * SOP-登录响应
    * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
    */
    virtual void OnRspSOPUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
     * SOP-登出响应
     * @param pData:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
     * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
     */
    virtual void OnRspSOPUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-用户口令更新响应
    * @param pData:指针若非空,返回用户口令更新响应信息结构地址,表明用户口令更新请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明用户口令更新请求失败
    */
    virtual void OnRspSOPUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-报单响应
    * @param pData:指针若非空,返回用户报单响应信息结构地址,表明报单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明报单请求失败
    */
    virtual void OnRspSOPEntrustOrder(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-做市商报单响应
    * @param pData:指针若非空,返回用户报价委托响应信息结构地址,表明做市商报单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明做市商报单请求失败
    */
    virtual void OnRspSOPQuoteEntrustOrder(DFITCSOPRspQuoteEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-组合拆分委托响应
    * @param pData:指针若非空,返回用户组合拆分委托响应信息结构地址,表明组合拆分委托请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明组合拆分委托请求失败
    */
    virtual void OnRspSOPGroupSplit(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
     * SOP-期权组合行权委托响应
     * @param pData:指针若非空,返回用户期权组合行权委托响应信息结构地址,表明期权组合行权委托请求成功
     * @return pRspInfo:指针若非空，返回错误信息地址，表明期权组合行权委托请求失败，具体错误请对照error.xml  
     */
    virtual void OnRspSOPGroupExectueOrder(DFITCSOPRspGroupExectueOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-查询客户组合持仓明细响应
    * @param pData:指针若非空,返回用户查询客户组合持仓明细响应结构地址,表明查询客户组合持仓明细请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明查询客户组合持仓明细请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryGroupPosition(DFITCSOPRspQryGroupPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-证券锁定解锁响应
    * @param pData:指针若非空,返回用户证券锁定解锁响应信息结构地址,表明证券锁定解锁请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明证券锁定解锁请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPLockOUnLockStock(DFITCSOPRspLockOUnLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {}; 
    /**
    * SOP-撤单响应
    * @param pData:指针若非空,返回用户撤单响应信息结构地址,表明撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明撤单请求失败
    */
    virtual void OnRspSOPWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-委托查询响应
    * @param pData:指针若非空,返回用户委托查询响应信息结构地址,表明委托查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明委托查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryEntrustOrder(DFITCSOPRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-分笔成交查询响应
    * @param pData:指针若非空,返回用户分笔成交查询响应信息结构地址,表明分笔成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明分笔成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQrySerialTrade(DFITCSOPRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-持仓查询响应
    * @param pData:指针若非空,返回用户持仓查询响应信息结构地址,表明持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryPosition(DFITCSOPRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-客户担保持仓查询响应
    * @param pData:指针若非空,返回用户客户担保持仓查询响应信息结构地址,表明客户担保持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户担保持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryCollateralPosition(DFITCSOPRspQryCollateralPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-客户资金查询响应
    * @param pData:指针若非空,返回用户客户资金查询响应信息结构地址,表明客户客户资金查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户资金查询请求失败
    */
    virtual void OnRspSOPQryCapitalAccountInfo(DFITCSOPRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-客户信息查询响应
    * @param pData:指针若非空,返回用户客户信息查询响应信息结构地址,表明客户客户信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户信息查询请求失败
    */
    virtual void OnRspSOPQryAccountInfo(DFITCSOPRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-股东信息查询响应
    * @param pData:指针若非空,返回用户股东信息查询响应信息结构地址,表明客户股东信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户股东信息查询请求失败
    */
    virtual void OnRspSOPQryShareholderInfo(DFITCSOPRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo) {}; 
    /**
    * SOP-可委托数量查询响应
    * @param pData:指针若非空,返回用户可委托数量查询响应信息结构地址,表明客户可委托数量查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户可委托数量查询请求失败
    */
    virtual void OnRspSOPCalcAbleEntrustQty(DFITCSOPRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-客户可锁定证券查询响应
    * @param pData:指针若非空,返回用户客户可锁定证券查询响应信息结构地址,表明客户客户可锁定证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可锁定证券查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryAbleLockStock(DFITCSOPRspQryAbleLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {}; 
    /**
    * SOP-期权合约代码查询响应
    * @param pData:指针若非空,返回用户期权合约代码查询响应信息结构地址,表明客户期权合约代码查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户期权合约代码查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryContactInfo(DFITCSOPRspQryContactField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {}; 
    /**
    * SOP-执行委托响应
    * @param pData:指针若非空,返回用户执行委托响应信息结构地址,表明客户执行委托请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户执行委托请求失败
    */
    virtual void OnRspSOPExectueOrder(DFITCSOPRspExectueOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * SOP-客户行权指派信息查询响应
    * @param pData:指针若非空,返回用户客户行权指派信息查询响应信息结构地址,表明客户客户行权指派信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户行权指派信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryExecAssiInfo(DFITCSOPRspQryExecAssiInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-查询交易时间响应
    * @param pData:指针若非空,返回用户查询交易时间响应信息结构地址,表明客户查询交易时间请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询交易时间请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryTradeTime(DFITCSOPRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-获取所有交易所参数响应
    * @param pData:指针若非空,返回用户获取所有交易所参数响应信息结构地址,表明客户获取所有交易所参数请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户获取所有交易所参数请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryExchangeInfo(DFITCSOPRspQryExchangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-查询手续费参数响应
    * @param pData:指针若非空,返回用户查询手续费参数响应信息结构地址,表明客户查询手续费参数请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询手续费参数请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryCommission(DFITCSOPRspQryCommissionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-查询保证金率参数响应
    * @param pData:指针若非空,返回用户查询保证金率参数响应信息结构地址,表明客户查询保证金率参数请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询保证金率参数请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryDeposit(DFITCSOPRspQryDepositField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-期权标的信息查询响应
    * @param pData:指针若非空,返回用户期权标的信息查询响应信息结构地址,表明客户期权标的信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户期权标的信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryContractObjectInfo(DFITCSOPRspQryContractObjectField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * SOP-委托回报响应
    * @param pData:返回委托回报结构体的地址
    */
    virtual void OnSOPEntrustOrderRtn(DFITCSOPEntrustOrderRtnField * pData){};
    /**
    * SOP-成交回报响应
    * @param pData:返回成交回报结构体的地址
    */
    virtual void OnSOPTradeRtn(DFITCSOPTradeRtnField * pData){};
    /**
    * SOP-撤单回报响应
    * @param pData:返回撤单回报结构体的地址
    */
    virtual void OnSOPWithdrawOrderRtn(DFITCSOPWithdrawOrderRtnField * pData){};

    /**
    * FASL-登录响应
    * @param pData:指针若非空,返回用户融资融券登录响应信息结构地址,表明客户融资融券登录请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券登录请求失败
    */
    virtual void OnRspFASLUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-登出响应
    * @param pData:指针若非空,返回用户融资融券登出响应信息结构地址,表明客户融资融券登出请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券登出请求失败
    */
    virtual void OnRspFASLUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-客户可融资信息响应
    * @param pData:指针若非空,返回用户客户可融资信息响应信息结构地址,表明客户客户可融资信息请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可融资信息请求失败
    */
    virtual void OnRspFASLQryAbleFinInfo(DFITCFASLRspAbleFinInfoField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-客户可融券信息响应
    * @param pData:指针若非空,返回用户客户可融券信息响应信息结构地址,表明客户客户可融券信息请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可融券信息请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryAbleSloInfo(DFITCFASLRspAbleSloInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-担保物划转响应
    * @param pData:指针若非空,返回用户担保物划转响应信息结构地址,表明客户担保物划转请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户担保物划转请求失败
    */
    virtual void OnRspFASLTransferCollateral(DFITCFASLRspTransferCollateralField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-直接还款响应
    * @param pData:指针若非空,返回用户直接还款响应信息结构地址,表明客户直接还款请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户直接还款请求失败
    */
    virtual void OnRspFASLDirectRepayment(DFITCFASLRspDirectRepaymentField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-还券划转响应
    * @param pData:指针若非空,返回用户还券划转响应信息结构地址,表明客户还券划转请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户还券划转请求失败
    */
    virtual void OnRspFASLRepayStockTransfer(DFITCFASLRspRepayStockTransferField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-信用交易响应
    * @param pData:指针若非空,返回用户信用交易响应信息结构地址,表明客户信用交易请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用交易请求失败
    */
    virtual void OnRspFASLEntrustCrdtOrder(DFITCFASLRspEntrustCrdtOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-融资融券交易响应
    * @param pData:指针若非空,返回用户融资融券交易响应信息结构地址,表明客户融资融券交易请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券交易请求失败
    */
    virtual void OnRspFASLEntrustOrder(DFITCFASLRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-信用可委托数量查询响应
    * @param pData:指针若非空,返回用户信用可委托数量查询响应信息结构地址,表明客户信用可委托数量查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用可委托数量查询请求失败
    */
    virtual void OnRspFASLCalcAbleEntrustCrdtQty(DFITCFASLRspCalcAbleEntrustCrdtQtyField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-查询信用资金响应
    * @param pData:指针若非空,返回用户查询信用资金响应信息结构地址,表明客户查询信用资金请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询信用资金请求失败
    */
    virtual void OnRspFASLQryCrdtFunds(DFITCFASLRspQryCrdtFundsField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-信用合约信息响应
    * @param pData:指针若非空,返回用户信用合约信息响应信息结构地址,表明客户信用合约信息请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用合约信息请求失败
    */
    virtual void OnRspFASLQryCrdtContract(DFITCFASLRspQryCrdtContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLat) {};
    /**
    * FASL-信用合约变动信息查询响应
    * @param pData:指针若非空,返回用户信用合约变动信息查询响应信息结构地址,表明客户信用合约变动信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用合约变动信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryCrdtConChangeInfo(DFITCFASLRspQryCrdtConChangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-资金调转响应
    * @param pData:指针若非空,返回用户资金调转响应信息结构地址,表明客户资金调转请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金调转请求失败
    */
    virtual void OnRspFASLTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-客户信息查询响应
    * @param pData:指针若非空,返回用户客户信息查询响应信息结构地址,表明客户客户信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户信息查询请求失败
    */
    virtual void OnRspFASLQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-客户资金查询响应
    * @param pData:指针若非空,返回用户客户资金查询响应信息结构地址,表明客户客户资金查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户资金查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-股东信息查询响应
    * @param pData:指针若非空,返回用户股东信息查询响应信息结构地址,表明客户股东信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户股东信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-持仓查询响应
    * @param pData:指针若非空,返回用户持仓查询响应信息结构地址,表明客户持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-委托查询响应
    * @param pData:指针若非空,返回用户委托查询响应信息结构地址,表明客户委托查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户委托查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryEntrustOrder(DFITCStockRspQryEntrustOrderField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-分笔成交查询响应
    * @param pData:指针若非空,返回用户分笔成交查询响应信息结构地址,表明客户分笔成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户分笔成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQrySerialTrade(DFITCStockRspQrySerialTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-实时成交查询响应
    * @param pData:指针若非空,返回用户实时成交查询响应信息结构地址,表明客户实时成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户实时成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-资金冻结明细查询响应
    * @param pData:指针若非空,返回用户资金冻结明细查询响应信息结构地址,表明客户资金冻结明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金冻结明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-证券冻结明细查询响应
    * @param pData:指针若非空,返回用户证券冻结明细查询响应信息结构地址,表明客户证券冻结明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户证券冻结明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-资金调拨明细查询响应
    * @param pData:指针若非空,返回用户资金调拨明细查询响应信息结构地址,表明客户资金调拨明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金调拨明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-撤单响应
    * @param pData:指针若非空,返回用户撤单响应信息结构地址,表明撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明撤单请求失败
    */
    virtual void OnRspFASLWithdrawOrder(DFITCFASLRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-当前系统时间查询请求响应
    * @param pData:指针若非空,返回用户系统时间查询响应信息结构地址,表明系统时间查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明系统时间查询请求失败
    */
    virtual void OnRspFASLQrySystemTime(DFITCFASLRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-可转入担保证券查询请求响应
    * @param pData:指针若非空,返回可转入担保证券查询响应信息结构地址,表明可转入担保证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明可转入担保证券查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryTransferredContract(DFITCFASLRspQryTransferredContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-客户可取资金调出请求响应
    * @param pData:指针若非空,返回客户可取资金调出响应信息结构地址,表明客户可取资金调出请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户可取资金调出请求失败
    */
    virtual void OnRspFASLDesirableFundsOut(DFITCFASLRspDesirableFundsOutField *pData, DFITCSECRspInfoField *pRspInfo) {};
    /**
    * FASL-担保证券查询请求响应
    * @param pData:指针若非空,返回担保证券查询响应信息结构地址,表明担保证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明担保证券查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryGuaranteedContract(DFITCFASLRspQryGuaranteedContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-标的证券查询请求响应
    * @param pData:指针若非空,返回标的证券查询响应信息结构地址,表明标的证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明标的证券查询失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryUnderlyingContract(DFITCFASLRspQryUnderlyingContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) {};
    /**
    * FASL-委托回报响应
    * @param pData:返回委托回报结构体的地址
    */
    virtual void OnFASLEntrustOrderRtn(DFITCStockEntrustOrderRtnField *pData){};
    /**
    * FASL-成交回报响应
    * @param pData:返回成交回报结构体的地址
    */
    virtual void OnFASLTradeRtn(DFITCStockTradeRtnField *pData){};
    /**
    * FASL-撤单回报响应
    * @param pData:返回撤单回报结构体的地址
    */
    virtual void OnFASLWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField *pData){};
};



class DFITCSEC_TRADER_API DFITCSECTraderApi
{
public:
     /**
      * 创建DFITCSECTraderApi接口对象
      * @ pszLogAddr log所在的路径，如果pszLogAddress为NULL，则不生成log。
      * @ pszPriFlowDir 私有流记录所在的路径，如果pszPriFlowDir为NULL，则默认将私有流记录在当前目录下。
      */
     static DFITCSECTraderApi *CreateDFITCSECTraderApi(const char* pszLogAddr = "", const char* pszPriFlowDir = "");
     /**
      * 释放DFITCSECTraderApi接口对象
      */
     virtual void Release() = 0;
     /**
      * 初始化 
      * @param pszFrontAddress:前置机地址
      *                  网络地址的格式为:"protocol://ipaddress:port",如"tcp://127.0.0.1:10920"
      *                  其中protocol的值必须为tcp。
      *                  ipaddress表示交易前置的IP,port表示交易前置的端口
      * @param pSpi:指向回调函数集的指针
      * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
      */
     virtual int Init(const char *pszFrontAddress, DFITCSECTraderSpi *pSpi) = 0;
     /**
      * 订阅私有流
      * @param nResumeType: 私有流重传方式
      *         TERT_RESTART:从本交易日开始重传
      *         TERT_RESUME:从上次收到的续传
      *         TERT_QUICK:只传送登录后私有流的内容
      * @remark 该方法要在UserLogin方法前调用。若不调用则不会收到私有流的数据。
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int SubscribePrivateTopic(RESUME_TYPE nResumeType) = 0; 
     /**
      * STOCK-登录请求
      * @param p:指向用户登录请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockUserLogin(DFITCSECReqUserLoginField *p) = 0;    
     /**
      * STOCK-登出请求
      * @param p:指向用户登出请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockUserLogout(DFITCSECReqUserLogoutField *p) = 0;
     /**
      * STOCK-密码更新请求
      * @param p:指向用户密码更新请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockUserPasswordUpdate(DFITCSECReqPasswordUpdateField *p) = 0;
     /**
      * STOCK-委托请求
      * @param p:指向用户委托请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockEntrustOrder(DFITCStockReqEntrustOrderField *p) = 0;
     /**
      * STOCK-撤单请求
      * @param p:指向用户撤单请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockWithdrawOrder(DFITCSECReqWithdrawOrderField *p) = 0;
     /**
      * STOCK-委托查询请求
      * @param p:指向用户委托查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryEntrustOrder(DFITCStockReqQryEntrustOrderField *p) = 0;
     /**
      * STOCK-实时成交查询请求
      * @param p:指向用户实时成交查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryRealTimeTrade(DFITCStockReqQryRealTimeTradeField *p) = 0;
     /**
      * STOCK-分笔成交查询请求
      * @param p:指向用户分笔成交查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQrySerialTrade(DFITCStockReqQrySerialTradeField *p) = 0;
     /**
      * STOCK-持仓查询请求
      * @param p:指向用户持仓查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryPosition(DFITCStockReqQryPositionField *p) = 0;
     /**
      * STOCK-资金账户查询请求
      * @param p:指向用户资金账户查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryCapitalAccountInfo(DFITCStockReqQryCapitalAccountField *p) = 0;
     /**
      * STOCK-账户查询请求
      * @param p:指向用户账户查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryAccountInfo(DFITCStockReqQryAccountField *p) = 0;
     /**
      * STOCK-股东查询请求
      * @param p:指向用户股东查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryShareholderInfo(DFITCStockReqQryShareholderField *p) = 0;
     /**
      * STOCK-调拨资金请求
      * @param p:指向用户调拨资金请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockTransferFunds(DFITCStockReqTransferFundsField *p) = 0;
     /**
      * STOCK-批量委托请求
      * @param p:指向用户批量委托请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockEntrustBatchOrder(DFITCStockReqEntrustBatchOrderField *p) = 0;
     /**
      * STOCK-批量撤单请求
      * @param p:指向用户批量撤单请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockWithdrawBatchOrder(DFITCStockReqWithdrawBatchOrderField *p) = 0;
     /**
      * STOCK-计算可委托数量请求
      * @param p:指向用户计算可委托数量请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockCalcAbleEntrustQty(DFITCStockReqCalcAbleEntrustQtyField *p) = 0;
     /**
      * STOCK-计算可申购ETF篮子数请求
      * @param p:指向用户计算可申购ETF篮子数请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockCalcAblePurchaseETFQty(DFITCStockReqCalcAblePurchaseETFQtyField *p) = 0;
     /**
      * STOCK-冻结资金明细查询请求
      * @param p:指向用户冻结资金明细查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryFreezeFundsDetail(DFITCStockReqQryFreezeFundsDetailField *p) = 0;
     /**
      * STOCK-冻结证券明细查询
      * @param p:指向用户冻结证券明细查询结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryFreezeStockDetail(DFITCStockReqQryFreezeStockDetailField *p) = 0;
     /**
      * STOCK-调拨资金明细查询请求
      * @param p:指向用户调拨资金明细查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryTransferFundsDetail(DFITCStockReqQryTransferFundsDetailField *p) = 0;
     /**
      * STOCK-调拨证券明细查询请求
      * @param p:指向用户调拨证券明细查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryTransferStockDetail(DFITCStockReqQryTransferStockDetailField *p) = 0; 
     /**
      * STOCK-股票查询请求
      * @param p:指向用户股票查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryStockInfo(DFITCStockReqQryStockField *p) = 0;
     /**
      * STOCK-股票静态信息查询请求
      * @param p:指向用户股票静态信息查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryStockStaticInfo(DFITCStockReqQryStockStaticField *p) = 0;
     /**
      * STOCK-交易时间查询请求
      * @param p:指向用户交易时间查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqStockQryTradeTime(DFITCStockReqQryTradeTimeField *p) = 0;
     /**
      * SOP-登录请求
      * @param p:指向用户登录请求结构的地址
      * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
      */
     virtual int ReqSOPUserLogin(DFITCSECReqUserLoginField *p) = 0;
     /**
      * SOP-登出请求
      * @param p:指向用户登出请求结构的地址
      * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
      */
     virtual int ReqSOPUserLogout(DFITCSECReqUserLogoutField *p) = 0;
     /**
      * SOP-交易密码更新请求
      * @param p:指向用户密码更新请求结构的地址
      * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
      */
     virtual int ReqSOPUserPasswordUpdate(DFITCSECReqPasswordUpdateField *p) = 0;
    /**
     * SOP-报单请求
     * @param p:指向用户报单请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
     */
    virtual int ReqSOPEntrustOrder(DFITCSOPReqEntrustOrderField *p) = 0;
    /**
     * SOP-做市商报单请求
     * @param p:指向用户做市商报单请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
     */
    virtual int ReqSOPQuoteEntrustOrder(DFITCSOPReqQuoteEntrustOrderField *p) = 0;
    /**
     * SOP-持仓组合拆分委托请求
     * @param p:指向用户交易所持仓组合拆分委托请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
     */
    virtual int ReqSOPGroupSplit(DFITCSOPReqGroupSplitField *p) = 0;
    /**
     * SOP-期权组合行权委托请求
     * @param p:指向用户期权组合行权委托请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPGroupExectueOrder(DFITCSOPReqGroupExectueOrderField *p) = 0;
    /**
     * SOP-查询客户组合持仓明细请求
     * @param p:指向用户查询客户组合持仓明细请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
     */
    virtual int ReqSOPQryGroupPosition(DFITCSOPReqQryGroupPositionField *p) = 0;
    /**
     * SOP-证券锁定解锁请求
     * @param p:指向用户证券锁定解锁请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPLockOUnLockStock(DFITCSOPReqLockOUnLockStockField *p) = 0;
    /**
     * SOP-撤单请求
     * @param p:指向用户撤单请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPWithdrawOrder(DFITCSECReqWithdrawOrderField *p) = 0;
    /**
     * SOP-当日委托查询请求
     * @param p:指向用户当日委托查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryEntrustOrder(DFITCSOPReqQryEntrustOrderField *p) = 0;
    /**
     * SOP-分笔成交查询请求
     * @param p:指向用户分笔成交查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQrySerialTrade(DFITCSOPReqQrySerialTradeField *p) = 0;
    /**
     * SOP-持仓查询请求
     * @param p:指向用户持仓查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryPosition(DFITCSOPReqQryPositionField *p) = 0;
    /**
     * SOP-担保物持仓查询请求
     * @param p:指向用户担保物持仓查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryCollateralPosition(DFITCSOPReqQryCollateralPositionField *p) = 0;
    /**
     * SOP-资金信息查询请求
     * @param p:指向用户资金信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryCapitalAccountInfo(DFITCSOPReqQryCapitalAccountField *p) = 0;
    /**
     * SOP-客户信息查询请求
     * @param p:指向用户客户信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryAccountInfo(DFITCSOPReqQryAccountField *p) = 0;
    /**
     * SOP-股东信息查询请求
     * @param p:指向用户股东信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryShareholderInfo(DFITCSOPReqQryShareholderField *p) = 0;
    /**
     * SOP-可委托数量计算请求
     * @param p:指向用户可委托数量计算请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPCalcAbleEntrustQty(DFITCSOPReqCalcAbleEntrustQtyField *p) = 0;
    /**
     * SOP-可锁定证券数量查询请求
     * @param p:指向用户可锁定证券数量查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryAbleLockStock(DFITCSOPReqQryAbleLockStockField *p) = 0;
    /**
     * SOP-期权合约代码查询请求
     * @param p:指向用户期权合约代码查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryContactInfo(DFITCSOPReqQryContactField *p) = 0;
    /**
     * SOP-行权委托请求
     * @param p:指向用户行权委托请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPExectueOrder(DFITCSOPReqExectueOrderField *p) = 0;
    /**
     * SOP-行权指派信息查询请求
     * @param p:指向用户行权指派信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryExecAssiInfo(DFITCSOPReqQryExecAssiInfoField *p) = 0;
    /**
     * SOP-交易时间查询请求
     * @param p:指向用户交易时间查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryTradeTime(DFITCSOPReqQryTradeTimeField *p) = 0;
    /**
     * SOP-交易所信息查询请求
     * @param p:指向用户交易所信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryExchangeInfo(DFITCSOPReqQryExchangeInfoField *p) = 0;
    /**
     * SOP-手续费查询请求
     * @param p:指向用户手续费查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryCommission(DFITCSOPReqQryCommissionField *p) = 0;
    /**
     * SOP-保证金查询请求
     * @param p:指向用户保证金查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryDeposit(DFITCSOPReqQryDepositField *p) = 0;
    /**
     * SOP-标的信息查询请求
     * @param p:指向用户标的信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqSOPQryContractObjectInfo(DFITCSOPReqQryContractObjectField *p) = 0;
    /**
     * FASL-登录请求
     * @param p:指向用户登录请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLUserLogin(DFITCSECReqUserLoginField *p) = 0;
    /**
     * FASL-登出请求
     * @param p:指向用户登出请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLUserLogout(DFITCSECReqUserLogoutField *p) = 0;
    /**
     * FASL-客户可融资信息请求
     * @param p:指向用户客户可融资信息请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryAbleFinInfo(DFITCFASLReqAbleFinInfoField *p) = 0;
    /**
     * FASL-客户可融券信息请求
     * @param p:指向用户客户可融券信息请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryAbleSloInfo(DFITCFASLReqAbleSloInfoField *p) = 0;
    /**
     * FASL-担保物划转请求
     * @param p:指向用户担保物划转请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLTransferCollateral(DFITCFASLReqTransferCollateralField *p) = 0;
    /**
     * FASL-直接还款请求
     * @param p:指向用户直接还款请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLDirectRepayment(DFITCFASLReqDirectRepaymentField *p) = 0;
    /**
     * FASL-还券划转请求
     * @param p:指向用户还券划转请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLRepayStockTransfer(DFITCFASLReqRepayStockTransferField *p) = 0;
    /**
     * FASL-信用交易请求
     * @param p:指向用户信用交易请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLEntrustCrdtOrder(DFITCFASLReqEntrustCrdtOrderField *p) = 0;
    /**
     * FASL-融资融券交易请求
     * @param p:指向用户融资融券交易请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLEntrsuctOrder(DFITCFASLReqEntrustOrderField *p) = 0;
    /**
     * FASL-撤单请求
     * @param p:指向用户撤单请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLWithdrawOrder(DFITCFASLReqWithdrawOrderField *p) = 0;
    /**
     * FASL-信用可委托数量查询请求
     * @param p:指向用户信用可委托数量查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLCalcAbleEntrustCrdtQty(DFITCFASLReqCalcAbleEntrustCrdtQtyField *p) = 0;
    /**
     * FASL-查询信用资金请求
     * @param p:指向用户查询信用资金请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryCrdtFunds(DFITCFASLReqQryCrdtFundsField *p) = 0;
    /**
     * FASL-信用合约信息请求
     * @param p:指向用户信用合约信息请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryCrdtContract(DFITCFASLReqQryCrdtContractField *p) = 0;
    /**
     * FASL-信用合约变动信息查询请求
     * @param p:指向用户信用合约变动信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryCrdtConChangeInfo(DFITCFASLReqQryCrdtConChangeInfoField *p) = 0;
    /**
     * FASL-资金调转请求
     * @param p:指向用户资金调转请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLTransferFunds(DFITCStockReqTransferFundsField *p) = 0;
    /**
     * FASL-客户信息查询请求
     * @param p:指向用户客户信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryAccountInfo(DFITCStockReqQryAccountField *p) = 0;
    /**
     * FASL-客户资金查询请求
     * @param p:指向用户客户资金查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryCapitalAccountInfo(DFITCStockReqQryCapitalAccountField *p) = 0;
    /**
     * FASL-股东信息查询请求
     * @param p:指向用户股东信息查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryShareholderInfo(DFITCStockReqQryShareholderField *p) = 0;
    /**
     * FASL-持仓查询请求
     * @param p:指向用户持仓查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryPosition(DFITCStockReqQryPositionField *p) = 0;
    /**
     * FASL-委托查询请求
     * @param p:指向用户委托查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryEntrustOrder(DFITCStockReqQryEntrustOrderField *p) = 0;
    /**
     * FASL-分笔成交查询请求
     * @param p:指向用户分笔成交查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQrySerialTrade(DFITCStockReqQrySerialTradeField *p) = 0;
    /**
     * FASL-实时成交查询请求
     * @param p:指向用户实时成交查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryRealTimeTrade(DFITCStockReqQryRealTimeTradeField *p) = 0;
    /**
     * FASL-资金冻结明细查询请求
     * @param p:指向用户资金冻结明细查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryFreezeFundsDetail(DFITCStockReqQryFreezeFundsDetailField *p) = 0;
    /**
     * FASL-证券冻结明细查询请求
     * @param p:指向用户证券冻结明细查询请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryFreezeStockDetail(DFITCStockReqQryFreezeStockDetailField *p) = 0;
    /**
     * FASL-查询资金调拨明细请求
     * @param p:指向用户查询资金调拨明细请求结构的地址
     * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml  
     */
    virtual int ReqFASLQryTransferFundsDetail(DFITCStockReqQryTransferFundsDetailField *p) = 0;
    /**
      * FASL-当前系统时间查询请求
      * @param p:指向用户交易时间查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqFASLQrySystemTime(DFITCFASLReqQryTradeTimeField *p) = 0;
    /**
      * FASL-可转入担保证券查询请求
      * @param p:指向可转入担保证券查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqFASLQryTransferredContract(DFITCFASLReqQryTransferredContractField *p) = 0;
    /**
      * FASL-客户可取资金调出请求
      * @param p:指向客户可取资金调出请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqFASLDesirableFundsOut(DFITCFASLReqDesirableFundsOutField *p) = 0;
    /**
      * FASL-担保证券查询请求
      * @param p:指向担保证券查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqFASLQryGuaranteedContract(DFITCFASLReqQryGuaranteedContractField *p) = 0;
    /**
      * FASL-标的证券查询请求
      * @param p:指向标的证券查询请求结构体的地址
      * @return : 0 表示请求发送成功，非 0 表示请求发送失败，具体错误请参考error.xml
      */
     virtual int ReqFASLQryUnderlyingContract(DFITCFASLReqQryUnderlyingContractField *p) = 0;

    /**
      * SOP-设置终端信息
      * @param p:指设置终端信息结构体的地址
      * @return : 0 表示设置成功，非0表示设置失败，具体错误请参考error.xml
      */
     virtual int SetTerminalInfo(DFITCTerminalInfoField* p) = 0;
public:
    DFITCSECTraderApi();
    virtual ~DFITCSECTraderApi();
};

#endif
