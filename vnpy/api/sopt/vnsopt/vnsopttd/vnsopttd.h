#ifdef WIN32
#include "stdafx.h"
#endif

#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONRSPAUTHENTICATE 3
#define ONRSPUSERLOGIN 4
#define ONRSPUSERLOGOUT 5
#define ONRSPUSERPASSWORDUPDATE 6
#define ONRSPTRADINGACCOUNTPASSWORDUPDATE 7
#define ONRSPORDERINSERT 8
#define ONRSPPARKEDORDERINSERT 9
#define ONRSPPARKEDORDERACTION 10
#define ONRSPORDERACTION 11
#define ONRSPQUERYMAXORDERVOLUME 12
#define ONRSPSETTLEMENTINFOCONFIRM 13
#define ONRSPREMOVEPARKEDORDER 14
#define ONRSPREMOVEPARKEDORDERACTION 15
#define ONRSPEXECORDERINSERT 16
#define ONRSPEXECORDERACTION 17
#define ONRSPFORQUOTEINSERT 18
#define ONRSPQUOTEINSERT 19
#define ONRSPQUOTEACTION 20
#define ONRSPLOCKINSERT 21
#define ONRSPBATCHORDERACTION 22
#define ONRSPCOMBACTIONINSERT 23
#define ONRSPQRYORDER 24
#define ONRSPQRYTRADE 25
#define ONRSPQRYINVESTORPOSITION 26
#define ONRSPQRYTRADINGACCOUNT 27
#define ONRSPQRYINVESTOR 28
#define ONRSPQRYTRADINGCODE 29
#define ONRSPQRYINSTRUMENTMARGINRATE 30
#define ONRSPQRYINSTRUMENTCOMMISSIONRATE 31
#define ONRSPQRYEXCHANGE 32
#define ONRSPQRYPRODUCT 33
#define ONRSPQRYINSTRUMENT 34
#define ONRSPQRYDEPTHMARKETDATA 35
#define ONRSPQRYSETTLEMENTINFO 36
#define ONRSPQRYTRANSFERBANK 37
#define ONRSPQRYINVESTORPOSITIONDETAIL 38
#define ONRSPQRYNOTICE 39
#define ONRSPQRYSETTLEMENTINFOCONFIRM 40
#define ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL 41
#define ONRSPQRYCFMMCTRADINGACCOUNTKEY 42
#define ONRSPQRYEWARRANTOFFSET 43
#define ONRSPQRYINVESTORPRODUCTGROUPMARGIN 44
#define ONRSPQRYEXCHANGEMARGINRATE 45
#define ONRSPQRYEXCHANGEMARGINRATEADJUST 46
#define ONRSPQRYEXCHANGERATE 47
#define ONRSPQRYSECAGENTACIDMAP 48
#define ONRSPQRYPRODUCTEXCHRATE 49
#define ONRSPQRYPRODUCTGROUP 50
#define ONRSPQRYMMINSTRUMENTCOMMISSIONRATE 51
#define ONRSPQRYMMOPTIONINSTRCOMMRATE 52
#define ONRSPQRYINSTRUMENTORDERCOMMRATE 53
#define ONRSPQRYOPTIONINSTRTRADECOST 54
#define ONRSPQRYOPTIONINSTRCOMMRATE 55
#define ONRSPQRYEXECORDER 56
#define ONRSPQRYFORQUOTE 57
#define ONRSPQRYQUOTE 58
#define ONRSPQRYLOCK 59
#define ONRSPQRYLOCKPOSITION 60
#define ONRSPQRYETFOPTIONINSTRCOMMRATE 61
#define ONRSPQRYINVESTORLEVEL 62
#define ONRSPQRYEXECFREEZE 63
#define ONRSPQRYCOMBINSTRUMENTGUARD 64
#define ONRSPQRYCOMBACTION 65
#define ONRSPQRYTRANSFERSERIAL 66
#define ONRSPQRYACCOUNTREGISTER 67
#define ONRSPERROR 68
#define ONRTNORDER 69
#define ONRTNTRADE 70
#define ONERRRTNORDERINSERT 71
#define ONERRRTNORDERACTION 72
#define ONRTNINSTRUMENTSTATUS 73
#define ONRTNBULLETIN 74
#define ONRTNTRADINGNOTICE 75
#define ONRTNERRORCONDITIONALORDER 76
#define ONRTNEXECORDER 77
#define ONERRRTNEXECORDERINSERT 78
#define ONERRRTNEXECORDERACTION 79
#define ONERRRTNFORQUOTEINSERT 80
#define ONRTNQUOTE 81
#define ONERRRTNQUOTEINSERT 82
#define ONERRRTNQUOTEACTION 83
#define ONRTNFORQUOTERSP 84
#define ONRTNCFMMCTRADINGACCOUNTTOKEN 85
#define ONRTNLOCK 86
#define ONERRRTNLOCKINSERT 87
#define ONERRRTNBATCHORDERACTION 88
#define ONRTNCOMBACTION 89
#define ONERRRTNCOMBACTIONINSERT 90
#define ONRSPQRYCONTRACTBANK 91
#define ONRSPQRYPARKEDORDER 92
#define ONRSPQRYPARKEDORDERACTION 93
#define ONRSPQRYTRADINGNOTICE 94
#define ONRSPQRYBROKERTRADINGPARAMS 95
#define ONRSPQRYBROKERTRADINGALGOS 96
#define ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN 97
#define ONRTNFROMBANKTOFUTUREBYBANK 98
#define ONRTNFROMFUTURETOBANKBYBANK 99
#define ONRTNREPEALFROMBANKTOFUTUREBYBANK 100
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 101
#define ONRTNFROMBANKTOFUTUREBYFUTURE 102
#define ONRTNFROMFUTURETOBANKBYFUTURE 103
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL 104
#define ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL 105
#define ONRTNQUERYBANKBALANCEBYFUTURE 106
#define ONERRRTNBANKTOFUTUREBYFUTURE 107
#define ONERRRTNFUTURETOBANKBYFUTURE 108
#define ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL 109
#define ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL 110
#define ONERRRTNQUERYBANKBALANCEBYFUTURE 111
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTURE 112
#define ONRTNREPEALFROMFUTURETOBANKBYFUTURE 113
#define ONRSPFROMBANKTOFUTUREBYFUTURE 114
#define ONRSPFROMFUTURETOBANKBYFUTURE 115
#define ONRSPQUERYBANKACCOUNTMONEYBYFUTURE 116
#define ONRTNOPENACCOUNTBYBANK 117
#define ONRTNCANCELACCOUNTBYBANK 118
#define ONRTNCHANGEACCOUNTBYBANK 119
#define ONRTNRESOPENACCCONFIRMTPDBYBANK 120
#define ONRSPRESERVEOPENACCOUNTTPDBYFUTURE 121
#define ONRSPSECURITIESDEPOSITINTERESTBYFUTURE 122
#define ONRSPDAYENDFILEREADYBYFUTURE 123
#define ONRSPEXECCOMBINEORDERINSERT 124
#define ONRSPEXECCOMBINEORDERACTION 125
#define ONRSPQRYEXECCOMBINEORDER 126
#define ONERRRTNEXECCOMBINEORDERACTION 127
#define ONERRRTNEXECCOMBINEORDERINSERT 128
#define ONRTNEXECCOMBINEORDER 129


