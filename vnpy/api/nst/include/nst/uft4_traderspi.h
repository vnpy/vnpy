#ifndef _UFT4_TRADESPI_H
#define _UFT4_TRADESPI_H

#include "uft4_UserApiStruct.h"
#include "uft4_UserApiDataType.h"


#ifdef _WIN32
#if !defined( FUNCTION_CALL_MODE )
#define FUNCTION_CALL_MODE		__stdcall
#endif
#else
#define FUNCTION_CALL_MODE
#endif

#if (defined WIN32) || (defined WIN64)  
#define TRADE_API_EXPORT _declspec(dllexport)
#else
#ifdef HSTRADEAPI_EXPORTS
#define TRADE_API_EXPORT __attribute__((visibility("default"))) 
#else
#define TRADE_API_EXPORT
#endif
#endif

class CUft4_TraderSpi
{
public:
	virtual void OnFrontConnected(){}
	virtual void OnRspUserLogin(CUftRspUserLoginField* pRspUserLogin, CUftRspInfoField* pRspInfo ){}

	//柜台报单录入响应
	virtual void OnAnsOrderInsert(CUftAnsOrderInsertField *pOrderRsp, CUftRspErrorField* pError){}

	//交易所报单录入响应
	virtual void OnRspOrderInsert(CUftRspnOrderInsertField *pOrderRsp, CUftRspErrorField* pError){}

	//柜台报单操作请求响应
	virtual void OnAnsOrderAction(CUftAnsOrderActionField *pOrderAction, CUftRspErrorField* pError){}

	//交易所报单操作请求响应
	virtual void OnRspOrderAction(CUftRspnOrderActionField *pOrderAction, CUftRspErrorField* pError){}


	//报单回报
	virtual void OnOrderRtn(CUftRtnnOrderField* pOrder){}

	//成交回报
	virtual void OnTradeRtn(CUftRtnnTradeField* pOrder){}

	//查询资金回报
	virtual void OnRspTradingAccount(CUftAnsQueryFundField *pRspFund){}

	virtual void OnRspError(CUftRspErrorField* pError){}


	///请求查询报单响应
	virtual void OnRspQryOrder(CUftAnsQueryOrderField *pEntrust, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(CUftAnsQueryTradeField *pTrade, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CUftAnsQueryPositionField *pInvestorPosition, bool bIsLast) {};



	///修改密码响应
	virtual void OnRspQryChangePwd() {};

	virtual void OnRspLogout(const char* szMsg) {};

	virtual void OnRtnInstrumentStatus(CUftRtnInstrumentStatusField *pInstStatus){};

	virtual void OnRspTest(CUftRspTest *pTest){};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CUftRspErrorField* pError) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CUftRspErrorField* pError) {};

};

class CUft4_TraderApi
{
public:
#ifndef OS_WIN
	//nCnnMode与服务端通信方式: 0, udp方式; 1, tcp方式
	static CUft4_TraderApi *CreateUft4Shfe_TraderApi(int nCnnMode = 0);

	static const char* GetApiVersion();
#endif
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;

	///API绑核操作,	支持接收回报和接收主推线程绑定CPU
	///此函数必须在Init之前调用
	///window版不支持
	virtual void TasksetCPU(int nBindingRspCpuId, int nBindingRtnCpuId) = 0;

	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	/*
	*	@param szAccount：证券账号
	*	@param szPwd：密码
	*	@param nReConnTimeout：超时重连时间
	*	@param nTimeStampFlag：时间戳
	*	@param szAccount：心跳间隔微妙
	*	@param eExType：市场
		返回值
		  0, OK
		 -1,sock通讯错误
		 -2,账号格式错误
		 -3,客户端交易模式与服务端不匹配错误
		 -4,服务端返回错误
	*/
	virtual int Init(const char* szAccount, const char* szPwd, int nReConnTimeout = 0, int nTimeStampFlag = 0, int nHeartBtFreq=100,E_EXCHANGE_TYPE eExType = EXCHANGE_CFFEX, int nNoBlock = 0) = 0;

	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;

