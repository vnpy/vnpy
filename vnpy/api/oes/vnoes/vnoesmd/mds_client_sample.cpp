/*
* make by KeKe 2020/8
*/


#include    <iostream>
#include    "mds_client_sample.h"
#include    <mds_api/mds_async_api.h>
#include    <mds_api/parser/mds_protocol_parser.h>
#include    <sutil/compiler.h>
#include    <sutil/string/spk_strings.h>
#include    <sutil/logger/spk_log.h>


using namespace Quant360;


/* ===================================================================
 * 内部函数声明
 * =================================================================== */

 /* 连接或重新连接完成后的回调函数 (适用于基于异步API的TCP通道和UDP通道) */
static int32    _MdsClientApi_OnAsyncConnect(
	MdsAsyncApiChannelT *pAsyncChannel,
	void *pCallbackParams);

/* 连接断开后的回调函数 (适用于基于异步API的TCP通道和UDP通道) */
static int32    _MdsClientApi_OnAsyncDisconnect(
	MdsAsyncApiChannelT *pAsyncChannel,
	void *pCallbackParams);

/* 连接或重新连接完成后的回调函数 (适用于基于同步API的查询通道) */
static int32    _MdsClientApi_OnQueryConnect(
	MdsApiSessionInfoT *pSessionInfo,
	MdsClientSpi *pSpi);

/* 连接断开后的回调函数 (适用于基于同步API的查询通道) */
static int32    _MdsClientApi_OnQueryDisconnect(
	MdsApiSessionInfoT *pSessionInfo,
	MdsClientSpi *pSpi,
	const MdsApiRemoteCfgT *pQryChannelCfg);

///* 对接收到的回报消息进行处理的回调函数 */
//static int32    _MdsClientApi_HandleReportMsg(
//	MdsApiSessionInfoT *pTcpChannel,
//	SMsgHeadT *pMsgHead,
//	void *pMsgBody,
//	void *pCallbackParams);

