/////////////////////////////////////////////////////////////////////////
///@company shanghai liber information Technology Co.,Ltd
///@file SecurityFtdcQueryApi.h
///@brief 定义客户端接口
/////////////////////////////////////////////////////////////////////////

#if !defined(SECURITY_FTDCQUERYAPI_H)
#define SECURITY_FTDCQUERYAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SecurityFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_QUERY_API_EXPORT
#define QUERY_API_EXPORT __declspec(dllexport)
#else
#define QUERY_API_EXPORT __declspec(dllimport)
#endif
#else
#define QUERY_API_EXPORT 
#endif

class CSecurityFtdcQuerySpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};	

	///错误应答
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登录请求响应
	virtual void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///获取认证随机码请求响应
	virtual void OnRspFetchAuthRandCode(CSecurityFtdcAuthRandCodeField *pAuthRandCode, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所响应
	virtual void OnRspQryExchange(CSecurityFtdcExchangeField *pExchange, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	virtual void OnRspQryInstrument(CSecurityFtdcInstrumentField *pInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CSecurityFtdcInvestorField *pInvestor, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易编码响应
	virtual void OnRspQryTradingCode(CSecurityFtdcTradingCodeField *pTradingCode, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CSecurityFtdcTradingAccountField *pTradingAccount, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询债券利息响应
	virtual void OnRspQryBondInterest(CSecurityFtdcBondInterestField *pBondInterest, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询市值配售信息响应
	virtual void OnRspQryMarketRationInfo(CSecurityFtdcMarketRationInfoField *pMarketRationInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(CSecurityFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询ETF合约响应
	virtual void OnRspQryETFInstrument(CSecurityFtdcETFInstrumentField *pETFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询ETF股票篮响应
	virtual void OnRspQryETFBasket(CSecurityFtdcETFBasketField *pETFBasket, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询OF合约响应
	virtual void OnRspQryOFInstrument(CSecurityFtdcOFInstrumentField *pOFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询SF合约响应
	virtual void OnRspQrySFInstrument(CSecurityFtdcSFInstrumentField *pSFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约单手保证金响应
	virtual void OnRspQryInstrumentUnitMargin(CSecurityFtdcInstrumentUnitMarginField *pInstrumentUnitMargin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询预交割信息响应
	virtual void OnRspQryPreDelivInfo(CSecurityFtdcPreDelivInfoField *pPreDelivInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询可融券分配信息响应
	virtual void OnRspQryCreditStockAssignInfo(CSecurityFtdcCreditStockAssignInfoField *pCreditStockAssignInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询可融资分配信息响应
	virtual void OnRspQryCreditCashAssignInfo(CSecurityFtdcCreditCashAssignInfoField *pCreditCashAssignInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询证券折算率响应
	virtual void OnRspQryConversionRate(CSecurityFtdcConversionRateField *pConversionRate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询历史信用负债信息响应
	virtual void OnRspQryHisCreditDebtInfo(CSecurityFtdcHisCreditDebtInfoField *pHisCreditDebtInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情静态信息响应
	virtual void OnRspQryMarketDataStaticInfo(CSecurityFtdcMarketDataStaticInfoField *pMarketDataStaticInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询到期回购信息响应
	virtual void OnRspQryExpireRepurchInfo(CSecurityFtdcExpireRepurchInfoField *pExpireRepurchInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询债券质押为标准券比例响应
	virtual void OnRspQryBondPledgeRate(CSecurityFtdcBondPledgeRateField *pBondPledgeRate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询债券质押代码对照关系响应
	virtual void OnRspQryPledgeBond(CSecurityFtdcPledgeBondField *pPledgeBond, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(CSecurityFtdcOrderField *pOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(CSecurityFtdcTradeField *pTrade, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CSecurityFtdcInvestorPositionField *pInvestorPosition, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金转账查询应答
	virtual void OnRspQryFundTransferSerial(CSecurityFtdcFundTransferField *pFundTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金内转流水查询应答
	virtual void OnRspQryFundInterTransferSerial(CSecurityFtdcFundInterTransferSerialField *pFundInterTransferSerial, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

#ifndef WINDOWS
	#if __GNUC__ >= 4
		#pragma GCC visibility push(default)
	#endif
#endif

class QUERY_API_EXPORT CSecurityFtdcQueryApi
{
public:
	///创建QueryApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CSecurityFtdcQueryApi *CreateFtdcQueryApi(const char *pszFlowPath = "");
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CSecurityFtdcQuerySpi *pSpi) = 0;
	
	///用户登录请求
	virtual int ReqUserLogin(CSecurityFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	

	///登出请求
	virtual int ReqUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	///获取认证随机码请求
	virtual int ReqFetchAuthRandCode(CSecurityFtdcAuthRandCodeField *pAuthRandCode, int nRequestID) = 0;

	///请求查询交易所
	virtual int ReqQryExchange(CSecurityFtdcQryExchangeField *pQryExchange, int nRequestID) = 0;

	///请求查询合约
	virtual int ReqQryInstrument(CSecurityFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///请求查询投资者
	virtual int ReqQryInvestor(CSecurityFtdcQryInvestorField *pQryInvestor, int nRequestID) = 0;

	///请求查询交易编码
	virtual int ReqQryTradingCode(CSecurityFtdcQryTradingCodeField *pQryTradingCode, int nRequestID) = 0;

	///请求查询资金账户
	virtual int ReqQryTradingAccount(CSecurityFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	///请求查询债券利息
	virtual int ReqQryBondInterest(CSecurityFtdcQryBondInterestField *pQryBondInterest, int nRequestID) = 0;

	///请求查询市值配售信息
	virtual int ReqQryMarketRationInfo(CSecurityFtdcQryMarketRationInfoField *pQryMarketRationInfo, int nRequestID) = 0;

	///请求查询合约手续费率
	virtual int ReqQryInstrumentCommissionRate(CSecurityFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID) = 0;

	///请求查询ETF合约
	virtual int ReqQryETFInstrument(CSecurityFtdcQryETFInstrumentField *pQryETFInstrument, int nRequestID) = 0;

	///请求查询ETF股票篮
	virtual int ReqQryETFBasket(CSecurityFtdcQryETFBasketField *pQryETFBasket, int nRequestID) = 0;

	///请求查询OF合约
	virtual int ReqQryOFInstrument(CSecurityFtdcQryOFInstrumentField *pQryOFInstrument, int nRequestID) = 0;

	///请求查询SF合约
	virtual int ReqQrySFInstrument(CSecurityFtdcQrySFInstrumentField *pQrySFInstrument, int nRequestID) = 0;

	///请求查询合约单手保证金
	virtual int ReqQryInstrumentUnitMargin(CSecurityFtdcQryInstrumentUnitMarginField *pQryInstrumentUnitMargin, int nRequestID) = 0;

	///请求查询预交割信息
	virtual int ReqQryPreDelivInfo(CSecurityFtdcQryPreDelivInfoField *pQryPreDelivInfo, int nRequestID) = 0;

	///请求查询可融券分配信息
	virtual int ReqQryCreditStockAssignInfo(CSecurityFtdcQryCreditStockAssignInfoField *pQryCreditStockAssignInfo, int nRequestID) = 0;

	///请求查询可融资分配信息
	virtual int ReqQryCreditCashAssignInfo(CSecurityFtdcQryCreditCashAssignInfoField *pQryCreditCashAssignInfo, int nRequestID) = 0;

	///请求查询证券折算率
	virtual int ReqQryConversionRate(CSecurityFtdcQryConversionRateField *pQryConversionRate, int nRequestID) = 0;

	///请求查询历史信用负债信息
	virtual int ReqQryHisCreditDebtInfo(CSecurityFtdcQryHisCreditDebtInfoField *pQryHisCreditDebtInfo, int nRequestID) = 0;

	///请求查询行情静态信息
	virtual int ReqQryMarketDataStaticInfo(CSecurityFtdcQryMarketDataStaticInfoField *pQryMarketDataStaticInfo, int nRequestID) = 0;

	///请求查询到期回购信息
	virtual int ReqQryExpireRepurchInfo(CSecurityFtdcQryExpireRepurchInfoField *pQryExpireRepurchInfo, int nRequestID) = 0;

	///请求查询债券质押为标准券比例
	virtual int ReqQryBondPledgeRate(CSecurityFtdcQryBondPledgeRateField *pQryBondPledgeRate, int nRequestID) = 0;

	///请求查询债券质押代码对照关系
	virtual int ReqQryPledgeBond(CSecurityFtdcQryPledgeBondField *pQryPledgeBond, int nRequestID) = 0;

	///请求查询报单
	virtual int ReqQryOrder(CSecurityFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///请求查询成交
	virtual int ReqQryTrade(CSecurityFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///请求查询投资者持仓
	virtual int ReqQryInvestorPosition(CSecurityFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///资金转账查询请求
	virtual int ReqQryFundTransferSerial(CSecurityFtdcQryFundTransferSerialField *pQryFundTransferSerial, int nRequestID) = 0;

	///资金内转流水查询请求
	virtual int ReqQryFundInterTransferSerial(CSecurityFtdcQryFundInterTransferSerialField *pQryFundInterTransferSerial, int nRequestID) = 0;
protected:
	~CSecurityFtdcQueryApi(){};
};
  
#ifndef WINDOWS
	#if __GNUC__ >= 4
		#pragma GCC visibility pop
	#endif
#endif

#endif
