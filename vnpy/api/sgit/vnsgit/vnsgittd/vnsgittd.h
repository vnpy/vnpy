//ϵͳ
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vnsgit.h"
#include "pybind11/pybind11.h"
#include "sgit/SgitFtdcTraderApi.h"


using namespace pybind11;
using namespace fstech;

//����
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
#define ONRSPBATCHORDERACTION 21
#define ONRSPCOMBACTIONINSERT 22
#define ONRSPQRYORDER 23
#define ONRSPQRYTRADE 24
#define ONRSPQRYINVESTORPOSITION 25
#define ONRSPQRYTRADINGACCOUNT 26
#define ONRSPQRYINVESTOR 27
#define ONRSPQRYTRADINGCODE 28
#define ONRSPQRYINSTRUMENTMARGINRATE 29
#define ONRSPQRYINSTRUMENTCOMMISSIONRATE 30
#define ONRSPQRYEXCHANGE 31
#define ONRSPQRYPRODUCT 32
#define ONRSPQRYINSTRUMENT 33
#define ONRSPQRYDEPTHMARKETDATA 34
#define ONRSPQRYSETTLEMENTINFO 35
#define ONRSPQRYTRANSFERBANK 36
#define ONRSPQRYINVESTORPOSITIONDETAIL 37
#define ONRSPQRYNOTICE 38
#define ONRSPQRYSETTLEMENTINFOCONFIRM 39
#define ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL 40
#define ONRSPQRYCFMMCTRADINGACCOUNTKEY 41
#define ONRSPQRYEWARRANTOFFSET 42
#define ONRSPQRYINVESTORPRODUCTGROUPMARGIN 43
#define ONRSPQRYEXCHANGEMARGINRATE 44
#define ONRSPQRYEXCHANGEMARGINRATEADJUST 45
#define ONRSPQRYEXCHANGERATE 46
#define ONRSPQRYSECAGENTACIDMAP 47
#define ONRSPQRYPRODUCTEXCHRATE 48
#define ONRSPQRYPRODUCTGROUP 49
#define ONRSPQRYOPTIONINSTRTRADECOST 50
#define ONRSPQRYOPTIONINSTRCOMMRATE 51
#define ONRSPQRYEXECORDER 52
#define ONRSPQRYFORQUOTE 53
#define ONRSPQRYQUOTE 54
#define ONRSPQRYCOMBINSTRUMENTGUARD 55
#define ONRSPQRYCOMBACTION 56
#define ONRSPQRYTRANSFERSERIAL 57
#define ONRSPQRYACCOUNTREGISTER 58
#define ONRSPERROR 59
#define ONRTNORDER 60
#define ONRTNTRADE 61
#define ONERRRTNORDERINSERT 62
#define ONERRRTNORDERACTION 63
#define ONRTNINSTRUMENTSTATUS 64
#define ONRTNTRADINGNOTICE 65
#define ONRTNERRORCONDITIONALORDER 66
#define ONRTNEXECORDER 67
#define ONERRRTNEXECORDERINSERT 68
#define ONERRRTNEXECORDERACTION 69
#define ONERRRTNFORQUOTEINSERT 70
#define ONRTNQUOTE 71
#define ONERRRTNQUOTEINSERT 72
#define ONERRRTNQUOTEACTION 73
#define ONRTNFORQUOTERSP 74
#define ONRTNCFMMCTRADINGACCOUNTTOKEN 75
#define ONERRRTNBATCHORDERACTION 76
#define ONRTNCOMBACTION 77
#define ONERRRTNCOMBACTIONINSERT 78
#define ONRSPQRYCONTRACTBANK 79
#define ONRSPQRYPARKEDORDER 80
#define ONRSPQRYPARKEDORDERACTION 81
#define ONRSPQRYTRADINGNOTICE 82
#define ONRSPQRYBROKERTRADINGPARAMS 83
#define ONRSPQRYBROKERTRADINGALGOS 84
#define ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN 85
#define ONRTNFROMBANKTOFUTUREBYBANK 86
#define ONRTNFROMFUTURETOBANKBYBANK 87
#define ONRTNREPEALFROMBANKTOFUTUREBYBANK 88
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 89
#define ONRTNFROMBANKTOFUTUREBYFUTURE 90
#define ONRTNFROMFUTURETOBANKBYFUTURE 91
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL 92
#define ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL 93
#define ONRTNQUERYBANKBALANCEBYFUTURE 94
#define ONERRRTNBANKTOFUTUREBYFUTURE 95
#define ONERRRTNFUTURETOBANKBYFUTURE 96
#define ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL 97
#define ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL 98
#define ONERRRTNQUERYBANKBALANCEBYFUTURE 99
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTURE 100
#define ONRTNREPEALFROMFUTURETOBANKBYFUTURE 101
#define ONRSPFROMBANKTOFUTUREBYFUTURE 102
#define ONRSPFROMFUTURETOBANKBYFUTURE 103
#define ONRSPQUERYBANKACCOUNTMONEYBYFUTURE 104
#define ONRTNOPENACCOUNTBYBANK 105
#define ONRTNCANCELACCOUNTBYBANK 106
#define ONRTNCHANGEACCOUNTBYBANK 107
#define ONRSPQRYDEFERFEERATE 108
#define ONRTNDEFERFEERATE 109
#define ONRSPQRYDEFERMIDTRADE 110
#define ONRTNDEFERMIDTRADE 111
#define ONRTNPOSITIONNETTING 112


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class TdApi : public CThostFtdcTraderSpi
{
private:
    CThostFtdcTraderApi* api;            //API����
    thread task_thread;                    //�����߳�ָ�루��python���������ݣ�
    TaskQueue task_queue;                //�������
    bool active = false;                //����״̬

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
    //API�ص�����
    //-------------------------------------------------------------------------------------

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ���������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///�ͻ�����֤��Ӧ
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û��������������Ӧ
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ʽ��˻��������������Ӧ
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ԥ��¼��������Ӧ
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ԥ�񳷵�¼��������Ӧ
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��ѯ��󱨵�������Ӧ
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ɾ��Ԥ����Ӧ
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ɾ��Ԥ�񳷵���Ӧ
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ִ������¼��������Ӧ
	virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ִ���������������Ӧ
	virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ѯ��¼��������Ӧ
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���۲���������Ӧ
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///������������������Ӧ
	virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�������¼��������Ӧ
	virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ӧ
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ɽ���Ӧ
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ������Ӧ
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ���ױ�����Ӧ
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��֤������Ӧ
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ����������Ӧ
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��������Ӧ
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Ʒ��Ӧ
	virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ӧ
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���߽�������Ӧ
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯת��������Ӧ
	virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ͻ�֪ͨ��Ӧ
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ϣȷ����Ӧ
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ֵ��۵���Ϣ��Ӧ
	virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤����Ӧ
	virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��������֤������Ӧ
	virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������������֤������Ӧ
	virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ӧ
	virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������������Ա����Ȩ����Ӧ
	virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Ʒ���ۻ���
	virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Ʒ��
	virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Ȩ���׳ɱ���Ӧ
	virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Ȩ��Լ��������Ӧ
	virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯִ��������Ӧ
	virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯѯ����Ӧ
	virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ������Ӧ
	virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
	virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ���������Ӧ
	virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯת����ˮ��Ӧ
	virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ����ǩԼ��ϵ��Ӧ
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

	///������������ر�
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

	///����֪ͨ
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

	///��ʾ������У�����
	virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

	///ִ������֪ͨ
	virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

	///ִ������¼�����ر�
	virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);

	///ִ�������������ر�
	virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);

	///ѯ��¼�����ر�
	virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);

	///����֪ͨ
	virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);

	///����¼�����ر�
	virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);

	///���۲�������ر�
	virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);

	///ѯ��֪ͨ
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	///��֤���������û�����
	virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);

	///����������������ر�
	virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);

	///�������֪ͨ
	virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction);

	///�������¼�����ر�
	virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);

	///�����ѯǩԼ������Ӧ
	virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯԤ����Ӧ
	virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯԤ�񳷵���Ӧ
	virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ����֪ͨ��Ӧ
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ���͹�˾���ײ�����Ӧ
	virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ���͹�˾�����㷨��Ӧ
	virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��������û�����
	virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���з��������ʽ�ת�ڻ�֪ͨ
	virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer);

	///���з����ڻ��ʽ�ת����֪ͨ
	virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer);

	///���з����������ת�ڻ�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal);

	///���з�������ڻ�ת����֪ͨ
	virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal);

	///�ڻ����������ʽ�ת�ڻ�֪ͨ
	virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);

	///�ڻ������ڻ��ʽ�ת����֪ͨ
	virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

	///�ڻ������ѯ�������֪ͨ
	virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);

	///�ڻ����������ʽ�ת�ڻ�����ر�
	virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

	///�ڻ������ڻ��ʽ�ת���д���ر�
	virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

	///�ڻ������ѯ����������ر�
	virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);

	///�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal);

	///�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal);

	///�ڻ����������ʽ�ת�ڻ�Ӧ��
	virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ڻ������ڻ��ʽ�ת����Ӧ��
	virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ڻ������ѯ�������Ӧ��
	virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���з������ڿ���֪ͨ
	virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount);

	///���з�����������֪ͨ
	virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount);

	///���з����������˺�֪ͨ
	virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount);

	/// ���յ���Լ��λ��ѯӦ��ʱ�ص��ú���
	virtual void onRspMBLQuot(CThostMBLQuotData *pMBLQuotData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};


	/// ���ӷѷ���ͷ���ѯ�ر�
	virtual void OnRspQryDeferFeeRate(CThostDeferFeeRateField *pDeferFeeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	/// ���ӷѷ���ͷ��ʸ�֪
	virtual void OnRtnDeferFeeRate(CThostDeferFeeRateField *pDeferFeeRate);

	/// ���ӽ���/�����ֳɽ���ѯ֪ͨ
	virtual void OnRspQryDeferMidTrade(CThostDeferMidAppTradeField *pDeferMidAppMatch, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	/// ���ӽ���/�����ֳɽ�֪ͨ
	virtual void OnRtnDeferMidTrade(CThostDeferMidAppTradeField *pDeferMidAppMatch);

	///�ֲ�����֪ͨ
	virtual void OnRtnPositionNetting(CThostFtdcPositionNettingField *pPositionNetting);

    //-------------------------------------------------------------------------------------
    //task������
    //-------------------------------------------------------------------------------------
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

	void processRspQryOptionInstrTradeCost(Task *task);

	void processRspQryOptionInstrCommRate(Task *task);

	void processRspQryExecOrder(Task *task);

	void processRspQryForQuote(Task *task);

	void processRspQryQuote(Task *task);

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

	void processRspQryDeferFeeRate(Task *task);

	void processRtnDeferFeeRate(Task *task);

	void processRspQryDeferMidTrade(Task *task);

	void processRtnDeferMidTrade(Task *task);

	void processRtnPositionNetting(Task *task);



    //-------------------------------------------------------------------------------------
    //data���ص������������ֵ�
    //error���ص������Ĵ����ֵ�
    //id������id
    //last���Ƿ�Ϊ��󷵻�
    //i������
    //-------------------------------------------------------------------------------------
    
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

	virtual void onRspQryOptionInstrTradeCost(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryOptionInstrCommRate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryExecOrder(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryForQuote(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspQryQuote(const dict &data, const dict &error, int reqid, bool last) {};

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

	virtual void onRspQryDeferFeeRate(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnDeferFeeRate(const dict &data) {};

	virtual void onRspQryDeferMidTrade(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnDeferMidTrade(const dict &data) {};

	virtual void onRtnPositionNetting(const dict &data) {};



    //-------------------------------------------------------------------------------------
    //req:���������������ֵ�
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

	int reqQryOptionInstrTradeCost(const dict &req, int reqid);

	int reqQryOptionInstrCommRate(const dict &req, int reqid);

	int reqQryExecOrder(const dict &req, int reqid);

	int reqQryForQuote(const dict &req, int reqid);

	int reqQryQuote(const dict &req, int reqid);

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

	//int reqMBLQuot(const dict &req, int reqid);

	int reqQryDeferFeeRate(const dict &req, int reqid);

	int reqQryDeferMidAppTrade(const dict &req, int reqid);


};