	/*
	*	@param 	pszFrontAddress 服务器地址
	*	@param 	nPort 服务器端口
	*	@param 	pszLocalAddr 本机地址
	*	@param 	nReqPort 请求端口
	*	@param 	nRspPort 应答端口
	*	@param 	nLocalNotifyPort 主推端口
	*/
	virtual void RegisterFront(const char *pszFrontAddress, uint16_t nPort, const char* pszLocalAddr, uint16_t nReqPort, uint16_t nRspPort, uint16_t nLocalNotifyPort) = 0;
	virtual void RegisterSpi(CUft4_TraderSpi *pSpi) = 0;

	///用户登录请求
	/*
		返回值
			-1,失败
			0,成功
	*/
	virtual int ReqUserLogin() = 0;
	///用户登出请求
	/*
		返回值
			-1,失败
			0,成功
	*/
	virtual int ReqUserLogout() = 0;

	///报单录入请求
	/*
	//  证券NST报单所需入参 begin
	*	@param 	szCode 证券代码
	*	@param 	bs 买卖方向
	*	@param 	dbPrice 价格
	*	@param 	nVolume 数量
	*	@param 	cOrderPriceType 委托类别
	*	@param 	nSeatId 席位ID， 默认为0
	//  证券NST报单所需入参 end
		返回值,-1,失败
				大于0, 本地sendid
	*/
	virtual int ReqOrderInsert(
		const char *szCode, 
		T_UFT_FtdcOrderBs bs,
		char kp, 
		double dbPrice, 
		int nVolume,
		int64_t nOrderRef,
		T_UFT_FtdcTimeConditionType cTimeCondtion = UFT_FTDC_TC_GFD,
		T_UFT_FtdcVolumeConditionType cVolumeCondition = UFT_FTDC_VC_AV,
		T_UFT_FtdcVolumeType	nMinVolume = 1,
		char cMargincheck = '1',
		T_UFT_FtdcOrderPriceTypeType cOrderPriceType = UFT_FTDC_OPT_LimitPrice,
		T_UFT_FtdcHedgeFlagType cHedgeFlagType = UFT_FTDC_HF_Speculation,
		uint8_t nSeatId = 0) = 0;

	///报单操作请求
	/*
		返回值,-1,失败
				大于0,本地sendid
	*/
	virtual int ReqOrderAction(int nOrderIndex, int64_t nOrderRef) = 0;
	///
	/*
		返回值,-1,失败
				大于0,本地sendid
	*/

	///会员资金查询请求
	/*
		返回值,-1,失败
				大于0,本地sendid
	*/
	virtual int ReqTradingAccount()=0;

	///请求查询报单
	/*
	*	@param 	szInstrumentID 证券代码
	*	@param 	nStartTime 开始时间
	*	@param 	nEndTime 结束时间
		返回值,-1,失败
				大于0,本地sendid
	*/
	virtual int ReqQryOrder(const char* szInstrumentID, int32_t nStartTime, int32_t nEndTime, const char* szOrderSysID, int64_t nOrderRef,  uint32_t nOrderIndex, bool bAllSession = false) = 0;
	
	///请求查询成交
	/*
		返回值,-1,失败
				大于0,本地sendid
	*/
	virtual int ReqQryTrade(const char* szInstrumentID, int32_t nStartTime, int32_t nEndTime, const char* szOrderSysID, uint32_t nOrderIndex,int64_t nOrderRef, bool bAllSession = false) = 0;

	///请求查询投资者持仓
	/*
		返回值,-1,失败
				大于0,本地sendid
	*/
	virtual int ReqQryInvestorPosition(const char* szInstrumentID) = 0;


	///修改密码请求
	/*
		返回值,-1,失败
				大于0,本地sendid
	*/
	virtual int ReqChangePwd(const char* szNewPwd, const char* szOldPwd) = 0;

	//通讯测试
	/*
		返回值,-1,失败
				大于0,本地sendid
	*/
	virtual int ReqQryTest() = 0;
	virtual uint64_t GetToken() = 0;
	virtual int GetReqPort() = 0;
};
#ifdef OS_WIN
#ifdef __cplusplus
extern "C"
{
#endif

	TRADE_API_EXPORT CUft4_TraderApi* FUNCTION_CALL_MODE CreateUft4Shfe_TraderApi(int nCnnMode = 0);

	TRADE_API_EXPORT const char* FUNCTION_CALL_MODE GetApiVersion();

#ifdef __cplusplus
}
#endif
#endif

#endif