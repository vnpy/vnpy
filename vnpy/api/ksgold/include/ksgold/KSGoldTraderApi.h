#ifndef __KSGOLDTRADEAPI__H__
#define __KSGOLDTRADEAPI__H__

#ifdef KSGOLDTRADERAPI_EXPORTS
#define KSGOLDTRADERAPI_API __declspec(dllexport)
#else
#ifdef WIN32
#define KSGOLDTRADERAPI_API __declspec(dllimport)
#else 
#define KSGOLDTRADERAPI_API
#endif
#endif

#include "KSGoldUserApiStructEx.h"

namespace KSGoldTradeAPI
{

class CKSGoldTraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时，该方法被调用。
	///出现断线重连时，也会调用此方法
	///@param nResult 返回结果
	///        0x1001 建立连接
	///        0x1002 断线重连成功
	virtual void OnFrontConnected(int nResult) {};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason) {};
	
	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	//市场状态通知
	virtual void OnNtyMktStatus(CThostFtdcMarketStatusField *pfldMktStatus){};
	
	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus){};
	
	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	//请求查询交割品种响应
	virtual void OnRspReqQryVarietyCode(CThostFtdcRspVarietyCodeField *pVarietyCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcRspInputOrderField *pRspInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	///ETF认购请求响应
	virtual void OnRspETFSubscriptionOrderInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///ETF申购请求响应
	virtual void OnRspETFPurchaseOrderInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///ETF赎回请求响应
	virtual void OnRspETFRedeemInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///ETF账户绑定请求响应
	virtual void OnRspETFAccountBinding(CThostFtdcETFBindingStatusField *pETFAccountBinding, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///ETF账户解绑定请求响应
	virtual void OnRspETFAccountUnbinding(CThostFtdcETFBindingStatusField *pETFAccountUnbinding, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) {};
	
	///强退通知
	virtual void OnForceLogout(CThostFtdcUserLogoutField *pLogout) {};

	//ETF账户绑定解绑定状态通知
	virtual void OnRtnETFAccountBindingStatus(CThostFtdcETFBindingStatusField * pETFBindgingStatus) {};

	//ETF认申赎报单状态通知
	virtual void OnRtnETFOrder(CThostFtdcETFTradeDetailField *pEtfTradeDetail){};
	
	///撤单应答
	virtual void OnRspOrderAction(CThostFtdcRspInputOrderActionField *pRspInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {};
	
	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	///请求历史资金查询
	virtual void OnRspQryHisCapital(CThostFtdcRspHisCapitalField *pHisCapital, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
	///查询客户库存响应
	virtual void OnRspQryClientStorage(CThostFtdcStorageField *pStorage, CThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast){};
	
	///费率\保证金率查询响应
	virtual void OnRspQryCostMarginFeeRate(CThostFtdcRspCostMarginFeeField *pCostMarginFee, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast){};
	
	///条件单委托响应
	virtual void OnRspConditionOrderInsert(CThostFtdcRspConditionOrderField *pConditionOrder, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast){};
	
	///条件单撤单响应
	virtual void OnRspConditionOrderAction(CThostFtdcRspConditionActionOrderField *pConditionActionOrder, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast){};
	
	///条件单委托查询响应
	virtual void OnRspQryConditionOrder(CThostFtdcRspConditionOrderQryField *pConditionOrderQry, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast){};
	
	///条件单成交查询响应
	virtual void OnRspQryConditionOrderTrade(CThostFtdcRspConditionOrderMatchField *pConditionOrderMatch, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast){};

	///客户会话信息通用查询响应
	virtual void OnRspQryClientSessionInfo(CThostFtdcRspClientSessionField *pClientSessionField, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast){};

	///查询行情信息响应
	virtual void OnRspQryQuotation(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};	

	///查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///ETF认申赎交易查询响应
	virtual void OnRspQryETFradeDetail(CThostFtdcETFTradeDetailField *pQryETFTradeDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///ETF认申赎清单查询
	virtual void OnRspQryETFPcfDetail(CThostFtdcETFPcfDetailField *pQryETFpcfDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///修改密码响应
	virtual void OnRspModifyPassword(CThostFtdcModifyPasswordRsqField *pRsqModifyPassword,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};
	
	///中行出入金响应
	virtual void OnRspB0CMoneyIO(CThostFtdcBOCMoneyIORspField *pRspBOCMoneyIO,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};


};

class KSGOLDTRADERAPI_API CKSGoldTraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮流文件目录，默认为当前目录
	///@return 创建出的UserApi
	static CKSGoldTraderApi *CreateGoldTraderApi(const char *pszFlowPath = "");
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual bool Init() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        KS_TERT_RESTART: 从本交易日开始重传
	///        KS_TERT_RESUME : 从上次收到的续传,功能暂时不可用
	///        KS_TERT_QUICK  : 只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则默认是KS_TERT_RESTART。
	virtual void SubscribePrivateTopic(KS_TE_RESUME_TYPE nResumeType) = 0;

	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        KS_TERT_RESTART: 从本交易日开始重传
	///        KS_TERT_RESUME : 从上次收到的续传,功能暂时不可用
	///        KS_TERT_QUICK  : 只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则默认是KS_TERT_RESTART。
	virtual void SubscribePublicTopic(KS_TE_RESUME_TYPE nResumeType) = 0;

	///注册API回调接口
	///@param pGeneralSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CKSGoldTraderSpi *pGeneralSpi) = 0;	
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///用户登录请求
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	
	///用户登出请求
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;
	
	///查询合约
	virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///查询交割品种
	virtual int ReqQryVarietyCode(CThostFtdcQryVarietyCodeField *pQryVarietyCode, int nRequestID) = 0;
	
	///下单请求
	virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) = 0;
	
	///报单操作请求(撤单)
	virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) = 0;
	
	///查询持仓请求
	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pInvestorPosition, int nRequestID) = 0;
	
	///查询资金请求
	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;
	
	///成交查询请求
	virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) = 0;
	
	///委托查询请求
	virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) = 0;
	
	///查询客户库存请求
	virtual int ReqQryStorage(CThostFtdcQryStorageField *pfldStorage, int nRequestID) =0;
	
	//费率\保证金率查询
	virtual int ReqQryCostMarginFeeRate(CThostFtdcQryCostMarginFeeField *pQryCostMarginFee, int nRequestID) = 0;
	
	///条件单委托
	virtual int ReqConditionOrderInsert(CThostFtdcConditionOrderField *pConditionOrder, int nRequestID) = 0;
	
	///条件单撤单
	virtual int ReqConditionOrderAction(CThostFtdcConditionActionOrderField *pConditionActionOrder, int nRequestID) = 0;
	
	///条件单委托查询
	virtual int ReqQryConditionOrder(CThostFtdcConditionOrderQryField *pConditionOrderQry, int nRequestID) = 0;
	
	///条件单成交查询
	virtual int ReqQryConditionOrderTrade(CThostFtdcConditionOrderMatchField *pConditionOrderMatch, int nRequestID) = 0;

	///客户会话信息通用查询
	virtual int ReqQryClientSessionInfo(CThostFtdcQryClientSessionField *pQryClientSession, int nRequestID) = 0;
	
	///查询行情信息
	virtual int ReqQryQuotation(CThostFtdcQryQuotationField *pQryQuotation, int nRequestID) = 0;

	///请求查询投资者持仓明细
	virtual int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) = 0;

	///修改密码请求
	virtual int ReqModifyPassword(CThostFtdcModifyPasswordField *pModifyPasswordFieldl, int nRequestID) = 0;

    ///请求查询客户历史资金
	virtual int ReqQryHisCapital(CThostFtdcQryHisCapitalField *pQryHisCapital,int nRequestID) = 0;

	///ETF认购请求
	virtual int ReqETFSubScription(CThostFtdcSubScriptionField *pEtfSubScription,int nRequestID) = 0;

    ///ETF申购请求
	virtual int ReqETFApplyForPurchase(CThostFtdcApplyForPurchaseField *pEtfApplyForPurchase,int nRequestID) = 0;

	///ETF赎回请求
	virtual int ReqETFRedeem(CThostFtdcRedeemField *pETFRedeem,int nRequestID)=0;

	///ETF账户绑定
	virtual int ReqETFAccountBinding(CThostFtdcETFBingingField *pETFAccountBinding,int nRequestID)=0;

	///ETF账户解绑定
	virtual int ReqETFAccountUnbinding(CThostFtdcETFUnBingingField *pETFAccountUnBinding,int nRequestID)=0;

	///ETF认申赎交易查询
	virtual int ReqETFTradeDetail(CThostFtdcQryETFTradeDetailField *pQryETFTradeDetail,int nRequestID) = 0;
 
	///ETF认申赎清单查询
	virtual int ReqETFPcfDetail(CThostFtdcQryETFPcfDetailField *pQryETFPcfDetail,int nRequestID) = 0;

	///中行出入金请求
	virtual int ReqBOCMoneyIO(CThostFtdcBOCMoneyIOField *pBOCMoneyIO, int nRequestID) = 0;


	protected:
		~CKSGoldTraderApi();
};

}  //end of namespace KSGoldTradeAPI

#endif   //__KSGOLDTRADEAPI__H__