/* 对接收到的应答消息进行处理的回调函数 (适用于TCP通道) */
static int32    _MdsClientApi_HandleTcpChannelRsp(
	MdsApiSessionInfoT *pSessionInfo,
	SMsgHeadT *pMsgHead,
	void *pMsgBody,
	void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 上下文管理接口
 * =================================================================== */

 /**
  * 构造函数
  */
MdsClientApi::MdsClientApi() {
	defaultClSeqNo = 0;

	_isInitialized = FALSE;
	_isRunning = FALSE;

	_pSpi = NULL;
	_pAsyncContext = NULL;
	_pDefaultTcpChannel = NULL;
	_pQryChannel = NULL;

	memset(&_apiCfg, 0, sizeof(MdsApiClientCfgT));
	memset(&_qryChannel, 0, sizeof(MdsApiSessionInfoT));
}


/**
 * 析构函数
 */
MdsClientApi::~MdsClientApi() {
	/* Do nothing */
}


/**
 * 注册SPI回调接口
 *
 * @param   pSpi                SPI回调接口
 * @retval  TRUE                设置成功
 * @retval  FALSE               设置失败
 */
void
MdsClientApi::RegisterSpi(MdsClientSpi *pSpi) {
	pSpi->pApi = this;
	this->_pSpi = pSpi;
}


/**
 * 加载配置文件并初始化相关资源
 *
 * @note    在 LoadCfg 之前需要先通过 RegisterSpi 接口注册回调服务
 *
 * @param   pCfgFile            配置文件路径
 * @retval  TRUE                加载成功
 * @retval  FALSE               加载失败
 */
BOOL
MdsClientApi::LoadCfg(const char *pCfgFile) {
	MdsApiClientCfgT        tmpApiCfg;

	if (_isInitialized || _pAsyncContext) {
		SLOG_ERROR("已初始化过, 不能重复初始化! " \
			"isInitialized[%d], pAsyncContext[%p]",
			_isInitialized, _pAsyncContext);
		return FALSE;
	}
	else if (_isRunning) {
		SLOG_ERROR("已经在运行过程中, 不能重复初始化!");
		return FALSE;
	}
	else if (!_pSpi) {
		SLOG_ERROR("尚未注册回调服务, 需要先通过 RegisterSpi 接口注册回调服务!");
		return FALSE;
	}

	if (SStr_IsBlank(pCfgFile)) {
		SLOG_ERROR("配置文件路径不能为空! cfgFile[%s]",
			pCfgFile ? pCfgFile : "NULL");
		return FALSE;
	}

	/* 初始化日志记录器 */
	if (!MdsApi_InitLogger(pCfgFile, MDSAPI_CFG_DEFAULT_SECTION_LOGGER)) {
		SLOG_ERROR("初始化API记录器失败! cfgFile[%s], cfgSection[%s]",
			pCfgFile, MDSAPI_CFG_DEFAULT_SECTION_LOGGER);
		return FALSE;
	}

	/* 解析配置文件 */
	memset(&tmpApiCfg, 0, sizeof(MdsApiClientCfgT));

	if (!MdsApi_ParseAllConfig(pCfgFile, &tmpApiCfg)) {
		SLOG_ERROR("解析配置文件失败! cfgFile[%s]", pCfgFile);
		return FALSE;
	}

	return LoadCfg(&tmpApiCfg, pCfgFile);
}


/**
 * 加载配置信息并初始化相关资源
 *
 * @note    在 LoadCfg 之前需要先通过 RegisterSpi 接口注册回调服务
 *
 * @param   pApiCfg             API配置结构
 * @retval  TRUE                加载成功
 * @retval  FALSE               加载失败
 */
BOOL
MdsClientApi::LoadCfg(MdsApiClientCfgT *pApiCfg, const char *pCfgFile) {
	MdsAsyncApiContextT     *pAsyncContext = (MdsAsyncApiContextT *)NULL;
	MdsAsyncApiChannelT     *pTcpChannel = (MdsAsyncApiChannelT *)NULL;

	if (_isInitialized || _pAsyncContext) {
		SLOG_ERROR("已初始化过, 不能重复初始化! " \
			"isInitialized[%d], pAsyncContext[%p]",
			_isInitialized, _pAsyncContext);
		return FALSE;
	}
	else if (_isRunning) {
		SLOG_ERROR("已经在运行过程中, 不能重复初始化!");
		return FALSE;
	}
	else if (!_pSpi) {
		SLOG_ERROR("尚未注册回调服务, 需要先通过 RegisterSpi 接口注册回调服务!");
		return FALSE;
	}

	if (!pApiCfg) {
		SLOG_ERROR("无效的参数, 不可为空! pApiCfg[%p]", pApiCfg);
		return FALSE;
	}

	if (pApiCfg != &_apiCfg) {
		memcpy(&_apiCfg, pApiCfg, sizeof(MdsApiClientCfgT));
	}

	/* 创建异步API的运行时环境 (初始化日志, 创建上下文环境) */
	pAsyncContext = MdsAsyncApi_CreateContext(pCfgFile);
	if (!pAsyncContext) {
		SLOG_ERROR("创建异步API的运行时环境失败!");
		return FALSE;
	}

	/* 添加初始的TCP通道 */
	if (_apiCfg.tcpChannelCfg.addrCnt > 0) {
		pTcpChannel = MdsAsyncApi_AddChannel(
			pAsyncContext,
			MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR,
			&_apiCfg.tcpChannelCfg,
			(MdsApiSubscribeInfoT *)NULL,
			_MdsClientApi_HandleTcpChannelRsp, _pSpi,
			_MdsClientApi_OnAsyncConnect, _pSpi,
			_MdsClientApi_OnAsyncDisconnect, _pSpi);
		if (__spk_unlikely(!pTcpChannel)) {
			SLOG_ERROR("添加TCP通道失败! channelTag[%s]",
				MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR);
			MdsAsyncApi_ReleaseContext(pAsyncContext);
			return FALSE;
		}
	}


	_pAsyncContext = pAsyncContext;
	_pDefaultTcpChannel = pTcpChannel;
	_isInitialized = TRUE;
	return TRUE;
}




/**
 * 设置客户端的IP地址
 *
 * @param   pIpStr              点分十进制的IP地址字符串
 * @retval  TRUE                成功
 * @retval  FALSE               失败
 */
BOOL
MdsClientApi::SetCustomizedIp(const char *pIpStr) {
	return MdsApi_SetCustomizedIp(pIpStr);
}


/**
 * 设置客户端的MAC地址
 *
 * @param   pMacStr             MAC地址字符串 (MAC地址格式 45:38:56:89:78:5A)
 * @retval  TRUE                成功
 * @retval  FALSE               失败
 */
BOOL
MdsClientApi::SetCustomizedMac(const char *pMacStr) {
	return MdsApi_SetCustomizedMac(pMacStr);
}


/**
 * 设置客户端的设备序列号
 *
 * @note    需要在 Start 前调用
 *
 * @param   pDriverIdStr        设备序列号字符串
 * @retval  TRUE                成功
 * @retval  FALSE               失败
 */
BOOL
MdsClientApi::SetCustomizedDriverId(const char *pDriverIdStr) {
	return MdsApi_SetCustomizedDriverId(pDriverIdStr);
}


/**
 * 设置当前线程登录OES时使用的登录用户名
 *
 * @note    需要在 Start 前调用
 *
 * @param   pUsername           登录用户名
 */
void
MdsClientApi::SetThreadUsername(const char *pUsername) {
	MdsApi_SetThreadUsername(pUsername);
}


/**
 * 设置当前线程登录OES时使用的登录密码
 *
 * @note    需要在 Start 前调用
 *
 * @param   pPassword           登录密码
 *                              - 支持通过前缀指定密码类型, 如 md5:PASSWORD, txt:PASSWORD
 */
void
MdsClientApi::SetThreadPassword(const char *pPassword) {
	MdsApi_SetThreadPassword(pPassword);
}




/**
 * 启动交易接口实例
 *
 * @param[out]  pLastClSeqNo    @deprecated 该参数已废弃, 只是为了保持兼容而保留
 *                              可改为使用如下方式替代:
 *                              - 服务器端最后接收到并校验通过的"客户委托流水号"可以通过
 *                                defaultClSeqNo 成员变量直接获取到
 *                              - 也可以重载 SPI.OnConnected 接口, 然后通过
 *                                <code>pSessionInfo->lastOutMsgSeq</code> 获知服
 *                                务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 * @param[in]   lastRptSeqNum   @deprecated 该参数已废弃, 只是为了保持兼容而保留
 *                              可改为使用如下方式替代:
 *                              - 客户端可以在OnConnect回调函数中重新设置
 *                                <code>pSessionInfo->lastInMsgSeq</code> 的取值来
 *                                重新指定初始的回报订阅位置, 效果等同于
 *                                MdsApi_InitRptChannel接口的lastRptSeqNum参数:
 *                                - 等于0, 从头开始推送回报数据 (默认值)
 *                                - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *                                - 小于0, 从最新的数据开始推送回报数据
 * @retval      TRUE            启动成功
 * @retval      FALSE           启动失败
 */
BOOL
MdsClientApi::Start(int32 *pLastClSeqNo, int64 lastRptSeqNum) {
	int32                   ret = 0;

	if (!_isInitialized || !_pAsyncContext) {
		SLOG_ERROR("尚未载入配置, 需要先通过 LoadCfg 接口初始化配置信息! " \
			"isInitialized[%d], pAsyncContext[%p]",
			_isInitialized, _pAsyncContext);
		return FALSE;
	}
	else if (_isRunning) {
		SLOG_ERROR("已经在运行过程中, 不能重复启动!");
		return FALSE;
	}
	else if (!_pSpi) {
		SLOG_ERROR("尚未注册回调服务, 需要先通过 RegisterSpi 接口注册回调服务!");
		return FALSE;
	}

	if (MdsAsyncApi_GetChannelCount(_pAsyncContext) <= 0
		&& _apiCfg.qryChannelCfg.addrCnt <= 0) {
		SLOG_ERROR("尚未配置任何有效的委托/回报/查询通道, 无法启动! " \
			"请检查配置信息是否正确!");
		return FALSE;
	}

	/* 连接查询通道 */
	if (_apiCfg.qryChannelCfg.addrCnt > 0) {
		if (!MdsApi_InitQryChannel2(&_qryChannel, &_apiCfg.qryChannelCfg)) {
			SLOG_ERROR("连接查询通道失败! error[%d - %s]",
				MdsApi_GetLastError(),
				MdsApi_GetErrorMsg(MdsApi_GetLastError()));
			return FALSE;
		}

		_pQryChannel = &_qryChannel;
		_isRunning = TRUE;

		/* 触发查询通道的 OnConnect 回调 */
		ret = _MdsClientApi_OnQueryConnect(_pQryChannel, _pSpi);
		if (ret < 0) {
			SLOG_ERROR("Callback query channel OnConnect failure! ret[%d]", ret);

			Stop();
			return FALSE;
		}
	}
	else {
		SLOG_INFO("未配置查询通道, 将忽略查询通道并继续执行!");
	}

	/* 启动异步API线程 (连接TCP通道和UDP通道) */
	if (MdsAsyncApi_GetChannelCount(_pAsyncContext) > 0) {
		MdsAsyncApi_SetPreconnectAble(_pAsyncContext, TRUE);

		if (!MdsAsyncApi_Start(_pAsyncContext)) {
			SLOG_ERROR("启动异步API线程失败! error[%d - %s]",
				MdsApi_GetLastError(),
				MdsApi_GetErrorMsg(MdsApi_GetLastError()));

			Stop();
			return FALSE;
		}
	}
	else {
		SLOG_INFO("未配置TCP通道或UDP通道, 将仅连接查询通道, 无需启动异步API线程!");
	}

	SLOG_INFO("启动交易接口实例...");
	_isRunning = TRUE;

	return TRUE;
}


/**
 * 停止交易接口实例并释放相关资源
 */
void
MdsClientApi::Stop(void) {
	if (_isRunning) {
		SLOG_INFO("停止交易接口实例并释放相关资源...");
	}

	/* 停止并销毁异步API线程 */
	if (_pAsyncContext) {
		MdsAsyncApi_Stop(_pAsyncContext);
		MdsAsyncApi_ReleaseContext(_pAsyncContext);
		_pAsyncContext = NULL;
	}

	/* 关闭并销毁查询通道 */
	if (_pQryChannel) {
		MdsApi_Destory(_pQryChannel);
		_pQryChannel = NULL;
	}

	_isRunning = FALSE;
}

/* ===================================================================
 * 订阅TCP行情接口
 * =================================================================== */

BOOL
MdsClientApi::SubscribeMarketData(const MdsMktDataRequestReqT *pMktDataRequestReq, const MdsMktDataRequestEntryT *pEntries) {
	return MdsAsyncApi_SubscribeMarketData(
		_pDefaultTcpChannel,
		pMktDataRequestReq, 
		pEntries
	);
}



/* ===================================================================
 * 回报消息处理和会话管理回调函数
 * =================================================================== */

 /**
  * 连接或重新连接完成后的回调函数 (适用于基于异步API的TCP通道和UDP通道)
  *
  * <p> 回调函数说明:
  * - 对于UDP通道, 需要通过该回调函数完成回报订阅操作。若函数指针为空, 则会使用通道配置中默认的
  *   回报订阅参数进行订阅。若函数指针不为空, 但未订阅回报, 90秒以后服务器端会强制断开连接
  * - 若回调函数返回小于0的数, 则异步线程将中止运行
  * </p>
  *
  * <p> @note 关于上一次会话的最大请求数据编号 (针对TCP通道)
  * - 将通过 lastOutMsgSeq 字段存储上一次会话实际已发送的出向消息序号, 即: 服务器端最
  *   后接收到的客户委托流水号(clSeqNo)
  * - 该值对应的是服务器端最后接收到并校验通过的(同一环境号下的)客户委托流水号, 效果等价
  *   于 MdsApi_InitOrdChannel接口的pLastClSeqNo参数的输出值
  * - 登录成功以后, API会将该值存储在 <code>pAsyncChannel->lastOutMsgSeq</code>
  *   和 <code>pSessionInfo->lastOutMsgSeq</code> 字段中
  * - 该字段在登录成功以后就不会再更新
  * - 客户端若想借用这个字段来维护自增的"客户委托流水号(clSeqNo)"也是可行的, 只是需要注
  *   意该字段在登录后会被重置为服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
  * </p>
  *
  * <p> @note 关于最近接收到的回报数据编号 (针对UDP通道):
  * - 将通过 lastInMsgSeq 字段存储上一次会话实际接收到的入向消息序号, 即: 最近接收到的
  *   回报数据编号
  * - 该字段会在接收到回报数据并回调OnMsg成功以后实时更新, 可以通过该字段获取到最近接收到
  *   的回报数据编号
  * - 当OnConnect函数指针为空时, 会执行默认的回报订阅处理, 此时会自动从断点位置继续订阅
  *   回报数据
  * - 若指定了OnConnect回调函数(函数指针不为空), 则需要显式的执行回报订阅处理
  * - API会将回报数据的断点位置存储在 <code>pAsyncChannel->lastInMsgSeq</code>
  *   和 <code>pSessionInfo->lastInMsgSeq</code> 字段中, 可以使用该值订阅回报
  * - 客户端可以在OnConnect回调函数中重新设置
  *   <code>pSessionInfo->lastInMsgSeq</code> 的取值来重新指定初始的回报订阅位置,
  *   效果等同于MdsApi_InitRptChannel接口的lastRptSeqNum参数:
  *   - 等于0, 从头开始推送回报数据 (默认值)
  *   - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
  *   - 小于0, 从最新的数据开始推送回报数据
  * </p>
  *
  * @param   pAsyncChannel       异步API的连接通道信息
  * @param   pCallbackParams     外部传入的参数
  * @retval  =0                  等于0, 成功
  * @retval  >0                  大于0, 处理失败, 将重建连接并继续尝试执行
  * @retval  <0                  小于0, 处理失败, 异步线程将中止运行
  */
static int32
_MdsClientApi_OnAsyncConnect(MdsAsyncApiChannelT *pAsyncChannel,
	void *pCallbackParams) {
	MdsApiSubscribeInfoT    *pSubscribeInfo = (MdsApiSubscribeInfoT *)NULL;
	MdsClientSpi            *pSpi = (MdsClientSpi *)pCallbackParams;
	int32                   ret = 0;

	SLOG_ASSERT(pAsyncChannel && pAsyncChannel->pSessionInfo);
	SLOG_ASSERT(pSpi && pSpi->pApi);

	if (__spk_unlikely(!pAsyncChannel || !pSpi)) {
		SLOG_ERROR("Invalid params! pAsyncChannel[%p], pCallbackParams[%p]",
			pAsyncChannel, pCallbackParams);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}
	else if (__spk_unlikely(!pSpi->pApi)) {
		SLOG_ERROR("Invalid SPI.pApi pointer! pApi[%p]", pSpi->pApi);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}


	/*
	 * 返回值说明
	 * - 等于0, 成功 (不再执行默认的回调函数)
	 * - 大于0, 忽略本次执行, 并继续执行默认的回调函数
	 * - 小于0, 处理失败, 异步线程将中止运行
	 */
	ret = pSpi->OnConnected(
		(eMdsApiChannelTypeT)pAsyncChannel->pChannelCfg->channelType,
		pAsyncChannel->pSessionInfo, pSubscribeInfo);
	if (__spk_unlikely(ret < 0)) {
		SLOG_ERROR("Call SPI.OnConnected failure! channelType[%d], ret[%d]",
			pAsyncChannel->pChannelCfg->channelType, ret);
		return ret;
	} if (ret == 0) {
		SLOG_DEBUG("Call SPI.OnConnected success! channelType[%d]",
			pAsyncChannel->pChannelCfg->channelType);
		return 0;
	}

	/* 执行默认处理 */
	switch (pAsyncChannel->pChannelCfg->channelType) {
	case MDSAPI_CHANNEL_TYPE_TCP:
		SLOG_INFO("Order channel connected. server[%s:%d], " \
			"lastOutMsgSeq[%" __SPK_FMT_LL__ "d]",
			pAsyncChannel->pSessionInfo->channel.remoteAddr,
			pAsyncChannel->pSessionInfo->channel.remotePort,
			pAsyncChannel->pSessionInfo->lastOutMsgSeq);

		/*
		 * 关于 lastOutMsgSeq 字段 (登录时服务器返回的上一次会话的最大请求数据编号)
		 * @note 提示:
		 * - 该字段存储的是登录成功以后, 服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)",
		 *   效果等价于MdsApi_InitOrdChannel接口的pLastClSeqNo参数的输出值
		 * - 该字段在登录成功以后就不会再更新
		 * - 对于SPI回调接口, 在OnConnect回调函数中直接更新 API.defaultClSeqNo 字段即可
		 */
		if (pSpi->pApi->defaultClSeqNo < pAsyncChannel->lastOutMsgSeq) {
			pSpi->pApi->defaultClSeqNo = pAsyncChannel->lastOutMsgSeq;
		}
		break;


		///*
		// * 关于 lastInMsgSeq 字段 (最近接收到的回报数据编号)
		// * @note 提示:
		// * - API会将回报数据的断点位置存储在 <code>pAsyncChannel->lastInMsgSeq</code> 和
		// *   <code>pSessionInfo->lastInMsgSeq</code> 字段中, 可以使用该值订阅回报
		// * - 对于SPI回调接口, 可以在OnConnect回调函数中重新设置
		// *   <code>pSessionInfo->lastInMsgSeq</code> 的取值来重新指定订阅条件
		// */
		//if (__spk_unlikely(!MdsApi_SendReportSynchronization(
		//	pAsyncChannel->pSessionInfo, pSubscribeInfo->clEnvId,
		//	pSubscribeInfo->rptTypes,
		//	pAsyncChannel->pSessionInfo->lastInMsgSeq))) {
		//	SLOG_ERROR("Send report synchronization failure, will retry! " \
		//		"server[%s:%d]",
		//		pAsyncChannel->pSessionInfo->channel.remoteAddr,
		//		pAsyncChannel->pSessionInfo->channel.remotePort);

		//	/* 处理失败, 将重建连接并继续尝试执行 */
		//	return EAGAIN;
		//}
		//break;

	case MDSAPI_CHANNEL_TYPE_QUERY:
	default:
		SLOG_ERROR("Invalid channel type! channelType[%d]",
			pAsyncChannel->pChannelCfg->channelType);
		SLOG_ASSERT(0);

		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}

	return 0;
}


/**
 * 连接断开后的回调函数 (适用于基于异步API的TCP通道和UDP通道)
 *
 * <p> 回调函数说明:
 * - 仅用于通知客户端连接已经断开, 无需做特殊处理, 异步线程会自动尝试重建连接
 * - 若函数指针为空, 异步线程会自动尝试重建连接并继续执行
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * @param   pAsyncChannel       异步API的连接通道信息
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 异步线程将尝试重建连接并继续执行
 * @retval  <0                  小于0, 异步线程将中止运行
 */
static int32
_MdsClientApi_OnAsyncDisconnect(MdsAsyncApiChannelT *pAsyncChannel,
	void *pCallbackParams) {
	MdsClientSpi            *pSpi = (MdsClientSpi *)pCallbackParams;
	int32                   ret = 0;

	SLOG_ASSERT(pAsyncChannel && pAsyncChannel->pSessionInfo);
	SLOG_ASSERT(pSpi);

	if (__spk_unlikely(!pAsyncChannel || !pSpi)) {
		SLOG_ERROR("Invalid params! pAsyncChannel[%p], pCallbackParams[%p]",
			pAsyncChannel, pCallbackParams);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}

	/*
	 * 返回值说明
	 * - 等于0, 成功 (不再执行默认的回调函数)
	 * - 大于0, 忽略本次执行, 并继续执行默认的回调函数
	 * - 小于0, 处理失败, 异步线程将中止运行
	 */
	ret = pSpi->OnDisconnected(
		(eMdsApiChannelTypeT)pAsyncChannel->pChannelCfg->channelType,
		pAsyncChannel->pSessionInfo);
	if (__spk_unlikely(ret < 0)) {
		SLOG_ERROR("Call SPI.OnDisconnected failure! channelType[%d], ret[%d]",
			pAsyncChannel->pChannelCfg->channelType, ret);
		return ret;
	} if (ret == 0) {
		SLOG_DEBUG("Call SPI.OnDisconnected success! channelType[%d]",
			pAsyncChannel->pChannelCfg->channelType);
		return 0;
	}

	/* 执行默认处理 */
	SLOG_INFO("%s channel disconnected! " \
		"server[%s:%d], channelType[%d], " \
		"channelInMsg[%" __SPK_FMT_LL__ "d], " \
		"channelOutMsg[%" __SPK_FMT_LL__ "d]",
		pAsyncChannel->pChannelCfg->channelType
		== MDSAPI_CHANNEL_TYPE_TCP ? "Order" : "Report",
		pAsyncChannel->pSessionInfo->channel.remoteAddr,
		pAsyncChannel->pSessionInfo->channel.remotePort,
		pAsyncChannel->pChannelCfg->channelType,
		pAsyncChannel->pSessionInfo->nextInMsgSeq,
		pAsyncChannel->pSessionInfo->nextOutMsgSeq);

	return 0;
}


/**
 * 连接或重新连接完成后的回调函数 (适用于基于同步API的查询通道)
 *
 * @param   pSessionInfo        会话信息
 * @param   pCallbackParams     外部传入的参数
 * @retval  =0                  等于0, 成功
 * @retval  >0                  大于0, 处理失败, 将重建连接并继续尝试执行
 * @retval  <0                  小于0, 处理失败, 异步线程将中止运行
 */
static int32
_MdsClientApi_OnQueryConnect(MdsApiSessionInfoT *pSessionInfo,
	MdsClientSpi *pSpi) {
	int32                   ret = 0;

	SLOG_ASSERT(pSessionInfo
		&& pSessionInfo->__channelType == MDSAPI_CHANNEL_TYPE_QUERY);
	SLOG_ASSERT(pSpi);

	if (__spk_unlikely(!pSessionInfo || !pSpi)) {
		SLOG_ERROR("Invalid params! pSessionInfo[%p], pSpi[%p]",
			pSessionInfo, pSpi);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}

	/*
	 * 返回值说明
	 * - 等于0, 成功 (不再执行默认的回调函数)
	 * - 大于0, 忽略本次执行, 并继续执行默认的回调函数
	 * - 小于0, 处理失败, 异步线程将中止运行
	 */
	ret = pSpi->OnConnected(MDSAPI_CHANNEL_TYPE_QUERY, pSessionInfo);
	if (__spk_unlikely(ret < 0)) {
		SLOG_ERROR("Call SPI.OnConnected failure! channelType[%d], ret[%d]",
			MDSAPI_CHANNEL_TYPE_QUERY, ret);
		return ret;
	} if (ret == 0) {
		SLOG_DEBUG("Call SPI.OnConnected success! channelType[%d]",
			MDSAPI_CHANNEL_TYPE_QUERY);
		return 0;
	}

	/* 执行默认处理 */
	SLOG_INFO("Query channel connected. server[%s:%d], " \
		"lastOutMsgSeq[%" __SPK_FMT_LL__ "d]",
		pSessionInfo->channel.remoteAddr, pSessionInfo->channel.remotePort,
		pSessionInfo->lastOutMsgSeq);

	return 0;
}


/**
 * 连接断开后的回调函数 (适用于基于同步API的查询通道)
 *
 * <p> 回调函数说明:
 * - 仅用于通知客户端连接已经断开, 无需做特殊处理, 异步线程会自动尝试重建连接
 * - 若函数指针为空, 异步线程会自动尝试重建连接并继续执行
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * @param   pSessionInfo        会话信息
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 异步线程将尝试重建连接并继续执行
 * @retval  <0                  小于0, 异步线程将中止运行
 */
static int32
_MdsClientApi_OnQueryDisconnect(MdsApiSessionInfoT *pSessionInfo,
	MdsClientSpi *pSpi, const MdsApiRemoteCfgT *pQryChannelCfg) {
	int32                   ret = 0;

	SLOG_ASSERT(pSessionInfo
		&& (pSessionInfo->__channelType == MDSAPI_CHANNEL_TYPE_QUERY
			|| __SPK_IS_INVALID_SOCKET(pSessionInfo->socketFd)));
	SLOG_ASSERT(pSpi && pQryChannelCfg);

	if (__spk_unlikely(!pSessionInfo || !pSpi || !pQryChannelCfg)) {
		SLOG_ERROR("Invalid params! " \
			"pSessionInfo[%p], pSpi[%p], pQryChannelCfg[%p]",
			pSessionInfo, pSpi, pQryChannelCfg);
		SPK_SET_ERRNO(EINVAL);
		return SPK_NEG(EINVAL);
	}

	if (!__SPK_IS_INVALID_SOCKET(pSessionInfo->socketFd)) {
		/*
		 * 返回值说明
		 * - 等于0, 成功 (不再执行默认的回调函数. 但对于查询通道仍将继续执行连接重建处理)
		 * - 大于0, 忽略本次执行, 并继续执行默认的回调函数
		 * - 小于0, 处理失败, 异步线程将中止运行
		 */
		ret = pSpi->OnDisconnected(MDSAPI_CHANNEL_TYPE_QUERY, pSessionInfo);
		if (__spk_unlikely(ret < 0)) {
			SLOG_ERROR("Call SPI.OnDisconnected failure! channelType[%d], ret[%d]",
				MDSAPI_CHANNEL_TYPE_QUERY, ret);
			return ret;
		} if (ret == 0) {
			/* 对于查询通道仍将继续执行连接重建处理 */
			SLOG_DEBUG("Call SPI.OnDisconnected success. " \
				"Will try reconnect immediately... " \
				"server[%s:%d], channelType[%d], " \
				"channelInMsg[%" __SPK_FMT_LL__ "d], " \
				"channelOutMsg[%" __SPK_FMT_LL__ "d]",
				pSessionInfo->channel.remoteAddr,
				pSessionInfo->channel.remotePort, MDSAPI_CHANNEL_TYPE_QUERY,
				pSessionInfo->nextInMsgSeq, pSessionInfo->nextOutMsgSeq);
		}
		else {
			SLOG_INFO("Query channel disconnected, try reconnect immediately... " \
				"server[%s:%d], channelType[%d], " \
				"channelInMsg[%" __SPK_FMT_LL__ "d], " \
				"channelOutMsg[%" __SPK_FMT_LL__ "d]",
				pSessionInfo->channel.remoteAddr,
				pSessionInfo->channel.remotePort, MDSAPI_CHANNEL_TYPE_QUERY,
				pSessionInfo->nextInMsgSeq, pSessionInfo->nextOutMsgSeq);
		}
	}
	else {
		SLOG_DEBUG("Try reconnect query channel... " \
			"server[%s:%d], channelType[%d], " \
			"channelInMsg[%" __SPK_FMT_LL__ "d], " \
			"channelOutMsg[%" __SPK_FMT_LL__ "d]",
			pSessionInfo->channel.remoteAddr,
			pSessionInfo->channel.remotePort, MDSAPI_CHANNEL_TYPE_QUERY,
			pSessionInfo->nextInMsgSeq, pSessionInfo->nextOutMsgSeq);
	}

	/* 立即销毁并重新连接查询通道 */
	MdsApi_Destory(pSessionInfo);

	if (!MdsApi_InitQryChannel2(pSessionInfo, pQryChannelCfg)) {
		SLOG_ERROR("尝试重新连接查询通道失败! error[%d - %s]",
			MdsApi_GetLastError(),
			MdsApi_GetErrorMsg(MdsApi_GetLastError()));

		/* 将等到下次查询失败后, 才会再次触发重建连接 */
		return EAGAIN;
	}

	/* 重建连接成功 */
	return _MdsClientApi_OnQueryConnect(pSessionInfo, pSpi);
}


///**
// * 对接收到的回报消息进行处理的回调函数 (适用于UDP通道)
// *
// * @param   pSessionInfo        会话信息
// * @param   pMsgHead            消息头
// * @param   pMsgBody            消息体数据
// * @param   pCallbackParams     外部传入的参数
// * @retval  >=0                 大于等于0, 成功
// * @retval  <0                  小于0, 处理失败, 将尝试断开并重建连接
// *
// * @see     eOesMsgTypeT
// * @see     OesRspMsgBodyT
// * @see     OesRptMsgT
// */
//static int32
//_MdsClientApi_HandleReportMsg(MdsApiSessionInfoT *pSessionInfo,
//	SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
//	MdsClientSpi            *pSpi = (MdsClientSpi *)pCallbackParams;
//	OesRspMsgBodyT          *pRspMsg = (OesRspMsgBodyT *)pMsgBody;
//	OesRptMsgT              *pRptMsg = &pRspMsg->rptMsg;
//
//	SLOG_ASSERT(pSessionInfo && pMsgHead && pMsgBody);
//	SLOG_ASSERT(pSpi);
//
//	switch (pMsgHead->msgId) {
//
//
//	case OESMSG_RPT_REPORT_SYNCHRONIZATION:                 /* 回报同步的应答消息 @see OesReportSynchronizationRspT */
//		pSpi->OnReportSynchronizationRsp(&pRspMsg->reportSynchronizationRsp);
//		break;
//
//	default:
//		/* 接收到非预期(未定义处理方式)的回报消息 */
//		SLOG_ERROR("Invalid message type! msgId[0x%02X]",
//			pMsgHead->msgId);
//		break;
//	}
//
//	return 0;
//}


/**
 * 对接收到的应答消息进行处理的回调函数 (适用于TCP通道)
 *
 * @param   pSessionInfo        会话信息
 * @param   pMsgHead            消息头
 * @param   pMsgBody            消息体数据
 * @param   pCallbackParams     外部传入的参数
 * @retval  >=0                 大于等于0, 成功
 * @retval  <0                  小于0, 处理失败, 将尝试断开并重建连接
 *
 * @see     eOesMsgTypeT
 * @see     OesRspMsgBodyT
 */
static int32
_MdsClientApi_HandleTcpChannelRsp(MdsApiSessionInfoT *pSessionInfo,
	SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
	MdsClientSpi            *pSpi = (MdsClientSpi *)pCallbackParams;
	MdsMktRspMsgBodyT          *pRspMsg = (MdsMktRspMsgBodyT *)pMsgBody;

	SLOG_ASSERT(pSessionInfo && pMsgHead && pMsgBody);

	switch (pMsgHead->msgId) {
	case MDS_MSGTYPE_HEARTBEAT:                 /* 心跳消息 */
		SLOG_DEBUG(">>> Recv heartbeat message.");
		break;

	case MDS_MSGTYPE_TEST_REQUEST:              /* 测试请求消息 */
		SLOG_DEBUG(">>> Recv test-request response message.");
		break;

	case MDS_MSGTYPE_MARKET_DATA_REQUEST:         /* 证券行情订阅消息 (5/0x05) */
		SLOG_DEBUG(">>> Recv market-data-request response message. ");
		break;

	case MDS_MSGTYPE_LOGOUT:         /*  */
		SLOG_DEBUG(">>> Recv logout message. ");
		break;

	case MDS_MSGTYPE_COMPRESSED_PACKETS:         /*  */
		SLOG_DEBUG(">>> Recv compressed message. ");
		break;


	default:
		/* 接收到非预期(未定义处理方式)的回报消息 */
		SLOG_ERROR("Invalid message type! msgId[0x%02X]",
			pMsgHead->msgId);
		break;
	}

	return 0;
}


/* ===================================================================
 * 委托申报接口
 * =================================================================== */



 /* ===================================================================
  * 查询接口
  * =================================================================== */

  /**
   * 获取API的发行版本号
   *
   * @return  API的发行版本号 (如: "0.15.3")
   */
const char *
MdsClientApi::GetVersion(void) {
	return MdsApi_GetApiVersion();
}





/* ===================================================================
 * 默认的SPI回调接口实现
 * =================================================================== */

 /**
  * 构造函数
  */
MdsClientSpi::MdsClientSpi() {
	pApi = NULL;
	currentRequestId = 0;
}


/**
 * 连接或重新连接完成后的回调函数的默认实现
 *
 * <p> 回调函数说明:
 * - 对于UDP通道, 需要通过该回调函数完成回报订阅操作。若函数指针为空, 则会使用通道配置中默认的
 *   回报订阅参数进行订阅。若函数指针不为空, 但未订阅回报, 90秒以后服务器端会强制断开连接
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * <p> @note 关于上一次会话的最大请求数据编号 (针对TCP通道)
 * - 将通过 lastOutMsgSeq 字段存储上一次会话实际已发送的出向消息序号, 即: 服务器端最
 *   后接收到的客户委托流水号(clSeqNo)
 * - 该值对应的是服务器端最后接收到并校验通过的(同一环境号下的)客户委托流水号, 效果等价
 *   于 MdsApi_InitOrdChannel接口的pLastClSeqNo参数的输出值
 * - 登录成功以后, API会将该值存储在 <code>pAsyncChannel->lastOutMsgSeq</code>
 *   和 <code>pSessionInfo->lastOutMsgSeq</code> 字段中
 * - 该字段在登录成功以后就不会再更新
 * - 客户端若想借用这个字段来维护自增的"客户委托流水号(clSeqNo)"也是可行的, 只是需要注
 *   意该字段在登录后会被重置为服务器端最后接收到并校验通过的"客户委托流水号(clSeqNo)"
 * </p>
 *
 * <p> @note 关于最近接收到的回报数据编号 (针对UDP通道):
 * - 将通过 lastInMsgSeq 字段存储上一次会话实际接收到的入向消息序号, 即: 最近接收到的
 *   回报数据编号
 * - 该字段会在接收到回报数据并回调OnMsg成功以后实时更新, 可以通过该字段获取到最近接收到
 *   的回报数据编号
 * - 当OnConnect函数指针为空时, 会执行默认的回报订阅处理, 此时会自动从断点位置继续订阅
 *   回报数据
 * - 若指定了OnConnect回调函数(函数指针不为空), 则需要显式的执行回报订阅处理
 * - API会将回报数据的断点位置存储在 <code>pAsyncChannel->lastInMsgSeq</code>
 *   和 <code>pSessionInfo->lastInMsgSeq</code> 字段中, 可以使用该值订阅回报
 * - 客户端可以在OnConnect回调函数中重新设置
 *   <code>pSessionInfo->lastInMsgSeq</code> 的取值来重新指定初始的回报订阅位置,
 *   效果等同于MdsApi_InitRptChannel接口的lastRptSeqNum参数:
 *   - 等于0, 从头开始推送回报数据 (默认值)
 *   - 大于0, 以指定的回报编号为起点, 从该回报编号的下一条数据开始推送
 *   - 小于0, 从最新的数据开始推送回报数据
 * </p>
 *
 * @param   channelType         通道类型
 * @param   pSessionInfo        会话信息
 * @param   pSubscribeInfo      默认的回报订阅参数 (仅适用于UDP通道)
 * @retval  =0                  等于0, 成功 (不再执行默认的回调函数)
 * @retval  >0                  大于0, 忽略本次执行, 并继续执行默认的回调函数
 * @retval  <0                  小于0, 处理失败, 异步线程将中止运行
 */
int32
MdsClientSpi::OnConnected(eMdsApiChannelTypeT channelType,
	MdsApiSessionInfoT *pSessionInfo,
	MdsApiSubscribeInfoT *pSubscribeInfo) {
	/*
	 * 返回值说明:
	 * - 返回大于0的值, 表示需要继续执行默认的 OnConnect 回调函数 (对于UDP通道, 将使用配置
	 *   文件中的订阅参数订阅回报)
	 * - 若返回0, 表示已经处理成功 (包括UDP通道的回报订阅操作也需要显式的调用并执行成功), 将
	 *   不再执行默认的回调函数
	 */
	return EAGAIN;
}


/**
 * 连接断开后的回调函数的默认实现
 *
 * <p> 回调函数说明:
 * - 仅用于通知客户端连接已经断开, 无需做特殊处理, 异步线程会自动尝试重建连接
 * - 若函数指针为空, 异步线程会自动尝试重建连接并继续执行
 * - 若回调函数返回小于0的数, 则异步线程将中止运行
 * </p>
 *
 * @param   channelType         通道类型
 * @param   pSessionInfo        会话信息
 * @param   pSubscribeInfo      默认的回报订阅参数 (仅适用于UDP通道)
 * @retval  =0                  等于0, 成功 (不再执行默认的回调函数. 但对于查询通道仍将继续执行连接重建处理)
 * @retval  >0                  大于0, 忽略本次执行, 并继续执行默认的回调函数
 * @retval  <0                  小于0, 处理失败, 异步线程将中止运行
 */
int32
MdsClientSpi::OnDisconnected(eMdsApiChannelTypeT channelType,
	MdsApiSessionInfoT *pSessionInfo) {
	/*
	 * 返回值说明:
	 * - 返回大于0的值, 表示需要继续执行默认的 OnDisconnect 回调函数
	 * - 若返回0, 表示已经处理成功, 但对于查询通道仍将继续执行连接重建处理
	 */
	return EAGAIN;
}
