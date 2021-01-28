
#if !defined(NH_STOCKTRADERAPI_H)
#define NH_STOCKTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NhStockUserApiStruct.h"

#if defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT __attribute__ ((visibility("default")))
#endif

namespace nhtd
{
	class CNhStockTraderSpi
	{
	public:
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected() {};

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		///@param nReason 错误原因
		///        0x1001 网络读失败
		///        0x1002 网络写失败
		///        0x2001 接收心跳超时
		///        0x2002 发送心跳失败
		///        0x2003 收到错误报文
		virtual void OnFrontDisconnected(int nReason) {};

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		///@param nTimeLapse 距离上次接收报文的时间
		virtual void OnHeartBeatWarning(int nTimeLapse) {};

		///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
		///@param nTopicID 主题代码（如私有流、公共流、行情流等）
		///@param nSequenceNo 报文序号
		virtual void OnPackageStart(int nTopicID, int nSequenceNo) {};

		///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
		///@param nTopicID 主题代码（如私有流、公共流、行情流等）
		///@param nSequenceNo 报文序号
		virtual void OnPackageEnd(int nTopicID, int nSequenceNo) {};

		///订阅主题应答
		virtual void OnRspSubscribeTopic(CStockFtdcDisseminationField *pDissemination, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///用户登录应答
		virtual void OnRspUserLogin(CStockFtdcRspUserLoginField *pRspUserLogin, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///用户退出应答
		virtual void OnRspUserLogout(CStockFtdcRspUserLogoutField *pRspUserLogout, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///用户密码修改应答
		virtual void OnRspUserPasswordUpdate(CStockFtdcUserPasswordUpdateField *pUserPasswordUpdate, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///股票报单应答
		virtual void OnRspStockInsert(CStockFtdcStockInsertRspField *pStockInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///股票撤单应答
		virtual void OnRspStockCancel(CStockFtdcStockCancelRspField *pStockCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///期权报单应答
		virtual void OnRspOptionsInsert(CStockFtdcOptionsInsertRspField *pOptionsInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///期权撤单应答
		virtual void OnRspOptionsCancel(CStockFtdcOptionsCancelRspField *pOptionsCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///期权报价应答
		virtual void OnRspQuoteInsert(CStockFtdcQuoteInsertRspField *pQuoteInsert, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///期权撤销报价应答
		virtual void OnRspForQuote(CStockFtdcForQuoteRspField *pForQuote, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///询价应答
		virtual void OnRspQuoteCancel(CStockFtdcQuoteCancelRspField *pQuoteCancel, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///证券锁定应答
		virtual void OnRspStockLock(CStockFtdcStockLockRspField *pStockLock, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///行权应答
		virtual void OnRspExercise(CStockFtdcExerciseRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///撤销行权应答
		virtual void OnRspExerciseCancel(CStockFtdcExerciseCancelRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///会员资金查询应答
		virtual void OnRspQryPartAccount(CStockFtdcRspPartAccountField *pRspPartAccount, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///股票报单查询应答
		virtual void OnRspQryStockOrder(CStockFtdcRspQryStockOrderField *pOrder, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///期权报单查询应答
		virtual void OnRspQryOptionsOrder(CStockFtdcRspQryOptionsOrderField *pOrder, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///报价查询应答
		virtual void OnRspQryQuoteOrder(CStockFtdcRspQryQuoteOrderField *pQuote, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///股票成交查询应答
		virtual void OnRspQryStockTrade(CStockFtdcStockTradeField *pTrade, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///期权成交查询应答
		virtual void OnRspQryOptionsTrade(CStockFtdcOptionsTradeField *pTrade, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///持仓查询应答
		virtual void OnRspQryPosition(CStockFtdcRspPositionField *pPosition, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///主题查询应答
		virtual void OnRspQryTopic(CStockFtdcDisseminationField *pDissemination, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		//股票查询应答
		virtual void OnRspQryStock(CStockFtdcRspQryStockField *pStock, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		//期权查询应答
		virtual void OnRspQryOptions(CStockFtdcRspQryOptionsField *pOptions, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///期权委托回报
		virtual void OnRtnOptionsOrder(CStockFtdcOptionsOrderField *pOrder) {};

		///股票委托回报
		virtual void OnRtnStockOrder(CStockFtdcStockOrderField *pOrder) {};

		///报价回报
		virtual void OnRtnQuoteOrder(CStockFtdcQuoteOrderField *pQuote) {};

		///期权成交回报
		virtual void OnRtnOptionsTrade(CStockFtdcOptionsTradeField *pTrade) {};

		///股票成交回报
		virtual void OnRtnStockTrade(CStockFtdcStockTradeField *pTrade) {};

		///行权回报
		virtual void OnRtnExercise(CStockFtdcExerciseRtnField *pExercise) {};

		///查询费率信息应答
		virtual void OnRspQryRate(CStockFtdcRspQryRateField *pRate, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///会员客户查询应答
		virtual void OnRspQryClient(CStockFtdcRspClientField *pRspClient, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///客户保证金查询应答
		virtual void OnRspQryClientMargin(CStockFtdcRspQryClientMarginField *pRspMargin, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///查询行权应答
		virtual void OnRspQryExercise(CStockFtdcExerciseRtnField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

		///出入金通知
		virtual void OnRtnWithdrawDeposit(CStockFtdcWithdrawDepositRtnField *pWithdrawDeposit) {};

		///客户申请组合请求
		virtual void OnRspMarginCombAction(CStockFtdcMarginCombActionRspField *pMarginCombAction, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
		
		///客户申请组合通知
		virtual void OnRtnMarginCombAction(CStockFtdcMarginCombActionRtnField *pMarginCombAction) {};

		///上期所组合持仓查询应答
		virtual void OnRspQrySseCombPosition(CStockFtdcCombPositionRspField *pPosi, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
		
		///组合行权应答
		virtual void OnRspCombExercise(CStockFtdcCombExerciseRspField *pExercise, CStockFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	};

	class TRADER_API_EXPORT CNhStockTraderApi
	{
	public:
		///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为不写日
	///@return 创建出的UserApi
		static CNhStockTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");

		///获取系统版本号
		///@param nMajorVersion 主版本号
		///@param nMinorVersion 子版本号
		///@return 系统标识字符串
		static const char *GetVersion(int &nMajorVersion, int &nMinorVersion);

		///删除接口对象本身
		///@remark 不再使用本接口对象时,调用该函数删除接口对象
		virtual void Release() = 0;

		///初始化
		///@param localIp：如果通过tcpdirect来发送接收数据，则为发送接收数据的网卡ip。
		///@param netWorkCard：如果通过tcpdirect来发送接收数据，则为发送接收数据的网卡名称
		///@remark 初始化运行环境,只有调用后,接口才开始工作
		virtual void Init(const char *localIp = "", const char *netWorkCard = "") = 0;

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
		virtual void RegisterSpi(CNhStockTraderSpi *pSpi) = 0;

		///订阅私有流。
		///@param nResumeType 私有流重传方式
		///        TERT_RESTART:从本交易日开始重传
		///        TERT_RESUME:从上次收到的续传
		///        TERT_QUICK:只传送登录后私有流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
		virtual void SubscribePrivateTopic(SZSE_TE_RESUME_TYPE nResumeType) = 0;

		///订阅公共流。
		///@param nResumeType 公共流重传方式
		///        TERT_RESTART:从本交易日开始重传
		///        TERT_RESUME:从上次收到的续传
		///        TERT_QUICK:只传送登录后公共流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
		virtual void SubscribePublicTopic(SZSE_TE_RESUME_TYPE nResumeType) = 0;

		///订阅交易员流。
		///@param nResumeType 交易员流重传方式
		///        TERT_RESTART:从本交易日开始重传
		///        TERT_RESUME:从上次收到的续传
		///        TERT_QUICK:只传送登录后交易员流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到交易员流的数据。
		virtual void SubscribeUserTopic(SZSE_TE_RESUME_TYPE nResumeType) = 0;

		///设置心跳超时时间。
		///@param timeout 心跳超时时间(秒)
		virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;

		///订阅主题请求
		virtual int ReqSubscribeTopic(CStockFtdcDisseminationField *pDissemination, int nRequestID) = 0;

		///用户登录请求
		virtual int ReqUserLogin(CStockFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

		///用户退出请求
		virtual int ReqUserLogout(CStockFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

		///用户密码修改请求
		virtual int ReqUserPasswordUpdate(CStockFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

		///股票报单请求
		virtual int ReqStockInsert(CStockFtdcStockInsertReqField *pStockInsert, int nRequestID) = 0;

		///股票撤单请求
		virtual int ReqStockCancel(CStockFtdcStockCancelReqField *pStockCancel, int nRequestID) = 0;

		///证券锁定请求
		virtual int ReqStockLock(CStockFtdcStockLockReqField *pStockLock, int nRequestID) = 0;

		///期权报单请求
		virtual int ReqOptionsInsert(CStockFtdcOptionsInsertReqField *pOptionsInsert, int nRequestID) = 0;

		///期权撤单请求
		virtual int ReqOptionsCancel(CStockFtdcOptionsCancelReqField *pOptionsCancel, int nRequestID) = 0;

		///期权报价请求
		virtual int ReqQuoteInsert(CStockFtdcQuoteInsertReqField *pQuoteInsert, int nRequestID) = 0;

		///期权撤销报价请求
		virtual int ReqQuoteCancel(CStockFtdcQuoteCancelReqField *pQuoteCancel, int nRequestID) = 0;

		///询价请求
		virtual int ReqForQuote(CStockFtdcForQuoteReqField *pForQuote, int nRequestID) = 0;

		///行权请求
		virtual int ReqExercise(CStockFtdcExerciseReqField *pExercise, int nRequestID) = 0;

		///撤销行权请求
		virtual int ReqExerciseCancel(CStockFtdcExerciseCancelReqField *pExerciseCancel, int nRequestID) = 0;

		///资金查询请求
		virtual int ReqQryPartAccount(CStockFtdcQryPartAccountField *pQryPartAccount, int nRequestID) = 0;

		///股票报单查询请求
		virtual int ReqQryStockOrder(CStockFtdcQryStockOrderField *pQryOrder, int nRequestID) = 0;

		///期权报单查询请求
		virtual int ReqQryOptionsOrder(CStockFtdcQryOptionsOrderField *pQryOrder, int nRequestID) = 0;

		///报价查询请求
		virtual int ReqQryQuoteOrder(CStockFtdcQryQuoteOrderField *pQryQuote, int nRequestID) = 0;

		///股票成交查询请求
		virtual int ReqQryStockTrade(CStockFtdcQryStockTradeField *pQryTrade, int nRequestID) = 0;

		///期权成交查询请求
		virtual int ReqQryOptionsTrade(CStockFtdcQryOptionsTradeField *pQryTrade, int nRequestID) = 0;

		///持仓查询请求
		virtual int ReqQryPosition(CStockFtdcQryPositionField *pQryPosition, int nRequestID) = 0;

		///主题查询请求
		virtual int ReqQryTopic(CStockFtdcDisseminationField *pDissemination, int nRequestID) = 0;

		//股票查询请求
		virtual int ReqQryStock(CStockFtdcQryStockField *pStock, int nRequestID) = 0;

		//期权查询请求
		virtual int ReqQryOptions(CStockFtdcQryOptionsField *pOptions, int nRequestID) = 0;

		///查询费率信息应答
		virtual int ReqQryRate(CStockFtdcQryRateField *pRate, int nRequestID) = 0;

		///会员客户查询请求
		virtual int ReqQryClient(int nRequestID) = 0;

		///查询保证金计算参数请求
		virtual int ReqQryClientMargin(CStockFtdcQryClientMarginField *pRate, int nRequestID) = 0;

		//行权查询请求
		virtual int ReqQryExercise(CStockFtdcQryExerciseField *pExercise, int nRequestID) = 0;

		///客户申请组合请求
		virtual int ReqMarginCombAction(CStockFtdcMarginCombActionField *pMarginCombAction, int nRequestID) = 0;

		///上交所组合持仓查询请求
		virtual int ReqQrySseCombPosition(CStockFtdcCombPositionField *pPosi, int nRequestID) = 0;

		///组合行权请求
		virtual int ReqCombExercise(CStockFtdcCombExerciseReqField *pExercise, int nRequestID) = 0;
	protected:
		~CNhStockTraderApi(){};
	};
}
#endif