#include "sopt/ThostFtdcTraderApi.h"
#include "pybind11/pybind11.h"
#include "vnsopt.h"

using namespace pybind11;

class TdApi :public CThostFtdcTraderSpi
{
private:
    CThostFtdcTraderApi* api;
    TaskQueue task_queue;
    bool active = false;
    thread task_thread;
public:
    TdApi() {};
    ~TdApi() {
        if (this->active) {
            this->exit();
        }
    }
    ////////////////////////////////////////////////////////////
    //////////原生SPI回调函数
    ////////////////////////////////////////////////////////////
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

    ///客户端认证响应
    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


    ///登录请求响应
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///登出请求响应
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///用户口令更新请求响应
    virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///资金账户口令更新请求响应
    virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单录入请求响应
    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///预埋单录入请求响应
    virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///预埋撤单录入请求响应
    virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单操作请求响应
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///查询最大报单数量响应
    virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///投资者结算结果确认响应
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///删除预埋单响应
    virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///删除预埋撤单响应
    virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///执行宣告录入请求响应
    virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///执行宣告操作请求响应
    virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///询价录入请求响应
    virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报价录入请求响应
    virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报价操作请求响应
    virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///锁定应答
    virtual void OnRspLockInsert(CThostFtdcInputLockField *pInputLock, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///批量报单操作请求响应
    virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///申请组合录入请求响应
    virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询报单响应
    virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询成交响应
    virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者持仓响应
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询资金账户响应
    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者响应
    virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询交易编码响应
    virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询合约保证金率响应
    virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询合约手续费率响应
    virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询交易所响应
    virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询产品响应
    virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询合约响应
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询行情响应
    virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者结算结果响应
    virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询转帐银行响应
    virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者持仓明细响应
    virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询客户通知响应
    virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询结算信息确认响应
    virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者持仓明细响应
    virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///查询保证金监管系统经纪公司资金账户密钥响应
    virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询仓单折抵信息响应
    virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者品种/跨品种保证金响应
    virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询交易所保证金率响应
    virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询交易所调整保证金率响应
    virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询汇率响应
    virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询二级代理操作员银期权限响应
    virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询产品报价汇率
    virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询产品组
    virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询做市商合约手续费率响应
    virtual void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询做市商期权合约手续费响应
    virtual void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询报单手续费响应
    virtual void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询期权交易成本响应
    virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询期权合约手续费响应
    virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询执行宣告响应
    virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询询价响应
    virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询报价响应
    virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询锁定应答
    virtual void OnRspQryLock(CThostFtdcLockField *pLock, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询锁定证券仓位应答
    virtual void OnRspQryLockPosition(CThostFtdcLockPositionField *pLockPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询ETF期权合约手续费响应
    virtual void OnRspQryETFOptionInstrCommRate(CThostFtdcETFOptionInstrCommRateField *pETFOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者分级
    virtual void OnRspQryInvestorLevel(CThostFtdcInvestorLevelField *pInvestorLevel, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询E+1日行权冻结响应
    virtual void OnRspQryExecFreeze(CThostFtdcExecFreezeField *pExecFreeze, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询组合合约安全系数响应
    virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询申请组合响应
    virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询转帐流水响应
    virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询银期签约关系响应
    virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///错误应答
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单通知
    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

    ///成交通知
    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

    ///报单录入错误回报
    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

    ///报单操作错误回报
    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

    ///合约交易状态通知
    virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

    ///交易所公告通知
    virtual void OnRtnBulletin(CThostFtdcBulletinField *pBulletin);

    ///交易通知
    virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

    ///提示条件单校验错误
    virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

    ///执行宣告通知
    virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

    ///执行宣告录入错误回报
    virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);

    ///执行宣告操作错误回报
    virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);

    ///询价录入错误回报
    virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);

    ///报价通知
    virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);

    ///报价录入错误回报
    virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);

    ///报价操作错误回报
    virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);

