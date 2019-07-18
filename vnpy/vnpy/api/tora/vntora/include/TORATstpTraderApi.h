/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰信息科技有限公司
///@file TORATstpTraderApi.h
///@brief 定义了客户端接口
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(TORA_TSTPTRADERAPI_H)
#define TORA_TSTPTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpUserApiStruct.h"

#ifdef TRADER_API_EXPORT
#ifdef WINDOWS
#define TRADER_API_DLL_EXPORT __declspec(dllexport)
#else
#define TRADER_API_DLL_EXPORT __attribute__ ((visibility("default")))
#endif
#else
#define TRADER_API_DLL_EXPORT 
#endif

class CTORATstpTraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        -3 连接已断开
	///        -4 网络读失败
	///        -5 网络写失败
	///        -6 订阅流错误
	///        -7 流序号错误
	///        -8 错误的心跳报文
	///        -9 错误的报文
	virtual void OnFrontDisconnected(int nReason){};
				
	///错误应答
	virtual void OnRspError(CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
		
	//登录应答	
	virtual void OnRspUserLogin(CTORATstpRspUserLoginField *pRspUserLoginField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//登出应答	
	virtual void OnRspUserLogout(CTORATstpUserLogoutField *pUserLogoutField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//修改密码应答	
	virtual void OnRspUserPasswordUpdate(CTORATstpUserPasswordUpdateField *pUserPasswordUpdateField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//请求录入设备序列应答	
	virtual void OnRspInputDeviceSerial(CTORATstpRspInputDeviceSerialField *pRspInputDeviceSerialField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//报单录入应答	
	virtual void OnRspOrderInsert(CTORATstpInputOrderField *pInputOrderField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//报单回报
	virtual void OnRtnOrder(CTORATstpOrderField *pOrder) {};
			
	//报单错误回报
	virtual void OnErrRtnOrderInsert(CTORATstpInputOrderField *pInputOrder, CTORATstpRspInfoField *pRspInfo) {};
				
	//撤单应答	
	virtual void OnRspOrderAction(CTORATstpInputOrderActionField *pInputOrderActionField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//撤单错误回报
	virtual void OnErrRtnOrderAction(CTORATstpOrderActionField *pOrderAction, CTORATstpRspInfoField *pRspInfo) {};
				
	//成交回报
	virtual void OnRtnTrade(CTORATstpTradeField *pTrade) {};
			
	//推送市场状态
	virtual void OnRtnMarketStatus(CTORATstpMarketStatusField *pMarketStatus) {};
		
	//条件单录入请求响应	
	virtual void OnRspCondOrderInsert(CTORATstpInputCondOrderField *pInputCondOrderField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//条件单通知
	virtual void OnRtnCondOrder(CTORATstpConditionOrderField *pConditionOrder) {};
			
	//条件单录入错误回报
	virtual void OnErrRtnCondOrderInsert(CTORATstpInputCondOrderField *pInputCondOrder, CTORATstpRspInfoField *pRspInfo) {};
				
	//条件单操作请求响应	
	virtual void OnRspCondOrderAction(CTORATstpInputCondOrderActionField *pInputCondOrderActionField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//条件单撤单操作错误回报
	virtual void OnErrRtnCondOrderAction(CTORATstpInputCondOrderActionField *pInputCondOrderAction, CTORATstpRspInfoField *pRspInfo) {};
				
	//查询集中交易系统资金响应	
	virtual void OnRspInquiryJZFund(CTORATstpRspInquiryJZFundField *pRspInquiryJZFundField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//资金转移请求应答	
	virtual void OnRspTransferFund(CTORATstpInputTransferFundField *pInputTransferFundField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//资金转移回报
	virtual void OnRtnTransferFund(CTORATstpTransferFundField *pTransferFund) {};
		
	//资金转移错误回报
	virtual void OnErrRtnTransferFund(CTORATstpInputTransferFundField *pInputTransferFund, CTORATstpRspInfoField *pRspInfo) {};
			
	//仓位转移回报
	virtual void OnRtnTransferPosition(CTORATstpTransferPositionField *pTransferPosition) {};
		
	//仓位转移错误回报
	virtual void OnErrRtnTransferPosition(CTORATstpInputTransferPositionField *pInputTransferPosition, CTORATstpRspInfoField *pRspInfo) {};
			
	//担保品划转响应	
	virtual void OnRspTransferCollateral(CTORATstpInputTransferCollateralField *pInputTransferCollateralField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//查询银行账户余额响应	
	virtual void OnRspInquiryBankAccountFund(CTORATstpRspInquiryBankAccountFundField *pRspInquiryBankAccountFundField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//交易成交集中度查询响应	
	virtual void OnRspInquiryTradeConcentration(CTORATstpInquiryTradeConcentrationField *pInquiryTradeConcentrationField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//交易通知
	virtual void OnRtnTradingNotice(CTORATstpTradingNoticeField *pTradingNotice) {};
		
	//查询最大委托量应答	
	virtual void OnRspInquiryMaxOrderVolume(CTORATstpRspInquiryMaxOrderVolumeField *pRspInquiryMaxOrderVolumeField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//外围系统仓位转移回报
	virtual void OnRtnPeripheryTransferPosition(CTORATstpPeripheryPositionTransferDetailField *pPeripheryPositionTransferDetail) {};
			
	//查询历史委托响应	
	virtual void OnRspInquiryHistoryOrder(CTORATstpHistoryOrderField *pHistoryOrderField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//查询历史成交响应	
	virtual void OnRspInquiryHistoryTrade(CTORATstpHistoryTradeField *pHistoryTradeField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
		
	//查询交易所
	virtual void OnRspQryExchange(CTORATstpExchangeField *pExchange, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询实时行情
	virtual void OnRspQryMarketData(CTORATstpMarketDataField *pMarketData, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询证券信息
	virtual void OnRspQrySecurity(CTORATstpSecurityField *pSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询ETF清单信息
	virtual void OnRspQryETFFile(CTORATstpETFFileField *pETFFile, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询ETF成份证券信息
	virtual void OnRspQryETFBasket(CTORATstpETFBasketField *pETFBasket, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询新股信息
	virtual void OnRspQryIPOInfo(CTORATstpIPOInfoField *pIPOInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询代理关系
	virtual void OnRspQryBUProxy(CTORATstpBUProxyField *pBUProxy, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询User
	virtual void OnRspQryUser(CTORATstpUserField *pUser, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询投资者
	virtual void OnRspQryInvestor(CTORATstpInvestorField *pInvestor, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询股东账户
	virtual void OnRspQryShareholderAccount(CTORATstpShareholderAccountField *pShareholderAccount, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//报单查询
	virtual void OnRspQryOrder(CTORATstpOrderField *pOrder, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询撤单
	virtual void OnRspQryOrderAction(CTORATstpOrderActionField *pOrderAction, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//成交查询
	virtual void OnRspQryTrade(CTORATstpTradeField *pTrade, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//资金账户查询
	virtual void OnRspQryTradingAccount(CTORATstpTradingAccountField *pTradingAccount, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//投资者持仓查询
	virtual void OnRspQryPosition(CTORATstpPositionField *pPosition, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询基础交易费用
	virtual void OnRspQryTradingFee(CTORATstpTradingFeeField *pTradingFee, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询佣金费率
	virtual void OnRspQryInvestorTradingFee(CTORATstpInvestorTradingFeeField *pInvestorTradingFee, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询新股申购额度
	virtual void OnRspQryIPOQuota(CTORATstpIPOQuotaField *pIPOQuota, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询市场
	virtual void OnRspQryMarket(CTORATstpMarketField *pMarket, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//报单明细资金查询
	virtual void OnRspQryOrderFundDetail(CTORATstpOrderFundDetailField *pOrderFundDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询资金转移流水
	virtual void OnRspQryFundTransferDetail(CTORATstpFundTransferDetailField *pFundTransferDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询持仓转移流水
	virtual void OnRspQryPositionTransferDetail(CTORATstpPositionTransferDetailField *pPositionTransferDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//请求投资者质押持仓查询响应
	virtual void OnRspQryPledgePosition(CTORATstpPledgePositionField *pPledgePosition, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//请求证券质押信息查询响应
	virtual void OnRspQryPledgeInfo(CTORATstpPledgeInfoField *pPledgeInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//请求可转债信息查询响应
	virtual void OnRspQryConversionBondInfo(CTORATstpConversionBondInfoField *pConversionBondInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//请求债券回售信息查询响应
	virtual void OnRspQryBondPutbackInfo(CTORATstpBondPutbackInfoField *pBondPutbackInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//请求标准券额度查询响应
	virtual void OnRspQryStandardBondPosition(CTORATstpStandardBondPositionField *pStandardBondPosition, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询实时特别行情响应
	virtual void OnRspQrySpecialMarketData(CTORATstpSpecialMarketDataField *pSpecialMarketData, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询未到期债券质押回购委托响应
	virtual void OnRspQryPrematurityRepoOrder(CTORATstpPrematurityRepoOrderField *pPrematurityRepoOrder, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询股东参数响应
	virtual void OnRspQryShareholderParam(CTORATstpShareholderParamField *pShareholderParam, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询外围系统仓位调拨流水
	virtual void OnRspQryPeripheryPositionTransferDetail(CTORATstpPeripheryPositionTransferDetailField *pPeripheryPositionTransferDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询投资者条件单限制参数响应
	virtual void OnRspQryInvestorCondOrderLimitParam(CTORATstpInvestorCondOrderLimitParamField *pInvestorCondOrderLimitParam, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询条件单响应
	virtual void OnRspQryCondOrder(CTORATstpCondOrderField *pCondOrder, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询条件单撤单响应
	virtual void OnRspQryCondOrderAction(CTORATstpCondOrderActionField *pCondOrderAction, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询交易通知响应
	virtual void OnRspQryTradingNotice(CTORATstpTradingNoticeField *pTradingNotice, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询新股申购配号结果响应
	virtual void OnRspQryIPONumberResult(CTORATstpIPONumberResultField *pIPONumberResult, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查询新股申购中签结果响应
	virtual void OnRspQryIPOMatchNumberResult(CTORATstpIPOMatchNumberResultField *pIPOMatchNumberResult, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
};

class TRADER_API_DLL_EXPORT CTORATstpTraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@param bEncrpyt 网络数据是否加密传输，默认不加密
	///@return 创建出的TraderApi
	
	static CTORATstpTraderApi *CreateTstpTraderApi(const char *pszFlowPath = "", bool bEncrypt = false);
	
	///获取API版本号
	///@return 版本号
	static const char* GetApiVersion();
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;

	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///注册衍生服务服务器网络地址
	///@param pszNsAddress：衍生服务服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:16001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”16001”代表服务器端口号。
	virtual void RegisterDeriveServer(char *pszDeriveAddress) = 0;

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CTORATstpTraderSpi *pSpi) = 0;
	
	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        TORA_TERT_RESTART:从本交易日开始重传
	///        TORA_TERT_RESUME:从上次收到的续传
	///        TORA_TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(TORA_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        TORA_TERT_RESTART:从本交易日开始重传
	///        TORA_TERT_RESUME:从上次收到的续传
	///        TORA_TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(TORA_TE_RESUME_TYPE nResumeType) = 0;
	
	
	//登录请求		
	virtual int ReqUserLogin(CTORATstpReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	
	//登出请求		
	virtual int ReqUserLogout(CTORATstpUserLogoutField *pUserLogoutField, int nRequestID) = 0;
	
	//修改密码请求		
	virtual int ReqUserPasswordUpdate(CTORATstpUserPasswordUpdateField *pUserPasswordUpdateField, int nRequestID) = 0;
	
	//请求录入设备序列		
	virtual int ReqInputDeviceSerial(CTORATstpReqInputDeviceSerialField *pReqInputDeviceSerialField, int nRequestID) = 0;
	
	//报单录入请求		
	virtual int ReqOrderInsert(CTORATstpInputOrderField *pInputOrderField, int nRequestID) = 0;
	
	//撤单请求		
	virtual int ReqOrderAction(CTORATstpInputOrderActionField *pInputOrderActionField, int nRequestID) = 0;
	
	//条件单录入请求		
	virtual int ReqCondOrderInsert(CTORATstpInputCondOrderField *pInputCondOrderField, int nRequestID) = 0;
	
	//条件单操作请求		
	virtual int ReqCondOrderAction(CTORATstpInputCondOrderActionField *pInputCondOrderActionField, int nRequestID) = 0;
	
	//查询集中交易系统资金请求		
	virtual int ReqInquiryJZFund(CTORATstpReqInquiryJZFundField *pReqInquiryJZFundField, int nRequestID) = 0;
	
	//资金转移请求		
	virtual int ReqTransferFund(CTORATstpInputTransferFundField *pInputTransferFundField, int nRequestID) = 0;
	
	//担保品划转请求		
	virtual int ReqTransferCollateral(CTORATstpInputTransferCollateralField *pInputTransferCollateralField, int nRequestID) = 0;
	
	//查询银行账户余额请求		
	virtual int ReqInquiryBankAccountFund(CTORATstpReqInquiryBankAccountFundField *pReqInquiryBankAccountFundField, int nRequestID) = 0;
	
	//查询交易成交集中度		
	virtual int ReqInquiryTradeConcentration(CTORATstpInquiryTradeConcentrationField *pInquiryTradeConcentrationField, int nRequestID) = 0;
	
	//查询最大委托量请求		
	virtual int ReqInquiryMaxOrderVolume(CTORATstpReqInquiryMaxOrderVolumeField *pReqInquiryMaxOrderVolumeField, int nRequestID) = 0;
	
	//查询历史委托请求		
	virtual int ReqInquiryHistoryOrder(CTORATstpQryHistoryOrderField *pQryHistoryOrderField, int nRequestID) = 0;
	
	//查询历史成交请求		
	virtual int ReqInquiryHistoryTrade(CTORATstpQryHistoryTradeField *pQryHistoryTradeField, int nRequestID) = 0;
	
	//查询交易所		
	virtual int ReqQryExchange(CTORATstpQryExchangeField *pQryExchangeField, int nRequestID) = 0;
	
	//查询实时行情		
	virtual int ReqQryMarketData(CTORATstpQryMarketDataField *pQryMarketDataField, int nRequestID) = 0;
	
	//查询证券信息		
	virtual int ReqQrySecurity(CTORATstpQrySecurityField *pQrySecurityField, int nRequestID) = 0;
	
	//查询ETF清单信息		
	virtual int ReqQryETFFile(CTORATstpQryETFFileField *pQryETFFileField, int nRequestID) = 0;
	
	//查询ETF成份证券信息		
	virtual int ReqQryETFBasket(CTORATstpQryETFBasketField *pQryETFBasketField, int nRequestID) = 0;
	
	//查询新股信息		
	virtual int ReqQryIPOInfo(CTORATstpQryIPOInfoField *pQryIPOInfoField, int nRequestID) = 0;
	
	//查询代理关系		
	virtual int ReqQryBUProxy(CTORATstpQryBUProxyField *pQryBUProxyField, int nRequestID) = 0;
	
	//查询User		
	virtual int ReqQryUser(CTORATstpQryUserField *pQryUserField, int nRequestID) = 0;
	
	//查询投资者		
	virtual int ReqQryInvestor(CTORATstpQryInvestorField *pQryInvestorField, int nRequestID) = 0;
	
	//查询股东账户		
	virtual int ReqQryShareholderAccount(CTORATstpQryShareholderAccountField *pQryShareholderAccountField, int nRequestID) = 0;
	
	//报单查询		
	virtual int ReqQryOrder(CTORATstpQryOrderField *pQryOrderField, int nRequestID) = 0;
	
	//查询撤单		
	virtual int ReqQryOrderAction(CTORATstpQryOrderActionField *pQryOrderActionField, int nRequestID) = 0;
	
	//成交查询		
	virtual int ReqQryTrade(CTORATstpQryTradeField *pQryTradeField, int nRequestID) = 0;
	
	//资金账户查询		
	virtual int ReqQryTradingAccount(CTORATstpQryTradingAccountField *pQryTradingAccountField, int nRequestID) = 0;
	
	//投资者持仓查询		
	virtual int ReqQryPosition(CTORATstpQryPositionField *pQryPositionField, int nRequestID) = 0;
	
	//查询基础交易费用		
	virtual int ReqQryTradingFee(CTORATstpQryTradingFeeField *pQryTradingFeeField, int nRequestID) = 0;
	
	//查询佣金费率		
	virtual int ReqQryInvestorTradingFee(CTORATstpQryInvestorTradingFeeField *pQryInvestorTradingFeeField, int nRequestID) = 0;
	
	//查询新股申购额度		
	virtual int ReqQryIPOQuota(CTORATstpQryIPOQuotaField *pQryIPOQuotaField, int nRequestID) = 0;
	
	//查询市场		
	virtual int ReqQryMarket(CTORATstpQryMarketField *pQryMarketField, int nRequestID) = 0;
	
	//报单明细资金查询		
	virtual int ReqQryOrderFundDetail(CTORATstpQryOrderFundDetailField *pQryOrderFundDetailField, int nRequestID) = 0;
	
	//查询资金转移流水		
	virtual int ReqQryFundTransferDetail(CTORATstpQryFundTransferDetailField *pQryFundTransferDetailField, int nRequestID) = 0;
	
	//查询持仓转移流水		
	virtual int ReqQryPositionTransferDetail(CTORATstpQryPositionTransferDetailField *pQryPositionTransferDetailField, int nRequestID) = 0;
	
	//请求投资者质押持仓查询		
	virtual int ReqQryPledgePosition(CTORATstpQryPledgePositionField *pQryPledgePositionField, int nRequestID) = 0;
	
	//请求证券质押信息查询		
	virtual int ReqQryPledgeInfo(CTORATstpQryPledgeInfoField *pQryPledgeInfoField, int nRequestID) = 0;
	
	//请求可转债信息查询		
	virtual int ReqQryConversionBondInfo(CTORATstpQryConversionBondInfoField *pQryConversionBondInfoField, int nRequestID) = 0;
	
	//请求债券回售信息查询		
	virtual int ReqQryBondPutbackInfo(CTORATstpQryBondPutbackInfoField *pQryBondPutbackInfoField, int nRequestID) = 0;
	
	//请求标准券额度查询		
	virtual int ReqQryStandardBondPosition(CTORATstpQryStandardBondPositionField *pQryStandardBondPositionField, int nRequestID) = 0;
	
	//查询实时特别行情		
	virtual int ReqQrySpecialMarketData(CTORATstpQrySpecialMarketDataField *pQrySpecialMarketDataField, int nRequestID) = 0;
	
	//查询未到期债券质押回购委托		
	virtual int ReqQryPrematurityRepoOrder(CTORATstpQryPrematurityRepoOrderField *pQryPrematurityRepoOrderField, int nRequestID) = 0;
	
	//查询股东参数		
	virtual int ReqQryShareholderParam(CTORATstpQryShareholderParamField *pQryShareholderParamField, int nRequestID) = 0;
	
	//查询外围系统仓位调拨流水		
	virtual int ReqQryPeripheryPositionTransferDetail(CTORATstpQryPeripheryPositionTransferDetailField *pQryPeripheryPositionTransferDetailField, int nRequestID) = 0;
	
	//查询投资者条件单限制参数请求		
	virtual int ReqQryInvestorCondOrderLimitParam(CTORATstpQryInvestorCondOrderLimitParamField *pQryInvestorCondOrderLimitParamField, int nRequestID) = 0;
	
	//查询条件单请求		
	virtual int ReqQryCondOrder(CTORATstpQryCondOrderField *pQryCondOrderField, int nRequestID) = 0;
	
	//查询条件单撤单请求		
	virtual int ReqQryCondOrderAction(CTORATstpQryCondOrderActionField *pQryCondOrderActionField, int nRequestID) = 0;
	
	//查询交易通知请求		
	virtual int ReqQryTradingNotice(CTORATstpQryTradingNoticeField *pQryTradingNoticeField, int nRequestID) = 0;
	
	//查询新股申购配号结果		
	virtual int ReqQryIPONumberResult(CTORATstpQryIPONumberResultField *pQryIPONumberResultField, int nRequestID) = 0;
	
	//查询新股申购中签结果		
	virtual int ReqQryIPOMatchNumberResult(CTORATstpQryIPOMatchNumberResultField *pQryIPOMatchNumberResultField, int nRequestID) = 0;
	
	
protected:
	~CTORATstpTraderApi(){};
};

#endif
