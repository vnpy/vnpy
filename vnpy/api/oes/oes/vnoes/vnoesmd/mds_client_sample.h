/*
* make by KeKe 2020/8
*/


#ifndef _OES_CPP_API_SAMPLE_H
#define _OES_CPP_API_SAMPLE_H


#include    <mds_api/mds_async_api.h>
#include    <sutil/compiler.h>


namespace   Quant360 {


	/* API类的前置声明 */
	class MdsClientApi;


	/**
	 * 交易接口响应类
	 */
	class MdsClientSpi {
	public:
		/* 连接或重新连接完成后的回调函数 */
		virtual int32       OnConnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo, MdsApiSubscribeInfoT *pSubscribeInfo = NULL);
		/* 连接断开后的回调函数 */
		virtual int32       OnDisconnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo);


	public:
		MdsClientSpi();
		virtual ~MdsClientSpi() {};

	public:
		MdsClientApi        *pApi;
		int32               currentRequestId;
	};


	/**
	 * 交易接口类
	 */
	class MdsClientApi {
	public:
		static const char * GetVersion(void);

	public:
		MdsClientApi();
		virtual ~MdsClientApi();

		/* 注册SPI回调接口 (需要在 LoadCfg 前调用) */
		void                RegisterSpi(MdsClientSpi *pSpi);
		/* 加载配置文件并初始化相关资源 */
		BOOL                LoadCfg(const char *pCfgFile);
		/* 加载配置信息并初始化相关资源 */
		BOOL                LoadCfg(MdsApiClientCfgT *pApiCfg, const char *pCfgFile = NULL);
		/* 设置客户端的IP地址 (需要在 Start 前调用) */
		BOOL                SetCustomizedIp(const char *pIpStr);
		/* 设置客户端的MAC地址 (需要在 Start 前调用) */
		BOOL                SetCustomizedMac(const char *pMacStr);
		/* 设置客户端的设备序列号 (需要在 Start 前调用) */
		BOOL                SetCustomizedDriverId(const char *pDriverStr);
		/* 设置当前线程登录OES时使用的登录用户名 (需要在 Start 前调用) */
		void                SetThreadUsername(const char *pUsername);
		/* 设置当前线程登录OES时使用的登录密码 (需要在 Start 前调用) */
		void                SetThreadPassword(const char *pPassword);


		/* 启动实例 */
		BOOL                Start(int32 *pLastClSeqNo = NULL, int64 lastRptSeqNum = -1);
		/* 停止实例并释放相关资源 */
		void                Stop(void);
		BOOL				SubscribeMarketData(const MdsMktDataRequestReqT *pMktDataRequestReq, const MdsMktDataRequestEntryT *pEntries);


	private:
		/* 禁止拷贝构造函数 */
		MdsClientApi(const MdsClientApi&);
		/* 禁止赋值函数 */
		MdsClientApi&       operator=(const MdsClientApi&);

	public:
		/* 为了方便客户端使用而内置的流水号计数器, 可以基于该字段来递增维护客户端委托流水号 */
		int32               defaultClSeqNo;

	protected:
		MdsApiClientCfgT    _apiCfg;
		MdsApiSessionInfoT  _qryChannel;
		BOOL                _isInitialized;
		BOOL                _isRunning;

		MdsClientSpi        *_pSpi;
		MdsAsyncApiContextT *_pAsyncContext;
		MdsAsyncApiChannelT *_pDefaultOrdChannel;
		MdsAsyncApiChannelT *_pDefaultRptChannel;
		MdsApiSessionInfoT  *_pQryChannel;
	};


}


#endif /* _OES_CPP_API_SAMPLE_H */