    ///询价通知
    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

    ///保证金监控中心用户令牌
    virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);

    ///锁定通知
    virtual void OnRtnLock(CThostFtdcLockField *pLock);

    ///锁定错误通知
    virtual void OnErrRtnLockInsert(CThostFtdcInputLockField *pInputLock, CThostFtdcRspInfoField *pRspInfo);

    ///批量报单操作错误回报
    virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);

    ///申请组合通知
    virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction);

    ///申请组合录入错误回报
    virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);

    ///请求查询签约银行响应
    virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询预埋单响应
    virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询预埋撤单响应
    virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询交易通知响应
    virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询经纪公司交易参数响应
    virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询经纪公司交易算法响应
    virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询监控中心用户令牌
    virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///银行发起银行资金转期货通知
    virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer);

    ///银行发起期货资金转银行通知
    virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer);

    ///银行发起冲正银行转期货通知
    virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal);

    ///银行发起冲正期货转银行通知
    virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal);

    ///期货发起银行资金转期货通知
    virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);

    ///期货发起期货资金转银行通知
    virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);

    ///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

    ///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

    ///期货发起查询银行余额通知
    virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);

    ///期货发起银行资金转期货错误回报
    virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

    ///期货发起期货资金转银行错误回报
    virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

    ///系统运行时期货端手工发起冲正银行转期货错误回报
    virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

    ///系统运行时期货端手工发起冲正期货转银行错误回报
    virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

    ///期货发起查询银行余额错误回报
    virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);

    ///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal);

    ///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
    virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal);

    ///期货发起银行资金转期货应答
    virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///期货发起期货资金转银行应答
    virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///期货发起查询银行余额应答
    virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///银行发起银期开户通知
    virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount);

    ///银行发起银期销户通知
    virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount);

    ///银行发起变更银行账号通知
    virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount);

    ///银行发起第三方存管业务开户确认通知
    virtual void OnRtnResOpenAccConfirmTpdByBank(CThostFtdcResOpenAccConfirmTpdField *pResOpenAccConfirmTpd);

    ///期货发起第三方存管业务开户预指定应答
    virtual void OnRspReserveOpenAccountTpdByFuture(CThostFtdcReqReserveOpenAccountTpdField *pReqReserveOpenAccountTpd, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///期货发起第三方存管证券资金结息应答
    virtual void OnRspSecuritiesDepositInterestByFuture(CThostFtdcReqSecuritiesDepositInterestField *pReqSecuritiesDepositInterest, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///期货发起日终文件就绪应答
    virtual void OnRspDayEndFileReadyByFuture(CThostFtdcReqDayEndFileReadyField *pReqDayEndFileReady, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///行权指令合并录入请求响应
    virtual void OnRspExecCombineOrderInsert(CThostFtdcInputExecCombineOrderField *pInputExecCombineOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///行权指令合并操作请求响应
    virtual void OnRspExecCombineOrderAction(CThostFtdcInputExecCombineOrderActionField *pInputExecCombineOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询行权指令合并响应
    virtual void OnRspQryExecCombineOrder(CThostFtdcExecCombineOrderField *pExecCombineOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///行权指令合并操作错误回报
    virtual void OnErrRtnExecCombineOrderAction(CThostFtdcExecCombineOrderActionField *pExecCombineOrderAction, CThostFtdcRspInfoField *pRspInfo);

    ///行权指令合并录入错误回报
    virtual void OnErrRtnExecCombineOrderInsert(CThostFtdcInputExecCombineOrderField *pInputExecCombineOrder, CThostFtdcRspInfoField *pRspInfo);

    ///行权指令合并通知
    virtual void OnRtnExecCombineOrder(CThostFtdcExecCombineOrderField *pExecCombineOrder);
    ////////////////////////////////////////////////////////////
    //////////python封装的回调函数
    ////////////////////////////////////////////////////////////

    virtual void onFrontConnected() {};

    virtual void onFrontDisconnected(int reqid) {};

    virtual void onHeartBeatWarning(int reqid) {};

    virtual void onRspAuthenticate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspUserPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspTradingAccountPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspParkedOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQueryMaxOrderVolume(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspSettlementInfoConfirm(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspRemoveParkedOrder(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspRemoveParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspExecOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspExecOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspForQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQuoteInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQuoteAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspLockInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspBatchOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspCombActionInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestor(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryTradingCode(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInstrumentMarginRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInstrumentCommissionRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryProduct(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryDepthMarketData(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQrySettlementInfo(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryTransferBank(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestorPositionDetail(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryNotice(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQrySettlementInfoConfirm(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestorPositionCombineDetail(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryCFMMCTradingAccountKey(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryEWarrantOffset(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestorProductGroupMargin(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryExchangeMarginRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryExchangeMarginRateAdjust(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryExchangeRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQrySecAgentACIDMap(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryProductExchRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryProductGroup(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryMMInstrumentCommissionRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryMMOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInstrumentOrderCommRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryOptionInstrTradeCost(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryExecOrder(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryForQuote(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryQuote(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryLock(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryLockPosition(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryETFOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestorLevel(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryExecFreeze(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryCombInstrumentGuard(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryCombAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryTransferSerial(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryAccountregister(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspError(const dict &error, int reqid, bool last) {};

    virtual void onRtnOrder(const dict &data) {};

    virtual void onRtnTrade(const dict &data) {};

    virtual void onErrRtnOrderInsert(const dict &data, const dict &error) {};

    virtual void onErrRtnOrderAction(const dict &data, const dict &error) {};

    virtual void onRtnInstrumentStatus(const dict &data) {};

    virtual void onRtnBulletin(const dict &data) {};

    virtual void onRtnTradingNotice(const dict &data) {};

    virtual void onRtnErrorConditionalOrder(const dict &data) {};

    virtual void onRtnExecOrder(const dict &data) {};

    virtual void onErrRtnExecOrderInsert(const dict &data, const dict &error) {};

    virtual void onErrRtnExecOrderAction(const dict &data, const dict &error) {};

    virtual void onErrRtnForQuoteInsert(const dict &data, const dict &error) {};

    virtual void onRtnQuote(const dict &data) {};

    virtual void onErrRtnQuoteInsert(const dict &data, const dict &error) {};

    virtual void onErrRtnQuoteAction(const dict &data, const dict &error) {};

    virtual void onRtnForQuoteRsp(const dict &data) {};

    virtual void onRtnCFMMCTradingAccountToken(const dict &data) {};

    virtual void onRtnLock(const dict &data) {};

    virtual void onErrRtnLockInsert(const dict &data, const dict &error) {};

    virtual void onErrRtnBatchOrderAction(const dict &data, const dict &error) {};

    virtual void onRtnCombAction(const dict &data) {};

    virtual void onErrRtnCombActionInsert(const dict &data, const dict &error) {};

    virtual void onRspQryContractBank(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryParkedOrder(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryParkedOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryTradingNotice(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryBrokerTradingParams(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryBrokerTradingAlgos(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQueryCFMMCTradingAccountToken(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRtnFromBankToFutureByBank(const dict &data) {};

    virtual void onRtnFromFutureToBankByBank(const dict &data) {};

    virtual void onRtnRepealFromBankToFutureByBank(const dict &data) {};

    virtual void onRtnRepealFromFutureToBankByBank(const dict &data) {};

    virtual void onRtnFromBankToFutureByFuture(const dict &data) {};

    virtual void onRtnFromFutureToBankByFuture(const dict &data) {};

    virtual void onRtnRepealFromBankToFutureByFutureManual(const dict &data) {};

    virtual void onRtnRepealFromFutureToBankByFutureManual(const dict &data) {};

    virtual void onRtnQueryBankBalanceByFuture(const dict &data) {};

    virtual void onErrRtnBankToFutureByFuture(const dict &data, const dict &error) {};

    virtual void onErrRtnFutureToBankByFuture(const dict &data, const dict &error) {};

    virtual void onErrRtnRepealBankToFutureByFutureManual(const dict &data, const dict &error) {};

    virtual void onErrRtnRepealFutureToBankByFutureManual(const dict &data, const dict &error) {};

    virtual void onErrRtnQueryBankBalanceByFuture(const dict &data, const dict &error) {};

    virtual void onRtnRepealFromBankToFutureByFuture(const dict &data) {};

    virtual void onRtnRepealFromFutureToBankByFuture(const dict &data) {};

    virtual void onRspFromBankToFutureByFuture(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspFromFutureToBankByFuture(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQueryBankAccountMoneyByFuture(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRtnOpenAccountByBank(const dict &data) {};

    virtual void onRtnCancelAccountByBank(const dict &data) {};

    virtual void onRtnChangeAccountByBank(const dict &data) {};

    virtual void onRtnResOpenAccConfirmTpdByBank(const dict &data) {};

    virtual void onRspReserveOpenAccountTpdByFuture(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspSecuritiesDepositInterestByFuture(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspDayEndFileReadyByFuture(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspExecCombineOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspExecCombineOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryExecCombineOrder(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onErrRtnExecCombineOrderAction(const dict &data, const dict &error) {};

    virtual void onErrRtnExecCombineOrderInsert(const dict &data, const dict &error) {};

    virtual void onRtnExecCombineOrder(const dict &data) {};

    //////////////////////////////////////////////////
    /////process
    //////////////////////////////////////////////////
    void processTask();

    void processFrontConnected(Task *task);

    void processFrontDisconnected(Task *task);

    void processHeartBeatWarning(Task *task);

    void processRspAuthenticate(Task *task);

    void processRspUserLogin(Task *task);

    void processRspUserLogout(Task *task);

    void processRspUserPasswordUpdate(Task *task);

    void processRspTradingAccountPasswordUpdate(Task *task);

    void processRspOrderInsert(Task *task);

    void processRspParkedOrderInsert(Task *task);

    void processRspParkedOrderAction(Task *task);

    void processRspOrderAction(Task *task);

    void processRspQueryMaxOrderVolume(Task *task);

    void processRspSettlementInfoConfirm(Task *task);

    void processRspRemoveParkedOrder(Task *task);

    void processRspRemoveParkedOrderAction(Task *task);

    void processRspExecOrderInsert(Task *task);

    void processRspExecOrderAction(Task *task);

    void processRspForQuoteInsert(Task *task);

    void processRspQuoteInsert(Task *task);

    void processRspQuoteAction(Task *task);

    void processRspLockInsert(Task *task);

    void processRspBatchOrderAction(Task *task);

    void processRspCombActionInsert(Task *task);

    void processRspQryOrder(Task *task);

    void processRspQryTrade(Task *task);

    void processRspQryInvestorPosition(Task *task);

    void processRspQryTradingAccount(Task *task);

    void processRspQryInvestor(Task *task);

    void processRspQryTradingCode(Task *task);

    void processRspQryInstrumentMarginRate(Task *task);

    void processRspQryInstrumentCommissionRate(Task *task);

    void processRspQryExchange(Task *task);

    void processRspQryProduct(Task *task);

    void processRspQryInstrument(Task *task);

    void processRspQryDepthMarketData(Task *task);

    void processRspQrySettlementInfo(Task *task);

    void processRspQryTransferBank(Task *task);

    void processRspQryInvestorPositionDetail(Task *task);

    void processRspQryNotice(Task *task);

    void processRspQrySettlementInfoConfirm(Task *task);

    void processRspQryInvestorPositionCombineDetail(Task *task);

    void processRspQryCFMMCTradingAccountKey(Task *task);

    void processRspQryEWarrantOffset(Task *task);

    void processRspQryInvestorProductGroupMargin(Task *task);

    void processRspQryExchangeMarginRate(Task *task);

    void processRspQryExchangeMarginRateAdjust(Task *task);

    void processRspQryExchangeRate(Task *task);

    void processRspQrySecAgentACIDMap(Task *task);

    void processRspQryProductExchRate(Task *task);

    void processRspQryProductGroup(Task *task);

    void processRspQryMMInstrumentCommissionRate(Task *task);

    void processRspQryMMOptionInstrCommRate(Task *task);

    void processRspQryInstrumentOrderCommRate(Task *task);

    void processRspQryOptionInstrTradeCost(Task *task);

    void processRspQryOptionInstrCommRate(Task *task);

    void processRspQryExecOrder(Task *task);

    void processRspQryForQuote(Task *task);

    void processRspQryQuote(Task *task);

    void processRspQryLock(Task *task);

    void processRspQryLockPosition(Task *task);

    void processRspQryETFOptionInstrCommRate(Task *task);

    void processRspQryInvestorLevel(Task *task);

    void processRspQryExecFreeze(Task *task);

    void processRspQryCombInstrumentGuard(Task *task);

    void processRspQryCombAction(Task *task);

    void processRspQryTransferSerial(Task *task);

    void processRspQryAccountregister(Task *task);

    void processRspError(Task *task);

    void processRtnOrder(Task *task);

    void processRtnTrade(Task *task);

    void processErrRtnOrderInsert(Task *task);

    void processErrRtnOrderAction(Task *task);

    void processRtnInstrumentStatus(Task *task);

    void processRtnBulletin(Task *task);

    void processRtnTradingNotice(Task *task);

    void processRtnErrorConditionalOrder(Task *task);

    void processRtnExecOrder(Task *task);

    void processErrRtnExecOrderInsert(Task *task);

    void processErrRtnExecOrderAction(Task *task);

    void processErrRtnForQuoteInsert(Task *task);

    void processRtnQuote(Task *task);

    void processErrRtnQuoteInsert(Task *task);

    void processErrRtnQuoteAction(Task *task);

    void processRtnForQuoteRsp(Task *task);

    void processRtnCFMMCTradingAccountToken(Task *task);

    void processRtnLock(Task *task);

    void processErrRtnLockInsert(Task *task);

    void processErrRtnBatchOrderAction(Task *task);

    void processRtnCombAction(Task *task);

    void processErrRtnCombActionInsert(Task *task);

    void processRspQryContractBank(Task *task);

    void processRspQryParkedOrder(Task *task);

    void processRspQryParkedOrderAction(Task *task);

    void processRspQryTradingNotice(Task *task);

    void processRspQryBrokerTradingParams(Task *task);

    void processRspQryBrokerTradingAlgos(Task *task);

    void processRspQueryCFMMCTradingAccountToken(Task *task);

    void processRtnFromBankToFutureByBank(Task *task);

    void processRtnFromFutureToBankByBank(Task *task);

    void processRtnRepealFromBankToFutureByBank(Task *task);

    void processRtnRepealFromFutureToBankByBank(Task *task);

    void processRtnFromBankToFutureByFuture(Task *task);

    void processRtnFromFutureToBankByFuture(Task *task);

    void processRtnRepealFromBankToFutureByFutureManual(Task *task);

    void processRtnRepealFromFutureToBankByFutureManual(Task *task);

    void processRtnQueryBankBalanceByFuture(Task *task);

    void processErrRtnBankToFutureByFuture(Task *task);

    void processErrRtnFutureToBankByFuture(Task *task);

    void processErrRtnRepealBankToFutureByFutureManual(Task *task);

    void processErrRtnRepealFutureToBankByFutureManual(Task *task);

    void processErrRtnQueryBankBalanceByFuture(Task *task);

    void processRtnRepealFromBankToFutureByFuture(Task *task);

    void processRtnRepealFromFutureToBankByFuture(Task *task);

    void processRspFromBankToFutureByFuture(Task *task);

    void processRspFromFutureToBankByFuture(Task *task);

    void processRspQueryBankAccountMoneyByFuture(Task *task);

    void processRtnOpenAccountByBank(Task *task);

    void processRtnCancelAccountByBank(Task *task);

    void processRtnChangeAccountByBank(Task *task);

    void processRtnResOpenAccConfirmTpdByBank(Task *task);

    void processRspReserveOpenAccountTpdByFuture(Task *task);

    void processRspSecuritiesDepositInterestByFuture(Task *task);

    void processRspDayEndFileReadyByFuture(Task *task);

    void processRspExecCombineOrderInsert(Task *task);

    void processRspExecCombineOrderAction(Task *task);

    void processRspQryExecCombineOrder(Task *task);

    void processErrRtnExecCombineOrderAction(Task *task);

    void processErrRtnExecCombineOrderInsert(Task *task);

    void processRtnExecCombineOrder(Task *task);

    //////////////////////////////////////////////////
    /////api主动函数
    //////////////////////////////////////////////////
    void createFtdcTraderApi(string pszFlowPath = "");

    void release();

    void init();

    int join();

    int exit();

    string getTradingDay();

    void registerFront(string pszFrontAddress);

    void subscribePrivateTopic(int x);

    void subscribePublicTopic(int x);

    int reqAuthenticate(const dict &req, int reqid);

    int reqUserLogin(const dict &req, int reqid);

    int reqUserLogout(const dict &req, int reqid);

    int reqUserPasswordUpdate(const dict &req, int reqid);

    int reqTradingAccountPasswordUpdate(const dict &req, int reqid);

    int reqOrderInsert(const dict &req, int reqid);

    int reqParkedOrderInsert(const dict &req, int reqid);

    int reqParkedOrderAction(const dict &req, int reqid);

    int reqOrderAction(const dict &req, int reqid);

    int reqQueryMaxOrderVolume(const dict &req, int reqid);

    int reqSettlementInfoConfirm(const dict &req, int reqid);

    int reqRemoveParkedOrder(const dict &req, int reqid);

    int reqRemoveParkedOrderAction(const dict &req, int reqid);

    int reqExecOrderInsert(const dict &req, int reqid);

    int reqExecOrderAction(const dict &req, int reqid);

    int reqForQuoteInsert(const dict &req, int reqid);

    int reqQuoteInsert(const dict &req, int reqid);

    int reqQuoteAction(const dict &req, int reqid);

    int reqLockInsert(const dict &req, int reqid);

    int reqBatchOrderAction(const dict &req, int reqid);

    int reqCombActionInsert(const dict &req, int reqid);

    int reqQryOrder(const dict &req, int reqid);

    int reqQryTrade(const dict &req, int reqid);

    int reqQryInvestorPosition(const dict &req, int reqid);

    int reqQryTradingAccount(const dict &req, int reqid);

    int reqQryInvestor(const dict &req, int reqid);

    int reqQryTradingCode(const dict &req, int reqid);

    int reqQryInstrumentMarginRate(const dict &req, int reqid);

    int reqQryInstrumentCommissionRate(const dict &req, int reqid);

    int reqQryExchange(const dict &req, int reqid);

    int reqQryProduct(const dict &req, int reqid);

    int reqQryInstrument(const dict &req, int reqid);

    int reqQryDepthMarketData(const dict &req, int reqid);

    int reqQrySettlementInfo(const dict &req, int reqid);

    int reqQryTransferBank(const dict &req, int reqid);

    int reqQryInvestorPositionDetail(const dict &req, int reqid);

    int reqQryNotice(const dict &req, int reqid);

    int reqQrySettlementInfoConfirm(const dict &req, int reqid);

    int reqQryInvestorPositionCombineDetail(const dict &req, int reqid);

    int reqQryCFMMCTradingAccountKey(const dict &req, int reqid);

    int reqQryEWarrantOffset(const dict &req, int reqid);

    int reqQryInvestorProductGroupMargin(const dict &req, int reqid);

    int reqQryExchangeMarginRate(const dict &req, int reqid);

    int reqQryExchangeMarginRateAdjust(const dict &req, int reqid);

    int reqQryExchangeRate(const dict &req, int reqid);

    int reqQrySecAgentACIDMap(const dict &req, int reqid);

    int reqQryProductExchRate(const dict &req, int reqid);

    int reqQryProductGroup(const dict &req, int reqid);

    int reqQryMMInstrumentCommissionRate(const dict &req, int reqid);

    int reqQryMMOptionInstrCommRate(const dict &req, int reqid);

    int reqQryInstrumentOrderCommRate(const dict &req, int reqid);

    int reqQryOptionInstrTradeCost(const dict &req, int reqid);

    int reqQryOptionInstrCommRate(const dict &req, int reqid);

    int reqQryExecOrder(const dict &req, int reqid);

    int reqQryForQuote(const dict &req, int reqid);

    int reqQryQuote(const dict &req, int reqid);

    int reqQryLock(const dict &req, int reqid);

    int reqQryLockPosition(const dict &req, int reqid);

    int reqQryETFOptionInstrCommRate(const dict &req, int reqid);

    int reqQryInvestorLevel(const dict &req, int reqid);

    int reqQryExecFreeze(const dict &req, int reqid);

    int reqQryCombInstrumentGuard(const dict &req, int reqid);

    int reqQryCombAction(const dict &req, int reqid);

    int reqQryTransferSerial(const dict &req, int reqid);

    int reqQryAccountregister(const dict &req, int reqid);

    int reqQryContractBank(const dict &req, int reqid);

    int reqQryParkedOrder(const dict &req, int reqid);

    int reqQryParkedOrderAction(const dict &req, int reqid);

    int reqQryTradingNotice(const dict &req, int reqid);

    int reqQryBrokerTradingParams(const dict &req, int reqid);

    int reqQryBrokerTradingAlgos(const dict &req, int reqid);

    int reqQueryCFMMCTradingAccountToken(const dict &req, int reqid);

    int reqFromBankToFutureByFuture(const dict &req, int reqid);

    int reqFromFutureToBankByFuture(const dict &req, int reqid);

    int reqQueryBankAccountMoneyByFuture(const dict &req, int reqid);

    int reqReserveOpenAccountTpdByFuture(const dict &req, int reqid);

    int reqSecuritiesDepositInterestByFuture(const dict &req, int reqid);

    int reqDayEndFileReadyByFuture(const dict &req, int reqid);

    int reqExecCombineOrderInsert(const dict &req, int reqid);

    int reqExecCombineOrderAction(const dict &req, int reqid);

    int reqQryExecCombineOrder(const dict &req, int reqid);
};