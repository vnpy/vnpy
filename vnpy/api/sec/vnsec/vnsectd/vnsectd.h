//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnsec.h"
#include "pybind11/pybind11.h"
#include "DFITCSECTraderApi.h"

using namespace pybind11;
using namespace std;

//常量

#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONRTNNOTICE 2
#define ONRSPERROR 3
#define ONRSPSTOCKUSERLOGIN 4
#define ONRSPSTOCKUSERLOGOUT 5
#define ONRSPSTOCKUSERPASSWORDUPDATE 6
#define ONRSPSTOCKENTRUSTORDER 7
#define ONRSPSTOCKWITHDRAWORDER 8
#define ONRSPSTOCKQRYENTRUSTORDER 9
#define ONRSPSTOCKQRYREALTIMETRADE 10
#define ONRSPSTOCKQRYSERIALTRADE 11
#define ONRSPSTOCKQRYPOSITION 12
#define ONRSPSTOCKQRYCAPITALACCOUNTINFO 13
#define ONRSPSTOCKQRYACCOUNTINFO 14
#define ONRSPSTOCKQRYSHAREHOLDERINFO 15
#define ONRSPSTOCKTRANSFERFUNDS 16
#define ONRSPSTOCKENTRUSTBATCHORDER 17
#define ONRSPSTOCKWITHDRAWBATCHORDER 18
#define ONRSPSTOCKCALCABLEENTRUSTQTY 19
#define ONRSPSTOCKCALCABLEPURCHASEETFQTY 20
#define ONRSPSTOCKQRYFREEZEFUNDSDETAIL 21
#define ONRSPSTOCKQRYFREEZESTOCKDETAIL 22
#define ONRSPSTOCKQRYTRANSFERSTOCKDETAIL 23
#define ONRSPSTOCKQRYTRANSFERFUNDSDETAIL 24
#define ONRSPSTOCKQRYSTOCKINFO 25
#define ONRSPSTOCKQRYSTOCKSTATICINFO 26
#define ONRSPSTOCKQRYTRADETIME 27
#define ONSTOCKENTRUSTORDERRTN 28
#define ONSTOCKTRADERTN 29
#define ONSTOCKWITHDRAWORDERRTN 30
#define ONRSPSOPUSERLOGIN 31
#define ONRSPSOPUSERLOGOUT 32
#define ONRSPSOPUSERPASSWORDUPDATE 33
#define ONRSPSOPENTRUSTORDER 34
#define ONRSPSOPQUOTEENTRUSTORDER 35
#define ONRSPSOPGROUPSPLIT 36
#define ONRSPSOPGROUPEXECTUEORDER 37
#define ONRSPSOPQRYGROUPPOSITION 38
#define ONRSPSOPLOCKOUNLOCKSTOCK 39
#define ONRSPSOPWITHDRAWORDER 40
#define ONRSPSOPQRYENTRUSTORDER 41
#define ONRSPSOPQRYSERIALTRADE 42
#define ONRSPSOPQRYPOSITION 43
#define ONRSPSOPQRYCOLLATERALPOSITION 44
#define ONRSPSOPQRYCAPITALACCOUNTINFO 45
#define ONRSPSOPQRYACCOUNTINFO 46
#define ONRSPSOPQRYSHAREHOLDERINFO 47
#define ONRSPSOPCALCABLEENTRUSTQTY 48
#define ONRSPSOPQRYABLELOCKSTOCK 49
#define ONRSPSOPQRYCONTACTINFO 50
#define ONRSPSOPEXECTUEORDER 51
#define ONRSPSOPQRYEXECASSIINFO 52
#define ONRSPSOPQRYTRADETIME 53
#define ONRSPSOPQRYEXCHANGEINFO 54
#define ONRSPSOPQRYCOMMISSION 55
#define ONRSPSOPQRYDEPOSIT 56
#define ONRSPSOPQRYCONTRACTOBJECTINFO 57
#define ONSOPENTRUSTORDERRTN 58
#define ONSOPTRADERTN 59
#define ONSOPWITHDRAWORDERRTN 60
#define ONRSPFASLUSERLOGIN 61
#define ONRSPFASLUSERLOGOUT 62
#define ONRSPFASLQRYABLEFININFO 63
#define ONRSPFASLQRYABLESLOINFO 64
#define ONRSPFASLTRANSFERCOLLATERAL 65
#define ONRSPFASLDIRECTREPAYMENT 66
#define ONRSPFASLREPAYSTOCKTRANSFER 67
#define ONRSPFASLENTRUSTCRDTORDER 68
#define ONRSPFASLENTRUSTORDER 69
#define ONRSPFASLCALCABLEENTRUSTCRDTQTY 70
#define ONRSPFASLQRYCRDTFUNDS 71
#define ONRSPFASLQRYCRDTCONTRACT 72
#define ONRSPFASLQRYCRDTCONCHANGEINFO 73
#define ONRSPFASLTRANSFERFUNDS 74
#define ONRSPFASLQRYACCOUNTINFO 75
#define ONRSPFASLQRYCAPITALACCOUNTINFO 76
#define ONRSPFASLQRYSHAREHOLDERINFO 77
#define ONRSPFASLQRYPOSITION 78
#define ONRSPFASLQRYENTRUSTORDER 79
#define ONRSPFASLQRYSERIALTRADE 80
#define ONRSPFASLQRYREALTIMETRADE 81
#define ONRSPFASLQRYFREEZEFUNDSDETAIL 82
#define ONRSPFASLQRYFREEZESTOCKDETAIL 83
#define ONRSPFASLQRYTRANSFERFUNDSDETAIL 84
#define ONRSPFASLWITHDRAWORDER 85
#define ONRSPFASLQRYSYSTEMTIME 86
#define ONRSPFASLQRYTRANSFERREDCONTRACT 87
#define ONRSPFASLDESIRABLEFUNDSOUT 88
#define ONRSPFASLQRYGUARANTEEDCONTRACT 89
#define ONRSPFASLQRYUNDERLYINGCONTRACT 90
#define ONFASLENTRUSTORDERRTN 91
#define ONFASLTRADERTN 92
#define ONFASLWITHDRAWORDERRTN 93

///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现

class TdApi : public DFITCSECTraderSpi
{
private:
    DFITCSECTraderApi* api;            //API对象
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

    /**
     * SEC-网络连接正常响应
     */
    virtual void OnFrontConnected();
    /**
     * SEC-网络连接不正常响应
     */
    virtual void OnFrontDisconnected(int nReason);
    /**
     * SEC-消息通知
     */
    virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice);
    /**
    * ERR-错误应答
    * @param pRspInfo:指针若非空，返回错误信息结构地址
    */
    virtual void OnRspError(DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-登录响应
    * @param pData:指针若非空,返回用户登录响应信息结构体的地址,表明登录请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明登录请求失败
    */
    virtual void OnRspStockUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-登出响应
    * @param pData:指针若非空,返回用户登出响应信息结构体的地址,表明登出请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明登出请求失败
    */
    virtual void OnRspStockUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-密码更新响应
    * @param pData:指针若非空,返回用户密码更新响应信息结构体的地址,表明密码更新请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明密码更新请求失败
    */
    virtual void OnRspStockUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-委托报单响应
    * @param pData:指针若非空,返回用户委托报单响应信息结构体的地址,表明报单请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托报单请求失败
    */
    virtual void OnRspStockEntrustOrder(DFITCStockRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-委托撤单响应
    * @param pData:指针若非空,返回用户委托撤单响应信息结构体的地址,表明撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托撤单请求失败
    */
    virtual void OnRspStockWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-委托查询响应
    * @param pData:指针若非空,返回用户委托查询响应信息结构体的地址,表明查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明委托查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryEntrustOrder(DFITCStockRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-实时成交查询响应
    * @param pData:指针若非空,返回用户实时成交查询响应信息结构体的地址,表明实时成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明实时成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-分笔成交查询响应
    * @param pData:指针若非空,返回用户分笔成交查询响应信息结构体的地址,表明分笔成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明分笔成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQrySerialTrade(DFITCStockRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-持仓查询响应
    * @param pData:指针若非空,返回用户持仓查询响应信息结构体的地址,表明持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-资金账号查询响应
    * @param pData:指针若非空,返回用户资金账号查询响应信息结构体的地址,表明资金账号查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明资金账号查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-交易账号查询响应
    * @param pData:指针若非空,返回用户交易账号查询响应信息结构体的地址,表明交易账号查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明交易账号查询请求失败
    */
    virtual void OnRspStockQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-股东号查询响应
    * @param pData:指针若非空,返回用户股东号查询响应信息结构体的地址,表明股东号查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明股东号查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-资金调拨响应
    * @param pData:指针若非空,返回用户资金调拨响应信息结构体的地址,表明股资金调拨请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明资金调拨请求失败
    */
    virtual void OnRspStockTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo);
    /*
    * STOCK-批量委托响应
    * @param pData:指针若非空,返回用户批量委托响应信息结构体的地址,表明批量委托请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明批量委托请求失败
    */
    virtual void OnRspStockEntrustBatchOrder(DFITCStockRspEntrustBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-批量撤单响应
    * @param pData:指针若非空,返回用户批量撤单响应信息结构体的地址,表明批量撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明批量撤单请求失败
    */
    virtual void OnRspStockWithdrawBatchOrder(DFITCStockRspWithdrawBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-计算可委托数量响应
    * @param pData:指针若非空,返回用户计算可委托数量响应信息结构体的地址,表明计算可委托数量请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明计算可委托数量请求失败
    */
    virtual void OnRspStockCalcAbleEntrustQty(DFITCStockRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-计算申购ETF数量响应
    * @param pData:指针若非空,返回用户计算申购ETF数量响应信息结构体的地址,表明计算申购ETF数量请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明计算申购ETF数量请求失败
    */
    virtual void OnRspStockCalcAblePurchaseETFQty(DFITCStockRspCalcAblePurchaseETFQtyField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-冻结资金明细查询响应
    * @param pData:指针若非空,返回用户冻结资金明细查询响应信息结构体的地址,表明冻结资金明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明冻结资金明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-冻结证券明细查询响应
    * @param pData:指针若非空,返回用户冻结证券明细查询响应信息结构体的地址,表明冻结证券明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明冻结证券明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-调拨证券明细查询响应
    * @param pData:指针若非空,返回用户调拨证券明细查询响应信息结构体的地址,表明调拨证券明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明调拨证券明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryTransferStockDetail(DFITCStockRspQryTransferStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-调拨资金明细查询响应
    * @param pData:指针若非空,返回用户调拨资金明细查询响应信息结构体的地址,表明调拨资金明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明调拨资金明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-证券信息查询响应
    * @param pData:指针若非空,返回用户证券信息查询响应信息结构体的地址,表明证券信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明证券信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryStockInfo(DFITCStockRspQryStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-证券静态信息查询响应
    * @param pData:指针若非空,返回用户证券静态信息查询响应信息结构体的地址,表明证券静态信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明证券静态信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspStockQryStockStaticInfo(DFITCStockRspQryStockStaticField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * STOCK-交易时间查询响应
    * @param pData:指针若非空,返回用户交易时间查询响应信息结构体的地址,表明交易时间查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息结构体的地址，表明交易时间查询请求失败
    */
    virtual void OnRspStockQryTradeTime(DFITCStockRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * STOCK-委托回报响应
    * @param pData:返回委托回报结构体的地址
    */
    virtual void OnStockEntrustOrderRtn(DFITCStockEntrustOrderRtnField * pData);
    /**
    * STOCK-成交回报响应
    * @param pData:返回成交回报结构体的地址
    */
    virtual void OnStockTradeRtn(DFITCStockTradeRtnField * pData);
    /**
    * STOCK-撤单回报响应
    * @param pData:返回撤单回报结构体的地址
    */
    virtual void OnStockWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField * pData);

    /**
    * SOP-登录响应
    * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
    */
    virtual void OnRspSOPUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
     * SOP-登出响应
     * @param pData:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
     * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
     */
    virtual void OnRspSOPUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-用户口令更新响应
    * @param pData:指针若非空,返回用户口令更新响应信息结构地址,表明用户口令更新请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明用户口令更新请求失败
    */
    virtual void OnRspSOPUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-报单响应
    * @param pData:指针若非空,返回用户报单响应信息结构地址,表明报单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明报单请求失败
    */
    virtual void OnRspSOPEntrustOrder(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-做市商报单响应
    * @param pData:指针若非空,返回用户报价委托响应信息结构地址,表明做市商报单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明做市商报单请求失败
    */
    virtual void OnRspSOPQuoteEntrustOrder(DFITCSOPRspQuoteEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-组合拆分委托响应
    * @param pData:指针若非空,返回用户组合拆分委托响应信息结构地址,表明组合拆分委托请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明组合拆分委托请求失败
    */
    virtual void OnRspSOPGroupSplit(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
     * SOP-期权组合行权委托响应
     * @param pData:指针若非空,返回用户期权组合行权委托响应信息结构地址,表明期权组合行权委托请求成功
     * @return pRspInfo:指针若非空，返回错误信息地址，表明期权组合行权委托请求失败，具体错误请对照error.xml
     */
    virtual void OnRspSOPGroupExectueOrder(DFITCSOPRspGroupExectueOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-查询客户组合持仓明细响应
    * @param pData:指针若非空,返回用户查询客户组合持仓明细响应结构地址,表明查询客户组合持仓明细请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明查询客户组合持仓明细请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryGroupPosition(DFITCSOPRspQryGroupPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-证券锁定解锁响应
    * @param pData:指针若非空,返回用户证券锁定解锁响应信息结构地址,表明证券锁定解锁请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明证券锁定解锁请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPLockOUnLockStock(DFITCSOPRspLockOUnLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-撤单响应
    * @param pData:指针若非空,返回用户撤单响应信息结构地址,表明撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明撤单请求失败
    */
    virtual void OnRspSOPWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-委托查询响应
    * @param pData:指针若非空,返回用户委托查询响应信息结构地址,表明委托查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明委托查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryEntrustOrder(DFITCSOPRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-分笔成交查询响应
    * @param pData:指针若非空,返回用户分笔成交查询响应信息结构地址,表明分笔成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明分笔成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQrySerialTrade(DFITCSOPRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-持仓查询响应
    * @param pData:指针若非空,返回用户持仓查询响应信息结构地址,表明持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryPosition(DFITCSOPRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-客户担保持仓查询响应
    * @param pData:指针若非空,返回用户客户担保持仓查询响应信息结构地址,表明客户担保持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户担保持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryCollateralPosition(DFITCSOPRspQryCollateralPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-客户资金查询响应
    * @param pData:指针若非空,返回用户客户资金查询响应信息结构地址,表明客户客户资金查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户资金查询请求失败
    */
    virtual void OnRspSOPQryCapitalAccountInfo(DFITCSOPRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-客户信息查询响应
    * @param pData:指针若非空,返回用户客户信息查询响应信息结构地址,表明客户客户信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户信息查询请求失败
    */
    virtual void OnRspSOPQryAccountInfo(DFITCSOPRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-股东信息查询响应
    * @param pData:指针若非空,返回用户股东信息查询响应信息结构地址,表明客户股东信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户股东信息查询请求失败
    */
    virtual void OnRspSOPQryShareholderInfo(DFITCSOPRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-可委托数量查询响应
    * @param pData:指针若非空,返回用户可委托数量查询响应信息结构地址,表明客户可委托数量查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户可委托数量查询请求失败
    */
    virtual void OnRspSOPCalcAbleEntrustQty(DFITCSOPRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-客户可锁定证券查询响应
    * @param pData:指针若非空,返回用户客户可锁定证券查询响应信息结构地址,表明客户客户可锁定证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可锁定证券查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryAbleLockStock(DFITCSOPRspQryAbleLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-期权合约代码查询响应
    * @param pData:指针若非空,返回用户期权合约代码查询响应信息结构地址,表明客户期权合约代码查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户期权合约代码查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryContactInfo(DFITCSOPRspQryContactField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-执行委托响应
    * @param pData:指针若非空,返回用户执行委托响应信息结构地址,表明客户执行委托请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户执行委托请求失败
    */
    virtual void OnRspSOPExectueOrder(DFITCSOPRspExectueOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * SOP-客户行权指派信息查询响应
    * @param pData:指针若非空,返回用户客户行权指派信息查询响应信息结构地址,表明客户客户行权指派信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户行权指派信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryExecAssiInfo(DFITCSOPRspQryExecAssiInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-查询交易时间响应
    * @param pData:指针若非空,返回用户查询交易时间响应信息结构地址,表明客户查询交易时间请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询交易时间请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryTradeTime(DFITCSOPRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-获取所有交易所参数响应
    * @param pData:指针若非空,返回用户获取所有交易所参数响应信息结构地址,表明客户获取所有交易所参数请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户获取所有交易所参数请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryExchangeInfo(DFITCSOPRspQryExchangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-查询手续费参数响应
    * @param pData:指针若非空,返回用户查询手续费参数响应信息结构地址,表明客户查询手续费参数请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询手续费参数请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryCommission(DFITCSOPRspQryCommissionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-查询保证金率参数响应
    * @param pData:指针若非空,返回用户查询保证金率参数响应信息结构地址,表明客户查询保证金率参数请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询保证金率参数请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryDeposit(DFITCSOPRspQryDepositField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-期权标的信息查询响应
    * @param pData:指针若非空,返回用户期权标的信息查询响应信息结构地址,表明客户期权标的信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户期权标的信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspSOPQryContractObjectInfo(DFITCSOPRspQryContractObjectField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * SOP-委托回报响应
    * @param pData:返回委托回报结构体的地址
    */
    virtual void OnSOPEntrustOrderRtn(DFITCSOPEntrustOrderRtnField * pData);
    /**
    * SOP-成交回报响应
    * @param pData:返回成交回报结构体的地址
    */
    virtual void OnSOPTradeRtn(DFITCSOPTradeRtnField * pData);
    /**
    * SOP-撤单回报响应
    * @param pData:返回撤单回报结构体的地址
    */
    virtual void OnSOPWithdrawOrderRtn(DFITCSOPWithdrawOrderRtnField * pData);

    /**
    * FASL-登录响应
    * @param pData:指针若非空,返回用户融资融券登录响应信息结构地址,表明客户融资融券登录请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券登录请求失败
    */
    virtual void OnRspFASLUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-登出响应
    * @param pData:指针若非空,返回用户融资融券登出响应信息结构地址,表明客户融资融券登出请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券登出请求失败
    */
    virtual void OnRspFASLUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-客户可融资信息响应
    * @param pData:指针若非空,返回用户客户可融资信息响应信息结构地址,表明客户客户可融资信息请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可融资信息请求失败
    */
    virtual void OnRspFASLQryAbleFinInfo(DFITCFASLRspAbleFinInfoField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-客户可融券信息响应
    * @param pData:指针若非空,返回用户客户可融券信息响应信息结构地址,表明客户客户可融券信息请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户可融券信息请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryAbleSloInfo(DFITCFASLRspAbleSloInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-担保物划转响应
    * @param pData:指针若非空,返回用户担保物划转响应信息结构地址,表明客户担保物划转请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户担保物划转请求失败
    */
    virtual void OnRspFASLTransferCollateral(DFITCFASLRspTransferCollateralField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-直接还款响应
    * @param pData:指针若非空,返回用户直接还款响应信息结构地址,表明客户直接还款请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户直接还款请求失败
    */
    virtual void OnRspFASLDirectRepayment(DFITCFASLRspDirectRepaymentField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-还券划转响应
    * @param pData:指针若非空,返回用户还券划转响应信息结构地址,表明客户还券划转请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户还券划转请求失败
    */
    virtual void OnRspFASLRepayStockTransfer(DFITCFASLRspRepayStockTransferField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-信用交易响应
    * @param pData:指针若非空,返回用户信用交易响应信息结构地址,表明客户信用交易请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用交易请求失败
    */
    virtual void OnRspFASLEntrustCrdtOrder(DFITCFASLRspEntrustCrdtOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-融资融券交易响应
    * @param pData:指针若非空,返回用户融资融券交易响应信息结构地址,表明客户融资融券交易请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户融资融券交易请求失败
    */
    virtual void OnRspFASLEntrustOrder(DFITCFASLRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-信用可委托数量查询响应
    * @param pData:指针若非空,返回用户信用可委托数量查询响应信息结构地址,表明客户信用可委托数量查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用可委托数量查询请求失败
    */
    virtual void OnRspFASLCalcAbleEntrustCrdtQty(DFITCFASLRspCalcAbleEntrustCrdtQtyField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-查询信用资金响应
    * @param pData:指针若非空,返回用户查询信用资金响应信息结构地址,表明客户查询信用资金请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户查询信用资金请求失败
    */
    virtual void OnRspFASLQryCrdtFunds(DFITCFASLRspQryCrdtFundsField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-信用合约信息响应
    * @param pData:指针若非空,返回用户信用合约信息响应信息结构地址,表明客户信用合约信息请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用合约信息请求失败
    */
    virtual void OnRspFASLQryCrdtContract(DFITCFASLRspQryCrdtContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLat);
    /**
    * FASL-信用合约变动信息查询响应
    * @param pData:指针若非空,返回用户信用合约变动信息查询响应信息结构地址,表明客户信用合约变动信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户信用合约变动信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryCrdtConChangeInfo(DFITCFASLRspQryCrdtConChangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-资金调转响应
    * @param pData:指针若非空,返回用户资金调转响应信息结构地址,表明客户资金调转请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金调转请求失败
    */
    virtual void OnRspFASLTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-客户信息查询响应
    * @param pData:指针若非空,返回用户客户信息查询响应信息结构地址,表明客户客户信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户信息查询请求失败
    */
    virtual void OnRspFASLQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-客户资金查询响应
    * @param pData:指针若非空,返回用户客户资金查询响应信息结构地址,表明客户客户资金查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户客户资金查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-股东信息查询响应
    * @param pData:指针若非空,返回用户股东信息查询响应信息结构地址,表明客户股东信息查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户股东信息查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-持仓查询响应
    * @param pData:指针若非空,返回用户持仓查询响应信息结构地址,表明客户持仓查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户持仓查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-委托查询响应
    * @param pData:指针若非空,返回用户委托查询响应信息结构地址,表明客户委托查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户委托查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryEntrustOrder(DFITCStockRspQryEntrustOrderField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-分笔成交查询响应
    * @param pData:指针若非空,返回用户分笔成交查询响应信息结构地址,表明客户分笔成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户分笔成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQrySerialTrade(DFITCStockRspQrySerialTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-实时成交查询响应
    * @param pData:指针若非空,返回用户实时成交查询响应信息结构地址,表明客户实时成交查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户实时成交查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-资金冻结明细查询响应
    * @param pData:指针若非空,返回用户资金冻结明细查询响应信息结构地址,表明客户资金冻结明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金冻结明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-证券冻结明细查询响应
    * @param pData:指针若非空,返回用户证券冻结明细查询响应信息结构地址,表明客户证券冻结明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户证券冻结明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-资金调拨明细查询响应
    * @param pData:指针若非空,返回用户资金调拨明细查询响应信息结构地址,表明客户资金调拨明细查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户资金调拨明细查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-撤单响应
    * @param pData:指针若非空,返回用户撤单响应信息结构地址,表明撤单请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明撤单请求失败
    */
    virtual void OnRspFASLWithdrawOrder(DFITCFASLRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-当前系统时间查询请求响应
    * @param pData:指针若非空,返回用户系统时间查询响应信息结构地址,表明系统时间查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明系统时间查询请求失败
    */
    virtual void OnRspFASLQrySystemTime(DFITCFASLRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-可转入担保证券查询请求响应
    * @param pData:指针若非空,返回可转入担保证券查询响应信息结构地址,表明可转入担保证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明可转入担保证券查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryTransferredContract(DFITCFASLRspQryTransferredContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-客户可取资金调出请求响应
    * @param pData:指针若非空,返回客户可取资金调出响应信息结构地址,表明客户可取资金调出请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明客户可取资金调出请求失败
    */
    virtual void OnRspFASLDesirableFundsOut(DFITCFASLRspDesirableFundsOutField *pData, DFITCSECRspInfoField *pRspInfo);
    /**
    * FASL-担保证券查询请求响应
    * @param pData:指针若非空,返回担保证券查询响应信息结构地址,表明担保证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明担保证券查询请求失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryGuaranteedContract(DFITCFASLRspQryGuaranteedContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-标的证券查询请求响应
    * @param pData:指针若非空,返回标的证券查询响应信息结构地址,表明标的证券查询请求成功
    * @param pRspInfo:指针若非空，返回错误信息地址，表明标的证券查询失败
    * @param bIsLast:返回值表明是否是最后一笔响应信息(0-否,1-是)
    */
    virtual void OnRspFASLQryUnderlyingContract(DFITCFASLRspQryUnderlyingContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast);
    /**
    * FASL-委托回报响应
    * @param pData:返回委托回报结构体的地址
    */
    virtual void OnFASLEntrustOrderRtn(DFITCStockEntrustOrderRtnField *pData);
    /**
    * FASL-成交回报响应
    * @param pData:返回成交回报结构体的地址
    */
    virtual void OnFASLTradeRtn(DFITCStockTradeRtnField *pData);
    /**
    * FASL-撤单回报响应
    * @param pData:返回撤单回报结构体的地址
    */
    virtual void OnFASLWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField *pData);

    //-------------------------------------------------------------------------------------
    //task：任务
    //-------------------------------------------------------------------------------------
    void processTask();

    void processFrontConnected(Task *task);

    void processFrontDisconnected(Task *task);

    void processRtnNotice(Task *task);

    void processRspError(Task *task);

    void processRspStockUserLogin(Task *task);

    void processRspStockUserLogout(Task *task);

    void processRspStockUserPasswordUpdate(Task *task);

    void processRspStockEntrustOrder(Task *task);

    void processRspStockWithdrawOrder(Task *task);

    void processRspStockQryEntrustOrder(Task *task);

    void processRspStockQryRealTimeTrade(Task *task);

    void processRspStockQrySerialTrade(Task *task);

    void processRspStockQryPosition(Task *task);

    void processRspStockQryCapitalAccountInfo(Task *task);

    void processRspStockQryAccountInfo(Task *task);

    void processRspStockQryShareholderInfo(Task *task);

    void processRspStockTransferFunds(Task *task);

    void processRspStockEntrustBatchOrder(Task *task);

    void processRspStockWithdrawBatchOrder(Task *task);

    void processRspStockCalcAbleEntrustQty(Task *task);

    void processRspStockCalcAblePurchaseETFQty(Task *task);

    void processRspStockQryFreezeFundsDetail(Task *task);

    void processRspStockQryFreezeStockDetail(Task *task);

    void processRspStockQryTransferStockDetail(Task *task);

    void processRspStockQryTransferFundsDetail(Task *task);

    void processRspStockQryStockInfo(Task *task);

    void processRspStockQryStockStaticInfo(Task *task);

    void processRspStockQryTradeTime(Task *task);

    void processStockEntrustOrderRtn(Task *task);

    void processStockTradeRtn(Task *task);

    void processStockWithdrawOrderRtn(Task *task);

    void processRspSOPUserLogin(Task *task);

    void processRspSOPUserLogout(Task *task);

    void processRspSOPUserPasswordUpdate(Task *task);

    void processRspSOPEntrustOrder(Task *task);

    void processRspSOPQuoteEntrustOrder(Task *task);

    void processRspSOPGroupSplit(Task *task);

    void processRspSOPGroupExectueOrder(Task *task);

    void processRspSOPQryGroupPosition(Task *task);

    void processRspSOPLockOUnLockStock(Task *task);

    void processRspSOPWithdrawOrder(Task *task);

    void processRspSOPQryEntrustOrder(Task *task);

    void processRspSOPQrySerialTrade(Task *task);

    void processRspSOPQryPosition(Task *task);

    void processRspSOPQryCollateralPosition(Task *task);

    void processRspSOPQryCapitalAccountInfo(Task *task);

    void processRspSOPQryAccountInfo(Task *task);

    void processRspSOPQryShareholderInfo(Task *task);

    void processRspSOPCalcAbleEntrustQty(Task *task);

    void processRspSOPQryAbleLockStock(Task *task);

    void processRspSOPQryContactInfo(Task *task);

    void processRspSOPExectueOrder(Task *task);

    void processRspSOPQryExecAssiInfo(Task *task);

    void processRspSOPQryTradeTime(Task *task);

    void processRspSOPQryExchangeInfo(Task *task);

    void processRspSOPQryCommission(Task *task);

    void processRspSOPQryDeposit(Task *task);

    void processRspSOPQryContractObjectInfo(Task *task);

    void processSOPEntrustOrderRtn(Task *task);

    void processSOPTradeRtn(Task *task);

    void processSOPWithdrawOrderRtn(Task *task);

    void processRspFASLUserLogin(Task *task);

    void processRspFASLUserLogout(Task *task);

    void processRspFASLQryAbleFinInfo(Task *task);

    void processRspFASLQryAbleSloInfo(Task *task);

    void processRspFASLTransferCollateral(Task *task);

    void processRspFASLDirectRepayment(Task *task);

    void processRspFASLRepayStockTransfer(Task *task);

    void processRspFASLEntrustCrdtOrder(Task *task);

    void processRspFASLEntrustOrder(Task *task);

    void processRspFASLCalcAbleEntrustCrdtQty(Task *task);

    void processRspFASLQryCrdtFunds(Task *task);

    void processRspFASLQryCrdtContract(Task *task);

    void processRspFASLQryCrdtConChangeInfo(Task *task);

    void processRspFASLTransferFunds(Task *task);

    void processRspFASLQryAccountInfo(Task *task);

    void processRspFASLQryCapitalAccountInfo(Task *task);

    void processRspFASLQryShareholderInfo(Task *task);

    void processRspFASLQryPosition(Task *task);

    void processRspFASLQryEntrustOrder(Task *task);

    void processRspFASLQrySerialTrade(Task *task);

    void processRspFASLQryRealTimeTrade(Task *task);

    void processRspFASLQryFreezeFundsDetail(Task *task);

    void processRspFASLQryFreezeStockDetail(Task *task);

    void processRspFASLQryTransferFundsDetail(Task *task);

    void processRspFASLWithdrawOrder(Task *task);

    void processRspFASLQrySystemTime(Task *task);

    void processRspFASLQryTransferredContract(Task *task);

    void processRspFASLDesirableFundsOut(Task *task);

    void processRspFASLQryGuaranteedContract(Task *task);

    void processRspFASLQryUnderlyingContract(Task *task);

    void processFASLEntrustOrderRtn(Task *task);

    void processFASLTradeRtn(Task *task);

    void processFASLWithdrawOrderRtn(Task *task);

    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------

    virtual void onFrontConnected() {};

    virtual void onFrontDisconnected(int reqid) {};

    virtual void onRtnNotice(const dict &data) {};

    virtual void onRspError(const dict &data) {};

    virtual void onRspStockUserLogin(const dict &data, const dict &error) {};

    virtual void onRspStockUserLogout(const dict &data, const dict &error) {};

    virtual void onRspStockUserPasswordUpdate(const dict &data, const dict &error) {};

    virtual void onRspStockEntrustOrder(const dict &data, const dict &error) {};

    virtual void onRspStockWithdrawOrder(const dict &data, const dict &error) {};

    virtual void onRspStockQryEntrustOrder(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryRealTimeTrade(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQrySerialTrade(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryPosition(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryCapitalAccountInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryAccountInfo(const dict &data, const dict &error) {};

    virtual void onRspStockQryShareholderInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockTransferFunds(const dict &data, const dict &error) {};

    virtual void onRspStockEntrustBatchOrder(const dict &data, const dict &error) {};

    virtual void onRspStockWithdrawBatchOrder(const dict &data, const dict &error) {};

    virtual void onRspStockCalcAbleEntrustQty(const dict &data, const dict &error) {};

    virtual void onRspStockCalcAblePurchaseETFQty(const dict &data, const dict &error) {};

    virtual void onRspStockQryFreezeFundsDetail(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryFreezeStockDetail(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryTransferStockDetail(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryTransferFundsDetail(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryStockInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryStockStaticInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspStockQryTradeTime(const dict &data, const dict &error) {};

    virtual void onStockEntrustOrderRtn(const dict &data) {};

    virtual void onStockTradeRtn(const dict &data) {};

    virtual void onStockWithdrawOrderRtn(const dict &data) {};

    virtual void onRspSOPUserLogin(const dict &data, const dict &error) {};

    virtual void onRspSOPUserLogout(const dict &data, const dict &error) {};

    virtual void onRspSOPUserPasswordUpdate(const dict &data, const dict &error) {};

    virtual void onRspSOPEntrustOrder(const dict &data, const dict &error) {};

    virtual void onRspSOPQuoteEntrustOrder(const dict &data, const dict &error) {};

    virtual void onRspSOPGroupSplit(const dict &data, const dict &error) {};

    virtual void onRspSOPGroupExectueOrder(const dict &data, const dict &error) {};

    virtual void onRspSOPQryGroupPosition(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPLockOUnLockStock(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPWithdrawOrder(const dict &data, const dict &error) {};

    virtual void onRspSOPQryEntrustOrder(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQrySerialTrade(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryPosition(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryCollateralPosition(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryCapitalAccountInfo(const dict &data, const dict &error) {};

    virtual void onRspSOPQryAccountInfo(const dict &data, const dict &error) {};

    virtual void onRspSOPQryShareholderInfo(const dict &data, const dict &error) {};

    virtual void onRspSOPCalcAbleEntrustQty(const dict &data, const dict &error) {};

    virtual void onRspSOPQryAbleLockStock(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryContactInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPExectueOrder(const dict &data, const dict &error) {};

    virtual void onRspSOPQryExecAssiInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryTradeTime(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryExchangeInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryCommission(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryDeposit(const dict &data, const dict &error, bool last) {};

    virtual void onRspSOPQryContractObjectInfo(const dict &data, const dict &error, bool last) {};

    virtual void onSOPEntrustOrderRtn(const dict &data) {};

    virtual void onSOPTradeRtn(const dict &data) {};

    virtual void onSOPWithdrawOrderRtn(const dict &data) {};

    virtual void onRspFASLUserLogin(const dict &data, const dict &error) {};

    virtual void onRspFASLUserLogout(const dict &data, const dict &error) {};

    virtual void onRspFASLQryAbleFinInfo(const dict &data, const dict &error) {};

    virtual void onRspFASLQryAbleSloInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLTransferCollateral(const dict &data, const dict &error) {};

    virtual void onRspFASLDirectRepayment(const dict &data, const dict &error) {};

    virtual void onRspFASLRepayStockTransfer(const dict &data, const dict &error) {};

    virtual void onRspFASLEntrustCrdtOrder(const dict &data, const dict &error) {};

    virtual void onRspFASLEntrustOrder(const dict &data, const dict &error) {};

    virtual void onRspFASLCalcAbleEntrustCrdtQty(const dict &data, const dict &error) {};

    virtual void onRspFASLQryCrdtFunds(const dict &data, const dict &error) {};

    virtual void onRspFASLQryCrdtContract(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryCrdtConChangeInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLTransferFunds(const dict &data, const dict &error) {};

    virtual void onRspFASLQryAccountInfo(const dict &data, const dict &error) {};

    virtual void onRspFASLQryCapitalAccountInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryShareholderInfo(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryPosition(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryEntrustOrder(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQrySerialTrade(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryRealTimeTrade(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryFreezeFundsDetail(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryFreezeStockDetail(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryTransferFundsDetail(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLWithdrawOrder(const dict &data, const dict &error) {};

    virtual void onRspFASLQrySystemTime(const dict &data, const dict &error) {};

    virtual void onRspFASLQryTransferredContract(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLDesirableFundsOut(const dict &data, const dict &error) {};

    virtual void onRspFASLQryGuaranteedContract(const dict &data, const dict &error, bool last) {};

    virtual void onRspFASLQryUnderlyingContract(const dict &data, const dict &error, bool last) {};

    virtual void onFASLEntrustOrderRtn(const dict &data) {};

    virtual void onFASLTradeRtn(const dict &data) {};

    virtual void onFASLWithdrawOrderRtn(const dict &data) {};

    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------

    void createDFITCSECTraderApi(string pszFlowPath);

    void release();

    int init(string protocol);

    int exit();

    int subscribePrivateTopic(int nResumeType);
    int reqStockUserLogin(const dict &req);

    int reqStockUserLogout(const dict &req);

    int reqStockUserPasswordUpdate(const dict &req);

    int reqStockEntrustOrder(const dict &req);

    int reqStockWithdrawOrder(const dict &req);

    int reqStockQryEntrustOrder(const dict &req);

    int reqStockQryRealTimeTrade(const dict &req);

    int reqStockQrySerialTrade(const dict &req);

    int reqStockQryPosition(const dict &req);

    int reqStockQryCapitalAccountInfo(const dict &req);

    int reqStockQryAccountInfo(const dict &req);

    int reqStockQryShareholderInfo(const dict &req);

    int reqStockTransferFunds(const dict &req);

    int reqStockEntrustBatchOrder(const dict &req);

    int reqStockWithdrawBatchOrder(const dict &req);

    int reqStockCalcAbleEntrustQty(const dict &req);

    int reqStockCalcAblePurchaseETFQty(const dict &req);

    int reqStockQryFreezeFundsDetail(const dict &req);

    int reqStockQryFreezeStockDetail(const dict &req);

    int reqStockQryTransferFundsDetail(const dict &req);

    int reqStockQryTransferStockDetail(const dict &req);

    int reqStockQryStockInfo(const dict &req);

    int reqStockQryStockStaticInfo(const dict &req);

    int reqStockQryTradeTime(const dict &req);

    int reqSOPUserLogin(const dict &req);

    int reqSOPUserLogout(const dict &req);

    int reqSOPUserPasswordUpdate(const dict &req);

    int reqSOPEntrustOrder(const dict &req);

    int reqSOPQuoteEntrustOrder(const dict &req);

    int reqSOPGroupSplit(const dict &req);

    int reqSOPGroupExectueOrder(const dict &req);

    int reqSOPQryGroupPosition(const dict &req);

    int reqSOPLockOUnLockStock(const dict &req);

    int reqSOPWithdrawOrder(const dict &req);

    int reqSOPQryEntrustOrder(const dict &req);

    int reqSOPQrySerialTrade(const dict &req);

    int reqSOPQryPosition(const dict &req);

    int reqSOPQryCollateralPosition(const dict &req);

    int reqSOPQryCapitalAccountInfo(const dict &req);

    int reqSOPQryAccountInfo(const dict &req);

    int reqSOPQryShareholderInfo(const dict &req);

    int reqSOPCalcAbleEntrustQty(const dict &req);

    int reqSOPQryAbleLockStock(const dict &req);

    int reqSOPQryContactInfo(const dict &req);

    int reqSOPExectueOrder(const dict &req);

    int reqSOPQryExecAssiInfo(const dict &req);

    int reqSOPQryTradeTime(const dict &req);

    int reqSOPQryExchangeInfo(const dict &req);

    int reqSOPQryCommission(const dict &req);

    int reqSOPQryDeposit(const dict &req);

    int reqSOPQryContractObjectInfo(const dict &req);

    int reqFASLUserLogin(const dict &req);

    int reqFASLUserLogout(const dict &req);

    int reqFASLQryAbleFinInfo(const dict &req);

    int reqFASLQryAbleSloInfo(const dict &req);

    int reqFASLTransferCollateral(const dict &req);

    int reqFASLDirectRepayment(const dict &req);

    int reqFASLRepayStockTransfer(const dict &req);

    int reqFASLEntrustCrdtOrder(const dict &req);

    int reqFASLEntrsuctOrder(const dict &req);

    int reqFASLWithdrawOrder(const dict &req);

    int reqFASLCalcAbleEntrustCrdtQty(const dict &req);

    int reqFASLQryCrdtFunds(const dict &req);

    int reqFASLQryCrdtContract(const dict &req);

    int reqFASLQryCrdtConChangeInfo(const dict &req);

    int reqFASLTransferFunds(const dict &req);

    int reqFASLQryAccountInfo(const dict &req);

    int reqFASLQryCapitalAccountInfo(const dict &req);

    int reqFASLQryShareholderInfo(const dict &req);

    int reqFASLQryPosition(const dict &req);

    int reqFASLQryEntrustOrder(const dict &req);

    int reqFASLQrySerialTrade(const dict &req);

    int reqFASLQryRealTimeTrade(const dict &req);

    int reqFASLQryFreezeFundsDetail(const dict &req);

    int reqFASLQryFreezeStockDetail(const dict &req);

    int reqFASLQryTransferFundsDetail(const dict &req);

    int reqFASLQrySystemTime(const dict &req);

    int reqFASLQryTransferredContract(const dict &req);

    int reqFASLDesirableFundsOut(const dict &req);

    int reqFASLQryGuaranteedContract(const dict &req);

    int reqFASLQryUnderlyingContract(const dict &req);

};